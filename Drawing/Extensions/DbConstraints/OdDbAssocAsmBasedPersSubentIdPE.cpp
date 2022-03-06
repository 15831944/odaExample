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
#include "OdaCommon.h"
#include "DbEntity.h"
#include "DbPlaneSurface.h"
#include "OdDbAssocAsmBasedPersSubentIdPE.h"
#include "ModelerGeometry.h"
#include "DbAssocEdgePersSubentId.h"
#include "ShHistory/DbAssocPersSubentManager.h"
#include "DbImpCenterLineActionBody.h"
#include "DbImpCenterMarkActionBody.h"
#include "Br/BrBrep.h"
#include "Br/BrBrepFaceTraverser.h"
#include "Br/BrBrepEdgeTraverser.h"
#include "Br/BrBrepVertexTraverser.h"

ODRX_NO_CONS_DEFINE_MEMBERS(OdDbAssocAsmBasedPersSubentIdPE, OdDbAssocPersSubentIdPE);

OdResult OdDbAssocAsmBasedPersSubentIdPE::getTransientSubentIds(const OdDbEntity* pEntity,
  const OdDbAssocPersSubentId* pPerSubentId,
  OdArray<OdDbSubentId>& subents) const
{
  if (!isBrepEntity(pEntity))
    return eWrongObjectType;

  OdDbSubentId currentSubentId;

  const OdDbAssocAsmBasedEntityPersSubentIdPtr pBrepPerSubentId = OdDbAssocAsmBasedEntityPersSubentId::cast(pPerSubentId);
  if (!pBrepPerSubentId.isNull())
  {
    currentSubentId = pBrepPerSubentId->subentId(pEntity);
  }

  const OdDbAssocIndexPersSubentIdPtr pIndexSubentId = OdDbAssocIndexPersSubentId::cast(pPerSubentId);
  if (!pIndexSubentId.isNull())
  {
    currentSubentId = pIndexSubentId->subentId(pEntity);
  }

  subents.clear();
  OdDb::SubentType internalType = pPerSubentId->subentType(pEntity);
  unsigned int internalIdx = currentSubentId.index();
  if ((internalType == OdDb::kVertexSubentType || internalType == OdDb::kEdgeSubentType || internalType == OdDb::kFaceSubentType) && internalIdx >= 1)
  {
    subents.append(OdDbSubentId(internalType, internalIdx));
  }

  return subents.isEmpty() ? eInvalidInput : eOk;
}


OdResult OdDbAssocAsmBasedPersSubentIdPE::getEdgeSubentityGeometry(const OdDbEntity* pEntity,
  const OdDbSubentId& edgeSubentId,
  OdGeCurve3d*& pEdgeCurve)
{
  pEntity->assertReadEnabled();
  OdModelerGeometryPtr pModeler = getModelerGeometry(pEntity);

  if (pModeler.isNull())
    return eGeneralModelingFailure;

  OdResult res = eInvalidFaceVertexIndex;
  const OdDbDatabase* pDb = pEntity->database();
  OdDbObjectId objId = OdDbAssocPersSubentManager::getInstanceFromDatabase(pDb);
  OdDbAssocPersSubentManagerPtr pAssocPSManager = objId.openObject(/*OdDb::kForWrite*/);

  OdUInt32 idx = (unsigned int)edgeSubentId.index();
  if (idx >= 1 && !pAssocPSManager.isNull())// && isTypeEqual(pEntity, OdDbCircle::desc()))
  {
    OdArray<OdUInt32> indexesOfEdgeCalculation = pAssocPSManager->infoAcisDataIndexes(idx);

    if (indexesOfEdgeCalculation.length() > 0)
    {
      res = pModeler->getEdgeSubentityGeometry(indexesOfEdgeCalculation, pEdgeCurve);
    }
  }

  return res;
}

OdResult OdDbAssocAsmBasedPersSubentIdPE::addSubentitySpecialSettings(OdDbEntityPtr pEntity, const OdDbSubentId subentId, OdUInt32 idx, OdDbAssocActionBodyPtr pActionBody)
{
  const OdDbDatabase* pDb = pEntity->database();
  OdDbObjectId objId = OdDbAssocPersSubentManager::getInstanceFromDatabase(pDb);
  OdDbAssocPersSubentManagerPtr pAssocPSManager = objId.openObject(OdDb::kForWrite);

  OdModelerGeometryPtr pModeler = getModelerGeometry(pEntity);
  if (pModeler.isNull())
    return eGeneralModelingFailure;

  OdArray<OdUInt32> idsArray;

  //pSurf->assertWriteEnabled();//TODO Is it neccessary here? This case call out() and delete m_pAcisData
  AcisDataType addedDT = kUndefinedDataType;
  AcisDataTypeArrFirst addedDTFirst = kUndefinedDataTypeArrFirst;
  OdDbCenterLineActionBodyPtr pCenterLineActionBody = OdDbCenterLineActionBody::cast(pActionBody);
  OdDbCenterMarkActionBodyPtr pCenterMarkActionBody = OdDbCenterMarkActionBody::cast(pActionBody);

  if (!pCenterLineActionBody.isNull())
  {
    //if (pSurf->isKindOf(OdDbExtrudedSurface::desc())) // TODO Default value
    {
      addedDT = kExtrudeSurface_TopOrBottom_CLine;
    }

    if (pEntity->isKindOf(OdDbPlaneSurface::desc()))
    {
      addedDT = kPlaneSurface_CLine;
      addedDTFirst = kArrSolidExtrude_CLCM;
    }
    // TODO kExtrudeSurface_Side_CLine
  }

  if (!pCenterMarkActionBody.isNull())
  {
    addedDT = kSurfaceExtrude_CMark;
    addedDTFirst = kArrFirstSurfaceExtrude_CMark;
  }

  OdResult ret = pModeler->addSubentitySpecialSettings(addedDT, addedDTFirst, subentId, idsArray, idx);

  if (eOk != ret && eAlreadyInDb != ret)
    return ret;

  if ((eOk == ret || eAlreadyInDb == ret) && kUndefinedDataType != addedDT)
    pAssocPSManager->addSubentRWData(addedDT, addedDTFirst, idx, idsArray);

  //if (kUndefinedDataType == addedDT)
  //  ret = eIllegalEntityType;

  return ret;
}

OdResult OdDbAssocAsmBasedPersSubentIdPE::getAllSubentities(const OdDbEntity* pEntity,
  OdDb::SubentType subentType,
  OdArray<OdDbSubentId>& allSubentIds)
{
  OdModelerGeometryPtr modelerGeom = getModelerGeometry(pEntity);
  if (modelerGeom.isNull())
    return eInvalidInput;
  OdBrBrep brep;
  modelerGeom->brep(brep);
  int num = 0;
  if (subentType == OdDb::kFaceSubentType)
  {
    OdBrBrepFaceTraverser traverser;
    traverser.setBrep(brep);
    for (; !traverser.done(); traverser.next(), ++num) {}
  }
  else if (subentType == OdDb::kEdgeSubentType)
  {
    OdBrBrepEdgeTraverser traverser;
    traverser.setBrep(brep);
    for (; !traverser.done(); traverser.next(), ++num) {}
  }
  else if (subentType == OdDb::kVertexSubentType)
  {
    OdBrBrepVertexTraverser traverser;
    traverser.setBrep(brep);
    for (; !traverser.done(); traverser.next(), ++num) {}
  }
  else
  {
    return eWrongObjectType;
  }

  allSubentIds.reserve(num);
  for (int i = 1; i <= num; ++i)
  {
    allSubentIds.push_back(OdDbSubentId(subentType, OdGsMarker(i)));
  }
  return eOk;
}

bool OdDbAssocAsmBasedPersSubentIdPE::isBrepEntity(const OdDbEntity* pEntity) const
{
  if (OdDb3dSolid* pSolid = OdDb3dSolid::cast(pEntity))
    return true;
  if (OdDbRegion* pReg = OdDbRegion::cast(pEntity))
    return true;
  if (OdDbBody* pBody = OdDbBody::cast(pEntity))
    return true;
  if (OdDbSurface* pSrf = OdDbSurface::cast(pEntity))
    return true;
  return false;
}
