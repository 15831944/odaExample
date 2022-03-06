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

#ifndef __NWGEOMETRYCOMPRESSSETTINGSIMPL_H__
#define __NWGEOMETRYCOMPRESSSETTINGSIMPL_H__

#include "NwGeometryCompressSettings.h"
#include "NwObjectImpl.h"

class OdNwGeometryCompressSettingsImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwGeometryCompressSettings)
public:
  OdNwGeometryCompressSettingsImpl();
  virtual ~OdNwGeometryCompressSettingsImpl();
  ODRX_DECLARE_MEMBERS(OdNwGeometryCompressSettingsImpl);

  DrawableType drawableType() const override;
  OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const override;

public:
  static OdNwGeometryCompressSettingsImpl* getImpl(const OdNwGeometryCompressSettings* pNwBck);
  static OdNwGeometryCompressSettingsImpl* getImpl(const OdRxObject* pRxBck);
  void subSetDatabaseDefaults(OdNwDatabase* pDb, bool doSubents);

public:
  void setPrecision(double);
  double getPrecision() const;

  void setGeometryCompressedFlags(OdUInt32);
  OdUInt32 getGeometryCompressedFlags();

  void setGeometryVertexCompressed(bool);
  bool getGeometryVertexCompressed() const;

  void setGeometryNormalCompressed(bool);
  bool getGeometryNormalCompressed() const;

  void setGeometryColorCompressed(bool);
  bool getGeometryColorCompressed() const;

  void setGeometryTexCoordCompressed(bool);
  bool getGeometryTexCoordCompressed() const;

  void setGeometryLengthsCompressed(bool);
  bool getGeometryLengthsCompressed() const;

  void setGeometryIndicesCompressed(bool);
  bool getGeometryIndicesCompressed() const;

  bool getNormalsPrecisionReduced() const;
  void setNormalsPrecisionReducedFlags(const OdUInt8);
  OdUInt8 getNormalsPrecisionReducedFlags() const;
  
  bool getColorsPrecisionReduced() const;
  void setColorsPrecisionReducedFlags(const OdUInt8);
  OdUInt8 getColorsPrecisionReducedFlags() const;

  bool getTextureCoordinatesPecisionReduced() const;
  void setTextureCoordinatesPecisionReducedFlags(const OdUInt8);
  OdUInt8 getTextureCoordinatesPecisionReducedFlags() const;


protected:
  double m_fPrecision;
  OdUInt32  m_nGeometryCompressedFlags;
  OdUInt8  m_nNormalsPrecisionReducedFlags;
  OdUInt8  m_nColorsPrecisionReducedFlags;
  OdUInt8  m_nTextureCoordinatesPecisionReducedFlags;
};



#endif //__NWGEOMETRYCOMPRESSSETTINGSIMPL_H__
