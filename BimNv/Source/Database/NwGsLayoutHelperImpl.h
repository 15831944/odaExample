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


#ifndef __ODNWGSLAYOUTHELPERIMPL_H__
#define __ODNWGSLAYOUTHELPERIMPL_H__

#include "NwGsLayoutHelper.h"
#include "GsBaseLayoutHelper.h"
#include "DoubleArray.h"
#include "Int32Array.h"
#include "NwObjectReactor.h"

class OdNwDatabase;

#include "TD_PackPush.h"

class OdNwGsLayoutHelperInt : public OdGsBaseLayoutHelperInt<OdNwDatabase, OdNwObject>, OdStaticRxObject<OdNwDatabaseReactor>
{
  static OdGiDrawablePtr openDrawable(OdDbStub* id);

  // OdDgDatabaseReactor overridden
  virtual void elementAppended(const OdNwDatabase* pDb, const OdNwObject* pElm);
  virtual void elementModified(const OdNwDatabase* pDb, const OdNwObject* pElm);
  virtual void elementErased(const OdNwDatabase* pDb, const OdNwObject* pElm, bool bErased);
  virtual void goodbye(const OdNwDatabase* pDb);

public:
  ODRX_HEAP_OPERATORS();

  void init(OdGsDevice* pUnderlyingDevice, const OdNwObjectId& layoutId);

  OdNwGsLayoutHelperInt();
  ~OdNwGsLayoutHelperInt() {
    if (this->m_pDb) {
      this->m_pDb->removeReactor(this);
    }
  }
};

template <class TBase>
class OdNwGsLayoutHelperImpl : public OdGsBaseLayoutHelperImpl<TBase, OdNwGsLayoutHelperInt>
{
protected:
  ODRX_HEAP_OPERATORS();

public:
  OdNwObjectId layoutId() const
  {
    return this->getLayoutId();
  }

  OdNwObjectId getActiveViewportId()
  {
    return this->getActiveViewportStub();
  }

  bool setActiveViewport(const OdNwObjectId& id)
  {
    return this->setActiveViewportStub(id);
  }
  typedef OdGsBaseLayoutHelperImpl<TBase, OdNwGsLayoutHelperInt> OdGsBaseLayoutHelperImplDef;
  TD_USING(OdGsBaseLayoutHelperImplDef::setActiveViewport);
};

class ExNwGsLayoutHelperImpl : public OdNwGsLayoutHelperImpl<OdNwGsLayoutHelper>
{
protected:
  ExNwGsLayoutHelperImpl();
public:
  ~ExNwGsLayoutHelperImpl();
  ODRX_DECLARE_MEMBERS(ExNwGsLayoutHelperImpl);
  static OdNwGsLayoutHelperPtr createObject(OdGsDevice* pUnderlyingDevice, const OdNwObjectId& idLayout);

  void update(OdGsDCRect* pUpdatedRect = NULL);

  bool setActiveViewport(const OdGePoint2d& screenPt);

  OdGsViewPtr overallView();

  void setDisplayStyle(OdGsView* pView, const class OdNwView* pNwView);
};

typedef OdSmartPtr<ExNwGsLayoutHelperImpl> ExNwGsLayoutHelperImplPtr;

#include "TD_PackPop.h"

#endif // __ODNWGSLAYOUTHELPERIMPL_H__


