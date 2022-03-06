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
#ifndef __NW_OBJECT_WRITER_MANAGER_H__
#define __NW_OBJECT_WRITER_MANAGER_H__

#include "TD_PackPush.h"
#define STL_USING_MEMORY
#include "OdaSTL.h"

class OdNwOptions;
class OdNwData;
class OdNwDatabaseImpl;
class OdNwStreamContext;
class OdNwEmbeddedFile;
class OdNwObject;
class OdStreamBuf;

typedef std::weak_ptr<OdNwData> OdNwDataWeakPtr;
typedef std::shared_ptr<OdNwEmbeddedFile> OdNwEmbeddedFilePtr;
typedef std::shared_ptr<OdNwStreamContext> OdNwStreamContextPtr;
typedef OdSmartPtr<OdNwObject> OdNwObjectPtr;
typedef OdSmartPtr<OdStreamBuf> OdStreamBufPtr;

class OdNwObjectWriterManager
{
public:
  OdNwObjectWriterManager(OdStreamBufPtr stream, const OdNwStreamContextPtr& pContext);
  ~OdNwObjectWriterManager() = default;

  OdResult writeObject(const OdNwObjectPtr& element);
  void writeOptions(OdNwOptions* pOptions);
  void writeData(OdNwDataWeakPtr pData);
  void writeEmbeddedFile(OdNwEmbeddedFilePtr pEmpFile);
  void alignPointer();
  void finish();

public:
  OdNwStreamContextPtr getContext() const;
  OdNwDatabaseImpl* getDatabase() const;
  operator OdStreamBuf& ();
  void addReusedIndex(OdUInt64&& key, OdUInt32 index);

protected:
  OdUInt32 m_nObjectIndex;
  OdStreamBufPtr m_pStream;
  OdNwStreamContextPtr m_pContext;
  std::map<OdUInt64, OdUInt32> m_mReusedIdxs;
};

/** \details
    This template class is a specialization of the OdSharedPtr class for OdNwObjectWriterManager object pointers.
*/
typedef OdSharedPtr<OdNwObjectWriterManager> OdNwObjectWriterManagerPtr;

#include "TD_PackPop.h"

#endif // __NW_OBJECT_WRITER_MANAGER_H__
