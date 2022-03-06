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

#ifndef _IFC_EX_MODEL_FILLER_H
#define _IFC_EX_MODEL_FILLER_H

#include "IfcCore.h"
#include "IfcModel.h"

#include "IfcModelFiller.h"

#include "IfcRepresentationBuilder.h"
#include "IfcAlignmentBuilder.h"
#include "IfcBridgeBuilder.h"
#include "IfcRailwayBuilder.h"
#include "IfcBuildingBuilder.h"
#include "IfcPropertySetFiller.h"
#include "IfcQuantitySetFiller.h"

class ExIfcModelFiller : public OdIfcModelFiller
{
protected:

  std::map<OdIfc::OdIfcEntity*, OdIfc::OdIfcEntity*> m_relAggregates;
  std::map<OdIfc::OdIfcEntity*, OdIfc::OdIfcEntity*> m_relContainedInSpatialStructure;
  std::map<OdIfc::OdIfcEntity*, OdIfc::OdIfcEntity*> m_relDefinesByProperties;
  std::map<OdIfc::OdIfcEntity*, OdIfc::OdIfcEntity*> m_relNests;
  std::map<OdAnsiString, OdIfc::OdIfcEntity*> m_geometricRepresentationContext;

  std::map<OdAnsiString, OdIfc::OdIfcEntity*> m_surfaceStyles;

public:

  ExIfcModelFiller(OdIfcModel *pModel)
    : OdIfcModelFiller(pModel)
  {}

  bool appendId(OdIfc::OdIfcEntity *pInst, OdIfc::OdIfcAttribute attr, OdDAIObjectId id);

  OdIfc::OdIfcEntityPtr fromScratch(
    const OdAnsiString &organizationName = "",
    const OdAnsiString &applicationIdentifier = "",
    const OdArray<OdIfc::OdIfcEntityPtr> &units = OdArray<OdIfc::OdIfcEntityPtr>());

  OdDAI::ApplicationInstancePtr createRooted(const char *typeName, const char *name = nullptr, bool append = true);

  OdIfc::OdIfcEntityPtr appendRelAggregates(OdIfc::OdIfcEntityPtr pRelating, OdIfc::OdIfcEntityPtr pRelated);
  OdIfc::OdIfcEntityPtr addRelAggregates(OdIfc::OdIfcEntityPtr pRelating, OdIfc::OdIfcEntityPtr pRelated);
  OdIfc::OdIfcEntityPtr getRelAggregates(OdIfc::OdIfcEntityPtr pRelating);

  OdIfc::OdIfcEntityPtr appendRelContainedInSpatialStructure(OdIfc::OdIfcEntityPtr pRelating, OdIfc::OdIfcEntityPtr pRelated);
  OdIfc::OdIfcEntityPtr addRelContainedInSpatialStructure(OdIfc::OdIfcEntityPtr pRelating, OdIfc::OdIfcEntityPtr pRelated);
  OdIfc::OdIfcEntityPtr getRelContainedInSpatialStructure(OdIfc::OdIfcEntityPtr pRelating);

  OdIfc::OdIfcEntityPtr addRelNests(OdIfc::OdIfcEntityPtr pRelating, const OdDAIObjectIds &related);
  OdIfc::OdIfcEntityPtr appendRelNests(OdIfc::OdIfcEntityPtr pRelating, OdIfc::OdIfcEntityPtr pRelated);
  OdIfc::OdIfcEntityPtr addRelNests(OdIfc::OdIfcEntityPtr pRelating, OdIfc::OdIfcEntityPtr pRelated);
  OdIfc::OdIfcEntityPtr getRelNests(OdIfc::OdIfcEntityPtr pRelating);

  OdIfc::OdIfcEntityPtr appendRelDefinesByProperties(OdIfc::OdIfcEntityPtr pRelatingPropertyDefinition, OdIfc::OdIfcEntityPtr relatedObjectDefinition);
  OdIfc::OdIfcEntityPtr addRelDefinesByProperties(OdIfc::OdIfcEntityPtr pRelatingPropertyDefinition, OdIfc::OdIfcEntityPtr pRelated);
  OdIfc::OdIfcEntityPtr getRelDefinesByProperties(OdIfc::OdIfcEntityPtr pRelatingPropertyDefinition);

  IfcBridgeBuilderPtr appendBridge(const OdAnsiString &name, IfcBridgeBuilder::Type type);
  IfcPropertySetFillerPtr createPropertySet(OdIfc::OdIfcEntityPtr objectDefinition);
  IfcQuantitySetFillerPtr createQuantitySet(OdIfc::OdIfcEntityPtr objectDefinition);

  OdIfc::OdIfcEntityPtr appendGeometricRepresentationContext(const OdAnsiString &name, const OdAnsiString &type, int dim, double precision = OdDAI::Consts::OdNan, OdDAIObjectId idWCS = OdDAIObjectId(), OdDAIObjectId idTrueNorth = OdDAIObjectId());
  OdIfc::OdIfcEntityPtr getGeometricRepresentationContext(const OdAnsiString &type);

  OdIfc::OdIfcEntityPtr createCartesianPoint3D(const OdGePoint3d &p);
  OdIfc::OdIfcEntityPtr createCartesianPoint2D(const OdGePoint2d &p);
  OdIfc::OdIfcEntityPtr createDirection2D(const OdGeVector2d& d);
  OdIfc::OdIfcEntityPtr createDirection3D(const OdGeVector3d &d);
  OdIfc::OdIfcEntityPtr createVector(OdIfc::OdIfcEntityPtr pDirection, double magnitude);
  OdIfc::OdIfcEntityPtr createLocalPlacement(OdIfc::OdIfcEntityPtr placementRelTo, OdIfc::OdIfcEntityPtr relativePlacement);

  OdIfc::OdIfcEntityPtr createSurfaceStyle(const OdAnsiString &name, const OdCmEntityColor &color);
  OdIfc::OdIfcEntityPtr findSurfaceStyle(const OdAnsiString &name);

  OdIfc::OdIfcEntityPtr createStyledItem(OdIfc::OdIfcEntityPtr item, OdIfc::OdIfcEntityPtr style);

  OdIfc::OdIfcEntityPtr createShapeRepresentation(const OdAnsiString &contextType, const OdAnsiString &name, const OdAnsiString &type);

  OdIfc::OdIfcEntityPtr createAlignmentSegment(OdDAIObjectId nestedSegmentId);

  IfcRepresentationBuilderPtr createRepresentationBuilder(OdIfc::OdIfcEntityPtr pInst);

  // Rail/Road infrastructure
  IfcAlignmentBuilderPtr appendAlignment(const OdAnsiString &name);

  // Railroad Builder
  IfcRailwayBuilderPtr appendRailway(const OdAnsiString &name);
};
typedef OdSharedPtr<ExIfcModelFiller> ExIfcModelFillerPtr;

#endif // _IFC_EX_MODEL_FILLER_H
