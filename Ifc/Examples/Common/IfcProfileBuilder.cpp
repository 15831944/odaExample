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
#include "IfcProfileBuilder.h"
#include "IfcEntity.h"
#include "daiUtils/daiUnset.h"

using namespace OdIfc;

ODRX_CONS_DEFINE_MEMBERS(IfcProfileBuilder, IfcBuilder, RXIMPL_CONSTR);

namespace {

  static char* profileDefTypes[] = {
    "CURVE",
    "AREA"
  };

}

OdSmartPtr<IfcProfileBuilder> IfcProfileBuilder::createObject(ExIfcModelFiller *filler)
{
  OdSmartPtr<IfcProfileBuilder> res = IfcProfileBuilder::desc()->create();
  res->setFiller(filler);
  return res;
}

OdIfc::OdIfcEntityPtr IfcProfileBuilder::createCartesianTransformationOperator2D(const OdGePoint2d &origin2D)
{
  OdIfc::OdIfcEntityPtr localOrigin = filler()->createCartesianPoint2D(origin2D);
  // filler()->model()->appendEntityInstance(localOrigin);

  OdIfc::OdIfcEntityPtr transformationOperator2D = filler()->model()->createEntityInstance("ifccartesiantransformationoperator2d");
  transformationOperator2D->putAttr(kLocalOrigin, OdDAIObjectId(localOrigin->id()));

  filler()->model()->appendEntityInstance(transformationOperator2D);
  return transformationOperator2D;
}

OdIfc::OdIfcEntityPtr IfcProfileBuilder::createCartesianTransformationOperator2D(const OdGePoint2d& origin2D, const OdGeVector2d& axis1, const OdGeVector2d& axis2)
{
  OdIfc::OdIfcEntityPtr localAxis1 = filler()->createDirection2D(axis1);
  OdIfc::OdIfcEntityPtr localAxis2 = filler()->createDirection2D(axis2);

  OdIfc::OdIfcEntityPtr transformationOperator2D = createCartesianTransformationOperator2D(origin2D);

  transformationOperator2D->putAttr(kAxis1, OdDAIObjectId(localAxis1->id()));
  transformationOperator2D->putAttr(kAxis2, OdDAIObjectId(localAxis2->id()));

  return transformationOperator2D;
}

OdIfc::OdIfcEntityPtr IfcProfileBuilder::createRectangleProfileDef(Type type, const OdAnsiString &name, double xdim, double ydim)
{
  OdIfc::OdIfcEntityPtr profileDef = filler()->model()->createEntityInstance("ifcrectangleprofiledef");

  OdAnsiString strProfileType = profileDefTypes[type];

  profileDef->putAttr("profiletype", strProfileType);
  profileDef->putAttr("profilename", name);
  profileDef->putAttr("xdim", xdim);
  profileDef->putAttr("ydim", ydim);

  filler()->model()->appendEntityInstance(profileDef);
  return profileDef;
}

OdIfc::OdIfcEntityPtr IfcProfileBuilder::createCircleProfileDef(Type type, const OdAnsiString &name, double radius)
{
  OdIfc::OdIfcEntityPtr profileDef = filler()->model()->createEntityInstance("ifccircleprofiledef");

  OdAnsiString strProfileType = profileDefTypes[type];

  profileDef->putAttr("profiletype", strProfileType);
  profileDef->putAttr("profilename", name);
  profileDef->putAttr("radius", radius);

  filler()->model()->appendEntityInstance(profileDef);
  return profileDef;
}

OdIfc::OdIfcEntityPtr IfcProfileBuilder::createIShapeProfileDef(Type type, const OdAnsiString& name, OdDAIObjectId position, double overallWidth, double overallDepth, double webThickness, double flangeThickness)
{
  OdIfc::OdIfcEntityPtr pProfileDef = filler()->model()->createEntityInstance("ifcishapeprofiledef");

  OdAnsiString strProfileType = profileDefTypes[type];

  pProfileDef->putAttr("profiletype", strProfileType);
  pProfileDef->putAttr("profilename", name);
  pProfileDef->putAttr("position", position);
  pProfileDef->putAttr("webthickness", webThickness);
  pProfileDef->putAttr("flangethickness", flangeThickness);
  pProfileDef->putAttr("overallwidth", overallWidth);
  pProfileDef->putAttr("overalldepth", overallDepth);

  filler()->model()->appendEntityInstance(pProfileDef);

  return pProfileDef;
}

OdIfc::OdIfcEntityPtr IfcProfileBuilder::createAsymmetricIShapeProfileDef(
  Type type, const OdAnsiString& name, OdDAIObjectId position,
  double bottomFlangeWidth,
  double overallDepth,
  double webThickness,
  double bottomFlangeThickness,
  double topFlangeWidth,

  double bottomFlangeFilletRadius /* = OdDAI::Consts::OdNan */,
  double topFlangeThickness /* = OdDAI::Consts::OdNan */,
  double topFlangeFilletRadius /* = OdDAI::Consts::OdNan */,
  double bottomFlangeEdgeRadius /* = OdDAI::Consts::OdNan */,
  double bottomFlangeSlope /* = OdDAI::Consts::OdNan */,
  double topFlangeEdgeRadius /* = OdDAI::Consts::OdNan */,
  double topFlangeSlope /* = OdDAI::Consts::OdNan */
)
{
  OdIfc::OdIfcEntityPtr pProfileDef = filler()->model()->createEntityInstance("ifcasymmetricishapeprofiledef");

  OdAnsiString strProfileType = profileDefTypes[type];

  pProfileDef->putAttr("profiletype", strProfileType);
  pProfileDef->putAttr("profilename", name);
  pProfileDef->putAttr("position", position);
  
  pProfileDef->putAttr("bottomflangewidth", bottomFlangeWidth);
  pProfileDef->putAttr("overalldepth", overallDepth);
  pProfileDef->putAttr("webthickness", webThickness);
  pProfileDef->putAttr("bottomflangethickness", bottomFlangeThickness);
  pProfileDef->putAttr("topflangewidth", topFlangeWidth);

  if (!OdDAI::Utils::isUnset(bottomFlangeFilletRadius))
    pProfileDef->putAttr("bottomflangefilletradius", bottomFlangeFilletRadius);
  if (!OdDAI::Utils::isUnset(topFlangeThickness))
    pProfileDef->putAttr("topflangethickness", topFlangeThickness);
  if (!OdDAI::Utils::isUnset(topFlangeFilletRadius))
    pProfileDef->putAttr("topflangefilletradius", topFlangeFilletRadius);
  if (!OdDAI::Utils::isUnset(bottomFlangeEdgeRadius))
    pProfileDef->putAttr("bottomflangeedgeradius", bottomFlangeEdgeRadius);
  if (!OdDAI::Utils::isUnset(bottomFlangeSlope))
    pProfileDef->putAttr("bottomflangeslope", bottomFlangeSlope);
  if (!OdDAI::Utils::isUnset(topFlangeEdgeRadius))
    pProfileDef->putAttr("topflangeedgeradius", topFlangeEdgeRadius);
  if (!OdDAI::Utils::isUnset(topFlangeSlope))
    pProfileDef->putAttr("topflangeslope", topFlangeSlope);

  filler()->model()->appendEntityInstance(pProfileDef);

  return pProfileDef;
}

OdIfc::OdIfcEntityPtr IfcProfileBuilder::createOpenCrossProfileDef(const OdAnsiString& name, bool horizontalWidths, const OdArray<double>& widths, const OdArray<double>& slopes, const OdArray<OdAnsiString>& tags)
{
  if (widths.length() < 1 || widths.length() != slopes.length() || (!tags.empty() && (widths.length() != tags.length() + 1)))
  {
    ODA_ASSERT_ONCE(!"Invalid OpenCrossProfileDef parametrs");
    return OdIfc::OdIfcEntityPtr();
  }
  OdIfc::OdIfcEntityPtr pProfileDef = filler()->model()->createEntityInstance("ifcopencrossprofiledef");

  OdAnsiString strProfileType = profileDefTypes[0];

  OdDAI::DoubleList* widthsAttr;
  OdDAI::DoubleList* slopesAttr;

  pProfileDef->putAttr("profiletype", strProfileType);
  if (!name.isEmpty())
    pProfileDef->putAttr("profilename", name);
  pProfileDef->putAttr("horizontalwidths", horizontalWidths);
  pProfileDef->getAttr("widths") >> widthsAttr;
  pProfileDef->getAttr("slopes") >> slopesAttr;

  widthsAttr->createEmpty();
  widthsAttr->setArray(widths);
  slopesAttr->createEmpty();
  slopesAttr->setArray(slopes);

  if (!tags.empty())
  {
    OdDAI::OdAnsiStringList* tagsAttr;
    pProfileDef->getAttr("tags") >> tagsAttr;

    tagsAttr->createEmpty();
    tagsAttr->setArray(tags);
  }

  filler()->model()->appendEntityInstance(pProfileDef);

  return pProfileDef;
}

OdIfc::OdIfcEntityPtr IfcProfileBuilder::createCompositeProfileDef(Type type, const OdAnsiString& name, OdDAIObjectIds profileIds)
{
  OdIfc::OdIfcEntityPtr pProfileDef = filler()->model()->createEntityInstance("ifccompositeprofiledef");

  OdAnsiString strProfileType = profileDefTypes[type];

  pProfileDef->putAttr("profiletype", strProfileType);
  pProfileDef->putAttr("profilename", name);
  pProfileDef->putAttr("profiles", profileIds);

  filler()->model()->appendEntityInstance(pProfileDef);

  return pProfileDef;
}

OdIfc::OdIfcEntityPtr IfcProfileBuilder::createDerivedProfileDef(const char *name, OdDAIObjectId parentProfile, OdDAIObjectId transformOperator, const char *label)
{
  ODA_ASSERT(transformOperator.isValid());

  OdIfc::OdIfcEntityPtr profileDef = filler()->model()->createEntityInstance("ifcderivedprofiledef");

  OdIfc::OdIfcEntityPtr pParentProfile = parentProfile.openObject();

  const char *strProfileType = nullptr;
  pParentProfile->getAttr("profiletype") >> strProfileType;

  profileDef->putAttr("profiletype", strProfileType);
  profileDef->putAttr("profilename", name);
  profileDef->putAttr("parentprofile", parentProfile);
  profileDef->putAttr("operator", transformOperator);
  if (label)
    profileDef->putAttr("label", label);

  filler()->model()->appendEntityInstance(profileDef);
  return profileDef;
}

OdIfc::OdIfcEntityPtr IfcProfileBuilder::createArbitraryClosedProfileDef(Type type, const OdAnsiString &name, const OdGePoint2dArray &points)
{
  if (points.size() < 3)
    return OdIfc::OdIfcEntityPtr();

  OdIfc::OdIfcEntityPtr profileDef = filler()->model()->createEntityInstance("ifcarbitraryclosedprofiledef");

  OdAnsiString strProfileType = profileDefTypes[type];

  profileDef->putAttr("profiletype", strProfileType);
  profileDef->putAttr("profilename", name);

  OdDAIObjectIds idsPoints(points.size());
  for (OdGePoint2dArray::const_iterator it = points.begin(), end = points.end();
    it != end; ++it)
  {
    idsPoints.append(appendPoint(*it)->id());
  }

  // Closed profile should be closed!
  if (points[0] != points[points.size() - 1])
    idsPoints.append(idsPoints[0]);

  OdIfc::OdIfcEntityPtr polyline = filler()->model()->createEntityInstance("ifcpolyline");
  polyline->putAttr(OdIfc::kPoints, idsPoints);
  OdDAIObjectId idPolyline = filler()->model()->appendEntityInstance(polyline);
  profileDef->putAttr("outercurve", idPolyline);
  
  filler()->model()->appendEntityInstance(profileDef);
  return profileDef;
}
