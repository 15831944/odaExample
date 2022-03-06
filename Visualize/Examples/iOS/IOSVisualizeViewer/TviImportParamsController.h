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
#ifndef TVIIMPORTPARAMSCONTROLLER_H
#define TVIIMPORTPARAMSCONTROLLER_H

#include "OdaCommon.h"
#include "TvImport.h"
#include <QObject>
#include <QColor>
#include <QSize>

class TviObjImportParams;
class TviDrwImportParams;
class TviRcsImportParams;
class TviDgnImportParams;
class TviStlImportParams;
class TviPrcImportParams;

class TviImportParamsController : public QObject
{
    Q_OBJECT

    explicit TviImportParamsController(QObject *parent = nullptr);

public:
    static TviImportParamsController * getInstance() {
        if(!m_pInstance)
            m_pInstance = new TviImportParamsController();
        return m_pInstance;
    }

    Q_INVOKABLE QObject *getObjImportParams();
    Q_INVOKABLE QObject *getDrwImportParams();
    Q_INVOKABLE QObject *getRcsImportParams();
    Q_INVOKABLE QObject *getDgnImportParams();
    Q_INVOKABLE QObject *getStlImportParams();
    Q_INVOKABLE QObject *getPrcImportParams();

    void setWindowSize(const QSize& size);

private:
    QSize m_windowSize;
    TviObjImportParams *m_pObjParams;
    TviDrwImportParams *m_pDrwParams;
    TviRcsImportParams *m_pRcsParams;
    TviDgnImportParams *m_pDgnParams;
    TviStlImportParams *m_pStlParams;
    TviPrcImportParams *m_pPrcParams;

    static TviImportParamsController *m_pInstance;
};

class TviBaseImportParams : public QObject
{
    Q_OBJECT
public:
    explicit TviBaseImportParams(QObject *parent);

    Q_INVOKABLE virtual void applyParams() = 0;
    Q_INVOKABLE virtual void resetParams() = 0;

    Q_PROPERTY(QColor baseColor MEMBER m_baseColor NOTIFY baseColorChanged)

signals:
    void baseColorChanged();

protected:
    QColor m_baseColor;
};

class TviObjImportParams : public TviBaseImportParams
{
    Q_OBJECT

public:
    explicit TviObjImportParams(QObject *parent);

    Q_PROPERTY(bool calculateNormals MEMBER m_bCalculateNormals NOTIFY calculateNormalsChanged)
    Q_PROPERTY(bool flipUVCoordSystem MEMBER m_bFlipUVCoord NOTIFY flipUVCoordSystemChanged)

    Q_INVOKABLE virtual void applyParams();
    Q_INVOKABLE virtual void resetParams();

    OdTvObjImportParams getImportParams() { return  m_objParams; }

private:
    void fillFields(OdTvObjImportParams *pParams);

signals:
    void calculateNormalsChanged();
    void flipUVCoordSystemChanged();

private:
    OdTvObjImportParams m_objParams;
    bool m_bCalculateNormals;
    bool m_bFlipUVCoord;
};


class TviDrwImportParams : public TviBaseImportParams
{
    Q_OBJECT

public:
    explicit TviDrwImportParams(QObject * parent);

    Q_PROPERTY( bool objectNaming MEMBER m_bObjectNaming NOTIFY objectNamingChanged )
    Q_PROPERTY( bool storeSource MEMBER m_bStoreSource NOTIFY storeSourceChanged )
    Q_PROPERTY( bool clearEmptyObjects MEMBER m_bClearEmptyObjects NOTIFY clearEmptyObjects )
    Q_PROPERTY( bool enableMultithreading MEMBER m_bEnableMultithreading NOTIFY enableMultithreadingChanged )
    Q_PROPERTY( unsigned short maxThreads MEMBER m_iMaxThreads NOTIFY maxThreadsChanged )
    Q_PROPERTY( bool useAdvancedTess MEMBER m_bUseAdvancedTess NOTIFY useAdvancedTessChanged )
    Q_PROPERTY( double facetRes MEMBER m_dFacetRes NOTIFY facetResChanged )
    Q_PROPERTY( long xMin MEMBER m_xMin NOTIFY xMinChanged )
    Q_PROPERTY( long xMax MEMBER m_xMax NOTIFY xMaxChanged )
    Q_PROPERTY( long yMin MEMBER m_yMin NOTIFY yMinChanged )
    Q_PROPERTY( long yMax MEMBER m_yMax NOTIFY yMaxChanged )
    Q_PROPERTY( bool lowMemoryImport MEMBER m_bLowMemoryImport NOTIFY lowMemoryImportChanged )

    Q_INVOKABLE virtual void applyParams();
    Q_INVOKABLE virtual void resetParams();

    OdTvDwgImportParams getImportParams() { return m_dwgParams; }

    void setDCRect(const OdTvDCRect& rect);

private:
    void fillFields(OdTvDwgImportParams *pParams, bool isReset = false);

signals:
    void objectNamingChanged();
    void storeSourceChanged();
    void clearEmptyObjects();
    void enableMultithreadingChanged();
    void maxThreadsChanged();
    void useAdvancedTessChanged();
    void facetResChanged();
    void xMinChanged();
    void xMaxChanged();
    void yMinChanged();
    void yMaxChanged();
    void lowMemoryImportChanged();

private:
    OdTvDwgImportParams m_dwgParams;
    bool m_bObjectNaming;
    bool m_bStoreSource;
    bool m_bClearEmptyObjects;
    bool m_bEnableMultithreading;
    unsigned short m_iMaxThreads;
    bool m_bUseAdvancedTess;
    double m_dFacetRes;
    long m_xMin;
    long m_xMax;
    long m_yMin;
    long m_yMax;
    bool m_bLowMemoryImport;
};

class TviRcsImportParams : public TviBaseImportParams
{
    Q_OBJECT
public:
    explicit TviRcsImportParams(QObject *parent);

    Q_PROPERTY(bool ignorePointSize MEMBER m_bIgnorePointSize NOTIFY ignorePointSizeChanged)

    Q_INVOKABLE virtual void applyParams();
    Q_INVOKABLE virtual void resetParams();

    OdTvRcsImportParams getImportParams() { return  m_rcsParams; }

signals:
    void ignorePointSizeChanged();

private:
    OdTvRcsImportParams m_rcsParams;
    bool m_bIgnorePointSize;
};

class TviDgnImportParams : public TviBaseImportParams
{
    Q_OBJECT

public:
    explicit TviDgnImportParams(QObject * parent);

    Q_PROPERTY( bool objectNaming MEMBER m_bObjectNaming NOTIFY objectNamingChanged )
    Q_PROPERTY( bool storeSource MEMBER m_bStoreSource NOTIFY storeSourceChanged )
    Q_PROPERTY( bool clearEmptyObjects MEMBER m_bClearEmptyObjects NOTIFY clearEmptyObjects )
    Q_PROPERTY( long xMin MEMBER m_xMin NOTIFY xMinChanged )
    Q_PROPERTY( long xMax MEMBER m_xMax NOTIFY xMaxChanged )
    Q_PROPERTY( long yMin MEMBER m_yMin NOTIFY yMinChanged )
    Q_PROPERTY( long yMax MEMBER m_yMax NOTIFY yMaxChanged )

    Q_INVOKABLE virtual void applyParams();
    Q_INVOKABLE virtual void resetParams();

    OdTvDgnImportParams getImportParams() { return m_dgnParams; }

    void setDCRect(const OdTvDCRect& rect);

private:
    void fillFields(OdTvDgnImportParams *pParams, bool isReset = false);

signals:
    void objectNamingChanged();
    void storeSourceChanged();
    void clearEmptyObjects();
    void xMinChanged();
    void xMaxChanged();
    void yMinChanged();
    void yMaxChanged();

private:
    OdTvDgnImportParams m_dgnParams;
    bool m_bObjectNaming;
    bool m_bStoreSource;
    bool m_bClearEmptyObjects;
    long m_xMin;
    long m_xMax;
    long m_yMin;
    long m_yMax;
};


class TviStlImportParams : public TviBaseImportParams
{
    Q_OBJECT
public:
    explicit TviStlImportParams(QObject *parent);

    Q_PROPERTY(bool fixNormals MEMBER m_bFixNormals NOTIFY fixNormalsChanged)
    Q_PROPERTY(bool unifyDuplicatedVertices MEMBER m_bUnifyDuplicatedVertices NOTIFY unifyDuplicatedVerticesChanged)
    Q_PROPERTY(bool calcNormalsAtVertices MEMBER m_bCalcNormalsAtVertices NOTIFY calcNormalsAtVerticesChanged)

    Q_INVOKABLE virtual void applyParams();
    Q_INVOKABLE virtual void resetParams();

    OdTvStlImportParams getImportParams() { return  m_stlParams; }

signals:
    void fixNormalsChanged();
    void unifyDuplicatedVerticesChanged();
    void calcNormalsAtVerticesChanged();

private:
    void fillFields(OdTvStlImportParams *pParams);

private:
    OdTvStlImportParams m_stlParams;
    bool m_bFixNormals;
    bool m_bUnifyDuplicatedVertices;
    bool m_bCalcNormalsAtVertices;
};

class TviPrcImportParams : public TviBaseImportParams
{
    Q_OBJECT

public:
    explicit TviPrcImportParams(QObject * parent);

    Q_PROPERTY( bool objectNaming MEMBER m_bObjectNaming NOTIFY objectNamingChanged )
    Q_PROPERTY( bool storeSource MEMBER m_bStoreSource NOTIFY storeSourceChanged )
    Q_PROPERTY( bool clearEmptyObjects MEMBER m_bClearEmptyObjects NOTIFY clearEmptyObjects )
    Q_PROPERTY( long xMin MEMBER m_xMin NOTIFY xMinChanged )
    Q_PROPERTY( long xMax MEMBER m_xMax NOTIFY xMaxChanged )
    Q_PROPERTY( long yMin MEMBER m_yMin NOTIFY yMinChanged )
    Q_PROPERTY( long yMax MEMBER m_yMax NOTIFY yMaxChanged )

    Q_INVOKABLE virtual void applyParams();
    Q_INVOKABLE virtual void resetParams();

    OdTvPrcImportParams getImportParams() { return m_prcParams; }

    void setDCRect(const OdTvDCRect& rect);

private:
    void fillFields(OdTvPrcImportParams *pParams, bool isReset = false);

signals:
    void objectNamingChanged();
    void storeSourceChanged();
    void clearEmptyObjects();
    void xMinChanged();
    void xMaxChanged();
    void yMinChanged();
    void yMaxChanged();

private:
    OdTvPrcImportParams m_prcParams;
    bool m_bObjectNaming;
    bool m_bStoreSource;
    bool m_bClearEmptyObjects;
    long m_xMin;
    long m_xMax;
    long m_yMin;
    long m_yMax;
};

#endif // TVIIMPORTPARAMSCONTROLLER_H
