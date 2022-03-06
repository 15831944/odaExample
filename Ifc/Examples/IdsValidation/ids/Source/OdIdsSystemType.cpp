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
#include <OdIdsSystemType.h>

ODRX_CONS_DEFINE_MEMBERS(OdIdsSystemType, OdRxObject, RXIMPL_CONSTR);

static OdRxValueType* g_valOdIdsSystemTypePtrArray = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsSystemTypePtrArray>::value() throw ()
{
  if (g_valOdIdsSystemTypePtrArray == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsSystemTypePtrArray == 0)
      g_valOdIdsSystemTypePtrArray = new OdRxNonBlittableType<OdIdsSystemTypePtrArray>((const OdChar*)L"OdIdsSystemTypePtrArray", 0);
  }
  return *g_valOdIdsSystemTypePtrArray;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsSystemTypePtrArray>::del()
{
  if (g_valOdIdsSystemTypePtrArray)
  {
    odrxClassDictionary()->remove(L"OdIdsSystemTypePtrArray");
    delete g_valOdIdsSystemTypePtrArray;
    g_valOdIdsSystemTypePtrArray = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsSystemTypePtrArray const &val) throw () : m_type(OdRxValueType::Desc<OdIdsSystemTypePtrArray>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsSystemTypePtrArray>::subEqualTo(const void* a, const void* b) const { return *(OdIdsSystemTypePtrArray*)a == *(OdIdsSystemTypePtrArray*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsSystemTypePtrArray>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

OdIdsSystemType::OdIdsSystemType(){}

OdIdsSystemType::~OdIdsSystemType(){}

void OdIdsSystemType::readXml(xmlNode* node)
{
  if (xmlAttrPtr href_attribute = xmlHasProp(node, (const xmlChar*)"href"))
    _href = OdAnsiString((const char*)href_attribute->children->children->content, CP_UTF_8);
}

void OdIdsSystemType::writeXml(xmlNode* node)
{
  if (!_href.isEmpty())
    xmlNewNsProp(node, 0, (const xmlChar*)"href", (const xmlChar*)(const char*)*rxvalue_cast<OdAnsiString>(&_href));
}

