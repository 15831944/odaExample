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
#include <OdIdsRequirementsTypeClassification.h>

ODRX_CONS_DEFINE_MEMBERS(OdIdsRequirementsTypeClassification, OdIdsClassificationType, RXIMPL_CONSTR);

static OdRxValueType* g_valOdIdsRequirementsTypeClassificationPtrArray = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsRequirementsTypeClassificationPtrArray>::value() throw ()
{
  if (g_valOdIdsRequirementsTypeClassificationPtrArray == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsRequirementsTypeClassificationPtrArray == 0)
      g_valOdIdsRequirementsTypeClassificationPtrArray = new OdRxNonBlittableType<OdIdsRequirementsTypeClassificationPtrArray>((const OdChar*)L"OdIdsRequirementsTypeClassificationPtrArray", 0);
  }
  return *g_valOdIdsRequirementsTypeClassificationPtrArray;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsRequirementsTypeClassificationPtrArray>::del()
{
  if (g_valOdIdsRequirementsTypeClassificationPtrArray)
  {
    odrxClassDictionary()->remove(L"OdIdsRequirementsTypeClassificationPtrArray");
    delete g_valOdIdsRequirementsTypeClassificationPtrArray;
    g_valOdIdsRequirementsTypeClassificationPtrArray = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsRequirementsTypeClassificationPtrArray const &val) throw () : m_type(OdRxValueType::Desc<OdIdsRequirementsTypeClassificationPtrArray>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsRequirementsTypeClassificationPtrArray>::subEqualTo(const void* a, const void* b) const { return *(OdIdsRequirementsTypeClassificationPtrArray*)a == *(OdIdsRequirementsTypeClassificationPtrArray*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsRequirementsTypeClassificationPtrArray>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

OdIdsRequirementsTypeClassification::OdIdsRequirementsTypeClassification(){}

OdIdsRequirementsTypeClassification::~OdIdsRequirementsTypeClassification(){}

void OdIdsRequirementsTypeClassification::readXml(xmlNode* node)
{
  OdIdsClassificationType::readXml(node);
  if (xmlAttrPtr uri_attribute = xmlHasProp(node, (const xmlChar*)"uri"))
    _uri = OdAnsiString((const char*)uri_attribute->children->children->content, CP_UTF_8);
  if (xmlAttrPtr use_attribute = xmlHasProp(node, (const xmlChar*)"use"))
    _use = OdAnsiString((const char*)use_attribute->children->children->content, CP_UTF_8);
  for (xmlNode* child = node->children; child; child = child->next)
  {
    if (child->type == XML_TEXT_NODE || child->type == XML_COMMENT_NODE)
      continue;
    if (child->type != XML_ELEMENT_NODE)
      throw "Invalid xml structure at reading <OdIdsRequirementsTypeClassification> ";
    if (xmlStrcmp(child->name, (const xmlChar*)"instructions") == 0)
    {
      _instructions = OdAnsiString((const char*)child->children->content, CP_UTF_8);
    }
  }
}

void OdIdsRequirementsTypeClassification::writeXml(xmlNode* node)
{
  OdIdsClassificationType::writeXml(node);
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

