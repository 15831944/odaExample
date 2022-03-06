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

#ifndef _ODDB_RASTERIMAGEIMPL_INCLUDED_
#define _ODDB_RASTERIMAGEIMPL_INCLUDED_

#include "DbEntityImpl.h"
#include "DbRasterImage.h"
#include "DbSystemInternals.h"

class OdGiGeometry;

class ISM_EXPORT OdDbRasterImageImpl : public OdDbEntityImpl
{
  static OdDbRasterImageImpl* getImpl(const OdDbRasterImage *pObj)
  { return (OdDbRasterImageImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
  OdInt32             m_ClassVersion;

  OdGeVector2d        m_Size;

  OdGePoint3d         m_origin;
  OdGeVector3d        m_uVector;
  OdGeVector3d        m_vVector;

  OdDbHardPointerId   m_ImageDefId;
  OdDbHardOwnershipId m_ReactorId;
  OdGePoint2dArray    m_ClipPoints;
  OdGePoint2dArray    m_ClipPointsCache;

  OdUInt8             m_Brightness;
  OdUInt8             m_Contrast;
  OdUInt8             m_Fade;

  bool                m_isClipInverted;

  OdUInt8             m_DisplayProps; 
  bool                m_Clipping;
  
public:
  OdDbRasterImageImpl();
  OdGeVector3d uWidth() const { return m_uVector * m_Size.x; };
  OdGeVector3d vHeight() const { return m_vVector * m_Size.y; }

  void setCastShadows(bool) {}
  bool castShadows() const { return false; }

  void setReceiveShadows(bool) {}
  bool receiveShadows() const { return false; }

  OdResult getVertices(const OdDbRasterImage *pImage, OdGePoint3dArray& pnts, bool bLoadIfNeed = true);
protected:
  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler) const;
  
  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;

  void setClipBoundaryToWholeImage();
  void audit(OdDbAuditInfo* pAuditInfo);

  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  void convertInvertedClip(OdGePoint2dArray& clipPoints);

  friend class OdDbRasterImage;
};


inline void oddbDrawImageFrame(const OdDbEntity *pEntity, OdGiGeometry &geom, OdGiSubEntityTraits &traits, OdGiRegenType regenType,
  const OdGePoint3d *pFramePoints, OdUInt32 nFramePoints, bool bDrawFrame, OdGsMarker baseSubEntMarker = -1)
{
  if (!bDrawFrame)
  {
    if ((regenType == kOdGiForExplode) ||
      (regenType == kOdGiSaveWorldDrawForProxy))
      return;
    traits.setTransparency(OdCmTransparency(OdUInt8(0u))); // Don't know why it is need, but acad does
    traits.setSelectionGeom(true);
  }
#if 0
  geom.polyline((OdInt32)nFramePoints, pFramePoints, NULL, baseSubEntMarker);
#else // #CORE-14753 : Acad apply linetype onto each segment separately.
  for (OdUInt32 nPt = 0; nPt < nFramePoints - 1; nPt++)
    geom.polyline(2, pFramePoints + nPt, NULL, (baseSubEntMarker > kNullSubentIndex) ? (baseSubEntMarker + 1) : baseSubEntMarker);
#endif
  if (!bDrawFrame)
  {
    traits.setTransparency(pEntity->transparency());
    traits.setSelectionGeom(false);
  }
}

#endif // _ODDB_RASTERIMAGEIMPL_INCLUDED_
