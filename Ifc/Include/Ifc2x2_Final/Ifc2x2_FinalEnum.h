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

#ifndef _IFC2X2_FINAL_ENUM_H
#define _IFC2X2_FINAL_ENUM_H

#include "RxValue.h"
#include "daiEnum.h"
#include "Ifc2x2_FinalBuildOption.h"

namespace OdIfc2x2_final {

enum IfcActionSourceTypeEnum
{
  kIfcActionSourceTypeEnum_DEAD_LOAD_G,
  kIfcActionSourceTypeEnum_COMPLETION_G1,
  kIfcActionSourceTypeEnum_LIVE_LOAD_Q,
  kIfcActionSourceTypeEnum_SNOW_S,
  kIfcActionSourceTypeEnum_WIND_W,
  kIfcActionSourceTypeEnum_PRESTRESSING_P,
  kIfcActionSourceTypeEnum_SETTLEMENT_U,
  kIfcActionSourceTypeEnum_TEMPERATURE_T,
  kIfcActionSourceTypeEnum_EARTHQUAKE_E,
  kIfcActionSourceTypeEnum_FIRE,
  kIfcActionSourceTypeEnum_IMPULSE,
  kIfcActionSourceTypeEnum_IMPACT,
  kIfcActionSourceTypeEnum_TRANSPORT,
  kIfcActionSourceTypeEnum_ERECTION,
  kIfcActionSourceTypeEnum_PROPPING,
  kIfcActionSourceTypeEnum_SYSTEM_IMPERFECTION,
  kIfcActionSourceTypeEnum_SHRINKAGE,
  kIfcActionSourceTypeEnum_CREEP,
  kIfcActionSourceTypeEnum_LACK_OF_FIT,
  kIfcActionSourceTypeEnum_BUOYANCY,
  kIfcActionSourceTypeEnum_ICE,
  kIfcActionSourceTypeEnum_CURRENT,
  kIfcActionSourceTypeEnum_WAVE,
  kIfcActionSourceTypeEnum_RAIN,
  kIfcActionSourceTypeEnum_BRAKES,
  kIfcActionSourceTypeEnum_USERDEFINED,
  kIfcActionSourceTypeEnum_NOTDEFINED,
  kIfcActionSourceTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcActionSourceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcActionSourceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcActionSourceTypeEnum& getUnset<OdIfc2x2_final::IfcActionSourceTypeEnum>() { static OdIfc2x2_final::IfcActionSourceTypeEnum nullEnum = OdIfc2x2_final::kIfcActionSourceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcActionTypeEnum
{
  kIfcActionTypeEnum_PERMANENT_G,
  kIfcActionTypeEnum_VARIABLE_Q,
  kIfcActionTypeEnum_EXTRAORDINARY_A,
  kIfcActionTypeEnum_USERDEFINED,
  kIfcActionTypeEnum_NOTDEFINED,
  kIfcActionTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcActionTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcActionTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcActionTypeEnum& getUnset<OdIfc2x2_final::IfcActionTypeEnum>() { static OdIfc2x2_final::IfcActionTypeEnum nullEnum = OdIfc2x2_final::kIfcActionTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcActuatorTypeEnum
{
  kIfcActuatorTypeEnum_ELECTRICACTUATOR,
  kIfcActuatorTypeEnum_HANDOPERATEDACTUATOR,
  kIfcActuatorTypeEnum_HYDRAULICACTUATOR,
  kIfcActuatorTypeEnum_PNEUMATICACTUATOR,
  kIfcActuatorTypeEnum_THERMOSTATICACTUATOR,
  kIfcActuatorTypeEnum_USERDEFINED,
  kIfcActuatorTypeEnum_NOTDEFINED,
  kIfcActuatorTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcActuatorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcActuatorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcActuatorTypeEnum& getUnset<OdIfc2x2_final::IfcActuatorTypeEnum>() { static OdIfc2x2_final::IfcActuatorTypeEnum nullEnum = OdIfc2x2_final::kIfcActuatorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcAddressTypeEnum
{
  kIfcAddressTypeEnum_OFFICE,
  kIfcAddressTypeEnum_SITE,
  kIfcAddressTypeEnum_HOME,
  kIfcAddressTypeEnum_DISTRIBUTIONPOINT,
  kIfcAddressTypeEnum_USERDEFINED,
  kIfcAddressTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcAddressTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAddressTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcAddressTypeEnum& getUnset<OdIfc2x2_final::IfcAddressTypeEnum>() { static OdIfc2x2_final::IfcAddressTypeEnum nullEnum = OdIfc2x2_final::kIfcAddressTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcAheadOrBehind
{
  kIfcAheadOrBehind_AHEAD,
  kIfcAheadOrBehind_BEHIND,
  kIfcAheadOrBehind_unset
};

class IFC2X2_FINAL_EXPORT IfcAheadOrBehindTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAheadOrBehindTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcAheadOrBehind& getUnset<OdIfc2x2_final::IfcAheadOrBehind>() { static OdIfc2x2_final::IfcAheadOrBehind nullEnum = OdIfc2x2_final::kIfcAheadOrBehind_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcAirTerminalBoxTypeEnum
{
  kIfcAirTerminalBoxTypeEnum_CONSTANTFLOW,
  kIfcAirTerminalBoxTypeEnum_VARIABLEFLOWPRESSUREDEPENDANT,
  kIfcAirTerminalBoxTypeEnum_VARIABLEFLOWPRESSUREINDEPENDANT,
  kIfcAirTerminalBoxTypeEnum_USERDEFINED,
  kIfcAirTerminalBoxTypeEnum_NOTDEFINED,
  kIfcAirTerminalBoxTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcAirTerminalBoxTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAirTerminalBoxTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcAirTerminalBoxTypeEnum& getUnset<OdIfc2x2_final::IfcAirTerminalBoxTypeEnum>() { static OdIfc2x2_final::IfcAirTerminalBoxTypeEnum nullEnum = OdIfc2x2_final::kIfcAirTerminalBoxTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcAirTerminalTypeEnum
{
  kIfcAirTerminalTypeEnum_GRILLE,
  kIfcAirTerminalTypeEnum_REGISTER,
  kIfcAirTerminalTypeEnum_DIFFUSER,
  kIfcAirTerminalTypeEnum_EYEBALL,
  kIfcAirTerminalTypeEnum_IRIS,
  kIfcAirTerminalTypeEnum_LINEARGRILLE,
  kIfcAirTerminalTypeEnum_LINEARDIFFUSER,
  kIfcAirTerminalTypeEnum_USERDEFINED,
  kIfcAirTerminalTypeEnum_NOTDEFINED,
  kIfcAirTerminalTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcAirTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAirTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcAirTerminalTypeEnum& getUnset<OdIfc2x2_final::IfcAirTerminalTypeEnum>() { static OdIfc2x2_final::IfcAirTerminalTypeEnum nullEnum = OdIfc2x2_final::kIfcAirTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcAirToAirHeatRecoveryTypeEnum
{
  kIfcAirToAirHeatRecoveryTypeEnum_FIXEDPLATECOUNTERFLOWEXCHANGER,
  kIfcAirToAirHeatRecoveryTypeEnum_FIXEDPLATECROSSFLOWEXCHANGER,
  kIfcAirToAirHeatRecoveryTypeEnum_FIXEDPLATEPARALLELFLOWEXCHANGER,
  kIfcAirToAirHeatRecoveryTypeEnum_ROTARYWHEEL,
  kIfcAirToAirHeatRecoveryTypeEnum_RUNAROUNDCOILLOOP,
  kIfcAirToAirHeatRecoveryTypeEnum_HEATPIPE,
  kIfcAirToAirHeatRecoveryTypeEnum_TWINTOWERENTHALPYRECOVERYLOOPS,
  kIfcAirToAirHeatRecoveryTypeEnum_THERMOSIPHONSEALEDTUBEHEATEXCHANGERS,
  kIfcAirToAirHeatRecoveryTypeEnum_THERMOSIPHONCOILTYPEHEATEXCHANGERS,
  kIfcAirToAirHeatRecoveryTypeEnum_USERDEFINED,
  kIfcAirToAirHeatRecoveryTypeEnum_NOTDEFINED,
  kIfcAirToAirHeatRecoveryTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcAirToAirHeatRecoveryTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAirToAirHeatRecoveryTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcAirToAirHeatRecoveryTypeEnum& getUnset<OdIfc2x2_final::IfcAirToAirHeatRecoveryTypeEnum>() { static OdIfc2x2_final::IfcAirToAirHeatRecoveryTypeEnum nullEnum = OdIfc2x2_final::kIfcAirToAirHeatRecoveryTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcAlarmTypeEnum
{
  kIfcAlarmTypeEnum_BELL,
  kIfcAlarmTypeEnum_BREAKGLASSBUTTON,
  kIfcAlarmTypeEnum_LIGHT,
  kIfcAlarmTypeEnum_MANUALPULLBOX,
  kIfcAlarmTypeEnum_SIREN,
  kIfcAlarmTypeEnum_WHISTLE,
  kIfcAlarmTypeEnum_USERDEFINED,
  kIfcAlarmTypeEnum_NOTDEFINED,
  kIfcAlarmTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcAlarmTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAlarmTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcAlarmTypeEnum& getUnset<OdIfc2x2_final::IfcAlarmTypeEnum>() { static OdIfc2x2_final::IfcAlarmTypeEnum nullEnum = OdIfc2x2_final::kIfcAlarmTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcAnalysisModelTypeEnum
{
  kIfcAnalysisModelTypeEnum_IN_PLANE_LOADING_2D,
  kIfcAnalysisModelTypeEnum_OUT_PLANE_LOADING_2D,
  kIfcAnalysisModelTypeEnum_LOADING_3D,
  kIfcAnalysisModelTypeEnum_USERDEFINED,
  kIfcAnalysisModelTypeEnum_NOTDEFINED,
  kIfcAnalysisModelTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcAnalysisModelTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAnalysisModelTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcAnalysisModelTypeEnum& getUnset<OdIfc2x2_final::IfcAnalysisModelTypeEnum>() { static OdIfc2x2_final::IfcAnalysisModelTypeEnum nullEnum = OdIfc2x2_final::kIfcAnalysisModelTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcAnalysisTheoryTypeEnum
{
  kIfcAnalysisTheoryTypeEnum_FIRST_ORDER_THEORY,
  kIfcAnalysisTheoryTypeEnum_SECOND_ORDER_THEORY,
  kIfcAnalysisTheoryTypeEnum_THIRD_ORDER_THEORY,
  kIfcAnalysisTheoryTypeEnum_FULL_NONLINEAR_THEORY,
  kIfcAnalysisTheoryTypeEnum_USERDEFINED,
  kIfcAnalysisTheoryTypeEnum_NOTDEFINED,
  kIfcAnalysisTheoryTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcAnalysisTheoryTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAnalysisTheoryTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcAnalysisTheoryTypeEnum& getUnset<OdIfc2x2_final::IfcAnalysisTheoryTypeEnum>() { static OdIfc2x2_final::IfcAnalysisTheoryTypeEnum nullEnum = OdIfc2x2_final::kIfcAnalysisTheoryTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcArithmeticOperatorEnum
{
  kIfcArithmeticOperatorEnum_ADD,
  kIfcArithmeticOperatorEnum_DIVIDE,
  kIfcArithmeticOperatorEnum_MULTIPLY,
  kIfcArithmeticOperatorEnum_SUBTRACT,
  kIfcArithmeticOperatorEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcArithmeticOperatorEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcArithmeticOperatorEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcArithmeticOperatorEnum& getUnset<OdIfc2x2_final::IfcArithmeticOperatorEnum>() { static OdIfc2x2_final::IfcArithmeticOperatorEnum nullEnum = OdIfc2x2_final::kIfcArithmeticOperatorEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcAssemblyPlaceEnum
{
  kIfcAssemblyPlaceEnum_SITE,
  kIfcAssemblyPlaceEnum_FACTORY,
  kIfcAssemblyPlaceEnum_NOTDEFINED,
  kIfcAssemblyPlaceEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcAssemblyPlaceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAssemblyPlaceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcAssemblyPlaceEnum& getUnset<OdIfc2x2_final::IfcAssemblyPlaceEnum>() { static OdIfc2x2_final::IfcAssemblyPlaceEnum nullEnum = OdIfc2x2_final::kIfcAssemblyPlaceEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcBSplineCurveForm
{
  kIfcBSplineCurveForm_POLYLINE_FORM,
  kIfcBSplineCurveForm_CIRCULAR_ARC,
  kIfcBSplineCurveForm_ELLIPTIC_ARC,
  kIfcBSplineCurveForm_PARABOLIC_ARC,
  kIfcBSplineCurveForm_HYPERBOLIC_ARC,
  kIfcBSplineCurveForm_UNSPECIFIED,
  kIfcBSplineCurveForm_unset
};

class IFC2X2_FINAL_EXPORT IfcBSplineCurveFormTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBSplineCurveFormTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcBSplineCurveForm& getUnset<OdIfc2x2_final::IfcBSplineCurveForm>() { static OdIfc2x2_final::IfcBSplineCurveForm nullEnum = OdIfc2x2_final::kIfcBSplineCurveForm_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcBeamTypeEnum
{
  kIfcBeamTypeEnum_BEAM,
  kIfcBeamTypeEnum_JOIST,
  kIfcBeamTypeEnum_LINTEL,
  kIfcBeamTypeEnum_T_BEAM,
  kIfcBeamTypeEnum_USERDEFINED,
  kIfcBeamTypeEnum_NOTDEFINED,
  kIfcBeamTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcBeamTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBeamTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcBeamTypeEnum& getUnset<OdIfc2x2_final::IfcBeamTypeEnum>() { static OdIfc2x2_final::IfcBeamTypeEnum nullEnum = OdIfc2x2_final::kIfcBeamTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcBenchmarkEnum
{
  kIfcBenchmarkEnum_GREATERTHAN,
  kIfcBenchmarkEnum_GREATERTHANOREQUALTO,
  kIfcBenchmarkEnum_LESSTHAN,
  kIfcBenchmarkEnum_LESSTHANOREQUALTO,
  kIfcBenchmarkEnum_EQUALTO,
  kIfcBenchmarkEnum_NOTEQUALTO,
  kIfcBenchmarkEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcBenchmarkEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBenchmarkEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcBenchmarkEnum& getUnset<OdIfc2x2_final::IfcBenchmarkEnum>() { static OdIfc2x2_final::IfcBenchmarkEnum nullEnum = OdIfc2x2_final::kIfcBenchmarkEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcBoilerTypeEnum
{
  kIfcBoilerTypeEnum_WATER,
  kIfcBoilerTypeEnum_STEAM,
  kIfcBoilerTypeEnum_USERDEFINED,
  kIfcBoilerTypeEnum_NOTDEFINED,
  kIfcBoilerTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcBoilerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBoilerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcBoilerTypeEnum& getUnset<OdIfc2x2_final::IfcBoilerTypeEnum>() { static OdIfc2x2_final::IfcBoilerTypeEnum nullEnum = OdIfc2x2_final::kIfcBoilerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcBooleanOperator
{
  kIfcBooleanOperator_UNION,
  kIfcBooleanOperator_INTERSECTION,
  kIfcBooleanOperator_DIFFERENCE,
  kIfcBooleanOperator_unset
};

class IFC2X2_FINAL_EXPORT IfcBooleanOperatorTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBooleanOperatorTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcBooleanOperator& getUnset<OdIfc2x2_final::IfcBooleanOperator>() { static OdIfc2x2_final::IfcBooleanOperator nullEnum = OdIfc2x2_final::kIfcBooleanOperator_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcCableCarrierFittingTypeEnum
{
  kIfcCableCarrierFittingTypeEnum_BEND,
  kIfcCableCarrierFittingTypeEnum_CROSS,
  kIfcCableCarrierFittingTypeEnum_REDUCER,
  kIfcCableCarrierFittingTypeEnum_TEE,
  kIfcCableCarrierFittingTypeEnum_USERDEFINED,
  kIfcCableCarrierFittingTypeEnum_NOTDEFINED,
  kIfcCableCarrierFittingTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcCableCarrierFittingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCableCarrierFittingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcCableCarrierFittingTypeEnum& getUnset<OdIfc2x2_final::IfcCableCarrierFittingTypeEnum>() { static OdIfc2x2_final::IfcCableCarrierFittingTypeEnum nullEnum = OdIfc2x2_final::kIfcCableCarrierFittingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcCableCarrierSegmentTypeEnum
{
  kIfcCableCarrierSegmentTypeEnum_CABLELADDERSEGMENT,
  kIfcCableCarrierSegmentTypeEnum_CABLETRAYSEGMENT,
  kIfcCableCarrierSegmentTypeEnum_CABLETRUNKINGSEGMENT,
  kIfcCableCarrierSegmentTypeEnum_CONDUITSEGMENT,
  kIfcCableCarrierSegmentTypeEnum_USERDEFINED,
  kIfcCableCarrierSegmentTypeEnum_NOTDEFINED,
  kIfcCableCarrierSegmentTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcCableCarrierSegmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCableCarrierSegmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcCableCarrierSegmentTypeEnum& getUnset<OdIfc2x2_final::IfcCableCarrierSegmentTypeEnum>() { static OdIfc2x2_final::IfcCableCarrierSegmentTypeEnum nullEnum = OdIfc2x2_final::kIfcCableCarrierSegmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcCableSegmentTypeEnum
{
  kIfcCableSegmentTypeEnum_CABLESEGMENT,
  kIfcCableSegmentTypeEnum_CONDUCTORSEGMENT,
  kIfcCableSegmentTypeEnum_USERDEFINED,
  kIfcCableSegmentTypeEnum_NOTDEFINED,
  kIfcCableSegmentTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcCableSegmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCableSegmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcCableSegmentTypeEnum& getUnset<OdIfc2x2_final::IfcCableSegmentTypeEnum>() { static OdIfc2x2_final::IfcCableSegmentTypeEnum nullEnum = OdIfc2x2_final::kIfcCableSegmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcChangeActionEnum
{
  kIfcChangeActionEnum_NOCHANGE,
  kIfcChangeActionEnum_MODIFIED,
  kIfcChangeActionEnum_ADDED,
  kIfcChangeActionEnum_DELETED,
  kIfcChangeActionEnum_MODIFIEDADDED,
  kIfcChangeActionEnum_MODIFIEDDELETED,
  kIfcChangeActionEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcChangeActionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcChangeActionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcChangeActionEnum& getUnset<OdIfc2x2_final::IfcChangeActionEnum>() { static OdIfc2x2_final::IfcChangeActionEnum nullEnum = OdIfc2x2_final::kIfcChangeActionEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcChillerTypeEnum
{
  kIfcChillerTypeEnum_AIRCOOLED,
  kIfcChillerTypeEnum_WATERCOOLED,
  kIfcChillerTypeEnum_HEATRECOVERY,
  kIfcChillerTypeEnum_USERDEFINED,
  kIfcChillerTypeEnum_NOTDEFINED,
  kIfcChillerTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcChillerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcChillerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcChillerTypeEnum& getUnset<OdIfc2x2_final::IfcChillerTypeEnum>() { static OdIfc2x2_final::IfcChillerTypeEnum nullEnum = OdIfc2x2_final::kIfcChillerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcCoilTypeEnum
{
  kIfcCoilTypeEnum_DXCOOLINGCOIL,
  kIfcCoilTypeEnum_WATERCOOLINGCOIL,
  kIfcCoilTypeEnum_STEAMHEATINGCOIL,
  kIfcCoilTypeEnum_WATERHEATINGCOIL,
  kIfcCoilTypeEnum_ELECTRICHEATINGCOIL,
  kIfcCoilTypeEnum_GASHEATINGCOIL,
  kIfcCoilTypeEnum_USERDEFINED,
  kIfcCoilTypeEnum_NOTDEFINED,
  kIfcCoilTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcCoilTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCoilTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcCoilTypeEnum& getUnset<OdIfc2x2_final::IfcCoilTypeEnum>() { static OdIfc2x2_final::IfcCoilTypeEnum nullEnum = OdIfc2x2_final::kIfcCoilTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcColumnTypeEnum
{
  kIfcColumnTypeEnum_COLUMN,
  kIfcColumnTypeEnum_USERDEFINED,
  kIfcColumnTypeEnum_NOTDEFINED,
  kIfcColumnTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcColumnTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcColumnTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcColumnTypeEnum& getUnset<OdIfc2x2_final::IfcColumnTypeEnum>() { static OdIfc2x2_final::IfcColumnTypeEnum nullEnum = OdIfc2x2_final::kIfcColumnTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcCompressorTypeEnum
{
  kIfcCompressorTypeEnum_DYNAMIC,
  kIfcCompressorTypeEnum_RECIPROCATING,
  kIfcCompressorTypeEnum_ROTARY,
  kIfcCompressorTypeEnum_SCROLL,
  kIfcCompressorTypeEnum_TROCHOIDAL,
  kIfcCompressorTypeEnum_SINGLESTAGE,
  kIfcCompressorTypeEnum_BOOSTER,
  kIfcCompressorTypeEnum_OPENTYPE,
  kIfcCompressorTypeEnum_HERMETIC,
  kIfcCompressorTypeEnum_SEMIHERMETIC,
  kIfcCompressorTypeEnum_WELDEDSHELLHERMETIC,
  kIfcCompressorTypeEnum_ROLLINGPISTON,
  kIfcCompressorTypeEnum_ROTARYVANE,
  kIfcCompressorTypeEnum_SINGLESCREW,
  kIfcCompressorTypeEnum_TWINSCREW,
  kIfcCompressorTypeEnum_USERDEFINED,
  kIfcCompressorTypeEnum_NOTDEFINED,
  kIfcCompressorTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcCompressorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCompressorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcCompressorTypeEnum& getUnset<OdIfc2x2_final::IfcCompressorTypeEnum>() { static OdIfc2x2_final::IfcCompressorTypeEnum nullEnum = OdIfc2x2_final::kIfcCompressorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcCondenserTypeEnum
{
  kIfcCondenserTypeEnum_WATERCOOLEDSHELLTUBE,
  kIfcCondenserTypeEnum_WATERCOOLEDSHELLCOIL,
  kIfcCondenserTypeEnum_WATERCOOLEDTUBEINTUBE,
  kIfcCondenserTypeEnum_WATERCOOLEDBRAZEDPLATE,
  kIfcCondenserTypeEnum_AIRCOOLED,
  kIfcCondenserTypeEnum_EVAPORATIVECOOLED,
  kIfcCondenserTypeEnum_USERDEFINED,
  kIfcCondenserTypeEnum_NOTDEFINED,
  kIfcCondenserTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcCondenserTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCondenserTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcCondenserTypeEnum& getUnset<OdIfc2x2_final::IfcCondenserTypeEnum>() { static OdIfc2x2_final::IfcCondenserTypeEnum nullEnum = OdIfc2x2_final::kIfcCondenserTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcConnectionTypeEnum
{
  kIfcConnectionTypeEnum_ATPATH,
  kIfcConnectionTypeEnum_ATSTART,
  kIfcConnectionTypeEnum_ATEND,
  kIfcConnectionTypeEnum_NOTDEFINED,
  kIfcConnectionTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcConnectionTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcConnectionTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcConnectionTypeEnum& getUnset<OdIfc2x2_final::IfcConnectionTypeEnum>() { static OdIfc2x2_final::IfcConnectionTypeEnum nullEnum = OdIfc2x2_final::kIfcConnectionTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcConstraintEnum
{
  kIfcConstraintEnum_HARD,
  kIfcConstraintEnum_SOFT,
  kIfcConstraintEnum_ADVISORY,
  kIfcConstraintEnum_USERDEFINED,
  kIfcConstraintEnum_NOTDEFINED,
  kIfcConstraintEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcConstraintEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcConstraintEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcConstraintEnum& getUnset<OdIfc2x2_final::IfcConstraintEnum>() { static OdIfc2x2_final::IfcConstraintEnum nullEnum = OdIfc2x2_final::kIfcConstraintEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcControllerTypeEnum
{
  kIfcControllerTypeEnum_FLOATING,
  kIfcControllerTypeEnum_PROPORTIONAL,
  kIfcControllerTypeEnum_PROPORTIONALINTEGRAL,
  kIfcControllerTypeEnum_PROPORTIONALINTEGRALDERIVATIVE,
  kIfcControllerTypeEnum_TIMEDTWOPOSITION,
  kIfcControllerTypeEnum_TWOPOSITION,
  kIfcControllerTypeEnum_USERDEFINED,
  kIfcControllerTypeEnum_NOTDEFINED,
  kIfcControllerTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcControllerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcControllerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcControllerTypeEnum& getUnset<OdIfc2x2_final::IfcControllerTypeEnum>() { static OdIfc2x2_final::IfcControllerTypeEnum nullEnum = OdIfc2x2_final::kIfcControllerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcCooledBeamTypeEnum
{
  kIfcCooledBeamTypeEnum_ACTIVE,
  kIfcCooledBeamTypeEnum_PASSIVE,
  kIfcCooledBeamTypeEnum_USERDEFINED,
  kIfcCooledBeamTypeEnum_NOTDEFINED,
  kIfcCooledBeamTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcCooledBeamTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCooledBeamTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcCooledBeamTypeEnum& getUnset<OdIfc2x2_final::IfcCooledBeamTypeEnum>() { static OdIfc2x2_final::IfcCooledBeamTypeEnum nullEnum = OdIfc2x2_final::kIfcCooledBeamTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcCoolingTowerTypeEnum
{
  kIfcCoolingTowerTypeEnum_NATURALDRAFT,
  kIfcCoolingTowerTypeEnum_MECHANICALINDUCEDDRAFT,
  kIfcCoolingTowerTypeEnum_MECHANICALFORCEDDRAFT,
  kIfcCoolingTowerTypeEnum_USERDEFINED,
  kIfcCoolingTowerTypeEnum_NOTDEFINED,
  kIfcCoolingTowerTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcCoolingTowerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCoolingTowerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcCoolingTowerTypeEnum& getUnset<OdIfc2x2_final::IfcCoolingTowerTypeEnum>() { static OdIfc2x2_final::IfcCoolingTowerTypeEnum nullEnum = OdIfc2x2_final::kIfcCoolingTowerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcCostScheduleTypeEnum
{
  kIfcCostScheduleTypeEnum_BUDGET,
  kIfcCostScheduleTypeEnum_COSTPLAN,
  kIfcCostScheduleTypeEnum_ESTIMATE,
  kIfcCostScheduleTypeEnum_TENDER,
  kIfcCostScheduleTypeEnum_PRICEDBILLOFQUANTITIES,
  kIfcCostScheduleTypeEnum_UNPRICEDBILLOFQUANTITIES,
  kIfcCostScheduleTypeEnum_SCHEDULEOFRATES,
  kIfcCostScheduleTypeEnum_USERDEFINED,
  kIfcCostScheduleTypeEnum_NOTDEFINED,
  kIfcCostScheduleTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcCostScheduleTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCostScheduleTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcCostScheduleTypeEnum& getUnset<OdIfc2x2_final::IfcCostScheduleTypeEnum>() { static OdIfc2x2_final::IfcCostScheduleTypeEnum nullEnum = OdIfc2x2_final::kIfcCostScheduleTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcCoveringTypeEnum
{
  kIfcCoveringTypeEnum_CEILING,
  kIfcCoveringTypeEnum_FLOORING,
  kIfcCoveringTypeEnum_CLADDING,
  kIfcCoveringTypeEnum_ROOFING,
  kIfcCoveringTypeEnum_INSULATION,
  kIfcCoveringTypeEnum_MEMBRANE,
  kIfcCoveringTypeEnum_SLEEVING,
  kIfcCoveringTypeEnum_WRAPPING,
  kIfcCoveringTypeEnum_USERDEFINED,
  kIfcCoveringTypeEnum_NOTDEFINED,
  kIfcCoveringTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcCoveringTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCoveringTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcCoveringTypeEnum& getUnset<OdIfc2x2_final::IfcCoveringTypeEnum>() { static OdIfc2x2_final::IfcCoveringTypeEnum nullEnum = OdIfc2x2_final::kIfcCoveringTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcCurrencyEnum
{
  kIfcCurrencyEnum_AED,
  kIfcCurrencyEnum_AES,
  kIfcCurrencyEnum_ATS,
  kIfcCurrencyEnum_AUD,
  kIfcCurrencyEnum_BBD,
  kIfcCurrencyEnum_BEG,
  kIfcCurrencyEnum_BGL,
  kIfcCurrencyEnum_BHD,
  kIfcCurrencyEnum_BMD,
  kIfcCurrencyEnum_BND,
  kIfcCurrencyEnum_BRL,
  kIfcCurrencyEnum_BSD,
  kIfcCurrencyEnum_BWP,
  kIfcCurrencyEnum_BZD,
  kIfcCurrencyEnum_CAD,
  kIfcCurrencyEnum_CBD,
  kIfcCurrencyEnum_CHF,
  kIfcCurrencyEnum_CLP,
  kIfcCurrencyEnum_CNY,
  kIfcCurrencyEnum_CYS,
  kIfcCurrencyEnum_CZK,
  kIfcCurrencyEnum_DDP,
  kIfcCurrencyEnum_DEM,
  kIfcCurrencyEnum_DKK,
  kIfcCurrencyEnum_EGL,
  kIfcCurrencyEnum_EST,
  kIfcCurrencyEnum_EUR,
  kIfcCurrencyEnum_FAK,
  kIfcCurrencyEnum_FIM,
  kIfcCurrencyEnum_FJD,
  kIfcCurrencyEnum_FKP,
  kIfcCurrencyEnum_FRF,
  kIfcCurrencyEnum_GBP,
  kIfcCurrencyEnum_GIP,
  kIfcCurrencyEnum_GMD,
  kIfcCurrencyEnum_GRX,
  kIfcCurrencyEnum_HKD,
  kIfcCurrencyEnum_HUF,
  kIfcCurrencyEnum_ICK,
  kIfcCurrencyEnum_IDR,
  kIfcCurrencyEnum_ILS,
  kIfcCurrencyEnum_INR,
  kIfcCurrencyEnum_IRP,
  kIfcCurrencyEnum_ITL,
  kIfcCurrencyEnum_JMD,
  kIfcCurrencyEnum_JOD,
  kIfcCurrencyEnum_JPY,
  kIfcCurrencyEnum_KES,
  kIfcCurrencyEnum_KRW,
  kIfcCurrencyEnum_KWD,
  kIfcCurrencyEnum_KYD,
  kIfcCurrencyEnum_LKR,
  kIfcCurrencyEnum_LUF,
  kIfcCurrencyEnum_MTL,
  kIfcCurrencyEnum_MUR,
  kIfcCurrencyEnum_MXN,
  kIfcCurrencyEnum_MYR,
  kIfcCurrencyEnum_NLG,
  kIfcCurrencyEnum_NZD,
  kIfcCurrencyEnum_OMR,
  kIfcCurrencyEnum_PGK,
  kIfcCurrencyEnum_PHP,
  kIfcCurrencyEnum_PKR,
  kIfcCurrencyEnum_PLN,
  kIfcCurrencyEnum_PTN,
  kIfcCurrencyEnum_QAR,
  kIfcCurrencyEnum_RUR,
  kIfcCurrencyEnum_SAR,
  kIfcCurrencyEnum_SCR,
  kIfcCurrencyEnum_SEK,
  kIfcCurrencyEnum_SGD,
  kIfcCurrencyEnum_SKP,
  kIfcCurrencyEnum_THB,
  kIfcCurrencyEnum_TRL,
  kIfcCurrencyEnum_TTD,
  kIfcCurrencyEnum_TWD,
  kIfcCurrencyEnum_USD,
  kIfcCurrencyEnum_VEB,
  kIfcCurrencyEnum_VND,
  kIfcCurrencyEnum_XEU,
  kIfcCurrencyEnum_ZAR,
  kIfcCurrencyEnum_ZWD,
  kIfcCurrencyEnum_NOK,
  kIfcCurrencyEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcCurrencyEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCurrencyEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcCurrencyEnum& getUnset<OdIfc2x2_final::IfcCurrencyEnum>() { static OdIfc2x2_final::IfcCurrencyEnum nullEnum = OdIfc2x2_final::kIfcCurrencyEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcDamperTypeEnum
{
  kIfcDamperTypeEnum_CONTROLDAMPER,
  kIfcDamperTypeEnum_FIREDAMPER,
  kIfcDamperTypeEnum_SMOKEDAMPER,
  kIfcDamperTypeEnum_FIRESMOKEDAMPER,
  kIfcDamperTypeEnum_BACKDRAFTDAMPER,
  kIfcDamperTypeEnum_RELIEFDAMPER,
  kIfcDamperTypeEnum_BLASTDAMPER,
  kIfcDamperTypeEnum_GRAVITYDAMPER,
  kIfcDamperTypeEnum_GRAVITYRELIEFDAMPER,
  kIfcDamperTypeEnum_BALANCINGDAMPER,
  kIfcDamperTypeEnum_FUMEHOODEXHAUST,
  kIfcDamperTypeEnum_USERDEFINED,
  kIfcDamperTypeEnum_NOTDEFINED,
  kIfcDamperTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcDamperTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDamperTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcDamperTypeEnum& getUnset<OdIfc2x2_final::IfcDamperTypeEnum>() { static OdIfc2x2_final::IfcDamperTypeEnum nullEnum = OdIfc2x2_final::kIfcDamperTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcDataOriginEnum
{
  kIfcDataOriginEnum_MEASURED,
  kIfcDataOriginEnum_PREDICTED,
  kIfcDataOriginEnum_SIMULATED,
  kIfcDataOriginEnum_USERDEFINED,
  kIfcDataOriginEnum_NOTDEFINED,
  kIfcDataOriginEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcDataOriginEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDataOriginEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcDataOriginEnum& getUnset<OdIfc2x2_final::IfcDataOriginEnum>() { static OdIfc2x2_final::IfcDataOriginEnum nullEnum = OdIfc2x2_final::kIfcDataOriginEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcDerivedUnitEnum
{
  kIfcDerivedUnitEnum_ANGULARVELOCITYUNIT,
  kIfcDerivedUnitEnum_COMPOUNDPLANEANGLEUNIT,
  kIfcDerivedUnitEnum_DYNAMICVISCOSITYUNIT,
  kIfcDerivedUnitEnum_HEATFLUXDENSITYUNIT,
  kIfcDerivedUnitEnum_INTEGERCOUNTRATEUNIT,
  kIfcDerivedUnitEnum_ISOTHERMALMOISTURECAPACITYUNIT,
  kIfcDerivedUnitEnum_KINEMATICVISCOSITYUNIT,
  kIfcDerivedUnitEnum_LINEARVELOCITYUNIT,
  kIfcDerivedUnitEnum_MASSDENSITYUNIT,
  kIfcDerivedUnitEnum_MASSFLOWRATEUNIT,
  kIfcDerivedUnitEnum_MOISTUREDIFFUSIVITYUNIT,
  kIfcDerivedUnitEnum_MOLECULARWEIGHTUNIT,
  kIfcDerivedUnitEnum_SPECIFICHEATCAPACITYUNIT,
  kIfcDerivedUnitEnum_THERMALADMITTANCEUNIT,
  kIfcDerivedUnitEnum_THERMALCONDUCTANCEUNIT,
  kIfcDerivedUnitEnum_THERMALRESISTANCEUNIT,
  kIfcDerivedUnitEnum_THERMALTRANSMITTANCEUNIT,
  kIfcDerivedUnitEnum_VAPORPERMEABILITYUNIT,
  kIfcDerivedUnitEnum_VOLUMETRICFLOWRATEUNIT,
  kIfcDerivedUnitEnum_ROTATIONALFREQUENCYUNIT,
  kIfcDerivedUnitEnum_TORQUEUNIT,
  kIfcDerivedUnitEnum_MOMENTOFINERTIAUNIT,
  kIfcDerivedUnitEnum_LINEARMOMENTUNIT,
  kIfcDerivedUnitEnum_LINEARFORCEUNIT,
  kIfcDerivedUnitEnum_PLANARFORCEUNIT,
  kIfcDerivedUnitEnum_MODULUSOFELASTICITYUNIT,
  kIfcDerivedUnitEnum_SHEARMODULUSUNIT,
  kIfcDerivedUnitEnum_LINEARSTIFFNESSUNIT,
  kIfcDerivedUnitEnum_ROTATIONALSTIFFNESSUNIT,
  kIfcDerivedUnitEnum_MODULUSOFSUBGRADEREACTIONUNIT,
  kIfcDerivedUnitEnum_ACCELERATIONUNIT,
  kIfcDerivedUnitEnum_CURVATUREUNIT,
  kIfcDerivedUnitEnum_HEATINGVALUEUNIT,
  kIfcDerivedUnitEnum_IONCONCENTRATIONUNIT,
  kIfcDerivedUnitEnum_LUMINOUSINTENSITYDISTRIBUTIONUNIT,
  kIfcDerivedUnitEnum_MASSPERLENGTHUNIT,
  kIfcDerivedUnitEnum_MODULUSOFLINEARSUBGRADEREACTIONUNIT,
  kIfcDerivedUnitEnum_MODULUSOFROTATIONALSUBGRADEREACTIONUNIT,
  kIfcDerivedUnitEnum_PHUNIT,
  kIfcDerivedUnitEnum_ROTATIONALMASSUNIT,
  kIfcDerivedUnitEnum_SECTIONAREAINTEGRALUNIT,
  kIfcDerivedUnitEnum_SECTIONMODULUSUNIT,
  kIfcDerivedUnitEnum_SOUNDPOWERUNIT,
  kIfcDerivedUnitEnum_SOUNDPRESSUREUNIT,
  kIfcDerivedUnitEnum_TEMPERATUREGRADIENTUNIT,
  kIfcDerivedUnitEnum_THERMALEXPANSIONCOEFFICIENTUNIT,
  kIfcDerivedUnitEnum_WARPINGCONSTANTUNIT,
  kIfcDerivedUnitEnum_WARPINGMOMENTUNIT,
  kIfcDerivedUnitEnum_USERDEFINED,
  kIfcDerivedUnitEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcDerivedUnitEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDerivedUnitEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcDerivedUnitEnum& getUnset<OdIfc2x2_final::IfcDerivedUnitEnum>() { static OdIfc2x2_final::IfcDerivedUnitEnum nullEnum = OdIfc2x2_final::kIfcDerivedUnitEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcDimensionExtentUsage
{
  kIfcDimensionExtentUsage_ORIGIN,
  kIfcDimensionExtentUsage_TARGET,
  kIfcDimensionExtentUsage_unset
};

class IFC2X2_FINAL_EXPORT IfcDimensionExtentUsageTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDimensionExtentUsageTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcDimensionExtentUsage& getUnset<OdIfc2x2_final::IfcDimensionExtentUsage>() { static OdIfc2x2_final::IfcDimensionExtentUsage nullEnum = OdIfc2x2_final::kIfcDimensionExtentUsage_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcDirectionSenseEnum
{
  kIfcDirectionSenseEnum_POSITIVE,
  kIfcDirectionSenseEnum_NEGATIVE,
  kIfcDirectionSenseEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcDirectionSenseEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDirectionSenseEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcDirectionSenseEnum& getUnset<OdIfc2x2_final::IfcDirectionSenseEnum>() { static OdIfc2x2_final::IfcDirectionSenseEnum nullEnum = OdIfc2x2_final::kIfcDirectionSenseEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcDistributionChamberElementTypeEnum
{
  kIfcDistributionChamberElementTypeEnum_FORMEDDUCT,
  kIfcDistributionChamberElementTypeEnum_INSPECTIONCHAMBER,
  kIfcDistributionChamberElementTypeEnum_INSPECTIONPIT,
  kIfcDistributionChamberElementTypeEnum_MANHOLE,
  kIfcDistributionChamberElementTypeEnum_METERCHAMBER,
  kIfcDistributionChamberElementTypeEnum_SUMP,
  kIfcDistributionChamberElementTypeEnum_TRENCH,
  kIfcDistributionChamberElementTypeEnum_VALVECHAMBER,
  kIfcDistributionChamberElementTypeEnum_USERDEFINED,
  kIfcDistributionChamberElementTypeEnum_NOTDEFINED,
  kIfcDistributionChamberElementTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcDistributionChamberElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDistributionChamberElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcDistributionChamberElementTypeEnum& getUnset<OdIfc2x2_final::IfcDistributionChamberElementTypeEnum>() { static OdIfc2x2_final::IfcDistributionChamberElementTypeEnum nullEnum = OdIfc2x2_final::kIfcDistributionChamberElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcDocumentConfidentialityEnum
{
  kIfcDocumentConfidentialityEnum_PUBLIC,
  kIfcDocumentConfidentialityEnum_RESTRICTED,
  kIfcDocumentConfidentialityEnum_CONFIDENTIAL,
  kIfcDocumentConfidentialityEnum_PERSONAL,
  kIfcDocumentConfidentialityEnum_USERDEFINED,
  kIfcDocumentConfidentialityEnum_NOTDEFINED,
  kIfcDocumentConfidentialityEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcDocumentConfidentialityEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDocumentConfidentialityEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcDocumentConfidentialityEnum& getUnset<OdIfc2x2_final::IfcDocumentConfidentialityEnum>() { static OdIfc2x2_final::IfcDocumentConfidentialityEnum nullEnum = OdIfc2x2_final::kIfcDocumentConfidentialityEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcDocumentStatusEnum
{
  kIfcDocumentStatusEnum_DRAFT,
  kIfcDocumentStatusEnum_FINALDRAFT,
  kIfcDocumentStatusEnum_FINAL,
  kIfcDocumentStatusEnum_REVISION,
  kIfcDocumentStatusEnum_NOTDEFINED,
  kIfcDocumentStatusEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcDocumentStatusEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDocumentStatusEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcDocumentStatusEnum& getUnset<OdIfc2x2_final::IfcDocumentStatusEnum>() { static OdIfc2x2_final::IfcDocumentStatusEnum nullEnum = OdIfc2x2_final::kIfcDocumentStatusEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcDoorPanelOperationEnum
{
  kIfcDoorPanelOperationEnum_SWINGING,
  kIfcDoorPanelOperationEnum_DOUBLE_ACTING,
  kIfcDoorPanelOperationEnum_SLIDING,
  kIfcDoorPanelOperationEnum_FOLDING,
  kIfcDoorPanelOperationEnum_REVOLVING,
  kIfcDoorPanelOperationEnum_ROLLINGUP,
  kIfcDoorPanelOperationEnum_USERDEFINED,
  kIfcDoorPanelOperationEnum_NOTDEFINED,
  kIfcDoorPanelOperationEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcDoorPanelOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorPanelOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcDoorPanelOperationEnum& getUnset<OdIfc2x2_final::IfcDoorPanelOperationEnum>() { static OdIfc2x2_final::IfcDoorPanelOperationEnum nullEnum = OdIfc2x2_final::kIfcDoorPanelOperationEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcDoorPanelPositionEnum
{
  kIfcDoorPanelPositionEnum_LEFT,
  kIfcDoorPanelPositionEnum_MIDDLE,
  kIfcDoorPanelPositionEnum_RIGHT,
  kIfcDoorPanelPositionEnum_NOTDEFINED,
  kIfcDoorPanelPositionEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcDoorPanelPositionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorPanelPositionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcDoorPanelPositionEnum& getUnset<OdIfc2x2_final::IfcDoorPanelPositionEnum>() { static OdIfc2x2_final::IfcDoorPanelPositionEnum nullEnum = OdIfc2x2_final::kIfcDoorPanelPositionEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcDoorStyleConstructionEnum
{
  kIfcDoorStyleConstructionEnum_ALUMINIUM,
  kIfcDoorStyleConstructionEnum_HIGH_GRADE_STEEL,
  kIfcDoorStyleConstructionEnum_STEEL,
  kIfcDoorStyleConstructionEnum_WOOD,
  kIfcDoorStyleConstructionEnum_ALUMINIUM_WOOD,
  kIfcDoorStyleConstructionEnum_ALUMINIUM_PLASTIC,
  kIfcDoorStyleConstructionEnum_PLASTIC,
  kIfcDoorStyleConstructionEnum_USERDEFINED,
  kIfcDoorStyleConstructionEnum_NOTDEFINED,
  kIfcDoorStyleConstructionEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcDoorStyleConstructionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorStyleConstructionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcDoorStyleConstructionEnum& getUnset<OdIfc2x2_final::IfcDoorStyleConstructionEnum>() { static OdIfc2x2_final::IfcDoorStyleConstructionEnum nullEnum = OdIfc2x2_final::kIfcDoorStyleConstructionEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcDoorStyleOperationEnum
{
  kIfcDoorStyleOperationEnum_SINGLE_SWING_LEFT,
  kIfcDoorStyleOperationEnum_SINGLE_SWING_RIGHT,
  kIfcDoorStyleOperationEnum_DOUBLE_DOOR_SINGLE_SWING,
  kIfcDoorStyleOperationEnum_DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_LEFT,
  kIfcDoorStyleOperationEnum_DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_RIGHT,
  kIfcDoorStyleOperationEnum_DOUBLE_SWING_LEFT,
  kIfcDoorStyleOperationEnum_DOUBLE_SWING_RIGHT,
  kIfcDoorStyleOperationEnum_DOUBLE_DOOR_DOUBLE_SWING,
  kIfcDoorStyleOperationEnum_SLIDING_TO_LEFT,
  kIfcDoorStyleOperationEnum_SLIDING_TO_RIGHT,
  kIfcDoorStyleOperationEnum_DOUBLE_DOOR_SLIDING,
  kIfcDoorStyleOperationEnum_FOLDING_TO_LEFT,
  kIfcDoorStyleOperationEnum_FOLDING_TO_RIGHT,
  kIfcDoorStyleOperationEnum_DOUBLE_DOOR_FOLDING,
  kIfcDoorStyleOperationEnum_REVOLVING,
  kIfcDoorStyleOperationEnum_ROLLINGUP,
  kIfcDoorStyleOperationEnum_USERDEFINED,
  kIfcDoorStyleOperationEnum_NOTDEFINED,
  kIfcDoorStyleOperationEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcDoorStyleOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorStyleOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcDoorStyleOperationEnum& getUnset<OdIfc2x2_final::IfcDoorStyleOperationEnum>() { static OdIfc2x2_final::IfcDoorStyleOperationEnum nullEnum = OdIfc2x2_final::kIfcDoorStyleOperationEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcDuctFittingTypeEnum
{
  kIfcDuctFittingTypeEnum_BEND,
  kIfcDuctFittingTypeEnum_CONNECTOR,
  kIfcDuctFittingTypeEnum_ENTRY,
  kIfcDuctFittingTypeEnum_EXIT,
  kIfcDuctFittingTypeEnum_JUNCTION,
  kIfcDuctFittingTypeEnum_OBSTRUCTION,
  kIfcDuctFittingTypeEnum_TRANSITION,
  kIfcDuctFittingTypeEnum_USERDEFINED,
  kIfcDuctFittingTypeEnum_NOTDEFINED,
  kIfcDuctFittingTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcDuctFittingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDuctFittingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcDuctFittingTypeEnum& getUnset<OdIfc2x2_final::IfcDuctFittingTypeEnum>() { static OdIfc2x2_final::IfcDuctFittingTypeEnum nullEnum = OdIfc2x2_final::kIfcDuctFittingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcDuctSegmentTypeEnum
{
  kIfcDuctSegmentTypeEnum_RIGIDSEGMENT,
  kIfcDuctSegmentTypeEnum_FLEXIBLESEGMENT,
  kIfcDuctSegmentTypeEnum_USERDEFINED,
  kIfcDuctSegmentTypeEnum_NOTDEFINED,
  kIfcDuctSegmentTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcDuctSegmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDuctSegmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcDuctSegmentTypeEnum& getUnset<OdIfc2x2_final::IfcDuctSegmentTypeEnum>() { static OdIfc2x2_final::IfcDuctSegmentTypeEnum nullEnum = OdIfc2x2_final::kIfcDuctSegmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcDuctSilencerTypeEnum
{
  kIfcDuctSilencerTypeEnum_FLATOVAL,
  kIfcDuctSilencerTypeEnum_RECTANGULAR,
  kIfcDuctSilencerTypeEnum_ROUND,
  kIfcDuctSilencerTypeEnum_USERDEFINED,
  kIfcDuctSilencerTypeEnum_NOTDEFINED,
  kIfcDuctSilencerTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcDuctSilencerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDuctSilencerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcDuctSilencerTypeEnum& getUnset<OdIfc2x2_final::IfcDuctSilencerTypeEnum>() { static OdIfc2x2_final::IfcDuctSilencerTypeEnum nullEnum = OdIfc2x2_final::kIfcDuctSilencerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcElectricApplianceTypeEnum
{
  kIfcElectricApplianceTypeEnum_COMPUTER,
  kIfcElectricApplianceTypeEnum_DIRECTWATERHEATER,
  kIfcElectricApplianceTypeEnum_DISHWASHER,
  kIfcElectricApplianceTypeEnum_ELECTRICCOOKER,
  kIfcElectricApplianceTypeEnum_ELECTRICHEATER,
  kIfcElectricApplianceTypeEnum_FACSIMILE,
  kIfcElectricApplianceTypeEnum_FREESTANDINGFAN,
  kIfcElectricApplianceTypeEnum_FREEZER,
  kIfcElectricApplianceTypeEnum_FRIDGE_FREEZER,
  kIfcElectricApplianceTypeEnum_HANDDRYER,
  kIfcElectricApplianceTypeEnum_INDIRECTWATERHEATER,
  kIfcElectricApplianceTypeEnum_MICROWAVE,
  kIfcElectricApplianceTypeEnum_PHOTOCOPIER,
  kIfcElectricApplianceTypeEnum_PRINTER,
  kIfcElectricApplianceTypeEnum_REFRIGERATOR,
  kIfcElectricApplianceTypeEnum_RADIANTHEATER,
  kIfcElectricApplianceTypeEnum_SCANNER,
  kIfcElectricApplianceTypeEnum_TELEPHONE,
  kIfcElectricApplianceTypeEnum_TUMBLEDRYER,
  kIfcElectricApplianceTypeEnum_TV,
  kIfcElectricApplianceTypeEnum_VENDINGMACHINE,
  kIfcElectricApplianceTypeEnum_WASHINGMACHINE,
  kIfcElectricApplianceTypeEnum_WATERHEATER,
  kIfcElectricApplianceTypeEnum_WATERCOOLER,
  kIfcElectricApplianceTypeEnum_USERDEFINED,
  kIfcElectricApplianceTypeEnum_NOTDEFINED,
  kIfcElectricApplianceTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcElectricApplianceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricApplianceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcElectricApplianceTypeEnum& getUnset<OdIfc2x2_final::IfcElectricApplianceTypeEnum>() { static OdIfc2x2_final::IfcElectricApplianceTypeEnum nullEnum = OdIfc2x2_final::kIfcElectricApplianceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcElectricCurrentEnum
{
  kIfcElectricCurrentEnum_ALTERNATING,
  kIfcElectricCurrentEnum_DIRECT,
  kIfcElectricCurrentEnum_NOTDEFINED,
  kIfcElectricCurrentEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcElectricCurrentEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricCurrentEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcElectricCurrentEnum& getUnset<OdIfc2x2_final::IfcElectricCurrentEnum>() { static OdIfc2x2_final::IfcElectricCurrentEnum nullEnum = OdIfc2x2_final::kIfcElectricCurrentEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcElectricDistributionPointFunctionEnum
{
  kIfcElectricDistributionPointFunctionEnum_ALARMPANEL,
  kIfcElectricDistributionPointFunctionEnum_CONSUMERUNIT,
  kIfcElectricDistributionPointFunctionEnum_CONTROLPANEL,
  kIfcElectricDistributionPointFunctionEnum_DISTRIBUTIONBOARD,
  kIfcElectricDistributionPointFunctionEnum_GASDETECTORPANEL,
  kIfcElectricDistributionPointFunctionEnum_INDICATORPANEL,
  kIfcElectricDistributionPointFunctionEnum_MIMICPANEL,
  kIfcElectricDistributionPointFunctionEnum_MOTORCONTROLCENTRE,
  kIfcElectricDistributionPointFunctionEnum_SWITCHBOARD,
  kIfcElectricDistributionPointFunctionEnum_USERDEFINED,
  kIfcElectricDistributionPointFunctionEnum_NOTDEFINED,
  kIfcElectricDistributionPointFunctionEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcElectricDistributionPointFunctionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricDistributionPointFunctionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcElectricDistributionPointFunctionEnum& getUnset<OdIfc2x2_final::IfcElectricDistributionPointFunctionEnum>() { static OdIfc2x2_final::IfcElectricDistributionPointFunctionEnum nullEnum = OdIfc2x2_final::kIfcElectricDistributionPointFunctionEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcElectricFlowStorageDeviceTypeEnum
{
  kIfcElectricFlowStorageDeviceTypeEnum_BATTERY,
  kIfcElectricFlowStorageDeviceTypeEnum_CAPACITORBANK,
  kIfcElectricFlowStorageDeviceTypeEnum_HARMONICFILTER,
  kIfcElectricFlowStorageDeviceTypeEnum_INDUCTORBANK,
  kIfcElectricFlowStorageDeviceTypeEnum_UPS,
  kIfcElectricFlowStorageDeviceTypeEnum_USERDEFINED,
  kIfcElectricFlowStorageDeviceTypeEnum_NOTDEFINED,
  kIfcElectricFlowStorageDeviceTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcElectricFlowStorageDeviceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricFlowStorageDeviceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcElectricFlowStorageDeviceTypeEnum& getUnset<OdIfc2x2_final::IfcElectricFlowStorageDeviceTypeEnum>() { static OdIfc2x2_final::IfcElectricFlowStorageDeviceTypeEnum nullEnum = OdIfc2x2_final::kIfcElectricFlowStorageDeviceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcElectricGeneratorTypeEnum
{
  kIfcElectricGeneratorTypeEnum_USERDEFINED,
  kIfcElectricGeneratorTypeEnum_NOTDEFINED,
  kIfcElectricGeneratorTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcElectricGeneratorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricGeneratorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcElectricGeneratorTypeEnum& getUnset<OdIfc2x2_final::IfcElectricGeneratorTypeEnum>() { static OdIfc2x2_final::IfcElectricGeneratorTypeEnum nullEnum = OdIfc2x2_final::kIfcElectricGeneratorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcElectricHeaterTypeEnum
{
  kIfcElectricHeaterTypeEnum_ELECTRICPOINTHEATER,
  kIfcElectricHeaterTypeEnum_ELECTRICCABLEHEATER,
  kIfcElectricHeaterTypeEnum_ELECTRICMATHEATER,
  kIfcElectricHeaterTypeEnum_USERDEFINED,
  kIfcElectricHeaterTypeEnum_NOTDEFINED,
  kIfcElectricHeaterTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcElectricHeaterTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricHeaterTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcElectricHeaterTypeEnum& getUnset<OdIfc2x2_final::IfcElectricHeaterTypeEnum>() { static OdIfc2x2_final::IfcElectricHeaterTypeEnum nullEnum = OdIfc2x2_final::kIfcElectricHeaterTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcElectricMotorTypeEnum
{
  kIfcElectricMotorTypeEnum_DC,
  kIfcElectricMotorTypeEnum_INDUCTION,
  kIfcElectricMotorTypeEnum_POLYPHASE,
  kIfcElectricMotorTypeEnum_RELUCTANCESYNCHRONOUS,
  kIfcElectricMotorTypeEnum_SYNCHRONOUS,
  kIfcElectricMotorTypeEnum_USERDEFINED,
  kIfcElectricMotorTypeEnum_NOTDEFINED,
  kIfcElectricMotorTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcElectricMotorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricMotorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcElectricMotorTypeEnum& getUnset<OdIfc2x2_final::IfcElectricMotorTypeEnum>() { static OdIfc2x2_final::IfcElectricMotorTypeEnum nullEnum = OdIfc2x2_final::kIfcElectricMotorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcElectricTimeControlTypeEnum
{
  kIfcElectricTimeControlTypeEnum_TIMECLOCK,
  kIfcElectricTimeControlTypeEnum_TIMEDELAY,
  kIfcElectricTimeControlTypeEnum_RELAY,
  kIfcElectricTimeControlTypeEnum_USERDEFINED,
  kIfcElectricTimeControlTypeEnum_NOTDEFINED,
  kIfcElectricTimeControlTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcElectricTimeControlTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricTimeControlTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcElectricTimeControlTypeEnum& getUnset<OdIfc2x2_final::IfcElectricTimeControlTypeEnum>() { static OdIfc2x2_final::IfcElectricTimeControlTypeEnum nullEnum = OdIfc2x2_final::kIfcElectricTimeControlTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcElementAssemblyTypeEnum
{
  kIfcElementAssemblyTypeEnum_ACCESSORY_ASSEMBLY,
  kIfcElementAssemblyTypeEnum_ARCH,
  kIfcElementAssemblyTypeEnum_BEAM_GRID,
  kIfcElementAssemblyTypeEnum_BRACED_FRAME,
  kIfcElementAssemblyTypeEnum_GIRDER,
  kIfcElementAssemblyTypeEnum_REINFORCEMENT_UNIT,
  kIfcElementAssemblyTypeEnum_RIGID_FRAME,
  kIfcElementAssemblyTypeEnum_SLAB_FIELD,
  kIfcElementAssemblyTypeEnum_TRUSS,
  kIfcElementAssemblyTypeEnum_USERDEFINED,
  kIfcElementAssemblyTypeEnum_NOTDEFINED,
  kIfcElementAssemblyTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcElementAssemblyTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElementAssemblyTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcElementAssemblyTypeEnum& getUnset<OdIfc2x2_final::IfcElementAssemblyTypeEnum>() { static OdIfc2x2_final::IfcElementAssemblyTypeEnum nullEnum = OdIfc2x2_final::kIfcElementAssemblyTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcElementCompositionEnum
{
  kIfcElementCompositionEnum_COMPLEX,
  kIfcElementCompositionEnum_ELEMENT,
  kIfcElementCompositionEnum_PARTIAL,
  kIfcElementCompositionEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcElementCompositionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElementCompositionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcElementCompositionEnum& getUnset<OdIfc2x2_final::IfcElementCompositionEnum>() { static OdIfc2x2_final::IfcElementCompositionEnum nullEnum = OdIfc2x2_final::kIfcElementCompositionEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcEnergySequenceEnum
{
  kIfcEnergySequenceEnum_PRIMARY,
  kIfcEnergySequenceEnum_SECONDARY,
  kIfcEnergySequenceEnum_TERTIARY,
  kIfcEnergySequenceEnum_AUXILIARY,
  kIfcEnergySequenceEnum_USERDEFINED,
  kIfcEnergySequenceEnum_NOTDEFINED,
  kIfcEnergySequenceEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcEnergySequenceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcEnergySequenceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcEnergySequenceEnum& getUnset<OdIfc2x2_final::IfcEnergySequenceEnum>() { static OdIfc2x2_final::IfcEnergySequenceEnum nullEnum = OdIfc2x2_final::kIfcEnergySequenceEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcEnvironmentalImpactCategoryEnum
{
  kIfcEnvironmentalImpactCategoryEnum_COMBINEDVALUE,
  kIfcEnvironmentalImpactCategoryEnum_DISPOSAL,
  kIfcEnvironmentalImpactCategoryEnum_EXTRACTION,
  kIfcEnvironmentalImpactCategoryEnum_INSTALLATION,
  kIfcEnvironmentalImpactCategoryEnum_MANUFACTURE,
  kIfcEnvironmentalImpactCategoryEnum_TRANSPORTATION,
  kIfcEnvironmentalImpactCategoryEnum_USERDEFINED,
  kIfcEnvironmentalImpactCategoryEnum_NOTDEFINED,
  kIfcEnvironmentalImpactCategoryEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcEnvironmentalImpactCategoryEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcEnvironmentalImpactCategoryEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcEnvironmentalImpactCategoryEnum& getUnset<OdIfc2x2_final::IfcEnvironmentalImpactCategoryEnum>() { static OdIfc2x2_final::IfcEnvironmentalImpactCategoryEnum nullEnum = OdIfc2x2_final::kIfcEnvironmentalImpactCategoryEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcEvaporativeCoolerTypeEnum
{
  kIfcEvaporativeCoolerTypeEnum_DIRECTEVAPORATIVERANDOMMEDIAAIRCOOLER,
  kIfcEvaporativeCoolerTypeEnum_DIRECTEVAPORATIVERIGIDMEDIAAIRCOOLER,
  kIfcEvaporativeCoolerTypeEnum_DIRECTEVAPORATIVESLINGERSPACKAGEDAIRCOOLER,
  kIfcEvaporativeCoolerTypeEnum_DIRECTEVAPORATIVEPACKAGEDROTARYAIRCOOLER,
  kIfcEvaporativeCoolerTypeEnum_DIRECTEVAPORATIVEAIRWASHER,
  kIfcEvaporativeCoolerTypeEnum_INDIRECTEVAPORATIVEPACKAGEAIRCOOLER,
  kIfcEvaporativeCoolerTypeEnum_INDIRECTEVAPORATIVEWETCOIL,
  kIfcEvaporativeCoolerTypeEnum_INDIRECTEVAPORATIVECOOLINGTOWERORCOILCOOLER,
  kIfcEvaporativeCoolerTypeEnum_INDIRECTDIRECTCOMBINATION,
  kIfcEvaporativeCoolerTypeEnum_USERDEFINED,
  kIfcEvaporativeCoolerTypeEnum_NOTDEFINED,
  kIfcEvaporativeCoolerTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcEvaporativeCoolerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcEvaporativeCoolerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcEvaporativeCoolerTypeEnum& getUnset<OdIfc2x2_final::IfcEvaporativeCoolerTypeEnum>() { static OdIfc2x2_final::IfcEvaporativeCoolerTypeEnum nullEnum = OdIfc2x2_final::kIfcEvaporativeCoolerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcEvaporatorTypeEnum
{
  kIfcEvaporatorTypeEnum_DIRECTEXPANSIONSHELLANDTUBE,
  kIfcEvaporatorTypeEnum_DIRECTEXPANSIONTUBEINTUBE,
  kIfcEvaporatorTypeEnum_DIRECTEXPANSIONBRAZEDPLATE,
  kIfcEvaporatorTypeEnum_FLOODEDSHELLANDTUBE,
  kIfcEvaporatorTypeEnum_SHELLANDCOIL,
  kIfcEvaporatorTypeEnum_USERDEFINED,
  kIfcEvaporatorTypeEnum_NOTDEFINED,
  kIfcEvaporatorTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcEvaporatorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcEvaporatorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcEvaporatorTypeEnum& getUnset<OdIfc2x2_final::IfcEvaporatorTypeEnum>() { static OdIfc2x2_final::IfcEvaporatorTypeEnum nullEnum = OdIfc2x2_final::kIfcEvaporatorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcFanTypeEnum
{
  kIfcFanTypeEnum_CENTRIFUGALFORWARDCURVED,
  kIfcFanTypeEnum_CENTRIFUGALRADIAL,
  kIfcFanTypeEnum_CENTRIFUGALBACKWARDINCLINEDCURVED,
  kIfcFanTypeEnum_CENTRIFUGALAIRFOIL,
  kIfcFanTypeEnum_TUBEAXIAL,
  kIfcFanTypeEnum_VANEAXIAL,
  kIfcFanTypeEnum_PROPELLORAXIAL,
  kIfcFanTypeEnum_USERDEFINED,
  kIfcFanTypeEnum_NOTDEFINED,
  kIfcFanTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcFanTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFanTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcFanTypeEnum& getUnset<OdIfc2x2_final::IfcFanTypeEnum>() { static OdIfc2x2_final::IfcFanTypeEnum nullEnum = OdIfc2x2_final::kIfcFanTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcFilterTypeEnum
{
  kIfcFilterTypeEnum_AIRPARTICLEFILTER,
  kIfcFilterTypeEnum_ODORFILTER,
  kIfcFilterTypeEnum_OILFILTER,
  kIfcFilterTypeEnum_STRAINER,
  kIfcFilterTypeEnum_WATERFILTER,
  kIfcFilterTypeEnum_USERDEFINED,
  kIfcFilterTypeEnum_NOTDEFINED,
  kIfcFilterTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcFilterTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFilterTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcFilterTypeEnum& getUnset<OdIfc2x2_final::IfcFilterTypeEnum>() { static OdIfc2x2_final::IfcFilterTypeEnum nullEnum = OdIfc2x2_final::kIfcFilterTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcFireSuppressionTerminalTypeEnum
{
  kIfcFireSuppressionTerminalTypeEnum_BREECHINGINLET,
  kIfcFireSuppressionTerminalTypeEnum_FIREHYDRANT,
  kIfcFireSuppressionTerminalTypeEnum_HOSEREEL,
  kIfcFireSuppressionTerminalTypeEnum_SPRINKLER,
  kIfcFireSuppressionTerminalTypeEnum_SPRINKLERDEFLECTOR,
  kIfcFireSuppressionTerminalTypeEnum_USERDEFINED,
  kIfcFireSuppressionTerminalTypeEnum_NOTDEFINED,
  kIfcFireSuppressionTerminalTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcFireSuppressionTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFireSuppressionTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcFireSuppressionTerminalTypeEnum& getUnset<OdIfc2x2_final::IfcFireSuppressionTerminalTypeEnum>() { static OdIfc2x2_final::IfcFireSuppressionTerminalTypeEnum nullEnum = OdIfc2x2_final::kIfcFireSuppressionTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcFlowDirectionEnum
{
  kIfcFlowDirectionEnum_SOURCE,
  kIfcFlowDirectionEnum_SINK,
  kIfcFlowDirectionEnum_SOURCEANDSINK,
  kIfcFlowDirectionEnum_NOTDEFINED,
  kIfcFlowDirectionEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcFlowDirectionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFlowDirectionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcFlowDirectionEnum& getUnset<OdIfc2x2_final::IfcFlowDirectionEnum>() { static OdIfc2x2_final::IfcFlowDirectionEnum nullEnum = OdIfc2x2_final::kIfcFlowDirectionEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcFlowInstrumentTypeEnum
{
  kIfcFlowInstrumentTypeEnum_PRESSUREGAUGE,
  kIfcFlowInstrumentTypeEnum_THERMOMETER,
  kIfcFlowInstrumentTypeEnum_AMMETER,
  kIfcFlowInstrumentTypeEnum_FREQUENCYMETER,
  kIfcFlowInstrumentTypeEnum_POWERFACTORMETER,
  kIfcFlowInstrumentTypeEnum_PHASEANGLEMETER,
  kIfcFlowInstrumentTypeEnum_VOLTMETER_PEAK,
  kIfcFlowInstrumentTypeEnum_VOLTMETER_RMS,
  kIfcFlowInstrumentTypeEnum_USERDEFINED,
  kIfcFlowInstrumentTypeEnum_NOTDEFINED,
  kIfcFlowInstrumentTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcFlowInstrumentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFlowInstrumentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcFlowInstrumentTypeEnum& getUnset<OdIfc2x2_final::IfcFlowInstrumentTypeEnum>() { static OdIfc2x2_final::IfcFlowInstrumentTypeEnum nullEnum = OdIfc2x2_final::kIfcFlowInstrumentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcFlowMeterTypeEnum
{
  kIfcFlowMeterTypeEnum_ELECTRICMETER,
  kIfcFlowMeterTypeEnum_ENERGYMETER,
  kIfcFlowMeterTypeEnum_FLOWMETER,
  kIfcFlowMeterTypeEnum_GASMETER,
  kIfcFlowMeterTypeEnum_OILMETER,
  kIfcFlowMeterTypeEnum_WATERMETER,
  kIfcFlowMeterTypeEnum_USERDEFINED,
  kIfcFlowMeterTypeEnum_NOTDEFINED,
  kIfcFlowMeterTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcFlowMeterTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFlowMeterTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcFlowMeterTypeEnum& getUnset<OdIfc2x2_final::IfcFlowMeterTypeEnum>() { static OdIfc2x2_final::IfcFlowMeterTypeEnum nullEnum = OdIfc2x2_final::kIfcFlowMeterTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcFootingTypeEnum
{
  kIfcFootingTypeEnum_FOOTING_BEAM,
  kIfcFootingTypeEnum_PAD_FOOTING,
  kIfcFootingTypeEnum_PILE_CAP,
  kIfcFootingTypeEnum_STRIP_FOOTING,
  kIfcFootingTypeEnum_USERDEFINED,
  kIfcFootingTypeEnum_NOTDEFINED,
  kIfcFootingTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcFootingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFootingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcFootingTypeEnum& getUnset<OdIfc2x2_final::IfcFootingTypeEnum>() { static OdIfc2x2_final::IfcFootingTypeEnum nullEnum = OdIfc2x2_final::kIfcFootingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcGasTerminalTypeEnum
{
  kIfcGasTerminalTypeEnum_GASAPPLIANCE,
  kIfcGasTerminalTypeEnum_GASBOOSTER,
  kIfcGasTerminalTypeEnum_GASBURNER,
  kIfcGasTerminalTypeEnum_USERDEFINED,
  kIfcGasTerminalTypeEnum_NOTDEFINED,
  kIfcGasTerminalTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcGasTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcGasTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcGasTerminalTypeEnum& getUnset<OdIfc2x2_final::IfcGasTerminalTypeEnum>() { static OdIfc2x2_final::IfcGasTerminalTypeEnum nullEnum = OdIfc2x2_final::kIfcGasTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcGeometricProjectionEnum
{
  kIfcGeometricProjectionEnum_GRAPH_VIEW,
  kIfcGeometricProjectionEnum_SKETCH_VIEW,
  kIfcGeometricProjectionEnum_MODEL_VIEW,
  kIfcGeometricProjectionEnum_PLAN_VIEW,
  kIfcGeometricProjectionEnum_REFLECTED_PLAN_VIEW,
  kIfcGeometricProjectionEnum_SECTION_VIEW,
  kIfcGeometricProjectionEnum_ELEVATION_VIEW,
  kIfcGeometricProjectionEnum_USERDEFINED,
  kIfcGeometricProjectionEnum_NOTDEFINED,
  kIfcGeometricProjectionEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcGeometricProjectionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcGeometricProjectionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcGeometricProjectionEnum& getUnset<OdIfc2x2_final::IfcGeometricProjectionEnum>() { static OdIfc2x2_final::IfcGeometricProjectionEnum nullEnum = OdIfc2x2_final::kIfcGeometricProjectionEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcGlobalOrLocalEnum
{
  kIfcGlobalOrLocalEnum_GLOBAL_COORDS,
  kIfcGlobalOrLocalEnum_LOCAL_COORDS,
  kIfcGlobalOrLocalEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcGlobalOrLocalEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcGlobalOrLocalEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcGlobalOrLocalEnum& getUnset<OdIfc2x2_final::IfcGlobalOrLocalEnum>() { static OdIfc2x2_final::IfcGlobalOrLocalEnum nullEnum = OdIfc2x2_final::kIfcGlobalOrLocalEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcHeatExchangerTypeEnum
{
  kIfcHeatExchangerTypeEnum_PLATE,
  kIfcHeatExchangerTypeEnum_SHELLANDTUBE,
  kIfcHeatExchangerTypeEnum_USERDEFINED,
  kIfcHeatExchangerTypeEnum_NOTDEFINED,
  kIfcHeatExchangerTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcHeatExchangerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcHeatExchangerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcHeatExchangerTypeEnum& getUnset<OdIfc2x2_final::IfcHeatExchangerTypeEnum>() { static OdIfc2x2_final::IfcHeatExchangerTypeEnum nullEnum = OdIfc2x2_final::kIfcHeatExchangerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcHumidifierTypeEnum
{
  kIfcHumidifierTypeEnum_STEAMINJECTION,
  kIfcHumidifierTypeEnum_ADIABATICAIRWASHER,
  kIfcHumidifierTypeEnum_ADIABATICPAN,
  kIfcHumidifierTypeEnum_ADIABATICWETTEDELEMENT,
  kIfcHumidifierTypeEnum_ADIABATICATOMIZING,
  kIfcHumidifierTypeEnum_ADIABATICULTRASONIC,
  kIfcHumidifierTypeEnum_ADIABATICRIGIDMEDIA,
  kIfcHumidifierTypeEnum_ADIABATICCOMPRESSEDAIRNOZZLE,
  kIfcHumidifierTypeEnum_ASSISTEDELECTRIC,
  kIfcHumidifierTypeEnum_ASSISTEDNATURALGAS,
  kIfcHumidifierTypeEnum_ASSISTEDPROPANE,
  kIfcHumidifierTypeEnum_ASSISTEDBUTANE,
  kIfcHumidifierTypeEnum_ASSISTEDSTEAM,
  kIfcHumidifierTypeEnum_USERDEFINED,
  kIfcHumidifierTypeEnum_NOTDEFINED,
  kIfcHumidifierTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcHumidifierTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcHumidifierTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcHumidifierTypeEnum& getUnset<OdIfc2x2_final::IfcHumidifierTypeEnum>() { static OdIfc2x2_final::IfcHumidifierTypeEnum nullEnum = OdIfc2x2_final::kIfcHumidifierTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcInternalOrExternalEnum
{
  kIfcInternalOrExternalEnum_INTERNAL,
  kIfcInternalOrExternalEnum_EXTERNAL,
  kIfcInternalOrExternalEnum_NOTDEFINED,
  kIfcInternalOrExternalEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcInternalOrExternalEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcInternalOrExternalEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcInternalOrExternalEnum& getUnset<OdIfc2x2_final::IfcInternalOrExternalEnum>() { static OdIfc2x2_final::IfcInternalOrExternalEnum nullEnum = OdIfc2x2_final::kIfcInternalOrExternalEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcInventoryTypeEnum
{
  kIfcInventoryTypeEnum_ASSETINVENTORY,
  kIfcInventoryTypeEnum_SPACEINVENTORY,
  kIfcInventoryTypeEnum_FURNITUREINVENTORY,
  kIfcInventoryTypeEnum_USERDEFINED,
  kIfcInventoryTypeEnum_NOTDEFINED,
  kIfcInventoryTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcInventoryTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcInventoryTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcInventoryTypeEnum& getUnset<OdIfc2x2_final::IfcInventoryTypeEnum>() { static OdIfc2x2_final::IfcInventoryTypeEnum nullEnum = OdIfc2x2_final::kIfcInventoryTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcJunctionBoxTypeEnum
{
  kIfcJunctionBoxTypeEnum_USERDEFINED,
  kIfcJunctionBoxTypeEnum_NOTDEFINED,
  kIfcJunctionBoxTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcJunctionBoxTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcJunctionBoxTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcJunctionBoxTypeEnum& getUnset<OdIfc2x2_final::IfcJunctionBoxTypeEnum>() { static OdIfc2x2_final::IfcJunctionBoxTypeEnum nullEnum = OdIfc2x2_final::kIfcJunctionBoxTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcLampTypeEnum
{
  kIfcLampTypeEnum_COMPACTFLUORESCENT,
  kIfcLampTypeEnum_FLUORESCENT,
  kIfcLampTypeEnum_HIGHPRESSUREMERCURY,
  kIfcLampTypeEnum_HIGHPRESSURESODIUM,
  kIfcLampTypeEnum_METALHALIDE,
  kIfcLampTypeEnum_TUNGSTENFILAMENT,
  kIfcLampTypeEnum_USERDEFINED,
  kIfcLampTypeEnum_NOTDEFINED,
  kIfcLampTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcLampTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLampTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcLampTypeEnum& getUnset<OdIfc2x2_final::IfcLampTypeEnum>() { static OdIfc2x2_final::IfcLampTypeEnum nullEnum = OdIfc2x2_final::kIfcLampTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcLayerSetDirectionEnum
{
  kIfcLayerSetDirectionEnum_AXIS1,
  kIfcLayerSetDirectionEnum_AXIS2,
  kIfcLayerSetDirectionEnum_AXIS3,
  kIfcLayerSetDirectionEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcLayerSetDirectionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLayerSetDirectionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcLayerSetDirectionEnum& getUnset<OdIfc2x2_final::IfcLayerSetDirectionEnum>() { static OdIfc2x2_final::IfcLayerSetDirectionEnum nullEnum = OdIfc2x2_final::kIfcLayerSetDirectionEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcLightDistributionCurveEnum
{
  kIfcLightDistributionCurveEnum_TYPE_A,
  kIfcLightDistributionCurveEnum_TYPE_B,
  kIfcLightDistributionCurveEnum_TYPE_C,
  kIfcLightDistributionCurveEnum_NOTDEFINED,
  kIfcLightDistributionCurveEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcLightDistributionCurveEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLightDistributionCurveEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcLightDistributionCurveEnum& getUnset<OdIfc2x2_final::IfcLightDistributionCurveEnum>() { static OdIfc2x2_final::IfcLightDistributionCurveEnum nullEnum = OdIfc2x2_final::kIfcLightDistributionCurveEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcLightEmissionSourceEnum
{
  kIfcLightEmissionSourceEnum_COMPACTFLUORESCENT,
  kIfcLightEmissionSourceEnum_FLUORESCENT,
  kIfcLightEmissionSourceEnum_HIGHPRESSUREMERCURY,
  kIfcLightEmissionSourceEnum_HIGHPRESSURESODIUM,
  kIfcLightEmissionSourceEnum_LIGHTEMITTINGDIODE,
  kIfcLightEmissionSourceEnum_LOWPRESSURESODIUM,
  kIfcLightEmissionSourceEnum_LOWVOLTAGEHALOGEN,
  kIfcLightEmissionSourceEnum_MAINVOLTAGEHALOGEN,
  kIfcLightEmissionSourceEnum_METALHALIDE,
  kIfcLightEmissionSourceEnum_TUNGSTENFILAMENT,
  kIfcLightEmissionSourceEnum_NOTDEFINED,
  kIfcLightEmissionSourceEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcLightEmissionSourceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLightEmissionSourceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcLightEmissionSourceEnum& getUnset<OdIfc2x2_final::IfcLightEmissionSourceEnum>() { static OdIfc2x2_final::IfcLightEmissionSourceEnum nullEnum = OdIfc2x2_final::kIfcLightEmissionSourceEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcLightFixtureTypeEnum
{
  kIfcLightFixtureTypeEnum_POINTSOURCE,
  kIfcLightFixtureTypeEnum_DIRECTIONSOURCE,
  kIfcLightFixtureTypeEnum_USERDEFINED,
  kIfcLightFixtureTypeEnum_NOTDEFINED,
  kIfcLightFixtureTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcLightFixtureTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLightFixtureTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcLightFixtureTypeEnum& getUnset<OdIfc2x2_final::IfcLightFixtureTypeEnum>() { static OdIfc2x2_final::IfcLightFixtureTypeEnum nullEnum = OdIfc2x2_final::kIfcLightFixtureTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcLoadGroupTypeEnum
{
  kIfcLoadGroupTypeEnum_LOAD_GROUP,
  kIfcLoadGroupTypeEnum_LOAD_CASE,
  kIfcLoadGroupTypeEnum_LOAD_COMBINATION_GROUP,
  kIfcLoadGroupTypeEnum_LOAD_COMBINATION,
  kIfcLoadGroupTypeEnum_USERDEFINED,
  kIfcLoadGroupTypeEnum_NOTDEFINED,
  kIfcLoadGroupTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcLoadGroupTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLoadGroupTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcLoadGroupTypeEnum& getUnset<OdIfc2x2_final::IfcLoadGroupTypeEnum>() { static OdIfc2x2_final::IfcLoadGroupTypeEnum nullEnum = OdIfc2x2_final::kIfcLoadGroupTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcLogicalOperatorEnum
{
  kIfcLogicalOperatorEnum_LOGICALAND,
  kIfcLogicalOperatorEnum_LOGICALOR,
  kIfcLogicalOperatorEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcLogicalOperatorEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLogicalOperatorEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcLogicalOperatorEnum& getUnset<OdIfc2x2_final::IfcLogicalOperatorEnum>() { static OdIfc2x2_final::IfcLogicalOperatorEnum nullEnum = OdIfc2x2_final::kIfcLogicalOperatorEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcMemberTypeEnum
{
  kIfcMemberTypeEnum_BRACE,
  kIfcMemberTypeEnum_CHORD,
  kIfcMemberTypeEnum_COLLAR,
  kIfcMemberTypeEnum_MEMBER,
  kIfcMemberTypeEnum_PLATE,
  kIfcMemberTypeEnum_POST,
  kIfcMemberTypeEnum_PURLIN,
  kIfcMemberTypeEnum_RAFTER,
  kIfcMemberTypeEnum_STRINGER,
  kIfcMemberTypeEnum_STRUT,
  kIfcMemberTypeEnum_STUD,
  kIfcMemberTypeEnum_USERDEFINED,
  kIfcMemberTypeEnum_NOTDEFINED,
  kIfcMemberTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcMemberTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMemberTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcMemberTypeEnum& getUnset<OdIfc2x2_final::IfcMemberTypeEnum>() { static OdIfc2x2_final::IfcMemberTypeEnum nullEnum = OdIfc2x2_final::kIfcMemberTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcMotorConnectionTypeEnum
{
  kIfcMotorConnectionTypeEnum_BELTDRIVE,
  kIfcMotorConnectionTypeEnum_COUPLING,
  kIfcMotorConnectionTypeEnum_DIRECTDRIVE,
  kIfcMotorConnectionTypeEnum_USERDEFINED,
  kIfcMotorConnectionTypeEnum_NOTDEFINED,
  kIfcMotorConnectionTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcMotorConnectionTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMotorConnectionTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcMotorConnectionTypeEnum& getUnset<OdIfc2x2_final::IfcMotorConnectionTypeEnum>() { static OdIfc2x2_final::IfcMotorConnectionTypeEnum nullEnum = OdIfc2x2_final::kIfcMotorConnectionTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcNullStyle
{
  kIfcNullStyle_NULL,
  kIfcNullStyle_unset
};

class IFC2X2_FINAL_EXPORT IfcNullStyleTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcNullStyleTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcNullStyle& getUnset<OdIfc2x2_final::IfcNullStyle>() { static OdIfc2x2_final::IfcNullStyle nullEnum = OdIfc2x2_final::kIfcNullStyle_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcObjectTypeEnum
{
  kIfcObjectTypeEnum_PRODUCT,
  kIfcObjectTypeEnum_PROCESS,
  kIfcObjectTypeEnum_CONTROL,
  kIfcObjectTypeEnum_RESOURCE,
  kIfcObjectTypeEnum_ACTOR,
  kIfcObjectTypeEnum_GROUP,
  kIfcObjectTypeEnum_PROJECT,
  kIfcObjectTypeEnum_NOTDEFINED,
  kIfcObjectTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcObjectTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcObjectTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcObjectTypeEnum& getUnset<OdIfc2x2_final::IfcObjectTypeEnum>() { static OdIfc2x2_final::IfcObjectTypeEnum nullEnum = OdIfc2x2_final::kIfcObjectTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcObjectiveEnum
{
  kIfcObjectiveEnum_CODECOMPLIANCE,
  kIfcObjectiveEnum_DESIGNINTENT,
  kIfcObjectiveEnum_HEALTHANDSAFETY,
  kIfcObjectiveEnum_REQUIREMENT,
  kIfcObjectiveEnum_SPECIFICATION,
  kIfcObjectiveEnum_TRIGGERCONDITION,
  kIfcObjectiveEnum_USERDEFINED,
  kIfcObjectiveEnum_NOTDEFINED,
  kIfcObjectiveEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcObjectiveEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcObjectiveEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcObjectiveEnum& getUnset<OdIfc2x2_final::IfcObjectiveEnum>() { static OdIfc2x2_final::IfcObjectiveEnum nullEnum = OdIfc2x2_final::kIfcObjectiveEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcOccupantTypeEnum
{
  kIfcOccupantTypeEnum_ASSIGNEE,
  kIfcOccupantTypeEnum_ASSIGNOR,
  kIfcOccupantTypeEnum_LESSEE,
  kIfcOccupantTypeEnum_LESSOR,
  kIfcOccupantTypeEnum_LETTINGAGENT,
  kIfcOccupantTypeEnum_OWNER,
  kIfcOccupantTypeEnum_TENANT,
  kIfcOccupantTypeEnum_USERDEFINED,
  kIfcOccupantTypeEnum_NOTDEFINED,
  kIfcOccupantTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcOccupantTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcOccupantTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcOccupantTypeEnum& getUnset<OdIfc2x2_final::IfcOccupantTypeEnum>() { static OdIfc2x2_final::IfcOccupantTypeEnum nullEnum = OdIfc2x2_final::kIfcOccupantTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcOutletTypeEnum
{
  kIfcOutletTypeEnum_AUDIOVISUALOUTLET,
  kIfcOutletTypeEnum_COMMUNICATIONSOUTLET,
  kIfcOutletTypeEnum_POWEROUTLET,
  kIfcOutletTypeEnum_USERDEFINED,
  kIfcOutletTypeEnum_NOTDEFINED,
  kIfcOutletTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcOutletTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcOutletTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcOutletTypeEnum& getUnset<OdIfc2x2_final::IfcOutletTypeEnum>() { static OdIfc2x2_final::IfcOutletTypeEnum nullEnum = OdIfc2x2_final::kIfcOutletTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcPermeableCoveringOperationEnum
{
  kIfcPermeableCoveringOperationEnum_GRILL,
  kIfcPermeableCoveringOperationEnum_LOUVER,
  kIfcPermeableCoveringOperationEnum_SCREEN,
  kIfcPermeableCoveringOperationEnum_USERDEFINED,
  kIfcPermeableCoveringOperationEnum_NOTDEFINED,
  kIfcPermeableCoveringOperationEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcPermeableCoveringOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPermeableCoveringOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcPermeableCoveringOperationEnum& getUnset<OdIfc2x2_final::IfcPermeableCoveringOperationEnum>() { static OdIfc2x2_final::IfcPermeableCoveringOperationEnum nullEnum = OdIfc2x2_final::kIfcPermeableCoveringOperationEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcPhysicalOrVirtualEnum
{
  kIfcPhysicalOrVirtualEnum_PHYSICAL,
  kIfcPhysicalOrVirtualEnum_VIRTUAL,
  kIfcPhysicalOrVirtualEnum_NOTDEFINED,
  kIfcPhysicalOrVirtualEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcPhysicalOrVirtualEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPhysicalOrVirtualEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcPhysicalOrVirtualEnum& getUnset<OdIfc2x2_final::IfcPhysicalOrVirtualEnum>() { static OdIfc2x2_final::IfcPhysicalOrVirtualEnum nullEnum = OdIfc2x2_final::kIfcPhysicalOrVirtualEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcPileConstructionEnum
{
  kIfcPileConstructionEnum_CAST_IN_PLACE,
  kIfcPileConstructionEnum_COMPOSITE,
  kIfcPileConstructionEnum_PRECAST_CONCRETE,
  kIfcPileConstructionEnum_PREFAB_STEEL,
  kIfcPileConstructionEnum_USERDEFINED,
  kIfcPileConstructionEnum_NOTDEFINED,
  kIfcPileConstructionEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcPileConstructionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPileConstructionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcPileConstructionEnum& getUnset<OdIfc2x2_final::IfcPileConstructionEnum>() { static OdIfc2x2_final::IfcPileConstructionEnum nullEnum = OdIfc2x2_final::kIfcPileConstructionEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcPileTypeEnum
{
  kIfcPileTypeEnum_COHESION,
  kIfcPileTypeEnum_FRICTION,
  kIfcPileTypeEnum_SUPPORT,
  kIfcPileTypeEnum_USERDEFINED,
  kIfcPileTypeEnum_NOTDEFINED,
  kIfcPileTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcPileTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPileTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcPileTypeEnum& getUnset<OdIfc2x2_final::IfcPileTypeEnum>() { static OdIfc2x2_final::IfcPileTypeEnum nullEnum = OdIfc2x2_final::kIfcPileTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcPipeFittingTypeEnum
{
  kIfcPipeFittingTypeEnum_BEND,
  kIfcPipeFittingTypeEnum_CONNECTOR,
  kIfcPipeFittingTypeEnum_ENTRY,
  kIfcPipeFittingTypeEnum_EXIT,
  kIfcPipeFittingTypeEnum_JUNCTION,
  kIfcPipeFittingTypeEnum_OBSTRUCTION,
  kIfcPipeFittingTypeEnum_TRANSITION,
  kIfcPipeFittingTypeEnum_USERDEFINED,
  kIfcPipeFittingTypeEnum_NOTDEFINED,
  kIfcPipeFittingTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcPipeFittingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPipeFittingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcPipeFittingTypeEnum& getUnset<OdIfc2x2_final::IfcPipeFittingTypeEnum>() { static OdIfc2x2_final::IfcPipeFittingTypeEnum nullEnum = OdIfc2x2_final::kIfcPipeFittingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcPipeSegmentTypeEnum
{
  kIfcPipeSegmentTypeEnum_FLEXIBLESEGMENT,
  kIfcPipeSegmentTypeEnum_RIGIDSEGMENT,
  kIfcPipeSegmentTypeEnum_GUTTER,
  kIfcPipeSegmentTypeEnum_SPOOL,
  kIfcPipeSegmentTypeEnum_USERDEFINED,
  kIfcPipeSegmentTypeEnum_NOTDEFINED,
  kIfcPipeSegmentTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcPipeSegmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPipeSegmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcPipeSegmentTypeEnum& getUnset<OdIfc2x2_final::IfcPipeSegmentTypeEnum>() { static OdIfc2x2_final::IfcPipeSegmentTypeEnum nullEnum = OdIfc2x2_final::kIfcPipeSegmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcPlateTypeEnum
{
  kIfcPlateTypeEnum_USERDEFINED,
  kIfcPlateTypeEnum_NOTDEFINED,
  kIfcPlateTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcPlateTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPlateTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcPlateTypeEnum& getUnset<OdIfc2x2_final::IfcPlateTypeEnum>() { static OdIfc2x2_final::IfcPlateTypeEnum nullEnum = OdIfc2x2_final::kIfcPlateTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcProcedureTypeEnum
{
  kIfcProcedureTypeEnum_ADVICE_CAUTION,
  kIfcProcedureTypeEnum_ADVICE_NOTE,
  kIfcProcedureTypeEnum_ADVICE_WARNING,
  kIfcProcedureTypeEnum_CALIBRATION,
  kIfcProcedureTypeEnum_DIAGNOSTIC,
  kIfcProcedureTypeEnum_SHUTDOWN,
  kIfcProcedureTypeEnum_STARTUP,
  kIfcProcedureTypeEnum_USERDEFINED,
  kIfcProcedureTypeEnum_NOTDEFINED,
  kIfcProcedureTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcProcedureTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProcedureTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcProcedureTypeEnum& getUnset<OdIfc2x2_final::IfcProcedureTypeEnum>() { static OdIfc2x2_final::IfcProcedureTypeEnum nullEnum = OdIfc2x2_final::kIfcProcedureTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcProfileTypeEnum
{
  kIfcProfileTypeEnum_CURVE,
  kIfcProfileTypeEnum_AREA,
  kIfcProfileTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcProfileTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProfileTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcProfileTypeEnum& getUnset<OdIfc2x2_final::IfcProfileTypeEnum>() { static OdIfc2x2_final::IfcProfileTypeEnum nullEnum = OdIfc2x2_final::kIfcProfileTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcProjectOrderRecordTypeEnum
{
  kIfcProjectOrderRecordTypeEnum_CHANGE,
  kIfcProjectOrderRecordTypeEnum_MAINTENANCE,
  kIfcProjectOrderRecordTypeEnum_MOVE,
  kIfcProjectOrderRecordTypeEnum_PURCHASE,
  kIfcProjectOrderRecordTypeEnum_WORK,
  kIfcProjectOrderRecordTypeEnum_USERDEFINED,
  kIfcProjectOrderRecordTypeEnum_NOTDEFINED,
  kIfcProjectOrderRecordTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcProjectOrderRecordTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProjectOrderRecordTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcProjectOrderRecordTypeEnum& getUnset<OdIfc2x2_final::IfcProjectOrderRecordTypeEnum>() { static OdIfc2x2_final::IfcProjectOrderRecordTypeEnum nullEnum = OdIfc2x2_final::kIfcProjectOrderRecordTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcProjectOrderTypeEnum
{
  kIfcProjectOrderTypeEnum_CHANGEORDER,
  kIfcProjectOrderTypeEnum_MAINTENANCEWORKORDER,
  kIfcProjectOrderTypeEnum_MOVEORDER,
  kIfcProjectOrderTypeEnum_PURCHASEORDER,
  kIfcProjectOrderTypeEnum_WORKORDER,
  kIfcProjectOrderTypeEnum_USERDEFINED,
  kIfcProjectOrderTypeEnum_NOTDEFINED,
  kIfcProjectOrderTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcProjectOrderTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProjectOrderTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcProjectOrderTypeEnum& getUnset<OdIfc2x2_final::IfcProjectOrderTypeEnum>() { static OdIfc2x2_final::IfcProjectOrderTypeEnum nullEnum = OdIfc2x2_final::kIfcProjectOrderTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcProjectedOrTrueLengthEnum
{
  kIfcProjectedOrTrueLengthEnum_PROJECTED_LENGTH,
  kIfcProjectedOrTrueLengthEnum_TRUE_LENGTH,
  kIfcProjectedOrTrueLengthEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcProjectedOrTrueLengthEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProjectedOrTrueLengthEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcProjectedOrTrueLengthEnum& getUnset<OdIfc2x2_final::IfcProjectedOrTrueLengthEnum>() { static OdIfc2x2_final::IfcProjectedOrTrueLengthEnum nullEnum = OdIfc2x2_final::kIfcProjectedOrTrueLengthEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcPropertySourceEnum
{
  kIfcPropertySourceEnum_DESIGN,
  kIfcPropertySourceEnum_DESIGNMAXIMUM,
  kIfcPropertySourceEnum_DESIGNMINIMUM,
  kIfcPropertySourceEnum_SIMULATED,
  kIfcPropertySourceEnum_ASBUILT,
  kIfcPropertySourceEnum_COMMISSIONING,
  kIfcPropertySourceEnum_MEASURED,
  kIfcPropertySourceEnum_USERDEFINED,
  kIfcPropertySourceEnum_NOTKNOWN,
  kIfcPropertySourceEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcPropertySourceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPropertySourceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcPropertySourceEnum& getUnset<OdIfc2x2_final::IfcPropertySourceEnum>() { static OdIfc2x2_final::IfcPropertySourceEnum nullEnum = OdIfc2x2_final::kIfcPropertySourceEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcProtectiveDeviceTypeEnum
{
  kIfcProtectiveDeviceTypeEnum_FUSEDISCONNECTOR,
  kIfcProtectiveDeviceTypeEnum_CIRCUITBREAKER,
  kIfcProtectiveDeviceTypeEnum_EARTHFAILUREDEVICE,
  kIfcProtectiveDeviceTypeEnum_RESIDUALCURRENTCIRCUITBREAKER,
  kIfcProtectiveDeviceTypeEnum_RESIDUALCURRENTSWITCH,
  kIfcProtectiveDeviceTypeEnum_VARISTOR,
  kIfcProtectiveDeviceTypeEnum_USERDEFINED,
  kIfcProtectiveDeviceTypeEnum_NOTDEFINED,
  kIfcProtectiveDeviceTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcProtectiveDeviceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProtectiveDeviceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcProtectiveDeviceTypeEnum& getUnset<OdIfc2x2_final::IfcProtectiveDeviceTypeEnum>() { static OdIfc2x2_final::IfcProtectiveDeviceTypeEnum nullEnum = OdIfc2x2_final::kIfcProtectiveDeviceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcPumpTypeEnum
{
  kIfcPumpTypeEnum_CIRCULATOR,
  kIfcPumpTypeEnum_ENDSUCTION,
  kIfcPumpTypeEnum_SPLITCASE,
  kIfcPumpTypeEnum_VERTICALINLINE,
  kIfcPumpTypeEnum_VERTICALTURBINE,
  kIfcPumpTypeEnum_USERDEFINED,
  kIfcPumpTypeEnum_NOTDEFINED,
  kIfcPumpTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcPumpTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPumpTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcPumpTypeEnum& getUnset<OdIfc2x2_final::IfcPumpTypeEnum>() { static OdIfc2x2_final::IfcPumpTypeEnum nullEnum = OdIfc2x2_final::kIfcPumpTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcRailingTypeEnum
{
  kIfcRailingTypeEnum_HANDRAIL,
  kIfcRailingTypeEnum_GUARDRAIL,
  kIfcRailingTypeEnum_BALUSTRADE,
  kIfcRailingTypeEnum_USERDEFINED,
  kIfcRailingTypeEnum_NOTDEFINED,
  kIfcRailingTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcRailingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRailingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcRailingTypeEnum& getUnset<OdIfc2x2_final::IfcRailingTypeEnum>() { static OdIfc2x2_final::IfcRailingTypeEnum nullEnum = OdIfc2x2_final::kIfcRailingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcRampFlightTypeEnum
{
  kIfcRampFlightTypeEnum_STRAIGHT,
  kIfcRampFlightTypeEnum_SPIRAL,
  kIfcRampFlightTypeEnum_USERDEFINED,
  kIfcRampFlightTypeEnum_NOTDEFINED,
  kIfcRampFlightTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcRampFlightTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRampFlightTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcRampFlightTypeEnum& getUnset<OdIfc2x2_final::IfcRampFlightTypeEnum>() { static OdIfc2x2_final::IfcRampFlightTypeEnum nullEnum = OdIfc2x2_final::kIfcRampFlightTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcRampTypeEnum
{
  kIfcRampTypeEnum_STRAIGHT_RUN_RAMP,
  kIfcRampTypeEnum_TWO_STRAIGHT_RUN_RAMP,
  kIfcRampTypeEnum_QUARTER_TURN_RAMP,
  kIfcRampTypeEnum_TWO_QUARTER_TURN_RAMP,
  kIfcRampTypeEnum_HALF_TURN_RAMP,
  kIfcRampTypeEnum_SPIRAL_RAMP,
  kIfcRampTypeEnum_USERDEFINED,
  kIfcRampTypeEnum_NOTDEFINED,
  kIfcRampTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcRampTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRampTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcRampTypeEnum& getUnset<OdIfc2x2_final::IfcRampTypeEnum>() { static OdIfc2x2_final::IfcRampTypeEnum nullEnum = OdIfc2x2_final::kIfcRampTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcReflectanceMethodEnum
{
  kIfcReflectanceMethodEnum_BLINN,
  kIfcReflectanceMethodEnum_FLAT,
  kIfcReflectanceMethodEnum_GLASS,
  kIfcReflectanceMethodEnum_MATT,
  kIfcReflectanceMethodEnum_METAL,
  kIfcReflectanceMethodEnum_MIRROR,
  kIfcReflectanceMethodEnum_PHONG,
  kIfcReflectanceMethodEnum_PLASTIC,
  kIfcReflectanceMethodEnum_STRAUSS,
  kIfcReflectanceMethodEnum_NOTDEFINED,
  kIfcReflectanceMethodEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcReflectanceMethodEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcReflectanceMethodEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcReflectanceMethodEnum& getUnset<OdIfc2x2_final::IfcReflectanceMethodEnum>() { static OdIfc2x2_final::IfcReflectanceMethodEnum nullEnum = OdIfc2x2_final::kIfcReflectanceMethodEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcReinforcingBarRoleEnum
{
  kIfcReinforcingBarRoleEnum_MAIN,
  kIfcReinforcingBarRoleEnum_SHEAR,
  kIfcReinforcingBarRoleEnum_LIGATURE,
  kIfcReinforcingBarRoleEnum_STUD,
  kIfcReinforcingBarRoleEnum_PUNCHING,
  kIfcReinforcingBarRoleEnum_EDGE,
  kIfcReinforcingBarRoleEnum_RING,
  kIfcReinforcingBarRoleEnum_USERDEFINED,
  kIfcReinforcingBarRoleEnum_NOTDEFINED,
  kIfcReinforcingBarRoleEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcReinforcingBarRoleEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcReinforcingBarRoleEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcReinforcingBarRoleEnum& getUnset<OdIfc2x2_final::IfcReinforcingBarRoleEnum>() { static OdIfc2x2_final::IfcReinforcingBarRoleEnum nullEnum = OdIfc2x2_final::kIfcReinforcingBarRoleEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcReinforcingBarSurfaceEnum
{
  kIfcReinforcingBarSurfaceEnum_PLAIN,
  kIfcReinforcingBarSurfaceEnum_TEXTURED,
  kIfcReinforcingBarSurfaceEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcReinforcingBarSurfaceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcReinforcingBarSurfaceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcReinforcingBarSurfaceEnum& getUnset<OdIfc2x2_final::IfcReinforcingBarSurfaceEnum>() { static OdIfc2x2_final::IfcReinforcingBarSurfaceEnum nullEnum = OdIfc2x2_final::kIfcReinforcingBarSurfaceEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcResourceConsumptionEnum
{
  kIfcResourceConsumptionEnum_CONSUMED,
  kIfcResourceConsumptionEnum_PARTIALLYCONSUMED,
  kIfcResourceConsumptionEnum_NOTCONSUMED,
  kIfcResourceConsumptionEnum_OCCUPIED,
  kIfcResourceConsumptionEnum_PARTIALLYOCCUPIED,
  kIfcResourceConsumptionEnum_NOTOCCUPIED,
  kIfcResourceConsumptionEnum_USERDEFINED,
  kIfcResourceConsumptionEnum_NOTDEFINED,
  kIfcResourceConsumptionEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcResourceConsumptionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcResourceConsumptionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcResourceConsumptionEnum& getUnset<OdIfc2x2_final::IfcResourceConsumptionEnum>() { static OdIfc2x2_final::IfcResourceConsumptionEnum nullEnum = OdIfc2x2_final::kIfcResourceConsumptionEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcRibPlateDirectionEnum
{
  kIfcRibPlateDirectionEnum_DIRECTION_X,
  kIfcRibPlateDirectionEnum_DIRECTION_Y,
  kIfcRibPlateDirectionEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcRibPlateDirectionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRibPlateDirectionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcRibPlateDirectionEnum& getUnset<OdIfc2x2_final::IfcRibPlateDirectionEnum>() { static OdIfc2x2_final::IfcRibPlateDirectionEnum nullEnum = OdIfc2x2_final::kIfcRibPlateDirectionEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcRoleEnum
{
  kIfcRoleEnum_SUPPLIER,
  kIfcRoleEnum_MANUFACTURER,
  kIfcRoleEnum_CONTRACTOR,
  kIfcRoleEnum_SUBCONTRACTOR,
  kIfcRoleEnum_ARCHITECT,
  kIfcRoleEnum_STRUCTURALENGINEER,
  kIfcRoleEnum_COSTENGINEER,
  kIfcRoleEnum_CLIENT,
  kIfcRoleEnum_BUILDINGOWNER,
  kIfcRoleEnum_BUILDINGOPERATOR,
  kIfcRoleEnum_MECHANICALENGINEER,
  kIfcRoleEnum_ELECTRICALENGINEER,
  kIfcRoleEnum_PROJECTMANAGER,
  kIfcRoleEnum_FACILITIESMANAGER,
  kIfcRoleEnum_CIVILENGINEER,
  kIfcRoleEnum_COMISSIONINGENGINEER,
  kIfcRoleEnum_ENGINEER,
  kIfcRoleEnum_OWNER,
  kIfcRoleEnum_CONSULTANT,
  kIfcRoleEnum_CONSTRUCTIONMANAGER,
  kIfcRoleEnum_FIELDCONSTRUCTIONMANAGER,
  kIfcRoleEnum_RESELLER,
  kIfcRoleEnum_USERDEFINED,
  kIfcRoleEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcRoleEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRoleEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcRoleEnum& getUnset<OdIfc2x2_final::IfcRoleEnum>() { static OdIfc2x2_final::IfcRoleEnum nullEnum = OdIfc2x2_final::kIfcRoleEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcRoofTypeEnum
{
  kIfcRoofTypeEnum_FLAT_ROOF,
  kIfcRoofTypeEnum_SHED_ROOF,
  kIfcRoofTypeEnum_GABLE_ROOF,
  kIfcRoofTypeEnum_HIP_ROOF,
  kIfcRoofTypeEnum_HIPPED_GABLE_ROOF,
  kIfcRoofTypeEnum_GAMBREL_ROOF,
  kIfcRoofTypeEnum_MANSARD_ROOF,
  kIfcRoofTypeEnum_BARREL_ROOF,
  kIfcRoofTypeEnum_RAINBOW_ROOF,
  kIfcRoofTypeEnum_BUTTERFLY_ROOF,
  kIfcRoofTypeEnum_PAVILION_ROOF,
  kIfcRoofTypeEnum_DOME_ROOF,
  kIfcRoofTypeEnum_FREEFORM,
  kIfcRoofTypeEnum_NOTDEFINED,
  kIfcRoofTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcRoofTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRoofTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcRoofTypeEnum& getUnset<OdIfc2x2_final::IfcRoofTypeEnum>() { static OdIfc2x2_final::IfcRoofTypeEnum nullEnum = OdIfc2x2_final::kIfcRoofTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcSIPrefix
{
  kIfcSIPrefix_EXA,
  kIfcSIPrefix_PETA,
  kIfcSIPrefix_TERA,
  kIfcSIPrefix_GIGA,
  kIfcSIPrefix_MEGA,
  kIfcSIPrefix_KILO,
  kIfcSIPrefix_HECTO,
  kIfcSIPrefix_DECA,
  kIfcSIPrefix_DECI,
  kIfcSIPrefix_CENTI,
  kIfcSIPrefix_MILLI,
  kIfcSIPrefix_MICRO,
  kIfcSIPrefix_NANO,
  kIfcSIPrefix_PICO,
  kIfcSIPrefix_FEMTO,
  kIfcSIPrefix_ATTO,
  kIfcSIPrefix_unset
};

class IFC2X2_FINAL_EXPORT IfcSIPrefixTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSIPrefixTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcSIPrefix& getUnset<OdIfc2x2_final::IfcSIPrefix>() { static OdIfc2x2_final::IfcSIPrefix nullEnum = OdIfc2x2_final::kIfcSIPrefix_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcSIUnitName
{
  kIfcSIUnitName_AMPERE,
  kIfcSIUnitName_BECQUEREL,
  kIfcSIUnitName_CANDELA,
  kIfcSIUnitName_COULOMB,
  kIfcSIUnitName_CUBIC_METRE,
  kIfcSIUnitName_DEGREE_CELSIUS,
  kIfcSIUnitName_FARAD,
  kIfcSIUnitName_GRAM,
  kIfcSIUnitName_GRAY,
  kIfcSIUnitName_HENRY,
  kIfcSIUnitName_HERTZ,
  kIfcSIUnitName_JOULE,
  kIfcSIUnitName_KELVIN,
  kIfcSIUnitName_LUMEN,
  kIfcSIUnitName_LUX,
  kIfcSIUnitName_METRE,
  kIfcSIUnitName_MOLE,
  kIfcSIUnitName_NEWTON,
  kIfcSIUnitName_OHM,
  kIfcSIUnitName_PASCAL,
  kIfcSIUnitName_RADIAN,
  kIfcSIUnitName_SECOND,
  kIfcSIUnitName_SIEMENS,
  kIfcSIUnitName_SIEVERT,
  kIfcSIUnitName_SQUARE_METRE,
  kIfcSIUnitName_STERADIAN,
  kIfcSIUnitName_TESLA,
  kIfcSIUnitName_VOLT,
  kIfcSIUnitName_WATT,
  kIfcSIUnitName_WEBER,
  kIfcSIUnitName_unset
};

class IFC2X2_FINAL_EXPORT IfcSIUnitNameTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSIUnitNameTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcSIUnitName& getUnset<OdIfc2x2_final::IfcSIUnitName>() { static OdIfc2x2_final::IfcSIUnitName nullEnum = OdIfc2x2_final::kIfcSIUnitName_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcSanitaryTerminalTypeEnum
{
  kIfcSanitaryTerminalTypeEnum_BATH,
  kIfcSanitaryTerminalTypeEnum_BIDET,
  kIfcSanitaryTerminalTypeEnum_CISTERN,
  kIfcSanitaryTerminalTypeEnum_SHOWER,
  kIfcSanitaryTerminalTypeEnum_SINK,
  kIfcSanitaryTerminalTypeEnum_SANITARYFOUNTAIN,
  kIfcSanitaryTerminalTypeEnum_TOILETPAN,
  kIfcSanitaryTerminalTypeEnum_URINAL,
  kIfcSanitaryTerminalTypeEnum_WASHHANDBASIN,
  kIfcSanitaryTerminalTypeEnum_WCSEAT,
  kIfcSanitaryTerminalTypeEnum_USERDEFINED,
  kIfcSanitaryTerminalTypeEnum_NOTDEFINED,
  kIfcSanitaryTerminalTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcSanitaryTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSanitaryTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcSanitaryTerminalTypeEnum& getUnset<OdIfc2x2_final::IfcSanitaryTerminalTypeEnum>() { static OdIfc2x2_final::IfcSanitaryTerminalTypeEnum nullEnum = OdIfc2x2_final::kIfcSanitaryTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcSectionTypeEnum
{
  kIfcSectionTypeEnum_UNIFORM,
  kIfcSectionTypeEnum_TAPERED,
  kIfcSectionTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcSectionTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSectionTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcSectionTypeEnum& getUnset<OdIfc2x2_final::IfcSectionTypeEnum>() { static OdIfc2x2_final::IfcSectionTypeEnum nullEnum = OdIfc2x2_final::kIfcSectionTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcSensorTypeEnum
{
  kIfcSensorTypeEnum_CO2SENSOR,
  kIfcSensorTypeEnum_FIRESENSOR,
  kIfcSensorTypeEnum_FLOWSENSOR,
  kIfcSensorTypeEnum_GASSENSOR,
  kIfcSensorTypeEnum_HEATSENSOR,
  kIfcSensorTypeEnum_HUMIDITYSENSOR,
  kIfcSensorTypeEnum_LIGHTSENSOR,
  kIfcSensorTypeEnum_MOISTURESENSOR,
  kIfcSensorTypeEnum_MOVEMENTSENSOR,
  kIfcSensorTypeEnum_PRESSURESENSOR,
  kIfcSensorTypeEnum_SMOKESENSOR,
  kIfcSensorTypeEnum_SOUNDSENSOR,
  kIfcSensorTypeEnum_TEMPERATURESENSOR,
  kIfcSensorTypeEnum_USERDEFINED,
  kIfcSensorTypeEnum_NOTDEFINED,
  kIfcSensorTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcSensorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSensorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcSensorTypeEnum& getUnset<OdIfc2x2_final::IfcSensorTypeEnum>() { static OdIfc2x2_final::IfcSensorTypeEnum nullEnum = OdIfc2x2_final::kIfcSensorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcSequenceEnum
{
  kIfcSequenceEnum_START_START,
  kIfcSequenceEnum_START_FINISH,
  kIfcSequenceEnum_FINISH_START,
  kIfcSequenceEnum_FINISH_FINISH,
  kIfcSequenceEnum_NOTDEFINED,
  kIfcSequenceEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcSequenceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSequenceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcSequenceEnum& getUnset<OdIfc2x2_final::IfcSequenceEnum>() { static OdIfc2x2_final::IfcSequenceEnum nullEnum = OdIfc2x2_final::kIfcSequenceEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcServiceLifeFactorTypeEnum
{
  kIfcServiceLifeFactorTypeEnum_A_QUALITYOFCOMPONENTS,
  kIfcServiceLifeFactorTypeEnum_B_DESIGNLEVEL,
  kIfcServiceLifeFactorTypeEnum_C_WORKEXECUTIONLEVEL,
  kIfcServiceLifeFactorTypeEnum_D_INDOORENVIRONMENT,
  kIfcServiceLifeFactorTypeEnum_E_OUTDOORENVIRONMENT,
  kIfcServiceLifeFactorTypeEnum_F_INUSECONDITIONS,
  kIfcServiceLifeFactorTypeEnum_G_MAINTENANCELEVEL,
  kIfcServiceLifeFactorTypeEnum_USERDEFINED,
  kIfcServiceLifeFactorTypeEnum_NOTDEFINED,
  kIfcServiceLifeFactorTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcServiceLifeFactorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcServiceLifeFactorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcServiceLifeFactorTypeEnum& getUnset<OdIfc2x2_final::IfcServiceLifeFactorTypeEnum>() { static OdIfc2x2_final::IfcServiceLifeFactorTypeEnum nullEnum = OdIfc2x2_final::kIfcServiceLifeFactorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcServiceLifeTypeEnum
{
  kIfcServiceLifeTypeEnum_ACTUALSERVICELIFE,
  kIfcServiceLifeTypeEnum_EXPECTEDSERVICELIFE,
  kIfcServiceLifeTypeEnum_OPTIMISTICREFERENCESERVICELIFE,
  kIfcServiceLifeTypeEnum_PESSIMISTICREFERENCESERVICELIFE,
  kIfcServiceLifeTypeEnum_REFERENCESERVICELIFE,
  kIfcServiceLifeTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcServiceLifeTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcServiceLifeTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcServiceLifeTypeEnum& getUnset<OdIfc2x2_final::IfcServiceLifeTypeEnum>() { static OdIfc2x2_final::IfcServiceLifeTypeEnum nullEnum = OdIfc2x2_final::kIfcServiceLifeTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcSlabTypeEnum
{
  kIfcSlabTypeEnum_FLOOR,
  kIfcSlabTypeEnum_ROOF,
  kIfcSlabTypeEnum_LANDING,
  kIfcSlabTypeEnum_USERDEFINED,
  kIfcSlabTypeEnum_NOTDEFINED,
  kIfcSlabTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcSlabTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSlabTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcSlabTypeEnum& getUnset<OdIfc2x2_final::IfcSlabTypeEnum>() { static OdIfc2x2_final::IfcSlabTypeEnum nullEnum = OdIfc2x2_final::kIfcSlabTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcSoundScaleEnum
{
  kIfcSoundScaleEnum_DBA,
  kIfcSoundScaleEnum_DBB,
  kIfcSoundScaleEnum_DBC,
  kIfcSoundScaleEnum_NC,
  kIfcSoundScaleEnum_NR,
  kIfcSoundScaleEnum_USERDEFINED,
  kIfcSoundScaleEnum_NOTDEFINED,
  kIfcSoundScaleEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcSoundScaleEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSoundScaleEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcSoundScaleEnum& getUnset<OdIfc2x2_final::IfcSoundScaleEnum>() { static OdIfc2x2_final::IfcSoundScaleEnum nullEnum = OdIfc2x2_final::kIfcSoundScaleEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcSpaceHeaterTypeEnum
{
  kIfcSpaceHeaterTypeEnum_SECTIONALRADIATOR,
  kIfcSpaceHeaterTypeEnum_PANELRADIATOR,
  kIfcSpaceHeaterTypeEnum_TUBULARRADIATOR,
  kIfcSpaceHeaterTypeEnum_CONVECTOR,
  kIfcSpaceHeaterTypeEnum_BASEBOARDHEATER,
  kIfcSpaceHeaterTypeEnum_FINNEDTUBEUNIT,
  kIfcSpaceHeaterTypeEnum_UNITHEATER,
  kIfcSpaceHeaterTypeEnum_USERDEFINED,
  kIfcSpaceHeaterTypeEnum_NOTDEFINED,
  kIfcSpaceHeaterTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcSpaceHeaterTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSpaceHeaterTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcSpaceHeaterTypeEnum& getUnset<OdIfc2x2_final::IfcSpaceHeaterTypeEnum>() { static OdIfc2x2_final::IfcSpaceHeaterTypeEnum nullEnum = OdIfc2x2_final::kIfcSpaceHeaterTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcStackTerminalTypeEnum
{
  kIfcStackTerminalTypeEnum_BIRDCAGE,
  kIfcStackTerminalTypeEnum_COWL,
  kIfcStackTerminalTypeEnum_RAINWATERHOPPER,
  kIfcStackTerminalTypeEnum_USERDEFINED,
  kIfcStackTerminalTypeEnum_NOTDEFINED,
  kIfcStackTerminalTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcStackTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStackTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcStackTerminalTypeEnum& getUnset<OdIfc2x2_final::IfcStackTerminalTypeEnum>() { static OdIfc2x2_final::IfcStackTerminalTypeEnum nullEnum = OdIfc2x2_final::kIfcStackTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcStairFlightTypeEnum
{
  kIfcStairFlightTypeEnum_STRAIGHT,
  kIfcStairFlightTypeEnum_WINDER,
  kIfcStairFlightTypeEnum_SPIRAL,
  kIfcStairFlightTypeEnum_CURVED,
  kIfcStairFlightTypeEnum_FREEFORM,
  kIfcStairFlightTypeEnum_USERDEFINED,
  kIfcStairFlightTypeEnum_NOTDEFINED,
  kIfcStairFlightTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcStairFlightTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStairFlightTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcStairFlightTypeEnum& getUnset<OdIfc2x2_final::IfcStairFlightTypeEnum>() { static OdIfc2x2_final::IfcStairFlightTypeEnum nullEnum = OdIfc2x2_final::kIfcStairFlightTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcStairTypeEnum
{
  kIfcStairTypeEnum_STRAIGHT_RUN_STAIR,
  kIfcStairTypeEnum_TWO_STRAIGHT_RUN_STAIR,
  kIfcStairTypeEnum_QUARTER_WINDING_STAIR,
  kIfcStairTypeEnum_QUARTER_TURN_STAIR,
  kIfcStairTypeEnum_HALF_WINDING_STAIR,
  kIfcStairTypeEnum_HALF_TURN_STAIR,
  kIfcStairTypeEnum_TWO_QUARTER_WINDING_STAIR,
  kIfcStairTypeEnum_TWO_QUARTER_TURN_STAIR,
  kIfcStairTypeEnum_THREE_QUARTER_WINDING_STAIR,
  kIfcStairTypeEnum_THREE_QUARTER_TURN_STAIR,
  kIfcStairTypeEnum_SPIRAL_STAIR,
  kIfcStairTypeEnum_DOUBLE_RETURN_STAIR,
  kIfcStairTypeEnum_CURVED_RUN_STAIR,
  kIfcStairTypeEnum_TWO_CURVED_RUN_STAIR,
  kIfcStairTypeEnum_USERDEFINED,
  kIfcStairTypeEnum_NOTDEFINED,
  kIfcStairTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcStairTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStairTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcStairTypeEnum& getUnset<OdIfc2x2_final::IfcStairTypeEnum>() { static OdIfc2x2_final::IfcStairTypeEnum nullEnum = OdIfc2x2_final::kIfcStairTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcStateEnum
{
  kIfcStateEnum_READWRITE,
  kIfcStateEnum_READONLY,
  kIfcStateEnum_LOCKED,
  kIfcStateEnum_READWRITELOCKED,
  kIfcStateEnum_READONLYLOCKED,
  kIfcStateEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcStateEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStateEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcStateEnum& getUnset<OdIfc2x2_final::IfcStateEnum>() { static OdIfc2x2_final::IfcStateEnum nullEnum = OdIfc2x2_final::kIfcStateEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcStructuralCurveTypeEnum
{
  kIfcStructuralCurveTypeEnum_RIGID_JOINED_MEMBER,
  kIfcStructuralCurveTypeEnum_PIN_JOINED_MEMBER,
  kIfcStructuralCurveTypeEnum_CABLE,
  kIfcStructuralCurveTypeEnum_TENSION_MEMBER,
  kIfcStructuralCurveTypeEnum_COMPRESSION_MEMBER,
  kIfcStructuralCurveTypeEnum_USERDEFINED,
  kIfcStructuralCurveTypeEnum_NOTDEFINED,
  kIfcStructuralCurveTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcStructuralCurveTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStructuralCurveTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcStructuralCurveTypeEnum& getUnset<OdIfc2x2_final::IfcStructuralCurveTypeEnum>() { static OdIfc2x2_final::IfcStructuralCurveTypeEnum nullEnum = OdIfc2x2_final::kIfcStructuralCurveTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcStructuralSurfaceTypeEnum
{
  kIfcStructuralSurfaceTypeEnum_BENDING_ELEMENT,
  kIfcStructuralSurfaceTypeEnum_MEMBRANE_ELEMENT,
  kIfcStructuralSurfaceTypeEnum_SHELL,
  kIfcStructuralSurfaceTypeEnum_USERDEFINED,
  kIfcStructuralSurfaceTypeEnum_NOTDEFINED,
  kIfcStructuralSurfaceTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcStructuralSurfaceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStructuralSurfaceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcStructuralSurfaceTypeEnum& getUnset<OdIfc2x2_final::IfcStructuralSurfaceTypeEnum>() { static OdIfc2x2_final::IfcStructuralSurfaceTypeEnum nullEnum = OdIfc2x2_final::kIfcStructuralSurfaceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcSurfaceSide
{
  kIfcSurfaceSide_POSITIVE,
  kIfcSurfaceSide_NEGATIVE,
  kIfcSurfaceSide_BOTH,
  kIfcSurfaceSide_unset
};

class IFC2X2_FINAL_EXPORT IfcSurfaceSideTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSurfaceSideTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcSurfaceSide& getUnset<OdIfc2x2_final::IfcSurfaceSide>() { static OdIfc2x2_final::IfcSurfaceSide nullEnum = OdIfc2x2_final::kIfcSurfaceSide_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcSurfaceTextureEnum
{
  kIfcSurfaceTextureEnum_BUMP,
  kIfcSurfaceTextureEnum_OPACITY,
  kIfcSurfaceTextureEnum_REFLECTION,
  kIfcSurfaceTextureEnum_SELFILLUMINATION,
  kIfcSurfaceTextureEnum_SHININESS,
  kIfcSurfaceTextureEnum_SPECULAR,
  kIfcSurfaceTextureEnum_TEXTURE,
  kIfcSurfaceTextureEnum_TRANSPARENCYMAP,
  kIfcSurfaceTextureEnum_NOTDEFINED,
  kIfcSurfaceTextureEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcSurfaceTextureEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSurfaceTextureEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcSurfaceTextureEnum& getUnset<OdIfc2x2_final::IfcSurfaceTextureEnum>() { static OdIfc2x2_final::IfcSurfaceTextureEnum nullEnum = OdIfc2x2_final::kIfcSurfaceTextureEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcSwitchingDeviceTypeEnum
{
  kIfcSwitchingDeviceTypeEnum_CONTACTOR,
  kIfcSwitchingDeviceTypeEnum_EMERGENCYSTOP,
  kIfcSwitchingDeviceTypeEnum_STARTER,
  kIfcSwitchingDeviceTypeEnum_SWITCHDISCONNECTOR,
  kIfcSwitchingDeviceTypeEnum_TOGGLESWITCH,
  kIfcSwitchingDeviceTypeEnum_USERDEFINED,
  kIfcSwitchingDeviceTypeEnum_NOTDEFINED,
  kIfcSwitchingDeviceTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcSwitchingDeviceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSwitchingDeviceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcSwitchingDeviceTypeEnum& getUnset<OdIfc2x2_final::IfcSwitchingDeviceTypeEnum>() { static OdIfc2x2_final::IfcSwitchingDeviceTypeEnum nullEnum = OdIfc2x2_final::kIfcSwitchingDeviceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcTankTypeEnum
{
  kIfcTankTypeEnum_PREFORMED,
  kIfcTankTypeEnum_SECTIONAL,
  kIfcTankTypeEnum_EXPANSION,
  kIfcTankTypeEnum_PRESSUREVESSEL,
  kIfcTankTypeEnum_USERDEFINED,
  kIfcTankTypeEnum_NOTDEFINED,
  kIfcTankTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcTankTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTankTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcTankTypeEnum& getUnset<OdIfc2x2_final::IfcTankTypeEnum>() { static OdIfc2x2_final::IfcTankTypeEnum nullEnum = OdIfc2x2_final::kIfcTankTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcTendonTypeEnum
{
  kIfcTendonTypeEnum_STRAND,
  kIfcTendonTypeEnum_WIRE,
  kIfcTendonTypeEnum_BAR,
  kIfcTendonTypeEnum_COATED,
  kIfcTendonTypeEnum_USERDEFINED,
  kIfcTendonTypeEnum_NOTDEFINED,
  kIfcTendonTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcTendonTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTendonTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcTendonTypeEnum& getUnset<OdIfc2x2_final::IfcTendonTypeEnum>() { static OdIfc2x2_final::IfcTendonTypeEnum nullEnum = OdIfc2x2_final::kIfcTendonTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcTextPath
{
  kIfcTextPath_LEFT,
  kIfcTextPath_RIGHT,
  kIfcTextPath_UP,
  kIfcTextPath_DOWN,
  kIfcTextPath_unset
};

class IFC2X2_FINAL_EXPORT IfcTextPathTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTextPathTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcTextPath& getUnset<OdIfc2x2_final::IfcTextPath>() { static OdIfc2x2_final::IfcTextPath nullEnum = OdIfc2x2_final::kIfcTextPath_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcThermalLoadSourceEnum
{
  kIfcThermalLoadSourceEnum_PEOPLE,
  kIfcThermalLoadSourceEnum_LIGHTING,
  kIfcThermalLoadSourceEnum_EQUIPMENT,
  kIfcThermalLoadSourceEnum_VENTILATIONINDOORAIR,
  kIfcThermalLoadSourceEnum_VENTILATIONOUTSIDEAIR,
  kIfcThermalLoadSourceEnum_RECIRCULATEDAIR,
  kIfcThermalLoadSourceEnum_EXHAUSTAIR,
  kIfcThermalLoadSourceEnum_AIREXCHANGERATE,
  kIfcThermalLoadSourceEnum_DRYBULBTEMPERATURE,
  kIfcThermalLoadSourceEnum_RELATIVEHUMIDITY,
  kIfcThermalLoadSourceEnum_INFILTRATION,
  kIfcThermalLoadSourceEnum_USERDEFINED,
  kIfcThermalLoadSourceEnum_NOTDEFINED,
  kIfcThermalLoadSourceEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcThermalLoadSourceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcThermalLoadSourceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcThermalLoadSourceEnum& getUnset<OdIfc2x2_final::IfcThermalLoadSourceEnum>() { static OdIfc2x2_final::IfcThermalLoadSourceEnum nullEnum = OdIfc2x2_final::kIfcThermalLoadSourceEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcThermalLoadTypeEnum
{
  kIfcThermalLoadTypeEnum_SENSIBLE,
  kIfcThermalLoadTypeEnum_LATENT,
  kIfcThermalLoadTypeEnum_RADIANT,
  kIfcThermalLoadTypeEnum_NOTDEFINED,
  kIfcThermalLoadTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcThermalLoadTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcThermalLoadTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcThermalLoadTypeEnum& getUnset<OdIfc2x2_final::IfcThermalLoadTypeEnum>() { static OdIfc2x2_final::IfcThermalLoadTypeEnum nullEnum = OdIfc2x2_final::kIfcThermalLoadTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcTimeSeriesDataTypeEnum
{
  kIfcTimeSeriesDataTypeEnum_CONTINUOUS,
  kIfcTimeSeriesDataTypeEnum_DISCRETE,
  kIfcTimeSeriesDataTypeEnum_DISCRETEBINARY,
  kIfcTimeSeriesDataTypeEnum_PIECEWISEBINARY,
  kIfcTimeSeriesDataTypeEnum_PIECEWISECONSTANT,
  kIfcTimeSeriesDataTypeEnum_PIECEWISECONTINUOUS,
  kIfcTimeSeriesDataTypeEnum_NOTDEFINED,
  kIfcTimeSeriesDataTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcTimeSeriesDataTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTimeSeriesDataTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcTimeSeriesDataTypeEnum& getUnset<OdIfc2x2_final::IfcTimeSeriesDataTypeEnum>() { static OdIfc2x2_final::IfcTimeSeriesDataTypeEnum nullEnum = OdIfc2x2_final::kIfcTimeSeriesDataTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcTimeSeriesScheduleTypeEnum
{
  kIfcTimeSeriesScheduleTypeEnum_ANNUAL,
  kIfcTimeSeriesScheduleTypeEnum_MONTHLY,
  kIfcTimeSeriesScheduleTypeEnum_WEEKLY,
  kIfcTimeSeriesScheduleTypeEnum_DAILY,
  kIfcTimeSeriesScheduleTypeEnum_USERDEFINED,
  kIfcTimeSeriesScheduleTypeEnum_NOTDEFINED,
  kIfcTimeSeriesScheduleTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcTimeSeriesScheduleTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTimeSeriesScheduleTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcTimeSeriesScheduleTypeEnum& getUnset<OdIfc2x2_final::IfcTimeSeriesScheduleTypeEnum>() { static OdIfc2x2_final::IfcTimeSeriesScheduleTypeEnum nullEnum = OdIfc2x2_final::kIfcTimeSeriesScheduleTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcTransformerTypeEnum
{
  kIfcTransformerTypeEnum_CURRENT,
  kIfcTransformerTypeEnum_FREQUENCY,
  kIfcTransformerTypeEnum_VOLTAGE,
  kIfcTransformerTypeEnum_USERDEFINED,
  kIfcTransformerTypeEnum_NOTDEFINED,
  kIfcTransformerTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcTransformerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTransformerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcTransformerTypeEnum& getUnset<OdIfc2x2_final::IfcTransformerTypeEnum>() { static OdIfc2x2_final::IfcTransformerTypeEnum nullEnum = OdIfc2x2_final::kIfcTransformerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcTransitionCode
{
  kIfcTransitionCode_DISCONTINUOUS,
  kIfcTransitionCode_CONTINUOUS,
  kIfcTransitionCode_CONTSAMEGRADIENT,
  kIfcTransitionCode_CONTSAMEGRADIENTSAMECURVATURE,
  kIfcTransitionCode_unset
};

class IFC2X2_FINAL_EXPORT IfcTransitionCodeTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTransitionCodeTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcTransitionCode& getUnset<OdIfc2x2_final::IfcTransitionCode>() { static OdIfc2x2_final::IfcTransitionCode nullEnum = OdIfc2x2_final::kIfcTransitionCode_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcTransportElementTypeEnum
{
  kIfcTransportElementTypeEnum_ELEVATOR,
  kIfcTransportElementTypeEnum_ESCALATOR,
  kIfcTransportElementTypeEnum_MOVINGWALKWAY,
  kIfcTransportElementTypeEnum_USERDEFINED,
  kIfcTransportElementTypeEnum_NOTDEFINED,
  kIfcTransportElementTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcTransportElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTransportElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcTransportElementTypeEnum& getUnset<OdIfc2x2_final::IfcTransportElementTypeEnum>() { static OdIfc2x2_final::IfcTransportElementTypeEnum nullEnum = OdIfc2x2_final::kIfcTransportElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcTrimmingPreference
{
  kIfcTrimmingPreference_CARTESIAN,
  kIfcTrimmingPreference_PARAMETER,
  kIfcTrimmingPreference_UNSPECIFIED,
  kIfcTrimmingPreference_unset
};

class IFC2X2_FINAL_EXPORT IfcTrimmingPreferenceTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTrimmingPreferenceTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcTrimmingPreference& getUnset<OdIfc2x2_final::IfcTrimmingPreference>() { static OdIfc2x2_final::IfcTrimmingPreference nullEnum = OdIfc2x2_final::kIfcTrimmingPreference_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcTubeBundleTypeEnum
{
  kIfcTubeBundleTypeEnum_FINNED,
  kIfcTubeBundleTypeEnum_USERDEFINED,
  kIfcTubeBundleTypeEnum_NOTDEFINED,
  kIfcTubeBundleTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcTubeBundleTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTubeBundleTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcTubeBundleTypeEnum& getUnset<OdIfc2x2_final::IfcTubeBundleTypeEnum>() { static OdIfc2x2_final::IfcTubeBundleTypeEnum nullEnum = OdIfc2x2_final::kIfcTubeBundleTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcUnitEnum
{
  kIfcUnitEnum_ABSORBEDDOSEUNIT,
  kIfcUnitEnum_AMOUNTOFSUBSTANCEUNIT,
  kIfcUnitEnum_AREAUNIT,
  kIfcUnitEnum_DOSEEQUIVALENTUNIT,
  kIfcUnitEnum_ELECTRICCAPACITANCEUNIT,
  kIfcUnitEnum_ELECTRICCHARGEUNIT,
  kIfcUnitEnum_ELECTRICCONDUCTANCEUNIT,
  kIfcUnitEnum_ELECTRICCURRENTUNIT,
  kIfcUnitEnum_ELECTRICRESISTANCEUNIT,
  kIfcUnitEnum_ELECTRICVOLTAGEUNIT,
  kIfcUnitEnum_ENERGYUNIT,
  kIfcUnitEnum_FORCEUNIT,
  kIfcUnitEnum_FREQUENCYUNIT,
  kIfcUnitEnum_ILLUMINANCEUNIT,
  kIfcUnitEnum_INDUCTANCEUNIT,
  kIfcUnitEnum_LENGTHUNIT,
  kIfcUnitEnum_LUMINOUSFLUXUNIT,
  kIfcUnitEnum_LUMINOUSINTENSITYUNIT,
  kIfcUnitEnum_MAGNETICFLUXDENSITYUNIT,
  kIfcUnitEnum_MAGNETICFLUXUNIT,
  kIfcUnitEnum_MASSUNIT,
  kIfcUnitEnum_PLANEANGLEUNIT,
  kIfcUnitEnum_POWERUNIT,
  kIfcUnitEnum_PRESSUREUNIT,
  kIfcUnitEnum_RADIOACTIVITYUNIT,
  kIfcUnitEnum_SOLIDANGLEUNIT,
  kIfcUnitEnum_THERMODYNAMICTEMPERATUREUNIT,
  kIfcUnitEnum_TIMEUNIT,
  kIfcUnitEnum_VOLUMEUNIT,
  kIfcUnitEnum_USERDEFINED,
  kIfcUnitEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcUnitEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcUnitEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcUnitEnum& getUnset<OdIfc2x2_final::IfcUnitEnum>() { static OdIfc2x2_final::IfcUnitEnum nullEnum = OdIfc2x2_final::kIfcUnitEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcUnitaryEquipmentTypeEnum
{
  kIfcUnitaryEquipmentTypeEnum_AIRHANDLER,
  kIfcUnitaryEquipmentTypeEnum_AIRCONDITIONINGUNIT,
  kIfcUnitaryEquipmentTypeEnum_SPLITSYSTEM,
  kIfcUnitaryEquipmentTypeEnum_ROOFTOPUNIT,
  kIfcUnitaryEquipmentTypeEnum_USERDEFINED,
  kIfcUnitaryEquipmentTypeEnum_NOTDEFINED,
  kIfcUnitaryEquipmentTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcUnitaryEquipmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcUnitaryEquipmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcUnitaryEquipmentTypeEnum& getUnset<OdIfc2x2_final::IfcUnitaryEquipmentTypeEnum>() { static OdIfc2x2_final::IfcUnitaryEquipmentTypeEnum nullEnum = OdIfc2x2_final::kIfcUnitaryEquipmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcValveTypeEnum
{
  kIfcValveTypeEnum_AIRRELEASE,
  kIfcValveTypeEnum_ANTIVACUUM,
  kIfcValveTypeEnum_CHANGEOVER,
  kIfcValveTypeEnum_CHECK,
  kIfcValveTypeEnum_COMMISSIONING,
  kIfcValveTypeEnum_DIVERTING,
  kIfcValveTypeEnum_DRAWOFFCOCK,
  kIfcValveTypeEnum_DOUBLECHECK,
  kIfcValveTypeEnum_DOUBLEREGULATING,
  kIfcValveTypeEnum_FAUCET,
  kIfcValveTypeEnum_FLUSHING,
  kIfcValveTypeEnum_GASCOCK,
  kIfcValveTypeEnum_GASTAP,
  kIfcValveTypeEnum_ISOLATING,
  kIfcValveTypeEnum_MIXING,
  kIfcValveTypeEnum_PRESSUREREDUCING,
  kIfcValveTypeEnum_PRESSURERELIEF,
  kIfcValveTypeEnum_REGULATING,
  kIfcValveTypeEnum_SAFETYCUTOFF,
  kIfcValveTypeEnum_STEAMTRAP,
  kIfcValveTypeEnum_STOPCOCK,
  kIfcValveTypeEnum_USERDEFINED,
  kIfcValveTypeEnum_NOTDEFINED,
  kIfcValveTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcValveTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcValveTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcValveTypeEnum& getUnset<OdIfc2x2_final::IfcValveTypeEnum>() { static OdIfc2x2_final::IfcValveTypeEnum nullEnum = OdIfc2x2_final::kIfcValveTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcVibrationIsolatorTypeEnum
{
  kIfcVibrationIsolatorTypeEnum_COMPRESSION,
  kIfcVibrationIsolatorTypeEnum_SPRING,
  kIfcVibrationIsolatorTypeEnum_USERDEFINED,
  kIfcVibrationIsolatorTypeEnum_NOTDEFINED,
  kIfcVibrationIsolatorTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcVibrationIsolatorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcVibrationIsolatorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcVibrationIsolatorTypeEnum& getUnset<OdIfc2x2_final::IfcVibrationIsolatorTypeEnum>() { static OdIfc2x2_final::IfcVibrationIsolatorTypeEnum nullEnum = OdIfc2x2_final::kIfcVibrationIsolatorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcWallTypeEnum
{
  kIfcWallTypeEnum_STANDARD,
  kIfcWallTypeEnum_POLYGONAL,
  kIfcWallTypeEnum_SHEAR,
  kIfcWallTypeEnum_USERDEFINED,
  kIfcWallTypeEnum_NOTDEFINED,
  kIfcWallTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcWallTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWallTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcWallTypeEnum& getUnset<OdIfc2x2_final::IfcWallTypeEnum>() { static OdIfc2x2_final::IfcWallTypeEnum nullEnum = OdIfc2x2_final::kIfcWallTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcWasteTerminalTypeEnum
{
  kIfcWasteTerminalTypeEnum_FLOORTRAP,
  kIfcWasteTerminalTypeEnum_FLOORWASTE,
  kIfcWasteTerminalTypeEnum_GULLYSUMP,
  kIfcWasteTerminalTypeEnum_GULLYTRAP,
  kIfcWasteTerminalTypeEnum_GREASEINTERCEPTOR,
  kIfcWasteTerminalTypeEnum_OILINTERCEPTOR,
  kIfcWasteTerminalTypeEnum_PETROLINTERCEPTOR,
  kIfcWasteTerminalTypeEnum_ROOFDRAIN,
  kIfcWasteTerminalTypeEnum_WASTEDISPOSALUNIT,
  kIfcWasteTerminalTypeEnum_WASTETRAP,
  kIfcWasteTerminalTypeEnum_USERDEFINED,
  kIfcWasteTerminalTypeEnum_NOTDEFINED,
  kIfcWasteTerminalTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcWasteTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWasteTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcWasteTerminalTypeEnum& getUnset<OdIfc2x2_final::IfcWasteTerminalTypeEnum>() { static OdIfc2x2_final::IfcWasteTerminalTypeEnum nullEnum = OdIfc2x2_final::kIfcWasteTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcWindowPanelOperationEnum
{
  kIfcWindowPanelOperationEnum_SIDEHUNGRIGHTHAND,
  kIfcWindowPanelOperationEnum_SIDEHUNGLEFTHAND,
  kIfcWindowPanelOperationEnum_TILTANDTURNRIGHTHAND,
  kIfcWindowPanelOperationEnum_TILTANDTURNLEFTHAND,
  kIfcWindowPanelOperationEnum_TOPHUNG,
  kIfcWindowPanelOperationEnum_BOTTOMHUNG,
  kIfcWindowPanelOperationEnum_PIVOTHORIZONTAL,
  kIfcWindowPanelOperationEnum_PIVOTVERTICAL,
  kIfcWindowPanelOperationEnum_SLIDINGHORIZONTAL,
  kIfcWindowPanelOperationEnum_SLIDINGVERTICAL,
  kIfcWindowPanelOperationEnum_REMOVABLECASEMENT,
  kIfcWindowPanelOperationEnum_FIXEDCASEMENT,
  kIfcWindowPanelOperationEnum_OTHEROPERATION,
  kIfcWindowPanelOperationEnum_NOTDEFINED,
  kIfcWindowPanelOperationEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcWindowPanelOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowPanelOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcWindowPanelOperationEnum& getUnset<OdIfc2x2_final::IfcWindowPanelOperationEnum>() { static OdIfc2x2_final::IfcWindowPanelOperationEnum nullEnum = OdIfc2x2_final::kIfcWindowPanelOperationEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcWindowPanelPositionEnum
{
  kIfcWindowPanelPositionEnum_LEFT,
  kIfcWindowPanelPositionEnum_MIDDLE,
  kIfcWindowPanelPositionEnum_RIGHT,
  kIfcWindowPanelPositionEnum_BOTTOM,
  kIfcWindowPanelPositionEnum_TOP,
  kIfcWindowPanelPositionEnum_NOTDEFINED,
  kIfcWindowPanelPositionEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcWindowPanelPositionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowPanelPositionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcWindowPanelPositionEnum& getUnset<OdIfc2x2_final::IfcWindowPanelPositionEnum>() { static OdIfc2x2_final::IfcWindowPanelPositionEnum nullEnum = OdIfc2x2_final::kIfcWindowPanelPositionEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcWindowStyleConstructionEnum
{
  kIfcWindowStyleConstructionEnum_ALUMINIUM,
  kIfcWindowStyleConstructionEnum_HIGH_GRADE_STEEL,
  kIfcWindowStyleConstructionEnum_STEEL,
  kIfcWindowStyleConstructionEnum_WOOD,
  kIfcWindowStyleConstructionEnum_ALUMINIUM_WOOD,
  kIfcWindowStyleConstructionEnum_PLASTIC,
  kIfcWindowStyleConstructionEnum_OTHER_CONSTRUCTION,
  kIfcWindowStyleConstructionEnum_NOTDEFINED,
  kIfcWindowStyleConstructionEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcWindowStyleConstructionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowStyleConstructionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcWindowStyleConstructionEnum& getUnset<OdIfc2x2_final::IfcWindowStyleConstructionEnum>() { static OdIfc2x2_final::IfcWindowStyleConstructionEnum nullEnum = OdIfc2x2_final::kIfcWindowStyleConstructionEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcWindowStyleOperationEnum
{
  kIfcWindowStyleOperationEnum_SINGLE_PANEL,
  kIfcWindowStyleOperationEnum_DOUBLE_PANEL_VERTICAL,
  kIfcWindowStyleOperationEnum_DOUBLE_PANEL_HORIZONTAL,
  kIfcWindowStyleOperationEnum_TRIPLE_PANEL_VERTICAL,
  kIfcWindowStyleOperationEnum_TRIPLE_PANEL_BOTTOM,
  kIfcWindowStyleOperationEnum_TRIPLE_PANEL_TOP,
  kIfcWindowStyleOperationEnum_TRIPLE_PANEL_LEFT,
  kIfcWindowStyleOperationEnum_TRIPLE_PANEL_RIGHT,
  kIfcWindowStyleOperationEnum_TRIPLE_PANEL_HORIZONTAL,
  kIfcWindowStyleOperationEnum_USERDEFINED,
  kIfcWindowStyleOperationEnum_NOTDEFINED,
  kIfcWindowStyleOperationEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcWindowStyleOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowStyleOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcWindowStyleOperationEnum& getUnset<OdIfc2x2_final::IfcWindowStyleOperationEnum>() { static OdIfc2x2_final::IfcWindowStyleOperationEnum nullEnum = OdIfc2x2_final::kIfcWindowStyleOperationEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {
enum IfcWorkControlTypeEnum
{
  kIfcWorkControlTypeEnum_ACTUAL,
  kIfcWorkControlTypeEnum_BASELINE,
  kIfcWorkControlTypeEnum_PLANNED,
  kIfcWorkControlTypeEnum_USERDEFINED,
  kIfcWorkControlTypeEnum_NOTDEFINED,
  kIfcWorkControlTypeEnum_unset
};

class IFC2X2_FINAL_EXPORT IfcWorkControlTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWorkControlTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x2_final::IfcWorkControlTypeEnum& getUnset<OdIfc2x2_final::IfcWorkControlTypeEnum>() { static OdIfc2x2_final::IfcWorkControlTypeEnum nullEnum = OdIfc2x2_final::kIfcWorkControlTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x2_final {

} // namespace

#endif // _IFC2X2_FINAL_ENUM_H

