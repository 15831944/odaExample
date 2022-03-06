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

#ifndef __TNW_GEOMETRYELLIPTICALSHAPE_H__
#define __TNW_GEOMETRYELLIPTICALSHAPE_H__

#include "NwGeometry.h"

class OdGeVector3d;

/** \details
  This class represents geometry with the elliptical shape type.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwGeometryEllipticalShape : public OdNwGeometry
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwGeometryEllipticalShape);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwGeometryEllipticalShape object.
  */
  OdNwGeometryEllipticalShape();

public:

  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwGeometryEllipticalShape();

public:

  /** \details
    Returns the origin of the geometry data.

    \returns OdGePoint3d object with the origin of the geometry data.
  */
  OdGePoint3d getOrigin() const;

  /** \details
    Returns the radius of the elliptical geometry data.

    \returns Radius of the elliptical geometry data.
  */
  double getRadius() const;

  /** \details
    Returns the X vector of the elliptical geometry data.

    \returns X vector of the elliptical geometry data.
  */
  OdGeVector3d getXVector() const;

  /** \details
    Returns the Y vector of the elliptical geometry data.

    \returns Y vector of the elliptical geometry data.
  */
  OdGeVector3d getYVector() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwGeometryEllipticalShape object pointers.
*/
typedef OdSmartPtr<OdNwGeometryEllipticalShape> OdNwGeometryEllipticalShapePtr;

#endif //__TNW_GEOMETRYELLIPTICALSHAPE_H__
