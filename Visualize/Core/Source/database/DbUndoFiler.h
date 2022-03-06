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

// DbUndoFiler.h: interface for the OdTvDbUndoFiler class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _ODDBUNDOFILER_H_
#define _ODDBUNDOFILER_H_

#include "TD_PackPush.h"

#include "OdDwgCopyFiler.h"
#include "DbUndoController.h"
#include "DbUndoObjFiler.h"
#define STL_USING_STACK
#define STL_USING_MAP
#include "OdaSTL.h"

class OdTvDbUndoFiler;
typedef OdSmartPtr<OdTvDbUndoFiler> OdTvDbUndoFilerPtr;
class OdTvDbUndoFilerImpl;
typedef OdSmartPtr<OdTvDbUndoFilerImpl> OdTvDbUndoFilerImplPtr;

class OdTvDbUndoStream;
typedef OdSmartPtr<OdTvDbUndoStream> OdTvDbUndoStreamPtr;

class OdDbHostAppProgressMeter;

#define OdTvDbUndoStream OdMemoryStreamImpl<OdStaticRxObject<OdStreamBuf> >

template< class TBase, class TStream >
class OdCopyFilerBase2 : public TBase
{
  mutable OdSmartPtr<TStream> m_stream;
public:
  inline TStream& stream() const { return *m_stream.get(); }
  inline void setStream(const OdSmartPtr<TStream> &stream) { m_stream = stream; }
};

class TOOLKIT_EXPORT OdTvDbUndoFiler : public OdDbDwgFiler
{
public:
  virtual void wrDatabase(OdTvDbDatabase* pDb) = 0;
  virtual OdTvDbDatabase* rdDatabase() = 0;
  virtual void wrClass(const OdRxClass* c) = 0;
  virtual OdRxClass* rdClass() = 0;
};

class OdTvDbUndoFilerImpl : public OdTvDbDwgCopyFiler<OdCopyFilerBase2<OdTvDbUndoFiler, OdStreamBuf > >
{
protected:
  OdUInt32                  m_nTransactionNo;
  bool                      m_bRecordStarted;

  // May be one of the flags from
  // OdDbUndoController::kBlockBegin = 1,
  // OdDbUndoController::kBlockEnd = 2,
  // OdDbUndoController::kMarker = 3
  OdUInt32                  m_nUndoRecordOptions;

  int                       m_nOffsetSize;
  OdInt32                   m_nRecPos;
  OdDbHostAppProgressMeter *m_pMeter;
  OdDbUndoControllerPtr     m_pUndoController;
  OdTvDbUndoFilerImplPtr      m_pRedoFiler;

  OdTvDbFiler::FilerType filerType() const;

  void startUndoMeter();
  void stepUndoMeter();
  void stopUndoMeter();

  virtual bool load();
  virtual void init(OdTvDbDatabase* pDb);
  OdTvDbUndoFilerImpl();
public:
  static OdTvDbUndoFilerPtr createObject(OdTvDbDatabase* pDb);

  virtual void setProgressMeter(OdDbHostAppProgressMeter *pMeter);

  OdTvDbUndoFilerImplPtr& redoFiler(bool bCreate = false);

  virtual void undo(OdUInt32 nTransactionNo);

  virtual void startUndoRecord(OdUInt32 nTransactionNo);

  void recordUndone(OdUInt32 nTransactionNo);

  virtual bool hasUndo() const;

  virtual void writeObjectUndo(OdTvDbObject* pObj, bool bAuto);

  bool hasUndoMark() const;

  void setBlockingOption(OdUInt32 nOpt);

  int getUNDOMARKS() const;

  void clearUndo();

  // returns number of kPU_DbUndoMark outside kPU_DbUndoGroupBegin/kPU_DbUndoGroupEnd for
  // the current undo records/stream, to be stored at UndoController per record
  OdUInt32 undoRecordOptions() const { return m_nUndoRecordOptions; };

  virtual void wrDatabase(OdTvDbDatabase* pDb){ wrAddress(pDb); }
  virtual OdTvDbDatabase* rdDatabase(){ return (OdTvDbDatabase*)rdAddress(); }
  virtual void wrClass(const OdRxClass* c) { wrAddress(c); }
  virtual OdRxClass* rdClass() { return (OdRxClass*)rdAddress(); }
  virtual OdTvDbObjectPtr getErasedObject(const OdDbHandle& h) { return OdTvDbObjectPtr(); }

// IS_DIFF_UNDO_ENABLED() support begin
public:
  void writeObjectForDiff(OdTvDbObject* pObj);
  void flushDiffData(OdTvDbObject* pObj, bool discard = false);
  void swapIds(const OdTvDbObjectId& id1, const OdTvDbObjectId& id2);
  void checkDiffUndoState(int nTrans, OdTvDbObject* pObj);
#ifdef _DEBUG
  void assertNoDiffData();
#endif

protected:
  typedef std::pair<int, OdTvDbUndoObjFilerPtr> TransDiff; //transaction/difference
  typedef OdArray<TransDiff> TransDiffArray;
  typedef std::map<OdTvDbObjectId, TransDiffArray> DiffMap;

protected:
  void clearDiffDataAll();
  void flushDiffDataAll();
  void writeObjDiff(OdTvDbObject* pObj, int nTrans, OdTvDbUndoObjFiler* pDst);
  void readObjectDiff(OdTvDbObject* pObj, bool bEnd);
  void appendDiffData(const OdTvDbObjectId& id, int nTrans, OdTvDbUndoObjFiler* pData);

protected:
  DiffMap m_pendingDiff;
// IS_DIFF_UNDO_ENABLED() support end
};

struct OdTvDbUndoFilerSave
{
  OdRxObjectPtr& filer;
  OdRxObjectPtr savedFiler;
  OdTvDbUndoFilerSave(OdRxObjectPtr& f) : filer(f)
  {
    savedFiler = f;
  }
  void reset()
  {
    filer = savedFiler;
    savedFiler = 0;
  }
  ~OdTvDbUndoFilerSave()
  {
    reset();
  }
};

#include "TD_PackPop.h"

#endif // _ODDBUNDOFILER_H_
