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

#ifndef __NWRUNMODELITEMIMPL_INCLUDED__
#define __NWRUNMODELITEMIMPL_INCLUDED__

#include "NwModelItemImpl.h"
#include "NwRunModelItem.h"

class NWDBEXPORT OdNwRunModelItemImpl : public OdNwModelItemImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwRunModelItem)
public:
  OdNwRunModelItemImpl();
  virtual ~OdNwRunModelItemImpl();
  ODRX_DECLARE_MEMBERS(OdNwRunModelItemImpl);

  static OdNwRunModelItemImpl* getImpl(const OdNwRunModelItem* pNwModelItem);
  static OdNwRunModelItemImpl* getImpl(const OdRxObject* pRxPathLink);
  //pHeadOfBranch - param for getting through end nodes from select tree branch, not from all tree
  static OdNwRunModelItem* getNextRunPath(OdNwModelItem* pPathLink, OdNwModelItem* pHeadOfBranch = nullptr);

protected:
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const override;
  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const override;

public:
  void addShape(OdNwObject* pFragment);
  OdResult subSetIsHidden(bool value) override;
  void setFragmentsIsHidden(bool isHidden);

public:
  inline OdArray<OdNwObject*>& getFragments() { return m_aFragments; }
  bool hasGeometry() const override;
  OdNwObjectId getGeometryComponentId() const override;
  OdUInt32 getFragmentsCount() const;
  OdNwObjectId getFragment(OdUInt32 idx) const;

  OdGeExtents3d getBoundingBox() const override;

protected:
  OdArray<OdNwObject*> m_aFragments;
  mutable OdNwObjectId m_geometryComponentId;
};

typedef OdSmartPtr<OdNwRunModelItemImpl> OdNwRunModelItemImplPtr;

#endif //__NWRUNMODELITEMIMPL_INCLUDED__
