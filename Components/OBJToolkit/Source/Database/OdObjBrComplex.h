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

// OdObjBrLump.h: interface for the OdObjBrLump class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(TEIGHA_ODOBJBRLUMP_H_INCLUDED_)
#define TEIGHA_ODOBJBRLUMP_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TD_PackPush.h"
#include "OBJToolkit.h"
#include "../DevInclude/IBr/IBrComplex.h"

#include "OdObjBrFile.h"
#include "OdObjBrBrep.h"
namespace OBJToolkit
{
  class OdObjBrShell;
  class OdObjBrBrep;

  //-------------------------------------------------------------------------------------------------
  // Class:       OdObjBrComplex
  // Description: This class encapsulates the Complex data 
  //-------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------
  class OdObjBrComplex : public OdIBrComplex
  {
  protected:
    OdObjBrComplex *m_pNextComplex;
    OdObjBrShell *m_pShell;
    OdObjBrBrep *m_pBody;

  public:
    OdObjBrComplex();
    ~OdObjBrComplex();

    OdObjBrBrep* getBody();
    const OdObjBrBrep* getBody() const;
    void setBody(OdObjBrBrep* pBody);
    void init();
    void setShell(OdObjBrShell* shell);
    OdObjBrShell* getShell();
    const OdObjBrShell* getShell() const;

    OdObjBrComplex* getNext();
    const OdObjBrComplex* getNext() const;
    void setNext(OdObjBrComplex *compelex);

  private:
    virtual void next(const OdIBrShell *pFirstChild, OdIBrShell * & pCurChild);
  };
}


#include "TD_PackPop.h"

#endif // !defined(TEIGHA_ODOBJBRLUMP_H_INCLUDED_)

