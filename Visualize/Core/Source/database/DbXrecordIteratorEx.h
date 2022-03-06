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




#ifndef ODDB_XRECORDEX_H
#define ODDB_XRECORDEX_H /* {Secret} */

#include "TD_PackPush.h"

#include "DbXrecord.h"
#include "XDataIteratorImpl.h"

class OdTvDbXrecordIteratorAccess : public OdTvDbXrecordIterator
{
  OdTvDbXrecordIteratorAccess() : OdTvDbXrecordIterator(0) {}
public:
  static OdTvXDataIteratorImpl* getImpl(OdTvDbXrecordIterator* pXRecIter);
  static const OdTvXDataIteratorImpl* getImpl(const OdTvDbXrecordIterator* pXRecIter);
};

class OdTvDbXrecordIteratorEx : public OdTvXDataIterator
{
public:
  OdTvDbXrecordIteratorEx(OdTvDbXrecordIterator* pXRecIter)
    : OdTvXDataIterator(OdTvDbXrecordIteratorAccess::getImpl(pXRecIter))
  {
  }
  void addRef() { }
  void release() { }
  ~OdTvDbXrecordIteratorEx()
  {
    m_pImpl = 0;
  }
};

#include "TD_PackPop.h"

#endif //ODDB_XRECORDEX_H

