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

// OdObjBrFile.h: interface for the OdObjBrFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(TEIGHA_ODOBJBRFILE_H_INCLUDED_)
#define TEIGHA_ODOBJBRFILE_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TD_PackPush.h"
#include "../DevInclude/IBr/IBrFile.h"
#include "OdObjBrFace.h"
#include "OdObjBrVertex.h"
#include "OdObjBrComplex.h"
#include "OdObjBrBrep.h"
#include "OdObjBrShell.h"
#include <set>

namespace OBJToolkit {

  class OdObjBrBrep;
  class OdObjBrComplex;
  class OdObjBrVertex;
  class OdObjBrFace;

  //-------------------------------------------------------------------------------------------------
  // Class:       OdObjBrFile
  // Description: This class encapsulates the File data 
  //-------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------
  class OdObjBrFile : public OdIBrFile
  {
  protected:
    OdObjBrBrep *m_pBody;
    OdObjBrComplex *m_pFirstComplex;

  public:

    void formEntityList();
    void clearEntityList();
    // OdIBrFile implementation 
    virtual void next(const OdIBrBrep *pFirstChild, OdIBrBrep * & pCurChild);
    virtual void next(const OdIBrVertex *pFirstChild, OdIBrVertex * & pCurChild);
    virtual void next(const OdIBrShell *pFirstChild, OdIBrShell * & pCurChild);
    virtual void next(const OdIBrFace *pFirstChild, OdIBrFace * & pCurChild);
    virtual void next(const OdIBrEdge *pFirstChild, OdIBrEdge * & pCurChild);
    virtual void next(const OdIBrComplex *pFirstChild, OdIBrComplex * & pCurChild);
    
    virtual void *getIBr();
    OdObjBrFile();
    ~OdObjBrFile();

    void setBody(OdObjBrBrep *pBody);
    OdObjBrBrep *getBody();
    void setComplex(OdObjBrComplex *firstComplex);
    OdObjBrComplex *getComplex();

    unsigned int m_pFaceIndexes;
    unsigned int m_pVertexIndexes;
    unsigned int m_pEdgeIndexes;
    unsigned int m_pShellIndexes;

    OdArray<OdObjBrShell *> m_Shells;
    OdArray<OdObjBrFace *> m_pFaces;
    OdArray<OdObjBrEdge *> m_pEdges;
    OdArray<OdObjBrVertex *> m_pVertexes;
    std::set<OdIBrEntity *> m_pEntityList;
    
  };
}


#include "TD_PackPop.h"

#endif // !defined(TEIGHA_ODOBJBRFILE_H_INCLUDED_)

