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

#ifndef __TNW_GRIDSYSTEMIMPL_H__
#define __TNW_GRIDSYSTEMIMPL_H__

#include "Grid/NwGridSystem.h"
#include "NwObjectImpl.h"
#include "NwGridLineImpl.h"
#include "NwGridLevelImpl.h"


class NWDBEXPORT OdNwGridSystemImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwGridSystem)
  OdNwGridLinePtrList m_gridLineList;
  OdNwGridLevelPtrList m_gridLevelList;
  OdString m_name;
  OdGeMatrix3d m_matrix;
  OdUInt32 m_IsGridLevelZero;
public:
  OdNwGridSystemImpl();
  virtual ~OdNwGridSystemImpl();
  ODRX_DECLARE_MEMBERS(OdNwGridSystemImpl);

  static OdNwGridSystemImpl* getImpl(const OdNwGridSystem* pNwGridSystem);
  static OdNwGridSystemImpl* getImpl(const OdRxObject* pRxGridSystem);

public:
  OdResult getGridLineList(OdArray<OdNwGridLinePtr> & gridLineList) const;
  OdResult getGridLevelList(OdArray<OdNwGridLevelPtr> & gridLevelList) const;

  void addGridLine(OdNwGridLinePtr);
  void addGridLevel(OdNwGridLevelPtr);
  void setName(const OdString & name);
  void setMatrix(OdGeMatrix3d m);
  OdString getName();
  const OdGeMatrix3d & getMatrix() const;
  OdGePoint3d getOrigin() const;
  OdGeVector3d getUpVector() const;
  void setGridLevelZeroFlag(OdUInt32 value);
  OdUInt32 getGridLevelZeroFlag() const;
};



#endif
