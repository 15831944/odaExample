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

#ifndef _PRCMATH1DCOMBINATION_INCLUDED_
#define _PRCMATH1DCOMBINATION_INCLUDED_ 
 

#include "PrcMath1d.h"

/** \details 
<group PRC_Mathematical_Operator_Classes> 

Class stores information about the one-dimensional mathematical combination function.
*/
class PRC_TOOLKIT OdPrcCombinationFunction
{
  //DOM-IGNORE-BEGIN
  double m_dCoefficient;
  OdPrcMath1dPtr m_pFunction;
  //DOM-IGNORE-END
public:

  /** \details 
    Creates the combination function object.
  */
  OdPrcCombinationFunction();
  
  /** \details 
    Sets a new coefficient value of the combination function object.
    \param dCoefficient [in] A new coefficient value.
  */
  void setCoefficient(double dCoefficient);
  
  /** \details 
    Retrieves the current coefficient value of the combination function object.
    \returns Returns the current coefficient value.
  */
  double getCoefficient() const;
  
  /** \details 
    Retrieves the current one-dimensional mathematical function of the combination function object.
    \returns Returns a reference to the smart pointer that points to the current one-dimensional mathematical function. Therefore the method can be used to set a new function object.
  */
  OdPrcMath1dPtr & function();
  
  /** \details 
    Retrieves the current one-dimensional mathematical function of the combination function object.
    \returns Returns the smart pointer to the current one-dimensional mathematical function.
  */
  const OdPrcMath1dPtr & function() const;
};

/** \details
  A data type that represents an array of combination functions.
*/
typedef OdArray<OdPrcCombinationFunction> OdPrcCombinationFunctionArray;

/** \details 
<group PRC_Mathematical_Operator_Classes> 

Class stores information about the combination of several one-dimensional mathematical functions.
*/
class PRC_TOOLKIT OdPrcMath1dCombination : public OdPrcMath1d
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_MATH(OdPrcMath1dCombination)
  //DOM-IGNORE-END

  /** \details
  Evaluates a specified parameter using the following algorithm: 

    for (i = 0; i < number_of_coefficients; i++) 
    { 
      output = output + coefficient[i] * function[i];
    }

  \param dParam [in] A parameter to be evaluated.
  */
  virtual double evaluate(double dParam) const;

  /** \details
  Returns the current combination functions array.
  combination functions array is returned as a reference to an OdPrcCombinationFunctionArray object, therefore it can be used to set a new combination functions array.
  */
  OdPrcCombinationFunctionArray &combinationFunctions();

  /** \details
  Returns the current combination functions array.
  */
  const OdPrcCombinationFunctionArray &combinationFunctions() const;
};

/** \details
  A data type that represents a smart pointer to a one-dimensional mathematical function.
*/
SMARTPTR(OdPrcMath1dCombination);

#endif // _PRCMATH1DCOMBINATION_INCLUDED_

