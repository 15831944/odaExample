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

namespace WpfVisualizeViewer
{
    public class OdTvPanDragger : OdTvDragger
    {
        // last clicked or moved point (WCS)
        private OdGePoint3d _prevPt = null;
        // last camera position (WCS)
        private OdGePoint3d _pos = null;

        private Cursor _panCursor = Cursors.Default;

        private new MemoryManager MM = MemoryManager.GetMemoryManager();

        public OdTvPanDragger(OdTvGsDeviceId tvDeviceId, OdTvModelId tvDraggersModelId)
            : base(tvDeviceId, tvDraggersModelId)
        {
            Bitmap bitmap = new Bitmap(new Bitmap("Images/Navigation/pan.png"), 20, 20);
            IntPtr handle = bitmap.GetHicon();
            _panCursor = new Cursor(handle);
        }

        public override DraggerResult NextPoint(int x, int y)
        {
            if (State == DraggerState.Waiting || TvView == null)
                return DraggerResult.NothingToDo;
            MemoryTransaction mtr = MM.StartTransaction();
            _pos = TvView.openObject().position();
            _prevPt = ToEyeToWorld(x, y) - _pos.asVector();
            MM.StopTransaction(mtr);

            return DraggerResult.NothingToDo;
        }

        public override DraggerResult Drag(int x, int y)
        {
            if (State == DraggerState.Waiting || TvView == null)
                return DraggerResult.NothingToDo;

            // calculate click point in WCS
            OdGePoint3d pt = ToEyeToWorld(x, y);
            // obtain delta for dolly
            OdGeVector3d delta = (_prevPt - (pt - _pos)).asVector();

            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsView view = TvView.openObject();
            // transform delta to eye
            delta.transformBy(view.viewingMatrix());

            // perform camera moving
            view.dolly(delta.x, delta.y, delta.z);

            // remember the difference between click point in WCS and camera previous position
            _prevPt = pt - _pos.asVector();

            // remember camera current position
            _pos = view.position();

            MM.StopTransaction(mtr);

            return DraggerResult.NeedUpdateView;
        }

        public override DraggerResult NextPointUp(int x, int y)
        {
            return Reset();
        }

        public override bool UpdateCursor()
        {
            switch (State)
            {
                case DraggerState.Waiting:
                case DraggerState.Working:
                    CurrentCursor = _panCursor;
                    break;
                case DraggerState.Finishing:
                    CurrentCursor = LasAppActiveCursor;
                    break;
            }

            return true;
        }
    }
}
