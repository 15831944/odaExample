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

// OdObjBrFace.h: interface for the OdObjBrFace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(TEIGHA_ODOBJBRFACE_H_INCLUDED_)
#define TEIGHA_ODOBJBRFACE_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OBJToolkit.h"

#include "TD_PackPush.h"
#include "../DevInclude/IBr/IBrFace.h"
#include "OdObjBrLoop.h"

namespace OBJToolkit {

  class OdObjBrShell;
  class OdObjBrLoop;

  //-------------------------------------------------------------------------------------------------
  // Class:       OdObjBrFace
  // Description: This class encapsulates the Face data 
  //-------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------
  class OdObjBrFace : public OdIBrFace
  {
  protected:
    OdGeNurbSurface *m_pNurbSurface;
    OdObjBrFace *m_pNextFace;
    OdObjBrShell *m_pShell;
    OdObjBrLoop *m_pFirstLoop;

  public:
    OdObjBrFace();
    ~OdObjBrFace();
    void init();
    void setSurface(OdGeNurbSurface *nurb);

    // OdIBrFace implementation

    virtual bool getSurfaceAsNurb(OdGeNurbSurface& nurb) const;

    virtual OdGeSurface* getSurface() const;

    virtual bool getSurfaceType(OdGe::EntityId& type) const;

    virtual bool getOrientToSurface() const;

    virtual OdIBrShell *getShell();

    virtual void next(const OdIBrLoop *pFirstChild, OdIBrLoop * & pCurChild);

    virtual bool getTrueColor(OdUInt32 &rgb) const;

    virtual bool getColorIndex(OdUInt16 &indx) const;

    virtual bool getMaterial(OdUInt64 &id) const;

    virtual bool getMaterial(OdString &strMatName) const;

    void setLoop(OdObjBrLoop *pLoop);
    OdObjBrLoop *getLoop();
    void setShell(OdObjBrShell *shell);
    OdObjBrShell* GetShell();
    void setNext(OdObjBrFace *pNextFace);
    OdObjBrFace* getNext();
    const OdObjBrFace* getNext() const;
    void addLoop(OdObjBrLoop * pObjBrLoop);
  };

}

#include "TD_PackPop.h"

#endif // !defined(TEIGHA_ODOBJBRFACE_H_INCLUDED_)

