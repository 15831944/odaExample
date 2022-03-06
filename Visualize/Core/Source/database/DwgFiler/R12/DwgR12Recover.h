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


#ifndef _DWGR12RECOVER_INCLUDED_
#define _DWGR12RECOVER_INCLUDED_

#include "DwgR12FileLoader.h"
#include "DbRecover.h"

class OdTvDwgR12Recover : public OdTvDwgR12FileLoader,
                        public OdTvDbRecover
{
public:
  OdTvDwgR12Recover() {}

  ODRX_DECLARE_MEMBERS(OdTvDwgR12Recover);

  // Overriden methods
  void setAuditInfo(OdTvDbAuditInfo* pAuditInfo) { OdTvDbRecover::setAuditInfo(pAuditInfo);
                                                 OdTvDwgR12FileLoader::setAuditInfo(pAuditInfo);}
  void startDbLoading(OdTvDbDatabase* pDbToLoad, OdDbHostAppProgressMeter* pProgressMeter);
  void endDbLoading();
  void endDbRecover();
  void loadHeader();
  void loadTable(OdTvDwgR12TableRecordType nType);
  void loadTableRecord(OdTvDwgR12TableRecordType nType, OdTvDbDwgFiler* pFiler, OdTvDbSymbolTable* pTable, OdUInt32 recIndex);
  bool loadEntity(OdTvDbEntityPtr& pEntity);
  void addDbEntity(OdTvDbEntityPtr& pEntity, OdDbHandle handle);
  void checkCrcInfo(OdString info);
  bool seekAddr(OdUInt32 addr, OdString info);
  void getRecordId(OdTvDwgR12TableRecordType nType, OdInt32 nIndex, OdTvDbObjectId& objId);
  bool findNextEntity();

  // Methods to get header info from invalid file
  void loadSecondHeader();
  void findHeaderInfo();
};

#endif //_DWGR12RECOVER_INCLUDED_
