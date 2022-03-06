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

#ifndef _TV_DWG2VISUALIZE_H_
#define _TV_DWG2VISUALIZE_H_

#include "TD_PackPush.h"
#include "RxDispatchImpl.h"

#include "RxObject.h"
#include "DbHostAppServices.h"
#include "HatchPatternManager.h"

#include "StaticRxObject.h"
#include "ExSystemServices.h"

#include "TvVisualizeFiler.h"

//SEA
#include "../Extensions/ExVisualizeDevice/GsVisualizeVectorizer.h"
#include "ExPageController.h"
#include "PartialImportNotifier.h"

//#define OD_TV_MEASURE_PARTIAL

namespace DWG2Visualize {
  /** \details
  This class implements the properties of the dwg loader
  */
  class OdTvVisualizeDwgFilerProperties : public OdRxDispatchImpl<>
  {
    enum ParamFlags
    {
      kObjectNaming = 1,                  // Give the names for the tv entities according to the file objects name (like AcDbCircle etc). If object names exist
      kStoreSource = 2,                   // Store source objects (OdDbEntities)
      kClearEmptyObjects = 4,             // Clear empty objects
      kMultithreading = 8,                // Enable/Disable multithreading
      kUseAdvancedTess = 16,              // Using facet res
      kPartialOpen = 32,                  // Open source .dwg file in partial mode
      kLowMemoryImportToVSF = 64,         // Use per-object import to VSF mechanism (in this mode the result of loadFrom will not the database but the VSF file)
      kImportBrepAsBrep     = 128,        // import brep as OdTvBrepData
      kConvertIndexedToRGB  = 256,        // Converted indexed colors to RGB during import
      kNeedCDATree = 512,                 // Need create CDA tree
      kNeedCollectPropertiesInCDA = 1024, // Need collect native properties in CDA nodes
      kDisableFontSubstitution = 2048,    // Disable font substitution for missed fonts
      kImportFrozenLayers = 4096          // Import objects on frozen layer
    };

  public:
    OdTvVisualizeDwgFilerProperties();
    virtual ~OdTvVisualizeDwgFilerProperties();

    ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(OdTvVisualizeDwgFilerProperties);
    static OdRxDictionaryPtr createObject();

    void      setBackgroundColor(OdIntPtr pBackgroundColor);
    OdIntPtr  getBackgroundColor() const;

    void      setPalette(OdIntPtr palette); //palette should have 256 colors
    OdIntPtr  getPalette() const;

    void      setDCRect(OdIntPtr rect);   //should be pointer to OdTvDCRect
    OdIntPtr  getDCRect() const;

    void setObjectNaming(bool bSet) { SETBIT(m_flags, kObjectNaming, bSet); }
    bool getObjectNaming() const { return GETBIT(m_flags, kObjectNaming); }

    void setStoreSourceObjects(bool bSet) { SETBIT(m_flags, kStoreSource, bSet); }
    bool getStoreSourceObjects() const { return GETBIT(m_flags, kStoreSource); }

    void setClearEmptyObjects(bool bSet) { SETBIT(m_flags, kClearEmptyObjects, bSet); }
    bool getClearEmptyObjects() const { return GETBIT(m_flags, kClearEmptyObjects); }

    void setMultithreading(bool bSet) { SETBIT(m_flags, kMultithreading, bSet); }
    bool getMultithreading() const { return GETBIT(m_flags, kMultithreading); }

    void setCountOfThreads(OdUInt16 nThreads);
    OdUInt16 getCountOfThreads() const;

    void setFeedbackForChooseCallback(OdIntPtr pCallback);
    OdIntPtr getFeedbackForChooseCallback() const;

    void      setUseAdvancedTess(bool bSet) { SETBIT(m_flags, kUseAdvancedTess, bSet); }
    bool      getUseAdvancedTess() const { return GETBIT(m_flags, kUseAdvancedTess); }

    void      setFacetRes(double dFacetRes);
    double    getFacetRes() const;

    void      setAppendTransform(OdIntPtr pTransform);
    OdIntPtr  getAppendTransform() const;

    void      setPartialOpen( bool b ) { SETBIT( m_flags, kPartialOpen, b ); }
    bool      getPartialOpen() const { return GETBIT( m_flags, kPartialOpen ); }

    void      setLowMemoryImportToVSF(bool b) { SETBIT(m_flags, kLowMemoryImportToVSF, b); }
    bool      getLowMemoryImportToVSF() const { return GETBIT(m_flags, kLowMemoryImportToVSF); }

    void      setPartialImportDumpFile(const OdString& str) { m_strPartialImportDumpFile = str; }
    OdString  getPartialImportDumpFile() const { return m_strPartialImportDumpFile; }

    void      setImportBrepAsBrep(bool b) { SETBIT(m_flags, kImportBrepAsBrep, b); }
    bool      getImportBrepAsBrep() const { return GETBIT(m_flags, kImportBrepAsBrep); }

    void      setConvertIndexedToRGB(bool b) { SETBIT(m_flags, kConvertIndexedToRGB, b); }
    bool      getConvertIndexedToRGB() const { return GETBIT(m_flags, kConvertIndexedToRGB); }

    void      setNeedCDATree(bool bSet) { SETBIT(m_flags, kNeedCDATree, bSet); }
    bool      getNeedCDATree() const { return GETBIT(m_flags, kNeedCDATree); }

    void      setNeedCollectPropertiesInCDA(bool bSet) { SETBIT(m_flags, kNeedCollectPropertiesInCDA, bSet); }
    bool      getNeedCollectPropertiesInCDA() const { return GETBIT(m_flags, kNeedCollectPropertiesInCDA); }

    void      setHostAppProgressMeter(OdIntPtr pProgressMeter);
    OdIntPtr  getHostAppProgressMeter() const;

    void      setLowMemoryImportAbort(OdIntPtr pAbort);
    OdIntPtr  getLowMemoryImportAbort() const;

    void      setLowMemoryImportVSFCompression(OdIntPtr pOptions);
    OdIntPtr  getLowMemoryImportVSFCompression() const;

    void      setDisableFontSubstitution( bool bSet ) { SETBIT( m_flags, kDisableFontSubstitution, bSet ); }
    bool      getDisableFontSubstitution() const      { return GETBIT( m_flags, kDisableFontSubstitution ); }

    void      setImportFrozenLayers(bool bSet) { SETBIT(m_flags, kImportFrozenLayers, bSet); };
    bool      getImportFrozenLayers() const { return GETBIT(m_flags, kImportFrozenLayers); };

    void      setDefaultUnits(OdInt16 units) { m_defaultUnits = units; }
    OdInt16   getDefaultUnits() const { return m_defaultUnits; }

  protected:

    ODCOLORREF                     m_background;        // Background color. Default: black
    const ODCOLORREF*              m_pPalette;          // Palette to be used. If NULL, one of two default palettes will be used depending on background color. Should have 256 colors
    OdTvDCRect                     m_importRect;        // Output rectangle. Used for correct import of some specific objects (OLE image, camera). The normal way is to set the output window size
    OdUInt16                       m_flags;             // Different options
    OdUInt16                       m_nThreads;          // Count of threads
    OdTvFeedbackForChooseCallback  m_pCallback;         // Callback for choose
    double                         m_dFACETRES;         // Facet res value (between from 0.01 to 10.0)
    OdTvMatrix                     m_appendTransform;   // Transform for the append
    OdString                       m_strPartialImportDumpFile; // output VSF file name (used only in low memory import mode)
    OdTvHostAppProgressMeter*      m_pHostAppProgressMeter;    // host app progress meter (used only in low memory import mode)
    OdTvLowMemoryImportAbort*      m_pLowMemoryImportAbort;    // callback for giving ability to abort the low memory process
    OdTvVSFExportOptions           m_VSFCompressOptions;       // options for VSF file compression during low memory process
    OdInt16                        m_defaultUnits;      // default units
  };
  typedef OdSmartPtr<OdTvVisualizeDwgFilerProperties> OdTvVisualizeDwgFilerPropertiesPtr;
}


/** \details
This class is an interface for the internal helper objects used inside the import process 
*/
class OdTvVisualizeDwgFilerDbSource
{
public:
  virtual ~OdTvVisualizeDwgFilerDbSource() {};
  virtual OdDbDatabasePtr   getDb() = 0;
  virtual OdString          getFilename() = 0;
  virtual double            getInitTime() const { return 0; }
  virtual bool              odWasInitialized() const { return true; }
  virtual bool              isPartialOpen() const{ return false; }

  virtual OdDbHostAppProgressMeter* progressMeter() { return NULL; }
};


/** \details
This class is dwg loader (to the Visualize database)
*/
class OdTvVisualizeDwgFiler : public OdTvVisualizeFiler
{
public:

  OdTvVisualizeDwgFiler();
  virtual OdRxDictionaryPtr properties() { return m_properties; }
  virtual OdTvDatabaseId loadFrom(OdDbBaseDatabase*   pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId loadFrom(OdStreamBuf*        pBuffer,   OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId loadFrom(const OdString&     filePath,  OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId generate(OdTvFilerTimeProfiling* pProfileRes = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase*  pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf*       pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, const OdString&    filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;

  //Native properties support
  virtual bool                    hasNativePropertiesSupport() const { return true; }
  virtual OdTvResult              startActionsWithNativeProperties(const OdString& sFilePath, bool bPartial);
  virtual bool                    isActionsWithNativePropertiesStarted(const OdString& sFilePath);
  virtual OdTvResult              endActionsWithNativeProperties();
  virtual OdRxMemberIteratorPtr   getNativePropertiesIterator(OdUInt64 dbHandle, OdTvResult* rc = NULL);
  virtual OdRxValue               getNativePropertyValue(OdUInt64 dbHandle, const OdRxPropertyPtr& pProperty, bool* bReadOnly = NULL, OdTvResult* rc = NULL);
  virtual OdRxValueIteratorPtr    getNativeCollectionPropertyIterator(OdUInt64 dbHandle, const OdRxCollectionPropertyPtr& pCollectionProperty, bool* bReadOnly = NULL, OdTvResult* rc = NULL);
  virtual OdTvResult              setNativePropertyValue(OdUInt64 dbHandle,       OdRxPropertyPtr& pProperty, const OdRxValue& value);
  virtual OdDbBaseDatabase*       getNativeDatabase(OdTvResult* rc = NULL) const;

private:


  OdTvDatabaseId loadFrom(OdTvVisualizeDwgFilerDbSource *pDwgDatabaseSource, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;

  OdTvDatabaseId partialLoadFrom(OdTvVisualizeDwgFilerDbSource *pDwgDatabaseSource, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdTvVisualizeDwgFilerDbSource *pDwgDatabaseSource, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  void           setupTvViews(OdDbObjectId layoutId, OdGsLayoutHelper* pLayoutHelper, OdTvGsDeviceId idTVDevice, const ODCOLORREF& borderColor, OdString* pNewModelName = NULL) const;
  int            getActiveViewId(OdGsLayoutHelper* pLayoutHelper, int& iPaperViewId) const;
  void           setViewBorderProperties(OdGsDevice* pDevice, const ODCOLORREF& color) const;
  int getChoosedSpaces(const OdDbDatabasePtr pDbDatabase, OdTvFilerFeedbackForChooseObject& filerFeedbackForChoose, bool& bCanceled) const;
  void           setViewAndModelNames(const OdTvGsViewId& viewId, const OdString& deviceName, const OdGsClientViewInfo& viewInfo, OdString* pNewModelName = NULL) const;
  void           setViewportConfiguration(const OdTvGsViewId& viewId, const OdTvGsViewId& activeViewId, OdGsLayoutHelperPtr pLayoutHelper, int iActViewInd, int ind) const;
  void           setupExVisualizeDeviceProp(OdRxDictionaryPtr& pProperties, const OdTvDatabaseId& tvDbId, bool bUseTimeProfiling,
                                            const OdString& modelSpaceName, const OdString& strDwgPath, const DWG2Visualize::OdTvVisualizeDwgFilerPropertiesPtr& importProperties,
                                            const ExGsVisualizeDeviceCache& deviceCache, OdTvGsDeviceId& tvDeviceIdForAppend, bool bHavePaperSpace) const;
  void createCommonDataAccessTree(OdTvDatabasePtr pTvDb, OdDbDatabase *pDatabase, const OdString& strTreeName, const std::set<OdString>& spaces) const;
  OdTvRegAppId setLayoutUserData(OdTvGsDeviceId tvDeviceId, OdDbObjectId layoutId, OdTvDatabaseId databaseId) const;
  void changeFrozenLayersToHidden(const OdDbDatabasePtr& pDb);
  void setFrozenLayersTotallyInvisible(const ExGsVisualizeDeviceCache* pDeviceCache);
private:
  DWG2Visualize::OdTvVisualizeDwgFilerPropertiesPtr m_properties;

  OdRxModulePtr m_pDbPropertiesModule;
  OdRxModulePtr m_pRxPropertiesModule;
  OdDbDatabasePtr m_pDatabaseForNativeProp;
  OdSharedPtr<OdTvVisualizeDwgFilerDbSource> m_pSourceOfDatabaseForNativeProp;    //we need to store it for having services valid all the time between startActions/endActions

  std::map<OdDbObjectId, OdTvGsViewId> m_viewportMap;
  mutable OdDbObjectId m_paperViewportId;

  OdArray<OdDbStub*> m_frozenLayers;
};


/** \details
This class is dwg loader module implementation
*/
class OdTvVisualizeDwgFilerModule : public OdTvVisualizeFilerModule
{
public:
  virtual OdTvVisualizeFilerPtr getVisualizeFiler() const;

  void initApp();
  void uninitApp();
};

/** \details
This class is service for getting database for dwg file
*/
class OdTvDwgService : public RxSystemServicesImpl, public OdDbHostAppServices2, public OdDbHostAppProgressMeter
{
  int m_pagingType;
  OdTvHostAppProgressMeter* m_pProgressMeter;
  bool m_bDisableFontSubstitution;

  OdHatchPatternManagerPtr m_patternManager;
public:
  OdTvDwgService()
  {
    m_pagingType = 0;
    m_pProgressMeter = 0;
    m_bDisableFontSubstitution = false;
  }

  void setHostAppProgressMeter(OdTvHostAppProgressMeter* pMeter)
  {
    m_pProgressMeter = pMeter;
  }

  virtual void start(const OdString& displayString = OdString::kEmpty)
  {
    if (m_pProgressMeter)
      m_pProgressMeter->start(displayString);
  }
  virtual void stop()
  {
    if (m_pProgressMeter)
      m_pProgressMeter->stop();
  }
  virtual void meterProgress() 
  {
    if (m_pProgressMeter)
      m_pProgressMeter->meterProgress();
  }
  virtual void setLimit(int max)
  {
    if (m_pProgressMeter)
      m_pProgressMeter->setLimit(max);
  }

  virtual OdHatchPatternManager* patternManager()
  { 
    if (m_patternManager.isNull())
    {
      // dna: use odrxSafeCreateObject() for no linking to TD_DbFull
      m_patternManager = odrxSafeCreateObject<OdHatchPatternManager>("OdHatchPatternManager", OdDbEntitiesAppName);
      m_patternManager->setApplicationService(this);
    }
    return m_patternManager.get();
  }

  virtual OdDbPageControllerPtr newPageController() 
  {
    switch (m_pagingType)
    {
    case 1: //OdDb::kUnload
      // Simple unloading of objects for partially loaded database.
      return OdRxObjectImpl<ExUnloadController>::createObject();
    case 2: //OdDb::kPage
    case 3: //OdDb::kUnload | OdDb::kPage
      // Unloading of objects for partially loaded database and paging of objects thru ExPageController.
      return OdRxObjectImpl<ExPageController>::createObject();
    }
    // Paging is not used.
    return OdDbPageControllerPtr();
  }

  int setPagingType(int pagingType) 
  { 
    int oldType = m_pagingType;  
    m_pagingType = pagingType; 
    return oldType; 
  }

  bool getDisableFontSubstitution() const { return m_bDisableFontSubstitution; }

  void setDisableFontSubstitution( bool bSet ) { m_bDisableFontSubstitution = bSet; }

  virtual OdString findFile(
    const OdString& filename,
    OdDbBaseDatabase* pDb = 0,
    FindFileHint hint = kDefault )
  {
    if (m_bDisableFontSubstitution && (hint == kFontFile ||
      hint == kCompiledShapeFile || hint == kTrueTypeFontFile))
    {
      // 1. Check file name itself as full path
      OdDbSystemServices* pSs = odSystemServices();
      if (pSs->accessFile(filename, Oda::kFileRead))
        return filename;

      if (!pDb)
        return OdString();

      // 2. Check around database
      OdString sFilenameFromAttr = filename;
      sFilenameFromAttr.replace('\\', '/');
      int iSlashPos = sFilenameFromAttr.reverseFind(L'/');
      if (iSlashPos != -1)
        sFilenameFromAttr = sFilenameFromAttr.right(sFilenameFromAttr.getAllocLength() - iSlashPos - 1);

      OdString sDatabaseFileName = OdDbBaseDatabasePEPtr(pDb)->getFilename(pDb);
      sDatabaseFileName.replace('\\', '/');
      iSlashPos = sDatabaseFileName.reverseFind(L'/');
      if (iSlashPos == -1)
        return OdString();

      OdString sFontFile = sDatabaseFileName.left(iSlashPos + 1);
      sFontFile += sFilenameFromAttr;
      if (pSs->accessFile(sFontFile, Oda::kFileRead))
        return sFontFile;

      return OdString();
    }
    return OdDbHostAppServices2::findFile( filename, pDb, hint );
  }

  virtual OdString getSubstituteFont(
    const OdString& fontName,
    OdFontType fontType )
  {
    if( m_bDisableFontSubstitution )
      return OdString();
    return OdDbHostAppServices2::getSubstituteFont( fontName, fontType );
  }

  virtual OdString getSubstituteFontByChar(
    const OdFont& pFont,
    OdChar unicodeChar, OdDbBaseDatabase* pDb )
  {
    if( m_bDisableFontSubstitution )
      return OdString();
    return OdDbHostAppServices2::getSubstituteFontByChar( pFont, unicodeChar, pDb );
  }
};

bool addTvPaperDrawingCustomization();
void removeTvPaperDrawingCustomization();
void writeNativeDbDataAsUserData(const OdTvDatabaseId& dbId, OdDbDatabasePtr pNativeDb);

#include "TD_PackPop.h"

#endif
