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

#ifndef _ODDB_POLYFACEMESHIMPL_INCLUDED_
#define _ODDB_POLYFACEMESHIMPL_INCLUDED_

#include "PolylineBaseImpl.h"
#include "DbPolyFaceMesh.h"
#include "DbSystemInternals.h"

class OdTvDbPolyFaceMeshImpl : public OdPolylineBaseImpl
{
  static OdTvDbPolyFaceMeshImpl* getImpl(const OdTvDbPolyFaceMesh *pObj)
  { return (OdTvDbPolyFaceMeshImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  OdInt16 m_nVertices;
  OdInt16 m_nFaces;

public:
  OdTvDbPolyFaceMeshImpl();
  void audit (OdTvDbAuditInfo* pAuditInfo);
  virtual bool isValidSubentityClass(OdRxClass* pClass) const;

  friend class OdTvDbPolyFaceMesh;
  friend class OdTvDbPolyFaceMeshVertex;
  friend class OdTvDbFaceRecord;
};

#endif // _ODDB_POLYFACEMESHIMPL_INCLUDED_