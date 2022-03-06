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

#if !defined(_ODOLESSITEMHANDLERMODULE_INCLUDED_)
#define _ODOLESSITEMHANDLERMODULE_INCLUDED_

#include "TD_PackPush.h"

#include "RxDynamicModule.h"
#include "ThreadsCounter.h"

/** \details
  This class implements the OLE item handler module and is based on 
  the cross-platform OleSS library.
  Library: Source code provided.
  <group Extension_Classes> 
*/
class OdOleSsItemHandlerModuleImpl : public OdRxModule
{
protected:
  void initApp();

  void uninitApp();
protected:
  struct OdMutexPtr2
  {
    OdMutexPtr *m_pMutex;
    OdMutexPtr2() : m_pMutex(NULL) { }
    void detach() { if (m_pMutex) { delete m_pMutex; m_pMutex = NULL; } }
    void attach() { if (!m_pMutex) { m_pMutex = new OdMutexPtr(); } }
    ~OdMutexPtr2() { detach(); }
  } m_pOleInitMutex;
  OdPseudoConstructorType m_savedConstructor;
public:
  OdOleSsItemHandlerModuleImpl();
  static OdMutexPtr &globalOleInitMutex();
  static void internalLockModule();
  static void internalUnlockModule();
};

#include "TD_PackPop.h"

#endif //#if !defined(_ODOLESSITEMHANDLERMODULE_INCLUDED_)
