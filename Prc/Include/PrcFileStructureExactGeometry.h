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

#ifndef _PRCFILESTRUCTUREEXACTGEOMETRY_INCLUDED_
#define _PRCFILESTRUCTUREEXACTGEOMETRY_INCLUDED_ 
 
#include "PrcTopoContext.h"

/** \details 
<group PRC_Files_Structures_Assemblies>

Class implements exact geometry and topology data of the leaf items of the file structure tree.
Exact geometry consists of an array of topological contexts. A topological context contains an array of boundary representation bodies. 
Each exact geometry or topological entity belongs to only one context. 
*/
class PRC_TOOLKIT OdPrcFileStructureExactGeometry
{
private:
  OdPrcTopoContextPtrArray m_topological_context;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcFileStructureExactGeometry)
  //DOM-IGNORE-END

  /** \details 
  Returns the current topological context of the exact geometry file structure.
  The topological context is returned as a reference to an OdPrcTopoContextPtrArray object, therefore it can be used to set a new topological context.
  */
  OdPrcTopoContextPtrArray &topologicalContext();
  
  /** \details 
  Returns the current topological context of the exact geometry file structure.
  */
  const OdPrcTopoContextPtrArray &topologicalContext() const;

  /** \details 
  Updates co-edge neighbors for the exact geometry file structure.
  Co-edges are called neighboring if they point to the same edge.
  */
  void updateCoedgeNeighbours (void);
};

#endif // _PRCFILESTRUCTUREEXACTGEOMETRY_INCLUDED_

