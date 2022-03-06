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

#ifndef __NW_FIND_SPEC_IMPL_H__
#define __NW_FIND_SPEC_IMPL_H__
#include "NwObjectImpl.h"
#include "SelectionSets/NwFindSpec.h"

class OdNwFindSelection;
typedef OdSmartPtr<OdNwFindSelection> OdNwFindSelectionPtr;

class NWDBEXPORT OdNwFindSpecImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwFindSpec)
  ODRX_DECLARE_MEMBERS(OdNwFindSpecImpl);
public:
  static OdNwFindSpecImpl* getImpl(const OdNwFindSpec*);
  static OdNwFindSpecImpl* getImpl(const OdRxObject*);
  void addFindCondition(OdNwFindConditionItemPtr pFindConditionItem);
  void setMode(NwSelectionFindConditionMode::Enum mode);
  void setPruneBelow(OdInt32 flag);
  bool isPruneBelow() const;
  OdResult getFindConditionList(OdNwFindConditionList & findConditionList);
  NwSelectionFindConditionMode::Enum getMode() const;
  OdNwFindSelectionPtr getFindSelection() const;
  void setFindSelection(OdNwFindSelectionPtr);
private:
  OdNwFindConditionList m_findConditionList;
  NwSelectionFindConditionMode::Enum m_mode;
  bool m_pruneBelow;
  OdNwFindSelectionPtr m_pFindSelection;

};



#endif // __NW_FIND_SPEC_IMPL_H__

