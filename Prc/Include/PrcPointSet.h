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

#ifndef _PRCPOINTSET_INCLUDED_
#define _PRCPOINTSET_INCLUDED_ 
 

#include "PrcRepresentationItemContent.h"
#include "PrcRepresentationItem.h"

/** \details 
<group PRC_Representation_Item_Classes> 

Class representing a group of 3D points.
*/
class PRC_TOOLKIT OdPrcPointSet : public OdPrcRepresentationItem
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcPointSet)
  //DOM-IGNORE-END

  /** \details
  Returns the current array of 3D points.
  The array of 3D points is returned as a reference to an OdGePoint3dArray object, therefore it can be used to set new 3D points.
  */
  OdGePoint3dArray &point();

  /** \details
  Returns the current array of 3D points.
  */
  const OdGePoint3dArray &point() const;

protected:
  virtual OdUInt32 subSetAttributes (OdGiDrawableTraits * traits) const;
  virtual bool subWorldDraw (OdGiWorldDraw * pWd) const;
};
SMARTPTR(OdPrcPointSet);

#endif // _PRCPOINTSET_INCLUDED_

