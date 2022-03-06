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

#ifndef __NWSAVEDVIEWPOINTIMPL_INCLUDED__
#define __NWSAVEDVIEWPOINTIMPL_INCLUDED__

#include "NwSavedViewpoint.h"
#include "NwSavedItemImpl.h"
#define STL_USING_LIST
#define STL_USING_MEMORY
#include "OdaSTL.h"

class OdNwElementRecord;
typedef OdSmartPtr<OdNwElementRecord> OdNwElementRecordPtr;
class OdNwViewpoint;
typedef OdSmartPtr<OdNwViewpoint> OdNwViewpointPtr;
class OdNwClipPlaneSet;
typedef OdSmartPtr<OdNwClipPlaneSet> OdNwClipPlaneSetPtr;
class OdNwRedLine;
typedef OdSmartPtr<OdNwRedLine> OdNwRedLinePtr;

class NWDBEXPORT OdNwSavedViewpointImpl : public OdNwSavedItemImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwSavedViewpoint)
public:
  ODRX_DECLARE_MEMBERS(OdNwSavedViewpointImpl);

public:
  OdNwSavedViewpointImpl();
  virtual ~OdNwSavedViewpointImpl();

public:
  static OdNwSavedViewpointImpl* getImpl(const OdNwSavedViewpoint* pNwSV);
  static OdNwSavedViewpointImpl* getImpl(const OdRxObject* pRxSV);

public:
  OdNwViewpointPtr getViewpoint() const;
  OdNwObjectId getViewpointId() const;
  OdNwClipPlaneSetPtr getClippingPlanes() const;
  OdNwObjectId getClippingPlanesId() const;
  OdResult getRedLineList(OdNwObjectIdArray& objIds) const;
  OdResult getHiddens(OdNwObjectIdArray& aHidenNodes) const;
  OdResult getRequireds(OdNwObjectIdArray& aReqNodes) const;
  OdUInt32 getAppearanceOverrideCount() const;
  OdResult getAppearanceOverride(OdUInt32 idx, OdNwObjectIdArray& modelItems, OdNwObjectId& materialId) const;
  inline OdArray<OdNwRedLinePtr>& getRedLineList() { return m_lRedLine; }
  inline OdArray<OdNwElementRecordPtr>& getElementRecordList() { return m_lElementRecord; }

public:
  void setViewpoint(OdNwViewpointPtr pView);
  void setClippingPlanes(OdNwClipPlaneSetPtr pCLipPlaneSet);

protected:
  OdNwViewpointPtr m_pViewpoint;
  OdNwClipPlaneSetPtr m_pClipPlaneSet;
  OdArray<OdNwRedLinePtr> m_lRedLine;
  OdArray<OdNwElementRecordPtr> m_lElementRecord;
};

typedef OdSmartPtr<OdNwSavedViewpointImpl> OdNwSavedViewpointImplPtr;

#endif // __NWSAVEDVIEWPOINTIMPL_INCLUDED__
