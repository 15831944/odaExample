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

#ifndef _PRCEDGE_INCLUDED_
#define _PRCEDGE_INCLUDED_ 
 

#include "PrcTopoItem.h"
#include "PrcContentWireEdge.h"
#include "PrcTopoItem.h"

/** \details 
<group PRC_Representation_Item_Classes> 

Class representing an edge which is a bounded segment of a curve.
*/
class PRC_TOOLKIT OdPrcEdge : public OdPrcTopoItem
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_TOPO(OdPrcEdge)
  //DOM-IGNORE-END
  
  /** \details 
  Sets a new end vertex for the edge.
  \param pEndVertex [in] A smart pointer to a topological item object to be used as an ending vertex.
  */
  void setEndVertex(const OdPrcTopoItemPtr &pEndVertex);
  
  /** \details
  Returns the current end vertex.
  */
  const OdPrcTopoItemPtr &vertexEnd() const;

  /** \details 
  Sets a new start vertex for the edge.
  \param pStartVertex [in] A smart pointer to a topological item object to be used as a starting vertex.
  */
  void setStartVertex(const OdPrcTopoItemPtr &pStartVertex);

  /** \details
  Returns the current start vertex.
  */
  const OdPrcTopoItemPtr &vertexStart() const;

  /** \details
  Returns the current wire edge content.
  The wire edge content is returned as a reference to an OdPrcContentWireEdge object, therefore it can be used to set a new wire edge content.
  */
  OdPrcContentWireEdge &contentWireEdge();

  /** \details
  Returns the current wire edge content.
  */
  const OdPrcContentWireEdge &contentWireEdge() const;

  /** \details
  Sets a new tolerance value.
  If the tolerance is 0.0 the topological context tolerance is used.
  \param tolerance [in] A new tolerance value to be set.
  */
  void setTolerance(double tolerance);

  /** \details
  Returns the current tolerance value.
  If the tolerance is 0.0 the topological context tolerance must be used.
  */
  double tolerance() const;
};
SMARTPTR(OdPrcEdge);

#endif // _PRCEDGE_INCLUDED_

