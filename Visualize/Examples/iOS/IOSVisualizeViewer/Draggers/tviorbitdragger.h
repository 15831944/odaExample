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
#ifndef TVIORBITDRAGGER_H
#define TVIORBITDRAGGER_H

#include "Tools/TvDragger.h"

class TviOrbitDragger : public OdTvDragger
{
public:
    TviOrbitDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvDraggersModelId);
    ~TviOrbitDragger() {}

    eDraggerResult start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView* pExtendedView);
    eDraggerResult nextpoint(int x, int y);
    eDraggerResult drag(int x, int y);
    eDraggerResult nextpointup(int x, int y);

  private:

    // last cliked or moved point (ECS)
    OdGePoint3d m_prevPt;

    // mouse move to rotation angle conversion coefficient
    double m_D;

    // center of the scene
    OdGePoint3d     m_viewCenter;
};

#endif // TVIORBITDRAGGER_H
