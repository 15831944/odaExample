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

#ifndef _ODDB_POLYGONMESHIMPL_INCLUDED_
#define _ODDB_POLYGONMESHIMPL_INCLUDED_

#include "PolylineBaseImpl.h"
#include "DbSystemInternals.h"
#include "DbPolygonMesh.h"

class OdDbPolygonMeshImpl : public OdPolylineBaseImpl
{
  static OdDbPolygonMeshImpl* getImpl(const OdDbPolygonMesh *pObj)
  { return (OdDbPolygonMeshImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
  OdInt16 m_MeshM;
  OdInt16 m_MeshN;
  OdInt16 m_MeshMDensity;
  OdInt16 m_MeshNDensity;

public:
  OdDbPolygonMeshImpl();
  virtual bool isValidSubentityClass(OdRxClass* pClass) const;

  OdResult prepareVertices(OdUInt32& rows, OdUInt32& cols,
    OdGePoint3dArray& vertices, unsigned& nMissingVerts) const;

  OdResult prepareVertices(OdDb::PolyMeshType sType, OdUInt32& rows, OdUInt32& cols,
    OdGePoint3dArray& vertices, unsigned& nMissingVerts) const;

  bool isMClosed() const { return (m_PolyFlags & 1) != 0; }
  void makeMClosed() { m_PolyFlags |= 1; }
  void makeMOpen() { m_PolyFlags &= 0xFFFE; }
  bool isNClosed() const { return (m_PolyFlags & 32) != 0; }
  void makeNClosed() { m_PolyFlags |= 32; }
  void makeNOpen() { m_PolyFlags &= 0xFFDF; }

  friend class OdDbPolygonMesh;
};

#endif // _ODDB_POLYGONMESHIMPL_INCLUDED_
