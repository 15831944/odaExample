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
#include <OdIdsIfcversion.h>
#include <OdAnsiString.h>
#include <OdIdsAuthor.h>

class ODIDS_DLLEXPORT OdIdsInfo : public OdRxObject
{
public:
  enum ChoiceTypeSelector {
    NONE,
    IFCVERSION,
    DESCRIPTION,
    AUTHOR,
    COPYRIGHT,
    VERSION,
    DATE,
    PURPOSE,
    MILESTONE,
  };
private:
  OdArray<OdRxValue> _value;
  OdArray<ChoiceTypeSelector> _choiceTypeSelector;
public:
ODRX_DECLARE_MEMBERS(OdIdsInfo);
  OdIdsInfo();
  ~OdIdsInfo();
  void readXml(xmlNode* node);
  void writeXml(xmlNode* node);
  unsigned int getNumberOfChoices() { return _value.size(); }
  ChoiceTypeSelector getChoiceType(int i) { return _choiceTypeSelector[i]; }
  OdRxValue getRawvalue(int i) { return _value[i]; }
  OdIdsIfcversion* getIfcversion(int i) { return rxvalue_cast<OdIdsIfcversion>(&_value[i]); }
  const OdIdsIfcversion* getIfcversion(int i) const { return rxvalue_cast<OdIdsIfcversion>(&_value[i]); }
  void setIfcversion(int i, OdIdsIfcversion* val) { _value[i] = *val; }
  OdAnsiString* getDescription(int i) { return rxvalue_cast<OdAnsiString>(&_value[i]); }
  const OdAnsiString* getDescription(int i) const { return rxvalue_cast<OdAnsiString>(&_value[i]); }
  void setDescription(int i, OdAnsiString* val) { _value[i] = *val; }
  OdIdsAuthor* getAuthor(int i) { return rxvalue_cast<OdIdsAuthor>(&_value[i]); }
  const OdIdsAuthor* getAuthor(int i) const { return rxvalue_cast<OdIdsAuthor>(&_value[i]); }
  void setAuthor(int i, OdIdsAuthor* val) { _value[i] = *val; }
  OdAnsiString* getCopyright(int i) { return rxvalue_cast<OdAnsiString>(&_value[i]); }
  const OdAnsiString* getCopyright(int i) const { return rxvalue_cast<OdAnsiString>(&_value[i]); }
  void setCopyright(int i, OdAnsiString* val) { _value[i] = *val; }
  OdAnsiString* getVersion(int i) { return rxvalue_cast<OdAnsiString>(&_value[i]); }
  const OdAnsiString* getVersion(int i) const { return rxvalue_cast<OdAnsiString>(&_value[i]); }
  void setVersion(int i, OdAnsiString* val) { _value[i] = *val; }
  OdAnsiString* getDate(int i) { return rxvalue_cast<OdAnsiString>(&_value[i]); }
  const OdAnsiString* getDate(int i) const { return rxvalue_cast<OdAnsiString>(&_value[i]); }
  void setDate(int i, OdAnsiString* val) { _value[i] = *val; }
  OdAnsiString* getPurpose(int i) { return rxvalue_cast<OdAnsiString>(&_value[i]); }
  const OdAnsiString* getPurpose(int i) const { return rxvalue_cast<OdAnsiString>(&_value[i]); }
  void setPurpose(int i, OdAnsiString* val) { _value[i] = *val; }
  OdAnsiString* getMilestone(int i) { return rxvalue_cast<OdAnsiString>(&_value[i]); }
  const OdAnsiString* getMilestone(int i) const { return rxvalue_cast<OdAnsiString>(&_value[i]); }
  void setMilestone(int i, OdAnsiString* val) { _value[i] = *val; }
};

typedef OdSmartPtr<OdIdsInfo> OdIdsInfoPtr;
typedef OdArray<OdIdsInfoPtr> OdIdsInfoPtrArray;

ODRX_DECLARE_VALUE_TYPE(OdIdsInfoPtrArray, ODIDS_DLLEXPORT)
