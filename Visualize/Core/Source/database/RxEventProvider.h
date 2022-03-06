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
{ OdRxEventImplPtr pEvt = odtvrxEvent(); if(!pEvt.isNull()) pEvt->fire_##method; }

#define FIRE_EDEVENT(method) \
{ OdEditorImplPtr pEvt = odtvedEditor(); if(!pEvt.isNull()) pEvt->fire_##method; }

class OdTvDbAbortEvent
{
protected:
  OdTvDbAbortEvent() : m_abort(true) {}
  bool aborted() { return m_abort; }
public:
  void finalize() { m_abort = false; }
private:
  bool m_abort;
};

class OdTvDbSaveEvent : public OdTvDbAbortEvent
{
  OdTvDbDatabase* m_pDb;
  OdString      m_fileName;
public:
  OdTvDbSaveEvent(OdTvDbDatabase* pDb, const OdString& fileName) 
    : m_pDb(pDb)
  {
    FIRE_RXEVENT(beginSave(pDb, fileName))
  }
  ~OdTvDbSaveEvent()
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
    OdTvDbAbortEvent::finalize();
    m_fileName  = fileName; 
  }
};

class OdTvDbDxfInEvent : public OdTvDbAbortEvent
{
public:
  OdTvDbDxfInEvent(OdTvDbDatabase* pDb) 
    : m_pDb(pDb)
  {
    FIRE_RXEVENT(beginDxfIn(m_pDb))
  }
  ~OdTvDbDxfInEvent()
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
  OdTvDbDatabase*  m_pDb;
};

class OdTvDbDxfOutEvent : public OdTvDbAbortEvent
{
public:
  OdTvDbDxfOutEvent(OdTvDbDatabase* pDb) 
    : m_pDb(pDb)
  {
    FIRE_RXEVENT(beginDxfOut(m_pDb))
  }
  ~OdTvDbDxfOutEvent()
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
  OdTvDbDatabase*  m_pDb;
};

class OdTvDbWblockCloneEvent : public OdTvDbAbortEvent
{
  OdTvDbDatabase*  m_pDbTo;
  OdTvDbDatabase*  m_pDbFrom;
  OdTvDbIdMapping& m_idMap;
public:
  OdTvDbWblockCloneEvent(OdTvDbDatabase* pTo, OdTvDbDatabase* pFrom, OdTvDbIdMapping& idMap)
    : m_pDbTo(pTo)
    , m_pDbFrom(pFrom)
    , m_idMap(idMap)
  {
    FIRE_RXEVENT(beginDeepClone(pTo, idMap))
    FIRE_RXEVENT(beginWblock(pTo, pFrom))
  }
  OdTvDbWblockCloneEvent(OdTvDbDatabase* pTo, OdTvDbDatabase* pFrom, OdTvDbIdMapping& idMap, OdTvDbObjectId blockId)
    : m_pDbTo(pTo)
    , m_pDbFrom(pFrom)
    , m_idMap(idMap)
  {
    FIRE_RXEVENT(beginDeepClone(pTo, idMap))
    FIRE_RXEVENT(beginWblock(pTo, pFrom, blockId))
  }
  OdTvDbWblockCloneEvent(OdTvDbDatabase* pTo, OdTvDbDatabase* pFrom, OdTvDbIdMapping& idMap, const OdGePoint3d& insertionPoint)
    : m_pDbTo(pTo)
    , m_pDbFrom(pFrom)
    , m_idMap(idMap)
  {
    FIRE_RXEVENT(beginDeepClone(pTo, idMap))
    FIRE_RXEVENT(beginWblock(pTo, pFrom, insertionPoint))
  }
  ~OdTvDbWblockCloneEvent()
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

class OdTvDbInsertEvent : public OdTvDbAbortEvent
{
  OdTvDbDatabase*  m_pDbTo;
public:
  OdTvDbInsertEvent(OdTvDbDatabase* pTo, const OdString& pBlockName, OdTvDbDatabase* pFrom)
    : m_pDbTo(pTo)
  {
    FIRE_RXEVENT(beginInsert(pTo, pBlockName, pFrom))
  }
  OdTvDbInsertEvent(OdTvDbDatabase* pTo, const OdGeMatrix3d& xform, OdTvDbDatabase* pFrom)
    : m_pDbTo(pTo)
  {
    FIRE_RXEVENT(beginInsert(pTo, xform, pFrom))
  }
  ~OdTvDbInsertEvent()
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

class XrefSubCommandEvent : public OdTvDbAbortEvent
{
  OdTvDbDatabase* m_pHostDb;
  OdXrefSubCommand m_subCmd;
  const OdTvDbObjectIdArray& m_btrIds;
  const OdStringArray& m_btrNames;
  const OdStringArray& m_paths;
public:
  XrefSubCommandEvent(OdTvDbDatabase* pHostDb, OdXrefSubCommand subCmd, const OdTvDbObjectIdArray& btrIds,
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
