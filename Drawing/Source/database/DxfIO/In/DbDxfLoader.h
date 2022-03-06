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

// OdDbDxfLoader.h - DXF parser interface

#ifndef DXFLOADER_INCLUDED
#define DXFLOADER_INCLUDED

#include "OdString.h"
#include "BaseDictionaryImpl.h"
#include "../../DbFilerController.h"
#include "DbFiler.h"
#include "../../DbFilerImpl.h"
#include "../../DbVXTable.h"
#include "../../Ds/DsObject.h"

class OdThumbnailImage;

class DxfLoadResolver : public OdRxObject
{
  mutable DxfLoadResolver* m_pNext;

public:
  DxfLoadResolver()
    : m_pNext(0)
    , m_pFiler(0)
  {
  }

  DxfLoadResolver* next() const { return m_pNext; }
  void setNext(DxfLoadResolver* pNext) const { m_pNext = pNext; }

  virtual void resolve() = 0;

  OdDbDxfFiler * m_pFiler;
};

typedef OdSmartPtr<DxfLoadResolver> DxfLoadResolverPtr;


class OdDbDxfLoader : public OdDbFilerController
{
  class DXFClassItem
  {
    OdString      m_key;
    OdRxClassPtr  m_val;
  public:
    DXFClassItem() {}
    DXFClassItem(const OdString& key, const OdRxClass* val)
      : m_key(key)
      , m_val(val)
    {}
    const OdString& getKey() const { return m_key; }
    void setKey(const OdString& key) { m_key = key; }
    const OdRxClass* getVal() const { return const_cast<OdRxClass*>(m_val.get()); }
    void setVal(const OdRxClass* pClass) { m_val = pClass; }
    bool isErased() const { return m_val.isNull(); }
    void erase() { m_val.release(); }
  };
  typedef OdBaseDictionaryImpl<OdString, OdRxClassPtr, OdString::lessnocase, DXFClassItem> DxfName2RxClassMap;

private:
  OdDbObjectId                  m_objectBeingLoading;
  int                           m_nProgress;
  OdUInt64                      m_nMax;
  DxfName2RxClassMap            m_RxClassMap;
  OdSmartPtr<OdDbCommonDxfFilerImpl> m_pFiler;
  DxfLoadResolver*              m_pResolvers;
  // AC27 support
  DxfName2RxClassMap            m_DsClassMap;

public:
  void setStream(OdStreamBuf* pInput) { m_pStream = pInput; }
  OdDbObjectId objectBeingLoading() { return m_objectBeingLoading; }
  virtual void addResolver(DxfLoadResolver* pRes);
  void processResolvers();  
  virtual void setFiler(OdDbDxfFiler* pFiler);
  static void addResolver(DxfLoadResolver* pRes, OdDbDxfFiler* pFiler)
  {
    OdDbFilerController* pLoader = pFiler->controller();
    if (pLoader)
    {
      pLoader->castToDxfLoader()->addResolver(pRes);
    }
    else
    {
      pRes->m_pFiler = pFiler;
      pRes->resolve();
    }
  }

private:
  // Names to be used in postprocessing
  OdString m_CLAYER;
  OdString m_CELTYPE;
  OdString m_CMLSTYLE;
  OdString m_DimBlk;
  OdString m_DimBlk1;
  OdString m_DimBlk2;
  OdString m_DIMSTYLE;
  OdString m_DIMTXTSTYLE;
  OdString m_DimLdrBlk;
//  OdString m_DRAGVS;
  //OdString m_INTERFEREOBJVS;
  //OdString m_INTERFEREVPVS;
  OdString m_PUCSBASE;
  OdString m_PUCSNAME;
  OdString m_PUCSORTHOREF;
  OdString m_TEXTSTYLE;
  OdString m_UCSBASE;
  OdString m_UCSNAME;
  OdString m_UCSORTHOREF;
  OdString m_Dimltype;
  OdString m_Dimltex1;
  OdString m_Dimltex2;

  // Active ViewportTableRecord properties
  OdGePoint2d m_VIEWCTR;
  double      m_VIEWSIZE;
  OdGePoint3d m_VIEWDIR;
  OdInt16     m_SNAPMODE;
  OdGePoint2d m_SNAPUNIT;
  OdGePoint2d m_SNAPBASE;
  double      m_SNAPANG;
  OdInt16     m_SNAPSTYLE;
  OdInt16     m_SNAPISOPAIR;
  OdInt16     m_GRIDMODE;
  OdGePoint2d m_GRIDUNIT;
  OdInt16     m_FASTZOOM;

  void loadHeader();
  void loadClasses();
  void loadTables();
public:
  void loadBlocks();
private:
  void loadEntities();
  void loadObjects();
  void loadThumbnailimage(OdThumbnailImage* pPreview);
  void adjustXrefDependentSTRs(OdDbSymbolTable * pBlockTable, OdDbObjectId idTbl);

  void setHeaderVar(const OdString& varName);
  OdDbHandle getObjectHandle();
  OdDbObjectPtr createObject(const OdString& dxfName);
  void loadDrawing();

  void getFileInfo(OdDb::DwgVersion& ver, OdDbHandle& handseed, OdUInt64& nHeaderPos, OdUInt64& nHeaderLine);
  bool findSectionStart(OdString& secName);
  void loadContents();
  void loadR12Contents();
  void restoreDefaultObjects();
  void resolveHeader();

  OdString getObjectName();

  // AC27 support
  void loadDsData();
  OdDs::ObjectPtr loadDsObject(OdUInt64 offset);
  OdDs::ObjectPtr createDsObject(const OdString& dxfName);
protected:
  OdDbDxfLoader();
public:
  ODRX_DECLARE_MEMBERS(OdDbDxfLoader);

  void pmMeterProgress()
  {
    int nProgress = int(m_pFiler->tell() / m_nMax);
    for(; m_nProgress < nProgress; ++m_nProgress)
    {
      OdDbFilerController::pmMeterProgress();
    }
  }
  ~OdDbDxfLoader();

  virtual OdRxClass* getRxClass(const OdString& key);
  void setRxClass(const OdString& key, OdRxClass* newRx);

  bool supportsPartialLoading() const  { return false;}
  void endDbLoading();
  TOOLKIT_EXPORT OdDbObjectPtr loadObject(OdUInt64 offset);

  virtual void getPreviewImg(OdThumbnailImage* pPreview);

//  virtual void setAuditInfo(OdDbAuditInfo* pAuditInfo) {m_pAuditInfo = pAuditInfo;}
//  virtual OdDbAuditInfo* getAuditInfo(void) { return m_pAuditInfo; }

  virtual OdDbDxfLoader* castToDxfLoader() { return this; }
};

#endif  // DXFLOADER_INCLUDED
