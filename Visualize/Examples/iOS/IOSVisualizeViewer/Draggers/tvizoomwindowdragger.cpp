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
#include "tvizoomwindowdragger.h"
#include "OdaCommon.h"
#include <QColor>

TviZoomWindowDragger::TviZoomWindowDragger(OdTvGsDeviceId &tvDeviceId, OdTvModelId &tvDraggersModelId, TviView *pView)
    : OdTvDragger (tvDeviceId, tvDraggersModelId)
{
    m_bJustCreatedObject = true;
    m_pts.resize(4);
    m_bHaveDrawableTemporaryGeometry = true;
    m_bNeedFreeDrag = true;
    m_pTviVeiw = pView;
}

eDraggerResult TviZoomWindowDragger::start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView *pExtendedView)
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

eDraggerResult TviZoomWindowDragger::nextpoint(int x, int y)
{
    CHECK_DRAGGER

    // remember first click
    m_firstPt = toEyeToWorld(x, y);
    m_firstPt_device = OdGePoint2d(x, y);

    if(!m_entityId.isNull())
        m_entityId.openObject(OdTv::kForWrite)->setVisibility(true);

    return kNothingToDo;
}

eDraggerResult TviZoomWindowDragger::drag(int x, int y)
{
    CHECK_DRAGGER

    //get current drag point
    m_lastDragPt = toEyeToWorld(x, y);

    // create temporary geometry if need or update
    OdTvEntityPtr entityPtr = m_entityId.openObject(OdTv::kForWrite);
    updateFrame(entityPtr.isNull());

    return kNeedUpdateView;
}

eDraggerResult TviZoomWindowDragger::nextpointup(int x, int y)
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
      m_pTviVeiw->setAnimation(pAnimation);
      if (pAnimation)
      {
        pAnimation->start();
        return kNeedUpdateView;
      }
    }
    
    return kNothingToDo;
}

OdTvDraggerPtr TviZoomWindowDragger::finish(eDraggerResult &rc)
{
    // remove the draggers model from the view
    removeDraggersModelFromView();

    return OdTvDragger::finish(rc);
}

void TviZoomWindowDragger::updateFrame(bool bCreate)
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
        QColor color = QColor(ODGETRED(bgColor), ODGETGREEN(bgColor), ODGETBLUE(bgColor));
        color = color.value() > 128 ? QColor(Qt::black) : QColor(Qt::white);
        entityNewPtr->setColor(OdTvColorDef(color.red(), color.green(), color.blue()));
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
