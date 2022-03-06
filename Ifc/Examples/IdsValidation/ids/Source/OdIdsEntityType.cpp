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
#include <OdIdsEntityType.h>

ODRX_CONS_DEFINE_MEMBERS(OdIdsEntityType, OdRxObject, RXIMPL_CONSTR);

static OdRxValueType* g_valOdIdsEntityTypePtrArray = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsEntityTypePtrArray>::value() throw ()
{
  if (g_valOdIdsEntityTypePtrArray == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsEntityTypePtrArray == 0)
      g_valOdIdsEntityTypePtrArray = new OdRxNonBlittableType<OdIdsEntityTypePtrArray>((const OdChar*)L"OdIdsEntityTypePtrArray", 0);
  }
  return *g_valOdIdsEntityTypePtrArray;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsEntityTypePtrArray>::del()
{
  if (g_valOdIdsEntityTypePtrArray)
  {
    odrxClassDictionary()->remove(L"OdIdsEntityTypePtrArray");
    delete g_valOdIdsEntityTypePtrArray;
    g_valOdIdsEntityTypePtrArray = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsEntityTypePtrArray const &val) throw () : m_type(OdRxValueType::Desc<OdIdsEntityTypePtrArray>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsEntityTypePtrArray>::subEqualTo(const void* a, const void* b) const { return *(OdIdsEntityTypePtrArray*)a == *(OdIdsEntityTypePtrArray*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsEntityTypePtrArray>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

OdIdsEntityType::OdIdsEntityType(){}

OdIdsEntityType::~OdIdsEntityType(){}

void OdIdsEntityType::readXml(xmlNode* node)
{
  for (xmlNode* child = node->children; child; child = child->next)
  {
    if (child->type == XML_TEXT_NODE || child->type == XML_COMMENT_NODE)
      continue;
    if (child->type != XML_ELEMENT_NODE)
      throw "Invalid xml structure at reading <OdIdsEntityType> ";
    if (xmlStrcmp(child->name, (const xmlChar*)"name") == 0)
    {
      _name = OdIdsIdsValue::createObject();
      _name->readXml(child);
    }
    if (xmlStrcmp(child->name, (const xmlChar*)"predefinedtype") == 0)
    {
      _predefinedtype = OdIdsIdsValue::createObject();
      _predefinedtype->readXml(child);
    }
  }
}

void OdIdsEntityType::writeXml(xmlNode* node)
{
  if (!_name.isNull())
  {
    xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"name");
    xmlAddChild(node, child);
    _name->writeXml(child);
  }
  if (!_predefinedtype.isNull())
  {
    xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"predefinedtype");
    xmlAddChild(node, child);
    _predefinedtype->writeXml(child);
  }
}

