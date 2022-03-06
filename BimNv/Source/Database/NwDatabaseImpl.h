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

#ifndef _NWDATABASEIMPL_INCLUDED_
#define _NWDATABASEIMPL_INCLUDED_

#include "StaticRxObject.h"
#include "NwDatabase.h"
#include "NwObjectImpl.h"
#include "NwFileLoader.h"
#include "NwUnitsFormatterImpl.h"
#include "tbb/tbb_stddef.h"
#include "NwOpenOptions.h"
#include "NwModeType.h"

namespace tbb 
{
  class spin_mutex;
}

class OdNwSavedItemsElement;
typedef OdSmartPtr<OdNwSavedItemsElement> OdNwSavedItemsElementPtr;
class OdNwGeometryCompressSettings;
typedef OdSmartPtr<OdNwGeometryCompressSettings> OdNwGeometryCompressSettingsPtr;
class OdNwSceneSet;
typedef OdSharedPtr<OdNwSceneSet> OdNwSceneSetPtr;
class OdNwViewElement;
typedef std::shared_ptr<OdNwViewElement> OdNwViewElementPtr;
class OdNwPathLinkMap;
typedef std::weak_ptr<OdNwPathLinkMap> OdNwPathLinkMapWeakPtr;
class OdNwPropertyOverrideAttribute;
typedef std::shared_ptr<OdNwPropertyOverrideAttribute> OdNwPropertyOverrideAttributePtr;
typedef std::map<OdNwObjectId, OdArray<OdNwPropertyOverrideAttributePtr> > OdNwPropOverAttrMap;
class OdNwURL;
typedef OdSmartPtr<OdNwURL> OdNwURLPtr;
typedef OdArray<OdNwURLPtr> OdNwHypOverCollection;
typedef std::map<OdNwObjectId, OdNwHypOverCollection> OdNwHypOverAttrMap;
class OdNwTreeItem;
typedef OdSmartPtr<OdNwTreeItem> OdNwTreeItemPtr;
class OdNwGridSystemElement;
typedef OdSmartPtr<OdNwGridSystemElement> OdNwGridSystemElementPtr;
class OdNwSelectionSetsElement;
typedef OdSmartPtr<OdNwSelectionSetsElement> OdNwSelectionSetsElementPtr;

class NWDBEXPORT OdNwDatabaseImpl : public OdNwObjectImpl
{
protected:
  OdSharedPtr<class OdHandleTree> m_pHandles; 

  friend class OdNwDatabase;
  friend class OdNwHostAppServices;

public:
  ODRX_DECLARE_MEMBERS(OdNwDatabaseImpl);
  OdNwDatabaseImpl();
  virtual ~OdNwDatabaseImpl();

  OdResult initialize();

  // OdNwDatabase methods :
  virtual OdNwHostAppServices* appServices() const;
  virtual void readFile(OdStreamBuf* pStreamBuf,
                        bool partialLoad2d = true,
                        const OdString& password = OdString::kEmpty);
  virtual void readFile(const OdString& fileName,
                        bool partialLoad2d = true,
                        const OdString& password = OdString::kEmpty);

  virtual void writeFile(const OdString& fileName);
  virtual void writeFile(OdStreamBuf* pFileBuff);

  virtual OdString getFilename() const;
  virtual OdString getPassword() const;

  OdNwObjectId addObject(OdNwObjectPtr pObj,
                          const OdDbHandle& handle = OdDbHandle());
  OdNwObjectId getObjectId(const OdDbHandle& handle,
                            bool createIfNotFound);
protected:
  OdNwObjectId getMTObjectId(const OdDbHandle& handle, bool createIfNotFound);
  OdNwObjectId getSTObjectId(const OdDbHandle& handle, bool createIfNotFound);
public:
  OdNwObjectId  getNewObjectId(const OdDbHandle& handle = OdDbHandle());

  static OdNwDatabaseImpl* getImpl(const OdNwDatabase* pNwDb);
  static OdNwDatabaseImpl* getImpl(const OdRxObject* pRxDb);

  OdArray<NwSubStreamDef> getCachedStreams();

protected:
  OdResult                 initCurrentSheetFromStream();

protected:
  template<typename T>
  T getElement(std::function<T(const OdNwSheetData&)> func) const;
  OdResult setElement(std::function<OdResult(OdNwSheetData&)> func);

public:
  OdNwObjectId                    getCurrentViewId();
  OdNwObjectId                    getCurrrentViewClippingPlanesId();
  OdNwViewElementPtr              getCurrentViewElement();
  OdResult                        getSavedViewsElements(OdNwObjectIdArray& aSavedViewsElements);
  OdNwSavedItemsElementPtr        getSavedViewsElement();
  OdNwObjectId                    getSavedViewsElementId();
  OdNwObjectId                    getBackgroundElementId();
  OdNwObjectId                    getClashElementId();
  OdNwGeometryCompressSettingsPtr getGeometryCompressSettings();
  OdResult                        getModels(OdNwObjectIdArray& arrModels);
  OdNwObjectId                    getModelItemRootId();
  OdGeMatrix3d                    getModelTransform();
  inline bool                     isComposite() const { return m_bIsComposite; }
  NwModelUnits::Enum              getUnits() const;
  OdResult                        getLightElements(OdNwObjectIdArray& arrLights);
  OdResult                        getLightItems(OdNwObjectIdArray& arrLights);
  bool                            isPartialLoading() const;
  OdInt16                         getMTMode() const;
  OdNwSceneSetPtr                 getSceneSet();
  OdNwXRefTablePtr                getXRefTable();
  OdNwSchemaCommonPtr             getSchemaCommon();
  OdNwObjectId                    getActiveSheetId();
  OdResult                        getSheets(OdNwObjectIdArray& aSheets);
  OdNwObjectId                    getFileInfo() const;
  OdResult                        getPartitionPropsBlocks(std::vector<OdInt32>& vPartPropsBlocks);
  OdNwPathLinkMapWeakPtr          getPathLinkMap();
  OdResult                        getPropertyOverrides(std::pair<OdNwPropOverAttrMap, OdNwPropOverAttrMap>& pPropOverAttrs);
  OdResult                        getHyperlinksOverrides(std::pair<OdNwHypOverAttrMap, OdNwHypOverAttrMap>& pHypOverAttrs);
  OdNwObjectId                    getShadOverrideElement();
  OdNwTreeItemPtr                 getRootTreeItem();
  OdNwGridSystemElementPtr        getGridSystemElement();
  OdNwSelectionSetsElementPtr     getSelectionSetsElement();
  OdNwObjectId                    getSelectionSetsElementId();
  OdNwObjectId                    getSavedAnimationElementId();
  bool                            isAllPartitionPropsLoaded();
  OdResult                        loadAllPartitionProps();

  const OdString&                 getTextureFolder() const;
  void                            setTextureFolder(const OdString& path);

  OdNwObjectId                    getVisualStyle(NwModeType::Enum renderMode);

public:
  OdResult                 addModel(OdNwModelPtr pModel);
  OdNwObjectId             addModel(const OdString& sourcePath, OdResult* pResCode);
  OdResult                 setActiveSheet(const OdString& sheetId, bool partialLoading = true);
  void                     setGeometryCompressSettings(OdNwGeometryCompressSettingsPtr settings);
  void                     setRootTreeItem(OdNwTreeItemPtr pRootTreeItem);
  void                     setShadOverrideElement(const OdNwObjectId& shOvElId);
  void                     setUnits(NwModelUnits::Enum units);
  OdResult                 clearCurrentSpatialHierarchyTree();
  NwFormatVersion::Enum    getOriginalFormatVersion();
  const OdNwUnitsFormatter& formatter() const;
  OdNwUnitsFormatter&       formatter();
  void                      setOptions(const std::map<NwOpenOptions::Enum, OdInt32>& options);
  OdInt32                   getOption(NwOpenOptions::Enum option);
  void                      setStreamsDumpPath(OdString path);
  

private:
  //database helper datafor reading/rendering
  OdString                          m_sFilePathName;
  OdString                          m_sTextureFolderPath;
  OdNwHostAppServices*              m_pNwHostAppSvcs;
  OdSharedPtr<tbb::spin_mutex>      m_pMutexHandle;
  OdInt16                           m_MTMode;
  bool                              m_bPartialLoading;
  std::map<NwModeType::Enum, OdNwObjectId> m_mVisualStyles;

  //database file loader with sheet states
  OdNwFileLoader                    m_oLoader;

  //database data
  OdNwXRefTablePtr                  m_pXRefTable;
  OdNwSchemaCommonPtr               m_pSchemaCommon;
  OdNwObjectId                      m_fileInfoId;
  bool                              m_bIsComposite;

  OdStaticRxObject<OdNwUnitsFormatterImpl>              m_pUnitsFormatter;
  
  // database reading options
  std::map<NwOpenOptions::Enum, OdInt32>    m_options;
};

typedef OdSmartPtr<OdNwDatabaseImpl> OdNwDatabaseImplPtr;

#endif // _NWDATABASEIMPL_INCLUDED_
