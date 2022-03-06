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

#ifndef _DBFULL_MODULE_API_H_
#define _DBFULL_MODULE_API_H_

#include "TD_PackPush.h"

#include "RxModule.h"
#include "DbField.h"

class OdTvDbEntity;
class OdTvDbLine;
class OdTvDbBlockReference;
class OdTvDbViewport;

class OdTvDbEntitiesModule : public OdRxModule {
  void DwgClassMap_init();
  void DwgClassMap_uninit();
protected:
  virtual void initApp();
  virtual void uninitApp();
public:
  virtual void PrepareHatchFromBlkRef(OdDb::SaveType format, OdTvResBuf* pXdata, OdTvDbBlockReference* pBlkRef);
  virtual void AnnotativeObject_composeBlockReference(OdTvDbObject *pObj);
  virtual void VerifyDefMLeaderStyle(OdTvDbDatabase* pDb, OdTvDbAuditInfo* pAuditInfo);
  virtual OdTvDbObjectId CreateArrowHead(OdTvDbDatabase* db, const OdChar* name);
  virtual OdResult Explode(const OdTvDbEntity* pEnt, OdRxObjectPtrArray& entitySet);
  virtual OdResult ExplodeBlockRefGeometry(const OdTvDbBlockReference* pRef, OdRxObjectPtrArray& entitySet);
  virtual OdResult ExplodeGeometry(const OdTvDbEntity* ent, OdRxObjectPtrArray& entitySet);
  virtual OdResult ExplodeMText(const OdTvDbEntity* mtext, OdRxObjectPtrArray& entitySet);
  virtual void ExplodeAsR12(const OdTvDbEntity* pEnt, const OdGeDoubleArray& deviations, OdRxObjectPtrArray& entitySet);
  virtual OdSmartPtr<OdGiWorldDraw> CreateDrawObjectForExplode();
  virtual OdSmartPtr<OdGiWorldDraw> CreateDrawObjectForExplodeViewportGeometry();
  virtual OdGeMatrix3d MsWcsToPsWcs(const OdTvDbViewport* pVp);
  virtual void VerifyDefTableStyle(OdTvDbDatabase* pDb);
  virtual void AuditDatabase(OdTvDbDatabase* pDb, OdTvDbAuditInfo* pAuditInfo);
  virtual OdTvDbAuditInfo* CreateAuditInfo();
  virtual OdResult GenerateClipBoundaryFromPline(
    const OdTvDbObjectId& plId, OdGePoint2dArray& clipBoundary,
    OdGeMatrix3d invTrans, OdGePoint2dArray clipBox);
  virtual OdResult getGeometry(OdTvDbEntity* ent, OdGeCurve3d *& result);
  virtual OdSmartPtr<OdTvDbLine> createDbLine(const OdGePoint3d& startPoint, const OdGePoint3d& endPoint);
  virtual OdResult evaluateFields(OdTvDbDatabase* pDb,
    int nContext,
    const OdTvDbObjectIdArray* objIds = 0,
    const OdTvDbObjectIdArray* pFieldsToEvaluate = 0,
    const OdString& pszEvaluatorId = OdString(),
    OdFd::EvalFields nEvalFlag = OdFd::kEvalRecursive,
    int* pNumFound = 0,
    int* pNumEvaluated = 0);
};

typedef OdSmartPtr<OdTvDbEntitiesModule> OdTvDbEntitiesModulePtr;


#include "TD_PackPop.h"

#endif // _DBFCTLR_MODULE_API_H_
