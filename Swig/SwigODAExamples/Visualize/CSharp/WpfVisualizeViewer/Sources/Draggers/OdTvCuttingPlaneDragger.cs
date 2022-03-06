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
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace WpfVisualizeViewer.Draggers
{
    class OdTvCuttingPlaneDragger : OdTvDragger
    {
        protected new MemoryManager MM = MemoryManager.GetMemoryManager();

        public const double OD_TV_CUTTINGPLANE_SIZE_COEFF = 1.3;
        public const byte OD_TV_CUTTINGPLANE_EDGE_DEFAULT_LINEWEIGHT = 3;
        public const byte OD_TV_CUTTINGPLANE_EDGE_SELECTED_LINEWEIGHT = 5;

        public enum CuttingState
        {
            WaitingForCutPlSelect = 0,
            WaitingForAxisControlSelect = 1,
            CuttingPlaneRotation = 2
        };

        // State of this dragger
        protected CuttingState _state = CuttingState.WaitingForCutPlSelect;
        //parents rendering area
        protected OdTvWpfView _wpfView;
        // Options used for the selection of cutting planes
        protected OdTvSelectionOptions _selectionOptions = new OdTvSelectionOptions();
        //axis control
        protected OdTvRotationAxisControl _axisControl = new OdTvRotationAxisControl();
        //map for storing the cutting planes entities
        protected Dictionary<string, int> _cuttingPlanesDict = new Dictionary<string, int>();
        // view for display cutting planes
        protected OdTvGsViewId _cuttingPlanesViewId = new OdTvGsViewId();
        // model for cutting planes
        protected OdTvModelId _cuttingPlanesModelId = new OdTvModelId();
        // selected cutting plane
        protected OdTvEntityId _selectedCuttingPlaneEntityId = new OdTvEntityId();
        // highlighted cutting plane
        protected OdTvEntityId _highlightedCuttingPlaneId = new OdTvEntityId();
        // indicate that dragger can be finished
        public bool IsCanFinish { get; set; }

        public OdTvCuttingPlaneDragger(OdTvGsDeviceId deviceId, OdTvModelId tvDraggersModelId, OdTvWpfView wpfView)
            : base(deviceId, tvDraggersModelId)
        {
            _wpfView = wpfView;
            IsCanFinish = false;
            _selectionOptions.setMode(OdTvSelectionOptions.Mode.kPoint);

            _cuttingPlanesViewId = wpfView.CuttingPlanesViewId;
            _cuttingPlanesModelId = wpfView.CuttingPlaneModelId;

            //init axis control
            OdTvGsViewId pActiveViewId = _wpfView.GetActiveTvExtendedView().getViewId();
            _axisControl.Init(pActiveViewId);

            NeedFreeDrag = true;
        }

        public void OnCuttingPlaneAdded(OdTvEntityId entId)
        {
            if (entId.isNull())
                return;
            MemoryTransaction mtr = MM.StartTransaction();

            OdTvEntity pEntity = entId.openObject();
            if(pEntity == null)
            {
                MM.StopTransaction(mtr);
                return;
            }

            OdTvGsViewIdsArray pViews = pEntity.getViewDependencies();
            if(pViews.Contains(_cuttingPlanesViewId))
            {
                OdTvUserData data = pEntity.getUserData(OdTvWpfView.AppTvId);
                if (data != null)
                {
                    OdTvByteUserData res = new OdTvByteUserData(OdTvUserData.getCPtr(data).Handle, false);
                    IntPtr ptr = res.getData();
                    pEntity.getDatabaseHandle();
                    if(!_cuttingPlanesDict.ContainsKey(pEntity.getName()))
                        _cuttingPlanesDict.Add(pEntity.getName(), Marshal.ReadInt32(ptr));
                }
            }

            MM.StopTransaction(mtr);
        }

        public void OnRemoveCuttingPlanes()
        {
            // clear entities map
            _cuttingPlanesDict.Clear();
            // for reset some internal fields
            ProcessEscape();
        }

        public override DraggerResult Start(OdTvDragger prevDragger, int activeView, Cursor cursor, TvWpfViewWCS wcs)
        {
            _state = CuttingState.WaitingForCutPlSelect;

            MemoryTransaction mtr = MM.StartTransaction();

            //fill map with entities used for the visualization of the cutting planes
            if (!_cuttingPlanesModelId.isNull())
            {
                OdTvModel pModel = _cuttingPlanesModelId.openObject(OpenMode.kForWrite);
                if (pModel != null)
                {
                    OdTvEntitiesIterator pIt = pModel.getEntitiesIterator();
                    while (!pIt.done())
                    {
                        OdTvEntityId entId = pIt.getEntity();
                        OnCuttingPlaneAdded(entId);
                        pIt.step();
                    }
                }
            }

            MM.StopTransaction(mtr);

            return DraggerResult.NeedUpdateView | base.Start(prevDragger, activeView, cursor, wcs);
        }

        public override DraggerResult NextPoint(int x, int y)
        {
            DraggerResult res = DraggerResult.NothingToDo;

            MemoryTransaction mtr = MM.StartTransaction();

            //first of all we need the active view to perform selection
            OdTvGsView pView = _cuttingPlanesViewId.openObject(OpenMode.kForWrite);
            if (pView == null)
            {
                MM.StopTransaction(mtr);
                return DraggerResult.NothingToDo;
            }

            if (_state == CuttingState.WaitingForCutPlSelect)
            {
                OdTvDCPoint[] pt = new OdTvDCPoint[1];
                pt[0] = new OdTvDCPoint(x, y);
                // perform selection
                OdTvSelectionSet pSSet = pView.select(pt, _selectionOptions, _cuttingPlanesModelId);
                // check selection results
                if (pSSet != null && pSSet.numItems() != 0)
                {
                    // merge new selection set with current
                    Merge(pSSet);
                    //call window update
                    res = DraggerResult.NeedUpdateView;
                }
            }
            else if (_state == CuttingState.WaitingForAxisControlSelect)
            {
                if (_axisControl != null && _axisControl.IsAttached && _axisControl.HasSelectedControl())
                {
                    _axisControl.Start(x, y);
                    _state = CuttingState.CuttingPlaneRotation;
                    res = DraggerResult.NeedUpdateView;
                }
            }
            else
                res = DraggerResult.NeedUpdateView;

            MM.StopTransaction(mtr);

            return res;
        }

        public override DraggerResult Drag(int x, int y)
        {
            MemoryTransaction mtr = MM.StartTransaction();

            if (_state == CuttingState.WaitingForCutPlSelect)
            {
                //first of all we need the active view to perform selection
                OdTvGsView pView = _cuttingPlanesViewId.openObject(OpenMode.kForWrite);
                if (pView == null)
                {
                    MM.StopTransaction(mtr);
                    return DraggerResult.NothingToDo;
                }
                // highlight thecutting plane
                OdTvSelectionOptions selOpt = new OdTvSelectionOptions();
                selOpt.setMode(OdTvSelectionOptions.Mode.kPoint);
                OdTvDCPoint[] pnt = new OdTvDCPoint[1];
                pnt[0] = new OdTvDCPoint(x, y);
                // check about something selected
                OdTvSelectionSet pSSet = pView.select(pnt, _selectionOptions, _cuttingPlanesModelId);
                // highlight
                if(pSSet != null && pSSet.numItems() == 1)
                {
                    OdTvEntityId selEntity = pSSet.getIterator().getEntity();
                    if(!selEntity.IsEqual(_highlightedCuttingPlaneId))
                    {
                        Highlight(_highlightedCuttingPlaneId, false);
                        Highlight(selEntity, true);
                        _highlightedCuttingPlaneId = selEntity;
                        MM.StopTransaction(mtr);
                        return DraggerResult.NeedUpdateView;
                    }
                }
                else if(!_highlightedCuttingPlaneId.isNull())
                {
                    Highlight(_highlightedCuttingPlaneId, false);
                    _highlightedCuttingPlaneId.setNull();
                    MM.StopTransaction(mtr);
                    return DraggerResult.NeedUpdateView;
                }
            }
            else if(_state == CuttingState.WaitingForAxisControlSelect)
            {
                if(_axisControl.IsAttached)
                {
                    if (_axisControl.Hover(x, y))
                    {
                        MM.StopTransaction(mtr);
                        return DraggerResult.NeedUpdateView;
                    }
                    MM.StopTransaction(mtr);
                    return DraggerResult.NothingToDo;
                }
            }
            else if(_state == CuttingState.CuttingPlaneRotation)
            {
                if (_selectedCuttingPlaneEntityId == null || _selectedCuttingPlaneEntityId.isNull())
                {
                    MM.StopTransaction(mtr);
                    return DraggerResult.NothingToDo;
                }
                OdTvEntity pEntity = _selectedCuttingPlaneEntityId.openObject(OpenMode.kForWrite);
                int index = -1;
                if (!_cuttingPlanesDict.TryGetValue(pEntity.getName(), out index))
                    index = -1;
                OdTvGsView pView = TvView.openObject(OpenMode.kForWrite);
                if (pView == null || index < 0)
                {
                    MM.StopTransaction(mtr);
                    return DraggerResult.NothingToDo;
                }
                OdGePlane cuttingPlane = new OdGePlane();
                uint cnt = pView.numCuttingPlanes();
                OdTvResult res = pView.getCuttingPlane((uint)index, cuttingPlane);
                if (res != OdTvResult.tvOk)
                {
                    MM.StopTransaction(mtr);
                    return DraggerResult.NothingToDo;
                }

                OdGePoint3d origin = new OdGePoint3d();
                OdGeVector3d u = new OdGeVector3d();
                OdGeVector3d v = new OdGeVector3d();
                cuttingPlane.get(origin, u, v);

                OdTvResult rc;
                OdGeMatrix3d transform = _axisControl.GetTransform(x, y, out rc);
                if (rc != OdTvResult.tvOk)
                {
                    MM.StopTransaction(mtr);
                    return DraggerResult.NothingToDo;
                }

                origin = origin.transformBy(transform);
                u = u.transformBy(transform);
                v = v.transformBy(transform);

                // Update cutting plane
                cuttingPlane.set(origin, u, v);
                pView.updateCuttingPlane((uint)index, cuttingPlane);

                // update cutting plane geometry
                pEntity.appendModelingMatrix(transform);

                OdTvGsDevice pDevice = pView.device().openObject();
                if (pDevice != null)
                {
                    pDevice.invalidate();
                }

                MM.StopTransaction(mtr);
                return DraggerResult.NeedUpdateView;
            }

            MM.StopTransaction(mtr);
            return DraggerResult.NothingToDo;
        }

        public override DraggerResult ProcessEscape()
        {
            _state = CuttingState.WaitingForCutPlSelect;

            MemoryTransaction mtr = MM.StartTransaction();

            if(_axisControl != null)
            {
                _axisControl.Unhighlight();
                _axisControl.Remove();
                _axisControl = null;
            }

            // reset cutting plane color
            if (!_selectedCuttingPlaneEntityId.isNull())
            {
                OdTvEntity pSelectedCuttingPlaneEntity = _selectedCuttingPlaneEntityId.openObject(OpenMode.kForWrite);
                pSelectedCuttingPlaneEntity.setColor(new OdTvColorDef(175, 175, 175));
                pSelectedCuttingPlaneEntity.setLineWeight(new OdTvLineWeightDef(OD_TV_CUTTINGPLANE_EDGE_DEFAULT_LINEWEIGHT));
            }

            // unselect cutting plane
            _selectedCuttingPlaneEntityId.setNull();

            MM.StopTransaction(mtr);

            return DraggerResult.NeedUpdateView;
        }

        public override DraggerResult NextPointUp(int x, int y)
        {
            DraggerResult res = DraggerResult.NothingToDo;

            if(_state == CuttingState.CuttingPlaneRotation)
            {
                if(_axisControl.IsAttached)
                {
                    _axisControl.ApplyTransformToAxis();
                    _axisControl.Finish();
                    if (_axisControl.Hover(x, y))
                        res = DraggerResult.NeedUpdateView;
                }

                _state = CuttingState.WaitingForAxisControlSelect;
            }

            return res;
        }

        public override bool CanFinish()
        {
            if(IsCanFinish)
            {
                IsCanFinish = false;
                return true;
            }

            return IsCanFinish;
        }

        public override OdTvDragger Finish(out DraggerResult rc)
        {
            ProcessEscape();

            if(_highlightedCuttingPlaneId.isNull())
            {
                Highlight(_highlightedCuttingPlaneId, false);
                _highlightedCuttingPlaneId.setNull();
            }

            return base.Finish(out rc);
        }

        public override void NotifyAboutViewChange(DraggerViewChangeType type)
        {
            if (!_axisControl.IsAttached)
                return;
            if ( (type & DraggerViewChangeType.ViewChangeFull) > 0 || (type & DraggerViewChangeType.ViewChangeZoom) > 0)
                _axisControl.Scale();
        }

        protected void Merge(OdTvSelectionSet pSSet)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvSelectionSetIterator pSelectIter = pSSet.getIterator();
            if (!pSelectIter.done())
            {
                if (_state == CuttingState.WaitingForCutPlSelect) // Create axis control for selected cutting plane
                {
                    _selectedCuttingPlaneEntityId = pSelectIter.getEntity();
                    if (!_selectedCuttingPlaneEntityId.isNull())
                    {
                        OdTvEntity pSelectedCuttingPlaneEntity = _selectedCuttingPlaneEntityId.openObject(OpenMode.kForWrite);
                        int cuttingPlaneIndex = -1;
                        if (!_cuttingPlanesDict.TryGetValue(pSelectedCuttingPlaneEntity.getName(), out cuttingPlaneIndex))
                            cuttingPlaneIndex = -1;

                        if (cuttingPlaneIndex < 0)
                        {
                            MM.StopTransaction(mtr);
                            return;
                        }

                        //reset highlight
                        if (!_highlightedCuttingPlaneId.isNull())
                        {
                            Highlight(_highlightedCuttingPlaneId, false);
                            _highlightedCuttingPlaneId.setNull();
                        }

                        // Change color
                        pSelectedCuttingPlaneEntity.setColor(new OdTvColorDef(255, 0, 0));
                        pSelectedCuttingPlaneEntity.setLineWeight(new OdTvLineWeightDef(OD_TV_CUTTINGPLANE_EDGE_SELECTED_LINEWEIGHT));

                        OdGePlane cuttingPlane = new OdGePlane();
                        OdTvGsView pView = null;
                        if (!TvView.isNull())
                            pView = TvView.openObject();
                        if (pView != null && pView.getCuttingPlane((uint)cuttingPlaneIndex, cuttingPlane) != OdTvResult.tvOk)
                        {
                            MM.StopTransaction(mtr);
                            return;
                        }

                        OdGePoint3d origin = new OdGePoint3d();
                        OdGeVector3d u = new OdGeVector3d();
                        OdGeVector3d v = new OdGeVector3d();
                        cuttingPlane.get(origin, u, v);

                        // Draw wcs
                        if (_axisControl == null)
                        {
                            _axisControl = new OdTvRotationAxisControl();
                            _axisControl.Init(TvView);
                        }
                        _axisControl.Attach(origin, u, v);
                        NotifyAboutViewChange(DraggerViewChangeType.ViewChangeZoom);

                        // Now wait for wcs axis selection or cutting plane selection for moving
                        _state = CuttingState.WaitingForAxisControlSelect;
                        NeedFreeDrag = true;
                    }
                }
            }
            MM.StopTransaction(mtr);
        }

        protected void Highlight(OdTvEntityId planeId, bool bHighlight)
        {
            if (planeId.isNull())
                return;
            MemoryTransaction mtr = MM.StartTransaction();

            OdTvEntity pPlane = planeId.openObject(OpenMode.kForWrite);

            // perform highlight
            if(bHighlight)
            {
                pPlane.setColor(new OdTvColorDef(255, 128, 0));
                pPlane.setLineWeight(new OdTvLineWeightDef(OD_TV_CUTTINGPLANE_EDGE_SELECTED_LINEWEIGHT));
            }
            else
            {
                pPlane.setColor(new OdTvColorDef(175, 175, 175));
                pPlane.setLineWeight(new OdTvLineWeightDef(OD_TV_CUTTINGPLANE_EDGE_DEFAULT_LINEWEIGHT));
            }

            MM.StopTransaction(mtr);
        }
    }
}
