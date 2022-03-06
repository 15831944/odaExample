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

#ifndef _ODDBDBVXTABLETABLEIMPL_INCLUDED
#define _ODDBDBVXTABLETABLEIMPL_INCLUDED

#include "DbSystemInternals.h"
#include "DbVXTable.h"
#include "DbSymbolTableImpl.h"

class OdTvDbVXTableImpl : public OdTvDbSymbolTableImpl
{
public:
  static OdTvDbVXTableImpl* getImpl(const OdTvDbVXTable *pObj)
  { return (OdTvDbVXTableImpl*)OdTvDbSystemInternals::getImpl(pObj);}

  OdTvDbVXTableImpl();

  // Virtual audit() not used here
  // as OdTvDbVXTable audit must follow PaperSpace viewports audit
  // (called from OdTvDbBlockTableRecord::audit())
  bool auditVX (OdTvDbAuditInfo* pAuditInfo);

  // Overriden
  bool needNameUnicity(OdTvDbSymbolTableRecord*) { return false; }

  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);  
};


#endif