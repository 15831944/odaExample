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

#ifndef OdTvNwdExporter_H
#define OdTvNwdExporter_H

#include "TD_PackPush.h"

#define STL_USING_STACK
#define STL_USING_MAP
#define STL_USING_FUNCTIONAL
#include "OdaSTL.h"
#include <tuple>
#include <unordered_map>

//nw
#include "NwObject.h"

//tv
#include "TvEntity.h"

//----------------------------------------------------------
//
// OdTvNwdExporter
//
//----------------------------------------------------------

class OdTvLayerId;
class OdTvMaterialId;
class OdTvBlockId;

//OdTvNwdMaterialLinkType is map with link between tv material id and tuple with nw object id
//nw material tuple has 3 members:
//0 - boolean flag, true - if tv material has inherit colors
//1 - OdNwObjectId with NwMaterial if tv material has not inherits colors, and empty in other case
//2 - hash map with pairs - override color in OdUInt32 value and OdNwObjectId with NwMaterial, empty if material has not inherit colors
using OdTvNwdMaterialLinkType = std::map<OdTvMaterialId, std::tuple<bool, OdNwObjectId, std::unordered_map<OdUInt32, OdNwObjectId> > >;
//OdTvNwdBlockLinkType is map with link between tv block id and map with pair OdTvGeometryDataId and OdNwObjectId with NwGeometry
//need for adding reused geometry in nw components of model item which created by block-insert
using OdTvNwdBlockLinkType = std::map<OdTvBlockId, std::map<OdTvGeometryDataId, OdNwObjectId> >;

class OdTvNwdExporter
{
public:
  OdTvNwdExporter(std::map<OdTvLayerId, OdNwObjectId>&& layersIdMap, std::function<bool(OdTvEntityId)> viewIdForExportInit);

  //create model item nodes with data by pEntIter and append them as children to nwParentId
  //pEntIter [in] - tv iterator with entities for export to nwd
  //nwParentId [in] - nw object id of model item which must be parent for new nodes which created by data from tv entity iterator
  //trm [in] - transformation for entity data(most used for tv blocks entities from insert)
  //isModelLvl [in] - is tv entity data is first level child of tv models
  void exportByEntityIterator(OdTvEntitiesIteratorPtr pEntIter, const OdNwObjectId& nwParentId, const OdTvMatrix& trm, bool isModelLvl);

private:
  void createModelItemsByTvEntity(OdTvEntityPtr pTvEntity, const OdNwObjectId& nwParentId, const OdTvMatrix& trm);
  void createModelItemsByTvInsert(OdTvInsertPtr pTvInsert, OdNwObjectId nwParentId, const OdTvMatrix& trm);

  OdResult addNwGeometryNode(const OdNwObjectId& nwParentId, const OdTvMaterialDef& tvMatDef, const OdTvColorDef& tvClrDef, const OdTvMatrix& trm, std::tuple<OdString, OdString, OdString, bool> nodeNamesAndIsHidden, std::function<OdNwObjectId(OdNwObjectId)> addGeomFrag);
  void setMaterialDataToComponent(OdNwObjectId nwCompId, const OdTvMaterialDef& tvMatDef, const OdTvColorDef& tvClrDef);
  void removeTvLayerFromHelperBranches(const OdTvLayerDef& tvLayerDef, bool isBlockBranch);

  OdNwObjectId getModelItemByTvLayerDef(const OdTvLayerDef& tvLayerDef, bool isBlockBranch);
  OdTvMaterialId getTvMatId(const OdTvMaterialDef& tvMatDef);
  OdUInt32 getInhClr(const OdTvColorDef& tvClrDef);

protected:
  //map for connection of tv layer id with nw object id with layer
  std::map<OdTvLayerId, OdNwObjectId> m_mLayersId;
  std::function<bool(OdTvEntityId)> m_clbkViewIdForExportInit;
  OdTvNwdMaterialLinkType m_mMaterials;
  OdTvNwdBlockLinkType m_mBlocks;

  //VAS: non defatual tv material line path from root to current node
  std::stack<OdTvMaterialDef> m_stNonDefaultMatBranch;
  //VAS: non defatual tv color line path from root to current node
  std::stack<OdTvColorDef> m_stNonDefaultClrHierarchyBranch;
  //VAS: not is by block tv layer line path from root to current node
  std::stack<OdTvLayerDef> m_stLayerBranch;
  //VAS: tv insert line path from root to current node
  std::stack<OdTvEntityId> m_stBlockBranch;
  //VAS: pointer to map with links between OdTvGeometryDataId objects and OdNwObjectId with OdNwGeometry, not empty for Insert cases
  std::map<OdTvGeometryDataId, OdNwObjectId>* m_pReusesGeometry;
  //VAS: OdNwObjectId with OdNwGeometry which already exist and must be reused in another OdNwFragment
  OdNwObjectId m_nwGeomReusedId;
};

#include "TD_PackPop.h"

#endif // OdTvNwdExporter_H
