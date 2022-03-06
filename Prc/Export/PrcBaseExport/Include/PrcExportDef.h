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


///////////////////////////////////////////////////////////////////////////////
//
// PrcExport.h - Open Design Prc Export definitions
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PRC_EXPORT_DEF_INCLUDED_
#define _PRC_EXPORT_DEF_INCLUDED_

#include "PrcCommon.h"
#include "OdPlatformSettings.h"

#ifdef OdPrcEXPORT_EXPORTS
#define OdPrcEXPORT_DLL           OD_TOOLKIT_EXPORT
#define OdPrcEXPORT_DLL_STATIC    OD_STATIC_EXPORT
#else                           
#define OdPrcEXPORT_DLL           OD_TOOLKIT_IMPORT
#define OdPrcEXPORT_DLL_STATIC    OD_STATIC_IMPORT
#endif

//////////////////////////////////////////////////////////////////////////

#endif // _PRC_EXPORT_DEF_INCLUDED_

