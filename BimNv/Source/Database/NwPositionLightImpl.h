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

#ifndef __NWPOSITIONLIGHTIMPL_INCLUDED__
#define __NWPOSITIONLIGHTIMPL_INCLUDED__

#include "NwPositionLight.h"
#include "NwCommonLightImpl.h"
#include "SharedPtr.h"

class OdNwPositionLightImpl : public OdNwCommonLightImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwPositionLight)
public:
  OdNwPositionLightImpl();
  virtual ~OdNwPositionLightImpl();
  ODRX_DECLARE_MEMBERS(OdNwPositionLightImpl);

public:
  static OdNwPositionLightImpl* getImpl(const OdNwPositionLight* pNwLight);
  static OdNwPositionLightImpl* getImpl(const OdRxObject* pRxLight);

public:
  OdGeVector3d getAttennuation() const;
  OdGePoint3d getPosition() const;
  double getRadiusOfInfluence() const;
  bool isTargeted() const;
  virtual OdNwVariant getValue(NwLightValueType::Enum val_type) const override;

public:
  void setAttennuation(const OdGeVector3d& attenuation);
  void setPosition(const OdGePoint3d& position);
  void setRadiusOfInfluence(const double& radius);
  void setTargeted(bool isTargeted);

protected:
  OdGeVector3d m_Attennuation;
  OdGePoint3d m_Position;
  double m_radiusOfInfluence;
  //parameters from json protein
  bool m_bIsTargeted;
};



#endif //__NWPOSITIONLIGHTIMPL_INCLUDED__
