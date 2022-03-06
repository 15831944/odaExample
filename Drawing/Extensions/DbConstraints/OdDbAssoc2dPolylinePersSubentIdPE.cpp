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
#include "Db2dPolyline.h"
#include "OdDbAssoc2dPolylinePersSubentIdPE.h"

ODRX_NO_CONS_DEFINE_MEMBERS_ALTNAME(OdDbAssoc2dPolylinePersSubentIdPE, OdDbAssocCurvePersSubentIdPE, L"AcDbAssoc2dPolylinePersSubentIdPE");


OdResult OdDbAssoc2dPolylinePersSubentIdPE::getAllSubentities(const OdDbEntity* pEntity,
  OdDb::SubentType subentType,
  OdArray<OdDbSubentId>& allSubentIds)
{
  if (!isTypeEqual(pEntity, OdDb2dPolyline::desc()))
    return eBadObjType;

  OdDb2dPolylinePtr pPolyline = OdDb2dPolyline::cast(pEntity);

  if (subentType == OdDb::kEdgeSubentType)
  {
    OdDbObjectIteratorPtr iterator = pPolyline->vertexIterator();
    int i = 1;
    for (iterator->step(); !iterator->done(); iterator->step(), ++i)
    {
      OdDb2dVertexPtr pVert = iterator->entity();
      if (pVert->vertexType() == OdDb::k2dSplineCtlVertex)
      {
        continue;
      }
      allSubentIds.append(OdDbSubentId(OdDb::kEdgeSubentType, i));
    }
    if (pPolyline->isClosed())
      allSubentIds.append(OdDbSubentId(OdDb::kEdgeSubentType, i));

    return eOk;
  }
  else if (subentType == OdDb::kVertexSubentType)
  {
    OdDbObjectIteratorPtr iterator = pPolyline->vertexIterator();
    for (int i = 1; !iterator->done(); ++i)
    {
      OdDb2dVertexPtr pVert = iterator->entity();
      iterator->step();
      if (pVert->vertexType() == OdDb::k2dSplineCtlVertex)
      {
        continue;
      }
      allSubentIds.append(OdDbSubentId(OdDb::kVertexSubentType, i));
      if (OdNonZero(pVert->bulge()))
        allSubentIds.append(OdDbSubentId(OdDb::kVertexSubentType, kCenterPLinePrefix + i));
      if (!iterator->done() || pPolyline->isClosed())
        allSubentIds.append(OdDbSubentId(OdDb::kVertexSubentType, kMiddlePLinePrefix + i));
    }
    if (pPolyline->isClosed())
      allSubentIds.append(OdDbSubentId(OdDb::kVertexSubentType, 1));

    return eOk;
  }
  else if (subentType == OdDb::kFaceSubentType)
    return eOk;
  else
    return eBadObjType;
}

void OdDbAssoc2dPolylinePersSubentIdPE::fillStartVertexSubentId(const OdDbEntity* pEntity,
  const OdDbSubentId& edgeSubentId,
  OdDbSubentId& startVertexSubentId)
{
  OdDbAssocCurvePersSubentIdPE::fillStartVertexSubentId(pEntity, edgeSubentId, startVertexSubentId);
  startVertexSubentId.setIndex(kStart);
}

void OdDbAssoc2dPolylinePersSubentIdPE::fillEndVertexSubentId(const OdDbEntity* pEntity,
  const OdDbSubentId& edgeSubentId,
  OdDbSubentId& endVertexSubentId)
{
  OdDbAssocCurvePersSubentIdPE::fillEndVertexSubentId(pEntity, edgeSubentId, endVertexSubentId);
  endVertexSubentId.setIndex(kEnd);
}
