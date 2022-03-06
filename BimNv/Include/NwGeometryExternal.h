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

#ifndef __TNW_GEOMETRYEXTERNAL_H__
#define __TNW_GEOMETRYEXTERNAL_H__

#include "NwGeometry.h"

class OdGeVector3d;

/** \details
  This class represents external geometry.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwGeometryExternal : public OdNwGeometry
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwGeometryExternal);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwGeometryExternal object.
  */
  OdNwGeometryExternal();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwGeometryExternal();

public:

public:
  /** \details
    Returns the key of the external geometry.

    \returns Returns a string object with the key value.
  */
  const OdString getKey() const;
  
  /** \details
    Returns the name of the external geometry.

    \returns Returns a string object with the name value.
  */
  const OdString getName() const;
  
  /** \details
    Returns the reference (URI) of the external geometry.

    \returns Returns a string object with reference value.
  */
  const OdString getReference() const;
  
  /** \details
    Returns flags for points in the external geometry.

    \returns Returns an integer value of point flags.
  */
  const OdUInt32 getPointsFlags() const;
  
  /** \details
    Returns the top-left point of the bounding box for the external geometry.

    \returns Returns an OdGePoint3d object that represents the top-left point.
  */
  const OdGePoint3d getTopLeft() const;
  
  /** \details
    Returns the bottom-right point of the bounding box for the external geometry.

    \returns Returns an OdGePoint3d object that represents the bottom-right point.
  */
  const OdGePoint3d getBottomRight() const;
  
  /** \details
    Returns flags of the external geometry.

    \returns Returns an integer value of flags.
  */
  const OdUInt32 getFlags() const;
  
  /** \details
    Returns the type of the external geometry.

    \returns Returns an integer value of the type.
  */
  const OdUInt32 getType() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwGeometryExternal object pointers.
*/
typedef OdSmartPtr<OdNwGeometryExternal> OdNwGeometryExternalPtr;

#endif //__TNW_GEOMETRYEXTERNAL_H__
