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

#ifndef OdTvDbAssocViewPortPersSubentIdPE_INCLUDED_
#define OdTvDbAssocViewPortPersSubentIdPE_INCLUDED_  /*!DOM*/

#include "OdTvDbAssocPersSubentIdPE.h"

#include "TD_PackPush.h"

/** \details
This class provides the base protocol extension class that declares the protocol for
working with ViewPort identifier.

Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocViewPortPersSubentIdPE : public OdTvDbAssocPersSubentIdPE
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocViewPortPersSubentIdPE);


  /** \details
  Returns the transient subent ID of the dependent-on entity corresponding to the internally
  held associated subentity.
  */
  virtual OdResult getTransientSubentIds(const OdTvDbEntity* pEntity,
    const OdTvDbAssocPersSubentId* pPerSubentId,
    OdArray<OdDbSubentId>& subents) const;

  /** \details
  Gets the curve of an edge subentity corresponding to the associated subentity ID.
  */
  virtual OdResult getEdgeSubentityGeometry(const OdTvDbEntity*   pEntity,
    const OdDbSubentId& edgeSubentId,
    OdGeCurve3d*&       pEdgeCurve);

  virtual OdResult getEdgeSubentityGeometry(const OdTvDbEntity*   pEntity,
    const OdDbSubentId& edgeSubentId,
    const OdTvDbImpAssocGeomDependency* assocGeomDependency,
    OdGeCurve3d*&       pEdgeCurve);

  //private:
//  /** \details
//  Checks the subentity identifier for a given type.
//  */
//  bool checkSubentId(const OdTvDbEntity* pEntity, const OdDbSubentId& subentId, const OdDb::SubentType type) const;
};

typedef OdSmartPtr<OdTvDbAssocViewPortPersSubentIdPE> OdTvDbAssocViewPortPersSubentIdPEPtr;

#include "TD_PackPop.h"

#endif
#pragma once
#pragma once
