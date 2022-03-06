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

#include <iostream>
#include "ExIfcTutorial_03.h"
#include "ModelInitializer.h"
#include "Ifc4/Ifc4SelectTypes.h"
#include "Ifc4/IfcCartesianPointList3DAutoImpl.h"
#include "Ifc4/IfcIndexedPolyCurveAutoImpl.h"
#include "Ifc4/IfcColourRgbAutoImpl.h"
#include "Ifc4/IfcSurfaceStyleRenderingAutoImpl.h"
#include "Ifc4/IfcSurfaceStyleAutoImpl.h"
#include "Ifc4/IfcSiteAutoImpl.h"
#include "Ifc4/IfcBuildingAutoImpl.h"
#include "Ifc4/IfcBuildingStoreyAutoImpl.h"
#include "Ifc4/IfcColumnAutoImpl.h"
#include "Ifc4/IfcArbitraryClosedProfileDefAutoImpl.h"
#include "Ifc4/IfcExtrudedAreaSolidAutoImpl.h"
#include "Ifc4/IfcStyledItemAutoImpl.h"
#include "Ifc4/IfcShapeRepresentationAutoImpl.h"
#include "Ifc4/IfcProductDefinitionShapeAutoImpl.h"
#include "Ifc4/IfcSweptDiskSolidAutoImpl.h"

using namespace OdIfc;
using namespace OdDAI;

void addLine(int segemntOrder, 
             OdDAI::ListSelect<OdIfc4::IfcSegmentIndexSelectTypeProvider>& segments,
             int startLineIndex, 
             int endLineIndex)
{
  OdArray<int> indices;
  indices.push_back(startLineIndex);
  indices.push_back(endLineIndex);

  auto lineIndexSelect = OdIfc4::IfcSegmentIndexSelect::createEmptySelect();
  OdIfc4::IfcSegmentIndexSelect lineIndexSelectWrapper(lineIndexSelect);
  lineIndexSelectWrapper.setIfcLineIndex(indices);
  segments.putByIndex<OdDAI::Select>(segemntOrder, lineIndexSelect);
}

void addArc(int segemntOrder,
             OdDAI::ListSelect<OdIfc4::IfcSegmentIndexSelectTypeProvider>& segments,
             int startArcIndex,
             int midArcIndex,
             int endArcIndex)
{
  OdArray<int> indices;
  indices.push_back(startArcIndex);
  indices.push_back(midArcIndex);
  indices.push_back(endArcIndex);

  auto lineIndexSelect = OdIfc4::IfcSegmentIndexSelect::createEmptySelect();
  OdIfc4::IfcSegmentIndexSelect arcIndexSelectWrapper(lineIndexSelect);
  arcIndexSelectWrapper.setIfcArcIndex(indices);
  segments.putByIndex<OdDAI::Select>(segemntOrder, lineIndexSelect);
}

int Tutorial_03(int argc, wchar_t* argv[], const MyServices &svcs)
{
  auto ifcFile = svcs.createDatabase(kScmIfc4);
  ModelInitializer modelCreator(ifcFile, 3);
  auto model = modelCreator.model();

  // Material
  auto colourRGB = OdIfc4::IfcColourRgb::createObject();
  colourRGB->setName("Green");
  colourRGB->setRed(0);
  colourRGB->setGreen(1);
  colourRGB->setBlue(0);
  auto idColourRGB = model->appendEntityInstance(colourRGB);

  auto surfaceStyleRendering = OdIfc4::IfcSurfaceStyleRendering::createObject();
  surfaceStyleRendering->setSurfaceColour(idColourRGB);
  surfaceStyleRendering->setReflectanceMethod(OdIfc4::IfcReflectanceMethodEnum::kIfcReflectanceMethodEnum_NOTDEFINED);
  auto idSurfaceStyleRendering = model->appendEntityInstance(surfaceStyleRendering);

  auto surfaceStyle = OdIfc4::IfcSurfaceStyle::createObject();
  surfaceStyle->setName("Style for columns");
  surfaceStyle->setSide(OdIfc4::IfcSurfaceSide::kIfcSurfaceSide_POSITIVE);
  auto& styles = surfaceStyle->styles();
  styles.createEmpty();
  auto selecToAdd = OdIfc4::IfcSurfaceStyleElementSelect::createEmptySelect();
  OdIfc4::IfcSurfaceStyleElementSelect  selecToAddWrapper(selecToAdd);
  selecToAddWrapper.setIfcSurfaceStyleShading(surfaceStyleRendering);
  styles.Add(selecToAdd);
  auto idSurfaceStyle = model->appendEntityInstance(surfaceStyle);

  // Spatial structure

  auto site = OdIfc4::IfcSite::createObject();
  site->setName("Site");
  auto idSite = appendSpatialChild(model, modelCreator.idProject(), site, modelCreator.idOwnerHistory());

  auto building = OdIfc4::IfcBuilding::createObject();
  building->setName("Building");
  auto idBuilding = appendSpatialChild(model, idSite, building, modelCreator.idOwnerHistory());

  auto buildingStorey = OdIfc4::IfcBuildingStorey::createObject();
  buildingStorey->setName("Floor 0");
  auto idBuildingStorey = appendSpatialChild(model, idBuilding, buildingStorey, modelCreator.idOwnerHistory());

  // Spatial containment

  auto column = OdIfc4::IfcColumn::createObject();
  column->setName("Tube");
  auto idColumn = appendContained(model, idBuildingStorey, column, modelCreator.idOwnerHistory());

  // IfcCartesianPointList3d
  auto cartesianpointlist3d = OdIfc4::IfcCartesianPointList3D::createObject();
  model->appendEntityInstance(cartesianpointlist3d);

  auto& coordList = cartesianpointlist3d->coordList();
  coordList.createEmpty();

  struct {
    double x;
    double y;
  }
  points[] = {
    { 100.0, 0.0 },
    { 100., 200.0 },
    { 129.3, 270.7 },
    { 200.0, 300.0 },
    { 300.0, 300.0 },
    { 370.7, 329.3 },
    { 400.0, 400.0 },
  };

  int nextIndex = 0;



  for (auto& point : points)
  {
    OdDAI::Aggr* pointsAggr;
    coordList.addAggregateInstanceByIndex(nextIndex, pointsAggr);

    auto pointsList = reinterpret_cast<OdDAI::DoubleList*>(pointsAggr);

    pointsList->createEmpty();
    pointsList->putByIndex(0, point.x);
    pointsList->putByIndex(1, point.y);
    pointsList->putByIndex(2, 0.);

    ++nextIndex;
  }

  ///indices.push_back(1);

  // IfcIndexedPolycurve
  auto indexedPolycurve = OdIfc4::IfcIndexedPolyCurve::createObject();
  auto idIndexedPolycurve = model->appendEntityInstance(indexedPolycurve);

  indexedPolycurve->setPoints(cartesianpointlist3d->id());

  auto& segments = indexedPolycurve->segments();
  segments.createEmpty();

  addLine(0, segments, 1, 2);
  addArc(1, segments, 2, 3, 4);
  addLine(2, segments, 4, 5);
  addArc(3, segments, 5, 6, 7);
  

  // Geometrical representation
  auto sweptAreaSolid = OdIfc4::IfcSweptDiskSolid::createObject();
  sweptAreaSolid->setRadius(10.);
  sweptAreaSolid->setInnerRadius(7.);
  sweptAreaSolid->setDirectrix(idIndexedPolycurve);
  auto idSweptAreasolid = model->appendEntityInstance(sweptAreaSolid);

  // Style assignment to Swept Disk Solid
  auto styledItem = OdIfc4::IfcStyledItem::createObject();
  styledItem->setItem(idSweptAreasolid);
  styledItem->styles().createEmpty();
  auto styleSelect = OdIfc4::IfcStyleAssignmentSelect::createEmptySelect();
  OdIfc4::IfcStyleAssignmentSelect  styleSelectWrapper(styleSelect);
  styleSelectWrapper.setIfcPresentationStyle(surfaceStyle);
  styledItem->styles().Add(styleSelect); // Aggregation of Selects
  auto idStyledItem = model->appendEntityInstance(styledItem);

  auto shapeRepresentation = OdIfc4::IfcShapeRepresentation::createObject();
  shapeRepresentation->setContextOfItems(modelCreator.ctxModel()->id());
  shapeRepresentation->setRepresentationIdentifier("Body");
  shapeRepresentation->setRepresentationType("AdvancedSweptSolid");
  shapeRepresentation->items().createEmpty();
  shapeRepresentation->items().Add(idSweptAreasolid);
  auto idShapeRepresentation = model->appendEntityInstance(shapeRepresentation);

  auto productDefinitionShape = OdIfc4::IfcProductDefinitionShape::createObject();
  productDefinitionShape->representations().createEmpty();
  productDefinitionShape->representations().addByIndex(0, idShapeRepresentation);
  auto idProductDefinitionShape = model->appendEntityInstance(productDefinitionShape);

  column->setRepresentation(idProductDefinitionShape);

  return (int)ifcFile->writeFile(argv[2]);
}

