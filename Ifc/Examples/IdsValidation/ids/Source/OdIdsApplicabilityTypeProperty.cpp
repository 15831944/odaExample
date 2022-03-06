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
#include <RxObject.h>
#include <RxObjectImpl.h>
#include <libxml/tree.h>
#include <RxValueTypeUtil.h>
#include <RxDictionary.h>
#include <OdIdsApplicabilityTypeProperty.h>

ODRX_CONS_DEFINE_MEMBERS(OdIdsApplicabilityTypeProperty, OdIdsPropertyType, RXIMPL_CONSTR);

static OdRxValueType* g_valOdIdsApplicabilityTypePropertyPtrArray = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsApplicabilityTypePropertyPtrArray>::value() throw ()
{
  if (g_valOdIdsApplicabilityTypePropertyPtrArray == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsApplicabilityTypePropertyPtrArray == 0)
      g_valOdIdsApplicabilityTypePropertyPtrArray = new OdRxNonBlittableType<OdIdsApplicabilityTypePropertyPtrArray>((const OdChar*)L"OdIdsApplicabilityTypePropertyPtrArray", 0);
  }
  return *g_valOdIdsApplicabilityTypePropertyPtrArray;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsApplicabilityTypePropertyPtrArray>::del()
{
  if (g_valOdIdsApplicabilityTypePropertyPtrArray)
  {
    odrxClassDictionary()->remove(L"OdIdsApplicabilityTypePropertyPtrArray");
    delete g_valOdIdsApplicabilityTypePropertyPtrArray;
    g_valOdIdsApplicabilityTypePropertyPtrArray = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsApplicabilityTypePropertyPtrArray const &val) throw () : m_type(OdRxValueType::Desc<OdIdsApplicabilityTypePropertyPtrArray>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsApplicabilityTypePropertyPtrArray>::subEqualTo(const void* a, const void* b) const { return *(OdIdsApplicabilityTypePropertyPtrArray*)a == *(OdIdsApplicabilityTypePropertyPtrArray*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsApplicabilityTypePropertyPtrArray>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

OdIdsApplicabilityTypeProperty::OdIdsApplicabilityTypeProperty(){}

OdIdsApplicabilityTypeProperty::~OdIdsApplicabilityTypeProperty(){}

void OdIdsApplicabilityTypeProperty::readXml(xmlNode* node)
{
  OdIdsPropertyType::readXml(node);
}

void OdIdsApplicabilityTypeProperty::writeXml(xmlNode* node)
{
  OdIdsPropertyType::writeXml(node);
}

