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
#include <OdIdsRequirementsType.h>

ODRX_CONS_DEFINE_MEMBERS(OdIdsRequirementsType, OdRxObject, RXIMPL_CONSTR);

static OdRxValueType* g_valOdIdsRequirementsTypePtrArray = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsRequirementsTypePtrArray>::value() throw ()
{
  if (g_valOdIdsRequirementsTypePtrArray == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsRequirementsTypePtrArray == 0)
      g_valOdIdsRequirementsTypePtrArray = new OdRxNonBlittableType<OdIdsRequirementsTypePtrArray>((const OdChar*)L"OdIdsRequirementsTypePtrArray", 0);
  }
  return *g_valOdIdsRequirementsTypePtrArray;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsRequirementsTypePtrArray>::del()
{
  if (g_valOdIdsRequirementsTypePtrArray)
  {
    odrxClassDictionary()->remove(L"OdIdsRequirementsTypePtrArray");
    delete g_valOdIdsRequirementsTypePtrArray;
    g_valOdIdsRequirementsTypePtrArray = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsRequirementsTypePtrArray const &val) throw () : m_type(OdRxValueType::Desc<OdIdsRequirementsTypePtrArray>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsRequirementsTypePtrArray>::subEqualTo(const void* a, const void* b) const { return *(OdIdsRequirementsTypePtrArray*)a == *(OdIdsRequirementsTypePtrArray*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsRequirementsTypePtrArray>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

OdIdsRequirementsType::OdIdsRequirementsType(){}

OdIdsRequirementsType::~OdIdsRequirementsType(){}

void OdIdsRequirementsType::readXml(xmlNode* node)
{
  for (xmlNode* child = node->children; child; child = child->next)
  {
    if (child->type == XML_TEXT_NODE || child->type == XML_COMMENT_NODE)
      continue;
    if (child->type != XML_ELEMENT_NODE)
      throw "Invalid xml structure at reading <OdIdsRequirementsType> ";
    if (xmlStrcmp(child->name, (const xmlChar*)"entity") == 0)
    {
      _entity = OdIdsEntityType::createObject();
      _entity->readXml(child);
    }
    if (xmlStrcmp(child->name, (const xmlChar*)"classification") == 0)
    {
      _classification = OdIdsRequirementsTypeClassification::createObject();
      _classification->readXml(child);
    }
    if (xmlStrcmp(child->name, (const xmlChar*)"property") == 0)
    {
      OdIdsRequirementsTypePropertyPtr property_tmp = OdIdsRequirementsTypeProperty::createObject();
      property_tmp->readXml(child);
      _property.append(property_tmp);
    }
    if (xmlStrcmp(child->name, (const xmlChar*)"material") == 0)
    {
      _material = OdIdsRequirementsTypeMaterial::createObject();
      _material->readXml(child);
    }
  }
}

void OdIdsRequirementsType::writeXml(xmlNode* node)
{
  if (!_entity.isNull())
  {
    xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"entity");
    xmlAddChild(node, child);
    _entity->writeXml(child);
  }
  if (!_classification.isNull())
  {
    xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"classification");
    xmlAddChild(node, child);
    _classification->writeXml(child);
  }
  for (OdIdsRequirementsTypePropertyPtrArray::iterator i = _property.begin(); i != _property.end(); ++i)
  {
    xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"property");
    xmlAddChild(node, child);
    (*i)->writeXml(child);
  }
  if (!_material.isNull())
  {
    xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"material");
    xmlAddChild(node, child);
    _material->writeXml(child);
  }
}

