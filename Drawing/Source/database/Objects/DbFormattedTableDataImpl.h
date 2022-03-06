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

#ifndef _ODDBFORMATTEDTABLEDATAIMPL_INCLUDED_
#define _ODDBFORMATTEDTABLEDATAIMPL_INCLUDED_

#include "DbLinkedTableDataImpl.h"
#include "DbCellStyleMapImpl.h"


class  OdDbFormattedTableDataImpl : public OdDbLinkedTableDataImpl
{
public:
  static OdDbFormattedTableDataImpl* getImpl(const OdDbFormattedTableData *pObj)
  { return (OdDbFormattedTableDataImpl*)OdDbSystemInternals::getImpl(pObj); }

public:
  OdDbFormattedTableDataImpl();

  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  OdResult dwgIn(OdDbDwgFiler* pFiler, bool bSaveParents = false);
  void     dwgOut(OdDbDwgFiler* pFiler, bool bLoadParents = false ) const;
  void setCellStyleAsOverride(OdInt32 nRow, OdInt32 nCol, OdCellStyle* cellStyle);

private:
  friend  class OdDbLinkedTableData;
};

#endif // _ODDBFORMATTEDTABLEDATAIMPL_INCLUDED_
