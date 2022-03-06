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

#ifndef _ODDBPOINTCLOUDDEFIMPL_INCLUDED_
#define _ODDBPOINTCLOUDDEFIMPL_INCLUDED_


#include "DbSystemInternals.h"
#include "DbPointCloudObj/DbPointCloudDef.h"
#include "DbPointCloudObj/DbPointCloudHostPE.h"
#include "Objects/DbObjectImpl.h"
#include "FileDependency.h"

class OdDbPointCloudDefImpl : public OdDbObjectImpl
{
public:
  OdDb::FileDependency m_FilePath;
  OdString            m_ActivePath;
  OdGeExtents3d       m_Extents;
  OdDbPointCloudItemPtr   m_pItem;
  OdUInt64            m_nPointsCount;
  bool                m_bLoaded;
  bool                m_bNotFound;

  OdDbPointCloudDefImpl();
  //void audit(OdDbAuditInfo* pAuditInfo);

  void unload()
  {
    m_bLoaded = false;
    m_bNotFound = false;
    m_pItem = NULL;
  }

  OdResult getItem(OdDbPointCloudDef*, OdDbPointCloudItemPtr&);

  static OdDbPointCloudDefImpl* getImpl(const OdDbPointCloudDef *pObj)
  { return (OdDbPointCloudDefImpl*)OdDbSystemInternals::getImpl(pObj);}

};

///////////////////////////////////////////////////////////////////////////////
class OdDbPointCloudDefReactorImpl : public OdDbObjectImpl
{
  friend class OdDbPointCloudDefReactor;
  static OdDbPointCloudDefReactorImpl* getImpl(const OdDbPointCloudDefReactor *pObj)
  { return (OdDbPointCloudDefReactorImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
  OdDbPointCloudDefReactorImpl() {}

};

class OdDbPointCloudHostPEDummyImpl : public OdDbPointCloudHostPE
{
public:
  OdDbPointCloudHostPEDummyImpl() {}
  ODRX_DECLARE_MEMBERS(OdDbPointCloudHostPEDummyImpl);

  virtual OdResult load(const OdString& strPath, OdDbPointCloudItemPtr& pItem);
};

#endif
