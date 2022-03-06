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

class OdDbBlockGripExprImpl : public OdDbConnectionPointsImpl<1, OdDbEvalExprImpl>
{
  friend class OdDbBlockGripExpr;
public:
  OdDbBlockGripExprImpl();
  DECLARE_GET_IMPL(OdDbBlockGripExpr);
};

class OdDbBlockGripImpl : public OdDbBlockElementImpl
{
  friend class OdDbBlockGrip;
public:
  OdDbEvalNodeId m_nId1,m_nId2; // ids of the OdDbBlockGripExpr
  OdGePoint3d m_pDefinitionPoint; // definition may be set only when creating the grip (in sync())
  OdGePoint3d m_pBasePoint; // grip location
  OdGePoint3d m_pUpdatedLocation;
  bool m_bCycling;
  OdInt32 m_nCyclingWeight;
  OdDbBlockGripImpl() : OdDbBlockElementImpl()
    , m_nId1(0)
    , m_nId2(0)
    , m_bCycling(false)
    , m_nCyclingWeight(0){}
  DECLARE_GET_IMPL(OdDbBlockGrip);
  void getConnectionNames( OdStringArray& a ) const;
  OdResBufPtr getConnectionValue(const OdString& name) const;
  virtual bool historyRequired() const { return true; }
};

class OdDbBlockLinearGripImpl : public OdDbBlockGripImpl
{
  friend class OdDbBlockLinearGrip;
protected:
  OdGeVector3d m_vInitialDistance;
public:
  OdDbBlockLinearGripImpl() : OdDbBlockGripImpl(){}
  DECLARE_GET_IMPL(OdDbBlockLinearGrip);
};

class OdDbBlockFlipGripImpl : public OdDbBlockGripImpl
{
  friend class OdDbBlockFlipGrip;
protected:
  OdGeVector3d m_pOrientation;
  int m_nFlipGripExpressionId;
  OdDbBlockFlipParameter::FlipState m_bFlipState;
  OdDbBlockFlipParameter::FlipState m_bUpdatedFlipState;
public:
  OdDbBlockFlipGripImpl() : OdDbBlockGripImpl()
    ,m_nFlipGripExpressionId(0), m_bUpdatedFlipState(OdDbBlockFlipParameter::NotFlipped), m_bFlipState(OdDbBlockFlipParameter::NotFlipped) {}
  bool hasInstanceData() const;
  OdResBufPtr saveInstanceData(const OdDbObject* pThis)const;
  bool loadInstanceData(OdDbObject* pThis, const OdResBuf*&, bool bRequireEvaluate);
  DECLARE_GET_IMPL(OdDbBlockFlipGrip);
};
class OdDbBlockAlignmentGripImpl : public OdDbBlockGripImpl
{
  friend class OdDbBlockAlignmentGrip;
protected:
  OdGeVector3d m_pAlignmentLine;
public:
  OdDbBlockAlignmentGripImpl() : OdDbBlockGripImpl(){}
  DECLARE_GET_IMPL(OdDbBlockAlignmentGrip);
};

#endif // _DbBlocksGripsImpl_h_Included_
