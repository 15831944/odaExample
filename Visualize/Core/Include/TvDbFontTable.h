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

// DbFontTable.h: interface for the OdTvDbFontTable class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _ODDBFONTTABLE_H_INCLUDED_
#define _ODDBFONTTABLE_H_INCLUDED_

#include "DbSymUtl.h"
#include "DbSystemInternals.h"


class OdGiTextStyle;
class OdTvDbTextStyleTableRecord;

class OdTvDbFontTableRecord : public OdTvDbSymbolTableRecord
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbFontTableRecord);

  OdTvDbFontTableRecord();

  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const;
};

typedef OdSmartPtr<OdTvDbFontTableRecord> OdDbFontTableRecordPtr;

class OdTvDbFontTable;
typedef OdSmartPtr<OdTvDbFontTable> OdDbFontTablePtr;

class OdTvDbFontTable : public OdTvDbSymbolTable
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbFontTable);

  OdTvDbFontTable();

  void createDefaultRecord();
/*
  static OdDbFontTablePtr open(OdDbDatabase* pDb)
  {
    return OdDbSystemInternals::getImpl(pDb)->fontTable(pDb);
  }
*/
  OdTvDbObjectId getFontId(const OdString& recName, bool bCreate = false);

};




#endif // _ODDBFONTTABLE_H_INCLUDED_
