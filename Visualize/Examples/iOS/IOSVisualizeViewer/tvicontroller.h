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
#ifndef TVICONTROLLER_H
#define TVICONTROLLER_H

#include "tviview.h"
#include "TviAppearanceParams.h"

#include <QQuickItem>
#include <QRunnable>

class TviController : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString filePath READ getFilePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(bool isFileLoaded READ getIsFileLoaded)

public:
    TviController();
    ~TviController();

    Q_INVOKABLE void showMessageEvent(const QString& titleStr, const QString& msgStr) {
     emit showMessage(titleStr, msgStr);
    }

    Q_INVOKABLE void resetSgEvent() {
     emit resetSg();
    }

    Q_INVOKABLE bool closeFileEvent();

    Q_INVOKABLE void onAcceptImportDlg(QObject *qParams);
    Q_INVOKABLE void onRejectImportDlg();

    Q_INVOKABLE QObject* getAppearanceParams() { return  m_pAppearanceParams; }

    Q_INVOKABLE void applyAppearanceParams();

    Q_INVOKABLE unsigned long getStatistic(int type);

    Q_INVOKABLE void saveFile(bool bPartialIndexes, const QString& fileName);

    Q_INVOKABLE void saveMarkup(const QString& name);
    Q_INVOKABLE void loadMarkup(const QString& name);
    Q_INVOKABLE void deleteMarkup(const QString& name);

    Q_INVOKABLE void onDraggerDonePressed();
    Q_INVOKABLE void onTextChanged(const QString& text);
    Q_INVOKABLE void onReturnPressed();
    Q_INVOKABLE void onBackspacePressed();

    QString getFilePath() const { return m_filePath; }
    void setFilePath( const QString& filePath );
    bool getIsFileLoaded() const { return  m_bIsFileLoaded; }

    void cleanRenderData();

signals:
    void filePathChanged();
    void fileLoadDoneSg(bool isPerspective, const QString& renderMode);
    void showMessage(const QString& titleStr, const QString& msgStr);
    void resetSg();
    void showImportParamsDialog(const QString& ext);
    void showTotalTime(long totalTime);
    void showSaveMarkupDlg();
    void showLoadMarkupDlg(const QStringList& list);
    void displayVirtualKeyboard();
    void hideVirtualKeyboard();
    void draggerFinished();

public slots:
    void sync();
    void cleanup();
    void loadDoneSl(bool isPerspective, const QString& renderMode);
    void showMessageSl(const QString& titleStr, const QString& msgStr);
    void resetSl();
    void onPanelButtonPressed(const QString& buttonName);
    void unblockRenderSl();
    void onZoomSl(double delta, int x, int y);
    void onTouchStartSl(int x, int y);
    void onTouchUpdatedSl(int x, int y);
    void onTouchReleasedSl(int x, int y);

private slots:
    void handleWindowChanged(QQuickWindow *win);

private:
    QString m_filePath;
    TviView *m_pTviView;
    bool m_bIsFileLoaded;
    TviAppearanceParams *m_pAppearanceParams;
    OdTvGeometryStatistic *m_pStat;
    OdTvVector m_backDelta;
};

class TviCleanRenderDataJob : public QRunnable
{
public:
    TviCleanRenderDataJob(TviController* pController);

    virtual void run();

private:
    TviController* m_pController;
};

#endif // TVICONTROLLER_H
