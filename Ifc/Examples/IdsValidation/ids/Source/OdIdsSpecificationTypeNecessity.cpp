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
#include <OdIdsSpecificationTypeNecessity.h>

static OdRxValueType* g_valOdIdsSpecificationTypeNecessity = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsSpecificationTypeNecessity>::value() throw ()
{
  if (g_valOdIdsSpecificationTypeNecessity == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsSpecificationTypeNecessity == 0)
      g_valOdIdsSpecificationTypeNecessity = new OdRxNonBlittableType<OdIdsSpecificationTypeNecessity>((const OdChar*)L"OdIdsSpecificationTypeNecessity", 0);
  }
  return *g_valOdIdsSpecificationTypeNecessity;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsSpecificationTypeNecessity>::del()
{
  if (g_valOdIdsSpecificationTypeNecessity)
  {
    odrxClassDictionary()->remove(L"OdIdsSpecificationTypeNecessity");
    delete g_valOdIdsSpecificationTypeNecessity;
    g_valOdIdsSpecificationTypeNecessity = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsSpecificationTypeNecessity const &val) throw () : m_type(OdRxValueType::Desc<OdIdsSpecificationTypeNecessity>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsSpecificationTypeNecessity>::subEqualTo(const void* a, const void* b) const { return *(OdIdsSpecificationTypeNecessity*)a == *(OdIdsSpecificationTypeNecessity*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsSpecificationTypeNecessity>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

static OdRxValueType* g_valOdIdsSpecificationTypeNecessityArray = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsSpecificationTypeNecessityArray>::value() throw ()
{
  if (g_valOdIdsSpecificationTypeNecessityArray == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsSpecificationTypeNecessityArray == 0)
      g_valOdIdsSpecificationTypeNecessityArray = new OdRxNonBlittableType<OdIdsSpecificationTypeNecessityArray>((const OdChar*)L"OdIdsSpecificationTypeNecessityArray", 0);
  }
  return *g_valOdIdsSpecificationTypeNecessityArray;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsSpecificationTypeNecessityArray>::del()
{
  if (g_valOdIdsSpecificationTypeNecessityArray)
  {
    odrxClassDictionary()->remove(L"OdIdsSpecificationTypeNecessityArray");
    delete g_valOdIdsSpecificationTypeNecessityArray;
    g_valOdIdsSpecificationTypeNecessityArray = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsSpecificationTypeNecessityArray const &val) throw () : m_type(OdRxValueType::Desc<OdIdsSpecificationTypeNecessityArray>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsSpecificationTypeNecessityArray>::subEqualTo(const void* a, const void* b) const { return *(OdIdsSpecificationTypeNecessityArray*)a == *(OdIdsSpecificationTypeNecessityArray*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsSpecificationTypeNecessityArray>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

OdIdsSpecificationTypeNecessity::OdIdsSpecificationTypeNecessity(){}

OdIdsSpecificationTypeNecessity::~OdIdsSpecificationTypeNecessity(){}

void OdIdsSpecificationTypeNecessity::readXml(xmlNode* node)
{
  _value = OdAnsiString((const char*)node->children->content, CP_UTF_8);
}

void OdIdsSpecificationTypeNecessity::writeXml(xmlNode* node)
{
  xmlNodeSetContent(node, (const xmlChar*)(const char*)_value);
}

