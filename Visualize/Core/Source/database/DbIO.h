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


#ifndef _DBFCTLR_MODULE_API_H_
#define _DBFCTLR_MODULE_API_H_

#include "RxModule.h"

#include "TD_PackPush.h"
#include "DbProxyEntity.h"
#include "DbFilerController.h"
#include "DbProxyObject.h"

/** \details
<group OdTvDb_Classes>

This class provides the implementation of the OdTvDbIOModule module.

Corresponding C++ library: TD_Db

\sa
<link CustomApplications.html, Creating Custom Applications>

OdRxModule, OdRxStaticModule, OdRxPseudoStaticModule, OdRxMacModule, OdRxUnixModule, OdRxWin32Module classes
*/
class OdTvDbIOModule : public OdRxModule {
protected:
  virtual void initApp();
  virtual void uninitApp();
public:
  // module virtual cross DLL API
  virtual OdTvDbFilerControllerPtr CreateInputController(OdStreamBuf* pFileBuff, bool bRecover);
  virtual void ReadFile(OdTvDbDatabase* pDb,
    OdStreamBuf* pFileBuff,
    bool bPartial,
    OdTvDbAuditInfo *pAuditInfo,
    const OdPassword& password,
    bool bAllowCPConversion);
  virtual void WriteFile(OdTvDbDatabase* pDb,
    OdStreamBuf* pFileBuff,
    OdDb::SaveType type,
    OdDb::DwgVersion ver,
    bool bSaveThumbnailImage,
    int dxfPrecision);

  virtual OdTvDbDate GetModificationTimeFromStream(OdStreamBuf* pFileBuff);

  virtual OdTvDbProxyObjectPtr ObjectToProxy(const OdTvDbObject& pObj, OdDb::DwgVersion dwgVer = OdDb::kDHL_CURRENT, OdDb::MaintReleaseVer nMaintVer = OdDb::kMRelease0);
  virtual OdTvDbProxyEntityPtr EntityToProxy(const OdTvDbEntity& pObj, OdDb::DwgVersion dwgVer = OdDb::kDHL_CURRENT, OdDb::MaintReleaseVer nMaintVer = OdDb::kMRelease0);
  virtual OdTvResBufPtr EntGet(const OdTvDbObject* pObj);
  virtual OdResult TurnToOriginalObject(OdTvDbObject* pProxyObj, OdTvDbFilerController* pFC);
  virtual void CreateGrData(const OdTvDbEntity* pEnt, OdBinaryData& data, OdDb::DwgVersion ver);
  virtual OdTvDbDxfFilerPtr createLSFileReadFiler(OdTvDbDatabase* pDb, OdStreamBuf* pOut);
  virtual OdTvDbDxfFilerPtr createLSFileWriteFiler(OdTvDbDatabase* pDb, OdStreamBuf* pOut);
  virtual OdTvDbDxfFilerPtr createMlineStyleFiler();
};

typedef OdSmartPtr<OdTvDbIOModule> OdTvDbIOModulePtr;


#include "TD_PackPop.h"

#endif // _DBFCTLR_MODULE_API_H_
