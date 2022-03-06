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

#ifndef __ODDBIDMAPPINGIMPL_INCLUDED__
#define __ODDBIDMAPPINGIMPL_INCLUDED__

#include "DbIdMapping.h"
#include "RxObjectImpl.h"
#include "OdBlob.h"

class OdDbIdMappingImpl : public OdRxObjectImpl<OdDbIdMapping>
{
  friend class OdDbIdMapping;
public:
  OdDb::DeepCloneType           m_DCType;
  OdDb::DuplicateRecordCloning  m_DRCloning;
  bool                          m_bGlobalWblock; // see #5859 for details
  OdDbDatabase*                 m_pOrigDb;
  OdDbDatabase*                 m_pDestDb;
  OdDbObjectId                  m_xrefBlockId;
  OdBlob                        m_blob;

  ODRX_DECLARE_MEMBERS(OdDbIdMappingImpl);

  OdDbIdMappingImpl(OdDbDatabase* pOrigDb, OdDbDatabase* pDestDb,
    OdDb::DeepCloneType DCType, OdDb::DuplicateRecordCloning DRCloning, bool bGlobalWblock = false)
    : m_pOrigDb(pOrigDb)
    , m_pDestDb(pDestDb)
    , m_DCType(DCType)
    , m_DRCloning(DRCloning)
    , m_blob(0x100)
    , m_bGlobalWblock(bGlobalWblock)
  { }

  OdDbIdMappingImpl()
    : m_pOrigDb(0)
    , m_pDestDb(0)
    , m_DCType(OdDb::kDcObjects)
    , m_DRCloning(OdDb::kDrcIgnore)
    , m_blob(0x100)
    , m_bGlobalWblock(false)
  { }

  void assign(const OdDbIdPair& idPair);
  bool compute(OdDbIdPair& idPair) const;
  bool del(const OdDbObjectId& key);
  OdDbIdMappingIterPtr newIterator();
  
  OdDbDatabase* destDb() const;
  void setDestDb(OdDbDatabase* pDb);
  OdDbDatabase* origDb() const;
  OdDbObjectId insertingXrefBlockId() const;
  
  OdDb::DeepCloneType deepCloneContext() const;
  OdDb::DuplicateRecordCloning duplicateRecordCloning() const;
  ~OdDbIdMappingImpl();

  bool isStarted() { return m_pOrigDb != 0; }
  int numIds() const { return ((OdBlob &)m_blob).length() / sizeof(OdDbObjectId); }
  bool isGlobalWblock(){ return m_bGlobalWblock; }
};

class OdDbIdMappingIterImpl : public OdRxObjectImpl<OdDbIdMappingIter>
{
public:
  ODRX_DECLARE_MEMBERS(OdDbIdMappingIterImpl);

  static OdDbIdMappingIterPtr createObject(OdBlob& blob);

  void start();
  void getMap(OdDbIdPair& idPair);
  void next();
  bool done();

private:
  OdDbIdMappingIterImpl(OdBlob& blob)
    : m_blob(blob)
  {}

  void nextId();
  OdBlob&      m_blob;
  OdDbObjectId m_id;
};

#endif // __ODDBIDMAPPINGIMPL_INCLUDED__

