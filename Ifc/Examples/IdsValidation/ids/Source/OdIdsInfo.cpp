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
#include <OdIdsInfo.h>

ODRX_CONS_DEFINE_MEMBERS(OdIdsInfo, OdRxObject, RXIMPL_CONSTR);

static OdRxValueType* g_valOdIdsInfoPtrArray = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdIdsInfoPtrArray>::value() throw ()
{
  if (g_valOdIdsInfoPtrArray == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdIdsInfoPtrArray == 0)
      g_valOdIdsInfoPtrArray = new OdRxNonBlittableType<OdIdsInfoPtrArray>((const OdChar*)L"OdIdsInfoPtrArray", 0);
  }
  return *g_valOdIdsInfoPtrArray;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdIdsInfoPtrArray>::del()
{
  if (g_valOdIdsInfoPtrArray)
  {
    odrxClassDictionary()->remove(L"OdIdsInfoPtrArray");
    delete g_valOdIdsInfoPtrArray;
    g_valOdIdsInfoPtrArray = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdIdsInfoPtrArray const &val) throw () : m_type(OdRxValueType::Desc<OdIdsInfoPtrArray>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdIdsInfoPtrArray>::subEqualTo(const void* a, const void* b) const { return *(OdIdsInfoPtrArray*)a == *(OdIdsInfoPtrArray*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdIdsInfoPtrArray>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

OdIdsInfo::OdIdsInfo(){}

OdIdsInfo::~OdIdsInfo(){}

void OdIdsInfo::readXml(xmlNode* node)
{
  _value.clear();
  for (xmlNode* child = node->children; child; child = child->next)
  {
    if (child->type == XML_TEXT_NODE || child->type == XML_COMMENT_NODE)
      continue;
    if (child->type != XML_ELEMENT_NODE)
      throw "Invalid xml structure at reading <OdIdsInfo> ";
    if (xmlStrcmp(child->name, (const xmlChar*)"ifcversion") == 0)
    {
      _choiceTypeSelector.append(IFCVERSION);
      OdIdsIfcversion e;
      e.readXml(child);
      _value.append(OdRxValue(e));
    }
    else if (xmlStrcmp(child->name, (const xmlChar*)"description") == 0)
    {
      _choiceTypeSelector.append(DESCRIPTION);
      OdAnsiString e = OdAnsiString((const char*)child->children->content, CP_UTF_8);
      _value.append(OdRxValue(e));
    }
    else if (xmlStrcmp(child->name, (const xmlChar*)"author") == 0)
    {
      _choiceTypeSelector.append(AUTHOR);
      OdIdsAuthor e;
      e.readXml(child);
      _value.append(OdRxValue(e));
    }
    else if (xmlStrcmp(child->name, (const xmlChar*)"copyright") == 0)
    {
      _choiceTypeSelector.append(COPYRIGHT);
      OdAnsiString e = OdAnsiString((const char*)child->children->content, CP_UTF_8);
      _value.append(OdRxValue(e));
    }
    else if (xmlStrcmp(child->name, (const xmlChar*)"version") == 0)
    {
      _choiceTypeSelector.append(VERSION);
      OdAnsiString e = OdAnsiString((const char*)child->children->content, CP_UTF_8);
      _value.append(OdRxValue(e));
    }
    else if (xmlStrcmp(child->name, (const xmlChar*)"date") == 0)
    {
      _choiceTypeSelector.append(DATE);
      OdAnsiString e = OdAnsiString((const char*)child->children->content, CP_UTF_8);
      _value.append(OdRxValue(e));
    }
    else if (xmlStrcmp(child->name, (const xmlChar*)"purpose") == 0)
    {
      _choiceTypeSelector.append(PURPOSE);
      OdAnsiString e = OdAnsiString((const char*)child->children->content, CP_UTF_8);
      _value.append(OdRxValue(e));
    }
    else if (xmlStrcmp(child->name, (const xmlChar*)"milestone") == 0)
    {
      _choiceTypeSelector.append(MILESTONE);
      OdAnsiString e = OdAnsiString((const char*)child->children->content, CP_UTF_8);
      _value.append(OdRxValue(e));
    }
  }
}

void OdIdsInfo::writeXml(xmlNode* node)
{
  for (unsigned int i = 0; i < _choiceTypeSelector.size(); ++i)
  {
    switch (_choiceTypeSelector[i])
    {
      case IFCVERSION:
      {
        xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"ifcversion");
        xmlAddChild(node, child);
        rxvalue_cast<OdIdsIfcversion>(&_value[i])->writeXml(child);
      }
      break;
      case DESCRIPTION:
      {
        xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"description");
        xmlAddChild(node, child);
        xmlNodeSetContent(child, (const xmlChar*)(const char*)*rxvalue_cast<OdAnsiString>(&_value[i]));
      }
      break;
      case AUTHOR:
      {
        xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"author");
        xmlAddChild(node, child);
        rxvalue_cast<OdIdsAuthor>(&_value[i])->writeXml(child);
      }
      break;
      case COPYRIGHT:
      {
        xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"copyright");
        xmlAddChild(node, child);
        xmlNodeSetContent(child, (const xmlChar*)(const char*)*rxvalue_cast<OdAnsiString>(&_value[i]));
      }
      break;
      case VERSION:
      {
        xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"version");
        xmlAddChild(node, child);
        xmlNodeSetContent(child, (const xmlChar*)(const char*)*rxvalue_cast<OdAnsiString>(&_value[i]));
      }
      break;
      case DATE:
      {
        xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"date");
        xmlAddChild(node, child);
        xmlNodeSetContent(child, (const xmlChar*)(const char*)*rxvalue_cast<OdAnsiString>(&_value[i]));
      }
      break;
      case PURPOSE:
      {
        xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"purpose");
        xmlAddChild(node, child);
        xmlNodeSetContent(child, (const xmlChar*)(const char*)*rxvalue_cast<OdAnsiString>(&_value[i]));
      }
      break;
      case MILESTONE:
      {
        xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"milestone");
        xmlAddChild(node, child);
        xmlNodeSetContent(child, (const xmlChar*)(const char*)*rxvalue_cast<OdAnsiString>(&_value[i]));
      }
      break;
    }
  }
}

