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

#include "TvAndDraggers.h"

#include <cmath>

OdTvViewportParams::OdTvViewportParams() : fieldWidth(1.0), fieldHeight(1.0), projectionType(OdTvGsView::kParallel)
{}

void OdTvViewportParams::store(OdTvGsViewPtr pView)
{
  position = pView->position();
  target = pView->target();
  up = pView->upVector();
  fieldWidth = pView->fieldWidth();
  fieldHeight = pView->fieldHeight();
  projectionType = pView->isPerspective() ? OdTvGsView::kPerspective : OdTvGsView::kParallel;
}

void OdTvViewportParams::setup(OdTvExtendedView* pTvExtendedView) const
{
  pTvExtendedView->setView(position, target, up, fieldWidth, fieldHeight, projectionType);
}

static void orbit(const OdTvViewportParams& params, double xOrbit, double yOrbit, const OdGePoint3d& viewCenter, OdTvExtendedView* pTvExtendedView)
{
  OdTvViewportParams rotatedParams = params;

  // compute camera side vector
  OdGeVector3d side = rotatedParams.up.crossProduct(rotatedParams.target - rotatedParams.position).normalize();
  double angle = sqrt(yOrbit * yOrbit + xOrbit * xOrbit);
  OdGeVector3d axis = (rotatedParams.up * yOrbit - side * xOrbit).normalize();

  rotatedParams.position.rotateBy(angle, axis, viewCenter);
  rotatedParams.target.rotateBy(angle, axis, viewCenter);
  if (yOrbit != 0.0)
  {
    side = side.rotateBy(angle, axis);
  }

  // update up vector
  rotatedParams.up = (rotatedParams.target - rotatedParams.position).crossProduct(side).normalize();

  rotatedParams.setup(pTvExtendedView);
}


static double screenSize(OdTvGsViewPtr pView)
{
  OdTvDCRect viewportRect;
  pView->getViewport(viewportRect);
  OdGePoint2d screenSize(Od_abs(viewportRect.xmax - viewportRect.xmin), Od_abs(viewportRect.ymax - viewportRect.ymin));
  return odmax(screenSize.x, screenSize.y);
}

////////////////////////////////////////////
////// TvAndBaseDragger implementation ///////
////////////////////////////////////////////

eDraggerResult TvAndBaseDragger::drag(int x, int y)
{
    if (!m_bFixedFrameRateEnabled && m_pGlobalParams && m_pGlobalParams->getFixedFrameRate())
    {
        OdTvGsViewPtr pView = getActiveTvViewPtr();
        if (!pView.isNull())
        {
            if (pView->isInInteractivity())
                pView->endInteractivity();
            pView->beginInteractivity(m_pGlobalParams->getFpsValue());
            m_bFixedFrameRateEnabled = true;
        }
    }
    return kNothingToDo;
}

eDraggerResult TvAndBaseDragger::nextpointup(int x, int y)
{
    if (m_bFixedFrameRateEnabled && m_pGlobalParams && m_pGlobalParams->getFixedFrameRate())
    {
        OdTvGsViewPtr pView = getActiveTvViewPtr();
        if (!pView.isNull() && pView->isInInteractivity())
        {
            pView->endInteractivity();
            m_bFixedFrameRateEnabled = false;
            if (!m_TvDeviceId.isNull())
            {
                OdTvGsDevicePtr pDev = m_TvDeviceId.openObject(OdTv::kForWrite);
                pDev->invalidate();
                pDev->update();
            }
        }
    }
    return kNothingToDo;
}

////////////////////////////////////////////
////// TvAndPanDragger implementation ////////
////////////////////////////////////////////

eDraggerResult TvAndPanDragger::start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView *pExtendedView)
{
    return OdTvDragger::start(pPrevDragger, pExtendedView);
}

eDraggerResult TvAndPanDragger::nextpoint(int x, int y)
{
    if ( m_state == kWaiting )
        return kNothingToDo;
    
    OdTvGsViewPtr pView = getActiveTvViewPtr();
    if ( pView.isNull() )
        return kNothingToDo;
    
    // remember camera current position
    m_pos = pView->position();
    
    // remember the difference between click point in WCS and camera current position
    m_prevPt = toEyeToWorld(x, y) - m_pos.asVector();
    
    return kNothingToDo;
}

eDraggerResult TvAndPanDragger::drag(int x, int y)
{
    if ( m_state == kWaiting )
        return kNothingToDo;
    
    OdTvGsViewPtr pView = getActiveTvViewPtr();
    if ( pView.isNull() )
        return kNothingToDo;
    
    // enable frame rate, if need
    TvAndBaseDragger::drag(x, y);
    
    // calculate click point in WCS
    OdGePoint3d pt = toEyeToWorld(x, y);
    
    //obtain delta for dolly
    OdGeVector3d delta = (m_prevPt - (pt - m_pos)).asVector();
    
    // transform delta to eye
    delta.transformBy(pView->viewingMatrix());
    
    // perform camera moving
    pView->dolly(delta.x, delta.y, delta.z);
    
    // remember the difference between click point in WCS and camera previous position
    m_prevPt = pt - m_pos.asVector();
    
    // remember camera current position
    m_pos = pView->position();
    
    return kNeedUpdateView;
}

eDraggerResult TvAndPanDragger::nextpointup(int x, int y)
{
    // off fixed frame rate mode
    TvAndBaseDragger::nextpointup(x, y);
    return reset();
}


////////////////////////////////////////////
///// TvAndOrbitDragger implementation ///////
////////////////////////////////////////////
TvAndOrbitDragger::TvAndOrbitDragger(OdTvGsDeviceId &tvDeviceId, OdTvModelId &tvDraggersModelId, TvAndGlobalParameters* pParams)
: TvAndBaseDragger (tvDeviceId, tvDraggersModelId, pParams)
{
}

eDraggerResult TvAndOrbitDragger::start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView *pExtendedView)
{
    return  OdTvDragger::start(pPrevDragger, pExtendedView);
}

eDraggerResult TvAndOrbitDragger::nextpoint(int x, int y)
{
    if ( m_state == kWaiting )
        return kNothingToDo;
    
    OdTvGsViewPtr pView = getActiveTvViewPtr();
    if ( pView.isNull() )
        return kNothingToDo;

    m_viewportParams.store(pView);
    m_startCursorPosition = OdTvDCPoint(x, y);

    if (m_pTvExtendedView)
    {
        OdGeBoundBlock3d lastExt;
        if (pView->getLastViewExtents(lastExt))
            m_pTvExtendedView->setViewExtentsForCaching(&lastExt);
    }
    
    return kNothingToDo;
}

eDraggerResult TvAndOrbitDragger::drag(int x, int y)
{
    if ( m_state == kWaiting )
        return kNothingToDo;
    
    OdTvGsViewPtr pView = getActiveTvViewPtr();
    if ( pView.isNull() )
        return kNothingToDo;
    
    // enable frame rate, if need
    TvAndBaseDragger::drag(x, y);

    double size = screenSize(pView);
    m_viewportParams.setup(m_pTvExtendedView);

    // calculate the angles for the rotation about appropriate axes
    double distX = (m_startCursorPosition.x - x) * OdaPI / size;
    double distY = (m_startCursorPosition.y - y) * OdaPI / size;

    // perform camera orbiting
    double xOrbit = distY;
    double yOrbit = distX;
    if (xOrbit != 0.0 || yOrbit != 0.0)
    {
      OdGeBoundBlock3d lastExt;
      m_pTvExtendedView->getCachedExtents(lastExt);
      orbit(m_viewportParams, xOrbit, yOrbit, lastExt.center(), m_pTvExtendedView);
    }
    
    return kNeedUpdateView;
}

eDraggerResult TvAndOrbitDragger::nextpointup(int x, int y)
{
    // off fixed frame rate mode
    TvAndBaseDragger::nextpointup(x, y);
    return reset();
}

////////////////////////////////////////////
/// TvAndZoomWindowDragger implementation ////
////////////////////////////////////////////
TvAndZoomWindowDragger::TvAndZoomWindowDragger(OdTvGsDeviceId &tvDeviceId, OdTvModelId &tvDraggersModelId, TvAndCore *pCore, TvAndGlobalParameters* pParams)
: TvAndBaseDragger (tvDeviceId, tvDraggersModelId, pParams)
{
    m_bJustCreatedObject = true;
    m_pts.resize(4);
    m_bHaveDrawableTemporaryGeometry = true;
    m_bNeedFreeDrag = true;
    m_pTvAndCore = pCore;
}

eDraggerResult TvAndZoomWindowDragger::start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView *pExtendedView)
{
    eDraggerResult rc = kNothingToDo;
    
    // create temporary geometry
    if (!m_bJustCreatedObject)
    {
        updateFrame(true);
        rc = kNeedUpdateView;
    }
    
    // add draggers model to the view
    addDraggersModelToView();
    
    rc = rc | OdTvDragger::start(pPrevDragger, pExtendedView);
    
    if (!m_bJustCreatedObject)
        m_state = kWorking;
    
    m_bJustCreatedObject = false;
    
    return rc;
}

eDraggerResult TvAndZoomWindowDragger::nextpoint(int x, int y)
{
    CHECK_DRAGGER
    
    // remember first click
    m_firstPt = toEyeToWorld(x, y);
    m_firstPt_device = OdGePoint2d(x, y);
    
    if(!m_entityId.isNull())
        m_entityId.openObject(OdTv::kForWrite)->setVisibility(true);
    
    return kNothingToDo;
}

eDraggerResult TvAndZoomWindowDragger::drag(int x, int y)
{
    CHECK_DRAGGER
    
    //get current drag point
    m_lastDragPt = toEyeToWorld(x, y);
    
    // create temporary geometry if need or update
    OdTvEntityPtr entityPtr = m_entityId.openObject(OdTv::kForWrite);
    updateFrame(entityPtr.isNull());
    
    return kNeedUpdateView;
}

eDraggerResult TvAndZoomWindowDragger::nextpointup(int x, int y)
{
    // perform zooming
    OdGePoint2d lowerLeft, upperRight;
    
    lowerLeft.x = odmin(m_firstPt_device.x, x);
    lowerLeft.y = odmin(m_firstPt_device.y, y);
    upperRight.x = odmax(m_firstPt_device.x, x);
    upperRight.y = odmax(m_firstPt_device.y, y);
    
    // perform action
    if (m_pTvExtendedView)
    {
        //perform zooming
        m_pTvExtendedView->zoomToWindow(lowerLeft, upperRight);
        
        if(!m_entityId.isNull())
            m_entityId.openObject(OdTv::kForWrite)->setVisibility(false);
        
        //check existence of the animation
        OdTvAnimation* pAnimation = m_pTvExtendedView->getAnimation();
        m_pTvAndCore->setAnimation(pAnimation);
        if (pAnimation)
        {
            pAnimation->start();
            if (m_pGlobalParams && m_pGlobalParams->getFixedFrameRate())
            {
                OdTvGsViewPtr pView = getActiveTvViewPtr();
                if (!pView.isNull() && !pView->isInInteractivity())
                    pView->beginInteractivity(m_pGlobalParams->getFpsValue());
            }

            return kNeedFinishDragger | kNeedUpdateView;
        }
    }
    
    return kNeedFinishDragger;
}

OdTvDraggerPtr TvAndZoomWindowDragger::finish(eDraggerResult &rc)
{
    // remove the draggers model from the view
    removeDraggersModelFromView();
    
    return OdTvDragger::finish(rc);
}

float getHueFromRGB(float fR, float fG, float fB) {
  float fCMax = fmax(fmax(fR, fG), fB);
  float fCMin = fmin(fmin(fR, fG), fB);
  float fDelta = fCMax - fCMin;

  float fH, fS, fV;
  
  if(fDelta > 0) {
    if(fCMax == fR) {
      fH = 60 * (fmod(((fG - fB) / fDelta), 6));
    } else if(fCMax == fG) {
      fH = 60 * (((fB - fR) / fDelta) + 2);
    } else if(fCMax == fB) {
      fH = 60 * (((fR - fG) / fDelta) + 4);
    }
    
    if(fCMax > 0) {
      fS = fDelta / fCMax;
    } else {
      fS = 0;
    }
    
    fV = fCMax;
  } else {
    fH = 0;
    fS = 0;
    fV = fCMax;
  }
  
  if(fH < 0) {
    fH = 360 + fH;
  }

  return fH;
}

void TvAndZoomWindowDragger::updateFrame(bool bCreate)
{
    OdTvGsViewPtr pView = getActiveTvViewPtr();
    if ( pView.isNull() )
        return;
    
    m_pts[0] = m_firstPt;
    m_pts[2] = m_lastDragPt;
    
    OdGeMatrix3d x = pView->viewingMatrix();
    OdGePoint3d p0 = x * m_pts[0];
    OdGePoint3d p2 = x * m_pts[2];
    
    m_pts[1].x = p0.x;
    m_pts[3].x = p2.x;
    m_pts[1].y = p2.y;
    m_pts[3].y = p0.y;
    m_pts[1].z = m_pts[3].z = p2.z;
    
    x = pView->eyeToWorldMatrix();
    m_pts[1].transformBy(x);
    m_pts[3].transformBy(x);
    
    //update or create entity
    if ( bCreate )
    {
        OdTvModelPtr modelPtr = m_tvDraggersModelId.openObject(OdTv::kForWrite);
        m_entityId = modelPtr->appendEntity();
        {
            OdTvEntityPtr entityNewPtr = m_entityId.openObject(OdTv::kForWrite);
            
            //create frame
            m_frameId = entityNewPtr->appendPolygon(m_pts);
            
            ODCOLORREF bgColor = m_TvDeviceId.openObject()->getBackgroundColor();
            OdUInt8 r = 255, g = 255, b = 255;
            if( getHueFromRGB(ODGETRED(bgColor) / 255, ODGETGREEN(bgColor) / 255, ODGETBLUE(bgColor) / 255) > 180 )
            {
                r = 0; g = 0; b = 0;
            }
            entityNewPtr->setColor(OdTvColorDef(r, g, b));
            entityNewPtr->setLineWeight(2);
        }
    }
    else
    {
        OdTvGeometryDataPtr framePtr = m_frameId.openObject();
        if ( framePtr.isNull() || framePtr->getType() != OdTv::kPolygon )
            return;
        
        OdTvPolygonDataPtr polygonPtr = framePtr->getAsPolygon();
        if ( !polygonPtr.isNull() )
            polygonPtr->setPoints(m_pts);
    }
    
    return;
}

////////////////////////////////////////////
/// TvAndCuttingPlaneDragger implementation //
////////////////////////////////////////////

TvAndCuttingPlaneDragger::TvAndCuttingPlaneDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvDraggersModelId, TvAndGlobalParameters* pParams, TvAndCore* pCore)
: TvAndBaseDragger(tvDeviceId, tvDraggersModelId, pParams)
, m_state(kWaitingForCutPlSelect)
, m_bCanFinish(false)
{
    m_pCore = pCore;
    
    m_SelectionOptions.setMode(OdTvSelectionOptions::kPoint);
    
    m_cuttingPlanesViewId = pCore->getCuttingPlanesViewId();
    m_cuttingPlanesModelId = pCore->getCuttingPlanesModelId();
    
    //inti axis control
    OdTvGsViewId pActiveTvViewId = pCore->getActiveTvViewId();
    m_axisControl.init(pActiveTvViewId);
    
    m_bNeedFreeDrag = true;
}

TvAndCuttingPlaneDragger::~TvAndCuttingPlaneDragger()
{
}

void TvAndCuttingPlaneDragger::onCuttingPlaneAdded(OdTvEntityId entId)
{
    OdTvEntityPtr pEntity = entId.openObject();
    if (!pEntity.isNull())
    {
        OdTvGsViewIdsArray pViews = pEntity->getViewDependencies();
        if (pViews.contains(m_cuttingPlanesViewId))
        {
            OdTvByteUserData *pUserData = dynamic_cast<OdTvByteUserData*>(pEntity->getUserData(m_pCore->getAppRegId()));
            if (pUserData)
            {
                OdUInt32* pData = (OdUInt32*)pUserData->getData();
                m_cuttingPlanes.insert(std::pair<OdTvEntityId, OdUInt32>(entId, *pData));
            }
        }
    }
}

void TvAndCuttingPlaneDragger::onRemoveCuttingPlanes()
{
    //clear entities map
    m_cuttingPlanes.clear();
    
    //for reset some internal fields
    processEscape();
}

eDraggerResult TvAndCuttingPlaneDragger::start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView* pExtendedView)
{
    m_state = kWaitingForCutPlSelect;
    
    //fill map with entities used for the visualization of the cutting planes
    if (!m_cuttingPlanesModelId.isNull())
    {
        OdTvModelPtr pModel = m_cuttingPlanesModelId.openObject(OdTv::kForWrite);
        if (!pModel.isNull())
        {
            OdTvEntitiesIteratorPtr pIt = pModel->getEntitiesIterator();
            while (!pIt->done())
            {
                OdTvEntityId entId = pIt->getEntity();
                onCuttingPlaneAdded(entId);
                pIt->step();
            }
        }
    }
    
    return kNeedUpdateView | OdTvDragger::start(pPrevDragger, pExtendedView);
}

eDraggerResult TvAndCuttingPlaneDragger::nextpoint(int x, int y)
{
    eDraggerResult rc = kNothingToDo;
    
    //first of all we need the active view to perform selection
    OdTvGsViewPtr pView = m_cuttingPlanesViewId.openObject();
    
    if (pView.isNull())
        return kNothingToDo;
    
    if (m_state == kWaitingForCutPlSelect)
    {
        //perform selection
        OdTvDCPoint pt[2];
        
        // prepare data for the selection call
        pt[0].x = x;
        pt[0].y = y;
        
        //perform selection
        OdTvSelectionSetPtr pSSet = pView->select(&pt[0], 1, m_SelectionOptions, m_cuttingPlanesModelId);
        
        //check selection results
        if (!pSSet.isNull() && pSSet->numItems() != 0)
        {
            // merge new selection set with current
            merge(pSSet);
            
            //call window update
            rc = kNeedUpdateView;
        }
    }
    else if (m_state == kWaitingForAxisControlSelect)
    {
        // unselection if tap in empty area
        OdTvDCPoint pt[2];
        pt[0].x = x;
        pt[0].y = y;
        OdTvSelectionSetPtr pSSet = pView->select(&pt[0], 1, m_SelectionOptions, m_cuttingPlanesModelId);
        if(pSSet.isNull() || pSSet->numItems() == 0)
            processEscape();
        
        if (m_axisControl.isAttached())
        {
            if (m_axisControl.hover(x, y))
                rc = kNeedUpdateView;
        }
        
        if (m_axisControl.isAttached() && m_axisControl.hasSelectedControl())
        {
            m_axisControl.start(x, y);
            m_state = kCuttingPlaneRotation;
            rc = kNeedUpdateView;
        }
    }
    else
        rc = kNeedUpdateView;
    
    return rc;
}

eDraggerResult TvAndCuttingPlaneDragger::drag(int x, int y)
{
    if (m_state == kWaitingForCutPlSelect)
    {
        //first of all we need the active view to perform selection
        OdTvGsViewPtr pView = m_cuttingPlanesViewId.openObject();
        
        if (pView.isNull())
            return kNothingToDo;
        
        //highlight the cutting plane
        OdTvSelectionOptions selOpt;
        selOpt.setMode(OdTvSelectionOptions::kPoint);
        OdTvDCPoint pnt = OdTvDCPoint(x, y);
        
        //check about something selected
        OdTvSelectionSetPtr pSSet = pView->select(&pnt, 1, m_SelectionOptions, m_cuttingPlanesModelId);
        
        // hightlight
        if (!pSSet.isNull() && pSSet->numItems() == 1)
        {
            OdTvEntityId selEntity = pSSet->getIterator()->getEntity();
            
            if (selEntity != m_highlightedCuttingPlaneId)
            {
                highlight(m_highlightedCuttingPlaneId, false);
                highlight(selEntity, true);
                m_highlightedCuttingPlaneId = selEntity;
                return kNeedUpdateView;
            }
        }
        else if (!m_highlightedCuttingPlaneId.isNull())
        {
            highlight(m_highlightedCuttingPlaneId, false);
            m_highlightedCuttingPlaneId.setNull();
            return kNeedUpdateView;
        }
        
        return kNothingToDo;
    }
    else if (m_state == kWaitingForAxisControlSelect)
    {
        if (m_axisControl.isAttached())
        {
            if (m_axisControl.hover(x, y))
                return kNeedUpdateView;
        }
        
        return kNothingToDo;
    }
    else if (m_state == kCuttingPlaneRotation)
    {
        OdUInt32 index = m_cuttingPlanes.at(m_selectedCuttingPlaneEntityId);
        OdTvGsViewPtr pActiveView = getActiveTvViewPtr();
        if (pActiveView.isNull())
            return kNothingToDo;
        
        OdTvPlane cuttingPlane;
        OdTvResult res = pActiveView->getCuttingPlane(index, cuttingPlane);
        if (res != tvOk)
            return kNothingToDo;
        
        OdTvPoint origin;
        OdTvVector u, v;
        cuttingPlane.get(origin, u, v);
        
        OdTvMatrix transform;
        if (!m_axisControl.getTransform(x, y, transform))
            return kNothingToDo;
        
        origin.transformBy(transform);
        u.transformBy(transform);
        v.transformBy(transform);
        
        // Update cutting plane
        cuttingPlane.set(origin, u, v);
        pActiveView->updateCuttingPlane(index, cuttingPlane);
        
        OdTvGsDevicePtr pDevice = pActiveView->device().openObject();
        if (!pDevice.isNull())
            pDevice->invalidate();
        
        // Update cutting plane geometry
        m_selectedCuttingPlaneEntityId.openObject(OdTv::kForWrite)->appendModelingMatrix(transform);
    }
    
    return kNeedUpdateView;
}

eDraggerResult TvAndCuttingPlaneDragger::processEscape()
{
    m_state = kWaitingForCutPlSelect;
    
    m_axisControl.unhighlight();
    m_axisControl.detach();
    
    // Reset cutting plane color
    if (!m_selectedCuttingPlaneEntityId.isNull())
    {
        OdTvEntityPtr pSelectedCuttingPlaneEntity = m_selectedCuttingPlaneEntityId.openObject(OdTv::kForWrite);
        pSelectedCuttingPlaneEntity->setColor(OdTvColorDef(175, 175, 175));
        pSelectedCuttingPlaneEntity->setLineWeight(OD_TV_CUTTINGPLANE_EDGE_DEFAULT_LINEWEIGHT);
    }
    
    // Unselect cutting plane
    m_selectedCuttingPlaneEntityId.setNull();
    
    return kNeedUpdateView;
}

eDraggerResult TvAndCuttingPlaneDragger::processDelete()
{
    removeSelectedCuttingPlane();
    
    return kNeedUpdateView;
}

eDraggerResult TvAndCuttingPlaneDragger::nextpointup(int x, int y)
{
    eDraggerResult res = kNothingToDo;
    
    if (m_state == kCuttingPlaneRotation)
    {
        if (m_axisControl.isAttached())
        {
            m_axisControl.applyTransformToAxis();
            m_axisControl.finish();
            if (m_axisControl.hover(x, y))
                res = kNeedUpdateView;
        }
        
        m_state = kWaitingForAxisControlSelect;
    }
    
    return res;
}

bool TvAndCuttingPlaneDragger::canFinish()
{
    if (m_bCanFinish)
    {
        m_bCanFinish = false;
        return true;
    }
    
    return m_bCanFinish;
}

OdTvDraggerPtr TvAndCuttingPlaneDragger::finish(eDraggerResult& rc)
{
    //reset some data
    processEscape();
    
    //reset highlight
    if (!m_highlightedCuttingPlaneId.isNull())
    {
        highlight(m_highlightedCuttingPlaneId, false);
        m_highlightedCuttingPlaneId.setNull();
    }
    
    return OdTvDragger::finish(rc);
}

void TvAndCuttingPlaneDragger::notifyAboutViewChange(eDraggerViewChangeType notify)
{
//    if (!m_axisControl.isAttached())
//        return;
//
//    if (notify & kViewChangeFull || notify & kViewChangeZoom)
//        m_axisControl.scale();
}

void TvAndCuttingPlaneDragger::merge(const OdTvSelectionSetPtr& pSSet)
{
    OdTvSelectionSetIteratorPtr pSelectIter = pSSet->getIterator();
    if (!pSelectIter->done())
    {
        if (m_state == kWaitingForCutPlSelect) // Create axis control for selected cutting plane
        {
            m_selectedCuttingPlaneEntityId = pSelectIter->getEntity();
            if (!m_selectedCuttingPlaneEntityId.isNull())
            {
                OdUInt32 cuttingPlaneIndex = m_cuttingPlanes.at(m_selectedCuttingPlaneEntityId);
                
                //reset highlight
                if (!m_highlightedCuttingPlaneId.isNull())
                {
                    highlight(m_highlightedCuttingPlaneId, false);
                    m_highlightedCuttingPlaneId.setNull();
                }
                
                // Change color
                OdTvEntityPtr pSelectedCuttingPlaneEntity = m_selectedCuttingPlaneEntityId.openObject(OdTv::kForWrite);
                pSelectedCuttingPlaneEntity->setColor(OdTvColorDef(255, 0, 0));
                pSelectedCuttingPlaneEntity->setLineWeight(OD_TV_CUTTINGPLANE_EDGE_SELECTED_LINEWEIGHT);
                
                OdTvPlane cuttingPlane;
                if (getActiveTvViewPtr()->getCuttingPlane(cuttingPlaneIndex, cuttingPlane) != tvOk)
                    return;
                
                OdTvPoint origin;
                OdTvVector u, v;
                cuttingPlane.get(origin, u, v);
                
                // Draw wcs
                m_axisControl.attach(origin, u, v);
                notifyAboutViewChange(kViewChangeZoom);
                
                // Now wait for wcs axis selection or cutting plane selection for moving
                m_state = kWaitingForAxisControlSelect;
                m_bNeedFreeDrag = true;
            }
        }
    }
}

void TvAndCuttingPlaneDragger::removeSelectedCuttingPlane()
{
    if (m_selectedCuttingPlaneEntityId.isNull())
        return;
    
    OdUInt32 index = m_cuttingPlanes.at(m_selectedCuttingPlaneEntityId);
    
    OdTvGsViewPtr pActiveView = m_pCore->getActiveTvViewPtr();
    if (!pActiveView.isNull())
        pActiveView->removeCuttingPlane(index);
    
    // Change cutting planes indexes
    std::map<OdTvEntityId, OdUInt32>::iterator iter = m_cuttingPlanes.find(m_selectedCuttingPlaneEntityId);
    if (iter != m_cuttingPlanes.end())
        m_cuttingPlanes.erase(iter);
    
    iter = m_cuttingPlanes.begin();
    while (iter != m_cuttingPlanes.end())
    {
        if (iter->second > index)
            iter->second--;
        
        iter++;
    }
    
    //notify rendering area about deleting of the cutting plane
    m_pCore->onRemoveCuttingPlane(m_selectedCuttingPlaneEntityId);
    
    //reset selected geometry
    m_selectedCuttingPlaneEntityId = OdTvEntityId();
    
    //reset a few parameters
    processEscape();
}

//highlight the appropriate cutting plane
void TvAndCuttingPlaneDragger::highlight(const OdTvEntityId& planeId, bool bHighlight)
{
    if (planeId.isNull())
        return;
    
    //open Entity
    OdTvEntityPtr pPlane = planeId.openObject(OdTv::kForWrite);
    
    //perform highlight
    if (bHighlight)
    {
        pPlane->setColor(OdTvColorDef(255, 128, 0));
        pPlane->setLineWeight(OD_TV_CUTTINGPLANE_EDGE_SELECTED_LINEWEIGHT);
    }
    else
    {
        pPlane->setColor(OdTvColorDef(175, 175, 175));
        pPlane->setLineWeight(OD_TV_CUTTINGPLANE_EDGE_DEFAULT_LINEWEIGHT);
    }
}

////////////////////////////////////////////
//// TvAndSelectionDragger implementation ////
////////////////////////////////////////////

#define OD_TV_SELECTOR_VIEW          OD_T("$ODA_TVVIEWER_SELECTORVIEW%d")
#define OD_TV_SELECTOR_LINETYPE      OD_T("$ODA_TVVIEWER_SELECTORLINETYPE")
#define OD_TV_COLLIDE_MODEL          OD_T("$ODA_TVVIEWER_COLLIDEMODEL")

TvAndSelectionDragger::TvAndSelectionDragger(OdTvGsDeviceId &tvDeviceId, OdTvModelId &tvModelId, OdTvModelId &tvDraggersModelId, TvAndGlobalParameters *pParams, TvAndCore *pCore)
 : TvAndBaseDragger(tvDeviceId, tvDraggersModelId, pParams)
, m_modelId(tvModelId)
, m_pCore(pCore)
, m_localstate(kPoint)
{
    OdTvGsDevicePtr pDevice = m_TvDeviceId.openObject(OdTv::kForWrite);
    static int sequenceNumber = 1;
    // Create view name
    OdString strViewName;
    strViewName.format(OD_TV_SELECTOR_VIEW, sequenceNumber++);
    
    m_tempViewId = pDevice->createView(strViewName, false);
    
    // Get specific linetype for the selection rectangle boundary
    OdTvDatabaseId dbId = m_modelId.openObject()->getDatabase();
    m_frameLinetypeId = dbId.openObject()->findLinetype(OD_TV_SELECTOR_LINETYPE);
    if (m_frameLinetypeId.isNull())
    {
        // Create custom linetype for the selection rectangle boundary
        OdTvLinetypeDashElementPtr pDash = OdTvLinetypeDashElement::createObject();
        pDash->setSize(0.25);
        
        OdTvLinetypeSpaceElementPtr pSpace = OdTvLinetypeSpaceElement::createObject();
        pSpace->setSize(0.25);
        
        OdTvLinetypeElementArray lparray;
        lparray.push_back(pDash);
        lparray.push_back(pSpace);
        m_frameLinetypeId = dbId.openObject(OdTv::kForWrite)->createLinetype(OD_TV_SELECTOR_LINETYPE, lparray);
    }
    
    m_frameLinetypeId.openObject(OdTv::kForWrite)->setScaledToFit(true);
}

TvAndSelectionDragger::~TvAndSelectionDragger()
{}

eDraggerResult TvAndSelectionDragger::start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView *pExtendedView)
{
    return OdTvDragger::start(pPrevDragger, pExtendedView);
}

eDraggerResult TvAndSelectionDragger::nextpoint(int x, int y)
{
    eDraggerResult rc = kNothingToDo;
    
    //first of all we need the active view to perform selection
    OdTvGsViewPtr pView = getActiveTvViewPtr();
    
    if (pView.isNull())
        return kNothingToDo;
    
    //perform selection
    OdTvDCPoint pt[2];
    if (m_localstate == kPoint)
    {
        //remember first click
        m_firstDevicePt.x = x;
        m_firstDevicePt.y = y;
        
        m_SelectionOptions.setMode(OdTvSelectionOptions::kPoint);
    }
    
    // prepare data for the selection call
    pt[0].x = m_firstDevicePt.x;
    pt[0].y = m_firstDevicePt.y;
    
    int nPoints = 1;
    if (m_localstate != kPoint)
        nPoints = 2;
    
    OdTvSelectionSetPtr pSSet = pView->select(&pt[0], nPoints, m_SelectionOptions, m_modelId);
    
    //check selection results
    if (m_localstate != kPoint)
        m_localstate = kPoint;
    
    if (!pSSet.isNull() && pSSet->numItems() != 0)
    {
        // merge new selection set with current
        merge(pSSet);
        
        //call window update
        rc = kNeedUpdateView;
    }
    
    return rc;
}

eDraggerResult TvAndSelectionDragger::drag(int x, int y)
{
    return kNothingToDo;
}

eDraggerResult TvAndSelectionDragger::processEscape()
{
    if (m_localstate != kPoint)
        return kNothingToDo;
    
    //remove current selection set
    m_pSSet.release();
    
    return kNeedUpdateView;
}

void TvAndSelectionDragger::merge(const OdTvSelectionSetPtr &pSSet)
{
    if (pSSet.isNull())
        return;
    
    //remove current selection set
    if(!m_pSSet.isNull())
        m_pSSet.release();
    
    // If 'ctrl' button is not pressed, remove old selection set and disabling highlighting
    if (m_pSSet.isNull())
    {
        m_pSSet = pSSet;
        highlight(m_pSSet, true);
    }
}

void TvAndSelectionDragger::highlight(const OdTvSelectionSetPtr &pSSet, bool bDoIt) const
{
    if (pSSet.isNull())
        return;
    
    OdTvSelectionSetIteratorPtr pIter = pSSet->getIterator();
    for (; !pIter->done(); pIter->step())
    {
        highlight(pIter, bDoIt);
    }
}

void TvAndSelectionDragger::highlight(const OdTvSelectionSetIteratorPtr &pIter, bool bDoIt) const
{
    OdTvGsViewPtr pView = getActiveTvViewPtr();
    if (pView.isNull())
        return;
    
    //get entity
    OdTvEntityId id = pIter->getEntity();
    if (id.isNull())
        return;
    
    //get sub item
    OdTvSubItemPath path;
    pIter->getPath(path);
    //perform highlight
    pView->highlight(id, path, bDoIt);
}

////////////////////////////////////////////
///// TvAndCollideDragger implementation /////
////////////////////////////////////////////


TvAndCollideDragger::TvAndCollideDragger(OdTvGsDeviceId &tvDeviceId, OdTvModelId &tvModelId, OdTvModelId &tvDraggersModelId, TvAndGlobalParameters *pParams, TvAndCore *pCore)
 : TvAndSelectionDragger(tvDeviceId, tvModelId, tvDraggersModelId, pParams, pCore)
, m_collideDraggerState(kSelection)
{
    m_bNeedFreeDrag = true;
    m_bNeedUnhighlight = true;
    
    //redefine the UCS
    m_yAxis = OdTvVector::kZAxis;
    
    OdTvDatabaseId dbId = tvModelId.openObject()->getDatabase();
    m_tvDraggersModelId = dbId.openObject(OdTv::kForWrite)->createModel(OD_TV_COLLIDE_MODEL, OdTvModel::kMain, false);
    
    //inti axis control
    OdTvGsViewId pActiveTvViewId = pCore->getActiveTvViewId();
    m_axisControl.init(pActiveTvViewId);
}

TvAndCollideDragger::~TvAndCollideDragger()
{
    //remove some data
    processEscape();
    
    if (!m_tvDraggersModelId.isNull())
    {
        OdTvModelPtr pModel = m_tvDraggersModelId.openObject();
        if (!pModel.isNull())
        {
            OdTvDatabaseId dbId = pModel->getDatabase();
            {
                dbId.openObject(OdTv::kForWrite)->removeModel(m_tvDraggersModelId);
            }
        }
    }
    
    // update device
    if(m_pCore)
    {
        m_pCore->update();
    }
}

eDraggerResult TvAndCollideDragger::processEnter()
{
    if (!m_pCollisionSSet.isNull())
        return kNothingToDo;
    //create selection set
    m_pCollisionSSet = OdTvSelectionSet::createObject(m_SelectionOptions);
    
    // Create entity for selected geometry
    OdTvModelPtr pDraggerModel = m_tvDraggersModelId.openObject(OdTv::kForWrite);
    OdTvEntityId collisionEntityId = pDraggerModel->appendEntity(OD_T("TempCollideModel"));
    
    if (m_collideDraggerState == kSelection)
    {
        OdTvSelectionSetPtr pSSet = getSelectionSet();
        if (pSSet.isNull())
            return kNothingToDo;
        OdTvSelectionSetIteratorPtr pSSetIter = pSSet->getIterator();
        
        OdTvExtents3d sSetExt;    //here we will try to collect all extents (now for the entities only)
        while (!pSSetIter->done())
        {
            OdTvEntityIdsArray entitiesArray;
            OdTvGeometryDataIdsArray geometriesDataArray;
            OdTvSubGeometryId subGeometryIdObj;
            
            OdTvGeometryDataId geometryDataId = pSSetIter->getGeometryData();
            OdTvGeometryDataId subEntityId = pSSetIter->getSubEntity();
            OdTvEntityId entityId = pSSetIter->getEntity();
            
            if (!geometryDataId.isNull())
            {
                OdTvGeometryDataPtr pGeometryDataPtr = geometryDataId.openObject();
                OdTvGeometryDataId copyedGeometryDataId = pGeometryDataPtr->copyTo(collisionEntityId);
                
                entitiesArray.append(collisionEntityId);
                geometriesDataArray.append(copyedGeometryDataId);
                
                pGeometryDataPtr->setTransparency(0.75);
                m_baseGeometries.push_back(geometryDataId);
                
                OdTvSubItemPath path(entitiesArray, geometriesDataArray, subGeometryIdObj);
                m_pCollisionSSet->appendSubEntity(collisionEntityId, path);
            }
            else if (!subEntityId.isNull()) //currently we can't go here
            {
                OdTvGeometryDataPtr pGeometryDataPtr = subEntityId.openObject();
                OdTvGeometryDataId copyedSubEntityId = pGeometryDataPtr->copyTo(collisionEntityId);
                
                entitiesArray.append(collisionEntityId);
                geometriesDataArray.append(copyedSubEntityId);
                
                OdTvSubItemPath path(entitiesArray, geometriesDataArray, subGeometryIdObj);
                m_pCollisionSSet->appendSubEntity(collisionEntityId, path);
            }
            else if (!entityId.isNull())
            {
                if (entityId.getType() == OdTvEntityId::kEntity)
                {
                    OdTvEntityPtr pEntity = entityId.openObject();
                    
                    //get entity extents
                    OdTvExtents3d entityExt;
                    pEntity->getExtents(entityExt, OdTv::kView);
                    if (entityExt.isValidExtents())
                        sSetExt.addExt(entityExt);
                    
                    // Create entity for selected entity copying
                    OdTvEntityId entityCopyId = pDraggerModel->appendEntity(pEntity->getName() + OD_T("_copy"));
                    
                    pEntity->copyTo(entityCopyId);
                    
                    pEntity->setTransparency(0.75);
                    m_baseEntities.push_back(entityId);
                    
                    m_pCollisionSSet->appendEntity(entityCopyId);
                }
            }
            
            pSSetIter->step();
        }
        
        m_collideDraggerState = kBasePointWaiting;
        
        //calculate insert point for the axis control
        OdTvPoint insertPos(0., 0., 0.);
        if (sSetExt.isValidExtents())
            insertPos = sSetExt.center();
        
        // attach the axis control to the view
        m_axisControl.attach(insertPos);
    }
    
    return kNeedUpdateView;
}

void TvAndCollideDragger::notifyAboutViewChange(eDraggerViewChangeType notify)
{
    if (!m_axisControl.isAttached())
        return;
    
//    if (notify & kViewChangeFull || notify & kViewChangeZoom)
//        m_axisControl.scale();
}

eDraggerResult TvAndCollideDragger::start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView *pExtendedView)
{
    return TvAndSelectionDragger::start(pPrevDragger, pExtendedView);
}

eDraggerResult TvAndCollideDragger::nextpoint(int x, int y)
{
    if (m_collideDraggerState == kSelection)
    {
        TvAndSelectionDragger::nextpoint(x, y);
        OdTvSelectionSetPtr pSSet = getSelectionSet();
        if (pSSet.isNull() || (!pSSet.isNull() && pSSet->numItems() == 0))
            return kNothingToDo;
        return processEnter();
    }
    else if (m_collideDraggerState == kBasePointWaiting)
    {
//        // unselection if tap in empty area
//        OdTvDCPoint pt[2];
//        pt[0].x = x;
//        pt[0].y = y;
//        OdTvSelectionSetPtr pMainModelSSet = getActiveTvViewPtr()->select(&pt[0], 1, m_SelectionOptions, m_modelId);
//        OdTvSelectionSetPtr pDraggerModelSSet = getActiveTvViewPtr()->select(&pt[0], 1, m_SelectionOptions, m_tvDraggersModelId);
//        if( (pMainModelSSet.isNull() && pDraggerModelSSet.isNull())
//           || (( !pDraggerModelSSet.isNull() && pDraggerModelSSet->numItems() == 0 )
//               && ( !pMainModelSSet.isNull() && pMainModelSSet->numItems() == 0 )) )
//            return kNeedFinishDragger;
        
        if (m_axisControl.isAttached())
        {
            m_axisControl.hover(x, y);
        }
        
        if (m_axisControl.isAttached() && m_axisControl.hasSelectedControl())
        {
            m_axisControl.start(x, y);
            m_collideDraggerState = kCollision;
        }
    }
    
    return kNothingToDo;
}

eDraggerResult TvAndCollideDragger::nextpointup(int x, int y)
{
    eDraggerResult res = kNothingToDo;
    
    if (m_collideDraggerState == kCollision)
    {
        if (m_axisControl.isAttached() )
        {
            m_axisControl.finish();
            if (m_axisControl.hover(x, y) )
                res = kNeedUpdateView;
        }
        
        m_collideDraggerState = kBasePointWaiting;
    }
    
    return res;
}

eDraggerResult TvAndCollideDragger::drag(int x, int y)
{
    if (m_collideDraggerState == kSelection)
    {
        return TvAndSelectionDragger::drag(x, y);
    }
    else if (m_collideDraggerState == kBasePointWaiting)
    {
        return kNothingToDo;
    }
    else if (m_collideDraggerState == kCollision)
    {
        // getBaseView()->getMainWindow()->statusBar()->showMessage(tr("Drag. Press Esc for exit."));
        
        if (m_bNeedUnhighlight)
        {
            OdTvSelectionSetPtr pSSet = getSelectionSet();
            OdTvSelectionSetIteratorPtr pSSetIterator = pSSet->getIterator();
            while (!pSSetIterator->done())
            {
                highlight(pSSetIterator, false);
                pSSetIterator->step();
            }
            m_bNeedUnhighlight = false;
        }
        
        addDraggersModelToView();
        
        //ask axis control about the new transfrom for append
        OdTvMatrix xTrans;
        m_axisControl.getTransform(x, y, xTrans);
        
        OdTvModelPtr pModel = m_tvDraggersModelId.openObject(OdTv::kForWrite);
        OdTvMatrix prevMatr = pModel->getModelingMatrix();
        prevMatr.preMultBy(xTrans);
        
        //here we will use fast transform
        pModel->setModelingMatrix(prevMatr, true);
        
        OdTvGsViewPtr pView = getActiveTvViewPtr();
        if (pView.isNull())
            return kNothingToDo;
        
        OdTvCollidedResultPtr secondObjectInPair;
        OdTvCollidedResultPtr pCollisionResult = pView->collide(m_pCollisionSSet, m_modelId, secondObjectInPair, m_resultSelectionOpt.getLevel());
        if (!m_pPrevHLTSet.isNull())
        {
            OdTvSelectionSetIteratorPtr pPrevHLTSetIter = m_pPrevHLTSet->getIterator();
            while (!pPrevHLTSetIter->done())
            {
                highlight(pPrevHLTSetIter, false);
                pPrevHLTSetIter->step();
            }
        }
        
        OdList<OdTvSubItemPath> pathesToRemove;
        OdList<OdTvEntityId> entitiesToRemove;
        OdTvSelectionSetIteratorPtr pCollisionResultSetIter = pCollisionResult->getIterator();
        while (!pCollisionResultSetIter->done())
        {
            if (needHighlight(pCollisionResultSetIter))
            {
                highlight(pCollisionResultSetIter, true);
            }
            else
            {
                OdTvEntityId entId = pCollisionResultSetIter->getEntity();
                OdTvSubItemPath path;
                pCollisionResultSetIter->getPath(path);
                
                entitiesToRemove.push_back(entId);
                pathesToRemove.push_back(path);
            }
            
            pCollisionResultSetIter->step();
        }
        
        //remove items from HLT set
        OdList<OdTvSubItemPath>::iterator it = pathesToRemove.begin();
        OdList<OdTvEntityId>::iterator itEnt = entitiesToRemove.begin();
        while (itEnt != entitiesToRemove.end())
        {
            if (it->entitiesIds().isEmpty())
                pCollisionResult->removeEntity(*itEnt);
            else
                pCollisionResult->removeSubEntity(*itEnt, *it);
            ++itEnt;
            ++it;
        }
        
        m_pPrevHLTSet.release();
        m_pPrevHLTSet = pCollisionResult;
        
        return kNeedUpdateView;
    }
    
    return kNothingToDo;
}

eDraggerResult TvAndCollideDragger::processEscape()
{
    // Clear highlighted objects.
    if (!m_pPrevHLTSet.isNull())
    {
        OdTvSelectionSetIteratorPtr pPrevHLTSetIter = m_pPrevHLTSet->getIterator();
        while (!pPrevHLTSetIter->done())
        {
            highlight(pPrevHLTSetIter, false);
            pPrevHLTSetIter->step();
        }
        m_pPrevHLTSet->clear();
    }
    
    OdTvModelPtr pDraggersModel = m_tvDraggersModelId.openObject(OdTv::kForWrite);
    if ( !pDraggersModel.isNull() )
    {
        pDraggersModel->clearEntities();
        removeDraggersModelFromView();
    }
    
    //here we should clear the selection set. In opposite case we will have problems with selection
    if (!m_bNeedUnhighlight)
    {
        OdTvSelectionSetPtr pSSet = getSelectionSet();
        if (!pSSet.isNull())
            pSSet->clear();
    }
    else if (m_collideDraggerState == kSelection || m_collideDraggerState == kBasePointWaiting)
    {
        OdTvSelectionSetPtr pSSet = getSelectionSet();
        if (!pSSet.isNull())
        {
            OdTvSelectionSetIteratorPtr pSSetIterator = pSSet->getIterator();
            while (!pSSetIterator->done())
            {
                highlight(pSSetIterator, false);
                pSSetIterator->step();
            }
            m_bNeedUnhighlight = false;
        }
    }
    
    m_axisControl.detach();
    
    for (OdUInt32 i = 0; i < m_baseEntities.size(); i++)
    {
        OdTvEntityPtr pEntity = m_baseEntities[i].openObject(OdTv::kForWrite);
        if (!pEntity.isNull())
            pEntity->setTransparency(0.);
    }
    m_baseEntities.clear();
    
    for (OdUInt32 i = 0; i < m_baseGeometries.size(); i++)
    {
        OdTvGeometryDataPtr pGeom = m_baseGeometries[i].openObject();
        if (!pGeom.isNull())
            pGeom->setTransparency(0.);
    }
    m_baseGeometries.clear();
    
    return TvAndSelectionDragger::processEscape();
}

void TvAndCollideDragger::merge(const OdTvSelectionSetPtr &pSSet)
{
    bool bHasShell = false;
    
    // Create set for valid objects for selection
    OdTvSelectionOptions opt(pSSet->getOptions());
    OdTvSelectionSetPtr pFilteredSSet = OdTvSelectionSet::createObject(opt);
    
    // Check if selection set have shell
    OdTvSelectionSetIteratorPtr pIter;
    for (pIter = pSSet->getIterator(); !pIter->done(); pIter->step())
    {
        OdTvGeometryDataId geometryDataId = pIter->getGeometryData();
        OdTvGeometryDataId subEntityId = pIter->getSubEntity();
        OdTvEntityId entityId = pIter->getEntity();
        
        if (!geometryDataId.isNull())
        {
            if (geometryDataId.getType() == OdTv::kShell || geometryDataId.getType() == OdTv::kBrep)
            {
                OdTvShellDataPtr pShell = geometryDataId.openAsShell();
                if (!pShell->getShowOnlyVertices())
                {
                    OdTvSubItemPath path;
                    pIter->getPath(path);
                    pFilteredSSet->appendSubEntity(entityId, path);
                    bHasShell = true;
                }
            }
        }
        else if (!subEntityId.isNull())
        {
            OdTvEntityPtr pSubEnt = subEntityId.openAsSubEntity();
            if (hasShell(pSubEnt))
            {
                OdTvSubItemPath path;
                pIter->getPath(path);
                pFilteredSSet->appendSubEntity(entityId, path);
                bHasShell = true;
            }
        }
        else if (!entityId.isNull() && entityId.getType() == OdTvEntityId::kEntity)
        {
            OdTvEntityPtr pEntity = entityId.openObject();
            if (hasShell(pEntity))
            {
                pFilteredSSet->appendEntity(entityId);
                bHasShell = true;
            }
        }
        
    }
    
    if (bHasShell)
        TvAndSelectionDragger::merge(pFilteredSSet);
    else
    {
        //m_pCore->showMessage(@"Warning", @"Any shell was not selected or selected shells have show only vertices property.");
    }
}

bool TvAndCollideDragger::needHighlight(const OdTvSelectionSetIteratorPtr &pCollidedIterIter) const
{
    OdTvSelectionSetPtr pSSet = getSelectionSet();
    OdTvSelectionSetIteratorPtr pSSetIterator = pSSet->getIterator();
    while (!pSSetIterator->done())
    {
        // Get collided object
        OdTvEntityId collidedEntityId = pCollidedIterIter->getEntity();
        if (collidedEntityId.isNull() || collidedEntityId.getType() == OdTvEntityId::kLight)
            return false;
        OdTvSubItemPath selectedPath;
        pCollidedIterIter->getPath(selectedPath);
        
        // Get
        OdTvEntityId currentEntityId = pSSetIterator->getEntity();
        if (currentEntityId.isNull() || currentEntityId.getType() == OdTvEntityId::kLight)
            return false;
        OdTvSubItemPath currentPath;
        pSSetIterator->getPath(currentPath);
        
        pSSetIterator->step();
        
        if (collidedEntityId == currentEntityId && selectedPath == currentPath)
            return false;
    }
    
    return true;
}

bool TvAndCollideDragger::hasShell(OdTvEntityPtr pEntity) const
{
    OdTvGeometryDataIteratorPtr pIter = pEntity->getGeometryDataIterator();
    while (!pIter->done())
    {
        OdTvGeometryDataId geomDataId = pIter->getGeometryData();
        if (geomDataId.getType() == OdTv::kShell || geomDataId.getType() == OdTv::kBrep)
        {
            OdTvShellDataPtr pShell = geomDataId.openAsShell();
            if (pShell.isNull() || !pShell->getShowOnlyVertices())
                return true;
            else
                return false;
        }
        else if (geomDataId.getType() == OdTv::kSubEntity)
        {
            OdTvEntityPtr pSubEnt = geomDataId.openAsSubEntity();
            bool res = hasShell(pSubEnt);
            if (res)
                return true;
        }
        
        pIter->step();
    }
    
    return false;
}
