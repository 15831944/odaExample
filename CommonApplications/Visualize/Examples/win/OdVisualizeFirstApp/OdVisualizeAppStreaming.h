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

#ifndef OD_VISUALIZE_APP_STREAMING_H
#define OD_VISUALIZE_APP_STREAMING_H
#include "stdafx.h"
#include "TD_PackPush.h"

#include "OdaCommon.h"
#include "resource.h"

#ifdef OD_VISUALIZE_APP_ENABLE_STREAMING
#include "TvDatabase.h"
#include "TvFactory.h"

#include "TvDatabaseReceiver.h"

class CApplicationBaseRender
{
public:
  virtual bool doRender( OdTvDatabaseId _dbId ) = 0;
  virtual void setupSceneGraphScheduler( OdUInt32 msec ) {}
  virtual void switchScheduler( bool bOn ) {}
  virtual bool isSchedulerOn() const { return false; }

  virtual void setUseSceneGraph( bool bUse ) {};
  virtual bool getUseSceneGraph() const { return true; }
};

class CApplicationLimitManager : public OdTvLimitManager
{
public:
  CApplicationLimitManager();
  virtual ~CApplicationLimitManager();
  virtual OdTvLimitManager::MemoryLimitControlResult checkMemoryUsage( OdUInt8 nReason, OdUInt64 nApproximateMemoryUsage = 0 ) const;
  void setMemoryLimit( OdUInt64 nLimit ) { m_nMemoryLimit = nLimit; }
  OdUInt64 memoryLimit() const { return m_nMemoryLimit; }

  OdUInt64 currentMemoryUsage( bool bMB = false ) const;

  bool isInitialized() const;

protected:
  OdUInt64 m_nMemoryLimit;
  mutable OdMutex m_mutex;
};

class CStreamingDialog : public CDialog
{
public:
  enum { IDD = IDD_DSTREAMING_DIALOG };

  CStreamingDialog( CApplicationBaseRender* pRender );
  ~CStreamingDialog();

  void resetStreaming();

  enum LogHint
  {
    kHint_Important = 1 << 0,
    kHint_StreamingCommon = 1 << 1,
    kHint_Timing = 1 << 2,
    kHint_RequestMode = 1 << 3,
    kHint_MemoryUsage = 1 << 4,
    kHint_Unloading = 1 << 5,

    kHint_Other = 1 << 6
  };

  void logMessage( const OdString& str, LogHint hint );
  OdUInt32 logMask() const { return m_options.commonOptions().logMask; }
  void setLogMask( OdUInt32 nMask ) { m_options.commonOptions().logMask = nMask; }
  void switchLogHint( LogHint hint, bool bEnable )
  {
    SETBIT( m_options.commonOptions().logMask, hint, bEnable );
  }
  bool isLogHintEnabled( LogHint hint ) const { return GETBIT( m_options.commonOptions().logMask, hint ); }

protected:
  class CApplicationStreamingOptions
  {
  public:
    struct CCommonOptions
    {
      OdUInt8 chunkSizeId;
      OdUInt32 chunkSizeBase;
      OdUInt8 updateId;
      OdUInt32 logMask;
    };

    struct CPartialOptions
    {
      enum FlagValue
      {
        kFlag_PartialMode = 1 << 0,
        kFlag_MemoryLimit = 1 << 1,
        kFlag_Sheduler = 1 << 2,
        kFlag_Unloading = 1 << 3
      };
      OdUInt32 flags;
      OdUInt32 nMemLimit;
      OdUInt32 nScheduler;
      bool partialMode() const { return GETBIT( flags, kFlag_PartialMode ); }
      bool memoryLimit() const { return GETBIT( flags, kFlag_MemoryLimit ); }
      bool scheduler() const { return GETBIT( flags, kFlag_Sheduler ); }
      bool objectUnloading() const { return GETBIT( flags, kFlag_Unloading ); }

      void setPartialMode( bool b ) { SETBIT( flags, kFlag_PartialMode, b ); }
      void setMemoryLimit( bool b ) { SETBIT( flags, kFlag_MemoryLimit, b ); }
      void setScheduler( bool b ) { SETBIT( flags, kFlag_Sheduler, b ); }
      void setObjectUnloading( bool b) { SETBIT( flags, kFlag_Unloading, b ); }
    };

    CApplicationStreamingOptions();
    ~CApplicationStreamingOptions();

    CCommonOptions& commonOptions() { return m_commonOpts; }
    const CCommonOptions& commonOptions() const { return m_commonOpts; }

    CPartialOptions& partialOptions() { return m_partialOpts; }
    const CPartialOptions& partialOptions() const { return m_partialOpts; }

    void writeToRegistry();
    void readFromRegistry();

  protected:
    CCommonOptions m_commonOpts;
    CPartialOptions m_partialOpts;
  };

  class CApplicationReactor : public OdTvDatabaseReceiverReactor
  {
  public:
    CApplicationReactor( CStreamingDialog* pDlg );
    ~CApplicationReactor();

    virtual bool onServicePartReceived( bool bHasIndex );
    virtual void onRequest( OdUInt32 requestID, OdUInt32 nRecCount, const OdTvRequestRecord* pRecords );
    virtual void onRequestResponseParsed( OdUInt32 requestID );
    virtual void onRequestAborted( OdUInt32 requestID );
  protected:
    CStreamingDialog* m_pDlg;
  };

  void onFileOpen();
  void onDoStream();
  void onDoStreamAll();
  void onDoStreamRequest( OdUInt64 chunkSize );

  void onPartialCheck();
  void onMemoryLimitCheck();
  void onShedulerCheck();
  void onOnbjectUnloadingCheck();

  void onLogClear();
  void onLogSetup();

  clock_t postProcessReciving();

  void logTiming( clock_t curParse, clock_t curUpdate );

  virtual void OnOK();
protected:
  OdTvDatabaseReceiverPtr m_pDbReceiver;
  OdStreamBufPtr m_pInputStream;
  CApplicationBaseRender* m_pRender;

  clock_t m_totalParseTime;
  clock_t m_totalUpdateTime;
  clock_t m_updateTime;
  clock_t m_updateDelay;

  void updateMemoryLimitUI( bool bEnable, bool bEnableEdit = false );
  bool m_bPartialMode;
  CApplicationReactor* m_pReactor;

  void updateStreamUI( bool bResponce, bool bEnable );

  void enableResponceMode( bool bResponce );

  struct ActiveRequest
  {
    bool m_bHasRequest;
    OdUInt32 m_requestID;
    OdVector< OdTvDatabaseReceiverReactor::OdTvRequestRecord > m_records;
    OdUInt32 m_nCurRecord;
    OdUInt64 m_curOffset;
    OdUInt64 m_maxSize;
    OdUInt64 m_curSize;

    ActiveRequest( OdUInt32 requestID, OdUInt32 nRecCount, const OdTvDatabaseReceiverReactor::OdTvRequestRecord* pRecords )
    {
      m_bHasRequest = true;
      m_requestID = requestID;
      m_records.resize( nRecCount );
      m_maxSize = 0;
      for( OdUInt32 i = 0; i < nRecCount; ++i )
      {
        m_records[ i ] = pRecords[ i ];
        m_maxSize += pRecords[ i ].length;
      }
      m_curSize = 0;
      m_nCurRecord = 0;
      m_curOffset = 0;
    }

    ActiveRequest()
    {
      m_bHasRequest = false;
      m_nCurRecord = 0;
      m_curOffset = 0;
      m_requestID = 0;
      m_maxSize = 0;
      m_curSize = 0;
    }

    bool getResponce( OdUInt64 nMaxSize, OdBinaryData& data, OdStreamBufPtr pStream );
  };

  ActiveRequest m_activeRequest;

  CApplicationLimitManager m_limitManager;
  bool m_bUseMemoryLimit;

  void fillManagementOptions( OdTvDatabaseReceiverManagementOptions& options );

  OdUInt64 m_initialMemUsage;
  bool m_bFirstResponce;

  CApplicationStreamingOptions m_options;
  void collectOptions();
  void applyCommonOptions();
  void applyPartialOptions();

//Additional by-reactor methods
protected:

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};

class CStreamingLogSetupDialog : public CDialog
{
public:
  enum { IDD = IDD_LOG_SETUP_DIALOG };

  CStreamingLogSetupDialog( OdUInt32 nMask );
  ~CStreamingLogSetupDialog();

  virtual void onCheckAll();
  virtual void onUncheckAll();

  OdUInt32 getMask();

  virtual void OnOK();
protected:
  OdUInt32 m_nMask;

  void initByMask( OdUInt32 mask );
  CButton* btnByHint( CStreamingDialog::LogHint hint );

  virtual BOOL OnInitDialog();
  DECLARE_MESSAGE_MAP()
};

#endif

#include "TD_PackPop.h"
#endif //OD_VISUALIZE_APP_STREAMING_H

