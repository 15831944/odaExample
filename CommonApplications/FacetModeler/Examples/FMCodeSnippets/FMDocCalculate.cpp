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
#include "FMProfile2D.h"
#include "FMContour2D.h"
#include "Modeler/FMMdlBody.h"
#include "Modeler/FMMdlIterators.h"

using namespace FacetModeler;


/** <snippet name="fm_calc_face_func" lang="cpp"> */
OdDouble calcFaceArea(Body& body)
{
  FacetModeler::FaceIterator iterator(&body);
  OdDouble faceArea = 0;
  for (; !iterator.done(); iterator.next())
  {
    faceArea += iterator.get()->area();
  }
  return faceArea;
}
/** </snippet> */

void _FMDocCalculate_func(OdEdCommandContext* pCmdCtx)
{
	double dSide = 10;
  /** <snippet name="fm_calc_contour" lang="cpp"> */
  Contour2D squareContour = Contour2D::createSquare(OdGePoint2d::kOrigin, dSide);

  // Calculate area of a contour
  double contourArea = squareContour.area();
  /** </snippet> */

  /** <snippet name="fm_calc_profile" lang="cpp"> */
  Profile2D squareProfile = Profile2D(Contour2D::createSquare(OdGePoint2d::kOrigin, dSide));

  // Calculate area of a profile
  double profileArea = squareProfile.signedArea();
  /** </snippet> */

  /** <snippet name="fm_calc_face" lang="cpp"> */
  OdGeVector3d dimensionsBig = OdGeVector3d(50., 50., 50.);
  Body bigBox = Body::box(OdGePoint3d::kOrigin, dimensionsBig);

  // Calculate face area of a body
  double surfaceArea = calcFaceArea(bigBox);
  /** </snippet> */


  /** <snippet name="fm_calc_body" lang="cpp"> */
  OdGeVector3d dimensionsSmall = OdGeVector3d(10., 10., 10.);
  Body smallBox = Body::box(OdGePoint3d::kOrigin, dimensionsSmall);

  // Calculate volume of a body
  double boxVolume = smallBox.volume();
  /** </snippet> */

}

