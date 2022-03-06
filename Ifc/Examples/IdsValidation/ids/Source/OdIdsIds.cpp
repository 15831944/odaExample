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
#include <OdIdsIds.h>

ODRX_CONS_DEFINE_MEMBERS(OdIdsIds, OdIdsIdsType, RXIMPL_CONSTR);

static OdRxValueType* g_valOdIdsIdsPtrArray = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsIdsPtrArray>::value() throw ()
{
  if (g_valOdIdsIdsPtrArray == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsIdsPtrArray == 0)
      g_valOdIdsIdsPtrArray = new OdRxNonBlittableType<OdIdsIdsPtrArray>((const OdChar*)L"OdIdsIdsPtrArray", 0);
  }
  return *g_valOdIdsIdsPtrArray;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsIdsPtrArray>::del()
{
  if (g_valOdIdsIdsPtrArray)
  {
    odrxClassDictionary()->remove(L"OdIdsIdsPtrArray");
    delete g_valOdIdsIdsPtrArray;
    g_valOdIdsIdsPtrArray = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsIdsPtrArray const &val) throw () : m_type(OdRxValueType::Desc<OdIdsIdsPtrArray>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsIdsPtrArray>::subEqualTo(const void* a, const void* b) const { return *(OdIdsIdsPtrArray*)a == *(OdIdsIdsPtrArray*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsIdsPtrArray>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

OdIdsIds::OdIdsIds(){}

OdIdsIds::~OdIdsIds(){}

void OdIdsIds::readXml(xmlNode* node)
{
  OdIdsIdsType::readXml(node);
  for (xmlNode* child = node->children; child; child = child->next)
  {
    if (child->type == XML_TEXT_NODE || child->type == XML_COMMENT_NODE)
      continue;
    if (child->type != XML_ELEMENT_NODE)
      throw "Invalid xml structure at reading <OdIdsIds> ";
    if (xmlStrcmp(child->name, (const xmlChar*)"info") == 0)
    {
      _info = OdIdsInfo::createObject();
      _info->readXml(child);
    }
  }
}

void OdIdsIds::writeXml(xmlNode* node)
{
  OdIdsIdsType::writeXml(node);
  if (!_info.isNull())
  {
    xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"info");
    xmlAddChild(node, child);
    _info->writeXml(child);
  }
}

