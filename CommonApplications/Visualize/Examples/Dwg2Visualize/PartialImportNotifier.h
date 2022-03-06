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

#ifndef _TV_PARTIALIMPORTNOTIFIER_H_
#define _TV_PARTIALIMPORTNOTIFIER_H_

#include "TD_PackPush.h"

#define STL_USING_SET
#include <set>

#include "DwgImportNotifier.h"

class OdTvPartialImportNotifier : public OdTvEmptyNotifier
{
  public:
  //entities
  virtual void entityVectorizationDone( const OdTvEntityId& entityId );
  virtual void insertVectorizationDone( const OdTvEntityId& insertId );

  virtual void blockCreated( const OdTvBlockId& blockId );
  virtual void blockVectorizationBegin( const OdTvBlockId& blockId );
  virtual void blockVectorizationDone( const OdTvBlockId& blockId );

  //Models
  virtual void modelCreated( const OdTvModelId& modelId );
  virtual void modelActivated( const OdTvModelId& modelId );

  //update
  virtual void updateBegins(){}
  virtual void updateEnds(){}

  //Other
  void setBlockTableEntitiesCount( OdDbStub* id, OdUInt32 nCount );
  void setProgressMeter( OdDbHostAppProgressMeter* pMeter )
  {
    m_pMeter = pMeter;
  }

  bool abortImport() const;
  void setImportAbort( OdTvLowMemoryImportAbort* );

public:

  OdTvPartialImportNotifier( OdTvDatabasePtr pDb, bool bAddPartialIndex = true, bool bClearEmptySubEntities = false);
  virtual ~OdTvPartialImportNotifier();

  void setLimitManager( OdTvLimitManager* pManager ) { m_pLimitManager = pManager; }

  void unloadCachedEntities();

  void clearProcessedMaps();

protected:
  struct ParentDescr
  {
    OdTvModelId m_model;
    OdTvBlockId m_block;
    bool m_bIsBlock;
    ParentDescr()
    {
      m_model.setNull();
      m_block.setNull();
      m_bIsBlock = false;
    }
  };
  OdStack< ParentDescr > m_parents;
  OdTvDatabasePtr m_pDatabase;

  bool m_bAddPartialIndex;

  OdTvLimitManager* m_pLimitManager;

  OdVector< OdTvEntityId > m_entitiesToUnload;

  std::set< OdDbStub* > m_processedBlocks;
  OdUInt32 m_nEntitiesEstimation;
  OdUInt32 m_nCurrentObject;
  OdDbHostAppProgressMeter* m_pMeter;
  bool m_bClearEmptySubEntities;
  OdTvLowMemoryImportAbort* m_pAbort;
};

#include "TD_PackPop.h"

#endif
