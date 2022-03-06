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

#ifndef _IFC_COMMON_H_
#define _IFC_COMMON_H_

#include "OdaCommon.h"

#include "RxObject.h"
#include "SmartPtr.h"
#include "daiValueTypes.h"

#define SMARTPTR(classname) class classname; typedef OdSmartPtr<classname> classname##Ptr; typedef OdArray<classname##Ptr> classname##PtrArray;

#define OD_IFC_CONS_DEFINE_MEMBERS(ClassName,ParentClass,DOCREATE,ClassType)                         \
                                                                                                     \
OD_IFC_CONS_DEFINE_MEMBERS_ALTNAME(ClassName,ParentClass,OD_T(#ClassName),DOCREATE,ClassType)

#define OD_IFC_CONS_DEFINE_MEMBERS_ALTNAME(ClassName,ParentClass,szClassName,DOCREATE,ClassType)     \
                                                                                                     \
OD_IFC_DEFINE_MEMBERS2(ClassName,ParentClass,ClassName::pseudoConstructor,0,0,0,szClassName,OdString::kEmpty,OdString::kEmpty,0,ClassType) \
                                                                                                     \
ODRX_DEFINE_PSEUDOCONSTRUCTOR(ClassName,DOCREATE)

#define OD_IFC_DEFINE_MEMBERS2(ClassName,ParentClass,pseudoConsFn,DwgVer,MaintVer,nProxyFlags,szDWGClassName,szDxfName,szAppName,nCustomFlags,ClassType) \
                                                                                                     \
ODRX_DEFINE_RTTI_MEMBERS(ClassName,ParentClass)                                                      \
                                                                                                     \
OD_IFC_DEFINE_INIT_MEMBERS(ClassName,ParentClass,pseudoConsFn,                                       \
    DwgVer,MaintVer,nProxyFlags,szDWGClassName,szDxfName,szAppName,nCustomFlags, ClassType)


#define OD_IFC_DEFINE_INIT_MEMBERS(ClassName, ParentClass, pseudoConsFn, DwgVer,              \
                                 MaintVer, nProxyFlags, szDWGClassName,                       \
                                 szDxfName, szAppName, nCustomFlags, ClassType)               \
  OD_IFC_DEFINE_INIT_MEMBERS_GENERIC(                                                         \
      ClassName,                                                                              \
      (::newOdRxClass(szDWGClassName, ParentClass::desc(), pseudoConsFn, DwgVer,              \
        MaintVer, nProxyFlags, szDxfName, szAppName, NULL, nCustomFlags)),                    \
      (::newOdRxClass(szDWGClassName, ParentClass::desc(), pseudoConsFn, DwgVer,              \
        MaintVer, nProxyFlags, szDxfName, szAppName, pAppNameChangeCallback, nCustomFlags)),  \
       ClassType)

#define OD_IFC_DEFINE_INIT_MEMBERS_GENERIC(ClassName, CREATE_CLASS_INSTANCE, CREATE_CLASS_INSTANCE2, ClassType)\
void ClassName::rxInit()                                                                             \
{                                                                                                    \
  if (!ClassName::g_pDesc) {                                                                         \
    ClassName::g_pDesc = CREATE_CLASS_INSTANCE;                                                      \
    odIfcClassDictionary().putAt(ClassType, ClassName::desc());                                      \
  } else {                                                                                           \
    ODA_ASSERT(("Class ["#ClassName"] is already initialized.",0));                                  \
    throw OdError(eExtendedError);                                                                   \
  }                                                                                                  \
}                                                                                                    \
void ClassName::rxInit(AppNameChangeFuncPtr pAppNameChangeCallback)                                  \
{                                                                                                    \
  if (!ClassName::g_pDesc) {                                                                         \
    ClassName::g_pDesc = CREATE_CLASS_INSTANCE2;                                                     \
    odIfcClassDictionary().putAt(ClassType, ClassName::desc());                                      \
  } else {                                                                                           \
    ODA_ASSERT(("Class ["#ClassName"] is already initialized.",0));                                  \
    throw OdError(eExtendedError);                                                                   \
  }                                                                                                  \
}                                                                                                    \
                                                                                                     \
/* Unregisters this class with ODA Platform.                                 */                      \
void ClassName::rxUninit()                                                                           \
{                                                                                                    \
  if (ClassName::g_pDesc) {                                                                          \
    ::deleteOdRxClass(ClassName::g_pDesc);                                                           \
    ClassName::g_pDesc = 0;                                                                          \
    odIfcClassDictionary().remove(ClassType);                                                        \
  } else {                                                                                           \
    ODA_ASSERT(("Class ["#ClassName"] is not initialized yet.",0));                                  \
    throw OdError(eNotInitializedYet);                                                               \
  }                                                                                                  \
}

#define OD_IFC_DECLARE_MEMBERS_GENERIC(ClassType, ClassName)                                         \
public:                                                                                              \
  static OdSmartPtr<ClassName> cast(const OdRxObject* pObj)                                          \
    {                                                                                                \
      if (pObj)                                                                                      \
        return OdSmartPtr<ClassName>(((ClassName*)pObj->queryX(ClassName::desc())), kOdRxObjAttach); \
      return (ClassName*)0;                                                                          \
    }                                                                                                \
  static ClassType* g_pDesc;                                                                         \
  static ClassType* desc();                                                                          \
  virtual ClassType* isA() const;                                                                    \
  virtual OdRxObject* queryX(const OdRxClass* protocolClass) const;                                  \
  static OdRxObjectPtr pseudoConstructor();                                                          \
  static OdSmartPtr<ClassName> createObject()                                                        \
  { if (!desc()) throw OdError(eNotInitializedYet); return desc()->create(); }                       \
  static OdSmartPtr<ClassName> createObject(OdIfcModel* pModel)                                      \
  {                                                                                                  \
  if (!pModel)                                                                                       \
    throw OdError(eNoDatabase);                                                                      \
  if (!desc())                                                                                       \
    throw OdError(eNotInitializedYet);                                                               \
  OdSmartPtr<ClassName> pObj = desc()->create();                                                     \
  OdIfcEntityPtr pEnt = pModel->createEntityInstance(desc()->name().mid(2));                         \
  if (pEnt.isNull())                                                                                 \
    throw OdError(eIllegalEntityType);                                                               \
  pModel->appendEntityInstance(pEnt);                                                                \
  pObj->m_pEntInst = pEnt;                                                                           \
  pEnt->resolve(kResCompound, new OdIfcCompoundPtr(pObj));                                           \
  return pObj;                                                                                       \
  }                                                                                                  \
  static void rxInit();                                                                              \
  static void rxInit(AppNameChangeFuncPtr appNameChangeFunc);                                        \
                                                                                                     \
  static void rxUninit()

#define OD_IFC_DECLARE_MEMBERS(ClassName)                                                            \
    OD_IFC_DECLARE_MEMBERS_GENERIC(OdRxClass, ClassName)

#endif // _IFC_COMMON_H_
