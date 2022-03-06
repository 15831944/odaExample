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

#ifndef PRC_VERSION_DEFINED
#define PRC_VERSION_DEFINED

#ifndef TD_VERSION_DEFINED
#include "../KernelBase/Include/TDVersion.h"
#endif

#define PRC_COMPANY_NAME_S       TD_COMPANY_NAME_S
#define PRC_COMPANY_NAME_W       TD_COMPANY_NAME_W

#define PRC_COPYRIGHT_S          TD_COPYRIGHT_S
#define PRC_PRODUCT_NAME_END_S   "PRC SDK"
#define PRC_PRODUCT_NAME_END_W  L"PRC SDK"

#define PRC_PRODUCT_NAME_S TD_PRODUCT_NAME_START_S  " " PRC_PRODUCT_NAME_END_S
#define PRC_PRODUCT_NAME_W TD_PRODUCT_NAME_START_W L" " PRC_PRODUCT_NAME_END_W

#define PRC_PRODUCT_VER_STR_S    TD_PRODUCT_VER_STR_S
#define PRC_PRODUCT_VER_STR_W    TD_PRODUCT_VER_STR_W

#define PRC_BUILD_COMMENTS_S     PRC_PRODUCT_NAME_S  " " PRC_PRODUCT_VER_STR_S
#define PRC_BUILD_COMMENTS_W     PRC_PRODUCT_NAME_W L" " PRC_PRODUCT_VER_STR_W
#define PRC_SHORT_STRING_VER_S   TD_SHORT_STRING_VER_S
#define PRC_SHORT_STRING_VER_W   TD_SHORT_STRING_VER_W

#endif  // PRC_VERSION_DEFINED

