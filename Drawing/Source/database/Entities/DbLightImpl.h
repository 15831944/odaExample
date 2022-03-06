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


#ifndef __OD_DB_LIGHT_IMPL__
#define __OD_DB_LIGHT_IMPL__

#include "DbEntityImpl.h"
#include "DbLight.h"
#include "DbLightIes.h"

class OdDbLightImpl : public OdDbEntityImpl
{
  OdUInt32                           m_nVersion; // "version number", stored in both dxf and dwg
  OdString                           m_name;
  OdGiDrawable::DrawableType         m_lightType;
  bool                               m_bOn;
  bool                               m_bPlotGlyph; // two bools are not enough to create bitfields :)
  OdCmColor                          m_color;    
  double                             m_dIntensity;
  OdGePoint3d                        m_position;
  OdGePoint3d                        m_target;
  OdGiLightAttenuation               m_attenuation;
  double                             m_dHotspot;
  double                             m_dFalloff;
  OdGiShadowParameters               m_shadowParams;
  bool                               m_bPhotometricData;
  OdDbLight::PhysicalIntensityMethod m_physIntMethod;
  double                             m_dPhysInt;
  double                             m_dIllumDist;
  OdDbLight::LampColorType           m_lampColorType;
  double                             m_dLampColorTemp;
  OdDbLight::LampColorPreset         m_lampColorPres;
  OdGiColorRGB                       m_lampColor;
  OdString                           m_webFile;
  OdGeVector3d                       m_webRotation;
  bool                               m_bHasTarget;
  OdDbLight::GlyphDisplayType        m_glyphType;
  double                             m_unknownDouble1_GC49;
  double                             m_unknownAngle1_GC50;
  double                             m_unknownAngle2_GC51;
  double                             m_unknownAngle3_GC53;
  double                             m_unknownAngle4_GC54;
  double                             m_unknownAngle5_GC55;
  // IESNA processing
  enum WebFileState
  {
    kWebFileNotLoaded = -1,
    kWebFileMissing   =  0,
    kWebFileLoaded    =  1
  }                                  m_webFileState;
  OdDbLightIes                       m_webFileData;
  // Runtime flags
  bool                               m_bHighlighted;

  static OdDbLightImpl* getImpl(const OdDbLight *pObj)
  { return (OdDbLightImpl*)OdDbSystemInternals::getImpl(pObj); }

public:
  OdDbLightImpl();

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler) const;

  friend class OdDbLight;

  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  void rdPhotometricData(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void wrPhotometricData(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void rdPhotometricData(OdDbDxfFiler *pFiler);
  void wrPhotometricData(OdDbDxfFiler *pFiler) const;
  void rdPhotometricData(OdDbDwgFiler *pFiler);
  void wrPhotometricData(OdDbDwgFiler *pFiler) const;
  void targetDirectionHasBeenChanged();
  void computeUnknownAngle3_GC53(OdGeVector2d dirVec);
  void computeUnknownAngle4_GC54(OdGeVector2d dirVec);
  double physicalIntensityInCandelas(const OdDbObject *pObj);
  OdGiColorRGB lampColorPreset(OdDbLight::LampColorPreset preset);
  OdGiColorRGB lampColorKelvin(double kelvin);
  OdGiColorRGB lampColor();

  void setCastShadows(bool) {}
  bool castShadows() const { return false; }

  void setReceiveShadows(bool) {}
  bool receiveShadows() const { return false; }

  void draw(
      OdGiGeometry& geom,
      OdGiSubEntityTraits* inTraits,
      OdGiContext* context,
      const OdGiContextualColors* pCtxColors,
      double size,
      OdGeVector3d& dir ) const;
  void drawExtendedLightShape(
      OdGiGeometry& geom,
      OdGiSubEntityTraits* inTraits,
      const OdGiContextualColors* pCtxColors) const;

  // IESNA processing
  bool syncWebFile(const OdDbObject *pObj);
  bool isWebFileInSync() const;
  void webFileNeedSync();

  // Highlighting
  bool isHighlightNeedUpdate(OdUInt16 lightingUnits) const;
};

#endif // __OD_DB_LIGHT_IMPL__
