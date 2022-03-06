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

#ifndef __NWSHEETDATA_INCLUDED_
#define __NWSHEETDATA_INCLUDED_

#include "NwExport.h"
#include "NwObject.h"
#include "NwModelUnits.h"
#include "OdArray.h"
#include "SharedPtr.h"
#define STL_USING_VECTOR
#define STL_USING_MAP
#define STL_USING_MEMORY
#include "OdaSTL.h"
#include "SmartPtr.h"

class OdNwViewElement;
typedef std::shared_ptr<OdNwViewElement> OdNwViewElementPtr;
class OdNwGeometryCompressSettings;
typedef OdSmartPtr<OdNwGeometryCompressSettings> OdNwGeometryCompressSettingsPtr;
class OdNwSceneSet;
typedef OdSharedPtr<OdNwSceneSet> OdNwSceneSetPtr;
class OdNwPathLinkMap;
typedef std::shared_ptr<OdNwPathLinkMap> OdNwPathLinkMapPtr;
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
class OdNwDatabase;
class OdNwAttribute;
typedef OdSmartPtr<OdNwAttribute> OdNwAttributePtr;

class NWDBEXPORT OdNwSheetData
{
public:
  OdNwSheetData() = default;
  ~OdNwSheetData() = default;

public:
  OdResult setDefault(OdNwDatabase* pDb);
  void clear();
  void clearSpatialHierarchyTree();

public:
  inline NwModelUnits::Enum getModelUnits() const { return m_modelUnits; }
  inline OdNwObjectId getSavedViewsElementId() const { return m_savedViewsElementId; }
  inline OdNwObjectId getBackgroundElementId() const { return m_backgroundElementId; }
  inline OdNwObjectId getClashElementId() const { return m_clashElementId; }
  inline OdNwObjectId getRootPartitionId() const { return m_rootPartitionId; }
  inline const OdNwObjectIdArray& getLightItems() const { return m_aLightItems; }
  inline const std::vector<OdUInt32>& getPartitionPropsBlocks() const { return m_vPartPropsBlocks; }
  inline bool isAllPartPropsLoaded() const { return m_bIsAllPartPropsLoaded; }
  inline const std::pair<OdNwPropOverAttrMap, OdNwPropOverAttrMap>& getPropertyOverrides() const { return m_pPropertyOverrides; }
  inline const std::pair<OdNwHypOverAttrMap, OdNwHypOverAttrMap>& getHyperlinksOverrides() const { return m_pHyperlinksOverrides; }
  inline OdNwObjectId getShadOverrideElementId() const { return m_shadOverrideElementId; }
  OdNwObjectId getCurrentViewId() const;
  OdNwObjectId getCurrrentViewClippingPlanesId() const;
  OdNwViewElementPtr getCurrentViewElement() const;
  OdNwGeometryCompressSettingsPtr getGeometryCompressSettings() const;
  OdNwSceneSetPtr getSceneSet() const;
  OdNwPathLinkMapWeakPtr getPathLinkMap() const;
  OdNwTreeItemPtr getRootTreeItem() const;
  OdNwGridSystemElementPtr getGridSystemElement() const;
  inline OdNwObjectId getSelectionSetsElementId() const { return m_selectionSetsElementId; }
  inline OdNwObjectId getSavedAnimationElementId() const { return m_savedAnimationElementId; }

public:
  inline void setModelUnits(NwModelUnits::Enum units) { m_modelUnits = units; }
  inline void setSavedViewsElement(const OdNwObjectId& objId)   { m_savedViewsElementId = objId; }
  inline void setBackgroundElement(const OdNwObjectId& objId)   { m_backgroundElementId = objId; }
  inline void setClashElement(const OdNwObjectId& objId)        { m_clashElementId = objId; }
  inline void setRootPartition(const OdNwObjectId& objId)       { m_rootPartitionId = objId; }
  inline void setPartitionPropsBlocks(const std::vector<OdUInt32>& vPartPropsBlocks) { m_vPartPropsBlocks = vPartPropsBlocks; }
  inline void setIsAllPartPropsLoaded(bool isAllPropsLoaded) { m_bIsAllPartPropsLoaded = isAllPropsLoaded; }
  inline void setShadOverridesElement(const OdNwObjectId& objId) { m_shadOverrideElementId = objId; }
  void setCurrentViewElement(OdNwViewElementPtr pView);
  void setLights(const OdNwObjectIdArray& aLights);
  void setSceneSet(OdNwSceneSetPtr pSceneSet);
  void setPathLinkMap(OdNwPathLinkMapPtr pPathLinkMap);
  void setPropOverrideAttrMap(const std::pair<OdNwPropOverAttrMap, OdNwPropOverAttrMap>& pPropOverAtrrMap);
  void setHypOverrideAttrMap(const std::pair<OdNwHypOverAttrMap, OdNwHypOverAttrMap>& pHypOverAtrrMap);
  void setRootTreeItem(OdNwTreeItemPtr pRootTI);
  void setGridSystemElement(OdNwGridSystemElementPtr pGridSysEl);
  inline void setSelectionSetsElement(const OdNwObjectId& objId) { m_selectionSetsElementId = objId; }
  void setGeometryCompressSettings(OdNwGeometryCompressSettingsPtr pGeomCompSettings);
  void setPartitionPropsToNodes(const std::vector<OdNwAttributePtr>& vAttrs);
  inline void setSavedAnimationElementId(const OdNwObjectId& objId) {
    m_savedAnimationElementId = objId; }

private:
  //required common variables
  NwModelUnits::Enum                m_modelUnits;
  //nwf required variables
  OdNwSceneSetPtr                   m_pSceneSet;
  //nwd required variables
  OdNwObjectId                      m_rootPartitionId;
  OdNwPathLinkMapPtr                m_pPathLinkMap;
  OdNwTreeItemPtr                   m_pTreeItemRoot;
  OdNwGeometryCompressSettingsPtr   m_pGeometryCompressSettings;
  std::vector<OdUInt32>             m_vPartPropsBlocks;
  bool                              m_bIsAllPartPropsLoaded;
  //additional unrequired variables for all formats(XXX_element objects)
  OdNwViewElementPtr                m_pCurViewElement;
  OdNwObjectId                      m_savedViewsElementId;
  OdNwObjectId                      m_backgroundElementId;
  OdNwObjectId                      m_clashElementId;
  OdNwObjectIdArray                 m_aLightItems;
  std::pair<OdNwPropOverAttrMap, OdNwPropOverAttrMap> m_pPropertyOverrides;
  std::pair<OdNwHypOverAttrMap, OdNwHypOverAttrMap> m_pHyperlinksOverrides;
  OdNwObjectId                      m_shadOverrideElementId;
  OdNwGridSystemElementPtr          m_pGridSystemElement;
  OdNwObjectId                      m_selectionSetsElementId;
  OdNwObjectId                      m_savedAnimationElementId;
};

#endif //__NWSHEETDATA_INCLUDED_
