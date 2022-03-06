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

#ifndef _DGN_IMPORTCONTEXT_INCLUDED_ 
#define _DGN_IMPORTCONTEXT_INCLUDED_

#define STL_USING_MAP
#include <OdaSTL.h>
#include <DgElementId.h>
#include <DgHostAppServices.h>
#include <DgModel.h>
#include <DgTable.h>
#include <DgLevelMask.h>
#include <DgView.h>
#include "DgAttributeLinkage.h"
#include "DgnImportImpl.h"
#include "DbHatch.h"

class OdDgDatabase;
class OdDbDatabase;
class OdDgLevelTableRecord;
class OdDbLayerTableRecord;
class OdDgElement;
class OdDgLineStyleResource;
class OdDgModel;


/** \details
  <group OdImport_Classes> 
*/
namespace TD_DGN_IMPORT {

class DgnImporter;

// Color map to convert dgn color index to dwg color.
struct OdDgnImportColorIndexDescription
{
  OdUInt8    m_uDwgColorIndex;
  ODCOLORREF m_clrDwgTrueColor;
  bool       m_bUseTrueColor;
};

// Dgn multiline style descriptor

struct OdDgnImportMultilineDescriptor
{
  bool              m_bShowJoints;
  bool              m_bShowStartCapLine;
  bool              m_bShowStartCapInArc;
  bool              m_bShowStartCapOutArc;
  bool              m_bShowEndCapLine;
  bool              m_bShowEndCapInArc;
  bool              m_bShowEndCapOutArc;
  bool              m_bShowFill;
  bool              m_bTableMLineStyle;
  bool              m_bCenterIsZero;
  double            m_dStartCapAngle;
  double            m_dEndCapAngle;
  OdUInt32          m_uFillColor;
  OdUInt32          m_uJustification;
  OdUInt64          m_uMLineStyle;
  OdArray<double>   m_arrOffsets;
  OdArray<OdUInt32> m_arrColorIndexes;
  OdArray<OdUInt32> m_arrLineStyles;
  OdString          m_strStyleName;
};

// Dwg dimension associativity descriptor

struct OdDgnImportDimAssocDescriptor
{
  OdDgnImportDimAssocDescriptor()
  {
    bRadialDiamDimension = false;
  }

  OdDgAssocPointRootPtr point1Desc;
  OdDgAssocPointRootPtr point2Desc;
  OdDgAssocPointRootPtr point3Desc;
  OdDgAssocPointRootPtr point4Desc;
  bool                  bRadialDiamDimension;
};

// Dwg symbol hatch descriptor

struct OdDgnImportSymbolHatchDescriptor
{
  OdHatchPattern m_hatchPattern;
  double         m_dHatchScale;
  OdUInt32       m_uColorIndex;
  double         m_dPatternRowSpacing;
  double         m_dPatternColSpacing;
};

// View flags

class OdDgnImportViewFlags
{
  public:
    OdDgnImportViewFlags();
    virtual ~OdDgnImportViewFlags();

    void init(const OdDgView* pView);
    void init(const OdDgReferenceAttachmentHeader* pXRef, OdUInt32 uViewIndex, const OdDgnImportViewFlags& defaultValues);

    bool getShowTextsFlag() const;
    void setShowTextsFlag(bool bSet);

    bool getShowTagsFlag() const;
    void setShowTagsFlag(bool bSet);

    bool getShowTextNodesFlag() const;
    void setShowTextNodesFlag(bool bSet);

    bool getShowPatternsFlag() const;
    void setShowPatternsFlag(bool bSet);

    bool getShowLineStylesFlag() const;
    void setShowLineStylesFlag(bool bSet);

    bool getShowLineWeightsFlag() const;
    void setShowLineWeightsFlag(bool bSet);

    bool getShowFillsFlag() const;
    void setShowFillsFlag(bool bSet);

    bool getShowConstructionFlag() const;
    void setShowConstructionFlag(bool bSet);

    bool getShowDimensionsFlag() const;
    void setShowDimensionsFlag(bool bSet);

    bool getUseTransparencyFlag() const;
    void setUseTransparencyFlag(bool bSet);

    bool getUseLevelSymbologyFlag() const;
    void setUseLevelSymbologyFlag(bool bSet);

  private:
    bool m_bShowTexts;
    bool m_bShowTags;
    bool m_bShowTextNodes;
    bool m_bShowPatterns;
    bool m_bShowLineStyles;
    bool m_bShowLineWeights;
    bool m_bShowFills;
    bool m_bShowConstruction;
    bool m_bShowDimensions;
    bool m_bUseTransparency;
    bool m_bUseLevelSymbology;    
};

//

class OdDgnImportContext
{
public:
  // Color transform
  static void pushPalette();
  static void popPalette();
  static void setPalette( OdDgDatabase* pDb );
  static void setPalette( const ODCOLORREF* pPalette );
  static void setBackgroundColor( ODCOLORREF bgColor );
  static bool getDwgColor( OdUInt32 uDgnColorIndex, OdDgnImportColorIndexDescription& retColor );
  static bool getConvertColorIndexToTrueColorFlag();
  static void setConvertColorIndexToTrueColorFlag( bool bSet );
  // Reference attachment map
  static void addDwgModelBlockId( const OdString& strFileName, const OdDgElementId& idModel, const OdDgLevelTable* pLevelTable,
                                  const OdString& strLevelMaskExt, const OdDbObjectId& idBlockDefinition );
  static OdDbObjectId getDwgModelBlockId( const OdString& strFileName, const OdDgElementId& idModel, const OdDgLevelTable* pLevelTable, const OdString& strLevelMaskExt );
  static OdUInt32 getXRefNestedDepth();
  static void     pushXRef( const OdString& strFileName, const OdDgElementId& idModel, const OdDgLevelTable* pLevelTable,
                            const OdDgElementId& idXRef, OdUInt32 uNestedDepth, const OdString& strLevelMaskExt );
  static void     popXRef();
  static bool     isXRefInStack( const OdString& strFileName, const OdDgElementId& idModel );
  static OdDgElementId getXRefId( OdUInt32 uIndex );
  static void     removeLastXRef();
  static void     restoreLastXRef();
  static bool     checkNestedDepth();
  // Global line style scales
  static bool getGlobalLineScale( double& dLineScale );
  static void pushGlobalLineScale( double dLineScale );
  static void popGlobalLineScale();
  // Continuous line style from dgn
  static OdDbObjectId getDgnContinuousLineStyleId();
  // Hatches
  static bool getImportCurvesOnlyFlag();
  static void setImportCurvesOnlyFlag( bool bSet );
  static bool getSkipPatternDrawFlag();
  static void setSkipPatternDrawFlag( bool bSet );
  // Text styles
  static bool isFontsEqual( const OdFont* pFont1, const OdFont* pFont2 );
  static OdDbObjectId createStyleForDbText( OdDbDatabase* pDb, OdDgDatabase* pDgDb, const OdGiTextStyle& textStyle, 
    bool bCheckHeight = true, bool bSetZeroHeightForNew = false);
  static OdDbObjectId getStyleForDbText(OdDbDatabase* pDb, const OdGiTextStyle& textStyle);
  static bool getConvertEmptyDataFieldsToSpacesFlag();
  static void setConvertEmptyDataFieldsToSpacesFlag( bool bSet );
  // Shared Cells
  static bool getLayerByBlockMode();
  static void setLayerByBlockMode( bool bSet );
  static bool getLockColorMode();
  static void setLockColorMode(bool bSet);
  static bool getLockLineWeightMode();
  static void setLockLineWeightMode(bool bSet);
  static bool getLockLineStyleMode();
  static void setLockLineStyleMode(bool bSet);
  static OdUInt32 getLockColor();
  static void setLockColor(OdUInt32 uColorIndex);
  static OdUInt32 getLockLineWeight();
  static void setLockLineWeight(OdUInt32 uLineWeight);
  static OdUInt32 getLockLineStyle();
  static void setLockLineStyle(OdUInt32 uLineStyleIndex);
  static void addBlockForSharedCellOverride( const OdString& strKey, const OdDbObjectId& idBlock);
  static OdDbObjectId getBlockForSharedCellOverride(const OdString& strKey);
  static void clearBlockForSharedCellOverrideMap();
  // Id Map
  static void addCellHeaderIdToPath( const OdDbObjectId& idCellHeader );
  static void removeLastCellHeaderIdFromPath();
  static OdDbObjectId getObjectId( const OdDgElementId& idDgnElement );
  static bool getObjectPath( const OdDgElementId& idDgnElement, OdDgnImportPathToDwgObject& dwgPath );
  static void addObjectPath( const OdDgElementId& idDgnElement, OdDgnImportPathToDwgObject& dwgPath );
  static void addResourceId( const OdDbObjectId& idResource );
  static void setResourceUsage( const OdDbObjectId& idResource );
  // Dimensions
  static bool isNoteDimensionCell( const OdDgElementId& idCellHeader );
  static void addNoteDimensionCell( const OdDgElementId& idCellHeader );
  static void removeNoteDimensionCell( const OdDgElementId& idCellHeader );

  static void   addScaledBlock(const OdDbObjectId& idBlock, double dDimTermScale);
  static double getScaleOfBlockTableRecord(const OdDbObjectId& idBlock);
  //
  static void         restoreAfterImport();
  static void         prepareToImport( DgnImporter* dgnImporter, bool bCopyLevelMasks = false );
  static DgnImporter* getDgnImporter();
  static bool         getInternalImportFlag();
  static void         setInternalImportFlag( bool bSet );
  // Level Masks
  static bool isLevelMask();
  static bool checkLevelMask( OdUInt32 uLevelEntryId, bool bDefaultValue = true);
  static OdString getLevelMaskString();
  static void pushLevelMask( const OdDgLevelMaskPtr& pLevelMask, const OdDgLevelTablePtr& pLevelTable, bool bShowNewLevels = false);
  static void popLevelMask();
	static bool isLevelVisibilityByLevelMask();
	static void setLevelVisibilityByLevelMask(bool bSet);
  static OdDgElementId getActiveXRefId();
  static void setActiveXRefId( const OdDgElementId& idXRef );
  // Level table overrides
  static void pushLevelTableOverride(std::map<OdDgElementId, OdDgElementId>& mapLevelOverrides);
  static void popLevelTableOverride();
  static OdDgElementId getLevelOverride(const OdDgElementId& idLevel);
  static bool getUseLevelOverrideFlag();
  static void setUseLevelOverrideFlag(bool bSet);
  static OdDgElementId getOverridedLevelTable();
  static void setOverridedLevelTable(const OdDgElementId& idLevelTableOverride);
  static bool getShowNewXRefLevelsFlag();
  static void setShowNewXRefLevelsFlag(bool bSet);
  // XRef clip mode
  static bool getCropXRefExtraClipByExtentsFlag();
  static void setCropXRefExtraClipByExtentsFlag( bool bSet );
  // Active View
  static OdDgViewPtr getActiveView();
  static void        setActiveView( const OdDgViewPtr& pView );
  static void pushViewFlags(const OdDgnImportViewFlags& viewFlags);
  static void popViewFlags();
  static OdDgnImportViewFlags getActualViewFlags();
  static void claerViewFlags();
  // Import invisible elements
  static bool isImportInvisible();
  static void setImportInvisible( bool bSet );
  // Text import mode
  static bool isImportDgTextAsDbMText();
  static void setImportDgTextAsDbMText(bool bSet);
  // Fast access to polygon import modes
  static OdUInt8 getShape3dImportMode();
  static OdUInt8 getShape2dImportMode();
  static OdUInt8 getObject3dImportMode();
  static OdUInt8 getEllipse3dImportMode();
  static OdUInt8 getEllipse2dImportMode();
  static OdUInt8 getClosedBSplineCurve3dImportMode();
  static OdUInt8 getClosedBSplineCurve2dImportMode();
  static void    setCurvesOnlyImportMode();
  static void    setUpdateCurvesImportMode();
  // Rsc to Shx conversion
  static OdUInt32 getRscFontCount();
  static OdString getRscFontName( OdUInt32 uIndex );
  static void     addRscFontName( const OdString& strName );
  static void     createShxFontFromRscFont( const OdString& strFontName, OdDgDatabase* pDgDb, OdDbHostAppServices* pHostAppServices, const OdString& strShxPath );
  static void     clearRscFontArray();
  // Import multilines
  static OdDbObjectId createMultilineStyle( const OdDgnImportMultilineDescriptor& desc, OdDbDatabase* pDb, OdDgDatabase* pDg );
  static OdDbObjectId getMultilineStyle( const OdDgnImportMultilineDescriptor& desc );
  static void         clearMultilineStyles();
  // Dimension association points
  static void     convertAccuracyToDwgFormat( OdDgDimTextFormat::Accuracy dgnAccur, OdUInt8& uDwgUnitsType, OdUInt8& uPresission );
  static OdUInt32 getDimAssocDescriptorCount();
  static void     addDimAssocDescriptor( const OdDbObjectId& idDwgDim, const OdDgnImportDimAssocDescriptor& dimAssocDesc );
  static void     getDimAssocDescriptor( OdUInt32 uIndex, OdDbObjectId& idDwgDim, OdDgnImportDimAssocDescriptor& dimAssocDesc );
  static void     clearDimAssocDescriptors();
  // Symbol Hatch
  static void     addSymbolHatchDesc( const OdDgElementId& idSymbol, const OdDgnImportSymbolHatchDescriptor& hatchDesc );
  static bool     getSymbolHatchDesc( const OdDgElementId& idSymbol, double dRowSpacing, double dColSpacing, OdDgnImportSymbolHatchDescriptor& hatchDesc );
  static void     clearSymbolHatchDesc();
  // Cell block index
  static void     setCellBlockNextIndex( const OdString& strCellName, OdUInt32 uIndex );
  static bool     getCellBlockNextIndex( const OdString& strCellName,  OdUInt32& uIndex );
  // Cell header transform
  static OdGeMatrix3d getCellHeaderTransform();
  static void         setCellHeaderTransform(const OdGeMatrix3d& matCellTransform);
};

}
#endif // _DGN_IMPORTCONTEXT_INCLUDED_
