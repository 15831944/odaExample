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
#ifndef __NW_OBJECT_READER_H__
#define __NW_OBJECT_READER_H__

#include "TD_PackPush.h"
#include "OdStreamBuf.h"
#include "SharedPtr.h"
#include "NwObjectType.h"

class OdNwObjectReaderManager;
typedef OdSharedPtr<OdNwObjectReaderManager> OdNwObjectReaderManagerPtr;
class OdNwObject;
typedef OdSmartPtr<OdNwObject> OdNwObjectPtr;

class OdNwObjectReader
{
public:
  OdNwObjectReader();
  explicit OdNwObjectReader(OdNwObjectPtr pElement);
  virtual ~OdNwObjectReader();

  virtual OdResult readFromStream(OdNwObjectReaderManager* stream) = 0;

  OdNwObjectPtr getElement();

  static OdSharedPtr<OdNwObjectReader> create(NwObjectType::Enum objType);

protected:
  OdNwObjectPtr m_pElement;
  bool          m_bNeedToInitElement;
};

/** \details
    This template class is a specialization of the OdSharedPtr class for OdNwObjectReader object pointers.
*/
typedef OdSharedPtr<OdNwObjectReader> OdNwObjectReaderPtr;

#include "TD_PackPop.h"

#endif // __NW_OBJECT_READER_H__
