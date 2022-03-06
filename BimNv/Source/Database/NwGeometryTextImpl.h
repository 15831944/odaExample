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

#ifndef __NWGEOMETRYTEXTIMPL_INCLUDED__
#define __NWGEOMETRYTEXTIMPL_INCLUDED__

#include "NwGeometryText.h"
#include "NwGeometryImpl.h"
#include "NwTextFontInfo.h"
#include "Ge/GeVector3d.h"

class OdNwGeometryTextImpl;


class OdNwGeometryTextImpl : public OdNwGeometryImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwGeometryText)
public:
  OdNwGeometryTextImpl();
  virtual ~OdNwGeometryTextImpl();
  ODRX_DECLARE_MEMBERS(OdNwGeometryTextImpl);

public:
  bool draw(OdGiWorldDraw* pWd) const override;

public:
  static OdNwGeometryTextImpl* getImpl(const OdNwGeometryText* pNwGeometry);
  static OdNwGeometryTextImpl* getImpl(const OdRxObject* pRxGeometry);

public:
  float getFirst() const;
  OdGePoint3d getLeftPoint() const;
  OdGePoint3d getRightPoint() const;
  OdGeVector3d getNormal() const;
  OdUInt32 getFontId() const;
  OdString getText() const;
  float getRotation() const;
  OdNwTextFontInfo getFont() const;
  OdNwObjectId getTextStyleId() const;
  float getScale() const;

  void setFirst(float val);
  void setLeftPoint(const OdGePoint3d& val);
  void setRightPoint(const OdGePoint3d& val);
  void setNormal(const OdGeVector3d& val);
  void setFontId(OdUInt32 val);
  void setText(const OdString& val);
  void setRotation(float val);
  void setTextStyle(OdNwObjectId val);
  void setScale(float val);

  OdGeExtents3d calculateBoundingBox() const override;

private:

  OdNwTextFontInfo convertTextStyleToFontInfo() const;

protected:
  float m_fFirst;
  OdGePoint3d m_ptLeftPoint;
  OdGePoint3d m_ptRightPoint;
  OdGeVector3d m_vNormal;
  OdUInt32 m_nFontId;
  OdString m_sText;
  float m_dRotation;
  OdNwObjectId m_TextStyleId;
  float m_dScale;
};

#endif //__NWGEOMETRYTEXTIMPL_INCLUDED__
