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
#ifndef __TNW_NWGRIDLINEIMPL_H__
#define __TNW_NWGRIDLINEIMPL_H__

#include "Grid/NwGridLine.h"
#include "NwObjectImpl.h"
#include "NwGridLineSegmentImpl.h"


typedef OdArray<OdNwGridLinePtr> OdNwGridLinePtrList;

class NWDBEXPORT OdNwGridLineImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwGridLine)
  OdNwGridLineSegmentPtrList m_gridLineSegmentList;
  OdString m_name;
  OdGePoint2d m_point;
  OdInt16 m_flag_1;
  OdInt16 m_flag_2;

public:
  OdNwGridLineImpl();
  virtual ~OdNwGridLineImpl();
  ODRX_DECLARE_MEMBERS(OdNwGridLineImpl);

  static OdNwGridLineImpl* getImpl(const OdNwGridLine*);
  static OdNwGridLineImpl* getImpl(const OdRxObject*);
  void setName(OdString name);
  void setPoint(OdGePoint2d p);
  void setFlags(OdInt16 flag_1, OdInt16 flag_2);

  const OdString getName() const;
  const OdGePoint2d getPoint() const;
  const OdInt16 getFlag1() const;
  const OdInt16 getFlag2() const;

  void addSegment(OdNwGridLineSegmentPtr lnsexgxp);
  OdResult getGridLineSegmentList(OdArray<OdNwGridLineSegmentPtr> & gridLineSegmentList) const;


};
typedef OdSmartPtr<OdNwGridLineImpl> OdNwGridLineImplPtr;

#endif
