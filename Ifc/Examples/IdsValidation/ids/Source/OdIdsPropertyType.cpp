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
#include <OdIdsPropertyType.h>

ODRX_CONS_DEFINE_MEMBERS(OdIdsPropertyType, OdRxObject, RXIMPL_CONSTR);

static OdRxValueType* g_valOdIdsPropertyTypePtrArray = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsPropertyTypePtrArray>::value() throw ()
{
  if (g_valOdIdsPropertyTypePtrArray == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsPropertyTypePtrArray == 0)
      g_valOdIdsPropertyTypePtrArray = new OdRxNonBlittableType<OdIdsPropertyTypePtrArray>((const OdChar*)L"OdIdsPropertyTypePtrArray", 0);
  }
  return *g_valOdIdsPropertyTypePtrArray;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsPropertyTypePtrArray>::del()
{
  if (g_valOdIdsPropertyTypePtrArray)
  {
    odrxClassDictionary()->remove(L"OdIdsPropertyTypePtrArray");
    delete g_valOdIdsPropertyTypePtrArray;
    g_valOdIdsPropertyTypePtrArray = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsPropertyTypePtrArray const &val) throw () : m_type(OdRxValueType::Desc<OdIdsPropertyTypePtrArray>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsPropertyTypePtrArray>::subEqualTo(const void* a, const void* b) const { return *(OdIdsPropertyTypePtrArray*)a == *(OdIdsPropertyTypePtrArray*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsPropertyTypePtrArray>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

OdIdsPropertyType::OdIdsPropertyType(){}

OdIdsPropertyType::~OdIdsPropertyType(){}

void OdIdsPropertyType::readXml(xmlNode* node)
{
  if (xmlAttrPtr location_attribute = xmlHasProp(node, (const xmlChar*)"location"))
    _location = OdAnsiString((const char*)location_attribute->children->content, CP_UTF_8);
  for (xmlNode* child = node->children; child; child = child->next)
  {
    if (child->type == XML_TEXT_NODE || child->type == XML_COMMENT_NODE)
      continue;
    if (child->type != XML_ELEMENT_NODE)
      throw "Invalid xml structure at reading <OdIdsPropertyType> ";
    if (xmlStrcmp(child->name, (const xmlChar*)"propertyset") == 0)
    {
      _propertyset = OdIdsIdsValue::createObject();
      _propertyset->readXml(child);
    }
    if (xmlStrcmp(child->name, (const xmlChar*)"name") == 0)
    {
      _name = OdIdsIdsValue::createObject();
      _name->readXml(child);
    }
    if (xmlStrcmp(child->name, (const xmlChar*)"value") == 0)
    {
      _value = OdIdsIdsValue::createObject();
      _value->readXml(child);
    }
  }
}

void OdIdsPropertyType::writeXml(xmlNode* node)
{
  if (!_location.isEmpty())
    xmlNewNsProp(node, 0, (const xmlChar*)"location", (const xmlChar*)(const char*)(*rxvalue_cast<OdIdsPropertyTypeLocation>(&_location)).getValue());
  if (!_propertyset.isNull())
  {
    xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"propertyset");
    xmlAddChild(node, child);
    _propertyset->writeXml(child);
  }
  if (!_name.isNull())
  {
    xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"name");
    xmlAddChild(node, child);
    _name->writeXml(child);
  }
  if (!_value.isNull())
  {
    xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"value");
    xmlAddChild(node, child);
    _value->writeXml(child);
  }
}

