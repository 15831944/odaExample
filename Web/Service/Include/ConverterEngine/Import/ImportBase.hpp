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
#include "OdString.h"
#include "BaseConverterWorker.hpp"
#include "RuntimeIO/DbRuntimeIO.h"
#include "TvVisualizeFiler.h"
#include "MemoryStream.h"

void callLoadOneDwgModel(OdTvFilerFeedbackForChooseObject& object);

void callLoadOneDgnModel(OdTvFilerFeedbackForChooseObject& object);

void callLoadOneBimView(OdTvFilerFeedbackForChooseObject& object);

void callLoadOneModel(OdTvFilerFeedbackForChooseObject& object);

void callbackForLoadBim3dView(OdTvFilerFeedbackForChooseObject& object);

void callLoadAll(OdTvFilerFeedbackForChooseObject& object);

class OdImportTemStream;
typedef OdSmartPtr<OdImportTemStream> OdImportTemStreamPtr;

class OdImportTemStream : public OdMemoryStream {
protected:
  OdImportTemStream();

public:
  ODRX_DECLARE_MEMBERS(OdImportTemStream);

  static OdImportTemStreamPtr createNew(const OdString& fileName, OdUInt32 pageDataSize = 0x800);

  OdString fileName();

private:
  OdString m_fileName;
};

class OdStreamWithCustomName;
typedef OdSmartPtr<OdStreamWithCustomName> OdStreamWithCustomNamePtr;

class OdStreamWithCustomName : public OdStreamBuf
{
protected: 
  OdStreamWithCustomName()
  {
    
  }

public:
  ODRX_DECLARE_MEMBERS(OdStreamWithCustomName);

  static OdStreamWithCustomNamePtr createNew(const OdString& filePath, const OdString& originalFileName)
  {
    OdStreamWithCustomNamePtr pRes = OdRxObjectImpl<OdStreamWithCustomName>::createObject();
    pRes->m_buff = ::odrxSystemServices()->createFile(filePath);
    pRes->m_originalFileName = originalFileName;
    return pRes;
  }

  OdString fileName() override
  {
    return m_originalFileName;
  }

  bool isEof() override
  {
    return m_buff->isEof();
  }

  OdUInt64 tell() override
  {
    return m_buff->tell();
  }

  OdUInt64 length() override
  {
    return m_buff->length();
  }

  void truncate() override
  {
    return m_buff->truncate();
  }

  void rewind() override
  {
    return m_buff->rewind();
  }

  OdUInt64 seek(OdInt64 offset, OdDb::FilerSeekType seekType) override
  {
    return m_buff->seek(offset, seekType);
  }

  OdUInt8 getByte() override
  {
    return m_buff->getByte();
  }

  void getBytes(void* buffer, OdUInt32 numBytes) override
  {
    m_buff->getBytes(buffer, numBytes);
  }

  void putByte(OdUInt8 value) override
  {
    m_buff->putByte(value);
  }

  void putBytes(const void* buffer, OdUInt32 numBytes) override
  {
    m_buff->putBytes(buffer, numBytes);
  }

  void copyDataTo(OdStreamBuf* pDestination, OdUInt64 sourceStart, OdUInt64 sourceEnd) override
  {
    m_buff->copyDataTo(pDestination, sourceStart, sourceEnd);
  }

  OdUInt32 getShareMode() override
  {
    return m_buff->getShareMode();
  }

private:
  OdStreamBufPtr m_buff;
  OdString m_originalFileName;
};

struct OdImportConvertOptions : public OdBaseConvertOptions
{
  bool     loadAll;
  OdString source;
  OdString pathToSaveDir;
  OdTvDatabaseId dbId;
  std::vector<MetaDataItem> importAllResult;
  bool isGenerateCdaTree;

  OdImportConvertOptions() : isGenerateCdaTree(true) {

  }
};

struct BaseImportWorker : public BaseConvertWorker {
public:
  virtual void convert(OdBaseConvertOptions *opt);

  virtual ~BaseImportWorker();

  virtual std::shared_ptr<OdTvBaseImportParams> getImportParams(
    const OdString& pathToFile, bool isNeedGenerateCDA = true) = 0;

  virtual std::shared_ptr<OdTvBaseImportParams> getAppendParams(
    const OdString& pathToFile, bool isNeedGenerateCDA = true) = 0;

  void saveCache(const OdTvDatabaseId& dbId, const OdString& savePath, bool isImportAll = false);
protected:
  virtual OdTvDatabaseId
    subImport(const OdString& sourcePath, OdBaseConvertOptions* opt, const OdString& model = L"", bool autoFind = true) = 0;

  virtual OdTvDatabaseId subImportAll(const OdString& sourcePath, OdBaseConvertOptions* opt);

  virtual void actionAfterGsUpdate(const OdTvDatabaseId& dbId) {}

  virtual std::tuple<bool, bool> subFilter(const OdString& name, const std::vector<OdString>& all);

  virtual void subOrderModelList();

  void import(OdBaseConvertOptions *opt);

  void importAll(OdBaseConvertOptions *opt);

  void zoomToExtents(const OdTvDatabaseId& dbId);

  void createSpaceIndex(const OdTvDatabaseId& tvDbId, OdTvDbRtFilerControllerPtr pController);

  void autoFixDb(const OdTvDatabaseId& dbId);

  OdString convertToMd5(const OdString& str);

  void setEnableCDA(OdTvBaseImportParams* baseImportParams, OdImportConvertOptions* pOpt);

  void explodeSubEntities(const OdTvDatabaseId& dbId);

  void setVisualStyleByName(const OdTvDatabaseId& dbId, const OdString& vsName);

  static void chooseActive(OdTvFilerFeedbackForChooseObject &object);

  static OdString m_activeModel;
  static std::vector<OdString> m_listModels;
};