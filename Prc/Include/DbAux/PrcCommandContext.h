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

#ifndef _ODPRCCOMMANDCONTEXT_H_INCLUDED_
#define _ODPRCCOMMANDCONTEXT_H_INCLUDED_

#include "PrcFile.h"
#include "Ed/EdBaseUserIO.h"
#include "Ed/EdCommandContext.h"
#include "OdError.h"

class OdPrcFile;
class OdPrcCommandContext;

#include "TD_PackPush.h"

/** \details 
This class defines the interface for I/O operations and database access 
for custom commands during their execution.

\remarks 
Client applications that invoke custom commands should use an instance of this
class (or a subclass) to pass to the OdEdCommandStack::executeCommand function.
Using this class instead of a true instance of OdEdCommandContext provides
custom commands with database access.

<group PRC_DbAux_Classes>
*/
class PRC_TOOLKIT OdPrcCommandContext : public OdEdCommandContext
{ 
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcCommandContext);
  //DOM-IGNORE-END

  /** \details 
  Returns a database pointer for using in a custom command.
  */
  virtual OdPrcFile* database();

  /** \details 
  Returns the user IO object for this CommandContext object.
  */
  OdEdBaseUserIO* dbUserIO();
};



inline OdEdBaseUserIO*
OdPrcCommandContext::dbUserIO()
{
  ODA_ASSERT(userIO() && userIO()->isKindOf(OdEdBaseUserIO::desc()));
  return static_cast<OdEdBaseUserIO*>(userIO());
}

inline OdPrcFile*
OdPrcCommandContext::database()
{
  OdPrcFile* pDb = OdPrcFile::cast(baseDatabase()).get();
  return pDb;
}

/** \details 
This template class is a specialization of the OdSmartPtr class for OdPrcCommandContext object pointers.
*/
typedef OdSmartPtr<OdPrcCommandContext> OdPrcCommandContextPtr;

#include "TD_PackPop.h"

#endif //#ifndef _ODPRCCOMMANDCONTEXT_H_INCLUDED_
