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

#ifndef _ODDBHISTORYCONTROLLER_H_INCLUDED_
#define _ODDBHISTORYCONTROLLER_H_INCLUDED_

#include "DbHostAppServices.h"
#include "OdStreamBuf.h"
#include "DbHistoryManager.h"

struct OdDbHistoryController : OdRxObject
{
  virtual OdUInt32 revision() = 0;
  virtual void saveFile(const OdString& name) = 0;
  virtual void loadFile(OdStreamBuf* pFile) = 0;
  virtual void createNewFile(OdDbHostAppServices*) = 0;
  virtual void loadRecord(OdDbHistoryLogRecord& log, OdStreamBuf* dataStream, OdStreamBuf* idStream, OdStreamBuf* stringStream, OdStreamBuf* appendedObjects) = 0;
  virtual bool getLogMessage(OdUInt32 revision, OdDbHistoryLogRecord& log) = 0;
  virtual bool setLogMessage(OdUInt32 revision, const OdDbHistoryLogRecord& log) = 0;
  virtual void loadErased(OdStreamBuf* erasedStream) = 0;
  virtual void saveRecord(const OdDbHistoryLogRecord& log, OdStreamBuf* dataStream, OdStreamBuf* idStream, OdStreamBuf* stringStream, OdStreamBuf* appendedObjects) = 0;
  virtual void saveErased(OdStreamBuf* erasedStream) = 0;
  virtual bool hasUndo() const = 0;
  virtual void changedObjects(OdUInt32 revision, OdDbHandleArray& ids) = 0;
  virtual OdInt32 getDatabaseIndex(OdDbDatabase*) = 0;
  virtual OdDbDatabase* getDatabaseByIndex(OdInt32) = 0;
};

typedef OdSmartPtr<OdDbHistoryController> OdDbHistoryControllerPtr;

#endif
