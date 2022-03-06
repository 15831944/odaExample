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

#ifndef _IFC2X_FINAL_SELECT_TYPES_H
#define _IFC2X_FINAL_SELECT_TYPES_H

#include "daiNamedType.h"
#include "daiSelectWrapper.h"
#include "daiValueTypes.h"
#include "Ifc2x_FinalCollectionTypes.h"
#include "Ifc2x_FinalSimpleTypes.h"
#include "Ifc2x_FinalEnum.h"
#include "Ifc2x_FinalBuildOption.h"

namespace OdIfc2x_final {

class IfcAxis2Placement2D;
class IfcAxis2Placement3D;
class IfcOrganization;
class IfcPerson;
class IfcPersonAndOrganization;
class IfcCalendarDate;
class IfcLocalTime;
class IfcDateAndTime;
class IfcClassificationNotation;
class IfcClassificationReference;
class IfcDocumentReference;
class IfcDocumentInformation;
class IfcLibraryReference;
class IfcLibraryInformation;
class IfcBooleanResult;
class IfcPoint;
class IfcCurve;
class IfcSurface;
class IfcSolidModel;
class IfcHalfSpaceSolid;
class IfcCartesianPoint;
class IfcDirection;
class IfcVector;
class IfcMaterial;
class IfcMaterialList;
class IfcMaterialLayerSetUsage;
class IfcDerivedUnit;
class IfcNamedUnit;
class IfcMonetaryUnit;
class IfcMaterialLayer;
class IfcExternalReference;
class IfcClosedShell;
class IfcOpenShell;
class IfcMeasureWithUnit;
class IfcTable;
class IfcCostModifierValue;
class IfcShapeAspect;
class IfcShapeRepresentation;
class IfcFurnitureStandard;
class IfcEquipmentStandard;
class IfcSpaceProgram;

extern const OdAnsiString sCommonUnset;

class IFC2X_FINAL_EXPORT IfcAxis2Placement
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

class IFC2X_FINAL_EXPORT IfcAxis2PlacementTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcAxis2PlacementTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcActorSelect
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

class IFC2X_FINAL_EXPORT IfcActorSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcActorSelectTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcDateTimeSelect
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

class IFC2X_FINAL_EXPORT IfcDateTimeSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcDateTimeSelectTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcClassificationNotationSelect
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

class IFC2X_FINAL_EXPORT IfcClassificationNotationSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcClassificationNotationSelectTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcDocumentSelect
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

class IFC2X_FINAL_EXPORT IfcDocumentSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcDocumentSelectTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcLibrarySelect
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

class IFC2X_FINAL_EXPORT IfcLibrarySelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcLibrarySelectTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcCsgSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcCsgSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcBooleanResult();
  void setIfcBooleanResult(IfcBooleanResult* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X_FINAL_EXPORT IfcCsgSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcCsgSelectTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcGeometricSetSelect
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

class IFC2X_FINAL_EXPORT IfcGeometricSetSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcGeometricSetSelectTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcBooleanOperand
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

class IFC2X_FINAL_EXPORT IfcBooleanOperandTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcBooleanOperandTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcTrimmingSelect
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

class IFC2X_FINAL_EXPORT IfcTrimmingSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcTrimmingSelectTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcVectorOrDirection
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

class IFC2X_FINAL_EXPORT IfcVectorOrDirectionTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcVectorOrDirectionTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcMaterialSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcMaterialSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcMaterial();
  void setIfcMaterial(IfcMaterial* val);

  bool isIfcMaterialLayerSetUsage();
  void setIfcMaterialLayerSetUsage(IfcMaterialLayerSetUsage* val);

  bool isIfcMaterialList();
  void setIfcMaterialList(IfcMaterialList* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X_FINAL_EXPORT IfcMaterialSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcMaterialSelectTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcUnit
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

class IFC2X_FINAL_EXPORT IfcUnitTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcUnitTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcValue
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

  bool isIfcCompoundPlaneAngleMeasure();
  void setIfcCompoundPlaneAngleMeasure(OdArray<int > val);

  bool isIfcContextDependentMeasure();
  void setIfcContextDependentMeasure(IfcContextDependentMeasure val);

  bool isIfcCountMeasure();
  void setIfcCountMeasure(IfcCountMeasure val);

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

  bool isIfcModulusOfElasticityMeasure();
  void setIfcModulusOfElasticityMeasure(IfcModulusOfElasticityMeasure val);

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

  bool isIfcRotationalStiffnessMeasure();
  void setIfcRotationalStiffnessMeasure(IfcRotationalStiffnessMeasure val);

  bool isIfcShearModulusMeasure();
  void setIfcShearModulusMeasure(IfcShearModulusMeasure val);

  bool isIfcSolidAngleMeasure();
  void setIfcSolidAngleMeasure(IfcSolidAngleMeasure val);

  bool isIfcSpecificHeatCapacityMeasure();
  void setIfcSpecificHeatCapacityMeasure(IfcSpecificHeatCapacityMeasure val);

  bool isIfcText();
  void setIfcText(IfcText val);

  bool isIfcThermalAdmittanceMeasure();
  void setIfcThermalAdmittanceMeasure(IfcThermalAdmittanceMeasure val);

  bool isIfcThermalConductivityMeasure();
  void setIfcThermalConductivityMeasure(IfcThermalConductivityMeasure val);

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

  static OdDAI::Select createEmptySelect();

};

class IFC2X_FINAL_EXPORT IfcValueTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcValueTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcMeasureValue
  : public OdDAI::SelectWrapper
{
public:

  IfcMeasureValue(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcAmountOfSubstanceMeasure();
  void setIfcAmountOfSubstanceMeasure(IfcAmountOfSubstanceMeasure val);

  bool isIfcAreaMeasure();
  void setIfcAreaMeasure(IfcAreaMeasure val);

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

class IFC2X_FINAL_EXPORT IfcMeasureValueTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcMeasureValueTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcSimpleValue
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

class IFC2X_FINAL_EXPORT IfcSimpleValueTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcSimpleValueTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcDerivedMeasureValue
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

  bool isIfcIlluminanceMeasure();
  void setIfcIlluminanceMeasure(IfcIlluminanceMeasure val);

  bool isIfcInductanceMeasure();
  void setIfcInductanceMeasure(IfcInductanceMeasure val);

  bool isIfcIntegerCountRateMeasure();
  void setIfcIntegerCountRateMeasure(IfcIntegerCountRateMeasure val);

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

  bool isIfcMagneticFluxDensityMeasure();
  void setIfcMagneticFluxDensityMeasure(IfcMagneticFluxDensityMeasure val);

  bool isIfcMagneticFluxMeasure();
  void setIfcMagneticFluxMeasure(IfcMagneticFluxMeasure val);

  bool isIfcMassDensityMeasure();
  void setIfcMassDensityMeasure(IfcMassDensityMeasure val);

  bool isIfcMassFlowRateMeasure();
  void setIfcMassFlowRateMeasure(IfcMassFlowRateMeasure val);

  bool isIfcModulusOfElasticityMeasure();
  void setIfcModulusOfElasticityMeasure(IfcModulusOfElasticityMeasure val);

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

  bool isIfcRotationalStiffnessMeasure();
  void setIfcRotationalStiffnessMeasure(IfcRotationalStiffnessMeasure val);

  bool isIfcShearModulusMeasure();
  void setIfcShearModulusMeasure(IfcShearModulusMeasure val);

  bool isIfcSpecificHeatCapacityMeasure();
  void setIfcSpecificHeatCapacityMeasure(IfcSpecificHeatCapacityMeasure val);

  bool isIfcThermalAdmittanceMeasure();
  void setIfcThermalAdmittanceMeasure(IfcThermalAdmittanceMeasure val);

  bool isIfcThermalConductivityMeasure();
  void setIfcThermalConductivityMeasure(IfcThermalConductivityMeasure val);

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

  static OdDAI::Select createEmptySelect();

};

class IFC2X_FINAL_EXPORT IfcDerivedMeasureValueTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcDerivedMeasureValueTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcObjectReferenceSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcObjectReferenceSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

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

  static OdDAI::Select createEmptySelect();

};

class IFC2X_FINAL_EXPORT IfcObjectReferenceSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcObjectReferenceSelectTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcShell
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

class IFC2X_FINAL_EXPORT IfcShellTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcShellTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcMetricValueSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcMetricValueSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcMeasureWithUnit();
  void setIfcMeasureWithUnit(IfcMeasureWithUnit* val);

  bool isIfcTable();
  void setIfcTable(IfcTable* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X_FINAL_EXPORT IfcMetricValueSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcMetricValueSelectTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcCostModifierValueSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcCostModifierValueSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcCostModifierValue();
  void setIfcCostModifierValue(IfcCostModifierValue* val);

  bool isIfcRatioMeasure();
  void setIfcRatioMeasure(IfcRatioMeasure val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X_FINAL_EXPORT IfcCostModifierValueSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcCostModifierValueSelectTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcStyledItemSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcStyledItemSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcShapeAspect();
  void setIfcShapeAspect(IfcShapeAspect* val);

  bool isIfcShapeRepresentation();
  void setIfcShapeRepresentation(IfcShapeRepresentation* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X_FINAL_EXPORT IfcStyledItemSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcStyledItemSelectTypeProvider& instance();


};

class IFC2X_FINAL_EXPORT IfcFMStandardSelect
  : public OdDAI::SelectWrapper
{
public:

  IfcFMStandardSelect(OdDAI::Select& select) : OdDAI::SelectWrapper(select) {};

  bool isIfcEquipmentStandard();
  void setIfcEquipmentStandard(IfcEquipmentStandard* val);

  bool isIfcFurnitureStandard();
  void setIfcFurnitureStandard(IfcFurnitureStandard* val);

  bool isIfcSpaceProgram();
  void setIfcSpaceProgram(IfcSpaceProgram* val);

  static OdDAI::Select createEmptySelect();

};

class IFC2X_FINAL_EXPORT IfcFMStandardSelectTypeProvider
  : public OdDAI::SelectTypeProvider
{
public:

  static const OdDAI::SelectType* SchemaType();
  static void init(const OdRxDictionaryPtr& types);
  static void uninit();
  static IfcFMStandardSelectTypeProvider& instance();


};


} // namespace

#endif // _IFC2X_FINAL_SELECT_TYPES_H

