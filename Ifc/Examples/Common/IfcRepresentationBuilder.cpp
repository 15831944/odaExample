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
#include "IfcRepresentationBuilder.h"
#include "IfcEntity.h"
#include "daiPrimitive.h"
#include "Ge/GeKnotVector.h"

using namespace OdIfc;

ODRX_CONS_DEFINE_MEMBERS(IfcRepresentationBuilder, IfcBuilder, RXIMPL_CONSTR);

OdSmartPtr<IfcRepresentationBuilder> IfcRepresentationBuilder::createObject(
  ExIfcModelFiller *filler, OdIfc::OdIfcEntityPtr product)
{
  OdSmartPtr<IfcRepresentationBuilder> res = IfcRepresentationBuilder::desc()->create();
  res->setFiller(filler);
  res->m_product = product;
  return res;
}

OdIfc::OdIfcEntityPtr IfcRepresentationBuilder::appendRepresentation(OdIfc::OdIfcEntity *representation, OdIfc::OdIfcEntity *ctx, const OdAnsiString &identifier, const OdAnsiString &type)
{
  if (representation == nullptr || !representation->isKindOf("ifcgeometricrepresentationitem"))
  {
    ODA_ASSERT_ONCE(0);
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfc::OdIfcEntityPtr productDefinitionShape;

  OdDAIObjectId idProductDefinitionShape;
  m_product->getAttr("representation") >> idProductDefinitionShape;

  if (idProductDefinitionShape.isNull())
  {
    productDefinitionShape = filler()->model()->createEntityInstance("ifcproductdefinitionshape");
    idProductDefinitionShape = filler()->model()->appendEntityInstance(productDefinitionShape);
    m_product->putAttr("representation", idProductDefinitionShape);
  }
  else
  {
    productDefinitionShape = idProductDefinitionShape.openObject();
  }

  OdDAI::Aggr *aggr = nullptr;
  productDefinitionShape->getAttr("representations") >> aggr;
  if (aggr == nullptr)
  {
    ODA_ASSERT(aggr);
    return OdIfc::OdIfcEntityPtr();
  }

  if (aggr->isNil())
    aggr->createEmpty();

  OdIfc::OdIfcEntityPtr pSR = filler()->model()->createEntityInstance("ifcshaperepresentation");
  pSR->putAttr("contextofitems", OdDAIObjectId(ctx->id()));
  pSR->putAttr("representationidentifier", identifier);
  pSR->putAttr("representationtype", type);
  filler()->appendId(pSR, OdIfc::kItems, OdDAIObjectId(representation->id()));
  OdDAIObjectId idShapeRepresentation = filler()->model()->appendEntityInstance(pSR);

  OdDAI::List<OdDAIObjectId> *representations = static_cast<OdDAI::List<OdDAIObjectId> *>(aggr);
  representations->addByIndex(representations->getMemberCount(), idShapeRepresentation);

  return pSR;
}

OdIfc::OdIfcEntityPtr IfcRepresentationBuilder::createIfcBooleanResult(OdIfc::OdIfcEntityPtr blank, OdIfc::OdIfcEntityPtr tool, const char *op)
{
  OdIfc::OdIfcEntityPtr booleanResult = filler()->model()->createEntityInstance("ifcbooleanresult");

  OdAnsiString strOperator(op);
  booleanResult->putAttr("operator", strOperator);
  booleanResult->putAttr("firstoperand", OdDAIObjectId(blank->id()));
  booleanResult->putAttr("secondoperand", OdDAIObjectId(tool->id()));
  filler()->model()->appendEntityInstance(booleanResult);
  return booleanResult;
}

OdIfc::OdIfcEntityPtr IfcRepresentationBuilder::createExtrudedAreaSolid(OdIfc::OdIfcEntityPtr profileDef, double depth, const OdGeVector3d &extrudeDirection)
{
  if (profileDef.isNull())
  {
    ODA_ASSERT("Profile definition is null.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (!profileDef->isKindOf(OdIfc::kIfcProfileDef))
  {
    ODA_ASSERT("Not a profile definition.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (extrudeDirection.isZeroLength())
  {
    ODA_ASSERT("Direction is zero length.");
    return OdIfc::OdIfcEntityPtr();
  }
     
  OdIfc::OdIfcEntityPtr directionInst = filler()->createDirection3D(extrudeDirection);
  return createExtrudedAreaSolid(profileDef, depth, OdDAIObjectId(directionInst->id()));
}

OdIfc::OdIfcEntityPtr IfcRepresentationBuilder::createExtrudedAreaSolid(OdIfc::OdIfcEntityPtr profileDef, double depth, const OdDAIObjectId &extrudeDirection)
{
  if (profileDef.isNull())
  {
    ODA_ASSERT("Profile definition is null.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (!profileDef->isKindOf(OdIfc::kIfcProfileDef))
  {
    ODA_ASSERT("Not a profile definition.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (extrudeDirection.isNull())
  {
    ODA_ASSERT("Extrude direction is null.");
    return OdIfc::OdIfcEntityPtr();
  }
  //if (!extrudeDirection->isKindOf(OdIfc::kIfcDirection))
  //{
  //  ODA_ASSERT("Not a direction.");
  //  return OdIfc::OdIfcEntityPtr();
  //}

  OdIfc::OdIfcEntityPtr extrudeBase = filler()->model()->createEntityInstance("ifcextrudedareasolid");
  extrudeBase->putAttr("sweptarea", OdDAIObjectId(profileDef->id()));
  extrudeBase->putAttr("depth", depth);
  extrudeBase->putAttr("extrudeddirection", extrudeDirection);
  OdDAIObjectId idExtrude = filler()->model()->appendEntityInstance(extrudeBase);
  return extrudeBase;
}


OdIfc::OdIfcEntityPtr IfcRepresentationBuilder::createSweptDiskSolid(OdIfc::OdIfcEntityPtr directrix, double radiusOuter, double radiusInner /*= 0.*/, double startParam /*= OdDAI::Consts::OdNan*/, double endParam /*= OdDAI::Consts::OdNan*/)
{
  if (!directrix->isKindOf("ifccurve"))
  {
    ODA_ASSERT("Directrix should be is kind of IfcCurve.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfc::OdIfcEntityPtr sweptDiskSolid = filler()->model()->createEntityInstance("ifcsweptdisksolid");
  sweptDiskSolid->putAttr("directrix", OdDAIObjectId(directrix->id()));
  sweptDiskSolid->putAttr("radius", radiusOuter);
  if (OdNonZero(radiusInner)) {
    sweptDiskSolid->putAttr("innerradius", radiusInner);
  }
  if (!OdDAI::Utils::isUnset(startParam)) {
    sweptDiskSolid->putAttr("startparam", startParam);
  }
  if (!OdDAI::Utils::isUnset(endParam)) {
    sweptDiskSolid->putAttr("endparam", endParam);
  }
  filler()->model()->appendEntityInstance(sweptDiskSolid);
  return sweptDiskSolid;
}

OdIfc::OdIfcEntityPtr IfcRepresentationBuilder::createFixedReferenceSweptAreaSolid(OdIfc::OdIfcEntityPtr profileDef, const OdGeMatrix3d &position, OdIfc::OdIfcEntityPtr directrix, double startParam, double endParam, const OdGeVector3d &fixedReference)
{
  if (profileDef.isNull())
  {
    ODA_ASSERT("Profile definition is null.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (!profileDef->isKindOf(OdIfc::kIfcProfileDef))
  {
    ODA_ASSERT("Not a profile definition.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (directrix.isNull())
  {
    ODA_ASSERT("Directrix is null.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (!directrix->isKindOf(OdIfc::kIfcCurve))
  {
    ODA_ASSERT("Not a directrix.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (fixedReference.isZeroLength())
  {
    ODA_ASSERT("Fixed reference is zero length.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfc::OdIfcEntityPtr positionInst = filler()->createAxis2Placement3D(position);
  OdIfc::OdIfcEntityPtr fixedReferenceInst = filler()->createDirection3D(fixedReference);
  return createFixedReferenceSweptAreaSolid(profileDef, positionInst, directrix, startParam, endParam, OdDAIObjectId(fixedReferenceInst->id()));
}

OdIfc::OdIfcEntityPtr IfcRepresentationBuilder::createFixedReferenceSweptAreaSolid(OdIfc::OdIfcEntityPtr profileDef, OdIfc::OdIfcEntityPtr position, OdIfc::OdIfcEntityPtr directrix, double startParam, double endParam, const OdDAIObjectId &fixedReference)
{
  if (profileDef.isNull())
  {
    ODA_ASSERT("Profile definition is null.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (!profileDef->isKindOf(OdIfc::kIfcProfileDef))
  {
    ODA_ASSERT("Not a profile definition.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (!position.isNull() && !position->isKindOf(OdIfc::kIfcAxis2Placement3D))
  {
    ODA_ASSERT("Not a position.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (directrix.isNull())
  {
    ODA_ASSERT("Directrix is null.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (!directrix->isKindOf(OdIfc::kIfcCurve))
  {
    ODA_ASSERT("Not a directrix.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (fixedReference.isNull())
  {
    ODA_ASSERT("Fixed reference is null.");
    return OdIfc::OdIfcEntityPtr();
  }
  //if (!fixedReference->isKindOf(OdIfc::kIfcDirection))
  //{
  //  ODA_ASSERT("Not a direction.");
  //  return OdIfc::OdIfcEntityPtr();
  //}

  OdIfc::OdIfcEntityPtr sweptArea = filler()->model()->createEntityInstance("ifcfixedreferencesweptareasolid");
  sweptArea->putAttr("sweptarea", OdDAIObjectId(profileDef->id()));
  if (!position.isNull())
    sweptArea->putAttr("position", OdDAIObjectId(position->id()));
  sweptArea->putAttr("directrix", OdDAIObjectId(directrix->id()));
  if (!OdDAI::Utils::isUnset(startParam))
  {
    sweptArea->putAttr("startparam", startParam);
  }
  if (!OdDAI::Utils::isUnset(endParam))
  {
    sweptArea->putAttr("endparam", endParam);
  }
  sweptArea->putAttr("fixedreference", fixedReference);
  filler()->model()->appendEntityInstance(sweptArea);
  return sweptArea;
}

OdIfc::OdIfcEntityPtr IfcRepresentationBuilder::createInclinedReferenceSweptAreaSolid(
  OdIfc::OdIfcEntityPtr profileDef, 
  OdIfc::OdIfcEntityPtr position, 
  OdIfc::OdIfcEntityPtr directrix, 
  double startDistance, 
  double endDistance, 
  bool fixedAxisVertical,
  OdIfc::OdIfcEntityPtr inclinating
  )
{
  if (profileDef.isNull())
  {
    ODA_ASSERT("Profile definition is null.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (!profileDef->isKindOf(OdIfc::kIfcProfileDef))
  {
    ODA_ASSERT("Not a profile definition.");
    return OdIfc::OdIfcEntityPtr();
  }
  // OPTIONAL
  /*if (position.isNull())
  {
    ODA_ASSERT("Position is null.");
    return OdIfc::OdIfcEntityPtr();
  }*/
  if (!position.isNull() && !position->isKindOf(OdIfc::kIfcAxis2Placement3D))
  {
    ODA_ASSERT("Not a position.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (directrix.isNull())
  {
    ODA_ASSERT("Directrix is null.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (!directrix->isKindOf(OdIfc::kIfcCurve))
  {
    ODA_ASSERT("Not a directrix.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (inclinating.isNull())
  {
    ODA_ASSERT("Inclinating is null.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (!inclinating->isKindOf(OdIfc::kIfcAlignment2DCant))
  {
    ODA_ASSERT("Not an inclinating.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfc::OdIfcEntityPtr sweptArea = filler()->model()->createEntityInstance("ifcinclinedreferencesweptareasolid");
  sweptArea->putAttr("sweptarea", OdDAIObjectId(profileDef->id()));
  if (!position.isNull())
    sweptArea->putAttr("position", OdDAIObjectId(position->id()));
  sweptArea->putAttr("directrix", OdDAIObjectId(directrix->id()));

  if (!OdDAI::Utils::isUnset(startDistance))
  {
    sweptArea->putAttr("startdistance", startDistance);
  }
  if (!OdDAI::Utils::isUnset(endDistance))
  {
    sweptArea->putAttr("enddistance", endDistance);
  }

  sweptArea->putAttr("inclinating", OdDAIObjectId(inclinating->id()));
  filler()->model()->appendEntityInstance(sweptArea);
  return sweptArea;
}

OdDAIObjectIds IfcRepresentationBuilder::createPoints(const OdGePoint3dArray& points)
{
  OdDAIObjectIds idsPoints(points.size());
  for (OdGePoint3dArray::const_iterator it = points.begin(), end = points.end();
    it < end; ++it)
  {
    idsPoints.append(filler()->createCartesianPoint3D(*it)->id());
  }
  return idsPoints;
}

OdIfc::OdIfcEntityPtr IfcRepresentationBuilder::createLine2d(const OdGePoint2d &pnt, const OdGeVector2d &dir)
{
  OdIfc::OdIfcEntityPtr _pnt = filler()->createCartesianPoint2D(pnt);
  OdIfc::OdIfcEntityPtr _dir = filler()->createVector(filler()->createDirection2D(dir), 1.);

  OdIfc::OdIfcEntityPtr line = filler()->model()->createEntityInstance("ifcline");
  line->putAttr("pnt", OdDAIObjectId(_pnt->id()));
  line->putAttr("dir", OdDAIObjectId(_dir->id()));
  filler()->model()->appendEntityInstance(line);
  return line;
}

OdIfc::OdIfcEntityPtr IfcRepresentationBuilder::createPolyline(OdGePoint3dArray points)
{
  if (points.size() < 2)
  {
    ODA_ASSERT("Not enough points to create polyline.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdDAIObjectIds idsPoints = createPoints(points);

  OdIfc::OdIfcEntityPtr polyline = filler()->model()->createEntityInstance("ifcpolyline");
  polyline->putAttr("points", idsPoints);
  filler()->model()->appendEntityInstance(polyline);
  return polyline;
}

OdIfc::OdIfcEntityPtr IfcRepresentationBuilder::createBSpline(int degree, const OdGePoint3dArray& points, bool isClosed, const OdGeKnotVector& knots, bool isSelfIntersected /*= false*/)
{
  // IfcBSplineCurve
  // 1. Degree IfcInteger
  // 2. ControlPointsList IfcCartesianPoint
  // 3. CurveForm IfcBSplineCurveForm
  // 4. ClosedCurve IfcLogical
  // 5. SelfIntersect IfcLogical
  // IfcBSplineCurveWithKnots
  // 6. KnotMultiplicities IfcInteger
  // 7. Knots IfcParameterValue
  // 8. KnotSpec IfcKnotType

  OdDAIObjectIds idsPoints = createPoints(points);

  OdIfc::OdIfcEntityPtr bspline = filler()->model()->createEntityInstance("ifcbsplinecurvewithknots");

  bspline->putAttr("degree", degree);
  bspline->putAttr("controlpointslist", idsPoints);
  bspline->putAttr("curveform", OdAnsiString("UNSPECIFIED"));
  bspline->putAttr("closedcurve", OdDAI::Logical(isClosed ? OdDAI::kLogical_T : OdDAI::kLogical_F));
  bspline->putAttr("selfintersect", OdDAI::Logical(isSelfIntersected ? OdDAI::kLogical_T : OdDAI::kLogical_F));

  OdArray<double> knotVals;
  OdArray<int> knotMultiplicities;
  if (knots.isEmpty()) {
    const int pointCount(points.size());
    const int uniqCount = pointCount - degree + 1;
    knotMultiplicities.resize(uniqCount, 1);
    knotMultiplicities[0] = knotMultiplicities[uniqCount - 1] = degree + 1;
    knotVals.reserve(uniqCount);
    for (int k = 0; k < uniqCount; ++k) {
      knotVals.append(k);
    }
  } else {
    OdGeDoubleArray _knotVals;
    OdGeIntArray _knotMultiplicities;
    knots.getDistinctKnots(_knotVals, &_knotMultiplicities);
    knotVals.assign(_knotVals.asArrayPtr(), _knotVals.asArrayPtr() + _knotVals.size());
    knotMultiplicities.assign(_knotMultiplicities.asArrayPtr(), _knotMultiplicities.asArrayPtr() + _knotVals.size());
  }

  bspline->putAttr("knotmultiplicities", knotMultiplicities);
  bspline->putAttr("knots", knotVals);
  bspline->putAttr("knotspec", OdAnsiString("UNSPECIFIED"));
  
  filler()->model()->appendEntityInstance(bspline);
  return bspline;
}

OdIfc::OdIfcEntityPtr IfcRepresentationBuilder::createBlock(const OdGeMatrix3d &position, double xLength, double yLength, double zLength)
{
  if (xLength <= 0)
  {
    ODA_ASSERT("X length is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (yLength <= 0)
  {
    ODA_ASSERT("Y length is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (zLength <= 0)
  {
    ODA_ASSERT("Z length is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfc::OdIfcEntityPtr positionInst = filler()->createAxis2Placement3D(position);
  return createBlock(positionInst, xLength, yLength, zLength);
}

OdIfc::OdIfcEntityPtr IfcRepresentationBuilder::createBlock(OdIfc::OdIfcEntityPtr position, double xLength, double yLength, double zLength)
{
  if (position.isNull())
  {
    ODA_ASSERT("Position is null.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (!position->isKindOf(OdIfc::kIfcAxis2Placement3D))
  {
    ODA_ASSERT("Not a position.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (xLength <= 0)
  {
    ODA_ASSERT("X length is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (yLength <= 0)
  {
    ODA_ASSERT("Y length is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (zLength <= 0)
  {
    ODA_ASSERT("Z length is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }
  
  OdIfc::OdIfcEntityPtr block = filler()->model()->createEntityInstance("ifcblock");
  block->putAttr("position", OdDAIObjectId(position->id()));
  block->putAttr("xlength", xLength);
  block->putAttr("ylength", yLength);
  block->putAttr("zlength", zLength);
  filler()->model()->appendEntityInstance(block);
  return block;
}

OdIfc::OdIfcEntityPtr IfcRepresentationBuilder::createRectangularPyramid(const OdGeMatrix3d &position, double xLength, double yLength, double height)
{
  if (xLength <= 0)
  {
    ODA_ASSERT("X length is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (yLength <= 0)
  {
    ODA_ASSERT("Y length is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (height <= 0)
  {
    ODA_ASSERT("Height is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfc::OdIfcEntityPtr positionInst = filler()->createAxis2Placement3D(position);
  return createRectangularPyramid(positionInst, xLength, yLength, height);
}

OdIfc::OdIfcEntityPtr IfcRepresentationBuilder::createRectangularPyramid(OdIfc::OdIfcEntityPtr position, double xLength, double yLength, double height)
{
  if (position.isNull())
  {
    ODA_ASSERT("Position is null.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (!position->isKindOf(OdIfc::kIfcAxis2Placement3D))
  {
    ODA_ASSERT("Not a position.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (xLength <= 0)
  {
    ODA_ASSERT("X length is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (yLength <= 0)
  {
    ODA_ASSERT("Y length is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (height <= 0)
  {
    ODA_ASSERT("Height is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfc::OdIfcEntityPtr rectangularPyramid = filler()->model()->createEntityInstance("ifcrectangularpyramid");
  rectangularPyramid->putAttr("position", OdDAIObjectId(position->id()));
  rectangularPyramid->putAttr("xlength", xLength);
  rectangularPyramid->putAttr("ylength", yLength);
  rectangularPyramid->putAttr("height", height);
  filler()->model()->appendEntityInstance(rectangularPyramid);
  return rectangularPyramid;
}

OdIfc::OdIfcEntityPtr IfcRepresentationBuilder::createRightCircularCone(const OdGeMatrix3d &position, double height, double bottomRadius)
{
  if (height <= 0)
  {
    ODA_ASSERT("Height is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (bottomRadius <= 0)
  {
    ODA_ASSERT("Bottom radius is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfc::OdIfcEntityPtr positionInst = filler()->createAxis2Placement3D(position);
  return createRightCircularCone(positionInst, height, bottomRadius);
}

OdIfc::OdIfcEntityPtr IfcRepresentationBuilder::createRightCircularCone(OdIfc::OdIfcEntityPtr position, double height, double bottomRadius)
{
  if (position.isNull())
  {
    ODA_ASSERT("Position is null.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (!position->isKindOf(OdIfc::kIfcAxis2Placement3D))
  {
    ODA_ASSERT("Not a position.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (height <= 0)
  {
    ODA_ASSERT("Height is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (bottomRadius <= 0)
  {
    ODA_ASSERT("Bottom radius is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfc::OdIfcEntityPtr rightCircularCone = filler()->model()->createEntityInstance("ifcrightcircularcone");
  rightCircularCone->putAttr("position", OdDAIObjectId(position->id()));
  rightCircularCone->putAttr("height", height);
  rightCircularCone->putAttr("bottomradius", bottomRadius);
  filler()->model()->appendEntityInstance(rightCircularCone);
  return rightCircularCone;
}

OdIfc::OdIfcEntityPtr IfcRepresentationBuilder::createRightCircularCylinder(const OdGeMatrix3d &position, double height, double radius)
{
  if (height <= 0)
  {
    ODA_ASSERT("Height is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (radius <= 0)
  {
    ODA_ASSERT("Radius is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfc::OdIfcEntityPtr positionInst = filler()->createAxis2Placement3D(position);
  return createRightCircularCylinder(positionInst, height, radius);
}

OdIfc::OdIfcEntityPtr IfcRepresentationBuilder::createRightCircularCylinder(OdIfc::OdIfcEntityPtr position, double height, double radius)
{
  if (position.isNull())
  {
    ODA_ASSERT("Position is null.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (!position->isKindOf(OdIfc::kIfcAxis2Placement3D))
  {
    ODA_ASSERT("Not a position.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (height <= 0)
  {
    ODA_ASSERT("Height is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (radius <= 0)
  {
    ODA_ASSERT("Radius is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfc::OdIfcEntityPtr rightCircularCylinder = filler()->model()->createEntityInstance("ifcrightcircularcylinder");
  rightCircularCylinder->putAttr("position", OdDAIObjectId(position->id()));
  rightCircularCylinder->putAttr("height", height);
  rightCircularCylinder->putAttr("radius", radius);
  filler()->model()->appendEntityInstance(rightCircularCylinder);
  return rightCircularCylinder;
}

OdIfc::OdIfcEntityPtr IfcRepresentationBuilder::createSphere(const OdGeMatrix3d &position, double radius)
{
  if (radius <= 0)
  {
    ODA_ASSERT("Radius is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfc::OdIfcEntityPtr positionInst = filler()->createAxis2Placement3D(position);
  return createSphere(positionInst, radius);
}

OdIfc::OdIfcEntityPtr IfcRepresentationBuilder::createSphere(OdIfc::OdIfcEntityPtr position, double radius)
{
  if (position.isNull())
  {
    ODA_ASSERT("Position is null.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (!position->isKindOf(OdIfc::kIfcAxis2Placement3D))
  {
    ODA_ASSERT("Not a position.");
    return OdIfc::OdIfcEntityPtr();
  }
  if (radius <= 0)
  {
    ODA_ASSERT("Radius is less than or equal to zero.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfc::OdIfcEntityPtr sphere = filler()->model()->createEntityInstance("ifcsphere");
  sphere->putAttr("position", OdDAIObjectId(position->id()));
  sphere->putAttr("radius", radius);
  filler()->model()->appendEntityInstance(sphere);
  return sphere;
}

IfcProfileBuilderPtr IfcRepresentationBuilder::createProfileBuilder()
{
  return IfcProfileBuilder::createObject(filler());
}

IfcIndexedPolycurveBuilderPtr IfcRepresentationBuilder::createIndexedPolycurveBuilder()
{
  return IfcIndexedPolycurveBuilder::createObject(filler());
}

bool IfcRepresentationBuilder::process(IfcRepresentationAdapter *adapter)
{
  bool res = false;
  try
  {
    adapter->init(this);
    res = adapter->process();
  }
  catch (...)
  {
    ODA_ASSERT("Adapter export failed.");
  }
  adapter->uninit();
  return res;
}

void IfcRepresentationAdapter::processPlacement()
{
  OdIfc::OdIfcEntityPtr pProduct = m_b->getProduct();

  OdIfc::OdIfcEntityPtr relativePlacement = m_b->filler()->createAxis2Placement3D(m_objectPlacement);

  OdIfc::OdIfcEntityPtr objectPlacement;
  OdDAIObjectId id;
  if (pProduct->getAttr("objectplacement") >> id)
  {
    OdIfc::OdIfcEntityPtr objectPlacement = id.openObject();
    objectPlacement->putAttr("relativeplacement", OdDAIObjectId(relativePlacement->id()));
  }
  else
  {
    objectPlacement = m_b->filler()->createLocalPlacement(OdIfc::OdIfcEntityPtr(), relativePlacement);
    m_b->getProduct()->putAttr("objectplacement", OdDAIObjectId(objectPlacement->id()));
  }
}

bool IfcRepresentationAdapter::setStyledItem(OdIfc::OdIfcEntityPtr pInst, const OdAnsiString &styleName)
{
  OdIfc::OdIfcEntityPtr surfaceStyle = m_b->filler()->findSurfaceStyle(styleName);
  if (surfaceStyle.isNull())
    return false;
  return !m_b->filler()->createStyledItem(pInst, surfaceStyle).isNull();
}

bool IfcRepresentationAdapter::process()
{
  OdIfc::OdIfcEntityPtr shapeRepresentation = subProcess();
  if (shapeRepresentation.isNull())
    return false;

  OdIfcModelPtr model = m_b->filler()->model();
  OdIfc::OdIfcEntityPtr pInst = model->createEntityInstance("ifcproductdefinitionshape");
  m_b->filler()->appendId(pInst, OdIfc::kRepresentations, OdDAIObjectId(shapeRepresentation->id()));
  OdDAIObjectId idPDS = model->appendEntityInstance(pInst);

  processPlacement();
  m_b->getProduct()->putAttr("representation", idPDS);
  return true;
}
