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

#import <Foundation/Foundation.h>
#include "TviGlobalParameters.hpp"

#define USERDEF_WCS_ENABLE_KEY @"WCS_Enable_Key"
#define USERDEF_FPS_ENABLE_KEY @"FPS_Enable_Key"
#define USERDEF_ANIMATION_ENABLE_KEY @"Animation_Enable_Key"
#define USERDEF_PARTIAL_OPEN_KEY @"PartialOpen_Key"
#define USERDEF_LIMIT_MANAGER_KEY @"LimitManager_Enable_Key"
#define USERDEF_SCENE_GRAPH_KEY @"SceneGraph_Key"
#define USERDEF_MEMORY_LIMIT_KEY @"MemoryLimit_Enable_Key"
#define USERDEF_FIXED_FRAME_RATE_KEY @"FFR_Key"
#define USERDEF_FPS_VALUE_KEY @"FFR_Value_Key"
#define USERDEF_FXAA_KEY @"FXAA_Value_Key"

TviGlobalParameters::TviGlobalParameters() {
    m_bWcsEnabled = true;
    m_bFpsEnabled = false;
    m_bAnimationEnabled = true;
    m_bPartialOpen = false;
    m_bUseLimitManager = false;
    m_bUseSceneGraph = false;
    m_nMemoryLimit = 1000;
    m_bFixedFrameRate = true;
    m_dFpsValue = 15.;
    m_device = OpenGLES2;
    m_bUseFXAA = false;
    
    readFromDefaults();
}

void TviGlobalParameters::readFromDefaults()
{
    NSUserDefaults* def = [NSUserDefaults standardUserDefaults];
    NSArray* keys = [[def dictionaryRepresentation] allKeys];
    if([keys containsObject:USERDEF_WCS_ENABLE_KEY])
        m_bWcsEnabled = [def boolForKey:USERDEF_WCS_ENABLE_KEY];
    if([keys containsObject:USERDEF_FPS_ENABLE_KEY])
        m_bFpsEnabled = [def boolForKey:USERDEF_FPS_ENABLE_KEY];
    if([keys containsObject:USERDEF_ANIMATION_ENABLE_KEY])
        m_bAnimationEnabled = [def boolForKey:USERDEF_ANIMATION_ENABLE_KEY];
    if([keys containsObject:USERDEF_PARTIAL_OPEN_KEY])
        m_bPartialOpen = [def boolForKey:USERDEF_PARTIAL_OPEN_KEY];
    if([keys containsObject:USERDEF_LIMIT_MANAGER_KEY])
        m_bUseLimitManager = [def boolForKey:USERDEF_LIMIT_MANAGER_KEY];
    if([keys containsObject:USERDEF_SCENE_GRAPH_KEY])
        m_bUseSceneGraph = [def boolForKey:USERDEF_SCENE_GRAPH_KEY];
    if([keys containsObject:USERDEF_MEMORY_LIMIT_KEY])
        m_nMemoryLimit = [def integerForKey:USERDEF_MEMORY_LIMIT_KEY];
    if([keys containsObject:USERDEF_FIXED_FRAME_RATE_KEY])
        m_bFixedFrameRate = [def boolForKey:USERDEF_FIXED_FRAME_RATE_KEY];
    if([keys containsObject:USERDEF_FPS_VALUE_KEY])
        m_dFpsValue = [def doubleForKey:USERDEF_FPS_VALUE_KEY];
    if([keys containsObject:USERDEF_FXAA_KEY])
        m_bUseFXAA = [def boolForKey:USERDEF_FXAA_KEY];
}

void TviGlobalParameters::writeToDefaults()
{
    NSUserDefaults* def = [NSUserDefaults standardUserDefaults];
    [def setBool:m_bWcsEnabled forKey:USERDEF_WCS_ENABLE_KEY];
    [def setBool:m_bFpsEnabled forKey:USERDEF_FPS_ENABLE_KEY];
    [def setBool:m_bAnimationEnabled forKey:USERDEF_ANIMATION_ENABLE_KEY];
    [def setBool:m_bPartialOpen forKey:USERDEF_PARTIAL_OPEN_KEY];
    [def setBool:m_bUseLimitManager forKey:USERDEF_LIMIT_MANAGER_KEY];
    [def setBool:m_bUseSceneGraph forKey:USERDEF_SCENE_GRAPH_KEY];
    [def setInteger:m_nMemoryLimit forKey:USERDEF_MEMORY_LIMIT_KEY];
    [def setBool:m_bFixedFrameRate forKey:USERDEF_FIXED_FRAME_RATE_KEY];
    [def setDouble:m_dFpsValue forKey:USERDEF_FPS_VALUE_KEY];
    [def setBool:m_bUseFXAA forKey:USERDEF_FXAA_KEY];
}

// setters
void TviGlobalParameters::setWcsEnabled(bool bValue) {
    m_bWcsEnabled = bValue;
}


void TviGlobalParameters::setFpsEnabled(bool bValue) {
    m_bFpsEnabled = bValue;
}


void TviGlobalParameters::setAnimationEnabled(bool bValue) {
    m_bAnimationEnabled = bValue;
}


void TviGlobalParameters::setPartialOpen(bool bValue) {
    m_bPartialOpen = bValue;
}


void TviGlobalParameters::setUseLimitManager(bool bValue) {
    m_bUseLimitManager = bValue;
}

void TviGlobalParameters::setUseSceneGraph(bool bValue) {
    m_bUseSceneGraph = bValue;
}

void TviGlobalParameters::setMemoryLimit(unsigned long value) {
    m_nMemoryLimit = value;
}

void TviGlobalParameters::setFixedFrameRate(bool bValue) {
    m_bFixedFrameRate = bValue;
}

void TviGlobalParameters::setFpsValue(double dValue) {
    m_dFpsValue = dValue;
}

void TviGlobalParameters::setDevice(Device device) {
    m_device = device;
}

void TviGlobalParameters::setUseFXAA(bool bValue) {
    m_bUseFXAA = bValue;
}

// getters
bool TviGlobalParameters::getWcsEnabled() const { 
    return m_bWcsEnabled;
}

bool TviGlobalParameters::getFpsEnabled() const { 
    return m_bFpsEnabled;
}

bool TviGlobalParameters::getAnimationEnabled() const { 
    return m_bAnimationEnabled;
}

bool TviGlobalParameters::getPartialOpen() const { 
    return m_bPartialOpen;
}

bool TviGlobalParameters::getUseLimitManager() const { 
    return m_bUseLimitManager;
}

bool TviGlobalParameters::getUseSceneGraph() const {
    return m_bUseSceneGraph;
}

unsigned long TviGlobalParameters::getMemoryLimit() const {
    return  m_nMemoryLimit;
}

bool TviGlobalParameters::getFixedFrameRate() const {
    return m_bFixedFrameRate;
}

double TviGlobalParameters::getFpsValue() const {
    return m_dFpsValue;
}

TviGlobalParameters::Device TviGlobalParameters::getDevice() const {
    return m_device;
}

bool TviGlobalParameters::getUseFXAA() const {
    return m_bUseFXAA;
}
