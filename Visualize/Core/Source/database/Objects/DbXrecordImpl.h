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

#ifndef _ODDBXRECORDIMPL_INCLUDED_
#define _ODDBXRECORDIMPL_INCLUDED_


#include "OdBinaryData.h"
#include "DbSystemInternals.h"
#include "DbXrecord.h"
#include "DbObjectImpl.h"

class OdTvDbXrecordImpl : public OdTvDbObjectImpl
{
  static OdTvDbXrecordImpl* getImpl(const OdTvDbXrecord *pObj)
  { return (OdTvDbXrecordImpl*)OdTvDbSystemInternals::getImpl(pObj);}

  OdUInt8      m_flags;
  bool         m_bFormatIsR15;
public:
	OdBinaryData m_binData;

  bool isXlateReferences() const { return GETBIT(m_flags, 0x80); }
  void setXlateReferences(bool bTranslate) { SETBIT(m_flags, 0x80, bTranslate); }

  OdDb::DuplicateRecordCloning mergeStyle() const
  { return OdDb::DuplicateRecordCloning(m_flags & 0x0F); }

  void setMergeStyle(OdDb::DuplicateRecordCloning style)
  { m_flags = OdUInt8(OdUInt8(style) | (m_flags & 0x80)); }

  OdResult appendRbChain(const OdTvResBuf* pRb, OdTvDbDatabase* pDb);
  
  virtual void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion ver);

public:
  OdTvDbXrecordImpl();

  void audit(OdTvDbAuditInfo* pAuditInfo);

  friend class OdTvDbXrecord;
};

#endif // _ODDBCIRCLEIMPL_INCLUDED_
