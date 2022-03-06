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
#include <OdIdsRequirementsTypeClassification.h>
#include <OdIdsClassificationType.h>
#include <OdIdsClassificationTypeLocation.h>
#include <OdIdsUse.h>
#include <OdIdsRequirementsTypeProperty.h>
#include <OdIdsPropertyType.h>
#include <OdIdsPropertyTypeLocation.h>
#include <OdIdsRequirementsTypeMaterial.h>
#include <OdIdsMaterialType.h>
#include <OdIdsMaterialTypeLocation.h>

class ODIDS_DLLEXPORT OdIdsRequirementsType : public OdRxObject
{
  OdIdsEntityTypePtr _entity;
  OdIdsRequirementsTypeClassificationPtr _classification;
  OdIdsRequirementsTypePropertyPtrArray _property;
  OdIdsRequirementsTypeMaterialPtr _material;
public:
ODRX_DECLARE_MEMBERS(OdIdsRequirementsType);
  OdIdsRequirementsType();
  ~OdIdsRequirementsType();
  void readXml(xmlNode* node);
  void writeXml(xmlNode* node);
  OdIdsEntityType* getEntity() { return _entity; }
  const OdIdsEntityType* getEntity() const { return _entity; }
  void setEntity(OdIdsEntityType* val) { _entity = val; }
  OdIdsRequirementsTypeClassification* getClassification() { return _classification; }
  const OdIdsRequirementsTypeClassification* getClassification() const { return _classification; }
  void setClassification(OdIdsRequirementsTypeClassification* val) { _classification = val; }
  OdIdsRequirementsTypePropertyPtrArray& getProperty() { return _property; }
  const OdIdsRequirementsTypePropertyPtrArray& getProperty() const { return _property; }
  void setProperty(const OdIdsRequirementsTypePropertyPtrArray& val) { _property = val; }
  OdIdsRequirementsTypeMaterial* getMaterial() { return _material; }
  const OdIdsRequirementsTypeMaterial* getMaterial() const { return _material; }
  void setMaterial(OdIdsRequirementsTypeMaterial* val) { _material = val; }
};

typedef OdSmartPtr<OdIdsRequirementsType> OdIdsRequirementsTypePtr;
typedef OdArray<OdIdsRequirementsTypePtr> OdIdsRequirementsTypePtrArray;

ODRX_DECLARE_VALUE_TYPE(OdIdsRequirementsTypePtrArray, ODIDS_DLLEXPORT)
