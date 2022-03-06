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
#include <OdXmlRestriction.h>
#include <RxValueTypeUtil.h>
#include <RxDictionary.h>

#if !defined(_WIN32)

inline char*
i2a(unsigned i, char* a, unsigned r) {
  if (i / r > 0) a = i2a(i / r, a, r);
  *a = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[i % r];
  return a + 1;
}

/**
 Transforms integer i into an ascii string and stores the result in a;
 string is encoded in the base indicated by r.
 @param i Number to be converted
 @param a String result
 @param r Base of value; must be in the range 2 - 36
 @return Returns a
*/
inline char*
_itoa(int i, char* a, int r) {
  r = ((r < 2) || (r > 36)) ? 10 : r;
  if (i < 0) {
    *a = '-';
    *i2a(-i, a + 1, r) = 0;
  }
  else *i2a(i, a, r) = 0;
  return a;
}

#endif // !defined(_WIN32)


OdXmlRestriction::OdXmlRestriction()
{
  whiteSpace = UNDEFINED;
}

static void readIntValue(xmlNode* child, OdRxValue& value, const char* valueName)
{
  if (xmlStrcmp(child->name, (const xmlChar*)valueName) == 0)
  {
    if (xmlAttrPtr value_attribute = xmlHasProp(child, (const xmlChar*)"value"))
    {
      value = atoi((const char*)value_attribute->children->content);
    }
  }
}

bool OdXmlRestriction::readXml(xmlNodePtr node)
{
  if (xmlStrcmp(node->name, (const xmlChar*)"restriction") != 0)
    return false;
  if (xmlAttrPtr base_attribute = xmlHasProp(node, (const xmlChar*)"base"))
    base = OdAnsiString((const char*)base_attribute->children->content, CP_UTF_8);
  for (xmlNode* child = node->children; child; child = child->next)
  {
    if (child->type == XML_TEXT_NODE)
      continue;
    if (child->type != XML_ELEMENT_NODE)
      return false;
    readIntValue(node, minExclusive, "minExclusive");
    readIntValue(node, minInclusive, "minInclusive");
    readIntValue(node, maxExclusive, "maxExclusive");
    readIntValue(node, maxInclusive, "maxInclusive");
    readIntValue(node, totalDigits, "totalDigits");
    readIntValue(node, fractionDigits, "fractionDigits");
    readIntValue(node, length, "length");
    readIntValue(node, minLength, "minLength");
    readIntValue(node, maxLength, "maxLength");
    
    if (xmlStrcmp(child->name, (const xmlChar*)"pattern") == 0)
    {
      if (xmlAttrPtr value_attribute = xmlHasProp(child, (const xmlChar*)"value"))
      {
        pattern = OdAnsiString((const char*)value_attribute->children->content, CP_UTF_8);
      }
    }

    if (xmlStrcmp(child->name, (const xmlChar*)"whiteSpace") == 0)
    {
      if (xmlAttrPtr value_attribute = xmlHasProp(child, (const xmlChar*)"value"))
      {
        if (xmlStrcmp(value_attribute->children->content, (const xmlChar*)"preserve") == 0)
          whiteSpace = PRESERVE;
        if (xmlStrcmp(value_attribute->children->content, (const xmlChar*)"replace") == 0)
          whiteSpace = REPLACE;
        if (xmlStrcmp(value_attribute->children->content, (const xmlChar*)"collapse") == 0)
          whiteSpace = COLLAPSE;
      }
    }

    if (xmlStrcmp(child->name, (const xmlChar*)"enumeration") == 0)
    {
      if (xmlAttrPtr value_attribute = xmlHasProp(child, (const xmlChar*)"value"))
      {
        enumeration.append(OdAnsiString((const char*)value_attribute->children->content, CP_UTF_8));
      }
    }
  }
  return true;
}

static void addIntValue(xmlNodePtr node, const OdRxValue& value, const char* valueName)
{
  if (const int* v = rxvalue_cast<int>(&value))
  {
    xmlNodePtr child = xmlNewNode(0, (const xmlChar*)valueName);
    xmlAddChild(node, child);
    char buf[30] = { 0 };
    _itoa(*v, buf, 10);
    xmlNewNsProp(child, 0, (const xmlChar*)"value", (const xmlChar*)buf);
  }
}

static void cleanup(xmlNodePtr node)
{
  for (xmlNode* child = node->children; child;)
  {
    if (child->type == XML_ELEMENT_NODE &&
      (xmlStrcmp(child->name, (const xmlChar*)"minExclusive") == 0
        || xmlStrcmp(child->name, (const xmlChar*)"minInclusive") == 0
        || xmlStrcmp(child->name, (const xmlChar*)"maxExclusive") == 0
        || xmlStrcmp(child->name, (const xmlChar*)"maxInclusive") == 0
        || xmlStrcmp(child->name, (const xmlChar*)"totalDigits") == 0
        || xmlStrcmp(child->name, (const xmlChar*)"fractionDigits") == 0
        || xmlStrcmp(child->name, (const xmlChar*)"length") == 0
        || xmlStrcmp(child->name, (const xmlChar*)"minLength") == 0
        || xmlStrcmp(child->name, (const xmlChar*)"maxLength") == 0
        || xmlStrcmp(child->name, (const xmlChar*)"enumeration") == 0
        || xmlStrcmp(child->name, (const xmlChar*)"whiteSpace") == 0
        || xmlStrcmp(child->name, (const xmlChar*)"pattern") == 0
        ))
    {
      xmlNodePtr toRemove = child;
      child = child->next;
      xmlUnlinkNode(toRemove);
      xmlFreeNode(toRemove);
    }
    else
    {
      child = child->next;
    }
  }
}

void OdXmlRestriction::writeXml(xmlNodePtr node) const
{
  cleanup(node);
  if (!base.isEmpty())
    xmlNewNsProp(node, 0, (const xmlChar*)"base", (const xmlChar*)(const char*)base);
  addIntValue(node, minExclusive, "minExclusive");
  addIntValue(node, minInclusive, "minInclusive");
  addIntValue(node, maxExclusive, "maxExclusive");
  addIntValue(node, maxInclusive, "maxInclusive");
  addIntValue(node, totalDigits, "totalDigits");
  addIntValue(node, fractionDigits, "fractionDigits");
  addIntValue(node, length, "length");
  addIntValue(node, minLength, "minLength");
  addIntValue(node, maxLength, "maxLength");
  for (unsigned i = 0; i < enumeration.size(); ++i)
  {
    xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"enumeration");
    xmlAddChild(node, child);
    xmlNewNsProp(child, 0, (const xmlChar*)"value", (const xmlChar*)(const char*)enumeration[i]);
  }
  if (whiteSpace != UNDEFINED)
  {
    xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"whiteSpace");
    xmlAddChild(node, child);
    switch (whiteSpace)
    {
    case PRESERVE:
      xmlNewNsProp(child, 0, (const xmlChar*)"value", (const xmlChar*)"preserve");
      break;
    case REPLACE:
      xmlNewNsProp(child, 0, (const xmlChar*)"value", (const xmlChar*)"replace");
      break;
    case COLLAPSE:
      xmlNewNsProp(child, 0, (const xmlChar*)"value", (const xmlChar*)"collapse");
      break;
    }
  }
  if (!pattern.isEmpty())
  {
    xmlNodePtr child = xmlNewNode(0, (const xmlChar*)"pattern");
    xmlAddChild(node, child);
    xmlNewNsProp(child, 0, (const xmlChar*)"value", (const xmlChar*)(const char*)pattern);
  }
}

static OdRxValueType* g_valOdXmlRestriction = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdXmlRestriction>::value() throw ()
{
  if (g_valOdXmlRestriction == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdXmlRestriction == 0)
      g_valOdXmlRestriction = new OdRxNonBlittableType<OdXmlRestriction>((const OdChar*)L"OdXmlRestriction", 0);
  }
  return *g_valOdXmlRestriction;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdXmlRestriction>::del()
{
  if (g_valOdXmlRestriction)
  {
    odrxClassDictionary()->remove(L"OdXmlRestriction");
    delete g_valOdXmlRestriction;
    g_valOdXmlRestriction = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdXmlRestriction const& val) throw () : m_type(OdRxValueType::Desc<OdXmlRestriction>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdXmlRestriction>::subEqualTo(const void* a, const void* b) const { return *(OdXmlRestriction*)a == *(OdXmlRestriction*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdXmlRestriction>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

static OdRxValueType* g_valOdXmlRestrictionArray = 0;

ODIDS_DLLEXPORT const OdRxValueType& OdRxValueType::Desc<OdXmlRestrictionArray>::value() throw ()
{
  if (g_valOdXmlRestrictionArray == 0)
  {
    static OdMutex m;
    TD_AUTOLOCK(m);
    if (g_valOdXmlRestrictionArray == 0)
      g_valOdXmlRestrictionArray = new OdRxNonBlittableType<OdXmlRestrictionArray>((const OdChar*)L"OdXmlRestrictionArray", 0);
  }
  return *g_valOdXmlRestrictionArray;
}

ODIDS_DLLEXPORT void OdRxValueType::Desc <OdXmlRestrictionArray>::del()
{
  if (g_valOdXmlRestrictionArray)
  {
    odrxClassDictionary()->remove(L"OdXmlRestrictionArray");
    delete g_valOdXmlRestrictionArray;
    g_valOdXmlRestrictionArray = 0;
  }
}

template <> ODIDS_DLLEXPORT OdRxValue::OdRxValue(OdXmlRestrictionArray const& val) throw () : m_type(OdRxValueType::Desc<OdXmlRestrictionArray>::value())
{
  initNonBlittable(val);
}

template<> ODIDS_DLLEXPORT bool OdRxNonBlittableType<OdXmlRestrictionArray>::subEqualTo(const void* a, const void* b) const { return *(OdXmlRestrictionArray*)a == *(OdXmlRestrictionArray*)b; }

template<> ODIDS_DLLEXPORT OdString OdRxNonBlittableType<OdXmlRestrictionArray>::subToString(const void* instance, OdRxValueType::StringFormat) const
{
  if (!instance)
    throw OdError(L"Value instance is null");
  return OdString::kEmpty;
}

bool OdXmlRestriction::operator==(const OdXmlRestriction& other) const
{
  return minExclusive == other.minExclusive 
    && base == other.base
    && minInclusive == other.minInclusive
    && maxExclusive == other.maxExclusive
    && maxInclusive == other.maxInclusive
    && totalDigits == other.totalDigits
    && fractionDigits == other.fractionDigits
    && length == other.length
    && minLength == other.minLength
    && maxLength == other.maxLength
    && enumeration == other.enumeration
    && pattern == other.pattern
    ;
}

