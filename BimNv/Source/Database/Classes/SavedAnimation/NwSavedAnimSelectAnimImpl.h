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

#ifndef __NW_SAVEDANIMSELECTANIM_IMPL_H__
#define __NW_SAVEDANIMSELECTANIM_IMPL_H__

#include "NwObjectImpl.h"
#include "NwSavedAnimSelectAnim.h"
#include "NwSavedAnimGroupImpl.h"
class OdNwFindSelection;
typedef OdSmartPtr<OdNwFindSelection> OdNwFindSelectionPtr;

class NWDBEXPORT OdNwSavedAnimSelectAnimImpl : public OdNwSavedAnimGroupImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwSavedAnimSelectAnim)
  
  ODRX_DECLARE_MEMBERS(OdNwSavedAnimSelectAnimImpl);
public:
  OdNwSavedAnimSelectAnimImpl();
  virtual ~OdNwSavedAnimSelectAnimImpl();
  static OdNwSavedAnimSelectAnimImpl* getImpl(const OdNwSavedAnimSelectAnim *);
  static OdNwSavedAnimSelectAnimImpl* getImpl(const OdRxObject *);
  OdNwFindSelectionPtr getFindSelection() const;
  void setFindSelection(OdNwFindSelectionPtr pFindSelection);
private:
  OdNwObjectIdArray m_ModelItems;
  OdNwFindSelectionPtr m_pFindSelection;
  OdString m_SelectionPath;
};

typedef OdSmartPtr<OdNwSavedAnimSelectAnimImpl> OdNwSavedAnimSelectAnimImplPtr;

#endif /* __NW_SAVEDANIMSELECTANIM_IMPL_H__ */
