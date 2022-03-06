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

#include "OdVisualizeAppStreaming.h"
#include "OdaCommon.h"

#ifdef OD_VISUALIZE_APP_ENABLE_STREAMING
#include "TvDatabase.h"
#include "TvFactory.h"
#include "TvError.h"
#include "TvModuleNames.h"
#include "RxRasterServices.h"
#include "RxVariantValue.h"
#include "DynamicLinker.h"

#include <string>

#include "Core\Include\DbSystemServices.h"

CApplicationLimitManager::CApplicationLimitManager() : m_nMemoryLimit( 0 )
{

}

CApplicationLimitManager::~CApplicationLimitManager()
{

}

OdTvLimitManager::MemoryLimitControlResult CApplicationLimitManager::checkMemoryUsage( OdUInt8 nReason, OdUInt64 nApproximateMemoryUsage ) const
{
  if( m_nMemoryLimit == 0 ) return OdTvLimitManager::kPassed;
  m_mutex.lock();
  OdUInt64 curMem = GetMemoryUsageInternalInfo( 0 );
  m_mutex.unlock();

  if( curMem >= m_nMemoryLimit ) return OdTvLimitManager::kNotPassed;
  if( nApproximateMemoryUsage > 0 )
  {
    if( curMem + nApproximateMemoryUsage >= m_nMemoryLimit ) return OdTvLimitManager::kTryLessSize;
  }
  return OdTvLimitManager::kPassed;
}

bool CApplicationLimitManager::isInitialized() const
{
  return GetMemoryUsageInternalInfo( 0 ) > 0;
}

OdUInt64 CApplicationLimitManager::currentMemoryUsage( bool bMB ) const
{
  if( !bMB )
    return GetMemoryUsageInternalInfo( 0 );
  else
    return GetMemoryUsageInternalInfo( 0 ) / (1024*1024);
}

#define AppRegistryKey _T("Open Design Alliance")

CStreamingDialog::CApplicationStreamingOptions::CApplicationStreamingOptions()
{
  m_commonOpts.chunkSizeId = 0;
  m_commonOpts.chunkSizeBase = 1;
  m_commonOpts.updateId = 0;
  m_commonOpts.logMask = kHint_Important | kHint_StreamingCommon | kHint_Timing | kHint_RequestMode | kHint_MemoryUsage | kHint_Unloading | kHint_Other;

  m_partialOpts.flags = 0;
  m_partialOpts.nMemLimit = 1000;
  m_partialOpts.nScheduler = 500;
}

CStreamingDialog::CApplicationStreamingOptions::~CApplicationStreamingOptions()
{
}

void CStreamingDialog::CApplicationStreamingOptions::writeToRegistry()
{
  HKEY hkey;
  long regOpenResult;
  regOpenResult = RegOpenKeyEx( HKEY_CURRENT_USER, _T( "Software\\" ) AppRegistryKey _T( "\\OdVisualizeFirstApp\\options" ), 0, KEY_ALL_ACCESS, &hkey );
  //  KEY_ALL_ACCESS, &hkey );
  if( regOpenResult != ERROR_SUCCESS )
  {
    regOpenResult = RegCreateKeyEx( HKEY_CURRENT_USER, _T( "Software\\" ) AppRegistryKey _T( "\\OdVisualizeFirstApp\\options" ), 0, NULL, 0, 0, NULL, &hkey, NULL );
    //  KEY_ALL_ACCESS, &hkey );
    if( regOpenResult != ERROR_SUCCESS ) return;
  }
  DWORD val = m_commonOpts.chunkSizeId;
  RegSetValueEx( hkey, OD_T( "chunkSizeId" ), 0, REG_DWORD, (BYTE*)( &val ), sizeof( DWORD ) );
  val = m_commonOpts.chunkSizeBase;
  RegSetValueEx( hkey, OD_T( "chunkSizeBase" ), 0, REG_DWORD, (BYTE*)( &val ), sizeof( DWORD ) );
  val = m_commonOpts.updateId;
  RegSetValueEx( hkey, OD_T( "updateId" ), 0, REG_DWORD, (BYTE*)( &val ), sizeof( DWORD ) );
  val = m_commonOpts.logMask;
  RegSetValueEx( hkey, OD_T( "logMask" ), 0, REG_DWORD, (BYTE*)( &val ), sizeof( DWORD ) );

  val = m_partialOpts.flags;
  RegSetValueEx( hkey, OD_T( "flags" ), 0, REG_DWORD, (BYTE*)( &val ), sizeof( DWORD ) );
  val = m_partialOpts.nMemLimit;
  RegSetValueEx( hkey, OD_T( "nMemLimit" ), 0, REG_DWORD, (BYTE*)( &val ), sizeof( DWORD ) );
  val = m_partialOpts.nScheduler;
  RegSetValueEx( hkey, OD_T( "nScheduler" ), 0, REG_DWORD, (BYTE*)( &val ), sizeof( DWORD ) );

  RegCloseKey( hkey );
}

void CStreamingDialog::CApplicationStreamingOptions::readFromRegistry()
{
  long regOpenResult;
  DWORD sz = sizeof( DWORD );
  DWORD val = 0;
  regOpenResult = RegGetValue( HKEY_CURRENT_USER, _T( "Software\\" ) AppRegistryKey _T( "\\OdVisualizeFirstApp\\options" ), OD_T( "chunkSizeId" ),
    RRF_RT_REG_DWORD, 0, (BYTE*)( &val ), &sz );
  if( regOpenResult == ERROR_SUCCESS ) m_commonOpts.chunkSizeId = (OdUInt8)( val );

  regOpenResult = RegGetValue( HKEY_CURRENT_USER, _T( "Software\\" ) AppRegistryKey _T( "\\OdVisualizeFirstApp\\options" ), OD_T( "chunkSizeBase" ),
    RRF_RT_REG_DWORD, 0, (BYTE*)( &val ), &sz );
  if( regOpenResult == ERROR_SUCCESS ) m_commonOpts.chunkSizeBase = (OdUInt8)( val );

  regOpenResult = RegGetValue( HKEY_CURRENT_USER, _T( "Software\\" ) AppRegistryKey _T( "\\OdVisualizeFirstApp\\options" ), OD_T( "updateId" ),
    RRF_RT_REG_DWORD, 0, (BYTE*)( &val ), &sz );
  if( regOpenResult == ERROR_SUCCESS ) m_commonOpts.updateId = (OdUInt8)( val );

  regOpenResult = RegGetValue( HKEY_CURRENT_USER, _T( "Software\\" ) AppRegistryKey _T( "\\OdVisualizeFirstApp\\options" ), OD_T( "logMask" ),
    RRF_RT_REG_DWORD, 0, (BYTE*)( &val ), &sz );
  if( regOpenResult == ERROR_SUCCESS ) m_commonOpts.logMask = (OdUInt8)( val );

  regOpenResult = RegGetValue( HKEY_CURRENT_USER, _T( "Software\\" ) AppRegistryKey _T( "\\OdVisualizeFirstApp\\options" ), OD_T( "flags" ),
    RRF_RT_REG_DWORD, 0, (BYTE*)( &val ), &sz );
  if( regOpenResult == ERROR_SUCCESS ) m_partialOpts.flags = val;

  regOpenResult = RegGetValue( HKEY_CURRENT_USER, _T( "Software\\" ) AppRegistryKey _T( "\\OdVisualizeFirstApp\\options" ), OD_T( "nMemLimit" ),
    RRF_RT_REG_DWORD, 0, (BYTE*)( &val ), &sz );
  if( regOpenResult == ERROR_SUCCESS ) m_partialOpts.nMemLimit = val;

  regOpenResult = RegGetValue( HKEY_CURRENT_USER, _T( "Software\\" ) AppRegistryKey _T( "\\OdVisualizeFirstApp\\options" ), OD_T( "nScheduler" ),
    RRF_RT_REG_DWORD, 0, (BYTE*)( &val ), &sz );
  if( regOpenResult == ERROR_SUCCESS ) m_partialOpts.nScheduler = val;

}


CStreamingDialog::CStreamingDialog( CApplicationBaseRender* pRender ) : CDialog( CStreamingDialog::IDD )
{
  OdTvFactoryId factId = odTvGetFactory();
  m_pDbReceiver = factId.createDatabaseReceiver();
  m_pRender = pRender;
  m_totalParseTime = 0;
  m_totalUpdateTime = 0;

  m_updateTime = 0;
  m_updateDelay = 0;

  m_bPartialMode = false;
  m_pReactor = NULL;

  m_bUseMemoryLimit = false;

  m_initialMemUsage = 0;
  m_bFirstResponce = true;

  m_options.readFromRegistry();

  m_pRender->setupSceneGraphScheduler( 300 );
}

CStreamingDialog::~CStreamingDialog()
{
  m_pRender->setupSceneGraphScheduler( 0 );
  m_pDbReceiver = OdTvDatabaseReceiverPtr();
  if( m_pReactor ) delete m_pReactor;
}

void CStreamingDialog::OnOK()
{
  //save options
  collectOptions();
  m_options.writeToRegistry();
  m_pDbReceiver->reset();
  CDialog::OnOK();
}

BEGIN_MESSAGE_MAP( CStreamingDialog, CDialog )
	ON_COMMAND( IDC_FILE_OPEN_VSFX, onFileOpen )
  ON_COMMAND( IDC_DOSTREAM_BTN, onDoStream )
  ON_COMMAND( IDC_DOSTREAM_ALL_BTN, onDoStreamAll )

  ON_COMMAND( IDC_PARTIALMODE_CHECK, onPartialCheck )
  ON_COMMAND( IDC_MEMLIMIT_CHECK, onMemoryLimitCheck )
  ON_COMMAND( IDC_SHEDULER_CHECK, onShedulerCheck )
  ON_COMMAND( IDC_UNLOADING_CHECK, onOnbjectUnloadingCheck )

  ON_COMMAND( IDC_LOG_CLEAR_BTN, onLogClear )
  ON_COMMAND( IDC_LOG_SETUP_BTN, onLogSetup )

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaterialsDlg message handlers

BOOL CStreamingDialog::OnInitDialog()
{
  BOOL bRet = CDialog::OnInitDialog();
  
  CComboBox* pCBox = (CComboBox*)( GetDlgItem( IDC_CHUNKSIZE_COMBO ) );
  pCBox->AddString( OD_T( "Bytes" ) );
  pCBox->AddString( OD_T( "KB" ) );
  pCBox->AddString( OD_T( "MB" ) );
  pCBox->AddString( OD_T( "Percent" ) );
  pCBox->SetCurSel( 1 );

  CEdit* pChunkSize = (CEdit*)( GetDlgItem( IDC_CHUNKSIZE_EDIT ) );
  pChunkSize->SetWindowText( OD_T( "60" ) );

  CButton* pBtn = (CButton*)( GetDlgItem( IDC_DOSTREAM_BTN ) );
  pBtn->EnableWindow( FALSE );
  pBtn = (CButton*)( GetDlgItem( IDC_DOSTREAM_ALL_BTN ) );
  pBtn->EnableWindow( FALSE );

  CEdit* pFileNameEdit = (CEdit*)( GetDlgItem( IDC_FILE_NAME ) );
  pFileNameEdit->SetWindowText( OD_T( "None" ) );

  pCBox = (CComboBox*)( GetDlgItem( IDC_UPDATE_COMBO ) );
  pCBox->AddString( OD_T( "Every chunk" ) );
  pCBox->AddString( OD_T( "500 msec" ) );
  pCBox->AddString( OD_T( "1 sec" ) );
  pCBox->AddString( OD_T( "2 sec" ) );
  pCBox->SetCurSel( 0 );

  updateMemoryLimitUI( m_bPartialMode );

  applyCommonOptions();

  return bRet;
}

void CStreamingDialog::onFileOpen()
{
	resetStreaming();
  OPENFILENAME ofn;
  char szFile[ 260 ];

  ZeroMemory( &ofn, sizeof( ofn ) );
  ofn.lStructSize = sizeof( ofn );
  ofn.hwndOwner = ::GetActiveWindow();
  ofn.lpstrFile = (LPWSTR)szFile;
  ofn.lpstrFile[ 0 ] = '\0';
  ofn.nMaxFile = sizeof( szFile );

  ofn.lpstrFilter = L"ODA Extended Visualize Stream Format (*.vsfx)\0*.vsfx\0\0";
  ofn.Flags = OFN_FILEMUSTEXIST;

  if( !GetOpenFileName( &ofn ) )
    return;

  OdString strFileW( ofn.lpstrFile );
  OdUInt8 flgs = OdTvDatabaseReceiver::collectStreamingFlags( strFileW );
  if( !OdTvDatabaseReceiver::isStreamingCompatible( strFileW )  || ( flgs & OdTvDatabaseReceiver::k_VSFXStreaming_CompatibleFlag ) == 0 )
  {
    if( MessageBox( OD_T( "File is not streaming compatible. Convert?" ), OD_T( "Streaming compatible check" ), MB_YESNO ) != IDYES )
    {
      logMessage( OD_T( "Streaming compatible conversion canceled" ), kHint_Important );
      return;
    }
    ZeroMemory( &ofn, sizeof( ofn ) );
    ofn.lStructSize = sizeof( ofn );
    ofn.hwndOwner = ::GetActiveWindow();
    ofn.lpstrFile = (LPWSTR)szFile;
    ofn.lpstrFile[ 0 ] = '\0';
    ofn.nMaxFile = sizeof( szFile );

    ofn.lpstrFilter = L"ODA Extended Visualize Stream Format (*.vsfx)\0*.vsfx\0\0";
    ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT;

    if( !GetSaveFileName( &ofn ) )
      return;

    OdString newFileW( ofn.lpstrFile );
    if( newFileW == strFileW )
    {
      logMessage( OD_T( "Wrong file name" ), kHint_Important );
      return;
    }
    logMessage( OD_T( "Converting " ) + strFileW + OD_T(" to ") + newFileW, kHint_Important );
    OdTvDatabaseReceiver::makeStreamingCompatible( strFileW, newFileW, 1024*1024 );
    strFileW = newFileW;
  }

  m_pInputStream = odTvSystemServices()->createFile( strFileW );
  if( m_pInputStream.isNull() )
  {
    logMessage( OD_T( "Can not open file" ), kHint_Important );
    return;
  }

  CEdit* pFileNameEdit = (CEdit*)( GetDlgItem( IDC_FILE_NAME ) );
  pFileNameEdit->SetWindowText( strFileW );
  CButton* pBtn = (CButton*)( GetDlgItem( IDC_DOSTREAM_BTN ) );
  pBtn->EnableWindow( TRUE );
  pBtn = (CButton*)( GetDlgItem( IDC_DOSTREAM_ALL_BTN ) );
  pBtn->EnableWindow( TRUE );
  logMessage( OD_T( "Prepare streaming of " ) + strFileW, kHint_StreamingCommon );

  applyPartialOptions();
}


void CStreamingDialog::resetStreaming()
{
  m_pInputStream = NULL;
  m_pDbReceiver->reset();
  CButton* pBtn = (CButton*)( GetDlgItem( IDC_DOSTREAM_BTN ) );
  pBtn->EnableWindow( FALSE );
  pBtn = (CButton*)( GetDlgItem( IDC_DOSTREAM_ALL_BTN ) );
  pBtn->EnableWindow( FALSE );
  CEdit* pFileNameEdit = (CEdit*)( GetDlgItem( IDC_FILE_NAME ) );
  pFileNameEdit->SetWindowText( OD_T("None") );
  updateStreamUI( false, true );
  m_bUseMemoryLimit = false;
  pBtn = (CButton*)( GetDlgItem( IDC_MEMLIMIT_CHECK ) );
  pBtn->SetCheck( BST_UNCHECKED );
  updateMemoryLimitUI( m_bPartialMode );
  m_initialMemUsage = 0;
  m_bFirstResponce = true;
}

void CStreamingDialog::logMessage( const OdString& str, LogHint hint )
{
  if( !isLogHintEnabled( hint ) ) return;
  CListBox* pListBox = (CListBox*)( GetDlgItem( IDC_LOG_LIST ) );
  pListBox->AddString( str );
  pListBox->SetTopIndex( pListBox->GetCount() - 1 );
}

void CStreamingDialog::onDoStream()
{
  bool bTakePercent = false;
  CComboBox* pCBox = (CComboBox*)( GetDlgItem( IDC_CHUNKSIZE_COMBO ) );
  OdUInt32 mult = 1;
  if( pCBox->GetCurSel() == 1 ) mult = 1024;
  else if( pCBox->GetCurSel() == 2 ) mult = 1024 * 1024;
  else if( pCBox->GetCurSel() == 3 )
  {
    mult = 1;
    bTakePercent = true;
  }
  updateMemoryLimitUI( false );
  CEdit* pChunkSize = (CEdit*)( GetDlgItem( IDC_CHUNKSIZE_EDIT ) );
  OdString text;
  wchar_t szText[ 260 ];
  pChunkSize->GetWindowText( szText, 260 );
  OdUInt64 chunkSize = wcstol( szText, 0, 10 ) * mult;
  if( bTakePercent )
  {
    if( chunkSize > 100 )
    {
      logMessage( OD_T("INVALID percent chunk size" ), kHint_Important );
      return;
    }
    OdUInt64 sz = m_pInputStream->length();
    chunkSize = ( sz / 100 ) * chunkSize;
  }
  if( chunkSize == 0 ) return;
  if( m_activeRequest.m_bHasRequest )
  {
    onDoStreamRequest( chunkSize );
    return;
  }
  OdString str; str.format( OD_T( "Try to stream %d bytes" ), chunkSize );
  logMessage( str, kHint_StreamingCommon );

  OdUInt64 fullSz = m_pInputStream->length();
  OdUInt64 left = fullSz - m_pInputStream->tell();
  if( left < chunkSize ) chunkSize = left;

  OdBinaryData binData;
  binData.resize( chunkSize );
  m_pInputStream->getBytes( binData.asArrayPtr(), chunkSize );
  clock_t start = clock();
  bool bRet = m_pDbReceiver->doReceive( binData.asArrayPtr(), chunkSize );
  clock_t receiveTime = clock() - start;
  str.format( OD_T( "Sent %d bytes. Current sent is %d of %d (%3.3f percents)" ), chunkSize, m_pInputStream->tell(), fullSz, 100.0 * (double)( m_pInputStream->tell() ) / (double)( fullSz ) );
  logMessage( str, kHint_StreamingCommon );
  if( bRet == true )
  {
    logMessage( OD_T( "Streaming complete" ), kHint_StreamingCommon );
    CButton* pBtn = (CButton*)( GetDlgItem( IDC_DOSTREAM_BTN ) );
    pBtn->EnableWindow( FALSE );
    pBtn = (CButton*)( GetDlgItem( IDC_DOSTREAM_ALL_BTN ) );
    pBtn->EnableWindow( FALSE );
    if( m_pInputStream->tell() == m_pInputStream->length() )
    {
      logMessage( OD_T( "FULL file streamed" ), kHint_StreamingCommon );
    }
    else
    {
      logMessage( OD_T( "INCOMPLETE file streamed" ), kHint_StreamingCommon );
      if( m_bPartialMode )
      {
        if( m_pDbReceiver->state() == OdTvDatabaseReceiver::kReceiver_RequestMode )
        {
          logMessage( OD_T( "Database is in REQUEST MODE" ), kHint_RequestMode );
        }
        else
        {
          logMessage( OD_T( "ERROR: missing request mode" ), kHint_RequestMode );
        }
      }
    }
  }
  clock_t updateTime = postProcessReciving();
  logTiming( receiveTime, updateTime );
  logMessage( OD_T( "" ), kHint_Important );
}

void CStreamingDialog::onDoStreamAll()
{
  if( m_pDbReceiver.isNull() ) return;
  if( m_pInputStream.isNull() ) return;
  updateMemoryLimitUI( false );
  if( m_bPartialMode )
  {
    if( m_pReactor == NULL ) m_pReactor = new CApplicationReactor( this );
    m_pInputStream->rewind();
    OdTvResult rc = tvOk;
    bool bHasPI = OdTvDatabaseReceiver::hasPartialIndex( m_pInputStream, &rc );
    if( rc == tvWarning )
    {
      if( MessageBox( OD_T( "File may not contain Partial Index, disable Partial Mode?" ), OD_T( "Partial Index check" ), MB_YESNO ) == IDYES )
      {
        m_bPartialMode = false;
        delete m_pReactor;
        m_pReactor = NULL;
        logMessage( OD_T( "DISABLED partial mode" ), kHint_Important );
      }
    }
    else if( !bHasPI )
    {
      MessageBox( OD_T( "File do not contain Partial Index, Partial Mode disabled" ), OD_T( "Partial Index check" ), MB_OK );
      m_bPartialMode = false;
      delete m_pReactor;
      m_pReactor = NULL;
      logMessage( OD_T( "DISABLED partial mode" ), kHint_Important );
    }
    else
    {
      logMessage( OD_T( "ENABLED partial mode" ), kHint_RequestMode );
    }
    m_pInputStream->rewind();
  }
  m_pDbReceiver->enablePartialMode( m_bPartialMode, m_pReactor );
  collectOptions();
  OdTvDatabaseReceiverManagementOptions opts;
  fillManagementOptions( opts );
  m_pDbReceiver->setManagementOptions( opts );

  CComboBox* pCBox = (CComboBox*)( GetDlgItem( IDC_UPDATE_COMBO ) );
  if( pCBox )
  {
    switch( pCBox->GetCurSel() )
    {
    case 0: m_updateDelay = 0; break;
    case 1: m_updateDelay = 500; break;
    case 2: m_updateDelay = 1000; break;
    case 3: m_updateDelay = 2000; break;
    default:
      m_updateDelay = 0;
    }
  }
  else
  {
    m_updateDelay = 0;
  }

  OdUInt32 nIter = 0;
  while( m_pDbReceiver->state() != OdTvDatabaseReceiver::kReceiver_Complete ||
         !m_pInputStream->isEof() )
  {
    onDoStream();
    nIter++;
    if( m_pDbReceiver->state() == OdTvDatabaseReceiver::kReceiver_RequestMode )
    {
      logMessage( OD_T( "STOP streaming since state is REQUEST MODE" ), kHint_RequestMode );
      break;
    }
  }
  OdString str;
  str.format( OD_T( "\n\nStreamed by %d iterations") , nIter );
  logMessage( str, kHint_StreamingCommon );
  if( m_updateDelay != 0 )
  {
    //Final update
    clock_t start = clock();
    if( m_pRender ) m_pRender->doRender( m_pDbReceiver->database() );
    clock_t time = clock() - start;
    str.format( OD_T( "Final update in %0.3f sec" ), time / 1000.f );
    m_totalUpdateTime += time;
    logMessage( str, kHint_Timing );
    m_updateDelay = 0;
  }
  str.format( OD_T( "Total time is %0.3f sec" ), ( m_totalParseTime + m_totalUpdateTime ) / 1000.f );
  logMessage( str, kHint_Timing );
}


clock_t CStreamingDialog::postProcessReciving()
{
  //1. Log receiver status
  OdString state = OD_T("UNKNOWN");
  switch( m_pDbReceiver->state() )
  {
  case OdTvDatabaseReceiver::kReceiver_Nothing:
    state = OD_T( "NOTHING" );
    break;
  case OdTvDatabaseReceiver::kReceiver_AwaitingServiceData:
    state = OD_T( "SERVICE STATE" );
    break;
  case OdTvDatabaseReceiver::kReceiver_AwaitingObjectsData:
    state = OD_T( "OBJECTS STATE" );
    break;
  case OdTvDatabaseReceiver::kReceiver_Complete:
    state = OD_T( "COMPLETE" );
    break;
  case OdTvDatabaseReceiver::kReceiver_RequestMode:
    state = OD_T( "REQUEST MODE" );
    break;
  }
  logMessage( OD_T( "Receiver state: " ) + state, kHint_StreamingCommon );

  OdString msg;
  msg.format( OD_T( "Received %d objects of %d" ), m_pDbReceiver->numReceivedObjects(), m_pDbReceiver->numExpectedObjects() );
  logMessage( msg, kHint_StreamingCommon );

  OdTvDatabaseId _dbId = m_pDbReceiver->database();
  if( _dbId.isNull() )
  {
    logMessage( OD_T( "Can not access database" ), kHint_StreamingCommon );
    return 0;
  }
  else
  {
    logMessage( OD_T( "Can access database" ), kHint_StreamingCommon );
  }

  bool isStrFr = m_pDbReceiver->isStreamingFriendlySource();
  bool isDbRender = m_pDbReceiver->isDatabaseRenderable();

  if( isStrFr )
  {
    logMessage( OD_T( "SOURCE is streaming friendly" ), kHint_StreamingCommon );
    if( isDbRender )
    {
      logMessage( OD_T( "DATABASE is RENDER ABLE" ), kHint_StreamingCommon );
    }
    else
    {
      logMessage( OD_T( "DATABASE is not RENDER ABLE" ), kHint_StreamingCommon );
    }
  }
  else
  {
    logMessage( OD_T( "SOURCE is NOT streaming friendly" ), kHint_StreamingCommon );
  }
  if( !isDbRender ) //Look up for details
  {
    OdTvDatabasePtr pDb = _dbId.openObject( OdTv::kForWrite );
    OdTvDevicesIteratorPtr pDevIt = pDb->getDevicesIterator();
    if( pDevIt.isNull() )
    {
      logMessage( OD_T( "Can not access device iterator" ), kHint_StreamingCommon );
      return 0;
    }
    else logMessage( OD_T( "Can access device iterator" ), kHint_StreamingCommon );

    OdTvGsDeviceId devId = pDevIt->getDevice();
    if( devId.isNull() )
    {
      logMessage( OD_T( "Can not access device" ), kHint_StreamingCommon );
      return 0;
    }
    else logMessage( OD_T( "Can access device" ), kHint_StreamingCommon );

    OdTvGsDevicePtr pDevice = devId.openObject( OdTv::kForRead );
    bool allViews = true;
    OdTvResult tvRes = tvOk;
    int nViews = pDevice->numViews( &tvRes );
    if( tvRes != tvOk )
    {
      logMessage( OD_T( "Not all views loaded" ), kHint_StreamingCommon );
      return 0;
    }
    for( int i = 0; i < nViews; ++i )
    {
      if( pDevice->viewAt( i ).isNull() ) allViews = false;
    }

    if( !allViews )
    {
      logMessage( OD_T( "Not all views ready" ), kHint_StreamingCommon );
      return 0;
    }
    else logMessage( OD_T( "All views ready" ), kHint_StreamingCommon );
    return 0;
  }

  if( m_bUseMemoryLimit )
  {
    OdString memStr;
    memStr.format( OD_T( "MEMORY USAGE: %d MB of %d limit" ), m_limitManager.currentMemoryUsage( true ), m_limitManager.memoryLimit() / (1024*1024) );
    logMessage( memStr, kHint_MemoryUsage );
  }

  logMessage( OD_T( "TRY RENDER" ), kHint_StreamingCommon );
  clock_t start = clock();
  if( m_pRender )
  {
    if( m_updateDelay == 0 || clock() - m_updateTime > m_updateDelay )
    {
      m_pRender->doRender( _dbId );
      m_updateTime = clock();
    }
    else
    {
      logMessage( OD_T( "Skipped render by update delay" ), kHint_StreamingCommon );
    }
  }
  return clock() - start;
}

void CStreamingDialog::logTiming( clock_t curParse, clock_t curUpdate )
{
  m_totalParseTime += curParse;
  m_totalUpdateTime += curUpdate;
  OdString str;
  str.format( OD_T( "Parse in %.3f sec (total %.3f sec)" ), (float)curParse / 1000.f, (float)m_totalParseTime / 1000.f );
  logMessage( str, kHint_Timing );
  str.format( OD_T( "Update in %.3f sec (total %.3f sec)" ), (float)curUpdate / 1000.f, (float)m_totalUpdateTime / 1000.f );
  logMessage( str, kHint_Timing );
}

void CStreamingDialog::onPartialCheck()
{
  CButton* btn = (CButton*)( GetDlgItem( IDC_PARTIALMODE_CHECK ) );
  m_bPartialMode = btn->GetCheck() == BST_CHECKED;
  updateMemoryLimitUI( m_bPartialMode );
}

void CStreamingDialog::onMemoryLimitCheck()
{
  CButton* btn = (CButton*)( GetDlgItem( IDC_MEMLIMIT_CHECK ) );
  if( btn->GetCheck() == BST_CHECKED )
  {
    if( !m_limitManager.isInitialized() )
    {
      OdString str = OdString( OD_T( "Limit manager disabled. Try to build VisualizeAlloc according manual in Visualize\\Extentions\\VisualizeAlloc\\VisualizeAlloc.cpp" ) );
      MessageBox( str, OD_T( "Limit Managed disabled" ), MB_OK | MB_ICONERROR );
      btn->SetCheck( BST_UNCHECKED );
      m_bUseMemoryLimit = false;
      updateMemoryLimitUI( m_bPartialMode, m_bUseMemoryLimit );
      return;
    }
    m_bUseMemoryLimit = true;
    updateMemoryLimitUI( m_bPartialMode, m_bUseMemoryLimit );
  }
  else
  {
    m_bUseMemoryLimit = false;
    updateMemoryLimitUI( m_bPartialMode, m_bUseMemoryLimit );
  }
}

void CStreamingDialog::onShedulerCheck()
{
  CButton* btn = (CButton*)( GetDlgItem( IDC_SHEDULER_CHECK ) );
  m_options.partialOptions().setScheduler( btn->GetCheck() == BST_CHECKED );
  CEdit* pEdit = (CEdit*)( GetDlgItem( IDC_SHEDULER_EDIT ) );
  wchar_t szText[ 260 ];
  pEdit->GetWindowText( szText, 260 );
  m_options.partialOptions().nScheduler = wcstol( szText, 0, 10 );
  updateMemoryLimitUI( m_bPartialMode, m_bUseMemoryLimit );
}

void CStreamingDialog::onOnbjectUnloadingCheck()
{
  CButton* btn = (CButton*)( GetDlgItem( IDC_UNLOADING_CHECK ) );
  m_options.partialOptions().setObjectUnloading( btn->GetCheck() == BST_CHECKED );
  updateMemoryLimitUI( m_bPartialMode, m_bUseMemoryLimit );
}

void CStreamingDialog::onLogClear()
{
  CListBox* pListBox = (CListBox*)( GetDlgItem( IDC_LOG_LIST ) );
  pListBox->ResetContent();
}

void CStreamingDialog::onLogSetup()
{
  CStreamingLogSetupDialog dlg( logMask() );
  if( dlg.DoModal() == IDOK )
  {
    setLogMask( dlg.getMask() );
  }
}

void CStreamingDialog::updateMemoryLimitUI( bool bEnable, bool bEnableEdit )
{
  CWnd* pWnd = GetDlgItem( IDC_MEMLIMIT_CHECK );
  pWnd->EnableWindow( bEnable );
  pWnd = GetDlgItem( IDC_MEMLIMIT_EDIT );
  pWnd->EnableWindow( bEnableEdit && bEnable );
  wchar_t szText[ 260 ];
  pWnd->GetWindowText( szText, 260 );
  OdUInt64 limit = wcstol( szText, 0, 10 );
  if( limit == 0 )
    pWnd->SetWindowText( OD_T( "1000" ) );
  pWnd = GetDlgItem( IDC_DOSTREAM_BTN );
  pWnd->EnableWindow( !bEnable );

  pWnd = GetDlgItem( IDC_SHEDULER_EDIT );
  pWnd->EnableWindow( m_options.partialOptions().scheduler() && bEnable );

  pWnd = GetDlgItem( IDC_SHEDULER_CHECK );
  pWnd->EnableWindow( bEnable );

  pWnd = GetDlgItem( IDC_UNLOADING_CHECK );
  pWnd->EnableWindow( bEnable );
}

CStreamingDialog::CApplicationReactor::CApplicationReactor( CStreamingDialog* pDlg )
  :m_pDlg( pDlg )
{

}

CStreamingDialog::CApplicationReactor::~CApplicationReactor()
{

}

bool CStreamingDialog::CApplicationReactor::onServicePartReceived( bool bHasIndex )
{
  m_pDlg->logMessage( OD_T( "onServicePartReceived" ), kHint_RequestMode );
  if( bHasIndex )
  {
    m_pDlg->logMessage( OD_T( "INDEX EXIST, keep partial mode" ), kHint_RequestMode );
  }
  else
  {
    m_pDlg->logMessage( OD_T( "INDEX MISSING, disable partial mode" ), kHint_RequestMode );
  }
  return bHasIndex;
}

void CStreamingDialog::CApplicationReactor::onRequest( OdUInt32 requestID, OdUInt32 nRecCount, const OdTvRequestRecord* pRecords )
{
  OdString msg;
  msg.format( OD_T( "REQUEST %d: %d records" ), requestID, nRecCount );
  m_pDlg->logMessage( msg, kHint_RequestMode );
  OdUInt64 sz = 0;
  for( OdUInt32 i = 0; i < nRecCount; ++i )
  {
    sz += pRecords[ i ].length;
  }
  msg.format( OD_T( "Total requested size %d bytes (%d MB)" ), sz, sz / ( 1024 * 1024 ) );
  m_pDlg->logMessage( msg, kHint_RequestMode );
  m_pDlg->m_activeRequest = ActiveRequest( requestID, nRecCount, pRecords );
  m_pDlg->enableResponceMode( sz > 0 );

  if( m_pDlg->m_options.partialOptions().objectUnloading() )
  {
    const OdTvDatabaseReceiver::StatisticTool* pTool = m_pDlg->m_pDbReceiver->statisticTool();
    if( pTool )
    {
      msg.format( OD_T( "UNLOADED %d objects" ), pTool->numUnloadedObjects() );
      m_pDlg->logMessage( msg, kHint_Unloading );
    }
  }
}

void CStreamingDialog::CApplicationReactor::onRequestResponseParsed( OdUInt32 requestID )
{
  OdString msg;
  msg.format( OD_T( "REQUEST %d PARESED COMPLETELY" ), requestID );
  m_pDlg->logMessage( msg, kHint_RequestMode );
  m_pDlg->m_activeRequest.m_bHasRequest = false;
  m_pDlg->updateStreamUI( true, false );
}

void CStreamingDialog::CApplicationReactor::onRequestAborted( OdUInt32 requestID )
{
  OdString msg;
  msg.format( OD_T( "REQUEST %d ABORTED" ), requestID );
  m_pDlg->logMessage( msg, kHint_RequestMode );
  m_pDlg->m_activeRequest.m_bHasRequest = false;
  m_pDlg->updateStreamUI( true, false );
}

void CStreamingDialog::updateStreamUI( bool bResponce, bool bEnable )
{
  CWnd* pWnd = GetDlgItem( IDC_DOSTREAM_BTN );
  if( !bResponce )
  {
    pWnd->SetWindowText( OD_T( "Do stream" ) );
  }
  else
  {
    pWnd->SetWindowText( OD_T( "Stream responce" ) );
  }
  pWnd->EnableWindow( bEnable );
}

void CStreamingDialog::enableResponceMode( bool bResponce )
{
  updateStreamUI( true, bResponce );
}

bool CStreamingDialog::ActiveRequest::getResponce( OdUInt64 nMaxSize, OdBinaryData& data, OdStreamBufPtr pStream )
{
  data.clear();
  if( !m_bHasRequest ) return true;
  OdUInt64 sz = nMaxSize < ( m_maxSize - m_curSize ) ? nMaxSize : m_maxSize - m_curSize;
  data.resize( sz );
  OdUInt64 curPos = 0;
  while( curPos < sz )
  {
    const OdTvDatabaseReceiverReactor::OdTvRequestRecord& rec = m_records[ m_nCurRecord ];
    OdUInt64 off = rec.offset + m_curOffset;
    pStream->seek( off, OdDb::kSeekFromStart );
    OdUInt64 bytesLeft = sz - curPos;
    OdUInt64 bytesToRead = rec.length - m_curOffset;
    if( bytesToRead <= bytesLeft )
    {
      pStream->getBytes( data.asArrayPtr() + curPos, bytesToRead );
      curPos += bytesToRead;
      m_nCurRecord++;
      m_curOffset = 0;
    }
    else
    {
      pStream->getBytes( data.asArrayPtr() + curPos, bytesLeft );
      curPos += bytesLeft;
      m_curOffset += bytesLeft;
    }
  }
  m_curSize += sz;
  return m_maxSize == m_curSize;
}

void CStreamingDialog::onDoStreamRequest( OdUInt64 chunkSize )
{
  if( m_bFirstResponce )
  {
    m_bFirstResponce = false;
  }
  else if( m_initialMemUsage == 0 && m_bUseMemoryLimit )
  {
    m_initialMemUsage = m_limitManager.currentMemoryUsage();
    OdTvDatabaseReceiver::StatisticTool* pTool = m_pDbReceiver->statisticTool();
    if( pTool ) pTool->reset();
  }
  if( !m_activeRequest.m_bHasRequest ) return;
  OdBinaryData binData;
  if( m_activeRequest.getResponce( chunkSize, binData, m_pInputStream ) )
  {
    m_activeRequest.m_bHasRequest = false;
  }
  OdString msg;
  msg.format( OD_T( "Stream RESPONCE: %d bytes of %d (%d MB), %d left" ), binData.size(), m_activeRequest.m_maxSize, m_activeRequest.m_maxSize / ( 1024 * 1024 ), m_activeRequest.m_maxSize - m_activeRequest.m_curSize );
  logMessage( msg, kHint_RequestMode );
  if( !m_activeRequest.m_bHasRequest )
  {
    logMessage( OD_T("RESPONCE DONE" ), kHint_RequestMode );
    updateStreamUI( true, false );
  }
  if( !m_pDbReceiver->doReceiveResponse( m_activeRequest.m_requestID, binData.asArrayPtr(), binData.size() ) )
  {
    logMessage( OD_T( "ERROR: responce not parsed" ), kHint_Important );
  }
  else
  {
    logMessage( OD_T( "Responce parsed" ), kHint_RequestMode );
  }
  if( m_pRender ) m_pRender->doRender( m_pDbReceiver->database() );

  if( m_bUseMemoryLimit )
  {
    OdString memStr;
    logMessage( OD_T( "AFTER RESPONCE:" ), kHint_RequestMode );
    memStr.format( OD_T( "MEMORY USAGE: %d MB of %d MB limit" ), m_limitManager.currentMemoryUsage( true ), m_limitManager.memoryLimit() / ( 1024 * 1024 ) );
    logMessage( memStr, kHint_MemoryUsage );
    const OdTvDatabaseReceiver::StatisticTool* pTool = m_pDbReceiver->statisticTool();
    if( pTool )
    {
      OdUInt64 memUse = m_limitManager.currentMemoryUsage();
      if( memUse < m_initialMemUsage )
      {
        ODA_ASSERT( m_initialMemUsage == 0 );
        memUse = 0;
      }
      else
      {
        memUse -= m_initialMemUsage;
      }
      OdUInt64 l = pTool->lengthParsedObjects();
      double dVal = 0.0;
      if( l > 0 && m_initialMemUsage != 0 )
      {
        dVal = (double)( memUse ) / (double)( l );
      }
      double rd = (double)( l ) / ( 1024.0 * 1024.0 );
      memStr.format( OD_T( "ESTIMATED MULT: %lf (read %lf MB)" ), dVal, rd );
      logMessage( memStr, kHint_MemoryUsage );
      memStr.format( OD_T( "UNLOADED %d objects" ), pTool->numUnloadedObjects() );
      logMessage( memStr, kHint_Unloading );
    }
  }

  {
    OdString objStr;
    logMessage( OD_T( "AFTER RESPONCE:" ), kHint_RequestMode );
    objStr.format( OD_T( "Received %d of %d objects" ), m_pDbReceiver->numReceivedObjects(), m_pDbReceiver->numExpectedObjects() );
    logMessage( objStr, kHint_RequestMode );
  }
}


void CStreamingDialog::fillManagementOptions( OdTvDatabaseReceiverManagementOptions& options )
{
  if( !m_bPartialMode || !m_bUseMemoryLimit )
  {
    options.setLimitManager( NULL );
    options.setObjectsUnloading( false );
  }
  else
  {
    wchar_t szText[ 260 ];
    CWnd* pWnd = GetDlgItem( IDC_MEMLIMIT_EDIT );
    pWnd->GetWindowText( szText, 260 );
    OdUInt64 limit = wcstol( szText, 0, 10 );
    if( limit == 0 )
    {
      options.setLimitManager( NULL );
      options.setObjectsUnloading( false );
    }
    else
    {
      m_limitManager.setMemoryLimit( limit * 1024 * 1024 );
      options.setLimitManager( &m_limitManager );
      options.setObjectsUnloading( m_options.partialOptions().objectUnloading(), m_options.partialOptions().scheduler() ? m_options.partialOptions().nScheduler : 0 );
      options.setEnableStatistic( true, true, true );
    }
  }
  m_pRender->setUseSceneGraph( !options.objectsUnloading() );
  m_pRender->switchScheduler( !options.objectsUnloading() );
}

void CStreamingDialog::collectOptions()
{
  CComboBox* pCBox = (CComboBox*)( GetDlgItem( IDC_CHUNKSIZE_COMBO ) );
  m_options.commonOptions().chunkSizeId = pCBox->GetCurSel();
  CEdit* pChunkSize = (CEdit*)( GetDlgItem( IDC_CHUNKSIZE_EDIT ) );
  OdString text;
  wchar_t szText[ 260 ];
  pChunkSize->GetWindowText( szText, 260 );
  m_options.commonOptions().chunkSizeBase = wcstol( szText, 0, 10 );
  pCBox = (CComboBox*)( GetDlgItem( IDC_UPDATE_COMBO ) );
  m_options.commonOptions().updateId = pCBox->GetCurSel();

  CButton* btn = (CButton*)( GetDlgItem( IDC_PARTIALMODE_CHECK ) );
  m_options.partialOptions().setPartialMode( btn->GetCheck() == BST_CHECKED );
  
  btn = (CButton*)( GetDlgItem( IDC_MEMLIMIT_CHECK ) );
  m_options.partialOptions().setMemoryLimit( btn->GetCheck() == BST_CHECKED );
  CEdit* pEdit = (CEdit*)( GetDlgItem( IDC_MEMLIMIT_EDIT ) );
  pEdit->GetWindowText( szText, 260 );
  m_options.partialOptions().nMemLimit = (OdUInt32)( wcstol( szText, 0, 10 ) );

  btn = (CButton*)( GetDlgItem( IDC_SHEDULER_CHECK ) );
  m_options.partialOptions().setScheduler( btn->GetCheck() == BST_CHECKED );
  pEdit = (CEdit*)( GetDlgItem( IDC_SHEDULER_EDIT ) );
  pEdit->GetWindowText( szText, 260 );
  m_options.partialOptions().nScheduler = (OdUInt32)( wcstol( szText, 0, 10 ) );

  btn = (CButton*)( GetDlgItem( IDC_UNLOADING_CHECK ) );
  m_options.partialOptions().setObjectUnloading( btn->GetCheck() == BST_CHECKED );
}

void CStreamingDialog::applyCommonOptions()
{
  OdString str;

  CComboBox* pCBox = (CComboBox*)( GetDlgItem( IDC_CHUNKSIZE_COMBO ) );
  pCBox->SetCurSel( m_options.commonOptions().chunkSizeId );
  CEdit* pEdit = (CEdit*)( GetDlgItem( IDC_CHUNKSIZE_EDIT ) );
  str.format( OD_T( "%d" ), m_options.commonOptions().chunkSizeBase );
  pEdit->SetWindowText( str );

  pCBox = (CComboBox*)( GetDlgItem( IDC_UPDATE_COMBO ) );
  pCBox->SetCurSel( m_options.commonOptions().updateId );
}

void CStreamingDialog::applyPartialOptions()
{
  OdString str;
  CButton* btn = (CButton*)( GetDlgItem( IDC_PARTIALMODE_CHECK ) );
  btn->SetCheck( m_options.partialOptions().partialMode() ? BST_CHECKED : BST_UNCHECKED );

  btn = (CButton*)( GetDlgItem( IDC_MEMLIMIT_CHECK ) );
  btn->SetCheck( m_options.partialOptions().memoryLimit() ? BST_CHECKED : BST_UNCHECKED );
  CEdit* pEdit = (CEdit*)( GetDlgItem( IDC_MEMLIMIT_EDIT ) );
  str.format( OD_T( "%d" ), m_options.partialOptions().nMemLimit );
  pEdit->SetWindowText( str );

  btn = (CButton*)( GetDlgItem( IDC_SHEDULER_CHECK ) );
  btn->SetCheck( m_options.partialOptions().scheduler() ? BST_CHECKED : BST_UNCHECKED );
  pEdit = (CEdit*)( GetDlgItem( IDC_SHEDULER_EDIT ) );
  str.format( OD_T( "%d" ), m_options.partialOptions().nScheduler );
  pEdit->SetWindowText( str );

  btn = (CButton*)( GetDlgItem( IDC_UNLOADING_CHECK ) );
  btn->SetCheck( m_options.partialOptions().objectUnloading() ? BST_CHECKED : BST_UNCHECKED );

  onPartialCheck();
  onMemoryLimitCheck();
}

//Log setup dlg
CStreamingLogSetupDialog::CStreamingLogSetupDialog( OdUInt32 nMask ) : CDialog( CStreamingLogSetupDialog::IDD, NULL )
{
  m_nMask = nMask;
}

CStreamingLogSetupDialog::~CStreamingLogSetupDialog()
{
}

void CStreamingLogSetupDialog::initByMask( OdUInt32 mask )
{
  btnByHint( CStreamingDialog::kHint_Important )->SetCheck( GETBIT( mask, CStreamingDialog::kHint_Important ) ? BST_CHECKED : BST_UNCHECKED );
  btnByHint( CStreamingDialog::kHint_StreamingCommon )->SetCheck( GETBIT( mask, CStreamingDialog::kHint_StreamingCommon ) ? BST_CHECKED : BST_UNCHECKED );
  btnByHint( CStreamingDialog::kHint_Timing )->SetCheck( GETBIT( mask, CStreamingDialog::kHint_Timing ) ? BST_CHECKED : BST_UNCHECKED );
  btnByHint( CStreamingDialog::kHint_RequestMode )->SetCheck( GETBIT( mask, CStreamingDialog::kHint_RequestMode ) ? BST_CHECKED : BST_UNCHECKED );
  btnByHint( CStreamingDialog::kHint_MemoryUsage )->SetCheck( GETBIT( mask, CStreamingDialog::kHint_MemoryUsage ) ? BST_CHECKED : BST_UNCHECKED );
  btnByHint( CStreamingDialog::kHint_Unloading )->SetCheck( GETBIT( mask, CStreamingDialog::kHint_Unloading ) ? BST_CHECKED : BST_UNCHECKED );
  btnByHint( CStreamingDialog::kHint_Other )->SetCheck( GETBIT( mask, CStreamingDialog::kHint_Other ) ? BST_CHECKED : BST_UNCHECKED );
}

OdUInt32 CStreamingLogSetupDialog::getMask()
{
  return m_nMask;
}

void CStreamingLogSetupDialog::OnOK()
{
  m_nMask = 0;
  SETBIT( m_nMask, CStreamingDialog::kHint_Important, btnByHint( CStreamingDialog::kHint_Important )->GetCheck() == BST_CHECKED );
  SETBIT( m_nMask, CStreamingDialog::kHint_StreamingCommon, btnByHint( CStreamingDialog::kHint_StreamingCommon )->GetCheck() == BST_CHECKED );
  SETBIT( m_nMask, CStreamingDialog::kHint_Timing, btnByHint( CStreamingDialog::kHint_Timing )->GetCheck() == BST_CHECKED );
  SETBIT( m_nMask, CStreamingDialog::kHint_RequestMode, btnByHint( CStreamingDialog::kHint_RequestMode )->GetCheck() == BST_CHECKED );
  SETBIT( m_nMask, CStreamingDialog::kHint_MemoryUsage, btnByHint( CStreamingDialog::kHint_MemoryUsage )->GetCheck() == BST_CHECKED );
  SETBIT( m_nMask, CStreamingDialog::kHint_Unloading, btnByHint( CStreamingDialog::kHint_Unloading )->GetCheck() == BST_CHECKED );
  SETBIT( m_nMask, CStreamingDialog::kHint_Other, btnByHint( CStreamingDialog::kHint_Other )->GetCheck() == BST_CHECKED );
  CDialog::OnOK();
}

CButton* CStreamingLogSetupDialog::btnByHint( CStreamingDialog::LogHint hint )
{
  CWnd* wnd = NULL;
  switch( hint )
  {
  case CStreamingDialog::kHint_Important:
    wnd = GetDlgItem( IDC_LOG_CHECK1 );
    break;
  case CStreamingDialog::kHint_StreamingCommon:
    wnd = GetDlgItem( IDC_LOG_CHECK2 );
    break;
  case CStreamingDialog::kHint_Timing:
    wnd = GetDlgItem( IDC_LOG_CHECK3 );
    break;
  case CStreamingDialog::kHint_RequestMode:
    wnd = GetDlgItem( IDC_LOG_CHECK4 );
    break;
  case CStreamingDialog::kHint_MemoryUsage:
    wnd = GetDlgItem( IDC_LOG_CHECK5 );
    break;
  case CStreamingDialog::kHint_Unloading:
    wnd = GetDlgItem( IDC_LOG_CHECK6 );
    break;
  case CStreamingDialog::kHint_Other:
    wnd = GetDlgItem( IDC_LOG_CHECK7 );
    break;
  }
  return (CButton*)( wnd );
}

BOOL CStreamingLogSetupDialog::OnInitDialog()
{
  BOOL bRet = CDialog::OnInitDialog();
  initByMask( m_nMask );
  return bRet;
}

void CStreamingLogSetupDialog::onCheckAll()
{
  initByMask( CStreamingDialog::kHint_Important | CStreamingDialog::kHint_StreamingCommon | CStreamingDialog::kHint_Timing | CStreamingDialog::kHint_RequestMode | 
    CStreamingDialog::kHint_MemoryUsage | CStreamingDialog::kHint_Unloading | CStreamingDialog::kHint_Other );
}

void CStreamingLogSetupDialog::onUncheckAll()
{
  initByMask( 0 );
}

BEGIN_MESSAGE_MAP( CStreamingLogSetupDialog, CDialog )
  ON_COMMAND( IDC_LOG_CHECKALL_BTN, onCheckAll )
  ON_COMMAND( IDC_LOG_UNCHECKALL_BTN, onUncheckAll )
END_MESSAGE_MAP()

#endif

