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
#ifndef __NW_GEOMETRYCOMPRESSSTREAMLOADER_H__
#define __NW_GEOMETRYCOMPRESSSTREAMLOADER_H__

#include "NwStreamLoader.h"
#include "TD_PackPush.h"
#include "NwGeometryCompressSettings.h"

class OdNwGeometryCompressStreamLoader : public OdNwStreamLoader
{
public:
  OdNwGeometryCompressStreamLoader(const std::shared_ptr<OdNwStreamContext> &ctx);
  virtual ~OdNwGeometryCompressStreamLoader();
  static OdNwStreamLoaderPtr createStreamLoader(const std::shared_ptr<OdNwStreamContext> &ctx);
  virtual OdResult parseStream() override;

  
  float getPrecision() const;
  bool geGeometryCompressed() const;
  OdUInt32 getCompressionFlags() const;
  bool getCoordinatesPrecisionReduced() const;
  bool getNormalsPrecisionReduced() const;
  OdUInt8 getNormalsPrecisionReducedFlags() const;
  bool getColorsPrecisionReduced() const;
  OdUInt8 getColorsPrecisionReducedFlags() const;
  bool getUVCoordinatesPrecisionReduced() const;
  OdUInt8 getUVCoordinatesPrecisionReducedFlags() const;
  bool getStreamCorrect() const;

  OdNwGeometryCompressSettingsPtr getSettings() const;

private:
  OdUInt32 m_nFlags;
  OdUInt8  m_nNormalsFlags;
  OdUInt8  m_nColorsFlags;
  OdUInt8  m_nTextureCoordsFlags;
  float m_fPrecision;
  bool  m_bStreamCorrect;
};

typedef std::shared_ptr<OdNwGeometryCompressStreamLoader> OdNwGeometryCompressStreamLoaderPtr;
typedef std::weak_ptr<OdNwGeometryCompressStreamLoader> OdNwGeometryCompressStreamLoaderWeakPtr;

#include "TD_PackPop.h"

#endif // __NW_GEOMETRYCOMPRESSSTREAMLOADER_H__
