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
#include <OdIdsEntityType.h>
#include <OdIdsIdsValue.h>
#include <OdAnsiString.h>
#include <OdXmlRestriction.h>
#include <OdIdsClassificationType.h>
#include <OdIdsClassificationTypeLocation.h>
#include <OdIdsApplicabilityTypeProperty.h>
#include <OdIdsPropertyType.h>
#include <OdIdsPropertyTypeLocation.h>
#include <OdIdsApplicabilityTypeMaterial.h>
#include <OdIdsMaterialType.h>
#include <OdIdsMaterialTypeLocation.h>

class ODIDS_DLLEXPORT OdIdsApplicabilityType : public OdRxObject
{
  OdIdsEntityTypePtr _entity;
  OdIdsClassificationTypePtr _classification;
  OdIdsApplicabilityTypePropertyPtrArray _property;
  OdIdsApplicabilityTypeMaterialPtr _material;
public:
ODRX_DECLARE_MEMBERS(OdIdsApplicabilityType);
  OdIdsApplicabilityType();
  ~OdIdsApplicabilityType();
  void readXml(xmlNode* node);
  void writeXml(xmlNode* node);
  OdIdsEntityType* getEntity() { return _entity; }
  const OdIdsEntityType* getEntity() const { return _entity; }
  void setEntity(OdIdsEntityType* val) { _entity = val; }
  OdIdsClassificationType* getClassification() { return _classification; }
  const OdIdsClassificationType* getClassification() const { return _classification; }
  void setClassification(OdIdsClassificationType* val) { _classification = val; }
  OdIdsApplicabilityTypePropertyPtrArray& getProperty() { return _property; }
  const OdIdsApplicabilityTypePropertyPtrArray& getProperty() const { return _property; }
  void setProperty(const OdIdsApplicabilityTypePropertyPtrArray& val) { _property = val; }
  OdIdsApplicabilityTypeMaterial* getMaterial() { return _material; }
  const OdIdsApplicabilityTypeMaterial* getMaterial() const { return _material; }
  void setMaterial(OdIdsApplicabilityTypeMaterial* val) { _material = val; }
};

typedef OdSmartPtr<OdIdsApplicabilityType> OdIdsApplicabilityTypePtr;
typedef OdArray<OdIdsApplicabilityTypePtr> OdIdsApplicabilityTypePtrArray;

ODRX_DECLARE_VALUE_TYPE(OdIdsApplicabilityTypePtrArray, ODIDS_DLLEXPORT)
