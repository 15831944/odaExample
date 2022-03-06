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

#ifndef _IFC4X3_RC4_ENUM_H
#define _IFC4X3_RC4_ENUM_H

#include "RxValue.h"
#include "daiEnum.h"
#include "Ifc4x3_RC4BuildOption.h"

namespace OdIfc4x3_rc4 {

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

class IFC4X3_RC4_EXPORT IfcActionRequestTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcActionRequestTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcActionRequestTypeEnum& getUnset<OdIfc4x3_rc4::IfcActionRequestTypeEnum>() { static OdIfc4x3_rc4::IfcActionRequestTypeEnum nullEnum = OdIfc4x3_rc4::kIfcActionRequestTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcActionSourceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcActionSourceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcActionSourceTypeEnum& getUnset<OdIfc4x3_rc4::IfcActionSourceTypeEnum>() { static OdIfc4x3_rc4::IfcActionSourceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcActionSourceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcActionTypeEnum
{
  kIfcActionTypeEnum_PERMANENT_G,
  kIfcActionTypeEnum_VARIABLE_Q,
  kIfcActionTypeEnum_EXTRAORDINARY_A,
  kIfcActionTypeEnum_USERDEFINED,
  kIfcActionTypeEnum_NOTDEFINED,
  kIfcActionTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcActionTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcActionTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcActionTypeEnum& getUnset<OdIfc4x3_rc4::IfcActionTypeEnum>() { static OdIfc4x3_rc4::IfcActionTypeEnum nullEnum = OdIfc4x3_rc4::kIfcActionTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcActuatorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcActuatorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcActuatorTypeEnum& getUnset<OdIfc4x3_rc4::IfcActuatorTypeEnum>() { static OdIfc4x3_rc4::IfcActuatorTypeEnum nullEnum = OdIfc4x3_rc4::kIfcActuatorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcAddressTypeEnum
{
  kIfcAddressTypeEnum_OFFICE,
  kIfcAddressTypeEnum_SITE,
  kIfcAddressTypeEnum_HOME,
  kIfcAddressTypeEnum_DISTRIBUTIONPOINT,
  kIfcAddressTypeEnum_USERDEFINED,
  kIfcAddressTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcAddressTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAddressTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcAddressTypeEnum& getUnset<OdIfc4x3_rc4::IfcAddressTypeEnum>() { static OdIfc4x3_rc4::IfcAddressTypeEnum nullEnum = OdIfc4x3_rc4::kIfcAddressTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcAirTerminalBoxTypeEnum
{
  kIfcAirTerminalBoxTypeEnum_CONSTANTFLOW,
  kIfcAirTerminalBoxTypeEnum_VARIABLEFLOWPRESSUREDEPENDANT,
  kIfcAirTerminalBoxTypeEnum_VARIABLEFLOWPRESSUREINDEPENDANT,
  kIfcAirTerminalBoxTypeEnum_USERDEFINED,
  kIfcAirTerminalBoxTypeEnum_NOTDEFINED,
  kIfcAirTerminalBoxTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcAirTerminalBoxTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAirTerminalBoxTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcAirTerminalBoxTypeEnum& getUnset<OdIfc4x3_rc4::IfcAirTerminalBoxTypeEnum>() { static OdIfc4x3_rc4::IfcAirTerminalBoxTypeEnum nullEnum = OdIfc4x3_rc4::kIfcAirTerminalBoxTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcAirTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAirTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcAirTerminalTypeEnum& getUnset<OdIfc4x3_rc4::IfcAirTerminalTypeEnum>() { static OdIfc4x3_rc4::IfcAirTerminalTypeEnum nullEnum = OdIfc4x3_rc4::kIfcAirTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcAirToAirHeatRecoveryTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAirToAirHeatRecoveryTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcAirToAirHeatRecoveryTypeEnum& getUnset<OdIfc4x3_rc4::IfcAirToAirHeatRecoveryTypeEnum>() { static OdIfc4x3_rc4::IfcAirToAirHeatRecoveryTypeEnum nullEnum = OdIfc4x3_rc4::kIfcAirToAirHeatRecoveryTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcAlarmTypeEnum
{
  kIfcAlarmTypeEnum_BELL,
  kIfcAlarmTypeEnum_BREAKGLASSBUTTON,
  kIfcAlarmTypeEnum_LIGHT,
  kIfcAlarmTypeEnum_MANUALPULLBOX,
  kIfcAlarmTypeEnum_SIREN,
  kIfcAlarmTypeEnum_WHISTLE,
  kIfcAlarmTypeEnum_RAILWAYCROCODILE,
  kIfcAlarmTypeEnum_RAILWAYDETONATOR,
  kIfcAlarmTypeEnum_USERDEFINED,
  kIfcAlarmTypeEnum_NOTDEFINED,
  kIfcAlarmTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcAlarmTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAlarmTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcAlarmTypeEnum& getUnset<OdIfc4x3_rc4::IfcAlarmTypeEnum>() { static OdIfc4x3_rc4::IfcAlarmTypeEnum nullEnum = OdIfc4x3_rc4::kIfcAlarmTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcAlignmentCantSegmentTypeEnum
{
  kIfcAlignmentCantSegmentTypeEnum_BLOSSCURVE,
  kIfcAlignmentCantSegmentTypeEnum_CONSTANTCANT,
  kIfcAlignmentCantSegmentTypeEnum_COSINECURVE,
  kIfcAlignmentCantSegmentTypeEnum_HELMERTCURVE,
  kIfcAlignmentCantSegmentTypeEnum_LINEARTRANSITION,
  kIfcAlignmentCantSegmentTypeEnum_SINECURVE,
  kIfcAlignmentCantSegmentTypeEnum_VIENNESEBEND,
  kIfcAlignmentCantSegmentTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcAlignmentCantSegmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAlignmentCantSegmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcAlignmentCantSegmentTypeEnum& getUnset<OdIfc4x3_rc4::IfcAlignmentCantSegmentTypeEnum>() { static OdIfc4x3_rc4::IfcAlignmentCantSegmentTypeEnum nullEnum = OdIfc4x3_rc4::kIfcAlignmentCantSegmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcAlignmentHorizontalSegmentTypeEnum
{
  kIfcAlignmentHorizontalSegmentTypeEnum_LINE,
  kIfcAlignmentHorizontalSegmentTypeEnum_CIRCULARARC,
  kIfcAlignmentHorizontalSegmentTypeEnum_CLOTHOID,
  kIfcAlignmentHorizontalSegmentTypeEnum_CUBIC,
  kIfcAlignmentHorizontalSegmentTypeEnum_HELMERTCURVE,
  kIfcAlignmentHorizontalSegmentTypeEnum_BLOSSCURVE,
  kIfcAlignmentHorizontalSegmentTypeEnum_COSINECURVE,
  kIfcAlignmentHorizontalSegmentTypeEnum_SINECURVE,
  kIfcAlignmentHorizontalSegmentTypeEnum_VIENNESEBEND,
  kIfcAlignmentHorizontalSegmentTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcAlignmentHorizontalSegmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAlignmentHorizontalSegmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcAlignmentHorizontalSegmentTypeEnum& getUnset<OdIfc4x3_rc4::IfcAlignmentHorizontalSegmentTypeEnum>() { static OdIfc4x3_rc4::IfcAlignmentHorizontalSegmentTypeEnum nullEnum = OdIfc4x3_rc4::kIfcAlignmentHorizontalSegmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcAlignmentTypeEnum
{
  kIfcAlignmentTypeEnum_USERDEFINED,
  kIfcAlignmentTypeEnum_NOTDEFINED,
  kIfcAlignmentTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcAlignmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAlignmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcAlignmentTypeEnum& getUnset<OdIfc4x3_rc4::IfcAlignmentTypeEnum>() { static OdIfc4x3_rc4::IfcAlignmentTypeEnum nullEnum = OdIfc4x3_rc4::kIfcAlignmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcAlignmentVerticalSegmentTypeEnum
{
  kIfcAlignmentVerticalSegmentTypeEnum_CONSTANTGRADIENT,
  kIfcAlignmentVerticalSegmentTypeEnum_CIRCULARARC,
  kIfcAlignmentVerticalSegmentTypeEnum_PARABOLICARC,
  kIfcAlignmentVerticalSegmentTypeEnum_CLOTHOID,
  kIfcAlignmentVerticalSegmentTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcAlignmentVerticalSegmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAlignmentVerticalSegmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcAlignmentVerticalSegmentTypeEnum& getUnset<OdIfc4x3_rc4::IfcAlignmentVerticalSegmentTypeEnum>() { static OdIfc4x3_rc4::IfcAlignmentVerticalSegmentTypeEnum nullEnum = OdIfc4x3_rc4::kIfcAlignmentVerticalSegmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcAnalysisModelTypeEnum
{
  kIfcAnalysisModelTypeEnum_IN_PLANE_LOADING_2D,
  kIfcAnalysisModelTypeEnum_OUT_PLANE_LOADING_2D,
  kIfcAnalysisModelTypeEnum_LOADING_3D,
  kIfcAnalysisModelTypeEnum_USERDEFINED,
  kIfcAnalysisModelTypeEnum_NOTDEFINED,
  kIfcAnalysisModelTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcAnalysisModelTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAnalysisModelTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcAnalysisModelTypeEnum& getUnset<OdIfc4x3_rc4::IfcAnalysisModelTypeEnum>() { static OdIfc4x3_rc4::IfcAnalysisModelTypeEnum nullEnum = OdIfc4x3_rc4::kIfcAnalysisModelTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcAnalysisTheoryTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAnalysisTheoryTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcAnalysisTheoryTypeEnum& getUnset<OdIfc4x3_rc4::IfcAnalysisTheoryTypeEnum>() { static OdIfc4x3_rc4::IfcAnalysisTheoryTypeEnum nullEnum = OdIfc4x3_rc4::kIfcAnalysisTheoryTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcAnnotationTypeEnum
{
  kIfcAnnotationTypeEnum_ASSUMEDPOINT,
  kIfcAnnotationTypeEnum_ASBUILTAREA,
  kIfcAnnotationTypeEnum_ASBUILTLINE,
  kIfcAnnotationTypeEnum_NON_PHYSICAL_SIGNAL,
  kIfcAnnotationTypeEnum_ASSUMEDLINE,
  kIfcAnnotationTypeEnum_WIDTHEVENT,
  kIfcAnnotationTypeEnum_ASSUMEDAREA,
  kIfcAnnotationTypeEnum_SUPERELEVATIONEVENT,
  kIfcAnnotationTypeEnum_ASBUILTPOINT,
  kIfcAnnotationTypeEnum_USERDEFINED,
  kIfcAnnotationTypeEnum_NOTDEFINED,
  kIfcAnnotationTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcAnnotationTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAnnotationTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcAnnotationTypeEnum& getUnset<OdIfc4x3_rc4::IfcAnnotationTypeEnum>() { static OdIfc4x3_rc4::IfcAnnotationTypeEnum nullEnum = OdIfc4x3_rc4::kIfcAnnotationTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcArithmeticOperatorEnum
{
  kIfcArithmeticOperatorEnum_ADD,
  kIfcArithmeticOperatorEnum_DIVIDE,
  kIfcArithmeticOperatorEnum_MULTIPLY,
  kIfcArithmeticOperatorEnum_SUBTRACT,
  kIfcArithmeticOperatorEnum_unset
};

class IFC4X3_RC4_EXPORT IfcArithmeticOperatorEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcArithmeticOperatorEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcArithmeticOperatorEnum& getUnset<OdIfc4x3_rc4::IfcArithmeticOperatorEnum>() { static OdIfc4x3_rc4::IfcArithmeticOperatorEnum nullEnum = OdIfc4x3_rc4::kIfcArithmeticOperatorEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcAssemblyPlaceEnum
{
  kIfcAssemblyPlaceEnum_SITE,
  kIfcAssemblyPlaceEnum_FACTORY,
  kIfcAssemblyPlaceEnum_NOTDEFINED,
  kIfcAssemblyPlaceEnum_unset
};

class IFC4X3_RC4_EXPORT IfcAssemblyPlaceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAssemblyPlaceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcAssemblyPlaceEnum& getUnset<OdIfc4x3_rc4::IfcAssemblyPlaceEnum>() { static OdIfc4x3_rc4::IfcAssemblyPlaceEnum nullEnum = OdIfc4x3_rc4::kIfcAssemblyPlaceEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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
  kIfcAudioVisualApplianceTypeEnum_COMMUNICATIONTERMINAL,
  kIfcAudioVisualApplianceTypeEnum_RECORDINGEQUIPMENT,
  kIfcAudioVisualApplianceTypeEnum_USERDEFINED,
  kIfcAudioVisualApplianceTypeEnum_NOTDEFINED,
  kIfcAudioVisualApplianceTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcAudioVisualApplianceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAudioVisualApplianceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcAudioVisualApplianceTypeEnum& getUnset<OdIfc4x3_rc4::IfcAudioVisualApplianceTypeEnum>() { static OdIfc4x3_rc4::IfcAudioVisualApplianceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcAudioVisualApplianceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcBSplineCurveFormTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBSplineCurveFormTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcBSplineCurveForm& getUnset<OdIfc4x3_rc4::IfcBSplineCurveForm>() { static OdIfc4x3_rc4::IfcBSplineCurveForm nullEnum = OdIfc4x3_rc4::kIfcBSplineCurveForm_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcBSplineSurfaceFormTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBSplineSurfaceFormTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcBSplineSurfaceForm& getUnset<OdIfc4x3_rc4::IfcBSplineSurfaceForm>() { static OdIfc4x3_rc4::IfcBSplineSurfaceForm nullEnum = OdIfc4x3_rc4::kIfcBSplineSurfaceForm_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcBeamTypeEnum
{
  kIfcBeamTypeEnum_BEAM,
  kIfcBeamTypeEnum_JOIST,
  kIfcBeamTypeEnum_HOLLOWCORE,
  kIfcBeamTypeEnum_LINTEL,
  kIfcBeamTypeEnum_SPANDREL,
  kIfcBeamTypeEnum_T_BEAM,
  kIfcBeamTypeEnum_GIRDER_SEGMENT,
  kIfcBeamTypeEnum_DIAPHRAGM,
  kIfcBeamTypeEnum_PIERCAP,
  kIfcBeamTypeEnum_HATSTONE,
  kIfcBeamTypeEnum_CORNICE,
  kIfcBeamTypeEnum_EDGEBEAM,
  kIfcBeamTypeEnum_USERDEFINED,
  kIfcBeamTypeEnum_NOTDEFINED,
  kIfcBeamTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcBeamTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBeamTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcBeamTypeEnum& getUnset<OdIfc4x3_rc4::IfcBeamTypeEnum>() { static OdIfc4x3_rc4::IfcBeamTypeEnum nullEnum = OdIfc4x3_rc4::kIfcBeamTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcBearingTypeDisplacementEnum
{
  kIfcBearingTypeDisplacementEnum_FIXED_MOVEMENT,
  kIfcBearingTypeDisplacementEnum_GUIDED_LONGITUDINAL,
  kIfcBearingTypeDisplacementEnum_GUIDED_TRANSVERSAL,
  kIfcBearingTypeDisplacementEnum_FREE_MOVEMENT,
  kIfcBearingTypeDisplacementEnum_NOTDEFINED,
  kIfcBearingTypeDisplacementEnum_unset
};

class IFC4X3_RC4_EXPORT IfcBearingTypeDisplacementEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBearingTypeDisplacementEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcBearingTypeDisplacementEnum& getUnset<OdIfc4x3_rc4::IfcBearingTypeDisplacementEnum>() { static OdIfc4x3_rc4::IfcBearingTypeDisplacementEnum nullEnum = OdIfc4x3_rc4::kIfcBearingTypeDisplacementEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcBearingTypeEnum
{
  kIfcBearingTypeEnum_CYLINDRICAL,
  kIfcBearingTypeEnum_SPHERICAL,
  kIfcBearingTypeEnum_ELASTOMERIC,
  kIfcBearingTypeEnum_POT,
  kIfcBearingTypeEnum_GUIDE,
  kIfcBearingTypeEnum_ROCKER,
  kIfcBearingTypeEnum_ROLLER,
  kIfcBearingTypeEnum_DISK,
  kIfcBearingTypeEnum_USERDEFINED,
  kIfcBearingTypeEnum_NOTDEFINED,
  kIfcBearingTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcBearingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBearingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcBearingTypeEnum& getUnset<OdIfc4x3_rc4::IfcBearingTypeEnum>() { static OdIfc4x3_rc4::IfcBearingTypeEnum nullEnum = OdIfc4x3_rc4::kIfcBearingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcBenchmarkEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBenchmarkEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcBenchmarkEnum& getUnset<OdIfc4x3_rc4::IfcBenchmarkEnum>() { static OdIfc4x3_rc4::IfcBenchmarkEnum nullEnum = OdIfc4x3_rc4::kIfcBenchmarkEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcBoilerTypeEnum
{
  kIfcBoilerTypeEnum_WATER,
  kIfcBoilerTypeEnum_STEAM,
  kIfcBoilerTypeEnum_USERDEFINED,
  kIfcBoilerTypeEnum_NOTDEFINED,
  kIfcBoilerTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcBoilerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBoilerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcBoilerTypeEnum& getUnset<OdIfc4x3_rc4::IfcBoilerTypeEnum>() { static OdIfc4x3_rc4::IfcBoilerTypeEnum nullEnum = OdIfc4x3_rc4::kIfcBoilerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcBooleanOperator
{
  kIfcBooleanOperator_UNION,
  kIfcBooleanOperator_INTERSECTION,
  kIfcBooleanOperator_DIFFERENCE,
  kIfcBooleanOperator_unset
};

class IFC4X3_RC4_EXPORT IfcBooleanOperatorTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBooleanOperatorTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcBooleanOperator& getUnset<OdIfc4x3_rc4::IfcBooleanOperator>() { static OdIfc4x3_rc4::IfcBooleanOperator nullEnum = OdIfc4x3_rc4::kIfcBooleanOperator_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcBridgePartTypeEnum
{
  kIfcBridgePartTypeEnum_ABUTMENT,
  kIfcBridgePartTypeEnum_DECK,
  kIfcBridgePartTypeEnum_DECK_SEGMENT,
  kIfcBridgePartTypeEnum_FOUNDATION,
  kIfcBridgePartTypeEnum_PIER,
  kIfcBridgePartTypeEnum_PIER_SEGMENT,
  kIfcBridgePartTypeEnum_PYLON,
  kIfcBridgePartTypeEnum_SUBSTRUCTURE,
  kIfcBridgePartTypeEnum_SUPERSTRUCTURE,
  kIfcBridgePartTypeEnum_SURFACESTRUCTURE,
  kIfcBridgePartTypeEnum_USERDEFINED,
  kIfcBridgePartTypeEnum_NOTDEFINED,
  kIfcBridgePartTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcBridgePartTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBridgePartTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcBridgePartTypeEnum& getUnset<OdIfc4x3_rc4::IfcBridgePartTypeEnum>() { static OdIfc4x3_rc4::IfcBridgePartTypeEnum nullEnum = OdIfc4x3_rc4::kIfcBridgePartTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcBridgeTypeEnum
{
  kIfcBridgeTypeEnum_ARCHED,
  kIfcBridgeTypeEnum_CABLE_STAYED,
  kIfcBridgeTypeEnum_CANTILEVER,
  kIfcBridgeTypeEnum_CULVERT,
  kIfcBridgeTypeEnum_FRAMEWORK,
  kIfcBridgeTypeEnum_GIRDER,
  kIfcBridgeTypeEnum_SUSPENSION,
  kIfcBridgeTypeEnum_TRUSS,
  kIfcBridgeTypeEnum_USERDEFINED,
  kIfcBridgeTypeEnum_NOTDEFINED,
  kIfcBridgeTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcBridgeTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBridgeTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcBridgeTypeEnum& getUnset<OdIfc4x3_rc4::IfcBridgeTypeEnum>() { static OdIfc4x3_rc4::IfcBridgeTypeEnum nullEnum = OdIfc4x3_rc4::kIfcBridgeTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcBuildingElementPartTypeEnum
{
  kIfcBuildingElementPartTypeEnum_INSULATION,
  kIfcBuildingElementPartTypeEnum_PRECASTPANEL,
  kIfcBuildingElementPartTypeEnum_APRON,
  kIfcBuildingElementPartTypeEnum_ARMOURUNIT,
  kIfcBuildingElementPartTypeEnum_SAFETYCAGE,
  kIfcBuildingElementPartTypeEnum_USERDEFINED,
  kIfcBuildingElementPartTypeEnum_NOTDEFINED,
  kIfcBuildingElementPartTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcBuildingElementPartTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBuildingElementPartTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcBuildingElementPartTypeEnum& getUnset<OdIfc4x3_rc4::IfcBuildingElementPartTypeEnum>() { static OdIfc4x3_rc4::IfcBuildingElementPartTypeEnum nullEnum = OdIfc4x3_rc4::kIfcBuildingElementPartTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcBuildingElementProxyTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBuildingElementProxyTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcBuildingElementProxyTypeEnum& getUnset<OdIfc4x3_rc4::IfcBuildingElementProxyTypeEnum>() { static OdIfc4x3_rc4::IfcBuildingElementProxyTypeEnum nullEnum = OdIfc4x3_rc4::kIfcBuildingElementProxyTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcBuildingSystemTypeEnum
{
  kIfcBuildingSystemTypeEnum_FENESTRATION,
  kIfcBuildingSystemTypeEnum_FOUNDATION,
  kIfcBuildingSystemTypeEnum_LOADBEARING,
  kIfcBuildingSystemTypeEnum_OUTERSHELL,
  kIfcBuildingSystemTypeEnum_SHADING,
  kIfcBuildingSystemTypeEnum_TRANSPORT,
  kIfcBuildingSystemTypeEnum_REINFORCING,
  kIfcBuildingSystemTypeEnum_PRESTRESSING,
  kIfcBuildingSystemTypeEnum_EROSIONPREVENTION,
  kIfcBuildingSystemTypeEnum_USERDEFINED,
  kIfcBuildingSystemTypeEnum_NOTDEFINED,
  kIfcBuildingSystemTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcBuildingSystemTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBuildingSystemTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcBuildingSystemTypeEnum& getUnset<OdIfc4x3_rc4::IfcBuildingSystemTypeEnum>() { static OdIfc4x3_rc4::IfcBuildingSystemTypeEnum nullEnum = OdIfc4x3_rc4::kIfcBuildingSystemTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcBuiltSystemTypeEnum
{
  kIfcBuiltSystemTypeEnum_REINFORCING,
  kIfcBuiltSystemTypeEnum_MOORING,
  kIfcBuiltSystemTypeEnum_OUTERSHELL,
  kIfcBuiltSystemTypeEnum_TRACKCIRCUIT,
  kIfcBuiltSystemTypeEnum_EROSIONPREVENTION,
  kIfcBuiltSystemTypeEnum_FOUNDATION,
  kIfcBuiltSystemTypeEnum_LOADBEARING,
  kIfcBuiltSystemTypeEnum_SHADING,
  kIfcBuiltSystemTypeEnum_FENESTRATION,
  kIfcBuiltSystemTypeEnum_TRANSPORT,
  kIfcBuiltSystemTypeEnum_PRESTRESSING,
  kIfcBuiltSystemTypeEnum_USERDEFINED,
  kIfcBuiltSystemTypeEnum_NOTDEFINED,
  kIfcBuiltSystemTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcBuiltSystemTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBuiltSystemTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcBuiltSystemTypeEnum& getUnset<OdIfc4x3_rc4::IfcBuiltSystemTypeEnum>() { static OdIfc4x3_rc4::IfcBuiltSystemTypeEnum nullEnum = OdIfc4x3_rc4::kIfcBuiltSystemTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcBurnerTypeEnum
{
  kIfcBurnerTypeEnum_USERDEFINED,
  kIfcBurnerTypeEnum_NOTDEFINED,
  kIfcBurnerTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcBurnerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBurnerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcBurnerTypeEnum& getUnset<OdIfc4x3_rc4::IfcBurnerTypeEnum>() { static OdIfc4x3_rc4::IfcBurnerTypeEnum nullEnum = OdIfc4x3_rc4::kIfcBurnerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcCableCarrierFittingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCableCarrierFittingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcCableCarrierFittingTypeEnum& getUnset<OdIfc4x3_rc4::IfcCableCarrierFittingTypeEnum>() { static OdIfc4x3_rc4::IfcCableCarrierFittingTypeEnum nullEnum = OdIfc4x3_rc4::kIfcCableCarrierFittingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcCableCarrierSegmentTypeEnum
{
  kIfcCableCarrierSegmentTypeEnum_CABLELADDERSEGMENT,
  kIfcCableCarrierSegmentTypeEnum_CABLETRAYSEGMENT,
  kIfcCableCarrierSegmentTypeEnum_CABLETRUNKINGSEGMENT,
  kIfcCableCarrierSegmentTypeEnum_CONDUITSEGMENT,
  kIfcCableCarrierSegmentTypeEnum_CABLEBRACKET,
  kIfcCableCarrierSegmentTypeEnum_CATENARYWIRE,
  kIfcCableCarrierSegmentTypeEnum_DROPPER,
  kIfcCableCarrierSegmentTypeEnum_USERDEFINED,
  kIfcCableCarrierSegmentTypeEnum_NOTDEFINED,
  kIfcCableCarrierSegmentTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcCableCarrierSegmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCableCarrierSegmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcCableCarrierSegmentTypeEnum& getUnset<OdIfc4x3_rc4::IfcCableCarrierSegmentTypeEnum>() { static OdIfc4x3_rc4::IfcCableCarrierSegmentTypeEnum nullEnum = OdIfc4x3_rc4::kIfcCableCarrierSegmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcCableFittingTypeEnum
{
  kIfcCableFittingTypeEnum_CONNECTOR,
  kIfcCableFittingTypeEnum_ENTRY,
  kIfcCableFittingTypeEnum_EXIT,
  kIfcCableFittingTypeEnum_JUNCTION,
  kIfcCableFittingTypeEnum_TRANSITION,
  kIfcCableFittingTypeEnum_FANOUT,
  kIfcCableFittingTypeEnum_USERDEFINED,
  kIfcCableFittingTypeEnum_NOTDEFINED,
  kIfcCableFittingTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcCableFittingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCableFittingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcCableFittingTypeEnum& getUnset<OdIfc4x3_rc4::IfcCableFittingTypeEnum>() { static OdIfc4x3_rc4::IfcCableFittingTypeEnum nullEnum = OdIfc4x3_rc4::kIfcCableFittingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcCableSegmentTypeEnum
{
  kIfcCableSegmentTypeEnum_BUSBARSEGMENT,
  kIfcCableSegmentTypeEnum_CABLESEGMENT,
  kIfcCableSegmentTypeEnum_CONDUCTORSEGMENT,
  kIfcCableSegmentTypeEnum_CORESEGMENT,
  kIfcCableSegmentTypeEnum_CONTACTWIRESEGMENT,
  kIfcCableSegmentTypeEnum_FIBERSEGMENT,
  kIfcCableSegmentTypeEnum_FIBERTUBE,
  kIfcCableSegmentTypeEnum_OPTICALCABLESEGMENT,
  kIfcCableSegmentTypeEnum_STITCHWIRE,
  kIfcCableSegmentTypeEnum_WIREPAIRSEGMENT,
  kIfcCableSegmentTypeEnum_USERDEFINED,
  kIfcCableSegmentTypeEnum_NOTDEFINED,
  kIfcCableSegmentTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcCableSegmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCableSegmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcCableSegmentTypeEnum& getUnset<OdIfc4x3_rc4::IfcCableSegmentTypeEnum>() { static OdIfc4x3_rc4::IfcCableSegmentTypeEnum nullEnum = OdIfc4x3_rc4::kIfcCableSegmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcCaissonFoundationTypeEnum
{
  kIfcCaissonFoundationTypeEnum_WELL,
  kIfcCaissonFoundationTypeEnum_CAISSON,
  kIfcCaissonFoundationTypeEnum_USERDEFINED,
  kIfcCaissonFoundationTypeEnum_NOTDEFINED,
  kIfcCaissonFoundationTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcCaissonFoundationTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCaissonFoundationTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcCaissonFoundationTypeEnum& getUnset<OdIfc4x3_rc4::IfcCaissonFoundationTypeEnum>() { static OdIfc4x3_rc4::IfcCaissonFoundationTypeEnum nullEnum = OdIfc4x3_rc4::kIfcCaissonFoundationTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcChangeActionEnum
{
  kIfcChangeActionEnum_NOCHANGE,
  kIfcChangeActionEnum_MODIFIED,
  kIfcChangeActionEnum_ADDED,
  kIfcChangeActionEnum_DELETED,
  kIfcChangeActionEnum_NOTDEFINED,
  kIfcChangeActionEnum_unset
};

class IFC4X3_RC4_EXPORT IfcChangeActionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcChangeActionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcChangeActionEnum& getUnset<OdIfc4x3_rc4::IfcChangeActionEnum>() { static OdIfc4x3_rc4::IfcChangeActionEnum nullEnum = OdIfc4x3_rc4::kIfcChangeActionEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcChillerTypeEnum
{
  kIfcChillerTypeEnum_AIRCOOLED,
  kIfcChillerTypeEnum_WATERCOOLED,
  kIfcChillerTypeEnum_HEATRECOVERY,
  kIfcChillerTypeEnum_USERDEFINED,
  kIfcChillerTypeEnum_NOTDEFINED,
  kIfcChillerTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcChillerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcChillerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcChillerTypeEnum& getUnset<OdIfc4x3_rc4::IfcChillerTypeEnum>() { static OdIfc4x3_rc4::IfcChillerTypeEnum nullEnum = OdIfc4x3_rc4::kIfcChillerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcChimneyTypeEnum
{
  kIfcChimneyTypeEnum_USERDEFINED,
  kIfcChimneyTypeEnum_NOTDEFINED,
  kIfcChimneyTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcChimneyTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcChimneyTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcChimneyTypeEnum& getUnset<OdIfc4x3_rc4::IfcChimneyTypeEnum>() { static OdIfc4x3_rc4::IfcChimneyTypeEnum nullEnum = OdIfc4x3_rc4::kIfcChimneyTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcCoilTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCoilTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcCoilTypeEnum& getUnset<OdIfc4x3_rc4::IfcCoilTypeEnum>() { static OdIfc4x3_rc4::IfcCoilTypeEnum nullEnum = OdIfc4x3_rc4::kIfcCoilTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcColumnTypeEnum
{
  kIfcColumnTypeEnum_COLUMN,
  kIfcColumnTypeEnum_PILASTER,
  kIfcColumnTypeEnum_PIERSTEM,
  kIfcColumnTypeEnum_PIERSTEM_SEGMENT,
  kIfcColumnTypeEnum_STANDCOLUMN,
  kIfcColumnTypeEnum_USERDEFINED,
  kIfcColumnTypeEnum_NOTDEFINED,
  kIfcColumnTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcColumnTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcColumnTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcColumnTypeEnum& getUnset<OdIfc4x3_rc4::IfcColumnTypeEnum>() { static OdIfc4x3_rc4::IfcColumnTypeEnum nullEnum = OdIfc4x3_rc4::kIfcColumnTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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
  kIfcCommunicationsApplianceTypeEnum_AUTOMATON,
  kIfcCommunicationsApplianceTypeEnum_INTELLIGENTPERIPHERAL,
  kIfcCommunicationsApplianceTypeEnum_IPNETWORKEQUIPMENT,
  kIfcCommunicationsApplianceTypeEnum_OPTICALNETWORKUNIT,
  kIfcCommunicationsApplianceTypeEnum_TELECOMMAND,
  kIfcCommunicationsApplianceTypeEnum_TELEPHONYEXCHANGE,
  kIfcCommunicationsApplianceTypeEnum_TRANSITIONCOMPONENT,
  kIfcCommunicationsApplianceTypeEnum_TRANSPONDER,
  kIfcCommunicationsApplianceTypeEnum_TRANSPORTEQUIPMENT,
  kIfcCommunicationsApplianceTypeEnum_OPTICALLINETERMINAL,
  kIfcCommunicationsApplianceTypeEnum_LINESIDEELECTRONICUNIT,
  kIfcCommunicationsApplianceTypeEnum_RADIOBLOCKCENTER,
  kIfcCommunicationsApplianceTypeEnum_USERDEFINED,
  kIfcCommunicationsApplianceTypeEnum_NOTDEFINED,
  kIfcCommunicationsApplianceTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcCommunicationsApplianceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCommunicationsApplianceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcCommunicationsApplianceTypeEnum& getUnset<OdIfc4x3_rc4::IfcCommunicationsApplianceTypeEnum>() { static OdIfc4x3_rc4::IfcCommunicationsApplianceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcCommunicationsApplianceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcComplexPropertyTemplateTypeEnum
{
  kIfcComplexPropertyTemplateTypeEnum_P_COMPLEX,
  kIfcComplexPropertyTemplateTypeEnum_Q_COMPLEX,
  kIfcComplexPropertyTemplateTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcComplexPropertyTemplateTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcComplexPropertyTemplateTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcComplexPropertyTemplateTypeEnum& getUnset<OdIfc4x3_rc4::IfcComplexPropertyTemplateTypeEnum>() { static OdIfc4x3_rc4::IfcComplexPropertyTemplateTypeEnum nullEnum = OdIfc4x3_rc4::kIfcComplexPropertyTemplateTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcCompressorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCompressorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcCompressorTypeEnum& getUnset<OdIfc4x3_rc4::IfcCompressorTypeEnum>() { static OdIfc4x3_rc4::IfcCompressorTypeEnum nullEnum = OdIfc4x3_rc4::kIfcCompressorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcCondenserTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCondenserTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcCondenserTypeEnum& getUnset<OdIfc4x3_rc4::IfcCondenserTypeEnum>() { static OdIfc4x3_rc4::IfcCondenserTypeEnum nullEnum = OdIfc4x3_rc4::kIfcCondenserTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcConnectionTypeEnum
{
  kIfcConnectionTypeEnum_ATPATH,
  kIfcConnectionTypeEnum_ATSTART,
  kIfcConnectionTypeEnum_ATEND,
  kIfcConnectionTypeEnum_NOTDEFINED,
  kIfcConnectionTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcConnectionTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcConnectionTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcConnectionTypeEnum& getUnset<OdIfc4x3_rc4::IfcConnectionTypeEnum>() { static OdIfc4x3_rc4::IfcConnectionTypeEnum nullEnum = OdIfc4x3_rc4::kIfcConnectionTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcConstraintEnum
{
  kIfcConstraintEnum_HARD,
  kIfcConstraintEnum_SOFT,
  kIfcConstraintEnum_ADVISORY,
  kIfcConstraintEnum_USERDEFINED,
  kIfcConstraintEnum_NOTDEFINED,
  kIfcConstraintEnum_unset
};

class IFC4X3_RC4_EXPORT IfcConstraintEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcConstraintEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcConstraintEnum& getUnset<OdIfc4x3_rc4::IfcConstraintEnum>() { static OdIfc4x3_rc4::IfcConstraintEnum nullEnum = OdIfc4x3_rc4::kIfcConstraintEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcConstructionEquipmentResourceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcConstructionEquipmentResourceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcConstructionEquipmentResourceTypeEnum& getUnset<OdIfc4x3_rc4::IfcConstructionEquipmentResourceTypeEnum>() { static OdIfc4x3_rc4::IfcConstructionEquipmentResourceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcConstructionEquipmentResourceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcConstructionMaterialResourceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcConstructionMaterialResourceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcConstructionMaterialResourceTypeEnum& getUnset<OdIfc4x3_rc4::IfcConstructionMaterialResourceTypeEnum>() { static OdIfc4x3_rc4::IfcConstructionMaterialResourceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcConstructionMaterialResourceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcConstructionProductResourceTypeEnum
{
  kIfcConstructionProductResourceTypeEnum_ASSEMBLY,
  kIfcConstructionProductResourceTypeEnum_FORMWORK,
  kIfcConstructionProductResourceTypeEnum_USERDEFINED,
  kIfcConstructionProductResourceTypeEnum_NOTDEFINED,
  kIfcConstructionProductResourceTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcConstructionProductResourceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcConstructionProductResourceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcConstructionProductResourceTypeEnum& getUnset<OdIfc4x3_rc4::IfcConstructionProductResourceTypeEnum>() { static OdIfc4x3_rc4::IfcConstructionProductResourceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcConstructionProductResourceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcControllerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcControllerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcControllerTypeEnum& getUnset<OdIfc4x3_rc4::IfcControllerTypeEnum>() { static OdIfc4x3_rc4::IfcControllerTypeEnum nullEnum = OdIfc4x3_rc4::kIfcControllerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcConveyorSegmentTypeEnum
{
  kIfcConveyorSegmentTypeEnum_CHUTECONVEYOR,
  kIfcConveyorSegmentTypeEnum_BELTCONVEYOR,
  kIfcConveyorSegmentTypeEnum_SCREWCONVEYOR,
  kIfcConveyorSegmentTypeEnum_BUCKETCONVEYOR,
  kIfcConveyorSegmentTypeEnum_USERDEFINED,
  kIfcConveyorSegmentTypeEnum_NOTDEFINED,
  kIfcConveyorSegmentTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcConveyorSegmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcConveyorSegmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcConveyorSegmentTypeEnum& getUnset<OdIfc4x3_rc4::IfcConveyorSegmentTypeEnum>() { static OdIfc4x3_rc4::IfcConveyorSegmentTypeEnum nullEnum = OdIfc4x3_rc4::kIfcConveyorSegmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcCooledBeamTypeEnum
{
  kIfcCooledBeamTypeEnum_ACTIVE,
  kIfcCooledBeamTypeEnum_PASSIVE,
  kIfcCooledBeamTypeEnum_USERDEFINED,
  kIfcCooledBeamTypeEnum_NOTDEFINED,
  kIfcCooledBeamTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcCooledBeamTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCooledBeamTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcCooledBeamTypeEnum& getUnset<OdIfc4x3_rc4::IfcCooledBeamTypeEnum>() { static OdIfc4x3_rc4::IfcCooledBeamTypeEnum nullEnum = OdIfc4x3_rc4::kIfcCooledBeamTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcCoolingTowerTypeEnum
{
  kIfcCoolingTowerTypeEnum_NATURALDRAFT,
  kIfcCoolingTowerTypeEnum_MECHANICALINDUCEDDRAFT,
  kIfcCoolingTowerTypeEnum_MECHANICALFORCEDDRAFT,
  kIfcCoolingTowerTypeEnum_USERDEFINED,
  kIfcCoolingTowerTypeEnum_NOTDEFINED,
  kIfcCoolingTowerTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcCoolingTowerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCoolingTowerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcCoolingTowerTypeEnum& getUnset<OdIfc4x3_rc4::IfcCoolingTowerTypeEnum>() { static OdIfc4x3_rc4::IfcCoolingTowerTypeEnum nullEnum = OdIfc4x3_rc4::kIfcCoolingTowerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcCostItemTypeEnum
{
  kIfcCostItemTypeEnum_USERDEFINED,
  kIfcCostItemTypeEnum_NOTDEFINED,
  kIfcCostItemTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcCostItemTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCostItemTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcCostItemTypeEnum& getUnset<OdIfc4x3_rc4::IfcCostItemTypeEnum>() { static OdIfc4x3_rc4::IfcCostItemTypeEnum nullEnum = OdIfc4x3_rc4::kIfcCostItemTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcCostScheduleTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCostScheduleTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcCostScheduleTypeEnum& getUnset<OdIfc4x3_rc4::IfcCostScheduleTypeEnum>() { static OdIfc4x3_rc4::IfcCostScheduleTypeEnum nullEnum = OdIfc4x3_rc4::kIfcCostScheduleTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcCourseTypeEnum
{
  kIfcCourseTypeEnum_ARMOUR,
  kIfcCourseTypeEnum_FILTER,
  kIfcCourseTypeEnum_BALLASTBED,
  kIfcCourseTypeEnum_CORE,
  kIfcCourseTypeEnum_PAVEMENT,
  kIfcCourseTypeEnum_PROTECTION,
  kIfcCourseTypeEnum_USERDEFINED,
  kIfcCourseTypeEnum_NOTDEFINED,
  kIfcCourseTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcCourseTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCourseTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcCourseTypeEnum& getUnset<OdIfc4x3_rc4::IfcCourseTypeEnum>() { static OdIfc4x3_rc4::IfcCourseTypeEnum nullEnum = OdIfc4x3_rc4::kIfcCourseTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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
  kIfcCoveringTypeEnum_COPING,
  kIfcCoveringTypeEnum_USERDEFINED,
  kIfcCoveringTypeEnum_NOTDEFINED,
  kIfcCoveringTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcCoveringTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCoveringTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcCoveringTypeEnum& getUnset<OdIfc4x3_rc4::IfcCoveringTypeEnum>() { static OdIfc4x3_rc4::IfcCoveringTypeEnum nullEnum = OdIfc4x3_rc4::kIfcCoveringTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcCrewResourceTypeEnum
{
  kIfcCrewResourceTypeEnum_OFFICE,
  kIfcCrewResourceTypeEnum_SITE,
  kIfcCrewResourceTypeEnum_USERDEFINED,
  kIfcCrewResourceTypeEnum_NOTDEFINED,
  kIfcCrewResourceTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcCrewResourceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCrewResourceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcCrewResourceTypeEnum& getUnset<OdIfc4x3_rc4::IfcCrewResourceTypeEnum>() { static OdIfc4x3_rc4::IfcCrewResourceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcCrewResourceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcCurtainWallTypeEnum
{
  kIfcCurtainWallTypeEnum_USERDEFINED,
  kIfcCurtainWallTypeEnum_NOTDEFINED,
  kIfcCurtainWallTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcCurtainWallTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCurtainWallTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcCurtainWallTypeEnum& getUnset<OdIfc4x3_rc4::IfcCurtainWallTypeEnum>() { static OdIfc4x3_rc4::IfcCurtainWallTypeEnum nullEnum = OdIfc4x3_rc4::kIfcCurtainWallTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcCurveInterpolationEnum
{
  kIfcCurveInterpolationEnum_LINEAR,
  kIfcCurveInterpolationEnum_LOG_LINEAR,
  kIfcCurveInterpolationEnum_LOG_LOG,
  kIfcCurveInterpolationEnum_NOTDEFINED,
  kIfcCurveInterpolationEnum_unset
};

class IFC4X3_RC4_EXPORT IfcCurveInterpolationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCurveInterpolationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcCurveInterpolationEnum& getUnset<OdIfc4x3_rc4::IfcCurveInterpolationEnum>() { static OdIfc4x3_rc4::IfcCurveInterpolationEnum nullEnum = OdIfc4x3_rc4::kIfcCurveInterpolationEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcDamperTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDamperTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcDamperTypeEnum& getUnset<OdIfc4x3_rc4::IfcDamperTypeEnum>() { static OdIfc4x3_rc4::IfcDamperTypeEnum nullEnum = OdIfc4x3_rc4::kIfcDamperTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcDataOriginEnum
{
  kIfcDataOriginEnum_MEASURED,
  kIfcDataOriginEnum_PREDICTED,
  kIfcDataOriginEnum_SIMULATED,
  kIfcDataOriginEnum_USERDEFINED,
  kIfcDataOriginEnum_NOTDEFINED,
  kIfcDataOriginEnum_unset
};

class IFC4X3_RC4_EXPORT IfcDataOriginEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDataOriginEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcDataOriginEnum& getUnset<OdIfc4x3_rc4::IfcDataOriginEnum>() { static OdIfc4x3_rc4::IfcDataOriginEnum nullEnum = OdIfc4x3_rc4::kIfcDataOriginEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcDerivedUnitEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDerivedUnitEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcDerivedUnitEnum& getUnset<OdIfc4x3_rc4::IfcDerivedUnitEnum>() { static OdIfc4x3_rc4::IfcDerivedUnitEnum nullEnum = OdIfc4x3_rc4::kIfcDerivedUnitEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcDirectionSenseEnum
{
  kIfcDirectionSenseEnum_POSITIVE,
  kIfcDirectionSenseEnum_NEGATIVE,
  kIfcDirectionSenseEnum_unset
};

class IFC4X3_RC4_EXPORT IfcDirectionSenseEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDirectionSenseEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcDirectionSenseEnum& getUnset<OdIfc4x3_rc4::IfcDirectionSenseEnum>() { static OdIfc4x3_rc4::IfcDirectionSenseEnum nullEnum = OdIfc4x3_rc4::kIfcDirectionSenseEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcDiscreteAccessoryTypeEnum
{
  kIfcDiscreteAccessoryTypeEnum_ANCHORPLATE,
  kIfcDiscreteAccessoryTypeEnum_BRACKET,
  kIfcDiscreteAccessoryTypeEnum_SHOE,
  kIfcDiscreteAccessoryTypeEnum_EXPANSION_JOINT_DEVICE,
  kIfcDiscreteAccessoryTypeEnum_CABLEARRANGER,
  kIfcDiscreteAccessoryTypeEnum_INSULATOR,
  kIfcDiscreteAccessoryTypeEnum_LOCK,
  kIfcDiscreteAccessoryTypeEnum_TENSIONINGEQUIPMENT,
  kIfcDiscreteAccessoryTypeEnum_RAILPAD,
  kIfcDiscreteAccessoryTypeEnum_SLIDINGCHAIR,
  kIfcDiscreteAccessoryTypeEnum_RAIL_LUBRICATION,
  kIfcDiscreteAccessoryTypeEnum_PANEL_STRENGTHENING,
  kIfcDiscreteAccessoryTypeEnum_RAILBRACE,
  kIfcDiscreteAccessoryTypeEnum_ELASTIC_CUSHION,
  kIfcDiscreteAccessoryTypeEnum_SOUNDABSORPTION,
  kIfcDiscreteAccessoryTypeEnum_POINTMACHINEMOUNTINGDEVICE,
  kIfcDiscreteAccessoryTypeEnum_POINT_MACHINE_LOCKING_DEVICE,
  kIfcDiscreteAccessoryTypeEnum_RAIL_MECHANICAL_EQUIPMENT,
  kIfcDiscreteAccessoryTypeEnum_BIRDPROTECTION,
  kIfcDiscreteAccessoryTypeEnum_USERDEFINED,
  kIfcDiscreteAccessoryTypeEnum_NOTDEFINED,
  kIfcDiscreteAccessoryTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcDiscreteAccessoryTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDiscreteAccessoryTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcDiscreteAccessoryTypeEnum& getUnset<OdIfc4x3_rc4::IfcDiscreteAccessoryTypeEnum>() { static OdIfc4x3_rc4::IfcDiscreteAccessoryTypeEnum nullEnum = OdIfc4x3_rc4::kIfcDiscreteAccessoryTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcDistributionBoardTypeEnum
{
  kIfcDistributionBoardTypeEnum_SWITCHBOARD,
  kIfcDistributionBoardTypeEnum_CONSUMERUNIT,
  kIfcDistributionBoardTypeEnum_MOTORCONTROLCENTRE,
  kIfcDistributionBoardTypeEnum_DISTRIBUTIONFRAME,
  kIfcDistributionBoardTypeEnum_DISTRIBUTIONBOARD,
  kIfcDistributionBoardTypeEnum_DISPATCHINGBOARD,
  kIfcDistributionBoardTypeEnum_USERDEFINED,
  kIfcDistributionBoardTypeEnum_NOTDEFINED,
  kIfcDistributionBoardTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcDistributionBoardTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDistributionBoardTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcDistributionBoardTypeEnum& getUnset<OdIfc4x3_rc4::IfcDistributionBoardTypeEnum>() { static OdIfc4x3_rc4::IfcDistributionBoardTypeEnum nullEnum = OdIfc4x3_rc4::kIfcDistributionBoardTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcDistributionChamberElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDistributionChamberElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcDistributionChamberElementTypeEnum& getUnset<OdIfc4x3_rc4::IfcDistributionChamberElementTypeEnum>() { static OdIfc4x3_rc4::IfcDistributionChamberElementTypeEnum nullEnum = OdIfc4x3_rc4::kIfcDistributionChamberElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcDistributionPortTypeEnum
{
  kIfcDistributionPortTypeEnum_CABLE,
  kIfcDistributionPortTypeEnum_CABLECARRIER,
  kIfcDistributionPortTypeEnum_DUCT,
  kIfcDistributionPortTypeEnum_PIPE,
  kIfcDistributionPortTypeEnum_WIRELESS,
  kIfcDistributionPortTypeEnum_USERDEFINED,
  kIfcDistributionPortTypeEnum_NOTDEFINED,
  kIfcDistributionPortTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcDistributionPortTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDistributionPortTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcDistributionPortTypeEnum& getUnset<OdIfc4x3_rc4::IfcDistributionPortTypeEnum>() { static OdIfc4x3_rc4::IfcDistributionPortTypeEnum nullEnum = OdIfc4x3_rc4::kIfcDistributionPortTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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
  kIfcDistributionSystemEnum_CATENARY_SYSTEM,
  kIfcDistributionSystemEnum_OVERHEAD_CONTACTLINE_SYSTEM,
  kIfcDistributionSystemEnum_RETURN_CIRCUIT,
  kIfcDistributionSystemEnum_FIXEDTRANSMISSIONNETWORK,
  kIfcDistributionSystemEnum_OPERATIONALTELEPHONYSYSTEM,
  kIfcDistributionSystemEnum_MOBILENETWORK,
  kIfcDistributionSystemEnum_MONITORINGSYSTEM,
  kIfcDistributionSystemEnum_USERDEFINED,
  kIfcDistributionSystemEnum_NOTDEFINED,
  kIfcDistributionSystemEnum_unset
};

class IFC4X3_RC4_EXPORT IfcDistributionSystemEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDistributionSystemEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcDistributionSystemEnum& getUnset<OdIfc4x3_rc4::IfcDistributionSystemEnum>() { static OdIfc4x3_rc4::IfcDistributionSystemEnum nullEnum = OdIfc4x3_rc4::kIfcDistributionSystemEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcDocumentConfidentialityEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDocumentConfidentialityEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcDocumentConfidentialityEnum& getUnset<OdIfc4x3_rc4::IfcDocumentConfidentialityEnum>() { static OdIfc4x3_rc4::IfcDocumentConfidentialityEnum nullEnum = OdIfc4x3_rc4::kIfcDocumentConfidentialityEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcDocumentStatusEnum
{
  kIfcDocumentStatusEnum_DRAFT,
  kIfcDocumentStatusEnum_FINALDRAFT,
  kIfcDocumentStatusEnum_FINAL,
  kIfcDocumentStatusEnum_REVISION,
  kIfcDocumentStatusEnum_NOTDEFINED,
  kIfcDocumentStatusEnum_unset
};

class IFC4X3_RC4_EXPORT IfcDocumentStatusEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDocumentStatusEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcDocumentStatusEnum& getUnset<OdIfc4x3_rc4::IfcDocumentStatusEnum>() { static OdIfc4x3_rc4::IfcDocumentStatusEnum nullEnum = OdIfc4x3_rc4::kIfcDocumentStatusEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcDoorPanelOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorPanelOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcDoorPanelOperationEnum& getUnset<OdIfc4x3_rc4::IfcDoorPanelOperationEnum>() { static OdIfc4x3_rc4::IfcDoorPanelOperationEnum nullEnum = OdIfc4x3_rc4::kIfcDoorPanelOperationEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcDoorPanelPositionEnum
{
  kIfcDoorPanelPositionEnum_LEFT,
  kIfcDoorPanelPositionEnum_MIDDLE,
  kIfcDoorPanelPositionEnum_RIGHT,
  kIfcDoorPanelPositionEnum_NOTDEFINED,
  kIfcDoorPanelPositionEnum_unset
};

class IFC4X3_RC4_EXPORT IfcDoorPanelPositionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorPanelPositionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcDoorPanelPositionEnum& getUnset<OdIfc4x3_rc4::IfcDoorPanelPositionEnum>() { static OdIfc4x3_rc4::IfcDoorPanelPositionEnum nullEnum = OdIfc4x3_rc4::kIfcDoorPanelPositionEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcDoorStyleConstructionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorStyleConstructionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcDoorStyleConstructionEnum& getUnset<OdIfc4x3_rc4::IfcDoorStyleConstructionEnum>() { static OdIfc4x3_rc4::IfcDoorStyleConstructionEnum nullEnum = OdIfc4x3_rc4::kIfcDoorStyleConstructionEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcDoorStyleOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorStyleOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcDoorStyleOperationEnum& getUnset<OdIfc4x3_rc4::IfcDoorStyleOperationEnum>() { static OdIfc4x3_rc4::IfcDoorStyleOperationEnum nullEnum = OdIfc4x3_rc4::kIfcDoorStyleOperationEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcDoorTypeEnum
{
  kIfcDoorTypeEnum_DOOR,
  kIfcDoorTypeEnum_GATE,
  kIfcDoorTypeEnum_TRAPDOOR,
  kIfcDoorTypeEnum_BOOM_BARRIER,
  kIfcDoorTypeEnum_TURNSTILE,
  kIfcDoorTypeEnum_USERDEFINED,
  kIfcDoorTypeEnum_NOTDEFINED,
  kIfcDoorTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcDoorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcDoorTypeEnum& getUnset<OdIfc4x3_rc4::IfcDoorTypeEnum>() { static OdIfc4x3_rc4::IfcDoorTypeEnum nullEnum = OdIfc4x3_rc4::kIfcDoorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcDoorTypeOperationEnum
{
  kIfcDoorTypeOperationEnum_SINGLE_SWING_LEFT,
  kIfcDoorTypeOperationEnum_SINGLE_SWING_RIGHT,
  kIfcDoorTypeOperationEnum_DOUBLE_PANEL_SINGLE_SWING,
  kIfcDoorTypeOperationEnum_DOUBLE_PANEL_SINGLE_SWING_OPPOSITE_LEFT,
  kIfcDoorTypeOperationEnum_DOUBLE_PANEL_SINGLE_SWING_OPPOSITE_RIGHT,
  kIfcDoorTypeOperationEnum_DOUBLE_SWING_LEFT,
  kIfcDoorTypeOperationEnum_DOUBLE_SWING_RIGHT,
  kIfcDoorTypeOperationEnum_DOUBLE_PANEL_DOUBLE_SWING,
  kIfcDoorTypeOperationEnum_SLIDING_TO_LEFT,
  kIfcDoorTypeOperationEnum_SLIDING_TO_RIGHT,
  kIfcDoorTypeOperationEnum_DOUBLE_PANEL_SLIDING,
  kIfcDoorTypeOperationEnum_FOLDING_TO_LEFT,
  kIfcDoorTypeOperationEnum_FOLDING_TO_RIGHT,
  kIfcDoorTypeOperationEnum_DOUBLE_PANEL_FOLDING,
  kIfcDoorTypeOperationEnum_REVOLVING_HORIZONTAL,
  kIfcDoorTypeOperationEnum_ROLLINGUP,
  kIfcDoorTypeOperationEnum_SWING_FIXED_LEFT,
  kIfcDoorTypeOperationEnum_SWING_FIXED_RIGHT,
  kIfcDoorTypeOperationEnum_DOUBLE_PANEL_LIFTING_VERTICAL,
  kIfcDoorTypeOperationEnum_LIFTING_HORIZONTAL,
  kIfcDoorTypeOperationEnum_LIFTING_VERTICAL_LEFT,
  kIfcDoorTypeOperationEnum_LIFTING_VERTICAL_RIGHT,
  kIfcDoorTypeOperationEnum_REVOLVING_VERTICAL,
  kIfcDoorTypeOperationEnum_USERDEFINED,
  kIfcDoorTypeOperationEnum_NOTDEFINED,
  kIfcDoorTypeOperationEnum_unset
};

class IFC4X3_RC4_EXPORT IfcDoorTypeOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorTypeOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcDoorTypeOperationEnum& getUnset<OdIfc4x3_rc4::IfcDoorTypeOperationEnum>() { static OdIfc4x3_rc4::IfcDoorTypeOperationEnum nullEnum = OdIfc4x3_rc4::kIfcDoorTypeOperationEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcDuctFittingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDuctFittingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcDuctFittingTypeEnum& getUnset<OdIfc4x3_rc4::IfcDuctFittingTypeEnum>() { static OdIfc4x3_rc4::IfcDuctFittingTypeEnum nullEnum = OdIfc4x3_rc4::kIfcDuctFittingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcDuctSegmentTypeEnum
{
  kIfcDuctSegmentTypeEnum_RIGIDSEGMENT,
  kIfcDuctSegmentTypeEnum_FLEXIBLESEGMENT,
  kIfcDuctSegmentTypeEnum_USERDEFINED,
  kIfcDuctSegmentTypeEnum_NOTDEFINED,
  kIfcDuctSegmentTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcDuctSegmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDuctSegmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcDuctSegmentTypeEnum& getUnset<OdIfc4x3_rc4::IfcDuctSegmentTypeEnum>() { static OdIfc4x3_rc4::IfcDuctSegmentTypeEnum nullEnum = OdIfc4x3_rc4::kIfcDuctSegmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcDuctSilencerTypeEnum
{
  kIfcDuctSilencerTypeEnum_FLATOVAL,
  kIfcDuctSilencerTypeEnum_RECTANGULAR,
  kIfcDuctSilencerTypeEnum_ROUND,
  kIfcDuctSilencerTypeEnum_USERDEFINED,
  kIfcDuctSilencerTypeEnum_NOTDEFINED,
  kIfcDuctSilencerTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcDuctSilencerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDuctSilencerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcDuctSilencerTypeEnum& getUnset<OdIfc4x3_rc4::IfcDuctSilencerTypeEnum>() { static OdIfc4x3_rc4::IfcDuctSilencerTypeEnum nullEnum = OdIfc4x3_rc4::kIfcDuctSilencerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcEarthworksCutTypeEnum
{
  kIfcEarthworksCutTypeEnum_TRENCH,
  kIfcEarthworksCutTypeEnum_DREDGING,
  kIfcEarthworksCutTypeEnum_EXCAVATION,
  kIfcEarthworksCutTypeEnum_OVEREXCAVATION,
  kIfcEarthworksCutTypeEnum_TOPSOILREMOVAL,
  kIfcEarthworksCutTypeEnum_STEPEXCAVATION,
  kIfcEarthworksCutTypeEnum_PAVEMENTMILLING,
  kIfcEarthworksCutTypeEnum_CUT,
  kIfcEarthworksCutTypeEnum_BASE_EXCAVATION,
  kIfcEarthworksCutTypeEnum_USERDEFINED,
  kIfcEarthworksCutTypeEnum_NOTDEFINED,
  kIfcEarthworksCutTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcEarthworksCutTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcEarthworksCutTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcEarthworksCutTypeEnum& getUnset<OdIfc4x3_rc4::IfcEarthworksCutTypeEnum>() { static OdIfc4x3_rc4::IfcEarthworksCutTypeEnum nullEnum = OdIfc4x3_rc4::kIfcEarthworksCutTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcEarthworksFillTypeEnum
{
  kIfcEarthworksFillTypeEnum_BACKFILL,
  kIfcEarthworksFillTypeEnum_COUNTERWEIGHT,
  kIfcEarthworksFillTypeEnum_SUBGRADE,
  kIfcEarthworksFillTypeEnum_EMBANKMENT,
  kIfcEarthworksFillTypeEnum_TRANSITIONSECTION,
  kIfcEarthworksFillTypeEnum_SUBGRADEBED,
  kIfcEarthworksFillTypeEnum_SLOPEFILL,
  kIfcEarthworksFillTypeEnum_USERDEFINED,
  kIfcEarthworksFillTypeEnum_NOTDEFINED,
  kIfcEarthworksFillTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcEarthworksFillTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcEarthworksFillTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcEarthworksFillTypeEnum& getUnset<OdIfc4x3_rc4::IfcEarthworksFillTypeEnum>() { static OdIfc4x3_rc4::IfcEarthworksFillTypeEnum nullEnum = OdIfc4x3_rc4::kIfcEarthworksFillTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcElectricApplianceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricApplianceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcElectricApplianceTypeEnum& getUnset<OdIfc4x3_rc4::IfcElectricApplianceTypeEnum>() { static OdIfc4x3_rc4::IfcElectricApplianceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcElectricApplianceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcElectricDistributionBoardTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricDistributionBoardTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcElectricDistributionBoardTypeEnum& getUnset<OdIfc4x3_rc4::IfcElectricDistributionBoardTypeEnum>() { static OdIfc4x3_rc4::IfcElectricDistributionBoardTypeEnum nullEnum = OdIfc4x3_rc4::kIfcElectricDistributionBoardTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcElectricFlowStorageDeviceTypeEnum
{
  kIfcElectricFlowStorageDeviceTypeEnum_BATTERY,
  kIfcElectricFlowStorageDeviceTypeEnum_CAPACITORBANK,
  kIfcElectricFlowStorageDeviceTypeEnum_HARMONICFILTER,
  kIfcElectricFlowStorageDeviceTypeEnum_INDUCTORBANK,
  kIfcElectricFlowStorageDeviceTypeEnum_UPS,
  kIfcElectricFlowStorageDeviceTypeEnum_CAPACITOR,
  kIfcElectricFlowStorageDeviceTypeEnum_COMPENSATOR,
  kIfcElectricFlowStorageDeviceTypeEnum_INDUCTOR,
  kIfcElectricFlowStorageDeviceTypeEnum_RECHARGER,
  kIfcElectricFlowStorageDeviceTypeEnum_USERDEFINED,
  kIfcElectricFlowStorageDeviceTypeEnum_NOTDEFINED,
  kIfcElectricFlowStorageDeviceTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcElectricFlowStorageDeviceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricFlowStorageDeviceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcElectricFlowStorageDeviceTypeEnum& getUnset<OdIfc4x3_rc4::IfcElectricFlowStorageDeviceTypeEnum>() { static OdIfc4x3_rc4::IfcElectricFlowStorageDeviceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcElectricFlowStorageDeviceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcElectricFlowTreatmentDeviceTypeEnum
{
  kIfcElectricFlowTreatmentDeviceTypeEnum_ELECTRONICFILTER,
  kIfcElectricFlowTreatmentDeviceTypeEnum_USERDEFINED,
  kIfcElectricFlowTreatmentDeviceTypeEnum_NOTDEFINED,
  kIfcElectricFlowTreatmentDeviceTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcElectricFlowTreatmentDeviceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricFlowTreatmentDeviceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcElectricFlowTreatmentDeviceTypeEnum& getUnset<OdIfc4x3_rc4::IfcElectricFlowTreatmentDeviceTypeEnum>() { static OdIfc4x3_rc4::IfcElectricFlowTreatmentDeviceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcElectricFlowTreatmentDeviceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcElectricGeneratorTypeEnum
{
  kIfcElectricGeneratorTypeEnum_CHP,
  kIfcElectricGeneratorTypeEnum_ENGINEGENERATOR,
  kIfcElectricGeneratorTypeEnum_STANDALONE,
  kIfcElectricGeneratorTypeEnum_USERDEFINED,
  kIfcElectricGeneratorTypeEnum_NOTDEFINED,
  kIfcElectricGeneratorTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcElectricGeneratorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricGeneratorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcElectricGeneratorTypeEnum& getUnset<OdIfc4x3_rc4::IfcElectricGeneratorTypeEnum>() { static OdIfc4x3_rc4::IfcElectricGeneratorTypeEnum nullEnum = OdIfc4x3_rc4::kIfcElectricGeneratorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcElectricMotorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricMotorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcElectricMotorTypeEnum& getUnset<OdIfc4x3_rc4::IfcElectricMotorTypeEnum>() { static OdIfc4x3_rc4::IfcElectricMotorTypeEnum nullEnum = OdIfc4x3_rc4::kIfcElectricMotorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcElectricTimeControlTypeEnum
{
  kIfcElectricTimeControlTypeEnum_TIMECLOCK,
  kIfcElectricTimeControlTypeEnum_TIMEDELAY,
  kIfcElectricTimeControlTypeEnum_RELAY,
  kIfcElectricTimeControlTypeEnum_USERDEFINED,
  kIfcElectricTimeControlTypeEnum_NOTDEFINED,
  kIfcElectricTimeControlTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcElectricTimeControlTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricTimeControlTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcElectricTimeControlTypeEnum& getUnset<OdIfc4x3_rc4::IfcElectricTimeControlTypeEnum>() { static OdIfc4x3_rc4::IfcElectricTimeControlTypeEnum nullEnum = OdIfc4x3_rc4::kIfcElectricTimeControlTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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
  kIfcElementAssemblyTypeEnum_ABUTMENT,
  kIfcElementAssemblyTypeEnum_PIER,
  kIfcElementAssemblyTypeEnum_PYLON,
  kIfcElementAssemblyTypeEnum_CROSS_BRACING,
  kIfcElementAssemblyTypeEnum_DECK,
  kIfcElementAssemblyTypeEnum_MAST,
  kIfcElementAssemblyTypeEnum_SIGNALASSEMBLY,
  kIfcElementAssemblyTypeEnum_GRID,
  kIfcElementAssemblyTypeEnum_SHELTER,
  kIfcElementAssemblyTypeEnum_SUPPORTINGASSEMBLY,
  kIfcElementAssemblyTypeEnum_SUSPENSIONASSEMBLY,
  kIfcElementAssemblyTypeEnum_TRACTION_SWITCHING_ASSEMBLY,
  kIfcElementAssemblyTypeEnum_TRACKPANEL,
  kIfcElementAssemblyTypeEnum_TURNOUTPANEL,
  kIfcElementAssemblyTypeEnum_DILATATIONPANEL,
  kIfcElementAssemblyTypeEnum_RAIL_MECHANICAL_EQUIPMENT_ASSEMBLY,
  kIfcElementAssemblyTypeEnum_ENTRANCEWORKS,
  kIfcElementAssemblyTypeEnum_SUMPBUSTER,
  kIfcElementAssemblyTypeEnum_TRAFFIC_CALMING_DEVICE,
  kIfcElementAssemblyTypeEnum_USERDEFINED,
  kIfcElementAssemblyTypeEnum_NOTDEFINED,
  kIfcElementAssemblyTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcElementAssemblyTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElementAssemblyTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcElementAssemblyTypeEnum& getUnset<OdIfc4x3_rc4::IfcElementAssemblyTypeEnum>() { static OdIfc4x3_rc4::IfcElementAssemblyTypeEnum nullEnum = OdIfc4x3_rc4::kIfcElementAssemblyTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcElementCompositionEnum
{
  kIfcElementCompositionEnum_COMPLEX,
  kIfcElementCompositionEnum_ELEMENT,
  kIfcElementCompositionEnum_PARTIAL,
  kIfcElementCompositionEnum_unset
};

class IFC4X3_RC4_EXPORT IfcElementCompositionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElementCompositionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcElementCompositionEnum& getUnset<OdIfc4x3_rc4::IfcElementCompositionEnum>() { static OdIfc4x3_rc4::IfcElementCompositionEnum nullEnum = OdIfc4x3_rc4::kIfcElementCompositionEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcEngineTypeEnum
{
  kIfcEngineTypeEnum_EXTERNALCOMBUSTION,
  kIfcEngineTypeEnum_INTERNALCOMBUSTION,
  kIfcEngineTypeEnum_USERDEFINED,
  kIfcEngineTypeEnum_NOTDEFINED,
  kIfcEngineTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcEngineTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcEngineTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcEngineTypeEnum& getUnset<OdIfc4x3_rc4::IfcEngineTypeEnum>() { static OdIfc4x3_rc4::IfcEngineTypeEnum nullEnum = OdIfc4x3_rc4::kIfcEngineTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcEvaporativeCoolerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcEvaporativeCoolerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcEvaporativeCoolerTypeEnum& getUnset<OdIfc4x3_rc4::IfcEvaporativeCoolerTypeEnum>() { static OdIfc4x3_rc4::IfcEvaporativeCoolerTypeEnum nullEnum = OdIfc4x3_rc4::kIfcEvaporativeCoolerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcEvaporatorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcEvaporatorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcEvaporatorTypeEnum& getUnset<OdIfc4x3_rc4::IfcEvaporatorTypeEnum>() { static OdIfc4x3_rc4::IfcEvaporatorTypeEnum nullEnum = OdIfc4x3_rc4::kIfcEvaporatorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcEventTriggerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcEventTriggerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcEventTriggerTypeEnum& getUnset<OdIfc4x3_rc4::IfcEventTriggerTypeEnum>() { static OdIfc4x3_rc4::IfcEventTriggerTypeEnum nullEnum = OdIfc4x3_rc4::kIfcEventTriggerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcEventTypeEnum
{
  kIfcEventTypeEnum_STARTEVENT,
  kIfcEventTypeEnum_ENDEVENT,
  kIfcEventTypeEnum_INTERMEDIATEEVENT,
  kIfcEventTypeEnum_USERDEFINED,
  kIfcEventTypeEnum_NOTDEFINED,
  kIfcEventTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcEventTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcEventTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcEventTypeEnum& getUnset<OdIfc4x3_rc4::IfcEventTypeEnum>() { static OdIfc4x3_rc4::IfcEventTypeEnum nullEnum = OdIfc4x3_rc4::kIfcEventTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcExternalSpatialElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcExternalSpatialElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcExternalSpatialElementTypeEnum& getUnset<OdIfc4x3_rc4::IfcExternalSpatialElementTypeEnum>() { static OdIfc4x3_rc4::IfcExternalSpatialElementTypeEnum nullEnum = OdIfc4x3_rc4::kIfcExternalSpatialElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcFacilityPartCommonTypeEnum
{
  kIfcFacilityPartCommonTypeEnum_SEGMENT,
  kIfcFacilityPartCommonTypeEnum_ABOVEGROUND,
  kIfcFacilityPartCommonTypeEnum_JUNCTION,
  kIfcFacilityPartCommonTypeEnum_LEVELCROSSING,
  kIfcFacilityPartCommonTypeEnum_BELOWGROUND,
  kIfcFacilityPartCommonTypeEnum_SUBSTRUCTURE,
  kIfcFacilityPartCommonTypeEnum_TERMINAL,
  kIfcFacilityPartCommonTypeEnum_SUPERSTRUCTURE,
  kIfcFacilityPartCommonTypeEnum_USERDEFINED,
  kIfcFacilityPartCommonTypeEnum_NOTDEFINED,
  kIfcFacilityPartCommonTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcFacilityPartCommonTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFacilityPartCommonTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcFacilityPartCommonTypeEnum& getUnset<OdIfc4x3_rc4::IfcFacilityPartCommonTypeEnum>() { static OdIfc4x3_rc4::IfcFacilityPartCommonTypeEnum nullEnum = OdIfc4x3_rc4::kIfcFacilityPartCommonTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcFacilityUsageEnum
{
  kIfcFacilityUsageEnum_LATERAL,
  kIfcFacilityUsageEnum_REGION,
  kIfcFacilityUsageEnum_VERTICAL,
  kIfcFacilityUsageEnum_LONGITUDINAL,
  kIfcFacilityUsageEnum_USERDEFINED,
  kIfcFacilityUsageEnum_NOTDEFINED,
  kIfcFacilityUsageEnum_unset
};

class IFC4X3_RC4_EXPORT IfcFacilityUsageEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFacilityUsageEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcFacilityUsageEnum& getUnset<OdIfc4x3_rc4::IfcFacilityUsageEnum>() { static OdIfc4x3_rc4::IfcFacilityUsageEnum nullEnum = OdIfc4x3_rc4::kIfcFacilityUsageEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcFanTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFanTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcFanTypeEnum& getUnset<OdIfc4x3_rc4::IfcFanTypeEnum>() { static OdIfc4x3_rc4::IfcFanTypeEnum nullEnum = OdIfc4x3_rc4::kIfcFanTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcFastenerTypeEnum
{
  kIfcFastenerTypeEnum_GLUE,
  kIfcFastenerTypeEnum_MORTAR,
  kIfcFastenerTypeEnum_WELD,
  kIfcFastenerTypeEnum_USERDEFINED,
  kIfcFastenerTypeEnum_NOTDEFINED,
  kIfcFastenerTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcFastenerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFastenerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcFastenerTypeEnum& getUnset<OdIfc4x3_rc4::IfcFastenerTypeEnum>() { static OdIfc4x3_rc4::IfcFastenerTypeEnum nullEnum = OdIfc4x3_rc4::kIfcFastenerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcFilterTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFilterTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcFilterTypeEnum& getUnset<OdIfc4x3_rc4::IfcFilterTypeEnum>() { static OdIfc4x3_rc4::IfcFilterTypeEnum nullEnum = OdIfc4x3_rc4::kIfcFilterTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcFireSuppressionTerminalTypeEnum
{
  kIfcFireSuppressionTerminalTypeEnum_BREECHINGINLET,
  kIfcFireSuppressionTerminalTypeEnum_FIREHYDRANT,
  kIfcFireSuppressionTerminalTypeEnum_HOSEREEL,
  kIfcFireSuppressionTerminalTypeEnum_SPRINKLER,
  kIfcFireSuppressionTerminalTypeEnum_SPRINKLERDEFLECTOR,
  kIfcFireSuppressionTerminalTypeEnum_FIREMONITOR,
  kIfcFireSuppressionTerminalTypeEnum_USERDEFINED,
  kIfcFireSuppressionTerminalTypeEnum_NOTDEFINED,
  kIfcFireSuppressionTerminalTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcFireSuppressionTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFireSuppressionTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcFireSuppressionTerminalTypeEnum& getUnset<OdIfc4x3_rc4::IfcFireSuppressionTerminalTypeEnum>() { static OdIfc4x3_rc4::IfcFireSuppressionTerminalTypeEnum nullEnum = OdIfc4x3_rc4::kIfcFireSuppressionTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcFlowDirectionEnum
{
  kIfcFlowDirectionEnum_SOURCE,
  kIfcFlowDirectionEnum_SINK,
  kIfcFlowDirectionEnum_SOURCEANDSINK,
  kIfcFlowDirectionEnum_NOTDEFINED,
  kIfcFlowDirectionEnum_unset
};

class IFC4X3_RC4_EXPORT IfcFlowDirectionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFlowDirectionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcFlowDirectionEnum& getUnset<OdIfc4x3_rc4::IfcFlowDirectionEnum>() { static OdIfc4x3_rc4::IfcFlowDirectionEnum nullEnum = OdIfc4x3_rc4::kIfcFlowDirectionEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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
  kIfcFlowInstrumentTypeEnum_COMBINED,
  kIfcFlowInstrumentTypeEnum_VOLTMETER,
  kIfcFlowInstrumentTypeEnum_USERDEFINED,
  kIfcFlowInstrumentTypeEnum_NOTDEFINED,
  kIfcFlowInstrumentTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcFlowInstrumentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFlowInstrumentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcFlowInstrumentTypeEnum& getUnset<OdIfc4x3_rc4::IfcFlowInstrumentTypeEnum>() { static OdIfc4x3_rc4::IfcFlowInstrumentTypeEnum nullEnum = OdIfc4x3_rc4::kIfcFlowInstrumentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcFlowMeterTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFlowMeterTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcFlowMeterTypeEnum& getUnset<OdIfc4x3_rc4::IfcFlowMeterTypeEnum>() { static OdIfc4x3_rc4::IfcFlowMeterTypeEnum nullEnum = OdIfc4x3_rc4::kIfcFlowMeterTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcFootingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFootingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcFootingTypeEnum& getUnset<OdIfc4x3_rc4::IfcFootingTypeEnum>() { static OdIfc4x3_rc4::IfcFootingTypeEnum nullEnum = OdIfc4x3_rc4::kIfcFootingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcFurnitureTypeEnum
{
  kIfcFurnitureTypeEnum_CHAIR,
  kIfcFurnitureTypeEnum_TABLE,
  kIfcFurnitureTypeEnum_DESK,
  kIfcFurnitureTypeEnum_BED,
  kIfcFurnitureTypeEnum_FILECABINET,
  kIfcFurnitureTypeEnum_SHELF,
  kIfcFurnitureTypeEnum_SOFA,
  kIfcFurnitureTypeEnum_TECHNICALCABINET,
  kIfcFurnitureTypeEnum_USERDEFINED,
  kIfcFurnitureTypeEnum_NOTDEFINED,
  kIfcFurnitureTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcFurnitureTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFurnitureTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcFurnitureTypeEnum& getUnset<OdIfc4x3_rc4::IfcFurnitureTypeEnum>() { static OdIfc4x3_rc4::IfcFurnitureTypeEnum nullEnum = OdIfc4x3_rc4::kIfcFurnitureTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcGeographicElementTypeEnum
{
  kIfcGeographicElementTypeEnum_TERRAIN,
  kIfcGeographicElementTypeEnum_SOIL_BORING_POINT,
  kIfcGeographicElementTypeEnum_USERDEFINED,
  kIfcGeographicElementTypeEnum_NOTDEFINED,
  kIfcGeographicElementTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcGeographicElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcGeographicElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcGeographicElementTypeEnum& getUnset<OdIfc4x3_rc4::IfcGeographicElementTypeEnum>() { static OdIfc4x3_rc4::IfcGeographicElementTypeEnum nullEnum = OdIfc4x3_rc4::kIfcGeographicElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcGeometricProjectionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcGeometricProjectionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcGeometricProjectionEnum& getUnset<OdIfc4x3_rc4::IfcGeometricProjectionEnum>() { static OdIfc4x3_rc4::IfcGeometricProjectionEnum nullEnum = OdIfc4x3_rc4::kIfcGeometricProjectionEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcGlobalOrLocalEnum
{
  kIfcGlobalOrLocalEnum_GLOBAL_COORDS,
  kIfcGlobalOrLocalEnum_LOCAL_COORDS,
  kIfcGlobalOrLocalEnum_unset
};

class IFC4X3_RC4_EXPORT IfcGlobalOrLocalEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcGlobalOrLocalEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcGlobalOrLocalEnum& getUnset<OdIfc4x3_rc4::IfcGlobalOrLocalEnum>() { static OdIfc4x3_rc4::IfcGlobalOrLocalEnum nullEnum = OdIfc4x3_rc4::kIfcGlobalOrLocalEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcGridTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcGridTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcGridTypeEnum& getUnset<OdIfc4x3_rc4::IfcGridTypeEnum>() { static OdIfc4x3_rc4::IfcGridTypeEnum nullEnum = OdIfc4x3_rc4::kIfcGridTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcHeatExchangerTypeEnum
{
  kIfcHeatExchangerTypeEnum_PLATE,
  kIfcHeatExchangerTypeEnum_SHELLANDTUBE,
  kIfcHeatExchangerTypeEnum_TURNOUTHEATING,
  kIfcHeatExchangerTypeEnum_USERDEFINED,
  kIfcHeatExchangerTypeEnum_NOTDEFINED,
  kIfcHeatExchangerTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcHeatExchangerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcHeatExchangerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcHeatExchangerTypeEnum& getUnset<OdIfc4x3_rc4::IfcHeatExchangerTypeEnum>() { static OdIfc4x3_rc4::IfcHeatExchangerTypeEnum nullEnum = OdIfc4x3_rc4::kIfcHeatExchangerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcHumidifierTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcHumidifierTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcHumidifierTypeEnum& getUnset<OdIfc4x3_rc4::IfcHumidifierTypeEnum>() { static OdIfc4x3_rc4::IfcHumidifierTypeEnum nullEnum = OdIfc4x3_rc4::kIfcHumidifierTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcImpactProtectionDeviceTypeEnum
{
  kIfcImpactProtectionDeviceTypeEnum_CRASHCUSHION,
  kIfcImpactProtectionDeviceTypeEnum_DAMPINGSYSTEM,
  kIfcImpactProtectionDeviceTypeEnum_FENDER,
  kIfcImpactProtectionDeviceTypeEnum_BUMPER,
  kIfcImpactProtectionDeviceTypeEnum_USERDEFINED,
  kIfcImpactProtectionDeviceTypeEnum_NOTDEFINED,
  kIfcImpactProtectionDeviceTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcImpactProtectionDeviceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcImpactProtectionDeviceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcImpactProtectionDeviceTypeEnum& getUnset<OdIfc4x3_rc4::IfcImpactProtectionDeviceTypeEnum>() { static OdIfc4x3_rc4::IfcImpactProtectionDeviceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcImpactProtectionDeviceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcInterceptorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcInterceptorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcInterceptorTypeEnum& getUnset<OdIfc4x3_rc4::IfcInterceptorTypeEnum>() { static OdIfc4x3_rc4::IfcInterceptorTypeEnum nullEnum = OdIfc4x3_rc4::kIfcInterceptorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcInternalOrExternalEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcInternalOrExternalEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcInternalOrExternalEnum& getUnset<OdIfc4x3_rc4::IfcInternalOrExternalEnum>() { static OdIfc4x3_rc4::IfcInternalOrExternalEnum nullEnum = OdIfc4x3_rc4::kIfcInternalOrExternalEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcInventoryTypeEnum
{
  kIfcInventoryTypeEnum_ASSETINVENTORY,
  kIfcInventoryTypeEnum_SPACEINVENTORY,
  kIfcInventoryTypeEnum_FURNITUREINVENTORY,
  kIfcInventoryTypeEnum_USERDEFINED,
  kIfcInventoryTypeEnum_NOTDEFINED,
  kIfcInventoryTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcInventoryTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcInventoryTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcInventoryTypeEnum& getUnset<OdIfc4x3_rc4::IfcInventoryTypeEnum>() { static OdIfc4x3_rc4::IfcInventoryTypeEnum nullEnum = OdIfc4x3_rc4::kIfcInventoryTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcJunctionBoxTypeEnum
{
  kIfcJunctionBoxTypeEnum_DATA,
  kIfcJunctionBoxTypeEnum_POWER,
  kIfcJunctionBoxTypeEnum_USERDEFINED,
  kIfcJunctionBoxTypeEnum_NOTDEFINED,
  kIfcJunctionBoxTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcJunctionBoxTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcJunctionBoxTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcJunctionBoxTypeEnum& getUnset<OdIfc4x3_rc4::IfcJunctionBoxTypeEnum>() { static OdIfc4x3_rc4::IfcJunctionBoxTypeEnum nullEnum = OdIfc4x3_rc4::kIfcJunctionBoxTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcKnotType
{
  kIfcKnotType_UNIFORM_KNOTS,
  kIfcKnotType_QUASI_UNIFORM_KNOTS,
  kIfcKnotType_PIECEWISE_BEZIER_KNOTS,
  kIfcKnotType_UNSPECIFIED,
  kIfcKnotType_unset
};

class IFC4X3_RC4_EXPORT IfcKnotTypeTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcKnotTypeTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcKnotType& getUnset<OdIfc4x3_rc4::IfcKnotType>() { static OdIfc4x3_rc4::IfcKnotType nullEnum = OdIfc4x3_rc4::kIfcKnotType_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcLaborResourceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLaborResourceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcLaborResourceTypeEnum& getUnset<OdIfc4x3_rc4::IfcLaborResourceTypeEnum>() { static OdIfc4x3_rc4::IfcLaborResourceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcLaborResourceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcLampTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLampTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcLampTypeEnum& getUnset<OdIfc4x3_rc4::IfcLampTypeEnum>() { static OdIfc4x3_rc4::IfcLampTypeEnum nullEnum = OdIfc4x3_rc4::kIfcLampTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcLayerSetDirectionEnum
{
  kIfcLayerSetDirectionEnum_AXIS1,
  kIfcLayerSetDirectionEnum_AXIS2,
  kIfcLayerSetDirectionEnum_AXIS3,
  kIfcLayerSetDirectionEnum_unset
};

class IFC4X3_RC4_EXPORT IfcLayerSetDirectionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLayerSetDirectionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcLayerSetDirectionEnum& getUnset<OdIfc4x3_rc4::IfcLayerSetDirectionEnum>() { static OdIfc4x3_rc4::IfcLayerSetDirectionEnum nullEnum = OdIfc4x3_rc4::kIfcLayerSetDirectionEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcLightDistributionCurveEnum
{
  kIfcLightDistributionCurveEnum_TYPE_A,
  kIfcLightDistributionCurveEnum_TYPE_B,
  kIfcLightDistributionCurveEnum_TYPE_C,
  kIfcLightDistributionCurveEnum_NOTDEFINED,
  kIfcLightDistributionCurveEnum_unset
};

class IFC4X3_RC4_EXPORT IfcLightDistributionCurveEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLightDistributionCurveEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcLightDistributionCurveEnum& getUnset<OdIfc4x3_rc4::IfcLightDistributionCurveEnum>() { static OdIfc4x3_rc4::IfcLightDistributionCurveEnum nullEnum = OdIfc4x3_rc4::kIfcLightDistributionCurveEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcLightEmissionSourceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLightEmissionSourceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcLightEmissionSourceEnum& getUnset<OdIfc4x3_rc4::IfcLightEmissionSourceEnum>() { static OdIfc4x3_rc4::IfcLightEmissionSourceEnum nullEnum = OdIfc4x3_rc4::kIfcLightEmissionSourceEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcLightFixtureTypeEnum
{
  kIfcLightFixtureTypeEnum_POINTSOURCE,
  kIfcLightFixtureTypeEnum_DIRECTIONSOURCE,
  kIfcLightFixtureTypeEnum_SECURITYLIGHTING,
  kIfcLightFixtureTypeEnum_USERDEFINED,
  kIfcLightFixtureTypeEnum_NOTDEFINED,
  kIfcLightFixtureTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcLightFixtureTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLightFixtureTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcLightFixtureTypeEnum& getUnset<OdIfc4x3_rc4::IfcLightFixtureTypeEnum>() { static OdIfc4x3_rc4::IfcLightFixtureTypeEnum nullEnum = OdIfc4x3_rc4::kIfcLightFixtureTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcLiquidTerminalTypeEnum
{
  kIfcLiquidTerminalTypeEnum_LOADINGARM,
  kIfcLiquidTerminalTypeEnum_HOSEREEL,
  kIfcLiquidTerminalTypeEnum_USERDEFINED,
  kIfcLiquidTerminalTypeEnum_NOTDEFINED,
  kIfcLiquidTerminalTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcLiquidTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLiquidTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcLiquidTerminalTypeEnum& getUnset<OdIfc4x3_rc4::IfcLiquidTerminalTypeEnum>() { static OdIfc4x3_rc4::IfcLiquidTerminalTypeEnum nullEnum = OdIfc4x3_rc4::kIfcLiquidTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcLoadGroupTypeEnum
{
  kIfcLoadGroupTypeEnum_LOAD_GROUP,
  kIfcLoadGroupTypeEnum_LOAD_CASE,
  kIfcLoadGroupTypeEnum_LOAD_COMBINATION,
  kIfcLoadGroupTypeEnum_USERDEFINED,
  kIfcLoadGroupTypeEnum_NOTDEFINED,
  kIfcLoadGroupTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcLoadGroupTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLoadGroupTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcLoadGroupTypeEnum& getUnset<OdIfc4x3_rc4::IfcLoadGroupTypeEnum>() { static OdIfc4x3_rc4::IfcLoadGroupTypeEnum nullEnum = OdIfc4x3_rc4::kIfcLoadGroupTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcLogicalOperatorEnum
{
  kIfcLogicalOperatorEnum_LOGICALAND,
  kIfcLogicalOperatorEnum_LOGICALOR,
  kIfcLogicalOperatorEnum_LOGICALXOR,
  kIfcLogicalOperatorEnum_LOGICALNOTAND,
  kIfcLogicalOperatorEnum_LOGICALNOTOR,
  kIfcLogicalOperatorEnum_unset
};

class IFC4X3_RC4_EXPORT IfcLogicalOperatorEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLogicalOperatorEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcLogicalOperatorEnum& getUnset<OdIfc4x3_rc4::IfcLogicalOperatorEnum>() { static OdIfc4x3_rc4::IfcLogicalOperatorEnum nullEnum = OdIfc4x3_rc4::kIfcLogicalOperatorEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcMarineFacilityTypeEnum
{
  kIfcMarineFacilityTypeEnum_CANAL,
  kIfcMarineFacilityTypeEnum_WATERWAYSHIPLIFT,
  kIfcMarineFacilityTypeEnum_REVETMENT,
  kIfcMarineFacilityTypeEnum_LAUNCHRECOVERY,
  kIfcMarineFacilityTypeEnum_MARINEDEFENCE,
  kIfcMarineFacilityTypeEnum_HYDROLIFT,
  kIfcMarineFacilityTypeEnum_SHIPYARD,
  kIfcMarineFacilityTypeEnum_SHIPLIFT,
  kIfcMarineFacilityTypeEnum_PORT,
  kIfcMarineFacilityTypeEnum_QUAY,
  kIfcMarineFacilityTypeEnum_FLOATINGDOCK,
  kIfcMarineFacilityTypeEnum_NAVIGATIONALCHANNEL,
  kIfcMarineFacilityTypeEnum_BREAKWATER,
  kIfcMarineFacilityTypeEnum_DRYDOCK,
  kIfcMarineFacilityTypeEnum_JETTY,
  kIfcMarineFacilityTypeEnum_SHIPLOCK,
  kIfcMarineFacilityTypeEnum_BARRIERBEACH,
  kIfcMarineFacilityTypeEnum_SLIPWAY,
  kIfcMarineFacilityTypeEnum_WATERWAY,
  kIfcMarineFacilityTypeEnum_USERDEFINED,
  kIfcMarineFacilityTypeEnum_NOTDEFINED,
  kIfcMarineFacilityTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcMarineFacilityTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMarineFacilityTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcMarineFacilityTypeEnum& getUnset<OdIfc4x3_rc4::IfcMarineFacilityTypeEnum>() { static OdIfc4x3_rc4::IfcMarineFacilityTypeEnum nullEnum = OdIfc4x3_rc4::kIfcMarineFacilityTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcMarinePartTypeEnum
{
  kIfcMarinePartTypeEnum_CREST,
  kIfcMarinePartTypeEnum_MANUFACTURING,
  kIfcMarinePartTypeEnum_LOWWATERLINE,
  kIfcMarinePartTypeEnum_CORE,
  kIfcMarinePartTypeEnum_WATERFIELD,
  kIfcMarinePartTypeEnum_CILL_LEVEL,
  kIfcMarinePartTypeEnum_BERTHINGSTRUCTURE,
  kIfcMarinePartTypeEnum_COPELEVEL,
  kIfcMarinePartTypeEnum_CHAMBER,
  kIfcMarinePartTypeEnum_STORAGEAREA,
  kIfcMarinePartTypeEnum_APPROACHCHANNEL,
  kIfcMarinePartTypeEnum_VEHICLESERVICING,
  kIfcMarinePartTypeEnum_SHIPTRANSFER,
  kIfcMarinePartTypeEnum_GATEHEAD,
  kIfcMarinePartTypeEnum_GUDINGSTRUCTURE,
  kIfcMarinePartTypeEnum_BELOWWATERLINE,
  kIfcMarinePartTypeEnum_WEATHERSIDE,
  kIfcMarinePartTypeEnum_LANDFIELD,
  kIfcMarinePartTypeEnum_PROTECTION,
  kIfcMarinePartTypeEnum_LEEWARDSIDE,
  kIfcMarinePartTypeEnum_ABOVEWATERLINE,
  kIfcMarinePartTypeEnum_ANCHORAGE,
  kIfcMarinePartTypeEnum_NAVIGATIONALAREA,
  kIfcMarinePartTypeEnum_HIGHWATERLINE,
  kIfcMarinePartTypeEnum_USERDEFINED,
  kIfcMarinePartTypeEnum_NOTDEFINED,
  kIfcMarinePartTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcMarinePartTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMarinePartTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcMarinePartTypeEnum& getUnset<OdIfc4x3_rc4::IfcMarinePartTypeEnum>() { static OdIfc4x3_rc4::IfcMarinePartTypeEnum nullEnum = OdIfc4x3_rc4::kIfcMarinePartTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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
  kIfcMechanicalFastenerTypeEnum_COUPLER,
  kIfcMechanicalFastenerTypeEnum_RAILJOINT,
  kIfcMechanicalFastenerTypeEnum_RAILFASTENING,
  kIfcMechanicalFastenerTypeEnum_CHAIN,
  kIfcMechanicalFastenerTypeEnum_ROPE,
  kIfcMechanicalFastenerTypeEnum_USERDEFINED,
  kIfcMechanicalFastenerTypeEnum_NOTDEFINED,
  kIfcMechanicalFastenerTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcMechanicalFastenerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMechanicalFastenerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcMechanicalFastenerTypeEnum& getUnset<OdIfc4x3_rc4::IfcMechanicalFastenerTypeEnum>() { static OdIfc4x3_rc4::IfcMechanicalFastenerTypeEnum nullEnum = OdIfc4x3_rc4::kIfcMechanicalFastenerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcMedicalDeviceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMedicalDeviceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcMedicalDeviceTypeEnum& getUnset<OdIfc4x3_rc4::IfcMedicalDeviceTypeEnum>() { static OdIfc4x3_rc4::IfcMedicalDeviceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcMedicalDeviceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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
  kIfcMemberTypeEnum_STIFFENING_RIB,
  kIfcMemberTypeEnum_ARCH_SEGMENT,
  kIfcMemberTypeEnum_SUSPENSION_CABLE,
  kIfcMemberTypeEnum_SUSPENDER,
  kIfcMemberTypeEnum_STAY_CABLE,
  kIfcMemberTypeEnum_STRUCTURALCABLE,
  kIfcMemberTypeEnum_TIEBAR,
  kIfcMemberTypeEnum_USERDEFINED,
  kIfcMemberTypeEnum_NOTDEFINED,
  kIfcMemberTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcMemberTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMemberTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcMemberTypeEnum& getUnset<OdIfc4x3_rc4::IfcMemberTypeEnum>() { static OdIfc4x3_rc4::IfcMemberTypeEnum nullEnum = OdIfc4x3_rc4::kIfcMemberTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcMobileTelecommunicationsApplianceTypeEnum
{
  kIfcMobileTelecommunicationsApplianceTypeEnum_E_UTRAN_NODE_B,
  kIfcMobileTelecommunicationsApplianceTypeEnum_REMOTERADIOUNIT,
  kIfcMobileTelecommunicationsApplianceTypeEnum_ACCESSPOINT,
  kIfcMobileTelecommunicationsApplianceTypeEnum_BASETRANSCEIVERSTATION,
  kIfcMobileTelecommunicationsApplianceTypeEnum_REMOTEUNIT,
  kIfcMobileTelecommunicationsApplianceTypeEnum_BASEBANDUNIT,
  kIfcMobileTelecommunicationsApplianceTypeEnum_MASTERUNIT,
  kIfcMobileTelecommunicationsApplianceTypeEnum_GATEWAY_GPRS_SUPPORT_NODE,
  kIfcMobileTelecommunicationsApplianceTypeEnum_SUBSCRIBERSERVER,
  kIfcMobileTelecommunicationsApplianceTypeEnum_MOBILESWITCHINGCENTER,
  kIfcMobileTelecommunicationsApplianceTypeEnum_MSCSERVER,
  kIfcMobileTelecommunicationsApplianceTypeEnum_PACKETCONTROLUNIT,
  kIfcMobileTelecommunicationsApplianceTypeEnum_SERVICE_GPRS_SUPPORT_NODE,
  kIfcMobileTelecommunicationsApplianceTypeEnum_USERDEFINED,
  kIfcMobileTelecommunicationsApplianceTypeEnum_NOTDEFINED,
  kIfcMobileTelecommunicationsApplianceTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcMobileTelecommunicationsApplianceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMobileTelecommunicationsApplianceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcMobileTelecommunicationsApplianceTypeEnum& getUnset<OdIfc4x3_rc4::IfcMobileTelecommunicationsApplianceTypeEnum>() { static OdIfc4x3_rc4::IfcMobileTelecommunicationsApplianceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcMobileTelecommunicationsApplianceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcMooringDeviceTypeEnum
{
  kIfcMooringDeviceTypeEnum_LINETENSIONER,
  kIfcMooringDeviceTypeEnum_MAGNETICDEVICE,
  kIfcMooringDeviceTypeEnum_MOORINGHOOKS,
  kIfcMooringDeviceTypeEnum_VACUUMDEVICE,
  kIfcMooringDeviceTypeEnum_BOLLARD,
  kIfcMooringDeviceTypeEnum_USERDEFINED,
  kIfcMooringDeviceTypeEnum_NOTDEFINED,
  kIfcMooringDeviceTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcMooringDeviceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMooringDeviceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcMooringDeviceTypeEnum& getUnset<OdIfc4x3_rc4::IfcMooringDeviceTypeEnum>() { static OdIfc4x3_rc4::IfcMooringDeviceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcMooringDeviceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcMotorConnectionTypeEnum
{
  kIfcMotorConnectionTypeEnum_BELTDRIVE,
  kIfcMotorConnectionTypeEnum_COUPLING,
  kIfcMotorConnectionTypeEnum_DIRECTDRIVE,
  kIfcMotorConnectionTypeEnum_USERDEFINED,
  kIfcMotorConnectionTypeEnum_NOTDEFINED,
  kIfcMotorConnectionTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcMotorConnectionTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMotorConnectionTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcMotorConnectionTypeEnum& getUnset<OdIfc4x3_rc4::IfcMotorConnectionTypeEnum>() { static OdIfc4x3_rc4::IfcMotorConnectionTypeEnum nullEnum = OdIfc4x3_rc4::kIfcMotorConnectionTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcNavigationElementTypeEnum
{
  kIfcNavigationElementTypeEnum_BEACON,
  kIfcNavigationElementTypeEnum_BUOY,
  kIfcNavigationElementTypeEnum_USERDEFINED,
  kIfcNavigationElementTypeEnum_NOTDEFINED,
  kIfcNavigationElementTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcNavigationElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcNavigationElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcNavigationElementTypeEnum& getUnset<OdIfc4x3_rc4::IfcNavigationElementTypeEnum>() { static OdIfc4x3_rc4::IfcNavigationElementTypeEnum nullEnum = OdIfc4x3_rc4::kIfcNavigationElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcObjectTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcObjectTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcObjectTypeEnum& getUnset<OdIfc4x3_rc4::IfcObjectTypeEnum>() { static OdIfc4x3_rc4::IfcObjectTypeEnum nullEnum = OdIfc4x3_rc4::kIfcObjectTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcObjectiveEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcObjectiveEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcObjectiveEnum& getUnset<OdIfc4x3_rc4::IfcObjectiveEnum>() { static OdIfc4x3_rc4::IfcObjectiveEnum nullEnum = OdIfc4x3_rc4::kIfcObjectiveEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcOccupantTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcOccupantTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcOccupantTypeEnum& getUnset<OdIfc4x3_rc4::IfcOccupantTypeEnum>() { static OdIfc4x3_rc4::IfcOccupantTypeEnum nullEnum = OdIfc4x3_rc4::kIfcOccupantTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcOpeningElementTypeEnum
{
  kIfcOpeningElementTypeEnum_OPENING,
  kIfcOpeningElementTypeEnum_RECESS,
  kIfcOpeningElementTypeEnum_USERDEFINED,
  kIfcOpeningElementTypeEnum_NOTDEFINED,
  kIfcOpeningElementTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcOpeningElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcOpeningElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcOpeningElementTypeEnum& getUnset<OdIfc4x3_rc4::IfcOpeningElementTypeEnum>() { static OdIfc4x3_rc4::IfcOpeningElementTypeEnum nullEnum = OdIfc4x3_rc4::kIfcOpeningElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcOutletTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcOutletTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcOutletTypeEnum& getUnset<OdIfc4x3_rc4::IfcOutletTypeEnum>() { static OdIfc4x3_rc4::IfcOutletTypeEnum nullEnum = OdIfc4x3_rc4::kIfcOutletTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcPavementTypeEnum
{
  kIfcPavementTypeEnum_FLEXIBLE,
  kIfcPavementTypeEnum_RIGID,
  kIfcPavementTypeEnum_USERDEFINED,
  kIfcPavementTypeEnum_NOTDEFINED,
  kIfcPavementTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcPavementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPavementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcPavementTypeEnum& getUnset<OdIfc4x3_rc4::IfcPavementTypeEnum>() { static OdIfc4x3_rc4::IfcPavementTypeEnum nullEnum = OdIfc4x3_rc4::kIfcPavementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcPerformanceHistoryTypeEnum
{
  kIfcPerformanceHistoryTypeEnum_USERDEFINED,
  kIfcPerformanceHistoryTypeEnum_NOTDEFINED,
  kIfcPerformanceHistoryTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcPerformanceHistoryTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPerformanceHistoryTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcPerformanceHistoryTypeEnum& getUnset<OdIfc4x3_rc4::IfcPerformanceHistoryTypeEnum>() { static OdIfc4x3_rc4::IfcPerformanceHistoryTypeEnum nullEnum = OdIfc4x3_rc4::kIfcPerformanceHistoryTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcPermeableCoveringOperationEnum
{
  kIfcPermeableCoveringOperationEnum_GRILL,
  kIfcPermeableCoveringOperationEnum_LOUVER,
  kIfcPermeableCoveringOperationEnum_SCREEN,
  kIfcPermeableCoveringOperationEnum_USERDEFINED,
  kIfcPermeableCoveringOperationEnum_NOTDEFINED,
  kIfcPermeableCoveringOperationEnum_unset
};

class IFC4X3_RC4_EXPORT IfcPermeableCoveringOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPermeableCoveringOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcPermeableCoveringOperationEnum& getUnset<OdIfc4x3_rc4::IfcPermeableCoveringOperationEnum>() { static OdIfc4x3_rc4::IfcPermeableCoveringOperationEnum nullEnum = OdIfc4x3_rc4::kIfcPermeableCoveringOperationEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcPermitTypeEnum
{
  kIfcPermitTypeEnum_ACCESS,
  kIfcPermitTypeEnum_BUILDING,
  kIfcPermitTypeEnum_WORK,
  kIfcPermitTypeEnum_USERDEFINED,
  kIfcPermitTypeEnum_NOTDEFINED,
  kIfcPermitTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcPermitTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPermitTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcPermitTypeEnum& getUnset<OdIfc4x3_rc4::IfcPermitTypeEnum>() { static OdIfc4x3_rc4::IfcPermitTypeEnum nullEnum = OdIfc4x3_rc4::kIfcPermitTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcPhysicalOrVirtualEnum
{
  kIfcPhysicalOrVirtualEnum_PHYSICAL,
  kIfcPhysicalOrVirtualEnum_VIRTUAL,
  kIfcPhysicalOrVirtualEnum_NOTDEFINED,
  kIfcPhysicalOrVirtualEnum_unset
};

class IFC4X3_RC4_EXPORT IfcPhysicalOrVirtualEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPhysicalOrVirtualEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcPhysicalOrVirtualEnum& getUnset<OdIfc4x3_rc4::IfcPhysicalOrVirtualEnum>() { static OdIfc4x3_rc4::IfcPhysicalOrVirtualEnum nullEnum = OdIfc4x3_rc4::kIfcPhysicalOrVirtualEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcPileConstructionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPileConstructionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcPileConstructionEnum& getUnset<OdIfc4x3_rc4::IfcPileConstructionEnum>() { static OdIfc4x3_rc4::IfcPileConstructionEnum nullEnum = OdIfc4x3_rc4::kIfcPileConstructionEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcPileTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPileTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcPileTypeEnum& getUnset<OdIfc4x3_rc4::IfcPileTypeEnum>() { static OdIfc4x3_rc4::IfcPileTypeEnum nullEnum = OdIfc4x3_rc4::kIfcPileTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcPipeFittingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPipeFittingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcPipeFittingTypeEnum& getUnset<OdIfc4x3_rc4::IfcPipeFittingTypeEnum>() { static OdIfc4x3_rc4::IfcPipeFittingTypeEnum nullEnum = OdIfc4x3_rc4::kIfcPipeFittingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcPipeSegmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPipeSegmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcPipeSegmentTypeEnum& getUnset<OdIfc4x3_rc4::IfcPipeSegmentTypeEnum>() { static OdIfc4x3_rc4::IfcPipeSegmentTypeEnum nullEnum = OdIfc4x3_rc4::kIfcPipeSegmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcPlateTypeEnum
{
  kIfcPlateTypeEnum_CURTAIN_PANEL,
  kIfcPlateTypeEnum_SHEET,
  kIfcPlateTypeEnum_FLANGE_PLATE,
  kIfcPlateTypeEnum_WEB_PLATE,
  kIfcPlateTypeEnum_STIFFENER_PLATE,
  kIfcPlateTypeEnum_GUSSET_PLATE,
  kIfcPlateTypeEnum_COVER_PLATE,
  kIfcPlateTypeEnum_SPLICE_PLATE,
  kIfcPlateTypeEnum_BASE_PLATE,
  kIfcPlateTypeEnum_USERDEFINED,
  kIfcPlateTypeEnum_NOTDEFINED,
  kIfcPlateTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcPlateTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPlateTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcPlateTypeEnum& getUnset<OdIfc4x3_rc4::IfcPlateTypeEnum>() { static OdIfc4x3_rc4::IfcPlateTypeEnum nullEnum = OdIfc4x3_rc4::kIfcPlateTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcPreferredSurfaceCurveRepresentation
{
  kIfcPreferredSurfaceCurveRepresentation_CURVE3D,
  kIfcPreferredSurfaceCurveRepresentation_PCURVE_S1,
  kIfcPreferredSurfaceCurveRepresentation_PCURVE_S2,
  kIfcPreferredSurfaceCurveRepresentation_unset
};

class IFC4X3_RC4_EXPORT IfcPreferredSurfaceCurveRepresentationTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPreferredSurfaceCurveRepresentationTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcPreferredSurfaceCurveRepresentation& getUnset<OdIfc4x3_rc4::IfcPreferredSurfaceCurveRepresentation>() { static OdIfc4x3_rc4::IfcPreferredSurfaceCurveRepresentation nullEnum = OdIfc4x3_rc4::kIfcPreferredSurfaceCurveRepresentation_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcProcedureTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProcedureTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcProcedureTypeEnum& getUnset<OdIfc4x3_rc4::IfcProcedureTypeEnum>() { static OdIfc4x3_rc4::IfcProcedureTypeEnum nullEnum = OdIfc4x3_rc4::kIfcProcedureTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcProfileTypeEnum
{
  kIfcProfileTypeEnum_CURVE,
  kIfcProfileTypeEnum_AREA,
  kIfcProfileTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcProfileTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProfileTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcProfileTypeEnum& getUnset<OdIfc4x3_rc4::IfcProfileTypeEnum>() { static OdIfc4x3_rc4::IfcProfileTypeEnum nullEnum = OdIfc4x3_rc4::kIfcProfileTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcProjectOrderTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProjectOrderTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcProjectOrderTypeEnum& getUnset<OdIfc4x3_rc4::IfcProjectOrderTypeEnum>() { static OdIfc4x3_rc4::IfcProjectOrderTypeEnum nullEnum = OdIfc4x3_rc4::kIfcProjectOrderTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcProjectedOrTrueLengthEnum
{
  kIfcProjectedOrTrueLengthEnum_PROJECTED_LENGTH,
  kIfcProjectedOrTrueLengthEnum_TRUE_LENGTH,
  kIfcProjectedOrTrueLengthEnum_unset
};

class IFC4X3_RC4_EXPORT IfcProjectedOrTrueLengthEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProjectedOrTrueLengthEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcProjectedOrTrueLengthEnum& getUnset<OdIfc4x3_rc4::IfcProjectedOrTrueLengthEnum>() { static OdIfc4x3_rc4::IfcProjectedOrTrueLengthEnum nullEnum = OdIfc4x3_rc4::kIfcProjectedOrTrueLengthEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcProjectionElementTypeEnum
{
  kIfcProjectionElementTypeEnum_BLISTER,
  kIfcProjectionElementTypeEnum_DEVIATOR,
  kIfcProjectionElementTypeEnum_USERDEFINED,
  kIfcProjectionElementTypeEnum_NOTDEFINED,
  kIfcProjectionElementTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcProjectionElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProjectionElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcProjectionElementTypeEnum& getUnset<OdIfc4x3_rc4::IfcProjectionElementTypeEnum>() { static OdIfc4x3_rc4::IfcProjectionElementTypeEnum nullEnum = OdIfc4x3_rc4::kIfcProjectionElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcPropertySetTemplateTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPropertySetTemplateTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcPropertySetTemplateTypeEnum& getUnset<OdIfc4x3_rc4::IfcPropertySetTemplateTypeEnum>() { static OdIfc4x3_rc4::IfcPropertySetTemplateTypeEnum nullEnum = OdIfc4x3_rc4::kIfcPropertySetTemplateTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcProtectiveDeviceTrippingUnitTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProtectiveDeviceTrippingUnitTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcProtectiveDeviceTrippingUnitTypeEnum& getUnset<OdIfc4x3_rc4::IfcProtectiveDeviceTrippingUnitTypeEnum>() { static OdIfc4x3_rc4::IfcProtectiveDeviceTrippingUnitTypeEnum nullEnum = OdIfc4x3_rc4::kIfcProtectiveDeviceTrippingUnitTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcProtectiveDeviceTypeEnum
{
  kIfcProtectiveDeviceTypeEnum_CIRCUITBREAKER,
  kIfcProtectiveDeviceTypeEnum_EARTHLEAKAGECIRCUITBREAKER,
  kIfcProtectiveDeviceTypeEnum_EARTHINGSWITCH,
  kIfcProtectiveDeviceTypeEnum_FUSEDISCONNECTOR,
  kIfcProtectiveDeviceTypeEnum_RESIDUALCURRENTCIRCUITBREAKER,
  kIfcProtectiveDeviceTypeEnum_RESIDUALCURRENTSWITCH,
  kIfcProtectiveDeviceTypeEnum_VARISTOR,
  kIfcProtectiveDeviceTypeEnum_ANTI_ARCING_DEVICE,
  kIfcProtectiveDeviceTypeEnum_SPARKGAP,
  kIfcProtectiveDeviceTypeEnum_VOLTAGELIMITER,
  kIfcProtectiveDeviceTypeEnum_USERDEFINED,
  kIfcProtectiveDeviceTypeEnum_NOTDEFINED,
  kIfcProtectiveDeviceTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcProtectiveDeviceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProtectiveDeviceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcProtectiveDeviceTypeEnum& getUnset<OdIfc4x3_rc4::IfcProtectiveDeviceTypeEnum>() { static OdIfc4x3_rc4::IfcProtectiveDeviceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcProtectiveDeviceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcPumpTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPumpTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcPumpTypeEnum& getUnset<OdIfc4x3_rc4::IfcPumpTypeEnum>() { static OdIfc4x3_rc4::IfcPumpTypeEnum nullEnum = OdIfc4x3_rc4::kIfcPumpTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcRailTypeEnum
{
  kIfcRailTypeEnum_RACKRAIL,
  kIfcRailTypeEnum_BLADE,
  kIfcRailTypeEnum_GUARDRAIL,
  kIfcRailTypeEnum_STOCKRAIL,
  kIfcRailTypeEnum_CHECKRAIL,
  kIfcRailTypeEnum_RAIL,
  kIfcRailTypeEnum_USERDEFINED,
  kIfcRailTypeEnum_NOTDEFINED,
  kIfcRailTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcRailTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRailTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcRailTypeEnum& getUnset<OdIfc4x3_rc4::IfcRailTypeEnum>() { static OdIfc4x3_rc4::IfcRailTypeEnum nullEnum = OdIfc4x3_rc4::kIfcRailTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcRailingTypeEnum
{
  kIfcRailingTypeEnum_HANDRAIL,
  kIfcRailingTypeEnum_GUARDRAIL,
  kIfcRailingTypeEnum_BALUSTRADE,
  kIfcRailingTypeEnum_FENCE,
  kIfcRailingTypeEnum_USERDEFINED,
  kIfcRailingTypeEnum_NOTDEFINED,
  kIfcRailingTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcRailingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRailingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcRailingTypeEnum& getUnset<OdIfc4x3_rc4::IfcRailingTypeEnum>() { static OdIfc4x3_rc4::IfcRailingTypeEnum nullEnum = OdIfc4x3_rc4::kIfcRailingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcRailwayPartTypeEnum
{
  kIfcRailwayPartTypeEnum_TRACKSTRUCTURE,
  kIfcRailwayPartTypeEnum_TRACKSTRUCTUREPART,
  kIfcRailwayPartTypeEnum_LINESIDESTRUCTUREPART,
  kIfcRailwayPartTypeEnum_DILATATIONSUPERSTRUCTURE,
  kIfcRailwayPartTypeEnum_PLAINTRACKSUPERSTRUCTURE,
  kIfcRailwayPartTypeEnum_LINESIDESTRUCTURE,
  kIfcRailwayPartTypeEnum_SUPERSTRUCTURE,
  kIfcRailwayPartTypeEnum_TURNOUTSUPERSTRUCTURE,
  kIfcRailwayPartTypeEnum_USERDEFINED,
  kIfcRailwayPartTypeEnum_NOTDEFINED,
  kIfcRailwayPartTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcRailwayPartTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRailwayPartTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcRailwayPartTypeEnum& getUnset<OdIfc4x3_rc4::IfcRailwayPartTypeEnum>() { static OdIfc4x3_rc4::IfcRailwayPartTypeEnum nullEnum = OdIfc4x3_rc4::kIfcRailwayPartTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcRailwayTypeEnum
{
  kIfcRailwayTypeEnum_USERDEFINED,
  kIfcRailwayTypeEnum_NOTDEFINED,
  kIfcRailwayTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcRailwayTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRailwayTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcRailwayTypeEnum& getUnset<OdIfc4x3_rc4::IfcRailwayTypeEnum>() { static OdIfc4x3_rc4::IfcRailwayTypeEnum nullEnum = OdIfc4x3_rc4::kIfcRailwayTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcRampFlightTypeEnum
{
  kIfcRampFlightTypeEnum_STRAIGHT,
  kIfcRampFlightTypeEnum_SPIRAL,
  kIfcRampFlightTypeEnum_USERDEFINED,
  kIfcRampFlightTypeEnum_NOTDEFINED,
  kIfcRampFlightTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcRampFlightTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRampFlightTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcRampFlightTypeEnum& getUnset<OdIfc4x3_rc4::IfcRampFlightTypeEnum>() { static OdIfc4x3_rc4::IfcRampFlightTypeEnum nullEnum = OdIfc4x3_rc4::kIfcRampFlightTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcRampTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRampTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcRampTypeEnum& getUnset<OdIfc4x3_rc4::IfcRampTypeEnum>() { static OdIfc4x3_rc4::IfcRampTypeEnum nullEnum = OdIfc4x3_rc4::kIfcRampTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcRecurrenceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRecurrenceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcRecurrenceTypeEnum& getUnset<OdIfc4x3_rc4::IfcRecurrenceTypeEnum>() { static OdIfc4x3_rc4::IfcRecurrenceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcRecurrenceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcReferentTypeEnum
{
  kIfcReferentTypeEnum_KILOPOINT,
  kIfcReferentTypeEnum_MILEPOINT,
  kIfcReferentTypeEnum_STATION,
  kIfcReferentTypeEnum_REFERENCEMARKER,
  kIfcReferentTypeEnum_LANDMARK,
  kIfcReferentTypeEnum_BOUNDARY,
  kIfcReferentTypeEnum_INTERSECTION,
  kIfcReferentTypeEnum_POSITION,
  kIfcReferentTypeEnum_USERDEFINED,
  kIfcReferentTypeEnum_NOTDEFINED,
  kIfcReferentTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcReferentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcReferentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcReferentTypeEnum& getUnset<OdIfc4x3_rc4::IfcReferentTypeEnum>() { static OdIfc4x3_rc4::IfcReferentTypeEnum nullEnum = OdIfc4x3_rc4::kIfcReferentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcReflectanceMethodEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcReflectanceMethodEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcReflectanceMethodEnum& getUnset<OdIfc4x3_rc4::IfcReflectanceMethodEnum>() { static OdIfc4x3_rc4::IfcReflectanceMethodEnum nullEnum = OdIfc4x3_rc4::kIfcReflectanceMethodEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcReinforcedSoilTypeEnum
{
  kIfcReinforcedSoilTypeEnum_SURCHARGEPRELOADED,
  kIfcReinforcedSoilTypeEnum_VERTICALLYDRAINED,
  kIfcReinforcedSoilTypeEnum_DYNAMICALLYCOMPACTED,
  kIfcReinforcedSoilTypeEnum_REPLACED,
  kIfcReinforcedSoilTypeEnum_ROLLERCOMPACTED,
  kIfcReinforcedSoilTypeEnum_GROUTED,
  kIfcReinforcedSoilTypeEnum_USERDEFINED,
  kIfcReinforcedSoilTypeEnum_NOTDEFINED,
  kIfcReinforcedSoilTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcReinforcedSoilTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcReinforcedSoilTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcReinforcedSoilTypeEnum& getUnset<OdIfc4x3_rc4::IfcReinforcedSoilTypeEnum>() { static OdIfc4x3_rc4::IfcReinforcedSoilTypeEnum nullEnum = OdIfc4x3_rc4::kIfcReinforcedSoilTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcReinforcingBarRoleEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcReinforcingBarRoleEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcReinforcingBarRoleEnum& getUnset<OdIfc4x3_rc4::IfcReinforcingBarRoleEnum>() { static OdIfc4x3_rc4::IfcReinforcingBarRoleEnum nullEnum = OdIfc4x3_rc4::kIfcReinforcingBarRoleEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcReinforcingBarSurfaceEnum
{
  kIfcReinforcingBarSurfaceEnum_PLAIN,
  kIfcReinforcingBarSurfaceEnum_TEXTURED,
  kIfcReinforcingBarSurfaceEnum_unset
};

class IFC4X3_RC4_EXPORT IfcReinforcingBarSurfaceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcReinforcingBarSurfaceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcReinforcingBarSurfaceEnum& getUnset<OdIfc4x3_rc4::IfcReinforcingBarSurfaceEnum>() { static OdIfc4x3_rc4::IfcReinforcingBarSurfaceEnum nullEnum = OdIfc4x3_rc4::kIfcReinforcingBarSurfaceEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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
  kIfcReinforcingBarTypeEnum_SPACEBAR,
  kIfcReinforcingBarTypeEnum_USERDEFINED,
  kIfcReinforcingBarTypeEnum_NOTDEFINED,
  kIfcReinforcingBarTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcReinforcingBarTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcReinforcingBarTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcReinforcingBarTypeEnum& getUnset<OdIfc4x3_rc4::IfcReinforcingBarTypeEnum>() { static OdIfc4x3_rc4::IfcReinforcingBarTypeEnum nullEnum = OdIfc4x3_rc4::kIfcReinforcingBarTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcReinforcingMeshTypeEnum
{
  kIfcReinforcingMeshTypeEnum_USERDEFINED,
  kIfcReinforcingMeshTypeEnum_NOTDEFINED,
  kIfcReinforcingMeshTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcReinforcingMeshTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcReinforcingMeshTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcReinforcingMeshTypeEnum& getUnset<OdIfc4x3_rc4::IfcReinforcingMeshTypeEnum>() { static OdIfc4x3_rc4::IfcReinforcingMeshTypeEnum nullEnum = OdIfc4x3_rc4::kIfcReinforcingMeshTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcRoadPartTypeEnum
{
  kIfcRoadPartTypeEnum_ROADSIDEPART,
  kIfcRoadPartTypeEnum_BUS_STOP,
  kIfcRoadPartTypeEnum_HARDSHOULDER,
  kIfcRoadPartTypeEnum_INTERSECTION,
  kIfcRoadPartTypeEnum_PASSINGBAY,
  kIfcRoadPartTypeEnum_ROADWAYPLATEAU,
  kIfcRoadPartTypeEnum_ROADSIDE,
  kIfcRoadPartTypeEnum_REFUGEISLAND,
  kIfcRoadPartTypeEnum_TOLLPLAZA,
  kIfcRoadPartTypeEnum_CENTRALRESERVE,
  kIfcRoadPartTypeEnum_SIDEWALK,
  kIfcRoadPartTypeEnum_PARKINGBAY,
  kIfcRoadPartTypeEnum_RAILWAYCROSSING,
  kIfcRoadPartTypeEnum_PEDESTRIAN_CROSSING,
  kIfcRoadPartTypeEnum_SOFTSHOULDER,
  kIfcRoadPartTypeEnum_BICYCLECROSSING,
  kIfcRoadPartTypeEnum_CENTRALISLAND,
  kIfcRoadPartTypeEnum_SHOULDER,
  kIfcRoadPartTypeEnum_TRAFFICLANE,
  kIfcRoadPartTypeEnum_ROADSEGMENT,
  kIfcRoadPartTypeEnum_ROUNDABOUT,
  kIfcRoadPartTypeEnum_LAYBY,
  kIfcRoadPartTypeEnum_CARRIAGEWAY,
  kIfcRoadPartTypeEnum_TRAFFICISLAND,
  kIfcRoadPartTypeEnum_USERDEFINED,
  kIfcRoadPartTypeEnum_NOTDEFINED,
  kIfcRoadPartTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcRoadPartTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRoadPartTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcRoadPartTypeEnum& getUnset<OdIfc4x3_rc4::IfcRoadPartTypeEnum>() { static OdIfc4x3_rc4::IfcRoadPartTypeEnum nullEnum = OdIfc4x3_rc4::kIfcRoadPartTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcRoadTypeEnum
{
  kIfcRoadTypeEnum_USERDEFINED,
  kIfcRoadTypeEnum_NOTDEFINED,
  kIfcRoadTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcRoadTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRoadTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcRoadTypeEnum& getUnset<OdIfc4x3_rc4::IfcRoadTypeEnum>() { static OdIfc4x3_rc4::IfcRoadTypeEnum nullEnum = OdIfc4x3_rc4::kIfcRoadTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcRoleEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRoleEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcRoleEnum& getUnset<OdIfc4x3_rc4::IfcRoleEnum>() { static OdIfc4x3_rc4::IfcRoleEnum nullEnum = OdIfc4x3_rc4::kIfcRoleEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcRoofTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRoofTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcRoofTypeEnum& getUnset<OdIfc4x3_rc4::IfcRoofTypeEnum>() { static OdIfc4x3_rc4::IfcRoofTypeEnum nullEnum = OdIfc4x3_rc4::kIfcRoofTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcSIPrefixTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSIPrefixTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcSIPrefix& getUnset<OdIfc4x3_rc4::IfcSIPrefix>() { static OdIfc4x3_rc4::IfcSIPrefix nullEnum = OdIfc4x3_rc4::kIfcSIPrefix_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcSIUnitNameTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSIUnitNameTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcSIUnitName& getUnset<OdIfc4x3_rc4::IfcSIUnitName>() { static OdIfc4x3_rc4::IfcSIUnitName nullEnum = OdIfc4x3_rc4::kIfcSIUnitName_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcSanitaryTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSanitaryTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcSanitaryTerminalTypeEnum& getUnset<OdIfc4x3_rc4::IfcSanitaryTerminalTypeEnum>() { static OdIfc4x3_rc4::IfcSanitaryTerminalTypeEnum nullEnum = OdIfc4x3_rc4::kIfcSanitaryTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcSectionTypeEnum
{
  kIfcSectionTypeEnum_UNIFORM,
  kIfcSectionTypeEnum_TAPERED,
  kIfcSectionTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcSectionTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSectionTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcSectionTypeEnum& getUnset<OdIfc4x3_rc4::IfcSectionTypeEnum>() { static OdIfc4x3_rc4::IfcSectionTypeEnum nullEnum = OdIfc4x3_rc4::kIfcSectionTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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
  kIfcSensorTypeEnum_EARTHQUAKESENSOR,
  kIfcSensorTypeEnum_FOREIGNOBJECTDETECTIONSENSOR,
  kIfcSensorTypeEnum_OBSTACLESENSOR,
  kIfcSensorTypeEnum_RAINSENSOR,
  kIfcSensorTypeEnum_SNOWDEPTHSENSOR,
  kIfcSensorTypeEnum_TRAINSENSOR,
  kIfcSensorTypeEnum_TURNOUTCLOSURESENSOR,
  kIfcSensorTypeEnum_WHEELSENSOR,
  kIfcSensorTypeEnum_USERDEFINED,
  kIfcSensorTypeEnum_NOTDEFINED,
  kIfcSensorTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcSensorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSensorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcSensorTypeEnum& getUnset<OdIfc4x3_rc4::IfcSensorTypeEnum>() { static OdIfc4x3_rc4::IfcSensorTypeEnum nullEnum = OdIfc4x3_rc4::kIfcSensorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcSequenceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSequenceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcSequenceEnum& getUnset<OdIfc4x3_rc4::IfcSequenceEnum>() { static OdIfc4x3_rc4::IfcSequenceEnum nullEnum = OdIfc4x3_rc4::kIfcSequenceEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcShadingDeviceTypeEnum
{
  kIfcShadingDeviceTypeEnum_JALOUSIE,
  kIfcShadingDeviceTypeEnum_SHUTTER,
  kIfcShadingDeviceTypeEnum_AWNING,
  kIfcShadingDeviceTypeEnum_USERDEFINED,
  kIfcShadingDeviceTypeEnum_NOTDEFINED,
  kIfcShadingDeviceTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcShadingDeviceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcShadingDeviceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcShadingDeviceTypeEnum& getUnset<OdIfc4x3_rc4::IfcShadingDeviceTypeEnum>() { static OdIfc4x3_rc4::IfcShadingDeviceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcShadingDeviceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcSignTypeEnum
{
  kIfcSignTypeEnum_MARKER,
  kIfcSignTypeEnum_PICTORAL,
  kIfcSignTypeEnum_MIRROR,
  kIfcSignTypeEnum_USERDEFINED,
  kIfcSignTypeEnum_NOTDEFINED,
  kIfcSignTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcSignTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSignTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcSignTypeEnum& getUnset<OdIfc4x3_rc4::IfcSignTypeEnum>() { static OdIfc4x3_rc4::IfcSignTypeEnum nullEnum = OdIfc4x3_rc4::kIfcSignTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcSignalTypeEnum
{
  kIfcSignalTypeEnum_VISUAL,
  kIfcSignalTypeEnum_AUDIO,
  kIfcSignalTypeEnum_MIXED,
  kIfcSignalTypeEnum_USERDEFINED,
  kIfcSignalTypeEnum_NOTDEFINED,
  kIfcSignalTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcSignalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSignalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcSignalTypeEnum& getUnset<OdIfc4x3_rc4::IfcSignalTypeEnum>() { static OdIfc4x3_rc4::IfcSignalTypeEnum nullEnum = OdIfc4x3_rc4::kIfcSignalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcSimplePropertyTemplateTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSimplePropertyTemplateTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcSimplePropertyTemplateTypeEnum& getUnset<OdIfc4x3_rc4::IfcSimplePropertyTemplateTypeEnum>() { static OdIfc4x3_rc4::IfcSimplePropertyTemplateTypeEnum nullEnum = OdIfc4x3_rc4::kIfcSimplePropertyTemplateTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcSlabTypeEnum
{
  kIfcSlabTypeEnum_FLOOR,
  kIfcSlabTypeEnum_ROOF,
  kIfcSlabTypeEnum_LANDING,
  kIfcSlabTypeEnum_BASESLAB,
  kIfcSlabTypeEnum_APPROACH_SLAB,
  kIfcSlabTypeEnum_PAVING,
  kIfcSlabTypeEnum_WEARING,
  kIfcSlabTypeEnum_SIDEWALK,
  kIfcSlabTypeEnum_TRACKSLAB,
  kIfcSlabTypeEnum_USERDEFINED,
  kIfcSlabTypeEnum_NOTDEFINED,
  kIfcSlabTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcSlabTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSlabTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcSlabTypeEnum& getUnset<OdIfc4x3_rc4::IfcSlabTypeEnum>() { static OdIfc4x3_rc4::IfcSlabTypeEnum nullEnum = OdIfc4x3_rc4::kIfcSlabTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcSolarDeviceTypeEnum
{
  kIfcSolarDeviceTypeEnum_SOLARCOLLECTOR,
  kIfcSolarDeviceTypeEnum_SOLARPANEL,
  kIfcSolarDeviceTypeEnum_USERDEFINED,
  kIfcSolarDeviceTypeEnum_NOTDEFINED,
  kIfcSolarDeviceTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcSolarDeviceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSolarDeviceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcSolarDeviceTypeEnum& getUnset<OdIfc4x3_rc4::IfcSolarDeviceTypeEnum>() { static OdIfc4x3_rc4::IfcSolarDeviceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcSolarDeviceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcSpaceHeaterTypeEnum
{
  kIfcSpaceHeaterTypeEnum_CONVECTOR,
  kIfcSpaceHeaterTypeEnum_RADIATOR,
  kIfcSpaceHeaterTypeEnum_USERDEFINED,
  kIfcSpaceHeaterTypeEnum_NOTDEFINED,
  kIfcSpaceHeaterTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcSpaceHeaterTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSpaceHeaterTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcSpaceHeaterTypeEnum& getUnset<OdIfc4x3_rc4::IfcSpaceHeaterTypeEnum>() { static OdIfc4x3_rc4::IfcSpaceHeaterTypeEnum nullEnum = OdIfc4x3_rc4::kIfcSpaceHeaterTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcSpaceTypeEnum
{
  kIfcSpaceTypeEnum_SPACE,
  kIfcSpaceTypeEnum_PARKING,
  kIfcSpaceTypeEnum_GFA,
  kIfcSpaceTypeEnum_INTERNAL,
  kIfcSpaceTypeEnum_EXTERNAL,
  kIfcSpaceTypeEnum_BERTH,
  kIfcSpaceTypeEnum_USERDEFINED,
  kIfcSpaceTypeEnum_NOTDEFINED,
  kIfcSpaceTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcSpaceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSpaceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcSpaceTypeEnum& getUnset<OdIfc4x3_rc4::IfcSpaceTypeEnum>() { static OdIfc4x3_rc4::IfcSpaceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcSpaceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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
  kIfcSpatialZoneTypeEnum_RESERVATION,
  kIfcSpatialZoneTypeEnum_INTERFERENCE,
  kIfcSpatialZoneTypeEnum_USERDEFINED,
  kIfcSpatialZoneTypeEnum_NOTDEFINED,
  kIfcSpatialZoneTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcSpatialZoneTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSpatialZoneTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcSpatialZoneTypeEnum& getUnset<OdIfc4x3_rc4::IfcSpatialZoneTypeEnum>() { static OdIfc4x3_rc4::IfcSpatialZoneTypeEnum nullEnum = OdIfc4x3_rc4::kIfcSpatialZoneTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcStackTerminalTypeEnum
{
  kIfcStackTerminalTypeEnum_BIRDCAGE,
  kIfcStackTerminalTypeEnum_COWL,
  kIfcStackTerminalTypeEnum_RAINWATERHOPPER,
  kIfcStackTerminalTypeEnum_USERDEFINED,
  kIfcStackTerminalTypeEnum_NOTDEFINED,
  kIfcStackTerminalTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcStackTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStackTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcStackTerminalTypeEnum& getUnset<OdIfc4x3_rc4::IfcStackTerminalTypeEnum>() { static OdIfc4x3_rc4::IfcStackTerminalTypeEnum nullEnum = OdIfc4x3_rc4::kIfcStackTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcStairFlightTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStairFlightTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcStairFlightTypeEnum& getUnset<OdIfc4x3_rc4::IfcStairFlightTypeEnum>() { static OdIfc4x3_rc4::IfcStairFlightTypeEnum nullEnum = OdIfc4x3_rc4::kIfcStairFlightTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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
  kIfcStairTypeEnum_LADDER,
  kIfcStairTypeEnum_USERDEFINED,
  kIfcStairTypeEnum_NOTDEFINED,
  kIfcStairTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcStairTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStairTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcStairTypeEnum& getUnset<OdIfc4x3_rc4::IfcStairTypeEnum>() { static OdIfc4x3_rc4::IfcStairTypeEnum nullEnum = OdIfc4x3_rc4::kIfcStairTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcStateEnum
{
  kIfcStateEnum_READWRITE,
  kIfcStateEnum_READONLY,
  kIfcStateEnum_LOCKED,
  kIfcStateEnum_READWRITELOCKED,
  kIfcStateEnum_READONLYLOCKED,
  kIfcStateEnum_unset
};

class IFC4X3_RC4_EXPORT IfcStateEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStateEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcStateEnum& getUnset<OdIfc4x3_rc4::IfcStateEnum>() { static OdIfc4x3_rc4::IfcStateEnum nullEnum = OdIfc4x3_rc4::kIfcStateEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcStructuralCurveActivityTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStructuralCurveActivityTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcStructuralCurveActivityTypeEnum& getUnset<OdIfc4x3_rc4::IfcStructuralCurveActivityTypeEnum>() { static OdIfc4x3_rc4::IfcStructuralCurveActivityTypeEnum nullEnum = OdIfc4x3_rc4::kIfcStructuralCurveActivityTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcStructuralCurveMemberTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStructuralCurveMemberTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcStructuralCurveMemberTypeEnum& getUnset<OdIfc4x3_rc4::IfcStructuralCurveMemberTypeEnum>() { static OdIfc4x3_rc4::IfcStructuralCurveMemberTypeEnum nullEnum = OdIfc4x3_rc4::kIfcStructuralCurveMemberTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcStructuralSurfaceActivityTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStructuralSurfaceActivityTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcStructuralSurfaceActivityTypeEnum& getUnset<OdIfc4x3_rc4::IfcStructuralSurfaceActivityTypeEnum>() { static OdIfc4x3_rc4::IfcStructuralSurfaceActivityTypeEnum nullEnum = OdIfc4x3_rc4::kIfcStructuralSurfaceActivityTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcStructuralSurfaceMemberTypeEnum
{
  kIfcStructuralSurfaceMemberTypeEnum_BENDING_ELEMENT,
  kIfcStructuralSurfaceMemberTypeEnum_MEMBRANE_ELEMENT,
  kIfcStructuralSurfaceMemberTypeEnum_SHELL,
  kIfcStructuralSurfaceMemberTypeEnum_USERDEFINED,
  kIfcStructuralSurfaceMemberTypeEnum_NOTDEFINED,
  kIfcStructuralSurfaceMemberTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcStructuralSurfaceMemberTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStructuralSurfaceMemberTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcStructuralSurfaceMemberTypeEnum& getUnset<OdIfc4x3_rc4::IfcStructuralSurfaceMemberTypeEnum>() { static OdIfc4x3_rc4::IfcStructuralSurfaceMemberTypeEnum nullEnum = OdIfc4x3_rc4::kIfcStructuralSurfaceMemberTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcSubContractResourceTypeEnum
{
  kIfcSubContractResourceTypeEnum_PURCHASE,
  kIfcSubContractResourceTypeEnum_WORK,
  kIfcSubContractResourceTypeEnum_USERDEFINED,
  kIfcSubContractResourceTypeEnum_NOTDEFINED,
  kIfcSubContractResourceTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcSubContractResourceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSubContractResourceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcSubContractResourceTypeEnum& getUnset<OdIfc4x3_rc4::IfcSubContractResourceTypeEnum>() { static OdIfc4x3_rc4::IfcSubContractResourceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcSubContractResourceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcSurfaceFeatureTypeEnum
{
  kIfcSurfaceFeatureTypeEnum_MARK,
  kIfcSurfaceFeatureTypeEnum_TAG,
  kIfcSurfaceFeatureTypeEnum_TREATMENT,
  kIfcSurfaceFeatureTypeEnum_DEFECT,
  kIfcSurfaceFeatureTypeEnum_HATCHMARKING,
  kIfcSurfaceFeatureTypeEnum_LINEMARKING,
  kIfcSurfaceFeatureTypeEnum_PAVEMENTSURFACEMARKING,
  kIfcSurfaceFeatureTypeEnum_SYMBOLMARKING,
  kIfcSurfaceFeatureTypeEnum_NONSKIDSURFACING,
  kIfcSurfaceFeatureTypeEnum_RUMBLESTRIP,
  kIfcSurfaceFeatureTypeEnum_TRANSVERSERUMBLESTRIP,
  kIfcSurfaceFeatureTypeEnum_USERDEFINED,
  kIfcSurfaceFeatureTypeEnum_NOTDEFINED,
  kIfcSurfaceFeatureTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcSurfaceFeatureTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSurfaceFeatureTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcSurfaceFeatureTypeEnum& getUnset<OdIfc4x3_rc4::IfcSurfaceFeatureTypeEnum>() { static OdIfc4x3_rc4::IfcSurfaceFeatureTypeEnum nullEnum = OdIfc4x3_rc4::kIfcSurfaceFeatureTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcSurfaceSide
{
  kIfcSurfaceSide_POSITIVE,
  kIfcSurfaceSide_NEGATIVE,
  kIfcSurfaceSide_BOTH,
  kIfcSurfaceSide_unset
};

class IFC4X3_RC4_EXPORT IfcSurfaceSideTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSurfaceSideTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcSurfaceSide& getUnset<OdIfc4x3_rc4::IfcSurfaceSide>() { static OdIfc4x3_rc4::IfcSurfaceSide nullEnum = OdIfc4x3_rc4::kIfcSurfaceSide_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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
  kIfcSwitchingDeviceTypeEnum_RELAY,
  kIfcSwitchingDeviceTypeEnum_START_AND_STOP_EQUIPMENT,
  kIfcSwitchingDeviceTypeEnum_USERDEFINED,
  kIfcSwitchingDeviceTypeEnum_NOTDEFINED,
  kIfcSwitchingDeviceTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcSwitchingDeviceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSwitchingDeviceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcSwitchingDeviceTypeEnum& getUnset<OdIfc4x3_rc4::IfcSwitchingDeviceTypeEnum>() { static OdIfc4x3_rc4::IfcSwitchingDeviceTypeEnum nullEnum = OdIfc4x3_rc4::kIfcSwitchingDeviceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcSystemFurnitureElementTypeEnum
{
  kIfcSystemFurnitureElementTypeEnum_PANEL,
  kIfcSystemFurnitureElementTypeEnum_WORKSURFACE,
  kIfcSystemFurnitureElementTypeEnum_SUBRACK,
  kIfcSystemFurnitureElementTypeEnum_USERDEFINED,
  kIfcSystemFurnitureElementTypeEnum_NOTDEFINED,
  kIfcSystemFurnitureElementTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcSystemFurnitureElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSystemFurnitureElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcSystemFurnitureElementTypeEnum& getUnset<OdIfc4x3_rc4::IfcSystemFurnitureElementTypeEnum>() { static OdIfc4x3_rc4::IfcSystemFurnitureElementTypeEnum nullEnum = OdIfc4x3_rc4::kIfcSystemFurnitureElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcTankTypeEnum
{
  kIfcTankTypeEnum_BASIN,
  kIfcTankTypeEnum_BREAKPRESSURE,
  kIfcTankTypeEnum_EXPANSION,
  kIfcTankTypeEnum_FEEDANDEXPANSION,
  kIfcTankTypeEnum_PRESSUREVESSEL,
  kIfcTankTypeEnum_STORAGE,
  kIfcTankTypeEnum_VESSEL,
  kIfcTankTypeEnum_OILRETENTIONTRAY,
  kIfcTankTypeEnum_USERDEFINED,
  kIfcTankTypeEnum_NOTDEFINED,
  kIfcTankTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcTankTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTankTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcTankTypeEnum& getUnset<OdIfc4x3_rc4::IfcTankTypeEnum>() { static OdIfc4x3_rc4::IfcTankTypeEnum nullEnum = OdIfc4x3_rc4::kIfcTankTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcTaskDurationEnum
{
  kIfcTaskDurationEnum_ELAPSEDTIME,
  kIfcTaskDurationEnum_WORKTIME,
  kIfcTaskDurationEnum_NOTDEFINED,
  kIfcTaskDurationEnum_unset
};

class IFC4X3_RC4_EXPORT IfcTaskDurationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTaskDurationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcTaskDurationEnum& getUnset<OdIfc4x3_rc4::IfcTaskDurationEnum>() { static OdIfc4x3_rc4::IfcTaskDurationEnum nullEnum = OdIfc4x3_rc4::kIfcTaskDurationEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcTaskTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTaskTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcTaskTypeEnum& getUnset<OdIfc4x3_rc4::IfcTaskTypeEnum>() { static OdIfc4x3_rc4::IfcTaskTypeEnum nullEnum = OdIfc4x3_rc4::kIfcTaskTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcTendonAnchorTypeEnum
{
  kIfcTendonAnchorTypeEnum_COUPLER,
  kIfcTendonAnchorTypeEnum_FIXED_END,
  kIfcTendonAnchorTypeEnum_TENSIONING_END,
  kIfcTendonAnchorTypeEnum_USERDEFINED,
  kIfcTendonAnchorTypeEnum_NOTDEFINED,
  kIfcTendonAnchorTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcTendonAnchorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTendonAnchorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcTendonAnchorTypeEnum& getUnset<OdIfc4x3_rc4::IfcTendonAnchorTypeEnum>() { static OdIfc4x3_rc4::IfcTendonAnchorTypeEnum nullEnum = OdIfc4x3_rc4::kIfcTendonAnchorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcTendonConduitTypeEnum
{
  kIfcTendonConduitTypeEnum_DUCT,
  kIfcTendonConduitTypeEnum_COUPLER,
  kIfcTendonConduitTypeEnum_GROUTING_DUCT,
  kIfcTendonConduitTypeEnum_TRUMPET,
  kIfcTendonConduitTypeEnum_DIABOLO,
  kIfcTendonConduitTypeEnum_USERDEFINED,
  kIfcTendonConduitTypeEnum_NOTDEFINED,
  kIfcTendonConduitTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcTendonConduitTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTendonConduitTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcTendonConduitTypeEnum& getUnset<OdIfc4x3_rc4::IfcTendonConduitTypeEnum>() { static OdIfc4x3_rc4::IfcTendonConduitTypeEnum nullEnum = OdIfc4x3_rc4::kIfcTendonConduitTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcTendonTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTendonTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcTendonTypeEnum& getUnset<OdIfc4x3_rc4::IfcTendonTypeEnum>() { static OdIfc4x3_rc4::IfcTendonTypeEnum nullEnum = OdIfc4x3_rc4::kIfcTendonTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcTextPath
{
  kIfcTextPath_LEFT,
  kIfcTextPath_RIGHT,
  kIfcTextPath_UP,
  kIfcTextPath_DOWN,
  kIfcTextPath_unset
};

class IFC4X3_RC4_EXPORT IfcTextPathTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTextPathTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcTextPath& getUnset<OdIfc4x3_rc4::IfcTextPath>() { static OdIfc4x3_rc4::IfcTextPath nullEnum = OdIfc4x3_rc4::kIfcTextPath_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcTimeSeriesDataTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTimeSeriesDataTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcTimeSeriesDataTypeEnum& getUnset<OdIfc4x3_rc4::IfcTimeSeriesDataTypeEnum>() { static OdIfc4x3_rc4::IfcTimeSeriesDataTypeEnum nullEnum = OdIfc4x3_rc4::kIfcTimeSeriesDataTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcTrackElementTypeEnum
{
  kIfcTrackElementTypeEnum_TRACKENDOFALIGNMENT,
  kIfcTrackElementTypeEnum_BLOCKINGDEVICE,
  kIfcTrackElementTypeEnum_VEHICLESTOP,
  kIfcTrackElementTypeEnum_SLEEPER,
  kIfcTrackElementTypeEnum_HALF_SET_OF_BLADES,
  kIfcTrackElementTypeEnum_SPEEDREGULATOR,
  kIfcTrackElementTypeEnum_DERAILER,
  kIfcTrackElementTypeEnum_FROG,
  kIfcTrackElementTypeEnum_USERDEFINED,
  kIfcTrackElementTypeEnum_NOTDEFINED,
  kIfcTrackElementTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcTrackElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTrackElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcTrackElementTypeEnum& getUnset<OdIfc4x3_rc4::IfcTrackElementTypeEnum>() { static OdIfc4x3_rc4::IfcTrackElementTypeEnum nullEnum = OdIfc4x3_rc4::kIfcTrackElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcTransformerTypeEnum
{
  kIfcTransformerTypeEnum_CURRENT,
  kIfcTransformerTypeEnum_FREQUENCY,
  kIfcTransformerTypeEnum_INVERTER,
  kIfcTransformerTypeEnum_RECTIFIER,
  kIfcTransformerTypeEnum_VOLTAGE,
  kIfcTransformerTypeEnum_CHOPPER,
  kIfcTransformerTypeEnum_COMBINED,
  kIfcTransformerTypeEnum_USERDEFINED,
  kIfcTransformerTypeEnum_NOTDEFINED,
  kIfcTransformerTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcTransformerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTransformerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcTransformerTypeEnum& getUnset<OdIfc4x3_rc4::IfcTransformerTypeEnum>() { static OdIfc4x3_rc4::IfcTransformerTypeEnum nullEnum = OdIfc4x3_rc4::kIfcTransformerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcTransitionCode
{
  kIfcTransitionCode_DISCONTINUOUS,
  kIfcTransitionCode_CONTINUOUS,
  kIfcTransitionCode_CONTSAMEGRADIENT,
  kIfcTransitionCode_CONTSAMEGRADIENTSAMECURVATURE,
  kIfcTransitionCode_unset
};

class IFC4X3_RC4_EXPORT IfcTransitionCodeTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTransitionCodeTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcTransitionCode& getUnset<OdIfc4x3_rc4::IfcTransitionCode>() { static OdIfc4x3_rc4::IfcTransitionCode nullEnum = OdIfc4x3_rc4::kIfcTransitionCode_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcTransportElementFixedTypeEnum
{
  kIfcTransportElementFixedTypeEnum_ELEVATOR,
  kIfcTransportElementFixedTypeEnum_ESCALATOR,
  kIfcTransportElementFixedTypeEnum_MOVINGWALKWAY,
  kIfcTransportElementFixedTypeEnum_CRANEWAY,
  kIfcTransportElementFixedTypeEnum_LIFTINGGEAR,
  kIfcTransportElementFixedTypeEnum_HAULINGGEAR,
  kIfcTransportElementFixedTypeEnum_USERDEFINED,
  kIfcTransportElementFixedTypeEnum_NOTDEFINED,
  kIfcTransportElementFixedTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcTransportElementFixedTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTransportElementFixedTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcTransportElementFixedTypeEnum& getUnset<OdIfc4x3_rc4::IfcTransportElementFixedTypeEnum>() { static OdIfc4x3_rc4::IfcTransportElementFixedTypeEnum nullEnum = OdIfc4x3_rc4::kIfcTransportElementFixedTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcTransportElementNonFixedTypeEnum
{
  kIfcTransportElementNonFixedTypeEnum_VEHICLE,
  kIfcTransportElementNonFixedTypeEnum_VEHICLETRACKED,
  kIfcTransportElementNonFixedTypeEnum_ROLLINGSTOCK,
  kIfcTransportElementNonFixedTypeEnum_VEHICLEWHEELED,
  kIfcTransportElementNonFixedTypeEnum_VEHICLEAIR,
  kIfcTransportElementNonFixedTypeEnum_CARGO,
  kIfcTransportElementNonFixedTypeEnum_VEHICLEMARINE,
  kIfcTransportElementNonFixedTypeEnum_USERDEFINED,
  kIfcTransportElementNonFixedTypeEnum_NOTDEFINED,
  kIfcTransportElementNonFixedTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcTransportElementNonFixedTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTransportElementNonFixedTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcTransportElementNonFixedTypeEnum& getUnset<OdIfc4x3_rc4::IfcTransportElementNonFixedTypeEnum>() { static OdIfc4x3_rc4::IfcTransportElementNonFixedTypeEnum nullEnum = OdIfc4x3_rc4::kIfcTransportElementNonFixedTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcTrimmingPreference
{
  kIfcTrimmingPreference_CARTESIAN,
  kIfcTrimmingPreference_PARAMETER,
  kIfcTrimmingPreference_UNSPECIFIED,
  kIfcTrimmingPreference_unset
};

class IFC4X3_RC4_EXPORT IfcTrimmingPreferenceTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTrimmingPreferenceTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcTrimmingPreference& getUnset<OdIfc4x3_rc4::IfcTrimmingPreference>() { static OdIfc4x3_rc4::IfcTrimmingPreference nullEnum = OdIfc4x3_rc4::kIfcTrimmingPreference_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcTubeBundleTypeEnum
{
  kIfcTubeBundleTypeEnum_FINNED,
  kIfcTubeBundleTypeEnum_USERDEFINED,
  kIfcTubeBundleTypeEnum_NOTDEFINED,
  kIfcTubeBundleTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcTubeBundleTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTubeBundleTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcTubeBundleTypeEnum& getUnset<OdIfc4x3_rc4::IfcTubeBundleTypeEnum>() { static OdIfc4x3_rc4::IfcTubeBundleTypeEnum nullEnum = OdIfc4x3_rc4::kIfcTubeBundleTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcUnitEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcUnitEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcUnitEnum& getUnset<OdIfc4x3_rc4::IfcUnitEnum>() { static OdIfc4x3_rc4::IfcUnitEnum nullEnum = OdIfc4x3_rc4::kIfcUnitEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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
  kIfcUnitaryControlElementTypeEnum_COMBINED,
  kIfcUnitaryControlElementTypeEnum_BASESTATIONCONTROLLER,
  kIfcUnitaryControlElementTypeEnum_USERDEFINED,
  kIfcUnitaryControlElementTypeEnum_NOTDEFINED,
  kIfcUnitaryControlElementTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcUnitaryControlElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcUnitaryControlElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcUnitaryControlElementTypeEnum& getUnset<OdIfc4x3_rc4::IfcUnitaryControlElementTypeEnum>() { static OdIfc4x3_rc4::IfcUnitaryControlElementTypeEnum nullEnum = OdIfc4x3_rc4::kIfcUnitaryControlElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcUnitaryEquipmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcUnitaryEquipmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcUnitaryEquipmentTypeEnum& getUnset<OdIfc4x3_rc4::IfcUnitaryEquipmentTypeEnum>() { static OdIfc4x3_rc4::IfcUnitaryEquipmentTypeEnum nullEnum = OdIfc4x3_rc4::kIfcUnitaryEquipmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcValveTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcValveTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcValveTypeEnum& getUnset<OdIfc4x3_rc4::IfcValveTypeEnum>() { static OdIfc4x3_rc4::IfcValveTypeEnum nullEnum = OdIfc4x3_rc4::kIfcValveTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcVibrationDamperTypeEnum
{
  kIfcVibrationDamperTypeEnum_BENDING_YIELD,
  kIfcVibrationDamperTypeEnum_SHEAR_YIELD,
  kIfcVibrationDamperTypeEnum_AXIAL_YIELD,
  kIfcVibrationDamperTypeEnum_FRICTION,
  kIfcVibrationDamperTypeEnum_VISCOUS,
  kIfcVibrationDamperTypeEnum_RUBBER,
  kIfcVibrationDamperTypeEnum_USERDEFINED,
  kIfcVibrationDamperTypeEnum_NOTDEFINED,
  kIfcVibrationDamperTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcVibrationDamperTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcVibrationDamperTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcVibrationDamperTypeEnum& getUnset<OdIfc4x3_rc4::IfcVibrationDamperTypeEnum>() { static OdIfc4x3_rc4::IfcVibrationDamperTypeEnum nullEnum = OdIfc4x3_rc4::kIfcVibrationDamperTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcVibrationIsolatorTypeEnum
{
  kIfcVibrationIsolatorTypeEnum_COMPRESSION,
  kIfcVibrationIsolatorTypeEnum_SPRING,
  kIfcVibrationIsolatorTypeEnum_BASE,
  kIfcVibrationIsolatorTypeEnum_USERDEFINED,
  kIfcVibrationIsolatorTypeEnum_NOTDEFINED,
  kIfcVibrationIsolatorTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcVibrationIsolatorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcVibrationIsolatorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcVibrationIsolatorTypeEnum& getUnset<OdIfc4x3_rc4::IfcVibrationIsolatorTypeEnum>() { static OdIfc4x3_rc4::IfcVibrationIsolatorTypeEnum nullEnum = OdIfc4x3_rc4::kIfcVibrationIsolatorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcVoidingFeatureTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcVoidingFeatureTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcVoidingFeatureTypeEnum& getUnset<OdIfc4x3_rc4::IfcVoidingFeatureTypeEnum>() { static OdIfc4x3_rc4::IfcVoidingFeatureTypeEnum nullEnum = OdIfc4x3_rc4::kIfcVoidingFeatureTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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
  kIfcWallTypeEnum_RETAININGWALL,
  kIfcWallTypeEnum_WAVEWALL,
  kIfcWallTypeEnum_USERDEFINED,
  kIfcWallTypeEnum_NOTDEFINED,
  kIfcWallTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcWallTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWallTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcWallTypeEnum& getUnset<OdIfc4x3_rc4::IfcWallTypeEnum>() { static OdIfc4x3_rc4::IfcWallTypeEnum nullEnum = OdIfc4x3_rc4::kIfcWallTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcWasteTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWasteTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcWasteTerminalTypeEnum& getUnset<OdIfc4x3_rc4::IfcWasteTerminalTypeEnum>() { static OdIfc4x3_rc4::IfcWasteTerminalTypeEnum nullEnum = OdIfc4x3_rc4::kIfcWasteTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcWindowPanelOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowPanelOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcWindowPanelOperationEnum& getUnset<OdIfc4x3_rc4::IfcWindowPanelOperationEnum>() { static OdIfc4x3_rc4::IfcWindowPanelOperationEnum nullEnum = OdIfc4x3_rc4::kIfcWindowPanelOperationEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcWindowPanelPositionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowPanelPositionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcWindowPanelPositionEnum& getUnset<OdIfc4x3_rc4::IfcWindowPanelPositionEnum>() { static OdIfc4x3_rc4::IfcWindowPanelPositionEnum nullEnum = OdIfc4x3_rc4::kIfcWindowPanelPositionEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcWindowStyleConstructionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowStyleConstructionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcWindowStyleConstructionEnum& getUnset<OdIfc4x3_rc4::IfcWindowStyleConstructionEnum>() { static OdIfc4x3_rc4::IfcWindowStyleConstructionEnum nullEnum = OdIfc4x3_rc4::kIfcWindowStyleConstructionEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcWindowStyleOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowStyleOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcWindowStyleOperationEnum& getUnset<OdIfc4x3_rc4::IfcWindowStyleOperationEnum>() { static OdIfc4x3_rc4::IfcWindowStyleOperationEnum nullEnum = OdIfc4x3_rc4::kIfcWindowStyleOperationEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcWindowTypeEnum
{
  kIfcWindowTypeEnum_WINDOW,
  kIfcWindowTypeEnum_SKYLIGHT,
  kIfcWindowTypeEnum_LIGHTDOME,
  kIfcWindowTypeEnum_USERDEFINED,
  kIfcWindowTypeEnum_NOTDEFINED,
  kIfcWindowTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcWindowTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcWindowTypeEnum& getUnset<OdIfc4x3_rc4::IfcWindowTypeEnum>() { static OdIfc4x3_rc4::IfcWindowTypeEnum nullEnum = OdIfc4x3_rc4::kIfcWindowTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
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

class IFC4X3_RC4_EXPORT IfcWindowTypePartitioningEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowTypePartitioningEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcWindowTypePartitioningEnum& getUnset<OdIfc4x3_rc4::IfcWindowTypePartitioningEnum>() { static OdIfc4x3_rc4::IfcWindowTypePartitioningEnum nullEnum = OdIfc4x3_rc4::kIfcWindowTypePartitioningEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcWorkCalendarTypeEnum
{
  kIfcWorkCalendarTypeEnum_FIRSTSHIFT,
  kIfcWorkCalendarTypeEnum_SECONDSHIFT,
  kIfcWorkCalendarTypeEnum_THIRDSHIFT,
  kIfcWorkCalendarTypeEnum_USERDEFINED,
  kIfcWorkCalendarTypeEnum_NOTDEFINED,
  kIfcWorkCalendarTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcWorkCalendarTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWorkCalendarTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcWorkCalendarTypeEnum& getUnset<OdIfc4x3_rc4::IfcWorkCalendarTypeEnum>() { static OdIfc4x3_rc4::IfcWorkCalendarTypeEnum nullEnum = OdIfc4x3_rc4::kIfcWorkCalendarTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcWorkPlanTypeEnum
{
  kIfcWorkPlanTypeEnum_ACTUAL,
  kIfcWorkPlanTypeEnum_BASELINE,
  kIfcWorkPlanTypeEnum_PLANNED,
  kIfcWorkPlanTypeEnum_USERDEFINED,
  kIfcWorkPlanTypeEnum_NOTDEFINED,
  kIfcWorkPlanTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcWorkPlanTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWorkPlanTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcWorkPlanTypeEnum& getUnset<OdIfc4x3_rc4::IfcWorkPlanTypeEnum>() { static OdIfc4x3_rc4::IfcWorkPlanTypeEnum nullEnum = OdIfc4x3_rc4::kIfcWorkPlanTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {
enum IfcWorkScheduleTypeEnum
{
  kIfcWorkScheduleTypeEnum_ACTUAL,
  kIfcWorkScheduleTypeEnum_BASELINE,
  kIfcWorkScheduleTypeEnum_PLANNED,
  kIfcWorkScheduleTypeEnum_USERDEFINED,
  kIfcWorkScheduleTypeEnum_NOTDEFINED,
  kIfcWorkScheduleTypeEnum_unset
};

class IFC4X3_RC4_EXPORT IfcWorkScheduleTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWorkScheduleTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc4x3_rc4::IfcWorkScheduleTypeEnum& getUnset<OdIfc4x3_rc4::IfcWorkScheduleTypeEnum>() { static OdIfc4x3_rc4::IfcWorkScheduleTypeEnum nullEnum = OdIfc4x3_rc4::kIfcWorkScheduleTypeEnum_unset; return nullEnum; } } }

namespace OdIfc4x3_rc4 {

} // namespace

#endif // _IFC4X3_RC4_ENUM_H

