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

#ifndef __NWFILELOADER_H__
#define __NWFILELOADER_H__

#include "NwExport.h"
#include "NwStreamSplitter.h"
#include "NwStreamType.h"
#include "NwStreamLoader.h"
#include "NwModelUnits.h"
#define STL_USING_MEMORY
#define STL_USING_VECTOR
#include "OdaSTL.h"
#include "NwObject.h"

class OdNwDatabaseImpl;
class OdNwXRefTable;
typedef OdSharedPtr<OdNwXRefTable> OdNwXRefTablePtr;
class OdNwSchemaCommon;
typedef OdSharedPtr<OdNwSchemaCommon> OdNwSchemaCommonPtr;
class OdNwFileInfo;
typedef OdSmartPtr<OdNwFileInfo> OdNwFileInfoPtr;
class OdNwStreamLoaderFactory;
class OdNwSheetData;

namespace NwFileLoaderState
{
  enum Enum
  {
    kIsNotInit = -1,
    kIsNotLoad = 0,
    kIsLoad = 1
  };
}

class OdNwFileLoader
{
public:
  OdNwFileLoader();
  ~OdNwFileLoader();

  void setCompressedMode(bool compressed);
  void setStreamsDumpPath(OdString path);

  bool Load(const OdStreamBufPtr& stream, OdNwDatabaseImpl* pDbImpl);
  bool loadCommonStreams(OdNwDatabaseImpl* pDbImpl, OdNwStreamLoaderFactory& streamLoaderFactory);

  void setTextureFolder(const OdString& path);
  OdResult parseSheetByIndex(OdInt32 sheetIdx, bool partialLoading = true);
  OdResult clearSpatialHierarchyTree(OdInt32 sheetIdx = -1);

  OdInt32 getVersion() const;
  inline NwFileLoaderState::Enum isLoaded() const { return m_loadStatus; }
  OdNwStreamLoaderPtr getLoader(const NwStreamType::Enum type, OdUInt32 sheetIndex = 0);

public:
  //init cuurent sheet state(with lazy mose if it necessary) data from streams
  OdResult initSheetState(bool partialLoading);
protected:
  template <typename Func, class ...Args>
  inline OdResult initSheetDataFromStream(Func firstInitFunc, Args... otherInitFunc)
  {
    OdResult resCode = (this->*firstInitFunc)();
    if (resCode == eOk || resCode == eNotInDatabase)
      resCode = initSheetDataFromStream(otherInitFunc...);
    return resCode;
  }
  template <typename Func>
  inline OdResult initSheetDataFromStream(Func initFunc)
  {
    return (this->*initFunc)();
  }
protected:
  template<NwStreamType::Enum streamType, typename streamLoader>
  OdResult initCurSheetData(std::function<OdResult(std::shared_ptr<streamLoader>, OdNwSheetData& sheetData)> initSheetData);
public:
  //methods for current sheet data initialization from streams
  OdResult initCurrentViewElement();
  OdResult initSavedViewsElement();
  OdResult initBackgroundElement();
  OdResult initClashElement();
  OdResult initModelItemRoot();
  OdResult initLightItems();
  OdResult initSceneSet();
  OdResult initPathLinkMap();
  OdResult initPartitionPropsBlocks();
  OdResult initPropertOverrideMaps();
  OdResult initHyperlinksOverrideMaps();
  OdResult initShadOverrideElement();
  OdResult initRootTreeItem();
  OdResult initGridSystemElement();
  OdResult initSelectionSetsElement();
  OdResult initPartitionProps();
  //methods for getting data from common stream
  OdNwXRefTablePtr getXRefTable() const;
  OdNwSchemaCommonPtr getSchemaCommon() const;
  OdNwObjectId getFileInfo() const;
  inline bool isComposite() { return m_bIsComposite; }

  void dump_StreamNames(const OdString& path);
  void reset();

  void getCachedStreams(OdArray<NwSubStreamDef>& streams);
  OdResult initSavedAnimationElement();

private:
  NwFileLoaderState::Enum m_loadStatus;
  OdNwStreamSplitter      m_oSplitter;
  OdString                m_sTextureFolderPath;
  OdNwObjectId            m_fileInfoId;
  OdNwXRefTablePtr        m_pXRefTable;
  OdNwSchemaCommonPtr     m_pCommonSchemas;
  bool                    m_bIsComposite;

  //VAS: m_vSheetStreams container for sheet loaders info:
  // first element - boolean status is sheet was loaded(partial or no, it's doesn't matter
  // second element - array with cached streams for sheets(common streams, wich still not be loaded in commonLoadStream also contains in first sheet)
  // third element - loader map with stream loaders for sheet
  std::vector<std::tuple<bool, OdArray<NwSubStreamDef>, OdNwLoadersMap > > m_vSheetStreams;
};

#endif // __NWFILELOADER_H__
