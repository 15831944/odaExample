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

#ifndef __ODGIVISUALSTYLEIMPL_H__
#define __ODGIVISUALSTYLEIMPL_H__

#include "TD_PackPush.h"

#include "Gi/GiVisualStyle.h"
#include "CmColor.h"
#include "StaticRxObject.h"

class TOOLKIT_EXPORT OdTvGiFaceStyleImpl : public OdGiFaceStyle
{
public:
  ODRX_DECLARE_MEMBERS(OdTvGiFaceStyleImpl);

  OdTvGiFaceStyleImpl();
  
  // OdGiFaceStyle overridden
  //
  void setLightingModel(LightingModel lightingModel);
  LightingModel lightingModel() const;

  void setLightingQuality(LightingQuality lightingQuality);
  LightingQuality lightingQuality() const;

  void setFaceColorMode(FaceColorMode mode);
  FaceColorMode faceColorMode() const;

  void setFaceModifiers(unsigned long nModifiers);
  void setFaceModifierFlag(FaceModifier flag, bool bEnable);
  unsigned long faceModifiers() const;
  bool isFaceModifierFlagSet(FaceModifier flag) const;

  void setOpacityLevel(double nLevel, bool bEnableModifier);
  double opacityLevel() const;

  void setSpecularAmount(double nAmount, bool bEnableModifier);
  double specularAmount() const;

  void setMonoColor(const OdCmColorBase& color, bool bEnableMode);
  const OdCmColorBase& monoColor() const;
  OdCmColorBase& monoColor();

  // OdTvCmColor accessors
  //
  OdTvCmColor& monoColorImpl() { return m_MonoColor; }

protected:
  FaceModifier    m_FaceModifiers;
  LightingModel   m_LightingModel;
  LightingQuality m_LightingQuality;
  FaceColorMode   m_FaceMode;
  double          m_nOpacityLevel;
  double          m_nSpecularLevel;
  OdTvCmColor       m_MonoColor; 
};


class TOOLKIT_EXPORT OdTvGiEdgeStyleImpl : public OdGiEdgeStyle
{
public:
  ODRX_DECLARE_MEMBERS(OdTvGiEdgeStyleImpl);

  OdTvGiEdgeStyleImpl();

  // OdGiEdgeStyle overridden
  //
  void setEdgeModel(EdgeModel model);
  EdgeModel edgeModel() const;

  void setEdgeStyles(unsigned long nStyles);
  void setEdgeStyleFlag(EdgeStyle flag, bool bEnable);
  unsigned long edgeStyles() const;
  bool isEdgeStyleFlagSet(EdgeStyle flag) const;

  void setIntersectionColor(const OdCmColorBase& color);
  const OdCmColorBase& intersectionColor() const;
  OdCmColorBase& intersectionColor();

  void setObscuredColor(const OdCmColorBase& color);
  const OdCmColorBase& obscuredColor() const;
  OdCmColorBase& obscuredColor();

  void setObscuredLinetype(LineType ltype);
  LineType obscuredLinetype() const;

  void setIntersectionLinetype(LineType ltype);
  LineType intersectionLinetype() const;

  void setCreaseAngle(double nAngle);
  double creaseAngle() const;

  void setEdgeModifiers(unsigned long nModifiers);
  void setEdgeModifierFlag(EdgeModifier flag, bool bEnable);
  unsigned long edgeModifiers() const;
  bool isEdgeModifierFlagSet(EdgeModifier flag) const;

  void setEdgeColor(const OdCmColorBase& color, bool bEnableModifier);
  const OdCmColorBase& edgeColor() const;
  OdCmColorBase& edgeColor();

  void setOpacityLevel(double nLevel, bool bEnableModifier);
  double opacityLevel() const;

  void setEdgeWidth(int nWidth, bool bEnableModifier);
  int edgeWidth() const;

  void setOverhangAmount(int nAmount, bool bEnableModifier);
  int overhangAmount() const;

  void setJitterAmount(JitterAmount amount, bool bEnableModifier);
  JitterAmount jitterAmount() const;

  void setWiggleAmount(WiggleAmount amount, bool bEnableModifier);
  WiggleAmount wiggleAmount() const;

  void setSilhouetteColor(const OdCmColorBase& color);
  const OdCmColorBase& silhouetteColor() const;
  OdCmColorBase& silhouetteColor();

  void setSilhouetteWidth(short nWidth);
  short silhouetteWidth() const;

  void setHaloGap(int nHaloGap, bool bEnableModifier);
  int haloGap() const;

  void setIsolines(unsigned short nIsolines);
  unsigned short isolines() const;

  void setHidePrecision(bool bHidePrecision);
  bool hidePrecision() const;

  void setEdgeStyleApply(EdgeStyleApply apply);
  EdgeStyleApply edgeStyleApply() const;

  // OdTvCmColor accessors
  //
  OdTvCmColor& edgeColorImpl() { return m_EdgeColor; }
  OdTvCmColor& silhouetteColorImpl() { return m_SilhouetteColor; }
  OdTvCmColor& intersectionColorImpl() { return m_IntersectionColor; }
  OdTvCmColor& obscuredColorImpl() { return m_ObscuredColor; }

protected:
  int             m_nOverhangAmount;
  JitterAmount    m_JitterAmount;
  short           m_nSilhouetteWidth;
  int             m_nHaloGap;
  unsigned short  m_nIsolines;
  bool            m_bHidePrecision;
  EdgeModel       m_EdgeModel;
  EdgeStyle       m_EdgeStyles;
  LineType        m_ObscuredLinetype;
  LineType        m_IntersectionLinetype;
  double          m_dCreaseAngle;
  EdgeModifier    m_EdgeModifier;
  double          m_nOpacityLevel;
  int             m_nEdgeWidth;
  OdTvCmColor       m_EdgeColor;
  OdTvCmColor       m_SilhouetteColor;
  OdTvCmColor       m_IntersectionColor;
  OdTvCmColor       m_ObscuredColor;
  EdgeStyleApply  m_EdgeStyleApply;
  WiggleAmount    m_WiggleAmount;
};


class TOOLKIT_EXPORT OdTvGiDisplayStyleImpl : public OdGiDisplayStyle
{
public:
  ODRX_DECLARE_MEMBERS(OdTvGiDisplayStyleImpl);

  OdTvGiDisplayStyleImpl();

  void setDisplaySettings(unsigned long nSettings);
  void setDisplaySettingsFlag(DisplaySettings flag, bool bEnable);
  unsigned long displaySettings() const;
  bool isDisplaySettingsFlagSet(DisplaySettings flag) const;

  void setBrightness(double value);
  double brightness() const;

  void setShadowType(ShadowType type);
  ShadowType shadowType() const;

protected:
  DisplaySettings     m_DisplaySettings;
  ShadowType          m_ShadowType;
  double              m_dBrightness;
};


class TOOLKIT_EXPORT OdTvGiVisualStyleImpl : public OdGiVisualStyle
{
public:
  ODRX_DECLARE_MEMBERS(OdTvGiVisualStyleImpl);

  OdTvGiVisualStyleImpl();

  OdGiFaceStyle& faceStyle();
  OdGiEdgeStyle& edgeStyle();
  OdGiDisplayStyle& displayStyle();

  const OdGiFaceStyle& faceStyle() const;
  const OdGiEdgeStyle& edgeStyle() const;
  const OdGiDisplayStyle& displayStyle() const;

  void setFaceStyle(const OdGiFaceStyle& style);
  void setEdgeStyle(const OdGiEdgeStyle& style);
  void setDisplayStyle(const OdGiDisplayStyle& style);

  // New interface

  bool setType(Type type);
  Type type() const;

  TD_USING(OdGiVisualStyle::setTrait);
  bool setTrait(Property prop, Operation op);
  bool setTrait(Property prop, const OdGiVariant *pVal,
                Operation op = OdGiVisualStyleOperations::kSet);
  bool setTrait(Property prop, const OdCmColorBase &pColor,
                Operation op = OdGiVisualStyleOperations::kSet);

  OdGiVariantPtr trait(Property prop, Operation *pOp = NULL) const;
  bool trait(Property prop, OdGiVariant &pVar, Operation *pOp = NULL) const;
  Operation operation(Property prop) const;
protected:
  OdStaticRxObject<OdTvGiFaceStyleImpl> m_faceStyle;
  OdStaticRxObject<OdTvGiEdgeStyleImpl> m_edgeStyle;
  OdStaticRxObject<OdTvGiDisplayStyleImpl> m_displayStyle;
  // Basic properties for new interface
  Type m_type;
  Operation m_propertyOperation[OdGiVisualStyleProperties::kPropertyCount];
  // ac27
  bool m_bUseDrawOrder;
  bool m_bViewportTransparency;
  bool m_bLightingEnabled;
  bool m_bPosterizeEffect;
  bool m_bMonoEffect;
  bool m_bBlurEffect;
  bool m_bPencilEffect;
  bool m_bBloomEffect;
  bool m_bPastelEffect;
  OdInt32 m_nBlurAmount;
  double m_dPencilAngle;
  double m_dPencilScale;
  OdInt32 m_nPencilPattern;
  OdTvCmColor m_clrPencilColor;
  OdInt32 m_nBloomThreshold;
  OdInt32 m_nBloomRadius;
  OdTvCmColor m_clrTintColor;
  bool m_bFaceAdjustment;
  OdInt32 m_nPostContrast;
  OdInt32 m_nPostBrightness;
  OdInt32 m_nPostPower;
  bool m_bTintEffect;
  OdInt32 m_nBloomIntensity;
  OdTvCmColor m_clrColor;
  double m_dTransparency;
  OdString m_strEdgeTexturePath;
  bool m_bDepthOfField;
  double m_dFocusDistance;
  double m_dFocusWidth;
};

#include "TD_PackPop.h"

#endif //__ODGIVISUALSTYLEIMPL_H__
