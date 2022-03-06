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

#ifndef DbAssocValueDependency_INCLUDED_
#define DbAssocValueDependency_INCLUDED_ /*!DOM*/

#include "DbConstraintsExports.h"
#include "DbAssocDependency.h"
#include "OdString.h"
#include "DoubleArray.h"
#include "DbEvalVariant.h"

#include "TD_PackPush.h"

/** \details
  This class that represents a dependency on a scalar value, same as on a numerical variable. 
  The dependent-on object requires the associated value provider protocol extension class 
  to obtain the value from the object.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocValueDependency : public OdTvDbAssocDependency
{
public: 
  ODRX_DECLARE_MEMBERS(OdTvDbAssocValueDependency);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbAssocValueDependency(bool createImp = true);

  /** \details
    Returns the name of the referenced value or an empty string if the value name is not required.
  */
  const OdString& valueName() const;

  /** \details
    Set the arbitrary string as the name of the referenced value.
  */
  OdResult setValueName(const OdString& newValueName);

  /** \details
    Returns the value of the dependent-on object.
  */
  OdResult getDependentOnObjectValue(OdTvDbEvalVariantPtr& objectValue) const;

  /** \details
    Sets the value for the dependent-on object and updates the cached value.
  */
  OdResult setDependentOnObjectValue(const OdTvDbEvalVariantPtr& newObjectValue);


  /** \details
    Returns the cached value of the dependent-on object.
  */
  OdResult getDependentOnObjectCachedValue(OdTvDbEvalVariantPtr& cachedValue) const;
};


/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbAssocValueDependency class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbAssocValueDependency> OdTvDbAssocValueDependencyPtr;

#include "TD_PackPop.h"

#endif
