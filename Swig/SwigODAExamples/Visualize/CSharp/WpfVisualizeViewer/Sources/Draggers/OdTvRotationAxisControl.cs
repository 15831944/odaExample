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

namespace WpfVisualizeViewer.Draggers
{
    public class OdTvRotationAxisControl : OdTvAxisControl
    {
        public OdGeVector3d UAxis { get; set; }
        public OdGeVector3d VAxis { get; set; }
        protected double _dAxisWcsLength = 0d;

        public OdTvRotationAxisControl()
        {
            UAxis = new OdGeVector3d(OdGeVector3d.kIdentity);
            VAxis = new OdGeVector3d(OdGeVector3d.kIdentity);
        }

        public OdTvRotationAxisControl(OdGeVector3d uAxis, OdGeVector3d vAxis)
        {
            UAxis = uAxis;
            VAxis = vAxis;
        }

        protected bool ConstructAxisGeometry(string name, OdTvColorDef color, OdGeVector3d uAxis, OdGeVector3d vAxis)
        {
            MemoryTransaction mtr = MM.StartTransaction();

            OdTvModel pModel = _modelId.openObject(OpenMode.kForWrite);
            if (pModel == null)
            {
                MM.StopTransaction(mtr);
                return false;
            }

            OdTvGsView pParentView = _parentViewId.openObject(OpenMode.kForWrite);
            if (pParentView == null)
            {
                MM.StopTransaction(mtr);
                return false;
            }

            //calculate sizes of the axis in WCS
            OdGePoint2d pixArea = new OdGePoint2d(OdGePoint2d.kOrigin);
            pParentView.getNumPixelsInUnitSquare(_wcsInsertPoint, pixArea, false);
            _wcsScaleCoef = Math.Max(pixArea.x, pixArea.y);
            double axisWcsLength = DEVICE_AXIS_LENGTH / _wcsScaleCoef;
            double cylinderRadius = DEVICE_AXIS_RADIUS / _wcsScaleCoef;

            _dAxisWcsLength = axisWcsLength; // TODO remove

            OdGePoint3d startPt = new OdGePoint3d(_wcsInsertPoint);
            OdGePoint3d endPt = new OdGePoint3d(startPt);

            OdGeMatrix3d transform = new OdGeMatrix3d();
            transform = transform.setToIdentity();
            if (name.Equals("Origin"))
            {
                cylinderRadius *= DEVICE_ROTATION_ORIGIN_AXIS_COEFF;
            }
            else if (name.Equals("U"))
            {
                transform = transform.setToTranslation(UAxis * axisWcsLength);
            }
            else if (name.Equals("V"))
            {
                transform = transform.setToTranslation(VAxis * axisWcsLength);
            }
            else
                return false;

            endPt = endPt.transformBy(transform);

            //create entity with axis
            OdTvEntityId axisId = pModel.appendEntity(name);
            OdTvEntity pAxis = axisId.openObject(OpenMode.kForWrite);

            //set color to the entity
            pAxis.setColor(color);

            if (name.Equals("Origin"))
            {
                //create axis as a cylinder
                OdTvGeometryDataId axisGeomId = pAxis.appendShellFromSphere(startPt, cylinderRadius, OdGeVector3d.kYAxis, OdGeVector3d.kXAxis, 20);

                // add xline
                OdGeVector3d dir = UAxis.crossProduct(VAxis);
                OdTvGeometryDataId xlineId = pAxis.appendInfiniteLine(startPt, startPt + dir, OdTvInfiniteLineData.Type.kLine);
                OdTvGeometryData pGeom = xlineId.openObject();
                pGeom.setVisibility(new OdTvVisibilityDef(false));
                pGeom.setColor(color);
            }
            else
            {
                //create axis as a cylinder
                OdTvGeometryDataId axisGeomId = pAxis.appendShellFromCylinder(startPt, endPt, cylinderRadius, OdTvCylinderData.Capping.kBoth, 50);
                // add xline
                OdTvGeometryDataId xlineId = pAxis.appendCircle(startPt, axisWcsLength, name.Equals("U") ? VAxis : UAxis);
                OdTvGeometryData pGeom = xlineId.openObject();
                pGeom.setVisibility(new OdTvVisibilityDef(false));
                pGeom.setColor(color);
            }

            return true;
        }

        public bool Attach(OdGePoint3d wcsPos, OdGeVector3d uAxis, OdGeVector3d vAxis)
        {
            _wcsInsertPoint = wcsPos;
            UAxis = uAxis;
            VAxis = vAxis;
            if (_parentViewId.isNull())
                return false;

            MemoryTransaction mtr = MM.StartTransaction();

            OdTvGsView pParentView = _parentViewId.openObject(OpenMode.kForWrite);
            // get parent device
            OdTvGsDeviceId devId = pParentView.device();
            if (devId.isNull())
            {
                MM.StopTransaction(mtr);
                return false;
            }
            OdTvGsDevice pDevice = devId.openObject(OpenMode.kForWrite);

            // 1. create or update new view
            if (_viewId == null || _viewId.isNull())
            {
                _viewId = pDevice.createView("$" + pParentView.getName() + "_AXISCONTROLVIEW", false);

                if (_viewId.isNull())
                {
                    MM.StopTransaction(mtr);
                    return false;
                }

                // 1.1 add view to the device
                pDevice.addView(_viewId);

                // 1.2 setup new view
                MemoryTransaction viewTr = MM.StartTransaction();
                OdTvGsView pView = _viewId.openObject(OpenMode.kForWrite);
                pView.setMode(OdTvGsView.RenderMode.kFlatShaded);
                pView.setView(pParentView.position(), pParentView.target(), pParentView.upVector(), pParentView.fieldWidth(), pParentView.fieldHeight()
                    , pParentView.isPerspective() ? OdTvGsView.Projection.kPerspective : OdTvGsView.Projection.kParallel);
                MM.StopTransaction(viewTr);

                //add view as sibling (need for the automatic transfer of the main view changes to the control view)
                pParentView.addSibling(_viewId);
            }
            else
                pDevice.addView(_viewId);

            // 2. create model or use existing
            if (_modelId == null || _modelId.isNull())
            {
                OdTvDatabase pTvDb = pDevice.getDatabase().openObject(OpenMode.kForWrite);
                // create model
                _modelId = pTvDb.createModel("$" + pParentView.getName() + "_AXISCONTROLMODEL", OdTvModel.Type.kMain, false);
                if (_modelId.isNull())
                {
                    MM.StopTransaction(mtr);
                    return false;
                }
            }

            // 2.1 Add model to view
            _viewId.openObject(OpenMode.kForWrite).addModel(_modelId);

            IsAttached = true;

            // 3. create geometry
            // create X axis
            if (!ConstructAxisGeometry("Origin", new OdTvColorDef(234, 47, 47), uAxis, vAxis))
            {
                MM.StopTransaction(mtr);
                return false;
            }

            // create Y axis
            if (!ConstructAxisGeometry("U", new OdTvColorDef(40, 240, 50), uAxis, vAxis))
            {
                MM.StopTransaction(mtr);
                return false;
            }

            // create Z axis
            if (!ConstructAxisGeometry("V", new OdTvColorDef(35, 72, 245), uAxis, vAxis))
            {
                MM.StopTransaction(mtr);
                return false;
            }

            MM.StopTransaction(mtr);

            return true;
        }

        public override OdGeMatrix3d GetTransform(int x, int y, out OdTvResult rc)
        {
            OdGeMatrix3d newTransform = new OdGeMatrix3d();
            newTransform = newTransform.setToIdentity();
            if (_highlightedAxis.isNull())
            {
                rc = OdTvResult.tvInvalidInput;
                return newTransform;
            }

            OdGePoint3d newPoint = ToEyeToWorld(x, y);

            // new full matrix
            OdGeMatrix3d matNewTransform = new OdGeMatrix3d();
            matNewTransform = matNewTransform.setToIdentity();

            OdGePlane cuttingPlane = new OdGePlane(_wcsInsertPoint, UAxis, VAxis);
            OdGeVector3d cuttingPlaneNormal = cuttingPlane.normal();

            MemoryTransaction mtr = MM.StartTransaction();

            OdTvGsView pMoveView = _viewId.openObject(OpenMode.kForWrite);

            // Get transform matrix for cutting plane updating
            string name = _highlightedAxis.openObject().getName();
            OdGeVector3d offset = newPoint - _basePoint;
            if (name.Equals("Origin"))
            {
                double projLength = offset.dotProduct(cuttingPlaneNormal);
                matNewTransform = OdGeMatrix3d.translation(cuttingPlaneNormal * projLength);
            }
            else if (name.Equals("U"))
            {
                OdGeVector3d proj = offset.orthoProject((pMoveView.position() - pMoveView.target()).normal());
                double dot = -proj.dotProduct(cuttingPlaneNormal);

                matNewTransform = OdGeMatrix3d.rotation(dot / _dAxisWcsLength, VAxis, _wcsInsertPoint);
            }
            else if (name.Equals("V"))
            {
                OdGeVector3d proj = offset.orthoProject((pMoveView.position() - pMoveView.target()).normal());
                double dot = proj.dotProduct(cuttingPlaneNormal);

                matNewTransform = OdGeMatrix3d.rotation(dot / _dAxisWcsLength, UAxis, _wcsInsertPoint);
            }
            else
            {
                rc = OdTvResult.tvInvalidInput;
                MM.StopTransaction(mtr);
                return newTransform;
            }

            MM.StopTransaction(mtr);

            newTransform = _xForm.inverse();
            newTransform = newTransform.preMultBy(matNewTransform);

            //remember last full transform
            _xForm = matNewTransform;
            //apply current transform
            ApplyCurrentTransform();

            rc = OdTvResult.tvOk;

            return newTransform;
        }

        public override void Scale()
        {
            base.Scale();
            _dAxisWcsLength *= _scaleForScaleMatrix;
        }

        public void Unhighlight()
        {
            Highlight(_highlightedAxis, false);
            if(_highlightedAxis != null)
                _highlightedAxis.setNull();
        }

        public void ApplyTransformToAxis()
        {
            UAxis = UAxis.transformBy(_xForm);
            VAxis = VAxis.transformBy(_xForm);
        }

    }
}
