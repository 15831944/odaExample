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

#ifndef _PRCMARKUPLEADER_INCLUDED_
#define _PRCMARKUPLEADER_INCLUDED_ 
 

#include "PrcObjectId.h"
#include "PrcBaseWithGraphics.h"
#include "PrcUserData.h"
#include "PrcBaseTessData.h"

SMARTPTR(OdPrcMarkupLeader);

/** \details
    <group PRC_Markup_Classes>
    Class stores data of a markup leader.
*/
class PRC_TOOLKIT OdPrcMarkupLeader : public OdPrcBaseWithGraphics
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcMarkupLeader);
  //DOM-IGNORE-END

  /** \details
  Returns current common tessellation data.
  Common tessellation data is returned as a reference to an OdPrcBaseTessDataPtr object, therefore it can be used to set new common tessellation data.
  */
  OdPrcBaseTessDataPtr &tessellation();
  
  /** \details
  Returns current common tessellation data.
  */
  const OdPrcBaseTessDataPtr &tessellation() const;
  
  /** \details
  Returns current user defined data.
  User defined data is returned as a reference to an OdPrcUserData object, therefore it can be used to set new user defined data.
  */
  OdPrcUserData &userData();
  
  /** \details
  Returns current user defined data.
  */
  const OdPrcUserData &userData() const;

  /** \details 
  Returns an identifier of the item linked with the leader. 
  The item is returned as a referenece to an OdPrcObjectId therefore it can be used to change the identifier.
  */
  OdPrcObjectId &linkedItem();

  /** \details 
  Returns an identifier of the item linked with the leader. 
  */
  const OdPrcObjectId &linkedItem() const;

  /** \details 
  Returns an identifier of the next leader. 
  The next leader is returned as a referenece to an OdPrcObjectId therefore it can be used to change the identifier.
  */
  OdPrcObjectId &nextLeader();

  /** \details 
  Returns an identifier of the next leader. 
  */
  const OdPrcObjectId &nextLeader() const;

protected:
  virtual OdUInt32 subSetAttributes (OdGiDrawableTraits * traits) const;
  virtual bool subWorldDraw (OdGiWorldDraw * pWd) const;
  virtual void subViewportDraw (OdGiViewportDraw * pVd) const;
};

#endif // _PRCMARKUPLEADER_INCLUDED_

