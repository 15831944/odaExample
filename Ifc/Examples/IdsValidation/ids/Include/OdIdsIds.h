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
#include <OdIdsIdsType.h>
#include <OdIdsInfo.h>
#include <OdIdsIfcversion.h>
#include <OdAnsiString.h>
#include <OdIdsAuthor.h>
#include <OdIdsSpecificationType.h>
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

class ODIDS_DLLEXPORT OdIdsIds : public OdIdsIdsType
{
  OdIdsInfoPtr _info;
public:
ODRX_DECLARE_MEMBERS(OdIdsIds);
  OdIdsIds();
  ~OdIdsIds();
  void readXml(xmlNode* node);
  void writeXml(xmlNode* node);
  OdIdsInfo* getInfo() { return _info; }
  const OdIdsInfo* getInfo() const { return _info; }
  void setInfo(OdIdsInfo* val) { _info = val; }
};

typedef OdSmartPtr<OdIdsIds> OdIdsIdsPtr;
typedef OdArray<OdIdsIdsPtr> OdIdsIdsPtrArray;

ODRX_DECLARE_VALUE_TYPE(OdIdsIdsPtrArray, ODIDS_DLLEXPORT)
