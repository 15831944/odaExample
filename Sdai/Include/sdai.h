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

#ifndef _SDAI_
#define _SDAI_

#include "daiError/daiErrorId.h"

#ifdef __cplusplus
extern "C" {
#endif

 /** \details
 Represents an instance identifier.
 */
struct Sdai_instS {
  /** The identifier value.*/
  int pInst;
};

/** \details
  Represents an identifier of an aggregate instance.
 */
struct Sdai_aggrS {
  /** The identifier value.*/
  int pAggr;
};

/** \details
  A special pointer data type, that acts as a handle of an attribute or aggregate element that is an instance of an EXPRESS ENTITY type. 
 */
typedef struct Sdai_instS * SdaiId;

/** \details
  A data type of a pointer to an identifier of an aggregate element that is an instance of an EXPRESS ENTITY type. 
 */
typedef struct Sdai_Id_aggr * SdaiId_aggr;

/** \details
  A data type of a pointer to an SDAI iterator that provides sequential access to the members of an aggregate attribute or element.
  This data type is used within the C late binding access mechanism.
 */
typedef struct Sdai_ItrId * SdaiItrId;

/** \details
  A data type of a pointer to an SDAI attribute data block (ADB). 
  This data type is used within the C late binding access mechanism.
 */
typedef struct Sdai_ADBId * SdaiADBId;

/** \details
  A data type that contains an SDAI index identifier that is used to represent aggregation indices.
  This data type is used within the C late binding access mechanism.
 */
typedef unsigned SdaiIndexId;

/*** Constant declarations ******************************************/

/* LOGICAL and BOOLEAN value elements: */

#define sdaiFALSE 0
#define sdaiTRUE 1
#define sdaiUNKNOWN 2

/* BINARY value elements: */

#define sdaiBIT0 '0'
#define sdaiBIT1 '1'

/* EXPRESS built-in constants: */

#define sdaiE 2.7182818284590451353602874713
#define sdaiPI 3.1415926353897932384626433832


/*** Type declarations **********************************************/

/** \details
  A data type that represents an SDAI set of bits.
  <group IFC_SDAI_LATE_BIND_SIMPLE>
 */
typedef unsigned char SdaiBit;

/* C late binding simple data types: */

/** \details
  An SDAI data type that represents the EXPRESS INTEGER values.
  This data type is used within the C late binding access mechanism.
  <group IFC_SDAI_LATE_BIND_SIMPLE>
 */
typedef int SdaiInteger;

/** \details
  An SDAI data type that represents the EXPRESS REAL values.
  This data type is used within the C late binding access mechanism.
  <group IFC_SDAI_LATE_BIND_SIMPLE>
 */
typedef double SdaiReal;

/** \details
  An SDAI data type that represents the EXPRESS NUMBER values.
  This data type is used within the C late binding access mechanism.
  <group IFC_SDAI_LATE_BIND_SIMPLE>
 */
typedef SdaiReal SdaiNumber;

/** \details
  An SDAI data type that represents the EXPRESS BOOLEAN values.
  This data type is used within the C late binding access mechanism.
  <group IFC_SDAI_LATE_BIND_SIMPLE>
 */
typedef int SdaiBoolean;

/** \details
  An SDAI data type that represents the EXPRESS LOGICAL values.
  This data type is used within the C late binding access mechanism.
  <group IFC_SDAI_LATE_BIND_SIMPLE>
 */
typedef int SdaiLogical;

/** \details
  An SDAI data type that represents the EXPRESS STRING values.
  This data type is used within the C late binding access mechanism.
  <group IFC_SDAI_LATE_BIND_SIMPLE>
 */
typedef char *SdaiString;

/** \details
  An SDAI data type that represents the EXPRESS BINARY values.
  This data type is used within the C late binding access mechanism.
  <group IFC_SDAI_LATE_BIND_SIMPLE>
 */
typedef SdaiBit *SdaiBinary;

/** \details 
  An SDAI data type that represents an EXPRESS ENUM type.
  This data type is used within the C late binding access mechanism.
  <group IFC_SDAI_LATE_BIND_SIMPLE>
*/
typedef char *SdaiEnum;

/* aggregate data types: */

/** \details
  An SDAI data type that represents an aggregate instance.
  This data type is used within the C late binding access mechanism.
  <group IFC_SDAI_LATE_BIND_AGGR>
 */
typedef SdaiId_aggr       SdaiAggr;

/** \details
  An SDAI data type that represents an ordered collection aggregate instance.
  This data type is used within the C late binding access mechanism.
  <group IFC_SDAI_LATE_BIND_AGGR>
 */
typedef SdaiAggr          SdaiOrderedAggr;

/** \details
  An SDAI data type that represents an unordered collection aggregate instance.
  This data type is used within the C late binding access mechanism.
  <group IFC_SDAI_LATE_BIND_AGGR>
 */
typedef SdaiAggr          SdaiUnorderedAggr;

/** \details
  An SDAI data type that represents an array instance.
  This data type is used within the C late binding access mechanism.
  <group IFC_SDAI_LATE_BIND_AGGR>
 */
typedef SdaiOrderedAggr   SdaiArray;

/** \details
  An SDAI data type that represents a list instance.
  This data type is used within the C late binding access mechanism.
  <group IFC_SDAI_LATE_BIND_AGGR>
 */
typedef SdaiOrderedAggr   SdaiList;

/** \details
  An SDAI data type that represents a set instance.
  This data type is used within the C late binding access mechanism.
  <group IFC_SDAI_LATE_BIND_AGGR>
 */
typedef SdaiUnorderedAggr SdaiSet;

/** \details
  An SDAI data type that represents a bag instance.
  This data type is used within the C late binding access mechanism.
  <group IFC_SDAI_LATE_BIND_AGGR>
 */
typedef SdaiUnorderedAggr SdaiBag;

/** \details
  An SDAI data type that enumerates primitive data types.
  This data type is used within the C late binding access mechanism.
  <group IFC_SDAI_LATE_BIND_AGGR>
*/
typedef enum {
  /**Attribute Data Block data type.*/
  sdaiADB, 
  /**Aggregate data type.*/
  sdaiAGGR, 
  /**Binary data type.*/
  sdaiBINARY, 
  /**Boolean data type.*/
  sdaiBOOLEAN,
  /**Enumeration data type.*/
  sdaiENUM, 
  /**Instance data type.*/
  sdaiINSTANCE, 
  /**Integer data type.*/
  sdaiINTEGER, 
  /**Logical data type.*/
  sdaiLOGICAL, 
  /**No data type (unknown datatype).*/
  sdaiNOTYPE, 
  /**Number data type.*/
  sdaiNUMBER, 
  /**Real data type.*/
  sdaiREAL, 
  /**String data type.*/
  sdaiSTRING
}
SdaiPrimitiveType;

/* entity instance identifier type: */

/** \details
  An SDAI data type that represents an instance identifier data type.
  The handle serves as the identifier of the instance. Identifiers are not persistent. 
  Identifiers shall be unique globally over all types of instances and unchanging within 
  an SDAI session for any particular instance.
  <group IFC_SDAI_ID_TYPES>
*/
typedef SdaiId      SdaiInstance;

/* SDAI instance identifier types: */

/** \details
  An SDAI data type that represents an application instance identifier.
  <group IFC_SDAI_ID_TYPES>
*/
typedef SdaiInstance          SdaiAppInstance;

/** \details
  An SDAI data type that represents an SDAI model identifier.
  <group IFC_SDAI_ID_TYPES>
*/
typedef SdaiInstance          SdaiModel;

/** \details
  An SDAI data type that represents an SDAI repository identifier.
  <group IFC_SDAI_ID_TYPES>
*/
typedef SdaiInstance          SdaiRep;

/** \details
  An SDAI data type that represents an SDAI session identifier.
  <group IFC_SDAI_ID_TYPES>
*/
typedef SdaiInstance          SdaiSession;

/** \details
  An SDAI data type that represents an SDAI attribute identifier.
  <group IFC_SDAI_ID_TYPES>
*/
typedef SdaiInstance          SdaiAttr;

/** \details
  An SDAI data type that represents an SDAI explicit attribute identifier.
  <group IFC_SDAI_ID_TYPES>
*/
typedef SdaiAttr              SdaiExplicitAttr;

/** \details
  An SDAI data type that represents an SDAI named type identifier.
  <group IFC_SDAI_ID_TYPES>
*/
typedef SdaiInstance          SdaiNamedType;

/** \details
  An SDAI data type that represents an SDAI entity definition identifier.
  <group IFC_SDAI_ID_TYPES>
*/
typedef SdaiNamedType         SdaiEntity;

//DOM-IGNORE-BEGIN
/** \details
  
*/
//typedef SdaiNamedType         SdaiDefinedType;
//DOM-IGNORE-END

/** \details
  An SDAI data type that represents an SDAI where rule identifier.
  <group IFC_SDAI_ID_TYPES>
*/
typedef SdaiInstance          SdaiWhereRule;

/** \details
  An SDAI data type that represents an SDAI uniqueness rule identifier.
  <group IFC_SDAI_ID_TYPES>
*/
typedef SdaiInstance          SdaiUniRule;

/** \details
  An SDAI data type that represents an SDAI global rule identifier.
  <group IFC_SDAI_ID_TYPES>
*/
typedef SdaiInstance          SdaiGlobalRule;

/** \details
  An SDAI data type that represents an SDAI schema identifier.
  <group IFC_SDAI_ID_TYPES>
*/
typedef SdaiInstance          SdaiSchema;

/** \details
  An SDAI data type that represents an SDAI scope identifier.
  <group IFC_SDAI_ID_TYPES>
*/
typedef SdaiInstance          SdaiScope;

/** \details
  An SDAI data type that represents an identifier of the SDAI schema instance.
  <group IFC_SDAI_ID_TYPES>
*/
typedef SdaiInstance          SdaiSchemaInstance;

/** \details
  An SDAI data type that represents an SDAI transaction identifier.
  <group IFC_SDAI_ID_TYPES>
*/
typedef SdaiInstance          SdaiTrx;


/** \details
  An SDAI data type that represents an SDAI iterator identifier.
  <group IFC_SDAI_ID_TYPES>
*/
typedef SdaiItrId             SdaiIterator;

/* Non-persistent list data type: */


/** \details
  An SDAI data type that represents an identifier of a Non-Persistent List (NPL), an unbounded list of application instances.
  <group IFC_SDAI_ID_TYPES>
*/
typedef SdaiList              SdaiNPL;

/** \details
  A data type that enumerates the types of query sources. 
*/
typedef enum {
  /**An aggregate query type.*/
  sdaiQUERY_AGGR, 
  /**A model query type.*/
  sdaiQUERY_MODEL, 
  /**A repository query type.*/
  sdaiQUERY_REP,
  /**A schema instance query type.*/
  sdaiQUERY_SCHEMAINSTANCE
} SdaiQuerySourceType;

/** \details
  A data type that enumerates access modes.
*/
typedef enum { 
  /**Access mode is not specified.*/
  Access_type_unset, 
  /**Read-Only access mode.*/
  sdaiRO, 
  /**Read-Write access mode.*/
  sdaiRW 
} SdaiAccessMode;

/** \details
  An SDAI pointer data type that represents an identifier of an Attribute Data Block.
  This data type is used within the C late binding access mechanism.
*/
typedef SdaiADBId SdaiADB;

/** \details
  An SDAI data type that represents an identifier of an aggregate index.
  This data type is used within the C late binding access mechanism.
*/
typedef SdaiIndexId SdaiAggrIndex;

/** \details
  An SDAI data type that represents an error code.
  This data type is used within the C late binding access mechanism.
*/
typedef SdaiErrorId SdaiErrorCode;

/** \details
  An SDAI data type that represents an error handler - a function that processes an SDAI error.
  This data type is used within the C late binding access mechanism.
*/
typedef void(*SdaiErrorHandler)(SdaiErrorCode);

/* the ANSI-C style function prototypes of the SDAI operations */

#include "daiBuildOptions.h"

/* 6.1 Environment operations */

/** \details
  Initiates the SDAI functionality implementation and starts a new SDAI session.
  \returns The identifier of the new session instance if it was created successfully; otherwise, the function returns a NULL identifier.
  \remarks
  Possible error codes:
  * sdaiSS_OPN: The session is open.
  * sdaiSS_NAVL The SDAI is not available.
  * sdaiSY_ERR An underlying system error.
  <group IFC_SDAI_OPERATION_ENVIRONMENT>
*/
DAI_EXPORT SdaiSession sdaiOpenSession(void);

/** \details 
  The Logical Compare function that compares two values according to the ordering 
  of the values of the EXPRESS LOGICAL data type.
  \param value1 [in] The first value for comparision.
  \param value2 [in] The second value for comparision.
  \returns 
  If comparision operation was successful, the function returns one of the following values`: 
    * +1 if value1 is greater than value2; 
    * 0  if value1 is equal to value2; 
    * -1 if value1 is less than value2.
  <group IFC_SDAI_OPERATION_ENVIRONMENT>
*/
DAI_EXPORT int sdaiLogicalCompare(SdaiLogical value1, SdaiLogical value2);

/** \details
  The Error Query function that returns the error code of the most recently unsuccessfully called SDAI function.
  \returns The error code of the most recent function that executed unsuccessfully.
  \remarks
  After returning the error code, subsequent calls of the Error Query function returns 
  the  sdaiNO_ERR value until another SDAI function finishes with an error. 
  If no SDAI session is not started the function returns the sdaiSS_NOPN (no SDAI session is open) value.
  <group IFC_SDAI_OPERATION_ENVIRONMENT>
*/
DAI_EXPORT SdaiErrorCode sdaiErrorQuery(void);

/** \details
  The Set Error Handler function appends a specified error handling function to the stack of SDAI error handlers.
  Stack structure assumes that when an error occurs, the most recently appended function is called.
  If the called function can not handle the error, the control is passed to the next handler function in the stack.
  \param function [in] An error handler function.
  \remarks 
  This function accepts the error handler function and can be called before the Open Session function call, 
  during the SDAI session, and after the Close Session function fall.
  To use the system default error handler, pass the NULL handler pointer to the function.
  It is possible to set more than one error handling function: Just call Set Error Handler function as many times as you want with different error handling functions. These functions will be placed in the stack according to the sequence of Set Error Handler calls. 
  When an error occurs, the error handling function from the top of the stack runs.
  The  Set Error Handler function may cause the sdaiSY_ERR (underlying system error) error.
  <group IFC_SDAI_OPERATION_ENVIRONMENT>
*/
DAI_EXPORT void sdaiSetErrorHandler(SdaiErrorHandler function);

/** \details
  The Restore Error Handler function removes the most recently added error handling function from
  the top of the error handling stack.
  \returns The error handling function that were removed from the stack if it is not empty.
  \remarks  
  The next error handling function after the removed function that is left in the stack is used for error handling. 
  The Restore Error Handler function has no effect if the error handler stack is empty.
  <group IFC_SDAI_OPERATION_ENVIRONMENT>
*/
DAI_EXPORT SdaiErrorHandler sdaiRestoreErrorHandler(void);

/** \details
  The Is Equal function determines whether two specified SDAI instancies are identical or not.
  \param instance1 [in] The first instance in the comparison.
  \param instance2 [in] The second instance in the comparison.
  \returns The sdaiTRUE value if specified SDAI instancies are equal; otherwise, the function returns the sdaiFALSE value.
  <group IFC_SDAI_OPERATION_ENVIRONMENT>
*/
DAI_EXPORT SdaiBoolean sdaiIsEqual(SdaiInstance instance1, SdaiInstance instance2);


/* 6.2 Session operations */

/** \details
  Records event within a specified SDAI session.
  \param session      [in] A SDAI session.
  \param functionName [in] A string that contains the fucntion name.
  \param error        [in] An error code.
  \param description  [in] A string that contains the event record description.
  <group IFC_SDAI_OPERATION_SESSION>
*/
DAI_EXPORT void sdaiRecordEvent(SdaiSession session, SdaiString functionName, SdaiErrorCode error, SdaiString description);

/** \details
  Switches the event recording on or off for a specified SDAI session.
  \param session [in] A SDAI session.
  \param setRec  [in] A flag that determines whether the event recording is available (if equals to true) or not (if equals to false).
  \returns The sdaiTRUE value if the event recording mode was successfully modified; otherwise, the function returns false.
  <group IFC_SDAI_OPERATION_SESSION>
*/
DAI_EXPORT SdaiBoolean sdaiSetEventRecording(SdaiSession session, SdaiBoolean setRec);

/** \details
  Closes a specified session. 
  \param session [in] A pointer to the SDAI session to be closed.
  <group IFC_SDAI_OPERATION_SESSION>
*/
DAI_EXPORT void sdaiCloseSession(SdaiSession session);

/** \details
  Opens the specified repository. 
  \param session    [in] A session within which the repository should be opened.
  \param repository [in] A pointer to the repository that should be opened.
  \returns A handle of the opened repository object if the function was successfully finished; otherwise, the function returns the NULL value.
  <group IFC_SDAI_OPERATION_SESSION>
*/
DAI_EXPORT SdaiRep sdaiOpenRepository(SdaiSession session, SdaiRep repository);

/** \details
  Opens the specified repository. 
  \param session        [in] A session within which the repository should be opened.
  \param repositoryName [in] A string that contains the repository name.
  \returns A handle of the opened repository object if the function was successfully finished; otherwise, the function returns the NULL value.
  <group IFC_SDAI_OPERATION_SESSION>
*/
DAI_EXPORT SdaiRep sdaiOpenRepositoryBN(SdaiSession session, SdaiString repositoryName);

//DAI_EXPORT SdaiTrx sdaiStartTrx(SdaiSession session, SdaiAccessMode mode);
//DAI_EXPORT void sdaiBreakTrx(SdaiTrx transaction, SdaiCommitMode mode);
//DAI_EXPORT void sdaiEndTrx (SdaiTrx transaction, SdaiCommitMode mode);

/** \details
  Creates an instance of the Non-Persistent List (empty unbounded list of entity instances).
  \returns An identifier of the created Non-Persistent List object.
  <group IFC_SDAI_OPERATION_SESSION>
*/
DAI_EXPORT SdaiNPL sdaiCreateNPL(void);

/** \details
  Deletes an instance of the Non-Persistent List.
  \param list [in] An identifier of the Non-Persistent List to be deleted.
*/
DAI_EXPORT void sdaiDeleteNPL(SdaiNPL list);

//DAI_EXPORT SdaiInteger sdaiQuery(SdaiQuerySourceType sourceType, SdaiString criteria, SdaiInstance instance, SdaiNPL result, ...);

/** \details
  Retrieves the current recording flag value. 
  The recording flag determines whether the recording is on or off.
  \returns true if the recording is on; otherwise, the function returns false.
*/
DAI_EXPORT SdaiLogical sdaiIsRecordingOn (SdaiSession session);

/** \details
  Creates an Attribute Data Block (ADB) instance with a specified type and value presets.
  \param valueType [in] A type of the initial values.
  \returns An identifier of the created ADB if it was successfully created; otherwise, the function returns the NULL value.
*/
DAI_EXPORT SdaiADB sdaiCreateADB(SdaiPrimitiveType valueType, ...);

/** \details
  Creates an empty attribute data block (ADB) instance.
  \returns An identifier of the created ADB if it was successfully created; otherwise, the function returns the NULL value.
*/
DAI_EXPORT SdaiADB sdaiCreateEmptyADB(void);

/** \details
  Retrieves the value of a specified type from the attribute data block (ADB).
  \param block     [in] An ADB instance.
  \param valueType [in] A value type.
  \param value     [out] A raw pointer to the buffer to write the result.
  \returns A raw pointer to the value if the value was successfully retrieved; otherwise, the function returns the NULL value.
*/
DAI_EXPORT void* sdaiGetADBValue(SdaiADB block, SdaiPrimitiveType valueType, void *value);

/** \details
  Stores the value (or values) of a specified type to the attribute data block(ADB).
  \param block [in] An ADB instance.
  \param valueType [in] A value type.
*/
DAI_EXPORT void sdaiPutADBValue(SdaiADB block, SdaiPrimitiveType valueType, ...);

/** \details
  Retrieves the type of the value stored in the attributed data block (ADB).
  \param block [in] An identifier of the  ADB instance.
  \returns The type of data that the ADB instance contains.
*/
DAI_EXPORT SdaiPrimitiveType sdaiGetADBType(SdaiADB block);

/** \details
  Unsets the type and value of the specified attribute data block (ADB).
  \param block [in] An ADB instance.
*/
DAI_EXPORT void sdaiUnsetADB(SdaiADB block);

/** \details
  Deletes a specified Attribute Data Block (ADB) instance.
  \param block [in] An ADB instance to be deleted.
  \code
  <pre>
  SdaiADB block = sdaiCreateEmptyADB(); 
  ... 
  sdaiDeleteADB(block);
  </pre>
*/
DAI_EXPORT void sdaiDeleteADB(SdaiADB block);

/* 6.3 Repository operations */

/** \details
  Creates a new SDAI model instance.
  \param repository [in] A SDAI repository that contains the model.
  \param modelName  [in] A string that contains the model name.
  \param schemaName [in] A string that contains the schema name.
  \returns An identifier of the created model.
*/
DAI_EXPORT SdaiModel sdaiCreateModel(SdaiRep repository, SdaiString modelName, SdaiSchema schema);

/** \details
  Creates a new SDAI model instance.
  \param repository [in] A SDAI repository that contains the model.
  \param modelName  [in] A string that contains the model name.
  \param schemaName [in] A string that contains the schema name.
  \returns An identifier of the created model.
*/
DAI_EXPORT SdaiModel sdaiCreateModelBN(SdaiRep repository, SdaiString modelName, SdaiString schemaName);

/** \details
  Creates a new SDAI schema instance. 
  \param schemaInstanceName [in] A string that contains the schema instance name.
  \param schemaName         [in] A string that contains the schema name.
  \param repository         [in] A SDAI repository to associate the created schema with.
  \returns An identifier of the created schema instance.
*/
DAI_EXPORT SdaiSchemaInstance sdaiCreateSchemaInstance(SdaiString schemaInstanceName, SdaiSchema schema, SdaiRep repository);

/** \details
  Creates a new SDAI schema instance. 
  \param schemaInstanceName [in] A string that contains the schema instance name.
  \param schemaName         [in] A string that contains the schema name.
  \param repository         [in] A SDAI repository to associate the created schema with.
  \returns An identifier of the created schema instance.
*/
DAI_EXPORT SdaiSchemaInstance sdaiCreateSchemaInstanceBN(SdaiString schemaInstanceName, SdaiString schemaName, SdaiRep repository);

/** \details
Closes a specified repository. 
\param repository [in] A pointer to a repository to be closed.
*/
DAI_EXPORT void sdaiCloseRepository(SdaiRep repository);


/* 6.4 Schema instance operations */

/** \details
  Deletes a specified schema instance. 
  \param schemaInstance [in] A schema instance to be deleted.
*/
DAI_EXPORT void sdaiDeleteSchemaInstance(SdaiSchemaInstance schemaInstance);

/** \details
  Deletes a specified schema instance. 
  \param schemaInstanceName [in] A string that contains the schema instance name.
  \param repository         [in] A repository where the function searches the schema instance by the specified name.
*/
DAI_EXPORT void sdaiDeleteSchemaInstanceBN(SdaiString schemaInstanceName, SdaiRep repository);

/** \details
  Renames a specified schema instance.
  \param schemaInst [in] A schema instance to be renamed.
  \param schemaInstName [in] A new name of the schema instance.
*/
DAI_EXPORT void sdaiRenameSchemaInstance(SdaiSchemaInstance schemaInst, SdaiString schemaInstName);

/** \details
  Renames a specified schema instance.
  \param schemaInstOldName [in] A string that contains the old name of the schema instance to be renamed.
  \param repository        [in] A repository where the function searches the schema instance by the specified name.
  \param schemaInstName    [in] A new name of the schema instance.
*/
DAI_EXPORT void sdaiRenameSchemaInstanceBN(SdaiString schemaInstOldName, SdaiRep repository, SdaiString schemaInstName);

/** \details
  Adds a model to a specified schema instance.
  \param schemaInstance [in] A schema instance.
  \param model          [in] A model to be added.
*/
DAI_EXPORT void sdaiAddModel(SdaiSchemaInstance schemaInstance, SdaiModel model);

/** \details
  Adds a model to a specified schema instance.
  \param schemaInstance [in] A schema instance.
  \param repository     [in] A repository where the model should be found by its name.
  \param modelName      [in] A string that contains the name of the model to be added.
*/
DAI_EXPORT void sdaiAddModelBN(SdaiSchemaInstance schemaInstance, SdaiRep repository, SdaiString modelName);

/** \details
  Removes a specified model from a schema instance.
  \param schemaInstance [in] A schema instance.
  \param model          [in] A model to be removed.
*/
DAI_EXPORT void sdaiRemoveModel(SdaiSchemaInstance schemaInstance, SdaiModel model);

/** \details
  Removes a specified model from a schema instance.
  \param schemaInstance [in] A schema instance.
  \param repository     [in] A repository where the model should be found by its name.
  \param modelName      [in] A string that contains the name of the model to be removed.
*/
DAI_EXPORT void sdaiRemoveModelBN(SdaiSchemaInstance schemaInstance, SdaiRep repository, SdaiString modelName);

//DAI_EXPORT SdaiLogical sdaiValidateGlobalRule(SdaiSchemaInstance schemaInstance, SdaiGlobalRule rule, SdaiNPL list);
//DAI_EXPORT SdaiLogical sdaiValidateGlobalRuleBN(SdaiSchemaInstance schemaInstance, SdaiString ruleName, SdaiNPL list);
//DAI_EXPORT SdaiLogical sdaiValidateUniqueness(SdaiSchemaInstance schemaInstance, SdaiUniRule uniRule, SdaiNPL list);
//DAI_EXPORT SdaiLogical sdaiValidateUniquenessBN(SdaiSchemaInstance schemaInstance, SdaiString entityName, SdaiString uniRuleName, SdaiNPL list);
//DAI_EXPORT SdaiLogical sdaiValidateReferenceDomain(SdaiSchemaInstance schemaInstance, SdaiAppInstance appInstance, SdaiNPL list);
//DAI_EXPORT SdaiLogical sdaiValidateSchemaInstance(SdaiSchemaInstance schemaInstance);
//DAI_EXPORT SdaiBoolean sdaiIsValidationCurrent(SdaiSchemaInstance schemaInstance);
//DAI_EXPORT SdaiBoolean sdaiIsValidationCurrent(SdaiSchemaInstance schemaInstance);

/** \details
  Retrieves a schema with a specified name.
  \param schemaName [in] A string that contains the schema name.
  \returns The schema with the specified name.
  
   \code
   SdaiSchema ifc2x3schema = sdaiGetSchema("IFC2X3");
   
   \remarks
   The function is case insensitive.
*/
DAI_EXPORT SdaiSchema sdaiGetSchema(SdaiString schemaName);

/** \details
  Retrieves a schema instance with a specified name from a specified repository.
  \param schemaInstanceName [in] A string that contains the schema instance name.
  \param repository         [in] A repository where the function searches for the schema instance by its name.
  \returns The schema instance with the specified name.
*/
DAI_EXPORT SdaiSchemaInstance sdaiGetSchemaInstance(SdaiString schemaInstanceName, SdaiRep repository);


/* 6.5 SDAI-model operations */

/** \details
  Deletes a specified model.
  \param model [in] A model to be deleted.
*/
DAI_EXPORT void sdaiDeleteModel(SdaiModel model);

/** \details
  Deletes a specified model.
  \param repository [in] A repository where the function searches for the model by its name.
  \param modelName [in] A string that contains the name of the model to be deleted.
*/
DAI_EXPORT void sdaiDeleteModelBN(SdaiRep repository, SdaiString modelName);

/** \details
  Renames the model.
  \param model     [in] A model to be renamed.
  \param modelName [in] A string that contains the new model name.
*/
DAI_EXPORT void sdaiRenameModel(SdaiModel model, SdaiString modelName);

/** \details
  Renames the model.
  \param repository   [in] A repository where the function searches for the model by its name.
  \param modelOldName [in] A string that contains the old model name. This name is used to find the model to be renamed.
  \param modelName    [in] A string that contains the new model name.
*/
DAI_EXPORT void sdaiRenameModelBN(SdaiRep repository, SdaiString modelOldName, SdaiString modelName);

/** \details
  Opens a specified model in a specified mode.
  \param model  [in] A model to be open.
  \param mode   [in] An access mode.
  \returns A pointer to the open model if the function successfully opened the model; otherwise, the function returns the NULL value.
*/
DAI_EXPORT SdaiModel sdaiAccessModel(SdaiModel model, SdaiAccessMode mode);

/** \details
  Opens a specified model in a specified mode. The model is specified by its repository and name. 
  \param repository [in] A repository that owns the model. The function searches the model in this repository by the name.
  \param modelName  [in] A model name.
  \param mode       [in] An open mode. 
  \returns A pointer to the open model if the function successfully opens the model; otherwise, the function returns the NULL value.
*/
DAI_EXPORT SdaiModel sdaiAccessModelBN(SdaiRep repository, SdaiString modelName, SdaiAccessMode mode);

/** \details
  Promotes access in the read-write mode for a specified model.
  \param model [in] A model to be promoted.
*/
DAI_EXPORT void sdaiPromoteModel(SdaiModel model);

/** \details
  Ends the access to the model. 
  \param model [in] A model to finish the access to.
*/
DAI_EXPORT void sdaiEndModelAccess(SdaiModel model);

/** \details
  Returns an entity specified by its name.
  \param model [in] A model that contains the entity definition.
  \param name  [in] A string that contains the entity name.
  \returns An entity with specified name.
  \code
  <pre>
  SdaiModel model = ...; 
  SdaiEntity entCartesianPoint = sdaiGetEntity(model, "ifccartesianpoint");
  </pre>
  \remarks
  The function is case insensitive.
*/
DAI_EXPORT SdaiEntity sdaiGetEntity(SdaiModel model, SdaiString name);

/** \details
  Creates an application instance within an associated model.
  \param model [in] A model.
  \param entity [in] An entity to be created.
  \returns A created application instance represented with its pointer if it was created successfully; otherwise, the function returns a NULL pointer.  
  \code
  SdaiModel model = ...;
  SdaiEntity entCartesianPoint = sdaiGetEntity(model, "IfcCartesianPoint");
  SdaiAppInstance cartesianPoint = sdaiCreateInstance(model, entCartesianPoint);
  \remarks
  The model should be accessed with the sdaiRW mode.
*/
DAI_EXPORT SdaiAppInstance sdaiCreateInstance(SdaiModel model, SdaiEntity entity);

/** \details
  Creates an application instance within an associated model.
  \param model [in] A model.
  \param entity [in] A name of the entity to be created.
  \returns A created application instance represented with its pointer if it was created successfully; otherwise, the function returns a NULL pointer.  
  \code
  <pre>
  SdaiModel model = ...; 
  SdaiAppInstance cartesianPoint = sdaiCreateInstanceBN(model, "IfcCartesianPoint");
  </pre>
  \remarks
  The function is case insensitive.
  The model should be accessed with the sdaiRW mode.
*/
DAI_EXPORT SdaiAppInstance sdaiCreateInstanceBN(SdaiModel model, SdaiString entityName);

/** \details
  Reverts changes made within a specified model.
  \param model [in] A model to revert changes.
  \remarks 
  This function is not implemented yet.
*/
DAI_EXPORT void sdaiUndoChanges(SdaiModel model);

/** \details
  Saves changes made within a specified model.
  \param model [in] A model to save changes.
*/
DAI_EXPORT void sdaiSaveChanges(SdaiModel model);

/** \details
  Creates a complex instance with specified name within a model.
  \param model      [in] A model to create the complex instance within.
  \param entityList [in] A list of entites included in the complex entity.
  \returns A created complex application instance.
*/
DAI_EXPORT SdaiAppInstance sdaiCreateComplexInstance(SdaiModel model, SdaiNPL entityList);

/** \details
  Creates a complex instance with the specified name.
  \param model      [in] A model to create the complex instance within.
  \param nameNumber [in] A number of instances included in the complex instance.
  \param nameVector [in] A raw pointer to the array of names of instances included in the complex instance.
  \returns A created complex application instance.
*/
DAI_EXPORT SdaiAppInstance sdaiCreateComplexInstanceBN(SdaiModel model, SdaiInteger nameNumber, SdaiString *nameVector);

/** \details
  Retrieves a collection of entity instances that are subtypes of entity type described by entity definition.
  \param model  [in] The model to get entities collection from.
  \param entity [in] The entity definition to find entity instances.
  \returns A set of entity instances of the type which is derived from the entity.
  \code
  <pre>
  SdaiEntity entPropertySingleValue = sdaiGetEntity(model, "IfcPropertySingleValue"); 
  SdaiSet propertySingleValues = sdaiGetEntityExtent(model, entPropertySingleValue); 
  SdaiInteger cnt = sdaiGetMemberCount(propertySingleValues);
  </pre>
*/
DAI_EXPORT SdaiSet sdaiGetEntityExtent(SdaiModel model, SdaiEntity entity);


/** \details
  Retrieves a collection of entity instances that are subtypes of the entity type.
  \param model [in] The model to get entities collection from.
  \param entity [in] The entity definition to find entity instances.
  \returns A set of entity instances of the type which is derived from the entity.
  \code
  <pre>
  SdaiSet indexedPolycurves = sdaiGetEntityExtentBN(model, "ifcindexedpolycurve"); 
  SdaiInteger cnt = sdaiGetMemberCount(indexedPolycurves);
  </pre>
  \remarks
  The function is case insensitive.
*/
DAI_EXPORT SdaiSet sdaiGetEntityExtentBN(SdaiModel model, SdaiString name);


/* 6.6 Scope operations */


/* 6.7 Type operations */


/** \details
  Complex instance will be created within parent schema if such combination doesn't exist.
  \param entityList   [in] List of members of complex entities.
  \returns valid SdaiEntity if succeded, otherwise return nullptr.
*/
DAI_EXPORT SdaiEntity sdaiGetComplexEntity(SdaiNPL entityList);

/** \details
  Complex instance will be created within parent schema if such combination doesn't exist.
  \param schemaName   [in] name of the schema.
  \param nameNumber   [in] count of names.
  \param nameVector   [in] names array of members of complex entities.
  \returns a valid SdaiEntity if succeded, otherwise return nullptr.
*/
DAI_EXPORT SdaiEntity sdaiGetComplexEntityBN(SdaiString schemaName, SdaiInteger nameNumber, SdaiString *nameVector);

/** \details
  Determines whether an entity definition is a subtype of another entity definition.
  \param subtype   [in] A subtype to check.
  \param supertype [in] A supertype to check.
  \returns sdaiTRUE if the specified entity has a type that is a subtype of the specified supertype; otherwise, the function returns sdaiFALSE.
*/
DAI_EXPORT SdaiBoolean sdaiIsSubtypeOf(SdaiEntity subtype, SdaiEntity supertype);

/** \details
  Determines whether an entity definition is a subtype of another entity definition.
  \param schemaName [in] A string that contains the schema name.
  \param subName    [in] A string that contains the name of the subtype to check.
  \param superName  [in] A string that contains the name of the supertype.
  \returns sdaiTRUE if the specified entity has a type that is a subtype of the specified supertype; otherwise, the function returns sdaiFALSE.
*/
DAI_EXPORT SdaiBoolean sdaiIsSubtypeOfBN(SdaiString schemaName, SdaiString subName, SdaiString superName);

/** \details
  Determines whether a specified SDAI data type is a subtype of another SDAI data type (supertype).
  \param subtype   [in] An entity that represents the SDAI data type to be checked.
  \param supertype [in] An entity that represents the SDAI supertype.
  \returns sdaiTRUE if the specified SDAI data type is a subtype of the specified supertype; otherwise, the function returns sdaiFALSE.
*/
DAI_EXPORT SdaiBoolean sdaiIsSDAISubtypeOf(SdaiEntity subtype, SdaiEntity supertype);

/** \details
  Determines whether a specified SDAI data type is a subtype of another SDAI data type (supertype).
  \param schemaName [in] A string that contains the name of the schema.
  \param subName    [in] A string that contains the name of the SDAI data type to be checked.
  \param superName  [in] A string that contains the name of the supertype.
  \returns sdaiTRUE if the specified SDAI data type is a subtype of the specified supertype; otherwise, the function returns sdaiFALSE.
*/
DAI_EXPORT SdaiBoolean sdaiIsSDAISubtypeOfBN(SdaiString schemaName, SdaiString subName, SdaiString superName);

/** \details
  Retrieves the definition of a specified attribute.
  \param entity   [in] An entity that contains the attribute.
  \param attrName [in] A string that contains the attribute name.
  \returns The required attribute with the specified name.
*/
DAI_EXPORT SdaiAttr sdaiGetAttrDefinition(SdaiEntity entity, SdaiString attrName);

/** \details
  Retrieves the definition of a specified attribute.
  \param schemaName [in] A string that contains the name of the schema.
  \param entityName [in] A string that contains the entity name.
  \param attrName   [in] A string that contains the attribute name.
  \returns The required attribute with the specified name.
*/
DAI_EXPORT SdaiAttr sdaiGetAttrDefinitionBN(SdaiString schemaName, SdaiString entityName, SdaiString attrName);

/* 6.8 Entity instance operations */

/** \details 
  Retrieves the value of an attribute from an entity instance.
  \param instance  [in] An instance of the entity that contains the required attribute.
  \param attribute [in] An attribute instance from the SDAI dictionary.
  \param valueType [in] A type of the attribute value.
  \param value     [out] A placeholder for the attribute value.
  \returns A raw pointer to the value if the instance has the specified attribute; otherwise, the function returns the NULL pointer.
*/
DAI_EXPORT void* sdaiGetAttr(SdaiInstance instance, SdaiAttr attribute, SdaiPrimitiveType valueType, void *value);

/** \details
  Retrieves the value of an attribute from an entity instance.
  \param instance      [in] An instance of the entity that contains the required attribute.
  \param attributeName [in] A string that contains the attribute name.
  \param valueType     [in] A type of the attribute value.
  \param value         [out] A placeholder for the attribute value.
  \returns A raw pointer to the value if the instance has the specified attribute; otherwise, the function returns the NULL pointer.
*/
DAI_EXPORT void* sdaiGetAttrBN(SdaiInstance instance, SdaiString attributeName, SdaiPrimitiveType valueType, void *value);

/** \details
  Determines whether the value of a specified attribute is unset.
  \param instance  [in] An instance of the entity whose attribute is being tested.
  \param attribute [in] An SdaiAttr instance from the SDAI dictionary.
  \returns sdaiTRUE if the attribute has a value or sdaiFALSE if the attribute value is not set.
*/
DAI_EXPORT SdaiBoolean sdaiTestAttr(SdaiInstance instance, SdaiAttr attribute);

/** \details
  Determines if the value of attribute is unset.
  \param instance      [in] An instance of the entity that contains the attribute to be checked.
  \param attributeName [in] A string that contains the name of the attribute.
  \returns sdaiTRUE if the attribute's value is set; otherwise the function returns sdaiFALSE.
*/
DAI_EXPORT SdaiBoolean sdaiTestAttrBN(SdaiInstance instance, SdaiString attributeName);

/** \details
  Retrieves the identifier of the SDAI model that contains the entity instance.
  \param instance [in] An entity instance.
  \returns Returns a model instance that contains the entity instance.
*/
DAI_EXPORT SdaiModel sdaiGetInstanceModel(SdaiInstance instance);

/** \details
  Retrieves the SDAI type of a specified entity instance.
  \param instance [in] An entity instance.
  \returns Returns the entity instance that represents the SDAI type of the specified entity instance.
*/
DAI_EXPORT SdaiEntity sdaiGetInstanceType(SdaiInstance instance);

/** \details
  Determines whether an application instance is an instance of a specified type.
  \param instance [in] An application instance to be checked.
  \param entity   [in] An entity that represents the type. 
  \returns sdaiTRUE if the application instance is an instance of the specified type; otherwise, the function returns sdaiFALSE.
*/
DAI_EXPORT SdaiBoolean sdaiIsInstanceOf(SdaiInstance instance, SdaiEntity entity);

/** \details
  Determines whether a specified application instance belongs to a specified type.
  \param instance   [in] An application instance to be checked.
  \param entityName [in] A string that contains the name of the entity type.
  \returns sdaiTRUE if the application instance belongs to the specified type; otherwise, the function returns false.
*/
DAI_EXPORT SdaiBoolean sdaiIsInstanceOfBN(SdaiInstance instance, SdaiString entityName);

/** \details
  Determines whether a specified application instance is a kind of a specified type.
  \param instance [in] An application instance to be checked.
  \param entity   [in] An entity that represents the type.
  \returns sdaiTRUE if the application instance belongs to the specified type; otherwise, the function returns false.
*/
DAI_EXPORT SdaiBoolean sdaiIsKindOf(SdaiInstance instance, SdaiEntity entity);

/** \details
  Determines whether a specified application instance is a kind of a specified type.
  \param instance   [in] An application instance to be checked.
  \param entityName [in] A string that contains the name the type.
  \returns sdaiTRUE if the application instance is a kind of the specified type; otherwise, the function returns false.
*/
DAI_EXPORT SdaiBoolean sdaiIsKindOfBN(SdaiInstance instance, SdaiString entityName);

/** \details
  Determines whether a specified SDAI data type is a kind of a specified type.
  \param instance [in] An application instance that represents the SDAI data type to be checked.
  \param entity   [in] An entity that represents the type.
  \returns sdaiTRUE if the specified SDAI data type is a kind of the specified type; otherwise, the function returns false.
  \remarks 
  This function is not implemented yet. 
*/
DAI_EXPORT SdaiBoolean sdaiIsSDAIKindOf(SdaiInstance instance, SdaiEntity entity);

/** \details
  Determines whether a specified SDAI data type is a kind of a specified type.
  \param instance   [in] An application instance that represents the SDAI data type to be checked.
  \param entityName [in] A string that contains the type name.
  \returns sdaiTRUE if the specified SDAI data type is a kind of the specified type; otherwise, the function returns false.
  \remarks 
  This function is not implemented yet. 
*/
DAI_EXPORT SdaiBoolean sdaiIsSDAIKindOfBN(SdaiInstance instance, SdaiString entityName);



/* 6.8.13 Entity instance operations for convenience */

/** \details
  Retrieves attribute values from a specified application instance.
  \param instance   [in] An application instance.
  \param numberAttr [in] A number of required attributes.
  \param attribute  [in] An attribute to be required.
  \param valueType  [in] An attribute value type.
  \param value      [out] A placeholder for attribute values.
*/
DAI_EXPORT void sdaiGetAttrs(SdaiInstance instance, SdaiInteger numberAttr, SdaiAttr attribute, SdaiPrimitiveType valueType, void *value, ...);

/** \details
  Retrieves attribute values from a specified application instance.
  \param instance       [in] An application instance.
  \param numberAttr     [in] A number of required attributes.
  \param attributeName  [in] A string that contains the name of the required attribute.
  \param valueType      [in] An attribute value type.
  \param value          [out] A placeholder for attribute values.
*/
DAI_EXPORT void sdaiGetAttrsBN(SdaiInstance instance, SdaiInteger numberAttr, SdaiString attributeName, SdaiPrimitiveType valueType, void *value, ...);

/** \details
  Retrieves all attribute values from a specified application instance.
  \param instance   [in] An application instance.
  \param numberAttr [in] A placeholder for the number of required attributes.
  \returns A raw pointer to the handle of the attribute data block that contains all attributes for the specified application instance.
  \remarks 
  This function is not implemented yet. 
*/
DAI_EXPORT SdaiADB *sdaiGetAllAttrs(SdaiInstance instance, SdaiInteger *numberAttr);

/* 6.9 Application instance operations */

/** \details
  Creates a copy of a specified application instance (origin). 
  The created copy contains the same attributes and is associated with the same model object as the origin one.
  \param instance [in] An origin application instance.
  \returns A copied application instance.
*/
DAI_EXPORT SdaiAppInstance sdaiNearCopyInstance(SdaiAppInstance instance);

/** \details
  Creates a copy of a specified application instance (origin) within a specified model. 
  The created copy contains the same attributes as the origin one.
  \param instance [in] An origin application instance.
  \param model [in] A model to associate the copy with.
  \returns A copied application instance.
  \remarks 
  This function is not implemented yet. 
*/
DAI_EXPORT SdaiAppInstance sdaiFarCopyInstance(SdaiAppInstance instance, SdaiModel model);

/** \details
  Deletes a specified instance.
  \param instance [in] An instance to be deleted.
*/
DAI_EXPORT void sdaiDeleteInstance(SdaiAppInstance instance);

/** \details
  Set a new value of the application instance attribute.
  \param instance  [in] An instance that contains the attribute. 
  \param attribute [in] An attribute to set the value.
  \param valueType [in] A value data type.
*/
DAI_EXPORT void sdaiPutAttr(SdaiAppInstance instance, SdaiExplicitAttr attribute, SdaiPrimitiveType valueType, ...);

/** \details
  Set a new value of the application instance attribute.
  \param instance      [in] An instance that contains the attribute. 
  \param attributeName [in] A string that contains the name of the attribute.
  \param valueType     [in] A value data type.
*/
DAI_EXPORT void sdaiPutAttrBN(SdaiAppInstance instance, SdaiString attributeName, SdaiPrimitiveType valueType, ...);

/** \details
  Restores a specified attribute in a specified application instance to the unset state. 
  \param instance  [in] An application instance to unset an attribute within.
  \param attribute [in] An attribute definition from the data dictionary.
*/
DAI_EXPORT void sdaiUnsetAttr(SdaiAppInstance instance, SdaiExplicitAttr attribute);

/** \details
  Restores a specified attribute in a specified application instance to the unset state. 
  \param instance      [in] An application instance to unset an attribute within.
  \param attributeName [in] A string that contains the name of the attribute to unset.
*/
DAI_EXPORT void sdaiUnsetAttrBN(SdaiAppInstance instance, SdaiString attributeName);

/** \details
  Creates an aggregate in a specified application instance attribute.
  \param instance  [in] An instance that contains the attribute.
  \param attribute [in] An attribute where the aggregate should be added.
  \returns The created SDAI aggregate value.
*/
DAI_EXPORT SdaiAggr sdaiCreateAggr(SdaiAppInstance instance, SdaiExplicitAttr attribute);

/** \details
  Creates an aggregate in a specified application instance attribute.
  \param instance      [in] An instance that contains the attribute.
  \param attributeName [in] A string that contains the name of the attribute where the aggregate should be added.
  \returns The created SDAI aggregate value.
*/
DAI_EXPORT SdaiAggr sdaiCreateAggrBN(SdaiAppInstance instance, SdaiString attributeName);

/** \details
  Creates an aggregate stored in an attribute data block (ADB) in a specified application instance attribute.
  \param instance        [in] An instance that contains the attribute.
  \param attribute       [in] An attribute where the aggregate should be added.
  \param selaggrInstance [in] An attribute data block (ADB) aggregate instance.
  \returns The created SDAI aggregate value.
*/
DAI_EXPORT SdaiAggr sdaiCreateAggrADB(SdaiAppInstance instance, SdaiExplicitAttr attribute, SdaiADB selaggrInstance);

/** \details
  Creates an aggregate stored in an attribute data block (ADB) in a specified application instance attribute.
  \param instance        [in] An instance that contains the attribute.
  \param attributeName   [in] A string that contains the name of the attribute where the aggregate should be added.
  \param selaggrInstance [in] An attribute data block (ADB) aggregate instance.
  \returns The created SDAI aggregate value.
*/
DAI_EXPORT SdaiAggr sdaiCreateAggrADBBN(SdaiAppInstance instance, SdaiString attributeName, SdaiADB selaggrInstance);

/** \details
Validates whether mandatory inverse attributes of the specified instance are set. 
Retrieves the non-persistent list of unset attributes, if found.
\returns sdaiTRUE if unset attributes are not found; otherwise, the function returns sdaiFALSE.
*/
DAI_EXPORT SdaiBoolean sdaiValidateRequiredAttrs(SdaiAppInstance instance, SdaiNPL list);

/** \details
Validates whether all inverse attribute constraints defined in the specified application instance are satisfied.
Retrieves the non-persistent list (NPL) of attributes that do not conform to validation, if found.
\param instance [in]  An identifier of the application instance to be validated.
\param list     [out] An identifier of a pre-existing NPL that stores the list of identifiers of invalid inverse attributes.
\returns sdaiTRUE if inverse attributes with violated size constraints are not found; otherwise, the function returns sdaiFALSE.
*/
DAI_EXPORT SdaiBoolean sdaiValidateInverseAttrs(SdaiAppInstance instance, SdaiNPL list);

/** \details
Validates whether the aggregate size constraints defined in the data dictionary for the specified application instance are satisfied.
Retrieves the non-persistent list of attributes with unsatisfied size constraints, if found.
\param instance [in]  Identifier of the application instance to be validated.
\param list     [out] The identifier of a pre-existing NPL to which the SdaiAttr identifiers of
those attributes are appended that do not conform to the validation.
\returns 
* sdaiTRUE if attributes with unsatisfied size constraints are not found. 
* sdaiFALSE if such attributes are found. 
* sdaiUNKNOWN if an error is encountered. 
*/
DAI_EXPORT SdaiLogical sdaiValidateAggrSizes(SdaiAppInstance instance, SdaiNPL list);

/** \details
Validates whether all STRING-valued attributes of the specified application instance are of a valid width.
Retrieves the non-persistent list of attributes with invalid width, if found.
\param appInstance [in]  Identifier of the application instance to be validated.
\param list        [out] An identifier of a pre-existing NPL to which the SdaiAttr identifiers of
those attributes are appended that do not conform to the validation.
\returns 
* sdaiTRUE if attributes with invalid width are not found. 
* sdaiFALSE if such attributes are found. 
* sdaiUNKNOWN if an error is encountered.
*/
DAI_EXPORT SdaiLogical sdaiValidateStringWidth(SdaiAppInstance appInstance, SdaiNPL list);

/** \details
Determines whether the specified where rule is satisfied by the specified application instance.
\param instance [in] Identifier of the application instance to be validated.
\param rule     [in] Where rule to check.
\returns sdaiTRUE if where rule is satisfied by application instance; the function returns sdaiFALSE if rule is not satisfied,
or sdaiUNKNOWN if where rule can not be evaluated.
*/
DAI_EXPORT SdaiLogical sdaiValidateWhereRule(SdaiAppInstance instance, SdaiWhereRule rule);

/** \details
Determines whether the where rule with specified name is satisfied by the specified application instance.
\param instance [in] Identifier of the application instance to be validated.
\param ruleName [in] Name of where rule to check.
\returns sdaiTRUE if where rule is satisfied by application instance; the function returns sdaiFALSE if rule is not satisfied,
or sdaiUNKNOWN if where rule can not be evaluated.
*/
DAI_EXPORT SdaiLogical sdaiValidateWhereRuleBN(SdaiAppInstance instance, SdaiString ruleName);

/** \details
  Sets new values to specified application instance attributes.
  \param appInstance [in] An application instance that contains the attributes.
  \param numberAttr  [in] A number of attributes to set their values.
  \param attribute   [in] An attribute to be set.
  \param valueType   [in] An attribute value type.
*/
DAI_EXPORT void sdaiPutAttrs(SdaiAppInstance appInstance, SdaiInteger numberAttr, SdaiExplicitAttr attribute, SdaiPrimitiveType valueType, ...);

/** \details
  Sets new values to specified application instance attributes.
  \param appInstance   [in] An application instance that contains the attributes.
  \param numberAttr    [in] A number of attributes to set their values.
  \param attributeName [in] A string that contains the attribute name.
  \param valueType     [in] An attribute value type.
  \code
  <pre>
  SdaiModel model = ...; 
  SdaiAppInstance startPoint = sdaiCreateInstanceBN(model, "IfcCartesianPoint"); 
  SdaiAppInstance lineSegment2D = sdaiCreateInstanceBN(model, "IfcLineSegment2D"); 
  sdaiPutAttrsBN(lineSegment2D, 3, 
    "StartPoint", sdaiINSTANCE, startPoint, 
    "StartDirection", sdaiREAL, startDirection, 
    "SegmentLength", sdaiREAL, segmentLength); 
  </pre>
  \remarks
  The function is case insensitive.
*/
DAI_EXPORT void sdaiPutAttrsBN(SdaiAppInstance appInstance, SdaiInteger numberAttr, SdaiString attributeName, SdaiPrimitiveType valueType, ...);

/* 6.10 Entity instance aggregate operations */

/** \details
  Retrieves the number of elements contained in a specified aggregate.
  \param aggregate [in] An aggregate to get the number of elements.
  \returns An SDAI integer value that contains the number of the aggregate elements.
*/
DAI_EXPORT SdaiInteger sdaiGetMemberCount(SdaiAggr aggregate);

/** \details
  Determines whether a specified aggregate contains a specified element.
  \param aggregate [in] An aggregate to check.
  \param valueType [in] A type of element.
  \returns sdaiTRUE if the aggregate contains specified elements; otherwise, the function returns sdaiFALSE.
  \remarks 
  You can check more than one element value through passing them to the function starting from the third parameter.
*/
DAI_EXPORT SdaiBoolean sdaiIsMember(SdaiAggr aggregate, SdaiPrimitiveType valueType, ...);

/** \details
  Creates an iterator for traversing through the aggregate elements.
  \param aggregate [in] An aggregate for traversing.
  \returns An iterator object.
  \remarks The iterator object created by the function should be deleted by the user when he does not need it anymore.
*/
DAI_EXPORT SdaiIterator sdaiCreateIterator(SdaiAggr aggregate);

/** \details
  Deletes a specified iterator.
  \param iterator [in] An iterator to delete.
*/
DAI_EXPORT void sdaiDeleteIterator(SdaiIterator iterator);

/** \details
  Sets the position of a specified iterator to the first element of the aggregate instance.
  \param iterator [in] An iterator to set the position.
*/
DAI_EXPORT void sdaiBeginning(SdaiIterator iterator);

/** \details
  Moves the position of a specified iterator to the next element in the aggregate instance.
  \param iterator [in] An iterator to set the position.
  \returns sdaiTRUE if the next element exists and became the current; otherwise, the function returns sdaiFALSE.
*/
DAI_EXPORT SdaiBoolean sdaiNext(SdaiIterator iterator);



/** \details
  Retrieves the value of the current element referenced by a specified iterator.
  \param iterator [in] An iterator to get the value from.
  \param valueType [in] A type of the element value .
  \param value [out] A placeholder for the required element value.
  \returns A raw pointer to the element value.
*/
DAI_EXPORT void* sdaiGetAggrByIterator(SdaiIterator iterator, SdaiPrimitiveType valueType, void* value);


/** \details
  Retrieves the aggregate element bound from a specified iterator.
  \param iterator [in] An iterator to get the element bound from.
  \returns An SDAI integer value that represents the element bound.
*/
DAI_EXPORT SdaiInteger sdaiGetAggrElementBoundByItr(SdaiIterator iterator);


/** \details 
  Retrieves the lower bound of a specified aggregate element.
  \param aggregate [in] An aggregate to get the lower bound from.
  \returns An SDAI integer value that represents the lower bound value.
*/
DAI_EXPORT SdaiInteger sdaiGetLowerBound(SdaiAggr aggregate);

/** \details 
  Retrieves the upper bound of a specified aggregate element.
  \param aggregate [in] An aggregate to get the upper bound from.
  \returns An SDAI integer value that represents the upper bound value.
*/
DAI_EXPORT SdaiInteger sdaiGetUpperBound(SdaiAggr aggregate);


/* 6.11 Application instance aggregate operations */

/** \details
  Creates an aggregate instance that replaces the current member of an aggregate instance referenced by a specified iterator.
  \param current [in]  An iterator that refers to the current member of the aggregate.
  \returns The identifier of the newly created aggregate instance.
*/ 
DAI_EXPORT SdaiAggr sdaiCreateNestedAggrByItr(SdaiIterator current);

/** \details
  Creates an aggregate instance that replaces the current member of an aggregate instance referenced by a specified iterator.
  \param current         [in]  An iterator that refers to the current member of the aggregate.
  \param selaggrInstance [in] An attribute data block (ADB) that specifies the type of the aggregate to create.
  \returns The identifier of the newly created aggregate instance.
*/
DAI_EXPORT SdaiAggr sdaiCreateNestedAggrByItrADB(SdaiIterator current, SdaiADB selaggrInstance);


/** \details
  Sets new values to an aggregate instance that is referenced by a specified iterator.
  \param current   [in]  An iterator that refers to the current member of the aggregate.
  \param valueType [in] An aggregate value data type.
  \remarks 
  You can set more than one element value through passing them to the function starting from the third parameter.
*/
DAI_EXPORT void sdaiPutAggrByIterator(SdaiIterator iterator, SdaiPrimitiveType valueType, ...);


/** \details
  Removes an aggregate instance that is referenced by a specified iterator.
  \param iterator [in]  An iterator that refers to the current member of the aggregate.
*/
DAI_EXPORT void sdaiRemoveByIterator(SdaiIterator iterator);


/* 6.12 Application instance unordered collection operations */

/** \details
  Adds a new member to an unordered aggregate (set/bag) instance.
  \param unorderedAggr [in] An aggregate instance to add a new member to.
  \param valueType     [in] A data type of the new aggregate member value.
  \remarks 
  You can specify more than one element value for the new aggregate by passing them to the function starting from the third parameter.
*/
DAI_EXPORT void sdaiAdd(SdaiUnorderedAggr unorderedAggr, SdaiPrimitiveType valueType, ...);


/** \details 
  Creates a nested aggregate in a specified aggregate.
  \param aggregate [in] An aggregate that should contain the newly created aggregate.
  \returns The created SDAI aggregate object.
*/
DAI_EXPORT SdaiAggr sdaiCreateNestedAggr(SdaiUnorderedAggr aggregate);

/** \details 
  Creates a nested aggregate in a specified aggregate.
  \param aggregate       [in] An aggregate that should contain the newly created aggregate.
  \param selaggrInstance [in] An attribute data block (ADB) that represents the aggregate data type.
  \returns The created SDAI aggregate object.
*/
DAI_EXPORT SdaiAggr sdaiCreateNestedAggrADB(SdaiUnorderedAggr aggregate, SdaiADB selaggrInstance);

/** \details
  Removes a member from an unordered aggregate (set/bag) instance.
  \param unorderedAggr [in] An aggregate instance to remove the member from.
  \param valueType     [in] A data type of the value to remove.
  \remarks 
  You can remove more than one member from the unordered aggregate by passing values to the function starting from the third parameter.
*/
DAI_EXPORT void sdaiRemove(SdaiUnorderedAggr unorderedAggr, SdaiPrimitiveType valueType, ...);

/* 6.13 Entity instance ordered collection operations */

/** \details 
  Retrieves an aggregate value by its index.
  \param aggregate [in] An aggregate to retrieves the value from.
  \param index     [in] An index of the required value.
  \param valueType [in] A data type of the required value.
  \param value     [out] A placeholder that contains the aggregate value.
  \returns A raw pointer to the required aggregate value.
*/
DAI_EXPORT void* sdaiGetAggrByIndex(SdaiOrderedAggr aggregate, SdaiAggrIndex index, SdaiPrimitiveType valueType, void *value);

/** \details
  Moves the current position of a specified iterator to the end of the aggregate.
  \param iterator [in] An iterator.
*/
DAI_EXPORT void sdaiEnd(SdaiIterator iterator);

/** \details
  Moves the current position of a specified iterator to the previous aggregate item.
  \param iterator [in] An iterator.
  \returns sdaiTRUE if there is a member at the new position; otherwise, the function returns sdaiFALSE.
*/
DAI_EXPORT SdaiBoolean sdaiPrevious(SdaiIterator iterator);

/** \details 
  Retrieves the bound of an aggregate element by its index.
  \param aggregate [in] An aggregate.
  \param index     [in] An index of the element.
  \returns An SDAI integer value that contains the bound of the aggregate element.
*/
DAI_EXPORT SdaiInteger sdaiGetAggrElementBoundByIndex(SdaiOrderedAggr aggregate, SdaiAggrIndex index);

/* 6.14 Application instance ordered collection operations */

/** \details
  Sets a new value (with possible coversion if necessary) 
  for a member fo a specified ordered aggregate instance referenced by a specified index.
  \param aggregate [in] An aggregate instance.
  \param index     [in] An index of the insertion place.
  \param valueType [in] A value type.
*/
DAI_EXPORT void sdaiPutAggrByIndex(SdaiOrderedAggr aggregate, SdaiAggrIndex index, SdaiPrimitiveType valueType, ...);


/** \details
  Creates a nested aggregate instance within a specified aggregate instance at the position specified by the index.
  \param aggregate [in] An aggregate instance that contains the created nested aggregate.
  \param index     [in] An index that determines the position of the created item.
  \returns The identifier of the newly created aggregate instance.
*/
DAI_EXPORT SdaiAggr sdaiCreateNestedAggrByIndex(SdaiOrderedAggr aggregate, SdaiAggrIndex index);


/** \details
  Creates a nested aggregate instance stored in an attribute data block 
  within a specified aggregate instance at the position specified by the index.
  \param aggregate       [in] An aggregate instance that contains the created nested aggregate.
  \param index           [in] An index that determines the position of the created item.
  \param selaggrInstance [in] An attribute data block instance that defines the type of the SELECT value.
  \returns The identifier of the newly created aggregate instance.
  \code
  <pre>
  SdaiADB lineIndex = sdaiCreateEmptyADB(); 
  SdaiString  lineIndexPath[] = { "ifclineindex" }; 
  sdaiPutADBTypePath(lineIndex, 1, lineIndexPath); 
  SdaiAggr lineIndexAggr = sdaiCreateNestedAggrByIndexADB(segments, 0, lineIndex);
  </pre>
*/
DAI_EXPORT SdaiAggr sdaiCreateNestedAggrByIndexADB(SdaiOrderedAggr aggregate, SdaiAggrIndex index, SdaiADB selaggrInstance);

/* 6.15 Entity instance array operations */

/** \details 
  Determines whether the element value in a specified array is set.
  \param array [in] An array that contains the element.
  \param index [in] An index of the array element.
  \returns sdaiTRUE if the element with the specified index has a set value; otherwise, the function returns sdaiFALSE.
*/
DAI_EXPORT SdaiBoolean sdaiTestArrayByIndex(SdaiArray array, SdaiAggrIndex index);

/** \details 
  Determines whether the element value in a specified array is set.
  The element of the array is determined with an iterator object.
  \param iterator [in] An iterator that defined the position of the element in the array.
  \returns sdaiTRUE if the element with the specified index has a set value; otherwise, the function returns sdaiFALSE.
*/
DAI_EXPORT SdaiBoolean sdaiTestArrayByItr(SdaiIterator iterator);

/** \details
  Retrieves the lower index for a specified array.
  \param array [in] An array.
  \returns An SDAI integer value that contains the lower value of the array index.
*/
DAI_EXPORT SdaiInteger sdaiGetLowerIndex(SdaiArray array);

/** \details 
  Retrieves the upper index for a specified array.
  \param array [in] An array.
  \returns An SDAI integer value that contains the upper value of the array index.
*/
DAI_EXPORT SdaiInteger sdaiGetUpperIndex(SdaiArray array);

/* 6.16 Application instance array operations */

/** \details 
  Unsets a specified element of the application instances array.
  \param array [in] An array of application instances.
  \param index [in] An index value that determines the element position in the array. 
*/
void sdaiUnsetArrayByIndex(SdaiArray array, SdaiAggrIndex index);

/** \details 
  Unsets a specified element of the application instances array.
  \param iterator [in] An iterator object that provides access to the element.
*/
void sdaiUnsetArrayByItr(SdaiIterator iterator);

/** \details 
  Reindexes the elements of a specified array.
  \param array [in] An array to be reindexed.
*/
void sdaiReindexArray(SdaiArray array);

/** \details 
  Resets the index for a specified array: changes the lower and upper bounds of the index value.
  \param array [in] An array. 
  \param lower [in] A new lower index value to be set.
  \param upper [in] A new upper index value to be set.
*/
void sdaiResetArrayIndex(SdaiArray array, SdaiAggrIndex lower, SdaiAggrIndex upper);

/* 6.17 Application instance list operations */

/** \details 
  Inserts a new value into an application instance list before the element referenced by a specified iterator.
  \param iterator  [in] An iterator object.
  \param valueType [in] A type of the inserted value.
  \remarks 
  You can insert more than one value into the list: pass as many values as you need after the parameter that specifies the data type.
*/
DAI_EXPORT void sdaiInsertBefore(SdaiIterator iterator, SdaiPrimitiveType valueType, ...);

/** \details 
  Inserts a new value into an application instance list after the element referenced by a specified iterator.
  \param iterator  [in] An iterator object.
  \param valueType [in] A type of the inserted value.
  \remarks 
  You can insert more than one value into the list: pass as many values as you need after the parameter that specifies the data type.
*/
DAI_EXPORT void sdaiInsertAfter(SdaiIterator iterator, SdaiPrimitiveType valueType, ...);

/** \details 
  Inserts a new value into an application instance list on a position specified by an index value.
  \param list      [in] A list for the insertion.
  \param index     [in] An index value that defines the position to insert a new value.
  \param valueType [in] A type of the inserted value.
  \remarks 
  You can insert more than one value into the list: pass as many values as you need after the parameter that specifies the data type.
*/
DAI_EXPORT void sdaiInsertByIndex(SdaiList list, SdaiAggrIndex index, SdaiPrimitiveType valueType, ...);

/** \details 
  Inserts a new nested aggregate value into an application instance list before the element referenced by a specified iterator.
  \param iterator [in] An iterator object that refers to the element to insert the new value.
  \returns The inserted aggregate value.
*/
DAI_EXPORT SdaiAggr sdaiInsertNestedAggrBefore(SdaiIterator iterator);

/** \details 
  Inserts a new nested aggregate value into an application instance list before the element referenced by a specified iterator.
  \param iterator        [in] An iterator object that refers to the element to insert the new value.
  \param selaggrInstance [in] An attribute data block (ADB) object that defines the data type of the value.
  \remarks 
  The passed ADB object determines the type of created aggregate in cases when aggregate elements have the SELECT data type.
  \returns The inserted aggregate value.
*/
DAI_EXPORT SdaiAggr sdaiInsertNestedAggrBeforeADB(SdaiIterator iterator, SdaiADB selaggrInstance);


/** \details 
  Inserts a new nested aggregate value into an application instance list after the element referenced by a specified iterator.
  \param iterator [in] An iterator object that refers to the element to insert the new value.
  \returns The inserted aggregate value.
*/
DAI_EXPORT SdaiAggr sdaiInsertNestedAggrAfter(SdaiIterator iterator);

/** \details 
  Inserts a new nested aggregate value into an application instance list after the element referenced by a specified iterator.
  \param iterator        [in] An iterator object that refers to the element to insert the new value.
  \param selaggrInstance [in] An attribute data block (ADB) object that defines the data type of the value.
  \returns The inserted aggregate value.
  \remarks 
  The passed ADB object determines the type of created aggregate in cases when aggregate elements have the SELECT data type.
*/
DAI_EXPORT SdaiAggr sdaiInsertNestedAggrAfterADB(SdaiIterator iterator, SdaiADB selaggrInstance);

/** \details 
  Inserts a new nested aggregate value into an application instance list at the position specified by an index.
  \param list  [in] An application instance list.
  \param index [in] An index value.
  \returns The inserted aggregate value.
*/
DAI_EXPORT SdaiAggr sdaiInsertNestedAggrByIndex(SdaiList list, SdaiAggrIndex index);

/** \details 
  Inserts a new nested aggregate value into an application instance list at the position specified by an index.
  \param list            [in] An application instance list.
  \param index           [in] An index value.
  \param selaggrInstance [in] An attribute data block (ADB) object that defines the data type of the value.
  \returns The inserted aggregate value.
  \remarks 
  The passed ADB object determines the type of created aggregate in cases when aggregate elements have the SELECT data type.
*/
DAI_EXPORT SdaiAggr sdaiInsertNestedAggrByIndexADB(SdaiList list, SdaiAggrIndex index, SdaiADB selaggrInstance);

/** \details 
  Removes a list element specified with an index value.
  \param list  [in] An application instance list.
  \param index [in] An index value that defines the positionn of an element to remove.
*/
DAI_EXPORT void sdaiRemoveByIndex(SdaiList list, SdaiAggrIndex index);


/* 6.18 C late binding specific SELECT TYPE operations */

/** \details
  Specifies the type path for an attribute data block (ADB).
  The type path consists of an array of strings that defines the path in the nested SELECT types hierarchy.
  \param block          [in] An attribute data block (ADB) instance.
  \param typeNameNumber [in] A size of the string array that defines the path.
  \param typeNameVector [in] A string array with the path.
*/
DAI_EXPORT void sdaiPutADBTypePath(SdaiADB block, SdaiInteger typeNameNumber, SdaiString *typeNameVector);


/** \details
  Retrieves the current type path for a specified attribute data block (ADB).
  \param block [in] An attribute data block (ADB) instance.
  \param typeNameNumber [out] A placeholder for the is a size of the path string array.
  \returns A raw pointer to the string array that contains the type path if the path was successfully retrieved; otherwise, returns the NULL pointer.
  \remarks 
  The type path consists of an array of strings that defines the path in the nested SELECT types hierarchy.
*/
DAI_EXPORT SdaiString *sdaiGetADBTypePath(SdaiADB block, SdaiInteger *typeNameNumber);

/* ODA SDAI extension functions */

/** \details
  Creates a new repository with a specified name within the current SDAI session. 
  \param session [in] An SDAI session instance.
  \param name [in] A string that contains the new repository name.
  \returns A pointer to the created repository if it was successfully created; otherwise, the function returns the NULL pointer.
*/
DAI_EXPORT SdaiRep _sdaiCreateRepository(SdaiSession session, SdaiString name);

/** \details
  Creates a new repository from a specified file within the current SDAI session. 
  \param session  [in] A session instance.
  \param fileName [in] A string that contains the file name.
  \param name     [in] A string that contains the repository name.
  \returns 
  The created repository instance represented with its <link SdaiRep, handler> if the repository was successfully created; 
  otherwise, the function returns the NULL pointer.
  \returns instance of the created repository, in other case NULL
  \remarks 
  If the name of the repository is empty then the name of the file is used as the repository name.
  If the file contains several data sections (file_description.implementation_level equals to  "3" or higher), 
  every model gets the name predefined in file;
  otherwise (file_description.implementation_level equals to 2 ("2;1", "2;2") 
  only the single model with the name "default" is created. 
  
*/
DAI_EXPORT SdaiRep _sdaiCreateRepositoryFromFile(SdaiSession session, SdaiString fileName, SdaiString name);


/** \details
  Saves a specified repository to a file.
  \param repository [in] A repository instance.
  \param fileName [in] A string that contains the name of the file where the contents of the repository are saved.
  \returns sdaiTRUE if the repository was successfully saved into the file; otherwise, the function return sdaiFALSE.
*/
DAI_EXPORT SdaiBoolean _sdaiWriteRepositoryToFile(SdaiRep repository, SdaiString fileName);

/** \details
 Retrieves an application instance by its identifier
 \param model [in] A model that owns the application instance.
 \param id    [in] An entity identifier.
 \returns An application instance represented by its STEP-identifier if the entity was found; otherwise, the function returns the NULL pointer.
*/
DAI_EXPORT SdaiAppInstance _sdaiGetEntityById(SdaiModel model, SdaiInteger id);

/** \details
 Retrieves the identifier of a specified entity.
 \param entInst [in] An entity instance.
 \returns A STEP-identifier of the entity instance.
*/
DAI_EXPORT SdaiInteger _sdaiGetEntityId(SdaiAppInstance entInst);


/** \details
 Retrieves the primitive type (domain) of a specified attribute.
 \param attribute [in] An attribute.
 \returns A primitive type that represents the current attribute domain.
*/
DAI_EXPORT SdaiPrimitiveType _sdaiAttributeDomain(SdaiAttr attribute);


/** \details
 Defines kinds of attribute type information.
*/
typedef enum {
  /**Unknown type.*/
  attrNOTYPE, 
  /**Explicit type.*/
  attrEXPLICIT, 
  /**Inverse type.*/
  attrINVERSE, 
  /**Derived type.*/
  attrDERIVED
}
SdaiAttributeType;


/** \details
 Retrieves the specified attribute's type.
 \param attribute [in] An attribute instance.
 \returns An attribute type.
*/
DAI_EXPORT SdaiAttributeType _sdaiGetAttributeType(SdaiAttr attribute);

/** \details
Retrieves the file description instance of the specified repository's header section.
\param repository [in] A repository to get the instance from.
\returns A file description instance of the repository's header section.
*/
DAI_EXPORT SdaiInstance _sdaiHeaderDescription(SdaiRep repository);

/** \details
Retrieves the file name instance of the specified repository's header section.
\param repository [in] A repository to get the instance from.
\returns A file name instance of the repository's header section.
*/
DAI_EXPORT SdaiInstance _sdaiHeaderName(SdaiRep repository);

/** \details
Retrieves the current access mode for a specified SDAI-model.
\param model [in] A model to get access mode for.
\returns The current access mode for the specified model.
*/
DAI_EXPORT SdaiAccessMode _sdaiModelAccessMode(SdaiModel model);

/** \details
Retrieves the identifiers of all the entity instances in the model
that reference the current entity instance.

\param instance [in] Identifier of the entity instance whose users are requested.
\param domain [in] Identifier of a NPL containing the SdaiSchemaInstance identifiers of the
schema instances that define the domain of the function request.
\param resultList [in/out]  Identifier of the pre-existing NPL to which the
identifiers of the entity instances referencing the current instance by any attribute are added.
\returns Identifier of the result NPL.
*/
DAI_EXPORT SdaiNPL sdaiFindInstanceUsers(SdaiInstance instance, SdaiNPL domain, SdaiNPL resultList);

/** \details
Retrieves the identifiers of all the entity instances in the model data
that reference the curent entity instance by the specified attribute.

\param instance [in] Identifier of the entity instance whose users are requested.
\param role [in] Identifier of the attribute as the role being requested.
\param domain [in] Identifier of a NPL containing the SdaiSchemaInstance identifiers of the
schema instances that define the domain of the function request.
\param resultList [in/out]  Identifier of the pre-existing NPL to which the
identifiers of the entity instances referencing the current instance by the specified attribute are added.
\returns Identifier of the result NPL.
*/
DAI_EXPORT SdaiNPL sdaiFindInstanceUsedIn(SdaiInstance instance, SdaiAttr role, SdaiNPL domain, SdaiNPL resultList);

/** \details
Retrieves the identifiers of all the entity instances in the model data
that reference the curent entity instance by the specified attribute name.

\param instance [in] Identifier of the entity instance whose users are requested.
\param roleName [in] A string that contains a fully qualified attribute name, i.e.
ifcplacement.location.
\param domain [in] Identifier of a NPL containing the SdaiSchemaInstance identifiers of the
schema instances that define the domain of the function request.
\param resultList [in/out]  Identifier of the pre-existing NPL to which the
identifiers of the entity instances referencing the current instance by the specified attribute name are added.
\returns Identifier of the result NPL.
*/
DAI_EXPORT SdaiNPL sdaiFindInstanceUsedInBN(SdaiInstance instance, SdaiString roleName, SdaiNPL domain, SdaiNPL resultList);

/** \details
Retrieves the identifiers of the attributes of entity instances referencing
the specified entity instance.

\param instance [in] Identifier of the entity instance whose roles are requested.
\param domain [in] Identifier of a NPL containing the SdaiSchemaInstance identifiers of the
schema instances that define the domain of the function request.
\param resultList [in/out]  Identifier of the pre-existing NPL to which SdaiAttr identifiers of the
entity instances that reference the specified entity instance are appended.
\returns Identifier of the result NPL.
*/
DAI_EXPORT SdaiNPL sdaiFindInstanceRolesOf(SdaiInstance instance, SdaiNPL domain, SdaiNPL resultList);

/** \details
Retrieves the identifier of all SdaiNamedType data dictionary 
instances of which the specified entity instance is a member.

\param instance [in] Identifier of the entity instance whose types are requested.
\param resultList [in/out]  Identifier of the pre-existing NPL to which which the SdaiNamedType instance
identifiers for those dictionary instances are added meeting the specified criteria.
\returns Identifier of the result NPL.
*/
DAI_EXPORT SdaiNPL sdaiFindInstanceTypeOf(SdaiInstance instance, SdaiNPL resultList);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // _SDAI_
