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

#ifndef _PRCSRFFROMCURVES_INCLUDED_
#define _PRCSRFFROMCURVES_INCLUDED_ 
 

#include "PrcSurface.h"
#include "PrcCurve.h"

/** \details 
<group PRC_Surface_Classes> 

Class stores information about a ruled surface, which is defined by two curves that have points connected by lines.
*/
class PRC_TOOLKIT OdPrcFromCurvesSurface : public OdPrcSurface
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_SURF(OdPrcFromCurvesSurface)
  //DOM-IGNORE-END

  /** \details
  Destroys the ruled surface object.
  */
  ~OdPrcFromCurvesSurface();
  
  /** \details
  Returns the current origin point.
  The origin point is returned as a reference to an OdGePoint3d object, therefore it can be used to set a new origin point.
  */
  OdGePoint3d &origin();
  
  /** \details
  Returns the current origin point.
  */
  const OdGePoint3d &origin() const;

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

SMARTPTR(OdPrcFromCurvesSurface);

#endif // _PRCSRFFROMCURVES_INCLUDED_

