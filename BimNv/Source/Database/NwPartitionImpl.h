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

#ifndef __NWPARTITIONIMPL_INCLUDED__
#define __NWPARTITIONIMPL_INCLUDED__

#include "NwPartition.h"
#include "NwModelItemImpl.h"

class OdNwDatabaseImpl;
class OdNwPartitionNode;
typedef OdSmartPtr<OdNwPartitionNode> OdNwPartitionNodePtr;

class NWDBEXPORT OdNwPartitionImpl : public OdNwModelItemImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwPartition)
public:
  OdNwPartitionImpl();
  virtual ~OdNwPartitionImpl();
  ODRX_DECLARE_MEMBERS(OdNwPartitionImpl);

public:
  static OdNwPartitionImpl* getImpl(const OdNwPartition* pNwNode);
  static OdNwPartitionImpl* getImpl(const OdRxObject* pRxNode);
  static OdNwObjectId createRootNode(OdNwDatabaseImpl* pDbImpl);

protected:
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const override;
  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const override;

public:
  OdString getSourceFileName() const;
  OdString getCreator() const;
  NwModelUnits::Enum getUnits() const;
  OdString getDisplayName() const override;
  OdGeVector3d getUpVector() const;
  OdGeVector3d getNorthVector() const;
  OdGeVector3d getFrontVector() const;
public:
  OdResult setUnits(NwModelUnits::Enum units);
  void setUpVector(const OdGeVector3d&);
  void setNorthVector(const OdGeVector3d&);
  void setFrontVector(const OdGeVector3d&);

public:
  OdNwObjectId addModelItem(const OdString& name, const OdString& displayName, NwModelItemIcon::Enum icon = NwModelItemIcon::GEOMETRY);
  void setInternalRoot(OdNwPartitionNodePtr pInternalRoot);

private:
  OdNwPartitionNodePtr m_pInternalRoot;
};

#endif //__NWPARTITIONIMPL_INCLUDED__
