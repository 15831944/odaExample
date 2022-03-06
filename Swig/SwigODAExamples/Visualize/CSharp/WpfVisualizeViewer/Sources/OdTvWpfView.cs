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
using System.Diagnostics;
using System.Drawing;
using Teigha.Visualize;
using Teigha.Core;
using System.Windows.Forms;
using WpfVisualizeViewer.Dialogs;
using WpfVisualizeViewer.Misc;
using WpfVisualizeViewer.ModelBrowser.ObjectProperties;
using MessageBox = System.Windows.Forms.MessageBox;
using OpenMode = Teigha.Visualize.OpenMode;
using System.Collections.Generic;
using WpfVisualizeViewer.ModelBrowser;
using System.Runtime.InteropServices;

namespace WpfVisualizeViewer
{
    public class OdTvWpfView : UserControl
    {
        // Visualize database
        private OdTvDatabaseId _dbId = null;
        public OdTvDatabaseId TvDatabaseId
        {
            get { return _dbId; }
        }
        // Visualize device
        private OdTvGsDeviceId _tvDevice = null;
        public OdTvGsDeviceId TvDeviceId
        {
            get { return _tvDevice; }
        }
        // index of active view
        public int TvActiveViewport = -1;
        // current active dragger
        private OdTvDragger _dragger = null;

        public string FilePath { get; private set; }

        // Models
        private OdTvModelId _tvActiveModelId = null;
        private OdTvModelId _tvMarkupModelId = null;
        private OdTvModelId _tvDraggersModelId = null;
        // cutting planes
        private OdTvModelId _cuttingPlanesModelId = null;
        public OdTvModelId CuttingPlaneModelId { get { return _cuttingPlanesModelId; } }
        private OdTvGsViewId _cuttingPlanesViewId = null;
        public OdTvGsViewId CuttingPlanesViewId { get { return _cuttingPlanesViewId; } }
        private static int CuttingPlaneNum = 0;
        public Draggers.OdTvSectioningOptions SectioningOptions { get; private set; }
        public static int OD_TV_CUTTING_PLANE_MAX_NUM = 5;

        public static OdTvRegAppId AppTvId { get; set; }

        // view-model class
        public OdTvWpfMainWindowModel VM { get; private set; }

        public TvDatabaseInfo DatabaseInfo { get; set; }

        // flag for shift button pressed
        bool _isShiftPressed = false;

        public TvWpfViewWCS WCS { get; set; }

        // index of wcs viewport
        public int TvWcsViewportInd = -1;

        enum MouseDownState
        {
            None,
            LeftMouseBtn,
            MiddleMouseBtn
        }

        private MouseDownState _mouseDown = MouseDownState.None;

        private MemoryManager MM = MemoryManager.GetMemoryManager();

        private Dictionary<OdTvGsViewId, OdTvExtendedView> _extendedViewDict = new Dictionary<OdTvGsViewId, OdTvExtendedView>();

        private OdTvAnimation _animation = null;

        // list with selected items(bold nodes in model browser)
        public List<TvTreeItem> SelectedNodes = new List<TvTreeItem>();

        public OdTvSelectionSet SelectionSet = null;

        public enum ZoomType
        {
            ZoomIn,
            ZoomOut,
            ZoomExtents
        }

        public OdTvWpfView(OdTvWpfMainWindowModel vm)
        {
            this.Paint += OdTvWpfView_Paint; ;
            this.Resize += ResizePanel;
            this.MouseWheel += MouseWheelEvent;
            this.MouseDown += MouseDownEvent;
            this.MouseUp += MouseUpEvent;
            this.MouseMove += MouseMoveEvent;
            this.KeyPress += TextInputEvent;
            VM = vm;
            Size newSize = new Size((int)VM.MainWindow.Width, (int)VM.MainWindow.Height);
            this.Size = newSize;
            SectioningOptions = new Draggers.OdTvSectioningOptions();
        }

        public void ClearDevices()
        {
            MemoryTransaction mtr = MM.StartTransaction();
            if (_dbId != null && !_dbId.isNull() && _dbId.isValid())
                _dbId.openObject(OpenMode.kForWrite).clearDevices();

            _extendedViewDict.Clear();

            MM.StopTransaction(mtr);
        }

        #region Paint and initialization

        private void OdTvWpfView_Paint(object sender, PaintEventArgs e)
        {
            if (!this.Disposing && _tvDevice != null && !_tvDevice.isNull())
            {
                MemoryTransaction mtr = MM.StartTransaction();

                OdTvGsDevice pDevice = _tvDevice.openObject();
                pDevice.update();

                if (_animation != null && _animation.isRunning())
                {
                    _animation.step();
                    Invalidate();
                    if (_dragger != null && !_animation.isRunning())
                        _dragger.NotifyAboutViewChange(DraggerViewChangeType.ViewChangeFull);
                }

                MM.StopTransaction(mtr);
            }
        }

        protected override void OnPaintBackground(PaintEventArgs e) { }

        private void Init()
        {
            if (_dbId == null || _tvDevice == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvDatabase pDb = _dbId.openObject(OpenMode.kForWrite);
            _tvDraggersModelId = pDb.createModel("Draggers", OdTvModel.Type.kDirect);
            OdTvSelectDragger selectDragger = new OdTvSelectDragger(this, _tvActiveModelId, _tvDevice, _tvDraggersModelId);
            _dragger = selectDragger;
            DraggerResult res = _dragger.Start(null, TvActiveViewport, Cursor, WCS);
            ActionAferDragger(res);
            bool exist;
            AppTvId = _dbId.openObject().registerAppName("WPF Visualize Viewer", out exist);

            // find service models
            OdTvResult rc = new OdTvResult();
            rc = OdTvResult.tvOk;
            _tvMarkupModelId = _dbId.openObject().findModel(OdTvMarkupDragger.NameOfMarkupModel, ref rc);
            if (rc != OdTvResult.tvOk)
                _tvMarkupModelId = null;

            // cutting planes
            _cuttingPlanesModelId = pDb.createModel("$ODA_TVVIEWER_SECTIONING_MODEL_" + CuttingPlaneNum, OdTvModel.Type.kMain, false);
            _cuttingPlanesViewId = TvDeviceId.openObject(OpenMode.kForWrite).createView("$ODA_TVVIEWER_SECTIONING_VIEW_" + CuttingPlaneNum++);
            OdTvGsView pVsectioningView = _cuttingPlanesViewId.openObject(OpenMode.kForWrite);
            pVsectioningView.addModel(_cuttingPlanesModelId);
            pVsectioningView.setMode(OdTvGsView.RenderMode.kGouraudShaded);

            // set projection button
            OdTvGsView view = _tvDevice.openObject().viewAt(TvActiveViewport).openObject();
            if (view.isPerspective())
                VM.MainWindow.PerspectiveBtn.IsChecked = true;
            else
                VM.MainWindow.IsometricBtn.IsChecked = true;
            // set render mode
            VM.SetRenderModeButton(view.mode());

            VM.MainWindow.PropertiesPalette.InitializePalette(_tvDevice, this);

            // enable or disable wcs, fps and grid
            OnOffFPS((VM.AppearanceOpt & OdTvWpfMainWindowModel.AppearanceOptions.FPSEnabled) == OdTvWpfMainWindowModel.AppearanceOptions.FPSEnabled);
            OnOffWCS((VM.AppearanceOpt & OdTvWpfMainWindowModel.AppearanceOptions.WCSEnabled) == OdTvWpfMainWindowModel.AppearanceOptions.WCSEnabled);
            OnOffAnimation((VM.AppearanceOpt & OdTvWpfMainWindowModel.AppearanceOptions.UseAnimation) == OdTvWpfMainWindowModel.AppearanceOptions.UseAnimation);

            selectDragger.ObjectSelected += VM.TvObjectExplorer.SelectObject;
            selectDragger.ObjectsSelected += VM.TvPropertiesPalette.ShowSelectionInfo;

            VM.TvObjectExplorer.ResetEvent += VM.TvPropertiesPalette.FillObjectParameters;

            MM.StopTransaction(mtr);
        }

        public OdTvExtendedView GetActiveTvExtendedView()
        {
            OdTvExtendedView exView = null;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsViewId viewId = _tvDevice.openObject().viewAt(TvActiveViewport);
            if (viewId.isNull())
                return null;

            if (_extendedViewDict.ContainsKey(viewId))
                exView = _extendedViewDict[viewId];
            else
            {
                exView = new OdTvExtendedView(viewId);
                exView.setAnimationEnabled((VM.AppearanceOpt & OdTvWpfMainWindowModel.AppearanceOptions.UseAnimation) == OdTvWpfMainWindowModel.AppearanceOptions.UseAnimation);
                exView.setZoomScale(VM.ZoomStep);
                exView.setAnimationDuration(0.9);

                OdTvGsView view = viewId.openObject();
                if (view != null)
                {
                    OdGeBoundBlock3d lastExt = new OdGeBoundBlock3d();
                    if (view.getLastViewExtents(lastExt))
                        exView.setViewExtentsForCaching(lastExt);
                }

                _extendedViewDict.Add(viewId, exView);
            }

            MM.StopTransaction(mtr);

            return exView;
        }

        public void SetAnimation(OdTvAnimation animation)
        {
            _animation = animation;
            if (_animation != null)
                _animation.start();
            else if (_dragger != null)
                _dragger.NotifyAboutViewChange(DraggerViewChangeType.ViewChangeFull);
        }

        #endregion

        #region View settings methods

        public void SetRenderMode(OdTvGsView.RenderMode renderMode)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            if (_tvDevice != null && !_tvDevice.isNull())
            {
                OdTvGsView view = _tvDevice.openObject().viewAt(TvActiveViewport).openObject(OpenMode.kForWrite);
                OdTvGsView.RenderMode oldMode = view.mode();
                if (oldMode != renderMode)
                {
                    view.setMode(renderMode);

                    // set mode for WCS
                    if (WCS != null && (VM.AppearanceOpt & OdTvWpfMainWindowModel.AppearanceOptions.WCSEnabled) == OdTvWpfMainWindowModel.AppearanceOptions.WCSEnabled
                        && WCS.IsNeedUpdateWCS(oldMode, renderMode))
                        WCS.UpdateWCS();

                    _tvDevice.openObject().update();
                    VM.SetRenderModeButton(renderMode);
                }
            }
            MM.StopTransaction(mtr);
        }

        public void SetProjectionType(OdTvGsView.Projection projection)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            if (_tvDevice != null && !_tvDevice.isNull())
            {
                OdTvGsView view = _tvDevice.openObject().viewAt(TvActiveViewport).openObject(OpenMode.kForWrite);
                view.setView(view.position(), view.target(), view.upVector(), view.fieldWidth(), view.fieldHeight(), projection);
                _tvDevice.openObject().update();
            }
            MM.StopTransaction(mtr);
        }

        public void SetBackgroundColor(Color color)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            uint iColor = ((uint)(color.R | color.G << 8 | ((color.B) << 16)));
            if (_tvDevice != null && !_tvDevice.isNull())
            {
                OdTvGsDevice dev = _tvDevice.openObject(OpenMode.kForWrite);
                dev.setBackgroundColor(iColor);
                dev.update();
            }
            MM.StopTransaction(mtr);
        }

        public void Regen(OdTvGsDevice.RegenMode rm)
        {
            if (_tvDevice == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsDevice dev = _tvDevice.openObject();
            dev.regen(rm);
            dev.invalidate();
            dev.update();
            MM.StopTransaction(mtr);
        }

        public void Regen()
        {
            if (_tvDevice == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsDevice dev = _tvDevice.openObject();
            if (TvActiveViewport > 0)
                dev.viewAt(TvActiveViewport).openObject().regen();
            dev.invalidate();
            dev.update();
            MM.StopTransaction(mtr);
        }

        public void Set3DView(OdTvExtendedView.e3DViewType type)
        {
            MemoryTransaction mtr = MM.StartTransaction();

            OdTvExtendedView exView = GetActiveTvExtendedView();
            if (exView == null)
                return;

            // set view type
            exView.setViewType(type);

            //update cached extents if need
            OdGeBoundBlock3d lastExt = new OdGeBoundBlock3d();
            if (!exView.getCachedExtents(lastExt))
            {
                OdTvGsView view = exView.getViewId().openObject();
                if (view.getLastViewExtents(lastExt))
                    exView.setViewExtentsForCaching(lastExt);
            }

            //check existance of the animation
            SetAnimation(exView.getAnimation());

            DisableMarkups();

            Invalidate();

            MM.StopTransaction(mtr);
        }

        public OdGeVector3d GetEyeDirection()
        {
            OdGeVector3d eyeDir = new OdGeVector3d(OdGeVector3d.kIdentity);
            MemoryTransaction mtr = MM.StartTransaction();

            OdTvGsView pView = GetActiveTvExtendedView().getViewId().openObject();
            if(pView != null)
                eyeDir = pView.position() - pView.target();

            MM.StopTransaction(mtr);
            return eyeDir;
        }

        #endregion

        #region Draggers methods

        private void ActionAferDragger(DraggerResult res)
        {
            if ((res & DraggerResult.NeedUpdateCursor) != 0)
                this.Cursor = _dragger.CurrentCursor;

            if ((res & DraggerResult.NeedUpdateView) != 0)
            {
                MemoryTransaction mtr = MM.StartTransaction();
                OdTvGsDevice pDevice = _tvDevice.openObject();
                pDevice.update();
                MM.StopTransaction(mtr);
            }

            if ((res & DraggerResult.NeedUFinishDragger) != 0)
                FinishDragger();
        }

        private void StartDragger(OdTvDragger dragger, bool useCurrentAsPrevious = false)
        {
            DraggerResult res = DraggerResult.NothingToDo;

            if (_dragger == null)
                res = dragger.Start(null, TvActiveViewport, Cursor, WCS);
            else
            {
                OdTvDragger pPrevDragger = _dragger;
                if (_dragger.HasPrevious())
                {
                    DraggerResult res_prev;
                    if (useCurrentAsPrevious)
                        _dragger.Finish(out res_prev);
                    else
                        pPrevDragger = _dragger.Finish(out res_prev);
                    ActionAferDragger(res_prev);
                }
                res = dragger.Start(pPrevDragger, TvActiveViewport, Cursor, WCS);
            }
            // need update active dragger before calling action
            _dragger = dragger;
            ActionAferDragger(res);
        }

        public void FinishDragger()
        {
            if (_dragger != null)
            {
                if (_dragger.HasPrevious() && _dragger.CanFinish())
                {
                    // release current dragger
                    DraggerResult res;
                    OdTvDragger prevDragger = _dragger.Finish(out res);
                    ActionAferDragger(res);

                    // activate previous dragger
                    _dragger = prevDragger;
                    res = _dragger.Start(null, TvActiveViewport, Cursor, WCS);
                    ActionAferDragger(res);
                }
            }
        }

        private void DisableMarkups()
        {
            if (_tvMarkupModelId != null && _dbId != null)
            {
                MemoryTransaction mtr = MM.StartTransaction();

                OdTvModel pMarkupModel = _tvMarkupModelId.openObject(OpenMode.kForWrite);
                if (pMarkupModel == null)
                {
                    MM.StopTransaction(mtr);
                    return;
                }
                OdTvEntitiesIterator pIt = pMarkupModel.getEntitiesIterator();
                if (pIt != null && !pIt.done())
                {
                    while (!pIt.done())
                    {
                        MemoryTransaction mtr2 = MM.StartTransaction();

                        OdTvEntityId entityId = pIt.getEntity();
                        OdTvEntity pEn = entityId.openObject(OpenMode.kForWrite);
                        if (pEn.getName() == OdTvMarkupDragger.NameOfMarkupTempEntity) // if temp entity
                        {
                            pMarkupModel.removeEntity(entityId);
                        }
                        else if (pEn.getVisibility().getType() != OdTvVisibilityDef.VisibilityType.kInvisible)
                        {
                            OdTvGeometryDataIterator pItF = pEn.getGeometryDataIterator();
                            // folds
                            while (!pItF.done())
                            {
                                // objects
                                OdTvEntity pFold = pItF.getGeometryData().openAsSubEntity(OpenMode.kForWrite);
                                OdTvGeometryDataIterator pItO = pFold.getGeometryDataIterator();

                                while (!pItO.done())
                                {
                                    OdTvGeometryDataId geomId = pItO.getGeometryData();
                                    OdTvUserData usrData = geomId.openAsSubEntity(OpenMode.kForWrite).getUserData(AppTvId);
                                    if (usrData == null)
                                        pFold.removeGeometryData(geomId);

                                    pItO.step();
                                }

                                pItF.step();
                            }
                            pEn.setVisibility(new OdTvVisibilityDef(false));
                        }

                        MM.StopTransaction(mtr2);
                        pIt.step();
                    }
                }

                MM.StopTransaction(mtr);
            }
        }

        #endregion

        #region Mouse and key down events

        private void TextInputEvent(object sender, KeyPressEventArgs e)
        {
            if ((int)e.KeyChar == (int)Keys.Back || (int)e.KeyChar == (int)Keys.Escape || (int)e.KeyChar == (int)Keys.Enter)
                return;
            if (_dragger != null)
            {
                DraggerResult? res = _dragger.ProcessText(e.KeyChar.ToString());
                if (res == DraggerResult.NeedUpdateView)
                    ActionAferDragger(DraggerResult.NeedUpdateView);
            }
        }

        public void KeyUpEvent(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if (e.Key == System.Windows.Input.Key.LeftShift || e.Key == System.Windows.Input.Key.RightShift)
            {
                _isShiftPressed = false;
                if (_dragger != null && _dragger is OdTvOrbitDragger)
                    FinishDragger();
            }
        }

        public void KeyDownEvent(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if (e.Key == System.Windows.Input.Key.Escape && _dragger != null)
            {
                VM.UncheckDraggersBtns();
                DraggerResult res = _dragger.ProcessEscape();
                ActionAferDragger(res);
                VM.TvObjectExplorer.ResetBrowser();
                FinishDragger();
                ClearSelectionSet();
                _mouseDown = MouseDownState.None;
            }
            else if (e.Key == System.Windows.Input.Key.Enter && _dragger != null)
            {
                bool? isNeedFinish = _dragger.ProcessEnter();
                if (isNeedFinish == true)
                {
                    FinishDragger();
                    _mouseDown = MouseDownState.None;
                }
            }
            else if (e.Key == System.Windows.Input.Key.Back && _dragger != null)
            {
                DraggerResult? res = _dragger.ProcessBackspace();
                if (res == DraggerResult.NeedUpdateView)
                    ActionAferDragger(DraggerResult.NeedUpdateView);
            }
            else if (e.Key == System.Windows.Input.Key.Back && _dragger != null)
            {
                DraggerResult? res = _dragger.ProcessBackspace();
                if (res == DraggerResult.NeedUpdateView)
                    ActionAferDragger(DraggerResult.NeedUpdateView);
            }
            else if (e.Key == System.Windows.Input.Key.LeftShift || e.Key == System.Windows.Input.Key.RightShift)
                _isShiftPressed = true;
        }

        private void ResizePanel(object sender, EventArgs e)
        {
            if (_tvDevice != null && !this.Disposing)
            {
                MemoryTransaction mtr = MM.StartTransaction();
                OdTvGsDevice dev = _tvDevice.openObject(OpenMode.kForWrite);
                if (this.Width > 0 && this.Height > 0)
                {
                    dev.onSize(new OdTvDCRect(0, this.Width, this.Height, 0));
                    dev.update();
                }
                MM.StopTransaction(mtr);
            }
        }

        private void MouseWheelEvent(object sender, MouseEventArgs e)
        {
            if (_dbId == null || _tvDevice == null)
                return;

            VM.UncheckDraggersBtns();

            MemoryTransaction mtr = MM.StartTransaction();

            FinishDragger();

            OdTvGsDevice dev = _tvDevice.openObject(OpenMode.kForWrite);
            OdTvGsViewId viewId = dev.viewAt(TvActiveViewport);
            OdTvGsView pView = viewId.openObject(OpenMode.kForWrite);
            if (pView == null)
                return;

            OdGePoint2d point = new OdGePoint2d(e.X, e.Y);

            OdGePoint3d pos = new OdGePoint3d(pView.position());
            pos.transformBy(pView.worldToDeviceMatrix());

            int vx, vy;
            vx = (int)pos.x;
            vy = (int)pos.y;

            vx = (int)point.x - vx;
            vy = (int)point.y - vy;

            double scale = 0.9; // wheel down
            if (e.Delta > 0)
                scale = 1.0 / scale; // wheel up

            ScreenDolly(vx, vy);
            pView.zoom(scale);
            ScreenDolly(-vx, -vy);

            dev.update();

            if (_dragger != null)
                _dragger.NotifyAboutViewChange(DraggerViewChangeType.ViewChangeZoom);

            GetActiveTvExtendedView().setViewType(OdTvExtendedView.e3DViewType.kCustom);

            MM.StopTransaction(mtr);
        }

        private void MouseDownEvent(object sender, MouseEventArgs e)
        {
            _mouseDown = e.Button == MouseButtons.Left ? MouseDownState.LeftMouseBtn :
                e.Button == MouseButtons.Middle ? MouseDownState.MiddleMouseBtn : MouseDownState.None;

            if (_dragger == null) return;

            if (_mouseDown == MouseDownState.MiddleMouseBtn)
            {
                VM.UncheckDraggersBtns();
                if (!_isShiftPressed)
                    Pan();
                else
                    Orbit();
            }

            // activation first
            DraggerResult res = _dragger.Activate();
            ActionAferDragger(res);
            res = _dragger.NextPoint(e.X, e.Y);
            ActionAferDragger(res);
        }

        private void MouseUpEvent(object sender, MouseEventArgs e)
        {
            if (_dragger != null)
            {
                DraggerResult res = _dragger.NextPointUp(e.X, e.Y);
                ActionAferDragger(res);
                if (_mouseDown == MouseDownState.MiddleMouseBtn)
                    FinishDragger();
            }

            _mouseDown = MouseDownState.None;
        }

        private void MouseMoveEvent(object sender, MouseEventArgs e)
        {
            if (_dragger != null)
            {
                if ((e.Button == MouseButtons.Left) || (e.Button == MouseButtons.Middle) || _dragger.NeedFreeDrag)
                {
                    DraggerResult res = _dragger.Drag(e.X, e.Y);
                    ActionAferDragger(res);
                }
            }
        }

        #endregion

        #region Navigation commands

        public void Pan()
        {
            if (_dbId == null || _tvDevice == null)
                return;
//             if (_dragger != null && (_dragger as OdTvSelectDragger) == null)
//                 FinishDragger();

            OdTvDragger newDragger = new OdTvPanDragger(_tvDevice, _tvDraggersModelId);
            StartDragger(newDragger, true);
        }

        public void Orbit()
        {
            if (_dbId == null || _tvDevice == null)
                return;

//             if (_dragger != null && (_dragger as OdTvSelectDragger) == null)
//                 FinishDragger();

            OdTvDragger newDragger = new OdTvOrbitDragger(_tvDevice, _tvDraggersModelId);
            StartDragger(newDragger, true);

            DisableMarkups();
        }

        public void Zoom(ZoomType type)
        {
            if (_dbId == null || _tvDevice == null)
                return;

            VM.UncheckDraggersBtns();

            MemoryTransaction mtr = MM.StartTransaction();

            OdTvExtendedView exView = GetActiveTvExtendedView();
            if (exView == null)
                return;
            switch (type)
            {
                case ZoomType.ZoomIn:
                    exView.zoomIn();
                    break;
                case ZoomType.ZoomOut:
                    exView.zoomOut();
                    break;
                case ZoomType.ZoomExtents:
                    {
                        exView.zoomToExtents();
                        //update cached extents if need
                        OdGeBoundBlock3d lastExt = new OdGeBoundBlock3d();
                        if (!exView.getCachedExtents(lastExt))
                        {
                            OdTvGsView view = exView.getViewId().openObject();
                            if (view.getLastViewExtents(lastExt))
                                exView.setViewExtentsForCaching(lastExt);
                        }
                        break;
                    }
                default:
                    throw new ArgumentOutOfRangeException(type.ToString() + " (" + type.GetType().ToString() + ")", type, null);
            }

            SetAnimation(exView.getAnimation());
            exView.setViewType(OdTvExtendedView.e3DViewType.kCustom);

            if (_dragger != null)
                _dragger.NotifyAboutViewChange(DraggerViewChangeType.ViewChangeZoom);

            Invalidate();

            MM.StopTransaction(mtr);
        }

        private void ScreenDolly(int x, int y)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsViewId viewId = _tvDevice.openObject().viewAt(TvActiveViewport);
            OdTvGsView pView = viewId.openObject();
            if (pView == null)
                return;

            OdGeVector3d vec = new OdGeVector3d(x, y, 0);
            vec.transformBy((pView.screenMatrix() * pView.projectionMatrix()).inverse());
            pView.dolly(vec);
            MM.StopTransaction(mtr);
        }

        #endregion

        #region File commands

        public void LoadFile(string filepath)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            this.Cursor = Cursors.WaitCursor;
            OdTvFactoryId factId = TV_Globals.odTvGetFactory();
            factId.clearDatabases();

            try
            {
                bool isVsf = false;
                OdTvBaseImportParams importparam = GetImportParams(filepath, ref isVsf);
                DatabaseInfo = new TvDatabaseInfo
                {
                    FilePath = filepath,
                    Type = isVsf ? TvDatabaseInfo.ProfilingType.FromFile : TvDatabaseInfo.ProfilingType.Import
                };

                importparam.setFilePath(filepath);
                importparam.setProfiling(DatabaseInfo);

                Stopwatch timer = Stopwatch.StartNew();
                timer.Start();
                _dbId = isVsf ? factId.readFile(importparam.getFilePath()) : factId.importFile(importparam);
                timer.Stop();
                DatabaseInfo.ImportTime = timer.ElapsedMilliseconds;
            }
            catch
            {
                MessageBox.Show("Import failed!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                Cursor = Cursors.Default;
                return;
            }

            if (_dbId != null)
            {
                OdTvDatabase pDb = _dbId.openObject(OpenMode.kForWrite);
                PDFExportParams pdfParams = new PDFExportParams();
                _tvActiveModelId = pDb == null ? null : pDb.getModelsIterator().getModel();
                if (_tvActiveModelId == null)
                {
                    MessageBox.Show("Import failed!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    Cursor = Cursors.Default;
                    MM.StopTransaction(mtr);
                    if (VM.FileIsExist)
                    {
                        VM.ClearRenderArea();
                    }

                    return;
                }

                OdTvDevicesIterator devIt = pDb.getDevicesIterator();
                if (devIt != null && !devIt.done())
                {
                    _tvDevice = devIt.getDevice();
                    OdTvGsDevice dev = _tvDevice.openObject(OpenMode.kForWrite);
                    IntPtr wndHndl = new IntPtr(this.Handle.ToInt32());
                    OdTvDCRect rect = new OdTvDCRect(0, this.Width, this.Height, 0);
                    dev.setupGs(wndHndl, rect, OdTvGsDevice.Name.kOpenGLES2);

                    for (int i = 0; i < dev.numViews(); i++)
                    {
                        MemoryTransaction viewTr = MM.StartTransaction();
                        if (dev.viewAt(i).openObject().getActive())
                            TvActiveViewport = i;
                        MM.StopTransaction(viewTr);
                    }
                    if (TvActiveViewport < 0)
                    {
                        TvActiveViewport = 0;
                        dev.viewAt(0).openObject(OpenMode.kForWrite).setActive(true);
                    }

                    dev.onSize(rect);
                    Stopwatch timer = Stopwatch.StartNew();
                    timer.Start();
                    dev.update();
                    timer.Stop();
                    DatabaseInfo.FirstUpdateTime = timer.ElapsedMilliseconds;
                }
                else if (devIt != null && devIt.done())
                {
                    _tvDevice = CreateNewDevice();
                    Stopwatch timer = Stopwatch.StartNew();
                    timer.Start();
                    _tvDevice.openObject().update();
                    timer.Stop();
                    DatabaseInfo.FirstUpdateTime = timer.ElapsedMilliseconds;
                }

                FilePath = filepath;
                VM.FileIsExist = true;
                Init();
                VM.MainWindow.ModelBrowser.Initialize(_dbId, this);
            }

            this.Cursor = Cursors.Default;
            MM.StopTransaction(mtr);
        }

        public void SaveFile(string filePath)
        {
            this.Cursor = Cursors.WaitCursor;
            if (_dbId == null)
            {
                MessageBox.Show("There is no database for the save", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            try
            {
                MemoryTransaction mtr = MM.StartTransaction();
                OdTvDatabase db = _dbId.openObject(OpenMode.kForWrite);
                OdTvResult rc = db.writeFile(filePath);
                MM.StopTransaction(mtr);
            }
            catch
            {
                MessageBox.Show("Saving of file\n'" + filePath + "'\n was failed", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            this.Cursor = Cursors.Default;
            FilePath = filePath;
        }

        public void CreateNewFile()
        {
            MemoryTransaction mtr = MM.StartTransaction();
            this.Cursor = Cursors.WaitCursor;
            OdTvFactoryId factId = TV_Globals.odTvGetFactory();
            factId.clearDatabases();
            DatabaseInfo = new TvDatabaseInfo();
            Stopwatch timer = Stopwatch.StartNew();
            timer.Start();
            _dbId = factId.createDatabase();
            try
            {
                OdTvResult rc = OdTvResult.tvCannotOpenFile;
                OdTvDatabase pDatabase = _dbId.openObject(OpenMode.kForWrite, ref rc);
                // Create model
                _tvActiveModelId = pDatabase.createModel("Tv_Model", OdTvModel.Type.kMain);
            }
            catch
            {
                MessageBox.Show("Cannot create new file!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            timer.Stop();
            DatabaseInfo.TvCreationTime = timer.ElapsedMilliseconds;

            _tvDevice = CreateNewDevice();
            Init();

            timer.Restart();
            _tvDevice.openObject().update();
            timer.Stop();
            DatabaseInfo.FirstUpdateTime = timer.ElapsedMilliseconds;

            VM.FileIsExist = true;
            FilePath = "";
            this.Cursor = Cursors.Default;
            VM.MainWindow.ModelBrowser.Initialize(_dbId, this);
            MM.StopTransaction(mtr);
        }

        private OdTvGsDeviceId CreateNewDevice()
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsDeviceId newDevId = null;

            try
            {
                IntPtr wndHndl = new IntPtr(Handle.ToInt32());
                OdTvDCRect rect = new OdTvDCRect(0, this.Width, this.Height, 0);
                newDevId = _dbId.openObject().createDevice("TV_Device", wndHndl, rect, OdTvGsDevice.Name.kOpenGLES2);
                // Open device
                OdTvGsDevice pDevice = newDevId.openObject(OpenMode.kForWrite);
                if (pDevice == null)
                    return null;

                //                 bool val;
                //                 pDevice.getOption(OdTvGsDevice.Options.kUseVisualStyles, out val);

                // Create view
                OdTvGsViewId newViewId = pDevice.createView("TV_View");
                TvActiveViewport = 0;

                // Add view to device
                pDevice.addView(newViewId);

                // Add current model to the view
                OdTvGsView viewPtr = newViewId.openObject(OpenMode.kForWrite);

                // Setup view to make it contr directional with the WCS normal
                viewPtr.setView(new OdGePoint3d(0, 0, 1), new OdGePoint3d(0, 0, 0), new OdGeVector3d(0, 1, 0), 1, 1);

                // Add main model to the view
                viewPtr.addModel(_tvActiveModelId);

                // Set current view as active
                viewPtr.setActive(true);

                // Set the render mode
                viewPtr.setMode(OdTvGsView.RenderMode.k2DOptimized);

                newDevId.openObject().onSize(rect);
            }
            catch (Exception e)
            {
                MessageBox.Show("Cannot create device:" + e);
                throw;
            }

            MM.StopTransaction(mtr);
            return newDevId;
        }

        private OdTvBaseImportParams GetImportParams(string filePath, ref bool isVsf)
        {
            OdTvBaseImportParams importParams = null;
            string ext = System.IO.Path.GetExtension(filePath);
            if (ext != null)
            {
                ext = ext.ToLower();
                if (ext == ".dwg")
                {
                    importParams = new OdTvDwgImportParams();
                    OdTvDwgImportParams dwgPmtrs = importParams as OdTvDwgImportParams;
                    dwgPmtrs.setDCRect(new OdTvDCRect(0, this.Width, this.Height, 0));
                    dwgPmtrs.setObjectNaming(true);
                    dwgPmtrs.setStoreSourceObjects(false);
                    dwgPmtrs.setFeedbackForChooseCallback(null);
                }
                else if (ext == ".obj")
                    importParams = new OdTvObjImportParams();
                else if (ext == ".stl")
                    importParams = new OdTvStlImportParams();
                else if (ext == ".vsf")
                {
                    isVsf = true;
                    importParams = new OdTvBaseImportParams();
                }
            }
            return importParams;
        }

        public void ExportToPdf(string fileName, bool is2D = true)
        {
            MemoryTransaction mtr = MM.StartTransaction();

            OdTvDatabase db = _dbId.openObject(OpenMode.kForWrite);
            if (db == null)
            {
                MessageBox.Show("There is no database for the save!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                MM.StopTransaction(mtr);
                return;
            }
            this.Cursor = Cursors.WaitCursor;

            //call method for write the file
            try
            {
                OdTvBaseExportParams exportParams = new OdTvBaseExportParams();
                exportParams.setFilePath(fileName);
                OdTvResult rc = db.exportTo(exportParams);
                if (rc != OdTvResult.tvOk)
                {
                    MessageBox.Show("Export of file " + fileName + " was failed!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    MM.StopTransaction(mtr);
                    this.Cursor = Cursors.Default;
                    return;
                }
            }
            catch
            {
                MessageBox.Show("Export of file " + fileName + " was failed!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                MM.StopTransaction(mtr);
                this.Cursor = Cursors.Default;
                return;
            }

            this.Cursor = Cursors.Default;
            MM.StopTransaction(mtr);
        }

        #endregion

        #region Markups commands

        private void CreateMarkupModel()
        {
            if (_tvMarkupModelId == null)
            {
                MemoryTransaction mtr = MM.StartTransaction();
                _tvMarkupModelId = _dbId.openObject(OpenMode.kForWrite).createModel(OdTvMarkupDragger.NameOfMarkupModel, OdTvModel.Type.kDirect, true);
                MM.StopTransaction(mtr);
            }
        }

        public void DrawRectMarkup()
        {
            CreateMarkupModel();
            OdTvDragger newDragger = new OdTvRectMarkupDragger(_tvDevice, _tvMarkupModelId);
            StartDragger(newDragger);
        }

        public void DrawCircMarkup()
        {
            CreateMarkupModel();
            OdTvDragger newDragger = new OdTvCircleMarkupDragger(_tvDevice, _tvMarkupModelId);
            StartDragger(newDragger);
        }

        public void DrawHandleMarkup()
        {
            CreateMarkupModel();
            OdTvDragger newDragger = new OdTvHandleMarkupDragger(_tvDevice, _tvMarkupModelId);
            StartDragger(newDragger);
        }

        public void DrawCloudMarkup()
        {
            CreateMarkupModel();
            OdTvDragger newDragger = new OdTvCloudMarkupDragger(_tvDevice, _tvMarkupModelId);
            StartDragger(newDragger);
        }

        public void DrawTextMarkup()
        {
            CreateMarkupModel();
            OdTvDragger newDragger = new OdTvTextMarkupDragger(_tvDevice, _tvMarkupModelId);
            StartDragger(newDragger);
        }

        public void SaveMarkup()
        {
            MemoryTransaction mtr = MM.StartTransaction();

            if (_tvMarkupModelId == null || _tvMarkupModelId.openObject().getEntitiesIterator().done())
            {
                MessageBox.Show("Markup model is empty!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (_tvMarkupModelId.openObject().getEntitiesIterator().done())
            {
                MessageBox.Show("No one marup for save!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            // find current active entity
            OdTvEntitiesIterator it = _tvMarkupModelId.openObject().getEntitiesIterator();
            OdTvEntityId activeEntityId = null;
            while (!it.done())
            {
                OdTvEntityId curEnId = it.getEntity();
                OdTvEntity curEn = curEnId.openObject();
                if (curEn.getName() == OdTvMarkupDragger.NameOfMarkupTempEntity || curEn.getVisibility().getType() !=
                    OdTvVisibilityDef.VisibilityType.kInvisible)
                {
                    activeEntityId = curEnId;
                    break;
                }
                it.step();
            }

            if (activeEntityId == null)
            {
                MessageBox.Show("No one marup for save!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            FinishDragger();

            SaveMarkupDialog dlg = new SaveMarkupDialog(_tvMarkupModelId, activeEntityId, _tvDevice.openObject().viewAt(TvActiveViewport));
            dlg.ShowDialog();

            MM.StopTransaction(mtr);
        }

        public void LoadMarkup()
        {
            MemoryTransaction mtr = MM.StartTransaction();

            if (_tvMarkupModelId == null || _tvMarkupModelId.openObject().getEntitiesIterator().done())
            {
                MessageBox.Show("Markup model is empty!\nPlease create markup.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            FinishDragger();

            LoadMarkupDialog dlg = new LoadMarkupDialog(_tvMarkupModelId, _tvDevice.openObject().viewAt(TvActiveViewport), this);
            if (dlg.ShowDialog() == true)
                Invalidate();

            MM.StopTransaction(mtr);
        }

        #endregion

        #region Appearance commands

        public void OnOffWCS(bool bEnable)
        {
            if (_tvDevice == null)
                return;

            if (bEnable)
            {
                if (WCS == null)
                    CreateWCS();
                else
                    WCS.UpdateWCS();
            }
            else if (!bEnable && WCS != null)
            {
                WCS.removeWCS();
            }
            MemoryTransaction mtr = MM.StartTransaction();
            _tvDevice.openObject().update();
            Invalidate();
            MM.StopTransaction(mtr);
        }

        private void CreateWCS()
        {
            if (WCS != null)
                WCS.removeWCS();

            MemoryTransaction mtr = MM.StartTransaction();
            WCS = new TvWpfViewWCS(_dbId, _tvDevice.openObject().viewAt(TvActiveViewport));
            OdTvGsView pWcsView = WCS.GetWcsViewId().openObject(OpenMode.kForWrite);
            OdTvGsView view = WCS.GetParentView().openObject();
            OdGePoint3d newPos = view.position();
            OdGeMatrix3d matr = new OdGeMatrix3d();
            matr.setTranslation(-view.target().asVector());
            pWcsView.setView(newPos.transformBy(matr), OdGePoint3d.kOrigin, view.upVector(), 1, 1);
            pWcsView.setMode(view.mode());
            pWcsView.zoom(4.2);
            OdGePoint2d lowerLeft = new OdGePoint2d();
            OdGePoint2d upperRight = new OdGePoint2d();
            view.getViewport(lowerLeft, upperRight);
            upperRight.x = lowerLeft.x + 0.15;
            upperRight.y = lowerLeft.y + 0.18;
            pWcsView.setViewport(lowerLeft, upperRight);
            WCS.UpdateWCS();

            MM.StopTransaction(mtr);
        }

        public void OnOffFPS(bool bEnable)
        {
            if (_tvDevice == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsDevice dev = _tvDevice.openObject(OpenMode.kForWrite);
            if (dev.getShowFPS() != bEnable)
            {
                dev.setShowFPS(bEnable);
                dev.update();
                Invalidate();
            }
            MM.StopTransaction(mtr);
        }

        public void OnOffAnimation(bool bEnable)
        {
            if (_tvDevice == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvExtendedView exView = GetActiveTvExtendedView();
            if (exView != null)
                exView.setAnimationEnabled(bEnable);
            MM.StopTransaction(mtr);
        }

        public void SetZoomStep(double dValue)
        {
            if (_tvDevice == null || dValue < 1)
                return;
            OdTvExtendedView exView = GetActiveTvExtendedView();
            if (exView != null)
                exView.setZoomScale(dValue);
        }

        #endregion

        #region Selection methods

        public void AddBoldItem(TvTreeItem node)
        {
            ClearSelectedNodes();
            node.SetBold(true);
            if (!SelectedNodes.Contains(node))
                SelectedNodes.Add(node);
        }

        public void ClearSelectedNodes()
        {
            for (int i = 0; i < SelectedNodes.Count; i++)
            {
                TvTreeItem node = SelectedNodes[i];
                node.SetBold(false);
            }
        }

        public void ClearSelectionSet()
        {
            if (SelectionSet == null || _tvDevice == null || _tvDevice.isNull())
                return;
            OdTvExtendedView exView = GetActiveTvExtendedView();
            if (exView == null)
                return;

            MemoryTransaction mtr = MM.StartTransaction();

            OdTvGsView view = exView.getViewId().openObject();
            if (view == null)
                return;

            OdTvSelectionSetIterator pIter = SelectionSet.getIterator();
            for (; pIter != null && !pIter.done(); pIter.step())
            {
                //get entity
                OdTvEntityId id = pIter.getEntity();
                //get sub item
                OdTvSubItemPath path = new OdTvSubItemPath();
                pIter.getPath(path);
                //perform highlight
                view.highlight(id, path, false);
            }

            SelectionSet.Dispose();
            SelectionSet = null;

            Invalidate();

            MM.StopTransaction(mtr);
        }

        public void AddEntityToSet(OdTvEntityId enId)
        {
            if (enId == null || enId.isNull())
                return;
            OdTvExtendedView exView = GetActiveTvExtendedView();
            if (exView == null)
                return;

            ClearSelectionSet();

            OdTvSelectionOptions opt = new OdTvSelectionOptions();
            opt.setLevel(OdTvSelectionOptions.Level.kEntity);
            opt.setMode(OdTvSelectionOptions.Mode.kPoint);
            SelectionSet = OdTvSelectionSet.createObject(opt);
            SelectionSet.appendEntity(enId);

            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsView view = exView.getViewId().openObject();
            if (view == null)
                return;

            OdTvSelectionSetIterator pIter = SelectionSet.getIterator();
            for (; pIter != null && !pIter.done(); pIter.step())
            {
                //get entity
                OdTvEntityId id = pIter.getEntity();
                //get sub item
                OdTvSubItemPath path = new OdTvSubItemPath();
                pIter.getPath(path);
                //perform highlight
                view.highlight(id, path, true);
            }

            MM.StopTransaction(mtr);

            Invalidate();
        }

        #endregion

        #region Cutting planes

        public void ShowSectioningOptions()
        {
            CuttingPlaneOptionsDialog dlg = new CuttingPlaneOptionsDialog(this);
            dlg.ShowDialog();
        }

        public void ApplySectioningOptions()
        {
            if (_tvDevice == null || _tvDevice.isNull())
                return;
            MemoryTransaction mtr = MM.StartTransaction();

            OdTvGsView pView = GetActiveTvExtendedView().getViewId().openObject(OpenMode.kForWrite);
            if (pView == null)
            {
                MM.StopTransaction(mtr);
                return;
            }

            uint iOldColor = 0;
            bool bOldFillingEnabled = pView.getCuttingPlaneFillEnabled(out iOldColor);

            bool bNewFillingEnabled = SectioningOptions.IsFilled;
            uint iNewColor = SectioningOptions.FillingColor;

            if (bNewFillingEnabled != bOldFillingEnabled || iNewColor != iOldColor)
                pView.setEnableCuttingPlaneFill(bNewFillingEnabled, iNewColor);

            uint iOldPatternColor = 0;
            OdTvGsView.CuttingPlaneFillStyle oldFillingPatternStyle = OdTvGsView.CuttingPlaneFillStyle.kCheckerboard;
            bool bOldFillingPatternEnabled = pView.getCuttingPlaneFillPatternEnabled(ref oldFillingPatternStyle, out iOldPatternColor);

            bool bNewFillingPatternEnabled = SectioningOptions.FillingPatternEnabled;
            OdTvGsView.CuttingPlaneFillStyle newFillingPatternStyle = SectioningOptions.FillingPaternStyle;
            uint iNewFillingPatternColor = SectioningOptions.FillingPatternColor;

            if (bNewFillingPatternEnabled != bOldFillingPatternEnabled
              || newFillingPatternStyle != oldFillingPatternStyle
              || iNewFillingPatternColor != iOldPatternColor)
                pView.setCuttingPlaneFillPatternEnabled(bNewFillingPatternEnabled, newFillingPatternStyle, iNewFillingPatternColor);

            OdTvGsDevice pDevice = _tvDevice.openObject();
            if(pDevice != null)
            {
                pDevice.invalidate();
                pDevice.update();
            }

            MM.StopTransaction(mtr);
        }

        public void OnAppearSectioningPanel(bool bAppear)
        {
            if(bAppear)
            {
                if(SectioningOptions.IsShown)
                {
                    if(!(_dragger is Draggers.OdTvCuttingPlaneDragger))
                    {
                        OdTvDragger pNewDragger = new Draggers.OdTvCuttingPlaneDragger(_tvDevice, _tvDraggersModelId, this);
                        if (pNewDragger != null)
                            StartDragger(pNewDragger, true);
                        Invalidate();
                    }
                }
            }
            else
            {
                if(_dragger is Draggers.OdTvCuttingPlaneDragger)
                {
                    Draggers.OdTvCuttingPlaneDragger cuttingPlaneDragger = (Draggers.OdTvCuttingPlaneDragger)_dragger;
                    if(cuttingPlaneDragger != null)
                    {
                        cuttingPlaneDragger.IsCanFinish = true;
                        FinishDragger();
                        Invalidate();
                    }
                }
            }
        }

        public bool ShowCuttingPlanes()
        {
            MemoryTransaction mtr = MM.StartTransaction();
            SectioningOptions.IsShown = !SectioningOptions.IsShown;

            bool bRet = false;

            OdTvGsView pActiveView = GetActiveTvExtendedView().getViewId().openObject(OpenMode.kForWrite);
            OdTvGsDevice pDevice = _tvDevice.openObject(OpenMode.kForWrite);
            if (pActiveView == null || pDevice == null)
            {
                MM.StopTransaction(mtr);
                return bRet;
            }

            if(SectioningOptions.IsShown)
            {
                //here we should add the view to the device and to the active view
                pDevice.addView(_cuttingPlanesViewId);
                //add view as sibling to an active
                pActiveView.addSibling(_cuttingPlanesViewId);
                //create sectioning planes geometry
                for (int i = 0; i < pActiveView.numCuttingPlanes(); i++)
                {
                    DrawCuttingPlane(i, pActiveView);
                }
                // create and start new dragger
                OdTvDragger pNewDragger = new Draggers.OdTvCuttingPlaneDragger(_tvDevice, _tvDraggersModelId, this);
                if (pNewDragger != null)
                    StartDragger(pNewDragger, true);

                pDevice.invalidate();

                bRet = true;
            }
            else
            {
                if(_dragger is Draggers.OdTvCuttingPlaneDragger)
                {
                    // finish the dragger
                    Draggers.OdTvCuttingPlaneDragger cuttingPlaneDragger = (Draggers.OdTvCuttingPlaneDragger)_dragger;
                    cuttingPlaneDragger.IsCanFinish = true;
                    FinishDragger();
                }

                // remove geometry for the sectioning planes
                if (!_cuttingPlanesModelId.isNull())
                {
                    OdTvModel pMoveModel = _cuttingPlanesModelId.openObject(OpenMode.kForWrite);
                    if (pMoveModel != null)
                        pMoveModel.clearEntities();
                }

                // remove view as sibling from an active
                pActiveView.removeSibling(_cuttingPlanesViewId);
                // remove view from device
                pDevice.removeView(_cuttingPlanesViewId);
                bRet = true;
            }

            Invalidate();
            MM.StopTransaction(mtr);
            return bRet;
        }

        protected void DrawCuttingPlane(int index, OdTvGsView pView, bool bNeedNotifyDragger = false)
        {
            if (pView == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();

            OdGePlane cuttingPlane = new OdGePlane();
            OdTvResult rc = pView.getCuttingPlane((uint)index, cuttingPlane);
            if(rc != OdTvResult.tvOk)
            {
                MM.StopTransaction(mtr);
                return;
            }

            OdTvModel pCuttingPlaneModel = _cuttingPlanesModelId.openObject(OpenMode.kForWrite);
            // create cutting plane entity
            OdTvEntityId cuttingPlanesEntityId = pCuttingPlaneModel.appendEntity("$_CUTTINGPLANE_ENTITY" + index);
            //set a few parameters to the cutting plane
            OdTvEntity pCuttingPlanesEntity = cuttingPlanesEntityId.openObject(OpenMode.kForWrite);
            pCuttingPlanesEntity.setColor(new OdTvColorDef(175, 175, 175));
            pCuttingPlanesEntity.setLineWeight(new OdTvLineWeightDef(Draggers.OdTvCuttingPlaneDragger.OD_TV_CUTTINGPLANE_EDGE_DEFAULT_LINEWEIGHT));
            pCuttingPlanesEntity.setTransparency(new OdTvTransparencyDef(0.8));
            pCuttingPlanesEntity.addViewDependency(_cuttingPlanesViewId);

            IntPtr ptr = Marshal.AllocHGlobal(Marshal.SizeOf(index));
            Marshal.WriteInt32(ptr, 0, index);
            OdTvByteUserData data = new OdTvByteUserData(ptr, sizeof(int), OdTvByteUserData.Ownership.kCopyOwn, false);

            pCuttingPlanesEntity.appendUserData(data, AppTvId);

            // Calculate points for cutting plane shell
            OdGePoint3d origin = new OdGePoint3d();
            OdGeVector3d uAxis = new OdGeVector3d();
            OdGeVector3d vAxis = new OdGeVector3d();
            cuttingPlane.get(origin, uAxis, vAxis);

            // Get max distance between extents
            double cuttingPlaneSize = getMainModelExtentsDistance() / 2d;

            OdTvPointArray points = new OdTvPointArray();

            OdGeMatrix3d transformMatrix = new OdGeMatrix3d();
            // 0
            OdGeVector3d moveVector0 = -vAxis - uAxis;
            moveVector0 = moveVector0 * cuttingPlaneSize * Draggers.OdTvCuttingPlaneDragger.OD_TV_CUTTINGPLANE_SIZE_COEFF;
            transformMatrix.setToIdentity();
            transformMatrix.setToTranslation(moveVector0);
            OdGePoint3d point0 = new OdGePoint3d(origin);
            point0 = point0.transformBy(transformMatrix);
            points.Add(point0);

            // 1
            OdGeVector3d moveVector1 = vAxis - uAxis;
            moveVector1 = moveVector1 * cuttingPlaneSize * Draggers.OdTvCuttingPlaneDragger.OD_TV_CUTTINGPLANE_SIZE_COEFF;
            transformMatrix.setToIdentity();
            transformMatrix.setToTranslation(moveVector1);
            OdGePoint3d point1 = new OdGePoint3d(origin);
            point1 = point1.transformBy(transformMatrix);
            points.Add(point1);

            // 2
            OdGeVector3d moveVector2 = vAxis + uAxis;
            moveVector2 = moveVector2 * cuttingPlaneSize * Draggers.OdTvCuttingPlaneDragger.OD_TV_CUTTINGPLANE_SIZE_COEFF;
            transformMatrix.setToIdentity();
            transformMatrix.setToTranslation(moveVector2);
            OdGePoint3d point2 = new OdGePoint3d(origin);
            point2 = point2.transformBy(transformMatrix);
            points.Add(point2);

            // 3
            OdGeVector3d moveVector3 = uAxis - vAxis;
            moveVector3 = moveVector3 * cuttingPlaneSize * Draggers.OdTvCuttingPlaneDragger.OD_TV_CUTTINGPLANE_SIZE_COEFF;
            transformMatrix.setToIdentity();
            transformMatrix.setToTranslation(moveVector3);
            OdGePoint3d point3 = new OdGePoint3d(origin);
            point3 = point3.transformBy(transformMatrix);
            points.Add(point3);

            OdInt32Array faces = new OdInt32Array();
            faces.Add(4);
            faces.Add(0);
            faces.Add(1);
            faces.Add(2);
            faces.Add(3);

            // append shell to cutting plane entity
            OdTvGeometryDataId cuttingPlaneShellId = pCuttingPlanesEntity.appendShell(points, faces);
            cuttingPlaneShellId.openAsShell().setDisableLighting(true);

            // append boundary polyline to cutting plane entity
            points.Add(point0);
            pCuttingPlanesEntity.appendPolyline(points);

            //notify dragger that cutting plane was added
            if(_dragger is Draggers.OdTvCuttingPlaneDragger)
            {
                Draggers.OdTvCuttingPlaneDragger cuttingPlaneDragger = (Draggers.OdTvCuttingPlaneDragger)_dragger;
                if (cuttingPlaneDragger != null)
                    cuttingPlaneDragger.OnCuttingPlaneAdded(cuttingPlanesEntityId);
            }

            MM.StopTransaction(mtr);
        }

        private double getMainModelExtentsDistance()
        {
            double maxDistance = 0d;
            MemoryTransaction mtr = MM.StartTransaction();

            OdTvModel pModel = _tvActiveModelId.openObject();

            // Get extents
            OdGeExtents3d extents = new OdGeExtents3d();
            OdTvResult res = pModel.getExtents(extents);
            if (res != OdTvResult.tvOk)
                return maxDistance;
            // Get max distance between extents
            OdGePoint3d center = extents.center();
            OdGePoint3d minPoint = extents.minPoint();
            OdGePoint3d maxPoint = extents.maxPoint();

            if ((maxPoint.x - minPoint.x < maxPoint.y - minPoint.y) && (maxPoint.x - minPoint.x < maxPoint.z - minPoint.z))
                maxDistance = maxPoint.x - minPoint.x;
            else if ((maxPoint.y - minPoint.y < maxPoint.x - minPoint.x) && (maxPoint.y - minPoint.y < maxPoint.z - minPoint.z))
                maxDistance = maxPoint.y - minPoint.y;
            else if ((maxPoint.z - minPoint.z < maxPoint.x - minPoint.x) && (maxPoint.z - minPoint.z < maxPoint.y - minPoint.y))
                maxDistance = maxPoint.z - minPoint.z;
            else
                maxDistance = maxPoint.x - minPoint.x;

            MM.StopTransaction(mtr);
            return maxDistance;
        }

        public bool AddCuttingPlane(OdGeVector3d axis, OdTvResult rc)
        {
            MemoryTransaction mtr = MM.StartTransaction();

            OdTvGsView pActiveView = GetActiveTvExtendedView().getViewId().openObject(OpenMode.kForWrite);
            if(pActiveView == null)
            {
                rc = OdTvResult.tvThereIsNoActiveView;
                MM.StopTransaction(mtr);
                return false;
            }

            uint nPlanes = pActiveView.numCuttingPlanes();
            if(nPlanes >= OD_TV_CUTTING_PLANE_MAX_NUM)
            {
                MM.StopTransaction(mtr);
                return false;
            }

            if(axis.isZeroLength())
            {
                rc = OdTvResult.tvCuttingPlaneZeroNormal;
                MM.StopTransaction(mtr);
                return false;
            }

            OdGeBoundBlock3d extents = new OdGeBoundBlock3d();
            if(!GetActiveTvExtendedView().getCachedExtents(extents))
            {
                if(pActiveView.viewExtents(extents))
                {
                    if (!pActiveView.isPerspective())
                        extents.setToBox(true);

                    OdGeMatrix3d xWorldToEye = pActiveView.viewingMatrix();
                    OdGeMatrix3d xEyeToWorld = xWorldToEye.invert();
                    // transform extents to WCS
                    extents.transformBy(xEyeToWorld);
                }
            }

            OdGePoint3d center = extents.center();
            OdGePlane plane = new OdGePlane(center, axis);

            // add cutting plae
            pActiveView.addCuttingPlane(plane);
            //update filling parameters first time
            if(nPlanes == 0)
            {
                pActiveView.setEnableCuttingPlaneFill(SectioningOptions.IsFilled, SectioningOptions.FillingColor);
                pActiveView.setCuttingPlaneFillPatternEnabled(SectioningOptions.FillingPatternEnabled,
                  SectioningOptions.FillingPaternStyle, SectioningOptions.FillingPatternColor);
            }

            try
            {
                MemoryTransaction mtrDev = MM.StartTransaction();
                OdTvGsDevice pDevice = _tvDevice.openObject(OpenMode.kForWrite);
                if (SectioningOptions.IsShown)
                {
                    // if it is the first added object
                    if (nPlanes == 0)
                    {
                        //here we should add the view to the device and to the active view
                        pDevice.addView(_cuttingPlanesViewId);
                        //add view as sibling to an active
                        pActiveView.addSibling(_cuttingPlanesViewId);
                    }
                    //create geometry for the new sectioning plane
                    DrawCuttingPlane((int)pActiveView.numCuttingPlanes() - 1, pActiveView, true);
                }

                pDevice.invalidate();
                Invalidate();
                MM.StopTransaction(mtrDev);
            }
            catch (System.Exception)
            {
            	
            }

            MM.StopTransaction(mtr);
            return true;
        }

        public void RemoveCuttingPlanes()
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsView pActiveView = GetActiveTvExtendedView().getViewId().openObject(OpenMode.kForWrite);
            if (pActiveView == null)
            {
                MM.StopTransaction(mtr);
                return;
            }

            try
            {
                OdTvGsDevice pDevice = _tvDevice.openObject(OpenMode.kForWrite);
                if (SectioningOptions.IsShown)
                {
                    //notify dragger
                    if(_dragger is Draggers.OdTvCuttingPlaneDragger)
                    {
                        Draggers.OdTvCuttingPlaneDragger cuttingPlaneDragger = (Draggers.OdTvCuttingPlaneDragger)_dragger;
                        if (cuttingPlaneDragger != null)
                            cuttingPlaneDragger.OnRemoveCuttingPlanes();
                    }

                    // remove geometry for the sectioning planes
                    if (!_cuttingPlanesModelId.isNull())
                    {
                        OdTvModel pMoveModel = _cuttingPlanesModelId.openObject(OpenMode.kForWrite);
                        if (pMoveModel != null)
                            pMoveModel.clearEntities();
                    }

                    // remove view as sibling from an active
                    pActiveView.removeSibling(_cuttingPlanesViewId);

                    // remove view from device
                    pDevice.removeView(_cuttingPlanesViewId);
                }
                //remove cutting planes
                pActiveView.removeCuttingPlanes();
                pDevice.invalidate();
                Invalidate();

            }
            catch (System.Exception)
            {
            }

            MM.StopTransaction(mtr);
        }

        #endregion

    }
}
