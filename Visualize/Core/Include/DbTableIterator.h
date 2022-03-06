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


#ifndef OD_DBTABLEITERATOR_H
#define OD_DBTABLEITERATOR_H

#include "RxObject.h"
#include "DbTableStyle.h"
#include "TD_PackPush.h"

/** 
  	<group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbCell
{
public:
  OdInt32  m_row;
  OdInt32  m_column;
  OdTvDbCell() { m_row = 0; m_column = 0; }
  OdTvDbCell(OdInt32 row, OdInt32 col) { m_row = row; m_column = col; }
};

class OdTvDbTableIteratorImpl;
class OdTvDbLinkedTableData;
class OdTvDbTable;

/** \details
  This class implements Iterator objects that traverse columns, rows and cells of tables.
  \remarks
  Instances of this class are returned by OdTvDbTable::getIterator() or OdTvDbLinkedTableData::getIterator() methods.

  <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbTableIterator : public OdStaticRxObject<OdRxObject>
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbTableIterator);

  OdTvDbTableIterator(const OdTvDbTable* pTable);

  OdTvDbTableIterator(const OdTvDbTable* pTable, const OdCellRange& range, OdDb::TableIteratorOption nOption);

  OdTvDbTableIterator(const OdTvDbLinkedTableData* pTable);

  OdTvDbTableIterator(const OdTvDbLinkedTableData* pTable, const OdCellRange& range, OdDb::TableIteratorOption nOption);

  OdTvDbTableIterator(const OdCellRange& range);

  OdTvDbTableIterator(const OdCellRange& range, OdDb::TableIteratorOption nOption);

  ~OdTvDbTableIterator();

  static OdSmartPtr<OdTvDbTableIterator> createObject(const OdTvDbTable* pTable);
  static OdSmartPtr<OdTvDbTableIterator> createObject(const OdTvDbTable* pTable, const OdCellRange& range, OdDb::TableIteratorOption nOption);
  static OdSmartPtr<OdTvDbTableIterator> createObject(const OdTvDbLinkedTableData* pTable);
  static OdSmartPtr<OdTvDbTableIterator> createObject(const OdTvDbLinkedTableData* pTable, const OdCellRange& range, OdDb::TableIteratorOption nOption);
  static OdSmartPtr<OdTvDbTableIterator> createObject(const OdCellRange& range);
  static OdSmartPtr<OdTvDbTableIterator> createObject(const OdCellRange& range, OdDb::TableIteratorOption nOption);

  /** \details
    Sets this Iterator object to the beginning of the iterated range.
  */
  void start(void);

  /** \details
    Increments this Iterator object so that it refers to the next object of the iterated range.
  */
  void step(void);

  /** \details
    Returns a value indicating whether this Iterator object has reached the end of the iterated range.
    \returns True if the end of the iterating range is reached, false otherwise.
  */
  bool done(void);

  /** \details
    Positions this Iterator object at the specified cell.
    \param cell [in] The cell to set the Iterator object at.
    \returns True if the specified cell is found within the iterating range, false otherwise.
    \remarks If the specified cell is not found within the iterating range, the Iterator object remains unchanged.
  */
  bool seek(const OdTvDbCell& cell);

  /** \details
    Returns the cell this Iterator object currently refers to.
    \returns The object of the OdTvDbCell class.
  */
  OdTvDbCell getCell(void) const;

  /** \details
    Returns the index of the row of the current iteration position.
    \returns The index of the row within the iteration range. Returns -1 if columns are currently iterated.
  */
  OdInt32 getRow (void) const;

  /** \details
    Returns the index of the column of the current iteration position.
    \returns The index of the column within the iteration range. Returns -1 if rows are currently iterated.
  */
  OdInt32 getColumn (void) const;

protected:
  OdTvDbTableIterator(void);

  OdTvDbTableIterator(OdTvDbTableIteratorImpl* pImpl);

  OdTvDbTableIteratorImpl  *m_pImpl;
};

typedef OdSmartPtr<OdTvDbTableIterator> OdTvDbTableIteratorPtr;

#include "TD_PackPop.h"

#endif
