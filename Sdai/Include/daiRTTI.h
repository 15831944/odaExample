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

#ifndef _DAI_RTTI_H
#define _DAI_RTTI_H

#include "OdaCommon.h"
#include "daiSchema.h"
#include "daiEntity.h"

namespace OdDAI {
  class Entity;
  class Schema;
  typedef OdSmartPtr<Schema> SchemaPtr;
}

DAI_EXPORT OdDAI::Entity* getOdDAIEntityClass(
  const OdString &szClassName,
  OdRxClass* pBaseClass,
  OdDAI::SchemaPtr expSchema,
  OdPseudoConstructorType pConstr = 0,
  int DwgVer = 0,
  int MaintVer = 0,
  int nProxyFlags = 0,
  const OdString& sDxfName = OdString::kEmpty,
  const OdString& sAppName = OdString::kEmpty,
  AppNameChangeFuncPtr fNameChangeFunc = NULL,
  int nCustomFlags = 0,
  OdRxMemberCollectionConstructorPtr memberConstruct = 0,
  void* userData = 0
);

/**
Headers declarations
*/

#define OD_EXP_DECLARE_ENTITY_DEFINITION()                                                          \
public:                                                                                             \
  static OdDAI::Entity* g_pExpEntityDef;                                                             

#define OD_EXP_DECLARE_MEMBERS_GENERIC(ClassType, ClassName)\
public:                                                                                              \
                                                                                                     \
  /** Casts the specified pointer to an ClassName SmartPointer. **/                      \
  static OdSmartPtr<ClassName> cast(const OdRxObject* pObj)                                          \
  {                                                                                                  \
    if (pObj)                                                                                        \
      return OdSmartPtr<ClassName>(((ClassName*)pObj->queryX(ClassName::desc())), kOdRxObjAttach);   \
    return (ClassName*)0;                                                                            \
  }                                                                                                  \
                                                                                                     \
  static ClassType* g_pDesc;                                                                         \
                                                                                                     \
  /** Returns the static ClassType description object associated with this object. **/  \
  /** This function is for use only when the class type of this object is known.          **/  \
  /** If the class type of this object is unknown, use instead isA().                           **/  \
  static ClassType* desc();                                                                   \
                                                                                                     \
  /** Returns the ClassType description instance associated with this object.      **/  \
  /** This function is for use only when the class type of this object is unknown.        **/  \
  /** If the class type of this object is known, use instead desc().                            **/  \
  virtual ClassType* isA() const;                                                                    \
                                                                                                     \
  /** Returns the Protocol Extension object for this object.        **/                 \
  /** Return null if there is no Protocol Extension object is found.    **/                 \
  virtual OdRxObject* queryX(const OdRxClass* protocolClass) const;                                 \
                                                                                                    \
  /** Creates a new instance of this object type.                   **/                             \
  /** Returns a SmartPointer to the new instance.                       **/                         \
  static OdRxObjectPtr pseudoConstructor();                                                         \
                                                                                                    \
  /** Registers ClassName with the ODA Platform.                           **/                      \
  static void rxInit();                                                                             \
  static void rxInit(AppNameChangeFuncPtr appNameChangeFunc);                                       \
                                                                                                    \
/* Unregisters ClassName with the ODA Platform.                          **/                 \
  static void rxUninit();

#define OD_EXP_DECLARE_MEMBERS_GENERIC_OBJECT_CREATE(ClassType, ClassName)                          \
public:                                                                                             \
/** Creates a new instance of this object type.                   **/                               \
/** Returns a SmartPointer to the new instance.                       **/                           \
static OdSmartPtr<ClassName> createObject()                                                         \
{ if (!desc()) throw OdError(eNotInitializedYet); return desc()->create(); }                        \



#define OD_EXP_DECLARE_MEMBERS_GENERIC_MODEL_CREATE(ClassType, ClassName)                           \
  public:                                                                                           \
  /** Creates a new instance of this object type.                   **/                             \
  /** Returns a SmartPointer to the new instance.                       **/                         \
  static OdSmartPtr<ClassName> createObject(OdDAI::Model* model);                                   \

#define OD_EXP_INTEROPERABLE_DECLARE_MEMBERS(ClassName)\
  OD_EXP_DECLARE_MEMBERS_GENERIC(OdRxClass, ClassName) \
  OD_EXP_DECLARE_MEMBERS_GENERIC_OBJECT_CREATE(OdRxClass, ClassName) \
  OD_EXP_DECLARE_MEMBERS_GENERIC_MODEL_CREATE(OdRxClass, ClassName)

#define OD_EXP_NON_INSTANTIABLE_DECLARE_MEMBERS(ClassName)\
  OD_EXP_DECLARE_ENTITY_DEFINITION() \
  OD_EXP_DECLARE_MEMBERS_GENERIC(OdRxClass, ClassName)\

#define OD_EXP_DECLARE_MEMBERS(ClassName) \
  OD_EXP_DECLARE_ENTITY_DEFINITION() \
  OD_EXP_DECLARE_MEMBERS_GENERIC(OdRxClass, ClassName) \
  OD_EXP_DECLARE_MEMBERS_GENERIC_OBJECT_CREATE(OdRxClass, ClassName) \
  OD_EXP_DECLARE_MEMBERS_GENERIC_MODEL_CREATE(OdRxClass, ClassName)


#define OD_EXP_HEADER_DECLARE_MEMBERS(ClassName)\
  OD_EXP_DECLARE_ENTITY_DEFINITION() \
  OD_EXP_DECLARE_MEMBERS_GENERIC(OdRxClass, ClassName)\
  OD_EXP_DECLARE_MEMBERS_GENERIC_OBJECT_CREATE(OdRxClass, ClassName) \




/**
Cpp definitions
*/
#define OD_EXP_DEFINE_RTTI_MEMBERS_GENERIC(ClassType, ClassName, ParentClass) \
                                                                            \
  OdDAI::Entity* ClassName::g_pExpEntityDef = 0;                            \
  ClassType* ClassName::g_pDesc = 0;                                        \
  ClassType* ClassName::desc() { return g_pDesc; }                          \
  ClassType* ClassName::isA() const { return g_pDesc; }                     \
                                                                            \
  OdRxObject* ClassName::queryX(const OdRxClass* pClass) const {            \
    return ::odQueryXImpl<ClassName, ParentClass>(this, pClass);            \
  }

#define OD_EXP_DEFINE_INIT_MEMBERS_GENERIC(ClassName, CREATE_CLASS_INSTANCE, CREATE_CLASS_INSTANCE2)   \
                                                                                                     \
/* Registers this class with ODA Platform.                                   */                      \
void ClassName::rxInit()                                                                             \
{                                                                                                    \
  if (!ClassName::g_pDesc) {                                                                         \
    ClassName::g_pDesc = CREATE_CLASS_INSTANCE;                                                      \
  } else {                                                                                           \
    ODA_ASSERT(("Class ["#ClassName"] is already initialized.",0));                                  \
    throw OdError(eExtendedError);                                                                   \
  }                                                                                                  \
}                                                                                                    \
void ClassName::rxInit(AppNameChangeFuncPtr pAppNameChangeCallback)                                  \
{                                                                                                    \
  if (!ClassName::g_pDesc) {                                                                         \
    ClassName::g_pDesc = CREATE_CLASS_INSTANCE2;                                                     \
  } else {                                                                                           \
    ODA_ASSERT(("Class ["#ClassName"] is already initialized.",0));                                  \
    throw OdError(eExtendedError);                                                                   \
  }                                                                                                  \
}                                                                                                    \
                                                                                                     \
/* Unregisters this class with ODA Platform.                                 */                      \
void ClassName::rxUninit()                                                                           \
{                                                                                                    \
  ClassName::g_pExpEntityDef = 0;                                                                    \
  if (ClassName::g_pDesc) {                                                                          \
    ::deleteOdRxClass(ClassName::g_pDesc);                                                           \
    ClassName::g_pDesc = 0;                                                                          \
  } else {                                                                                           \
    ODA_ASSERT(("Class ["#ClassName"] is not initialized yet.",0));                                  \
    throw OdError(eNotInitializedYet);                                                               \
  }                                                                                                  \
}                                                                                                    
                                                                                                     
#define OD_EXP_DEFINE_INIT_MEMBERS_GENERIC_MODEL_CREATE(ClassName)                                                \
OdSmartPtr<ClassName> ClassName::createObject(OdDAI::Model* model)                                   \
{                                                                                                    \
  if (!desc()) { throw OdError(eNotInitializedYet); }                                                \
  if (!model)  { return OdSmartPtr<ClassName>(); }                                                   \
  const OdDAI::Schema*  pModelSchema = model->underlyingSchema().get();                              \
  /*g_pExpEntityDef->parentSchema() == NULL in case when we have interoperable entity*/              \
  if (pModelSchema != g_pExpEntityDef->parentSchema() &&                                             \
      g_pExpEntityDef->parentSchema() != NULL)                                                       \
  { return OdSmartPtr<ClassName>(); }                                                                \
  OdSmartPtr<ClassName> createdObject = desc()->create();                                            \
  model->appendEntityInstance(createdObject);                                                        \
  return createdObject;                                                                              \
}                                                                                                  

#define OD_EXP_DEFINE_RTTI_MEMBERS(ClassName, ParentClass) \
  OD_EXP_DEFINE_RTTI_MEMBERS_GENERIC(OdRxClass, ClassName, ParentClass)

#define OD_EXP_DEFINE_INIT_MEMBERS(SchemaName,ClassName, ParentClass, pseudoConsFn, DwgVer,                \
                                 MaintVer, nProxyFlags, szDWGClassName,                       \
                                 szDxfName, szAppName, nCustomFlags)                          \
  OD_EXP_DEFINE_INIT_MEMBERS_GENERIC(                                                           \
      ClassName,                                                                              \
      (/*getOdDAIEntityClass*/::newOdRxClass(szDWGClassName, ParentClass::desc()/*, g_pSchemaDef*/, pseudoConsFn, DwgVer,              \
        MaintVer, nProxyFlags, szDxfName, szAppName, NULL, nCustomFlags)),                    \
      (/*getOdDAIEntityClass*/::newOdRxClass(szDWGClassName, ParentClass::desc()/*, g_pSchemaDef*/, pseudoConsFn, DwgVer,              \
        MaintVer, nProxyFlags, szDxfName, szAppName, pAppNameChangeCallback, nCustomFlags)))


//
#define OD_EXP_DEFINE_MEMBERS2(SchemaName,ClassName,ParentClass,pseudoConsFn,DwgVer,MaintVer,nProxyFlags,szDWGClassName,szDxfName,szAppName,nCustomFlags) \
                                                                                                     \
OD_EXP_DEFINE_RTTI_MEMBERS(ClassName,ParentClass)                                                      \
                                                                                                     \
OD_EXP_DEFINE_INIT_MEMBERS(SchemaName,ClassName,ParentClass,pseudoConsFn,                                         \
    DwgVer,MaintVer,nProxyFlags,szDWGClassName,szDxfName,szAppName,nCustomFlags)



#define OD_EXP_DEFINE_PSEUDOCONSTRUCTOR(ClassName,DOCREATE)                                       \
OdRxObjectPtr ClassName::pseudoConstructor() { return OdRxObjectPtr(DOCREATE(ClassName)); }       \


#define OD_EXP_CONS_DEFINE_MEMBERS_ALTNAME(SchemaName,ClassName,ParentClass,szClassName,DOCREATE)                 \
OD_EXP_DEFINE_MEMBERS2(SchemaName,ClassName,ParentClass,ClassName::pseudoConstructor,0,0,0,szClassName,OdString::kEmpty,OdString::kEmpty,0) \
OD_EXP_DEFINE_PSEUDOCONSTRUCTOR(ClassName,DOCREATE)

#define OD_EXP_CONS_DEFINE_MEMBERS(SchemaName,ClassName,ParentClass,DOCREATE)                     \
OD_EXP_CONS_DEFINE_MEMBERS_ALTNAME(SchemaName,ClassName,ParentClass,OD_T(#ClassName),DOCREATE)    \
OD_EXP_DEFINE_INIT_MEMBERS_GENERIC_MODEL_CREATE(ClassName)


#define OD_EXP_CONS_NON_INSTANTIABLE_DEFINE_MEMBERS(SchemaName,ClassName,ParentClass,DOCREATE)                                    \
OD_EXP_CONS_DEFINE_MEMBERS_ALTNAME(SchemaName,ClassName,ParentClass,OD_T(#ClassName),DOCREATE)    \

#define OD_EXP_HEADER_CONS_DEFINE_MEMBERS(SchemaName,ClassName,ParentClass,DOCREATE)              \
OD_EXP_CONS_DEFINE_MEMBERS_ALTNAME(SchemaName,ClassName,ParentClass,OD_T(#ClassName),DOCREATE)    \


#endif // _DAI_RTTI_H
