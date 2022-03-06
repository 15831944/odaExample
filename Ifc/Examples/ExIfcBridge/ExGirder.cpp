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

#include "ExIfcModelFiller.h"
#include "ExGirder.h"

namespace 
{
  class ExProfileBuilder
    : public IfcProfileBuilder
  {
  public:

    static OdSmartPtr<IfcProfileBuilder> createObject(ExIfcModelFiller* filler)
    {
      return IfcProfileBuilder::createObject(filler);
    }
  };
}

ExGirderProfile::ExGirderProfile(ExIfcModelFiller* filler,
                                 OdAnsiString name,
                                 double xdim,
                                 double ydim,
                                 double plateThickness,
                                 double wingWidth,
                                 double bearingDist,
                                 double bearingXDim)
{
  if (filler == nullptr)
  {
    ODA_ASSERT(0);
    return;
  }

  IfcProfileBuilderPtr profileBuilder = ExProfileBuilder::createObject(filler);

  double left = -xdim * 0.5;
  double right = xdim * 0.5;
  double bearingHalfXDim = bearingXDim * 0.5;

  OdGePoint2dArray points;

  // left bearing
  double leftBearingCenter = -bearingDist;


  points.append(OdGePoint2d(-plateThickness * 1.5, ydim - plateThickness)); // 0
  points.append(OdGePoint2d(-plateThickness * 1.5, ydim - plateThickness * 2)); // 1
  points.append(OdGePoint2d(leftBearingCenter, plateThickness));



  points.append(OdGePoint2d(leftBearingCenter - bearingHalfXDim, ydim - plateThickness));
  points.append(OdGePoint2d(leftBearingCenter - bearingHalfXDim - plateThickness, ydim - plateThickness));

  points.append(OdGePoint2d(leftBearingCenter - bearingHalfXDim, 0.));
  points.append(OdGePoint2d(leftBearingCenter + bearingHalfXDim, 0.));

  // mid
  points.append(OdGePoint2d(-bearingDist * 0.25, ydim * 0.25));
  points.append(OdGePoint2d(-plateThickness * 0.75, ydim - plateThickness * 3));
  points.append(OdGePoint2d(plateThickness * 0.75, ydim - plateThickness * 3));
  points.append(OdGePoint2d(bearingDist * 0.25, ydim * 0.25));

  // right bearing
  double rightBearingCenter = bearingDist;
  points.append(OdGePoint2d(rightBearingCenter - bearingHalfXDim, 0.));
  points.append(OdGePoint2d(rightBearingCenter + bearingHalfXDim, 0.));

  points.append(OdGePoint2d(rightBearingCenter + bearingHalfXDim + plateThickness, ydim - plateThickness));
  points.append(OdGePoint2d(rightBearingCenter + bearingHalfXDim, ydim - plateThickness));

  points.append(OdGePoint2d(rightBearingCenter, plateThickness));
  points.append(OdGePoint2d(plateThickness * 1.5, ydim - plateThickness * 2));
  points.append(OdGePoint2d(plateThickness * 1.5, ydim - plateThickness));

  m_profile = profileBuilder->createArbitraryClosedProfileDef(IfcProfileBuilder::kAREA, name, points);
  
  ODA_ASSERT(!m_profile.isNull());
}

OdDAIObjectId ExGirderProfile::profile() const
{
  return !m_profile.isNull() ? static_cast<OdDAIObjectId>(m_profile->id()) : OdDAI::Utils::getUnset<OdDAIObjectId>();
}

