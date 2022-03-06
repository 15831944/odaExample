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
#include <OdIdsPropertyTypeLocation.h>

static OdRxValueType* g_valOdIdsPropertyTypeLocation = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsPropertyTypeLocation>::value() throw ()
{
  if (g_valOdIdsPropertyTypeLocation == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsPropertyTypeLocation == 0)
      g_valOdIdsPropertyTypeLocation = new OdRxNonBlittableType<OdIdsPropertyTypeLocation>((const OdChar*)L"OdIdsPropertyTypeLocation", 0);
  }
  return *g_valOdIdsPropertyTypeLocation;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsPropertyTypeLocation>::del()
{
  if (g_valOdIdsPropertyTypeLocation)
  {
    odrxClassDictionary()->remove(L"OdIdsPropertyTypeLocation");
    delete g_valOdIdsPropertyTypeLocation;
    g_valOdIdsPropertyTypeLocation = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsPropertyTypeLocation const &val) throw () : m_type(OdRxValueType::Desc<OdIdsPropertyTypeLocation>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsPropertyTypeLocation>::subEqualTo(const void* a, const void* b) const { return *(OdIdsPropertyTypeLocation*)a == *(OdIdsPropertyTypeLocation*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsPropertyTypeLocation>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

static OdRxValueType* g_valOdIdsPropertyTypeLocationArray = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsPropertyTypeLocationArray>::value() throw ()
{
  if (g_valOdIdsPropertyTypeLocationArray == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsPropertyTypeLocationArray == 0)
      g_valOdIdsPropertyTypeLocationArray = new OdRxNonBlittableType<OdIdsPropertyTypeLocationArray>((const OdChar*)L"OdIdsPropertyTypeLocationArray", 0);
  }
  return *g_valOdIdsPropertyTypeLocationArray;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsPropertyTypeLocationArray>::del()
{
  if (g_valOdIdsPropertyTypeLocationArray)
  {
    odrxClassDictionary()->remove(L"OdIdsPropertyTypeLocationArray");
    delete g_valOdIdsPropertyTypeLocationArray;
    g_valOdIdsPropertyTypeLocationArray = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsPropertyTypeLocationArray const &val) throw () : m_type(OdRxValueType::Desc<OdIdsPropertyTypeLocationArray>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsPropertyTypeLocationArray>::subEqualTo(const void* a, const void* b) const { return *(OdIdsPropertyTypeLocationArray*)a == *(OdIdsPropertyTypeLocationArray*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsPropertyTypeLocationArray>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

OdIdsPropertyTypeLocation::OdIdsPropertyTypeLocation(){}

OdIdsPropertyTypeLocation::~OdIdsPropertyTypeLocation(){}

void OdIdsPropertyTypeLocation::readXml(xmlNode* node)
{
  _value = OdAnsiString((const char*)node->children->content, CP_UTF_8);
}

void OdIdsPropertyTypeLocation::writeXml(xmlNode* node)
{
  xmlNodeSetContent(node, (const xmlChar*)(const char*)_value);
}

