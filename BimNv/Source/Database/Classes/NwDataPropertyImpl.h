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

#ifndef __NWDATAPROPERTYIMPL_INCLUDED_
#define __NWDATAPROPERTYIMPL_INCLUDED_

#include "NwDataProperty.h"
#include "NwObjectImpl.h"
#include <memory>

class OdNwOptionData;
typedef std::weak_ptr<OdNwOptionData> OdNwOptionDataWeakPtr;

class OdNwDataPropertyImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwDataProperty)
public:
  OdNwDataPropertyImpl();
  virtual ~OdNwDataPropertyImpl();
  ODRX_DECLARE_MEMBERS(OdNwDataPropertyImpl);

  static OdNwDataPropertyImpl* getImpl(const OdNwDataProperty* pNwDataProperty);
  static OdNwDataPropertyImpl* getImpl(const OdRxObject* pRxDataProperty);

public:
  OdString getCombineName() const;
  OdString getDisplayName() const;
  OdString getName() const;
  NwDataType::Enum getDataType() const;
  OdResult getValue(OdNwVariant& val) const;

public:
  void setOptionData(OdNwOptionDataWeakPtr pOptionData);

private:
  OdNwOptionDataWeakPtr m_pOptionData;
};

typedef OdSmartPtr<OdNwDataPropertyImpl> OdNwDataPropertyImplPtr;

#endif //__NWDATAPROPERTYIMPL_INCLUDED_
