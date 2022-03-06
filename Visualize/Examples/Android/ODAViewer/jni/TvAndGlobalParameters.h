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

#ifndef TVANDGLOBALPARAMETERS_H
#define TVANDGLOBALPARAMETERS_H

#include <stdio.h>

#define OD_TV_APP_NAME "ODA Viewer"

struct TvAndDwgImportParams
{
    bool m_bStoreSource;
    bool m_bClearEmptyObjects;
    bool m_bEnableMT;
    int m_iThreadsCount;
    bool m_bImportBrepAsBrep;
    bool m_bLowMemoryImport;
    int m_iBackgroundColor;

    TvAndDwgImportParams() : m_bStoreSource(false), m_bClearEmptyObjects(false), m_bEnableMT(false)
    , m_iThreadsCount(4), m_bImportBrepAsBrep(false), m_bLowMemoryImport(false), m_iBackgroundColor(0) {}
};

struct TvAndStlImportParams
{
    bool m_bFixNormals;
    bool m_bUnifyDuplicatedVertices;
    bool m_bCalcNormalsAtVertices;

    TvAndStlImportParams() : m_bFixNormals(true), m_bUnifyDuplicatedVertices(true), m_bCalcNormalsAtVertices(false) {}
};

struct TvAndPrcImportParams
{
    bool m_bStoreSource;
    bool m_bClearEmptyObjects;
    bool m_bRearrangeObjects;
    bool m_bImportBrepAsBrep;

    TvAndPrcImportParams() : m_bStoreSource(false), m_bClearEmptyObjects(true), m_bRearrangeObjects(true)
    , m_bImportBrepAsBrep(false) {}
};

struct TvAndDgnImportParams
{
    bool m_bStoreSource;
    bool m_bClearEmptyObjects;
    bool m_bUseIsolinesFor3DObjects;

    TvAndDgnImportParams() : m_bStoreSource(false), m_bClearEmptyObjects(true), m_bUseIsolinesFor3DObjects(true) {}
};

struct TvAndObjImportParams
{
    bool m_bCalculateNormalsAtVertices;
    bool m_bFlipUVCoordinateSystem;
    bool m_bImportBrepAsBrep;

    TvAndObjImportParams() : m_bCalculateNormalsAtVertices(false), m_bFlipUVCoordinateSystem(false), m_bImportBrepAsBrep(false) {}
};

struct TvAndImportParamContainer
{
    TvAndDwgImportParams m_dwgParams;
    TvAndStlImportParams m_stlParams;
    TvAndPrcImportParams m_prcParams;
    TvAndDgnImportParams m_dgnParams;
    TvAndObjImportParams m_objParams;
};

class TvAndGlobalParameters
{
public:
    TvAndGlobalParameters()
    {
        m_bWcsEnabled = true;
        m_bFpsEnabled = false;
        m_bAnimationEnabled = true;
        m_bPartialOpen = false;
        m_bUseLimitManager = false;
        m_bUseSceneGraph = false;
        m_nMemoryLimit = 1000;
        m_bFixedFrameRate = true;
        m_dFpsValue = 15.;
    }
    
    void setWcsEnabled(bool bValue) { m_bWcsEnabled = bValue; }
    void setFpsEnabled(bool bValue) { m_bFpsEnabled = bValue; }
    void setAnimationEnabled(bool bValue) { m_bAnimationEnabled = bValue; }
    void setPartialOpen(bool bValue) { m_bPartialOpen = bValue; }
    void setUseLimitManager(bool bValue) { m_bUseLimitManager = bValue; }
    void setUseSceneGraph(bool bValue) { m_bUseSceneGraph = bValue; }
    void setMemoryLimit(unsigned long value) { m_nMemoryLimit = value; }
    void setFixedFrameRate(bool bValue) { m_bFixedFrameRate = bValue; }
    void setFpsValue(double dValue) { m_dFpsValue = dValue; }
    
    bool getWcsEnabled() const { return m_bWcsEnabled; }
    bool getFpsEnabled() const { return m_bFpsEnabled; }
    bool getAnimationEnabled() const { return m_bAnimationEnabled; }
    bool getPartialOpen() const { return m_bPartialOpen; }
    bool getUseLimitManager() const { return m_bUseLimitManager; }
    bool getUseSceneGraph() const { return m_bUseSceneGraph; }
    unsigned long getMemoryLimit() const { return m_nMemoryLimit; }
    bool getFixedFrameRate() const { return m_bFixedFrameRate; }
    double getFpsValue() const { return m_dFpsValue; }

private:
    bool m_bWcsEnabled;
    bool m_bFpsEnabled;
    bool m_bAnimationEnabled;
    bool m_bPartialOpen;
    bool m_bUseLimitManager;
    bool m_bUseSceneGraph;
    unsigned long m_nMemoryLimit;
    bool m_bFixedFrameRate;
    double m_dFpsValue;

public:
    TvAndImportParamContainer m_importContainer;
};

#endif //TVANDGLOBALPARAMETERS_H
