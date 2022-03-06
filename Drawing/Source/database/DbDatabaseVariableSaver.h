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

#ifndef _ODDBVARIABLESAVER_INCLUDED_
#define _ODDBVARIABLESAVER_INCLUDED_

#include "DbDatabaseImpl.h"

// This template silently changes system variable value in constructor, 
// and restores it in destructor. Use with caution.
//
template <typename ValueType, 
void (OdDbDatabaseImpl::*setFun)(ValueType), 
ValueType (OdDbDatabaseImpl::*getFun)() const > 
struct OdDbDatabaseVariableSaver
{
  OdDbDatabaseImpl* _pDb;
  ValueType _oldValue;
  OdDbDatabaseVariableSaver(OdDbDatabaseImpl*pDb, ValueType newValue)
  {
    _pDb = pDb;
    _oldValue = (pDb->*getFun)();
    (pDb->*setFun)(newValue);
  }
  ~OdDbDatabaseVariableSaver()
  {
    (_pDb->*setFun)(_oldValue);
  }
};

#endif
