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
//   This application incorporates Open Design Alliance software pursuant to a
//   license agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance.
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "CloudLibTools.h"
#include "OdaCommon.h"
#include "ExEdBaseIO.h"
#include <vector>
#include "RxVariant.h"
#include "ExDbCommandContext.h"
#include "OdaCommon.h"
#include "OdStreamOutput.h"
#include "OdStreamContext.h"
#include "OdNativePropertiesManager.h"
#include "GsVisualizeVectorizer.h"
#include "IStreamOutput.hpp"

namespace OdWeb {
  using namespace std;

  CLOUD_CMDCTX_EXPORT class NativeHandleEntityStoreImpl : public INativeHandleEntityStore {
  public:
    virtual bool getByNativeHandle(OdDbHandle handle, OdTvEntityId& entityId) override {
      auto itr = m_tree.find(handle);
      const auto isFind = itr != m_tree.end();

      if (isFind) {
        entityId = itr->second;
      }

      return isFind;
    }

    virtual bool bind(OdDbHandle handle, OdTvEntityId entityId) override {
      m_tree.insert(std::make_pair(handle, entityId));
      return true;
    }

    virtual void remove(OdDbHandle handle) override {
      m_tree.erase(handle);
    }

  private:
    std::map<OdDbHandle, OdTvEntityId> m_tree;
  };


  /**
    Impl OdEdBaseIO for cloud
  */
  class CLOUD_CMDCTX_EXPORT TBaseIO : public OdEdBaseIO {
  public:
    /*
      Return answer
    */
    vector<string> getAnswer();

    /*
      Initialize set data as string vector
    */
    void init(const vector<string>& args);

    /*
      Return command argument
    */
    virtual OdString getString
    (
      const OdString& prompt,
      int options = OdEd::kInpDefault,
      OdEdStringTracker* pTracker = 0
    ) override;

    /*
      Add string to answer
    */
    virtual void putString(const OdString& string) override;

    OdVariant getVariant();

  protected:
      int              m_current;
      vector<OdString> m_args;
      vector<string>   m_answer;
  };
  /*
    Entry for all stream data
  */
  class CLOUD_CMDCTX_EXPORT CloudStreamEntry : public IStreamOutput {
  public: 
    CloudStreamEntry() {}
    /*
      Destroy stream context
    */
    void release() {
      m_context.release();
    }
    
    /*
      Get stream context settings
    */
    OdStreamContextSettings getSettings() {
      if (m_context.isNull()) {
        return m_settings;
      }
      return m_context->getSettings();
    }

    /*
      Set stream context settings
    */
    void setSettings(const OdStreamContextSettings& settings) {
       m_settings = settings;
       if (!m_context.isNull()) {
         m_context->setSettings(settings);
       }
    }

    /*
      Get stream context
    */
    OdStreamContextPtr getContext() {
      if (m_context.isNull()) {
        m_context = OdStreamContext::create();
        m_context->setSettings(m_settings);
      }
      return m_context;
    }

    virtual void orderModify(const OdTvModelId& modelId, const OdArray<OdTvEntityId>& entitiesArray, Order direction) override {
      getContext()->orderModify(modelId, entitiesArray, direction);
    }
  private:

    OdStreamContextPtr m_context;

    OdStreamContextSettings m_settings;
  };

  /*
    Impl ExGsVisualizeDeviceNotifier for handle update visualize database
  */
  class CLOUD_CMDCTX_EXPORT OdNativeEditNotifier : public ExGsVisualizeDeviceNotifier {
  public:
    OdNativeEditNotifier(OdStreamContextPtr dataManager) {
      m_dataManager = dataManager;
    }

    ~OdNativeEditNotifier() {
      if (m_pStore) {
        delete m_pStore;
      }
    }

    virtual void entityVectorizationDone(const OdTvEntityId& entityId) override;


    virtual void insertVectorizationDone(const OdTvEntityId& insertId) override;


    virtual void lightVectorizationDone(const OdTvEntityId& lightId) override;


    virtual void entityRemoved(const OdTvEntityId& entityId) override;


    virtual void insertRemoved(const OdTvEntityId& insertId) override;


    virtual void lightRemoved(const OdTvEntityId& insertId) override;


    virtual void viewCreated(const OdTvGsViewId& viewId) override;


    virtual void viewModified(const OdTvGsViewId& viewId) override;


    virtual void layerCreated(const OdTvLayerId& layerId) override;


    virtual void layerModified(const OdTvLayerId& layerId) override;


    virtual void materialCreated(const OdTvMaterialId& materialId) override;


    virtual void imageCreated(const OdTvRasterImageId& iamgeId) override;


    virtual void blockCreated(const OdTvBlockId& blockId) override;


    virtual void blockVectorizationBegin(const OdTvBlockId& blockId) override;


    virtual void blockVectorizationDone(const OdTvBlockId& blockId) override;


    virtual void linetypeCreated(const OdTvLinetypeId& linetypeId) override;


    virtual void textStyleCreated(const OdTvTextStyleId& textStyleId) override;


    virtual void modelCreated(const OdTvModelId& modelId) override;


    virtual void modelActivated(const OdTvModelId& modelId) override;


    virtual void updateBegins() override;


    virtual void updateEnds() override;

    void setNativeHandleEntityStore(INativeHandleEntityStore* pStore) {
      m_pStore = pStore;
    }

  protected:
    void sendAdd(const OdTvDbObjectId& idRoot);

    void sendErase(const OdUInt64& handle);

  private:
    OdStreamContextPtr m_dataManager;
    OdStreamBufPtr m_buffer;
    INativeHandleEntityStore* m_pStore;
  };

  typedef OdSharedPtr<OdNativeEditNotifier> CloudnativeEditNotifierPtr;

  /*
    Entry for save information about native format
  */
  class CLOUD_CMDCTX_EXPORT OdNativeDbEntry {
  public:
    ~OdNativeDbEntry() {
    }

    void release() {
      if (!m_notifier.isNull()) {
        m_notifier.detach();
      }
    }
    /*
      Initialize, save native database and device attach to this db
    */
    void initialize(OdRxObject* pDb, OdGsDevice* pDevice) {
      m_pDb     = pDb;
      m_pDevice = pDevice;
    }

    /*
      Set notifier for get all changes
    */
    void setNotifier(CloudnativeEditNotifierPtr pNotifier) {
      m_notifier = pNotifier;
      OdRxDictionaryPtr pProperties = m_pDevice->properties();
      if (pProperties->has(OD_T("DeviceNotifier")))
        pProperties->putAt(OD_T("DeviceNotifier"), OdRxVariantValue((OdIntPtr)(m_notifier.get())));
    }

    /*
      Get native database
    */
    template<class DatabaseCLass>
    DatabaseCLass* getDatabase() { return static_cast<DatabaseCLass*>(m_pDb); }

    /*
      Update device, need call after edit native database
    */
    void update() {
      if (m_pDevice != nullptr) {
        m_pDevice->invalidate();
        m_pDevice->update();
      }
    }
  private:
    OdRxObject*              m_pDb;
    OdGsDevice*              m_pDevice;
    CloudnativeEditNotifierPtr m_notifier;
  };

  typedef OdSharedPtr<OdNativeDbEntry> CloudNativeDbEntryPtr;
  /*
  Command context for work with visualize database
  */
  class CLOUD_CMDCTX_EXPORT OdCommandContext : public ExDbCommandContext {
  public:
    ODRX_USING_HEAP_OPERATORS(ExDbCommandContext);
    /*
      Cast OdEdCommandContext to TeighaVisualizeCommandContext
    */
    static OdCommandContext* cast(OdEdCommandContext* ctx);

    OdCommandContext();

    ~OdCommandContext();

    /*
      Create DBRuntimeIO 
    */
    void createController();

    /*
      Get DBRuntimeIO controller
    */
    OdTvDbRtFilerControllerPtr getController();

    /*
      Set new TBaseIO
    */
    void setBaseIo(TBaseIO *io);

    /*
      Set visualize database id
    */
    void setDatabase(const OdTvDatabaseId& db_id);

    /*
      Get visualize database id 
    */
    OdTvDatabaseId getDatabase();

    /*
      Reset context and initialize for support ExDbCommandContext
    */
    virtual void reset(OdEdBaseIO* io, OdRxObject* base_db) override;

    /*
      Get current TBaseIO
    */
    TBaseIO* getIo();

    /*
      Get currant stream entry
    */
    CloudStreamEntry& getStreamEntry();

    /*
      Get stream output for send graphics data
    */
    OdStreamOutputPtr getStreamOutput();

    /*
      set current stream output 
    */
    void setStreamOutput(OdStreamOutputPtr output);

    /*
      Set native database properties
    */
    void setPropertiesManager(OdNativePropertiesManagerPtr propManager);

    /*
      Get current properties
    */
    OdNativePropertiesManagerPtr getPropertiesManager();

    /*
      Remove and destroy visualize database
    */
    void removeDatabase(const OdTvDatabaseId& t_DbId);

    /*
      Set current native database entry
    */
    void setNativeDbEntry(CloudNativeDbEntryPtr nativeDb);

    /*
    Get current database entry
    */
    CloudNativeDbEntryPtr getNativeDbEntry();

    /*
    Get current stream context
    */
    OdStreamContextPtr getStreamContext();

    /*
    Set current stream context
    */
    void setStreamContext(const OdStreamContextPtr &dataManager);

  private:
    TBaseIO*                     m_baseIo;
    OdTvDatabaseId               m_dbId;
    OdTvDbRtFilerControllerPtr   m_controller;
    OdStreamOutputPtr            m_streamOutput;
    OdNativePropertiesManagerPtr m_propManager;
    CloudStreamEntry             m_streamEntry;
    CloudNativeDbEntryPtr        m_nativeDb;
  };

  typedef OdSmartPtr<OdCommandContext> OdCommandContextPtr;
}
