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

#ifndef _ODTV_FACTORY_H_INCLUDED_
#define _ODTV_FACTORY_H_INCLUDED_

#include "Tv.h"
#include "TvDatabase.h"
#include "TvImport.h"
#include "TvDatabaseReceiver.h"

/** \details
  This is an interface that provides Visualize limitation control.
*/
class OdTvLimitManager
{
public:
  /** \details
    List of possible supported limits.
  */
  enum SupportedLimit
  {
    kMemoryLimit = 1,        //objects memory usage limit
    kUnloadingLimit = 1 << 1 //objects unloading limit
  };
  
  /** \details
    Returns limits supported by current OdTvLimitManager implementation.
    
    \returns
    Value that represents supported limits.
  */
  virtual OdUInt8 supportedLimits() const { return kMemoryLimit; }
  
  /** \details
    Enumeration for memory limit control.
  */
  enum MemoryLimitControlResult
  {
    kPassed,        //control passed
    kTryLessSize,   //control not passed, but it may be passed for smaller objects
    kNotPassed      //control not passed
  };
  
  /** \details
    Enumeration for checking limit reasons.
  */
  enum MemoryLimitControlReason
  {
    kReasonLoadObject,      //object loading
    kReasonVectorization,   //object vectorization
    kReasonUnloadObject     //object unloading
  };
  
  /** \details
    Checks memory limit before operation iteration.
    
    \param nReason                    [in] Reason of checking, specifies current operation.
    \param nApproximateMemoryUsage    [in] Approximate memory amount to check whether it can be additionally used considering current memory consumption. May be 0 if there is no estimate.
  */
  virtual MemoryLimitControlResult checkMemoryUsage( OdUInt8 nReason, OdUInt64 nApproximateMemoryUsage = 0 ) const = 0;
};

/** \details
  This is an interface class for an OdTvFactory object used by Visualize SDK client applications to create new object instances.

  \remarks
  The OdTvFactory class is used through its API calls to create and delete main Visualize SDK object instances.
  \sa
  <link tv_working_with_base_classes_factory, Work with Factories>
*/
class ODTV_EXPORT OdTvFactoryId : public OdTvId 
{
  public:

  /** \details
    Creates a new Visualize database object and returns its identifier.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the database identifier if the database is successfully created, otherwise returns a null identifier.
    \remarks 
    If the rc parameter is not null and the database is successfully created, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    If the database is successfully created, the result of the isNull() method of the returned identifier object is equal to false; 
    otherwise the isNull() method returns true.
  */
  OdTvDatabaseId createDatabase(OdTvResult* rc = NULL);

  /** \details
    Creates a new Visualize database object with the given code page and returns its identifier (should be used very carefully)
    
    \param cp       [in]  Value for the code page.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the database identifier if the database is successfully created, otherwise returns a null identifier.
    \remarks
    If the rc parameter is not null and the database is successfully created, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    If the database is successfully created, the result of the isNull() method of the returned identifier object is equal to false;
    otherwise the isNull() method returns true.
  */
  OdTvDatabaseId createDatabase(OdCodePageId cp, OdTvResult* rc = NULL);

  /** \details
    Removes the Visualize database object specified by its identifier.
    
    \param id [in] A database identifier.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the database object with the specified identifier is found and successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  OdTvResult removeDatabase(const OdTvDatabaseId& id);

  /** \details
    Removes all Visualize databases created during the current session.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If all database objects are successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  OdTvResult clearDatabases();

  /** \details
    This method is deprecated and will be removed soon, use importFile() instead.
    It is possible to use analogue from OdTvDeprecated namespace, but this analogue eventually will be removed too.
    Creates a new Visualize database and loads the content of a specified file into the newly created database.
    
    \param filename     [in] A full file path.
    \param bMtMode      [in] A flag value that determines whether the reading file mode is multi-threading (if equal to true) or not (if equal to false).
    \param bPartialMode [in] A flag value that determines whether the partial reading mode is applied (if is equal to true) or not (if is equal to false).
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the database identifier if the database is successfully created and the content of the file is uploaded to the database; 
    otherwise it returns a null identifier.
    \remarks 
    If the rc parameter is not null and the database is successfully created and filled with the file content, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    The method throws the <link OdTvError, OdTvError> exception if the read operation is not successful.
    The partial read mode assumes that only visible data is loaded from the specified stream buffer.
  */
  OdTvDatabaseId readFile(const OdString& filename, bool bMtMode = false, bool bPartialMode = false, OdTvResult* rc = NULL);

  /** \details
    Creates a new Visualize database and loads the content of a specified .VSFX file into the newly created database.
    
    \param filename     [in] A full .VSFX file path.
    \param bMtMode      [in] A flag value that determines whether the reading file mode is multi-threading (if equal to true) or not (if equal to false).
    \param bPartialMode [in] A flag value that determines whether the partial reading mode is applied (if is equal to true) or not (if is equal to false).
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \param options      [in] An instance of OdTvVSFXReadOptions that specifies VSFX-specific read options.
    \returns Returns the database identifier if the database is successfully created and the content of the file is uploaded to the database;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the database is successfully created and filled with the file content, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    The method throws the <link OdTvError, OdTvError> exception if the read operation is not successful.
    The partial read mode assumes that only visible data is loaded from the specified stream buffer.
  */
  OdTvDatabaseId readVSFX( const OdString& filename, bool bMtMode = false, bool bPartialMode = false, OdTvResult* rc = NULL, const OdTvVSFXReadOptions& options = OdTvVSFXReadOptions() );

  /** \details
    This method is deprecated and will be removed soon, use importFile() instead.
    It is possible to use analogue from OdTvDeprecated namespace, but this analogue eventually will be removed too.
    Creates a new Visualize database and loads the data from a specified stream buffer into the newly created database.
    
    \param buff         [in] A pointer to the data stream buffer.
    \param bMtMode      [in] A flag value that determines whether the reading file mode is multi-threading (if equal to true) or not (if equal to false).
    \param bPartialMode [in] A flag value that determines whether the partial reading mode is applied (if equal to true) or not (if equal to false).
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the database identifier if the database is successfully created and filled from the specified data stream buffer; otherwise it returns a null identifier.
    \remarks 
    If the rc parameter is not null and the database is successfully created and filled with the data, the rc parameter accepts tvOk value; otherwise it contains an appropriate error code.
    The method throws the <link OdTvError, OdTvError> exception if the read operation is not successful.
    The partial read mode assumes that only visible data is loaded from the specified stream buffer.
  */
  OdTvDatabaseId read(OdStreamBuf *buff, bool bMtMode = false, bool bPartialMode = false, OdTvResult* rc = NULL);

  /** \details
    Creates a new Visualize database and loads the data from a specified .VSFX stream buffer into the newly created database.
    
    \param buff         [in] A pointer to the .VSFX data stream buffer.
    \param bMtMode      [in] A flag value that determines whether the reading file mode is multi-threading (if equal to true) or not (if equal to false).
    \param bPartialMode [in] A flag value that determines whether the partial reading mode is applied (if equal to true) or not (if equal to false).
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \param options      [in] An instance of OdTvVSFXReadOptions that specifies VSFX-specific read options.
    \returns Returns the database identifier if the database is successfully created and filled from the specified data stream buffer; otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the database is successfully created and filled with the data, the rc parameter accepts tvOk value; otherwise it contains an appropriate error code.
    The method throws the <link OdTvError, OdTvError> exception if the read operation is not successful.
    The partial read mode assumes that only visible data is loaded from the specified stream buffer.
  */
  OdTvDatabaseId readVSFX( OdStreamBufPtr pStream, bool bMtMode = false, bool bPartialMode = false, OdTvResult* rc = NULL, const OdTvVSFXReadOptions& options = OdTvVSFXReadOptions() );

  /** \details
    Creates a new Visualize database and imports the content of the specified file into the newly created database.
    
    \param pParams  [in] A pointer to an object that contains the <link OdTvBaseImportParams, import parameters>.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the database identifier if the database is successfully created and the content of the file is imported to the database; 
    otherwise it returns a null identifier.
    \remarks 
    If the rc parameter is not null and the database is successfully created and filled with the file content, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    The method throws the <link OdTvError, OdTvError> exception if the import operation is not successful.
  */
  OdTvDatabaseId importFile(const OdTvBaseImportParams* pParams, OdTvResult* rc = NULL);

  /** \details
    Imports the contents of the specified file into the VSF file trying to use as much less memory as it is possible (currently implemented only for .dwg files)
    
    \param pParams         [in] A pointer to an object that contains the <link OdTvBaseImportParams, import parameters>.
    \param outPutFileName  [in] A full path to the output VSF file.
    \param pOptions        [in] Pointer to a structure which describes the compression options.
    \param rc              [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the import process is successfully performed, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  OdTvResult lowMemoryImportFile(const OdTvBaseImportParams* pParams, const OdString& outPutFileName, const OdTvVSFExportOptions* pOptions = NULL);

  /** \details
    This method is deprecated and will be removed soon, use importFile() instead.
    It is possible to use analogue from OdTvDeprecated namespace, but this analogue eventually will be removed too.
    Creates a new Visualize database and loads the data from a specified steam buffer into the newly created database 
    using a specified controller.
    
    \param controller [in] A pointer to a controller object.
    \param buff       [in] A pointer to the data stream buffer.
    \param closeInput [in] A close input flag value.
    \param rc         [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the database identifier if the database is successfully created and the content of the stream is loaded to the database; 
    otherwise it returns a null identifier.
    \remarks
    The method throws the <link OdTvError, OdTvError> exception if the loading operation is not successful.
    In most cases this method is used for internal purposes in other ODA products.
  */
  OdTvDatabaseId read(OdRxObject* controller, OdStreamBuf *buff, bool closeInput = true, OdTvResult* rc = NULL);

  /** \details
    Removes all fonts from the global font table.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If all fonts objects are successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
    This operation has influence on every text style in each database. Should be used very carefully.
  */
  OdTvResult clearFontTable();

  /** \details
    Assigns the OdTvLimitManager to the factory
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the limit manager was successfully assign, the method returns tvOk; otherwise it returns an appropriate error code.
    Such manger can be used in partial viewing mode or (in the future) during low memory import functionality.
  */
  OdTvResult setLimitManager( OdTvLimitManager* pLimitManager );

  /** \details
    Returns the assigned OdTvLimitManager instance
    
    \param rc         [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  OdTvLimitManager* limitManager( OdTvResult* rc = NULL );
  
  /** \details
    Creates an instance of OdTvDatabaseReceiver.
    
    \param rc         [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the OdTvDatabaseReceiver instance.
  */
  OdTvDatabaseReceiverPtr createDatabaseReceiver( OdTvResult* rc = NULL );
};

/** \details
  Global function for Visualize SDK initialization. 
  \returns Returns the identifier of the Visualize SDK factory singleton object.
  \sa
  <link tv_activation_cpp, Activating ODA Software>
*/
ODTV_EXPORT OdTvFactoryId odTvInitialize();


/** \details
  Global function for Visualize SDK de-initialization.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \remarks 
  If Visualize platform-dependent functionality is successfully de-initialized, the function returns tvOk; otherwise it returns an appropriate error code.
  \sa
  <link tv_activation_cpp, Activating ODA Software>
*/
ODTV_EXPORT OdTvResult odTvUninitialize();


/** \details
  Retrieves the identifier of the Visualize SDK factory singleton object.
  \returns Returns the factory identifier.
  \sa
  <link tv_working_with_base_classes_factory, Work with Factories>
*/
ODTV_EXPORT OdTvFactoryId odTvGetFactory();

#endif //_ODTV_FACTORY_H_INCLUDED_
