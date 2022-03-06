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

#ifndef _PRCUNIQUEVERTEX_INCLUDED_
#define _PRCUNIQUEVERTEX_INCLUDED_ 
 

#include "PrcTopoItem.h"
#include "PrcBaseTopology.h"

/** \details 
<group PRC_Topology_Classes> 

Class representing an unique vertex. A vertex position is specified with a tolerance and a 3D absolute position.
*/
class PRC_TOOLKIT OdPrcUniqueVertex : public OdPrcTopoItem
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_TOPO(OdPrcUniqueVertex)
  //DOM-IGNORE-END

  /** \details
  Returns the current 3D point which specifies the vertex position.
  The 3D point is returned as a reference to an OdGePoint3d object, therefore it can be used to set a new 3D point to specify the vertex.
  */
  OdGePoint3d &point();
  
  /** \details
  Returns the current 3D point which specifies the vertex position.
  */
  const OdGePoint3d &point() const;

  /** \details
  Returns current base topology data.
  Base topology data is returned as an OdPrcBaseTopology object, therefore it can be used to set new topology data.
  */
  OdPrcBaseTopology &baseTopology();

  /** \details
  Returns current base topology data.
  */  
  const OdPrcBaseTopology &baseTopology() const;

  /** \details
  Sets a new tolerance value.

  \param tolerance [in] A new tolerance value to be set.
  */
  void setTolerance(double tolerance);
  
  /** \details
  Returns the current tolerance value.
  */
  double tolerance() const;

  /** \details
  Sets a new value of the tolerance flag. 
  The tolerance flag indicates whether the tolerance is associated with the vertex (true) or not (false).

  \param have_tolerance [in] A new value of the tolerance flag to be set.
  */
  void setHaveTolerance(bool have_tolerance);
  
  /** \details
  Returns the current value the tolerance flag.
  The tolerance flag indicates whether the tolerance is associated with the vertex (true) or not (false).
  */
  bool haveTolerance() const;
};
SMARTPTR(OdPrcUniqueVertex);

#endif // _PRCUNIQUEVERTEX_INCLUDED_

