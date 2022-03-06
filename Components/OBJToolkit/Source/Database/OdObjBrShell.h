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

// OdObjBrShell.h: interface for the OdObjBrShell class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(TEIGHA_ODOBJBRSHELL_H_INCLUDED_)
#define TEIGHA_ODOBJBRSHELL_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TD_PackPush.h"
#include "OBJToolkit.h"
#include "../DevInclude/IBr/IBrShell.h"

namespace OBJToolkit
{
  class OdObjBrFace;
  class OdObjBrComplex;

  //-------------------------------------------------------------------------------------------------
  // Class:       OdObjBrShell
  // Description: the class encapsulates the information about a Shell
  //-------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------
  class OdObjBrShell : public OdIBrShell
  {
  protected:
    OdObjBrShell *m_pNextShell;
    OdObjBrFace *m_pFirstFace;
    OdObjBrComplex *m_pComplex;

  public:
    OdObjBrShell();
    ~OdObjBrShell();

    void SetFace(OdObjBrFace *);
    OdObjBrFace *GetFace();
    OdObjBrShell* GetNext();
    void setNext(OdObjBrShell *pNextShell);
    OdObjBrComplex* GetComplex();
    void SetComplex(OdObjBrComplex *complex);
    const OdObjBrFace *GetFace() const;
    const OdObjBrShell *GetNext() const;

  private:
    void init();
    // OdIBrShell implementation
    virtual OdIBrComplex *getComplex();
    virtual void next(const OdIBrFace *pFirstChild, OdIBrFace * & pCurChild);
  };
}


#include "TD_PackPop.h"

#endif // !defined(TEIGHA_ODOBJBRSHELL_H_INCLUDED_)

