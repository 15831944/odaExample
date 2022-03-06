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

#ifndef __NWVIEWPOINTIMPL_INCLUDED__
#define __NWVIEWPOINTIMPL_INCLUDED__

#include "NwViewpoint.h"
#include "Ge/GeQuaternion.h"
#include "NwObjectImpl.h"

#include "NwCamera.h"
#include "NwViewer.h"
#include "NwViewTools.h"

class NWDBEXPORT OdNwViewpointImpl : public OdNwModelView
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwViewpoint)
public:
  OdNwViewpointImpl();
  virtual ~OdNwViewpointImpl();
  ODRX_DECLARE_MEMBERS(OdNwViewpointImpl);

  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* traits) const override;

  static OdNwViewpointImpl* getImpl(const OdNwViewpoint* pNwView);
  static OdNwViewpointImpl* getImpl(const OdRxObject* pRxView);

public:
  double getAngularSpeed() const;
  double getFarDistance() const;
  double getFocalDistance() const;
  bool hasAngularSpeed() const;
  bool hasFocalDistance() const;
  bool hasLighting() const;
  bool hasLinearSpeed() const;
  bool hasRenderStyle() const;
  bool hasWorldUpVector() const;
  double getHeightField() const;
  double getHorizontalScale() const;
  NwLightType::Enum getLighting() const;
  double getLinearSpeed() const;
  double getNearDistance() const;
  OdGePoint3d getPosition() const;
  NwViewType::Enum getProjection() const;
  NwModeType::Enum getRenderStyle() const;
  OdGeQuaternion getRotation() const;
  OdString getAvatar() const;
  NwCameraMode::Enum getViewerCameraMode() const;
  OdGeVector3d getWorldUpVector() const;
  double getViewAspect() const;

public:
  const OdNwCamera& getCamera() const;
  const OdNwViewer& getViewer() const;
  OdUInt32 getTool() const;
  const std::pair<double, double>& getTiltLimits() const;
  double getPreferedFOV() const;
  double getVPNearDistance() const;
  OdUInt32 getVPNearDistanceType() const;
  double getVPFarDistance() const;
  OdUInt32 getVPFarDistanceType() const;
  OdUInt32 getVPImageFit() const;
  double getVPHorizontalScale() const;
  double getVPApertureDiameter() const;
  double getVPShutterSpeed() const;

  inline OdUInt32& getFlags() { return m_flags; }
  inline OdUInt32& getPrimitiveTypesBitfields() { return m_primitiveTypesBitfields; }

public:
  //api methods fr setting of camera's data
  OdResult setProjection(NwViewType::Enum type);
  OdResult setPosition(const OdGePoint3d& pos);
  OdResult setRotation(const OdGeQuaternion& rot);
  OdResult setHeightField(double value);
  OdResult setViewAspect(double value);
  OdResult setCameraNearDistance(double value);
  OdResult setCameraFarDistance(double value);

  void setAngularSpeed(double value);
  OdResult setFocalDistance(double value);
  void setLighting(NwLightType::Enum ligh);
  void setLinearSpeed(double value);
  OdResult setRenderStyle(NwModeType::Enum render);
  OdResult setWorldUpVector(const OdGeVector3d& up);
  void setTool(OdUInt32 tool);
  void setPreferedFOV(double value);
  void setTiltLimits(std::pair<double, double>&& val);
  void setCamera(OdNwCamera&& camera);
  void setViewer(OdNwViewer&& viewer);
  void setNearDistance(double val);
  void setNearDistanceType(OdUInt32 val);
  void setFarDistance(double val);
  void setFarDistanceType(OdUInt32 val);
  void setImageFit(OdUInt32 val);
  void setHorizontalScale(double val);
  void setApertureDiameter(double val);
  void setShutterSpeed(double val);

private:
  OdUInt32 m_flags;
  OdGeVector3d m_Up;
  double m_FocalDistance;
  double m_LinearSpeed;
  double m_AngularSpeed;
  OdUInt32 m_Tool;
  NwLightType::Enum m_Lighting;
  NwModeType::Enum m_Mode;
  //Define the area of the scene that can be viewed throught the camera (degrees)
  double m_PreferedFOV;
  //
  OdNwCamera m_camera;
  OdNwViewer m_viewer;
  //
  std::pair<double, double> m_tiltLimits;
  OdUInt32 m_primitiveTypesBitfields;
  double m_nearDistance;
  OdUInt32 m_nearDistanceType;
  double m_farDistance;
  OdUInt32 m_farDistanceType;
  OdUInt32 m_imageFit;
  double m_horizontalScale;
  double m_apertureDiameter;
  double m_shutterSpeed;
};



#endif //__NWVIEWPOINTIMPL_INCLUDED__
