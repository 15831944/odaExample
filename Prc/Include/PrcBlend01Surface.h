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

#ifndef _PRCSRFBLEND01_INCLUDED_
#define _PRCSRFBLEND01_INCLUDED_ 
 

#include "PrcSurface.h"
#include "PrcCurve.h"

/** \details 
<group PRC_Surface_Classes>

Class stores information about a surface, which is defined by a center curve, origin curve, and tangent curve.
*/
class PRC_TOOLKIT OdPrcBlend01Surface : public OdPrcSurface
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_SURF(OdPrcBlend01Surface)
  //DOM-IGNORE-END

  /** \details
  Destructor of the class.
  */
  ~OdPrcBlend01Surface();

  /** \details
  Sets a new center curve data.
  
  \param value [in] A new center curve data to be set.
  
  \returns Returns eOk if new center curve data was successfully set, or an appropriate error code in the other case.
  */
  OdResult setCenterCurve(const OdPrcCurvePtr &value);
  
  /** \details
  Returns current center curve data of the surface.
  */
  const OdPrcCurvePtr &centerCurve() const;

  /** \details
  Sets new origin curve data.

  \param value [in] New origin curve data to be set.
  
  \returns Returns eOk if new origin curve data was successfully set, or an appropriate error code in the other case.
  */
  OdResult setOriginCurve(const OdPrcCurvePtr &value);
  
  /** \details
  Returns current origin curve data.
  */
  const OdPrcCurvePtr &originCurve() const;

  /** \details
  Sets new tangent curve data.

  \param value [in] New tangent curve data to be set.
  
  \returns Returns eOk if new tangent curve data was successfully set, or an appropriate error code in the other case.
  */
  OdResult setTangentCurve(const OdPrcCurvePtr &value);
  
  /** \details
  Returns current tangent curve data.
  */
  const OdPrcCurvePtr &tangentCurve() const;
};

SMARTPTR(OdPrcBlend01Surface);

#endif // _PRCSRFBLEND01_INCLUDED_

