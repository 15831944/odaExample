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

#ifndef OD_TV_VISUALIZEFILER_H
#define OD_TV_VISUALIZEFILER_H

#include "RxModule.h"
#include "RxMember.h"
#include "RxValue.h"
#include "RxProperty.h"
#include "SharedPtr.h"
#include "DbBaseDatabase.h"

#include "TD_PackPush.h"
#include "TvDatabase.h"

#define STL_USING_MAP
#include "OdaSTL.h"

/** \details
  The structure stores an item that is passed to the filer callback function to implement item selection.
  The structure contains the item name and the choose flag which determines whether the item is chosen (if equal to true) or not (if equal to false).
  
  \remarks 
  If the items should not be in a simple list but in a tree, the item name should have the AAA\BBB\CCC format, 
  where AAA is the name of the parent of BBB, and BBB is the name of the parent of CCC,
  and CCC is the actual item name.
  \sa
  <link tv_interact_with_file_formats_filers, Work with Visualize Filers>
*/
struct OdTvFilerFeedbackItemForChoose
{
  /** \details 
    Creates a new choose feedback item instance with default parameters.
  */
  OdTvFilerFeedbackItemForChoose()
  {
    m_strName = OD_T("");
    m_strUniqueName = OD_T("");
    m_bChosen = false;
  }

  /** \details 
    Creates a new choose feedback item instance with specified parameters.
    
    \param strContents    [in] A new item name.
    \param bChosen        [in] A new choose flag value.
  */
  OdTvFilerFeedbackItemForChoose(OdString strContents, bool bChosen = false)
  {
    m_strName = strContents;
    m_strUniqueName = OD_T("");
    m_bChosen = bChosen;
  }

  /** \details
    Creates a new choose feedback item instance with specified parameters.
    
    \param strContents        [in] A new item name.
    \param strUniqueContents  [in] A new unique item name.
    \param bChosen            [in] A new choose flag value.
  */
  OdTvFilerFeedbackItemForChoose(OdString strContents, OdString strUniqueContents, bool bChosen = false)
  {
    m_strName = strContents;
    m_strUniqueName = strUniqueContents;
    m_bChosen = bChosen;
  }

  /** \details 
    The equality operator for the choose item instance. 
    
    \param object [in] Another choose item instance to be compared with.
    \returns Returns true if the choose item is equal to the other choose item instance specified with the object parameter; otherwise the method returns false.
  */
  bool operator == (const OdTvFilerFeedbackItemForChoose& object) const
  {
    return m_strName == object.m_strName  && m_bChosen == object.m_bChosen && m_strUniqueName == object.m_strUniqueName;
  }

  OdString  m_strName;      // The item name. 
  OdString  m_strUniqueName; // THe unique item name.
  bool      m_bChosen;      // The choose flag.
};

/** \details
  A data type that represents an array of <link OdTvFilerFeedbackItemForChoose, OdTvFilerFeedbackItemForChoose> instances.
*/
typedef OdVector<OdTvFilerFeedbackItemForChoose> OdTvFilerFeedbackItemForChooseArray;


/** \details
  The base interface class that stores all items that should be passed 
  to the filer's callback function for selecting or deselecting.
  \sa
  <link tv_interact_with_file_formats_filers, Work with Visualize Filers>
*/
class ODTV_EXPORT OdTvFilerFeedbackForChooseObject
{
public:

  /** \details
    Creates a new selected item storage object with default parameters.
  */
  OdTvFilerFeedbackForChooseObject();

  /** \details
    Creates a new selected item storage object with a specified caption.
    
    \param strCaption [in] A string that contains the caption.
  */
  OdTvFilerFeedbackForChooseObject(OdString strCaption);

  /** \details
    Retrieves the current item array.
    
    \returns Returns a raw pointer to the item array.
  */
  OdTvFilerFeedbackItemForChooseArray* getFilerFeedbackItemForChooseArrayPtr();

  /** \details
    Retrieves the current object caption.
    
    \returns Returns a string that contains the current caption.
  */
  OdString getCaption() const;

  /** \details
    Searches for a specified item in the storage.
    
    \param item [in] An item to be found.
    \returns Returns true if the specified item was found; otherwise the method returns false.
  */
  bool find(const OdTvFilerFeedbackItemForChoose& item);

//DOM-IGNORE-BEGIN
private:

  OdString                              m_strCaption;
  OdTvFilerFeedbackItemForChooseArray   m_filerFeedbackItemsForChoose;
//DOM-IGNORE-END
};

/** \details
  A data type that represents a pointer to the callback function for chosen items.
*/
typedef void(*OdTvFeedbackForChooseCallback)(OdTvFilerFeedbackForChooseObject&);


/** \details
  The base interface class that display warnings during import the file.
  \sa
  <link tv_interact_with_file_formats_filers, Work with Visualize Filers>
*/
class ODTV_EXPORT OdTvFilerFeedbackForWarning
{
public:

  /** \details
    Creates the warning message storage.
    
    \param displayStr [in] A warning message.
  */
  OdTvFilerFeedbackForWarning(const OdString& displayStr);

  /** \details
    Retrieves the warning message.
    
    \returns Returns a warning message string.
  */
  OdString getDisplayString() const;

  /** \details
    Sets value for abort.
    
    \param bValue [in] An value for abort.
  */
  void setAbort(bool bValue);

  /** \details
    Retrieves the abort value.
    
    \returns Returns abort value.
  */
  bool isAborted() const;

  //DOM-IGNORE-BEGIN
private:
  OdString m_displayStr;
  bool m_bAbort;
  //DOM-IGNORE-END
};

/** \details
  A data type that represents a pointer to the callback function for chosen items.
*/
typedef void(*OdTvFeedbackForWarningCallback)(OdTvFilerFeedbackForWarning&);

/** \details
  The abstract interface class for time profiling results.
  \sa
  <link tv_interact_with_file_formats_filers, Work with Visualize Filers>
*/
class ODTV_EXPORT OdTvFilerTimeProfiling
{
public:
  //DOM-IGNORE-BEGIN
  ODRX_HEAP_OPERATORS();
  //DOM-IGNORE-END

  /** \details 
    Retrieves the time of file loading.
    
    \returns Returns the file loading time in milliseconds.
  */
  virtual OdInt64 getImportTime() const = 0;

  /** \details 
    Retrieves the time of vectorizing.
    
    \returns Returns the vectorizing time in milliseconds.
  */
  virtual OdInt64 getVectorizingTime() const = 0;

  /** \details 
    Retrieves the total time of the operation processed by Visualize SDK.
    
    \returns Returns the total operation time in milliseconds.
  */
  virtual OdInt64 getTvTime() const = 0;

  /** \details
    Retrieves the total time of the CDA tree (and properties cache) creation
    
    \returns Returns the total operation time in milliseconds.
  */
  virtual OdInt64 getCDATreeCreationTime() const = 0;

  /** \details
    Retrieves the misc time.
    
    \returns Returns the misc time in milliseconds.
  */
  virtual OdInt64 getMiscTime() const { return 0; }

  /** \details 
    Sets a new time of the import operation (file loading) processed by Visualize SDK. 
    
    \param time [in] A new value of the import operation time in milliseconds.
  */
  virtual void setImportTime(OdInt64 time) = 0;

  /** \details 
    Sets a new time of the vectorization operation processed by Visualize SDK.
    
    \param time [in] A new value of the vectorization operation time in milliseconds.
  */
  virtual void setVectorizingTime(OdInt64 time) = 0;

  /** \details 
    Sets a new time of the Visualize SDK methods call.
    
    \param time [in] A new value of the call time in milliseconds.
  */
  virtual void setTvTime(OdInt64 time) = 0;

  /** \details
    Sets a new time occupied by the CDA tree (and properties cache) creation
    
    \param time [in] A new value of the call time in milliseconds.
  */
  virtual void setCDATreeCreationTime(OdInt64 time) = 0;

  /** \details
    Sets a new misc time.
    
    \param time [in] A new value of the misc time in milliseconds.
  */
  virtual void setMiscTime(OdInt64 time) {}
};


/** \details
  The abstract interface class for the file load operations for Visualize SDK.
  \sa
  <link tv_interact_with_file_formats_filers, Work with Visualize Filers>
*/
class ODTV_EXPORT OdTvVisualizeFiler
{
public:

  /** \details
    Creates a new Visualize SDK filer object with default parameters.
  */
  OdTvVisualizeFiler() {};

  /** \details
    Destroys the Visualize SDK filer object.
  */
  virtual ~OdTvVisualizeFiler() {}

  /** \details
    Retrieves the current dictionary object that contains properties of the import operation for Visualize SDK.
    
    \returns Returns a smart pointer to the properties dictionary object.
  */
  virtual OdRxDictionaryPtr properties() = 0;

  /** \details
    Loads a Visualize SDK database from a specified file.
    
    \param filePath     [in] A string that contains the path to the file to be read.
    \param pProfileRes  [in] A raw pointer to the time profiling object if it is needed to track operation timing.
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the load operation.
    \returns Returns the loaded Visualize SDK database identifier.
    \remarks 
    If the rc parameter is not null and the database was successfully loaded from the file, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvDatabaseId loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const = 0;

  /** \details
    Loads a Visualize SDK database from a specified data stream buffer.
    
    \param pBuffer      [in] A raw pointer to the data stream to read from.
    \param pProfileRes  [in] A raw pointer to the time profiling object if it is needed to track operation timing.
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the load operation.
    \returns Returns the loaded Visualize SDK database identifier.
    \remarks 
    If the rc parameter is not null and the database was successfully loaded from the data stream, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvDatabaseId loadFrom(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const = 0;

  /** \details
    Loads a Visualize SDK database from a specified database.
    
    \param pDatabase    [in] A raw pointer to the database to load from.
    \param pProfileRes  [in] A raw pointer to the time profiling object if it is needed to track operation timing.
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the load operation.
    \returns Returns the loaded Visualize SDK database identifier.
    \remarks
    If the rc parameter is not null and the database was successfully loaded from the input database, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvDatabaseId loadFrom(OdDbBaseDatabase*  pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const = 0;

  /** \details
    Generates Visualize SDK database content.
    
    \param pProfileRes [in] A raw pointer to the time profiling object if it is needed to track operation timing.
    \returns Returns an identifier of the generated database.
  */
  virtual OdTvDatabaseId generate(OdTvFilerTimeProfiling* pProfileRes = NULL) const = 0;

  /** \details
    Appends new data from a specified file to an existing database.
    
    \param databaseId   [in] An identifier of a database for appending to.
    \param filePath     [in] A string that contains the path to the file to be read.
    \param pProfileRes  [in] A raw pointer to the time profiling object if it is needed to track operation timing.
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the append operation.
    \returns Returns an identifier of the <link OdTvModel, OdTvModel> object that contains the contents of the file after appending.
    \remarks 
    If the rc parameter is not null and the file content was successfully appended to the database, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvModelId appendFrom(const OdTvDatabaseId& databaseId, const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const = 0;

  /** \details
    Appends new data from a specified stream to an existing database.
    
    \param databaseId  [in] An identifier of a database for appending to.
    \param pBuffer     [in] A raw pointer to the stream buffer to be read.
    \param pProfileRes [in] A raw pointer to the time profiling object if it is needed to track operation timing.
    \param rc          [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the append operation.
    \returns Returns an identifier of the <link OdTvModel, OdTvModel> object that contains the contents of the stream after appending.
    \remarks 
    If the rc parameter is not null and the stream content was successfully appended to the database, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
  */
  virtual OdTvModelId appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const = 0;

  /** \details
    Appends new data from a specified database to an existing database.
    
    \param databaseId  [in] An identifier of a database for appending to.
    \param pDatabase   [in] A raw pointer to the database to append from.
    \param pProfileRes [in] A raw pointer to the time profiling object if it is needed to track operation timing.
    \param rc          [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the append operation.
    \returns Returns an identifier of the <link OdTvModel, OdTvModel> object that contains the contents appended from the database.
    \remarks 
    If the rc parameter is not null and the database content was successfully appended to the target database, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
  */
  virtual OdTvModelId appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase*  pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const = 0;

  /** \details
    Returns whether a filer supports the native properties
    
    \returns Returns true if and only if the filer supports the native properties.
  */
  virtual bool hasNativePropertiesSupport() const
  {
    return false;
  }

  /** \details
    Prepares the filer for working with native properties (initializations, loading database).
    
    \param sFilePath  [in] File path to the database.
    \param bPartial   [in] Indicates that the database should be loaded in partial mode (if supported).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the loading native database operation.
    \remarks
    If the filer has been successfully prepared for working with native properties, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult startActionsWithNativeProperties(const OdString& sFilePath, bool bPartial)
  {
    return tvNotImplementedYet;
  }

  /** \details
    Checks whether the filer is already prepared for working with native properties.
    
    \param sFilePath  [in] File path to the database.
    \returns Returns true if and only if the filer supports the native properties.
  */
  virtual bool isActionsWithNativePropertiesStarted(const OdString& sFilePath)
  {
    return false;
  }

  /** \details
    Finalize working with native properties (uninit, unloading the database etc).
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the loading native database operation.
    \remarks
    If the the working with native properties has been successfully finalized, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult endActionsWithNativeProperties()
  {
    return tvNotImplementedYet;
  }

  /** \details
    Gets native properties iterator of the object specified by database handle.
    
    \param dbHandle  [in]  A database handle of object.
    \param rc        [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns <exref target="https://docs.opendesign.com/tkernel/OdRxMemberIteratorPtr.html">OdRxMemberIteratorPtr</exref> which iterates thought native parameters of an object.
    \remarks
    If the rc parameter is not null and the properties iterator was successfully received, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  virtual OdRxMemberIteratorPtr getNativePropertiesIterator(OdUInt64 dbHandle, OdTvResult* rc = NULL)
  {
    if (rc)
      *rc = tvNotImplementedYet;
    return OdRxMemberIteratorPtr();
  }

  /** \details
    Gets a value from the native property of the object specified by database handle.
    
    \param dbHandle   [in] A database handle of the object.
    \param pProperty  [in] A native property of the database object.
    \param bReadOnly  [out] A read only flag. If bReadOnly is not NULL, method will return true if property is read only, false otherwise.
    \param rc         [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a value of <exref target="https://docs.opendesign.com/tkernel/OdRxValue.html">OdRxValue</exref> type that contains data of native property.
    \remarks
    If the rc parameter is not null and the property was successfully received, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  virtual OdRxValue getNativePropertyValue(OdUInt64 dbHandle, const OdRxPropertyPtr& pProperty, bool* bReadOnly = NULL, OdTvResult* rc = NULL)
  {
    if (rc)
      *rc = tvNotImplementedYet;
    return OdRxValue();
  }

  /** \details
    Gets values iterator from the native property with collection type of the object specified by database handle.
    
    \param dbHandle             [in] A database handle of the object.
    \param pCollectionProperty  [in] A native property with collection type of the database object.
    \param bReadOnly            [out] A read only flag. If bReadOnly is not NULL, method will return true if property with collection type is read only, false otherwise.
    \param rc                   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a iterator of <exref target="https://docs.opendesign.com/tkernel/OdRxValueIteratorPtr.html">OdRxValueIteratorPtr</exref> with values of native property with collection type.
    \remarks
    If the rc parameter is not null and the values iterator was successfully received, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  virtual OdRxValueIteratorPtr getNativeCollectionPropertyIterator(OdUInt64 dbHandle, const OdRxCollectionPropertyPtr& pCollectionProperty, bool* bReadOnly = NULL, OdTvResult* rc = NULL)
  {
    if (rc)
      *rc = tvNotImplementedYet;
    return OdRxValueIteratorPtr();
  }

  /** \details
    Sets a value to the native property of the object specified by database handle.
    
    \param dbHandle   [in] A database handle of the object.
    \param pProperty  [in] A native property of the database object.
    \param value      [in] A value to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the filer has been successfully prepared for working with native properties, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setNativePropertyValue(OdUInt64 dbHandle, OdRxPropertyPtr& pProperty, const OdRxValue& value)
  {
    return tvNotImplementedYet;
  }

  /** \details
    Gets a native database.
    
    \param rc                   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a <exref target="https://docs.opendesign.com/tkernel/OdDbBaseDatabase.html">OdDbBaseDatabase</exref> pointer to database.
    \remarks
    If the rc parameter is not null, filer was prepared for working with native properties and the values database was successfully received, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  virtual OdDbBaseDatabase* getNativeDatabase(OdTvResult* rc = NULL) const
  {
    if (rc)
      *rc = tvNotImplementedYet;

    return NULL;
  }
};

/** \details
  A data type that represents a shared smart pointer to an <link OdTvVisualizeFiler, OdTvVisualizeFiler> object.
*/
typedef OdSharedPtr<OdTvVisualizeFiler> OdTvVisualizeFilerPtr;


/** \details
  A data type that represents a map of native properties of an Visualize SDK filer object.
*/
typedef std::map<OdString, OdString>             OdTvNativeProperties;

/** \details
  A data type that represents a map of object properties of an Visualize SDK filer object.
*/
typedef std::map<OdUInt64, OdTvNativeProperties> OdTvObjectsProperties;

/** \details
  A data type that represents a shared smart pointer to a map of object properties of an Visualize SDK filer object.
*/
typedef OdSharedPtr<OdTvObjectsProperties>       OdTvObjectsPropertiesPtr;

/** \details 
  The abstract interface class for loading import properties for Visualize SDK.
*/
class ODTV_EXPORT OdTvImportPropertiesLoader
{
public:

  /** \details
    Creates a new import properties loader object with default parameters.
  */
  virtual ~OdTvImportPropertiesLoader() {}

  /** \details
    Sets a new native Visualize SDK database.
    
    \param nativeDb [in] A raw pointer to the native database.
  */
  virtual void setNativeDatabase(const OdDbBaseDatabase* nativeDb) = 0;

  /** \details
    Sets a new native Visualize SDK database.
    
    \param path [in] A string that contains the full path to the file to load the native database from.
  */
  virtual void setNativeDatabase(const OdString& path) = 0;

  /** \details
    Retrieves all object properties from a specified database.
    
    \param dbId [in] A database identifier.
    \returns Returns a shared smart pointer to a map of all object properties.
  */
  virtual OdTvObjectsPropertiesPtr getAllProperties(const OdTvDatabaseId& dbId) = 0;

  /** \details
    Retrieves all native properties for a specified object.
    
    \param handle [in] An object handle.
    \returns Returns a shared smart pointer to a map of native properties.
  */
  virtual OdTvNativeProperties getProperties(OdUInt64 handle) = 0;
};

/** \details
  A data type that represents a shared smart pointer to an <link OdTvImportPropertiesLoader, OdTvImportPropertiesLoader> object.
*/
typedef OdSharedPtr<OdTvImportPropertiesLoader> OdTvImportPropertiesLoaderPtr;


/** \details
  The abstract interface class for the VisualizeSDK filer module.
  \sa
  <link tv_interact_with_file_formats_filers, Work with Visualize Filers>
*/
class ODTV_EXPORT OdTvVisualizeFilerModule : public OdRxModule
{
public:

  /** \details
    Retrieves the interface for loading or generating Visualize SDK database content.
    
    \returns Returns a shared smart pointer to the Visualize SDK filer interface object.
  */
  virtual OdTvVisualizeFilerPtr getVisualizeFiler() const = 0;

  /** \details
    Retrieves the interface for loading native properties of objects from a Visualize SDK database.
    
    \returns Returns a shared smart pointer to the Visualize SDK native properties loader object.
    \remarks 
    This functionality is not implemented yet.
  */
  virtual OdTvImportPropertiesLoaderPtr getPropertiesLoader() const { throw OdError("Not implemented"); };
};

/** \details
  A data type that represents a smart pointer to an <link OdTvVisualizeFilerModule, OdTvVisualizeFilerModule> object.
*/
typedef OdSmartPtr<OdTvVisualizeFilerModule> OdTvVisualizeFilerModulePtr;

#include "TD_PackPop.h"

#endif // OD_TV_VISUALIZEFILER_H
