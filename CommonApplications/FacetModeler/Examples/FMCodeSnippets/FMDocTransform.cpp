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
#include "Modeler/FMMdlIterators.h"

using namespace FacetModeler;

/** <snippet name="fm_scaled_cube" lang="cpp"> */
Body scaledCube(const DeviationParams& devParams, double edgeLen) {
  Body cube = Body::box(OdGePoint3d::kOrigin, OdGeVector3d(edgeLen, edgeLen, edgeLen));
  OdGeMatrix3d matrix;
  matrix.setToScaling(.5);
  cube.transform(matrix);

  return cube;
}
/** </snippet> */

/** <snippet name="fm_trans_cube" lang="cpp"> */
Body transCube(const DeviationParams& devParams, double edgeLen) {
  Body cube = Body::box(OdGePoint3d::kOrigin, OdGeVector3d(edgeLen, edgeLen, edgeLen));
  OdGeMatrix3d matrix1, matrix2, matrix3, resMatrix;
  matrix1.setToScaling(.5);
  matrix2.setToRotation(OdaPI / 6, OdGeVector3d::kXAxis);
  matrix3.setToTranslation(OdGeVector3d(50.0, 50.0, 50.0));
  resMatrix = resMatrix.setToProduct(matrix1, matrix2);
  resMatrix = resMatrix.setToProduct(resMatrix, matrix3);
  cube.transform(resMatrix);

  return cube;
}
/** </snippet> */

void _FMDocTransform_func(OdEdCommandContext* pCmdCtx)
{
  DeviationParams devParams;

  Body cube1 = scaledCube(devParams, 10.);
  Body cube2 = transCube(devParams, 10.);
}

