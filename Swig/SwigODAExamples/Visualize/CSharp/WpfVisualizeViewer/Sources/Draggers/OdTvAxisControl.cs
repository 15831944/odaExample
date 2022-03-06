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
    public class OdTvAxisControl
    {
        protected MemoryManager MM = MemoryManager.GetMemoryManager();

        public const uint DEVICE_AXIS_LENGTH = 75;
        public const uint DEVICE_AXISARROW_LENGTH = 15;
        public const uint DEVICE_AXIS_RADIUS = 1;
        public const double DEVICE_AXIS_ARROW_COEFF = 6d;
        public const double DEVICE_ROTATION_AXIS_COEFF = 6d;
        public const double DEVICE_ROTATION_ORIGIN_AXIS_COEFF = 10d;

        // model for temp axis object
        protected OdTvModelId _modelId;
        // view for display axis object
        protected OdTvGsViewId _viewId;
        // view for display axis object
        protected OdTvGsViewId _parentViewId;
        // insertion point
        protected OdGePoint3d _wcsInsertPoint;
        // scale coefficient to transfrom device -> WCS (first time)
        protected double _wcsScaleCoef = 1d;
        // coefficient for the scale matrix
        protected double _scaleForScaleMatrix = 1d;
        // indicate whether the control is attached or not
        public bool IsAttached { get; set; }
        // currently highlighted axis
        protected OdTvEntityId _highlightedAxis;
        protected OdTvColorDef _unhighlightedAxisColor;
        // base point for calculating the transform
        protected OdGePoint3d _basePoint = new OdGePoint3d(OdGePoint3d.kOrigin);
        // last transformation
        protected OdGeMatrix3d _xForm = OdGeMatrix3d.kIdentity;

        public OdTvAxisControl()
        {
            IsAttached = false;
        }

        public void Remove()
        {
            if (IsAttached)
                Detach();

            MemoryTransaction mtr = MM.StartTransaction();

            if (_modelId != null && !_modelId.isNull())
            {
                OdTvDatabaseId dbId = null;
                {
                    OdTvModel pModel = _modelId.openObject();
                    if (pModel != null)
                        dbId = pModel.getDatabase();
                }

                if (dbId != null && !dbId.isNull())
                {
                    OdTvDatabase pTvDb = dbId.openObject(OpenMode.kForWrite);
                    pTvDb.removeModel(_modelId);
                }
            }

            if (_viewId != null && !_viewId.isNull())
            {
                OdTvGsDeviceId tvDeviceId = null;
                {
                    OdTvGsView pView = _viewId.openObject();
                    if (pView != null)
                        tvDeviceId = _viewId.openObject().device();
                }

                if (tvDeviceId != null && !tvDeviceId.isNull())
                    tvDeviceId.openObject(OpenMode.kForWrite).eraseView(_viewId);
            }

            MM.StopTransaction(mtr);
        }

        //initialize
        public void Init(OdTvGsViewId parentViewId)
        {
            _parentViewId = parentViewId;
        }

        //attach control to the parent view
        public virtual bool Attach(OdGePoint3d wcsPos)
        {
            _wcsInsertPoint = wcsPos;
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
                OdTvGsView pView = _viewId.openObject(OpenMode.kForWrite);
                pView.setMode(OdTvGsView.RenderMode.kFlatShaded);
                pView.setView(pParentView.position(), pParentView.target(), pParentView.upVector(), pParentView.fieldWidth(), pParentView.fieldHeight()
                    , pParentView.isPerspective() ? OdTvGsView.Projection.kPerspective : OdTvGsView.Projection.kParallel);

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
            if (!ConstructAxisGeometry("X", new OdTvColorDef(234, 47, 47)))
            {
                MM.StopTransaction(mtr);
                return false;
            }

            // create Y axis
            if (!ConstructAxisGeometry("Y", new OdTvColorDef(40, 240, 50)))
            {
                MM.StopTransaction(mtr);
                return false;
            }

            // create Z axis
            if (!ConstructAxisGeometry("Z", new OdTvColorDef(35, 72, 245)))
            {
                MM.StopTransaction(mtr);
                return false;
            }

            MM.StopTransaction(mtr);

            return true;
        }

        //construct the axis geometry
        protected virtual bool ConstructAxisGeometry(string name, OdTvColorDef color)
        {
            MemoryTransaction mtr = MM.StartTransaction();

            OdTvModel pModel = _modelId.openObject(OpenMode.kForWrite);
            if(pModel == null)
            {
                MM.StopTransaction(mtr);
                return false;
            }

            OdTvGsView pParentView = _parentViewId.openObject(OpenMode.kForWrite);
            if(pParentView == null)
            {
                MM.StopTransaction(mtr);
                return false;
            }

            //calculate sizes of the axis in WCS
            OdGePoint2d pixArea = new OdGePoint2d(OdGePoint2d.kOrigin);
            pParentView.getNumPixelsInUnitSquare(_wcsInsertPoint, pixArea, false);
            _wcsScaleCoef = Math.Max(pixArea.x, pixArea.y);
            double axisWcsLength = DEVICE_AXIS_LENGTH / _wcsScaleCoef;
            double axisArrowWcsLength = DEVICE_AXISARROW_LENGTH / _wcsScaleCoef;
            double cylinderRadius = DEVICE_AXIS_RADIUS / _wcsScaleCoef;

            OdGePoint3d startPt = new OdGePoint3d(_wcsInsertPoint);
            OdGePoint3d endPt = new OdGePoint3d(startPt);
            OdGePoint3d lastPt = new OdGePoint3d(endPt);

            if(name.Equals("X"))
            {
                endPt.x += axisWcsLength;
                lastPt.x = endPt.x + axisArrowWcsLength;
            }
            else if(name.Equals("Y"))
            {
                endPt.y += axisWcsLength;
                lastPt.y = endPt.y + axisArrowWcsLength;
            }
            else if(name.Equals("Z"))
            {
                endPt.z += axisWcsLength;
                lastPt.z = endPt.z + axisArrowWcsLength;
            }
            else
            {
                MM.StopTransaction(mtr);
                return false;
            }

            //create entity with axis
            OdTvEntityId axisId = pModel.appendEntity(name);
            OdTvEntity pAxis = axisId.openObject(OpenMode.kForWrite);

            // set color to the entity
            pAxis.setColor(color);

            // create axis as a set of cylinders
            OdTvPointArray vertices = new OdTvPointArray();
            vertices.Add(startPt);
            vertices.Add(endPt);
            vertices.Add(endPt);
            vertices.Add(lastPt);

            OdGeDoubleArray radii = new OdGeDoubleArray();
            radii.Add(cylinderRadius);
            radii.Add(cylinderRadius);
            radii.Add(cylinderRadius * DEVICE_AXIS_ARROW_COEFF);
            radii.Add(0d);

            pAxis.appendShellFromCylinder(vertices, radii, OdTvCylinderData.Capping.kBoth, 50);

            // add xline
            OdTvGeometryDataId xlineId = pAxis.appendInfiniteLine(startPt, endPt, OdTvInfiniteLineData.Type.kLine);
            OdTvGeometryData pGeom = xlineId.openObject();
            pGeom.setVisibility(new OdTvVisibilityDef(false));
            pGeom.setColor(color);

            MM.StopTransaction(mtr);
            return true;
        }

        //remove control from the parent view
        public void Detach()
        {
            MemoryTransaction mtr = MM.StartTransaction();

            IsAttached = false;

            try
            {
                if (_viewId == null || _modelId == null || _parentViewId == null
                    || _viewId.isNull() || _modelId.isNull() || _parentViewId.isNull())
                {
                    MM.StopTransaction(mtr);
                    return;
                }

                OdTvGsView pParentView = _parentViewId.openObject(OpenMode.kForWrite);
                if (pParentView == null)
                {
                    MM.StopTransaction(mtr);
                    return;
                }

                OdTvGsDeviceId devId = pParentView.device();
                if (devId.isNull())
                {
                    MM.StopTransaction(mtr);
                    return;
                }

                OdTvGsDevice pDevice = devId.openObject(OpenMode.kForWrite);
                pDevice.removeView(_viewId);

                OdTvModel pModel = _modelId.openObject(OpenMode.kForWrite);
                if (pModel != null)
                    pModel.clearEntities();
            }
            catch (System.Exception)
            {

            }

            MM.StopTransaction(mtr);
        }

        //scale control according to the current view parameters
        public virtual void Scale()
        {
            MemoryTransaction mtr = MM.StartTransaction();

            OdTvGsView pParentView = _parentViewId.openObject(OpenMode.kForWrite);
            if(pParentView == null)
            {
                MM.StopTransaction(mtr);
                return;
            }
            OdTvModel pModel = _modelId.openObject(OpenMode.kForWrite);
            if(pModel == null)
            {
                MM.StopTransaction(mtr);
                return;
            }

            //calculate new coeeficient from device->WCS
            OdGePoint2d pixArea = new OdGePoint2d(OdGePoint2d.kOrigin);
            pParentView.getNumPixelsInUnitSquare(_wcsInsertPoint, pixArea, false);
            double wcsScaleCoef = Math.Max(pixArea.x, pixArea.y);
            if (wcsScaleCoef < 1.0e-10)
                wcsScaleCoef = 1.0e-10;

            _scaleForScaleMatrix = _wcsScaleCoef / wcsScaleCoef;

            ApplyCurrentTransform();

            MM.StopTransaction(mtr);
        }

        protected void ApplyCurrentTransform()
        {
            MemoryTransaction mtr = MM.StartTransaction();

            OdTvModel pModel = _modelId.openObject(OpenMode.kForWrite);
            if(pModel == null)
            {
                MM.StopTransaction(mtr);
                return;
            }

            //calculate scaling matrix
            OdGeMatrix3d xFullTrans = new OdGeMatrix3d();
            xFullTrans = xFullTrans.setToIdentity();
            xFullTrans = xFullTrans.setToScaling(_scaleForScaleMatrix, _wcsInsertPoint);

            //add controller matrix
            xFullTrans = xFullTrans.preMultBy(_xForm);

            //scale the axis model. Here we will not use the fast transfrom since we have xLines and for us it will be usefull
            //if after setting the new transfrom matrix the entities will be regenerated
            pModel.setModelingMatrix(xFullTrans);

            MM.StopTransaction(mtr);
        }

        public bool Hover(int x, int y)
        {
            if (_viewId.isNull())
                return false;

            MemoryTransaction mtr = MM.StartTransaction();

            OdTvGsView pMoveView = _viewId.openObject(OpenMode.kForWrite);
            OdTvDCPoint[] pnts = new OdTvDCPoint[1];
            pnts[0] = new OdTvDCPoint(x, y);

            OdTvSelectionOptions selOpt = new OdTvSelectionOptions();
            selOpt.setMode(OdTvSelectionOptions.Mode.kPoint);

            //check about something selected
            OdTvSelectionSet pSset = pMoveView.select(pnts, selOpt, _modelId);

            // hightlight WCS axis
            if (pSset != null && pSset.numItems() == 1)
            {
                OdTvEntityId selEntity = pSset.getIterator().getEntity();

                if (selEntity != _highlightedAxis)
                {
                    Highlight(_highlightedAxis, false);
                    Highlight(selEntity, true);
                    _highlightedAxis = selEntity;
                    MM.StopTransaction(mtr);
                    return true;
                }
            }
            else if (_highlightedAxis != null && !_highlightedAxis.isNull())
            {
                Highlight(_highlightedAxis, false);
                _highlightedAxis.setNull();
                MM.StopTransaction(mtr);
                return true;
            }

            MM.StopTransaction(mtr);

            return false;
        }

        protected void Highlight(OdTvEntityId axisId, bool bHighlight)
        {
            if (axisId == null || axisId.isNull())
                return;

            MemoryTransaction mtr = MM.StartTransaction();

            //open Entity
            OdTvEntity pAxis = axisId.openObject(OpenMode.kForWrite);

            //get xLine
            OdTvGeometryDataIterator pGeometryIt = pAxis.getGeometryDataIterator();
            if (pGeometryIt != null && !pGeometryIt.done())
                pGeometryIt.step();

            OdTvGeometryDataId xlineId = null;
            if (!pGeometryIt.done())
                xlineId = pGeometryIt.getGeometryData();

            OdTvGeometryData pXLine = null;
            if (!xlineId.isNull())
                pXLine = xlineId.openObject();

            //perform highlight
            if (bHighlight)
            {
                _unhighlightedAxisColor = pAxis.getColor();
                pAxis.setColor(new OdTvColorDef(255, 128, 0));
            }
            else
                pAxis.setColor(_unhighlightedAxisColor);

            if (pXLine != null)
                pXLine.setVisibility(new OdTvVisibilityDef(bHighlight));

            MM.StopTransaction(mtr);
        }

        public bool HasSelectedControl()
        {
            return _highlightedAxis != null && !_highlightedAxis.isNull();
        }

        public void Start(int x, int y)
        {
            _xForm = OdGeMatrix3d.kIdentity;

            if (_parentViewId.isNull())
            {
                _basePoint = new OdGePoint3d(OdGePoint3d.kOrigin);
                return;
            }

            //calculate point in world coordinate
            _basePoint = ToEyeToWorld(x, y);
        }

        protected OdGePoint3d ToEyeToWorld(int x, int y)
        {
            OdGePoint3d wcsPt = new OdGePoint3d(x, y, 0d);

            if (_parentViewId.isNull())
                return wcsPt;

            MemoryTransaction mtr = MM.StartTransaction();

            OdTvGsView pView = _parentViewId.openObject(OpenMode.kForWrite);
            if (pView.isPerspective())
                wcsPt.z = pView.projectionMatrix()[2, 3];
            wcsPt = wcsPt.transformBy((pView.screenMatrix() * pView.projectionMatrix()).inverse());
            wcsPt.z = 0d;

            wcsPt = wcsPt.transformBy(pView.eyeToWorldMatrix());

            MM.StopTransaction(mtr);

            return wcsPt;
        }

        public void Finish()
        {
            MemoryTransaction mtr = MM.StartTransaction();

            _wcsInsertPoint = _wcsInsertPoint.transformBy(_xForm);

            //append last transfrom matrix to the internal entities
            if (!_modelId.isNull())
            {
                OdTvEntitiesIterator pEntIter = _modelId.openObject(OpenMode.kForWrite).getEntitiesIterator();
                while (!pEntIter.done())
                {
                    OdTvEntityId entityId = pEntIter.getEntity();
                    if (entityId.getType() == OdTvEntityId.EntityTypes.kEntity)
                    {
                        OdTvEntity pEntity = entityId.openObject(OpenMode.kForWrite);
                        pEntity.appendModelingMatrix(_xForm);
                    }

                    pEntIter.step();
                }
            }

            _basePoint = OdGePoint3d.kOrigin;
            _xForm = OdGeMatrix3d.kIdentity;

            ApplyCurrentTransform();

            MM.StopTransaction(mtr);
        }

        public virtual OdGeMatrix3d GetTransform(int x, int y, out OdTvResult rc)
        {
            OdGeMatrix3d newTransform = new OdGeMatrix3d();
            if (_highlightedAxis.isNull())
            {
                rc = OdTvResult.tvInvalidInput;
                return newTransform;
            }

            MemoryTransaction mtr = MM.StartTransaction();

            string name = _highlightedAxis.openObject().getName();
            OdGePoint3d newPoint = ToEyeToWorld(x, y);

            //new full matrix
            OdGeMatrix3d matNewTransform = new OdGeMatrix3d();
            matNewTransform = OdGeMatrix3d.kIdentity;
            OdGeVector3d diff = newPoint - _basePoint;

            if (!name.Equals("X"))
                matNewTransform[0, 3] = diff.x;
            else if (!name.Equals("Y"))
                matNewTransform[1, 3] = diff.y;
            else if (!name.Equals("Z"))
                matNewTransform[2, 3] = diff.z;

            newTransform = _xForm.inverse();
            newTransform = newTransform.preMultBy(matNewTransform);

            //remember last full transfrom
            _xForm = matNewTransform;

            //apply current transform
            ApplyCurrentTransform();

            MM.StopTransaction(mtr);

            rc = OdTvResult.tvOk;

            return newTransform;
        }

    }
}
