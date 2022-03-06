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
#include "Ge/GeCircArc2d.h"
using namespace FacetModeler;

/** <snippet name="fm_create_makeVector" lang="cpp"> */
template< typename T, size_t N >
std::vector<T> makeVector(const T(&data)[N])
{
  return std::vector<T>(data, data + N);
}
/** </snippet> */

/** <snippet name="fm_create_cube" lang="cpp"> */
Body createCube(double edgeLen)
{
  // Create dimensions vector
  OdGeVector3d dimensions(edgeLen, edgeLen, edgeLen);

  // Move the origin point to the center of the cube base
  OdGeVector3d shift(edgeLen / 2, edgeLen / 2, 0.0);

  return Body::box(OdGePoint3d::kOrigin - shift, dimensions);
}
/** </snippet> */

/** <snippet name="fm_create_pyramid" lang="cpp"> */
Body createPyramid(const DeviationParams& devDeviation, double dRadius, double dHeight, unsigned int sidesCnt)
{
  // Create circle for polygon inscribing
  OdGeCircArc2d circle(OdGePoint3d::kOrigin.convert2d(), dRadius);
  OdGePoint2dArray points;

  // Inscribe a polygon in a circle and get vertices
  circle.getSamplePoints(sidesCnt, points);

  // Create base profile
  Profile2D cBase;

  // Only with one contour
  cBase.resize(1);

  // Fill contour with vertices
  cBase.front().appendVertices(points);

  // Close profile
  cBase.front().setClosed();

  // Make contour outer
  cBase.front().makeCCW();

  // Create apex
  OdGePoint3d apex(
    OdGePoint3d::kOrigin.x,
    OdGePoint3d::kOrigin.y,
    OdGePoint3d::kOrigin.z + dHeight
  );

  // Create pyramid
  return Body::pyramid(cBase, apex, devDeviation);
}
/** </snippet> */

/** <snippet name="fm_create_cone" lang="cpp"> */
Body createCone(const DeviationParams& devDeviation, double dRadius, double dHeight)
{
  // Create base profile
  Profile2D cBase;

  // With one contour
  cBase.resize(1);

  // Add vertices with bulge == 1 (so that they form an arc)
  cBase.front().appendVertex(OdGePoint2d::kOrigin - OdGeVector2d::kXAxis * dRadius, 1);
  cBase.front().appendVertex(OdGePoint2d::kOrigin + OdGeVector2d::kXAxis * dRadius, 1);

  cBase.front().setOrientationAt(0, efoFront);
  cBase.front().setOrientationAt(1, efoFront);

  // Close profile
  cBase.front().setClosed();

  // Make contour outer
  cBase.front().makeCCW();

  // Create apex point
  OdGePoint3d apex(
    OdGePoint3d::kOrigin.x,
    OdGePoint3d::kOrigin.y,
    OdGePoint3d::kOrigin.z + dHeight
  );

  return Body::pyramid(cBase, apex, devDeviation);
}
/** </snippet> */
/** <snippet name="fm_create_meshCube" lang="cpp"> */
Body createMeshCube(const DeviationParams& devDeviation)
{
  // Create array of vertices
  OdGePoint3d aVertices[] = {
    OdGePoint3d(0.0, 0.0, 0.0),
    OdGePoint3d(1.0, 0.0, 0.0),
    OdGePoint3d(1.0, 1.0, 0.0),
    OdGePoint3d(0.0, 1.0, 0.0),
    OdGePoint3d(0.0, 0.0, 1.0),
    OdGePoint3d(1.0, 0.0, 1.0),
    OdGePoint3d(1.0, 1.0, 1.0),
    OdGePoint3d(0.0, 1.0, 1.0),
  };

  // Create array with face data
  OdInt32 aFaceData[] = {
    4, 3, 2, 1, 0,
    4, 4, 5, 6, 7,
    4, 2, 3, 7, 6,
    4, 1, 2, 6, 5,
    4, 0, 1, 5, 4,
    4, 3, 0, 4, 7
  };

  Body body = Body::createFromMesh(
    makeVector(aVertices), makeVector(aFaceData)
  );

  return body;
}
/** </snippet> */

void _FMDocCreation_func(OdEdCommandContext* pCmdCtx)
{
  DeviationParams devParams;
  Body cube = createCube(10.);
  Body pyramid = createPyramid(devParams, 10., 20., 5);
  Body cone = createCone(devParams, 10., 20.);
  Body meshCube = createMeshCube(devParams);
}

