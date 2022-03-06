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

// OdDwgCopyFiler.h: interface for the OdTvDwgCopyFiler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ODDWGCOPYFILER_H__1333DE9F_5830_404F_8153_0FE30A74D35A__INCLUDED_)
#define AFX_ODDWGCOPYFILER_H__1333DE9F_5830_404F_8153_0FE30A74D35A__INCLUDED_


#include "CopyFiler.h"
#include "RxObjectImpl.h"
#include "DwgFiler/DwgStream.h"

class OdTvProxyStuff;

//#pragma MARKMESSAGE(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! implementation class OdTvDwgProxyFiler is exported )
class TOOLKIT_EXPORT OdTvDwgProxyFiler : public OdRxObjectImpl<OdTvDwgStream>
{
  OdTvDwgProxyFiler& operator = (OdTvDwgProxyFiler);
public:
  OdTvDwgProxyFiler(OdTvDbDatabase * pDb, const OdTvProxyStuff* pProxy)
    : m_pDb(pDb)
    , m_pProxy(pProxy)
    , m_idPos(0)
  {}

  void openR(const OdBitBinaryData* pBinData, const OdBitBinaryData* pStrData = 0);
	void openW(OdBitBinaryData* pBinData, OdBitBinaryData* pStrData = 0);

  const OdTypedIdsArray *getIds() const { return &m_ids; }
  // OdTvDwgStream overridden
  //
  void close();

  // OdTvDbFiler overridden
  //
  OdTvDbDatabase* database() const  { return m_pDb;}
  FilerType filerType() const;
  OdDb::DwgVersion dwgVersion(OdDb::MaintReleaseVer *pnMaintReleaseVer = NULL) const;

  // OdTvDbDwgFiler overridden
  //
  OdTvDbObjectId rdSoftOwnershipId();
  OdTvDbObjectId rdHardOwnershipId();
  OdTvDbObjectId rdHardPointerId();
  OdTvDbObjectId rdSoftPointerId();
  OdString     rdString();

  void wrSoftOwnershipId(const OdTvDbObjectId& id);
  void wrHardOwnershipId(const OdTvDbObjectId& id);
  void wrSoftPointerId(const OdTvDbObjectId& id);
  void wrHardPointerId(const OdTvDbObjectId& id);
  void wrString(const OdString& val);

  OdUInt64 getStringStreamSizeInBits() const;
  virtual bool isPersistentMode() const ODRX_OVERRIDE { return true; }
private:
  void rdObjectIdRef(OdTvDbObjectId& id, OdDb::ReferenceType* pRefType = NULL);

  OdTvDbDatabase*       m_pDb;
  const OdTvProxyStuff* m_pProxy;
  OdTypedIdsArray     m_ids;
  int                 m_idPos;
  OdTvDwgStreamPtr      m_pStrStream;
};


template< class TBase = OdTvCopyFilerBase<OdTvDbDwgFiler> >
class OdTvDbDwgCopyFiler : public OdCopyFilerImpl<TBase>
{
public:
  mutable OdTvDbDatabase* m_pDb;
public:
  inline OdTvDbDwgCopyFiler<TBase>() : m_pDb(0) { }
  inline OdTvDbDwgCopyFiler<TBase>(OdTvDbDatabase* pDb) : m_pDb(pDb) { }

  OD_TYPENAME2 OdTvDbDatabase* database() const { return m_pDb; }
  inline void setDatabaseRef(OdTvDbDatabase* pDb) { m_pDb = pDb; }

  OdTvDbFiler::FilerType filerType() const { return OdTvDbFiler::kCopyFiler; }
  OdDb::DwgVersion dwgVersion(OdDb::MaintReleaseVer* maint_ver) const
  {
    if(maint_ver)
      *maint_ver = OdDb::kMReleaseCurrent;
    return OdDb::kDHL_CURRENT;
  }
};

class OdTvDbDwgCopyFilerForClone : public OdTvDbDwgCopyFiler<>
{
public:
  inline OdTvDbDwgCopyFilerForClone() {}
  inline OdTvDbDwgCopyFilerForClone(OdTvDbDatabase* pDb) : OdTvDbDwgCopyFiler<>(pDb) { }

  OdTvDbObjectId rdSoftOwnershipId()
  {
    OdTvDbDwgCopyFiler<>::rdSoftOwnershipId();
    return OdTvDbObjectId(0);
  }

  OdTvDbObjectId rdHardOwnershipId()
  {
    OdTvDbDwgCopyFiler<>::rdHardOwnershipId();
    return OdTvDbObjectId(0);
  }
};

#endif // !defined(AFX_ODDWGCOPYFILER_H__1333DE9F_5830_404F_8153_0FE30A74D35A__INCLUDED_)
