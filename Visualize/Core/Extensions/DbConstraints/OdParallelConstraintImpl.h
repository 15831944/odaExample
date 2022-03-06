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

#ifndef OdParallelConstraintImpl_INCLUDED_
#define OdParallelConstraintImpl_INCLUDED_/*!DOM*/

#include "DbConstraintsExports.h"
#include "OdGeomConstraint.h"
#include "OdGeomConstraintImpl.h"

#include "TD_PackPush.h"

/** \details
  This class represents custom implementation of a parallel constraint node in 
  the owning constraint group. This constraint can be applied between two lines.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdParallelConstraintImpl : public OdGeomConstraintImpl
{
public:
  /** \details
    Constructor creates an instance of this class.
  */
  OdParallelConstraintImpl();

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdParallelConstraintImpl();

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
    Returns the node ID of the datum line.
  */
  OdConstraintGroupNodeId getDatumLineIdx() const { return m_datumLineIdx; }

  /** \details
    Sets the datum line using the node ID.
  */
  void setDatumLineIdx(OdConstraintGroupNodeId id);
protected:
  /*!DOM*/
  OdConstraintGroupNodeId m_datumLineIdx;
};

#include "TD_PackPop.h"

#endif

