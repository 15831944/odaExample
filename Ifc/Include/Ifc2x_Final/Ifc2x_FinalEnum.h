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

#ifndef _IFC2X_FINAL_ENUM_H
#define _IFC2X_FINAL_ENUM_H

#include "RxValue.h"
#include "daiEnum.h"
#include "Ifc2x_FinalBuildOption.h"

namespace OdIfc2x_final {

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

class IFC2X_FINAL_EXPORT IfcRoleEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRoleEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcRoleEnum& getUnset<OdIfc2x_final::IfcRoleEnum>() { static OdIfc2x_final::IfcRoleEnum nullEnum = OdIfc2x_final::kIfcRoleEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcAddressTypeEnum
{
  kIfcAddressTypeEnum_OFFICE,
  kIfcAddressTypeEnum_SITE,
  kIfcAddressTypeEnum_HOME,
  kIfcAddressTypeEnum_DISTRIBUTIONPOINT,
  kIfcAddressTypeEnum_USERDEFINED,
  kIfcAddressTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcAddressTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAddressTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcAddressTypeEnum& getUnset<OdIfc2x_final::IfcAddressTypeEnum>() { static OdIfc2x_final::IfcAddressTypeEnum nullEnum = OdIfc2x_final::kIfcAddressTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcAheadOrBehind
{
  kIfcAheadOrBehind_AHEAD,
  kIfcAheadOrBehind_BEHIND,
  kIfcAheadOrBehind_unset
};

class IFC2X_FINAL_EXPORT IfcAheadOrBehindTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAheadOrBehindTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcAheadOrBehind& getUnset<OdIfc2x_final::IfcAheadOrBehind>() { static OdIfc2x_final::IfcAheadOrBehind nullEnum = OdIfc2x_final::kIfcAheadOrBehind_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcDocumentConfidentialityEnum
{
  kIfcDocumentConfidentialityEnum_PUBLIC,
  kIfcDocumentConfidentialityEnum_RESTRICTED,
  kIfcDocumentConfidentialityEnum_CONFIDENTIAL,
  kIfcDocumentConfidentialityEnum_PERSONAL,
  kIfcDocumentConfidentialityEnum_NOTDEFINED,
  kIfcDocumentConfidentialityEnum_unset
};

class IFC2X_FINAL_EXPORT IfcDocumentConfidentialityEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDocumentConfidentialityEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcDocumentConfidentialityEnum& getUnset<OdIfc2x_final::IfcDocumentConfidentialityEnum>() { static OdIfc2x_final::IfcDocumentConfidentialityEnum nullEnum = OdIfc2x_final::kIfcDocumentConfidentialityEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcDocumentStatusEnum
{
  kIfcDocumentStatusEnum_DRAFT,
  kIfcDocumentStatusEnum_FINALDRAFT,
  kIfcDocumentStatusEnum_FINAL,
  kIfcDocumentStatusEnum_REVISION,
  kIfcDocumentStatusEnum_NOTDEFINED,
  kIfcDocumentStatusEnum_unset
};

class IFC2X_FINAL_EXPORT IfcDocumentStatusEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDocumentStatusEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcDocumentStatusEnum& getUnset<OdIfc2x_final::IfcDocumentStatusEnum>() { static OdIfc2x_final::IfcDocumentStatusEnum nullEnum = OdIfc2x_final::kIfcDocumentStatusEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcBooleanOperator
{
  kIfcBooleanOperator_UNION,
  kIfcBooleanOperator_INTERSECTION,
  kIfcBooleanOperator_DIFFERENCE,
  kIfcBooleanOperator_unset
};

class IFC2X_FINAL_EXPORT IfcBooleanOperatorTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBooleanOperatorTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcBooleanOperator& getUnset<OdIfc2x_final::IfcBooleanOperator>() { static OdIfc2x_final::IfcBooleanOperator nullEnum = OdIfc2x_final::kIfcBooleanOperator_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcTransitionCode
{
  kIfcTransitionCode_DISCONTINUOUS,
  kIfcTransitionCode_CONTINUOUS,
  kIfcTransitionCode_CONTSAMEGRADIENT,
  kIfcTransitionCode_CONTSAMEGRADIENTSAMECURVATURE,
  kIfcTransitionCode_unset
};

class IFC2X_FINAL_EXPORT IfcTransitionCodeTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTransitionCodeTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcTransitionCode& getUnset<OdIfc2x_final::IfcTransitionCode>() { static OdIfc2x_final::IfcTransitionCode nullEnum = OdIfc2x_final::kIfcTransitionCode_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcTrimmingPreference
{
  kIfcTrimmingPreference_CARTESIAN,
  kIfcTrimmingPreference_PARAMETER,
  kIfcTrimmingPreference_UNSPECIFIED,
  kIfcTrimmingPreference_unset
};

class IFC2X_FINAL_EXPORT IfcTrimmingPreferenceTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTrimmingPreferenceTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcTrimmingPreference& getUnset<OdIfc2x_final::IfcTrimmingPreference>() { static OdIfc2x_final::IfcTrimmingPreference nullEnum = OdIfc2x_final::kIfcTrimmingPreference_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcLayerSetDirectionEnum
{
  kIfcLayerSetDirectionEnum_AXIS1,
  kIfcLayerSetDirectionEnum_AXIS2,
  kIfcLayerSetDirectionEnum_AXIS3,
  kIfcLayerSetDirectionEnum_unset
};

class IFC2X_FINAL_EXPORT IfcLayerSetDirectionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLayerSetDirectionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcLayerSetDirectionEnum& getUnset<OdIfc2x_final::IfcLayerSetDirectionEnum>() { static OdIfc2x_final::IfcLayerSetDirectionEnum nullEnum = OdIfc2x_final::kIfcLayerSetDirectionEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcDirectionSenseEnum
{
  kIfcDirectionSenseEnum_POSITIVE,
  kIfcDirectionSenseEnum_NEGATIVE,
  kIfcDirectionSenseEnum_unset
};

class IFC2X_FINAL_EXPORT IfcDirectionSenseEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDirectionSenseEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcDirectionSenseEnum& getUnset<OdIfc2x_final::IfcDirectionSenseEnum>() { static OdIfc2x_final::IfcDirectionSenseEnum nullEnum = OdIfc2x_final::kIfcDirectionSenseEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
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

class IFC2X_FINAL_EXPORT IfcSIPrefixTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSIPrefixTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcSIPrefix& getUnset<OdIfc2x_final::IfcSIPrefix>() { static OdIfc2x_final::IfcSIPrefix nullEnum = OdIfc2x_final::kIfcSIPrefix_unset; return nullEnum; } } }

namespace OdIfc2x_final {
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

class IFC2X_FINAL_EXPORT IfcSIUnitNameTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSIUnitNameTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcSIUnitName& getUnset<OdIfc2x_final::IfcSIUnitName>() { static OdIfc2x_final::IfcSIUnitName nullEnum = OdIfc2x_final::kIfcSIUnitName_unset; return nullEnum; } } }

namespace OdIfc2x_final {
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

class IFC2X_FINAL_EXPORT IfcUnitEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcUnitEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcUnitEnum& getUnset<OdIfc2x_final::IfcUnitEnum>() { static OdIfc2x_final::IfcUnitEnum nullEnum = OdIfc2x_final::kIfcUnitEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
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
  kIfcDerivedUnitEnum_MOMENTORINERTIAUNIT,
  kIfcDerivedUnitEnum_LINEARMOMENTUNIT,
  kIfcDerivedUnitEnum_LINEARFORCEUNIT,
  kIfcDerivedUnitEnum_PLANARFORCEUNIT,
  kIfcDerivedUnitEnum_MODULUSOFELASTICITYUNIT,
  kIfcDerivedUnitEnum_SHEARMODULUSUNIT,
  kIfcDerivedUnitEnum_LINEARSTIFFNESSUNIT,
  kIfcDerivedUnitEnum_ROTATIONALSTIFFNESSUNIT,
  kIfcDerivedUnitEnum_MODULUSOFSUBGRADEREACTIONUNIT,
  kIfcDerivedUnitEnum_ACCELERATIONUNIT,
  kIfcDerivedUnitEnum_USERDEFINED,
  kIfcDerivedUnitEnum_unset
};

class IFC2X_FINAL_EXPORT IfcDerivedUnitEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDerivedUnitEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcDerivedUnitEnum& getUnset<OdIfc2x_final::IfcDerivedUnitEnum>() { static OdIfc2x_final::IfcDerivedUnitEnum nullEnum = OdIfc2x_final::kIfcDerivedUnitEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
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

class IFC2X_FINAL_EXPORT IfcCurrencyEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCurrencyEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcCurrencyEnum& getUnset<OdIfc2x_final::IfcCurrencyEnum>() { static OdIfc2x_final::IfcCurrencyEnum nullEnum = OdIfc2x_final::kIfcCurrencyEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcProfileTypeEnum
{
  kIfcProfileTypeEnum_CURVE,
  kIfcProfileTypeEnum_AREA,
  kIfcProfileTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcProfileTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcProfileTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcProfileTypeEnum& getUnset<OdIfc2x_final::IfcProfileTypeEnum>() { static OdIfc2x_final::IfcProfileTypeEnum nullEnum = OdIfc2x_final::kIfcProfileTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcStateEnum
{
  kIfcStateEnum_READWRITE,
  kIfcStateEnum_READONLY,
  kIfcStateEnum_LOCKED,
  kIfcStateEnum_READWRITELOCKED,
  kIfcStateEnum_READONLYLOCKED,
  kIfcStateEnum_unset
};

class IFC2X_FINAL_EXPORT IfcStateEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStateEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcStateEnum& getUnset<OdIfc2x_final::IfcStateEnum>() { static OdIfc2x_final::IfcStateEnum nullEnum = OdIfc2x_final::kIfcStateEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
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

class IFC2X_FINAL_EXPORT IfcChangeActionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcChangeActionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcChangeActionEnum& getUnset<OdIfc2x_final::IfcChangeActionEnum>() { static OdIfc2x_final::IfcChangeActionEnum nullEnum = OdIfc2x_final::kIfcChangeActionEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcSequenceEnum
{
  kIfcSequenceEnum_START_START,
  kIfcSequenceEnum_START_FINISH,
  kIfcSequenceEnum_FINISH_START,
  kIfcSequenceEnum_FINISH_FINISH,
  kIfcSequenceEnum_NOTDEFINED,
  kIfcSequenceEnum_unset
};

class IFC2X_FINAL_EXPORT IfcSequenceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSequenceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcSequenceEnum& getUnset<OdIfc2x_final::IfcSequenceEnum>() { static OdIfc2x_final::IfcSequenceEnum nullEnum = OdIfc2x_final::kIfcSequenceEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
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

class IFC2X_FINAL_EXPORT IfcResourceConsumptionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcResourceConsumptionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcResourceConsumptionEnum& getUnset<OdIfc2x_final::IfcResourceConsumptionEnum>() { static OdIfc2x_final::IfcResourceConsumptionEnum nullEnum = OdIfc2x_final::kIfcResourceConsumptionEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
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

class IFC2X_FINAL_EXPORT IfcObjectTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcObjectTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcObjectTypeEnum& getUnset<OdIfc2x_final::IfcObjectTypeEnum>() { static OdIfc2x_final::IfcObjectTypeEnum nullEnum = OdIfc2x_final::kIfcObjectTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcInternalOrExternalEnum
{
  kIfcInternalOrExternalEnum_INTERNAL,
  kIfcInternalOrExternalEnum_EXTERNAL,
  kIfcInternalOrExternalEnum_NOTDEFINED,
  kIfcInternalOrExternalEnum_unset
};

class IFC2X_FINAL_EXPORT IfcInternalOrExternalEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcInternalOrExternalEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcInternalOrExternalEnum& getUnset<OdIfc2x_final::IfcInternalOrExternalEnum>() { static OdIfc2x_final::IfcInternalOrExternalEnum nullEnum = OdIfc2x_final::kIfcInternalOrExternalEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcPhysicalOrVirtualEnum
{
  kIfcPhysicalOrVirtualEnum_PHYSICAL,
  kIfcPhysicalOrVirtualEnum_VIRTUAL,
  kIfcPhysicalOrVirtualEnum_NOTDEFINED,
  kIfcPhysicalOrVirtualEnum_unset
};

class IFC2X_FINAL_EXPORT IfcPhysicalOrVirtualEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPhysicalOrVirtualEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcPhysicalOrVirtualEnum& getUnset<OdIfc2x_final::IfcPhysicalOrVirtualEnum>() { static OdIfc2x_final::IfcPhysicalOrVirtualEnum nullEnum = OdIfc2x_final::kIfcPhysicalOrVirtualEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcElementCompositionEnum
{
  kIfcElementCompositionEnum_COMPLEX,
  kIfcElementCompositionEnum_ELEMENT,
  kIfcElementCompositionEnum_PARTIAL,
  kIfcElementCompositionEnum_unset
};

class IFC2X_FINAL_EXPORT IfcElementCompositionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElementCompositionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcElementCompositionEnum& getUnset<OdIfc2x_final::IfcElementCompositionEnum>() { static OdIfc2x_final::IfcElementCompositionEnum nullEnum = OdIfc2x_final::kIfcElementCompositionEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcTransportElementTypeEnum
{
  kIfcTransportElementTypeEnum_ELEVATOR,
  kIfcTransportElementTypeEnum_ESCALATOR,
  kIfcTransportElementTypeEnum_MOVINGWALKWAY,
  kIfcTransportElementTypeEnum_USERDEFINED,
  kIfcTransportElementTypeEnum_NOTDEFINED,
  kIfcTransportElementTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcTransportElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTransportElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcTransportElementTypeEnum& getUnset<OdIfc2x_final::IfcTransportElementTypeEnum>() { static OdIfc2x_final::IfcTransportElementTypeEnum nullEnum = OdIfc2x_final::kIfcTransportElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcConnectionTypeEnum
{
  kIfcConnectionTypeEnum_ATPATH,
  kIfcConnectionTypeEnum_ATSTART,
  kIfcConnectionTypeEnum_ATEND,
  kIfcConnectionTypeEnum_NOTDEFINED,
  kIfcConnectionTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcConnectionTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcConnectionTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcConnectionTypeEnum& getUnset<OdIfc2x_final::IfcConnectionTypeEnum>() { static OdIfc2x_final::IfcConnectionTypeEnum nullEnum = OdIfc2x_final::kIfcConnectionTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcCoveringTypeEnum
{
  kIfcCoveringTypeEnum_CEILING,
  kIfcCoveringTypeEnum_FLOORING,
  kIfcCoveringTypeEnum_CLADDING,
  kIfcCoveringTypeEnum_ROOFING,
  kIfcCoveringTypeEnum_USERDEFINED,
  kIfcCoveringTypeEnum_NOTDEFINED,
  kIfcCoveringTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcCoveringTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCoveringTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcCoveringTypeEnum& getUnset<OdIfc2x_final::IfcCoveringTypeEnum>() { static OdIfc2x_final::IfcCoveringTypeEnum nullEnum = OdIfc2x_final::kIfcCoveringTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcSlabTypeEnum
{
  kIfcSlabTypeEnum_FLOOR,
  kIfcSlabTypeEnum_ROOF,
  kIfcSlabTypeEnum_LANDING,
  kIfcSlabTypeEnum_USERDEFINED,
  kIfcSlabTypeEnum_NOTDEFINED,
  kIfcSlabTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcSlabTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSlabTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcSlabTypeEnum& getUnset<OdIfc2x_final::IfcSlabTypeEnum>() { static OdIfc2x_final::IfcSlabTypeEnum nullEnum = OdIfc2x_final::kIfcSlabTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
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

class IFC2X_FINAL_EXPORT IfcRoofTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRoofTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcRoofTypeEnum& getUnset<OdIfc2x_final::IfcRoofTypeEnum>() { static OdIfc2x_final::IfcRoofTypeEnum nullEnum = OdIfc2x_final::kIfcRoofTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
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

class IFC2X_FINAL_EXPORT IfcStairTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcStairTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcStairTypeEnum& getUnset<OdIfc2x_final::IfcStairTypeEnum>() { static OdIfc2x_final::IfcStairTypeEnum nullEnum = OdIfc2x_final::kIfcStairTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
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

class IFC2X_FINAL_EXPORT IfcRampTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRampTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcRampTypeEnum& getUnset<OdIfc2x_final::IfcRampTypeEnum>() { static OdIfc2x_final::IfcRampTypeEnum nullEnum = OdIfc2x_final::kIfcRampTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
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

class IFC2X_FINAL_EXPORT IfcDoorStyleOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorStyleOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcDoorStyleOperationEnum& getUnset<OdIfc2x_final::IfcDoorStyleOperationEnum>() { static OdIfc2x_final::IfcDoorStyleOperationEnum nullEnum = OdIfc2x_final::kIfcDoorStyleOperationEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
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

class IFC2X_FINAL_EXPORT IfcDoorStyleConstructionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorStyleConstructionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcDoorStyleConstructionEnum& getUnset<OdIfc2x_final::IfcDoorStyleConstructionEnum>() { static OdIfc2x_final::IfcDoorStyleConstructionEnum nullEnum = OdIfc2x_final::kIfcDoorStyleConstructionEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
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

class IFC2X_FINAL_EXPORT IfcWindowStyleConstructionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowStyleConstructionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcWindowStyleConstructionEnum& getUnset<OdIfc2x_final::IfcWindowStyleConstructionEnum>() { static OdIfc2x_final::IfcWindowStyleConstructionEnum nullEnum = OdIfc2x_final::kIfcWindowStyleConstructionEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
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

class IFC2X_FINAL_EXPORT IfcWindowStyleOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowStyleOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcWindowStyleOperationEnum& getUnset<OdIfc2x_final::IfcWindowStyleOperationEnum>() { static OdIfc2x_final::IfcWindowStyleOperationEnum nullEnum = OdIfc2x_final::kIfcWindowStyleOperationEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
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

class IFC2X_FINAL_EXPORT IfcDoorPanelOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorPanelOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcDoorPanelOperationEnum& getUnset<OdIfc2x_final::IfcDoorPanelOperationEnum>() { static OdIfc2x_final::IfcDoorPanelOperationEnum nullEnum = OdIfc2x_final::kIfcDoorPanelOperationEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcDoorPanelPositionEnum
{
  kIfcDoorPanelPositionEnum_LEFT,
  kIfcDoorPanelPositionEnum_MIDDLE,
  kIfcDoorPanelPositionEnum_RIGHT,
  kIfcDoorPanelPositionEnum_NOTDEFINED,
  kIfcDoorPanelPositionEnum_unset
};

class IFC2X_FINAL_EXPORT IfcDoorPanelPositionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDoorPanelPositionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcDoorPanelPositionEnum& getUnset<OdIfc2x_final::IfcDoorPanelPositionEnum>() { static OdIfc2x_final::IfcDoorPanelPositionEnum nullEnum = OdIfc2x_final::kIfcDoorPanelPositionEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
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

class IFC2X_FINAL_EXPORT IfcWindowPanelOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowPanelOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcWindowPanelOperationEnum& getUnset<OdIfc2x_final::IfcWindowPanelOperationEnum>() { static OdIfc2x_final::IfcWindowPanelOperationEnum nullEnum = OdIfc2x_final::kIfcWindowPanelOperationEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
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

class IFC2X_FINAL_EXPORT IfcWindowPanelPositionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWindowPanelPositionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcWindowPanelPositionEnum& getUnset<OdIfc2x_final::IfcWindowPanelPositionEnum>() { static OdIfc2x_final::IfcWindowPanelPositionEnum nullEnum = OdIfc2x_final::kIfcWindowPanelPositionEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcApprovalStatusEnum
{
  kIfcApprovalStatusEnum_APPROVED,
  kIfcApprovalStatusEnum_PROCESSED,
  kIfcApprovalStatusEnum_ONHOLD,
  kIfcApprovalStatusEnum_SUBMITTED,
  kIfcApprovalStatusEnum_USERDEFINED,
  kIfcApprovalStatusEnum_NOTDEFINED,
  kIfcApprovalStatusEnum_unset
};

class IFC2X_FINAL_EXPORT IfcApprovalStatusEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcApprovalStatusEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcApprovalStatusEnum& getUnset<OdIfc2x_final::IfcApprovalStatusEnum>() { static OdIfc2x_final::IfcApprovalStatusEnum nullEnum = OdIfc2x_final::kIfcApprovalStatusEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcBenchmarkEnum
{
  kIfcBenchmarkEnum_GREATERTHAN,
  kIfcBenchmarkEnum_GREATERTHANOREQUALTO,
  kIfcBenchmarkEnum_LESSTHAN,
  kIfcBenchmarkEnum_LESSTHANOREQUALTO,
  kIfcBenchmarkEnum_EQUALTO,
  kIfcBenchmarkEnum_NOTEQUALTO,
  kIfcBenchmarkEnum_TARGETWITHTOLERANCE,
  kIfcBenchmarkEnum_RANGE,
  kIfcBenchmarkEnum_USERDEFINED,
  kIfcBenchmarkEnum_NOTDEFINED,
  kIfcBenchmarkEnum_unset
};

class IFC2X_FINAL_EXPORT IfcBenchmarkEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBenchmarkEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcBenchmarkEnum& getUnset<OdIfc2x_final::IfcBenchmarkEnum>() { static OdIfc2x_final::IfcBenchmarkEnum nullEnum = OdIfc2x_final::kIfcBenchmarkEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcMetricDataEnum
{
  kIfcMetricDataEnum_SCALAR,
  kIfcMetricDataEnum_VECTOR,
  kIfcMetricDataEnum_TIMESERIES,
  kIfcMetricDataEnum_TABLE,
  kIfcMetricDataEnum_GRAPH,
  kIfcMetricDataEnum_DISTRIBUTION,
  kIfcMetricDataEnum_USERDEFINED,
  kIfcMetricDataEnum_NOTDEFINED,
  kIfcMetricDataEnum_unset
};

class IFC2X_FINAL_EXPORT IfcMetricDataEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMetricDataEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcMetricDataEnum& getUnset<OdIfc2x_final::IfcMetricDataEnum>() { static OdIfc2x_final::IfcMetricDataEnum nullEnum = OdIfc2x_final::kIfcMetricDataEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcObjectiveEnum
{
  kIfcObjectiveEnum_CODECOMPLIANCE,
  kIfcObjectiveEnum_DESIGNINTENT,
  kIfcObjectiveEnum_USERDEFINED,
  kIfcObjectiveEnum_NOTDEFINED,
  kIfcObjectiveEnum_unset
};

class IFC2X_FINAL_EXPORT IfcObjectiveEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcObjectiveEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcObjectiveEnum& getUnset<OdIfc2x_final::IfcObjectiveEnum>() { static OdIfc2x_final::IfcObjectiveEnum nullEnum = OdIfc2x_final::kIfcObjectiveEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcConstraintEnum
{
  kIfcConstraintEnum_HARD,
  kIfcConstraintEnum_SOFT,
  kIfcConstraintEnum_ADVISORY,
  kIfcConstraintEnum_USERDEFINED,
  kIfcConstraintEnum_NOTDEFINED,
  kIfcConstraintEnum_unset
};

class IFC2X_FINAL_EXPORT IfcConstraintEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcConstraintEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcConstraintEnum& getUnset<OdIfc2x_final::IfcConstraintEnum>() { static OdIfc2x_final::IfcConstraintEnum nullEnum = OdIfc2x_final::kIfcConstraintEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcAggregatorEnum
{
  kIfcAggregatorEnum_LOGICALAND,
  kIfcAggregatorEnum_LOGICALOR,
  kIfcAggregatorEnum_LOGICALXOR,
  kIfcAggregatorEnum_LOGICALNOT,
  kIfcAggregatorEnum_unset
};

class IFC2X_FINAL_EXPORT IfcAggregatorEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAggregatorEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcAggregatorEnum& getUnset<OdIfc2x_final::IfcAggregatorEnum>() { static OdIfc2x_final::IfcAggregatorEnum nullEnum = OdIfc2x_final::kIfcAggregatorEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcConstraintIntentEnum
{
  kIfcConstraintIntentEnum_RATIONALE,
  kIfcConstraintIntentEnum_EXPECTEDPERFORMANCE,
  kIfcConstraintIntentEnum_USERDEFINED,
  kIfcConstraintIntentEnum_NOTDEFINED,
  kIfcConstraintIntentEnum_unset
};

class IFC2X_FINAL_EXPORT IfcConstraintIntentEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcConstraintIntentEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcConstraintIntentEnum& getUnset<OdIfc2x_final::IfcConstraintIntentEnum>() { static OdIfc2x_final::IfcConstraintIntentEnum nullEnum = OdIfc2x_final::kIfcConstraintIntentEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcCostModifierBasisEnum
{
  kIfcCostModifierBasisEnum_RUNNING,
  kIfcCostModifierBasisEnum_STATIC,
  kIfcCostModifierBasisEnum_unset
};

class IFC2X_FINAL_EXPORT IfcCostModifierBasisEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCostModifierBasisEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcCostModifierBasisEnum& getUnset<OdIfc2x_final::IfcCostModifierBasisEnum>() { static OdIfc2x_final::IfcCostModifierBasisEnum nullEnum = OdIfc2x_final::kIfcCostModifierBasisEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcCostOperatorEnum
{
  kIfcCostOperatorEnum_ADDVALUE,
  kIfcCostOperatorEnum_SUBTRACTVALUE,
  kIfcCostOperatorEnum_MULTIPLYVALUE,
  kIfcCostOperatorEnum_unset
};

class IFC2X_FINAL_EXPORT IfcCostOperatorEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCostOperatorEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcCostOperatorEnum& getUnset<OdIfc2x_final::IfcCostOperatorEnum>() { static OdIfc2x_final::IfcCostOperatorEnum nullEnum = OdIfc2x_final::kIfcCostOperatorEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcQuantityRoundOffBasisEnum
{
  kIfcQuantityRoundOffBasisEnum_ROUNDTOCLOSEST,
  kIfcQuantityRoundOffBasisEnum_ROUNDTUP,
  kIfcQuantityRoundOffBasisEnum_ROUNDTDOWN,
  kIfcQuantityRoundOffBasisEnum_NONE,
  kIfcQuantityRoundOffBasisEnum_unset
};

class IFC2X_FINAL_EXPORT IfcQuantityRoundOffBasisEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcQuantityRoundOffBasisEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcQuantityRoundOffBasisEnum& getUnset<OdIfc2x_final::IfcQuantityRoundOffBasisEnum>() { static OdIfc2x_final::IfcQuantityRoundOffBasisEnum nullEnum = OdIfc2x_final::kIfcQuantityRoundOffBasisEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcSurfaceSideEnum
{
  kIfcSurfaceSideEnum_POSITIVE,
  kIfcSurfaceSideEnum_NEGATIVE,
  kIfcSurfaceSideEnum_BOTH,
  kIfcSurfaceSideEnum_unset
};

class IFC2X_FINAL_EXPORT IfcSurfaceSideEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSurfaceSideEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcSurfaceSideEnum& getUnset<OdIfc2x_final::IfcSurfaceSideEnum>() { static OdIfc2x_final::IfcSurfaceSideEnum nullEnum = OdIfc2x_final::kIfcSurfaceSideEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcTaskStatusEnum
{
  kIfcTaskStatusEnum_COMPLETED,
  kIfcTaskStatusEnum_NOTYETSTARTED,
  kIfcTaskStatusEnum_STARTED,
  kIfcTaskStatusEnum_USERDEFINED,
  kIfcTaskStatusEnum_NOTDEFINED,
  kIfcTaskStatusEnum_unset
};

class IFC2X_FINAL_EXPORT IfcTaskStatusEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTaskStatusEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcTaskStatusEnum& getUnset<OdIfc2x_final::IfcTaskStatusEnum>() { static OdIfc2x_final::IfcTaskStatusEnum nullEnum = OdIfc2x_final::kIfcTaskStatusEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcTaskMilestoneEnum
{
  kIfcTaskMilestoneEnum_CONTRACTMILESTONE,
  kIfcTaskMilestoneEnum_CUSTOMERMILESTONE,
  kIfcTaskMilestoneEnum_FINANCIALMILESTONE,
  kIfcTaskMilestoneEnum_FINISHMILESTONE,
  kIfcTaskMilestoneEnum_MANAGEMENTMILESTONE,
  kIfcTaskMilestoneEnum_SCHEDULEDMILESTONE,
  kIfcTaskMilestoneEnum_STARTMILESTONE,
  kIfcTaskMilestoneEnum_SUPPLYMILESTONE,
  kIfcTaskMilestoneEnum_USERDEFINED,
  kIfcTaskMilestoneEnum_NOTDEFINED,
  kIfcTaskMilestoneEnum_unset
};

class IFC2X_FINAL_EXPORT IfcTaskMilestoneEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcTaskMilestoneEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcTaskMilestoneEnum& getUnset<OdIfc2x_final::IfcTaskMilestoneEnum>() { static OdIfc2x_final::IfcTaskMilestoneEnum nullEnum = OdIfc2x_final::kIfcTaskMilestoneEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcWorkControlTypeEnum
{
  kIfcWorkControlTypeEnum_ACTUAL,
  kIfcWorkControlTypeEnum_BASELINE,
  kIfcWorkControlTypeEnum_PLANNED,
  kIfcWorkControlTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcWorkControlTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWorkControlTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcWorkControlTypeEnum& getUnset<OdIfc2x_final::IfcWorkControlTypeEnum>() { static OdIfc2x_final::IfcWorkControlTypeEnum nullEnum = OdIfc2x_final::kIfcWorkControlTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcMultiplierOrDivider
{
  kIfcMultiplierOrDivider_MULTIPLIER,
  kIfcMultiplierOrDivider_DIVIDER,
  kIfcMultiplierOrDivider_unset
};

class IFC2X_FINAL_EXPORT IfcMultiplierOrDividerTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMultiplierOrDividerTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcMultiplierOrDivider& getUnset<OdIfc2x_final::IfcMultiplierOrDivider>() { static OdIfc2x_final::IfcMultiplierOrDivider nullEnum = OdIfc2x_final::kIfcMultiplierOrDivider_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcFlowDirectionEnum
{
  kIfcFlowDirectionEnum_SOURCE,
  kIfcFlowDirectionEnum_SINK,
  kIfcFlowDirectionEnum_SOURCEANDSINK,
  kIfcFlowDirectionEnum_USERDEFINED,
  kIfcFlowDirectionEnum_NOTDEFINED,
  kIfcFlowDirectionEnum_unset
};

class IFC2X_FINAL_EXPORT IfcFlowDirectionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFlowDirectionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcFlowDirectionEnum& getUnset<OdIfc2x_final::IfcFlowDirectionEnum>() { static OdIfc2x_final::IfcFlowDirectionEnum nullEnum = OdIfc2x_final::kIfcFlowDirectionEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcPortConnectionTypeEnum
{
  kIfcPortConnectionTypeEnum_ANGLE,
  kIfcPortConnectionTypeEnum_BEADEDSLEEVE,
  kIfcPortConnectionTypeEnum_BRAZED,
  kIfcPortConnectionTypeEnum_COMPRESSION,
  kIfcPortConnectionTypeEnum_CRIMP,
  kIfcPortConnectionTypeEnum_DRAWBAND,
  kIfcPortConnectionTypeEnum_DRIVESLIP,
  kIfcPortConnectionTypeEnum_FLANGED,
  kIfcPortConnectionTypeEnum_GROOVED,
  kIfcPortConnectionTypeEnum_OUTSIDESLEEVE,
  kIfcPortConnectionTypeEnum_SLIPON,
  kIfcPortConnectionTypeEnum_SOLDERED,
  kIfcPortConnectionTypeEnum_SSLIP,
  kIfcPortConnectionTypeEnum_STANDINGSEAM,
  kIfcPortConnectionTypeEnum_SWEDGE,
  kIfcPortConnectionTypeEnum_THREADED,
  kIfcPortConnectionTypeEnum_WELDED,
  kIfcPortConnectionTypeEnum_USERDEFINED,
  kIfcPortConnectionTypeEnum_NOTDEFINED,
  kIfcPortConnectionTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcPortConnectionTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPortConnectionTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcPortConnectionTypeEnum& getUnset<OdIfc2x_final::IfcPortConnectionTypeEnum>() { static OdIfc2x_final::IfcPortConnectionTypeEnum nullEnum = OdIfc2x_final::kIfcPortConnectionTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcDiscreteElementTypeEnum
{
  kIfcDiscreteElementTypeEnum_INSULATION,
  kIfcDiscreteElementTypeEnum_USERDEFINED,
  kIfcDiscreteElementTypeEnum_NOTDEFINED,
  kIfcDiscreteElementTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcDiscreteElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDiscreteElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcDiscreteElementTypeEnum& getUnset<OdIfc2x_final::IfcDiscreteElementTypeEnum>() { static OdIfc2x_final::IfcDiscreteElementTypeEnum nullEnum = OdIfc2x_final::kIfcDiscreteElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcFlowFittingTypeEnum
{
  kIfcFlowFittingTypeEnum_DUCTFITTING,
  kIfcFlowFittingTypeEnum_PIPEFITTING,
  kIfcFlowFittingTypeEnum_USERDEFINED,
  kIfcFlowFittingTypeEnum_NOTDEFINED,
  kIfcFlowFittingTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcFlowFittingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFlowFittingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcFlowFittingTypeEnum& getUnset<OdIfc2x_final::IfcFlowFittingTypeEnum>() { static OdIfc2x_final::IfcFlowFittingTypeEnum nullEnum = OdIfc2x_final::kIfcFlowFittingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcPrimaryFittingEnum
{
  kIfcPrimaryFittingEnum_ENTRY,
  kIfcPrimaryFittingEnum_EXIT,
  kIfcPrimaryFittingEnum_ELBOW,
  kIfcPrimaryFittingEnum_TRANSITION,
  kIfcPrimaryFittingEnum_JUNCTION,
  kIfcPrimaryFittingEnum_OBSTRUCTION,
  kIfcPrimaryFittingEnum_OTHER,
  kIfcPrimaryFittingEnum_USERDEFINED,
  kIfcPrimaryFittingEnum_NOTDEFINED,
  kIfcPrimaryFittingEnum_unset
};

class IFC2X_FINAL_EXPORT IfcPrimaryFittingEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPrimaryFittingEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcPrimaryFittingEnum& getUnset<OdIfc2x_final::IfcPrimaryFittingEnum>() { static OdIfc2x_final::IfcPrimaryFittingEnum nullEnum = OdIfc2x_final::kIfcPrimaryFittingEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcFlowSegmentTypeEnum
{
  kIfcFlowSegmentTypeEnum_DUCTSEGMENT,
  kIfcFlowSegmentTypeEnum_PIPESEGMENT,
  kIfcFlowSegmentTypeEnum_GUTTERSEGMENT,
  kIfcFlowSegmentTypeEnum_USERDEFINED,
  kIfcFlowSegmentTypeEnum_NOTDEFINED,
  kIfcFlowSegmentTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcFlowSegmentTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFlowSegmentTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcFlowSegmentTypeEnum& getUnset<OdIfc2x_final::IfcFlowSegmentTypeEnum>() { static OdIfc2x_final::IfcFlowSegmentTypeEnum nullEnum = OdIfc2x_final::kIfcFlowSegmentTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcAirFlowTypeEnum
{
  kIfcAirFlowTypeEnum_SUPPLYAIR,
  kIfcAirFlowTypeEnum_RETURNAIR,
  kIfcAirFlowTypeEnum_EXHAUSTAIR,
  kIfcAirFlowTypeEnum_OTHER,
  kIfcAirFlowTypeEnum_NOTKNOWN,
  kIfcAirFlowTypeEnum_UNSET,
  kIfcAirFlowTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcAirFlowTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAirFlowTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcAirFlowTypeEnum& getUnset<OdIfc2x_final::IfcAirFlowTypeEnum>() { static OdIfc2x_final::IfcAirFlowTypeEnum nullEnum = OdIfc2x_final::kIfcAirFlowTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcAirTerminalFinishTypeEnum
{
  kIfcAirTerminalFinishTypeEnum_ANNODIZED,
  kIfcAirTerminalFinishTypeEnum_PAINTED,
  kIfcAirTerminalFinishTypeEnum_NONE,
  kIfcAirTerminalFinishTypeEnum_OTHER,
  kIfcAirTerminalFinishTypeEnum_NOTKNOWN,
  kIfcAirTerminalFinishTypeEnum_UNSET,
  kIfcAirTerminalFinishTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcAirTerminalFinishTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAirTerminalFinishTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcAirTerminalFinishTypeEnum& getUnset<OdIfc2x_final::IfcAirTerminalFinishTypeEnum>() { static OdIfc2x_final::IfcAirTerminalFinishTypeEnum nullEnum = OdIfc2x_final::kIfcAirTerminalFinishTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcAirTerminalMountingTypeEnum
{
  kIfcAirTerminalMountingTypeEnum_SURFACE,
  kIfcAirTerminalMountingTypeEnum_FLATFLUSH,
  kIfcAirTerminalMountingTypeEnum_LAYIN,
  kIfcAirTerminalMountingTypeEnum_OTHER,
  kIfcAirTerminalMountingTypeEnum_NOTKNOWN,
  kIfcAirTerminalMountingTypeEnum_UNSET,
  kIfcAirTerminalMountingTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcAirTerminalMountingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAirTerminalMountingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcAirTerminalMountingTypeEnum& getUnset<OdIfc2x_final::IfcAirTerminalMountingTypeEnum>() { static OdIfc2x_final::IfcAirTerminalMountingTypeEnum nullEnum = OdIfc2x_final::kIfcAirTerminalMountingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcAirTerminalFaceTypeEnum
{
  kIfcAirTerminalFaceTypeEnum_FOURWAYPATTERN,
  kIfcAirTerminalFaceTypeEnum_SINGLEDEFLECTION,
  kIfcAirTerminalFaceTypeEnum_DOUBLEDEFLECTION,
  kIfcAirTerminalFaceTypeEnum_SIGHTPROOF,
  kIfcAirTerminalFaceTypeEnum_EGGCRATE,
  kIfcAirTerminalFaceTypeEnum_PERFORATED,
  kIfcAirTerminalFaceTypeEnum_LOUVERED,
  kIfcAirTerminalFaceTypeEnum_OTHER,
  kIfcAirTerminalFaceTypeEnum_NOTKNOWN,
  kIfcAirTerminalFaceTypeEnum_UNSET,
  kIfcAirTerminalFaceTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcAirTerminalFaceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAirTerminalFaceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcAirTerminalFaceTypeEnum& getUnset<OdIfc2x_final::IfcAirTerminalFaceTypeEnum>() { static OdIfc2x_final::IfcAirTerminalFaceTypeEnum nullEnum = OdIfc2x_final::kIfcAirTerminalFaceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcAirTerminalCoreTypeEnum
{
  kIfcAirTerminalCoreTypeEnum_SHUTTERBLADE,
  kIfcAirTerminalCoreTypeEnum_CURVEDBLADE,
  kIfcAirTerminalCoreTypeEnum_REMOVABLE,
  kIfcAirTerminalCoreTypeEnum_REVERSIBLE,
  kIfcAirTerminalCoreTypeEnum_NONE,
  kIfcAirTerminalCoreTypeEnum_OTHER,
  kIfcAirTerminalCoreTypeEnum_NOTKNOWN,
  kIfcAirTerminalCoreTypeEnum_UNSET,
  kIfcAirTerminalCoreTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcAirTerminalCoreTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAirTerminalCoreTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcAirTerminalCoreTypeEnum& getUnset<OdIfc2x_final::IfcAirTerminalCoreTypeEnum>() { static OdIfc2x_final::IfcAirTerminalCoreTypeEnum nullEnum = OdIfc2x_final::kIfcAirTerminalCoreTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcSanitaryTerminalTypeEnum
{
  kIfcSanitaryTerminalTypeEnum_FAUCET,
  kIfcSanitaryTerminalTypeEnum_ROOFDRAIN,
  kIfcSanitaryTerminalTypeEnum_SHOWER,
  kIfcSanitaryTerminalTypeEnum_SINK,
  kIfcSanitaryTerminalTypeEnum_TOILET,
  kIfcSanitaryTerminalTypeEnum_URINAL,
  kIfcSanitaryTerminalTypeEnum_USERDEFINED,
  kIfcSanitaryTerminalTypeEnum_NOTDEFINED,
  kIfcSanitaryTerminalTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcSanitaryTerminalTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSanitaryTerminalTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcSanitaryTerminalTypeEnum& getUnset<OdIfc2x_final::IfcSanitaryTerminalTypeEnum>() { static OdIfc2x_final::IfcSanitaryTerminalTypeEnum nullEnum = OdIfc2x_final::kIfcSanitaryTerminalTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcHydronicHeaterTypeEnum
{
  kIfcHydronicHeaterTypeEnum_PANELRADIATOR,
  kIfcHydronicHeaterTypeEnum_COLUMNRADIATOR,
  kIfcHydronicHeaterTypeEnum_TUBERADIATOR,
  kIfcHydronicHeaterTypeEnum_CONVECTOR,
  kIfcHydronicHeaterTypeEnum_BASEBOARDHEATER,
  kIfcHydronicHeaterTypeEnum_FINTUBEHEATER,
  kIfcHydronicHeaterTypeEnum_OTHER,
  kIfcHydronicHeaterTypeEnum_NOTKNOWN,
  kIfcHydronicHeaterTypeEnum_UNSET,
  kIfcHydronicHeaterTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcHydronicHeaterTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcHydronicHeaterTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcHydronicHeaterTypeEnum& getUnset<OdIfc2x_final::IfcHydronicHeaterTypeEnum>() { static OdIfc2x_final::IfcHydronicHeaterTypeEnum nullEnum = OdIfc2x_final::kIfcHydronicHeaterTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcCoilTypeEnum
{
  kIfcCoilTypeEnum_PRECOOLING,
  kIfcCoilTypeEnum_COOLING,
  kIfcCoilTypeEnum_RECOOLING,
  kIfcCoilTypeEnum_PREHEATING,
  kIfcCoilTypeEnum_HEATING,
  kIfcCoilTypeEnum_REHEATING,
  kIfcCoilTypeEnum_OTHER,
  kIfcCoilTypeEnum_NOTKNOWN,
  kIfcCoilTypeEnum_UNSET,
  kIfcCoilTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcCoilTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCoilTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcCoilTypeEnum& getUnset<OdIfc2x_final::IfcCoilTypeEnum>() { static OdIfc2x_final::IfcCoilTypeEnum nullEnum = OdIfc2x_final::kIfcCoilTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcCoilFlowArrangementEnum
{
  kIfcCoilFlowArrangementEnum_COUNTERFLOW,
  kIfcCoilFlowArrangementEnum_CROSSFLOW,
  kIfcCoilFlowArrangementEnum_PARALLELFLOW,
  kIfcCoilFlowArrangementEnum_DIRECTEXPANSION,
  kIfcCoilFlowArrangementEnum_OTHER,
  kIfcCoilFlowArrangementEnum_NOTKNOWN,
  kIfcCoilFlowArrangementEnum_UNSET,
  kIfcCoilFlowArrangementEnum_unset
};

class IFC2X_FINAL_EXPORT IfcCoilFlowArrangementEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCoilFlowArrangementEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcCoilFlowArrangementEnum& getUnset<OdIfc2x_final::IfcCoilFlowArrangementEnum>() { static OdIfc2x_final::IfcCoilFlowArrangementEnum nullEnum = OdIfc2x_final::kIfcCoilFlowArrangementEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcHeatExchangerTypeEnum
{
  kIfcHeatExchangerTypeEnum_PLATE,
  kIfcHeatExchangerTypeEnum_SHELLANDTUBE,
  kIfcHeatExchangerTypeEnum_OTHER,
  kIfcHeatExchangerTypeEnum_NOTKNOWN,
  kIfcHeatExchangerTypeEnum_UNSET,
  kIfcHeatExchangerTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcHeatExchangerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcHeatExchangerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcHeatExchangerTypeEnum& getUnset<OdIfc2x_final::IfcHeatExchangerTypeEnum>() { static OdIfc2x_final::IfcHeatExchangerTypeEnum nullEnum = OdIfc2x_final::kIfcHeatExchangerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcHeatExchangerArrangementEnum
{
  kIfcHeatExchangerArrangementEnum_COUNTERFLOW,
  kIfcHeatExchangerArrangementEnum_CROSSFLOW,
  kIfcHeatExchangerArrangementEnum_PARALLELFLOW,
  kIfcHeatExchangerArrangementEnum_MULTIPASS,
  kIfcHeatExchangerArrangementEnum_OTHER,
  kIfcHeatExchangerArrangementEnum_NOTKNOWN,
  kIfcHeatExchangerArrangementEnum_UNSET,
  kIfcHeatExchangerArrangementEnum_unset
};

class IFC2X_FINAL_EXPORT IfcHeatExchangerArrangementEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcHeatExchangerArrangementEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcHeatExchangerArrangementEnum& getUnset<OdIfc2x_final::IfcHeatExchangerArrangementEnum>() { static OdIfc2x_final::IfcHeatExchangerArrangementEnum nullEnum = OdIfc2x_final::kIfcHeatExchangerArrangementEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcCoolingTowerTypeEnum
{
  kIfcCoolingTowerTypeEnum_OPENTOWER,
  kIfcCoolingTowerTypeEnum_CLOSEDTOWER,
  kIfcCoolingTowerTypeEnum_WOODFILL,
  kIfcCoolingTowerTypeEnum_CERAMIC,
  kIfcCoolingTowerTypeEnum_CROSSFLOW,
  kIfcCoolingTowerTypeEnum_OTHER,
  kIfcCoolingTowerTypeEnum_NOTKNOWN,
  kIfcCoolingTowerTypeEnum_UNSET,
  kIfcCoolingTowerTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcCoolingTowerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCoolingTowerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcCoolingTowerTypeEnum& getUnset<OdIfc2x_final::IfcCoolingTowerTypeEnum>() { static OdIfc2x_final::IfcCoolingTowerTypeEnum nullEnum = OdIfc2x_final::kIfcCoolingTowerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcChillerTypeEnum
{
  kIfcChillerTypeEnum_AIRCOOLED,
  kIfcChillerTypeEnum_WATERCOOLED,
  kIfcChillerTypeEnum_HEATRECOVERY,
  kIfcChillerTypeEnum_OTHER,
  kIfcChillerTypeEnum_NOTKNOWN,
  kIfcChillerTypeEnum_UNSET,
  kIfcChillerTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcChillerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcChillerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcChillerTypeEnum& getUnset<OdIfc2x_final::IfcChillerTypeEnum>() { static OdIfc2x_final::IfcChillerTypeEnum nullEnum = OdIfc2x_final::kIfcChillerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcBoilerTypeEnum
{
  kIfcBoilerTypeEnum_HOTWATER,
  kIfcBoilerTypeEnum_GASFIRED,
  kIfcBoilerTypeEnum_STEAM,
  kIfcBoilerTypeEnum_OTHER,
  kIfcBoilerTypeEnum_NOTKNOWN,
  kIfcBoilerTypeEnum_UNSET,
  kIfcBoilerTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcBoilerTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBoilerTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcBoilerTypeEnum& getUnset<OdIfc2x_final::IfcBoilerTypeEnum>() { static OdIfc2x_final::IfcBoilerTypeEnum nullEnum = OdIfc2x_final::kIfcBoilerTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcEnergySourceEnum
{
  kIfcEnergySourceEnum_ELECTRICITY,
  kIfcEnergySourceEnum_NATURALGAS,
  kIfcEnergySourceEnum_OIL,
  kIfcEnergySourceEnum_LIQUIFIEDPETROLEUMGAS,
  kIfcEnergySourceEnum_PROPANE,
  kIfcEnergySourceEnum_STEAM,
  kIfcEnergySourceEnum_OTHER,
  kIfcEnergySourceEnum_NOTKNOWN,
  kIfcEnergySourceEnum_UNSET,
  kIfcEnergySourceEnum_unset
};

class IFC2X_FINAL_EXPORT IfcEnergySourceEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcEnergySourceEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcEnergySourceEnum& getUnset<OdIfc2x_final::IfcEnergySourceEnum>() { static OdIfc2x_final::IfcEnergySourceEnum nullEnum = OdIfc2x_final::kIfcEnergySourceEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcCompressorTypeEnum
{
  kIfcCompressorTypeEnum_HERMETIC,
  kIfcCompressorTypeEnum_RECIPROCATING,
  kIfcCompressorTypeEnum_SCREW,
  kIfcCompressorTypeEnum_OTHER,
  kIfcCompressorTypeEnum_NOTKNOWN,
  kIfcCompressorTypeEnum_UNSET,
  kIfcCompressorTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcCompressorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCompressorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcCompressorTypeEnum& getUnset<OdIfc2x_final::IfcCompressorTypeEnum>() { static OdIfc2x_final::IfcCompressorTypeEnum nullEnum = OdIfc2x_final::kIfcCompressorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcFanPressureClassEnum
{
  kIfcFanPressureClassEnum_CLASS1,
  kIfcFanPressureClassEnum_CLASS2,
  kIfcFanPressureClassEnum_CLASS3,
  kIfcFanPressureClassEnum_CLASS4,
  kIfcFanPressureClassEnum_OTHER,
  kIfcFanPressureClassEnum_NOTKNOWN,
  kIfcFanPressureClassEnum_UNSET,
  kIfcFanPressureClassEnum_unset
};

class IFC2X_FINAL_EXPORT IfcFanPressureClassEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFanPressureClassEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcFanPressureClassEnum& getUnset<OdIfc2x_final::IfcFanPressureClassEnum>() { static OdIfc2x_final::IfcFanPressureClassEnum nullEnum = OdIfc2x_final::kIfcFanPressureClassEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcFanWheelTypeEnum
{
  kIfcFanWheelTypeEnum_FORWARDCURVED,
  kIfcFanWheelTypeEnum_BACKWARDCURVED,
  kIfcFanWheelTypeEnum_AIRFOIL,
  kIfcFanWheelTypeEnum_PROPELLER,
  kIfcFanWheelTypeEnum_VANEAXIAL,
  kIfcFanWheelTypeEnum_PLUG,
  kIfcFanWheelTypeEnum_OTHER,
  kIfcFanWheelTypeEnum_NOTKNOWN,
  kIfcFanWheelTypeEnum_UNSET,
  kIfcFanWheelTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcFanWheelTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFanWheelTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcFanWheelTypeEnum& getUnset<OdIfc2x_final::IfcFanWheelTypeEnum>() { static OdIfc2x_final::IfcFanWheelTypeEnum nullEnum = OdIfc2x_final::kIfcFanWheelTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcFanDischargeTypeEnum
{
  kIfcFanDischargeTypeEnum_DUCT,
  kIfcFanDischargeTypeEnum_SCREEN,
  kIfcFanDischargeTypeEnum_NONE,
  kIfcFanDischargeTypeEnum_OTHER,
  kIfcFanDischargeTypeEnum_NOTKNOWN,
  kIfcFanDischargeTypeEnum_UNSET,
  kIfcFanDischargeTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcFanDischargeTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFanDischargeTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcFanDischargeTypeEnum& getUnset<OdIfc2x_final::IfcFanDischargeTypeEnum>() { static OdIfc2x_final::IfcFanDischargeTypeEnum nullEnum = OdIfc2x_final::kIfcFanDischargeTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcFanArrangementEnum
{
  kIfcFanArrangementEnum_TOPHORIZONTAL,
  kIfcFanArrangementEnum_TOPANGULARDOWN,
  kIfcFanArrangementEnum_DOWNBLAST,
  kIfcFanArrangementEnum_BOTTOMANGULARDOWN,
  kIfcFanArrangementEnum_BOTTOMHORIZONTAL,
  kIfcFanArrangementEnum_BOTTOMANGULARUP,
  kIfcFanArrangementEnum_UPBLAST,
  kIfcFanArrangementEnum_TOPANGULARUP,
  kIfcFanArrangementEnum_OTHER,
  kIfcFanArrangementEnum_NOTKNOWN,
  kIfcFanArrangementEnum_UNSET,
  kIfcFanArrangementEnum_unset
};

class IFC2X_FINAL_EXPORT IfcFanArrangementEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFanArrangementEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcFanArrangementEnum& getUnset<OdIfc2x_final::IfcFanArrangementEnum>() { static OdIfc2x_final::IfcFanArrangementEnum nullEnum = OdIfc2x_final::kIfcFanArrangementEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcFanRotationEnum
{
  kIfcFanRotationEnum_CLOCKWISE,
  kIfcFanRotationEnum_COUNTERCLOCKWISE,
  kIfcFanRotationEnum_OTHER,
  kIfcFanRotationEnum_NOTKNOWN,
  kIfcFanRotationEnum_UNSET,
  kIfcFanRotationEnum_unset
};

class IFC2X_FINAL_EXPORT IfcFanRotationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFanRotationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcFanRotationEnum& getUnset<OdIfc2x_final::IfcFanRotationEnum>() { static OdIfc2x_final::IfcFanRotationEnum nullEnum = OdIfc2x_final::kIfcFanRotationEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcFanDriveArrangementEnum
{
  kIfcFanDriveArrangementEnum_ARRANGEMENT1,
  kIfcFanDriveArrangementEnum_ARRANGEMENT2,
  kIfcFanDriveArrangementEnum_ARRANGEMENT3,
  kIfcFanDriveArrangementEnum_ARRANGEMENT4,
  kIfcFanDriveArrangementEnum_ARRANGEMENT5,
  kIfcFanDriveArrangementEnum_ARRANGEMENT6,
  kIfcFanDriveArrangementEnum_ARRANGEMENT7,
  kIfcFanDriveArrangementEnum_ARRANGEMENT8,
  kIfcFanDriveArrangementEnum_ARRANGEMENT9,
  kIfcFanDriveArrangementEnum_ARRANGEMENT10,
  kIfcFanDriveArrangementEnum_OTHER,
  kIfcFanDriveArrangementEnum_NOTKNOWN,
  kIfcFanDriveArrangementEnum_UNSET,
  kIfcFanDriveArrangementEnum_unset
};

class IFC2X_FINAL_EXPORT IfcFanDriveArrangementEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFanDriveArrangementEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcFanDriveArrangementEnum& getUnset<OdIfc2x_final::IfcFanDriveArrangementEnum>() { static OdIfc2x_final::IfcFanDriveArrangementEnum nullEnum = OdIfc2x_final::kIfcFanDriveArrangementEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcMoterConnectionTypeEnum
{
  kIfcMoterConnectionTypeEnum_DIRECTDRIVE,
  kIfcMoterConnectionTypeEnum_BELTDRIVE,
  kIfcMoterConnectionTypeEnum_COUPLING,
  kIfcMoterConnectionTypeEnum_OTHER,
  kIfcMoterConnectionTypeEnum_NOTKNOWN,
  kIfcMoterConnectionTypeEnum_UNSET,
  kIfcMoterConnectionTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcMoterConnectionTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMoterConnectionTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcMoterConnectionTypeEnum& getUnset<OdIfc2x_final::IfcMoterConnectionTypeEnum>() { static OdIfc2x_final::IfcMoterConnectionTypeEnum nullEnum = OdIfc2x_final::kIfcMoterConnectionTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcFanMountingTypeEnum
{
  kIfcFanMountingTypeEnum_MANUFACTUREDCURB,
  kIfcFanMountingTypeEnum_FIELDERECTEDCURB,
  kIfcFanMountingTypeEnum_CONCRETEPAD,
  kIfcFanMountingTypeEnum_SUSPENDED,
  kIfcFanMountingTypeEnum_WALLMOUNTED,
  kIfcFanMountingTypeEnum_DUCTMOUNTED,
  kIfcFanMountingTypeEnum_OTHER,
  kIfcFanMountingTypeEnum_NOTKNOWN,
  kIfcFanMountingTypeEnum_UNSET,
  kIfcFanMountingTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcFanMountingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcFanMountingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcFanMountingTypeEnum& getUnset<OdIfc2x_final::IfcFanMountingTypeEnum>() { static OdIfc2x_final::IfcFanMountingTypeEnum nullEnum = OdIfc2x_final::kIfcFanMountingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcPumpTypeEnum
{
  kIfcPumpTypeEnum_CIRCULATOR,
  kIfcPumpTypeEnum_ENDSUCTION,
  kIfcPumpTypeEnum_SPLITCASE,
  kIfcPumpTypeEnum_VERTICALINLINE,
  kIfcPumpTypeEnum_VERTICALTURBINE,
  kIfcPumpTypeEnum_OTHER,
  kIfcPumpTypeEnum_NOTKNOWN,
  kIfcPumpTypeEnum_UNSET,
  kIfcPumpTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcPumpTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPumpTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcPumpTypeEnum& getUnset<OdIfc2x_final::IfcPumpTypeEnum>() { static OdIfc2x_final::IfcPumpTypeEnum nullEnum = OdIfc2x_final::kIfcPumpTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcPumpBaseTypeEnum
{
  kIfcPumpBaseTypeEnum_FRAME,
  kIfcPumpBaseTypeEnum_BASE,
  kIfcPumpBaseTypeEnum_INLINE,
  kIfcPumpBaseTypeEnum_OTHER,
  kIfcPumpBaseTypeEnum_NOTKNOWN,
  kIfcPumpBaseTypeEnum_UNSET,
  kIfcPumpBaseTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcPumpBaseTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPumpBaseTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcPumpBaseTypeEnum& getUnset<OdIfc2x_final::IfcPumpBaseTypeEnum>() { static OdIfc2x_final::IfcPumpBaseTypeEnum nullEnum = OdIfc2x_final::kIfcPumpBaseTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcDistributionFlowElementTypeEnum
{
  kIfcDistributionFlowElementTypeEnum_FLUIDFLOW,
  kIfcDistributionFlowElementTypeEnum_USERDEFINED,
  kIfcDistributionFlowElementTypeEnum_NOTDEFINED,
  kIfcDistributionFlowElementTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcDistributionFlowElementTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDistributionFlowElementTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcDistributionFlowElementTypeEnum& getUnset<OdIfc2x_final::IfcDistributionFlowElementTypeEnum>() { static OdIfc2x_final::IfcDistributionFlowElementTypeEnum nullEnum = OdIfc2x_final::kIfcDistributionFlowElementTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcThermalLoadTypeEnum
{
  kIfcThermalLoadTypeEnum_PEOPLESENSIBLE,
  kIfcThermalLoadTypeEnum_PEOPLELATENT,
  kIfcThermalLoadTypeEnum_LIGHTING,
  kIfcThermalLoadTypeEnum_EQUIPMENTSENSIBLE,
  kIfcThermalLoadTypeEnum_EQUIPMENTLATENT,
  kIfcThermalLoadTypeEnum_VENTILATIONINDOORAIR,
  kIfcThermalLoadTypeEnum_VENTILATIONOUTSIDEAIR,
  kIfcThermalLoadTypeEnum_RECIRCULATEDAIR,
  kIfcThermalLoadTypeEnum_EXHAUSTAIR,
  kIfcThermalLoadTypeEnum_AIREXCHANGERATE,
  kIfcThermalLoadTypeEnum_DRYBULBTEMPERATURE,
  kIfcThermalLoadTypeEnum_RELATIVEHUMIDITY,
  kIfcThermalLoadTypeEnum_INFILTRATIONSENSIBLE,
  kIfcThermalLoadTypeEnum_INFILTRATIONLATENT,
  kIfcThermalLoadTypeEnum_OTHER,
  kIfcThermalLoadTypeEnum_NOTKNOWN,
  kIfcThermalLoadTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcThermalLoadTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcThermalLoadTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcThermalLoadTypeEnum& getUnset<OdIfc2x_final::IfcThermalLoadTypeEnum>() { static OdIfc2x_final::IfcThermalLoadTypeEnum nullEnum = OdIfc2x_final::kIfcThermalLoadTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcRequirementOrCriteriaEnum
{
  kIfcRequirementOrCriteriaEnum_REQUIREMENT,
  kIfcRequirementOrCriteriaEnum_CRITERIA,
  kIfcRequirementOrCriteriaEnum_NOTDEFINED,
  kIfcRequirementOrCriteriaEnum_unset
};

class IFC2X_FINAL_EXPORT IfcRequirementOrCriteriaEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRequirementOrCriteriaEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcRequirementOrCriteriaEnum& getUnset<OdIfc2x_final::IfcRequirementOrCriteriaEnum>() { static OdIfc2x_final::IfcRequirementOrCriteriaEnum nullEnum = OdIfc2x_final::kIfcRequirementOrCriteriaEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcLossOrGainEnum
{
  kIfcLossOrGainEnum_LOSS,
  kIfcLossOrGainEnum_GAIN,
  kIfcLossOrGainEnum_NOTDEFINED,
  kIfcLossOrGainEnum_unset
};

class IFC2X_FINAL_EXPORT IfcLossOrGainEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcLossOrGainEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcLossOrGainEnum& getUnset<OdIfc2x_final::IfcLossOrGainEnum>() { static OdIfc2x_final::IfcLossOrGainEnum nullEnum = OdIfc2x_final::kIfcLossOrGainEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcElectricCurrentEnum
{
  kIfcElectricCurrentEnum_ALTERNATING,
  kIfcElectricCurrentEnum_DIRECT,
  kIfcElectricCurrentEnum_NOTDEFINED,
  kIfcElectricCurrentEnum_unset
};

class IFC2X_FINAL_EXPORT IfcElectricCurrentEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricCurrentEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcElectricCurrentEnum& getUnset<OdIfc2x_final::IfcElectricCurrentEnum>() { static OdIfc2x_final::IfcElectricCurrentEnum nullEnum = OdIfc2x_final::kIfcElectricCurrentEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcRiskTypeEnum
{
  kIfcRiskTypeEnum_HEALTHANDSAFETY,
  kIfcRiskTypeEnum_HAZARD,
  kIfcRiskTypeEnum_INSURANCE,
  kIfcRiskTypeEnum_BUSINESS,
  kIfcRiskTypeEnum_GENERALRISKFACTOR,
  kIfcRiskTypeEnum_USERDEFINED,
  kIfcRiskTypeEnum_NOTDEFINED,
  kIfcRiskTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcRiskTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRiskTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcRiskTypeEnum& getUnset<OdIfc2x_final::IfcRiskTypeEnum>() { static OdIfc2x_final::IfcRiskTypeEnum nullEnum = OdIfc2x_final::kIfcRiskTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcInventoryTypeEnum
{
  kIfcInventoryTypeEnum_ASSETINVENTORY,
  kIfcInventoryTypeEnum_SPACEINVENTORY,
  kIfcInventoryTypeEnum_FURNITUREINVENTORY,
  kIfcInventoryTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcInventoryTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcInventoryTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcInventoryTypeEnum& getUnset<OdIfc2x_final::IfcInventoryTypeEnum>() { static OdIfc2x_final::IfcInventoryTypeEnum nullEnum = OdIfc2x_final::kIfcInventoryTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcCostUseEnum
{
  kIfcCostUseEnum_EXTENSIONONLY,
  kIfcCostUseEnum_ELEMENTONLY,
  kIfcCostUseEnum_ELEMENTSETEXTENSIONCALC,
  kIfcCostUseEnum_EXTENSIONSETELEMENTCALC,
  kIfcCostUseEnum_USERDEFINED,
  kIfcCostUseEnum_NOTDEFINED,
  kIfcCostUseEnum_unset
};

class IFC2X_FINAL_EXPORT IfcCostUseEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcCostUseEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcCostUseEnum& getUnset<OdIfc2x_final::IfcCostUseEnum>() { static OdIfc2x_final::IfcCostUseEnum nullEnum = OdIfc2x_final::kIfcCostUseEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcChangeOrderStatusEnum
{
  kIfcChangeOrderStatusEnum_PROPOSING,
  kIfcChangeOrderStatusEnum_PROPOSED,
  kIfcChangeOrderStatusEnum_REQUESTED,
  kIfcChangeOrderStatusEnum_BEINGAPPROVED,
  kIfcChangeOrderStatusEnum_PLANNING,
  kIfcChangeOrderStatusEnum_WORKSTARTED,
  kIfcChangeOrderStatusEnum_WORKDELAYED,
  kIfcChangeOrderStatusEnum_WORKDONE,
  kIfcChangeOrderStatusEnum_USERDEFINED,
  kIfcChangeOrderStatusEnum_NOTDEFINED,
  kIfcChangeOrderStatusEnum_unset
};

class IFC2X_FINAL_EXPORT IfcChangeOrderStatusEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcChangeOrderStatusEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcChangeOrderStatusEnum& getUnset<OdIfc2x_final::IfcChangeOrderStatusEnum>() { static OdIfc2x_final::IfcChangeOrderStatusEnum nullEnum = OdIfc2x_final::kIfcChangeOrderStatusEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcPurchaseOrderStatusEnum
{
  kIfcPurchaseOrderStatusEnum_REQUESTED,
  kIfcPurchaseOrderStatusEnum_BEINGAPPROVED,
  kIfcPurchaseOrderStatusEnum_ISSUED,
  kIfcPurchaseOrderStatusEnum_RECEIVED,
  kIfcPurchaseOrderStatusEnum_ITEMSRECEIVED,
  kIfcPurchaseOrderStatusEnum_USERDEFINED,
  kIfcPurchaseOrderStatusEnum_NOTDEFINED,
  kIfcPurchaseOrderStatusEnum_unset
};

class IFC2X_FINAL_EXPORT IfcPurchaseOrderStatusEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPurchaseOrderStatusEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcPurchaseOrderStatusEnum& getUnset<OdIfc2x_final::IfcPurchaseOrderStatusEnum>() { static OdIfc2x_final::IfcPurchaseOrderStatusEnum nullEnum = OdIfc2x_final::kIfcPurchaseOrderStatusEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcWorkOrderStatusEnum
{
  kIfcWorkOrderStatusEnum_REQUESTED,
  kIfcWorkOrderStatusEnum_BEINGAPPROVED,
  kIfcWorkOrderStatusEnum_PLANNING,
  kIfcWorkOrderStatusEnum_WORKSTARTED,
  kIfcWorkOrderStatusEnum_WORKDELAYED,
  kIfcWorkOrderStatusEnum_WORKDONE,
  kIfcWorkOrderStatusEnum_USERDEFINED,
  kIfcWorkOrderStatusEnum_NOTDEFINED,
  kIfcWorkOrderStatusEnum_unset
};

class IFC2X_FINAL_EXPORT IfcWorkOrderStatusEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWorkOrderStatusEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcWorkOrderStatusEnum& getUnset<OdIfc2x_final::IfcWorkOrderStatusEnum>() { static OdIfc2x_final::IfcWorkOrderStatusEnum nullEnum = OdIfc2x_final::kIfcWorkOrderStatusEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcWorkOrderRiskTypeEnum
{
  kIfcWorkOrderRiskTypeEnum_HEALTHANDSAFETY,
  kIfcWorkOrderRiskTypeEnum_HAZARDS,
  kIfcWorkOrderRiskTypeEnum_INSURANCE,
  kIfcWorkOrderRiskTypeEnum_GENERALRISKFACTOR,
  kIfcWorkOrderRiskTypeEnum_USERDEFINED,
  kIfcWorkOrderRiskTypeEnum_NOTDEFINED,
  kIfcWorkOrderRiskTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcWorkOrderRiskTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcWorkOrderRiskTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcWorkOrderRiskTypeEnum& getUnset<OdIfc2x_final::IfcWorkOrderRiskTypeEnum>() { static OdIfc2x_final::IfcWorkOrderRiskTypeEnum nullEnum = OdIfc2x_final::kIfcWorkOrderRiskTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcOccupantTypeEnum
{
  kIfcOccupantTypeEnum_OWNER,
  kIfcOccupantTypeEnum_LESSEE,
  kIfcOccupantTypeEnum_TENANT,
  kIfcOccupantTypeEnum_ASSIGNEE,
  kIfcOccupantTypeEnum_NOTDEFINED,
  kIfcOccupantTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcOccupantTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcOccupantTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcOccupantTypeEnum& getUnset<OdIfc2x_final::IfcOccupantTypeEnum>() { static OdIfc2x_final::IfcOccupantTypeEnum nullEnum = OdIfc2x_final::kIfcOccupantTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcPermeableCoveringOperationEnum
{
  kIfcPermeableCoveringOperationEnum_GRILL,
  kIfcPermeableCoveringOperationEnum_LOUVER,
  kIfcPermeableCoveringOperationEnum_SCREEN,
  kIfcPermeableCoveringOperationEnum_USERDEFINED,
  kIfcPermeableCoveringOperationEnum_NOTDEFINED,
  kIfcPermeableCoveringOperationEnum_unset
};

class IFC2X_FINAL_EXPORT IfcPermeableCoveringOperationEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPermeableCoveringOperationEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcPermeableCoveringOperationEnum& getUnset<OdIfc2x_final::IfcPermeableCoveringOperationEnum>() { static OdIfc2x_final::IfcPermeableCoveringOperationEnum nullEnum = OdIfc2x_final::kIfcPermeableCoveringOperationEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcJointEnum
{
  kIfcJointEnum_EXPANSION_JOINT,
  kIfcJointEnum_EDGE_JOINT,
  kIfcJointEnum_CONTROL_JOINT,
  kIfcJointEnum_NOTDEFINED,
  kIfcJointEnum_unset
};

class IFC2X_FINAL_EXPORT IfcJointEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcJointEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcJointEnum& getUnset<OdIfc2x_final::IfcJointEnum>() { static OdIfc2x_final::IfcJointEnum nullEnum = OdIfc2x_final::kIfcJointEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcRailingTypeEnum
{
  kIfcRailingTypeEnum_HANDRAIL,
  kIfcRailingTypeEnum_GUARDRAIL,
  kIfcRailingTypeEnum_BALUSTRADE,
  kIfcRailingTypeEnum_USERDEFINED,
  kIfcRailingTypeEnum_NOTDEFINED,
  kIfcRailingTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcRailingTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcRailingTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcRailingTypeEnum& getUnset<OdIfc2x_final::IfcRailingTypeEnum>() { static OdIfc2x_final::IfcRailingTypeEnum nullEnum = OdIfc2x_final::kIfcRailingTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcBuiltInTypeEnum
{
  kIfcBuiltInTypeEnum_ACCESSORY,
  kIfcBuiltInTypeEnum_CABINET,
  kIfcBuiltInTypeEnum_COUNTER,
  kIfcBuiltInTypeEnum_SHELF,
  kIfcBuiltInTypeEnum_USERDEFINED,
  kIfcBuiltInTypeEnum_NOTDEFINED,
  kIfcBuiltInTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcBuiltInTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcBuiltInTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcBuiltInTypeEnum& getUnset<OdIfc2x_final::IfcBuiltInTypeEnum>() { static OdIfc2x_final::IfcBuiltInTypeEnum nullEnum = OdIfc2x_final::kIfcBuiltInTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcMotorWindingEnum
{
  kIfcMotorWindingEnum_SYNCHRONOUS,
  kIfcMotorWindingEnum_ASYNCHRONOUS,
  kIfcMotorWindingEnum_SERIESWOUND,
  kIfcMotorWindingEnum_PARALLELWOUND,
  kIfcMotorWindingEnum_OTHER,
  kIfcMotorWindingEnum_NOTDEFINED,
  kIfcMotorWindingEnum_NOTKNOWN,
  kIfcMotorWindingEnum_UNSET,
  kIfcMotorWindingEnum_unset
};

class IFC2X_FINAL_EXPORT IfcMotorWindingEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMotorWindingEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcMotorWindingEnum& getUnset<OdIfc2x_final::IfcMotorWindingEnum>() { static OdIfc2x_final::IfcMotorWindingEnum nullEnum = OdIfc2x_final::kIfcMotorWindingEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcMotorHousingEnum
{
  kIfcMotorHousingEnum_SEALED,
  kIfcMotorHousingEnum_OPEN,
  kIfcMotorHousingEnum_OTHER,
  kIfcMotorHousingEnum_NOTKNOWN,
  kIfcMotorHousingEnum_UNSET,
  kIfcMotorHousingEnum_unset
};

class IFC2X_FINAL_EXPORT IfcMotorHousingEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMotorHousingEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcMotorHousingEnum& getUnset<OdIfc2x_final::IfcMotorHousingEnum>() { static OdIfc2x_final::IfcMotorHousingEnum nullEnum = OdIfc2x_final::kIfcMotorHousingEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcOutletTypeEnum
{
  kIfcOutletTypeEnum_POWEROUTLET,
  kIfcOutletTypeEnum_USERDEFINED,
  kIfcOutletTypeEnum_NOTDEFINED,
  kIfcOutletTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcOutletTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcOutletTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcOutletTypeEnum& getUnset<OdIfc2x_final::IfcOutletTypeEnum>() { static OdIfc2x_final::IfcOutletTypeEnum nullEnum = OdIfc2x_final::kIfcOutletTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcElectricalApplianceTypeEnum
{
  kIfcElectricalApplianceTypeEnum_COMPUTER,
  kIfcElectricalApplianceTypeEnum_COPIER,
  kIfcElectricalApplianceTypeEnum_FACSIMILE,
  kIfcElectricalApplianceTypeEnum_PRINTER,
  kIfcElectricalApplianceTypeEnum_RADIANTHEATER,
  kIfcElectricalApplianceTypeEnum_TELEPHONE,
  kIfcElectricalApplianceTypeEnum_USERDEFINED,
  kIfcElectricalApplianceTypeEnum_NOTDEFINED,
  kIfcElectricalApplianceTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcElectricalApplianceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcElectricalApplianceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcElectricalApplianceTypeEnum& getUnset<OdIfc2x_final::IfcElectricalApplianceTypeEnum>() { static OdIfc2x_final::IfcElectricalApplianceTypeEnum nullEnum = OdIfc2x_final::kIfcElectricalApplianceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcMaintenanceTypeEnum
{
  kIfcMaintenanceTypeEnum_SCHEDULED,
  kIfcMaintenanceTypeEnum_CORRECTIVE,
  kIfcMaintenanceTypeEnum_PLANNEDCORRECTIVE,
  kIfcMaintenanceTypeEnum_CONDITIONBASED,
  kIfcMaintenanceTypeEnum_USERDEFINED,
  kIfcMaintenanceTypeEnum_NOTDEFINED,
  kIfcMaintenanceTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcMaintenanceTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcMaintenanceTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcMaintenanceTypeEnum& getUnset<OdIfc2x_final::IfcMaintenanceTypeEnum>() { static OdIfc2x_final::IfcMaintenanceTypeEnum nullEnum = OdIfc2x_final::kIfcMaintenanceTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcPriorityEnum
{
  kIfcPriorityEnum_HIGH,
  kIfcPriorityEnum_MEDIUM,
  kIfcPriorityEnum_LOW,
  kIfcPriorityEnum_unset
};

class IFC2X_FINAL_EXPORT IfcPriorityEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcPriorityEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcPriorityEnum& getUnset<OdIfc2x_final::IfcPriorityEnum>() { static OdIfc2x_final::IfcPriorityEnum nullEnum = OdIfc2x_final::kIfcPriorityEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcActuatorTypeEnum
{
  kIfcActuatorTypeEnum_ELECTRICACTUATOR,
  kIfcActuatorTypeEnum_PNEUMATICACTUATOR,
  kIfcActuatorTypeEnum_HYDRAULICACTUATOR,
  kIfcActuatorTypeEnum_HANDOPERATEDACTUATOR,
  kIfcActuatorTypeEnum_USERDEFINED,
  kIfcActuatorTypeEnum_NOTDEFINED,
  kIfcActuatorTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcActuatorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcActuatorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcActuatorTypeEnum& getUnset<OdIfc2x_final::IfcActuatorTypeEnum>() { static OdIfc2x_final::IfcActuatorTypeEnum nullEnum = OdIfc2x_final::kIfcActuatorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcActuatorFailPositionEnum
{
  kIfcActuatorFailPositionEnum_FAILOPEN,
  kIfcActuatorFailPositionEnum_FAILCLOSED,
  kIfcActuatorFailPositionEnum_USERDEFINED,
  kIfcActuatorFailPositionEnum_NOTDEFINED,
  kIfcActuatorFailPositionEnum_unset
};

class IFC2X_FINAL_EXPORT IfcActuatorFailPositionEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcActuatorFailPositionEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcActuatorFailPositionEnum& getUnset<OdIfc2x_final::IfcActuatorFailPositionEnum>() { static OdIfc2x_final::IfcActuatorFailPositionEnum nullEnum = OdIfc2x_final::kIfcActuatorFailPositionEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcSensorTypeEnum
{
  kIfcSensorTypeEnum_HVACSENSOR,
  kIfcSensorTypeEnum_USERDEFINED,
  kIfcSensorTypeEnum_NOTDEFINED,
  kIfcSensorTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcSensorTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcSensorTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcSensorTypeEnum& getUnset<OdIfc2x_final::IfcSensorTypeEnum>() { static OdIfc2x_final::IfcSensorTypeEnum nullEnum = OdIfc2x_final::kIfcSensorTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcValveEnum
{
  kIfcValveEnum_AUTOMATED,
  kIfcValveEnum_ANGLE,
  kIfcValveEnum_AWWA,
  kIfcValveEnum_BALL,
  kIfcValveEnum_BUTTERFLY,
  kIfcValveEnum_CHECK,
  kIfcValveEnum_DIVERTER,
  kIfcValveEnum_GATE,
  kIfcValveEnum_GLOBE,
  kIfcValveEnum_NACE,
  kIfcValveEnum_NEEDLE,
  kIfcValveEnum_PLUG,
  kIfcValveEnum_PIPELINE,
  kIfcValveEnum_SAFETY,
  kIfcValveEnum_THREEWAY,
  kIfcValveEnum_ULFM,
  kIfcValveEnum_USERDEFINED,
  kIfcValveEnum_NOTDEFINED,
  kIfcValveEnum_unset
};

class IFC2X_FINAL_EXPORT IfcValveEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcValveEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcValveEnum& getUnset<OdIfc2x_final::IfcValveEnum>() { static OdIfc2x_final::IfcValveEnum nullEnum = OdIfc2x_final::kIfcValveEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcAirTerminalBoxEnum
{
  kIfcAirTerminalBoxEnum_VARIABLEAIRVOLUME,
  kIfcAirTerminalBoxEnum_CONSTANTVOLUME,
  kIfcAirTerminalBoxEnum_VARIABLEAIRVOLUMEREHEAT,
  kIfcAirTerminalBoxEnum_CONSTANTVOLUMEREHEAT,
  kIfcAirTerminalBoxEnum_VARIABLEAIRVOLUMEDUALDUCT,
  kIfcAirTerminalBoxEnum_CONSTANTVOLUMEDUALDUCT,
  kIfcAirTerminalBoxEnum_FANPOWERED,
  kIfcAirTerminalBoxEnum_USERDEFINED,
  kIfcAirTerminalBoxEnum_NOTDEFINED,
  kIfcAirTerminalBoxEnum_unset
};

class IFC2X_FINAL_EXPORT IfcAirTerminalBoxEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcAirTerminalBoxEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcAirTerminalBoxEnum& getUnset<OdIfc2x_final::IfcAirTerminalBoxEnum>() { static OdIfc2x_final::IfcAirTerminalBoxEnum nullEnum = OdIfc2x_final::kIfcAirTerminalBoxEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcDamperTypeEnum
{
  kIfcDamperTypeEnum_FIREDAMPER,
  kIfcDamperTypeEnum_SMOKEDAMPER,
  kIfcDamperTypeEnum_FIRESMOKEDAMPER,
  kIfcDamperTypeEnum_BACKDRAFTDAMPER,
  kIfcDamperTypeEnum_CONTROLDAMPER,
  kIfcDamperTypeEnum_LOUVER,
  kIfcDamperTypeEnum_USERDEFINED,
  kIfcDamperTypeEnum_NOTDEFINED,
  kIfcDamperTypeEnum_unset
};

class IFC2X_FINAL_EXPORT IfcDamperTypeEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDamperTypeEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcDamperTypeEnum& getUnset<OdIfc2x_final::IfcDamperTypeEnum>() { static OdIfc2x_final::IfcDamperTypeEnum nullEnum = OdIfc2x_final::kIfcDamperTypeEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {
enum IfcDamperSizingMethodEnum
{
  kIfcDamperSizingMethodEnum_NOMINAL,
  kIfcDamperSizingMethodEnum_EXACT,
  kIfcDamperSizingMethodEnum_USERDEFINED,
  kIfcDamperSizingMethodEnum_NOTDEFINED,
  kIfcDamperSizingMethodEnum_unset
};

class IFC2X_FINAL_EXPORT IfcDamperSizingMethodEnumTypeProvider
    : public OdDAI::EnumItemTypeProvider
{
public:
    static const OdDAI::EnumerationType* SchemaType();
    static void init(const OdRxDictionaryPtr& types);
    static void uninit();
    static IfcDamperSizingMethodEnumTypeProvider& instance();
};
}

namespace OdDAI { namespace Utils { template <> inline const OdIfc2x_final::IfcDamperSizingMethodEnum& getUnset<OdIfc2x_final::IfcDamperSizingMethodEnum>() { static OdIfc2x_final::IfcDamperSizingMethodEnum nullEnum = OdIfc2x_final::kIfcDamperSizingMethodEnum_unset; return nullEnum; } } }

namespace OdIfc2x_final {

} // namespace

#endif // _IFC2X_FINAL_ENUM_H

