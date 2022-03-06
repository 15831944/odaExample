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
#include "BooleanCommand.h"

#include "DbDatabase.h"
#include "DbEntity.h"
#include "DbCommandContext.h"
#include "DbSSet.h"
#include "DbBlockTableRecord.h"
#include "DbBlockReference.h"
#include "DbHostAppServices.h"
#include "Ge/GeScale3d.h"
#include "DbErrorInvalidSysvar.h"
#include "SysVarInfo.h"
#include "StaticRxObject.h"
#include "DbUserIO.h"
#include "DbRegion.h"
#include "DbBody.h"
#include "Db3dSolid.h"
#include "DbSurface.h"
#include "Br/BrBrep.h"
#include "DbViewport.h"

class BooleanFilter : public OdStaticRxObject<OdEdSSetTracker>
{
public:
  bool allowDbBody;
  bool allowMesh;
  BooleanFilter()
    : allowDbBody(false)
    , allowMesh(false)
  {}

  int addDrawables(OdGsView*) ODRX_OVERRIDE { return 0; }
  void removeDrawables(OdGsView*) ODRX_OVERRIDE {}

  bool check(const OdDbObjectId& entId)
  {
    OdDbEntityPtr pEnt = entId.openObject();
    return !pEnt.isNull() && (pEnt->isKindOf(OdDbRegion::desc()) || pEnt->isKindOf(OdDb3dSolid::desc()) ||
      pEnt->isKindOf(OdDbSurface::desc()) || allowDbBody && pEnt->isKindOf(OdDbBody::desc()) ||
      allowMesh && pEnt->isKindOf(OdDbSubDMesh::desc()));
  }

  bool append(const OdDbObjectId& entId, const OdDbSelectionMethod*)
  {
    return check(entId);
  }

  bool remove(const OdDbObjectId& entId, const OdDbSelectionMethod*)
  {
    return check(entId);
  }
};

static bool unionEntities(OdDbCommandContext* pDbCmdCtx, OdDbUserIO* pIO, OdDbSelectionSet* pSet,
  OdDb3dSolidPtr& pResultSolid, OdDbSurfacePtr& pResultSurface, OdDbRegionPtr& pResultRegion)
{
  ODA_ASSERT(pResultSolid.isNull() && pResultSurface.isNull() && pResultRegion.isNull());

  OdDbSelectionSetIteratorPtr pIter;
  for (pIter = pSet->newIterator(); !pIter->done(); pIter->next())
  {
    OdDbObjectId objId = pIter->objectId();
    OdDbEntityPtr pEnt = objId.openObject(OdDb::kForWrite);
    if (pEnt.isNull())
      continue;
    if (pEnt->isKindOf(OdDb3dSolid::desc()))
    {
      if (pResultSolid.isNull())
        pResultSolid = OdDb3dSolidPtr(pEnt);
      else
      {
        OdResult res = pResultSolid->booleanOper(OdDb::kBoolUnite, OdDb3dSolidPtr(pEnt));
        if (res != eOk)
        {
          ODA_FAIL();
          pIO->putString(OD_T("Boolean union failed."));
          return false;
        }
        pEnt->erase();
      }
    }
    else if (pEnt->isKindOf(OdDbRegion::desc()))
    {
      if (pResultRegion.isNull())
        pResultRegion = OdDbRegionPtr(pEnt);
      else
      {
        OdResult res = pResultRegion->booleanOper(OdDb::kBoolUnite, OdDbRegionPtr(pEnt));
        if (res != eOk)
        {
          ODA_FAIL();
          pIO->putString(OD_T("Boolean union failed."));
          return false;
        }
        pEnt->erase();
      }
    }
    else if (pEnt->isKindOf(OdDbSurface::desc()))
    {
      if (pResultSurface.isNull())
        pResultSurface = OdDbSurfacePtr(pEnt);
      else
      {
        OdDbDatabase* pDatabase = pDbCmdCtx->database();
        OdDbBlockTableRecordPtr pMs = pDatabase->getModelSpaceId().safeOpenObject(OdDb::kForWrite);

        OdDbSurfacePtr pNewSurf;
        OdResult res = pResultSurface->booleanUnion(OdDbSurfacePtr(pEnt), pNewSurf);
        if (res != eOk)
        {
          ODA_FAIL();
          pIO->putString(OD_T("Boolean union failed."));
          return false;
        }
        pEnt->erase();
        if (!pNewSurf.isNull())
        {
          pMs->appendOdDbEntity(pNewSurf);
          pResultSurface->erase();
          pResultSurface = pNewSurf;
        }
      }
    }
  }
  return true;
}

void UnionCommand::execute(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbUserIOPtr pIO = pDbCmdCtx->dbUserIO();

  BooleanFilter filter;
  OdDbSelectionSetPtr pSet = pIO->select(OD_T("Select objects:"), OdEd::kSelDefault, 0, OdString::kEmpty, &filter);

  OdDb3dSolidPtr pResultSolid;
  OdDbSurfacePtr pResultSurface;
  OdDbRegionPtr pResultRegion;
  unionEntities(pDbCmdCtx, pIO, pSet, pResultSolid, pResultSurface, pResultRegion);
}

void IntersectSurfCommand::execute(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbUserIOPtr pIO = pDbCmdCtx->dbUserIO();
  OdDbDatabase* pDatabase = pDbCmdCtx->database();
  OdDbBlockTableRecordPtr pMs = pDatabase->getModelSpaceId().safeOpenObject(OdDb::kForWrite);

  BooleanFilter filter;
  OdDbSelectionSetPtr pSet = pIO->select(OD_T("Select surface:"), OdEd::kSelDefault, 0, OdString::kEmpty, &filter);
  OdDbSelectionSetPtr pSet2 = pIO->select(OD_T("Select second object:"), OdEd::kSelDefault, 0, OdString::kEmpty, &filter);

  if (pSet->numEntities() < 2 && pSet2->numEntities() < 2)
  {
    OdDbSelectionSetIteratorPtr pIter = pSet->newIterator();
    OdDbSelectionSetIteratorPtr pIter2 = pSet2->newIterator();

    if (pIter->done() || pIter2->done())
      return;

    OdDbObjectId objId = pIter->objectId();
    OdDbEntityPtr pEnt = objId.openObject(OdDb::kForWrite);
    OdDbObjectId objId2 = pIter2->objectId();
    OdDbEntityPtr pEnt2 = objId2.openObject(OdDb::kForWrite);

    if (!pEnt.isNull() && !pEnt2.isNull() && pEnt->isKindOf(OdDbSurface::desc()) &&
      (pEnt2->isKindOf(OdDbSurface::desc()) || pEnt2->isKindOf(OdDb3dSolid::desc()) || pEnt2->isKindOf(OdDbRegion::desc()) || pEnt2->isKindOf(OdDbBody::desc())))
    {
      OdDbEntityPtrArray entArr;
      OdResult res = OdDbSurface::cast(pEnt)->createInterferenceObjects(entArr, pEnt2, 0);

      if (res != eOk && res != eNoIntersections)
        return;

      pEnt->erase();
      pEnt2->erase();
      for (unsigned i = 0; i < entArr.length(); ++i)
      {
        pMs->appendOdDbEntity(entArr[i]);
      }
    }
    else
    {
      pIO->putString(OD_T("Wrong objects types."));
    }
  }
  else
  {
    pIO->putString(OD_T("Too many objects selected."));
  }
}

void IntersectCommand::execute(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbUserIOPtr pIO = pDbCmdCtx->dbUserIO();

  BooleanFilter filter;
  OdDbSelectionSetPtr pSet = pIO->select(OD_T("Select objects:"), OdEd::kSelDefault, 0, OdString::kEmpty, &filter);

  if (pSet->numEntities() >= 2)
  {
    OdDbSelectionSetIteratorPtr pIter;
    OdDbRegionPtr pMainReg;
    OdDb3dSolidPtr pMainSolid;
    OdDbSurfacePtr pMainSurf;
    for (pIter = pSet->newIterator(); !pIter->done(); pIter->next())
    {
      OdDbObjectId objId = pIter->objectId();
      OdDbEntityPtr pEnt = objId.openObject(OdDb::kForWrite);
      if (pEnt.isNull())
        continue;
      if (pEnt->isKindOf(OdDb3dSolid::desc()))
      {
        if (pMainSolid.isNull())
          pMainSolid = OdDb3dSolid::cast(pEnt);
        else
        {
          if (!pMainSolid->isNull())
          {
            OdResult res = pMainSolid->booleanOper(OdDb::kBoolIntersect, OdDb3dSolid::cast(pEnt));
            if (res != eOk && res != eNoIntersections)
            {
              ODA_FAIL();
              pIO->putString(OD_T("Boolean intersect failed."));
              return;
            }
          }
          pEnt->erase();
        }
      }
      if (pEnt->isKindOf(OdDbRegion::desc()))
      {
        if (pMainReg.isNull())
          pMainReg = OdDbRegion::cast(pEnt);
        else
        {
          if (!pMainReg->isNull())
          {
            OdResult res = pMainReg->booleanOper(OdDb::kBoolIntersect, OdDbRegion::cast(pEnt));
            if (res != eOk && res != eNoIntersections)
            {
              ODA_FAIL();
              pIO->putString(OD_T("Boolean intersect failed."));
              return;
            }
          }
          pEnt->erase();
        }
      }
      if (pEnt->isKindOf(OdDbSurface::desc()))
      {
        if (pMainSurf.isNull())
          pMainSurf = OdDbSurface::cast(pEnt);
        else
        {
          OdDbDatabase* pDatabase = pDbCmdCtx->database();
          OdDbBlockTableRecordPtr pMs = pDatabase->getModelSpaceId().safeOpenObject(OdDb::kForWrite);

          OdDbEntityPtrArray intersectionEntities;
          OdResult res = pMainSurf->booleanIntersect(OdDbSurface::cast(pEnt), intersectionEntities);
          if (res != eOk && res != eNoIntersections)
          {
            ODA_FAIL();
            pIO->putString(OD_T("Boolean intersect failed."));
            return;
          }
          pEnt->erase();
          if (res == eNoIntersections)
          {
            pMainSurf->erase();
          }
          if (intersectionEntities.size() >= 1)
          {
            pMainSurf->erase();
            for (unsigned i = 0; i < intersectionEntities.size(); ++i)
            {
              pMs->appendOdDbEntity(intersectionEntities[i]);
            }
            if (intersectionEntities[0]->isKindOf(OdDbSurface::desc()))
            {
              ODA_ASSERT_ONCE(intersectionEntities.size() == 1);
              pMainSurf = intersectionEntities[0];
            }
          }
        }
      }
    }
    if (!pMainSurf.isNull() && !pMainSolid.isNull())
    {
      OdDbDatabase* pDatabase = pDbCmdCtx->database();
      OdDbBlockTableRecordPtr pMs = pDatabase->getModelSpaceId().safeOpenObject(OdDb::kForWrite);

      OdDbEntityPtrArray intersectionEntities;
      OdResult res = pMainSurf->booleanIntersect(pMainSolid, intersectionEntities);
      if (res != eOk && res != eNoIntersections)
      {
        ODA_FAIL();
        pIO->putString(OD_T("Boolean intersect failed."));
        return;
      }
      pMainSolid->erase();
      if (res == eNoIntersections)
      {
        pMainSurf->erase();
      }
      if (intersectionEntities.size() >= 1)
      {
        pMainSurf->erase();
        for (unsigned i = 0; i < intersectionEntities.size(); ++i)
        {
          pMs->appendOdDbEntity(intersectionEntities[i]);
        }
      }
    }
  }
}

OdDbObjectId booleanActiveBlockTableRecord(const OdDbDatabase* pDb)
{
  OdDbObjectId idSpace = pDb->getActiveLayoutBTRId();
  if (idSpace == pDb->getPaperSpaceId())
  {
    OdDbViewportPtr pVp = pDb->activeViewportId().safeOpenObject();
    if (pVp->number() > 1)
      idSpace = pDb->getModelSpaceId();
  }
  return idSpace;
}

class BooleanExTracker : public OdStaticRxObject<OdEdPointTracker>
{
public:

  OdDbDatabasePtr m_pDb;
  OdGsView       *m_pGsView;

  OdDbEntityPtr      m_booleanResult;
  const OdDbEntity*  m_pEnt1;
  OdDbEntityPtr      m_pEnt2;
  OdDb::BoolOperType m_operation;

  OdGePoint3d getEnt2Point() const
  {
    OdGeExtents3d extents;
    m_pEnt2->getGeomExtents(extents);
    return extents.isValidExtents() ? extents.center() : OdGePoint3d::kOrigin;
  }

public:
  BooleanExTracker(OdDbDatabasePtr pDb, OdDbEntityPtr pEnt1, OdDbEntityPtr pEnt2, OdDb::BoolOperType operation)
    : m_pDb(pDb)
    , m_pGsView(NULL)
    , m_operation(operation)
  {
    if (pEnt1.isNull() || pEnt2.isNull()) return;

    m_pEnt1 = pEnt1;
    m_pEnt2 = pEnt2->clone();
  }

  void setValue(const OdGePoint3d& pt) ODRX_OVERRIDE
  {
    if (m_pEnt1 == NULL) return;

    if (m_pGsView)
    {
      removeDrawables(m_pGsView);
    }

    m_booleanResult = m_pEnt1->clone();

    OdGePoint3d basePoint = getEnt2Point();

    OdGeVector3d v = pt - basePoint;
    OdGeMatrix3d mx = OdGeMatrix3d::translation(v);
    m_pEnt2->transformBy(mx);
    OdDbEntityPtr pTmpEnt = m_pEnt2->clone();
    OdResult res;
    if (m_booleanResult->isKindOf(OdDb3dSolid::desc()) && pTmpEnt->isKindOf(OdDb3dSolid::desc()))
    {
      res = OdDb3dSolid::cast(m_booleanResult)->booleanOper(m_operation, OdDb3dSolid::cast(pTmpEnt));
    }
    else if (m_booleanResult->isKindOf(OdDbRegion::desc()) && pTmpEnt->isKindOf(OdDbRegion::desc()))
    {
      res = OdDbRegion::cast(m_booleanResult)->booleanOper(m_operation, OdDbRegion::cast(pTmpEnt));
    }
    else
      return;
    if (res == eOk)
    {
      OdGeExtents3d ext;
      m_booleanResult->getGeomExtents(ext);
      if (ext.isValidExtents())
      {
        m_booleanResult->setColorIndex(4);
      }
      else
      {
        m_booleanResult.release();
      }
    }
    else
    {
      m_booleanResult.release();
    }

    if (m_pGsView)
    {
      removeDrawables(m_pGsView);
      addDrawables(m_pGsView);
    }
  }

  int addDrawables(OdGsView* pView) ODRX_OVERRIDE
  {
    m_pGsView = pView;

    if (!m_pEnt2.isNull())
    {
      pView->add(m_pEnt2, 0);
    }

    if (!m_booleanResult.isNull())
    {
      pView->add(m_booleanResult, 0);
    }

    return 1;
  }

  void removeDrawables(OdGsView* pView) ODRX_OVERRIDE
  {
    if (!pView) return;

    // do not reset m_pGsView, need little later
    if (!m_booleanResult.isNull()) pView->erase(m_booleanResult);
    if (!m_pEnt2.isNull()) pView->erase(m_pEnt2);
  }

  void invalidate()
  {
    if (!m_pGsView) return;

    OdGsDevice* pDevice = m_pGsView->device();
    if (pDevice)
    {
      pDevice->invalidate();
      pDevice->update();
    }
  }
};

void BooleanExCommand::execute(OdEdCommandContext* pCmdCtx, OdDb::BoolOperType operationType)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabasePtr pDb = pDbCmdCtx->database();
  OdDbUserIO* pIO = pDbCmdCtx->dbUserIO();

  OdDbObjectIdArray objectIdsArray = OdDbSelectionSet::cast(pIO->select(L"", OdEd::kSelAllowObjects | OdEd::kSelAllowInactSpaces).get())->objectIdArray();

  if (objectIdsArray.size() < 2)
  {
    pIO->putString(OD_T("Two entities should be selected."));
    return;
  }

  OdDbEntityPtr pEnt1 = objectIdsArray[0].openObject(OdDb::kForWrite);
  OdDbEntityPtr pEnt2 = objectIdsArray[1].openObject(OdDb::kForWrite);

  {
    BooleanExTracker heightTracker(pDb, pEnt1, pEnt2, operationType);

    try
    {
      OdGePoint3d point = pIO->getPoint(OD_T("Move second entity."),
        OdEd::kGptNoUCS | OdEd::kInpThrowOther | OdEd::kInpThrowEmpty,
        0, OD_T(""), &heightTracker);
    }
    catch (const OdEdKeyword& )
    {
      heightTracker.invalidate();
    }
    catch (const OdEdOtherInput& other)
    {
      heightTracker.invalidate();
      if (other.string().isEmpty()) return;
    }
    catch (const OdEdCancel& )
    {
      pIO->putString(OD_T("Canceled."));
      return;
    }

    pEnt1->erase();
    pEnt2->erase();

    if (!heightTracker.m_booleanResult.isNull())
    {
      OdDbBlockTableRecordPtr pSpace = booleanActiveBlockTableRecord(pDb).openObject(OdDb::kForWrite);
      pSpace->appendOdDbEntity(heightTracker.m_booleanResult);
    }
  }
}

void SubtractCommand::execute(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbUserIOPtr pIO = pDbCmdCtx->dbUserIO();

  BooleanFilter filter;
  OdDbSelectionSetPtr pSet = pIO->select(OD_T("Select objects:"), OdEd::kSelDefault, 0, OdString::kEmpty, &filter);
  OdDbSelectionSetPtr pSet2 = pIO->select(OD_T("Select objects:"), OdEd::kSelDefault, 0, OdString::kEmpty, &filter);

  //remove duplicates
  OdDbSelectionSetIteratorPtr pIter;
  for (pIter = pSet->newIterator(); !pIter->done(); pIter->next())
  {
    OdDbObjectId objId = pIter->objectId();
    OdDbSelectionSetIteratorPtr pIter2;
    for (pIter2 = pSet2->newIterator(); !pIter2->done(); pIter2->next())
    {
      if (objId == pIter2->objectId())
      {
        pSet2->remove(pIter2->objectId());
        break;
      }
    }
  }
  if (pSet->numEntities() == 0 || pSet2->numEntities() == 0)
  {
    pIO->putString(OD_T("Empty set."));
    return;
  }

  //union entities from the first set
  OdDb3dSolidPtr pResultSolid;
  OdDbSurfacePtr pResultSurface;
  OdDbRegionPtr pResultRegion;
  if (!unionEntities(pDbCmdCtx, pIO, pSet, pResultSolid, pResultSurface, pResultRegion))
    return;

  //perform subtraction
  OdDbSelectionSetIteratorPtr pIter2;
  for (pIter2 = pSet2->newIterator(); !pIter2->done(); pIter2->next())
  {
    OdDbObjectId objId2 = pIter2->objectId();
    OdDbEntityPtr pEnt2 = objId2.openObject(OdDb::kForWrite);
    if (pEnt2.isNull())
      continue;
    if (pEnt2->isKindOf(OdDb3dSolid::desc()))
    {
      if (!pResultSolid.isNull())
      {
        OdResult res = pResultSolid->booleanOper(OdDb::kBoolSubtract, OdDb3dSolid::cast(pEnt2));
        if (res != eOk && res != eNoIntersections)
        {
          ODA_FAIL();
          pIO->putString(OD_T("Boolean subtract failed."));
          continue;
        }
      }
      if (!pResultSurface.isNull())
      {
        OdDbDatabase* pDatabase = pDbCmdCtx->database();
        OdDbBlockTableRecordPtr pMs = pDatabase->getModelSpaceId().safeOpenObject(OdDb::kForWrite);

        OdDbSurfacePtr pNewSurf;
        OdResult res = pResultSurface->booleanSubtract(OdDb3dSolid::cast(pEnt2), pNewSurf);
        if (res != eOk && res != eNoIntersections)
        {
          ODA_FAIL();
          pIO->putString(OD_T("Boolean subtract failed."));
          return;
        }
        if (res == eNoIntersections)
        {
          pResultSurface->erase();
          pResultSurface = NULL;
        }
        if (!pNewSurf.isNull())
        {
          pMs->appendOdDbEntity(pNewSurf);
          pResultSurface->erase();
          pResultSurface = pNewSurf;
        }
      }
      pEnt2->erase();
    }
    else if (pEnt2->isKindOf(OdDbRegion::desc()))
    {
      if (!pResultRegion.isNull())
      {
        OdResult res = pResultRegion->booleanOper(OdDb::kBoolSubtract, OdDbRegion::cast(pEnt2));
        if (res != eOk && res != eNoIntersections)
        {
          ODA_FAIL();
          pIO->putString(OD_T("Boolean subtract failed."));
          return;
        }
      }
      pEnt2->erase();
    }
    else if (pEnt2->isKindOf(OdDbSurface::desc()))
    {
      if (!pResultSurface.isNull())
      {
        OdDbDatabase* pDatabase = pDbCmdCtx->database();
        OdDbBlockTableRecordPtr pMs = pDatabase->getModelSpaceId().safeOpenObject(OdDb::kForWrite);

        OdDbSurfacePtr pNewSurf;
        OdResult res = pResultSurface->booleanSubtract(OdDbSurface::cast(pEnt2), pNewSurf);
        if (res == eNoIntersections)
        {
          pResultSurface->erase();
          pResultSurface = NULL;
        }
        if (res != eOk && res != eNoIntersections)
        {
          ODA_FAIL();
          pIO->putString(OD_T("Boolean subtract failed."));
          return;
        }
        if (!pNewSurf.isNull())
        {
          pMs->appendOdDbEntity(pNewSurf);
          pResultSurface->erase();
          pResultSurface = pNewSurf;
        }
      }
      pEnt2->erase();
    }
  }
}

void SculptCommand::execute(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbUserIOPtr pIO = pDbCmdCtx->dbUserIO();

  BooleanFilter filter;
  filter.allowDbBody = true;
  filter.allowMesh = true;
  OdDbSelectionSetPtr pSet = pIO->select(OD_T("Select objects:"), OdEd::kSelDefault, 0, OdString::kEmpty, &filter);

  //ACAD 2020 doesn't perform sculpt command for a single solid with "Solid creation failed, no watertight volume detected."
  //However, this message is incorrect. Also createSculptedSolid makes sense and may be non trivial, e.g., for a solid with holes.
  if (pSet->numEntities() >= 1)
  {
    OdDbEntityPtrArray entities;
    OdDbSelectionSetIteratorPtr pIter;
    for (pIter = pSet->newIterator(); !pIter->done(); pIter->next())
    {
      OdDbObjectId objId = pIter->objectId();
      OdDbEntityPtr pEnt = objId.openObject(OdDb::kForWrite);
      //already filtered in BooleanFilter
      ODA_ASSERT(!pEnt.isNull() && (pEnt->isKindOf(OdDb3dSolid::desc()) || pEnt->isKindOf(OdDbRegion::desc()) ||
        pEnt->isKindOf(OdDbSurface::desc()) || pEnt->isKindOf(OdDbBody::desc()) || pEnt->isKindOf(OdDbSubDMesh::desc())));
      entities.append(pEnt);
    }
    if (entities.empty())
    {
      return;
    }

    //convert meshes to surfaces
    for (unsigned entityIdx = 0; entityIdx < entities.size(); ++entityIdx)
    {
      OdDbEntityPtr pEnt = entities[entityIdx];
      if (pEnt->isKindOf(OdDbSubDMesh::desc()))
      {
        OdDbSurfacePtr pSurf;
        //TODO (CORE-12444): SMOOTHMESHCONVERT should be used, but it is not implemented yet.
        OdResult res = OdDbSubDMesh::cast(pEnt)->convertToSurface(false, false, pSurf);
        if (res == eOk)
        {
          ODA_ASSERT_ONCE(!pSurf.isNull());
          pEnt->erase();
          entities[entityIdx] = pSurf;
        }
        else
        {
          pIO->putString(OD_T("Failed to convert mesh to surface."));
          return;
        }
      }
    }

    OdDb3dSolidPtr sculptSolid = OdDb3dSolid::createObject();
    OdGeIntArray limitingFlags;
    OdResult res = sculptSolid->createSculptedSolid(entities, limitingFlags);
    if (res != eOk)
    {
      pIO->putString(OD_T("Solid creation failed, no watertight volume created."));
      return;
    }

    for (unsigned entityIdx = 0; entityIdx < entities.size(); ++entityIdx)
    {
      entities[entityIdx]->erase();
    }
    OdDbDatabase* pDatabase = pDbCmdCtx->database();
    OdDbBlockTableRecordPtr pMs = pDatabase->getModelSpaceId().safeOpenObject(OdDb::kForWrite);
    pMs->appendOdDbEntity(sculptSolid);
  }
}
