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

#ifndef _ODDBLINETYPETABLEIMPL_INCLUDED_
#define _ODDBLINETYPETABLEIMPL_INCLUDED_

#include "DbLinetypeTable.h"
#include "DbSymbolTableImpl.h"
#include "../DbSystemInternals.h"


class OdTvDbLinetypeTableImpl : public OdTvDbSymbolTableImpl
{
public:
  static OdTvDbLinetypeTableImpl* getImpl(const OdTvDbLinetypeTable *pObj)
  { return (OdTvDbLinetypeTableImpl*)OdTvDbSystemInternals::getImpl(pObj);}

  enum { kByBlock = 0x7FFE, kByLayer = 0x7FFF };

	OdTvDbHardOwnershipId	m_ByBlockLinetypeId;
	OdTvDbHardOwnershipId	m_ByLayerLinetypeId;

  virtual OdTvDbObjectId getByIndex(OdInt16 nIndex) const;
  virtual OdInt16 getIndexById(const OdTvDbObjectId& id) const;
  virtual OdString getNameByIndex(OdInt16 nIndex) const;
  virtual OdInt16 getIndexByName(const OdString& name) const;

  void audit (OdTvDbAuditInfo* pAuditInfo);

  friend class OdTvDbLinetypeTable;
private:
  const OdString getEntryDxfName() const { return OD_T("TV_DXF_LTYPE");}
  bool isValidRecordClass(OdRxClass* pClass) const;
};

#endif //_ODDBLINETYPETABLERECORDIMPL_INCLUDED_
