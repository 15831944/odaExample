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


#ifndef   _ODRX_EVENTPROVIDER_H__
#define   _ODRX_EVENTPROVIDER_H__

#include "EditorImpl.h"

#define FIRE_RXEVENT(method) \
{ OdRxEventImplPtr pEvt = odrxEvent(); if(!pEvt.isNull()) pEvt->fire_##method; }

#define FIRE_EDEVENT(method) \
{ OdEditorImplPtr pEvt = odedEditor(); if(!pEvt.isNull()) pEvt->fire_##method; }

class OdDbAbortEvent
{
protected:
  OdDbAbortEvent() : m_abort(true) {}
  bool aborted() { return m_abort; }
public:
  void finalize() { m_abort = false; }
private:
  bool m_abort;
};

class OdDbSaveEvent : public OdDbAbortEvent
{
  OdDbDatabase* m_pDb;
  OdString      m_fileName;
public:
  OdDbSaveEvent(OdDbDatabase* pDb, const OdString& fileName) 
    : m_pDb(pDb)
  {
    FIRE_RXEVENT(beginSave(pDb, fileName))
  }
  ~OdDbSaveEvent()
  {
    if (aborted())
    {
      FIRE_RXEVENT(abortSave(m_pDb))
    }
    else
    {
      FIRE_RXEVENT(saveComplete(m_pDb, m_fileName))
    }
  }
  void finalize(const OdString& fileName)
  { 
    OdDbAbortEvent::finalize();
    m_fileName  = fileName; 
  }
};

class OdDbDxfInEvent : public OdDbAbortEvent
{
public:
  OdDbDxfInEvent(OdDbDatabase* pDb) 
    : m_pDb(pDb)
  {
    FIRE_RXEVENT(beginDxfIn(m_pDb))
  }
  ~OdDbDxfInEvent()
  {
    if (aborted())
    {
      FIRE_RXEVENT(abortDxfIn(m_pDb))
    }
    else
    {
      FIRE_RXEVENT(dxfInComplete(m_pDb))
    }
  }
private:
  OdDbDatabase*  m_pDb;
};

class OdDbDxfOutEvent : public OdDbAbortEvent
{
public:
  OdDbDxfOutEvent(OdDbDatabase* pDb) 
    : m_pDb(pDb)
  {
    FIRE_RXEVENT(beginDxfOut(m_pDb))
  }
  ~OdDbDxfOutEvent()
  {
    if (aborted())
    {
      FIRE_RXEVENT(abortDxfOut(m_pDb))
    }
    else
    {
      FIRE_RXEVENT(dxfOutComplete(m_pDb))
    }
  }
private:
  OdDbDatabase*  m_pDb;
};

class OdDbDeepCloneEvent : public OdDbAbortEvent
{
  OdDbIdMapping& m_idMap;
public:
  OdDbDeepCloneEvent(OdDbDatabase* pTo, OdDbIdMapping& idMap)
    : m_idMap(idMap)
  {
    FIRE_RXEVENT(beginDeepClone(pTo, idMap))
  }
  ~OdDbDeepCloneEvent()
  {
    if (aborted())
    {
      FIRE_RXEVENT(abortDeepClone(m_idMap))
    }
    else
    {
      FIRE_RXEVENT(endDeepClone(m_idMap))
    }
  }
  void beginXlation()
  {
    FIRE_RXEVENT(beginDeepCloneXlation(m_idMap))
  }
};

class OdDbWblockCloneEvent : public OdDbAbortEvent
{
  OdDbDatabase*  m_pDbTo;
  OdDbDatabase*  m_pDbFrom;
  OdDbIdMapping& m_idMap;
public:
  OdDbWblockCloneEvent(OdDbDatabase* pTo, OdDbDatabase* pFrom, OdDbIdMapping& idMap)
    : m_pDbTo(pTo)
    , m_pDbFrom(pFrom)
    , m_idMap(idMap)
  {
    FIRE_RXEVENT(beginDeepClone(pTo, idMap))
    FIRE_RXEVENT(beginWblock(pTo, pFrom))
  }
  OdDbWblockCloneEvent(OdDbDatabase* pTo, OdDbDatabase* pFrom, OdDbIdMapping& idMap, OdDbObjectId blockId)
    : m_pDbTo(pTo)
    , m_pDbFrom(pFrom)
    , m_idMap(idMap)
  {
    FIRE_RXEVENT(beginDeepClone(pTo, idMap))
    FIRE_RXEVENT(beginWblock(pTo, pFrom, blockId))
  }
  OdDbWblockCloneEvent(OdDbDatabase* pTo, OdDbDatabase* pFrom, OdDbIdMapping& idMap, const OdGePoint3d& insertionPoint)
    : m_pDbTo(pTo)
    , m_pDbFrom(pFrom)
    , m_idMap(idMap)
  {
    FIRE_RXEVENT(beginDeepClone(pTo, idMap))
    FIRE_RXEVENT(beginWblock(pTo, pFrom, insertionPoint))
  }
  ~OdDbWblockCloneEvent()
  {
    if (aborted())
    {
      FIRE_RXEVENT(abortDeepClone(m_idMap))
      FIRE_RXEVENT(abortWblock(m_pDbTo))
    }
    else
    {
      FIRE_RXEVENT(endDeepClone(m_idMap))
      FIRE_RXEVENT(endWblock(m_pDbTo))
    }
  }
  void beginXlation()
  {
    FIRE_RXEVENT(otherWblock(m_pDbTo, m_idMap, m_pDbFrom));
    FIRE_RXEVENT(beginDeepCloneXlation(m_idMap))
  }
};

class OdDbInsertEvent : public OdDbAbortEvent
{
  OdDbDatabase*  m_pDbTo;
public:
  OdDbInsertEvent(OdDbDatabase* pTo, const OdString& pBlockName, OdDbDatabase* pFrom)
    : m_pDbTo(pTo)
  {
    FIRE_RXEVENT(beginInsert(pTo, pBlockName, pFrom))
  }
  OdDbInsertEvent(OdDbDatabase* pTo, const OdGeMatrix3d& xform, OdDbDatabase* pFrom)
    : m_pDbTo(pTo)
  {
    FIRE_RXEVENT(beginInsert(pTo, xform, pFrom))
  }
  ~OdDbInsertEvent()
  {
    if (aborted())
    {
      FIRE_RXEVENT(abortInsert(m_pDbTo))
    }
    else
    {
      FIRE_RXEVENT(endInsert(m_pDbTo))
    }
  }
};

class OdDbXrefAttachEvent : public OdDbAbortEvent
{
  OdDbDatabase* m_pHostDb;
  OdDbDatabase* m_pXrefDb;
public:
  OdDbXrefAttachEvent(OdDbDatabase* pHostDb, const OdString& pBlockName, OdDbDatabase* pXrefDb)
    : m_pHostDb(pHostDb)
    , m_pXrefDb(pXrefDb)
  {
    FIRE_RXEVENT(beginAttach(pHostDb, pBlockName, pXrefDb))
  }
  OdDbXrefAttachEvent(OdDbDatabase* pHostDb, const OdGeMatrix3d& xform, OdDbDatabase* pXrefDb)
    : m_pHostDb(pHostDb)
    , m_pXrefDb(pXrefDb)
  {
    FIRE_RXEVENT(beginInsert(pHostDb, xform, pXrefDb))
  }
  ~OdDbXrefAttachEvent()
  {
    if (aborted())
    {
      FIRE_RXEVENT(abortAttach(m_pHostDb))
    }
    else
    {
      FIRE_RXEVENT(otherAttach(m_pHostDb, m_pXrefDb))
        FIRE_RXEVENT(endAttach(m_pHostDb))
    }
  }
};

class XrefSubCommandEvent : public OdDbAbortEvent
{
  OdDbDatabase* m_pHostDb;
  OdXrefSubCommand m_subCmd;
  const OdDbObjectIdArray& m_btrIds;
  const OdStringArray& m_btrNames;
  const OdStringArray& m_paths;
public:
  XrefSubCommandEvent(OdDbDatabase* pHostDb, OdXrefSubCommand subCmd, const OdDbObjectIdArray& btrIds,
    const OdStringArray& btrNames, const OdStringArray& paths)
    : m_pHostDb(pHostDb), m_subCmd(subCmd), m_btrIds(btrIds), m_btrNames(btrNames), m_paths(paths)
  {
    bool abort = false;
    FIRE_RXEVENT(xrefSubCommandStart(pHostDb, subCmd, btrIds, btrNames, paths, abort));
    if (abort)
    {
      FIRE_RXEVENT(xrefSubCommandAborted(m_pHostDb, m_subCmd, m_btrIds, m_btrNames, m_paths));
      throw OdError(eVetoed);
    }
  }
  ~XrefSubCommandEvent()
  {
    if (aborted())
    {
      FIRE_RXEVENT(xrefSubCommandAborted(m_pHostDb, m_subCmd, m_btrIds, m_btrNames, m_paths));
    }
    else
    {
      FIRE_RXEVENT(xrefSubCommandEnd(m_pHostDb, m_subCmd, m_btrIds, m_btrNames, m_paths));
    }
  }
};

#endif //_ODRX_EVENTPROVIDER_H__
