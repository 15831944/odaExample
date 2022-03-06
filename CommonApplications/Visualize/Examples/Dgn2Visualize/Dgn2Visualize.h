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

#ifndef _TV_DGN2VISUALIZE_H_
#define _TV_DGN2VISUALIZE_H_

#include "TD_PackPush.h"
#include "RxDispatchImpl.h"

#include "RxObject.h"
#include "ExDgnHostAppServices.h"
#include "DgDatabase.h"

#include "DgGsManager.h"

#include "StaticRxObject.h"

#include "TvVisualizeFiler.h"
#include "RxSystemServices.h"


class OdTvVisualizeDgnFilerSourceFromFile;

namespace DGN2Visualize {
  /** \details
  This class implements the properties of the dgn loader
  */
  class OdTvVisualizeDgnFilerProperties : public OdRxDispatchImpl<>
  {
    enum ParamFlags
    {
      kObjectNaming = 1,                // Give the names for the tv entities according to the file objects name (like AcDbCircle etc). If object names exist
      kStoreSource = 2,                 // Store source objects (OdDbEntities)
      kClearEmptyObjects = 4,           // Clear empty objects
      kNeedCDATree = 8,                 // Need create CDA tree 
      kUseIsolinesFor3DObjects = 16,    // Use isolines for 3D objects
      kNeedCollectPropertiesInCDA = 32  // Need collect native properties in CDA nodes
    };

  public:
    OdTvVisualizeDgnFilerProperties();
    virtual ~OdTvVisualizeDgnFilerProperties();

    ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(OdTvVisualizeDgnFilerProperties);
    static OdRxDictionaryPtr createObject();

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

    void setNeedCDATree(bool bSet) { SETBIT(m_flags, kNeedCDATree, bSet); }
    bool getNeedCDATree() const { return GETBIT(m_flags, kNeedCDATree); }

    void setUseIsolinesFor3DObjects(bool bSet) { SETBIT(m_flags, kUseIsolinesFor3DObjects, bSet); }
    bool getUseIsolinesFor3DObjects() const { return GETBIT(m_flags, kUseIsolinesFor3DObjects); }

    void setFeedbackForChooseCallback(OdIntPtr pCallback);
    OdIntPtr getFeedbackForChooseCallback() const;

    void setNeedCollectPropertiesInCDA(bool bSet) { SETBIT(m_flags, kNeedCollectPropertiesInCDA, bSet); }
    bool getNeedCollectPropertiesInCDA() const { return GETBIT(m_flags, kNeedCollectPropertiesInCDA); }

    void      setAppendTransform(OdIntPtr pTransform);
    OdIntPtr  getAppendTransform() const;

    void      setDefaultUnits(OdInt16 units) { m_defaultUnits = units; }
    OdInt16   getDefaultUnits() const { return m_defaultUnits; }

  protected:

    const ODCOLORREF*              m_pPalette;               // Palette to be used. If NULL, one of two default palettes will be used depending on background color. Should have 256 colors
    OdTvDCRect                     m_importRect;             // Output rectangle. Used for correct import of some specific objects (OLE image, camera). The normal way is to set the output window size
    OdUInt8                        m_flags;                  // Different options
    OdTvFeedbackForChooseCallback  m_pCallback;              // Callback for choose
    OdTvMatrix                     m_appendTransform;        // Transform for the append
    OdInt16                        m_defaultUnits;           // default units
  };
  typedef OdSmartPtr<OdTvVisualizeDgnFilerProperties> OdTvVisualizeDgnFilerPropertiesPtr;
}

/** \details
This class is an interface for the internal helper objects used inside the import process
*/
class OdTvVisualizeDgnFilerDbSource
{
public:
  virtual ~OdTvVisualizeDgnFilerDbSource() {};
  virtual OdDgDatabasePtr   getDb() = 0;
  virtual OdString          getFilename() = 0;
  virtual double            getInitTime() const { return 0; }
  virtual bool              odWasInitialized() const { return true; }
};

/** \details
This class is dgn loader (to the Visualize database)
*/
class OdTvVisualizeDgnFiler : public OdTvVisualizeFiler
{
public:

  OdTvVisualizeDgnFiler();
  virtual ~OdTvVisualizeDgnFiler();

  virtual OdRxDictionaryPtr properties() { return m_properties; }
  virtual OdTvDatabaseId loadFrom(OdDbBaseDatabase *pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId loadFrom(OdStreamBuf        *pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId loadFrom(const OdString    &filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId generate(OdTvFilerTimeProfiling* pProfileRes = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase *pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf        *pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, const OdString    &filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;

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

  OdTvDatabaseId  loadFrom(OdTvVisualizeDgnFilerDbSource *pDgnDatabaseSource, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  OdTvModelId     appendFrom(const OdTvDatabaseId& databaseId, OdTvVisualizeDgnFilerDbSource *pDgnDatabaseSource, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  int             getActiveViewId(OdGsDeviceForDgModel* pLayoutHelper) const;
  OdTvGsDeviceId  getActiveTvDevice(OdTvDatabaseId& tvDbId, int idDevice) const;
  OdTvGsViewId    getActiveTvView(OdTvGsDeviceId& tvDeviceId, int iActViewViewInd) const;
  void getChoosedViews(OdDgViewGroupPtr pViewGroup, OdTvFilerFeedbackForChooseObject& filerFeedbackForChoose, bool& bCanceled) const;

  void createCommonDataAccessTree(OdTvDatabasePtr pTvDb, OdDbBaseDatabase *pDatabase, const OdString& strTreeName) const;

private:
  DGN2Visualize::OdTvVisualizeDgnFilerPropertiesPtr m_properties;

  OdRxModulePtr m_pDgPropertiesModule;
  OdRxModulePtr m_pRxPropertiesModule;
  OdRxModulePtr m_pDgDatabaseModule;
  OdTvVisualizeDgnFilerSourceFromFile* m_pDl;

  OdDgDatabasePtr m_pDatabaseForNativeProp;
};

/** \details
This class is dgn loader module implementation
*/
class OdTvVisualizeDgnFilerModule : public OdTvVisualizeFilerModule
{
public:
  virtual OdTvVisualizeFilerPtr getVisualizeFiler() const;

  void initApp();
  void uninitApp();
};

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
This class is service for getting database for dgn file
*/
class OdTvDgnService : public OdDgHostAppServices, public OdDbHostAppProgressMeter, public TvRxSystemServicesImpl
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

#endif
