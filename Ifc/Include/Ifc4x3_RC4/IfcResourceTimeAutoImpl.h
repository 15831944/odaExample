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

#ifndef _IFC4X3_RC4_IFCRESOURCETIME_AUTO_IMPL_H
#define _IFC4X3_RC4_IFCRESOURCETIME_AUTO_IMPL_H

#include "IfcSchedulingTimeAutoImpl.h"

/** \details
  The namespace contains schema-dependent classes, definitions and sub routines
  for work with IFC4X3_RC4 express schema definitions.
*/
namespace OdIfc4x3_rc4 {

class IFC4X3_RC4_EXPORT IfcResourceTime : public IfcSchedulingTime
{
  //DOM-IGNORE-BEGIN
  OD_EXP_DECLARE_MEMBERS(OdIfc4x3_rc4::IfcResourceTime);
  //DOM-IGNORE-END

public:


  //
  // OdDAI early binding accessors
  //

  const OdAnsiString& getScheduleWork() const;
  void setScheduleWork(const OdAnsiString& ScheduleWork);
  double getScheduleUsage() const;
  void setScheduleUsage(double ScheduleUsage);
  const OdAnsiString& getScheduleStart() const;
  void setScheduleStart(const OdAnsiString& ScheduleStart);
  const OdAnsiString& getScheduleFinish() const;
  void setScheduleFinish(const OdAnsiString& ScheduleFinish);
  const OdAnsiString& getScheduleContour() const;
  void setScheduleContour(const OdAnsiString& ScheduleContour);
  const OdAnsiString& getLevelingDelay() const;
  void setLevelingDelay(const OdAnsiString& LevelingDelay);
  OdDAI::Boolean getIsOverAllocated() const;
  void setIsOverAllocated(OdDAI::Boolean IsOverAllocated);
  const OdAnsiString& getStatusTime() const;
  void setStatusTime(const OdAnsiString& StatusTime);
  const OdAnsiString& getActualWork() const;
  void setActualWork(const OdAnsiString& ActualWork);
  double getActualUsage() const;
  void setActualUsage(double ActualUsage);
  const OdAnsiString& getActualStart() const;
  void setActualStart(const OdAnsiString& ActualStart);
  const OdAnsiString& getActualFinish() const;
  void setActualFinish(const OdAnsiString& ActualFinish);
  const OdAnsiString& getRemainingWork() const;
  void setRemainingWork(const OdAnsiString& RemainingWork);
  double getRemainingUsage() const;
  void setRemainingUsage(double RemainingUsage);
  double getCompletion() const;
  void setCompletion(double Completion);


public:
  IfcResourceTime();

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
  Early-bound version of instances comparison.
  \param pOther [in] Other application instance.
  \param ordering [out] Receives the ordering (comparison) status.
  \returns
  true if comparison was performed, false if method has no implementation, so late-bound version could be applied.
  \remarks
  If the method returns true,
  the ordering parameter can receive one of the following statuses:
  <table>
    Name             Value    Description
    _kLessThan_      -1       This object < Other Object.
    _kEqual_          0       This object = Other Object.
    _kGreaterThan_    1       This object > Other Object.
    _kNotOrderable_   2       This class is not orderable.
  </table>
  */
  virtual bool comparedToEarlyImpl(const OdDAI::ApplicationInstance *pOther, OdRx::Ordering &ordering) const;

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
  OdAnsiString m_ScheduleWork;   // IfcDuration  [optional]
  IfcPositiveRatioMeasure m_ScheduleUsage;   // IfcPositiveRatioMeasure  [optional]
  OdAnsiString m_ScheduleStart;   // IfcDateTime  [optional]
  OdAnsiString m_ScheduleFinish;   // IfcDateTime  [optional]
  OdAnsiString m_ScheduleContour;   // IfcLabel  [optional]
  OdAnsiString m_LevelingDelay;   // IfcDuration  [optional]
  OdDAI::Boolean m_IsOverAllocated;   // IfcBoolean  [optional]
  OdAnsiString m_StatusTime;   // IfcDateTime  [optional]
  OdAnsiString m_ActualWork;   // IfcDuration  [optional]
  IfcPositiveRatioMeasure m_ActualUsage;   // IfcPositiveRatioMeasure  [optional]
  OdAnsiString m_ActualStart;   // IfcDateTime  [optional]
  OdAnsiString m_ActualFinish;   // IfcDateTime  [optional]
  OdAnsiString m_RemainingWork;   // IfcDuration  [optional]
  IfcPositiveRatioMeasure m_RemainingUsage;   // IfcPositiveRatioMeasure  [optional]
  IfcPositiveRatioMeasure m_Completion;   // IfcPositiveRatioMeasure  [optional]
};

/** \details
  A data type that represents a smart pointer to a <link OdIfc4x3_rc4::IfcResourceTime, IfcResourceTime> object.
*/
typedef OdSmartPtr<IfcResourceTime> IfcResourceTimePtr;

} // namespace

#endif // _IFC4X3_RC4_IFCRESOURCETIME_AUTO_IMPL_H
