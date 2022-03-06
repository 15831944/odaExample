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
#include "ProjectSetup.h"
#include "ExIfcTutorial_01.h"

using namespace OdIfc;

OdDAIObjectId appendCartesianPoint(OdIfcModel *model, const OdArray<double> &dblArr)
{
  auto cartesianPoint = model->createEntityInstance("ifccartesianpoint");
  cartesianPoint->putAttr("coordinates", dblArr);
  return model->appendEntityInstance(cartesianPoint);
}

OdDAIObjectId appendDirection(OdIfcModel *model, const OdArray<double> &dblArr)
{
  auto direction = model->createEntityInstance("ifcdirection");
  direction->putAttr("directionratios", dblArr);
  return model->appendEntityInstance(direction);
}

OdDAIObjectId appendSpatialChild(OdIfcModel *model, const OdDAIObjectId &idRelating, OdIfc::OdIfcEntity *related, const OdDAIObjectId &idOwnerHistory)
{
  ODA_ASSERT(!idRelating.isNull());
  ODA_ASSERT(related->id() == nullptr);

  auto relAggregates = model->createEntityInstance("ifcrelaggregates");
  relAggregates->putAttr("globalid", OdIfcGUID::generate());
  relAggregates->putAttr("relatingobject", idRelating);
  model->appendEntityInstance(relAggregates);

  if (!related->testAttr("globalid"))
    related->putAttr("globalid", OdIfcGUID::generate());
  if (!idOwnerHistory.isNull())
    related->putAttr("ownerhistory", idOwnerHistory);

  auto idRelated = model->appendEntityInstance(related);
  OdDAIObjectIds ids;
  ids.append(idRelated);
  relAggregates->putAttr("relatedobjects", ids);
  return idRelated;
}

OdDAIObjectId appendContained(OdIfcModel *model, const OdDAIObjectId &idRelating, OdIfc::OdIfcEntity *related, const OdDAIObjectId &idOwnerHistory)
{
  ODA_ASSERT(!idRelating.isNull());
  ODA_ASSERT(related->id() == nullptr);

  auto relContained = model->createEntityInstance("ifcrelcontainedinspatialstructure");
  relContained->putAttr("globalid", OdIfcGUID::generate());
  relContained->putAttr("relatingstructure", idRelating);
  model->appendEntityInstance(relContained);

  if (!related->testAttr("globalid"))
    related->putAttr("globalid", OdIfcGUID::generate());
  if (!idOwnerHistory.isNull())
    related->putAttr("ownerhistory", idOwnerHistory);

  auto idRelated = model->appendEntityInstance(related);
  OdDAIObjectIds ids;
  ids.append(idRelated);
  relContained->putAttr("relatedelements", ids);
  return idRelated;
}

int Tutorial_01(int argc, wchar_t* argv[], const MyServices &svcs)
{
  OdIfcFilePtr ifcFile = svcs.createDatabase(kScmIfc4);
  OdIfcModelPtr model = ifcFile->getModel(sdaiRW);

  OdDAI::ApplicationInstancePtr person = model->createEntityInstance("ifcperson");
  OdDAIObjectId idPerson = model->appendEntityInstance(person); // person added to model and has id after this line

  OdDAI::ApplicationInstancePtr organization = model->createEntityInstance("ifcorganization");
  organization->putAttr("name", (const char *)"Open Design Alliance");
  OdDAIObjectId idOrganization = model->appendEntityInstance(organization);

  auto personAndOrganization = model->createEntityInstance("ifcpersonandorganization");
  personAndOrganization->putAttr("theperson", idPerson);
  personAndOrganization->putAttr("theorganization", idOrganization);
  auto idPersonAndOrganization = model->appendEntityInstance(personAndOrganization);

  auto organizationForApplication = model->createEntityInstance("ifcorganization");
  organizationForApplication->putAttr("name", OdAnsiString("Company 1"));
  organizationForApplication->putAttr("description", OdAnsiString("File produced in ExIfcTutorials"));
  auto idOrganizationForApplication = model->appendEntityInstance(organizationForApplication);

  auto application = model->createEntityInstance("ifcapplication");
  application->putAttr("applicationdeveloper", idOrganizationForApplication);
  application->putAttr("version", OdAnsiString("0.1 pre alpha"));
  application->putAttr("applicationfullname", OdAnsiString("ExIfcTutorials module for ODA IFC SDK"));
  application->putAttr("applicationidentifier", OdAnsiString("ExIfcTutorials"));
  auto idApplication = model->appendEntityInstance(application);

  auto ownerHistory = model->createEntityInstance("ifcownerhistory");
  ownerHistory->putAttr("owninguser", idPersonAndOrganization);
  ownerHistory->putAttr("owningapplication", idApplication);
  ownerHistory->putAttr("changeaction", OdAnsiString("ADDED"));
  ownerHistory->putAttr("creationdate", 0);
  auto idOwnerHistory = model->appendEntityInstance(ownerHistory);

  OdArray<OdRxValue> units;
  units.append(appendIfcSiUnit(model, "LENGTHUNIT", "MILLI", "METRE")); // ENUM
  units.append(appendIfcSiUnit(model, "PLANEANGLEUNIT", NULL, "RADIAN"));
  units.append(appendIfcSiUnit(model, "AREAUNIT", NULL, "SQUARE_METRE"));
  units.append(appendIfcSiUnit(model, "VOLUMEUNIT", NULL, "CUBIC_METRE"));

  auto unitAssignment = model->createEntityInstance("ifcunitassignment");
  unitAssignment->putAttrCaseInsensitive("Units", units);
  auto idUnitAssignment = model->appendEntityInstance(unitAssignment);

  auto project = model->createEntityInstance("ifcproject");
  project->putAttr("globalid", OdIfcGUID::generate());
  project->putAttr("ownerhistory", idOwnerHistory);
  project->putAttr("unitsincontext", idUnitAssignment);
  auto idProject = model->appendEntityInstance(project);

  OdArray<double> dblArr;
  dblArr.append(0.);
  dblArr.append(0.);
  auto idCartesianPoint2d = appendCartesianPoint(model, dblArr);
  dblArr.append(0.);
  auto idCartesianPoint3d = appendCartesianPoint(model, dblArr);

  dblArr[2] = 1.;
  auto idDirectionZ = appendDirection(model, dblArr);

  OdDAIObjectIds idsCtx;

  // Plan context
  auto axis2placement2d = model->createEntityInstance("ifcaxis2placement2d");
  axis2placement2d->putAttr("location", idCartesianPoint2d);
  auto idAxis2Placement2d = model->appendEntityInstance(axis2placement2d);

  auto ctxPlan = model->createEntityInstance("ifcgeometricrepresentationcontext");
  ctxPlan->putAttr("contextidentifier", OdAnsiString("2D"));
  ctxPlan->putAttr("contexttype", OdAnsiString("Plan"));
  ctxPlan->putAttr("coordinatespacedimension", 2);
  ctxPlan->putAttr("worldcoordinatesystem", idAxis2Placement2d);
  idsCtx.append(model->appendEntityInstance(ctxPlan));

  // Model context
  auto axis2placement3d = model->createEntityInstance("ifcaxis2placement3d");
  axis2placement3d->putAttr("location", idCartesianPoint3d);
  auto idAxis2Placement3d = model->appendEntityInstance(axis2placement3d);

  auto ctxModel = model->createEntityInstance("ifcgeometricrepresentationcontext");
  ctxModel->putAttr("contextidentifier", OdAnsiString("3D"));
  ctxModel->putAttr("contexttype", OdAnsiString("Model"));
  ctxModel->putAttr("coordinatespacedimension", 3);
  ctxModel->putAttr("worldcoordinatesystem", idAxis2Placement3d);
  idsCtx.append(model->appendEntityInstance(ctxModel));

  project->putAttr("representationcontexts", idsCtx);

  // Material
  auto colourRGB = model->createEntityInstance("ifccolourrgb");
  colourRGB->putAttr("name", OdAnsiString("Blue"));
  colourRGB->putAttr("red", 0.);
  colourRGB->putAttr("green", 0.);
  colourRGB->putAttr("blue", 1.);
  auto idColourRGB = model->appendEntityInstance(colourRGB);

  auto surfaceStyleRendering = model->createEntityInstance("ifcsurfacestylerendering");
  surfaceStyleRendering->putAttr("surfacecolour", idColourRGB);
  surfaceStyleRendering->putAttr("reflectancemethod", OdAnsiString("NOTDEFINED"));
  auto idSurfaceStyleRendering = model->appendEntityInstance(surfaceStyleRendering);

  OdArray<OdRxValue> styles; // Aggregation of Selects
  styles.push_back(idSurfaceStyleRendering);
  auto surfaceStyle = model->createEntityInstance("ifcsurfacestyle");
  surfaceStyle->putAttr("name", OdAnsiString("Style for columns"));
  surfaceStyle->putAttr("side", OdAnsiString("POSITIVE"));
  surfaceStyle->putAttr("styles", styles);
  auto idSurfaceStyle = model->appendEntityInstance(surfaceStyle);

  // Spatial structure
  
  OdIfcEntityPtr site = model->createEntityInstance("ifcsite");
  site->putAttr("name", OdAnsiString("Site"));
  auto idSite = appendSpatialChild(model, idProject, site, idOwnerHistory);

  OdIfcEntityPtr building = model->createEntityInstance("ifcbuilding");
  building->putAttr("name", OdAnsiString("Building"));
  auto idBuilding = appendSpatialChild(model, idSite, building, idOwnerHistory);

  OdIfcEntityPtr buildingStorey = model->createEntityInstance("ifcbuildingstorey");
  buildingStorey->putAttr("name", OdAnsiString("Floor 0"));
  auto idBuildingStorey = appendSpatialChild(model, idBuilding, buildingStorey, idOwnerHistory);

  // Spatial containment

  OdIfcEntityPtr column = model->createEntityInstance("ifccolumn");
  column->putAttr("name", OdAnsiString("Column"));
  auto idColumn = appendContained(model, idBuildingStorey, column, idOwnerHistory);

  // Geometrical representation
  auto circleProfileDef = model->createEntityInstance("ifccircleprofiledef");
  circleProfileDef->putAttr("profiletype", OdAnsiString("AREA")); // ENUM
  circleProfileDef->putAttr("profilename", OdAnsiString("Circular profile for columns"));
  circleProfileDef->putAttr("radius", 400.);
  auto idCircleProfileDef = model->appendEntityInstance(circleProfileDef);

  auto extrudedAreasolid = model->createEntityInstance("ifcextrudedareasolid");
  extrudedAreasolid->putAttr("sweptarea", idCircleProfileDef);
  extrudedAreasolid->putAttr("extrudeddirection", idDirectionZ);
  extrudedAreasolid->putAttr("depth", 4000.);

  OdDAIObjectIds items;
  items.append(model->appendEntityInstance(extrudedAreasolid));

  // Style assignment to Extruded Area Solid
  OdArray<OdRxValue> stylesForIlem;
  stylesForIlem.append(idSurfaceStyle);
  auto styledItem = model->createEntityInstance("ifcstyleditem");
  styledItem->putAttr("item", items[0]);
  styledItem->putAttr("styles", stylesForIlem); // Aggregation of Selects
  auto idStyledItem = model->appendEntityInstance(styledItem);

  auto shapeRepresentation = model->createEntityInstance("ifcshaperepresentation");
  shapeRepresentation->putAttr("contextofitems", OdDAIObjectId(ctxModel->id()));
  shapeRepresentation->putAttr("representationidentifier", OdAnsiString("Body"));
  shapeRepresentation->putAttr("representationtype", (const char *)"SweptSolid");
  shapeRepresentation->putAttr("items", items);

  OdDAIObjectIds idsRepresentation;
  idsRepresentation.append(model->appendEntityInstance(shapeRepresentation));

  auto productDefinitionShape = model->createEntityInstance("ifcproductdefinitionshape");
  productDefinitionShape->putAttr("representations", idsRepresentation);
  auto idProductDefinitionShape = model->appendEntityInstance(productDefinitionShape);

  column->putAttr("representation", idProductDefinitionShape);

  return (int)ifcFile->writeFile(argv[2]);
}

