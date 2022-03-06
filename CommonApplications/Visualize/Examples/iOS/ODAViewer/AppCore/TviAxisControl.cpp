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

// ODA Platform
#include "OdaCommon.h"

// ODA Visualize SDK
#include "TvGsDevice.h"
#include "TvDatabase.h"

#include "TviAxisControl.hpp"

#define DEVICE_AXIS_LENGTH 170
#define DEVICE_AXISARROW_LENGTH 15
#define DEVICE_AXIS_RADIUS 3
#define DEVICE_ROTATION_AXIS_RADIUS 9
#define DEVICE_AXIS_ARROW_COEFF 2.5
#define DEVICE_ROTATION_AXIS_COEFF 6.
#define DEVICE_ROTATION_ORIGIN_AXIS_COEFF 10.


//***************************************************************************//
// 'OdTvViewerBaseDragger' methods implementation
//***************************************************************************//

OdTvUIAxisControl::~OdTvUIAxisControl()
{
  detach();

  if (!m_modelId.isNull())
  {
    OdTvDatabaseId dbId;
    {
      OdTvModelPtr pModel = m_modelId.openObject();
      if (!pModel.isNull())
        dbId = pModel->getDatabase();
    }

    if (!dbId.isNull())
    {
      OdTvDatabasePtr pTvDb = dbId.openObject(OdTv::kForWrite);
      pTvDb->removeModel(m_modelId);
    }
  }

  if (!m_viewId.isNull())
  {
    OdTvGsDeviceId tvDeviceId;
    {
      OdTvGsViewPtr pView = m_viewId.openObject();
      if (!pView.isNull())
        tvDeviceId = m_viewId.openObject()->device();
    }

    if ( !tvDeviceId.isNull() )
      tvDeviceId.openObject(OdTv::kForWrite)->eraseView(m_viewId);
  }
}

void OdTvUIAxisControl::init(OdTvGsViewId& parentViewId)
{
  m_parentViewId = parentViewId;
}

bool OdTvUIAxisControl::attach(const OdTvPoint& wcsPos)
{
  m_wcsInsertPoint = wcsPos;

  if (m_parentViewId.isNull())
    return false;

  OdTvGsViewPtr pParentView = m_parentViewId.openObject(OdTv::kForWrite);

  //get parent device
  OdTvGsDeviceId devId = pParentView->device();
  if (devId.isNull())
    return false;
  OdTvGsDevicePtr pDevice = devId.openObject(OdTv::kForWrite);

  // 1. create or update new view
  if ( m_viewId.isNull() )
  {
    OdString strAxisViewName = OD_T("$") + pParentView->getName() + OD_T("_AXISCONTROLVIEW");
    m_viewId = pDevice->createView(strAxisViewName, false);

    if (m_viewId.isNull())
      return false;

    // 1.1 add view to the device
    pDevice->addView(m_viewId);

    // 1.2 setup new view
    OdTvGsViewPtr pView = m_viewId.openObject(OdTv::kForWrite);
    pView->setMode(OdTvGsView::kFlatShaded);
    pView->setView(pParentView->position(), pParentView->target(), pParentView->upVector(), pParentView->fieldWidth(), pParentView->fieldHeight(), pParentView->isPerspective() ? OdTvGsView::kPerspective : OdTvGsView::kParallel);

    //add view as sibling (need for the automatic transfer of the main view changes to the control view)
    pParentView->addSibling(m_viewId);
  }
  else
    pDevice->addView(m_viewId);

  // 2. create model or use existing
  if (m_modelId.isNull())
  {
    //generate name for the model
    OdString strWcsModelName = OD_T("$") + pParentView->getName() + OD_T("_AXISCONTROLMODEL");
   
    //get the database
    OdTvDatabasePtr pTvDb = pDevice->getDatabase().openObject(OdTv::kForWrite);
    
    // create new model
    m_modelId = pTvDb->createModel(strWcsModelName, OdTvModel::kMain, false);
    if (m_modelId.isNull())
      return false;
  }

  // 2.1 Add model to view
  m_viewId.openObject(OdTv::kForWrite)->addModel(m_modelId);

  m_bIsAttached = true;

  // 3. create geometry
  // create X axis
  if ( !constructAxisGeometry(OD_T("X"), OdTvColorDef(234, 47, 47)) )
    return false;

  // create Y axis
  if ( !constructAxisGeometry(OD_T("Y"), OdTvColorDef(40, 240, 50)) )
    return false;

  // create Z axis
  if ( !constructAxisGeometry(OD_T("Z"), OdTvColorDef(35, 72, 245)) )
    return false;

  return true;
}

void OdTvUIAxisControl::detach()
{
  m_bIsAttached = false;

  if (m_viewId.isNull() || m_modelId.isNull())
    return;

  if (m_parentViewId.isNull())
    return;

  OdTvGsViewPtr pParentView = m_parentViewId.openObject(OdTv::kForWrite);
  if (pParentView.isNull())
    return;

  //get parent device
  OdTvGsDeviceId devId = pParentView->device();
  if (devId.isNull())
    return;

  OdTvGsDevicePtr pDevice = devId.openObject(OdTv::kForWrite);
  pDevice->removeView(m_viewId);

  OdTvModelPtr pModel = m_modelId.openObject(OdTv::kForWrite);
  if (!pModel.isNull())
    pModel->clearEntities();
}

void OdTvUIAxisControl::scale()
{
  OdTvGsViewPtr pParentView = m_parentViewId.openObject(OdTv::kForWrite);
  if (pParentView.isNull())
    return;

  OdTvModelPtr pModel = m_modelId.openObject(OdTv::kForWrite);
  if (pModel.isNull())
    return;

  //calculate new coeeficient from device->WCS
  OdGePoint2d pixArea;
  pParentView->getNumPixelsInUnitSquare(m_wcsInsertPoint, pixArea, false);
  double wcsScaleCoef = odmax(pixArea.x, pixArea.y);
  if (wcsScaleCoef < 1.e-10)
    wcsScaleCoef = 1.e-10;

  m_scaleForScaleMatrix = m_wcsScaleCoef / wcsScaleCoef;

  //apply current transform
  applyCurrentTransform();
}


bool OdTvUIAxisControl::hover(int x, int y)
{
  if (m_viewId.isNull())
    return false;

  OdTvGsViewPtr pMoveView = m_viewId.openObject(OdTv::kForWrite);
  OdTvDCPoint pnt = OdTvDCPoint(x, y);

  OdTvSelectionOptions selOpt;
  selOpt.setMode(OdTvSelectionOptions::kPoint);

  //check about something selected
  OdTvSelectionSetPtr pSset = pMoveView->select(&pnt, 1, selOpt, m_modelId);
  
  // hightlight WCS axis
  if (!pSset.isNull() && pSset->numItems() == 1)
  {
    OdTvEntityId selEntity = pSset->getIterator()->getEntity();

    if (selEntity != m_highlightedAxis)
    {
      highlight(m_highlightedAxis, false);
      highlight(selEntity, true);
      m_highlightedAxis = selEntity;
      return true;
    }
  }
  else if (!m_highlightedAxis.isNull())
  {
    highlight(m_highlightedAxis, false);
    m_highlightedAxis.setNull();
    return true;
  }

  return false;
}

void OdTvUIAxisControl::start(int x, int y)
{
  m_xForm = OdTvMatrix::kIdentity;

  if (m_parentViewId.isNull())
  {
    m_basePoint = OdTvPoint::kOrigin;
    return;
  }

  //calculate point in world coordinate
  m_basePoint = toEyeToWorld(x, y);
}

void OdTvUIAxisControl::finish()
{
  m_wcsInsertPoint.transformBy(m_xForm);

  //append last transfrom matrix to the internal entities
  if (!m_modelId.isNull())
  {
    OdTvEntitiesIteratorPtr pEntIter = m_modelId.openObject(OdTv::kForWrite)->getEntitiesIterator();
    while (!pEntIter->done())
    {
      OdTvEntityId entityId = pEntIter->getEntity();
      if (entityId.getType() == OdTvEntityId::kEntity)
      {
        OdTvEntityPtr pEntity = entityId.openObject(OdTv::kForWrite);
        pEntity->appendModelingMatrix(m_xForm);
      }

      pEntIter->step();
    }
  }

  m_basePoint = OdTvPoint::kOrigin;
  m_xForm = OdTvMatrix::kIdentity;

  applyCurrentTransform();
}

bool OdTvUIAxisControl::getTransform(int x, int y, OdTvMatrix& xTrans)
{
  if (m_highlightedAxis.isNull())
    return false;

  OdString name = m_highlightedAxis.openObject()->getName();
  OdTvPoint newPoint = toEyeToWorld(x, y);

  //new full matrix
  OdGeMatrix3d matNewTransform = OdTvMatrix::kIdentity;
  OdTvVector diff = newPoint - m_basePoint;

  if (!name.compare(OD_T("X")))
    matNewTransform(0, 3) = diff.x;
  else if (!name.compare(OD_T("Y")))
    matNewTransform(1, 3) = diff.y;
  else if (!name.compare(OD_T("Z")))
    matNewTransform(2, 3) = diff.z;

  xTrans = m_xForm.inverse();
  xTrans.preMultBy(matNewTransform);

  //remember last full transfrom
  m_xForm = matNewTransform;

  //apply current transform
  applyCurrentTransform();

  return true;
}

//highlight the appropriate axis
void OdTvUIAxisControl::highlight(OdTvEntityId axisId, bool bHighlight)
{
  if (axisId.isNull())
    return;

  //open Entity
  OdTvEntityPtr pAxis = axisId.openObject(OdTv::kForWrite);

  //get xLine
  OdTvGeometryDataIteratorPtr pGeometryIt = pAxis->getGeometryDataIterator();
  if (!pGeometryIt.isNull() && !pGeometryIt->done())
    pGeometryIt->step();

  OdTvGeometryDataId xlineId;
  if (!pGeometryIt->done())
    xlineId = pGeometryIt->getGeometryData();

  OdTvGeometryDataPtr pXLine;
  if (!xlineId.isNull())
    pXLine = xlineId.openObject();

  //perform highlight
  if (bHighlight)
  {
    m_unhighlightedAxisColor = pAxis->getColor();
    pAxis->setColor(OdTvColorDef(255, 128, 0));
    if (!pXLine.isNull())
      pXLine->setVisibility(true);
  }
  else
  {
    pAxis->setColor(m_unhighlightedAxisColor);
    if (!pXLine.isNull())
      pXLine->setVisibility(false);
  }
}

bool OdTvUIAxisControl::constructAxisGeometry(const OdString& name, const OdTvColorDef& color)
{
  OdTvModelPtr pModel = m_modelId.openObject(OdTv::kForWrite);
  if (pModel.isNull())
    return false;

  OdTvGsViewPtr pParentView = m_parentViewId.openObject(OdTv::kForWrite);
  if (pParentView.isNull())
    return false;

  //calculate sizes of the axis in WCS
  OdGePoint2d pixArea;
  pParentView->getNumPixelsInUnitSquare(m_wcsInsertPoint, pixArea, false);
  m_wcsScaleCoef = odmax(pixArea.x, pixArea.y);
  double axisWcsLength =      (DEVICE_AXIS_LENGTH + 70) / m_wcsScaleCoef;
  double axisArrowWcsLength = (DEVICE_AXISARROW_LENGTH + 40) / m_wcsScaleCoef;
  double cylinderRadius =     (DEVICE_AXIS_RADIUS + 10) / m_wcsScaleCoef;

  OdTvPoint startPt = m_wcsInsertPoint;
  OdTvPoint endPt = startPt;
  OdTvPoint lastPt = endPt;

  if (name == OD_T("X"))
  {
    endPt.x += axisWcsLength;
    lastPt.x = endPt.x + axisArrowWcsLength;
  }
  else if (name == OD_T("Y"))
  {
    endPt.y += axisWcsLength;
    lastPt.y = endPt.y + axisArrowWcsLength;
  }
  else if (name == OD_T("Z"))
  {
    endPt.z += axisWcsLength;
    lastPt.z = endPt.z + axisArrowWcsLength;
  }
  else
    return false;

  //create entity with axis
  OdTvEntityId axisId = pModel->appendEntity(name);
  OdTvEntityPtr pAxis = axisId.openObject(OdTv::kForWrite);

  //set color to the entity
  pAxis->setColor(color);

  //create axis as a set of cylinders
  OdTvPointArray vertices;
  vertices.append(startPt);
  vertices.append(endPt);
  vertices.append(endPt);
  vertices.append(lastPt);

  OdDoubleArray radii;
  radii.append(cylinderRadius);
  radii.append(cylinderRadius);
  radii.append(cylinderRadius * DEVICE_AXIS_ARROW_COEFF);
  radii.append(0.);
  pAxis->appendShellFromCylinder(vertices.length(), vertices.asArrayPtr(), radii.length(), radii.asArrayPtr(), OdTvCylinderData::kBoth, 50);

  // add xline
  OdTvGeometryDataId xlineId = pAxis->appendInfiniteLine(startPt, endPt, OdTvInfiniteLineData::kLine);
  OdTvGeometryDataPtr pGeom = xlineId.openObject();
  pGeom->setVisibility(false);
  pGeom->setColor(color);

  return true;
}

OdTvPoint OdTvUIAxisControl::toEyeToWorld(int x, int y) const
{
  //calculate point in world coordinate
  if (m_parentViewId.isNull())
    return OdTvPoint::kOrigin;

  OdTvGsViewPtr pView = m_parentViewId.openObject(OdTv::kForWrite);

  OdGePoint3d wcsPt(x, y, 0.0);
  if (pView->isPerspective())
  {
    wcsPt.z = pView->projectionMatrix()(2, 3);
  }
  wcsPt.transformBy((pView->screenMatrix() * pView->projectionMatrix()).inverse());
  wcsPt.z = 0.;
  // eye CS at this point.

  //transform to world coordinate system
  wcsPt.transformBy(pView->eyeToWorldMatrix());

  return wcsPt;
}

//transfrom + scael
void OdTvUIAxisControl::applyCurrentTransform()
{
  OdTvModelPtr pModel = m_modelId.openObject(OdTv::kForWrite);
  if (pModel.isNull())
    return;

  //calculate scaling matrix
  OdTvMatrix xFullTrans;
  xFullTrans.setToScaling(m_scaleForScaleMatrix, m_wcsInsertPoint);

  //add controller matrix
  xFullTrans.preMultBy(m_xForm);

  //scale the axis model. Here we will not use the fast transfrom since we have xLines and for us it will be usefull
  //if after setting the new transfrom matrix the entities will be regenerated
  pModel->setModelingMatrix(xFullTrans);
}

//***************************************************************************//
// 'OdTvUIRotationAxisControl' methods implementation
//***************************************************************************//

OdTvUIRotationAxisControl::~OdTvUIRotationAxisControl()
{
}

bool OdTvUIRotationAxisControl::attach(const OdTvPoint& wcsPos, const OdTvVector& uAxis, const OdTvVector& vAxis)
{
  m_wcsInsertPoint = wcsPos;
  m_uAxis = uAxis;
  m_vAxis = vAxis;

  if (m_parentViewId.isNull())
    return false;

  OdTvGsViewPtr pParentView = m_parentViewId.openObject(OdTv::kForWrite);

  //get parent device
  OdTvGsDeviceId devId = pParentView->device();
  if (devId.isNull())
    return false;
  OdTvGsDevicePtr pDevice = devId.openObject(OdTv::kForWrite);

  // 1. create or update new view
  if (m_viewId.isNull())
  {
    OdString strAxisViewName = OD_T("$") + pParentView->getName() + OD_T("_AXISCONTROLVIEW");
    m_viewId = pDevice->createView(strAxisViewName, false);

    if (m_viewId.isNull())
      return false;

    // 1.1 add view to the device
    pDevice->addView(m_viewId);

    // 1.2 setup new view
    OdTvGsViewPtr pView = m_viewId.openObject(OdTv::kForWrite);
    pView->setMode(OdTvGsView::kFlatShaded);
    pView->setView(pParentView->position(), pParentView->target(), pParentView->upVector(), pParentView->fieldWidth(), pParentView->fieldHeight(), pParentView->isPerspective() ? OdTvGsView::kPerspective : OdTvGsView::kParallel);

    //add view as sibling (need for the automatic transfer of the main view changes to the control view)
    pParentView->addSibling(m_viewId);
  }
  else
    pDevice->addView(m_viewId);

  // 2. create model or use existing
  if (m_modelId.isNull())
  {
    //generate name for the model
    OdString strWcsModelName = OD_T("$") + pParentView->getName() + OD_T("_AXISCONTROLMODEL");

    //get the database
    OdTvDatabasePtr pTvDb = pDevice->getDatabase().openObject(OdTv::kForWrite);

    // create new model
    m_modelId = pTvDb->createModel(strWcsModelName, OdTvModel::kMain, false);
    if (m_modelId.isNull())
      return false;
  }

  // 2.1 Add model to view
  m_viewId.openObject(OdTv::kForWrite)->addModel(m_modelId);

  m_bIsAttached = true;

  // 3. create geometry
  if (!constructAxisGeometry(OD_T("Origin"), OdTvColorDef(234, 47, 47), uAxis, vAxis))
    return false;

  // create Y axis
  if (!constructAxisGeometry(OD_T("U"), OdTvColorDef(40, 240, 50), uAxis, vAxis))
    return false;

  // create Z axis
  if (!constructAxisGeometry(OD_T("V"), OdTvColorDef(35, 72, 245), uAxis, vAxis))
    return false;

  return true;
}

bool OdTvUIRotationAxisControl::getTransform(int x, int y, OdTvMatrix& xTrans)
{
  if (m_highlightedAxis.isNull())
    return false;

  OdString name = m_highlightedAxis.openObject()->getName();
  OdTvPoint newPoint = toEyeToWorld(x, y);

  //new full matrix
  OdGeMatrix3d matNewTransform = OdTvMatrix::kIdentity;

  OdTvPlane cuttingPlane(m_wcsInsertPoint, m_uAxis, m_vAxis);
  OdTvVector cuttingPlaneNormal = cuttingPlane.normal();

  OdTvGsViewPtr pMoveView = m_viewId.openObject(OdTv::kForWrite);

  // Get transform matrix for cutting plane updating
  OdTvVector offset = newPoint - m_basePoint;
  if (name == OD_T("Origin"))
  {
    double projLength = offset.dotProduct(cuttingPlaneNormal);
    matNewTransform = OdGeMatrix3d::translation(cuttingPlaneNormal*projLength);
  }
  else if (name == OD_T("U"))
  {
    const OdTvVector proj = offset.orthoProject((pMoveView->position() - pMoveView->target()).normal());
    const double dot = -proj.dotProduct(cuttingPlaneNormal);

    matNewTransform = OdGeMatrix3d::rotation(dot / m_dAxisWcsLength, m_vAxis, m_wcsInsertPoint);
  }
  else if (name == OD_T("V"))
  {
    const OdTvVector proj = offset.orthoProject((pMoveView->position() - pMoveView->target()).normal());
    const double dot = proj.dotProduct(cuttingPlaneNormal);

    matNewTransform = OdGeMatrix3d::rotation(dot / m_dAxisWcsLength, m_uAxis, m_wcsInsertPoint);
  }
  else
  {
    return false;
  }

  xTrans = m_xForm.inverse();
  xTrans.preMultBy(matNewTransform);

  //remember last full transfrom
  m_xForm = matNewTransform;

  //apply current transform
  applyCurrentTransform();

  return true;
}

void OdTvUIRotationAxisControl::scale()
{
  OdTvUIAxisControl::scale();

  m_dAxisWcsLength *= m_scaleForScaleMatrix;
}

void OdTvUIRotationAxisControl::unhighlight()
{
  highlight(m_highlightedAxis, false);
  m_highlightedAxis.setNull();
}

void OdTvUIRotationAxisControl::applyTransformToAxis()
{
  m_uAxis.transformBy(m_xForm);
  m_vAxis.transformBy(m_xForm);
}

bool OdTvUIRotationAxisControl::constructAxisGeometry(const OdString& name, const OdTvColorDef& color, const OdTvVector& uAxis, const OdTvVector& vAxis)
{
  OdTvModelPtr pModel = m_modelId.openObject(OdTv::kForWrite);
  if (pModel.isNull())
    return false;

  OdTvGsViewPtr pParentView = m_parentViewId.openObject(OdTv::kForWrite);
  if (pParentView.isNull())
    return false;

  //calculate sizes of the axis in WCS
  OdGePoint2d pixArea;
  pParentView->getNumPixelsInUnitSquare(m_wcsInsertPoint, pixArea, false);
  m_wcsScaleCoef = odmax(pixArea.x, pixArea.y);
  double axisWcsLength = DEVICE_AXIS_LENGTH / m_wcsScaleCoef;
  double cylinderRadius = DEVICE_AXIS_RADIUS / m_wcsScaleCoef;

  m_dAxisWcsLength = axisWcsLength; // TODO remove

  OdTvPoint startPt = m_wcsInsertPoint;
  OdTvPoint endPt = startPt;

  OdTvMatrix transform = OdTvMatrix::kIdentity;
  if (name == OD_T("Origin"))
  {
    cylinderRadius *= DEVICE_ROTATION_ORIGIN_AXIS_COEFF;
  }
  else if (name == OD_T("U"))
  {

    transform.setToTranslation(uAxis * axisWcsLength);
  }
  else if (name == OD_T("V"))
  {
    transform.setToTranslation(vAxis * axisWcsLength);
  }
  else
    return false;

  endPt.transformBy(transform);

  //create entity with axis
  OdTvEntityId axisId = pModel->appendEntity(name);
  OdTvEntityPtr pAxis = axisId.openObject(OdTv::kForWrite);

  //set color to the entity
  pAxis->setColor(color);

  if (name == OD_T("Origin"))
  {
    //create axis as a cylinder
    OdTvGeometryDataId axisGeomId = pAxis->appendShellFromSphere(startPt, cylinderRadius, OdTvVector::kYAxis, OdTvVector::kXAxis, 20);

    // add xline
    OdTvVector dir = uAxis.crossProduct(vAxis); 
    OdTvGeometryDataId xlineId = pAxis->appendInfiniteLine(startPt, startPt + dir, OdTvInfiniteLineData::kLine);
    OdTvGeometryDataPtr pGeom = xlineId.openObject();
    pGeom->setVisibility(false);
    pGeom->setColor(color);
  }
  else
  {
    //create axis as a cylinder
    OdTvGeometryDataId axisGeomId = pAxis->appendShellFromCylinder(startPt, endPt, (DEVICE_ROTATION_AXIS_RADIUS / m_wcsScaleCoef), OdTvCylinderData::kBoth, 50);

    // add xline
    OdTvGeometryDataId xlineId = pAxis->appendCircle(startPt, axisWcsLength, name == OD_T("U") ? vAxis : uAxis);
    OdTvGeometryDataPtr pGeom = xlineId.openObject();
    pGeom->setVisibility(false);
    pGeom->setColor(color);
  }

  return true;
}

