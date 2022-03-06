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

#ifndef _DAI_VALIDATION_COMMON_H_
#define _DAI_VALIDATION_COMMON_H_

#include "OdaCommon.h"

#define STL_USING_LIST
#include "OdaSTL.h"

#include "RxObject.h"


void addValidationTask(OdRxClass*);
void removeValidationTask(OdRxClass*);

#define ODRX_VALIDATION_CONS_DEFINE_MEMBERS(ClassName,ParentClass,DOCREATE)                         \
                                                                                                     \
ODRX_VALIDATION_CONS_DEFINE_MEMBERS_ALTNAME(ClassName,ParentClass,OD_T(#ClassName),DOCREATE)



#define ODRX_VALIDATION_CONS_DEFINE_MEMBERS_ALTNAME(ClassName,ParentClass,szClassName,DOCREATE)                 \
                                                                                                     \
ODRX_VALIDATION_DEFINE_MEMBERS2(ClassName,ParentClass,ClassName::pseudoConstructor,0,0,0,szClassName,OdString::kEmpty,OdString::kEmpty,0) \
                                                                                                     \
ODRX_DEFINE_PSEUDOCONSTRUCTOR(ClassName,DOCREATE)



#define ODRX_VALIDATION_DEFINE_MEMBERS2(ClassName,ParentClass,pseudoConsFn,DwgVer,MaintVer,nProxyFlags,szDWGClassName,szDxfName,szAppName,nCustomFlags) \
                                                                                                     \
ODRX_DEFINE_RTTI_MEMBERS(ClassName,ParentClass)                                                      \
                                                                                                     \
ODRX_VALIDATION_DEFINE_INIT_MEMBERS(ClassName,ParentClass,pseudoConsFn,                                         \
    DwgVer,MaintVer,nProxyFlags,szDWGClassName,szDxfName,szAppName,nCustomFlags,0,0)



#define ODRX_VALIDATION_DEFINE_INIT_MEMBERS(ClassName, ParentClass, pseudoConsFn, DwgVer,                \
                                 MaintVer, nProxyFlags, szDWGClassName,                       \
                                 szDxfName, szAppName, nCustomFlags, pMemberCreate, pUserData)\
  ODRX_VALIDATION_DEFINE_INIT_MEMBERS_GENERIC(                                                           \
      ClassName,                                                                              \
      (::newOdRxClass(szDWGClassName, ParentClass::desc(), pseudoConsFn, DwgVer,              \
        MaintVer, nProxyFlags, szDxfName, szAppName, NULL, nCustomFlags, pMemberCreate, pUserData)),                    \
      (::newOdRxClass(szDWGClassName, ParentClass::desc(), pseudoConsFn, DwgVer,              \
        MaintVer, nProxyFlags, szDxfName, szAppName, pAppNameChangeCallback, nCustomFlags, pMemberCreate, pUserData)))



#define ODRX_VALIDATION_DEFINE_INIT_MEMBERS_GENERIC(ClassName, CREATE_CLASS_INSTANCE, CREATE_CLASS_INSTANCE2)   \
                                                                                                     \
/* Registers this class with Teigha.                                         */                      \
void ClassName::rxInit()                                                                             \
{                                                                                                    \
  if (!ClassName::g_pDesc) {                                                                         \
    ClassName::g_pDesc = CREATE_CLASS_INSTANCE;                                                      \
    addValidationTask(ClassName::desc());                                                         \
  } else {                                                                                           \
    ODA_ASSERT(("Class ["#ClassName"] is already initialized.",0));                                  \
    throw OdError(eExtendedError);                                                                   \
  }                                                                                                  \
}                                                                                                    \
void ClassName::rxInit(AppNameChangeFuncPtr pAppNameChangeCallback)                                  \
{                                                                                                    \
  if (!ClassName::g_pDesc) {                                                                         \
    ClassName::g_pDesc = CREATE_CLASS_INSTANCE2;                                                     \
    addValidationTask(ClassName::desc());                                                            \
  } else {                                                                                           \
    ODA_ASSERT(("Class ["#ClassName"] is already initialized.",0));                                  \
    throw OdError(eExtendedError);                                                                   \
  }                                                                                                  \
}                                                                                                    \
                                                                                                     \
/* Unregisters this class with Teigha.                                       */                      \
void ClassName::rxUninit()                                                                           \
{                                                                                                    \
  if (ClassName::g_pDesc) {                                                                          \
    removeValidationTask(ClassName::desc());                                                         \
    ::deleteOdRxClass(ClassName::g_pDesc);                                                           \
    ClassName::g_pDesc = 0;                                                                          \
  } else {                                                                                           \
    ODA_ASSERT(("Class ["#ClassName"] is not initialized yet.",0));                                  \
    throw OdError(eNotInitializedYet);                                                               \
  }                                                                                                  \
}
//addModelTask(ClassName::desc());        \

#endif // _DAI_VALIDATION_COMMON_H_
