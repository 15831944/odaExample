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

#ifndef _NW_CLASHTEST_IMPL_H_
#define _NW_CLASHTEST_IMPL_H_

#include "NwClashTest.h"
#include "NwSavedItemImpl.h"
#include "NwFindSelectionImpl.h"

class OdNwClashTestImpl;


class OdNwSavedItemsElement;
typedef OdSmartPtr<OdNwSavedItemsElement> OdNwSavedItemsElementPtr;

class OdNwModelItem;
typedef OdSmartPtr<OdNwModelItem> OdNwModelItemPtr;


class OdNwClashTestImpl : public OdNwSavedItemImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwClashTest)
public:
  OdNwClashTestImpl();
  virtual ~OdNwClashTestImpl();
  ODRX_DECLARE_MEMBERS(OdNwClashTestImpl);

  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;
  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const;
  virtual void subViewportDraw(OdGiViewportDraw* pVd) const;

public:
  static OdNwClashTestImpl* getImpl(const OdNwClashTest* pNwGeometry);
  static OdNwClashTestImpl* getImpl(const OdRxObject* pRxGeometry);

public:
  void setTestType(NwClashTestType::Enum val);
  NwClashTestType::Enum getTestType() const;

  void setStatus(NwClashTestStatusType::Enum val);
  NwClashTestStatusType::Enum getStatus() const;

  void setSimulationType(OdInt32 val);
  OdInt32 getSimulationType() const;

  bool getIsRelativeTouchTolerance() const;
  void setIsRelativeTouchTolerance(const bool val);
  double getRelativeTouchTolerance() const;
  void setRelativeTouchTolerance(const double val);
  double getAbsoluteTouchTolerance() const;
  void setAbsoluteTouchTolerance(const double val);

  double getTolerance() const;
  void setTolerance(const double val);
  double getSimulationStep() const;
  void setSimulationStep(const double val);

  void setLastRunTime(const tm& time);
  tm getLastRunTime() const;
  void setMergeComposites(bool val);
  bool getMergeComposites() const;

  void setTestResults(const OdNwSavedItemsElementPtr& val);
  OdNwSavedItemsElementPtr getTestResults() const;
  OdNwObjectId getTestResultsId() const;

  void setRules(const OdNwObjectIdArray& rules);
  OdNwObjectIdArray getRules() const;

  OdString getCustomTestName() const;
  void setCustomTestName (OdString val);

  void setFindSelection1(const OdNwFindSelectionPtr& val);
  OdNwFindSelectionPtr getFindSelection1() const;

  void setFindSelection2(const OdNwFindSelectionPtr& val);
  OdNwFindSelectionPtr getFindSelection2() const;
  void setSelectionBool1(OdUInt32 val);
  void setSelectionBool2(OdUInt32 val);
  OdUInt32 getSelectionBool1() const;
  OdUInt32 getSelectionBool2() const;

  void setSelectionBitfield1(OdInt32 val);
  void setSelectionBitfield2(OdInt32 val);
  OdInt32 getSelectionBitfield1() const;
  OdInt32 getSelectionBitfield2() const;

private:
  NwClashTestType::Enum             m_nTestType;
  NwClashTestStatusType::Enum       m_nStatusType;
  OdInt32                           m_nSimulationType;
  bool                              m_bIsRelativeTouchTolerance;
  double                            m_dRelativeTouchTolerance;
  double                            m_dAbsoluteTouchTolerance;
  double                            m_dTolerance;
  double                            m_dSimulationStep;
  tm                                m_tLastRunTime;
  bool                              m_bMergeComposites;
  OdNwSavedItemsElementPtr          m_pClashTestResults;
  OdNwObjectIdArray                 m_aRules;
  OdString                          m_sCustomTestName;

  OdNwFindSelectionPtr              m_pFindSelection1;
  OdNwFindSelectionPtr              m_pFindSelection2;

  OdUInt32                          m_bSelectionBool1;
  OdUInt32                          m_bSelectionBool2;

  OdInt32                           m_nSelectionBitfield1;
  OdInt32                           m_nSelectionBitfield2;
};

#endif //_NW_CLASHTEST_IMPL_H_

