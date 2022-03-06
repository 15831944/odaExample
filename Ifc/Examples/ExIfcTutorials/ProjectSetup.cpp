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
#include "RxValue.h"

using namespace OdIfc;
using namespace OdDAI;

OdDAIObjectId appendIfcDimensionalExponents(OdIfcModel *model,
  int LengthExponent,
  int MassExponent,
  int TimeExponent,
  int ElectricCurrentExponent,
  int ThermodynamicTemperatureExponent,
  int AmountOfSubstanceExponent,
  int LuminousIntensityExponent
)
{
  OdDAI::ApplicationInstancePtr dimensionalExponents = model->createEntityInstance("ifcdimensionalexponents");

  dimensionalExponents->putAttr("lengthexponent", LengthExponent);
  dimensionalExponents->putAttr("massexponent", MassExponent);
  dimensionalExponents->putAttr("timeexponent", TimeExponent);
  dimensionalExponents->putAttr("electriccurrentexponent", ElectricCurrentExponent);
  dimensionalExponents->putAttr("thermodynamictemperatureexponent", ThermodynamicTemperatureExponent);
  dimensionalExponents->putAttr("amountofsubstanceexponent", AmountOfSubstanceExponent);
  dimensionalExponents->putAttr("luminousintensityexponent", LuminousIntensityExponent);
  
  return model->appendEntityInstance(dimensionalExponents);
}

OdDAIObjectId appendIfcSiUnit(OdIfcModel *model, const char *unitType, const char *prefix, const char *name)
{
  auto siUnit = model->createEntityInstance("ifcsiunit");
  ODA_ASSERT(unitType);
  siUnit->putAttr("unittype", unitType);
  if (prefix)
    siUnit->putAttr("prefix", prefix);
  ODA_ASSERT(name);
  siUnit->putAttr("name", name);
  return model->appendEntityInstance(siUnit);
}

int ProjectSetup(OdDAI::Model *model, ProjectData &projectData, PlaneAngleUnits planeAngleUnits /* = PlaneAngleUnits::kRadians */, const char *lengthUnitPrefix /* = "MILLI" */)
{
  if (model == nullptr)
    return eNullPtr;

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
  projectData.ownerHistory = model->appendEntityInstance(ownerHistory);

  OdArray<OdRxValue> units;
  units.append(appendIfcSiUnit(model, "LENGTHUNIT", lengthUnitPrefix, "METRE")); // ENUM
  units.append(appendIfcSiUnit(model, "AREAUNIT", nullptr, "SQUARE_METRE"));
  units.append(appendIfcSiUnit(model, "VOLUMEUNIT", nullptr, "CUBIC_METRE"));
  units.append(appendIfcSiUnit(model, "MASSUNIT", "KILO", "GRAM"));
  units.append(appendIfcSiUnit(model, "TIMEUNIT", nullptr, "SECOND"));

  OdDAIObjectId idPlaneAngleUnit = appendIfcSiUnit(model, "PLANEANGLEUNIT", NULL, "RADIAN");
  if (planeAngleUnits == PlaneAngleUnits::kDegrees)
  {
    OdDAI::ApplicationInstancePtr measureWithUnit = model->createEntityInstance("ifcmeasurewithunit");
    OdDAI::AttributeDataBlock valueComponent;
    valueComponent.typePath.putPath("IfcPlaneAngleMeasure");
    valueComponent.value.setValue(0.017453292519943295);
    measureWithUnit->putAttr("valuecomponent", &valueComponent);
    measureWithUnit->putAttr("unitcomponent", idPlaneAngleUnit);
    auto idMeasureWithUnit = model->appendEntityInstance(measureWithUnit);

    auto idDimensionalExponents = appendIfcDimensionalExponents(model);

    OdDAI::ApplicationInstancePtr conversionBasedUnit = model->createEntityInstance("ifcconversionbasedunit");
    conversionBasedUnit->putAttr("dimensions", idDimensionalExponents);
    conversionBasedUnit->putAttr("unittype", (const char *)"PLANEANGLEUNIT");
    conversionBasedUnit->putAttr("name", (const char *)"DEGREE");
    conversionBasedUnit->putAttr("conversionfactor", idMeasureWithUnit);
    idPlaneAngleUnit = model->appendEntityInstance(conversionBasedUnit);
  }
  units.append(idPlaneAngleUnit);

  auto unitAssignment = model->createEntityInstance("ifcunitassignment");
  unitAssignment->putAttrCaseInsensitive("Units", units);
  auto idUnitAssignment = model->appendEntityInstance(unitAssignment);

  OdArray<double> dblArr;
  dblArr.append(0.);
  dblArr.append(0.);
  projectData.origin2d = appendCartesianPoint(model, dblArr);
  dblArr.append(0.);
  projectData.origin3d = appendCartesianPoint(model, dblArr);

  dblArr[2] = 1.;
  projectData.dirZ = appendDirection(model, dblArr);

  OdDAIObjectIds idsCtx;

  // Plan context
  auto axis2placement2d = model->createEntityInstance("ifcaxis2placement2d");
  axis2placement2d->putAttr("location", projectData.origin2d);
  auto idAxis2Placement2d = model->appendEntityInstance(axis2placement2d);

  auto ctxPlan = model->createEntityInstance("ifcgeometricrepresentationcontext");
  ctxPlan->putAttr("contextidentifier", OdAnsiString("2D"));
  ctxPlan->putAttr("contexttype", OdAnsiString("Plan"));
  ctxPlan->putAttr("coordinatespacedimension", 2);
  ctxPlan->putAttr("worldcoordinatesystem", idAxis2Placement2d);
  projectData.planContext = model->appendEntityInstance(ctxPlan);
  idsCtx.append(projectData.planContext);

  // Model context
  auto axis2placement3d = model->createEntityInstance("ifcaxis2placement3d");
  axis2placement3d->putAttr("location", projectData.origin3d);
  auto idAxis2Placement3d = model->appendEntityInstance(axis2placement3d);

  auto ctxModel = model->createEntityInstance("ifcgeometricrepresentationcontext");
  ctxModel->putAttr("contextidentifier", OdAnsiString("3D"));
  ctxModel->putAttr("contexttype", OdAnsiString("Model"));
  ctxModel->putAttr("coordinatespacedimension", 3);
  ctxModel->putAttr("worldcoordinatesystem", idAxis2Placement3d);
  projectData.planContext = model->appendEntityInstance(ctxModel);
  idsCtx.append(projectData.planContext);

  auto project = model->createEntityInstance("ifcproject");
  project->putAttr("globalid", OdIfcGUID::generate());
  project->putAttr("ownerhistory", projectData.ownerHistory);
  project->putAttr("unitsincontext", idUnitAssignment);
  projectData.project = model->appendEntityInstance(project);
  project->putAttr("representationcontexts", idsCtx);

  return eOk;
}

int Tutorial_ProjectSetup(int argc, wchar_t* argv[], const MyServices &svcs)
{
  OdIfcFilePtr ifcFile = svcs.createDatabase(kScmIfc4);
  OdIfcModelPtr model = ifcFile->getModel(sdaiRW);

  ProjectData projectData;
  ProjectSetup(model, projectData, PlaneAngleUnits::kDegrees, "MILLI");

  return (int)ifcFile->writeFile(argv[2]);
}
