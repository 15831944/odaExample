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

#ifndef _PRCPOLYBREPMODEL_INCLUDED_
#define _PRCPOLYBREPMODEL_INCLUDED_ 
 

#include "PrcRepresentationItemContent.h"
#include "PrcRepresentationItem.h"

/** \details 
<group PRC_Representation_Item_Classes> 

Class representing a PolyBrepModel defined with tessellation data.
*/
class PRC_TOOLKIT OdPrcPolyBrepModel : public OdPrcRepresentationItem
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcPolyBrepModel)
  //DOM-IGNORE-END
  
  /** \details
  Sets a new value of the closed flag.
  The closed flag indicates whether the tessellation is closed (if true) or opened (if false).

  \param is_closed [in] A new flag value to be set.
  */
  void setIsClosed(bool is_closed);
  
  /** \details
  Returns the current value of the closed flag. 
  The closed flag indicates whether the tessellation is closed (if true) or opened (if false).
  */
  bool isClosed() const;

protected:
  virtual OdUInt32 subSetAttributes (OdGiDrawableTraits * traits) const;
  virtual bool subWorldDraw (OdGiWorldDraw * pWd) const;
};
SMARTPTR(OdPrcPolyBrepModel);

#endif // _PRCPOLYBREPMODEL_INCLUDED_

