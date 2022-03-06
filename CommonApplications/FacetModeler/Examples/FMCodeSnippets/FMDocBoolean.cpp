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

using namespace FacetModeler;

/** <snippet name="fm_boolean_ring" lang="cpp"> */
Profile2D createRing(double dMinorRadius, double dMajorRadius)
{
  Profile2D result;

  Profile2D minorCircle = Profile2D(Contour2D::createCircle(OdGePoint2d::kOrigin, dMinorRadius));
  Profile2D majorCircle = Profile2D(Contour2D::createCircle(OdGePoint2d::kOrigin, dMajorRadius));

  Profile2D::PerformOperation(FacetModeler::BooleanOperation::eDifference, majorCircle, minorCircle, result);

  return result;
}
/** </snippet> */

void _FMDocBoolean_func(OdEdCommandContext* pCmdCtx)
{
  Profile2D ring = createRing(5, 10);
}

