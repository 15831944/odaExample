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
#include "PrcCreateTopologyHelper.h"
#include "PrcCreateMeshHelper.h"
#include "Prc3dTess.h"
#include "PrcPolyBrepModel.h"
#include "PrcExportContext.h"
#include "PrcExport.h"

struct PrcFaceKey
{
public:
  OdUInt32 m_face_index;
  TriangleInfo::TriangleType m_type;
  OdDbStub* m_materialID;
  OdCmEntityColor m_color;
  OdUInt8 m_alpha;
  PrcFaceKey(OdUInt32 face_index,
    TriangleInfo::TriangleType type,
    OdDbStub* materialID,
    OdCmEntityColor color,
    OdUInt8 alpha)
    :m_face_index(face_index), m_type(type), m_materialID(materialID), m_color(color), m_alpha(alpha)
  {}

  bool operator<(const PrcFaceKey& prcFaceKey) const
  {
    if (m_face_index < prcFaceKey.m_face_index)
    {
      return true;
    }
    if (m_face_index > prcFaceKey.m_face_index)
    {
      return false;
    }
    if (m_type < prcFaceKey.m_type)
    {
      return true;
    }
    if (m_type > prcFaceKey.m_type)
    {
      return false;
    }
    if (m_materialID < prcFaceKey.m_materialID)
    {
      return true;
    }
    if (m_materialID > prcFaceKey.m_materialID)
    {
      return false;
    }
    if (m_color.color() < prcFaceKey.m_color.color())
    {
      return true;
    }
    if (m_color.color() > prcFaceKey.m_color.color())
    {
      return false;
    }
    if (m_alpha < prcFaceKey.m_alpha)
    {
      return true;
    }
    return false;
  }
};

OdPrc3dTessPtr fillTessellation(OdPrcFileStructure &newStructure, const TriangleInfoPtrArray &mesh, OdPrcExportContext &prcContext)
{
  // general tess section
  OdPrcFileStructureTessellation &tess = newStructure.fileStructureTessellation();
  OdPrcBaseTessDataPtrArray &tessData = tess.tessellations();
  OdPrc3dTessPtr tess3d = OdPrc3dTess::createObject();
  tess3d->setIsCalculated(true);
  tess3d->setHasFaces(true);
  tess3d->setHasLoops(false);
  tess3d->setMustRecalculateNormals(false);
  tessData.append(tess3d);
  OdFloatArray &coordinates = tess3d->coordinates();
  coordinates.reserve(mesh.size() * 9);
  OdFloatArray &normal_coordinate = tess3d->normalCoordinate();
  normal_coordinate.reserve(mesh.size() * 9);
  OdUInt32Array &triangulated_index = tess3d->triangulatedIndex();
  triangulated_index.reserve(mesh.size() * 9);
  OdFloatArray &texture_coordinates = tess3d->textureCoordinate();
  texture_coordinates.reserve(mesh.size() * 6);

  // group Triangles by Faces and materials
  std::map <PrcFaceKey, TriangleInfoPtrArray> arrFaces;
  for (OdUInt32 idx = 0; idx < mesh.size(); ++idx)
  {
    const TriangleInfoPtr & triangleInfo = mesh[idx];
    PrcFaceKey key(triangleInfo->faceIdx, triangleInfo->getTriangleType(), triangleInfo->materialID, triangleInfo->color, triangleInfo->alpha);
    arrFaces[key].push_back(triangleInfo);
  }

  OdUInt32 uStartTriangulated = 0;
  tess3d->faceTessellation().reserve(unsigned(arrFaces.size()));
  for (std::map <PrcFaceKey, TriangleInfoPtrArray>::iterator it = arrFaces.begin(); it != arrFaces.end(); ++it)
  {
    tess3d->faceTessellation().append();
    OdPrcTessFace & curFace = tess3d->faceTessellation().last();
    const PrcFaceKey & prcFaceKey = it->first;
    const TriangleInfoPtrArray & arrTriangleInfo = it->second;
    curFace.setStartTriangulated(uStartTriangulated);
    curFace.setBehaviour(1);
    curFace.sizesTriangulated().push_back(arrTriangleInfo.size());

    if (prcFaceKey.m_type == TriangleInfo::kTriangleColored)
    {
      curFace.setUsedEntitiesFlag(PRC_FACETESSDATA_Triangle);
      curFace.setHasVertexColors(true);
      curFace.arrayRGBA().colors().reserve(arrTriangleInfo.size() * 9);
      for (OdUInt32 i = 0; i < arrTriangleInfo.size(); ++i)
      {
        const TriangleInfoColoredPoints *pTriangle = ((const TriangleInfoColoredPoints*)arrTriangleInfo[i].get());

        //points
        OdUInt32 nCoordIndex = coordinates.size();
        coordinates.push_back(pTriangle->p1.x); coordinates.push_back(pTriangle->p1.y); coordinates.push_back(pTriangle->p1.z);
        coordinates.push_back(pTriangle->p2.x); coordinates.push_back(pTriangle->p2.y); coordinates.push_back(pTriangle->p2.z);
        coordinates.push_back(pTriangle->p3.x); coordinates.push_back(pTriangle->p3.y); coordinates.push_back(pTriangle->p3.z);

        // normals
        OdUInt32 nNormalIndex = normal_coordinate.size();
        normal_coordinate.push_back(pTriangle->vtx_normal[0].x); normal_coordinate.push_back(pTriangle->vtx_normal[0].y); normal_coordinate.push_back(pTriangle->vtx_normal[0].z);
        normal_coordinate.push_back(pTriangle->vtx_normal[1].x); normal_coordinate.push_back(pTriangle->vtx_normal[1].y); normal_coordinate.push_back(pTriangle->vtx_normal[1].z);
        normal_coordinate.push_back(pTriangle->vtx_normal[2].x); normal_coordinate.push_back(pTriangle->vtx_normal[2].y); normal_coordinate.push_back(pTriangle->vtx_normal[2].z);

        // triangulated indices
        triangulated_index.push_back(nNormalIndex);
        triangulated_index.push_back(nCoordIndex);
        triangulated_index.push_back(nNormalIndex + 3);
        triangulated_index.push_back(nCoordIndex + 3);
        triangulated_index.push_back(nNormalIndex + 6);
        triangulated_index.push_back(nCoordIndex + 6);

        for (OdUInt32 iColor = 0; iColor < 3; ++iColor)
        {
          curFace.arrayRGBA().colors().push_back(pTriangle->red[iColor]);
          curFace.arrayRGBA().colors().push_back(pTriangle->green[iColor]);
          curFace.arrayRGBA().colors().push_back(pTriangle->blue[iColor]);
        }
      }
      uStartTriangulated += arrTriangleInfo.size() * 6;
    }
    else if (prcFaceKey.m_type == TriangleInfo::kTriangleTextured)
    {
      curFace.setUsedEntitiesFlag(PRC_FACETESSDATA_TriangleTextured);
      curFace.setNumberOfTextureCoordinateIndexes(1);
      for (OdUInt32 i = 0; i < arrTriangleInfo.size(); ++i)
      {
        const TriangleInfoTextured *pTriangle = ((const TriangleInfoTextured*)arrTriangleInfo[i].get());

        // normals
        OdUInt32 nNormalIndex = normal_coordinate.size();
        normal_coordinate.push_back(pTriangle->vtx_normal[0].x); normal_coordinate.push_back(pTriangle->vtx_normal[0].y); normal_coordinate.push_back(pTriangle->vtx_normal[0].z);
        normal_coordinate.push_back(pTriangle->vtx_normal[1].x); normal_coordinate.push_back(pTriangle->vtx_normal[1].y); normal_coordinate.push_back(pTriangle->vtx_normal[1].z);
        normal_coordinate.push_back(pTriangle->vtx_normal[2].x); normal_coordinate.push_back(pTriangle->vtx_normal[2].y); normal_coordinate.push_back(pTriangle->vtx_normal[2].z);

        // texture coordinates
        OdUInt32 nTexCoordIndex = texture_coordinates.size();
        texture_coordinates.push_back(pTriangle->texCoords[0].x); texture_coordinates.push_back(pTriangle->texCoords[0].y);
        texture_coordinates.push_back(pTriangle->texCoords[1].x); texture_coordinates.push_back(pTriangle->texCoords[1].y);
        texture_coordinates.push_back(pTriangle->texCoords[2].x); texture_coordinates.push_back(pTriangle->texCoords[2].y);

        //points
        OdUInt32 nCoordIndex = coordinates.size();
        coordinates.push_back(pTriangle->p1.x); coordinates.push_back(pTriangle->p1.y); coordinates.push_back(pTriangle->p1.z);
        coordinates.push_back(pTriangle->p2.x); coordinates.push_back(pTriangle->p2.y); coordinates.push_back(pTriangle->p2.z);
        coordinates.push_back(pTriangle->p3.x); coordinates.push_back(pTriangle->p3.y); coordinates.push_back(pTriangle->p3.z);

        // triangulated indices
        triangulated_index.push_back(nNormalIndex);
        triangulated_index.push_back(nTexCoordIndex);
        triangulated_index.push_back(nCoordIndex);
        triangulated_index.push_back(nNormalIndex + 3);
        triangulated_index.push_back(nTexCoordIndex + 2);
        triangulated_index.push_back(nCoordIndex + 3);
        triangulated_index.push_back(nNormalIndex + 6);
        triangulated_index.push_back(nTexCoordIndex + 4);
        triangulated_index.push_back(nCoordIndex + 6);
      }

      //material
      OdPrcObjectId lineStyleID;
      const TriangleInfoTextured *pTriangle = ((const TriangleInfoTextured*)arrTriangleInfo[0].get());
      if (pTriangle->materialLineStyleID)
      {
        lineStyleID = pTriangle->materialLineStyleID;
      }
      if (lineStyleID.isNull())
      {
        if (pTriangle->materialID)
        {
          DrawingMaterialNode matNode;
          matNode.pMaterial = pTriangle->materialID;
          matNode.drawingColor = pTriangle->color;
          matNode.transparency.setAlpha(pTriangle->alpha);
          lineStyleID = prcContext.getLineStyleID(matNode, newStructure);
        }
        else
        {
          DrawingColorNode colorNode;
          colorNode.drawingColor = pTriangle->color;
          colorNode.transparency.setAlpha(pTriangle->alpha);
          lineStyleID = prcContext.getLineStyleID(colorNode, newStructure);
        }
      }
      if (!lineStyleID.isNull())
      {
        curFace.lineAttributes().append(lineStyleID);
      }

      uStartTriangulated += arrTriangleInfo.size() * 9;
    }
    else if (prcFaceKey.m_type == TriangleInfo::kTriangle)
    {
      curFace.setUsedEntitiesFlag(PRC_FACETESSDATA_Triangle);
      for (OdUInt32 i = 0; i < arrTriangleInfo.size(); ++i)
      {
        const TriangleInfoColoredPoints *pTriangle = ((const TriangleInfoColoredPoints*)arrTriangleInfo[i].get());

        //points
        OdUInt32 nCoordIndex = coordinates.size();
        coordinates.push_back(pTriangle->p1.x); coordinates.push_back(pTriangle->p1.y); coordinates.push_back(pTriangle->p1.z);
        coordinates.push_back(pTriangle->p2.x); coordinates.push_back(pTriangle->p2.y); coordinates.push_back(pTriangle->p2.z);
        coordinates.push_back(pTriangle->p3.x); coordinates.push_back(pTriangle->p3.y); coordinates.push_back(pTriangle->p3.z);

        // normals
        OdUInt32 nNormalIndex = normal_coordinate.size();
        normal_coordinate.push_back(pTriangle->vtx_normal[0].x); normal_coordinate.push_back(pTriangle->vtx_normal[0].y); normal_coordinate.push_back(pTriangle->vtx_normal[0].z);
        normal_coordinate.push_back(pTriangle->vtx_normal[1].x); normal_coordinate.push_back(pTriangle->vtx_normal[1].y); normal_coordinate.push_back(pTriangle->vtx_normal[1].z);
        normal_coordinate.push_back(pTriangle->vtx_normal[2].x); normal_coordinate.push_back(pTriangle->vtx_normal[2].y); normal_coordinate.push_back(pTriangle->vtx_normal[2].z);

        // triangulated indices
        triangulated_index.push_back(nNormalIndex);
        triangulated_index.push_back(nCoordIndex);
        triangulated_index.push_back(nNormalIndex + 3);
        triangulated_index.push_back(nCoordIndex + 3);
        triangulated_index.push_back(nNormalIndex + 6);
        triangulated_index.push_back(nCoordIndex + 6);
      }

      //material
      OdPrcObjectId lineStyleID;
      const TriangleInfo *pTriangle = arrTriangleInfo[0].get();
      if (pTriangle->materialID)
      {
        DrawingMaterialNode matNode;
        matNode.pMaterial = pTriangle->materialID;
        matNode.drawingColor = pTriangle->color;
        matNode.transparency.setAlpha(pTriangle->alpha);
        lineStyleID = prcContext.getLineStyleID(matNode, newStructure);
      }
      else
      {
        DrawingColorNode colorNode;
        colorNode.drawingColor = pTriangle->color;
        colorNode.transparency.setAlpha(pTriangle->alpha);
        lineStyleID = prcContext.getLineStyleID(colorNode, newStructure);
      }
      if (!lineStyleID.isNull())
      {
        curFace.lineAttributes().append(lineStyleID);
      }

      uStartTriangulated += arrTriangleInfo.size() * 6;
    }
    else
    {
      throw OdError(eInvalidInput);
    }
  }

  //remove duplicate data
  tess3d->optimize();
  return tess3d;
}

void meshExtents(const TriangleInfoPtrArray &mesh, OdGeExtents3d &extents)
{
  TriangleInfoPtrArray::const_iterator pIt = mesh.begin();
  TriangleInfoPtrArray::const_iterator pItEnd = mesh.end();

  extents = OdGeExtents3d();
  while(pIt != pItEnd)
  {
    const TriangleInfo *pT = pIt->get();
    extents.addPoint(OdGePoint3d(pT->p1.x, pT->p1.y, pT->p1.z));
    extents.addPoint(OdGePoint3d(pT->p2.x, pT->p2.y, pT->p2.z));
    extents.addPoint(OdGePoint3d(pT->p3.x, pT->p3.y, pT->p3.z));
    ++pIt;
  }
}
