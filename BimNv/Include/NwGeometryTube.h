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

#ifndef __TNW_GEOMETRYTUBE_H__
#define __TNW_GEOMETRYTUBE_H__

#include "NwGeometry.h"

class OdGeVector3d;

/** \details
  This class represents geometry with the tube type.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwGeometryTube : public OdNwGeometry
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwGeometryTube);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwGeometryTube class.
  */
  OdNwGeometryTube();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwGeometryTube();

public:

  /** \details
    Returns the radius of the tube geometry data.

    \returns Returns a double object with the radius of the tube geometry data.
  */
  double getRadius() const;

  /** \details
    Returns the top center of the tube geometry data.

    \returns Returns an OdGePoint3d object with the top center of the tube geometry data.
  */
  OdGePoint3d getTopCenter() const;

  /** \details
    Returns the bottom center of the tube geometry data.

    \returns Returns an OdGePoint3d object with the bottom center of the tube geometry data.
  */
  OdGePoint3d getBottomCenter() const;

  /** \details
    Returns the x-axis of the tube geometry data.

    \returns Returns an OdGeVector3d object with the x-axis of the tube geometry data.
  */
  OdGeVector3d getXAxis() const;

  /** \details
    Returns the y-axis of the tube geometry data.

    \returns Returns an OdGeVector3d object with the y-axis of the tube geometry data.
  */
  OdGeVector3d getYAxis() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwGeometryTube object pointers.
*/
typedef OdSmartPtr<OdNwGeometryTube> OdNwGeometryTubePtr;

#endif //__TNW_GEOMETRYTUBE_H__
