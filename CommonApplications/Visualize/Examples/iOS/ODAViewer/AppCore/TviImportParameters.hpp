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

#ifndef TviImportParameters_hpp
#define TviImportParameters_hpp

#import <Foundation/Foundation.h>
#include <stdio.h>
#include "OdaCommon.h"
#include "TvImport.h"

class TviBaseImport
{
public:
    TviBaseImport()
    {
        m_userDef = [NSUserDefaults standardUserDefaults];
    }
    
    virtual void readFromDefaults() = 0;
    virtual void writeToDefaults() = 0;
    
protected:
    NSUserDefaults* m_userDef;
};

class TviObjImportParams : public TviBaseImport, public OdTvObjImportParams
{
public:
    TviObjImportParams() { readFromDefaults(); }
    
    virtual void readFromDefaults();
    virtual void writeToDefaults();
};

class TviDrwImportParams : public TviBaseImport, public OdTvDwgImportParams
{
public:
    TviDrwImportParams() { readFromDefaults(); }
    
    virtual void readFromDefaults();
    virtual void writeToDefaults();
};

class TviRcsImportParams : public TviBaseImport, public OdTvRcsImportParams
{
public:
    TviRcsImportParams() { }
    
    virtual void readFromDefaults(){}
    virtual void writeToDefaults(){}
};

class TviDgnImportParams : public TviBaseImport, public OdTvDgnImportParams
{
public:
    TviDgnImportParams() { readFromDefaults(); }
    
    virtual void readFromDefaults();
    virtual void writeToDefaults();
};

class TviStlImportParams : public TviBaseImport, public OdTvStlImportParams
{
public:
    TviStlImportParams() { readFromDefaults(); }
    
    virtual void readFromDefaults();
    virtual void writeToDefaults();
};

class TviPrcImportParams : public TviBaseImport, public OdTvPrcImportParams
{
public:
    TviPrcImportParams() { readFromDefaults(); }
    
    virtual void readFromDefaults();
    virtual void writeToDefaults();
};

class TviIfcImportParams : public TviBaseImport, public OdTvIfcImportParams
{
public:
    TviIfcImportParams() { readFromDefaults(); }
    
    virtual void readFromDefaults() {}
    virtual void writeToDefaults() {}
};

class TviImportParamsController
{
public:
    TviImportParamsController();
    void setRect(int w, int h);
    
    TviObjImportParams* getObjImportParams() { return &m_objParams; }
    TviDrwImportParams* getDwgImportParams() { return &m_dwgParams; }
    TviRcsImportParams* getRcsImportParams() { return &m_rcsParams; }
    TviDgnImportParams* getDgnImportParams() { return &m_dgnParams; }
    TviStlImportParams* getStlImportParams() { return &m_stlParams; }
    TviPrcImportParams* getPrcImportParams() { return &m_prcParams; }
    TviIfcImportParams* getIfcImportParams() { return &m_ifcParams; }
    
private:
    TviObjImportParams m_objParams;
    TviDrwImportParams m_dwgParams;
    TviRcsImportParams m_rcsParams;
    TviDgnImportParams m_dgnParams;
    TviStlImportParams m_stlParams;
    TviPrcImportParams m_prcParams;
    TviIfcImportParams m_ifcParams;
};

#endif /* TviImportParameters_hpp */
