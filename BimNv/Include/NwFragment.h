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

#ifndef __TNW_FRAGMENT_H__
#define __TNW_FRAGMENT_H__

#include "NwObject.h"
#include "RxSystemServices.h"
#include "NwExport.h"
#include "Ge/GeMatrix3d.h"

/** \details
  This class represents fragment geometry of a geometry component.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwFragment : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwFragment);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwFragment object.
  */
  OdNwFragment();

public:

  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwFragment();

public:

  /** \details
    Returns the low bound of geometry data.

    \returns OdGePoint3d object with the low bound of geometry data.
  */
  OdGePoint3d getLowBound() const;

  /** \details
    Returns the high bound of geometry data.

    \returns OdGePoint3d object with the high bound of geometry data.
  */
  OdGePoint3d getHighBound() const;

  /** \details
    Returns the transformation matrix of geometry data.

    \returns OdGeMatrix3d object with the transformation matrix of geometry
    data.
  */
  OdGeMatrix3d getTransformation() const;
  
  /** \details
    Sets the transformation matrix for geometry data.

    \param trm [in] OdGeMatrix3d object with tranformation for geometry data.

    \returns eOk if transfomration setting is successfully, or an appropriate error code otherwise.
  */
  OdResult setTransformation(const OdGeMatrix3d& trm);

  /** \details
    Indicates whether the type of geometry data is ellipse.

    \returns True if the geometry data's type is ellipse, otherwise false.
    \remarks
    The method is deprecated. Use getGeometryId() method and check returned geometry type instead.
  */
  bool isEllipse() const;

  /** \details
    Indicates whether the type of geometry data is line set.

    \returns True if the geometry data's type is line set, otherwise false.
    \remarks
    The method is deprecated. Use getGeometryId() method and check returned geometry type instead.
  */
  bool isLineSet() const;

  /** \details
    Indicates whether the type of geometry data is mesh.

    \returns True if the geometry data's type is mesh, otherwise false.
    \remarks
    The method is deprecated. Use getGeometryId() method and check returned geometry type instead.
  */
  bool isMesh() const;

  /** \details
    Indicates whether the type of geometry data is point set.

    \returns True if the geometry data's type is point set, otherwise false.
    \remarks
    The method is deprecated. Use getGeometryId() method and check returned geometry type instead.
  */
  bool isPointSet() const;

  /** \details
    Indicates whether the type of geometry data is text.

    \returns True if the geometry data's type is text, otherwise false.
    \remarks
    The method is deprecated. Use getGeometryId() method and check returned geometry type instead.
  */
  bool isText() const;

  /** \details
    Indicates whether the type of geometry data is tube.

    \returns True if the geometry data's type is tube, otherwise false.
    \remarks
    The method is deprecated. Use getGeometryId() method and check returned geometry type instead.
  */
  bool isTube() const;

  /** \details
    Indicates whether the type of geometry data is external geometry data.

    \returns True if the geometry data's type is external geometry, otherwise false.
    \remarks
    The method is deprecated. Use getGeometryId() method and check returned geometry type instead.
  */
  bool isExternal() const;

  /** \details
    Returns an object ID of geometry.

    \returns Object ID of the base class OdNwGeometry object with geometry data.
  */
  OdNwObjectId getGeometryId() const;

  /** \details
    Sets geometry for this fragment.

    \param geometryId [in] Object ID of the object with geometry.
  */
  void setGeometry(const OdNwObjectId& geometryId);
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwFragment object pointers.
*/
typedef OdSmartPtr<OdNwFragment> OdNwFragmentPtr;

#endif //__TNW_FRAGMENT_H__
