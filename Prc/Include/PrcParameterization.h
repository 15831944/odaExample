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

#ifndef _PRCINCLUDED_
#define _PRCINCLUDED_ 
 

#include "PrcInterval.h"
#include "Ge/GeInterval.h"

/** \details 
<group PRC_Datatypes_Classes> 

Class for storing and working with a curve domain and parameters. 
It contains an interval for specifying curve domain values and two coefficients (coeff_a and coeff_b) used to parameterize the curve to its implicit parameters.
*/
class PRC_TOOLKIT OdPrcParameterization
{
private:
  OdPrcInterval m_interval;
  double        m_coeff_a;
  double        m_coeff_b;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcParameterization)
  //DOM-IGNORE-END

  /** \details
  Creates a OdPrcParameterization object based on a specified interval and coefficient values.
  
  \param interval [in] A reference to an OdPrcInterval object to specify the curve domain.
  \param coeff_a [in] A value of coeff_a coefficient. Default value is 1.0.
  \param coeff_b [in] A value of coeff_b coefficient. Default value is 0.0.
  */
  OdPrcParameterization( const OdPrcInterval &interval, double coeff_a = 1., double coeff_b = 0. );
  
  /** \details
  Creates an OdPrcParameterization object based on a specified OdGeInterval object and coefficient values.
  
  \param interval [in] A reference to an OdGeInterval object to specify the curve domain.
  \param coeff_a [in] A value of coeff_a coefficient. Default value is 1.0.
  \param coeff_b [in] A value of coeff_b coefficient. Default value is 0.0.
  */
  OdPrcParameterization( const OdGeInterval &interval, double coeff_a = 1., double coeff_b = 0. );
  
  /** \details
  Creates an OdPrcParameterization object based on an interval specified with start and end values and coefficient values.
  
  \param min [in] A start value of the interval.
  \param max [in] An end value of the interval.
  \param coeff_a [in] A value of coeff_a coefficient. Default value is 1.0.
  \param coeff_b [in] A value of coeff_b coefficient. Default value is 0.0.
  */
  OdPrcParameterization( double min, double max, double coeff_a = 1., double coeff_b = 0. );
  
  /** \details
  Returns the implicit interval according to the current coefficient values and interval boundaries.
  */
  OdPrcInterval getImplicitInterval() const;
  
  /** \details
  Returns the implicit parameter according to the current coefficient values and specified parameter value.
  
  \param dParam [in] A param value from the interval.
  */  
  double getImplicitParam( double dParam ) const;

  /** \details
    Returns the real parameter according to the current coefficient values and specified parameter value.
    
    \param dParam [in] A param value from the implicit interval.
  */  
  double getRealParam( double dParam ) const;

  /** \details
  Returns the current value of coeff_a coefficient.
  */  
  double coeffA() const;
  
  /** \details
  Returns the current value of coeff_a coefficient.
  */  
  double coeffB() const;
  
  /** \details
  Returns the current interval of parameterization.
  */  
  const OdPrcInterval &interval() const;
  
  /** \details
  Sets a new interval and coefficient values.
  
  \param interval [in] A reference to a new interval to be set.
  \param coeff_a [in] A new coeff_a value to be set. Default value is 1.0.
  \param coeff_b [in]  A new coeff_b value to be set. Default value is 0.0.
  */  
  OdResult set(const OdPrcInterval &interval, double coeff_a = 1., double coeff_b = 0.);
  
  /** \details
  Sets a new interval and coefficient values.
  
  \param interval [in] A reference to a new interval to be set.
  \param coeff_a [in] A new coeff_a value to be set. Default value is 1.0.
  \param coeff_b [in]  A new coeff_b value to be set. Default value is 0.0.
  */  
  OdResult set(const OdGeInterval &interval, double coeff_a = 1., double coeff_b = 0.);
  
  /** \details
  Sets a new interval and coefficient values.
  
  \param min [in] A start boundary of a new interval.
  \param max [in] An end boundary of a new interval.
  \param coeff_a [in] A new coeff_a value to be set. Default value is 1.0.
  \param coeff_b [in]  A new coeff_b value to be set. Default value is 0.0.
  */  
  OdResult set(double min, double max, double coeff_a = 1., double coeff_b = 0.);
};

#endif // _PRCINCLUDED_

