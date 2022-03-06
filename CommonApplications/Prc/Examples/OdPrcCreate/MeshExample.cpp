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
#include "DbHostAppServices.h"
#include "OdPrcCreateStart.h"
#include "PrcCreateMeshHelper.h"
#include "PrcExport.h"
#include "PdfExportService.h"

void addSimpleTriangle(TriangleInfoPtrArray &mesh,
  double nx, double ny, double nz,
  double p1x, double p1y, double p1z,
  double p2x, double p2y, double p2z,
  double p3x, double p3y, double p3z,
  OdUInt8 r, OdUInt8 g, OdUInt8 b);

void meshExample(OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  TriangleInfoPtrArray mesh;
  OdUInt32 entities_flag;
  if (mode == kMeshBox)
  {
    entities_flag = PRC_FACETESSDATA_Triangle;
    addSimpleTriangle(mesh, 0,0,-1, 0,0,0, 1,1,0, 1,0,0, 255,0,0);
    addSimpleTriangle(mesh, 0,0,-1, 1,1,0, 0,0,0, 0,1,0, 128,0,0);

    addSimpleTriangle(mesh, 0,0,1, 1,0,1, 1,1,1, 0,0,1, 0,255,0);
    addSimpleTriangle(mesh, 0,0,1, 0,1,1, 0,0,1, 1,1,1, 0,128,0);

    addSimpleTriangle(mesh, 0,1,0, 0,1,0, 1,1,1, 1,1,0, 0,0,255);
    addSimpleTriangle(mesh, 0,1,0, 1,1,1, 0,1,0, 0,1,1, 0,0,128);

    addSimpleTriangle(mesh, 0,-1,0, 1,0,0, 1,0,1, 0,0,0, 255,255,0);
    addSimpleTriangle(mesh, 0,-1,0, 0,0,1, 0,0,0, 1,0,1, 128,128,0);

    addSimpleTriangle(mesh, 1,0,0, 1,1,1, 1,0,0, 1,1,0, 0,255,255);
    addSimpleTriangle(mesh, 1,0,0, 1,0,0, 1,1,1, 1,0,1, 0,128,128);

    addSimpleTriangle(mesh, -1,0,0, 0,0,0, 0,1,1, 0,1,0, 255,0,255);
    addSimpleTriangle(mesh, -1,0,0, 0,1,1, 0,0,0, 0,0,1, 128,0,128);
  }
  if (mode == kTriangleFan)
  {
    //entities_flag = PRC_FACETESSDATA_TriangleFan;
    entities_flag = PRC_FACETESSDATA_Triangle;
    addSimpleTriangle(mesh, 0,0,1, 0,0,0, 1,0,0, 1,1,0, 255,0,0);
    addSimpleTriangle(mesh, 0,0,1, 0,0,0, 1,1,0, 0,1,0, 128,0,0);
    addSimpleTriangle(mesh, 0,0,1, 0,0,0, 0,1,0, -1,0,0, 0,0,255);
    addSimpleTriangle(mesh, 0,0,1, 0,0,0, -1,0,0, -1,-1,0, 0,0,128);
    addSimpleTriangle(mesh, 0,0,1, 0,0,0, -1,-1,0, 0,-1,0, 0,255,0);
    addSimpleTriangle(mesh, 0,0,1, 0,0,0, 0,-1,0, 1,0,0, 0,128,0);

  }
  if (mode == kTriangleStripe)
  {
    //entities_flag = PRC_FACETESSDATA_TriangleStripe;
    entities_flag = PRC_FACETESSDATA_Triangle;
    addSimpleTriangle(mesh, 0,0,-1, 0,0,0, 0,2,0, 2,0,0, 0,0,255);
    addSimpleTriangle(mesh, 1,1,0,  0,2,0, 2,0,0, 1,1,2, 0,0,255);
    addSimpleTriangle(mesh, 0,-1,1, 2,0,0, 1,1,2, 0,0,0, 0,0,255);
    addSimpleTriangle(mesh, -1,0,1, 1,1,2, 0,0,0, 0,2,0, 0,0,255);
  }
  if (mode == kTessCombination)
  {
    // Figure for combine type
    // - Roof
    entities_flag = PRC_FACETESSDATA_Triangle;
    addSimpleTriangle(mesh, 0,0,1, 1,0,1, 1,1,1, 0,1,1, 255,0,0);
    addSimpleTriangle(mesh, 0,0,1, 0,1,1, -1,0,1, 0,0,1, 0,255,0);
    addSimpleTriangle(mesh, 0,0,1, -1,0,1, -1,-1,1, 0,-1,1, 255,0,0);
    addSimpleTriangle(mesh, 0,0,1, 0,0,1, 0,-1,1, 1,0,1, 0,255,0);
    addSimpleTriangle(mesh, 0,0,1, 1,0,1, 0,1,1, 0,0,1, 0,0,255);
    addSimpleTriangle(mesh, 0,0,1, -1,0,1, 0,-1,1, 0,0,1, 0,0,255);

    // - Floor
    //entities_flag = PRC_FACETESSDATA_TriangleFan;
    entities_flag = PRC_FACETESSDATA_Triangle;
    addSimpleTriangle(mesh, 0,0,-1, 0,0,0, 1,0,0, 0,-1,0, 255,0,0);
    addSimpleTriangle(mesh, 0,0,-1, 0,0,0, 0,-1,0, -1,-1,0, 128,0,0);
    addSimpleTriangle(mesh, 0,0,-1, 0,0,0, -1,-1,0, -1,0,0, 0,0,255);
    addSimpleTriangle(mesh, 0,0,-1, 0,0,0, -1,0,0, 0,1,0, 0,0,128);
    addSimpleTriangle(mesh, 0,0,-1, 0,0,0, 0,1,0, 1,1,0, 0,255,0);
    addSimpleTriangle(mesh, 0,0,-1, 0,0,0, 1,1,0, 1,0,0, 0,128,0);

    // - Walls
    //entities_flag = PRC_FACETESSDATA_TriangleStripe;

    addSimpleTriangle(mesh, 1,0,0, 1,0,1, 1,0,0, 1,1,1, 255,0,0 );
    addSimpleTriangle(mesh, 1,0,0, 1,0,0, 1,1,1, 1,1,0, 0,255,0 );
                            
    addSimpleTriangle(mesh, 0,1,0, 1,1,1, 1,1,0, 0,1,1, 0,0,255 );
    addSimpleTriangle(mesh, 0,1,0, 1,1,0, 0,1,1, 0,1,0, 255,255,0 );
                            
    addSimpleTriangle(mesh, -1,1,0, 0,1,1, 0,1,0, -1,0,1, 255,0,255 );
    addSimpleTriangle(mesh, -1,1,0, 0,1,0, -1,0,1, -1,0,0, 0,255,255 );
                            
    addSimpleTriangle(mesh, -1,0,0, -1,0,1, -1,0,0, -1,-1,1, 128,0,0 );
    addSimpleTriangle(mesh, -1,0,0, -1,0,0, -1,-1,1, -1,-1,0, 0,128,0 );
                            
    addSimpleTriangle(mesh, 0,-1,0, -1,-1,1, -1,-1,0, 0,-1,1, 0,0,128 );
    addSimpleTriangle(mesh, 0,-1,0, -1,-1,0, 0,-1,1, 0,-1,0, 128,128,0 );
                            
    addSimpleTriangle(mesh, 1,-1,0, 0,-1,1, 0,-1,0, 1,0,1, 128,0,128 );
    addSimpleTriangle(mesh, 1,-1,0, 0,-1,0, 1,0,1, 1,0,0, 0,128,128 );
  }

  // load module
  odrxDynamicLinker()->loadModule(OdDwg2PrcExportModuleName, false);

  PdfExportServiceInterfacePtr pExportIFace = getPdfExportService();
  // write file to stream
  PDF2PRCExportParams params;
  params.m_exportAsBrep = false;
  OdRxObjectPtr pContext = pExportIFace->createPrcExportContext(NULL);
  OdResult res = exportMeshToPrc(mesh, pContext);
  if (res != eOk)
  {
    throw OdError(res);
  }
  res = pExportIFace->serialize(pPrcStream, pContext, &params);
  if (res != eOk)
  {
    throw OdError(res);
  }
}

