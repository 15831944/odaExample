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

#ifndef _NW_RULE_IMPL_H_
#define _NW_RULE_IMPL_H_

#include "NwRule.h"
#include "NwObjectImpl.h"

class OdNwRuleImpl;


class OdNwData;
typedef std::shared_ptr<OdNwData> OdNwDataPtr;

typedef std::pair<OdInt32, OdNwDataPtr> OdNwRuleParamPair;

typedef OdArray<OdNwRuleParamPair> OdNwRuleParamPairArray;

class OdNwRuleImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwRule)
public:
  OdNwRuleImpl();
  virtual ~OdNwRuleImpl();
  ODRX_DECLARE_MEMBERS(OdNwRuleImpl);

  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;
  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const;
  virtual void subViewportDraw(OdGiViewportDraw* pVd) const;

public:
  static OdNwRuleImpl* getImpl(const OdNwRule* pNwGeometry);
  static OdNwRuleImpl* getImpl(const OdRxObject* pRxGeometry);

public:
  OdNwObjectIdArray getParameters() const;
  OdString getName() const;
  OdString getDescription() const;
  bool isEnabled() const;

  void setName(const OdString& name);
  void setDescription(const OdString& val);
  void setEnabled(const bool val);
  void setParameters(const OdNwObjectIdArray& val);
  void addRuleParam(const OdNwRuleParamPair& param);
  OdNwRuleParamPairArray getRuleParams() const;

private:
  OdString                m_sName;
  OdString                m_sDescription;
  bool                    m_bIsEnabled;
  mutable OdNwObjectIdArray       m_aParameters;

  OdNwRuleParamPairArray m_aRuleParamPairs;
};

#endif //_NW_RULE_IMPL_H_

