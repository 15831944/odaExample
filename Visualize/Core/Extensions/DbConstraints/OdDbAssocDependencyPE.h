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
#ifndef OdTvDbAssocDependencyPE_INCLUDED_
#define OdTvDbAssocDependencyPE_INCLUDED_ /*!DOM*/

#include "DbConstraintsExports.h"

#include "TD_PackPush.h"
#include "DbObject.h"

/** \details
  This class provides the base protocol extension class that declares the protocol for 
  working with objects and entities to control the asociated dependencies attached to them.
 
  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocDependencyPE : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocDependencyPE);

  /** \details
    Allows the attaching of dependencies for objects and entities.

    \remarks
    Returns always False.
  */
  virtual bool allowsDependencies(const OdTvDbObject* pObject, bool isWriteDependency) const
    { return false; }

};

#include "TD_PackPop.h"

#endif
