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

#ifndef _IFC2X2_FINAL_SIMPLETYPES_H
#define _IFC2X2_FINAL_SIMPLETYPES_H

#include "daiPrimitive.h"
#include "IfcGUID.h"

namespace OdIfc2x2_final {


  // Simple types

  typedef double IfcAbsorbedDoseMeasure;
  typedef double IfcAccelerationMeasure;
  typedef double IfcAmountOfSubstanceMeasure;
  typedef double IfcAngularVelocityMeasure;
  typedef double IfcAreaMeasure;
  typedef OdDAI::Boolean IfcBoolean;
  typedef double IfcContextDependentMeasure;
  typedef double IfcCountMeasure;
  typedef double IfcCurvatureMeasure;
  typedef int IfcDayInMonthNumber;
  typedef int IfcDaylightSavingHour;
  typedef OdAnsiString IfcDescriptiveMeasure;
  typedef int IfcDimensionCount;
  typedef double IfcDoseEquivalentMeasure;
  typedef double IfcDynamicViscosityMeasure;
  typedef double IfcElectricCapacitanceMeasure;
  typedef double IfcElectricChargeMeasure;
  typedef double IfcElectricConductanceMeasure;
  typedef double IfcElectricCurrentMeasure;
  typedef double IfcElectricResistanceMeasure;
  typedef double IfcElectricVoltageMeasure;
  typedef double IfcEnergyMeasure;
  typedef double IfcForceMeasure;
  typedef double IfcFrequencyMeasure;
  typedef OdIfcGUID IfcGloballyUniqueId;
  typedef double IfcHeatFluxDensityMeasure;
  typedef double IfcHeatingValueMeasure;
  typedef int IfcHourInDay;
  typedef OdAnsiString IfcIdentifier;
  typedef double IfcIlluminanceMeasure;
  typedef double IfcInductanceMeasure;
  typedef int IfcInteger;
  typedef int IfcIntegerCountRateMeasure;
  typedef double IfcIonConcentrationMeasure;
  typedef double IfcIsothermalMoistureCapacityMeasure;
  typedef double IfcKinematicViscosityMeasure;
  typedef OdAnsiString IfcLabel;
  typedef double IfcLengthMeasure;
  typedef double IfcLinearForceMeasure;
  typedef double IfcLinearMomentMeasure;
  typedef double IfcLinearStiffnessMeasure;
  typedef double IfcLinearVelocityMeasure;
  typedef OdDAI::Logical IfcLogical;
  typedef double IfcLuminousFluxMeasure;
  typedef double IfcLuminousIntensityDistributionMeasure;
  typedef double IfcLuminousIntensityMeasure;
  typedef double IfcMagneticFluxDensityMeasure;
  typedef double IfcMagneticFluxMeasure;
  typedef double IfcMassDensityMeasure;
  typedef double IfcMassFlowRateMeasure;
  typedef double IfcMassMeasure;
  typedef double IfcMassPerLengthMeasure;
  typedef int IfcMinuteInHour;
  typedef double IfcModulusOfElasticityMeasure;
  typedef double IfcModulusOfLinearSubgradeReactionMeasure;
  typedef double IfcModulusOfRotationalSubgradeReactionMeasure;
  typedef double IfcModulusOfSubgradeReactionMeasure;
  typedef double IfcMoistureDiffusivityMeasure;
  typedef double IfcMolecularWeightMeasure;
  typedef double IfcMomentOfInertiaMeasure;
  typedef double IfcMonetaryMeasure;
  typedef int IfcMonthInYearNumber;
  typedef double IfcNumericMeasure;
  typedef double IfcPHMeasure;
  typedef double IfcParameterValue;
  typedef double IfcPlanarForceMeasure;
  typedef double IfcPlaneAngleMeasure;
  typedef double IfcPowerMeasure;
  typedef OdAnsiString IfcPresentableText;
  typedef double IfcPressureMeasure;
  typedef double IfcRadioActivityMeasure;
  typedef double IfcRatioMeasure;
  typedef double IfcReal;
  typedef double IfcRotationalFrequencyMeasure;
  typedef double IfcRotationalMassMeasure;
  typedef double IfcRotationalStiffnessMeasure;
  typedef double IfcSecondInMinute;
  typedef double IfcSectionModulusMeasure;
  typedef double IfcSectionalAreaIntegralMeasure;
  typedef double IfcShearModulusMeasure;
  typedef double IfcSolidAngleMeasure;
  typedef double IfcSoundPowerMeasure;
  typedef double IfcSoundPressureMeasure;
  typedef double IfcSpecificHeatCapacityMeasure;
  typedef double IfcSpecularExponent;
  typedef double IfcSpecularRoughness;
  typedef double IfcTemperatureGradientMeasure;
  typedef OdAnsiString IfcText;
  typedef double IfcThermalAdmittanceMeasure;
  typedef double IfcThermalConductivityMeasure;
  typedef double IfcThermalExpansionCoefficientMeasure;
  typedef double IfcThermalResistanceMeasure;
  typedef double IfcThermalTransmittanceMeasure;
  typedef double IfcThermodynamicTemperatureMeasure;
  typedef double IfcTimeMeasure;
  typedef int IfcTimeStamp;
  typedef double IfcTorqueMeasure;
  typedef double IfcVaporPermeabilityMeasure;
  typedef double IfcVolumeMeasure;
  typedef double IfcVolumetricFlowRateMeasure;
  typedef double IfcWarpingConstantMeasure;
  typedef double IfcWarpingMomentMeasure;
  typedef int IfcYearNumber;

  // Defined types

  typedef IfcRatioMeasure IfcNormalisedRatioMeasure;
  typedef IfcLengthMeasure IfcPositiveLengthMeasure;
  typedef IfcPlaneAngleMeasure IfcPositivePlaneAngleMeasure;
  typedef IfcRatioMeasure IfcPositiveRatioMeasure;
  typedef IfcLabel IfcTextAlignment;


} // namespace

#endif // _IFC2X2_FINAL_SIMPLETYPES_H

