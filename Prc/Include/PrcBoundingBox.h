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

#ifndef _PRCBOUNDINGBOX_INCLUDED_
#define _PRCBOUNDINGBOX_INCLUDED_ 
 
#include "Ge/GeExtents3d.h"
/** \details
<group PRC_Datatypes_Classes>

Class stores information about a bounding box, which has sides that are parallel to the XYZ coordinate planes.
*/
class PRC_TOOLKIT OdPrcBoundingBox
{
private:
  OdGeExtents3d m_extents;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcBoundingBox)
  //DOM-IGNORE-END

  /** \details
    Returns the current box.
    Box is returned as a reference to an OdGeExtents3d object, therefore it can be used to set a new Box.
  */
  OdGeExtents3d & box();
  /** \details
    Returns the current box.
  */
  const OdGeExtents3d & box() const;
};

#endif // _PRCBOUNDINGBOX_INCLUDED_

