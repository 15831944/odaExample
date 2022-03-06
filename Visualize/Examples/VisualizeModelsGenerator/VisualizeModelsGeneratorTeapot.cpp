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

#include "VisualizeModelsGeneratorTeapot.h"
#include "TvGeometryData.h"

void OdTvVisualizeSampleModelsTeapot::drawTeapot(OdTvShellDataPtr& pShell, OdTvPoint2dArray& mappingCoords, OdTvEntityPtr& pEntityPtr, double x, double y, double z)
{
  OdTvPointArray vertices; OdInt32Array faces;  OdTvVectorArray normals;
  calculateTeapotParams(vertices, faces, normals, mappingCoords, x, y, z);

  OdTvGeometryDataId shellId = pEntityPtr->appendShell(vertices, faces);

  shellId.openObject()->rotateAxis(OdTvVector::kYAxis, OdaPI / 2);

  pShell = shellId.openAsShell();
  pShell->setVertexNormalsViaRange(0, normals);
}

void OdTvVisualizeSampleModelsTeapot::calculateTeapotParams(OdTvPointArray& vertices, OdInt32Array& faces, OdTvVectorArray& normals, OdTvPoint2dArray& mappingCoords, double x, double y, double z)
{
  OdInt32 nVertices = 363 + 159 + 149 + 252;
  OdInt32 nFacesListSize = (512 + 128 + 128 + 256) * 4;

  vertices.resize(nVertices);
  faces.resize(nFacesListSize);
  normals.resize(nVertices);
  mappingCoords.resize(nVertices);

  OdUInt32 i = 0;
  calculateTeapotVertices(vertices, ExTeapotBodyVertices, i, 363 * 3, x, y, z);
  calculateTeapotVertices(vertices, ExTeapotHandleVertices, i, 159 * 3, x, y, z);
  calculateTeapotVertices(vertices, ExTeapotSpoutVertices, i, 149 * 3, x, y, z);
  calculateTeapotVertices(vertices, ExTeapotLidVertices, i, 252 * 3, x, y, z);

  i = 0;
  calculateTeapotFaces(faces, ExTeapotBodyIndices, i, 512 * 4, 0);
  calculateTeapotFaces(faces, ExTeapotHandleIndices, i, 128 * 4, 363);
  calculateTeapotFaces(faces, ExTeapotSpoutIndices, i, 128 * 4, 363 + 159);
  calculateTeapotFaces(faces, ExTeapotLidIndices, i, 256 * 4, 363 + 159 + 149);

  i = 0;
  calculateTeapotNormals(normals, ExTeapotBodyNormals, i, 363 * 3);
  calculateTeapotNormals(normals, ExTeapotHandleNormals, i, 159 * 3);
  calculateTeapotNormals(normals, ExTeapotSpoutNormals, i, 149 * 3);
  calculateTeapotNormals(normals, ExTeapotLidNormals, i, 252 * 3);

  i = 0;
  calculateTeapotMappingCoords(mappingCoords, ExTeapotBodyTexCoords, i, 363 * 2);
  calculateTeapotMappingCoords(mappingCoords, ExTeapotHandleTexCoords, i, 159 * 2);
  calculateTeapotMappingCoords(mappingCoords, ExTeapotSpoutTexCoords, i, 149 * 2);
  calculateTeapotMappingCoords(mappingCoords, ExTeapotLidTexCoords, i, 252 * 2);
}

void OdTvVisualizeSampleModelsTeapot::calculateTeapotVertices(OdTvPointArray& vertices, const double* ExVertices, OdUInt32& pos, OdUInt32 num, double x, double y, double z)
{
  OdUInt32 k = 0;
  while (k < num)
  {
    vertices[pos].x = ExVertices[k++] + x;
    vertices[pos].y = ExVertices[k++] + y;
    vertices[pos].z = ExVertices[k++] + z;
    pos++;
  }
}

void OdTvVisualizeSampleModelsTeapot::calculateTeapotFaces(OdInt32Array& faces, const OdInt32* ExFaces, OdUInt32& pos, OdUInt32 num, OdUInt32 prevNum)
{
  OdUInt32 k = 0;

  while (k < num)
  {
    OdInt32 faceNum = ExFaces[k++];
    faces[pos++] = faceNum;
    for (OdUInt32 i = 0; i < (OdUInt32)faceNum; i++)
    {
      faces[pos++] = ExFaces[k++] + prevNum;
    }
  }

}

void OdTvVisualizeSampleModelsTeapot::calculateTeapotNormals(OdTvVectorArray& normals, const double* ExNormals, OdUInt32& pos, OdUInt32 num)
{
  OdUInt32 k = 0;
  while (k < num)
  {
    normals[pos].x = ExNormals[k++];
    normals[pos].y = ExNormals[k++];
    normals[pos].z = ExNormals[k++];
    pos++;
  }
}

void OdTvVisualizeSampleModelsTeapot::calculateTeapotMappingCoords(OdTvPoint2dArray& mappingCoords, const double* ExMappingCoords, OdUInt32& pos, OdUInt32 num)
{
  OdUInt32 k = 0;
  while (k < num)
  {
    mappingCoords[pos].x = ExMappingCoords[k++];
    mappingCoords[pos].y = ExMappingCoords[k++];
    pos++;
  }
}
