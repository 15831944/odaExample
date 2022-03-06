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

#include <OdaCommon.h>
#include "DgnImportImpl.h"
#include <DgDatabase.h>
#include <DgLevelTableRecord.h>
#include "DbSymUtl.h"
#include "DgnImportContext.h"
#include "DgnImportCommon.h"
#include <Gi/GiTextStyle.h>
#include <DbTextStyleTable.h>
#include <DbMlineStyle.h>
#include <DbDictionary.h>
#include "DgMultiline.h"
#include "DgFontTableRecord.h"
#include "DgReferenceAttach.h"

namespace TD_DGN_IMPORT {

struct OdDgImportXRefDescriptor
{
  OdString m_strName;
  OdUInt32 m_uNestedDepth;
  OdDgElementId m_idXRef;
};

typedef std::map<OdUInt32,bool>           OdDgnImportLevelMaskDescriptor;
typedef std::map<OdUInt32,bool>::iterator OdDgnImportLevelMaskDescriptorIterator;

class OdDgnImportContextData
{
public:
  OdDgnImportContextData() :m_bInternalImport(false), m_bImportCurvesOnly(false),
    m_bSkipPatternDraw(false),
    m_bImportInvisible(false), m_bInitPolygonImportModes(false),
    m_3dEllipseImportMode(0), m_2dEllipseImportMode(0),
    m_3dShapeImportMode(1), m_2dShapeImportMode(0),
    m_3dSplineImportMode(1), m_2dSplineImportMode(0),
    m_3dObjectImportMode(0),
    m_bConvertColorIndexToTrueColor(false),
    m_bConvertEmptyDataFieldsToSpaces(true),
    m_bSetLevelVisibilityByLevelMask(false),
    m_bLayerByBlockMode(false),
    m_bLockColorMode(false),
    m_bLockLineStyleMode(false),
    m_bLockLineWeightMode(false),
    m_uLockColorIndex(0),
    m_uLockLineStyle(0),
    m_uLockLineWeight(0),
    m_bImportDgTextAsDbMText(false),
    m_bUseLevelOverride(false),
    m_bCropXRefExtraClipByExtents(true),
    m_bShowNewXRefLevels(false)
  {};

public:
  OdArray<std::map<OdUInt32, OdDgnImportColorIndexDescription> > m_paletteStack;
  std::map<OdUInt32, OdDgnImportColorIndexDescription> m_dgnToDwgColorMap;
  std::map<OdString, OdDbObjectId>                     m_dgnModelToBlockDefMap;
  OdArray<double>                                      m_dGlobalLineScaleStack;
  DgnImporter*                                         m_pDgnImporter;
  bool                                                 m_bInternalImport;
  bool                                                 m_bImportCurvesOnly;
  bool                                                 m_bSkipPatternDraw;
  bool                                                 m_bImportInvisible;
  bool                                                 m_bImportDgTextAsDbMText;
  bool                                                 m_bConvertColorIndexToTrueColor;
  bool                                                 m_bConvertEmptyDataFieldsToSpaces;
  OdArray<OdDgnImportLevelMaskDescriptor>              m_pLevelMaskStack;
  OdDgViewPtr                                          m_pActiveView;
  bool                                                 m_bInitPolygonImportModes;
  OdUInt8                                              m_3dEllipseImportMode;
  OdUInt8                                              m_2dEllipseImportMode;
  OdUInt8                                              m_3dShapeImportMode;
  OdUInt8                                              m_3dObjectImportMode;
  OdUInt8                                              m_2dShapeImportMode;
  OdUInt8                                              m_3dSplineImportMode;
  OdUInt8                                              m_2dSplineImportMode;
  OdArray<OdString>                                      m_arrRscFontNames;
  std::map<OdDbObjectId, OdDgnImportMultilineDescriptor> m_mapMultilineStyles;
  std::map<OdUInt64,OdDbObjectId>                        m_mapTableMLStyleIds;
  std::map<OdDbObjectId, OdDgnImportDimAssocDescriptor>  m_mapDimAssocDescripotors;
  std::map<OdDgElementId, OdDgnImportSymbolHatchDescriptor> m_mapSymbolHatch;
  std::map<OdString, OdUInt32>                           m_mapCellNextBlockIndex;
  OdDbObjectIdArray                                      m_arrCellHeaderIds;
  OdArray<OdDgElementId>                               m_arrNoteCellHeaders;
	bool																								 m_bSetLevelVisibilityByLevelMask;
  bool                                                 m_bLayerByBlockMode;
  bool                                                 m_bLockColorMode;
  bool                                                 m_bLockLineStyleMode;
  bool                                                 m_bLockLineWeightMode;
  OdUInt32                                             m_uLockColorIndex;
  OdUInt32                                             m_uLockLineWeight;
  OdUInt32                                             m_uLockLineStyle;
  std::map< OdString, OdDbObjectId>                    m_mapSharedCellOverrides;
  OdDgElementId                                        m_idActiveXRef;
  OdGeMatrix3d                                         m_matCellTransform;
  OdArray< std::map<OdDgElementId, OdDgElementId> >    m_arrLevelOverrides;
  bool                                                 m_bUseLevelOverride;
  bool                                                 m_bCropXRefExtraClipByExtents;
  bool                                                 m_bShowNewXRefLevels;
  OdDgElementId                                        m_idLevelTableOverride;
  OdArray<OdDgnImportViewFlags>                        m_arrViewFlagsStack;
  std::map<OdDbObjectId, double>                       m_mapScaledBlocks;
};

//==================================================================================
//
//      Implementation of OdDgnImportViewFlags class
//
//==================================================================================

OdDgnImportViewFlags::OdDgnImportViewFlags()
{
  m_bShowTexts = true;
  m_bShowTags = true;
  m_bShowTextNodes = false;
  m_bShowPatterns = true;
  m_bShowLineStyles = true;
  m_bShowLineWeights = true;
  m_bShowFills = true;
  m_bShowConstruction = true;
  m_bShowDimensions = true;
  m_bUseTransparency = true;
  m_bUseLevelSymbology = false;
}

//==================================================================================

OdDgnImportViewFlags::~OdDgnImportViewFlags()
{}

//==================================================================================

void OdDgnImportViewFlags::init(const OdDgView* pView)
{
  if( pView )
  {
    m_bShowTexts          = !pView->getHideTextsFlag();
    m_bShowTags           = pView->getShowTagsFlag();
    m_bShowTextNodes      = pView->getShowTextNodesFlag();
    m_bShowPatterns       = pView->getShowPatternsFlag();
    m_bShowLineStyles     = !pView->getIgnoreLineStylesFlag();
    m_bShowLineWeights    = pView->getShowLineWeightsFlag();
    m_bShowFills          = pView->getShowFillsFlag();
    m_bShowConstruction   = pView->getShowConstructionFlag();
    m_bShowDimensions     = pView->getShowDimensionsFlag();
    m_bUseTransparency    = pView->getUseTransparencyFlag();
    m_bUseLevelSymbology  = pView->getShowLevelSymbologyFlag();
  }
}

//==================================================================================

void OdDgnImportViewFlags::init(const OdDgReferenceAttachmentHeader* pXRef, OdUInt32 uViewIndex, const OdDgnImportViewFlags& defaultValues)
{
  if( !pXRef || !pXRef->getUseViewFlagsFlag() || (uViewIndex > 7))
  {
    m_bShowTexts = defaultValues.m_bShowTexts;
    m_bShowTags = defaultValues.m_bShowTags;
    m_bShowTextNodes = defaultValues.m_bShowTextNodes;
    m_bShowPatterns = defaultValues.m_bShowPatterns;
    m_bShowLineStyles = defaultValues.m_bShowLineStyles;
    m_bShowLineWeights = defaultValues.m_bShowLineWeights;
    m_bShowFills = defaultValues.m_bShowFills;
    m_bShowConstruction = defaultValues.m_bShowConstruction;
    m_bShowDimensions = defaultValues.m_bShowDimensions;
    m_bUseTransparency = defaultValues.m_bUseTransparency;
    m_bUseLevelSymbology = defaultValues.m_bUseLevelSymbology;
  }
  else
  {
    OdDgReferenceAttachmentViewFlags viewFlags = pXRef->getViewFlags(uViewIndex);

    m_bShowTexts = !viewFlags.getHideTextsFlag();
    m_bShowTags = viewFlags.getShowTagsFlag();
    m_bShowTextNodes = viewFlags.getShowTextNodesFlag();
    m_bShowPatterns = viewFlags.getShowPatternsFlag();
    m_bShowLineStyles = !viewFlags.getIgnoreLineStylesFlag();
    m_bShowLineWeights = viewFlags.getShowLineWeightsFlag();
    m_bShowFills = viewFlags.getShowFillsFlag();
    m_bShowConstruction = viewFlags.getShowConstructionFlag();
    m_bShowDimensions = viewFlags.getShowDimensionsFlag();
    m_bUseTransparency = viewFlags.getTransparencyFlag();
    m_bUseLevelSymbology = viewFlags.getShowLevelSymbologyFlag();
  }
}

//==================================================================================

bool OdDgnImportViewFlags::getShowTextsFlag() const
{
  return m_bShowTexts;
}

//==================================================================================

void OdDgnImportViewFlags::setShowTextsFlag(bool bSet)
{
  m_bShowTexts = bSet;
}

//==================================================================================

bool OdDgnImportViewFlags::getShowTagsFlag() const
{
  return m_bShowTags;
}

//==================================================================================

void OdDgnImportViewFlags::setShowTagsFlag(bool bSet)
{
  m_bShowTags = bSet;
}

//==================================================================================

bool OdDgnImportViewFlags::getShowTextNodesFlag() const
{
  return m_bShowTextNodes;
}

//==================================================================================

void OdDgnImportViewFlags::setShowTextNodesFlag(bool bSet)
{
  m_bShowTextNodes = bSet;
}

//==================================================================================

bool OdDgnImportViewFlags::getShowPatternsFlag() const
{
  return m_bShowPatterns;
}

//==================================================================================

void OdDgnImportViewFlags::setShowPatternsFlag(bool bSet)
{
  m_bShowPatterns = bSet;
}

//==================================================================================

bool OdDgnImportViewFlags::getShowLineStylesFlag() const
{
  return m_bShowLineStyles;
}

//==================================================================================

void OdDgnImportViewFlags::setShowLineStylesFlag(bool bSet)
{
  m_bShowLineStyles = bSet;
}

//==================================================================================

bool OdDgnImportViewFlags::getShowLineWeightsFlag() const
{
  return m_bShowLineWeights;
}

//==================================================================================

void OdDgnImportViewFlags::setShowLineWeightsFlag(bool bSet)
{
  m_bShowLineWeights = bSet;
}

//==================================================================================

bool OdDgnImportViewFlags::getShowFillsFlag() const
{
  return m_bShowFills;
}

//==================================================================================

void OdDgnImportViewFlags::setShowFillsFlag(bool bSet)
{
  m_bShowFills = bSet;
}

//==================================================================================

bool OdDgnImportViewFlags::getShowConstructionFlag() const
{
  return m_bShowConstruction;
}

//==================================================================================

void OdDgnImportViewFlags::setShowConstructionFlag(bool bSet)
{
  m_bShowConstruction = bSet;
}

//==================================================================================

bool OdDgnImportViewFlags::getShowDimensionsFlag() const
{
  return m_bShowDimensions;
}

//==================================================================================

void OdDgnImportViewFlags::setShowDimensionsFlag(bool bSet)
{
  m_bShowDimensions = bSet;
}

//==================================================================================

bool OdDgnImportViewFlags::getUseTransparencyFlag() const
{
  return m_bUseTransparency;
}

//==================================================================================

void OdDgnImportViewFlags::setUseTransparencyFlag(bool bSet)
{
  m_bUseTransparency = bSet;
}

//==================================================================================

bool OdDgnImportViewFlags::getUseLevelSymbologyFlag() const
{
  return m_bUseLevelSymbology;
}

//==================================================================================

void OdDgnImportViewFlags::setUseLevelSymbologyFlag(bool bSet)
{
  m_bUseLevelSymbology = bSet;
}

//==================================================================================
//
//      Implementation of OdDgnImportContext class
//
//==================================================================================


OdArray<OdDgnImportContextData>   g_importContextDataArr;
OdArray<OdDgImportXRefDescriptor> g_strXRefNameStack;
OdDgImportXRefDescriptor          g_lastXRefRecord;

static OdDgnImportContextData* getCurrentContext()
{
  if( g_importContextDataArr.size() > 0 )
  {
    return g_importContextDataArr.asArrayPtr() + g_importContextDataArr.size() - 1;
  }
  else
  {
    return NULL;
  }
}

void OdDgnImportContext::pushPalette()
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    pContextData->m_paletteStack.push_back(pContextData->m_dgnToDwgColorMap);
  }
}

void OdDgnImportContext::popPalette()
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData && pContextData->m_paletteStack.size() > 0 )
  {
    pContextData->m_dgnToDwgColorMap = pContextData->m_paletteStack[pContextData->m_paletteStack.size() - 1];
    pContextData->m_paletteStack.removeLast();
  }
}

void OdDgnImportContext::setPalette( OdDgDatabase* pDb )
{
  const ODCOLORREF* pPalette = OdDgColorTable::currentPalette( pDb );

  setPalette( pPalette );
}

void OdDgnImportContext::setPalette( const ODCOLORREF* pPalette )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pPalette && pContextData )
  {
    for( OdUInt32 i = 0; i < 256; i++ )
    {
      ODCOLORREF curDgnColor = pPalette[i];

      OdDgnImportColorIndexDescription curDwgColor;

      if( (i == 0) && ( ((ODGETRED(curDgnColor) == 255) && (ODGETGREEN(curDgnColor) == 255) && (ODGETBLUE(curDgnColor) == 255)) || 
                        ((ODGETRED(curDgnColor) == 0) && (ODGETGREEN(curDgnColor) == 0) && (ODGETBLUE(curDgnColor) == 0))
                      )
        )
      {
        curDwgColor.m_uDwgColorIndex  = 7;
        curDwgColor.m_bUseTrueColor   = false;
      }
      else
      {
        curDwgColor.m_uDwgColorIndex = OdCmEntityColor::lookUpACI( ODGETRED(curDgnColor), ODGETGREEN(curDgnColor), ODGETBLUE(curDgnColor) );
        curDwgColor.m_clrDwgTrueColor = curDgnColor;

        OdUInt32 curDwgTrueColor   = OdCmEntityColor::lookUpRGB( curDwgColor.m_uDwgColorIndex );

        curDwgTrueColor |= 0xC2000000;

        OdUInt8 uDwgTrueColorRed   = OdCmEntityColor::red( &curDwgTrueColor );
        OdUInt8 uDwgTrueColorGreen =  OdCmEntityColor::green( &curDwgTrueColor );
        OdUInt8 uDwgTrueColorBlue  = OdCmEntityColor::blue( &curDwgTrueColor );

        if( (uDwgTrueColorRed != ODGETRED(curDgnColor)) || (uDwgTrueColorGreen != ODGETGREEN(curDgnColor)) || (uDwgTrueColorBlue != ODGETBLUE(curDgnColor)) )
        {
          curDwgColor.m_bUseTrueColor = true;
        }
        else
        {
          curDwgColor.m_bUseTrueColor = false;
        }
      }

      pContextData->m_dgnToDwgColorMap[ i ] = curDwgColor;
    }
  }
}

void OdDgnImportContext::setBackgroundColor( ODCOLORREF bgColor )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    std::map<OdUInt32, OdDgnImportColorIndexDescription>::iterator pIter = pContextData->m_dgnToDwgColorMap.find(255);

    if( pIter != pContextData->m_dgnToDwgColorMap.end() )
    {
      OdDgnImportColorIndexDescription curDwgColor;

      curDwgColor.m_uDwgColorIndex = OdCmEntityColor::lookUpACI( ODGETRED(bgColor), ODGETGREEN(bgColor), ODGETBLUE(bgColor) );
      curDwgColor.m_clrDwgTrueColor = bgColor;

      OdUInt32 curDwgTrueColor   = OdCmEntityColor::lookUpRGB( curDwgColor.m_uDwgColorIndex );

      curDwgTrueColor |= 0xC2000000;

      OdUInt8 uDwgTrueColorRed   = OdCmEntityColor::red( &curDwgTrueColor );
      OdUInt8 uDwgTrueColorGreen =  OdCmEntityColor::green( &curDwgTrueColor );
      OdUInt8 uDwgTrueColorBlue  = OdCmEntityColor::blue( &curDwgTrueColor );

      if( (uDwgTrueColorRed != ODGETRED(bgColor)) || (uDwgTrueColorGreen != ODGETGREEN(bgColor)) || (uDwgTrueColorBlue != ODGETBLUE(bgColor)) )
      {
        curDwgColor.m_bUseTrueColor = true;
      }
      else
      {
        curDwgColor.m_bUseTrueColor = false;
      }

      pContextData->m_dgnToDwgColorMap[ 255 ] = curDwgColor;
    }

  }
}

bool OdDgnImportContext::getDwgColor( OdUInt32 uDgnColorIndex, OdDgnImportColorIndexDescription& retColor )
{
  bool bRet = false;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    std::map<OdUInt32, OdDgnImportColorIndexDescription>::iterator pIter = pContextData->m_dgnToDwgColorMap.find(uDgnColorIndex);

    if( pIter != pContextData->m_dgnToDwgColorMap.end() )
    {
      bRet = true;

      retColor = pIter->second;
    }
  }

  return bRet;
}

bool OdDgnImportContext::getConvertColorIndexToTrueColorFlag()
{
  bool bRet = false;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    bRet = pContextData->m_bConvertColorIndexToTrueColor;
  }

  return bRet;
}

void OdDgnImportContext::setConvertColorIndexToTrueColorFlag( bool bSet )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    pContextData->m_bConvertColorIndexToTrueColor = bSet;
  }
}

// Reference attachment map

OdString getViewFlagsKey()
{
  OdString strRet;

  OdDgnImportViewFlags curFlags = OdDgnImportContext::getActualViewFlags();

  if (curFlags.getShowTextsFlag())
    strRet += L"1";
  else
    strRet += L"0";

  if (curFlags.getShowTagsFlag())
    strRet += L"1";
  else
    strRet += L"0";

  if (curFlags.getShowPatternsFlag())
    strRet += L"1";
  else
    strRet += L"0";

  if (curFlags.getShowDimensionsFlag())
    strRet += L"1";
  else
    strRet += L"0";

  if (curFlags.getShowFillsFlag())
    strRet += L"1";
  else
    strRet += L"0";

  if (curFlags.getUseLevelSymbologyFlag())
    strRet += L"1";
  else
    strRet += L"0";

  return strRet;
}

void OdDgnImportContext::addDwgModelBlockId( const OdString& strFileName, 
                                               const OdDgElementId& idModel,
                                                 const OdDgLevelTable* pLevelTable,
                                                   const OdString& strLevelMaskExt,
                                                     const OdDbObjectId& idBlockDefinition )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    OdString strModelId;
    strModelId.format(L"%08X", (OdUInt64)(idModel.getHandle()) );

    OdString strLevelTable;

    if (pLevelTable)
      strLevelTable.format(L"%x", (OdUInt32)(pLevelTable->elementId().getHandle()));
    else
      strLevelTable.format(L"0");

    OdString strMapName = strFileName + strModelId + strLevelTable + strLevelMaskExt + getViewFlagsKey();

    pContextData->m_dgnModelToBlockDefMap[strMapName] = idBlockDefinition;
  }
}

void OdDgnImportContext::restoreAfterImport()
{
  if( g_importContextDataArr.size() > 0 )
  {
    g_importContextDataArr.removeLast();
  }
}

void         OdDgnImportContext::prepareToImport( DgnImporter* dgnImporter, bool bCopyLevelMasks )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  OdDgnImportContextData newData;

  if( dgnImporter && pContextData && pContextData->m_pDgnImporter )
    dgnImporter->setDgnContinuousLineStyle(pContextData->m_pDgnImporter->getDgnContinuousLineStyle());

  newData.m_pDgnImporter = dgnImporter;
  newData.m_pActiveView  = getActiveView();

  if (pContextData)
  {
    newData.m_dgnToDwgColorMap   = pContextData->m_dgnToDwgColorMap;
    newData.m_mapMultilineStyles = pContextData->m_mapMultilineStyles;
    newData.m_idActiveXRef       = pContextData->m_idActiveXRef;
    newData.m_bImportDgTextAsDbMText = pContextData->m_bImportDgTextAsDbMText;
    newData.m_bUseLevelOverride = pContextData->m_bUseLevelOverride;
    newData.m_arrLevelOverrides = pContextData->m_arrLevelOverrides;
    newData.m_idLevelTableOverride = pContextData->m_idLevelTableOverride;
    newData.m_arrViewFlagsStack = pContextData->m_arrViewFlagsStack;
    newData.m_bCropXRefExtraClipByExtents = pContextData->m_bCropXRefExtraClipByExtents;
  }

  if( bCopyLevelMasks && g_importContextDataArr.size() > 0 )
  {
		newData.m_bSetLevelVisibilityByLevelMask = isLevelVisibilityByLevelMask();

    for( OdUInt32 i = 0; i < g_importContextDataArr[g_importContextDataArr.size()-1].m_pLevelMaskStack.size(); i++ )
      newData.m_pLevelMaskStack.push_back( g_importContextDataArr[g_importContextDataArr.size()-1].m_pLevelMaskStack[i] );
  }

  g_importContextDataArr.push_back( newData );
}

DgnImporter* OdDgnImportContext::getDgnImporter()
{
  DgnImporter*        pImporter = NULL;
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    pImporter = pContextData->m_pDgnImporter;
  }

  return pImporter;
}

bool OdDgnImportContext::getInternalImportFlag()
{
  bool bRet = false;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    bRet = pContextData->m_bInternalImport;
  }

  return bRet;
}

void OdDgnImportContext::setInternalImportFlag( bool bSet )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    pContextData->m_bInternalImport = bSet;
  }
}

OdDbObjectId OdDgnImportContext::getDwgModelBlockId( const OdString& strFileName, 
                                                       const OdDgElementId& idModel,
                                                         const OdDgLevelTable* pLevelTable,
                                                           const OdString& strLevelMaskExt
                                                    )
{
    OdDbObjectId retVal;

    OdDgnImportContextData* pContextData = getCurrentContext();

    if( pContextData )
    {
      OdString strModelId;
      strModelId.format(L"%08X", (OdUInt64)(idModel.getHandle()) );

      OdString strMapName = strFileName + strModelId;

      OdString strLevelTable;

      if (pLevelTable)
        strLevelTable.format(L"%x", (OdUInt32)(pLevelTable->elementId().getHandle()));
      else
        strLevelTable.format(L"0");

      strMapName += strLevelTable;

      if( !strLevelMaskExt.isEmpty() )
      {
        strMapName += strLevelMaskExt;
      }

      strMapName += getViewFlagsKey();

      std::map<OdString, OdDbObjectId>::iterator pIter = pContextData->m_dgnModelToBlockDefMap.find( strMapName );

      if( pIter != pContextData->m_dgnModelToBlockDefMap.end() )
      {
        retVal = pIter->second;
      }
    }

    return retVal;
}

OdUInt32 OdDgnImportContext::getXRefNestedDepth()
{
  return g_strXRefNameStack.size();
}

void     OdDgnImportContext::pushXRef( const OdString& strFileName, 
                                         const OdDgElementId& idModel,
                                            const OdDgLevelTable* pLevelTable,
                                              const OdDgElementId& idXRef,
                                                OdUInt32 uNestedDepth,
                                                  const OdString& strLevelMaskExt
                                      )
{
  OdString strModelId;
  strModelId.format(L"%08X", (OdUInt64)(idModel.getHandle()) );

  OdString strMapName = strFileName + strModelId;

  OdString strLevelTable;

  if (pLevelTable)
    strLevelTable.format(L"%x", (OdUInt32)(pLevelTable->elementId().getHandle()));
  else
    strLevelTable.format(L"0");

  strMapName += strLevelTable;

  if( !strLevelMaskExt.isEmpty() )
  {
    strMapName += strLevelMaskExt;
  }

  strMapName += getViewFlagsKey();

  OdDgImportXRefDescriptor tmp;
  tmp.m_strName = strMapName;
  tmp.m_uNestedDepth = uNestedDepth;
  tmp.m_idXRef = idXRef;

  g_strXRefNameStack.push_back( tmp );
}

void     OdDgnImportContext::popXRef()
{
  if( g_strXRefNameStack.size() > 0 )
  {
    g_strXRefNameStack.removeLast();
  }
}

void     OdDgnImportContext::removeLastXRef()
{
  if (g_strXRefNameStack.size() > 0)
  {
    g_lastXRefRecord = g_strXRefNameStack.last();
    g_strXRefNameStack.removeLast();
  }
  else
    g_lastXRefRecord.m_strName.empty();
}

void     OdDgnImportContext::restoreLastXRef()
{
  if( !g_lastXRefRecord.m_strName.isEmpty() )
  {
    g_strXRefNameStack.push_back(g_lastXRefRecord);
    g_lastXRefRecord.m_strName.empty();
  }
}

bool     OdDgnImportContext::checkNestedDepth()
{
  bool bRet = true;

  OdUInt32 uStackLenght = g_strXRefNameStack.size();

  for( OdUInt32 i = 0; i < uStackLenght; i++ )
  {
     if( g_strXRefNameStack[i].m_uNestedDepth < (uStackLenght - i) )
     {
       bRet = false;
       break;
     }
  }

  return bRet;
}

bool     OdDgnImportContext::isXRefInStack( const OdString& strFileName, const OdDgElementId& idModel )
{
  OdDbObjectId retVal;

  OdString strModelId;
  strModelId.format(L"%08X", (OdUInt64)(idModel.getHandle()) );

  OdString strMapName = strFileName + strModelId;

  bool bRet = false;

  for( OdUInt32 i = 0; i < g_strXRefNameStack.size(); i++ )
  {
    if( g_strXRefNameStack[i].m_strName == strMapName )
    {
      bRet = true;
      break;
    }
  }

  return bRet;
}

//---------------------------------------------------------------------------

OdDgElementId OdDgnImportContext::getXRefId( OdUInt32 uIndex )
{
  OdDgElementId idRet;

  if( g_strXRefNameStack.size() > uIndex )
  {
    idRet = g_strXRefNameStack[uIndex].m_idXRef;
  }

  return idRet;
}

//---------------------------------------------------------------------------

OdDbObjectId OdDgnImportContext::getDgnContinuousLineStyleId()
{
  OdDbObjectId idRet;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    idRet = pContextData->m_pDgnImporter->getDgnContinuousLineStyle();
  }

  return idRet;
}

//---------------------------------------------------------------------------

bool OdDgnImportContext::getGlobalLineScale( double& dLineScale )
{
  bool bRet = false;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData && (pContextData->m_dGlobalLineScaleStack.size() > 0) )
  {

    dLineScale = pContextData->m_dGlobalLineScaleStack[ pContextData->m_dGlobalLineScaleStack.size() - 1];
    bRet = true;
  }

  return bRet;
}

//---------------------------------------------------------------------------

void OdDgnImportContext::pushGlobalLineScale( double dLineScale )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    pContextData->m_dGlobalLineScaleStack.push_back( dLineScale );
  }
}

//---------------------------------------------------------------------------

void OdDgnImportContext::popGlobalLineScale()
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData && pContextData->m_dGlobalLineScaleStack.size() > 0 )
  {
    pContextData->m_dGlobalLineScaleStack.removeLast();
  }
}

//---------------------------------------------------------------------------

bool OdDgnImportContext::isFontsEqual(const OdFont* pFont1, const OdFont* pFont2)
{
  bool bRet = false;

  if( !pFont1 && !pFont2 )
  {
    bRet = true;
  }
  else if( pFont1 && pFont2 && (pFont1->getFileName() == pFont2->getFileName()) &&
         (pFont1->getFlags() == pFont2->getFlags())
    )
  {
     bRet = true;
  }

  return bRet;
}

//---------------------------------------------------------------------------

bool OdDgnImportContext::getConvertEmptyDataFieldsToSpacesFlag()
{
  bool bRet = true;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    bRet = pContextData->m_bConvertEmptyDataFieldsToSpaces;
  }

  return bRet;
}

//---------------------------------------------------------------------------

void OdDgnImportContext::setConvertEmptyDataFieldsToSpacesFlag( bool bSet )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    pContextData->m_bConvertEmptyDataFieldsToSpaces = bSet;
  }
}

//---------------------------------------------------------------------------

 OdDbObjectId OdDgnImportContext::getStyleForDbText(OdDbDatabase* pDb, const OdGiTextStyle& textStyle)
 {
   if (!pDb)
   {
     return OdDbObjectId::kNull;
   }

   // Try to find existing text style with suitable properties
   // - get a style by name,
   // - find an acceptable style by properties.
   //
   OdDbTextStyleTablePtr pTable = pDb->getTextStyleTableId().safeOpenObject();
   OdDbObjectId styleId;
   if (!textStyle.styleName().isEmpty())
   {
     OdDbTextStyleTableRecordPtr pRec = pTable->getAt(textStyle.styleName(), OdDb::kForRead);
     if (pRec.get())
     {
       OdGiTextStyle recStyle;
       giFromDbTextStyle(pRec, recStyle);
       if ( recStyle.getFont() == textStyle.getFont()
         && recStyle.getBigFont() == textStyle.getBigFont()
         && recStyle.textSize() == textStyle.textSize()
         && recStyle.isVertical() == textStyle.isVertical()
         && recStyle.isBackward() == textStyle.isBackward()
         && recStyle.isUpsideDown() == textStyle.isUpsideDown())
       {
         OdDgnImportContext::setResourceUsage(pRec->objectId());
         return pRec->objectId();
       }
     }
   }

   for (OdDbSymbolTableIteratorPtr pIter = pTable->newIterator(); !pIter->done(); pIter->step())
   {
     OdDbTextStyleTableRecordPtr pRec = pIter->getRecord();
     OdGiTextStyle recStyle;
     giFromDbTextStyle(pRec, recStyle);
     if ( isFontsEqual(recStyle.getFont(), textStyle.getFont())
       && isFontsEqual(recStyle.getBigFont(), textStyle.getBigFont())
       && recStyle.textSize() == textStyle.textSize()
       && recStyle.isVertical() == textStyle.isVertical()
       && recStyle.isBackward() == textStyle.isBackward()
       && recStyle.isUpsideDown() == textStyle.isUpsideDown())
     {
       OdDgnImportContext::setResourceUsage(pIter->getRecordId());
       return pIter->getRecordId();
     }
   }

   return OdDbObjectId::kNull;
 }

//---------------------------------------------------------------------------

OdDbObjectId OdDgnImportContext::createStyleForDbText( OdDbDatabase* pDb, 
                                                         OdDgDatabase* pDgDb, 
                                                           const OdGiTextStyle& textStyle,
                                                             bool bCheckHeight,
                                                               bool bSetZeroHeightForNew )
{
  OdDbObjectId recId;

  if( !pDb )
  {
    return recId;
  }

  OdDbTextStyleTableRecordPtr pRec = OdDbTextStyleTableRecord::createObject();
  pDb->addOdDbObject(pRec);

  OdString sTypeFace;
  bool bBold = false, bItalic = false;
  int nCharSet = 0, nPitchAndFamily = 0;
  OdGiTextStyle srcStyle(textStyle);
  srcStyle.font(sTypeFace, bBold, bItalic, nCharSet, nPitchAndFamily);

  pRec->setFont(sTypeFace, bBold, bItalic, nCharSet, nPitchAndFamily);

  if(srcStyle.getFont() && srcStyle.getFont()->isShxFont() )
  {
    OdString fileName = srcStyle.ttfdescriptor().fileName();

    if(fileName.isEmpty() )
    {
      pRec->setFileName(srcStyle.ttfdescriptor().typeface());
    }
    else if( OdDgnImportContext::getDgnImporter() )
    {
      OdString strFileExt = fileName;

      if( strFileExt.getLength() > 4 )
      {
        strFileExt = strFileExt.right(4);
        strFileExt.makeUpper();

        if( strFileExt != L".SHX" )
        {
          if( OdDgnImportContext::getDgnImporter() )
            OdDgnImportContext::getDgnImporter()->createShxFontFromRscFont( fileName );
          fileName += L".shx";
        }
      }

      pRec->setFileName(fileName);
    }
  }
  else
  {
    if( sTypeFace.isEmpty() )
    {
      sTypeFace = srcStyle.ttfdescriptor().fileName();
      pRec->setFont(sTypeFace, bBold, bItalic, nCharSet, nPitchAndFamily);
    }
  }

  pRec->setBigFontFileName(srcStyle.bigFontFileName());
  pRec->setIsVertical(textStyle.isVertical());
  pRec->setIsUpsideDown(textStyle.isUpsideDown());
  pRec->setIsBackwards(textStyle.isBackward());
  pRec->setTextSize( textStyle.textSize() );
  pRec->setXScale(textStyle.xScale());

  OdDbTextStyleTablePtr pTable = pDb->getTextStyleTableId().openObject(OdDb::kForWrite);

  OdDbSymbolTableIteratorPtr pDbTextStyleIter = pTable->newIterator();

  unsigned index = 0;

  for(; !pDbTextStyleIter->done(); pDbTextStyleIter->step() )
  {
    OdDbTextStyleTableRecordPtr pDbTextStyle = pDbTextStyleIter->getRecord( OdDb::kForRead );

    OdString sCurTypeFace, sRecTypeFace;
    bool bCurBold = false, bCurItalic = false, bRecBold = false, bRecItalic = false;
    int nCurCharSet = 0, nCurPitchAndFamily = 0, nRecCharSet = 0, nRecPitchAndFamily = 0;

    pDbTextStyle->font(sCurTypeFace, bCurBold, bCurItalic, nCurCharSet, nCurPitchAndFamily);
    pRec->font(sRecTypeFace, bRecBold, bRecItalic, nRecCharSet, nRecPitchAndFamily);

    bool bCorrectTextSize = OdZero(pDbTextStyle->xScale() - pRec->xScale());

    if( bCheckHeight && bCorrectTextSize )
    {
      bCorrectTextSize = OdZero(pDbTextStyle->textSize() - pRec->textSize());

      if (!bCorrectTextSize && bSetZeroHeightForNew)
        bCorrectTextSize = OdZero(pDbTextStyle->textSize());
    }

    if( (sCurTypeFace == sRecTypeFace) && (bCurBold == bRecBold) && (bCurItalic == bRecItalic) && 
        (nCurCharSet == nRecCharSet) && (nCurPitchAndFamily == nRecPitchAndFamily) &&
        (pDbTextStyle->bigFontFileName() == pRec->bigFontFileName() ) &&
        (pDbTextStyle->isVertical() == pRec->isVertical() ) &&
        (pDbTextStyle->isUpsideDown() == pRec->isUpsideDown() ) &&
        (pDbTextStyle->isBackwards() == pRec->isBackwards() ) && bCorrectTextSize
      )
    {
      OdDgnImportContext::setResourceUsage(pDbTextStyle->objectId());
      recId = pDbTextStyle->objectId();
      break;
    }
  }

  if( recId.isNull() )
  {
    for (;;)
    {
      try
      {
        OdString sName;
        sName.format(L"Style_%d", index++);

        if( pTable->getAt(sName) )
          continue;

        if (bSetZeroHeightForNew)
          pRec->setTextSize(0.0);
        
        pRec->setName(sName);
        recId = pTable->add(pRec);
        break;
      }
      catch (const OdError_DuplicateRecordName&)
      {
      }
    }
  }

  return recId;
}

//---------------------------------------------------------------------------

OdDbObjectId OdDgnImportContext::getObjectId( const OdDgElementId& idDgnElement )
{
  OdDbObjectId retVal;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData && pContextData->m_pDgnImporter )
  {
    retVal = pContextData->m_pDgnImporter->getObjectId( idDgnElement );
    pContextData->m_pDgnImporter->setResourceUsage(retVal);
  }

  return retVal;
}

//---------------------------------------------------------------------------

bool OdDgnImportContext::getObjectPath( const OdDgElementId& idDgnElement,
                                          OdDgnImportPathToDwgObject& dwgPath
                                      )
{
  bool bRet = false;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData && pContextData->m_pDgnImporter )
  {
    bRet = pContextData->m_pDgnImporter->getObjectPath( idDgnElement, dwgPath );
  }

  return bRet;
}

//---------------------------------------------------------------------------

void OdDgnImportContext::addObjectPath( const OdDgElementId& idDgnElement, OdDgnImportPathToDwgObject& dwgPath )
{
  if( idDgnElement.isNull() || idDgnElement.getHandle() == (OdUInt64)(0))
    return;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData && pContextData->m_pDgnImporter )
  {
    if( pContextData->m_arrCellHeaderIds.size() > 0 )
    {
      dwgPath.m_idPath.objectIds().insert( dwgPath.m_idPath.objectIds().begin(), pContextData->m_arrCellHeaderIds.begin(), pContextData->m_arrCellHeaderIds.end() );
    }

    pContextData->m_pDgnImporter->addObjectPath( idDgnElement, dwgPath );
  }
}

//---------------------------------------------------------------------------

void OdDgnImportContext::addResourceId( const OdDbObjectId& idResource )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData && pContextData->m_pDgnImporter )
    pContextData->m_pDgnImporter->addResourceId( idResource );
}

//---------------------------------------------------------------------------

void OdDgnImportContext::setResourceUsage( const OdDbObjectId& idResource )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData && pContextData->m_pDgnImporter )
    pContextData->m_pDgnImporter->setResourceUsage( idResource );
}

//---------------------------------------------------------------------------

void OdDgnImportContext::addCellHeaderIdToPath( const OdDbObjectId& idCellHeader )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    pContextData->m_arrCellHeaderIds.push_back( idCellHeader );
  }
}

//---------------------------------------------------------------------------

void OdDgnImportContext::removeLastCellHeaderIdFromPath()
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData && pContextData->m_arrCellHeaderIds.size() )
  {
    pContextData->m_arrCellHeaderIds.removeLast();
  }
}

//---------------------------------------------------------------------------

bool OdDgnImportContext::getImportCurvesOnlyFlag()
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    return pContextData->m_bImportCurvesOnly;
  }

  return false;
}

//---------------------------------------------------------------------------

void OdDgnImportContext::setImportCurvesOnlyFlag( bool bSet )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    pContextData->m_bImportCurvesOnly = bSet;
  }
}

//---------------------------------------------------------------------------

bool OdDgnImportContext::getSkipPatternDrawFlag()
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    return pContextData->m_bSkipPatternDraw;
  }

  return false;
}

//---------------------------------------------------------------------------

void OdDgnImportContext::setSkipPatternDrawFlag( bool bSet )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    pContextData->m_bSkipPatternDraw = bSet;
  }
}

//----------------------------------------------------------------------------

bool OdDgnImportContext::isNoteDimensionCell( const OdDgElementId& idCellHeader )
{
  bool bRet = false;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    for( OdUInt32 i = 0; i < pContextData->m_arrNoteCellHeaders.size(); i++ )
    {
      if( pContextData->m_arrNoteCellHeaders[i] == idCellHeader )
      {
        bRet = true;
        break;
      }
    }
  }

  return bRet;
}

//----------------------------------------------------------------------------

void OdDgnImportContext::addNoteDimensionCell( const OdDgElementId& idCellHeader )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    pContextData->m_arrNoteCellHeaders.push_back( idCellHeader );
  }
}

//----------------------------------------------------------------------------

void OdDgnImportContext::removeNoteDimensionCell( const OdDgElementId& idCellHeader )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    for( OdUInt32 i = 0; i < pContextData->m_arrNoteCellHeaders.size(); i++ )
    {
      if( pContextData->m_arrNoteCellHeaders[i] == idCellHeader )
      {
        pContextData->m_arrNoteCellHeaders.removeAt(i);
        break;
      }
    }
  }
}

//---------------------------------------------------------------------------

void   OdDgnImportContext::addScaledBlock(const OdDbObjectId& idBlock, double dDimTermScale)
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    pContextData->m_mapScaledBlocks[idBlock] = dDimTermScale;
  }
}

//---------------------------------------------------------------------------

double OdDgnImportContext::getScaleOfBlockTableRecord(const OdDbObjectId& idBlock)
{
  double dScale = 1.0;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    std::map<OdDbObjectId, double>::const_iterator pIter = pContextData->m_mapScaledBlocks.find(idBlock);

    if (pIter != pContextData->m_mapScaledBlocks.end())
      dScale = pIter->second;
  }

  return dScale;
}

//---------------------------------------------------------------------------

void OdDgnImportContext::pushLevelMask( const OdDgLevelMaskPtr& pLevelMask, const OdDgLevelTablePtr& pLevelTable, bool bShowNewLevels )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    OdDgnImportLevelMaskDescriptor tmp;

    if( !pLevelTable.isNull() && !pLevelMask.isNull() )
    {
      OdDgElementIteratorPtr pLevelIter = pLevelTable->createIterator();

      for(; !pLevelIter->done(); pLevelIter->step() )
      {
        OdDgLevelTableRecordPtr pLevel = pLevelIter->item().openObject(OdDg::kForRead);

        if( !pLevel.isNull() )
          tmp[pLevel->getEntryId()] = pLevelMask->getLevelIsVisible(pLevel->elementId(), !bShowNewLevels) == OdDgLevelMask::kLevelVisible;
      }
    }

    pContextData->m_pLevelMaskStack.push_back( tmp );
  }
}

//---------------------------------------------------------------------------

void OdDgnImportContext::popLevelMask()
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData && pContextData->m_pLevelMaskStack.size() > 0 )
  {
    pContextData->m_pLevelMaskStack.removeLast();
  }
}

//---------------------------------------------------------------------------

bool OdDgnImportContext::isLevelMask()
{
  bool bRet = false;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData && pContextData->m_pLevelMaskStack.size() > 0 )
  {
    bRet = true;
  }

  return bRet;
}

//----------------------------------------------------------------------------

bool OdDgnImportContext::checkLevelMask( OdUInt32 uLevelEntryId, bool bDefaultValue )
{
  bool bRet = bDefaultValue;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData && pContextData->m_pLevelMaskStack.size() > 0 )
  {
    OdDgnImportLevelMaskDescriptor& curMask = pContextData->m_pLevelMaskStack[pContextData->m_pLevelMaskStack.size() - 1];

    OdDgnImportLevelMaskDescriptorIterator curIter = curMask.find( uLevelEntryId );

    if( curIter != curMask.end() )
    {
      bRet = curIter->second;
    }
  }

  return bRet;
}

//----------------------------------------------------------------------------

OdString OdDgnImportContext::getLevelMaskString()
{
  OdString strRet = OdString::kEmpty;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData && pContextData->m_pLevelMaskStack.size() > 0 )
  {
    OdDgnImportLevelMaskDescriptor& curMask = pContextData->m_pLevelMaskStack[pContextData->m_pLevelMaskStack.size() - 1];

    OdDgnImportLevelMaskDescriptorIterator curIter = curMask.begin();

    while( curIter != curMask.end() )
    {
      if( curIter->second )
      {
        strRet += L"1";
      }
      else
      {
        strRet += L"0";
      }

      curIter++;
    }
  }

  return strRet;
}

//----------------------------------------------------------------------------

bool OdDgnImportContext::isImportInvisible()
{
  bool bRet = false;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData  )
  {
    bRet = pContextData->m_bImportInvisible;
  }

  return bRet;
}

//----------------------------------------------------------------------------

void OdDgnImportContext::setImportInvisible( bool bSet )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData  )
  {
    pContextData->m_bImportInvisible = bSet;
  }
}

//----------------------------------------------------------------------------

bool OdDgnImportContext::isImportDgTextAsDbMText()
{
  bool bRet = false;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData  )
  {
    bRet = pContextData->m_bImportDgTextAsDbMText;
  }

  return bRet;
}

//----------------------------------------------------------------------------

void OdDgnImportContext::setImportDgTextAsDbMText( bool bSet )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData  )
  {
    pContextData->m_bImportDgTextAsDbMText = bSet;
  }
}

//----------------------------------------------------------------------------

OdDgViewPtr OdDgnImportContext::getActiveView()
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData  )
  {
    return pContextData->m_pActiveView;
  }

  return OdDgViewPtr();
}

//----------------------------------------------------------------------------

void        OdDgnImportContext::setActiveView( const OdDgViewPtr& pView )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData  )
  {
    pContextData->m_pActiveView = pView;
  }
}

void OdDgnImportContext::pushViewFlags(const OdDgnImportViewFlags& viewFlags)
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData  )
  {
    pContextData->m_arrViewFlagsStack.push_back(viewFlags);
  }
}

void OdDgnImportContext::popViewFlags()
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData && !pContextData->m_arrViewFlagsStack.isEmpty() )
  {
    pContextData->m_arrViewFlagsStack.removeLast();
  }
}

void OdDgnImportContext::claerViewFlags()
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData && !pContextData->m_arrViewFlagsStack.isEmpty())
  {
    pContextData->m_arrViewFlagsStack.clear();
  }
}

OdDgnImportViewFlags OdDgnImportContext::getActualViewFlags()
{
  OdDgnImportViewFlags retVal;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData && !pContextData->m_arrViewFlagsStack.isEmpty())
    retVal = pContextData->m_arrViewFlagsStack.last();

  return retVal;
}

//----------------------------------------------------------------------------

void initPolygonImportModes()
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData && pContextData->m_pDgnImporter )
  {
    OdRxVariantValue tmpVar = (OdRxVariantValue)pContextData->m_pDgnImporter->properties()->getAt("3dShapeImportMode");
    pContextData->m_3dShapeImportMode = tmpVar->getInt8();
    tmpVar = (OdRxVariantValue)pContextData->m_pDgnImporter->properties()->getAt("2dShapeImportMode");
    pContextData->m_2dShapeImportMode = tmpVar->getInt8();
    tmpVar = (OdRxVariantValue)pContextData->m_pDgnImporter->properties()->getAt("3dEllipseImportMode");
    pContextData->m_3dEllipseImportMode = tmpVar->getInt8();
    tmpVar = (OdRxVariantValue)pContextData->m_pDgnImporter->properties()->getAt("2dEllipseImportMode");
    pContextData->m_2dEllipseImportMode = tmpVar->getInt8();
    tmpVar = (OdRxVariantValue)pContextData->m_pDgnImporter->properties()->getAt("3dClosedBSplineCurveImportMode");
    pContextData->m_3dSplineImportMode = tmpVar->getInt8();
    tmpVar = (OdRxVariantValue)pContextData->m_pDgnImporter->properties()->getAt("2dClosedBSplineCurveImportMode");
    pContextData->m_2dSplineImportMode = tmpVar->getInt8();
    tmpVar = (OdRxVariantValue)pContextData->m_pDgnImporter->properties()->getAt("3dObjectImportMode");
    pContextData->m_3dObjectImportMode = tmpVar->getInt8();

    pContextData->m_bInitPolygonImportModes = true;
  }
}

//----------------------------------------------------------------------------

OdUInt8 OdDgnImportContext::getShape3dImportMode()
{
  OdUInt8 uRet = 1;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData  )
  {
    if( !pContextData->m_bInitPolygonImportModes )
    {
      initPolygonImportModes();
    }

    uRet = pContextData->m_3dShapeImportMode;
  }

  return uRet;
}

//----------------------------------------------------------------------------

OdUInt8 OdDgnImportContext::getObject3dImportMode()
{
  OdUInt8 uRet = 1;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData  )
  {
    if( !pContextData->m_bInitPolygonImportModes )
    {
      initPolygonImportModes();
    }

    uRet = pContextData->m_3dObjectImportMode;
  }

  return uRet;
}


//----------------------------------------------------------------------------

OdUInt8 OdDgnImportContext::getShape2dImportMode()
{
  OdUInt8 uRet = 0;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData  )
  {
    if( !pContextData->m_bInitPolygonImportModes )
    {
      initPolygonImportModes();
    }

    uRet = pContextData->m_2dShapeImportMode;
  }

  return uRet;
}

//----------------------------------------------------------------------------

OdUInt8 OdDgnImportContext::getEllipse3dImportMode()
{
  OdUInt8 uRet = 0;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData  )
  {
    if( !pContextData->m_bInitPolygonImportModes )
    {
      initPolygonImportModes();
    }

    uRet = pContextData->m_3dEllipseImportMode;
  }

  return uRet;
}

//----------------------------------------------------------------------------

OdUInt8 OdDgnImportContext::getEllipse2dImportMode()
{
  OdUInt8 uRet = 0;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData  )
  {
    if( !pContextData->m_bInitPolygonImportModes )
    {
      initPolygonImportModes();
    }

    uRet = pContextData->m_2dEllipseImportMode;
  }

  return uRet;
}

//----------------------------------------------------------------------------

OdUInt8 OdDgnImportContext::getClosedBSplineCurve3dImportMode()
{
  OdUInt8 uRet = 1;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData  )
  {
    if( !pContextData->m_bInitPolygonImportModes )
    {
      initPolygonImportModes();
    }

    uRet = pContextData->m_3dSplineImportMode;
  }

  return uRet;
}

//----------------------------------------------------------------------------

OdUInt8 OdDgnImportContext::getClosedBSplineCurve2dImportMode()
{
  OdUInt8 uRet = 0;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData  )
  {
    if( !pContextData->m_bInitPolygonImportModes )
    {
      initPolygonImportModes();
    }

    uRet = pContextData->m_2dSplineImportMode;
  }

  return uRet;
}

//----------------------------------------------------------------------------

void    OdDgnImportContext::setCurvesOnlyImportMode()
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData  )
  {
    pContextData->m_2dSplineImportMode  = 0;
    pContextData->m_3dSplineImportMode  = 0;
    pContextData->m_2dEllipseImportMode = 0;
    pContextData->m_3dEllipseImportMode = 0;
    pContextData->m_2dShapeImportMode   = 0;
    pContextData->m_3dShapeImportMode   = 0;
    pContextData->m_bInitPolygonImportModes = true;
  }
}

//----------------------------------------------------------------------------

void    OdDgnImportContext::setUpdateCurvesImportMode()
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData  )
  {
    pContextData->m_bInitPolygonImportModes = false;
  }
}

//----------------------------------------------------------------------------

bool OdDgnImportContext::getLayerByBlockMode()
{
  bool bRet = false;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    bRet = pContextData->m_bLayerByBlockMode;
  }

  return bRet;
}

//----------------------------------------------------------------------------

void OdDgnImportContext::setLayerByBlockMode(bool bSet)
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    pContextData->m_bLayerByBlockMode = bSet;
  }
}

//----------------------------------------------------------------------------

bool OdDgnImportContext::getLockColorMode()
{
  bool bRet = false;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    bRet = pContextData->m_bLockColorMode;
  }

  return bRet;
}

//----------------------------------------------------------------------------

void OdDgnImportContext::setLockColorMode(bool bSet)
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    pContextData->m_bLockColorMode = bSet;
  }
}

//----------------------------------------------------------------------------

bool OdDgnImportContext::getLockLineWeightMode()
{
  bool bRet = false;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    bRet = pContextData->m_bLockLineWeightMode;
  }

  return bRet;
}

//----------------------------------------------------------------------------

void OdDgnImportContext::setLockLineWeightMode(bool bSet)
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    pContextData->m_bLockLineWeightMode = bSet;
  }
}

//----------------------------------------------------------------------------

bool OdDgnImportContext::getLockLineStyleMode()
{
  bool bRet = false;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    bRet = pContextData->m_bLockLineStyleMode;
  }

  return bRet;
}

//----------------------------------------------------------------------------

void OdDgnImportContext::setLockLineStyleMode(bool bSet)
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    pContextData->m_bLockLineStyleMode = bSet;
  }
}

//----------------------------------------------------------------------------

OdUInt32 OdDgnImportContext::getLockColor()
{
  OdUInt32 uRet = 0;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    uRet = pContextData->m_uLockColorIndex;
  }

  return uRet;
}

//----------------------------------------------------------------------------

void OdDgnImportContext::setLockColor(OdUInt32 uColorIndex)
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    pContextData->m_uLockColorIndex = uColorIndex;
  }
}

//----------------------------------------------------------------------------

OdUInt32 OdDgnImportContext::getLockLineStyle()
{
  OdUInt32 uRet = 0;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    uRet = pContextData->m_uLockLineStyle;
  }

  return uRet;
}

//----------------------------------------------------------------------------

void OdDgnImportContext::setLockLineStyle(OdUInt32 uLineStyle)
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    pContextData->m_uLockLineStyle = uLineStyle;
  }
}

//----------------------------------------------------------------------------

OdUInt32 OdDgnImportContext::getLockLineWeight()
{
  OdUInt32 uRet = 0;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    uRet = pContextData->m_uLockLineWeight;
  }

  return uRet;
}

//----------------------------------------------------------------------------

void OdDgnImportContext::setLockLineWeight(OdUInt32 uLineWeight)
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    pContextData->m_uLockLineWeight = uLineWeight;
  }
}

//----------------------------------------------------------------------------

void OdDgnImportContext::addBlockForSharedCellOverride(const OdString& strKey, const OdDbObjectId& idBlock)
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    pContextData->m_mapSharedCellOverrides[strKey] = idBlock;
  }
}

//----------------------------------------------------------------------------

OdDbObjectId OdDgnImportContext::getBlockForSharedCellOverride(const OdString& strKey)
{
  OdDbObjectId idRet;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    std::map< OdString, OdDbObjectId>::iterator pIter = pContextData->m_mapSharedCellOverrides.find(strKey);

    if (pIter != pContextData->m_mapSharedCellOverrides.end())
      idRet = pIter->second;
  }

  return idRet;
}

//----------------------------------------------------------------------------

void OdDgnImportContext::clearBlockForSharedCellOverrideMap()
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
    pContextData->m_mapSharedCellOverrides.clear();
}

//----------------------------------------------------------------------------

OdUInt32 OdDgnImportContext::getRscFontCount()
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData  )
  {
    return pContextData->m_arrRscFontNames.size();
  }

  return 0;
}


//----------------------------------------------------------------------------

OdString OdDgnImportContext::getRscFontName( OdUInt32 uIndex )
{
  OdString strRet;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData && pContextData->m_arrRscFontNames.size() > uIndex )
  {
    strRet = pContextData->m_arrRscFontNames[uIndex];
  }

  return strRet;
}

//----------------------------------------------------------------------------

void     OdDgnImportContext::addRscFontName( const OdString& strName )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData && !strName.isEmpty() )
  {
    bool bFontNamePresent = false;

    for( OdUInt32 i = 0; i < pContextData->m_arrRscFontNames.size(); i++ )
    {
      if( pContextData->m_arrRscFontNames[i] == strName )
      {
        bFontNamePresent = true;
        break;
      }
    }

    if( !bFontNamePresent )
    {
      pContextData->m_arrRscFontNames.push_back(strName);
    }
  }
}

//----------------------------------------------------------------------------

void     OdDgnImportContext::createShxFontFromRscFont( const OdString& strFontName, 
                                                         OdDgDatabase* pDgDb,
                                                           OdDbHostAppServices* pHostAppServices,
                                                             const OdString& strShxPathData )
{
  if( !pDgDb )
    return;

  OdDgFontTablePtr   pFontTable   = pDgDb->getFontTable(OdDg::kForRead);
  OdDgFontTablePEPtr pFontTablePE = OdDgFontTablePEPtr(OdRxObjectPtr(pFontTable));

  if( pFontTable.isNull() || pFontTablePE.isNull() )
  {
    return;
  }

  bool bFontWasCreated = false;

  for( OdUInt32 i = 0; i < OdDgnImportContext::getRscFontCount(); i++ )
  {
    if( OdDgnImportContext::getRscFontName( i ) == strFontName )
    {
      bFontWasCreated = true;
      break;
    }
  }

  if( !bFontWasCreated)
  {
    OdDgnImportContext::addRscFontName( strFontName );

    OdString strCurFontName = strFontName;

    OdString strFontExt = strCurFontName;

    if( strFontExt.getLength() > 4 )
    {
      strFontExt = strFontExt.right(4);
    }

    strFontExt.makeUpper();

    if( strFontExt == L".SHX" )
    {
      return;
    }

    OdDgFontTableRecordPtr pFontRec = pFontTable->getFont( strCurFontName );

    if( !pFontRec.isNull() && (pFontRec->getType() == kFontTypeRsc) )
    {
      OdString strFileName = pHostAppServices->findFile( strCurFontName + L".shx", 0, OdDbBaseHostAppServices::kFontFile );

      if( !strFileName.isEmpty() )
      {
        return;
      }

      OdString strShxPath = strShxPathData;

      if( !strShxPath.isEmpty() )
      {
        strShxPath.replace(L'\\', L'/');

        if( strShxPath[strShxPath.getLength()-1] != L'/' )
        {
          strShxPath += L"/";
        }

        OdString strFileName = pHostAppServices->findFile( strShxPath + strCurFontName + L".shx", 0, OdDbBaseHostAppServices::kFontFile );

        if( !strFileName.isEmpty() )
        {
          return;
        }
      }
      else
      {
        strShxPath.replace(L'\\', L'/');

        if( strShxPath.reverseFind(L'/') != -1 )
        {
          strShxPath = strShxPath.left(strShxPath.reverseFind(L'/') + 1);
        }
        else
        {
          strShxPath.empty();
        }
      }

      OdString strShxFileName = strShxPath + strCurFontName + L".shx";

      strFileName = pHostAppServices->findFile( strShxFileName, 0, OdDbBaseHostAppServices::kFontFile );

      if( strFileName.isEmpty() )
      {
        pFontTablePE->convertRscFontToShxFont( pFontTable, strCurFontName, strShxFileName );
      }
    }
  }
}

//----------------------------------------------------------------------------

void     OdDgnImportContext::clearRscFontArray()
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    pContextData->m_arrRscFontNames.clear();
  }
}

//----------------------------------------------------------------------------

OdDbObjectId OdDgnImportContext::createMultilineStyle( const OdDgnImportMultilineDescriptor& mLineDesc, OdDbDatabase* pDb, OdDgDatabase* pDg )
{
  OdDgnImportMultilineDescriptor desc = mLineDesc;

  OdDgnImportContextData* pContextData = getCurrentContext();

  OdDbDictionaryPtr pMLDic = pDb->getMLStyleDictionaryId().safeOpenObject(OdDb::kForWrite);

  OdDbMlineStylePtr pMLStyle = OdDbMlineStyle::createObject();

  OdString strStyleName = L"MLStyle_0";

  if( !desc.m_strStyleName.isEmpty() )
  {
    strStyleName = desc.m_strStyleName;
    strStyleName.remove( L' ' );

    if( strStyleName.getLength() > 32 )
    {
      strStyleName = strStyleName.left(32);
    }
  }

  OdString repairedName;

  if( OdDbSymUtil::repairSymbolName(repairedName, strStyleName, pDb ) == eOk && !repairedName.isEmpty() )
  {
    strStyleName = repairedName;
  }

  OdUInt32 iCount = 0;

  while( pMLDic->has(strStyleName) || (strStyleName.getLength() >= 32) )
  {
    iCount++;

    strStyleName.format(L"MLStyle_%d", iCount);
  }

  OdCmColor clrFillColor;

  setDwgColorByDgnIndex( pDg, clrFillColor, desc.m_uFillColor );

  // Create multiline style

  pMLStyle->initMlineStyle();
  pMLStyle->setName( strStyleName );
  pMLStyle->setShowMiters( desc.m_bShowJoints );
  pMLStyle->setStartSquareCap( desc.m_bShowStartCapLine );
  pMLStyle->setStartInnerArcs( desc.m_bShowStartCapInArc );
  pMLStyle->setStartRoundCap( desc.m_bShowStartCapOutArc );

  if(desc.m_dStartCapAngle < 0 )
    pMLStyle->setStartAngle(OdaPI + desc.m_dStartCapAngle);
  else
    pMLStyle->setStartAngle( desc.m_dStartCapAngle );

  pMLStyle->setEndSquareCap( desc.m_bShowEndCapLine );
  pMLStyle->setEndInnerArcs( desc.m_bShowEndCapInArc );
  pMLStyle->setEndRoundCap( desc.m_bShowEndCapOutArc );
  
  if (desc.m_dEndCapAngle < 0)
    pMLStyle->setEndAngle(OdaPI + desc.m_dEndCapAngle);
  else
    pMLStyle->setEndAngle(desc.m_dEndCapAngle);

  pMLStyle->setFilled( desc.m_bShowFill );
  pMLStyle->setFillColor( clrFillColor );

  OdArray<double>       arrOffsets;
  OdArray<OdCmColor>    arrColors;
  OdArray<OdDbObjectId> arrLineTypes;
  double                dMaxOffset = -1e20;
  double                dMinOffset = 1e20;

  OdUInt32 i;

  for( i = 0; i < desc.m_arrOffsets.size(); i++ )
  {
    double dCurOffset = desc.m_arrOffsets[i];

    arrOffsets.push_back( dCurOffset );

    if( dCurOffset < dMinOffset )
    {
      dMinOffset = dCurOffset;
    }

    if( dCurOffset > dMaxOffset )
    {
      dMaxOffset = dCurOffset;
    }

    OdCmColor curColor;
    setDwgColorByDgnIndex( pDg, curColor, desc.m_arrColorIndexes[i] );

    arrColors.push_back( curColor );

    OdDbObjectId idCurLineStyle;

    setDwgLineTypeIdByDgnLineTypeIndex(pDb, pDg, desc.m_arrLineStyles[i], idCurLineStyle );

    arrLineTypes.push_back( idCurLineStyle );
  }
  
  double dCenterOffset = (dMinOffset + dMaxOffset) / 2.0;

  desc.m_bCenterIsZero = OdZero( dCenterOffset );

  if( desc.m_uJustification == OdDgMultiline::kByCenter )
  {
    for( i = 0; i < arrOffsets.size(); i++ )
    {
      arrOffsets[i] -= dCenterOffset;
    }
  }

  for( OdInt32 l = arrOffsets.size() - 1; l >= 0 ; l-- )
  {
    pMLStyle->addElement( arrOffsets[l], arrColors[l], arrLineTypes[l] );
  }

  pMLDic->setAt(strStyleName, pMLStyle);

  OdDbObjectId idStyle = pMLStyle->objectId();

  if( pContextData )
  {
    pContextData->m_mapMultilineStyles[idStyle] = desc;

    if( desc.m_bTableMLineStyle )
    {
      pContextData->m_mapTableMLStyleIds[ desc.m_uMLineStyle ] = idStyle;
    }
  }

  return idStyle;
}

//----------------------------------------------------------------------------

bool isEqualMLineStyle( const OdDgnImportMultilineDescriptor& desc1, 
                          const OdDgnImportMultilineDescriptor& desc2 
                      )
{
  bool bRet = true;

  if( bRet && (desc1.m_arrOffsets.size() != desc2.m_arrOffsets.size()) )
  {
    bRet = false;
  }

  if( desc1.m_bShowJoints != desc2.m_bShowJoints )
  {
    bRet = false;
  }

  if( bRet && (desc1.m_bShowStartCapLine != desc2.m_bShowStartCapLine) )
  {
    bRet = false;
  }

  if( bRet && (desc1.m_bShowStartCapInArc != desc2.m_bShowStartCapInArc) )
  {
    bRet = false;
  }

  if( bRet && (desc1.m_bShowStartCapOutArc != desc2.m_bShowStartCapOutArc) )
  {
    bRet = false;
  }

  if( bRet && (desc1.m_bShowEndCapLine != desc2.m_bShowEndCapLine) )
  {
    bRet = false;
  }

  if( bRet && (desc1.m_bShowEndCapInArc != desc2.m_bShowEndCapInArc) )
  {
    bRet = false;
  }

  if( bRet && (desc1.m_bShowEndCapOutArc != desc2.m_bShowEndCapOutArc) )
  {
    bRet = false;
  }

  if( bRet && (desc1.m_bShowFill != desc2.m_bShowFill) )
  {
    bRet = false;
  }


  if( bRet && !OdZero( desc1.m_dStartCapAngle - desc2.m_dStartCapAngle) )
  {
    bRet = false;
  }

  if( bRet && !OdZero( desc1.m_dEndCapAngle - desc2.m_dEndCapAngle) )
  {
    bRet = false;
  }

  if( bRet && desc1.m_bShowFill )
  {
    if( desc1.m_uFillColor != desc2.m_uFillColor )
    {
      bRet = false;
    }
  }

  if( bRet )
  {
    if( desc2.m_uJustification == OdDgMultiline::kByCenter )
    {
      if( !desc1.m_bCenterIsZero && (desc1.m_uJustification != OdDgMultiline::kByCenter) )
      {
        bRet = false;
      }
    }
  }

  bool bCheckByDifs = false;

  if( (desc2.m_uJustification == OdDgMultiline::kByMaximum) ||(desc2.m_uJustification == OdDgMultiline::kByMinimum) )
  {
    bCheckByDifs = true;
  }

  if( bRet )
  {
    bool bEqualElementData = true;

    for( OdUInt32 i = 0; i < desc1.m_arrOffsets.size(); i++ )
    {
      if( desc1.m_arrColorIndexes[i] != desc2.m_arrColorIndexes[i] )
      {
        bEqualElementData = false;
        break;
      }

      if( desc1.m_arrLineStyles[i] != desc2.m_arrLineStyles[i] )
      {
        bEqualElementData = false;
        break;
      }

      if( !bCheckByDifs && !OdZero(desc1.m_arrOffsets[i] - desc2.m_arrOffsets[i] ) )
      {
        bEqualElementData = false;
        break;
      }
      else if( bCheckByDifs && (i < (desc1.m_arrOffsets.size() - 1)) )
      {
        double dDif1 = desc1.m_arrOffsets[i] - desc1.m_arrOffsets[i+1];
        double dDif2 = desc2.m_arrOffsets[i] - desc2.m_arrOffsets[i+1];

        if( !OdZero(dDif2 - dDif1) )
        {
          bEqualElementData = false;
          break;
        }
      }
    }

    bRet = bEqualElementData;
  }

  return bRet;
}

//----------------------------------------------------------------------------

OdDbObjectId OdDgnImportContext::getMultilineStyle( const OdDgnImportMultilineDescriptor& desc )
{
  OdDbObjectId idRet;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    OdDbObjectId                   mlStyleId;

    if( !desc.m_bTableMLineStyle )
    {
      std::map<OdUInt64, OdDbObjectId>::iterator pMlStyleIter = pContextData->m_mapTableMLStyleIds.find(desc.m_uMLineStyle);

      if( pMlStyleIter != pContextData->m_mapTableMLStyleIds.end() )
      {
        mlStyleId = pMlStyleIter->second;

        std::map<OdDbObjectId, OdDgnImportMultilineDescriptor>::iterator pCurIter = pContextData->m_mapMultilineStyles.find(mlStyleId);

        if( pCurIter != pContextData->m_mapMultilineStyles.end() )
        {
          OdDgnImportMultilineDescriptor curDesc = pCurIter->second;

          if( isEqualMLineStyle( curDesc, desc ) )
          {
            idRet = mlStyleId;
          }
        }
      }
    }

    if( idRet.isNull() )
    {
      std::map<OdDbObjectId, OdDgnImportMultilineDescriptor>::iterator pIter = pContextData->m_mapMultilineStyles.begin();

      while( pIter != pContextData->m_mapMultilineStyles.end() )
      {
        OdDgnImportMultilineDescriptor curDesc = pIter->second;
        OdDbObjectId                   curId   = pIter->first;

        pIter++;

        if( curDesc.m_bTableMLineStyle )
        {
          continue;
        }

        if( !isEqualMLineStyle( curDesc, desc ) )
        {
          continue;
        }

        idRet = curId;
        break;
      }
    }
  }

  return idRet;
}

//----------------------------------------------------------------------------

void         OdDgnImportContext::clearMultilineStyles()
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    pContextData->m_mapMultilineStyles.clear();
  }
}

//----------------------------------------------------------------------------

OdUInt32 OdDgnImportContext::getDimAssocDescriptorCount()
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    return (OdUInt32)(pContextData->m_mapDimAssocDescripotors.size());
  }

  return 0;
}

//----------------------------------------------------------------------------

void     OdDgnImportContext::addDimAssocDescriptor( const OdDbObjectId& idDwgDim, 
                                                      const OdDgnImportDimAssocDescriptor& dimAssocDesc )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    pContextData->m_mapDimAssocDescripotors[idDwgDim] = dimAssocDesc;
  }
}

//----------------------------------------------------------------------------

void     OdDgnImportContext::getDimAssocDescriptor( OdUInt32 uIndex, 
                                                      OdDbObjectId& idDwgDim, 
                                                        OdDgnImportDimAssocDescriptor& dimAssocDesc )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    if( uIndex >= pContextData->m_mapDimAssocDescripotors.size() )
    {
      return;
    }

    std::map<OdDbObjectId, OdDgnImportDimAssocDescriptor>::iterator pIter = pContextData->m_mapDimAssocDescripotors.begin();

    for( OdUInt32 i = 0; i < uIndex; i++ )
    {
      pIter++;
    }

    idDwgDim     = pIter->first;
    dimAssocDesc = pIter->second;
  }
}

//----------------------------------------------------------------------------

void     OdDgnImportContext::clearDimAssocDescriptors()
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    pContextData->m_mapDimAssocDescripotors.clear();
  }
}

//----------------------------------------------------------------------------

void     OdDgnImportContext::addSymbolHatchDesc( const OdDgElementId& idSymbol, const OdDgnImportSymbolHatchDescriptor& hatchDesc )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    pContextData->m_mapSymbolHatch[idSymbol] = hatchDesc;
  }
}

//----------------------------------------------------------------------------

bool     OdDgnImportContext::getSymbolHatchDesc( const OdDgElementId& idSymbol, 
                                                   double dRowSpacing, 
                                                     double dColSpacing, 
                                                       OdDgnImportSymbolHatchDescriptor& hatchDesc )
{
  bool bRet = false;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    std::map<OdDgElementId, OdDgnImportSymbolHatchDescriptor>::iterator pIter = pContextData->m_mapSymbolHatch.find( idSymbol );

    if( pIter != pContextData->m_mapSymbolHatch.end() )
    {
      hatchDesc = pIter->second;

      if( OdZero(hatchDesc.m_dPatternRowSpacing - dRowSpacing, 1e-6) && OdZero(hatchDesc.m_dPatternColSpacing - dColSpacing, 1e-6) )
      {
        bRet = true;
      }
    }
  }

  return bRet;
}

//----------------------------------------------------------------------------

void     OdDgnImportContext::clearSymbolHatchDesc()
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    pContextData->m_mapSymbolHatch.clear();
  }
}

//----------------------------------------------------------------------------

void     OdDgnImportContext::setCellBlockNextIndex( const OdString& strCellName, OdUInt32 uIndex )
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    pContextData->m_mapCellNextBlockIndex[ strCellName ] = uIndex;
  }
}

//----------------------------------------------------------------------------

bool     OdDgnImportContext::getCellBlockNextIndex( const OdString& strCellName, OdUInt32& uIndex )
{
  bool bRet = false;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    std::map<OdString, OdUInt32>::iterator pIter = pContextData->m_mapCellNextBlockIndex.find( strCellName );

    if( pIter != pContextData->m_mapCellNextBlockIndex.end() )
    {
      bRet = true;
      uIndex = pIter->second;
    }
  }

  return bRet;
}

//----------------------------------------------------------------------------

bool OdDgnImportContext::isLevelVisibilityByLevelMask()
{
	bool bRet = false;

	OdDgnImportContextData* pContextData = getCurrentContext();

	if (pContextData)
	{
		bRet = pContextData->m_bSetLevelVisibilityByLevelMask;
	}

	return bRet;
}

//----------------------------------------------------------------------------

void OdDgnImportContext::setLevelVisibilityByLevelMask( bool bSet )
{
	OdDgnImportContextData* pContextData = getCurrentContext();

	if (pContextData)
		pContextData->m_bSetLevelVisibilityByLevelMask = bSet;
}

//----------------------------------------------------------------------------

OdDgElementId OdDgnImportContext::getActiveXRefId()
{
  OdDgElementId idRet;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
    idRet = pContextData->m_idActiveXRef;

  return idRet;
}

//----------------------------------------------------------------------------

void OdDgnImportContext::setActiveXRefId(const OdDgElementId& idXRef)
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    pContextData->m_idActiveXRef = idXRef;
  }
}

//----------------------------------------------------------------------------

void OdDgnImportContext::pushLevelTableOverride(std::map<OdDgElementId, OdDgElementId>& mapLevelOverrides)
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData )
  {
    pContextData->m_arrLevelOverrides.push_back(mapLevelOverrides);
  }
}

//----------------------------------------------------------------------------

void OdDgnImportContext::popLevelTableOverride()
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if( pContextData  && !pContextData->m_arrLevelOverrides.isEmpty() )
  {
    pContextData->m_arrLevelOverrides.removeLast();
  }
}

//----------------------------------------------------------------------------

OdDgElementId OdDgnImportContext::getLevelOverride(const OdDgElementId& idLevel)
{
  OdDgElementId idRet = idLevel;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData && pContextData->m_bUseLevelOverride && !pContextData->m_arrLevelOverrides.isEmpty() )
  {
    const std::map<OdDgElementId, OdDgElementId>& mapLevels = pContextData->m_arrLevelOverrides.last();
    std::map<OdDgElementId, OdDgElementId>::const_iterator pIter = mapLevels.find(idLevel);

    if (pIter != mapLevels.end())
      idRet = pIter->second;
  }

  return idRet;
}

//----------------------------------------------------------------------------

bool OdDgnImportContext::getUseLevelOverrideFlag()
{
  bool bRet = false;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    bRet = pContextData->m_bUseLevelOverride;
  }

  return bRet;
}

//----------------------------------------------------------------------------

void OdDgnImportContext::setUseLevelOverrideFlag(bool bSet)
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    pContextData->m_bUseLevelOverride = bSet;
  }
}

//----------------------------------------------------------------------------

OdDgElementId OdDgnImportContext::getOverridedLevelTable()
{
  OdDgElementId idRet;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    idRet = pContextData->m_idLevelTableOverride;
  }

  return idRet;
}

//----------------------------------------------------------------------------

void OdDgnImportContext::setOverridedLevelTable(const OdDgElementId& idLevelTableOverride)
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    pContextData->m_idLevelTableOverride = idLevelTableOverride;
  }
}

//----------------------------------------------------------------------------

bool OdDgnImportContext::getShowNewXRefLevelsFlag()
{
  bool bRet = false;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    bRet = pContextData->m_bShowNewXRefLevels;
  }

  return bRet;
}

//----------------------------------------------------------------------------

void OdDgnImportContext::setShowNewXRefLevelsFlag(bool bSet)
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    pContextData->m_bShowNewXRefLevels = bSet;
  }
}

//----------------------------------------------------------------------------

bool OdDgnImportContext::getCropXRefExtraClipByExtentsFlag()
{
  bool bRet = true;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    bRet = pContextData->m_bCropXRefExtraClipByExtents;
  }

  return bRet;
}

//----------------------------------------------------------------------------

void OdDgnImportContext::setCropXRefExtraClipByExtentsFlag(bool bSet)
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    pContextData->m_bCropXRefExtraClipByExtents = bSet;
  }
}

//----------------------------------------------------------------------------

OdGeMatrix3d OdDgnImportContext::getCellHeaderTransform()
{
  OdGeMatrix3d matRet;

  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
    matRet = pContextData->m_matCellTransform;

  return matRet;
}

//----------------------------------------------------------------------------

void         OdDgnImportContext::setCellHeaderTransform(const OdGeMatrix3d& matCellTransform)
{
  OdDgnImportContextData* pContextData = getCurrentContext();

  if (pContextData)
  {
    pContextData->m_matCellTransform = matCellTransform;
  }
}

//----------------------------------------------------------------------------

}
