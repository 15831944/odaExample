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

#ifndef _ODDBCOMMANDCONTEXT_H_INCLUDED_
#define _ODDBCOMMANDCONTEXT_H_INCLUDED_

#include "DbExport.h"
#include "DbUserIO.h"
#include "Ed/EdCommandContext.h"
#include "OdError.h"

class OdTvDbDatabase;
class OdTvDbCommandContext;

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbCommandContext object pointers.
*/
typedef OdSmartPtr<OdTvDbCommandContext> OdTvDbCommandContextPtr;

#include "TD_PackPush.h"

/** \details
    This class defines the interface for I/O and database access 
    for custom commands during their execution.

    \remarks
    Client applications that invoke custom commands, should use an instance of this
    class (or a subclass) to pass to the OdEdCommandStack::executeCommand function.
    Using this class instead of a true instance of OdEdCommandContext provides
    custom commands with database access.

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbCommandContext : public OdEdCommandContext
{ 
public:
  ODRX_DECLARE_MEMBERS(OdTvDbCommandContext);

  /** \details
      Returns a database, for use in a custom command.
  */
  virtual OdTvDbDatabase* database();

  OdTvDbUserIO* dbUserIO();
};



inline OdTvDbUserIO*
OdTvDbCommandContext::dbUserIO()
{
  ODA_ASSERT(userIO() && userIO()->isKindOf(OdTvDbUserIO::desc()));
  return static_cast<OdTvDbUserIO*>(userIO());
}

inline OdTvDbDatabase*
OdTvDbCommandContext::database()
{
  //ODA_ASSERT(baseDatabase()->isKindOf(OdTvDbDatabase::desc()));
  //return static_cast<OdTvDbDatabase*>(baseDatabase());
  //
  // support for ODADrawingsExplorer 
  OdTvDbDatabase* pDb = OdTvDbDatabase::cast(baseDatabase()).get();
  if (!pDb)
    throw OdError(eNoDatabase);
  return pDb;
}

#include "TD_PackPop.h"

#endif //#ifndef _ODDBCOMMANDCONTEXT_H_INCLUDED_
