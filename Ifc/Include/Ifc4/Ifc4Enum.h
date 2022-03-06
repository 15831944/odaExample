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

#ifndef _IFC4_ENUM_H
#define _IFC4_ENUM_H

#include "RxValue.h"
#include "daiEnum.h"
#include "Ifc4BuildOption.h"

namespace OdIfc4 {

enum IfcActionRequestTypeEnum
{
  kIfcActionRequestTypeEnum_EMAIL,
  kIfcActionRequestTypeEnum_FAX,
  kIfcActionRequestTypeEnum_PHONE,
  kIfcActionRequestTypeEnum_POST,
  kIfcActionRequestTypeEnum_VERBAL,
  kIfcActionRequestTypeEnum_USERDEFINED,
  kIfcActionRequestTypeEnum_NOTDEFINED,
  kIfcActionRequestTypeEnum_unset
};

class IFC4_EXPORT IfcActionRequestTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcActionRequestTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcActionRequestTypeEnum& getUnset<OdIfc4::IfcActionRequestTypeEnum>() { static OdIfc4::IfcActionRequestTypeEnum nullEnum = OdIfc4::kIfcActionRequestTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcActionSourceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcActionSourceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcActionSourceTypeEnum& getUnset<OdIfc4::IfcActionSourceTypeEnum>() { static OdIfc4::IfcActionSourceTypeEnum nullEnum = OdIfc4::kIfcActionSourceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcActionTypeEnum
{
  kIfcActionTypeEnum_PERMANENT_G,
  kIfcActionTypeEnum_VARIABLE_Q,
  kIfcActionTypeEnum_EXTRAORDINARY_A,
  kIfcActionTypeEnum_USERDEFINED,
  kIfcActionTypeEnum_NOTDEFINED,
  kIfcActionTypeEnum_unset
};

class IFC4_EXPORT IfcActionTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcActionTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcActionTypeEnum& getUnset<OdIfc4::IfcActionTypeEnum>() { static OdIfc4::IfcActionTypeEnum nullEnum = OdIfc4::kIfcActionTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcActuatorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcActuatorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcActuatorTypeEnum& getUnset<OdIfc4::IfcActuatorTypeEnum>() { static OdIfc4::IfcActuatorTypeEnum nullEnum = OdIfc4::kIfcActuatorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcAddressTypeEnum
{
  kIfcAddressTypeEnum_OFFICE,
  kIfcAddressTypeEnum_SITE,
  kIfcAddressTypeEnum_HOME,
  kIfcAddressTypeEnum_DISTRIBUTIONPOINT,
  kIfcAddressTypeEnum_USERDEFINED,
  kIfcAddressTypeEnum_unset
};

class IFC4_EXPORT IfcAddressTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAddressTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcAddressTypeEnum& getUnset<OdIfc4::IfcAddressTypeEnum>() { static OdIfc4::IfcAddressTypeEnum nullEnum = OdIfc4::kIfcAddressTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcAirTerminalBoxTypeEnum
{
  kIfcAirTerminalBoxTypeEnum_CONSTANTFLOW,
  kIfcAirTerminalBoxTypeEnum_VARIABLEFLOWPRESSUREDEPENDANT,
  kIfcAirTerminalBoxTypeEnum_VARIABLEFLOWPRESSUREINDEPENDANT,
  kIfcAirTerminalBoxTypeEnum_USERDEFINED,
  kIfcAirTerminalBoxTypeEnum_NOTDEFINED,
  kIfcAirTerminalBoxTypeEnum_unset
};

class IFC4_EXPORT IfcAirTerminalBoxTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAirTerminalBoxTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcAirTerminalBoxTypeEnum& getUnset<OdIfc4::IfcAirTerminalBoxTypeEnum>() { static OdIfc4::IfcAirTerminalBoxTypeEnum nullEnum = OdIfc4::kIfcAirTerminalBoxTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcAirTerminalTypeEnum
{
  kIfcAirTerminalTypeEnum_DIFFUSER,
  kIfcAirTerminalTypeEnum_GRILLE,
  kIfcAirTerminalTypeEnum_LOUVRE,
  kIfcAirTerminalTypeEnum_REGISTER,
  kIfcAirTerminalTypeEnum_USERDEFINED,
  kIfcAirTerminalTypeEnum_NOTDEFINED,
  kIfcAirTerminalTypeEnum_unset
};

class IFC4_EXPORT IfcAirTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAirTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcAirTerminalTypeEnum& getUnset<OdIfc4::IfcAirTerminalTypeEnum>() { static OdIfc4::IfcAirTerminalTypeEnum nullEnum = OdIfc4::kIfcAirTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcAirToAirHeatRecoveryTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAirToAirHeatRecoveryTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcAirToAirHeatRecoveryTypeEnum& getUnset<OdIfc4::IfcAirToAirHeatRecoveryTypeEnum>() { static OdIfc4::IfcAirToAirHeatRecoveryTypeEnum nullEnum = OdIfc4::kIfcAirToAirHeatRecoveryTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcAlarmTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAlarmTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcAlarmTypeEnum& getUnset<OdIfc4::IfcAlarmTypeEnum>() { static OdIfc4::IfcAlarmTypeEnum nullEnum = OdIfc4::kIfcAlarmTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcAnalysisModelTypeEnum
{
  kIfcAnalysisModelTypeEnum_IN_PLANE_LOADING_2D,
  kIfcAnalysisModelTypeEnum_OUT_PLANE_LOADING_2D,
  kIfcAnalysisModelTypeEnum_LOADING_3D,
  kIfcAnalysisModelTypeEnum_USERDEFINED,
  kIfcAnalysisModelTypeEnum_NOTDEFINED,
  kIfcAnalysisModelTypeEnum_unset
};

class IFC4_EXPORT IfcAnalysisModelTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAnalysisModelTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcAnalysisModelTypeEnum& getUnset<OdIfc4::IfcAnalysisModelTypeEnum>() { static OdIfc4::IfcAnalysisModelTypeEnum nullEnum = OdIfc4::kIfcAnalysisModelTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcAnalysisTheoryTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAnalysisTheoryTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcAnalysisTheoryTypeEnum& getUnset<OdIfc4::IfcAnalysisTheoryTypeEnum>() { static OdIfc4::IfcAnalysisTheoryTypeEnum nullEnum = OdIfc4::kIfcAnalysisTheoryTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcArithmeticOperatorEnum
{
  kIfcArithmeticOperatorEnum_ADD,
  kIfcArithmeticOperatorEnum_DIVIDE,
  kIfcArithmeticOperatorEnum_MULTIPLY,
  kIfcArithmeticOperatorEnum_SUBTRACT,
  kIfcArithmeticOperatorEnum_unset
};

class IFC4_EXPORT IfcArithmeticOperatorEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcArithmeticOperatorEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcArithmeticOperatorEnum& getUnset<OdIfc4::IfcArithmeticOperatorEnum>() { static OdIfc4::IfcArithmeticOperatorEnum nullEnum = OdIfc4::kIfcArithmeticOperatorEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcAssemblyPlaceEnum
{
  kIfcAssemblyPlaceEnum_SITE,
  kIfcAssemblyPlaceEnum_FACTORY,
  kIfcAssemblyPlaceEnum_NOTDEFINED,
  kIfcAssemblyPlaceEnum_unset
};

class IFC4_EXPORT IfcAssemblyPlaceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAssemblyPlaceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcAssemblyPlaceEnum& getUnset<OdIfc4::IfcAssemblyPlaceEnum>() { static OdIfc4::IfcAssemblyPlaceEnum nullEnum = OdIfc4::kIfcAssemblyPlaceEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcAudioVisualApplianceTypeEnum
{
  kIfcAudioVisualApplianceTypeEnum_AMPLIFIER,
  kIfcAudioVisualApplianceTypeEnum_CAMERA,
  kIfcAudioVisualApplianceTypeEnum_DISPLAY,
  kIfcAudioVisualApplianceTypeEnum_MICROPHONE,
  kIfcAudioVisualApplianceTypeEnum_PLAYER,
  kIfcAudioVisualApplianceTypeEnum_PROJECTOR,
  kIfcAudioVisualApplianceTypeEnum_RECEIVER,
  kIfcAudioVisualApplianceTypeEnum_SPEAKER,
  kIfcAudioVisualApplianceTypeEnum_SWITCHER,
  kIfcAudioVisualApplianceTypeEnum_TELEPHONE,
  kIfcAudioVisualApplianceTypeEnum_TUNER,
  kIfcAudioVisualApplianceTypeEnum_USERDEFINED,
  kIfcAudioVisualApplianceTypeEnum_NOTDEFINED,
  kIfcAudioVisualApplianceTypeEnum_unset
};

class IFC4_EXPORT IfcAudioVisualApplianceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAudioVisualApplianceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcAudioVisualApplianceTypeEnum& getUnset<OdIfc4::IfcAudioVisualApplianceTypeEnum>() { static OdIfc4::IfcAudioVisualApplianceTypeEnum nullEnum = OdIfc4::kIfcAudioVisualApplianceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcBSplineCurveFormTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBSplineCurveFormTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcBSplineCurveForm& getUnset<OdIfc4::IfcBSplineCurveForm>() { static OdIfc4::IfcBSplineCurveForm nullEnum = OdIfc4::kIfcBSplineCurveForm_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcBSplineSurfaceForm
{
  kIfcBSplineSurfaceForm_PLANE_SURF,
  kIfcBSplineSurfaceForm_CYLINDRICAL_SURF,
  kIfcBSplineSurfaceForm_CONICAL_SURF,
  kIfcBSplineSurfaceForm_SPHERICAL_SURF,
  kIfcBSplineSurfaceForm_TOROIDAL_SURF,
  kIfcBSplineSurfaceForm_SURF_OF_REVOLUTION,
  kIfcBSplineSurfaceForm_RULED_SURF,
  kIfcBSplineSurfaceForm_GENERALISED_CONE,
  kIfcBSplineSurfaceForm_QUADRIC_SURF,
  kIfcBSplineSurfaceForm_SURF_OF_LINEAR_EXTRUSION,
  kIfcBSplineSurfaceForm_UNSPECIFIED,
  kIfcBSplineSurfaceForm_unset
};

class IFC4_EXPORT IfcBSplineSurfaceFormTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBSplineSurfaceFormTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcBSplineSurfaceForm& getUnset<OdIfc4::IfcBSplineSurfaceForm>() { static OdIfc4::IfcBSplineSurfaceForm nullEnum = OdIfc4::kIfcBSplineSurfaceForm_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcBeamTypeEnum
{
  kIfcBeamTypeEnum_BEAM,
  kIfcBeamTypeEnum_JOIST,
  kIfcBeamTypeEnum_HOLLOWCORE,
  kIfcBeamTypeEnum_LINTEL,
  kIfcBeamTypeEnum_SPANDREL,
  kIfcBeamTypeEnum_T_BEAM,
  kIfcBeamTypeEnum_USERDEFINED,
  kIfcBeamTypeEnum_NOTDEFINED,
  kIfcBeamTypeEnum_unset
};

class IFC4_EXPORT IfcBeamTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBeamTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcBeamTypeEnum& getUnset<OdIfc4::IfcBeamTypeEnum>() { static OdIfc4::IfcBeamTypeEnum nullEnum = OdIfc4::kIfcBeamTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcBenchmarkEnum
{
  kIfcBenchmarkEnum_GREATERTHAN,
  kIfcBenchmarkEnum_GREATERTHANOREQUALTO,
  kIfcBenchmarkEnum_LESSTHAN,
  kIfcBenchmarkEnum_LESSTHANOREQUALTO,
  kIfcBenchmarkEnum_EQUALTO,
  kIfcBenchmarkEnum_NOTEQUALTO,
  kIfcBenchmarkEnum_INCLUDES,
  kIfcBenchmarkEnum_NOTINCLUDES,
  kIfcBenchmarkEnum_INCLUDEDIN,
  kIfcBenchmarkEnum_NOTINCLUDEDIN,
  kIfcBenchmarkEnum_unset
};

class IFC4_EXPORT IfcBenchmarkEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBenchmarkEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcBenchmarkEnum& getUnset<OdIfc4::IfcBenchmarkEnum>() { static OdIfc4::IfcBenchmarkEnum nullEnum = OdIfc4::kIfcBenchmarkEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcBoilerTypeEnum
{
  kIfcBoilerTypeEnum_WATER,
  kIfcBoilerTypeEnum_STEAM,
  kIfcBoilerTypeEnum_USERDEFINED,
  kIfcBoilerTypeEnum_NOTDEFINED,
  kIfcBoilerTypeEnum_unset
};

class IFC4_EXPORT IfcBoilerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBoilerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcBoilerTypeEnum& getUnset<OdIfc4::IfcBoilerTypeEnum>() { static OdIfc4::IfcBoilerTypeEnum nullEnum = OdIfc4::kIfcBoilerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcBooleanOperator
{
  kIfcBooleanOperator_UNION,
  kIfcBooleanOperator_INTERSECTION,
  kIfcBooleanOperator_DIFFERENCE,
  kIfcBooleanOperator_unset
};

class IFC4_EXPORT IfcBooleanOperatorTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBooleanOperatorTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcBooleanOperator& getUnset<OdIfc4::IfcBooleanOperator>() { static OdIfc4::IfcBooleanOperator nullEnum = OdIfc4::kIfcBooleanOperator_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcBuildingElementPartTypeEnum
{
  kIfcBuildingElementPartTypeEnum_INSULATION,
  kIfcBuildingElementPartTypeEnum_PRECASTPANEL,
  kIfcBuildingElementPartTypeEnum_USERDEFINED,
  kIfcBuildingElementPartTypeEnum_NOTDEFINED,
  kIfcBuildingElementPartTypeEnum_unset
};

class IFC4_EXPORT IfcBuildingElementPartTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBuildingElementPartTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcBuildingElementPartTypeEnum& getUnset<OdIfc4::IfcBuildingElementPartTypeEnum>() { static OdIfc4::IfcBuildingElementPartTypeEnum nullEnum = OdIfc4::kIfcBuildingElementPartTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcBuildingElementProxyTypeEnum
{
  kIfcBuildingElementProxyTypeEnum_COMPLEX,
  kIfcBuildingElementProxyTypeEnum_ELEMENT,
  kIfcBuildingElementProxyTypeEnum_PARTIAL,
  kIfcBuildingElementProxyTypeEnum_PROVISIONFORVOID,
  kIfcBuildingElementProxyTypeEnum_PROVISIONFORSPACE,
  kIfcBuildingElementProxyTypeEnum_USERDEFINED,
  kIfcBuildingElementProxyTypeEnum_NOTDEFINED,
  kIfcBuildingElementProxyTypeEnum_unset
};

class IFC4_EXPORT IfcBuildingElementProxyTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBuildingElementProxyTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcBuildingElementProxyTypeEnum& getUnset<OdIfc4::IfcBuildingElementProxyTypeEnum>() { static OdIfc4::IfcBuildingElementProxyTypeEnum nullEnum = OdIfc4::kIfcBuildingElementProxyTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcBuildingSystemTypeEnum
{
  kIfcBuildingSystemTypeEnum_FENESTRATION,
  kIfcBuildingSystemTypeEnum_FOUNDATION,
  kIfcBuildingSystemTypeEnum_LOADBEARING,
  kIfcBuildingSystemTypeEnum_OUTERSHELL,
  kIfcBuildingSystemTypeEnum_SHADING,
  kIfcBuildingSystemTypeEnum_TRANSPORT,
  kIfcBuildingSystemTypeEnum_USERDEFINED,
  kIfcBuildingSystemTypeEnum_NOTDEFINED,
  kIfcBuildingSystemTypeEnum_unset
};

class IFC4_EXPORT IfcBuildingSystemTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBuildingSystemTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcBuildingSystemTypeEnum& getUnset<OdIfc4::IfcBuildingSystemTypeEnum>() { static OdIfc4::IfcBuildingSystemTypeEnum nullEnum = OdIfc4::kIfcBuildingSystemTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcBurnerTypeEnum
{
  kIfcBurnerTypeEnum_USERDEFINED,
  kIfcBurnerTypeEnum_NOTDEFINED,
  kIfcBurnerTypeEnum_unset
};

class IFC4_EXPORT IfcBurnerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBurnerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcBurnerTypeEnum& getUnset<OdIfc4::IfcBurnerTypeEnum>() { static OdIfc4::IfcBurnerTypeEnum nullEnum = OdIfc4::kIfcBurnerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcCableCarrierFittingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCableCarrierFittingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcCableCarrierFittingTypeEnum& getUnset<OdIfc4::IfcCableCarrierFittingTypeEnum>() { static OdIfc4::IfcCableCarrierFittingTypeEnum nullEnum = OdIfc4::kIfcCableCarrierFittingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcCableCarrierSegmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCableCarrierSegmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcCableCarrierSegmentTypeEnum& getUnset<OdIfc4::IfcCableCarrierSegmentTypeEnum>() { static OdIfc4::IfcCableCarrierSegmentTypeEnum nullEnum = OdIfc4::kIfcCableCarrierSegmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcCableFittingTypeEnum
{
  kIfcCableFittingTypeEnum_CONNECTOR,
  kIfcCableFittingTypeEnum_ENTRY,
  kIfcCableFittingTypeEnum_EXIT,
  kIfcCableFittingTypeEnum_JUNCTION,
  kIfcCableFittingTypeEnum_TRANSITION,
  kIfcCableFittingTypeEnum_USERDEFINED,
  kIfcCableFittingTypeEnum_NOTDEFINED,
  kIfcCableFittingTypeEnum_unset
};

class IFC4_EXPORT IfcCableFittingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCableFittingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcCableFittingTypeEnum& getUnset<OdIfc4::IfcCableFittingTypeEnum>() { static OdIfc4::IfcCableFittingTypeEnum nullEnum = OdIfc4::kIfcCableFittingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcCableSegmentTypeEnum
{
  kIfcCableSegmentTypeEnum_BUSBARSEGMENT,
  kIfcCableSegmentTypeEnum_CABLESEGMENT,
  kIfcCableSegmentTypeEnum_CONDUCTORSEGMENT,
  kIfcCableSegmentTypeEnum_CORESEGMENT,
  kIfcCableSegmentTypeEnum_USERDEFINED,
  kIfcCableSegmentTypeEnum_NOTDEFINED,
  kIfcCableSegmentTypeEnum_unset
};

class IFC4_EXPORT IfcCableSegmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCableSegmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcCableSegmentTypeEnum& getUnset<OdIfc4::IfcCableSegmentTypeEnum>() { static OdIfc4::IfcCableSegmentTypeEnum nullEnum = OdIfc4::kIfcCableSegmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcChangeActionEnum
{
  kIfcChangeActionEnum_NOCHANGE,
  kIfcChangeActionEnum_MODIFIED,
  kIfcChangeActionEnum_ADDED,
  kIfcChangeActionEnum_DELETED,
  kIfcChangeActionEnum_NOTDEFINED,
  kIfcChangeActionEnum_unset
};

class IFC4_EXPORT IfcChangeActionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcChangeActionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcChangeActionEnum& getUnset<OdIfc4::IfcChangeActionEnum>() { static OdIfc4::IfcChangeActionEnum nullEnum = OdIfc4::kIfcChangeActionEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcChillerTypeEnum
{
  kIfcChillerTypeEnum_AIRCOOLED,
  kIfcChillerTypeEnum_WATERCOOLED,
  kIfcChillerTypeEnum_HEATRECOVERY,
  kIfcChillerTypeEnum_USERDEFINED,
  kIfcChillerTypeEnum_NOTDEFINED,
  kIfcChillerTypeEnum_unset
};

class IFC4_EXPORT IfcChillerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcChillerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcChillerTypeEnum& getUnset<OdIfc4::IfcChillerTypeEnum>() { static OdIfc4::IfcChillerTypeEnum nullEnum = OdIfc4::kIfcChillerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcChimneyTypeEnum
{
  kIfcChimneyTypeEnum_USERDEFINED,
  kIfcChimneyTypeEnum_NOTDEFINED,
  kIfcChimneyTypeEnum_unset
};

class IFC4_EXPORT IfcChimneyTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcChimneyTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcChimneyTypeEnum& getUnset<OdIfc4::IfcChimneyTypeEnum>() { static OdIfc4::IfcChimneyTypeEnum nullEnum = OdIfc4::kIfcChimneyTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcCoilTypeEnum
{
  kIfcCoilTypeEnum_DXCOOLINGCOIL,
  kIfcCoilTypeEnum_ELECTRICHEATINGCOIL,
  kIfcCoilTypeEnum_GASHEATINGCOIL,
  kIfcCoilTypeEnum_HYDRONICCOIL,
  kIfcCoilTypeEnum_STEAMHEATINGCOIL,
  kIfcCoilTypeEnum_WATERCOOLINGCOIL,
  kIfcCoilTypeEnum_WATERHEATINGCOIL,
  kIfcCoilTypeEnum_USERDEFINED,
  kIfcCoilTypeEnum_NOTDEFINED,
  kIfcCoilTypeEnum_unset
};

class IFC4_EXPORT IfcCoilTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCoilTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcCoilTypeEnum& getUnset<OdIfc4::IfcCoilTypeEnum>() { static OdIfc4::IfcCoilTypeEnum nullEnum = OdIfc4::kIfcCoilTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcColumnTypeEnum
{
  kIfcColumnTypeEnum_COLUMN,
  kIfcColumnTypeEnum_PILASTER,
  kIfcColumnTypeEnum_USERDEFINED,
  kIfcColumnTypeEnum_NOTDEFINED,
  kIfcColumnTypeEnum_unset
};

class IFC4_EXPORT IfcColumnTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcColumnTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcColumnTypeEnum& getUnset<OdIfc4::IfcColumnTypeEnum>() { static OdIfc4::IfcColumnTypeEnum nullEnum = OdIfc4::kIfcColumnTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcCommunicationsApplianceTypeEnum
{
  kIfcCommunicationsApplianceTypeEnum_ANTENNA,
  kIfcCommunicationsApplianceTypeEnum_COMPUTER,
  kIfcCommunicationsApplianceTypeEnum_FAX,
  kIfcCommunicationsApplianceTypeEnum_GATEWAY,
  kIfcCommunicationsApplianceTypeEnum_MODEM,
  kIfcCommunicationsApplianceTypeEnum_NETWORKAPPLIANCE,
  kIfcCommunicationsApplianceTypeEnum_NETWORKBRIDGE,
  kIfcCommunicationsApplianceTypeEnum_NETWORKHUB,
  kIfcCommunicationsApplianceTypeEnum_PRINTER,
  kIfcCommunicationsApplianceTypeEnum_REPEATER,
  kIfcCommunicationsApplianceTypeEnum_ROUTER,
  kIfcCommunicationsApplianceTypeEnum_SCANNER,
  kIfcCommunicationsApplianceTypeEnum_USERDEFINED,
  kIfcCommunicationsApplianceTypeEnum_NOTDEFINED,
  kIfcCommunicationsApplianceTypeEnum_unset
};

class IFC4_EXPORT IfcCommunicationsApplianceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCommunicationsApplianceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcCommunicationsApplianceTypeEnum& getUnset<OdIfc4::IfcCommunicationsApplianceTypeEnum>() { static OdIfc4::IfcCommunicationsApplianceTypeEnum nullEnum = OdIfc4::kIfcCommunicationsApplianceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcComplexPropertyTemplateTypeEnum
{
  kIfcComplexPropertyTemplateTypeEnum_P_COMPLEX,
  kIfcComplexPropertyTemplateTypeEnum_Q_COMPLEX,
  kIfcComplexPropertyTemplateTypeEnum_unset
};

class IFC4_EXPORT IfcComplexPropertyTemplateTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcComplexPropertyTemplateTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcComplexPropertyTemplateTypeEnum& getUnset<OdIfc4::IfcComplexPropertyTemplateTypeEnum>() { static OdIfc4::IfcComplexPropertyTemplateTypeEnum nullEnum = OdIfc4::kIfcComplexPropertyTemplateTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcCompressorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCompressorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcCompressorTypeEnum& getUnset<OdIfc4::IfcCompressorTypeEnum>() { static OdIfc4::IfcCompressorTypeEnum nullEnum = OdIfc4::kIfcCompressorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcCondenserTypeEnum
{
  kIfcCondenserTypeEnum_AIRCOOLED,
  kIfcCondenserTypeEnum_EVAPORATIVECOOLED,
  kIfcCondenserTypeEnum_WATERCOOLED,
  kIfcCondenserTypeEnum_WATERCOOLEDBRAZEDPLATE,
  kIfcCondenserTypeEnum_WATERCOOLEDSHELLCOIL,
  kIfcCondenserTypeEnum_WATERCOOLEDSHELLTUBE,
  kIfcCondenserTypeEnum_WATERCOOLEDTUBEINTUBE,
  kIfcCondenserTypeEnum_USERDEFINED,
  kIfcCondenserTypeEnum_NOTDEFINED,
  kIfcCondenserTypeEnum_unset
};

class IFC4_EXPORT IfcCondenserTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCondenserTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcCondenserTypeEnum& getUnset<OdIfc4::IfcCondenserTypeEnum>() { static OdIfc4::IfcCondenserTypeEnum nullEnum = OdIfc4::kIfcCondenserTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcConnectionTypeEnum
{
  kIfcConnectionTypeEnum_ATPATH,
  kIfcConnectionTypeEnum_ATSTART,
  kIfcConnectionTypeEnum_ATEND,
  kIfcConnectionTypeEnum_NOTDEFINED,
  kIfcConnectionTypeEnum_unset
};

class IFC4_EXPORT IfcConnectionTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcConnectionTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcConnectionTypeEnum& getUnset<OdIfc4::IfcConnectionTypeEnum>() { static OdIfc4::IfcConnectionTypeEnum nullEnum = OdIfc4::kIfcConnectionTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcConstraintEnum
{
  kIfcConstraintEnum_HARD,
  kIfcConstraintEnum_SOFT,
  kIfcConstraintEnum_ADVISORY,
  kIfcConstraintEnum_USERDEFINED,
  kIfcConstraintEnum_NOTDEFINED,
  kIfcConstraintEnum_unset
};

class IFC4_EXPORT IfcConstraintEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcConstraintEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcConstraintEnum& getUnset<OdIfc4::IfcConstraintEnum>() { static OdIfc4::IfcConstraintEnum nullEnum = OdIfc4::kIfcConstraintEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcConstructionEquipmentResourceTypeEnum
{
  kIfcConstructionEquipmentResourceTypeEnum_DEMOLISHING,
  kIfcConstructionEquipmentResourceTypeEnum_EARTHMOVING,
  kIfcConstructionEquipmentResourceTypeEnum_ERECTING,
  kIfcConstructionEquipmentResourceTypeEnum_HEATING,
  kIfcConstructionEquipmentResourceTypeEnum_LIGHTING,
  kIfcConstructionEquipmentResourceTypeEnum_PAVING,
  kIfcConstructionEquipmentResourceTypeEnum_PUMPING,
  kIfcConstructionEquipmentResourceTypeEnum_TRANSPORTING,
  kIfcConstructionEquipmentResourceTypeEnum_USERDEFINED,
  kIfcConstructionEquipmentResourceTypeEnum_NOTDEFINED,
  kIfcConstructionEquipmentResourceTypeEnum_unset
};

class IFC4_EXPORT IfcConstructionEquipmentResourceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcConstructionEquipmentResourceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcConstructionEquipmentResourceTypeEnum& getUnset<OdIfc4::IfcConstructionEquipmentResourceTypeEnum>() { static OdIfc4::IfcConstructionEquipmentResourceTypeEnum nullEnum = OdIfc4::kIfcConstructionEquipmentResourceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcConstructionMaterialResourceTypeEnum
{
  kIfcConstructionMaterialResourceTypeEnum_AGGREGATES,
  kIfcConstructionMaterialResourceTypeEnum_CONCRETE,
  kIfcConstructionMaterialResourceTypeEnum_DRYWALL,
  kIfcConstructionMaterialResourceTypeEnum_FUEL,
  kIfcConstructionMaterialResourceTypeEnum_GYPSUM,
  kIfcConstructionMaterialResourceTypeEnum_MASONRY,
  kIfcConstructionMaterialResourceTypeEnum_METAL,
  kIfcConstructionMaterialResourceTypeEnum_PLASTIC,
  kIfcConstructionMaterialResourceTypeEnum_WOOD,
  kIfcConstructionMaterialResourceTypeEnum_NOTDEFINED,
  kIfcConstructionMaterialResourceTypeEnum_USERDEFINED,
  kIfcConstructionMaterialResourceTypeEnum_unset
};

class IFC4_EXPORT IfcConstructionMaterialResourceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcConstructionMaterialResourceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcConstructionMaterialResourceTypeEnum& getUnset<OdIfc4::IfcConstructionMaterialResourceTypeEnum>() { static OdIfc4::IfcConstructionMaterialResourceTypeEnum nullEnum = OdIfc4::kIfcConstructionMaterialResourceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcConstructionProductResourceTypeEnum
{
  kIfcConstructionProductResourceTypeEnum_ASSEMBLY,
  kIfcConstructionProductResourceTypeEnum_FORMWORK,
  kIfcConstructionProductResourceTypeEnum_USERDEFINED,
  kIfcConstructionProductResourceTypeEnum_NOTDEFINED,
  kIfcConstructionProductResourceTypeEnum_unset
};

class IFC4_EXPORT IfcConstructionProductResourceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcConstructionProductResourceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcConstructionProductResourceTypeEnum& getUnset<OdIfc4::IfcConstructionProductResourceTypeEnum>() { static OdIfc4::IfcConstructionProductResourceTypeEnum nullEnum = OdIfc4::kIfcConstructionProductResourceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcControllerTypeEnum
{
  kIfcControllerTypeEnum_FLOATING,
  kIfcControllerTypeEnum_PROGRAMMABLE,
  kIfcControllerTypeEnum_PROPORTIONAL,
  kIfcControllerTypeEnum_MULTIPOSITION,
  kIfcControllerTypeEnum_TWOPOSITION,
  kIfcControllerTypeEnum_USERDEFINED,
  kIfcControllerTypeEnum_NOTDEFINED,
  kIfcControllerTypeEnum_unset
};

class IFC4_EXPORT IfcControllerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcControllerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcControllerTypeEnum& getUnset<OdIfc4::IfcControllerTypeEnum>() { static OdIfc4::IfcControllerTypeEnum nullEnum = OdIfc4::kIfcControllerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcCooledBeamTypeEnum
{
  kIfcCooledBeamTypeEnum_ACTIVE,
  kIfcCooledBeamTypeEnum_PASSIVE,
  kIfcCooledBeamTypeEnum_USERDEFINED,
  kIfcCooledBeamTypeEnum_NOTDEFINED,
  kIfcCooledBeamTypeEnum_unset
};

class IFC4_EXPORT IfcCooledBeamTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCooledBeamTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcCooledBeamTypeEnum& getUnset<OdIfc4::IfcCooledBeamTypeEnum>() { static OdIfc4::IfcCooledBeamTypeEnum nullEnum = OdIfc4::kIfcCooledBeamTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcCoolingTowerTypeEnum
{
  kIfcCoolingTowerTypeEnum_NATURALDRAFT,
  kIfcCoolingTowerTypeEnum_MECHANICALINDUCEDDRAFT,
  kIfcCoolingTowerTypeEnum_MECHANICALFORCEDDRAFT,
  kIfcCoolingTowerTypeEnum_USERDEFINED,
  kIfcCoolingTowerTypeEnum_NOTDEFINED,
  kIfcCoolingTowerTypeEnum_unset
};

class IFC4_EXPORT IfcCoolingTowerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCoolingTowerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcCoolingTowerTypeEnum& getUnset<OdIfc4::IfcCoolingTowerTypeEnum>() { static OdIfc4::IfcCoolingTowerTypeEnum nullEnum = OdIfc4::kIfcCoolingTowerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcCostItemTypeEnum
{
  kIfcCostItemTypeEnum_USERDEFINED,
  kIfcCostItemTypeEnum_NOTDEFINED,
  kIfcCostItemTypeEnum_unset
};

class IFC4_EXPORT IfcCostItemTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCostItemTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcCostItemTypeEnum& getUnset<OdIfc4::IfcCostItemTypeEnum>() { static OdIfc4::IfcCostItemTypeEnum nullEnum = OdIfc4::kIfcCostItemTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcCostScheduleTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCostScheduleTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcCostScheduleTypeEnum& getUnset<OdIfc4::IfcCostScheduleTypeEnum>() { static OdIfc4::IfcCostScheduleTypeEnum nullEnum = OdIfc4::kIfcCostScheduleTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcCoveringTypeEnum
{
  kIfcCoveringTypeEnum_CEILING,
  kIfcCoveringTypeEnum_FLOORING,
  kIfcCoveringTypeEnum_CLADDING,
  kIfcCoveringTypeEnum_ROOFING,
  kIfcCoveringTypeEnum_MOLDING,
  kIfcCoveringTypeEnum_SKIRTINGBOARD,
  kIfcCoveringTypeEnum_INSULATION,
  kIfcCoveringTypeEnum_MEMBRANE,
  kIfcCoveringTypeEnum_SLEEVING,
  kIfcCoveringTypeEnum_WRAPPING,
  kIfcCoveringTypeEnum_USERDEFINED,
  kIfcCoveringTypeEnum_NOTDEFINED,
  kIfcCoveringTypeEnum_unset
};

class IFC4_EXPORT IfcCoveringTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCoveringTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcCoveringTypeEnum& getUnset<OdIfc4::IfcCoveringTypeEnum>() { static OdIfc4::IfcCoveringTypeEnum nullEnum = OdIfc4::kIfcCoveringTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcCrewResourceTypeEnum
{
  kIfcCrewResourceTypeEnum_OFFICE,
  kIfcCrewResourceTypeEnum_SITE,
  kIfcCrewResourceTypeEnum_USERDEFINED,
  kIfcCrewResourceTypeEnum_NOTDEFINED,
  kIfcCrewResourceTypeEnum_unset
};

class IFC4_EXPORT IfcCrewResourceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCrewResourceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcCrewResourceTypeEnum& getUnset<OdIfc4::IfcCrewResourceTypeEnum>() { static OdIfc4::IfcCrewResourceTypeEnum nullEnum = OdIfc4::kIfcCrewResourceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcCurtainWallTypeEnum
{
  kIfcCurtainWallTypeEnum_USERDEFINED,
  kIfcCurtainWallTypeEnum_NOTDEFINED,
  kIfcCurtainWallTypeEnum_unset
};

class IFC4_EXPORT IfcCurtainWallTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCurtainWallTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcCurtainWallTypeEnum& getUnset<OdIfc4::IfcCurtainWallTypeEnum>() { static OdIfc4::IfcCurtainWallTypeEnum nullEnum = OdIfc4::kIfcCurtainWallTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcCurveInterpolationEnum
{
  kIfcCurveInterpolationEnum_LINEAR,
  kIfcCurveInterpolationEnum_LOG_LINEAR,
  kIfcCurveInterpolationEnum_LOG_LOG,
  kIfcCurveInterpolationEnum_NOTDEFINED,
  kIfcCurveInterpolationEnum_unset
};

class IFC4_EXPORT IfcCurveInterpolationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCurveInterpolationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcCurveInterpolationEnum& getUnset<OdIfc4::IfcCurveInterpolationEnum>() { static OdIfc4::IfcCurveInterpolationEnum nullEnum = OdIfc4::kIfcCurveInterpolationEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcDamperTypeEnum
{
  kIfcDamperTypeEnum_BACKDRAFTDAMPER,
  kIfcDamperTypeEnum_BALANCINGDAMPER,
  kIfcDamperTypeEnum_BLASTDAMPER,
  kIfcDamperTypeEnum_CONTROLDAMPER,
  kIfcDamperTypeEnum_FIREDAMPER,
  kIfcDamperTypeEnum_FIRESMOKEDAMPER,
  kIfcDamperTypeEnum_FUMEHOODEXHAUST,
  kIfcDamperTypeEnum_GRAVITYDAMPER,
  kIfcDamperTypeEnum_GRAVITYRELIEFDAMPER,
  kIfcDamperTypeEnum_RELIEFDAMPER,
  kIfcDamperTypeEnum_SMOKEDAMPER,
  kIfcDamperTypeEnum_USERDEFINED,
  kIfcDamperTypeEnum_NOTDEFINED,
  kIfcDamperTypeEnum_unset
};

class IFC4_EXPORT IfcDamperTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDamperTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcDamperTypeEnum& getUnset<OdIfc4::IfcDamperTypeEnum>() { static OdIfc4::IfcDamperTypeEnum nullEnum = OdIfc4::kIfcDamperTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcDataOriginEnum
{
  kIfcDataOriginEnum_MEASURED,
  kIfcDataOriginEnum_PREDICTED,
  kIfcDataOriginEnum_SIMULATED,
  kIfcDataOriginEnum_USERDEFINED,
  kIfcDataOriginEnum_NOTDEFINED,
  kIfcDataOriginEnum_unset
};

class IFC4_EXPORT IfcDataOriginEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDataOriginEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcDataOriginEnum& getUnset<OdIfc4::IfcDataOriginEnum>() { static OdIfc4::IfcDataOriginEnum nullEnum = OdIfc4::kIfcDataOriginEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcDerivedUnitEnum
{
  kIfcDerivedUnitEnum_ANGULARVELOCITYUNIT,
  kIfcDerivedUnitEnum_AREADENSITYUNIT,
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
  kIfcDerivedUnitEnum_SOUNDPOWERLEVELUNIT,
  kIfcDerivedUnitEnum_SOUNDPOWERUNIT,
  kIfcDerivedUnitEnum_SOUNDPRESSURELEVELUNIT,
  kIfcDerivedUnitEnum_SOUNDPRESSUREUNIT,
  kIfcDerivedUnitEnum_TEMPERATUREGRADIENTUNIT,
  kIfcDerivedUnitEnum_TEMPERATURERATEOFCHANGEUNIT,
  kIfcDerivedUnitEnum_THERMALEXPANSIONCOEFFICIENTUNIT,
  kIfcDerivedUnitEnum_WARPINGCONSTANTUNIT,
  kIfcDerivedUnitEnum_WARPINGMOMENTUNIT,
  kIfcDerivedUnitEnum_USERDEFINED,
  kIfcDerivedUnitEnum_unset
};

class IFC4_EXPORT IfcDerivedUnitEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDerivedUnitEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcDerivedUnitEnum& getUnset<OdIfc4::IfcDerivedUnitEnum>() { static OdIfc4::IfcDerivedUnitEnum nullEnum = OdIfc4::kIfcDerivedUnitEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcDirectionSenseEnum
{
  kIfcDirectionSenseEnum_POSITIVE,
  kIfcDirectionSenseEnum_NEGATIVE,
  kIfcDirectionSenseEnum_unset
};

class IFC4_EXPORT IfcDirectionSenseEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDirectionSenseEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcDirectionSenseEnum& getUnset<OdIfc4::IfcDirectionSenseEnum>() { static OdIfc4::IfcDirectionSenseEnum nullEnum = OdIfc4::kIfcDirectionSenseEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcDiscreteAccessoryTypeEnum
{
  kIfcDiscreteAccessoryTypeEnum_ANCHORPLATE,
  kIfcDiscreteAccessoryTypeEnum_BRACKET,
  kIfcDiscreteAccessoryTypeEnum_SHOE,
  kIfcDiscreteAccessoryTypeEnum_USERDEFINED,
  kIfcDiscreteAccessoryTypeEnum_NOTDEFINED,
  kIfcDiscreteAccessoryTypeEnum_unset
};

class IFC4_EXPORT IfcDiscreteAccessoryTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDiscreteAccessoryTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcDiscreteAccessoryTypeEnum& getUnset<OdIfc4::IfcDiscreteAccessoryTypeEnum>() { static OdIfc4::IfcDiscreteAccessoryTypeEnum nullEnum = OdIfc4::kIfcDiscreteAccessoryTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcDistributionChamberElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDistributionChamberElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcDistributionChamberElementTypeEnum& getUnset<OdIfc4::IfcDistributionChamberElementTypeEnum>() { static OdIfc4::IfcDistributionChamberElementTypeEnum nullEnum = OdIfc4::kIfcDistributionChamberElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcDistributionPortTypeEnum
{
  kIfcDistributionPortTypeEnum_CABLE,
  kIfcDistributionPortTypeEnum_CABLECARRIER,
  kIfcDistributionPortTypeEnum_DUCT,
  kIfcDistributionPortTypeEnum_PIPE,
  kIfcDistributionPortTypeEnum_USERDEFINED,
  kIfcDistributionPortTypeEnum_NOTDEFINED,
  kIfcDistributionPortTypeEnum_unset
};

class IFC4_EXPORT IfcDistributionPortTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDistributionPortTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcDistributionPortTypeEnum& getUnset<OdIfc4::IfcDistributionPortTypeEnum>() { static OdIfc4::IfcDistributionPortTypeEnum nullEnum = OdIfc4::kIfcDistributionPortTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcDistributionSystemEnum
{
  kIfcDistributionSystemEnum_AIRCONDITIONING,
  kIfcDistributionSystemEnum_AUDIOVISUAL,
  kIfcDistributionSystemEnum_CHEMICAL,
  kIfcDistributionSystemEnum_CHILLEDWATER,
  kIfcDistributionSystemEnum_COMMUNICATION,
  kIfcDistributionSystemEnum_COMPRESSEDAIR,
  kIfcDistributionSystemEnum_CONDENSERWATER,
  kIfcDistributionSystemEnum_CONTROL,
  kIfcDistributionSystemEnum_CONVEYING,
  kIfcDistributionSystemEnum_DATA,
  kIfcDistributionSystemEnum_DISPOSAL,
  kIfcDistributionSystemEnum_DOMESTICCOLDWATER,
  kIfcDistributionSystemEnum_DOMESTICHOTWATER,
  kIfcDistributionSystemEnum_DRAINAGE,
  kIfcDistributionSystemEnum_EARTHING,
  kIfcDistributionSystemEnum_ELECTRICAL,
  kIfcDistributionSystemEnum_ELECTROACOUSTIC,
  kIfcDistributionSystemEnum_EXHAUST,
  kIfcDistributionSystemEnum_FIREPROTECTION,
  kIfcDistributionSystemEnum_FUEL,
  kIfcDistributionSystemEnum_GAS,
  kIfcDistributionSystemEnum_HAZARDOUS,
  kIfcDistributionSystemEnum_HEATING,
  kIfcDistributionSystemEnum_LIGHTING,
  kIfcDistributionSystemEnum_LIGHTNINGPROTECTION,
  kIfcDistributionSystemEnum_MUNICIPALSOLIDWASTE,
  kIfcDistributionSystemEnum_OIL,
  kIfcDistributionSystemEnum_OPERATIONAL,
  kIfcDistributionSystemEnum_POWERGENERATION,
  kIfcDistributionSystemEnum_RAINWATER,
  kIfcDistributionSystemEnum_REFRIGERATION,
  kIfcDistributionSystemEnum_SECURITY,
  kIfcDistributionSystemEnum_SEWAGE,
  kIfcDistributionSystemEnum_SIGNAL,
  kIfcDistributionSystemEnum_STORMWATER,
  kIfcDistributionSystemEnum_TELEPHONE,
  kIfcDistributionSystemEnum_TV,
  kIfcDistributionSystemEnum_VACUUM,
  kIfcDistributionSystemEnum_VENT,
  kIfcDistributionSystemEnum_VENTILATION,
  kIfcDistributionSystemEnum_WASTEWATER,
  kIfcDistributionSystemEnum_WATERSUPPLY,
  kIfcDistributionSystemEnum_USERDEFINED,
  kIfcDistributionSystemEnum_NOTDEFINED,
  kIfcDistributionSystemEnum_unset
};

class IFC4_EXPORT IfcDistributionSystemEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDistributionSystemEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcDistributionSystemEnum& getUnset<OdIfc4::IfcDistributionSystemEnum>() { static OdIfc4::IfcDistributionSystemEnum nullEnum = OdIfc4::kIfcDistributionSystemEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcDocumentConfidentialityEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDocumentConfidentialityEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcDocumentConfidentialityEnum& getUnset<OdIfc4::IfcDocumentConfidentialityEnum>() { static OdIfc4::IfcDocumentConfidentialityEnum nullEnum = OdIfc4::kIfcDocumentConfidentialityEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcDocumentStatusEnum
{
  kIfcDocumentStatusEnum_DRAFT,
  kIfcDocumentStatusEnum_FINALDRAFT,
  kIfcDocumentStatusEnum_FINAL,
  kIfcDocumentStatusEnum_REVISION,
  kIfcDocumentStatusEnum_NOTDEFINED,
  kIfcDocumentStatusEnum_unset
};

class IFC4_EXPORT IfcDocumentStatusEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDocumentStatusEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcDocumentStatusEnum& getUnset<OdIfc4::IfcDocumentStatusEnum>() { static OdIfc4::IfcDocumentStatusEnum nullEnum = OdIfc4::kIfcDocumentStatusEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcDoorPanelOperationEnum
{
  kIfcDoorPanelOperationEnum_SWINGING,
  kIfcDoorPanelOperationEnum_DOUBLE_ACTING,
  kIfcDoorPanelOperationEnum_SLIDING,
  kIfcDoorPanelOperationEnum_FOLDING,
  kIfcDoorPanelOperationEnum_REVOLVING,
  kIfcDoorPanelOperationEnum_ROLLINGUP,
  kIfcDoorPanelOperationEnum_FIXEDPANEL,
  kIfcDoorPanelOperationEnum_USERDEFINED,
  kIfcDoorPanelOperationEnum_NOTDEFINED,
  kIfcDoorPanelOperationEnum_unset
};

class IFC4_EXPORT IfcDoorPanelOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorPanelOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcDoorPanelOperationEnum& getUnset<OdIfc4::IfcDoorPanelOperationEnum>() { static OdIfc4::IfcDoorPanelOperationEnum nullEnum = OdIfc4::kIfcDoorPanelOperationEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcDoorPanelPositionEnum
{
  kIfcDoorPanelPositionEnum_LEFT,
  kIfcDoorPanelPositionEnum_MIDDLE,
  kIfcDoorPanelPositionEnum_RIGHT,
  kIfcDoorPanelPositionEnum_NOTDEFINED,
  kIfcDoorPanelPositionEnum_unset
};

class IFC4_EXPORT IfcDoorPanelPositionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorPanelPositionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcDoorPanelPositionEnum& getUnset<OdIfc4::IfcDoorPanelPositionEnum>() { static OdIfc4::IfcDoorPanelPositionEnum nullEnum = OdIfc4::kIfcDoorPanelPositionEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcDoorStyleConstructionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorStyleConstructionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcDoorStyleConstructionEnum& getUnset<OdIfc4::IfcDoorStyleConstructionEnum>() { static OdIfc4::IfcDoorStyleConstructionEnum nullEnum = OdIfc4::kIfcDoorStyleConstructionEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcDoorStyleOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorStyleOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcDoorStyleOperationEnum& getUnset<OdIfc4::IfcDoorStyleOperationEnum>() { static OdIfc4::IfcDoorStyleOperationEnum nullEnum = OdIfc4::kIfcDoorStyleOperationEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcDoorTypeEnum
{
  kIfcDoorTypeEnum_DOOR,
  kIfcDoorTypeEnum_GATE,
  kIfcDoorTypeEnum_TRAPDOOR,
  kIfcDoorTypeEnum_USERDEFINED,
  kIfcDoorTypeEnum_NOTDEFINED,
  kIfcDoorTypeEnum_unset
};

class IFC4_EXPORT IfcDoorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcDoorTypeEnum& getUnset<OdIfc4::IfcDoorTypeEnum>() { static OdIfc4::IfcDoorTypeEnum nullEnum = OdIfc4::kIfcDoorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcDoorTypeOperationEnum
{
  kIfcDoorTypeOperationEnum_SINGLE_SWING_LEFT,
  kIfcDoorTypeOperationEnum_SINGLE_SWING_RIGHT,
  kIfcDoorTypeOperationEnum_DOUBLE_DOOR_SINGLE_SWING,
  kIfcDoorTypeOperationEnum_DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_LEFT,
  kIfcDoorTypeOperationEnum_DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_RIGHT,
  kIfcDoorTypeOperationEnum_DOUBLE_SWING_LEFT,
  kIfcDoorTypeOperationEnum_DOUBLE_SWING_RIGHT,
  kIfcDoorTypeOperationEnum_DOUBLE_DOOR_DOUBLE_SWING,
  kIfcDoorTypeOperationEnum_SLIDING_TO_LEFT,
  kIfcDoorTypeOperationEnum_SLIDING_TO_RIGHT,
  kIfcDoorTypeOperationEnum_DOUBLE_DOOR_SLIDING,
  kIfcDoorTypeOperationEnum_FOLDING_TO_LEFT,
  kIfcDoorTypeOperationEnum_FOLDING_TO_RIGHT,
  kIfcDoorTypeOperationEnum_DOUBLE_DOOR_FOLDING,
  kIfcDoorTypeOperationEnum_REVOLVING,
  kIfcDoorTypeOperationEnum_ROLLINGUP,
  kIfcDoorTypeOperationEnum_SWING_FIXED_LEFT,
  kIfcDoorTypeOperationEnum_SWING_FIXED_RIGHT,
  kIfcDoorTypeOperationEnum_USERDEFINED,
  kIfcDoorTypeOperationEnum_NOTDEFINED,
  kIfcDoorTypeOperationEnum_unset
};

class IFC4_EXPORT IfcDoorTypeOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorTypeOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcDoorTypeOperationEnum& getUnset<OdIfc4::IfcDoorTypeOperationEnum>() { static OdIfc4::IfcDoorTypeOperationEnum nullEnum = OdIfc4::kIfcDoorTypeOperationEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcDuctFittingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDuctFittingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcDuctFittingTypeEnum& getUnset<OdIfc4::IfcDuctFittingTypeEnum>() { static OdIfc4::IfcDuctFittingTypeEnum nullEnum = OdIfc4::kIfcDuctFittingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcDuctSegmentTypeEnum
{
  kIfcDuctSegmentTypeEnum_RIGIDSEGMENT,
  kIfcDuctSegmentTypeEnum_FLEXIBLESEGMENT,
  kIfcDuctSegmentTypeEnum_USERDEFINED,
  kIfcDuctSegmentTypeEnum_NOTDEFINED,
  kIfcDuctSegmentTypeEnum_unset
};

class IFC4_EXPORT IfcDuctSegmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDuctSegmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcDuctSegmentTypeEnum& getUnset<OdIfc4::IfcDuctSegmentTypeEnum>() { static OdIfc4::IfcDuctSegmentTypeEnum nullEnum = OdIfc4::kIfcDuctSegmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcDuctSilencerTypeEnum
{
  kIfcDuctSilencerTypeEnum_FLATOVAL,
  kIfcDuctSilencerTypeEnum_RECTANGULAR,
  kIfcDuctSilencerTypeEnum_ROUND,
  kIfcDuctSilencerTypeEnum_USERDEFINED,
  kIfcDuctSilencerTypeEnum_NOTDEFINED,
  kIfcDuctSilencerTypeEnum_unset
};

class IFC4_EXPORT IfcDuctSilencerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDuctSilencerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcDuctSilencerTypeEnum& getUnset<OdIfc4::IfcDuctSilencerTypeEnum>() { static OdIfc4::IfcDuctSilencerTypeEnum nullEnum = OdIfc4::kIfcDuctSilencerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcElectricApplianceTypeEnum
{
  kIfcElectricApplianceTypeEnum_DISHWASHER,
  kIfcElectricApplianceTypeEnum_ELECTRICCOOKER,
  kIfcElectricApplianceTypeEnum_FREESTANDINGELECTRICHEATER,
  kIfcElectricApplianceTypeEnum_FREESTANDINGFAN,
  kIfcElectricApplianceTypeEnum_FREESTANDINGWATERHEATER,
  kIfcElectricApplianceTypeEnum_FREESTANDINGWATERCOOLER,
  kIfcElectricApplianceTypeEnum_FREEZER,
  kIfcElectricApplianceTypeEnum_FRIDGE_FREEZER,
  kIfcElectricApplianceTypeEnum_HANDDRYER,
  kIfcElectricApplianceTypeEnum_KITCHENMACHINE,
  kIfcElectricApplianceTypeEnum_MICROWAVE,
  kIfcElectricApplianceTypeEnum_PHOTOCOPIER,
  kIfcElectricApplianceTypeEnum_REFRIGERATOR,
  kIfcElectricApplianceTypeEnum_TUMBLEDRYER,
  kIfcElectricApplianceTypeEnum_VENDINGMACHINE,
  kIfcElectricApplianceTypeEnum_WASHINGMACHINE,
  kIfcElectricApplianceTypeEnum_USERDEFINED,
  kIfcElectricApplianceTypeEnum_NOTDEFINED,
  kIfcElectricApplianceTypeEnum_unset
};

class IFC4_EXPORT IfcElectricApplianceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricApplianceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcElectricApplianceTypeEnum& getUnset<OdIfc4::IfcElectricApplianceTypeEnum>() { static OdIfc4::IfcElectricApplianceTypeEnum nullEnum = OdIfc4::kIfcElectricApplianceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcElectricDistributionBoardTypeEnum
{
  kIfcElectricDistributionBoardTypeEnum_CONSUMERUNIT,
  kIfcElectricDistributionBoardTypeEnum_DISTRIBUTIONBOARD,
  kIfcElectricDistributionBoardTypeEnum_MOTORCONTROLCENTRE,
  kIfcElectricDistributionBoardTypeEnum_SWITCHBOARD,
  kIfcElectricDistributionBoardTypeEnum_USERDEFINED,
  kIfcElectricDistributionBoardTypeEnum_NOTDEFINED,
  kIfcElectricDistributionBoardTypeEnum_unset
};

class IFC4_EXPORT IfcElectricDistributionBoardTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricDistributionBoardTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcElectricDistributionBoardTypeEnum& getUnset<OdIfc4::IfcElectricDistributionBoardTypeEnum>() { static OdIfc4::IfcElectricDistributionBoardTypeEnum nullEnum = OdIfc4::kIfcElectricDistributionBoardTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcElectricFlowStorageDeviceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricFlowStorageDeviceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcElectricFlowStorageDeviceTypeEnum& getUnset<OdIfc4::IfcElectricFlowStorageDeviceTypeEnum>() { static OdIfc4::IfcElectricFlowStorageDeviceTypeEnum nullEnum = OdIfc4::kIfcElectricFlowStorageDeviceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcElectricGeneratorTypeEnum
{
  kIfcElectricGeneratorTypeEnum_CHP,
  kIfcElectricGeneratorTypeEnum_ENGINEGENERATOR,
  kIfcElectricGeneratorTypeEnum_STANDALONE,
  kIfcElectricGeneratorTypeEnum_USERDEFINED,
  kIfcElectricGeneratorTypeEnum_NOTDEFINED,
  kIfcElectricGeneratorTypeEnum_unset
};

class IFC4_EXPORT IfcElectricGeneratorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricGeneratorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcElectricGeneratorTypeEnum& getUnset<OdIfc4::IfcElectricGeneratorTypeEnum>() { static OdIfc4::IfcElectricGeneratorTypeEnum nullEnum = OdIfc4::kIfcElectricGeneratorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcElectricMotorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricMotorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcElectricMotorTypeEnum& getUnset<OdIfc4::IfcElectricMotorTypeEnum>() { static OdIfc4::IfcElectricMotorTypeEnum nullEnum = OdIfc4::kIfcElectricMotorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcElectricTimeControlTypeEnum
{
  kIfcElectricTimeControlTypeEnum_TIMECLOCK,
  kIfcElectricTimeControlTypeEnum_TIMEDELAY,
  kIfcElectricTimeControlTypeEnum_RELAY,
  kIfcElectricTimeControlTypeEnum_USERDEFINED,
  kIfcElectricTimeControlTypeEnum_NOTDEFINED,
  kIfcElectricTimeControlTypeEnum_unset
};

class IFC4_EXPORT IfcElectricTimeControlTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricTimeControlTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcElectricTimeControlTypeEnum& getUnset<OdIfc4::IfcElectricTimeControlTypeEnum>() { static OdIfc4::IfcElectricTimeControlTypeEnum nullEnum = OdIfc4::kIfcElectricTimeControlTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcElementAssemblyTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElementAssemblyTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcElementAssemblyTypeEnum& getUnset<OdIfc4::IfcElementAssemblyTypeEnum>() { static OdIfc4::IfcElementAssemblyTypeEnum nullEnum = OdIfc4::kIfcElementAssemblyTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcElementCompositionEnum
{
  kIfcElementCompositionEnum_COMPLEX,
  kIfcElementCompositionEnum_ELEMENT,
  kIfcElementCompositionEnum_PARTIAL,
  kIfcElementCompositionEnum_unset
};

class IFC4_EXPORT IfcElementCompositionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElementCompositionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcElementCompositionEnum& getUnset<OdIfc4::IfcElementCompositionEnum>() { static OdIfc4::IfcElementCompositionEnum nullEnum = OdIfc4::kIfcElementCompositionEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcEngineTypeEnum
{
  kIfcEngineTypeEnum_EXTERNALCOMBUSTION,
  kIfcEngineTypeEnum_INTERNALCOMBUSTION,
  kIfcEngineTypeEnum_USERDEFINED,
  kIfcEngineTypeEnum_NOTDEFINED,
  kIfcEngineTypeEnum_unset
};

class IFC4_EXPORT IfcEngineTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcEngineTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcEngineTypeEnum& getUnset<OdIfc4::IfcEngineTypeEnum>() { static OdIfc4::IfcEngineTypeEnum nullEnum = OdIfc4::kIfcEngineTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcEvaporativeCoolerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcEvaporativeCoolerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcEvaporativeCoolerTypeEnum& getUnset<OdIfc4::IfcEvaporativeCoolerTypeEnum>() { static OdIfc4::IfcEvaporativeCoolerTypeEnum nullEnum = OdIfc4::kIfcEvaporativeCoolerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcEvaporatorTypeEnum
{
  kIfcEvaporatorTypeEnum_DIRECTEXPANSION,
  kIfcEvaporatorTypeEnum_DIRECTEXPANSIONSHELLANDTUBE,
  kIfcEvaporatorTypeEnum_DIRECTEXPANSIONTUBEINTUBE,
  kIfcEvaporatorTypeEnum_DIRECTEXPANSIONBRAZEDPLATE,
  kIfcEvaporatorTypeEnum_FLOODEDSHELLANDTUBE,
  kIfcEvaporatorTypeEnum_SHELLANDCOIL,
  kIfcEvaporatorTypeEnum_USERDEFINED,
  kIfcEvaporatorTypeEnum_NOTDEFINED,
  kIfcEvaporatorTypeEnum_unset
};

class IFC4_EXPORT IfcEvaporatorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcEvaporatorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcEvaporatorTypeEnum& getUnset<OdIfc4::IfcEvaporatorTypeEnum>() { static OdIfc4::IfcEvaporatorTypeEnum nullEnum = OdIfc4::kIfcEvaporatorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcEventTriggerTypeEnum
{
  kIfcEventTriggerTypeEnum_EVENTRULE,
  kIfcEventTriggerTypeEnum_EVENTMESSAGE,
  kIfcEventTriggerTypeEnum_EVENTTIME,
  kIfcEventTriggerTypeEnum_EVENTCOMPLEX,
  kIfcEventTriggerTypeEnum_USERDEFINED,
  kIfcEventTriggerTypeEnum_NOTDEFINED,
  kIfcEventTriggerTypeEnum_unset
};

class IFC4_EXPORT IfcEventTriggerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcEventTriggerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcEventTriggerTypeEnum& getUnset<OdIfc4::IfcEventTriggerTypeEnum>() { static OdIfc4::IfcEventTriggerTypeEnum nullEnum = OdIfc4::kIfcEventTriggerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcEventTypeEnum
{
  kIfcEventTypeEnum_STARTEVENT,
  kIfcEventTypeEnum_ENDEVENT,
  kIfcEventTypeEnum_INTERMEDIATEEVENT,
  kIfcEventTypeEnum_USERDEFINED,
  kIfcEventTypeEnum_NOTDEFINED,
  kIfcEventTypeEnum_unset
};

class IFC4_EXPORT IfcEventTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcEventTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcEventTypeEnum& getUnset<OdIfc4::IfcEventTypeEnum>() { static OdIfc4::IfcEventTypeEnum nullEnum = OdIfc4::kIfcEventTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcExternalSpatialElementTypeEnum
{
  kIfcExternalSpatialElementTypeEnum_EXTERNAL,
  kIfcExternalSpatialElementTypeEnum_EXTERNAL_EARTH,
  kIfcExternalSpatialElementTypeEnum_EXTERNAL_WATER,
  kIfcExternalSpatialElementTypeEnum_EXTERNAL_FIRE,
  kIfcExternalSpatialElementTypeEnum_USERDEFINED,
  kIfcExternalSpatialElementTypeEnum_NOTDEFINED,
  kIfcExternalSpatialElementTypeEnum_unset
};

class IFC4_EXPORT IfcExternalSpatialElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcExternalSpatialElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcExternalSpatialElementTypeEnum& getUnset<OdIfc4::IfcExternalSpatialElementTypeEnum>() { static OdIfc4::IfcExternalSpatialElementTypeEnum nullEnum = OdIfc4::kIfcExternalSpatialElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcFanTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFanTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcFanTypeEnum& getUnset<OdIfc4::IfcFanTypeEnum>() { static OdIfc4::IfcFanTypeEnum nullEnum = OdIfc4::kIfcFanTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcFastenerTypeEnum
{
  kIfcFastenerTypeEnum_GLUE,
  kIfcFastenerTypeEnum_MORTAR,
  kIfcFastenerTypeEnum_WELD,
  kIfcFastenerTypeEnum_USERDEFINED,
  kIfcFastenerTypeEnum_NOTDEFINED,
  kIfcFastenerTypeEnum_unset
};

class IFC4_EXPORT IfcFastenerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFastenerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcFastenerTypeEnum& getUnset<OdIfc4::IfcFastenerTypeEnum>() { static OdIfc4::IfcFastenerTypeEnum nullEnum = OdIfc4::kIfcFastenerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcFilterTypeEnum
{
  kIfcFilterTypeEnum_AIRPARTICLEFILTER,
  kIfcFilterTypeEnum_COMPRESSEDAIRFILTER,
  kIfcFilterTypeEnum_ODORFILTER,
  kIfcFilterTypeEnum_OILFILTER,
  kIfcFilterTypeEnum_STRAINER,
  kIfcFilterTypeEnum_WATERFILTER,
  kIfcFilterTypeEnum_USERDEFINED,
  kIfcFilterTypeEnum_NOTDEFINED,
  kIfcFilterTypeEnum_unset
};

class IFC4_EXPORT IfcFilterTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFilterTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcFilterTypeEnum& getUnset<OdIfc4::IfcFilterTypeEnum>() { static OdIfc4::IfcFilterTypeEnum nullEnum = OdIfc4::kIfcFilterTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcFireSuppressionTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFireSuppressionTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcFireSuppressionTerminalTypeEnum& getUnset<OdIfc4::IfcFireSuppressionTerminalTypeEnum>() { static OdIfc4::IfcFireSuppressionTerminalTypeEnum nullEnum = OdIfc4::kIfcFireSuppressionTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcFlowDirectionEnum
{
  kIfcFlowDirectionEnum_SOURCE,
  kIfcFlowDirectionEnum_SINK,
  kIfcFlowDirectionEnum_SOURCEANDSINK,
  kIfcFlowDirectionEnum_NOTDEFINED,
  kIfcFlowDirectionEnum_unset
};

class IFC4_EXPORT IfcFlowDirectionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFlowDirectionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcFlowDirectionEnum& getUnset<OdIfc4::IfcFlowDirectionEnum>() { static OdIfc4::IfcFlowDirectionEnum nullEnum = OdIfc4::kIfcFlowDirectionEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcFlowInstrumentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFlowInstrumentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcFlowInstrumentTypeEnum& getUnset<OdIfc4::IfcFlowInstrumentTypeEnum>() { static OdIfc4::IfcFlowInstrumentTypeEnum nullEnum = OdIfc4::kIfcFlowInstrumentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcFlowMeterTypeEnum
{
  kIfcFlowMeterTypeEnum_ENERGYMETER,
  kIfcFlowMeterTypeEnum_GASMETER,
  kIfcFlowMeterTypeEnum_OILMETER,
  kIfcFlowMeterTypeEnum_WATERMETER,
  kIfcFlowMeterTypeEnum_USERDEFINED,
  kIfcFlowMeterTypeEnum_NOTDEFINED,
  kIfcFlowMeterTypeEnum_unset
};

class IFC4_EXPORT IfcFlowMeterTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFlowMeterTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcFlowMeterTypeEnum& getUnset<OdIfc4::IfcFlowMeterTypeEnum>() { static OdIfc4::IfcFlowMeterTypeEnum nullEnum = OdIfc4::kIfcFlowMeterTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcFootingTypeEnum
{
  kIfcFootingTypeEnum_CAISSON_FOUNDATION,
  kIfcFootingTypeEnum_FOOTING_BEAM,
  kIfcFootingTypeEnum_PAD_FOOTING,
  kIfcFootingTypeEnum_PILE_CAP,
  kIfcFootingTypeEnum_STRIP_FOOTING,
  kIfcFootingTypeEnum_USERDEFINED,
  kIfcFootingTypeEnum_NOTDEFINED,
  kIfcFootingTypeEnum_unset
};

class IFC4_EXPORT IfcFootingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFootingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcFootingTypeEnum& getUnset<OdIfc4::IfcFootingTypeEnum>() { static OdIfc4::IfcFootingTypeEnum nullEnum = OdIfc4::kIfcFootingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcFurnitureTypeEnum
{
  kIfcFurnitureTypeEnum_CHAIR,
  kIfcFurnitureTypeEnum_TABLE,
  kIfcFurnitureTypeEnum_DESK,
  kIfcFurnitureTypeEnum_BED,
  kIfcFurnitureTypeEnum_FILECABINET,
  kIfcFurnitureTypeEnum_SHELF,
  kIfcFurnitureTypeEnum_SOFA,
  kIfcFurnitureTypeEnum_USERDEFINED,
  kIfcFurnitureTypeEnum_NOTDEFINED,
  kIfcFurnitureTypeEnum_unset
};

class IFC4_EXPORT IfcFurnitureTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFurnitureTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcFurnitureTypeEnum& getUnset<OdIfc4::IfcFurnitureTypeEnum>() { static OdIfc4::IfcFurnitureTypeEnum nullEnum = OdIfc4::kIfcFurnitureTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcGeographicElementTypeEnum
{
  kIfcGeographicElementTypeEnum_TERRAIN,
  kIfcGeographicElementTypeEnum_USERDEFINED,
  kIfcGeographicElementTypeEnum_NOTDEFINED,
  kIfcGeographicElementTypeEnum_unset
};

class IFC4_EXPORT IfcGeographicElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcGeographicElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcGeographicElementTypeEnum& getUnset<OdIfc4::IfcGeographicElementTypeEnum>() { static OdIfc4::IfcGeographicElementTypeEnum nullEnum = OdIfc4::kIfcGeographicElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcGeometricProjectionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcGeometricProjectionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcGeometricProjectionEnum& getUnset<OdIfc4::IfcGeometricProjectionEnum>() { static OdIfc4::IfcGeometricProjectionEnum nullEnum = OdIfc4::kIfcGeometricProjectionEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcGlobalOrLocalEnum
{
  kIfcGlobalOrLocalEnum_GLOBAL_COORDS,
  kIfcGlobalOrLocalEnum_LOCAL_COORDS,
  kIfcGlobalOrLocalEnum_unset
};

class IFC4_EXPORT IfcGlobalOrLocalEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcGlobalOrLocalEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcGlobalOrLocalEnum& getUnset<OdIfc4::IfcGlobalOrLocalEnum>() { static OdIfc4::IfcGlobalOrLocalEnum nullEnum = OdIfc4::kIfcGlobalOrLocalEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcGridTypeEnum
{
  kIfcGridTypeEnum_RECTANGULAR,
  kIfcGridTypeEnum_RADIAL,
  kIfcGridTypeEnum_TRIANGULAR,
  kIfcGridTypeEnum_IRREGULAR,
  kIfcGridTypeEnum_USERDEFINED,
  kIfcGridTypeEnum_NOTDEFINED,
  kIfcGridTypeEnum_unset
};

class IFC4_EXPORT IfcGridTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcGridTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcGridTypeEnum& getUnset<OdIfc4::IfcGridTypeEnum>() { static OdIfc4::IfcGridTypeEnum nullEnum = OdIfc4::kIfcGridTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcHeatExchangerTypeEnum
{
  kIfcHeatExchangerTypeEnum_PLATE,
  kIfcHeatExchangerTypeEnum_SHELLANDTUBE,
  kIfcHeatExchangerTypeEnum_USERDEFINED,
  kIfcHeatExchangerTypeEnum_NOTDEFINED,
  kIfcHeatExchangerTypeEnum_unset
};

class IFC4_EXPORT IfcHeatExchangerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcHeatExchangerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcHeatExchangerTypeEnum& getUnset<OdIfc4::IfcHeatExchangerTypeEnum>() { static OdIfc4::IfcHeatExchangerTypeEnum nullEnum = OdIfc4::kIfcHeatExchangerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcHumidifierTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcHumidifierTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcHumidifierTypeEnum& getUnset<OdIfc4::IfcHumidifierTypeEnum>() { static OdIfc4::IfcHumidifierTypeEnum nullEnum = OdIfc4::kIfcHumidifierTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcInterceptorTypeEnum
{
  kIfcInterceptorTypeEnum_CYCLONIC,
  kIfcInterceptorTypeEnum_GREASE,
  kIfcInterceptorTypeEnum_OIL,
  kIfcInterceptorTypeEnum_PETROL,
  kIfcInterceptorTypeEnum_USERDEFINED,
  kIfcInterceptorTypeEnum_NOTDEFINED,
  kIfcInterceptorTypeEnum_unset
};

class IFC4_EXPORT IfcInterceptorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcInterceptorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcInterceptorTypeEnum& getUnset<OdIfc4::IfcInterceptorTypeEnum>() { static OdIfc4::IfcInterceptorTypeEnum nullEnum = OdIfc4::kIfcInterceptorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcInternalOrExternalEnum
{
  kIfcInternalOrExternalEnum_INTERNAL,
  kIfcInternalOrExternalEnum_EXTERNAL,
  kIfcInternalOrExternalEnum_EXTERNAL_EARTH,
  kIfcInternalOrExternalEnum_EXTERNAL_WATER,
  kIfcInternalOrExternalEnum_EXTERNAL_FIRE,
  kIfcInternalOrExternalEnum_NOTDEFINED,
  kIfcInternalOrExternalEnum_unset
};

class IFC4_EXPORT IfcInternalOrExternalEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcInternalOrExternalEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcInternalOrExternalEnum& getUnset<OdIfc4::IfcInternalOrExternalEnum>() { static OdIfc4::IfcInternalOrExternalEnum nullEnum = OdIfc4::kIfcInternalOrExternalEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcInventoryTypeEnum
{
  kIfcInventoryTypeEnum_ASSETINVENTORY,
  kIfcInventoryTypeEnum_SPACEINVENTORY,
  kIfcInventoryTypeEnum_FURNITUREINVENTORY,
  kIfcInventoryTypeEnum_USERDEFINED,
  kIfcInventoryTypeEnum_NOTDEFINED,
  kIfcInventoryTypeEnum_unset
};

class IFC4_EXPORT IfcInventoryTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcInventoryTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcInventoryTypeEnum& getUnset<OdIfc4::IfcInventoryTypeEnum>() { static OdIfc4::IfcInventoryTypeEnum nullEnum = OdIfc4::kIfcInventoryTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcJunctionBoxTypeEnum
{
  kIfcJunctionBoxTypeEnum_DATA,
  kIfcJunctionBoxTypeEnum_POWER,
  kIfcJunctionBoxTypeEnum_USERDEFINED,
  kIfcJunctionBoxTypeEnum_NOTDEFINED,
  kIfcJunctionBoxTypeEnum_unset
};

class IFC4_EXPORT IfcJunctionBoxTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcJunctionBoxTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcJunctionBoxTypeEnum& getUnset<OdIfc4::IfcJunctionBoxTypeEnum>() { static OdIfc4::IfcJunctionBoxTypeEnum nullEnum = OdIfc4::kIfcJunctionBoxTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcKnotType
{
  kIfcKnotType_UNIFORM_KNOTS,
  kIfcKnotType_QUASI_UNIFORM_KNOTS,
  kIfcKnotType_PIECEWISE_BEZIER_KNOTS,
  kIfcKnotType_UNSPECIFIED,
  kIfcKnotType_unset
};

class IFC4_EXPORT IfcKnotTypeTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcKnotTypeTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcKnotType& getUnset<OdIfc4::IfcKnotType>() { static OdIfc4::IfcKnotType nullEnum = OdIfc4::kIfcKnotType_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcLaborResourceTypeEnum
{
  kIfcLaborResourceTypeEnum_ADMINISTRATION,
  kIfcLaborResourceTypeEnum_CARPENTRY,
  kIfcLaborResourceTypeEnum_CLEANING,
  kIfcLaborResourceTypeEnum_CONCRETE,
  kIfcLaborResourceTypeEnum_DRYWALL,
  kIfcLaborResourceTypeEnum_ELECTRIC,
  kIfcLaborResourceTypeEnum_FINISHING,
  kIfcLaborResourceTypeEnum_FLOORING,
  kIfcLaborResourceTypeEnum_GENERAL,
  kIfcLaborResourceTypeEnum_HVAC,
  kIfcLaborResourceTypeEnum_LANDSCAPING,
  kIfcLaborResourceTypeEnum_MASONRY,
  kIfcLaborResourceTypeEnum_PAINTING,
  kIfcLaborResourceTypeEnum_PAVING,
  kIfcLaborResourceTypeEnum_PLUMBING,
  kIfcLaborResourceTypeEnum_ROOFING,
  kIfcLaborResourceTypeEnum_SITEGRADING,
  kIfcLaborResourceTypeEnum_STEELWORK,
  kIfcLaborResourceTypeEnum_SURVEYING,
  kIfcLaborResourceTypeEnum_USERDEFINED,
  kIfcLaborResourceTypeEnum_NOTDEFINED,
  kIfcLaborResourceTypeEnum_unset
};

class IFC4_EXPORT IfcLaborResourceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLaborResourceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcLaborResourceTypeEnum& getUnset<OdIfc4::IfcLaborResourceTypeEnum>() { static OdIfc4::IfcLaborResourceTypeEnum nullEnum = OdIfc4::kIfcLaborResourceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcLampTypeEnum
{
  kIfcLampTypeEnum_COMPACTFLUORESCENT,
  kIfcLampTypeEnum_FLUORESCENT,
  kIfcLampTypeEnum_HALOGEN,
  kIfcLampTypeEnum_HIGHPRESSUREMERCURY,
  kIfcLampTypeEnum_HIGHPRESSURESODIUM,
  kIfcLampTypeEnum_LED,
  kIfcLampTypeEnum_METALHALIDE,
  kIfcLampTypeEnum_OLED,
  kIfcLampTypeEnum_TUNGSTENFILAMENT,
  kIfcLampTypeEnum_USERDEFINED,
  kIfcLampTypeEnum_NOTDEFINED,
  kIfcLampTypeEnum_unset
};

class IFC4_EXPORT IfcLampTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLampTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcLampTypeEnum& getUnset<OdIfc4::IfcLampTypeEnum>() { static OdIfc4::IfcLampTypeEnum nullEnum = OdIfc4::kIfcLampTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcLayerSetDirectionEnum
{
  kIfcLayerSetDirectionEnum_AXIS1,
  kIfcLayerSetDirectionEnum_AXIS2,
  kIfcLayerSetDirectionEnum_AXIS3,
  kIfcLayerSetDirectionEnum_unset
};

class IFC4_EXPORT IfcLayerSetDirectionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLayerSetDirectionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcLayerSetDirectionEnum& getUnset<OdIfc4::IfcLayerSetDirectionEnum>() { static OdIfc4::IfcLayerSetDirectionEnum nullEnum = OdIfc4::kIfcLayerSetDirectionEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcLightDistributionCurveEnum
{
  kIfcLightDistributionCurveEnum_TYPE_A,
  kIfcLightDistributionCurveEnum_TYPE_B,
  kIfcLightDistributionCurveEnum_TYPE_C,
  kIfcLightDistributionCurveEnum_NOTDEFINED,
  kIfcLightDistributionCurveEnum_unset
};

class IFC4_EXPORT IfcLightDistributionCurveEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLightDistributionCurveEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcLightDistributionCurveEnum& getUnset<OdIfc4::IfcLightDistributionCurveEnum>() { static OdIfc4::IfcLightDistributionCurveEnum nullEnum = OdIfc4::kIfcLightDistributionCurveEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcLightEmissionSourceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLightEmissionSourceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcLightEmissionSourceEnum& getUnset<OdIfc4::IfcLightEmissionSourceEnum>() { static OdIfc4::IfcLightEmissionSourceEnum nullEnum = OdIfc4::kIfcLightEmissionSourceEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcLightFixtureTypeEnum
{
  kIfcLightFixtureTypeEnum_POINTSOURCE,
  kIfcLightFixtureTypeEnum_DIRECTIONSOURCE,
  kIfcLightFixtureTypeEnum_SECURITYLIGHTING,
  kIfcLightFixtureTypeEnum_USERDEFINED,
  kIfcLightFixtureTypeEnum_NOTDEFINED,
  kIfcLightFixtureTypeEnum_unset
};

class IFC4_EXPORT IfcLightFixtureTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLightFixtureTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcLightFixtureTypeEnum& getUnset<OdIfc4::IfcLightFixtureTypeEnum>() { static OdIfc4::IfcLightFixtureTypeEnum nullEnum = OdIfc4::kIfcLightFixtureTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcLoadGroupTypeEnum
{
  kIfcLoadGroupTypeEnum_LOAD_GROUP,
  kIfcLoadGroupTypeEnum_LOAD_CASE,
  kIfcLoadGroupTypeEnum_LOAD_COMBINATION,
  kIfcLoadGroupTypeEnum_USERDEFINED,
  kIfcLoadGroupTypeEnum_NOTDEFINED,
  kIfcLoadGroupTypeEnum_unset
};

class IFC4_EXPORT IfcLoadGroupTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLoadGroupTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcLoadGroupTypeEnum& getUnset<OdIfc4::IfcLoadGroupTypeEnum>() { static OdIfc4::IfcLoadGroupTypeEnum nullEnum = OdIfc4::kIfcLoadGroupTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcLogicalOperatorEnum
{
  kIfcLogicalOperatorEnum_LOGICALAND,
  kIfcLogicalOperatorEnum_LOGICALOR,
  kIfcLogicalOperatorEnum_LOGICALXOR,
  kIfcLogicalOperatorEnum_LOGICALNOTAND,
  kIfcLogicalOperatorEnum_LOGICALNOTOR,
  kIfcLogicalOperatorEnum_unset
};

class IFC4_EXPORT IfcLogicalOperatorEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLogicalOperatorEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcLogicalOperatorEnum& getUnset<OdIfc4::IfcLogicalOperatorEnum>() { static OdIfc4::IfcLogicalOperatorEnum nullEnum = OdIfc4::kIfcLogicalOperatorEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcMechanicalFastenerTypeEnum
{
  kIfcMechanicalFastenerTypeEnum_ANCHORBOLT,
  kIfcMechanicalFastenerTypeEnum_BOLT,
  kIfcMechanicalFastenerTypeEnum_DOWEL,
  kIfcMechanicalFastenerTypeEnum_NAIL,
  kIfcMechanicalFastenerTypeEnum_NAILPLATE,
  kIfcMechanicalFastenerTypeEnum_RIVET,
  kIfcMechanicalFastenerTypeEnum_SCREW,
  kIfcMechanicalFastenerTypeEnum_SHEARCONNECTOR,
  kIfcMechanicalFastenerTypeEnum_STAPLE,
  kIfcMechanicalFastenerTypeEnum_STUDSHEARCONNECTOR,
  kIfcMechanicalFastenerTypeEnum_USERDEFINED,
  kIfcMechanicalFastenerTypeEnum_NOTDEFINED,
  kIfcMechanicalFastenerTypeEnum_unset
};

class IFC4_EXPORT IfcMechanicalFastenerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMechanicalFastenerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcMechanicalFastenerTypeEnum& getUnset<OdIfc4::IfcMechanicalFastenerTypeEnum>() { static OdIfc4::IfcMechanicalFastenerTypeEnum nullEnum = OdIfc4::kIfcMechanicalFastenerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcMedicalDeviceTypeEnum
{
  kIfcMedicalDeviceTypeEnum_AIRSTATION,
  kIfcMedicalDeviceTypeEnum_FEEDAIRUNIT,
  kIfcMedicalDeviceTypeEnum_OXYGENGENERATOR,
  kIfcMedicalDeviceTypeEnum_OXYGENPLANT,
  kIfcMedicalDeviceTypeEnum_VACUUMSTATION,
  kIfcMedicalDeviceTypeEnum_USERDEFINED,
  kIfcMedicalDeviceTypeEnum_NOTDEFINED,
  kIfcMedicalDeviceTypeEnum_unset
};

class IFC4_EXPORT IfcMedicalDeviceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMedicalDeviceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcMedicalDeviceTypeEnum& getUnset<OdIfc4::IfcMedicalDeviceTypeEnum>() { static OdIfc4::IfcMedicalDeviceTypeEnum nullEnum = OdIfc4::kIfcMedicalDeviceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcMemberTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMemberTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcMemberTypeEnum& getUnset<OdIfc4::IfcMemberTypeEnum>() { static OdIfc4::IfcMemberTypeEnum nullEnum = OdIfc4::kIfcMemberTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcMotorConnectionTypeEnum
{
  kIfcMotorConnectionTypeEnum_BELTDRIVE,
  kIfcMotorConnectionTypeEnum_COUPLING,
  kIfcMotorConnectionTypeEnum_DIRECTDRIVE,
  kIfcMotorConnectionTypeEnum_USERDEFINED,
  kIfcMotorConnectionTypeEnum_NOTDEFINED,
  kIfcMotorConnectionTypeEnum_unset
};

class IFC4_EXPORT IfcMotorConnectionTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMotorConnectionTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcMotorConnectionTypeEnum& getUnset<OdIfc4::IfcMotorConnectionTypeEnum>() { static OdIfc4::IfcMotorConnectionTypeEnum nullEnum = OdIfc4::kIfcMotorConnectionTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcNullStyle
{
  kIfcNullStyle_NULL,
  kIfcNullStyle_unset
};

class IFC4_EXPORT IfcNullStyleTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcNullStyleTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcNullStyle& getUnset<OdIfc4::IfcNullStyle>() { static OdIfc4::IfcNullStyle nullEnum = OdIfc4::kIfcNullStyle_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcObjectTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcObjectTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcObjectTypeEnum& getUnset<OdIfc4::IfcObjectTypeEnum>() { static OdIfc4::IfcObjectTypeEnum nullEnum = OdIfc4::kIfcObjectTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcObjectiveEnum
{
  kIfcObjectiveEnum_CODECOMPLIANCE,
  kIfcObjectiveEnum_CODEWAIVER,
  kIfcObjectiveEnum_DESIGNINTENT,
  kIfcObjectiveEnum_EXTERNAL,
  kIfcObjectiveEnum_HEALTHANDSAFETY,
  kIfcObjectiveEnum_MERGECONFLICT,
  kIfcObjectiveEnum_MODELVIEW,
  kIfcObjectiveEnum_PARAMETER,
  kIfcObjectiveEnum_REQUIREMENT,
  kIfcObjectiveEnum_SPECIFICATION,
  kIfcObjectiveEnum_TRIGGERCONDITION,
  kIfcObjectiveEnum_USERDEFINED,
  kIfcObjectiveEnum_NOTDEFINED,
  kIfcObjectiveEnum_unset
};

class IFC4_EXPORT IfcObjectiveEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcObjectiveEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcObjectiveEnum& getUnset<OdIfc4::IfcObjectiveEnum>() { static OdIfc4::IfcObjectiveEnum nullEnum = OdIfc4::kIfcObjectiveEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcOccupantTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcOccupantTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcOccupantTypeEnum& getUnset<OdIfc4::IfcOccupantTypeEnum>() { static OdIfc4::IfcOccupantTypeEnum nullEnum = OdIfc4::kIfcOccupantTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcOpeningElementTypeEnum
{
  kIfcOpeningElementTypeEnum_OPENING,
  kIfcOpeningElementTypeEnum_RECESS,
  kIfcOpeningElementTypeEnum_USERDEFINED,
  kIfcOpeningElementTypeEnum_NOTDEFINED,
  kIfcOpeningElementTypeEnum_unset
};

class IFC4_EXPORT IfcOpeningElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcOpeningElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcOpeningElementTypeEnum& getUnset<OdIfc4::IfcOpeningElementTypeEnum>() { static OdIfc4::IfcOpeningElementTypeEnum nullEnum = OdIfc4::kIfcOpeningElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcOutletTypeEnum
{
  kIfcOutletTypeEnum_AUDIOVISUALOUTLET,
  kIfcOutletTypeEnum_COMMUNICATIONSOUTLET,
  kIfcOutletTypeEnum_POWEROUTLET,
  kIfcOutletTypeEnum_DATAOUTLET,
  kIfcOutletTypeEnum_TELEPHONEOUTLET,
  kIfcOutletTypeEnum_USERDEFINED,
  kIfcOutletTypeEnum_NOTDEFINED,
  kIfcOutletTypeEnum_unset
};

class IFC4_EXPORT IfcOutletTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcOutletTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcOutletTypeEnum& getUnset<OdIfc4::IfcOutletTypeEnum>() { static OdIfc4::IfcOutletTypeEnum nullEnum = OdIfc4::kIfcOutletTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcPerformanceHistoryTypeEnum
{
  kIfcPerformanceHistoryTypeEnum_USERDEFINED,
  kIfcPerformanceHistoryTypeEnum_NOTDEFINED,
  kIfcPerformanceHistoryTypeEnum_unset
};

class IFC4_EXPORT IfcPerformanceHistoryTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPerformanceHistoryTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcPerformanceHistoryTypeEnum& getUnset<OdIfc4::IfcPerformanceHistoryTypeEnum>() { static OdIfc4::IfcPerformanceHistoryTypeEnum nullEnum = OdIfc4::kIfcPerformanceHistoryTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcPermeableCoveringOperationEnum
{
  kIfcPermeableCoveringOperationEnum_GRILL,
  kIfcPermeableCoveringOperationEnum_LOUVER,
  kIfcPermeableCoveringOperationEnum_SCREEN,
  kIfcPermeableCoveringOperationEnum_USERDEFINED,
  kIfcPermeableCoveringOperationEnum_NOTDEFINED,
  kIfcPermeableCoveringOperationEnum_unset
};

class IFC4_EXPORT IfcPermeableCoveringOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPermeableCoveringOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcPermeableCoveringOperationEnum& getUnset<OdIfc4::IfcPermeableCoveringOperationEnum>() { static OdIfc4::IfcPermeableCoveringOperationEnum nullEnum = OdIfc4::kIfcPermeableCoveringOperationEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcPermitTypeEnum
{
  kIfcPermitTypeEnum_ACCESS,
  kIfcPermitTypeEnum_BUILDING,
  kIfcPermitTypeEnum_WORK,
  kIfcPermitTypeEnum_USERDEFINED,
  kIfcPermitTypeEnum_NOTDEFINED,
  kIfcPermitTypeEnum_unset
};

class IFC4_EXPORT IfcPermitTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPermitTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcPermitTypeEnum& getUnset<OdIfc4::IfcPermitTypeEnum>() { static OdIfc4::IfcPermitTypeEnum nullEnum = OdIfc4::kIfcPermitTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcPhysicalOrVirtualEnum
{
  kIfcPhysicalOrVirtualEnum_PHYSICAL,
  kIfcPhysicalOrVirtualEnum_VIRTUAL,
  kIfcPhysicalOrVirtualEnum_NOTDEFINED,
  kIfcPhysicalOrVirtualEnum_unset
};

class IFC4_EXPORT IfcPhysicalOrVirtualEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPhysicalOrVirtualEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcPhysicalOrVirtualEnum& getUnset<OdIfc4::IfcPhysicalOrVirtualEnum>() { static OdIfc4::IfcPhysicalOrVirtualEnum nullEnum = OdIfc4::kIfcPhysicalOrVirtualEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcPileConstructionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPileConstructionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcPileConstructionEnum& getUnset<OdIfc4::IfcPileConstructionEnum>() { static OdIfc4::IfcPileConstructionEnum nullEnum = OdIfc4::kIfcPileConstructionEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcPileTypeEnum
{
  kIfcPileTypeEnum_BORED,
  kIfcPileTypeEnum_DRIVEN,
  kIfcPileTypeEnum_JETGROUTING,
  kIfcPileTypeEnum_COHESION,
  kIfcPileTypeEnum_FRICTION,
  kIfcPileTypeEnum_SUPPORT,
  kIfcPileTypeEnum_USERDEFINED,
  kIfcPileTypeEnum_NOTDEFINED,
  kIfcPileTypeEnum_unset
};

class IFC4_EXPORT IfcPileTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPileTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcPileTypeEnum& getUnset<OdIfc4::IfcPileTypeEnum>() { static OdIfc4::IfcPileTypeEnum nullEnum = OdIfc4::kIfcPileTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcPipeFittingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPipeFittingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcPipeFittingTypeEnum& getUnset<OdIfc4::IfcPipeFittingTypeEnum>() { static OdIfc4::IfcPipeFittingTypeEnum nullEnum = OdIfc4::kIfcPipeFittingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcPipeSegmentTypeEnum
{
  kIfcPipeSegmentTypeEnum_CULVERT,
  kIfcPipeSegmentTypeEnum_FLEXIBLESEGMENT,
  kIfcPipeSegmentTypeEnum_RIGIDSEGMENT,
  kIfcPipeSegmentTypeEnum_GUTTER,
  kIfcPipeSegmentTypeEnum_SPOOL,
  kIfcPipeSegmentTypeEnum_USERDEFINED,
  kIfcPipeSegmentTypeEnum_NOTDEFINED,
  kIfcPipeSegmentTypeEnum_unset
};

class IFC4_EXPORT IfcPipeSegmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPipeSegmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcPipeSegmentTypeEnum& getUnset<OdIfc4::IfcPipeSegmentTypeEnum>() { static OdIfc4::IfcPipeSegmentTypeEnum nullEnum = OdIfc4::kIfcPipeSegmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcPlateTypeEnum
{
  kIfcPlateTypeEnum_CURTAIN_PANEL,
  kIfcPlateTypeEnum_SHEET,
  kIfcPlateTypeEnum_USERDEFINED,
  kIfcPlateTypeEnum_NOTDEFINED,
  kIfcPlateTypeEnum_unset
};

class IFC4_EXPORT IfcPlateTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPlateTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcPlateTypeEnum& getUnset<OdIfc4::IfcPlateTypeEnum>() { static OdIfc4::IfcPlateTypeEnum nullEnum = OdIfc4::kIfcPlateTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcPreferredSurfaceCurveRepresentation
{
  kIfcPreferredSurfaceCurveRepresentation_CURVE3D,
  kIfcPreferredSurfaceCurveRepresentation_PCURVE_S1,
  kIfcPreferredSurfaceCurveRepresentation_PCURVE_S2,
  kIfcPreferredSurfaceCurveRepresentation_unset
};

class IFC4_EXPORT IfcPreferredSurfaceCurveRepresentationTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPreferredSurfaceCurveRepresentationTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcPreferredSurfaceCurveRepresentation& getUnset<OdIfc4::IfcPreferredSurfaceCurveRepresentation>() { static OdIfc4::IfcPreferredSurfaceCurveRepresentation nullEnum = OdIfc4::kIfcPreferredSurfaceCurveRepresentation_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcProcedureTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProcedureTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcProcedureTypeEnum& getUnset<OdIfc4::IfcProcedureTypeEnum>() { static OdIfc4::IfcProcedureTypeEnum nullEnum = OdIfc4::kIfcProcedureTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcProfileTypeEnum
{
  kIfcProfileTypeEnum_CURVE,
  kIfcProfileTypeEnum_AREA,
  kIfcProfileTypeEnum_unset
};

class IFC4_EXPORT IfcProfileTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProfileTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcProfileTypeEnum& getUnset<OdIfc4::IfcProfileTypeEnum>() { static OdIfc4::IfcProfileTypeEnum nullEnum = OdIfc4::kIfcProfileTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcProjectOrderTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProjectOrderTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcProjectOrderTypeEnum& getUnset<OdIfc4::IfcProjectOrderTypeEnum>() { static OdIfc4::IfcProjectOrderTypeEnum nullEnum = OdIfc4::kIfcProjectOrderTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcProjectedOrTrueLengthEnum
{
  kIfcProjectedOrTrueLengthEnum_PROJECTED_LENGTH,
  kIfcProjectedOrTrueLengthEnum_TRUE_LENGTH,
  kIfcProjectedOrTrueLengthEnum_unset
};

class IFC4_EXPORT IfcProjectedOrTrueLengthEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProjectedOrTrueLengthEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcProjectedOrTrueLengthEnum& getUnset<OdIfc4::IfcProjectedOrTrueLengthEnum>() { static OdIfc4::IfcProjectedOrTrueLengthEnum nullEnum = OdIfc4::kIfcProjectedOrTrueLengthEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcProjectionElementTypeEnum
{
  kIfcProjectionElementTypeEnum_USERDEFINED,
  kIfcProjectionElementTypeEnum_NOTDEFINED,
  kIfcProjectionElementTypeEnum_unset
};

class IFC4_EXPORT IfcProjectionElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProjectionElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcProjectionElementTypeEnum& getUnset<OdIfc4::IfcProjectionElementTypeEnum>() { static OdIfc4::IfcProjectionElementTypeEnum nullEnum = OdIfc4::kIfcProjectionElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcPropertySetTemplateTypeEnum
{
  kIfcPropertySetTemplateTypeEnum_PSET_TYPEDRIVENONLY,
  kIfcPropertySetTemplateTypeEnum_PSET_TYPEDRIVENOVERRIDE,
  kIfcPropertySetTemplateTypeEnum_PSET_OCCURRENCEDRIVEN,
  kIfcPropertySetTemplateTypeEnum_PSET_PERFORMANCEDRIVEN,
  kIfcPropertySetTemplateTypeEnum_QTO_TYPEDRIVENONLY,
  kIfcPropertySetTemplateTypeEnum_QTO_TYPEDRIVENOVERRIDE,
  kIfcPropertySetTemplateTypeEnum_QTO_OCCURRENCEDRIVEN,
  kIfcPropertySetTemplateTypeEnum_NOTDEFINED,
  kIfcPropertySetTemplateTypeEnum_unset
};

class IFC4_EXPORT IfcPropertySetTemplateTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPropertySetTemplateTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcPropertySetTemplateTypeEnum& getUnset<OdIfc4::IfcPropertySetTemplateTypeEnum>() { static OdIfc4::IfcPropertySetTemplateTypeEnum nullEnum = OdIfc4::kIfcPropertySetTemplateTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcProtectiveDeviceTrippingUnitTypeEnum
{
  kIfcProtectiveDeviceTrippingUnitTypeEnum_ELECTRONIC,
  kIfcProtectiveDeviceTrippingUnitTypeEnum_ELECTROMAGNETIC,
  kIfcProtectiveDeviceTrippingUnitTypeEnum_RESIDUALCURRENT,
  kIfcProtectiveDeviceTrippingUnitTypeEnum_THERMAL,
  kIfcProtectiveDeviceTrippingUnitTypeEnum_USERDEFINED,
  kIfcProtectiveDeviceTrippingUnitTypeEnum_NOTDEFINED,
  kIfcProtectiveDeviceTrippingUnitTypeEnum_unset
};

class IFC4_EXPORT IfcProtectiveDeviceTrippingUnitTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProtectiveDeviceTrippingUnitTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcProtectiveDeviceTrippingUnitTypeEnum& getUnset<OdIfc4::IfcProtectiveDeviceTrippingUnitTypeEnum>() { static OdIfc4::IfcProtectiveDeviceTrippingUnitTypeEnum nullEnum = OdIfc4::kIfcProtectiveDeviceTrippingUnitTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcProtectiveDeviceTypeEnum
{
  kIfcProtectiveDeviceTypeEnum_CIRCUITBREAKER,
  kIfcProtectiveDeviceTypeEnum_EARTHLEAKAGECIRCUITBREAKER,
  kIfcProtectiveDeviceTypeEnum_EARTHINGSWITCH,
  kIfcProtectiveDeviceTypeEnum_FUSEDISCONNECTOR,
  kIfcProtectiveDeviceTypeEnum_RESIDUALCURRENTCIRCUITBREAKER,
  kIfcProtectiveDeviceTypeEnum_RESIDUALCURRENTSWITCH,
  kIfcProtectiveDeviceTypeEnum_VARISTOR,
  kIfcProtectiveDeviceTypeEnum_USERDEFINED,
  kIfcProtectiveDeviceTypeEnum_NOTDEFINED,
  kIfcProtectiveDeviceTypeEnum_unset
};

class IFC4_EXPORT IfcProtectiveDeviceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProtectiveDeviceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcProtectiveDeviceTypeEnum& getUnset<OdIfc4::IfcProtectiveDeviceTypeEnum>() { static OdIfc4::IfcProtectiveDeviceTypeEnum nullEnum = OdIfc4::kIfcProtectiveDeviceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcPumpTypeEnum
{
  kIfcPumpTypeEnum_CIRCULATOR,
  kIfcPumpTypeEnum_ENDSUCTION,
  kIfcPumpTypeEnum_SPLITCASE,
  kIfcPumpTypeEnum_SUBMERSIBLEPUMP,
  kIfcPumpTypeEnum_SUMPPUMP,
  kIfcPumpTypeEnum_VERTICALINLINE,
  kIfcPumpTypeEnum_VERTICALTURBINE,
  kIfcPumpTypeEnum_USERDEFINED,
  kIfcPumpTypeEnum_NOTDEFINED,
  kIfcPumpTypeEnum_unset
};

class IFC4_EXPORT IfcPumpTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPumpTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcPumpTypeEnum& getUnset<OdIfc4::IfcPumpTypeEnum>() { static OdIfc4::IfcPumpTypeEnum nullEnum = OdIfc4::kIfcPumpTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcRailingTypeEnum
{
  kIfcRailingTypeEnum_HANDRAIL,
  kIfcRailingTypeEnum_GUARDRAIL,
  kIfcRailingTypeEnum_BALUSTRADE,
  kIfcRailingTypeEnum_USERDEFINED,
  kIfcRailingTypeEnum_NOTDEFINED,
  kIfcRailingTypeEnum_unset
};

class IFC4_EXPORT IfcRailingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRailingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcRailingTypeEnum& getUnset<OdIfc4::IfcRailingTypeEnum>() { static OdIfc4::IfcRailingTypeEnum nullEnum = OdIfc4::kIfcRailingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcRampFlightTypeEnum
{
  kIfcRampFlightTypeEnum_STRAIGHT,
  kIfcRampFlightTypeEnum_SPIRAL,
  kIfcRampFlightTypeEnum_USERDEFINED,
  kIfcRampFlightTypeEnum_NOTDEFINED,
  kIfcRampFlightTypeEnum_unset
};

class IFC4_EXPORT IfcRampFlightTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRampFlightTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcRampFlightTypeEnum& getUnset<OdIfc4::IfcRampFlightTypeEnum>() { static OdIfc4::IfcRampFlightTypeEnum nullEnum = OdIfc4::kIfcRampFlightTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcRampTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRampTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcRampTypeEnum& getUnset<OdIfc4::IfcRampTypeEnum>() { static OdIfc4::IfcRampTypeEnum nullEnum = OdIfc4::kIfcRampTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcRecurrenceTypeEnum
{
  kIfcRecurrenceTypeEnum_DAILY,
  kIfcRecurrenceTypeEnum_WEEKLY,
  kIfcRecurrenceTypeEnum_MONTHLY_BY_DAY_OF_MONTH,
  kIfcRecurrenceTypeEnum_MONTHLY_BY_POSITION,
  kIfcRecurrenceTypeEnum_BY_DAY_COUNT,
  kIfcRecurrenceTypeEnum_BY_WEEKDAY_COUNT,
  kIfcRecurrenceTypeEnum_YEARLY_BY_DAY_OF_MONTH,
  kIfcRecurrenceTypeEnum_YEARLY_BY_POSITION,
  kIfcRecurrenceTypeEnum_unset
};

class IFC4_EXPORT IfcRecurrenceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRecurrenceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcRecurrenceTypeEnum& getUnset<OdIfc4::IfcRecurrenceTypeEnum>() { static OdIfc4::IfcRecurrenceTypeEnum nullEnum = OdIfc4::kIfcRecurrenceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcReflectanceMethodEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcReflectanceMethodEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcReflectanceMethodEnum& getUnset<OdIfc4::IfcReflectanceMethodEnum>() { static OdIfc4::IfcReflectanceMethodEnum nullEnum = OdIfc4::kIfcReflectanceMethodEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcReinforcingBarRoleEnum
{
  kIfcReinforcingBarRoleEnum_MAIN,
  kIfcReinforcingBarRoleEnum_SHEAR,
  kIfcReinforcingBarRoleEnum_LIGATURE,
  kIfcReinforcingBarRoleEnum_STUD,
  kIfcReinforcingBarRoleEnum_PUNCHING,
  kIfcReinforcingBarRoleEnum_EDGE,
  kIfcReinforcingBarRoleEnum_RING,
  kIfcReinforcingBarRoleEnum_ANCHORING,
  kIfcReinforcingBarRoleEnum_USERDEFINED,
  kIfcReinforcingBarRoleEnum_NOTDEFINED,
  kIfcReinforcingBarRoleEnum_unset
};

class IFC4_EXPORT IfcReinforcingBarRoleEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcReinforcingBarRoleEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcReinforcingBarRoleEnum& getUnset<OdIfc4::IfcReinforcingBarRoleEnum>() { static OdIfc4::IfcReinforcingBarRoleEnum nullEnum = OdIfc4::kIfcReinforcingBarRoleEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcReinforcingBarSurfaceEnum
{
  kIfcReinforcingBarSurfaceEnum_PLAIN,
  kIfcReinforcingBarSurfaceEnum_TEXTURED,
  kIfcReinforcingBarSurfaceEnum_unset
};

class IFC4_EXPORT IfcReinforcingBarSurfaceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcReinforcingBarSurfaceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcReinforcingBarSurfaceEnum& getUnset<OdIfc4::IfcReinforcingBarSurfaceEnum>() { static OdIfc4::IfcReinforcingBarSurfaceEnum nullEnum = OdIfc4::kIfcReinforcingBarSurfaceEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcReinforcingBarTypeEnum
{
  kIfcReinforcingBarTypeEnum_ANCHORING,
  kIfcReinforcingBarTypeEnum_EDGE,
  kIfcReinforcingBarTypeEnum_LIGATURE,
  kIfcReinforcingBarTypeEnum_MAIN,
  kIfcReinforcingBarTypeEnum_PUNCHING,
  kIfcReinforcingBarTypeEnum_RING,
  kIfcReinforcingBarTypeEnum_SHEAR,
  kIfcReinforcingBarTypeEnum_STUD,
  kIfcReinforcingBarTypeEnum_USERDEFINED,
  kIfcReinforcingBarTypeEnum_NOTDEFINED,
  kIfcReinforcingBarTypeEnum_unset
};

class IFC4_EXPORT IfcReinforcingBarTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcReinforcingBarTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcReinforcingBarTypeEnum& getUnset<OdIfc4::IfcReinforcingBarTypeEnum>() { static OdIfc4::IfcReinforcingBarTypeEnum nullEnum = OdIfc4::kIfcReinforcingBarTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcReinforcingMeshTypeEnum
{
  kIfcReinforcingMeshTypeEnum_USERDEFINED,
  kIfcReinforcingMeshTypeEnum_NOTDEFINED,
  kIfcReinforcingMeshTypeEnum_unset
};

class IFC4_EXPORT IfcReinforcingMeshTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcReinforcingMeshTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcReinforcingMeshTypeEnum& getUnset<OdIfc4::IfcReinforcingMeshTypeEnum>() { static OdIfc4::IfcReinforcingMeshTypeEnum nullEnum = OdIfc4::kIfcReinforcingMeshTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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
  kIfcRoleEnum_COMMISSIONINGENGINEER,
  kIfcRoleEnum_ENGINEER,
  kIfcRoleEnum_OWNER,
  kIfcRoleEnum_CONSULTANT,
  kIfcRoleEnum_CONSTRUCTIONMANAGER,
  kIfcRoleEnum_FIELDCONSTRUCTIONMANAGER,
  kIfcRoleEnum_RESELLER,
  kIfcRoleEnum_USERDEFINED,
  kIfcRoleEnum_unset
};

class IFC4_EXPORT IfcRoleEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRoleEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcRoleEnum& getUnset<OdIfc4::IfcRoleEnum>() { static OdIfc4::IfcRoleEnum nullEnum = OdIfc4::kIfcRoleEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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
  kIfcRoofTypeEnum_USERDEFINED,
  kIfcRoofTypeEnum_NOTDEFINED,
  kIfcRoofTypeEnum_unset
};

class IFC4_EXPORT IfcRoofTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRoofTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcRoofTypeEnum& getUnset<OdIfc4::IfcRoofTypeEnum>() { static OdIfc4::IfcRoofTypeEnum nullEnum = OdIfc4::kIfcRoofTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcSIPrefixTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSIPrefixTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcSIPrefix& getUnset<OdIfc4::IfcSIPrefix>() { static OdIfc4::IfcSIPrefix nullEnum = OdIfc4::kIfcSIPrefix_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcSIUnitNameTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSIUnitNameTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcSIUnitName& getUnset<OdIfc4::IfcSIUnitName>() { static OdIfc4::IfcSIUnitName nullEnum = OdIfc4::kIfcSIUnitName_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcSanitaryTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSanitaryTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcSanitaryTerminalTypeEnum& getUnset<OdIfc4::IfcSanitaryTerminalTypeEnum>() { static OdIfc4::IfcSanitaryTerminalTypeEnum nullEnum = OdIfc4::kIfcSanitaryTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcSectionTypeEnum
{
  kIfcSectionTypeEnum_UNIFORM,
  kIfcSectionTypeEnum_TAPERED,
  kIfcSectionTypeEnum_unset
};

class IFC4_EXPORT IfcSectionTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSectionTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcSectionTypeEnum& getUnset<OdIfc4::IfcSectionTypeEnum>() { static OdIfc4::IfcSectionTypeEnum nullEnum = OdIfc4::kIfcSectionTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcSensorTypeEnum
{
  kIfcSensorTypeEnum_COSENSOR,
  kIfcSensorTypeEnum_CO2SENSOR,
  kIfcSensorTypeEnum_CONDUCTANCESENSOR,
  kIfcSensorTypeEnum_CONTACTSENSOR,
  kIfcSensorTypeEnum_FIRESENSOR,
  kIfcSensorTypeEnum_FLOWSENSOR,
  kIfcSensorTypeEnum_FROSTSENSOR,
  kIfcSensorTypeEnum_GASSENSOR,
  kIfcSensorTypeEnum_HEATSENSOR,
  kIfcSensorTypeEnum_HUMIDITYSENSOR,
  kIfcSensorTypeEnum_IDENTIFIERSENSOR,
  kIfcSensorTypeEnum_IONCONCENTRATIONSENSOR,
  kIfcSensorTypeEnum_LEVELSENSOR,
  kIfcSensorTypeEnum_LIGHTSENSOR,
  kIfcSensorTypeEnum_MOISTURESENSOR,
  kIfcSensorTypeEnum_MOVEMENTSENSOR,
  kIfcSensorTypeEnum_PHSENSOR,
  kIfcSensorTypeEnum_PRESSURESENSOR,
  kIfcSensorTypeEnum_RADIATIONSENSOR,
  kIfcSensorTypeEnum_RADIOACTIVITYSENSOR,
  kIfcSensorTypeEnum_SMOKESENSOR,
  kIfcSensorTypeEnum_SOUNDSENSOR,
  kIfcSensorTypeEnum_TEMPERATURESENSOR,
  kIfcSensorTypeEnum_WINDSENSOR,
  kIfcSensorTypeEnum_USERDEFINED,
  kIfcSensorTypeEnum_NOTDEFINED,
  kIfcSensorTypeEnum_unset
};

class IFC4_EXPORT IfcSensorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSensorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcSensorTypeEnum& getUnset<OdIfc4::IfcSensorTypeEnum>() { static OdIfc4::IfcSensorTypeEnum nullEnum = OdIfc4::kIfcSensorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcSequenceEnum
{
  kIfcSequenceEnum_START_START,
  kIfcSequenceEnum_START_FINISH,
  kIfcSequenceEnum_FINISH_START,
  kIfcSequenceEnum_FINISH_FINISH,
  kIfcSequenceEnum_USERDEFINED,
  kIfcSequenceEnum_NOTDEFINED,
  kIfcSequenceEnum_unset
};

class IFC4_EXPORT IfcSequenceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSequenceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcSequenceEnum& getUnset<OdIfc4::IfcSequenceEnum>() { static OdIfc4::IfcSequenceEnum nullEnum = OdIfc4::kIfcSequenceEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcShadingDeviceTypeEnum
{
  kIfcShadingDeviceTypeEnum_JALOUSIE,
  kIfcShadingDeviceTypeEnum_SHUTTER,
  kIfcShadingDeviceTypeEnum_AWNING,
  kIfcShadingDeviceTypeEnum_USERDEFINED,
  kIfcShadingDeviceTypeEnum_NOTDEFINED,
  kIfcShadingDeviceTypeEnum_unset
};

class IFC4_EXPORT IfcShadingDeviceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcShadingDeviceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcShadingDeviceTypeEnum& getUnset<OdIfc4::IfcShadingDeviceTypeEnum>() { static OdIfc4::IfcShadingDeviceTypeEnum nullEnum = OdIfc4::kIfcShadingDeviceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcSimplePropertyTemplateTypeEnum
{
  kIfcSimplePropertyTemplateTypeEnum_P_SINGLEVALUE,
  kIfcSimplePropertyTemplateTypeEnum_P_ENUMERATEDVALUE,
  kIfcSimplePropertyTemplateTypeEnum_P_BOUNDEDVALUE,
  kIfcSimplePropertyTemplateTypeEnum_P_LISTVALUE,
  kIfcSimplePropertyTemplateTypeEnum_P_TABLEVALUE,
  kIfcSimplePropertyTemplateTypeEnum_P_REFERENCEVALUE,
  kIfcSimplePropertyTemplateTypeEnum_Q_LENGTH,
  kIfcSimplePropertyTemplateTypeEnum_Q_AREA,
  kIfcSimplePropertyTemplateTypeEnum_Q_VOLUME,
  kIfcSimplePropertyTemplateTypeEnum_Q_COUNT,
  kIfcSimplePropertyTemplateTypeEnum_Q_WEIGHT,
  kIfcSimplePropertyTemplateTypeEnum_Q_TIME,
  kIfcSimplePropertyTemplateTypeEnum_unset
};

class IFC4_EXPORT IfcSimplePropertyTemplateTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSimplePropertyTemplateTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcSimplePropertyTemplateTypeEnum& getUnset<OdIfc4::IfcSimplePropertyTemplateTypeEnum>() { static OdIfc4::IfcSimplePropertyTemplateTypeEnum nullEnum = OdIfc4::kIfcSimplePropertyTemplateTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcSlabTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSlabTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcSlabTypeEnum& getUnset<OdIfc4::IfcSlabTypeEnum>() { static OdIfc4::IfcSlabTypeEnum nullEnum = OdIfc4::kIfcSlabTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcSolarDeviceTypeEnum
{
  kIfcSolarDeviceTypeEnum_SOLARCOLLECTOR,
  kIfcSolarDeviceTypeEnum_SOLARPANEL,
  kIfcSolarDeviceTypeEnum_USERDEFINED,
  kIfcSolarDeviceTypeEnum_NOTDEFINED,
  kIfcSolarDeviceTypeEnum_unset
};

class IFC4_EXPORT IfcSolarDeviceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSolarDeviceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcSolarDeviceTypeEnum& getUnset<OdIfc4::IfcSolarDeviceTypeEnum>() { static OdIfc4::IfcSolarDeviceTypeEnum nullEnum = OdIfc4::kIfcSolarDeviceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcSpaceHeaterTypeEnum
{
  kIfcSpaceHeaterTypeEnum_CONVECTOR,
  kIfcSpaceHeaterTypeEnum_RADIATOR,
  kIfcSpaceHeaterTypeEnum_USERDEFINED,
  kIfcSpaceHeaterTypeEnum_NOTDEFINED,
  kIfcSpaceHeaterTypeEnum_unset
};

class IFC4_EXPORT IfcSpaceHeaterTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSpaceHeaterTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcSpaceHeaterTypeEnum& getUnset<OdIfc4::IfcSpaceHeaterTypeEnum>() { static OdIfc4::IfcSpaceHeaterTypeEnum nullEnum = OdIfc4::kIfcSpaceHeaterTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcSpaceTypeEnum
{
  kIfcSpaceTypeEnum_SPACE,
  kIfcSpaceTypeEnum_PARKING,
  kIfcSpaceTypeEnum_GFA,
  kIfcSpaceTypeEnum_INTERNAL,
  kIfcSpaceTypeEnum_EXTERNAL,
  kIfcSpaceTypeEnum_USERDEFINED,
  kIfcSpaceTypeEnum_NOTDEFINED,
  kIfcSpaceTypeEnum_unset
};

class IFC4_EXPORT IfcSpaceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSpaceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcSpaceTypeEnum& getUnset<OdIfc4::IfcSpaceTypeEnum>() { static OdIfc4::IfcSpaceTypeEnum nullEnum = OdIfc4::kIfcSpaceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcSpatialZoneTypeEnum
{
  kIfcSpatialZoneTypeEnum_CONSTRUCTION,
  kIfcSpatialZoneTypeEnum_FIRESAFETY,
  kIfcSpatialZoneTypeEnum_LIGHTING,
  kIfcSpatialZoneTypeEnum_OCCUPANCY,
  kIfcSpatialZoneTypeEnum_SECURITY,
  kIfcSpatialZoneTypeEnum_THERMAL,
  kIfcSpatialZoneTypeEnum_TRANSPORT,
  kIfcSpatialZoneTypeEnum_VENTILATION,
  kIfcSpatialZoneTypeEnum_USERDEFINED,
  kIfcSpatialZoneTypeEnum_NOTDEFINED,
  kIfcSpatialZoneTypeEnum_unset
};

class IFC4_EXPORT IfcSpatialZoneTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSpatialZoneTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcSpatialZoneTypeEnum& getUnset<OdIfc4::IfcSpatialZoneTypeEnum>() { static OdIfc4::IfcSpatialZoneTypeEnum nullEnum = OdIfc4::kIfcSpatialZoneTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcStackTerminalTypeEnum
{
  kIfcStackTerminalTypeEnum_BIRDCAGE,
  kIfcStackTerminalTypeEnum_COWL,
  kIfcStackTerminalTypeEnum_RAINWATERHOPPER,
  kIfcStackTerminalTypeEnum_USERDEFINED,
  kIfcStackTerminalTypeEnum_NOTDEFINED,
  kIfcStackTerminalTypeEnum_unset
};

class IFC4_EXPORT IfcStackTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStackTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcStackTerminalTypeEnum& getUnset<OdIfc4::IfcStackTerminalTypeEnum>() { static OdIfc4::IfcStackTerminalTypeEnum nullEnum = OdIfc4::kIfcStackTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcStairFlightTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStairFlightTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcStairFlightTypeEnum& getUnset<OdIfc4::IfcStairFlightTypeEnum>() { static OdIfc4::IfcStairFlightTypeEnum nullEnum = OdIfc4::kIfcStairFlightTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcStairTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStairTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcStairTypeEnum& getUnset<OdIfc4::IfcStairTypeEnum>() { static OdIfc4::IfcStairTypeEnum nullEnum = OdIfc4::kIfcStairTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcStateEnum
{
  kIfcStateEnum_READWRITE,
  kIfcStateEnum_READONLY,
  kIfcStateEnum_LOCKED,
  kIfcStateEnum_READWRITELOCKED,
  kIfcStateEnum_READONLYLOCKED,
  kIfcStateEnum_unset
};

class IFC4_EXPORT IfcStateEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStateEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcStateEnum& getUnset<OdIfc4::IfcStateEnum>() { static OdIfc4::IfcStateEnum nullEnum = OdIfc4::kIfcStateEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcStructuralCurveActivityTypeEnum
{
  kIfcStructuralCurveActivityTypeEnum_CONST,
  kIfcStructuralCurveActivityTypeEnum_LINEAR,
  kIfcStructuralCurveActivityTypeEnum_POLYGONAL,
  kIfcStructuralCurveActivityTypeEnum_EQUIDISTANT,
  kIfcStructuralCurveActivityTypeEnum_SINUS,
  kIfcStructuralCurveActivityTypeEnum_PARABOLA,
  kIfcStructuralCurveActivityTypeEnum_DISCRETE,
  kIfcStructuralCurveActivityTypeEnum_USERDEFINED,
  kIfcStructuralCurveActivityTypeEnum_NOTDEFINED,
  kIfcStructuralCurveActivityTypeEnum_unset
};

class IFC4_EXPORT IfcStructuralCurveActivityTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStructuralCurveActivityTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcStructuralCurveActivityTypeEnum& getUnset<OdIfc4::IfcStructuralCurveActivityTypeEnum>() { static OdIfc4::IfcStructuralCurveActivityTypeEnum nullEnum = OdIfc4::kIfcStructuralCurveActivityTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcStructuralCurveMemberTypeEnum
{
  kIfcStructuralCurveMemberTypeEnum_RIGID_JOINED_MEMBER,
  kIfcStructuralCurveMemberTypeEnum_PIN_JOINED_MEMBER,
  kIfcStructuralCurveMemberTypeEnum_CABLE,
  kIfcStructuralCurveMemberTypeEnum_TENSION_MEMBER,
  kIfcStructuralCurveMemberTypeEnum_COMPRESSION_MEMBER,
  kIfcStructuralCurveMemberTypeEnum_USERDEFINED,
  kIfcStructuralCurveMemberTypeEnum_NOTDEFINED,
  kIfcStructuralCurveMemberTypeEnum_unset
};

class IFC4_EXPORT IfcStructuralCurveMemberTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStructuralCurveMemberTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcStructuralCurveMemberTypeEnum& getUnset<OdIfc4::IfcStructuralCurveMemberTypeEnum>() { static OdIfc4::IfcStructuralCurveMemberTypeEnum nullEnum = OdIfc4::kIfcStructuralCurveMemberTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcStructuralSurfaceActivityTypeEnum
{
  kIfcStructuralSurfaceActivityTypeEnum_CONST,
  kIfcStructuralSurfaceActivityTypeEnum_BILINEAR,
  kIfcStructuralSurfaceActivityTypeEnum_DISCRETE,
  kIfcStructuralSurfaceActivityTypeEnum_ISOCONTOUR,
  kIfcStructuralSurfaceActivityTypeEnum_USERDEFINED,
  kIfcStructuralSurfaceActivityTypeEnum_NOTDEFINED,
  kIfcStructuralSurfaceActivityTypeEnum_unset
};

class IFC4_EXPORT IfcStructuralSurfaceActivityTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStructuralSurfaceActivityTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcStructuralSurfaceActivityTypeEnum& getUnset<OdIfc4::IfcStructuralSurfaceActivityTypeEnum>() { static OdIfc4::IfcStructuralSurfaceActivityTypeEnum nullEnum = OdIfc4::kIfcStructuralSurfaceActivityTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcStructuralSurfaceMemberTypeEnum
{
  kIfcStructuralSurfaceMemberTypeEnum_BENDING_ELEMENT,
  kIfcStructuralSurfaceMemberTypeEnum_MEMBRANE_ELEMENT,
  kIfcStructuralSurfaceMemberTypeEnum_SHELL,
  kIfcStructuralSurfaceMemberTypeEnum_USERDEFINED,
  kIfcStructuralSurfaceMemberTypeEnum_NOTDEFINED,
  kIfcStructuralSurfaceMemberTypeEnum_unset
};

class IFC4_EXPORT IfcStructuralSurfaceMemberTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStructuralSurfaceMemberTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcStructuralSurfaceMemberTypeEnum& getUnset<OdIfc4::IfcStructuralSurfaceMemberTypeEnum>() { static OdIfc4::IfcStructuralSurfaceMemberTypeEnum nullEnum = OdIfc4::kIfcStructuralSurfaceMemberTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcSubContractResourceTypeEnum
{
  kIfcSubContractResourceTypeEnum_PURCHASE,
  kIfcSubContractResourceTypeEnum_WORK,
  kIfcSubContractResourceTypeEnum_USERDEFINED,
  kIfcSubContractResourceTypeEnum_NOTDEFINED,
  kIfcSubContractResourceTypeEnum_unset
};

class IFC4_EXPORT IfcSubContractResourceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSubContractResourceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcSubContractResourceTypeEnum& getUnset<OdIfc4::IfcSubContractResourceTypeEnum>() { static OdIfc4::IfcSubContractResourceTypeEnum nullEnum = OdIfc4::kIfcSubContractResourceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcSurfaceFeatureTypeEnum
{
  kIfcSurfaceFeatureTypeEnum_MARK,
  kIfcSurfaceFeatureTypeEnum_TAG,
  kIfcSurfaceFeatureTypeEnum_TREATMENT,
  kIfcSurfaceFeatureTypeEnum_USERDEFINED,
  kIfcSurfaceFeatureTypeEnum_NOTDEFINED,
  kIfcSurfaceFeatureTypeEnum_unset
};

class IFC4_EXPORT IfcSurfaceFeatureTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSurfaceFeatureTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcSurfaceFeatureTypeEnum& getUnset<OdIfc4::IfcSurfaceFeatureTypeEnum>() { static OdIfc4::IfcSurfaceFeatureTypeEnum nullEnum = OdIfc4::kIfcSurfaceFeatureTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcSurfaceSide
{
  kIfcSurfaceSide_POSITIVE,
  kIfcSurfaceSide_NEGATIVE,
  kIfcSurfaceSide_BOTH,
  kIfcSurfaceSide_unset
};

class IFC4_EXPORT IfcSurfaceSideTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSurfaceSideTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcSurfaceSide& getUnset<OdIfc4::IfcSurfaceSide>() { static OdIfc4::IfcSurfaceSide nullEnum = OdIfc4::kIfcSurfaceSide_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcSwitchingDeviceTypeEnum
{
  kIfcSwitchingDeviceTypeEnum_CONTACTOR,
  kIfcSwitchingDeviceTypeEnum_DIMMERSWITCH,
  kIfcSwitchingDeviceTypeEnum_EMERGENCYSTOP,
  kIfcSwitchingDeviceTypeEnum_KEYPAD,
  kIfcSwitchingDeviceTypeEnum_MOMENTARYSWITCH,
  kIfcSwitchingDeviceTypeEnum_SELECTORSWITCH,
  kIfcSwitchingDeviceTypeEnum_STARTER,
  kIfcSwitchingDeviceTypeEnum_SWITCHDISCONNECTOR,
  kIfcSwitchingDeviceTypeEnum_TOGGLESWITCH,
  kIfcSwitchingDeviceTypeEnum_USERDEFINED,
  kIfcSwitchingDeviceTypeEnum_NOTDEFINED,
  kIfcSwitchingDeviceTypeEnum_unset
};

class IFC4_EXPORT IfcSwitchingDeviceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSwitchingDeviceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcSwitchingDeviceTypeEnum& getUnset<OdIfc4::IfcSwitchingDeviceTypeEnum>() { static OdIfc4::IfcSwitchingDeviceTypeEnum nullEnum = OdIfc4::kIfcSwitchingDeviceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcSystemFurnitureElementTypeEnum
{
  kIfcSystemFurnitureElementTypeEnum_PANEL,
  kIfcSystemFurnitureElementTypeEnum_WORKSURFACE,
  kIfcSystemFurnitureElementTypeEnum_USERDEFINED,
  kIfcSystemFurnitureElementTypeEnum_NOTDEFINED,
  kIfcSystemFurnitureElementTypeEnum_unset
};

class IFC4_EXPORT IfcSystemFurnitureElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSystemFurnitureElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcSystemFurnitureElementTypeEnum& getUnset<OdIfc4::IfcSystemFurnitureElementTypeEnum>() { static OdIfc4::IfcSystemFurnitureElementTypeEnum nullEnum = OdIfc4::kIfcSystemFurnitureElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcTankTypeEnum
{
  kIfcTankTypeEnum_BASIN,
  kIfcTankTypeEnum_BREAKPRESSURE,
  kIfcTankTypeEnum_EXPANSION,
  kIfcTankTypeEnum_FEEDANDEXPANSION,
  kIfcTankTypeEnum_PRESSUREVESSEL,
  kIfcTankTypeEnum_STORAGE,
  kIfcTankTypeEnum_VESSEL,
  kIfcTankTypeEnum_USERDEFINED,
  kIfcTankTypeEnum_NOTDEFINED,
  kIfcTankTypeEnum_unset
};

class IFC4_EXPORT IfcTankTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTankTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcTankTypeEnum& getUnset<OdIfc4::IfcTankTypeEnum>() { static OdIfc4::IfcTankTypeEnum nullEnum = OdIfc4::kIfcTankTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcTaskDurationEnum
{
  kIfcTaskDurationEnum_ELAPSEDTIME,
  kIfcTaskDurationEnum_WORKTIME,
  kIfcTaskDurationEnum_NOTDEFINED,
  kIfcTaskDurationEnum_unset
};

class IFC4_EXPORT IfcTaskDurationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTaskDurationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcTaskDurationEnum& getUnset<OdIfc4::IfcTaskDurationEnum>() { static OdIfc4::IfcTaskDurationEnum nullEnum = OdIfc4::kIfcTaskDurationEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcTaskTypeEnum
{
  kIfcTaskTypeEnum_ATTENDANCE,
  kIfcTaskTypeEnum_CONSTRUCTION,
  kIfcTaskTypeEnum_DEMOLITION,
  kIfcTaskTypeEnum_DISMANTLE,
  kIfcTaskTypeEnum_DISPOSAL,
  kIfcTaskTypeEnum_INSTALLATION,
  kIfcTaskTypeEnum_LOGISTIC,
  kIfcTaskTypeEnum_MAINTENANCE,
  kIfcTaskTypeEnum_MOVE,
  kIfcTaskTypeEnum_OPERATION,
  kIfcTaskTypeEnum_REMOVAL,
  kIfcTaskTypeEnum_RENOVATION,
  kIfcTaskTypeEnum_USERDEFINED,
  kIfcTaskTypeEnum_NOTDEFINED,
  kIfcTaskTypeEnum_unset
};

class IFC4_EXPORT IfcTaskTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTaskTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcTaskTypeEnum& getUnset<OdIfc4::IfcTaskTypeEnum>() { static OdIfc4::IfcTaskTypeEnum nullEnum = OdIfc4::kIfcTaskTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcTendonAnchorTypeEnum
{
  kIfcTendonAnchorTypeEnum_COUPLER,
  kIfcTendonAnchorTypeEnum_FIXED_END,
  kIfcTendonAnchorTypeEnum_TENSIONING_END,
  kIfcTendonAnchorTypeEnum_USERDEFINED,
  kIfcTendonAnchorTypeEnum_NOTDEFINED,
  kIfcTendonAnchorTypeEnum_unset
};

class IFC4_EXPORT IfcTendonAnchorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTendonAnchorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcTendonAnchorTypeEnum& getUnset<OdIfc4::IfcTendonAnchorTypeEnum>() { static OdIfc4::IfcTendonAnchorTypeEnum nullEnum = OdIfc4::kIfcTendonAnchorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcTendonTypeEnum
{
  kIfcTendonTypeEnum_BAR,
  kIfcTendonTypeEnum_COATED,
  kIfcTendonTypeEnum_STRAND,
  kIfcTendonTypeEnum_WIRE,
  kIfcTendonTypeEnum_USERDEFINED,
  kIfcTendonTypeEnum_NOTDEFINED,
  kIfcTendonTypeEnum_unset
};

class IFC4_EXPORT IfcTendonTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTendonTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcTendonTypeEnum& getUnset<OdIfc4::IfcTendonTypeEnum>() { static OdIfc4::IfcTendonTypeEnum nullEnum = OdIfc4::kIfcTendonTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcTextPath
{
  kIfcTextPath_LEFT,
  kIfcTextPath_RIGHT,
  kIfcTextPath_UP,
  kIfcTextPath_DOWN,
  kIfcTextPath_unset
};

class IFC4_EXPORT IfcTextPathTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTextPathTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcTextPath& getUnset<OdIfc4::IfcTextPath>() { static OdIfc4::IfcTextPath nullEnum = OdIfc4::kIfcTextPath_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcTimeSeriesDataTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTimeSeriesDataTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcTimeSeriesDataTypeEnum& getUnset<OdIfc4::IfcTimeSeriesDataTypeEnum>() { static OdIfc4::IfcTimeSeriesDataTypeEnum nullEnum = OdIfc4::kIfcTimeSeriesDataTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcTransformerTypeEnum
{
  kIfcTransformerTypeEnum_CURRENT,
  kIfcTransformerTypeEnum_FREQUENCY,
  kIfcTransformerTypeEnum_INVERTER,
  kIfcTransformerTypeEnum_RECTIFIER,
  kIfcTransformerTypeEnum_VOLTAGE,
  kIfcTransformerTypeEnum_USERDEFINED,
  kIfcTransformerTypeEnum_NOTDEFINED,
  kIfcTransformerTypeEnum_unset
};

class IFC4_EXPORT IfcTransformerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTransformerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcTransformerTypeEnum& getUnset<OdIfc4::IfcTransformerTypeEnum>() { static OdIfc4::IfcTransformerTypeEnum nullEnum = OdIfc4::kIfcTransformerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcTransitionCode
{
  kIfcTransitionCode_DISCONTINUOUS,
  kIfcTransitionCode_CONTINUOUS,
  kIfcTransitionCode_CONTSAMEGRADIENT,
  kIfcTransitionCode_CONTSAMEGRADIENTSAMECURVATURE,
  kIfcTransitionCode_unset
};

class IFC4_EXPORT IfcTransitionCodeTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTransitionCodeTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcTransitionCode& getUnset<OdIfc4::IfcTransitionCode>() { static OdIfc4::IfcTransitionCode nullEnum = OdIfc4::kIfcTransitionCode_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcTransportElementTypeEnum
{
  kIfcTransportElementTypeEnum_ELEVATOR,
  kIfcTransportElementTypeEnum_ESCALATOR,
  kIfcTransportElementTypeEnum_MOVINGWALKWAY,
  kIfcTransportElementTypeEnum_CRANEWAY,
  kIfcTransportElementTypeEnum_LIFTINGGEAR,
  kIfcTransportElementTypeEnum_USERDEFINED,
  kIfcTransportElementTypeEnum_NOTDEFINED,
  kIfcTransportElementTypeEnum_unset
};

class IFC4_EXPORT IfcTransportElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTransportElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcTransportElementTypeEnum& getUnset<OdIfc4::IfcTransportElementTypeEnum>() { static OdIfc4::IfcTransportElementTypeEnum nullEnum = OdIfc4::kIfcTransportElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcTrimmingPreference
{
  kIfcTrimmingPreference_CARTESIAN,
  kIfcTrimmingPreference_PARAMETER,
  kIfcTrimmingPreference_UNSPECIFIED,
  kIfcTrimmingPreference_unset
};

class IFC4_EXPORT IfcTrimmingPreferenceTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTrimmingPreferenceTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcTrimmingPreference& getUnset<OdIfc4::IfcTrimmingPreference>() { static OdIfc4::IfcTrimmingPreference nullEnum = OdIfc4::kIfcTrimmingPreference_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcTubeBundleTypeEnum
{
  kIfcTubeBundleTypeEnum_FINNED,
  kIfcTubeBundleTypeEnum_USERDEFINED,
  kIfcTubeBundleTypeEnum_NOTDEFINED,
  kIfcTubeBundleTypeEnum_unset
};

class IFC4_EXPORT IfcTubeBundleTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTubeBundleTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcTubeBundleTypeEnum& getUnset<OdIfc4::IfcTubeBundleTypeEnum>() { static OdIfc4::IfcTubeBundleTypeEnum nullEnum = OdIfc4::kIfcTubeBundleTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcUnitEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcUnitEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcUnitEnum& getUnset<OdIfc4::IfcUnitEnum>() { static OdIfc4::IfcUnitEnum nullEnum = OdIfc4::kIfcUnitEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcUnitaryControlElementTypeEnum
{
  kIfcUnitaryControlElementTypeEnum_ALARMPANEL,
  kIfcUnitaryControlElementTypeEnum_CONTROLPANEL,
  kIfcUnitaryControlElementTypeEnum_GASDETECTIONPANEL,
  kIfcUnitaryControlElementTypeEnum_INDICATORPANEL,
  kIfcUnitaryControlElementTypeEnum_MIMICPANEL,
  kIfcUnitaryControlElementTypeEnum_HUMIDISTAT,
  kIfcUnitaryControlElementTypeEnum_THERMOSTAT,
  kIfcUnitaryControlElementTypeEnum_WEATHERSTATION,
  kIfcUnitaryControlElementTypeEnum_USERDEFINED,
  kIfcUnitaryControlElementTypeEnum_NOTDEFINED,
  kIfcUnitaryControlElementTypeEnum_unset
};

class IFC4_EXPORT IfcUnitaryControlElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcUnitaryControlElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcUnitaryControlElementTypeEnum& getUnset<OdIfc4::IfcUnitaryControlElementTypeEnum>() { static OdIfc4::IfcUnitaryControlElementTypeEnum nullEnum = OdIfc4::kIfcUnitaryControlElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcUnitaryEquipmentTypeEnum
{
  kIfcUnitaryEquipmentTypeEnum_AIRHANDLER,
  kIfcUnitaryEquipmentTypeEnum_AIRCONDITIONINGUNIT,
  kIfcUnitaryEquipmentTypeEnum_DEHUMIDIFIER,
  kIfcUnitaryEquipmentTypeEnum_SPLITSYSTEM,
  kIfcUnitaryEquipmentTypeEnum_ROOFTOPUNIT,
  kIfcUnitaryEquipmentTypeEnum_USERDEFINED,
  kIfcUnitaryEquipmentTypeEnum_NOTDEFINED,
  kIfcUnitaryEquipmentTypeEnum_unset
};

class IFC4_EXPORT IfcUnitaryEquipmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcUnitaryEquipmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcUnitaryEquipmentTypeEnum& getUnset<OdIfc4::IfcUnitaryEquipmentTypeEnum>() { static OdIfc4::IfcUnitaryEquipmentTypeEnum nullEnum = OdIfc4::kIfcUnitaryEquipmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcValveTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcValveTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcValveTypeEnum& getUnset<OdIfc4::IfcValveTypeEnum>() { static OdIfc4::IfcValveTypeEnum nullEnum = OdIfc4::kIfcValveTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcVibrationIsolatorTypeEnum
{
  kIfcVibrationIsolatorTypeEnum_COMPRESSION,
  kIfcVibrationIsolatorTypeEnum_SPRING,
  kIfcVibrationIsolatorTypeEnum_USERDEFINED,
  kIfcVibrationIsolatorTypeEnum_NOTDEFINED,
  kIfcVibrationIsolatorTypeEnum_unset
};

class IFC4_EXPORT IfcVibrationIsolatorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcVibrationIsolatorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcVibrationIsolatorTypeEnum& getUnset<OdIfc4::IfcVibrationIsolatorTypeEnum>() { static OdIfc4::IfcVibrationIsolatorTypeEnum nullEnum = OdIfc4::kIfcVibrationIsolatorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcVoidingFeatureTypeEnum
{
  kIfcVoidingFeatureTypeEnum_CUTOUT,
  kIfcVoidingFeatureTypeEnum_NOTCH,
  kIfcVoidingFeatureTypeEnum_HOLE,
  kIfcVoidingFeatureTypeEnum_MITER,
  kIfcVoidingFeatureTypeEnum_CHAMFER,
  kIfcVoidingFeatureTypeEnum_EDGE,
  kIfcVoidingFeatureTypeEnum_USERDEFINED,
  kIfcVoidingFeatureTypeEnum_NOTDEFINED,
  kIfcVoidingFeatureTypeEnum_unset
};

class IFC4_EXPORT IfcVoidingFeatureTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcVoidingFeatureTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcVoidingFeatureTypeEnum& getUnset<OdIfc4::IfcVoidingFeatureTypeEnum>() { static OdIfc4::IfcVoidingFeatureTypeEnum nullEnum = OdIfc4::kIfcVoidingFeatureTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcWallTypeEnum
{
  kIfcWallTypeEnum_MOVABLE,
  kIfcWallTypeEnum_PARAPET,
  kIfcWallTypeEnum_PARTITIONING,
  kIfcWallTypeEnum_PLUMBINGWALL,
  kIfcWallTypeEnum_SHEAR,
  kIfcWallTypeEnum_SOLIDWALL,
  kIfcWallTypeEnum_STANDARD,
  kIfcWallTypeEnum_POLYGONAL,
  kIfcWallTypeEnum_ELEMENTEDWALL,
  kIfcWallTypeEnum_USERDEFINED,
  kIfcWallTypeEnum_NOTDEFINED,
  kIfcWallTypeEnum_unset
};

class IFC4_EXPORT IfcWallTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWallTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcWallTypeEnum& getUnset<OdIfc4::IfcWallTypeEnum>() { static OdIfc4::IfcWallTypeEnum nullEnum = OdIfc4::kIfcWallTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcWasteTerminalTypeEnum
{
  kIfcWasteTerminalTypeEnum_FLOORTRAP,
  kIfcWasteTerminalTypeEnum_FLOORWASTE,
  kIfcWasteTerminalTypeEnum_GULLYSUMP,
  kIfcWasteTerminalTypeEnum_GULLYTRAP,
  kIfcWasteTerminalTypeEnum_ROOFDRAIN,
  kIfcWasteTerminalTypeEnum_WASTEDISPOSALUNIT,
  kIfcWasteTerminalTypeEnum_WASTETRAP,
  kIfcWasteTerminalTypeEnum_USERDEFINED,
  kIfcWasteTerminalTypeEnum_NOTDEFINED,
  kIfcWasteTerminalTypeEnum_unset
};

class IFC4_EXPORT IfcWasteTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWasteTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcWasteTerminalTypeEnum& getUnset<OdIfc4::IfcWasteTerminalTypeEnum>() { static OdIfc4::IfcWasteTerminalTypeEnum nullEnum = OdIfc4::kIfcWasteTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcWindowPanelOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowPanelOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcWindowPanelOperationEnum& getUnset<OdIfc4::IfcWindowPanelOperationEnum>() { static OdIfc4::IfcWindowPanelOperationEnum nullEnum = OdIfc4::kIfcWindowPanelOperationEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcWindowPanelPositionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowPanelPositionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcWindowPanelPositionEnum& getUnset<OdIfc4::IfcWindowPanelPositionEnum>() { static OdIfc4::IfcWindowPanelPositionEnum nullEnum = OdIfc4::kIfcWindowPanelPositionEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcWindowStyleConstructionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowStyleConstructionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcWindowStyleConstructionEnum& getUnset<OdIfc4::IfcWindowStyleConstructionEnum>() { static OdIfc4::IfcWindowStyleConstructionEnum nullEnum = OdIfc4::kIfcWindowStyleConstructionEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
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

class IFC4_EXPORT IfcWindowStyleOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowStyleOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcWindowStyleOperationEnum& getUnset<OdIfc4::IfcWindowStyleOperationEnum>() { static OdIfc4::IfcWindowStyleOperationEnum nullEnum = OdIfc4::kIfcWindowStyleOperationEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcWindowTypeEnum
{
  kIfcWindowTypeEnum_WINDOW,
  kIfcWindowTypeEnum_SKYLIGHT,
  kIfcWindowTypeEnum_LIGHTDOME,
  kIfcWindowTypeEnum_USERDEFINED,
  kIfcWindowTypeEnum_NOTDEFINED,
  kIfcWindowTypeEnum_unset
};

class IFC4_EXPORT IfcWindowTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcWindowTypeEnum& getUnset<OdIfc4::IfcWindowTypeEnum>() { static OdIfc4::IfcWindowTypeEnum nullEnum = OdIfc4::kIfcWindowTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcWindowTypePartitioningEnum
{
  kIfcWindowTypePartitioningEnum_SINGLE_PANEL,
  kIfcWindowTypePartitioningEnum_DOUBLE_PANEL_VERTICAL,
  kIfcWindowTypePartitioningEnum_DOUBLE_PANEL_HORIZONTAL,
  kIfcWindowTypePartitioningEnum_TRIPLE_PANEL_VERTICAL,
  kIfcWindowTypePartitioningEnum_TRIPLE_PANEL_BOTTOM,
  kIfcWindowTypePartitioningEnum_TRIPLE_PANEL_TOP,
  kIfcWindowTypePartitioningEnum_TRIPLE_PANEL_LEFT,
  kIfcWindowTypePartitioningEnum_TRIPLE_PANEL_RIGHT,
  kIfcWindowTypePartitioningEnum_TRIPLE_PANEL_HORIZONTAL,
  kIfcWindowTypePartitioningEnum_USERDEFINED,
  kIfcWindowTypePartitioningEnum_NOTDEFINED,
  kIfcWindowTypePartitioningEnum_unset
};

class IFC4_EXPORT IfcWindowTypePartitioningEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowTypePartitioningEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcWindowTypePartitioningEnum& getUnset<OdIfc4::IfcWindowTypePartitioningEnum>() { static OdIfc4::IfcWindowTypePartitioningEnum nullEnum = OdIfc4::kIfcWindowTypePartitioningEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcWorkCalendarTypeEnum
{
  kIfcWorkCalendarTypeEnum_FIRSTSHIFT,
  kIfcWorkCalendarTypeEnum_SECONDSHIFT,
  kIfcWorkCalendarTypeEnum_THIRDSHIFT,
  kIfcWorkCalendarTypeEnum_USERDEFINED,
  kIfcWorkCalendarTypeEnum_NOTDEFINED,
  kIfcWorkCalendarTypeEnum_unset
};

class IFC4_EXPORT IfcWorkCalendarTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWorkCalendarTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcWorkCalendarTypeEnum& getUnset<OdIfc4::IfcWorkCalendarTypeEnum>() { static OdIfc4::IfcWorkCalendarTypeEnum nullEnum = OdIfc4::kIfcWorkCalendarTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcWorkPlanTypeEnum
{
  kIfcWorkPlanTypeEnum_ACTUAL,
  kIfcWorkPlanTypeEnum_BASELINE,
  kIfcWorkPlanTypeEnum_PLANNED,
  kIfcWorkPlanTypeEnum_USERDEFINED,
  kIfcWorkPlanTypeEnum_NOTDEFINED,
  kIfcWorkPlanTypeEnum_unset
};

class IFC4_EXPORT IfcWorkPlanTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWorkPlanTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcWorkPlanTypeEnum& getUnset<OdIfc4::IfcWorkPlanTypeEnum>() { static OdIfc4::IfcWorkPlanTypeEnum nullEnum = OdIfc4::kIfcWorkPlanTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {
enum IfcWorkScheduleTypeEnum
{
  kIfcWorkScheduleTypeEnum_ACTUAL,
  kIfcWorkScheduleTypeEnum_BASELINE,
  kIfcWorkScheduleTypeEnum_PLANNED,
  kIfcWorkScheduleTypeEnum_USERDEFINED,
  kIfcWorkScheduleTypeEnum_NOTDEFINED,
  kIfcWorkScheduleTypeEnum_unset
};

class IFC4_EXPORT IfcWorkScheduleTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWorkScheduleTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4::IfcWorkScheduleTypeEnum& getUnset<OdIfc4::IfcWorkScheduleTypeEnum>() { static OdIfc4::IfcWorkScheduleTypeEnum nullEnum = OdIfc4::kIfcWorkScheduleTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4 {

} // namespace

#endif // _IFC4_ENUM_H

