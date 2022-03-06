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

#ifndef _PRCSRFREVOLUTION_INCLUDED_
#define _PRCSRFREVOLUTION_INCLUDED_ 
 

#include "PrcSurface.h"
#include "PrcCurve.h"

/** \details 
<group PRC_Surface_Classes>

Class representing a surface of revolution. 
A base curve that revolves around an axis of revolution defines this surface. 
*/
class PRC_TOOLKIT OdPrcRevolutionSurface : public OdPrcSurface
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_SURF(OdPrcRevolutionSurface)
  //DOM-IGNORE-END

  /** \details
  Destroys the revolution surface object.
  */
  ~OdPrcRevolutionSurface();
  
  /** \details
  Returns the current Y axis.
  The Y axis is returned as a reference to an OdGeVector3d object, therefore it can be used to set a new Y axis.
  */
  OdGeVector3d &y();
  
  /** \details
  Returns the current Y axis.
  */
  const OdGeVector3d &y() const;
  
  /** \details
  Returns the current X axis.
  The X axis is returned as a reference to an OdGeVector3d object, therefore it can be used to set a new X axis.
  */
  OdGeVector3d &x();
  
  /** \details
  Returns the current X axis.
  */
  const OdGeVector3d &x() const;
  
  /** \details
  Returns current coordinates of the origin.
  Origin coordinates are returned as a reference to an OdGePoint3d object, therefore it can be used to set new coordinates.
  */
  OdGePoint3d &origin();
  
  /** \details
  Returns current coordinates of the origin.
  */
  const OdGePoint3d &origin() const;

  /** \details
  Sets a new tolerance value.

  \param tolerance [in] A new tolerance value to be set.
  */
  void setTolerance(double tolerance);
  
  /** \details
  Returns the current tolerance value.
  */
  double tolerance() const;
  
  /** \details
  Sets a new base curve.

  \param value [in] A new base curve object to set.
  
  \returns Returns eOk if new base curve data was successfully applied to the revolution surface or an appropriate error code in the other case.
  */
  OdResult setBaseCurve(const OdPrcCurvePtr &value);
  
  /** \details
  Returns the current base curve.
  */
  const OdPrcCurvePtr &baseCurve() const;
};

SMARTPTR(OdPrcRevolutionSurface);

#endif // _PRCSRFREVOLUTION_INCLUDED_

