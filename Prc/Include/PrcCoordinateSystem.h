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

#ifndef _PRCCOORDINATESYSTEM_INCLUDED_
#define _PRCCOORDINATESYSTEM_INCLUDED_ 
 

#include "PrcTransformation3d.h"
#include "PrcRepresentationItemContent.h"
#include "PrcRepresentationItem.h"

/** \details 
<group PRC_Representation_Item_Classes> 

Class representing a coordinate system.
*/
class PRC_TOOLKIT OdPrcCoordinateSystem : public OdPrcRepresentationItem
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcCoordinateSystem)
  //DOM-IGNORE-END

  /** \details 
  Destroys the coordinate system object.
  */
  virtual ~OdPrcCoordinateSystem();

  /** \details
  Returns current 3D coordinates. 
  3D coordinates are returned as a reference to an OdPrcTransformation3d object, therefore it can be used to set new coordinates.
  */
  OdPrcTransformation3d& axisSet();

  /** \details
  Returns current 3D coordinates. 
  */
  const OdPrcTransformation3d& axisSet() const;
};
SMARTPTR(OdPrcCoordinateSystem);

#endif // _PRCCOORDINATESYSTEM_INCLUDED_

