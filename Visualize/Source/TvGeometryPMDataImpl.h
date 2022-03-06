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
#ifndef _ODTV_ENTITYPROGRESSIVEMESHDATA_H_INCLUDED_
#define _ODTV_ENTITYPROGRESSIVEMESHDATA_H_INCLUDED_

#include "TD_PackPush.h"
#include "TvGeometryDataImpl.h"
#include "TvGeometryProgressiveMeshData.h"
#include "Gi/GiProgressiveMesh.h"
#include "TvFilerWrapper.h"

class OdTvPMDataExtractor : public OdGiDataExtractor
{
public:
  OdTvPMDataExtractor( OdTvCoreFilerWrapperPtr pFiler, OdUInt64 nStreamOffset );
  ~OdTvPMDataExtractor();
  virtual bool registerDataBegin( OdUInt8 dataId, OdUInt64 localOffset );
  virtual bool registerDataEnd( OdUInt8 dataId, OdUInt64 localOffset );
  virtual OdUInt64 tell();
  virtual bool beginExtraction( OdUInt8 dataId );
  virtual bool endExtraction( OdUInt8 dataId );
  virtual bool seekFromLocalOffset( OdUInt64 offset );
  virtual void extractBytes( void* buffer, OdUInt32 numBytes );

  void setFastMode( bool bFast );

protected:
  OdTvCoreFilerWrapperPtr m_pFiler;
  OdUInt64 m_nDataOffset;
  OdUInt64 m_nStreamOffset;
  OdUInt64 m_lastOffset;

  OdUInt32 m_bufferSize;
  OdStreamBufPtr m_pBuffer;
  bool m_isFastMode;
  void restoreStream();
};

class OdTvProgressiveMeshInterpolation : public OdGiProgressiveMeshAutoLODSelectCallback
{
public:
  OdTvProgressiveMeshInterpolation();
  ~OdTvProgressiveMeshInterpolation();
  OdUInt32 selectLOD( const OdGiProgressiveMesh* pPM, const OdGiViewport* pView, const OdGeMatrix3d* pModelToWorldTransform ) const;
  void setInterpolationCallback( OdTvCustomInterpolation* pCallback );
  OdTvCustomInterpolation* getInterpolationCallback() const;

  void initByArray( OdUInt32 nMin, OdUInt32 nMax, const OdUInt32Array& values );

  bool fillArray( OdUInt32 nMin, OdUInt32 nMax, OdUInt32 yMax );

  bool isArrayFilled() const { return !m_values.empty(); }

  void write( OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion() ) const;
  void read( OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion() );

  const OdUInt32Array& values() const { return m_values; }
  OdUInt32 getMin() const { return m_nMin; }
  OdUInt32 getMax() const { return m_nMax; }

protected:

  OdUInt32 fromArray( OdUInt32 x, OdUInt32 yMax ) const;

  OdTvCustomInterpolation* m_pCallback;
  OdUInt32Array m_values;
  OdUInt32 m_nMin;
  OdUInt32 m_nMax;
};

class OdTvProgressiveMeshDataImpl : public OdTvGeometryDataImpl
{
public:
  OdTvProgressiveMeshDataImpl();
  OdTvProgressiveMeshDataImpl(OdInt32 nPoints, const OdTvPoint* points, OdInt32 faceListSize, const OdInt32* faces);

  ~OdTvProgressiveMeshDataImpl();

  // Inherited via OdTvGeometryDataImpl
  virtual TvGeometryType entityGeometryDataType() const;

  virtual OdTvResult buildProgressiveMesh( OdUInt32 nMinPoints = 0, OdUInt32 nMinFaces = 0 );

  virtual OdTvResult getParam(OdTvPointArray& verticesArray, OdInt32Array& faces) const;

  virtual OdTvResult setVertexNormalsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvVector* vectors);
  virtual OdTvResult setVertexNormalsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvVector& vector);
  virtual OdTvResult setVertexNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector& vector);
  virtual OdTvResult setVertexNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector* vectors);
  virtual OdTvResult getVertexNormalsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVectorArray& vectors) const;
  virtual OdTvResult getVertexNormalsViaList(const OdInt32Array& indVertices, OdTvVectorArray& vectors) const;
  virtual OdTvVector getVertexNormal(OdInt32 ind, OdTvResult* rc = NULL) const;

  virtual OdTvResult setVertexColorsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvRGBColorDef* colors);
  virtual OdTvResult setVertexColorsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvRGBColorDef& color);
  virtual OdTvResult setVertexColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef& color);
  virtual OdTvResult setVertexColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef* colors);
  virtual OdTvResult getVertexColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvRGBColorDefArray& colors) const;
  virtual OdTvResult getVertexColorsViaList(const OdInt32Array& indVertices, OdTvRGBColorDefArray& colors) const;
  virtual OdTvRGBColorDef getVertexColor(OdInt32 ind, OdTvResult* rc = NULL) const;

  virtual OdTvResult setVertexMappingCoordsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvPoint2d* mappingCoords);
  virtual OdTvResult setVertexMappingCoordsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvPoint2d& mappingCoord);
  virtual OdTvResult setVertexMappingCoordsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvPoint2d& mappingCoord);
  virtual OdTvResult setVertexMappingCoordsViaRange( OdInt32 indStart, OdInt32 nCount, const OdTvPoint2d* mappingCoords );
  virtual OdTvResult getVertexMappingCoordsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvPoint2dArray& mappingCoords) const;
  virtual OdTvResult getVertexMappingCoordsViaList(const OdInt32Array& indVert, OdTvPoint2dArray& mappingCoords) const;
  virtual OdTvPoint2d getVertexMappingCoord(OdInt32 ind, OdTvResult* rc = NULL) const;

  virtual OdTvResult setFaceColorsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvColorDef* colors);
  virtual OdTvResult setFaceColorsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvColorDef& color);
  virtual OdTvResult setFaceColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef& color);
  virtual OdTvResult setFaceColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef* colors);
  virtual OdTvResult getFaceColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvColorDefArray& colors) const;
  virtual OdTvResult getFaceColorsViaList(const OdInt32Array& indFaces, OdTvColorDefArray& colors) const;
  virtual OdTvColorDef getFaceColor(OdInt32 ind, OdTvResult* rc = NULL) const;

  virtual OdTvResult setFaceMaterialsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvMaterialDef* materials, OdTvDbDatabase* pDb);
  virtual OdTvResult setFaceMaterialsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvMaterialDef& material, OdTvDbDatabase* pDb);
  virtual OdTvResult setFaceMaterialsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMaterialDef* materials, OdTvDbDatabase* pDb);
  virtual OdTvResult setFaceMaterialsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMaterialDef& material, OdTvDbDatabase* pDb);
  virtual OdTvResult getFaceMaterialsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvMaterialDefArray& materials, OdTvDbDatabase* pDb) const;
  virtual OdTvResult getFaceMaterialsViaList(const OdInt32Array& indFaces, OdTvMaterialDefArray& materials, OdTvDbDatabase* pDb) const;
  virtual OdTvMaterialDef getFaceMaterial(OdInt32 ind, OdTvDbDatabase* pDb, OdTvResult* rc = NULL) const;

  virtual OdTvResult setEdgeVisibilitiesViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvVisibilityDef* visibilities);
  virtual OdTvResult setEdgeVisibilitiesViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvVisibilityDef& visibility);
  virtual OdTvResult setEdgeVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef& visibility);
  virtual OdTvResult setEdgeVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef* visibilities);
  virtual OdTvResult getEdgeVisibilitiesViaList(const OdInt32Array& indEdges, OdTvVisibilityDefArray& visibilities) const;
  virtual OdTvResult getEdgeVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVisibilityDefArray& visibilities) const;
  virtual OdTvVisibilityDef getEdgeVisibility(OdUInt32 ind, OdTvResult* rc = NULL) const;

  virtual void                                read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                                write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;

  virtual bool draw(OdGiWorldDraw * pWorldDraw, const OdTvEntityImpl * pParentEntitym, OdGsMarker & marker) const;

  virtual void drawView( OdGiViewportDraw* pViewportDraw, const OdTvEntityImpl* pParentEntity ) const;

  virtual void drawForMarkers(const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;

  virtual OdTvGeometryData::GeometryTypes getFirstColorGeomType() const;

  virtual OdUInt32 numLODs( OdTvResult* rc = NULL ) const;
  virtual OdUInt32 currentLOD( OdTvResult* rc = NULL ) const;
  virtual OdTvResult setLOD( OdUInt32 lod );

  virtual OdUInt32 numFaces( OdTvResult* rc = NULL ) const;
  virtual OdUInt32 numVertices( OdTvResult* rc = NULL ) const;

  bool getIgnoreFaceNormals( OdTvResult* rc = NULL ) const;
  OdTvResult setIgnoreFaceNormals( bool bIgnore );

  bool isProgressiveMeshGenerated( OdTvResult* rc = NULL ) const;

  virtual OdTvResult setAutoLODSelection( OdTvProgressiveMeshData::LODAutoSelectType AutoSelectType );
  virtual OdTvProgressiveMeshData::LODAutoSelectType getAutoLODSelection( OdTvResult* rc = NULL ) const;

  virtual OdTvResult getAutoLODSelectInterpolationThresholds( OdUInt32& nMin, OdUInt32& nMax ) const;
  virtual OdTvResult setAutoLODSelectInterpolationThresholds( OdUInt32 nMin, OdUInt32 nMax );

  virtual OdTvResult setAutoLODCustomInterpolation( OdTvCustomInterpolation* pInterpolation );
  virtual OdTvCustomInterpolation* getAutoLODCustomInterpolation( OdTvResult* rc = NULL ) const;

  virtual bool copyTo( OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity ) const;

  virtual bool isInPartialMode( OdTvResult* rc = NULL ) const;
  virtual OdTvResult endPartialMode();

private:
  mutable OdGiProgressiveMeshExPtr m_pPM;
  OdTvPointArray m_pts;
  OdInt32Array m_faces;
  OdTvVector3dArrayStorage       m_vertexNormals;
  OdTvColorArrayStorage          m_vertexColors;
  OdTvPoint2dAs3dArrayStorage    m_vertexMappingCoords;
  OdTvColorArrayStorage          m_facesColors;
  OdTvStubArrayStorage           m_facesMaterials;
  OdTvUInt8ArrayStorage          m_edgesVisibility;

  OdUInt8 m_pmFlags;

  enum ProgressiveMeshFlags
  {
    kIgnoreFaceNormals = 1,
    kAutoLODSelect_SQR = 2,
    kAutoLODSelect_SQRT = 4,
    kAutoLODSelect_Custom = 8
  };

  OdTvProgressiveMeshInterpolation* m_pInterpolationCallback;

  OdGiProgressiveMesh::ProgressiveMeshAutoSelectLOD toGiAutoSelectType() const;

  OdTvPMDataExtractor* m_pExtractor;

  OdDbHandle m_parentHandle;

public:
  void setParentHandle( OdDbHandle h ) { m_parentHandle = h; }
  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;
};

typedef OdTvSmartPtrInternal<OdTvProgressiveMeshDataImpl> OdTvProgressiveMeshDataImplPtr;


/** \details
  This is an wrapper of the interface class for OdTvGeometryData object.

  \remarks
  The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvProgressiveMeshDataWrapper : public OdTvProgressiveMeshData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvProgressiveMeshData)

protected:
  ODRX_HEAP_OPERATORS();

public:
  virtual OdTvResult buildProgressiveMesh( OdUInt32 nMinPoints = 0, OdUInt32 nMinFaces = 0 );

  virtual OdTvResult getParam(OdTvPointArray& verticesArray, OdInt32Array& faces) const;

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

  virtual OdTvResult setVertexMappingCoordsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvPoint2d* mappingCoords);
  virtual OdTvResult setVertexMappingCoordsViaList(const OdInt32Array indVertices, const OdTvPoint2dArray& mappingCoords);
  virtual OdTvResult setVertexMappingCoordsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvPoint2d& mappingCoord);
  virtual OdTvResult setVertexMappingCoordsViaList(const OdInt32Array indVertices, const OdTvPoint2d& mappingCoord);
  virtual OdTvResult setVertexMappingCoordsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvPoint2d& mappingCoord);
  virtual OdTvResult setVertexMappingCoordsViaRange(OdInt32 indStart, const OdTvPoint2dArray& mappingCoords);
  virtual OdTvResult setVertexMappingCoordsViaRange( OdInt32 indStart, OdInt32 nCount, const OdTvPoint2d* mappingCoords );
  virtual OdTvResult getVertexMappingCoordsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvPoint2dArray& mappingCoords) const;
  virtual OdTvResult getVertexMappingCoordsViaList(const OdInt32Array& indVert, OdTvPoint2dArray& mappingCoords) const;
  virtual OdTvPoint2d getVertexMappingCoord(OdInt32 ind, OdTvResult* rc = NULL) const;

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

  virtual OdUInt32 numLODs( OdTvResult* rc = NULL ) const;
  virtual OdUInt32 currentLOD( OdTvResult* rc = NULL ) const;
  virtual OdTvResult setLOD( OdUInt32 lod );

  virtual OdUInt32 numFaces( OdTvResult* rc = NULL ) const;
  virtual OdUInt32 numVertices( OdTvResult* rc = NULL ) const;

  virtual bool getIgnoreFaceNormals( OdTvResult* rc ) const;
  virtual OdTvResult setIgnoreFaceNormals( bool bIgnore );
  virtual bool isProgressiveMeshGenerated( OdTvResult* rc = NULL ) const;

  virtual OdTvResult setAutoLODSelection( OdTvProgressiveMeshData::LODAutoSelectType autoSelectType );
  virtual OdTvProgressiveMeshData::LODAutoSelectType getAutoLODSelection( OdTvResult* rc = NULL ) const;

  virtual OdTvResult getAutoLODSelectInterpolationThresholds( OdUInt32& nMin, OdUInt32& nMax ) const;
  virtual OdTvResult setAutoLODSelectInterpolationThresholds( OdUInt32 nMin, OdUInt32 nMax );

  virtual OdTvResult setAutoLODCustomInterpolation( OdTvCustomInterpolation* pInterpolation );
  virtual OdTvCustomInterpolation* getAutoLODCustomInterpolation( OdTvResult* rc = NULL ) const;

  virtual bool isInPartialMode( OdTvResult* rc = NULL ) const;
  virtual OdTvResult endPartialMode();
};

#endif //_ODTV_ENTITYPROGRESSIVEMESHDATA_H_INCLUDED_

