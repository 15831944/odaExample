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

// IfcExport.h: interface for the OdIfcExport class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _NV2IFC_EXPORT_H_INCLUDED_
#define _NV2IFC_EXPORT_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OdPlatformSettings.h"
#include "RxModule.h"
#include "Gs/Gs.h"

#include "IfcCore.h"

#ifdef NV2IFC_EXPORTS
  #define NV2IFC_EXPORT          OD_TOOLKIT_EXPORT
  #define NV2IFC_EXPORT_STATIC   OD_STATIC_EXPORT
#else
  #define NV2IFC_EXPORT          OD_TOOLKIT_EXPORT
  #define NV2IFC_EXPORT_STATIC   OD_STATIC_EXPORT
#endif // NV2IFC_EXPORTS

class OdGiDrawable;

namespace NV_IFC_EXPORT
{
  class OdIfcExport : public OdRxObject
  {
  public:
    enum ExportResult { success, fail, bad_password, bad_file, schema_not_supported, bad_database, encrypted_file };

    virtual ExportResult doExport() = 0;
    virtual OdRxDictionaryPtr properties() = 0;
  };
  typedef OdSmartPtr<OdIfcExport> OdIfcExportPtr;

  class OdNv2IfcModule : public OdRxModule
  {
  public:
    virtual OdIfcExportPtr create() = 0;
  };
  typedef OdSmartPtr<OdNv2IfcModule> OdNv2IfcModulePtr;
}


#endif // _NV2IFCEXPORT_H_INCLUDED_

