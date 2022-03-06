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

#ifndef _ODTV_ENTITYMESHDATA_H_INCLUDED_
#define _ODTV_ENTITYMESHDATA_H_INCLUDED_

#include "TD_PackPush.h"
#include "TvGeometryDataImpl.h"
#include "TvGeometry3DAttributes.h"

/** \details
This class implements the mesh data
*/
class OdTvMeshDataImpl : public OdTvGeometryDataImpl, OdGiDrawablePESelectionReactor
{
public:
  OdTvMeshDataImpl();
  virtual ~OdTvMeshDataImpl();

  //set/get
  OdTvResult set(OdUInt32 nRows, OdUInt32 nColumns, const OdTvPointArray& verticesArray);
  OdTvResult set(OdUInt32 nRows, OdUInt32 nColumns, OdUInt32 nVertices, const OdTvPoint* vertices);
  void get(OdUInt32& nRows, OdUInt32& nColumns, OdTvPointArray& verticesArray);

  OdTvResult setFacesSelectable(bool bSelectable);
  bool getFacesSelectable(bool* bIsInherited = NULL) const;

  OdTvResult setEdgesSelectable(bool bSelectable);
  bool getEdgesSelectable(bool* bIsInherited = NULL) const;

  OdTvResult setVerticesSelectable(bool bSelectable);
  bool getVerticesSelectable(bool* bIsInherited = NULL) const;

  OdUInt32 getFacesCount(OdTvResult* rc = NULL) const;
  OdUInt32 getEdgesCount(OdTvResult* rc = NULL) const;
  OdUInt32 getVerticesCount(OdTvResult* rc = NULL) const;
  OdUInt32 getRowsCount(OdTvResult* rc = NULL) const;
  OdUInt32 getColumnsCount(OdTvResult* rc = NULL) const;

  OdTvResult editVerticesViaRange(OdUInt32 startRow, OdUInt32 startColumn, OdUInt32 nRows, OdUInt32 nColumns, OdUInt32 nVertices, const OdTvPoint* vertices);
  
  OdTvResult editVerticesViaList(OdUInt32 nVertices, const OdTvVertexPos* indVertices, const OdTvPoint* vertices);

  /** \details
  Sets the selectability for faces, edges and vertices
  */
  virtual void setSelectabilityForElements(bool bFaces, bool bEdges, bool bVertices);

  /** \details
  Get sub geometry by marker
  */
  bool getSubGeomIdByGsMarker(const OdGsMarker& marker, OdTv::SubGeometryType& type, OdInt64& subGeomId) const;

  /** \details
  Get marker by sub geometry
  */
  bool getGsMarkerBySubGeomId(OdGsMarker& marker, const OdTv::SubGeometryType& type, const OdInt64& subGeomId) const;

  /** \details
  Get markers by sub geometry ids
  */
  bool getGsMarkersBySubGeomIds(OdArray< OdGsMarker >& markers, const OdTv::SubGeometryType& type, const OdUInt32Array& subGeomIds) const;

  /** \details
  Return the last marker of this shell object
  */
  OdGsMarker getEndMarker() const;

  /** \details
  Return the first - 1 marker of this shell object
  */
  OdGsMarker getStartMarker() const;

  /** \details
  Get all markers of this geometry data (including subgeometry)
  */
  virtual void getMarkers(std::set< OdGsMarker >& markers, std::set< OdGsMarker >* pCompareMarkers = NULL) const;

  //**************************************************************************************
  // Group of the methods for managing the properties of the vertices
  //**************************************************************************************

  /**
  Vertex colors management
  */
  OdTvResult setVertexColorsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvRGBColorDef* colors);
  OdTvResult setVertexColorsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvRGBColorDef& color);

  OdTvResult setVertexColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef& color);
  OdTvResult setVertexColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef* colors);

  OdTvResult getVertexColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvRGBColorDefArray& colors) const;
  OdTvResult getVertexColorsViaList(const OdInt32Array& indVertices, OdTvRGBColorDefArray& colors) const;
  OdTvRGBColorDef getVertexColor(OdInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Vertex orientation management
  */
  OdTvResult setVertexOrientation(OdTv::OrientationType orientation);
  OdTv::OrientationType getVertexOrientation(OdTvResult* rc = NULL) const;

  /**
  Vertex normals management
  */
  OdTvResult setVertexNormalsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvVector* vectors);
  OdTvResult setVertexNormalsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvVector& vector);

  OdTvResult setVertexNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector& vector);
  OdTvResult setVertexNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector* vectors);

  OdTvResult getVertexNormalsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVectorArray& vectors) const;
  OdTvResult getVertexNormalsViaList(const OdInt32Array& indVertices, OdTvVectorArray& vectors) const;
  OdTvVector getVertexNormal(OdInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Vertex mapping coords management
  */
  OdTvResult setVertexMappingCoordsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvPoint2d* mappingCoords);
  OdTvResult setVertexMappingCoordsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvPoint2d& mappingCoord);

  OdTvResult setVertexMappingCoordsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvPoint2d* mappingCoords);
  OdTvResult setVertexMappingCoordsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvPoint2d& mappingCoord);

  OdTvResult getVertexMappingCoordsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvPoint2dArray& mappingCoords) const;
  OdTvResult getVertexMappingCoordsViaList(const OdInt32Array& indexes, OdTvPoint2dArray& mappingCoords) const;
  OdTvPoint2d getVertexMappingCoord(OdInt32 ind, OdTvResult* rc = NULL) const;

  /** \details
  Check if mesh vertices can be selected
  */
  bool isVerticesSelectable(OdTvResult* rc = NULL) const;

  //**************************************************************************************
  // Group of the methods for managing the properties of the faces
  //**************************************************************************************

  /**
  Faces colors management
  */
  OdTvResult setFaceColorsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvColorDef* colors);
  OdTvResult setFaceColorsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvColorDef& color);

  OdTvResult setFaceColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef& color);
  OdTvResult setFaceColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef* colors);

  OdTvResult getFaceColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvColorDefArray& colors) const;
  OdTvResult getFaceColorsViaList(const OdInt32Array& indFaces, OdTvColorDefArray& colors) const;
  OdTvColorDef getFaceColor(OdInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Faces normals management
  */
  OdTvResult setFaceNormalsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvVector* vectors);
  OdTvResult setFaceNormalsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvVector& vector);

  OdTvResult setFaceNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector& vector);
  OdTvResult setFaceNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector* vectors);

  OdTvResult getFaceNormalsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVectorArray& vectors) const;
  OdTvResult getFaceNormalsViaList(const OdInt32Array& indFaces, OdTvVectorArray& vectors) const;
  OdTvVector getFaceNormal(OdInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Faces visibility management
  */
  OdTvResult setFaceVisibilitiesViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvVisibilityDef* visibles);
  OdTvResult setFaceVisibilitiesViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvVisibilityDef& visible);

  OdTvResult setFaceVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef* visibles);
  OdTvResult setFaceVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef& visible);

  OdTvResult getFaceVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVisibilityDefArray& visibilities) const;
  OdTvResult getFaceVisibilitiesViaList(const OdInt32Array& indFaces, OdTvVisibilityDefArray& visibilities) const;
  OdTvVisibilityDef getFaceVisibility(OdInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Faces layers management
  */
  OdTvResult setFaceLayersViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvLayerDef* layers, OdTvDbDatabase* pDb);
  OdTvResult setFaceLayersViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvLayerDef& layer, OdTvDbDatabase* pDb);

  OdTvResult setFaceLayersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLayerDef* layers, OdTvDbDatabase* pDb);
  OdTvResult setFaceLayersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLayerDef& layer, OdTvDbDatabase* pDb);

  OdTvResult getFaceLayersViaRange(OdInt32 indStart, OdInt32 nCount, OdTvLayerDefArray& layers, OdTvDbDatabase* pDb) const;
  OdTvResult getFaceLayersViaList(const OdInt32Array& indFaces, OdTvLayerDefArray& layers, OdTvDbDatabase* pDb) const;
  OdTvLayerDef getFaceLayer(OdInt32 ind, OdTvDbDatabase* pDb, OdTvResult* rc = NULL) const;

  /**
  Faces transparency management
  */
  OdTvResult setFaceTransparencyViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvTransparencyDef* transparencies);
  OdTvResult setFaceTransparencyViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvTransparencyDef& transparency);

  OdTvResult setFaceTransparencyViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvTransparencyDef* transparencies);
  OdTvResult setFaceTransparencyViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvTransparencyDef& transparency);

  OdTvResult getFaceTransparencyViaRange(OdInt32 indStart, OdInt32 nCount, OdTvTransparencyDefArray& transparencies) const;
  OdTvResult getFaceTransparencyViaList(const OdInt32Array& indFaces, OdTvTransparencyDefArray& transparencies) const;
  OdTvTransparencyDef getFaceTransparency(OdInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Faces materials management
  */
  OdTvResult setFaceMaterialsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvMaterialDef* materials, OdTvDbDatabase* pDb);
  OdTvResult setFaceMaterialsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvMaterialDef& material, OdTvDbDatabase* pDb);

  OdTvResult setFaceMaterialsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMaterialDef* materials, OdTvDbDatabase* pDb);
  OdTvResult setFaceMaterialsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMaterialDef& material, OdTvDbDatabase* pDb);

  OdTvResult getFaceMaterialsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvMaterialDefArray& materials, OdTvDbDatabase* pDb) const;
  OdTvResult getFaceMaterialsViaList(const OdInt32Array& indFaces, OdTvMaterialDefArray& materials, OdTvDbDatabase* pDb) const;
  OdTvMaterialDef getFaceMaterial(OdInt32 ind, OdTvDbDatabase* pDb, OdTvResult* rc = NULL) const;

  /**
  Faces mappers management
  */
  OdTvResult setFaceMappersViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvMapperDef* mappers);
  OdTvResult setFaceMappersViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvMapperDef& mapper);

  OdTvResult setFaceMappersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMapperDef* mappers);
  OdTvResult setFaceMappersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMapperDef& mapper);

  OdTvResult getFaceMappersViaRange(OdInt32 indStart, OdInt32 nCount, OdTvMapperDefArray& mappers) const;
  OdTvResult getFaceMappersViaList(const OdInt32Array& indFaces, OdTvMapperDefArray& mappers) const;
  OdTvMapperDef getFaceMapper(OdInt32 ind, OdTvResult* rc = NULL) const;

  /** \details
  Check if mesh faces can be selected
  */
  bool isFacesSelectable(OdTvResult* rc = NULL) const;

  //**************************************************************************************
  // Group of the methods for managing the properties of the edges
  //**************************************************************************************

  /**
  Edges colors management
  */
  OdTvResult setEdgeColorsViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvColorDef* colors);
  OdTvResult setEdgeColorsViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvColorDef& color);

  OdTvResult setEdgeColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef& color);
  OdTvResult setEdgeColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef* colors);

  OdTvResult getEdgeColorsViaList(const OdInt32Array& indEdges, OdTvColorDefArray& colors) const;
  OdTvResult getEdgeColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvColorDefArray& colors) const;
  OdTvColorDef getEdgeColor(OdUInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Edges visibilities management
  */
  OdTvResult setEdgeVisibilitiesViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvVisibilityDef* visibilities);
  OdTvResult setEdgeVisibilitiesViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvVisibilityDef& visibility);

  OdTvResult setEdgeVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef& visibility);
  OdTvResult setEdgeVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef* visibilities);

  OdTvResult getEdgeVisibilitiesViaList(const OdInt32Array& indEdges, OdTvVisibilityDefArray& visibilities) const;
  OdTvResult getEdgeVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVisibilityDefArray& visibilities) const;
  OdTvVisibilityDef getEdgeVisibility(OdUInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Edges linetypes management
  */
  OdTvResult setEdgeLinetypesViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvLinetypeDef* linetypes, OdTvDbDatabase* pDb);
  OdTvResult setEdgeLinetypesViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvLinetypeDef& linetype, OdTvDbDatabase* pDb);

  OdTvResult setEdgeLinetypesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLinetypeDef& linetype, OdTvDbDatabase* pDb);
  OdTvResult setEdgeLinetypesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLinetypeDef* linetypes, OdTvDbDatabase* pDb);

  OdTvResult getEdgeLinetypesViaList(const OdInt32Array& indEdges, OdTvLinetypeDefArray& linetypes, OdTvDbDatabase* pDb) const;
  OdTvResult getEdgeLinetypesViaRange(OdInt32 indStart, OdInt32 nCount, OdTvLinetypeDefArray& linetypes, OdTvDbDatabase* pDb) const;
  OdTvLinetypeDef getEdgeLinetype(OdUInt32 ind, OdTvDbDatabase* pDb, OdTvResult* rc = NULL) const;

  /**
  Edges layers management
  */
  OdTvResult setEdgeLayersViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvLayerDef* layers, OdTvDbDatabase* pDb);
  OdTvResult setEdgeLayersViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvLayerDef& layer, OdTvDbDatabase* pDb);

  OdTvResult setEdgeLayersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLayerDef& layer, OdTvDbDatabase* pDb);
  OdTvResult setEdgeLayersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLayerDef* layers, OdTvDbDatabase* pDb);

  OdTvResult getEdgeLayersViaList(const OdInt32Array& indEdges, OdTvLayerDefArray& layers, OdTvDbDatabase* pDb) const;
  OdTvResult getEdgeLayersViaRange(OdInt32 indStart, OdInt32 nCount, OdTvLayerDefArray& layers, OdTvDbDatabase* pDb) const;
  OdTvLayerDef getEdgeLayer(OdUInt32 ind, OdTvDbDatabase* pDb, OdTvResult* rc = NULL) const;

  /** \details
  Check if mesh edges can be selected
  */
  bool isEdgesSelectable(OdTvResult* rc = NULL) const;

  /** \details
  Set vertices color. If bOverride flag is true, color will be applied to mesh. Otherwise, color from attributes will be applied.
  */
  OdTvResult setOverrideVerticesColor(bool bOverride, const OdTvRGBColorDef& color);
  OdTvRGBColorDef getOverrideVerticesColor(bool& bOverride, OdTvResult* rc = NULL) const;

  /**
  Vertices visibility
  */
  OdTvResult setShowVertices(bool bShow, OdInt32 verticesSize = 10);
  bool getShowVertices(OdInt32& verticesSize, OdTvResult* rc = NULL) const;

  OdTvResult setShowOnlyVertices(bool bShowOnly);
  bool getShowOnlyVertices(OdTvResult* rc = NULL) const;

  //**************************************************************************************
  // Override 'OdTvGeometryDataImpl' methods
  //**************************************************************************************

  virtual TvGeometryType                      entityGeometryDataType() const { return Mesh; }
  virtual bool                                draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual void                                drawForMarkers(const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual OdTvGeometryData::GeometryTypes     getFirstColorGeomType() const { return OdTvGeometryData::kFaces; } // it important to use the same geometry in the following two methods
  virtual OdTvGeometryData::GeometryTypes     getSecondColorGeomType() const { return OdTvGeometryData::kFaces; }
  virtual void                                read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                                write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual void                                setSelectability(const OdTvSelectabilityDef& selectability);
  virtual bool                                isSelectable() const;
  virtual bool                                copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;

  //**************************************************************************************
  // OdTvIObject methods implementation
  //**************************************************************************************
  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

  /** \details
  Use spatial tree for selection.
  */
  OdTvResult setUseSpatialTreeForSelection(bool bUseSpatialTreeForSelection, OdUInt32 nVerticesLimit);
  OdUInt32 getUseSpatialTreeForSelection(OdTvResult* rc = NULL) const;

  virtual OdTvResult getSnapPoints(OdTvGeometryData::SnapMode snapMode, const OdTvPoint& pickPoint, const OdTvMatrix& xWorldToEye
    , OdTvPointArray& snapPoints, const OdTvMatrix* pTransform = NULL, double focalLength = -1.) const;

  virtual bool getSupportSnapMode(OdTvGeometryData::SnapMode snapMode, OdTvResult* rc = NULL) const;

  virtual OdUInt32 selected(OdGsMarker offset, double depth);

  virtual OdUInt32 hasOutOfSelection();

private:
  void generateFacesArray(OdInt32Array& facesList) const;
  void generateTriangFacesArray(OdInt32Array& facesList) const;

  //methods for support internal spatial tree and getShapPoints
  void updateExtents();
  //Init spatial tree
  void initSpatialTree();
  //  Reset spatial tree
  virtual void resetSpatialTree();
  // Process spatial tree edit
  virtual void processSpatialTreeEdit(OdUInt32 startPos, OdUInt32 nFaces, bool bNeedRemove = true);
  virtual void processSpatialTreeEdit(OdUInt32 nFaces, const OdUInt32* indFaces);

private:
  OdTvPointArray        m_vertices;
  mutable OdInt32Array  m_triangFaces;

  OdUInt32 m_nRows;
  OdUInt32 m_nColumns;

  // attributes storage
  OdTvGeometry3DAttributes m_attributes;

  OdTvExtents3d            m_extents;

  //indicates that it is need to use internal spatial tree
  bool                          m_bUseSpatialTreeForSelection;
  OdTvExtentsSpaceTreeTriangle* m_pSpatialTree;
  OdUInt32                      m_nLimitVertices;

  //for get snap points (not for copy of read/write
  mutable std::map<OdUInt32, double>        m_faceWithEyeDepthMap;
};

typedef OdTvSmartPtrInternal<OdTvMeshDataImpl> OdTvMeshDataImplPtr;

/** \details
This is an wrapper of the interface class for OdTvGeometryData object.

\remarks
The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvMeshDataWrapper : public OdTvMeshData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvMeshData)

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
  Set the geometry data of the mesh
  */
  virtual OdTvResult setParam(OdUInt32 nRows, OdUInt32 nColumns, const OdTvPointArray& verticesArray);

  /** \details
  Set the geometry data of the mesh
  */
  virtual OdTvResult setParam(OdUInt32 nRows, OdUInt32 nColumns, OdUInt32 nVertices, const OdTvPoint* vertices);

  /** \details
  Get the geometry data of the mesh
  */
  virtual OdTvResult getParam(OdUInt32& nRows, OdUInt32& nColumns, OdTvPointArray& verticesArray);

  /** \details
  Returns the number of vertices in the mesh
  */
  virtual OdUInt32 getVerticesCount(OdTvResult* rc = NULL) const;

  /** \details
  Returns the number of faces in the mesh
  */
  virtual OdUInt32 getFacesCount(OdTvResult* rc = NULL) const;

  /** \details
  Returns the number of edges in the mesh
  */
  virtual OdUInt32 getEdgesCount(OdTvResult* rc = NULL) const;

  /** \details
  Returns the rows of rows in the mesh
  */
  virtual OdUInt32 getRowsCount(OdTvResult* rc = NULL) const;

  /** \details
  Returns the number of columns in the mesh
  */
  virtual OdUInt32 getColumnsCount(OdTvResult* rc = NULL) const;

  /** \details
  Sets that the faces of the mesh can be selected
  */
  virtual OdTvResult setFacesSelectable(bool bSelectable);

  /** \details
  Returns true if and only if the faces of the mesh can be slelected.
  The second returned parameter 'bIsInherited' will be true if and only if
  the faces should be selected due to appropriate selectability of the parent entity or subentity
  */
  virtual bool getFacesSelectable(bool* bIsInherited = NULL, OdTvResult* rc = NULL) const;

  /** \details
  Sets that the edges of the mesh can be selected
  */
  virtual OdTvResult setEdgesSelectable(bool bSelectable);

  /** \details
  Returns true if and only if the edges of the mesh can be selected.
  The second returned parameter 'bIsInherited' will be true if and only if
  the edges should be selected due to appropriate selectability of the parent entity or subentity
  */
  virtual bool getEdgesSelectable(bool* bIsInherited = NULL, OdTvResult* rc = NULL) const;
 
/** \details
  Replace vertices of the mesh starting with startPos
  */
  virtual OdTvResult editVerticesViaRange(OdUInt32 startRow, OdUInt32 startColumn, OdUInt32 nRows, OdUInt32 nColumns, const OdTvPointArray& verticesArray);

  /** \details
  Replace vertices of the mesh starting with startPos
  */
  virtual OdTvResult editVerticesViaRange(OdUInt32 startRow, OdUInt32 startColumn, OdUInt32 nRows, OdUInt32 nColumns, OdUInt32 nVertices, const OdTvPoint* vertices);

  /** \details
  Replace vertices defined by 'indVertices' of the mesh
  */
  virtual OdTvResult editVerticesViaList(const OdTvVertexPosArray& indVertices, const OdTvPointArray& verticesArray);

  /** \details
  Replace vertices defined by 'indVertices' of the mesh
  */
  virtual OdTvResult editVerticesViaList(OdUInt32 nVertices, const OdTvVertexPos* indVertices, const OdTvPoint* vertices);

  //**************************************************************************************
  // Group of the methods for managing the properties of the vertices
  //**************************************************************************************

  /**
  Vertex colors management
  */
  virtual OdTvResult setVertexColorsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvRGBColorDef* colors);
  virtual OdTvResult setVertexColorsViaList(const OdInt32Array& indVertices, const OdTvRGBColorDefArray& colors);
  virtual OdTvResult setVertexColorsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvRGBColorDef& color);
  virtual OdTvResult setVertexColorsViaList(const OdInt32Array& indVertices, const OdTvRGBColorDef& color);

  virtual OdTvResult setVertexColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef& color);
  virtual OdTvResult setVertexColorsViaRange(OdInt32 indStart, const OdTvRGBColorDefArray& colors);
  virtual OdTvResult setVertexColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef* colors);

  virtual OdTvResult getVertexColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvRGBColorDefArray& colors) const;
  virtual OdTvResult getVertexColorsViaList(const OdInt32Array& indVertices, OdTvRGBColorDefArray& colors) const;
  virtual OdTvRGBColorDef getVertexColor(OdInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Vertex orientation management
  */
  virtual OdTvResult setVertexOrientation(OdTv::OrientationType orientation);
  virtual OdTv::OrientationType getVertexOrientation(OdTvResult* rc = NULL) const;

  /**
  Vertex normals management
  */
  virtual OdTvResult setVertexNormalsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvVector* vectors);
  virtual OdTvResult setVertexNormalsViaList(const OdInt32Array& indVertices, const OdTvVectorArray& vectors);
  virtual OdTvResult setVertexNormalsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvVector& vector);
  virtual OdTvResult setVertexNormalsViaList(const OdInt32Array& indVertices, const OdTvVector& vector);

  virtual OdTvResult setVertexNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector& vector);
  virtual OdTvResult setVertexNormalsViaRange(OdInt32 indStart, const OdTvVectorArray& vectors);
  virtual OdTvResult setVertexNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector* vectors);

  virtual OdTvResult getVertexNormalsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVectorArray& vectors) const;
  virtual OdTvResult getVertexNormalsViaList(const OdInt32Array& indVertices, OdTvVectorArray& vectors) const;
  virtual OdTvVector getVertexNormal(OdInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Vertex mapping coords management
  */
  virtual OdTvResult setVertexMappingCoordsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvPoint2d* mappingCoords);
  virtual OdTvResult setVertexMappingCoordsViaList(const OdInt32Array indVertices, const OdTvPoint2dArray& mappingCoords);
  virtual OdTvResult setVertexMappingCoordsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvPoint2d& mappingCoord);
  virtual OdTvResult setVertexMappingCoordsViaList(const OdInt32Array indVertices, const OdTvPoint2d& mappingCoord);

  virtual OdTvResult setVertexMappingCoordsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvPoint2d* mappingCoords);
  virtual OdTvResult setVertexMappingCoordsViaRange(OdInt32 indStart, const OdTvPoint2dArray& mappingCoords);
  virtual OdTvResult setVertexMappingCoordsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvPoint2d& mappingCoord);

  virtual OdTvResult getVertexMappingCoordsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvPoint2dArray& mappingCoords) const;
  virtual OdTvResult getVertexMappingCoordsViaList(const OdInt32Array& indexes, OdTvPoint2dArray& mappingCoords) const;
  virtual OdTvPoint2d getVertexMappingCoord(OdInt32 ind, OdTvResult* rc = NULL) const;

  //**************************************************************************************
  // Group of the methods for managing the properties of the faces
  //**************************************************************************************

  /**
  Faces colors management
  */
  virtual OdTvResult setFaceColorsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvColorDef* colors);
  virtual OdTvResult setFaceColorsViaList(const OdInt32Array& indFaces, const OdTvColorDefArray& colors);
  virtual OdTvResult setFaceColorsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvColorDef& color);
  virtual OdTvResult setFaceColorsViaList(const OdInt32Array& indFaces, const OdTvColorDef& color);

  virtual OdTvResult setFaceColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef& color);
  virtual OdTvResult setFaceColorsViaRange(OdInt32 indStart, const OdTvColorDefArray& colors);
  virtual OdTvResult setFaceColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef* colors);

  virtual OdTvResult getFaceColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvColorDefArray& colors) const;
  virtual OdTvResult getFaceColorsViaList(const OdInt32Array& indFaces, OdTvColorDefArray& colors) const;
  virtual OdTvColorDef getFaceColor(OdInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Faces normals management
  */
  virtual OdTvResult setFaceNormalsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvVector* vectors);
  virtual OdTvResult setFaceNormalsViaList(const OdInt32Array& indFaces, const OdTvVectorArray& vectors);
  virtual OdTvResult setFaceNormalsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvVector& vector);
  virtual OdTvResult setFaceNormalsViaList(const OdInt32Array& indFaces, const OdTvVector& vector);

  virtual OdTvResult setFaceNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector& vector);
  virtual OdTvResult setFaceNormalsViaRange(OdInt32 indStart, const OdTvVectorArray& vectors);
  virtual OdTvResult setFaceNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector* vectors);

  virtual OdTvResult getFaceNormalsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVectorArray& vectors) const;
  virtual OdTvResult getFaceNormalsViaList(const OdInt32Array& indFaces, OdTvVectorArray& vectors) const;
  virtual OdTvVector getFaceNormal(OdInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Faces visibility management
  */
  virtual OdTvResult setFaceVisibilitiesViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvVisibilityDef* visibilities);
  virtual OdTvResult setFaceVisibilitiesViaList(const OdInt32Array& indFaces, const OdTvVisibilityDefArray& visibilities);
  virtual OdTvResult setFaceVisibilitiesViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvVisibilityDef& visibility);
  virtual OdTvResult setFaceVisibilitiesViaList(const OdInt32Array& indFaces, const OdTvVisibilityDef& visibility);

  virtual OdTvResult setFaceVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef* visibilities);
  virtual OdTvResult setFaceVisibilitiesViaRange(OdInt32 indStart, const OdTvVisibilityDefArray& visibilities);
  virtual OdTvResult setFaceVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef& visibility);

  virtual OdTvResult getFaceVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVisibilityDefArray& visibilities) const;
  virtual OdTvResult getFaceVisibilitiesViaList(const OdInt32Array& indFaces, OdTvVisibilityDefArray& visibilities) const;
  virtual OdTvVisibilityDef getFaceVisibility(OdInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Faces layers management
  */
  virtual OdTvResult setFaceLayersViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvLayerDef* layers);
  virtual OdTvResult setFaceLayersViaList(const OdInt32Array& indFaces, const OdTvLayerDefArray& layers);
  virtual OdTvResult setFaceLayersViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvLayerDef& layer);
  virtual OdTvResult setFaceLayersViaList(const OdInt32Array& indFaces, const OdTvLayerDef& layer);

  virtual OdTvResult setFaceLayersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLayerDef* layers);
  virtual OdTvResult setFaceLayersViaRange(OdInt32 indStart, const OdTvLayerDefArray& layers);
  virtual OdTvResult setFaceLayersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLayerDef& layer);

  virtual OdTvResult getFaceLayersViaRange(OdInt32 indStart, OdInt32 nCount, OdTvLayerDefArray& layers) const;
  virtual OdTvResult getFaceLayersViaList(const OdInt32Array& indFaces, OdTvLayerDefArray& layers) const;
  virtual OdTvLayerDef getFaceLayer(OdInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Faces transparency management
  */
  virtual OdTvResult setFaceTransparencyViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvTransparencyDef* transparencies);
  virtual OdTvResult setFaceTransparencyViaList(const OdInt32Array& indFaces, const OdTvTransparencyDefArray& transparencies);
  virtual OdTvResult setFaceTransparencyViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvTransparencyDef& transparency);
  virtual OdTvResult setFaceTransparencyViaList(const OdInt32Array& indFaces, const OdTvTransparencyDef& transparency);

  virtual OdTvResult setFaceTransparencyViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvTransparencyDef* transparencies);
  virtual OdTvResult setFaceTransparencyViaRange(OdInt32 indStart, const OdTvTransparencyDefArray& transparencies);
  virtual OdTvResult setFaceTransparencyViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvTransparencyDef& transparency);

  virtual OdTvResult getFaceTransparencyViaRange(OdInt32 indStart, OdInt32 nCount, OdTvTransparencyDefArray& transparencies) const;
  virtual OdTvResult getFaceTransparencyViaList(const OdInt32Array& indFaces, OdTvTransparencyDefArray& transparencies) const;
  virtual OdTvTransparencyDef getFaceTransparency(OdInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Faces materials management
  */
  virtual OdTvResult setFaceMaterialsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvMaterialDef* materials);
  virtual OdTvResult setFaceMaterialsViaList(const OdInt32Array& indFaces, const OdTvMaterialDefArray& materials);
  virtual OdTvResult setFaceMaterialsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvMaterialDef& material);
  virtual OdTvResult setFaceMaterialsViaList(const OdInt32Array& indFaces, const OdTvMaterialDef& material);

  virtual OdTvResult setFaceMaterialsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMaterialDef* materials);
  virtual OdTvResult setFaceMaterialsViaRange(OdInt32 indStart, const OdTvMaterialDefArray& materials);
  virtual OdTvResult setFaceMaterialsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMaterialDef& material);

  virtual OdTvResult getFaceMaterialsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvMaterialDefArray& materials) const;
  virtual OdTvResult getFaceMaterialsViaList(const OdInt32Array& indFaces, OdTvMaterialDefArray& materials) const;
  virtual OdTvMaterialDef getFaceMaterial(OdInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Faces mappers management
  */
  virtual OdTvResult setFaceMappersViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvMapperDef* mappers);
  virtual OdTvResult setFaceMappersViaList(const OdInt32Array& indFaces, const OdTvMapperDefArray& mappers);
  virtual OdTvResult setFaceMappersViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvMapperDef& mapper);
  virtual OdTvResult setFaceMappersViaList(const OdInt32Array& indFaces, const OdTvMapperDef& mapper);

  virtual OdTvResult setFaceMappersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMapperDef* mappers);
  virtual OdTvResult setFaceMappersViaRange(OdInt32 indStart, const OdTvMapperDefArray& mappers);
  virtual OdTvResult setFaceMappersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMapperDef& mapper);

  virtual OdTvResult setFaceMapper(const OdTvMapperDef& mapper);
  virtual OdTvResult getFaceMappersViaRange(OdInt32 indStart, OdInt32 nCount, OdTvMapperDefArray& mappers) const;
  virtual OdTvResult getFaceMappersViaList(const OdInt32Array& indFaces, OdTvMapperDefArray& mappers) const;
  virtual OdTvMapperDef getFaceMapper(OdInt32 ind, OdTvResult* rc = NULL) const;

  //**************************************************************************************
  // Group of the methods for managing the properties of the edges
  //**************************************************************************************

  /**
  Edges colors management
  */
  virtual OdTvResult setEdgeColorsViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvColorDef* colors);
  virtual OdTvResult setEdgeColorsViaList(const OdInt32Array& indEdges, const OdTvColorDefArray& colors);
  virtual OdTvResult setEdgeColorsViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvColorDef& color);
  virtual OdTvResult setEdgeColorsViaList(const OdInt32Array& indEdges, const OdTvColorDef& color);

  virtual OdTvResult setEdgeColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef& color);
  virtual OdTvResult setEdgeColorsViaRange(OdInt32 indStart, const OdTvColorDefArray& colors);
  virtual OdTvResult setEdgeColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef* colors);

  virtual OdTvResult getEdgeColorsViaList(const OdInt32Array& indEdges, OdTvColorDefArray& colors) const;
  virtual OdTvResult getEdgeColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvColorDefArray& colors) const;
  virtual OdTvColorDef getEdgeColor(OdUInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Edges visibility management
  */
  virtual OdTvResult setEdgeVisibilitiesViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvVisibilityDef* visibilities);
  virtual OdTvResult setEdgeVisibilitiesViaList(const OdInt32Array& indEdges, const OdTvVisibilityDefArray& visibilities);
  virtual OdTvResult setEdgeVisibilitiesViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvVisibilityDef& visibility);
  virtual OdTvResult setEdgeVisibilitiesViaList(const OdInt32Array& indEdges, const OdTvVisibilityDef& visibility);

  virtual OdTvResult setEdgeVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef& visibility);
  virtual OdTvResult setEdgeVisibilitiesViaRange(OdInt32 indStart, const OdTvVisibilityDefArray& visibilities);
  virtual OdTvResult setEdgeVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef* visibilities);

  virtual OdTvResult getEdgeVisibilitiesViaList(const OdInt32Array& indEdges, OdTvVisibilityDefArray& visibilities) const;
  virtual OdTvResult getEdgeVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVisibilityDefArray& visibilities) const;
  virtual OdTvVisibilityDef getEdgeVisibility(OdUInt32 ind, OdTvResult* rc = NULL) const;


  /**
  Edges linetypes management
  */
  virtual OdTvResult setEdgeLinetypesViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvLinetypeDef* linetypes);
  virtual OdTvResult setEdgeLinetypesViaList(const OdInt32Array& indEdges, const OdTvLinetypeDefArray& linetypes);
  virtual OdTvResult setEdgeLinetypesViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvLinetypeDef& linetype);
  virtual OdTvResult setEdgeLinetypesViaList(const OdInt32Array& indEdges, const OdTvLinetypeDef& linetype);

  virtual OdTvResult setEdgeLinetypesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLinetypeDef& linetype);
  virtual OdTvResult setEdgeLinetypesViaRange(OdInt32 indStart, const OdTvLinetypeDefArray& linetypes);
  virtual OdTvResult setEdgeLinetypesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLinetypeDef* linetypes);

  virtual OdTvResult getEdgeLinetypesViaList(const OdInt32Array& indEdges, OdTvLinetypeDefArray& linetypes) const;
  virtual OdTvResult getEdgeLinetypesViaRange(OdInt32 indStart, OdInt32 nCount, OdTvLinetypeDefArray& linetypes) const;
  virtual OdTvLinetypeDef getEdgeLinetype(OdUInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Edges layers management
  */
  virtual OdTvResult setEdgeLayersViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvLayerDef* layers);
  virtual OdTvResult setEdgeLayersViaList(const OdInt32Array& indEdges, const OdTvLayerDefArray& layers);
  virtual OdTvResult setEdgeLayersViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvLayerDef& layer);
  virtual OdTvResult setEdgeLayersViaList(const OdInt32Array& indEdges, const OdTvLayerDef& layer);

  virtual OdTvResult setEdgeLayersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLayerDef& layer);
  virtual OdTvResult setEdgeLayersViaRange(OdInt32 indStart, const OdTvLayerDefArray& layers);
  virtual OdTvResult setEdgeLayersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLayerDef* layers);

  virtual OdTvResult getEdgeLayersViaList(const OdInt32Array& indEdges, OdTvLayerDefArray& layers) const;
  virtual OdTvResult getEdgeLayersViaRange(OdInt32 indStart, OdInt32 nCount, OdTvLayerDefArray& layers) const;
  virtual OdTvLayerDef getEdgeLayer(OdUInt32 ind, OdTvResult* rc = NULL) const;

  /** \details
  Set vertices color. If bOverride flag is true, color will be applied to mesh. Otherwise, color from attributes will be applied.
  */
  virtual OdTvResult setOverrideVerticesColor(bool bOverride, const OdTvRGBColorDef& color);
  virtual OdTvRGBColorDef getOverrideVerticesColor(bool& bOverride, OdTvResult* rc = NULL) const;

  /**
  Vertices visibility
  */
  virtual OdTvResult setShowVertices(bool bShow, OdInt32 verticesSize = 10);
  virtual bool getShowVertices(OdInt32& verticesSize, OdTvResult* rc = NULL) const;

  virtual OdTvResult setShowOnlyVertices(bool bShowOnly);
  virtual bool getShowOnlyVertices(OdTvResult* rc = NULL) const;

  /** \details
  Use spatial tree for selection.
  */
  virtual OdTvResult setUseSpatialTreeForSelection(bool bUseSpatialTreeForSelection, OdUInt32 nVerticesLimit = 50000);
  virtual OdUInt32 getUseSpatialTreeForSelection(OdTvResult* rc = NULL) const;
};

#include "TD_PackPop.h"

#endif //_ODTV_ENTITYMESHDATA_H_INCLUDED_
