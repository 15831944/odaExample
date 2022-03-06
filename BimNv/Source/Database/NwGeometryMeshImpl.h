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

#ifndef __NWGEOMETRYMESHIMPL_INCLUDED__
#define __NWGEOMETRYMESHIMPL_INCLUDED__

#include "NwGeometryMesh.h"
#include "NwGeometryImpl.h"
#include "UInt16Array.h"

class OdNwGeometryMeshImpl;


class OdNwGeometryMeshImpl : public OdNwGeometryImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwGeometryMesh)
public:
  OdNwGeometryMeshImpl();
  virtual ~OdNwGeometryMeshImpl();
  ODRX_DECLARE_MEMBERS(OdNwGeometryMeshImpl);

public:
  bool draw(OdGiWorldDraw* pWd) const;

public:
  static OdNwGeometryMeshImpl* getImpl(const OdNwGeometryMesh* pNwGeometry);
  static OdNwGeometryMeshImpl* getImpl(const OdRxObject* pRxGeometry);

public:
  static OdNwGeometryMeshPtr createShell(const OdGePoint3dArray& pVertexList, const OdGeVector3dArray& pNormalList, const OdUInt16Array& pFaceList);
  static OdNwGeometryMeshPtr createShell(const OdGePoint3dArray& pVertexList, const OdGeVector3dArray& pNormalList, const OdArray<OdNwTriangleIndexes>& pFaceList);

public:
  // deprected
  OdArray<OdGePoint3d> getVertexes() const override;
  // deprected
   OdArray<OdUInt32> getColors() const override;

public:
  OdUInt16Array getVerticesCountPerFace() const;
  OdUInt16Array getIndices() const;

  OdArray<OdNwTriangleIndexes> getTriangles() const;

  void setIndexes(const OdUInt16Array& val);
  void setVerticesCountPerFace(const OdUInt16Array& val);

  OdUInt32 getPrimitiveCount() const override;

public:
  OdNwVerticesDataPtr getVerticesData() const;
  void setVerticesData(const OdNwVerticesDataPtr& val);

  virtual OdGeExtents3d calculateBoundingBox() const;

protected:
  OdUInt16Array             m_aVertexCountPerFace;
  OdUInt16Array             m_aIndexes;

  OdNwVerticesDataPtr m_pVerticesData;  
};

#endif //__NWGEOMETRYMESHIMPL_INCLUDED__
