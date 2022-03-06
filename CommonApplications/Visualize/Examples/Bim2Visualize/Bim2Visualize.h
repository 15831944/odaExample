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

#ifndef _TV_BIM2VISUALIZE_H_
#define _TV_BIM2VISUALIZE_H_

#include "TD_PackPush.h"

#include "RxDispatchImpl.h"
#include "RxObject.h"
#include "BimCommon.h"
#include "HatchPatternManager.h"

#include "Common/BmBuildSettings.h"
#include "Loader/BmHostAppServices.h"
#include "Base/BmObjectId.h"
#include "PE/BmLabelUtilsPE.h"
#include "Database/BmDatabase.h"

#include "TvFactory.h"
#include "TvVisualizeFiler.h"

namespace BIM2Visualize {
  /** \details
  This class implements the properties of the bim loader
  */
  class OdTvVisualizeBimFilerProperties : public OdRxDispatchImpl<>
  {
    enum ParamFlags
    {
      kObjectNaming = 1,                // Give the names for the tv entities according to the file objects name (like AcDbCircle etc). If object names exist
      kStoreSource = 2,                 // Store source objects (OdDbEntities)
      kThinLines = 4,                   // Use thin lines mode
      kClearEmptyObjects = 8,           // Clear empty objects
      kNeedCDATree = 16,                // Need create CDA tree
      kNeedCollectPropertiesInCDA = 32, // Need collect native properties in CDA nodes
      kIgnoreEdgesColors = 64,          // Ignore edge's colors
      kUseSilhouettes   = 128           // Use silhouettes
    };

  public:
    OdTvVisualizeBimFilerProperties();
    virtual ~OdTvVisualizeBimFilerProperties();

    ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(OdTvVisualizeBimFilerProperties);
    static OdRxDictionaryPtr createObject();

    void      setBackgroundColor(OdIntPtr pBackgroundColor);
    OdIntPtr  getBackgroundColor() const;


    void      setDCRect(OdIntPtr rect);   //should be pointer to OdTvDCRect
    OdIntPtr  getDCRect() const;

    void setObjectNaming(bool bSet) { SETBIT(m_flags, kObjectNaming, bSet); }
    bool getObjectNaming() const { return GETBIT(m_flags, kObjectNaming); }

    void setStoreSourceObjects(bool bSet) { SETBIT(m_flags, kStoreSource, bSet); }
    bool getStoreSourceObjects() const { return GETBIT(m_flags, kStoreSource); }

    void setThinLines(bool bSet) { SETBIT(m_flags, kThinLines, bSet); }
    bool getThinLines() const { return GETBIT(m_flags, kThinLines); }

    void setClearEmptyObjects(bool bSet) { SETBIT(m_flags, kClearEmptyObjects, bSet); }
    bool getClearEmptyObjects() const { return GETBIT(m_flags, kClearEmptyObjects); }

    void setFeedbackForChooseCallback(OdIntPtr pCallback);
    OdIntPtr getFeedbackForChooseCallback() const;

    void setFeedbackForWarningCallback(OdIntPtr pCallback);
    OdIntPtr getFeedbackForWarningCallback() const;

    void      setAppendTransform(OdIntPtr pTransform);
    OdIntPtr  getAppendTransform() const;

    void      setNeedCDATree(bool bSet) { SETBIT(m_flags, kNeedCDATree, bSet); }
    bool      getNeedCDATree() const { return GETBIT(m_flags, kNeedCDATree); }

    void      setNeedCollectPropertiesInCDA(bool bSet) { SETBIT(m_flags, kNeedCollectPropertiesInCDA, bSet); }
    bool      getNeedCollectPropertiesInCDA() const { return GETBIT(m_flags, kNeedCollectPropertiesInCDA); }

    void      setIgnoreEdgesColors(bool bSet) { SETBIT(m_flags, kIgnoreEdgesColors, bSet); }
    bool      getIgnoreEdgesColors() const { return GETBIT(m_flags, kIgnoreEdgesColors); }

    void      setUseSilhouettes(bool bSet) { SETBIT(m_flags, kUseSilhouettes, bSet); }
    bool      getUseSilhouettes() const { return GETBIT(m_flags, kUseSilhouettes); }

    void      setUseMTforViewsImport(bool bSet) { m_bUseMTforViewsImport = bSet; };
    bool      getUseMTforViewsImport() const { return m_bUseMTforViewsImport; };

    void      setViewsImportThreads(OdUInt64 nViewsImportThreads) { m_nViewsImportThreads = nViewsImportThreads; };
    OdUInt64  getViewsImportThreads() const { return m_nViewsImportThreads; };

    void      setCreate3DView(bool bCreate3DView) { m_bCreate3DView = bCreate3DView; };
    bool      getCreate3DView() const { return m_bCreate3DView; };

    void      setUseAlternativeCDATree(bool useAlternativeCDATree) { m_useAlternativeCDATree = useAlternativeCDATree; };
    bool      getUseAlternativeCDATree() const { return m_useAlternativeCDATree; };

  protected:
    ODCOLORREF                     m_background;             // Background color. Default: black
    OdTvDCRect                     m_importRect;             // Output rectangle. Used for correct import of some specific objects (OLE image, camera). The normal way is to set the output window size
    OdUInt8                        m_flags;                  // Different options
    OdTvFeedbackForChooseCallback  m_pCallback;              // Callback for views choosing
    OdTvFeedbackForWarningCallback m_pWarningCallback;       // Callback for warning
    OdTvMatrix                     m_appendTransform;        // Transform for the append
    bool                           m_bUseMTforViewsImport;   // Use multi thread vectorization
    OdUInt64                       m_nViewsImportThreads;    // Max number of vectorization threads
    bool                           m_bCreate3DView;          // Create 3D view if not exists
    bool                           m_useAlternativeCDATree;
  };
  typedef OdSmartPtr<OdTvVisualizeBimFilerProperties> OdTvVisualizeBimFilerPropertiesPtr;
}

class TvRxSystemServicesImpl : public OdRxSystemServices
{
public:
  TvRxSystemServicesImpl() {};

  OdInt64 getFileCTime(const OdString& filename) { return 0; };
  OdInt64 getFileMTime(const OdString& filename) { return 0; };
  OdInt64 getFileSize(const OdString& filename) { return 0; };

  OdString formatMessage(unsigned int formatId, va_list* argList = 0) { return OD_T(""); };

  /** \details
  Returns the system code page.

  \remarks
  On Windows platforms system code page is initialized based on computer's
  Regional Settings. On other platforms with CP_UNDEFINED.
  It can be altered by setSystemCodePage()
  */
  OdCodePageId systemCodePage() const { return CP_UNDEFINED; };

  OdResult getEnvVar(const OdString& varName, OdString& value)
  {
    return eNotImplemented;
  };

  OdResult setEnvVar(const OdString& varName, const OdString& newValue)
  {
    return eNotImplemented;
  };

};

/** \details
This class is service for getting database for dgn file
*/
class OdTvService : public OdBmLoaderHostAppServices, public TvRxSystemServicesImpl
{
public:
  virtual void start(const OdString& displayString = OdString::kEmpty) { };
  virtual void stop() { };
  virtual void meterProgress() { };
  virtual void setLimit(int max) { };

  virtual OdHatchPatternManager* patternManager() { return NULL; }
#if defined(ODA_WINDOWS)
  virtual OdString findFile(
    const OdString& filename,
    OdDbBaseDatabase* pDb = 0,
    FindFileHint hint = kDefault);
#endif
protected:
  ODRX_USING_HEAP_OPERATORS(TvRxSystemServicesImpl);

};


/** \details
This class is an interface for the internal helper objects used inside the import process
*/
class OdTvVisualizeBimFilerDbSource
{
public:
  virtual ~OdTvVisualizeBimFilerDbSource() {};
  virtual OdBmDatabasePtr   getDb() = 0;
  virtual OdString          getFilename() = 0;
  virtual double            getInitTime() const { return 0; }
  virtual bool              odWasInitialized() const { return true; }
  virtual bool              isFileValid(OdString& errStr)
  {
    if (!m_svcs.isFileVersionSupported(m_filePath, false))
    {
      errStr = OD_T("The version of file is not supported!");
      return false;
    }
    else if (!m_svcs.isFileVersionSupported(m_filePath))
    {
      errStr = OD_T("The file cannot be converted to the latest version! Many algorithms cannot work with unconverted data. Functionality is limited!");
      return false;
    }

    return true;
  }

protected:
  OdString m_filePath;
  OdStaticRxObject<OdTvService> m_svcs;
};


/** \details
This class is bim loader (to the Visualize database)
*/
class OdTvVisualizeBimFiler : public OdTvVisualizeFiler
{
public:
  OdTvVisualizeBimFiler();

  virtual OdRxDictionaryPtr properties() { return m_properties; }
  virtual OdTvDatabaseId loadFrom(OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId loadFrom(OdStreamBuf* pBuffer,        OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId loadFrom(const OdString& filePath,    OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId generate(OdTvFilerTimeProfiling* pProfileRes = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase*  pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf*       pBuffer,   OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, const OdString&    filePath,  OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;

  //Native properties support
  virtual bool                    hasNativePropertiesSupport() const { return true; }
  virtual OdTvResult              startActionsWithNativeProperties(const OdString& sFilePath, bool bIsPartial);
  virtual bool                    isActionsWithNativePropertiesStarted(const OdString& sFilePath);
  virtual OdTvResult              endActionsWithNativeProperties();
  virtual OdRxMemberIteratorPtr   getNativePropertiesIterator(OdUInt64 dbHandle, OdTvResult* rc = NULL);
  virtual OdRxValue               getNativePropertyValue(OdUInt64 dbHandle, const OdRxPropertyPtr& pProperty, bool* bReadOnly = NULL, OdTvResult* rc = NULL);
  virtual OdRxValueIteratorPtr    getNativeCollectionPropertyIterator(OdUInt64 dbHandle, const OdRxCollectionPropertyPtr& pCollectionProperty, bool* bReadOnly = NULL, OdTvResult* rc = NULL);
  virtual OdTvResult              setNativePropertyValue(OdUInt64 dbHandle, OdRxPropertyPtr& pProperty, const OdRxValue& value);
  virtual OdDbBaseDatabase*       getNativeDatabase(OdTvResult* rc = NULL) const;

private:
  OdTvDatabaseId loadFrom(OdTvVisualizeBimFilerDbSource *pBimDatabaseSource, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  OdTvDatabaseId loadFromMT(OdTvVisualizeBimFilerDbSource *pBimDatabaseSource, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdTvVisualizeBimFilerDbSource *pBimDatabaseSource, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;

  void           setupConnectionsBetweenTvViews(OdBmObjectId idDBDrawing, OdGsDevice* pDevice, OdTvGsDeviceId idTVDevice) const;
  void           resetViewsModelsNames(OdTvGsDeviceId idTVDevice) const;
  OdString       resetModelNameForAppend(OdTvGsDeviceId idTVDevice, const OdString& fileName, const std::set<OdTvModelId>& foreignModels) const;
  int            getViewId(OdGsDevice* pDevice, OdGsView* pView) const;
  void           applyClipping(OdTvGsViewPtr pTvView, OdGsView* pGsView, const OdGeMatrix3d& mDevToWorld, bool bIs3DView) const;
  void getChosenViews(OdBmDatabasePtr pDb, OdTvFilerFeedbackForChooseObject& filerFeedbackForChoose, bool& bCanceled) const;
  void           setupExVisualizeDeviceProp(OdRxDictionaryPtr& pProperties, const OdTvDatabaseId& tvDbId, bool bUseTimeProfiling,
                                            const OdString& modelName, const BIM2Visualize::OdTvVisualizeBimFilerPropertiesPtr& importProperties,
                                            OdTvGsDeviceId& tvDeviceIdForAppend, bool bIs3DView) const;

  bool checkFileVersion(OdTvVisualizeBimFilerDbSource* pBimFiler, OdTvResult* rc) const;

  void create3DView(OdBmDatabase* pBimDb) const;

private:
  void createCommonDataAccessTree(OdTvDatabasePtr pTvDb, OdDbBaseDatabase *pDatabase, const OdString& strTreeName) const;

  OdRxModulePtr m_pBmPropertiesModule;
  OdRxModulePtr m_pRxPropertiesModule;
  OdBmDatabasePtr m_pDatabaseForNativeProp;

  BIM2Visualize::OdTvVisualizeBimFilerPropertiesPtr m_properties;
  OdSharedPtr< OdTvVisualizeBimFilerDbSource > m_pFilerPtr;
  mutable OdString m_moduleNameForCDA;
};


/** \details
This class is an implementation of the BIM native properties loader
*/
class OdTvBimPropertiesLoader : public OdTvImportPropertiesLoader
{
public:

  OdTvBimPropertiesLoader();
  virtual ~OdTvBimPropertiesLoader();

  virtual void setNativeDatabase(const OdString& path);
  virtual void setNativeDatabase(const OdDbBaseDatabase* nativeDb);

  virtual OdTvObjectsPropertiesPtr getAllProperties(const OdTvDatabaseId& dbId);
  virtual OdTvNativeProperties     getProperties(OdUInt64 handle);

private:
  OdBmDatabasePtr     m_bimDb;
  OdBmLabelUtilsPEPtr m_pLabelUtils;
};


/** \details
This class is bim loader module implementation
*/
class OdTvVisualizeBimFilerModule : public OdTvVisualizeFilerModule
{
public:
  virtual OdTvVisualizeFilerPtr getVisualizeFiler() const;

  virtual OdTvImportPropertiesLoaderPtr getPropertiesLoader() const;

  void initApp();
  void uninitApp();
};

OdString correctName(const OdString& str);

#include "TD_PackPop.h"

#endif
