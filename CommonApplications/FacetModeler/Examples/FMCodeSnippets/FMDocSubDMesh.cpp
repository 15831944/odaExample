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

#include "FMCodeSnippetsStdAfx.h"
#include "Modeler/FMMdlBody.h"
#include "Modeler/FMDrawBody.h"
#include "Ge/GeTrMeshSimplification.h"
#include "DbSubDMesh.h"
#include "DbBlockTableRecord.h"

using namespace FacetModeler;

void _FMDocSubDMesh_func(OdEdCommandContext* pCmdCtx)
{
  /** <snippet name="fm_mesh_box" lang="cpp"> */
  FacetModeler::Body body = Body::box(OdGePoint3d::kOrigin, OdGeVector3d(10., 10., 10.));
  /*...*/
  GeMesh::OdGeTrMesh mesh;
  body.generateMesh(mesh);
  /** </snippet> */

  /** <snippet name="fm_mesh_convert" lang="cpp"> */
  OdInt32Array faceArray;
  faceArray.reserve(mesh.m_aTr.logicalLength() * 4);
  for (unsigned int j = 0; j < mesh.m_aTr.logicalLength(); ++j)
  {
    const GeMesh::OdGeTr& tr = mesh.m_aTr[j];
    faceArray.push_back(3);
    faceArray.push_back(tr.tr[0]);
    faceArray.push_back(tr.tr[1]);
    faceArray.push_back(tr.tr[2]);
  }
  /** </snippet> */

  /** <snippet name="fm_mesh_final" lang="cpp"> */
  OdDbSubDMeshPtr pMesh = OdDbSubDMesh::createObject();
  /*...*/
  OdResult res = pMesh->setSubDMesh(mesh.m_aVx, faceArray, 0); // 0 - no smoothing
  /** </snippet> */

  /** <snippet name="fm_mesh_block" lang="cpp"> */
  OdDbDatabase* pDb;
  /*...*/
  OdDbBlockTableRecordPtr pMS = pDb->getModelSpaceId().openObject(OdDb::kForWrite);
  pMesh->setDatabaseDefaults(pDb);
  pMS->appendOdDbEntity(pMesh);
  /** </snippet> */
}

