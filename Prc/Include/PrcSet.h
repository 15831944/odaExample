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

#ifndef _PRCSET_INCLUDED_
#define _PRCSET_INCLUDED_ 
 

#include "PrcRepresentationItem.h"

/** \details 
<group PRC_Representation_Item_Classes> 

Class stores information about an array of representation items.
*/
class PRC_TOOLKIT OdPrcSet : public OdPrcRepresentationItem
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcSet)
  //DOM-IGNORE-END

  /** \details
  Returns the current array of representation item identifiers.
  The array of identifiers is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set a new identifiers array or modify the existing one.
  */
  OdPrcObjectIdArray &representationItem();
  
  /** \details
  Returns the current array of representation item identifiers.
  */
  const OdPrcObjectIdArray &representationItem() const;

protected:
  virtual OdUInt32 subSetAttributes (OdGiDrawableTraits * traits) const;
  virtual bool subWorldDraw(OdGiWorldDraw * pWd) const;
};
SMARTPTR(OdPrcSet);

#endif // _PRCSET_INCLUDED_

