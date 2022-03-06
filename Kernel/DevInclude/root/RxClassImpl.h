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

#ifndef _ODRXCLASSIMPL_H_INCLUDED_
#define _ODRXCLASSIMPL_H_INCLUDED_

#include "RxObject.h"
#include "OdString.h"
#include "RxMember.h"
#include "RxAttribute.h"
#include "TD_PackPush.h"

class OdRxOverruleIterator;

class FIRSTDLL_EXPORT OdRxClassImpl
{
  friend class OdRxClass;
  friend class OdRxOverruleInternals;
  friend class OdRxMemberCollectionImpl;
  friend FIRSTDLL_EXPORT void odrxSetMemberConstructor(OdRxClass*, OdRxMemberCollectionConstructorPtr, void*);
  class ExtEntry
  {
  public:
    ExtEntry(OdRxClass* pProtocolClass, OdRxObject* pProtocolObject);
    static ExtEntry* find(ExtEntry* pFirstEntry, const OdRxClass* pProtocolClass);

    OdRxClassPtr  m_pProtocolClass;
    OdRxObjectPtr m_pProtocolObject;
    ExtEntry*     m_pNextEntry;
  };
protected:
  ExtEntry*   m_pFirstEntry;
  OdRxModule* m_pModule;
  OdRxClass*  m_pParent;
  OdRxOverruleIterator* m_overrules[kTotalOverrules];
  OdString m_szName;
  static const char* m_pStr;  // To use in conversion to ANSI
  OdPseudoConstructorType m_pConstr;
  OdString      m_szDxfName;
  OdString      m_szAppName;
  AppNameChangeFuncPtr m_appNameChangeFunc;
  OdUInt32      m_proxyFlags;
  OdUInt32      m_customFlags;
  OdUInt16      m_maintVer;
  OdUInt16      m_dwgVer;
  OdRxMemberCollectionConstructorPtr m_pMembersConstr;
  void* m_userdata;
  OdRxMemberCollection* m_members;
  OdRxAttributeCollection m_attributes;
public:
  OdRxClassImpl();
  ~OdRxClassImpl();

  void reset();
  void init(OdRxModule* pModule, OdRxClass* pParent,
            OdPseudoConstructorType pConstr,
            const OdString& name,
            const OdString& dxfName = OdString::kEmpty,
            const OdString& appName = OdString::kEmpty,
            AppNameChangeFuncPtr appNameChangeFunc = 0,
            OdDb::DwgVersion dwgVer = (OdDb::DwgVersion)0,
            OdDb::MaintReleaseVer maintVer = OdDb::kMRelease0,
            OdUInt32 nProxyFlags = 0,
            OdUInt32 nCustomFlags = 0,
            OdRxMemberCollectionConstructorPtr memberConstruct = 0,
            void* userData = 0
  );
  static OdRxClassImpl* getImpl(OdRxClass* pClass) { return pClass->m_pImpl; }
  static const OdRxClassImpl* getImpl(const OdRxClass* pClass) { return pClass->m_pImpl; }
  void setDxfName(const OdString& classDxfName) { m_szDxfName = classDxfName; }
  void setName(const OdString& className) { m_szName = className; }
  void setAppName(const OdString& appName) { m_szAppName = appName; }
  void setProxyFlags(OdUInt32 value) { m_proxyFlags = value; }
  void setClassVersion(int DwgVer, int MaintVer)
  {
    m_dwgVer = OdDb::DwgVersion(DwgVer);
    m_maintVer = OdDb::MaintReleaseVer(MaintVer);
  }
  OdRxOverruleIterator* getOverrule(OverrulingType t) const
  {
    return m_overrules[t];
  }
  void setOverrule(OdRxOverruleIterator* pIt, OverrulingType t)
  {
    m_overrules[t] = pIt;
  }
  void deleteMember(const OdRxMember*);
};

#include "TD_PackPop.h"

#endif // _ODRXCLASSIMPL_H_INCLUDED_
