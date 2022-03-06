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

typedef OdArray<OdDbDataColumnPtr> OdDbDataColumnArray;

class OdDbDataCellImpl
{
public:  
  OdDbDataCellImpl() :
      m_type(OdDbDataCell::kUnknown)
      {
      }

      OdFieldVariant m_value;
      OdDbDataCell::CellType m_type;

      friend class OdDbDataCell;
};

class OdDbDataColumnImpl
{
public:
  OdDbDataColumnImpl() :
      m_type(OdDbDataCell::kUnknown)
      {}

      OdDbDataCellArray m_cells;
      OdDbDataCell::CellType m_type;
      OdString m_name;

      friend class OdDbDataColumn;
};

class OdDbDataTableImpl : public OdDbObjectImpl
{
  static OdDbDataTableImpl* getImpl(const OdDbDataTable *pObj)
  { return (OdDbDataTableImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
  OdDbDataTableImpl() : m_rows(0)
    , m_columns(0)
    , m_version(2)
  {
  }

  OdDbDataColumnArray m_columnsArray;
  OdInt16  m_version;
  OdUInt32 m_rows;
  OdUInt32 m_columns;
  OdString m_name;

  friend class OdDbDataTable;
  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
};
#endif
