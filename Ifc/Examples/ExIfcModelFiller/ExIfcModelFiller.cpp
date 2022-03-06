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
/************************************************************************/
/* This console application make creates a new IFC file.                */
/*                                                                      */
/* Calling sequence:                                                    */
/*                                                                      */
/* ExIfcModelFiller <destination dump filename>                         */
/*                                                                      */
/************************************************************************/

#include "OdaCommon.h"
#include "StaticRxObject.h"
#include "DynamicLinker.h"
#include "RxInit.h"
#include "RxObjectImpl.h"
#include "RxDynamicModule.h"
#include "diagnostics.h"

#include "daiHeaderSection.h"
#include "daiHeader/daiHeaderEntities.h"

#include "ExIfcModelFiller.h"
#include "IfcExamplesCommon.h"
#include "ExIfcHostAppServices.h"
#include "IfcCore.h"
#include "IfcEntityTypes.h"

#include "FillerExtender.h"

#define STL_USING_SET
#define STL_USING_MAP
#define STL_USING_IOSTREAM
#include "OdaSTL.h"
#define  STD(a)  std:: a

DBROOT_EXPORT void odDbRootInitialize();
DBROOT_EXPORT void odDbRootUninitialize();

ODGI_EXPORT void odgiInitialize();
ODGI_EXPORT void odgiUninitialize();

static void customAssertFunc(const char* expr, const char* fileName, int nLine)
{
  printf( 
    "Assertion has occurs:\n"
    " Expression: %s\n"
    " Filename: %s\n"
    " Line number: %d\n",
    expr, fileName, nLine );
}

bool isDir(OdString &szSource, bool &upperLevel)
{
  if (szSource.getLength() < 3)
  {
    upperLevel = true;
    return true;
  }
  if (szSource[szSource.getLength()-1] == '.')
  {
    upperLevel = true;
    return true;
  }

  upperLevel = false;
  int len = szSource.getLength();
  int pos = szSource.find(OD_T(".ifc"));
  if (pos < 1)
  {
    pos = szSource.find(OD_T(".IFC"));
    if (pos < 1)
    {
      pos = szSource.reverseFind(OdChar('.'));
      int posSlash = szSource.reverseFind(OdChar('\\'));
      if (pos > posSlash)
      {
        // Unsupported file extension
        upperLevel = true;
        return true;
      }
    }
  }
  return !(pos == len - 4);
}

#ifndef _TOOLKIT_IN_DLL_
  using namespace OdIfc;                                                             \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdSDAIModule);                              \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcCoreModule);                           \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc2x3Module);                            \
  ODRX_BEGIN_STATIC_MODULE_MAP()                                                     \
    ODRX_DEFINE_STATIC_APPMODULE(OdSDAIModuleName, OdSDAIModule)                     \
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcCoreModuleName, OdIfcCoreModule)               \
    ODRX_DEFINE_STATIC_APPMODULE(OdIfc2x3ModuleName, OdIfc2x3Module)                 \
  ODRX_END_STATIC_MODULE_MAP()
#endif

  namespace {

    template <class THeaderEntity, OdDAI::OdHeaderEntityType headerType>
    THeaderEntity*  getHeaderFromSection(OdDAI::OdHeaderSectionPtr headerSection)
    {
      OdDAI::ApplicationInstancePtr headerEntity = headerSection->getEntityByType(headerType);
      if (headerEntity.isNull())
      {
        ODA_ASSERT(0 && "Header entity was not created.");
        throw OdError(eNullEntityPointer);
      }

      THeaderEntity* castedPointer = dynamic_cast<THeaderEntity*>(headerEntity.get());

      if (castedPointer == NULL)
      {
        ODA_ASSERT(0 && "Header entity was not created.");
        throw OdError(eIllegalEntityType);
      }

      // Returns valid row pointer. This pointer will be valid until header section destroy.
      return castedPointer;
    }

    void initHeader(OdIfcFile *pDb)
    {
      if (pDb == NULL)
      {
        throw OdError(eNullPtr);
      }

      OdDAI::OdHeaderSectionPtr headerSection = pDb->getHeaderSection();

      if (headerSection.isNull())
      {
        ODA_ASSERT(0 && "Header is not valid.");
        headerSection->initialize();
      }

      OdDAI::FileDescription* fileDescription = getHeaderFromSection<OdDAI::FileDescription, OdDAI::kFileDescription>(headerSection);
      OdArray<OdAnsiString> descriptionCollection;
      descriptionCollection.push_back("ViewDefinition [CoordinationView]");
      fileDescription->setDescription(descriptionCollection);

      OdDAI::FileName* fileName = getHeaderFromSection<OdDAI::FileName, OdDAI::kFileName>(headerSection);
      OdAnsiStringArray arrAuthor;
      arrAuthor.append("ExIfcModelFiller example");
      fileName->setAuthor(arrAuthor);
      OdAnsiStringArray arrOrganization;
      arrOrganization.append("ODA");
      fileName->setOrganization(arrOrganization);
    }

    void fillModel(OdIfcFile *pDb)
    {
      if (pDb == NULL)
      {
        throw OdError(eNullPtr);
      }

      OdIfcModelPtr model = pDb->getModel(sdaiRW);

      if (model.isNull() || model->underlyingSchemaName().find("IFC2X3") != 0)
      {
        ODA_ASSERT(0 && "Model is not valid.");
        throw OdError(eNullEntityPointer);
      }

      OdDAIObjectId handleOwnerHistory = OdIfc::Utils::createOwnerHistory(model);
      OdDAIObjectId direction_6 = OdIfc::Utils::createDirection(model, 0., 1., 0.);
      OdDAIObjectId direction_7 = OdIfc::Utils::createDirection(model, 1., 0., 0.);
      OdDAIObjectId direction_8 = OdIfc::Utils::createDirection(model, 0., 0., 1.);

      OdDAIObjectId cartesian_9 = OdIfc::Utils::createCartesianPoint(model, 0, 0, 0);
      OdDAIObjectId axis2Placement3D_10 = OdIfc::Utils::createAxis2Placement3D(model, cartesian_9, direction_8, direction_7);

      OdDAIObjectId representationContext_11 = OdIfc::Utils::createGeometricRepresentationContext(model, "Plan", "Model", 3, 0.00001, axis2Placement3D_10, direction_6);
      OdDAIObjectId dimensionalExponents_12 = OdIfc::Utils::createDimensionalExponents(model, 0, 0, 0, 0, 0, 0, 0);

      OdDAIObjectId siunit_13 = OdIfc::Utils::createSIUnit(model, OdIfc2x3::kIfcUnitEnum_LENGTHUNIT, OdIfc2x3::kIfcSIPrefix_MILLI, OdIfc2x3::kIfcSIUnitName_METRE, NULL);
      OdDAIObjectId siunit_14 = OdIfc::Utils::createSIUnit(model, OdIfc2x3::kIfcUnitEnum_PLANEANGLEUNIT, OdIfc2x3::kIfcSIPrefix_unset, OdIfc2x3::kIfcSIUnitName_RADIAN, NULL);

      OdDAIObjectId measureWithUnit_15 = OdIfc::Utils::createMeasureWithUnit(model, 0.0174532925, siunit_14);
      OdDAIObjectId conversionBasedUnit_16 = OdIfc::Utils::createConversionBasedUnit(model, L"Degrees", measureWithUnit_15, dimensionalExponents_12, OdIfc2x3::kIfcUnitEnum_PLANEANGLEUNIT);

      OdDAIObjectIds  unitsCollection_17;
      unitsCollection_17.push_back(siunit_13);
      unitsCollection_17.push_back(conversionBasedUnit_16);
      OdDAIObjectId unitAssignment_17 = OdIfc::Utils::createUnitAssignment(model, unitsCollection_17);

      OdDAIObjectIds  representationContext_18;
      representationContext_18.push_back(representationContext_11);
      OdDAIObjectId project_18 = OdIfc::Utils::createProject(model, L"Sample project made with ODA ExIfcModelFiller app", representationContext_18, unitAssignment_17, handleOwnerHistory);

      OdDAIObjectId direction_19 = OdIfc::Utils::createDirection(model, 1, 0, 0);
      OdDAIObjectId direction_20 = OdIfc::Utils::createDirection(model, 0, 0, 1);

      OdDAIObjectId cartesian_21 = OdIfc::Utils::createCartesianPoint(model, 0, 0, 0);

      OdDAIObjectId axis2Placement3D_22 = OdIfc::Utils::createAxis2Placement3D(model, cartesian_21, direction_20, direction_19);
      OdDAIObjectId localPlacement_23 = OdIfc::Utils::createLocalPlacement(model, axis2Placement3D_22);

      OdDAIObjectId site_24 = OdIfc::Utils::createSite(model, localPlacement_23, handleOwnerHistory, OdIfc2x3::kIfcElementCompositionEnum_ELEMENT);

      OdDAIObjectIds  relatedObjectCollection_25;
      relatedObjectCollection_25.push_back(site_24);
      OdDAIObjectId relAggregates_25 = OdIfc::Utils::createRelAggregates(model, handleOwnerHistory, project_18, relatedObjectCollection_25);

      OdDAIObjectId direction_26 = OdIfc::Utils::createDirection(model, 1., 0., 0.);
      OdDAIObjectId direction_27 = OdIfc::Utils::createDirection(model, 0., 0., 1.);
      OdDAIObjectId cartesian_28 = OdIfc::Utils::createCartesianPoint(model, 0., 0., 0.);

      OdDAIObjectId axis2Placement3D_29 = OdIfc::Utils::createAxis2Placement3D(model, cartesian_28, direction_27, direction_26);
      OdDAIObjectId localPlacement_30 = OdIfc::Utils::createLocalPlacement(model, axis2Placement3D_29, &localPlacement_23);

      OdDAIObjectId building_31 = OdIfc::Utils::createBuilding(model, handleOwnerHistory, localPlacement_30, OdIfc2x3::kIfcElementCompositionEnum_ELEMENT);

      OdDAIObjectIds  relatedObjectCollection_32;
      relatedObjectCollection_32.push_back(building_31);
      OdDAIObjectId relAggregates_32 = OdIfc::Utils::createRelAggregates(model, handleOwnerHistory, site_24, relatedObjectCollection_32);

      OdDAIObjectId direction_33 = OdIfc::Utils::createDirection(model, 1, 0, 0);
      OdDAIObjectId direction_34 = OdIfc::Utils::createDirection(model, 0, 0, 1);
      OdDAIObjectId cartesian_35 = OdIfc::Utils::createCartesianPoint(model, 0, 0, 0);

      OdDAIObjectId axis2Placement3D_36 = OdIfc::Utils::createAxis2Placement3D(model, cartesian_35, direction_34, direction_33);
      OdDAIObjectId localPlacement_37 = OdIfc::Utils::createLocalPlacement(model, axis2Placement3D_36, &localPlacement_30);

      OdDAIObjectId buildingStorey_38 = OdIfc::Utils::createBuildingStorey(model, handleOwnerHistory, localPlacement_37, OdIfc2x3::kIfcElementCompositionEnum_ELEMENT);

      OdDAIObjectIds  relatedObjectCollection_39;
      relatedObjectCollection_39.push_back(buildingStorey_38);
      OdDAIObjectId relAggregates_39 = OdIfc::Utils::createRelAggregates(model, handleOwnerHistory, building_31, relatedObjectCollection_39);

      OdDAIObjectId buildingElementProxy_40 = OdIfc::Utils::createBuildingElementProxy(model, handleOwnerHistory);
      OdIfc::Utils::LocalPlacementPostSetter<OdIfc2x3::IfcBuildingElementProxy> localPlacementSetter_40(model, buildingElementProxy_40);
      OdIfc::Utils::ProductDefinitionShapeSetter<OdIfc2x3::IfcBuildingElementProxy> productDefinitionShapeSetter_40(model, buildingElementProxy_40);

      OdDAIObjectIds  relatedElements_41;
      relatedElements_41.push_back(buildingElementProxy_40);
      OdDAIObjectId ispetialStructure_41 = OdIfc::Utils::createRelContainedInspatialStructure(model, handleOwnerHistory, relatedElements_41, buildingStorey_38);

      OdDAIObjectId direction_42 = OdIfc::Utils::createDirection(model, 1, 0, 0);
      OdDAIObjectId direction_43 = OdIfc::Utils::createDirection(model, 0, 0, 1);
      OdDAIObjectId cartesian_44 = OdIfc::Utils::createCartesianPoint(model, 0, 0, 0);

      OdDAIObjectId axis2Placement3D_45 = OdIfc::Utils::createAxis2Placement3D(model, cartesian_44, direction_43, direction_42);
      OdDAIObjectId localPlacement_46 = OdIfc::Utils::createLocalPlacement(model, axis2Placement3D_45, NULL);

      localPlacementSetter_40.Set(localPlacement_46);

      OdDAIObjectId direction_47 = OdIfc::Utils::createDirection(model, 1, 0);
      OdDAIObjectId cartesian_48 = OdIfc::Utils::createCartesianPoint(model, 0, 0);

      OdDAIObjectId axis2Placement_49 = OdIfc::Utils::createAxis2Placement2D(model, cartesian_48, direction_47);

      OdDAIObjectId direction_50 = OdIfc::Utils::createDirection(model, 0, 0, 1);
      OdDAIObjectId direction_51 = OdIfc::Utils::createDirection(model, 1, 0, 0);
      OdDAIObjectId direction_52 = OdIfc::Utils::createDirection(model, 0, 0, 1);
      OdDAIObjectId cartesian_53 = OdIfc::Utils::createCartesianPoint(model, 0, 0, 0);
      OdDAIObjectId axis2Placement3D_54 = OdIfc::Utils::createAxis2Placement3D(model, cartesian_53, direction_52, direction_51);

      OdDAIObjectId iShapeProfileDef_55 = OdIfc::Utils::createIShapeProfileDef(model, OdIfc2x3::kIfcProfileTypeEnum_AREA, axis2Placement_49, 50., 25., 5., 2.);

      OdDAIObjectId extrudedAreaSolid_56 = OdIfc::Utils::createExtrudedAreaSolid(model, iShapeProfileDef_55, axis2Placement3D_54, direction_50, 20);

      OdDAIObjectIds  representationItemsCollection_57;
      representationItemsCollection_57.push_back(extrudedAreaSolid_56);
      OdDAIObjectId shapeRepresentation_57 = OdIfc::Utils::createShapeRepresentation(model, representationContext_11, "Body", "SweptSolid", representationItemsCollection_57);

      OdDAIObjectIds  represntationCollection_58;
      represntationCollection_58.push_back(shapeRepresentation_57);
      OdDAIObjectId productDefinitionShape_58 = OdIfc::Utils::createProductDefinitionShape(model, represntationCollection_58);

      productDefinitionShapeSetter_40.Set(productDefinitionShape_58);

      OdDAIObjectId buildingElementProxy_59 = OdIfc::Utils::createBuildingElementProxy(model, handleOwnerHistory);
      OdIfc::Utils::LocalPlacementPostSetter<OdIfc2x3::IfcBuildingElementProxy> localPlacementSetter_59(model, buildingElementProxy_59);
      OdIfc::Utils::ProductDefinitionShapeSetter<OdIfc2x3::IfcBuildingElementProxy> productDefinitionShapeSetter_59(model, buildingElementProxy_59);

      OdDAIObjectIds  relatedElements_60;
      relatedElements_60.push_back(buildingElementProxy_59);
      OdDAIObjectId ispetialStructure_60 = OdIfc::Utils::createRelContainedInspatialStructure(model, handleOwnerHistory, relatedElements_60, buildingStorey_38);

      OdDAIObjectId direction_61 = OdIfc::Utils::createDirection(model, 1, 0, 0);
      OdDAIObjectId direction_62 = OdIfc::Utils::createDirection(model, 0, 0, 1);
      OdDAIObjectId cartesian_63 = OdIfc::Utils::createCartesianPoint(model, 100, 0, 0);

      OdDAIObjectId axis2Placement3D_64 = OdIfc::Utils::createAxis2Placement3D(model, cartesian_63, direction_62, direction_61);
      OdDAIObjectId localPlacement_65 = OdIfc::Utils::createLocalPlacement(model, axis2Placement3D_64, NULL);
      localPlacementSetter_59.Set(localPlacement_65);

      OdDAIObjectId direction_66 = OdIfc::Utils::createDirection(model, 1, 0);
      OdDAIObjectId cartesian_67 = OdIfc::Utils::createCartesianPoint(model, 0, 0);
      OdDAIObjectId axis2Placement_68 = OdIfc::Utils::createAxis2Placement2D(model, cartesian_67, direction_66);

      OdDAIObjectId direction_69 = OdIfc::Utils::createDirection(model, 0, 0, 1);
      OdDAIObjectId direction_70 = OdIfc::Utils::createDirection(model, 1, 0, 0);
      OdDAIObjectId direction_71 = OdIfc::Utils::createDirection(model, 0, 0, 1);
      OdDAIObjectId cartesian_72 = OdIfc::Utils::createCartesianPoint(model, 0, 0, 0);
      OdDAIObjectId axis2Placement3D_73 = OdIfc::Utils::createAxis2Placement3D(model, cartesian_72, direction_71, direction_70);


      const double radius = 2.;
      OdDAIObjectId iShapeProfileDef_74 = OdIfc::Utils::createIShapeProfileDef(model, OdIfc2x3::kIfcProfileTypeEnum_AREA, axis2Placement_68, 50., 25., 5., 5., &radius);

      OdDAIObjectId extrudedAreaSolid_75 = OdIfc::Utils::createExtrudedAreaSolid(model, iShapeProfileDef_74, axis2Placement3D_73, direction_69, 20);

      OdDAIObjectIds  representationItemsCollection_76;
      representationItemsCollection_76.push_back(extrudedAreaSolid_75);
      OdDAIObjectId shapeRepresentation_76 = OdIfc::Utils::createShapeRepresentation(model, representationContext_11, "Body", "SweptSolid", representationItemsCollection_76);

      OdDAIObjectIds  represntationCollection_77;
      represntationCollection_77.push_back(shapeRepresentation_76);
      OdDAIObjectId productDefinitionShape_77 = OdIfc::Utils::createProductDefinitionShape(model, represntationCollection_77);
      productDefinitionShapeSetter_59.Set(productDefinitionShape_77);
    }
  }

#if defined(OD_USE_WMAIN)
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
  ::odSetAssertFunc( customAssertFunc );

  //parse commands
  if( argc < 2 )
  {
    odPrintConsoleString(L"\nExIfcModelFiller sample program. Copyright (c) 2022, Open Design Alliance\n");
    odPrintConsoleString(L"\tusage: ExIfcModelFiller <destination file>\n");
    odPrintConsoleString(L"\nPress ENTER to continue...\n");
    STD(cin).get();
    return 1;
  }

  OdString szTargetFileName = argv[1]; 

#ifndef _TOOLKIT_IN_DLL_
  ODRX_INIT_STATIC_MODULE_MAP();
#endif

  //create some service
  OdStaticRxObject< MyServices > svcs;

  /**********************************************************************/
  /* Initialize Runtime Extension environment                           */
  /**********************************************************************/
  odrxInitialize( &svcs );
  odDbRootInitialize();

  /**********************************************************************/
  /* Initialize IfcCore                                                 */
  /**********************************************************************/
  odIfcInitialize(false /* No CDA */, false /* No geometry calculation needed */);

  try
  {
    OdIfcFilePtr pDb = svcs.createDatabase(kScmIfc2x3);
    if (!pDb.isNull())
    {
      initHeader(pDb);
      fillModel(pDb);
      pDb->writeFile(szTargetFileName, true);
    }
  }
  catch (OdError& e)
  {
    odPrintConsoleString(L"\nODASDK\174 for .IFC Error: %ls\n", e.description().c_str());
  }
  catch (...)
  {
    odPrintConsoleString(L"\nUnknown Error.\n");
  }

  /**********************************************************************/
  /* Uninitialize IfcCore                                               */
  /**********************************************************************/
  odIfcUninitialize();

  /**********************************************************************/
  /* Uninitialize Runtime Extension environment                         */
  /**********************************************************************/
  odDbRootUninitialize();
  ::odrxUninitialize();

  return 0;
}
