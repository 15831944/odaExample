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

#ifndef _ODDBREGAPPTABLERECORDIMPL_INCLUDED_
#define _ODDBREGAPPTABLERECORDIMPL_INCLUDED_

#include "DbSystemInternals.h"
#include "DbRegAppTableRecord.h"
#include "DbSymbolTableRecordImpl.h"

class OdDbRegAppTableRecordImpl : public OdDbSymbolTableRecordImpl
{
  static OdDbRegAppTableRecordImpl* getImpl(const OdDbRegAppTableRecord *pObj)
  { return (OdDbRegAppTableRecordImpl*)OdDbSystemInternals::getImpl(pObj);}

	enum {XDATANOTSAVED = 1};

public:
	OdUInt8 m_UnkUInt8;

public:
  OdDbRegAppTableRecordImpl() { m_UnkUInt8 = 0; }

  // OdDbSymbolTableRecordImpl overriden
  //
  virtual void setXrefBlockId(
    const OdDbObjectId&,
    OdDbSymbolTableRecord*) {}
  virtual bool mangleName(
    OdDb::DeepCloneType,
    OdDb::DuplicateRecordCloning,
    const OdString&,
    unsigned = 0,
    const OdString& = OdString::kEmpty) { return false; }

protected:
	void setIsXdataNotWritten(bool value) { SETBIT(m_Flags, XDATANOTSAVED, value); }
	bool isXdataNotWritten() const { return GETBIT(m_Flags, XDATANOTSAVED); }

  friend class OdDbRegAppTableRecord;
};

#endif //_ODDBREGAPPTABLERECORDIMPL_INCLUDED_
