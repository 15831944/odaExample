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

#ifndef _DAI_SETTINGS_H
#define _DAI_SETTINGS_H

#include "daiBuildOptions.h"
#include "OdHeap.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI
{
  /** \details
    Defines multithreading modes.
  */
  enum class MultithreadingMode
  {
    /** The reading should run in one thread. */
    Single,

    /** The reading should run in multithread 
    with using ODA threadpool functionality. */
    MultiThreadPool,

#if (__cplusplus > 199711L) || (_MSC_VER >= 1700)
    /** The reading should run in multithread
    based on std::thread. */
    MultiThreadStd,
#endif

  };

  /** \details
  Defines deflate level for the compression of the HDF5 files.
  */
  enum class hdf5DeflateLevel
  {
    /**Compression level 0.*/
    Level0 = 0,
    /**Compression level 1.*/
    Level1,
    /**Compression level 2.*/
    Level2,
    /**Compression level 3.*/
    Level3,
    /**Compression level 4.*/
    Level4,
    /**Compression level 5.*/
    Level5,
    /**Compression level 6.*/
    Level6,
    /**Compression level 7.*/
    Level7,
    /**Compression level 8.*/
    Level8,
    /**Compression level 9.*/
    Level9
  };
}

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI 
{
  /** \details
  A class that stores and operates the global settings for some DAI processes. 
  \remarks
  The Settings class is not a thread-safe.
  */
  class DAI_EXPORT Settings
  {
  public:

    /** \details
    Retrieves the current multithreading mode that is used for some DAI operations.
    \returns A <link OdDAI::MultithreadingMode, ultithreadingMode> enumeration values that represents the current multithreading mode.
    \remarks 
    The multithreading mode is applicable to the loading process of Step Physical File or HDF5 files.
    */
    MultithreadingMode get_multiThreadingMode() const;
    
    /** \details
    Sets a new multithreading mode that is using for some DAI operations.
    \param newMode [in] A new multithreading mode represented with a <link OdDAI::Multithreading, Modeenumeration> value.
    */
    void set_multiThreadingMode(MultithreadingMode newMode);
    
    /** \details
    Retrieves the current number of threads that can be run in the multithreading mode.
    \returns A 16-bit signed integer value that represents the current number of threads.
    */
    OdInt16 get_ThreadsCount() const;

    /** \details
    Sets a new number of threads that can be run in the multithreading mode.
    \param threadsCount [in] A new number of threads to be set.
    */
    void set_ThreadsCount(OdInt16 threadsCount);

    /** \details
    Retrieves the current size of a memory block allocated for one thread in the multithreading mode.
    \returns A 16-bit signed integer value that represents the size of the thread memory block in bytes.
    \remarks 
    The multithreading mode is applicable to the loading process of Step Physical File or HDF5 files.
    */
    OdInt16 get_threadsMemBlockSize() const;

    /** \details
    Sets a new size of a memory block allocated for one thread in the multithreading mode.
    \param newBlockSize [in] A 16-bit signed integer value that represents the new size of the thread memory block in bytes.
    */
    void set_threadsMemBlockSize(OdInt16 newBlockSize);

    /** \details
    Retrieves whether the DAI stores type path strings into the type path dictionary of HDF5 files.
    \returns true if the dictionary for type path strings in HDF5 files is used; otherwise, the method returns false.
    \remarks 
    If this flag is equal to true, type path strings of the SELECT data type are stored in a separate dictionary inside an HDF5 file.
    */
    bool get_hdf5useDictionaryTypePath() const;

    /** \details
    Sets the dictionary usage for type path strings in HDF5 files on or off. 
    If this flag is equal to true, type path strings of the SELECT data type are stored in a separate dictionary inside an HDF5 file.
    \param useDictionaryTypePath [in] A dictionary usage flag value. 
    \remarks 
    To set the dictionary usage on pass the true value to the method; to set the dictionary usage off, pass the false.
    */
    void set_hdf5useDictionaryTypePath(bool useDictionaryTypePath);

    /** \details
    Retrieves whether DAI inverse attributes are stored in HDF5 files.
    \returns true if inverse attributes are stored in HDF5 files; otherwise the method returns false.
    */
    bool get_hdf5storeInverseAttributes() const;

    /** \details
    Sets the inverse attributes storage mode for HDF5 files on or off.
    \param storeInverseAttributes [in] An inverse attributes storage flag value. 
    \remarks 
    To set the inverse attribute storage on pass the true value to the method; to set it off, pass the false.
    */
    void set_hdf5storeInverseAttributes(bool storeInverseAttributes);

    /** \details
    Retrieves the current compression deflate level for HDF5 files that is used in the SDAI module.
    \returns A value of the <link OdDAI::hdf5DeflateLevel hdf5DeflateLevel> enumeration that represenets the current deflate level.
    */
    hdf5DeflateLevel get_hdf5deflateLevel() const;

    /** \details
    Sets a new deflate level for the compression in HDF5 files.
    \param deflateLevel [in] A value of the <link OdDAI::hdf5DeflateLevel, hdf5DeflateLevel> enumeration that represents the new deflate level.
    */
    void set_hdf5deflateLevel(hdf5DeflateLevel deflateLevel);

    /** \details
    Retrieves whether committed data types are used for the SDAI module.
    \returns true if committed data types are used for HDF5 files; otherwise, the method returns false.
    \remarks 
    Committed data types can not be used multiple times, so the OdDAI::Schema should be converted to the 
    OdHDF5Schema every time when serializing. Transient types (not committed) can be used multiple times 
    to store models of the same schema, this makes every save operation a bit faster 
    (since no time for the type conversion every time is spent) and allows us to get a smaller HDF5 file. 
    Committed types assume that an HDF5 file contains the SCHEMA_encoding folder with an appropriate schema meta-data.
    */
    bool get_hdf5useCommittedTypes() const;

    /** \details
    Sets a new value of the committed data types usage mode for HDF5 files on or off.
    \param useCommittedTypes [in] A commited data types usage flag value. 
    \remarks 
    To set the usage of committed data types on pass the true value to the method; to set it off, pass the false.
    
    Committed data types can not be used multiple times, so the OdDAI::Schema should be converted to the 
    OdHDF5Schema every time when serializing. Transient types (not committed) can be used multiple times 
    to store models of the same schema, this makes every save operation a bit faster 
    (since no time for the type conversion every time is spent) and allows us to get a smaller HDF5 file. 
    Committed types assume that an HDF5 file contains the SCHEMA_encoding folder with an appropriate schema meta-data.
    */
    void set_hdf5useCommittedTypes(bool useCommittedTypes);

    /** \details
    Retrieves the maximum number of elements of aggregations, which are stored in embedded fields of HDF5 files for the SDAI module.
    \returns The max number of aggregate element values, which are stored in embedded fields.
    */
    OdUInt32 get_hdf5maxEmbededAggr() const;

    /** \details
    Sets the maximum number of elements of aggregations, which are stored in embedded fields of HDF5 files for the SDAI module.
    \param maxEmbededAggr [in] A new value of maximum elements number to be set.
    \remarks 
    When the maximum number of elements is exceeded, aggregation element values are written in a separate dataset.
    */
    void set_hdf5maxEmbededAggr(OdUInt32 maxEmbededAggr);

    /** \details
    Retrieves the current chunk size used in the SDAI module for writing data in HDF5 files.
    \returns An unsigned 32-bit integer value that contains the current chunk size.
    */
    OdUInt32 get_hdf5writeChunkSize() const;

    /** \details
    Sets a new chunk size used in the SDAI module for writing data in HDF5 files.
    \param writeChunkSize[in] A new chunk size value to be set.
    */
    void set_hdf5writeChunkSize(OdUInt32 writeChunkSize);

    /** \details
    Retrieves the current chunk size used in the SDAI module for reading data from HDF5 files.
    \returns An unsigned 32-bit integer value that contains the current chunk size.
    \remarks
    If the chunk size is equal to zero, the entire dataset is read into the memory.
    */
    OdUInt32 get_hdf5readChunkSize() const;

    /** \details
    Sets a new chunk size used in the SDAI module for reading data from HDF5 files.
    \param readChunkSize[in] A new chunk size value to be set.
    */
    void set_hdf5readChunkSize(OdUInt32 readChunkSize);

    /** \details
    Retrieves the current flag that determines whether inverse attributes are calculated after a file load.
    \returns true if inverse attributes are calculated; otherwise, the method returns false.
    */
    bool get_calculateInverseAttributes() const;

    /** \details
    Sets a new value of the flag that determines whether inverse attributes are calculated after a file loading.
    If the flag is equal to true, inverse attributes are calculated; 
    If the flag is equal to false inverse attributes are not calculated.
    \param calculateInverseAttributes [in] A new flag value to be set.
    */
    void set_calculateInverseAttributes(bool calculateInverseAttributes);

    /** \details
    Retrieves the maximum buffer size in bytes for string data type read from a file. 
    Data block that exceeds this size is truncated while reading.
    \returns The maximum string size that can be read from a file in bytes.
    */
    size_t get_stringReadMaxBufferSize();

    /** \details
    Sets a new maximum buffer size for the string data type read from a file. 
    Data block that exceeds this size is truncated while reading.
    \param stringReadMaxBufferSize [in] The new maximum string size in bytes to be set.
    */
    void set_stringReadMaxBufferSize(size_t stringReadMaxBufferSize);

    /** \details
    Retrieves if Time Zone information should be written into time_stamp attribute of file_name
    instance in data section of Step Physical File.
    \returns true if Time Zone information should be written into Step Physical File data section, otherwise returns false.
    */
    bool get_writeTimeZone();

    /** \details
    Sets a new value of the flag that determines if Time Zone information should be written into
    time_stamp attribute of file_name instance in data section of Step Physical File.
    \param writeTimeZone [in] A new flag value to be set.
    */
    void set_writeTimeZone(bool writeTimeZone);

    /** \details
   Retrieves a number of digits for real numbers when they are written to a file.
   \returns Number of digits in a real number. The returned non-positive value indicates that default settings are used.
   */
    OdInt16 get_digitsNumber();

    /** \details
    Sets a number of digits for real numbers when they are written to a file. The passed non-positive value or more than sixteen sets default settings.
    The passed positive value less than three sets the number to three. 
    \param digitsNumber [in] Number of digits in a real number.
    */
    void set_digitsNumber(OdInt16 digitsNumber);

    /** \details
    Retrieves a template for real numbers when they are written to a file.
    \returns Pointer to char with a template for real numbers.
    */
    const char* get_doubleBufferTemplate();

    //DOM-IGNORE-BEGIN
  private:
    friend class SettingsHolder;

    Settings();
    ~Settings();

  private:
    MultithreadingMode  m_multiThreadingMode;
    OdInt16             m_threadsCount;
    OdInt16             m_threadsMemBlockSize;
    bool                m_hdf5useDictionaryTypePath;
    bool                m_hdf5storeInverseAttributes;
    hdf5DeflateLevel    m_hdf5deflateLevel;
    OdUInt32            m_hdf5writeChunkSize;
    OdUInt32            m_hdf5readChunkSize;

    /** \details
    Committed data types can not be used multiple times, so the OdDAI::Schema should be converted to the 
    OdHDF5Schema every time when serializing. Transient types (not committed) can be used multiple times 
    to store models of the same schema, this makes every save operation a bit faster 
    (since no time for the type conversion every time is spent) and allows us to get a smaller HDF5 file. 
    Committed types assume that an HDF5 file contains the SCHEMA_encoding folder with an appropriate schema meta-data.
    */
    bool                m_hdf5useCommittedTypes;

    /** \details
    Max elements of aggregations for store in embedded fields of HDF5 files for SDAI module.
    All aggregations larger than this value will be written as separated data set.
    */
    OdUInt32            m_hdf5maxEmbededAggr;

    bool                m_calculateInverseAttributes;

    size_t              m_stringReadMaxBufferSize;

    size_t              m_stringWriteTruncateSize;

    bool                m_writeTimeZone;

    OdInt16             m_digitsNumber;
    char               m_doubleFormat[10];
    //DOM-IGNORE-END
  };

  /** \details
  Retrieves the global settings for some DAI processes.
  \returns A reference to a <link OdDAI::Settings, Settings> class instance that contains current global settings.
  */
  DAI_EXPORT Settings&  settings();

  //DOM-IGNORE-BEGIN
  void initSettings();
  void uninitSettings();
  //DOM-IGNORE-END
}
#endif // _DAI_HOST_APP_SERVICES_BASE_H
