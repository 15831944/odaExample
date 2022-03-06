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

// DbSystemInternals.h: interface for the OdDbSystemInternals class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBSYSTEMINTERNALS_H__5B8F8EE2_246A_43CF_98DB_AD72643F9A92__INCLUDED_)
#define AFX_DBSYSTEMINTERNALS_H__5B8F8EE2_246A_43CF_98DB_AD72643F9A92__INCLUDED_


#include "DbObject.h"
#include "DbDatabase.h"


class OdDbObjectImpl;
class OdDbDatabase;

class OdDbSystemInternals
{
public:
  static OdDbObjectImpl* getImpl(const OdDbObject* pObj)
  {
     return const_cast<OdDbObjectImpl*>(pObj->m_pImpl);
  }

  TOOLKIT_EXPORT static bool isDatabaseLoading(const OdDbDatabase * pDb);
  TOOLKIT_EXPORT static bool isDatabaseConverting(const OdDbDatabase* pDb);
};

#endif // !defined(AFX_DBSYSTEMINTERNALS_H__5B8F8EE2_246A_43CF_98DB_AD72643F9A92__INCLUDED_)
