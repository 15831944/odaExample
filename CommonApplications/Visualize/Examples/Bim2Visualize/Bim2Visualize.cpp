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

#include "OdaCommon.h"
#include "RxDynamicModule.h"
#include "RxVariantValue.h"
#include "RxInit.h"

#include "Bim2Visualize.h"

#include "TvFilerTimer.h"
#include "TvModuleNames.h"
#include "TvDatabaseCleaner.h"
#include "TvDatabaseUtils.h"

#include "BimCommon.h"
#include "RxObjectImpl.h"
#include "ExBimHostAppServices.h"
#include "Database/BmDatabase.h"
#include "Database/GiContextForBmDatabase.h"
#include "Database/Managers/BmDBDrawingInfo.h"
#include "Database/Entities/BmDBDrawing.h"
#include "BmGsManager.h"
#include "Entities/BmDBDrawing.h"
#include "Entities/BmViewport.h"

#include "ColorMapping.h"

#include "../Extensions/ExVisualizeDevice/GsVisualizeVectorizer.h"
#include "Bim2VisualizeThreadContext.h"

#include "Entities/BmDBView3d.h"
#include "BmTransaction.h"
#include "Base/BmParameterSet.h"

/************************************************************************/
/* Replaced forbidden symbols in the name                               */
/************************************************************************/

OdString correctName(const OdString& str)
{
  OdString res = str;

  res.replace('<', '_');
  res.replace('>', '_');
  res.replace('\\', '_');
  res.replace('/', '_');
  res.replace(':', '_');
  res.replace(';', '_');
  res.replace('?', '_');
  res.replace('*', '_');
  res.replace('|', '_');
  res.replace('=', '_');
  res.replace(L"'", L"_");

  return res;
}

/************************************************************************/
/* Convert Bim view format name from enum to string                     */
/************************************************************************/

OdString getNodeNameByViewType(OdBm::ViewNameFormat::Enum viewNameFormat)
{
  OdString sName = L"";

  switch (viewNameFormat)
  {
  case OdBm::ViewType::Plan: { sName = L"?? Plans"; break; }
  case OdBm::ViewNameFormat::FloorPlan: { sName = L"Floor Plans"; break; }
  case OdBm::ViewNameFormat::CeilingPlan: { sName = L"Ceiling Plans"; break; }
  case OdBm::ViewType::Section: { sName = L"Sections"; break; }
  case OdBm::ViewNameFormat::Elevation: { sName = L"Elevations"; break; }
  case OdBm::ViewNameFormat::AreaPlan: { sName = L"Area Plans"; break; }
  case OdBm::ViewType::_3d: { sName = L"3D Views"; break; }
  case OdBm::ViewType::Project: { sName = L"Project Views"; break; }
  case OdBm::ViewType::AnonDrafting: { sName = L"Anon Drafting Views"; break; }
  case OdBm::ViewType::Cost: { sName = L"Cost View"; break; }
  case OdBm::ViewType::Legend: { sName = L"Legend Views"; break; }
  case OdBm::ViewType::Drafting: { sName = L"Sheets"; break; }
  case OdBm::ViewType::SystemNavigator: { sName = L"Rbs System Navigator Views"; break; }
  case OdBm::ViewType::TableView: { sName = L"Table Views"; break; }
  case OdBm::ViewType::Schedule: { sName = L"Schedule Views"; break; }
  case OdBm::ViewType::Report: { sName = L"Abs Pressure Loss Report Views"; break; }
  case OdBm::ViewType::_3dEnergyAnalysis: { sName = L"Energy Analysis 3D Views"; break; }
  case OdBm::ViewType::_3dEnergyAnalysisPreview: { sName = L"Energy Analysis Preview 3D Views"; break; }
  case OdBm::ViewType::EnergyAnalysis: { sName = L"Energy Analysis Views"; break; }
  case OdBm::ViewType::EnergyAnalysisReport: { sName = L"Energy Analysis Report Views"; break; }
  case OdBm::ViewType::GraphSchedColumn: { sName = L"Graph Sched Column Views"; break; }
  case OdBm::ViewType::HVACLoadsReport: { sName = L"HVAC Loads Report Views"; break; }
  case OdBm::ViewType::Rendering: { sName = L"Renderings"; break; }
  case OdBm::ViewType::RbsPanelSchedule: { sName = L"Rbs Panel Schedule Views"; break; }
  default: { sName = L"Unknown Views"; break; }
  }

  return sName;
}

#if defined(ODA_WINDOWS)

#define MAX_PATH_LENGTH 1024
#define SMALL_STRING_SIZE 32
#define LARGE_STRING_SIZE 1024

bool GetRegistryString(  HKEY key, const wchar_t *subkey, const wchar_t *name, wchar_t *value, int size)
{
  bool rv = false;
  HKEY hKey;
  if( RegOpenKeyExW( key, subkey, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
  {
    DWORD dwSize( MAX_PATH_LENGTH);
    unsigned char data[MAX_PATH_LENGTH];
    memset (&data, 0x00, MAX_PATH_LENGTH);
    if( RegQueryValueExW( hKey, name, 0, 0, &data[0], &dwSize) == ERROR_SUCCESS)
    {
      rv = true;
    }
    else
    {
      if ( ERROR_SUCCESS == RegEnumKeyExW(hKey, 0, (LPWSTR)(unsigned short*)&data[0], &dwSize
        , NULL, NULL, NULL, NULL))
      {
        rv = true;
      }
    }
    
    if( size < MAX_PATH_LENGTH)
    {
      swprintf( value, L"%ls\0", (const wchar_t*)data);
    }
    else
    {
      wcsncpy( value, (wchar_t*)data, size - 1);
      value[ size-1] = '\0';
    }
    
    RegCloseKey(hKey);
  }
  return rv;
}

OdString GetRegistryADSKTextureLibraryLocation()
{
  OdString subkey = L"SOFTWARE\\WOW6432Node\\Autodesk\\ADSKTextureLibrary\\1";
  TCHAR searchPath[LARGE_STRING_SIZE];

  // get the version and concatenate onto subkey
  if (GetRegistryString(HKEY_LOCAL_MACHINE, (LPCTSTR)subkey, L"LibraryPaths", searchPath, LARGE_STRING_SIZE) != 0)
    return OdString(searchPath);
  else {
    subkey = L"SOFTWARE\\WOW6432Node\\Autodesk\\ADSKTextureLibraryNew\\1";
    if (GetRegistryString(HKEY_LOCAL_MACHINE, (LPCTSTR)subkey, L"LibraryPaths", searchPath, LARGE_STRING_SIZE) != 0) {
      subkey += L"\\";
      subkey += searchPath;//it should be year
      if (GetRegistryString(HKEY_LOCAL_MACHINE, (LPCTSTR)subkey, L"LibraryPaths", searchPath, LARGE_STRING_SIZE) != 0)
        return OdString(searchPath);
    }
  }
  return L"";
}

#ifndef ODA_UNIXOS
#define pathChar '\\'
#define oldPathChar '/'
#else
#define pathChar '/'
#define oldPathChar '\\'
#endif

OdString OdTvService::findFile( const OdString& file, OdDbBaseDatabase* pBaseDb, FindFileHint hint )
{
  OdString ffile = OdBmLoaderHostAppServices::findFile(file, pBaseDb, hint);
  if (!ffile.isEmpty())
    return ffile;
  OdString sPath;
  if (hint == kTextureMapFile)
    sPath = GetRegistryADSKTextureLibraryLocation();
  if (!sPath.isEmpty()) {
    ffile = sPath + OdChar(pathChar) + file;
    ffile = OdBmLoaderHostAppServices::findFile(ffile, pBaseDb, hint);
    if (!ffile.isEmpty())
      return ffile;
    // some times there is no 1/Mats in path, check it.
    ffile = sPath + OD_T("1") + OdChar(pathChar) + OD_T("Mats") + OdChar(pathChar) + file;
    ffile = OdBmLoaderHostAppServices::findFile(ffile, pBaseDb, hint);
    if (!ffile.isEmpty())
      return ffile;
  }

  OdInt32 nSlashPos = file.reverseFind(pathChar) + 1;
  sPath = file.right(file.getLength() - nSlashPos);
  sPath = OdBmLoaderHostAppServices::findFile(sPath, pBaseDb, hint);
  return sPath;
}

#endif

//*************************************************************************************//
// Implementation of the methods of the inheritants of 'OdTvVisualizeBimFilerDbSource'
//*************************************************************************************//
class OdTvVisualizeBimFilerSourceFromDb : public OdTvVisualizeBimFilerDbSource
{
  OdDbBaseDatabase *mDatabase;

public:
  OdTvVisualizeBimFilerSourceFromDb(OdDbBaseDatabase* pDatabase) : mDatabase(pDatabase) { initialize(); };
  virtual OdBmDatabasePtr   getDb() { return mDatabase; };
  virtual bool              odWasInitialized() const { return false; }
  virtual OdString          getFilename()
  {
    OdBmDatabasePtr pDb = mDatabase;
    if (!pDb.isNull())
    {
      OdString fileName = pDb->getFilename();
      if (!fileName.isEmpty())
        return fileName;
    }

    return OD_T("NoNameBimDatabase");
  }

protected:
  void initialize()
  {
    OdBmDatabasePtr pDb = mDatabase;
    if (!pDb.isNull())
    {
      m_filePath = pDb->getFilename();
    }
  };
};


class OdTvVisualizeBimFilerSourceFromStream : public OdTvVisualizeBimFilerDbSource
{
  OdStreamBufPtr mStreamBuf;

protected:
  double         m_initTime;

public:
  OdTvVisualizeBimFilerSourceFromStream(OdStreamBufPtr pBuffer, OdTvFilerTimeProfiling* pProfileRes) { initialize(pBuffer, pProfileRes); };
  virtual OdBmDatabasePtr getDb() { return m_svcs.readFile(mStreamBuf); };
  virtual double          getInitTime() const { return m_initTime; }
  virtual OdString        getFilename()
  {
    OdString strFileName = mStreamBuf->fileName();
    if (strFileName.isEmpty())
      return OD_T("NoNameBimDatabase");

    //generate name for the stream file
    return OdTvDatabaseUtils::getFileNameFromPath(strFileName);
  };

protected:
  OdTvVisualizeBimFilerSourceFromStream() {};
  void initialize(OdStreamBufPtr pBuffer, OdTvFilerTimeProfiling* pProfileRes)
  {
    mStreamBuf = pBuffer;

    OdTvFilerTimer timing(needTimer(pProfileRes));
    timing.startTotal();

    //load module
    ::odrxDynamicLinker()->loadApp(OdBmLoaderModuleName, false);

    timing.endTotal();
    m_initTime = timing.getTotalTime();

    m_filePath = mStreamBuf->fileName();
  };
};


class OdTvVisualizeBimFilerSourceFromFile : public OdTvVisualizeBimFilerDbSource
{
protected:
  double         m_initTime;

public:
  OdTvVisualizeBimFilerSourceFromFile(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes) { initialize(filePath, pProfileRes); };
  virtual OdBmDatabasePtr getDb() { return m_svcs.readFile(m_filePath); };
  virtual double          getInitTime() const { return m_initTime; }
  virtual OdString        getFilename()
  {
    //generate name for the stream file
    return OdTvDatabaseUtils::getFileNameFromPath(m_filePath);
  };

protected:
  OdTvVisualizeBimFilerSourceFromFile() {};
  void initialize(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes)
  {
    m_filePath = filePath;

    OdTvFilerTimer timing(needTimer(pProfileRes));
    timing.startTotal();

    //load module
    ::odrxDynamicLinker()->loadApp(OdBmLoaderModuleName, false);

    timing.endTotal();
    m_initTime = timing.getTotalTime();
  };
};


//***************************************************************************//
// 'OdTvVisualizeBimFilerProperties' methods implementation
//***************************************************************************//
using namespace BIM2Visualize;

OdTvVisualizeBimFilerProperties::OdTvVisualizeBimFilerProperties() : m_background(ODRGB(255, 255, 255)), m_flags(4), m_pCallback(NULL), m_pWarningCallback(NULL), m_bUseMTforViewsImport(false), m_nViewsImportThreads(4), m_bCreate3DView(false), m_useAlternativeCDATree(false)
{
  m_importRect.xmax = 0;
  m_importRect.xmin = 0;
  m_importRect.ymax = 0;
  m_importRect.ymin = 0;
}

OdRxDictionaryPtr OdTvVisualizeBimFilerProperties::createObject()
{
  return OdRxObjectImpl<OdTvVisualizeBimFilerProperties, OdRxDictionary>::createObject();
}

OdTvVisualizeBimFilerProperties::~OdTvVisualizeBimFilerProperties()
{
}

namespace BIM2Visualize {
  ODRX_DECLARE_PROPERTY(BackgroundColor)
  ODRX_DECLARE_PROPERTY(DCRect)
  ODRX_DECLARE_PROPERTY(ObjectNaming)
  ODRX_DECLARE_PROPERTY(StoreSourceObjects)
  ODRX_DECLARE_PROPERTY(ThinLines)
  ODRX_DECLARE_PROPERTY(FeedbackForChooseCallback)
  ODRX_DECLARE_PROPERTY(FeedbackForWarningCallback)
  ODRX_DECLARE_PROPERTY(ClearEmptyObjects)
  ODRX_DECLARE_PROPERTY(AppendTransform)
  ODRX_DECLARE_PROPERTY(NeedCDATree)
  ODRX_DECLARE_PROPERTY(NeedCollectPropertiesInCDA)
  ODRX_DECLARE_PROPERTY(IgnoreEdgesColors)
  ODRX_DECLARE_PROPERTY(UseSilhouettes)
  ODRX_DECLARE_PROPERTY(UseMTforViewsImport)
  ODRX_DECLARE_PROPERTY(ViewsImportThreads)
  ODRX_DECLARE_PROPERTY(Create3DView)
  ODRX_DECLARE_PROPERTY(UseAlternativeCDATree)

  ODRX_BEGIN_DYNAMIC_PROPERTY_MAP(OdTvVisualizeBimFilerProperties);
  ODRX_GENERATE_PROPERTY(BackgroundColor)
  ODRX_GENERATE_PROPERTY(DCRect)
  ODRX_GENERATE_PROPERTY(ObjectNaming)
  ODRX_GENERATE_PROPERTY(StoreSourceObjects)
  ODRX_GENERATE_PROPERTY(ThinLines)
  ODRX_GENERATE_PROPERTY(FeedbackForChooseCallback)
  ODRX_GENERATE_PROPERTY(FeedbackForWarningCallback)
  ODRX_GENERATE_PROPERTY(ClearEmptyObjects)
  ODRX_GENERATE_PROPERTY(AppendTransform)
  ODRX_GENERATE_PROPERTY(NeedCDATree)
  ODRX_GENERATE_PROPERTY(NeedCollectPropertiesInCDA)
  ODRX_GENERATE_PROPERTY(IgnoreEdgesColors)
  ODRX_GENERATE_PROPERTY(UseSilhouettes)
  ODRX_GENERATE_PROPERTY(UseMTforViewsImport)
  ODRX_GENERATE_PROPERTY(ViewsImportThreads)
  ODRX_GENERATE_PROPERTY(Create3DView)
  ODRX_GENERATE_PROPERTY(UseAlternativeCDATree)
  ODRX_END_DYNAMIC_PROPERTY_MAP(OdTvVisualizeBimFilerProperties);

  ODRX_DEFINE_PROPERTY_METHODS(BackgroundColor, OdTvVisualizeBimFilerProperties, getBackgroundColor, setBackgroundColor, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(DCRect, OdTvVisualizeBimFilerProperties, getDCRect, setDCRect, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(ObjectNaming, OdTvVisualizeBimFilerProperties, getObjectNaming, setObjectNaming, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(StoreSourceObjects, OdTvVisualizeBimFilerProperties, getStoreSourceObjects, setStoreSourceObjects, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(ThinLines, OdTvVisualizeBimFilerProperties, getThinLines, setThinLines, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(FeedbackForChooseCallback, OdTvVisualizeBimFilerProperties, getFeedbackForChooseCallback, setFeedbackForChooseCallback, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(FeedbackForWarningCallback, OdTvVisualizeBimFilerProperties, getFeedbackForWarningCallback, setFeedbackForWarningCallback, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(ClearEmptyObjects, OdTvVisualizeBimFilerProperties, getClearEmptyObjects, setClearEmptyObjects, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(AppendTransform, OdTvVisualizeBimFilerProperties, getAppendTransform, setAppendTransform, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(NeedCDATree, OdTvVisualizeBimFilerProperties, getNeedCDATree, setNeedCDATree, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(NeedCollectPropertiesInCDA, OdTvVisualizeBimFilerProperties, getNeedCollectPropertiesInCDA, setNeedCollectPropertiesInCDA, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(IgnoreEdgesColors, OdTvVisualizeBimFilerProperties, getIgnoreEdgesColors, setIgnoreEdgesColors, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(UseSilhouettes, OdTvVisualizeBimFilerProperties, getUseSilhouettes, setUseSilhouettes, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(UseMTforViewsImport, OdTvVisualizeBimFilerProperties, getUseMTforViewsImport, setUseMTforViewsImport, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(ViewsImportThreads, OdTvVisualizeBimFilerProperties, getViewsImportThreads, setViewsImportThreads, getUInt64);
  ODRX_DEFINE_PROPERTY_METHODS(Create3DView, OdTvVisualizeBimFilerProperties, getCreate3DView, setCreate3DView, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(UseAlternativeCDATree, OdTvVisualizeBimFilerProperties, getUseAlternativeCDATree, setUseAlternativeCDATree, getBool);
}

void OdTvVisualizeBimFilerProperties::setBackgroundColor(OdIntPtr ptr)
{
  ODCOLORREF* pColor = (ODCOLORREF*)(ptr);
  if (!pColor)
  {
    ODA_ASSERT(false);
  }
  m_background = *pColor;
}

OdIntPtr OdTvVisualizeBimFilerProperties::getBackgroundColor() const
{
  return (OdIntPtr)(&m_background);
}

void OdTvVisualizeBimFilerProperties::setFeedbackForChooseCallback(OdIntPtr pCallback)
{
  m_pCallback = (OdTvFeedbackForChooseCallback)pCallback;
}

OdIntPtr OdTvVisualizeBimFilerProperties::getFeedbackForChooseCallback() const
{
  return (OdIntPtr)m_pCallback;
}

void OdTvVisualizeBimFilerProperties::setFeedbackForWarningCallback(OdIntPtr pCallback)
{
  m_pWarningCallback = (OdTvFeedbackForWarningCallback)pCallback;
}

OdIntPtr OdTvVisualizeBimFilerProperties::getFeedbackForWarningCallback() const
{
  return (OdIntPtr)m_pWarningCallback;
}


void OdTvVisualizeBimFilerProperties::setDCRect(OdIntPtr rect)
{
  OdTvDCRect* pRect = (OdTvDCRect*)(rect);
  if (!pRect)
  {
    ODA_ASSERT(false);
  }

  m_importRect = *pRect;
}

OdIntPtr OdTvVisualizeBimFilerProperties::getDCRect() const
{
  return (OdIntPtr)(&m_importRect);
}

void OdTvVisualizeBimFilerProperties::setAppendTransform(OdIntPtr pTransform)
{
  const OdTvMatrix* pAppendTransform = (const OdTvMatrix*)(pTransform);

  if (pAppendTransform)
  {
    m_appendTransform = *pAppendTransform;
  }
  else
  {
    m_appendTransform = OdTvMatrix::kIdentity;
  }
}

OdIntPtr OdTvVisualizeBimFilerProperties::getAppendTransform() const
{
  return (OdIntPtr)(&m_appendTransform);
}

//***************************************************************************//
// 'OdTvVisualizeBimFiler' methods implementation
//***************************************************************************//

OdTvVisualizeBimFiler::OdTvVisualizeBimFiler() : m_properties(OdTvVisualizeBimFilerProperties::createObject()), m_moduleNameForCDA(L"TB_CDAProperties")
{
}

OdTvDatabaseId OdTvVisualizeBimFiler::loadFrom(OdDbBaseDatabase *pDatabase, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeBimFilerSourceFromDb dl(pDatabase);
  if (!checkFileVersion(&dl, rc))
    return OdTvDatabaseId();

  if (m_properties->getUseMTforViewsImport())
    return loadFromMT(&dl, pProfileRes, rc);

  return loadFrom(&dl, pProfileRes, rc);
}

OdTvDatabaseId OdTvVisualizeBimFiler::loadFrom(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeBimFilerSourceFromStream dl(pBuffer, pProfileRes);
  if (!checkFileVersion(&dl, rc))
    return OdTvDatabaseId();

  if (m_properties->getUseMTforViewsImport())
    return loadFromMT(&dl, pProfileRes, rc);

  return loadFrom(&dl, pProfileRes, rc);
}

OdTvDatabaseId OdTvVisualizeBimFiler::loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeBimFilerSourceFromFile dl(filePath, pProfileRes);
  if (!checkFileVersion(&dl, rc))
    return OdTvDatabaseId();

  if (m_properties->getUseMTforViewsImport())
    return loadFromMT(&dl, pProfileRes, rc);

  return loadFrom(&dl, pProfileRes, rc);
}

OdTvDatabaseId OdTvVisualizeBimFiler::loadFromMT(OdTvVisualizeBimFilerDbSource *pBimDatabaseSource, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  ODCOLORREF background = *((ODCOLORREF*)m_properties->getBackgroundColor());

  OdTvDatabaseId tvDbId;

  if (rc)
    *rc = tvOk;

  //check that time profiling is need
  bool bUseTimeProfiling = needTimer(pProfileRes);

  double dbReadingTime = 0;
  double tvDbExternalTiming = 0;
  double tvDbInternalTiming = 0.;

  //prepare timing object
  OdTvFilerTimer timing(bUseTimeProfiling);
  timing.startTotal();

  try
  {
    timing.startMisc();

    OdBmDatabasePtr pDb = pBimDatabaseSource->getDb();

    // Create 3D view, if it's absent
    if (!pDb.isNull())
    {
      if (m_properties->getCreate3DView())
        create3DView(pDb.get());
    }

    timing.endMisc();
    dbReadingTime = timing.getMiscTime() + pBimDatabaseSource->getInitTime();

    if (!pDb.isNull())
    {
      // Get chosen views
      OdTvFilerFeedbackForChooseObject filerFeedbackForChooseObject(OD_T("Choose views for import"));
      bool bCanceled = false;
      getChosenViews(pDb, filerFeedbackForChooseObject, bCanceled);
      if (bCanceled)
      {
        if (rc)
          *rc = tvFilerEmptyInternalDatabase;
        //unload Bim modules (try to emulate the OdUninitialized for BIM)
        //here we will unload all including Visualize device
        pDb = NULL;
        odrxDynamicLinker()->unloadUnreferenced();
        return tvDbId;
      }

      timing.startVectorizing();

      OdGsModulePtr pGs = ::odrxDynamicLinker()->loadModule(OdTvVisualizeDeviceModuleName, false);
      if (pGs.isNull())
      {
        if (rc)
          *rc = tvMissingVisualizeDeviceModule;
        return tvDbId;
      }

      //create empty tv database.
      OdTvFactoryId tvFactoryId = odTvGetFactory();
      tvDbId = tvFactoryId.createDatabase();

      // save filename to database user data
      OdTvDatabaseUtils::writeFileNameToTvDatabase(tvDbId, pBimDatabaseSource->getFilename());

      OdBmDBDrawingInfoPtr pDBDrawingInfo = pDb->getAppInfo(OdBm::ManagerType::DBDrawingInfo);

      OdTvBim2VisualizeVecorizationThreadContextPtr pThreadContext = OdTvBim2VisualizeVecorizationThreadContext::createObject();

      //run over all DBDrawings
      OdMutexPtr databaseAccessMutex;
      OdMutexPtr setupDBDrawingViewsMutex; // VIS-1826: temporary solution

      OdGsDevicePtr pEmptyDevice = pGs->createDevice();
      OdRxDictionaryPtr pEmptyProperties = pEmptyDevice->properties();
      if (pEmptyProperties->has(OD_T("DisplayViaGLES2")))
        pEmptyProperties->putAt(OD_T("DisplayViaGLES2"), OdRxVariantValue(false));
      pEmptyDevice->update();

      OdBmUserParamIteratorPtr drawingIterator = pDBDrawingInfo->createIteratorDBDrawings(true);
      while (!drawingIterator->done())
      {
        // Get drawing from iterator and check if it was chosen for import
        OdBmObjectId bmObjectId = drawingIterator->object();
        drawingIterator->next();

        //get name
        OdBmDBDrawingPtr pDBDrawing = bmObjectId.openObject();
        OdString strDrawindName = getNodeNameByViewType(pDBDrawing->getBaseViewNameFormat()) + OD_T("\\") + pDBDrawing->getName();
        OdString strUniqueDrawingName = pDBDrawing->getUniqueName();

        if (!filerFeedbackForChooseObject.find(OdTvFilerFeedbackItemForChoose(strDrawindName, strUniqueDrawingName, true)))
          continue;

        OdTvBim2VisualizeVecorizationContext* pContextForThread = new OdTvBim2VisualizeVecorizationContext(pGs, tvDbId, pDb, background, bmObjectId, m_properties, databaseAccessMutex.get(), setupDBDrawingViewsMutex.get(), m_properties->getViewsImportThreads());
        pThreadContext->vectorizeDevice(pContextForThread);
      } //eo while...
      pThreadContext->wait();

      timing.startMisc();

      if (tvDbId.isValid() && m_properties->getClearEmptyObjects())
        OdTvDatabaseCleaner::cleanTvDatabase(tvDbId);

      timing.endMisc();
      tvDbExternalTiming += timing.getMiscTime();

      timing.endVectorizing();
    }
    else
    {
      if (rc)
        *rc = tvFilerEmptyInternalDatabase;
    }

    if (m_properties->getNeedCDATree())
    {
      timing.startMisc();

      OdTvDatabasePtr pTvDb = tvDbId.openObject(OdTv::kForWrite);
      if (!pTvDb.isNull())
        createCommonDataAccessTree(pTvDb, pDb, pBimDatabaseSource->getFilename() + OD_T(".rvt"));

      timing.endMisc();

      if (pProfileRes)
        pProfileRes->setCDATreeCreationTime(OdInt64((timing.getMiscTime()) * 1000.));
    }

    //Set units
    OdTvModelsIteratorPtr modelsIterPtr = tvDbId.openObject()->getModelsIterator();
    while (!modelsIterPtr->done())
    {
      OdTvModelPtr pModel = modelsIterPtr->getModel().openObject();
      if (!pModel.isNull())
        pModel->setUnits(OdTv::kFeet);
      modelsIterPtr->step();
    }

    // get active device
    for (OdTvDevicesIteratorPtr pIt = tvDbId.openObject()->getDevicesIterator(); !pIt->done(); pIt->step())
    {
      OdTvGsDeviceId devId = pIt->getDevice();

      // get active view
      if (devId.isNull())
        continue;

      OdTvGsDevicePtr pDev = devId.openObject();

      for (int i = 0; i < pDev->numViews(); i++)
      {
        OdTvGsViewId viewId = pDev->viewAt(i);
        if (!viewId.isNull())
        {
          // get visual style
          OdTvVisualStyleId visId = viewId.openObject()->getVisualStyle();
          if (!visId.isNull())
          {
            OdTvVisualStylePtr pVis = visId.openObject(OdTv::kForWrite);
            OdInt32 flag;
            pVis->getOption(OdTvVisualStyleOptions::kEdgeStyles, flag);
            if (m_properties->getUseSilhouettes() != GETBIT(flag, OdTvVisualStyleOptions::kSilhouette))
            {
              SETBIT(flag, OdTvVisualStyleOptions::kSilhouette, m_properties->getUseSilhouettes());
              pVis->setOption(OdTvVisualStyleOptions::kEdgeStyles, flag);
            }
          }
        }
      }
    }
  }
  catch (...)
  {
    if (rc)
      *rc = tvInternal;

    timing.endVectorizing();
  }

  //unload Bim modules (try to emulate the OdUninitialized for BIM)
  //here we will unload all including Visualize device
  odrxDynamicLinker()->unloadUnreferenced();

  timing.endTotal();

  if (pProfileRes)
  {
    pProfileRes->setImportTime(OdInt64(dbReadingTime * 1000.));
    pProfileRes->setVectorizingTime(OdInt64((timing.getVectorizingTime()) * 1000.));
#if !defined(__APPLE__)
    pProfileRes->setTvTime(OdInt64((tvDbInternalTiming + tvDbExternalTiming) * 1000.));
#endif
  }

  return tvDbId;
}

OdTvDatabaseId OdTvVisualizeBimFiler::generate(OdTvFilerTimeProfiling* pProfileRes) const
{
  OdTvDatabaseId tvDbId;

  // does nothing
  return tvDbId;
}

OdTvModelId OdTvVisualizeBimFiler::appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase *pDatabase, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeBimFilerSourceFromDb dl(pDatabase);
  if (!checkFileVersion(&dl, rc))
    return OdTvModelId();
  return appendFrom(databaseId, &dl, pProfileRes, rc);
}

OdTvModelId OdTvVisualizeBimFiler::appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeBimFilerSourceFromStream dl(pBuffer, pProfileRes);
  if (!checkFileVersion(&dl, rc))
    return OdTvModelId();
  return appendFrom(databaseId, &dl, pProfileRes, rc);
}

OdTvModelId OdTvVisualizeBimFiler::appendFrom(const OdTvDatabaseId& databaseId, const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeBimFilerSourceFromFile dl(filePath, pProfileRes);
  if (!checkFileVersion(&dl, rc))
    return OdTvModelId();
  return appendFrom(databaseId, &dl, pProfileRes, rc);
}

OdTvDatabaseId OdTvVisualizeBimFiler::loadFrom(OdTvVisualizeBimFilerDbSource *pBimDatabaseSource, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  ODCOLORREF background = *((ODCOLORREF*)m_properties->getBackgroundColor());

  OdTvDatabaseId tvDbId;

  if (rc)
    *rc = tvOk;

  //check that time profiling is need
  bool bUseTimeProfiling = needTimer(pProfileRes);
  
  double dbReadingTime = 0;
  double tvDbExternalTiming = 0;
  double tvDbInternalTiming = 0.;

  //prepare timing object
  OdTvFilerTimer timing(bUseTimeProfiling);
  timing.startTotal();

  try
  {
    timing.startMisc();

    OdBmDatabasePtr pDb = pBimDatabaseSource->getDb();

    // Create 3D view, if it's absent
    if (!pDb.isNull())
    {
      if (m_properties->getCreate3DView())
        create3DView(pDb.get());
    }

    timing.endMisc();
    dbReadingTime = timing.getMiscTime() + pBimDatabaseSource->getInitTime();

    if (!pDb.isNull())
    {
      // Get chosen views
      OdTvFilerFeedbackForChooseObject filerFeedbackForChooseObject(OD_T("Choose views for import"));
      bool bCanceled = false;
      getChosenViews(pDb, filerFeedbackForChooseObject, bCanceled);
      if (bCanceled)
      {
        if (rc)
          *rc = tvFilerEmptyInternalDatabase;
        //unload Bim modules (try to emulate the OdUninitialized for BIM)
        //here we will unload all including Visualize device
        pDb = NULL;
        odrxDynamicLinker()->unloadUnreferenced();
        return tvDbId;
      }

      timing.startVectorizing();

      OdGsModulePtr pGs = ::odrxDynamicLinker()->loadModule(OdTvVisualizeDeviceModuleName, false);
      if (pGs.isNull())
      {
        if (rc)
          *rc = tvMissingVisualizeDeviceModule;
        return tvDbId;
      }

      //create empty tv database.
      OdTvFactoryId tvFactoryId = odTvGetFactory();
      tvDbId = tvFactoryId.createDatabase();

      // save filename to database user data
      OdTvDatabaseUtils::writeFileNameToTvDatabase(tvDbId, pBimDatabaseSource->getFilename());

      OdBmDBDrawingInfoPtr pDBDrawingInfo = pDb->getAppInfo(OdBm::ManagerType::DBDrawingInfo);

      //run over all DBDrawings
      OdBmUserParamIteratorPtr drawingIterator = pDBDrawingInfo->createIteratorDBDrawings(true);
      unsigned int tvDeviceCount = 0;
      while (!drawingIterator->done())
      {
        // Get drawing from iterator and check if it was chosen for import
        OdBmObjectId bmObjectId = drawingIterator->object();
        drawingIterator->next();

        //get name
        OdBmDBDrawingPtr pDBDrawing = bmObjectId.openObject();
        OdString strDrawindName = getNodeNameByViewType(pDBDrawing->getBaseViewNameFormat()) + OD_T("\\") + pDBDrawing->getName();
        OdString strUniqueDrawingName = pDBDrawing->getUniqueName();

        if (!filerFeedbackForChooseObject.find(OdTvFilerFeedbackItemForChoose(strDrawindName, strUniqueDrawingName, true)))
          continue;

        //create Ex Visualize device
        OdGsDevicePtr pDevice = pGs->createDevice();

        // setup ExVisualize device properties
        OdRxDictionaryPtr pProperties = pDevice->properties();
        OdTvGsDeviceId activeTvDeviceId = OdTvGsDeviceId();
        OdString tvModelName = OdString();
        setupExVisualizeDeviceProp(pProperties, tvDbId, bUseTimeProfiling, tvModelName, m_properties, activeTvDeviceId
          , pDBDrawing->getBaseViewNameFormat() == OdBm::ViewType::_3d);

        //setup bim context
        OdGiContextForBmDatabasePtr pBmContext = OdGiContextForBmDatabase::createObject();
        pBmContext->enableGsModel(true);
        pBmContext->setDatabase(pDb);

        //set the palette
        const ODCOLORREF* palette = odcmAcadPalette(background);

        OdArray<ODCOLORREF, OdMemoryAllocator<ODCOLORREF> > pPalCpy;
        pPalCpy.insert(pPalCpy.begin(), palette, palette + 256);
        pDevice->setLogicalPalette(pPalCpy.asArrayPtr(), 256);

        //set the background
        pDevice->setBackgroundColor(background);
        pBmContext->setPaletteBackground(background);

        //setup layout
        OdGsBmDBDrawingHelperPtr pDrawingHelper = OdGsBmDBDrawingHelper::setupDBDrawingViews(bmObjectId, pDevice, pBmContext);

        //set thin mode
        pDrawingHelper->setThinLinesMode(m_properties->getThinLines());

        //call onsize
        OdTvDCRect* pRect = (OdTvDCRect*)m_properties->getDCRect();
        if (pRect && (pRect->xmax > 0 || pRect->xmin > 0 || pRect->ymax > 0 || pRect->ymin > 0))
        {
          OdGsDCRect  gsRect(pRect->xmin, pRect->xmax, pRect->ymin, pRect->ymax);
          pDrawingHelper->onSize(gsRect);
        }

        //call update (vectorization)
        pDrawingHelper->update();

        //setup connections between views in device and append non db lights
        if (tvDbId.isValid())
        {
          timing.startMisc();

          OdTvDevicesIteratorPtr pDevicesIterator = tvDbId.openObject()->getDevicesIterator();
          if (!pDevicesIterator.isNull()) // here we have O(n^2) but it us not a problem
          {
            unsigned int nCount = 0;
            while (!pDevicesIterator->done())
            {
              OdTvGsDeviceId tvDeviceId = pDevicesIterator->getDevice();
              if (nCount == tvDeviceCount)
              {
                setupConnectionsBetweenTvViews(bmObjectId, pDevice, tvDeviceId);
                resetViewsModelsNames(tvDeviceId);
                break;
              }
              nCount++;
              pDevicesIterator->step();
            }
          }

          timing.endMisc();
          tvDbExternalTiming += timing.getMiscTime();
        }

        tvDeviceCount++;

        if (bUseTimeProfiling)
        {
#if !defined(__APPLE__)
          if (pProperties->has(OD_T("TvElapsedTime")))
          {
            tvDbInternalTiming += OdRxVariantValue(pProperties->getAt(OD_T("TvElapsedTime")).get())->getDouble();
          }
#endif
        }
      } //eo while...

      timing.startMisc();

      if (tvDbId.isValid() && m_properties->getClearEmptyObjects())
        OdTvDatabaseCleaner::cleanTvDatabase(tvDbId);

      timing.endMisc();
      tvDbExternalTiming += timing.getMiscTime();

      timing.endVectorizing();
    }
    else
    {
      if (rc)
        *rc = tvFilerEmptyInternalDatabase;
    }

    if (m_properties->getNeedCDATree())
    {
      timing.startMisc();

      OdTvDatabasePtr pTvDb = tvDbId.openObject(OdTv::kForWrite);
      if (!pTvDb.isNull())
        createCommonDataAccessTree(pTvDb, pDb, pBimDatabaseSource->getFilename() + OD_T(".rvt"));

      timing.endMisc();

      if (pProfileRes)
        pProfileRes->setCDATreeCreationTime(OdInt64((timing.getMiscTime()) * 1000.));
    }

    //Set units
    OdTvModelsIteratorPtr modelsIterPtr = tvDbId.openObject()->getModelsIterator();
    while (!modelsIterPtr->done())
    {
      OdTvModelPtr pModel = modelsIterPtr->getModel().openObject();
      if (!pModel.isNull())
        pModel->setUnits(OdTv::kFeet);
      modelsIterPtr->step();
    }

    // get active device
    for (OdTvDevicesIteratorPtr pIt = tvDbId.openObject()->getDevicesIterator(); !pIt->done(); pIt->step())
    {
      OdTvGsDeviceId devId = pIt->getDevice();

      // get active view
      if (devId.isNull())
        continue;

      OdTvGsDevicePtr pDev = devId.openObject();

      for (int i = 0; i < pDev->numViews(); i++)
      {
        OdTvGsViewId viewId = pDev->viewAt(i);
        if (!viewId.isNull())
        {
          // get visual style
          OdTvVisualStyleId visId = viewId.openObject()->getVisualStyle();
          if (!visId.isNull())
          {
            OdTvVisualStylePtr pVis = visId.openObject(OdTv::kForWrite);
            OdInt32 flag;
            pVis->getOption(OdTvVisualStyleOptions::kEdgeStyles, flag);
            if (m_properties->getUseSilhouettes() != GETBIT(flag, OdTvVisualStyleOptions::kSilhouette))
            {
              SETBIT(flag, OdTvVisualStyleOptions::kSilhouette, m_properties->getUseSilhouettes());
              pVis->setOption(OdTvVisualStyleOptions::kEdgeStyles, flag);
            }
          }
        }
      }
    }
  }
  catch (...)
  {
    if (rc)
      *rc = tvInternal;

    timing.endVectorizing();
  }

  //unload Bim modules (try to emulate the OdUninitialized for BIM)
  //here we will unload all including Visualize device
  odrxDynamicLinker()->unloadUnreferenced();

  timing.endTotal();

  if (pProfileRes)
  {
    pProfileRes->setImportTime(OdInt64(dbReadingTime * 1000.));
    pProfileRes->setVectorizingTime(OdInt64((timing.getVectorizingTime()) * 1000.));
#if !defined(__APPLE__)
    pProfileRes->setTvTime(OdInt64((tvDbInternalTiming + tvDbExternalTiming) * 1000.));
#endif
  }

  return tvDbId;
}


OdTvModelId OdTvVisualizeBimFiler::appendFrom(const OdTvDatabaseId& databaseId, OdTvVisualizeBimFilerDbSource *pBimDatabaseSource, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvModelId tvModelId;

  if (rc)
    *rc = tvOk;

  //check that we are in the real append mode
  OdTvGsDeviceId activeTvGsDeviceId;
  {
    OdTvDatabasePtr pTvDb = databaseId.openObject();
    OdTvDevicesIteratorPtr devicesIteratorPtr = pTvDb->getDevicesIterator();
    while (!devicesIteratorPtr->done())
    {
      activeTvGsDeviceId = devicesIteratorPtr->getDevice();
      if (activeTvGsDeviceId.openObject()->getActive())
        break;
    }
  }

  //get palette, background and device size
  ODCOLORREF background = ODRGB(0, 0, 0);
  OdTvDCRect rect(0, 0, 0, 0);
  OdArray<ODCOLORREF, OdMemoryAllocator<ODCOLORREF> > pPalCpy;

  bool bDeviceExist = false;

  if (!activeTvGsDeviceId.isNull())
  {
    bDeviceExist = true;

    OdTvGsDevicePtr pTvDevice = activeTvGsDeviceId.openObject();

    background = pTvDevice->getBackgroundColor();
    pTvDevice->getSize(rect);

    int nColors;
    const ODCOLORREF* pPalette = pTvDevice->getLogicalPalette(nColors);
    if (nColors >= 256)
      pPalCpy.insert(pPalCpy.begin(), pPalette, pPalette + 256);
    else
    {
      pPalCpy.insert(pPalCpy.begin(), pPalette, pPalette + nColors);
      pPalCpy.insert(pPalCpy.begin() + nColors, 256 - nColors, ODRGB(0, 0, 0));
    }
  }
  else
  {
    background = *((ODCOLORREF*)m_properties->getBackgroundColor());
    OdTvDCRect* pRect = (OdTvDCRect*)m_properties->getDCRect();
    if (pRect)
      rect = *pRect;

    const ODCOLORREF* palette = odcmAcadPalette(background);  // black background
    pPalCpy.insert(pPalCpy.begin(), palette, palette + 256);
  }

  //collcet current models and blocks
  std::set<OdTvGsViewId> foreignViews;
  std::set<OdTvModelId> foreignModels;
  std::set<OdTvBlockId> foreignBlocks;
  OdTvDatabaseUtils::collectViewsModelsAndBlocks(databaseId, foreignViews, foreignModels, foreignBlocks);

  //check that time profiling is need
  bool bUseTimeProfiling = false;
  if (pProfileRes)
    bUseTimeProfiling = true;

  double dbReadingTime = 0;
  double tvDbExternalTiming = 0;
  double tvDbInternalTiming = 0.;

  //prepare timing object
  OdTvFilerTimer timing(bUseTimeProfiling);
  timing.startTotal();

  //get file name
  OdString fileName = pBimDatabaseSource->getFilename();

  try
  {
    timing.startMisc();

    OdBmDatabasePtr pDb = pBimDatabaseSource->getDb();

    // Create 3D view, if it's absent (for the append we should do it always)
    if (!pDb.isNull())
      create3DView(pDb.get());

    timing.endMisc();
    dbReadingTime = timing.getMiscTime() + pBimDatabaseSource->getInitTime();

    if (!pDb.isNull())
    {
      timing.startVectorizing();

      OdGsModulePtr pGs = ::odrxDynamicLinker()->loadModule(OdTvVisualizeDeviceModuleName, false);
      if (pGs.isNull())
      {
        if (rc)
          *rc = tvMissingVisualizeDeviceModule;
        return tvModelId;
      }

      // save filename to database user data
      OdTvDatabaseUtils::writeFileNameToTvDatabase(databaseId, fileName);

      OdBmDBDrawingInfoPtr pDBDrawingInfo = pDb->getAppInfo(OdBm::ManagerType::DBDrawingInfo);

      // Get 3d drawing
      OdBmObjectId bmObjectId;
      OdBmDBDrawingPtr pDBDrawing;
      OdBmUserParamIteratorPtr drawingIterator = pDBDrawingInfo->createIteratorDBDrawings(true);
      while (!drawingIterator->done())
      {
        bmObjectId = drawingIterator->object();
        pDBDrawing = bmObjectId.openObject();

        if (pDBDrawing->getName() == OD_T("{3D}"))
          break;

        drawingIterator->next();
      }
      if (bmObjectId.isNull())
      {
        if (rc)
          *rc = tvInternal;
        return tvModelId;
      }

      // Generate model name
      OdString modelName = OdTvDatabaseUtils::generateModelName(databaseId, fileName);

      //create ExVisualize device
      OdGsDevicePtr pDevice = pGs->createDevice();

      // setup ExVisualize device properties
      OdRxDictionaryPtr pProperties = pDevice->properties();
      setupExVisualizeDeviceProp(pProperties, databaseId, bUseTimeProfiling, modelName, m_properties, activeTvGsDeviceId, pDBDrawing->getBaseViewNameFormat() == OdBm::ViewType::_3d);

      //we don't need to setup extents inside appendFrom since we can have additional units transform matrix here
      if (pProperties->has(OD_T("DisableSetingExtents")))
        pProperties->putAt(OD_T("DisableSetingExtents"), OdRxVariantValue(true));

      //create BIM context
      OdGiContextForBmDatabasePtr pBmContext = OdGiContextForBmDatabase::createObject();
      pBmContext->enableGsModel(true);
      pBmContext->setDatabase(pDb);

      //setup palette, background and device size
      //a.palette
      pDevice->setLogicalPalette(pPalCpy.asArrayPtr(), 256);

      //b. background
      pDevice->setBackgroundColor(background);
      pBmContext->setPaletteBackground(background);

      //setup layout
      OdGsBmDBDrawingHelperPtr pDrawingHelper = OdGsBmDBDrawingHelper::setupDBDrawingViews(bmObjectId, pDevice, pBmContext);

      //c. thin line mode
      pDrawingHelper->setThinLinesMode(m_properties->getThinLines());

      //d. call onsize
      if (rect.xmax > 0 || rect.xmin > 0 || rect.ymax > 0 || rect.ymin > 0)
      {
        OdGsDCRect  gsRect(rect.xmin, rect.xmax, rect.ymin, rect.ymax);
        pDrawingHelper->onSize(gsRect);
      }

      //call update (vectorization)
      pDrawingHelper->update();

      if (bUseTimeProfiling)
      {
#if !defined(__APPLE__)
        if (pProperties->has(OD_T("TvElapsedTime")))
        {
          tvDbInternalTiming = OdRxVariantValue(pProperties->getAt(OD_T("TvElapsedTime")).get())->getDouble();
        }
#endif
      }

      if (databaseId.isValid())
      {
        timing.startMisc();

        //get active device if need
        OdTvDatabaseId& tvDvId = const_cast<OdTvDatabaseId&>(databaseId);
        if (activeTvGsDeviceId.isNull())
        {
          for (OdTvDevicesIteratorPtr pIt = tvDvId.openObject()->getDevicesIterator(); !pIt->done(); pIt->step())
          {
            OdTvGsDeviceId devId = pIt->getDevice();

            if (devId.isNull())
              continue;
            else
            {
              activeTvGsDeviceId = devId;
              setupConnectionsBetweenTvViews(bmObjectId, pDevice, activeTvGsDeviceId);
              break;
            }
          }
        }

        //clear empty objects (always)
        OdTvDatabaseCleaner::cleanTvDatabaseForAppend(tvDvId, foreignViews, foreignModels, foreignBlocks);

        //rename and get model
        OdString newModelName = resetModelNameForAppend(activeTvGsDeviceId, fileName, foreignModels);
        {
          OdTvDatabasePtr pTvDb = databaseId.openObject();
          tvModelId = pTvDb->findModel(newModelName);
        }

        //apply transform if need 
        OdTvMatrix* pTransfrom = (OdTvMatrix*)m_properties->getAppendTransform();
        if (pTransfrom)
        {
          OdTvDatabaseId& tvDvId = const_cast<OdTvDatabaseId&>(databaseId);
          OdTvDatabaseUtils::applyTransformToTheModel(tvDvId, newModelName, *pTransfrom);
        }

        //apply units
        if (!tvModelId.isNull())
        {
          OdTvModelPtr pModel = tvModelId.openObject(OdTv::kForWrite);
          if (!pModel.isNull())
            pModel->setUnits(OdTv::kFeet);
        }

        timing.endMisc();
        tvDbExternalTiming = timing.getMiscTime();

        // get active device
        if(!bDeviceExist)
        {
          for (OdTvDevicesIteratorPtr pIt = tvDvId.openObject()->getDevicesIterator(); !pIt->done(); pIt->step())
          {
            OdTvGsDeviceId devId = pIt->getDevice();

            // get active view
            if (devId.isNull())
              continue;

            OdTvGsDevicePtr pDev = devId.openObject();

            for (int i = 0; i < pDev->numViews(); i++)
            {
              OdTvGsViewId viewId = pDev->viewAt(i);
              if (!viewId.isNull())
              {
                // get visual style
                OdTvVisualStyleId visId = viewId.openObject()->getVisualStyle();
                if (!visId.isNull())
                {
                  OdTvVisualStylePtr pVis = visId.openObject(OdTv::kForWrite);
                  OdInt32 flag;
                  pVis->getOption(OdTvVisualStyleOptions::kEdgeStyles, flag);
                  if (m_properties->getUseSilhouettes() != GETBIT(flag, OdTvVisualStyleOptions::kSilhouette))
                  {
                    SETBIT(flag, OdTvVisualStyleOptions::kSilhouette, m_properties->getUseSilhouettes());
                    pVis->setOption(OdTvVisualStyleOptions::kEdgeStyles, flag);
                  }
                }
              }
            }
          }
        }

      }

      timing.endVectorizing();

    }
    else
    {
      if (rc)
        *rc = tvFilerEmptyInternalDatabase;
    }

  }
  catch (...)
  {
    if (rc)
      *rc = tvInternal;

    timing.endMisc();
    timing.endVectorizing();
  }

  //unload Bim modules (try to emulate the OdUninitialized for BIM)
  //here we will unload all including Visualize device
  odrxDynamicLinker()->unloadUnreferenced();

  timing.endTotal();

  if (pProfileRes)
  {
    pProfileRes->setImportTime(OdInt64(dbReadingTime * 1000.));
    pProfileRes->setVectorizingTime(OdInt64((timing.getVectorizingTime()) * 1000.));
#if !defined(__APPLE__)
    pProfileRes->setTvTime(OdInt64((tvDbInternalTiming + tvDbExternalTiming) * 1000.));
#endif
  }

  return tvModelId;
}

OdTvResult OdTvVisualizeBimFiler::startActionsWithNativeProperties(const OdString& sFilePath, bool bIsPartial)
{
  if (!m_pDatabaseForNativeProp.isNull() && m_pDatabaseForNativeProp->getFilename() != sFilePath)
    m_pDatabaseForNativeProp.release();
  else if (!m_pDatabaseForNativeProp.isNull())
    return tvOk;

  OdTvResult rc = tvOk;
  if( m_pFilerPtr.isNull() )
  {
    m_pFilerPtr = new OdTvVisualizeBimFilerSourceFromFile( sFilePath, NULL );
  }
  OdTvVisualizeBimFilerSourceFromFile* pFiler = (OdTvVisualizeBimFilerSourceFromFile*)( m_pFilerPtr.get() );// dl(sFilePath, NULL);
  
  if (m_pRxPropertiesModule.isNull())
    m_pRxPropertiesModule = ::odrxDynamicLinker()->loadModule(L"RxProperties");

  m_moduleNameForCDA = m_properties->getUseAlternativeCDATree() ? OdString("TB_CDA3DViewTree") : OdString("TB_CDAProperties");

  if (m_pBmPropertiesModule.isNull())
    m_pBmPropertiesModule = ::odrxDynamicLinker()->loadModule(m_moduleNameForCDA);

  try
  {
    m_pDatabaseForNativeProp = pFiler->getDb();
  }
  catch (...)
  {
    return tvFilerEmptyInternalDatabase;
  }

  return rc;
}

bool OdTvVisualizeBimFiler::isActionsWithNativePropertiesStarted(const OdString& sFilePath)
{
  if (!m_pDatabaseForNativeProp.isNull() && m_pDatabaseForNativeProp->getFilename() == sFilePath)
    return true;

  return false;
}

OdTvResult OdTvVisualizeBimFiler::endActionsWithNativeProperties()
{
  m_pFilerPtr = NULL;
  if (!m_pDatabaseForNativeProp.isNull())
    m_pDatabaseForNativeProp.release();

  if (!m_pBmPropertiesModule.isNull())
  {
    m_pRxPropertiesModule.release();
    m_pBmPropertiesModule.release();
    ::odrxDynamicLinker()->unloadModule(L"RxProperties");
    ::odrxDynamicLinker()->unloadModule(m_moduleNameForCDA);
    ::odrxDynamicLinker()->unloadUnreferenced();
  }

  return tvOk;
}

OdRxMemberIteratorPtr OdTvVisualizeBimFiler::getNativePropertiesIterator(OdUInt64 dbHandle, OdTvResult* rc)
{
  if (m_pDatabaseForNativeProp.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedDatabase;
    return OdRxMemberIteratorPtr();
  }

  OdRxMemberIteratorPtr pIter;
  if (dbHandle == 0)
    pIter = OdRxMemberQueryEngine::theEngine()->newMemberIterator(m_pDatabaseForNativeProp.get());
  else
  {
    OdBmObjectId dbObjectId = m_pDatabaseForNativeProp->getObjectId(OdDbHandle(dbHandle));
    if (dbObjectId.isNull())
    {
      if (rc)
        *rc = tvNativePropMissedObject;
      return OdRxMemberIteratorPtr();
    }
    OdBmObjectPtr pDbObject = dbObjectId.safeOpenObject();
    pIter = OdRxMemberQueryEngine::theEngine()->newMemberIterator(pDbObject.get());
  }

  if (pIter.isNull())
  {
    if (rc)
      *rc = tvInternal;
    return OdRxMemberIteratorPtr();
  }

  if (rc)
    *rc = tvOk;

  return pIter;
}

OdRxValue OdTvVisualizeBimFiler::getNativePropertyValue(OdUInt64 dbHandle, const OdRxPropertyPtr& pProperty, bool* bReadOnly, OdTvResult* rc)
{
  if (pProperty.isNull())
  {
    if (rc)
      *rc = tvInvalidInput;
    return OdRxValue();
  }

  if (m_pDatabaseForNativeProp.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedDatabase;
    return OdRxValue();
  }

  OdBmObjectPtr pDbObject;
  if (dbHandle == 0)
    pDbObject = m_pDatabaseForNativeProp;
  else
  {
    OdBmObjectId dbObjectId = m_pDatabaseForNativeProp->getObjectId(OdDbHandle(dbHandle));
    pDbObject = dbObjectId.safeOpenObject();
  }

  if (pDbObject.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedObject;
    return OdRxValue();
  }

  OdRxValue value;
  OdResult odRes = pProperty->getValue(pDbObject, value);
  if (bReadOnly)
    *bReadOnly = pProperty->isReadOnly(pDbObject);

  if (odRes != eOk)
  {
    if (rc)
      *rc = tvInternal;

    return OdRxValue();
  }

  if (rc)
    *rc = tvOk;

  return value;
}

OdRxValueIteratorPtr OdTvVisualizeBimFiler::getNativeCollectionPropertyIterator(OdUInt64 dbHandle, const OdRxCollectionPropertyPtr& pCollectionProperty, bool* bReadOnly /*= NULL*/, OdTvResult* rc /*= NULL*/)
{
  if (m_pDatabaseForNativeProp.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedDatabase;
    return OdRxValueIteratorPtr();
  }

  if (pCollectionProperty.isNull())
  {
    if (rc)
      *rc = tvInvalidInput;
    return OdRxValueIteratorPtr();
  }

  OdRxValueIteratorPtr pValIter;
  if (dbHandle == 0)
  {
    pValIter = pCollectionProperty->newValueIterator(m_pDatabaseForNativeProp.get());

    if (bReadOnly)
      *bReadOnly = pCollectionProperty->isReadOnly(m_pDatabaseForNativeProp);
  }
  else
  {
    OdBmObjectId dbObjectId = m_pDatabaseForNativeProp->getObjectId(OdDbHandle(dbHandle));
    if (dbObjectId.isNull())
    {
      if (rc)
        *rc = tvNativePropMissedObject;
      return OdRxValueIteratorPtr();
    }
    OdBmObjectPtr pDbObject = dbObjectId.safeOpenObject();

    pValIter = pCollectionProperty->newValueIterator(pDbObject.get());

    if (bReadOnly)
      *bReadOnly = pCollectionProperty->isReadOnly(pDbObject.get());

  }

  if (rc)
    *rc = tvOk;

  return pValIter;
}

OdTvResult OdTvVisualizeBimFiler::setNativePropertyValue(OdUInt64 dbHandle, OdRxPropertyPtr& pProperty, const OdRxValue& value)
{
  if (pProperty.isNull())
    return tvInvalidInput;

  if (m_pDatabaseForNativeProp.isNull())
    return tvNativePropMissedDatabase;

  OdBmObjectPtr pDbObject;
  if (dbHandle == 0)
    pDbObject = m_pDatabaseForNativeProp;
  else
  {
    OdBmObjectId dbObjectId = m_pDatabaseForNativeProp->getObjectId(OdDbHandle(dbHandle));
    pDbObject = dbObjectId.safeOpenObject();
  }

  if (pDbObject.isNull())
    return tvNativePropMissedObject;

  pProperty->setValue(pDbObject, value);

  return tvOk;
}


OdDbBaseDatabase* OdTvVisualizeBimFiler::getNativeDatabase(OdTvResult* rc ) const
{
  if (m_pDatabaseForNativeProp.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedDatabase;
    return NULL;
  }

  return (OdDbBaseDatabase*)m_pDatabaseForNativeProp.get();
}

void OdTvVisualizeBimFiler::setupConnectionsBetweenTvViews(OdBmObjectId idDBDrawing, OdGsDevice* pDevice, OdTvGsDeviceId idTVDevice) const
{
  //check existance of the tv device
  OdTvGsDevicePtr pTvDevice = idTVDevice.openObject(OdTv::kForWrite);
  if (pTvDevice.isNull())
    return;

  OdBmDBDrawingPtr pDBDrawing = idDBDrawing.safeOpenObject();
  OdBmObjectIdArray vpsArray;
  pDBDrawing->getViewports(vpsArray);
  ODA_ASSERT(0 != vpsArray.size());
  if (vpsArray.size() == 0)
    return;

  //set name to the device
  pTvDevice->setName(pDBDrawing->getName());

  //get main view (gs views and names)
  OdBmViewportPtr pViewport = vpsArray.getAt(0).safeOpenObject();

  OdBmObjectId idDBMainView = pViewport->getDbViewId();
  OdBmDBViewPtr pDBMainView = idDBMainView.safeOpenObject();
  OdString strMainViewName = correctName(pDBMainView->getViewName());
  OdString strMainViewNameFront = strMainViewName + OD_T("_Front");
  OdString strMainViewNameBack = strMainViewName + OD_T("_Back");

  OdGsView* pMainView = pViewport->gsView();
  OdGsView* pMainViewFront = pViewport->gsFrontView();
  OdGsView* pMainViewBack = pViewport->gsBackView();
  if (!pMainView || !pMainViewFront || !pMainViewBack)
    return;

  //get world to Device matrix from main view
  OdGeMatrix3d matr = pMainView->worldToDeviceMatrix();
  matr.invert();

  //get appropriate Visualize main and front main views
  int mainViewId = getViewId(pDevice, pMainView);
  int mainFrontViewId = getViewId(pDevice, pMainViewFront);
  int mainBackViewId = getViewId(pDevice, pMainViewBack);

  OdTvGsViewId idTvMainView = pTvDevice->viewAt(mainViewId);
  OdTvGsViewId idTvMainFrontView = pTvDevice->viewAt(mainFrontViewId);
  OdTvGsViewId idTvMainBackView = pTvDevice->viewAt(mainBackViewId);
  if (idTvMainView.isNull() || idTvMainFrontView.isNull() || idTvMainBackView.isNull())
    return;

  // Create app
  OdTvDatabaseId tvDatabaseId = idTVDevice.openObject()->getDatabase();
  OdTvDatabasePtr pTvDatabase = tvDatabaseId.openObject();
  bool bAlreadyExist = false;
  OdTvRegAppId appId = pTvDatabase->registerAppName(L"2Visualize", bAlreadyExist);

  OdTvGsViewPtr pTVViewMain = idTvMainView.openObject(OdTv::kForWrite);
  pTVViewMain->setActive(true);
  pTVViewMain->setName(strMainViewName);
  pTVViewMain->addSibling(idTvMainFrontView);
  pTVViewMain->addSibling(idTvMainBackView);

  OdTvGsViewPtr pTVViewMainFront = idTvMainFrontView.openObject(OdTv::kForWrite);
  pTVViewMainFront->setName(strMainViewNameFront);

  OdTvGsViewPtr pTVViewMainBack = idTvMainBackView.openObject(OdTv::kForWrite);
  pTVViewMainBack->setName(strMainViewNameBack);

  if (pDBDrawing->getBaseViewNameFormat() != OdBm::ViewType::_3d)
  {
    pTVViewMain->set2dMode(true);
    pTVViewMainFront->set2dMode(true);
    pTVViewMainBack->set2dMode(true);
  }

  //apply clipping 
  applyClipping(pTVViewMain, pMainView, matr, pDBDrawing->getBaseViewNameFormat() == OdBm::ViewType::_3d);
  applyClipping(pTVViewMainFront, pMainViewFront, matr, pDBDrawing->getBaseViewNameFormat() == OdBm::ViewType::_3d);
  applyClipping(pTVViewMainBack, pMainViewBack, matr, pDBDrawing->getBaseViewNameFormat() == OdBm::ViewType::_3d);

  // Set of viewports for a sheet. OdGsPaperLayoutHelper is an example.
  OdUInt32 iArrSize = vpsArray.size();
  if (iArrSize > 1) // Sheets has more than 1 viewport
  {
    for (OdUInt32 i = 1; i < iArrSize; ++i)
    {
      OdBmViewportPtr pEmbeddedViewport = vpsArray.getAt(i).safeOpenObject();

      OdBmObjectId idDBView = pEmbeddedViewport->getDbViewId();
      OdBmDBViewPtr pDBView = idDBView.safeOpenObject();
      OdString strName = correctName(pDBView->getViewName());

      OdGsView* pGsView = pEmbeddedViewport->gsView();
      OdGsView* pGsFrontView = pEmbeddedViewport->gsFrontView();
      OdGsView* pGsBackView = pEmbeddedViewport->gsBackView();

      int embeddedViewId = getViewId(pDevice, pGsView);
      int embeddedFrontViewId = getViewId(pDevice, pGsFrontView);
      int embeddedBackViewId = getViewId(pDevice, pGsBackView);
      OdTvGsViewId idTvEmbeddedView = idTVDevice.openObject()->viewAt(embeddedViewId);
      OdTvGsViewId idTvEmbeddedFrontView = idTVDevice.openObject()->viewAt(embeddedFrontViewId);
      OdTvGsViewId idTvEmbeddedBackView = idTVDevice.openObject()->viewAt(embeddedBackViewId);
      if (!idTvEmbeddedView.isNull() && !idTvEmbeddedFrontView.isNull() && !idTvEmbeddedBackView.isNull())
      {
        OdTvGsViewPtr pTVViewEmbedded = idTvEmbeddedView.openObject(OdTv::kForWrite);
        OdTvGsViewPtr pTVViewEmbeddedFront = idTvEmbeddedFrontView.openObject(OdTv::kForWrite);
        OdTvGsViewPtr pTVViewEmbeddedBack = idTvEmbeddedBackView.openObject(OdTv::kForWrite);

        OdString strNameFront = strName + OD_T("_Front");
        OdString strNameBack = strName + OD_T("_Back");
        pTVViewEmbedded->setName(strName);
        pTVViewEmbeddedFront->setName(strNameFront);
        pTVViewEmbeddedBack->setName(strNameBack);

        if (pDBDrawing->getBaseViewNameFormat() != OdBm::ViewType::_3d)
        {
          pTVViewEmbedded->set2dMode(true);
          pTVViewEmbeddedFront->set2dMode(true);
          pTVViewEmbeddedBack->set2dMode(true);
        }

        pTVViewEmbedded->addSibling(idTvEmbeddedFrontView);
        pTVViewEmbedded->addSibling(idTvEmbeddedBackView);
        OdTvGsView::ViewportObjectInfo vi;

        //get viewport parameters
        OdGsDCRect rect;
        pGsView->getViewport(rect);

        OdTvPoint ll, ur;
        ll.set(rect.m_min.x, rect.m_min.y, 0.);
        ur.set(rect.m_max.x, rect.m_max.y, 0.);

        ll.transformBy(matr);
        ur.transformBy(matr);

        vi.m_wcsLowerLeft = OdTvPoint2d(ll.x, ll.y);
        vi.m_wcsUpperRight = OdTvPoint2d(ur.x, ur.y);

        //get clipping parameters
        OdIntArray counts;
        OdGePoint2dArray vertices;
        pGsView->viewportClipRegion(counts, vertices);

        vi.m_numPtsInContours.resize(counts.size());
        for (unsigned int i = 0; i < counts.size(); i++)
        {
          vi.m_numPtsInContours[i] = OdUInt32(counts[i]);
        }

        vi.m_wcsCountoursPts.resize(vertices.size());
        for (unsigned int i = 0; i < vertices.size(); i++)
        {
          OdTvPoint vertices3d = OdTvPoint(vertices[i].x, vertices[i].y, 0.);
          vertices3d.transformBy(matr);
          vi.m_wcsCountoursPts[i] = OdTvPoint2d(vertices3d.x, vertices3d.y);
        }

        //add view as a viewport object
        pTVViewMain->addViewportObject(idTvEmbeddedView, vi);

        vi.m_wcsCountoursPts.clear();
        vi.m_numPtsInContours.clear();
        pTVViewMain->addViewportObject(idTvEmbeddedFrontView, vi);
        pTVViewMain->addViewportObject(idTvEmbeddedBackView, vi);
      }
    }
  }

  return;
}

void OdTvVisualizeBimFiler::resetViewsModelsNames(OdTvGsDeviceId idTVDevice) const
{
  OdTvGsDevicePtr pDevice = idTVDevice.openObject();

  for (int i = 0; i < pDevice->numViews(); i++)
  {
    OdTvGsViewId viewId = pDevice->viewAt(i);
    OdTvGsViewPtr pView = viewId.openObject();
    if ( pView.isNull() )
      continue;

    OdString viewName = pView->getName();
    int nModels = pView->numModels();

    for (int j = 0; j < nModels; j++)
    {
      OdTvModelId modelId = pView->modelAt(j);
      OdTvModelPtr pModel = modelId.openObject(OdTv::kForWrite);

      if ( !pModel.isNull() )
      {
        if (nModels == 1)
          pModel->setName(viewName);
        else
        {
          OdString modelName;
          modelName.format(L"%s_%d", viewName.c_str(), j+1);
        }
      }
    }
  }
  return;
}

OdString OdTvVisualizeBimFiler::resetModelNameForAppend(OdTvGsDeviceId idTVDevice, const OdString& fileName, const std::set<OdTvModelId>& foreignModels) const
{
  OdTvGsDevicePtr pDevice = idTVDevice.openObject();

  //here we will suppose that our model is in active view
  OdTvGsViewId viewId = pDevice->getActiveView();
  if (viewId.isNull()) //bad case - we get first
  {
    for (int i = 0; i < pDevice->numViews(); i++)
    {
      OdTvGsViewId vId = pDevice->viewAt(i);
      if (vId.isNull())
        continue;
      else
      {
        viewId = vId;
        break;
      }
    }
  }
  if (viewId.isNull())
    return OdString();

  OdString newModelName;
  {
    OdTvGsViewPtr pView = viewId.openObject();
    OdString name = pView->getName();
    
    int nModels = pView->numModels();
    for (int j = 0; j < nModels; j++)
    {
      OdTvModelId modelId = pView->modelAt(j);
      if (foreignModels.find(modelId) == foreignModels.end())
      {
        OdTvModelPtr pModel = modelId.openObject(OdTv::kForWrite);
        if (pModel->getNeedSaveInFile()) //means normal model
        {
          newModelName = name + OD_T("_");
          newModelName += fileName;
          OdString baseModelName = newModelName;
          OdUInt32 modelIndex = 1;
          while ( pModel->setName(newModelName) != tvOk && modelIndex < 10)
          {
            OdString sModelIndex;
            sModelIndex.format(OD_T("%d"), modelIndex);

            newModelName = baseModelName + OD_T("_") + sModelIndex;
            modelIndex++;
          }
          break;
        }
      }
    }
  }

  return newModelName;
}

int OdTvVisualizeBimFiler::getViewId(OdGsDevice* pDevice, OdGsView* pView) const
{
  if (!pDevice || !pView)
    return -1;

  int num = pDevice->numViews();
  int iViewId = -1;
  for (int i = 0; i < num; ++i)
  {
    OdGsView* pViewForFind = pDevice->viewAt(i);
    if (pViewForFind == pView)
    {
      iViewId = i;
      break;
    }
  }

  return iViewId;
}

void OdTvVisualizeBimFiler::applyClipping(OdTvGsViewPtr pTvView, OdGsView* pGsView, const OdGeMatrix3d& mDevToWorld, bool bIs3DView) const
{
  if ( pGsView == 0 || pTvView.isNull() )
    return;

  //get clipping parameters
  OdIntArray counts;
  OdGePoint2dArray vertices;
  pGsView->viewportClipRegion(counts, vertices);

  if ( counts.size() == 0 ) //there is no clipping
    return;

  OdUInt32Array     numPtsInContours;
  numPtsInContours.resize(counts.size());
  for (unsigned int i = 0; i < counts.size(); i++)
  {
    numPtsInContours[i] = OdUInt32(counts[i]);
  }

  OdTvPoint2dArray wcsPoints;
  wcsPoints.resize(vertices.size());
  for (unsigned int i = 0; i < vertices.size(); i++)
  {
    OdGePoint3d vertices3d = OdGePoint3d(vertices[i].x, vertices[i].y, 0.);
    if (!bIs3DView)
      vertices3d.transformBy(mDevToWorld);
    wcsPoints[i] = OdTvPoint2d(vertices3d.x, vertices3d.y);
  }

  pTvView->setClipRegion(int(counts.size()), numPtsInContours.getPtr(), wcsPoints.getPtr(), true);
}


void OdTvVisualizeBimFiler::getChosenViews(OdBmDatabasePtr pDb, OdTvFilerFeedbackForChooseObject& filerFeedbackForChoose, bool& bCanceled) const
{
  OdTvFilerFeedbackItemForChooseArray* pFilerFeedbackForChooseArray = filerFeedbackForChoose.getFilerFeedbackItemForChooseArrayPtr();

  OdBmDBDrawingInfoPtr pDBDrawingInfo = pDb->getAppInfo(OdBm::ManagerType::DBDrawingInfo);

  //run over all DBDrawings
  OdBmUserParamIteratorPtr drawingIterator = pDBDrawingInfo->createIteratorDBDrawings(true);
  while (!drawingIterator->done())
  {
    // Get drawing from iterator and check if it was chosen for import
    OdBmObjectId bmObjectId = drawingIterator->object();
    drawingIterator->next();

    //get name
    OdBmDBDrawingPtr pDBDrawing = bmObjectId.openObject();
    if (!pDBDrawing.isNull())
    {
      OdString strDrawindName = getNodeNameByViewType(pDBDrawing->getBaseViewNameFormat()) + OD_T("\\") + pDBDrawing->getName();
      OdString strUniqueDrawindName = pDBDrawing->getUniqueName();

      OdTvFilerFeedbackItemForChoose filerFeedbackForChoose(strDrawindName, strUniqueDrawindName);
      if ( bmObjectId == pDBDrawingInfo->getActiveDBDrawingId() )
        filerFeedbackForChoose.m_bChosen = true;

      pFilerFeedbackForChooseArray->append(filerFeedbackForChoose);
    }
  }

  if (m_properties->getFeedbackForChooseCallback() != NULL)
  {
    ((OdTvFeedbackForChooseCallback)m_properties->getFeedbackForChooseCallback())(filerFeedbackForChoose);
    if (filerFeedbackForChoose.getFilerFeedbackItemForChooseArrayPtr()->length() == 0)
      bCanceled = true;
  }
}

void OdTvVisualizeBimFiler::setupExVisualizeDeviceProp(OdRxDictionaryPtr& pProperties, const OdTvDatabaseId& tvDbId, bool bUseTimeProfiling,
                                                       const OdString& modelName, const OdTvVisualizeBimFilerPropertiesPtr& importProperties,
                                                       OdTvGsDeviceId& tvDeviceIdForAppend, bool bIs3DView) const
{
  if (pProperties.get())
  {
    if (pProperties->has(OD_T("DisplayViaGLES2")))
      pProperties->putAt(OD_T("DisplayViaGLES2"), OdRxVariantValue(false));
    if (pProperties->has(OD_T("AllowNonPersistentObjects")))
      pProperties->putAt(OD_T("AllowNonPersistentObjects"), OdRxVariantValue(false));
#if !defined(__APPLE__)
    if (pProperties->has(OD_T("EnableTiming")))
      pProperties->putAt(OD_T("EnableTiming"), OdRxVariantValue(bUseTimeProfiling));
#endif
    if (pProperties->has(OD_T("TvDatabaseID")))
      pProperties->putAt(OD_T("TvDatabaseID"), OdRxVariantValue((OdIntPtr)(&tvDbId)));

    if (pProperties->has(OD_T("WriteUserData")))
      pProperties->putAt(OD_T("WriteUserData"), OdRxVariantValue(importProperties->getStoreSourceObjects()));
    if (pProperties->has(OD_T("GenerateEntityNames")))
      pProperties->putAt(OD_T("GenerateEntityNames"), OdRxVariantValue(importProperties->getObjectNaming()));

    if (pProperties->has(OD_T("PerModelViews")))
      pProperties->putAt(OD_T("PerModelViews"), OdRxVariantValue(true));
    if (pProperties->has(OD_T("CompareUnnamedImages")))
      pProperties->putAt(OD_T("CompareUnnamedImages"), OdRxVariantValue(true));

    if (bIs3DView)
    {
      if (pProperties->has(OD_T("IgnoreColoredShape")))
        pProperties->putAt(OD_T("IgnoreColoredShape"), OdRxVariantValue(true));
    }

    if (pProperties->has(OD_T("ModelName")))
      pProperties->putAt(OD_T("ModelName"), OdRxVariantValue(modelName));

    if (!tvDeviceIdForAppend.isNull())
    {
      if (pProperties->has(OD_T("IgnoreViewInfoFlags")))
        pProperties->putAt(OD_T("IgnoreViewInfoFlags"), OdRxVariantValue(true));
      if (pProperties->has(OD_T("NamePrefix")))
        pProperties->putAt(OD_T("NamePrefix"), OdRxVariantValue(modelName));
      if (pProperties->has(OD_T("TvDeviceDAM")))
        pProperties->putAt(OD_T("TvDeviceDAM"), OdRxVariantValue((OdIntPtr)(&tvDeviceIdForAppend)));

      OdTvGsViewId viewId = tvDeviceIdForAppend.openObject()->getActiveView();
      OdString name = viewId.openObject()->getName();
      if (pProperties->has(OD_T("TvViewDAM")))
        pProperties->putAt(OD_T("TvViewDAM"), OdRxVariantValue((OdIntPtr)(&viewId)));
    }
    //Write font file path as user data
    if( pProperties->has( OD_T("WriteFontFilePath") ))
      pProperties->putAt( OD_T("WriteFontFilePath"), OdRxVariantValue( true ) );

    if (pProperties->has(OD_T("IgnoreFlags")))
    {
      OdUInt16 flags = OdRxVariantValue(pProperties->getAt(OD_T("IgnoreFlags")).get())->getUInt16();
      SETBIT(flags, DeviceIgnoreFlags::kIgnoreEdgesColors, m_properties->getIgnoreEdgesColors());
      pProperties->putAt(OD_T("IgnoreFlags"), OdRxVariantValue(flags));
    }

    //Support geometry inside lights
    if( pProperties->has( OD_T( "SupportGeometryInLight" ) ) )
      pProperties->putAt( OD_T( "SupportGeometryInLight" ), OdRxVariantValue( true ) );
  }
}

bool OdTvVisualizeBimFiler::checkFileVersion(OdTvVisualizeBimFilerDbSource* pBimFiler, OdTvResult* rc) const
{
  if (!pBimFiler)
    return false;

  OdString errStr;
  if (!pBimFiler->isFileValid(errStr))
  {
    OdTvFilerFeedbackForWarning warningFeedback(errStr);
    if (m_properties->getFeedbackForWarningCallback() != NULL)
    {
      ((OdTvFeedbackForWarningCallback)m_properties->getFeedbackForWarningCallback())(warningFeedback);
      if (warningFeedback.isAborted())
      {
        if (rc)
          *rc = tvUserAbort;

        return false;
      }
    }
  }

  return true;
}

void OdTvVisualizeBimFiler::create3DView(OdBmDatabase* pDb) const
{
  OdBmDBDrawingInfoPtr pDBDrawingInfo = pDb->getAppInfo(OdBm::ManagerType::DBDrawingInfo);
  OdBmUserParamIteratorPtr drawingIterator = pDBDrawingInfo->createIteratorDBDrawings(true);
  while (!drawingIterator->done())
  {
    OdBmObjectId bmObjectId = drawingIterator->object();
    OdBmDBDrawingPtr pDBDrawing = bmObjectId.openObject();

    if (pDBDrawing->getBaseViewNameFormat() == OdBm::ViewType::_3d)
      return;

    drawingIterator->next();
  }

  ODBM_TRANSACTION_BEGIN(tr, pDb)
  tr.start();

  OdBmDBView3dPtr pDBView3d = OdBmDBView3d::createObject();
  pDBView3d->setViewName(OD_T("{3D}"));

  // element must be added to DB before setDefaultOrigin, setPerspective
  OdBmObjectId newElemId = pDb->addElement(pDBView3d);

  OdResult result = pDBView3d->setDefaultOrigin();

  tr.commit();
  ODBM_TRANSACTION_END()
}

//***************************************************************************//
// 'OdTvBimPropertiesLoader' methods implementation
//***************************************************************************//

OdTvBimPropertiesLoader::OdTvBimPropertiesLoader()
{
}

OdTvBimPropertiesLoader::~OdTvBimPropertiesLoader()
{
}

void OdTvBimPropertiesLoader::setNativeDatabase(const OdDbBaseDatabase* nativeDb)
{
  m_bimDb = OdBmDatabase::cast(nativeDb);

  if (m_bimDb.isNull())
    throw OdError("Invalid native database, need OdBimDatabase");

  if (m_pLabelUtils.isNull())
    m_pLabelUtils = OdBmObject::desc()->getX(OdBmLabelUtilsPE::desc());
}

void OdTvBimPropertiesLoader::setNativeDatabase(const OdString& path)
{
  OdStaticRxObject<OdTvService> svcs;
  ::odrxDynamicLinker()->loadApp(OdBmLoaderModuleName, false);

  m_bimDb = svcs.readFile(path);
  if (m_bimDb.isNull())
    throw OdError("Error during reading the native database");

  if ( m_pLabelUtils.isNull() )
    m_pLabelUtils = OdBmObject::desc()->getX(OdBmLabelUtilsPE::desc());
}

OdTvObjectsPropertiesPtr OdTvBimPropertiesLoader::getAllProperties(const OdTvDatabaseId& dbId)
{
  if (dbId.isNull())
    throw OdError("OdTvDatabaseId is NULL");

  if (m_bimDb.isNull())
    return OdTvObjectsPropertiesPtr();

  if (m_pLabelUtils.isNull())
    return OdTvObjectsPropertiesPtr();

  OdTvObjectsPropertiesPtr res = new OdTvObjectsProperties();

  OdTvEntitiesIteratorPtr entitesItr;
  OdTvModelsIteratorPtr   modelItr = dbId.openObject()->getModelsIterator();

  OdTvEntityId      entity;
  OdTvEntityPtr     entityPtr;
  OdTvByteUserData* userData;
  OdUInt64          handle;

  OdString regAppName = L"ExGsVisualizeDevice";

  bool exits;
  OdTvRegAppId regId = dbId.openObject()->registerAppName(regAppName, exits);

  if (!exits)
    throw OdError("Not found OdTvRegAppId");

  for (; !modelItr->done(); modelItr->step()) {
    entitesItr = modelItr->getModel().openObject()->getEntitiesIterator();

    for (; !entitesItr->done(); entitesItr->step()) {

      entity = entitesItr->getEntity();
      if (entity.getType() == OdTvEntityId::kEntity) {

        entityPtr = entity.openObject();
        userData = static_cast<OdTvByteUserData*>(entityPtr->getUserData(regId));

        if (userData  && userData->getSize() == sizeof(OdUInt64)) {
          memcpy(&handle, userData->getData(), userData->getSize());
          if (res->find(handle) == res->end())
            (*res)[handle] = getProperties(handle);
        }
      }
    }
  }

  return res;
}

OdTvNativeProperties OdTvBimPropertiesLoader::getProperties(OdUInt64 handle)
{
  OdTvNativeProperties properties;

  if ( m_bimDb.isNull() )
    return properties;

  if ( m_pLabelUtils.isNull() )
    return properties;

  OdBmObjectId objId = m_bimDb->getObjectId(handle);
  OdBmElementPtr element = objId.safeOpenObject();

  if (element.isNull())
    return properties;

  OdTfVariant         value;
  OdBmParameterSet paramSet;
  element->getListParams(paramSet);

  OdString  name;
  OdString  params;
  OdDbStub* pStub;

  for (OdBm::BuiltInParameter::Enum param : paramSet.getBuiltInParamsIterator()) {
    name = m_pLabelUtils->getLabelFor(param);

    if (name.isEmpty()) {
      name = OdBm::BuiltInParameter(param).toString();
    }

    if (element->getParam(param, value) == eOk) {
      OdVariant::Type odType = value.type();

      switch (odType) {
      case OdVariant::kInt32: {
        params.format(OD_T("%d"), value.getInt32());
      } break;
      case OdVariant::kDouble: {
        params.format(OD_T("%.15f"), value.getDouble());
      } break;
      case OdVariant::kString: {
        params.format(value.getString().c_str());
      } break;
      default: {
        if (odType == OdTfVariant::kDbStubPtr) {
          pStub = value.getDbStubPtr();
          if (pStub)
          {
            OdBmObjectId rawValue = OdBmObjectId(pStub);
            if (param == OdBm::BuiltInParameter::ELEM_CATEGORY_PARAM ||
              param == OdBm::BuiltInParameter::ELEM_CATEGORY_PARAM_MT)
            {
              OdBm::BuiltInCategory::Enum builtInValue = static_cast<OdBm::BuiltInCategory::Enum>((OdUInt64)rawValue.getHandle());
              params.format(L"%ls", OdBm::BuiltInCategory(builtInValue).toString().c_str());
            }
            else
              params.format(OD_T("%d"), (OdUInt64)(rawValue.getHandle()));
          }
          else
            params.format(OD_T("-1"));
        }
      }
      }
    }
    else {
      params.format(L"None");
    }

    properties[name] = params;
  }

  return properties;
}


void OdTvVisualizeBimFiler::createCommonDataAccessTree(OdTvDatabasePtr pTvDb, OdDbBaseDatabase *pDatabase, const OdString& strTreeName) const
{
  m_moduleNameForCDA = m_properties->getUseAlternativeCDATree() ? OdString("TB_CDA3DViewTree") : OdString("TB_CDAProperties");
  
  ::odrxDynamicLinker()->loadModule(m_moduleNameForCDA);

  //Create CDA tree
  OdTvCDATreePtr pTree = OdTvCDATree::createObject();
  pTree->createDatabaseHierarchyTree(pDatabase, m_properties->getNeedCollectPropertiesInCDA());

  //Add tree to the Tv database
  OdTvResult rc;
  OdTvCDATreeStorageId cdaTreeId = pTvDb->addCDATreeStorage(strTreeName, pTree, &rc);
  if (rc == tvAlreadyExistSameName)
  {
    OdUInt32 i = 1;
    while (rc != tvOk && i < MAX_CDATREENAME_GENERATION_ATTEMPTS)
    {
      OdString str;
      str.format(L"%s_%d", strTreeName.c_str(), i++); //not to fast but it is not a "bottle neck"
      cdaTreeId = pTvDb->addCDATreeStorage(str, pTree, &rc);
    }
  }

  //Add new CDA tree to the appropriate models
  OdTvModelsIteratorPtr modelsIterPtr = pTvDb->getModelsIterator();
  while (!modelsIterPtr->done())
  {
    OdTvModelPtr pModel = modelsIterPtr->getModel().openObject();
    if (!pModel.isNull())
    {
      pModel->setCDATreeStorage(cdaTreeId);
    }
    modelsIterPtr->step();
  }

  //mark all nodes that it is not need group nodes
  OdRxModelTreeBaseNodePtr pDbNode = pTree->getDatabaseNode();
  if (!pDbNode.isNull())
    OdTvDatabaseUtils::markCDANode(pDbNode.get());
}

//***************************************************************************//
// 'OdTvVisualizeBimFilerModule' methods implementation
//***************************************************************************//

ODRX_DEFINE_DYNAMIC_MODULE(OdTvVisualizeBimFilerModule);

void OdTvVisualizeBimFilerModule::initApp()
{
  // initialize the Visualize SDK
  odTvInitialize();
}

void OdTvVisualizeBimFilerModule::uninitApp()
{
  // Uninitialize the Visualize SDK
  odTvUninitialize();
}

OdTvVisualizeFilerPtr OdTvVisualizeBimFilerModule::getVisualizeFiler() const
{
  OdTvVisualizeFilerPtr pBimFiler = new OdTvVisualizeBimFiler();

  return pBimFiler;
}

OdTvImportPropertiesLoaderPtr OdTvVisualizeBimFilerModule::getPropertiesLoader() const
{
  OdTvImportPropertiesLoaderPtr loader = new OdTvBimPropertiesLoader();
  return loader;
}
