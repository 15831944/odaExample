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
#include <OdIdsAuthor.h>

static OdRxValueType* g_valOdIdsAuthor = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsAuthor>::value() throw ()
{
  if (g_valOdIdsAuthor == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsAuthor == 0)
      g_valOdIdsAuthor = new OdRxNonBlittableType<OdIdsAuthor>((const OdChar*)L"OdIdsAuthor", 0);
  }
  return *g_valOdIdsAuthor;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsAuthor>::del()
{
  if (g_valOdIdsAuthor)
  {
    odrxClassDictionary()->remove(L"OdIdsAuthor");
    delete g_valOdIdsAuthor;
    g_valOdIdsAuthor = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsAuthor const &val) throw () : m_type(OdRxValueType::Desc<OdIdsAuthor>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsAuthor>::subEqualTo(const void* a, const void* b) const { return *(OdIdsAuthor*)a == *(OdIdsAuthor*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsAuthor>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

static OdRxValueType* g_valOdIdsAuthorArray = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsAuthorArray>::value() throw ()
{
  if (g_valOdIdsAuthorArray == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsAuthorArray == 0)
      g_valOdIdsAuthorArray = new OdRxNonBlittableType<OdIdsAuthorArray>((const OdChar*)L"OdIdsAuthorArray", 0);
  }
  return *g_valOdIdsAuthorArray;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsAuthorArray>::del()
{
  if (g_valOdIdsAuthorArray)
  {
    odrxClassDictionary()->remove(L"OdIdsAuthorArray");
    delete g_valOdIdsAuthorArray;
    g_valOdIdsAuthorArray = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsAuthorArray const &val) throw () : m_type(OdRxValueType::Desc<OdIdsAuthorArray>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsAuthorArray>::subEqualTo(const void* a, const void* b) const { return *(OdIdsAuthorArray*)a == *(OdIdsAuthorArray*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsAuthorArray>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

OdIdsAuthor::OdIdsAuthor(){}

OdIdsAuthor::~OdIdsAuthor(){}

void OdIdsAuthor::readXml(xmlNode* node)
{
  _value = OdAnsiString((const char*)node->children->content, CP_UTF_8);
}

void OdIdsAuthor::writeXml(xmlNode* node)
{
  xmlNodeSetContent(node, (const xmlChar*)(const char*)_value);
}

