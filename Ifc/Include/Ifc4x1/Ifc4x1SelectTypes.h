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

#ifndef _IFC4X1_SELECT_TYPES_H
#define _IFC4X1_SELECT_TYPES_H

#include "daiNamedType.h"
#include "daiSelectWrapper.h"
#include "daiValueTypes.h"
#include "Ifc4x1CollectionTypes.h"
#include "Ifc4x1SimpleTypes.h"
#include "Ifc4x1Enum.h"
#include "Ifc4x1BuildOption.h"

namespace OdIfc4x1 {

class IfcOrganization;
class IfcPerson;
class IfcPersonAndOrganization;
class IfcMeasureWithUnit;
class IfcReference;
class IfcAxis2Placement2D;
class IfcAxis2Placement3D;
class IfcBooleanResult;
class IfcCsgPrimitive3D;
class IfcHalfSpaceSolid;
class IfcSolidModel;
class IfcTessellatedFaceSet;
class IfcClassification;
class IfcClassificationReference;
class IfcColourSpecification;
class IfcPreDefinedColour;
class IfcColourRgb;
class IfcCoordinateReferenceSystem;
class IfcGeometricRepresentationContext;
class IfcCurveStyleFontAndScaling;
class IfcCurveStyleFont;
class IfcPreDefinedCurveFont;
class IfcCompositeCurveOnSurface;
class IfcPcurve;
class IfcSurfaceCurve;
class IfcBoundedCurve;
class IfcEdgeCurve;
class IfcObjectDefinition;
class IfcPropertyDefinition;
class IfcDocumentInformation;
class IfcDocumentReference;
class IfcExternallyDefinedHatchStyle;
class IfcFillAreaStyleHatching;
class IfcFillAreaStyleTiles;
class IfcCurve;
class IfcPoint;
class IfcSurface;
class IfcDirection;
class IfcVirtualGridIntersection;
class IfcVector;
class IfcRepresentation;
class IfcRepresentationItem;
class IfcLibraryInformation;
class IfcLibraryReference;
class IfcExternalReference;
class IfcLightIntensityDistribution;
class IfcMaterialDefinition;
class IfcMaterialList;
class IfcMaterialUsageDefinition;
class IfcAppliedValue;
class IfcTable;
class IfcTimeSeries;
class IfcAddress;
class IfcVertexPoint;
class IfcCurveStyle;
class IfcFillAreaStyle;
class IfcSurfaceStyle;
class IfcTextStyle;
class IfcProcess;
class IfcTypeProcess;
class IfcProductDefinitionShape;
class IfcRepresentationMap;
class IfcProduct;
class IfcTypeProduct;
class IfcPropertySetDefinition;
class IfcActorRole;
class IfcApproval;
class IfcConstraint;
class IfcContextDependentUnit;
class IfcConversionBasedUnit;
class IfcExternalInformation;
class IfcPhysicalQuantity;
class IfcProfileDef;
class IfcPropertyAbstraction;
class IfcShapeAspect;
class IfcResource;
class IfcTypeResource;
class IfcClosedShell;
class IfcOpenShell;
class IfcExternalSpatialElement;
class IfcSpace;
class IfcElement;
class IfcStructuralItem;
class IfcPresentationStyle;
class IfcPresentationStyleAssignment;
class IfcFaceBasedSurfaceModel;
class IfcFaceSurface;
class IfcExternallyDefinedSurfaceStyle;
class IfcSurfaceStyleLighting;
class IfcSurfaceStyleRefraction;
class IfcSurfaceStyleShading;
class IfcSurfaceStyleWithTextures;
class IfcExternallyDefinedTextFont;
class IfcPreDefinedTextFont;
class IfcCartesianPoint;
class IfcDerivedUnit;
class IfcMonetaryUnit;
class IfcNamedUnit;

extern const OdAnsiString sCommonUnset;

class IFC4X1_EXPORT IfcActorSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcActorSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcOrganization();
  void setIfcOrganization(IfcOrganization* val);

  bool isIfcPerson();
  void setIfcPerson(IfcPerson* val);

  bool isIfcPersonAndOrganization();
  void setIfcPersonAndOrganization(IfcPersonAndOrganization* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcActorSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcActorSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcAppliedValueSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcAppliedValueSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcAbsorbedDoseMeasure();
  void setIfcAbsorbedDoseMeasure(IfcAbsorbedDoseMeasure val);

  bool isIfcAccelerationMeasure();
  void setIfcAccelerationMeasure(IfcAccelerationMeasure val);

  bool isIfcAmountOfSubstanceMeasure();
  void setIfcAmountOfSubstanceMeasure(IfcAmountOfSubstanceMeasure val);

  bool isIfcAngularVelocityMeasure();
  void setIfcAngularVelocityMeasure(IfcAngularVelocityMeasure val);

  bool isIfcAreaDensityMeasure();
  void setIfcAreaDensityMeasure(IfcAreaDensityMeasure val);

  bool isIfcAreaMeasure();
  void setIfcAreaMeasure(IfcAreaMeasure val);

  bool isIfcBinary();
  void setIfcBinary(IfcBinary val);

  bool isIfcBoolean();
  void setIfcBoolean(IfcBoolean val);

  bool isIfcComplexNumber();
  void setIfcComplexNumber(OdArray<double > val);

  bool isIfcCompoundPlaneAngleMeasure();
  void setIfcCompoundPlaneAngleMeasure(OdArray<int > val);

  bool isIfcContextDependentMeasure();
  void setIfcContextDependentMeasure(IfcContextDependentMeasure val);

  bool isIfcCountMeasure();
  void setIfcCountMeasure(IfcCountMeasure val);

  bool isIfcCurvatureMeasure();
  void setIfcCurvatureMeasure(IfcCurvatureMeasure val);

  bool isIfcDate();
  void setIfcDate(IfcDate val);

  bool isIfcDateTime();
  void setIfcDateTime(IfcDateTime val);

  bool isIfcDescriptiveMeasure();
  void setIfcDescriptiveMeasure(IfcDescriptiveMeasure val);

  bool isIfcDoseEquivalentMeasure();
  void setIfcDoseEquivalentMeasure(IfcDoseEquivalentMeasure val);

  bool isIfcDuration();
  void setIfcDuration(IfcDuration val);

  bool isIfcDynamicViscosityMeasure();
  void setIfcDynamicViscosityMeasure(IfcDynamicViscosityMeasure val);

  bool isIfcElectricCapacitanceMeasure();
  void setIfcElectricCapacitanceMeasure(IfcElectricCapacitanceMeasure val);

  bool isIfcElectricChargeMeasure();
  void setIfcElectricChargeMeasure(IfcElectricChargeMeasure val);

  bool isIfcElectricConductanceMeasure();
  void setIfcElectricConductanceMeasure(IfcElectricConductanceMeasure val);

  bool isIfcElectricCurrentMeasure();
  void setIfcElectricCurrentMeasure(IfcElectricCurrentMeasure val);

  bool isIfcElectricResistanceMeasure();
  void setIfcElectricResistanceMeasure(IfcElectricResistanceMeasure val);

  bool isIfcElectricVoltageMeasure();
  void setIfcElectricVoltageMeasure(IfcElectricVoltageMeasure val);

  bool isIfcEnergyMeasure();
  void setIfcEnergyMeasure(IfcEnergyMeasure val);

  bool isIfcForceMeasure();
  void setIfcForceMeasure(IfcForceMeasure val);

  bool isIfcFrequencyMeasure();
  void setIfcFrequencyMeasure(IfcFrequencyMeasure val);

  bool isIfcHeatFluxDensityMeasure();
  void setIfcHeatFluxDensityMeasure(IfcHeatFluxDensityMeasure val);

  bool isIfcHeatingValueMeasure();
  void setIfcHeatingValueMeasure(IfcHeatingValueMeasure val);

  bool isIfcIdentifier();
  void setIfcIdentifier(IfcIdentifier val);

  bool isIfcIlluminanceMeasure();
  void setIfcIlluminanceMeasure(IfcIlluminanceMeasure val);

  bool isIfcInductanceMeasure();
  void setIfcInductanceMeasure(IfcInductanceMeasure val);

  bool isIfcInteger();
  void setIfcInteger(IfcInteger val);

  bool isIfcIntegerCountRateMeasure();
  void setIfcIntegerCountRateMeasure(IfcIntegerCountRateMeasure val);

  bool isIfcIonConcentrationMeasure();
  void setIfcIonConcentrationMeasure(IfcIonConcentrationMeasure val);

  bool isIfcIsothermalMoistureCapacityMeasure();
  void setIfcIsothermalMoistureCapacityMeasure(IfcIsothermalMoistureCapacityMeasure val);

  bool isIfcKinematicViscosityMeasure();
  void setIfcKinematicViscosityMeasure(IfcKinematicViscosityMeasure val);

  bool isIfcLabel();
  void setIfcLabel(IfcLabel val);

  bool isIfcLengthMeasure();
  void setIfcLengthMeasure(IfcLengthMeasure val);

  bool isIfcLinearForceMeasure();
  void setIfcLinearForceMeasure(IfcLinearForceMeasure val);

  bool isIfcLinearMomentMeasure();
  void setIfcLinearMomentMeasure(IfcLinearMomentMeasure val);

  bool isIfcLinearStiffnessMeasure();
  void setIfcLinearStiffnessMeasure(IfcLinearStiffnessMeasure val);

  bool isIfcLinearVelocityMeasure();
  void setIfcLinearVelocityMeasure(IfcLinearVelocityMeasure val);

  bool isIfcLogical();
  void setIfcLogical(IfcLogical val);

  bool isIfcLuminousFluxMeasure();
  void setIfcLuminousFluxMeasure(IfcLuminousFluxMeasure val);

  bool isIfcLuminousIntensityDistributionMeasure();
  void setIfcLuminousIntensityDistributionMeasure(IfcLuminousIntensityDistributionMeasure val);

  bool isIfcLuminousIntensityMeasure();
  void setIfcLuminousIntensityMeasure(IfcLuminousIntensityMeasure val);

  bool isIfcMagneticFluxDensityMeasure();
  void setIfcMagneticFluxDensityMeasure(IfcMagneticFluxDensityMeasure val);

  bool isIfcMagneticFluxMeasure();
  void setIfcMagneticFluxMeasure(IfcMagneticFluxMeasure val);

  bool isIfcMassDensityMeasure();
  void setIfcMassDensityMeasure(IfcMassDensityMeasure val);

  bool isIfcMassFlowRateMeasure();
  void setIfcMassFlowRateMeasure(IfcMassFlowRateMeasure val);

  bool isIfcMassMeasure();
  void setIfcMassMeasure(IfcMassMeasure val);

  bool isIfcMassPerLengthMeasure();
  void setIfcMassPerLengthMeasure(IfcMassPerLengthMeasure val);

  bool isIfcMeasureWithUnit();
  void setIfcMeasureWithUnit(IfcMeasureWithUnit* val);

  bool isIfcModulusOfElasticityMeasure();
  void setIfcModulusOfElasticityMeasure(IfcModulusOfElasticityMeasure val);

  bool isIfcModulusOfLinearSubgradeReactionMeasure();
  void setIfcModulusOfLinearSubgradeReactionMeasure(IfcModulusOfLinearSubgradeReactionMeasure val);

  bool isIfcModulusOfRotationalSubgradeReactionMeasure();
  void setIfcModulusOfRotationalSubgradeReactionMeasure(IfcModulusOfRotationalSubgradeReactionMeasure val);

  bool isIfcModulusOfSubgradeReactionMeasure();
  void setIfcModulusOfSubgradeReactionMeasure(IfcModulusOfSubgradeReactionMeasure val);

  bool isIfcMoistureDiffusivityMeasure();
  void setIfcMoistureDiffusivityMeasure(IfcMoistureDiffusivityMeasure val);

  bool isIfcMolecularWeightMeasure();
  void setIfcMolecularWeightMeasure(IfcMolecularWeightMeasure val);

  bool isIfcMomentOfInertiaMeasure();
  void setIfcMomentOfInertiaMeasure(IfcMomentOfInertiaMeasure val);

  bool isIfcMonetaryMeasure();
  void setIfcMonetaryMeasure(IfcMonetaryMeasure val);

  bool isIfcNonNegativeLengthMeasure();
  void setIfcNonNegativeLengthMeasure(IfcNonNegativeLengthMeasure val);

  bool isIfcNormalisedRatioMeasure();
  void setIfcNormalisedRatioMeasure(IfcNormalisedRatioMeasure val);

  bool isIfcNumericMeasure();
  void setIfcNumericMeasure(IfcNumericMeasure val);

  bool isIfcPHMeasure();
  void setIfcPHMeasure(IfcPHMeasure val);

  bool isIfcParameterValue();
  void setIfcParameterValue(IfcParameterValue val);

  bool isIfcPlanarForceMeasure();
  void setIfcPlanarForceMeasure(IfcPlanarForceMeasure val);

  bool isIfcPlaneAngleMeasure();
  void setIfcPlaneAngleMeasure(IfcPlaneAngleMeasure val);

  bool isIfcPositiveInteger();
  void setIfcPositiveInteger(IfcPositiveInteger val);

  bool isIfcPositiveLengthMeasure();
  void setIfcPositiveLengthMeasure(IfcPositiveLengthMeasure val);

  bool isIfcPositivePlaneAngleMeasure();
  void setIfcPositivePlaneAngleMeasure(IfcPositivePlaneAngleMeasure val);

  bool isIfcPositiveRatioMeasure();
  void setIfcPositiveRatioMeasure(IfcPositiveRatioMeasure val);

  bool isIfcPowerMeasure();
  void setIfcPowerMeasure(IfcPowerMeasure val);

  bool isIfcPressureMeasure();
  void setIfcPressureMeasure(IfcPressureMeasure val);

  bool isIfcRadioActivityMeasure();
  void setIfcRadioActivityMeasure(IfcRadioActivityMeasure val);

  bool isIfcRatioMeasure();
  void setIfcRatioMeasure(IfcRatioMeasure val);

  bool isIfcReal();
  void setIfcReal(IfcReal val);

  bool isIfcReference();
  void setIfcReference(IfcReference* val);

  bool isIfcRotationalFrequencyMeasure();
  void setIfcRotationalFrequencyMeasure(IfcRotationalFrequencyMeasure val);

  bool isIfcRotationalMassMeasure();
  void setIfcRotationalMassMeasure(IfcRotationalMassMeasure val);

  bool isIfcRotationalStiffnessMeasure();
  void setIfcRotationalStiffnessMeasure(IfcRotationalStiffnessMeasure val);

  bool isIfcSectionModulusMeasure();
  void setIfcSectionModulusMeasure(IfcSectionModulusMeasure val);

  bool isIfcSectionalAreaIntegralMeasure();
  void setIfcSectionalAreaIntegralMeasure(IfcSectionalAreaIntegralMeasure val);

  bool isIfcShearModulusMeasure();
  void setIfcShearModulusMeasure(IfcShearModulusMeasure val);

  bool isIfcSolidAngleMeasure();
  void setIfcSolidAngleMeasure(IfcSolidAngleMeasure val);

  bool isIfcSoundPowerLevelMeasure();
  void setIfcSoundPowerLevelMeasure(IfcSoundPowerLevelMeasure val);

  bool isIfcSoundPowerMeasure();
  void setIfcSoundPowerMeasure(IfcSoundPowerMeasure val);

  bool isIfcSoundPressureLevelMeasure();
  void setIfcSoundPressureLevelMeasure(IfcSoundPressureLevelMeasure val);

  bool isIfcSoundPressureMeasure();
  void setIfcSoundPressureMeasure(IfcSoundPressureMeasure val);

  bool isIfcSpecificHeatCapacityMeasure();
  void setIfcSpecificHeatCapacityMeasure(IfcSpecificHeatCapacityMeasure val);

  bool isIfcTemperatureGradientMeasure();
  void setIfcTemperatureGradientMeasure(IfcTemperatureGradientMeasure val);

  bool isIfcTemperatureRateOfChangeMeasure();
  void setIfcTemperatureRateOfChangeMeasure(IfcTemperatureRateOfChangeMeasure val);

  bool isIfcText();
  void setIfcText(IfcText val);

  bool isIfcThermalAdmittanceMeasure();
  void setIfcThermalAdmittanceMeasure(IfcThermalAdmittanceMeasure val);

  bool isIfcThermalConductivityMeasure();
  void setIfcThermalConductivityMeasure(IfcThermalConductivityMeasure val);

  bool isIfcThermalExpansionCoefficientMeasure();
  void setIfcThermalExpansionCoefficientMeasure(IfcThermalExpansionCoefficientMeasure val);

  bool isIfcThermalResistanceMeasure();
  void setIfcThermalResistanceMeasure(IfcThermalResistanceMeasure val);

  bool isIfcThermalTransmittanceMeasure();
  void setIfcThermalTransmittanceMeasure(IfcThermalTransmittanceMeasure val);

  bool isIfcThermodynamicTemperatureMeasure();
  void setIfcThermodynamicTemperatureMeasure(IfcThermodynamicTemperatureMeasure val);

  bool isIfcTime();
  void setIfcTime(IfcTime val);

  bool isIfcTimeMeasure();
  void setIfcTimeMeasure(IfcTimeMeasure val);

  bool isIfcTimeStamp();
  void setIfcTimeStamp(IfcTimeStamp val);

  bool isIfcTorqueMeasure();
  void setIfcTorqueMeasure(IfcTorqueMeasure val);

  bool isIfcVaporPermeabilityMeasure();
  void setIfcVaporPermeabilityMeasure(IfcVaporPermeabilityMeasure val);

  bool isIfcVolumeMeasure();
  void setIfcVolumeMeasure(IfcVolumeMeasure val);

  bool isIfcVolumetricFlowRateMeasure();
  void setIfcVolumetricFlowRateMeasure(IfcVolumetricFlowRateMeasure val);

  bool isIfcWarpingConstantMeasure();
  void setIfcWarpingConstantMeasure(IfcWarpingConstantMeasure val);

  bool isIfcWarpingMomentMeasure();
  void setIfcWarpingMomentMeasure(IfcWarpingMomentMeasure val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcAppliedValueSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcAppliedValueSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcAxis2Placement
  : public OdDAI::SelectWrapper
{
public:

  IfcAxis2Placement(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcAxis2Placement2D();
  void setIfcAxis2Placement2D(IfcAxis2Placement2D* val);

  bool isIfcAxis2Placement3D();
  void setIfcAxis2Placement3D(IfcAxis2Placement3D* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcAxis2PlacementTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcAxis2PlacementTypeProvider& instance();


};

class IFC4X1_EXPORT IfcBendingParameterSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcBendingParameterSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcLengthMeasure();
  void setIfcLengthMeasure(IfcLengthMeasure val);

  bool isIfcPlaneAngleMeasure();
  void setIfcPlaneAngleMeasure(IfcPlaneAngleMeasure val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcBendingParameterSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcBendingParameterSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcBooleanOperand
  : public OdDAI::SelectWrapper
{
public:

  IfcBooleanOperand(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcBooleanResult();
  void setIfcBooleanResult(IfcBooleanResult* val);

  bool isIfcCsgPrimitive3D();
  void setIfcCsgPrimitive3D(IfcCsgPrimitive3D* val);

  bool isIfcHalfSpaceSolid();
  void setIfcHalfSpaceSolid(IfcHalfSpaceSolid* val);

  bool isIfcSolidModel();
  void setIfcSolidModel(IfcSolidModel* val);

  bool isIfcTessellatedFaceSet();
  void setIfcTessellatedFaceSet(IfcTessellatedFaceSet* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcBooleanOperandTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcBooleanOperandTypeProvider& instance();


};

class IFC4X1_EXPORT IfcClassificationReferenceSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcClassificationReferenceSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcClassification();
  void setIfcClassification(IfcClassification* val);

  bool isIfcClassificationReference();
  void setIfcClassificationReference(IfcClassificationReference* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcClassificationReferenceSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcClassificationReferenceSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcClassificationSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcClassificationSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcClassification();
  void setIfcClassification(IfcClassification* val);

  bool isIfcClassificationReference();
  void setIfcClassificationReference(IfcClassificationReference* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcClassificationSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcClassificationSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcColour
  : public OdDAI::SelectWrapper
{
public:

  IfcColour(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcColourSpecification();
  void setIfcColourSpecification(IfcColourSpecification* val);

  bool isIfcPreDefinedColour();
  void setIfcPreDefinedColour(IfcPreDefinedColour* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcColourTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcColourTypeProvider& instance();


};

class IFC4X1_EXPORT IfcColourOrFactor
  : public OdDAI::SelectWrapper
{
public:

  IfcColourOrFactor(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcColourRgb();
  void setIfcColourRgb(IfcColourRgb* val);

  bool isIfcNormalisedRatioMeasure();
  void setIfcNormalisedRatioMeasure(IfcNormalisedRatioMeasure val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcColourOrFactorTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcColourOrFactorTypeProvider& instance();


};

class IFC4X1_EXPORT IfcCoordinateReferenceSystemSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcCoordinateReferenceSystemSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcCoordinateReferenceSystem();
  void setIfcCoordinateReferenceSystem(IfcCoordinateReferenceSystem* val);

  bool isIfcGeometricRepresentationContext();
  void setIfcGeometricRepresentationContext(IfcGeometricRepresentationContext* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcCoordinateReferenceSystemSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcCoordinateReferenceSystemSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcCsgSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcCsgSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcBooleanResult();
  void setIfcBooleanResult(IfcBooleanResult* val);

  bool isIfcCsgPrimitive3D();
  void setIfcCsgPrimitive3D(IfcCsgPrimitive3D* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcCsgSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcCsgSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcCurveFontOrScaledCurveFontSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcCurveFontOrScaledCurveFontSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcCurveStyleFont();
  void setIfcCurveStyleFont(IfcCurveStyleFont* val);

  bool isIfcCurveStyleFontAndScaling();
  void setIfcCurveStyleFontAndScaling(IfcCurveStyleFontAndScaling* val);

  bool isIfcPreDefinedCurveFont();
  void setIfcPreDefinedCurveFont(IfcPreDefinedCurveFont* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcCurveFontOrScaledCurveFontSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcCurveFontOrScaledCurveFontSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcCurveOnSurface
  : public OdDAI::SelectWrapper
{
public:

  IfcCurveOnSurface(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcCompositeCurveOnSurface();
  void setIfcCompositeCurveOnSurface(IfcCompositeCurveOnSurface* val);

  bool isIfcPcurve();
  void setIfcPcurve(IfcPcurve* val);

  bool isIfcSurfaceCurve();
  void setIfcSurfaceCurve(IfcSurfaceCurve* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcCurveOnSurfaceTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcCurveOnSurfaceTypeProvider& instance();


};

class IFC4X1_EXPORT IfcCurveOrEdgeCurve
  : public OdDAI::SelectWrapper
{
public:

  IfcCurveOrEdgeCurve(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcBoundedCurve();
  void setIfcBoundedCurve(IfcBoundedCurve* val);

  bool isIfcEdgeCurve();
  void setIfcEdgeCurve(IfcEdgeCurve* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcCurveOrEdgeCurveTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcCurveOrEdgeCurveTypeProvider& instance();


};

class IFC4X1_EXPORT IfcCurveStyleFontSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcCurveStyleFontSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcCurveStyleFont();
  void setIfcCurveStyleFont(IfcCurveStyleFont* val);

  bool isIfcPreDefinedCurveFont();
  void setIfcPreDefinedCurveFont(IfcPreDefinedCurveFont* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcCurveStyleFontSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcCurveStyleFontSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcDefinitionSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcDefinitionSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcObjectDefinition();
  void setIfcObjectDefinition(IfcObjectDefinition* val);

  bool isIfcPropertyDefinition();
  void setIfcPropertyDefinition(IfcPropertyDefinition* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcDefinitionSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcDefinitionSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcDerivedMeasureValue
  : public OdDAI::SelectWrapper
{
public:

  IfcDerivedMeasureValue(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcAbsorbedDoseMeasure();
  void setIfcAbsorbedDoseMeasure(IfcAbsorbedDoseMeasure val);

  bool isIfcAccelerationMeasure();
  void setIfcAccelerationMeasure(IfcAccelerationMeasure val);

  bool isIfcAngularVelocityMeasure();
  void setIfcAngularVelocityMeasure(IfcAngularVelocityMeasure val);

  bool isIfcAreaDensityMeasure();
  void setIfcAreaDensityMeasure(IfcAreaDensityMeasure val);

  bool isIfcCompoundPlaneAngleMeasure();
  void setIfcCompoundPlaneAngleMeasure(OdArray<int > val);

  bool isIfcCurvatureMeasure();
  void setIfcCurvatureMeasure(IfcCurvatureMeasure val);

  bool isIfcDoseEquivalentMeasure();
  void setIfcDoseEquivalentMeasure(IfcDoseEquivalentMeasure val);

  bool isIfcDynamicViscosityMeasure();
  void setIfcDynamicViscosityMeasure(IfcDynamicViscosityMeasure val);

  bool isIfcElectricCapacitanceMeasure();
  void setIfcElectricCapacitanceMeasure(IfcElectricCapacitanceMeasure val);

  bool isIfcElectricChargeMeasure();
  void setIfcElectricChargeMeasure(IfcElectricChargeMeasure val);

  bool isIfcElectricConductanceMeasure();
  void setIfcElectricConductanceMeasure(IfcElectricConductanceMeasure val);

  bool isIfcElectricResistanceMeasure();
  void setIfcElectricResistanceMeasure(IfcElectricResistanceMeasure val);

  bool isIfcElectricVoltageMeasure();
  void setIfcElectricVoltageMeasure(IfcElectricVoltageMeasure val);

  bool isIfcEnergyMeasure();
  void setIfcEnergyMeasure(IfcEnergyMeasure val);

  bool isIfcForceMeasure();
  void setIfcForceMeasure(IfcForceMeasure val);

  bool isIfcFrequencyMeasure();
  void setIfcFrequencyMeasure(IfcFrequencyMeasure val);

  bool isIfcHeatFluxDensityMeasure();
  void setIfcHeatFluxDensityMeasure(IfcHeatFluxDensityMeasure val);

  bool isIfcHeatingValueMeasure();
  void setIfcHeatingValueMeasure(IfcHeatingValueMeasure val);

  bool isIfcIlluminanceMeasure();
  void setIfcIlluminanceMeasure(IfcIlluminanceMeasure val);

  bool isIfcInductanceMeasure();
  void setIfcInductanceMeasure(IfcInductanceMeasure val);

  bool isIfcIntegerCountRateMeasure();
  void setIfcIntegerCountRateMeasure(IfcIntegerCountRateMeasure val);

  bool isIfcIonConcentrationMeasure();
  void setIfcIonConcentrationMeasure(IfcIonConcentrationMeasure val);

  bool isIfcIsothermalMoistureCapacityMeasure();
  void setIfcIsothermalMoistureCapacityMeasure(IfcIsothermalMoistureCapacityMeasure val);

  bool isIfcKinematicViscosityMeasure();
  void setIfcKinematicViscosityMeasure(IfcKinematicViscosityMeasure val);

  bool isIfcLinearForceMeasure();
  void setIfcLinearForceMeasure(IfcLinearForceMeasure val);

  bool isIfcLinearMomentMeasure();
  void setIfcLinearMomentMeasure(IfcLinearMomentMeasure val);

  bool isIfcLinearStiffnessMeasure();
  void setIfcLinearStiffnessMeasure(IfcLinearStiffnessMeasure val);

  bool isIfcLinearVelocityMeasure();
  void setIfcLinearVelocityMeasure(IfcLinearVelocityMeasure val);

  bool isIfcLuminousFluxMeasure();
  void setIfcLuminousFluxMeasure(IfcLuminousFluxMeasure val);

  bool isIfcLuminousIntensityDistributionMeasure();
  void setIfcLuminousIntensityDistributionMeasure(IfcLuminousIntensityDistributionMeasure val);

  bool isIfcMagneticFluxDensityMeasure();
  void setIfcMagneticFluxDensityMeasure(IfcMagneticFluxDensityMeasure val);

  bool isIfcMagneticFluxMeasure();
  void setIfcMagneticFluxMeasure(IfcMagneticFluxMeasure val);

  bool isIfcMassDensityMeasure();
  void setIfcMassDensityMeasure(IfcMassDensityMeasure val);

  bool isIfcMassFlowRateMeasure();
  void setIfcMassFlowRateMeasure(IfcMassFlowRateMeasure val);

  bool isIfcMassPerLengthMeasure();
  void setIfcMassPerLengthMeasure(IfcMassPerLengthMeasure val);

  bool isIfcModulusOfElasticityMeasure();
  void setIfcModulusOfElasticityMeasure(IfcModulusOfElasticityMeasure val);

  bool isIfcModulusOfLinearSubgradeReactionMeasure();
  void setIfcModulusOfLinearSubgradeReactionMeasure(IfcModulusOfLinearSubgradeReactionMeasure val);

  bool isIfcModulusOfRotationalSubgradeReactionMeasure();
  void setIfcModulusOfRotationalSubgradeReactionMeasure(IfcModulusOfRotationalSubgradeReactionMeasure val);

  bool isIfcModulusOfSubgradeReactionMeasure();
  void setIfcModulusOfSubgradeReactionMeasure(IfcModulusOfSubgradeReactionMeasure val);

  bool isIfcMoistureDiffusivityMeasure();
  void setIfcMoistureDiffusivityMeasure(IfcMoistureDiffusivityMeasure val);

  bool isIfcMolecularWeightMeasure();
  void setIfcMolecularWeightMeasure(IfcMolecularWeightMeasure val);

  bool isIfcMomentOfInertiaMeasure();
  void setIfcMomentOfInertiaMeasure(IfcMomentOfInertiaMeasure val);

  bool isIfcMonetaryMeasure();
  void setIfcMonetaryMeasure(IfcMonetaryMeasure val);

  bool isIfcPHMeasure();
  void setIfcPHMeasure(IfcPHMeasure val);

  bool isIfcPlanarForceMeasure();
  void setIfcPlanarForceMeasure(IfcPlanarForceMeasure val);

  bool isIfcPowerMeasure();
  void setIfcPowerMeasure(IfcPowerMeasure val);

  bool isIfcPressureMeasure();
  void setIfcPressureMeasure(IfcPressureMeasure val);

  bool isIfcRadioActivityMeasure();
  void setIfcRadioActivityMeasure(IfcRadioActivityMeasure val);

  bool isIfcRotationalFrequencyMeasure();
  void setIfcRotationalFrequencyMeasure(IfcRotationalFrequencyMeasure val);

  bool isIfcRotationalMassMeasure();
  void setIfcRotationalMassMeasure(IfcRotationalMassMeasure val);

  bool isIfcRotationalStiffnessMeasure();
  void setIfcRotationalStiffnessMeasure(IfcRotationalStiffnessMeasure val);

  bool isIfcSectionModulusMeasure();
  void setIfcSectionModulusMeasure(IfcSectionModulusMeasure val);

  bool isIfcSectionalAreaIntegralMeasure();
  void setIfcSectionalAreaIntegralMeasure(IfcSectionalAreaIntegralMeasure val);

  bool isIfcShearModulusMeasure();
  void setIfcShearModulusMeasure(IfcShearModulusMeasure val);

  bool isIfcSoundPowerLevelMeasure();
  void setIfcSoundPowerLevelMeasure(IfcSoundPowerLevelMeasure val);

  bool isIfcSoundPowerMeasure();
  void setIfcSoundPowerMeasure(IfcSoundPowerMeasure val);

  bool isIfcSoundPressureLevelMeasure();
  void setIfcSoundPressureLevelMeasure(IfcSoundPressureLevelMeasure val);

  bool isIfcSoundPressureMeasure();
  void setIfcSoundPressureMeasure(IfcSoundPressureMeasure val);

  bool isIfcSpecificHeatCapacityMeasure();
  void setIfcSpecificHeatCapacityMeasure(IfcSpecificHeatCapacityMeasure val);

  bool isIfcTemperatureGradientMeasure();
  void setIfcTemperatureGradientMeasure(IfcTemperatureGradientMeasure val);

  bool isIfcTemperatureRateOfChangeMeasure();
  void setIfcTemperatureRateOfChangeMeasure(IfcTemperatureRateOfChangeMeasure val);

  bool isIfcThermalAdmittanceMeasure();
  void setIfcThermalAdmittanceMeasure(IfcThermalAdmittanceMeasure val);

  bool isIfcThermalConductivityMeasure();
  void setIfcThermalConductivityMeasure(IfcThermalConductivityMeasure val);

  bool isIfcThermalExpansionCoefficientMeasure();
  void setIfcThermalExpansionCoefficientMeasure(IfcThermalExpansionCoefficientMeasure val);

  bool isIfcThermalResistanceMeasure();
  void setIfcThermalResistanceMeasure(IfcThermalResistanceMeasure val);

  bool isIfcThermalTransmittanceMeasure();
  void setIfcThermalTransmittanceMeasure(IfcThermalTransmittanceMeasure val);

  bool isIfcTorqueMeasure();
  void setIfcTorqueMeasure(IfcTorqueMeasure val);

  bool isIfcVaporPermeabilityMeasure();
  void setIfcVaporPermeabilityMeasure(IfcVaporPermeabilityMeasure val);

  bool isIfcVolumetricFlowRateMeasure();
  void setIfcVolumetricFlowRateMeasure(IfcVolumetricFlowRateMeasure val);

  bool isIfcWarpingConstantMeasure();
  void setIfcWarpingConstantMeasure(IfcWarpingConstantMeasure val);

  bool isIfcWarpingMomentMeasure();
  void setIfcWarpingMomentMeasure(IfcWarpingMomentMeasure val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcDerivedMeasureValueTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcDerivedMeasureValueTypeProvider& instance();


};

class IFC4X1_EXPORT IfcDocumentSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcDocumentSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcDocumentInformation();
  void setIfcDocumentInformation(IfcDocumentInformation* val);

  bool isIfcDocumentReference();
  void setIfcDocumentReference(IfcDocumentReference* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcDocumentSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcDocumentSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcFillStyleSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcFillStyleSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcColourSpecification();
  void setIfcColourSpecification(IfcColourSpecification* val);

  bool isIfcExternallyDefinedHatchStyle();
  void setIfcExternallyDefinedHatchStyle(IfcExternallyDefinedHatchStyle* val);

  bool isIfcFillAreaStyleHatching();
  void setIfcFillAreaStyleHatching(IfcFillAreaStyleHatching* val);

  bool isIfcFillAreaStyleTiles();
  void setIfcFillAreaStyleTiles(IfcFillAreaStyleTiles* val);

  bool isIfcPreDefinedColour();
  void setIfcPreDefinedColour(IfcPreDefinedColour* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcFillStyleSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcFillStyleSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcGeometricSetSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcGeometricSetSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcCurve();
  void setIfcCurve(IfcCurve* val);

  bool isIfcPoint();
  void setIfcPoint(IfcPoint* val);

  bool isIfcSurface();
  void setIfcSurface(IfcSurface* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcGeometricSetSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcGeometricSetSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcGridPlacementDirectionSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcGridPlacementDirectionSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcDirection();
  void setIfcDirection(IfcDirection* val);

  bool isIfcVirtualGridIntersection();
  void setIfcVirtualGridIntersection(IfcVirtualGridIntersection* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcGridPlacementDirectionSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcGridPlacementDirectionSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcHatchLineDistanceSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcHatchLineDistanceSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcPositiveLengthMeasure();
  void setIfcPositiveLengthMeasure(IfcPositiveLengthMeasure val);

  bool isIfcVector();
  void setIfcVector(IfcVector* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcHatchLineDistanceSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcHatchLineDistanceSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcLayeredItem
  : public OdDAI::SelectWrapper
{
public:

  IfcLayeredItem(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcRepresentation();
  void setIfcRepresentation(IfcRepresentation* val);

  bool isIfcRepresentationItem();
  void setIfcRepresentationItem(IfcRepresentationItem* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcLayeredItemTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcLayeredItemTypeProvider& instance();


};

class IFC4X1_EXPORT IfcLibrarySelect
  : public OdDAI::SelectWrapper
{
public:

  IfcLibrarySelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcLibraryInformation();
  void setIfcLibraryInformation(IfcLibraryInformation* val);

  bool isIfcLibraryReference();
  void setIfcLibraryReference(IfcLibraryReference* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcLibrarySelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcLibrarySelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcLightDistributionDataSourceSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcLightDistributionDataSourceSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcExternalReference();
  void setIfcExternalReference(IfcExternalReference* val);

  bool isIfcLightIntensityDistribution();
  void setIfcLightIntensityDistribution(IfcLightIntensityDistribution* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcLightDistributionDataSourceSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcLightDistributionDataSourceSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcMaterialSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcMaterialSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcMaterialDefinition();
  void setIfcMaterialDefinition(IfcMaterialDefinition* val);

  bool isIfcMaterialList();
  void setIfcMaterialList(IfcMaterialList* val);

  bool isIfcMaterialUsageDefinition();
  void setIfcMaterialUsageDefinition(IfcMaterialUsageDefinition* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcMaterialSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcMaterialSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcMeasureValue
  : public OdDAI::SelectWrapper
{
public:

  IfcMeasureValue(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcAmountOfSubstanceMeasure();
  void setIfcAmountOfSubstanceMeasure(IfcAmountOfSubstanceMeasure val);

  bool isIfcAreaMeasure();
  void setIfcAreaMeasure(IfcAreaMeasure val);

  bool isIfcComplexNumber();
  void setIfcComplexNumber(OdArray<double > val);

  bool isIfcContextDependentMeasure();
  void setIfcContextDependentMeasure(IfcContextDependentMeasure val);

  bool isIfcCountMeasure();
  void setIfcCountMeasure(IfcCountMeasure val);

  bool isIfcDescriptiveMeasure();
  void setIfcDescriptiveMeasure(IfcDescriptiveMeasure val);

  bool isIfcElectricCurrentMeasure();
  void setIfcElectricCurrentMeasure(IfcElectricCurrentMeasure val);

  bool isIfcLengthMeasure();
  void setIfcLengthMeasure(IfcLengthMeasure val);

  bool isIfcLuminousIntensityMeasure();
  void setIfcLuminousIntensityMeasure(IfcLuminousIntensityMeasure val);

  bool isIfcMassMeasure();
  void setIfcMassMeasure(IfcMassMeasure val);

  bool isIfcNonNegativeLengthMeasure();
  void setIfcNonNegativeLengthMeasure(IfcNonNegativeLengthMeasure val);

  bool isIfcNormalisedRatioMeasure();
  void setIfcNormalisedRatioMeasure(IfcNormalisedRatioMeasure val);

  bool isIfcNumericMeasure();
  void setIfcNumericMeasure(IfcNumericMeasure val);

  bool isIfcParameterValue();
  void setIfcParameterValue(IfcParameterValue val);

  bool isIfcPlaneAngleMeasure();
  void setIfcPlaneAngleMeasure(IfcPlaneAngleMeasure val);

  bool isIfcPositiveLengthMeasure();
  void setIfcPositiveLengthMeasure(IfcPositiveLengthMeasure val);

  bool isIfcPositivePlaneAngleMeasure();
  void setIfcPositivePlaneAngleMeasure(IfcPositivePlaneAngleMeasure val);

  bool isIfcPositiveRatioMeasure();
  void setIfcPositiveRatioMeasure(IfcPositiveRatioMeasure val);

  bool isIfcRatioMeasure();
  void setIfcRatioMeasure(IfcRatioMeasure val);

  bool isIfcSolidAngleMeasure();
  void setIfcSolidAngleMeasure(IfcSolidAngleMeasure val);

  bool isIfcThermodynamicTemperatureMeasure();
  void setIfcThermodynamicTemperatureMeasure(IfcThermodynamicTemperatureMeasure val);

  bool isIfcTimeMeasure();
  void setIfcTimeMeasure(IfcTimeMeasure val);

  bool isIfcVolumeMeasure();
  void setIfcVolumeMeasure(IfcVolumeMeasure val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcMeasureValueTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcMeasureValueTypeProvider& instance();


};

class IFC4X1_EXPORT IfcMetricValueSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcMetricValueSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcAbsorbedDoseMeasure();
  void setIfcAbsorbedDoseMeasure(IfcAbsorbedDoseMeasure val);

  bool isIfcAccelerationMeasure();
  void setIfcAccelerationMeasure(IfcAccelerationMeasure val);

  bool isIfcAmountOfSubstanceMeasure();
  void setIfcAmountOfSubstanceMeasure(IfcAmountOfSubstanceMeasure val);

  bool isIfcAngularVelocityMeasure();
  void setIfcAngularVelocityMeasure(IfcAngularVelocityMeasure val);

  bool isIfcAppliedValue();
  void setIfcAppliedValue(IfcAppliedValue* val);

  bool isIfcAreaDensityMeasure();
  void setIfcAreaDensityMeasure(IfcAreaDensityMeasure val);

  bool isIfcAreaMeasure();
  void setIfcAreaMeasure(IfcAreaMeasure val);

  bool isIfcBinary();
  void setIfcBinary(IfcBinary val);

  bool isIfcBoolean();
  void setIfcBoolean(IfcBoolean val);

  bool isIfcComplexNumber();
  void setIfcComplexNumber(OdArray<double > val);

  bool isIfcCompoundPlaneAngleMeasure();
  void setIfcCompoundPlaneAngleMeasure(OdArray<int > val);

  bool isIfcContextDependentMeasure();
  void setIfcContextDependentMeasure(IfcContextDependentMeasure val);

  bool isIfcCountMeasure();
  void setIfcCountMeasure(IfcCountMeasure val);

  bool isIfcCurvatureMeasure();
  void setIfcCurvatureMeasure(IfcCurvatureMeasure val);

  bool isIfcDate();
  void setIfcDate(IfcDate val);

  bool isIfcDateTime();
  void setIfcDateTime(IfcDateTime val);

  bool isIfcDescriptiveMeasure();
  void setIfcDescriptiveMeasure(IfcDescriptiveMeasure val);

  bool isIfcDoseEquivalentMeasure();
  void setIfcDoseEquivalentMeasure(IfcDoseEquivalentMeasure val);

  bool isIfcDuration();
  void setIfcDuration(IfcDuration val);

  bool isIfcDynamicViscosityMeasure();
  void setIfcDynamicViscosityMeasure(IfcDynamicViscosityMeasure val);

  bool isIfcElectricCapacitanceMeasure();
  void setIfcElectricCapacitanceMeasure(IfcElectricCapacitanceMeasure val);

  bool isIfcElectricChargeMeasure();
  void setIfcElectricChargeMeasure(IfcElectricChargeMeasure val);

  bool isIfcElectricConductanceMeasure();
  void setIfcElectricConductanceMeasure(IfcElectricConductanceMeasure val);

  bool isIfcElectricCurrentMeasure();
  void setIfcElectricCurrentMeasure(IfcElectricCurrentMeasure val);

  bool isIfcElectricResistanceMeasure();
  void setIfcElectricResistanceMeasure(IfcElectricResistanceMeasure val);

  bool isIfcElectricVoltageMeasure();
  void setIfcElectricVoltageMeasure(IfcElectricVoltageMeasure val);

  bool isIfcEnergyMeasure();
  void setIfcEnergyMeasure(IfcEnergyMeasure val);

  bool isIfcForceMeasure();
  void setIfcForceMeasure(IfcForceMeasure val);

  bool isIfcFrequencyMeasure();
  void setIfcFrequencyMeasure(IfcFrequencyMeasure val);

  bool isIfcHeatFluxDensityMeasure();
  void setIfcHeatFluxDensityMeasure(IfcHeatFluxDensityMeasure val);

  bool isIfcHeatingValueMeasure();
  void setIfcHeatingValueMeasure(IfcHeatingValueMeasure val);

  bool isIfcIdentifier();
  void setIfcIdentifier(IfcIdentifier val);

  bool isIfcIlluminanceMeasure();
  void setIfcIlluminanceMeasure(IfcIlluminanceMeasure val);

  bool isIfcInductanceMeasure();
  void setIfcInductanceMeasure(IfcInductanceMeasure val);

  bool isIfcInteger();
  void setIfcInteger(IfcInteger val);

  bool isIfcIntegerCountRateMeasure();
  void setIfcIntegerCountRateMeasure(IfcIntegerCountRateMeasure val);

  bool isIfcIonConcentrationMeasure();
  void setIfcIonConcentrationMeasure(IfcIonConcentrationMeasure val);

  bool isIfcIsothermalMoistureCapacityMeasure();
  void setIfcIsothermalMoistureCapacityMeasure(IfcIsothermalMoistureCapacityMeasure val);

  bool isIfcKinematicViscosityMeasure();
  void setIfcKinematicViscosityMeasure(IfcKinematicViscosityMeasure val);

  bool isIfcLabel();
  void setIfcLabel(IfcLabel val);

  bool isIfcLengthMeasure();
  void setIfcLengthMeasure(IfcLengthMeasure val);

  bool isIfcLinearForceMeasure();
  void setIfcLinearForceMeasure(IfcLinearForceMeasure val);

  bool isIfcLinearMomentMeasure();
  void setIfcLinearMomentMeasure(IfcLinearMomentMeasure val);

  bool isIfcLinearStiffnessMeasure();
  void setIfcLinearStiffnessMeasure(IfcLinearStiffnessMeasure val);

  bool isIfcLinearVelocityMeasure();
  void setIfcLinearVelocityMeasure(IfcLinearVelocityMeasure val);

  bool isIfcLogical();
  void setIfcLogical(IfcLogical val);

  bool isIfcLuminousFluxMeasure();
  void setIfcLuminousFluxMeasure(IfcLuminousFluxMeasure val);

  bool isIfcLuminousIntensityDistributionMeasure();
  void setIfcLuminousIntensityDistributionMeasure(IfcLuminousIntensityDistributionMeasure val);

  bool isIfcLuminousIntensityMeasure();
  void setIfcLuminousIntensityMeasure(IfcLuminousIntensityMeasure val);

  bool isIfcMagneticFluxDensityMeasure();
  void setIfcMagneticFluxDensityMeasure(IfcMagneticFluxDensityMeasure val);

  bool isIfcMagneticFluxMeasure();
  void setIfcMagneticFluxMeasure(IfcMagneticFluxMeasure val);

  bool isIfcMassDensityMeasure();
  void setIfcMassDensityMeasure(IfcMassDensityMeasure val);

  bool isIfcMassFlowRateMeasure();
  void setIfcMassFlowRateMeasure(IfcMassFlowRateMeasure val);

  bool isIfcMassMeasure();
  void setIfcMassMeasure(IfcMassMeasure val);

  bool isIfcMassPerLengthMeasure();
  void setIfcMassPerLengthMeasure(IfcMassPerLengthMeasure val);

  bool isIfcMeasureWithUnit();
  void setIfcMeasureWithUnit(IfcMeasureWithUnit* val);

  bool isIfcModulusOfElasticityMeasure();
  void setIfcModulusOfElasticityMeasure(IfcModulusOfElasticityMeasure val);

  bool isIfcModulusOfLinearSubgradeReactionMeasure();
  void setIfcModulusOfLinearSubgradeReactionMeasure(IfcModulusOfLinearSubgradeReactionMeasure val);

  bool isIfcModulusOfRotationalSubgradeReactionMeasure();
  void setIfcModulusOfRotationalSubgradeReactionMeasure(IfcModulusOfRotationalSubgradeReactionMeasure val);

  bool isIfcModulusOfSubgradeReactionMeasure();
  void setIfcModulusOfSubgradeReactionMeasure(IfcModulusOfSubgradeReactionMeasure val);

  bool isIfcMoistureDiffusivityMeasure();
  void setIfcMoistureDiffusivityMeasure(IfcMoistureDiffusivityMeasure val);

  bool isIfcMolecularWeightMeasure();
  void setIfcMolecularWeightMeasure(IfcMolecularWeightMeasure val);

  bool isIfcMomentOfInertiaMeasure();
  void setIfcMomentOfInertiaMeasure(IfcMomentOfInertiaMeasure val);

  bool isIfcMonetaryMeasure();
  void setIfcMonetaryMeasure(IfcMonetaryMeasure val);

  bool isIfcNonNegativeLengthMeasure();
  void setIfcNonNegativeLengthMeasure(IfcNonNegativeLengthMeasure val);

  bool isIfcNormalisedRatioMeasure();
  void setIfcNormalisedRatioMeasure(IfcNormalisedRatioMeasure val);

  bool isIfcNumericMeasure();
  void setIfcNumericMeasure(IfcNumericMeasure val);

  bool isIfcPHMeasure();
  void setIfcPHMeasure(IfcPHMeasure val);

  bool isIfcParameterValue();
  void setIfcParameterValue(IfcParameterValue val);

  bool isIfcPlanarForceMeasure();
  void setIfcPlanarForceMeasure(IfcPlanarForceMeasure val);

  bool isIfcPlaneAngleMeasure();
  void setIfcPlaneAngleMeasure(IfcPlaneAngleMeasure val);

  bool isIfcPositiveInteger();
  void setIfcPositiveInteger(IfcPositiveInteger val);

  bool isIfcPositiveLengthMeasure();
  void setIfcPositiveLengthMeasure(IfcPositiveLengthMeasure val);

  bool isIfcPositivePlaneAngleMeasure();
  void setIfcPositivePlaneAngleMeasure(IfcPositivePlaneAngleMeasure val);

  bool isIfcPositiveRatioMeasure();
  void setIfcPositiveRatioMeasure(IfcPositiveRatioMeasure val);

  bool isIfcPowerMeasure();
  void setIfcPowerMeasure(IfcPowerMeasure val);

  bool isIfcPressureMeasure();
  void setIfcPressureMeasure(IfcPressureMeasure val);

  bool isIfcRadioActivityMeasure();
  void setIfcRadioActivityMeasure(IfcRadioActivityMeasure val);

  bool isIfcRatioMeasure();
  void setIfcRatioMeasure(IfcRatioMeasure val);

  bool isIfcReal();
  void setIfcReal(IfcReal val);

  bool isIfcReference();
  void setIfcReference(IfcReference* val);

  bool isIfcRotationalFrequencyMeasure();
  void setIfcRotationalFrequencyMeasure(IfcRotationalFrequencyMeasure val);

  bool isIfcRotationalMassMeasure();
  void setIfcRotationalMassMeasure(IfcRotationalMassMeasure val);

  bool isIfcRotationalStiffnessMeasure();
  void setIfcRotationalStiffnessMeasure(IfcRotationalStiffnessMeasure val);

  bool isIfcSectionModulusMeasure();
  void setIfcSectionModulusMeasure(IfcSectionModulusMeasure val);

  bool isIfcSectionalAreaIntegralMeasure();
  void setIfcSectionalAreaIntegralMeasure(IfcSectionalAreaIntegralMeasure val);

  bool isIfcShearModulusMeasure();
  void setIfcShearModulusMeasure(IfcShearModulusMeasure val);

  bool isIfcSolidAngleMeasure();
  void setIfcSolidAngleMeasure(IfcSolidAngleMeasure val);

  bool isIfcSoundPowerLevelMeasure();
  void setIfcSoundPowerLevelMeasure(IfcSoundPowerLevelMeasure val);

  bool isIfcSoundPowerMeasure();
  void setIfcSoundPowerMeasure(IfcSoundPowerMeasure val);

  bool isIfcSoundPressureLevelMeasure();
  void setIfcSoundPressureLevelMeasure(IfcSoundPressureLevelMeasure val);

  bool isIfcSoundPressureMeasure();
  void setIfcSoundPressureMeasure(IfcSoundPressureMeasure val);

  bool isIfcSpecificHeatCapacityMeasure();
  void setIfcSpecificHeatCapacityMeasure(IfcSpecificHeatCapacityMeasure val);

  bool isIfcTable();
  void setIfcTable(IfcTable* val);

  bool isIfcTemperatureGradientMeasure();
  void setIfcTemperatureGradientMeasure(IfcTemperatureGradientMeasure val);

  bool isIfcTemperatureRateOfChangeMeasure();
  void setIfcTemperatureRateOfChangeMeasure(IfcTemperatureRateOfChangeMeasure val);

  bool isIfcText();
  void setIfcText(IfcText val);

  bool isIfcThermalAdmittanceMeasure();
  void setIfcThermalAdmittanceMeasure(IfcThermalAdmittanceMeasure val);

  bool isIfcThermalConductivityMeasure();
  void setIfcThermalConductivityMeasure(IfcThermalConductivityMeasure val);

  bool isIfcThermalExpansionCoefficientMeasure();
  void setIfcThermalExpansionCoefficientMeasure(IfcThermalExpansionCoefficientMeasure val);

  bool isIfcThermalResistanceMeasure();
  void setIfcThermalResistanceMeasure(IfcThermalResistanceMeasure val);

  bool isIfcThermalTransmittanceMeasure();
  void setIfcThermalTransmittanceMeasure(IfcThermalTransmittanceMeasure val);

  bool isIfcThermodynamicTemperatureMeasure();
  void setIfcThermodynamicTemperatureMeasure(IfcThermodynamicTemperatureMeasure val);

  bool isIfcTime();
  void setIfcTime(IfcTime val);

  bool isIfcTimeMeasure();
  void setIfcTimeMeasure(IfcTimeMeasure val);

  bool isIfcTimeSeries();
  void setIfcTimeSeries(IfcTimeSeries* val);

  bool isIfcTimeStamp();
  void setIfcTimeStamp(IfcTimeStamp val);

  bool isIfcTorqueMeasure();
  void setIfcTorqueMeasure(IfcTorqueMeasure val);

  bool isIfcVaporPermeabilityMeasure();
  void setIfcVaporPermeabilityMeasure(IfcVaporPermeabilityMeasure val);

  bool isIfcVolumeMeasure();
  void setIfcVolumeMeasure(IfcVolumeMeasure val);

  bool isIfcVolumetricFlowRateMeasure();
  void setIfcVolumetricFlowRateMeasure(IfcVolumetricFlowRateMeasure val);

  bool isIfcWarpingConstantMeasure();
  void setIfcWarpingConstantMeasure(IfcWarpingConstantMeasure val);

  bool isIfcWarpingMomentMeasure();
  void setIfcWarpingMomentMeasure(IfcWarpingMomentMeasure val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcMetricValueSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcMetricValueSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcModulusOfRotationalSubgradeReactionSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcModulusOfRotationalSubgradeReactionSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcBoolean();
  void setIfcBoolean(IfcBoolean val);

  bool isIfcModulusOfRotationalSubgradeReactionMeasure();
  void setIfcModulusOfRotationalSubgradeReactionMeasure(IfcModulusOfRotationalSubgradeReactionMeasure val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcModulusOfRotationalSubgradeReactionSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcModulusOfRotationalSubgradeReactionSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcModulusOfSubgradeReactionSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcModulusOfSubgradeReactionSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcBoolean();
  void setIfcBoolean(IfcBoolean val);

  bool isIfcModulusOfSubgradeReactionMeasure();
  void setIfcModulusOfSubgradeReactionMeasure(IfcModulusOfSubgradeReactionMeasure val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcModulusOfSubgradeReactionSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcModulusOfSubgradeReactionSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcModulusOfTranslationalSubgradeReactionSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcModulusOfTranslationalSubgradeReactionSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcBoolean();
  void setIfcBoolean(IfcBoolean val);

  bool isIfcModulusOfLinearSubgradeReactionMeasure();
  void setIfcModulusOfLinearSubgradeReactionMeasure(IfcModulusOfLinearSubgradeReactionMeasure val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcModulusOfTranslationalSubgradeReactionSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcModulusOfTranslationalSubgradeReactionSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcObjectReferenceSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcObjectReferenceSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcAddress();
  void setIfcAddress(IfcAddress* val);

  bool isIfcAppliedValue();
  void setIfcAppliedValue(IfcAppliedValue* val);

  bool isIfcExternalReference();
  void setIfcExternalReference(IfcExternalReference* val);

  bool isIfcMaterialDefinition();
  void setIfcMaterialDefinition(IfcMaterialDefinition* val);

  bool isIfcOrganization();
  void setIfcOrganization(IfcOrganization* val);

  bool isIfcPerson();
  void setIfcPerson(IfcPerson* val);

  bool isIfcPersonAndOrganization();
  void setIfcPersonAndOrganization(IfcPersonAndOrganization* val);

  bool isIfcTable();
  void setIfcTable(IfcTable* val);

  bool isIfcTimeSeries();
  void setIfcTimeSeries(IfcTimeSeries* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcObjectReferenceSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcObjectReferenceSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcPointOrVertexPoint
  : public OdDAI::SelectWrapper
{
public:

  IfcPointOrVertexPoint(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcPoint();
  void setIfcPoint(IfcPoint* val);

  bool isIfcVertexPoint();
  void setIfcVertexPoint(IfcVertexPoint* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcPointOrVertexPointTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcPointOrVertexPointTypeProvider& instance();


};

class IFC4X1_EXPORT IfcPresentationStyleSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcPresentationStyleSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcCurveStyle();
  void setIfcCurveStyle(IfcCurveStyle* val);

  bool isIfcFillAreaStyle();
  void setIfcFillAreaStyle(IfcFillAreaStyle* val);

  bool isIfcNullStyle();
  void setIfcNullStyle(IfcNullStyle val);

  bool isIfcSurfaceStyle();
  void setIfcSurfaceStyle(IfcSurfaceStyle* val);

  bool isIfcTextStyle();
  void setIfcTextStyle(IfcTextStyle* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcPresentationStyleSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcPresentationStyleSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcProcessSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcProcessSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcProcess();
  void setIfcProcess(IfcProcess* val);

  bool isIfcTypeProcess();
  void setIfcTypeProcess(IfcTypeProcess* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcProcessSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcProcessSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcProductRepresentationSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcProductRepresentationSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcProductDefinitionShape();
  void setIfcProductDefinitionShape(IfcProductDefinitionShape* val);

  bool isIfcRepresentationMap();
  void setIfcRepresentationMap(IfcRepresentationMap* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcProductRepresentationSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcProductRepresentationSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcProductSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcProductSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcProduct();
  void setIfcProduct(IfcProduct* val);

  bool isIfcTypeProduct();
  void setIfcTypeProduct(IfcTypeProduct* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcProductSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcProductSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcPropertySetDefinitionSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcPropertySetDefinitionSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcPropertySetDefinition();
  void setIfcPropertySetDefinition(IfcPropertySetDefinition* val);

  bool isIfcPropertySetDefinitionSet();
  void setIfcPropertySetDefinitionSet(OdArray<OdDAIObjectId > val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcPropertySetDefinitionSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcPropertySetDefinitionSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcResourceObjectSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcResourceObjectSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcActorRole();
  void setIfcActorRole(IfcActorRole* val);

  bool isIfcAppliedValue();
  void setIfcAppliedValue(IfcAppliedValue* val);

  bool isIfcApproval();
  void setIfcApproval(IfcApproval* val);

  bool isIfcConstraint();
  void setIfcConstraint(IfcConstraint* val);

  bool isIfcContextDependentUnit();
  void setIfcContextDependentUnit(IfcContextDependentUnit* val);

  bool isIfcConversionBasedUnit();
  void setIfcConversionBasedUnit(IfcConversionBasedUnit* val);

  bool isIfcExternalInformation();
  void setIfcExternalInformation(IfcExternalInformation* val);

  bool isIfcExternalReference();
  void setIfcExternalReference(IfcExternalReference* val);

  bool isIfcMaterialDefinition();
  void setIfcMaterialDefinition(IfcMaterialDefinition* val);

  bool isIfcOrganization();
  void setIfcOrganization(IfcOrganization* val);

  bool isIfcPerson();
  void setIfcPerson(IfcPerson* val);

  bool isIfcPersonAndOrganization();
  void setIfcPersonAndOrganization(IfcPersonAndOrganization* val);

  bool isIfcPhysicalQuantity();
  void setIfcPhysicalQuantity(IfcPhysicalQuantity* val);

  bool isIfcProfileDef();
  void setIfcProfileDef(IfcProfileDef* val);

  bool isIfcPropertyAbstraction();
  void setIfcPropertyAbstraction(IfcPropertyAbstraction* val);

  bool isIfcShapeAspect();
  void setIfcShapeAspect(IfcShapeAspect* val);

  bool isIfcTimeSeries();
  void setIfcTimeSeries(IfcTimeSeries* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcResourceObjectSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcResourceObjectSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcResourceSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcResourceSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcResource();
  void setIfcResource(IfcResource* val);

  bool isIfcTypeResource();
  void setIfcTypeResource(IfcTypeResource* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcResourceSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcResourceSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcRotationalStiffnessSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcRotationalStiffnessSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcBoolean();
  void setIfcBoolean(IfcBoolean val);

  bool isIfcRotationalStiffnessMeasure();
  void setIfcRotationalStiffnessMeasure(IfcRotationalStiffnessMeasure val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcRotationalStiffnessSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcRotationalStiffnessSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcSegmentIndexSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcSegmentIndexSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcArcIndex();
  void setIfcArcIndex(OdArray<int > val);

  bool isIfcLineIndex();
  void setIfcLineIndex(OdArray<int > val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcSegmentIndexSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcSegmentIndexSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcShell
  : public OdDAI::SelectWrapper
{
public:

  IfcShell(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcClosedShell();
  void setIfcClosedShell(IfcClosedShell* val);

  bool isIfcOpenShell();
  void setIfcOpenShell(IfcOpenShell* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcShellTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcShellTypeProvider& instance();


};

class IFC4X1_EXPORT IfcSimpleValue
  : public OdDAI::SelectWrapper
{
public:

  IfcSimpleValue(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcBinary();
  void setIfcBinary(IfcBinary val);

  bool isIfcBoolean();
  void setIfcBoolean(IfcBoolean val);

  bool isIfcDate();
  void setIfcDate(IfcDate val);

  bool isIfcDateTime();
  void setIfcDateTime(IfcDateTime val);

  bool isIfcDuration();
  void setIfcDuration(IfcDuration val);

  bool isIfcIdentifier();
  void setIfcIdentifier(IfcIdentifier val);

  bool isIfcInteger();
  void setIfcInteger(IfcInteger val);

  bool isIfcLabel();
  void setIfcLabel(IfcLabel val);

  bool isIfcLogical();
  void setIfcLogical(IfcLogical val);

  bool isIfcPositiveInteger();
  void setIfcPositiveInteger(IfcPositiveInteger val);

  bool isIfcReal();
  void setIfcReal(IfcReal val);

  bool isIfcText();
  void setIfcText(IfcText val);

  bool isIfcTime();
  void setIfcTime(IfcTime val);

  bool isIfcTimeStamp();
  void setIfcTimeStamp(IfcTimeStamp val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcSimpleValueTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcSimpleValueTypeProvider& instance();


};

class IFC4X1_EXPORT IfcSizeSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcSizeSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcDescriptiveMeasure();
  void setIfcDescriptiveMeasure(IfcDescriptiveMeasure val);

  bool isIfcLengthMeasure();
  void setIfcLengthMeasure(IfcLengthMeasure val);

  bool isIfcNormalisedRatioMeasure();
  void setIfcNormalisedRatioMeasure(IfcNormalisedRatioMeasure val);

  bool isIfcPositiveLengthMeasure();
  void setIfcPositiveLengthMeasure(IfcPositiveLengthMeasure val);

  bool isIfcPositiveRatioMeasure();
  void setIfcPositiveRatioMeasure(IfcPositiveRatioMeasure val);

  bool isIfcRatioMeasure();
  void setIfcRatioMeasure(IfcRatioMeasure val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcSizeSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcSizeSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcSolidOrShell
  : public OdDAI::SelectWrapper
{
public:

  IfcSolidOrShell(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcClosedShell();
  void setIfcClosedShell(IfcClosedShell* val);

  bool isIfcSolidModel();
  void setIfcSolidModel(IfcSolidModel* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcSolidOrShellTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcSolidOrShellTypeProvider& instance();


};

class IFC4X1_EXPORT IfcSpaceBoundarySelect
  : public OdDAI::SelectWrapper
{
public:

  IfcSpaceBoundarySelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcExternalSpatialElement();
  void setIfcExternalSpatialElement(IfcExternalSpatialElement* val);

  bool isIfcSpace();
  void setIfcSpace(IfcSpace* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcSpaceBoundarySelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcSpaceBoundarySelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcSpecularHighlightSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcSpecularHighlightSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcSpecularExponent();
  void setIfcSpecularExponent(IfcSpecularExponent val);

  bool isIfcSpecularRoughness();
  void setIfcSpecularRoughness(IfcSpecularRoughness val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcSpecularHighlightSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcSpecularHighlightSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcStructuralActivityAssignmentSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcStructuralActivityAssignmentSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcElement();
  void setIfcElement(IfcElement* val);

  bool isIfcStructuralItem();
  void setIfcStructuralItem(IfcStructuralItem* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcStructuralActivityAssignmentSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcStructuralActivityAssignmentSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcStyleAssignmentSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcStyleAssignmentSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcPresentationStyle();
  void setIfcPresentationStyle(IfcPresentationStyle* val);

  bool isIfcPresentationStyleAssignment();
  void setIfcPresentationStyleAssignment(IfcPresentationStyleAssignment* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcStyleAssignmentSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcStyleAssignmentSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcSurfaceOrFaceSurface
  : public OdDAI::SelectWrapper
{
public:

  IfcSurfaceOrFaceSurface(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcFaceBasedSurfaceModel();
  void setIfcFaceBasedSurfaceModel(IfcFaceBasedSurfaceModel* val);

  bool isIfcFaceSurface();
  void setIfcFaceSurface(IfcFaceSurface* val);

  bool isIfcSurface();
  void setIfcSurface(IfcSurface* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcSurfaceOrFaceSurfaceTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcSurfaceOrFaceSurfaceTypeProvider& instance();


};

class IFC4X1_EXPORT IfcSurfaceStyleElementSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcSurfaceStyleElementSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcExternallyDefinedSurfaceStyle();
  void setIfcExternallyDefinedSurfaceStyle(IfcExternallyDefinedSurfaceStyle* val);

  bool isIfcSurfaceStyleLighting();
  void setIfcSurfaceStyleLighting(IfcSurfaceStyleLighting* val);

  bool isIfcSurfaceStyleRefraction();
  void setIfcSurfaceStyleRefraction(IfcSurfaceStyleRefraction* val);

  bool isIfcSurfaceStyleShading();
  void setIfcSurfaceStyleShading(IfcSurfaceStyleShading* val);

  bool isIfcSurfaceStyleWithTextures();
  void setIfcSurfaceStyleWithTextures(IfcSurfaceStyleWithTextures* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcSurfaceStyleElementSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcSurfaceStyleElementSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcTextFontSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcTextFontSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcExternallyDefinedTextFont();
  void setIfcExternallyDefinedTextFont(IfcExternallyDefinedTextFont* val);

  bool isIfcPreDefinedTextFont();
  void setIfcPreDefinedTextFont(IfcPreDefinedTextFont* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcTextFontSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcTextFontSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcTimeOrRatioSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcTimeOrRatioSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcDuration();
  void setIfcDuration(IfcDuration val);

  bool isIfcRatioMeasure();
  void setIfcRatioMeasure(IfcRatioMeasure val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcTimeOrRatioSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcTimeOrRatioSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcTranslationalStiffnessSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcTranslationalStiffnessSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcBoolean();
  void setIfcBoolean(IfcBoolean val);

  bool isIfcLinearStiffnessMeasure();
  void setIfcLinearStiffnessMeasure(IfcLinearStiffnessMeasure val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcTranslationalStiffnessSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcTranslationalStiffnessSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcTrimmingSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcTrimmingSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcCartesianPoint();
  void setIfcCartesianPoint(IfcCartesianPoint* val);

  bool isIfcParameterValue();
  void setIfcParameterValue(IfcParameterValue val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcTrimmingSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcTrimmingSelectTypeProvider& instance();


};

class IFC4X1_EXPORT IfcUnit
  : public OdDAI::SelectWrapper
{
public:

  IfcUnit(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcDerivedUnit();
  void setIfcDerivedUnit(IfcDerivedUnit* val);

  bool isIfcMonetaryUnit();
  void setIfcMonetaryUnit(IfcMonetaryUnit* val);

  bool isIfcNamedUnit();
  void setIfcNamedUnit(IfcNamedUnit* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcUnitTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcUnitTypeProvider& instance();


};

class IFC4X1_EXPORT IfcValue
  : public OdDAI::SelectWrapper
{
public:

  IfcValue(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcAbsorbedDoseMeasure();
  void setIfcAbsorbedDoseMeasure(IfcAbsorbedDoseMeasure val);

  bool isIfcAccelerationMeasure();
  void setIfcAccelerationMeasure(IfcAccelerationMeasure val);

  bool isIfcAmountOfSubstanceMeasure();
  void setIfcAmountOfSubstanceMeasure(IfcAmountOfSubstanceMeasure val);

  bool isIfcAngularVelocityMeasure();
  void setIfcAngularVelocityMeasure(IfcAngularVelocityMeasure val);

  bool isIfcAreaDensityMeasure();
  void setIfcAreaDensityMeasure(IfcAreaDensityMeasure val);

  bool isIfcAreaMeasure();
  void setIfcAreaMeasure(IfcAreaMeasure val);

  bool isIfcBinary();
  void setIfcBinary(IfcBinary val);

  bool isIfcBoolean();
  void setIfcBoolean(IfcBoolean val);

  bool isIfcComplexNumber();
  void setIfcComplexNumber(OdArray<double > val);

  bool isIfcCompoundPlaneAngleMeasure();
  void setIfcCompoundPlaneAngleMeasure(OdArray<int > val);

  bool isIfcContextDependentMeasure();
  void setIfcContextDependentMeasure(IfcContextDependentMeasure val);

  bool isIfcCountMeasure();
  void setIfcCountMeasure(IfcCountMeasure val);

  bool isIfcCurvatureMeasure();
  void setIfcCurvatureMeasure(IfcCurvatureMeasure val);

  bool isIfcDate();
  void setIfcDate(IfcDate val);

  bool isIfcDateTime();
  void setIfcDateTime(IfcDateTime val);

  bool isIfcDescriptiveMeasure();
  void setIfcDescriptiveMeasure(IfcDescriptiveMeasure val);

  bool isIfcDoseEquivalentMeasure();
  void setIfcDoseEquivalentMeasure(IfcDoseEquivalentMeasure val);

  bool isIfcDuration();
  void setIfcDuration(IfcDuration val);

  bool isIfcDynamicViscosityMeasure();
  void setIfcDynamicViscosityMeasure(IfcDynamicViscosityMeasure val);

  bool isIfcElectricCapacitanceMeasure();
  void setIfcElectricCapacitanceMeasure(IfcElectricCapacitanceMeasure val);

  bool isIfcElectricChargeMeasure();
  void setIfcElectricChargeMeasure(IfcElectricChargeMeasure val);

  bool isIfcElectricConductanceMeasure();
  void setIfcElectricConductanceMeasure(IfcElectricConductanceMeasure val);

  bool isIfcElectricCurrentMeasure();
  void setIfcElectricCurrentMeasure(IfcElectricCurrentMeasure val);

  bool isIfcElectricResistanceMeasure();
  void setIfcElectricResistanceMeasure(IfcElectricResistanceMeasure val);

  bool isIfcElectricVoltageMeasure();
  void setIfcElectricVoltageMeasure(IfcElectricVoltageMeasure val);

  bool isIfcEnergyMeasure();
  void setIfcEnergyMeasure(IfcEnergyMeasure val);

  bool isIfcForceMeasure();
  void setIfcForceMeasure(IfcForceMeasure val);

  bool isIfcFrequencyMeasure();
  void setIfcFrequencyMeasure(IfcFrequencyMeasure val);

  bool isIfcHeatFluxDensityMeasure();
  void setIfcHeatFluxDensityMeasure(IfcHeatFluxDensityMeasure val);

  bool isIfcHeatingValueMeasure();
  void setIfcHeatingValueMeasure(IfcHeatingValueMeasure val);

  bool isIfcIdentifier();
  void setIfcIdentifier(IfcIdentifier val);

  bool isIfcIlluminanceMeasure();
  void setIfcIlluminanceMeasure(IfcIlluminanceMeasure val);

  bool isIfcInductanceMeasure();
  void setIfcInductanceMeasure(IfcInductanceMeasure val);

  bool isIfcInteger();
  void setIfcInteger(IfcInteger val);

  bool isIfcIntegerCountRateMeasure();
  void setIfcIntegerCountRateMeasure(IfcIntegerCountRateMeasure val);

  bool isIfcIonConcentrationMeasure();
  void setIfcIonConcentrationMeasure(IfcIonConcentrationMeasure val);

  bool isIfcIsothermalMoistureCapacityMeasure();
  void setIfcIsothermalMoistureCapacityMeasure(IfcIsothermalMoistureCapacityMeasure val);

  bool isIfcKinematicViscosityMeasure();
  void setIfcKinematicViscosityMeasure(IfcKinematicViscosityMeasure val);

  bool isIfcLabel();
  void setIfcLabel(IfcLabel val);

  bool isIfcLengthMeasure();
  void setIfcLengthMeasure(IfcLengthMeasure val);

  bool isIfcLinearForceMeasure();
  void setIfcLinearForceMeasure(IfcLinearForceMeasure val);

  bool isIfcLinearMomentMeasure();
  void setIfcLinearMomentMeasure(IfcLinearMomentMeasure val);

  bool isIfcLinearStiffnessMeasure();
  void setIfcLinearStiffnessMeasure(IfcLinearStiffnessMeasure val);

  bool isIfcLinearVelocityMeasure();
  void setIfcLinearVelocityMeasure(IfcLinearVelocityMeasure val);

  bool isIfcLogical();
  void setIfcLogical(IfcLogical val);

  bool isIfcLuminousFluxMeasure();
  void setIfcLuminousFluxMeasure(IfcLuminousFluxMeasure val);

  bool isIfcLuminousIntensityDistributionMeasure();
  void setIfcLuminousIntensityDistributionMeasure(IfcLuminousIntensityDistributionMeasure val);

  bool isIfcLuminousIntensityMeasure();
  void setIfcLuminousIntensityMeasure(IfcLuminousIntensityMeasure val);

  bool isIfcMagneticFluxDensityMeasure();
  void setIfcMagneticFluxDensityMeasure(IfcMagneticFluxDensityMeasure val);

  bool isIfcMagneticFluxMeasure();
  void setIfcMagneticFluxMeasure(IfcMagneticFluxMeasure val);

  bool isIfcMassDensityMeasure();
  void setIfcMassDensityMeasure(IfcMassDensityMeasure val);

  bool isIfcMassFlowRateMeasure();
  void setIfcMassFlowRateMeasure(IfcMassFlowRateMeasure val);

  bool isIfcMassMeasure();
  void setIfcMassMeasure(IfcMassMeasure val);

  bool isIfcMassPerLengthMeasure();
  void setIfcMassPerLengthMeasure(IfcMassPerLengthMeasure val);

  bool isIfcModulusOfElasticityMeasure();
  void setIfcModulusOfElasticityMeasure(IfcModulusOfElasticityMeasure val);

  bool isIfcModulusOfLinearSubgradeReactionMeasure();
  void setIfcModulusOfLinearSubgradeReactionMeasure(IfcModulusOfLinearSubgradeReactionMeasure val);

  bool isIfcModulusOfRotationalSubgradeReactionMeasure();
  void setIfcModulusOfRotationalSubgradeReactionMeasure(IfcModulusOfRotationalSubgradeReactionMeasure val);

  bool isIfcModulusOfSubgradeReactionMeasure();
  void setIfcModulusOfSubgradeReactionMeasure(IfcModulusOfSubgradeReactionMeasure val);

  bool isIfcMoistureDiffusivityMeasure();
  void setIfcMoistureDiffusivityMeasure(IfcMoistureDiffusivityMeasure val);

  bool isIfcMolecularWeightMeasure();
  void setIfcMolecularWeightMeasure(IfcMolecularWeightMeasure val);

  bool isIfcMomentOfInertiaMeasure();
  void setIfcMomentOfInertiaMeasure(IfcMomentOfInertiaMeasure val);

  bool isIfcMonetaryMeasure();
  void setIfcMonetaryMeasure(IfcMonetaryMeasure val);

  bool isIfcNonNegativeLengthMeasure();
  void setIfcNonNegativeLengthMeasure(IfcNonNegativeLengthMeasure val);

  bool isIfcNormalisedRatioMeasure();
  void setIfcNormalisedRatioMeasure(IfcNormalisedRatioMeasure val);

  bool isIfcNumericMeasure();
  void setIfcNumericMeasure(IfcNumericMeasure val);

  bool isIfcPHMeasure();
  void setIfcPHMeasure(IfcPHMeasure val);

  bool isIfcParameterValue();
  void setIfcParameterValue(IfcParameterValue val);

  bool isIfcPlanarForceMeasure();
  void setIfcPlanarForceMeasure(IfcPlanarForceMeasure val);

  bool isIfcPlaneAngleMeasure();
  void setIfcPlaneAngleMeasure(IfcPlaneAngleMeasure val);

  bool isIfcPositiveInteger();
  void setIfcPositiveInteger(IfcPositiveInteger val);

  bool isIfcPositiveLengthMeasure();
  void setIfcPositiveLengthMeasure(IfcPositiveLengthMeasure val);

  bool isIfcPositivePlaneAngleMeasure();
  void setIfcPositivePlaneAngleMeasure(IfcPositivePlaneAngleMeasure val);

  bool isIfcPositiveRatioMeasure();
  void setIfcPositiveRatioMeasure(IfcPositiveRatioMeasure val);

  bool isIfcPowerMeasure();
  void setIfcPowerMeasure(IfcPowerMeasure val);

  bool isIfcPressureMeasure();
  void setIfcPressureMeasure(IfcPressureMeasure val);

  bool isIfcRadioActivityMeasure();
  void setIfcRadioActivityMeasure(IfcRadioActivityMeasure val);

  bool isIfcRatioMeasure();
  void setIfcRatioMeasure(IfcRatioMeasure val);

  bool isIfcReal();
  void setIfcReal(IfcReal val);

  bool isIfcRotationalFrequencyMeasure();
  void setIfcRotationalFrequencyMeasure(IfcRotationalFrequencyMeasure val);

  bool isIfcRotationalMassMeasure();
  void setIfcRotationalMassMeasure(IfcRotationalMassMeasure val);

  bool isIfcRotationalStiffnessMeasure();
  void setIfcRotationalStiffnessMeasure(IfcRotationalStiffnessMeasure val);

  bool isIfcSectionModulusMeasure();
  void setIfcSectionModulusMeasure(IfcSectionModulusMeasure val);

  bool isIfcSectionalAreaIntegralMeasure();
  void setIfcSectionalAreaIntegralMeasure(IfcSectionalAreaIntegralMeasure val);

  bool isIfcShearModulusMeasure();
  void setIfcShearModulusMeasure(IfcShearModulusMeasure val);

  bool isIfcSolidAngleMeasure();
  void setIfcSolidAngleMeasure(IfcSolidAngleMeasure val);

  bool isIfcSoundPowerLevelMeasure();
  void setIfcSoundPowerLevelMeasure(IfcSoundPowerLevelMeasure val);

  bool isIfcSoundPowerMeasure();
  void setIfcSoundPowerMeasure(IfcSoundPowerMeasure val);

  bool isIfcSoundPressureLevelMeasure();
  void setIfcSoundPressureLevelMeasure(IfcSoundPressureLevelMeasure val);

  bool isIfcSoundPressureMeasure();
  void setIfcSoundPressureMeasure(IfcSoundPressureMeasure val);

  bool isIfcSpecificHeatCapacityMeasure();
  void setIfcSpecificHeatCapacityMeasure(IfcSpecificHeatCapacityMeasure val);

  bool isIfcTemperatureGradientMeasure();
  void setIfcTemperatureGradientMeasure(IfcTemperatureGradientMeasure val);

  bool isIfcTemperatureRateOfChangeMeasure();
  void setIfcTemperatureRateOfChangeMeasure(IfcTemperatureRateOfChangeMeasure val);

  bool isIfcText();
  void setIfcText(IfcText val);

  bool isIfcThermalAdmittanceMeasure();
  void setIfcThermalAdmittanceMeasure(IfcThermalAdmittanceMeasure val);

  bool isIfcThermalConductivityMeasure();
  void setIfcThermalConductivityMeasure(IfcThermalConductivityMeasure val);

  bool isIfcThermalExpansionCoefficientMeasure();
  void setIfcThermalExpansionCoefficientMeasure(IfcThermalExpansionCoefficientMeasure val);

  bool isIfcThermalResistanceMeasure();
  void setIfcThermalResistanceMeasure(IfcThermalResistanceMeasure val);

  bool isIfcThermalTransmittanceMeasure();
  void setIfcThermalTransmittanceMeasure(IfcThermalTransmittanceMeasure val);

  bool isIfcThermodynamicTemperatureMeasure();
  void setIfcThermodynamicTemperatureMeasure(IfcThermodynamicTemperatureMeasure val);

  bool isIfcTime();
  void setIfcTime(IfcTime val);

  bool isIfcTimeMeasure();
  void setIfcTimeMeasure(IfcTimeMeasure val);

  bool isIfcTimeStamp();
  void setIfcTimeStamp(IfcTimeStamp val);

  bool isIfcTorqueMeasure();
  void setIfcTorqueMeasure(IfcTorqueMeasure val);

  bool isIfcVaporPermeabilityMeasure();
  void setIfcVaporPermeabilityMeasure(IfcVaporPermeabilityMeasure val);

  bool isIfcVolumeMeasure();
  void setIfcVolumeMeasure(IfcVolumeMeasure val);

  bool isIfcVolumetricFlowRateMeasure();
  void setIfcVolumetricFlowRateMeasure(IfcVolumetricFlowRateMeasure val);

  bool isIfcWarpingConstantMeasure();
  void setIfcWarpingConstantMeasure(IfcWarpingConstantMeasure val);

  bool isIfcWarpingMomentMeasure();
  void setIfcWarpingMomentMeasure(IfcWarpingMomentMeasure val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcValueTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcValueTypeProvider& instance();


};

class IFC4X1_EXPORT IfcVectorOrDirection
  : public OdDAI::SelectWrapper
{
public:

  IfcVectorOrDirection(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcDirection();
  void setIfcDirection(IfcDirection* val);

  bool isIfcVector();
  void setIfcVector(IfcVector* val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcVectorOrDirectionTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcVectorOrDirectionTypeProvider& instance();


};

class IFC4X1_EXPORT IfcWarpingStiffnessSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcWarpingStiffnessSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcBoolean();
  void setIfcBoolean(IfcBoolean val);

  bool isIfcWarpingMomentMeasure();
  void setIfcWarpingMomentMeasure(IfcWarpingMomentMeasure val);

  static OdDAI::Select createEmptySelect();

};

class IFC4X1_EXPORT IfcWarpingStiffnessSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcWarpingStiffnessSelectTypeProvider& instance();


};


} // namespace

#endif // _IFC4X1_SELECT_TYPES_H

