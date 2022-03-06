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
#include "Dgn2PrcExportModule.h"
#include "RxDictionary.h"
#include "PdfExportGiDrawablePE.h"
#include "Dgn2PrcContextForPdfExportImpl.h"
#include "Dgn2PrcExportGiDrawablePE_Impl.h"
#include "DynamicLinker.h"

//DD:EXPORT_ON
ODRX_DEFINE_DYNAMIC_MODULE(OdDgn2PrcExportModule);
//DD:EXPORT_OFF

static OdStaticRxObject<PdfExportGiDrawablePE_DGN_Default> drwblDftPE;

void OdDgn2PrcExportModule::initApp()
{
  {
    OdRxModulePtr pModule = odrxDynamicLinker()->loadModule(OdPrcBaseExportModuleName);
    if (!pModule.isNull())
    {
      pModule->addRef();
    }
  }

  OdPrcContextForPdfExport_AllInSingleView_DGN::rxInit();
  PdfExportGiDrawablePE_DGN_Default::rxInit();
  OdGiDrawable::desc()->addX(PdfExportGiDrawablePE::desc(), &drwblDftPE);
}

void OdDgn2PrcExportModule::uninitApp()
{
  OdPrcContextForPdfExport_AllInSingleView_DGN::rxUninit();
  OdGiDrawable::desc()->delX(PdfExportGiDrawablePE::desc());
  PdfExportGiDrawablePE_DGN_Default::rxUninit();

  {
    OdRxModulePtr pModule = odrxDynamicLinker()->getModule(OdPrcBaseExportModuleName);
    if (!pModule.isNull())
    {
      pModule->release();
    }
  }
}
