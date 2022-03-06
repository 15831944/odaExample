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

#ifndef __NW_MODEL_BASE_IMPL_H__
#define __NW_MODEL_BASE_IMPL_H__

#include "NwModelBase.h"
#include "NwObjectImpl.h"
#include "NwExport.h"

class OdNwName;
typedef OdSmartPtr<OdNwName> OdNwNamePtr;

class NWDBEXPORT OdNwModelBaseImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwModelBase)
public:
  OdNwModelBaseImpl();
  virtual ~OdNwModelBaseImpl();
  ODRX_DECLARE_MEMBERS(OdNwModelBaseImpl);

public:
  static OdNwModelBaseImpl* getImpl(const OdNwModelBase* pNwSB);
  static OdNwModelBaseImpl* getImpl(const OdRxObject* pRxSB);

  inline OdString getUserName() const { return m_userName; }
  OdNwNamePtr getClassNameInternal() const;

  OdString getClassName() const;
  OdString getClassDisplayName() const;

public:
  inline void setUserName(const OdString& name) { m_userName = name; }
  void setClassNameInternal(OdNwNamePtr pName);

  void setClassName(const OdString& name);
  void setClassDisplayName(const OdString& displayName);

protected:
  OdString m_userName;
  OdNwNamePtr m_pClassNameInternal;
};

typedef OdSmartPtr<OdNwModelBaseImpl> OdNwModelBaseImplPtr;

#endif //__NW_MODEL_BASE_IMPL_H__
