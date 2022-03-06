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
#ifndef __DGELEMENTPROPS__H__
#define __DGELEMENTPROPS__H__

#include "DgProperties.h"
#include "OdTimeStamp.h"

// Class OdDgElement properties. Category "Raw Data":

// No category.

/* 1 - ElementId        */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgElement,ElementId,OdDgElementId,"",1,"Element id value");

// Category "Raw Data"

/* 1 - ODAUniqueID      */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgElement, ODAUniqueID, OdUInt64, "Raw Data",1, "Handle value of element");
/* 2 - ElementType      */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgElement,ElementType,OdDgElement::ElementTypes,"Raw Data",2,"Base element type");
/* 3 - ElementSubType   */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgElement,ElementSubType,OdUInt8,"Raw Data",3,"Element subentity type");
/* 4 - ModificationTime */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgElement,ModificationTime,OdTimeStamp,"Raw Data",4,"Last modification time");
/* 5 - New              */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgElement,New,bool,"Raw Data",5,"Is new element");
/* 6 - Modified         */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgElement,Modified,bool,"Raw Data",6,"Is element modified");
/* 7 - Locked           */ ODRX_DECLARE_RX_PROPERTY(OdDgElement,Locked,bool,"Raw Data",7,"Is element locked", "");

// Category "General"

/* 1 - Name             */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgElement, Name, OdString, "General",1, "Default name of element");

// no category.

/*1 - ItemTypeInstances */ ODRX_DECLARE_RX_CPLX_PROPERTY_UNIONTYPE_INDEXED(OdDgElement, ECClassInstances, OdRxObjectPtr, "",1, "ECClass instance array", "OdDgECClassInstance");

// Category "EC Data"

/** \details
  RxProperty for representation of OdDgElement simple meta-data properties.
  
  <group Dg_Extension_Classes>
*/
struct OdDgElementECProperty : OdRxProperty
{
  static OdRxMemberPtr createObject(const OdString& strName, const OdDgECPropertyInstance& propInstance, const OdDgECClassReference& classRef, OdUInt32 uWeight, const OdRxClass* owner);
  virtual OdResult subGetValue(const OdRxObject* pO, OdRxValue& value) const ODRX_OVERRIDE;
  virtual OdResult subSetValue(OdRxObject* pO, const OdRxValue& value) const ODRX_OVERRIDE;
  virtual bool isReadOnly(const OdRxObject* pO) const ODRX_OVERRIDE { return false; };

private:
  OdString               m_propertyName;
  OdDgECClassReference   m_classRef;
};

/** \details
  RxProperty for representation of OdDgElement meta-data array properties.
  
  <group Dg_Extension_Classes>
*/
struct OdDgElementArrayECProperty : OdRxIndexedProperty
{
  static OdRxMemberPtr createObject(const OdString& strName, const OdDgECPropertyInstance& propInstance, const OdDgECClassReference& classRef, OdUInt32 uWeight, const OdRxClass* owner);
  virtual OdResult subGetValue(const OdRxObject* pO, int index, OdRxValue& value) const ODRX_OVERRIDE;
  virtual OdResult subSetValue(OdRxObject* pO, int index, const OdRxValue& value) const ODRX_OVERRIDE;
  virtual OdResult subInsertValue(OdRxObject* pO, int index, const OdRxValue& value) const ODRX_OVERRIDE;
  virtual OdResult subRemoveValue(OdRxObject* pO, int index) const ODRX_OVERRIDE;
  virtual OdRxValueIteratorPtr subNewValueIterator(const OdRxObject* pO) const ODRX_OVERRIDE;
  virtual OdResult subTryGetCount(const OdRxObject* pO, int& count) const ODRX_OVERRIDE;

private:
  OdString               m_propertyName;
  OdDgECClassReference   m_classRef;
};

#endif // __DGELEMENTPROPS__H__
