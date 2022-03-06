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

#ifndef TviCore_hpp
#define TviCore_hpp

#include <stdio.h>
#include "TviGlobalParameters.hpp"
#include "TviLimitManager.hpp"
#include "TviDatabaseInfo.h"
// Visualize SDK
#include "TvFactory.h"
#include "TvImport.h"
#include "Tools/TvDragger.h"
#include "Tools/TvExtendedView.h"
#include "Tools/TvMarkupDraggers.h"
#include "TvGsView.h"
#include "../BaseViewController.h"

class TviDiffViewParams
{
public:
    TviDiffViewParams()
    : viewPos(0., 0., 0.), viewTarget(0., 0., 0.)
    , viewUpVect(0., 0., 0.), viewFieldWidth(0.), viewFieldHeight(0.)
    { };
    
    TviDiffViewParams(const OdTvGsViewId& viewId)
    : viewPos(0., 0., 0.), viewTarget(0., 0., 0.)
    , viewUpVect(0., 0., 0.), viewFieldWidth(0.), viewFieldHeight(0.)
    {
        if(!viewId.isNull())
        {
            OdTvGsViewPtr pView = viewId.openObject();
            if(!pView.isNull())
            {
                viewPos = pView->position();
                viewTarget = pView->target();
                viewUpVect = pView->upVector();
                viewFieldWidth = pView->fieldWidth();
                viewFieldHeight = pView->fieldHeight();
            }
        }
    };
    ~TviDiffViewParams(){};
    
    bool operator!=(const TviDiffViewParams& params) const
    {
        if (viewPos != params.viewPos)
            return true;
        
        if (viewTarget != params.viewTarget)
            return true;
        
        if (viewUpVect != params.viewUpVect)
            return true;
        
        if (viewFieldWidth != params.viewFieldWidth)
            return true;
        
        if (viewFieldHeight != params.viewFieldHeight)
            return true;
        
        return false;
    }
    
public:
    OdTvPoint viewPos;
    OdTvPoint viewTarget;
    OdTvVector viewUpVect;
    double viewFieldWidth;
    double viewFieldHeight;
};

/** \details
 This class implements the sectioning properties
 */

#define ODTVUI_CUTTINGPLANESMAXNUM 5

class TviSectioningOptions
{
public:
    TviSectioningOptions() : m_bShow(true), m_bFill(true), m_iFillingColor(ODRGBA(255, 0, 0, 255)) {}
    
    void setShown(bool bShow) { m_bShow = bShow; }
    bool getShown() const { return m_bShow; }
    
    void setFilled(bool bFill) { m_bFill = bFill; }
    bool getFilled() const { return m_bFill; }
    
    void setFillingColor(ODCOLORREF color) { m_iFillingColor = color; }
    ODCOLORREF getFillingColor() const { return m_iFillingColor; }
    
protected:
    
    bool m_bShow;
    bool m_bFill;
    ODCOLORREF m_iFillingColor;
};

class TviCore
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
    
    enum ProjectionType
    {
        Isometric   = 0,
        Perspective = 1
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
        Ifc
    };
    
    TviCore();
    ~TviCore();
    
    void openFile(const OdString& name, OdTvBaseImportParams* pParams, bool bImport, NSObject* context, const OdTvDCRect& rect);
    void update();
    void resizeDevice(long xMin, long xMax, long yMin, long yMax);
    // set/get global params
    void setGlobalParams(TviGlobalParameters* params) { m_pGlobalParams = params; }
    TviGlobalParameters* getGlobalParameters() const { return m_pGlobalParams; }
    void applyGlobalParams();
    // get active OdTvGsViewId
    OdTvGsViewId getActiveTvViewId() const;
    OdTvGsViewPtr getActiveTvViewPtr();
    // get visualize extended view
    OdTvExtendedView* getActiveTvExtendedView();
    // get dragger pointer
    OdTvDragger* getActiveDragger() { return m_pActiveDragger.get(); }
    // set current animation
    void setAnimation(OdTvAnimation *pAnimation) { m_pAnimation = pAnimation; }
    // perform action after dragger
    void actionsAfterDragger(eDraggerResult res);
    // perform zoom event
    void zoom(double delta, double x, double y);
    // perform navigation action
    void runNavigationAction(NavigationAction navAct);
    // change view
    void set3DView(OdTvExtendedView::e3DViewType type);
    // regen action
    void runRegenAction(RegenAction regenAct);
    // change visual style
    void runRenderMode(OdTvGsView::RenderMode newMode);
    // perform markup action
    void runMarkupAction(MarkupAction act);
    // change projecton type of view
    void setProjection(ProjectionType projType);
    // set parent controller
    void attach(BaseViewController* controller) { m_pParentController = controller; }
    void detach() { m_pParentController = NULL; }
    // show popup message
    void showMessage(NSString* title, NSString* msg);
    // save markup
    bool saveMarkup(NSString* markupName);
    // load markup
    bool loadMarkup(NSString* markupName);
    // remove markup
    bool removeMarkup(NSString* markupName);
    // get/set file extension
    void setFileExtension(FileExtension fileExt) { m_fileExt = fileExt; }
    FileExtension getFileExtension() const { return m_fileExt; }
    // update partial
    void autoUpdate();
    // save file
    bool saveFile(NSString* filePath, bool bPartialIndexing);
    // get model statistic
    OdTvGeometryStatistic* getModelStatistic();
    // disable active markups
    void disableMarkups();
    // begin fixed frame rate mode, if need
    void performFixedFrameRate();
    // finish fixed frame rate mode
    void finishFixedFrameRate();
    // Cutting plane methods
    void onAppearSectioningPanel(bool bAppear);
    bool setShowCuttingPlanes(bool bShow);
    bool addCuttingPlane(const OdTvVector& axis, OdTvResult* rc = NULL);
    void setCuttingPlanesFilled(bool bFill);
    void setCuttingPlanesFillingColor(OdUInt32 color);
    void removeCuttingPlanes();
    void onRemoveCuttingPlane(const OdTvEntityId& entId);
    //create visual representation of the cutting planes
    void drawCuttingPlane(OdUInt32 index, bool bNeedNotifyDragger = false);
    //special method for the definition the size of the visual representation of the cutting planes
    double getMainModelExtentsDistance() const;
    
    OdTvGsViewId getCuttingPlanesViewId() const { return m_cuttingPlanesViewId; }
    OdTvModelId getCuttingPlanesModelId() const { return m_cuttingPlanesModelId; }
    
    // get sectioning options
    TviSectioningOptions* getSectioningOptions() { return &m_sectioningOptions; }

    // get app reg id
    OdTvRegAppId getAppRegId() const { return m_appTvId; }
    
    // run collide dragger
    bool runCollide();
    
    // reset active dragger indicator
    void resetDraggerIndicator();
    
    // methods for stard and finish dragger
    void finishDragger();
    void startDragger(OdTvDraggerPtr pNewDragger, bool bUseCurrentAsPrevious = false);
    
    // methods for the regen aborting
    void setRegenAbort(bool bRegenAbort) { m_bRegenAbort = bRegenAbort; }
    bool getRegenAbort() const { return m_bRegenAbort; }
    
    bool isValid() const { return !m_TvDatabaseId.isNull() && !m_TvMainModelId.isNull() && !m_TvDeviceId.isNull();  }
    
    OdTvModelId getMarkupModelId() const { return m_TvMarkupsModelId; }
	
	bool exportToPdf(bool b3D) const;
    
private:
    void release();
    void setupDevice(NSObject* context, const OdTvDCRect& rect);
    void screenDolly(int x, int y);
    
private:
    OdTvDatabaseId m_TvDatabaseId;
    OdTvGsDeviceId m_TvDeviceId;
    OdTvModelId    m_TvMainModelId;
    // Draggers model id
    OdTvModelId     m_TvDraggersModelId;
    // Markups model id
    OdTvModelId     m_TvMarkupsModelId;
    OdTvRegAppId    m_appTvId;
    TviDatabaseInfo m_databaseInfo;
    TviGlobalParameters *m_pGlobalParams;
    bool m_bIsBlocked;
    // Current dragger pointer
    OdTvDraggerPtr  m_pActiveDragger;
    //index of the wcs viewport (should be update on resize)
    std::map < OdTvGsViewId, OdTvExtendedView* > m_tvExtendedViewsMap;
    //pointer to the animation
    OdTvAnimation* m_pAnimation;
    // render controller
    BaseViewController* m_pParentController;
    // file extension
    FileExtension m_fileExt;
    // limit manager for low memory
    TviLimitManager m_limitator;
    // initialized flag, need for measure first update time
    bool m_bIsInitialized;
    // model statistic info
    OdTvGeometryStatistic m_modelStat;
    //options for the cutting plane
    TviSectioningOptions m_sectioningOptions;
    // view for display cutting planes
    OdTvGsViewId m_cuttingPlanesViewId;
    // model for cutting planes
    OdTvModelId m_cuttingPlanesModelId;
    // view params for compare
    TviDiffViewParams m_viewParams;
    // flag for regen aborting
    bool m_bRegenAbort;
    // flag for low memory import file
    bool m_bLowMemory;
};

// class for regen aborting
class TviRegenAbortImpl : public OdTvRegenAbort
{
public:
    TviRegenAbortImpl( TviCore* pCore )
    {
        m_pCore = pCore;
        m_bAbort = false;
        m_pCurDate = [NSDate date];
    }
    
    TviRegenAbortImpl()
    {}
    
    virtual bool regenAbort() const
    {
        if( m_bAbort )
            return true;
        
        double time = [m_pCurDate timeIntervalSinceNow] * (-1);
        if(time > 0.5)
        {
            m_bAbort = true;
            return true;
        }
        return false;
//        m_bAbort = m_pCore->getRegenAbort();
//        return m_bAbort;
    }
    
protected:
    TviCore* m_pCore;
    mutable bool m_bAbort;
    NSDate* m_pCurDate;
};

#endif /* TviCore_hpp */
