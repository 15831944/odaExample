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

#ifndef __NWSPOTLIGHTIMPL_INCLUDED__
#define __NWSPOTLIGHTIMPL_INCLUDED__

#include "NwSpotLight.h"
#include "NwPositionLightImpl.h"
#include "SharedPtr.h"

class OdNwSpotLightImpl : public OdNwPositionLightImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwSpotLight)
public:
  OdNwSpotLightImpl();
  virtual ~OdNwSpotLightImpl();
  ODRX_DECLARE_MEMBERS(OdNwSpotLightImpl);

  DrawableType drawableType() const override;
  OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const override;

public:
  static OdNwSpotLightImpl* getImpl(const OdNwSpotLight* pNwLight);
  static OdNwSpotLightImpl* getImpl(const OdRxObject* pRxLight);

public:
  OdGeVector3d getDirection() const;
  double getDropoffRate() const;
  double getCutoffAngle() const;
  OdGeMatrix3d getWebMatrix() const;
  virtual OdNwVariant getValue(NwLightValueType::Enum val_type) const override;

public:
  void setDirection(const OdGeVector3d& direction);
  void setDropoffRate(const double& dropoffRate);
  void setCutoffAngle(const double& cutoffAngle);
  void setWebMatrix(const OdGeMatrix3d& mtr);

protected:
  OdGeVector3d m_Direction;
  double m_DropoffRate;
  double m_CutoffAngle;
  OdGeMatrix3d m_WebMatrix;
};



#endif //__NWSPOTLIGHTIMPL_INCLUDED__
