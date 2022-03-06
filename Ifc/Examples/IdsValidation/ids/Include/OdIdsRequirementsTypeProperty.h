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
#include <OdIdsPropertyType.h>
#include <OdAnsiString.h>
#include <RxValue.h>
#include <OdIdsUse.h>
#include <OdIdsPropertyTypeLocation.h>
#include <OdIdsIdsValue.h>
#include <OdXmlRestriction.h>

class ODIDS_DLLEXPORT OdIdsRequirementsTypeProperty : public OdIdsPropertyType
{
  OdRxValue _uri;
  OdRxValue _use;
  OdRxValue _instructions;
public:
ODRX_DECLARE_MEMBERS(OdIdsRequirementsTypeProperty);
  OdIdsRequirementsTypeProperty();
  ~OdIdsRequirementsTypeProperty();
  void readXml(xmlNode* node);
  void writeXml(xmlNode* node);
  bool getUri(OdAnsiString& result) { 
    if (OdAnsiString* r = rxvalue_cast<OdAnsiString>(&_uri)) {
      result = *r;
      return true;
    }
    return false;
  }
  void setUri(OdAnsiString value) { _uri = value; }
  bool getUse(OdIdsUse& result) { 
    if (OdIdsUse* r = rxvalue_cast<OdIdsUse>(&_use)) {
      result = *r;
      return true;
    }
    return false;
  }
  void setUse(OdIdsUse value) { _use = value; }
  OdAnsiString* getInstructions() { return rxvalue_cast<OdAnsiString>(&_instructions); }
  void setInstructions(OdAnsiString val) { _instructions = val; }
};

typedef OdSmartPtr<OdIdsRequirementsTypeProperty> OdIdsRequirementsTypePropertyPtr;
typedef OdArray<OdIdsRequirementsTypePropertyPtr> OdIdsRequirementsTypePropertyPtrArray;

ODRX_DECLARE_VALUE_TYPE(OdIdsRequirementsTypePropertyPtrArray, ODIDS_DLLEXPORT)
