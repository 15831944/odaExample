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

#ifndef __NWCAMERA_INCLUDED_
#define __NWCAMERA_INCLUDED_

#include "NwExport.h"
#define STL_USING_MEMORY
#include "OdaSTL.h"
#include "NwViewType.h"
#include "Ge/GeQuaternion.h"

class NWDBEXPORT OdNwCamera
{
public:
  OdNwCamera();
  OdNwCamera(OdNwCamera&& other);
  OdNwCamera& operator=(OdNwCamera&& other);
  ~OdNwCamera() = default;

public:
  NwViewType::Enum getProjection() const;
  const OdGePoint3d& getPosition() const;
  const OdGeQuaternion& getRotation() const;
  double getViewAspect() const;
  double getHeightField() const;
  double getNear() const;
  double getFar() const;
  double getUpOffsetFactor() const;
  double getRightOffsetFactor() const;

public:
  void setProjection(NwViewType::Enum proj);
  void setPosition(OdGePoint3d&& pos);
  void setPosition(const OdGePoint3d& pos);
  void setRotation(OdGeQuaternion&& rot);
  void setRotation(const OdGeQuaternion& rot);
  void setViewAspect(double&& val);
  void setHeightField(double&& val);
  void setNear(double&& val);
  void setFar(double&& val);
  void setUpOffsetFactor(double&& val);
  void setRightOffsetFactor(double&& val);

private:
  NwViewType::Enum m_projection;
  OdGePoint3d m_position;
  OdGeQuaternion m_rotation;
  double m_viewAspect;
  double m_heightField;
  double m_near;
  double m_far;
  double m_upOffsetFactor;
  double m_rightOffsetFactor;
};

typedef std::shared_ptr<OdNwCamera> OdNwCameraPtr;

#endif //__NWCAMERA_INCLUDED_
