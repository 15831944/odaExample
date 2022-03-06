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

#ifndef _ODTV_ENTITYIMPL_H_INCLUDED_
#define _ODTV_ENTITYIMPL_H_INCLUDED_

#include "TD_PackPush.h"

#include "TvEntity.h"
#include "TvSelection.h"
#include "TvInterfaceWrappers.h"
#include "TvGeometryDataImpl.h"
#include "TvEntityIteratorImpl.h"
#include "TvUserDataImpl.h"
#include "TvGeometryTypifiedDataMiscImpl.h"
#include "TvExtentsSpaceTree.h"
#include "TvSelectionImpl.h"

#include "DbEntity.h"
#include "CmColor.h"

#define STL_USING_VECTOR
#define STL_USING_SET
#include "OdaSTL.h"
#include "OdList.h"
#include <map>

#include "Gi/GiShellToolkit.h"
#include "RcsFileServices/RxRcsFileServices.h"
class OdTvVisualStyleId;
typedef OdVector<OdTvDbObjectId, OdMemoryAllocator<OdTvDbObjectId> > OdTvIsolatedObjectsArray;
typedef std::set<OdTvDbObjectId> OdTvHidedObjectsSet;

/** \details
    This class is the base class for the OdTvBlockImpl and OdTvModelImpl
*/
class OdTvEntityImpl : public OdTvDbEntity, public OdTvXDataStorage
{
  friend class OdTvSubEntityDataImpl;
  friend class OdTvGeometryDataImpl;
protected:
  OdTvEntityImpl();
public:
  ODRX_DECLARE_MEMBERS(OdTvEntityImpl);

  virtual ~OdTvEntityImpl();

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Interface implementation 
//////////////////////////////////////////////////////////////////////////////////////////////////////
  /** \details
  Adds a simple line to the entity
  */
  OdTvGeometryDataId appendPolyline(const OdTvPoint& start, const OdTvPoint& end, OdTvResult* rc = NULL);

  /** \details
  Adds a polyline to the entity
  */
  OdTvGeometryDataId appendPolyline(const OdTvPointArray& points, OdTvResult* rc = NULL);

  /** \details
  Adds a polyline to the entity
  */
  OdTvGeometryDataId appendPolyline(OdInt32 nPoints, const OdTvPoint* points, OdTvResult* rc = NULL);

  /** \details
  Adds an unfilled circle to the entity 
  */
  OdTvGeometryDataId appendCircle(const OdTvPoint& firstPoint, const OdTvPoint& secondPoint, const OdTvPoint& thirdPoint, OdTvResult* rc = NULL);

  /** \details
  Adds an unfilled circle (via radius) to the entity
  */
  OdTvGeometryDataId appendCircle(const OdTvPoint& center, double radius, const OdTvVector& normal, OdTvResult* rc = NULL);

  /** \details
  Adds an unfilled circle arc to the entity
  */
  OdTvGeometryDataId appendCircleArc(const OdTvPoint& startPoint, const OdTvPoint& middlePoint, const OdTvPoint& endPoint, OdTvResult* rc = NULL);

  /** \details
  Adds an unfilled circle wedge to the entity
  */
  OdTvGeometryDataId appendCircleWedge(const OdTvPoint& startPoint, const OdTvPoint& middlePoint, const OdTvPoint& endPoint, OdTvResult* rc = NULL);

  /** \details
  Adds an unfilled ellipse to the entity
  */
  OdTvGeometryDataId appendEllipse(const OdTvPoint& centerPoint, const OdTvPoint& majorPoint, const OdTvPoint& minorPoint, OdTvResult* rc = NULL);

  /** \details
  Adds an unfilled elliptic arc to the entity
  */
  OdTvGeometryDataId appendEllipticArc(const OdTvPoint& centerPoint, const OdTvPoint& majorPoint, const OdTvPoint& minorPoint, const double startAng, const double endAng, OdTvResult* rc = NULL);

  /** \details
  Adds an unfilled polygon to the entity 
  */
  OdTvGeometryDataId appendPolygon(const OdTvPointArray& points, OdTvResult* rc = NULL);

  /** \details
  Adds a polyline to the entity
  */
  OdTvGeometryDataId appendPolygon(OdInt32 nPoints, const OdTvPoint* points, OdTvResult* rc = NULL);

  /** \details
  Adds a shell to the entity 
  */
  OdTvGeometryDataId appendShell(const OdTvPointArray& points, const OdInt32Array& faces, OdTvResult* rc = NULL);

  /** \details
  Adds a shell to the entity 
  */
  OdTvGeometryDataId appendShell(OdInt32 nPoints, const OdTvPoint* points, OdInt32 faceListSize, const OdInt32* faces, OdTvResult* rc = NULL);

  /** \details
  Adds a cylinder to the entity as shell
  */
  OdTvGeometryDataId appendShellFromCylinder(const OdTvPoint& point1, const OdTvPoint& point2, double radius, OdTvCylinderData::Capping caps = OdTvCylinderData::kBoth, int nDiv = 10, OdTvResult* rc = NULL);

  /** \details
  Adds a cylinder to the entity as shell
  */
  OdTvGeometryDataId appendShellFromCylinder(OdInt32 nPoints, const OdTvPoint* points, OdInt32 nRadii, const double* radii, const OdTvCylinderData::Capping& caps = OdTvCylinderData::kBoth, int nDiv = 10, OdTvResult* rc = NULL);

  /** \details
  Adds a sphere to the entity as shell
  */
  OdTvGeometryDataId appendShellFromSphere(const OdTvPoint& center, double radius, const OdTvVector& axis = OdTvVector(0., 1., 0.), const OdTvVector& primeMeridian = OdTvVector(1., 0., 0.), int nDiv = 10, OdTvResult* rc = NULL);

  /** \details
  Adds a box to the entity as shell
  */
  OdTvGeometryDataId appendShellFromBox(const OdTvPoint& centerPt, double dLength, double dWidth, double dHeight, const OdTvVector& baseNormal = OdTvVector::kZAxis, const OdTvVector& lengthDir = OdTvVector::kXAxis, OdTvResult* rc = NULL);

  /** \details
  Adds a mesh to the entity
  */
  OdTvGeometryDataId appendMesh(OdUInt32 nRows, OdUInt32 nColumns, const OdTvPointArray& verticesArray, OdTvResult* rc = NULL);

  /** \details
  Adds a mesh to the entity
  */
  OdTvGeometryDataId appendMesh(OdUInt32 nRows, OdUInt32 nColumns, OdUInt32 nVertices, const OdTvPoint* vertices, OdTvResult* rc = NULL);

  /** \details
  Adds a sphere to the entity
  */
  OdTvGeometryDataId appendSphere(const OdTvPoint& center, double radius, const OdTvVector& axis = OdTvVector(0., 1., 0.), const OdTvVector& primeMeridian = OdTvVector(1., 0., 0.), OdTvResult* rc = NULL);

  /** \details
  Adds a cylinder to the entity
  */
  OdTvGeometryDataId appendCylinder(const OdTvPoint& point1, const OdTvPoint& point2, double radius, OdTvCylinderData::Capping caps = OdTvCylinderData::kBoth, OdTvResult* rc = NULL);

  /** \details
  Adds a poly cylinder to the entity
  */
  OdTvGeometryDataId appendCylinder(const OdTvPointArray& points, const OdDoubleArray& radii, OdTvCylinderData::Capping caps = OdTvCylinderData::kBoth, OdTvResult* rc = NULL);

  /** \details
  Adds a poly cylinder to the entity
  */
  OdTvGeometryDataId appendCylinder(OdInt32 nPoints, const OdTvPoint* points, OdInt32 nRadii, const double* radii, const OdTvCylinderData::Capping& caps = OdTvCylinderData::kBoth, OdTvResult* rc = NULL);

  /** \details
  Adds a box to the entity
  */
  OdTvGeometryDataId appendBox(const OdTvPoint& centerPt, double dLength, double dWidth, double dHeight, const OdTvVector& baseNormal = OdTvVector::kZAxis, const OdTvVector& lengthDir = OdTvVector::kXAxis, OdTvResult* rc = NULL);

  /** \details
  Adds a brep to the entity.
  */
  OdTvGeometryDataId appendBrep(const OdBrBrep& brep, OdDbBaseDatabase *pDb, OdTvResult* rc = NULL);
  
  /** \details
  Adds a text to the entity 
  */
  OdTvGeometryDataId appendText(const OdTvPoint& ref_point, const OdString& msg, OdTvResult* rc = NULL);

  /** \details
  Adds a NURBS to the entity
  */
  OdTvGeometryDataId appendNurbs(unsigned int degree, const OdTvPointArray& controlPoints, const OdDoubleArray& weights, const OdDoubleArray& knots, double start = 0., double end = 1., OdTvResult* rc = NULL);

  /** \details
  Adds a NURBS to the entity
  */
  OdTvGeometryDataId appendNurbs(unsigned int degree, unsigned int nControlPoints, const OdTvPoint* controlPoints, const double* weights, unsigned int nKnots, const double* knots, double start = 0., double end = 1., OdTvResult* rc = NULL);
  
  /** \details
  Adds a infinite line to the entity
  */
  OdTvGeometryDataId appendInfiniteLine(const OdTvPoint& first, const OdTvPoint& second, OdTvInfiniteLineData::Type ilt, OdTvResult* rc = NULL);

  /** \details
  Adds an image to the entity
  */
  OdTvGeometryDataId appendRasterImage(OdTvRasterImageId imageId, const OdTvPoint& origin, const OdTvVector& u, const OdTvVector& v, OdTvResult* rc = NULL);

  /** \details
  Adds a point cloud to the entity
  */
  OdTvGeometryDataId appendPointCloud(const OdTvPointArray& points, OdTvResult* rc = NULL);

  /** \details
  Adds a point cloud to the entity
  */
  OdTvGeometryDataId appendPointCloud(OdInt32 nPoints, const OdTvPoint* points, OdTvResult* rc = NULL);

  /** \details
  Adds a point cloud to the entity
  */
  OdTvGeometryDataId appendPointCloud(OdPointCloudDataSourcePtr pDataSource, OdTvResult* rc = NULL);

  /** \details
  Adds an .rcs point cloud to the entity
  */
  OdTvGeometryDataId appendRcsPointCloud(OdPointCloudScanDatabasePtr pScanDb,
    OdPointCloudProjectDatabasePtr pProjDb = NULL, OdTvResult* rc = NULL);

  OdTvGeometryDataId appendRcsPointCloud(OdPointCloudDataSourcePtr pDataSource, const OdString& outputFilePath, OdTvResult* rc = NULL);

  /** \details
  Adds a grid to the entity
  */
  OdTvGeometryDataId appendGrid(const OdTvPoint& origin, const OdTvPoint& firstPoint = OdTvPoint(1., 0., 0.), const OdTvPoint& secondPoint = OdTvPoint(0., 10., 0.),
                                OdInt32 firstCount = 0, OdInt32 secondCount = 0, const OdTvGridData::Type type = OdTvGridData::kQuadratic, OdTvResult* rc = NULL);

  /** \details
  Adds a plane colored area to the entity
  */
  OdTvGeometryDataId appendColoredShape(const OdTvPointArray& points, const OdInt32Array& faces, OdTvResult* rc = NULL);

  /** \details
  Adds a plane colored area to the entity
  */
  OdTvGeometryDataId appendColoredShape(OdInt32 nPoints, const OdTvPoint* points, OdInt32 faceListSize, const OdInt32* faces, OdTvResult* rc = NULL);

  /** \details
  Ads a subentity object and returns the appropriate ID
  */
  OdTvGeometryDataId appendSubEntity(OdString name = OdString::kEmpty, OdTvResult* rc = NULL);

  /** \details
  Adds an insert object and returns the appropriate ID
  */
  OdTvGeometryDataId appendInsert(const OdTvBlockId& blockId, OdTvResult* rc = NULL);

  /** \details
  Adds a progressive mesh to the entity 
  */
  OdTvGeometryDataId appendProgressiveMesh(const OdTvPointArray& points, const OdInt32Array& faces, OdTvResult* rc = NULL);

  /** \details
  Adds a progressive mesh to the entity 
  */
  OdTvGeometryDataId appendProgressiveMesh(OdInt32 nPoints, const OdTvPoint* points, OdInt32 faceListSize, const OdInt32* faces, OdTvResult* rc = NULL);

  /** \details
  Remove geometry data by the appropriate ID
  */
  OdTvResult removeGeometryData(const OdTvGeometryDataId& geomId);

  /** \details
  Clear geometries data
  */
  OdTvResult clearGeometriesData();

  /** \details
  Returns the pointer to the geometry data iterator object
  */
  OdTvGeometryDataIteratorPtr getGeometryDataIterator(OdTvResult* rc = NULL);

  void collectUnloadedSubentities( OdVector< OdUInt64 >& handles );

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Group of the interface methods for setting the attributes
//////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
  Set the color of the entity or of the specified geometry type in the entity
  */
  OdTvResult setColor(const OdTvColorDef& color, OdUInt16 geomType = (OdUInt16)OdTvGeometryData::kAll, bool bFromParent = false);

  /** \details
  Get the color of the entity or of the specified geometry type in the entity as rgb, inherited or index
  */
  OdTvColorDef getColor(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll);

  /** \details
  Set the line weight of the entity or of the specified geometry type in the entity
  */
  OdTvResult setLineWeight(const OdTvLineWeightDef& lw, OdUInt16 geomType = (OdUInt16)OdTvGeometryData::kAll, bool bFromParent = false);

  /** \details
  Get the line weight of the entity or of the specified geometry type in the entity
  */
  OdTvLineWeightDef getLineWeight(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll);

  /** \details
  Set the linetype of the entity or of the specified geometry type in the entity
  */
  OdTvResult setLinetype(const OdTvLinetypeDef& lt, OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll, bool bFromParent = false);

  /** \details
  Get the linetype of the entity or of the specified geometry type in the entity
  */
  OdTvLinetypeDef getLinetype(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll) const;

  /** \details
  Set the linetype scale of the entity or of the specified geometry type in the entity
  */
  OdTvResult setLinetypeScale(double linetypeScale, OdUInt16 geomType = (OdUInt16)OdTvGeometryData::kAll, bool bFromParent = false);

  /** \details
  Get the linetype scale of the entity or of the specified geometry type in the entity
  */
  double getLinetypeScale(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll);

  /** \details
  Set the layer of the entity or of the specified geometry type in the entity
  */
  OdTvResult setLayer(const OdTvLayerDef& l, OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll, bool bFromParent = false);

  /** \details
  Get the layer of the entity or of the specified geometry type in the entity
  */
  OdTvLayerDef getLayer(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll, OdTvResult* rc = NULL);

  /** \details
  Set the visibility property of the entity or of the specified geometry type in the entity
  */
  OdTvResult setVisibility(const OdTvVisibilityDef& visible, OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll, bool bFromParent = false);

  /** \details
  Get the visibility property of the entity or of the specified geometry type in the entity
  */
  OdTvVisibilityDef getVisibility(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll, OdTvResult* rc = NULL) const;

  /** \details
  Set the text style for all text inside entity
  */
  OdTvResult setTextStyle(const OdTvTextStyleDef& textStyle, bool bFromParent = false);

  /** \details
  Returns the text style of all text inside entity
  */
  OdTvTextStyleDef getTextStyle(OdTvResult* rc = NULL) const;

  /** \details
  Set the transparency of the entity or of the specified geometry type in the entity
  */
  OdTvResult setTransparency(const OdTvTransparencyDef& transparency, OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll, bool bFromParent = false);

  /** \details
  Get the transparency of the entity or of the specified geometry type in the entity
  */
  OdTvTransparencyDef getTransparency(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll, OdTvResult* rc = NULL);

  /** \details
  Set the material of the entity
  */
  OdTvResult setMaterial(const OdTvMaterialDef& material, bool bFromParent = false);

  /** \details
  Get the material of the entity
  */
  OdTvMaterialDef getMaterial(OdTvResult* rc = NULL) const;

  /** \details
  Sets the mapper used to map a material to the entity.
  */
  OdTvResult setMaterialMapper(const OdTvMapperDef& mapper, bool bFromParent = false);

  /** \details
  Returns OdTvMapperDef used to map a material of the entity.
  */
  const OdTvMapperDef getMaterialMapper(OdTvResult* rc = NULL) const;

  /** \details
  Sets the visual style for the entity. The visual style should be compatible with the visual style assigned to the view.
  This functionality should be used very carefully. The typical case for it is the customization of the highlighting.
  */
  OdTvResult setVisualStyle(const OdTvVisualStyleId& vsId);

  /** \details
  Retrieves the current visual style applied to the entity.
  */
  OdTvVisualStyleId getVisualStyle(OdTvResult* rc = NULL) const;

  /** \details
  Sets the selectability to the entity.
  */
  OdTvResult setSelectability(const OdTvSelectabilityDef& selectability, bool bFromParent = false);

  /** \details
  Sets the sectionable flag to entity. This mean, that all geometry in this entity can be cut via cutting plane.
  */
  OdTvResult setSectionable(bool bVal, bool bFromParent = false);

  /** \details
  Check if entity is sectionable. This mean, that all geometry in this entity can be cut via cutting plane.
  */
  bool getSectionable() const;

  /** \details
  Returns OdTvSelectabilityDef of the entity
  */
  OdTvSelectabilityDef getSelectability(bool* bInherited = NULL, OdTvResult* rc = NULL) const;

  /** \details
  Check if entity can be selected
  */
  bool isSelectable(OdTvResult* rc = NULL) const;

  /** \details
  Get object by marker
  */
  OdTvGeometryDataImpl* getObjectByGsMarker(const OdGsMarker& marker, OdTv::SubGeometryType& type, OdInt64& subGeomId) const;

  /** \details
  Sets that it is need to show shell normals for all shell objects in this entity.
  */
  OdTvResult setShowShellNormals(bool bShow, double normalsLength = 0., const OdTvRGBColorDef& normalsColor = OdTvRGBColorDef());

  /** \details
  Returns true if shell normals are visible.
  */
  bool getShowShellNormals(OdTvResult* rc = NULL) const;

  /** \details
  Sets that it is need to show sharp edges for all shell objects.
  */
  OdTvResult setShowShellSharpEdges(bool bShow, OdUInt8 edgesWidth = 5, const OdTvRGBColorDef& edgesColor = OdTvRGBColorDef());

  /** \details
  Returns true if shell sharp edges are visible.
  */
  bool getShowShellSharpEdges(OdTvResult* rc = NULL) const;

  /** \details
  Find an sub entity by name
  */
  OdTvGeometryDataId findSubEntity(const OdUInt64 h, OdTvResult* rc = NULL);

  //**************************************************************************************
  // Group of the methods for the using transform matrix with this entity
  //**************************************************************************************

  /** \details
  Join rotation matrix to this matrix that rotates entity around the X, Y and Z axes.
  */
  OdTvResult rotate(double x, double y, double z);

  /** \details
  Join rotation matrix to this matrix with rotation around an arbitrary vector by number of degrees
  */
  OdTvResult rotateAxis(const OdTvVector& aVector, double ang, const OdTvPoint& center = OdTvPoint::kOrigin);

  /** \details
  Join translation matrix to this matrix that moves geometry along X, Y, Z axis
  */
  OdTvResult translate(double x, double y, double z);

  /** \details
  Join translation matrix to this matrix that moves geometry in vector distance
  */
  OdTvResult translate(const OdTvVector& aVector);

  /** \details
  Join scale matrix to this matrix that scales multiplier along X, Y, Z axis
  */
  OdTvResult scale(double x, double y, double z);

  /** \details
  Set the transform matrix which can rotate, transform and scale the entity
  */
  OdTvResult setModelingMatrix(const OdTvMatrix& matrix);

  /** \details
  Set the transform matrix which can rotate, transform and scale the entity
  */
  OdTvMatrix getModelingMatrix() const;

  /** \details
  Multiply existing transform matrix by new matrix
  */
  OdTvResult appendModelingMatrix(const OdTvMatrix& matrix);

  //**************************************************************************************
  // Misc methods
  //**************************************************************************************

  /** \details
  Marks that entity should be regenerated
  */
  OdTvResult regen();

  /** \details
  Marks that entity should be regenerated at each redraw
  */
  OdTvResult setAutoRegen(bool bOn);

  /** \details
  Returns the autoregenerated state of the entity
  */
  bool getAutoRegen() const;

  /** \details
  Set target display mode of the entity
  */
  OdTvResult setTargetDisplayMode(OdTvGeometryData::TargetDisplayMode targetMode);

  /** \details
  Gettarget display mode of the entity
  */
  OdTvGeometryData::TargetDisplayMode getTargetDisplayMode() const;

  /** \details
  Set extents to the entity
  */
  OdTvResult setExtents(const OdTvExtents3d& ext);

  /** \details
  Get extents from this entity.
  */
  OdTvResult getExtents(OdTvExtents3d& ext, OdTv::ExtentsType eType = OdTv::kPreferred) const;

  /** \details
  Add view in which entity will be drawn
  */
  OdTvResult addViewDependency(const OdTvGsViewId& viewId);

  /** \details
  Remove the view from the views in which the entity should be drawn
  */
  OdTvResult removeViewDependency(const OdTvGsViewId& viewId);

  /** \details
  Remove any view dependencies which means that the entity will be drawn in all views
  */
  OdTvResult removeViewDependencies();

  /** \details
  Checks that the entity is view dependent (means should be drawn in the specified views)
  */
  bool isViewDependent(OdTvResult* rc = NULL);

  /** \details
  Returns the views in which this entity should be drawn
  */
  OdTvGsViewIdsArray getViewDependencies(OdTvResult *rc = NULL);

  /** \details
  Copy all entity data to specified entity
  */
  OdTvResult copyTo(OdTvEntityId& targetEntityId, bool bFromInterface = true) const;

  OdTvResult copyTo(OdTvEntityId& targetEntityId, OdTvAttributeResolverPtr pResolver, bool bFromInterface = true ) const;

  /** \details
  Copy all entity's geometry to specified entity
  */
  OdTvResult copyGeometryTo(OdTvEntityId& targetEntityId) const;

  /** \details
  Make from all first level sub entities top level entities.
  */
  OdTvResult explodeSubEntities(OdTvEntityIdsArray* pNewEntities = NULL);

  /** \details
  Removes subentities replacing them by it's childs geometries
  */
  OdTvResult removeSubEntities(OdUInt8 removingFlags = OdTvEntity::kRemoveEmpty, bool bRecursive = false, bool bSilent = true);

  /** \details
  Returns true if the enity has no geometry
  */
  bool isEmpty() const;

  /** \details
  Returns the number of geometries in this entity
  */
  OdUInt32 getNumGeometries(bool bRecursive = false, bool bIgnoreSubentityItself = false) const;

  /** \details
  Remove geometry data by the pointer
  */
  OdTvResult removeGeometryDataInternal(OdTvGeometryDataImpl* pDataForDeleting);

  /** \details
  Add entity and sub entities to multimap.
  */
  void collectEntitiesForCDA(std::multimap<OdUInt64, OdTvEntityId>& entitiesMap, const OdTvRegAppId& appId);

//////////////////////////////////////////////////////////////////////////////////////////////////////
//OdTvEntityImpl own methods 
//////////////////////////////////////////////////////////////////////////////////////////////////////

  enum entChangedTypes
  {
    kColor = 1,
    kLinetype = 2,
    kLinetypeScale = 4,
    kLineweight = 8,
    kLayer = 16,
    kVisible = 32,
    kTransparency = 64,
    kMaterial = 128,
    kMapper = 256,
    kVisualStyle = 512,
    kShadows = 1024,
    kOther = 2048
  };

  //       1 bit. Target display (everywhere or not). 0 - everywhere.
  //       2 bit. Target display (wireframe or render) valid only if first bit is 1. 0 - wireframe
  //       3 bit. Means that for the entity the autoregenerated flag is set
  //       4 bit. Should be auto regenerated. Can be set only for the first-level entities (child of the model or block)
  //       5 bit. Has or not child's shells, meshes, spheres or cylinders which are not everywhere displayed. Can be set only for the first-level entities (child's of the model or block)
  //       6 bit. Means that the it is subentity and contains selectable childs.
  //       7 bit. Means that the entity has per session invisible geometry
  //       8 bit. Means that the entity has persistent invisible geometry
  enum entFlags
  {
    kDisplay = 1,
    kTargetDisplay = 2,
    kAutoRegenSet = 4,
    kAutoRegen = 8,
    kRenderModeDependent = 16,
    kSubEntityHasSelectableChilds = 32,
    kSectionable = 64,
    kHasInvisiblePersistentGeom = 128
  };

  enum entExFlags
  {
    kHasInvisiblePerSessionGeom = 1,    // not need anymore but we can't remove it since it is already present in old files
    kShowNormals = 2,
    kShowSharpEdges = 4,
    kShadowsNoCast = 8,
    kShadowNoReceive = 16,
    kNeedCheckShellsTopology = 32
  };

  //set name
  void setName(const OdString& name){m_name = name;}
  OdString getName() const {return m_name;}

  // set the bit value for the flag (also in the case of the false it will check that there is no more childs which need this flag)
  void setBitValue(entFlags bit, bool value);

  // transfer specific traits to the childs
  void setParentGeomSpecificTraits(OdTvGeomSpecificTraits* pParentTraits);

  // push down to the children all traits (after open the file)
  virtual void pushDownSpecificTraits();

  // push down to the child subentity all traits (after or during open the file)
  virtual void pushDownSpecificTraitsForSubEntity(OdTvEntityImpl* pSubent);

  // push down sub entity markers
  void pushDownSubEntityMark(bool isPartial = false);

  //  updates sub entity markers
  //  returns false if parent does not find this sub-entity in children list
  bool updateSubEntityMark( OdTvEntityImplPtr pParent, bool isPartial = false );

  //returns true if and only if this entity is a subentity
  bool getIsSubEntity() const {return m_pSubEntityGeometryData != NULL;}

  //returns true if and only if the selectability of this entity is compatible with the incoming seletion sevel
  bool getIsSelectionLevelCompatible(OdTvSelectionOptions::Level level);

  // methods for geom specific attributes
  bool                hasGeomSpecificColor(OdTvGeometryData::GeometryTypes geomType) const;
  OdTvCmEntityColor   getGeomSpecificColor(OdTvGeometryData::GeometryTypes geomType) const;

  bool                hasGeomSpecificLineWeight(OdTvGeometryData::GeometryTypes geomType) const;
  OdDb::LineWeight    getGeomSpecificLineWeight(OdTvGeometryData::GeometryTypes geomType) const;

  bool                hasGeomSpecificLinetype(OdTvGeometryData::GeometryTypes geomType) const;
  OdTvDbObjectId        getGeomSpecificLinetype(OdTvGeometryData::GeometryTypes geomType) const;

  bool                hasGeomSpecificLinetypeScale(OdTvGeometryData::GeometryTypes geomType) const;
  double              getGeomSpecificLinetypeScale(OdTvGeometryData::GeometryTypes geomType) const;

  bool                hasGeomSpecificLayer(OdTvGeometryData::GeometryTypes geomType) const;
  OdTvDbObjectId        getGeomSpecificLayer(OdTvGeometryData::GeometryTypes geomType) const;

  bool                hasGeomSpecificVisibility(OdTvGeometryData::GeometryTypes geomType) const;
  bool                getGeomSpecificVisibility(OdTvGeometryData::GeometryTypes geomType) const;

  bool                hasGeomSpecificTransparency(OdTvGeometryData::GeometryTypes geomType) const;
  OdCmTransparency    getGeomSpecificTransparency(OdTvGeometryData::GeometryTypes geomType) const;

  // re-implemented subWorldDraw
  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const;

  // re-implemented subViewportDraw
  virtual void subViewportDraw(OdGiViewportDraw* pVd) const;

  // re-implemented subSetAttributes
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;

  // re-implemented subSetAttributes
  virtual OdResult subTransformBy(const OdGeMatrix3d& mx);

  // re-implemented subGetGeomExtents
  virtual OdResult subGetGeomExtents(OdGeExtents3d& extents) const;

  // for loading from VSF file
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  // for saving in VSF file
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
  Set the real time visibility property of the entity

  \param visible [in]  if false, make entity invisible
  */
  OdTvResult setTempVisibility(const OdTvVisibilityDef& visible);

  /** \details
  Isolate geometries from this entity (persistent) which are present in array of subItem pathes (returns 'true' if it is need to update entity)
  */
  bool isolatePathes(OdUInt32 iLevel, const OdTvSubItemPathArray& pathes);

  /** \details
  Hide geometry from this entity (persistent)
  */
  OdTvResult hideGeometryData(const OdTvGeometryDataId& geometryId);

  /** \details
  Unisolate geometries in this entity
  */
  OdTvResult unIsolate();

  /** \details
  Check that the entity has persistent invisible geom
  */
  bool hasPersistenInvisibleGeom() { return GETBIT(m_flags, kHasInvisiblePersistentGeom); }

  /** \details
  Mark entity that it has persistent invisible geometry
  */
  void setHasPersistenInvisibleGeom() { SETBIT(m_flags, kHasInvisiblePersistentGeom, true); }

  /** \details
  Update flag for the entity
  */
  bool updateHasPersistenInvisibleGeom(OdUInt32 checkDepth);

  /** \details
  Return the OdTvGeometryDataId of this entity if this is sub entity
  */
  OdTvGeometryDataId getParentGeometryId() const;

  /** \details
  Return the OdTvGeometryDataImpl of this entity if this is sub entity
  */
  OdTvGeometryDataImpl* getParentGeometryData() const { return m_pSubEntityGeometryData; }

  /** \details
  Return the value of memory, which this object takes up.
  */
  OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

  /** \details
  Calculate number of geometries and markered geometries (used in selection procedure)
  */
  void getGeometriesNumber(OdUInt64& nGeometries, OdUInt64& nMaxMarker) const;

  /** \details
  Get vector of markered geometries. Every markered geometry will be on [marker] position in vector (used in selection procedure)
  This vector should be already resized to valid number
  */
  void getMarkeredGeometries(std::vector<OdTvGeometryDataImpl*>* pMarkeredGeometries) const;

  /** \details
  Recursive travel in object tree.
  */
  void writeSubEntitityObjectPartial(OdList<OdDbStub*>* pSubEntitiesStubsl);

  /** \details
  Clear vertices spatial tree in all entities in block of this  insert
  */
  void clearSpatialTreeCacheInEntities();

  //////////////////////////////////////////////////////////////////////////////////////////////////////
  //OdTvEntityImpl methods which is need for OdTvGeometryDataImpl
  //////////////////////////////////////////////////////////////////////////////////////////////////////

  // append geometry to the list
  void appendGeometry(OdTvGeometryDataImpl* pData, bool bSilent = false);

  // create geometry data on the base of it's type
  OdTvGeometryDataImpl* createGeometryDataViaType(OdInt8 iDataType);

  /** \details
  Check if entity (and sub entities inside) has geometry.
  */
  bool hasGeometry() const;

  OdTvResult setShadowParameters( bool bCastShadows, bool bReceiveShadow );

  OdTvResult getShadowParameters( bool& bCastShadows, bool& bReceiveShadow );

  bool checkForSectionFilling( OdTvResult* rc = NULL ) const;
  virtual OdTvResult fixForSectionFilling( bool bNotify = true );
  OdTvResult setNeedCheckShellsTopology( bool bCheck );
  bool getNeedCheckShellsTopology( OdTvResult* rc = NULL ) const;

  void putDataInToolkit( OdGiShellToolkitPtr pShellToolkit ) const;

  /** \details
  Get extents space tree by marker. If there is no tree in this marker, NULL will be returned.
  */
  OdTvExtentsSpaceTreeBase* getExtentsSpaceTree(OdGsMarker gsMarker) const;

  /** \details
  Add tree to extents space tree map. If map already has marker, update tree.
  */
  void addTreeToExtentsSpaceTreeMap(OdGsMarker gsMarker, OdTvExtentsSpaceTreeBase* pTree);

  /** \details
  Remove tree from extents space tree map.
  */
  void removeTreeFromExtentsSpaceTreeMap(OdGsMarker gsMarker);

  /** \details
  Draw subentity for markers
  */
  void drawForMarkers();

  /** \details
  Returns first geometry data
  */
  OdTvGeometryDataImpl* getFirstGeometryData() const { return m_pFirstData;  }

  /** \details
  Returns the maximal marker for the entity contents
  */
  OdGsMarker getMaximalMarker() const;

protected:

  // create local geometry specific traits
  void createGeomSpecificTraits(bool bFromParent);
 
  // clear local geometry specific traits if it is empty
  void clearGeomSpecificTraits();

  // methods for geometry specific traits
  void setGeomSpecificColor(const OdTvCmEntityColor& color, OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);
  void setGeomSpecificColors(OdTvCmEntityColor& color, OdUInt16 geomTypes, bool bFromParent = true);
  void setGeomSpecificLineWeight(OdDb::LineWeight lw, OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);
  void setGeomSpecificLinetype(OdTvDbObjectId lt, OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);
  void setGeomSpecificLinetypeScale(double ltScale, OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);
  void setGeomSpecificLayer(OdTvDbObjectId l, OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);
  void setGeomSpecificVisibility(bool bVisible, OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);
  void setGeomSpecificTransparency(OdCmTransparency& transparency, OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);

  void resetGeomSpecificColor(OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);
  void clearGeomSpecificColors(OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);

  void resetGeomSpecificLineWeight(OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);
  void clearGeomSpecificLineWeight(OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);

  void resetGeomSpecificLinetype(OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);
  void clearGeomSpecificLinetype(OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);

  void resetGeomSpecificLinetypeScale(OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);
  void clearGeomSpecificLinetypeScale(OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);

  void resetGeomSpecificLayer(OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);
  void clearGeomSpecificLayer(OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);

  void resetGeomSpecificVisibility(OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);
  void clearGeomSpecificVisibility(OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);

  void resetGeomSpecificTransparency(OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);
  void clearGeomSpecificTransparency(OdTvGeometryData::GeometryTypes geomType, bool bFromParent = true);

  // update flag for the common traits
  void updateChangedFlags(entChangedTypes type);

  // reset flag for the common traits
  void resetChangedFlags(entChangedTypes type);

  // push down geometry specific color
  void pushDownGeomSpecificColor(OdTvEntityImpl* pSubent, OdTvGeometryData::GeometryTypes types);

  // push down geometry specific lineweight
  void pushDownGeomSpecificLineWeight(OdTvEntityImpl* pSubent, OdTvGeometryData::GeometryTypes types);

  // push down geometry specific linetype
  void pushDownGeomSpecificLinetype(OdTvEntityImpl* pSubent, OdTvGeometryData::GeometryTypes types);

  // push down geometry specific linetypescale
  void pushDownGeomSpecificLinetypeScale(OdTvEntityImpl* pSubent, OdTvGeometryData::GeometryTypes types);

  // push down geometry specific layer
  void pushDownGeomSpecificLayer(OdTvEntityImpl* pSubent, OdTvGeometryData::GeometryTypes types);

  // push down geometry specific visibility
  void pushDownGeomSpecificVisibility(OdTvEntityImpl* pSubent, OdTvGeometryData::GeometryTypes types);

  // push down geometry specific transparency
  void pushDownGeomSpecificTransparency(OdTvEntityImpl* pSubent, OdTvGeometryData::GeometryTypes types);

  // check the possibility of the reset the bit
  bool checkNecessityOfBit(entFlags bit);

  // match the target display mode
  static bool matchTargetDisplayMode(OdTvGeometryData::TargetDisplayMode targetDisplayMode, OdGiWorldDraw* pWd);
  static bool matchTargetDisplayMode(OdTvGeometryData::TargetDisplayMode targetDisplayMode, OdGiViewportDraw* pVd);

  virtual OdResult explodeGeometry(OdRxObjectPtrArray& entitySet) const;

  // apply properties from this entity to exploded sub entity
  void copyExplodedSubEntityParameters(OdTvSubEntityDataImpl* pSubEntityDataImpl);
  
  // copy traits from incoming entity
  void copyTraits(OdTvEntityImpl* pEntityImpl, bool bAllowSubstituteTransform);

  // set geometry in sub geometry markers position
  void setGeomToSubGeomMarkers(OdTvGeometryDataImpl* pGeometryDataImpl, const OdTv::SubGeometryType& type, std::vector<OdTvGeometryDataImpl*>* pMarkeredGeometries) const;

  // Check if visual style is default
  bool isVisualStyleDefault(const OdString& sVisualStyleName) const;

  // Go thought child geometry and update transform matrices in spatial trees
  void updateChildrensTransformInSpatialTree() const;
protected:
  // name of the entity
  OdString m_name;

  // pointer to the first data in the Doubly linked list of the data stored in the entity
  OdTvGeometryDataImpl*  m_pFirstData;

  // pointer to the first data in the Doubly linked list of the data stored in the entity
  OdTvGeometryDataImpl*  m_pLastData;

  // specific attributes
  OdTvGeomSpecificTraitsPtr    m_pGeomTypeTraits;    // pointer to the geom type specific attributes

  // default text style (used for creation the text)
  OdTvDbSoftPointerId             m_defTextStyleId;      // default text style

  // color for the geometry type OdTvGeometryData::kAll (where index 0 means NOT byBlock)
  OdTvCmEntityColor  m_color;

  // line for the geometry type OdTvGeometryData::kAll (not as index - simply as int)
  OdDb::LineWeight    m_lineWeight;

  // marks changed attributes
  OdUInt16           m_entChangedFlags;

  // transform matrix (NULL by default)
  OdTvMatrix*       m_pTransform;

  // entity flag according to the entFlags enum
  OdUInt8          m_flags;

  // entity ex flag according to the entExFlags enum
  OdUInt8          m_exFlags;

  // selectability flags
  OdUInt8          m_selectability;

  // pointer to sub entity, NULL if this entity is top entity level or child of the insert
  OdTvGeometryDataImpl*     m_pSubEntityGeometryData;

  // extents of the entity in the OCS (object (entity coordinate system) with taking into account local transform
  // (NULL by default)
  OdTvExtents3d*            m_pExtents;

  // current marker (real time field not for saving in file)
  OdGsMarker m_marker;

  // List of views where this entity should be drawn
  OdHardPtrIdArray    m_views;

  // True if list of view is not empty, even if view was deleted from database
  bool              m_bIsViewDependent;

  // indicate whether the traits are local of reference to parent
  bool m_bTraitsLocal;

  // Map with extents space trees
  std::map<OdGsMarker, OdTvExtentsSpaceTreeBase*> m_extentsSpaceTreeMap;
};

typedef OdSmartPtr<OdTvEntityImpl> OdTvEntityImplPtr;



/** \details
    This is an wrapper of the interface class for OdTvEntity object.

    \remarks
    The purpose of this class is to connect the internal entity object with an interface object
*/
  
class OdTvEntityWrapper : public OdTvEntity
{
  ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL(OdTvEntity, OdTvEntityImpl)   

  friend class OdTvModelRootEntityImpl;
  friend class OdTvBlockWrapper;

protected:
  ODRX_HEAP_OPERATORS();

public:

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface implementation
//////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
  Adds a simple line to the entity
  */
  virtual OdTvGeometryDataId appendPolyline(const OdTvPoint& start, const OdTvPoint& end, OdTvResult* rc = NULL);

  /** \details
  Adds a polyline to the entity
  */
  virtual OdTvGeometryDataId appendPolyline(const OdTvPointArray& points, OdTvResult* rc = NULL);

  /** \details
  Adds a polyline to the entity
  */
  virtual OdTvGeometryDataId appendPolyline(OdInt32 nPoints, const OdTvPoint* points, OdTvResult* rc = NULL);

  /** \details
  Adds an unfilled circle to the entity 
  */
  virtual OdTvGeometryDataId appendCircle(const OdTvPoint& firstPoint, const OdTvPoint& secondPoint, const OdTvPoint& thirdPoint, OdTvResult* rc = NULL);

  /** \details
  Adds an unfilled circle (via radius) to the entity
  */
  virtual OdTvGeometryDataId appendCircle(const OdTvPoint& center, double radius, const OdTvVector& normal, OdTvResult* rc = NULL);
  
  /** \details
  Adds an unfilled circle arc to the entity
  */
  virtual OdTvGeometryDataId appendCircleArc(const OdTvPoint& startPoint, const OdTvPoint& middlePoint, const OdTvPoint& endPoint, OdTvResult* rc = NULL);

  /** \details
  Adds an unfilled circle wedge to the entity
  */
  virtual OdTvGeometryDataId appendCircleWedge(const OdTvPoint& startPoint, const OdTvPoint& middlePoint, const OdTvPoint& endPoint, OdTvResult* rc = NULL);

  /** \details
  Adds an unfilled ellipse to the entity
  */
  virtual OdTvGeometryDataId appendEllipse(const OdTvPoint& centerPoint, const OdTvPoint& majorPoint, const OdTvPoint& minorPoint, OdTvResult* rc = NULL);
  
  /** \details
  Adds an unfilled elliptic arc to the entity
  */
  virtual OdTvGeometryDataId appendEllipticArc(const OdTvPoint& centerPoint, const OdTvPoint& majorPoint, const OdTvPoint& minorPoint, double startAng, double endAng, OdTvResult* rc = NULL);

  /** \details
  Adds an unfilled polygon to the entity 
  */
  virtual OdTvGeometryDataId appendPolygon(const OdTvPointArray& points, OdTvResult* rc = NULL);

  /** \details
  Adds a polyline to the entity
  */
  virtual OdTvGeometryDataId appendPolygon(OdInt32 nPoints, const OdTvPoint* points, OdTvResult* rc = NULL);

  /** \details
  Adds a shell to the entity 
  */
  virtual OdTvGeometryDataId appendShell(const OdTvPointArray& points, const OdInt32Array& faces, OdTvResult* rc = NULL);

  /** \details
  Adds a shell to the entity 
  */
  virtual OdTvGeometryDataId appendShell(OdInt32 nPoints, const OdTvPoint* points, OdInt32 faceListSize, const OdInt32* faces, OdTvResult* rc = NULL);

  /** \details
  Adds a cylinder to the entity as shell
  */
  virtual OdTvGeometryDataId appendShellFromCylinder(const OdTvPoint& point1, const OdTvPoint& point2, double radius, OdTvCylinderData::Capping caps = OdTvCylinderData::kBoth, int nDiv = 10, OdTvResult* rc = NULL);

  /** \details
  Adds a cylinder to the entity as shell
  */
  virtual OdTvGeometryDataId appendShellFromCylinder(OdInt32 nPoints, const OdTvPoint* points, OdInt32 nRadii, const double* radii, const OdTvCylinderData::Capping& caps = OdTvCylinderData::kBoth, int nDiv = 10, OdTvResult* rc = NULL);

  /** \details
  Adds a sphere to the entity as shell
  */
  virtual OdTvGeometryDataId appendShellFromSphere(const OdTvPoint& center, double radius, const OdTvVector& axis = OdTvVector(0., 1., 0.), const OdTvVector& primeMeridian = OdTvVector(1., 0., 0.), int nDiv = 10, OdTvResult* rc = NULL);

  /** \details
  Adds a box to the entity  as shell
  */
  virtual OdTvGeometryDataId appendShellFromBox(const OdTvPoint& centerPt, double dLength, double dWidth, double dHeight, const OdTvVector& baseNormal = OdTvVector::kZAxis, const OdTvVector& lengthDir = OdTvVector::kXAxis, OdTvResult* rc = NULL);

  /** \details
  Adds a mesh to the entity
  */
  virtual OdTvGeometryDataId appendMesh(OdUInt32 nRows, OdUInt32 nColumns, const OdTvPointArray& verticesArray, OdTvResult* rc = NULL);

  /** \details
  Adds a mesh to the entity
  */
  virtual OdTvGeometryDataId appendMesh(OdUInt32 nRows, OdUInt32 nColumns, OdUInt32 nVertices, const OdTvPoint* vertices, OdTvResult* rc = NULL);

  /** \details
  Adds a sphere to the entity
  */
  virtual OdTvGeometryDataId appendSphere(const OdTvPoint& center, double radius, const OdTvVector& axis = OdTvVector(0., 1., 0.), const OdTvVector& primeMeridian = OdTvVector(1., 0., 0.), OdTvResult* rc = NULL);

  /** \details
  Adds a cylinder to the entity
  */
  virtual OdTvGeometryDataId appendCylinder(const OdTvPoint& point1, const OdTvPoint& point2, double radius, OdTvCylinderData::Capping caps = OdTvCylinderData::kBoth, OdTvResult* rc = NULL);

  /** \details
  Adds a poly cylinder to the entity
  */
  virtual OdTvGeometryDataId appendCylinder(const OdTvPointArray& points, const OdDoubleArray& radii, OdTvCylinderData::Capping caps = OdTvCylinderData::kBoth, OdTvResult* rc = NULL);

  /** \details
  Adds a poly cylinder to the entity
  */
  virtual OdTvGeometryDataId appendCylinder(OdInt32 nPoints, const OdTvPoint* points, OdInt32 nRadii, const double* radii, const OdTvCylinderData::Capping& caps = OdTvCylinderData::kBoth, OdTvResult* rc = NULL);

  /** \details
  Adds a box to the entity
  */
  virtual OdTvGeometryDataId appendBox(const OdTvPoint& centerPt, double dLength, double dWidth, double dHeight, const OdTvVector& baseNormal = OdTvVector::kZAxis, const OdTvVector& lengthDir = OdTvVector::kXAxis, OdTvResult* rc = NULL);

  /** \details
  Adds a brep to the entity.
  */
  virtual OdTvGeometryDataId appendBrep(const OdBrBrep& brep, OdDbBaseDatabase *pDb, OdTvResult* rc = NULL);
  
  /** \details
  Adds a text to the entity 
  */
  virtual OdTvGeometryDataId appendText(const OdTvPoint& ref_point, const OdString& msg, OdTvResult* rc = NULL);

  /** \details
  Adds a NURBS to the entity
  */
  virtual OdTvGeometryDataId appendNurbs(unsigned int degree, const OdTvPointArray& controlPoints, const OdDoubleArray& weights, const OdDoubleArray& knots, double start = 0., double end = 1., OdTvResult* rc = NULL);

    /** \details
  Adds a NURBS to the entity
  */
  virtual OdTvGeometryDataId appendNurbs(unsigned int degree, unsigned int nControlPoints, const OdTvPoint* controlPoints, const double* weights, unsigned int nKnots, const double* knots, double start = 0., double end = 1., OdTvResult* rc = NULL);

  /** \details
  Adds a infinite line to the entity
  */
  virtual OdTvGeometryDataId appendInfiniteLine(const OdTvPoint& first, const OdTvPoint& second, OdTvInfiniteLineData::Type ilt, OdTvResult* rc = NULL);

  /** \details
  Adds an image to the entity
  */
  virtual OdTvGeometryDataId appendRasterImage(OdTvRasterImageId imageId, const OdTvPoint& origin, const OdTvVector& u, const OdTvVector& v, OdTvResult* rc = NULL);

  /** \details
  Adds a point cloud to the entity
  */
  virtual OdTvGeometryDataId appendPointCloud(const OdTvPointArray& points, OdTvResult* rc = NULL);

  /** \details
  Adds a point cloud to the entity
  */
  virtual OdTvGeometryDataId appendPointCloud(OdInt32 nPoints, const OdTvPoint* points, OdTvResult* rc = NULL);

  /** \details
  Adds a point cloud to the entity
  */
  virtual OdTvGeometryDataId appendPointCloud(OdPointCloudDataSourcePtr pDataSource, OdTvResult* rc = NULL);

  /** \details
  Adds an .rcs point cloud to the entity
  */
  virtual OdTvGeometryDataId appendRcsPointCloud(OdPointCloudScanDatabasePtr pScanDb, 
    OdPointCloudProjectDatabasePtr pProjDb = NULL, OdTvResult* rc = NULL);

  virtual OdTvGeometryDataId appendRcsPointCloud(OdPointCloudDataSourcePtr pDataSource, const OdString& outputFilePath, OdTvResult* rc = NULL);

  /** \details
  Adds a grid to the entity
  */
  virtual OdTvGeometryDataId appendGrid(const OdTvPoint& origin, const OdTvPoint& firstPoint = OdTvPoint(1., 0., 0.), const OdTvPoint& secondPoint = OdTvPoint(0., 1., 0.),
                                        OdInt32 firstCount = 0, OdInt32 secondCount = 0, const OdTvGridData::Type type = OdTvGridData::kQuadratic, OdTvResult* rc = NULL);

  /** \details
  Adds a plane colored area to the entity
  */
  virtual OdTvGeometryDataId appendColoredShape(const OdTvPointArray& points, const OdInt32Array& faces, OdTvResult* rc = NULL);

  /** \details
  Adds a plane colored area to the entity
  */
  virtual OdTvGeometryDataId appendColoredShape(OdInt32 nPoints, const OdTvPoint* points, OdInt32 faceListSize, const OdInt32* faces, OdTvResult* rc = NULL);

  /** \details
  Adds a subentity object and returns the appropriate ID
  */
  virtual OdTvGeometryDataId appendSubEntity(OdString name = OdString::kEmpty, OdTvResult* rc = NULL);

  /** \details
  Adds an insert object and returns the appropriate ID
  */
  virtual OdTvGeometryDataId appendInsert(const OdTvBlockId& blockId, OdTvResult* rc = NULL);

  /** \details
  Adds a progressive mesh to the entity 
  */
  virtual OdTvGeometryDataId appendProgressiveMesh(const OdTvPointArray& points, const OdInt32Array& faces, OdTvResult* rc = NULL);

  /** \details
  Adds a progressive mesh to the entity 
  */
  virtual OdTvGeometryDataId appendProgressiveMesh(OdInt32 nPoints, const OdTvPoint* points, OdInt32 faceListSize, const OdInt32* faces, OdTvResult* rc = NULL);

  /** \details
  Remove geometry data by the appropriate ID
  */
  virtual OdTvResult removeGeometryData(const OdTvGeometryDataId& geomId);

  /** \details
  Clear geometries data
  */
  virtual OdTvResult clearGeometriesData();

  /** \details
  Returns the pointer to the geometry data iterator object
  */
  virtual OdTvGeometryDataIteratorPtr getGeometryDataIterator(OdTvResult* rc = NULL);

  //**************************************************************************************
  // Group of the methods for the using transform matrix with this entity
  //**************************************************************************************

  /** \details
  Join rotation matrix to this matrix that rotates entity around the X, Y and Z axes.
  */
  virtual OdTvResult rotate(double x, double y, double z);

  /** \details
  Join rotation matrix to this matrix with rotation around an arbitrary vector by number of degrees
  */
  virtual OdTvResult rotateAxis(const OdTvVector& aVector, double ang, const OdTvPoint& center = OdTvPoint::kOrigin);

  /** \details
  Join translation matrix to this matrix that moves geometry along X, Y, Z axis
  */
  virtual OdTvResult translate(double x, double y, double z);

  /** \details
  Join translation matrix to this matrix that moves geometry in vector distance
  */
  virtual OdTvResult translate(const OdTvVector& aVector);

  /** \details
  Join scale matrix to this matrix that scales multiplier along X, Y, Z axis
  */
  virtual OdTvResult scale(double x, double y, double z);

  /** \details
  Set the transform matrix which can rotate, transform and scale the entity
  */
  virtual OdTvResult setModelingMatrix(const OdTvMatrix& matrix);;

  /** \details
  Set the transform matrix which can rotate, transform and scale the entity
  */
  virtual OdTvMatrix getModelingMatrix(OdTvResult* rc = NULL) const;

  /** \details
  Multiply existing transform matrix by new matrix
  */
  virtual OdTvResult appendModelingMatrix(const OdTvMatrix& matrix);

  //**************************************************************************************
  // Misc methods
  //**************************************************************************************

  /** \details
  Sets the name for the entity

  \param sName [in]  Entity name
  */
  virtual OdTvResult setName(const OdString& sName);

  /** \details
  Returns the name of the entity
  */
  virtual OdString getName(OdTvResult* rc = NULL) const;

  /** \details
  Marks that entity should be regenerated
  */
  virtual OdTvResult regen();

  /** \details
  Marks that entity should be regenerated at each redraw
  */
  virtual OdTvResult setAutoRegen(bool bOn);

  /** \details
  Returns the autoregenerated state of the entity
  */
  virtual bool getAutoRegen(OdTvResult*rc = NULL) const;

  /** \details
  Set target display mode of the entity
  */
  virtual OdTvResult setTargetDisplayMode(OdTvGeometryData::TargetDisplayMode targetMode);

  /** \details
  Gettarget display mode of the entity
  */
  virtual OdTvGeometryData::TargetDisplayMode getTargetDisplayMode(OdTvResult*rc = NULL) const;

  /** \details
  Set extents to the entity
  */
  virtual OdTvResult setExtents(const OdTvExtents3d& ext);

  /** \details
  Get extents from this entity.
  */
  virtual OdTvResult getExtents(OdTvExtents3d& ext, OdTv::ExtentsType eType = OdTv::kPreferred) const;

  /** \details
  Add view in which entity will be drawn
  */
  virtual OdTvResult addViewDependency(const OdTvGsViewId& viewId);

  /** \details
  Remove the view from the views in which the entity should be drawn
  */
  virtual OdTvResult removeViewDependency(const OdTvGsViewId& viewId);

  /** \details
  Remove any view dependencies which means that the entity will be drawn in all views
  */
  virtual OdTvResult removeViewDependencies();

  /** \details
  Checks that the entity is view dependent (means should be drawn in the specified views)
  */
  virtual bool isViewDependent(OdTvResult* rc = NULL);

  /** \details
  Returns the views in which this entity should be drawn
  */
  virtual OdTvGsViewIdsArray getViewDependencies(OdTvResult *rc = NULL);

  /** \details
  Copy all entity's data to the specified entity (attributes, geometries etc)
  */
  virtual OdTvResult copyTo(OdTvEntityId& targetEntityId) const;
  virtual OdTvResult copyTo(OdTvEntityId& targetEntityId, OdTvAttributeResolverPtr pResolver) const;

  /** \details
  Copy all entity's geometry to specified entity
  */
  virtual OdTvResult copyGeometryTo(OdTvEntityId& targetEntityId) const;

  /** \details
  Make from all first level sub entities top level entities.
  */
  virtual OdTvResult explodeSubEntities(OdTvEntityIdsArray* pNewEntities = NULL);

  /** \details
  Removes subentities replacing them by it's childs geometries
  */
  virtual OdTvResult removeSubEntities(OdUInt8 removingFlags = kRemoveEmpty, bool bRecursive = false);

  /** \details
  Returns true if the enity has no geometry
  */
  virtual bool isEmpty(OdTvResult *rc = NULL) const;

  /** \details
  Returns the number of geometries in this entity
  */
  virtual OdUInt32 getNumGeometries(bool bRecursive = false, bool bIgnoreSubentityItself = false, OdTvResult *rc = NULL) const;

  //**************************************************************************************
  // Group of the methods for setting the attributes
  //**************************************************************************************

  /** \details
  Set the color of the entity or of the specified geometry type in the entity
  */
  virtual OdTvResult setColor(const OdTvColorDef& color, OdUInt16 geomType = (OdUInt16)OdTvGeometryData::kAll);

  /** \details
  Get the color of the entity or of the specified geometry type in the entity as rgb, inherited or index
  */
  virtual OdTvColorDef getColor(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll, OdTvResult* rc = NULL);

  /** \details
  Set the line weight of the entity or of the specified geometry type in the entity
  */
  virtual OdTvResult setLineWeight(const OdTvLineWeightDef& lw, OdUInt16 geomType = OdTvGeometryData::kAll);

  /** \details
  Get the line weight of the entity or of the specified geometry type in the entity
  */
  virtual OdTvLineWeightDef getLineWeight(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll, OdTvResult* rc = NULL);

  /** \details
  Set the linetype of the entity or of the specified geometry type in the entity
  */
  virtual OdTvResult setLinetype(const OdTvLinetypeDef& lt, OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll);

  /** \details
  Get the linetype of the entity or of the specified geometry type in the entity
  */
  virtual OdTvLinetypeDef getLinetype(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll, OdTvResult* rc = NULL);

  /** \details
  Set the linetype scale of the entity or of the specified geometry type in the entity
  */
  virtual OdTvResult setLinetypeScale(double linetypeScale, OdUInt16 geomType = (OdUInt16)OdTvGeometryData::kAll);

  /** \details
  Get the linetype scale of the entity or of the specified geometry type in the entity
  */
  virtual double getLinetypeScale(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll, OdTvResult* rc = NULL);
  /** \details
  Set the layer of the entity or of the specified geometry type in the entity
  */
  virtual OdTvResult setLayer(const OdTvLayerDef& l, OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll);

  /** \details
  Get the layer of the entity or of the specified geometry type in the entity
  */
  virtual OdTvLayerDef getLayer(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll, OdTvResult* rc = NULL);

  /** \details
  Set the visibility property of the entity or of the specified geometry type in the entity
  */
  virtual OdTvResult setVisibility(const OdTvVisibilityDef& visible, OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll);

  /** \details
  Get the visibility property of the entity or of the specified geometry type in the entity
  */
  virtual OdTvVisibilityDef getVisibility(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll, OdTvResult* rc = NULL) const;

  /** \details
  Set the text style for all text inside entity
  */
  virtual OdTvResult setTextStyle(const OdTvTextStyleDef& textStyle);

  /** \details
  Returns the text style of all text inside entity
  */
  virtual OdTvTextStyleDef getTextStyle(OdTvResult* rc = NULL) const;

  /** \details
  Set the transparency of the entity or of the specified geometry type in the entity
  */
  virtual OdTvResult setTransparency(const OdTvTransparencyDef& transparency, OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll);

  /** \details
  Get the transparency of the entity or of the specified geometry type in the entity
  */
  virtual OdTvTransparencyDef getTransparency(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll, OdTvResult* rc = NULL);

  /** \details
  Set the material of the entity
  */
  virtual OdTvResult setMaterial(const OdTvMaterialDef& material);

  /** \details
  Get the material of the entity
  */
  virtual OdTvMaterialDef getMaterial(OdTvResult* rc = NULL) const;

  /** \details
  Sets the mapper used to map a material to the entity.
  */
  virtual OdTvResult setMaterialMapper(const OdTvMapperDef& mapper);

  /** \details
  Returns OdTvMapperDef used to map a material to the entity.
  */
  virtual const OdTvMapperDef getMaterialMapper(OdTvResult* rc = NULL) const;

  /** \details
  Sets the visual style for the entity. The visual style should be compatible with the visual style assigned to the view.
  This functionality should be used very carefully. The typical case for it is the customization of the highlighting.
  */
  virtual OdTvResult setVisualStyle(const OdTvVisualStyleId& vsId);

  /** \details
  Retrieves the current visual style applied to the entity.
  */
  virtual OdTvVisualStyleId getVisualStyle(OdTvResult* rc = NULL) const;

  /** \details
  Sets the selectability to the entity.
  */
  virtual OdTvResult setSelectability(const OdTvSelectabilityDef& selectability);

  /** \details
  Returns OdTvSelectabilityDef of the entity
  */
  virtual OdTvSelectabilityDef getSelectability(bool* bInherited = NULL, OdTvResult* rc = NULL) const;

  /** \details
  Sets the sectionable flag to entity. This mean, that all geometry in this entity can be cut via cutting plane.
  */
  virtual OdTvResult setSectionable(bool bVal);

  /** \details
  Check if entity is sectionable. This mean, that all geometry in this entity can be cut via cutting plane.
  */
  virtual bool getSectionable(OdTvResult* rc = NULL) const;

  /** \details
  Sets that it is need to show shell normals for all shell objects in this entity.
  */
  virtual OdTvResult setShowShellNormals(bool bShow, double normalsLength = 0., const OdTvRGBColorDef& normalsColor = OdTvRGBColorDef());

  /** \details
  Returns true if shell normals are visible.
  */
  virtual bool getShowShellNormals(OdTvResult* rc = NULL) const;

  /** \details
  Sets that it is need to show sharp edges for all shell objects.
  */
  virtual OdTvResult setShowShellSharpEdges(bool bShow, OdUInt8 edgesWidth = 5, const OdTvRGBColorDef& edgesColor = OdTvRGBColorDef());

  /** \details
  Returns true if shell sharp edges are visible.
  */
  virtual bool getShowShellSharpEdges(OdTvResult* rc = NULL) const;

  /** \details
  Find an sub entity by name
  */
  virtual OdTvGeometryDataId findSubEntity(const OdUInt64 h, OdTvResult* rc = NULL);

  virtual OdTvResult setShadowParameters( bool bCastShadows, bool bReceiveShadow );

  virtual OdTvResult getShadowParameters( bool& bCastShadows, bool& bReceiveShadow );

  bool checkForSectionFilling( OdTvResult* rc = NULL ) const;
  virtual OdTvResult fixForSectionFilling();
  OdTvResult setNeedCheckShellsTopology( bool bCheck );
  bool getNeedCheckShellsTopology( OdTvResult* rc = NULL ) const;

  ODTV_DEFINE_XDATA_DECL(virtual);
  ODTV_DEFINE_HANDLED_OBJECT_DECL(virtual);
  ODTV_DEFINE_SERIALIZABLE_OBJECT_DECL(virtual);
};


/** \details
This is an implementation of the iterator class for the entity
*/
class ODTV_EXPORT OdTvEntitiesIteratorImpl : public OdTvEntitiesIterator
{
  friend class OdTvDatabaseImpl;
public:

  /** \details
  Returns true if and only if the traversal by this Iterator object is complete.
  */
  virtual bool done(OdTvResult* rc = NULL) const;

  /** \details
  Steps this Iterator object.
  */
  virtual OdTvResult step();

  /** \details
  Returns the entity currently referenced by this Iterator object.
  */
  virtual OdTvEntityId getEntity(OdTvResult* rc = NULL) const;

  /** \details
  Positions this Iterator object at the specified entity.
  \param objectId [in]  Entity ID.
  */
  virtual OdTvResult seek(const OdTvEntityId& EntityId);

  /** \details
  Methods for creating the object
  */
  static OdTvEntitiesIteratorPtr createObject(OdTvDbObjectIterator* pDbIterator);

  ODTV_WRAPPERS_REFERENCE_MEMBERS()

  virtual ~OdTvEntitiesIteratorImpl();

private:
  OdTvEntitiesIteratorImpl();
  OdTvEntitiesIteratorImpl(OdTvDbObjectIterator* pDbIterator);

  OdTvDbObjectIteratorPtr  m_pDbIterator;

  // reference counter
  unsigned int                m_nRefCounter;
};


/** \details
This is the most important function for the entity notifications about changes
This function finds first parent which has non-zero Gs node
*/
void odTvNotifyFirstParentWithGsNode(OdTvDbObjectId entityId);

/** \details
This is the very important function for the entity notifications about specific
changes of the child's entities or geometry.
This function finds first top-level parent (child of the model or block)
*/
void odTvNotifyTopParent(OdTvDbObjectId entityId, bool value, OdTvEntityImpl::entFlags bit);

//*********************************************************************************//
// This is the very important function for the entity notifications about specific 
// changes of the child's entities or geometry. 
// This function each parent entity in the subentiy paths until first top-level parent (child of the model or block)
//*********************************************************************************//
void odTvNotifyParentsTree(OdTvDbObjectId entityId, bool value, OdTvEntityImpl::entFlags bit, bool bIsSilent);

/** \details
Get native object's handle. If object has not user data, method will return -1
*/
OdUInt64 odTvGetNativeDatabaseHandle(OdTvXDataStorage* pObject, const OdTvRegAppId& appId);

#include "TD_PackPop.h"

#endif //_ODTV_ENTITYIMPL_H_INCLUDED_
