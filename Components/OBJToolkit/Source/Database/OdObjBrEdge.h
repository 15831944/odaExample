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

// OdObjBrEdge.h: interface for the OdObjBrEdge class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(TEIGHA_ODOBJBREDGE_H_INCLUDED_)
#define TEIGHA_ODOBJBREDGE_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OBJToolkit.h"

#include "TD_PackPush.h"
#include "../DevInclude/IBr/IBrEdge.h"
#include "Ge/GeSurfaceCurve2dTo3d.h"

namespace OBJToolkit {

  class OdObjBrVertex;
  class OdObjBrCoedge;

  //-------------------------------------------------------------------------------------------------
  // Class:       OdObjBrEdge
  // Description: This class encapsulates the Edge data 
  //-------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------
  class OdObjBrEdge : public OdIBrEdge
  {
  protected:
    OdObjBrVertex *m_pVertex1;
    OdObjBrVertex *m_pVertex2;
    OdObjBrCoedge *m_pFirstCoedge;
    OdGeSurfaceCurve2dTo3d *m_pCurv3d;

  public:
    OdObjBrEdge();
    ~OdObjBrEdge();

    void init();
    const OdObjBrVertex *getStart() const;
    OdObjBrVertex *getStart();
    void setStart(OdObjBrVertex *pVertex1);
    const OdObjBrVertex *getEnd() const;
    OdObjBrVertex *getEnd();
    void setEnd(OdObjBrVertex *pVertex2);

    void setCoedge(OdObjBrCoedge *coedge);
    const OdObjBrCoedge *getCoedge() const;
    OdObjBrCoedge *getCoedge();

  private:
    virtual OdIBrVertex *getVertex1() const;

    virtual OdIBrVertex *getVertex2() const;
    
    virtual OdGe::EntityId getCurveType() const;

    virtual OdGeCurve3d* getGeCurve() const;

    virtual OdBrErrorStatus getGeCurve(OdGeCurve3d* &pCurve) const;

    virtual bool getCurveAsNurb(OdGeNurbCurve3d& nurb) const;

    virtual bool getOrientToCurve() const;

    virtual void next(const OdIBrCoedge *pFirstChild, OdIBrCoedge * & pCurChild);

    virtual bool hasColor(OdUInt8 typeFlag);

    virtual bool getTrueColor(OdUInt32 &rgb);

    virtual bool getColorIndex(OdUInt16 &indx);

  public:
    void setCurve3d(OdGeSurfaceCurve2dTo3d * pCurve3d);
  };

}
#include "TD_PackPop.h"

#endif // !defined(TEIGHA_ODOBJBREDGE_H_INCLUDED_)

