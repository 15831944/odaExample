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

#ifndef _PRCSHELL_INCLUDED_
#define _PRCSHELL_INCLUDED_ 
 

#include "PrcTopoItem.h"
#include "PrcBaseTopology.h"
#include "PrcFace.h"
#include "PrcShell.h"

/** \details 
<group PRC_Topology_Classes> 

Class stores information about an array of topological items.
*/
class PRC_TOOLKIT OdPrcShell : public OdPrcTopoItem
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_TOPO(OdPrcShell)
  //DOM-IGNORE-END

  /** \details
  Adds a new face to the shell.
  \param pFace [in] A new face to be added.
  */
  void addFace(const OdPrcFacePtr &pFace);

  /** \details
  Adds a new array of faces to the loop.
  \param arrFaces [in] A new array of faces to be added.
  */
  void setFaces(const OdPrcFacePtrArray &arrFaces);
  
  /** \details
  Returns the current array of the shell faces.
  */
  const OdPrcFacePtrArray &faces() const;
  
  /** \details
  Returns current common topology data of the shell.
  Common topology data is returned as a reference to an OdPrcBaseTopology object, therefore it can be used to set new common topology data.
  */
  OdPrcBaseTopology &baseTopology();
  
  /** \details
  Returns current common topology data of the shell.
  */
  const OdPrcBaseTopology &baseTopology() const;
  
  /** \details
  Sets a new value of the closed flag.
  The closed flag indicates whether the shell is closed (true) or not (false).

  \param shell_is_closed [in] A new closed flag value to be set.
  */
  void setShellIsClosed(bool shell_is_closed);
  
  /** \details
  Returns the current value of the closed flag.
  The closed flag indicates whether the shell is closed (true) or not (false).
  */
  bool shellIsClosed() const;

  /** \details
  Updates the current value of the closed flag.
  The closed flag indicates whether the shell is closed (true) or not (false).
  */
  bool updateShellIsClosedFlag (void);
};
SMARTPTR(OdPrcShell);

#endif // _PRCSHELL_INCLUDED_

