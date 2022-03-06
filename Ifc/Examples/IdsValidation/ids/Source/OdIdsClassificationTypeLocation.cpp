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
#include <OdIdsClassificationTypeLocation.h>

static OdRxValueType* g_valOdIdsClassificationTypeLocation = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsClassificationTypeLocation>::value() throw ()
{
  if (g_valOdIdsClassificationTypeLocation == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsClassificationTypeLocation == 0)
      g_valOdIdsClassificationTypeLocation = new OdRxNonBlittableType<OdIdsClassificationTypeLocation>((const OdChar*)L"OdIdsClassificationTypeLocation", 0);
  }
  return *g_valOdIdsClassificationTypeLocation;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsClassificationTypeLocation>::del()
{
  if (g_valOdIdsClassificationTypeLocation)
  {
    odrxClassDictionary()->remove(L"OdIdsClassificationTypeLocation");
    delete g_valOdIdsClassificationTypeLocation;
    g_valOdIdsClassificationTypeLocation = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsClassificationTypeLocation const &val) throw () : m_type(OdRxValueType::Desc<OdIdsClassificationTypeLocation>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsClassificationTypeLocation>::subEqualTo(const void* a, const void* b) const { return *(OdIdsClassificationTypeLocation*)a == *(OdIdsClassificationTypeLocation*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsClassificationTypeLocation>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

static OdRxValueType* g_valOdIdsClassificationTypeLocationArray = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsClassificationTypeLocationArray>::value() throw ()
{
  if (g_valOdIdsClassificationTypeLocationArray == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsClassificationTypeLocationArray == 0)
      g_valOdIdsClassificationTypeLocationArray = new OdRxNonBlittableType<OdIdsClassificationTypeLocationArray>((const OdChar*)L"OdIdsClassificationTypeLocationArray", 0);
  }
  return *g_valOdIdsClassificationTypeLocationArray;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsClassificationTypeLocationArray>::del()
{
  if (g_valOdIdsClassificationTypeLocationArray)
  {
    odrxClassDictionary()->remove(L"OdIdsClassificationTypeLocationArray");
    delete g_valOdIdsClassificationTypeLocationArray;
    g_valOdIdsClassificationTypeLocationArray = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsClassificationTypeLocationArray const &val) throw () : m_type(OdRxValueType::Desc<OdIdsClassificationTypeLocationArray>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsClassificationTypeLocationArray>::subEqualTo(const void* a, const void* b) const { return *(OdIdsClassificationTypeLocationArray*)a == *(OdIdsClassificationTypeLocationArray*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsClassificationTypeLocationArray>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

OdIdsClassificationTypeLocation::OdIdsClassificationTypeLocation(){}

OdIdsClassificationTypeLocation::~OdIdsClassificationTypeLocation(){}

void OdIdsClassificationTypeLocation::readXml(xmlNode* node)
{
  _value = OdAnsiString((const char*)node->children->content, CP_UTF_8);
}

void OdIdsClassificationTypeLocation::writeXml(xmlNode* node)
{
  xmlNodeSetContent(node, (const xmlChar*)(const char*)_value);
}

