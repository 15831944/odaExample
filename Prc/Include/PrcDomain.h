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

#ifndef _PRCDOMAIN_INCLUDED_
#define _PRCDOMAIN_INCLUDED_ 
 

#include "Ge/GeInterval.h"
#include "Ge/GePoint2d.h"

/** \details
<group PRC_Datatypes_Classes>

Class implements the PRC domain for surface uv-parameterization.
*/
class PRC_TOOLKIT OdPrcDomain
{
private:
  OdGePoint2d m_minUV; 
  OdGePoint2d m_maxUV; 
  OdPrcDomain(double minU, double minV, double maxU, double maxV);

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcDomain);
  //DOM-IGNORE-END

  /** \details 
  A double value used as the minus infinite value (equal to -12345.0) */
  PRC_TOOLKIT_STATIC static const double kLowerInfinite;
  /** \details 
  A double value used as the infinite value (equal to 12345.0) */
  PRC_TOOLKIT_STATIC static const double kUpperInfinite;
  /** \details 
  The infinitive domain */
  PRC_TOOLKIT_STATIC static const OdPrcDomain kInfinite;

  /** \details
  Returns current minimum values for U and V.
  */
  const OdGePoint2d &minUV() const;
  
  /** \details
  Returns current maximum values for U and V.
  */
  const OdGePoint2d &maxUV() const;

  /** \details
  Sets new values for U and V.
  
  \param minUV [in] A new minimum value for U and V to be set.
  \param maxUV [in] A new maximum value for U and V to be set.
  
  \return Returns eOk if new values were successfully set or an appropriate error code in the other case.
  
  \remarks
  minUV.x and minUV.y must be less than maxUV.x and maxUV.y respectively. If not, eInvalidInput is returned.
  */
  OdResult set(const OdGePoint2d &minUV, const OdGePoint2d &maxUV);
  
  /** \details
  Sets new values for U and V.
  
  \param intervalU [in] A new minimum and maximum value for U represented with an OdGeInterval object.
  \param intervalV [in] A new minimum and maximum value for V represented with an OdGeInterval object.
  
  \return Returns eOk if new values were successfully set or an appropriate error code in the other case.
  */
  OdResult set(const OdGeInterval &intervalU, const OdGeInterval &intervalV);
  
  /** \details
  Sets new values for U and V.
  
  \param minU [in] A new minimum value for U.
  \param minV [in] A new minimum value for V.
  \param maxU [in] A new maximum value for U.
  \param maxV [in] A new maximum value for V.
  
  \return Returns eOk if new values were successfully set or an appropriate error code in the other case.
  */
  OdResult set(double minU, double minV, double maxU, double maxV);
};

#endif // _PRCDOMAIN_INCLUDED_

