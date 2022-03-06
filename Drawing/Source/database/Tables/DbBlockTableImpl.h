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

#ifndef _ODDBBLOCKTABLEIMPL_INCLUDED_
#define _ODDBBLOCKTABLEIMPL_INCLUDED_

#include "../DbSystemInternals.h"
#include "DbBlockTable.h"
#include "DbSymbolTableImpl.h"


class OdDbBlockTableImpl : public OdDbSymbolTableImpl
{
  static OdDbBlockTableImpl* getImpl(const OdDbBlockTable *pObj)
  { return (OdDbBlockTableImpl*)OdDbSystemInternals::getImpl(pObj);}

//public:
  OdDbHardOwnershipId	m_ModelSpaceId;
  OdDbHardOwnershipId	m_PaperSpaceId;

private:
  const OdString getEntryDxfName() const { return OD_T("BLOCK_RECORD"); }
  void audit (OdDbAuditInfo* pAuditInfo);
  bool isValidRecordClass(OdRxClass* pClass) const;

  friend class OdDbBlockTable;
  friend class OdDbBlockTableIteratorImpl;
  friend class OdDbBlockTableRecordImpl;
  friend class OdDbBlockReferenceImpl;
  friend class OdDwgRecover;
  friend class OdDbDatabase;
  friend class OdDbDxfLoader;
  friend class OdDwgR12FileLoader;
  friend struct OdDbBlockTableTfPE;
  friend OdResult xrefBind(OdDbBlockTableRecord* pBTR, bool bInsertBind, OdList<OdDbObjectId>& nestedXrefIds);

public:
  TOOLKIT_EXPORT void updateAnonymousBlocks(bool purgeBlocks);
  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion ver);
  static void swapPaperSpaceId(OdDbBlockTable* pBlockTable, const OdDbObjectId& newPsId);
};

#endif //_ODDBBLOCKTABLEIMPL_INCLUDED_
