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

#ifndef _ODGSLAYOUTHELPER_H_
#define _ODGSLAYOUTHELPER_H_

#include "DbStdAfx.h"
#include "DbDatabase.h"
#include "DbLayout.h"
#include "GsBaseLayoutHelper.h"
#include "DbGsManager.h"
#include "DbDatabaseReactor.h"
#include "OdDbGeoDataMarker.h"
#include "OdDbGeoDataDrawingPE.h"

class OdTvDbGsLayoutHelperIntCallback
{
  public:
    virtual void dbObjectModified(const OdTvDbObject* /*pDbObj*/) { }
    virtual void dbMAXACTVPModified(const OdTvDbDatabase* /*pDb*/) { }
};

class OdTvDbGsLayoutHelperInt : public OdGsBaseLayoutHelperInt<OdTvDbDatabase, OdTvDbObject>, OdStaticRxObject<OdTvDbDatabaseReactor>
{
  static OdGiDrawablePtr openDrawable(OdDbStub* id);

  // OdTvDbDatabase's notifications
  void objectAppended(const OdTvDbDatabase* pDb, const OdTvDbObject* pDbObj);
  void objectModified(const OdTvDbDatabase* pDb, const OdTvDbObject* pDbObj);
  void objectErased(const OdTvDbDatabase* pDb, const OdTvDbObject* pDbObj, bool bErased);
  void goodbye(const OdTvDbDatabase* pDb);
  void headerSysVar_MAXACTVP_Changed(const OdTvDbDatabase* pDb);

  OdTvDbGsLayoutHelperIntCallback *m_pIntCallback;

public:
  ODRX_HEAP_OPERATORS();

  void init(OdGsDevice* pUnderlyingDevice, const OdTvDbObjectId& layoutId);
  void setCallback(OdTvDbGsLayoutHelperIntCallback *pCallback, const OdTvDbObjectId& /*layoutId*/) { m_pIntCallback = pCallback; }  

  bool linkReactorsEnabled() const;
  void restoreDbLinkState();

  bool storeLayoutGsState(OdStreamBuf* pStream, const OdGsDevice *pDevice) const;
  bool restoreLayoutGsState(OdStreamBuf* pStream, OdGsDevice *pDevice);

  bool saveDeviceState(OdGsFiler *pFiler) const;
  bool loadDeviceState(OdGsFiler *pFiler, bool bPartial);

  OdTvDbGsLayoutHelperInt();
  ~OdTvDbGsLayoutHelperInt() 
  {
    if(this->m_pDb)
    {
      this->m_pDb->removeReactor(this);
    }
  }
};

template <class TBase>
class OdTvGsLayoutHelperImpl : public OdGsBaseLayoutHelperImpl<TBase, OdTvDbGsLayoutHelperInt>
{
protected:
  ODRX_HEAP_OPERATORS();

  OdTvDbObjectReactorArray m_linkReactors;
public:
  bool linkReactorsEnabled() const
  {
    return this->m_int.linkReactorsEnabled();
  }

  void restoreGsViewDbLinkState()
  {
    this->m_int.restoreDbLinkState();
  }

  bool supportLayoutGsStateSaving() const
  {
    return this->m_int.m_pDevice->saveDeviceState(NULL);
  }
  bool storeLayoutGsState(OdStreamBuf* pStream, OdUInt32 /*nFlags*/ = 0) const
  {
    return this->m_int.storeLayoutGsState(pStream, this);
  }
  bool restoreLayoutGsState(OdStreamBuf* pStream, OdUInt32 /*nFlags*/ = 0)
  {
    return this->m_int.restoreLayoutGsState(pStream, this);
  }

  OdTvDbObjectId layoutId() const
  {
    return this->getLayoutId();
  }

  OdTvDbObjectId getActiveViewportId()
  {
    return this->getActiveViewportStub();
  }
  bool setActiveViewport(const OdTvDbObjectId& id)
  {
    return this->setActiveViewportStub(id);
  }
  typedef OdGsBaseLayoutHelperImpl<TBase, OdTvDbGsLayoutHelperInt> OdGsBaseLayoutHelperImplDef;
  TD_USING(OdGsBaseLayoutHelperImplDef::setActiveViewport);
};

class OdTvGsPaperLayoutHelperImpl;
typedef OdSmartPtr<OdTvGsPaperLayoutHelperImpl> OdGsPaperLayoutHelperImplPtr;

class OdTvGsPaperLayoutHelperImpl : public OdTvGsLayoutHelperImpl<OdTvGsPaperLayoutHelper>, protected OdTvDbGsLayoutHelperIntCallback
{
  struct ViewInfo
  {
    ViewInfo() : needCalc(false), contours(0) {}

    OdGePoint2d       lowerLeft;
    OdGePoint2d       upperRight;

    bool              needCalc;
    OdTvDbObjectId      calcObjId;

    int               contours;
    OdIntArray        counts;
    OdGePoint3dArray  points;
  };
  OdArray<ViewInfo>   m_viewInfos;
  OdGsViewPtr         m_pHelperSpaceView;
  OdTvDbObjectIdArray   m_viewportIds;
  OdTvDbObjectId        m_layoutActiveId;
  int                 m_curMAXACTVP;
  OdTvDbGeoDataMarkerPtr m_pGeoDataMarker;
protected:
  OdUInt32            m_nOverall;
  bool                m_bDrawViewportsFirst;
  OdTvGsPaperLayoutHelperImpl();
  ~OdTvGsPaperLayoutHelperImpl();
  OdTvDbObjectPtr overallViewport() const;

  void firstInitLayoutState();
  bool layoutChanged(const OdTvDbObject *pLayout, bool forceUpdateAllViewports = false);
  bool MAXACTVPChanged(bool bForce = false);
  void dbObjectModified(const OdTvDbObject* pDbObj);
  void dbMAXACTVPModified(const OdTvDbDatabase* pDb);
public:
  static OdGsPaperLayoutHelperImplPtr createObject(OdGsDevice* pUnderlyingDevice, const OdTvDbObjectId& layoutId);

  void viewPsCoordinates(int viewNo, OdGePoint2d& lowerLeft, OdGePoint2d& upperRight);
  void setViewPsCoordinates(int viewNo, const OdGePoint2d& lowerLeft, const OdGePoint2d& upperRight);
  void setViewportClipRegion(int viewNo, int contours, const int* counts, const OdGePoint3d* points);
  void initGsView(int viewNo, const OdTvDbViewport* pVp);
  void initGsView(OdGsView* pView, const OdTvDbViewport* pVp);

  void update(OdGsDCRect* pUpdatedRect = NULL);
  void addView(OdGsView* pView);
  void insertView(int viewIndex, OdGsView* pView);
  bool eraseView(OdGsView* pView);
  bool eraseView(int n);
  void eraseAllViews();
  void onSize(const OdGsDCRect& outputRect);
  OdGsViewPtr overallView() const;
  void makeViewOverall(OdGsView* pView);

  bool setActiveViewport(const OdGePoint2d& screenPt);

  void attachLinkReactors();
  void detachLinkReactors();

  bool saveDeviceState(OdGsFiler *pFiler) const;
  bool loadDeviceState(OdGsFiler *pFiler);

  // For reactors only
  void updateViewportsState(OdGsView *pView);
  int viewportIndex(OdGsView *pView);

  static double calcLwScale(OdGsView* pOverallView, OdTvDbDatabase* pDb,
      OdTvDbLayout* pLayout, bool isPlotting);

  void setViewsParams(OdTvGiContextForDbDatabase* pGiCtx, OdGsView* pOverallView,
      bool bPSLTSCALE, double lwScale);
  void createHelperSpaceView(OdTvGiContextForDbDatabase* pGiCtx, OdGsView* pOverallView,
      OdTvDbLayout* pLayout, bool bAddPSpace);
};

class OdTvGsModelLayoutHelperImpl;
typedef OdSmartPtr<OdTvGsModelLayoutHelperImpl> OdGsModelLayoutHelperImplPtr;


class OdTvGsModelLayoutHelperImpl : public OdTvGsLayoutHelperImpl<OdTvGsModelLayoutHelper>, protected OdTvDbGsLayoutHelperIntCallback
{
  bool m_bLWDISPLAY;
  double m_fLWDISPSCALE;
  OdTvDbObjectId m_vptRecId;
  OdTvDbGeoDataMarkerPtr m_pGeoDataMarker;
  OdTvDbGeoDataChunksPtr m_pGeoDataChunks_kUserBg1;
  OdTvDbGeoDataChunksPtr m_pGeoDataChunks_kMain;
  OdTvDbGeoDataProvidersStringPtr m_pGeoDataProvidersString;
protected:
  OdTvGsModelLayoutHelperImpl();
  ~OdTvGsModelLayoutHelperImpl();

  bool viewportTableRecordModified(const OdTvDbObject* pVTR);
  void dbObjectModified(const OdTvDbObject* pDbObj);
public:
  static OdTvGsModelLayoutHelperPtr createObject(OdGsDevice* pUnderlyingDevice, const OdTvDbObjectId& layoutId);
  void update(OdGsDCRect* pUpdatedRect = NULL);

  bool setActiveViewport(const OdGePoint2d& screenPt);

  void addView(OdGsView* pView);
  void insertView(int viewIndex, OdGsView* pView);
  bool eraseView(OdGsView* pView);
  bool eraseView(int n);
  void eraseAllViews();

  void attachLinkReactors();
  void detachLinkReactors();

  bool saveDeviceState(OdGsFiler *pFiler) const;
  bool loadDeviceState(OdGsFiler *pFiler);
};

#endif //#ifndef _ODGSLAYOUTHELPER_H_
