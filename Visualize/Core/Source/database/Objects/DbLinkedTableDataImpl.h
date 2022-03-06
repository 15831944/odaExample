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

#ifndef _ODDBLINKEDTABLEDATAIMPL_INCLUDED_
#define _ODDBLINKEDTABLEDATAIMPL_INCLUDED_

#include "DbLinkedDataImpl.h"
#include "DbCellStyleMapImpl.h"
#include "DbCustomData.h"
#include "DbTableGeometryImpl.h"

class OdColumnData
{
public:
  OdString m_name;
  OdInt32 m_intCustomData;

  OdCustomDataArray m_customData; 

  OdCellStyle m_format;
  OdInt32 m_cellStyleId;
  double m_width;

  OdColumnData() : m_intCustomData(0)
    , m_cellStyleId(0)
    , m_width(1.0)
  {
  }
  void dxfIn(OdTvDbDxfFiler* pFiler);
  void dxfOut(OdTvDbDxfFiler* pFiler) const;

  void dxfInLINKEDTABLEDATACOLUMN(OdTvDbDxfFiler* pFiler);
  void dxfInFORMATTEDTABLEDATACOLUMN(OdTvDbDxfFiler* pFiler);
  void dxfInTABLECOLUMN(OdTvDbDxfFiler* pFiler);

  void dxfOutLINKEDTABLEDATACOLUMN(OdTvDbDxfFiler* pFiler) const;
  void dxfOutFORMATTEDTABLEDATACOLUMN(OdTvDbDxfFiler* pFiler) const;
  void dxfOutTABLECOLUMN(OdTvDbDxfFiler* pFiler) const;

};

class OdAttrContent
{
public:
  OdString m_attrValue;
  OdTvDbObjectId m_id;
  OdInt32 m_index;
};

typedef OdArray<OdAttrContent>  OdAttrContents;

class OdCellContent
{
public: 
  OdDb::CellContentType m_type;
  OdValue m_value;
  OdTvDbObjectId m_id;
  OdInt32 m_flagFormat;
  OdCellStyle m_format; // OdContentFormat
  // Compromise: only the OdContentFormat subset of OdCellStyle properties is used,
  // but for implementation convenience in  OdTvDbLinkedTableDataImpl::getCellStyle()
  // OdCellStyle is used instead of OdContentFormat.
  OdAttrContents m_attributes;

  OdCellContent() : m_type(OdDb::kCellContentTypeValue)
    , m_flagFormat(1)
  {
  }

  void dwgInCONTENTFORMAT(OdTvDbDwgFiler* pFiler);
  void dwgOutCONTENTFORMAT(OdTvDbDwgFiler* pFiler) const;

  void dxfIn(OdTvDbDxfFiler* pFiler);
  void dxfInCONTENT(OdTvDbDxfFiler* pFiler);
  void dxfInFORMATTEDCELLCONTENT(OdTvDbDxfFiler* pFiler);

  void dxfOut(OdTvDbDxfFiler* pFiler) const;
  void dxfOutCONTENT(OdTvDbDxfFiler* pFiler) const;
  void dxfOutFORMATTEDCELLCONTENT(OdTvDbDxfFiler* pFiler) const;
};

typedef OdArray<OdCellContent>  OdCellContents;

class OdLinkedData
{
public:
  OdTvDbObjectId m_dataLinkId; // This points to OdTvDbDataLink.
  OdInt32 m_rows;
  OdInt32 m_cols;
  OdInt32 m_gc96; // Unknown: DXF group code 96
  
  OdLinkedData() : m_rows(0)
    , m_cols(0)
    , m_gc96(0)
  {}

};

class OdTableCell
{
public:
  OdTableCell() : m_gc91_1(0)
      ,m_gc91_2(0)
      ,m_geomDataFlag(0)
      ,m_gc40(0)
      ,m_gc41(0)
  {}

  OdInt32  m_gc91_1;
  OdInt32  m_gc91_2;
  OdInt32  m_geomDataFlag;
  double   m_gc40;
  double   m_gc41;
  OdTvDbObjectId m_id;
};

class OdCellData
{
public:
  OdInt32 m_state; // OdDb::CellState 
  OdString m_toolTip;

  OdInt32 m_intCustomData;
  OdCustomDataArray m_customData;
  
  OdInt32 m_linkedFlag;
  OdLinkedData m_linkedData;

  OdInt32 m_amFields;  // Number of fields in m_content (amount fields).
  OdCellContents m_content;
  OdCellStyle m_cellFormat;
  OdTableCell m_tableCell;
  OdInt32 m_cellStyleID;

  OdCellGeometryDataArray m_geomData;
  OdInt16 m_rtState;

  OdCellData() : m_amFields(0) 
    , m_state(OdDb::kCellStateNone)
    , m_intCustomData(0)
    , m_linkedFlag(0)
    , m_cellStyleID(0)
    , m_rtState(0)
  {
  }

  void dwgIn(OdTvDbDwgFiler* pFiler);
  void dwgOut(OdTvDbDwgFiler* pFiler) const;

  void dxfIn(OdTvDbDxfFiler* pFiler);
  void dxfInLINKEDTABLEDATACELL(OdTvDbDxfFiler* pFiler);
  void dxfInFORMATTEDTABLEDATACELL(OdTvDbDxfFiler* pFiler);
  void dxfInTABLECELL(OdTvDbDxfFiler* pFiler);

  void dxfOut(OdTvDbDxfFiler* pFiler) const;
  void dxfOutLINKEDTABLEDATACELL(OdTvDbDxfFiler* pFiler) const;
  void dxfOutFORMATTEDTABLEDATACELL(OdTvDbDxfFiler* pFiler) const;
  void dxfOutTABLECELL(OdTvDbDxfFiler* pFiler) const;
};

typedef OdArray<OdCellData> OdCells;

class OdRowData
{
public:
  OdCells m_cells;
  OdCellStyle m_cellStyle;

  OdInt32 m_intCustomData;
  OdCustomDataArray m_customData;

  OdInt32 m_cellStyleId;
  double  m_height;

  OdRowData() : m_intCustomData(0)
    ,m_cellStyleId(0)
    ,m_height(0.0)
    {
    }

  void dxfIn(OdTvDbDxfFiler* pFiler);
  void dxfInTABLEFORMAT(OdTvDbDxfFiler* pFiler);
  void dxfInTABLEROW(OdTvDbDxfFiler* pFiler);

  void dxfOut(OdTvDbDxfFiler* pFiler) const;
  void dxfOutTABLEFORMAT(OdTvDbDxfFiler* pFiler) const;
  void dxfOutTABLEROW(OdTvDbDxfFiler* pFiler) const;
};

typedef OdArray<OdRowData>  OdTableData;
typedef OdArray<OdColumnData>  OdTableColumnsData;

class OdTvDbLinkedTableDataImpl : public OdTvDbLinkedDataImpl
{
public:
  static OdTvDbLinkedTableDataImpl* getImpl(const OdTvDbLinkedTableData *pObj)
  { return (OdTvDbLinkedTableDataImpl*)OdTvDbSystemInternals::getImpl(pObj); }

public:
  OdTvDbLinkedTableDataImpl();

  OdTvDbObjectId m_tableStyleId;

  // OdUInt32          m_columns;
  // OdUInt32          m_rows;

  OdTableData           m_table;
  OdTableColumnsData    m_columnsData;

  // The fields contain a collection of all fields (OdTvDbField) that are part of
  // all cell contents (OdCellContent::m_id in case it represents a field).
  OdArray<OdTvDbObjectId> m_fields;

  OdCellStyle m_tableStyleData;
  OdCellRangeArray m_mergeData;
  OdArray<OdTvDbObjectId> m_FieldsExpr;

private:
  friend  class OdTvDbLinkedData;
  
public:
  bool getCell(OdInt32 nRow, OdInt32 nCol, OdCellData& cell);
  OdCellData* getCell(OdInt32 nRow, OdInt32 nCol);
  OdCellData* getMainLinkedCell(OdInt32& nRow, OdInt32& nCol);

  bool getRow(OdInt32 row, OdRowData& rowData);
  OdRowData* getRow(OdInt32 row);

  OdColumnData* getColumnData(OdInt32 nCol);
  bool getColumnData(OdInt32 nCol, OdColumnData& colData);
  OdCellStyle* getStyleData(OdInt32 nRow, OdInt32 nCol, OdInt32 nContent = 0);

  OdInt32 columns() const;
  OdInt32 rows() const;
  void setSize(OdInt32 nRows, OdInt32 nCols);

  OdTableGridLine* getGridLines(OdInt32 nRow, OdInt32 nCol);
  OdTableGridLine* getGridLine(OdInt32 nRow, OdInt32 nCol, OdDb::GridLineType grType);
  OdTableGridLine* getAdjoiningLine(OdInt32& nRow, OdInt32& nCol, OdDb::GridLineType nGridLineType);
  OdDb::GridLineType insideGridLineType(OdInt32 nRow, OdInt32 nCol, OdDb::GridLineType nGridLineType);

  const OdString cellStyle(OdInt32 nRow, OdInt32 nCol);
  void setCellStyle(OdInt32 nRow, OdInt32 nCol, const OdString& sCellStyle);
  void collectFields();

  OdTvDbTableStylePtr getTableStylePtr() const
  {
    return m_tableStyleId.safeOpenObject();
  }
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  OdResult dwgIn(OdTvDbDwgFiler* pFiler, bool bLoadParents = false );
  void dwgOut(OdTvDbDwgFiler* pFiler, bool bSaveParents = false) const;

  bool isMerged(OdInt32 nRow, OdInt32 nCol);
  OdCellRange getMergeRange(OdInt32 nRow, OdInt32 nCol) const;
  void merge(const OdCellRange& range);
  void unmerge(const OdCellRange& range);

  void copyFrom(const OdTvDbLinkedTableData* pSrc, OdDb::TableCopyOption nOption);
  void copyFrom(const OdTvDbLinkedTableData* pSrc, OdDb::TableCopyOption nOption, 
    const OdCellRange& srcRange, const OdCellRange& targetRange,
    OdCellRange* pNewTargetRange = NULL, OdTvDbLinkedTableData* pTag = NULL);

  bool isFormatEditable(OdInt32 nRow, OdInt32 nCol, bool bCheckLinked = false);
  bool isLinkedCell(OdInt32 nRow, OdInt32 nCol);
  bool hasFormula(OdCellData* cell, OdUInt32 nContent) const;
  void correctFormulas(OdInt32 index, OdInt32 amount, bool bRow);
  void setFormulaEvaluationOption();
  void resize(const OdCellRange& srcRange, const OdCellRange& targetRange, OdTvDbLinkedTableData* pTag);

  bool canDelete(OdInt32 nRow, OdInt32 nCol);
  bool canDeleteRow(OdInt32 nRow, OdInt32 columns);
  bool canDeleteCol(OdInt32 nCol, OdInt32 rows);
  bool canInsertRow(OdInt32 nRow, OdInt32 columns);
  bool canInsertCol(OdInt32 nCol, OdInt32 rows);
  bool isContentEmpty(OdInt32 nRow, OdInt32 nCol);
  bool isRowEmpty(OdInt32 nRow, OdInt32 startCol = 0, OdInt32 endCol = -1);
  bool isColumnEmpty(OdInt32 nCol, OdInt32 startRow = 0, OdInt32 endRow = -1);


  OdInt32 numColumns() const;
  OdInt32 numRows() const;
};

#endif // _ODDBLINKEDTABLEDATAIMPL_INCLUDED_

