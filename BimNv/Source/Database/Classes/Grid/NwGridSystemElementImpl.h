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

#ifndef __TNW_GRIDSYSTEMELEMENTIMPL_H__
#define __TNW_GRIDSYSTEMELEMENTIMPL_H__
#include "Grid/NwGridSystemElement.h"
#include "NwObjectImpl.h"
#include "NwGridSystemImpl.h"


class NWDBEXPORT OdNwGridSystemElementImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwGridSystemElement)
  OdArray<OdNwGridSystemPtr> m_gridSystemList;
  OdUInt32 m_GridSystemLock1;
  OdUInt32 m_GridSystemLock2;
public:
  OdNwGridSystemElementImpl();
  virtual ~OdNwGridSystemElementImpl();
  ODRX_DECLARE_MEMBERS(OdNwGridSystemElementImpl);

  static OdNwGridSystemElementImpl* getImpl(const OdNwGridSystemElement*);
  static OdNwGridSystemElementImpl* getImpl(const OdRxObject*);

public:
  OdResult getGridSystemList(OdArray<OdNwGridSystemPtr>& ) const;
  void addGridSystem(OdNwGridSystemPtr);
  void setGridSystemLock1(OdUInt32 lock);
  void setGridSystemLock2(OdUInt32 lock);
  OdUInt32 getGridSystemLock1() const;
  OdUInt32 getGridSystemLock2() const;
};



#endif
