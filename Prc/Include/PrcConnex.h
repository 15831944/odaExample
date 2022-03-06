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

#ifndef _PRCCONNEX_INCLUDED_
#define _PRCCONNEX_INCLUDED_ 
 

#include "PrcTopoItem.h"
#include "PrcBaseTopology.h"
#include "PrcShell.h"

/** \details 
<group PRC_Topology_Classes> 

Class representing a space region delimited by one or more shells.
*/
class PRC_TOOLKIT OdPrcConnex : public OdPrcTopoItem
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_TOPO(OdPrcConnex)
  //DOM-IGNORE-END

  /** \details
  Adds a new shell to the shell array.
  \param pShell [in] A new shell to be added to the array.
  */
  void addShell(const OdPrcShellPtr &pShell);

  /** \details
  Sets a new array of shells.
  \param arrShells [in] A new shell array to be set.
  */
  void setShells(const OdPrcShellPtrArray &arrShells);

  /** \details
  Returns the current array of shells.
  */
  const OdPrcShellPtrArray &shells() const;
  
  /** \details
  Returns current base topology data.
  Base topology data is returned as a reference to an OdPrcBaseTopology object, therefore it can be used to set new data.
  */
  OdPrcBaseTopology &baseTopology();

  /** \details
  Returns current base topology data.
  */
  const OdPrcBaseTopology &baseTopology() const;
};
SMARTPTR(OdPrcConnex);

#endif // _PRCCONNEX_INCLUDED_

