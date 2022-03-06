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

#include "PrcCommon.h"
#include "StaticRxObject.h"
#include "PrcBaseExportModule.h"
#include "PrcExport.h"
#include "PrcExportContext.h"
#include "PdfExportServiceImpl.h"
#include "RxDictionary.h"
#include "PrcBaseContextForPdfExportImpl.h"
#include "PrcBaseExportGiDrawablePE_Default.h"

//DD:EXPORT_ON
ODRX_DEFINE_DYNAMIC_MODULE(OdPrcBaseExportModule);
//DD:EXPORT_OFF

static OdStaticRxObject<PdfExportGiDrawablePE_Default> drwblDftPE;
static OdStaticRxObject<PdfExportServiceInterface_Impl> service;

void OdPrcBaseExportModule::initApp()
{
  OdPrcExportContext::rxInit();

  OdPrcContextForPdfExport::rxInit();
  OdPrcContextForPdfExportWrapper::rxInit();
  OdPrcContextForPdfExport_AllInSingleView_Base::rxInit();

  PdfExportGiDrawablePE::rxInit();
  PdfExportGiDrawablePE_Default::rxInit();
  OdGiDrawable::desc()->addX(PdfExportGiDrawablePE::desc(), &drwblDftPE);

  PdfExportServiceInterface::rxInit();
  PdfExportServiceInterface_Impl::rxInit();
  PdfExportServiceInterface::desc()->addX(PdfExportServiceInterface::desc(), &service);
}

void OdPrcBaseExportModule::uninitApp()
{
  PdfExportServiceInterface::desc()->delX(PdfExportServiceInterface::desc());
  PdfExportServiceInterface_Impl::rxUninit();
  PdfExportServiceInterface::rxUninit();

  OdGiDrawable::desc()->delX(PdfExportGiDrawablePE::desc());
  PdfExportGiDrawablePE_Default::rxUninit();
  PdfExportGiDrawablePE::rxUninit();

  OdPrcContextForPdfExport_AllInSingleView_Base::rxUninit();
  OdPrcContextForPdfExportWrapper::rxUninit();
  OdPrcContextForPdfExport::rxUninit();

  OdPrcExportContext::rxUninit();
}
