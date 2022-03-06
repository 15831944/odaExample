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

#ifndef _ODDBBLOCKBEGIIMPL_INCLUDED_
#define _ODDBBLOCKBEGIIMPL_INCLUDED_

#include "DbEntityImpl.h"
#include "DbSystemInternals.h"
#include "DbBlockBegin.h"

class OdTvDbBlockBeginImpl : public OdTvDbEntityImpl
{
  static OdTvDbBlockBeginImpl* getImpl(const OdTvDbBlockBegin *pObj)
  { return (OdTvDbBlockBeginImpl*)OdTvDbSystemInternals::getImpl(pObj);}

private:
  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

public:
  OdTvDbBlockBeginImpl (void) {}

  void setCastShadows(bool) {}
  bool castShadows() const { return false; }

  void setReceiveShadows(bool) {}
  bool receiveShadows() const { return false; }
  void audit (OdTvDbAuditInfo* pAuditInfo);

  friend class OdTvDbBlockBegin;

// ODA_MT_DBIO_BEGIN
private:
  OdString m_NameWithIndex;
  friend class OdTvDbBlockTableRecordImpl;
// ODA_MT_DBIO_END
};

#endif // _ODDBBLOCKBEGIIMPL_INCLUDED_
