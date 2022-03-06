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


class OdDbLinetypeTableRecordImpl
  : public OdDbSymbolTableRecordImpl
  , public OdGiLinetype
{
  static OdDbLinetypeTableRecordImpl* getImpl(const OdDbLinetypeTableRecord *pObj)
  { return (OdDbLinetypeTableRecordImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
  OdString        m_strDescText;
  OdUInt8         m_AlignFlag;

public:
  OdDbLinetypeTableRecordImpl();
  void audit (OdDbAuditInfo* pAuditInfo);

  // OdDbSymbolTableRecordImpl overridden
  void adjustXrefDependenceFromDXF(OdDbSymbolTable* pBlockTable);
  void setName(const OdString& name);
  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdDbObject* pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  static void resizeDashes(OdDbLinetypeTableRecord* pThis, int count)
  {
    pThis->assertWriteEnabled();
    OdDbLinetypeTableRecordImpl::getImpl(pThis)->m_dashes.resize(count);
  }
//  bool isReferenced_dxf() const;
private:
  friend class OdDbLinetypeTableRecord;
  friend class OdDwgR12FileLoader;
  friend class OdDwgR12FileWriter;
};

#endif //_ODDBLINETYPETABLERECORDIMPL_INCLUDED_
