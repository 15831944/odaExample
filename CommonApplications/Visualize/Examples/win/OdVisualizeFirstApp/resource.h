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
//////////////////////////////////////////////////////////////////////////////

//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by OdVisualizeFirstApp.rc
//
#include <afxres.h>

//#define OD_VISUALIZE_APP_ENABLE_STREAMING 1

#ifndef OD_VISUALIZE_APP_ENABLE_STREAMING

#ifndef OD_VISUALIZE_STREAMING_SHOW_NOTE
#if defined( _DLL )
#define OD_VISUALIZE_STREAMING_SHOW_NOTE 1
#pragma MARKMESSAGE("Visualize note : E. Slupko: Uncomment OD_VISUALIZE_APP_ENABLE_STREAMING to enable VSFX streaming tool.");
#endif
#endif

#else

#if !defined( _DLL )
#pragma MARKMESSAGE("Visualize note : E. Slupko: OD_VISUALIZE_APP_ENABLE_STREAMING is not supported in static build.")
//#undef OD_VISUALIZE_APP_ENABLE_STREAMING
#endif

#endif

//#endif

#define IDC_MYICON                      2
#define IDD_ODVISUALIZEFIRSTAPP_DIALOG  102
#define IDS_APP_TITLE                   103
#define IDD_ABOUTBOX                    103
#define IDM_ABOUT                       104
#define IDM_EXIT                        105
#define IDI_ODVISUALIZEFIRSTAPP         107
#define IDI_SMALL                       108
#define IDC_ODVISUALIZEFIRSTAPP         109
#define IDR_MAINFRAME                   128
#define ID_FILE_GENERATESAMPLE          32771
#define ID_FILE_OPEN_CMD                32772
#define ID_ZOOMTOEXTENTS                32773
#define ID_NAVIGATION_PAN               32774
#define ID_NAVIGATION_ORBIT             32775
#define ID_SAMPLE_MULTIVIEW             32776
#define ID_CHANGEACTIVEVIEW             32777
#define ID_SAMPLE_WALKINGANIMATION      32778
#define ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_1 32779
#define ID_DO_STREAM                    32780
#define ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_2 32781
#define ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_3 32782

#define IDD_DSTREAMING_DIALOG           129
#define IDD_LOG_SETUP_DIALOG            130
#define IDC_FILE_NAME                   1000
#define IDC_FILE_OPEN_VSFX              1001
#define IDC_CHUNKSIZE_EDIT              1002
#define IDC_CHUNKSIZE_COMBO             1003
#define IDC_DOSTREAM_BTN                1004
#define IDC_LOG_LIST                    1005
#define ID_REGENALL_CMD                 1006
#define IDC_DOSTREAM_ALL_BTN            1007
#define IDC_UPDATE_COMBO                1008
#define IDC_PARTIALMODE_CHECK           1009
#define IDC_MEMLIMIT_CHECK              1010
#define IDC_MEMLIMIT_EDIT               1011
#define IDC_SHEDULER_CHECK              1012
#define IDC_SHEDULER_EDIT               1013
#define IDC_UNLOADING_CHECK             1014
#define IDC_LOG_CLEAR_BTN               1015
#define IDC_LOG_SETUP_BTN               1016
#define IDC_LOG_CHECK1                  1017
#define IDC_LOG_CHECK2                  1018
#define IDC_LOG_CHECK3                  1019
#define IDC_LOG_CHECK4                  1020
#define IDC_LOG_CHECK5                  1021
#define IDC_LOG_CHECK6                  1022
#define IDC_LOG_CHECK7                  1023
#define IDC_LOG_CHECKALL_BTN            1024
#define IDC_LOG_UNCHECKALL_BTN          1025
#define ID_UPDATE_CMD                   1026

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NO_MFC                     1
#define _APS_NEXT_RESOURCE_VALUE        129
#define _APS_NEXT_COMMAND_VALUE         32783
#define _APS_NEXT_CONTROL_VALUE         1000
#define _APS_NEXT_SYMED_VALUE           110
#endif
#endif
