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

#ifndef _PRCSRFBLEND02_INCLUDED_
#define _PRCSRFBLEND02_INCLUDED_ 
 

#include "PrcSurface.h"
#include "PrcCurve.h"

/** \details
<group PRC_Surface_Classes> 

Class stores information about a surface, which is defined by rolling a ball with a constant radius over the center curve and contacting two surfaces.
*/
class PRC_TOOLKIT OdPrcBlend02Surface : public OdPrcSurface
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_SURF(OdPrcBlend02Surface)
  //DOM-IGNORE-END

  /** \details
  Destructor of the Blend02Surface.
  */
  ~OdPrcBlend02Surface();
  
  /** \details
  Returns the current cliff supporting surface 1.
  The cliff supporting surface 1 is returned as a reference to an OdPrcSurfacePtr object, therefore it can be used to set a new cliff supporting surface 1. 
  */
  OdPrcSurfacePtr &cliffSupportingSurface1();
  
  /** \details
  Returns the current cliff supporting surface 1.
  */
  const OdPrcSurfacePtr &cliffSupportingSurface1() const;
  
  /** \details
  Returns the current cliff supporting surface 0.
  The cliff supporting surface 0 is returned as a reference to an OdPrcSurfacePtr object, therefore it can be used to set a new cliff supporting surface 0. 
  */
  OdPrcSurfacePtr &cliffSupportingSurface0();
  
  /** \details
  Returns the current cliff supporting surface 0.
  */
  const OdPrcSurfacePtr &cliffSupportingSurface0() const;
  
  /** \details
  Returns the current bound curve 1.
  The bound curve 1 is returned as a reference to an OdPrcCurvePtr object, therefore it can be used to set a new bound curve 1. 
  */
  OdPrcCurvePtr &boundCurve1();
  
  /** \details
  Returns the current bound curve 1.
  */
  const OdPrcCurvePtr &boundCurve1() const;
  
  /** \details
  Returns the current bound curve 0.
  The bound curve 0 is returned as a reference to an OdPrcCurvePtr object, therefore it can be used to set a new bound curve 0. 
  */
  OdPrcCurvePtr &boundCurve0();
  
  /** \details
  Returns the current bound curve 0.
  */
  const OdPrcCurvePtr &boundCurve0() const;
  
  /** \details
  Returns the current bound surface 1.
  The bound surface 1 is returned as a reference to an OdPrcSurfacePtr object, therefore it can be used to set a new bound surface 1. 
  */
  OdPrcSurfacePtr &boundSurface1();
  
  /** \details
  Returns the current bound surface 1.
  */
  const OdPrcSurfacePtr &boundSurface1() const;
  
  /** \details
  Returns the current bound surface 0.
  The bound surface 0 is returned as a reference to an OdPrcSurfacePtr object, therefore it can be used to set a new bound surface 0. 
  */
  OdPrcSurfacePtr &boundSurface0();
  
  /** \details
  Returns the current bound surface 0.
  */
  const OdPrcSurfacePtr &boundSurface0() const;
  
  /** \details
  Sets a new value of the radius 1.

  \param radius1 [in] A new value of the radius 1 to be set.
  */
  void setRadius1(double radius1);
  
  /** \details
  Returns the current value of the radius 1.
  */
  double radius1() const;
  
  /** \details
  Sets a new value of the radius 0.

  \param radius0 [in] A new value of the radius 0.
  */
  void setRadius0(double radius0);
  
  /** \details
  Returns the current value of the radius 0.
  */
  double radius0() const;
  
  /** \details
  Sets a new value of the bound surface sense 1.

  \param bound_surface_sens1 [in] A new value of the bound surface sense 1 to be set.
  */
  void setBoundSurfaceSens1(bool bound_surface_sens1);
  
  /** \details
  Returns the current bound surface sense 1.
  */
  bool boundSurfaceSens1() const;
  
  /** \details
  Sets a new value of the bound surface sense 0.

  \param bound_surface_sens0 [in] A new value of the bound surface sense 0 to be set.
  */
  void setBoundSurfaceSens0(bool bound_surface_sens0);
  
  /** \details
  Returns the current bound surface sense 0.
  */
  bool boundSurfaceSens0() const;
  
  /** \details
  Sets a new value of the center curve sense.

  \param center_curve_sens [in] A new value of the center curve sense to be set.
  */
  void setCenterCurveSens(bool center_curve_sens);
  
  /** \details
  Returns the current center curve sense.
  */
  bool centerCurveSens() const;

  /** \details
  Sets a new center curve data.

  \param value [in] A new center curve data to be set.
  
  \returns Returns eOk if new center curve data was set successfully or an appropriate error code in the other case.
  */
  OdResult setCenterCurve(const OdPrcCurvePtr &value);
  
  /** \details
  Returns current center curve data.
  */
  const OdPrcCurvePtr &centerCurve() const;

  /** \details
  Sets a new parameterization type for the surface. 

  \param value [in] A new parameterization type to be set.
  
  Returns eOk if a new parameterization type was successfully set, or an appropriate error code in the other case.
  */
  OdResult setParameterizationType(OdUInt8 value);
  
  /** \details
  Returns the current parametrization type for the surface.
  */
  OdUInt8 parameterizationType() const;
};

SMARTPTR(OdPrcBlend02Surface);

#endif // _PRCSRFBLEND02_INCLUDED_

