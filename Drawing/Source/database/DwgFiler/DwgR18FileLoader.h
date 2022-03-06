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

// DwgFileController.h: interface for the OdDwgFileLoader class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _OD_DWGR18FILELOADER_H_INCLUDED_
#define _OD_DWGR18FILELOADER_H_INCLUDED_

#include "DwgFileLoader.h"
#include "DbSecurity.h"
#include "MemoryStream.h"
#include "DwgR18Controller.h"

class DBIO_EXPORT OdDwgR18FileLoader : public OdDwgFileLoader,
                           public OdDwgR18FileController
{
public:
  ODRX_DECLARE_MEMBERS(OdDwgR18FileLoader);
  OdDwgR18FileLoader();

  // OdDwgFileLoader overridden
  void getVbaProjectData(OdUInt32 size, OdBinaryData& binaryData);

  // DbFilerController overridden 
  OdDbDatabasePtr loadDbHeader(OdDbHostAppServices* apps);
  virtual void setPassword(const OdPassword& pass){OdDwgR18FileController::setPassword(pass);}
  OdDbObjectPtr loadObject(OdUInt64 offset);

  void verifyExistingSignature(OdCryptoServices::OdSignatureVerificationResult& verificationResult, 
    OdSignatureDescription& signatureDesc);
  OdDbDate getStreamModTimeFromSummary();

protected:
  OdStreamBufPtr m_pObjectData;

  // OdDwgFileLoader overridden
  void loadFileHeader();

  // Load R18 system data
  void loadMetadata();
  void loadHeaderPage();
  void loadPagesMap();
  void loadSectionsMap();
  OdStreamBufPtr loadSysPage(OdUInt32 secType, OdInt64 offset);

  virtual void loadAppInfo();
  virtual void loadAppInfoHistory();
  virtual void loadRevHistory();

  // AC27 support
  // Load data sections present in dwg files of version >=R27 
  void loadDsPrototype();

// ODA_MT_DBIO_BEGIN
public:
  class R18MTContext : public MTContext
  {
  public:
    OdArray<OdBinaryData> m_buffs;
    OdArray<OdDwgR18Compressor> m_compressors;
  };
protected:
  // OdDwgFileLoader overridden
  OdApcAtomPtr beginMTLoading(int threadsCount, OdDbObjectIterator* pObjs = 0, OdMTLoadReactor* pInterruptFlag = 0) ODRX_OVERRIDE;
  OdResult loadObject(OdDbObjectPtr& pObj, const OdRxObject* pMTResolver, int threadId);
// ODA_MT_DBIO_END
};

#endif // _OD_DWGR18FILELOADER_H_INCLUDED_
