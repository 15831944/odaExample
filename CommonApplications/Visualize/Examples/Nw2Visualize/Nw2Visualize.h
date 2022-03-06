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


#ifndef NW2VISUALIZE_H
#define NW2VISUALIZE_H

#include "TD_PackPush.h"
#include "RxDispatchImpl.h"
#include "HatchPatternManager.h"

// Visualize SDK
#include "TvVisualizeFiler.h"

#include "NwHostAppServices.h"
#include "Animation.h"

namespace NW2Visualize
{
  /** \details
  This class implements the properties of the obj loader
  */
  class OdTvVisualizeNwFilerProperties : public OdRxDispatchImpl<>
  {
    enum ParamFlags
    {
      kNeedCDATree                = 0x1, // Need create CDA tree
      kNeedCollectPropertiesInCDA = 0x2, // Need collect native properties in CDA nodes
      kChangeToNwc                = 0x4, // is model is original with nwc or it replacing origin format file in nwf
      kStoreSource                = 0x8, // Store source objects (OdDbEntities)
      kImportCuttingPlanes        = 0x10,// Import cutting planes
      kImportGrid                 = 0x20 // Import grid
    };
  public:
    OdTvVisualizeNwFilerProperties();
    virtual ~OdTvVisualizeNwFilerProperties();

    ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(OdTvVisualizeNwFilerProperties);
    static OdRxDictionaryPtr createObject();

    void      setDCRect(OdIntPtr rect);   //should be pointer to OdTvDCRect
    OdIntPtr  getDCRect() const;

    void      setBackgroundColor(OdIntPtr pBackgroundColor);
    OdIntPtr  getBackgroundColor() const;

    void     setDefaultNwColor(OdIntPtr pDefColor);
    OdIntPtr getDefaultNwColor() const;

    void setNeedCDATree(bool bSet) { SETBIT(m_flags, kNeedCDATree, bSet); }
    bool getNeedCDATree() const { return GETBIT(m_flags, kNeedCDATree); }

    void setNeedCollectPropertiesInCDA(bool bSet) { SETBIT(m_flags, kNeedCollectPropertiesInCDA, bSet); }
    bool getNeedCollectPropertiesInCDA() const { return GETBIT(m_flags, kNeedCollectPropertiesInCDA); }

    void setReplaceByNwc(bool bSet) { SETBIT(m_flags, kChangeToNwc, bSet); }
    bool getReplaceByNwc() const { return GETBIT(m_flags, kChangeToNwc); }

    void      setAppendTransform(OdIntPtr pTransform);
    OdIntPtr  getAppendTransform() const;

    void      setDeviceToAppend(OdIntPtr pDevice);
    OdIntPtr  getDeviceToAppend() const;
    OdTvGsDeviceId getTvDeviceToAppend() const { return m_appendDevice; }

    void setStoreSourceObjects(bool bSet) { SETBIT(m_flags, kStoreSource, bSet); }
    bool getStoreSourceObjects() const { return GETBIT(m_flags, kStoreSource); }

    void setImportCuttingPlanes(bool bSet) { SETBIT(m_flags, kImportCuttingPlanes, bSet); }
    bool getImportCuttingPlanes() const { return GETBIT(m_flags, kImportCuttingPlanes); }

    void setFeedbackForChooseCallback(OdIntPtr pCallback);
    OdIntPtr getFeedbackForChooseCallback() const;

    void setImportGrid(bool bSet) { SETBIT(m_flags, kImportGrid, bSet); }
    bool getImportGrid() const { return GETBIT(m_flags, kImportGrid); }
  protected:

    OdTvDCRect                     m_importRect;     // Output rectangle. Used for correct import of some specific objects (OLE image, camera). The normal way is to set the output window size
    ODCOLORREF                     m_background;     // Background color.
    ODCOLORREF                     m_defaultColor;   // default color which is set to the entity
    OdUInt8                        m_flags;          // Different options
    OdTvMatrix                     m_appendTransform;// Transform for the append
    OdTvGsDeviceId                 m_appendDevice;   // Device that will receive appended data
    OdTvFeedbackForChooseCallback  m_pCallback;      // Callback for choose
  };
  typedef OdSmartPtr<OdTvVisualizeNwFilerProperties> OdTvVisualizeNwFilerPropertiesPtr;
}

class OdTvVisualizeNwFilerSourceFromFile;
class OdNwDatabase;
typedef OdSmartPtr<OdNwDatabase> OdNwDatabasePtr;
class OdNwObjectId;
typedef OdArray<OdNwObjectId, OdMemoryAllocator<OdNwObjectId> > OdNwObjectIdArray;

typedef std::map<OdNwObjectId, OdTvEntityId> mapNwObjectId2EntityIdType;
typedef std::map<OdNwObjectId, std::vector<OdTvEntityId> > mapNwObjId2TvIdsType;

/** \details
This class is an interface for the internal helper objects used inside the import process
*/
class OdTvVisualizeNwFilerDbSource
{
public:
  virtual ~OdTvVisualizeNwFilerDbSource() {};
  virtual OdNwDatabasePtr   getDb() = 0;
  virtual OdString          getFilename() = 0;
  virtual double            getInitTime() const { return 0; }
  virtual bool              odWasInitialized() const { return true; }
};

/** \details
This class is nwinterop loader (to the Visualize database)
*/
class OdTvVisualizeNwFiler : public OdTvVisualizeFiler
{
  OdTvMaterialId importMaterial(const OdTvDatabaseId& tvDbId, const OdNwObjectId& nwRealisticMtlId, const OdNwObjectId& nwShadedMtlId) const;

public:

  OdTvVisualizeNwFiler();

  virtual OdRxDictionaryPtr properties() { return m_properties; }
  virtual OdTvDatabaseId loadFrom(OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId loadFrom(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
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
  virtual OdTvResult              setNativePropertyValue(OdUInt64 dbHandle, OdRxPropertyPtr& pProperty, const OdRxValue& value);
  virtual OdDbBaseDatabase*       getNativeDatabase(OdTvResult* rc = NULL) const;

private:
  OdTvModelId appendFrom(const OdTvDatabaseId& databaseId, OdTvVisualizeNwFilerDbSource *pNwDatabaseSource, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;

  void setupGeometry(const OdNwObjectId& nwModelItemRootId, const OdTvModelId& tvModelId, OdPerfTimerBase* pTvTimer, double& nTotalTvTime, mapNwObjId2TvIdsType &nwId2TvIds) const;
  OdTvGsViewBackgroundId setupBackground(const OdNwObjectId& nwBackGroundId, OdTvDatabasePtr tvDb) const;
  OdTvGsViewId setupCurrentView(const OdNwObjectId& nwCurViewId, const OdTvGsDeviceId& tvDeviceId, const OdTvModelId& tvModelId, const OdTvGsViewBackgroundId& backgroundId) const;
  void setupLights(const OdTvModelId& tvModelId, const OdNwObjectIdArray& aNwLights) const;
  void setupGrid(OdNwDatabasePtr pNwDb, OdTvDatabaseId tvDbId, OdTvGsViewId viewId) const;
  void loadNwd(OdTvDatabaseId tvDbId, OdNwDatabasePtr pNwDb, OdTvFilerTimer &timing, OdTvFilerTimeProfiling* pProfileRes) const;
  void loadNwf(OdTvDatabaseId tvDbId, OdNwDatabasePtr pNwDb, OdTvFilerTimer &timing, OdTvFilerTimeProfiling* pProfileRes) const;

  void createCommonDataAccessTree(OdTvDatabasePtr pTvDb, OdDbBaseDatabase *pDatabase, const OdString& strTreeName, const OdTvModelId& modelId) const;

  struct LoadNwOptions
  {
    enum Type
    {
      kFilePath,
      kDatabase,
      kBuffer
    };

    OdString          m_filePath;
    OdDbBaseDatabase* m_pDatabase;
    OdStreamBuf*      m_pBuffer;
    Type              m_type;

    LoadNwOptions(const OdString& filePath) : m_filePath(filePath), m_type(kFilePath), m_pDatabase(NULL), m_pBuffer(NULL) {}
    LoadNwOptions(OdDbBaseDatabase* pDatabase) : m_pDatabase(pDatabase), m_type(kDatabase), m_pBuffer(NULL) {}
    LoadNwOptions(OdStreamBuf* pBuffer) : m_pBuffer(pBuffer), m_type(kBuffer), m_pDatabase(NULL) {}
  };

  OdTvDatabaseId importFile(const LoadNwOptions& opt, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;

private:
  NW2Visualize::OdTvVisualizeNwFilerPropertiesPtr   m_properties;

  OdRxModulePtr m_pNwPropertiesModule;
  OdRxModulePtr m_pRxPropertiesModule;
  OdRxModulePtr m_pNwDatabaseModule;
  OdTvVisualizeNwFilerSourceFromFile* m_pDl;

  OdNwDatabasePtr m_pDatabaseForNativeProp;
};


/** \details
This class is obj loader module implementation
*/
class OdTvVisualizeNwFilerModule : public OdTvVisualizeFilerModule
{
public:
  virtual OdTvVisualizeFilerPtr getVisualizeFiler() const;

  void initApp();
  void uninitApp();
};
typedef OdSmartPtr<OdTvVisualizeNwFilerModule> OdTvVisualizeNwFilerModulePtr;


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

  OdResult getEnvVar(const OdString &varName, OdString &value)
  {
    return eNotImplemented;
  };

  OdResult setEnvVar(const OdString &varName, const OdString &newValue)
  {
    return eNotImplemented;
  };
};

/** \details
This class is service for getting database for nw file
*/
class OdTvNw2VisService : public OdNwHostAppServices, public OdDbHostAppProgressMeter, public TvRxSystemServicesImpl
{
public:
  virtual void start(const OdString& displayString = OdString::kEmpty) { };
  virtual void stop() { };
  virtual void meterProgress() { };
  virtual void setLimit(int max) { };

  virtual OdHatchPatternManager* patternManager() { return NULL; }

protected:
  ODRX_USING_HEAP_OPERATORS(TvRxSystemServicesImpl);

};


#include "TD_PackPop.h"

#endif // NW2VISUALIZE_H

