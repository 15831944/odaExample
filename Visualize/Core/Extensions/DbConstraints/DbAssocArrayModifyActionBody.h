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

#ifndef DbAssocArrayModifyActionBody_INCLUDED_
#define DbAssocArrayModifyActionBody_INCLUDED_

#include "DbAssocArrayActionBody.h"
#include "DbAssocArrayParameters.h"

#include "TD_PackPush.h"


/** \details
    <group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocArrayModifyParameters : public OdTvDbAssocArrayParameters
{
public:
  ODRX_DECLARE_MEMBERS( OdTvDbAssocArrayModifyParameters );

  OdTvDbAssocArrayModifyParameters();

  /** \details
    Destructor destroys an instance of this class.
    */
  virtual ~OdTvDbAssocArrayModifyParameters();

  /** \details
    Gets an array of items.
  */
  virtual OdResult getItems( OdArray<OdTvDbAssocArrayItemPtr>& items ) const;

protected:

  /** \details
    Gets the item locator, position, and transformation matrix. This method is pure and 
    must be overridden in derived classes.
  */
  virtual OdResult getItemPosition( const OdTvDbItemLocator& locator,
                                   OdGePoint3d& position,
                                   OdGeMatrix3d& xform ) const;

  /** \details
    Gets the item locator. This method is pure and must be overridden in derived classes.
  */
  virtual OdTvDbItemLocator getCanonicalForm( const OdTvDbItemLocator& locator ) const
  {
    return OdTvDbItemLocator();
  }

  OdTvDbAssocArrayModifyParameters(class OdTvDbImpAssocArrayModifyParameters* pImpl);
  
private:
  
};


typedef OdSmartPtr<OdTvDbAssocArrayModifyParameters> OdTvDbAssocArrayModifyParametersPtr;


/** \details
  This class represents an array of associated actions which can be evaluated to manage or locate the items.

  Library: Source *code* provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocArrayModifyActionBody : public OdTvDbAssocArrayActionBody
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocArrayModifyActionBody);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbAssocArrayModifyActionBody();

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbAssocArrayModifyActionBody();

  /** \details
    Get indices of overridden items.
  */
  OdResult getOverridenItems( OdArray<OdTvDbItemLocator> &indices ) const;
  
  /** \details
    Set indices of overridden items.
  */
  OdResult setOverridenItems( const OdArray<OdTvDbItemLocator> &indices);

  /** \details
    Checks whether an item of an associated array can be controlled either by created action 
    or by another action which modifies this item.
  */
  virtual bool controlsItem(const OdTvDbItemLocator &index) const;

  
  /** \details
    Creates associative array: action, action body, dependencies etc.
  */
  static OdResult createInstance( OdTvDbObjectId arrayId,
                                  const OdArray<OdTvDbItemLocator> &indices,
                                  const OdTvDbObjectIdArray &subEnt,
                                  OdTvDbVertexRef &basePoint,
                                  OdTvDbObjectId& actionBodyId);
 
};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbAssocArrayModifyActionBody class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbAssocArrayModifyActionBody> OdTvDbAssocArrayModifyActionBodyPtr;

#include "TD_PackPop.h"

#endif

