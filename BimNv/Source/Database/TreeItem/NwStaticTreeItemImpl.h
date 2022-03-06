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

#ifndef __NWSTATICTREEITEMIMPL_INCLUDED__
#define __NWSTATICTREEITEMIMPL_INCLUDED__

#include "NwStaticTreeItem.h"
#include "NwTreeItemImpl.h"

class NWDBEXPORT OdNwStaticTreeItemImpl : public OdNwTreeItemImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwStaticTreeItem)
public:
  OdNwStaticTreeItemImpl();
  virtual ~OdNwStaticTreeItemImpl();
  ODRX_DECLARE_MEMBERS(OdNwStaticTreeItemImpl);

  static OdNwStaticTreeItemImpl* getImpl(const OdNwStaticTreeItem* pNwStaticTreeItem);
  static OdNwStaticTreeItemImpl* getImpl(const OdRxObject* pRxStaticTreeGroup);

public:
  OdResult getChildren(std::vector<OdNwObjectPtr>& arr) const override;

public:
  OdResult setChildren(const std::vector<OdNwObjectPtr>& vChildrens);

protected:
  OdResult deleteChildren(bool bNested) override;
  OdResult initChildren(const std::vector<OdNwObjectPtr>& vChildrens);

private:
  std::vector<OdNwObjectPtr> m_vChildren;
};



#endif //__NWSTATICTREEITEMIMPL_INCLUDED__
