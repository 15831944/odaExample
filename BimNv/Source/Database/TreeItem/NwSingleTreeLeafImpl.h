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

#ifndef __NWSINGLETREELEAFIMPL_INCLUDED__
#define __NWSINGLETREELEAFIMPL_INCLUDED__

#include "NwSingleTreeLeaf.h"
#include "NwTreeItemImpl.h"

class NWDBEXPORT OdNwSingleTreeLeafImpl : public OdNwTreeItemImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwSingleTreeLeaf)
public:
  OdNwSingleTreeLeafImpl();
  virtual ~OdNwSingleTreeLeafImpl();
  ODRX_DECLARE_MEMBERS(OdNwSingleTreeLeafImpl);

  static OdNwSingleTreeLeafImpl* getImpl(const OdNwSingleTreeLeaf* pNwSingleTreeLeaf);
  static OdNwSingleTreeLeafImpl* getImpl(const OdRxObject* pRxDynamicTreeGroup);

public:
  OdResult getChildren(std::vector<OdNwObjectPtr>& arr) const override { return eNotApplicable; }
  OdNwObjectId getFragment() const;

public:
  OdResult setFragment(const OdNwObjectId& fragId);

public:
  OdResult update() override;
  OdResult deleteChildren(bool bNested) override;

private:
  OdNwObjectId m_fragmentId;
};



#endif //__NWSINGLETREELEAFIMPL_INCLUDED__
