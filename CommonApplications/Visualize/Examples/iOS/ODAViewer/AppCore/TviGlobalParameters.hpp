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

#ifndef TviGlobalParameters_hpp
#define TviGlobalParameters_hpp

#include <stdio.h>

class TviGlobalParameters
{
public:
    enum Device
    {
      OpenGLES2,
      Metal
    };
    
    TviGlobalParameters();
    
    void setWcsEnabled(bool bValue);
    void setFpsEnabled(bool bValue);
    void setAnimationEnabled(bool bValue);
    void setPartialOpen(bool bValue);
    void setUseLimitManager(bool bValue);
    void setUseSceneGraph(bool bValue);
    void setMemoryLimit(unsigned long value);
    void setFixedFrameRate(bool bValue);
    void setFpsValue(double dValue);
    void setDevice(Device device);
    void setUseFXAA(bool bValue);
    
    bool getWcsEnabled() const;
    bool getFpsEnabled() const;
    bool getAnimationEnabled() const;
    bool getPartialOpen() const;
    bool getUseLimitManager() const;
    bool getUseSceneGraph() const;
    unsigned long getMemoryLimit() const;
    bool getFixedFrameRate() const;
    double getFpsValue() const;
    Device getDevice() const;
    bool getUseFXAA() const;
    
    void readFromDefaults();
    void writeToDefaults();
    
private:
    bool m_bWcsEnabled;
    bool m_bFpsEnabled;
    bool m_bAnimationEnabled;
    bool m_bPartialOpen;
    bool m_bUseLimitManager;
    bool m_bUseSceneGraph;
    bool m_bUseFXAA;
    unsigned long m_nMemoryLimit;
    bool m_bFixedFrameRate;
    double m_dFpsValue;
    Device m_device;
};

#endif /* TviGlobalParameters_hpp */
