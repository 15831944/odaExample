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

#ifndef _PRCINTERVAL_INCLUDED_
#define _PRCINTERVAL_INCLUDED_ 
 

/** \details 
<group PRC_Datatypes_Classes> 

Class stores information about intervals.
*/
class PRC_TOOLKIT OdPrcInterval
{
private:
  double m_maxValue;
  double m_minValue;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcInterval)
  //DOM-IGNORE-END

  /** \details 
  Sets a new maximum value of the interval. 
  
  \param maxValue [in] A new maximum value to be set.
  */
  void setMaxValue(double maxValue);
  
  /** \details 
  Returns the current maximum value of the interval.
  */
  double maxValue() const;
  
  /** \details 
  Sets a new minimum value of the interval. 
  
  \param minValue [in] A new minimum value to be set.
  */
  void setMinValue(double minValue);
  
  /** \details 
  Returns the current minimum value of the interval. 
  */
  double minValue() const;
};

#endif // _PRCWIREEDGE_INCLUDED_

