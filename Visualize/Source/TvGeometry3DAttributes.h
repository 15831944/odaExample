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

#ifndef _ODTV_GEOMETRY3DATTRIBUTES_H_INCLUDED_
#define _ODTV_GEOMETRY3DATTRIBUTES_H_INCLUDED_

#include "TD_PackPush.h"
#include "GiWorldDraw.h"
#include "GiFill.h"

#include "TvTraitsDefImpl.h"
#include "TvEntityImpl.h"
#include "TvGeometryTypifiedData3DImpl.h"

#define kTvSubentTypeStep 3
#define tvGetFaceMarker(nIndex) ((nIndex) * kTvSubentTypeStep + OdDb::kFaceSubentType)
#define tvGetEdgeMarker(nIndex) ((nIndex) * kTvSubentTypeStep + OdDb::kEdgeSubentType)
#define tvGetVertexMarker(nIndex) ((nIndex) * kTvSubentTypeStep + OdDb::kVertexSubentType)

/** \details
  This class implements the storage and the calculator of the faces, edges and vertices attributes
*/
class OdTvGeometry3DAttributes
{
public:

  enum SelectableSubGeom
  {
    kFaces = 1,
    kEdges = 2,
    kVertices = 4,
    kFacesParent = 8,
    kEdgesParent = 16,
    kVerticesParent = 32
  };

  OdTvGeometry3DAttributes(): m_bRaw3DGeometry(true), m_vertexOrientationType(kOdGiNoOrientation), m_selectableFlags(0), m_endMarker(0), m_startMarker(0), m_bShowVertices(false), m_nVerticesSize(5), m_bShowOnlyVertices(false), m_bOverrideVerticesColor(false) {}
  virtual ~OdTvGeometry3DAttributes()
  {
    m_facesMarkers.clear();
    m_edgesMarkers.clear();
  }

  OdTvGeometry3DAttributes& operator = (const OdTvGeometry3DAttributes& source);

  void read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  void write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;

  OdGiFaceData*     getFaceData(OdUInt32 nFaces, const OdTvPointArray& vertices, const OdInt32Array& faces, const OdTvEntityImpl* pParentEntity, OdGiWorldDraw* pWorldDraw, OdTvGeometryDataAttributes* pAttribs, OdGiFaceData* fData);
  OdGiEdgeData*     getEdgeData(OdUInt32 nEdges, const OdInt32Array& faces, const OdTvEntityImpl* pParentEntity, OdGiWorldDraw* pWorldDraw, OdTvGeometryDataAttributes* pAttribs, OdGiEdgeData* eData);
  OdGiVertexData*   getVertexData(const OdTvPointArray& vertices, const OdInt32Array& faces, const OdTvEntityImpl* pParentEntity, OdGiWorldDraw* pWorldDraw, OdTvGeometryDataAttributes* pAttribs, OdGiVertexData* vData);

  void setFaceMarkers(OdUInt32 nFaces);
  void setEdgeMarkers(OdUInt32 nEdges);
  void setVertexMarkers(OdUInt32 nVertices);

  void restoreAttributeArrays();
  void clear();
  void clearEdges();
  void clearMarkers();

  /** \details
  Get sub geometry by marker
  */
  bool getSubGeomIdByGsMarker(const OdGsMarker& marker, OdTv::SubGeometryType& type, OdInt64& subGeomId, OdUInt32 nFaces, OdUInt32 nEdges, OdUInt32 nVertices) const;

  /** \details
  Get marker by sub geometry
  */
  bool getGsMarkerBySubGeomId(OdGsMarker& marker, const OdTv::SubGeometryType& type, const OdInt64& subGeomId) const;

  /** \details
  Get markers by sub geometry ids
  */
  bool getGsMarkersBySubGeomIds(OdArray< OdGsMarker >& markers, const OdTv::SubGeometryType& type, const OdUInt32Array& subGeomIds) const;


  void setStartMarker(const OdGsMarker& marker) { m_startMarker = marker; }
  OdGsMarker getStartMarker() const { return m_startMarker; }
  OdGsMarker getEndMarker() const { return m_endMarker; }

  /** \details
  Set/get the selectability for faces, edges and vertices
  */
  void setFacesSelectable(bool bFaces, bool bFromParent = false);
  void setEdgesSelectable(bool bEdges, bool bFromParent = false);
  void setVerticesSelectable(bool bVertices, bool bFromParent = false);

  bool getFacesSelectable(bool& bFromParent) const;
  bool getEdgesSelectable(bool& bFromParent) const;
  bool getVerticesSelectable(bool& bFromParent) const;

  //**************************************************************************************
  // Group of the methods for managing the properties of the vertices
  //**************************************************************************************

  /**
  Vertex colors management
  */
  OdTvResult setVertexColorsViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indVertices, const OdTvRGBColorDef* colors);
  OdTvResult setVertexColorsViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indVertices, const OdTvRGBColorDef& color);

  OdTvResult setVertexColorsViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef& color);
  OdTvResult setVertexColorsViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef* colors);

  OdTvResult getVertexColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvRGBColorDefArray& colors) const;
  OdTvResult getVertexColorsViaList(const OdInt32Array& indexes, OdTvRGBColorDefArray& colors) const;
  OdTvRGBColorDef getVertexColor(OdInt32 ind, OdTvResult* rc = NULL) const;
  const OdTvColorArrayStorage& getVertexColors() const { return m_vertexColors; };

  /**
  Vertex orientation management
  */
  OdTvResult setVertexOrientation(OdTv::OrientationType orientation);
  OdTv::OrientationType getVertexOrientation(OdTvResult* rc = NULL) const;

  /**
  Vertex normals management
  */
  OdTvResult setVertexNormalsViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indVertices, const OdTvVector* vectors);
  OdTvResult setVertexNormalsViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indVertices, const OdTvVector& vector);
                       
  OdTvResult setVertexNormalsViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvVector& vector);
  OdTvResult setVertexNormalsViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvVector* vectors);

  OdTvResult getVertexNormalsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVectorArray& vectors) const;
  OdTvResult getVertexNormalsViaList(const OdInt32Array& indexes, OdTvVectorArray& vectors) const;
  OdTvVector getVertexNormal(OdInt32 ind, OdTvResult* rc = NULL) const;
  const OdTvVector3dArrayStorage& getVertexNormals() const { return m_vertexNormals; }

  /**
  Vertex mapping coords management
  */
  OdTvResult setVertexMappingCoordsViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indVertices, const OdTvPoint* mappingCoords);
  OdTvResult setVertexMappingCoordsViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indVertices, const OdTvPoint& mappingCoord);

  OdTvResult setVertexMappingCoordsViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvPoint* mappingCoords);
  OdTvResult setVertexMappingCoordsViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvPoint& mappingCoord);

  OdTvResult getVertexMappingCoordsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvPointArray& mappingCoords) const;
  OdTvResult getVertexMappingCoordsViaList(const OdInt32Array& indexes, OdTvPointArray& mappingCoords) const;
  OdTvPoint getVertexMappingCoord(OdInt32 ind, OdTvResult* rc = NULL) const;

  /** \details
  Check if vertices can be selected
  */
  bool isVerticesSelectable(OdTvResult* rc = NULL) const;

  /** \details
  Get vertex markers array
  */
  const OdGsMarkerArray* getVertexMarkers() const;

  //**************************************************************************************
  // Group of the methods for managing the properties of the faces
  //**************************************************************************************

  /**
  Faces colors management
  */
  OdTvResult setFaceColorsViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indFaces, const OdTvColorDef* colors);
  OdTvResult setFaceColorsViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indFaces, const OdTvColorDef& color);

  OdTvResult setFaceColorsViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvColorDef& color);
  OdTvResult setFaceColorsViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvColorDef* colors);

  OdTvResult getFaceColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvColorDefArray& colors) const;
  OdTvResult getFaceColorsViaList(const OdInt32Array& indexes, OdTvColorDefArray& colors) const;
  OdTvColorDef getFaceColor(OdInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Faces normals management
  */
  OdTvResult setFaceNormalsViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indFaces, const OdTvVector* vectors);
  OdTvResult setFaceNormalsViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indFaces, const OdTvVector& vector);

  OdTvResult setFaceNormalsViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvVector& vector);
  OdTvResult setFaceNormalsViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvVector* vectors);

  OdTvResult getFaceNormalsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVectorArray& vectors) const;
  OdTvResult getFaceNormalsViaList(const OdInt32Array& indexes, OdTvVectorArray& vectors) const;
  OdTvVector getFaceNormal(OdInt32 ind, OdTvResult* rc = NULL) const;
  const OdTvVector3dArrayStorage& getFaceNormals() const { return m_faceNormals; }

  /**
  Faces visibility management
  */
  OdTvResult setFaceVisibilitiesViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indFaces, const OdTvVisibilityDef* visibles);
  OdTvResult setFaceVisibilitiesViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indFaces, const OdTvVisibilityDef& visible);

  OdTvResult setFaceVisibilitiesViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef* visibles);
  OdTvResult setFaceVisibilitiesViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef& visible);

  OdTvResult getFaceVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVisibilityDefArray& visibilities) const;
  OdTvResult getFaceVisibilitiesViaList(const OdInt32Array& indexes, OdTvVisibilityDefArray& visibilities) const;
  OdTvVisibilityDef getFaceVisibility(OdInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Faces layers management
  */
  OdTvResult setFaceLayersViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indFaces, const OdTvLayerDef* layers, OdTvDbDatabase* pDb);
  OdTvResult setFaceLayersViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indFaces, const OdTvLayerDef& layer, OdTvDbDatabase* pDb);

  OdTvResult setFaceLayersViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvLayerDef* layers, OdTvDbDatabase* pDb);
  OdTvResult setFaceLayersViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvLayerDef& layer, OdTvDbDatabase* pDb);

  OdTvResult getFaceLayersViaRange(OdInt32 indStart, OdInt32 nCount, OdTvLayerDefArray& layers, OdTvDbDatabase* pDb) const;
  OdTvResult getFaceLayersViaList(const OdInt32Array& indexes, OdTvLayerDefArray& layers, OdTvDbDatabase* pDb) const;
  OdTvLayerDef getFaceLayer(OdInt32 ind, OdTvDbDatabase* pDb, OdTvResult* rc = NULL) const;

  /**
  Faces transparency management
  */
  OdTvResult setFaceTransparencyViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indFaces, const OdTvTransparencyDef* transparencies);
  OdTvResult setFaceTransparencyViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indFaces, const OdTvTransparencyDef& transparency);

  OdTvResult setFaceTransparencyViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvTransparencyDef* transparencies);
  OdTvResult setFaceTransparencyViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvTransparencyDef& transparency);

  OdTvResult getFaceTransparencyViaRange(OdInt32 indStart, OdInt32 nCount, OdTvTransparencyDefArray& transparencies) const;
  OdTvResult getFaceTransparencyViaList(const OdInt32Array& indFaces, OdTvTransparencyDefArray& transparencies) const;
  OdTvTransparencyDef getFaceTransparency(OdInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Faces materials management
  */
  OdTvResult setFaceMaterialsViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indFaces, const OdTvMaterialDef* materials, OdTvDbDatabase* pDb);
  OdTvResult setFaceMaterialsViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indFaces, const OdTvMaterialDef& material, OdTvDbDatabase* pDb);

  OdTvResult setFaceMaterialsViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvMaterialDef* materials, OdTvDbDatabase* pDb);
  OdTvResult setFaceMaterialsViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvMaterialDef& material, OdTvDbDatabase* pDb);

  OdTvResult getFaceMaterialsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvMaterialDefArray& materials, OdTvDbDatabase* pDb) const;
  OdTvResult getFaceMaterialsViaList(const OdInt32Array& indexes, OdTvMaterialDefArray& materials, OdTvDbDatabase* pDb) const;
  OdTvMaterialDef getFaceMaterial(OdInt32 ind, OdTvDbDatabase* pDb, OdTvResult* rc = NULL) const;

  /**
  Faces mappers management
  */
  OdTvResult setFaceMappersViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indFaces, const OdTvMapperDef* mappers);
  OdTvResult setFaceMappersViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indFaces, const OdTvMapperDef& mapper);

  OdTvResult setFaceMappersViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvMapperDef* mappers);
  OdTvResult setFaceMappersViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvMapperDef& mapper);

  OdTvResult getFaceMappersViaRange(OdInt32 indStart, OdInt32 nCount, OdTvMapperDefArray& mappers) const;
  OdTvResult getFaceMappersViaList(const OdInt32Array& indexes, OdTvMapperDefArray& mappers) const;
  OdTvMapperDef getFaceMapper(OdInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Faces fill origins managment
  */
  OdTvResult setFaceFillOriginsViaList(OdUInt32 nSize, OdInt nCount, const OdInt32* indFaces, const OdTvPoint2d* origins);
  OdTvResult setFaceFillOriginsViaList(OdUInt32 nSize, OdInt nCount, const OdInt32* indFaces, const OdTvPoint2d& origin);

  OdTvResult setFaceFillOriginsViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvPoint2d* origins);
  OdTvResult setFaceFillOriginsViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvPoint2d& origin);

  OdTvResult getFaceFillOriginsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvPoint2dArray& origins) const;
  OdTvResult getFaceFillOriginsViaList(const OdInt32Array& indexes, OdTvPoint2dArray& origins) const;
  OdTvPoint2d getFaceFillOrigin(OdInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Faces fill directions managment
  */
  OdTvResult setFaceFillDirectionsViaList(OdUInt32 nSize, OdInt nCount, const OdInt32* indFaces, const OdTvVector2d* directions);
  OdTvResult setFaceFillDirectionsViaList(OdUInt32 nSize, OdInt nCount, const OdInt32* indFaces, const OdTvVector2d& direction);

  OdTvResult setFaceFillDirectionsViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvVector2d* directions);
  OdTvResult setFaceFillDirectionsViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvVector2d& direction);

  OdTvResult getFaceFillDirectionsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVector2dArray& directions) const;
  OdTvResult getFaceFillDirectionsViaList(const OdInt32Array& indexes, OdTvVector2dArray& directions) const;
  OdTvVector2d getFaceFillDirection(OdInt32 ind, OdTvResult* rc = NULL) const;


  /** \details
  Check if faces can be selected
  */
  bool isFacesSelectable(OdTvResult* rc = NULL) const;

  //**************************************************************************************
  // Group of the methods for managing the properties of the edges
  //**************************************************************************************

  /**
  Edges colors management
  */
  OdTvResult setEdgeColorsViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indEdges, const OdTvColorDef* colors);
  OdTvResult setEdgeColorsViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indEdges, const OdTvColorDef& color);

  OdTvResult setEdgeColorsViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvColorDef& color);
  OdTvResult setEdgeColorsViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvColorDef* colors);

  OdTvResult getEdgeColorsViaList(const OdInt32Array& indexes, OdTvColorDefArray& colors) const;
  OdTvResult getEdgeColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvColorDefArray& colors) const;
  OdTvColorDef getEdgeColor(OdUInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Edges visibilities management
  */
  OdTvResult setEdgeVisibilitiesViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indEdges, const OdTvVisibilityDef* visibilities);
  OdTvResult setEdgeVisibilitiesViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indEdges, const OdTvVisibilityDef& visibility);

  OdTvResult setEdgeVisibilitiesViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef& visibility);
  OdTvResult setEdgeVisibilitiesViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef* visibilities);

  OdTvResult getEdgeVisibilitiesViaList(const OdInt32Array& indexes, OdTvVisibilityDefArray& visibilities) const;
  OdTvResult getEdgeVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVisibilityDefArray& visibilities) const;
  OdTvVisibilityDef getEdgeVisibility(OdUInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Edges linetypes management
  */
  OdTvResult setEdgeLinetypesViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indEdges, const OdTvLinetypeDef* linetypes, OdTvDbDatabase* pDb);
  OdTvResult setEdgeLinetypesViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indEdges, const OdTvLinetypeDef& linetype, OdTvDbDatabase* pDb);

  OdTvResult setEdgeLinetypesViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvLinetypeDef& linetype, OdTvDbDatabase* pDb);
  OdTvResult setEdgeLinetypesViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvLinetypeDef* linetypes, OdTvDbDatabase* pDb);

  OdTvResult getEdgeLinetypesViaList(const OdInt32Array& indexes, OdTvLinetypeDefArray& linetypes, OdTvDbDatabase* pDb) const;
  OdTvResult getEdgeLinetypesViaRange(OdInt32 indStart, OdInt32 nCount, OdTvLinetypeDefArray& linetypes, OdTvDbDatabase* pDb) const;
  OdTvLinetypeDef getEdgeLinetype(OdUInt32 ind, OdTvDbDatabase* pDb, OdTvResult* rc = NULL) const;

  /**
  Edges layers management
  */
  OdTvResult setEdgeLayersViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indEdges, const OdTvLayerDef* layers, OdTvDbDatabase* pDb);
  OdTvResult setEdgeLayersViaList(OdUInt32 nSize, OdInt32 nCount, const OdInt32* indEdges, const OdTvLayerDef& layer, OdTvDbDatabase* pDb);

  OdTvResult setEdgeLayersViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvLayerDef& layer, OdTvDbDatabase* pDb);
  OdTvResult setEdgeLayersViaRange(OdUInt32 nSize, OdInt32 indStart, OdInt32 nCount, const OdTvLayerDef* layers, OdTvDbDatabase* pDb);

  OdTvResult getEdgeLayersViaList(const OdInt32Array& indexes, OdTvLayerDefArray& layers, OdTvDbDatabase* pDb) const;
  OdTvResult getEdgeLayersViaRange(OdInt32 indStart, OdInt32 nCount, OdTvLayerDefArray& layers, OdTvDbDatabase* pDb) const;
  OdTvLayerDef getEdgeLayer(OdUInt32 ind, OdTvDbDatabase* pDb, OdTvResult* rc = NULL) const;

  /** \details
  Check if edges can be selected
  */
  bool isEdgesSelectable(OdTvResult* rc = NULL) const;

  //Hatch pattern fill
  OdTvResult setHatchPattern(const OdTvHatchPatternDef& def);
  OdTvHatchPatternDef getHatchPattern(OdTvResult* rc = NULL) const;
  const OdGiFill* hatchPattern() const;
  virtual OdUInt64 getObjectSize() const;

  /**
  Vertices visibility
  */
  OdTvResult setOverrideVerticesColor(bool bOverride, const OdTvRGBColorDef& color);
  OdTvRGBColorDef getOverrideVerticesColor(bool& bOverride, OdTvResult* rc = NULL) const;

  OdTvResult setShowVertices(bool bShow, OdInt32 verticesSize = 10);
  bool getShowVertices(OdInt32& verticesSize, OdTvResult* rc = NULL) const;

  OdTvResult setShowOnlyVertices(bool bShowOnly);
  bool getShowOnlyVertices(OdTvResult* rc = NULL) const;

private:

  // vertex specific routines
  void calculateVertexColors(const OdTvPointArray& vertices, const OdInt32Array& faces, const OdTvEntityImpl* pParentEntity, OdGiWorldDraw* pWorldDraw, OdTvGeometryDataTraits* pLocalTraits);
  void calculateVertexNormals(const OdTvPointArray& vertices, const OdInt32Array& faces);
  void affectVertexColors(OdTvCmEntityColor& color, OdTvCmEntityColor& blockRefColor, OdDbStub* layerdbId, OdGiWorldDraw* pWorldDraw);

  // faces specific routines
  void calculateFaceColors(OdUInt32 nFaces, const OdTvEntityImpl* pParentEntity, OdGiWorldDraw* pWorldDraw, OdTvGeometryDataTraits* pLocalTraits);
  void calculateFaceNormals(const OdTvPointArray& vertices, const OdInt32Array& faces);
  void calculateFaceVisibilities(OdUInt32 nFaces, const OdTvEntityImpl* pParentEntity, OdGiWorldDraw* pWorldDraw, OdTvGeometryDataTraits* pLocalTraits);
  void calculateFaceLayers(OdUInt32 nFaces, const OdTvEntityImpl* pParentEntity, OdGiWorldDraw* pWorldDraw, OdTvGeometryDataTraits* pLocalTraits);
  void calculateFaceTransparency(OdUInt32 nFaces, const OdTvEntityImpl* pParentEntity, OdGiWorldDraw* pWorldDraw, OdTvGeometryDataTraits* pLocalTraits);

  // edge specific routines
  void calculateEdgeColors(OdUInt32 nEdges, const OdInt32Array& faces, const OdTvEntityImpl* pParentEntity, OdGiWorldDraw* pWorldDraw, OdTvGeometryDataTraits* pLocalTraits);
  void calculateEdgeVisibilities(OdUInt32 nEdges, const OdInt32Array& faces, const OdTvEntityImpl* pParentEntity, OdTvGeometryDataTraits* pLocalTraits);
  void calculateEdgeLinetypes(OdUInt32 nEdges, const OdTvEntityImpl* pParentEntity, OdGiWorldDraw* pWorldDraw, OdTvGeometryDataTraits* pLocalTraits);
  void calculateEdgeLayers(OdUInt32 nEdges, const OdInt32Array& faces, const OdTvEntityImpl* pParentEntity, OdGiWorldDraw* pWorldDraw, OdTvGeometryDataTraits* pLocalTraits);

  // calculate index for sub geometry type
  bool calculateIndex(const OdGsMarker& marker, const OdDb::SubentType& type, OdInt64& subGeomId, OdUInt32 elements) const;
  // calculate marker for index and sub geometry type
  bool calculateMarker(OdGsMarker& marker, const OdDb::SubentType& type, const OdInt64& subGeomId) const;
  // calculate markers for indexes and sub geometry type
  bool calculateMarkers(OdArray< OdGsMarker >& markers, const OdDb::SubentType& type, const OdUInt32Array& subGeomIds) const;

public:

  //Additional data for vertex
  OdTvColorArrayStorage          m_vertexColors;
  OdGiOrientationType            m_vertexOrientationType;
  OdTvVector3dArrayStorage       m_vertexNormals;
  OdTvPoint2dAs3dArrayStorage    m_vertexMappingCoords;
  OdGsMarkerArray                m_vertexMarkers;      //not need save in file

  //Additional data for faces
  OdTvColorArrayStorage          m_facesColors;
  OdTvVector3dArrayStorage       m_faceNormals;
  OdTvUInt8ArrayStorage          m_facesVisibility;
  OdTvStubArrayStorage           m_facesLayers;
  OdTvTransparencyArrayStorage   m_facesTransparency;
  OdTvStubArrayStorage           m_facesMaterials;
  OdGiMapperArrayStorage         m_facesMappers;
  OdGsMarkerArray                m_facesMarkers;      //not need save in file
  OdTvPoint2dArrayStorage        m_faceFillOrigins;
  OdTvVector2dArrayStorage       m_faceFillDirections;

  //Additional data for edges
  OdTvColorArrayStorage          m_edgesColors;
  OdTvUInt8ArrayStorage          m_edgesVisibility;
  OdTvStubArrayStorage           m_edgesLinetypes;
  OdTvStubArrayStorage           m_edgesLayers;
  OdGsMarkerArray                m_edgesMarkers;      //not need save in file

  //selectability data
  OdUInt8                        m_selectableFlags;
  OdGsMarker                     m_endMarker;
  OdGsMarker                     m_startMarker;

  //hatch pattern fill data
  OdGiHatchPatternPtr            m_pHatchPattern;

  // This flag is true if and only if the holder of this attribute is a (shell or mesh) and false for the case of (sphere and cylinder)
  bool                           m_bRaw3DGeometry;

  bool                           m_bShowVertices;
  OdInt32                        m_nVerticesSize;
  bool                           m_bShowOnlyVertices;
  bool                           m_bOverrideVerticesColor;
  OdTvRGBColorDef                m_overrideVerticesColor;

};

#include "TD_PackPop.h"

#endif // _ODTV_GEOMETRY3DATTRIBUTES_H_INCLUDED_

