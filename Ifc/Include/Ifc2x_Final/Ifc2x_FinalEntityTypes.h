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

// This file is generated automatically.

#ifndef _IFC2X_FINAL_ENTITYTYPES_H
#define _IFC2X_FINAL_ENTITYTYPES_H

namespace OdIfc2x_final {

enum OdIfcEntityType {

  kIfcOrganization,
  kIfcActorRole,
  kIfcAddress,
  kIfcPostalAddress,
  kIfcTelecomAddress,
  kIfcPerson,
  kIfcPersonAndOrganization,
  kIfcOrganizationRelationship,
  kIfcCalendarDate,
  kIfcLocalTime,
  kIfcCoordinatedUniversalTimeOffset,
  kIfcDateAndTime,
  kIfcClassificationNotation,
  kIfcClassificationNotationFacet,
  kIfcClassificationReference,
  kIfcExternalReference,
  kIfcLibraryReference,
  kIfcLibraryInformation,
  kIfcDocumentReference,
  kIfcDocumentInformation,
  kIfcDocumentElectronicFormat,
  kIfcDocumentInformationRelationship,
  kIfcClassification,
  kIfcClassificationItem,
  kIfcClassificationItemRelationship,
  kIfcConnectionGeometry,
  kIfcConnectionPointGeometry,
  kIfcConnectionCurveGeometry,
  kIfcConnectionSurfaceGeometry,
  kIfcConnectionPortGeometry,
  kIfcGridAxis,
  kIfcVirtualGridIntersection,
  kIfcGridPlacement,
  kIfcObjectPlacement,
  kIfcLocalPlacement,
  kIfcBooleanResult,
  kIfcHalfSpaceSolid,
  kIfcBoxedHalfSpace,
  kIfcBoundingBox,
  kIfcPolygonalBoundedHalfSpace,
  kIfcSolidModel,
  kIfcManifoldSolidBrep,
  kIfcFacetedBrep,
  kIfcFacetedBrepWithVoids,
  kIfcSweptAreaSolid,
  kIfcExtrudedAreaSolid,
  kIfcRevolvedAreaSolid,
  kIfcCsgSolid,
  kIfcSectionedSpine,
  kIfcGeometricSet,
  kIfcFaceBasedSurfaceModel,
  kIfcShellBasedSurfaceModel,
  kIfcBooleanClippingResult,
  kIfcAxis2Placement2D,
  kIfcPlacement,
  kIfcGeometricRepresentationItem,
  kIfcRepresentationItem,
  kIfcMappedItem,
  kIfcRepresentationMap,
  kIfcCartesianTransformationOperator,
  kIfcCartesianTransformationOperator2D,
  kIfcCartesianTransformationOperator2DnonUniform,
  kIfcDirection,
  kIfcCartesianTransformationOperator3D,
  kIfcCartesianTransformationOperator3DnonUniform,
  kIfcCartesianPoint,
  kIfcPoint,
  kIfcCompositeCurveSegment,
  kIfcCurve,
  kIfcBoundedCurve,
  kIfcCompositeCurve,
  kIfc2DCompositeCurve,
  kIfcPolyline,
  kIfcTrimmedCurve,
  kIfcConic,
  kIfcCircle,
  kIfcEllipse,
  kIfcLine,
  kIfcVector,
  kIfcOffsetCurve2D,
  kIfcOffsetCurve3D,
  kIfcSurface,
  kIfcElementarySurface,
  kIfcPlane,
  kIfcAxis2Placement3D,
  kIfcSweptSurface,
  kIfcSurfaceOfRevolution,
  kIfcAxis1Placement,
  kIfcSurfaceOfLinearExtrusion,
  kIfcBoundedSurface,
  kIfcCurveBoundedPlane,
  kIfcRectangularTrimmedSurface,
  kIfcMaterial,
  kIfcMaterialClassificationRelationship,
  kIfcMaterialLayer,
  kIfcMaterialLayerSet,
  kIfcMaterialLayerSetUsage,
  kIfcMaterialList,
  kIfcDerivedUnit,
  kIfcDerivedUnitElement,
  kIfcNamedUnit,
  kIfcContextDependentUnit,
  kIfcConversionBasedUnit,
  kIfcMeasureWithUnit,
  kIfcSIUnit,
  kIfcDimensionalExponents,
  kIfcMonetaryUnit,
  kIfcUnitAssignment,
  kIfcProfileDef,
  kIfcArbitraryClosedProfileDef,
  kIfcArbitraryProfileDefWithVoids,
  kIfcCircleProfileDef,
  kIfcRectangleProfileDef,
  kIfcTrapeziumProfileDef,
  kIfcEllipseProfileDef,
  kIfcRoundedRectangleProfileDef,
  kIfcDerivedProfileDef,
  kIfcArbitraryOpenProfileDef,
  kIfcIshapeProfileDef,
  kIfcCompositeProfileDef,
  kIfcPropertyEnumeratedValue,
  kIfcSimpleProperty,
  kIfcProperty,
  kIfcComplexProperty,
  kIfcPropertySingleValue,
  kIfcPropertyBoundedValue,
  kIfcPropertyTableValue,
  kIfcPropertyReferenceValue,
  kIfcPropertyEnumeration,
  kIfcPhysicalQuantity,
  kIfcQuantityLength,
  kIfcQuantityArea,
  kIfcQuantityVolume,
  kIfcQuantityCount,
  kIfcQuantityWeight,
  kIfcGeometricRepresentationContext,
  kIfcRepresentationContext,
  kIfcRepresentation,
  kIfcShapeRepresentation,
  kIfcShapeAspect,
  kIfcProductDefinitionShape,
  kIfcProductRepresentation,
  kIfcClosedShell,
  kIfcConnectedFaceSet,
  kIfcTopologicalRepresentationItem,
  kIfcEdge,
  kIfcOrientedEdge,
  kIfcVertex,
  kIfcVertexPoint,
  kIfcEdgeCurve,
  kIfcFace,
  kIfcFaceSurface,
  kIfcFaceBound,
  kIfcFaceOuterBound,
  kIfcLoop,
  kIfcPolyLoop,
  kIfcPath,
  kIfcOpenShell,
  kIfcApplication,
  kIfcOwnerHistory,
  kIfcTable,
  kIfcTableRow,
  kIfcProduct,
  kIfcObject,
  kIfcRoot,
  kIfcPropertyDefinition,
  kIfcTypeObject,
  kIfcTypeProduct,
  kIfcPropertySetDefinition,
  kIfcPropertySet,
  kIfcRelDefinesByProperties,
  kIfcRelDefines,
  kIfcRelationship,
  kIfcRelAssigns,
  kIfcRelAssignsToProcess,
  kIfcProcess,
  kIfcRelSequence,
  kIfcRelConnects,
  kIfcRelAssignsToProduct,
  kIfcRelAssignsToControl,
  kIfcControl,
  kIfcRelAssignsToResource,
  kIfcResource,
  kIfcRelAssignsToActor,
  kIfcActor,
  kIfcRelAssignsToGroup,
  kIfcGroup,
  kIfcRelDecomposes,
  kIfcRelAggregates,
  kIfcRelNests,
  kIfcRelAssociates,
  kIfcRelAssociatesClassification,
  kIfcRelAssociatesDocument,
  kIfcRelAssociatesLibrary,
  kIfcRelDefinesByType,
  kIfcRelOverridesProperties,
  kIfcProject,
  kIfcProxy,
  kIfcZone,
  kIfcSystem,
  kIfcRelServicesBuildings,
  kIfcRelVoidsElement,
  kIfcBuildingElement,
  kIfcElement,
  kIfcSpatialStructureElement,
  kIfcBuilding,
  kIfcBuildingStorey,
  kIfcSpace,
  kIfcRelSpaceBoundary,
  kIfcSite,
  kIfcRelContainedInSpatialStructure,
  kIfcGrid,
  kIfcOpeningElement,
  kIfcRelFillsElement,
  kIfcFurnishingElement,
  kIfcElectricalElement,
  kIfcDistributionElement,
  kIfcTransportElement,
  kIfcEquipmentElement,
  kIfcRelConnectsElements,
  kIfcBuildingElementProxy,
  kIfcElementQuantity,
  kIfcRelAssociatesMaterial,
  kIfcRelCoversBldgElements,
  kIfcRelConnectsPathElements,
  kIfcWall,
  kIfcWallStandardCase,
  kIfcCovering,
  kIfcColumn,
  kIfcBeam,
  kIfcDoor,
  kIfcWindow,
  kIfcSlab,
  kIfcRoof,
  kIfcStair,
  kIfcStairFlight,
  kIfcRamp,
  kIfcRampFlight,
  kIfcDoorStyle,
  kIfcWindowStyle,
  kIfcDoorLiningProperties,
  kIfcDoorPanelProperties,
  kIfcWindowLiningProperties,
  kIfcWindowPanelProperties,
  kIfcApproval,
  kIfcConstraint,
  kIfcMetric,
  kIfcMetricBenchmark,
  kIfcMetricValue,
  kIfcObjective,
  kIfcConstraintAggregationRelationship,
  kIfcActionTimeControl,
  kIfcCostValue,
  kIfcCostModifier,
  kIfcCostModifierValue,
  kIfcReferencesCostDocument,
  kIfcCostValueRelationship,
  kIfcCostQuantity,
  kIfcMaterialProperties,
  kIfcMechanicalMaterialProperties,
  kIfcThermalMaterialProperties,
  kIfcHygroscopicMaterialProperties,
  kIfcExtendedMaterialProperties,
  kIfcGeneralMaterialProperties,
  kIfcOpticalMaterialProperties,
  kIfcSurfaceStyleUsage,
  kIfcSurfaceStyle,
  kIfcSurfaceStyleProperties,
  kIfcSurfaceExtendedProperties,
  kIfcSurfaceShadingProperties,
  kIfcSurfaceRenderingProperties,
  kIfcPresentationLightSource,
  kIfcDirectionalLightSource,
  kIfcPointLightSource,
  kIfcSpotLightSource,
  kIfcReferenceGeometry,
  kIfcReferenceEdge,
  kIfcReferenceVertex,
  kIfcReferenceFace,
  kIfcTask,
  kIfcScheduleTimeControl,
  kIfcRelAssignsTasks,
  kIfcWorkControl,
  kIfcWorkPlan,
  kIfcWorkSchedule,
  kIfcRelUsesResource,
  kIfcConstraintUsage,
  kIfcApprovalUsage,
  kIfcRelFlowControlElements,
  kIfcControlElement,
  kIfcRelConnectsPorts,
  kIfcDiscreteElement,
  kIfcDistributionFlowElement,
  kIfcFlowController,
  kIfcFlowFitting,
  kIfcFlowSegment,
  kIfcFlowTerminal,
  kIfcAirTerminal,
  kIfcSanitaryTerminal,
  kIfcHydronicHeater,
  kIfcCoil,
  kIfcHeatTransferDevice,
  kIfcUnitHeater,
  kIfcTubeBundle,
  kIfcHeatExchanger,
  kIfcCoolingTower,
  kIfcChiller,
  kIfcBoiler,
  kIfcFluidMovingDevice,
  kIfcCompressor,
  kIfcFan,
  kIfcPump,
  kIfcTreatmentDevice,
  kIfcAirFilter,
  kIfcStorageDevice,
  kIfcTank,
  kIfcSpaceThermalLoad,
  kIfcFluidFlowProperties,
  kIfcElectricalBaseProperties,
  kIfcElectricalExtendedProperties,
  kIfcAsset,
  kIfcSystemFurnitureElement,
  kIfcFurniture,
  kIfcInventory,
  kIfcManufacturerInformation,
  kIfcCostSchedule,
  kIfcBudget,
  kIfcCost,
  kIfcProjectOrder,
  kIfcChangeOrder,
  kIfcPurchaseOrder,
  kIfcWorkOrder,
  kIfcRelCostsObjects,
  kIfcSpaceProgramGroup,
  kIfcRelInteractionRequirements,
  kIfcCompartment,
  kIfcOccupant,
  kIfcSpaceProgram,
  kIfcRelOccupiesSpaces,
  kIfcPermeableCoveringProperties,
  kIfcConnectionConstraint,
  kIfcRailing,
  kIfcCurtainWall,
  kIfcAssessory,
  kIfcBuiltIn,
  kIfcCMDocPackage,
  kIfcConstructionEquipmentResource,
  kIfcLaborResource,
  kIfcConstructionProductResource,
  kIfcSubContractResource,
  kIfcConstructionMaterialResource,
  kIfcCrewResource,
  kIfcRelAggregatesResources,
  kIfcElectricMotor,
  kIfcLightFixture,
  kIfcOutlet,
  kIfcElectricalAppliance,
  kIfcFurnitureStandard,
  kIfcEquipmentStandard,
  kIfcMaintenanceRecord,
  kIfcRelMaintenanceEvent,
  kIfcRelAssignsFMStandard,
  kIfcMaintenanceWorkOrder,
  kIfcMove,
  kIfcActuator,
  kIfcController,
  kIfcSensor,
  kIfcValve,
  kIfcAirTerminalBox,
  kIfcDamper

, kAny
};


} // namespace

#endif // _IFC2X_FINAL_ENTITYTYPES_H

