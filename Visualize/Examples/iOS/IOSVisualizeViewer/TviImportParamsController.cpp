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
#include "TviImportParamsController.h"

TviImportParamsController *TviImportParamsController::m_pInstance = 0;

////////////////////////////////////////////////////////////
///     TviBaseImportParams methods implementation       ///
////////////////////////////////////////////////////////////

TviBaseImportParams::TviBaseImportParams(QObject *parent)
    : QObject (parent)
{

}

////////////////////////////////////////////////////////////
///  TviImportParamsController methods implementation    ///
////////////////////////////////////////////////////////////

TviImportParamsController::TviImportParamsController(QObject *parent)
    : QObject(parent), m_pObjParams(NULL), m_pDrwParams(NULL), m_pRcsParams(NULL)
    , m_pDgnParams(NULL), m_pStlParams(NULL), m_pPrcParams(NULL)
{
}

QObject *TviImportParamsController::getObjImportParams()
{
    if(!m_pObjParams)
        m_pObjParams = new TviObjImportParams(this);
    return  m_pObjParams;
}

QObject *TviImportParamsController::getDrwImportParams()
{
    if(!m_pDrwParams)
        m_pDrwParams = new TviDrwImportParams(this);
    return  m_pDrwParams;
}

QObject *TviImportParamsController::getRcsImportParams()
{
    if(!m_pRcsParams)
        m_pRcsParams = new TviRcsImportParams(this);
    return  m_pRcsParams;
}

QObject *TviImportParamsController::getDgnImportParams()
{
    if(!m_pDgnParams)
        m_pDgnParams = new TviDgnImportParams(this);
    return  m_pDgnParams;
}

QObject *TviImportParamsController::getStlImportParams()
{
    if(!m_pStlParams)
        m_pStlParams = new TviStlImportParams(this);
    return  m_pStlParams;
}

QObject *TviImportParamsController::getPrcImportParams()
{
    if(!m_pPrcParams)
        m_pPrcParams = new TviPrcImportParams(this);
    return  m_pPrcParams;
}

void TviImportParamsController::setWindowSize(const QSize &size)
{
    m_windowSize = size;
    OdTvDCRect rect = OdTvDCRect( 0, size.width(), size.height(), 0 );
    if(m_pDrwParams)
        m_pDrwParams->setDCRect( rect );
    if(m_pDgnParams)
        m_pDgnParams->setDCRect( rect );
    if(m_pPrcParams)
        m_pPrcParams->setDCRect( rect );
}

////////////////////////////////////////////////////////////
///     TviObjImportParams methods implementation       ////
////////////////////////////////////////////////////////////

TviObjImportParams::TviObjImportParams(QObject *parent)
    : TviBaseImportParams (parent)
{
    fillFields(&m_objParams);
}

void TviObjImportParams::applyParams()
{
    m_objParams.setCalculateNormals(m_bCalculateNormals);
    m_objParams.setBrepFlipUVCoordinates(m_bFlipUVCoord);
    m_objParams.setDefaultColor( ODRGB(m_baseColor.red(), m_baseColor.green(), m_baseColor.blue()) );
}

void TviObjImportParams::resetParams()
{
    OdTvObjImportParams objParams;
    fillFields(&objParams);
}

void TviObjImportParams::fillFields(OdTvObjImportParams *pParams)
{
    m_bCalculateNormals = pParams->getCalculateNormals();
    m_bFlipUVCoord = pParams->getBrepFlipUVCoordinates();
    OdUInt32 color = pParams->getDefaultColor();
    m_baseColor = QColor( ODGETRED(color), ODGETGREEN(color), ODGETBLUE(color) );
}

////////////////////////////////////////////////////////////
///     TviDrwImportParams methods implementation       ////
////////////////////////////////////////////////////////////

TviDrwImportParams::TviDrwImportParams(QObject *parent)
    : TviBaseImportParams(parent)
{
    fillFields(&m_dwgParams);
}

void TviDrwImportParams::applyParams()
{
    m_dwgParams.setObjectNaming( m_bObjectNaming );
    m_dwgParams.setStoreSourceObjects( m_bStoreSource );
    m_dwgParams.setClearEmptyObjects( m_bClearEmptyObjects );
    m_dwgParams.setMultithreading( m_bEnableMultithreading );
    m_dwgParams.setCountOfThreads( m_iMaxThreads );
    m_dwgParams.setUseAdvancedTess( m_bUseAdvancedTess );
    m_dwgParams.setFacetRes( m_dFacetRes );
    m_dwgParams.setDCRect( OdTvDCRect(m_xMin, m_xMax, m_yMin, m_yMax) );
    m_dwgParams.setBackground( ODRGB(m_baseColor.red(), m_baseColor.green(), m_baseColor.blue()) );
    m_dwgParams.setOpenSourcePartial(m_bLowMemoryImport);
}

void TviDrwImportParams::resetParams()
{
    OdTvDwgImportParams dwgParams;
    fillFields(&dwgParams, true);
}

void TviDrwImportParams::setDCRect(const OdTvDCRect &rect)
{
    m_dwgParams.setDCRect(rect);
    m_xMin = rect.xmin;
    m_xMax = rect.xmax;
    m_yMin = rect.ymin;
    m_yMax = rect.ymax;
}

void TviDrwImportParams::fillFields(OdTvDwgImportParams *pParams, bool isReset)
{
    m_bObjectNaming = pParams->getObjectNaming();
    m_bStoreSource = pParams->getStoreSourceObjects();
    m_bClearEmptyObjects = pParams->getClearEmptyObjects();
    m_bEnableMultithreading = pParams->getMultithreading();
    m_iMaxThreads = pParams->getCountOfThreads();
    m_bUseAdvancedTess = pParams->getUseAdvancedTess();
    m_dFacetRes = pParams->getFacetRes();
    if(!isReset)
    {
        OdTvDCRect rect = pParams->getDCRect();
        m_xMin = rect.xmin;
        m_xMax = rect.xmax;
        m_yMin = rect.ymin;
        m_yMax = rect.ymax;
    }
    OdUInt32 color = pParams->getBackground();
    m_baseColor = QColor( ODGETRED(color), ODGETGREEN(color), ODGETBLUE(color) );
    m_bLowMemoryImport = pParams->getOpenSourcePartial();
}
////////////////////////////////////////////////////////////
///     TviRcsImportParams methods implementation       ////
////////////////////////////////////////////////////////////

TviRcsImportParams::TviRcsImportParams(QObject *parent)
    : TviBaseImportParams (parent)
{
    m_bIgnorePointSize = m_rcsParams.getIgnorePointSize();
    OdUInt32 color = m_rcsParams.getDefaultColor();
    m_baseColor = QColor( ODGETRED(color), ODGETGREEN(color), ODGETBLUE(color) );
}

void TviRcsImportParams::applyParams()
{
    m_rcsParams.setIgnorePointSize(m_bIgnorePointSize);
    m_rcsParams.setDefaultColor( ODRGB(m_baseColor.red(), m_baseColor.green(), m_baseColor.blue()) );
}

void TviRcsImportParams::resetParams()
{
    OdTvRcsImportParams rcsParams;
    m_bIgnorePointSize = rcsParams.getIgnorePointSize();
    OdUInt32 color = rcsParams.getDefaultColor();
    m_baseColor = QColor( ODGETRED(color), ODGETGREEN(color), ODGETBLUE(color) );
}

////////////////////////////////////////////////////////////
///     TviDgnImportParams methods implementation       ////
////////////////////////////////////////////////////////////

TviDgnImportParams::TviDgnImportParams(QObject *parent)
    : TviBaseImportParams (parent)
{
    fillFields(&m_dgnParams);
}

void TviDgnImportParams::applyParams()
{
    m_dgnParams.setObjectNaming( m_bObjectNaming );
    m_dgnParams.setStoreSourceObjects( m_bStoreSource );
    m_dgnParams.setClearEmptyObjects( m_bClearEmptyObjects );
    m_dgnParams.setDCRect( OdTvDCRect(m_xMin, m_xMax, m_yMin, m_yMax) );
}

void TviDgnImportParams::resetParams()
{
    OdTvDgnImportParams dgnParams;
    fillFields(&dgnParams, true);
}

void TviDgnImportParams::setDCRect(const OdTvDCRect &rect)
{
    m_dgnParams.setDCRect(rect);
    m_xMin = rect.xmin;
    m_xMax = rect.xmax;
    m_yMin = rect.ymin;
    m_yMax = rect.ymax;
}

void TviDgnImportParams::fillFields(OdTvDgnImportParams *pParams, bool isReset)
{
    m_bObjectNaming = pParams->getObjectNaming();
    m_bStoreSource = pParams->getStoreSourceObjects();
    m_bClearEmptyObjects = pParams->getClearEmptyObjects();;
    if(!isReset)
    {
        OdTvDCRect rect = pParams->getDCRect();
        m_xMin = rect.xmin;
        m_xMax = rect.xmax;
        m_yMin = rect.ymin;
        m_yMax = rect.ymax;
    }
}

////////////////////////////////////////////////////////////
///     TviStlImportParams methods implementation       ////
////////////////////////////////////////////////////////////

TviStlImportParams::TviStlImportParams(QObject *parent)
    : TviBaseImportParams (parent)
{
    fillFields(&m_stlParams);
}

void TviStlImportParams::applyParams()
{
    m_stlParams.setFixNormals(m_bFixNormals);
    m_stlParams.setUnifyDuplicatedVertices(m_bUnifyDuplicatedVertices);
    m_stlParams.setCalcNormalsAtVertices(m_bCalcNormalsAtVertices);
    m_stlParams.setDefaultColor( ODRGB(m_baseColor.red(), m_baseColor.green(), m_baseColor.blue()) );
}

void TviStlImportParams::resetParams()
{
    OdTvStlImportParams stlParams;
    fillFields(&stlParams);
}

void TviStlImportParams::fillFields(OdTvStlImportParams *pParams)
{
    m_bFixNormals = pParams->getFixNormals();
    m_bUnifyDuplicatedVertices = pParams->getUnifyDuplicatedVertices();
    m_bCalcNormalsAtVertices = pParams->getCalcNormalsAtVertices();
    OdUInt32 color = pParams->getDefaultColor();
    m_baseColor = QColor( ODGETRED(color), ODGETGREEN(color), ODGETBLUE(color) );
}

////////////////////////////////////////////////////////////
///     TviPrcImportParams methods implementation       ////
////////////////////////////////////////////////////////////

TviPrcImportParams::TviPrcImportParams(QObject *parent)
    : TviBaseImportParams (parent)
{
    fillFields(&m_prcParams);
}

void TviPrcImportParams::applyParams()
{
    m_prcParams.setObjectNaming( m_bObjectNaming );
    m_prcParams.setStoreSourceObjects( m_bStoreSource );
    m_prcParams.setClearEmptyObjects( m_bClearEmptyObjects );
    m_prcParams.setDCRect( OdTvDCRect(m_xMin, m_xMax, m_yMin, m_yMax) );
}

void TviPrcImportParams::resetParams()
{
    OdTvPrcImportParams prcParams;
    fillFields(&prcParams, true);
}

void TviPrcImportParams::setDCRect(const OdTvDCRect &rect)
{
    m_prcParams.setDCRect(rect);
    m_xMin = rect.xmin;
    m_xMax = rect.xmax;
    m_yMin = rect.ymin;
    m_yMax = rect.ymax;
}

void TviPrcImportParams::fillFields(OdTvPrcImportParams *pParams, bool isReset)
{
    m_bObjectNaming = pParams->getObjectNaming();
    m_bStoreSource = pParams->getStoreSourceObjects();
    m_bClearEmptyObjects = pParams->getClearEmptyObjects();
    if(!isReset)
    {
        OdTvDCRect rect = pParams->getDCRect();
        m_xMin = rect.xmin;
        m_xMax = rect.xmax;
        m_yMin = rect.ymin;
        m_yMax = rect.ymax;
    }
}
