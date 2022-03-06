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

#ifndef __NWTREEITEMIMPL_INCLUDED__
#define __NWTREEITEMIMPL_INCLUDED__

#include "NwTreeItem.h"
#include "NwBaseTreeItemImpl.h"
#include "Ge/GeExtents3d.h"

class NWDBEXPORT OdNwTreeItemImpl : public OdNwBaseTreeItemImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwTreeItem)
public:
  OdNwTreeItemImpl();
  virtual ~OdNwTreeItemImpl();
  ODRX_DECLARE_MEMBERS(OdNwTreeItemImpl);

  static OdNwTreeItemImpl* getImpl(const OdNwTreeItem* pNwTreeItem);
  static OdNwTreeItemImpl* getImpl(const OdRxObject* pRxBaseTreeItem);

public:
  inline OdGeExtents3d& getBoundingBox() { return m_boundingBox; }
  inline const OdGeExtents3d& getBoundingBox() const { return m_boundingBox; }
  virtual OdResult getChildren(std::vector<OdNwObjectPtr>& arr) const = 0;

public:
  virtual OdResult update();
  virtual OdResult deleteChildren(bool bNested = true) = 0;

protected:
  OdGeExtents3d m_boundingBox;
};



#endif //__NWTREEITEMIMPL_INCLUDED__
