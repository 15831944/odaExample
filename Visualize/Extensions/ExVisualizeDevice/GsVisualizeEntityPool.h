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

#ifndef __OD_GS_VISUALIZE_ENTITY_POOL__
#define __OD_GS_VISUALIZE_ENTITY_POOL__

#include "TD_PackPush.h"

#include "Gs/GsBaseInclude.h"
#include "TvFactory.h"

class ExGsVisualizeEntityPool
{
public:
  ExGsVisualizeEntityPool();
  virtual ~ExGsVisualizeEntityPool();

  void addEntity( OdTvModelId modelId, OdTvEntityId entityId, bool isInsert );
  bool getEntity( OdTvModelId modelId, OdTvEntityId& entityId, bool isInsert );

  OdUInt32 getModelCount() const { return m_entities.size(); }
  OdUInt32 getEntitiesCount( OdUInt32 nModel, bool isInsert ) const;
  OdTvModelId getModel( OdUInt32 nModel );
  OdTvEntityId getEntityByIndex( OdUInt32 nModel, OdUInt32 nEntity, bool isInsert );

  void clearAll();

protected:
  struct ModelEntities
  {
    OdTvModelId modelId;
    OdArray< OdTvEntityId > entities;
    OdArray< OdTvEntityId > inserts;
  };
  OdArray< ModelEntities > m_entities;
};



#include "TD_PackPop.h"

#endif // __OD_GS_VISUALIZE_ENTITY_POOL__
