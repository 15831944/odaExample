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




#ifndef _OD_DB_POLYFACE_MESH_
#define _OD_DB_POLYFACE_MESH_

#include "TD_PackPush.h"

#include "DbEntity.h"
#include "DbObjectIterator.h"
#include "DwgDeclareMembers.h"

class OdTvDbPolyFaceMeshVertex;
class OdTvDbSequenceEnd;
class OdTvDbFaceRecord;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbPolyFaceMeshVertex object pointers.
*/
typedef OdSmartPtr<OdTvDbPolyFaceMeshVertex> OdTvDbPolyFaceMeshVertexPtr;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbSequenceEnd object pointers.
*/
typedef OdSmartPtr<OdTvDbSequenceEnd> OdTvDbSequenceEndPtr;

/** \details
    This class represents PolyFaceMesh entities in an OdTvDbDatabase instance.
  
    \sa
    TD_Db

    \remarks
    A PolyFaceMesh entity consists of a list of PolyFaceMeshVertex (coordinate) vertices 
    and a list of OdTvDbFaceRecord face records.
    Together they define a set of 3D faces.
    
    \remarks
    Never derive from this class.

    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbPolyFaceMesh : public OdTvDbEntity
{
public:
  DWGMAP_DECLARE_MEMBERS(OdTvDbPolyFaceMesh);

  OdTvDbPolyFaceMesh();
  
  /** \details
    Returns the number of vertices in this PolyFaceMesh entity (DXF 71).
  */
  OdInt16 numVertices() const;

  /** \details
    Returns the number of faces in this PolyFaceMesh entity (DXF 72).
  */
  OdInt16 numFaces() const;
  
  /** \details
    Appends the specified face vertex onto this PolyFaceMesh entity.

    \param pVertex [in]  Pointer to the vertex to append.

    \returns
    Returns the Object ID of the appended face vertex.
  */
  OdTvDbObjectId appendVertex(
    OdTvDbPolyFaceMeshVertex* pVertex);
  
  /** \details
    Appends the specified face record onto this PolyFaceMesh entity.

    \param pFaceRecord [in]  Pointer to the face record to append.

    \returns
    Returns the Object ID of the newly appended face record.
  */
  OdTvDbObjectId appendFaceRecord(
    OdTvDbFaceRecord* pFaceRecord);
  
  /** \details
    Opens the specified vertex owned by this PolyFaceMesh entity.

    \param subObjId [in]  Object ID of vertex to be opened.
    \param mode [in]  Mode in which the object is being opened.
    \param openErasedOne [in]  If and only if true, erased objects will be opened.
    \returns
    Returns a SmartPointer to the opened object if successful, otherwise a null SmartPointer.
  */
  OdTvDbPolyFaceMeshVertexPtr openVertex(
    OdTvDbObjectId subObjId, 
    OdDb::OpenMode mode, 
    bool openErasedOne = false);
  
  /** \details
    Opens the OdTvDbSequenceEnd entity for this PolyfaceMesh entity.

    \param mode [in]  Mode in which to open the OdTvDbSequenceEnd entity.

    \returns
    Returns a SmartPointer to the newly opened OdTvDbSequenceEnd, or a null SmartPointer.

    \remarks
    This method is provided solely for applications that store XData on
    OdTvDbSequenceEnd entities; this is not recommended. 
  */
  OdTvDbSequenceEndPtr openSequenceEnd(
    OdDb::OpenMode mode);
  

 /** \details
    Removes all vertices and faces
*/
  void clear();

  /** \details
    Returns a SmartPointer to an iterator that can be used to traverse the vertices and face records owned 
    by this PolyFaceMesh entity.
  */
  OdTvDbObjectIteratorPtr vertexIterator() const;

  virtual bool subWorldDraw(
    OdGiWorldDraw* pWd) const;
  
  virtual OdResult dwgInFields(
    OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(
    OdTvDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdTvDbDxfFiler* pFiler);

  virtual void dxfOutFields(
    OdTvDbDxfFiler* pFiler) const;

  virtual void dxfOut(
    OdTvDbDxfFiler* pFiler) const;

  virtual OdResult dxfIn(
    OdTvDbDxfFiler* pFiler);

 /* virtual OdResult subGetClassID(
    void* pClsid) const;*/

  virtual OdResult dxfInFields_R12(
    OdTvDbDxfFiler* pFiler);

  virtual void dxfOutFields_R12(
    OdTvDbDxfFiler* pFiler) const;

  void subClose();

  virtual bool isPlanar() const;
  
  virtual OdResult getPlane(
    OdGePlane& plane, 
    OdDb::Planarity& planarity) const;

  virtual OdResult subTransformBy(
    const OdGeMatrix3d& xfm);

  OdResult subGetGeomExtents(
    OdGeExtents3d& extents) const;

  /** \remarks
    Creates and returns a set of OdTvDbFace entities.
  */
  virtual OdResult subExplode(
    OdRxObjectPtrArray& entitySet) const;

  /** \remarks
    Creates and returns a set of OdTvDbFace entities.
  */
  virtual OdResult explodeGeometry(OdRxObjectPtrArray& entitySet) const;

  OdResult subGetSubentPathsAtGsMarker( OdDb::SubentType type,
                                        OdGsMarker gsMark, 
                                        const OdGePoint3d& ,
                                        const OdGeMatrix3d& , 
                                        OdTvDbFullSubentPathArray& subentPaths, 
                                        const OdTvDbObjectIdArray* pEntAndInsertStack ) const;

  OdResult subGetGsMarkersAtSubentPath( const OdTvDbFullSubentPath& subPath, 
                                        OdGsMarkerArray& gsMarkers) const;

};
/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbPolyFaceMesh object pointers.
*/
typedef OdSmartPtr<OdTvDbPolyFaceMesh> OdTvDbPolyFaceMeshPtr;

#include "TD_PackPop.h"

#endif
