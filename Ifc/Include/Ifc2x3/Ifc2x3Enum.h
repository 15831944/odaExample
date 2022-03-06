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

#ifndef _IFC2X3_ENUM_H
#define _IFC2X3_ENUM_H

#include "RxValue.h"
#include "daiEnum.h"
#include "Ifc2x3BuildOption.h"

namespace OdIfc2x3 {

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

class IFC2X3_EXPORT IfcActionSourceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcActionSourceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcActionSourceTypeEnum& getUnset<OdIfc2x3::IfcActionSourceTypeEnum>() { static OdIfc2x3::IfcActionSourceTypeEnum nullEnum = OdIfc2x3::kIfcActionSourceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcActionTypeEnum
{
  kIfcActionTypeEnum_PERMANENT_G,
  kIfcActionTypeEnum_VARIABLE_Q,
  kIfcActionTypeEnum_EXTRAORDINARY_A,
  kIfcActionTypeEnum_USERDEFINED,
  kIfcActionTypeEnum_NOTDEFINED,
  kIfcActionTypeEnum_unset
};

class IFC2X3_EXPORT IfcActionTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcActionTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcActionTypeEnum& getUnset<OdIfc2x3::IfcActionTypeEnum>() { static OdIfc2x3::IfcActionTypeEnum nullEnum = OdIfc2x3::kIfcActionTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcActuatorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcActuatorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcActuatorTypeEnum& getUnset<OdIfc2x3::IfcActuatorTypeEnum>() { static OdIfc2x3::IfcActuatorTypeEnum nullEnum = OdIfc2x3::kIfcActuatorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcAddressTypeEnum
{
  kIfcAddressTypeEnum_OFFICE,
  kIfcAddressTypeEnum_SITE,
  kIfcAddressTypeEnum_HOME,
  kIfcAddressTypeEnum_DISTRIBUTIONPOINT,
  kIfcAddressTypeEnum_USERDEFINED,
  kIfcAddressTypeEnum_unset
};

class IFC2X3_EXPORT IfcAddressTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAddressTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcAddressTypeEnum& getUnset<OdIfc2x3::IfcAddressTypeEnum>() { static OdIfc2x3::IfcAddressTypeEnum nullEnum = OdIfc2x3::kIfcAddressTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcAheadOrBehind
{
  kIfcAheadOrBehind_AHEAD,
  kIfcAheadOrBehind_BEHIND,
  kIfcAheadOrBehind_unset
};

class IFC2X3_EXPORT IfcAheadOrBehindTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAheadOrBehindTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcAheadOrBehind& getUnset<OdIfc2x3::IfcAheadOrBehind>() { static OdIfc2x3::IfcAheadOrBehind nullEnum = OdIfc2x3::kIfcAheadOrBehind_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcAirTerminalBoxTypeEnum
{
  kIfcAirTerminalBoxTypeEnum_CONSTANTFLOW,
  kIfcAirTerminalBoxTypeEnum_VARIABLEFLOWPRESSUREDEPENDANT,
  kIfcAirTerminalBoxTypeEnum_VARIABLEFLOWPRESSUREINDEPENDANT,
  kIfcAirTerminalBoxTypeEnum_USERDEFINED,
  kIfcAirTerminalBoxTypeEnum_NOTDEFINED,
  kIfcAirTerminalBoxTypeEnum_unset
};

class IFC2X3_EXPORT IfcAirTerminalBoxTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAirTerminalBoxTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcAirTerminalBoxTypeEnum& getUnset<OdIfc2x3::IfcAirTerminalBoxTypeEnum>() { static OdIfc2x3::IfcAirTerminalBoxTypeEnum nullEnum = OdIfc2x3::kIfcAirTerminalBoxTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcAirTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAirTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcAirTerminalTypeEnum& getUnset<OdIfc2x3::IfcAirTerminalTypeEnum>() { static OdIfc2x3::IfcAirTerminalTypeEnum nullEnum = OdIfc2x3::kIfcAirTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcAirToAirHeatRecoveryTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAirToAirHeatRecoveryTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcAirToAirHeatRecoveryTypeEnum& getUnset<OdIfc2x3::IfcAirToAirHeatRecoveryTypeEnum>() { static OdIfc2x3::IfcAirToAirHeatRecoveryTypeEnum nullEnum = OdIfc2x3::kIfcAirToAirHeatRecoveryTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcAlarmTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAlarmTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcAlarmTypeEnum& getUnset<OdIfc2x3::IfcAlarmTypeEnum>() { static OdIfc2x3::IfcAlarmTypeEnum nullEnum = OdIfc2x3::kIfcAlarmTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcAnalysisModelTypeEnum
{
  kIfcAnalysisModelTypeEnum_IN_PLANE_LOADING_2D,
  kIfcAnalysisModelTypeEnum_OUT_PLANE_LOADING_2D,
  kIfcAnalysisModelTypeEnum_LOADING_3D,
  kIfcAnalysisModelTypeEnum_USERDEFINED,
  kIfcAnalysisModelTypeEnum_NOTDEFINED,
  kIfcAnalysisModelTypeEnum_unset
};

class IFC2X3_EXPORT IfcAnalysisModelTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAnalysisModelTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcAnalysisModelTypeEnum& getUnset<OdIfc2x3::IfcAnalysisModelTypeEnum>() { static OdIfc2x3::IfcAnalysisModelTypeEnum nullEnum = OdIfc2x3::kIfcAnalysisModelTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcAnalysisTheoryTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAnalysisTheoryTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcAnalysisTheoryTypeEnum& getUnset<OdIfc2x3::IfcAnalysisTheoryTypeEnum>() { static OdIfc2x3::IfcAnalysisTheoryTypeEnum nullEnum = OdIfc2x3::kIfcAnalysisTheoryTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcArithmeticOperatorEnum
{
  kIfcArithmeticOperatorEnum_ADD,
  kIfcArithmeticOperatorEnum_DIVIDE,
  kIfcArithmeticOperatorEnum_MULTIPLY,
  kIfcArithmeticOperatorEnum_SUBTRACT,
  kIfcArithmeticOperatorEnum_unset
};

class IFC2X3_EXPORT IfcArithmeticOperatorEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcArithmeticOperatorEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcArithmeticOperatorEnum& getUnset<OdIfc2x3::IfcArithmeticOperatorEnum>() { static OdIfc2x3::IfcArithmeticOperatorEnum nullEnum = OdIfc2x3::kIfcArithmeticOperatorEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcAssemblyPlaceEnum
{
  kIfcAssemblyPlaceEnum_SITE,
  kIfcAssemblyPlaceEnum_FACTORY,
  kIfcAssemblyPlaceEnum_NOTDEFINED,
  kIfcAssemblyPlaceEnum_unset
};

class IFC2X3_EXPORT IfcAssemblyPlaceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAssemblyPlaceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcAssemblyPlaceEnum& getUnset<OdIfc2x3::IfcAssemblyPlaceEnum>() { static OdIfc2x3::IfcAssemblyPlaceEnum nullEnum = OdIfc2x3::kIfcAssemblyPlaceEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcBSplineCurveFormTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBSplineCurveFormTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcBSplineCurveForm& getUnset<OdIfc2x3::IfcBSplineCurveForm>() { static OdIfc2x3::IfcBSplineCurveForm nullEnum = OdIfc2x3::kIfcBSplineCurveForm_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcBeamTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBeamTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcBeamTypeEnum& getUnset<OdIfc2x3::IfcBeamTypeEnum>() { static OdIfc2x3::IfcBeamTypeEnum nullEnum = OdIfc2x3::kIfcBeamTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcBenchmarkEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBenchmarkEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcBenchmarkEnum& getUnset<OdIfc2x3::IfcBenchmarkEnum>() { static OdIfc2x3::IfcBenchmarkEnum nullEnum = OdIfc2x3::kIfcBenchmarkEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcBoilerTypeEnum
{
  kIfcBoilerTypeEnum_WATER,
  kIfcBoilerTypeEnum_STEAM,
  kIfcBoilerTypeEnum_USERDEFINED,
  kIfcBoilerTypeEnum_NOTDEFINED,
  kIfcBoilerTypeEnum_unset
};

class IFC2X3_EXPORT IfcBoilerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBoilerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcBoilerTypeEnum& getUnset<OdIfc2x3::IfcBoilerTypeEnum>() { static OdIfc2x3::IfcBoilerTypeEnum nullEnum = OdIfc2x3::kIfcBoilerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcBooleanOperator
{
  kIfcBooleanOperator_UNION,
  kIfcBooleanOperator_INTERSECTION,
  kIfcBooleanOperator_DIFFERENCE,
  kIfcBooleanOperator_unset
};

class IFC2X3_EXPORT IfcBooleanOperatorTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBooleanOperatorTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcBooleanOperator& getUnset<OdIfc2x3::IfcBooleanOperator>() { static OdIfc2x3::IfcBooleanOperator nullEnum = OdIfc2x3::kIfcBooleanOperator_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcBuildingElementProxyTypeEnum
{
  kIfcBuildingElementProxyTypeEnum_USERDEFINED,
  kIfcBuildingElementProxyTypeEnum_NOTDEFINED,
  kIfcBuildingElementProxyTypeEnum_unset
};

class IFC2X3_EXPORT IfcBuildingElementProxyTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBuildingElementProxyTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcBuildingElementProxyTypeEnum& getUnset<OdIfc2x3::IfcBuildingElementProxyTypeEnum>() { static OdIfc2x3::IfcBuildingElementProxyTypeEnum nullEnum = OdIfc2x3::kIfcBuildingElementProxyTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcCableCarrierFittingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCableCarrierFittingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcCableCarrierFittingTypeEnum& getUnset<OdIfc2x3::IfcCableCarrierFittingTypeEnum>() { static OdIfc2x3::IfcCableCarrierFittingTypeEnum nullEnum = OdIfc2x3::kIfcCableCarrierFittingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcCableCarrierSegmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCableCarrierSegmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcCableCarrierSegmentTypeEnum& getUnset<OdIfc2x3::IfcCableCarrierSegmentTypeEnum>() { static OdIfc2x3::IfcCableCarrierSegmentTypeEnum nullEnum = OdIfc2x3::kIfcCableCarrierSegmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcCableSegmentTypeEnum
{
  kIfcCableSegmentTypeEnum_CABLESEGMENT,
  kIfcCableSegmentTypeEnum_CONDUCTORSEGMENT,
  kIfcCableSegmentTypeEnum_USERDEFINED,
  kIfcCableSegmentTypeEnum_NOTDEFINED,
  kIfcCableSegmentTypeEnum_unset
};

class IFC2X3_EXPORT IfcCableSegmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCableSegmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcCableSegmentTypeEnum& getUnset<OdIfc2x3::IfcCableSegmentTypeEnum>() { static OdIfc2x3::IfcCableSegmentTypeEnum nullEnum = OdIfc2x3::kIfcCableSegmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcChangeActionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcChangeActionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcChangeActionEnum& getUnset<OdIfc2x3::IfcChangeActionEnum>() { static OdIfc2x3::IfcChangeActionEnum nullEnum = OdIfc2x3::kIfcChangeActionEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcChillerTypeEnum
{
  kIfcChillerTypeEnum_AIRCOOLED,
  kIfcChillerTypeEnum_WATERCOOLED,
  kIfcChillerTypeEnum_HEATRECOVERY,
  kIfcChillerTypeEnum_USERDEFINED,
  kIfcChillerTypeEnum_NOTDEFINED,
  kIfcChillerTypeEnum_unset
};

class IFC2X3_EXPORT IfcChillerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcChillerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcChillerTypeEnum& getUnset<OdIfc2x3::IfcChillerTypeEnum>() { static OdIfc2x3::IfcChillerTypeEnum nullEnum = OdIfc2x3::kIfcChillerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcCoilTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCoilTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcCoilTypeEnum& getUnset<OdIfc2x3::IfcCoilTypeEnum>() { static OdIfc2x3::IfcCoilTypeEnum nullEnum = OdIfc2x3::kIfcCoilTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcColumnTypeEnum
{
  kIfcColumnTypeEnum_COLUMN,
  kIfcColumnTypeEnum_USERDEFINED,
  kIfcColumnTypeEnum_NOTDEFINED,
  kIfcColumnTypeEnum_unset
};

class IFC2X3_EXPORT IfcColumnTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcColumnTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcColumnTypeEnum& getUnset<OdIfc2x3::IfcColumnTypeEnum>() { static OdIfc2x3::IfcColumnTypeEnum nullEnum = OdIfc2x3::kIfcColumnTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcCompressorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCompressorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcCompressorTypeEnum& getUnset<OdIfc2x3::IfcCompressorTypeEnum>() { static OdIfc2x3::IfcCompressorTypeEnum nullEnum = OdIfc2x3::kIfcCompressorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcCondenserTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCondenserTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcCondenserTypeEnum& getUnset<OdIfc2x3::IfcCondenserTypeEnum>() { static OdIfc2x3::IfcCondenserTypeEnum nullEnum = OdIfc2x3::kIfcCondenserTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcConnectionTypeEnum
{
  kIfcConnectionTypeEnum_ATPATH,
  kIfcConnectionTypeEnum_ATSTART,
  kIfcConnectionTypeEnum_ATEND,
  kIfcConnectionTypeEnum_NOTDEFINED,
  kIfcConnectionTypeEnum_unset
};

class IFC2X3_EXPORT IfcConnectionTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcConnectionTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcConnectionTypeEnum& getUnset<OdIfc2x3::IfcConnectionTypeEnum>() { static OdIfc2x3::IfcConnectionTypeEnum nullEnum = OdIfc2x3::kIfcConnectionTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcConstraintEnum
{
  kIfcConstraintEnum_HARD,
  kIfcConstraintEnum_SOFT,
  kIfcConstraintEnum_ADVISORY,
  kIfcConstraintEnum_USERDEFINED,
  kIfcConstraintEnum_NOTDEFINED,
  kIfcConstraintEnum_unset
};

class IFC2X3_EXPORT IfcConstraintEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcConstraintEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcConstraintEnum& getUnset<OdIfc2x3::IfcConstraintEnum>() { static OdIfc2x3::IfcConstraintEnum nullEnum = OdIfc2x3::kIfcConstraintEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcControllerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcControllerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcControllerTypeEnum& getUnset<OdIfc2x3::IfcControllerTypeEnum>() { static OdIfc2x3::IfcControllerTypeEnum nullEnum = OdIfc2x3::kIfcControllerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcCooledBeamTypeEnum
{
  kIfcCooledBeamTypeEnum_ACTIVE,
  kIfcCooledBeamTypeEnum_PASSIVE,
  kIfcCooledBeamTypeEnum_USERDEFINED,
  kIfcCooledBeamTypeEnum_NOTDEFINED,
  kIfcCooledBeamTypeEnum_unset
};

class IFC2X3_EXPORT IfcCooledBeamTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCooledBeamTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcCooledBeamTypeEnum& getUnset<OdIfc2x3::IfcCooledBeamTypeEnum>() { static OdIfc2x3::IfcCooledBeamTypeEnum nullEnum = OdIfc2x3::kIfcCooledBeamTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcCoolingTowerTypeEnum
{
  kIfcCoolingTowerTypeEnum_NATURALDRAFT,
  kIfcCoolingTowerTypeEnum_MECHANICALINDUCEDDRAFT,
  kIfcCoolingTowerTypeEnum_MECHANICALFORCEDDRAFT,
  kIfcCoolingTowerTypeEnum_USERDEFINED,
  kIfcCoolingTowerTypeEnum_NOTDEFINED,
  kIfcCoolingTowerTypeEnum_unset
};

class IFC2X3_EXPORT IfcCoolingTowerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCoolingTowerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcCoolingTowerTypeEnum& getUnset<OdIfc2x3::IfcCoolingTowerTypeEnum>() { static OdIfc2x3::IfcCoolingTowerTypeEnum nullEnum = OdIfc2x3::kIfcCoolingTowerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcCostScheduleTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCostScheduleTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcCostScheduleTypeEnum& getUnset<OdIfc2x3::IfcCostScheduleTypeEnum>() { static OdIfc2x3::IfcCostScheduleTypeEnum nullEnum = OdIfc2x3::kIfcCostScheduleTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcCoveringTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCoveringTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcCoveringTypeEnum& getUnset<OdIfc2x3::IfcCoveringTypeEnum>() { static OdIfc2x3::IfcCoveringTypeEnum nullEnum = OdIfc2x3::kIfcCoveringTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcCurrencyEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCurrencyEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcCurrencyEnum& getUnset<OdIfc2x3::IfcCurrencyEnum>() { static OdIfc2x3::IfcCurrencyEnum nullEnum = OdIfc2x3::kIfcCurrencyEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcCurtainWallTypeEnum
{
  kIfcCurtainWallTypeEnum_USERDEFINED,
  kIfcCurtainWallTypeEnum_NOTDEFINED,
  kIfcCurtainWallTypeEnum_unset
};

class IFC2X3_EXPORT IfcCurtainWallTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCurtainWallTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcCurtainWallTypeEnum& getUnset<OdIfc2x3::IfcCurtainWallTypeEnum>() { static OdIfc2x3::IfcCurtainWallTypeEnum nullEnum = OdIfc2x3::kIfcCurtainWallTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcDamperTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDamperTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcDamperTypeEnum& getUnset<OdIfc2x3::IfcDamperTypeEnum>() { static OdIfc2x3::IfcDamperTypeEnum nullEnum = OdIfc2x3::kIfcDamperTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcDataOriginEnum
{
  kIfcDataOriginEnum_MEASURED,
  kIfcDataOriginEnum_PREDICTED,
  kIfcDataOriginEnum_SIMULATED,
  kIfcDataOriginEnum_USERDEFINED,
  kIfcDataOriginEnum_NOTDEFINED,
  kIfcDataOriginEnum_unset
};

class IFC2X3_EXPORT IfcDataOriginEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDataOriginEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcDataOriginEnum& getUnset<OdIfc2x3::IfcDataOriginEnum>() { static OdIfc2x3::IfcDataOriginEnum nullEnum = OdIfc2x3::kIfcDataOriginEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcDerivedUnitEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDerivedUnitEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcDerivedUnitEnum& getUnset<OdIfc2x3::IfcDerivedUnitEnum>() { static OdIfc2x3::IfcDerivedUnitEnum nullEnum = OdIfc2x3::kIfcDerivedUnitEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcDimensionExtentUsage
{
  kIfcDimensionExtentUsage_ORIGIN,
  kIfcDimensionExtentUsage_TARGET,
  kIfcDimensionExtentUsage_unset
};

class IFC2X3_EXPORT IfcDimensionExtentUsageTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDimensionExtentUsageTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcDimensionExtentUsage& getUnset<OdIfc2x3::IfcDimensionExtentUsage>() { static OdIfc2x3::IfcDimensionExtentUsage nullEnum = OdIfc2x3::kIfcDimensionExtentUsage_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcDirectionSenseEnum
{
  kIfcDirectionSenseEnum_POSITIVE,
  kIfcDirectionSenseEnum_NEGATIVE,
  kIfcDirectionSenseEnum_unset
};

class IFC2X3_EXPORT IfcDirectionSenseEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDirectionSenseEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcDirectionSenseEnum& getUnset<OdIfc2x3::IfcDirectionSenseEnum>() { static OdIfc2x3::IfcDirectionSenseEnum nullEnum = OdIfc2x3::kIfcDirectionSenseEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcDistributionChamberElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDistributionChamberElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcDistributionChamberElementTypeEnum& getUnset<OdIfc2x3::IfcDistributionChamberElementTypeEnum>() { static OdIfc2x3::IfcDistributionChamberElementTypeEnum nullEnum = OdIfc2x3::kIfcDistributionChamberElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcDocumentConfidentialityEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDocumentConfidentialityEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcDocumentConfidentialityEnum& getUnset<OdIfc2x3::IfcDocumentConfidentialityEnum>() { static OdIfc2x3::IfcDocumentConfidentialityEnum nullEnum = OdIfc2x3::kIfcDocumentConfidentialityEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcDocumentStatusEnum
{
  kIfcDocumentStatusEnum_DRAFT,
  kIfcDocumentStatusEnum_FINALDRAFT,
  kIfcDocumentStatusEnum_FINAL,
  kIfcDocumentStatusEnum_REVISION,
  kIfcDocumentStatusEnum_NOTDEFINED,
  kIfcDocumentStatusEnum_unset
};

class IFC2X3_EXPORT IfcDocumentStatusEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDocumentStatusEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcDocumentStatusEnum& getUnset<OdIfc2x3::IfcDocumentStatusEnum>() { static OdIfc2x3::IfcDocumentStatusEnum nullEnum = OdIfc2x3::kIfcDocumentStatusEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcDoorPanelOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorPanelOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcDoorPanelOperationEnum& getUnset<OdIfc2x3::IfcDoorPanelOperationEnum>() { static OdIfc2x3::IfcDoorPanelOperationEnum nullEnum = OdIfc2x3::kIfcDoorPanelOperationEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcDoorPanelPositionEnum
{
  kIfcDoorPanelPositionEnum_LEFT,
  kIfcDoorPanelPositionEnum_MIDDLE,
  kIfcDoorPanelPositionEnum_RIGHT,
  kIfcDoorPanelPositionEnum_NOTDEFINED,
  kIfcDoorPanelPositionEnum_unset
};

class IFC2X3_EXPORT IfcDoorPanelPositionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorPanelPositionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcDoorPanelPositionEnum& getUnset<OdIfc2x3::IfcDoorPanelPositionEnum>() { static OdIfc2x3::IfcDoorPanelPositionEnum nullEnum = OdIfc2x3::kIfcDoorPanelPositionEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcDoorStyleConstructionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorStyleConstructionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcDoorStyleConstructionEnum& getUnset<OdIfc2x3::IfcDoorStyleConstructionEnum>() { static OdIfc2x3::IfcDoorStyleConstructionEnum nullEnum = OdIfc2x3::kIfcDoorStyleConstructionEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcDoorStyleOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorStyleOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcDoorStyleOperationEnum& getUnset<OdIfc2x3::IfcDoorStyleOperationEnum>() { static OdIfc2x3::IfcDoorStyleOperationEnum nullEnum = OdIfc2x3::kIfcDoorStyleOperationEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcDuctFittingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDuctFittingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcDuctFittingTypeEnum& getUnset<OdIfc2x3::IfcDuctFittingTypeEnum>() { static OdIfc2x3::IfcDuctFittingTypeEnum nullEnum = OdIfc2x3::kIfcDuctFittingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcDuctSegmentTypeEnum
{
  kIfcDuctSegmentTypeEnum_RIGIDSEGMENT,
  kIfcDuctSegmentTypeEnum_FLEXIBLESEGMENT,
  kIfcDuctSegmentTypeEnum_USERDEFINED,
  kIfcDuctSegmentTypeEnum_NOTDEFINED,
  kIfcDuctSegmentTypeEnum_unset
};

class IFC2X3_EXPORT IfcDuctSegmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDuctSegmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcDuctSegmentTypeEnum& getUnset<OdIfc2x3::IfcDuctSegmentTypeEnum>() { static OdIfc2x3::IfcDuctSegmentTypeEnum nullEnum = OdIfc2x3::kIfcDuctSegmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcDuctSilencerTypeEnum
{
  kIfcDuctSilencerTypeEnum_FLATOVAL,
  kIfcDuctSilencerTypeEnum_RECTANGULAR,
  kIfcDuctSilencerTypeEnum_ROUND,
  kIfcDuctSilencerTypeEnum_USERDEFINED,
  kIfcDuctSilencerTypeEnum_NOTDEFINED,
  kIfcDuctSilencerTypeEnum_unset
};

class IFC2X3_EXPORT IfcDuctSilencerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDuctSilencerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcDuctSilencerTypeEnum& getUnset<OdIfc2x3::IfcDuctSilencerTypeEnum>() { static OdIfc2x3::IfcDuctSilencerTypeEnum nullEnum = OdIfc2x3::kIfcDuctSilencerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcElectricApplianceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricApplianceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcElectricApplianceTypeEnum& getUnset<OdIfc2x3::IfcElectricApplianceTypeEnum>() { static OdIfc2x3::IfcElectricApplianceTypeEnum nullEnum = OdIfc2x3::kIfcElectricApplianceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcElectricCurrentEnum
{
  kIfcElectricCurrentEnum_ALTERNATING,
  kIfcElectricCurrentEnum_DIRECT,
  kIfcElectricCurrentEnum_NOTDEFINED,
  kIfcElectricCurrentEnum_unset
};

class IFC2X3_EXPORT IfcElectricCurrentEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricCurrentEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcElectricCurrentEnum& getUnset<OdIfc2x3::IfcElectricCurrentEnum>() { static OdIfc2x3::IfcElectricCurrentEnum nullEnum = OdIfc2x3::kIfcElectricCurrentEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcElectricDistributionPointFunctionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricDistributionPointFunctionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcElectricDistributionPointFunctionEnum& getUnset<OdIfc2x3::IfcElectricDistributionPointFunctionEnum>() { static OdIfc2x3::IfcElectricDistributionPointFunctionEnum nullEnum = OdIfc2x3::kIfcElectricDistributionPointFunctionEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcElectricFlowStorageDeviceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricFlowStorageDeviceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcElectricFlowStorageDeviceTypeEnum& getUnset<OdIfc2x3::IfcElectricFlowStorageDeviceTypeEnum>() { static OdIfc2x3::IfcElectricFlowStorageDeviceTypeEnum nullEnum = OdIfc2x3::kIfcElectricFlowStorageDeviceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcElectricGeneratorTypeEnum
{
  kIfcElectricGeneratorTypeEnum_USERDEFINED,
  kIfcElectricGeneratorTypeEnum_NOTDEFINED,
  kIfcElectricGeneratorTypeEnum_unset
};

class IFC2X3_EXPORT IfcElectricGeneratorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricGeneratorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcElectricGeneratorTypeEnum& getUnset<OdIfc2x3::IfcElectricGeneratorTypeEnum>() { static OdIfc2x3::IfcElectricGeneratorTypeEnum nullEnum = OdIfc2x3::kIfcElectricGeneratorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcElectricHeaterTypeEnum
{
  kIfcElectricHeaterTypeEnum_ELECTRICPOINTHEATER,
  kIfcElectricHeaterTypeEnum_ELECTRICCABLEHEATER,
  kIfcElectricHeaterTypeEnum_ELECTRICMATHEATER,
  kIfcElectricHeaterTypeEnum_USERDEFINED,
  kIfcElectricHeaterTypeEnum_NOTDEFINED,
  kIfcElectricHeaterTypeEnum_unset
};

class IFC2X3_EXPORT IfcElectricHeaterTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricHeaterTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcElectricHeaterTypeEnum& getUnset<OdIfc2x3::IfcElectricHeaterTypeEnum>() { static OdIfc2x3::IfcElectricHeaterTypeEnum nullEnum = OdIfc2x3::kIfcElectricHeaterTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcElectricMotorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricMotorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcElectricMotorTypeEnum& getUnset<OdIfc2x3::IfcElectricMotorTypeEnum>() { static OdIfc2x3::IfcElectricMotorTypeEnum nullEnum = OdIfc2x3::kIfcElectricMotorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcElectricTimeControlTypeEnum
{
  kIfcElectricTimeControlTypeEnum_TIMECLOCK,
  kIfcElectricTimeControlTypeEnum_TIMEDELAY,
  kIfcElectricTimeControlTypeEnum_RELAY,
  kIfcElectricTimeControlTypeEnum_USERDEFINED,
  kIfcElectricTimeControlTypeEnum_NOTDEFINED,
  kIfcElectricTimeControlTypeEnum_unset
};

class IFC2X3_EXPORT IfcElectricTimeControlTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricTimeControlTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcElectricTimeControlTypeEnum& getUnset<OdIfc2x3::IfcElectricTimeControlTypeEnum>() { static OdIfc2x3::IfcElectricTimeControlTypeEnum nullEnum = OdIfc2x3::kIfcElectricTimeControlTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcElementAssemblyTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElementAssemblyTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcElementAssemblyTypeEnum& getUnset<OdIfc2x3::IfcElementAssemblyTypeEnum>() { static OdIfc2x3::IfcElementAssemblyTypeEnum nullEnum = OdIfc2x3::kIfcElementAssemblyTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcElementCompositionEnum
{
  kIfcElementCompositionEnum_COMPLEX,
  kIfcElementCompositionEnum_ELEMENT,
  kIfcElementCompositionEnum_PARTIAL,
  kIfcElementCompositionEnum_unset
};

class IFC2X3_EXPORT IfcElementCompositionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElementCompositionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcElementCompositionEnum& getUnset<OdIfc2x3::IfcElementCompositionEnum>() { static OdIfc2x3::IfcElementCompositionEnum nullEnum = OdIfc2x3::kIfcElementCompositionEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcEnergySequenceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcEnergySequenceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcEnergySequenceEnum& getUnset<OdIfc2x3::IfcEnergySequenceEnum>() { static OdIfc2x3::IfcEnergySequenceEnum nullEnum = OdIfc2x3::kIfcEnergySequenceEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcEnvironmentalImpactCategoryEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcEnvironmentalImpactCategoryEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcEnvironmentalImpactCategoryEnum& getUnset<OdIfc2x3::IfcEnvironmentalImpactCategoryEnum>() { static OdIfc2x3::IfcEnvironmentalImpactCategoryEnum nullEnum = OdIfc2x3::kIfcEnvironmentalImpactCategoryEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcEvaporativeCoolerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcEvaporativeCoolerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcEvaporativeCoolerTypeEnum& getUnset<OdIfc2x3::IfcEvaporativeCoolerTypeEnum>() { static OdIfc2x3::IfcEvaporativeCoolerTypeEnum nullEnum = OdIfc2x3::kIfcEvaporativeCoolerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcEvaporatorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcEvaporatorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcEvaporatorTypeEnum& getUnset<OdIfc2x3::IfcEvaporatorTypeEnum>() { static OdIfc2x3::IfcEvaporatorTypeEnum nullEnum = OdIfc2x3::kIfcEvaporatorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcFanTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFanTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcFanTypeEnum& getUnset<OdIfc2x3::IfcFanTypeEnum>() { static OdIfc2x3::IfcFanTypeEnum nullEnum = OdIfc2x3::kIfcFanTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcFilterTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFilterTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcFilterTypeEnum& getUnset<OdIfc2x3::IfcFilterTypeEnum>() { static OdIfc2x3::IfcFilterTypeEnum nullEnum = OdIfc2x3::kIfcFilterTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcFireSuppressionTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFireSuppressionTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcFireSuppressionTerminalTypeEnum& getUnset<OdIfc2x3::IfcFireSuppressionTerminalTypeEnum>() { static OdIfc2x3::IfcFireSuppressionTerminalTypeEnum nullEnum = OdIfc2x3::kIfcFireSuppressionTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcFlowDirectionEnum
{
  kIfcFlowDirectionEnum_SOURCE,
  kIfcFlowDirectionEnum_SINK,
  kIfcFlowDirectionEnum_SOURCEANDSINK,
  kIfcFlowDirectionEnum_NOTDEFINED,
  kIfcFlowDirectionEnum_unset
};

class IFC2X3_EXPORT IfcFlowDirectionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFlowDirectionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcFlowDirectionEnum& getUnset<OdIfc2x3::IfcFlowDirectionEnum>() { static OdIfc2x3::IfcFlowDirectionEnum nullEnum = OdIfc2x3::kIfcFlowDirectionEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcFlowInstrumentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFlowInstrumentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcFlowInstrumentTypeEnum& getUnset<OdIfc2x3::IfcFlowInstrumentTypeEnum>() { static OdIfc2x3::IfcFlowInstrumentTypeEnum nullEnum = OdIfc2x3::kIfcFlowInstrumentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcFlowMeterTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFlowMeterTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcFlowMeterTypeEnum& getUnset<OdIfc2x3::IfcFlowMeterTypeEnum>() { static OdIfc2x3::IfcFlowMeterTypeEnum nullEnum = OdIfc2x3::kIfcFlowMeterTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcFootingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFootingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcFootingTypeEnum& getUnset<OdIfc2x3::IfcFootingTypeEnum>() { static OdIfc2x3::IfcFootingTypeEnum nullEnum = OdIfc2x3::kIfcFootingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcGasTerminalTypeEnum
{
  kIfcGasTerminalTypeEnum_GASAPPLIANCE,
  kIfcGasTerminalTypeEnum_GASBOOSTER,
  kIfcGasTerminalTypeEnum_GASBURNER,
  kIfcGasTerminalTypeEnum_USERDEFINED,
  kIfcGasTerminalTypeEnum_NOTDEFINED,
  kIfcGasTerminalTypeEnum_unset
};

class IFC2X3_EXPORT IfcGasTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcGasTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcGasTerminalTypeEnum& getUnset<OdIfc2x3::IfcGasTerminalTypeEnum>() { static OdIfc2x3::IfcGasTerminalTypeEnum nullEnum = OdIfc2x3::kIfcGasTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcGeometricProjectionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcGeometricProjectionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcGeometricProjectionEnum& getUnset<OdIfc2x3::IfcGeometricProjectionEnum>() { static OdIfc2x3::IfcGeometricProjectionEnum nullEnum = OdIfc2x3::kIfcGeometricProjectionEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcGlobalOrLocalEnum
{
  kIfcGlobalOrLocalEnum_GLOBAL_COORDS,
  kIfcGlobalOrLocalEnum_LOCAL_COORDS,
  kIfcGlobalOrLocalEnum_unset
};

class IFC2X3_EXPORT IfcGlobalOrLocalEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcGlobalOrLocalEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcGlobalOrLocalEnum& getUnset<OdIfc2x3::IfcGlobalOrLocalEnum>() { static OdIfc2x3::IfcGlobalOrLocalEnum nullEnum = OdIfc2x3::kIfcGlobalOrLocalEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcHeatExchangerTypeEnum
{
  kIfcHeatExchangerTypeEnum_PLATE,
  kIfcHeatExchangerTypeEnum_SHELLANDTUBE,
  kIfcHeatExchangerTypeEnum_USERDEFINED,
  kIfcHeatExchangerTypeEnum_NOTDEFINED,
  kIfcHeatExchangerTypeEnum_unset
};

class IFC2X3_EXPORT IfcHeatExchangerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcHeatExchangerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcHeatExchangerTypeEnum& getUnset<OdIfc2x3::IfcHeatExchangerTypeEnum>() { static OdIfc2x3::IfcHeatExchangerTypeEnum nullEnum = OdIfc2x3::kIfcHeatExchangerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcHumidifierTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcHumidifierTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcHumidifierTypeEnum& getUnset<OdIfc2x3::IfcHumidifierTypeEnum>() { static OdIfc2x3::IfcHumidifierTypeEnum nullEnum = OdIfc2x3::kIfcHumidifierTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcInternalOrExternalEnum
{
  kIfcInternalOrExternalEnum_INTERNAL,
  kIfcInternalOrExternalEnum_EXTERNAL,
  kIfcInternalOrExternalEnum_NOTDEFINED,
  kIfcInternalOrExternalEnum_unset
};

class IFC2X3_EXPORT IfcInternalOrExternalEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcInternalOrExternalEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcInternalOrExternalEnum& getUnset<OdIfc2x3::IfcInternalOrExternalEnum>() { static OdIfc2x3::IfcInternalOrExternalEnum nullEnum = OdIfc2x3::kIfcInternalOrExternalEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcInventoryTypeEnum
{
  kIfcInventoryTypeEnum_ASSETINVENTORY,
  kIfcInventoryTypeEnum_SPACEINVENTORY,
  kIfcInventoryTypeEnum_FURNITUREINVENTORY,
  kIfcInventoryTypeEnum_USERDEFINED,
  kIfcInventoryTypeEnum_NOTDEFINED,
  kIfcInventoryTypeEnum_unset
};

class IFC2X3_EXPORT IfcInventoryTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcInventoryTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcInventoryTypeEnum& getUnset<OdIfc2x3::IfcInventoryTypeEnum>() { static OdIfc2x3::IfcInventoryTypeEnum nullEnum = OdIfc2x3::kIfcInventoryTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcJunctionBoxTypeEnum
{
  kIfcJunctionBoxTypeEnum_USERDEFINED,
  kIfcJunctionBoxTypeEnum_NOTDEFINED,
  kIfcJunctionBoxTypeEnum_unset
};

class IFC2X3_EXPORT IfcJunctionBoxTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcJunctionBoxTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcJunctionBoxTypeEnum& getUnset<OdIfc2x3::IfcJunctionBoxTypeEnum>() { static OdIfc2x3::IfcJunctionBoxTypeEnum nullEnum = OdIfc2x3::kIfcJunctionBoxTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcLampTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLampTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcLampTypeEnum& getUnset<OdIfc2x3::IfcLampTypeEnum>() { static OdIfc2x3::IfcLampTypeEnum nullEnum = OdIfc2x3::kIfcLampTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcLayerSetDirectionEnum
{
  kIfcLayerSetDirectionEnum_AXIS1,
  kIfcLayerSetDirectionEnum_AXIS2,
  kIfcLayerSetDirectionEnum_AXIS3,
  kIfcLayerSetDirectionEnum_unset
};

class IFC2X3_EXPORT IfcLayerSetDirectionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLayerSetDirectionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcLayerSetDirectionEnum& getUnset<OdIfc2x3::IfcLayerSetDirectionEnum>() { static OdIfc2x3::IfcLayerSetDirectionEnum nullEnum = OdIfc2x3::kIfcLayerSetDirectionEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcLightDistributionCurveEnum
{
  kIfcLightDistributionCurveEnum_TYPE_A,
  kIfcLightDistributionCurveEnum_TYPE_B,
  kIfcLightDistributionCurveEnum_TYPE_C,
  kIfcLightDistributionCurveEnum_NOTDEFINED,
  kIfcLightDistributionCurveEnum_unset
};

class IFC2X3_EXPORT IfcLightDistributionCurveEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLightDistributionCurveEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcLightDistributionCurveEnum& getUnset<OdIfc2x3::IfcLightDistributionCurveEnum>() { static OdIfc2x3::IfcLightDistributionCurveEnum nullEnum = OdIfc2x3::kIfcLightDistributionCurveEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcLightEmissionSourceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLightEmissionSourceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcLightEmissionSourceEnum& getUnset<OdIfc2x3::IfcLightEmissionSourceEnum>() { static OdIfc2x3::IfcLightEmissionSourceEnum nullEnum = OdIfc2x3::kIfcLightEmissionSourceEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcLightFixtureTypeEnum
{
  kIfcLightFixtureTypeEnum_POINTSOURCE,
  kIfcLightFixtureTypeEnum_DIRECTIONSOURCE,
  kIfcLightFixtureTypeEnum_USERDEFINED,
  kIfcLightFixtureTypeEnum_NOTDEFINED,
  kIfcLightFixtureTypeEnum_unset
};

class IFC2X3_EXPORT IfcLightFixtureTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLightFixtureTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcLightFixtureTypeEnum& getUnset<OdIfc2x3::IfcLightFixtureTypeEnum>() { static OdIfc2x3::IfcLightFixtureTypeEnum nullEnum = OdIfc2x3::kIfcLightFixtureTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcLoadGroupTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLoadGroupTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcLoadGroupTypeEnum& getUnset<OdIfc2x3::IfcLoadGroupTypeEnum>() { static OdIfc2x3::IfcLoadGroupTypeEnum nullEnum = OdIfc2x3::kIfcLoadGroupTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcLogicalOperatorEnum
{
  kIfcLogicalOperatorEnum_LOGICALAND,
  kIfcLogicalOperatorEnum_LOGICALOR,
  kIfcLogicalOperatorEnum_unset
};

class IFC2X3_EXPORT IfcLogicalOperatorEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLogicalOperatorEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcLogicalOperatorEnum& getUnset<OdIfc2x3::IfcLogicalOperatorEnum>() { static OdIfc2x3::IfcLogicalOperatorEnum nullEnum = OdIfc2x3::kIfcLogicalOperatorEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcMemberTypeEnum
{
  kIfcMemberTypeEnum_BRACE,
  kIfcMemberTypeEnum_CHORD,
  kIfcMemberTypeEnum_COLLAR,
  kIfcMemberTypeEnum_MEMBER,
  kIfcMemberTypeEnum_MULLION,
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

class IFC2X3_EXPORT IfcMemberTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMemberTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcMemberTypeEnum& getUnset<OdIfc2x3::IfcMemberTypeEnum>() { static OdIfc2x3::IfcMemberTypeEnum nullEnum = OdIfc2x3::kIfcMemberTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcMotorConnectionTypeEnum
{
  kIfcMotorConnectionTypeEnum_BELTDRIVE,
  kIfcMotorConnectionTypeEnum_COUPLING,
  kIfcMotorConnectionTypeEnum_DIRECTDRIVE,
  kIfcMotorConnectionTypeEnum_USERDEFINED,
  kIfcMotorConnectionTypeEnum_NOTDEFINED,
  kIfcMotorConnectionTypeEnum_unset
};

class IFC2X3_EXPORT IfcMotorConnectionTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMotorConnectionTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcMotorConnectionTypeEnum& getUnset<OdIfc2x3::IfcMotorConnectionTypeEnum>() { static OdIfc2x3::IfcMotorConnectionTypeEnum nullEnum = OdIfc2x3::kIfcMotorConnectionTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcNullStyle
{
  kIfcNullStyle_NULL,
  kIfcNullStyle_unset
};

class IFC2X3_EXPORT IfcNullStyleTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcNullStyleTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcNullStyle& getUnset<OdIfc2x3::IfcNullStyle>() { static OdIfc2x3::IfcNullStyle nullEnum = OdIfc2x3::kIfcNullStyle_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcObjectTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcObjectTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcObjectTypeEnum& getUnset<OdIfc2x3::IfcObjectTypeEnum>() { static OdIfc2x3::IfcObjectTypeEnum nullEnum = OdIfc2x3::kIfcObjectTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcObjectiveEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcObjectiveEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcObjectiveEnum& getUnset<OdIfc2x3::IfcObjectiveEnum>() { static OdIfc2x3::IfcObjectiveEnum nullEnum = OdIfc2x3::kIfcObjectiveEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcOccupantTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcOccupantTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcOccupantTypeEnum& getUnset<OdIfc2x3::IfcOccupantTypeEnum>() { static OdIfc2x3::IfcOccupantTypeEnum nullEnum = OdIfc2x3::kIfcOccupantTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcOutletTypeEnum
{
  kIfcOutletTypeEnum_AUDIOVISUALOUTLET,
  kIfcOutletTypeEnum_COMMUNICATIONSOUTLET,
  kIfcOutletTypeEnum_POWEROUTLET,
  kIfcOutletTypeEnum_USERDEFINED,
  kIfcOutletTypeEnum_NOTDEFINED,
  kIfcOutletTypeEnum_unset
};

class IFC2X3_EXPORT IfcOutletTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcOutletTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcOutletTypeEnum& getUnset<OdIfc2x3::IfcOutletTypeEnum>() { static OdIfc2x3::IfcOutletTypeEnum nullEnum = OdIfc2x3::kIfcOutletTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcPermeableCoveringOperationEnum
{
  kIfcPermeableCoveringOperationEnum_GRILL,
  kIfcPermeableCoveringOperationEnum_LOUVER,
  kIfcPermeableCoveringOperationEnum_SCREEN,
  kIfcPermeableCoveringOperationEnum_USERDEFINED,
  kIfcPermeableCoveringOperationEnum_NOTDEFINED,
  kIfcPermeableCoveringOperationEnum_unset
};

class IFC2X3_EXPORT IfcPermeableCoveringOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPermeableCoveringOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcPermeableCoveringOperationEnum& getUnset<OdIfc2x3::IfcPermeableCoveringOperationEnum>() { static OdIfc2x3::IfcPermeableCoveringOperationEnum nullEnum = OdIfc2x3::kIfcPermeableCoveringOperationEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcPhysicalOrVirtualEnum
{
  kIfcPhysicalOrVirtualEnum_PHYSICAL,
  kIfcPhysicalOrVirtualEnum_VIRTUAL,
  kIfcPhysicalOrVirtualEnum_NOTDEFINED,
  kIfcPhysicalOrVirtualEnum_unset
};

class IFC2X3_EXPORT IfcPhysicalOrVirtualEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPhysicalOrVirtualEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcPhysicalOrVirtualEnum& getUnset<OdIfc2x3::IfcPhysicalOrVirtualEnum>() { static OdIfc2x3::IfcPhysicalOrVirtualEnum nullEnum = OdIfc2x3::kIfcPhysicalOrVirtualEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcPileConstructionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPileConstructionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcPileConstructionEnum& getUnset<OdIfc2x3::IfcPileConstructionEnum>() { static OdIfc2x3::IfcPileConstructionEnum nullEnum = OdIfc2x3::kIfcPileConstructionEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcPileTypeEnum
{
  kIfcPileTypeEnum_COHESION,
  kIfcPileTypeEnum_FRICTION,
  kIfcPileTypeEnum_SUPPORT,
  kIfcPileTypeEnum_USERDEFINED,
  kIfcPileTypeEnum_NOTDEFINED,
  kIfcPileTypeEnum_unset
};

class IFC2X3_EXPORT IfcPileTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPileTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcPileTypeEnum& getUnset<OdIfc2x3::IfcPileTypeEnum>() { static OdIfc2x3::IfcPileTypeEnum nullEnum = OdIfc2x3::kIfcPileTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcPipeFittingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPipeFittingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcPipeFittingTypeEnum& getUnset<OdIfc2x3::IfcPipeFittingTypeEnum>() { static OdIfc2x3::IfcPipeFittingTypeEnum nullEnum = OdIfc2x3::kIfcPipeFittingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcPipeSegmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPipeSegmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcPipeSegmentTypeEnum& getUnset<OdIfc2x3::IfcPipeSegmentTypeEnum>() { static OdIfc2x3::IfcPipeSegmentTypeEnum nullEnum = OdIfc2x3::kIfcPipeSegmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcPlateTypeEnum
{
  kIfcPlateTypeEnum_CURTAIN_PANEL,
  kIfcPlateTypeEnum_SHEET,
  kIfcPlateTypeEnum_USERDEFINED,
  kIfcPlateTypeEnum_NOTDEFINED,
  kIfcPlateTypeEnum_unset
};

class IFC2X3_EXPORT IfcPlateTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPlateTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcPlateTypeEnum& getUnset<OdIfc2x3::IfcPlateTypeEnum>() { static OdIfc2x3::IfcPlateTypeEnum nullEnum = OdIfc2x3::kIfcPlateTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcProcedureTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProcedureTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcProcedureTypeEnum& getUnset<OdIfc2x3::IfcProcedureTypeEnum>() { static OdIfc2x3::IfcProcedureTypeEnum nullEnum = OdIfc2x3::kIfcProcedureTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcProfileTypeEnum
{
  kIfcProfileTypeEnum_CURVE,
  kIfcProfileTypeEnum_AREA,
  kIfcProfileTypeEnum_unset
};

class IFC2X3_EXPORT IfcProfileTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProfileTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcProfileTypeEnum& getUnset<OdIfc2x3::IfcProfileTypeEnum>() { static OdIfc2x3::IfcProfileTypeEnum nullEnum = OdIfc2x3::kIfcProfileTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcProjectOrderRecordTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProjectOrderRecordTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcProjectOrderRecordTypeEnum& getUnset<OdIfc2x3::IfcProjectOrderRecordTypeEnum>() { static OdIfc2x3::IfcProjectOrderRecordTypeEnum nullEnum = OdIfc2x3::kIfcProjectOrderRecordTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcProjectOrderTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProjectOrderTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcProjectOrderTypeEnum& getUnset<OdIfc2x3::IfcProjectOrderTypeEnum>() { static OdIfc2x3::IfcProjectOrderTypeEnum nullEnum = OdIfc2x3::kIfcProjectOrderTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcProjectedOrTrueLengthEnum
{
  kIfcProjectedOrTrueLengthEnum_PROJECTED_LENGTH,
  kIfcProjectedOrTrueLengthEnum_TRUE_LENGTH,
  kIfcProjectedOrTrueLengthEnum_unset
};

class IFC2X3_EXPORT IfcProjectedOrTrueLengthEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProjectedOrTrueLengthEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcProjectedOrTrueLengthEnum& getUnset<OdIfc2x3::IfcProjectedOrTrueLengthEnum>() { static OdIfc2x3::IfcProjectedOrTrueLengthEnum nullEnum = OdIfc2x3::kIfcProjectedOrTrueLengthEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcPropertySourceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPropertySourceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcPropertySourceEnum& getUnset<OdIfc2x3::IfcPropertySourceEnum>() { static OdIfc2x3::IfcPropertySourceEnum nullEnum = OdIfc2x3::kIfcPropertySourceEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcProtectiveDeviceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProtectiveDeviceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcProtectiveDeviceTypeEnum& getUnset<OdIfc2x3::IfcProtectiveDeviceTypeEnum>() { static OdIfc2x3::IfcProtectiveDeviceTypeEnum nullEnum = OdIfc2x3::kIfcProtectiveDeviceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcPumpTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPumpTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcPumpTypeEnum& getUnset<OdIfc2x3::IfcPumpTypeEnum>() { static OdIfc2x3::IfcPumpTypeEnum nullEnum = OdIfc2x3::kIfcPumpTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcRailingTypeEnum
{
  kIfcRailingTypeEnum_HANDRAIL,
  kIfcRailingTypeEnum_GUARDRAIL,
  kIfcRailingTypeEnum_BALUSTRADE,
  kIfcRailingTypeEnum_USERDEFINED,
  kIfcRailingTypeEnum_NOTDEFINED,
  kIfcRailingTypeEnum_unset
};

class IFC2X3_EXPORT IfcRailingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRailingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcRailingTypeEnum& getUnset<OdIfc2x3::IfcRailingTypeEnum>() { static OdIfc2x3::IfcRailingTypeEnum nullEnum = OdIfc2x3::kIfcRailingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcRampFlightTypeEnum
{
  kIfcRampFlightTypeEnum_STRAIGHT,
  kIfcRampFlightTypeEnum_SPIRAL,
  kIfcRampFlightTypeEnum_USERDEFINED,
  kIfcRampFlightTypeEnum_NOTDEFINED,
  kIfcRampFlightTypeEnum_unset
};

class IFC2X3_EXPORT IfcRampFlightTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRampFlightTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcRampFlightTypeEnum& getUnset<OdIfc2x3::IfcRampFlightTypeEnum>() { static OdIfc2x3::IfcRampFlightTypeEnum nullEnum = OdIfc2x3::kIfcRampFlightTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcRampTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRampTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcRampTypeEnum& getUnset<OdIfc2x3::IfcRampTypeEnum>() { static OdIfc2x3::IfcRampTypeEnum nullEnum = OdIfc2x3::kIfcRampTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcReflectanceMethodEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcReflectanceMethodEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcReflectanceMethodEnum& getUnset<OdIfc2x3::IfcReflectanceMethodEnum>() { static OdIfc2x3::IfcReflectanceMethodEnum nullEnum = OdIfc2x3::kIfcReflectanceMethodEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcReinforcingBarRoleEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcReinforcingBarRoleEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcReinforcingBarRoleEnum& getUnset<OdIfc2x3::IfcReinforcingBarRoleEnum>() { static OdIfc2x3::IfcReinforcingBarRoleEnum nullEnum = OdIfc2x3::kIfcReinforcingBarRoleEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcReinforcingBarSurfaceEnum
{
  kIfcReinforcingBarSurfaceEnum_PLAIN,
  kIfcReinforcingBarSurfaceEnum_TEXTURED,
  kIfcReinforcingBarSurfaceEnum_unset
};

class IFC2X3_EXPORT IfcReinforcingBarSurfaceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcReinforcingBarSurfaceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcReinforcingBarSurfaceEnum& getUnset<OdIfc2x3::IfcReinforcingBarSurfaceEnum>() { static OdIfc2x3::IfcReinforcingBarSurfaceEnum nullEnum = OdIfc2x3::kIfcReinforcingBarSurfaceEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcResourceConsumptionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcResourceConsumptionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcResourceConsumptionEnum& getUnset<OdIfc2x3::IfcResourceConsumptionEnum>() { static OdIfc2x3::IfcResourceConsumptionEnum nullEnum = OdIfc2x3::kIfcResourceConsumptionEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcRibPlateDirectionEnum
{
  kIfcRibPlateDirectionEnum_DIRECTION_X,
  kIfcRibPlateDirectionEnum_DIRECTION_Y,
  kIfcRibPlateDirectionEnum_unset
};

class IFC2X3_EXPORT IfcRibPlateDirectionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRibPlateDirectionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcRibPlateDirectionEnum& getUnset<OdIfc2x3::IfcRibPlateDirectionEnum>() { static OdIfc2x3::IfcRibPlateDirectionEnum nullEnum = OdIfc2x3::kIfcRibPlateDirectionEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcRoleEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRoleEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcRoleEnum& getUnset<OdIfc2x3::IfcRoleEnum>() { static OdIfc2x3::IfcRoleEnum nullEnum = OdIfc2x3::kIfcRoleEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcRoofTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRoofTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcRoofTypeEnum& getUnset<OdIfc2x3::IfcRoofTypeEnum>() { static OdIfc2x3::IfcRoofTypeEnum nullEnum = OdIfc2x3::kIfcRoofTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcSIPrefixTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSIPrefixTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcSIPrefix& getUnset<OdIfc2x3::IfcSIPrefix>() { static OdIfc2x3::IfcSIPrefix nullEnum = OdIfc2x3::kIfcSIPrefix_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcSIUnitNameTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSIUnitNameTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcSIUnitName& getUnset<OdIfc2x3::IfcSIUnitName>() { static OdIfc2x3::IfcSIUnitName nullEnum = OdIfc2x3::kIfcSIUnitName_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcSanitaryTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSanitaryTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcSanitaryTerminalTypeEnum& getUnset<OdIfc2x3::IfcSanitaryTerminalTypeEnum>() { static OdIfc2x3::IfcSanitaryTerminalTypeEnum nullEnum = OdIfc2x3::kIfcSanitaryTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcSectionTypeEnum
{
  kIfcSectionTypeEnum_UNIFORM,
  kIfcSectionTypeEnum_TAPERED,
  kIfcSectionTypeEnum_unset
};

class IFC2X3_EXPORT IfcSectionTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSectionTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcSectionTypeEnum& getUnset<OdIfc2x3::IfcSectionTypeEnum>() { static OdIfc2x3::IfcSectionTypeEnum nullEnum = OdIfc2x3::kIfcSectionTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcSensorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSensorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcSensorTypeEnum& getUnset<OdIfc2x3::IfcSensorTypeEnum>() { static OdIfc2x3::IfcSensorTypeEnum nullEnum = OdIfc2x3::kIfcSensorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcSequenceEnum
{
  kIfcSequenceEnum_START_START,
  kIfcSequenceEnum_START_FINISH,
  kIfcSequenceEnum_FINISH_START,
  kIfcSequenceEnum_FINISH_FINISH,
  kIfcSequenceEnum_NOTDEFINED,
  kIfcSequenceEnum_unset
};

class IFC2X3_EXPORT IfcSequenceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSequenceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcSequenceEnum& getUnset<OdIfc2x3::IfcSequenceEnum>() { static OdIfc2x3::IfcSequenceEnum nullEnum = OdIfc2x3::kIfcSequenceEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcServiceLifeFactorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcServiceLifeFactorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcServiceLifeFactorTypeEnum& getUnset<OdIfc2x3::IfcServiceLifeFactorTypeEnum>() { static OdIfc2x3::IfcServiceLifeFactorTypeEnum nullEnum = OdIfc2x3::kIfcServiceLifeFactorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcServiceLifeTypeEnum
{
  kIfcServiceLifeTypeEnum_ACTUALSERVICELIFE,
  kIfcServiceLifeTypeEnum_EXPECTEDSERVICELIFE,
  kIfcServiceLifeTypeEnum_OPTIMISTICREFERENCESERVICELIFE,
  kIfcServiceLifeTypeEnum_PESSIMISTICREFERENCESERVICELIFE,
  kIfcServiceLifeTypeEnum_REFERENCESERVICELIFE,
  kIfcServiceLifeTypeEnum_unset
};

class IFC2X3_EXPORT IfcServiceLifeTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcServiceLifeTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcServiceLifeTypeEnum& getUnset<OdIfc2x3::IfcServiceLifeTypeEnum>() { static OdIfc2x3::IfcServiceLifeTypeEnum nullEnum = OdIfc2x3::kIfcServiceLifeTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcSlabTypeEnum
{
  kIfcSlabTypeEnum_FLOOR,
  kIfcSlabTypeEnum_ROOF,
  kIfcSlabTypeEnum_LANDING,
  kIfcSlabTypeEnum_BASESLAB,
  kIfcSlabTypeEnum_USERDEFINED,
  kIfcSlabTypeEnum_NOTDEFINED,
  kIfcSlabTypeEnum_unset
};

class IFC2X3_EXPORT IfcSlabTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSlabTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcSlabTypeEnum& getUnset<OdIfc2x3::IfcSlabTypeEnum>() { static OdIfc2x3::IfcSlabTypeEnum nullEnum = OdIfc2x3::kIfcSlabTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcSoundScaleEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSoundScaleEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcSoundScaleEnum& getUnset<OdIfc2x3::IfcSoundScaleEnum>() { static OdIfc2x3::IfcSoundScaleEnum nullEnum = OdIfc2x3::kIfcSoundScaleEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcSpaceHeaterTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSpaceHeaterTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcSpaceHeaterTypeEnum& getUnset<OdIfc2x3::IfcSpaceHeaterTypeEnum>() { static OdIfc2x3::IfcSpaceHeaterTypeEnum nullEnum = OdIfc2x3::kIfcSpaceHeaterTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcSpaceTypeEnum
{
  kIfcSpaceTypeEnum_USERDEFINED,
  kIfcSpaceTypeEnum_NOTDEFINED,
  kIfcSpaceTypeEnum_unset
};

class IFC2X3_EXPORT IfcSpaceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSpaceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcSpaceTypeEnum& getUnset<OdIfc2x3::IfcSpaceTypeEnum>() { static OdIfc2x3::IfcSpaceTypeEnum nullEnum = OdIfc2x3::kIfcSpaceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcStackTerminalTypeEnum
{
  kIfcStackTerminalTypeEnum_BIRDCAGE,
  kIfcStackTerminalTypeEnum_COWL,
  kIfcStackTerminalTypeEnum_RAINWATERHOPPER,
  kIfcStackTerminalTypeEnum_USERDEFINED,
  kIfcStackTerminalTypeEnum_NOTDEFINED,
  kIfcStackTerminalTypeEnum_unset
};

class IFC2X3_EXPORT IfcStackTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStackTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcStackTerminalTypeEnum& getUnset<OdIfc2x3::IfcStackTerminalTypeEnum>() { static OdIfc2x3::IfcStackTerminalTypeEnum nullEnum = OdIfc2x3::kIfcStackTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcStairFlightTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStairFlightTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcStairFlightTypeEnum& getUnset<OdIfc2x3::IfcStairFlightTypeEnum>() { static OdIfc2x3::IfcStairFlightTypeEnum nullEnum = OdIfc2x3::kIfcStairFlightTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcStairTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStairTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcStairTypeEnum& getUnset<OdIfc2x3::IfcStairTypeEnum>() { static OdIfc2x3::IfcStairTypeEnum nullEnum = OdIfc2x3::kIfcStairTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcStateEnum
{
  kIfcStateEnum_READWRITE,
  kIfcStateEnum_READONLY,
  kIfcStateEnum_LOCKED,
  kIfcStateEnum_READWRITELOCKED,
  kIfcStateEnum_READONLYLOCKED,
  kIfcStateEnum_unset
};

class IFC2X3_EXPORT IfcStateEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStateEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcStateEnum& getUnset<OdIfc2x3::IfcStateEnum>() { static OdIfc2x3::IfcStateEnum nullEnum = OdIfc2x3::kIfcStateEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcStructuralCurveTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStructuralCurveTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcStructuralCurveTypeEnum& getUnset<OdIfc2x3::IfcStructuralCurveTypeEnum>() { static OdIfc2x3::IfcStructuralCurveTypeEnum nullEnum = OdIfc2x3::kIfcStructuralCurveTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcStructuralSurfaceTypeEnum
{
  kIfcStructuralSurfaceTypeEnum_BENDING_ELEMENT,
  kIfcStructuralSurfaceTypeEnum_MEMBRANE_ELEMENT,
  kIfcStructuralSurfaceTypeEnum_SHELL,
  kIfcStructuralSurfaceTypeEnum_USERDEFINED,
  kIfcStructuralSurfaceTypeEnum_NOTDEFINED,
  kIfcStructuralSurfaceTypeEnum_unset
};

class IFC2X3_EXPORT IfcStructuralSurfaceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStructuralSurfaceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcStructuralSurfaceTypeEnum& getUnset<OdIfc2x3::IfcStructuralSurfaceTypeEnum>() { static OdIfc2x3::IfcStructuralSurfaceTypeEnum nullEnum = OdIfc2x3::kIfcStructuralSurfaceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcSurfaceSide
{
  kIfcSurfaceSide_POSITIVE,
  kIfcSurfaceSide_NEGATIVE,
  kIfcSurfaceSide_BOTH,
  kIfcSurfaceSide_unset
};

class IFC2X3_EXPORT IfcSurfaceSideTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSurfaceSideTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcSurfaceSide& getUnset<OdIfc2x3::IfcSurfaceSide>() { static OdIfc2x3::IfcSurfaceSide nullEnum = OdIfc2x3::kIfcSurfaceSide_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcSurfaceTextureEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSurfaceTextureEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcSurfaceTextureEnum& getUnset<OdIfc2x3::IfcSurfaceTextureEnum>() { static OdIfc2x3::IfcSurfaceTextureEnum nullEnum = OdIfc2x3::kIfcSurfaceTextureEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcSwitchingDeviceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSwitchingDeviceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcSwitchingDeviceTypeEnum& getUnset<OdIfc2x3::IfcSwitchingDeviceTypeEnum>() { static OdIfc2x3::IfcSwitchingDeviceTypeEnum nullEnum = OdIfc2x3::kIfcSwitchingDeviceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcTankTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTankTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcTankTypeEnum& getUnset<OdIfc2x3::IfcTankTypeEnum>() { static OdIfc2x3::IfcTankTypeEnum nullEnum = OdIfc2x3::kIfcTankTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcTendonTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTendonTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcTendonTypeEnum& getUnset<OdIfc2x3::IfcTendonTypeEnum>() { static OdIfc2x3::IfcTendonTypeEnum nullEnum = OdIfc2x3::kIfcTendonTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcTextPath
{
  kIfcTextPath_LEFT,
  kIfcTextPath_RIGHT,
  kIfcTextPath_UP,
  kIfcTextPath_DOWN,
  kIfcTextPath_unset
};

class IFC2X3_EXPORT IfcTextPathTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTextPathTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcTextPath& getUnset<OdIfc2x3::IfcTextPath>() { static OdIfc2x3::IfcTextPath nullEnum = OdIfc2x3::kIfcTextPath_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcThermalLoadSourceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcThermalLoadSourceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcThermalLoadSourceEnum& getUnset<OdIfc2x3::IfcThermalLoadSourceEnum>() { static OdIfc2x3::IfcThermalLoadSourceEnum nullEnum = OdIfc2x3::kIfcThermalLoadSourceEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcThermalLoadTypeEnum
{
  kIfcThermalLoadTypeEnum_SENSIBLE,
  kIfcThermalLoadTypeEnum_LATENT,
  kIfcThermalLoadTypeEnum_RADIANT,
  kIfcThermalLoadTypeEnum_NOTDEFINED,
  kIfcThermalLoadTypeEnum_unset
};

class IFC2X3_EXPORT IfcThermalLoadTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcThermalLoadTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcThermalLoadTypeEnum& getUnset<OdIfc2x3::IfcThermalLoadTypeEnum>() { static OdIfc2x3::IfcThermalLoadTypeEnum nullEnum = OdIfc2x3::kIfcThermalLoadTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcTimeSeriesDataTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTimeSeriesDataTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcTimeSeriesDataTypeEnum& getUnset<OdIfc2x3::IfcTimeSeriesDataTypeEnum>() { static OdIfc2x3::IfcTimeSeriesDataTypeEnum nullEnum = OdIfc2x3::kIfcTimeSeriesDataTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcTimeSeriesScheduleTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTimeSeriesScheduleTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcTimeSeriesScheduleTypeEnum& getUnset<OdIfc2x3::IfcTimeSeriesScheduleTypeEnum>() { static OdIfc2x3::IfcTimeSeriesScheduleTypeEnum nullEnum = OdIfc2x3::kIfcTimeSeriesScheduleTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcTransformerTypeEnum
{
  kIfcTransformerTypeEnum_CURRENT,
  kIfcTransformerTypeEnum_FREQUENCY,
  kIfcTransformerTypeEnum_VOLTAGE,
  kIfcTransformerTypeEnum_USERDEFINED,
  kIfcTransformerTypeEnum_NOTDEFINED,
  kIfcTransformerTypeEnum_unset
};

class IFC2X3_EXPORT IfcTransformerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTransformerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcTransformerTypeEnum& getUnset<OdIfc2x3::IfcTransformerTypeEnum>() { static OdIfc2x3::IfcTransformerTypeEnum nullEnum = OdIfc2x3::kIfcTransformerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcTransitionCode
{
  kIfcTransitionCode_DISCONTINUOUS,
  kIfcTransitionCode_CONTINUOUS,
  kIfcTransitionCode_CONTSAMEGRADIENT,
  kIfcTransitionCode_CONTSAMEGRADIENTSAMECURVATURE,
  kIfcTransitionCode_unset
};

class IFC2X3_EXPORT IfcTransitionCodeTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTransitionCodeTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcTransitionCode& getUnset<OdIfc2x3::IfcTransitionCode>() { static OdIfc2x3::IfcTransitionCode nullEnum = OdIfc2x3::kIfcTransitionCode_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcTransportElementTypeEnum
{
  kIfcTransportElementTypeEnum_ELEVATOR,
  kIfcTransportElementTypeEnum_ESCALATOR,
  kIfcTransportElementTypeEnum_MOVINGWALKWAY,
  kIfcTransportElementTypeEnum_USERDEFINED,
  kIfcTransportElementTypeEnum_NOTDEFINED,
  kIfcTransportElementTypeEnum_unset
};

class IFC2X3_EXPORT IfcTransportElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTransportElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcTransportElementTypeEnum& getUnset<OdIfc2x3::IfcTransportElementTypeEnum>() { static OdIfc2x3::IfcTransportElementTypeEnum nullEnum = OdIfc2x3::kIfcTransportElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcTrimmingPreference
{
  kIfcTrimmingPreference_CARTESIAN,
  kIfcTrimmingPreference_PARAMETER,
  kIfcTrimmingPreference_UNSPECIFIED,
  kIfcTrimmingPreference_unset
};

class IFC2X3_EXPORT IfcTrimmingPreferenceTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTrimmingPreferenceTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcTrimmingPreference& getUnset<OdIfc2x3::IfcTrimmingPreference>() { static OdIfc2x3::IfcTrimmingPreference nullEnum = OdIfc2x3::kIfcTrimmingPreference_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcTubeBundleTypeEnum
{
  kIfcTubeBundleTypeEnum_FINNED,
  kIfcTubeBundleTypeEnum_USERDEFINED,
  kIfcTubeBundleTypeEnum_NOTDEFINED,
  kIfcTubeBundleTypeEnum_unset
};

class IFC2X3_EXPORT IfcTubeBundleTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTubeBundleTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcTubeBundleTypeEnum& getUnset<OdIfc2x3::IfcTubeBundleTypeEnum>() { static OdIfc2x3::IfcTubeBundleTypeEnum nullEnum = OdIfc2x3::kIfcTubeBundleTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcUnitEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcUnitEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcUnitEnum& getUnset<OdIfc2x3::IfcUnitEnum>() { static OdIfc2x3::IfcUnitEnum nullEnum = OdIfc2x3::kIfcUnitEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcUnitaryEquipmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcUnitaryEquipmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcUnitaryEquipmentTypeEnum& getUnset<OdIfc2x3::IfcUnitaryEquipmentTypeEnum>() { static OdIfc2x3::IfcUnitaryEquipmentTypeEnum nullEnum = OdIfc2x3::kIfcUnitaryEquipmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcValveTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcValveTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcValveTypeEnum& getUnset<OdIfc2x3::IfcValveTypeEnum>() { static OdIfc2x3::IfcValveTypeEnum nullEnum = OdIfc2x3::kIfcValveTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcVibrationIsolatorTypeEnum
{
  kIfcVibrationIsolatorTypeEnum_COMPRESSION,
  kIfcVibrationIsolatorTypeEnum_SPRING,
  kIfcVibrationIsolatorTypeEnum_USERDEFINED,
  kIfcVibrationIsolatorTypeEnum_NOTDEFINED,
  kIfcVibrationIsolatorTypeEnum_unset
};

class IFC2X3_EXPORT IfcVibrationIsolatorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcVibrationIsolatorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcVibrationIsolatorTypeEnum& getUnset<OdIfc2x3::IfcVibrationIsolatorTypeEnum>() { static OdIfc2x3::IfcVibrationIsolatorTypeEnum nullEnum = OdIfc2x3::kIfcVibrationIsolatorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcWallTypeEnum
{
  kIfcWallTypeEnum_STANDARD,
  kIfcWallTypeEnum_POLYGONAL,
  kIfcWallTypeEnum_SHEAR,
  kIfcWallTypeEnum_ELEMENTEDWALL,
  kIfcWallTypeEnum_PLUMBINGWALL,
  kIfcWallTypeEnum_USERDEFINED,
  kIfcWallTypeEnum_NOTDEFINED,
  kIfcWallTypeEnum_unset
};

class IFC2X3_EXPORT IfcWallTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWallTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcWallTypeEnum& getUnset<OdIfc2x3::IfcWallTypeEnum>() { static OdIfc2x3::IfcWallTypeEnum nullEnum = OdIfc2x3::kIfcWallTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcWasteTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWasteTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcWasteTerminalTypeEnum& getUnset<OdIfc2x3::IfcWasteTerminalTypeEnum>() { static OdIfc2x3::IfcWasteTerminalTypeEnum nullEnum = OdIfc2x3::kIfcWasteTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcWindowPanelOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowPanelOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcWindowPanelOperationEnum& getUnset<OdIfc2x3::IfcWindowPanelOperationEnum>() { static OdIfc2x3::IfcWindowPanelOperationEnum nullEnum = OdIfc2x3::kIfcWindowPanelOperationEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcWindowPanelPositionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowPanelPositionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcWindowPanelPositionEnum& getUnset<OdIfc2x3::IfcWindowPanelPositionEnum>() { static OdIfc2x3::IfcWindowPanelPositionEnum nullEnum = OdIfc2x3::kIfcWindowPanelPositionEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcWindowStyleConstructionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowStyleConstructionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcWindowStyleConstructionEnum& getUnset<OdIfc2x3::IfcWindowStyleConstructionEnum>() { static OdIfc2x3::IfcWindowStyleConstructionEnum nullEnum = OdIfc2x3::kIfcWindowStyleConstructionEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
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

class IFC2X3_EXPORT IfcWindowStyleOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowStyleOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcWindowStyleOperationEnum& getUnset<OdIfc2x3::IfcWindowStyleOperationEnum>() { static OdIfc2x3::IfcWindowStyleOperationEnum nullEnum = OdIfc2x3::kIfcWindowStyleOperationEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {
enum IfcWorkControlTypeEnum
{
  kIfcWorkControlTypeEnum_ACTUAL,
  kIfcWorkControlTypeEnum_BASELINE,
  kIfcWorkControlTypeEnum_PLANNED,
  kIfcWorkControlTypeEnum_USERDEFINED,
  kIfcWorkControlTypeEnum_NOTDEFINED,
  kIfcWorkControlTypeEnum_unset
};

class IFC2X3_EXPORT IfcWorkControlTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWorkControlTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x3::IfcWorkControlTypeEnum& getUnset<OdIfc2x3::IfcWorkControlTypeEnum>() { static OdIfc2x3::IfcWorkControlTypeEnum nullEnum = OdIfc2x3::kIfcWorkControlTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x3 {

} // namespace

#endif // _IFC2X3_ENUM_H

