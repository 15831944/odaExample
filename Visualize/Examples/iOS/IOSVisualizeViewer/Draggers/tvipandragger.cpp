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
#include "tvipandragger.h"
#include "OdaCommon.h"

#include <QDebug>

eDraggerResult TviPanDragger::start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView *pExtendedView)
{
    return OdTvDragger::start(pPrevDragger, pExtendedView);
}

eDraggerResult TviPanDragger::nextpoint(int x, int y)
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

eDraggerResult TviPanDragger::drag(int x, int y)
{
    if ( m_state == kWaiting )
        return kNothingToDo;

    OdTvGsViewPtr pView = getActiveTvViewPtr();
    if ( pView.isNull() )
        return kNothingToDo;

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

eDraggerResult TviPanDragger::nextpointup(int x, int y)
{
    return reset();
}
