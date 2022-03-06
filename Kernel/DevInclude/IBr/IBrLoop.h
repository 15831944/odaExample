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

#ifndef _INC_DDBRIMPLOOP_3F9F7BD203C8_INCLUDED
#define _INC_DDBRIMPLOOP_3F9F7BD203C8_INCLUDED

#include "IBrEntity.h"
#include "Br/BrEnums.h"

class OdIBrFace;
class OdIBrVertex;
class OdIBrEdge;
class OdIBrCoedge;
class OdGeNurbCurve2d;
class OdGeNurbCurve3d;
class OdGeCurve2d;
class OdGeCurve3d;

class OdIBrLoop : public OdIBrEntity
{
public:
    virtual const OdIBrFace *getFace() const = 0;
    virtual void next(const OdIBrVertex *pFirstChild,  OdIBrVertex * & pCurChild) = 0;
    virtual void next(const OdIBrCoedge *pFirstChild,  OdIBrCoedge * & pCurChild) = 0;
    virtual const OdIBrCoedge* find(const OdIBrEdge *pEdge) = 0;

    virtual OdGeCurve2d* getParamCurve(const OdIBrCoedge *pIBrCoedge) const = 0;
    virtual bool getParamCurveAsNurb(const OdIBrCoedge *pIBrCoedge, OdGeNurbCurve2d& nurb ) const = 0;
    virtual OdGeCurve3d * getOrientedCurve(const OdIBrCoedge *pIBrCoedge) const = 0;
    virtual bool getOrientedCurveAsNurb(const OdIBrCoedge *pIBrCoedge, OdGeNurbCurve3d& nurb) const = 0;
    virtual bool getEdgeOrientToLoop(const OdIBrCoedge *pIBrCoedge) const = 0;
    virtual BrLoopType getType() const { return odbrLoopUnclassified;}
};

#endif /* _INC_DDBRIMPLOOP_3F9F7BD203C8_INCLUDED */

