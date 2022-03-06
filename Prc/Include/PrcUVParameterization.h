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

#ifndef _PRCUVINCLUDED_
#define _PRCUVINCLUDED_ 
 

#include "PrcDomain.h"

/** \details 
<group PRC_Datatypes_Classes> 

Class for storing and operating with surface parameterization. 
It contains a surface domain and four coefficients (u_coeff_a and v_coeff_a, u_coeff_b, and v_coeff_b) used to parameterize the surface to its implicit parameters.
*/
class PRC_TOOLKIT OdPrcUVParameterization
{
private:
  OdPrcDomain m_uv_domain;
  bool        m_swap_uv;
  double      m_u_coeff_a;
  double      m_v_coeff_a;
  double      m_u_coeff_b;
  double      m_v_coeff_b;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcUVParameterization)
  //DOM-IGNORE-END

  /** \details
  Creates an OdPrcUVParameterization object based on specified domain and coefficient values.
  
  \param uv_domain [in] A reference to an OdPrcDomain object to specify the surface domain.
  \param swap_uv [in] A flag that determines whether the uv param is swapped. Default value is false (not swapped).
  \param u_coeff_a [in] A value of the u_coeff_a coefficient. Default value is 1.0.
  \param v_coeff_a [in] A value of the v_coeff_a coefficient. Default value is 1.0.
  \param u_coeff_b [in] A value of the u_coeff_b coefficient. Default value is 0.0.
  \param v_coeff_b [in] A value of the v_coeff_b coefficient. Default value is 0.0.
  */
  OdPrcUVParameterization(const OdPrcDomain &uv_domain, bool swap_uv = false, double u_coeff_a = 1, double v_coeff_a = 1, double u_coeff_b = 0, double v_coeff_b = 0);
  
  /** \details
  Creates an OdPrcUVParameterization object based on a domain specified with starting and ending intervals and coefficient values.
  
  \param ivU       [in] A new minimum and maximum value for U represented with an OdGeInterval object.
  \param ivV       [in] A new minimum and maximum value for V represented with an OdGeInterval object.
  \param swap_uv   [in] A flag that determines whether the uv param is swapped. Default value is false (not swapped).
  \param u_coeff_a [in] A value of u_coeff_a coefficient. Default value is 1.0.
  \param v_coeff_a [in] A value of v_coeff_a coefficient. Default value is 1.0.
  \param u_coeff_b [in] A value of u_coeff_b coefficient. Default value is 0.0.
  \param v_coeff_b [in] A value of v_coeff_b coefficient. Default value is 0.0.
  */
  OdPrcUVParameterization(const OdGeInterval &ivU, const OdGeInterval &ivV, bool swap_uv = false, double u_coeff_a = 1, double v_coeff_a = 1, double u_coeff_b = 0, double v_coeff_b = 0);
  
  /** \details
  Creates an OdPrcUVParameterization object based on a domain specified with starting and ending values for u- and v-intervals and coefficient values.
  
  \param minU [in] A starting value for the u-interval.
  \param maxU [in] An ending value for the u-interval.
  \param minV [in] A starting value for the v-interval.
  \param maxV [in] An ending value for the v-interval.
  \param swap_uv [in] A flag that determines whether uv param is swapped. Default value is false (not swapped).
  \param u_coeff_a [in] A value of the u_coeff_a coefficient. Default value is 1.0.
  \param v_coeff_a [in] A value of the v_coeff_a coefficient. Default value is 1.0.
  \param u_coeff_b [in] A value of the u_coeff_b coefficient. Default value is 0.0.
  \param v_coeff_b [in] A value of the v_coeff_b coefficient. Default value is 0.0.
  */
  OdPrcUVParameterization(double minU, double maxU, double minV, double maxV, bool swap_uv = false, double u_coeff_a = 1, double v_coeff_a = 1, double u_coeff_b = 0, double v_coeff_b = 0);

  /** \details
  Returns the current domain of the parameterization.
  */
  const OdPrcDomain& uvDomain() const;
  
  /** \details
  Returns the current uv parameter swap flag value. If returns true, uv parameters were swapped; returns false in the other case.
  */
  bool swapUV() const;
  
  /** \details
  Returns the current value of the u_coeff_a coefficient.
  */
  double uCoeffA() const;
  
  /** \details
  Returns the current value of the v_coeff_a coefficient.
  */
  double vCoeffA() const;
  
  /** \details
  Returns the current value of the u_coeff_b coefficient.
  */
  double uCoeffB() const;
  
  /** \details
  Returns the current value of the v_coeff_b coefficient.
  */
  double vCoeffB() const;
  
  /** \details
  Sets a new domain, a new swap flag value, and u- and v-coefficients to new values.
  
  \param uv_domain [in] A reference to a new domain to be set.
  \param swap_uv [in] A new value of the swap flag to be set.
  \param u_coeff_a [in] A new u_coeff_a value. Default value is 1.0.
  \param v_coeff_a [in] A new v_coeff_a value. Default value is 1.0.
  \param u_coeff_b [in] A new u_coeff_b value. Default value is 0.0.
  \param v_coeff_b [in] A new v_coeff_b value. Default value is 0.0.      
  
  \returns Returns eOk if new values were successfully set, or an appropriate error code in the other case.
  */
  OdResult set(const OdPrcDomain &uv_domain, bool swap_uv = false, double u_coeff_a = 1, double v_coeff_a = 1, double u_coeff_b = 0, double v_coeff_b = 0);

  /** \details
  Sets a new domain, a new swap flag value, and u- and v-coefficients to new values.
  
  \param ivU       [in] A new minimum and maximum value for U represented with an OdGeInterval object.
  \param ivV       [in] A new minimum and maximum value for V represented with an OdGeInterval object.
  \param swap_uv   [in] A new value of the swap flag to be set.
  \param u_coeff_a [in] A new u_coeff_a value. Default value is 1.0.
  \param v_coeff_a [in] A new v_coeff_a value. Default value is 1.0.
  \param u_coeff_b [in] A new u_coeff_b value. Default value is 0.0.
  \param v_coeff_b [in] A new v_coeff_b value. Default value is 0.0.      
  
  \returns Returns eOk if new values were successfully set, or an appropriate error code in the other case.
  */
  OdResult set(const OdGeInterval &ivU, const OdGeInterval &ivV, bool swap_uv = false, double u_coeff_a = 1, double v_coeff_a = 1, double u_coeff_b = 0, double v_coeff_b = 0);
  
  /** \details
  Sets a new domain, a swap flag value, and u- and v-coefficients to new values.
  
  \param minU [in] A new starting value of the u-interval.
  \param maxU [in] A new ending value of the u-interval.
  \param minV [in] A new starting value of the v-interval.
  \param maxV [in] A new ending value of the v-interval.
  \param swap_uv [in] A new value of the swap flag to be set.
  \param u_coeff_a [in] A new u_coeff_a value. Default value is 1.0.
  \param v_coeff_a [in] A new v_coeff_a value. Default value is 1.0.
  \param u_coeff_b [in]  A new u_coeff_b value. Default value is 0.0.
  \param v_coeff_b [in]  A new v_coeff_b value. Default value is 0.0.
  
  \returns Returns eOk if new values were successfully set, or an appropriate error code in the other case.
  */
  OdResult set(double minU, double maxU, double minV, double maxV, bool swap_uv = false, double u_coeff_a = 1, double v_coeff_a = 1, double u_coeff_b = 0, double v_coeff_b = 0);

  /** \details
  Returns the implicit u-parameter according to the current coefficient values and a specified parameter value.
  
  \param param [in] A param value from the u-interval.
  \returns A double value that contains the U-parameter value.
  */
  double getImplicitUParam( const OdGePoint2d& param ) const;
  
  /** \details
    Returns the implicit v-parameter according to the current coefficient values and a specified parameter value.
    
    \param param [in] A param value from the v-interval.
    \returns A double value that contains the V-parameter value.
  */
  double getImplicitVParam( const OdGePoint2d& param ) const;

  /** \details
  Retrieves the current implicit domain of the parameterization. End parameter can be less than start.
  \param startU [out] A placeholder for starting U-parameter value.
  \param startV [out] A placeholder for starting V-parameter value. 
  \param endU   [out] A placeholder for ending U-parameter value.
  \param endV   [out] A placeholder for ending V-parameter value.
  \remarks 
  The method fills the passed values and returns them to a calling subroutine.
  */
  void getImplicitDomain(double& startU, double& startV, double& endU, double& endV) const;

  /** \details
    Retrieves the current implicit domain of the parameterization. End parameter can be less than start.

    \param domain [out] Calculated domain.
  */
  void getImplicitDomain(OdPrcDomain& domain) const;

  /** \details
  Retrieves the real U-parameter according to the current cofficient values and a specified implicit parameter value.
  \param implicitParam [in] A two-dimensional point that represent the implicit U-parameter.
  \returns A double value that contains the U-parameter value.
  */
  double getRealUParam( const OdGePoint2d& implicitParam ) const;

  /** \details
  Retrieves the real v-parameter according to the current cofficient values and a specified implicit parameter value.
  \param implicitParam [in] A two-dimensional point that represent the implicit V-parameter.
  \returns A double value that contains the V-parameter value.
  */
  double getRealVParam( const OdGePoint2d& implicitParam ) const;

  /** \details
    Retrieves the real parameter according to the current cofficient values and a specified implicit parameter value.
    
    \param implicitParam [in] A two-dimensional point that represent the implicit UV-parameter.
    \returns A real parameter value.
  */
  OdGePoint2d getRealParam(const OdGePoint2d& implicitParam) const;
};

#endif // _PRCUVINCLUDED_

