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

#ifndef _COLLADA_EXPORT_VIEW_INCLUDED_
#define _COLLADA_EXPORT_VIEW_INCLUDED_
#pragma once
#include "OdaCommon.h"
#include "OdError.h"
#include "Gi/GiRasterImage.h"
#include "Gi/GiDrawable.h"
#include "Gi/GiGeometrySimplifier.h"
#include "Gi/GiLightTraitsData.h"
#include "Gi/GiUtils.h"
#include "Gs/GsBaseVectorizer.h"
#include "Gs/GsBaseMaterialView.h"
#include "RxObjectImpl.h"
#include "RxDynamicModule.h"
#include "COLLADASWEffectProfile.h"
#include "LightExporter.h"


/** \details
  Provides a set of classes, structures and enumerations for exporting to Collada files.
*/
namespace TD_COLLADA_EXPORT
{
  /** Count of Collada entities. */
  static OdUInt64 iColladaEntCounter = 0;

  /** \details
    This structure implements the material data for exporting to Collada files.
  */
  struct MaterialData
  {
    /** Ambient color. */
    COLLADASW::Color ambientColor;
    /** Diffuse color. */
    COLLADASW::Color diffuseColor;
    /** Specular color. */
    COLLADASW::Color specularColor;
    /** Ambient color factor. */
    double           dAmbientColorFactor;
    /** Diffuse color factor. */
    double           dDiffuseColorFactor;
    /** Specular color factor. */
    double           dSpecularColorFactor;
    /** Availability of a diffuse texture. */
    bool             bDiffuseHasTexture;
    /** Availability of a specular texture. */
    bool             bSpecularHasTexture;
    /** Availability of an ambient channel. */
    bool             bAmbientChannelEnabled;
    /** Availability of a diffuse channel. */
    bool             bDiffuseChannelEnabled;
    /** Availability of a specular channel. */
    bool             bSpecularChannelEnabled;
    /** Diffuse file source. */
    OdString         sDiffuseFileSource;
    /** Specular file source. */
    OdString         sSpecularFileSource;
    /** Gloss factor. */
    double           dGlossFactor;
    /** Availability of an opacity channel. */
    bool             bOpacityChannelEnabled;
    /** Opacity percentage. */
    double           dOpacityPercentage;
    /** Availability of an opacity texture. */
    bool             bOpacityHasTexture;
    /** Opacity file source. */
    OdString         sOpacityFileSource;
    /** Availability of a reflection channel. */
    bool             bReflectionChannelEnabled;
    /** Reflection percentage. */
    double           dReflectionPercentage;
    /** Availability of a reflection texture. */
    bool             bReflectionHasTexture;
    /** Reflection file source. */
    OdString         sReflectionFileSource;
    /** Availability of a bump channel. */
    bool             bBumpChannelEnabled;
    /** Bump percentage. */
    double           dBumpPercentage;
    /** Availability of a bump texture. */
    bool             bBumpHasTexture;
    /** Availability of a bump file source. */
    OdString         sBumpFileSource;
    /** Availability of an emission channel. */
    bool             bEmissionChannelEnabled;
    /** Emission percentage. */
    double           dEmissionPercentage;
    /** Availability of an emission texture. */
    bool             bEmissionHasTexture;
    /** Emission file source. */
    OdString         sEmissionFileSource;
    /** Availbility of a refraction channel. */
    bool             bRefractionChannelEnabled;
    /** Refraction index. */
    double           dRefractionIndex;
    /** Availability of a refraction texture. */
    bool             bRefractionHasTexture;
    /** Refraction file source. */
    OdString         sRefractionFileSource;
    /** Translucence. */
    double           dTranslucence;

    /** \details
      Comparison operator for the MaterialData object.

      \returns
      A boolean value that indicates whether the input MaterialData is identical to this MaterialData.
    */
    bool operator ==(MaterialData& val) const
    {
      return bAmbientChannelEnabled == val.bAmbientChannelEnabled && (bAmbientChannelEnabled ? (ambientColor == val.ambientColor && OdEqual(dAmbientColorFactor, val.dAmbientColorFactor)) : true) &&
        bDiffuseChannelEnabled == val.bDiffuseChannelEnabled && (bDiffuseChannelEnabled ? (diffuseColor == val.diffuseColor && OdEqual(dDiffuseColorFactor, val.dDiffuseColorFactor) &&
        bDiffuseHasTexture == val.bDiffuseHasTexture && (bDiffuseHasTexture ? sDiffuseFileSource == val.sDiffuseFileSource : true)) : true) &&
        bSpecularChannelEnabled == val.bSpecularChannelEnabled && (bSpecularChannelEnabled ? (specularColor == val.specularColor &&
        OdEqual(dSpecularColorFactor, val.dSpecularColorFactor) && OdEqual(dGlossFactor, val.dGlossFactor) &&
        bSpecularHasTexture == val.bSpecularHasTexture && (bSpecularHasTexture ? sSpecularFileSource == val.sSpecularFileSource : true)) : true) &&
        bOpacityChannelEnabled == val.bOpacityChannelEnabled && (bOpacityChannelEnabled ? (OdEqual(dOpacityPercentage, val.dOpacityPercentage) &&
        bOpacityHasTexture == val.bOpacityHasTexture && (bOpacityHasTexture ? sOpacityFileSource == val.sOpacityFileSource : true)) : true) &&
        bReflectionChannelEnabled == val.bReflectionChannelEnabled && (bReflectionChannelEnabled ? (OdEqual(dReflectionPercentage, val.dReflectionPercentage) &&
        bReflectionHasTexture == val.bReflectionHasTexture && (bReflectionHasTexture ? sReflectionFileSource == val.sReflectionFileSource : true)) : true) &&
        bBumpChannelEnabled == val.bBumpChannelEnabled && (bBumpChannelEnabled ? (OdEqual(dBumpPercentage, val.dBumpPercentage) &&
        bBumpHasTexture == val.bBumpHasTexture && (bBumpHasTexture ? sBumpFileSource == val.sBumpFileSource : true)) : true) &&
        bRefractionChannelEnabled == val.bRefractionChannelEnabled && (bRefractionChannelEnabled ? (OdEqual(dRefractionIndex, val.dRefractionIndex) &&
        bRefractionHasTexture == val.bRefractionHasTexture && (bRefractionHasTexture ? sRefractionFileSource == val.sRefractionFileSource : true)) : true) &&
        bEmissionChannelEnabled == val.bEmissionChannelEnabled && (bEmissionChannelEnabled ? (OdEqual(dEmissionPercentage, val.dEmissionPercentage) &&
        bEmissionHasTexture == val.bEmissionHasTexture && (bEmissionHasTexture ? sEmissionFileSource == val.sEmissionFileSource : true)) : true) &&
        OdEqual(dTranslucence, val.dTranslucence);
    }

    /** \details
      Creates a new instance of a MaterialData object with the default parameters.
    */
    MaterialData() : dAmbientColorFactor(0.0), dDiffuseColorFactor(0.0), dSpecularColorFactor(0.0),
                     bDiffuseHasTexture(false), bSpecularHasTexture(false), bAmbientChannelEnabled(false),
                     bDiffuseChannelEnabled(false), bSpecularChannelEnabled(false), bOpacityChannelEnabled(false),
                     dOpacityPercentage(0.0), bOpacityHasTexture(false), bReflectionChannelEnabled(false),
                     dReflectionPercentage(0.0), bReflectionHasTexture(false), bBumpChannelEnabled(false),
                     dBumpPercentage(0.0), bBumpHasTexture(false), bEmissionChannelEnabled(false),
                     dEmissionPercentage(0.0), bEmissionHasTexture(false), bRefractionChannelEnabled(false),
                     dRefractionIndex(0.0), bRefractionHasTexture(false), dTranslucence(0.0), dGlossFactor(0.0) {}
  };

  /** \details
    Defines flags of the material.
  */
  enum Flags
  {
    /** Raster image. */
    kRasterImage    = 1,
    /** Raster image material. */
    kRasterImageMat = 2,
    /** Entity. */
    kAddEntity      = 4
  };

  /** \details
    This structure implements the material mapper for exporting to a Collada file.
  */
  struct ColladaMaterialMapper
  {
    /** Points of the texture coordinates. */
    OdGePoint2dArray   m_ptTextureCoordArr;
    /** Indexes of the texture coordinates. */
    OdUInt32Array      m_indTextureCoordArr;
  };

  /** \details
    This structure stores the entity data for exporting to a Collada file.
  */
  struct ColladaEntData
  {
    /** Array of the number of vertices on faces. */
    OdUInt64Array         m_numVtxOnFaceArr;
    /** Array of points. */
    OdGePoint3dArray      m_ptArr;
    /** Array of the points' indexes. */
    OdUInt32Array         m_indPtsArr;
    /** Array of the points' normals. */
    OdGeVector3dArray     m_normVtxArr;
    /** Array of the normals' indexes. */
    OdUInt32Array         m_indVtxNormArr;
    /** Array of the normals' indexes. */
    ColladaMaterialMapper m_pDiffuseMaterialMapperArr;
    /** Entity ID. */
    OdUInt64              m_iId;
    /** Index of the entity material. */
    unsigned int          m_iEntMaterial;
    /** Flag that states whether an entity is a polyline or a polygon. */
    bool m_bIsPolyline;

    /** \details
      Creates a new instance of a ColladaEntData object with the default parameters.
    */
    ColladaEntData() : m_iId(0), m_iEntMaterial(0), m_bIsPolyline(false) {}
  };

  /** \details
    This structure stores the material data for exporting to a Collada file.
  */
  struct ColladaMaterialData
  {
    /** Array of the material data. */
    OdArray<MaterialData>           m_matDataArr;
    /** Array of the material data IDs. */
    OdUInt64Array                   m_matIdArr;
  };

  typedef OdArray<ColladaEntData> ColladaEntDataArray;
  typedef OdArray<ColladaEntDataArray> EntityDataArray;

  /** \details
    This class implements the stub vectorize device for exporting to a Collada file.
  */
  class StubVectorizeDevice : public OdGsBaseVectorizeDevice
  {
  protected:
    ODRX_USING_HEAP_OPERATORS(OdGsBaseVectorizeDevice);
  public:

    /** \details
      Creates a new instance of a StubVectorizeDevice object with the default parameters.
    */
    StubVectorizeDevice() { }
    /** \details
      Destroys the instance of a StubVectorizeDevice.
    */
    ~StubVectorizeDevice() { }
  };  

  /** \details
    Fixes the color by ACI.
  
    \param ids [in] Input ODCOLORREF.
    \param color [in] Entity color.
    \returns Fixed OdCmEntityColor.
  */
  static OdCmEntityColor fixByACI(const ODCOLORREF *ids, const OdCmEntityColor &color)
  {
    if (color.isByACI() || color.isByDgnIndex())
    {
      return OdCmEntityColor(ODGETRED(ids[color.colorIndex()]), ODGETGREEN(ids[color.colorIndex()]), ODGETBLUE(ids[color.colorIndex()]));
    }
    else if (!color.isByColor())
    {
      return OdCmEntityColor(0, 0, 0);
    }
    return color;
  }

  /** \details
    This class implements the Collada output.
  */
  class OdColladaOut : public OdGsBaseMaterialView, 
                       public OdGiGeometrySimplifier
  {
    /** Array of texture points. */
    OdGePoint2dArray      m_texCoordsArray;

    /** Pointer on the array of array entity data. */
    EntityDataArray*      m_pEntityDataArr;
    /** Pointer on the material data. */
    ColladaMaterialData*  m_pColladaMaterialData;
    /** Pointer on the light exporter. */
    LightExporter*        m_pLightExp;

    /** Pointer on the array of entity data. */
    ColladaEntDataArray*  m_pCurrentColladaEntDataArr;
    /** Pointer on the array of array entity data. */
    ColladaEntData*       m_pCurrentColladaEntData;
    /** Index of the current material. */
    unsigned int          m_iCurMaterial;
    /** Flags for the raster material. */
    OdUInt32              m_flags;
    /** Counter of lights. */
    unsigned int          m_iLightCounter;

    /** Temporary index. */
    unsigned int          iTmpIndex;
    /** Count of the points in the array. */
    OdInt32               m_iPtArrSize;
    /** Matrix for 3D transformation. */
    OdGeMatrix3d          m_matTransform;
    /** Map for the deviations. */
    const std::map<OdDbStub*, double>* m_pMapDeviations;
    /** Flag that indicates whether to export wire entities (as lines). */
    bool m_bExportWires;
    /** Deviation stack. */
    OdArray<double>       m_arrDeviationStack;

    /** \details
      Adds ColladaEntData to the array of entities with the current material.
    */
    void addColladaEntData();

  protected:
    OdGiMapperItemPtr setMapper(const OdGePoint3d& origin, const OdGeVector3d& u, const OdGeVector3d& v, const OdGiRasterImage* pImage);

    void triangleOut(const OdInt32* p3Vertices, const OdGeVector3d* pNormal);

    void fillCache(OdUInt64 matId, const MaterialData& matData, unsigned int iStartFind);
    void fillMaterialCache(MaterialData& mData, const OdGiMaterialTraitsData &materialData);
    OdGiMaterialItemPtr fillMaterialCache(OdGiMaterialItemPtr prevCache, OdDbStub* materialId, const OdGiMaterialTraitsData & materialData) ODRX_OVERRIDE;

    void polylineOut(OdInt32 numPoints, const OdGePoint3d* vertexList) ODRX_OVERRIDE;

    void circle(const OdGePoint3d& center, double radius, const OdGeVector3d& normal) ODRX_OVERRIDE;
    void circle(const OdGePoint3d& firstPoint, const OdGePoint3d& secondPoint, const OdGePoint3d& thirdPoint) ODRX_OVERRIDE;

    void circularArc(const OdGePoint3d& center, double radius, const OdGeVector3d& normal, const OdGeVector3d& startVector,
                     double sweepAngle, OdGiArcType arcType) ODRX_OVERRIDE;

    void circularArc(const OdGePoint3d& firstPoint, const OdGePoint3d& secondPoint, const OdGePoint3d& thirdPoint, OdGiArcType arcType) ODRX_OVERRIDE;

    void polyline(OdInt32 numVertices, const OdGePoint3d* vertexList, const OdGeVector3d* pNormal, OdGsMarker baseSubEntMarker) ODRX_OVERRIDE;

    void polygon(OdInt32 numVertices, const OdGePoint3d* vertexList) ODRX_OVERRIDE;

    void pline(const OdGiPolyline& polyline, OdUInt32 fromIndex = 0, OdUInt32 numSegs = 0) ODRX_OVERRIDE;

    void shape(const OdGePoint3d& position, const OdGeVector3d& normal, const OdGeVector3d& direction,
               int shapeNumber, const OdGiTextStyle* pTextStyle);

    void text(const OdGePoint3d& position, const OdGeVector3d& normal, const OdGeVector3d& direction,
              double height, double width, double oblique, const OdString& msg) ODRX_OVERRIDE;

    void text(const OdGePoint3d& position, const OdGeVector3d& normal, const OdGeVector3d& direction,
              const OdChar* msg, OdInt32 length, bool raw, const OdGiTextStyle* pTextStyle) ODRX_OVERRIDE;

    void xline(const OdGePoint3d& firstPoint, const OdGePoint3d& secondPoint) ODRX_OVERRIDE;
    void ray(const OdGePoint3d& basePoint, const OdGePoint3d& throughPoint) ODRX_OVERRIDE;

    void nurbs(const OdGeNurbCurve3d& nurbsCurve) ODRX_OVERRIDE;

    void ellipArc(const OdGeEllipArc3d& ellipArc, const OdGePoint3d* endPointsOverrides, OdGiArcType arcType) ODRX_OVERRIDE;

    void mesh(OdInt32 numRows, OdInt32 numColumns, const OdGePoint3d* vertexList, const OdGiEdgeData* pEdgeData,
              const OdGiFaceData* pFaceData, const OdGiVertexData* pVertexData) ODRX_OVERRIDE;

    void meshProc(OdInt32 numRows, OdInt32 numColumns, const OdGePoint3d* vertexList, const OdGiEdgeData* pEdgeData = 0,
                  const OdGiFaceData* pFaceData = 0, const OdGiVertexData* pVertexData = 0) ODRX_OVERRIDE;

    void worldLine(const OdGePoint3d points[2]) ODRX_OVERRIDE;

    void edge(const OdGiEdge2dArray& edges) ODRX_OVERRIDE;

    void shell(OdInt32 numVerts, const OdGePoint3d* pVertexList,
               OdInt32 faceListSize, const OdInt32* pFaceList, const OdGiEdgeData* pEdgeData,
               const OdGiFaceData* pFaceData, const OdGiVertexData* pVertexData) ODRX_OVERRIDE;

    void shellProc(OdInt32 numVertices, const OdGePoint3d* vertexList,
                   OdInt32 faceListSize, const OdInt32* faceList, const OdGiEdgeData* pEdgeData,
                   const OdGiFaceData* pFaceData, const OdGiVertexData* pVertexData) ODRX_OVERRIDE;

    void shellFaceOut(OdInt32 faceListSize, const OdInt32* pFaceList, const OdGeVector3d* pNormal) ODRX_OVERRIDE;

    void meshFaceOut(const OdInt32* faceList, const OdGeVector3d* pNormal) ODRX_OVERRIDE;

    void rasterImageDc(const OdGePoint3d& origin,
                       const OdGeVector3d& u,
                       const OdGeVector3d& v,
                       const OdGiRasterImage* pImage,
                       const OdGePoint2d* uvBoundary,
                       OdUInt32 numBoundPts,
                       bool transparency = false,
                       double brightness = 50.0,
                       double contrast = 50.0,
                       double fade = 0.0) ODRX_OVERRIDE;

    void image(const OdGiImageBGRA32& img,
               const OdGePoint3d& origin,
               const OdGeVector3d& uVec,
               const OdGeVector3d& vVec,
               OdGiRasterImage::TransparencyMode trpMode = OdGiRasterImage::kTransparency8Bit) ODRX_OVERRIDE;

    void processMaterialNode(OdDbStub *materialId, OdGsMaterialNode *pNode) ODRX_OVERRIDE;

    void initTexture(const OdGePoint3d& origin, const OdGeVector3d& u, const OdGeVector3d& v,
                     const OdGiRasterImage* pImage, bool transparency, double brightness, double contrast, double fade) ODRX_OVERRIDE;

    void uninitTexture() ODRX_OVERRIDE;

    void addColladaEntity();
  public:

    /** \details
      Creates a new instance of an OdColladaOut object with the default parameters.
    */
    OdColladaOut();

    /** \details
      Returns a pointer to the device.

      \returns StubVectorizeDevice if the pointer is not NULL, or a non-NULL pointer otherwise.
    */
    StubVectorizeDevice* device();

    /** \details
      Draws the specified drawable.
      
      \param drawableFlags [in]  Drawable flags.
      \param pDrawable [in]  Pointer to the drawable to draw.
      \returns The true value if drawable is successfully drawn, or false otherwise.
    */
    bool doDraw(OdUInt32 i, const OdGiDrawable* pDrawable) ODRX_OVERRIDE;

    /** \details
      Initializes OdColladaOut class by input parameters.
    
      \param pEntityDataArr [in] Pointer on array of array entity data.
      \param pColladaMaterialData [in]  Pointer to the material data.
      \param pLightExp [in]  Pointer to the light exporter.
      \param matTransform [in]  Matrix for 3D transformation.
      \param pMapDeviations [in]  Map for the deviations.
      \param exportWires [in]  Flag that indicates whether to export wire entities (as lines).
    */
    void init(EntityDataArray* pEntityDataArr, ColladaMaterialData* pColladaMaterialData, LightExporter* pLightExp,
      const OdGeMatrix3d& matTransform, const std::map<OdDbStub*, double>* pMapDeviations = NULL, bool exportWires = false);

    /** \details
      Begins view vectorization.
    */
    void beginViewVectorization() ODRX_OVERRIDE;

    /** \details
      Ends view vectorization.
    */
    void endViewVectorization() ODRX_OVERRIDE;

    /** \details
      Updates the viewport: loads viewport traits, updates extents (if necessary), displays associated drawables, and draws the viewport frame.
    */
    virtual void updateViewport() ODRX_OVERRIDE;

    /** \details
      Returns the recommended maximum deviation of the current vectorization for the specified point on the curve or surface being tesselated.

      \param deviationType [in]  Deviation type.
      \param pointOnCurve [in]  Point on the curve.
    
      \returns Recommended maximum deviation of the current vectorization as a double value.
    
      \remarks
      deviationType must be one of the following:
    
      <table>
      Name                       Value
      kOdGiMaxDevForCircle       0
      kOdGiMaxDevForCurve        1
      kOdGiMaxDevForBoundary     2
      kOdGiMaxDevForIsoline      3
      kOdGiMaxDevForFacet        4
      </table>
    */
    virtual double deviation(const OdGiDeviationType deviationType, const OdGePoint3d& pointOnCurve) const ODRX_OVERRIDE;

    /** \details
      Sets render mode for the view.

      \param mode [in]  Render mode.
    */
    void setMode(OdGsView::RenderMode mode) ODRX_OVERRIDE;
  };
}
#endif //_COLLADA_EXPORT_VIEW_INCLUDED_

