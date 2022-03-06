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

// OdObjBrLoop.h: interface for the OdObjBrLoop class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(TEIGHA_ODOBJBRLOOP_H_INCLUDED_)
#define TEIGHA_ODOBJBRLOOP_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TD_PackPush.h"
#include "OBJToolkit.h"
#include "../DevInclude/IBr/IBrLoop.h"
#include "OdObjBrCoedge.h"
#include "OdObjBrVertex.h"
namespace OBJToolkit
{
  class OdObjBrFace;
  class OdObjBrCoedge;

  //-------------------------------------------------------------------------------------------------
  // Class:       OdObjBrLoop
  // Description: This class encapsulates the Loop data 
  //-------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------
  class OdObjBrLoop : public OdIBrLoop
  {
    OdObjBrFace *m_pFace;
    OdObjBrLoop *m_pNextLoop;
    OdObjBrCoedge *m_pFirstCoedge;
    OdObjBrVertex *m_pFirstVertex;
    OdObjBrCoedge *m_pLastCoedge;
  
  public:
    void init();
    ~OdObjBrLoop();
    OdObjBrLoop();
  
  private:
    virtual const OdIBrFace * getFace() const;

    virtual void next(const OdIBrVertex *pFirstChild, OdIBrVertex * & pCurChild);

    virtual void next(const OdIBrCoedge *pFirstChild, OdIBrCoedge * & pCurChild);

    virtual const OdIBrCoedge* find(const OdIBrEdge *pEdge);

    virtual OdGeCurve2d* getParamCurve(const OdIBrCoedge *pIBrCoedge) const;

    virtual bool getParamCurveAsNurb(const OdIBrCoedge *pIBrCoedge, OdGeNurbCurve2d& nurb) const;

    virtual OdGeCurve3d * getOrientedCurve(const OdIBrCoedge *pIBrCoedge) const;

    virtual bool getOrientedCurveAsNurb(const OdIBrCoedge *pIBrCoedge, OdGeNurbCurve3d& nurb) const;

    virtual bool getEdgeOrientToLoop(const OdIBrCoedge *pIBrCoedge) const;
  
  public:
    void setNext(OdObjBrLoop *pNextLoop);
    OdObjBrLoop *getNext() const;
    void setFace(OdObjBrFace *face);
    OdObjBrFace *GetFace() const;
    void setCoedge(OdObjBrCoedge *coedge);
    OdObjBrCoedge *getCoedge();
    OdObjBrVertex *getVertex();
    const OdObjBrVertex *getVertex() const;
    void SetVertex(OdObjBrVertex *pVertex);

    void addCoedge(OdObjBrCoedge * pObjBrCoedge);
    OdObjBrCoedge *getLastCoedge();
  };

}

#include "TD_PackPop.h"

#endif // !defined(TEIGHA_ODOBJBRLOOP_H_INCLUDED_)

