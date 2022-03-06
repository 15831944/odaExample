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
#include <OdIdsApplicabilityTypeMaterial.h>

ODRX_CONS_DEFINE_MEMBERS(OdIdsApplicabilityTypeMaterial, OdIdsMaterialType, RXIMPL_CONSTR);

static OdRxValueType* g_valOdIdsApplicabilityTypeMaterialPtrArray = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsApplicabilityTypeMaterialPtrArray>::value() throw ()
{
  if (g_valOdIdsApplicabilityTypeMaterialPtrArray == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsApplicabilityTypeMaterialPtrArray == 0)
      g_valOdIdsApplicabilityTypeMaterialPtrArray = new OdRxNonBlittableType<OdIdsApplicabilityTypeMaterialPtrArray>((const OdChar*)L"OdIdsApplicabilityTypeMaterialPtrArray", 0);
  }
  return *g_valOdIdsApplicabilityTypeMaterialPtrArray;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsApplicabilityTypeMaterialPtrArray>::del()
{
  if (g_valOdIdsApplicabilityTypeMaterialPtrArray)
  {
    odrxClassDictionary()->remove(L"OdIdsApplicabilityTypeMaterialPtrArray");
    delete g_valOdIdsApplicabilityTypeMaterialPtrArray;
    g_valOdIdsApplicabilityTypeMaterialPtrArray = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsApplicabilityTypeMaterialPtrArray const &val) throw () : m_type(OdRxValueType::Desc<OdIdsApplicabilityTypeMaterialPtrArray>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsApplicabilityTypeMaterialPtrArray>::subEqualTo(const void* a, const void* b) const { return *(OdIdsApplicabilityTypeMaterialPtrArray*)a == *(OdIdsApplicabilityTypeMaterialPtrArray*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsApplicabilityTypeMaterialPtrArray>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

OdIdsApplicabilityTypeMaterial::OdIdsApplicabilityTypeMaterial(){}

OdIdsApplicabilityTypeMaterial::~OdIdsApplicabilityTypeMaterial(){}

void OdIdsApplicabilityTypeMaterial::readXml(xmlNode* node)
{
  OdIdsMaterialType::readXml(node);
}

void OdIdsApplicabilityTypeMaterial::writeXml(xmlNode* node)
{
  OdIdsMaterialType::writeXml(node);
}

