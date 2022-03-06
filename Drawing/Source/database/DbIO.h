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
<group OdDb_Classes>

This class provides the implementation of the OdDbIOModule module.

Corresponding C++ library: TD_Db

\sa
<link CustomApplications, Creating Custom Applications>

OdRxModule, OdRxStaticModule, OdRxPseudoStaticModule, OdRxMacModule, OdRxUnixModule, OdRxWin32Module classes
*/
class OdDbIOModule : public OdRxModule {
protected:
  virtual void initApp();
  virtual void uninitApp();
public:
  // module virtual cross DLL API
  virtual OdDbFilerControllerPtr CreateInputController(OdStreamBuf* pFileBuff, bool bRecover);
  virtual void ReadFile(OdDbDatabase* pDb,
    OdStreamBuf* pFileBuff,
    bool bPartial,
    OdDbAuditInfo *pAuditInfo,
    const OdPassword& password,
    bool bAllowCPConversion);
  virtual void WriteFile(OdDbDatabase* pDb,
    OdStreamBuf* pFileBuff,
    OdDb::SaveType type,
    OdDb::DwgVersion ver,
    bool bSaveThumbnailImage,
    int dxfPrecision);

  virtual OdDbDate GetModificationTimeFromStream(OdStreamBuf* pFileBuff);

  virtual OdDbProxyObjectPtr ObjectToProxy(const OdDbObject& pObj, OdDb::DwgVersion dwgVer = OdDb::kDHL_CURRENT, OdDb::MaintReleaseVer nMaintVer = OdDb::kMRelease0);
  virtual OdDbProxyEntityPtr EntityToProxy(const OdDbEntity& pObj, OdDb::DwgVersion dwgVer = OdDb::kDHL_CURRENT, OdDb::MaintReleaseVer nMaintVer = OdDb::kMRelease0);
  virtual OdResBufPtr EntGet(const OdDbObject* pObj);
  virtual OdResult TurnToOriginalObject(OdDbObject* pProxyObj, OdDbFilerController* pFC);
  virtual void CreateGrData(const OdDbEntity* pEnt, OdBinaryData& data, OdDb::DwgVersion ver);
  virtual OdDbDxfFilerPtr createLSFileReadFiler(OdDbDatabase* pDb, OdStreamBuf* pOut);
  virtual OdDbDxfFilerPtr createLSFileWriteFiler(OdDbDatabase* pDb, OdStreamBuf* pOut);
  virtual OdDbDxfFilerPtr createMlineStyleFiler();
};

typedef OdSmartPtr<OdDbIOModule> OdDbIOModulePtr;


#include "TD_PackPop.h"

#endif // _DBFCTLR_MODULE_API_H_
