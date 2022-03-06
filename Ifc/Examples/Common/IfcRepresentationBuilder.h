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

#ifndef _IFC_REPRESENTATION_BUILDER_H
#define _IFC_REPRESENTATION_BUILDER_H

#include "Ge/GeMatrix3d.h"
#include "IfcBuilder.h"
#include "IfcProfileBuilder.h"
#include "IfcIndexedPolycurveBuilder.h"

class OdGeKnotVector;
class IfcRepresentationAdapter;

/** \details

*/
class IfcRepresentationBuilder : public IfcBuilder
{
protected:

  OdIfc::OdIfcEntityPtr m_product;

  static OdSmartPtr<IfcRepresentationBuilder> createObject(ExIfcModelFiller *filler, OdIfc::OdIfcEntityPtr product);

public:

  ODRX_DECLARE_MEMBERS(IfcRepresentationBuilder);

  OdIfc::OdIfcEntityPtr getProduct() { return m_product; };

  OdIfc::OdIfcEntityPtr appendRepresentation(OdIfc::OdIfcEntity *representation, OdIfc::OdIfcEntity *ctx, const OdAnsiString &identifier, const OdAnsiString &type);

  bool process(IfcRepresentationAdapter *adapter);

  OdIfc::OdIfcEntityPtr createIfcBooleanResult(OdIfc::OdIfcEntityPtr blank, OdIfc::OdIfcEntityPtr tool, const char *op);

  OdIfc::OdIfcEntityPtr createExtrudedAreaSolid(OdIfc::OdIfcEntityPtr profileDef, double elevation, const OdGeVector3d &extrudeDirection = OdGeVector3d::kZAxis);
  OdIfc::OdIfcEntityPtr createExtrudedAreaSolid(OdIfc::OdIfcEntityPtr profileDef, double elevation, const OdDAIObjectId &extrudeDirection);

  OdIfc::OdIfcEntityPtr createSweptDiskSolid(OdIfc::OdIfcEntityPtr profileDef, double radiusOuter, double radiusInner = 0., double startParam = OdDAI::Consts::OdNan, double endParam = OdDAI::Consts::OdNan);
  OdIfc::OdIfcEntityPtr createFixedReferenceSweptAreaSolid(OdIfc::OdIfcEntityPtr profileDef, const OdGeMatrix3d &position, OdIfc::OdIfcEntityPtr directrix, double startParam = OdDAI::Consts::OdNan, double endParam = OdDAI::Consts::OdNan, const OdGeVector3d &fixedReference = OdGeVector3d::kXAxis);
  OdIfc::OdIfcEntityPtr createFixedReferenceSweptAreaSolid(OdIfc::OdIfcEntityPtr profileDef, OdIfc::OdIfcEntityPtr position, OdIfc::OdIfcEntityPtr directrix, double startParam, double endParam, const OdDAIObjectId &fixedReference);

  OdDAIObjectIds createPoints(const OdGePoint3dArray& points);
  OdIfc::OdIfcEntityPtr createLine2d(const OdGePoint2d &position, const OdGeVector2d &direction);
  OdIfc::OdIfcEntityPtr createPolyline(OdGePoint3dArray points);
  OdIfc::OdIfcEntityPtr createBSpline(int degree, const OdGePoint3dArray& points, bool isClosed, const OdGeKnotVector& knots, bool isSelfIntersected = false);
  
  OdIfc::OdIfcEntityPtr createBlock(const OdGeMatrix3d &position, double xLength, double yLength, double zLength);
  OdIfc::OdIfcEntityPtr createBlock(OdIfc::OdIfcEntityPtr position, double xLength, double yLength, double zLength);
  
  OdIfc::OdIfcEntityPtr createRectangularPyramid(const OdGeMatrix3d &position, double xLength, double yLength, double height);
  OdIfc::OdIfcEntityPtr createRectangularPyramid(OdIfc::OdIfcEntityPtr position, double xLength, double yLength, double height);

  OdIfc::OdIfcEntityPtr createRightCircularCone(const OdGeMatrix3d &position, double height, double bottomRadius);
  OdIfc::OdIfcEntityPtr createRightCircularCone(OdIfc::OdIfcEntityPtr position, double height, double bottomRadius);

  OdIfc::OdIfcEntityPtr createRightCircularCylinder(const OdGeMatrix3d &position, double height, double radius);
  OdIfc::OdIfcEntityPtr createRightCircularCylinder(OdIfc::OdIfcEntityPtr position, double height, double radius);

  OdIfc::OdIfcEntityPtr createSphere(const OdGeMatrix3d &position, double radius);
  OdIfc::OdIfcEntityPtr createSphere(OdIfc::OdIfcEntityPtr position, double radius);

  OdIfc::OdIfcEntityPtr createInclinedReferenceSweptAreaSolid(
    OdIfc::OdIfcEntityPtr profileDef,
    OdIfc::OdIfcEntityPtr position,
    OdIfc::OdIfcEntityPtr directrix,
    double startDistance,
    double endDistance,
    bool fixedAxisVertical,
    OdIfc::OdIfcEntityPtr inclinating
  );

  IfcIndexedPolycurveBuilderPtr createIndexedPolycurveBuilder();
  
  IfcProfileBuilderPtr createProfileBuilder();

  friend class ExIfcModelFiller;
};
typedef OdSmartPtr<IfcRepresentationBuilder> IfcRepresentationBuilderPtr;

/** \details

*/
class ExIfcModelFiller;
class IfcRepresentationAdapter
{
protected:

  OdGeMatrix3d m_objectPlacement;

  IfcRepresentationBuilderPtr m_b;

  void init(IfcRepresentationBuilderPtr representationBuilder)
  {
    m_b = representationBuilder;
  }

  void uninit()
  {
    m_b.release();
  }

  IfcRepresentationAdapter(const OdGeMatrix3d &objectPlacement)
  {
    m_objectPlacement = objectPlacement;
  };

  IfcRepresentationAdapter() {};

  virtual OdIfc::OdIfcEntityPtr subProcess() = 0;

  void processPlacement();

  bool setStyledItem(OdIfc::OdIfcEntityPtr pInst, const OdAnsiString &styleName);

public:

  virtual ~IfcRepresentationAdapter() {};

  bool process();

  void setObjectPlacement(const OdGeMatrix3d &objectPlacement)
  {
    m_objectPlacement = objectPlacement;
  }

  const OdGeMatrix3d& getObjectPlacement() const
  {
    return m_objectPlacement;
  }

  friend class IfcRepresentationBuilder;
};

#endif // _IFC_REPRESENTATION_BUILDER_H
