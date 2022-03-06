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

#ifndef OdExplicitConstraintImpl_INCLUDED
#define OdExplicitConstraintImpl_INCLUDED

#include "OdGeomConstraint.h"
#include "OdGeomConstraintImpl.h"

#include "TD_PackPush.h"

/** \details
  This class represents custom implementation of a dimensional constraint node in 
  the owning constraint group.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdExplicitConstraintImpl : public OdGeomConstraintImpl
{
public:
  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdExplicitConstraintImpl();

  /** \details
    Returns an object ID of the dimension dependency object referenced from the dimensional constraint node.
  */
  OdTvDbObjectId dimDependencyId() const;

  /** \details
    Set the object ID of the dimension dependency object to be referenced from the dimensional constraint node.
  */
  OdResult setDimDependencyId(const OdTvDbObjectId& dimDependencyId);

  /** \details
    Returns an object ID of the dependency object referenced from this constraint node.
  */
  OdTvDbObjectId valueDependencyId() const;

  /** \details
    Sets the object ID of the dependency object to be referenced from this constraint node.
  */
  OdResult setValueDependencyId(const OdTvDbObjectId& valueDependencyId);

  /** \details
    Returns the value of the dimensional constraint object measured from units of the constained geometries. 
  */
  OdResult getMeasuredValue(double& val) const;

  /** \details
    Updates the dimensional dependencies.
  */
  virtual void updateDimDependency(const OdGeMatrix3d& matrToWrd) = 0;

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

protected:
  /** \details
    Constructor creates an instance of this class.
  */
  OdExplicitConstraintImpl();

  /*!DOM*/
  OdTvDbObjectId m_dimDependencyId;
  /*!DOM*/
  OdTvDbObjectId m_valueDependencyId;
};

#include "TD_PackPop.h"

#endif
