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

#ifndef _ODTV_DATABASERECEIVER_H_INCLUDED_
#define _ODTV_DATABASERECEIVER_H_INCLUDED_

#include "OdaCommon.h"

#include "Tv.h"
#include "TvIObject.h"
#include "TvDatabase.h"
/** \details
  The abstract interface class for a Visualize SDK database receiver reactor object.
  \remarks
  This object implements streaming Partial Viewing support: it is used to generate request to the server side.
*/
class OdTvDatabaseReceiverReactor
{
public:
  /** \details
    This structure defines request record fields.
  */
  struct OdTvRequestRecord
  {
    /** Offset of the requested bytes data in the original stream. */
    OdUInt64 offset;
    /** Length of the requested bytes data. */
    OdUInt64 length;
  };
  
  /** \details
    This method being called when service part of the database stream are parsed.
    
    \param  bHasPartialIndex [in] Flag that indicates that service section has partial index for all content (modela and blocks).
    \returns Returns true if and only if receiver should be switched to the Partial Mode; otherwise returns false.
    \remarks
    Parsing started from OdTvDatabaseReceiver::doReceive() calls. However, in Partial Mode, after receiving all service data,
    OdTvDatabaseReceiver being switching to the kReceiver_RequestMode state and all other doReceive() calls will be ignored.
    This method notifies about such mode switching.
    If not all content has partial index, Partial Mode still can be enabled, but only indexed objects will be requested.
  */
  virtual bool onServicePartReceived( bool bHasPartialIndex ) = 0;
  
  /** \details
    This method being called to send partial request to the server.
    
    \param requestID [in] ID of request.
    \param nRecCount [in] Number of OdTvRequestRecords in request.
    \param pRecords  [in] Pointer to the OdTvRequestRecords.
  */
  virtual void onRequest( OdUInt32 requestID, OdUInt32 nRecCount, const OdTvRequestRecord* pRecords ) = 0;
  
  /** \details
    This method being called when responce on request are completely parsed.
    
    \param requestID [in] ID of request the response to which has been completely parsed.
  */
  virtual void onRequestResponseParsed( OdUInt32 requestID ) = 0;
  
  /** \details
    This method being called when request are aborted.
    
    \param requestID [in] ID of request that was aborted.
  */
  virtual void onRequestAborted( OdUInt32 requestID ) = 0;
};

class OdTvLimitManager;
/** \details
The class describes streaming partial viewing options.
*/
class ODTV_EXPORT OdTvDatabaseReceiverManagementOptions
{
//DOM-IGNORE-BEGIN
protected:
  //Pointer to instance of the OdTvLimitManager, associated with this database receiver.
  OdTvLimitManager* m_pLimitManager;
  //Memory estimation multiplier.
  double m_memEstMult;
  //Management options flags.
  enum ManagementFlag
  {
    /** Objects unloading flag. */
    kManagement_ObjectsUnloading = 1 << 0,
    /** Statistic gathering flag. */
    kManagement_EnableStatistic = 1 << 1,
    /** Gathter statistic for requests only flag. */
    kManagement_StatisticOnlyRequest = 1 << 2,
    /** Gathter statistic for objects unloading flag. */
    kManagement_StatisticUnloadObjects = 1 << 3
  };
  //Management options flags.
  OdUInt8 m_flags;
  //Objects unloading time limit.
  OdUInt32 m_nUnloadingTimeLimit;
  //Request records count limit.
  OdUInt32 m_nRequestRecordsLimit;
//DOM-IGNORE-END
public:
  /** \details
  Constructs an instance of OdTvDatabaseReceiverManagementOptions.
  */
  OdTvDatabaseReceiverManagementOptions();
  /** \details
  Destructs an instance of OdTvDatabaseReceiverManagementOptions.
  */
  ~OdTvDatabaseReceiverManagementOptions();
  /** \details
  Specifies pointer to the OdTvLimitManager instance.
  \param pManager [in] Pointer to the OdTvLimitManager instance, may be NULL.
  */
  void setLimitManager( OdTvLimitManager* pManager );
  /** \details
  Retrives pointer to the OdTvLimitManager instance that is used during the streaming.
  \returns Returns pointer to the OdTvLimitManager instance.
  */
  OdTvLimitManager* limitManager() const;
  /** \details
  Specifies the memory estimation multiplier.
  \param mult [in] Memory estimation multiplier.
  \remarks
  When limit manager is enabled, receiver trying to estimate is it possible to load object using formula memUsage = <object raw stream size> * multiplier.
  This estimation reduces network load by skipping requests of objects that are impossible to load.
  */
  void setMemoryEstimationMultiplier( double mult );
  /** \details
  Retrives the memory estimation multiplier.
  \returns Returns the memory estimation multiplier.
  */
  double memoryEstimationMultiplier() const;
  /** \details
  Specifies whether receiver should unload out of screen objects or not.
  \param bUnload [in] Flag that indicates should receiver unload out of screen objects or not.
  \param nSchedulerMSec [in] Unloading scheduler limit, may be 0.
  \remarks
  By default receiver unloads all appropriate objects each Update call. However, if unloadTimeLimit is greater than 0,
  it will unload only those objects that will be in time.
  */
  void setObjectsUnloading( bool bUnload, OdUInt32 unloadTimeLimit = 0 );
  /** \details
  Checks whether receiver should unload out of screen objects or not.
  \returns Returns true if and only if receiver should unload out of screen objects; otherwise returns false.
  */
  bool objectsUnloading() const;
  /** \details
  Retrives objects unloading time limit.
  \returns Returns objects unloading time limit.
  */
  OdUInt32 objectsUnloadingTimeLimit() const;
  /** \details
  Specifies whether receiver should gather streaming statistic or not.
  \param bEnable [in]  Flag that indicates should receiver gather streaming statistic or not.
  \param bOnlyRequestedItems [in] Flag that indicates that receiver should gather streaming statistic for requests only.
  \param bCountUnloadObjects [in] Flag that indicates that receiver should gather statistic for objects unloading.
  \remarks
  If bOnlyRequestedItems is false, receiver will gather statistic for both: 
  a) linear streaming of service .VSFX file part 
  b) request-based streaming part (entities, geometries, etc.)
  */
  void setEnableStatistic( bool bEnable, bool bOnlyRequestedItems = true, bool bCountUnloadObjects = false );
  /** \details
  Checks whether receiver should gather streaming statistic or not.
  \returns Returns true if and only if receiver should gather streaming statistic; otherwise returns false.
  */
  bool enableStatistic() const;
  /** \details
  Checks whether receiver should gather streaming statistic for requests only or not.
  \returns Returns true if and only if receiver should gather streaming statistic for requests only; otherwise returns false.
  */
  bool isStatisticOnlyRequestItems() const;
  /** \details
  Checks whether receiver should gather streaming statistic for objects unloading or not.
  \returns Returns true if and only if receiver should gather streaming statistic for objects unloading; otherwise returns false.
  */
  bool isStatisticCountUnloadObjectsItems() const;
  /** \details
  Specifies the maximum of request records count.
  \param nLimit [in] Maximum number of records per request.
  \remarks 
  Some servers can not process huge number of records in single request. 
  If limit is zero, single request will contain all necessary records. 
  Otherwise request will be splitted into few request, each of them will contain not more then specified number of records.
  */
  void setRequestRecordsLimit( OdUInt32 nLimit );
  /** \details
  Retrives the maximum number of records per request.
  \returns Returns the maximum number of records per request.
  */
  OdUInt32 requestRecordsLimit() const;
};

/** \details
  The abstract interface class for a Visualize SDK database receiver object.
  \remarks
  This object implements streaming support: it constructs database from parts of .VSFX file.
*/
class ODTV_EXPORT OdTvDatabaseReceiver : public OdTvIObject
{
public:
  /** \details
    Checks whether the file is streaming-compatible.
    
    \param fileName [in]  Input file name.
    \param pRes     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if file exist and streaming is compatible; otherwise returns false.
    \remarks
    Not streaming-compatible .VSFX file also can be streamed, but efficiency will be very low.
  */
  static bool isStreamingCompatible( const OdString& fileName, OdTvResult* pRes = NULL );
  
  /** \details
    Checks whether the file is streaming-compatible.
    
    \param pBuffer  [in]  Input file stream buffer.
    \param pRes     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if file exist and streaming is compatible; otherwise returns false.
    \remarks
    Not streaming-compatible .VSFX file also can be streamed, but efficiency will be very low.
  */
  static bool isStreamingCompatible( OdStreamBuf* pBuffer, OdTvResult* pRes = NULL );
  
  /** \details
    Checks whether the file contains partial index.
    
    \param fileName [in]  Input file name.
    \param pRes     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if file exists and contains partial index; otherwise returns false.
    \remarks
    .VSFX file without partial index can not be streamed in partial mode.
    If partial index existance is unknown, return value will be false and pRes will be tvWarning.
  */
  static bool hasPartialIndex( const OdString& fileName, OdTvResult* pRes = NULL );
  
  /** \details
    Checks whether the file contains partial index.
    \param pBuffer  [in]  Input file stream buffer.
    \param pRes     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if file exist and contains partial index; otherwise returns false.
    \remarks
    .VSFX file without partial index can not be streamed in partial mode.
    If partial index existance is unknown, return value will be false and pRes will be tvWarning.
  */
  static bool hasPartialIndex( OdStreamBuf* pBuffer, OdTvResult* pRes = NULL );
  
  /** \details
    Checks whether the file is streaming friendly.
    \param fileName [in]  Input file name.
    \param pRes     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if file exist and is streaming friendly; otherwise returns false.
    \remarks
    Not streaming-compatible .VSFX file also can be streamed, but efficiency will be very low.
  */
  static bool isStreamingFriendly( const OdString& fileName, OdTvResult* pRes = NULL );
  
  /** \details
    Checks whether the file is streaming friendly.
    \param pBuffer  [in]  Input file stream buffer.
    \param pRes     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if file exist and is streaming friendly; otherwise returns false.
    \remarks
    Not streaming-compatible .VSFX file also can be streamed, but efficiency will be very low.
  */
  static bool isStreamingFriendly( OdStreamBuf* pBuffer, OdTvResult* pRes = NULL );
  
  /** \details
    Defines streaming-related VSFX stream properties.
  */
  enum VSFXStreamingFlag
  {
    /** VSFX stream is streaming-compatible. */
    k_VSFXStreaming_CompatibleFlag = 1 << 0,
    /** VSFX stream is streaming-friendly. */
    k_VSFXStreaming_FriendlyFlag = 1 << 1,
    /** VSFX stream contains Partial Index. */
    k_VSFXStreaming_HasPartialIndexFlag = 1 << 2
  };
  
  /** \details
    Retrives streaming-related VSFX stream properties from the specified file.
    \param fileName [in]  Input file name.
    \param pRes     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a bit mask of retrived properties.
  */
  static OdUInt8 collectStreamingFlags( const OdString& fileName, OdTvResult* pRes = NULL );
  
  /** \details
    Retrives streaming-related VSFX stream properties from the specified stream.
    \param fileName [in]  Input file stream buffer.
    \param pRes     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a bit mask of retrived properties.
  */
  static OdUInt8 collectStreamingFlags( OdStreamBuf* pBuffer, OdTvResult* pRes = NULL );
  
  /** \details
    Converts specified .VSFX file to streaming-compatible.
    \param input          [in] Input file name.
    \param output         [in] Output file name.
    \param nMaxBufferSize [in] Maximum buffer size.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of operation.
  */
  static OdTvResult makeStreamingCompatible( const OdString& input, const OdString& output, OdUInt32 nMaxBufferSize = 10 * 1024 * 1024 );
  
  /** \details
    Converts specified .VSFX file to streaming-compatible.
    
    \param input          [in] Input file stream buffer.
    \param output         [in] Output file stream buffer.
    \param nMaxBufferSize [in] Maximum buffer size.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of operation.
  */
  static OdTvResult makeStreamingCompatible( OdStreamBuf* pInput, OdStreamBuf* pOutput, OdUInt32 nMaxBufferSize = 10 * 1024 * 1024 );
  
  /** \details
    Defines database receiving state.
  */
  enum DatabaseReceivingState
  {
    /** No data has been received. */
    kReceiver_Nothing = 0,
    /** Receiver awaits service data. */
    kReceiver_AwaitingServiceData,
    /** Receiver awaits objects data. */
    kReceiver_AwaitingObjectsData,
    /** Receiver switched to the request/responce mode */
    kReceiver_RequestMode,
    /** Database completely received. */
    kReceiver_Complete
  };
  
  /** \details
    Retrieves current database receiving state.
    
    \returns Returns current database receiving state.
  */
  virtual DatabaseReceivingState state() const = 0;
  
  /** \details
    Retrieves received database.
    
    \returns Returns received database.
    \remarks
    This method has no sense until receiver reaches kReceiver_AwaitingObjectsData receiving state.
  */
  virtual OdTvDatabaseId database() const = 0;
  
  /** \details
    Receives part of .VSFX file.
    
    \param pData [in] Pointer to the bytes array that contains part of .VSFX file.
    \param nSize [in] Size of receiving bytes array.
    \param rc    [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if database is completely received; otherwise, if database needs more data to be completely received, returns false.
    \remarks
    Database receiver supports only linear streaming. It means that all .VSFX file parts must be received strictly in order, starting from the very first.
  */
  virtual bool doReceive( const OdUInt8* pData, OdUInt32 nSize, OdTvResult* rc = NULL ) = 0;
  
  /** \details
    Resets receiver.
  */
  virtual void reset() = 0;
  
  /** \details
    Retrieves number of objects that database expects to receive.
    
    \returns Returns number of expected objects.
    \remarks
    This method has no sense until receiver reaches kReceiver_AwaitingObjectsData receiving state.
  */
  virtual OdUInt64 numExpectedObjects() const = 0;
  
  /** \details
    Retrieves number of objects that receiver has already received.
    
    \returns Returns number of received objects.
    \remarks
    This method has no sense until receiver reaches kReceiver_AwaitingObjectsData receiving state.
  */
  virtual OdUInt64 numReceivedObjects() const = 0;
  
  /** \details
    Checks whether the input source is streaming-friendly.
    
    \returns Returns true if the input source is streaming-friendly; otherwise returns false.
    \remarks
    In addition to streaming-compatible, streaming-friendly status increases efficiency of streaming.
  */
  virtual bool isStreamingFriendlySource() const = 0;
  
  /** \details
    Checks whether the database can be rendered.
    
    \returns Returns true if the database is render able; otherwise returns false.
    \remarks
    This method has no sense until receiver reaches kReceiver_AwaitingObjectsData receiving state.
    This method has no sense if input source is not streaming-friendly.
    Non-renderable database can be rendered in theory, but it may miss some service data. In this case 
    rendering result differs from the rendering result of complete database and 
    the "Regenerate" command may not fix this.
  */
  virtual bool isDatabaseRenderable() const = 0;
  
  /** \details
    Specifies whether streaming should happens in Partial Mode on not.
    
    \param bEnable  [in] A flag that indicates whether streaming should happens in Partial Viewing Mode on not.
    \param pReactor [in] A pointer to the instance of OdTvDatabaseReceiverReactor that required for the Partial Viewing Mode.
  */
  virtual void enablePartialMode( bool bEnable, OdTvDatabaseReceiverReactor* pReactor ) = 0;
  
  /** \details
    Checks whether streaming should happens in Partial Mode on not.
    
    \returns Returns true if and only if streaming should happens in Partial Mode; otherwise returns false.
  */
  virtual bool isPartialMode() const = 0;
  
  /** \details
    Retrives receiver reactor.
    
    \returns Returns pointer to the instance of OdTvDatabaseReceiverReactor.
  */
  virtual OdTvDatabaseReceiverReactor* partialModeReactor() const = 0;
  
  /** \details
    Receives part of request responce.
    
    \param requestID  [in]  ID of request the part of response to which should be received.
    \param pData      [in]  Part of responce data.
    \param nSize      [in]  Part of responce data length.
    \param pRes       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns                Returns true if part of responce was parsed; otherwise returns false.
    \remarks
    In Partial Viewing Mode, after receiver being switched to the kReceiver_RequestMode state, all ordinary doReceive() calls will be ignored.
    Instead of it doReceiveResponce() method should be used to parce requests responces.
  */
  virtual bool doReceiveResponse( OdUInt32 requestID, const OdUInt8* pData, OdUInt32 nSize, OdTvResult* rc = NULL ) = 0;
  /** \details
  Specifies management options.
  \param options [in] Management options.
  */
  virtual void setManagementOptions( const OdTvDatabaseReceiverManagementOptions& options ) = 0;
  /** \details
  Retrives management options.
  \returns Returns managemant options.
  */
  virtual const OdTvDatabaseReceiverManagementOptions& managementOptions() const = 0;
  /** \details
  The abstract interface class for a Visualize SDK database receiver statistic tool.
  */
  class StatisticTool
  {
  public:
    /** \details
    Retrives number of parsed objects.
    \returns Returns number of parsed objects.
    */
    virtual OdUInt64 numParsedObjects() const = 0;
    /** \details
    Retrives number of unloaded objects.
    \returns Returns number of unloaded objects.
    */
    virtual OdUInt64 numUnloadedObjects() const = 0;
    /** \details
    Retrives total length of parsed objects.
    \returns Returns total length of parsed objects.
    */
    virtual OdUInt64 lengthParsedObjects() const = 0;
    /** \details
    Retrives total length of unloaded objects.
    \returns Returns total length of unloaded objects.
    */
    virtual OdUInt64 lengthUnloadedObjects() const = 0;
    /** \details
    Resets statistic.
    */
    virtual void reset() = 0;
    /** \details
    Checks whether statistic is gathered for the requests only or not.
    \returns Returns true if and only if statistic is gathered for the requests only.
    */
    virtual bool isOnlyRequestedItems() const = 0;
    /** \details
    Specifies whether statistic should be gathered for the requests only or not.
    \param b [in] Flag that indicates should statistic be gathered for the requests only or not.
    */
    virtual void setOnlyRequestedItems( bool b ) = 0;
  };
  /** \details
  Retrives receiver statistic tool.
  \returns Returns pointer to the receiver statistic tool.
  */
  virtual const StatisticTool* statisticTool() const = 0;
  /** \details
  Retrives receiver statistic tool.
  \returns Returns pointer to the receiver statistic tool.
  */
  virtual StatisticTool* statisticTool() = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvDatabaseReceiver, OdTvDatabaseReceiver> object.
*/
typedef OdTvSmartPtr<OdTvDatabaseReceiver> OdTvDatabaseReceiverPtr;

#endif //_ODTV_DATABASERECEIVER_H_INCLUDED_
