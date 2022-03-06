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
//#include "../Source/database/DbSystemInternals.h"
#include "DbEntity.h"
#include "Db3dSolid.h"
#include "OdDbAssoc3dSolidPersSubentIdPE.h"
#include <ModelerGeometry.h>
#include "DbAssocEdgePersSubentId.h"
#include "ShHistory/DbAssocPersSubentManager.h"
#include "DbImpCenterLineActionBody.h"
#include "DbImpCenterMarkActionBody.h"
#include "ShHistory/DbShHistory.h"
#include "DbEvalGraph.h"
#include "ShHistory/DbShPrimitive.h"
#include "ShHistory/DbShCylinder.h"
#include "ShHistory/DbShBox.h"

ODRX_NO_CONS_DEFINE_MEMBERS_ALTNAME(OdDbAssoc3dSolidPersSubentIdPE, OdDbAssocAsmBasedPersSubentIdPE, L"AcDbAssoc3dSolidPersSubentIdPE");

//OdDbAssocPersSubentIdPtr OdDbAssoc3dSolidPersSubentIdPE::createNewPersSubent(OdDbEntity* pEntity,
//  const class OdDbCompoundObjectId& compId,
//  const OdDbSubentId& subentId)
//{
//  OdDbAssocEdgePersSubentIdPtr res;
//  if (!isTypeEqual(pEntity, OdDbPolyline::desc()) || !checkSubentId(pEntity, subentId, OdDb::kEdgeSubentType))
//    res.attach((OdDbAssocEdgePersSubentId*)NULL);
//  else
//  {
//    OdDbPolylinePtr pPolyLine = OdDbPolyline::cast(pEntity);
//    int ptQty = pPolyLine->numVerts();
//    int maxIdentifier = 0;
//    for (int i = 0; i < ptQty; i++)
//    {
//      if (pPolyLine->getVertexIdentifierAt(i) > maxIdentifier)
//        maxIdentifier = pPolyLine->getVertexIdentifierAt(i);
//    }
//
//    int startVertexIdx = (int)subentId.index() - 1;
//    int endVertexIdx = startVertexIdx + 1;
//    if (endVertexIdx >= ptQty)
//      endVertexIdx = 0;
//
//    if (pPolyLine->getVertexIdentifierAt(startVertexIdx) == 0)
//    {
//      pPolyLine->setVertexIdentifierAt(startVertexIdx, ++maxIdentifier);
//    }
//
//    if (pPolyLine->getVertexIdentifierAt(endVertexIdx) == 0)
//    {
//      pPolyLine->setVertexIdentifierAt(endVertexIdx, ++maxIdentifier);
//    }
//
//    res = OdDbAssocEdgePersSubentId::createObject();
//    res->init(pPolyLine->getVertexIdentifierAt(startVertexIdx), pPolyLine->getVertexIdentifierAt(endVertexIdx));
//  }
//
//  return res;
//}
static OdDbObjectId FormatValue(OdResBufPtr rb, OdDbDatabase *pDb)
{
  OdDbObjectId s;
  switch (OdDxfCode::_getType(rb->restype()))
  {
  case OdDxfCode::ObjectId:
  case OdDxfCode::SoftPointerId:
  case OdDxfCode::HardPointerId:
  case OdDxfCode::SoftOwnershipId:
  case OdDxfCode::HardOwnershipId:
    s = rb->getObjectId(pDb);
    break;
  case OdDxfCode::Unknown: // to use control codes
    ODA_ASSERT(!L"Check the restype!");
  break;
  default:
    break;
  }
  return s;
}

static OdString FormatCode(OdResBufPtr rb)
{
  OdString s;
  s.format(L"%d", rb->restype());
  return s;
}

OdResult OdDbAssoc3dSolidPersSubentIdPE::get3DSolidHistoryObject(OdDb3dSolidPtr pEntity, OdDbObjectId &historyObjId)
{
  for (OdResBufPtr rb = oddbEntGet(pEntity->objectId()); !rb.isNull(); rb = rb->next())
  {
    OdString str = /*OdBagFiler::*/FormatCode(rb);

    if (!strcmp(str, "350"))
    {
      historyObjId = FormatValue(rb, pEntity->database());
      break;
    }
  }
  //OdDb3dSolidImpl* pSolidImpl = OdDb3dSolidImpl::getImpl(pEntity);

  //if (!pSolidImpl)
  //{
  //  return eNullEntityPointer;
  //}

  //historyObjId = pSolidImpl->m_idHistory;

  return eOk;
}

OdResult OdDbAssoc3dSolidPersSubentIdPE::addSubentitySpecialSettings(OdDbEntityPtr pEntity, const OdDbSubentId subentId, OdUInt32 idx, OdDbAssocActionBodyPtr pActionBody)
{
  const OdDbDatabase* pDb = pEntity->database();
  OdDbObjectId objId = OdDbAssocPersSubentManager::getInstanceFromDatabase(pDb);
  OdDbAssocPersSubentManagerPtr pAssocPSManager = objId.openObject( OdDb::kForWrite );

  OdArray<OdUInt32> idsArray;

  OdDb3dSolidPtr pSolid = OdDb3dSolid::cast(pEntity);

  if (pSolid.isNull())
    return eGeneralModelingFailure;

  OdModelerGeometryPtr pModeler = getModelerGeometry(pSolid);

  if (pModeler.isNull())
    return eGeneralModelingFailure;

  //pSolid->assertWriteEnabled(); //TODO Is it neccessary here? This case call out() and delete m_pAcisData

  AcisDataType addedDT = kUndefinedDataType;
  AcisDataTypeArrFirst addedDTFirst = kUndefinedDataTypeArrFirst;
  OdDbCenterLineActionBodyPtr pCenterLineActionBody = OdDbCenterLineActionBody::cast(pActionBody);
  OdDbCenterMarkActionBodyPtr pCenterMarkActionBody = OdDbCenterMarkActionBody::cast(pActionBody);
  OdDbObjectId historyObjId;

  get3DSolidHistoryObject(pEntity, historyObjId);
  
  OdDbShHistoryPtr pShHist = historyObjId.openObject();
  bool isBox = false;
  bool isCylinder = false;

  if (!pShHist.isNull())
  {
    OdDbObjectId graphObjId;
    pShHist->getGraph(graphObjId);
    OdDbEvalGraphPtr pEvalGraph = graphObjId.openObject();
    
    //OdDbShCone

    //  OdDbShExtrusion
    //  OdDbShLoft
    //  OdDbShPyramid
    //  OdDbShRevolve
    //  OdDbShSweep
    //  OdDbShTorus
    //  OdDbShWedge

    if (!pEvalGraph.isNull())
    {
      OdDbEvalNodeIdArray nodes;
      pEvalGraph->getAllNodes(nodes);

      if (nodes.length() > 0)
      {
        OdDbEvalExprPtr pEvalExpr = pEvalGraph->getNode(1, OdDb::kForRead);
        
        if (!pEvalExpr.isNull())
        {
          OdDbShPrimitivePtr pPrimitive = OdDbShPrimitive::cast(pEvalExpr);;

          if (!pPrimitive.isNull())
          {
            isBox = pPrimitive->isKindOf(OdDbShBox::desc()); // TODO Default value;
            isCylinder = pPrimitive->isKindOf(OdDbShCylinder::desc()); // TODO Default value;
          }
        }
      }
    }
  }

  if (!pCenterLineActionBody.isNull())
  {
    addedDT = kSolidBox_CLine;//TODO Is it for Box only?
    addedDTFirst = kArrSolidBox_CLine;
  }

  if (!pCenterMarkActionBody.isNull())
  {
    addedDT = kSolidExtrude_CLCM;//TODO Is it for Box only?
    addedDTFirst = kArrSolidExtrude_CLCM;

    if (isCylinder)
    {
      addedDT = kSolidExtrude_CMark;
      addedDTFirst = kArrFirstSolidExtrude_CMark;
    }
  }

  OdResult ret = pModeler->addSubentitySpecialSettings(addedDT, addedDTFirst, subentId, idsArray, idx);

  if (eOk != ret && eAlreadyInDb != ret)
    return ret;

  if ((eOk == ret || eAlreadyInDb == ret) && kUndefinedDataType != addedDT)
    pAssocPSManager->addSubentRWData(addedDT, addedDTFirst, idx, idsArray);

  return eOk;
}
