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

#ifndef OdTvDbAssocTextPersSubentIdPE_INCLUDED_
#define OdTvDbAssocTextPersSubentIdPE_INCLUDED_  /*!DOM*/

#include "OdTvDbAssocPointPersSubentIdPE.h"

#include "TD_PackPush.h"

/** \details
This class provides the base protocol extension class that declares the protocol for
working with OdTvDbText persistent subentity identifier.

Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocTextPersSubentIdPE : public OdTvDbAssocPointBasedPersSubentIdPE
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocTextPersSubentIdPE);

  /** \details
  Creates new persistent subentity identifier.
  */
  OdTvDbAssocPersSubentIdPtr createNewPersSubent(OdTvDbEntity* pEntity,
                                               const class OdTvDbCompoundObjectId& compId,
                                               const OdDbSubentId& subentId) ODRX_OVERRIDE;

  /** \details
  Returns the transient subent ID of the dependent-on entity corresponding to the internally
  held associated subentity.
  */
  OdResult getTransientSubentIds(const OdTvDbEntity* pEntity,
                                 const OdTvDbAssocPersSubentId* pPerSubentId,
                                 OdArray<OdDbSubentId>& subents) const ODRX_OVERRIDE;

  /** \details
  Gets all subentity identifiers for a given subentity type.
  */
  OdResult getAllSubentities(const OdTvDbEntity* pEntity,
                             OdDb::SubentType subentType,
                             OdArray<OdDbSubentId>& allSubentIds) ODRX_OVERRIDE;

  /** \details
  Gets the coordinates of a vertex subentity corresponding to the associated subentity ID.
  */
  OdResult getVertexSubentityGeometry(const OdTvDbEntity* pEntity,
                                      const OdDbSubentId& vertexSubentId,
                                      OdGePoint3d& vertexPosition) ODRX_OVERRIDE;

  /** \details
  Sets the coordinates of a vertex subentity corresponding to the associated subentity ID.
  */
  OdResult setVertexSubentityGeometry(OdTvDbEntity* pEntity,
                                      const OdDbSubentId& vertexSubentId,
                                      const OdGePoint3d& newVertexPosition) ODRX_OVERRIDE;

  /** \details
  Modifiers the geometry of a subentity.
  */
  OdResult setSubentityGeometry(OdTvDbEntity* pEntity,
                                const OdDbSubentId& subentId,
                                const OdTvDbEntity* pNewSubentityGeometry) ODRX_OVERRIDE;
};

typedef OdSmartPtr<OdTvDbAssocTextPersSubentIdPE> OdTvDbAssocTextPersSubentIdPEPtr;

/** \details
This class provides the base protocol extension class that declares the protocol for
working with OdTvDbMText persistent subentity identifier.

Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocMTextPersSubentIdPE : public OdTvDbAssocPointBasedPersSubentIdPE
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocMTextPersSubentIdPE);

  /** \details
  Creates new persistent subentity identifier.
  */
  OdTvDbAssocPersSubentIdPtr createNewPersSubent(OdTvDbEntity* pEntity,
                                               const class OdTvDbCompoundObjectId& compId,
                                               const OdDbSubentId& subentId) ODRX_OVERRIDE;

  /** \details
  Returns the transient subent ID of the dependent-on entity corresponding to the internally
  held associated subentity.
  */
  OdResult getTransientSubentIds(const OdTvDbEntity* pEntity,
                                 const OdTvDbAssocPersSubentId* pPerSubentId,
                                 OdArray<OdDbSubentId>& subents) const ODRX_OVERRIDE;

  /** \details
  Gets all subentity identifiers for a given subentity type.
  */
  OdResult getAllSubentities(const OdTvDbEntity* pEntity,
                             OdDb::SubentType subentType,
                             OdArray<OdDbSubentId>& allSubentIds) ODRX_OVERRIDE;

  /** \details
  Gets the coordinates of a vertex subentity corresponding to the associated subentity ID.
  */
  OdResult getVertexSubentityGeometry(const OdTvDbEntity* pEntity,
                                      const OdDbSubentId& vertexSubentId,
                                      OdGePoint3d& vertexPosition) ODRX_OVERRIDE;

  /** \details
  Sets the coordinates of a vertex subentity corresponding to the associated subentity ID.
  */
  OdResult setVertexSubentityGeometry(OdTvDbEntity* pEntity,
                                      const OdDbSubentId& vertexSubentId,
                                      const OdGePoint3d& newVertexPosition) ODRX_OVERRIDE;

  /** \details
  Modifiers the geometry of a subentity.
  */
  OdResult setSubentityGeometry(OdTvDbEntity* pEntity,
                                const OdDbSubentId& subentId,
                                const OdTvDbEntity* pNewSubentityGeometry) ODRX_OVERRIDE;
};

typedef OdSmartPtr<OdTvDbAssocMTextPersSubentIdPE> OdTvDbAssocMTextPersSubentIdPEPtr;

#include "TD_PackPop.h"

#endif
