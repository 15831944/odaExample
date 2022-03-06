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

using System.Windows.Forms;
using Teigha.Core;
using Teigha.Visualize;
using WpfVisualizeViewer.Misc;

namespace WpfVisualizeViewer
{
    public class OdTvRectMarkupDragger : OdTvMarkupDragger
    {
        // first click point
        private OdGePoint3d _firstPoint = null;
        // last drag point
        private OdGePoint3d _lastDragPoint = null;
        // flag for success exit from dragger
        private bool _isSuccess = false;
        // local state of the dragger
        private bool _isPressed = false;

        // temporary geometry
        private OdTvEntityId _entityId = null;
        private OdTvGeometryDataId _rectFoldId = null;
        private OdTvGeometryDataId _rectEntityId = null;
        private OdTvGeometryDataId _rectId = null;

        // point for polygon
        OdGePoint3d[] _points = null;

        public OdTvRectMarkupDragger(OdTvGsDeviceId deviceId, OdTvModelId markupModelId)
            : base(deviceId, markupModelId)
        {
            NeedFreeDrag = true;

            _points = new OdGePoint3d[4];

            MemoryTransaction mtr = MM.StartTransaction();
            // create main entity
            OdTvModel pModel = markupModelId.openObject(OpenMode.kForWrite);
            if (pModel == null)
                return;

            _entityId = FindMarkupEntity(NameOfMarkupTempEntity, true);
            if (_entityId == null)
            {
                _entityId = pModel.appendEntity(NameOfMarkupTempEntity);
                _entityId.openObject(OpenMode.kForWrite).setColor(MarkupColor);
            }

            // crate rectangles subEntity if not exist
            _rectFoldId = FindSubEntity(_entityId.openObject().getGeometryDataIterator(), NameOfMarkupRectFold) ??
                          _entityId.openObject(OpenMode.kForWrite).appendSubEntity(NameOfMarkupRectFold);
            

            MM.StopTransaction(mtr);
        }

        public override DraggerResult Start(OdTvDragger prevDragger, int activeView, Cursor cursor, TvWpfViewWCS wcs)
        {
            TvActiveViewport = activeView;
            DraggerResult res = DraggerResult.NothingToDo;

            res = res | base.Start(prevDragger, activeView, cursor, wcs);

            // add dragger model to the view
            AddDraggersModelToView();

            return res;
        }

        public override DraggerResult NextPoint(int x, int y)
        {
            if (!CheckDragger())
                return DraggerResult.NothingToDo;

            if (!_isPressed)
            {
                _isPressed = true;
                // remember first click
                _firstPoint = ToEyeToWorld(x, y);
            }
            else
            {
                _isPressed = false;
                MemoryTransaction mtr = MM.StartTransaction();
                if(_rectEntityId != null)
                    _rectEntityId.openAsSubEntity().setLineWeight(LineWeight);
                MM.StopTransaction(mtr);
                return DraggerResult.NeedUpdateView;
            }
            return DraggerResult.NothingToDo;
        }

        public override DraggerResult NextPointUp(int x, int y)
        {
            if (!_isPressed)
            {
                _isSuccess = true;
                return DraggerResult.NeedUFinishDragger | Reset();
            }

            return DraggerResult.NothingToDo;
        }

        public override DraggerResult Drag(int x, int y)
        {
            if (!CheckDragger())
                return DraggerResult.NothingToDo;

            if (!_isPressed)
                return DraggerResult.NothingToDo;

            // get current drag point
            _lastDragPoint = ToEyeToWorld(x, y);

            // create temporary geometry if need
            UpdateFrame(_rectEntityId == null);

            return DraggerResult.NeedUpdateView;
        }

        public override bool UpdateCursor()
        {
            CurrentCursor = State == DraggerState.Finishing ? LasAppActiveCursor : Cursors.Cross;
            return true;
        }

        public override OdTvDragger Finish(out DraggerResult rc)
        {
            if (!_isSuccess && _rectEntityId != null)
            {
                MemoryTransaction mtr = MM.StartTransaction();
                _rectFoldId.openAsSubEntity(OpenMode.kForWrite).removeGeometryData(_rectEntityId);
                TvDeviceId.openObject().update();
                MM.StopTransaction(mtr);
            }

            return base.Finish(out rc);
        }

        private void UpdateFrame(bool isNeedCreate)
        {
            if (TvView == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();

            OdTvGsView view = TvView.openObject();;

            _points[0] = _firstPoint;
            _points[2] = _lastDragPoint;

            OdGeMatrix3d x = view.viewingMatrix();
            OdGePoint3d p0 = x * _points[0];
            OdGePoint3d p2 = x * _points[2];

            _points[1] = new OdGePoint3d(p0.x, p2.y, p2.z);
            _points[3] = new OdGePoint3d(p2.x, p0.y, p2.z);

            x = view.eyeToWorldMatrix();

            _points[1].transformBy(x);
            _points[3].transformBy(x);

            // update or create entity
            if (isNeedCreate)
            {
                _rectEntityId = _rectFoldId.openAsSubEntity(OpenMode.kForWrite).appendSubEntity("RectEntity");
                OdTvEntity rectEnt = _rectEntityId.openAsSubEntity(OpenMode.kForWrite);
                _rectId = rectEnt.appendPolygon(_points);
            }
            else
            {
                OdTvGeometryData pFrame = _rectId.openObject();
                if (pFrame == null || pFrame.getType() != OdTvGeometryDataType.kPolygon)
                    return;
                OdTvPolygonData polygon = pFrame.getAsPolygon();
                polygon.setPoints(_points);
            }
            MM.StopTransaction(mtr);
        }
    }
}
