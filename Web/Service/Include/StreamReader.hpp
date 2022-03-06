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
#include "OdaCommon.h"
#include "Tv.h"

#include "RuntimeIO/DbRuntimeIO.h"
#include "TvFactory.h"

#include "OdaCommon.h"
#include "TvFactory.h"
#include "TvDatabase.h"
#include "RuntimeIO/DbRuntimeIO.h"
#include "DbEntity.h"
#include "OdStreamBuf.h"
#include "DbObjectId.h"
#include "DbBlockTableRecord.h"
#include "OdDbStub.h"
#include "OdPlatformStreamer.h"
#include "GsNode.h"
#include "GsModel.h"
#include "DbBlockBegin.h"
#include "DbBlockEnd.h"

#include "TvDatabaseImpl.h"
#include "TvGsViewImpl.h"
#include "TvLinetypeImpl.h"
#include "DbDatabase.h"
#include "DbLinetypeTable.h"
#include "DbLayerTableRecord.h"
#include "DbLayerTable.h"

namespace OdStream {
  enum class PackageType {
    Database,
    AddObject,
    EraseObject,
    NewObject,
    ChangeOrder
  };

  enum Order
  {
    MoveFront,
    MoveBottom
  };

  class Reader {
  public:

    Reader() :
      m_className(L"StreamController"), m_moduleName(L"OdTvDbRtFilerController")
    {
      m_dbId.setNull();
    }

    Reader(const Reader& reader) :
      m_className(L"StreamController"), m_moduleName(L"OdTvDbRtFilerController")
    {
      m_dbId = reader.m_dbId;
      m_controller = reader.m_controller;
    }

    void initialize()
    {
      m_dbId.setNull();
      m_controller = ::odrxSafeCreateObject<OdTvDbRtFilerController>(m_moduleName, m_className);
    }

    void clear()
    {
      m_dbId.setNull();
      if (!m_controller.isNull()) {
        m_controller->reset(nullptr);
        m_controller.release();
      }
    }

    OdTvDbRtFilerControllerPtr getController() const
    {
      return m_controller;
    }

    OdTvDatabaseId handleDatabaseChunk(OdTvFactoryId& factory, OdStreamBufPtr stream)
    {
      OdTvResult rc;
      m_dbId = factory.read(m_controller, stream, true, &rc);

      if (rc != tvOk) {
        OdString errorMsg;
        errorMsg.format(OD_T("Error read db code = %d"), rc);
        throw OdError(errorMsg);
      }

      removeExtensionDictionary();
      fixAllFilePath(m_dbId);
      invalidateDevice();
      return m_dbId;
    }

    void handleEntitiesChunk(OdStreamBufPtr stream)
    {
      auto* dbImpl = static_cast<OdTvDbDatabase*>(m_dbId.openObject(OdTv::kForWrite)->getInternalDatabase());
      auto* tvDb = dynamic_cast<OdDbDatabaseTv*>(dbImpl);

      m_controller->reset(dbImpl);

      tvDb->setSilentMode(true);

      while (!stream->isEof()) {
        try
        {
          auto obj = m_controller->readObject(*stream);
          auto ent = OdTvDbEntity::cast(obj);
          auto* gsModel = findGsModel(ent);
          if (gsModel) {
            auto topParentId = getPreTopParent(ent);
            if (!topParentId.isNull()) {
              auto parent = topParentId.openObject();
              parent->isA() == ent->isA() ? gsModel->onModified(parent, parent->ownerId()) : gsModel->onAdded(ent, parent);
            }
          }
        }
#ifdef EMCC
        catch (const OdError& err) {
          OdAnsiString ansiStr(err.description());
          std::cout << std::string(ansiStr.c_str(), ansiStr.getLength());
        }
#endif
        catch (...)
        {
          tvDb->setSilentMode(false);
        }
      }

      tvDb->setSilentMode(false);
      invalidateDevice();
    }

    void handleEraseChunk(OdStreamBufPtr stream)
    {
      auto* dbImpl = static_cast<OdTvDbDatabase*>(m_dbId.openObject(OdTv::kForWrite)->getInternalDatabase());
      auto* tvDb = dynamic_cast<OdDbDatabaseTv*>(dbImpl);

      m_controller->reset(dbImpl);

      tvDb->setSilentMode(true);

      while (!stream->isEof()) {
        auto id = dbImpl->getOdTvDbObjectId((OdUInt64)OdPlatformStreamer::rdInt64(*stream));
        auto obj = id.openObject(OdDb::kForWrite, true);
        if (obj.get()) {
          auto* gsCache = obj->gsNode();
          if (gsCache) {
            auto gsModel = gsCache->model();
            if (gsModel) {
              gsModel->onErased(obj, obj->ownerId());
            }
          }
          id->setObject(0);
          id->setFlags(kOdDbIdLoading, kOdDbIdLoading);
        }
      }

      tvDb->setSilentMode(false);
      invalidateDevice();
    }

    void handleModifyOrderChunk(OdStreamBufPtr stream)
    {
      auto tvDbPtr = m_dbId.openObject(OdTv::kForWrite);
      auto* dbImpl = static_cast<OdTvDbDatabase*>(tvDbPtr->getInternalDatabase());
      auto* tvDb = dynamic_cast<OdDbDatabaseTv*>(dbImpl);
      OdTvResult tvOk;

      auto direction = OdPlatformStreamer::rdInt32(*stream);
      auto modelHandle = (OdUInt64)OdPlatformStreamer::rdInt64(*stream);
      OdTvModelPtr modelPtr;

      for (auto modelItr = tvDbPtr->getModelsIterator(); !modelItr->done(); modelItr->step())
      {
        auto model = modelItr->getModel().openObject(OdTv::kForWrite);
        if (model->getDatabaseHandle() == modelHandle)
        {
          modelPtr = model;
          break;
        }
      }
      
      while (!stream->isEof()) {
        auto entityHandle = (OdUInt64)OdPlatformStreamer::rdInt64(*stream);
        if (modelPtr.isNull()) {
          continue;
        }
        auto entityId = modelPtr->findEntity(entityHandle, &tvOk);
        if (tvOk == OdTvResult::tvOk)
        {
          if (direction == Order::MoveFront)
          {
            modelPtr->moveToFront(entityId);
          }
          else if (direction == Order::MoveBottom)
          {
            modelPtr->moveToBottom(entityId);
          }
          else
          {
            //TODO
          }
        }
      }
      invalidateDevice();
    }

    void handleNewEntityChunk(OdStreamBufPtr stream)
    {
      auto* dbImpl = static_cast<OdTvDbDatabase*>(m_dbId.openObject(OdTv::kForWrite)->getInternalDatabase());
      auto* tvDb = dynamic_cast<OdDbDatabaseTv*>(dbImpl);

      bool needRegen = false;
      m_controller->reset(dbImpl);

      tvDb->setSilentMode(true);
      bool m_isNotFoundGsModel = false;

      for (; !stream->isEof();) {
        try {
          auto obj = m_controller->readObject(*stream);
          auto ent = OdTvDbEntity::cast(obj);
          auto pBegin = OdTvDbBlockBegin::cast(obj);
          auto pEnd = OdTvDbBlockEnd::cast(obj);
          if (!ent.isNull() && pBegin.isNull() && pEnd.isNull())
          {
            auto parent = ent->ownerId().openObject(OdDb::kForWrite);
            auto pBlock = OdTvDbBlockTableRecord::cast(parent);
            if (!pBlock.isNull())
            {
              pBlock->appendOdTvDbEntity(ent);
            }

            auto* gsModel = findGsModel(ent);
            if (gsModel) {
              auto topParentId = getPreTopParent(ent);
              if (!topParentId.isNull()) {
                auto parent = topParentId.openObject();
                parent->isA() == ent->isA() ? gsModel->onModified(parent, parent->ownerId()) : gsModel->onAdded(ent, parent);
              }
            }

            if (m_isNotFoundGsModel)
            {
              m_isNotFoundGsModel = false;
              tvDb->setSilentMode(true);
            }
          }
          else if (!OdTvDbBlockTableRecord::cast(obj).isNull())
          {
            auto pBlock = OdTvDbBlockTableRecord::cast(obj);
            const auto blockName = pBlock->getName();

            {
              OdTvDbBlockTablePtr pBlocksTable = dbImpl->getBlockTableId().openObject(OdDb::kForWrite);
              if (pBlocksTable->getAt(blockName).isNull()) {
                pBlocksTable->add(pBlock);
              }
            }

            {
              bool isAdded = false;

              auto devItr = m_dbId.openObject()->getDevicesIterator();
              auto device = devItr->getDevice().openObject();
              auto viewId = device->getActiveView();
              auto view = viewId.openObject();

              for (int i = 0; i < view->numModels(); i++) {
                isAdded = view->modelAt(i).openObject()->getName() == blockName;
              }

              if (!isAdded) {
                auto findModel = m_dbId.openObject()->findModel(blockName);
                if (!findModel.isNull()) {
                  view->addModel(findModel);
                }
              }
            }
          }
          else if (!OdTvDbLinetypeTableRecord::cast(obj).isNull())
          {
            auto linetype = OdTvDbLinetypeTableRecord::cast(obj);
            const auto linetypeName = linetype->getName();
            OdTvDbLinetypeTablePtr plinetypeTable = dbImpl->getLinetypeTableId().openObject(OdDb::kForWrite);
            if (plinetypeTable->getAt(linetypeName).isNull()) {
              plinetypeTable->add(linetype);
            }
          }
          else if (!OdTvDbLayerTableRecord::cast(obj).isNull())
          {
            auto layer = OdTvDbLayerTableRecord::cast(obj);
            const auto layerName = layer->getName();
            OdTvDbLayerTablePtr playerTable = dbImpl->getLayerTableId().openObject(OdDb::kForWrite);
            if (playerTable->getAt(layerName).isNull()) {
              playerTable->add(layer);
            }
          }
          else {
            needRegen = true;
          }
        }
        catch (...) {
          m_isNotFoundGsModel = true;
          tvDb->setSilentMode(false);
        }
      }

      tvDb->setSilentMode(false);

      if (needRegen) {
        auto devItr = m_dbId.openObject()->getDevicesIterator();
        auto device = devItr->getDevice();
        device.openObject()->regen(OdTvGsDevice::kRegenVisible);
      }
      invalidateDevice();
    }

    void fixAllFilePath(const OdTvDatabaseId& dbId)
    {
      OdTvDatabasePtr dbPtr = dbId.openObject(OdTv::kForWrite);
      auto pItrTextStyle = dbPtr->getTextStylesIterator();
      if (!pItrTextStyle.isNull())
      {
        OdString userDataName = OD_T("ExGsVisualizeDevice");
        bool exit = false;
        OdTvRegAppId regId = dbPtr->registerAppName(userDataName, exit);
        OdTvRegAppId regAppTypefaceCahce = dbPtr->registerAppName(OD_T("TypeFaceStreamCache"), exit);

        for (; !pItrTextStyle->done(); pItrTextStyle->step())
        {
          OdTvTextStyleId textStyleID = pItrTextStyle->getTextStyle();
          OdTvTextStylePtr pTextStyle = textStyleID.openObject(OdTv::kForWrite);

          OdString fName = pTextStyle->getFileName();
          if (fName.isEmpty())
          {
            OdTvByteUserData* userData = dynamic_cast<OdTvByteUserData*>(pTextStyle->getUserData(regId));
            if (userData != nullptr)
            {
              fName = OdString(static_cast<const char*>(userData->getData()),
                userData->getSize(), CP_UTF_8);
            }
          }

          if (!fName.isEmpty())
          {
            pTextStyle->setFileName(getFileNameW(fName));
          }

          // Get typeface from user data
          OdString typeface;
          OdTvByteUserData* userData = dynamic_cast<OdTvByteUserData*>(pTextStyle->getUserData(regAppTypefaceCahce));
          if (userData != nullptr)
          {
            typeface = OdString(static_cast<const char*>(userData->getData()),
              userData->getSize(), CP_UTF_8);
          }

          if (!typeface.isEmpty()) {
            bool bold, italic;
            int charsetm, pitchAndFamily;
            OdString tmp;
            pTextStyle->getFont(tmp, bold, italic, charsetm, pitchAndFamily);
            pTextStyle->setFont(typeface, bold, italic, charsetm, pitchAndFamily);
          }

          if (!pTextStyle->getBigFontFileName().isEmpty())
          {
            pTextStyle->setBigFontFileName(getFileNameW(pTextStyle->getBigFontFileName()));
          }
        }
      }

      auto pItrRasterIngItr = dbPtr->getRasterImagesIterator();
      if (!pItrRasterIngItr.isNull())
      {
        for (; !pItrRasterIngItr->done(); pItrRasterIngItr->step())
        {
          OdTvRasterImageId textStyleID = pItrRasterIngItr->getRasterImage();
          OdTvRasterImagePtr pRasterImg = textStyleID.openObject(OdTv::kForWrite);

          if (!pRasterImg->getSourceFileName().isEmpty())
          {
            pRasterImg->setSourceFileName(getFileNameW(pRasterImg->getSourceFileName()));
          }
        }
      }

      auto pItrBackgrounds = dbPtr->getBackgroundsIterator();
      if (!pItrBackgrounds.isNull())
      {
        for (; !pItrBackgrounds->done(); pItrBackgrounds->step())
        {
          OdTvGsViewBackgroundId backgroundId = pItrBackgrounds->getGsViewBackground();
          if (backgroundId.getType() == OdTvGsViewBackgroundId::kImage)
          {
            OdTvGsViewImageBackgroundPtr pImgBackground = backgroundId.openAsImageBackground(OdTv::kForWrite);
            if (!pImgBackground->getImageFilename().isEmpty())
            {
              pImgBackground->setImageFilename(getFileNameW(pImgBackground->getImageFilename()));
            }
          }
        }
      }
    }

  protected:
    void removeExtensionDictionary()
    {
      OdTvDatabasePtr dbPtr = m_dbId.openObject(OdTv::kForWrite);

      OdTvModelId               idM;
      OdTvDbObjectId            dictionaryId;
      OdTvDbBlockTableRecordPtr block;

      for (auto itr = dbPtr->getModelsIterator(); !itr->done(); itr->step()) {
        idM = itr->getModel();
        block = ((const OdTvDbObjectId*)(&idM))->openObject();
        dictionaryId = block->extensionDictionary();
        if (!dictionaryId.isNull()) {
          dictionaryId->setObject(0);
          dictionaryId->setFlags(kOdDbIdErased, kOdDbIdErased);
        }
      }
    }

    void invalidateDevice() {
      auto devItr = m_dbId.openObject()->getDevicesIterator();

      for (; !devItr->done(); devItr->step()) {
        auto devId = devItr->getDevice();
        if (devId.isNull()) {
          continue;
        }
        auto device = devId.openObject();
        if (device->getActive()) {
          device->invalidate();
          break;
        }
      }
    }

    OdString getFileNameW(const OdString& path) {
      OdString fixPath = path;
      fixPath.replace('\\', '/');
      return fixPath.right(fixPath.getLength() - (fixPath.reverseFind('/') + 1));
    }

    OdTvDbObjectId getPreTopParent(OdTvDbObjectPtr entity) {
      if (entity.isNull()) {
        return OdTvDbObjectId();
      }

      {
        auto parentId = entity->ownerId();
        auto parentObjPtr = parentId.openObject();

        if (parentObjPtr.isNull())
          return parentId;

        if (parentObjPtr->isA() != entity->isA()) {
          return parentId;
        }
      }

      do {
        auto parentId = entity->ownerId();
        auto parentObjPtr = parentId.openObject();

        if (parentObjPtr.isNull())
          return parentId;

        if (parentObjPtr->isA() != entity->isA()) {
          return entity->objectId();
        }

        entity = parentObjPtr;

      } while (!entity.isNull());

      return OdTvDbObjectId();
    }

    OdGsModel* findGsModel(const OdTvDbEntityPtr& entity)
    {
      if (!entity.get()) {
        return nullptr;
      }
      OdGsModel* pModel = nullptr;
      OdGsNode* pGsNode = nullptr;

      OdTvDbObjectPtr owner = entity->ownerId().openObject();

      while (!owner.isNull()) {
        pGsNode = (OdGsNode*)owner->gsNode();
        pModel = pGsNode ? pGsNode->model() : nullptr;
        if (pModel) {
          break;
        }
        owner = owner->ownerId().openObject();
      }

      return pModel;
    }
  private:
    OdString m_moduleName;
    OdString m_className;
    OdTvDatabaseId m_dbId;
    OdTvDbRtFilerControllerPtr m_controller;
  };
}