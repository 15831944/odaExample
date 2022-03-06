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

using namespace OdDbHistoryInternal;

class OdDbPersSubentManagerImpl : public OdDbObjectImpl
{
  static OdDbPersSubentManagerImpl* getImpl(const OdDbPersSubentManager *pObj)
  { 
    return (OdDbPersSubentManagerImpl*)OdDbSystemInternals::getImpl(pObj);
  }  

  OdUInt32 m_iLastId;
  OdUInt32 m_iNumSubent;

  SubentRWDataArray m_subentDataRWArr;
  OdUInt32Array m_arrId;
  
public:
  OdDbPersSubentManagerImpl();

  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);

  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);

  virtual void dxfOutFields(OdDbDxfFiler* pFiler) const;

  virtual void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  virtual void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  virtual OdResult parseSubentData(SubentDataArray& pData);

  //OdDbPersSubentManager(OdDbPersSubentManager const &)

  //Convert OdDbPersSubentManager data to OdDbAssocPersSubentManager data
  //void convertToAssocPersSubentManager();

  void cleanData();

protected:
  friend class OdDbPersSubentManager;
  friend class OdDbAssocPersSubentManagerImpl;
};

#endif //_ODDBPERSSUBENTMANAGERIMPL_INCLUDED_

