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

#ifndef _ODDBRASTERIMAGEDEFIMPL_INCLUDED_
#define _ODDBRASTERIMAGEDEFIMPL_INCLUDED_


#include "DbSystemInternals.h"
#include "DbRasterImageDef.h"
#include "Ge/GeVector2d.h"
#include "FileDependency.h"
#include "DbObjectImpl.h"

class OdDbRasterImageDefImpl : public OdDbObjectImpl
{
  friend OdResult OdDbRasterImageDef::dxfInFields(OdDbDxfFiler* pFiler);
  friend OdGiRasterImagePtr OdDbRasterImageDef::image(bool bLoad);
protected:
  // Cashed data used when image is unloaded
	OdGeVector2d        m_size;
	OdGeVector2d        m_pixelSize;
  OdUInt8             m_resUnits;
  // End of cashed data
  bool                m_bImageLoaded;
public:
  OdGiRasterImagePtr  m_pImage;
  bool                m_bNotFound;
  bool                m_bDependencyCreated;
  OdInt32             m_classVer;
  OdDb::FileDependency m_FilePath;
  OdString            m_ActivePath;

  // loaded image

public:
  OdDbRasterImageDefImpl();

  void audit(OdDbAuditInfo* pAuditInfo);

  bool isLoaded() const { return m_bImageLoaded; }
  const OdGeVector2d& size() const { return m_size; }
  const OdGeVector2d& resolutionMMPerPixel() const { return m_pixelSize; }
  OdDbRasterImageDef::Units resolutionUnits() const { return OdDbRasterImageDef::Units(m_resUnits); }
  void setResolutionUnits( OdGiRasterImage::Units unit )  { m_resUnits = OdUInt8(unit); }
  void setResolutionMMPerPixel( const OdGeVector2d& mmPerPixel )
  {m_pixelSize = mmPerPixel;}

  void setImage(OdGiRasterImage* pImage);
  OdResult load();

  void unload()
  {
    m_bImageLoaded = false;
    m_bNotFound = false;
    m_pImage.release();
  }

  static OdDbRasterImageDefImpl* getImpl(const OdDbRasterImageDef *pObj)
  { return (OdDbRasterImageDefImpl*)OdDbSystemInternals::getImpl(pObj);}

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
};

#endif // _ODDBRASTERIMAGEDEFREACTORIMPL_INCLUDED_
