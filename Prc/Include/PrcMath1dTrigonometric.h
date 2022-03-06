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

#ifndef _PRCMATH1DTRIGONOMETRIC_INCLUDED_
#define _PRCMATH1DTRIGONOMETRIC_INCLUDED_ 
 

#include "PrcMath1d.h"

/** \details 
<group PRC_Mathematical_Operator_Classes> 

Class stores information about a one-dimensional trigonometric equation.
*/
class PRC_TOOLKIT OdPrcMath1dTrigonometric : public OdPrcMath1d
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_MATH(OdPrcMath1dTrigonometric)
  //DOM-IGNORE-END

  /** \details
  Sets a new Dc offset value.

  \param dc_offset [in] A new Dc offset value to be set.
  */
  void setDcOffset(double dc_offset);
  
  /** \details
  Returns the current Dc offset value.
  */
  double dcOffset() const;
  
  /** \details
  Sets a new frequency value.

  \param frequency [in] A new frequency value to be set.
  */
  void setFrequency(double frequency);
  
  /** \details
  Returns the current frequency value.
  */
  double frequency() const;
  
  /** \details
  Sets a new phase value.

  \param phase [in] A new phase value to be set.
  */
  void setPhase(double phase);
  
  /** \details
  Returns the current phase value.
  */
  double phase() const;
  
  /** \details
  Sets a new amplitude value.

  \param amplitude [in] A new amplitude value to be set.
  */
  void setAmplitude(double amplitude);
  
  /** \details
  Returns the current amplitude value.
  */
  double amplitude() const;
 
  /** \details
  Evaluates a specified parameter using the following formula: output = dc_offset + amplitude * cos(param*frequency – phase).

  \param dParam [in] A parameter to be evaluated.
  */
  virtual double evaluate( double dParam ) const;
};

SMARTPTR(OdPrcMath1dTrigonometric);

#endif // _PRCMATH1DTRIGONOMETRIC_INCLUDED_

