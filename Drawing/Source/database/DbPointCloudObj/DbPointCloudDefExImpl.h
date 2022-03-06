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
#ifndef _ODDBPOINTCLOUDDEFEXIMPL_INCLUDED_
#define _ODDBPOINTCLOUDDEFEXIMPL_INCLUDED_


#include "DbSystemInternals.h"
#include "DbPointCloudObj/DbPointCloudDefEx.h"
#include "DbPointCloudObj/DbPointCloudHostPE.h"
#include "Objects/DbObjectImpl.h"
#include "FileDependency.h"

class OdDbPointCloudDefExImpl : public OdDbObjectImpl
{
public:
  OdDb::FileDependency m_FilePath;
  OdString            m_ActivePath;
  OdGeExtents3d       m_Extents;
  OdDbPointCloudExItemPtr   m_pItem;
  OdUInt64            m_nPointsCount;
  bool                m_bLoaded;
  bool                m_bNotFound;

  OdDbPointCloudDefExImpl();
  //void audit(OdDbAuditInfo* pAuditInfo);

  void clear();

  void unload( )
  {
    m_bLoaded = false;
    m_bNotFound = false;
    m_pItem = NULL;
  }

  OdResult getItem(OdDbPointCloudExItemPtr& );

  static OdDbPointCloudDefExImpl* getImpl( const OdDbPointCloudDefEx *pObj )
  {
    return (OdDbPointCloudDefExImpl*)OdDbSystemInternals::getImpl( pObj );
  }

};

///////////////////////////////////////////////////////////////////////////////
class OdDbPointCloudDefReactorExImpl : public OdDbObjectImpl
{
  friend class OdDbPointCloudDefReactorEx;
  static OdDbPointCloudDefReactorExImpl* getImpl( const OdDbPointCloudDefReactorEx *pObj )
  {
    return (OdDbPointCloudDefReactorExImpl*)OdDbSystemInternals::getImpl( pObj );
  }

public:
  OdDbPointCloudDefReactorExImpl() {}

};

class OdDbPointCloudExHostPEDummyImpl : public OdDbPointCloudExHostPE
{
public:
  OdDbPointCloudExHostPEDummyImpl() {}
  ODRX_DECLARE_MEMBERS( OdDbPointCloudExHostPEDummyImpl );

  virtual OdResult loadRcs( const OdString& strPath, OdDbPointCloudExItemPtr& pItem );
  virtual OdResult loadRcp( const OdString& strPath, OdDbPointCloudExItemPtr& pItem );
};

#endif //_ODDBPOINTCLOUDDEFEXIMPL_INCLUDED_
