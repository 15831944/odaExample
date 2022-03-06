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

#ifndef __NW_SELECTION_SET_ITEM_IMPL_H__
#define __NW_SELECTION_SET_ITEM_IMPL_H__

#include "NwSavedItemImpl.h"
#include "SelectionSets/NwSelectionSetItem.h"

typedef OdSmartPtr<OdNwFindSelection> OdNwFindSelectionPtr;

class OdNwFindSelection;
class OdNwSelectionSetItemImpl : public OdNwSavedItemImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwSelectionSetItem)
  ODRX_DECLARE_MEMBERS(OdNwSelectionSetItemImpl);
public:
  OdNwSelectionSetItemImpl();
  virtual ~OdNwSelectionSetItemImpl();

  static OdNwSelectionSetItemImpl* getImpl(const OdNwSelectionSetItem*);
  static OdNwSelectionSetItemImpl* getImpl(const OdRxObject*);
  OdNwObjectIdArray getModelItems() const;
  void setModelItem(OdNwObjectIdArray pPathLinkList);
  NwSelectionSetItemType::Enum getItemType() const;
  void setItemType(NwSelectionSetItemType::Enum typ);
  OdNwFindSpecPtr getFindSpec() const;
  void setFindSpec(OdNwFindSpecPtr findSpec);
  void setStr(OdString & str);
  void setTime(tm & t);
  const OdString &getAStr() const;
  const tm & getATime() const;
  OdNwFindSelectionPtr getFindSelection() const;
  void setFindSelection(OdNwFindSelectionPtr pFindSelection);
private:
  OdNwFindSelectionPtr m_pFindSelection;
  OdNwObjectIdArray m_pPathLinkList;
  NwSelectionSetItemType::Enum m_itemType;
  OdNwFindSpecPtr m_pFindSpec;
  OdString m_astr;
  tm m_atime;
};



#endif
