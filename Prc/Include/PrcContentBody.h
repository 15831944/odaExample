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

#ifndef _PRCCONTENTBODY_INCLUDED_
#define _PRCCONTENTBODY_INCLUDED_ 
 

#include "PrcBaseTopology.h"

/** \details 
<group PRC_Topology_Classes> 

Class stores additional data of base topological entities.
*/
class PRC_TOOLKIT OdPrcContentBody
{
private:
  OdPrcBaseTopology m_BaseTopology;
  OdInt8            m_boundingBoxBehaviour;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcContentBody)
  //DOM-IGNORE-END

  /** \details
  Returns the current base topology information.
  The topology information is returned as a reference to an OdPrcBaseTopology object, therefore it can be used to set new topology information.
  */
  OdPrcBaseTopology &baseTopology();
  
  /** \details
  Returns the current base topology information.
  */
  const OdPrcBaseTopology &baseTopology() const;
  
  /** \details
  Sets a new bounding box behavior.
  
  \param boundingBoxBehaviour [in] A new bounding box behavior to be set.
  */
  void setBoundingBoxBehaviour(OdInt8 boundingBoxBehaviour);
  
  /** \details
  Returns the current bounding box behavior.
  */
  OdInt8 boundingBoxBehaviour() const;
};

#endif // _PRCCONTENTBODY_INCLUDED_

