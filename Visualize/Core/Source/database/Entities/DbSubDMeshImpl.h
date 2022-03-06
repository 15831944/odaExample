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

#ifndef _ODDBSUBDMESHIMPL_INCLUDED_
#define _ODDBSUBDMESHIMPL_INCLUDED_

#include "DbSystemInternals.h"
#include "DbSubDMesh.h"
#include "DbEntityImpl.h"
#include "DbSubDMeshEngine.h"

class OdTvDbSubDMeshImpl : public OdTvDbEntityImpl
{
  static OdTvDbSubDMeshImpl* getImpl(const OdTvDbSubDMesh *pObj)
  { return (OdTvDbSubDMeshImpl*)OdTvDbSystemInternals::getImpl(pObj);}

  bool getVertexData(OdUInt32 numVertexes, const OdCmEntityColor &color, OdGiVertexData &giVertexData,
                     OdCmEntityColorArray &entColors, OdGeVector3dArray &vertexNormals,
                     OdGePoint3dArray &texCoords) const;
  OdResult subWorldDrawViaShells(OdGiWorldDraw* pWd) const;
  OdResult subWorldDrawViaPolylines(OdGiWorldDraw* pWd) const;
  void getShellInfo(OdGiWorldDraw* pWd
                  , OdGePoint3dArray &vxs1
                  , OdInt32Array &faces1
                  , OdGiFaceData &FaceData
                  , SUBDENGINE::FaceData &faceData
                  , SUBDENGINE::CreaseInfo &newCreaseInfo) const;

protected:

  void fillFaceData(SUBDENGINE::FaceData &fd, OdGiSubEntityTraits &pTraits) const;
  void updateEdges();

private:
  enum BlendCreaseEnum
  {
    eTurnoff = 0,
    eTurnon = 1
  } ;

  class OverrideData
  {
  public:
    enum PropertyType
    {
      eColor = 0,
      eMaterial,
      eTransparency,
      eMaterialMapper,
    };
  private:
    PropertyType  m_Type;
    void         *m_pData;
    
  public:
    OverrideData() : m_Type(eColor), m_pData(0) {}
    OverrideData(const OverrideData& other) : m_Type(eColor), m_pData(0) { operator=(other); }

    bool isEmpty() const { return m_pData == 0 && m_Type != eMaterialMapper; }
    PropertyType type() const { return m_Type; }

    OdTvCmColor getColor() const { return *(OdTvCmColor*)m_pData; }
    OdTvDbObjectId getMaterial() const { return *(OdTvDbObjectId*)m_pData; }
    OdTvCmTransparency getTransparency() const { return *(OdTvCmTransparency*)m_pData; }
    OdGiMapper getMapper() const { return OdGiMapper(); }

    void setColor(const OdTvCmColor &c) { clearData(); m_pData = new OdTvCmColor(c); m_Type = eColor; }
    void setMaterial(const OdTvDbObjectId &c) { clearData(); m_pData = new OdTvDbObjectId(c); m_Type = eMaterial; }
    void setTransparency(const OdTvCmTransparency &c) { clearData(); m_pData = new OdTvCmTransparency(c); m_Type = eTransparency; }
    void setMapper(const OdGiMapper &) { m_Type = eMaterialMapper; }

    void clearData()
    {
      if (!isEmpty())
      {
        if (type() == eColor)
          delete (OdTvCmColor*)m_pData;
        else if (type() == eMaterial)
          delete (OdTvDbObjectId*)m_pData;
        else if (type() == eTransparency)
          delete (OdTvCmTransparency*)m_pData;
        m_Type = eColor; m_pData = 0;
      }
    }

    OverrideData& operator=(const OverrideData& other)
    {
      m_Type = other.m_Type;
      m_pData = NULL;
      if (!isEmpty())
      {
        switch (type())
        {
        case eColor:
          m_pData = new OdTvCmColor(*(OdTvCmColor*)other.m_pData); break;
        case eMaterial:
          m_pData = new OdTvDbObjectId(*(OdTvDbObjectId*)other.m_pData); break;
        case eTransparency:
          m_pData = new OdTvCmTransparency(*(OdTvCmTransparency*)other.m_pData); break;
        default:
          break;
        }
      }
      return *this;
    }

    ~OverrideData()
    {
      clearData();
    }
  };

  typedef OdArray<OverrideData> OdOverrideDataArray;

  struct OverrideElem
  {
    OdGsMarker          m_Marker;
    OdOverrideDataArray m_Data;
  };

  struct SubentityCache
  {
    OdUInt8                  m_nSubDlevel;
    OdUInt32                 m_nNumSubDEntities;
    bool                     m_bNumSubDEntities;
    OdGePoint3dArray         m_pEntities;
    bool                     m_bEntities;
    OdGeVector3dArray        m_VertexNormals;
    bool                     m_bVertexNormals;
    OdGeVector3dArray        m_SubDividedVertexNormals;
    bool                     m_bSubDividedVertexNormals;
    SubentityCache() :
      m_bNumSubDEntities(false),
      m_bEntities(false),
      m_nNumSubDEntities(0),
      m_nSubDlevel(0)
    {
      m_pEntities.clear();
    }
  };

  typedef OdArray<OverrideElem> OdOverrideArray;

private:

  mutable SubentityCache   m_VertexesCache;
  mutable SubentityCache   m_FacesCache;
  BlendCreaseEnum          m_BlendCrease;
  OdUInt8                  m_nSubDLevel;
  OdGePoint3dArray         m_Vertexes;
  OdInt32Array             m_Faces;
  OdInt32Array             m_Edges;
  OdDoubleArray            m_EdgeCrease;
  OdOverrideArray          m_Overrided;

  OdGePoint3dArray         m_VertexTextCoord;
  OdGeVector3dArray        m_VertexNormals;
  OdCmEntityColorArray     m_EntColors;
protected:
  void clear();

public:


  ODRX_HEAP_OPERATORS();  // ODRX_USING_HEAP_OPERATORS() causes mac compiler error

  OdTvDbSubDMeshImpl();

  bool isEmpty() const { return m_Vertexes.isEmpty(); }

  ///////////////////////////////////////////////////////////////////////////
  // Methods for OdTvDbSubDMesh
  ///////////////////////////////////////////////////////////////////////////
  //
  
  OdResult setSubDMesh (const OdGePoint3dArray& vertexArray,
    const OdInt32Array& faceArray,
    OdInt32 subDLevel);

  OdResult setSphere (double radius,
    OdInt32 divAxis,
    OdInt32 divHeight,
    OdInt32 subDLevel);

  OdResult setCylinder (double majorRadius,
    double minorRadius,
    double height,
    OdInt32 divAxis,
    OdInt32 divHeight,
    OdInt32 divCap,
    OdInt32 subDLevel);

  OdResult setCone (double majorRadius,
    double minorRadius,
    double height,
    OdInt32 divAxis,
    OdInt32 divHeight,
    OdInt32 divCap,
    double radiusRatio,
    OdInt32 subDLevel);

  OdResult setTorus (double majorRadius,
    OdInt32 divSection,
    OdInt32 divSweepPath,
    double sectionRadiusRatio,
    double sectionRotate,
    OdInt32 subDLevel);

  OdResult setBox (double xLen,
    double yLen,
    double zLen,
    OdInt32 divX,
    OdInt32 divY,
    OdInt32 divZ,
    OdInt32 subDLevel);

  OdResult setWedge (double xLen,
    double yLen,
    double zLen,
    OdInt32 divLength,
    OdInt32 divWidth,
    OdInt32 divHeight,
    OdInt32 divSlope,
    OdInt32 divCap,
    OdInt32 subDLevel);

  OdResult setPyramid (double radius,
    double height,
    OdInt32 divLength,
    OdInt32 divHeight,
    OdInt32 divCap,
    OdInt32 nSides,
    double radiusRatio,
    OdInt32 subDLevel);

  OdResult subdDivideUp ();
  OdResult subdDivideDown ();
  OdResult subdRefine ();
  OdResult subdRefine (const OdTvDbFullSubentPathArray& subentPaths);
  OdResult subdLevel (OdInt32& result) const;

  OdResult splitFace (const OdDbSubentId& subentFaceId,
    const OdDbSubentId& subent0,
    const OdGePoint3d& point0,
    const OdDbSubentId& subent1,
    const OdGePoint3d& point1);

  OdResult extrudeFaces (const OdTvDbFullSubentPathArray& subentPaths,
    double length,
    const OdGeVector3d& dir,
    double taper);

  OdResult extrudeFaces (const OdTvDbFullSubentPathArray& subentPaths,
    const OdGePoint3dArray& alongPath,
    double taper);

  OdResult negate();

  OdResult isWatertight (bool& result) const;

  OdResult numOfFaces (OdInt32& result) const;
  OdResult numOfSubDividedFaces (OdInt32& result) const;
  OdResult numOfSubDividedFacesAt (const OdTvDbFullSubentPathArray& subentPaths, OdInt32& result) const;
  OdResult numOfVertices (OdInt32& result) const;
  OdResult numOfSubDividedVertices (OdInt32& result) const;
  OdResult numOfEdges (OdInt32& result) const;

  OdResult getVertices (OdGePoint3dArray& vertexArray) const;
  OdResult getEdgeArray (OdInt32Array& edgeArray) const;
  OdResult getFaceArray (OdInt32Array& faceArray) const;
  OdResult getNormalArray (OdGeVector3dArray& normalArray) const;

  OdResult getSubDividedVertices (OdGePoint3dArray& vertexArray) const;
  OdResult getSubDividedFaceArray (OdInt32Array& faceArray) const;
  OdResult getSubDividedNormalArray(OdGeVector3dArray& normalArray) const;

  OdResult getVertexAt (OdInt32 nIndex, OdGePoint3d& vertex) const;
  OdResult setVertexAt (OdInt32 nIndex, const OdGePoint3d& vertex);
  OdResult getVertexAt (const OdDbSubentId& id, OdGePoint3d& vertex) const;
  OdResult setVertexAt (const OdDbSubentId& id, const OdGePoint3d& vertex);

  OdResult getSubDividedVertexAt (OdInt32 nIndex, OdGePoint3d& vertex) const;
  OdResult getSubDividedVertexAt (const OdDbSubentId& id, OdGePoint3d& vertex) const;

  OdResult setCrease (double creaseVal);
  OdResult setCrease (const OdTvDbFullSubentPathArray& subentPaths, double creaseVal);
  OdResult getCrease (const OdTvDbFullSubentPathArray& subentPaths, OdDoubleArray& result) const;
  OdResult getCrease (const OdDbSubentId& id, double& result) const;

  OdResult getAdjacentSubentPath (const OdTvDbFullSubentPath& path,
    OdDb::SubentType type,
    OdTvDbFullSubentPathArray& subentPaths) const;

  OdResult getSubentPath (OdInt32 nIndex,
    OdDb::SubentType type,
    OdTvDbFullSubentPathArray& subentPaths) const;

  OdResult convertToSurface (bool bConvertAsSmooth, const OdDbSubentId& id, OdTvDbSurfacePtr& pSurface) const;
  OdResult convertToSurface (bool bConvertAsSmooth, bool optimize, OdTvDbSurfacePtr& pSurface) const;
  OdResult convertToSolid (bool bConvertAsSmooth, bool optimize, OdTvDb3dSolidPtr& pSolid) const;

  OdResult getSubentColor (const OdDbSubentId& id, OdTvCmColor& color) const;
  OdResult setSubentColor (const OdDbSubentId& id, const OdTvCmColor& color);
  OdResult getSubentMaterial (const OdDbSubentId& id, OdTvDbObjectId& material) const;
  OdResult setSubentMaterial (const OdDbSubentId& id, const OdTvDbObjectId& material);
  OdResult getSubentMaterialMapper (const OdDbSubentId& id, OdGiMapper& mapper) const;
  OdResult setSubentMaterialMapper (const OdDbSubentId& id, const OdGiMapper& mapper);

  OdResult getFacePlane (const OdDbSubentId& id, OdGePlane& facePlane) const;

  OdResult computeVolume (double &retVolume) const;
  OdResult computeSurfaceArea (double &retSurfArea) const;
  OdResult computeRayIntersection(const OdGePoint3d &rayStart,
    const OdGeVector3d &rayDir,
    OdArray<OdDbSubentId> &retSubents,
    OdArray<double> &retIntersectDist,
    OdGePoint3dArray& retIntersectPoint) const;

  OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void decomposeForSave( OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  bool subWorldDraw(OdGiWorldDraw* pWd) const;

  OdResult subTransformBy(const OdGeMatrix3d& xfm);
  OdResult subGetGeomExtents(OdGeExtents3d& extents) const;

  OdResult getVertexNormalArray(OdGeVector3dArray& arrNorm) const;
  OdResult getVertexTextureArray(OdGePoint3dArray& arrPts) const;
  OdResult getVertexColorArray(OdCmEntityColorArray& arrColor) const;
  OdResult setVertexNormalArray(OdGeVector3dArray& arrNorm);
  OdResult setVertexTextureArray(OdGePoint3dArray& arrPts);
  OdResult setVertexColorArray(OdCmEntityColorArray& arrColor);
  OdResult clearVertexNormalArray();
  OdResult clearVertexTextureArray();
  OdResult clearVertexColorArray();

private:
  OdResult convertTo(bool bOneSubentity, const OdDbSubentId& id, bool bConvertAsSmooth, bool optimize, OdTvDbSurfacePtr& pSurface) const;
  void prepareConvData(SUBDENGINE::FaceData &fd, OdGePoint3dArray &newVertexes, OdInt32Array &newFaces, OdInt32Array &newEdges,
                      OdBoolArray &arFacesColors, OdBoolArray &arFacesMaterials) const;
  void prepareConvDataBySubEntityId(const OdDbSubentId id, SUBDENGINE::FaceData &fd, OdGePoint3dArray &newVertexes, OdInt32Array &newFaces, 
    OdInt32Array &newEdges, OdBoolArray&arFacesColors, OdBoolArray&arFaceMaterials) const;
  void calculateSubDividedEntities(OdGePoint3dArray &vertexArray, OdInt32Array &faceArray) const;
  void selectFaceBySubEntityId(const OdDbSubentId id, OdGePoint3dArray &newVertexes, OdInt32Array &newFaces,
    OdInt32Array &newEdges, OdDoubleArray &newEdgeCrease) const;
  void getAdjacentFacesForFace(OdTvDbFullSubentPathArray &pathArray, const OdInt32Array faces, const OdGsMarker faceIndex) const;
  void getEdgesOnTheFace(OdTvDbFullSubentPathArray &pathArray, const OdGsMarker faceIndex) const;
  void getVertexesOnTheFace(OdTvDbFullSubentPathArray &pathArray, const OdGsMarker faceIndex) const;
  void getEdgesConectedWithVertex(OdTvDbFullSubentPathArray &pathArray, const OdGsMarker vertexIndex) const;
  void getFacesConectedWithVertex(OdTvDbFullSubentPathArray &pathArray, const OdGsMarker vertexIndex) const;
  void getAdjacentEdgesForEdge(OdTvDbFullSubentPathArray &pathArray, const OdGsMarker edgeIndex) const;
  void getFacesIncludingEdge(OdTvDbFullSubentPathArray &pathArray, const OdGsMarker edgeIndex) const;
  void getVertexesOnEdge(OdTvDbFullSubentPathArray &pathArray, const OdGsMarker edgeIndex) const;
  void copyFaces(OdInt32Array faceIdexes, OdInt32Array &retFaces) const;
  void calculateSubDividedVertexNormals(OdGeVector3dArray &subDividedNormals, bool isSubDivided) const;
  friend class OdTvDbSubDMesh;
};

#endif // _ODDBSUBDMESHIMPL_INCLUDED_
