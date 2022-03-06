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

#ifndef DbGeomRef_INCLUDED_
#define DbGeomRef_INCLUDED_ /*!DOM*/

#include "DbConstraintsExports.h"
#include "DbAssocGlobal.h" 
#include "DbSubentId.h"
#include "DbCompoundObjectId.h"
#include "Ge/GeCurve3d.h"
#include "RxObjectImpl.h"

#include "TD_PackPush.h"

/** \details
  This class represents a reference to a geometry object. It is the base class for references.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbGeomRef : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbGeomRef);

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbGeomRef();

  /** \details
    Resets this geometry reference.
  */
  virtual void reset();

  /** \details
    Checks whether this geometry reference is valid.
  */
  virtual bool isValid() const;

  /** \details
    Checks whether this geometry reference is empty.
  */
  virtual bool isEmpty() const;

  /** \details
    Creates an antity using this geometry reference.
  */
  virtual OdTvDbEntity* createEntity() const;

  /** \details
    Evaluates and caches the geometry.
  */
  virtual OdResult  evaluateAndCacheGeometry();
};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbGeomRef class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbGeomRef> OdTvDbGeomRefPtr;


/** \details
  This class represents a reference to a subent object.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbSubentRef : public OdTvDbGeomRef
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbSubentRef);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbSubentRef();
  OdTvDbSubentRef(const OdTvDbCompoundObjectId&, 
                const OdDbSubentId& = OdDbSubentId()); 

  static OdSmartPtr<OdTvDbSubentRef> createObject( const OdTvDbCompoundObjectId&,
                const OdDbSubentId& = OdDbSubentId() );

  /** \details
    Deprecated.
  */
  static OdSmartPtr<OdTvDbSubentRef> createObject( const OdTvDbCompoundObjectId* pid,
                const OdDbSubentId& subentid = OdDbSubentId() )
  {
    return createObject( *pid, subentid );
  }

  OdTvDbSubentRef& operator =(const OdTvDbSubentRef&);
  virtual void copyFrom(const OdRxObject*);

  /** \details
    Resets this subent reference.
  */
  virtual void reset();

  /** \details
    Checks whether this subent reference is valid.
  */
  virtual bool isValid() const;

  /** \details
    Checks whether this subent reference is empty.
  */
  virtual bool isEmpty() const;

  /** \details
    Returns an object ID of the compounded entity.
  */
  virtual const OdTvDbCompoundObjectId& entity() const;

  /** \details
    Returns an subent ID.
  */
  virtual OdDbSubentId subentId() const;

  /** \details
    Creates an entity using this subent reference.
  */
  virtual OdTvDbEntity* createEntity() const;

  /** \details
    Evaluates and caches the geometry.
  */
  virtual OdResult evaluateAndCacheGeometry(); 

protected:
  /** \details
    Sets the compounded entity using an object ID.
  */
  void setEntity(const OdTvDbCompoundObjectId& entityId);
 
  /** \details
    Sets an subent ID.
  */
  void setSubent(const OdDbSubentId& subentId);

  /** \details
    Sets an subent ID using the full subent path.
  */
  void setFromSubentPath(const OdTvDbFullSubentPath&);

private:
  /*!DOM*/
  OdTvDbCompoundObjectId m_entityId;
  /*!DOM*/
  OdDbSubentId m_SubentId;
};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbSubentRef class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbSubentRef> OdTvDbSubentRefPtr;


/** \details
  This class represents a reference to a face object.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbFaceRef : public OdRxObjectImpl<OdTvDbSubentRef>
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbFaceRef);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbFaceRef();
  OdTvDbFaceRef(const OdTvDbCompoundObjectId&, 
              const OdDbSubentId& = OdDbSubentId(), 
              class BODY* = NULL); 
  OdTvDbFaceRef(const OdTvDbFaceRef&);

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbFaceRef();

  /** \details
    Copies a given fase reference to this reference.
  */
  OdTvDbFaceRef& operator =(const OdTvDbFaceRef&);

  /** \details
    Initializes this reference using a given object.
  */
  virtual void copyFrom(const OdRxObject*);

  /** \details
    Resets this fase reference.
  */
  virtual void reset();

  /** \details
    Checks whether this face reference is valid.
  */
  virtual bool isValid() const;

  /** \details
    Checks whether this face reference is empty.
  */
  virtual bool isEmpty() const;

  /** \details
    Returns the ASM BODY object which this face reference may hold.
  */
  class BODY* asmBody() const;

  /** \details
    Creates an entity using this face reference.
  */
  virtual OdTvDbEntity* createEntity() const;

  /** \details
    Evaluates and caches the geometry.
  */
  virtual OdResult evaluateAndCacheGeometry();

private:
  /*!DOM*/
  class BODY* m_pAsmBody;
};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbFaceRef class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbFaceRef> OdTvDbFaceRefPtr;


/** \details
  This class represents a reference to an endge object.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbEdgeRef : public OdRxObjectImpl<OdTvDbSubentRef>
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbEdgeRef);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbEdgeRef();
  OdTvDbEdgeRef(const OdTvDbFullSubentPath&);
  OdTvDbEdgeRef(const OdTvDbCompoundObjectId&,
              const OdDbSubentId& edgeSubentId = OdDbSubentId(),
              const OdDbSubentId& faceSubentId = OdDbSubentId(),
              const OdGeCurve3d* pCurve = NULL);
  OdTvDbEdgeRef(const OdGeCurve3d* pGeCurve);
  OdTvDbEdgeRef(const OdTvDbEdgeRef&);

  /** \details
    Deprecated.
  */
  static OdSmartPtr<OdTvDbEdgeRef> createObject( const OdTvDbCompoundObjectIdPtr & pid, const OdGeCurve3d* pCurve ) {
    return createObject( *pid, pCurve );
  }

  static OdSmartPtr<OdTvDbEdgeRef> createObject( const OdTvDbCompoundObjectId&, const OdGeCurve3d* pCurve );
  static OdSmartPtr<OdTvDbEdgeRef> createObject( const OdTvDbEntity* pEnt );
  static OdSmartPtr<OdTvDbEdgeRef> createObject( const OdGeCurve3d* pCurve );

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbEdgeRef();

  /** \details
    Copies a given edge reference to this reference.
  */
  OdTvDbEdgeRef& operator =(const OdTvDbEdgeRef&);

  /** \details
    Initializes this reference using a given object.
  */
  virtual void copyFrom(const OdRxObject*);

  /** \details
    Resets this edge reference.
  */
  virtual void reset();

  /** \details
    Checks whether this edge reference is valid.
  */
  virtual bool isValid() const;

  /** \details
    Checks whether this edge reference is empty.
  */
  virtual bool isEmpty() const;

  /** \details
    The edge reference can use the subent ID of a face subentity. The face entity is used to restrict
    the referenced edge subentity.
  */
  void setFaceSubentity(const OdDbSubentId& faceSubentId);

  /** \details
    Returns the face subent ID of one of the faces adjacent to the referenced edge.
  */
  OdDbSubentId faceSubentId() const;

  /** \details
    Returns the constant three-dimensional curve which the edge reference can hold.
  */
  const OdGeCurve3d* curve() const;

  /** \details
    Evaluates the curve.
  */
  virtual OdResult evaluateCurve(OdGeCurve3d*&) const;

  /** \details
    Creates an entity using this edge reference.
  */
  virtual OdTvDbEntity* createEntity() const;

  /** \details
    Evaluates and caches the geometry.
  */
  virtual OdResult evaluateAndCacheGeometry(); 

  
  /** \details
  Sets the constant three-dimensional curve to be hold by this edge reference.
  */
  void setCurve(const OdGeCurve3d* pCurve);

private:
  ///** \details
  //  Sets the constant three-dimensional curve to be hold by this edge reference.
  //*/
  //void setCurve(const OdGeCurve3d* pCurve);
  /*!DOM*/
  OdDbSubentId m_FaceSubentId;
  /*!DOM*/
  OdGeCurve3dPtr m_pCurve;
};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbEdgeRef class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbEdgeRef> OdTvDbEdgeRefPtr;


/** \details
  This class represents a reference to a vertex object.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbVertexRef : public OdRxObjectImpl<OdTvDbSubentRef>
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbVertexRef);

  /** \details
    Declares the implied types.
  */
  enum ImpliedType
  {
    kExplicitVertex, // directly specified vertex
    kUnknownType,
    kEdgeStart,
    kEdgeEnd,
    kEdgeMid,
    kEdgeCenter,
    kEdgeSplineControlPoint,
    kEdgeSplineFitPoint,
  };

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbVertexRef();
  OdTvDbVertexRef(const OdTvDbCompoundObjectId&, 
                const OdDbSubentId& = OdDbSubentId(), 
                const OdGePoint3d& = OdGePoint3d::kOrigin);
  OdTvDbVertexRef(const OdTvDbFullSubentPath&);
  OdTvDbVertexRef(const OdTvDbEntity*);
  OdTvDbVertexRef(const OdGePoint3d&);
  OdTvDbVertexRef(ImpliedType, 
                const OdTvDbEdgeRef& edgeRef, 
                int controlOrFitPointIndex = 0,
                const OdGePoint3d& = OdGePoint3d::kOrigin);
  OdTvDbVertexRef(const OdTvDbVertexRef&);

  static OdSmartPtr<OdTvDbVertexRef> createObject( const OdGePoint3d& );
  static OdSmartPtr<OdTvDbVertexRef> createObject( const OdTvDbObjectId entId, const OdDbSubentId subId, const OdGePoint3d& point );

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbVertexRef();

  /** \details
    Copies a given vertex reference to this reference.
  */
  OdTvDbVertexRef& operator =(const OdTvDbVertexRef&);

  /** \details
    Initializes this reference using a given object.
  */
  virtual void copyFrom(const OdRxObject*);

  /** \details
    Resets this vertex reference.
  */
  virtual void reset();

  /** \details
    Checks whether this vertex reference is valid.
  */
  virtual bool isValid() const;

  /** \details
    Checks whether this vertex reference is empty.
  */
  virtual const OdTvDbCompoundObjectId& entity() const;

  /** \details
    Returns the subent ID.
  */
  virtual OdDbSubentId subentId() const;

  /** \details
    Returns the implied type.
  */
  ImpliedType impliedType() const;

  /** \details
    Returns the geometry reference referenced by this vertex reference.
  */
  const OdTvDbGeomRef* referencedRef() const;

  /** \details
    Returns the vertex index.
  */
  int index() const;

  /** \details
    Returns the three-dimensional point directly held by this vertex reference.
  */
  OdGePoint3d point() const;

  /** \details
    Evaluate the point.
  */
  virtual OdResult evaluatePoint(OdGePoint3d&) const;

  /** \details
    Creates an entity using this vertex reference.
  */
  class OdTvDbEntity* createEntity()const;

  /** \details
    Evaluates and caches the geometry.
  */
  virtual OdResult evaluateAndCacheGeometry(); 

private:
  /** \details
    Sets the geometry reference to be hold by this vertex reference.
  */
  void setReferencedRef(OdTvDbGeomRefPtr pReferencedRef);

  /*!DOM*/
  ImpliedType m_ImpliedType;
  /*!DOM*/
  OdTvDbGeomRefPtr m_pReferencedRef;
  /*!DOM*/
  int m_Index;
  /*!DOM*/
  OdGePoint3d m_Point; 
};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbVertexRef class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbVertexRef> OdTvDbVertexRefPtr;


/** \details
  This class represents a reference to a path object.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbPathRef : public OdRxObjectImpl<OdTvDbGeomRef>
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbPathRef);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbPathRef();
  OdTvDbPathRef(const OdArray<OdTvDbEdgeRef>&);
  OdTvDbPathRef(const OdTvDbFullSubentPathArray& edgeSubentPathArr,
              const OdTvDbFullSubentPathArray& faceSubentPathArr);
  OdTvDbPathRef(const OdTvDbPathRef&);

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbPathRef();

  /** \details
    Copies a given path reference to this reference.
  */
  OdTvDbPathRef& operator =(const OdTvDbPathRef&);

  /** \details
    Initializes this reference using a given object.
  */
  virtual void copyFrom(const OdRxObject*);

  /** \details
    Resets this path reference.
  */
  virtual void reset();

  /** \details
    Checks whether this path reference is valid.
  */
  virtual bool isValid() const;

  /** \details
    Checks whether this path reference is empty.
  */
  virtual bool isEmpty() const;

  /** \details
    Sets the path reference from a sequence of edge references.
  */
  void setEdgeRefs(const OdArray<OdTvDbEdgeRef>& edges);

  /** \details
    Returns an array of entities created from the edge references in the path. 
    If the second argument is True, it tries to concatenate them.
  */
  OdResult getEntityArray(OdArray<OdTvDbEntity*>& entities, bool concatenate) const;

  /** \details
    Returns the array of edge references stored in the path reference.
  */
  const OdArray<OdTvDbEdgeRef>& edgeRefs() const;

  /** \details
    Checks whether the geometry of the path is equal to the geometry of a given curve.
  */
  bool isEqualTo(const OdGeCurve3d*);

  /** \details
    Checks whether all elements of this path reference are the references to the entities.
  */
  bool isReferencePath();

  /** \details
    Creates an entity using this path reference.
  */
  virtual OdTvDbEntity* createEntity() const;

  /** \details
    Evaluates and caches the geometry.
  */
  virtual OdResult evaluateAndCacheGeometry();

private:
  /*!DOM*/
  OdArray<OdTvDbEdgeRef> m_EdgeRefs;
};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbPathRef class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbPathRef> OdTvDbPathRefPtr;


/** \details
  This class represents a reference to a vector object.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbVectorRef : public OdRxObjectImpl<OdTvDbGeomRef>
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbVectorRef);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbVectorRef();
  OdTvDbVectorRef(const OdGeVector3d&);
  OdTvDbVectorRef(const OdTvDbVectorRef&);

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbVectorRef();

  /** \details
    Copies a given vector reference to this reference.
  */
  OdTvDbVectorRef& operator =(const OdTvDbVectorRef&);

  /** \details
    Initializes this reference using a given object.
  */
  virtual void copyFrom(const OdRxObject*);

  /** \details
    Resets this vector reference.
  */
  virtual void reset();

  /** \details
    Checks whether this vector reference is valid.
  */
  virtual bool isValid() const;

  /** \details
    Checks whether this vector reference is empty.
  */
  virtual bool isEmpty() const;

  /** \details
    Returns a three-dimensional vector stored by this vector reference.
  */
  const OdGeVector3d vector() const;

  /** \details
    Sets a three-dimensional vector for this vector reference.
  */
  void set(const OdGeVector3d&);

  /** \details
    Creates an entity using this vector reference.
  */
  virtual OdTvDbEntity* createEntity() const;

  /** \details
    Evaluates and caches the geometry.
  */
  virtual OdResult evaluateAndCacheGeometry();

private:
  /*!DOM*/
  OdGeVector3d m_Vector;
};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbVectorRef class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbVectorRef> OdTvDbVectorRefPtr;


/** \details
  This class represents a reference to a coordinate system.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbCoordSystemRef : public OdRxObjectImpl<OdTvDbGeomRef>
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbCoordSystemRef);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbCoordSystemRef();
  OdTvDbCoordSystemRef(const OdGeMatrix3d&);
  OdTvDbCoordSystemRef(const OdTvDbCompoundObjectId&, const OdGeMatrix3d&); 
  OdTvDbCoordSystemRef(const OdArray<OdTvDbSubentRef*>&);
  OdTvDbCoordSystemRef(const OdTvDbCoordSystemRef&);

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbCoordSystemRef();

  /** \details
    Copies a given coordinate system reference to this reference.
  */
  OdTvDbCoordSystemRef& operator = (const OdTvDbCoordSystemRef&);

  /** \details
    Initializes this reference using a given object.
  */
  virtual void copyFrom(const OdRxObject*);

  /** \details
    Resets this coordinate system reference.
  */
  virtual void reset();

  /** \details
    Checks whether this coordinate system reference is valid.
  */
  virtual bool isValid() const;

  /** \details
    Checks whether this coordinate system reference is empty.
  */
  virtual bool isEmpty() const;

  /** \details
    Returns the transformation matrix of the coordinate system held by this reference.
  */
  const OdGeMatrix3d& coordSystem() const;

  /** \details
    Returns an entity ID held by this reference.
  */
  const OdTvDbCompoundObjectId& entityId() const;

  /** \details
    Returns an array of subent references held by this reference.
  */
  const OdArray<OdTvDbSubentRef*>& subentRefs() const;

  /** \details
    Sets this reference using a transformation matrix.
  */
  void set(const OdGeMatrix3d&);
  
  /** \details
    Sets this reference using an entity ID.
  */
  void set(const OdTvDbCompoundObjectId&);
  
  /** \details
    Sets this reference using an array of subent references held.
  */
  void set(const OdArray<OdTvDbSubentRef*>&);

  /** \details
    Creates an entity using this coordinate system reference.
  */
  virtual OdTvDbEntity* createEntity() const;

  /** \details
    Evaluates and caches the geometry.
  */
  virtual OdResult evaluateAndCacheGeometry();

private:
  /*!DOM*/
  OdGeMatrix3d m_CoordSystem;
  /*!DOM*/
  OdTvDbCompoundObjectId m_entityId;
  /*!DOM*/
  OdArray<OdTvDbSubentRef*> m_SubentRefs;
};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbCoordSystemRef class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbCoordSystemRef> OdTvDbCoordSystemRefPtr;

#include "TD_PackPop.h"

#endif // DbGeomRef_INCLUDED_
