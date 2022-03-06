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
#include <OdIdsIdsValue.h>

ODRX_CONS_DEFINE_MEMBERS(OdIdsIdsValue, OdRxObject, RXIMPL_CONSTR);

static OdRxValueType* g_valOdIdsIdsValuePtrArray = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsIdsValuePtrArray>::value() throw ()
{
  if (g_valOdIdsIdsValuePtrArray == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsIdsValuePtrArray == 0)
      g_valOdIdsIdsValuePtrArray = new OdRxNonBlittableType<OdIdsIdsValuePtrArray>((const OdChar*)L"OdIdsIdsValuePtrArray", 0);
  }
  return *g_valOdIdsIdsValuePtrArray;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsIdsValuePtrArray>::del()
{
  if (g_valOdIdsIdsValuePtrArray)
  {
    odrxClassDictionary()->remove(L"OdIdsIdsValuePtrArray");
    delete g_valOdIdsIdsValuePtrArray;
    g_valOdIdsIdsValuePtrArray = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsIdsValuePtrArray const &val) throw () : m_type(OdRxValueType::Desc<OdIdsIdsValuePtrArray>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsIdsValuePtrArray>::subEqualTo(const void* a, const void* b) const { return *(OdIdsIdsValuePtrArray*)a == *(OdIdsIdsValuePtrArray*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsIdsValuePtrArray>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

OdIdsIdsValue::OdIdsIdsValue(){}

OdIdsIdsValue::~OdIdsIdsValue(){}

void OdIdsIdsValue::readXml(xmlNode* node)
{
  _value = OdRxValue();
  for (xmlNode* child = node->children; child; child = child->next)
  {
    if (child->type == XML_TEXT_NODE || child->type == XML_COMMENT_NODE)
      continue;
    if (child->type != XML_ELEMENT_NODE)
      throw "Invalid xml structure at reading <OdIdsIdsValue> ";
    if (xmlStrcmp(child->name, (const xmlChar*)"simpleValue") == 0)
    {
      _choiceTypeSelector = SIMPLEVALUE;
      OdAnsiString e = OdAnsiString((const char*)child->children->content, CP_UTF_8);
      _value = e;
    }
    else if (xmlStrcmp(child->name, (const xmlChar*)"restriction") == 0)
    {
      _choiceTypeSelector = RESTRICTION;
      OdXmlRestriction e;
      e.readXml(child);
      if (_value.isEmpty())
        _value = OdArray<OdXmlRestriction>();
      rxvalue_cast<OdArray<OdXmlRestriction>>(&_value)->append(e);
    }
  }
}

void OdIdsIdsValue::writeXml(xmlNode* node)
{
    switch (_choiceTypeSelector)
    {
      case SIMPLEVALUE:
      {
        xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"simpleValue");
        xmlAddChild(node, child);
        xmlNodeSetContent(child, (const xmlChar*)(const char*)*rxvalue_cast<OdAnsiString>(&_value));
      }
      break;
      case RESTRICTION:
      {
        if (OdArray<OdXmlRestriction>* a = rxvalue_cast<OdArray<OdXmlRestriction> >(&_value))
        {
          for (unsigned i = 0; i < a->size(); ++i)
          {
            xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"restriction");
            xmlAddChild(node, child);
            a->getAt(i).writeXml(child);
          }
        }
      }
      break;
    }
}

