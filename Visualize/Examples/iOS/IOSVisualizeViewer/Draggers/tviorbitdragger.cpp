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
#include "tviorbitdragger.h"
#include "OdaCommon.h"

TviOrbitDragger::TviOrbitDragger(OdTvGsDeviceId &tvDeviceId, OdTvModelId &tvDraggersModelId)
    : OdTvDragger (tvDeviceId, tvDraggersModelId)
{
    m_D = 16.0;
}

eDraggerResult TviOrbitDragger::start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView *pExtendedView)
{
    return  OdTvDragger::start(pPrevDragger, pExtendedView);
}

eDraggerResult TviOrbitDragger::nextpoint(int x, int y)
{
    if ( m_state == kWaiting )
        return kNothingToDo;

    OdTvGsViewPtr pView = getActiveTvViewPtr();
    if ( pView.isNull() )
        return kNothingToDo;

    // calculate click point in WCS
    OdGePoint3d pt = toEyeToWorld(x, y);

    // transfer point to the eye coordinate system
    m_prevPt = pView->viewingMatrix() * pt;

    // calculate mouse move to rotation angle conversion coefficient in base of viewport dc size
    OdGePoint3d pt1;
    OdGePoint2d pt2;
    pView->viewDcCorners((OdGePoint2d&)pt1, pt2);
    pt2.x -= pt1.x;
    pt2.y -= pt1.y;
    double r = odmin(pt2.x, pt2.y);
    m_D = r;

    // here we should to remember the extents since we want to rotate the scene about this point
    if (m_pTvExtendedView)
    {
        OdGeBoundBlock3d cachedExt;
        if (m_pTvExtendedView->getCachedExtents(cachedExt))
        {
            m_viewCenter = cachedExt.center();
            return kNothingToDo;
        }
    }

    OdGeBoundBlock3d extents;
    pView->viewExtents(extents);
    m_viewCenter = extents.center();
    m_viewCenter.transformBy(pView->eyeToWorldMatrix());

    if (m_pTvExtendedView)
    {
        OdGeBoundBlock3d lastExt;
        if (pView->getLastViewExtents(lastExt))
            m_pTvExtendedView->setViewExtentsForCaching(&lastExt);
    }

    return kNothingToDo;
}

eDraggerResult TviOrbitDragger::drag(int x, int y)
{
    if ( m_state == kWaiting )
        return kNothingToDo;

    OdTvGsViewPtr pView = getActiveTvViewPtr();
    if ( pView.isNull() )
        return kNothingToDo;

    // calculate click point in WCS
    OdGePoint3d pt = toEyeToWorld(x, y);

    // transfer point to the eye coordinate system
    OdGePoint3d ptView = pView->viewingMatrix() * pt;

    // calculate the angles for the rotation about appropriate axes
    double distX = ptView.x - m_prevPt.x; // around vertical
    double distY = ptView.y - m_prevPt.y; // around horizontal

    distX *= -OdaPI / m_D;
    distY *= OdaPI / m_D;

    // perform camera orbiting
    if (m_pTvExtendedView)
        m_pTvExtendedView->orbit(distY, distX, &m_viewCenter);

    // store previous click point
    m_prevPt = ptView;

    return kNeedUpdateView;
}

eDraggerResult TviOrbitDragger::nextpointup(int x, int y)
{
    return reset();
}
