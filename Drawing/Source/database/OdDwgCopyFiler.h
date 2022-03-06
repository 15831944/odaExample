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

// OdDwgCopyFiler.h: interface for the OdDwgCopyFiler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ODDWGCOPYFILER_H__1333DE9F_5830_404F_8153_0FE30A74D35A__INCLUDED_)
#define AFX_ODDWGCOPYFILER_H__1333DE9F_5830_404F_8153_0FE30A74D35A__INCLUDED_


#include "CopyFiler.h"
#include "RxObjectImpl.h"
#include "DwgFiler/DwgStream.h"

class OdProxyStuff;

//#pragma MARKMESSAGE(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! implementation class OdDwgProxyFiler is exported )
class TOOLKIT_EXPORT OdDwgProxyFiler : public OdRxObjectImpl<OdDwgStream>
{
  OdDwgProxyFiler& operator = (OdDwgProxyFiler);
public:
  OdDwgProxyFiler(OdDbDatabase * pDb, const OdProxyStuff* pProxy)
    : m_pDb(pDb)
    , m_pProxy(pProxy)
    , m_idPos(0)
  {}

  void openR(const OdBitBinaryData* pBinData, const OdBitBinaryData* pStrData = 0);
	void openW(OdBitBinaryData* pBinData, OdBitBinaryData* pStrData = 0);

  const OdTypedIdsArray *getIds() const { return &m_ids; }
  // OdDwgStream overridden
  //
  void close();

  // OdDbFiler overridden
  //
  OdDbDatabase* database() const  { return m_pDb;}
  FilerType filerType() const;
  OdDb::DwgVersion dwgVersion(OdDb::MaintReleaseVer *pnMaintReleaseVer = NULL) const;

  // OdDbDwgFiler overridden
  //
  OdDbObjectId rdSoftOwnershipId();
  OdDbObjectId rdHardOwnershipId();
  OdDbObjectId rdHardPointerId();
  OdDbObjectId rdSoftPointerId();
  OdString     rdString();

  void wrSoftOwnershipId(const OdDbObjectId& id);
  void wrHardOwnershipId(const OdDbObjectId& id);
  void wrSoftPointerId(const OdDbObjectId& id);
  void wrHardPointerId(const OdDbObjectId& id);
  void wrString(const OdString& val);

  OdUInt64 getStringStreamSizeInBits() const;
  virtual bool isPersistentMode() const ODRX_OVERRIDE { return true; }
private:
  void rdObjectIdRef(OdDbObjectId& id, OdDb::ReferenceType* pRefType = NULL);

  OdDbDatabase*       m_pDb;
  const OdProxyStuff* m_pProxy;
  OdTypedIdsArray     m_ids;
  int                 m_idPos;
  OdDwgStreamPtr      m_pStrStream;
};


template< class TBase = OdCopyFilerBase<OdDbDwgFiler> >
class OdDbDwgCopyFiler : public OdCopyFilerImpl<TBase>
{
public:
  mutable OdDbDatabase* m_pDb;
public:
  inline OdDbDwgCopyFiler<TBase>() : m_pDb(0) { }
  inline OdDbDwgCopyFiler<TBase>(OdDbDatabase* pDb) : m_pDb(pDb) { }

  OD_TYPENAME2 OdDbDatabase* database() const { return m_pDb; }
  inline void setDatabaseRef(OdDbDatabase* pDb) { m_pDb = pDb; }

  OdDbFiler::FilerType filerType() const { return OdDbFiler::kCopyFiler; }
  OdDb::DwgVersion dwgVersion(OdDb::MaintReleaseVer* maint_ver) const
  {
    if(maint_ver)
      *maint_ver = OdDb::kMReleaseCurrent;
    return OdDb::kDHL_CURRENT;
  }
};

class OdDbDwgCopyFilerForClone : public OdDbDwgCopyFiler<>
{
public:
  inline OdDbDwgCopyFilerForClone() {}
  inline OdDbDwgCopyFilerForClone(OdDbDatabase* pDb) : OdDbDwgCopyFiler<>(pDb) { }

  OdDbObjectId rdSoftOwnershipId()
  {
    OdDbDwgCopyFiler<>::rdSoftOwnershipId();
    return OdDbObjectId(0);
  }

  OdDbObjectId rdHardOwnershipId()
  {
    OdDbDwgCopyFiler<>::rdHardOwnershipId();
    return OdDbObjectId(0);
  }
};

#endif // !defined(AFX_ODDWGCOPYFILER_H__1333DE9F_5830_404F_8153_0FE30A74D35A__INCLUDED_)
