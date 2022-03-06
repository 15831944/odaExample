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
#ifndef TVIZOOMWINDOWDRAGGER_H
#define TVIZOOMWINDOWDRAGGER_H

#include "Tools/TvDragger.h"
#include "tviview.h"

class TviZoomWindowDragger : public OdTvDragger
{
public:
    TviZoomWindowDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvDraggersModelId, TviView *pView);
    ~TviZoomWindowDragger() {}

    eDraggerResult start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView* pExtendedView);
    eDraggerResult nextpoint(int x, int y);
    eDraggerResult drag(int x, int y);
    eDraggerResult nextpointup(int x, int y);
    OdTvDraggerPtr finish(eDraggerResult& rc);

  private:
    void updateFrame(bool bCreate);

  private:

    // first clicked point (WCS)
    OdGePoint3d m_firstPt;

    // first clicked point (DCS) pixels
    OdGePoint2d m_firstPt_device;

    // last drag point (WCS)
    OdGePoint3d m_lastDragPt;

    // need to control the ::start called first time or not
    bool m_bJustCreatedObject;

    // temporary geometry
    OdTvEntityId m_entityId;
    OdTvGeometryDataId m_frameId;

    // points for creating the polygon frame
    OdTvPointArray m_pts;

    TviView *m_pTviVeiw;
};

#endif // TVIZOOMWINDOWDRAGGER_H
