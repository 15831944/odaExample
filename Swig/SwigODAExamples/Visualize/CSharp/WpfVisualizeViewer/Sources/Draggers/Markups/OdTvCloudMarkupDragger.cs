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
using System.Collections.Generic;
using System.Windows.Forms;
using Teigha.Core;
using Teigha.Visualize;
using WpfVisualizeViewer.Misc;

namespace WpfVisualizeViewer
{
    public class OdTvCloudMarkupDragger : OdTvMarkupDragger
    {
        private bool _isSuccess = false;
        // first and last click
        private OdGePoint3d _firstPoint;
        private OdGePoint3d _lastPoint;
        // local state of the dragger
        private bool _isPressed = false;
        // need to control the ::start called first time or not
        private bool _justCreatedObject = true;

        // temporary geometry
        private OdTvEntityId _entityId = null;
        private OdTvGeometryDataId _cloudFoldId = null;
        private OdTvGeometryDataId _cloudId = null;
        private OdTvGeometryDataId _tempEntity = null;

        List<OdTvGeometryDataId> _lastAppendedArcsList = new List<OdTvGeometryDataId>();

        private static int NumOfMarkup = 1;

        public OdTvCloudMarkupDragger(OdTvGsDeviceId deviceId, OdTvModelId markupModelId)
            : base(deviceId, markupModelId)
        {
            NeedFreeDrag = true;

            MemoryTransaction mTr = MM.StartTransaction();
            // create main entity
            OdTvModel pModel = markupModelId.openObject(OpenMode.kForWrite);
            _entityId = FindMarkupEntity(NameOfMarkupTempEntity, true);
            if (_entityId == null)
            {
                _entityId = pModel.appendEntity(NameOfMarkupTempEntity);
                _entityId.openObject(OpenMode.kForWrite).setColor(MarkupColor);
            }

            // crate circle subEntity if not exist
            _cloudFoldId = FindSubEntity(_entityId.openObject().getGeometryDataIterator(), NameOfMarkupCloudFold);
            if (_cloudFoldId == null)
                _cloudFoldId = _entityId.openObject(OpenMode.kForWrite).appendSubEntity(NameOfMarkupCloudFold);

            MM.StopTransaction(mTr);
        }

        public override DraggerResult Start(OdTvDragger prevDragger, int activeView, Cursor cursor, TvWpfViewWCS wcs)
        {
            TvActiveViewport = activeView;
            DraggerResult res = DraggerResult.NothingToDo;

            // create temporary geometry
            if (!_justCreatedObject)
            {
                UpdateFrame(true);
                res = DraggerResult.NeedUpdateView;
            }

            res = res | base.Start(prevDragger, activeView, cursor, wcs);

            // add dragger model to the view
            AddDraggersModelToView();

            if (!_justCreatedObject)
                State = DraggerState.Working;

            _justCreatedObject = false;

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
                _lastPoint = _firstPoint;
            }
            else if (_lastPoint != _firstPoint)
            {
                MemoryTransaction mtr = MM.StartTransaction();
                if (_cloudId == null)
                    CreateFrame();
                DrawArcs(_cloudId.openAsSubEntity(OpenMode.kForWrite));
                _firstPoint = _lastPoint;
                MM.StopTransaction(mtr);
                return DraggerResult.NeedUpdateView;
            }

            return DraggerResult.NothingToDo;
        }

        public override DraggerResult Drag(int x, int y)
        {
            if (!CheckDragger() || !_isPressed)
                return DraggerResult.NothingToDo;

            _lastPoint = ToEyeToWorld(x, y);
            UpdateFrame(_tempEntity == null);

            return DraggerResult.NeedUpdateView;
        }

        public override bool ProcessEnter()
        {
            MemoryTransaction mtr = MM.StartTransaction();
            if (_cloudId != null)
            {
                OdTvEntity cloud = _cloudId.openAsSubEntity(OpenMode.kForWrite);
                OdTvGeometryDataIterator it = cloud.getGeometryDataIterator();

                OdGePoint3d firstPt = null;
                if (it != null && !it.done())
                    firstPt = it.getGeometryData().openAsCircleArc().getStart();

                // count of arcs
                uint acrsNum = 0;

                while (!it.done())
                {
                    it.step();
                    acrsNum++;
                }

                // close cloud
                if (acrsNum >= 2)
                {
                    _lastPoint = firstPt;
                    DrawArcs(cloud);
                }
            }

            _isSuccess = true;

            State = DraggerState.Waiting;

            MM.StopTransaction(mtr);

            return true;
        }

        public override OdTvDragger Finish(out DraggerResult rc)
        {
            MemoryTransaction mtr = MM.StartTransaction();

            if (!_isSuccess && _cloudId != null && _lastAppendedArcsList.Count > 0)
                _lastAppendedArcsList.ForEach(id => { _cloudId.openAsSubEntity(OpenMode.kForWrite).removeGeometryData(id); });

            if(_cloudId != null)
                _cloudId.openAsSubEntity(OpenMode.kForWrite).setLineWeight(LineWeight);
            if (_tempEntity != null)
                RemoveGeometryData(ref _cloudFoldId, ref _tempEntity);

            DraggerResult rcFinish;
            OdTvDragger retFinish = base.Finish(out rcFinish);

            rc = rcFinish | DraggerResult.NeedUpdateView;

            MM.StopTransaction(mtr);

            return retFinish;
        }


        public override bool UpdateCursor()
        {
            CurrentCursor = State == DraggerState.Finishing ? LasAppActiveCursor : Cursors.Cross;
            return true;
        }

        private bool ComparePoints(OdGePoint3d p1, OdGePoint3d p2)
        {
            if (p1.x.Equals(p2.x) && p1.y.Equals(p2.y) && p1.z.Equals(p2.z))
                return false;
            return true;
        }

        private void UpdateFrame(bool isNeedCreate)
        {
            if (TvView == null || !ComparePoints(_firstPoint, _lastPoint))
                return;
            MemoryTransaction mtr = MM.StartTransaction();

            if (isNeedCreate)
            {
                if (_tempEntity == null)
                    _tempEntity = _cloudFoldId.openAsSubEntity(OpenMode.kForWrite).appendSubEntity("TempArcs");
                OdTvEntity newEn = _tempEntity.openAsSubEntity(OpenMode.kForWrite);
                DrawArcs(newEn);
            }
            else
            {
                if(_tempEntity != null)
                {
                    // Get arcs and update them
                    OdTvEntity cloudEntity = _tempEntity.openAsSubEntity(OpenMode.kForWrite);
                    OdTvGeometryDataIterator pGeomIterator = cloudEntity.getGeometryDataIterator();
                    OdTvGeometryDataId firstArcId = pGeomIterator.getGeometryData();
                    pGeomIterator.step();
                    OdTvGeometryDataId secondArcId = pGeomIterator.getGeometryData();
                    if (firstArcId == null || secondArcId == null)
                        return;
                    // Edit arcs
                    UpdateArcs(firstArcId, secondArcId);
                }
            }

            MM.StopTransaction(mtr);
        }

        private void CalculateArcs(ref OdGePoint3d startPt, ref OdGePoint3d firstMidPt, ref OdGePoint3d midPt,
            ref OdGePoint3d secMidPt, ref OdGePoint3d endPt)
        {
            startPt = _firstPoint;
            endPt = _lastPoint;

            // Calculate point in the middle of arcs
            double lth = (startPt - endPt).length();
            double r = lth / 3;
            double lth2 = lth / 2;
            double s = Math.Sqrt(lth2 * (lth2 - r) * (lth2 - r) * (lth2 - lth + 2 * r));
            double ang = Math.Asin(2 * s / (r * (lth - 2 * r))) / 2;
            double c = r * Math.Sin(2 * ang) / Math.Sin(ang);

            midPt = endPt - startPt.asVector();
            if(!lth.Equals(0d) && !c.Equals(0d))
                midPt = new OdGePoint3d(midPt.x / lth * c, midPt.y / lth * c, midPt.z / lth * c);

            OdGeMatrix3d rotMatr = new OdGeMatrix3d();

            OdTvGsView view = TvView.openObject();
            rotMatr.setToRotation(ang, view.position() - view.target());
            midPt = rotMatr * midPt + startPt.asVector();

            // Calculate circles centers
            OdGePoint3d firstCenter = startPt + (endPt - startPt) / lth * r;
            OdGePoint3d secondCenter = endPt + (startPt - endPt) / lth * r;

            // Calculate third point for arcs
            rotMatr.setToIdentity();
            rotMatr.setToRotation(-Math.PI / 2, view.position() - view.target());

            OdGeVector3d dir = startPt - firstCenter;
            firstMidPt = firstCenter + rotMatr * dir;

            dir = midPt - secondCenter;
            secMidPt = secondCenter + rotMatr * dir;
        }

        private void DrawArcs(OdTvEntity entity)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdGePoint3d startPoint = OdGePoint3d.kOrigin, firstMidPoint = OdGePoint3d.kOrigin, midPoint = OdGePoint3d.kOrigin, secondMidPoint = OdGePoint3d.kOrigin, endPoint = OdGePoint3d.kOrigin;
            CalculateArcs(ref startPoint, ref firstMidPoint, ref midPoint, ref secondMidPoint, ref endPoint);

            _lastAppendedArcsList.Add(entity.appendCircleArc(startPoint, firstMidPoint, midPoint));
            _lastAppendedArcsList.Add(entity.appendCircleArc(midPoint, secondMidPoint, endPoint));
            MM.StopTransaction(mtr);
        }

        private void UpdateArcs(OdTvGeometryDataId id1, OdTvGeometryDataId id2)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdGePoint3d startPoint = OdGePoint3d.kOrigin, firstMidPoint = OdGePoint3d.kOrigin, midPoint = OdGePoint3d.kOrigin, secondMidPoint = OdGePoint3d.kOrigin, endPoint = OdGePoint3d.kOrigin;
            CalculateArcs(ref startPoint, ref firstMidPoint, ref midPoint, ref secondMidPoint, ref endPoint);
            id1.openAsCircleArc().set(startPoint, firstMidPoint, midPoint);
            id2.openAsCircleArc().set(midPoint, secondMidPoint, endPoint);
            MM.StopTransaction(mtr);
        }

        private void CreateFrame()
        {
            MemoryTransaction mtr = MM.StartTransaction();
            _cloudId = _cloudFoldId.openAsSubEntity(OpenMode.kForWrite).appendSubEntity("CloudMarkup_" + NumOfMarkup++);
            MM.StopTransaction(mtr);
        }
    }
}
