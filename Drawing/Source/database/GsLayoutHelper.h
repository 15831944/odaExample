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

class OdGsLayoutHelperIntCallback
{
  public:
    virtual void dbObjectModified(const OdDbObject* /*pDbObj*/) { }
    virtual void dbMAXACTVPModified(const OdDbDatabase* /*pDb*/) { }
};

class OdGsLayoutHelperInt : public OdGsBaseLayoutHelperInt<OdDbDatabase, OdDbObject>, OdStaticRxObject<OdDbDatabaseReactor>
{
  static OdGiDrawablePtr openDrawable(OdDbStub* id);

  // OdDbDatabase's notifications
  void objectAppended(const OdDbDatabase* pDb, const OdDbObject* pDbObj);
  void objectModified(const OdDbDatabase* pDb, const OdDbObject* pDbObj);
  void objectErased(const OdDbDatabase* pDb, const OdDbObject* pDbObj, bool bErased);
  void goodbye(const OdDbDatabase* pDb);
  void headerSysVar_MAXACTVP_Changed(const OdDbDatabase* pDb);

  OdGsLayoutHelperIntCallback *m_pIntCallback;

public:
  ODRX_HEAP_OPERATORS();

  void init(OdGsDevice* pUnderlyingDevice, const OdDbObjectId& layoutId);
  void setCallback(OdGsLayoutHelperIntCallback *pCallback, const OdDbObjectId& /*layoutId*/) { m_pIntCallback = pCallback; }  

  bool linkReactorsEnabled() const;
  void restoreDbLinkState();

  bool storeLayoutGsState(OdStreamBuf* pStream, const OdGsDevice *pDevice) const;
  bool restoreLayoutGsState(OdStreamBuf* pStream, OdGsDevice *pDevice);

  bool saveDeviceState(OdGsFiler *pFiler) const;
  bool loadDeviceState(OdGsFiler *pFiler, bool bPartial);

  OdGsLayoutHelperInt();
  ~OdGsLayoutHelperInt() 
  {
    if(this->m_pDb)
    {
      this->m_pDb->removeReactor(this);
    }
  }
};

template <class TBase>
class OdGsLayoutHelperImpl : public OdGsBaseLayoutHelperImpl<TBase, OdGsLayoutHelperInt>
{
protected:
  ODRX_HEAP_OPERATORS();

  OdDbObjectReactorArray m_linkReactors;
  OdDbGeoDataMarkerPtr m_pGeoDataMarker;
  OdDbGeoDataChunksPtr m_pGeoDataChunks_kUserBg1;
  OdDbGeoDataChunksPtr m_pGeoDataChunks_kMain;
  OdDbGeoDataProvidersStringPtr m_pGeoDataProvidersString;
  std::map<OdGsView*, bool> m_mapViewsWithGeo;
  OdGsModelPtr m_pDirectOverlay;
  OdGsModelPtr m_pUserBg1Overlay;

  OdGsLayoutHelperImpl();
  void clearViewWithGeo(OdGsView* pView, bool bMode2DOptimized);
  void eraseGeoDrawables();
  virtual bool checkGeoMarkerVisibility() const;
  virtual bool checkGeoDataVisibility(OdGsView* pView) const;
  void updateGeoDrawables();

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

  OdDbObjectId layoutId() const
  {
    return this->getLayoutId();
  }

  OdDbObjectId getActiveViewportId()
  {
    return this->getActiveViewportStub();
  }
  bool setActiveViewport(const OdDbObjectId& id)
  {
    return this->setActiveViewportStub(id);
  }
  typedef OdGsBaseLayoutHelperImpl<TBase, OdGsLayoutHelperInt> OdGsBaseLayoutHelperImplDef;
  TD_USING(OdGsBaseLayoutHelperImplDef::setActiveViewport);
};

class OdGsPaperLayoutHelperImpl;
typedef OdSmartPtr<OdGsPaperLayoutHelperImpl> OdGsPaperLayoutHelperImplPtr;

class OdGsPaperLayoutHelperImpl : public OdGsLayoutHelperImpl<OdGsPaperLayoutHelper>, protected OdGsLayoutHelperIntCallback
{
  // Viewports filter
  struct ViewportsFilter
  {
    struct ViewClient
    {
      enum Flags
      {
        kVpOff         = (1 << 0), // Viewport in off-state
        kVpOutOfScreen = (1 << 1), // Viewport is out of screen (screen filter)
        kVpTooSmall    = (1 << 2), // Filtered by size filter
        kVpOutOfMaxAct = (1 << 3), // Filtered by MAXACTVP filter
        kVpNew         = (1 << 4), // New viewport (must be processed earlier)
        kVpInitialized = (1 << 5), // Viewport was visible at least once
        kVpVisible     = (1 << 6), // Viewport is in visible state
        kVpViewNotSync = (1 << 7), // Detected that current gsView visibility state is not in sync with viewport
        kLastFlag      = kVpViewNotSync,
        kVpFilter      = kVpOutOfScreen | kVpTooSmall | kVpOutOfMaxAct
      };
      OdUInt32    vpFlags;
      ViewClient() : vpFlags(0) {}
    };
    enum BranchIndex
    {
      kDefaultBranch = kVpBrDefault - 1, // Default branch.
      kPlotBranch    = kVpBrPlot - 1,    // Plot generation branch.
    };
    struct Branch
    {
      enum Flags
      {
        kEnableScreenFilter = (1 << 0), // Enable screen filter
        kApplyScreenFilter  = (1 << 1), // Apply screen filter visually
        kEnableSizeFilter   = (1 << 2), // Enable size filter
        kApplySizeFilter    = (1 << 3), // Apply size filter visually
        kEnableMaxActVp     = (1 << 4), // Enable MaxActVp filter
        kApplyMaxActVp      = (1 << 5), // Apply MaxActVp filter visually
        kFirstInit          = (1 << 6), // We can have new viewports only after first init.
        kRecompute          = (1 << 7), // Mark recompution required
        kHasNewViewports    = (1 << 8), // Set during filtering if newly created viewports detected.
        kHasUninitialized   = (1 << 9)  // Set during filtering if non-initialized viewports detected.
      };
      OdUInt32 m_branchFlags;
      // Size filter param
      OdUInt32 m_nMinSize;

      Branch() : m_branchFlags(kEnableScreenFilter | kApplyScreenFilter | kEnableSizeFilter | kApplySizeFilter |
                               kEnableMaxActVp | kApplyMaxActVp | kFirstInit | kRecompute)
               , m_nMinSize(10) { }
    } m_branch[2];
    // Screen filter param
    OdGsDCRectDouble m_screenSize;
    // MAXACTVP filter param
    OdUInt32 m_nMAXACTVP;
    // Current filter branch
    BranchIndex m_curBranch;

    ViewportsFilter() : m_screenSize(0.0, 0.0, 0.0, 0.0), m_nMAXACTVP(0), m_curBranch(kDefaultBranch)
    { /* Documentation says "MAXACTVP has no effect on the number of viewports that are plotted." */
      SETBIT_0(m_branch[kPlotBranch].m_branchFlags, Branch::kEnableMaxActVp | Branch::kApplyMaxActVp); 
    }

    void setFlag(ViewportFilterBranch nBranch, Branch::Flags nFlag, bool bSet)
    {
      if (GETBIT(nBranch, kVpBrDefault))
        SETBIT(m_branch[kDefaultBranch].m_branchFlags, nFlag, bSet);
      if (GETBIT(nBranch, kVpBrPlot))
        SETBIT(m_branch[kPlotBranch].m_branchFlags, nFlag, bSet);
    }
    bool getFlag(ViewportFilterBranch nBranch, Branch::Flags nFlag)
    { bool bSet = false;
      if (GETBIT(nBranch, kVpBrDefault))
        bSet = GETBIT(m_branch[kDefaultBranch].m_branchFlags, nFlag);
      if (GETBIT(nBranch, kVpBrPlot))
        bSet |= GETBIT(m_branch[kPlotBranch].m_branchFlags, nFlag);
      return bSet;
    }
    void setRecompute() { setFlag(kVpBrAll, ViewportsFilter::Branch::kRecompute, true); }

    void setBranch(bool bPlotGeneration)
    { m_curBranch = (bPlotGeneration) ? kPlotBranch : kDefaultBranch; }
    BranchIndex branch() const { return m_curBranch; }

    typedef std::pair<OdGsView *, ViewClient *> VpData;
    OdVector<VpData, OdMemoryAllocator<VpData> > m_views;
    void startViewsFiltration(OdUInt32 numViews);
    void filterView(OdUInt32 nView, OdGsView *pView, ViewClient &vpData);
    bool filtrationPass(bool bForward, OdUInt32 procConditionInclusive, OdUInt32 procConditionExclusive,
                        OdUInt32 branchConditionInclusive, OdUInt32 branchConditionExclusive,
                        const OdUInt32 nMAXACTVP, OdUInt32 &actVp);
    void executeViewsFiltration();
  } m_vpFilter;

  struct ViewInfo : public ViewportsFilter::ViewClient
  {
    ViewInfo() : contours(0) {}

    OdGePoint2d lowerLeft;
    OdGePoint2d upperRight;

    enum { kNeedCalc = kLastFlag << 1 };
    OdDbObjectId      calcObjId;

    int               contours;
    OdIntArray        counts;
    OdGePoint3dArray  points;
  };
  OdArray<ViewInfo>   m_viewInfos;
  OdGsViewPtr         m_pHelperSpaceView;
  OdDbObjectIdArray   m_viewportIds;
  OdDbObjectId        m_layoutActiveId;
  int                 m_curMAXACTVP;
protected:
  OdUInt32            m_nOverall;
  bool                m_bDrawViewportsFirst;
  OdGsPaperLayoutHelperImpl();
  ~OdGsPaperLayoutHelperImpl();
  OdDbObjectPtr overallViewport() const;

  void firstInitLayoutState();
  bool layoutChanged(const OdDbObject *pLayout, bool forceUpdateAllViewports = false);
  bool MAXACTVPChanged(bool bForce = false);
  void dbObjectModified(const OdDbObject* pDbObj);
  void dbMAXACTVPModified(const OdDbDatabase* pDb);

  virtual bool checkGeoMarkerVisibility() const;
  virtual bool checkGeoDataVisibility(OdGsView* pView) const;
public:
  static OdGsPaperLayoutHelperImplPtr createObject(OdGsDevice* pUnderlyingDevice, const OdDbObjectId& layoutId);

  void viewPsCoordinates(int viewNo, OdGePoint2d& lowerLeft, OdGePoint2d& upperRight);
  void setViewPsCoordinates(int viewNo, const OdGePoint2d& lowerLeft, const OdGePoint2d& upperRight);
  void setViewportClipRegion(int viewNo, int contours, const int* counts, const OdGePoint3d* points);
  void initGsView(int viewNo, const OdDbViewport* pVp);
  void initGsView(OdGsView* pView, const OdDbViewport* pVp);

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
  OdUInt32 storeFlags(OdUInt32Vector &svFlags);
  void restoreFlags(const OdUInt32Vector &svFlags);

  void setViewportFilter(ViewportFilter vpFilter, ViewportFilterBranch filterBranch = kVpBrAll,
                         ViewportFilterMode filterMode = kVpFilterVisible, OdUInt32 filterParam = 0);
  void setupFilters(OdUInt32 numViews);

  static double calcLwScale(OdGsView* pOverallView, OdDbDatabase* pDb,
      OdDbLayout* pLayout, bool isPlotting);

  void setViewsParams(OdGiContextForDbDatabase* pGiCtx, OdGsView* pOverallView,
      bool bPSLTSCALE, double lwScale);
  void createHelperSpaceView(OdGiContextForDbDatabase* pGiCtx, OdGsView* pOverallView,
      OdDbLayout* pLayout, bool bAddPSpace);
};

class OdGsModelLayoutHelperImpl;
typedef OdSmartPtr<OdGsModelLayoutHelperImpl> OdGsModelLayoutHelperImplPtr;


class OdGsModelLayoutHelperImpl : public OdGsLayoutHelperImpl<OdGsModelLayoutHelper>, protected OdGsLayoutHelperIntCallback
{
  bool m_bLWDISPLAY;
  double m_fLWDISPSCALE;
  OdDbObjectId m_vptRecId;
protected:
  OdGsModelLayoutHelperImpl();
  ~OdGsModelLayoutHelperImpl();

  bool viewportTableRecordModified(const OdDbObject* pVTR);
  void dbObjectModified(const OdDbObject* pDbObj);
public:
  static OdGsModelLayoutHelperPtr createObject(OdGsDevice* pUnderlyingDevice, const OdDbObjectId& layoutId);
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
