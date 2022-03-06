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

#ifndef __TNW_GEOMETRY_H__
#define __TNW_GEOMETRY_H__

#include "RxSystemServices.h"
#include "NwProxy.h"

class OdGePoint3d;
class OdGePoint2d;
class OdGeVector3d;

/** \details
  This class represents object geometry for vectorization.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwGeometry : public OdNwProxy
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwGeometry);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwGeometry object.
  */
  OdNwGeometry();
  
  /** \details
    Constructor. Creates a new OdNwGeometry object.

    \param pImpl [in]  OdNwGeometry implementation object.
  */
  explicit OdNwGeometry(OdNwObjectImpl* pImpl);

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwGeometry();

  /** \details
    Returns an array of vertices.

    \returns Array of vertices.
    \remarks
    The method is deprecated. Using this method can decrease the performance.
    Please use getVerticesData() for correcponding class instead,
    i.e. OdNwGeometryLineSet::getVerticesData(), OdNwGeometryMesh::getVerticesData() etc.
  */
  OdArray<OdGePoint3d> getVertexes() const;

  /** \details
    Returns an array of colors.

    \returns Array of colors.
    \remarks
    The method is deprecated. Using this method can decrease the performance.
    Please use getVerticesData() for correcponding class instead,
    i.e. OdNwGeometryLineSet::getColors(), OdNwGeometryMesh::getColors() etc.
  */
  OdArray<OdUInt32> getColors() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwGeometry object pointers.
*/
typedef OdSmartPtr<OdNwGeometry> OdNwGeometryPtr;

/** \details
  This template class is a specialization of the OdArray class for
  OdNwGeometryPtr's collection.
*/
typedef OdArray<OdNwGeometryPtr> OdNwGeometryArray;

#endif //__TNW_GEOMETRY_H__
