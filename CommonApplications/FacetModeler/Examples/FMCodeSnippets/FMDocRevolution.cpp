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
#include "Ge/GeCircArc3d.h"

using namespace FacetModeler;

/** <snippet name="fm_revolution_sphere" lang="cpp"> */
Body createSphere(const DeviationParams& devDeviation, double dRadius)
{
  // Create a sphere profile
  Profile2D cSphereProfile;

  // With one contour
  cSphereProfile.resize(1);

  // Add vertices with bulge == 1 (Arc)
  cSphereProfile.front().appendVertex(OdGePoint2d::kOrigin); // Add first point
  cSphereProfile.front().appendVertex(OdGePoint2d::kOrigin + OdGeVector2d::kXAxis * dRadius * 2, 1);

  // Will be reversed in revolution method.
  cSphereProfile.front().setOrientationAt(0, efoBack);
  cSphereProfile.front().setOrientationAt(1, efoBack);

  // Close profile
  cSphereProfile.front().setClosed();

  // Make contour outer
  cSphereProfile.front().makeCCW();

  // Create revolution body
  return Body::revolution(cSphereProfile, dRadius, dRadius * 2, devDeviation);
}
/** </snippet> */

/** <snippet name="fm_revolution_torus" lang="cpp"> */
Body createTorus(const DeviationParams& devDeviation, double dRadius1, double dRadius2)
{
  Profile2D cTorusProfile;
  cTorusProfile.resize(1);

  OdGeMatrix2d move;
  OdGeCircArc3d arc(OdGePoint3d::kOrigin, OdGeVector3d::kXAxis, dRadius2);

  cTorusProfile.front().appendVertex(OdGePoint2d::kOrigin + OdGeVector2d::kXAxis * dRadius1, 1);
  cTorusProfile.front().appendVertex(OdGePoint2d::kOrigin - OdGeVector2d::kXAxis * dRadius1, 1);

  move.setToTranslation(OdGeVector2d(dRadius2, 0.0));

  cTorusProfile.transformBy(move);

  cTorusProfile.front().setOrientationAt(0, efoFront);
  cTorusProfile.front().setOrientationAt(1, efoFront);
  cTorusProfile.front().setClosed();
  cTorusProfile.front().makeCCW();

  return Body::revolution(cTorusProfile, arc, devDeviation);
}
/** </snippet> */

void _FMDocRevolution_func(OdEdCommandContext* pCmdCtx)
{
  DeviationParams devParams;
  Body sphere = createSphere(devParams, 10.);
  Body torus = createTorus(devParams, 10., 5.);
}

