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
#include "RxObject.h"
// ge
#include "Ge/GeCircArc3d.h"
#include "Ge/GeCompositeCurve3d.h"
// db common
#include "DbHostAppServices.h"
#include "DbDatabase.h"
#include "DbBlockTableRecord.h"
#include "DbCommandContext.h"
// db entities
#include "DbCircle.h"
#include "DbEllipse.h"
#include "DbLine.h"
#include "DbSpline.h"
#include "DbPolyline.h"
#include "Db3dPolyline.h"
#include "DbRegion.h"
#include "Db3dSolid.h"
#include "DbLoftedSurface.h"
#include "DbExtrudedSurface.h"
#include "DbRevolvedSurface.h"
#include "DbPlaneSurface.h"
#include "Db3dPolylineVertex.h"
#include "DbSweepOptions.h"
#include "DbSweptSurface.h"
#include "DbRevolveOptions.h"
#include "DbLoftOptions.h"
#include "DbMText.h"
#include "DbTextStyleTable.h"
#include "DbTextStyleTableRecord.h"
#include "DbDictionary.h"
#include "DbBackground.h"
// other
#include "ClassFilter.h"
#include "Ed/EdCommandStack.h"
#include "AbstractViewPE.h"

// Helpers

template <class T>
static OdSmartPtr<T> selectSingleObject(OdDbUserIO* pIO, const OdString& msg)
{
  ClassFilter filter(T::desc());
  OdDbSelectionSetPtr pFirstSel = pIO->select(msg, OdEd::kSelSingleEntity, 0, OdString::kEmpty, &filter);
  if (0 == pFirstSel->numEntities()) {
    pIO->putString(OD_T("Nothing selected."));
    return OdSmartPtr<T>();
  }

  OdDbSelectionSetIteratorPtr pIter = pFirstSel->newIterator();
  return pIter->objectId().openObject();
}

static void collectDbEnts(OdDbSelectionSetPtr pSet, OdDbEntityPtrArray& dbEnts, OdSmartPtr<OdDbUserIO> pIO)
{
  OdString tmp;
  OdUInt32 selectedCount = pSet->numEntities();
  if (selectedCount == 0)
  {
    pIO->putString(OD_T("Nothing selected."));
    return;
  }
  tmp.format(OD_T("%d Entities selected"), selectedCount);
  pIO->putString(tmp);

  OdDbSelectionSetIteratorPtr pIt = pSet->newIterator();

  while (!pIt->done())
  {
    OdDbObjectPtr pObj = pIt->objectId().safeOpenObject(OdDb::kForRead);

    OdDbEntityPtr pEntity = OdDbEntity::cast(pObj);
    if (pEntity.isNull())
    {
      pIO->putString(OD_T("Unsupported entity."));
      pIt->next();
      continue;
    }

    dbEnts.append(pEntity);
    pIt->next();
  }
}

void CreateRegions(OdRxObjectPtrArray &regions);


static bool getDerivAtCurveEnd(OdDbDatabase* pDatabase, OdDbUserIO* pIO, OdDbCurve* pCurve, bool isAtEnd, OdGeVector3d& deriv)
{
  double param = 0;
  OdResult status = isAtEnd ? pCurve->getEndParam(param) : pCurve->getStartParam(param);
  if (eOk != status) {
    pIO->putString(pDatabase->appServices()->getErrorDescription(status));
    return false;
  }

  status = pCurve->getFirstDeriv(param, deriv);
  if (eOk != status) {
    pIO->putString(pDatabase->appServices()->getErrorDescription(status));
    return false;
  }
  if (deriv.isZeroLength()) {
    pIO->putString(OD_T("Bad curve"));
    return false;
  }

  return true;
}

static OdDbRegionPtr createRegionAtCurveStart(OdDbCurve* pCurve, double radius, OdDbDatabase* pDatabase, OdDbUserIO* pIO)
{
  OdGePoint3d startPoint;
  OdGeVector3d startDer;

  OdResult status = pCurve->getStartPoint(startPoint);
  if (eOk != status) {
    pIO->putString(pDatabase->appServices()->getErrorDescription(status));
    return OdDbRegionPtr();
  }

  if (!getDerivAtCurveEnd(pDatabase, pIO, pCurve, false, startDer)) {
    return OdDbRegionPtr();
  }

  OdDbCirclePtr pCircleProfile = OdDbCircle::createObject();
  pCircleProfile->setDatabaseDefaults(pDatabase);
  pCircleProfile->setCenter(startPoint);
  pCircleProfile->setRadius(radius);
  pCircleProfile->setNormal(startDer);

  OdRxObjectPtrArray pCurves;
  pCurves.append(pCircleProfile);
  OdRxObjectPtrArray pRegions;

  status = OdDbRegion::createFromCurves(pCurves, pRegions);
  if (eOk != status) {
    pIO->putString(pDatabase->appServices()->getErrorDescription(status));
    return OdDbRegionPtr();
  }
  if (1 != pRegions.size()) {
    pIO->putString(OD_T("Failed to create region"));
    return OdDbRegionPtr();
  }

  OdDbRegionPtr pResult = pRegions[0];
  pResult->setDatabaseDefaults(pDatabase);
  return pResult;
}

static void addVertToPline(OdDb3dPolyline* polyline, const OdGePoint3d& point)
{
  OdDb3dPolylineVertexPtr pVert3d = OdDb3dPolylineVertex::createObject();
  pVert3d->setPosition(point);
  polyline->appendVertex(pVert3d);
}

// Extrude

void _ExtrudeSolid_func(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdSmartPtr<OdDbUserIO> pIO = pDbCmdCtx->userIO();
  OdDbDatabase* pDatabase = pDbCmdCtx->database();
  OdDbBlockTableRecordPtr pMs = pDatabase->getModelSpaceId().safeOpenObject(OdDb::kForWrite);

  OdDbSelectionSetPtr pSel = pIO->select(OD_T("Select objects:"), OdEd::kSelSingleEntity |
    OdEd::kSelAllowSubents);
  if (pSel->numEntities() != 0)
  {
    OdDbSelectionSetIteratorPtr pIter = pSel->newIterator();
    while (!pIter->done())
    {
      OdDbObjectId objId = pIter->objectId();
      OdDbEntityPtr pEnt = objId.openObject(OdDb::kForWrite);
      OdDbSweepOptions sweepOptions;

      if (!pEnt.isNull() && pEnt->isKindOf(OdDb3dSolid::desc()))
      {
        if (pIter->subentCount())
        {
          OdDbFullSubentPath subentPath;
          int count = pIter->subentCount();
          for (int i = 0; i < count; i++)
          {
            if (pIter->getSubentity(i, subentPath))
            {
              OdDb3dSolidPtr pSolid1 = OdDb3dSolid::createObject();
              double height = pIO->getReal(OD_T("Specify height:"));
              OdResult res = pSolid1->createExtrudedSolid(pEnt, subentPath.subentId(), height, sweepOptions);
              if (res == eOk)
              {
                OdDbBlockTableRecordPtr pMs = pDatabase->getModelSpaceId().safeOpenObject(OdDb::kForWrite);
                pMs->appendOdDbEntity(pSolid1);
                pIO->putString(OD_T("eOk"));
              }
              else
                pIO->putString(OD_T("Error"));
            }
          }
        }
      }
      pIter->next();
    }
  }
}

void _ExtrudeFaces_func(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdSmartPtr<OdDbUserIO> pIO = pDbCmdCtx->userIO();

  OdDbSelectionSetPtr pSel = pIO->select(OD_T("Select objects:"), OdEd::kSelSingleEntity |
    OdEd::kSelAllowSubents);
  if (pSel->numEntities() != 0)
  {
    OdDbSelectionSetIteratorPtr pIter = pSel->newIterator();
    while (!pIter->done())
    {
      OdDbObjectId objId = pIter->objectId();
      OdDbEntityPtr pEnt = objId.openObject(OdDb::kForWrite);
      OdDbSweepOptions sweepOptions;

      if (!pEnt.isNull() && pEnt->isKindOf(OdDb3dSolid::desc()))
      {
        if (pIter->subentCount())
        {
          OdDbFullSubentPath subentPath;
          int count = pIter->subentCount();
          OdArray<OdDbSubentId*> arr;
          OdArray<OdDbFullSubentPath> arrPath;
          arrPath.resize(count);
          for (int i = 0; i < count; i++)
          {
            if (pIter->getSubentity(i, arrPath[i]))
            {
              arr.push_back(&arrPath[i].subentId());
            }
          }
          double height = pIO->getReal(OD_T("Specify height:"));
          double taper = pIO->getReal(OD_T("Specify taper:"));
          OdResult res = OdDb3dSolidPtr(pEnt)->extrudeFaces(arr, height, taper);
          if (res == eOk)
          {
            pIO->putString(OD_T("eOk"));
          }
          else
            pIO->putString(OD_T("Error"));
        }
      }
      pIter->next();
    }
  }
}

void _ExtrudeRegionsFromModelSpace_func(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabase* pDatabase = pDbCmdCtx->database();

  OdDbBlockTableRecordPtr pMs = pDatabase->getModelSpaceId().safeOpenObject(OdDb::kForWrite);

  OdDbObjectIteratorPtr pIter = pMs->newIterator();
  while (!pIter->done())
  {
    OdDbObjectPtr pObj = pIter->objectId().safeOpenObject(OdDb::kForWrite);
    if (pObj->isKindOf(OdDbRegion::desc()))
    {
      OdDbRegionPtr pRegion = OdDbRegionPtr(pObj);

      OdDb3dSolidPtr pSolid = OdDb3dSolid::createObject();
      OdDb3dSolidPtr pSolid2 = OdDb3dSolid::createObject();

      if (pSolid->extrude(OdDbRegionPtr(pObj), 5, 0) == eOk)
      {
        pMs->appendOdDbEntity(pSolid);
      }

      if (pSolid2->extrude(OdDbRegionPtr(pObj), -5, 0) == eOk)
      {
        pMs->appendOdDbEntity(pSolid2);
      }

    }

    pIter->step();
  }
}

void _ExtrudeRegionsFromCurves_func(OdEdCommandContext* pCmdCtx)
{
  // Create regions
  OdRxObjectPtrArray regions;
  CreateRegions(regions);

  // Extrude regions
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabasePtr pDb = pDbCmdCtx->database();

  OdDbBlockTableRecordPtr pMs = pDb->getModelSpaceId().safeOpenObject(OdDb::kForWrite);

  OdRxObjectPtrArray::iterator pIt = regions.begin();
  OdRxObjectPtrArray::iterator pEnd = regions.end();
  //pIt = pEnd - 1;

  while (pIt != pEnd)
  {
    OdDb3dSolidPtr pSolid1 = OdDb3dSolid::createObject();
    OdResult res = pSolid1->extrude(OdDbRegion::cast(*pIt), 5, 0); // non 0 angles are not supported.
    ODA_ASSERT(res == eOk);
    if (res == eOk)
    {
      pMs->appendOdDbEntity(pSolid1);
    }

    OdDb3dSolidPtr pSolid2 = OdDb3dSolid::createObject();
    res = pSolid2->extrude(OdDbRegion::cast(*pIt), -5, 0); // non 0 angles are not supported.
    ODA_ASSERT(res == eOk);
    if (res == eOk)
    {
      pMs->appendOdDbEntity(pSolid2);
    }

    ++pIt;
  }
}


// Revolve

void _Revolve_func(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabase* pDatabase = pDbCmdCtx->database();
  OdSmartPtr<OdDbUserIO> pIO = pDbCmdCtx->userIO();
  OdDbBlockTableRecordPtr pMs = pDatabase->getModelSpaceId().safeOpenObject(OdDb::kForWrite);

  OdDbLinePtr pLine;
  while (pLine.isNull())
  {
    OdDbSelectionSetPtr pFirstSel = pIO->select(OD_T("Select axis of revolution"), OdEd::kSelSingleEntity/*, 0, OdString::kEmpty, &filter*/);
    if (pFirstSel->numEntities() == 0)
    {
      pIO->putString(OD_T("Nothing selected."));
      continue;
    }
    OdDbSelectionSetIteratorPtr pIter = pFirstSel->newIterator();
    pLine = OdDbLine::cast(pIter->objectId().openObject());
  }
  OdGePoint3d axisPnt = pLine->startPoint();
  OdGeVector3d axisDir = pLine->endPoint() - axisPnt;


  OdDbSelectionSetPtr pFirstSel = pIO->select(OD_T("Select entity to rotate"), OdEd::kSelSingleEntity/*, 0, OdString::kEmpty, &filter*/);
  if (pFirstSel->numEntities() == 0)
  {
    pIO->putString(OD_T("Nothing selected."));
    return;
  }
  OdDbSelectionSetIteratorPtr pIter = pFirstSel->newIterator();
  while (!pIter->done())
  {
    OdDbObjectId objId = pIter->objectId();

    OdDbEntityPtr pEnt = objId.openObject();
    OdGePoint3dArray aPts;
    if (!pEnt.isNull())
    {
      OdDb3dSolidPtr pSolid = OdDb3dSolid::createObject();
      pSolid->setDatabaseDefaults(pDatabase);
      double revAngle = Oda2PI; double startAngle = 0.;
      OdDbRevolveOptions revolveOptions;
      //revolveOptions.setDraftAngle(3);

      //revolveOptions.setTwistAngle(1);
      OdResult res = pSolid->createRevolvedSolid(pEnt, axisPnt, axisDir, revAngle, startAngle, revolveOptions);
      ODA_ASSERT(res == eOk);
      if (res == eOk)
      {
        OdDbBlockTableRecordPtr pMs = pDatabase->getModelSpaceId().safeOpenObject(OdDb::kForWrite);
        pMs->appendOdDbEntity(pSolid);
      }
      break;
    }
    pIter->next();
  }
}

void _RevolveRegionsFromModelSpace_func(OdEdCommandContext* pCmdCtx)
{
  OdGeLine3d revolveAxis(OdGePoint3d::kOrigin, OdGeVector3d::kYAxis);
  double revolveAngle = OdaPI2;

  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabase* pDatabase = pDbCmdCtx->database();

  OdDbBlockTableRecordPtr pMs = pDatabase->getModelSpaceId().safeOpenObject(OdDb::kForWrite);

  OdDbObjectIteratorPtr pIter = pMs->newIterator();
  while (!pIter->done())
  {
    OdDbObjectPtr pObj = pIter->objectId().safeOpenObject(OdDb::kForWrite);
    if (pObj->isKindOf(OdDbRegion::desc()))
    {
      OdDbRegionPtr pRegion = OdDbRegionPtr(pObj);
      OdDb3dSolidPtr pSolid = OdDb3dSolid::createObject();
      pSolid->setColor(pRegion->color());
      if (pSolid->revolve(OdDbRegionPtr(pObj), revolveAxis.pointOnLine(), revolveAxis.direction(), revolveAngle) == eOk)
      {
        pMs->appendOdDbEntity(pSolid);
      }
    }

    pIter->step();
  }
}

// Sweep

void _ExtrudeAlongPath_func(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabase* pDatabase = pDbCmdCtx->database();
  OdDbUserIOPtr pIO = pDbCmdCtx->userIO();

  OdDbRegionPtr pRegion = selectSingleObject<OdDbRegion>(pIO, OD_T("Select region to extrude"));
  if (pRegion.isNull()) {
    return;
  }

  OdDbCurvePtr pPath = selectSingleObject<OdDbCurve>(pIO, OD_T("Select extrusion path"));
  if (pPath.isNull()) {
    return;
  }

  OdDb3dSolidPtr pExtrude = OdDb3dSolid::createObject();
  pExtrude->setDatabaseDefaults(pDatabase);
  OdResult status = pExtrude->extrudeAlongPath(pRegion, pPath);
  if (eOk != status) {
    pIO->putString(pDatabase->appServices()->getErrorDescription(status));
    return;
  }
  OdDbBlockTableRecordPtr pMS = pDatabase->getModelSpaceId().safeOpenObject(OdDb::kForWrite);
  pMS->appendOdDbEntity(pExtrude);
}

void _Sweep_func(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabase* pDatabase = pDbCmdCtx->database();
  OdSmartPtr<OdDbUserIO> pIO = pDbCmdCtx->userIO();

  OdDbSelectionSetPtr pFirstSel = pIO->select(OD_T("Select objects to sweep"), OdEd::kSelSingleEntity/*, 0, OdString::kEmpty, &filter*/);
  if (pFirstSel->numEntities() == 0)
  {
    pIO->putString(OD_T("Nothing selected."));
    return;
  }

  OdDbSelectionSetPtr pSecondSel = pIO->select(OD_T("Select sweep path"), OdEd::kSelSingleEntity/*, 0, OdString::kEmpty, &filter*/);

  if (pSecondSel->numEntities() == 0)
  {
    pIO->putString(OD_T("Nothing selected."));
    return;
  }
  int nAlign = pDbCmdCtx->dbUserIO()->getKeyword(L"NoAlignment-AlignSweepEntityToPath-TranslateSweepEntityToPath-TranslatePathToSweepEntity? (N\\A\\S\\P)", L"N A S P", 1);
  int nType = pDbCmdCtx->dbUserIO()->getKeyword(L"3dSolid(S) ur Surface(U)? (S\\U)", L"S U", 1);
  OdDbSelectionSetIteratorPtr pIter = pFirstSel->newIterator();
  bool notBrack = true;
  while (!pIter->done() && notBrack)
  {
    OdDbObjectId objId = pIter->objectId();
    OdDbEntityPtr pEnt = objId.openObject();
    OdDbSweepOptions sweep;
    OdDb::Planarity planarity;
    OdGePoint3d pnt;
    OdGeVector3d vec;
    bool closed;
    double approxArcLen;

    if (!pEnt.isNull() && sweep.checkSweepCurve(pEnt, planarity, pnt, vec, closed, approxArcLen) == eOk)
    {
      OdDbSelectionSetIteratorPtr pSecondIter = pSecondSel->newIterator();
      while (!pSecondIter->done() && pIter != pSecondIter)
      {
        objId = pSecondIter->objectId();
        OdDbEntityPtr pSecondEnt = objId.openObject();
        if (!pSecondEnt.isNull() && sweep.checkPathCurve(pSecondEnt) == eOk)
        {
          //ARX 2016 twistAngle is 0
          //sweep.setTwistAngle(2); 
          //OdGeVector3d vec1;
          //vec1.set(3, 1, 0);
          //sweep.setTwistRefVec(vec1);
          sweep.setAlign((OdDbSweepOptions::AlignOption)nAlign);
          OdResult res;
          OdDbEntityPtr pBody;
          if (nType == 0)
          {
            pBody = OdDb3dSolid::createObject();
            res = static_cast<OdDb3dSolidPtr>(pBody)->createSweptSolid(pEnt, pSecondEnt, sweep);
          }
          else
          {
            pBody = OdDbSweptSurface::createObject();
            res = static_cast<OdDbSweptSurfacePtr>(pBody)->createSweptSurface(pEnt, pSecondEnt, sweep);
          }
          ODA_ASSERT(res == eOk);
          if (res == eOk)
          {
            OdDbBlockTableRecordPtr pMs = pDatabase->getModelSpaceId().safeOpenObject(OdDb::kForWrite);
            pMs->appendOdDbEntity(pBody);
          }
          notBrack = false;
          break;
        }
        pSecondIter->next();
      }
    }
    pIter->next();
  }
}

static OdDbSplinePtr createSplineFromPline(OdDbDatabase* pDatabase, OdDbUserIO* pIO, OdDb3dPolyline* polyline)
{
  OdGeVector3d startDer;
  OdGeVector3d endDer;
  if (!getDerivAtCurveEnd(pDatabase, pIO, polyline, false, startDer)
    || !getDerivAtCurveEnd(pDatabase, pIO, polyline, true, endDer))
  {
    return OdDbSplinePtr();
  }
  startDer.normalize();
  endDer.normalize();

  OdDb::Poly3dType polyType = polyline->polyType();

  OdDb3dPolylinePtr tmpPolyline;
  if (OdDb::k3dSimplePoly == polyType) {
    tmpPolyline = polyline->clone();
    tmpPolyline->setPolyType(polyType = OdDb::k3dCubicSplinePoly);
    OdResult status = tmpPolyline->splineFit();
    if (eOk != status) {
      pIO->putString(pDatabase->appServices()->getErrorDescription(status));
      return OdDbSplinePtr();
    }
    polyline = tmpPolyline;
  }

  OdGePoint3dArray points;
  OdGePoint3dArray nonfitPoints;
  for (OdDbObjectIteratorPtr pIter = polyline->vertexIterator(); !pIter->done(); pIter->step())
  {
    OdDb3dPolylineVertexPtr pVert = pIter->entity();
    OdDb::Vertex3dType vertType = pVert->vertexType();

    if (OdDb::k3dFitVertex != vertType) {
      nonfitPoints.append(pVert->position());
      continue;
    }

    points.append(pVert->position());
  }

  if (points.isEmpty()) {
    pIO->putString(OD_T("Bad curve"));
    return OdDbSplinePtr();
  }

  OdDbSplinePtr pSpline = OdDbSpline::createObject();
  pSpline->setDatabaseDefaults(pDatabase);
  pSpline->setFitData(points, 3, 1e-10, startDer, endDer);

  return pSpline;
}

static void makeSmoothSweep3dPoly(OdDbDatabase* pDatabase, OdDbUserIO* pIO, OdDb3dPolyline* pipePath, double pipeRadius)
{
  OdDbRegionPtr pProfile = createRegionAtCurveStart(pipePath, pipeRadius, pDatabase, pIO);
  if (pProfile.isNull()) {
    return;
  }

  OdDbSplinePtr pSplinePath = createSplineFromPline(pDatabase, pIO, pipePath);
  if (pSplinePath.isNull()) {
    return;
  }

  OdDb3dSolidPtr pExtrude = OdDb3dSolid::createObject();
  pExtrude->setDatabaseDefaults(pDatabase);
  OdResult status = pExtrude->extrudeAlongPath(pProfile, pSplinePath);
  if (eOk != status) {
    pIO->putString(pDatabase->appServices()->getErrorDescription(status));
    return;
  }
  OdDbBlockTableRecordPtr pMS = pDatabase->getModelSpaceId().safeOpenObject(OdDb::kForWrite);
  pMS->appendOdDbEntity(pExtrude);
}

void _CreateSmoothPipeEx_func(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabase* pDatabase = pDbCmdCtx->database();
  OdDbUserIOPtr pIO = pDbCmdCtx->userIO();

  OdDb3dPolylinePtr pipePath = selectSingleObject<OdDb3dPolyline>(pIO, OD_T("Select extrusion path"));
  if (pipePath.isNull()) {
    return;
  }

  double pipeRadius = pIO->getReal(OD_T("Enter pipe radius"));

  makeSmoothSweep3dPoly(pDatabase, pIO, pipePath, pipeRadius);
}

void _CreateComlexSmoothPipeEx_func(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabase* pDatabase = pDbCmdCtx->database();
  OdDbUserIOPtr pIO = pDbCmdCtx->userIO();

  OdGePoint3d points[] =
  {
    OdGePoint3d(20., 20., 0.),
    OdGePoint3d(20., 40., 0.),
    OdGePoint3d(20., 60., 0.),
    OdGePoint3d(50., 60., 0.),
    OdGePoint3d(80., 60., 0.),
    OdGePoint3d(80., 50., 0.),
    OdGePoint3d(80., 40., 0.),
    OdGePoint3d(100., 40., 0.),
    OdGePoint3d(280., 40., 0.),
    OdGePoint3d(300., 40., 0.),
    OdGePoint3d(300., 40., -20),
    OdGePoint3d(300., 40., -180),
    OdGePoint3d(300., 40., -200.),
    OdGePoint3d(275., 40., -200.),
    OdGePoint3d(250., 40., -200.),
    OdGePoint3d(250., 40., -220.),
    OdGePoint3d(250., 40., -240.),
    OdGePoint3d(285., 40., -240.),
    OdGePoint3d(320., 40., -240.),
    OdGePoint3d(320., 60., -240.),
    OdGePoint3d(320., 80., -240.),
  };
  int pointsCount = sizeof(points) / sizeof(*points);
  OdDb3dPolylinePtr pipePath = OdDb3dPolyline::createObject();
  pipePath->setDatabaseDefaults(pDatabase);
  for (int i = 0; i < pointsCount; ++i) {
    addVertToPline(pipePath, points[i]);
  }

  makeSmoothSweep3dPoly(pDatabase, pIO, pipePath, 3.);
}

// Loft

void _CreateLoftedSolid_func(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabase* pDatabase = pDbCmdCtx->database();
  OdSmartPtr<OdDbUserIO> pIO = pDbCmdCtx->userIO();
  OdDbBlockTableRecordPtr pMs = pDatabase->getModelSpaceId().safeOpenObject(OdDb::kForWrite);

  try
  {
    OdDbEntityPtrArray crossSectionCurves, guideCurvesArray, pathCurves;
    OdDbSelectionSetPtr pSetCrossSection = pIO->select(OD_T("Select cross section curves:"), OdEd::kSelAllowSubentsAlways, 0, OdString::kEmpty);
    collectDbEnts(pSetCrossSection, crossSectionCurves, pIO);

    int mode = pIO->getKeyword(OD_T("Select Mode [Only cross section curves/Path curve/Guide curves]:"),
      OD_T("Cross-Section Path Guide"), 0, OdEd::kInpDefault);

    OdDb3dSolidPtr pSolid = OdDb3dSolid::createObject();
    OdDbLoftOptions loftOptions;
    loftOptions.setNormal(OdDbLoftOptions::kNoNormal);

    // only cross section curves 
    if (mode == 0 || mode == 2)
    {
      if (mode == 2)
      {
        OdDbSelectionSetPtr pSetGuideCurves = pIO->select(OD_T("Select guide curves:"), OdEd::kSelAllowSubentsAlways, 0, OdString::kEmpty);
        collectDbEnts(pSetGuideCurves, guideCurvesArray, pIO);
      }
      OdResult res = pSolid->createLoftedSolid(crossSectionCurves, guideCurvesArray, NULL, loftOptions);
      if (res == eOk)
      {
        OdDbBlockTableRecordPtr pMs = pDatabase->getModelSpaceId().safeOpenObject(OdDb::kForRead);
        pMs->appendOdDbEntity(pSolid);
        pIO->putString(OD_T("eOk"));
      }
      else
        pIO->putString(OD_T("Error"));
    }
    else if (mode == 1) // cross section and path curve
    {
      OdDbSelectionSetPtr pSetPathCurve = pIO->select(OD_T("Select path curve:"), OdEd::kSelSingleEntity, 0, OdString::kEmpty);
      collectDbEnts(pSetPathCurve, pathCurves, pIO);
      OdResult res = pSolid->createLoftedSolid(crossSectionCurves, guideCurvesArray, pathCurves.first(), loftOptions);
      if (res == eOk)
      {
        OdDbBlockTableRecordPtr pMs = pDatabase->getModelSpaceId().safeOpenObject(OdDb::kForRead);
        pMs->appendOdDbEntity(pSolid);
        pIO->putString(OD_T("eOk"));
      }
      else
        pIO->putString(OD_T("Error"));
    }
  }
  catch (...)
  {
    pIO->putString(OD_T("Create Lofted Solid Failed!"));
  }
}

void _CreateLoftSurface_func(OdEdCommandContext* pCmdCtx)
{
  // Using the AcDbLoftedSurface class creating a lofted Surface. 
  // The lamp shade surface and the bowl surface are created as a lofted surface
  OdCmColor col;
  col.setRGB(252, 234, 39);

  // In memory circles that represents the lamp shade profile
  OdDbCirclePtr pCirc1 = OdDbCircle::createObject();
  pCirc1->setCenter(OdGePoint3d(18.0, 8.0, 15.5));
  pCirc1->setNormal(OdGeVector3d::kZAxis);
  pCirc1->setRadius(2.);

  OdDbCirclePtr pCirc2 = OdDbCircle::createObject();
  pCirc2->setCenter(OdGePoint3d(18.0, 8.0, 17.5));
  pCirc2->setNormal(OdGeVector3d::kZAxis);
  pCirc2->setRadius(1.);

  OdGePoint3dArray pts;

  pts.append(OdGePoint3d(20.0, 8.0, 15.5));
  pts.append(OdGePoint3d(19.3, 8.0, 16.5));
  pts.append(OdGePoint3d(19.0, 8.0, 17.5));

  // In memory splines that serve as guide curves for the lamp shade
  OdDbSplinePtr pSpln1 = OdDbSpline::createObject();
  pSpln1->setFitData(pts, 3, 0., OdGeVector3d::kIdentity, OdGeVector3d::kIdentity);

  pts.clear();
  pts.append(OdGePoint3d(16.0, 8.0, 15.5));
  pts.append(OdGePoint3d(16.7, 8.0, 16.5));
  pts.append(OdGePoint3d(17.0, 8.0, 17.5));

  OdDbSplinePtr pSpln2 = OdDbSpline::createObject();
  pSpln2->setFitData(pts, 3, 0., OdGeVector3d::kIdentity, OdGeVector3d::kIdentity);

  // Create the shade surfOde
  OdDbLoftedSurfacePtr pLoftSurfTemp = OdDbLoftedSurface::createObject();

  OdDbLoftOptions loftOptsTemp;

  OdArray<OdDbEntityPtr> pEntsTemp;
  pEntsTemp.append(pCirc1);
  pEntsTemp.append(pCirc2);
  OdArray<OdDbEntityPtr> pGuidesTemp;

  pGuidesTemp.append(pSpln1);
  pGuidesTemp.append(pSpln2);

  OdResult esTemp = pLoftSurfTemp->createLoftedSurface(pEntsTemp, pGuidesTemp, NULL, loftOptsTemp);

  pLoftSurfTemp->setLoftOptions(loftOptsTemp);

  if (esTemp == eOk)
  {
    OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
    OdDbDatabase* pDatabase = pDbCmdCtx->database();

    OdDbBlockTableRecordPtr pMs = pDatabase->getModelSpaceId().safeOpenObject(OdDb::kForWrite);
    pMs->appendOdDbEntity(pLoftSurfTemp);
  }
}

OdDbRegionPtr createLetterBRegion(OdEdCommandContext* pCmdCtx)
{
  // IO for messages
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabasePtr pDb = pDbCmdCtx->database();
  OdDbUserIO* pIO = pDbCmdCtx->dbUserIO();
  OdResult res;

  // Create char 'B' geometry -------------------------------------------
  OdRxObjectPtrArray aCurves, aRegions;

  // Outer region
  OdDbPolylinePtr pPlineOuter = OdDbPolyline::createObject();
  pPlineOuter->addVertexAt(0, OdGePoint2d(2., 0.), 1.);
  pPlineOuter->addVertexAt(1, OdGePoint2d(2., 2.7), 1.);
  pPlineOuter->addVertexAt(2, OdGePoint2d(2., 5.), 0.);
  pPlineOuter->addVertexAt(3, OdGePoint2d(0., 5.), 0.);
  pPlineOuter->addVertexAt(4, OdGePoint2d(0., 0.), 0.);
  pPlineOuter->setClosed(true);
  aCurves.push_back(pPlineOuter);

  // 0 inner region
  OdDbPolylinePtr pPlineInner0 = OdDbPolyline::createObject();
  pPlineInner0->addVertexAt(0, OdGePoint2d(0.6, 0.6), 0.);
  pPlineInner0->addVertexAt(1, OdGePoint2d(2.0, 0.6), 1.);
  pPlineInner0->addVertexAt(2, OdGePoint2d(2.0, 2.3), 0.);
  pPlineInner0->addVertexAt(3, OdGePoint2d(0.6, 2.3), 0.);
  pPlineInner0->setClosed(true);
  // Convert to spline for testing purposes
  OdGeCurve3d* gePline;
  pPlineInner0->getOdGeCurve(gePline);
  OdSharedPtr<OdGeCompositeCurve3d> pGePline = static_cast<OdGeCompositeCurve3d*>(gePline);
  const OdGeCurve3dPtrArray& curveList = pGePline->getCurveList();
  for (unsigned int i = 0; i < curveList.length(); ++i)
  {
    OdDbCurve* pDbCurve;
    OdGeCurve3dPtr pGeCurve = OdGeNurbCurve3d::convertFrom(curveList[i]);
    res = OdDbCurve::createFromOdGeCurve(*pGeCurve, pDbCurve);
    OdDbCurvePtr pNewDbCrv;
    pNewDbCrv.attach(pDbCurve);
    if (eOk != res)
    {
      pIO->putString(pDb->appServices()->getErrorDescription(res));
      return OdDbRegionPtr();
    }
    aCurves.push_back(pDbCurve);
  }

  // 1 inner region
  OdDbPolylinePtr pPlineInner1 = OdDbPolyline::createObject();
  pPlineInner1->addVertexAt(0, OdGePoint2d(0.6, 2.9), 0.);
  pPlineInner1->addVertexAt(1, OdGePoint2d(1.8, 2.9), 1.);
  pPlineInner1->addVertexAt(2, OdGePoint2d(1.8, 4.4), 0.);
  pPlineInner1->addVertexAt(3, OdGePoint2d(0.6, 4.4), 0.);
  pPlineInner1->setClosed(true);
  aCurves.push_back(pPlineInner1);

  res = OdDbRegion::createFromCurves(aCurves, aRegions);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return OdDbRegionPtr();
  }

  if (aRegions.length() != 3)
  {
    pIO->putString(L"Wrong regions count!");
    return OdDbRegionPtr();
  }

  // Surfaces Boolean --------------------------------------------------------
  OdDbRegionPtr pMainRegion = aRegions[0];
  // First kBoolSubtract
  res = pMainRegion->booleanOper(OdDb::kBoolSubtract, OdDbRegion::cast(aRegions[1].get()));
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return OdDbRegionPtr();
  }
  // Second kBoolSubtract
  res = pMainRegion->booleanOper(OdDb::kBoolSubtract, OdDbRegion::cast(aRegions[2].get()));
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return OdDbRegionPtr();
  }
  return pMainRegion;
}

OdRxClassPtr odrxGetModelerGeometryCreatorService();
static void checkModeler()
{
  // we should check if some modeler was loaded and if not - load ModelerGeometry.
  OdRxClassPtr pService = odrxGetModelerGeometryCreatorService();
  if (!pService.get())
  {
    ::odrxDynamicLinker()->loadApp(OdModelerGeometryModuleName, false);
  }
}

void _BooleanPETest_func(OdEdCommandContext* pCmdCtx)
{
  // IO for messages
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabasePtr pDb = pDbCmdCtx->database();
  OdDbUserIO* pIO = pDbCmdCtx->dbUserIO();
  OdResult res;

  // Try to load ModelerGeometry module if no Modeler is loaded
  checkModeler();

  OdDbRegionPtr pMainRegion = createLetterBRegion(pCmdCtx);
  if (pMainRegion.isNull())
  {
    pIO->putString(L"Null region!");
    return;
  }

  OdDb3dSolidPtr pSolid = OdDb3dSolid::createObject();
  OdDbSweepOptions options;
  // Extrude region
  res = pSolid->createExtrudedSolid(pMainRegion, OdGeVector3d::kZAxis * 2, options);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }

  // Solids Boolean --------------------------------------------------------
  OdDb3dSolidPtr pChamferSolid0 = OdDb3dSolid::createObject();
  pChamferSolid0->createBox(10., 10., 10.);
  pChamferSolid0->transformBy(OdGeMatrix3d::translation(OdGeVector3d(0., 5., 5.)));
  pChamferSolid0->transformBy(OdGeMatrix3d::rotation(OdaPI4, OdGeVector3d::kXAxis));
  OdDb3dSolidPtr pChamferSolid1 = pChamferSolid0->clone();
  pChamferSolid1->transformBy(OdGeMatrix3d::translation(OdGeVector3d(0., 5., 0.)));

  // First kBoolSubtract
  res = pSolid->booleanOper(OdDb::kBoolSubtract, pChamferSolid0);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  // Second kBoolSubtract
  res = pSolid->booleanOper(OdDb::kBoolSubtract, pChamferSolid1);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }

  // Append entity to database
  OdDbBlockTableRecordPtr pMS = pDb->getModelSpaceId().openObject(OdDb::kForWrite);
  pMS->appendOdDbEntity(pSolid);
}

// creates a key
void _BooleanKeyDemo_func(OdEdCommandContext* pCmdCtx)
{
  // IO for messages
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabasePtr pDb = pDbCmdCtx->database();
  OdDbUserIO* pIO = pDbCmdCtx->dbUserIO();
  OdResult res;

  // Try to load ModelerGeometry module if no Modeler is loaded
  checkModeler();

  OdUInt16 colorIndices[] = { 253, 252, 42 };

  OdDbBlockTableRecordPtr pMS = pDb->getModelSpaceId().openObject(OdDb::kForWrite);

  OdDbRegionPtr keyRegion;
  OdRxObjectPtrArray curves, regions;

  OdDbCirclePtr circle = OdDbCircle::createObject();
  circle->setCenter(OdGePoint3d::kOrigin);
  circle->setRadius(2.7);
  curves.append(circle);
  res = OdDbRegion::createFromCurves(curves, regions);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  OdDbRegionPtr circleRegion = OdDbRegion::cast(regions[0]);

  OdDbPolylinePtr poly = OdDbPolyline::createObject();
  poly->addVertexAt(0, OdGePoint2d(2.0, -1.0), 0.0);
  poly->addVertexAt(1, OdGePoint2d(9.7, -1.0), 0.0);
  poly->addVertexAt(2, OdGePoint2d(10.7, 0.2), 0.0);
  poly->addVertexAt(3, OdGePoint2d(10.2, 1.0), 0.0);
  poly->addVertexAt(4, OdGePoint2d(2.0, 1.0), 0.0);
  poly->setClosed(true);
  curves.clear();
  curves.append(poly);
  regions.clear();
  res = OdDbRegion::createFromCurves(curves, regions);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  OdDbRegionPtr polyRegion = OdDbRegion::cast(regions[0]);

  circleRegion->setColorIndex(colorIndices[0]);
  polyRegion->setColorIndex(colorIndices[1]);

  OdDbObjectId id = pDb->activeViewportId();
  if (!id.isNull())
  {
    OdDbObjectPtr pVp = id.safeOpenObject(OdDb::kForWrite);
    OdAbstractViewPEPtr pAVP(pVp);
    pAVP->zoomExtents(pVp, NULL, 1.2);
  }

  res = circleRegion->booleanOper(OdDb::kBoolUnite, polyRegion);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  keyRegion = circleRegion;

  OdDb3dSolidPtr key = OdDb3dSolid::createObject();
  OdDbSweepOptions sweepOptions;
  res = key->createExtrudedSolid(keyRegion, OdGeVector3d::kZAxis * 0.47, sweepOptions);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }

  key->setColorIndex(colorIndices[0]);
  pMS->appendOdDbEntity(key);

  OdDbPolylinePtr triangle = OdDbPolyline::createObject();
  triangle->addVertexAt(0, OdGePoint2d(0.0, 0.0), 0.0);
  triangle->addVertexAt(1, OdGePoint2d(0.4, 0.4 * sqrt(3.0)), 0.0);
  triangle->addVertexAt(2, OdGePoint2d(0.8, 0.0), 0.0);
  triangle->setClosed(true);
  curves.clear();
  curves.append(triangle);
  regions.clear();
  res = OdDbRegion::createFromCurves(curves, regions);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  OdDbRegionPtr triangleRegion = OdDbRegion::cast(regions[0]);

  OdDb3dSolidPtr file = OdDb3dSolid::createObject();
  res = file->createExtrudedSolid(triangle, OdGeVector3d::kZAxis * 9.0, sweepOptions);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  file->transformBy(OdGeMatrix3d::rotation(OdaPI2, OdGeVector3d::kYAxis));
  file->transformBy(OdGeMatrix3d::rotation(OdaPI / 6.0, OdGeVector3d::kXAxis));
  file->transformBy(OdGeMatrix3d::translation(OdGeVector3d(2.7, 0.2, 0.82)));

  file->setColorIndex(colorIndices[1]);

  OdDb3dSolidPtr fileForBoolean = file;
  file = file->clone();
  res = key->booleanOper(OdDb::kBoolSubtract, fileForBoolean);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }

  file->transformBy(OdGeMatrix3d::rotation(OdaPI, OdGeVector3d::kXAxis));
  file->transformBy(OdGeMatrix3d::translation(OdGeVector3d(0.0, 0.65, 0.47)));

  fileForBoolean = file;
  file = file->clone();
  res = key->booleanOper(OdDb::kBoolSubtract, fileForBoolean);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }

  file->transformBy(OdGeMatrix3d::rotation(OdaPI, OdGeVector3d::kXAxis));
  file->transformBy(OdGeMatrix3d::translation(OdGeVector3d(0.0, -0.5, 0.47)));

  fileForBoolean = file;
  file = file->clone();
  res = key->booleanOper(OdDb::kBoolSubtract, fileForBoolean);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }

  file->transformBy(OdGeMatrix3d::rotation(-OdaPI / 6.0, OdGeVector3d::kXAxis));
  file->transformBy(OdGeMatrix3d::rotation(-OdaPI2, OdGeVector3d::kYAxis));
  file->transformBy(OdGeMatrix3d::translation(OdGeVector3d(10.0, -0.77, -4.5)));

  fileForBoolean = file;
  file = file->clone();
  res = key->booleanOper(OdDb::kBoolSubtract, fileForBoolean);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }

  file->transformBy(OdGeMatrix3d::translation(OdGeVector3d(-0.8, -0.15, 0.0)));

  fileForBoolean = file;
  file = file->clone();
  res = key->booleanOper(OdDb::kBoolSubtract, fileForBoolean);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }

  file->transformBy(OdGeMatrix3d::translation(OdGeVector3d(-0.8, 0.3, 0.0)));

  fileForBoolean = file;
  file = file->clone();
  res = key->booleanOper(OdDb::kBoolSubtract, fileForBoolean);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }

  file->transformBy(OdGeMatrix3d::translation(OdGeVector3d(-0.8, -0.15, 0.0)));

  fileForBoolean = file;
  file = file->clone();
  res = key->booleanOper(OdDb::kBoolSubtract, fileForBoolean);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }

  file->transformBy(OdGeMatrix3d::translation(OdGeVector3d(-0.8, 0.1, 0.0)));

  fileForBoolean = file;
  file = file->clone();
  res = key->booleanOper(OdDb::kBoolSubtract, fileForBoolean);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }

  circle = OdDbCircle::createObject();
  circle->setCenter(OdGePoint3d(-1.3, 0.0, 0.0));
  circle->setRadius(0.5);
  curves.clear();
  curves.append(circle);
  regions.clear();
  res = OdDbRegion::createFromCurves(curves, regions);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  circleRegion = OdDbRegion::cast(regions[0]);

  OdDb3dSolidPtr cylinder = OdDb3dSolid::createObject();
  res = cylinder->createExtrudedSolid(circleRegion, OdGeVector3d::kZAxis * 4.0, sweepOptions);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  cylinder->transformBy(OdGeMatrix3d::translation(OdGeVector3d(0.0, 0.0, -2.0)));
  cylinder->setColorIndex(colorIndices[0]);

  res = key->booleanOper(OdDb::kBoolSubtract, cylinder);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }

  OdDbTextStyleTablePtr pStyles = pDb->getTextStyleTableId().safeOpenObject(OdDb::kForWrite);
  OdDbTextStyleTableRecordPtr pStyle = OdDbTextStyleTableRecord::createObject();
  OdDbObjectId ttfStyleId;
  pStyle->setName(L"DemoTtfStyle");
  ttfStyleId = pStyles->add(pStyle);
  pStyle->setFileName(L"arial.ttf");
  pStyle->setFont(L"arial", false, false, 0, 34);

  OdDbMTextPtr odaText = OdDbMText::createObject();
  odaText->setDatabaseDefaults(pDb);
  odaText->setContents(L"ODA");
  odaText->setTextStyle(ttfStyleId);
  odaText->setAttachment(OdDbMText::kMiddleCenter);
  odaText->setLocation(OdGePoint3d::kOrigin);
  odaText->setTextHeight(1.2);
  odaText->transformBy(OdGeMatrix3d::translation(OdGeVector3d(0.0, 0.0, 1.0)));
  odaText->setColorIndex(colorIndices[2]);

  pMS->appendOdDbEntity(odaText);

  OdSelectionSetPtr pSSet = OdDbSelectionSet::createObject(pDb);
  pSSet->append(odaText->id());
  pIO->setPickfirst(pSSet);
  ::odedRegCmds()->executeCommand(L"TxtExp", pCmdCtx);

  curves.clear();
  for (OdDbObjectIteratorPtr pIter = pMS->newIterator(); !pIter->done(); pIter->step())
  {
    OdDbEntityPtr pEnt = pIter->objectId().openObject(OdDb::kForWrite);
    if (pEnt->isKindOf(OdDbPolyline::desc()))
    {
      pEnt->setColorIndex(colorIndices[2]);
      curves.append(pEnt);
      OdDbPolyline::cast(pEnt)->erase();
    }
  }

  regions.clear();
  res = OdDbRegion::createFromCurves(curves, regions);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  if (regions.size() != 6)
  {
    pIO->putString(L"createFromCurves failed");
    return;
  }

  OdDbRegionPtr regionO = OdDbRegion::cast(regions[0]);
  OdDbRegionPtr regionOInner = OdDbRegion::cast(regions[1]);
  OdDbRegionPtr regionD = OdDbRegion::cast(regions[2]);
  OdDbRegionPtr regionDInner = OdDbRegion::cast(regions[3]);
  OdDbRegionPtr regionA = OdDbRegion::cast(regions[4]);
  OdDbRegionPtr regionAInner = OdDbRegion::cast(regions[5]);
  res = regionO->booleanOper(OdDb::kBoolSubtract, regionOInner);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  res = regionD->booleanOper(OdDb::kBoolSubtract, regionDInner);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  res = regionA->booleanOper(OdDb::kBoolSubtract, regionAInner);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  res = regionO->booleanOper(OdDb::kBoolUnite, regionD);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  res = regionO->booleanOper(OdDb::kBoolUnite, regionA);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  OdDbRegionPtr regionODA = regionO;
  regionODA->setColorIndex(colorIndices[2]);

  OdDb3dSolidPtr solidODA = OdDb3dSolid::createObject();
  res = solidODA->createExtrudedSolid(regionODA, OdGeVector3d::kZAxis * 0.7, sweepOptions);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }

  solidODA->setColorIndex(colorIndices[2]);
  regionODA->erase();

  solidODA->transformBy(OdGeMatrix3d::rotation(OdaPI2, OdGeVector3d::kZAxis));
  solidODA->transformBy(OdGeMatrix3d::translation(OdGeVector3d(0.6, 0.0, -0.7)));

  res = key->booleanOper(OdDb::kBoolSubtract, solidODA);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
}


// creates a pipe
void _SculptPipeDemo_func(OdEdCommandContext* pCmdCtx)
{
  // make false to perform demo in one step
  bool stepByStep = true;

  OdResult res;
  // IO for messages
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabasePtr pDb = pDbCmdCtx->database();
  OdDbUserIO* pIO = pDbCmdCtx->dbUserIO();

  OdDbBlockTableRecordPtr pMS = pDb->getModelSpaceId().openObject(OdDb::kForWrite);

  OdDbObjectId viewportId = pDb->activeViewportId();
  if (!viewportId.isNull())
  {
    OdDbObjectPtr pVp = viewportId.safeOpenObject(OdDb::kForWrite);
    OdAbstractViewPEPtr pAVP(pVp);

    pAVP->setRenderMode(pVp, OdDb::kGouraudShaded);

    //set background
    OdDbDictionaryPtr pBgDic = oddbGetBackgroundDictionary(pDb.get(), OdDb::kForWrite, true);
    OdDbGradientBackgroundPtr pGradientBg = OdDbGradientBackground::createObject();

    pGradientBg->setColorTop(OdCmEntityColor(33, 108, 170));
    pGradientBg->setColorMiddle(OdCmEntityColor(109, 158, 200));
    pGradientBg->setColorBottom(OdCmEntityColor(184, 208, 230));
    pGradientBg->setHeight(0.33);
    pGradientBg->setHorizon(0.5);

    OdDbObjectId bgId = pBgDic->setAt(L"gradientBg", pGradientBg);
    pAVP->setBackground(pVp, bgId);

    // Zoom to extents
    pAVP->setView(pVp, OdGePoint3d(6.0, 0.0, 0.0), OdGeVector3d(-0.2, -1.0, 1.0), OdGeVector3d::kZAxis, pAVP->fieldWidth(pVp), pAVP->fieldHeight(pVp), pAVP->isPerspective(pVp));
    OdGeBoundBlock3d extents(OdGePoint3d(-12, -12, -8), OdGePoint3d(12, 12, 23));
    pAVP->zoomExtents(pVp, &extents);
  }

  // Try to load ModelerGeometry module if no Modeler is loaded
  checkModeler();

  pDb->setLWDISPLAY(true);

  OdCmColor faceColor;
  faceColor.setRGB(0xBE, 0xBE, 0xBE);
  OdUInt16 edgeColorIndex = 30;

  OdRxObjectPtrArray curves, regions;

  OdDbCirclePtr circle = OdDbCircle::createObject();
  circle->setCenter(OdGePoint3d(6.0, 0.0, 0.0));
  circle->setRadius(3.0);
  circle->setColorIndex(edgeColorIndex);
  circle->setLineWeight(OdDb::kLnWt030);
  pMS->appendOdDbEntity(circle);

  if (stepByStep)
  {
    ::odedRegCmds()->executeCommand(L"REGEN", pCmdCtx);
    pIO->getString("Step 1. Press ENTER.");
  }
//TODO: enable after createRevolvedSurface implementation
#if 0
  OdDbRevolvedSurfacePtr turning = OdDbRevolvedSurface::createObject();
  OdDbRevolveOptions revolveOptions;
  res = turning->createRevolvedSurface(circle, OdGePoint3d::kOrigin, -OdGeVector3d::kYAxis, OdaPI * 0.7, 0.0, revolveOptions);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
#else
  //temporary code via solid extrude
  OdDb3dSolidPtr turningSolid = OdDb3dSolid::createObject();
  OdDbRevolveOptions revolveOptions;
  res = turningSolid->createRevolvedSolid(circle, OdGePoint3d::kOrigin, -OdGeVector3d::kYAxis, OdaPI * 0.7, 0.0, revolveOptions);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  OdRxObjectPtrArray objectsArr;
  res = turningSolid->explode(objectsArr);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  turningSolid->erase();
  OdDbSurfacePtr turning;
  ODA_ASSERT(objectsArr.size() == 3);
  for (unsigned i = 0; i < objectsArr.size(); ++i)
  {
    if (objectsArr[i]->isA() == OdDbSurface::desc())
    {
      ODA_ASSERT(turning.isNull());
      turning = objectsArr[i];
    }
    else
    {
      ODA_ASSERT(objectsArr[i]->isA() == OdDbRegion::desc());
      OdDbRegion::cast(objectsArr[i])->erase();
    }
  }
#endif
  turning->setColor(faceColor);
  pMS->appendOdDbEntity(turning);
  circle->erase();
  circle = NULL;

  if (stepByStep)
  {
    ::odedRegCmds()->executeCommand(L"REGEN", pCmdCtx);
    pIO->getString("Step 2. Press ENTER.");
  }

  OdDb3dSolidPtr sphere = OdDb3dSolid::createObject();
  sphere->createSphere(0.95);
  sphere->transformBy(OdGeMatrix3d::translation(OdGeVector3d(1.7, 0.0, 8.7)));
  sphere->setColorIndex(30);
  pMS->appendOdDbEntity(sphere);

  if (stepByStep)
  {
    ::odedRegCmds()->executeCommand(L"REGEN", pCmdCtx);
    pIO->getString("Step 3. Press ENTER.");
  }

  OdDbSurfacePtr newSurface;
  res = turning->booleanSubtract(sphere, newSurface);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  if (!newSurface.isNull())
  {
    turning = newSurface;
  }
  sphere->erase();
  sphere = NULL;

  if (stepByStep)
  {
    ::odedRegCmds()->executeCommand(L"REGEN", pCmdCtx);
    pIO->getString("Step 4. Press ENTER.");
  }

  circle = OdDbCircle::createObject();
  circle->setCenter(OdGePoint3d(6.0, 0.0, -10.0));
  circle->setRadius(2.0);
  circle->setColorIndex(edgeColorIndex);
  circle->setLineWeight(OdDb::kLnWt030);
  pMS->appendOdDbEntity(circle);

  if (stepByStep)
  {
    ::odedRegCmds()->executeCommand(L"REGEN", pCmdCtx);
    pIO->getString("Step 5. Press ENTER.");
  }

  OdDbExtrudedSurfacePtr pipe1 = OdDbExtrudedSurface::createObject();
  OdDbSweepOptions sweepOptions;
  res = pipe1->createExtrudedSurface(circle, OdGeVector3d::kZAxis * 16.0, sweepOptions);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  circle->erase();
  circle = NULL;
  pipe1->setColor(faceColor);
  pMS->appendOdDbEntity(pipe1);

  if (stepByStep)
  {
    ::odedRegCmds()->executeCommand(L"REGEN", pCmdCtx);
    pIO->getString("Step 6. Press ENTER.");
  }

  OdDbEntityPtr ent;
  pipe1->getTransformedCopy(OdGeMatrix3d::rotation(OdaPI, OdGeVector3d::kXAxis + OdGeVector3d::kZAxis), ent);
  OdDbExtrudedSurfacePtr pipe2 = OdDbExtrudedSurface::cast(ent);
  pMS->appendOdDbEntity(pipe2);

  if (stepByStep)
  {
    ::odedRegCmds()->executeCommand(L"REGEN", pCmdCtx);
    pIO->getString("Step 7. Press ENTER.");
  }

  pipe1->getTransformedCopy(OdGeMatrix3d::translation(OdGeVector3d(-1.5, 0.0, 10.0)) * OdGeMatrix3d::scaling(0.55), ent);
  OdDbExtrudedSurfacePtr pipe3 = OdDbExtrudedSurface::cast(ent);
  pMS->appendOdDbEntity(pipe3);

  if (stepByStep)
  {
    ::odedRegCmds()->executeCommand(L"REGEN", pCmdCtx);
    pIO->getString("Step 8. Press ENTER.");
  }

  OdDbPolylinePtr square = OdDbPolyline::createObject();
  square->addVertexAt(0, OdGePoint2d(-5.0, -5.0), 0.0);
  square->addVertexAt(1, OdGePoint2d(-5.0, 5.0), 0.0);
  square->addVertexAt(2, OdGePoint2d(5.0, 5.0), 0.0);
  square->addVertexAt(3, OdGePoint2d(5.0, -5.0), 0.0);
  square->setClosed(true);
  curves.clear();
  curves.append(square);
  regions.clear();
  res = OdDbRegion::createFromCurves(curves, regions);
  if (eOk != res || regions.size() != 1)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  OdDbRegionPtr squareRegion = OdDbRegion::cast(regions[0]);
  squareRegion->transformBy(OdGeMatrix3d::translation(OdGeVector3d(6.0, 0.0, 0.0)));
  OdDbPlaneSurfacePtr plane1 = OdDbPlaneSurface::createObject();
  plane1->createFromRegion(squareRegion);
  squareRegion->erase();
  plane1->setColor(faceColor);
  pMS->appendOdDbEntity(plane1);

  if (stepByStep)
  {
    ::odedRegCmds()->executeCommand(L"REGEN", pCmdCtx);
    pIO->getString("Step 9. Press ENTER.");
  }

  plane1->getTransformedCopy(OdGeMatrix3d::translation(OdGeVector3d(0.0, 0.0, -5.0)), ent);
  OdDbPlaneSurfacePtr plane2 = OdDbPlaneSurface::cast(ent);
  pMS->appendOdDbEntity(plane2);

  if (stepByStep)
  {
    ::odedRegCmds()->executeCommand(L"REGEN", pCmdCtx);
    pIO->getString("Step 10. Press ENTER.");
  }

  plane1->getTransformedCopy(OdGeMatrix3d::rotation(OdaPI, OdGeVector3d::kXAxis + OdGeVector3d::kZAxis), ent);
  OdDbPlaneSurfacePtr plane3 = OdDbPlaneSurface::cast(ent);
  pMS->appendOdDbEntity(plane3);

  plane2->getTransformedCopy(OdGeMatrix3d::rotation(OdaPI, OdGeVector3d::kXAxis + OdGeVector3d::kZAxis), ent);
  OdDbPlaneSurfacePtr plane4 = OdDbPlaneSurface::cast(ent);
  pMS->appendOdDbEntity(plane4);

  if (stepByStep)
  {
    ::odedRegCmds()->executeCommand(L"REGEN", pCmdCtx);
    pIO->getString("Step 11. Press ENTER.");
  }

  plane1->getTransformedCopy(OdGeMatrix3d::translation(OdGeVector3d(-0.8, 0.0, 12.0)) * OdGeMatrix3d::scaling(0.4), ent);
  OdDbPlaneSurfacePtr plane5 = OdDbPlaneSurface::cast(ent);
  pMS->appendOdDbEntity(plane5);

  if (stepByStep)
  {
    ::odedRegCmds()->executeCommand(L"REGEN", pCmdCtx);
    pIO->getString("Step 12. Press ENTER.");
  }

  OdSelectionSetPtr pSSet = OdDbSelectionSet::createObject(pDb);
  pSSet->append(pipe1->id());
  pSSet->append(pipe2->id());
  pSSet->append(pipe3->id());
  pSSet->append(turning->id());
  pSSet->append(plane1->id());
  pSSet->append(plane2->id());
  pSSet->append(plane3->id());
  pSSet->append(plane4->id());
  pSSet->append(plane5->id());
  pIO->setPickfirst(pSSet);
  ::odedRegCmds()->executeCommand(L"Sculpt", pDbCmdCtx);

  if (stepByStep)
  {
    ::odedRegCmds()->executeCommand(L"REGEN", pCmdCtx);
    pIO->getString("Step 13. Press ENTER.");
  }

  OdDb3dSolidPtr pipe;
  for (OdDbObjectIteratorPtr pIter = pMS->newIterator(); !pIter->done(); pIter->step())
  {
    OdDbEntityPtr pEnt = pIter->objectId().openObject(OdDb::kForWrite);
    if (pEnt->isKindOf(OdDb3dSolid::desc()))
    {
      ODA_ASSERT(pipe.isNull());
      pipe = OdDb3dSolid::cast(pEnt);
    }
  }

  OdDbEllipsePtr arc = OdDbEllipse::createObject();
  double majorRadius = 1.2;
  double minorRadius = 0.8;
  arc->set(OdGePoint3d(4.0 - majorRadius + 0.1, 0.0, -minorRadius + 0.1), -OdGeVector3d::kYAxis,
    OdGeVector3d::kXAxis * majorRadius, minorRadius / majorRadius, -OdaPI2, OdaPI * 0.85);
  arc->setColorIndex(edgeColorIndex);
  arc->setLineWeight(OdDb::kLnWt030);
  pMS->appendOdDbEntity(arc);

  if (stepByStep)
  {
    ::odedRegCmds()->executeCommand(L"REGEN", pCmdCtx);
    pIO->getString("Step 14. Press ENTER.");
  }

  //TODO: enable after createRevolvedSurface implementation
#if 0
  OdDbRevolvedSurfacePtr smoothPart1 = OdDbRevolvedSurface::createObject();
  res = smoothPart1->createRevolvedSurface(arc, OdGePoint3d(6.0, 0.0, 0.0), OdGeVector3d::kZAxis, Oda2PI, 0.0, revolveOptions);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
#else
  //temporary code via solid extrude
  OdDbLinePtr line = OdDbLine::createObject();
  OdGePoint3d point;
  arc->getStartPoint(point);
  line->setEndPoint(point);
  arc->getEndPoint(point);
  line->setStartPoint(point);
  curves.clear();
  curves.append(arc);
  curves.append(line);
  regions.clear();
  res = OdDbRegion::createFromCurves(curves, regions);
  if (eOk != res || regions.size() != 1)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  OdDbRegionPtr moonRegion = OdDbRegion::cast(regions[0]);
  
  OdDb3dSolidPtr smoothPartSolid = OdDb3dSolid::createObject();
  res = smoothPartSolid->createRevolvedSolid(moonRegion, OdGePoint3d(6.0, 0.0, 0.0), OdGeVector3d::kZAxis, Oda2PI, 0.0, revolveOptions);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  objectsArr.clear();
  res = smoothPartSolid->explode(objectsArr);
  if (eOk != res)
  {
    pIO->putString(pDb->appServices()->getErrorDescription(res));
    return;
  }
  smoothPartSolid->erase();
  smoothPartSolid = NULL;
  OdDbSurfacePtr smoothPart1;
  ODA_ASSERT(objectsArr.size() == 2 && objectsArr[0]->isA() == OdDbSurface::desc() && objectsArr[1]->isA() == OdDbSurface::desc());
  smoothPart1 = objectsArr[0];
  OdDbSurface::cast(objectsArr[1])->erase();
  line->erase();
  moonRegion->erase();
#endif
  arc->erase();
  smoothPart1->setColor(faceColor);
  pMS->appendOdDbEntity(smoothPart1);

  if (stepByStep)
  {
    ::odedRegCmds()->executeCommand(L"REGEN", pCmdCtx);
    pIO->getString("Step 15. Press ENTER.");
  }

  smoothPart1->getTransformedCopy(OdGeMatrix3d::rotation(OdaPI, OdGeVector3d::kXAxis + OdGeVector3d::kZAxis), ent);
  OdDbSurfacePtr smoothPart2 = OdDbSurface::cast(ent);
  pMS->appendOdDbEntity(smoothPart2);

  if (stepByStep)
  {
    ::odedRegCmds()->executeCommand(L"REGEN", pCmdCtx);
    pIO->getString("Step 16. Press ENTER.");
  }

  pSSet->clear();
  pSSet->append(pipe->id());
  pSSet->append(smoothPart1->id());
  pSSet->append(smoothPart2->id());
  pIO->setPickfirst(pSSet);
  pipe = NULL;
  ::odedRegCmds()->executeCommand(L"Sculpt", pDbCmdCtx);

  if (stepByStep)
  {
    ::odedRegCmds()->executeCommand(L"REGEN", pCmdCtx);
    pIO->getString("Done!");
  }
}

static OdDbRegionPtr createCircularRegion(OdDbDatabase* pDatabase)
{
  OdRxObjectPtrArray curveSegments;

  // create dummy OdDbCircle
  OdDbCirclePtr pC = OdDbCircle::createObject();
  pC->setFromOdGeCurve(OdGeCircArc3d());
  pC->setDatabaseDefaults(pDatabase);

  curveSegments.append(pC);

  OdRxObjectPtrArray regions;
  OdDbRegion::createFromCurves(curveSegments, regions);
  if (regions.isEmpty())
    return OdDbRegionPtr();

  return regions.first();
}

static void applyTransform(OdDb3dSolid *pSolid, OdGeVector3d translate, double dAngle = 0.)
{
  if (!pSolid)
    return;

  if (dAngle != 0.)
  {
    pSolid->transformBy(OdGeMatrix3d::rotation(dAngle, OdGeVector3d::kYAxis));
  }

  if (!translate.isZeroLength())
  {
    pSolid->transformBy(OdGeMatrix3d::translation(translate));
  }
}

static OdDb3dSolidPtr create90degree(OdDbDatabase* pDatabase, OdGeVector3d translate, double dAngle = 0.)
{
  OdDbRegionPtr pBase = createCircularRegion(pDatabase);

  OdDb3dSolidPtr pSolid = OdDb3dSolid::createObject();
  pSolid->setDatabaseDefaults(pDatabase);
  pSolid->setColorIndex(2);
  OdResult res = pSolid->revolve(pBase, OdGePoint3d(10, 0, 0), OdGeVector3d::kYAxis, OdaPI2);
  if (res != eOk)
  {
    return OdDb3dSolidPtr();
  }

  applyTransform(pSolid, translate, dAngle);
  return pSolid;
}

static OdDb3dSolidPtr createCylinder(OdDbDatabase* pDatabase, OdGeVector3d translate, double dAngle = 0.)
{
  OdDbRegionPtr pBase = createCircularRegion(pDatabase);

  OdDb3dSolidPtr pSolid = OdDb3dSolid::createObject();
  pSolid->setDatabaseDefaults(pDatabase);
  pSolid->setColorIndex(1);
  OdResult res = pSolid->extrude(pBase, 10);
  if (res != eOk)
  {
    return OdDb3dSolidPtr();
  }

  applyTransform(pSolid, translate, dAngle);
  return pSolid;
}

static void addToModelSpace(OdDbDatabase* pDatabase, OdDbEntity *pEntity)
{
  if (pDatabase && pEntity)
  {
    OdDbBlockTableRecordPtr pMs = pDatabase->getModelSpaceId().safeOpenObject(OdDb::kForWrite);
    pMs->appendOdDbEntity(pEntity);
  }
}

void _PipeDemo_func(OdEdCommandContext* pCmdCtx)
{
  // init 3d operations support
  checkModeler();

  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabase* pDatabase = pDbCmdCtx->database();

  // Lets create pipe from 8 pieces. 4 x 90 degree revolved solids and 4x extruded cylinders.

  OdDb3dSolidPtr pSolids[8];

  // create 90 degree revolved solid
  pSolids[0] = create90degree(pDatabase, OdGeVector3d(0, 0, 10));
  pSolids[2] = create90degree(pDatabase, OdGeVector3d(20, 0, 20), OdaPI2);
  pSolids[4] = create90degree(pDatabase, OdGeVector3d(30, 0, 0), OdaPI);
  pSolids[6] = create90degree(pDatabase, OdGeVector3d(10, 0, -10), OdaPI + OdaPI2);

  // create extruded cylinder
  pSolids[1] = createCylinder(pDatabase, OdGeVector3d::kIdentity);
  pSolids[3] = createCylinder(pDatabase, OdGeVector3d(30, 0, 0));
  pSolids[5] = createCylinder(pDatabase, OdGeVector3d(10, 0, 20), OdaPI2);
  pSolids[7] = createCylinder(pDatabase, OdGeVector3d(10, 0, -10), OdaPI2);

  // add copies of all 8 solids to model space
  for (OdUInt32 f = 0; f < 8; ++f)
  {
    pSolids[f]->transformBy(OdGeMatrix3d::rotation(OdaPI2, OdGeVector3d::kXAxis));
    addToModelSpace(pDatabase, OdDb3dSolidPtr(pSolids[f]->clone()));
  }

  // Boolean part:
  // Union all solids into single pipe 
  for (OdUInt32 f = 1; f < 8; ++f)
  {
    OdResult res = pSolids[0]->booleanOper(OdDb::kBoolUnite, pSolids[f]);
    if (res != eOk)
      return;
  }

  // add pipe to model space
  pSolids[0]->transformBy(OdGeMatrix3d::translation(OdGeVector3d(40, 0, 0)));
  addToModelSpace(pDatabase, pSolids[0]);
}
