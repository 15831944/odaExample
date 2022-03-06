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

using namespace FacetModeler;

/** <snippet name="fm_extrusion_cylinder" lang="cpp"> */
Body createCylinder(const DeviationParams& devDeviation, double dRadius, double dHeight)
{
  // Create base profile
  Profile2D cBase;

  // With one contour
  cBase.resize(1);

  cBase.front().appendVertex(OdGePoint2d::kOrigin - OdGeVector2d::kXAxis * dRadius, 1);
  cBase.front().appendVertex(OdGePoint2d::kOrigin + OdGeVector2d::kXAxis * dRadius, 1);

  cBase.front().setOrientationAt(0, efoFront);
  cBase.front().setOrientationAt(1, efoFront);

  // Close profile
  cBase.front().setClosed();

  // Make contour outer
  cBase.front().makeCCW();

  return Body::extrusion(cBase, OdGeVector3d::kZAxis * dHeight, devDeviation);
}
/** </snippet> */

/** <snippet name="fm_extrusion_pipe1" lang="cpp"> */
Body createPipe1(const DeviationParams& devDeviation, double dRadius1, double dRadius2, double dHeight)
{
  Profile2D circle1;
  Profile2D circle2;
  Profile2D res;

  circle1 = Profile2D(Contour2D::createCircle(OdGePoint2d::kOrigin, dRadius1));
  circle2 = Profile2D(Contour2D::createCircle(OdGePoint2d::kOrigin, dRadius2));

  Profile2D::PerformOperation(eDifference, circle1, circle2, res);

  return Body::extrusion(res, OdGeVector3d::kZAxis * dHeight, devDeviation);
}
/** </snippet> */

/** <snippet name="fm_extrusion_pipe2" lang="cpp"> */
Body createPipe2(const DeviationParams& devDeviation, double dRadius1, double dRadius2, double dHeight)
{
  Body cyl1 = createCylinder(devDeviation, dRadius1, dHeight);
  Body cyl2 = createCylinder(devDeviation, dRadius2, dHeight);

  return Body::boolOper(eDifference, cyl1, cyl2);
}
/** </snippet> */

void _FMDocExtrusion_func(OdEdCommandContext* pCmdCtx)
{
  DeviationParams devParams;
  Body cylinder = createCylinder(devParams, 10., 20.);
  Body pipe1 = createPipe1(devParams, 10., 5., 10.);
  Body pipe2 = createPipe2(devParams, 20., 10., 10.);
}

