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

#ifndef _ODTV_USERDATAIMPL_H_INCLUDED_
#define _ODTV_USERDATAIMPL_H_INCLUDED_

#include "TD_PackPush.h"
#include "TvUserData.h"

#define STL_USING_MAP
#include "OdaSTL.h"
#include "DbObjectId.h"
#include "DbFiler.h"

/** \details
This is an implementation of the custom user data storage
*/
class OdTvXDataStorage
{
  typedef std::map<OdTvDbObjectId, OdTvUserData*> OdTvUserDataMap;

  OdTvUserDataMap* m_userdatas;

public:

  friend class OdTvGeometryDataImpl;

  //constructor
  OdTvXDataStorage();

  //destructor
  virtual ~OdTvXDataStorage();

  /** \details
  Append the user data to the entity
  */
  OdTvResult appendUserData(OdTvUserData* pUserData, const OdTvRegAppId& id);

  /** \details
  Get user data
  */
  OdTvUserData* getUserData(const OdTvRegAppId& id) const;

  /** \details
  Get the count of the user data
  */
  OdUInt32 getUserDataCount();

  /** \details
  All registered apps for which the user data is set
  */
  OdTvResult getUserDataApps(OdTvRegAppIdArray& ids);

  /** \details
  Removes user data
  */
  OdTvResult removeUserData(const OdTvRegAppId& id);

  /** \details
  Removes all user data
  */
  OdTvResult clearUserData();

  /** \details
  Read method.
  */
  void readXData(OdTvDbDwgFiler* pFiler, OdTvDbDatabase* pDb, OdTvVSFVersion ver);

  /** \details
  Write method.
  */
  void writeXData(OdTvDbDwgFiler* pFiler, OdTvVSFVersion ver) const;

  /** \details
  Return the value of memory, which this object takes up.
  */
  OdUInt64 getSizeOfDynamicData() const;

private:

  /** \details
  Read method (base)
  */
  void readXData_base(OdTvDbDwgFiler* pFiler, OdTvDbDatabase* pDb, OdTvVSFVersion ver);
};

#include "TD_PackPop.h"

#endif //_ODTV_USERDATAIMPL_H_INCLUDED_
