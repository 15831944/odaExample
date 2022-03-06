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

#ifndef TVANDCORE_H
#define TVANDCORE_H

#include <stdio.h>
#include "TvAndGlobalParameters.h"
#include "TvAndDatabaseInfo.h"
#include "TvAndSectioningOptions.h"
#include "TvAndViewParamsComparator.h"
#include "TvAndLimitManager.h"
#include "TvAndProgressMeter.h"
// Visualize SDK
#include "TvFactory.h"
#include "TvImport.h"
#include "Tools/TvDragger.h"
#include "Tools/TvExtendedView.h"
#include "Tools/TvMarkupDraggers.h"
#include "Tools/TvGroundShadow.h"
#include "TvGsView.h"

#include "OdPerfTimer.h"
#include "TvDeprecated.h"

struct ImportParamsContainer
{
    OdTvBaseImportParams baseParams;
    OdTvDwgImportParams dwgParams;
    OdTvDgnImportParams dgnParams;
    OdTvPrcImportParams prcParams;
    OdTvObjImportParams objParams;
    OdTvStlImportParams stlParams;
    OdTvRcsImportParams rcsParams;
    OdTvIfcImportParams ifcParams;
};

class TvAndCore
{
public:
    enum NavigationAction
    {
        Pan         = 0,
        Orbit       = 1,
        ZoomWindow  = 2,
        ZoomExtents = 3
    };
    
    enum RegenAction
    {
        All      = 0,
        Visible  = 1,
        View     = 2
    };
    
    enum MarkupAction
    {
        Rectangle  = 0,
        Circle     = 1,
        Handle     = 2,
        Cloud      = 3,
        Text       = 4,
        Save       = 5,
        Load       = 6
    };
    
    enum FileExtension
    {
        None   = 0,
        Vsf    = 1,
        Rcs    = 2,
        Drw    = 3,
        Dgn    = 4,
        Stl    = 5,
        Obj    = 6,
        Prc    = 7,
        Ifc    = 8
    };
    
    TvAndCore();
    ~TvAndCore();

    // global params
    void setGlobalParams(const TvAndGlobalParameters& params) { m_globalParams = params; }
    TvAndGlobalParameters getGlobalParameters() const { return m_globalParams; }
    void applyGlobalParams();

    // release data
    void release();
    // open file
    OdString openFile(const OdString& filePath);
    // setup device with context
    OdString setupDevice(OSWindowGLContext context, const OdTvDCRect& rect);
    // update device
    void update();
    // resize device
    void resizeDevice(int xMin, int xMax, int yMin, int yMax);
    // get active OdTvGsViewId
    OdTvGsViewId getActiveTvViewId() const;
    OdTvGsViewPtr getActiveTvViewPtr() const;
    // get visualize extended view
    OdTvExtendedView* getActiveTvExtendedView();
    // set current animation
    void setAnimation(OdTvAnimation *pAnimation) { m_pAnimation = pAnimation; }
    // get block status of update
    bool isBlocked() const { return m_bIsBlocked; }
    // methods for stard and finish dragger
    void startDragger(OdTvDraggerPtr pNewDragger, bool bUseCurrentAsPrevious = false);
    void finishDragger();
    // get dragger pointer
    OdTvDragger* getActiveDragger() { return m_pActiveDragger.get(); }
    // perform action after dragger
    void actionsAfterDragger(eDraggerResult res);
    // dragger events
    eDraggerResult onTouchDown(int x, int y);
    void onTouchMove(int x, int y);
    eDraggerResult onTouchUp(int x, int y);
    eDraggerResult onProcessEnter();
    void onProcessBackspace();
    void onProcessText(const OdString& text);
    // perform zoom event
    void zoom(double delta, double x, double y);
    // run navigation command
    void runNavigationAction(TvAndCore::NavigationAction navAct);
    // run change view command
    void set3DView(OdTvExtendedView::e3DViewType type);
    // regen
    void regenVisible();
    // projection
    bool isPerspective() const;
    void setProjection(OdTvGsView::Projection projType);
    // render mode
    void runRenderMode(OdTvGsView::RenderMode newMode);
    OdTvGsView::RenderMode getRenderMode();
    // markups
    void runMarkupAction(TvAndCore::MarkupAction act);
    void disableMarkups();
    OdString isSaveMarkupAvaliable() const;
    OdString saveMarkup(const OdString& markupName);
    OdString isLoadMarkupAvaliable() const;
    OdString loadMarkup(const OdString& markupName);
    // begin fixed frame rate mode, if need
    void performFixedFrameRate();
    // finish fixed frame rate mode
    void finishFixedFrameRate();
    // Cutting plane methods
    void onAppearSectioningPanel(bool bAppear);
    bool setShowCuttingPlanes(bool bShow);
    bool addCuttingPlane(const OdTvVector& axis, OdTvResult* rc = NULL);
    void onAddCuttingPlane(const OdTvVector& axis);
    void setCuttingPlanesFilled(bool bFill);
    void setCuttingPlanesFillingColor(OdUInt32 color);
    void removeCuttingPlanes();
    void onRemoveCuttingPlane(const OdTvEntityId& entId);
    //create visual representation of the cutting planes
    void drawCuttingPlane(OdUInt32 index, bool bNeedNotifyDragger = false);
    //special method for the definition the size of the visual representation of the cutting planes
    double getMainModelExtentsDistance() const;
    // cutting planes model/view
    OdTvGsViewId getCuttingPlanesViewId() const { return m_cuttingPlanesViewId; }
    OdTvModelId getCuttingPlanesModelId() const { return m_cuttingPlanesModelId; }
    // get sectioning options
    TvAndSectioningOptions* getSectioningOptions() { return &m_sectioningOptions; }
    bool isCuttingPlanesVisible() const { return m_sectioningOptions.getShown(); }
    bool isCuttingPlanesFilled() const { return m_sectioningOptions.getFilled(); }
    // get app reg id
    OdTvRegAppId getAppRegId() const { return m_appTvId; }
    // collide
    OdString runCollide();

    long getTotalTime() const { return (long)m_databaseInfo.getTotalTime(); }

    ImportParamsContainer getImportParamsContainer() { return m_importParamsContainer; }

    void setDwgImportParams(const OdTvDwgImportParams& params) { m_importParamsContainer.dwgParams = params; }

    void save(const OdString& fileName, bool bPartialIndexing);

    void setProgressMeter(TvAndProgressMeter* pMeter) { m_pProgressMeter = pMeter; }

    bool addGroundShadow();
    bool isViewAllowGroundShadow();

    bool exportToPdf(bool b3D) const;

private:
    void init();
    void screenDolly(int x, int y);
    void syncParams(OdTvBaseImportParams* pParams);
   
private:
    OdTvDatabaseId m_TvDatabaseId;
    OdTvGsDeviceId m_TvDeviceId;
    OdTvModelId    m_TvMainModelId;
    // Draggers model id
    OdTvModelId     m_TvDraggersModelId;
    // Markups model id
    OdTvModelId     m_TvMarkupsModelId;
    OdTvRegAppId    m_appTvId;
    TvAndDatabaseInfo m_databaseInfo;
    TvAndGlobalParameters m_globalParams;
    bool m_bIsBlocked;
    // Current dragger pointer
    OdTvDraggerPtr  m_pActiveDragger;
    //index of the wcs viewport (should be update on resize)
    std::map < OdTvGsViewId, OdTvExtendedView* > m_tvExtendedViewsMap;
    //pointer to the animation
    OdTvAnimation* m_pAnimation;
    // file extension
    FileExtension m_fileExt;
    // limit manager for low memory
    TvAndLimitManager m_limitator;
    // initialized flag, need for measure first update time
    bool m_bIsInitialized;
    // model statistic info
    OdTvGeometryStatistic m_modelStat;
    //options for the cutting plane
    TvAndSectioningOptions m_sectioningOptions;
    // view for display cutting planes
    OdTvGsViewId m_cuttingPlanesViewId;
    // model for cutting planes
    OdTvModelId m_cuttingPlanesModelId;
    // view params for compare
    TvAndViewParamsComparator m_viewParams;
    // flag for regen aborting
    bool m_bRegenAbort;
    // flag for low memory import file
    bool m_bLowMemory;
    bool m_bPartial;
    // back delta for text markup dragger
    OdTvVector m_backDelta;

    ImportParamsContainer m_importParamsContainer;

    TvAndProgressMeter* m_pProgressMeter;

    OdTvGroundShadow m_groundShadow;
};

// class for regen aborting
class TvAndRegenAbortImpl : public OdTvRegenAbort
{
public:
    TvAndRegenAbortImpl()
    {
        m_bAbort = false;
        m_pTimer = OdPerfTimerBase::createTiming();
        m_pTimer->start();
    }
    
    ~TvAndRegenAbortImpl()
    {}
    
    virtual bool regenAbort() const
    {
        if( m_bAbort )
            return true;
        
        double time = m_pTimer->permanentSec();
        m_pTimer->stop();
        if(time > 0.5)
        {
            m_bAbort = true;
            return true;
        }
        return false;
    }
    
protected:
    mutable bool m_bAbort;
    OdPerfTimerBase* m_pTimer;
};

#endif //TVANDCORE_H
