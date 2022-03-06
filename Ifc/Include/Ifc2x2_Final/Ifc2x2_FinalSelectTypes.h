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

#ifndef _IFC2X2_FINAL_SELECT_TYPES_H
#define _IFC2X2_FINAL_SELECT_TYPES_H

#include "daiNamedType.h"
#include "daiSelectWrapper.h"
#include "daiValueTypes.h"
#include "Ifc2x2_FinalCollectionTypes.h"
#include "Ifc2x2_FinalSimpleTypes.h"
#include "Ifc2x2_FinalEnum.h"
#include "Ifc2x2_FinalBuildOption.h"

namespace OdIfc2x2_final {

class IfcOrganization;
class IfcPerson;
class IfcPersonAndOrganization;
class IfcMeasureWithUnit;
class IfcAxis2Placement2D;
class IfcAxis2Placement3D;
class IfcSolidModel;
class IfcHalfSpaceSolid;
class IfcBooleanResult;
class IfcColourSpecification;
class IfcPreDefinedColour;
class IfcClassificationNotation;
class IfcClassificationReference;
class IfcColourRgb;
class IfcPreDefinedCurveFont;
class IfcCurveStyleFont;
class IfcCurveStyleFontAndScaling;
class IfcCalendarDate;
class IfcLocalTime;
class IfcDateAndTime;
class IfcPreDefinedSymbol;
class IfcExternallyDefinedSymbol;
class IfcDocumentReference;
class IfcDocumentInformation;
class IfcAnnotationCurveOccurrence;
class IfcAnnotationTextOccurrence;
class IfcAnnotationSymbolOccurrence;
class IfcFillAreaStyleTileSymbolWithStyle;
class IfcFillAreaStyleHatching;
class IfcFillAreaStyleTiles;
class IfcExternallyDefinedHatchStyle;
class IfcPreDefinedTextFont;
class IfcExternallyDefinedTextFont;
class IfcPoint;
class IfcCurve;
class IfcSurface;
class IfcRepresentationItem;
class IfcRepresentation;
class IfcLibraryReference;
class IfcLibraryInformation;
class IfcExternalReference;
class IfcLightIntensityDistribution;
class IfcMaterial;
class IfcMaterialList;
class IfcMaterialLayerSetUsage;
class IfcMaterialLayerSet;
class IfcMaterialLayer;
class IfcTable;
class IfcTimeSeries;
class IfcCostValue;
class IfcAddress;
class IfcAppliedValue;
class IfcCurveStyle;
class IfcSymbolStyle;
class IfcFillAreaStyle;
class IfcTextStyle;
class IfcSurfaceStyle;
class IfcClosedShell;
class IfcOpenShell;
class IfcStructuralItem;
class IfcBuildingElement;
class IfcSurfaceStyleShading;
class IfcSurfaceStyleLighting;
class IfcSurfaceStyleWithTextures;
class IfcExternallyDefinedSufaceStyle;
class IfcSurfaceStyleRefraction;
class IfcTextStyleWithMirror;
class IfcTextStyleWithSpacing;
class IfcTextStyleWithBoxCharacteristics;
class IfcCartesianPoint;
class IfcDerivedUnit;
class IfcNamedUnit;
class IfcMonetaryUnit;
class IfcDirection;
class IfcVector;

extern const OdAnsiString sCommonUnset;

class IFC2X2_FINAL_EXPORT IfcActorSelect
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

class IFC2X2_FINAL_EXPORT IfcActorSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcActorSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcAppliedValueSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcAppliedValueSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcMeasureWithUnit();
  void setIfcMeasureWithUnit(IfcMeasureWithUnit* val);

  bool isIfcMonetaryMeasure();
  void setIfcMonetaryMeasure(IfcMonetaryMeasure val);

  bool isIfcRatioMeasure();
  void setIfcRatioMeasure(IfcRatioMeasure val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X2_FINAL_EXPORT IfcAppliedValueSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcAppliedValueSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcAxis2Placement
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

class IFC2X2_FINAL_EXPORT IfcAxis2PlacementTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcAxis2PlacementTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcBooleanOperand
  : public OdDAI::SelectWrapper
{
public:

  IfcBooleanOperand(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcBooleanResult();
  void setIfcBooleanResult(IfcBooleanResult* val);

  bool isIfcHalfSpaceSolid();
  void setIfcHalfSpaceSolid(IfcHalfSpaceSolid* val);

  bool isIfcSolidModel();
  void setIfcSolidModel(IfcSolidModel* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X2_FINAL_EXPORT IfcBooleanOperandTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcBooleanOperandTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcCharacterSpacingSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcCharacterSpacingSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcLengthMeasure();
  void setIfcLengthMeasure(IfcLengthMeasure val);

  bool isIfcMeasureWithUnit();
  void setIfcMeasureWithUnit(IfcMeasureWithUnit* val);

  bool isIfcRatioMeasure();
  void setIfcRatioMeasure(IfcRatioMeasure val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X2_FINAL_EXPORT IfcCharacterSpacingSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcCharacterSpacingSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcCharacterStyleSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcCharacterStyleSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcColourSpecification();
  void setIfcColourSpecification(IfcColourSpecification* val);

  bool isIfcPreDefinedColour();
  void setIfcPreDefinedColour(IfcPreDefinedColour* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X2_FINAL_EXPORT IfcCharacterStyleSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcCharacterStyleSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcClassificationNotationSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcClassificationNotationSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcClassificationNotation();
  void setIfcClassificationNotation(IfcClassificationNotation* val);

  bool isIfcClassificationReference();
  void setIfcClassificationReference(IfcClassificationReference* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X2_FINAL_EXPORT IfcClassificationNotationSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcClassificationNotationSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcColour
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

class IFC2X2_FINAL_EXPORT IfcColourTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcColourTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcColourOrFactor
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

class IFC2X2_FINAL_EXPORT IfcColourOrFactorTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcColourOrFactorTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcConditionCriterionSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcConditionCriterionSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcLabel();
  void setIfcLabel(IfcLabel val);

  bool isIfcMeasureWithUnit();
  void setIfcMeasureWithUnit(IfcMeasureWithUnit* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X2_FINAL_EXPORT IfcConditionCriterionSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcConditionCriterionSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcCsgSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcCsgSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcBooleanResult();
  void setIfcBooleanResult(IfcBooleanResult* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X2_FINAL_EXPORT IfcCsgSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcCsgSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcCurveFontOrScaledCurveFontSelect
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

class IFC2X2_FINAL_EXPORT IfcCurveFontOrScaledCurveFontSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcCurveFontOrScaledCurveFontSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcCurveStyleFontSelect
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

class IFC2X2_FINAL_EXPORT IfcCurveStyleFontSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcCurveStyleFontSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcDateTimeSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcDateTimeSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcCalendarDate();
  void setIfcCalendarDate(IfcCalendarDate* val);

  bool isIfcDateAndTime();
  void setIfcDateAndTime(IfcDateAndTime* val);

  bool isIfcLocalTime();
  void setIfcLocalTime(IfcLocalTime* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X2_FINAL_EXPORT IfcDateTimeSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcDateTimeSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcDefinedSymbolSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcDefinedSymbolSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcExternallyDefinedSymbol();
  void setIfcExternallyDefinedSymbol(IfcExternallyDefinedSymbol* val);

  bool isIfcPreDefinedSymbol();
  void setIfcPreDefinedSymbol(IfcPreDefinedSymbol* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X2_FINAL_EXPORT IfcDefinedSymbolSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcDefinedSymbolSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcDerivedMeasureValue
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

  bool isIfcSoundPowerMeasure();
  void setIfcSoundPowerMeasure(IfcSoundPowerMeasure val);

  bool isIfcSoundPressureMeasure();
  void setIfcSoundPressureMeasure(IfcSoundPressureMeasure val);

  bool isIfcSpecificHeatCapacityMeasure();
  void setIfcSpecificHeatCapacityMeasure(IfcSpecificHeatCapacityMeasure val);

  bool isIfcTemperatureGradientMeasure();
  void setIfcTemperatureGradientMeasure(IfcTemperatureGradientMeasure val);

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

  bool isIfcTimeStamp();
  void setIfcTimeStamp(IfcTimeStamp val);

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

class IFC2X2_FINAL_EXPORT IfcDerivedMeasureValueTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcDerivedMeasureValueTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcDocumentSelect
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

class IFC2X2_FINAL_EXPORT IfcDocumentSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcDocumentSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcDraughtingCalloutElement
  : public OdDAI::SelectWrapper
{
public:

  IfcDraughtingCalloutElement(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcAnnotationCurveOccurrence();
  void setIfcAnnotationCurveOccurrence(IfcAnnotationCurveOccurrence* val);

  bool isIfcAnnotationSymbolOccurrence();
  void setIfcAnnotationSymbolOccurrence(IfcAnnotationSymbolOccurrence* val);

  bool isIfcAnnotationTextOccurrence();
  void setIfcAnnotationTextOccurrence(IfcAnnotationTextOccurrence* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X2_FINAL_EXPORT IfcDraughtingCalloutElementTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcDraughtingCalloutElementTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcFillAreaStyleTileShapeSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcFillAreaStyleTileShapeSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcFillAreaStyleTileSymbolWithStyle();
  void setIfcFillAreaStyleTileSymbolWithStyle(IfcFillAreaStyleTileSymbolWithStyle* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X2_FINAL_EXPORT IfcFillAreaStyleTileShapeSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcFillAreaStyleTileShapeSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcFillStyleSelect
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

class IFC2X2_FINAL_EXPORT IfcFillStyleSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcFillStyleSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcFontSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcFontSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcExternallyDefinedTextFont();
  void setIfcExternallyDefinedTextFont(IfcExternallyDefinedTextFont* val);

  bool isIfcPreDefinedTextFont();
  void setIfcPreDefinedTextFont(IfcPreDefinedTextFont* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X2_FINAL_EXPORT IfcFontSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcFontSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcGeometricSetSelect
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

class IFC2X2_FINAL_EXPORT IfcGeometricSetSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcGeometricSetSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcLayeredItem
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

class IFC2X2_FINAL_EXPORT IfcLayeredItemTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcLayeredItemTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcLibrarySelect
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

class IFC2X2_FINAL_EXPORT IfcLibrarySelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcLibrarySelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcLightDistributionDataSourceSelect
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

class IFC2X2_FINAL_EXPORT IfcLightDistributionDataSourceSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcLightDistributionDataSourceSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcMaterialSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcMaterialSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcMaterial();
  void setIfcMaterial(IfcMaterial* val);

  bool isIfcMaterialLayer();
  void setIfcMaterialLayer(IfcMaterialLayer* val);

  bool isIfcMaterialLayerSet();
  void setIfcMaterialLayerSet(IfcMaterialLayerSet* val);

  bool isIfcMaterialLayerSetUsage();
  void setIfcMaterialLayerSetUsage(IfcMaterialLayerSetUsage* val);

  bool isIfcMaterialList();
  void setIfcMaterialList(IfcMaterialList* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X2_FINAL_EXPORT IfcMaterialSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcMaterialSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcMeasureValue
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

class IFC2X2_FINAL_EXPORT IfcMeasureValueTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcMeasureValueTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcMetricValueSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcMetricValueSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcCalendarDate();
  void setIfcCalendarDate(IfcCalendarDate* val);

  bool isIfcCostValue();
  void setIfcCostValue(IfcCostValue* val);

  bool isIfcDateAndTime();
  void setIfcDateAndTime(IfcDateAndTime* val);

  bool isIfcLocalTime();
  void setIfcLocalTime(IfcLocalTime* val);

  bool isIfcMeasureWithUnit();
  void setIfcMeasureWithUnit(IfcMeasureWithUnit* val);

  bool isIfcTable();
  void setIfcTable(IfcTable* val);

  bool isIfcText();
  void setIfcText(IfcText val);

  bool isIfcTimeSeries();
  void setIfcTimeSeries(IfcTimeSeries* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X2_FINAL_EXPORT IfcMetricValueSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcMetricValueSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcObjectReferenceSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcObjectReferenceSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcAddress();
  void setIfcAddress(IfcAddress* val);

  bool isIfcAppliedValue();
  void setIfcAppliedValue(IfcAppliedValue* val);

  bool isIfcCalendarDate();
  void setIfcCalendarDate(IfcCalendarDate* val);

  bool isIfcDateAndTime();
  void setIfcDateAndTime(IfcDateAndTime* val);

  bool isIfcExternalReference();
  void setIfcExternalReference(IfcExternalReference* val);

  bool isIfcLocalTime();
  void setIfcLocalTime(IfcLocalTime* val);

  bool isIfcMaterial();
  void setIfcMaterial(IfcMaterial* val);

  bool isIfcMaterialLayer();
  void setIfcMaterialLayer(IfcMaterialLayer* val);

  bool isIfcMaterialList();
  void setIfcMaterialList(IfcMaterialList* val);

  bool isIfcOrganization();
  void setIfcOrganization(IfcOrganization* val);

  bool isIfcPerson();
  void setIfcPerson(IfcPerson* val);

  bool isIfcPersonAndOrganization();
  void setIfcPersonAndOrganization(IfcPersonAndOrganization* val);

  bool isIfcTimeSeries();
  void setIfcTimeSeries(IfcTimeSeries* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X2_FINAL_EXPORT IfcObjectReferenceSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcObjectReferenceSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcPresentationStyleSelect
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

  bool isIfcSymbolStyle();
  void setIfcSymbolStyle(IfcSymbolStyle* val);

  bool isIfcTextStyle();
  void setIfcTextStyle(IfcTextStyle* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X2_FINAL_EXPORT IfcPresentationStyleSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcPresentationStyleSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcShell
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

class IFC2X2_FINAL_EXPORT IfcShellTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcShellTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcSimpleValue
  : public OdDAI::SelectWrapper
{
public:

  IfcSimpleValue(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcBoolean();
  void setIfcBoolean(IfcBoolean val);

  bool isIfcIdentifier();
  void setIfcIdentifier(IfcIdentifier val);

  bool isIfcInteger();
  void setIfcInteger(IfcInteger val);

  bool isIfcLabel();
  void setIfcLabel(IfcLabel val);

  bool isIfcLogical();
  void setIfcLogical(IfcLogical val);

  bool isIfcReal();
  void setIfcReal(IfcReal val);

  bool isIfcText();
  void setIfcText(IfcText val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X2_FINAL_EXPORT IfcSimpleValueTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcSimpleValueTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcSizeSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcSizeSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcMeasureWithUnit();
  void setIfcMeasureWithUnit(IfcMeasureWithUnit* val);

  bool isIfcPositiveLengthMeasure();
  void setIfcPositiveLengthMeasure(IfcPositiveLengthMeasure val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X2_FINAL_EXPORT IfcSizeSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcSizeSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcSpecularHighlightSelect
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

class IFC2X2_FINAL_EXPORT IfcSpecularHighlightSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcSpecularHighlightSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcStructuralActivityAssignmentSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcStructuralActivityAssignmentSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcBuildingElement();
  void setIfcBuildingElement(IfcBuildingElement* val);

  bool isIfcStructuralItem();
  void setIfcStructuralItem(IfcStructuralItem* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X2_FINAL_EXPORT IfcStructuralActivityAssignmentSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcStructuralActivityAssignmentSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcSurfaceStyleElementSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcSurfaceStyleElementSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcExternallyDefinedSufaceStyle();
  void setIfcExternallyDefinedSufaceStyle(IfcExternallyDefinedSufaceStyle* val);

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

class IFC2X2_FINAL_EXPORT IfcSurfaceStyleElementSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcSurfaceStyleElementSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcSymbolStyleSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcSymbolStyleSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcColourSpecification();
  void setIfcColourSpecification(IfcColourSpecification* val);

  bool isIfcPreDefinedColour();
  void setIfcPreDefinedColour(IfcPreDefinedColour* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X2_FINAL_EXPORT IfcSymbolStyleSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcSymbolStyleSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcTextStyleSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcTextStyleSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcTextStyleWithBoxCharacteristics();
  void setIfcTextStyleWithBoxCharacteristics(IfcTextStyleWithBoxCharacteristics* val);

  bool isIfcTextStyleWithMirror();
  void setIfcTextStyleWithMirror(IfcTextStyleWithMirror* val);

  bool isIfcTextStyleWithSpacing();
  void setIfcTextStyleWithSpacing(IfcTextStyleWithSpacing* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X2_FINAL_EXPORT IfcTextStyleSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcTextStyleSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcTrimmingSelect
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

class IFC2X2_FINAL_EXPORT IfcTrimmingSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcTrimmingSelectTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcUnit
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

class IFC2X2_FINAL_EXPORT IfcUnitTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcUnitTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcValue
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

  bool isIfcAreaMeasure();
  void setIfcAreaMeasure(IfcAreaMeasure val);

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

  bool isIfcDescriptiveMeasure();
  void setIfcDescriptiveMeasure(IfcDescriptiveMeasure val);

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

  bool isIfcSoundPowerMeasure();
  void setIfcSoundPowerMeasure(IfcSoundPowerMeasure val);

  bool isIfcSoundPressureMeasure();
  void setIfcSoundPressureMeasure(IfcSoundPressureMeasure val);

  bool isIfcSpecificHeatCapacityMeasure();
  void setIfcSpecificHeatCapacityMeasure(IfcSpecificHeatCapacityMeasure val);

  bool isIfcTemperatureGradientMeasure();
  void setIfcTemperatureGradientMeasure(IfcTemperatureGradientMeasure val);

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

class IFC2X2_FINAL_EXPORT IfcValueTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcValueTypeProvider& instance();


};

class IFC2X2_FINAL_EXPORT IfcVectorOrDirection
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

class IFC2X2_FINAL_EXPORT IfcVectorOrDirectionTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcVectorOrDirectionTypeProvider& instance();


};


} // namespace

#endif // _IFC2X2_FINAL_SELECT_TYPES_H

