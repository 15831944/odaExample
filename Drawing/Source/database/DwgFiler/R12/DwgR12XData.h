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


#ifndef _ODDWGR12XDATAITERATORIMPL_
#define _ODDWGR12XDATAITERATORIMPL_

#include "XDataIteratorImpl.h"

class DwgR12IOContext;

class OdDwgR12XDataIteratorImpl : public OdXDataIteratorImpl
{
public:
  virtual int dataSize() const;
  virtual OdString getString() const;
  virtual OdDbHandle getHandle() const;
  virtual void setHandle(int gCode, const OdDbHandle& handle);
  virtual void setString(int gCode, const OdString& str);

  // In dwgR12 some string value present as index
  // To convert such index to string it is need loading context
  DwgR12IOContext* m_pContext; 
};

#define StaticR12XDataIterator OdStaticRxObject<OdObjectWithImpl<OdXDataIterator, OdDwgR12XDataIteratorImpl> >

#endif  // _ODDWGR12XDATAITERATORIMPL_
