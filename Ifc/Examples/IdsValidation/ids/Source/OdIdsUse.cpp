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
#include <OdIdsUse.h>

static OdRxValueType* g_valOdIdsUse = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsUse>::value() throw ()
{
  if (g_valOdIdsUse == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsUse == 0)
      g_valOdIdsUse = new OdRxNonBlittableType<OdIdsUse>((const OdChar*)L"OdIdsUse", 0);
  }
  return *g_valOdIdsUse;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsUse>::del()
{
  if (g_valOdIdsUse)
  {
    odrxClassDictionary()->remove(L"OdIdsUse");
    delete g_valOdIdsUse;
    g_valOdIdsUse = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsUse const &val) throw () : m_type(OdRxValueType::Desc<OdIdsUse>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsUse>::subEqualTo(const void* a, const void* b) const { return *(OdIdsUse*)a == *(OdIdsUse*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsUse>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

static OdRxValueType* g_valOdIdsUseArray = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsUseArray>::value() throw ()
{
  if (g_valOdIdsUseArray == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsUseArray == 0)
      g_valOdIdsUseArray = new OdRxNonBlittableType<OdIdsUseArray>((const OdChar*)L"OdIdsUseArray", 0);
  }
  return *g_valOdIdsUseArray;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsUseArray>::del()
{
  if (g_valOdIdsUseArray)
  {
    odrxClassDictionary()->remove(L"OdIdsUseArray");
    delete g_valOdIdsUseArray;
    g_valOdIdsUseArray = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsUseArray const &val) throw () : m_type(OdRxValueType::Desc<OdIdsUseArray>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsUseArray>::subEqualTo(const void* a, const void* b) const { return *(OdIdsUseArray*)a == *(OdIdsUseArray*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsUseArray>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

OdIdsUse::OdIdsUse(){}

OdIdsUse::~OdIdsUse(){}

void OdIdsUse::readXml(xmlNode* node)
{
  _value = OdAnsiString((const char*)node->children->content, CP_UTF_8);
}

void OdIdsUse::writeXml(xmlNode* node)
{
  xmlNodeSetContent(node, (const xmlChar*)(const char*)_value);
}

