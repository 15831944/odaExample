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

#ifndef __TNW_GEOMETRYPOINTSET_H__
#define __TNW_GEOMETRYPOINTSET_H__

#include "NwGeometry.h"

/** Forward declaration of the OdNwVerticesData class. */
class OdNwVerticesData;

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwVerticesData object pointers.
*/
typedef OdSmartPtr<OdNwVerticesData> OdNwVerticesDataPtr;

/** \details
  This class represents geometry with the point set type.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwGeometryPointSet : public OdNwGeometry
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwGeometryPointSet);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwGeometryPointSet class.
  */
  OdNwGeometryPointSet();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwGeometryPointSet();

public:
  /** \details
    Indicates whether the points are snap points.

    \returns True if the points are snap points; false otherwise.
  */
  bool getIsSnap() const;

  /** \details
    Sets the snap points attribute.

    \param val [in] Boolean flag that indicates whether the points are snap
                    points (true) or not (false).
  */
  void setIsSnap(bool val);

  /** \details
  Returns a vertices data object.

  \returns OdNwVerticesDataPtr objects with vertices, normals, colors etc.
  */
  OdNwVerticesDataPtr getVerticesData() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwGeometryPointSet object pointers.
*/
typedef OdSmartPtr<OdNwGeometryPointSet> OdNwGeometryPointSetPtr;

#endif //__TNW_GEOMETRYPOINTSET_H__
