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

%include "Kernel_Defines.i"
#define TD_USING(X)

#define OD_TOOLKIT_IMPORT
#define OD_TOOLKIT_EXPORT
#define DBROOT_EXPORT
#define TOOLKIT_EXPORT
#define DBLIB_EXPORT
#define TOOLKIT_EXPORT_STATIC
#define DBIO_EXPORT
#define DBENT_EXPORT
#define DBDIM_EXPORT
#define ODRX_OVERRIDE
#define DBCONSTRAINTS_EXPORT
#define SMDLL_EXPORT
#define ODDGNLS_EXPORT
#define DB3DSOLIDHISTORY_EXPORT
#define MODELDOCOBJ_EXPORT
#define SCENEOE_EXPORT
#define UNDERLAY_EXPORT
#define ASSURFBODYEXPORT
#define OD_DLL_EXPORT
#define WIPEOUT_EXPORTS

#define AC_STRING(name, val) \
//extern TOOLKIT_EXPORT_GLOBAL const OdConstString name;
%include "StdStrings.h"
#undef AC_STRING