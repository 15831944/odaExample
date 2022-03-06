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
#ifndef OdDbAssocAsmBasedPersSubentIdPE_INCLUDED_
#define OdDbAssocAsmBasedPersSubentIdPE_INCLUDED_  /*!DOM*/

#include "OdDbAssocPersSubentIdPE.h"

#include "TD_PackPush.h"

/** \details
  This class provides the base protocol extension class that declares the protocol for
  working with BRep-based entities' persistent subentity identifier.

  Library: Source code provided.
  <group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdDbAssocAsmBasedPersSubentIdPE : public OdDbAssocPersSubentIdPE
{
public:
  ODRX_DECLARE_MEMBERS(OdDbAssocAsmBasedPersSubentIdPE);

  /** \details
    Returns the transient subent ID of the dependent-on entity corresponding to the internally
    held associated subentity.
  */
  virtual OdResult getTransientSubentIds(const OdDbEntity* pEntity,
    const OdDbAssocPersSubentId* pPerSubentId,
    OdArray<OdDbSubentId>& subents) const ODRX_OVERRIDE;

  virtual OdResult getEdgeSubentityGeometry(const OdDbEntity* pEntity,
    const OdDbSubentId& edgeSubentId,
    OdGeCurve3d*& pEdgeCurve) ODRX_OVERRIDE;

  virtual OdResult addSubentitySpecialSettings(OdDbEntityPtr ent, const OdDbSubentId subentId, OdUInt32 idx, OdDbAssocActionBodyPtr pActionBody) ODRX_OVERRIDE;

  virtual OdResult getAllSubentities(const OdDbEntity* pEntity,
    OdDb::SubentType subentType,
    OdArray<OdDbSubentId>& allSubentIds) ODRX_OVERRIDE;
protected:
  bool isBrepEntity(const OdDbEntity* pEntity) const;
};

#include "TD_PackPop.h"
#endif
