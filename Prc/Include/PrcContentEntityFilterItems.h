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

#ifndef _PRCCONTENTENTITYFILTERITEMS_INCLUDED_
#define _PRCCONTENTENTITYFILTERITEMS_INCLUDED_ 
 

#include "PrcReference.h"

/** \details 
<group PRC_Files_Structures_Assemblies>

Class representing information for filtering by entities.
*/
class PRC_TOOLKIT OdPrcContentEntityFilterItems
{
private:
  OdPrcObjectIdArray  m_entities; // OdPrcReferencePtr
  bool                m_isInclusive;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcContentEntityFilterItems)
  //DOM-IGNORE-END

  /** \details
  Returns the current array of basic entity identifiers.
  The array is returned as a reference to an OdPrcObjectIdArray object, therefore it can be uset to set a new entities set. 
  */
  OdPrcObjectIdArray &entities();

  /** \details
  Returns the current array of basic entity identifiers.
  */
  const OdPrcObjectIdArray &entities() const;
  
  /** \details
  Sets a new value of the inclusive flag.
  Inclusive flag indicates whether the elements in the filter will be stored (if true) or not (if false).

  \param isInclusive [in] A new inclusive flag value to be set.
  */
  void setIsInclusive(bool isInclusive);

  /** \details
  Returns the current value of the inclusive flag.
  Inclusive flag indicates whether the elements in the filter will be stored (if true) or not (if false).
  */
  bool isInclusive() const;
};

#endif // _PRCCONTENTENTITYFILTERITEMS_INCLUDED_

