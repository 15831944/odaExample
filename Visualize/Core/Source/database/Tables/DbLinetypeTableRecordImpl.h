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

#ifndef _ODDBLINETYPETABLERECORDIMPL_INCLUDED_
#define _ODDBLINETYPETABLERECORDIMPL_INCLUDED_

#include "DbLinetypeTableRecord.h"
#include "DbSymbolTableRecordImpl.h"
#include "Gi/GiLinetype.h"


class OdTvDbLinetypeTableRecordImpl
  : public OdTvDbSymbolTableRecordImpl
  , public OdGiLinetype
{
  static OdTvDbLinetypeTableRecordImpl* getImpl(const OdTvDbLinetypeTableRecord *pObj)
  { return (OdTvDbLinetypeTableRecordImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  OdString        m_strDescText;
  OdUInt8         m_AlignFlag;

public:
  OdTvDbLinetypeTableRecordImpl();
  void audit (OdTvDbAuditInfo* pAuditInfo);

  // OdTvDbSymbolTableRecordImpl overridden
  void adjustXrefDependenceFromDXF(OdTvDbSymbolTable* pBlockTable);
  void setName(const OdString& name);
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdTvDbObject* pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  static void resizeDashes(OdTvDbLinetypeTableRecord* pThis, int count)
  {
    pThis->assertWriteEnabled();
    OdTvDbLinetypeTableRecordImpl::getImpl(pThis)->m_dashes.resize(count);
  }
//  bool isReferenced_dxf() const;
private:
  friend class OdTvDbLinetypeTableRecord;
  friend class OdTvDwgR12FileLoader;
  friend class OdTvDwgR12FileWriter;
};

#endif //_ODDBLINETYPETABLERECORDIMPL_INCLUDED_
