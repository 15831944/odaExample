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

#include "DgDatabaseProperties.h"
#include "DgColorTable.h"
#include "DgTable.h"

//-----------------------------------------------------------------------------------------------------------------------
//                                          property:LevelTableId
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseLevelTableIdProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  OdDgLevelTablePtr pLevelTable = pObj->getLevelTable();

  OdDgElementId idLevelTable;

  if (!pLevelTable.isNull())
    idLevelTable = pLevelTable->elementId();

  value = idLevelTable;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property:LevelFilterTableId
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseLevelFilterTableIdProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  OdDgLevelFilterTablePtr pLevelFilterTable = pObj->getLevelFilterTable();

  OdDgElementId idLevelFilterTable;

  if (!pLevelFilterTable.isNull())
    idLevelFilterTable = pLevelFilterTable->elementId();

  value = idLevelFilterTable;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property:FontTableId
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseFontTableIdProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  OdDgFontTablePtr pTable = pObj->getFontTable();

  OdDgElementId idTable;

  if (!pTable.isNull())
    idTable = pTable->elementId();

  value = idTable;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property:TextStyleTableId
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseTextStyleTableIdProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  OdDgTextStyleTablePtr pTable = pObj->getTextStyleTable();

  OdDgElementId idTable;

  if (!pTable.isNull())
    idTable = pTable->elementId();

  value = idTable;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property:LineStyleTableId
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseLineStyleTableIdProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  OdDgLineStyleTablePtr pTable = pObj->getLineStyleTable();

  OdDgElementId idTable;

  if (!pTable.isNull())
    idTable = pTable->elementId();

  value = idTable;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property:Models
//-----------------------------------------------------------------------------------------------------------------------

OdRxValueIteratorPtr OdDgDatabaseModelsProperty::subNewValueIterator(const OdRxObject* pO) const
{
  OdRxValueIteratorPtr res;
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (!pDb.isNull())
  {
    OdDgModelTablePtr pTable = pDb->getModelTable(OdDg::kForRead);

    res = OdRxObjectImpl<OdDgElementIdValueIterator>::createObject();
    ((OdDgElementIdValueIterator*)res.get())->m_pIter = pTable->createIterator();
    ((OdDgElementIdValueIterator*)res.get())->m_bAllowNull = false;
  }
  return res;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseModelsProperty::subTryGetCount(const OdRxObject* pO, int& count) const
{
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (pDb.isNull())
    return eNotApplicable;

  OdDgModelTablePtr pTable = pDb->getModelTable(OdDg::kForRead);

  if (pTable.isNull())
    return eNotApplicable;

  int N = 0;

  for (OdDgElementIteratorPtr it = pTable->createIterator(); !it->done(); it->step())
    ++N;
  count = N;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property:MajorVersion
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseMajorVersionProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  value = pObj->getMajorVersion();
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property:MinorVersion
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseMinorVersionProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  value = pObj->getMinorVersion();
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property:FileName
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseFileNameProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  value = pObj->getFilename();
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property:ColorPalette
//-----------------------------------------------------------------------------------------------------------------------

ODDG_DEFINE_RX_VALUE_ARRAY_ITERATOR(OdCmEntityColor);

OdRxValueIteratorPtr OdDgDatabaseColorPaletteProperty::subNewValueIterator(const OdRxObject* pO) const
{
  OdRxValueIteratorPtr res;
  res = OdRxObjectImpl<OdRxOdCmEntityColorValueIterator>::createObject();

  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  const ODCOLORREF* pPalette = OdDgColorTable::currentPalette(pDb);

  if (pPalette)
  {
    OdArray<OdCmEntityColor> arrPalette;
    arrPalette.resize(256);

    for (OdUInt32 i = 0; i < 256; i++)
    {
      OdCmEntityColor curColor;
      curColor.setRGB(ODGETRED(pPalette[i]), ODGETGREEN(pPalette[i]), ODGETBLUE(pPalette[i]));
      arrPalette[i] = curColor;
    }

    ((OdRxOdCmEntityColorValueIterator*)res.get())->init(arrPalette, 0);
  }
  return res;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseColorPaletteProperty::subTryGetCount(const OdRxObject* pO, int& count) const
{
  count = 256;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property:MaterialTableId
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseMaterialTableIdProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  OdDgMaterialTablePtr pMaterialTable = pObj->getMaterialTable();

  OdDgElementId idMatTable;

  if (!pMaterialTable.isNull())
    idMatTable = pMaterialTable->elementId();

  value = idMatTable;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property:DisplayStyleTableId
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseDisplayStyleTableIdProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  OdDgDisplayStyleTablePtr pDSTable = pObj->getDisplayStyleTable(OdDg::kForRead);

  OdDgElementId idDSTable;

  if (!pDSTable.isNull())
    idDSTable = pDSTable->elementId();

  value = idDSTable;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property:SharedCellDefinitions
//-----------------------------------------------------------------------------------------------------------------------

OdRxValueIteratorPtr OdDgDatabaseSharedCellDefinitionsProperty::subNewValueIterator(const OdRxObject* pO) const
{
  OdRxValueIteratorPtr res;
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (!pDb.isNull())
  {
    OdDgSharedCellDefinitionTablePtr pTable = pDb->getSharedCellDefinitionTable(OdDg::kForRead);

    res = OdRxObjectImpl<OdDgElementIdValueIterator>::createObject();
    ((OdDgElementIdValueIterator*)res.get())->m_pIter = pTable->createIterator();
    ((OdDgElementIdValueIterator*)res.get())->m_bAllowNull = false;
  }
  return res;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSharedCellDefinitionsProperty::subTryGetCount(const OdRxObject* pO, int& count) const
{
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (pDb.isNull())
    return eNotApplicable;

  OdDgSharedCellDefinitionTablePtr pTable = pDb->getSharedCellDefinitionTable(OdDg::kForRead);

  if (pTable.isNull())
    return eNotApplicable;

  int N = 0;

  for (OdDgElementIteratorPtr it = pTable->createIterator(); !it->done(); it->step())
    ++N;
  count = N;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property:RetainOriginalThumbnailBitmap
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseRetainOriginalThumbnailBitmapProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getRetainOriginalThumbnailBitmap();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseRetainOriginalThumbnailBitmapProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setRetainOriginalThumbnailBitmap(*rxvalue_cast<bool>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property:DimStyleTableId
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseDimStyleTableIdProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  OdDgDimStyleTablePtr pDimStyleTable = pObj->getDimStyleTable();

  OdDgElementId idDimStyleTable;

  if (!pDimStyleTable.isNull())
    idDimStyleTable = pDimStyleTable->elementId();

  value = idDimStyleTable;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: MultilineStyleTableId
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseMultilineStyleTableIdProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  OdDgMultilineStyleTablePtr pMultilineStyleTable = pObj->getMultilineStyleTable();

  OdDgElementId idMultilineStyleTable;

  if (!pMultilineStyleTable.isNull())
    idMultilineStyleTable = pMultilineStyleTable->elementId();

  value = idMultilineStyleTable;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: RegApps
//-----------------------------------------------------------------------------------------------------------------------

OdRxValueIteratorPtr OdDgDatabaseRegAppsProperty::subNewValueIterator(const OdRxObject* pO) const
{
  OdRxValueIteratorPtr res;
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (!pDb.isNull())
  {
    OdDgRegAppTablePtr pTable = pDb->getRegAppTable(OdDg::kForRead);

    res = OdRxObjectImpl<OdDgElementIdValueIterator>::createObject();
    ((OdDgElementIdValueIterator*)res.get())->m_pIter = pTable->createIterator();
    ((OdDgElementIdValueIterator*)res.get())->m_bAllowNull = false;
  }
  return res;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseRegAppsProperty::subTryGetCount(const OdRxObject* pO, int& count) const
{
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (pDb.isNull())
    return eNotApplicable;

  OdDgRegAppTablePtr pTable = pDb->getRegAppTable(OdDg::kForRead);

  if (pTable.isNull())
    return eNotApplicable;

  int N = 0;

  for (OdDgElementIteratorPtr it = pTable->createIterator(); !it->done(); it->step())
    ++N;
  count = N;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ViewGroups
//-----------------------------------------------------------------------------------------------------------------------

OdRxValueIteratorPtr OdDgDatabaseViewGroupsProperty::subNewValueIterator(const OdRxObject* pO) const
{
  OdRxValueIteratorPtr res;
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (!pDb.isNull())
  {
    OdDgViewGroupTablePtr pTable = pDb->getViewGroupTable(OdDg::kForRead);

    res = OdRxObjectImpl<OdDgElementIdValueIterator>::createObject();
    ((OdDgElementIdValueIterator*)res.get())->m_pIter = pTable->createIterator();
    ((OdDgElementIdValueIterator*)res.get())->m_bAllowNull = false;
  }
  return res;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseViewGroupsProperty::subTryGetCount(const OdRxObject* pO, int& count) const
{
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (pDb.isNull())
    return eNotApplicable;

  OdDgViewGroupTablePtr pTable = pDb->getViewGroupTable(OdDg::kForRead);

  if (pTable.isNull())
    return eNotApplicable;

  int N = 0;

  for (OdDgElementIteratorPtr it = pTable->createIterator(); !it->done(); it->step())
    ++N;
  count = N;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: NamedViews
//-----------------------------------------------------------------------------------------------------------------------

OdRxValueIteratorPtr OdDgDatabaseNamedViewsProperty::subNewValueIterator(const OdRxObject* pO) const
{
  OdRxValueIteratorPtr res;
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (!pDb.isNull())
  {
    OdDgNamedViewTablePtr pTable = pDb->getNamedViewTable(OdDg::kForRead);

    res = OdRxObjectImpl<OdDgElementIdValueIterator>::createObject();
    ((OdDgElementIdValueIterator*)res.get())->m_pIter = pTable->createIterator();
    ((OdDgElementIdValueIterator*)res.get())->m_bAllowNull = false;
  }
  return res;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseNamedViewsProperty::subTryGetCount(const OdRxObject* pO, int& count) const
{
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (pDb.isNull())
    return eNotApplicable;

  OdDgNamedViewTablePtr pTable = pDb->getNamedViewTable(OdDg::kForRead);

  if (pTable.isNull())
    return eNotApplicable;

  int N = 0;

  for (OdDgElementIteratorPtr it = pTable->createIterator(); !it->done(); it->step())
    ++N;
  count = N;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: PrintStyles
//-----------------------------------------------------------------------------------------------------------------------

OdRxValueIteratorPtr OdDgDatabasePrintStylesProperty::subNewValueIterator(const OdRxObject* pO) const
{
  OdRxValueIteratorPtr res;
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (!pDb.isNull())
  {
    OdDgPrintStyleTablePtr pTable = pDb->getPrintStyleTable(OdDg::kForRead);

    res = OdRxObjectImpl<OdDgElementIdValueIterator>::createObject();
    ((OdDgElementIdValueIterator*)res.get())->m_pIter = pTable->createIterator();
    ((OdDgElementIdValueIterator*)res.get())->m_bAllowNull = false;
  }
  return res;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabasePrintStylesProperty::subTryGetCount(const OdRxObject* pO, int& count) const
{
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (pDb.isNull())
    return eNotApplicable;

  OdDgPrintStyleTablePtr pTable = pDb->getPrintStyleTable(OdDg::kForRead);

  if (pTable.isNull())
    return eNotApplicable;

  int N = 0;

  for (OdDgElementIteratorPtr it = pTable->createIterator(); !it->done(); it->step())
    ++N;
  count = N;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ModelTableId
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseModelTableIdProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  OdDgModelTablePtr pModelTable = pObj->getModelTable();

  OdDgElementId idModelTable;

  if (!pModelTable.isNull())
    idModelTable = pModelTable->elementId();

  value = idModelTable;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: TagDefinitions
//-----------------------------------------------------------------------------------------------------------------------

OdRxValueIteratorPtr OdDgDatabaseTagDefinitionsProperty::subNewValueIterator(const OdRxObject* pO) const
{
  OdRxValueIteratorPtr res;
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (!pDb.isNull())
  {
    OdDgTagDefinitionSetTablePtr pTable = pDb->getTagDefinitionSetTable(OdDg::kForRead);

    res = OdRxObjectImpl<OdDgElementIdValueIterator>::createObject();
    ((OdDgElementIdValueIterator*)res.get())->m_pIter = pTable->createIterator();
    ((OdDgElementIdValueIterator*)res.get())->m_bAllowNull = false;
  }
  return res;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseTagDefinitionsProperty::subTryGetCount(const OdRxObject* pO, int& count) const
{
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (pDb.isNull())
    return eNotApplicable;

  OdDgTagDefinitionSetTablePtr pTable = pDb->getTagDefinitionSetTable(OdDg::kForRead);

  if (pTable.isNull())
    return eNotApplicable;

  int N = 0;

  for (OdDgElementIteratorPtr it = pTable->createIterator(); !it->done(); it->step())
    ++N;
  count = N;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ElementTemplates
//-----------------------------------------------------------------------------------------------------------------------

OdRxValueIteratorPtr OdDgDatabaseElementTemplatesProperty::subNewValueIterator(const OdRxObject* pO) const
{
  OdRxValueIteratorPtr res;
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (!pDb.isNull())
  {
    OdDgElementTemplateTablePtr pTable = pDb->getElementTemplateTable(OdDg::kForRead);

    res = OdRxObjectImpl<OdDgElementIdValueIterator>::createObject();
    ((OdDgElementIdValueIterator*)res.get())->m_pIter = pTable->createIterator();
    ((OdDgElementIdValueIterator*)res.get())->m_bAllowNull = false;
  }
  return res;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseElementTemplatesProperty::subTryGetCount(const OdRxObject* pO, int& count) const
{
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (pDb.isNull())
    return eNotApplicable;

  OdDgElementTemplateTablePtr pTable = pDb->getElementTemplateTable(OdDg::kForRead);

  if (pTable.isNull())
    return eNotApplicable;

  int N = 0;

  for (OdDgElementIteratorPtr it = pTable->createIterator(); !it->done(); it->step())
    ++N;
  count = N;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: LinkSets
//-----------------------------------------------------------------------------------------------------------------------

OdRxValueIteratorPtr OdDgDatabaseLinkSetsProperty::subNewValueIterator(const OdRxObject* pO) const
{
  OdRxValueIteratorPtr res;
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (!pDb.isNull())
  {
    OdDgLinkSetTablePtr pTable = pDb->getLinkSetTable(OdDg::kForRead);

    res = OdRxObjectImpl<OdDgElementIdValueIterator>::createObject();
    ((OdDgElementIdValueIterator*)res.get())->m_pIter = pTable->createIterator();
    ((OdDgElementIdValueIterator*)res.get())->m_bAllowNull = false;
  }
  return res;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseLinkSetsProperty::subTryGetCount(const OdRxObject* pO, int& count) const
{
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (pDb.isNull())
    return eNotApplicable;

  OdDgLinkSetTablePtr pTable = pDb->getLinkSetTable(OdDg::kForRead);

  if (pTable.isNull())
    return eNotApplicable;

  int N = 0;

  for (OdDgElementIteratorPtr it = pTable->createIterator(); !it->done(); it->step())
    ++N;
  count = N;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property:NonModelElementCollection
//-----------------------------------------------------------------------------------------------------------------------

OdRxValueIteratorPtr OdDgDatabaseNonModelElementCollectionProperty::subNewValueIterator(const OdRxObject* pO) const
{
  OdRxValueIteratorPtr res;
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (!pDb.isNull())
  {
    OdDgNonModelElementCollectionPtr pCollection = pDb->getNonModelElementCollection(OdDg::kForRead);

    res = OdRxObjectImpl<OdDgElementIdValueIterator>::createObject();
    ((OdDgElementIdValueIterator*)res.get())->m_pIter = pCollection->createIterator();
    ((OdDgElementIdValueIterator*)res.get())->m_bAllowNull = false;
  }
  return res;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseNonModelElementCollectionProperty::subTryGetCount(const OdRxObject* pO, int& count) const
{
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (pDb.isNull())
    return eNotApplicable;

  OdDgNonModelElementCollectionPtr pCollection = pDb->getNonModelElementCollection(OdDg::kForRead);

  if (pCollection.isNull())
    return eNotApplicable;

  int N = 0;

  for (OdDgElementIteratorPtr it = pCollection->createIterator(); !it->done(); it->step())
    ++N;
  count = N;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: EnvironmentMaps
//-----------------------------------------------------------------------------------------------------------------------

ODDG_DEFINE_RX_VALUE_ARRAY_ITERATOR(OdDgEnvironmentMap);

OdRxValueIteratorPtr OdDgDatabaseEnvironmentMapsProperty::subNewValueIterator(const OdRxObject* pO) const
{
  OdRxValueIteratorPtr res;
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);
  if (!pDb.isNull())
  {
    OdDgEnvironmentMapTablePtr pTable = pDb->getEnvironmentMapTable(OdDg::kForRead);

    OdArray<OdDgEnvironmentMap> arrEnvironmentMap;

    if( !pTable.isNull() )
    {
      const OdUInt32 mapCount = pTable->getMapCount();
      arrEnvironmentMap.resize(mapCount);

      for (OdUInt32 i = 0; i < mapCount; i++)
      {
        OdDgEnvironmentMap pEnvMap = pTable->getMapAt(i);
        arrEnvironmentMap[i] = pEnvMap;
      }
    }

    res = OdRxObjectImpl<OdRxOdDgEnvironmentMapValueIterator>::createObject();
    ((OdRxOdDgEnvironmentMapValueIterator*)res.get())->init(arrEnvironmentMap, 0);
  }
  return res;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseEnvironmentMapsProperty::subTryGetCount(const OdRxObject* pO, int& count) const
{
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (pDb.isNull())
    return eNotApplicable;

  OdDgEnvironmentMapTablePtr pTable = pDb->getEnvironmentMapTable(OdDg::kForRead);

  if (pTable.isNull())
    count = 0;
  else
    count = pTable->getMapCount();

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: PrototypeElements
//-----------------------------------------------------------------------------------------------------------------------

OdRxValueIteratorPtr OdDgDatabasePrototypeElementsProperty::subNewValueIterator(const OdRxObject* pO) const
{
  OdRxValueIteratorPtr res;
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (!pDb.isNull())
  {
    OdDgPrototypeElementTablePtr pTable = pDb->getPrototypeElementTable(OdDg::kForRead);

    res = OdRxObjectImpl<OdDgElementIdValueIterator>::createObject();
    ((OdDgElementIdValueIterator*)res.get())->m_pIter = pTable->createIterator();
    ((OdDgElementIdValueIterator*)res.get())->m_bAllowNull = false;
  }
  return res;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabasePrototypeElementsProperty::subTryGetCount(const OdRxObject* pO, int& count) const
{
  OdDgDatabasePtr pDb = OdDgDatabase::cast(pO);

  if (pDb.isNull())
    return eNotApplicable;

  OdDgPrototypeElementTablePtr pTable = pDb->getPrototypeElementTable(OdDg::kForRead);

  if (pTable.isNull())
    return eNotApplicable;

  int N = 0;

  for (OdDgElementIteratorPtr it = pTable->createIterator(); !it->done(); it->step())
    ++N;
  count = N;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: DictionaryTableId
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseDictionaryTableIdProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  OdDgDictionaryTablePtr pDictionaryTable = pObj->getDictionaryTable();

  OdDgElementId idDictionaryTable;

  if (!pDictionaryTable.isNull())
    idDictionaryTable = pDictionaryTable->elementId();

  value = idDictionaryTable;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ControlFlags
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseControlFlagsProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  value = pObj->getControlFlags();
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: LockFlags
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseLockFlagsProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  value = (OdUInt16)(pObj->getLockFlags());
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ExtLockFlags
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseExtLockFlagsProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  value = pObj->getExtLockFlags();
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: SaveMaterialAssignmentTableFileFlag
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSaveMaterialAssignmentTableFileFlagProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getSaveMaterialAssignmentTableFileFlag();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSaveMaterialAssignmentTableFileFlagProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setSaveMaterialAssignmentTableFileFlag(*rxvalue_cast<bool>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ActAngle
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActAngleProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getActAngle();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActAngleProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setActAngle(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: AngleRnd
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAngleRndProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getAngleRnd();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAngleRndProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setAngleRnd(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: XActScale
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseXActScaleProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getXActScale();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseXActScaleProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setXActScale(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: YActScale
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseYActScaleProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getYActScale();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseYActScaleProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setYActScale(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ZActScale
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseZActScaleProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getZActScale();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseZActScaleProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setZActScale(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: RoundScale
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseRoundScaleProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getRoundScale();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseRoundScaleProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setRoundScale(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: Azimuth
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAzimuthProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getAzimuth();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAzimuthProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setAzimuth(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ExtMin
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseExtMinProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getExtMin();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseExtMinProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setExtMin(*rxvalue_cast<OdGePoint3d>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ExtMax
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseExtMaxProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getExtMax();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseExtMaxProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setExtMax(*rxvalue_cast<OdGePoint3d>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ActiveLevelEntryId
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActiveLevelEntryIdProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getActiveLevelEntryId();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActiveLevelEntryIdProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setActiveLevelEntryId(*rxvalue_cast<OdUInt32>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ActiveLineStyleEntryId
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActiveLineStyleEntryIdProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getActiveLineStyleEntryId();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActiveLineStyleEntryIdProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setActiveLineStyleEntryId(*rxvalue_cast<OdInt32>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ActiveLineWeight
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActiveLineWeightProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = (OdDb::LineWeight)(pObj->getActiveLineWeight());
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActiveLineWeightProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setActiveLineWeight((OdUInt32)(*rxvalue_cast<OdDb::LineWeight>(&value)));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ActiveColorIndex
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActiveColorIndexProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getActiveColorIndex();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActiveColorIndexProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setActiveColorIndex(*rxvalue_cast<OdUInt32>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: FillColor
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseFillColorProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const //TODO resolve this property
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  OdCmEntityColor cmColor;

  OdUInt32 uIndex = pObj->getFillColorIndex();

  if (uIndex == OdDg::kColorByLevel)
  {
    cmColor.setColorMethod(OdCmEntityColor::kByLayer);
  }
  else if (uIndex == OdDg::kColorByCell)
    cmColor.setColorMethod(OdCmEntityColor::kByBlock);
  else if (uIndex < 256)
  {
    OdCmEntityColor::setDgnColorIndex(&uIndex, uIndex);
    cmColor.setColor(uIndex);
  }
  else
  {
    OdDgColorTablePtr pColorTable = pObj->getColorTable();

    OdDgCmColor fillColor;
    pColorTable->getExtendedColor(pObj, uIndex, fillColor);
    ODCOLORREF rgbColor = fillColor.color();
    cmColor.setColorMethod(OdCmEntityColor::kByColor);
    cmColor.setRed(ODGETRED(rgbColor));
    cmColor.setGreen(ODGETGREEN(rgbColor));
    cmColor.setBlue(ODGETBLUE(rgbColor));
  }

  value = cmColor;

  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseFillColorProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  const OdCmEntityColor* pColor = rxvalue_cast<OdCmEntityColor>(&value);

  switch (pColor->colorMethod())
  {
  case OdCmEntityColor::kByLayer:
    pObj->setFillColorIndex(OdDg::kColorByLevel); break;
  case OdCmEntityColor::kByBlock:
    pObj->setFillColorIndex(OdDg::kColorByCell); break;
  case OdCmEntityColor::kByACI:
    pObj->setFillColorIndex(pColor->colorIndex()); break;
  case OdCmEntityColor::kByDgnIndex:
    pObj->setFillColorIndex(pColor->colorIndex()); break;
  case OdCmEntityColor::kByPen:
    pObj->setFillColorIndex(pColor->colorIndex()); break;
  case OdCmEntityColor::kByColor:
  {
    ODCOLORREF curColor = ODRGB(pColor->red(), pColor->green(), pColor->blue());
    pObj->setFillColorIndex(curColor);
  }break;
  }

  return eOk;

}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ActiveProps
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActivePropsProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getActiveProps();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActivePropsProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setActiveProps(*rxvalue_cast<OdUInt16>(&value));
  return eOk;
}
//
//-----------------------------------------------------------------------------------------------------------------------
//                                          property: LineStyleInfo
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseLineStyleInfoProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getLineStyle();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseLineStyleInfoProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setLineStyle(*rxvalue_cast<OdDgLineStyleInfo>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: LineStyleScale
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseLineStyleScaleProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getLineStyleScale();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseLineStyleScaleProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setLineStyleScale(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: MultiLineFlags
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseMultiLineFlagsProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getMultiLineFlags();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseMultiLineFlagsProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setMultiLineFlags(*rxvalue_cast<OdUInt16>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ActiveTextStyleEntryId
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActiveTextStyleEntryIdProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getActiveTextStyleEntryId();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActiveTextStyleEntryIdProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setActiveTextStyleEntryId(*rxvalue_cast<OdUInt32>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: TextScaleLock
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseTextScaleLockProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getTextScaleLock();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseTextScaleLockProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setTextScaleLock(*rxvalue_cast<OdUInt16>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ActiveViewGroupId
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActiveViewGroupIdProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getActiveViewGroupId();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActiveViewGroupIdProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setActiveViewGroupId(*rxvalue_cast<OdDgElementId>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ActiveModelId
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActiveModelIdProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getActiveModelId();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActiveModelIdProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setActiveModelId(*rxvalue_cast<OdDgElementId>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: AngleFormat
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAngleFormatProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getAngleFormat();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAngleFormatProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setAngleFormat(*rxvalue_cast<OdDgDimTextFormat::AngleValueDisplayMode>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: AngleReadoutPrec
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAngleReadoutPrecProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getAngleReadoutPrec();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAngleReadoutPrecProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setAngleReadoutPrec(*rxvalue_cast<OdDg::OdDgDecimalAccuracy>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: AngleReadoutDirectionMode
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAngleReadoutDirectionModeProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getAngleReadoutDirectionMode();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAngleReadoutDirectionModeProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setAngleReadoutDirectionMode(*rxvalue_cast<OdDg::OdDgAngleReadoutDirectionMode>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: AngleReadoutBaseAngle
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAngleReadoutBaseAngleProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getAngleReadoutBaseAngle();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAngleReadoutBaseAngleProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setAngleReadoutBaseAngle(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: AngleReadoutClockwiseFlag
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAngleReadoutClockwiseFlagProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getAngleReadoutClockwiseFlag();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAngleReadoutClockwiseFlagProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setAngleReadoutClockwiseFlag(*rxvalue_cast<bool>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: TentativeMode
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseTentativeModeProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getTentativeMode();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseTentativeModeProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setTentativeMode(*rxvalue_cast<OdUInt16>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: TentativeSubMode
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseTentativeSubModeProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getTentativeSubMode();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseTentativeSubModeProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setTentativeSubMode(*rxvalue_cast<OdUInt16>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: KeyPointDividend
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseKeyPointDividendProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getKeyPointDividend();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseKeyPointDividendProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setKeyPointDividend(*rxvalue_cast<OdUInt16>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: DefaultSnapMode
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseDefaultSnapModeProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getDefaultSnapMode();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseDefaultSnapModeProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setDefaultSnapMode(*rxvalue_cast<OdUInt16>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: SystemClass
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSystemClassProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getSystemClass();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSystemClassProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setSystemClass(*rxvalue_cast<OdUInt16>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: DMRSFlag
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseDMRSFlagProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getDMRSFlag();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseDMRSFlagProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setDMRSFlag(*rxvalue_cast<OdUInt8>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: DMRSLinkageGenerationMode
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseDMRSLinkageGenerationModeProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getDMRSLinkageGenerationMode();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseDMRSLinkageGenerationModeProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setDMRSLinkageGenerationMode(*rxvalue_cast<OdUInt16>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: AutoDimFlags
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAutoDimFlagsProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getAutoDimFlags();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAutoDimFlagsProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setAutoDimFlags(*rxvalue_cast<OdUInt16>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: AssocLockMask
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAssocLockMaskProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getAssocLockMask();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAssocLockMaskProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setAssocLockMask(*rxvalue_cast<OdUInt16>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ActiveCell
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActiveCellProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getActiveCell();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActiveCellProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setActiveCell(*rxvalue_cast<OdString>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ActiveTermCell
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActiveTermCellProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getActiveTermCell();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActiveTermCellProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setActiveTermCell(*rxvalue_cast<OdString>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ActiveTermScale
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActiveTermScaleProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getActiveTermScale();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActiveTermScaleProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setActiveTermScale(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ActivePatternCell
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActivePatternCellProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getActivePatternCell();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActivePatternCellProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setActivePatternCell(*rxvalue_cast<OdString>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ActivePatternScale
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActivePatternScaleProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getActivePatternScale();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActivePatternScaleProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setActivePatternScale(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ActivePatternAngle
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActivePatternAngleProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getActivePatternAngle();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActivePatternAngleProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setActivePatternAngle(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ActivePatternAngle2
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActivePatternAngle2Property::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getActivePatternAngle2();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActivePatternAngle2Property::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setActivePatternAngle2(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ActivePatternRowSpacing
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActivePatternRowSpacingProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getActivePatternRowSpacing();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActivePatternRowSpacingProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setActivePatternRowSpacing(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ActivePatternColumnSpacing
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActivePatternColumnSpacingProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getActivePatternColumnSpacing();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActivePatternColumnSpacingProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setActivePatternColumnSpacing(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: PatternTolerance
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabasePatternToleranceProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getPatternTolerance();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabasePatternToleranceProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setPatternTolerance(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ActivePointType
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActivePointTypeProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getActivePointType();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActivePointTypeProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setActivePointType(*rxvalue_cast<OdUInt32>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ActivePointSymbol
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActivePointSymbolProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getActivePointSymbol();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActivePointSymbolProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setActivePointSymbol(*rxvalue_cast<OdUInt16>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ActivePointCell
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActivePointCellProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getActivePointCell();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseActivePointCellProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setActivePointCell(*rxvalue_cast<OdString>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: AreaPatternAngle
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAreaPatternAngleProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getAreaPatternAngle();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAreaPatternAngleProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setAreaPatternAngle(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: AreaPatternRowSpacing
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAreaPatternRowSpacingProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getAreaPatternRowSpacing();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAreaPatternRowSpacingProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setAreaPatternRowSpacing(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: AreaPatternColumnSpacing
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAreaPatternColumnSpacingProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getAreaPatternColumnSpacing();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAreaPatternColumnSpacingProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setAreaPatternColumnSpacing(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ReservedCell
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseReservedCellProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getReservedCell();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseReservedCellProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setReservedCell(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ZRange2dLow
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseZRange2dLowProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getZRange2dLow();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseZRange2dLowProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setZRange2dLow(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ZRange2dHigh
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseZRange2dHighProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getZRange2dHigh();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseZRange2dHighProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setZRange2dHigh(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: StreamDelta
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseStreamDeltaProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getStreamDelta();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseStreamDeltaProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setStreamDelta(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: StreamTolerance
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseStreamToleranceProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getStreamTolerance();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseStreamToleranceProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setStreamTolerance(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: AngleTolerance
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAngleToleranceProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getAngleTolerance();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAngleToleranceProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setAngleTolerance(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: AreaTolerance
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAreaToleranceProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getAreaTolerance();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAreaToleranceProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setAreaTolerance(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: HighlightColorIndex
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseHighlightColorIndexProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getHighlightColorIndex();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseHighlightColorIndexProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setHighlightColorIndex(*rxvalue_cast<OdUInt32>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: XorColorIndex
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseXorColorIndexProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getXorColorIndex();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseXorColorIndexProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setXorColorIndex(*rxvalue_cast<OdUInt32>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: AxisLockAngle
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAxisLockAngleProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getAxisLockAngle();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAxisLockAngleProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setAxisLockAngle(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: AxisLockOrigin
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAxisLockOriginProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getAxisLockOrigin();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAxisLockOriginProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setAxisLockOrigin(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ChamferDist1
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseChamferDist1Property::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getChamferDist1();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseChamferDist1Property::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setChamferDist1(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ChamferDist2
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseChamferDist2Property::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getChamferDist2();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseChamferDist2Property::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setChamferDist2(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: AutochainTolerance
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAutochainToleranceProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getAutochainTolerance();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAutochainToleranceProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setAutochainTolerance(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ConslineDistance
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseConslineDistanceProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getConslineDistance();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseConslineDistanceProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setConslineDistance(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ArcRadius
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseArcRadiusProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getArcRadius();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseArcRadiusProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setArcRadius(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ArcLength
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseArcLengthProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getArcLength();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseArcLengthProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setArcLength(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ConeRadius1
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseConeRadius1Property::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getConeRadius1();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseConeRadius1Property::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setConeRadius1(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ConeRadius2
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseConeRadius2Property::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getConeRadius2();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseConeRadius2Property::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setConeRadius2(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: PolygonRadius
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabasePolygonRadiusProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getPolygonRadius();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabasePolygonRadiusProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setPolygonRadius(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: SurrevAngle
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSurrevAngleProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getSurrevAngle();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSurrevAngleProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setSurrevAngle(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ExtendDistance
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseExtendDistanceProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getExtendDistance();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseExtendDistanceProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setExtendDistance(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: FilletRadius
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseFilletRadiusProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getFilletRadius();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseFilletRadiusProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setFilletRadius(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: CopparDistance
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseCopparDistanceProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getCopparDistance();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseCopparDistanceProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setCopparDistance(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ArrayRowDistance
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseArrayRowDistanceProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getArrayRowDistance();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseArrayRowDistanceProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setArrayRowDistance(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ArrayColumnDistance
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseArrayColumnDistanceProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getArrayColumnDistance();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseArrayColumnDistanceProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setArrayColumnDistance(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ArrayFillAngle
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseArrayFillAngleProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getArrayFillAngle();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseArrayFillAngleProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setArrayFillAngle(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: PointDistance
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabasePointDistanceProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getPointDistance();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabasePointDistanceProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setPointDistance(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: PolygonEdges
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabasePolygonEdgesProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getPolygonEdges();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabasePolygonEdgesProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setPolygonEdges(*rxvalue_cast<OdUInt16>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: PointsBetween
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabasePointsBetweenProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getPointsBetween();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabasePointsBetweenProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setPointsBetween(*rxvalue_cast<OdUInt16>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ArrayNumItems
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseArrayNumItemsProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getArrayNumItems();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseArrayNumItemsProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setArrayNumItems(*rxvalue_cast<OdUInt16>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ArrayNumRows
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseArrayNumRowsProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getArrayNumRows();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseArrayNumRowsProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setArrayNumRows(*rxvalue_cast<OdUInt16>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ArrayNumCols
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseArrayNumColsProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getArrayNumCols();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseArrayNumColsProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setArrayNumCols(*rxvalue_cast<OdUInt16>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ArrayRotate
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseArrayRotateProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getArrayRotate();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseArrayRotateProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setArrayRotate(*rxvalue_cast<OdUInt8>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: BSplineOrder
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseBSplineOrderProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getBSplineOrder();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseBSplineOrderProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setBSplineOrder(*rxvalue_cast<OdUInt8>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: DispAttrType
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseDispAttrTypeProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getDispAttrType();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseDispAttrTypeProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setDispAttrType(*rxvalue_cast<OdUInt8>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: AmbientFlag
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAmbientFlagProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getAmbientFlag();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAmbientFlagProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setAmbientFlag(*rxvalue_cast<bool>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: FlashbulbFlag
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseFlashbulbFlagProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getFlashbulbFlag();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseFlashbulbFlagProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setFlashbulbFlag(*rxvalue_cast<bool>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: SolarFlag
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSolarFlagProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getSolarFlag();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSolarFlagProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setSolarFlag(*rxvalue_cast<bool>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: SolarShadowsFlag
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSolarShadowsFlagProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getSolarShadowsFlag();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSolarShadowsFlagProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setSolarShadowsFlag(*rxvalue_cast<bool>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: SolarShadowResolution
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSolarShadowResolutionProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getSolarShadowResolution();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSolarShadowResolutionProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setSolarShadowResolution(*rxvalue_cast<OdUInt16>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: KeepSolarDirectionFlag
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseKeepSolarDirectionFlagProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getKeepSolarDirectionFlag();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseKeepSolarDirectionFlagProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setKeepSolarDirectionFlag(*rxvalue_cast<bool>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: Latitude
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseLatitudeProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getLatitude();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseLatitudeProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setLatitude(*rxvalue_cast<OdAngleCoordinate>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: Longitude
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseLongitudeProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getLongitude();
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseLongitudeProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setLongitude(*rxvalue_cast<OdAngleCoordinate>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: SolarTime
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSolarTimeProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getSolarTime();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSolarTimeProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setSolarTime(*rxvalue_cast<OdUInt32>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: SolarYear
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSolarYearProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getSolarYear();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSolarYearProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setSolarYear(*rxvalue_cast<OdUInt32>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: GMTOffset
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseGMTOffsetProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getGMTOffset();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseGMTOffsetProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setGMTOffset(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: SolarDirection
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSolarDirectionProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getSolarDirection();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSolarDirectionProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setSolarDirection(*rxvalue_cast<OdGePoint3d>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: SolarVectorOverride
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSolarVectorOverrideProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getSolarVectorOverride();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSolarVectorOverrideProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setSolarVectorOverride(*rxvalue_cast<OdGePoint3d>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: SolarIntensity
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSolarIntensityProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getSolarIntensity();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSolarIntensityProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setSolarIntensity(*rxvalue_cast<OdDgLightColor>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: AmbientIntensity
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAmbientIntensityProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getAmbientIntensity();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseAmbientIntensityProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setAmbientIntensity(*rxvalue_cast<OdDgLightColor>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: FlashIntensity
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseFlashIntensityProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getFlashIntensity();;
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseFlashIntensityProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setFlashIntensity(*rxvalue_cast<OdDgLightColor>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: NearDepthDensity
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseNearDepthDensityProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getNearDepthDensity();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseNearDepthDensityProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setNearDepthDensity(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: FarDepthDensity
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseFarDepthDensityProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getFarDepthDensity();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseFarDepthDensityProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setFarDepthDensity(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: NearDepthDistance
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseNearDepthDistanceProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getNearDepthDistance();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseNearDepthDistanceProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setNearDepthDistance(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: HazeColor
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseHazeColorProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getHazeColor();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseHazeColorProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setHazeColor(*rxvalue_cast<OdDgLightColor>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ShadowTolerance
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseShadowToleranceProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getShadowTolerance();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseShadowToleranceProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setShadowTolerance(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: StrokeTolerance
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseStrokeToleranceProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getStrokeTolerance();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseStrokeToleranceProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setStrokeTolerance(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: MaxPolygonSize
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseMaxPolygonSizeProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getMaxPolygonSize();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseMaxPolygonSizeProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setMaxPolygonSize(*rxvalue_cast<OdInt16>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ArcMinimum
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseArcMinimumProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getArcMinimum();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseArcMinimumProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setArcMinimum(*rxvalue_cast<OdInt16>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ExactHLineAccuracy
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseExactHLineAccuracyProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getExactHLineAccuracy();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseExactHLineAccuracyProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setExactHLineAccuracy(*rxvalue_cast<OdUInt32>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ExactHLineTolerance
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseExactHLineToleranceProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getExactHLineTolerance();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseExactHLineToleranceProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setExactHLineTolerance(*rxvalue_cast<double>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: SelectionHighlightOverride
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSelectionHighlightOverrideProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getSelectionHighlightOverride();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSelectionHighlightOverrideProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setSelectionHighlightOverride(*rxvalue_cast<OdUInt32>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: SelectionHighlightColor
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSelectionHighlightColorProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getSelectionHighlightColor();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseSelectionHighlightColorProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setSelectionHighlightColor(*rxvalue_cast<OdUInt32>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: CellFileName
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseCellFileNameProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getCellFileName();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseCellFileNameProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setCellFileName(*rxvalue_cast<OdString>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: BackgroundFile
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseBackgroundFileProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getBackgroundFile();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseBackgroundFileProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setBackgroundFile(*rxvalue_cast<OdString>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: DesignCenterUnits
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseDesignCenterUnitsProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getDesignCenterUnits();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseDesignCenterUnitsProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setDesignCenterUnits(*rxvalue_cast<OdDg::OdDgDesignCenterUnits>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: NextGraphicGroup
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseNextGraphicGroupProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getNextGraphicGroup();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseNextGraphicGroupProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setNextGraphicGroup(*rxvalue_cast<OdUInt32>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: Handseed
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseHandseedProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getHandseed();
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: LastSaveTime
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseLastSaveTimeProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  OdTimeStamp tmp;
  tmp.setPackedValue((OdUInt64)(pObj->getLastSaveTime()) / 1000);
  value = tmp;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: DefaultModelId
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseDefaultModelIdProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getDefaultModelId();
  return eOk;
}


//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseDefaultModelIdProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  pObj->setDefaultModelId(*rxvalue_cast<OdDgElementId>(&value));
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: OriginalFileVersion
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgDatabaseOriginalFileVersionProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgDatabasePtr pObj = OdDgDatabase::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getOriginalFileVersion();
  return eOk;
}
