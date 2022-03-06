/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2022, Open Design Alliance (the "Alliance"). 
// All rights reserved. 
// 
// This software and its documentation and related materials are owned by 
// the Alliance. The software may only be incorporated into application 
// programs owned by members of the Alliance, subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable  
// trade secrets of the Alliance and its suppliers. The software is also 
// protected by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement 
// with their copyright notices:
//   
//   This application incorporates Open Design Alliance software pursuant to a license 
//   agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

using System;
using System.Drawing;
using System.Windows.Forms;
using Teigha.Core;
using Teigha.Visualize;
using WpfVisualizeViewer.Misc;

namespace WpfVisualizeViewer
{
    [Flags]
    public enum DraggerResult
    {
        NothingToDo = 0,
        NeedUpdateCursor = 1,
        NeedUpdateView = 2,
        NeedUFinishDragger = 4,
    };

    /** \details
    Dragging object states.
    */
    [Flags]
    public enum DraggerViewChangeType
    {
        ViewChangePan = 0x00,    // Notify that the view was panned
        ViewChangeZoom = 0x01,    // Notify that the view was zoomed (in/out, window, extents)
        ViewChangeRotate = 0x02,    // Notify that the view was rotated
        ViewChangeFull = 0x04     // Notify that the view parameters was changed
    };

    public abstract class OdTvDragger
    {
        public enum DraggerState
        {
            Waiting,
            Working,
            Finishing
        }

        // state of current dragger
        protected DraggerState State { get; set; }
        // view object
        protected OdTvGsViewId TvView { get; private set; }
        //device, associated with this dragger
        protected OdTvGsDeviceId TvDeviceId { get; private set; }
        // index of active viewport
        protected int TvActiveViewport { get; set; }
        // previous dragger
        protected OdTvDragger PrevDragger { get; set; }
        // true if and only if the dragger have temporary drawable geometry
        protected bool HaveDrawableTemporaryGeometry { get; set; }
        // true if and only if the dragger wants to receive drag without pressed buttons 
        public bool NeedFreeDrag { get; protected set; }
        // color of dragger
        protected OdTvColorDef TvDraggerColor { get; private set; }
        // dragger model id
        protected OdTvModelId TvDraggerModelId { get; private set; }

        // cursors
        public Cursor CurrentCursor { get; set; }
        public Cursor LasAppActiveCursor { get; set; }

        protected MemoryManager MM = MemoryManager.GetMemoryManager();

        public TvWpfViewWCS WCS { get; set; }

        // Constructor
        public OdTvDragger(OdTvGsDeviceId tvDeviceId, OdTvModelId tvDraggersModelId)
        {
            TvDeviceId = tvDeviceId;
            TvDraggerModelId = tvDraggersModelId;
            TvDraggerColor = new OdTvColorDef();

            State = DraggerState.Waiting;
            TvActiveViewport = -1;
            HaveDrawableTemporaryGeometry = false;
            NeedFreeDrag = false;
        }

        /// <summary>
        /// Update base color in dependence of the current background
        /// </summary>
        public void UpdateBaseColor()
        {
            MemoryTransaction mtr = MM.StartTransaction();
            uint bgColor = TvDeviceId.openObject().getBackgroundColor();
            byte[] bytes = new[] { byte.MaxValue, (byte)(bgColor >> 16), (byte)(bgColor >> 8), (byte)(bgColor >> 0) };
            int newColor = BitConverter.ToInt32(bytes, 0);
            Color col = Color.FromArgb(newColor);
            col = col.GetHue() < 128 ? Color.Black : Color.White;
            TvDraggerColor = new OdTvColorDef(col.R, col.G, col.B);
            MM.StopTransaction(mtr);
        }

        /// <summary>
        /// Should be called to prepare dragger for the work
        /// </summary>
        public virtual DraggerResult Start(OdTvDragger prevDragger, int activeView, Cursor cursor, TvWpfViewWCS wcs)
        {
            if (prevDragger != null)
                PrevDragger = prevDragger;

            TvActiveViewport = activeView;

            CurrentCursor = cursor;
            LasAppActiveCursor = cursor;

            WCS = wcs;

            MemoryTransaction mtr = MM.StartTransaction();
            TvView = TvDeviceId.openObject().getActiveView();
            MM.StopTransaction(mtr);

            State = DraggerState.Waiting;

            if (UpdateCursor())
                return DraggerResult.NeedUpdateCursor;

            return DraggerResult.NothingToDo;
        }

        /// <summary>
        /// Should be called to prepare dragger for the work
        /// </summary>
        public virtual DraggerResult Activate()
        {
            if (State == DraggerState.Working || State == DraggerState.Finishing)
                return DraggerResult.NothingToDo;

            State = DraggerState.Working;

            if (UpdateCursor())
                return DraggerResult.NeedUpdateCursor;

            return DraggerResult.NothingToDo;
        }

        /// <summary>
        /// Predominantly should be called on the mouse click
        /// </summary>
        public virtual DraggerResult NextPoint(int x, int y)
        {
            return DraggerResult.NothingToDo;
        }

        /// <summary>
        /// Predominantly should be called on the mouse release
        /// </summary>
        public virtual DraggerResult NextPointUp(int x, int y)
        {
            return DraggerResult.NothingToDo;
        }

        /// <summary>
        /// Predominantly should be called on mouse move
        /// </summary>
        public virtual DraggerResult Drag(int x, int y)
        {
            return DraggerResult.NothingToDo;
        }

        /// <summary>
        /// Should be called before exit the dragger. Returns the previous dragger.
        /// </summary>
        public virtual OdTvDragger Finish(out DraggerResult rc)
        {
            rc = DraggerResult.NothingToDo;

            if (HaveDrawableTemporaryGeometry)
            {
                // remove the draggers model from the view
                RemoveDraggersModelFromView();

                //remove entities from the model
                MemoryTransaction mtr = MM.StartTransaction();
                OdTvModel model = TvDraggerModelId.openObject(OpenMode.kForWrite);
                if (model != null)
                    model.clearEntities();
                MM.StopTransaction(mtr);

                // need redraw after
                rc = DraggerResult.NeedUpdateView;
            }

            // update the state of the dragger
            State = DraggerState.Finishing;

            //reset the dragger
            rc = rc | Reset();

            return PrevDragger;
        }

        /// <summary>
        /// Return true if and only if the dragger can be finished
        /// </summary>
        public virtual bool CanFinish()
        {
            return State == DraggerState.Waiting ? true : false;
        }

        /// <summary>
        /// Process 'enter' pressing
        /// </summary>
        public virtual bool ProcessEnter()
        {
            return false;
        }

        /// <summary>
        /// Process 'escape' pressing
        /// </summary>
        public virtual DraggerResult ProcessEscape()
        {
            return DraggerResult.NothingToDo;
        }

        /// <summary>
        /// Process 'backspace' pressing
        /// </summary>
        public virtual DraggerResult ProcessBackspace()
        {
            return DraggerResult.NothingToDo;
        }

        /// <summary>
        /// Process any key pressing
        /// </summary>
        public virtual DraggerResult ProcessText(string text)
        {
            return DraggerResult.NothingToDo;
        }

        /// <summary>
        /// Formally creating and deleting of the temporary draggers geometry should be performed inside
        /// 'start' and 'finish' methods or in other methods.Modification of such objects should be normally performed
        /// inside 'nextpoint', 'nextpointup' and 'drag' methods.But there are some situations when the geometry should be modified at the wach
        /// view update. For such cases there is this method
        /// </summary>
        public virtual void DrawInvalidate() { }

        public virtual void NotifyAboutViewChange(DraggerViewChangeType type) { }

        /// <summary>
        /// This method updates the cursor (if it is need)
        /// </summary>
        public virtual bool UpdateCursor()
        {
            return false;
        }

        /// <summary>
        /// Returns true if and only of the current dragger has the previous one
        /// </summary>
        public bool HasPrevious()
        {
            return PrevDragger != null;
        }

        /// <summary>
        /// add draggers model to the active view
        /// </summary>
        protected void AddDraggersModelToView()
        {
            MemoryTransaction mtr = MM.StartTransaction();
            if (TvView != null)
                TvView.openObject(OpenMode.kForWrite).addModel(TvDraggerModelId);
            MM.StopTransaction(mtr);
        }
        /// <summary>
        /// Remove the draggers model from active view
        /// </summary>
        protected void RemoveDraggersModelFromView()
        {
            MemoryTransaction mtr = MM.StartTransaction();
            if (TvView != null)
                TvView.openObject(OpenMode.kForWrite).eraseModel(TvDraggerModelId);
            MM.StopTransaction(mtr);
        }
        /// <summary>
        /// Reset the dragger state
        /// </summary>
        protected DraggerResult Reset()
        {
            if (State == DraggerState.Working)
                State = DraggerState.Waiting;

            if (UpdateCursor())
                return DraggerResult.NeedUpdateCursor;

            return DraggerResult.NothingToDo;
        }

        /// <summary>
        /// Method for transform from eye to WCS
        /// </summary>
        protected OdGePoint3d ToEyeToWorld(int x, int y)
        {
            OdGePoint3d wcsPt = new OdGePoint3d(x, y, 0d);
            if (TvView == null)
                return wcsPt;

            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsView view = TvView.openObject();

            if (view.isPerspective())
                wcsPt.z = view.projectionMatrix()[2, 3];

            wcsPt.transformBy((view.screenMatrix() * view.projectionMatrix()).inverse());
            wcsPt.z = 0d;

            // transform to WCS
            wcsPt.transformBy(view.eyeToWorldMatrix());

            MM.StopTransaction(mtr);

            return wcsPt;
        }

        /// <summary>
        /// Method for check correct work of the dragger
        /// </summary>
        protected bool CheckDragger()
        {
            return State != DraggerState.Waiting && TvView != null;
        }
    }
}