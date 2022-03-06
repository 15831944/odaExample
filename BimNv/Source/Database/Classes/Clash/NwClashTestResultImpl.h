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

#ifndef _NW_CLASHTESTRESULT_IMPL_H_
#define _NW_CLASHTESTRESULT_IMPL_H_

#include "NwClashTestResult.h"
#include "NwSavedItemImpl.h"
#include "Ge/GePoint3d.h"
#include "Ge/GeExtents3d.h"

class OdNwClashTestResultImpl;

class OdNwRedLine;
typedef OdSmartPtr<OdNwRedLine> OdNwRedLinePtr;
class OdNwModelItem;
typedef OdSmartPtr<OdNwModelItem> OdNwModelItemPtr;
class OdNwViewpoint;
typedef OdSmartPtr<OdNwViewpoint> OdNwViewpointPtr;

class OdNwClashTestResultImpl : public OdNwSavedItemImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwClashTestResult)
public:
  OdNwClashTestResultImpl();
  virtual ~OdNwClashTestResultImpl();
  ODRX_DECLARE_MEMBERS(OdNwClashTestResultImpl);

  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;
  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const;
  virtual void subViewportDraw(OdGiViewportDraw* pVd) const;

public:
  OdArray<OdNwRedLinePtr>& getRedlineList();
  OdResult getRedlineList(OdArray<OdNwRedLinePtr>& list) const;
  OdResult getRedlineList(OdNwObjectIdArray& list) const;
  OdString getDescription() const;
  void setDescription(const OdString& val);
  double getDistance() const;
  void setDistance(double val);
  void setPathLinkFirst(OdUInt32 val);
  OdNwModelItemPtr getFirstNode() const;
  OdNwObjectId getFirstNodeId() const;
  void setPathLinkSecond(OdUInt32 val);
  OdNwModelItemPtr getSecondNode() const;
  OdNwObjectId getSecondNodeId() const;
  OdGePoint3d getPoint1() const;
  void setPoint1(const OdGePoint3d& val);
  OdGePoint3d getPoint2() const;
  void setPoint2(const OdGePoint3d& val);
  OdGeExtents3d getBoundingBox() const;
  void setBoundingBox(const OdGeExtents3d& val);

  NwClashTestResultStatusType::Enum getResultStatus() const;
  void setResultStatus(NwClashTestResultStatusType::Enum val);

  void setCreatedTime(const tm& val);
  tm getCreatedTime() const;
  void setApprovedTime(const tm& val);
  tm getApprovedTime() const;
  void setSimulationStartTime(const tm& val);
  tm getSimulationStartTime() const;
  void setSimulationEndTime(const tm& val);
  tm getSimulationEndTime() const;
  void setSimulationMinTimeOffset(const double val);
  double getSimulationMinTimeOffset() const;
  void setSimulationEventName(const OdString& val);
  OdString getSimulationEventName() const;

  void setApprovedBy(const OdString& val);
  OdString getApprovedBy() const;
  void setAssignedTo(const OdString& val);
  OdString getAssignedTo() const;
  void setSimulationType(OdUInt32 val);
  OdUInt32 getSimulationType() const;
  void setTestType(NwClashTestType::Enum val);
  NwClashTestType::Enum getTestType() const;

  OdNwViewpointPtr getViewPoint() const;
  OdNwObjectId getViewPointId() const;
  void setViewPoint(const OdNwObjectId& viewId);

public:
  static OdNwClashTestResultImpl* getImpl(const OdNwClashTestResult* pNwGeometry);
  static OdNwClashTestResultImpl* getImpl(const OdRxObject* pRxGeometry);
protected:
  OdString                      m_sDecription;
  double                        m_dDistance;
  std::pair<OdUInt32, OdUInt32> m_PathLinkObjects;
  OdGePoint3d                   m_nPoint1;
  OdGePoint3d                   m_nPoint2;
  OdGeExtents3d                 m_nBoundingBox;

  NwClashTestResultStatusType::Enum m_nResultStatus;

  tm                      m_nCreatedTime;
  tm                      m_nApprovedTime;
  tm                      m_nSimulationStartTime;
  tm                      m_nSimulationEndTime;
  double                  m_dSimulationMinTimeOffset;
  OdString                m_sSimulationEventName;

  OdString                m_sApprovedBy;
  OdString                m_sAssignedTo;
  OdUInt32                m_nSimulationType;
  NwClashTestType::Enum   m_nTestType;

  OdNwObjectId            m_viewPointId;
  OdArray<OdNwRedLinePtr> m_aRedlines;

};

#endif //_NW_CLASHTESTRESULT_IMPL_H_

