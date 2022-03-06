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


using OdIfcExamplesLibMgd;
using System;
using Teigha.Core;
using ODA.Ifc.IFC2X3;
using ODA.Ifc.IfcCore;
using ODA.Sdai.sdai;

namespace ExIfcModelFillerSwigMgd
{
  public class OdExIfcModelFillerSample
  {
    public void initHeader(OdIfcFile pDb)
    {
      if (pDb == null)
      {
        throw new OdError(OdResult.eNullPtr);
      }

      OdDAI_OdHeaderSection headerSection = pDb.getHeaderSection();

      if (headerSection == null)
      {
        Globals.OdAssert("", "Header is not valid.", 0);
        headerSection.initialize();
      }

      OdDAI_FileDescription fileDescription = getHeaderFromSection<OdDAI_FileDescription>(headerSection, OdDAI_OdHeaderEntityType.kFileDescription);
      OdAnsiStringArray descriptionCollection = new OdAnsiStringArray();
      descriptionCollection.Add("ViewDefinition [CoordinationView]");
      fileDescription.setDescription(descriptionCollection);

      OdDAI_FileName fileName = getHeaderFromSection<OdDAI_FileName>(headerSection, OdDAI_OdHeaderEntityType.kFileName);
      OdAnsiStringArray arrAuthor = new OdAnsiStringArray();
      arrAuthor.Add("ExIfcModelFiller example");
      fileName.setAuthor(arrAuthor);
      OdAnsiStringArray arrOrganization = new OdAnsiStringArray();
      arrOrganization.Add("ODA");
      fileName.setOrganization(arrOrganization);
    }

    public void fillModel(OdIfcFile pDb)
    {
      if (pDb == null)
      {
        throw new OdError(OdResult.eNullPtr);
      }

      OdDAI_Model model = pDb.getModel(SdaiAccessMode.sdaiRW);

      if (model == null || model.underlyingSchemaName() != ("IFC2X3"))
      {
        Globals.OdAssert("", "Model is not valid.", 0);
        throw new OdError(OdResult.eNullEntityPointer);
      }

      OdDAIObjectId handleOwnerHistory = OdExIfcModelHelper.createOwnerHistory(model);
      OdDAIObjectId direction_6 = OdExIfcModelHelper.createDirection(model, 0.0, 1.0, 0.0);
      OdDAIObjectId direction_7 = OdExIfcModelHelper.createDirection(model, 1.0, 0.0, 0.0);
      OdDAIObjectId direction_8 = OdExIfcModelHelper.createDirection(model, 0.0, 0.0, 1.0);

      OdDAIObjectId cartesian_9 = OdExIfcModelHelper.createCartesianPoint(model, 0, 0, 0);
      OdDAIObjectId axis2Placement3D_10 = OdExIfcModelHelper.createAxis2Placement3D(model, cartesian_9, direction_8, direction_7);

      OdDAIObjectId representationContext_11 = OdExIfcModelHelper.createGeometricRepresentationContext(model, "Plan", "Model", 3, 0.00001, axis2Placement3D_10, direction_6);
      OdDAIObjectId dimensionalExponents_12 = OdExIfcModelHelper.createDimensionalExponents(model, 0, 0, 0, 0, 0, 0, 0);

      OdDAIObjectId siunit_13 = OdExIfcModelHelper.createSIUnit(model,
        OdIfc2x3_IfcUnitEnum.kIfcUnitEnum_LENGTHUNIT,
        OdIfc2x3_IfcSIPrefix.kIfcSIPrefix_MILLI,
        OdIfc2x3_IfcSIUnitName.kIfcSIUnitName_METRE,
        null);
      OdDAIObjectId siunit_14 = OdExIfcModelHelper.createSIUnit(model,
        OdIfc2x3_IfcUnitEnum.kIfcUnitEnum_PLANEANGLEUNIT,
        OdIfc2x3_IfcSIPrefix.kIfcSIPrefix_unset,
        OdIfc2x3_IfcSIUnitName.kIfcSIUnitName_RADIAN, null);

      OdDAIObjectId measureWithUnit_15 = OdExIfcModelHelper.createMeasureWithUnit(model, 0.0174532925, siunit_14);
      OdDAIObjectId conversionBasedUnit_16 = OdExIfcModelHelper.createConversionBasedUnit(model,
        "Degrees",
        measureWithUnit_15,
        dimensionalExponents_12,
        OdIfc2x3_IfcUnitEnum.kIfcUnitEnum_PLANEANGLEUNIT);

      OdDAIObjectIds unitsCollection_17 = new OdDAIObjectIds();
      unitsCollection_17.Add(siunit_13);
      unitsCollection_17.Add(conversionBasedUnit_16);
      OdDAIObjectId unitAssignment_17 = OdExIfcModelHelper.createUnitAssignment(model, unitsCollection_17);

      OdDAI_OdDAIObjectIdSet representationContext_18 = new OdDAI_OdDAIObjectIdSet();
      representationContext_18.Add(OdRxValueHelper.rxvalue_create(representationContext_11));
      OdDAIObjectId project_18 = OdExIfcModelHelper.createProject(model, "Sample project made with ODA ExIfcModelFiller app", representationContext_18, unitAssignment_17, handleOwnerHistory);

      OdDAIObjectId direction_19 = OdExIfcModelHelper.createDirection(model, 1, 0, 0);
      OdDAIObjectId direction_20 = OdExIfcModelHelper.createDirection(model, 0, 0, 1);

      OdDAIObjectId cartesian_21 = OdExIfcModelHelper.createCartesianPoint(model, 0, 0, 0);

      OdDAIObjectId axis2Placement3D_22 = OdExIfcModelHelper.createAxis2Placement3D(model, cartesian_21, direction_20, direction_19);
      OdDAIObjectId localPlacement_23 = OdExIfcModelHelper.createLocalPlacement(model, axis2Placement3D_22);

      OdDAIObjectId site_24 = OdExIfcModelHelper.createSite(model, localPlacement_23, handleOwnerHistory, OdIfc2x3_IfcElementCompositionEnum.kIfcElementCompositionEnum_ELEMENT);

      OdDAI_OdDAIObjectIdSet relatedObjectCollection_25 = new OdDAI_OdDAIObjectIdSet();
      relatedObjectCollection_25.Add(OdRxValueHelper.rxvalue_create(site_24));
      OdDAIObjectId relAggregates_25 = OdExIfcModelHelper.createRelAggregates(model, handleOwnerHistory, project_18, relatedObjectCollection_25);

      OdDAIObjectId direction_26 = OdExIfcModelHelper.createDirection(model, 1.0, 0.0, 0.0);
      OdDAIObjectId direction_27 = OdExIfcModelHelper.createDirection(model, 0.0, 0.0, 1.0);
      OdDAIObjectId cartesian_28 = OdExIfcModelHelper.createCartesianPoint(model, 0.0, 0.0, 0.0);

      OdDAIObjectId axis2Placement3D_29 = OdExIfcModelHelper.createAxis2Placement3D(model, cartesian_28, direction_27, direction_26);
      OdDAIObjectId localPlacement_30 = OdExIfcModelHelper.createLocalPlacement(model, axis2Placement3D_29, localPlacement_23);

      OdDAIObjectId building_31 = OdExIfcModelHelper.createBuilding(model, handleOwnerHistory, localPlacement_30, OdIfc2x3_IfcElementCompositionEnum.kIfcElementCompositionEnum_ELEMENT);

      OdDAI_OdDAIObjectIdSet relatedObjectCollection_32 = new OdDAI_OdDAIObjectIdSet();
      relatedObjectCollection_32.Add(OdRxValueHelper.rxvalue_create(building_31));
      OdDAIObjectId relAggregates_32 = OdExIfcModelHelper.createRelAggregates(model, handleOwnerHistory, site_24, relatedObjectCollection_32);

      OdDAIObjectId direction_33 = OdExIfcModelHelper.createDirection(model, 1, 0, 0);
      OdDAIObjectId direction_34 = OdExIfcModelHelper.createDirection(model, 0, 0, 1);
      OdDAIObjectId cartesian_35 = OdExIfcModelHelper.createCartesianPoint(model, 0, 0, 0);

      OdDAIObjectId axis2Placement3D_36 = OdExIfcModelHelper.createAxis2Placement3D(model, cartesian_35, direction_34, direction_33);
      OdDAIObjectId localPlacement_37 = OdExIfcModelHelper.createLocalPlacement(model, axis2Placement3D_36, localPlacement_30);

      OdDAIObjectId buildingStorey_38 = OdExIfcModelHelper.createBuildingStorey(model, handleOwnerHistory, localPlacement_37, OdIfc2x3_IfcElementCompositionEnum.kIfcElementCompositionEnum_ELEMENT);

      OdDAI_OdDAIObjectIdSet relatedObjectCollection_39 = new OdDAI_OdDAIObjectIdSet();
      relatedObjectCollection_39.Add(OdRxValueHelper.rxvalue_create(buildingStorey_38));
      OdDAIObjectId relAggregates_39 = OdExIfcModelHelper.createRelAggregates(model, handleOwnerHistory, building_31, relatedObjectCollection_39);

      OdDAIObjectId buildingElementProxy_40 = OdExIfcModelHelper.createBuildingElementProxy(model, handleOwnerHistory);


      OdExIfcModelHelper.LocalPlacementPostSetter<OdIfc2x3_IfcBuildingElementProxy> localPlacementSetter_40
        = new OdExIfcModelHelper.LocalPlacementPostSetter<OdIfc2x3_IfcBuildingElementProxy>(model, buildingElementProxy_40);
      OdExIfcModelHelper.ProductDefinitionShapeSetter<OdIfc2x3_IfcBuildingElementProxy> productDefinitionShapeSetter_40
        = new OdExIfcModelHelper.ProductDefinitionShapeSetter<OdIfc2x3_IfcBuildingElementProxy>(model, buildingElementProxy_40);

      OdDAI_OdDAIObjectIdSet relatedElements_41 = new OdDAI_OdDAIObjectIdSet();
      relatedElements_41.Add(OdRxValueHelper.rxvalue_create(buildingElementProxy_40));
      OdDAIObjectId ispetialStructure_41 = OdExIfcModelHelper.createRelContainedInspatialStructure(model, handleOwnerHistory, relatedElements_41, buildingStorey_38);

      OdDAIObjectId direction_42 = OdExIfcModelHelper.createDirection(model, 1, 0, 0);
      OdDAIObjectId direction_43 = OdExIfcModelHelper.createDirection(model, 0, 0, 1);
      OdDAIObjectId cartesian_44 = OdExIfcModelHelper.createCartesianPoint(model, 0, 0, 0);

      OdDAIObjectId axis2Placement3D_45 = OdExIfcModelHelper.createAxis2Placement3D(model, cartesian_44, direction_43, direction_42);
      OdDAIObjectId localPlacement_46 = OdExIfcModelHelper.createLocalPlacement(model, axis2Placement3D_45, null);

      localPlacementSetter_40.Set(localPlacement_46);

      OdDAIObjectId direction_47 = OdExIfcModelHelper.createDirection(model, 1, 0);
      OdDAIObjectId cartesian_48 = OdExIfcModelHelper.createCartesianPoint(model, 0, 0);

      OdDAIObjectId axis2Placement_49 = OdExIfcModelHelper.createAxis2Placement2D(model, cartesian_48, direction_47);

      OdDAIObjectId direction_50 = OdExIfcModelHelper.createDirection(model, 0, 0, 1);
      OdDAIObjectId direction_51 = OdExIfcModelHelper.createDirection(model, 1, 0, 0);
      OdDAIObjectId direction_52 = OdExIfcModelHelper.createDirection(model, 0, 0, 1);
      OdDAIObjectId cartesian_53 = OdExIfcModelHelper.createCartesianPoint(model, 0, 0, 0);
      OdDAIObjectId axis2Placement3D_54 = OdExIfcModelHelper.createAxis2Placement3D(model, cartesian_53, direction_52, direction_51);

      OdDAIObjectId iShapeProfileDef_55 = OdExIfcModelHelper.createIShapeProfileDef(model, OdIfc2x3_IfcProfileTypeEnum.kIfcProfileTypeEnum_AREA, axis2Placement_49, 50.0, 25.0, 5.0, 2.0);

      OdDAIObjectId extrudedAreaSolid_56 = OdExIfcModelHelper.createExtrudedAreaSolid(model, iShapeProfileDef_55, axis2Placement3D_54, direction_50, 20);

      OdDAI_OdDAIObjectIdSet representationItemsCollection_57 = new OdDAI_OdDAIObjectIdSet();
      representationItemsCollection_57.Add(OdRxValueHelper.rxvalue_create(extrudedAreaSolid_56));
      OdDAIObjectId shapeRepresentation_57 = OdExIfcModelHelper.createShapeRepresentation(model, representationContext_11, "Body", "SweptSolid", representationItemsCollection_57);

      OdDAI_OdDAIObjectIdList represntationCollection_58 = new OdDAI_OdDAIObjectIdList();
      represntationCollection_58.addByIndex(0,shapeRepresentation_57);
      OdDAIObjectId productDefinitionShape_58 = OdExIfcModelHelper.createProductDefinitionShape(model, represntationCollection_58);

      productDefinitionShapeSetter_40.Set(productDefinitionShape_58);

      OdDAIObjectId buildingElementProxy_59 = OdExIfcModelHelper.createBuildingElementProxy(model, handleOwnerHistory);
      OdExIfcModelHelper.LocalPlacementPostSetter<OdIfc2x3_IfcBuildingElementProxy> localPlacementSetter_59
        = new OdExIfcModelHelper.LocalPlacementPostSetter<OdIfc2x3_IfcBuildingElementProxy>(model, buildingElementProxy_59);
      OdExIfcModelHelper.ProductDefinitionShapeSetter<OdIfc2x3_IfcBuildingElementProxy> productDefinitionShapeSetter_59
        = new OdExIfcModelHelper.ProductDefinitionShapeSetter<OdIfc2x3_IfcBuildingElementProxy>(model, buildingElementProxy_59);

      OdDAI_OdDAIObjectIdSet relatedElements_60 = new OdDAI_OdDAIObjectIdSet();
      relatedElements_60.Add(OdRxValueHelper.rxvalue_create(buildingElementProxy_59));
      OdDAIObjectId ispetialStructure_60 = OdExIfcModelHelper.createRelContainedInspatialStructure(model, handleOwnerHistory, relatedElements_60, buildingStorey_38);

      OdDAIObjectId direction_61 = OdExIfcModelHelper.createDirection(model, 1, 0, 0);
      OdDAIObjectId direction_62 = OdExIfcModelHelper.createDirection(model, 0, 0, 1);
      OdDAIObjectId cartesian_63 = OdExIfcModelHelper.createCartesianPoint(model, 100, 0, 0);

      OdDAIObjectId axis2Placement3D_64 = OdExIfcModelHelper.createAxis2Placement3D(model, cartesian_63, direction_62, direction_61);
      OdDAIObjectId localPlacement_65 = OdExIfcModelHelper.createLocalPlacement(model, axis2Placement3D_64, null);
      localPlacementSetter_59.Set(localPlacement_65);

      OdDAIObjectId direction_66 = OdExIfcModelHelper.createDirection(model, 1, 0);
      OdDAIObjectId cartesian_67 = OdExIfcModelHelper.createCartesianPoint(model, 0, 0);
      OdDAIObjectId axis2Placement_68 = OdExIfcModelHelper.createAxis2Placement2D(model, cartesian_67, direction_66);

      OdDAIObjectId direction_69 = OdExIfcModelHelper.createDirection(model, 0, 0, 1);
      OdDAIObjectId direction_70 = OdExIfcModelHelper.createDirection(model, 1, 0, 0);
      OdDAIObjectId direction_71 = OdExIfcModelHelper.createDirection(model, 0, 0, 1);
      OdDAIObjectId cartesian_72 = OdExIfcModelHelper.createCartesianPoint(model, 0, 0, 0);
      OdDAIObjectId axis2Placement3D_73 = OdExIfcModelHelper.createAxis2Placement3D(model, cartesian_72, direction_71, direction_70);


      const double radius = 2.0;
      OdDAIObjectId iShapeProfileDef_74 = OdExIfcModelHelper.createIShapeProfileDef(model, OdIfc2x3_IfcProfileTypeEnum.kIfcProfileTypeEnum_AREA, axis2Placement_68, 50.0, 25.0, 5.0, 5.0, radius);

      OdDAIObjectId extrudedAreaSolid_75 = OdExIfcModelHelper.createExtrudedAreaSolid(model, iShapeProfileDef_74, axis2Placement3D_73, direction_69, 20);

      OdDAI_OdDAIObjectIdSet representationItemsCollection_76 = new OdDAI_OdDAIObjectIdSet();
      representationItemsCollection_76.Add(OdRxValueHelper.rxvalue_create(extrudedAreaSolid_75));
      OdDAIObjectId shapeRepresentation_76 = OdExIfcModelHelper.createShapeRepresentation(model, representationContext_11, "Body", "SweptSolid", representationItemsCollection_76);

      OdDAI_OdDAIObjectIdList represntationCollection_77 = new OdDAI_OdDAIObjectIdList();
      represntationCollection_77.addByIndex(0,shapeRepresentation_76);
      OdDAIObjectId productDefinitionShape_77 = OdExIfcModelHelper.createProductDefinitionShape(model, represntationCollection_77);
      productDefinitionShapeSetter_59.Set(productDefinitionShape_77);
    }

    private static THeaderEntity getHeaderFromSection<THeaderEntity>(OdDAI_OdHeaderSection headerSection, OdDAI_OdHeaderEntityType headerType)
    {
      OdDAI_ApplicationInstance headerEntity = headerSection.getEntityByType(headerType);
      if (headerEntity == null)
      {
        Globals.OdAssert("", "Header entity was not created.", 0);
        throw new OdError(OdResult.eNullEntityPointer);
      }

      THeaderEntity castedPointer = Cast<THeaderEntity>(headerEntity);

      if (castedPointer == null)
      {
        Globals.OdAssert("", "Header entity was not created.", 0);
        throw new OdError(OdResult.eIllegalEntityType);
      }

      // Returns valid row pointer. This pointer will be valid until header section destroy.
      return castedPointer;
    }

    private static THeaderEntity Cast<THeaderEntity>(OdRxObject entity)
    {
      Type type = typeof(THeaderEntity);
      var method = type.GetMethod("cast");
      return (THeaderEntity)method.Invoke(null, new object[] { entity });
    }
  }
}