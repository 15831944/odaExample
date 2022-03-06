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
using Teigha.Visualize;
using Teigha.Core;

namespace WpfVisualizeViewer.Misc
{
    public class TvWpfViewWCS
    {
        // Special model for WCS object
        private OdTvModelId _tvWcsModelId;

        // View, in which this WCS is located
        private OdTvGsViewId _viewId;

        // View, associated with this view
        private OdTvGsViewId _wcsViewId;

        private static int wcsViewNumber = 1;

        private MemoryManager MM = MemoryManager.GetMemoryManager();

        public TvWpfViewWCS(OdTvDatabaseId tvDbId, OdTvGsViewId tvViewId)
        {
            _viewId = tvViewId;

            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsDevice dev = _viewId.openObject().device().openObject(OpenMode.kForWrite);

            // add wcs view
            OdTvResult rc = new OdTvResult();
            rc = OdTvResult.tvOk;
            _wcsViewId = dev.createView("WcsView_" + wcsViewNumber, false, ref rc);
            dev.addView(_wcsViewId);

            _tvWcsModelId = tvDbId.openObject(OpenMode.kForWrite).createModel("$ODA_TVVIEWER_WCS_" + wcsViewNumber++);
            OdTvGsView wcsView = _wcsViewId.openObject(OpenMode.kForWrite);
            wcsView.addModel(_tvWcsModelId);

            MM.StopTransaction(mtr);
        }
        
        public void UpdateWCS()
        {
            MemoryTransaction mtr = MM.StartTransaction();

            OdTvGsView view = _viewId.openObject();

            // remove old wcs entities
            OdTvModel wcsModel = _tvWcsModelId.openObject(OpenMode.kForWrite);
            wcsModel.clearEntities();

            //1.1 Add wcs entity
            OdTvEntityId wcsObjId = wcsModel.appendEntity("WCS");
            OdTvEntity wcsObj = wcsObjId.openObject(OpenMode.kForWrite);

            // define the start point for the WCS
            OdGePoint3d start = new OdGePoint3d(0d, 0d, 0d);

            // caculate axis lines length in wireframe and shaded modes
            double lineLength = 0.09;
            if ((int)view.mode() != (int)OdGsView.RenderMode.kWireframe && (int)view.mode() != (int)OdGsView.RenderMode.k2DOptimized)
                lineLength = 0.07;

            // create X axis and label
            OdTvGeometryDataId wcsX = wcsObj.appendSubEntity("wcs_x");
            OdTvEntity pWcsX = wcsX.openAsSubEntity(OpenMode.kForWrite);
            OdGePoint3d endx = new OdGePoint3d(start);
            endx.x += lineLength;
            CreateWcsAxis(wcsX, new OdTvColorDef(189, 19, 19), start, endx, "X");

            // create Y axis and label
            OdTvGeometryDataId wcsY = wcsObj.appendSubEntity("wcs_y");
            OdTvEntity pWcsY = wcsY.openAsSubEntity(OpenMode.kForWrite);
            OdGePoint3d endy = new OdGePoint3d(start);
            endy.y += lineLength;
            CreateWcsAxis(wcsY, new OdTvColorDef(12, 171, 20), start, endy, "Y");

            // create Z axis and label
            OdTvGeometryDataId wcsZ = wcsObj.appendSubEntity("wcs_z");
            OdTvEntity pWcsZ = wcsZ.openAsSubEntity(OpenMode.kForWrite);
            OdGePoint3d endz = new OdGePoint3d(start);
            endz.z += lineLength;
            CreateWcsAxis(wcsZ, new OdTvColorDef(20, 57, 245), start, endz, "Z");

            _wcsViewId.openObject().device().openObject().invalidate();
            MM.StopTransaction(mtr);
        }

        public bool IsNeedUpdateWCS(OdTvGsView.RenderMode oldmode, OdTvGsView.RenderMode newmode)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsView wcsView = _wcsViewId.openObject(OpenMode.kForWrite);
            if (wcsView == null)
            {
                MM.StopTransaction(mtr);
                return false;
            }

            bool bOldModeWire = false;
            if (oldmode == OdTvGsView.RenderMode.k2DOptimized || oldmode == OdTvGsView.RenderMode.kWireframe)
                bOldModeWire = true;

            bool bNewModeWire = false;
            if (newmode == OdTvGsView.RenderMode.k2DOptimized || newmode == OdTvGsView.RenderMode.kWireframe)
                bNewModeWire = true;

            wcsView.setMode(bNewModeWire ? OdTvGsView.RenderMode.kWireframe : OdTvGsView.RenderMode.kGouraudShaded);

            if (bOldModeWire != bNewModeWire)
            {
                MM.StopTransaction(mtr);
                return true;
            }

            MM.StopTransaction(mtr);
            return false;
        }

        private void CreateWcsAxis(OdTvGeometryDataId wcsId, OdTvColorDef color, OdGePoint3d startPoint, OdGePoint3d endPoint, string axisName)
        {
            MemoryTransaction mtr = MM.StartTransaction();

            OdTvEntity pWcs = wcsId.openAsSubEntity(OpenMode.kForWrite);
            pWcs.setColor(color);

            OdTvGsView view = _wcsViewId.openObject();

            OdGePoint3d labelRefPoint = new OdGePoint3d(endPoint);

            // draw lines in wireframe and draw cylinders in shaded modes
            if ((int)view.mode() == (int)OdGsView.RenderMode.k2DOptimized || (int)view.mode() == (int)OdGsView.RenderMode.kWireframe)
            {
                //append axis
                pWcs.appendPolyline(startPoint, endPoint);
            }
            else
            {
                // distance to the end of the arrow
                double lastPointDist = 0.022;
                OdGePoint3d lastPoint = new OdGePoint3d(endPoint);
                if (axisName == "X")
                    lastPoint.x += lastPointDist;
                else if (axisName == "Y")
                    lastPoint.y += lastPointDist;
                else if (axisName == "Z")
                    lastPoint.z += lastPointDist;

                OdTvPointArray pnts = new OdTvPointArray();
                pnts.Add(new OdGePoint3d(startPoint));
                pnts.Add(new OdGePoint3d(endPoint));
                pnts.Add(new OdGePoint3d(endPoint));
                pnts.Add(new OdGePoint3d(lastPoint));

                OdGeDoubleArray radii = new OdGeDoubleArray(4);
                radii.Add(0.007);
                radii.Add(0.007);
                radii.Add(0.015);
                radii.Add(0d);

                pWcs.appendShellFromCylinder(pnts, radii, OdTvCylinderData.Capping.kBoth, 50);

                // update label reference point
                labelRefPoint = lastPoint;
            }

            // append labels
            if (axisName == "X")
                labelRefPoint.x += 0.015;
            else if (axisName == "Y")
                labelRefPoint.y += 0.015;
            else if (axisName == "Z")
                labelRefPoint.z += 0.015;

            OdTvEntityId wcsTextEntityId = _tvWcsModelId.openObject(OpenMode.kForWrite).appendEntity("TextEntity");
            OdTvEntity textEntity = wcsTextEntityId.openObject(OpenMode.kForWrite);
            textEntity.setColor(color);
            textEntity.setAutoRegen(true);

            OdTvGeometryDataId labelTextId = textEntity.appendText(labelRefPoint, axisName);
            OdTvTextData labelText = labelTextId.openAsText();
            labelText.setAlignmentMode(OdTvTextStyle.AlignmentType.kMiddleCenter);
            labelText.setTextSize(0.02);
            labelText.setNonRotatable(true);

            if ((int)view.mode() != (int)OdGsView.RenderMode.k2DOptimized && (int)view.mode() != (int)OdGsView.RenderMode.kWireframe)
                textEntity.setLineWeight(new OdTvLineWeightDef(4));

            MM.StopTransaction(mtr);
        }

        public void removeWCS()
        {
            MemoryTransaction mtr = MM.StartTransaction();
            // remove old wcs entities
            _tvWcsModelId.openObject(OpenMode.kForWrite).clearEntities();
            MM.StopTransaction(mtr);
        }

        public OdTvGsViewId GetWcsViewId()
        {
            return _wcsViewId;
        }

        public OdTvGsViewId GetParentView()
        {
            return _viewId;
        }
    }
}
