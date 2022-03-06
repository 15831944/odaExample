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
#include <OdIdsRequirementsTypeProperty.h>

ODRX_CONS_DEFINE_MEMBERS(OdIdsRequirementsTypeProperty, OdIdsPropertyType, RXIMPL_CONSTR);

static OdRxValueType* g_valOdIdsRequirementsTypePropertyPtrArray = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsRequirementsTypePropertyPtrArray>::value() throw ()
{
  if (g_valOdIdsRequirementsTypePropertyPtrArray == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsRequirementsTypePropertyPtrArray == 0)
      g_valOdIdsRequirementsTypePropertyPtrArray = new OdRxNonBlittableType<OdIdsRequirementsTypePropertyPtrArray>((const OdChar*)L"OdIdsRequirementsTypePropertyPtrArray", 0);
  }
  return *g_valOdIdsRequirementsTypePropertyPtrArray;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsRequirementsTypePropertyPtrArray>::del()
{
  if (g_valOdIdsRequirementsTypePropertyPtrArray)
  {
    odrxClassDictionary()->remove(L"OdIdsRequirementsTypePropertyPtrArray");
    delete g_valOdIdsRequirementsTypePropertyPtrArray;
    g_valOdIdsRequirementsTypePropertyPtrArray = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsRequirementsTypePropertyPtrArray const &val) throw () : m_type(OdRxValueType::Desc<OdIdsRequirementsTypePropertyPtrArray>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsRequirementsTypePropertyPtrArray>::subEqualTo(const void* a, const void* b) const { return *(OdIdsRequirementsTypePropertyPtrArray*)a == *(OdIdsRequirementsTypePropertyPtrArray*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsRequirementsTypePropertyPtrArray>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

OdIdsRequirementsTypeProperty::OdIdsRequirementsTypeProperty(){}

OdIdsRequirementsTypeProperty::~OdIdsRequirementsTypeProperty(){}

void OdIdsRequirementsTypeProperty::readXml(xmlNode* node)
{
  OdIdsPropertyType::readXml(node);
  if (xmlAttrPtr uri_attribute = xmlHasProp(node, (const xmlChar*)"uri"))
    _uri = OdAnsiString((const char*)uri_attribute->children->content, CP_UTF_8);
  if (xmlAttrPtr use_attribute = xmlHasProp(node, (const xmlChar*)"use"))
    _use = OdAnsiString((const char*)use_attribute->children->content, CP_UTF_8);
  for (xmlNode* child = node->children; child; child = child->next)
  {
    if (child->type == XML_TEXT_NODE || child->type == XML_COMMENT_NODE)
      continue;
    if (child->type != XML_ELEMENT_NODE)
      throw "Invalid xml structure at reading <OdIdsRequirementsTypeProperty> ";
    if (xmlStrcmp(child->name, (const xmlChar*)"instructions") == 0)
    {
      _instructions = OdAnsiString((const char*)child->children->content, CP_UTF_8);
    }
  }
}

void OdIdsRequirementsTypeProperty::writeXml(xmlNode* node)
{
  OdIdsPropertyType::writeXml(node);
  if (!_uri.isEmpty())
    xmlNewNsProp(node, 0, (const xmlChar*)"uri", (const xmlChar*)(const char*)*rxvalue_cast<OdAnsiString>(&_uri));
  if (!_use.isEmpty())
    xmlNewNsProp(node, 0, (const xmlChar*)"use", (const xmlChar*)(const char*)(*rxvalue_cast<OdIdsUse>(&_use)).getValue());
  if (!_instructions.isEmpty())
  {
    xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"instructions");
    xmlAddChild(node, child);
    xmlNodeSetContent(child, (const xmlChar*)(const char*)*rxvalue_cast<OdAnsiString>(&_instructions));
  }
}

