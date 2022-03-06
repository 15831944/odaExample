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


#ifndef OD_DBDATATABLE_H
#define OD_DBDATATABLE_H

#include "TD_PackPush.h"
#include "RxObject.h"
#include "DbObject.h"

class OdTvDbDataCellImpl;
/** \details
    Corresponding C++ library: TD_Db 
    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbDataCell : public OdRxObject
{
public:
  enum CellType {
      kUnknown      = 0,
      kInteger      = 1,
      kDouble       = 2,
      kCharPtr      = 3,
      kPoint        = 4,
      kObjectId     = 5,
      kHardOwnerId  = 6,
      kSoftOwnerId  = 7,
      kHardPtrId    = 8,
      kSoftPtrId    = 9,
      kBool         = 10,
      kVector       = 11
  };
  ODDB_DECLARE_MEMBERS(OdTvDbDataCell);

  // Constructors
  
  OdTvDbDataCell();

  /*
  OdTvDbDataCell(const OdTvDbDataCell& rCell);

  OdTvDbDataCell(bool b);
  OdTvDbDataCell(int i);
  OdTvDbDataCell(double d);
  OdTvDbDataCell(const OdString& str);
  OdTvDbDataCell(const OdGePoint3d& point);
  OdTvDbDataCell(const OdGeVector3d& vec);
  OdTvDbDataCell(const OdTvDbObjectId& id);
  OdTvDbDataCell(const OdTvDbHardOwnershipId& id);
  OdTvDbDataCell(const OdTvDbSoftOwnershipId& id);
  OdTvDbDataCell(const OdTvDbHardPointerId&   id);
  OdTvDbDataCell(const OdTvDbSoftPointerId&   id);

  virtual ~OdTvDbDataCell();

  */
  
  virtual void init();

  virtual void set(const OdTvDbDataCell& cell);
  virtual void set(bool b);
  virtual void set(OdInt32 i);
  virtual void set(double d);
  virtual void set(const OdString& str);
  virtual void set(const OdGePoint3d& pt);
  virtual void set(const OdGeVector3d& vec);
  virtual void set(const OdTvDbObjectId& id);
  virtual void set(const OdTvDbHardOwnershipId& id);
  virtual void set(const OdTvDbSoftOwnershipId& id);
  virtual void set(const OdTvDbHardPointerId& id);
  virtual void set(const OdTvDbSoftPointerId& id);

  virtual void get(OdTvDbDataCell& cell);
  virtual void get(bool& b);
  virtual void get(OdInt32& i);
  virtual void get(double& d);
  virtual void get(OdString& str);
  virtual void get(OdGePoint3d& pt);
  virtual void get(OdGeVector3d& vec);
  virtual void get(OdTvDbObjectId& id);
  virtual void get(OdTvDbHardOwnershipId& id);
  virtual void get(OdTvDbSoftOwnershipId& id);
  virtual void get(OdTvDbHardPointerId& id);
  virtual void get(OdTvDbSoftPointerId& id);

/*
  virtual bool operator == (const OdTvDbDataCell &cell) const;
  virtual bool operator != (const OdTvDbDataCell &cell) const;
*/

  virtual OdTvDbDataCell::CellType type() const;
  OdTvDbDataCell(OdTvDbDataCellImpl* pValImpl);

protected:
  friend class OdTvDbSystemInternals;
  OdTvDbDataCellImpl* m_pImpl;
};

typedef OdSmartPtr<OdTvDbDataCell> OdTvDbDataCellPtr;

typedef OdArray<OdTvDbDataCellPtr> OdTvDbDataCellArray; 

class OdTvDbDataColumnImpl;

/** \details
    Corresponding C++ library: TD_Db 
    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbDataColumn : public OdRxObject
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbDataColumn);
  OdTvDbDataColumn();
  OdTvDbDataColumn(const OdTvDbDataColumn& rCol);
//  OdTvDbDataColumn(const OdTvDbDataCell::CellType type,
//       const OdString pColName = NULL);

//  virtual ~OdTvDbDataColumn();

  virtual OdUInt32 physicalLength() const;
  virtual OdUInt32 growLength() const;

  virtual void setPhysicalLength(OdUInt32 n);
  virtual void setGrowLength(OdUInt32 n);

//  virtual OdTvDbDataColumn& operator = (const OdTvDbDataColumn& col);

  virtual void setColumnType(OdTvDbDataCell::CellType type);
  virtual OdTvDbDataCell::CellType columnType() const;

  virtual void setColumnName(const OdString& pName);
  virtual OdString columnName() const;

  virtual OdTvDbDataCellPtr getCellAt(OdUInt32 index) const;
  virtual void setCellAt(OdUInt32 index, const OdTvDbDataCellPtr cell);

  virtual void appendCell(const OdTvDbDataCellPtr cell);

  virtual void insertCellAt(OdUInt32 index, const OdTvDbDataCellPtr& cell);
  virtual void   removeCellAt(OdUInt32 index);
  virtual OdInt32  getIndexAtCell(const OdTvDbDataCellPtr& cell) const;

  virtual OdUInt32 numCells() const;

  OdTvDbDataColumn(OdTvDbDataColumnImpl* m_pImpl);

protected:
  friend class OdTvDbSystemInternals;
  OdTvDbDataColumnImpl* m_pImpl;
};

typedef OdSmartPtr<OdTvDbDataColumn> OdTvDbDataColumnPtr;

class OdTvDbDataTableImpl;

/** \details
    Corresponding C++ library: TD_Db 
    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbDataTable : public OdTvDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbDataTable);
  
  OdTvDbDataTable(void);
  
//  virtual OdTvDbDataTable& operator = (const OdTvDbDataTable& table);

  virtual OdUInt32 numColumns() const;
  virtual OdUInt32 numRows() const;

  virtual void setNumRowsPhysicalSize(OdUInt32 n);
  virtual void setNumRowsGrowSize(OdUInt32 n);

  virtual OdUInt32 numRowsPhysicalSize() const;
  virtual OdUInt32 numRowsGrowSize() const;

  virtual void setNumColsPhysicalSize(OdUInt32 n);
  virtual void setNumColsGrowSize(OdUInt32 n);

  virtual OdUInt32 numColsPhysicalSize() const;
  virtual OdUInt32 numColsGrowSize() const;
  
  virtual OdString tableName() const;
  virtual void setTableName(const OdString& pName);

  virtual OdTvDbDataColumnPtr getColumnAt(OdUInt32 index) const;
  virtual OdString columnNameAt(OdUInt32 index) const;

  virtual  OdTvDbDataCell::CellType columnTypeAt(OdUInt32 index) const;
  virtual  OdInt32 columnIndexAtName (const OdString& name) const;

  virtual  void appendColumn(
      OdTvDbDataCell::CellType type, const OdString& colName);
  virtual  void insertColumnAt(OdUInt32 index, 
      OdTvDbDataCell::CellType type, const OdString& colName);
  virtual  void removeColumnAt(OdUInt32 index);

  virtual  void getRowAt(OdUInt32 index, 
      OdTvDbDataCellArray& outRow) const;
  virtual  void setRowAt(OdUInt32 index,
      const OdTvDbDataCellArray& row, bool bValidate = true);

  virtual  void appendRow(
      const OdTvDbDataCellArray& row, bool bValidate = true);

  virtual  void insertRowAt(OdUInt32 index,
      const OdTvDbDataCellArray& row, bool bValidate = true);

  virtual  void removeRowAt(OdUInt32 index);

  virtual  OdTvDbDataCellPtr getCellAt(OdUInt32 row, OdUInt32 col) const;
  virtual  void setCellAt(OdUInt32 row, OdUInt32 col,
      const OdTvDbDataCellPtr& cell);

  //********************************************************************
  // Overridden methods from OdTvDbObject
  //********************************************************************
  //

  virtual OdResult  dwgInFields(
    OdTvDbDwgFiler* pFiler);
  virtual void dwgOutFields(
    OdTvDbDwgFiler* pFiler) const;
  virtual OdResult  dxfInFields(
    OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(
    OdTvDbDxfFiler* pFiler) const;

  // virtual   audit(OdTvDbAuditInfo* pAuditInfo);
};

typedef OdSmartPtr<OdTvDbDataTable> OdTvDbDataTablePtr;

#include "TD_PackPop.h"

#endif
