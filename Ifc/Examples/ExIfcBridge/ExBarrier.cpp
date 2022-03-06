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
#include "ExBarrier.h"

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

ExBarrierProfile::ExBarrierProfile(ExIfcModelFiller* filler,
                                   const OdAnsiString& name,
                                   double xdim,
                                   double ydim,
                                   double pavementLeftHeight,
                                   double pavementRightHeight,
                                   double depth,
                                   double offsetX,
                                   double offsetY)
{
  if (filler == nullptr)
  {
    ODA_ASSERT(0);
    return;
  }

  IfcProfileBuilderPtr profileBuilder = ExProfileBuilder::createObject(filler);

  double left = -xdim * 0.5 ;
  double right = xdim * 0.5 ;
  double barrierQuarterXDim = xdim * 0.25 ;

  OdGePoint2dArray points;
  points.append(OdGePoint2d(left + offsetX, 0. + offsetY));
  points.append(OdGePoint2d(right + offsetX, 0. + offsetY));
  points.append(OdGePoint2d(right + offsetX, pavementRightHeight + offsetY));
  points.append(OdGePoint2d(barrierQuarterXDim * 0.5 + offsetX, ydim + offsetY));
  points.append(OdGePoint2d(-barrierQuarterXDim * 0.5 + offsetX, ydim + offsetY));
  points.append(OdGePoint2d(left + offsetX, pavementLeftHeight + offsetY));

  m_profile = profileBuilder->createArbitraryClosedProfileDef(IfcProfileBuilder::kAREA, name, points);
  ODA_ASSERT(!m_profile.isNull());
}

OdDAIObjectId ExBarrierProfile::profile() const
{
  return !m_profile.isNull() ? static_cast<OdDAIObjectId>(m_profile->id()) : OdDAI::Utils::getUnset<OdDAIObjectId>();
}

