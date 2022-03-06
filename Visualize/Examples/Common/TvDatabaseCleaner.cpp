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

#include "TvDatabaseCleaner.h"
#include "TvInsert.h"


void OdTvDatabaseCleaner::cleanTvDatabase(OdTvDatabaseId& tvDbId)
{
  OdTvDatabasePtr pTvDb = tvDbId.openObject(OdTv::kForWrite);

  OdTvGsViewIdArray activeViews;

  OdTvDevicesIteratorPtr pDevicesIterator = pTvDb->getDevicesIterator();

  OdTvBlockIdSet blockArray;

  while (!pDevicesIterator->done())
  {
    OdTvGsDeviceId deviceId = pDevicesIterator->getDevice();
    OdTvGsDevicePtr pDevice = deviceId.openObject(OdTv::kForWrite);

    OdTvGsViewId activeViewId = pDevice->getActiveView();
    if (!activeViewId.isNull())
      activeViews.append(activeViewId);

    for (int i = pDevice->numViews() - 1; i >= 0; i--)
    {
      OdTvGsViewId viewId = pDevice->viewAt(i);
      OdTvGsViewPtr pView = viewId.openObject(OdTv::kForWrite);

      if (clearModelsLevel(pView, blockArray) && viewId != activeViewId)
      {
        pDevice->removeView(viewId);
      }
    }

    pDevicesIterator->step();
  }

  OdTvModelsIteratorPtr pModelsIterator = pTvDb->getModelsIterator();
  while (!pModelsIterator->done())
  {
    OdTvModelId modelId = pModelsIterator->getModel();
    pModelsIterator->step();

    OdTvModelPtr pModel = modelId.openObject(OdTv::kForWrite);
    if (clearEntitiesLevel(pModel, blockArray) && !modelIsFromActiveView(modelId, activeViews))
    {
      pTvDb->removeModel(modelId);
    }
  }

  OdTvBlocksIteratorPtr pBlocksIterator = pTvDb->getBlocksIterator();
  while (!pBlocksIterator->done())
  {
    OdTvBlockId blockId = pBlocksIterator->getBlock();
    pBlocksIterator->step();
    if( blockArray.find( blockId ) != blockArray.end() ) continue;
    if (clearEntitiesLevel(blockId.openObject(OdTv::kForWrite), blockArray))
    {
      pTvDb->removeBlock(blockId);
    }
  }
}


void OdTvDatabaseCleaner::cleanTvDatabaseForAppend(OdTvDatabaseId& tvDbId, std::set<OdTvGsViewId>& foreignViews,
                                                   std::set<OdTvModelId>& foreignModels, std::set<OdTvBlockId>& foreignBlocks)
{
  OdTvDatabasePtr pTvDb = tvDbId.openObject(OdTv::kForWrite);
  OdTvBlockIdSet blockArray;
  OdTvDevicesIteratorPtr pDevicesIterator = pTvDb->getDevicesIterator();
  while (!pDevicesIterator->done())
  {
    OdTvGsDeviceId deviceId = pDevicesIterator->getDevice();
    OdTvGsDevicePtr pDevice = deviceId.openObject(OdTv::kForWrite);

    for (int i = pDevice->numViews() - 1; i >= 0; i--)
    {
      OdTvGsViewId viewId = pDevice->viewAt(i);
      OdTvGsViewPtr pView = viewId.openObject(OdTv::kForWrite);

      if (clearModelsLevelForAppend(pView, foreignModels, blockArray) && foreignViews.find(viewId) == foreignViews.end())
      {
        pDevice->removeView(viewId);
      }
    }

    pDevicesIterator->step();
  }

  OdTvModelsIteratorPtr pModelsIterator = pTvDb->getModelsIterator();
  while (!pModelsIterator->done())
  {
    OdTvModelId modelId = pModelsIterator->getModel();
    pModelsIterator->step();

    if (foreignModels.find(modelId) == foreignModels.end())
    {
      OdTvModelPtr pModel = modelId.openObject(OdTv::kForWrite);
      if (clearEntitiesLevel(pModel, blockArray))
      {
        pTvDb->removeModel(modelId);
      }
    }
  }

  OdTvBlocksIteratorPtr pBlocksIterator = pTvDb->getBlocksIterator();
  while (!pBlocksIterator->done())
  {
    OdTvBlockId blockId = pBlocksIterator->getBlock();
    pBlocksIterator->step();

    if (foreignBlocks.find(blockId) == foreignBlocks.end() && blockArray.find(blockId) == blockArray.end())
    {
      if (clearEntitiesLevel(blockId.openObject(OdTv::kForWrite), blockArray))
      {
        pTvDb->removeBlock(blockId);
      }
    }
  }
}


bool OdTvDatabaseCleaner::clearModelsLevel(OdTvGsViewPtr pView, OdTvBlockIdSet& blockArray)
{
  bool bIsEmpty = true;

  for (int i = pView->numModels() - 1; i >= 0; i--)
  {
    OdTvModelId modelId = pView->modelAt(i);
    OdTvModelPtr pModel = modelId.openObject(OdTv::kForWrite);

    if (clearEntitiesLevel(pModel, blockArray) && !pView->getActive())
    {
      pView->eraseModel(modelId);
    }
    else
    {
      bIsEmpty = false;
    }
  }

  return bIsEmpty;
}

bool OdTvDatabaseCleaner::clearModelsLevelForAppend( OdTvGsViewPtr pView, std::set<OdTvModelId>& foreignModels, OdTvBlockIdSet& blockArray )
{
  bool bIsEmpty = true;

  for (int i = pView->numModels() - 1; i >= 0; i--)
  {
    OdTvModelId modelId = pView->modelAt(i);

    if (foreignModels.find(modelId) == foreignModels.end())
    {
      OdTvModelPtr pModel = modelId.openObject(OdTv::kForWrite);
      if (clearEntitiesLevel(pModel, blockArray))
      {
        pView->eraseModel(modelId);
      }
      else
      {
        bIsEmpty = false;
      }
    }
  }

  return bIsEmpty;
}


bool OdTvDatabaseCleaner::clearEntitiesLevel(OdTvModelPtr pModel, OdTvBlockIdSet& blockArray)
{
  bool bIsEmpty = true;
  OdTvEntitiesIteratorPtr pEntitiesIterator = pModel->getEntitiesIterator();
  while (!pEntitiesIterator->done())
  {
    OdTvEntityId entityId = pEntitiesIterator->getEntity();
    pEntitiesIterator->step();

    if (entityId.getType() == OdTvEntityId::kEntity)
    {
      OdTvEntityPtr pEntity = entityId.openObject(OdTv::kForWrite);
      if (clearGeometryLevel(pEntity))
      {
        pModel->removeEntity(entityId);
      }
      else
      {
        bIsEmpty = false;
      }
    }
    else if (entityId.getType() == OdTvEntityId::kInsert)
    {
      OdTvInsertPtr pInsert = entityId.openObjectAsInsert(OdTv::kForWrite);
      OdTvBlockPtr pBlock = pInsert->getBlock().openObject(OdTv::kForWrite);
      if( clearEntitiesLevel( pBlock, blockArray) )
      {
        if( pInsert->hasSubEntities() )
        {
          blockArray.insert( pInsert->getBlock() );
          bIsEmpty = false;
        }
        else
        {
          pModel->removeEntity(entityId);
        }
      }
      else
      {
        bIsEmpty = false;
      }
    }
    else
    {
      bIsEmpty = false;
    }
  }

  return bIsEmpty;
}

bool OdTvDatabaseCleaner::clearEntitiesLevel(OdTvBlockPtr pBlockl, OdTvBlockIdSet& blockArray)
{
  bool bIsEmpty = true;
  OdTvEntitiesIteratorPtr pEntitiesIterator = pBlockl->getEntitiesIterator();
  while (!pEntitiesIterator->done())
  {
    OdTvEntityId entityId = pEntitiesIterator->getEntity();
    pEntitiesIterator->step();

    if (entityId.getType() == OdTvEntityId::kEntity)
    {
      OdTvEntityPtr pEntity = entityId.openObject(OdTv::kForWrite);
      if (clearGeometryLevel(pEntity))
      {
        pBlockl->removeEntity(entityId);
      }
      else
      {
        bIsEmpty = false;
      }
    }
    else if (entityId.getType() == OdTvEntityId::kInsert)
    {
      OdTvInsertPtr pInsert = entityId.openObjectAsInsert(OdTv::kForWrite);
      OdTvBlockPtr pBlock = pInsert->getBlock().openObject(OdTv::kForWrite);
      if (clearEntitiesLevel(pBlock, blockArray))
      {
        if (pInsert->hasSubEntities())
        {
          blockArray.insert(pInsert->getBlock());
          bIsEmpty = false;
        }
        else
        {
          pBlockl->removeEntity(entityId);
        }
      }
      else
      {
        bIsEmpty = false;
      }
    }
    else
    {
      bIsEmpty = false;
    }
  }

  return bIsEmpty;
}

bool OdTvDatabaseCleaner::clearGeometryLevel(OdTvEntityPtr pEntity)
{
  bool bIsEmpty = true;
  OdTvGeometryDataIteratorPtr pGeometryIterator = pEntity->getGeometryDataIterator();
  while (!pGeometryIterator->done())
  {
    OdTvGeometryDataId geometryDataId = pGeometryIterator->getGeometryData();
    pGeometryIterator->step();

    if (geometryDataId.getType() == OdTv::kSubEntity)
    {
      OdTvEntityPtr pSubEntity = geometryDataId.openAsSubEntity(OdTv::kForWrite);
      if (clearGeometryLevel(pSubEntity))
      {
        pEntity->removeGeometryData(geometryDataId);
      }
      else
      {
        bIsEmpty = false;
      }
    }
    else
    {
      bIsEmpty = false;
    }
  }

  return bIsEmpty;
}


bool OdTvDatabaseCleaner::modelIsFromActiveView(OdTvModelId modelId, OdTvGsViewIdArray& activesViews)
{
  for (unsigned int i = 0; i < activesViews.size(); i++)
  {
    OdTvGsViewId activeView = activesViews[i];
    OdTvGsViewPtr pActiveView = activeView.openObject(OdTv::kForRead);

    for (int j = 0; j < pActiveView->numModels(); j++)
    {
      if (pActiveView->modelAt(j) == modelId)
        return true;
    }
  }

  return false;
}
