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

// ODA Platform
#include "OdaCommon.h"
#include "TvDatabaseUtils.h"

OdString OdTvDatabaseUtils::getFileNameFromPath(const OdString& filePath)
{
  OdString path = filePath;
  path.replace('/', '\\');
  OdString filename = path.mid(path.reverseFind('\\') + 1);
  OdString ext = filename.mid(filename.reverseFind('.'));
  filename.deleteChars(filename.find(ext), ext.getLength());
  filename.replace('.', '_');
  return filename;
}

void OdTvDatabaseUtils::writeFileNameToTvDatabase(const OdTvDatabaseId& dbId, const OdString& fileName)
{
  // get buffer
  const OdChar *pStr = fileName.c_str();
  
  //transfer to UTF-8
  OdAnsiString sAnsiUtf8(pStr, CP_UTF_8);
  const char* pUtf8Str = sAnsiUtf8.c_str();
  int size = sAnsiUtf8.getLength() + 1; //+1 for the trailing zero

  // create user data
  OdTvByteUserData *data = new OdTvByteUserData((void*)pUtf8Str, size, OdTvByteUserData::kCopyOwn, false);
 
  OdTvDatabasePtr pTvDb = dbId.openObject(OdTv::kForWrite);

  //register app
  bool alreadyExist = false;
  OdTvRegAppId regAppId = pTvDb->registerAppName(OD_T("Import to Visualize - name for save"), alreadyExist);
  
  // append user data to the database
  pTvDb->appendUserData(data, regAppId);
}

void OdTvDatabaseUtils::createDeviceAndView(const OdTvDatabaseId& dbId, const OdTvModelId& modelId, OdTvGsView::RenderMode renderMode, bool bAdvencedLightingSetup)
{
  OdTvDatabasePtr pTvDb = dbId.openObject(OdTv::kForWrite);

  OdTvGsDeviceId tvDeviceId = pTvDb->createDevice(OD_TV_COMMON_DEVICE_NAME);
  OdTvGsDevicePtr pDevice = tvDeviceId.openObject(OdTv::kForWrite);

  // create view
  OdTvGsViewId tvViewId = pDevice->createView(OD_TV_COMMON_VIEW_NAME);
  pDevice->addView(tvViewId);

  //setup view
  OdTvGsViewPtr pView = tvViewId.openObject(OdTv::kForWrite);
  pView->addModel(modelId);
  pView->setMode(renderMode);
  pView->setView(OdTvPoint(0., 0., 1.), OdTvPoint(0., 0., 0.), OdTvVector(0., 1., 0.), 1., 1.);
  pView->setActive(true);
  
  //setup lightng and backgound
  if (bAdvencedLightingSetup)
  {
    pView->enableDefaultLighting(true, OdTvGsView::kUserDefined);
    pView->setUserDefinedLightDirection(OdTvVector(0.5, 0.0, -1.0));
    pView->setDefaultLightingIntensity(1.4);
    pView->setAmbientLightColor(OdTvColorDef(50, 50, 50));
    pDevice->setBackgroundColor(ODRGB(33, 108, 170));
  }

  // since the GS is not setup yet,we can call empty zoom to extens to mark the view.
  // The action will be performed inside first setupGs
  OdTvPoint minPt, maxPt;
  pView->zoomExtents(minPt, maxPt);

}

OdString OdTvDatabaseUtils::generateModelName(OdTvDatabaseId databaseId, const OdString& fileName)
{
  OdString baseModelName, modelName;
  baseModelName = fileName + OD_T("_Model");
  OdUInt32 modelIndex = 0;
  bool bFound = true;
  while (bFound)
  {
    OdString sModelIndex;
    sModelIndex.format(OD_T("%d"), modelIndex);
    modelName = baseModelName + sModelIndex;

    bFound = false;
    OdTvModelsIteratorPtr modelsIterPtr = databaseId.openObject()->getModelsIterator();
    while (!modelsIterPtr->done())
    {
      OdString name = modelsIterPtr->getModel().openObject()->getName();
      if (modelName == name)
      {
        bFound = true;
        break;
      }

      modelsIterPtr->step();
    }
    if (bFound)
    {
      modelIndex++;
      bFound = true;
    }
  }

  return modelName;
}

bool OdTvDatabaseUtils::applyTransformToTheModel(OdTvDatabaseId& databaseId, const OdString& modelSpaceName, const OdTvMatrix& transform)
{
  if (transform == OdTvMatrix::kIdentity)
    return false;

  OdTvDatabasePtr pTvDb = databaseId.openObject();

  // Get new model
  OdTvModelId newModel;
  OdTvModelsIteratorPtr modelsIterPtr = pTvDb->getModelsIterator();
  while (!modelsIterPtr->done())
  {
    newModel = modelsIterPtr->getModel();
    OdString newModelName = newModel.openObject()->getName();

    modelsIterPtr->step();
    if (newModelName == modelSpaceName || modelsIterPtr->done())
      break;
  }

  if (newModel.isNull())
    return false;

  // transform the model
  OdTvModelPtr newModelPtr = newModel.openObject(OdTv::kForWrite);
  newModelPtr->setModelingMatrix(transform);

  return true;
}

void OdTvDatabaseUtils::collectViewsModelsAndBlocks(const OdTvDatabaseId& tvDbId, std::set<OdTvGsViewId>& foreignViews, std::set<OdTvModelId>& foreignModels, std::set<OdTvBlockId>& foreignBlocks)
{
  OdTvDatabasePtr pTvDb = tvDbId.openObject(OdTv::kForWrite);

  OdTvDevicesIteratorPtr pDevicesIterator = pTvDb->getDevicesIterator();
  while (!pDevicesIterator->done())
  {
    OdTvGsDeviceId deviceId = pDevicesIterator->getDevice();
    OdTvGsDevicePtr pDevice = deviceId.openObject(OdTv::kForWrite);

    for (int i = 0; i < pDevice->numViews(); i++)
    {
      OdTvGsViewId viewId = pDevice->viewAt(i);
      foreignViews.insert(viewId);
    }

    pDevicesIterator->step();
  }

  OdTvModelsIteratorPtr pModelsIterator = pTvDb->getModelsIterator();
  while (!pModelsIterator->done())
  {
    OdTvModelId modelId = pModelsIterator->getModel();
    pModelsIterator->step();
    foreignModels.insert(modelId);
  }

  OdTvBlocksIteratorPtr pBlocksIterator = pTvDb->getBlocksIterator();
  while (!pBlocksIterator->done())
  {
    OdTvBlockId blockId = pBlocksIterator->getBlock();
    pBlocksIterator->step();

    foreignBlocks.insert(blockId);
  }
}

void OdTvDatabaseUtils::markCDANode(OdRxModelTreeBaseNode* pNode)
{
  if (!pNode)
    return;
  OdRxModelTreeBaseNodePtr pNodePtr(pNode);
  OdTvCDATreeNodePtr pTvNode = pNodePtr;
  if (!pTvNode.isNull())
    pTvNode->setNeedGroup(false);

  OdRxModelTreeBaseNodePtrArray childs = pNode->getChildren();
  if (childs.isEmpty())
    return;

  for (OdRxModelTreeBaseNodePtrArray::iterator it = childs.begin(); it != childs.end(); ++it)
    markCDANode((*it).get());

  return;
}
