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

#ifndef _PRCSRFNURBS_INCLUDED_
#define _PRCSRFNURBS_INCLUDED_ 
 

#include "PrcSurface.h"
#include "Ge/GeNurbSurface.h"
#include "Ge/GeInterval.h"


/** \details 
<group PRC_Surface_Classes>

Class stores information about a rational b-spline surface.
*/
class PRC_TOOLKIT OdPrcNurbsSurface : public OdPrcSurface
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_SURF(OdPrcNurbsSurface)
  //DOM-IGNORE-END

  /** \details
  Returns current nurbs surface data.
  Nurbs surface data is returned as a reference to an OdGeNurbSurface object, therefore it can be used to set new nurbs surface data.
  */
  OdGeNurbSurface &nurbSurface();
  
  /** \details
  Returns current nurbs surface data.
  */
  const OdGeNurbSurface &nurbSurface() const;

  /** \details
  Sets a new knot type value to the nurbs surface.

  \param value [in] A new knot type value to be set.

  \returns Returns eOk if a new knot type value was successfully set or an appropriate error code in the other case.
  */
  OdResult setKnotType(OdUInt32 value);
  
  /** \details
  Returns the current knot type of the nurbs surface.
  */
  OdUInt32 knotType() const;

  /** \details
  Sets a new surface form value to the nurbs surface.

  \param value [in] A new surface form value to be set.

  \returns Returns eOk if a new surface form value was successfully set or an appropriate error code in the other case.
  */
  OdResult setSurfaceForm(OdUInt32 value);
  
  /** \details
  Returns the current surface form value of the nurbs surface.
  */
  OdUInt32 surfaceForm() const;
};

SMARTPTR(OdPrcNurbsSurface);

#endif // _PRCSRFNURBS_INCLUDED_

