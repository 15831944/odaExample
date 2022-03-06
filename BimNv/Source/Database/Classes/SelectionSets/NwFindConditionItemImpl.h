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

#ifndef __NW_FIND_CONDITION_ITEM_IMPL_H__
#define __NW_FIND_CONDITION_ITEM_IMPL_H__

#include "NwObjectImpl.h"
#include "SelectionSets/NwFindConditionItem.h"
#include "NwName.h"
#include "NwData.h"

class NWDBEXPORT OdNwFindConditionItemImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwFindConditionItem)
  OdNwNamePtr m_pCategory;
  OdNwNamePtr m_pProperty;
  bool m_pruneBelowResult;
  NwSelectionFindConditionType::Enum m_condition;
  OdNwDataPtr m_pValue;
  NwSelectionFindConditionFlags::Enum m_flags;

  ODRX_DECLARE_MEMBERS(OdNwFindConditionItemImpl);
public:
  static OdNwFindConditionItemImpl* getImpl(const OdNwFindConditionItem*);
  static OdNwFindConditionItemImpl* getImpl(const OdRxObject*);

  OdNwNamePtr getCategory() const;
  OdNwNamePtr getProperty() const;
  NwSelectionFindConditionFlags::Enum getFlags() const;
  NwSelectionFindConditionType::Enum getCondition() const;

  OdNwDataPtr getValue() const;

  void setCategory(OdNwNamePtr name);

  void setProperty(OdNwNamePtr name);

  void setFlags(NwSelectionFindConditionFlags::Enum flags);

  void setCondition(NwSelectionFindConditionType::Enum enm);
  void setFlagPruneBelowResult(bool);

  void setValue(OdNwDataPtr data);
  bool isFlagSet(NwSelectionFindConditionFlags::Enum flag);
};


#endif /* __NW_FIND_CONDITION_ITEM_IMPL_H__ */
