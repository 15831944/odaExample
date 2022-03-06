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

#ifndef _PRCBREPMODEL_INCLUDED_
#define _PRCBREPMODEL_INCLUDED_ 
 

#include "PrcRepresentationItemContent.h"
#include "PrcRepresentationItem.h"
#include "BrepBuilder/BrepBuilder.h"

/** \details 
<group PRC_Representation_Item_Classes> 

Class stores information about a boundary representation model.
*/
class PRC_TOOLKIT OdPrcBrepModel : public OdPrcRepresentationItem
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcBrepModel)
  //DOM-IGNORE-END

  /** \details 
  Sets a new value of the closed body flag.
  
  \param is_closed [in] A new value of the flag to be set.
  The flag is equal to true if the body is closed
        or false if it is not.
  */
  void setIsClosed(bool is_closed);
  
  /** \details 
  Returns the current value of the closed body flag.
  
  \returns The flag is equal to true if the body is closed
        or false if it is not.
  */
  bool isClosed() const;

  /** \details 
  Updates the current value of the closed body flag.
  
  \returns Returns eOk if the closed body flag has been successfully updated or eInvalidInput in the other case.
  */
  OdResult updateIsClosedFlag();

protected:
  virtual OdUInt32 subSetAttributes (OdGiDrawableTraits * traits) const;
  virtual bool subWorldDraw (OdGiWorldDraw * pWd) const;
};
SMARTPTR(OdPrcBrepModel);

/** \details
Creates a new Brep Builder instance of a specified Brep type. 
\param bbuilder [out] A reference to an Brep builder instance to be created.
\param bbType   [in]  A Brep type value.
\returns Returns the result of the creation operation. If the builder was successfully created, the method return the eOk value, otherwise it returns an appropriate error code. 
*/
OdResult PRC_TOOLKIT createBrepBuilder(OdBrepBuilder& bbuilder, BrepType bbType);

#endif // _PRCBREPMODEL_INCLUDED_

