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

#ifndef _PRCDIRECTION_INCLUDED_
#define _PRCDIRECTION_INCLUDED_ 
 

#include "PrcRepresentationItemContent.h"
#include "PrcRepresentationItem.h"

/** \details 
<group PRC_Representation_Item_Classes> 

Class representing a direction vector.
*/
class PRC_TOOLKIT OdPrcDirection : public OdPrcRepresentationItem
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcDirection)
  //DOM-IGNORE-END
  
  /** \details
  Returns the current coordinates of the direction's start point.
  The start point is returned as a reference to an OdGePoint3d object, therefore it can be uset to set a new direction start point.
  */
  OdGePoint3d &origin();

  /** \details
  Returns the current coordinates of the direction's start point.
  */
  const OdGePoint3d &origin() const;

  /** \details
  Returns the current direction vector.
  The direction vector is returned as a reference to an OdGeVector3d object, therefore it can be used to set a new direction vector.
  */
  OdGeVector3d &direction();

  /** \details
  Returns the current direction vector.
  */
  const OdGeVector3d &direction() const;

  /** \details
  Sets a new value of the origin flag.
  The origin flag indicates whether the direction has an origin (if true).

  \param has_origin [in] A new flag value to be set.
  */
  void setHasOrigin(bool has_origin);

  /** \details
  Returns the current value of the origin flag.
  The origin flag indicates whether the direction has an origin (if true).
  */
  bool hasOrigin() const;

};
SMARTPTR(OdPrcDirection);

#endif // _PRCDIRECTION_INCLUDED_

