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

//#include "OdArray.h"
#include "ExPrintConsole.h"
#include "IfcExamplesCommon.h"
#include "IfcCore.h"
#include "IfcModel.h"

#include "OdaCommon.h"

OdDAIObjectId appendIfcSiUnit(OdIfcModel* model, const char* unitType, const char* prefix, const char* name);
OdDAIObjectId appendCartesianPoint(OdIfcModel* model, const OdArray<double>& dblArr);
OdDAIObjectId appendDirection(OdIfcModel* model, const OdArray<double>& dblArr);
OdDAIObjectId appendSpatialChild(OdIfcModel* model, const OdDAIObjectId& relating, OdIfc::OdIfcEntity* related, const OdDAIObjectId& ownerHistory );
OdDAIObjectId appendContained(OdIfcModel* model, const OdDAIObjectId& relating, OdIfc::OdIfcEntity* related, const OdDAIObjectId& ownerHistory);


class ModelInitializer
{
public:
  ModelInitializer(OdIfcFilePtr ifcFile, int tutorialNumber)
  {
    m_model = ifcFile->getModel(sdaiRW);

    OdDAI::ApplicationInstancePtr person = m_model->createEntityInstance("ifcperson");
    person->putAttr("identification", (const char*)"ODA tutorial person");
    OdDAIObjectId idPerson = m_model->appendEntityInstance(person); // person added to m_model and has id after this line

    OdDAI::ApplicationInstancePtr organization = m_model->createEntityInstance("ifcorganization");
    organization->putAttr("name", (const char*)"Open Design Alliance");
    OdDAIObjectId idOrganization = m_model->appendEntityInstance(organization);

    auto personAndOrganization = m_model->createEntityInstance("ifcpersonandorganization");
    personAndOrganization->putAttr("theperson", idPerson);
    personAndOrganization->putAttr("theorganization", idOrganization);
    auto idPersonAndOrganization = m_model->appendEntityInstance(personAndOrganization);

    auto organizationForApplication = m_model->createEntityInstance("ifcorganization");
    organizationForApplication->putAttr("name", OdAnsiString("Company 1"));
    organizationForApplication->putAttr("description", OdAnsiString("File produced in ExIfcTutorials"));
    auto idOrganizationForApplication = m_model->appendEntityInstance(organizationForApplication);

    auto application = m_model->createEntityInstance("ifcapplication");
    application->putAttr("applicationdeveloper", idOrganizationForApplication);
    application->putAttr("version", OdAnsiString("0.1 pre alpha"));
    application->putAttr("applicationfullname", OdAnsiString("ExIfcTutorials module for ODA IFC SDK"));
    application->putAttr("applicationidentifier", OdAnsiString("ExIfcTutorials"));
    auto idApplication = m_model->appendEntityInstance(application);

    auto ownerHistory = m_model->createEntityInstance("ifcownerhistory");
    ownerHistory->putAttr("owninguser", idPersonAndOrganization);
    ownerHistory->putAttr("owningapplication", idApplication);
    ownerHistory->putAttr("changeaction", OdAnsiString("ADDED"));
    ownerHistory->putAttr("creationdate", 0);
    m_idOwnerHistory = m_model->appendEntityInstance(ownerHistory);

    OdArray<OdRxValue> units;
    units.append(appendIfcSiUnit(m_model, "LENGTHUNIT", "MILLI", "METRE")); // ENUM
    units.append(appendIfcSiUnit(m_model, "PLANEANGLEUNIT", NULL, "RADIAN"));
    units.append(appendIfcSiUnit(m_model, "AREAUNIT", NULL, "SQUARE_METRE"));
    units.append(appendIfcSiUnit(m_model, "VOLUMEUNIT", NULL, "CUBIC_METRE"));

    auto unitAssignment = m_model->createEntityInstance("ifcunitassignment");
    unitAssignment->putAttrCaseInsensitive("Units", units);
    auto idUnitAssignment = m_model->appendEntityInstance(unitAssignment);


    auto project = m_model->createEntityInstance("ifcproject");

    OdAnsiString stringTutorial;
    stringTutorial.format("ODA IFC SDK tutorial %d", tutorialNumber);
    project->putAttr("name", stringTutorial);

    project->putAttr("globalid", OdIfcGUID::generate());
    project->putAttr("ownerhistory", m_idOwnerHistory);
    project->putAttr("unitsincontext", idUnitAssignment);
    m_idProject = m_model->appendEntityInstance(project);

    OdArray<double> dblArr;
    dblArr.append(0.);
    dblArr.append(0.);
    auto idCartesianPoint2d = appendCartesianPoint(m_model, dblArr);
    dblArr.append(0.);
    auto idCartesianPoint3d = appendCartesianPoint(m_model, dblArr);

    dblArr[2] = 1.;
    m_idDirectionZ = appendDirection(m_model, dblArr);

    OdDAIObjectIds idsCtx;

    // Plan context
    auto axis2placement2d = m_model->createEntityInstance("ifcaxis2placement2d");
    axis2placement2d->putAttr("location", idCartesianPoint2d);
    auto idAxis2Placement2d = m_model->appendEntityInstance(axis2placement2d);

    auto ctxPlan = m_model->createEntityInstance("ifcgeometricrepresentationcontext");
    ctxPlan->putAttr("contextidentifier", OdAnsiString("2D"));
    ctxPlan->putAttr("contexttype", OdAnsiString("Plan"));
    ctxPlan->putAttr("coordinatespacedimension", 2);
    ctxPlan->putAttr("worldcoordinatesystem", idAxis2Placement2d);
    idsCtx.append(m_model->appendEntityInstance(ctxPlan));

    // Model context
    auto axis2placement3d = m_model->createEntityInstance("ifcaxis2placement3d");
    axis2placement3d->putAttr("location", idCartesianPoint3d);
    auto idAxis2Placement3d = m_model->appendEntityInstance(axis2placement3d);

    m_ctxModel = m_model->createEntityInstance("ifcgeometricrepresentationcontext");
    m_ctxModel->putAttr("contextidentifier", OdAnsiString("3D"));
    m_ctxModel->putAttr("contexttype", OdAnsiString("Model"));
    m_ctxModel->putAttr("coordinatespacedimension", 3);
    m_ctxModel->putAttr("worldcoordinatesystem", idAxis2Placement3d);
    idsCtx.append(m_model->appendEntityInstance(m_ctxModel));

    project->putAttr("representationcontexts", idsCtx);
  }

  OdDAIObjectId   idDirectionZ() const { return m_idDirectionZ; }
  OdDAIObjectId   idProject() const { return m_idProject; }
  OdDAIObjectId   idOwnerHistory() const { return m_idOwnerHistory; }

  OdDAI::ApplicationInstancePtr ctxModel() const { return m_ctxModel; }

  OdIfcModelPtr   model()const { return m_model; }

private:
  OdDAIObjectId   m_idDirectionZ = 0;
  OdDAIObjectId   m_idProject = 0;
  OdDAIObjectId   m_idOwnerHistory = 0;

  OdDAI::ApplicationInstancePtr m_ctxModel;
  OdIfcModelPtr                 m_model;
};
