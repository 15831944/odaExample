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

#ifndef _ODTV_ENTITY_H_INCLUDED_
#define _ODTV_ENTITY_H_INCLUDED_

#include "Tv.h"
#include "TvIObject.h"
#include "TvGeometryData.h"
#include "TvLinetype.h"
#include "TvLayer.h"
#include "TvGeometryGridData.h"
#include "TvLight.h"
#include "TvCamera.h"
#include "TvAttributeResolver.h"

#include "Br/BrBrep.h"

#include "RcsFileServices/RxRcsFileServices.h"

class OdTvEntity;
class OdTvVisualStyleId;
class OdPointCloudScanDatabase;
class OdPointCloudProjectDatabase;
class OdPointCloudDataSource;

//DOM-IGNORE-BEGIN
typedef OdRxObject OdDbBaseDatabase;
//DOM-IGNORE-END

/** \details
  A data type that represents a smart pointer to an <link OdTvEntity, OdTvEntity> object.
*/
typedef OdTvSmartPtr<OdTvEntity> OdTvEntityPtr;

class OdTvInsert;

/** \details
  A data type that represents a smart pointer to an <link OdTvInsert, OdTvInsert> object.
*/
typedef OdTvSmartPtr<OdTvInsert> OdTvInsertPtr;

class OdTvGsViewId;

/** \details
  A data type that represents an array of OdTvGsViewId objects.
*/
typedef OdArray<OdTvGsViewId> OdTvGsViewIdsArray;

/** \details
  The base interface class for a Visualize SDK entity identifier that allows access to an entity.
  \sa
  <link tv_working_with_base_classes_entity, Work with Entities>
*/
class ODTV_EXPORT OdTvEntityId : public OdTvId
{
public:

  /** \details
    Enumerates entity types.
  */
  enum EntityTypes
  {
    kUndefined = 0, // An undefined type
    kEntity = 1,    // An entity type.
    kInsert = 2,    // An insert object.
    kLight  = 3,    // A light object.
    kCamera = 4     // A camera object.
  };

  /** \details
    Returns the type of an entity.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current type of the entity represented as a value of the <link OdTvEntityId::EntityTypes, EntityTypes> enumeration.
    \remarks 
    If the rc parameter is not null and the entity type has been successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  EntityTypes getType(OdTvResult* rc = NULL) const;
  
  /** \details
    Opens the entity determined with its identifier for a read or write operation. 
    
    \param mode [in] An open mode value (read or write).
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the entity object.
    \remarks
    If the rc parameter is not null and the entity has been successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  OdTvEntityPtr openObject(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const;

  /** \details
    Opens the entity determined with its identifier as an <link OdTvInsert, OdTvInsert> object for a read or write operation. 
    
    \param mode [in] An open mode value (read or write).
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the insert object.
    \remarks
    If the rc parameter is not null and the entity has been successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_base_classes_reference_geometry, Work with Reference Geometry (Inserts)>
  */
  OdTvInsertPtr openObjectAsInsert(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const;

  /** \details
    Opens the entity determined with its identifier as an <link OdTvLight, OdTvLight> object for a read or write operation. 
    
    \param mode [in] An open mode value (read or write).
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the light object.
    \remarks
    If the rc parameter is not null and the entity has been successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_lights, Work with Lights>
  */
  OdTvLightPtr openObjectAsLight(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const;

  /** \details
    Opens the entity determined with its identifier as an <link OdTvCamera, OdTvCamera> object for a read or write operation.
    
    \param mode [in] An open mode value (read or write).
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the light object.
    \remarks
    If the rc parameter is not null and the entity has been successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  OdTvCameraPtr openObjectAsCamera( OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL ) const;

  /** \details
    Returns the model in which this entity placed.
    
    \param rc  [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the ID of the model in which this entity placed.
    \remarks
    Since the entity can be child (or grandchild) not only of model but also of block, this function can return invalid ID.
    In this case it is possible to call 'getOwnerBlock' method.
    If the rc parameter is not null and the flag value has been successfully returned, the rc parameter accepts tvOk value; otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_base_classes_model, Work with Models>
  */
  OdTvModelId getOwnerModel(OdTvResult *rc = NULL) const;

  /** \details
    Returns the block in which this entity placed.
    
    \param rc  [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the ID of the block in which this entity placed.
    \remarks
    Since the entity can be child (or grand child) not only of block but also of model, this function can return invalid ID.
    In this case it is possible to call 'getOwnerModel' method.
    If the rc parameter is not null and the flag value has been successfully returned, the rc parameter accepts tvOk value; otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_base_classes_reference_geometry, Work with Reference Geometry (Inserts)>
  */
  OdTvBlockId getOwnerBlock(OdTvResult *rc = NULL) const;

  /** \details
    Retrieves the WCS extents of this entity (including models transformations).
    
    \param rc  [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the WCS extents of the entity.
    \remarks
    Work for the entities and inserts which are children of the OdTvModel.
    If the rc parameter is not null and the flag value has been successfully returned, the rc parameter accepts tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual OdTvExtents3d getWCSExtents(OdTvResult* rc = NULL) const;
};

/** \details
  A data type that represents an array of Visualize SDK entity identifiers.
*/
typedef OdArray<OdTvEntityId, OdMemoryAllocator<OdTvEntityId> > OdTvEntityIdsArray;

/** \details
  The abstract interface class for a Visualize SDK entity object.
*/ 
class ODTV_EXPORT OdTvEntity : public OdTvHandledIObject
{
public:

  /** \details
    Enumerates types for the subentity removing procedure (method removeSubEntities).
  */
  enum SubEntityRemovingFilter
  {
    kRemoveAlone = 0x01,             // only alone subentites will be removed
    kRemoveEmpty = 0x02,             // only empty subentities will be removed
    kRemoveWithSingleChild = 0x04,   // only subentites with one child geometry will be removed
    kRemoveAll = 0xFF                // remove all subentities
  };

//DOM-IGNORE-BEGIN
  //**************************************************************************************
  // Group of the methods for the creating (inserting) the geometry in the entity
  //**************************************************************************************
//DOM-IGNORE-END
  
  /** \details
    Adds a simple line to the entity.
    
    \param start  [in] A start (first) point of the line.
    \param end    [in] An end (second) point of the line.
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created line object if the line has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the line has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_lines, Work with Lines>
  */
  virtual OdTvGeometryDataId appendPolyline(const OdTvPoint& start, const OdTvPoint& end, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a polyline to the entity.
    
    \param points [in] An array of polyline points.
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created polyline object if the polyline has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the polyline has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_lines, Work with Lines>
  */
  virtual OdTvGeometryDataId appendPolyline(const OdTvPointArray& points, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a polyline to the entity.
    
    \param nPoints [in] A number of polyline points.
    \param points  [in] A pointer to the beginning of the polyline points array.
    \param rc      [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created polyline object if the polyline has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the polyline has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_lines, Work with Lines>
  */
  virtual OdTvGeometryDataId appendPolyline(OdInt32 nPoints, const OdTvPoint* points, OdTvResult* rc = NULL) = 0;
   
  /** \details
    Adds an unfilled circle to the entity.
    
    \param firstPoint  [in] A first point of the circle.
    \param secondPoint [in] A second point of the circle.
    \param thirdPoint  [in] A third point of the circle.
    \param rc          [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created circle object if the circle has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the circle has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_circles, Work with Circles>
  */
  virtual OdTvGeometryDataId appendCircle(const OdTvPoint& firstPoint, const OdTvPoint& secondPoint, const OdTvPoint& thirdPoint, OdTvResult* rc = NULL) = 0;
  
  /** \details
    Adds an unfilled circle (via radius) to the entity.
    
    \param center [in] A circle center point.
    \param radius [in] A circle radius value.
    \param normal [in] A circle normal vector.
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created circle object if the circle has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the circle has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_circles, Work with Circles>
  */
  virtual OdTvGeometryDataId appendCircle(const OdTvPoint& center, double radius, const OdTvVector& normal, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds an unfilled circle arc to the entity.
    
    \param startPoint  [in] A circle arc start point.
    \param middlePoint [in] A circle arc middle point.
    \param endPoint    [in] A circle arc end point.
    \param rc          [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created circle arc if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the circle arc has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_arcs, Work with Arcs>
  */
  virtual OdTvGeometryDataId appendCircleArc(const OdTvPoint& startPoint, const OdTvPoint& middlePoint, const OdTvPoint& endPoint, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a circle wedge to the entity.
    
    \param startPoint  [in] A circle wedge start point.
    \param middlePoint [in] A circle wedge middle point.
    \param endPoint    [in] A circle wedge end point.
    \param rc          [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created circle wedge if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the circle wedge has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_arcs, Work with Arcs>
  */
  virtual OdTvGeometryDataId appendCircleWedge(const OdTvPoint& startPoint, const OdTvPoint& middlePoint, const OdTvPoint& endPoint, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds an unfilled ellipse to the entity.
    
    \param centerPoint [in] A point that represents the ellipse center.
    \param majorPoint  [in] A point that represents the ellipse major radius.
    \param minorPoint  [in] A point that represents the ellipse minor radius.
    \param rc          [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created ellipse if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the ellipse has been created and added, the rc parameter accepts the tvOk value,
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_ellipses, Work with Ellipses>
  */
  virtual OdTvGeometryDataId appendEllipse(const OdTvPoint& centerPoint, const OdTvPoint& majorPoint, const OdTvPoint& minorPoint, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds an unfilled elliptical arc to the entity.
    
    \param centerPoint [in] A point that represents the ellipse center.
    \param majorPoint  [in] A point that represents the ellipse major radius.
    \param minorPoint  [in] A point that represents the ellipse minor radius.
    \param startAng    [in] The start angle for the elliptical arc.
    \param endAng      [in] The end angle for the elliptical arc.
    \param rc          [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created elliptical arc if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the elliptical arc has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_arcs, Work with Arcs>
  */
  virtual OdTvGeometryDataId appendEllipticArc(const OdTvPoint& centerPoint, const OdTvPoint& majorPoint, const OdTvPoint& minorPoint, double startAng, double endAng, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds an unfilled polygon to the entity.
    
    \param points [in] A polygon's vertices.
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created polygon if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the polygon has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_polygons, Work with Polygons>
  */
  virtual OdTvGeometryDataId appendPolygon(const OdTvPointArray& points, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds an unfilled polygon to the entity.
    
    \param nPoints  [in] A polygon vertex quantity.
    \param points   [in] A pointer to an <link OdTvPoint, OdTvPoint> array that contains polygon vertices.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created polygon if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the polygon has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_polygons, Work with Polygons>
  */
  virtual OdTvGeometryDataId appendPolygon(OdInt32 nPoints, const OdTvPoint* points, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a shell to the entity.
    
    \param points [in] An array of points that represents shell vertices.
    \param faces  [in] An array that represents faces.
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created shell if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the shell has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    Each face is represented in the face array in the following way: the first value is the number of face vertices, and other values
    are the indices from the points array. The next value is the number of the next face's vertices followed by the indices
    of the face vertices in the point array, and so on.
    \sa
    <link tv_geometry_shells, Work with Shells>
  */
  virtual OdTvGeometryDataId appendShell(const OdTvPointArray& points, const OdInt32Array& faces, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a shell to the entity.
    
    \param nPoints      [in] A shell vertex quantity.
    \param points       [in] A pointer to an <link OdTvPoint, OdTvPoint> array that contains shell vertices.
    \param faceListSize [in] A size of the face array.
    \param faces        [in] A pointer to an array of faces.
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created shell if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the shell has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    Each face is represented in the face array in the following way: the first value is the number of face vertices, and other values
    are the indices from the points array. The next value is the number of the next face vertices followed by the indices
    of the face vertices in the point array, and so on.
    \sa
    <link tv_geometry_shells, Work with Shells>
  */
  virtual OdTvGeometryDataId appendShell(OdInt32 nPoints, const OdTvPoint* points, OdInt32 faceListSize, const OdInt32* faces, OdTvResult* rc = NULL) = 0;
  
  /** \details
    Adds a cylinder to the entity as a shell.
    
    \param point1 [in] A center point of the first cylinder circle.
    \param point2 [in] A center point of the second cylinder circle.
    \param radius [in] A cylinder radius.
    \param caps   [in] An option that determines whether caps of the cylinder are rendered.
    \param nDiv   [in] The quantity of edges that join the two circles and form the cylindrical surface.
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created shell if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the shell has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_shells, Work with Shells>
  */
  virtual OdTvGeometryDataId appendShellFromCylinder(const OdTvPoint& point1, const OdTvPoint& point2, double radius, OdTvCylinderData::Capping caps = OdTvCylinderData::kBoth, int nDiv = 10, OdTvResult* rc = NULL) = 0;
  
  /** \details
    Adds a cylinder to the entity as a shell.
    
    \param nPoints  [in] A quantity of center points for cylinder circles.
    \param points   [in] A pointer to the beginning of the array of center points for cylinder circles.
    \param nRadii   [in] A size of the circle radius array.
    \param radii    [in] A pointer to the beginning of the circle radius values array.
    \param caps     [in] An option that determines whether caps of the cylinder are rendered.
    \param nDiv     [in] The quantity of edges that join the circles and form the cylindrical surface.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created shell if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the shell has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    This method can create cylindrical objects with different radii, for example cones.
    \sa
    <link tv_geometry_shells, Work with Shells>
  */
  virtual OdTvGeometryDataId appendShellFromCylinder(OdInt32 nPoints, const OdTvPoint* points, OdInt32 nRadii, const double* radii, const OdTvCylinderData::Capping& caps = OdTvCylinderData::kBoth, int nDiv = 10, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a sphere to the entity as a shell.
    
    \param center         [in] A sphere center.
    \param radius         [in] A sphere radius.
    \param axis           [in] A vector that specifies the sphere axis.
    \param primeMeridian  [in] A vector that specifies the sphere prime meridian.
    \param nDiv           [in] A value that determines the quantity of vertices, faces and edges for the created shell.
    \param rc             [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created shell if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the shell has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_shells, Work with Shells>
  */
  virtual OdTvGeometryDataId appendShellFromSphere(const OdTvPoint& center, double radius, const OdTvVector& axis = OdTvVector(0., 1., 0.), const OdTvVector& primeMeridian = OdTvVector(1., 0., 0.), int nDiv = 10, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a box to the entity as a shell.
    
    \param centerPt    [in] A box center.
    \param dLength        [in] A box length.
    \param dWidth         [in] A box width.
    \param dHeight        [in] A box height.
    \param baseNormal     [in] A vector that specifies the box height direction (by other words defines the base plane).
    \param lengthDir      [in] A vector that specifies the box length direction.
    \param rc             [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created shell if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the shell has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_shells, Work with Shells>
  */
  virtual OdTvGeometryDataId appendShellFromBox(const OdTvPoint& centerPt, double dLength, double dWidth, double dHeight, const OdTvVector& baseNormal = OdTvVector::kZAxis, const OdTvVector& lengthDir = OdTvVector::kXAxis, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a mesh to the entity.
    
    \param nRows          [in] A count of mesh rows.
    \param nColumns       [in] A count of mesh columns.
    \param verticesArray  [in] An array of mesh vertices.
    \param rc             [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created mesh if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the mesh has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_meshes, Work with Meshes>
  */
  virtual OdTvGeometryDataId appendMesh(OdUInt32 nRows, OdUInt32 nColumns, const OdTvPointArray& verticesArray, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a mesh to the entity.
    
    \param nRows     [in] A count of mesh rows.
    \param nColumns  [in] A count of mesh columns.
    \param nVertices [in] A count of mesh vertices.
    \param vertices  [in] A pointer to the beginning of the mesh vertices array.
    \param rc        [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created mesh if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the mesh has been created and added; the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_meshes, Work with Meshes>
  */
  virtual OdTvGeometryDataId appendMesh(OdUInt32 nRows, OdUInt32 nColumns, OdUInt32 nVertices, const OdTvPoint* vertices, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a sphere to the entity.
    
    \param center         [in] A sphere center.
    \param radius         [in] A sphere radius.
    \param axis           [in] A vector that specifies the sphere axis.
    \param primeMeridian  [in] A vector that specifies the sphere prime meridian.
    \param rc             [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created sphere if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the sphere has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_spheres, Work with Spheres>
  */
  virtual OdTvGeometryDataId appendSphere(const OdTvPoint& center, double radius, const OdTvVector& axis = OdTvVector(0., 1., 0.), const OdTvVector& primeMeridian = OdTvVector(1., 0., 0.), OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a cylinder to the entity.
    
    \param point1 [in] A center point of the first cylinder circle.
    \param point2 [in] A center point of the second cylinder circle.
    \param radius [in] A cylinder radius.
    \param caps   [in] An option that determines whether caps of the cylinder are rendered.
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created cylinder if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the cylinder has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_cylinders, Work with Cylinders>
  */
  virtual OdTvGeometryDataId appendCylinder(const OdTvPoint& point1, const OdTvPoint& point2, double radius, OdTvCylinderData::Capping caps = OdTvCylinderData::kBoth, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a cylinder to the entity.
    
    \param points   [in] An array of center points for cylinder circles.
    \param radii    [in] An array of circle radii values.
    \param caps     [in] An option that determines whether caps of the cylinder are rendered.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created cylinder if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the cylinder has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    This method can create a cylindric object with different radii, for example cones.
    \sa
    <link tv_geometry_cylinders, Work with Cylinders>
  */
  virtual OdTvGeometryDataId appendCylinder(const OdTvPointArray& points, const OdDoubleArray& radii, OdTvCylinderData::Capping caps = OdTvCylinderData::kBoth, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a poly cylinder to the entity.
    
    \param nPoints  [in] A quantity of center points for cylinder circles.
    \param points   [in] A pointer to the beginning of the array of center points for cylinder circles.
    \param nRadii   [in] A size of the circle radius array.
    \param radii    [in] A pointer to the beginning of the circle radius values array.
    \param caps     [in] An option that determines whether caps of the cylinder are rendered.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created cylinder if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the cylinder has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    This method can create a cylindric object with different radii (a poly cylinder), for example cones.
    \sa
    <link tv_geometry_cylinders, Work with Cylinders>
  */
  virtual OdTvGeometryDataId appendCylinder(OdInt32 nPoints, const OdTvPoint* points, OdInt32 nRadii, const double* radii, const OdTvCylinderData::Capping& caps = OdTvCylinderData::kBoth, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a box to the entity.
    
    \param centerPt       [in] A box center.
    \param dLength        [in] A box length.
    \param dWidth         [in] A box width.
    \param dHeight        [in] A box height.
    \param baseNormal     [in] A vector that specifies the box height direction (by other words defines the base plane).
    \param lengthDir      [in] A vector that specifies the box length direction.
    \param rc             [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created shell if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the shell has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_boxes, Work with Boxes>
  */
  virtual OdTvGeometryDataId appendBox(const OdTvPoint& centerPt, double dLength, double dWidth, double dHeight, const OdTvVector& baseNormal = OdTvVector::kZAxis, const OdTvVector& lengthDir = OdTvVector::kXAxis, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a brep to the entity.
    
    \param brep                 [in] A brep object.
    \param pDb                  [in] The database object for this brep.
    \param pMaterialResolver    [in] Pointer to the material resolver.
    \param rc    [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the text object if it has been successfully created and added to the entity;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the text object has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  virtual OdTvGeometryDataId appendBrep(const OdBrBrep& brep, OdDbBaseDatabase *pDb, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a text to the entity.
    
    \param ref_point  [in] A starting point for the text.
    \param msg        [in] Text content.
    \param rc         [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the text object if it has been successfully created and added to the entity;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the text object has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_text, Work with Text Entities>
  */
  virtual OdTvGeometryDataId appendText(const OdTvPoint& ref_point, const OdString& msg, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a NURBS to the entity.
    
    \param degree         [in] A curve degree value.
    \param controlPoints  [in] An array of control points.
    \param weights        [in] An array of weights.
    \param knots          [in] An array of knots.
    \param start          [in] A start value.
    \param end            [in] An end value.
    \param rc             [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created NURBS if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the NURBS has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_nurbs, Work with NURBS>
  */
  virtual OdTvGeometryDataId appendNurbs(unsigned int degree, const OdTvPointArray& controlPoints, const OdDoubleArray& weights, const OdDoubleArray& knots, double start = 0., double end = 1., OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a NURBS to the entity.
    
    \param degree         [in] A curve degree value.
    \param nControlPoints [in] A quantity of the control points.
    \param controlPoints  [in] A pointer to the beginning of the control points array.
    \param weights        [in] A pointer to the beginning of the array of weights.
    \param nKnots         [in] A quantity of knots.
    \param knots          [in] A pointer to the beginning of the array of knots.
    \param start          [in] A start value.
    \param end            [in] An end value.
    \param rc             [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created NURBS if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the NURBS has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_nurbs, Work with NURBS>
  */
  virtual OdTvGeometryDataId appendNurbs(unsigned int degree, unsigned int nControlPoints, const OdTvPoint* controlPoints, const double* weights, unsigned int nKnots, const double* knots, double start = 0., double end = 1., OdTvResult* rc = NULL) = 0;
  
  /** \details
    Adds an infinite line to the entity.
    
    \param first  [in] A first point.
    \param second [in] A second point.
    \param ilt    [in] A type of line (ray or line).
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created line if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the line has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_lines, Work with Lines>
  */
  virtual OdTvGeometryDataId appendInfiniteLine(const OdTvPoint& first, const OdTvPoint& second, OdTvInfiniteLineData::Type ilt, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds an image to the entity.
    
    \param imageId  [in] An identifier of the image object to be appended.
    \param origin   [in] A point that specifies the position where the image should be inserted.
    \param u        [in] A U-vector.
    \param v        [in] A V-vector.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the image object if it has been successfully created and added; otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the image object has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_raster_images, Work with Raster Image Geometry Data>
  */
  virtual OdTvGeometryDataId appendRasterImage(OdTvRasterImageId imageId, const OdTvPoint& origin, const OdTvVector& u, const OdTvVector& v, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a point cloud to the entity.
    
    \param points [in] An array of points.
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the point cloud object if it has been successfully created and added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the point cloud has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  virtual OdTvGeometryDataId appendPointCloud(const OdTvPointArray& points, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a point cloud to the entity.
    
    \param nPoints [in] A quantity of points.
    \param points  [in] A pointer to the beginning of the point array.
    \param rc      [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the point cloud object if it has been successfully created and added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the point cloud has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  virtual OdTvGeometryDataId appendPointCloud(OdInt32 nPoints, const OdTvPoint* points, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a point cloud to the entity.
    
    \param pDataSource    [in]  A pointer to data source object.
    \param rc             [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the RCS point cloud object if it has been successfully created and added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the point cloud has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  virtual OdTvGeometryDataId appendPointCloud(OdPointCloudDataSourcePtr pDataSource, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a grid to the entity.
    
    \param origin       [in] A grid origin.
    \param firstPoint   [in] A grid first point.
    \param secondPoint  [in] A grid second point.
    \param firstCount   [in] A grid cell count along the first axis.
    \param secondCount  [in] A grid cell count along the second axis.
    \param type         [in] A grid type.
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the grid object if it has been successfully created and added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the grid has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    A grid is a planar object and is represented as a set of faces.
    The origin determines the starting point for the grid.
    The first and second point determine the measurement vectors along two grid axes.
    The firstCount and secondCount specify the quantity of grid cells along both axes.
    \sa
    <link tv_geometry_grids, Work with Grids>
  */
  virtual OdTvGeometryDataId appendGrid(const OdTvPoint& origin, const OdTvPoint& firstPoint = OdTvPoint(1. ,0., 0.), const OdTvPoint& secondPoint = OdTvPoint(0., 1., 0.),
                                        OdInt32 firstCount = 0, OdInt32 secondCount = 0, const OdTvGridData::Type type = OdTvGridData::kQuadratic, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a plane colored area to the entity. 
    
    \param points [in] An array of the area points. 
    \param faces  [in] An array of the point indices that determine the area faces.
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the appended area object if it has been successfully created and added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the area has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    An area is a planar object and is represented with a set of faces. 
    Each face is defined with a quantity of points and a set of indices from the points array that determines the face configuration.
  */
  virtual OdTvGeometryDataId appendColoredShape(const OdTvPointArray& points, const OdInt32Array& faces, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a plane colored area to the entity. 
    
    \param nPoints      [in] A size of the points array. 
    \param points       [in] A pointer to the beginning of the area points array. 
    \param faceListSize [in] A size of the array of the point indices that determine the area faces.
    \param faces        [in] An array of the point indices that determine the area faces.
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the appended area object if it has been successfully created and added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the area has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    An area is a planar object and is represented with a set of faces. 
    Each face is defined with a quantity of points and a set of indices from the points array that determine the face configuration.
  */
  virtual OdTvGeometryDataId appendColoredShape(OdInt32 nPoints, const OdTvPoint* points, OdInt32 faceListSize, const OdInt32* faces, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a subentity object to the entity.
    
    \param name [in] A subentity object's name.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the appended subentity if it has been successfully created and added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the subentity has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_sub_entities, Work with Sub-Entities>
  */
  virtual OdTvGeometryDataId appendSubEntity(OdString name = OdString::kEmpty, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds an insert object to the entity.
    
    \param blockId  [in] An identifier of the block object that is added as an insert object.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the appended insert object if it has been successfully created and added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the insert object has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_sub_inserts, Work with Sub-Inserts>
  */
  virtual OdTvGeometryDataId appendInsert(const OdTvBlockId& blockId, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a RCS point cloud data to the entity.
    
    \param pScanDb  [in]  A pointer to scan database (.rcs).
    \param pProjDb  [in]  A pointer to host project database (.rcp). It may be NULL.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the RCS point cloud object if it has been successfully created and added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the RCS point cloud has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  virtual OdTvGeometryDataId appendRcsPointCloud(OdPointCloudScanDatabasePtr pScanDb,
    OdPointCloudProjectDatabasePtr pProjDb = NULL, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a RCS point cloud data to the entity.
    
    \param pDataSource    [in]  A pointer to data source object.
    \param outputFilePath [in]  A file path for the .rcs file which will be the data storage for the object.
    \param rc             [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the RCS point cloud object if it has been successfully created and added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the RCS point cloud has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the 'outputFilePath' is empty, the file was saved in the temporary files folder (which will be returned by odrxSystemServices()->getTemporaryPath())
    with generated unique name
  */
  virtual OdTvGeometryDataId appendRcsPointCloud(OdPointCloudDataSourcePtr pDataSource, const OdString& outputFilePath = OdString(), OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a progressive mesh to the entity.
    
    \param points [in] An array of points that represents mesh vertices.
    \param faces  [in] An array that represents faces.
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created progressive mesh if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the shell has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    Each face is represented in the face array in the following way: the first value is the number of face vertices, and other values
    are the indices from the points array. The next value is the number of the next face's vertices followed by the indices
    of the face vertices in the point array, and so on.
    \sa
    <link tv_geometry_progressive_mesh, Work with Progressive Mesh>
  */
  virtual OdTvGeometryDataId appendProgressiveMesh(const OdTvPointArray& points, const OdInt32Array& faces, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a progressive mesh to the entity.
    
    \param nPoints      [in] A mesh vertex quantity.
    \param points       [in] A pointer to an <link OdTvPoint, OdTvPoint> array that contains mesh vertices.
    \param faceListSize [in] A size of the face array.
    \param faces        [in] A pointer to an array of faces.
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the created shell if it has been successfully added;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the progressive mesh has been created and added, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    Each face is represented in the face array in the following way: the first value is the number of face vertices, and other values
    are the indices from the points array. The next value is the number of the next face vertices followed by the indices
    of the face vertices in the point array, and so on.
    \sa
    <link tv_geometry_progressive_mesh, Work with Progressive Mesh>
  */
  virtual OdTvGeometryDataId appendProgressiveMesh(OdInt32 nPoints, const OdTvPoint* points, OdInt32 faceListSize, const OdInt32* faces, OdTvResult* rc = NULL) = 0;

  /** \details
    Removes geometry data with the specified identifier from the entity.
    
    \param geomId [in] A geometry data identifier.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the write operation.
    \remarks
    If the specified geometry data has been successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult removeGeometryData(const OdTvGeometryDataId& geomId) = 0;

  /** \details
    Clears all geometry data that the entity contains.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the write operation.
    \remarks
    If all geometry data has been successfully removed from the entity, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult clearGeometriesData() = 0;

  /** \details
    Returns a smart pointer to an iterator object to get sequential access to the entity geometry data objects.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the iterator.
    \remarks
    If the rc parameter is not null and the iterator returned by the method is correct, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is null (or not passed in the calling subroutine),
    you can check whether the correct iterator was returned by the method
    by checking whether the returned smart pointer is not NULL.
  */
  virtual OdTvGeometryDataIteratorPtr getGeometryDataIterator(OdTvResult* rc = NULL) = 0;

  //DOM-IGNORE-BEGIN
  //**************************************************************************************
  // Group of the methods for the using transform matrix with this entity
  //**************************************************************************************
  //DOM-IGNORE-END

  /** \details
    Rotates the entity around the X, Y and Z axes.
    
    \param x [in] A rotation angle around the X-axis (in degrees).
    \param y [in] A rotation angle around the Y-axis (in degrees).
    \param z [in] A rotation angle around the Z-axis (in degrees).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks  
    If the entity has been successfully rotated, the method returns tvOk; otherwise it returns an appropriate error code.
    The method joins the appropriate rotation matrix to the entity's transformation matrix.
  */
  virtual OdTvResult rotate(double x, double y, double z) = 0;

  /** \details
    Rotates the entity around a specified arbitrary vector.
    
    \param aVector  [in] An arbitrary vector.
    \param ang      [in] A rotation angle in degrees.
    \param center   [in] A rotation center point.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks  
    If the entity has been successfully rotated, the method returns tvOk; otherwise it returns an appropriate error code.
    The method joins the appropriate rotation matrix to the entity's transformation matrix.
  */
  virtual OdTvResult rotateAxis(const OdTvVector& aVector, double ang, const OdTvPoint& center = OdTvPoint::kOrigin) = 0;

  /** \details
    Moves the entity geometry along the X, Y, Z axes.
    
    \param x [in] A translation distance along the X-axis (in degrees).
    \param y [in] A translation distance along the Y-axis (in degrees).
    \param z [in] A translation distance along the Z-axis (in degrees).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks  
    If the entity has been successfully moved, the method returns tvOk; otherwise it returns an appropriate error code.
    The method joins the translation matrix to the entity's transformation matrix.  
  */
  virtual OdTvResult translate(double x, double y, double z) = 0;

  /** \details
    Moves the entity geometry along a specified vector for a distance that is equal to the vector length.
    
    \param aVector [in] A translation vector.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks  
    If the entity has been successfully moved, the method returns tvOk; otherwise it returns an appropriate error code.
    The method joins the translation matrix to the entity's transformation matrix.  
  */
  virtual OdTvResult translate(const OdTvVector& aVector) = 0;

  /** \details
    Scales the entity along the X, Y and Z axes using specified multipliers.
    
    \param x [in] A scale multiplier for the X-axis.
    \param y [in] A scale multiplier for the Y-axis.
    \param z [in] A scale multiplier for the Z-axis.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks  
    If the entity has been successfully scaled, the method returns tvOk; otherwise it returns an appropriate error code.
    The method joins the scaling matrix to the entity's transformation matrix.  
  */
  virtual OdTvResult scale(double x, double y, double z) = 0;

  /** \details
    Sets a new transformation matrix that can rotate, translate (move) and scale the entity.
    
    \param matrix [in] A transformation matrix object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks  
    If the transformation matrix has been successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setModelingMatrix(const OdTvMatrix& matrix) = 0;

  /** \details
    Retrieves the current transformation matrix for the entity. 
    A transformation matrix can rotate, translate (move) and scale the entity.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the transformation matrix represented as an instance of the <link OdTvMatrix, OdTvMatrix> class.
    \remarks 
    If the rc parameter is not null and the transformation matrix has been successfully returned, the rc parameter accepts tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual OdTvMatrix getModelingMatrix(OdTvResult* rc = NULL) const = 0;

  /** \details
    Appends a new transformation matrix to the entity. 
    Appending a new transformation matrix means that the new matrix and existing matrix will be multiplied.
    
    \param matrix [in] A new transformation matrix object to append.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks  
    If the new transformation matrix has been successfully appended, the method returns tvOk; otherwise it returns an appropriate error code. 
  */
  virtual OdTvResult appendModelingMatrix(const OdTvMatrix& matrix) = 0;

  //DOM-IGNORE-BEGIN
  //**************************************************************************************
  // Misc methods
  //**************************************************************************************
  //DOM-IGNORE-END
  
  /** \details
    Sets the name for the entity.
    
    \param sName [in]  A new entity name.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks  
    If the new name has been successfully set, the method returns tvOk; otherwise it returns an appropriate error code. 
  */
  virtual OdTvResult setName(const OdString& sName) = 0;

  /** \details
    Retrieves the current name of the entity.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current entity name.
    \remarks 
    If the rc parameter is not null and the name has been successfully returned, the rc parameter accepts tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual OdString getName(OdTvResult* rc = NULL) const = 0;

  /** \details
    Marks the entity for one regeneration.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks  
    If the entity has been successfully marked for regeneration, the method returns tvOk; otherwise it returns an appropriate error code. 
  */
  virtual OdTvResult regen() = 0;

  /** \details
    Sets the auto regeneration flag value. 
    The auto regeneration flag determines whether the entity should be regenerated for each redraw (if true) or not (if false).
    
    \param bOn [in] A new flag value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks  
    If the new flag value has been successfully set, the method returns tvOk; otherwise it returns an appropriate error code. 
  */
  virtual OdTvResult setAutoRegen(bool bOn) = 0;

  /** \details
    Retrieves the current value of the auto regeneration flag.
    The auto regeneration flag determines whether the entity should be regenerated for each redraw (if true) or not (if false).
    
    \param rc  [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if the entity should be regenerated for each redraw; otherwise it returns false.
    \remarks 
    If the rc parameter is not null and the flag value has been successfully returned, the rc parameter accepts tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual bool getAutoRegen(OdTvResult*rc = NULL) const = 0;

  /** \details
    Sets the target display mode for the entity.
    
    \param targetMode [in] A new value of the target display mode.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks  
    If the new target display mode has been successfully set, the method returns tvOk; otherwise it returns an appropriate error code. 
  */
  virtual OdTvResult setTargetDisplayMode(OdTvGeometryData::TargetDisplayMode targetMode) = 0;

  /** \details
    Retrieves the current target display mode for the entity.
    
    \param rc  [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current target display mode value.
    \remarks 
    If the rc parameter is not null and the target display mode value has been successfully returned, the rc parameter accepts tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual OdTvGeometryData::TargetDisplayMode getTargetDisplayMode(OdTvResult*rc = NULL) const = 0;

  /** \details
    Sets new extents for the entity.
    
    \param ext [in] An object of the <link OdTvExtents3d, OdTvExtents3d> class that represents new extents for the entity.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks  
    If the new extents have been successfully set, the method returns tvOk; otherwise it returns an appropriate error code. 
  */
  virtual OdTvResult setExtents(const OdTvExtents3d& ext) = 0;

  /** \details
    Retrieves the current extents of the specified type for the entity. 
    
    \param ext    [out] A placeholder for the extents object.
    \param eType  [in] A type of the retrieved extents.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the extents have been successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getExtents(OdTvExtents3d& ext, OdTv::ExtentsType eType = OdTv::kPreferred) const = 0;

  /** \details
    Adds the view in which entity will be drawn.
    
    \param    viewId [in] View, in which this entity will be drawn.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the view have been successfully add, the method returns tvOk; otherwise it returns an appropriate error code.
    For the performance issue during adding the new view dependency there is only one check that the view is valid. All other
    things like presence of the entity's parent model in the view should be check at the user's side.
  */
  virtual OdTvResult addViewDependency(const OdTvGsViewId& viewId) = 0;

  /** \details
    Removes the view from the views in which the entity should be drawn.
    
    \param    viewId [in] View, which should be removed from the views in which this entity will be drawn.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the view have been successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult removeViewDependency(const OdTvGsViewId& viewId) = 0;

  /** \details
    Removes any view dependencies which means that the entity will be drawn in all views.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the operation has been successfully performed, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult removeViewDependencies() = 0;

  /** \details
    Checks whether the entity is view dependent (means should be drawn in the specified views).
    
    \param rc  [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if the entity is view-dependent; otherwise it returns false.
    \remarks
    If the rc parameter is not null and the flag value has been successfully returned, the rc parameter accepts tvOk value; otherwise it contains an
    appropriate error code. The view can be still view dependent even if there is no view dependencies. This can happen in the case of the deleting the view.
    To fully remove the view dependencies state use 'removeViewDependencies' method.
  */
  virtual bool isViewDependent(OdTvResult* rc = NULL) = 0;

  /** \details
    Returns the views in which this entity should be drawn.
    
    \param rc  [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns views array in which this entity should be drawn.
    \remarks
    If the rc parameter is not null and the views array has been successfully returned, the rc parameter accepts tvOk value; otherwise it contains an
    appropriate error code. The view can be still view dependent even if this function has returned the empty array. This can happen in the case of the deleting the view.
    To fully remove the view dependencies state use 'removeViewDependencies' method.
  */
  virtual OdTvGsViewIdsArray getViewDependencies(OdTvResult *rc = NULL) = 0;

  /** \details
    Copies all entity's data to a specified entity (attributes, geometries etc). 
    All current data in the target entity will be deleted or overwritten.
    
    \param targetEntityId [in] A target <link OdTvEntityId, entity identifier>. The data will be copied to the entity the identifier refers.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the operation was successfully performed, the method returns tvOk; otherwise it returns an appropriate error code.
    This function is designed for copying entities within the same database. If source and destination entities belong to different databases
    default OdTvAttributeResolver will be created and used. Using copyTo(OdTvEntityId& targetEntityId, OdTvAttributeResolverPtr pResolver) will be
    more optimal in this case.
  */
  virtual OdTvResult copyTo(OdTvEntityId& targetEntityId) const = 0;

  /** \details
    Copies all entity's data to a specified entity (attributes, geometries etc). 
    All current data in the target entity will be deleted or overwritten.
    
    \param targetEntityId [in] A target <link OdTvEntityId, entity identifier>. The data will be copied to the entity the identifier refers.
    \param pResolver      [in] A smart pointer to the instance of OdTvAttributeResolver.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the operation was successfully performed, the method returns tvOk; otherwise it returns an appropriate error code.
    This function is designed for copying entities from different databases. If source and destination entities belong to the same database using
    copyTo(OdTvEntityId& targetEntityId) will be more optimal.
  */
  virtual OdTvResult copyTo(OdTvEntityId& targetEntityId, OdTvAttributeResolverPtr pResolver) const = 0;

  /** \details
    Copies all entity's geometry to a specified entity.
    
    \param targetEntityId [in] A target <link OdTvEntityId, entity identifier>. The data will be copied to the entity the identifier refers.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the operation has been successfully performed, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult copyGeometryTo(OdTvEntityId& targetEntityId) const = 0;

  /** \details
    Transforms the sub-entites from this entity in to a set of entities and adds them to the parent's model.
    
    \param pNewEntities  [out] Receives an array of ids to the new entities.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    Entities resulting from the explosion are appended to the specified array (if it is specified). Works only for the top-level entities (direct childs of the model).
    If the operation has been successfully performed, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult explodeSubEntities(OdTvEntityIdsArray* pNewEntities = NULL) = 0;

  /** \details
    Removes subentities replacing them by it's childs geometries.
    
    \param removingFlags  [in] Indicates which subentities should be removed (empty, without brothers (alone), with only one child geometry or all)
    \param bRecursive     [in] True if the subentities itself also should be processed. By other word if it is need to remove subentities from subentities
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    During this operation the subentities will be removed and replaced by their geometries.
    If the operation has been successfully performed, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult removeSubEntities(OdUInt8 removingFlags = kRemoveEmpty, bool bRecursive = false) = 0;

  /** \details
    Returns true if and only if the entity has no geometries.
    
    \param rc  [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if and only if the entity has no geometry.
    \remarks
    If the rc parameter is not null and the flag value has been successfully returned, the rc parameter accepts tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual bool isEmpty(OdTvResult *rc = NULL) const = 0;

  /** \details
    Returns the number of geometries in this entity.
    
    \param bRecursive             [in] True if it is need to take into account the geometries inside subentities (if they exists).
    \param bIgnoreSubentityItself [in] True if it is need to skip counting of the subentities itself (if they exists). Works only when bRecursive flag is true.
    \param rc                     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the number of child geometries.
    \remarks
    If the rc parameter is not null and the flag value has been successfully returned, the rc parameter accepts tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual OdUInt32 getNumGeometries(bool bRecursive = false, bool bIgnoreSubentityItself = false, OdTvResult *rc = NULL) const = 0;

  //DOM-IGNORE-BEGIN
  //**************************************************************************************
  // Group of the methods for setting the attributes
  //**************************************************************************************
  //DOM-IGNORE-END
  
  /** \details
    Sets a new color for the entity or for the specified geometry type in the entity.
    
    \param color    [in] A new color represented with an instance of the <link OdTvColorDef, OdTvColorDef> class.
    \param geomType [in] A geometry type.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the geomType parameter value is not specified, the color is applied to the whole entity.
    If the color has been successfully applied, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setColor(const OdTvColorDef& color, OdUInt16 geomType = (OdUInt16)OdTvGeometryData::kAll) = 0;

  /** \details
    Retrieves the current color of the entity or of the specified geometry type in the entity.
    
    \param geomType [in] The type of the geometry. If omitted, the color information for the whole entity is returned.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current color definition represented as a RGB color, inherited color or color index.
    \remarks 
    If the rc parameter is not null and the color information has been successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvColorDef getColor(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll, OdTvResult* rc = NULL) = 0;

  /** \details
    Sets the lineweight value for the whole entity or the specified geometry type in the entity.
    
    \param lw       [in] A new lineweight value.
    \param geomType [in] A geometry type. If omitted, the lineweight is applied to the whole entity.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the lineweight has been successfully applied, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_lineweights, Work with Lineweights>
  */
  virtual OdTvResult setLineWeight(const OdTvLineWeightDef& lw, OdUInt16 geomType = (OdUInt16)OdTvGeometryData::kAll) = 0;

  /** \details
    Retrieves the current lineweight of the entity or of the specified geometry type in the entity.
    
    \param geomType [in] The type of the geometry. If omitted, the lineweight value for the whole entity is returned.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current lineweight value.
    \remarks 
    If the rc parameter is not null and the lineweight value has been successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_attributes_lineweights, Work with Lineweights>
  */
  virtual OdTvLineWeightDef getLineWeight(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll, OdTvResult* rc = NULL) = 0;

  /** \details
    Sets the linetype value for the whole entity or the the specified geometry type in the entity.
    
    \param lt       [in] A new linetype value.
    \param geomType [in] A geometry type. If omitted, the linetype is applied to the whole entity.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the linetype has been successfully applied, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult setLinetype(const OdTvLinetypeDef& lt, OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll) = 0;

  /** \details
    Retrieves the current linetype of the entity or of the specified geometry type in the entity.
    
    \param geomType [in] The type of the geometry. If omitted, the linetype value for the whole entity is returned.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current linetype value.
    \remarks 
    If the rc parameter is not null and the linetype value has been successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvLinetypeDef getLinetype(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll, OdTvResult* rc = NULL) = 0;

  /** \details
    Sets the linetype scale value for the whole entity or the specified geometry type in the entity.
    
    \param linetypeScale  [in] A new linetype scale value.
    \param geomType       [in] A geometry type. If omitted, the linetype scale is applied to the whole entity.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the linetype scale has been successfully applied, the method returns tvOk, otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult setLinetypeScale(double linetypeScale, OdUInt16 geomType = (OdUInt16)OdTvGeometryData::kAll) = 0;

  /** \details
    Retrieves the current linetype scale of the entity or of the specified geometry type in the entity.
    
    \param geomType [in] The type of the geometry. If omitted, the linetype scale value for the whole entity is returned.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current linetype scale value.
    \remarks 
    If the rc parameter is not null and the linetype scale value has been successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual double getLinetypeScale(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll, OdTvResult* rc = NULL) = 0;

  /** \details
    Sets a new layer object for the whole entity or the specified geometry type in the entity.
    
    \param layer    [in] A new layer definition object.
    \param geomType [in] A geometry type. If omitted, the layer is applied to the whole entity.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the layer object has been successfully applied, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setLayer(const OdTvLayerDef& layer, OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll) = 0;

  /** \details
    Retrieves the layer for the entity or for the specified geometry type in the entity.
    
    \param geomType [in] The type of the geometry. If omitted, the layer definition for the whole entity is returned.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current layer definition object for the whole entity or for a specified type of its geometry.
    \remarks 
    If the rc parameter is not null and the layer object has been successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvLayerDef getLayer(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll, OdTvResult* rc = NULL) = 0;

  /** \details
    Set the visibility property value for the whole entity or for the specified geometry type in the entity.
    
    \param visible  [in] A new visibility property value.
    \param geomType [in] The type of the geometry. If omitted, the visibility property affects to the whole entity.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the visibility property value has been successfully applied, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVisibility(const OdTvVisibilityDef& visible, OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll) = 0;

  /** \details
    Retrieves the visibility property value for the entity or for the specified geometry type in the entity.
    
    \param geomType [in] The type of the geometry. If omitted, the visibility property for the whole entity is returned.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current visibility property value for the whole entity or for a specified type of its geometry.
    \remarks 
    If the rc parameter is not null and the visibility property value has been successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual OdTvVisibilityDef getVisibility(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a text style for all text objects that the entity contains.
    
    \param textStyle [in] A text style definition object to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the text style has been successfully applied, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_text_style, Work with Text Styles>
  */
  virtual OdTvResult setTextStyle(const OdTvTextStyleDef& textStyle) = 0;

  /** \details
    Retrieves the text style of all text objects that the entity contains.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current text style for entity text objects.
    \remarks 
    If the rc parameter is not null and the text style definition has been successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_attributes_text_style, Work with Text Styles>
  */
  virtual OdTvTextStyleDef getTextStyle(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the transparency property value for the entity or for the specified geometry type in the entity.
    
    \param transparency [in] A new transparency property value.
    \param geomType     [in] The type of the geometry. If omitted, the transparency property affects to the whole entity.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the transparency property value has been successfully applied, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setTransparency(const OdTvTransparencyDef& transparency, OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll) = 0;

  /** \details
    Retrieves the transparency property value for the entity or for the specified geometry type in the entity.
    
    \param geomType [in] The type of the geometry. If omitted, the transparency property for the whole entity is returned.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current transparency property value for the whole entity or for a specified type of its geometry.
    \remarks 
    If the rc parameter is not null and the transparency property value has been successfully returned; the rc parameter accepts the tvOk value, otherwise it contains an
    appropriate error code.
  */
  virtual OdTvTransparencyDef getTransparency(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll, OdTvResult* rc = NULL) = 0;
  
  /** \details
    Sets the material for the entity.
    
    \param material [in] A material definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the material has been successfully applied, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setMaterial(const OdTvMaterialDef& material) = 0;

  /** \details
    Retrieves the current material applied to the entity.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current material definition for the entity.
    \remarks 
    If the rc parameter is not null and the material definition has been successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvMaterialDef getMaterial(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a material mapper for the entity. The material mapper is used to map the materials.
    
    \param mapper [in] A material mapper definition object to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the material mapper has been successfully applied, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvResult setMaterialMapper(const OdTvMapperDef& mapper) = 0;

  /** \details
    Retrieves the current material mapper definition that is applied to the entity.
    The material mapper is used to map the materials.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current material mapper definition for the entity.
    \remarks 
    If the rc parameter is not null and the material mapper definition has been successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual const OdTvMapperDef getMaterialMapper(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new visual style for the entity. The visual style should be compatible with the visual style assigned to the view.
    This functionality should be used very carefully. The typical case for it is the customization of the highlighting.
    
    \param vsId [in] An identifier of the visual style object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the visual style was successfully applied, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_visual_styles, Work with Visual Styles>
  */
  virtual OdTvResult setVisualStyle(const OdTvVisualStyleId& vsId) = 0;

  /** \details
    Retrieves the current visual style applied to the entity.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the identifier of the current visual style object associated with the entity.
    \remarks
    If the rc parameter is not null and the new visual style object's identifier was successfully returned, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_visual_styles, Work with Visual Styles>
  */
  virtual OdTvVisualStyleId getVisualStyle(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the selectability property value for the entity. 
    
    \param selectability [in] A new selectability property value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the selectability property value has been successfully changed, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_features_selections, Work with Selections>
  */
  virtual OdTvResult setSelectability(const OdTvSelectabilityDef& selectability) = 0;

  /** \details
    Retrieves the current value of the selectability property for the entity.
    
    \param bInherited [out] A placeholder for a flag that determines whether the selectability property is inherited (if true) or not (if false).
    \param rc         [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current value of the selectability property for the entity.
    \remarks 
    If the rc parameter is not null and the selectability property value has been successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_features_selections, Work with Selections>
  */
  virtual OdTvSelectabilityDef getSelectability(bool* bInherited = NULL, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the sectionable property to the entity. This mean, that all geometry in this entity can be cut via cutting plane.
    
    \param bVal [in] A flag that specify if sectionable is enabled.
    \remarks
    If the sectionable property value has been successfully changed, the method returns tvOk; otherwise it returns an appropriate error code.
    This method is actual only for the top level entities. If this method will be called for subentity, tvNotSupported will be returned.
    Setting this property to the true means that the geometry contents of the entity will be cut in the case of the presence of the cutting planes.
    \sa
    <link tv_working_with_features_cutting_planes, Work with Cutting Planes>
  */
  virtual OdTvResult setSectionable(bool bVal) = 0;

  /** \details
    Retrieves the current value of the sectionable property for the entity.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current sectionable property.
    \remarks
    If the rc parameter is not null and the sectionable property was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_features_cutting_planes, Work with Cutting Planes>
  */
  virtual bool getSectionable(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets that it is need to show normals for all shell objects in this entity.
    
    \param bShow         [in] Flag which indicates that it is need to show shells normals.
    \param normalsLength [in] A lines length which will be used for the normals visualization.
    \param normalsColor  [in] A lines color which will be used for the normals visualization. If this parameter is default, color will be taken from shell color.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the normalsLength is 0., the lines length will be calculated automatically for each shell on the basis of shell extents' size.
    If the normalsColor is 'default', the lines color will be the same as the color of normal's source (face or vertex).
    If normals visibility is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    This method is introduced for the convenience with purpose the aggregate a set of calls for each shell inside the entity in one common call. 
    So, this method simply calls the appropriate method of each shell object inside the entity and translates the parameters to these shell objects.
    Thus, entity itself will not store any information like 'normalsLength' except the 'bShow' value. It also means, that if the shell will be added to entity
    after the calling this method, the normals for this shell will be shown (if need) with default parameters.
    \sa
    <link tv_geometry_shells, Work with Shells>
  */
  virtual OdTvResult setShowShellNormals(bool bShow, double normalsLength = 0., const OdTvRGBColorDef& normalsColor = OdTvRGBColorDef()) = 0;

  /** \details
    Returns true if normals are visible for each shell inside the entity.
    
    \param rc             [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if shell normals are visible, false otherwise.
    \remarks
    If the normals visibility is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
    This method returns only the value with which the method 'setShowShellNormals' was called. It means that if after calling the 'setShowShellNormals'
    method with 'bShow' = true will be a set of calls of the 'setShowNormals' method for each shell object inside the entity with 'bShow' = false,
    this method will return true, but on the screen there will be no visible normals.
    \sa
    <link tv_geometry_shells, Work with Shells>
  */
  virtual bool getShowShellNormals(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets that it is need to show sharp edges for all shell objects in this entity.
    
    \param bShow         [in] Flag which indicates that it is need to show sharp edges of all shells.
    \param edgesWidth    [in] A lines lineweight which will be used for the sharp edges visualization.
    \param edgesColor    [in] A lines color which will be used for the sharp edges visualization.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the edgesColor is 'default', the lines color will be taken from each shell color
    If sharp edges visibility is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    This method is introduced for the convenience with purpose the aggregate a set of calls for each shell inside the entity in one common call. 
    So, this method simply calls the appropriate method of each shell object inside the entity and translates the parameters to these shell objects.
    Thus, entity itself will not store any information 'edgesWidth' except the 'bShow' value. It also means, that if the shell will be added to entity
    after the calling this method, the sharp edges for this shell will be shown (if need) with default parameters.
    \sa
    <link tv_geometry_shells, Work with Shells>
  */
  virtual OdTvResult setShowShellSharpEdges(bool bShow, OdUInt8 edgesWidth = 5, const OdTvRGBColorDef& edgesColor = OdTvRGBColorDef()) = 0;

  /** \details
    Returns true if shell sharp edges are visible.
    
    \param rc            [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if shell sharp edges are visible, false otherwise.
    \remarks
    If the sharp edges visibility is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
    This method returns only the value with which the method 'setShowShellSharpEdges' was called. It means that if after calling the 'setShowShellSharpEdges'
    method with 'bShow' = true will be a set of calls of the 'setShowSharpEdges' method for each shell object inside the entity with 'bShow' = false,
    this method will return true, but on the screen there will be no visible sharp edges.
    \sa
    <link tv_geometry_shells, Work with Shells>
  */
  virtual bool getShowShellSharpEdges(OdTvResult* rc = NULL) const = 0;

  /** \details
    Searches for a sub-entity using its handler. 
    
    \param h  [in] A handler of the sub-entity.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the identifier of the sub-entity if it has been found, otherwise returns a null-value identifier.
    \remarks 
    If the rc parameter is not null and the sub-entity with the specified handler has been found, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    Another way to check whether the sub-entity has been found is to check the identifier that is returned by the method; if the identifier's isNull() method returns false, 
    the sub-entity has been found.
    \sa
    <link tv_geometry_shells, Work with Shells>
  */
  virtual OdTvGeometryDataId findSubEntity(const OdUInt64 h, OdTvResult* rc = NULL) = 0;

  /** \details
    Specifies entity shadow behavior.
    \param bCastShadows   [in] Flag which indicates that entity should (true) or should not (false) cast shadows.
    \param bReceiveShadow [in] Flag which indicates that entity should (true) or should not (false) receive shadows.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvResult setShadowParameters( bool bCastShadows, bool bReceiveShadow ) = 0;
  
  /** \details
    Retrieves entity shadow behavior.
    
    \param bCastShadows   [out] Flag which indicates that entity should (true) or should not (false) cast shadows.
    \param bReceiveShadow [out] Flag which indicates that entity should (true) or should not (false) receive shadows.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvResult getShadowParameters( bool& bCastShadows, bool& bReceiveShadow ) = 0;
  
  /** \details
    Checks that entity content is suitable for section filling.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if and only if  entity content is suitable for section filling.
    \remarks This method checks shells and returns true if all shells are suitable for section filling or there are no shells in the entity.
  */
  virtual bool checkForSectionFilling( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Repairs entity content for section filling.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks In the current implementation this method simply removes backface culling flag from all shells inside the entity. After that
    the shells in the entity will not participate in the section filling. 
  */
  virtual OdTvResult fixForSectionFilling() = 0;
  
  /** \details
    Specifies that entity shells topology require checking.
    
    \param bCheck [in] Flag which indicates that entity should (true) or should not (false) check shells topology.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvResult setNeedCheckShellsTopology( bool bCheck ) = 0;
  
  /** \details
    Checks that entity shells topology require checking.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if and only if  entity shells topology require additional checking.
  */
  virtual bool getNeedCheckShellsTopology( OdTvResult* rc = NULL ) const = 0;
};


/** \details
  The base interface class for the iterator of Visualize SDK entity objects.
  An iterator object provides sequential access to a collection of entities. 
*/
class ODTV_EXPORT OdTvEntitiesIterator : public OdTvIterator, public OdTvIObject
{
public:
  /** \details
    Retrieves the entity that is currently referenced by the iterator object.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the entity identifier if the iterator refers to an entity; otherwise it returns an identifier with a null value.
    \remarks 
    If the rc parameter is not null and the entity identifier has been successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    If the iterator refers to an entity, the identifier that the method returns is not null (i.e., the result of the isNull() method of the identifier is equal to false).
  */
  virtual OdTvEntityId getEntity(OdTvResult* rc = NULL) const = 0;

  /** \details
    Searches the entity defined through its identifier and moves the iterator to this entity if found.
    
    \param entityId [in]  An entity identifier.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the entity specified through its identifier has been found, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult seek(const OdTvEntityId& entityId) = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvEntitiesIterator, OdTvEntitiesIterator> object.
*/
typedef OdTvSmartPtr<OdTvEntitiesIterator> OdTvEntitiesIteratorPtr;

#endif //_ODTV_ENTITY_H_INCLUDED_
