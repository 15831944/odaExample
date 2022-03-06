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
#ifndef OdTvDbAssocCurvePersSubentIdPE_INCLUDED_
#define OdTvDbAssocCurvePersSubentIdPE_INCLUDED_  /*!DOM*/

#include "OdTvDbAssocPersSubentIdPE.h"

#include "TD_PackPush.h"

/** \details
  This class provides the base protocol extension class that declares the protocol for 
  working with curve persistent subentity identifier.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocCurvePersSubentIdPE : public OdTvDbAssocPersSubentIdPE
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocCurvePersSubentIdPE);

  /** \details
    Declares the vertex type.
  */
  enum VertexSubentIdx
  {
    kNotDefine = 0,                   // Undefined
    kStart = -1,                      // Start
    kEnd = -3,                        // End
    kCenter= -5,                      // Center
    kMiddle = -6,                     // Middle
    kMiddlePLinePrefix = 10000000,
    kCenterPLinePrefix = 1000000,
  };

  /** \details
    Gets all subentity identifiers corresponding to this associated persistent subentity identifier.
  */
  virtual OdResult getTransientSubentIds(const OdTvDbEntity* pEntity, 
                                         const OdTvDbAssocPersSubentId* pPerSubentId,
                                         OdArray<OdDbSubentId>& subents) const;

  /** \details
    Gets the vertex subentity identifier corresponding to the given edge subentity identifier. 
    This protocol provides the query of relations between the edge and vertex subentities.
  */
  virtual OdResult getEdgeVertexSubentities(const OdTvDbEntity*      pEntity,
                                            const OdDbSubentId&    edgeSubentId,
                                            OdDbSubentId&          startVertexSubentId,
                                            OdDbSubentId&          endVertexSubentId,
                                            OdArray<OdDbSubentId>& otherVertexSubentIds);
protected:
  /** \details
    Checks whether the type equals to a given type specified by the class description instance.
  */
  bool isTypeEqual(const OdTvDbEntity* pEntity, const OdRxClass* pTypeDesc) const;

  /** \details
    Fills the start vertex subentity identifiers.
  */
  virtual void fillStartVertexSubentId(const OdTvDbEntity*      pEntity,
                                       const OdDbSubentId&    edgeSubentId,
                                       OdDbSubentId& startVertexSubentId);

  /** \details
    Fills the end vertex subentity identifiers.
  */
  virtual void fillEndVertexSubentId(const OdTvDbEntity*      pEntity,
                                     const OdDbSubentId&    edgeSubentId,
                                     OdDbSubentId& startVertexSubentId);

  /** \details
    Gets other vertex subentity identifiers.
  */
  virtual void getOtherVertexSubentIds(const OdTvDbEntity*      pEntity,
                                       const OdDbSubentId&    edgeSubentId,
                                       OdArray<OdDbSubentId>& otherVertexSubentIds);
};

#include "TD_PackPop.h"
#endif
