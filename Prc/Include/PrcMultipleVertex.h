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

#ifndef _PRCMULTIPLEVERTEX_INCLUDED_
#define _PRCMULTIPLEVERTEX_INCLUDED_ 
 

#include "PrcTopoItem.h"
#include "PrcBaseTopology.h"

/** \details 
<group PRC_Topology_Classes> 

Class stores information about a vertex at the position that is the average value of extremity positions of all edges.
*/
class PRC_TOOLKIT OdPrcMultipleVertex : public OdPrcTopoItem
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_TOPO(OdPrcMultipleVertex)
  //DOM-IGNORE-END

  /** \details
  Returns the current array of points.
  The points array is returned as a reference to an OdGePoint3dArray object, therefore it can be used to set new points. 
  */
  OdGePoint3dArray &points();
  
  /** \details
  Returns the current array of points.
  */
  const OdGePoint3dArray &points() const;
  
  /** \details
  Returns current common topology data of the multiple vertex.
  Common topology data is returned as a reference to an OdPrcBaseTopology object, therefore it can be used to set new topology data. 
  */
  OdPrcBaseTopology &baseTopology();
  
  /** \details
  Returns current common topology data of the multiple vertex.
  */
  const OdPrcBaseTopology &baseTopology() const;
};
SMARTPTR(OdPrcMultipleVertex);

#endif // _PRCMULTIPLEVERTEX_INCLUDED_

