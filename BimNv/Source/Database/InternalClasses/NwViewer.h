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

#ifndef __NWVIEWER_INCLUDED_
#define __NWVIEWER_INCLUDED_

#include "NwExport.h"
#define STL_USING_MEMORY
#include "OdaSTL.h"
#include "NwCameraMode.h"
#include "OdString.h"

class NWDBEXPORT OdNwViewer
{
public:
  OdNwViewer();
  OdNwViewer(OdNwViewer&& other);
  OdNwViewer& operator=(OdNwViewer&& other);
  ~OdNwViewer() = default;

public:
  double getRadius() const;
  double getHeight() const;
  double getActualHeight() const;
  double getEyeHeightOffset() const;
  const OdString& getAvatar() const;
  NwCameraMode::Enum getCameraMode() const;
  double getFirstToThirdAngle() const;
  double getFirstToThirdDistance() const;
  double getFirstToThirdParam() const;
  bool isFirstToThirdCorrection() const;
  bool isColisionDetection() const;
  bool isGravity() const;
  double getGravityValue() const;
  double getTerminalVelocity() const;
  bool isAutoCrouch() const;

public:
  void setRadius(double&& val);
  void setHeight(double&& val);
  void setActualHeight(double&& val);
  void setEyeHeightOffset(double&& val);
  void setAvatar(OdString&& val);
  void setCameraMode(NwCameraMode::Enum val);
  void setFirstToThirdAngle(double&& val);
  void setFirstToThirdDistance(double&& val);
  void setFirstToThirdParam(double&& val);
  void setIsFirstToThirdCorrection(bool val);
  void setIsColisionDetection(bool val);
  void setIsGravity(bool val);
  void setGravityValue(double&& val);
  void setTerminalVelocity(double&& val);
  void setIsAutoCrouch(bool val);

private:
  double m_radius;
  double m_height;
  double m_actualHeight;
  double m_eyeHeightOffset;
  OdString m_avatar;
  NwCameraMode::Enum m_cameraMode;
  double m_firstToThirdAngle;
  double m_firstToThirdDistance;
  double m_firstToThirdParam;
  bool m_bIsFirstToThirdCorrection;
  bool m_bIsColisionDetection;
  bool m_bIsGravity;
  double m_gravityValue;
  double m_terminalVelocity;
  bool m_bIsAutoCrouch;
};

typedef std::shared_ptr<OdNwViewer> OdNwViewerPtr;

#endif //__NWVIEWER_INCLUDED_
