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

#ifndef _ODDATADBTABLIMPL_INCLUDED_
#define _ODDATADBTABLIMPL_INCLUDED_

typedef OdArray<OdTvDbDataColumnPtr> OdTvDbDataColumnArray;

class OdTvDbDataCellImpl
{
public:  
  OdTvDbDataCellImpl() :
      m_type(OdTvDbDataCell::kUnknown)
      {
      }

      OdFieldVariant m_value;
      OdTvDbDataCell::CellType m_type;

      friend class OdTvDbDataCell;
};

class OdTvDbDataColumnImpl
{
public:
  OdTvDbDataColumnImpl() :
      m_type(OdTvDbDataCell::kUnknown)
      {}

      OdTvDbDataCellArray m_cells;
      OdTvDbDataCell::CellType m_type;
      OdString m_name;

      friend class OdTvDbDataColumn;
};

class OdTvDbDataTableImpl : public OdTvDbObjectImpl
{
  static OdTvDbDataTableImpl* getImpl(const OdTvDbDataTable *pObj)
  { return (OdTvDbDataTableImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  OdTvDbDataTableImpl() : m_rows(0)
    , m_columns(0)
    , m_version(2)
  {
  }

  OdTvDbDataColumnArray m_columnsArray;
  OdInt16  m_version;
  OdUInt32 m_rows;
  OdUInt32 m_columns;
  OdString m_name;

  friend class OdTvDbDataTable;
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
};
#endif
