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

#ifndef _PRCMATH1DFRACTION_INCLUDED_
#define _PRCMATH1DFRACTION_INCLUDED_ 
 

#include "PrcMath1d.h"

/** \details 
<group PRC_Mathematical_Operator_Classes> 

Class stores information about a fraction of two one-dimensional equations.
*/
class PRC_TOOLKIT OdPrcMath1dFraction : public OdPrcMath1d
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_MATH(OdPrcMath1dFraction)
  //DOM-IGNORE-END

  /** \details
  Sets a new value of the fraction numerator.

  \param value [in] A new numerator value to be set.

  \returns Returns eOk if a new numerator was successfully set or an appropriate error code in the other case.
  */
  OdResult setNumerator(const OdPrcMath1dPtr &value);

  /** \details
  Returns the current numerator value.
  */
  const OdPrcMath1dPtr &numerator() const;

  /** \details
  Sets a new value of the fraction denominator.

  \param value [in] A new denominator value to be set.

  \returns Returns eOk if a new denominator was successfully set or an appropriate error code in the other case.
  */
  OdResult setDenominator(const OdPrcMath1dPtr &value);

  /** \details
  Returns the current fraction denominator. 
  */
  const OdPrcMath1dPtr &denominator() const;

  /** \details
  Evaluates the parameter using the following formula: output = numerator / denominator.

  \param dParam [in] A parameter value to be evaluated.
  */
  virtual double evaluate( double dParam ) const;
};

SMARTPTR(OdPrcMath1dFraction);

#endif // _PRCMATH1DFRACTION_INCLUDED_

