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
#ifndef TVIVIEW_H
#define TVIVIEW_H

// QT
#include <QObject>
#include <QQuickWindow>
#include <QMutex>
#include <QWaitCondition>
#include <QTimer>
// Oda SDK
#include "OdaCommon.h"
// Visualize SDK
#include "TvDatabase.h"
#include "TvImport.h"
#include "Tools/TvExtendedView.h"
#include "Tools/TvMarkupDraggers.h"

#include "Draggers/tvipandragger.h"
#include "Draggers/tviorbitdragger.h"
#include "tvifileopenthreadtask.h"
#include "TviAppearanceParams.h"
#include "TviLimitManager.h"

class QString2WString
{
public:
    QString2WString( const QString& str )
    {
        if( str.isEmpty() )
        {
            m_pChars = NULL;
            return;
        }
        m_pChars = new wchar_t[ str.length() + 1 ];
        str.toWCharArray( m_pChars );
        m_pChars[ str.length() ] = 0;
        m_wstring = std::wstring( m_pChars );
    }

    ~QString2WString()
    {
        m_wstring.clear();
        if( m_pChars )
        {
            delete[] m_pChars;
            m_pChars = NULL;
        }
    }

    std::wstring& wstr() { return m_wstring; }

    void reassign( const QString& str )
    {
        m_wstring.clear();
        if( m_pChars ) delete[] m_pChars;
        if( str.isEmpty() )
        {
            m_pChars = NULL;
            return;
        }
        m_pChars = new wchar_t[ str.length() + 1 ];
        str.toWCharArray( m_pChars );
        m_pChars[ str.length() ] = 0;
        m_wstring = std::wstring( m_pChars );
    }
protected:
    QString2WString();
    QString2WString( const QString2WString& );
    QString2WString& operator=( const QString2WString& );

    wchar_t* m_pChars;
    std::wstring m_wstring;
};


class TviView : public QObject
{   
    Q_OBJECT
public:
    
    enum LoadMode
    {
        kRead   = 0,
        kImport = 1,
        kCustom = 2
    };

    enum NavigationAction
    {
        kPan         = 0,
        kOrbit       = 1,
        kZoomWindow  = 2,
        kZoomExtents = 3
    };

    enum RegenAction
    {
        kAll      = 0,
        kVisible  = 1,
        kView     = 2
    };

    enum ProjectionType
    {
        kIsometric   = 0,
        kPerspective = 1
    };
    
    enum AfterPainAction
    {
        kNothing = 0x00,
        kSetFps  = 0x01,
        kSetWcs  = 0x02
    };

    enum MarkupAction
    {
        kRectangle  = 0,
        kCircle     = 1,
        kHandle     = 2,
        kCloud      = 3,
        kText       = 4,
        kSave       = 5,
        kLoad       = 6
    };

    struct ImportParameters
    {
        OdTvBaseImportParams   vsfReadParam;
        OdTvRcsImportParams    rcsImportParam;
        OdTvStlImportParams    stlImportParam;
        OdTvObjImportParams    objImportParam;
        OdTvDwgImportParams    dwgImportParam;
        OdTvDgnImportParams    dgnImportParam;
        OdTvPrcImportParams    prcImportParam;
    };

    enum FileExtension
    {
        kNone   = 0,
        kVsf    = 1,
        kRcs    = 2,
        kDrw    = 3,
        kDgn    = 4,
        kStl    = 5,
        kObj    = 6,
        kPrc    = 7
    };

    TviView(TviAppearanceParams *pAppearanceParams);
    ~TviView();

    void setViewportSize(const QSize &size) { m_viewportSize = size; }
    void setWindow(QQuickWindow *window) { m_window = window; }

    void setFilePath(const QString& filePath);

    void createTvDevice();

    OdTvDatabaseId getTvDatabaseId() const { return  m_TvDatabaseId; }

    OdTvGsDeviceId getDeviceId() const { return  m_TvDeviceId; }

    // get active OdTvGsViewId
    OdTvGsViewId getActiveTvViewId() const;
    OdTvGsViewPtr getActiveTvViewPtr();
    // get visualize extended view
    OdTvExtendedView* getActiveTvExtendedView();

    OdTvDragger* getActiveDragger() { return m_pActiveDragger.get(); }

    void setAnimation(OdTvAnimation *pAnimation) { m_pAnimation = pAnimation; }

    void actionsAfterDragger(eDraggerResult res);

    void runNavigationAction(NavigationAction navAct);

    void set3DView(OdTvExtendedView::e3DViewType type);

    void runRegenAction(RegenAction regenAct);

    void runRenderMode(OdTvGsView::RenderMode newMode);

    void runMarkupAction(MarkupAction act);

    void setProjection(ProjectionType projType);

    void performZoomEvent(const QPointF& pnt, double delta);

    void setRenderBlocked(bool isBlocked);
    
    bool isPainting() const { return m_bIsPainting; }
    
    void adjustPointY(QPointF& pnt);

    ImportParameters& getImportParameters() { return m_importParams; }

    FileExtension getFileExtension() const { return  m_fileExt; }

    void openFile();

    void applyAppearanceParams();

    OdTvGeometryStatistic* getStatistic();

    void saveFile(bool bPartialIndexes, const QString &fileName);

    void saveMarkup(const QString& name);
    void loadMarkup(const QString& name);
    void deleteMarkup(const QString& name);

signals:
    void loadDoneSg(bool isPerspective, const QString& renderMode);
    void showMessageSg(const QString& titleStr, const QString& msgStr);
    void resetSg();
    void showImportParamsDialog(const QString& ext);
    void showTotalTime(long totalTime);
    void showSaveMarkupDlg();
    void showLoadMarkupDlg(const QStringList& list);

public slots:
    void paint();
    void onErrorHandle(const QString& msg);
    void onUnexpectedError();
    void onDatabaseLoadDone();

private slots:
    void autoUpdateTimeout();

private:
    void setImportParams(const OdString& strExt);
    OdTvModelId loadTvDatabase(OdTvBaseImportParams* pImportParam, LoadMode loadMode);
    void setupGs();
    bool initialize();
    void finishDragger();
    void startDragger(OdTvDraggerPtr pNewDragger, bool bUseCurrentAsPrevious = false);
    void screenDolly(int x, int y);
    void actionAfterPaint();
    // markups methods
    void disableMarkups();
    void markupSaveView();
    void markupLoadView();

private:
    QSize m_viewportSize;

    OdTvGsDeviceId m_TvDeviceId;
    OdTvModelId m_TvMainModel;
    OdTvModelId m_TvMarkupsModelId;
    OdTvRegAppId m_appTvId;
    OdTvDatabaseId m_TvDatabaseId;

    QQuickWindow *m_window;
    bool m_bInitialized;

    // Draggers model id
    OdTvModelId     m_TvDraggersModelId;

    // Current dragger pointer
    OdTvDraggerPtr  m_pActiveDragger;

    //index of the wcs viewport (should be update on resize)
    std::map < OdTvGsViewId, OdTvExtendedView* > m_tvExtendedViewsMap;
    //pointer to the animation
    OdTvAnimation* m_pAnimation;

    // threadcontroller and tasks
    TviThreadController *m_pThreadController;
    TviFileOpenThreadTask *m_pFileOpenTask;

    // import parameters
    ImportParameters m_importParams;
    TviDatabaseInfo m_databaseInfo;

    bool m_bIsBlocked;
    bool m_bIsPainting;
    
    int m_iFooterHeight;
    int m_iHeaderHeight;

    FileExtension m_fileExt;
    QString m_filePath;
    TviAppearanceParams *m_pAppearanceParams;
    
    unsigned int m_afterPaintActions;
    OdTvGeometryStatistic m_modelStat;
    QTimer m_autoUpdateTimer;

    // memory limit manager
    TviLimitManager m_limitator;
    // markups list model
    QStringList m_savedMarkups;
};

#endif // TVIVIEW_H
