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

#ifndef _TV_IFC2VISUALIZE_H_
#define _TV_IFC2VISUALIZE_H_


#include "TD_PackPush.h"

#include "RxDispatchImpl.h"
#include "RxObject.h"

#include "ExSystemServices.h"
#include "ExIfcHostAppServices.h"
#include "IfcCore.h"
#include "IfcModel.h"

#include "OdFileBuf.h"
#include "IfcGsManager.h"

#include "TvVisualizeFiler.h"
#include "../Extensions/ExVisualizeDevice/GsVisualizeVectorizer.h"

namespace IFC2Visualize {
  /** \details
  This class implements the properties of the ifc loader
  */
  class OdTvVisualizeIfcFilerProperties : public OdRxDispatchImpl<>
  {
    enum ParamFlags
    {
      kObjectNaming = 1,                // Give the names for the tv entities according to the file objects name (like AcDbCircle etc). If object names exist
      kStoreSource = 2,                 // Store source objects (OdDbEntities)
      kClearEmptyObjects = 4,           // Clear empty objects
      kRearrangeObjects = 8,            // Rearrange objects
      kNeedCDATree =      16,           // Need create CDA tree
      kNeedCollectPropertiesInCDA = 32, // Need collect native properties in CDA nodes
      kUseCustomBgColor = 64,           // Set custom backround color
      kIsLogOn = 128,                   // Enable logging
    };

  public:
    OdTvVisualizeIfcFilerProperties();
    virtual ~OdTvVisualizeIfcFilerProperties();

    ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(OdTvVisualizePrcFilerProperties);
    static OdRxDictionaryPtr createObject();

    void      setInterruptionCallback(OdIntPtr pInterrupt);
    OdIntPtr  getInterruptionCallback() const;

    void      setDefaultColor(OdIntPtr pDefColor);
    OdIntPtr  getDefaultColor() const;

    void      setBgColor(OdIntPtr pDefColor);
    OdIntPtr  getBgColor() const;

    void      setPalette(OdIntPtr palette); //palette should have 256 colors
    OdIntPtr  getPalette() const;

    void      setDCRect(OdIntPtr rect);   //should be pointer to OdTvDCRect
    OdIntPtr  getDCRect() const;

    void      setObjectNaming(bool bSet) { SETBIT(m_flags, kObjectNaming, bSet); }
    bool      getObjectNaming() const { return GETBIT(m_flags, kObjectNaming); }

    void      setStoreSourceObjects(bool bSet) { SETBIT(m_flags, kStoreSource, bSet); }
    bool      getStoreSourceObjects() const { return GETBIT(m_flags, kStoreSource); }

    void      setClearEmptyObjects(bool bSet) { SETBIT(m_flags, kClearEmptyObjects, bSet); }
    bool      getClearEmptyObjects() const { return GETBIT(m_flags, kClearEmptyObjects); }

    void      setRearrangeObjects(bool bSet) { SETBIT(m_flags, kRearrangeObjects, bSet); }
    bool      getRearrangeObjects() const { return GETBIT(m_flags, kRearrangeObjects); }

    void      setNeedCDATree(bool bSet) { SETBIT(m_flags, kNeedCDATree, bSet); }
    bool      getNeedCDATree() const { return GETBIT(m_flags, kNeedCDATree); }

    void      setNeedCollectPropertiesInCDA(bool bSet) { SETBIT(m_flags, kNeedCollectPropertiesInCDA, bSet); }
    bool      getNeedCollectPropertiesInCDA() const { return GETBIT(m_flags, kNeedCollectPropertiesInCDA); }

    void      setUseCustomBgColor(bool bSet) { SETBIT(m_flags, kUseCustomBgColor, bSet); }
    bool      getUseCustomBgColor() const { return GETBIT(m_flags, kUseCustomBgColor); }

    void      setIsLogOn(bool bSet) { SETBIT(m_flags, kIsLogOn, bSet); }
    bool      getIsLogOn() const { return GETBIT(m_flags, kIsLogOn); }

    void      setAppendTransform(OdIntPtr pTransform);
    OdIntPtr  getAppendTransform() const;

    void      setFeedbackForChooseCallback(OdIntPtr pCallback);
    OdIntPtr  getFeedbackForChooseCallback() const;

    void setDeviation(double deviation);
    double getDeviation() const;

    void setMinPerCircle(OdUInt16 minPerCircle);
    OdUInt16 getMinPerCircle() const;

    void setMaxPerCircle(OdUInt16 maxPerCircle);
    OdUInt16 getMaxPerCircle() const;

    void setModelerType(OdUInt8 type);
    OdUInt8 getModelerType() const;

    void      setHostAppProgressMeter(OdIntPtr pProgressMeter);
    OdIntPtr  getHostAppProgressMeter() const;

    void setMultithreadingEnable(bool isEnabled);
    bool getMultithreadingEnable() const;

    void setThreadsCount(OdInt16 countThreads);
    OdInt16 getThreadsCount() const;

    /** \details
    Sets a new value for 'use dictionary of TypePath' flag for hdf5 file.
    \param useDictionaryTypePath [in] A new value for 'use dictionary of TypePath' flag value.
    */
    void setUseDictionaryTypePath(bool useDictionaryTypePath);

    /** \details
    Retrieves the current 'use dictionary of TypePath' flag value for hdf5 file.
    \returns Returns the current value of the 'use dictionary of TypePath' flag.
    */
    bool getUseDictionaryTypePath() const;

    /** \details
    Sets a new value for 'store invese attributes' flag for hdf5 file.
    \param useDictionaryTypePath [in] A new value for 'store invese attributes' flag value.
    */
    void setStoreInveseAttributes(bool storeInveseAttributes);

    /** \details
    Retrieves the current 'store invese attributes' flag value for hdf5 file.
    \returns Returns the current value of the 'store invese attributes' flag.
    */
    bool getStoreInveseAttributes() const;

    /** \details
    Sets a new value of the deflate level for hdf5 file.
    \param deflateLevel [in] A new deflate level value.
    */
    void setDeflateLevel(OdUInt16 deflateLevel);

    /** \details
    Retrieves the current deflate level value for hdf5 file.
    \returns Returns the current value of the deflate level.
    */
    OdUInt16 getDeflateLevel() const;

    /** \details
    Sets a new value of the chunk size for read from hdf5 file.
    \param deflateLevel [in] A new chunk size value.
    */
    void setReadChunkSize(OdUInt32 readChunkSize);

    /** \details
    Retrieves the current chunk size value for read from hdf5 file.
    \returns Returns the current value of the chunk size.
    */
    OdUInt32 getReadChunkSize() const;

    /** \details
    Sets a new value of the chunk size for write to hdf5 file.
    \param deflateLevel [in] A new chunk size value.
    */
    void setWriteChunkSize(OdUInt32 writeChunkSize);

    /** \details
    Retrieves the current chunk size value for write to hdf5 file.
    \returns Returns the current value of the chunk size.
    */
    OdUInt32 getWriteChunkSize() const;

  protected:

    ODCOLORREF              m_defaultColor;                     // default color which is set to the entity
    ODCOLORREF              m_bgColor;                          // background color which is set to the scene
    const ODCOLORREF*       m_pPalette;                         // Palette to be used. If NULL, one of two default palettes will be used depending on background color. Should have 256 colors
    OdTvDCRect              m_importRect;                       // Output rectangle. Used for correct import of some specific objects (OLE image, camera). The normal way is to set the output window size
    OdUInt32                m_flags;                            // Different options
    OdTvMatrix              m_appendTransform;                  // Transform for the append
    OdTvFeedbackForChooseCallback  m_pCallback;                 // Callback for choose
    OdTvHostAppProgressMeter*      m_pHostAppProgressMeter;     // host app progress meter
    OdDAI::InterruptCallback       m_pInterruptCallback;               //interruption callback

    bool                    m_isMultithreadLoadEnabled;  // Ifc multithread loading enabled.
    OdUInt16                m_countedLoadedThreads;

    double                  m_deviation;
    OdUInt16                m_minPerCircle;
    OdUInt16                m_maxPerCircle;
    OdUInt8                 m_modelerType;

    bool                    m_useDictionaryTypePath; // Write dictionary of TypePath to hdf5 file
    bool                    m_storeInveseAttributes; // Write invese attributes to hdf5 file
    OdUInt16                m_deflateLevel; // Deflate level for hdf5 file
    OdUInt32                m_readChunkSize; // Chunk size for read from hdf5 file
    OdUInt32                m_writeChunkSize; // Chunk size for write to hdf5 file
  };
  typedef OdSmartPtr<OdTvVisualizeIfcFilerProperties> OdTvVisualizeIfcFilerPropertiesPtr;
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
This class is service for getting database for ifc file
*/
class OdTvIfc2VisService : public OdIfcHostAppServices, public OdDbHostAppProgressMeter, public TvRxSystemServicesImpl
{
public:
  OdTvIfc2VisService() { m_pMeter = NULL; }
  void setProgressMeter(OdDbHostAppProgressMeter* pMeter) { m_pMeter = pMeter; }
  virtual void start(const OdString& displayString = OdString::kEmpty) { if (m_pMeter) m_pMeter->start(displayString); };
  virtual void stop() { if (m_pMeter) m_pMeter->stop(); };
  virtual void meterProgress() { if (m_pMeter) m_pMeter->meterProgress(); };
  virtual void setLimit(int max) { if (m_pMeter) m_pMeter->setLimit(max); };

  virtual OdHatchPatternManager* patternManager() { return NULL; }

  virtual OdDbHostAppProgressMeter* newProgressMeter() { return m_pMeter; }

protected:
  ODRX_USING_HEAP_OPERATORS(TvRxSystemServicesImpl);
  OdDbHostAppProgressMeter* m_pMeter;
};

/** \details
This class wraps ifc system services used inside the import process
*/
class OdTvVisualizeIfcFilerDbSource
{
protected:
  OdStaticRxObject<OdTvIfc2VisService> m_svcs;

public:
  virtual OdIfcFilePtr readFile(const OdString &file);
};

/** \details
This class is ifc loader (to the Visualize database)
*/
class OdTvVisualizeIfcFiler : public OdTvVisualizeFiler
{
public:

  OdTvVisualizeIfcFiler();

  virtual OdRxDictionaryPtr properties() { return m_properties; }
  virtual OdTvDatabaseId loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId loadFrom(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId loadFrom(OdDbBaseDatabase*  pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId generate(OdTvFilerTimeProfiling* pProfileRes = NULL) const;
  virtual OdTvModelId appendFrom(const OdTvDatabaseId& databaseId, const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvModelId appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvModelId appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase*  pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;

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

  int getChoosedRepresentationContexts(OdIfcFilePtr pIfcFile, OdTvFilerFeedbackForChooseObject & filerFeedbackForChoose, bool& bCanceled, OdArray<OdIfc::OdIfcEntityType>& composedTypes) const;
  OdAnsiString getLog(OdDAI::SessionPtr& pSession, OdIfcFilePtr pFile) const;

protected:

  mutable OdDAIObjectIds m_selContexts;

  OdTvModelId import(OdTvDatabaseId &tvDbId, OdStreamBuf* pBuffer, OdIfcFilePtr pIfcFile, OdTvFilerTimeProfiling* pProfileRes /*= NULL*/, OdTvResult* rc /*= NULL*/) const;

private:

  OdTvGsDeviceId  getActiveTvDevice(OdTvDatabaseId& tvDbId, int idDevice) const;
  int             getActiveViewId(OdGsIfcLayoutHelper* pLayoutHelper) const;
  OdTvGsViewId    getActiveTvView(OdTvGsDeviceId& tvDeviceId, int iActViewViewInd) const;
  OdTvGsViewId    getActiveTvView(OdTvDatabaseId& dbId, int iActViewViewInd) const;

  void createCommonDataAccessTree(OdTvDatabasePtr pTvDb, OdDbBaseDatabase *pDatabase, const OdString& strTreeName, const OdTvModelId& modelId = OdTvModelId()) const;
  bool            processCDANode(OdRxModelTreeBaseNode* pNode, OdRxModelTreeBaseNode* pParentNode) const;
  OdString        getClassNameProperty(const OdArray<PropertyInfo>& nodeProperties) const;
  int             odSelectRepresentationContextsByDefault(OdIfcModelPtr pModel) const;

private:

  IFC2Visualize::OdTvVisualizeIfcFilerPropertiesPtr m_properties;

  OdIfcFilePtr m_pIfcFile;
  OdIfcModelPtr m_pIfcModel;
  OdRxModulePtr m_pRxPropertiesModule;
  OdRxModulePtr m_pIfcCoreModule;
  OdSharedPtr<OdTvVisualizeIfcFilerDbSource> m_pFilerPtr;
};

/** \details
This class is ifc loader module implementation
*/
class OdTvVisualizeIfcFilerModule : public OdTvVisualizeFilerModule
{
public:
  virtual OdTvVisualizeFilerPtr getVisualizeFiler() const;

  void initApp();
  void uninitApp();
};



class OdTvIfcPartialImportNotifier : public ExGsVisualizeDeviceNotifier
{
public:
  OdTvIfcPartialImportNotifier();
  virtual ~OdTvIfcPartialImportNotifier();

  //entities
  virtual void entityVectorizationDone(const OdTvEntityId& entityId);
  virtual void insertVectorizationDone(const OdTvEntityId& insertId);
  virtual void lightVectorizationDone(const OdTvEntityId& lightId) {}

  virtual void entityRemoved(const OdTvEntityId& entityId) {}
  virtual void insertRemoved(const OdTvEntityId& insertId) {}
  virtual void lightRemoved(const OdTvEntityId& insertId) {}

  //view
  virtual void viewCreated(const OdTvGsViewId& viewId) {}
  virtual void viewModified(const OdTvGsViewId& viewId) {}

  //Table records
  virtual void layerCreated(const OdTvLayerId& layerId) {}
  virtual void layerModified(const OdTvLayerId& layerId) {}

  virtual void materialCreated(const OdTvMaterialId& materialId) {}

  virtual void imageCreated(const OdTvRasterImageId& iamgeId) {}

  virtual void blockCreated(const OdTvBlockId& blockId) {}
  virtual void blockVectorizationBegin(const OdTvBlockId& blockId) {}
  virtual void blockVectorizationDone(const OdTvBlockId& blockId) {}

  virtual void linetypeCreated(const OdTvLinetypeId& linetypeId) {}

  virtual void textStyleCreated(const OdTvTextStyleId& textStyleId) {}

  //Models
  virtual void modelCreated(const OdTvModelId& modelId) {}
  virtual void modelActivated(const OdTvModelId& modelId) {}

  //update
  virtual void updateBegins() {}
  virtual void updateEnds() {}

  //Other
  void setEntitiesCount(OdUInt32 nCount);
  void setProgressMeter(OdDbHostAppProgressMeter* pMeter)
  {
    m_pMeter = pMeter;
  }

protected:
  OdUInt32 m_nEntitiesEstimation;
  OdUInt32 m_nCurrentObject;
  OdDbHostAppProgressMeter* m_pMeter;
};

#include "TD_PackPop.h"

#endif // _TV_IFC2VISUALIZE_H_
