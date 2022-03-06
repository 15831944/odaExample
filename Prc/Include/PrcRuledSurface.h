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

#ifndef _PRCSRFRULED_INCLUDED_
#define _PRCSRFRULED_INCLUDED_ 
 

#include "PrcSurface.h"
#include "PrcCurve.h"

/** \details 
<group PRC_Surface_Classes>

Class represents a ruled surface defined by connecting points on each of two curves by a straight line.
*/
class PRC_TOOLKIT OdPrcRuledSurface : public OdPrcSurface
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_SURF(OdPrcRuledSurface)
  //DOM-IGNORE-END

  /** \details
  Destroys the spherical surface object.
  */
  ~OdPrcRuledSurface();

  /** \details
  Returns the first curve of the surface.
  The first curve is returned as a reference to an OdPrcCurvePtr object, therefore it can be used to set a new first curve.
  */
  OdPrcCurvePtr &firstCurve();

  /** \details
  Returns the first curve of the surface.
  */
  const OdPrcCurvePtr &firstCurve() const;

  /** \details
  Returns the second curve of the surface.
  The second curve is returned as a reference to an OdPrcCurvePtr object, therefore it can be used to set a new second curve.
  */
  OdPrcCurvePtr &secondCurve();

  /** \details
  Returns the second curve of the ruled surface.
  */
  const OdPrcCurvePtr &secondCurve() const;
};

SMARTPTR(OdPrcRuledSurface);

#endif // _PRCSRFRULED_INCLUDED_

