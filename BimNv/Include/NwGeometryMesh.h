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

#ifndef __TNW_GEOMETRYMESH_H__
#define __TNW_GEOMETRYMESH_H__

#include "NwGeometry.h"
#include "NwTriangleIndexes.h"
#include "Ge/GePoint2dArray.h"
#include "Ge/GeVector3dArray.h"
#include "Int32Array.h"
#include "UInt16Array.h"

/** Forward declaration of the OdNwVerticesData class. */
class OdNwVerticesData;

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwVerticesData object pointers.
*/
typedef OdSmartPtr<OdNwVerticesData> OdNwVerticesDataPtr;

/** \details
  This class represents geometry with the mesh type.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwGeometryMesh : public OdNwGeometry
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwGeometryMesh);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwGeometryMesh object.
  */
  OdNwGeometryMesh();

public:
  /** \details
    Virtual destructor. Releases allocated resources.
  */
  virtual ~OdNwGeometryMesh();

public:

  /** \details
    Returns an array with the number of vertices per face.

    \returns OdArray object with the number of vertices per face.
    \remarks
    This method is deprecated and will be removed in further releases. Please use getVerticesPerFace() method instead.
  */
  OdArray<OdUInt16> getVertexCountPerFace() const;

  /** \details
  Returns an array with the number of vertices per face.

  \returns OdArray object with the number of vertices per face.
  */
  OdUInt16Array getVerticesPerFace() const;

  /** \details
    Returns an array with the indices for this mesh.

    \returns OdArray object with the indices.
    \remarks
    This method is deprecated and will be removed in further releases. Please use getIndices() method instead.
  */
  OdArray<OdUInt16> getIndexes() const;

  /** \details
  Returns an array with the indices for this mesh.

  \returns OdArray object with the indices.
  */
  OdUInt16Array getIndices() const;

  /** \details
    Returns an array with the normals for this mesh.

    \returns OdArray object with normal vectors.
    \remarks
    This method is deprecated and will be removed in further releases. Please use getVerticesData() method instead.
  */
  OdArray<OdGeVector3d> getNormales() const;

  /** \details
    Returns an array with the UV parameters for this mesh.

    \returns OdArray object with points of the UV parameters.
    \remarks
    This method is deprecated and will be removed in further releases. Please use getVerticesData() method instead.
  */
  OdArray<OdGePoint2d> getUVParameters() const;

  /** \details
    Returns an array with the triangles for this shell.

    \returns OdArray object with the trianglulated faces. Each element of the
    face is a 0-based index of a vertex.

    \remarks
    Each element of a triangle is a 0-based index of vertex instead of 1-based
    returned by the getFaces() method.
  */
  OdArray<OdNwTriangleIndexes> getTriangles();

  /** \details
  Returns a vertices data object.

  \returns OdNwVerticesDataPtr objects with vertices, normals, colors etc.
  */
  OdNwVerticesDataPtr getVerticesData() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwGeometryMesh object pointers.
*/
typedef OdSmartPtr<OdNwGeometryMesh> OdNwGeometryMeshPtr;

#endif //__TNW_GEOMETRYMESH_H__
