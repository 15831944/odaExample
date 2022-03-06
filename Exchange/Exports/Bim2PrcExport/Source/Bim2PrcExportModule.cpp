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
#include "BimCommon.h"
#include "StaticRxObject.h"
#include "Bim2PrcExportModule.h"
#include "Bim2PrcContextForPdfExportImpl.h"
#include "Bim2PrcExportGiDrawablePE_Impl.h"
#include "../BimRv/Include/Database/BmElement.h"
#include "Architecture/Entities/BmGrid.h"
#include "Essential/Entities/BmIndependentTag.h"
#include "Database/Entities/BmRefPlane.h"
#include "StairsRamp/Entities/BmBaseRailing.h"
#include "Essential/Entities/BmImportInstance.h"
#include "MEP/Entities/BmFlexCenterLine.h"
#include "Essential/Entities/BmLinearDimString.h"
#include "DynamicLinker.h"

//DD:EXPORT_ON
ODRX_DEFINE_DYNAMIC_MODULE(OdBim2PrcExportModule);
//DD:EXPORT_OFF

static OdStaticRxObject<PdfExportGiDrawablePE_Default> drwblDftPE;
static OdStaticRxObject<PdfExportBmElementPE> bmElementPE;

void OdBim2PrcExportModule::initApp()
{
  {
    OdRxModulePtr pModule = odrxDynamicLinker()->loadModule(OdPrcBaseExportModuleName);
    if (!pModule.isNull())
    {
      pModule->addRef();
    }
  }
  OdPrcContextForPdfExport_AllInSingleView_BIM::rxInit();

  PdfExportBmElementPE::rxInit();
  OdBmElement::desc()->addX(PdfExportGiDrawablePE::desc(), &bmElementPE);

  //bmElementPE shouldn't be used for all OdBmElement:
  OdBmGrid::desc()->addX(PdfExportGiDrawablePE::desc(), &drwblDftPE);
  OdBmRefPlane::desc()->addX(PdfExportGiDrawablePE::desc(), &drwblDftPE);
  OdBmIndependentTag::desc()->addX(PdfExportGiDrawablePE::desc(), &drwblDftPE);
  OdBmLinearDimString::desc()->addX(PdfExportGiDrawablePE::desc(), &drwblDftPE);
  OdBmFlexCenterLine::desc()->addX(PdfExportGiDrawablePE::desc(), &drwblDftPE);
  OdBmBaseRailing::desc()->addX(PdfExportGiDrawablePE::desc(), &drwblDftPE);
}

void OdBim2PrcExportModule::uninitApp()
{
  //bmElementPE shouldn't be used for all OdBmElement:
  OdBmBaseRailing::desc()->delX(PdfExportGiDrawablePE::desc());
  OdBmFlexCenterLine::desc()->delX(PdfExportGiDrawablePE::desc());
  OdBmLinearDimString::desc()->delX(PdfExportGiDrawablePE::desc());
  OdBmIndependentTag::desc()->delX(PdfExportGiDrawablePE::desc());
  OdBmRefPlane::desc()->delX(PdfExportGiDrawablePE::desc());
  OdBmGrid::desc()->delX(PdfExportGiDrawablePE::desc());

  OdBmElement::desc()->delX(PdfExportGiDrawablePE::desc());
  PdfExportBmElementPE::rxUninit();

  OdPrcContextForPdfExport_AllInSingleView_BIM::rxUninit();
  {
    OdRxModulePtr pModule = odrxDynamicLinker()->getModule(OdPrcBaseExportModuleName);
    if (!pModule.isNull())
    {
      pModule->release();
    }
  }
}
