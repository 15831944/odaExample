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
#ifndef TVIAPPEARANCEPARAMS_H
#define TVIAPPEARANCEPARAMS_H

#include <QObject>

class TviAppearanceParams : public QObject
{
    Q_OBJECT
public:
    explicit TviAppearanceParams(QObject *parent = NULL);

    Q_PROPERTY(bool wcsEnabled MEMBER m_bWcsEnabled NOTIFY wcsEnabledChanged)
    Q_PROPERTY(bool fpsEnabled MEMBER m_bFpsEnabled NOTIFY fpsEnabledChanged)
    Q_PROPERTY(bool animationEnabled MEMBER m_bAnimationEnabled NOTIFY animationEnabledChanged)
    Q_PROPERTY(bool partialOpen MEMBER m_bPartialOpen NOTIFY partialOpenChanged)
    Q_PROPERTY(bool useLimitManager MEMBER m_bUseLimitManager NOTIFY useLimitManagerChanged)
    Q_PROPERTY(bool useSceneGraph MEMBER m_bUseSceneGraph NOTIFY useSceneGraphChanged)

    bool getWcsEnabled() const { return m_bWcsEnabled; }
    bool getFpsEnabled() const { return m_bFpsEnabled; }
    bool getAnimationEnabled() const { return  m_bAnimationEnabled; }
    bool getPartialOpen() const { return m_bPartialOpen; }
    bool getUseLimitManager() const { return m_bUseLimitManager; }
    bool getUseSceneGraph() const { return m_bUseSceneGraph; }

signals:
    void wcsEnabledChanged();
    void fpsEnabledChanged();
    void animationEnabledChanged();
    void partialOpenChanged();
    void useLimitManagerChanged();
    void useSceneGraphChanged();

private:
    bool m_bWcsEnabled;
    bool m_bFpsEnabled;
    bool m_bAnimationEnabled;
    bool m_bPartialOpen;
    bool m_bUseLimitManager;
    bool m_bUseSceneGraph;
};

#endif // TVIAPPEARANCEPARAMS_H
