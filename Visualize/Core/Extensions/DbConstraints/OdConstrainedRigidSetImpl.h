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

#ifndef OdConstrainedRigidSetImpl_INCLUDED
#define OdConstrainedRigidSetImpl_INCLUDED

#include "OdConstrainedGeometryImpl.h"

#include "TD_PackPush.h"

/** \details
  This class represents custom implementation of the constrained rigid set node in the owning constraint group. 

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdConstrainedRigidSetImpl : public OdConstrainedGeometryImpl
{
public:
  /** \details
    Constructor creates an instance of this class.
  */
  OdConstrainedRigidSetImpl();

  /** \details
    Initializes this constrained rigid set.
  */
  virtual OdResult init(OdTvDbObjectId depId);

  /** \details
    Adds given OdConstrainedGeometry object to this rigid set.
  */
  OdResult addConstrainedGeom(OdConstraintGroupNodeId geomId);

  /** \details
    Removes OdConstrainedGeometry with given id from this rigid set
  */
  OdResult removeConstrainedGeom(OdConstraintGroupNodeId geomId);

  /** \details
    Returns the number of constrained geometries in the group.
  */
  int  numOfConstrainedGeoms() const;

  /** \details
    Returns a pointer which refers to the constrained geometry at the given index.
  */
  OdConstrainedGeometry*  getConstrainedGeomAt(int index) const;

  /** \details
    Returns the transformation matrix for this rigid set relative to the plane of the owning constraint group.
  */
  OdGeMatrix3d  transform() const;

  /** \details
    Returns the original transformation matrix for this rigid set relative to the plane of the owning constraint group.
  */
  OdGeMatrix3d originalTransform() const;

  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  /** \details
    Applies the transformation matrix for this rigid set.
  */
  void setTransform(const OdGeMatrix3d &val);

  /** \details
    Sets data from a given geometry dependency using transformation matrix.
  */
  virtual OdResult setDataFromGeomDependency(const OdTvDbObjectId geomDependencyId,
                                             const OdGeMatrix3d& matrFromWrd);

  /** \details
    Updates the database object.
  */
  virtual OdResult updateDbObject(OdTvDbObject *pObj, OdTvDbAssocGeomDependency* pDep, const OdGeMatrix3d& matrToWrd);
protected:
  /*!DOM*/
  bool m_unk_Bool;
  /*!DOM*/
  OdGeMatrix3d m_matrix;
  /*!DOM*/
  OdGeMatrix3d m_origMatrix;
  /*!DOM*/
  OdArray<OdConstraintGroupNodeId,
  /*!DOM*/
  OdMemoryAllocator<OdConstraintGroupNodeId> > m_connections;
};

#include "TD_PackPop.h"

#endif
