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




#ifndef   _ODEDITORIMPL_H_INCLUDED_
#define   _ODEDITORIMPL_H_INCLUDED_

#include "TD_PackPush.h"

#include "Editor.h"
#include "DbIdMapping.h"

/** \details

    <group OdRx_Classes> 
*/

#define RXEVENT_FIRE(method, inparams, params) \
inline void fire_##method inparams \
{ \
  TD_AUTOLOCK( m_mutex ); \
  const OdArray<OdRxEventReactorPtr> reactors = m_reactors; \
  for (unsigned i = 0; i < reactors.size(); ++i) \
  { \
    OdRxEventReactorPtr reactor = reactors[i]; \
    if (m_reactors.contains(reactor))\
      reactor->method params; \
  } \
}

#define EDEVENT_FIRE(method, inparams, params) \
inline void fire_##method inparams \
{ \
  TD_AUTOLOCK( m_mutex ); \
  const OdArray<OdRxEventReactorPtr> reactors = m_reactors; \
  for (unsigned i = 0; i < reactors.size(); ++i) \
  { \
    OdRxEventReactorPtr reactor = reactors[i]; \
    if (m_reactors.contains(reactor))\
    {\
      OdEditorReactorPtr edReactor = OdTvEditorReactor::cast(reactor); \
      if (edReactor.get()) edReactor->method params; \
    }\
  } \
}

#define DCEVENT_FIRE(method, inparams, params, IdMappingToDatabase) \
inline void fire_##method inparams \
{ \
  TD_AUTOLOCK( m_mutex ); \
  const OdArray<OdRxEventReactorPtr> reactors = m_reactors; \
  for (unsigned i = 0; i < reactors.size(); ++i) \
  { \
    OdRxEventReactorPtr reactor = reactors[i]; \
    if (m_reactors.contains(reactor))\
      reactor->method params; \
  } \
}

#define RXEVENT_FIRE_ABORT(method, inparams, params, abortmethod, abortparams) \
inline void fire_##method inparams \
{ \
  TD_AUTOLOCK( m_mutex ); \
  OdArray<OdRxEventReactorPtr> reactors = m_reactors; \
  OdArray<OdRxEventReactorPtr> firedReactors(reactors.length()); \
  for (unsigned i = 0; i < reactors.size(); ++i) \
  { \
    if (m_reactors.contains(reactors[i])) \
    { \
      try \
      { \
        firedReactors.append(reactors[i]); \
        reactors[i]->method params; \
      } \
      catch(...) \
      { \
        for (unsigned j = 0; j < firedReactors.size(); ++j) \
        { \
          if (m_reactors.contains(firedReactors[j])) \
            firedReactors[j]->abortmethod abortparams; \
        } \
        throw; \
      } \
    } \
  } \
}

#define EDEVENT_FIRE_ABORT(method, inparams, params, abortmethod, abortparams) \
inline void fire_##method inparams \
{ \
  TD_AUTOLOCK( m_mutex ); \
  OdArray<OdRxEventReactorPtr> reactors = m_reactors; \
  OdArray<OdEditorReactorPtr> firedReactors(reactors.length()); \
  for (unsigned i = 0; i < reactors.size(); ++i) \
  { \
    if (m_reactors.contains(reactors[i])) \
    { \
      try \
      { \
        OdEditorReactorPtr pReactor = OdTvEditorReactor::cast(reactors[i]); \
        if (pReactor.get()) \
        { \
          firedReactors.append(pReactor); \
          pReactor->method params; \
        } \
      } \
      catch(...) \
      { \
        for (unsigned i = 0; i < firedReactors.size(); ++i) \
        { \
          if (m_reactors.contains(firedReactors[i])) \
            firedReactors[i]->abortmethod abortparams; \
        } \
        throw; \
      } \
    } \
  } \
}


/** \details
    This class defines the events that trigger OdTvRxEventReactor instances. 
    Corresponding C++ library: TD_Db
    <group OdRx_Classes> 
*/
class TOOLKIT_EXPORT OdTvRxEventImpl : public OdTvEditor
{
protected:
  OdArray<OdRxEventReactorPtr> m_reactors;
  OdMutex m_mutex;
public:
  OdTvRxEventImpl() {}
  ODRX_DECLARE_MEMBERS(OdTvRxEventImpl);
  
  void addReactor(OdTvRxEventReactor* pReactor);
  void removeReactor(OdTvRxEventReactor* pReactor);

  // notifiers
  RXEVENT_FIRE(dwgFileOpened, (OdTvDbDatabase* db, const OdString& filename),(db, filename))
  RXEVENT_FIRE(initialDwgFileOpenComplete, (OdTvDbDatabase* db), (db))
  RXEVENT_FIRE(databaseConstructed, (OdTvDbDatabase* db), (db))
  RXEVENT_FIRE(databaseToBeDestroyed, (OdTvDbDatabase* db), (db))
  RXEVENT_FIRE_ABORT(beginSave, (OdTvDbDatabase* db, const OdString& pIntendedName), (db, pIntendedName), abortSave, (db))
  RXEVENT_FIRE(saveComplete, (OdTvDbDatabase* db, const OdString& pActualName), (db, pActualName))
  RXEVENT_FIRE(abortSave, (OdTvDbDatabase* db), (db))
  // DXF In/Out Events.
  RXEVENT_FIRE_ABORT(beginDxfIn, (OdTvDbDatabase* db), (db), abortDxfIn, (db))
  RXEVENT_FIRE(abortDxfIn, (OdTvDbDatabase* db), (db))
  RXEVENT_FIRE(dxfInComplete, (OdTvDbDatabase* db), (db))
  //
  RXEVENT_FIRE_ABORT(beginDxfOut, (OdTvDbDatabase* db), (db), abortDxfOut, (db))
  RXEVENT_FIRE(abortDxfOut, (OdTvDbDatabase* db), (db))
  RXEVENT_FIRE(dxfOutComplete, (OdTvDbDatabase* db), (db))
  // Insert Events.
  RXEVENT_FIRE_ABORT(beginInsert, (OdTvDbDatabase* pTo, const OdString& pBlockName, OdTvDbDatabase* pFrom), (pTo, pBlockName, pFrom), abortInsert, (pTo))
  RXEVENT_FIRE_ABORT(beginInsert, (OdTvDbDatabase* pTo, const OdGeMatrix3d& xform, OdTvDbDatabase* pFrom), (pTo, xform, pFrom), abortInsert, (pTo))
  RXEVENT_FIRE_ABORT(otherInsert, (OdTvDbDatabase* pTo, OdTvDbIdMapping& idMap, OdTvDbDatabase* pFrom), (pTo, idMap, pFrom), abortInsert, (pTo))
  RXEVENT_FIRE(abortInsert, (OdTvDbDatabase* pTo), (pTo))
  RXEVENT_FIRE(endInsert, (OdTvDbDatabase* pTo), (pTo))

  // Wblock Events.
  RXEVENT_FIRE(wblockNotice, (OdTvDbDatabase* pDb), (pDb))
  RXEVENT_FIRE_ABORT(beginWblock, (OdTvDbDatabase* pTo, OdTvDbDatabase* pFrom, const OdGePoint3d& insertionPoint), (pTo, pFrom, insertionPoint), abortWblock, (pTo))
  RXEVENT_FIRE_ABORT(beginWblock, (OdTvDbDatabase* pTo, OdTvDbDatabase* pFrom, OdTvDbObjectId blockId), (pTo, pFrom, blockId), abortWblock, (pTo))
  RXEVENT_FIRE_ABORT(beginWblock, (OdTvDbDatabase* pTo, OdTvDbDatabase* pFrom), (pTo, pFrom), abortWblock, (pTo))
  RXEVENT_FIRE_ABORT(otherWblock, (OdTvDbDatabase* pTo, OdTvDbIdMapping& m, OdTvDbDatabase* pFrom), (pTo, m, pFrom), abortWblock, (pTo))
  RXEVENT_FIRE(abortWblock, (OdTvDbDatabase* pTo), (pTo))
  RXEVENT_FIRE(endWblock, (OdTvDbDatabase* pTo), (pTo))
  RXEVENT_FIRE(beginWblockObjects, (OdTvDbDatabase* pDb, OdTvDbIdMapping& m), (pDb, m))

  // Deep Clone Events.
  DCEVENT_FIRE(beginDeepClone, (OdTvDbDatabase* pTo, OdTvDbIdMapping& m), (pTo, m), &m)
  RXEVENT_FIRE_ABORT(beginDeepCloneXlation, (OdTvDbIdMapping& m), (m), abortDeepClone, (m))
  DCEVENT_FIRE(abortDeepClone, (OdTvDbIdMapping& m), (m), 0)
  DCEVENT_FIRE(endDeepClone, (OdTvDbIdMapping& m), (m), 0)

  // Partial Open Events.
  RXEVENT_FIRE(partialOpenNotice, (OdTvDbDatabase* pDb), (pDb))

  RXEVENT_FIRE_ABORT(xrefSubCommandStart,   (OdTvDbDatabase* pHostDb, OdXrefSubCommand subCmd, const OdTvDbObjectIdArray& btrIds, const OdStringArray& btrNames, const OdStringArray& paths, bool& vetoOp),
                                            (pHostDb, subCmd, btrIds, btrNames, paths, vetoOp), xrefSubCommandAborted, (pHostDb, subCmd, btrIds, btrNames, paths))

  RXEVENT_FIRE_ABORT(xrefSubCommandEnd,     (OdTvDbDatabase* pHostDb, OdXrefSubCommand subCmd, const OdTvDbObjectIdArray& btrIds, const OdStringArray& btrNames, const OdStringArray& paths),
                                            (pHostDb, subCmd, btrIds, btrNames, paths), xrefSubCommandAborted, (pHostDb, subCmd, btrIds, btrNames, paths))

  RXEVENT_FIRE_ABORT(xrefSubCommandAborted, (OdTvDbDatabase* pHostDb, OdXrefSubCommand subCmd, const OdTvDbObjectIdArray& btrIds, const OdStringArray& btrNames, const OdStringArray& paths),
                                            (pHostDb, subCmd, btrIds, btrNames, paths), xrefSubCommandAborted, (pHostDb, subCmd, btrIds, btrNames, paths))
  //
  // OdTvEditorReactor events.
  //
  // file events
  EDEVENT_FIRE(beginDwgOpen, (const OdString& filename), (filename))
  EDEVENT_FIRE(endDwgOpen,   (const OdString& filename), (filename))
  EDEVENT_FIRE(beginClose,   (OdTvDbDatabase* pDb), (pDb))

  // xref events
  EDEVENT_FIRE_ABORT(beginAttach,  (OdTvDbDatabase* pToDb, const OdString& filename, OdTvDbDatabase* pFromDb), (pToDb, filename, pFromDb), abortAttach, (pToDb))
  EDEVENT_FIRE_ABORT(otherAttach,  (OdTvDbDatabase* pToDb, OdTvDbDatabase* pFromDb), (pToDb, pFromDb), abortAttach, (pToDb))
  EDEVENT_FIRE(abortAttach,  (OdTvDbDatabase* pFromDb), (pFromDb))
  EDEVENT_FIRE(endAttach,    (OdTvDbDatabase* pToDb), (pToDb))
  EDEVENT_FIRE(redirected,   (OdTvDbObjectId newId, OdTvDbObjectId oldId), (newId, oldId))
  EDEVENT_FIRE(comandeered,  (OdTvDbDatabase* pToDb, OdTvDbObjectId id, OdTvDbDatabase* pFromDb), (pToDb, id, pFromDb))
  EDEVENT_FIRE_ABORT(beginRestore, (OdTvDbDatabase* pToDb, const OdString& filename, OdTvDbDatabase* pFromDb), (pToDb, filename, pFromDb), abortRestore, (pToDb))
  EDEVENT_FIRE(abortRestore, (OdTvDbDatabase* pToDb), (pToDb))
  EDEVENT_FIRE(endRestore,   (OdTvDbDatabase* pToDb), (pToDb))

  // xref subcommand events
  EDEVENT_FIRE_ABORT(xrefSubCommandStart,       (OdTvDbDatabase* pHostDb, OdXrefSubCommand subCmd, const OdTvDbObjectIdArray& btrIds, const OdStringArray& btrNames, const OdStringArray& paths),
                                                (pHostDb, subCmd, btrIds, btrNames, paths), xrefSubCommandAborted, (pHostDb, subCmd, btrIds, btrNames, paths))
  EDEVENT_FIRE(xrefSubcommandBindItem,    (int activity, OdTvDbObjectId blockId), (activity, blockId))
  EDEVENT_FIRE(xrefSubcommandAttachItem,  (int activity, const OdString& xrefPath), (activity, xrefPath))
  EDEVENT_FIRE(xrefSubcommandOverlayItem, (int activity, const OdString& xrefPath), (activity, xrefPath))
  EDEVENT_FIRE(xrefSubcommandDetachItem,  (int activity, OdTvDbObjectId blockId), (activity, blockId))
  EDEVENT_FIRE(xrefSubcommandPathItem,    (int activity, OdTvDbObjectId blockId, const OdString& newPath), (activity, blockId, newPath))
  EDEVENT_FIRE(xrefSubcommandReloadItem,  (int activity, OdTvDbObjectId blockId), (activity, blockId))
  EDEVENT_FIRE(xrefSubcommandUnloadItem,  (int activity, OdTvDbObjectId blockId), (activity, blockId))

  // command undo events
  EDEVENT_FIRE(undoSubcommandAuto,   (int activity, bool state), (activity, state))
  EDEVENT_FIRE(undoSubcommandControl,(int activity, int option), (activity, option))
  EDEVENT_FIRE(undoSubcommandBegin,  (int activity), (activity))
  EDEVENT_FIRE(undoSubcommandEnd,    (int activity), (activity))
  EDEVENT_FIRE(undoSubcommandMark,   (int activity), (activity))
  EDEVENT_FIRE(undoSubcommandBack,   (int activity), (activity))
  EDEVENT_FIRE(undoSubcommandNumber, (int activity, int num), (activity, num))

  // pickfirst selection event
  EDEVENT_FIRE(pickfirstModified, (), ())

  // layout event
  EDEVENT_FIRE(layoutSwitched, (const OdString& newLayoutName), (newLayoutName))

  // window events
  EDEVENT_FIRE(docFrameMovedOrResized, (OdHWnd hwndDocFrame, bool moved), (hwndDocFrame, moved))
  EDEVENT_FIRE(mainFrameMovedOrResized, (OdHWnd hwndMainFrame, bool moved), (hwndMainFrame, moved))

  // mouse events
  EDEVENT_FIRE(beginDoubleClick, (const OdGePoint3d& clickPoint), (clickPoint))
  EDEVENT_FIRE(beginRightClick, (const OdGePoint3d& clickPoint), (clickPoint))

  // toolbar events
  EDEVENT_FIRE(toolbarBitmapSizeWillChange, (bool largeBitmaps), (largeBitmaps))
  EDEVENT_FIRE(toolbarBitmapSizeChanged, (bool largeBitmaps), (largeBitmaps))

  // partial open events
  EDEVENT_FIRE(objectsLazyLoaded, (const OdTvDbObjectIdArray& objectIds), (objectIds))

  // quit events
  EDEVENT_FIRE_ABORT(beginQuit,       (), (), quitAborted, ())
  EDEVENT_FIRE(quitAborted,     (), ())
  EDEVENT_FIRE(quitWillStart,   (), ())

  // modeless operation events
  EDEVENT_FIRE(modelessOperationWillStart, (const OdString& contextString), (contextString))
  EDEVENT_FIRE(modelessOperationEnded, (const OdString& contextString), (contextString))

  // SysVar events
  EDEVENT_FIRE( sysVarChanged, (OdTvDbDatabase* pDb, const OdString& varName),(pDb, varName))
  EDEVENT_FIRE( sysVarWillChange, (OdTvDbDatabase* pDb, const OdString& varName), (pDb, varName))
};

typedef OdSmartPtr<OdTvRxEventImpl> OdRxEventImplPtr;

/** \details
    This class defines the events that trigger OdTvRxEventReactor instances. 
    <group Other_Classes>
*/
class TOOLKIT_EXPORT OdTvEditorImpl : public OdTvRxEventImpl
{
public:
  OdTvEditorImpl() {}
  ODRX_DECLARE_MEMBERS(OdTvEditorImpl);
};

typedef OdSmartPtr<OdTvEditorImpl> OdEditorImplPtr;

#include "TD_PackPop.h"

#endif // _ODEDITORIMPL_H_INCLUDED_

