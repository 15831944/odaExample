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

#ifndef _ODVIINFO_INCLUDED_
#define _ODVIINFO_INCLUDED_

#include "UCSInfo.h"
#include "Ge/GePoint2d.h"

class OdDbDwgFiler;
class OdDbAuditInfo;
class OdString;

class OdViInfo : public OdUCSInfo
{
public:
  OdViInfo();

  void setRenderMode(OdUInt8 value)
  {
    ODA_ASSERT(value < OdDb::kMaxRenderMode);
    m_RenderMode = OdUInt8( (value < OdDb::kMaxRenderMode)
      ? value
      : OdDb::k2DOptimized);
  }
  OdUInt8 getRenderMode() const 
  { 
    return m_RenderMode; 
  }

  void setTwistAngle(double value) 
  { 
    m_dTwistAngle = value; 
  }
  double getTwistAngle() const 
  { 
    return m_dTwistAngle; 
  }

  void setBackZ(double value) 
  { 
    m_dBackZ = value; 
  }
  double getBackZ() const 
  { 
    return m_dBackZ; 
  }

  void setFrontZ(double value) 
  { 
    m_dFrontZ = value; 
  }
  double getFrontZ() const 
  { 
    return m_dFrontZ; 
  }

  void setLensLength(double value) 
  { 
    m_dLensLength = value; 
  }
  double getLensLength() const 
  { 
    return m_dLensLength; 
  }

  void setViewHeight(double value) 
  { 
    m_dViewHeight = value; 
  }
  double getViewHeight() const 
  { 
    return m_dViewHeight; 
  }

  void setDirFromTarget(const OdGeVector3d& value) 
  { 
    m_DirFromTarget = value; 
  }
  OdGeVector3d& dirFromTarget() 
  { 
    return m_DirFromTarget; 
  }
  const OdGeVector3d& getDirFromTarget() const 
  { 
    return m_DirFromTarget; 
  }

  void setTarget(const OdGePoint3d& value) 
  { 
    m_Target = value; 
  }
  OdGePoint3d& target()
  {
    return m_Target; 
  }
  const OdGePoint3d& getTarget() const 
  { 
    return m_Target;
  }

  void setViewCenter(const OdGePoint2d& value) 
  { 
    m_ViewCenter = value; 
  }
  OdGePoint2d& viewCenter()
  { 
    return m_ViewCenter; 
  }
  const OdGePoint2d& getViewCenter() const 
  { 
    return m_ViewCenter; 
  }

  bool isPerspective() const 
  { 
    return GETBIT(m_ViewFlags, kPerspective); 
  }
  bool isFrontClipEnabled() const 
  { 
    return GETBIT(m_ViewFlags, kFrontClipEnabled); 
  }
  bool isBackClipEnabled() const 
  { 
    return GETBIT(m_ViewFlags, kBackClipEnabled); 
  }
  bool isUcsFollowMode() const 
  { 
    return GETBIT(m_ViewFlags, kUcsFollowMode); 
  }
  bool isFrontClipAtEyeOn() const 
  { 
    return GETBIT(m_ViewFlags, kFrontClipAtEyeOn); 
  }

  void setPerspective(bool val) 
  { 
    SETBIT(m_ViewFlags, kPerspective, val); 
  }
  void setFrontClipEnabled(bool val) 
  { 
    SETBIT(m_ViewFlags, kFrontClipEnabled, val); 
  }
  void setBackClipEnabled(bool val) 
  { 
    SETBIT(m_ViewFlags, kBackClipEnabled, val); 
  }
  void setUcsFollowMode(bool val) 
  { 
    SETBIT(m_ViewFlags, kUcsFollowMode, val); 
  }
  void setFrontClipAtEyeOn(bool val) 
  { 
    SETBIT(m_ViewFlags, kFrontClipAtEyeOn, val); 
  }

  OdInt16 getViewMode() const 
  { 
    return OdInt16(m_ViewFlags ^ 0x10); 
  }
  void setViewMode(OdInt16 value) 
  { 
    m_ViewFlags = OdUInt8(value ^ 0x10); 
  }

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;

  void auditViInfo (OdDbAuditInfo* pAuditInfo, OdDbObject* pObj);

protected:
  OdGePoint2d  m_ViewCenter;
  OdGeVector3d m_DirFromTarget;
  OdGePoint3d  m_Target;
  double       m_dViewHeight;
  double       m_dLensLength;
  double       m_dFrontZ;
  double       m_dBackZ;
  double       m_dTwistAngle;
  OdUInt8      m_RenderMode;

  // new AC2007 fields
  OdDbSoftPointerId   m_background;
  OdDbHardPointerId   m_visualStyle;
  OdDbSoftPointerId   m_shadePlotId;
  bool                m_bUseDefaultLights; // use default lighting instead OdDbLights in this viewport
  OdUInt8             m_defaultLightingType; // OdGiViewportTraits::DefaultLightingType
  double              m_dBrightness, m_dContrast;
  OdCmColor           m_ambientLightColor;
  OdDbHardOwnershipId m_sun;
  OdInt16             m_gridMajor; // groupcode 61, the frequency of major grid lines compared to minor grid lines

  void composeForLoadRenderMode(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

private:
  // ViewMode flags
  enum
  {
    kPerspective      = 1,
    kFrontClipEnabled = 2,
    kBackClipEnabled  = 4,
    kUcsFollowMode    = 8,
    kFrontClipAtEyeOn = 16
  };
  OdUInt8 m_ViewFlags;
};

#endif // _ODVIINFO_INCLUDED_
