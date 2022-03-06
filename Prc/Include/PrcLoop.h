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

#ifndef _PRCLOOP_INCLUDED_
#define _PRCLOOP_INCLUDED_ 
 

#include "PrcTopoItem.h"
#include "PrcBaseTopology.h"
#include "PrcCoEdge.h"

/** \details 
<group PRC_Topology_Classes> 

Class stores information about a loop. A loop is a list of co-edges that bound a piece of a face.
*/
class PRC_TOOLKIT OdPrcLoop : public OdPrcTopoItem
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_TOPO(OdPrcLoop)
  //DOM-IGNORE-END

  /** \details
  Adds a new co-edge to the loop.
  \param pCoEdge [in] A new co-edge to be added.
  */
  void addCoEdge(const OdPrcCoEdgePtr &pCoEdge);

  /** \details
  Adds a new array of co-edges to the loop.
  \param arrCoEdges [in] A new array of co-edges to be added.
  */
  void setCoEdges(const OdPrcCoEdgePtrArray &arrCoEdges);
  
  /** \details
  Returns the current array of co-edges in the loop.
  */
  const OdPrcCoEdgePtrArray &coedges() const;
  
  /** \details
  Returns current common topology data.
  Common topology data is returned as a reference to an OdPrcBaseTopology object, therefore it can be used to set new topology data.
  */
  OdPrcBaseTopology &baseTopology();
  
  /** \details
  Returns current common topology data.
  */
  const OdPrcBaseTopology &baseTopology() const;
  
  /** \details
  Sets a new loop orientation with respect to the surface normal.

  \param orientation_with_surface [in] A new loop orientation value to be set.
  */
  void setOrientationWithSurface(OdInt8 orientation_with_surface);
  
  /** \details
  Returns the current loop orientation with respect to the surface normal.
  */
  OdInt8 orientationWithSurface() const;
};
SMARTPTR(OdPrcLoop);

#endif // _PRCLOOP_INCLUDED_

