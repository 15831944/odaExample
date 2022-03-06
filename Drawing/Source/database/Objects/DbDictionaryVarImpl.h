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

#ifndef _OD_DB_DICTIONARYVAR_IMPL_
#define _OD_DB_DICTIONARYVAR_IMPL_

#include "DbSystemInternals.h"
#include "DbDictionaryVar.h"
#include "DbObjectImpl.h"


class OdDbDictionaryVarImpl : public OdDbObjectImpl
{
  static OdDbDictionaryVarImpl* getImpl(const OdDbDictionaryVar *pObj)
  { return (OdDbDictionaryVarImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
  OdInt16  m_Schema;
  OdString m_strValue;

public:
  OdDbDictionaryVarImpl() : m_Schema(0) {}

private:
  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;

  friend class OdDbDictionaryVar;
};

#endif
