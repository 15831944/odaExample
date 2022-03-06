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

#ifndef _PRCSRFEXTRUSION_INCLUDED_
#define _PRCSRFEXTRUSION_INCLUDED_ 
 

#include "PrcSurface.h"
#include "PrcCurve.h"

/** \details 
<group PRC_Surface_Classes>

Class representing an extruded surface with a base curve that is extruded along a sweep vector.
*/
class PRC_TOOLKIT OdPrcExtrusionSurface : public OdPrcSurface
{

public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_SURF(OdPrcExtrusionSurface)
  //DOM-IGNORE-END

  /** \details
  Destroys the extruded surface object.
  */
  ~OdPrcExtrusionSurface();
  
  /** \details
  Returns the current sweep vector.
  The sweep vector is returned as a reference to an OdGeVector3d object, therefore it can be used to set a new sweep vector.
  */
  OdGeVector3d &sweepVector();
  
  /** \details
  Returns the current sweep vector.
  */
  const OdGeVector3d &sweepVector() const;

  /** \details
  Sets a new base curve.

  \param value [in] A smart pointer to an OdPrcCurve object to be set as a new base curve.
  
  \returns Returns eOk if new base curve data was successfully applied to the extrusion surface or an appropriate error code in the other case.
  */
  OdResult setBaseCurve(const OdPrcCurvePtr &value);
  
  /** \details
  Returns the current base curve of the extrusion surface.
  */
  const OdPrcCurvePtr &baseCurve() const;
};

SMARTPTR(OdPrcExtrusionSurface);

#endif // _PRCSRFEXTRUSION_INCLUDED_

