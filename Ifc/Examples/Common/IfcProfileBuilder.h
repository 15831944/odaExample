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

#ifndef _IFC_PROFILE_BUILDER_H
#define _IFC_PROFILE_BUILDER_H

#include "IfcBuilder.h"
#include "daiConsts.h"

class IfcProfileBuilder : public IfcBuilder
{
public:

  enum Type
  {
    kCURVE,
    kAREA
  };

protected:

  static OdSmartPtr<IfcProfileBuilder> createObject(ExIfcModelFiller *filler);

  IfcProfileBuilder()
  {};

public:

  ODRX_DECLARE_MEMBERS(IfcProfileBuilder);

  OdIfc::OdIfcEntityPtr createCartesianTransformationOperator2D(const OdGePoint2d &origin2D);
  OdIfc::OdIfcEntityPtr createCartesianTransformationOperator2D(const OdGePoint2d& origin2D, const OdGeVector2d& axis1, const OdGeVector2d& axis2);

  OdIfc::OdIfcEntityPtr createArbitraryClosedProfileDef(Type type, const OdAnsiString &name, const OdGePoint2dArray &points);
  OdIfc::OdIfcEntityPtr createRectangleProfileDef(Type type, const OdAnsiString &name, double xdim, double ydim);
  OdIfc::OdIfcEntityPtr createCircleProfileDef(Type type, const OdAnsiString &name, double radius);
  OdIfc::OdIfcEntityPtr createIShapeProfileDef(Type type, const OdAnsiString& name, OdDAIObjectId position, double overallWidth, double overallDepth, double webThickness, double flangeThickness);
  OdIfc::OdIfcEntityPtr createCompositeProfileDef(Type type, const OdAnsiString& name, OdDAIObjectIds profileIds);
  OdIfc::OdIfcEntityPtr createDerivedProfileDef(const char *name, OdDAIObjectId parentProfile, OdDAIObjectId transformOperator, const char *label = nullptr);
  OdIfc::OdIfcEntityPtr createAsymmetricIShapeProfileDef(
    Type type, const OdAnsiString& name, OdDAIObjectId position,
    double bottomFlangeWidth,
    double overallDepth,
    double webThickness,
    double bottomFlangeThickness,
    double topFlangeWidth,

    double bottomFlangeFilletRadius = OdDAI::Consts::OdNan,
    double topFlangeThickness = OdDAI::Consts::OdNan,
    double topFlangeFilletRadius = OdDAI::Consts::OdNan,
    double bottomFlangeEdgeRadius = OdDAI::Consts::OdNan,
    double bottomFlangeSlope = OdDAI::Consts::OdNan,
    double topFlangeEdgeRadius = OdDAI::Consts::OdNan,
    double topFlangeSlope = OdDAI::Consts::OdNan
  );
  OdIfc::OdIfcEntityPtr createOpenCrossProfileDef(const OdAnsiString& name, bool horizontalWidths, const OdArray<double>& widths, const OdArray<double>& slopes, const OdArray<OdAnsiString>& tags = OdArray<OdAnsiString>());
  friend class IfcModelFiller;
  friend class IfcRepresentationBuilder;
};
typedef OdSmartPtr<IfcProfileBuilder> IfcProfileBuilderPtr;

#endif // _IFC_PROFILE_BUILDER_H
