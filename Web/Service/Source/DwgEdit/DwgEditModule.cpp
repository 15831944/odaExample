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
//   This application incorporates Open Design Alliance software pursuant to a
//   license agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance.
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////
#include "OdaCommon.h"
#include "RxDynamicModule.h"
#include "RxObject.h"
#include "ExDynamicModule.h"
#include "DwgEditModule.h"
#include "RxVariantValue.h"
#include "DbGsManager.h"
#include "ColorMapping.h"
#include "TvModuleNames.h"
#include "DbBlockTableRecord.h"
#include "DbViewport.h"
#include "DbLine.h"
#include "ExEdBaseIO.h"
#include "DbDatabase.h"
#include "../../../../CommonApplications/Visualize/Examples/Dwg2Visualize/Dwg2Visualize.h"
#include "GiContextForDbDatabase.h"
#include "DwgHelper/DwgHelper.hpp"

#include <tuple>
#include "DbBlockReference.h"
#include "DbBlockTable.h"
#include "DbLayerTableRecord.h"
#include "DbLayerTable.h"

#include "IStreamOutput.hpp"

using namespace Oda;

void DwgEditModule::AddLine(OdEdCommandContext *ctx)
{
  DwgHelper dwgHelper;
  OdDbDatabase* pDb = dwgHelper.getDwgDatabase(ctx);
  {
    OdDbObjectId spaceId = activeBlockTableRecord(pDb);
    OdDbBlockTableRecordPtr pSpace = spaceId.safeOpenObject(OdDb::kForWrite);

    OdGeVector3d vNormal(ucsNormal(pDb));
    OdGePoint3d ptStart(100, 100, 0);
    OdGePoint3d ptEnd(-100, -100, 0);

    OdDbLinePtr pNewLine = OdDbLine::createObject();
    pNewLine->setDatabaseDefaults(pDb);
    pNewLine->setNormal(vNormal);
    pNewLine->setStartPoint(ptStart);
    pNewLine->setEndPoint(ptEnd);
    pSpace->appendOdDbEntity(pNewLine);
  }
  dwgHelper.invalidateAndUpdate(ctx);
}

void DwgEditModule::MoveToFront(OdEdCommandContext* ctx)
{
  DwgHelper dwgHelper;
  auto visDbId = dwgHelper.getVisualizeDbId(ctx);
  auto visDbPtr = visDbId->openObject();
  auto modelIterator = visDbPtr->getModelsIterator();
  auto madelId = modelIterator->getModel();
  auto modelPtr = madelId.openObject();
  auto entIter = modelPtr->getEntitiesIterator();
  auto ent = entIter->getEntity();
  OdArray<OdTvEntityId> entIdArr;
  entIdArr.append(ent);

  IStreamOutput* pStreamOutput = dwgHelper.getStreamOutput(ctx);
  pStreamOutput->orderModify(madelId, entIdArr, Order::MoveFront);
}

void DwgEditModule::MoveToBottom(OdEdCommandContext* ctx)
{
  DwgHelper dwgHelper;
  auto visDbId = dwgHelper.getVisualizeDbId(ctx);
  auto visDbPtr = visDbId->openObject();
  auto modelIterator = visDbPtr->getModelsIterator();
  auto madelId = modelIterator->getModel();
  auto modelPtr = madelId.openObject();
  auto entIter = modelPtr->getEntitiesIterator();
  auto ent = entIter->getEntity();
  OdArray<OdTvEntityId> entIdArr;
  entIdArr.append(ent);

  IStreamOutput* pStreamOutput = dwgHelper.getStreamOutput(ctx);
  pStreamOutput->orderModify(madelId, entIdArr, Order::MoveBottom);
}

void DwgEditModule::BindNativeHandlesWithVisualizeEntities(OdEdCommandContext* ctx)
{
  DwgHelper dwgHelper;
  dwgHelper.bindNativeHandlesWithVisualizeEntities(ctx);
}

void DwgEditModule::DeleteLine(OdEdCommandContext *ctx)
{
  DwgHelper dwgHelper;

  OdEdUserIO& io = *ctx->userIO();

  OdString strHandle = io.getString(L"handle(HEX)", OdEd::kInpNonNeg | OdEd::kInpThrowEmpty);

  OdDbDatabase* pDb = dwgHelper.getDwgDatabase(ctx);

  OdDbHandle handle(strHandle);
  auto objId = pDb->getOdDbObjectId(handle);
  if (!objId.isNull() && !objId.isErased())
  {
    objId.openObject(OdDb::kForWrite)->erase();
  }

  dwgHelper.invalidateAndUpdate(ctx);
}

void DwgEditModule::MoveLine(OdEdCommandContext *ctx)
{
  DwgHelper dwgHelper;

  OdEdUserIO& io = *ctx->userIO();

  OdString strHandle = io.getString(L"handle(HEX)", OdEd::kInpNonNeg | OdEd::kInpThrowEmpty);

  OdDbDatabase* pDb = dwgHelper.getDwgDatabase(ctx);

  OdDbHandle handle(strHandle);
  auto objId = pDb->getOdDbObjectId(handle);
  if (!objId.isNull() && !objId.isErased())
  {
    OdDbLinePtr line = objId.openObject(OdDb::kForWrite);
    OdGeMatrix3d matrix;
    matrix.setTranslation(OdGeVector3d::kXAxis*1.1);
    line->transformBy(matrix);
  }

  dwgHelper.invalidateAndUpdate(ctx);
}

void DwgEditModule::CreateLayer(OdEdCommandContext* ctx)
{
  DwgHelper dwgHelper;
  {
    OdDbDatabase* pDb = dwgHelper.getDwgDatabase(ctx);
    OdDbObjectId spaceId = activeBlockTableRecord(pDb);
    OdDbBlockTableRecordPtr pSpace = spaceId.safeOpenObject(OdDb::kForWrite);
    OdDbLayerTablePtr pOdLayerTable;
    OdDbLayerTableRecordPtr pODLayerTableRecord;
    pOdLayerTable = pDb->getLayerTableId().safeOpenObject(OdDb::kForWrite);
    if (!pOdLayerTable->has("testLayer"))
    {
      OdGeVector3d vNormal(ucsNormal(pDb));
      OdGePoint3d ptStart(100, 100, 0);
      OdGePoint3d ptEnd(-100, -100, 0);

      OdDbLinePtr pNewLine = OdDbLine::createObject();
      pNewLine->setDatabaseDefaults(pDb);
      pNewLine->setNormal(vNormal);
      pNewLine->setStartPoint(ptStart);
      pNewLine->setEndPoint(ptEnd);
      pSpace->appendOdDbEntity(pNewLine);
      auto nAutoCadColor = abs(1);
      pODLayerTableRecord = OdDbLayerTableRecord::createObject();
      pODLayerTableRecord->setName("testLayer");
      pODLayerTableRecord->setLineWeight(OdDb::LineWeight(0));
      pODLayerTableRecord->setColorIndex(nAutoCadColor);
      pODLayerTableRecord->setIsOff(false);

      pOdLayerTable->add(pODLayerTableRecord);
      pNewLine->setLayer(pODLayerTableRecord->objectId());
    }
  }
  dwgHelper.invalidateAndUpdate(ctx);
}

void DwgEditModule::switchDwgLayout(OdEdCommandContext* ctx)
{
  OdEdBaseIO* io = ctx->baseIO();

  DwgHelper dwgHelper;

  OdDbDatabase* pDb = dwgHelper.getDwgDatabase(ctx);  
  OdGsDevice* pOldDevice = dwgHelper.getImportDevice(ctx);

  pOldDevice->release();

  const OdString spaceName = io->getString("space name");

  if (!spaceName.isEmpty())
  {
    pDb->setCurrentLayout(spaceName);
  }

  std::tuple<OdTvDatabaseId*, OdGsDevice*> setupRes = dwgHelper.setupRuntimeImportDwgToVsf(pDb);

  dwgHelper.setDwgDatabase(ctx, pDb);
  dwgHelper.setImportDevice(ctx, std::get<1>(setupRes));
  dwgHelper.setVisualizeDbId(ctx, std::get<0>(setupRes));
}

void DwgEditModule::CreateBlockRef(OdEdCommandContext* ctx)
{
  DwgHelper dwgHelper;
  OdDbDatabase* pDb = dwgHelper.getDwgDatabase(ctx);
  {
    OdDbObjectId spaceId = activeBlockTableRecord(pDb);
    OdDbBlockTableRecordPtr pSpace = spaceId.safeOpenObject(OdDb::kForWrite);
    OdGeVector3d vNormal(ucsNormal(pDb));
    OdGePoint3d ptStart(100, 100, 0);
    OdGePoint3d ptEnd(-100, -100, 0);
    OdDbLinePtr pNewLine = OdDbLine::createObject();
    pNewLine->setDatabaseDefaults(pDb);
    pNewLine->setNormal(vNormal);
    pNewLine->setStartPoint(ptStart);
    pNewLine->setEndPoint(ptEnd);

    OdDbBlockTablePtr pTable = pDb->getBlockTableId().safeOpenObject(OdDb::kForWrite);
    OdDbBlockTableRecordPtr pRecord = OdDbBlockTableRecord::createObject();
    pRecord->setName(L"pRecord");
    pRecord->appendOdDbEntity(pNewLine);
    OdDbObjectId pRecordId = pTable->add(pRecord);

    OdDbBlockReferencePtr pBlkRef = OdDbBlockReference::createObject();
    pBlkRef->setDatabaseDefaults(pRecord->database());
    pBlkRef->setBlockTableRecord(pRecordId);
    pSpace->appendOdDbEntity(pBlkRef);
  }
  dwgHelper.invalidateAndUpdate(ctx);
}

void DwgEditModule::initApp() {

  OdEdCommandStackPtr regCmds = ::odedRegCmds();
  OdString cmd, grp = "DwgEdit";

  cmd = "AddLine";
  regCmds->addCommand(grp, cmd, cmd, 0, &AddLine);

  cmd = "MoveLine";
  regCmds->addCommand(grp, cmd, cmd, 0, &MoveLine);

  cmd = "DeleteLine";
  regCmds->addCommand(grp, cmd, cmd, 0, &DeleteLine);

  cmd = "switchLayout";
  regCmds->addCommand(grp, cmd, cmd, 0, &switchDwgLayout);

  cmd = "CreateBlockRef";
  regCmds->addCommand(grp, cmd, cmd, 0, &CreateBlockRef);

  cmd = "CreateLayer";
  regCmds->addCommand(grp, cmd, cmd, 0, &CreateLayer);
  
  cmd = "MoveToBottom";
  regCmds->addCommand(grp, cmd, cmd, 0, &MoveToBottom);

  cmd = "MoveToFront";
  regCmds->addCommand(grp, cmd, cmd, 0, &MoveToFront);

  cmd = "BindNativeHandlesWithVisualizeEntities";
  regCmds->addCommand(grp, cmd, cmd, 0, &BindNativeHandlesWithVisualizeEntities);
}

void DwgEditModule::uninitApp() {
  odUninitialize();
  ::odedRegCmds()->removeGroup("DwgEdit");
}

ODRX_DEFINE_DYNAMIC_MODULE(DwgEditModule);

OdDbObjectId activeBlockTableRecord(const OdDbDatabase* pDb)
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

OdGeVector3d ucsNormal(const OdDbDatabase * pDb)
{
  OdGeVector3d vNormal(OdGeVector3d::kZAxis);
  OdDbObjectId idSpace = activeBlockTableRecord(pDb);
  if (idSpace == pDb->getModelSpaceId())
  {
    OdDbObjectId idVp = pDb->activeViewportId();
    OdDbObjectPtr pVp(idVp.openObject());
    OdAbstractViewPEPtr pAVp(pVp);
    if (!pAVp.isNull())
    {
      OdGePoint3d ptOrigin;
      OdGeVector3d vX, vY;
      pAVp->getUcs(pVp, ptOrigin, vX, vY);
      vNormal = vX.crossProduct(vY).normalize();
    }
  }
  return vNormal;
}