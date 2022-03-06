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

#ifndef __TNW_POSITIONLIGHT_H__
#define __TNW_POSITIONLIGHT_H__

#include "NwCommonLight.h"

/** \details
  This class represents a position light of a model.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwPositionLight : public OdNwCommonLight
{
  ODRX_DECLARE_MEMBERS(OdNwPositionLight);
  
protected:
  OdNwPositionLight();
  explicit OdNwPositionLight(OdNwObjectImpl* pImpl);

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwPositionLight();

public:

  /** \details
    Returns the attennuation vector of the light.

    \returns Returns an OdGeVector3d value with the attennuation vector of the light.
  */
  OdGeVector3d getAttennuation() const;

  /** \details
    Returns the position point of the light.

    \returns Returns an OdGePoint3d value with the position point of the light.
  */
  OdGePoint3d getPosition() const;

  /** \details
    Returns the radius of influence of the light.

    \returns Returns a double value with the radius of influence of the light.
  */
  double getRadiusOfInfluence() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwPositionLight object pointers.
*/
typedef OdSmartPtr<OdNwPositionLight> OdNwPositionLightPtr;

#endif //__TNW_POSITIONLIGHT_H__
