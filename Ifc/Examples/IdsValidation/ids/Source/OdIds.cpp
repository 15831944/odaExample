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
#include <OdaCommon.h>
#include "OdIds.h"
#include <RxValueTypeUtil.h>
#include <RxDictionary.h>
#include <RxInit.h>
#include <OdIdsIdsType.h>
#include <OdIdsIds.h>
#include <OdIdsEntityType.h>
#include <OdIdsIdsValue.h>
#include <OdIdsClassificationType.h>
#include <OdIdsApplicabilityType.h>
#include <OdIdsSystemType.h>
#include <OdIdsPropertyType.h>
#include <OdIdsMaterialType.h>
#include <OdIdsRequirementsType.h>
#include <OdIdsSpecificationType.h>
#include <OdIdsApplicabilityTypeProperty.h>
#include <OdIdsApplicabilityTypeMaterial.h>
#include <OdIdsRequirementsTypeClassification.h>
#include <OdIdsRequirementsTypeProperty.h>
#include <OdIdsRequirementsTypeMaterial.h>
#include <OdIdsInfo.h>

static OdRxValueType* g_valxmlNodePtr = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<xmlNodePtr>::value() throw ()
{
  if (g_valxmlNodePtr == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valxmlNodePtr == 0)
      g_valxmlNodePtr = new OdRxValueTypePOD<xmlNodePtr>((const OdChar*)L"xmlNodePtr", 0);
  }
  return *g_valxmlNodePtr;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <xmlNodePtr>::del()
{
  if (g_valxmlNodePtr)
  {
    odrxClassDictionary()->remove(L"xmlNodePtr");
    delete g_valxmlNodePtr;
    g_valxmlNodePtr = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(xmlNodePtr const &val) throw () : m_type(OdRxValueType::Desc<xmlNodePtr>::value())
{
  initBlittable<sizeof(xmlNodePtr) <= 24> (&val, sizeof(xmlNodePtr));
}

template<> ODIDS_DLLEXPORT bool OdRxValueTypePOD<xmlNodePtr>::subEqualTo(const void* a, const void* b) const { return *(xmlNodePtr*)a == *(xmlNodePtr*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxValueTypePOD<xmlNodePtr>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}


ODIDS_DLLEXPORT void OdIdsInitalize(OdRxSystemServices* svc)
{
  ::odrxInitialize(svc);
  OdIdsIdsType::rxInit();
  OdIdsIds::rxInit();
  OdIdsEntityType::rxInit();
  OdIdsIdsValue::rxInit();
  OdIdsClassificationType::rxInit();
  OdIdsApplicabilityType::rxInit();
  OdIdsSystemType::rxInit();
  OdIdsPropertyType::rxInit();
  OdIdsMaterialType::rxInit();
  OdIdsRequirementsType::rxInit();
  OdIdsSpecificationType::rxInit();
  OdIdsApplicabilityTypeProperty::rxInit();
  OdIdsApplicabilityTypeMaterial::rxInit();
  OdIdsRequirementsTypeClassification::rxInit();
  OdIdsRequirementsTypeProperty::rxInit();
  OdIdsRequirementsTypeMaterial::rxInit();
  OdIdsInfo::rxInit();
}

ODIDS_DLLEXPORT void OdIdsUninitalize()
{
  ::odrxUninitialize();
  OdIdsIdsType::rxUninit();
  OdRxValueType::Desc <OdIdsIdsTypePtrArray>::del();
  OdIdsIds::rxUninit();
  OdRxValueType::Desc <OdIdsIdsPtrArray>::del();
  OdIdsEntityType::rxUninit();
  OdRxValueType::Desc <OdIdsEntityTypePtrArray>::del();
  OdIdsIdsValue::rxUninit();
  OdRxValueType::Desc <OdIdsIdsValuePtrArray>::del();
  OdIdsClassificationType::rxUninit();
  OdRxValueType::Desc <OdIdsClassificationTypePtrArray>::del();
  OdIdsApplicabilityType::rxUninit();
  OdRxValueType::Desc <OdIdsApplicabilityTypePtrArray>::del();
  OdIdsSystemType::rxUninit();
  OdRxValueType::Desc <OdIdsSystemTypePtrArray>::del();
  OdIdsPropertyType::rxUninit();
  OdRxValueType::Desc <OdIdsPropertyTypePtrArray>::del();
  OdIdsMaterialType::rxUninit();
  OdRxValueType::Desc <OdIdsMaterialTypePtrArray>::del();
  OdIdsRequirementsType::rxUninit();
  OdRxValueType::Desc <OdIdsRequirementsTypePtrArray>::del();
  OdIdsSpecificationType::rxUninit();
  OdRxValueType::Desc <OdIdsSpecificationTypePtrArray>::del();
  OdRxValueType::Desc <OdIdsSpecificationTypeNecessity>::del();
  OdRxValueType::Desc <OdIdsSpecificationTypeNecessityArray>::del();
  OdRxValueType::Desc <OdIdsClassificationTypeLocation>::del();
  OdRxValueType::Desc <OdIdsClassificationTypeLocationArray>::del();
  OdIdsApplicabilityTypeProperty::rxUninit();
  OdRxValueType::Desc <OdIdsApplicabilityTypePropertyPtrArray>::del();
  OdRxValueType::Desc <OdIdsPropertyTypeLocation>::del();
  OdRxValueType::Desc <OdIdsPropertyTypeLocationArray>::del();
  OdIdsApplicabilityTypeMaterial::rxUninit();
  OdRxValueType::Desc <OdIdsApplicabilityTypeMaterialPtrArray>::del();
  OdRxValueType::Desc <OdIdsMaterialTypeLocation>::del();
  OdRxValueType::Desc <OdIdsMaterialTypeLocationArray>::del();
  OdIdsRequirementsTypeClassification::rxUninit();
  OdRxValueType::Desc <OdIdsRequirementsTypeClassificationPtrArray>::del();
  OdRxValueType::Desc <OdIdsUse>::del();
  OdRxValueType::Desc <OdIdsUseArray>::del();
  OdIdsRequirementsTypeProperty::rxUninit();
  OdRxValueType::Desc <OdIdsRequirementsTypePropertyPtrArray>::del();
  OdIdsRequirementsTypeMaterial::rxUninit();
  OdRxValueType::Desc <OdIdsRequirementsTypeMaterialPtrArray>::del();
  OdIdsInfo::rxUninit();
  OdRxValueType::Desc <OdIdsInfoPtrArray>::del();
  OdRxValueType::Desc <OdIdsIfcversion>::del();
  OdRxValueType::Desc <OdIdsIfcversionArray>::del();
  OdRxValueType::Desc <OdIdsAuthor>::del();
  OdRxValueType::Desc <OdIdsAuthorArray>::del();

  OdRxValueType::Desc <OdXmlRestrictionArray>::del();
}
