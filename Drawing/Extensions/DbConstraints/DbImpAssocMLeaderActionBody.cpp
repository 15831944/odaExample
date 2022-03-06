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
#include "NextCodeDefs.h"
#include "DbAssocArrayModifyActionBody.h"
#include "DbBlockReference.h"
#include "DbBlockTableRecord.h"
#include "DbBlockTable.h"
#include "DbAssocDependency.h"
#include "DbAssocGeomDependency.h"
#include "DbLinetypeTable.h"
#include "DbImpAssocMLeaderActionBody.h"
#include "DbImpAssocRotatedDimActionBody.h"
#include "DbObjectId.h"
#include "DbAssocNetwork.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OdDbImpAssocMLeaderActionBody::OdDbImpAssocMLeaderActionBody()
{
  // CORE-14828
  m_version = 0;
  OdUInt32 numDeps = 1;
  m_assocDependencyIndexes.resize(numDeps);
  m_assocDependencyIds.resize(numDeps);
  m_assocDependencyIndexes[0] = 0;
  m_assocDependencyIds[0] = OdDbObjectId();

//  m_ActionBodyType = kMleader;
  m_paramBasedActionBody = new OdDbImpAssocParamBasedActionBody(true);
}

OdDbImpAssocMLeaderActionBody::~OdDbImpAssocMLeaderActionBody()
{
}

OdResult OdDbImpAssocMLeaderActionBody::dwgInFields(OdDbDwgFiler* pFiler)
{
  OdResult res = OdDbImpAssocAnnotationActionBody::dwgInFields(pFiler);

  if (res != eOk)
    return res;

  m_version = pFiler->rdInt32();
  ODA_ASSERT_ONCE_X(MDSO, !m_version);
  // CORE-14828
  OdUInt32 numDeps = pFiler->rdInt32(); // 1 or 3
  ODA_ASSERT_ONCE_X(MDSO, numDeps);
  m_assocDependencyIndexes.resize(numDeps);
  m_assocDependencyIds.resize(numDeps);
  for (OdUInt32 idx = 0; idx < numDeps; idx++)
  {
    OdUInt32& index = m_assocDependencyIndexes[idx]; index = 0;
    index = pFiler->rdInt32(); // 0 1
    ODA_ASSERT_ONCE_X(MDSO,    (numDeps > 1 && index == (idx + 1))
                            || (numDeps == 1 && !index));

    OdDbObjectId& id = m_assocDependencyIds[idx]; id = OdDbObjectId();
    id = pFiler->rdSoftPointerId();
    ODA_ASSERT_ONCE_X(MDSO,    (idx < (numDeps - 1) && !id.isNull())
                            || (!idx && numDeps == 1 && !id.isNull()) // DimensionsToCMandPolyline.dwg of DbAssocDimensionTest
                            || (idx == (numDeps - 1) && id.isNull()));
  }

  return res;
}

void OdDbImpAssocMLeaderActionBody::dwgOutFields(OdDbDwgFiler* pFiler) const
{
  OdDbImpAssocAnnotationActionBody::dwgOutFields(pFiler);
  //m_paramBasedActionBody->dwgOutFields(pFiler);

  ODA_ASSERT_ONCE_X(MDSO, !m_version);
  pFiler->wrInt32(m_version);
  // CORE-14828
  OdUInt32 numDeps = m_assocDependencyIndexes.size(); // 1 or 3
  ODA_ASSERT_ONCE_X(MDSO, numDeps && numDeps == m_assocDependencyIds.size());
  pFiler->wrInt32(numDeps);
  for (OdUInt32 idx = 0; idx < numDeps; idx++)
  {
    const OdUInt32& index = m_assocDependencyIndexes[idx];
    ODA_ASSERT_ONCE_X(MDSO,    (numDeps > 1 && index == (idx + 1))
                            || (numDeps == 1 && !index));
    pFiler->wrInt32(index); // 0 1

    const OdDbObjectId& id = m_assocDependencyIds[idx];
    ODA_ASSERT_ONCE_X(MDSO,    (idx < (numDeps - 1) && !id.isNull())
                            || (idx == (numDeps - 1) && id.isNull()));
    pFiler->wrSoftPointerId(id);
  }
}

OdResult OdDbImpAssocMLeaderActionBody::dxfInFields(OdDbDxfFiler* pFiler)
{
  OdResult res = OdDbImpAssocAnnotationActionBody::dxfInFields(pFiler);

  if (res != eOk)
    return res;

  if (!pFiler->atSubclassData(OdDbAssocMLeaderActionBody::desc()->dxfName()))
  {
    ODA_FAIL_ONCE();
    return eMakeMeProxy;
  }

  NEXT_CODE(90);
  m_version = pFiler->rdUInt32(); // 0
  ODA_ASSERT_ONCE_X(MDSO, !m_version);
  // CORE-14828
  NEXT_CODE(90);
  OdUInt32 numDeps = pFiler->rdUInt32(); // 1 or 3
  ODA_ASSERT_ONCE_X(MDSO, numDeps);
  m_assocDependencyIndexes.resize(numDeps);
  m_assocDependencyIds.resize(numDeps);
  for (OdUInt32 idx = 0; idx < numDeps; idx++)
  {
    OdUInt32& index = m_assocDependencyIndexes[idx]; index = 0;
    NEXT_CODE(90);
    index = pFiler->rdUInt32(); // 0 1
    ODA_ASSERT_ONCE_X(MDSO,    (numDeps > 1 && index == (idx + 1))
                            || (numDeps == 1 && !index));

    OdDbObjectId& id = m_assocDependencyIds[idx]; id = OdDbObjectId();
    NEXT_CODE(330);
    id = pFiler->rdObjectId();
    ODA_ASSERT_ONCE_X(MDSO,    (idx < (numDeps - 1) && !id.isNull())
                            || (idx == (numDeps - 1) && id.isNull()));
  }

  return eOk;
}

void OdDbImpAssocMLeaderActionBody::dxfOutFields(OdDbDxfFiler* pFiler) const
{
  OdDbImpAssocAnnotationActionBody::dxfOutFields(pFiler);

  pFiler->wrSubclassMarker(OdDbAssocMLeaderActionBody::desc()->dxfName());

  ODA_ASSERT_ONCE_X(MDSO, !m_version);
  pFiler->wrUInt32(90, m_version);
  // CORE-14828
  OdUInt32 numDeps = m_assocDependencyIndexes.size(); // 1 or 3
  ODA_ASSERT_ONCE_X(MDSO, numDeps && numDeps == m_assocDependencyIds.size());
  pFiler->wrUInt32(90, numDeps);
  for (OdUInt32 idx = 0; idx < numDeps; idx++)
  {
    const OdUInt32& index = m_assocDependencyIndexes[idx]; // 0 1
    ODA_ASSERT_ONCE_X(MDSO,    (numDeps > 1 && index == (idx + 1))
                            || (numDeps == 1 && !index));
    pFiler->wrUInt32(90, index);

    const OdDbObjectId& id = m_assocDependencyIds[idx];
    ODA_ASSERT_ONCE_X(MDSO,    (idx < (numDeps - 1) && !id.isNull())
                            || (idx == (numDeps - 1) && id.isNull()));
    pFiler->wrObjectId(330, id);
  }
}

//void OdDbImpAssocMLeaderActionBody::composeForLoad(OdDbObject *pObject,
//  OdDb::SaveType format,
//  OdDb::DwgVersion version,
//  OdDbAuditInfo* pAuditInfo)
//{
//  OdDbAssocRotatedDimActionBody *Body = static_cast<OdDbAssocRotatedDimActionBody *>(pObject);
//  //m_matrix = OdDbBlockReference::cast(getArrayEntity(Body->parentAction()).safeOpenObject())->blockTransform();
//}


void OdDbImpAssocMLeaderActionBody::evaluateOverride(OdDbObjectId parentActionId)
{
  OdDbAssocActionPtr pAction = OdDbAssocAction::cast(parentActionId.openObject(OdDb::kForWrite));
  OdDbEntityPtr bEntRef = checkAccompanying(parentActionId, pAction);

  if (bEntRef.isNull())
    return;

  OdDbMLeaderPtr objDim = OdDbMLeader::cast(bEntRef);

  if (objDim.isNull())
    return;

  int const pointNum = 1;
  OdGePoint3d ptPoint[pointNum];
  OdGePoint3d ptDimPoint[pointNum];
  ODA_ASSERT(pAction->ownedParams().length() == pointNum);
  OdResult res = objDim->getFirstVertex(0, ptDimPoint[0]);

  if (res == eOk)
  {
    OdResult res = evaluateOverrideAssocDim(parentActionId, ptPoint, ptDimPoint, pointNum);

    if (!objDim.isNull() && res == eOk)
    {
      objDim->setFirstVertex(0, ptPoint[0]);
      return;
    }
  }

  ODA_FAIL_ONCE();
  return;
}

OdResult OdDbImpAssocMLeaderActionBody::createInstance(
  const OdDbFullSubentPathArray &entPathArray,
	const OdDbObjectId bodyId,
	OdGePoint3dArray &ptsSelected,
	const OdString mText,
	OdDbObjectId& actionBodyId)
{
  OdResult res = eOk;
  OdDbDatabase *pDb = NULL;
  OdDbObjectIdArray pathArray = entPathArray[0].objectIds();

  if (pathArray.length() < 1)
    return eInvalidInput;

  OdDbFullSubentPath pathDep0(pathArray, entPathArray[0].subentId());

  if ( bodyId.isNull() )
    return eInvalidInput;

  OdDbObjectPtr ptObj1;

  OdDbSmartCenterActionBodyPtr smartObj1;
  if (!bodyId.isNull())
  {
    ptObj1 = bodyId.openObject();
    smartObj1 = OdDbSmartCenterActionBody::cast(ptObj1);
  }

  if ( smartObj1.isNull() )
    return eInvalidInput;

  OdDbObjectId ownerBTRId;

  if (!bodyId.isNull())
  {
    pDb = bodyId.database();
    ownerBTRId = bodyId.openObject()->ownerId();

    if (!smartObj1.isNull())
    {
      ownerBTRId = ownerBTRId.openObject()->ownerId();
      ownerBTRId = ownerBTRId.openObject()->ownerId();
      ownerBTRId = ownerBTRId.openObject()->ownerId();
      ownerBTRId = ownerBTRId.openObject()->ownerId();
    }
  }

  OdDbBlockTableRecordPtr pOwnerSpace = ownerBTRId.safeOpenObject(OdDb::kForWrite);
  OdDbObjectId networkId = OdDbAssocNetwork::getInstanceFromObject(pOwnerSpace->objectId(), true);

  //create action and action body
  //BEGIN
  OdString pClassName = OD_T("AcDbAssocMLeaderActionBody");
  OdRxClass* pClass;
  pClass = (OdRxClass*)odrxClassDictionary()->getAt(pClassName).get();

  OdDbObjectId actionId;

  if (eOk != createActionAndActionBodyAndPostToDatabase(pClass, networkId, actionId, actionBodyId))
  {
    return eInvalidInput;
  }

  OdDbAssocAnnotationActionBodyPtr pActionBody =
    OdDbAssocActionBody::cast(actionBodyId.openObject(OdDb::kForWrite));

  ODA_ASSERT(!pActionBody.isNull());

  OdDbAssocActionPtr pAction = OdDbAssocAction::cast(actionId.openObject(OdDb::kForWrite));
  pAction->setActionBody(actionBodyId);

  /**********************************************************************/
  /* Create an rotated dimension and dimension the ends of the line     */
  /**********************************************************************/
  pClassName = OD_T("AcDbMLeader");
  pClass = (OdRxClass*)odrxClassDictionary()->getAt(pClassName).get();
  OdDbMLeaderPtr pDimension = OdDbMLeader::cast(pClass->create());
  /**********************************************************************/
  /* Add the DimStyle                                                   */
  /**********************************************************************/
  //OdDbObjectId odaDimStyleId = pDb->getDimStyleStandardId();
  //OdDbObjectId spaceId = ExCommandsUtils::activeBlockTableRecord(pDb);
  //OdDbBlockTableRecordPtr pSpace = spaceId.safeOpenObject(OdDb::kForWrite);
  if (!pDimension.isNull())
  {
    int llIndex;
    pDimension->setDatabaseDefaults(pDb);
    pOwnerSpace->appendOdDbEntity(pDimension);

    OdDbMTextPtr pMText = OdDbMText::createObject();
    pMText->setDatabaseDefaults(pDb);
    pDimension->setEnableFrameText(true);
    pMText->setContents(mText);
    pMText->setLocation(ptsSelected[1]);

    pDimension->setMText(pMText);
    pDimension->addLeaderLine(ptsSelected[0], llIndex);
  }

  OdDbObjectId anchorId;

  PointPositionOnBlockLine isStartPoint1;

  OdDbAssocGeomDependencyPtr pGeomDependency1, pGeomDependency2, pGeomDependency3, pGeomDependency4;
  if (!bodyId.isNull())
  {
    CreateGeomDependencies(pathDep0, actionId, bodyId, pGeomDependency1, pGeomDependency2, isStartPoint1);
  }

  ////array block reference
  OdDbObjectId snapParamID1;
  OdDbAssocDependencyPtr pDependency = OdDbAssocDependency::createObject();
  pDb->addOdDbObject(pDependency);
  pDependency->setIsReadDependency(true);
  pDependency->setIsWriteDependency(true);

  OdDbCompoundObjectId compoundObjectId;
  compoundObjectId.set(pDimension->objectId());
  pDependency->attachToObject(compoundObjectId);
  pAction->addDependency(pDependency->objectId(), true);
  pActionBody->setAssocDependencyID(pDependency->objectId());

  if (!bodyId.isNull())
  {
    snapParamID1 = createOdDbAssocOSnapPointRefActionParam(actionId, bodyId, ptsSelected[0], pGeomDependency1, pGeomDependency2, anchorId, isStartPoint1, 0);
    pActionBody->setActionParamID1(snapParamID1);
  }

  return res;
}
