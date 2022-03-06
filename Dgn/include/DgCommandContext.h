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

#ifndef _ODDG_COMMANDCONTEXT_H_INCLUDED_
#define _ODDG_COMMANDCONTEXT_H_INCLUDED_

#include "DgExport.h"
#include "DgUserIO.h"
#include "Ed/EdCommandContext.h"
#include "OdError.h"
#include "DgDatabase.h"

//class OdDgDatabase;
class OdDgSelectionSet;
class OdDgCommandContext;

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDgCommandContext object pointers.
*/
typedef OdSmartPtr<OdDgCommandContext> OdDgCommandContextPtr;

#include "TD_PackPush.h"

/** \details
    This class defines the interface for I/O and database access 
    for custom commands during their execution.

    \remarks
    Client applications that invoke custom commands, should use an instance of this
    class (or a subclass) to pass to the OdEdCommandStack::executeCommand function.
    Using this class instead of a true instance of OdEdCommandContext provides
    custom commands with database access.

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgCommandContext : public OdEdCommandContext
{ 
public:
  ODRX_DECLARE_MEMBERS(OdDgCommandContext);

  /** \details
      Returns a database, for use in a custom command.
  */
  OdDgDatabase* database();

  OdDgUserIO* dbUserIO();
};



inline OdDgUserIO* OdDgCommandContext::dbUserIO()
{
  ODA_ASSERT(userIO() && userIO()->isKindOf(OdDgUserIO::desc()));
  return static_cast<OdDgUserIO*>(userIO());
}

inline OdDgDatabase* OdDgCommandContext::database()
{
  //ODA_ASSERT(baseDatabase()->isKindOf(OdDgDatabase::desc()));
  //return static_cast<OdDgDatabase*>(baseDatabase());
  //
  // support for ODA Drawings Explorer. 
  OdDgDatabase* pDb = OdDgDatabase::cast(baseDatabase()).get();
  if (!pDb)
    throw OdError(eNoDatabase);
  return pDb;
}

#include "TD_PackPop.h"

#endif //#ifndef _ODDG_COMMANDCONTEXT_H_INCLUDED_
