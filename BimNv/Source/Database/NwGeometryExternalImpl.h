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

#ifndef __TNW_GEOMETRYEXTERNAL_IMPL_
#define __TNW_GEOMETRYEXTERNAL_IMPL_

#include "NwGeometryExternal.h"
#include "NwGeometryImpl.h"
#include "Ge/GeVector3d.h"

class OdNwGeometryExternalImpl;


class OdNwGeometryExternalImpl : public OdNwGeometryImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwGeometryExternal)
public:
  OdNwGeometryExternalImpl();
  virtual ~OdNwGeometryExternalImpl();
  ODRX_DECLARE_MEMBERS(OdNwGeometryExternalImpl);

  bool draw(OdGiWorldDraw* pWd) const override;

public:
  static OdNwGeometryExternalImpl* getImpl(const OdNwGeometryExternal* pNwGeometry);
  static OdNwGeometryExternalImpl* getImpl(const OdRxObject* pRxGeometry);

public:
  const OdString getKey() const;
  const OdString getName() const;
  const OdString getReference() const;
  void getSchemaData(OdInt32& val1, OdGUID& val2, OdInt32& val3) const;
  const OdUInt32 getPointsFlags() const;
  const OdGePoint3d getTopLeft() const;
  const OdGePoint3d getBottomRight() const;
  const OdUInt32 getFlags() const;
  const OdUInt32 getType() const;

  void setKey(const OdString& val);
  void setName(const OdString& val);
  void setReference(const OdString& val);
  void setSchemaData(const OdInt32 val1, const OdGUID& val2, const OdInt32 val3);
  void setPointsFlags(const OdUInt32 val);
  void setTopLeft(const OdGePoint3d& val);
  void setBottomRight(const OdGePoint3d& val);
  void setFlags(const OdUInt32 val);
  void setType(const OdUInt32 val);

  OdGeExtents3d calculateBoundingBox() const override;

protected:
  OdString m_sKey;
  OdString m_sName;
  OdString m_sReference;
  
  OdInt32 m_nSchemaField1;
  OdGUID m_nSchemaField2;
  OdInt32 m_nSchemaField3;

  OdUInt32 m_nPointFlags;
  OdGePoint3d m_ptTopLeft;
  OdGePoint3d m_ptBottomRight;
  OdUInt32 m_nFlags;
  OdUInt32 m_nType;
};

#endif //__TNW_GEOMETRYEXTERNAL_IMPL_
