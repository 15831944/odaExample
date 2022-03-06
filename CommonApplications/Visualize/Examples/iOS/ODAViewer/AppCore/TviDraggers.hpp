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

#ifndef TviDraggers_hpp
#define TviDraggers_hpp

#include <stdio.h>
#include "Tools/TvDragger.h"
#include "TviGlobalParameters.hpp"

#include "TviCore.hpp"

#include "TviAxisControl.hpp"

////////////////////////////////////////////
////// TviBaseDragger implementation ///////
////////////////////////////////////////////
class TviBaseDragger : public OdTvDragger
{
public :
    TviBaseDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvDraggersModelId, TviGlobalParameters* pParams)
    : OdTvDragger (tvDeviceId, tvDraggersModelId), m_pGlobalParams(pParams), m_bFixedFrameRateEnabled(false) {}
    ~TviBaseDragger() {}
    
    virtual eDraggerResult drag(int x, int y);
    virtual eDraggerResult nextpointup(int x, int y);
    
protected:
    TviGlobalParameters* m_pGlobalParams;
    bool m_bFixedFrameRateEnabled;
};

////////////////////////////////////////////
////// TviPanDragger implementation ////////
////////////////////////////////////////////
class TviPanDragger : public TviBaseDragger
{
    public :
    TviPanDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvDraggersModelId, TviGlobalParameters* pParams)
    : TviBaseDragger (tvDeviceId, tvDraggersModelId, pParams) {}
    ~TviPanDragger() {}
    
    virtual eDraggerResult start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView* pExtendedView);
    virtual eDraggerResult nextpoint(int x, int y);
    virtual eDraggerResult drag(int x, int y);
    virtual eDraggerResult nextpointup(int x, int y);
    
private:
    // last cliked or moved point (WCS)
    OdGePoint3d m_prevPt;
    // last camera position (WCS)
    OdGePoint3d m_pos;
};

////////////////////////////////////////////
///// TviOrbitDragger implementation ///////
////////////////////////////////////////////
class TviOrbitDragger : public TviBaseDragger
{
public:
    TviOrbitDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvDraggersModelId, TviGlobalParameters* pParams);
    ~TviOrbitDragger() {}
    
    eDraggerResult start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView* pExtendedView);
    eDraggerResult nextpoint(int x, int y);
    eDraggerResult drag(int x, int y);
    eDraggerResult nextpointup(int x, int y);
    
private:
    // last cliked or moved point (ECS)
    OdGePoint3d m_prevPt;
    // mouse move to rotation angle conversion coefficient
    double m_D;
    // center of the scene
    OdGePoint3d     m_viewCenter;
};

////////////////////////////////////////////
/// TviZoomWindowDragger implementation ////
////////////////////////////////////////////
class TviZoomWindowDragger : public TviBaseDragger
{
public:
    TviZoomWindowDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvDraggersModelId, TviCore *pCore, TviGlobalParameters* pParams);
    ~TviZoomWindowDragger() {}
    
    eDraggerResult start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView* pExtendedView);
    eDraggerResult nextpoint(int x, int y);
    eDraggerResult drag(int x, int y);
    eDraggerResult nextpointup(int x, int y);
    OdTvDraggerPtr finish(eDraggerResult& rc);
    
private:
    void updateFrame(bool bCreate);
    
private:
    
    // first clicked point (WCS)
    OdGePoint3d m_firstPt;
    
    // first clicked point (DCS) pixels
    OdGePoint2d m_firstPt_device;
    
    // last drag point (WCS)
    OdGePoint3d m_lastDragPt;
    
    // need to control the ::start called first time or not
    bool m_bJustCreatedObject;
    
    // temporary geometry
    OdTvEntityId m_entityId;
    OdTvGeometryDataId m_frameId;
    
    // points for creating the polygon frame
    OdTvPointArray m_pts;
    
    TviCore *m_pTviCore;
};

////////////////////////////////////////////
/// TviCuttingPlaneDragger implementation //
////////////////////////////////////////////

#define OD_TV_CUTTINGPLANE_SIZE_COEFF 1.3
#define OD_TV_CUTTINGPLANE_EDGE_DEFAULT_LINEWEIGHT 3
#define OD_TV_CUTTINGPLANE_EDGE_SELECTED_LINEWEIGHT 5

/** \details
 This class implements the cutting plane dragger
 */
class TviCuttingPlaneDragger : public TviBaseDragger
{
    enum State
    {
        kWaitingForCutPlSelect = 0,
        kWaitingForAxisControlSelect = 1,
        kCuttingPlaneRotation = 2
    };
    
public:
    TviCuttingPlaneDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvDraggersModelId, TviGlobalParameters* pParams, TviCore* pCore);
    ~TviCuttingPlaneDragger();
    
    void onCuttingPlaneAdded(OdTvEntityId entId);
    void onRemoveCuttingPlanes();
    void setCanBeFinished(bool bCanFinish) { m_bCanFinish = bCanFinish; }
    
    //rewrite a set of virtual methods
    virtual eDraggerResult start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView* pExtendedView);
    virtual eDraggerResult nextpoint(int x, int y);
    virtual eDraggerResult drag(int x, int y);
    virtual eDraggerResult processEscape();
    virtual eDraggerResult processDelete();
    virtual eDraggerResult nextpointup(int x, int y);
    virtual bool           canFinish();
    virtual OdTvDraggerPtr finish(eDraggerResult& rc);
    virtual void           notifyAboutViewChange(eDraggerViewChangeType notify);
    
protected:
    //merge two selection sets
    void merge(const OdTvSelectionSetPtr& pSSet);
    
    // remove selected cutting plane
    void removeSelectedCuttingPlane();
    
    //highlight the appropriate cutting plane
    void highlight(const OdTvEntityId& planeId, bool bHighlight);
    
protected:
    // application core
    TviCore* m_pCore;
    
    // State of this dragger
    State m_state;
    
    // Options used for the selection of cutting planes
    OdTvSelectionOptions m_SelectionOptions;
    
    //axis control
    OdTvUIRotationAxisControl m_axisControl;
    
    //map for storing the cutting planes entities
    std::map<OdTvEntityId, OdUInt32> m_cuttingPlanes;
    
    // view for display cutting planes
    OdTvGsViewId m_cuttingPlanesViewId;
    
    // model for cutting planes
    OdTvModelId m_cuttingPlanesModelId;
    
    // selected cutting plane
    OdTvEntityId m_selectedCuttingPlaneEntityId;
    
    // highlighted cutting plane
    OdTvEntityId m_highlightedCuttingPlaneId;
    
    // indicate that dragger can be finished
    bool m_bCanFinish;
};


////////////////////////////////////////////
//// TviSelectionDragger implementation ////
////////////////////////////////////////////

struct OdTvUISelectionOptions
{
    int level;
    int mode;
    int pickBoxSize;
    bool m_bEnableHoverHighlight;
    
    OdTvUISelectionOptions() : level(0), mode(5), pickBoxSize(3), m_bEnableHoverHighlight(false){};
    
    OdTvUISelectionOptions(const OdTvSelectionOptions& opt, bool bEnableHoverHighlight = false) : level(0), mode(5), pickBoxSize(3)
    {
        level = opt.getLevel();
        mode = opt.getMode();
        pickBoxSize = opt.getPickBoxSize();
        m_bEnableHoverHighlight = bEnableHoverHighlight;
    }
    
    OdTvSelectionOptions getSelectionOptions()
    {
        OdTvSelectionOptions opt;
        opt.setLevel((OdTvSelectionOptions::Level)level);
        opt.setMode((OdTvSelectionOptions::Mode)mode);
        opt.setPickBoxSize((OdUInt16)pickBoxSize);
        return opt;
    }
    
    bool getEnableHoverHighlight()
    {
        return m_bEnableHoverHighlight;
    }
    
    ~OdTvUISelectionOptions() {}
};


/** \details
 This class implements the selecting dragger
 */
class TviSelectionDragger : public TviBaseDragger
{
    enum State
    {
        kPoint = 0,
        kWindow = 1,
        kCrossing = 2
    };
    public :
    TviSelectionDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvModelId, OdTvModelId& tvDraggersModelId, TviGlobalParameters* pParams, TviCore* pCore);
    ~TviSelectionDragger();
    
protected:
    virtual eDraggerResult start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView* pExtendedView);
    virtual eDraggerResult nextpoint(int x, int y);
    virtual eDraggerResult drag(int x, int y);
    virtual eDraggerResult processEscape();
    
    //update selection frame
    void updateFrame(bool bCreate, int x, int y);
    
    //prepare temporary view and model
    void enableTemporaryObjects();
    
    //remove temporary view and model
    void disableTemporaryObjects();
    
    //transform device pt to world in local temporary view
    OdGePoint3d toEyeToWorldLocal(int x, int y) const;
    
    //merge two selection sets
    virtual void merge(const OdTvSelectionSetPtr& pSSet);
    
    /** \details
     Return temporary view
     */
    OdTvGsViewId getTempViewId() const
    {
        return m_tempViewId;
    }
    
    // highlight data for the whole selection set
    void highlight(const OdTvSelectionSetPtr& pSSet, bool bDoIt) const;
    
    //highlight data for selection set iterator
    void highlight(const OdTvSelectionSetIteratorPtr& pIter, bool bDoIt) const;
    
    /** \details
     Return selection set
     */
    OdTvSelectionSetPtr getSelectionSet() const
    {
        return m_pSSet;
    };
    
    /** \details
     Return selection options
     */
    OdTvSelectionOptions* getSelectionOptions()
    {
        return &m_SelectionOptions;
    }
    
protected:
    
    // Options for selection set.
    OdTvSelectionOptions m_SelectionOptions;
    
    // model for the selection
    OdTvModelId   m_modelId;
    
    //app core
    TviCore* m_pCore;
    
    // axis control
    OdTvUIAxisControl m_axisControl;
    
private:
    
    //current selection set
    OdTvSelectionSetPtr m_pSSet;
    
    //highlighted by hover
    OdTvSelectionSetPtr m_pHoverHighlighted;
    
    //dragger state
    State         m_localstate;
    
    // first cliked point (Device CS)
    OdTvDCPoint   m_firstDevicePt;
    
    // temporary view for draggers geometry
    OdTvGsViewId  m_tempViewId;
    
    // temporary model for draggers geometry
    OdTvModelId   m_tempModelId;
    
    // specific linetype for the selector
    OdTvLinetypeId m_frameLinetypeId;
    
    // temporary geometry
    OdTvEntityId m_entityId;
    OdTvGeometryDataId m_frameId;
    OdTvGeometryDataId m_frameIdContourId;
};

////////////////////////////////////////////
///// TviCollideDragger implementation /////
////////////////////////////////////////////

/** \details
 This class implements the collide dragger
 */
class TviCollideDragger : public TviSelectionDragger
{
    enum CoolideState
    {
        kSelection = 0,
        kBasePointWaiting = 1,
        kCollision = 2
    };
    
public:
    TviCollideDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvModelId, OdTvModelId& tvDraggersModelId, TviGlobalParameters *pParams, TviCore* pCore);
    ~TviCollideDragger();
    
    virtual eDraggerResult processEnter();
    virtual void notifyAboutViewChange(eDraggerViewChangeType notify);
    virtual bool canFinish() { return true; };
    virtual eDraggerResult start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView* pExtendedView);
    virtual eDraggerResult nextpoint(int x, int y);
    virtual eDraggerResult nextpointup(int x, int y);
    virtual eDraggerResult drag(int x, int y);
    virtual eDraggerResult processEscape();
    
protected:
    
    //merge two selection sets
    virtual void merge(const OdTvSelectionSetPtr& pSSet);
    
    //check if need to highlight
    bool needHighlight(const OdTvSelectionSetIteratorPtr& pCollidedIterIter) const;
    
    //check if entity has shell
    bool hasShell(OdTvEntityPtr pEntity) const;
    
protected:
    
    // State of this dragger.
    CoolideState m_collideDraggerState;
    
    // Collision selection set.
    OdTvSelectionSetPtr m_pCollisionSSet;
    
    // Result of collision
    OdTvCollidedResultPtr m_pPrevHLTSet;
    
    // Mark the it is need to unhighlight
    bool m_bNeedUnhighlight;
    
    //selection options for the collide result
    OdTvSelectionOptions m_resultSelectionOpt;
    
    OdVector<OdTvEntityId>        m_baseEntities;
    OdVector<OdTvGeometryDataId>  m_baseGeometries;
};

#endif /* TviDraggers_hpp */
