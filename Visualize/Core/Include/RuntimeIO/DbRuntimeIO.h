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


#ifndef _OdTvDbRuntimeIOModule_H_
#define _OdTvDbRuntimeIOModule_H_

//#ifdef DBRUNTIMEIO_EXPORTS
//#define DBRTIO_EXPORT            OD_TOOLKIT_EXPORT
//#define DBRTIO_EXPORT_GLOBAL     OD_DLL_EXPORT
//#define DBRTIO_EXPORT_STATIC     OD_STATIC_EXPORT
//#else
//#define DBRTIO_EXPORT            OD_TOOLKIT_IMPORT
//#define DBRTIO_EXPORT_GLOBAL     OD_DLL_IMPORT
//#define DBRTIO_EXPORT_STATIC     OD_STATIC_IMPORT
//#endif

#include "RxModule.h"
#include "SmartPtr.h"
#include "OdArray.h"
#include "RxSystemServices.h"
#include "UInt64Array.h"
#define STL_USING_QUEUE
#include "OdaSTL.h"

#include "TD_PackPush.h"
#include "DbObjectId.h"

class OdTvDbDatabase;

/** \details
  Library:  DbRuntimeIO
  <group OdTvDb_Classes>
*/
class OdTvDbRuntimeIOModule : public OdRxModule {
protected:
  virtual void initApp();
  virtual void uninitApp();
public:
  virtual void writeFile(OdTvDbDatabase* db, const OdString& fileName);
  virtual void readFile(OdTvDbDatabase* db, const OdString& fileName, bool lazyObjectLoading = false);
};

typedef OdSmartPtr<OdTvDbRuntimeIOModule> OdTvDbRuntimeIOModulePtr;
class OdDbStub;
class OdTvDbObject;
typedef OdSmartPtr<OdTvDbObject> OdTvDbObjectPtr;

/**   
  <group !!RECORDS_tdrawings_apiref>
*/
enum OdTvDbReferenceType {
  kSoftPointer = 0,  // Soft Pointer Reference
  kHardPointer = 1,  // Hard Pointer Reference
  kSoftOwnership = 2,  // Soft Ownership Reference
  kHardOwnership = 3   // Hard Ownership Reference
};

/** \details
  <group OdTvDb_Classes>
  Library:  DbRuntimeIO
*/
template <class TReference>
class OdTvDbReferenceQueue {
  typedef std::pair<TReference, OdTvDbReferenceType> TypedReference;
  typedef std::queue<TypedReference> RefQueueImp;
  RefQueueImp queue;
  bool addHardRef, addOwnershipRef, addSoftRef;
public:
  OdTvDbReferenceQueue(bool addOwnershipRef = true, bool addHardRef = false, bool addSoftRef = false) {
    this->addOwnershipRef = addOwnershipRef;
    this->addHardRef = addHardRef;
    this->addSoftRef = addHardRef;
  }
  size_t size() const { return queue.size(); }
  bool push(const TReference& ref, OdTvDbReferenceType type = kSoftPointer);
  TReference pop(OdTvDbReferenceType* type = 0);
  void clear() { queue = RefQueueImp(); }
};

/** \details
  Library:  DbRuntimeIO
  <group OdTvDb_Classes>
*/
class OdTvDbRtFilerController : public OdRxObject {
public:
  ODRX_DECLARE_MEMBERS(OdTvDbRtFilerController);

  virtual void reset(OdTvDbDatabase* db) = 0;

  virtual OdTvDbDatabase* database() = 0;

  virtual void writeDataFrame(OdStreamBuf& output) = 0;

  virtual void closeInput(bool finishDataLoading = false) = 0;

  // loads only index if no database
  virtual void loadDataFrame(OdStreamBuf& input) = 0;

  void writeFile(OdTvDbDatabase* db, const OdString& fileName) {
    reset(db);
    using namespace Oda;
    writeDataFrame(*::odrxSystemServices()->createFile(fileName, kFileWrite, kShareDenyReadWrite, kCreateAlways));
    closeInput();
  }

  void readFile(OdTvDbDatabase* db, const OdString& fileName, bool lazyObjectLoading) {
    reset(db);
    loadDataFrame(*::odrxSystemServices()->createFile(fileName));
    closeInput();
  }

  virtual OdStreamBufPtr openStream(const OdString& name, Oda::FileAccessMode mode) = 0;

  virtual OdUInt64 lookupOffset(OdDbStub* id) = 0;

  virtual OdUInt64 lookupOffset(OdUInt64 handle) = 0;

  virtual OdUInt64 seekObject(OdUInt64 handle) = 0;

  virtual void loadObjects(OdStreamBuf& objectStream, OdUInt64 endPos = 0xFFFFFFFFFFFFFFFFULL) = 0;

  virtual void startDataFrame(OdStreamBuf& output, bool enableCopyMaping = true) = 0;

  virtual void disableObjectCopyMapping(bool doIt = true) = 0;

  typedef OdTvDbReferenceQueue<OdUInt64> RefQueue;
  typedef OdTvDbReferenceQueue<OdDbStub*> IdRefQueue;

  virtual OdTvDbObjectPtr readObject(OdStreamBuf& objectInStream, IdRefQueue* refQueue = 0) = 0;
  virtual void copyObjectStream(OdUInt64 handle, OdStreamBuf& output, RefQueue* refQueue = 0) = 0;
  virtual void copyStream(OdStreamBuf& output, RefQueue* refQueue = 0) = 0;

  virtual void copyObjectStream(const OdTvDbObjectId &id, OdStreamBuf& output, IdRefQueue* idrefQueue = 0) = 0;
  virtual void copyStream(OdStreamBuf& output, IdRefQueue* idrefQueue = 0) = 0;

  virtual OdUInt64 readObjectSize(OdStreamBuf& input) = 0; // reads and returns object data counter; curpos after counter
  virtual OdUInt64 getObjectSize(OdStreamBuf& input) = 0; // restores input stream position after reading data counter
  virtual OdUInt64 getObjectSize(OdUInt64 handle) = 0; // restores input stream position after reading data counter

  virtual void finishDataFrame(OdStreamBuf& output) = 0;

  virtual void writeDbRoot(OdStreamBuf* output = 0, OdTvDbRtFilerController::RefQueue* refQueue = 0) = 0;
  virtual void writeObject(OdTvDbObject* obj, OdStreamBuf* output, RefQueue* refQueue = 0) = 0;
};

typedef OdSmartPtr<OdTvDbRtFilerController> OdTvDbRtFilerControllerPtr;



template <class TReference>
inline TReference OdTvDbReferenceQueue<TReference>::pop(OdTvDbReferenceType* type) {
  TReference referenceHandle;
  if (!queue.empty()) {
    TypedReference& reference = queue.front();
    referenceHandle = reference.first;
    if (type)
      *type = reference.second;
    ODA_ASSERT(referenceHandle != 0);
    queue.pop();
  }
  return referenceHandle;
}

template <class TReference>
inline bool OdTvDbReferenceQueue<TReference>::push(const TReference& ref, OdTvDbReferenceType type) {
  if ((const OdUInt64&)ref) {
    if (addSoftRef || addHardRef && GETBIT(type, 1) || addOwnershipRef && GETBIT(type, 2)) {
      queue.push(TypedReference(ref, type));
      return true;
    }
  }
  return false;
}


#include "TD_PackPop.h"

#endif // _OdTvDbRuntimeIOModule_H_
