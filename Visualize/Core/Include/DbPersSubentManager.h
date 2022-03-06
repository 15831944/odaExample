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

#ifndef _ODDBPERSSUBENTMANAGER_INCLUDED_
#define _ODDBPERSSUBENTMANAGER_INCLUDED_

#include "TD_PackPush.h"
#include "DbObject.h"
#include "ShHistory/DbManagerSubentData.h"
#include "ShHistory/TD_3DSolidHistoryDef.h"

/** \details
    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class DB3DSOLIDHISTORY_EXPORT OdTvDbPersSubentManager : public OdTvDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbPersSubentManager);

  OdTvDbPersSubentManager();
  virtual ~OdTvDbPersSubentManager();

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);

  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  //test method
  OdResult parseSubentData(SubentDataArray& pData);
  //test method
  OdUInt32 lastStepId();

  static OdTvDbObjectId getInstanceFromDatabase(OdTvDbDatabase const * pDatabase);
  static OdTvDbObjectId createIfItDoesNotExist(OdTvDbDatabase* pDatabase);
};

typedef OdSmartPtr<OdTvDbPersSubentManager> OdTvDbPersSubentManagerPtr;

#include "TD_PackPop.h"

#endif

