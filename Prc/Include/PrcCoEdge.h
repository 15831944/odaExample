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

#ifndef _PRCCOEDGE_INCLUDED_
#define _PRCCOEDGE_INCLUDED_ 
 

#include "PrcTopoItem.h"
#include "PrcBaseTopology.h"
#include "PrcCurve.h"
#include "PrcEdge.h"

/** \details 
<group PRC_Topology_Classes> 

Class stores data of an edge inside the loop.
*/
class PRC_TOOLKIT OdPrcCoEdge : public OdPrcTopoItem
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_TOPO(OdPrcCoEdge)
  //DOM-IGNORE-END

  /** \details
  Sets a new neighboring co-edge of the co-edge.
  
  \param pCoEdge [in] A pointer to a new neighboring co-edge to be set.
  */
  void setNeighCoEdge(OdPrcCoEdge* pCoEdge);
  
  /** \details
  Returns the current constant neighboring co-edge of the co-edge.
    */
  const OdPrcCoEdge* neighCoEdge() const;
  
  /** \details
  Returns the current UV curve of the co-edge.
  The UV curve is returned as a reference to an OdPrcCurvePtr object, therefore it can be used to set a new UV curve.
  */
  OdPrcCurvePtr &curveUV();
  
  /** \details
  Returns the current UV curve.
  */
  const OdPrcCurvePtr &curveUV() const;

  /** \details 
  Sets a new current edge.
  \param pEdge [in] A smart pointer to a PRC edge object to be set.
  */
  void setEdge(const OdPrcEdgePtr &pEdge);
  
  /** \details
  Returns the current edge.
  */
  const OdPrcEdgePtr &edge() const;
  
  /** \details
  Returns current topology data of the co-edge.
  Topology data is returned as a reference to an OdPrcBaseTopology object, therefore it can be used to set new topology data of the co-edge.
  */
  OdPrcBaseTopology &baseTopology();
  
  /** \details
  Returns current topology data of the co-edge.
  */
  const OdPrcBaseTopology &baseTopology() const;
  
  /** \details
  Sets a new UV curve orientation with respect to the loop.

  \param orientation_uv_with_loop [in] A new UV curve orientation to be set.
  */
  void setOrientationUvWithLoop(OdInt8 orientation_uv_with_loop);
  
  /** \details
  Returns the current UV curve orientation with respect to the loop.
  */
  OdInt8 orientationUvWithLoop() const;
  
  /** \details
  Sets a new co-edge orientation with respect to the loop.

  \param orientation_with_loop [in] A new co-edge orientation to be set.
  */
  void setOrientationWithLoop(OdInt8 orientation_with_loop);
  
  /** \details
  Returns the current co-edge orientation with respect to the loop.
  */
  OdInt8 orientationWithLoop() const;
};
SMARTPTR(OdPrcCoEdge);

#endif // _PRCCOEDGE_INCLUDED_

