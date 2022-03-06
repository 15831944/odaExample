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

#ifndef _PRCSINGLEWIREBODY_INCLUDED_
#define _PRCSINGLEWIREBODY_INCLUDED_ 
 

#include "PrcBody.h"
#include "PrcContentBody.h"
#include "PrcTopoItem.h"

/** \details 
<group PRC_Topology_Classes> 

Class stores information about a single wire body.
*/
class PRC_TOOLKIT OdPrcSingleWireBody : public OdPrcBody
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_BODY(OdPrcSingleWireBody)
  //DOM-IGNORE-END

  /** \details
  Returns the current wire edge.
  The wire edge is returned as a reference to an OdPrcTopoItemPtr object, therefore it can be used to set a new wire edge of the body.
  */
  OdPrcTopoItemPtr &wireEdge();
  
  /** \details
  Returns the current wire edge.
  */
  const OdPrcTopoItemPtr &wireEdge() const;
  
  /** \details
  Returns the current content body.
  The content body is returned as a reference to an OdPrcContentBody object, therefore it can be used to set a new content body.
  */
  OdPrcContentBody &contentBody();
  
  /** \details
  Returns the current content body.
  */
  const OdPrcContentBody &contentBody() const;
  
  /** \details
  Returns the current serial type of the object.
  */
  virtual OdUInt32 getSerialType() const;

protected:
  virtual OdUInt32 subSetAttributes (OdGiDrawableTraits * traits) const;
  virtual bool subWorldDraw (OdGiWorldDraw * pWd) const;
};
SMARTPTR(OdPrcSingleWireBody);

#endif // _PRCSINGLEWIREBODY_INCLUDED_

