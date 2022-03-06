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

#ifndef OdTvDbAssocSurfacePersSubentIdPE_INCLUDED_
#define OdTvDbAssocSurfacePersSubentIdPE_INCLUDED_  /*!DOM*/

#include "OdTvDbAssocCurvePersSubentIdPE.h"

#include "TD_PackPush.h"

/** \details
This class provides the base protocol extension class that declares the protocol for
working with polyline persistent subentity identifier.

Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocSurfacePersSubentIdPE : public OdTvDbAssocCurvePersSubentIdPE
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocSurfacePersSubentIdPE);

  ///** \details
  //Creates new persistent subentity identifier.
  //*/
  //virtual OdTvDbAssocPersSubentIdPtr createNewPersSubent(OdTvDbEntity* pEntity,
  //  const class OdTvDbCompoundObjectId& compId,
  //  const OdDbSubentId& subentId);

  /** \details
  Returns the transient subent ID of the dependent-on entity corresponding to the internally
  held associated subentity.
  */
  virtual OdResult getTransientSubentIds(const OdTvDbEntity* pEntity,
    const OdTvDbAssocPersSubentId* pPerSubentId,
    OdArray<OdDbSubentId>& subents) const;

  ///** \details
  //Gets all subentity identifiers for a given subentity type.
  //*/
  //virtual OdResult getAllSubentities(const OdTvDbEntity* pEntity,
  //  OdDb::SubentType subentType,
  //  OdArray<OdDbSubentId>& allSubentIds);

  ///** \details
  //Gets the vertex subentity identifier corresponding to the given edge subentity identifier.
  //This protocol provides the query of relations between the edge and vertex subentities.
  //*/
  //virtual OdResult getEdgeVertexSubentities(const OdTvDbEntity*      pEntity,
  //  const OdDbSubentId&    edgeSubentId,
  //  OdDbSubentId&          startVertexSubentId,
  //  OdDbSubentId&          endVertexSubentId,
  //  OdArray<OdDbSubentId>& otherVertexSubentIds);

  /** \details
  Gets the curve of an edge subentity corresponding to the associated subentity ID.
  */
  virtual OdResult getEdgeSubentityGeometry(const OdTvDbEntity* pEntity,
    const OdDbSubentId& edgeSubentId,
    OdGeCurve3d*&       pEdgeCurve);

//  /** \details
//  Sets the curve of an edge subentity corresponding to the associated subentity ID.
//  */
//  virtual OdResult setEdgeSubentityGeometry(OdTvDbEntity*         pEntity,
//    const OdDbSubentId& edgeSubentId,
//    const OdGeCurve3d*  pNewEdgeCurve);
//
//  /** \details
//  Gets the coordinates of a vertex subentity corresponding to the associated subentity ID.
//  */
//  virtual OdResult getVertexSubentityGeometry(const OdTvDbEntity*   pEntity,
//    const OdDbSubentId& vertexSubentId,
//    OdGePoint3d&        vertexPosition);
//
//  /** \details
//  Sets the coordinates of a vertex subentity corresponding to the associated subentity ID.
//  */
//  virtual OdResult setVertexSubentityGeometry(OdTvDbEntity*         pEntity,
//    const OdDbSubentId& vertexSubentId,
//    const OdGePoint3d&  newVertexPosition);
//
//  /** \details
//  Modifiers the geometry of a subentity.
//  */
//  virtual OdResult setSubentityGeometry(OdTvDbEntity*         pEntity,
//    const OdDbSubentId& subentId,
//    const OdTvDbEntity*   pNewSubentityGeometry);
//
//protected:
  virtual OdResult addSubentitySpecialSettings(OdTvDbEntityPtr ent, const OdDbSubentId subentId, OdUInt32 idx, OdTvDbAssocActionBodyPtr pActionBody);
private:
  /** \details
  Checks the subentity identifier for a given type.
  */
  bool checkSubentId(const OdTvDbEntity* pEntity, const OdDbSubentId& subentId, const OdDb::SubentType type) const;
};

typedef OdSmartPtr<OdTvDbAssocSurfacePersSubentIdPE> OdTvDbAssocSurfacePersSubentIdPEPtr;

#include "TD_PackPop.h"

#endif

