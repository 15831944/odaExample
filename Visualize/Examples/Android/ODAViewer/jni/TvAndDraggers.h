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

#ifndef TVANDDRAGGERS_H
#define TVANDDRAGGERS_H

#include <stdio.h>
#include "Tools/TvDragger.h"
#include "TvAndCore.h"
#include "TvAndAxisControl.h"

//structure for storing viewport params
struct OdTvViewportParams
{
  OdTvViewportParams();

  //save camera params
  void store(OdTvGsViewPtr pView);

  //restore saved param to view
  void setup(OdTvExtendedView* pTvExtendedView) const;

  OdTvPoint position;
  OdTvPoint target;
  OdTvVector up;
  double fieldWidth;
  double fieldHeight;
  OdTvGsView::Projection projectionType;
};

////////////////////////////////////////////
////// TvAndBaseDragger implementation ///////
////////////////////////////////////////////
class TvAndBaseDragger : public OdTvDragger
{
public :
    TvAndBaseDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvDraggersModelId, TvAndGlobalParameters* pParams)
    : OdTvDragger (tvDeviceId, tvDraggersModelId), m_pGlobalParams(pParams), m_bFixedFrameRateEnabled(false) {}
    ~TvAndBaseDragger() {}
    
    virtual eDraggerResult drag(int x, int y);
    virtual eDraggerResult nextpointup(int x, int y);
    
protected:
    TvAndGlobalParameters* m_pGlobalParams;
    bool m_bFixedFrameRateEnabled;
};

////////////////////////////////////////////
////// TvAndPanDragger implementation ////////
////////////////////////////////////////////
class TvAndPanDragger : public TvAndBaseDragger
{
    public :
    TvAndPanDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvDraggersModelId, TvAndGlobalParameters* pParams)
    : TvAndBaseDragger (tvDeviceId, tvDraggersModelId, pParams) {}
    ~TvAndPanDragger() {}
    
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
///// TvAndOrbitDragger implementation ///////
////////////////////////////////////////////
class TvAndOrbitDragger : public TvAndBaseDragger
{
public:
    TvAndOrbitDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvDraggersModelId, TvAndGlobalParameters* pParams);
    ~TvAndOrbitDragger() {}
    
    eDraggerResult start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView* pExtendedView);
    eDraggerResult nextpoint(int x, int y);
    eDraggerResult drag(int x, int y);
    eDraggerResult nextpointup(int x, int y);
    
private:
    OdTvDCPoint m_startCursorPosition;
    OdTvViewportParams m_viewportParams;
};

////////////////////////////////////////////
/// TvAndZoomWindowDragger implementation ////
////////////////////////////////////////////
class TvAndZoomWindowDragger : public TvAndBaseDragger
{
public:
    TvAndZoomWindowDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvDraggersModelId, TvAndCore *pCore, TvAndGlobalParameters* pParams);
    ~TvAndZoomWindowDragger() {}
    
    eDraggerResult start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView* pExtendedView);
    eDraggerResult nextpoint(int x, int y);
    eDraggerResult drag(int x, int y);
    eDraggerResult nextpointup(int x, int y);
    OdTvDraggerPtr finish(eDraggerResult& rc);
    bool canFinish() { return true; }
    
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
    
    TvAndCore *m_pTvAndCore;
};

////////////////////////////////////////////
/// TvAndCuttingPlaneDragger implementation //
////////////////////////////////////////////

#define OD_TV_CUTTINGPLANE_SIZE_COEFF 1.3
#define OD_TV_CUTTINGPLANE_EDGE_DEFAULT_LINEWEIGHT 3
#define OD_TV_CUTTINGPLANE_EDGE_SELECTED_LINEWEIGHT 5

class TvAndCuttingPlaneDragger : public TvAndBaseDragger
{
    enum State
    {
        kWaitingForCutPlSelect = 0,
        kWaitingForAxisControlSelect = 1,
        kCuttingPlaneRotation = 2
    };
    
public:
    TvAndCuttingPlaneDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvDraggersModelId, TvAndGlobalParameters* pParams, TvAndCore* pCore);
    ~TvAndCuttingPlaneDragger();
    
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
    TvAndCore* m_pCore;
    
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
//// TvAndSelectionDragger implementation ////
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
class TvAndSelectionDragger : public TvAndBaseDragger
{
    enum State
    {
        kPoint = 0,
        kWindow = 1,
        kCrossing = 2
    };
    public :
    TvAndSelectionDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvModelId, OdTvModelId& tvDraggersModelId, TvAndGlobalParameters* pParams, TvAndCore* pCore);
    ~TvAndSelectionDragger();
    
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
    TvAndCore* m_pCore;
    
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
///// TvAndCollideDragger implementation /////
////////////////////////////////////////////

/** \details
 This class implements the collide dragger
 */
class TvAndCollideDragger : public TvAndSelectionDragger
{
    enum CoolideState
    {
        kSelection = 0,
        kBasePointWaiting = 1,
        kCollision = 2
    };
    
public:
    TvAndCollideDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvModelId, OdTvModelId& tvDraggersModelId, TvAndGlobalParameters *pParams, TvAndCore* pCore);
    ~TvAndCollideDragger();
    
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


#endif //TVANDDRAGGERS_H
