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

// OdObjBrVertex.h: interface for the OdObjBrVertex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(TEIGHA_ODOBJBRVERTEX_H_INCLUDED_)
#define TEIGHA_ODOBJBRVERTEX_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OBJToolkit.h"

#include "TD_PackPush.h"
#include "../DevInclude/IBr/IBrVertex.h" 
#include "OdObjBrEdge.h"
#include "OdObjBrFile.h"

namespace OBJToolkit {

  //-------------------------------------------------------------------------------------------------
  // Class:       OdObjBrVertex
  // Description: This class encapsulates the Vertex data 
  //-------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------
  class OdObjBrVertex : public OdIBrVertex
  {
    OdGePoint3d  m_vPoint;
    OdObjBrVertex *m_pNextVertex;
    OdArray<OdObjBrEdge *> m_pEdgeList;


  private:
    virtual OdGePoint3d getPoint() const;

    virtual void next(const OdIBrLoop *pFirstChild, OdIBrLoop * & pCurChild);
    virtual void next(const OdIBrEdge *pFirstChild, OdIBrEdge * & pCurChild);
    virtual bool getParamPoint(OdGePoint2d &pnt, const OdIBrLoop *pLoop) const;
    
  public:
    void init();
    OdObjBrVertex(OdGePoint3d pPoint);
    ~OdObjBrVertex();

    void setGePoint3d(OdGePoint3d pPoint);
    const OdGePoint3d  GetPoint() const;
    void addEdge(OdObjBrEdge *edge);

    OdObjBrVertex *getNext();
    const OdObjBrVertex *getNext() const;
    void setNext(OdObjBrVertex *pVertex);

  };

}

#include "TD_PackPop.h"

#endif // !defined(TEIGHA_ODOBJBRVERTEX_H_INCLUDED_)

