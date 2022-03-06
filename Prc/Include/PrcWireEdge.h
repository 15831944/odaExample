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

#ifndef _PRCWIREEDGE_INCLUDED_
#define _PRCWIREEDGE_INCLUDED_ 
 

#include "PrcTopoItem.h"
#include "PrcContentWireEdge.h"

/** \details 
<group PRC_Representation_Item_Classes> 

Class representing a 3D curve which has a trimming interval for limiting the geometric definition of the curve.
*/
class PRC_TOOLKIT OdPrcWireEdge : public OdPrcTopoItem
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_TOPO(OdPrcWireEdge)
  //DOM-IGNORE-END

  /** \details
  Returns the current wire edge content representing the 3D curve and the trimming interval
  for restricting a wire edge to a subset of a curve.
  The wire edge content is returned as a reference to an OdPrcContentWireEdge object, therefore it can be used to set new wire edge content or modify the existing one.
  */
  OdPrcContentWireEdge &contentWireEdge();
  
  /** \details
  Returns the current wire edge content representing the 3D curve and the trimming interval
  for restricting a wire edge to a subset of a curve.
  */
  const OdPrcContentWireEdge &contentWireEdge() const;
};
SMARTPTR(OdPrcWireEdge);

#endif // _PRCWIREEDGE_INCLUDED_

