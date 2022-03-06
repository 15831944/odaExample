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

#ifndef _PRCCRVHELIXTYPE1_INCLUDED_
#define _PRCCRVHELIXTYPE1_INCLUDED_ 
 

#include "PrcCurve3d.h"
#include "PrcMath1d.h"

/** \details 
<group PRC_Curve_Classes>

Class implements a helix with a variable pitch. A helix is a three-dimensional curve defined on an [-infinite, infinite] interval.
A helix can be parameterized and transformed for positioning in model space. 
\remarks
Transformation can be one of the following:
  <table>
    Value  Description
    0x00  Identity
    0x01  Translate
    0x02  Rotate
    0x08  Scale
  </table>

OdPrcHelixType0Curve inherits the OdPrcCurve class and can be reparameterized and trimmed using the OdPrcParameterization class and setParameterization() method. 
*/
class PRC_TOOLKIT OdPrcHelixType1Curve : public OdPrcCurve3d
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_CRV(OdPrcHelixType1Curve)
  //DOM-IGNORE-END

  /** \details 
  Destroys the helix.
  */
  ~OdPrcHelixType1Curve();
  
  /** \details
  Returns the current start point of the helix.
  The start point is returned as a reference to an OdGePoint3d object, therefore it can be used to set a new start point.
  */
  OdGePoint3d &start();
  
  /** \details
  Returns the current start point of the helix.
  */
  const OdGePoint3d &start() const;
  
  /** \details
  Sets the trigonometric orientation flag.
  The trigonometric orientation flag determines the turn direction of the helix.
  If the flag is set to true, the helix turns in the clockwise direction; if the flag is set to false, it turns in the counter-clockwise direction.
  
  \param trigonometric_orientation [in] A new value of the trigonometric orientation.
  */
  void setTrigonometricOrientation(bool trigonometric_orientation);
  
  /** \details
  Returns the current value of the trigonometric orientation flag.
  The trigonometric orientation flag determines the turn direction of the helix.
  If the flag is set to true, the helix turns in the clockwise direction; if the flag is set to false, it turns in the counter-clockwise direction.
  */
  bool trigonometricOrientation() const;
 
  /** \details
  Sets a new unit_z vector. 
  The unit_z vector determines the Z-axis for the helix's coordinate system.
  
  \param value [in] A new unit_z vector to be set.
  
  \returns Returns eOk if a new unit_z vector was successfully set or an appropriate error code in the other case.
  */
  OdResult setUnitZ(const OdGeVector3d& value);
  
  /** \details
  Returns the current unit_z vector.
  The unit_z vector determines the Z-axis for the helix's coordinate system.
  */
  const OdGeVector3d &unitZ() const;

  /** \details
  Sets a new unit_u vector. 
  The unit_u vector determines the X-axis for the helix's coordinate system.  
  
  \param value [in] A new unit_u vector to be set.
  
  \returns Returns eOk if a new unit_u vector was successfully set or an appropriate error code in the other case.
  */
  OdResult setUnitU(const OdGeVector3d& value);
  
  /** \details
  Returns the current unit_u vector represented as a constant reference to an OdGeVector3d object.
  The unit_u vector determines the X-axis for the helix's coordinate system.
  */
  const OdGeVector3d &unitU() const;

  /** \details 
  Sets a new radius law for the helix.
  The radius law is used to change the radius according to the angle around the helix.
  
  \param value [in] A new radius law to be set.
  
  \returns Returns eOk if a new radius law was successfully set or an appropriate error code in the other case.
  */
  OdResult setRadiusLaw(const OdPrcMath1dPtr &value);
  
  /** \details 
  Returns the current radius law for the helix.
  The radius law is used to change the radius according to the angle around the helix.
  */
  const OdPrcMath1dPtr &radiusLaw() const;

  /** \details 
  Sets a new z-law for the helix.
  The z-law is used to change the helix pitch along the Z-axis of the coordinate system.
  
  \param value [in] A new z-law to be set.
  
  \returns Returns eOk if a new z-law was successfully set or an appropriate error code in the other case.
  */
  OdResult setZLaw(const OdPrcMath1dPtr &value);
  
  /** \details 
  Returns the current z-law for the helix.
  The z-law is used to change the helix pitch along the Z-axis of the coordinate system.
  */
  const OdPrcMath1dPtr &zLaw() const;

  /** \details 
  Sets a new theta law for the helix.
  The theta law is used to change the radius according to the angle around the helix.
  
  \param value [in] A new theta law to be set.
  
  \returns Returns eOk if a new theta law was successfully set or an appropriate error code in the other case.
  */
  OdResult setThetaLaw(const OdPrcMath1dPtr &value);
  
  /** \details 
  Returns the current theta law for the helix.
  The theta law is used to change the radius according to the angle around the helix.
  */
  const OdPrcMath1dPtr &thetaLaw() const;
};
SMARTPTR(OdPrcHelixType1Curve);

#endif // _PRCCRVHELIXTYPE1_INCLUDED_

