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

#ifndef _ODTV_GEOMETRYDATA_H_INCLUDED_
#define _ODTV_GEOMETRYDATA_H_INCLUDED_

#include "Tv.h"
#include "TvIObject.h"
#include "TvUserData.h"
#include "TvTraitsDef.h"
#include "TvGeometryShellData.h"
#include "TvGeometryMeshData.h"
#include "TvGeometryTypifiedData.h"
#include "TvGeometryTypifiedDataMisc.h"
#include "TvGeometryTypifiedData3D.h"
#include "TvGeometryProgressiveMeshData.h"
#include "TvLinetype.h"
#include "TvLayer.h"
#include "TvGeometryGridData.h"
// #include "TvModel.h"

class OdTvEntity;

/** \details
A data type that represents a smart pointer to an <link OdTvEntity, OdTvEntity> object.
*/
typedef OdTvSmartPtr<OdTvEntity> OdTvEntityPtr;

class OdTvEntityId;
class OdTvModelId;
class OdTvGeometryDataId;

/** \details
  This is an interface class for manipulating Visualize geometry data.
*/
class ODTV_EXPORT OdTvGeometryData : public OdTvIObjectWithXdata
{
public:

  /** \details
    Types of geometry data.
  */
  enum GeometryTypes
  {
    kNone                   = 0,  // No geometry data.
    kAll                    = 1,  // All types of geometry data.
    kPolylines              = 2,  // Lines and polylines.
    kEdges                  = 4,  // Edges data, i.e. lines connecting vertices of a polygon, shell, or mesh, or the border of an ellipse or a circle.
    kFaces                  = 8,  // Faces data, i.e. interior filled areas of polygons, shells, meshes, ellipses, and circles (surfaces).
    kVertices               = 16, // Data about vertices.
    kText                   = 32, // A color of the text.
  };

  /** \details
    Target display modes of the geometry data.
  */
  enum TargetDisplayMode
  {
    kEveryWhere = 0,  // All display modes.
    kWireframe = 1,   // Wireframe display mode.
    kRender = 2       // Rendering display mode.
  };

  /** \details
    The object snap mode.
  */
  enum SnapMode
  {
    kEnd          = 0,  // Endpoints
    kMiddle       = 1,  // Middle
    kNear         = 2,  // Nearest
    kCenter       = 3,  // Center
    kVertex       = 4   // Vertex
  };

  /** \details
    Retrieves the current type of the geometry data.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current type of the geometry data represented with a value of the <link OdTv::OdTvGeometryDataType, OdTvGeometryDataType> enumeration.
    \remarks
    If the rc parameter is not null and the geometry data type was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTv::OdTvGeometryDataType getType(OdTvResult* rc = NULL) const =  0;

  /** \details
    Retrieves the parent entity of the geometry data.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the identifier of the parent entity.
    \remarks
    If the rc parameter is not null and the entity identifier was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    If the geometry data lies inside the top level entity, this method returns the same result as 'getParentTolLevelEntity'.
    Top level entity is an entity whose parent is OdTvModel or OdTvBlock in contrast to an entity which is subentity and whose parent is another entity.
    \sa
    <link tv_working_with_base_classes_entity, Work with Entities>
  */
  virtual OdTvEntityId getParentEntity(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the parent subentity of the geometry data.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the identifier of the parent subentity.
    \remarks
    If the rc parameter is not null and the subentity identifier was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    If the geometry data lies inside the top level entity, this method returns an empty identifier, otherwise this method returns the same as result 'getParentEntity' in the following context:
    geomId.getParentSubEntity().openAsSubEntity() == geomId.getParentEntity().openObject().
    Top level entity is an entity whose parent is OdTvModel or OdTvBlock in contrast to an entity which is subentity and whose parent is another entity.
  */
  virtual OdTvGeometryDataId getParentSubEntity(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the top level parent entity of the geometry data.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the identifier of the top level parent entity.
    \remarks
    If the rc parameter is not null and the top level entity identifier was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    Top level entity is an entity whose parent is OdTvModel or OdTvBlock in contrast to an entity which is subentity and whose parent is another entity.
    If the geometry data lies inside the top level entity, this method return the same result as 'getParentEntity'.
    \sa
    <link tv_working_with_base_classes_entity, Work with Entities>
  */
  virtual OdTvEntityId getParentTopLevelEntity(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new color value for the geometry data.
    
    \param color    [in] A new color value.
    \param geomType [in] A geometry type value. The color is assigned to geometry of this type. 
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the set color operation.
    \remarks
    If the specified color was successfully assigned to the geometry data, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setColor(const OdTvColorDef& color, OdUInt16 geomType = (OdUInt16)kAll) = 0;

  /** \details
    Retrieves the current color, as RGB, inherited or index, of the geometry data for the specified geometry type.
    
    \param geomType [in] A type of geometry.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the instance of the <link OdTvColorDef, OdTvColorDef> class that represents the current color.
    \remarks
    If the rc parameter is not null and the color object was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvColorDef getColor(GeometryTypes geomType = kAll, OdTvResult*rc = NULL) = 0;

  /** \details
    Sets a new lineweight of the geometry data.
    
    \param lw [in] A new lineweight value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the set lineweight operation.
    \remarks
    If the specified lineweight value was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_lineweights, Work with Lineweights>
  */
  virtual OdTvResult setLineWeight(const OdTvLineWeightDef& lw) = 0;

  /** \details
    Retrieves the current lineweight of the geometry data.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the instance of the <link OdTvLineWeightDef, OdTvLineWeightDef> class that represents the current lineweight value.
    \remarks
    If the rc parameter is not null and the lineweight object was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_lineweights, Work with Lineweights>
  */
  virtual OdTvLineWeightDef getLineWeight(OdTvResult* rc = NULL) = 0;

  /** \details
    Sets the linetype of the geometry data.
    
    \param lt [in] A new linetype value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the set linetype operation.
    \remarks
    If the specified linetype value was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult setLinetype(const OdTvLinetypeDef& lt) = 0;

  /** \details
    Retrieves the current linetype of the geometry data.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the instance of the <link OdTvLineWeightDef, OdTvLineWeightDef> class that represents the current linetype value.
    \remarks
    If the rc parameter is not null and the linetype object was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvLinetypeDef getLinetype(OdTvResult*rc = NULL) = 0;

  /** \details
    Sets the linetype scale of the geometry data.
    
    \param linetypeScale [in] A new linetype scale.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the set linetype scale.
    \remarks
    If the specified linetype scale was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult setLinetypeScale(double linetypeScale) = 0;
  
  /** \details
    Retrieves the current linetype scale of the geometry data.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current linetype scale.
    \remarks
    If the rc parameter is not null and the linetype scale was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual double getLinetypeScale (OdTvResult* rc = NULL) = 0;

  /** \details
    Sets the layer of the geometry data.
    
    \param layer [in] An instance of the <link OdTvLayerDef, OdTvLayerDef> class that defines the layer.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the layer setting operation.
    \remarks
    If the specified layer was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setLayer(const OdTvLayerDef& layer) = 0;

  /** \details
    Retrieves the current layer for the geometry data.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current layer object.
    \remarks
    If the rc parameter is not null and the layer was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvLayerDef getLayer(OdTvResult*rc = NULL) = 0;

  /** \details
    Sets the visibility property of the geometry.
    
    \param visible [in] A new visibility property value represented with an <link OdTvVisibilityDef, OdTvVisibilityDef> object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the visibility setting operation.
    \remarks
    If the specified visibility value was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVisibility(const OdTvVisibilityDef& visible) = 0;

  /** \details
    Retrieves the current visibility property for the geometry data.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current visibility property represented with an <link OdTvVisibilityDef, OdTvVisibilityDef> object.
    \remarks
    If the rc parameter is not null and the visibility property was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvVisibilityDef getVisibility(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the transparency property of the geometry.
    
    \param transparency [in] A new transparency property value represented with an <link OdTvTransparencyDef, OdTvTransparencyDef> object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the transparency setting operation.
    \remarks
    If the specified transparency value was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setTransparency(const OdTvTransparencyDef& transparency) = 0;

  /** \details
    Retrieves the current transparency property for the geometry data.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current transparency property represented with an <link OdTvTransparencyDef, OdTvTransparencyDef> object.
    \remarks
    If the rc parameter is not null and the transparency property was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvTransparencyDef getTransparency(OdTvResult* rc = NULL) = 0;

  /** \details
    Sets the material for the geometry.
    
    \param material [in] A material definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the material has been successfully applied, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setMaterial(const OdTvMaterialDef& material) = 0;

  /** \details
    Retrieves the current material applied to the geometry.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current material definition for the geometry.
    \remarks
    If the rc parameter is not null and the material definition has been successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvMaterialDef getMaterial(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the database that contains the geometry data.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the identifier of the database object that contains the geometry data.
    \remarks
    If the rc parameter is not null and the database identifier was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_base_classes_db, Work with Visualize Databases>
  */
  virtual OdTvDatabaseId getDatabase(OdTvResult* rc = NULL) = 0;

  //**************************************************************************************
  // Misc methods
  //**************************************************************************************

  /** \details
    Sets the target display mode of the geometry.
    
    \param targetMode [in] A new value of the target display mode.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified display mode value was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setTargetDisplayMode(TargetDisplayMode targetMode) = 0;

  /** \details
    Retrieves the current target display mode of the geometry.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the target display mode of the geometry.
    \remarks
    If the rc parameter is not null and the target display mode value was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual TargetDisplayMode getTargetDisplayMode(OdTvResult*rc = NULL) const = 0;

  /** \details
    Copies the geometry data to a specified entity.
    
    \param targetEntityId [out] A placeholder for an identifier of the target entity.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the identifier of the geometry data object created in the result of the copy operation.
    \remarks
    If the rc parameter is not null and the geometry data was copied successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvGeometryDataId copyTo(OdTvEntityId& targetEntityId, OdTvResult*rc = NULL) const = 0;

  //**************************************************************************************
  // Group of the methods for the using transform matrix with this entity
  //**************************************************************************************

  /** \details
    Rotates the geometry data around X, Y and Z axes with specified angles (represented in degrees).
    
    \param x [in] An angle to rotate around the X axis.
    \param y [in] An angle to rotate around the Y axis.
    \param z [in] An angle to rotate around the Z axis.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the rotation operation.
    \remarks
    If the geometry data was successfully rotated, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult rotate(double x, double y, double z) = 0;

  /** \details
    Rotates the geometry data around an arbitrary vector with a specified angle (represented in degrees).
    
    \param aVector  [in] An arbitrary vector.
    \param ang      [in] An angle to rotate around the vector.
    \param center   [in] The rotation center.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the rotation operation.
    \remarks
    If the geometry data was successfully rotated, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult rotateAxis(const OdTvVector& aVector, double ang, const OdTvPoint& center = OdTvPoint::kOrigin) = 0;

  /** \details
    Moves the geometry data along X, Y and Z axes with specified distances.
    
    \param x [in] A distance to move along the X axis.
    \param y [in] A distance to move along the Y axis.
    \param z [in] A distance to move along the Z axis.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the translation operation.
    \remarks
    If the geometry data was successfully moved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult translate(double x, double y, double z) = 0;

  /** \details
    Moves the geometry data along an arbitrary vector.
    
    \param aVector  [in] An arbitrary vector.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the translation operation.
    \remarks
    If the geometry data was successfully moved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult translate(const OdTvVector& aVector) = 0;

  /** \details
    Sets a new scale rate for the geometry data along X, Y and Z axes.
    
    \param x [in] A scale rate along the X axis.
    \param y [in] A scale rate along the Y axis.
    \param z [in] A scale rate along the Z axis.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the scale operation.
    \remarks
    If the geometry data was successfully scaled, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult scale(double x, double y, double z) = 0;

  /** \details
    Sets a new transformation matrix for the geometry data. The transformation matrix rotates, translates and scales the geometry data.
    
    \param matrix [in] An instance of the transformation matrix represented with an <link OdTvMatrix, OdTvMatrix>  object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the transformation operation.
    \remarks
    If the transformation matrix was successfully applied to the geometry data, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setModelingMatrix(const OdTvMatrix& matrix) = 0;

  /** \details
    Retrieves the current transformation matrix applied to the geometry data. The transformation matrix rotates, translates and scales the geometry data.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current transformation matrix represented with an <link OdTvMatrix, OdTvMatrix> object.
    \remarks
    If the rc parameter is not null and the transformation matrix was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvMatrix getModelingMatrix(OdTvResult* rc = NULL) const = 0;

  /** \details
    Appends a new transformation matrix for the geometry data. The previously added transformation matrix (if exists) is multiplied by the new matrix.
    
    \param matrix [in] An instance of the transformation matrix represented with an <link OdTvMatrix, OdTvMatrix>  object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the transformation operation.
    \remarks
    If the transformation matrix was successfully added to the geometry data, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult appendModelingMatrix(const OdTvMatrix& matrix) = 0;

  /** \details
    Returns appropriate snap points of this geometry object.
    
    \param snapMode     [in]            Snap mode being queried.
    \param pickPoint    [in]            The WCS point picked during appropriate operation.
    \param xWorldToEye  [in]            The WCS->ECS transformation matrix.
    \param snapPoints   [out]           Array of snap points.
    \param pTransform   [optional in]   The transformation matrix.
    \param focalLength  [optional in]   The focus length. Should be used for the case of view perspective mode. Ignored if negative
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the snap points are successfully received, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getSnapPoints(OdTvGeometryData::SnapMode snapMode, const OdTvPoint& pickPoint,
                                   const OdTvMatrix& xWorldToEye, OdTvPointArray& snapPoints,
                                   const OdTvMatrix* pTransform = NULL, double focalLength = -1.) const = 0;

  /** \details
    Checks whether the requested snap mode is supported by this geometry object.
    
    \param snapMode  [in]  Snap mode to check.
    \param rc        [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the true if this geometry object supports the requested snap mode, otherwise returns false.
    \remarks
    If the rc parameter is not null and the support flag is returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool getSupportSnapMode(OdTvGeometryData::SnapMode snapMode, OdTvResult* rc = NULL) const = 0;

  //**************************************************************************************
  // set of the methods, which have returned the typified data
  //**************************************************************************************

  /** \details
    Retrieves the geometry data represented as a polyline if the data has the appropriate type.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the polyline data represented with an <link OdTvPolylineData, OdTvPolylineData> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as a polyline, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_lines, Work with Lines>
  */
  virtual OdTvPolylineDataPtr getAsPolyline(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as a circle if the data has the appropriate type.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the circle data represented with an <link OdTvCircleData, OdTvCircleData> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as a circle, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_circles, Work with Circles>
  */
  virtual OdTvCircleDataPtr getAsCircle(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as a circle arc if the data has the appropriate type.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the circle arc data represented with an <link OdTvCircleArcData, OdTvCircleArcData> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as a circle arc, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_arcs, Work with Arcs>
  */
  virtual OdTvCircleArcDataPtr getAsCircleArc(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as a circle wedge if the data has the appropriate type.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the circle wedge data represented with an <link OdTvCircleWedgeData, OdTvCircleWedgeData> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as a circle wedge, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_arcs, Work with Arcs>
  */
  virtual OdTvCircleWedgeDataPtr getAsCircleWedge(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as an ellipse if the data has the appropriate type.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the ellipse data represented with an <link OdTvEllipseData, OdTvEllipseData> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as an ellipse, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_ellipses, Work with Ellipses>
  */
  virtual OdTvEllipseDataPtr getAsEllipse(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as an elliptical arc if the data has the appropriate type.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the elliptical arc data represented with an <link OdTvEllipticArcData, OdTvEllipticArcData> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as an elliptical arc, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_arcs, Work with Arcs>
  */
  virtual OdTvEllipticArcDataPtr getAsEllipticArc(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as a polygon if the data has the appropriate type.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the polygon data represented with an <link OdTvPolygonData, OdTvPolygonData> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as a polygon, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_polygons, Work with Polygons>
  */
  virtual OdTvPolygonDataPtr getAsPolygon(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as a shell if the data has the appropriate type.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the shell data represented with an <link OdTvShellData, OdTvShellData> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as a shell, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_shells, Work with Shells>
  */
  virtual OdTvShellDataPtr getAsShell(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as a boundary representation for a read or write operation.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvBrepData, B-Rep entity>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  virtual OdTvBrepDataPtr getAsBrep(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as a mesh if the data has the appropriate type.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the mesh data represented with an <link OdTvMeshData, OdTvMeshData> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as a mesh, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_meshes, Work with Meshes>
  */
  virtual OdTvMeshDataPtr getAsMesh(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as a sphere if the data has the appropriate type.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the sphere data represented with an <link OdTvSphereData, OdTvSphereData> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as a sphere, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_spheres, Work with Spheres>
  */
  virtual OdTvSphereDataPtr getAsSphere(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as a cylinder if the data has the appropriate type.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the cylinder data represented with an <link OdTvCylinderData, OdTvCylinderData> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as a cylinder, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_cylinders, Work with Cylinders>
  */
  virtual OdTvCylinderDataPtr getAsCylinder(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as a box if the data has the appropriate type.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the box data represented with an <link OdTvBoxData, OdTvBoxData> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as a box, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_boxes, Work with Boxes>
  */
  virtual OdTvBoxDataPtr getAsBox(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as text if the data has the appropriate type.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the text data represented with an <link OdTvTextData, OdTvTextData> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as text, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_text, Work with Text Entities>
  */
  virtual OdTvTextDataPtr getAsText(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as a NURBS curve if the data has the appropriate type.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the NURBS curve data represented with an <link OdTvNurbsData, OdTvNurbsData> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as a NURBS curve, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_nurbs, Work with NURBS>
  */
  virtual OdTvNurbsDataPtr getAsNurbs(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as an infinite line if the data has the appropriate type.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the infinite line data represented with an <link OdTvInfiniteLineData, OdTvInfiniteLineData> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as an infinite line, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_lines, Work with Lines>
  */
  virtual OdTvInfiniteLineDataPtr getAsInfiniteLine(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as a raster image if the data has the appropriate type.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the raster image represented with an <link OdTvRasterImageData, OdTvRasterImageData> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as a raster image, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_raster_images, Work with Raster Image Geometry Data>
  */
  virtual OdTvRasterImageDataPtr getAsRasterImage(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as a point cloud if the data has the appropriate type.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the point cloud data represented with an <link OdTvPointCloudData, OdTvPointCloudData> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as a point cloud, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvPointCloudDataPtr getAsPointCloud(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as a grid if the data has the appropriate type.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the grid data represented with an <link OdTvGridData, OdTvGridData> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as a grid, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_grids, Work with Grids>
  */
  virtual OdTvGridDataPtr getAsGrid(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as a colored shape if the data has the appropriate type.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the colored shape data represented with an <link OdTvColoredShapeData, OdTvColoredShapeData> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as a colored shape, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvColoredShapeDataPtr getAsColoredShape(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as a Visualize sub-entity if the data has the appropriate type.
    
    \param mode [in] A mode value for opening the sub-entity.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the sub-entity data represented with an <link OdTvEntity, OdTvEntity> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as a sub-entity, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_sub_entities, Work with Sub-Entities>
  */
  virtual OdTvEntityPtr getAsSubEntity(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as an insert entity if the data has the appropriate type.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the insert entity represented with an <link OdTvInsertData, OdTvInsertData> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as an insert entity, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_sub_inserts, Work with Sub-Inserts>
  */
  virtual OdTvInsertDataPtr getAsInsert(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry data represented as a RCS point cloud if the data has the appropriate type.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the point cloud data represented with an <link OdTvRcsPointCloudData, OdTvRcsPointCloudData> object.
    \remarks
    If the rc parameter is not null and the geometry data can be represented as a RCS point cloud, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvRcsPointCloudDataPtr getAsRcsPointCloud(OdTvResult* rc = NULL) const = 0;

};

/** \details
  A data type that represents a smart pointer to an <link OdTvGeometryData, OdTvGeometryData> object.
*/
typedef OdTvSmartPtr<OdTvGeometryData> OdTvGeometryDataPtr;


/** \details
  The interface class for a geometry object identifier that allows access to the <link OdTvGeometryData, OdTvGeometryData> object.
*/
class ODTV_EXPORT OdTvGeometryDataId : public OdTvLinkId
{
public:

  /** \details
    Retrieves the geometry data type.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an <link OdTv::OdTvGeometryDataType, OdTvGeometryDataType> value that represents the geometry type.
    \remarks
    If the rc parameter is not null and the geometry type value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  OdTv::OdTvGeometryDataType getType(OdTvResult* rc = NULL) const;
  
  /** \details
    Opens the geometry data object, determined with its identifier, for a read or write operation. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvGeometryData, geometry data object>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  OdTvGeometryDataPtr openObject(OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as a polyline for a read or write operation. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvPolylineData, polyline entity>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_lines, Work with Lines>
  */
  OdTvPolylineDataPtr openAsPolyline(OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as a circle for a read or write operation. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvCircleData, circle entity>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_circles, Work with Circles>
  */
  OdTvCircleDataPtr openAsCircle(OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as a circle arc for a read or write operation. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvCircleArcData, circle arc entity>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_arcs, Work with Arcs>
  */
  OdTvCircleArcDataPtr openAsCircleArc(OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as a circle wedge for a read or write operation. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvCircleWedgeData, circle wedge entity>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_arcs, Work with Arcs>
  */
  OdTvCircleWedgeDataPtr openAsCircleWedge(OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as an ellipse for a read or write operation. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvEllipseData, ellipse entity>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_ellipses, Work with Ellipses>
  */
  OdTvEllipseDataPtr openAsEllipse(OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as an elliptical arc for a read or write operation. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvEllipticArcData, elliptic arc entity>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_arcs, Work with Arcs>
  */
  OdTvEllipticArcDataPtr openAsEllipticArc(OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as a polygon for a read or write operation. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvPolygonData, polygon entity>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_polygons, Work with Polygons>
  */
  OdTvPolygonDataPtr openAsPolygon(OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as a shell for a read or write operation. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvShellData, shell entity>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_shells, Work with Shells>
  */
  OdTvShellDataPtr openAsShell(OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as a boundary representation for a read or write operation.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvBrepData, B-Rep entity>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  OdTvBrepDataPtr openAsBrep(OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as a mesh for a read or write operation. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvMeshData, mesh entity>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_meshes, Work with Meshes>
  */
  OdTvMeshDataPtr openAsMesh(OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as a sphere for a read or write operation. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvSphereData, sphere entity>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_spheres, Work with Spheres>
  */
  OdTvSphereDataPtr openAsSphere(OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as a cylinder for a read or write operation. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvCylinderData, cylinder entity>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_cylinders, Work with Cylinders>
  */
  OdTvCylinderDataPtr openAsCylinder(OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as a box for a read or write operation. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvBoxData, box entity>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_boxes, Work with Boxes>
  */
  OdTvBoxDataPtr openAsBox(OdTvResult* rc = NULL) const;

 /** \details
    Opens the geometry data object, determined with its identifier, as text for a read or write operation. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvTextData, text entity>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_text, Work with Text Entities>
  */
  OdTvTextDataPtr openAsText(OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as a NURBS curve for a read or write operation. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvNurbsData, NURBS curve entity>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_nurbs, Work with NURBS>
  */
  OdTvNurbsDataPtr openAsNurbs(OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as an infinite line for a read or write operation.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvInfiniteLineData, infinite line entity>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_lines, Work with Lines>
  */
  OdTvInfiniteLineDataPtr openAsInfiniteLine(OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as a raster image for a read or write operation. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvRasterImageData, raster image object>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_raster_images, Work with Raster Image Geometry Data>
  */
  OdTvRasterImageDataPtr openAsRasterImage(OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as a point cloud for a read or write operation. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvPointCloudData, point cloud object>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  OdTvPointCloudDataPtr openAsPointCloud(OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as a grid for a read or write operation. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvGridData, grid object>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_grids, Work with Grids>
  */
  OdTvGridDataPtr openAsGrid(OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as a colored shape for a read or write operation. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvColoredShapeData, colored shape object>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  OdTvColoredShapeDataPtr openAsColoredShape(OdTvResult * rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as a sub-entity for a read or write operation. 
    
    \param mode [in] An open mode value (read-only, write-only).
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvEntity, sub-entity object>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_sub_entities, Work with Sub-Entities>
  */
  OdTvEntityPtr openAsSubEntity(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as an insert entity for a read or write operation. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvInsertData, insert entity>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_sub_inserts, Work with Sub-Inserts>
  */
  OdTvInsertDataPtr openAsInsert(OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as a RCS point cloud for a read or write operation.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvRcsPointCloudData, RCS point cloud object>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  OdTvRcsPointCloudDataPtr openAsRcsPointCloud(OdTvResult* rc = NULL) const;

  /** \details
    Opens the geometry data object, determined with its identifier, as a progressive mesh for a read or write operation. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the <link OdTvProgressiveMeshData, progressive mesh entity>.
    \remarks
    If the rc parameter is not null and the geometry data object was successfully opened, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  OdTvProgressiveMeshDataPtr openAsProgressiveMesh(OdTvResult* rc = NULL) const;
};

/** \details
  The abstract class that provides an interface for the geometry data iterator object.
  The objects of classes inherited from this class can be used to get sequential access (i.e. one-by-one) to geometries that the model contains.
*/
class ODTV_EXPORT OdTvGeometryDataIterator : public OdTvIterator, public OdTvIObject
{
public:
  /** \details
    Gets the geometry data currently referenced by the iterator.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the identifier of the geometry data that the iterator references.
    \remarks
    If the method successfully gets access to the referenced geometry, and the rc parameter is not NULL, it accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvGeometryDataId getGeometryData(OdTvResult* rc = NULL) const = 0;

  /** \details
    Searches for the geometry data specified with its identifier through the iterator object.
    
    \param geometryDataId [in]  A geometry data identifier to search for.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the search operation.
    If the block with the specified identifier is found, the method returns tvOk value; otherwise it returns an appropriate error code.
    \remarks
    If the block is found, the method changes the iterator position, therefore the iterator references the found block in this case.
  */
  virtual OdTvResult seek(const OdTvGeometryDataId& geometryDataId) = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvGeometryDataIterator, OdTvGeometryDataIterator> object.
*/
typedef OdTvSmartPtr<OdTvGeometryDataIterator> OdTvGeometryDataIteratorPtr;

#endif // _ODTV_GEOMETRYDATA_H_INCLUDED_

