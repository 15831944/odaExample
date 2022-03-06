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
#include <RxValue.h>
#include <OdIdsPropertyTypeLocation.h>
#include <OdAnsiString.h>
#include <OdIdsIdsValue.h>
#include <OdXmlRestriction.h>

class ODIDS_DLLEXPORT OdIdsPropertyType : public OdRxObject
{
  OdRxValue _location;
  OdIdsIdsValuePtr _propertyset;
  OdIdsIdsValuePtr _name;
  OdIdsIdsValuePtr _value;
public:
ODRX_DECLARE_MEMBERS(OdIdsPropertyType);
  OdIdsPropertyType();
  ~OdIdsPropertyType();
  void readXml(xmlNode* node);
  void writeXml(xmlNode* node);
  bool getLocation(OdIdsPropertyTypeLocation& result) { 
    if (OdIdsPropertyTypeLocation* r = rxvalue_cast<OdIdsPropertyTypeLocation>(&_location)) {
      result = *r;
      return true;
    }
    return false;
  }
  void setLocation(OdIdsPropertyTypeLocation value) { _location = value; }
  OdIdsIdsValue* getPropertyset() { return _propertyset; }
  const OdIdsIdsValue* getPropertyset() const { return _propertyset; }
  void setPropertyset(OdIdsIdsValue* val) { _propertyset = val; }
  OdIdsIdsValue* getName() { return _name; }
  const OdIdsIdsValue* getName() const { return _name; }
  void setName(OdIdsIdsValue* val) { _name = val; }
  OdIdsIdsValue* getValue() { return _value; }
  const OdIdsIdsValue* getValue() const { return _value; }
  void setValue(OdIdsIdsValue* val) { _value = val; }
};

typedef OdSmartPtr<OdIdsPropertyType> OdIdsPropertyTypePtr;
typedef OdArray<OdIdsPropertyTypePtr> OdIdsPropertyTypePtrArray;

ODRX_DECLARE_VALUE_TYPE(OdIdsPropertyTypePtrArray, ODIDS_DLLEXPORT)
