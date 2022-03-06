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




#ifndef _OD_DB_VERTEX_
#define _OD_DB_VERTEX_

#include "TD_PackPush.h"

#include "DbEntity.h"
#include "DwgDeclareMembers.h"

/** \details
  
    <group TD_Namespaces>
*/
namespace OdDb
{
  enum Vertex3dType
  {
    k3dSimpleVertex  = 0,  // Standard vertex.
    k3dControlVertex = 1,  // Spline-fit or curve-fit control point.
    k3dFitVertex     = 2   // Spline-fit or curve-fit generated vertex.
  };
}

/** \details
    The class is the base class for all OdDb vertices.

    Corresponding C++ library: TD_Db

    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbVertex: public OdTvDbEntity
{
public:
  DWGMAP_DECLARE_MEMBERS(OdTvDbVertex);

//  OdTvDbVertex();

  OdResult dxfInFields(
    OdTvDbDxfFiler* pFiler);

  void dxfOutFields(
    OdTvDbDxfFiler* pFiler) const;

  OdResult subGetGeomExtents(
    OdGeExtents3d& extents) const;

  OdResult subTransformBy(const OdGeMatrix3d& xform);

  OdTvDbEntityPtr subSubentPtr(const OdTvDbFullSubentPath& path) const;
};
/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbVertex object pointers.
*/
typedef OdSmartPtr<OdTvDbVertex> OdTvDbVertexPtr;

#include "TD_PackPop.h"

#endif
