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

#ifndef OdTvDbAssoc2dConstraintGroupImpl_INCLUDED
#define OdTvDbAssoc2dConstraintGroupImpl_INCLUDED

#include "OdConstraintGroupNode.h"
#include "OdConstraintGroupNodeImpl.h"

#include "TD_PackPush.h"

/** \details
  This static class provides obtaing the custom implementation of the planar constraint group node.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssoc2dConstraintGroupImpl
{
public:
  /** \details
    Gets an implementation of the planar constraint group node.
  */
  static OdConstraintGroupNodeImpl* getConstraintGroupNodeImpl(OdConstraintGroupNode *node)
  {
    return node->m_pImpl;
  }
  static OdConstraintGroupNodeImpl* getConstraintGroupNodeImpl(const OdConstraintGroupNode *node)
  {
    return const_cast<OdConstraintGroupNodeImpl*>(node->m_pImpl);
  }
};
#include "TD_PackPop.h"

#endif
