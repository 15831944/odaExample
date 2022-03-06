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

#ifndef _ODDBPERSSUBENTMANAGERIMPL_INCLUDED_
#define _ODDBPERSSUBENTMANAGERIMPL_INCLUDED_

#include "DbPersSubentManager.h"
#include "DbObjectImpl.h"

using namespace OdTvDbHistoryInternal;

class OdTvDbPersSubentManagerImpl : public OdTvDbObjectImpl
{
  static OdTvDbPersSubentManagerImpl* getImpl(const OdTvDbPersSubentManager *pObj)
  { 
    return (OdTvDbPersSubentManagerImpl*)OdTvDbSystemInternals::getImpl(pObj);
  }  

  OdUInt32 m_iLastId;
  OdUInt32 m_iNumSubent;

  SubentRWDataArray m_subentDataRWArr;
  OdUInt32Array m_arrId;
  
public:
  OdTvDbPersSubentManagerImpl();

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);

  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  virtual void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  virtual void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  virtual OdResult parseSubentData(SubentDataArray& pData);

  //OdTvDbPersSubentManager(OdTvDbPersSubentManager const &)

  //Convert OdTvDbPersSubentManager data to OdTvDbAssocPersSubentManager data
  //void convertToAssocPersSubentManager();

  void cleanData();

protected:
  friend class OdTvDbPersSubentManager;
  friend class OdTvDbAssocPersSubentManagerImpl;
};

#endif //_ODDBPERSSUBENTMANAGERIMPL_INCLUDED_

