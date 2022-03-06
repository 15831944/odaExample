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

#ifndef _PRCCRVBlend02Boundary3d_INCLUDED_
#define _PRCCRVBlend02Boundary3d_INCLUDED_ 
 

#include "PrcCurve3d.h"
#include "PrcBlend02Surface.h"

/** \details 
<group PRC_Curve_Classes> 

Class stores data of a U iso-parametric curve of a Blend02 surface.
*/
class PRC_TOOLKIT OdPrcBlend02Boundary3d : public OdPrcCurve3d
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_CRV(OdPrcBlend02Boundary3d)
  //DOM-IGNORE-END
  
  /** \details
  Destructor of a Blend02 surface.
  */
  ~OdPrcBlend02Boundary3d();

  /** \details
  Returns the current point of the ending limit.
  The point is returned as a reference to an OdGePoint3d object, therefore it can be used to set a new ending limit point.
  */
  OdGePoint3d &endLimitPoint();
  
  /** \details
  Returns the current point of the ending limit.
  */
  const OdGePoint3d &endLimitPoint() const;
  
  /** \details
  Returns the current point of the starting limit.
  The point is returned as a reference to an OdGePoint3d object, therefore it can be used to set a new starting limit point.
  */
  OdGePoint3d &startLimitPoint();
  
  /** \details
  Returns the current point of the starting limit.
  */
  const OdGePoint3d &startLimitPoint() const;
  
  /** \details
  Returns the current crossing point position.
  The crossing point position is returned as a reference to an OdGePoint3dArray object, therefore it can be used to set a new crossing point position.
  */
  OdGePoint3dArray &crossingPointPositions();
  
  /** \details
  Returns the current crossing point position.
  */
  const OdGePoint3dArray &crossingPointPositions() const;
  
  /** \details
  Sets a new base scale.

  \param base_scale [in] A new base scale to be set.
  */
  void setBaseScale(double base_scale);
  
  /** \details
  Returns the current base scale.
  */
  double baseScale() const;
  
  /** \details
  Sets a new base parameter value.

  \param base_parameter [in] A new base parameter value to be set.
  */
  void setBaseParameter(double base_parameter);
  
  /** \details 
  Returns the current base parameter.
  */
  double baseParameter() const;
  
  /** \details
  Sets a new value of the angular error.

  \param angular_error [in] A new angular error value to be set.
  */
  void setAngularError(double angular_error);
  
  /** \details
  Returns the current angular error.
  */
  double angularError() const;
  
  /** \details
  Sets a new value of the chordal error.

  \param chordal_error [in] A new chordal error value to be set.
  */
  void setChordalError(double chordal_error);
  
  /** \details
  Returns the current chordal error.
  */
  double chordalError() const;
  
  /** \details
  Sets a new value of the intersection curve sense.

  \param intersection_curve_sens [in] A new intersection curve sense value to be set.
  */
  void setIntersectionCurveSens(bool intersection_curve_sens);
  
  /** \details
  Returns the current intersection curve sense.
  */
  bool intersectionCurveSens() const;
  
  /** \details
  Sets the current intersection order.

  \param intersection_order [in] A new intersection order to be set.
  */
  void setIntersectionOrder(bool intersection_order);
  
  /** \details
  Returns the current intersection order.
  */
  bool intersectionOrder() const;
  
  /** \details
  Sets a new bounding surface sense.

  \param bounding_surface_sens [in] A new bounding surface sense to be set.
  */
  void setBoundingSurfaceSens(bool bounding_surface_sens);
  
  /** \details
  Returns the current bounding surface sense.
  */
  bool boundingSurfaceSens() const;

  /** \details
  Sets a new blend.

  \param value [in] A new blend to be set.
        
  \returns Returns eOk if a new blend was successfully set, or an appropriate error code in the other case.
  */
  OdResult setBlend(const OdPrcBlend02SurfacePtr &value);
  
  /** \details
  Returns the current blend.
  */
  const OdPrcBlend02SurfacePtr &blend() const;

  /** \details
  Sets a new bound value.

  \param value [in] A new bound value to be set.
  
  \returns Returns eOk if a new bound value was successfully set, or an appropriate error code in the other case.
  */
  OdResult setBound(OdUInt8 value);
  
  /** \details
  Returns the current bound value.
  */
  OdUInt8 bound() const;

  /** \details
  Sets a new bounding surface.

  \param value [in] A new bounding surface to be set.
  
  \returns Returns eOk if a new bounding surface was successfully set, or an appropriate error code in the other case.
  */
  OdResult setBoundingSurface(const OdPrcSurfacePtr &value);
  
  /** \details
  Returns the current bounding surface.
  */
  const OdPrcSurfacePtr &boundingSurface() const;

  /** \details
  Sets a new starting limit type.

  \param value [in] A new starting limit type to be set.
  
  \returns Returns eOk if a new starting limit type was successfully set, or an appropriate error code in the other case.
  */
  OdResult setStartLimitType(OdUInt32 value);
  
  /** \details
  Returns the current starting limit type.
  */
  OdUInt32 startLimitType() const;

  /** \details
  Sets a new ending limit type.

  \param value [in] A new ending limit type to be set.
    
  \returns Returns eOk if a new ending limit type was successfully set, or an appropriate error code in the other case.
  */
  OdResult setEndLimitType(OdUInt32 value);
  
  /** \details
  Returns the current ending limit type.
  */
  OdUInt32 endLimitType() const;
};
SMARTPTR(OdPrcBlend02Boundary3d);

#endif // _PRCCRVBlend02Boundary3d_INCLUDED_

