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

#include "PrcCommon.h"
#include "PrcExport.h"
#include "PrcCreateTopologyHelper.h"
#include "PrcCreateMeshHelper.h"
#include "PrcPolyBrepModel.h"
#include "PrcMaterialGeneric.h"
#include "PrcTextureApplication.h"
#include "PrcCoordinateSystem.h"
#include "PrcBrepData.h"
#include "PrcExportColor.h"
#include "PrcMaterialAndColorHelper.h"

#include "PrcSingleWireBody.h"
#include "PrcWireEdge.h"
#include "PrcPolyLine3d.h"
#include "PrcPointSet.h"

#include "Gi/GiGeometrySimplifier.h"
#include "Gs/GsBaseMaterialView.h"
#include "Gi/GiBrep.h"
#include "RxObjectImpl.h"
#include "ColorMapping.h"
#include "DbBaseHostAppServices.h"
#include "Ge/GeScale3d.h"
#include "Br/BrBrep.h"
#include "BrepBuilderFillerModule.h"
#include "BrepRenderer/BrepRendererImpl.h"
#include "Gs/GsVisualStyleProperties.h"

#define STL_USING_LIMITS
#define STL_USING_VECTOR
#define STL_USING_MAP
#define STL_USING_ALGORITHM
#define STL_USING_FUNCTIONAL
#include "OdaSTL.h"

// =========================================================
// helper functions and structures
// =========================================================
struct OdPLineInfo
{
  OdGePoint3dArray m_points;
  OdUInt32Array m_segment_lengths;
  OdUInt8Array m_colors; // triplets of r, g, b, alpha

  OdPLineInfo()
  {
    m_points.reserve(100);
    m_segment_lengths.reserve(10);
    m_colors.reserve(40);
  }

  void addColor(OdUInt8 r, OdUInt8 g, OdUInt8 b, OdUInt8 alpha)
  {
    m_colors.push_back(r);
    m_colors.push_back(g);
    m_colors.push_back(b);
    m_colors.push_back(alpha);
  }
};

struct OdExPrcMaterialCache : public OdRxObject
{
  OdGiMaterialTraitsData m_MaterialTraits;
};
typedef OdSmartPtr<OdExPrcMaterialCache> OdExPrcMaterialCachePtr;

OdPrcObjectId createLineStyleForPicture(const OdPrcPicturePtr &pPicture, OdPrcFileStructure &newStructure)
{
  // material generic
  OdPrcMaterialGenericPtr pMat = OdPrcMaterialGeneric::createObject();
  newStructure.addObject(pMat);
  OdPrcRgbColorArray &colorArr = newStructure.fileStructureGlobals().colors();
  OdPrcRgbColor color;
  color.set(1., 1., 1.);
  unsigned int nColorIndex;
  if (!colorArr.find(color, nColorIndex))
  {
    nColorIndex = colorArr.size();
    colorArr.append(color);
  }
  pMat->setAmbient(nColorIndex);
  pMat->setDiffuse(nColorIndex);
  pMat->setSpecular(nColorIndex);

  color.set(0., 0., 0.);
  if (!colorArr.find(color, nColorIndex))
  {
    nColorIndex = colorArr.size();
    colorArr.append(color);
  }
  pMat->setEmissive(nColorIndex);

  pMat->setShininess(0.85);
  pMat->setAmbientAlpha(1.);
  pMat->setDiffuseAlpha(1.);
  pMat->setEmissiveAlpha(1.);
  pMat->setSpecularAlpha(1.);
  newStructure.fileStructureGlobals().materials().push_back(pMat->id());

  // texture definition
  OdPrcTextureDefinitionPtr pTextureDef = OdPrcTextureDefinition::createObject();
  newStructure.addObject(pTextureDef);
  newStructure.fileStructureGlobals().textureDefinitions().push_back(pTextureDef->id());
  pTextureDef->setTextureDimension(2);
  pTextureDef->textureMappingType().eMappingType() = KEPRCTextureMappingType_Stored;
  pTextureDef->setTextureMappingAttributes(PRC_TEXTURE_MAPPING_DIFFUSE);
  pTextureDef->textureMappingAttributesIntensities().push_back(1.0f);
  pTextureDef->textureMappingAttributesComponents().push_back(PRC_TEXTURE_MAPPING_COMPONENTS_RGB);
  pTextureDef->setTextureFunction(KEPRCTextureFunction_Modulate);
  pTextureDef->setBlendSrcRgb(KEPRCTextureBlendParameter_Unknown);
  pTextureDef->setBlendSrcAlpha(KEPRCTextureBlendParameter_Unknown);
  pTextureDef->setTextureApplyingMode(PRC_TEXTURE_APPLYING_MODE_NONE);
  pTextureDef->setTextureWrappingModeS(KEPRCTextureWrappingMode_Repeat);
  pTextureDef->setTextureWrappingModeT(KEPRCTextureWrappingMode_Repeat);
  pTextureDef->removeTextureTransformation();
  pTextureDef->picture() = pPicture;

  // texture application
  OdPrcTextureApplicationPtr pTextureApp = OdPrcTextureApplication::createObject();
  newStructure.addObject(pTextureApp);
  pTextureApp->setTextureDefinitionID(pTextureDef->id());
  pTextureApp->setMaterialGenericID(pMat->id());

  return OdPrcCategory1LineStyle::createByMaterial(pTextureApp->id(), newStructure);
}

void fillPolyline(OdPrcFileStructure &newStructure, const OdGePoint3dArray &points, OdPrcExportContext &context, const DrawingColorNode &colorNode)
{
  // ensure valid topology
  ODA_ASSERT(newStructure.fileStructureGeometry().fileStructureExactGeometry().topologicalContext().size() > 0);

  // get wire body
  OdPrcTopoContextPtr newTopoContext = newStructure.fileStructureGeometry().fileStructureExactGeometry().topologicalContext().last();
  OdPrcSingleWireBodyPtr wireBody = newTopoContext->bodies().last().safeOpenObject(kForWrite);

  // fill params for SingleWireBody with PRC_TYPE_CRV_PolyLine
  // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
  OdPrcWireEdgePtr wEdge = OdPrcWireEdge::createObject();
  wireBody->wireEdge() = wEdge;

  // set curve
  OdPrcContentWireEdge &wContent = wEdge->contentWireEdge();
  OdPrcPolyLine3dPtr crvPolyLine = OdPrcPolyLine3d::createObject();
  {
    OdPrcContentCurve &crvContent = crvPolyLine->contentCurve();

    // - array of control points defining curve
    crvPolyLine->setPoints(points, true);
  }

  wContent.curve() = crvPolyLine;

  // color
  OdPrcObjectId lineStyleID = context.getLineStyleID(colorNode, newStructure);
  OdPrcPartDefinitionPtr pPD = newStructure.fileStructureTree().partDefinition().last().safeOpenObject(kForWrite);
  OdPrcRepresentationItemPtr item = pPD->representationItem().last().safeOpenObject(kForWrite);
  item->styleId() = lineStyleID;
  item->setBehaviourBitField(PRC_GRAPHICS_Show);
}

void fillPoint(const OdGePoint3d & pt, OdPrcFileStructure &newStructure, OdPrcPointSetPtr pPointSet, OdPrcExportContext &context, const DrawingColorNode &colorNode)
{
  pPointSet->point().push_back(pt);
  // color
  OdPrcObjectId lineStyleID = context.getLineStyleID(colorNode, newStructure);
  pPointSet->styleId() = lineStyleID;
  pPointSet->setBehaviourBitField(PRC_GRAPHICS_Show);
}

void setColorValues(OdUInt8 & r, OdUInt8 & g, OdUInt8 & b, const OdCmEntityColor & color, const OdGsBaseVectorizeDevice * pDevice)
{
  if (color.isByColor() == false)
  {
    ODCOLORREF rgb = pDevice->getColor(color.colorIndex());
    r = ODGETRED(rgb);
    g = ODGETGREEN(rgb);
    b = ODGETBLUE(rgb);
  }
  else
  {
    r = color.red();
    g = color.green();
    b = color.blue();
  }
}
// =========================================================
// helper functions and structures end
// =========================================================


class OdPrcExportVectorizeDevice : public OdGsBaseVectorizeDevice
{
protected:
  ODRX_USING_HEAP_OPERATORS(OdGsBaseVectorizeDevice);
public:
  OdPrcExportVectorizeDevice() { }
  ~OdPrcExportVectorizeDevice() { }
};


// =========================================================
// StubVectorizeView
// =========================================================
class StubVectorizeView : public OdGsBaseMaterialView /*OdGsBaseVectorizeViewDef*/, public OdGiGeometrySimplifier
{
public:
  StubVectorizeView() { }
  ~StubVectorizeView() { }
  
  OdPrcExportVectorizeDevice* device() { return static_cast<OdPrcExportVectorizeDevice*>(OdGsBaseVectorizeView::device()); }

  void loadViewport() { }
  void beginViewVectorization()
  {
    OdGsBaseVectorizer::beginViewVectorization();

    setEyeToOutputTransform(getEyeToWorldTransform());

    OdGiGeometrySimplifier::setDrawContext(OdGsBaseVectorizer::drawContext());
    output().setDestGeometry((OdGiGeometrySimplifier&)*this);
  }
  void endViewVectorization()
  {
    OdGsBaseVectorizer::endViewVectorization();
  }
};
//typedef OdSmartPtr<StubVectorizeView> StubVectorizeViewPtr;
// =========================================================
// StubVectorizeView end
// =========================================================


// =========================================================
// OdPrcExportVectorizeView
// =========================================================
class OdPrcExportVectorizeView : public StubVectorizeView
{
protected:
  float m_fEpsilon;
  OdPrcExportContext *m_context;
  const PDF2PRCExportParams *pParams;
  OdDbBaseDatabase      *m_pDb;

  TriangleInfoPtrArray   m_Data;

  OdUInt32               m_tmp_vertexIdx[3];
  OdPLineInfo            m_plines;

  OdUInt32               m_currFaceIdx;

  bool                   m_isTextured;
  OdGePoint2d            m_texCoords[3];

  //rasterImage export
  OdPrcObjectId          m_materialLineStyleID;
  OdGeMatrix3d           m_World2UV;

public:
  OdPrcExportVectorizeView()
    : m_context(NULL)
    , pParams(NULL)
    , m_currFaceIdx(0)
    , m_isTextured(false)
    , m_pDb(NULL)
    , m_fEpsilon(0.001f)
    , m_materialLineStyleID(NULL)
  {
    m_tmp_vertexIdx[0] = -1;
    m_tmp_vertexIdx[1] = -1;
    m_tmp_vertexIdx[2] = -1;
  }

public:
  void setEpsilon(float e)
  {
    m_fEpsilon = e;
  }

  void setContext(OdPrcExportContext *pContext)
  {
    m_context = pContext;
  }

  void setDatabase(OdDbBaseDatabase *pDb)
  {
    m_pDb = pDb;
  }

  void setExportParams(const PDF2PRCExportParams *params)
  {
    pParams = params;
  }

  void beginViewVectorization()
  {
    StubVectorizeView::beginViewVectorization();
    start();
  }

  void endViewVectorization()
  {
    finish();
    StubVectorizeView::endViewVectorization();
  }

  bool viewExtents(OdGeBoundBlock3d& extents) const
  {
    return false; // performance optimization. For dumping geometry zoom to extents is nonsensical.
  }

  virtual double deviation(const OdGiDeviationType deviationType, const OdGePoint3d& pointOnCurve) const
  {
    return pParams->m_arrDeviation[deviationType];
  }

  virtual void addTriangle(const TriangleInfoPtr &cell)
  {
    m_Data.append(cell);
  }
  
  // method from OdGiGeometrySimplifier
  virtual void polylineOut(OdInt32 nPoints, const OdGePoint3d* pVertexList)
  {
    // ensure valid input
    if ((nPoints < 2) || (!pVertexList))
    {
      return;
    }

    // fill polyline array with input data; single wire bodies would be created from it at finish
    m_plines.m_points.insert(m_plines.m_points.asArrayPtr() + m_plines.m_points.size(), pVertexList, pVertexList + nPoints);

    // save count of lines in polyline
    m_plines.m_segment_lengths.push_back(nPoints);

    // color
    OdUInt8 r, g, b;
    setColorValues(r, g, b, effectiveTraits().trueColor(), device());
    m_plines.addColor(r, g, b, effectiveTraits().transparency().alpha());
  }

  // method from OdGiGeometrySimplifier
  virtual void polygonOut(OdInt32 num, const OdGePoint3d* pPnts, const OdGeVector3d* pNormal)
  {
    if (num != 3)
    {
      OdGiGeometrySimplifier::polygonOut(num, pPnts, pNormal);
      return;
    }

    if (m_materialLineStyleID)
    {
      m_isTextured = true;
      for (OdUInt32 i = 0; i < 3; ++i)
      {
        OdGePoint3d pt = pPnts[i];
        pt.transformBy(m_World2UV);
        m_texCoords[i].set(pt.x, pt.y);
      }
    }
    TriangleInfoPtr cell;
    if (vertexData() && vertexData()->trueColors())
    {
      cell = new TriangleInfoColoredPoints();
      TriangleInfoColoredPoints *pTinfo3 = ((TriangleInfoColoredPoints*)cell.get());
      for (OdUInt32 i = 0; i < 3; ++i)
      {
        setColorValues(pTinfo3->red[i], pTinfo3->green[i], pTinfo3->blue[i], vertexData()->trueColors()[m_tmp_vertexIdx[i]], device());
      }
    }
    else if (m_isTextured)
    {
      cell = new TriangleInfoTextured();
      ((TriangleInfoTextured*)cell.get())->texCoords[0] = m_texCoords[0];
      ((TriangleInfoTextured*)cell.get())->texCoords[1] = m_texCoords[1];
      ((TriangleInfoTextured*)cell.get())->texCoords[2] = m_texCoords[2];
    }
    else
    {
      cell = new TriangleInfo();
    }

    cell->p1.set(pPnts[0]);
    cell->p2.set(pPnts[1]);
    cell->p3.set(pPnts[2]);
    if (cell->collinear(m_fEpsilon))
    {
      return;
    }

    if (effectiveTraits().trueColor().colorMethod() == OdCmEntityColor::kNone
      || effectiveTraits().trueColor().colorMethod() == OdCmEntityColor::kByColor)
    {
      cell->color = effectiveTraits().trueColor();
    }
    else
    {
      ODCOLORREF rgb = device()->getColor(effectiveTraits().trueColor().colorIndex());
      cell->color.setRGB(ODGETRED(rgb), ODGETGREEN(rgb), ODGETBLUE(rgb));
    }

    cell->alpha = effectiveTraits().transparency().alpha();

    if ((m_tmp_vertexIdx[0] != -1) && vertexData() && vertexData()->normals())
    {
      cell->vtx_normal[0] = vertexData()->normals()[m_tmp_vertexIdx[0]];
      cell->vtx_normal[1] = vertexData()->normals()[m_tmp_vertexIdx[1]];
      cell->vtx_normal[2] = vertexData()->normals()[m_tmp_vertexIdx[2]];
    }
    else
    {
      OdGeVector3d resultNormal;
      if (pNormal)
      {
        resultNormal = *pNormal;
      }
      else
      {
        resultNormal = (pPnts[1] - pPnts[0]).crossProduct(pPnts[2] - pPnts[0]);
      }

      cell->vtx_normal[0] = resultNormal;
      cell->vtx_normal[1] = resultNormal;
      cell->vtx_normal[2] = resultNormal;
    }

    {
      //points order correction
      OdGeVector3d normal(cell->vtx_normal[0] +cell->vtx_normal[1] + cell->vtx_normal[2]);
      
      OdGeError err;
      normal.normalize(OdGeContext::gTol, err);
      if (err != OdGe::kOk)
      { // Degenerate triangle
        return;
      }

      if (normal.dotProduct((pPnts[1] - pPnts[0]).crossProduct(pPnts[2] - pPnts[0])) < 0)
      {
        //swap all data between 2nd and 3rd points
        std::swap(cell->p2, cell->p3);
        std::swap(cell->vtx_normal[1], cell->vtx_normal[2]);

        if (vertexData() && vertexData()->trueColors())
        {
          TriangleInfoColoredPoints *pTinfo3 = ((TriangleInfoColoredPoints*)cell.get());
          std::swap(pTinfo3->red[1], pTinfo3->red[2]);
          std::swap(pTinfo3->green[1], pTinfo3->green[2]);
          std::swap(pTinfo3->blue[1], pTinfo3->blue[2]);
        }
        else if (m_isTextured)
        {
          TriangleInfoTextured* cellTextured = (TriangleInfoTextured*)cell.get();
          std::swap(cellTextured->texCoords[1], cellTextured->texCoords[2]);
        }
      }
    }

    cell->faceIdx = m_currFaceIdx;

    // material
    if (m_materialLineStyleID)
    {
      ((TriangleInfoTextured*)cell.get())->materialLineStyleID = m_materialLineStyleID;
    }
    else
    {
      OdDbStub *materialId = effectiveTraits().material();
      if (materialId)
      {
        cell->materialID = materialId;
      }
    }
    addTriangle(cell);
  }

  void generateMeshFaces(OdInt32 rows, OdInt32 columns, const OdGiFaceData* pFaceData)
  {
    OdGiGeometrySimplifier::generateMeshFaces(rows, columns, pFaceData);
    ++m_currFaceIdx;
  }

  virtual void generateShellFaces(OdInt32 faceListSize,
    const OdInt32* pFaceList,
    const OdGiEdgeData*,
    const OdGiFaceData* pFaceData)
  {
    OdGiGeometrySimplifier::generateShellFaces(faceListSize, pFaceList, NULL, pFaceData);
    ++m_currFaceIdx;
  }

  virtual void textProc(const OdGePoint3d& position,
    const OdGeVector3d& u,
    const OdGeVector3d& v,
    const OdChar* msg,
    OdInt32 length,
    bool raw,
    const OdGiTextStyle* pTextStyle,
    const OdGeVector3d* pExtrusion)
  {
    //TODO: export text as text (currently it exports as mesh)
    OdDbStub* pMaterial = m_effectiveEntityTraitsData.material();
    const OdGiMapper* pMapper = m_effectiveEntityTraitsData.mapper();
    OdDbStub* pMaterialEnt = m_entityTraitsData.material();
    const OdGiMapper* pMapperEnt = m_entityTraitsData.mapper();
    m_effectiveEntityTraitsData.setMaterial(NULL);
    m_effectiveEntityTraitsData.setMapper(NULL);
    m_entityTraitsData.setMaterial(NULL);
    m_entityTraitsData.setMapper(NULL);
    try
    {
      OdGiGeometrySimplifier::textProc(position, u, v, msg, length, raw, pTextStyle, pExtrusion);
    }
    catch (...)
    {
      m_effectiveEntityTraitsData.setMaterial(pMaterial);
      m_effectiveEntityTraitsData.setMapper(pMapper);
      m_entityTraitsData.setMaterial(pMaterialEnt);
      m_entityTraitsData.setMapper(pMapperEnt);
      throw;
    }
    m_effectiveEntityTraitsData.setMaterial(pMaterial);
    m_effectiveEntityTraitsData.setMapper(pMapper);
    m_entityTraitsData.setMaterial(pMaterialEnt);
    m_entityTraitsData.setMapper(pMapperEnt);
  }

  void initTexture(const OdGePoint3d& origin,
    const OdGeVector3d& u,
    const OdGeVector3d& v,
    const OdGiRasterImage* pImage,
    bool transparency,
    double brightness,
    double contrast,
    double fade)
  {
    //OdGiGeometrySimplifier::initTexture(origin, u, v, pImage, transparency, brightness, contrast, fade);

    OdGeMatrix3d world2uvInvU;
    OdGeVector3d normal = u.crossProduct(v);
    world2uvInvU.setCoordSystem(origin, u, v, normal);
    world2uvInvU.invert();
    OdGeMatrix3d uv2uvNorm;
    OdUInt32 iPixelWidth = pImage->pixelWidth();
    OdUInt32 iPixelHeight = pImage->pixelHeight();
    uv2uvNorm.setToScaling(OdGeScale3d(1.0 / iPixelWidth, 1.0 / iPixelHeight, 1.0));
    m_World2UV = uv2uvNorm * world2uvInvU;

    // create material line style for picture
    OdPrcFilePtr pPrcFile = m_context->getFile();
    OdPrcFileStructure & newStructure = *pPrcFile->fileStructures()[0].get();

    //put picture to the file
    OdPrcPicturePtr pPicture = OdPrcPicture::createByImage(pImage, newStructure);
    if (pPicture.isNull())
    {
      ODA_ASSERT(false);
      return;
    }
    m_materialLineStyleID = createLineStyleForPicture(pPicture, newStructure);
  }

  void uninitTexture()
  {
    //OdGiGeometrySimplifier::uninitTexture();
    m_materialLineStyleID = NULL;
  }

  // method from OdGiGeometrySimplifier
  virtual void triangleOut(const OdInt32* p3Vertices, const OdGeVector3d* pNormal)
  {
    m_tmp_vertexIdx[0] = p3Vertices[0];
    m_tmp_vertexIdx[1] = p3Vertices[1];
    m_tmp_vertexIdx[2] = p3Vertices[2];

    if (p3Vertices[0] == p3Vertices[1] || p3Vertices[1] == p3Vertices[2] || p3Vertices[0] == p3Vertices[2])
    {
      return;
    }

    // get triangle coordinates
    OdGePoint3d trgPoints[3] =
    {
      vertexDataList()[p3Vertices[0]],
      vertexDataList()[p3Vertices[1]],
      vertexDataList()[p3Vertices[2]]
    };

    m_isTextured = true;
    if (vertexData() && vertexData()->mappingCoords(OdGiVertexData::kAllChannels))
    {
      OdGePoint3d pTrianlgeMappingCoords[3];
      const OdGePoint3d* pMappingCoords = vertexData()->mappingCoords(OdGiVertexData::kAllChannels);
      for (OdUInt32 i = 0; i < 3; ++i)
      {
        pTrianlgeMappingCoords[i] = pMappingCoords[p3Vertices[i]];
        m_texCoords[i] = pTrianlgeMappingCoords[i].convert2d();
      }
      if (currentMapper().get() && currentMapper()->diffuseMapper().get())
      {
        currentMapper()->diffuseMapper()->mapPredefinedCoords(pTrianlgeMappingCoords, m_texCoords, 3);
      }
    }
    else if (isMaterialAvailable() && currentMaterial()->haveDiffuseTexture())
    {
      if (pNormal)
      {
        currentMapper()->diffuseMapper()->mapCoords(trgPoints, *pNormal, m_texCoords);
      }
      else
      {
        currentMapper()->diffuseMapper()->mapCoords(trgPoints, m_texCoords);
      }
    }
    else
    {
      m_isTextured = false;
    }

    OdGiGeometrySimplifier::triangleOut(p3Vertices, pNormal);

    m_tmp_vertexIdx[0] = -1;
    m_tmp_vertexIdx[1] = -1;
    m_tmp_vertexIdx[2] = -1;
  }

  virtual void start()
  {
    if (!m_context)
    {
      return;
    }
    if (!pParams)
    {
      throw OdError(eInvalidInput);
    }
    setByBlockTraits(pParams->m_pByBlockTraitsData);
  }

  virtual void finish()
  {
    if (!m_context)
    {
      return;
    }
    setByBlockTraits(NULL);
    
    // ensure has file
    if (m_context->getFile().isNull())
    {
      throw OdError(eCreateFailed);
    }
    if (!pParams)
    {
      throw OdError(eInvalidInput);
    }

    OdPrcFileStructurePtr pFS = m_context->getFile()->fileStructures().last();

    // create polylines
    OdUInt32 countSegments = m_plines.m_segment_lengths.size();
    if (countSegments != m_plines.m_colors.size()/4)
    {
      throw OdError(eInvalidInput);
    }

    if (countSegments > 0 || m_Data.size() > 0)
    {
      OdPrcProductOccurrencePtr pRootPO = pFS->fileStructureTree().internalData().getRootProductOccurrenceID().openObject(kForWrite);
      OdPrcProductOccurrencePtr pPO = createProductOccurrence(*pFS, *pRootPO);
      OdPrcTransformation3d prcMat;
      prcMat.set(pParams->m_bodyTransformationMatr);
      pPO->setLocation(&prcMat);
      OdPrcPartDefinitionPtr pPD = createPartDefinition(*pFS, *pPO);

      if (countSegments > 0)
      {
        OdPrcTopoContextPtr pTopoContext = createTopoContext(*pFS);
        OdUInt32 i = 0;
        for (OdUInt32 idx = 0; idx < countSegments; ++idx)
        {
          OdGePoint3dArray points;
          OdUInt32 uStart = i;
          i += m_plines.m_segment_lengths[idx];
          points.assign(m_plines.m_points.asArrayPtr() + uStart, m_plines.m_points.asArrayPtr() + i);

          DrawingColorNode colorNode;
          colorNode.drawingColor = OdCmEntityColor(m_plines.m_colors[idx * 4], m_plines.m_colors[idx * 4 + 1], m_plines.m_colors[idx * 4 + 2]);
          colorNode.transparency.setAlpha(m_plines.m_colors[idx * 4 + 3]);

          bool bIsPoint = true;
          for (OdUInt32 i = 0; i < points.size() - 1; ++i)
          {
            if (points[i] != points[i + 1])
            {
              bIsPoint = false;
              break;
            }
          }

          if (bIsPoint)
          {
            // create point topology
            OdPrcPointSetPtr pPointSet = createRI<OdPrcPointSet>(*pFS, *pPD);
            fillPoint(points[0], *pFS, pPointSet, *m_context, colorNode);
            pPD->boundingBox().box().addPoint(points[0]);
          }
          else
          {
            // create single wire topology
            OdPrcWireCurvePtr newCurve = createRI<OdPrcWireCurve>(*pFS, *pPD);
            createBody<OdPrcSingleWireBody>(*pFS, *pTopoContext, *newCurve);
            fillPolyline(*pFS, points, *m_context, colorNode);
            pPD->boundingBox().box().addPoints(points);
          }
        }
      }

      // create tessellation
      if (m_Data.size() > 0)
      {
        OdPrcPolyBrepModelPtr pRI = createRI<OdPrcPolyBrepModel>(*pFS, *pPD);
        pRI->tessellation() = fillTessellation(*pFS, m_Data, *m_context);

        // bounding box
        OdGeExtents3d extents;
        meshExtents(m_Data, extents);
        pPD->boundingBox().box().addExt(extents);
      }
    }
  }

  virtual OdGiMaterialItemPtr fillMaterialCache(OdGiMaterialItemPtr prevCache, OdDbStub *materialId, const OdGiMaterialTraitsData &materialData)
  {
    OdGiMaterialItemPtr pMatItem = OdGiMaterialItem::createObject();
    OdExPrcMaterialCachePtr pMatCache = OdRxObjectImpl<OdExPrcMaterialCache>::createObject();
    pMatCache->m_MaterialTraits = materialData;
    
    if (GETBIT(materialData.channelFlags(), OdGiMaterialTraits::kUseDiffuse))
    {
      OdGiMaterialMap diffuseMap;
      OdGiMaterialColor diffuseColor;
      materialData.diffuse(diffuseColor, diffuseMap);
      if (!pMatItem->createDiffuseTexture()->setGiMaterialTexture(NULL, OdGiMaterialTextureData::defaultTextureDataImplementationDesc(), giCtx(), diffuseMap))
      {
        // The texture can't be loaded, remove empty texture data.
        pMatItem->removeDiffuseTexture();
      }
    }
    
    pMatItem->setCachedData(pMatCache);
    return pMatItem;
  }

  virtual void renderMaterialCache(OdGiMaterialItemPtr pCache, OdDbStub *materialId)
  {
    //empty, invokes after reset material
  }

  struct OdGiMaterialTraits_Stub_PRC : public OdGiMaterialTraits_Stub
  {
    OdGiMaterialColor m_diffuseColor;
    OdGiMaterialMap   m_diffuseMap;

    virtual void setDiffuse(const OdGiMaterialColor & diffuseColor, const OdGiMaterialMap& diffuseMap)
    {
      m_diffuseColor = diffuseColor;
      m_diffuseMap = diffuseMap;
    }

    void diffuse(OdGiMaterialColor& diffuseColor, OdGiMaterialMap& diffuseMap) const
    {
      diffuseColor = m_diffuseColor;
      diffuseMap = m_diffuseMap;
    }
  };

  bool materialHasTexture(OdDbStub *materialId, const OdDbBaseDatabase *pDb)
  {
    if (NULL == materialId || NULL == pDb)
      return false;

    OdGiDrawablePtr pGiMaterial = OdDbBaseDatabasePEPtr(pDb)->openObject(materialId);

    OdGiMaterialTraits_Stub_PRC myTraits;

    OdUInt32 flags = pGiMaterial->setAttributes(&myTraits);

    if (myTraits.m_diffuseColor.method() == OdGiMaterialColor::kOverride)
    {
      if (!myTraits.m_diffuseMap.sourceFileName().isEmpty())
      {
        // try to find file
        OdString textureName = OdDbBaseDatabasePEPtr(pDb)->appServices((OdDbBaseDatabase*)pDb)->findFile(
          myTraits.m_diffuseMap.sourceFileName(), (OdDbBaseDatabase*)pDb, OdDbBaseHostAppServices::kTextureMapFile);
        return !textureName.isEmpty();
      }
      const OdGiMaterialTexturePtr pTexture = myTraits.m_diffuseMap.texture();
      return !pTexture.isNull() && pTexture->isKindOf(OdGiRasterImageTexture::desc()) && ((const OdGiRasterImageTexturePtr)pTexture)->rasterImage();
    }

    return false;
  }

  virtual bool brep(const OdGiBrep& giBrep)
  {
    if (!pParams->m_exportAsBrep || regenType() == kOdGiForExtents)
    {
      //return StubVectorizeView::brep(giBrep); 
      return false;
    }

    // Check material
    OdDbStub * pResMaterial =  m_effectiveEntityTraitsData.material();
    if (materialHasTexture(pResMaterial, giBrep.database()))
    {
      //return StubVectorizeView::brep(giBrep); 
      return false;
    }

    // Get brep
    OdBrBrep brep;
    giBrep.brep(brep);

    // Get extents
    OdGeExtents3d extents;
    OdBrepRendererImpl renderer;
    renderer.setBrep(brep);
    wrTriangulationParams trianParams;
    renderer.setTriangulationParams(&trianParams);
    renderer.getExtents(extents);
    if (!renderer.getExtents(extents))
    {
      //return StubVectorizeView::brep(giBrep); 
      return false;
    }

    // Brep Builder
    OdBrepBuilder bbuilder;
    if (createBrepBuilder(bbuilder, kOpenShell) != eOk)
    {
      //return StubVectorizeView::brep(giBrep);
      return false;
    }

    // Finish
    PrcMaterialAndColorHelper materialHelper(pParams, m_context, pResMaterial);
    OdBrepBuilderFiller BBFiller;
    BBFiller.params()
      .setupFor(m_context->getDatabase(), m_context->getFile())
      .setSkipNullSurface(true);
    if (BBFiller.initFrom(bbuilder, brep, &materialHelper) != eOk)
    {
      //return StubVectorizeView::brep(giBrep);
      return false;
    }

    // Add new PrcBrepModel
    OdPrcFileStructurePtr pFS = m_context->getFile()->fileStructures().last();
    OdPrcProductOccurrencePtr pRootPO = pFS->fileStructureTree().internalData().getRootProductOccurrenceID().openObject(kForWrite);
    OdPrcProductOccurrencePtr pPO = createProductOccurrence(*pFS, *pRootPO);
    OdPrcPartDefinitionPtr pPD = createPartDefinition(*pFS, *pPO);
    OdPrcTopoContextPtr pTopoContext = createTopoContext(*pFS);
    OdPrcBrepModelPtr pRI = createRI<OdPrcBrepModel>(*pFS, *pPD);
    pPD->boundingBox().box() = extents;

    // create brep body
    bbuilder.enableValidator(false);
    OdPrcBrepDataPtr brepData = bbuilder.finish();
    brepData->boundingBox().box() = extents;
    pFS->addObject(brepData);
    brepData->contentBody().setBoundingBoxBehaviour(2);
    // - set reference to this body in representation item
    pRI->setReferenceToBody(brepData);
    pTopoContext->appendBody(brepData->objectId());

    ODA_VERIFY(pRI->updateIsClosedFlag() == eOk);

    // transformation matrix
    OdGeMatrix3d brepMatrix;
    brep.getTransformation(brepMatrix);
    OdGeMatrix3d mtModelToWord = modelToWorldTransform(); 
    brepMatrix = pParams->m_bodyTransformationMatr * brepMatrix * mtModelToWord;
    if (brepMatrix != OdGeMatrix3d())
    {
      // - create representation item for transformation
      OdPrcCoordinateSystemPtr pCS = OdPrcCoordinateSystem::createObject();
      pFS->addObject(pCS);
      pCS->axisSet().set(brepMatrix);
      // - add this item to file structure globals
      pFS->fileStructureGlobals().coordinateSystem().push_back(pCS->objectId());
      pRI->localCoordinateSystemID() = pCS->objectId();
    }

    //save color or material
    //saveCurrentEntityMaterial(m_context, pParams, pDrawable);
    if (pResMaterial)
    {
      DrawingMaterialNode matNode;
      matNode.pMaterial = pResMaterial;
      matNode.drawingColor = m_effectiveEntityTraitsData.trueColor();// getCurrentEntityColor(params, pDrawable);
      matNode.transparency = m_effectiveEntityTraitsData.transparency(); // getCurrentEntityTransparency(params, pDrawable);

      //create material
      OdPrcObjectId lineStyleID = m_context->getLineStyleID(matNode, *pFS);
      pRI->styleId() = lineStyleID;
    }
    else
    {
      DrawingColorNode colorNode;
      colorNode.drawingColor = m_effectiveEntityTraitsData.trueColor(); //getCurrentEntityColor(params, pDrawable);
      colorNode.transparency = m_effectiveEntityTraitsData.transparency(); //getCurrentEntityTransparency(params, pDrawable);

      if (colorNode.drawingColor.isNone())
      {
        OdPrcObjectId lineStyleID = m_context->getLineStyleID(colorNode, *pFS, true);
        OdPrcPartDefinitionPtr pPD = pFS->fileStructureTree().partDefinition().last().safeOpenObject(kForWrite);
        OdPrcRepresentationItemPtr pRI = pPD->representationItem().last().safeOpenObject(kForWrite);
        pRI->styleId() = lineStyleID;
      }
    }

    return true;
  }
};

//typedef OdSmartPtr<OdPrcExportVectorizeView> OdPrcExportVectorizeViewPtr;
// =========================================================
// OdPrcExportVectorizeView end
// =========================================================


// =========================================================
// OdPrcExportDeviceModule
// =========================================================
class OdPrcExportDeviceModule : public OdGsBaseModule
{
  float m_fEpsilon;
  OdPrcExportContext *m_context;
  const PDF2PRCExportParams *pParams;
  OdDbBaseDatabase *m_pDb;
public:
  OdPrcExportDeviceModule()
    : m_fEpsilon(0.000001f)
    , m_context(NULL)
    , pParams(NULL)
    , m_pDb(NULL)
  {}
  void setEpsilon(float e)
  {
    m_fEpsilon = e;
  }

  void setContext(OdPrcExportContext *pContext)
  {
    m_context = pContext;
  }

  void setDatabase(OdDbBaseDatabase *pDb)
  {
    m_pDb = pDb;
  }

  void setExportParams(const PDF2PRCExportParams *params)
  {
    pParams = params;
  }
protected:
  OdSmartPtr<OdGsBaseVectorizeDevice> createDeviceObject()
  {
    return OdRxObjectImpl<OdPrcExportVectorizeDevice, OdGsBaseVectorizeDevice>::createObject();
  }

  OdSmartPtr<OdGsViewImpl> createViewObject()
  {
    OdSmartPtr<OdGsViewImpl> pCurView = OdRxObjectImpl<OdPrcExportVectorizeView, OdGsViewImpl>::createObject();
    ((OdPrcExportVectorizeView*)pCurView.get())->setContext(m_context);
    ((OdPrcExportVectorizeView*)pCurView.get())->setExportParams(pParams);
    ((OdPrcExportVectorizeView*)pCurView.get())->setDatabase(m_pDb);
    ((OdPrcExportVectorizeView*)pCurView.get())->setEpsilon(m_fEpsilon);
    return pCurView;
  }
  OdSmartPtr<OdGsBaseVectorizeDevice> createBitmapDeviceObject()
  {
    return OdSmartPtr<OdGsBaseVectorizeDevice>();
  }
  OdSmartPtr<OdGsViewImpl> createBitmapViewObject()
  {
    return OdSmartPtr<OdGsViewImpl>();
  }
};
typedef OdSmartPtr<OdPrcExportDeviceModule> OdPrcExportDeviceModulePtr;

ODRX_DEFINE_PSEUDO_STATIC_MODULE(OdPrcExportDeviceModule);
// =========================================================
// OdPrcExportDeviceModule end declaration
// =========================================================


// =========================================================
// PrcExport public interface
// =========================================================
OdResult exportMeshToPrc(const TriangleInfoPtrArray &mesh, OdRxObject *pContext)
{
  if (mesh.isEmpty())
  {
    return eInvalidInput;
  }

  // ensure has context
  ODA_ASSERT(pContext);
  OdPrcExportContextPtr ptrContext = pContext;
  if (ptrContext.isNull())
  {
    return eInvalidInput;
  }

  OdPrcFileStructurePtr pFS = ptrContext->getFile()->fileStructures().last();

  // export mesh into prc file
  OdPrcProductOccurrencePtr pRootPO = pFS->fileStructureTree().internalData().getRootProductOccurrenceID().openObject(kForWrite);

  OdPrcPartDefinitionPtr pPD;
  if (pRootPO->referencesOfProductOccurrence().getCorrespondingPartDefinition().isNull())
  {
    pPD = createPartDefinition(*pFS, *pRootPO);
  }
  else
  {
    pPD = pRootPO->referencesOfProductOccurrence().getCorrespondingPartDefinition().openObject(kForWrite);
  }

  OdPrcPolyBrepModelPtr pRI = createRI<OdPrcPolyBrepModel>(*pFS, *pPD);

  // create and fill tessellation
  pRI->tessellation() = fillTessellation(*pFS, mesh, *ptrContext);

  // bounding box
  OdGeExtents3d extents;
  meshExtents(mesh, extents);
  pPD->boundingBox().box() = extents;

  return eOk;
}

OdResult initDevice(OdGiDrawable* pEntity, OdDbBaseDatabase *pDb, OdGsDevicePtr &pDevice, OdGiDefaultContextPtr pCtx, OdPrcExportContext *pExContext, const PDF2PRCExportParams *params)
{
  OdDbBaseDatabasePEPtr pDbPE = OdDbBaseDatabasePE::cast(pDb);
  pDevice = pDbPE->setupActiveLayoutViews(pDevice, pCtx);
  if (pDevice->numViews() < 1)
  {
    ODA_VERIFY(pDevice->numViews() > 0);
    return eInvalidView;
  }

  for (int i = 0; i < pDevice->numViews(); ++i)
  {
    OdGsViewPtr pCurView = pDevice->viewAt(i);
    if (pCurView.isNull())
    {
      ODA_VERIFY(!pCurView.isNull());
      return eNullObjectPointer;
    }
    pCurView->eraseAll();
  }

  // add drawable entity into view
  OdGsViewPtr pCurView = pDevice->viewAt(params->m_viewIdx);
  if (pCurView.isNull())
  {
    //m_pHelperSpaceView, e.g. file "multipleviews.dwg"
    pCurView = pDevice->viewAt(0);
  }
  pCurView->add(pEntity, NULL);
  pCurView->setMode(OdGsView::kFlatShaded);
  return eOk;
}

// wraps run of vectorizer (overloaded for prc export)
OdResult exportMeshToPrc(const OdGiDrawable *pDrawable, const PDF2PRCExportParams &params, OdRxObject *pContext)
{
  // cast rxobject to context
  ODA_ASSERT(pContext);
  OdPrcExportContextPtr ptrContext = pContext;
  if (ptrContext.isNull())
  {
    return eInvalidInput;
  }
  OdDbBaseDatabase *pDb = ptrContext->getDatabase();

  // continue with export
  OdResult ret = eOk;
  try
  {
    odgsInitialize();

    OdPrcExportDeviceModulePtr pGsModule = ODRX_STATIC_MODULE_ENTRY_POINT(OdPrcExportDeviceModule)(OD_T("OdPrcExportDeviceModule"));

    pGsModule->setContext(ptrContext);
    pGsModule->setDatabase(pDb);
    pGsModule->setExportParams(&params);
    OdGeExtents3d extents;
    pDrawable->getGeomExtents(extents);
    if (extents.isValidExtents())
    {
      pGsModule->setEpsilon(std::numeric_limits<float>::epsilon() * extents.minPoint().distanceTo(extents.maxPoint()));
    }

    OdGiDefaultContextPtr pContext = OdDbBaseDatabasePEPtr(pDb)->createGiContext(pDb);
    OdGsDevicePtr pDevice = pGsModule->createDevice();

    OdRxVariantValue rxPallet = OdRxVariantValue(params.m_extraOptions->getAt("Pallet"));
    OdRxVariantValue rxNumColors = OdRxVariantValue(params.m_extraOptions->getAt("NumColors"));
    if (rxPallet.get() && rxNumColors.get())
    {
      OdUInt64 ppallete = rxPallet->getUInt64();
      OdUInt32 numColors = rxNumColors->getUInt32();
      pDevice->setLogicalPalette((OdUInt32*)ppallete, numColors);
    }
    else
    {
      pDevice->setLogicalPalette(::odcmAcadLightPalette(), 256);
      //pDevice->setLogicalPalette(::odcmAcadDarkPalette(), 256);
    }
    pDevice->setBackgroundColor(ODRGB(168, 168, 168));
    pContext->setPaletteBackground(ODRGB(255, 255, 255));

    if (initDevice((OdGiDrawable *)pDrawable, pDb, pDevice, pContext, ptrContext, &params) == eOk)
    {
      OdGsDCRect screenRect(OdGsDCPoint(0, 1000), OdGsDCPoint(1000, 0));
      pDevice->onSize(screenRect);
      pDevice->update();
    }
    else
    {
      ODA_VERIFY(!"Error! GsDevice was not initialised!");
    }

    pDevice.release();
    pContext.release();
    pGsModule.release();
    odgsUninitialize();
  }
  catch (OdError* e)
  {
    ret = e->code();
  }
  catch(...)
  {
    ret = eExtendedError;
  }

  // will return eOk if no exception is thrown by the vectorizer
  return ret;
}

// =========================================================
// PrcExport public interface end
// =========================================================
