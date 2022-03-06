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

/** <snippet name="fm_create_square" lang="cpp"> */
Profile2D createSquare(const double dSide)
{
	// Create a contour
	Contour2D square;

	// Set points that form a square
	OdGePoint2dArray aPoints;
	aPoints.reserve(4);
	aPoints.push_back(OdGePoint2d(dSide, dSide));
	aPoints.push_back(OdGePoint2d(dSide, 0.0));
	aPoints.push_back(OdGePoint2d::kOrigin);
	aPoints.push_back(OdGePoint2d(0.0, dSide));

	// Insert points into the contour
	square.appendVertices(aPoints);

	// Form edges by connecting points and close the profile
	square.setOrientationAt(0, efoFront);
	square.setOrientationAt(1, efoFront);
	square.setOrientationAt(2, efoFront);
	square.setOrientationAt(3, efoFront);
	square.setClosed();

	// Make the contour outer by setting its direction counterclockwise
	square.makeCCW();

	return Profile2D(square);
}
/** </snippet> */
/** <snippet name="fm_create_circle1" lang="cpp"> */
Profile2D createCircle(const double dRadius)
{
  // Create a profile
  Profile2D profile;

  // With one contour
  profile.resize(1);

  // Add first point with bulge == 1 (Arc)
  profile.front().appendVertex(OdGePoint2d::kOrigin + OdGeVector2d::kXAxis * dRadius, 1);

  // Add second point with bulge == 1 (Arc)
  profile.front().appendVertex(OdGePoint2d::kOrigin - OdGeVector2d::kXAxis * dRadius, 1);

  profile.front().setOrientationAt(0, efoFront);
  profile.front().setOrientationAt(1, efoFront);

  // Close contour
  profile.front().setClosed();

  // Make contour outer 
  profile.front().makeCCW();

  return profile;
}
/** </snippet> */

/** <snippet name="fm_create_circle2" lang="cpp"> */
Contour2D createCircle(const OdGePoint2d& center, double dRadius)
{
	const unsigned int iVrt = 2;

	const OdGePoint2d aPoints[iVrt] = {
		center - OdGeVector2d::kXAxis * dRadius,
		center + OdGeVector2d::kXAxis * dRadius,
	};

	const double aBulges[iVrt] = { 1., 1. };

	Contour2D result;
	result.appendVertices(iVrt, aPoints, aBulges);
	result.setClosed();  // Close profile

	return result;
}
/** </snippet> */

void _FMDocProfiles_func(OdEdCommandContext* pCmdCtx)
{
  DeviationParams devParams;
	OdGePoint2d center = OdGePoint2d::kOrigin;
	double dRadius = 10.;
	double dSide = 10.;

	/** <snippet name="fm_oda_create" lang="cpp"> */
	Profile2D circle = Profile2D(Contour2D::createCircle(center, dRadius));
	Profile2D square = Profile2D(Contour2D::createSquare(center, dSide));
	/** </snippet> */

	Profile2D square2 = createSquare(10.);
	Profile2D cicrcle2 = createCircle(10.);
	Contour2D circle3 = createCircle(center, dRadius);
}

