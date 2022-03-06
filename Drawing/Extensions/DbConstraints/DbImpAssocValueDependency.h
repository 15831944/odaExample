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
#ifndef DbImpAssocValueDependency_INCLUDED_
#define DbImpAssocValueDependency_INCLUDED_ /*!DOM*/

#include "DbConstraintsExports.h"
#include "DbImpAssocDependency.h"
#include "OdString.h"
#include "DoubleArray.h"
#include "DbEvalVariant.h"

#include "TD_PackPush.h"

/** \details
  This class that represents the custom implementation of the dependency on a numerical variable. 

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdDbImpAssocValueDependency : public OdDbImpAssocDependency
{
public: 
  /** \details
    Constructor creates an instance of this class.
  */
  OdDbImpAssocValueDependency();

  /** \details
    Returns the name of the referenced value or an empty string if the value name is not required.
  */
  const OdString& valueName() const;

  /** \details
    Set the arbitrary string as the name of the referenced value.
  */
  OdResult setValueName(const OdString& newValueName);

  bool hasCachedValue() const;

  /** \details
    Returns the value of the dependent-on object or cached value if can't open the dependent-on object.
  */
  OdResult getDependentOnObjectValue(OdDbEvalVariantPtr& objectValue) const;

  /** \details
    Sets the value for the dependent-on object and updates the cached value.
  */
  OdResult setDependentOnObjectValue(const OdDbEvalVariant* newObjectValue);

  /** \details
    Updates dependency cache and set its status to kIsUpToDateAssocStatus.
  */
  virtual void evaluate(OdDbAssocDependency* thisDependency);

  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdDbDxfFiler* pFiler) const;

  /** \details
    Checks whether the changes are relevant to the depended-on object for this dependency type.
  */
  virtual bool isRelevantChange(const OdDbAssocDependency *pDep) const;

  /** \details
    Updates the object depends on the dependency, based on the information obtained from the owning 
    action.
  */
  virtual OdResult updateDependentOnObject(OdDbAssocDependency * pDep);

  /** \details
    Returns cached value of the dependent-on object.
  */
  OdResult getDependentOnObjectCachedValue(OdDbEvalVariantPtr& cachedValue) const;

protected:
  /*!DOM*/
  OdString m_valueName;
  /*!DOM*/
  OdDbEvalVariantPtr m_cashedValue;
};

#include "TD_PackPop.h"

#endif
