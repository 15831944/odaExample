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
#include <OdIdsSpecificationType.h>

ODRX_CONS_DEFINE_MEMBERS(OdIdsSpecificationType, OdRxObject, RXIMPL_CONSTR);

static OdRxValueType* g_valOdIdsSpecificationTypePtrArray = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsSpecificationTypePtrArray>::value() throw ()
{
  if (g_valOdIdsSpecificationTypePtrArray == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsSpecificationTypePtrArray == 0)
      g_valOdIdsSpecificationTypePtrArray = new OdRxNonBlittableType<OdIdsSpecificationTypePtrArray>((const OdChar*)L"OdIdsSpecificationTypePtrArray", 0);
  }
  return *g_valOdIdsSpecificationTypePtrArray;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsSpecificationTypePtrArray>::del()
{
  if (g_valOdIdsSpecificationTypePtrArray)
  {
    odrxClassDictionary()->remove(L"OdIdsSpecificationTypePtrArray");
    delete g_valOdIdsSpecificationTypePtrArray;
    g_valOdIdsSpecificationTypePtrArray = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsSpecificationTypePtrArray const &val) throw () : m_type(OdRxValueType::Desc<OdIdsSpecificationTypePtrArray>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsSpecificationTypePtrArray>::subEqualTo(const void* a, const void* b) const { return *(OdIdsSpecificationTypePtrArray*)a == *(OdIdsSpecificationTypePtrArray*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsSpecificationTypePtrArray>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

OdIdsSpecificationType::OdIdsSpecificationType(){}

OdIdsSpecificationType::~OdIdsSpecificationType(){}

void OdIdsSpecificationType::readXml(xmlNode* node)
{
  if (xmlAttrPtr name_attribute = xmlHasProp(node, (const xmlChar*)"name"))
    _name = OdAnsiString((const char*)name_attribute->children->content, CP_UTF_8);
  if (xmlAttrPtr necessity_attribute = xmlHasProp(node, (const xmlChar*)"necessity"))
    _necessity = OdAnsiString((const char*)necessity_attribute->children->content, CP_UTF_8);
  for (xmlNode* child = node->children; child; child = child->next)
  {
    if (child->type == XML_TEXT_NODE || child->type == XML_COMMENT_NODE)
      continue;
    if (child->type != XML_ELEMENT_NODE)
      throw "Invalid xml structure at reading <OdIdsSpecificationType> ";
    if (xmlStrcmp(child->name, (const xmlChar*)"applicability") == 0)
    {
      _applicability = OdIdsApplicabilityType::createObject();
      _applicability->readXml(child);
    }
    if (xmlStrcmp(child->name, (const xmlChar*)"requirements") == 0)
    {
      _requirements = OdIdsRequirementsType::createObject();
      _requirements->readXml(child);
    }
  }
}

void OdIdsSpecificationType::writeXml(xmlNode* node)
{
  if (!_name.isEmpty())
    xmlNewNsProp(node, 0, (const xmlChar*)"name", (const xmlChar*)(const char*)*rxvalue_cast<OdAnsiString>(&_name));
  if (!_necessity.isEmpty())
    xmlNewNsProp(node, 0, (const xmlChar*)"necessity", (const xmlChar*)(const char*)(*rxvalue_cast<OdIdsSpecificationTypeNecessity>(&_necessity)).getValue());
  if (!_applicability.isNull())
  {
    xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"applicability");
    xmlAddChild(node, child);
    _applicability->writeXml(child);
  }
  if (!_requirements.isNull())
  {
    xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"requirements");
    xmlAddChild(node, child);
    _requirements->writeXml(child);
  }
}

