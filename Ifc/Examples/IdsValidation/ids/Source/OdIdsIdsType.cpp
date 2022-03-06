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
#include <OdIdsIdsType.h>

ODRX_CONS_DEFINE_MEMBERS(OdIdsIdsType, OdRxObject, RXIMPL_CONSTR);

static OdRxValueType* g_valOdIdsIdsTypePtrArray = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsIdsTypePtrArray>::value() throw ()
{
  if (g_valOdIdsIdsTypePtrArray == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsIdsTypePtrArray == 0)
      g_valOdIdsIdsTypePtrArray = new OdRxNonBlittableType<OdIdsIdsTypePtrArray>((const OdChar*)L"OdIdsIdsTypePtrArray", 0);
  }
  return *g_valOdIdsIdsTypePtrArray;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsIdsTypePtrArray>::del()
{
  if (g_valOdIdsIdsTypePtrArray)
  {
    odrxClassDictionary()->remove(L"OdIdsIdsTypePtrArray");
    delete g_valOdIdsIdsTypePtrArray;
    g_valOdIdsIdsTypePtrArray = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsIdsTypePtrArray const &val) throw () : m_type(OdRxValueType::Desc<OdIdsIdsTypePtrArray>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsIdsTypePtrArray>::subEqualTo(const void* a, const void* b) const { return *(OdIdsIdsTypePtrArray*)a == *(OdIdsIdsTypePtrArray*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsIdsTypePtrArray>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

OdIdsIdsType::OdIdsIdsType(){}

OdIdsIdsType::~OdIdsIdsType(){}

void OdIdsIdsType::readXml(xmlNode* node)
{
  for (xmlNode* child = node->children; child; child = child->next)
  {
    if (child->type == XML_TEXT_NODE || child->type == XML_COMMENT_NODE)
      continue;
    if (child->type != XML_ELEMENT_NODE)
      throw "Invalid xml structure at reading <OdIdsIdsType> ";
    if (xmlStrcmp(child->name, (const xmlChar*)"specification") == 0)
    {
      OdIdsSpecificationTypePtr specification_tmp = OdIdsSpecificationType::createObject();
      specification_tmp->readXml(child);
      _specification.append(specification_tmp);
    }
  }
}

void OdIdsIdsType::writeXml(xmlNode* node)
{
  for (OdIdsSpecificationTypePtrArray::iterator i = _specification.begin(); i != _specification.end(); ++i)
  {
    xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"specification");
    xmlAddChild(node, child);
    (*i)->writeXml(child);
  }
}

