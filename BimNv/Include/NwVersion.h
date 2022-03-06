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


#ifndef TNW_VERSION_DEFINED
#define TNW_VERSION_DEFINED

#ifndef TD_VERSION_DEFINED
  #include "../../KernelBase/Include/TDVersion.h"
#endif

// Full Product version is:
//   TD_MAJOR_VERSION.TD_MINOR_VERSION.TD_MAJOR_BUILD_NUMBER.TD_MINOR_BUILD_NUMBER
// Example: 1.11.00.00 (initial 1.11 release).
// OpenDesign maintenance updates to 1.11 will increase the major build number,
// for example, 1.11.01.00, 1.11.02.00, etc.  Minor build number is reserved for
// client builds.

#define TNW_COMPANY_NAME_S       TD_COMPANY_NAME_S
#define TNW_COMPANY_NAME_W       TD_COMPANY_NAME_W

#define TNW_COPYRIGHT_S          TD_COPYRIGHT_S
#define TNW_COPYRIGHT_W          TD_COPYRIGHT_W
#define TNW_PRODUCT_NAME_END_S   "BimNv SDK"
#define TNW_PRODUCT_NAME_END_W  L"BimNv SDK"

#define TNW_PRODUCT_NAME_S TD_PRODUCT_NAME_START_S " " TNW_PRODUCT_NAME_END_S
#define TNW_PRODUCT_NAME_W TD_PRODUCT_NAME_START_W L" " TNW_PRODUCT_NAME_END_W

#define TNW_MAJOR_VERSION        TD_MAJOR_VERSION
#define TNW_MINOR_VERSION        TD_MINOR_VERSION
#define TNW_TYPELIB_VER(MAJ,MIN) TD_TYPELIB_VER(MAJ,MIN)
#define TNW_MAJOR_BUILD_VERSION  TD_MAJOR_BUILD
#define TNW_MINOR_BUILD_VERSION  TD_MINOR_BUILD

#define TNW_PRODUCT_VER_STR_S    TD_PRODUCT_VER_STR_S	// "3, 6, 0, 0\0"
#define TNW_PRODUCT_VER_STR_W    TD_PRODUCT_VER_STR_W	// L"3, 6, 0, 0\0"

#define TNW_BUILD_COMMENTS_S     TNW_PRODUCT_NAME_S " " TNW_PRODUCT_VER_STR_S
#define TNW_BUILD_COMMENTS_W     TNW_PRODUCT_NAME_W L" " TNW_PRODUCT_VER_STR_W
#define TNW_SHORT_STRING_VER_S   TD_SHORT_STRING_VER_S
#define TNW_SHORT_STRING_VER_W   TD_SHORT_STRING_VER_W


#endif  // TNW_VERSION_DEFINED

