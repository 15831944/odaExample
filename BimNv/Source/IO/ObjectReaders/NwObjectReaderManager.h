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
#ifndef __NW_OBJECT_READER_MANAGER_H__
#define __NW_OBJECT_READER_MANAGER_H__

#include "TD_PackPush.h"
#include "NwObjectType.h"
#include "NwFormatVersionEx.h"
#define STL_USING_MEMORY
#define STL_USING_VECTOR
#include "OdaSTL.h"
#include "SharedPtr.h"

class OdNwData;
typedef std::shared_ptr<OdNwData> OdNwDataPtr;
class OdNwOptions;
typedef OdSharedPtr<OdNwOptions> OdNwOptionsPtr;
class OdNwStreamContext;
typedef std::shared_ptr<OdNwStreamContext> OdNwStreamContextPtr;
class OdNwEmbeddedFile;
typedef std::shared_ptr<OdNwEmbeddedFile> OdNwEmbeddedFilePtr;
class OdNwObject;
typedef OdSmartPtr<OdNwObject> OdNwObjectPtr;
class OdStreamBuf;
typedef OdSmartPtr<OdStreamBuf> OdStreamBufPtr;
class OdNwDatabaseImpl;

class OdNwObjectReaderManager
{
public:
  OdNwObjectReaderManager(OdStreamBufPtr pStreamBuf, const OdNwStreamContextPtr& pContext);
  explicit OdNwObjectReaderManager(const OdNwStreamContextPtr& pContext);
  virtual ~OdNwObjectReaderManager() {};

  OdResult addToObjectVector(OdNwObjectPtr pObject, OdInt32 index);
  template <typename T>
  void processObjects(T func)
  {
    func(m_vObjects);
  }
  OdNwObjectPtr readObject(OdResult& res, NwObjectType::Enum verifyType = NwObjectType::Unknown);
  OdResult readObjectVector(std::vector<OdNwObjectPtr>& vObjects);

  OdNwOptionsPtr readOptions();
  OdNwDataPtr readData();
  OdNwEmbeddedFilePtr readEmbeddedFile();

  NwFormatVersionEx::Enum getFormatVersion() const;
  void alignPointer();

public:
  OdNwStreamContextPtr getContext() const;
  OdNwDatabaseImpl* getDatabase() const;
  operator OdStreamBuf& ();
  OdStreamBufPtr getStreamBuf();

protected:
  OdUInt32 m_nObjectIndex;
  OdStreamBufPtr m_pStream;
  OdNwStreamContextPtr m_pContext;
  std::vector<OdNwObjectPtr> m_vObjects;
};

/** \details
    This template class is a specialization of the OdSharedPtr class for OdNwObjectReaderManager object pointers.
*/
typedef OdSharedPtr<OdNwObjectReaderManager> OdNwObjectReaderManagerPtr;

#include "TD_PackPop.h"

#endif // __NW_OBJECT_READER_MANAGER_H__
