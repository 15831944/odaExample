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

// This file is generated automatically.

#ifndef _IFC2X_FINAL_IFCWORKORDER_AUTO_IMPL_H
#define _IFC2X_FINAL_IFCWORKORDER_AUTO_IMPL_H

#include "IfcProjectOrderAutoImpl.h"
#include "IfcDateAndTimeAutoImpl.h"
#include "IfcCostScheduleAutoImpl.h"
#include "IfcWorkPlanAutoImpl.h"
#include "IfcCostValueAutoImpl.h"

/** \details
  The namespace contains schema-dependent classes, definitions and sub routines
  for work with IFC2X_FINAL express schema definitions.
*/
namespace OdIfc2x_final {

class IFC2X_FINAL_EXPORT IfcWorkOrder : public IfcProjectOrder
{
  //DOM-IGNORE-BEGIN
  OD_EXP_DECLARE_MEMBERS(OdIfc2x_final::IfcWorkOrder);
  //DOM-IGNORE-END

public:


  //
  // OdDAI early binding accessors
  //

  const OdAnsiString& getProductDescription() const;
  void setProductDescription(const OdAnsiString& ProductDescription);
  const OdAnsiString& getShortJobDescription() const;
  void setShortJobDescription(const OdAnsiString& ShortJobDescription);
  const OdAnsiString& getLongJobDescription() const;
  void setLongJobDescription(const OdAnsiString& LongJobDescription);
  const OdAnsiString& getWorkTypeRequested() const;
  void setWorkTypeRequested(const OdAnsiString& WorkTypeRequested);
  const OdAnsiString& getContractualType() const;
  void setContractualType(const OdAnsiString& ContractualType);
  void getIfNotAccomplished(OdArray<OdAnsiString >& IfNotAccomplished) const;
  OdDAI::OdAnsiStringList& ifNotAccomplished();
  const OdDAIObjectId& getRequestedStartTime() const;
  void setRequestedStartTime(const OdDAIObjectId& RequestedStartTime);
  const OdDAIObjectId& getRequestedFinishTime() const;
  void setRequestedFinishTime(const OdDAIObjectId& RequestedFinishTime);
  const OdDAIObjectId& getActualStartTime() const;
  void setActualStartTime(const OdDAIObjectId& ActualStartTime);
  const OdDAIObjectId& getActualFinishTime() const;
  void setActualFinishTime(const OdDAIObjectId& ActualFinishTime);
  const OdDAIObjectId& getCostEstimate() const;
  void setCostEstimate(const OdDAIObjectId& CostEstimate);
  const OdDAIObjectId& getWorkPlan() const;
  void setWorkPlan(const OdDAIObjectId& WorkPlan);
  IfcWorkOrderStatusEnum getStatus() const;
  void setStatus(IfcWorkOrderStatusEnum Status);
  void getWorkOrderRiskType(OdArray<OdDAI::Enum >& WorkOrderRiskType) const;
  OdDAI::Set<OdDAI::Enum>& workOrderRiskType();
  void getPerformedBy(OdDAIObjectIds& PerformedBy) const;
  OdDAI::OdDAIObjectIdSet& performedBy();
  const OdDAIObjectId& getActualCost() const;
  void setActualCost(const OdDAIObjectId& ActualCost);


public:
  IfcWorkOrder();

  /** \details
  Reads object's data from the specified filer.
  \param rdFiler [in] Pointer to a filer from which to read the data.
  \returns
  A value of OdResult type that contains the result of the method execution.
  */
  virtual OdResult inFields(OdDAI::OdSpfFilerBase* rdFiler);

  /** \details
  Writes object's data the the specified filer.
  \param wrFiler [in] Pointer to a filer to which to write the data.
  \returns
  A value of OdResult type that contains the result of the method execution.
  */
  virtual OdResult outFields(OdDAI::OdSpfFilerBase* wrFiler);

  /** \details
  Returns a type of a class instance.
  \returns
  Pointer to the <link OdDAI__Entity, OdDAI::Entity> type that determines an entity definition within a schema.
  */
  virtual OdDAI::Entity* getInstanceType() const;

  /** \details
  Returns an attribute value for the specified attribute name.
  \param attrName [in] Name of an attribute to query.
  \returns
  OdRxValue object that represents a generic variant type value.
  */
  virtual OdRxValue getAttr(const char * attrName) const;

  /** \details
  Resets a value for the specified attribute.
  \param explicitAttrName [in] Explicit name of the attribute to reset.
  */
  virtual void unsetAttr(const char * explicitAttrName);

  /** \details
  Checks whether the specified attribute is set.
  \param explicitAttrName [in] Explicit name of the attribute to test.
  \returns
  true if the specified attribute is set, false otherwise.
  */
  virtual bool testAttr(const char * explicitAttrName) const;

  /** \details
  Sets the specified attribute with a given value.
  \param explicitAttrName [in] Explicit name of the attribute to set.
  \param val [in] Value to set.
  \returns
  true if the value is successfully set for the specified attribute, false otherwise.
  */
  virtual bool putAttr(const char * explicitAttrName, const OdRxValue &val);

  /** \details
  Checks whether the specified instance is the object derived from or belongs to this class.
  \param entityType [in] Entity to check.
  \returns
  true if the specified instance is the object derived from or belongs to this class, false otherwise.
  */
  virtual bool isKindOf(OdIfc::OdIfcEntityType entityType) const;

  /** \details
  Returns the type of this entity.
  \returns
  A value of the <link OdIfc__OdIfcEntityType, OdIfc::OdIfcEntityType> type that represents type of this entity.
  */
  virtual OdIfc::OdIfcEntityType type() const;

  /** \details
  Returns an attribute value for the specified attribute definition.
  \param attrDef [in] Attribute definition to query.
  \returns
  OdRxValue object that represents a generic variant type value.
  */
  virtual OdRxValue getAttr(const OdIfc::OdIfcAttribute attrDef) const;

  /** \details
  Resets a value for the specified attribute.
  \param explicitAttrDef [in] Explicit definition that represents an attribute to reset.
  */
  virtual void unsetAttr(const OdIfc::OdIfcAttribute explicitAttrDef);

  /** \details
  Checks whether the specified attribute is set.
  \param explicitAttrDef [in] Attribute definition to test.
  \returns
  true if the specified attribute is set, false otherwise.
  */
  virtual bool testAttr(const OdIfc::OdIfcAttribute explicitAttrDef) const;

  /** \details
  Sets the specified attribute with a given value.
  \param explicitAttrDef [in] Explicit attribute definition to set.
  \param val [in] Value to set.
  \returns
  true if the value is successfully set for the specified attribute, false otherwise.
  */
  virtual bool putAttr(const OdIfc::OdIfcAttribute explicitAttrDef, const OdRxValue &val);

protected:
  // Fields declaration: 
  OdAnsiString m_ProductDescription;   // IfcLabel  [optional]
  OdAnsiString m_ShortJobDescription;   // IfcLabel
  OdAnsiString m_LongJobDescription;   // IfcLabel  [optional]
  OdAnsiString m_WorkTypeRequested;   // IfcLabel  [optional]
  OdAnsiString m_ContractualType;   // IfcLabel  [optional]
  OdDAI::OdAnsiStringList m_IfNotAccomplished; // LIST [1:?] of IfcLabel [optional]

  OdDAIObjectId m_RequestedStartTime;   // IfcDateAndTime  [optional]
  OdDAIObjectId m_RequestedFinishTime;   // IfcDateAndTime  [optional]
  OdDAIObjectId m_ActualStartTime;   // IfcDateAndTime  [optional]
  OdDAIObjectId m_ActualFinishTime;   // IfcDateAndTime  [optional]
  OdDAIObjectId m_CostEstimate;   // IfcCostSchedule  [optional]
  OdDAIObjectId m_WorkPlan;   // IfcWorkPlan  [optional]
  OdDAI::Enum m_Status;   // IfcWorkOrderStatusEnum
  OdDAI::Set<OdDAI::Enum> m_WorkOrderRiskType; // SET [1:?] of IfcWorkOrderRiskTypeEnum [optional]

  OdDAI::OdDAIObjectIdSet m_PerformedBy; // SET [1:?] of IfcPerson
  OdDAIObjectId m_ActualCost;   // IfcCostValue  [optional]
};

/** \details
  A data type that represents a smart pointer to a <link OdIfc2x_final::IfcWorkOrder, IfcWorkOrder> object.
*/
typedef OdSmartPtr<IfcWorkOrder> IfcWorkOrderPtr;

} // namespace

#endif // _IFC2X_FINAL_IFCWORKORDER_AUTO_IMPL_H
