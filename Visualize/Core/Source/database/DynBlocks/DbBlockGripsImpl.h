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

#ifndef _DbBlocksGripsImpl_h_Included_
#define _DbBlocksGripsImpl_h_Included_

#include "DbObjectImpl.h"
#include "DbEvalGraph.h"
#include "DbEvalGraphImpl.h"
#include "DbBlockGrips.h"
#include "DbBlockElementImpl.h"

class OdTvDbBlockGripExprImpl : public OdTvDbConnectionPointsImpl<1, OdTvDbEvalExprImpl>
{
  friend class OdTvDbBlockGripExpr;
public:
  OdTvDbBlockGripExprImpl();
  DECLARE_GET_IMPL(OdTvDbBlockGripExpr);
};

class OdTvDbBlockGripImpl : public OdTvDbBlockElementImpl
{
  friend class OdTvDbBlockGrip;
public:
  OdTvDbEvalNodeId m_nId1,m_nId2; // ids of the OdTvDbBlockGripExpr
  OdGePoint3d m_pDefinitionPoint; // definition may be set only when creating the grip (in sync())
  OdGePoint3d m_pBasePoint; // grip location
  OdGePoint3d m_pUpdatedLocation;
  bool m_bCycling;
  OdInt32 m_nCyclingWeight;
  OdTvDbBlockGripImpl() : OdTvDbBlockElementImpl()
    , m_nId1(0)
    , m_nId2(0)
    , m_bCycling(false)
    , m_nCyclingWeight(0){}
  DECLARE_GET_IMPL(OdTvDbBlockGrip);
  void getConnectionNames( OdStringArray& a ) const;
  OdTvResBufPtr getConnectionValue(const OdString& name) const;
  virtual bool historyRequired() const { return true; }
};

class OdTvDbBlockLinearGripImpl : public OdTvDbBlockGripImpl
{
  friend class OdTvDbBlockLinearGrip;
protected:
  OdGeVector3d m_vInitialDistance;
public:
  OdTvDbBlockLinearGripImpl() : OdTvDbBlockGripImpl(){}
  DECLARE_GET_IMPL(OdTvDbBlockLinearGrip);
};

class OdTvDbBlockFlipGripImpl : public OdTvDbBlockGripImpl
{
  friend class OdTvDbBlockFlipGrip;
protected:
  OdGeVector3d m_pOrientation;
  int m_nFlipGripExpressionId;
  OdTvDbBlockFlipParameter::FlipState m_bFlipState;
  OdTvDbBlockFlipParameter::FlipState m_bUpdatedFlipState;
public:
  OdTvDbBlockFlipGripImpl() : OdTvDbBlockGripImpl()
    ,m_nFlipGripExpressionId(0), m_bUpdatedFlipState(OdTvDbBlockFlipParameter::NotFlipped), m_bFlipState(OdTvDbBlockFlipParameter::NotFlipped) {}
  bool hasInstanceData() const;
  OdTvResBufPtr saveInstanceData(const OdTvDbObject* pThis)const;
  bool loadInstanceData(OdTvDbObject* pThis, const OdTvResBuf*&, bool bRequireEvaluate);
  DECLARE_GET_IMPL(OdTvDbBlockFlipGrip);
};
class OdTvDbBlockAlignmentGripImpl : public OdTvDbBlockGripImpl
{
  friend class OdTvDbBlockAlignmentGrip;
protected:
  OdGeVector3d m_pAlignmentLine;
public:
  OdTvDbBlockAlignmentGripImpl() : OdTvDbBlockGripImpl(){}
  DECLARE_GET_IMPL(OdTvDbBlockAlignmentGrip);
};

#endif // _DbBlocksGripsImpl_h_Included_
