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

#ifndef _ODDBSYNERGYIMPL_INCLUDED_
#define _ODDBSYNERGYIMPL_INCLUDED_

#include "DbSynergy.h"
#include "DbObjectImpl.h"

#define STL_USING_MAP
#include "OdaSTL.h"

class OdDbIdwSheetImpl
{
public:
  //OdUInt64 m_viewId;
  OdDbObjectId m_viewRepId;
  OdDbObjectId m_viewportId;
};

class OdDbIdwSheetMappingImpl
{
public:
  //OdUInt32 m_idwSheetId;
  OdDbObjectId m_layoutId;

  std::map<OdUInt64, // viewId
           OdDbIdwSheetImpl> m_mapIdwSheetImpl;
};

class OdDbSynergyMappingsImpl : public OdDbObjectImpl
{
private:
  friend class OdDbSynergyMappings;

  static OdDbSynergyMappingsImpl* getImpl(const OdDbSynergyMappings* pObj)
  { 
    return (OdDbSynergyMappingsImpl*) OdDbSystemInternals::getImpl(pObj);
  }
  OdDbSynergyMappingsImpl();

  std::map<OdUInt32, // idwSheetId
           OdDbIdwSheetMappingImpl> m_mapSheets;

  std::map<OdUInt16, // enum OdSynergyObj::ViewEdgeLayerStyleType
           OdDbObjectId> m_mapLayerIds;
};

//class OdDbSynergyBulletinImpl : public OdDbObjectImpl
//{
//private:
//  friend class OdDbSynergyBulletin;
//
//  static OdDbSynergyBulletinImpl* getImpl(const OdDbSynergyBulletin* pObj)
//  { 
//    return (OdDbSynergyBulletinImpl*) OdDbSystemInternals::getImpl(pObj);
//  }
//  OdDbSynergyBulletinImpl();
//};

#endif // _ODDBSYNERGYIMPL_INCLUDED_
