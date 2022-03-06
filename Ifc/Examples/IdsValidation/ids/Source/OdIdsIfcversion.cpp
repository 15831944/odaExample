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
#include <OdIdsIfcversion.h>

static OdRxValueType* g_valOdIdsIfcversion = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsIfcversion>::value() throw ()
{
  if (g_valOdIdsIfcversion == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsIfcversion == 0)
      g_valOdIdsIfcversion = new OdRxNonBlittableType<OdIdsIfcversion>((const OdChar*)L"OdIdsIfcversion", 0);
  }
  return *g_valOdIdsIfcversion;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsIfcversion>::del()
{
  if (g_valOdIdsIfcversion)
  {
    odrxClassDictionary()->remove(L"OdIdsIfcversion");
    delete g_valOdIdsIfcversion;
    g_valOdIdsIfcversion = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsIfcversion const &val) throw () : m_type(OdRxValueType::Desc<OdIdsIfcversion>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsIfcversion>::subEqualTo(const void* a, const void* b) const { return *(OdIdsIfcversion*)a == *(OdIdsIfcversion*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsIfcversion>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

static OdRxValueType* g_valOdIdsIfcversionArray = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsIfcversionArray>::value() throw ()
{
  if (g_valOdIdsIfcversionArray == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsIfcversionArray == 0)
      g_valOdIdsIfcversionArray = new OdRxNonBlittableType<OdIdsIfcversionArray>((const OdChar*)L"OdIdsIfcversionArray", 0);
  }
  return *g_valOdIdsIfcversionArray;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsIfcversionArray>::del()
{
  if (g_valOdIdsIfcversionArray)
  {
    odrxClassDictionary()->remove(L"OdIdsIfcversionArray");
    delete g_valOdIdsIfcversionArray;
    g_valOdIdsIfcversionArray = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsIfcversionArray const &val) throw () : m_type(OdRxValueType::Desc<OdIdsIfcversionArray>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsIfcversionArray>::subEqualTo(const void* a, const void* b) const { return *(OdIdsIfcversionArray*)a == *(OdIdsIfcversionArray*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsIfcversionArray>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

OdIdsIfcversion::OdIdsIfcversion(){}

OdIdsIfcversion::~OdIdsIfcversion(){}

void OdIdsIfcversion::readXml(xmlNode* node)
{
  _value = OdAnsiString((const char*)node->children->content, CP_UTF_8);
}

void OdIdsIfcversion::writeXml(xmlNode* node)
{
  xmlNodeSetContent(node, (const xmlChar*)(const char*)_value);
}

