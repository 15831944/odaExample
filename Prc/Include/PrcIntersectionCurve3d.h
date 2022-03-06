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

#ifndef _PRCCRVINTERSECTION3d_INCLUDED_
#define _PRCCRVINTERSECTION3d_INCLUDED_ 
 

#include "PrcCurve3d.h"
#include "PrcCrossingPointsCrvIntersection.h"
#include "PrcSurface.h"

/** \details
<group PRC_Curve_Classes>

Class implements a curve which represents the exact intersections of two surfaces. 
An intersection curve can be parameterized and transformed for positioning in model space. 
\remarks
Transformation can be one of the following:
  <table>
    Value  Description
    0x00  Identity
    0x01  Translate
    0x02  Rotate
    0x08  Scale
  </table>
  
OdPrcIntersectionCurve3d inherits the OdPrcCurve class and can be reparameterized and trimmed using the OdPrcParameterization class and setParameterization() method. 
*/
class PRC_TOOLKIT OdPrcIntersectionCurve3d : public OdPrcCurve3d
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_CRV(OdPrcIntersectionCurve3d)
  //DOM-IGNORE-END
  
  /** \details 
  Destroys the intersection curve.
  */
  virtual ~OdPrcIntersectionCurve3d();
  
  /** \details
  Returns the current end limit point of the intersection curve.
  The end limit point is returned as a reference to an OdGePoint3d object, therefore it can be used to set a new end limit point.
  */
  OdGePoint3d &endLimitPoint();

  /** \details
  Returns the current end limit point of the intersection curve.
  */
  const OdGePoint3d &endLimitPoint() const;
  
  /** \details
  Returns the current start limit point of the intersection curve represented as a reference to an OdGePoint3d object.
  The start limit point is returned as a reference to an OdGePoint3d object, therefore it can be used to set a new start limit point.
  */
  OdGePoint3d &startLimitPoint();
  
  /** \details
  Returns the current start limit point of the intersection curve.
  */
  const OdGePoint3d &startLimitPoint() const;
  
  /** \details
  Returns the current crossing points array of the intersection curve.
  The crossing points array is returned as a reference to an OdPrcCrossingPointsCrvIntersectionArray object, therefore it can be used to set new crossing points.
  */
  OdPrcCrossingPointsCrvIntersectionArray &crossingPointsCrvIntersection();
  
  /** \details
  Returns the current crossing points array of the intersection curve.
  */
  const OdPrcCrossingPointsCrvIntersectionArray &crossingPointsCrvIntersection() const;
  
  /** \details
  Sets a new value of the angular error for the intersection curve.
  
  \param angular_error [in] A new value to be set.
  */
  void setAngularError(double angular_error);
  
  /** \details
  Returns the current value of the angular error for the intersection curve.
  */
  double angularError() const;
  
  /** \details
  Sets a new value of the chordal error for the intersection curve.
  
  \param chordal_error [in] A new value to be set.
  */
  void setChordalError(double chordal_error);
  
  /** \details
  Returns the current value of the chordal error for the intersection curve.
  */
  double chordalError() const;
  
  /** \details
  Sets a new value of the parameterization definition respected flag.
  If this flag is set to true, the parameterization definition is respected; in the other case (flag is false) the parameterization definition is not respected.
  
  \param parameterization_definition_respected [in] A new value to be set.
  */
  void setParameterizationDefinitionRespected(bool parameterization_definition_respected);
  
  /** \details
  Returns the current value of the parameterization definition respected flag.
  If this flag is set to true, the parameterization definition is respected; in the other case (flag is false) the parameterization definition is not respected.
  */
  bool parameterizationDefinitionRespected() const;
  
  /** \details
  Sets a new value of the sense crossing flag.
  The flag value is equal to true if the sense of the intersection is the first surface crossing the second one; it is equal to false in the other case.  
  
  \param intersection_sense [in] A new value to be set.  
  */
  void setIntersectionSense(bool intersection_sense);

  /** \details
  Returns the current value of the sense crossing flag.
  The flag value is equal to true if the sense of the intersection is the first surface crossing the second one; it is equal to false in the other case.  
  */
  bool intersectionSense() const;
  
  /** \details
  Sets a new value of the second surface sense flag.
  The flag value is equal to true if the sense of the intersection is the same as the second surface sense; it is equal to false in the other case.  
  
  \param surface_2_sense [in] A new value to be set.
  */
  void setSurface2Sense(bool surface_2_sense);
  
  /** \details
  Returns the current value of the second surface sense flag.
  The flag value is equal to true if the sense of the intersection is the same as the second surface sense; it is equal to false in the other case.  
  */
  bool surface2Sense() const;
  
  /** \details
  Sets a new value of the first surface sense flag.
  The flag value is equal to true if the sense of the intersection is the same as the first surface sense; it is equal to false in the other case.  
  
  \param surface_1_sense [in] A new value to be set.
  */
  void setSurface1Sense(bool surface_1_sense);
  
  /** \details
  Returns the current value of the first surface sense flag.
  The flag value is equal to true if the sense of the intersection is the same as the first surface sense; it is equal to false in the other case.  
  */
  bool surface1Sense() const;
 
  /** \details
  Sets a new first surface for the intersection curve.
  
  \param value [in] A new first surface to be set.
  
  \returns Returns eOk if a new first surface was successfully set or an appropriate error code in the other case.
  */
  OdResult setSurface1(const OdPrcSurfacePtr &value);
  
  /** \details
  Returns the current first surface of the intersection curve.
  */
  const OdPrcSurfacePtr &surface1() const;

  /** \details
  Sets a new second surface for the intersection curve.
  
  \param value [in] A new second surface to be set.
  
  \returns Returns eOk if a new second surface was successfully set or an appropriate error code in the other case.
  */
  OdResult setSurface2(const OdPrcSurfacePtr &value);
  
  /** \details
  Returns the current second surface for the intersection curve.
  */
  const OdPrcSurfacePtr &surface2() const;

  /** \details
  Sets a new start limit type for the intersection curve.
  
  \param value [in] A new start limit type to be set.
  
  \returns Returns eOk if a new start limit type was successfully set or an appropriate error code in the other case.
  */
  OdResult setStartLimitType(OdUInt32 value);
  
  /** \details
  Returns the current start limit type for the intersection curve.
  */
  OdUInt32 startLimitType() const;

  /** \details
  Sets a new end limit type for the intersection curve.
  
  \param value [in] A new end limit type to be set.
  
  \returns Returns eOk if a new end limit type was successfully set or an appropriate error code in the other case.
  */
  OdResult setEndLimitType(OdUInt32 value);
  
  /** \details
  Returns the current end limit type for the intersection curve.
  */
  OdUInt32 endLimitType() const;
};
SMARTPTR(OdPrcIntersectionCurve3d);

#endif // _PRCCRVINTERSECTION3d_INCLUDED_

