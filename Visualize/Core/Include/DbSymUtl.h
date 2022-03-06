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




#ifndef DBSYMUTL_DEFINED
#define DBSYMUTL_DEFINED

#include "TD_PackPush.h"

#include "OdString.h"
#include "DbObjectId.h"
#include "DbSymbolTable.h"
#include "DbSymbolTableRecord.h"
#include "DbTextStyleTableRecord.h"
#include "DbDictionary.h"
#include "DbDatabase.h"

// Predefined names
#define AC_STRING(name, val) \
extern TOOLKIT_EXPORT_GLOBAL const OdConstString name;
#include "StdStrings.h"
#undef AC_STRING

/** \details

    <group TD_Namespaces>
*/
namespace OdTvDbSymUtil
{
  // --- DbSymbolUtilities Services  ---

  TOOLKIT_EXPORT OdResult repairPreExtendedSymbolName(
    OdString& newName,
    const OdString& oldName,
    const OdTvDbDatabase* pDb,
    bool allowVerticalBar = false,
    const OdChar symSubst = L'_',
    bool insertPrefix = true);

  /** \details
    If the symbol name was repaired, then newName is a repaired symbol name. 
    newName is empty if oldName did not need any repairing.
    allowVerticalBar is a boolean to indicate if vertical bars are allowed in the symbol name 
    
    \returns
    eInvalidInput      if the specified name is empty
    eOk                in else case 
  */
  TOOLKIT_EXPORT OdResult repairSymbolName(
    OdString& newName,
    const OdString& oldName,
    const OdTvDbDatabase* pDb,
    bool allowVerticalBar = false,
    const OdChar symSubst = L'_',
    bool insertPrefix = true);
  
  TOOLKIT_EXPORT OdResult validatePreExtendedSymbolName(
    const OdString& name,
    const OdTvDbDatabase* pDb,
    bool allowVerticalBar = false);

  /** \details
    This method validates name according to the rules for extended (AutoCAD 2000 and later) symbol names.
    allowVerticalBar is a boolean to indicate if vertical bars are allowed in the symbol name 
    
    \returns
    eOk            Symbol name is valid 
    eInvalidInput  Symbol name contains invalid characters 
  */
  TOOLKIT_EXPORT OdResult validateSymbolName(
    const OdString& name,
    const OdTvDbDatabase* pDb,
    bool allowVerticalBar = false);

  TOOLKIT_EXPORT bool getMaxSymbolNameLength(
    OdUInt32& maxLength,
    OdUInt32& maxSize,
    bool isNewName,
    bool compatibilityMode); // true for extended names

  inline OdString getSymbolName(const OdTvDbObjectId& objId)
  {
    OdTvDbSymbolTableRecordPtr pRec
      = OdTvDbSymbolTableRecord::cast(objId.openObject(OdDb::kForRead, true).get());
    if (!pRec.isNull())
    {
      return pRec->getName();
    }
    return OdString::kEmpty;
  }

  #define DBSYMUTL_MAKE_GETSYMBOLID_FUNC(T_TABLE) \
  inline OdTvDbObjectId \
  get ## T_TABLE ## Id(const OdString& name, const OdTvDbDatabase *pDb) \
  { \
    if (!pDb) return OdTvDbObjectId::kNull; \
    OdTvDbSymbolTablePtr pTable = pDb->get ## T_TABLE ## TableId().safeOpenObject(); \
    ODA_ASSERT(!pTable->isOdTvDbObjectIdsInFlux()); \
    return pTable->getAt(name); \
  }
  DBSYMUTL_MAKE_GETSYMBOLID_FUNC(Viewport)
  DBSYMUTL_MAKE_GETSYMBOLID_FUNC(Block)
  DBSYMUTL_MAKE_GETSYMBOLID_FUNC(DimStyle)
  DBSYMUTL_MAKE_GETSYMBOLID_FUNC(Layer)
  DBSYMUTL_MAKE_GETSYMBOLID_FUNC(Linetype)
  DBSYMUTL_MAKE_GETSYMBOLID_FUNC(RegApp)
  //DBSYMUTL_MAKE_GETSYMBOLID_FUNC(TextStyle)

  inline OdTvDbObjectId getTextStyleId(const OdString& name, const OdTvDbDatabase *pDb)
  {
    if (!pDb) return OdTvDbObjectId::kNull;
    OdTvDbSymbolTablePtr pTable = pDb->getTextStyleTableId().safeOpenObject();
    ODA_ASSERT(!pTable->isOdTvDbObjectIdsInFlux());
    OdTvDbTextStyleTableRecordPtr pRec = pTable->getAt(name, OdDb::kForRead);

    if (pRec.get())
      if (!pRec->isShapeFile())
        return pRec->objectId();
    return OdTvDbObjectId::kNull;
  }

  DBSYMUTL_MAKE_GETSYMBOLID_FUNC(UCS)
  DBSYMUTL_MAKE_GETSYMBOLID_FUNC(View)
  #undef DBSYMUTL_MAKE_GETSYMBOLID_FUNC

  inline OdTvDbObjectId getPlotstyleId(const OdString& name, const OdTvDbDatabase *pDb)
  {
    if (!pDb) return OdTvDbObjectId::kNull;
    OdTvDbDictionaryPtr pDic = pDb->getPlotStyleNameDictionaryId(false).openObject();
    if (!pDic.isNull())
    {
      ODA_ASSERT(!pDic->isOdTvDbObjectIdsInFlux());
      return pDic->getAt(name);
    }
    return OdTvDbObjectId::kNull;
  }

  inline OdTvDbObjectId getMLStyleId(const OdString& name, const OdTvDbDatabase *pDb)
  {
    if (!pDb) return OdTvDbObjectId::kNull;
    OdTvDbDictionaryPtr pDic = pDb->getMLStyleDictionaryId(false).openObject();
    if (!pDic.isNull())
    {
      ODA_ASSERT(!pDic->isOdTvDbObjectIdsInFlux());
      return pDic->getAt(name);
    }
    return OdTvDbObjectId::kNull;
  }

  inline OdTvDbObjectId getTableStyleId(const OdString& name, const OdTvDbDatabase *pDb)
  {
    if (!pDb) return OdTvDbObjectId::kNull;
    OdTvDbDictionaryPtr pDic = pDb->getTableStyleDictionaryId(false).openObject();
    if (!pDic.isNull())
    {
      ODA_ASSERT(!pDic->isOdTvDbObjectIdsInFlux());
      return pDic->getAt(name);
    }
    return OdTvDbObjectId::kNull;
  }

  inline OdTvDbObjectId getMLeaderStyleId(const OdString& name, const OdTvDbDatabase *pDb)
  {
    if (!pDb) return OdTvDbObjectId::kNull;
    OdTvDbDictionaryPtr pDic = pDb->getMLeaderStyleDictionaryId(false).openObject();
    if (!pDic.isNull())
    {
      ODA_ASSERT(!pDic->isOdTvDbObjectIdsInFlux());
      return pDic->getAt(name);
    }
    return OdTvDbObjectId::kNull;
  }

  inline OdTvDbObjectId getVisualStyleId(const OdString& name, const OdTvDbDatabase *pDb)
  {
    if (!pDb) return OdTvDbObjectId::kNull;
    OdTvDbDictionaryPtr pDic = pDb->getVisualStyleDictionaryId(false).openObject();
    if (!pDic.isNull())
    {
      ODA_ASSERT(!pDic->isOdTvDbObjectIdsInFlux());
      return pDic->getAt(name);
    }
    return OdTvDbObjectId::kNull;
  }

  inline const OdString& linetypeByLayerName()
  { return  tv_byLayerNameStr; }

  inline bool isLinetypeByLayerName(const OdString& name)
  { return !odStrICmp(name, linetypeByLayerName()); }

  inline const OdString& linetypeByBlockName()
  { return  tv_byBlockNameStr; }

  inline bool isLinetypeByBlockName(const OdString& name)
  { return !odStrICmp(name, linetypeByBlockName()); }

  inline const OdString& linetypeContinuousName()
  { return  tv_linetypeContinuousNameStr; }

  inline bool isLinetypeContinuousName(const OdString& name)
  { return !odStrICmp(name, linetypeContinuousName()); }

  inline const OdString& layerZeroName()
  { return  tv_layerZeroNameStr; }

  inline bool isLayerZeroName(const OdString& name)
  { return !odStrICmp(name, layerZeroName()); }

  inline const OdString& layerDefpointsName()
  { return  tv_layerDefpointsNameStr; }

  inline bool isLayerDefpointsName(const OdString& name)
  { return !odStrICmp(name, layerDefpointsName()); }

  inline const OdString& textStyleStandardName()
  { return tv_standardStr; }

  inline const OdString& MLineStyleStandardName()
  { return tv_standardStr; }

  inline bool isMLineStandardName(const OdString& name)
  { return !odStrICmp(name, MLineStyleStandardName()); }

  inline const OdString& dimStyleStandardName(OdDb::MeasurementValue measurement)
  { return measurement == OdDb::kEnglish ? tv_standardStr : tv_metricDimStandardStr; }

  inline const OdString& viewportActiveName()
  { return tv_viewportActiveNameStr; }

  inline bool isViewportActiveName(const OdString& name)
  { return !odStrICmp(name, viewportActiveName()); }

  inline bool isTextStyleStandardName(const OdString& name)
  { return !odStrICmp(name, textStyleStandardName()); }

  TOOLKIT_EXPORT const OdTvDbObjectId& textStyleStandardId(const OdTvDbDatabase* pDb);
	TOOLKIT_EXPORT const OdTvDbObjectId& dimStyleStandardId(const OdTvDbDatabase* pDb);
  TOOLKIT_EXPORT const OdTvDbObjectId  MLineStyleStandardId(const OdTvDbDatabase* pDb);
  // Returns layer Id for given name. Creates new layer if it's missing
  TOOLKIT_EXPORT const OdTvDbObjectId  getLayerId(OdTvDbDatabase* pDb, const OdString& strLayer);

  inline const OdString& blockModelSpaceName(OdDb::DwgVersion version = OdDb::kDHL_CURRENT)
  { return version <= OdDb::vAC12 ? tv_modelSpaceStr_R12 : tv_modelSpaceStr; }

  inline bool isBlockModelSpaceName(const OdString& pN, OdDb::DwgVersion version = OdDb::kDHL_CURRENT)
  { return odStrICmp(pN, blockModelSpaceName(version)) == 0; }

  inline const OdString& blockPaperSpaceName(OdDb::DwgVersion version = OdDb::kDHL_CURRENT)
  { return version <= OdDb::vAC12 ? tv_paperSpaceStr_R12 : tv_paperSpaceStr; }

  inline bool isBlockPaperSpaceName(const OdString& pN, OdDb::DwgVersion version = OdDb::kDHL_CURRENT)
  { return odStrICmp(pN, blockPaperSpaceName(version)) == 0; }

  inline const OdString& plotStyleNormalName()
  { return tv_plotStyleNormalNameStr;}

  inline const OdString& TableStyleStandardName()
  { return tv_standardStr; }

  inline bool isTableStandardName(const OdString& name)
  { return !odStrICmp(name, TableStyleStandardName()); }

  inline const OdString& MLeaderStyleStandardName()
  { return tv_standardStr; }

  inline bool isMLeaderStandardName(const OdString& name)
  { return !odStrICmp(name, MLeaderStyleStandardName()); }

  inline const OdString& DetailViewStyleStandardName(OdTvDbDatabase* pDb)
  {
    ODA_ASSERT_ONCE(pDb);
    return (pDb && pDb->getMEASUREMENT() == OdDb::kMetric) ? tv_standardMetricDictStr : tv_standardImperialDictStr;
  }

  inline bool isDetailViewStyleStandardName(OdTvDbDatabase* pDb, const OdString& name)
  { 
    return !odStrICmp(name, DetailViewStyleStandardName(pDb)); 
  }

  inline const OdString& SectionViewStyleStandardName(OdTvDbDatabase* pDb)
  {
    return DetailViewStyleStandardName(pDb);
  }

  inline bool isSectionViewStyleStandardName(OdTvDbDatabase* pDb, const OdString& name)
  { 
    return !odStrICmp(name, SectionViewStyleStandardName(pDb)); 
  }
}
// namespace OdTvDbSymUtil

#include "TD_PackPop.h"

#endif // DBSYMUTL_DEFINED

