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
#ifndef OdTvDbAssocPersSubentIdPE_INCLUDED_
#define OdTvDbAssocPersSubentIdPE_INCLUDED_ /*!DOM*/

#include "DbAssocPersSubentId.h"
#include "Ge/GePoint3d.h"
#include "Ge/GeCurve3d.h"
#include "DbImpAssocGeomDependency.h"
#include "DbAssocActionBody.h"
#include "DbCompoundObjectId.h"
#include "DbBody.h"
#include <ModelerGeometry.h>

DBENT_EXPORT OdModelerGeometryPtr getModelerGeometry(const OdTvDbEntity* pEnt);

#include "TD_PackPush.h"

/*
struct OdTvDbAssocTransInfo
{
  enum TransType
  {
    kGeneral = 0,
    kScaling,
    kRadius,
    kMajorRadius,
    kMinorRadius,
    kFixedRadius,
    kFixed,
    kFixWhenPossible,
    kNone,
  };

  OdTvDbAssocTransInfo() : mRadius(-1.0), mTransType(kGeneral)
  {}
  TransType mTransType;

  OdGeMatrix3d mTrans;

  double mRadius;
};


struct OdTvDbAssocSubentTransInfo : OdTvDbAssocTransInfo
{
  OdDbSubentId mSubentId;
};
*/

/** \details
  Declares the rigidset type.
*/
enum RigidSetType
{
  kNotRigidSet = 0,
  kScalableRigidSet,
  kNonScalableRigidSet
};


/** \details
  This class provides the base protocol extension class that declares the protocol for 
  obtaining a persistent subentity identifier from a transient subentity identifier.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocPersSubentIdPE : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocPersSubentIdPE);
  OdTvDbAssocPersSubentIdPE() 
  { 
  }
  //OdTvDbAssocPersSubentIdPE() { m_assocGeomDependency = NULL; }

  /** \details
    Creates new persistent subentity identifier.
  */
  virtual OdTvDbAssocPersSubentIdPtr createNewPersSubent(OdTvDbEntity* pEntity,
                                                     const class OdTvDbCompoundObjectId& compId,
                                                     const OdDbSubentId& subentId)
  {
      OdTvDbAssocSimplePersSubentIdPtr res = OdTvDbAssocSimplePersSubentId::createObject();
      res->init(subentId);
      return res;
  }

  /** \details
    Returns the transient subent ID of the dependent-on entity corresponding to the internally 
    held associated subentity. 
  */
  virtual OdResult getTransientSubentIds(const OdTvDbEntity* pEntity, 
                                         const OdTvDbAssocPersSubentId* pPerSubentId,
                                         OdArray<OdDbSubentId>& subents) const = 0;

  /** \details
    Gets all subentity identifiers for a given subentity type.
  */
  virtual OdResult getAllSubentities(const OdTvDbEntity* pEntity,
                                     OdDb::SubentType subentType,
                                     OdArray<OdDbSubentId>& allSubentIds)
  {
      return eNotImplemented;
  }

  /** \details
    Gets the vertex subentity identifier corresponding to the given edge subentity identifier. 
    This protocol provides the query of relations between the edge and vertex subentities.
  */
  virtual OdResult getEdgeVertexSubentities(const OdTvDbEntity*      pEntity,
                                            const OdDbSubentId&    edgeSubentId,
                                            OdDbSubentId&          startVertexSubentId,
                                            OdDbSubentId&          endVertexSubentId,
                                            OdArray<OdDbSubentId>& otherVertexSubentIds)
  {
      return eNotImplemented;
  }


  /** \details
    Gets the vertex subentity identifier corresponding to the given spline subentity identifier. 
    This protocol provides the query of relations between the spline edge and vertex subentities.
  */
  virtual OdResult getSplineEdgeVertexSubentities(const OdTvDbEntity*      pEntity,
                                                  const OdDbSubentId&    edgeSubentId,
                                                  OdDbSubentId&          startVertexSubentId,
                                                  OdDbSubentId&          endVertexSubentId,
                                                  OdArray<OdDbSubentId>& controlPointSubentIds,
                                                  OdArray<OdDbSubentId>& fitPointSubentIds)
  {
      return eNotImplemented;
  }

  /** \details
    Gets the coordinates of a vertex subentity corresponding to the associated subentity ID.
  */
  virtual OdResult getVertexSubentityGeometry(const OdTvDbEntity*   pEntity,
                                              const OdDbSubentId& vertexSubentId,
                                              OdGePoint3d&        vertexPosition)
  {
      return eNotImplemented;
  }

  /** \details
    Gets the curve of an edge subentity corresponding to the associated subentity ID.
  */
  virtual OdResult getEdgeSubentityGeometry(const OdTvDbEntity*   pEntity,
                                            const OdDbSubentId& edgeSubentId,
                                            OdGeCurve3d*&       pEdgeCurve)
  {
      return eNotImplemented;
  }

  virtual OdResult getEdgeSubentityGeometry(const OdTvDbEntity*   pEntity,
    const OdDbSubentId& edgeSubentId,
    const OdTvDbImpAssocGeomDependency* m_assocGeomDependency,
    OdGeCurve3d*&       pEdgeCurve 
    )
  {
    return getEdgeSubentityGeometry(pEntity, edgeSubentId, pEdgeCurve);
  }

  virtual OdResult addSubentitySpecialSettings(OdTvDbEntityPtr ent, const OdDbSubentId subentId, OdUInt32 idx, OdTvDbAssocActionBodyPtr pActionBody ) { return eOk; };
  /** \details
    Gets the surface of a face subentity corresponding to the associated subentity ID.
  */
  virtual OdResult getFaceSubentityGeometry(const OdTvDbEntity*   pEntity,
                                            const OdDbSubentId& faceSubentId,
                                            OdGeSurface*&       pFaceSurface)
  {
      return eNotImplemented;
  }

  /** \details
    Sets the coordinates of a vertex subentity corresponding to the associated subentity ID.
  */
  virtual OdResult setVertexSubentityGeometry(OdTvDbEntity*         pEntity,
                                              const OdDbSubentId& vertexSubentId,
                                              const OdGePoint3d&  newVertexPosition)
  {
      return eNotImplemented;
  }

  /** \details
    Sets the curve of an edge subentity corresponding to the associated subentity ID.
  */
  virtual OdResult setEdgeSubentityGeometry(OdTvDbEntity*         pEntity,
                                            const OdDbSubentId& edgeSubentId,
                                            const OdGeCurve3d*  pNewEdgeCurve)
  {
      return eNotImplemented;
  }

  /** \details
    Sets the surface of a face subentity corresponding to the associated subentity ID.
  */
  virtual OdResult setFaceSubentityGeometry(OdTvDbEntity*         pEntity,
                                            const OdDbSubentId& faceSubentId,
                                            const OdGeSurface*  pNewFaceSurface)
  {
      return eNotImplemented;
  }

  /** \details
    Modifiers the geometry of a subentity.
  */
  virtual OdResult setSubentityGeometry(OdTvDbEntity*         pEntity,
                                        const OdDbSubentId& subentId,
                                        const OdTvDbEntity*   pNewSubentityGeometry)
  {
      return eNotImplemented;
  }

  ///These methods are deprecated and should not be used.
  /*
  virtual OdResult getSubentTransFromStretchPoints(const OdTvDbEntity*   pEntity,
                                                   const OdTvDbIntArray& indices, 
                                                   const OdGeVector3d& offset,
                                                   OdArray<OdTvDbAssocSubentTransInfo>& aSubentTransInfos) const
  {
    return eNotImplemented;
  }

  virtual OdResult getSubentTransFromGripPoints(const OdTvDbEntity*   pEntity,
                                                         const OdTvDbIntArray& indices, 
                                                         const OdGeVector3d& offset,
                                                         OdArray<OdTvDbAssocSubentTransInfo>& aSubentTransInfos) const
  {
    return eNotImplemented;
  }

  virtual OdResult getSubentTransFromGripPoints(const OdTvDbEntity*       pEntity,
                                                         const OdDbVoidPtrArray& gripAppData, 
                                                         const OdGeVector3d&     offset,
                                                         OdArray<OdTvDbAssocSubentTransInfo>& aSubentTransInfos) const
  {
    return eNotImplemented;
  }
  */

  /** \details
    Obtains a transformation matrix for a given subentity within the block reference.
  */
  virtual OdResult getSubentGeometryXform(const OdTvDbEntity*        pEntity,
                                          const OdTvDbObjectIdArray& fullSubentPath,
                                          OdGeMatrix3d&            trans) const
  {
      trans.setToIdentity();
      return eOk;
  }

  /** \details
    Mirrors the specified persistent subentity identifier. This method modifies the identifier 
    so that it identifies the same subentity in the mirrored entity as it identified before 
    the entity was mirrored.
  */
  virtual OdResult mirrorPersSubent(const OdTvDbEntity*      pMirroredEntity,
                                    OdTvDbAssocPersSubentId& persSubentIdToMirror)
  {
      return eOk;
  }

  /** \details
    If the entity is a rigid set, this method returns kScalableRigidSet or kNonScalableRigidSet type.

    \remarks
    Returns kNotRigidSet in default implementation.
  */
  virtual int getRigidSetState(const OdTvDbEntity* pEntity)
  {
    return kNotRigidSet;
  }

  /** \details
    Gets the transformation matrix of the rigid set entity.
  */
  virtual OdResult getRigidSetTransform(const OdTvDbEntity* pEntity,
                                        OdGeMatrix3d&     trans)
  {
      return eNotApplicable;
  }

  /** \details
    Gets the transformation matrix for the rigid set entity.
  */
  virtual OdResult setRigidSetTransform(OdTvDbEntity*         pEntity, 
                                        const OdGeMatrix3d& trans)
  {
      return eNotApplicable;
  }

  //OdTvDbImpAssocGeomDependency* assocGeomDependency() const
  //{
  //  OdTvDbImpAssocGeomDependency* ret = m_assocGeomDependency;
  //  return ret;
  //}

//  void setAssocGeomDependency(const OdTvDbImpAssocGeomDependency* assocGeomDependency)
//  {
//    m_assocGeomDependency = (OdTvDbImpAssocGeomDependency*)assocGeomDependency;
//  }
//protected:
//
//  OdTvDbImpAssocGeomDependency* m_assocGeomDependency;
};

typedef OdSmartPtr<OdTvDbAssocPersSubentIdPE> OdTvDbAssocPersSubentIdPEPtr;


#include "TD_PackPop.h"
#endif
