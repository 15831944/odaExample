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

#ifndef _ODTV_DEPRECATED_H_INCLUDED_
#define _ODTV_DEPRECATED_H_INCLUDED_

#include "Tv.h"
#include "TvDatabase.h"
#include "TvImport.h"
#include "TvFactory.h"

/** \details
  This namespace contains analogues of deprecated VisualizeSDK methods for temporary backward compatibility.
  Declared functions will be eventually removed.
  Refer to the documentation for the correct transition from deprecated to new methods.
*/
namespace OdTvDeprecated
{
  /** \details 
  This is anologue of deprecated OdTvFactoryId::readFile(). Use OdTvFactoryId::importFile() instead.
  Creates a new Visualize database and loads the content of a specified file into the newly created database.

  \param factoryId    [in] An identifier of OdTvFactory.
  \param filename     [in] A full file path.
  \param bMtMode      [in] A flag value that determines whether the reading file mode is multi-threading (if equal to true) or not (if equal to false).
  \param bPartialMode [in] A flag value that determines whether the partial reading mode is applied (if is equal to true) or not (if is equal to false).
  \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns the database identifier if the database is successfully created and the content of the file is uploaded to the database;
  otherwise it returns a null identifier.
  */
  ODTV_EXPORT OdTvDatabaseId readFile( const OdTvFactoryId& factoryId, const OdString& filename, bool bMtMode = false, bool bPartialMode = false, OdTvResult* rc = NULL );
  /** \details
  This is anologue of deprecated OdTvFactoryId::read(). Use OdTvFactoryId::importFile() instead.
  Creates a new Visualize database and loads the data from a specified stream buffer into the newly created database.

  \param factoryId    [in] An identifier of OdTvFactory.
  \param buff         [in] A pointer to the data stream buffer.
  \param bMtMode      [in] A flag value that determines whether the reading file mode is multi-threading (if equal to true) or not (if equal to false).
  \param bPartialMode [in] A flag value that determines whether the partial reading mode is applied (if equal to true) or not (if equal to false).
  \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns the database identifier if the database is successfully created and filled from the specified data stream buffer; otherwise it returns a null identifier.
  */
  ODTV_EXPORT OdTvDatabaseId read( const OdTvFactoryId& factoryId, OdStreamBuf* buff, bool bMtMode = false, bool bPartialMode = false, OdTvResult* rc = NULL );
  /** \details
  This is anologue of deprecated OdTvFactoryId::read(). Use OdTvFactoryId::importFile() instead.
  Creates a new Visualize database and loads the data from a specified steam buffer into the newly created database
  using a specified controller.

  \param factoryId    [in] An identifier of OdTvFactory.
  \param controller [in] A pointer to a controller object.
  \param buff       [in] A pointer to the data stream buffer.
  \param closeInput [in] A close input flag value.
  \param rc         [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns the database identifier if the database is successfully created and the content of the stream is loaded to the database;
  otherwise it returns a null identifier.
  */
  ODTV_EXPORT OdTvDatabaseId read( const OdTvFactoryId& factoryId,  OdRxObject* controller, OdStreamBuf* buff, bool closeInput = true, OdTvResult* rc = NULL );
  /** \details
  This is anologue of deprecated OdTvDatabase::write(). Use OdTvDatabase::writeVSFX() instead.
  Writes the content of the database to a specified file.

  \param dbId             [in] An identifier of database to be written.
  \param filename         [in] A full path to the output file.
  \param pOptions         [in] Pointer to a structure which describes the compression options.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the write operation.
  If the write operation was successful, the method returns the tvOk value; otherwise it throws an <link OdTvError, OdTvError> exception.
  */
  ODTV_EXPORT OdTvResult writeFile( const OdTvDatabaseId& dbId, const OdString& filename, const OdTvVSFExportOptions* pOptions = NULL );
  /** \details
  This is anologue of deprecated OdTvDatabase::write(). Use OdTvDatabase::writeVSFX() instead.
  Writes the contents of the database object to the specified stream buffer.
    
  \param dbId             [in] An identifier of database to be written.
  \param buff             [in] Pointer to a stream buffer.
  \param pOptions         [in] Pointer to a structure which describes the compression options.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the write operation.
  If the write operation was successful, the method returns the tvOk value; otherwise it throws an <link OdTvError, OdTvError> exception.
  */
  ODTV_EXPORT OdTvResult write( const OdTvDatabaseId& dbId, OdStreamBuf* buff, const OdTvVSFExportOptions* pOptions = NULL );
};

#endif //_ODTV_DEPRECATED_H_INCLUDED_
