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
#include "DbRevolvedSurface.h"
#include "DbAssocRevolvedSurfaceActionBody.h"
#include "DbImpAssocRevolvedSurfaceActionBody.h"
//////////////////////////////////////////////////////////////////////////

OdDbImpAssocRevolvedSurfaceActionBody::OdDbImpAssocRevolvedSurfaceActionBody()
{
  m_unknownInt32 = 0;
}

OdDbImpAssocRevolvedSurfaceActionBody::~OdDbImpAssocRevolvedSurfaceActionBody()
{
}

OdResult OdDbImpAssocRevolvedSurfaceActionBody::dwgInFields(OdDbDwgFiler* pFiler)
{
  OdResult res = OdDbImpAssocPathBasedSurfaceActionBody::dwgInFields(pFiler);

  if (res != eOk)
    return res;

  m_unknownInt32 = pFiler->rdInt32();  // 0
  m_undefinedBoolRevolved = pFiler->rdBool();

  return res;
}

void OdDbImpAssocRevolvedSurfaceActionBody::dwgOutFields(OdDbDwgFiler* pFiler) const
{
  OdDbImpAssocPathBasedSurfaceActionBody::dwgOutFields(pFiler);
  pFiler->wrInt32(m_unknownInt32);
  pFiler->wrBool(m_undefinedBoolRevolved);
}

OdResult OdDbImpAssocRevolvedSurfaceActionBody::dxfInFields(OdDbDxfFiler* pFiler)
{
  OdResult res = OdDbImpAssocPathBasedSurfaceActionBody::dxfInFields(pFiler);

  if (res != eOk)
    return res;

  if (!pFiler->atSubclassData(OdDbAssocRevolvedSurfaceActionBody::desc()->name()))
  {
    ODA_FAIL_ONCE();
    return eMakeMeProxy;
  }

  NEXT_CODE(90);
  m_unknownInt32 = pFiler->rdUInt32();
  NEXT_CODE(290);
  m_undefinedBoolRevolved = pFiler->rdBool();

  return eOk;
}

void OdDbImpAssocRevolvedSurfaceActionBody::dxfOutFields(OdDbDxfFiler* pFiler) const
{
  OdDbImpAssocPathBasedSurfaceActionBody::dxfOutFields(pFiler);

  pFiler->wrSubclassMarker(OdDbAssocRevolvedSurfaceActionBody::desc()->name());
  pFiler->wrUInt32(90, m_unknownInt32);
  pFiler->wrBool(290, m_undefinedBoolRevolved);
}

void OdDbImpAssocRevolvedSurfaceActionBody::evaluateOverride(OdDbObjectId parentActionId)
{
  OdDbAssocActionPtr pAction = OdDbAssocAction::cast(parentActionId.openObject(OdDb::kForWrite));
  OdDbObjectIdArray snapPointParams = pAction->ownedParams();

  OdDbAssocDependencyPtr pSurfaceAssocDep = m_surfaceObjectDepId.openObject(OdDb::kForWrite);

  if (pSurfaceAssocDep.isNull())
    return;

  OdDbEntityPtr bEntRef = checkAccompanying(parentActionId, pAction);

  if (bEntRef.isNull())
    return;

  OdDbRevolvedSurfacePtr pSurface = OdDbRevolvedSurface::cast(bEntRef);
  //OdDbRevolvedSurfacePtr pSurface = OdDbRevolvedSurface::cast(pSurfaceAssocDep->dependentOnObject().openObject(OdDb::kForWrite));

  ODA_ASSERT(!pSurface.isNull());
  OdDbRevolveOptions revolveOptions;
  pSurface->getRevolveOptions(revolveOptions);
  OdGePoint3d axisPnt = pSurface->getAxisPnt();
  OdGeVector3d axisDir = pSurface->getAxisVec();
  //double revAngle = pSurface->getRevolveAngle();
  OdString expression, evaluatorId;
  double revAngle = revolveAngle(pAction, expression, evaluatorId);
  double startAngle = pSurface->getStartAngle();


  OdDbObjectIdArray objDependentIDs;
  pAction->getDependencies(true, true, objDependentIDs); //getDependentObjects(true, true, objDependentIDs);

  ODA_ASSERT(objDependentIDs.length() > 1);
  OdDbSurfacePtr pSurf;
  OdDbCurvePtr pEntTemp;

  for (OdUInt32 i = 0; i < objDependentIDs.length(); i++)
  {
    OdDbAssocDependencyPtr pDep = objDependentIDs.getAt(i).openObject(OdDb::kForRead);
    pEntTemp = OdDbCurve::cast(pDep->dependentOnObject().openObject());
  }

  OdResult esTemp = eNotInitializedYet;

  if (!pEntTemp.isNull())
  {
    OdDbRevolvedSurfacePtr pRevolvedSurfTemp = OdDbRevolvedSurface::createObject();

    pRevolvedSurfTemp->setUIsolineDensity(pSurface->uIsolineDensity());
    pRevolvedSurfTemp->setVIsolineDensity(pSurface->vIsolineDensity());
    esTemp = pRevolvedSurfTemp->createRevolvedSurface(pEntTemp, axisPnt, axisDir, revAngle, startAngle, revolveOptions);// , 0, true);

    if (esTemp == eOk)
    {
      pSurface->handOverTo(pRevolvedSurfTemp);
    }
  }
  //delete[] objIdForLoft;
}

OdDouble  OdDbImpAssocRevolvedSurfaceActionBody::revolveAngle(const OdDbAssocActionPtr pAction, OdString& expression, OdString& evaluatorId) const
{
  OdDouble retD = -1;
  OdDbEvalVariantPtr value = OdDbEvalVariant::init(retD);

  if (pAction->getValueParam(kRevolveAngleParamName, *value.get(), expression, evaluatorId, 0) != eOk)
  {
    return -1;
  }

  return value->getDouble();
}

OdResult OdDbImpAssocRevolvedSurfaceActionBody::setRevolveAngle(OdDbAssocActionPtr pAction, OdDouble dValue, const OdString& expression, const OdString& evaluatorId)
{
  const OdDbEvalVariantPtr value = OdDbEvalVariant::init(dValue);
  OdString emptyStr("");
  return pAction->setValueParam(kRevolveAngleParamName, *value.get(), expression, evaluatorId, emptyStr, false, 0);
}
