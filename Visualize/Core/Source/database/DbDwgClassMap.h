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

// OdTvDbDwgClassMap.h: interface for the OdTvDbDwgClassMap class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _ODDBDWGCLASSESMAP_H_INCLUDED_
#define _ODDBDWGCLASSESMAP_H_INCLUDED_

#include "RxClassImpl.h"
#include "StaticRxObject.h"
#include "DwgDeclareMembers.h"
#include "OdHeap.h"

FIRSTDLL_EXPORT OdRxModule* odrxLoadingModule();

class TOOLKIT_EXPORT OdTvDbDwgClassMap  
{
public:
  class Entry : public OdStaticRxObject<OdObjectWithImpl<OdRxClass, OdRxClassImpl> >{
  public:
    Entry() { registered = 0; }
    OdRxClass* registered;
  };
private:
  static const Entry* cast(const OdRxClass* pClass)
  {
    return static_cast<const Entry*>(pClass);
  }
  static Entry* cast(OdRxClass* pClass)
  {
    return static_cast<Entry*>(pClass);
  }
public:
	OdTvDbDwgClassMap();
	~OdTvDbDwgClassMap();
  static void init();
  static void uninit();
  OdUInt16 dwgType(const OdRxClass* pClass) const;
  OdRxClass* getClass(OdUInt16 nDwgType) const;
  OdRxClass* getDesc(OdUInt16 nDwgType) const;
  bool has(OdRxClass* pClass) const;

  void initEntry(OdUInt16 dwgType,
    OdRxClass* pParent,
    OdPseudoConstructorType pConstr,
    const OdString& name,
    const OdString& dxfName,
    OdDb::DwgVersion dwgVer,
    OdDb::MaintReleaseVer maintVer,
    OdUInt32 nProxyFlags,
    OdUInt32 nCustomFlags
    );

  void uninitEntry(OdUInt16 dwgType);

private:
  OdString s_ObjectDBX_Classes;
  Entry m_dbDwgClassMap[kOdDbDwgClassMapSize_WithProxy];
};

TOOLKIT_EXPORT OdTvDbDwgClassMap& odTvDbDwgClassMap();


#define DWGMAP_DEFINE_MEMBERS_BASE(DwgType, ClassName, BaseClassName, DwgVer, MaintVer, DxfName, ProxyFlags, CustomFlags) \
                                                                              \
  OdRxClass* OdTvDb##ClassName::isA() const { return desc(); }                  \
                                                                              \
  OdRxObject* OdTvDb##ClassName::queryX(const OdRxClass* pClass) const {        \
    return ::odQueryXImpl<OdTvDb##ClassName, OdTvDb##BaseClassName>(this, pClass);\
  }                                                                           \
                                                                              \
  void OdTvDb##ClassName::rxInit() {\
    ::odTvDbDwgClassMap().initEntry(DwgType, OdTvDb##BaseClassName::desc(), OdTvDb##ClassName::pseudoConstructor,\
      OD_CONCAT("AcTvDb", #ClassName), OD_T(#DxfName), OdDb::DwgVer, OdDb::MaintVer, ProxyFlags, CustomFlags);\
  }\
  void OdTvDb##ClassName::rxUninit() {\
    ::odTvDbDwgClassMap().uninitEntry(DwgType);\
  }

#define DWGMAP_DEFINE_MEMBERS(DwgType, ClassName, BaseClassName, DwgVer, MaintVer, DxfName, ProxyFlags, CustomFlags) \
  DWGMAP_DEFINE_MEMBERS_BASE(DwgType, ClassName, BaseClassName, DwgVer, MaintVer, TV_DXF_##DxfName, ProxyFlags, CustomFlags) \
  OdRxObjectPtr OdTvDb##ClassName::pseudoConstructor() { return OdObjectWithImpl<OdTvDb##ClassName,OdTvDb##ClassName##Impl>::createObject(); }\

#define DWGMAP_NO_CONS_DEFINE_MEMBERS(DwgType, ClassName, BaseClassName, DwgVer, MaintVer, DxfName, ProxyFlags, CustomFlags) \
  DWGMAP_DEFINE_MEMBERS_BASE(DwgType, ClassName, BaseClassName, DwgVer, MaintVer, TV_DXF_##DxfName, ProxyFlags, CustomFlags) \
  OdRxObjectPtr OdTvDb##ClassName::pseudoConstructor() { throw OdError(eNotApplicable); }\



#endif // _ODDBDWGCLASSESMAP_H_INCLUDED_
