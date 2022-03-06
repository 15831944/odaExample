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
#include <RxValue.h>
#include <OdIdsSpecificationTypeNecessity.h>
#include <OdIdsApplicabilityType.h>
#include <OdIdsEntityType.h>
#include <OdIdsIdsValue.h>
#include <OdXmlRestriction.h>
#include <OdIdsClassificationType.h>
#include <OdIdsClassificationTypeLocation.h>
#include <OdIdsApplicabilityTypeProperty.h>
#include <OdIdsPropertyType.h>
#include <OdIdsPropertyTypeLocation.h>
#include <OdIdsApplicabilityTypeMaterial.h>
#include <OdIdsMaterialType.h>
#include <OdIdsMaterialTypeLocation.h>
#include <OdIdsRequirementsType.h>
#include <OdIdsRequirementsTypeClassification.h>
#include <OdIdsUse.h>
#include <OdIdsRequirementsTypeProperty.h>
#include <OdIdsRequirementsTypeMaterial.h>

class ODIDS_DLLEXPORT OdIdsSpecificationType : public OdRxObject
{
  OdRxValue _name;
  OdRxValue _necessity;
  OdIdsApplicabilityTypePtr _applicability;
  OdIdsRequirementsTypePtr _requirements;
public:
ODRX_DECLARE_MEMBERS(OdIdsSpecificationType);
  OdIdsSpecificationType();
  ~OdIdsSpecificationType();
  void readXml(xmlNode* node);
  void writeXml(xmlNode* node);
  bool getName(OdAnsiString& result) { 
    if (OdAnsiString* r = rxvalue_cast<OdAnsiString>(&_name)) {
      result = *r;
      return true;
    }
    return false;
  }
  void setName(OdAnsiString value) { _name = value; }
  bool getNecessity(OdIdsSpecificationTypeNecessity& result) { 
    if (OdIdsSpecificationTypeNecessity* r = rxvalue_cast<OdIdsSpecificationTypeNecessity>(&_necessity)) {
      result = *r;
      return true;
    }
    return false;
  }
  void setNecessity(OdIdsSpecificationTypeNecessity value) { _necessity = value; }
  OdIdsApplicabilityType* getApplicability() { return _applicability; }
  const OdIdsApplicabilityType* getApplicability() const { return _applicability; }
  void setApplicability(OdIdsApplicabilityType* val) { _applicability = val; }
  OdIdsRequirementsType* getRequirements() { return _requirements; }
  const OdIdsRequirementsType* getRequirements() const { return _requirements; }
  void setRequirements(OdIdsRequirementsType* val) { _requirements = val; }
};

typedef OdSmartPtr<OdIdsSpecificationType> OdIdsSpecificationTypePtr;
typedef OdArray<OdIdsSpecificationTypePtr> OdIdsSpecificationTypePtrArray;

ODRX_DECLARE_VALUE_TYPE(OdIdsSpecificationTypePtrArray, ODIDS_DLLEXPORT)
