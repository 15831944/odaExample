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

#ifndef _ODDBTABLESTYLEMPL_INCLUDED_
#define _ODDBTABLESTYLEMPL_INCLUDED_

#include "DbTableStyle.h"

#include "DbSystemInternals.h"
#include "DbColor.h"
#include "DbObjectImpl.h"
#include "OdValue.h"
#include "RxThreadPoolService.h"
#include "DbEntities.h"

#define ROWS_DEFINED_IN_STYLE     3
#define GRIDLINES_DEFINED_IN_ROW  6
#define GRID_MARGINS              6

enum TypeStyle
{
  kCellStyle = 1,
  kRowStyle = 2,
  kColumnStyle = 3,
  kFormattedStyle = 4,
  kTableStyle = 5
};

//  kCellMarginTop         = 0x1, // Vector (0,-1,0)  VertCellMargin
//  kCellMarginLeft        = 0x2, // Vector (1,0,0)   HorzCellMargin
//  kCellMarginBottom      = 0x4, // Vector (0,1,0)
//  kCellMarginRight       = 0x8, // Vector (-1,0,0)
//  kCellMarginHorzSpacing = 0x10,
//  kCellMarginVertSpacing = 0x20 

class OdTableGridLine
{
public:  
  OdTableGridLine()
      : m_lineWeight(OdDb::kLnWtByBlock)
      , m_bVisibility(OdDb::kVisible)
      , m_color(OdCmEntityColor::kByBlock)
      , m_type(OdDb::kHorzTop)
      , m_lineStyle(OdDb::kGridLineStyleSingle)
      , m_lineSpacing(0.045)
      , m_propFlag(0)
      , m_bOverrideFlag(false)
  {}
  ~OdTableGridLine(){};

  OdDb::LineWeight      m_lineWeight;
  OdDb::Visibility      m_bVisibility;
  OdTvCmColor             m_color;

  // new 2008 property
  OdDb::GridLineType    m_type;
  OdDb::GridLineStyle   m_lineStyle;       // single/double line
  OdTvDbObjectId          m_linetypeId;
  double                m_lineSpacing;
  OdInt32               m_propFlag;

  bool                  m_bOverrideFlag;
  bool dwgIn(OdTvDbDwgFiler* pFiler);
  void dwgOut(OdTvDbDwgFiler* pFiler) const;
  bool isEqualTo(const OdTableGridLine& gridLine) const;

  bool operator == (const OdTableGridLine& gridLine) const
  {
    return isEqualTo(gridLine);
  }
  bool operator != (const OdTableGridLine& gridLine) const
  {
    return !isEqualTo(gridLine);
  }
};

typedef OdArray<OdTableGridLine>  OdTableGridLines;

class OdContentFormat
{

public:
  OdContentFormat();
  // Content format
  OdInt32               m_overrides;      // 90    override flag
                                             
  OdInt32               m_mixFlags;       // 91    0x100 auto scale FLAG 
                                          //       0x10000 flow direction UP

  OdTvDbObjectId          m_textStyleId;    // 340   0x40
  double                m_textHeight;     // 144   0x80
  OdDb::CellAlignment   m_textAlignment;  //  94   used in cell style // 0x10

  OdTvCmColor             m_textColor;      //  62   0x02 text col // 0x20 block col

  OdValue::DataType     m_dataType;       //  92
  OdValue::UnitType     m_unitType;       //  93
  OdString              m_strFormat;      // 300

  double                m_rotation;       //  40   0x04
  double                m_blockScale;     // 140   0X08

  // Not used when part of OdCellContent
  // In this case OdCellContent::m_flagData is used.
  OdUInt32              m_flagData; // flag table format data. 0 - empty 

  void dxfInCONTENTFORMAT(OdTvDbDxfFiler* pFiler);
  void dxfOutCONTENTFORMAT(OdTvDbDxfFiler* pFiler) const;
};

class OdCellStyle : public OdContentFormat
{
public:
  
  OdCellStyle();
  ~OdCellStyle(){};


  OdTvCmColor             m_fillColor;            // 0x200
  bool                  m_bBackGrColorEnable;  

  OdTableGridLine       m_GridLines[GRIDLINES_DEFINED_IN_ROW];

  // ACAD2008
  OdInt32               m_id;      
  OdUInt32              m_class;      

  OdUInt32              m_mergedFlag; // 92 0x8000 - unmerged title or merged data/header

  OdString              m_name;
  double                m_gridMargins[GRID_MARGINS];
  OdUInt32              m_marginFlag;
  OdUInt32              m_typeStyle;      // GC 90
  OdUInt32              m_cellOverrides;  // GC 91 
  OdDb::CellContentLayout     m_contentLayout; // GC93 Flow - 1/Stacked Hor-2/Stacked Ver - 4

  bool dwgIn(OdTvDbDwgFiler* pFiler);
  void dwgOut(OdTvDbDwgFiler* pFiler) const;

  void dxfIn(OdTvDbDxfFiler* pFiler);
  void dxfInTABLEFORMAT(OdTvDbDxfFiler* pFiler);
  void dxfInCELLMARGIN(OdTvDbDxfFiler* pFiler);
  void dxfInGRIDFORMAT(OdTvDbDxfFiler* pFiler, OdTableGridLine& grLine);

  void dxfOut(OdTvDbDxfFiler* pFiler) const;
  void dxfOutTABLEFORMAT(OdTvDbDxfFiler* pFiler) const;
  void dxfOutCELLMARGIN(OdTvDbDxfFiler* pFiler) const;
  void dxfOutGRIDFORMAT(OdTvDbDxfFiler* pFiler, const OdTableGridLine& grLine) const;

  OdTableGridLine* getGridLine(OdDb::GridLineType grType);
  OdInt32 getGridIndexByType(OdDb::GridLineType grType);

  bool isEqualTo(const OdCellStyle& cellStyle) const;
  bool operator == (const OdCellStyle& cellStyle) const
  {
    return isEqualTo(cellStyle);
  }
  bool operator != (const OdCellStyle& cellStyle) const
  {
    return !isEqualTo(cellStyle);
  }
};

class OdTvDbTableStyleImpl : public OdTvDbObjectImpl
{
  static OdTvDbTableStyleImpl* getImpl(const OdTvDbTableStyle *pObj)
  { return (OdTvDbTableStyleImpl*)OdTvDbSystemInternals::getImpl(pObj);}
public:
  OdTvDbTableStyleImpl();

  /*
  * The first 3 cell styles in the cell style map are
  * the date, title and header cell styles.
  * The subsequent cell styles are user defined.
  */
  enum StyleRowIndex
  {
    kDataInd = 0,
    kTitleInd = 1,
    kHeaderInd = 2
  };

  OdString              m_description;
  OdDb::FlowDirection   m_flowDirection;
  OdUInt16              m_bitFlag;
  double                m_dHorizontalCellMargin;
  double                m_dVerticalCellMargin;
  bool                  m_bTitleSuppressed;
  bool                  m_bHeaderSuppressed;
  // OdTableRow            m_tableRows[ROWS_DEFINED_IN_STYLE];
  OdArray<OdCellStyle>  m_tableRows; //[ROWS_DEFINED_IN_STYLE];

//#pragma MARKMESSAGE(TODO: AC24 issue. Unknown data.)
  OdCellStyle           m_tableCellStyle; // Contains the default cell style for the table.
  OdUInt8               m_Ac24Unk1;
  OdUInt32              m_Ac24Unk2;
  OdUInt32              m_Ac24Unk3; // ? m_bitFlag
  OdTvDbObjectId          m_tableTemplateID;

  OdInt32 getNewCellStyleID();
  void addCellStyle(OdString cellStyle);
  OdInt32 rowIndex(OdDb::RowType rowType);
  static OdInt32 gridLineIndex(OdDb::GridLineType gridLineType);
  static OdInt32 cellMarginIndex(OdDb::CellMargin nMargin);
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void correctDefaultValue(OdDb::SaveType format, OdDb::DwgVersion version);
  void setTableStyleDefault(OdTvDbDatabase* pDb);

  OdCellStyle* getCellStyle(const OdString& cellStyle);
  OdTableGridLine* getGridLine(OdDb::GridLineType nGridLineType, const OdString& cellStyle);

  void audit(OdTvDbAuditInfo* pAuditInfo);
private:
  friend  class OdTvDbTableStyle;

  OdInt32 findStyle(const OdString& cellStyle);
  OdInt32 findStyleById(OdInt32 cellStyle);
};

inline void odtvdbVerifyDefTableStyle(OdTvDbDatabase* pDb) {
  if (!pDb->usingCoreOnly())
    OdTvDbEntitiesModulePtr(odrxSafeLoadApp(OdDbEntitiesAppName))->VerifyDefTableStyle(pDb);
}

#endif // _ODDBTABLESTYLEMPL_INCLUDED_
