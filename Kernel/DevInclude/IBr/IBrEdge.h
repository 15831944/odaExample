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

#ifndef _INC_DDBRIMPEDGE_3F82D9CE009C_INCLUDED
#define _INC_DDBRIMPEDGE_3F82D9CE009C_INCLUDED

#include "IBrEntity.h"
#include "Ge/Ge.h"
#include "Br/BrEnums.h"

class OdIBrVertex;
class OdIBrCoedge;
class OdGeCurve3d;
class OdGeNurbCurve3d;

class OdIBrEdge : public OdIBrEntity
{
public:
		virtual OdIBrVertex *getVertex1( ) const = 0;
		virtual OdIBrVertex *getVertex2( ) const = 0;

		virtual OdGe::EntityId getCurveType() const = 0;

		virtual OdGeCurve3d* getGeCurve() const = 0;

    virtual OdBrErrorStatus getGeCurve(OdGeCurve3d* &pCurve) const = 0;

    virtual bool getCurveAsNurb(OdGeNurbCurve3d& nurb) const = 0;

		virtual bool getOrientToCurve() const = 0;

    virtual void next(const OdIBrCoedge *pFirstChild,  OdIBrCoedge * & pCurChild) = 0;

    virtual bool hasColor(OdUInt8 typeFlag) = 0;

    virtual bool getTrueColor(OdUInt32 &rgb) = 0;
    
    virtual bool getColorIndex(OdUInt16 &indx) = 0;
};

#endif /* _INC_DDBRIMPEDGE_3F82D9CE009C_INCLUDED */

