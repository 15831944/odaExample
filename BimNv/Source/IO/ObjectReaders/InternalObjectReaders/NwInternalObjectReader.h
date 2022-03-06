  /////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2018, Open Design Alliance (the "Alliance"). 
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
//   This application incorporates Teigha(R) software pursuant to a license 
//   agreement with Open Design Alliance.
//   Teigha(R) Copyright (C) 2002-2019 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////
#ifndef __NW_INTERNAL_OBJECT_REDAER_H__
#define __NW_INTERNAL_OBJECT_REDAER_H__

#include "TD_PackPush.h"

class OdNwObjectReaderManager;

template <class... Args> class OdNwInternalObjectReader;

template <typename T>
class OdNwInternalObjectReader<T>
{
public:
  using InternalObjectPtr = T;

public:
  OdNwInternalObjectReader() = default;
  explicit OdNwInternalObjectReader(InternalObjectPtr pElement) :m_pElement(pElement) {}
  virtual ~OdNwInternalObjectReader() = default;

  virtual OdResult readFromStream(OdNwObjectReaderManager* stream) = 0;

  InternalObjectPtr getElement() { return m_pElement; }

protected:
  InternalObjectPtr m_pElement;
};

#include "TD_PackPop.h"

#endif // __NW_INTERNAL_OBJECT_REDAER_H__
