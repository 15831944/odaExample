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
#include <OdIdsMaterialTypeLocation.h>

static OdRxValueType* g_valOdIdsMaterialTypeLocation = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsMaterialTypeLocation>::value() throw ()
{
  if (g_valOdIdsMaterialTypeLocation == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsMaterialTypeLocation == 0)
      g_valOdIdsMaterialTypeLocation = new OdRxNonBlittableType<OdIdsMaterialTypeLocation>((const OdChar*)L"OdIdsMaterialTypeLocation", 0);
  }
  return *g_valOdIdsMaterialTypeLocation;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsMaterialTypeLocation>::del()
{
  if (g_valOdIdsMaterialTypeLocation)
  {
    odrxClassDictionary()->remove(L"OdIdsMaterialTypeLocation");
    delete g_valOdIdsMaterialTypeLocation;
    g_valOdIdsMaterialTypeLocation = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsMaterialTypeLocation const &val) throw () : m_type(OdRxValueType::Desc<OdIdsMaterialTypeLocation>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsMaterialTypeLocation>::subEqualTo(const void* a, const void* b) const { return *(OdIdsMaterialTypeLocation*)a == *(OdIdsMaterialTypeLocation*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsMaterialTypeLocation>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

static OdRxValueType* g_valOdIdsMaterialTypeLocationArray = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsMaterialTypeLocationArray>::value() throw ()
{
  if (g_valOdIdsMaterialTypeLocationArray == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsMaterialTypeLocationArray == 0)
      g_valOdIdsMaterialTypeLocationArray = new OdRxNonBlittableType<OdIdsMaterialTypeLocationArray>((const OdChar*)L"OdIdsMaterialTypeLocationArray", 0);
  }
  return *g_valOdIdsMaterialTypeLocationArray;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsMaterialTypeLocationArray>::del()
{
  if (g_valOdIdsMaterialTypeLocationArray)
  {
    odrxClassDictionary()->remove(L"OdIdsMaterialTypeLocationArray");
    delete g_valOdIdsMaterialTypeLocationArray;
    g_valOdIdsMaterialTypeLocationArray = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsMaterialTypeLocationArray const &val) throw () : m_type(OdRxValueType::Desc<OdIdsMaterialTypeLocationArray>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsMaterialTypeLocationArray>::subEqualTo(const void* a, const void* b) const { return *(OdIdsMaterialTypeLocationArray*)a == *(OdIdsMaterialTypeLocationArray*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsMaterialTypeLocationArray>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

OdIdsMaterialTypeLocation::OdIdsMaterialTypeLocation(){}

OdIdsMaterialTypeLocation::~OdIdsMaterialTypeLocation(){}

void OdIdsMaterialTypeLocation::readXml(xmlNode* node)
{
  _value = OdAnsiString((const char*)node->children->content, CP_UTF_8);
}

void OdIdsMaterialTypeLocation::writeXml(xmlNode* node)
{
  xmlNodeSetContent(node, (const xmlChar*)(const char*)_value);
}

