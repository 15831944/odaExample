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

#include "GeometryExporter.h"
#include "ColladaExportView.h"

namespace TD_COLLADA_EXPORT
{
  GeometryExporter::GeometryExporter(COLLADASW::StreamWriter * streamWriter):COLLADASW::LibraryGeometries ( streamWriter ) 
  {
    openLibrary();
  }

  GeometryExporter::~GeometryExporter()
  {
    closeLibrary(); 
  }

  void GeometryExporter::exportGeometry(OdDbBaseDatabase *pDb, ColladaEntData* pColladaData, ColladaMaterialData& pMatTraitsDataArr, const OdGiDrawable* pEntity)
  {
    int iNumPos = pColladaData->m_ptArr.size();
    if (iNumPos == 0)
      return;
    OdString buffer;
    buffer.format(OD_T("%i"), pColladaData->m_iId); 

    COLLADASW::NativeString idStr(buffer.c_str());
    COLLADASW::String strShape("shape" + idStr + "-lib");
    openMesh(strShape);

    //points array
    COLLADASW::FloatSource source( this->mSW );
    source.setId(strShape + COLLADASW::LibraryGeometries::POSITIONS_SOURCE_ID_SUFFIX);
    source.setArrayId(strShape + COLLADASW::LibraryGeometries::POSITIONS_SOURCE_ID_SUFFIX + ARRAY_ID_SUFFIX);

    //source.setId(str + strLib + COLLADASW::LibraryGeometries::POSITIONS_SOURCE_ID_SUFFIX);
    source.setNodeName(COLLADASW::String("position"));
    source.setAccessorStride( 3 );
    source.getParameterNameList().push_back( "X" );
    source.getParameterNameList().push_back( "Y" );
    source.getParameterNameList().push_back( "Z" );
    source.setAccessorCount( iNumPos );
    source.prepareToAppendValues();

    for (int iIdx = 0; iIdx < iNumPos; ++iIdx)
    {
      source.appendValues( pColladaData->m_ptArr[iIdx].x, pColladaData->m_ptArr[iIdx].y, pColladaData->m_ptArr[iIdx].z );
    }
    source.finish();

    if (!pColladaData->m_bIsPolyline)
    {
      //normals array
      int iNumVtxPos = pColladaData->m_normVtxArr.size();
      COLLADASW::FloatSource sourceNorm(this->mSW);
      sourceNorm.setId(strShape + COLLADASW::LibraryGeometries::NORMALS_SOURCE_ID_SUFFIX);
      sourceNorm.setArrayId(strShape + COLLADASW::LibraryGeometries::NORMALS_SOURCE_ID_SUFFIX + ARRAY_ID_SUFFIX);

      sourceNorm.setNodeName(COLLADASW::String("normal"));
      sourceNorm.setAccessorStride(3);
      sourceNorm.getParameterNameList().push_back("X");
      sourceNorm.getParameterNameList().push_back("Y");
      sourceNorm.getParameterNameList().push_back("Z");
      sourceNorm.setAccessorCount(iNumVtxPos);
      sourceNorm.prepareToAppendValues();

      for (int iIdx = 0; iIdx < iNumVtxPos; ++iIdx)
      {
        sourceNorm.appendValues(pColladaData->m_normVtxArr[iIdx].x, pColladaData->m_normVtxArr[iIdx].y, pColladaData->m_normVtxArr[iIdx].z);
      }
      sourceNorm.finish();

      //texture coord array
      if (pMatTraitsDataArr.m_matDataArr[pColladaData->m_iEntMaterial].bDiffuseChannelEnabled &&
        pMatTraitsDataArr.m_matDataArr[pColladaData->m_iEntMaterial].bDiffuseHasTexture)
      {
        int iNumTextCoord = pColladaData->m_pDiffuseMaterialMapperArr.m_ptTextureCoordArr.size();
        COLLADASW::FloatSource sourceTextCoord(this->mSW);
        sourceTextCoord.setId(strShape + COLLADASW::LibraryGeometries::TEXCOORDS_SOURCE_ID_SUFFIX);
        sourceTextCoord.setArrayId(strShape + COLLADASW::LibraryGeometries::TEXCOORDS_SOURCE_ID_SUFFIX + ARRAY_ID_SUFFIX);

        sourceTextCoord.setNodeName(COLLADASW::String("textcoord"));
        sourceTextCoord.setAccessorStride(2);
        sourceTextCoord.getParameterNameList().push_back("S");
        sourceTextCoord.getParameterNameList().push_back("T");
        sourceTextCoord.setAccessorCount(iNumTextCoord);
        sourceTextCoord.prepareToAppendValues();

        for (int iIdx = 0; iIdx < iNumTextCoord; ++iIdx)
        {
          sourceTextCoord.appendValues(pColladaData->m_pDiffuseMaterialMapperArr.m_ptTextureCoordArr[iIdx].x, pColladaData->m_pDiffuseMaterialMapperArr.m_ptTextureCoordArr[iIdx].y);
        }
        sourceTextCoord.finish();
      }
    }

    //vertices array
    {
      COLLADASW::VerticesElement vertices( this->mSW );
      vertices.setId( strShape + COLLADASW::LibraryGeometries::VERTICES_ID_SUFFIX );
      vertices.getInputList().push_back(COLLADASW::Input(COLLADASW::InputSemantic::POSITION, "#" + strShape + COLLADASW::LibraryGeometries::POSITIONS_SOURCE_ID_SUFFIX));
      vertices.add();
    }

    buffer.format(OD_T("%i"), pColladaData->m_iEntMaterial + 1);
    COLLADASW::NativeString matIDStr(buffer.c_str());
    if (pColladaData->m_bIsPolyline)
    {
      //lines
      for (unsigned lineIdx = 0, vertexIdx = 0; lineIdx < pColladaData->m_numVtxOnFaceArr.size(); ++lineIdx)
      {
        COLLADASW::Linestrips lines(this->mSW);
        lines.setMaterial("Material" + matIDStr);
        lines.setCount(1);
        lines.getInputList().push_back(COLLADASW::Input(COLLADASW::InputSemantic::VERTEX, "#" + strShape + COLLADASW::LibraryGeometries::VERTICES_ID_SUFFIX, 0));

        lines.prepareToAppendValues();
        for (unsigned iIdx = 0; iIdx < pColladaData->m_numVtxOnFaceArr[lineIdx]; ++iIdx, ++vertexIdx)
        {
          lines.appendValues(vertexIdx);
        }

        lines.finish();
      }
    }
    else
    {
      //triangles
      iNumPos = pColladaData->m_indPtsArr.size();
      COLLADASW::Triangles triangles(this->mSW);
      triangles.setMaterial("Material" + matIDStr);
      ODA_ASSERT(iNumPos % 3 == 0);
      triangles.setCount(iNumPos / 3);
      triangles.getInputList().push_back(COLLADASW::Input(COLLADASW::InputSemantic::VERTEX, "#" + strShape + COLLADASW::LibraryGeometries::VERTICES_ID_SUFFIX, 0));
      triangles.getInputList().push_back(COLLADASW::Input(COLLADASW::InputSemantic::NORMAL, "#" + strShape + COLLADASW::LibraryGeometries::NORMALS_SOURCE_ID_SUFFIX, 1));

      bool hasTextures = pMatTraitsDataArr.m_matDataArr[pColladaData->m_iEntMaterial].bDiffuseChannelEnabled &&
        pMatTraitsDataArr.m_matDataArr[pColladaData->m_iEntMaterial].bDiffuseHasTexture;

      if (hasTextures)
        triangles.getInputList().push_back(COLLADASW::Input(COLLADASW::InputSemantic::TEXCOORD, "#" + strShape + COLLADASW::LibraryGeometries::TEXCOORDS_SOURCE_ID_SUFFIX, 2));

      triangles.prepareToAppendValues();
      for (int iIdx = 0; iIdx < iNumPos; ++iIdx)
      {
        triangles.appendValues(pColladaData->m_indPtsArr[iIdx]);
        triangles.appendValues(pColladaData->m_indVtxNormArr[iIdx]);
        if (hasTextures)
          triangles.appendValues(pColladaData->m_pDiffuseMaterialMapperArr.m_indTextureCoordArr[iIdx]);
      }

      triangles.finish();
    }

    closeGeometry();
  }
}
