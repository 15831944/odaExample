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
#pragma once

#include <OdIds.h>
#include <OdAnsiString.h>
#include <OdXmlRestriction.h>

class ODIDS_DLLEXPORT OdIdsIdsValue : public OdRxObject
{
public:
  enum ChoiceTypeSelector {
    NONE,
    SIMPLEVALUE,
    RESTRICTION,
  };
private:
  OdRxValue _value;
  ChoiceTypeSelector _choiceTypeSelector;
public:
ODRX_DECLARE_MEMBERS(OdIdsIdsValue);
  OdIdsIdsValue();
  ~OdIdsIdsValue();
  void readXml(xmlNode* node);
  void writeXml(xmlNode* node);
  ChoiceTypeSelector getChoiceType() { return _choiceTypeSelector; }
  OdRxValue getRawvalue() { return _value; }
  OdAnsiString* getSimpleValue() { return rxvalue_cast<OdAnsiString>(&_value); }
  const OdAnsiString* getSimpleValue() const { return rxvalue_cast<OdAnsiString>(&_value); }
  void setSimpleValue(OdAnsiString val) { _value = val; }
  OdArray<OdXmlRestriction>* getRestriction() { return rxvalue_cast<OdArray<OdXmlRestriction>>(&_value); }
  const OdArray<OdXmlRestriction>* getRestriction() const { return rxvalue_cast<OdArray<OdXmlRestriction>>(&_value); }
  void setRestriction(const OdArray<OdXmlRestriction>& val) { _value = val; }
};

typedef OdSmartPtr<OdIdsIdsValue> OdIdsIdsValuePtr;
typedef OdArray<OdIdsIdsValuePtr> OdIdsIdsValuePtrArray;

ODRX_DECLARE_VALUE_TYPE(OdIdsIdsValuePtrArray, ODIDS_DLLEXPORT)
