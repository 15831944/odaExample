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

#ifndef _DAI_MODULE_H_
#define _DAI_MODULE_H_

#include "OdaCommon.h"
#include "DynamicLinker.h"

#include "daiHostModule.h"
#include "daiBuildOptions.h"
#include "daiHostAppServicesBase.h"

#include "daiValueTypes.h"
#include "daiSchema.h"
#include "daiSession.h"

/** \details
Unregisters a schema-dependent module.

\param schemaName [in] Name of EXPRESS schema to unregister.
*/
DAI_EXPORT void oddaiUnregisterSchema(const OdAnsiString &schemaName);

/** \details
Unregisters all schema-dependent modules.
*/
DAI_EXPORT void oddaiUnregisterSchemas();

/** \details
Returns a smart pointer to a schema definition by the name of the schema.
If the schema isn't supported (or isn't registered in schemas dictionary),
NULL will be returned.

\param schemaName [in] Name of EXPRESS schema to find.
\returns Smart pointer to a Schema class, if schema is supported, otherwise returns null SmartPtr.
*/
DAI_EXPORT OdDAI::SchemaPtr oddaiGetSchema(const OdAnsiString &schemaName);

/** \details
Initializes a schema from provided string which contains schema definition into EXPRESS format
(ISO 10303-11).
\param expContent [in] Source code for schema definition written in EXPRESS language.
\returns Smart pointer to a Schema class, if schema was initialized successfully, otherwise returns null SmartPtr.
*/
DAI_EXPORT OdDAI::SchemaPtr oddaiInitSchema(const char *expContent);

/** \details
Returns a smart pointer to currently opened session.
\remarks The function is thread-safe.
*/
DAI_EXPORT OdDAI::SessionPtr oddaiSession();

/** \details
Returns a smart pointer to a newly created session, if session wasn't created before.
\remarks The function is thread-safe.
*/
DAI_EXPORT OdDAI::SessionPtr oddaiCreateSession();

/** \details
Closes currently opened session.
\remarks The function is thread-safe.
*/
DAI_EXPORT bool oddaiCloseCurrentSession();

/** \details
Prints formatted string in console window.
*/
DAI_EXPORT void oddaiPrintConsoleString(const wchar_t* fmt, ...);

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

/** \details
A class that implements a DAI module for data access.
*/
class DAI_EXPORT OdSDAIModule : public OdDAIHostModule
{
public:

  /** \details
  Initialization of the SDAI module.
  */
  virtual void      initApp();

  /** \details
  Uninitialization of the SDAI module.
  */
  virtual void      uninitApp();

  /** \details
  Register .exprt module.
  \returns Returns eOk if .exprt module was successfully registered.
  */
  virtual OdResult registerSchemaModule(OdExpSchemaModule *expSchemaModule);

  /** \details
  Retrieves if CDA is allowed for OdDAI host module.
  \returns Returns true if CDA is enabled.
  \remarks Always returns false for OdSDAIModule implementation. 
  */
  virtual bool isCDAEnabled();

};

/** \details 
A data type that represents a smart pointer to an <link OdDAI::OdSDAIModule, OdSDAIModule> object.
*/
typedef OdSmartPtr<OdSDAIModule> OdSDAIModulePtr;

/** \details
Type definition for pointer on a function that should be used for time-intensive processes interruption.
*/
typedef bool (*InterruptCallback)();
}

#endif // _DAI_MODULE_H_
