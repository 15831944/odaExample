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

#ifndef __NWGEOMETRYELLIPTICALSHAPEIMPL_INCLUDED__
#define __NWGEOMETRYELLIPTICALSHAPEIMPL_INCLUDED__

#include "NwGeometryEllipticalShape.h"
#include "NwGeometryImpl.h"

class OdNwGeometryEllipticalShapeImpl;


class OdNwGeometryEllipticalShapeImpl : public OdNwGeometryImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwGeometryEllipticalShape)
public:
  OdNwGeometryEllipticalShapeImpl();
  virtual ~OdNwGeometryEllipticalShapeImpl();
  ODRX_DECLARE_MEMBERS(OdNwGeometryEllipticalShapeImpl);

public:
  bool draw(OdGiWorldDraw* pWd) const override;

public:
  static OdNwGeometryEllipticalShapeImpl* getImpl(const OdNwGeometryEllipticalShape* pNwGeometry);
  static OdNwGeometryEllipticalShapeImpl* getImpl(const OdRxObject* pRxGeometry);

  static OdNwGeometryEllipticalShapePtr createCircle(const OdGePoint3d& center, double radius, const OdGeVector3d& normal);

public:
  const OdUInt32 getFlags() const;
  OdGePoint3d getOrigin() const;

  double getRadius() const;
  inline double getXRadius() const { return getRadius(); }//deprecated
  inline double getYRadius() const { return 0; }//deprecated

  OdGeVector3d getXVector() const;
  OdGeVector3d getYVector() const;

public:
  void setFlags(const OdUInt32 val);
  void setOrigin(const OdGePoint3d& val);

  void setXVector(const OdGeVector3d& val);
  void setYVector(const OdGeVector3d& val);

  void setRadius(const double& val);

public:
  OdGeExtents3d calculateBoundingBox() const override;

protected:
  OdUInt32 m_nFlags;
  OdGePoint3d m_ptOrigin;
  double m_dRadius;

  OdGeVector3d m_vxVector;
  OdGeVector3d m_vyVector;
};

#endif //__NWGEOMETRYELLIPTICALSHAPEIMPL_INCLUDED__
