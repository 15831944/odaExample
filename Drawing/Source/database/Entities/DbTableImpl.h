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

#ifndef _ODDBTABLIMPL_INCLUDED_
#define _ODDBTABLIMPL_INCLUDED_

#include "DbBlockReferenceImpl.h"
#include "DbObjectId.h"
#include "CmColor.h"
#include "DbTable.h"
#include "TableVariant.h"
#include "Ge/GeVector3d.h"
#include "DbTableContent.h"
#include "Ge/GeDoubleArray.h"

class OdTableAttrDef
{
public:
  OdTableAttrDef() :  m_index(0) {}

  OdDbObjectId   m_attributeDefId;
  OdInt16        m_index;
  OdString       m_text;
};

class OdPropertyValuePair
{
public:
  OdUInt32         key;
  OdTableVariant  val;
  
  OdPropertyValuePair() {}
  OdPropertyValuePair(OdUInt32 pkey, const OdTableVariant& pval) : key(pkey), val(pval) {}
};

/*
    m_edgeFlags and m_virtualEdgeFlag

    Specifies which edges have property overrides in a cell, 1 = top, 2 =  
  right, 4 = bottom, 8 = left. Note that if a shared edge between two  
  cells has property overrides, the edge overrides flag is set in both  
  adjacent cells, but in one of them the edge is marked as virtual. So  
  the virtual edge flag property determines where the override is  
  stored: each property override is stored only once. When a virtual  
  edge flag is set, the override is determined by the adjacent cell,  
  when it is not set it is determined by the cell itself. Normally a  
  property override is stored with the cell on which the user made the  
  modification, but sometimes when the user makes multiple changes in  
  both adjacent cells, e.g. a color modification in cell A, and a line  
  weight modification in cell B (adjacent to cell A), then for the  
  shared edge, the property overrides for both color and line weight are  
  stored in the same cell (either A or B). The reason for this is that  
  the virtual edge flag doesn't allow to discriminate between individual  
  properties, only on the edge level.
*/

class OdCell
{
public:
  OdCell();
  
  OdDb::CellType m_type;
  
  OdUInt32       m_edgeFlags;
  OdUInt8        m_virtualEdgeFlag;

  bool           m_bMerged;
  bool           m_bAutoFit;
  OdUInt32       m_mergedWidth;
  OdUInt32       m_mergedHeight;
  double         m_dRotation;
  // OdString       m_strText; // it is moved to m_value
  OdDbObjectId   m_objectId; // field ID to text cell
                             // block ID to block cell
  double         m_dBlockScale;

  OdArray<OdTableAttrDef>  m_blockAttribs;

  OdUInt32       m_flagOverrides;
  OdUInt32       m_extendedFlag;
  OdValue        m_value;

private:
  void dwgInEdgeProperty(OdDbDwgFiler* pFiler, OdUInt32 flags, OdUInt32 shift);
  void dwgOutEdgeProperty(OdDbDwgFiler* pFiler, OdUInt32 flags, OdUInt32 shift) const;

public:
  // This contains property overrides.
  OdArray<OdPropertyValuePair>  m_property;
  void setValue(OdUInt32 key, const OdTableVariant& val);
  bool getValue(OdUInt32 key, OdTableVariant& val) const;
  void removeValue(OdUInt32 key);

  void dwgIn(OdDbDwgFiler* pFiler);
  void dwgOut(OdDbDwgFiler* pFiler, OdDbDatabase* pDb, const OdDbObjectId& textStyleId) const;

  bool dxfIn(OdDbDxfFiler* pFiler, OdDbDatabase* pDb);
  void dxfOut(OdDbDxfFiler* pFiler, OdDbDatabase* pDb, const OdDbObjectId& textStyleId) const;

  void updateFlagOverrides();
  void getOverrides( OdUInt32Array& overrides) const;
  bool isOverrided(OdUInt32 val) const;
  void setContent(OdCell* cell);
  void setRoudtripData(double checkSum, OdUInt32 flag91, OdUInt32 flag92, const OdResBufPtr& xRec);
  void getRoudtripData(double& checkSum, OdUInt32& flag91, OdUInt32& flag92, OdResBufPtr& xRec) const;
  OdString getText() const;
  void setText(const OdString& text);
};

typedef OdArray<OdCell> OdRow;
typedef OdArray<OdRow>  OdTable;

class OdCellCalcCache
{
public:
  OdCellCalcCache():
      m_Height(0.0),
      m_Width(0.0),
      m_IsValid(false),
      m_BlkScale(1.0)
  {}
  bool m_IsValid;
  double m_Height;
  double m_Width;
  double m_BlkScale;
  OdDbEntityPtr m_Entity;
  OdGeVector3d  m_Position;
};

typedef OdArray<OdCellCalcCache> OdRowCache;
typedef OdArray<OdRowCache>  OdTableCache;

enum TypeCellEdgeKey {
  kColorKey = 0,
  kLineWeightKey = 1,
  kVisibilityKey = 2
};

class OdBreakHeight
{
public:
  OdBreakHeight() : m_height(0.0)
    , m_flag(2)   // #17033
  {}

  OdGeVector3d m_position;
  double m_height;
  OdInt32 m_flag;
};


/** Description:
*   This is calculated data based on OdBreakHeight.
*/
class OdBreakRowRange
{
public:
  OdBreakRowRange() : m_startRow(0)
    , m_endRow(0)
    , m_actHeight(0.0)
  {}

  OdGeVector3d m_position;
  OdInt32    m_startRow;
  OdInt32    m_endRow;
  double     m_actHeight;
};

typedef OdArray<OdBreakRowRange>  OdBreakColumnsData;
typedef OdArray<OdBreakHeight>  OdBreakHeightsData;

class OdBreakData
{
public:
  OdBreakData() : m_option(OdDb::kTableBreakNone)
    , m_flowDirection(OdDb::kTableBreakFlowRight)
    , m_breakSpacing(0.99)
    , m_unknownFlag1(0)
    , m_unknownFlag2(0)
  {
  }

 
  OdInt32  m_option;          // OdDb::TableBreakOption 
  OdInt32  m_flowDirection;   // OdDb::TableBreakFlowDirection 
  OdBreakHeightsData m_breakHeightData;

  double m_breakSpacing;
  OdBreakColumnsData m_breakColData;
  OdDbObjectIdArray m_subTables; // Points to OdDbTable
  OdInt32 m_unknownFlag1;
  OdInt32 m_unknownFlag2;
  void clear() 
  {
    m_option = (OdInt32)OdDb::kTableBreakNone;
    m_flowDirection = (OdInt32)OdDb::kTableBreakFlowRight;
    m_breakSpacing = 0.99;
    m_unknownFlag1 = m_unknownFlag2 = 0;
    m_breakHeightData.clear();
    m_breakColData.clear();
    m_subTables.clear();
  }
};


class RoundTrip2008Data
{
public:
  OdDbObjectId m_contentID;
  OdDbObjectId m_geometryID;

  RoundTrip2008Data() {}
};

/** Description:
  The ACAD_TABLE entity was introduced in AutoCAD 2005.
  In AutoCAD 2008 completely new data structures were introduced 
  (rooted in the OdDbTableContent object), which coexist in parallel to the 2005 data structures.
  I.e. in a file written by AutoCAD 2008, the file will contain both the 2005 and 2008 data 
  structures, having considerable overlap.
  The new 2008 data structures are now the main data structures,
  and the old ones are filled (using method setFromContent) upon saving.
  The opposite may also happen, when reading an old file,
  in this case table content is created using method makeContent upon loading.
  The new data structures are available through field m_Content.

  A brief mapping of 2005 to 2008 classes (some 2008 classes have no 2005 counterpart):

  OdCell -> OdCellData + OdCellContent
  OdRow -> OdRowData
  OdColumn -> OdColunData
  OdTableAttrDef -> OdAttrContent
  OdPropertyValuePair -> No longer used, 
    can directly specify propery overrides using OdCellStyle override flags.
*/

class OdDbTableImpl : public OdDbBlockReferenceImpl
{
  static OdDbTableImpl* getImpl(const OdDbTable *pObj)
  { return (OdDbTableImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
  OdDbTableImpl();

  OdDbHardPointerId  m_tableStyleId; 
  OdGeVector3d      m_vDir;
  OdUInt32          m_flagsValue;
  OdUInt32          m_columns;
  OdUInt32          m_rows;
  OdGeDoubleArray   m_columnWidths;
  OdGeDoubleArray   m_rowHeights;

  // flags
  OdUInt32          m_flagOverrides;
  OdUInt32          m_flagBorderColorOverrides;
  OdUInt32          m_flagBorderLWOverrides;
  OdUInt32          m_flagBorderVisibilityOverrides;

  OdArray<OdPropertyValuePair>  m_property; // This contains property overrides.
  void setValue(OdUInt32 key, const OdTableVariant& val);
  bool getValue(OdUInt32 key, OdTableVariant& val) const;
  void removeValue(OdUInt32 key);

  OdTable           m_table;
  // OdTableCache      m_tableCache;
  // used for recompute block
  // -1.0 is indicate that these value isn't used
  // double m_width;
  // double m_height;
  RoundTrip2008Data m_savedRT2008Data;
  
  OdBreakData  m_breakData;
  OdDbBlockTableRecordPtr m_pNDBRBlock;

  // This contains the main table data that was introduced in AutoCAD 2008.
  // It is gotten from m_savedRT2008Data above.
  // Upon loading/saving, the old and new data are synchronized.
  // This happens in the setFromContent and makeContent methods.
  OdDbTableContentPtr m_content;

  // R24 data
  OdInt8 m_unknown_R21_I8;
  OdDbObjectId m_tableTemplateID;
  OdInt32  m_unknown_R24_I32_1;
  bool  m_unknown_R24_B;
  OdInt32  m_unknown_I32_2;

  OdInt16 m_unknown_R24_I16;
  OdGeVector3d m_unknown_R24_V_2;

  OdInt32 m_rowMin, m_rowMax;
  OdInt32 m_colMin, m_colMax;
  OdInt32 m_subTableSelect;
  OdGePoint3d       m_HitPoint;
  OdUInt8           m_runTimeFlags;

  double  m_dIndicatorTextSize;
  double  m_dIndicatorHeight;
  double  m_dIndicatorWidth;
  bool    m_bHasDataRows;

  bool    m_reattachDatalink;
  OdCmEntityColor m_bgLabelClr, m_txtLabelClr, m_mrkLabelClr, m_linkLabelClr, m_boxLabelClr;;

  enum
  {
    kHasSubSelection = 1,
    kIsNewTable = 2,
    kHasClonedBlock = 4,
    kHighlighted = 8,
    kDragging = 16,
    kSuppressRegenarate = 32
  };
  bool hasSubSelection() const { return GETBIT(m_runTimeFlags, kHasSubSelection); }
  void setHasSubSelection(bool value) { SETBIT(m_runTimeFlags, kHasSubSelection, value); }
  bool isNewTable() const { return GETBIT(m_runTimeFlags, kIsNewTable); }
  void setIsNewTable(bool value) { SETBIT(m_runTimeFlags, kIsNewTable, value); }
  bool hasClonedBlock() const { return GETBIT(m_runTimeFlags, kHasClonedBlock); }
  void setHasClonedBlock(bool value) { SETBIT(m_runTimeFlags, kHasClonedBlock, value); }
  bool isHighlighted() const { return GETBIT(m_runTimeFlags, kHighlighted); }
  void setIsHighlighted(bool value) { SETBIT(m_runTimeFlags, kHighlighted, value); }
  bool isDragging() const { return GETBIT(m_runTimeFlags, kDragging); }
  void setIsDragging(bool value) { SETBIT(m_runTimeFlags, kDragging, value); }
  bool isSuppressRegenarate() const { return GETBIT(m_runTimeFlags, kSuppressRegenarate); }
  void setIsSuppressRegenarate(bool value) { SETBIT(m_runTimeFlags, kSuppressRegenarate, value); }


  void dwgInTableOverrides(OdDbDwgFiler* pFiler);
  void dwgInBorderColorOverrides(OdDbDwgFiler* pFiler);
  void dwgInBorderLWOverrides(OdDbDwgFiler* pFiler);
  void dwgInBorderVisibilityOverrides(OdDbDwgFiler* pFiler);

  void dwgOutTableOverrides(OdDbDwgFiler* pFiler) const;
  void dwgOutBorderColorOverrides(OdDbDwgFiler* pFiler) const;
  void dwgOutBorderLWOverrides(OdDbDwgFiler* pFiler) const;
  void dwgOutBorderVisibilityOverrides(OdDbDwgFiler* pFiler) const;

  bool getCell(OdUInt32 row, OdUInt32 col, OdCell& cell) const;
  OdCell* getCell(OdUInt32 row, OdUInt32 col);

  OdResult generateLayout();

  OdDbTableStylePtr getTableStylePtr() const
  {
    OdDbObjectPtr pObject = m_tableStyleId.openObject();
    if( pObject.isNull() )
    {
      if ( database() )
      {
        OdDbTableImpl* pThis = const_cast<OdDbTableImpl*>(this);
        pThis->setDefaultTableStyle( database() );
      }
    }
    return m_tableStyleId.safeOpenObject();
  }
  OdDb::RowType rowType(OdUInt32 row) const;
  OdDb::RowType rowTypeContent(OdUInt32 row) const;

  OdDb::FlowDirection flowDirection() const;
  void setFlowDirection(OdDb::FlowDirection flow);

  bool isTitleSuppressed() const;
  void suppressTitleRow(bool value);
  bool isHeaderSuppressed() const;
  void suppressHeaderRow(bool value);

  double horzCellMargin() const;
  void setHorzCellMargin(double gap);
  double vertCellMargin() const;
  void setVertCellMargin(double gap);

  OdDb::CellAlignment alignment(OdDb::RowType type) const;
  void setAlignment(OdDb::CellAlignment align, OdUInt32 rowTypes);

  bool isBackgroundColorNone(OdDb::RowType type) const;
  void setBackgroundColorNone(bool value, OdUInt32 rowTypes);

  OdCmColor  backgroundColor(OdDb::RowType type) const;
  void setBackgroundColor(const OdCmColor& color, OdUInt32 rowTypes);

  OdCmColor contentColor(OdDb::RowType type) const;
  void setContentColor(const OdCmColor& color, OdUInt32 rowTypes);

  OdDbObjectId  textStyle(OdDb::RowType type) const;
  void setTextStyle(const OdDbObjectId& id, OdUInt32 rowTypes);

  double textHeight(OdDb::RowType type) const;
  void setTextHeight(double height, OdUInt32 rowTypes);

  OdDb::LineWeight gridLineWeight(OdDb::GridLineType gridlineType, OdDb::RowType type) const;
  void setGridLineWeight(OdDb::LineWeight lwt, OdUInt32 nBorders, OdUInt32 nRows);

  OdCmColor gridColor(OdDb::GridLineType gridlineType, OdDb::RowType type) const;
  void setGridColor(const OdCmColor& color, OdUInt32 nBorders, OdUInt32 nRows);

  OdDb::Visibility gridVisibility(OdDb::GridLineType gridlineType, OdDb::RowType type) const;
  void setGridVisibility(OdDb::Visibility visible, OdUInt32 nBorders, OdUInt32 nRows);

  bool tableStyleOverrides( OdUInt32Array& overrides) const;
  void clearTableStyleOverrides(int options);
  bool cellStyleOverrides(OdUInt32 row, OdUInt32 col, OdUInt32Array& overrides) const;

  void deleteCellContent(OdUInt32 row, OdUInt32 col);

  OdDb::CellType cellType(OdUInt32 row, OdUInt32 col) const;
  void setCellType(OdUInt32 row, OdUInt32 col, OdDb::CellType type);

  OdString textString(OdUInt32 row, OdUInt32 col) const;
  void setTextString(OdUInt32 row, OdUInt32 col, const OdString& text);

  OdDbObjectId fieldId(OdUInt32 row, OdUInt32 col) const;
  void setFieldId(OdUInt32 row, OdUInt32 col, const OdDbObjectId& fieldId);

  OdDbObjectId textStyle(OdUInt32 row, OdUInt32 col) const;
  void setTextStyle(OdUInt32 row, OdUInt32 col, const OdDbObjectId& id);

  double textHeight(OdUInt32 row, OdUInt32 col) const;
  void setTextHeight(OdUInt32 row, OdUInt32 col, double height);

  OdDb::RotationAngle textRotation(OdUInt32 row, OdUInt32 col) const;
  void setTextRotation(OdUInt32 row, OdUInt32 col, OdDb::RotationAngle rot);

  OdDb::CellAlignment alignment(OdUInt32 row, OdUInt32 col) const;
  void setAlignment(OdUInt32 row, OdUInt32 col, OdDb::CellAlignment align);

  bool isBackgroundColorNone(OdUInt32 row, OdUInt32 col) const;
  void setBackgroundColorNone(OdUInt32 row, OdUInt32 col, bool value);

  OdCmColor backgroundColor(OdUInt32 row, OdUInt32 col) const;
  void setBackgroundColor(OdUInt32 row, OdUInt32 col, const OdCmColor& color);

  OdCmColor contentColor(OdUInt32 row, OdUInt32 col) const;
  void setContentColor(OdUInt32 row, OdUInt32 col, const OdCmColor& color);

  bool isAutoScale(OdUInt32 row, OdUInt32 col) const;
  void setAutoScale(OdUInt32 row, OdUInt32 col, bool autoFit);

  OdDbObjectId blockTableRecordId(OdUInt32 row, OdUInt32 col) const;
  void setBlockTableRecordId(OdUInt32 row, OdUInt32 col, const OdDbObjectId& blkId, bool autoFit);

  double blockScale(OdUInt32 row, OdUInt32 col) const;
  void setBlockScale(OdUInt32 row, OdUInt32 col, double scale);

  double blockRotation(OdUInt32 row, OdUInt32 col) const;
  void setBlockRotation(OdUInt32 row, OdUInt32 col, double rotAng);

  void getBlockAttributeValue(OdUInt32 row, OdUInt32 col, const OdDbObjectId& attdefId, OdString& value) const;
  void setBlockAttributeValue(OdUInt32 row, OdUInt32 col, const OdDbObjectId& attdefId, const OdString& value);

  OdCmColor gridColor(OdUInt32 row, OdUInt32 col, OdDb::CellEdgeMask iEdge);
  void setGridColor(OdUInt32 row, OdUInt32 col, OdInt16 nEdges, const OdCmColor& color);

  OdDb::Visibility gridVisibility(OdUInt32 row, OdUInt32 col, OdDb::CellEdgeMask iEdge);
  void setGridVisibility(OdUInt32 row, OdUInt32 col, OdInt16 nEdges, OdDb::Visibility value);

  OdDb::LineWeight gridLineWeight(OdUInt32 row, OdUInt32 col, OdDb::CellEdgeMask iEdge);
  void setGridLineWeight(OdUInt32 row, OdUInt32 col, OdInt16 nEdges, OdDb::LineWeight value);

  void updateFlagOverrides();
  void correctValueOverrides();

  OdDb::GridLineType getGridLineType(OdUInt32 row, OdUInt32 col, 
                               OdDb::CellEdgeMask iEdge, OdDb::RowType& rType); //, const OdDbTable* mTable);

  void calcCellGridsOnly(OdDbTable* table, OdTableCache& cellSet);
  void calcCells(OdDbTable* table, OdTableCache&);
  void calcTextCell(OdDbTable* table, OdUInt32 row, OdUInt32 col, 
              double CellWidth, double CellHeight, OdCellCalcCache* CellSet, OdInt32 content = -1);
  void calcBlockCell(OdDbTable* table, OdUInt32 row, OdUInt32 col, 
              double CellWidth, double CellHeight, OdCellCalcCache* CellSet, OdInt32 content = -1);
  void calcMultipleContentCell(OdDbTable* table, OdUInt32 row, OdUInt32 col, 
              double CellWidth, double CellHeight, OdCellCalcCache* CellSet, OdRowCache* cellProp = NULL);
  void calcMultipleContentCellMin(OdDbTable* table, OdUInt32 row, OdUInt32 col,
              double CellWidth, double CellHeight, OdCellCalcCache* CellSet);

  OdCell* getAdjoiningCell(OdUInt32 row, OdUInt32 col, OdDb::CellEdgeMask dir);
  void adjustCellFlags();
  bool adjustRowColumnSize(OdDbTable* table, OdTableCache&);

  void setEgdeProperty( OdUInt32 row, OdUInt32 col,
              OdDb::CellEdgeMask iEdge, TypeCellEdgeKey typeKey, const OdTableVariant &val);
  void clearEgdeProperty( OdUInt32 row, OdUInt32 col,
              OdDb::CellEdgeMask iEdge, TypeCellEdgeKey typeKey);
  // void updateTableCache();
  void mergeCells(OdUInt32 minRow, OdUInt32 maxRow, OdUInt32 minCol, OdUInt32 maxCol);
  void unmergeCells(OdUInt32 minRow, OdUInt32 maxRow, OdUInt32 minCol, OdUInt32 maxCol);
  bool isMergedCell(OdUInt32 row, OdUInt32 col, OdUInt32* minRow, OdUInt32* maxRow,
            OdUInt32* minCol, OdUInt32* maxCol) const;

  void getDataType(OdValue::DataType& nDataType, OdValue::UnitType& nUnitType, OdDb::RowType type) const;
  void setDataType(OdValue::DataType nDataType, OdValue::UnitType nUnitType, int nRowTypes);
  OdString format(OdDb::RowType type) const;
  void setFormat(const OdString& pszFormat, int nRowTypes);
  void getDataType(OdUInt32 row, OdUInt32 col, OdValue::DataType& nDataType, OdValue::UnitType& nUnitType) const;
  void setDataType(OdUInt32 row, OdUInt32 col, OdValue::DataType nDataType, OdValue::UnitType nUnitType);
  OdValue value(OdUInt32 row, OdUInt32 col) const;
  void setValue(OdUInt32 row, OdUInt32 col, const OdValue& val);
  void setValue(OdUInt32 row, OdUInt32 col, OdString& pszText, OdValue::ParseOption nOption);
  void resetValue(OdUInt32 row, OdUInt32 col);
  OdString format(OdUInt32 row, OdUInt32 col) const;
  void setFormat(OdUInt32 row, OdUInt32 col, const OdString& pszFormat);

  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version, OdDbAuditInfo* pAuditInfo);

  OdInt32 getCellExtents(const OdDbTable* table, OdInt32 iRow, OdInt32 iCol, OdGePoint3dArray& pts);

  OdGeMatrix3d tableTranform(OdDb::FlowDirection flowDir);
  void convertToSysCodePage();
  void correctTextCoding();

  void setDefaultTableStyle(OdDbDatabase* pDb);
  void audit(OdDbAuditInfo* pAuditInfo);

  void startSettingEntities(OdDbBlockTableRecordPtr pRec);
  OdDbObjectId setEntity(OdDbBlockTableRecordPtr pRec, OdDbEntity* pEntity);
  void finishSettingEntities(OdDbBlockTableRecordPtr pRec, OdGeMatrix3d matr);

  void setCastShadows(bool) {}
  bool castShadows() const { return false; }

  void setReceiveShadows(bool) {}
  bool receiveShadows() const { return false; }

  OdResBufPtr read2007RoundTripData(OdResBufPtr pRb1, bool& pre2007);
  OdResBufPtr read2008RoundTripData(OdResBufPtr pRb1, OdDb::SaveType format, OdBreakData* brData);

  void composeData(OdDbObject *pObj, OdDb::DwgVersion version, OdDb::SaveType format, OdDbTableContentPtr content);
  void makeContent(OdDbObject *pObj, OdDbTableContentPtr content);
  void makeTableGeometryData(OdDbObject *pObj);
  void setFromContent(OdDbTableContentPtr content, bool bUseBreakData = false);
  void copyLockedFormat(OdDbObject *pObj, OdDbTableContentPtr content);

  OdUInt32 mergedHeight(OdUInt32 row, OdUInt32 column) const;
  OdUInt32 mergedWidth(OdUInt32 row, OdUInt32 column) const;
  bool mergedFlag(OdUInt32 row, OdUInt32 column) const;

  OdDbTableContentPtr getContentPtr()
  {
    return m_content;
  }

  void insertColumns(OdUInt32 col, double width,OdUInt32 nCols);
  void deleteColumns(OdUInt32 col, OdUInt32 nCols);
  void insertRows(OdUInt32 row, double height, OdUInt32 nRows);
  void deleteRows(OdUInt32 row, OdUInt32 nRows);

  void splitTable(OdDbTablePtr table, OdBreakData& breakData);
  void calcBreakData(OdDbTablePtr table, bool bAdjustSize = false);
  double heightRows(OdDbTablePtr table, OdInt32 startRow, OdInt32 endRow);
  double widthCols(OdDbTablePtr table, OdInt32 startCol, OdInt32 endCol);
  void heightLabelRows(OdDbTablePtr table, double& topLabelHeight, double& bottomLabelHeight);
  void  getTopBottomLabels(OdDbTablePtr table, OdInt32& amRowsInTopLabel,  OdInt32& amRowsInBottomLabel);
  bool isLabelRow(OdDbTablePtr table, OdInt32 row);

  OdInt32 getLastNoMergedRow(OdDbTablePtr table, OdInt32 row);

  void subCloseNewTable(OdDbTablePtr table);

  void setSubSelection(OdInt32 rowMin, OdInt32 rowMax, OdInt32 colMin, OdInt32 colMax);
  bool hitTest(OdDbTablePtr table, const OdGePoint3d& wpt, const OdGeVector3d& wviewVec, double wxaper, double wyaper,
    OdInt32& resultRowIndex, OdInt32& resultColumnIndex, OdInt32& resultTable);
  bool isHitGridLine(OdInt32 rowIndex, OdInt32 columnIndex, double wxaper, double wyaper, OdInt32 resultTable);
  OdInt32 findHitContent(OdDbTablePtr table, OdInt32 rowIndex, OdInt32 columnIndex, 
    double CellWidth, double CellHeight, OdGePoint3d startPoint);

  void getMinMerged(OdInt32& row, OdInt32& col);
  void getMaxMerged(OdInt32& row, OdInt32& col);

  virtual bool applyClipBoundary(OdGiCommonDraw* pWd, OdGiGeometry& geom) const {return false; }

  OdInt32 getRangeIndicatorPoints(OdDbTablePtr pTable, OdCellRange selRange, double gap, OdGePoint3d* points);
  bool drawHighlighting(OdDbTablePtr table, OdGiWorldDraw* worldDraw);
  bool drawCellSelector(OdDbTablePtr table, OdGiWorldDraw* worldDraw, double indicatorSize, const OdGeMatrix3d& mat);
  bool drawLinkIndicator(OdDbTablePtr table, OdGiWorldDraw* worldDraw, double indicatorSize, const OdGeMatrix3d& mat);

  bool drawCellIndicator(OdDbTablePtr table, OdGiWorldDraw* worldDraw, const OdGiTextStyle& textStyle, const OdGeMatrix3d& mat);
  void drawCellIndicatorBreak(OdDbTablePtr pTable, OdGiWorldDraw* worldDraw, const OdGiTextStyle& textStyle, OdInt32 brkIndx, const OdGeMatrix3d& mat);
  void drawSelectIndicator(OdDbTablePtr pTable, OdGiWorldDraw* worldDraw, OdCellRange selRange, double topLabelheight, OdInt32 startRow, const OdGeMatrix3d& mat);
  void drawHorizontalTextLabels(OdDbTablePtr pTable, OdGiWorldDraw* worldDraw, const OdGiTextStyle& textStyle, const OdGeMatrix3d& mat);
  void drawVerticalTextLabels(OdDbTablePtr pTable, OdGiWorldDraw* worldDraw, const OdGiTextStyle& textStyle, OdInt32 brkIndx, const OdGeMatrix3d& mat);

  double indicatorRowWidth() { return m_dIndicatorWidth; }
  double indicatorColHeight() { return m_dIndicatorHeight; }
  double indicatorTextHeight() { return m_dIndicatorTextSize; }
  void   clearIndicatorSize() { m_dIndicatorWidth = 0.0; m_dIndicatorHeight = 0.0;  m_dIndicatorTextSize = 0.0; }
  void   updateBaseIndicatorSize();

private:
  OdDbObjectIteratorPtr m_entityIter;
  friend class OdDbTable;
  friend class OdDbTableTemplate;
};

#endif

