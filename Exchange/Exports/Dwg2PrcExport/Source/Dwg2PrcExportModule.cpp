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
#include "Dwg2PrcExportModule.h"
#include "RxDictionary.h"
#include "Dwg2PrcContextForPdfExportImpl.h"
#include "Dwg2PrcExportGiDrawablePE_Impl.h"
#include "Db3dSolid.h"
#include "DbArc.h"
#include "DbRegion.h"
#include "DbSurface.h"
#include "DbBody.h"
#include "DbLine.h"
#include "DbCircle.h"
#include "DbPolyline.h"
#include "DbSpline.h"
#include "DbBlockReference.h"
#include "DbBlockTableRecord.h"
#include "DbObjectIterator.h"
#include "DbLayerTableRecord.h"

//DD:EXPORT_ON
ODRX_DEFINE_DYNAMIC_MODULE(OdDwg2PrcExportModule);
//DD:EXPORT_OFF

//#define PRC_EXPORT_BREP_OLD

static OdStaticRxObject<PdfExportGiDrawablePE_Entity> drwblEntPE;
#ifdef PRC_EXPORT_BREP_OLD
static OdStaticRxObject<PdfExportGiDrawablePE_3dSolid> drwblSldPE;
static OdStaticRxObject<PdfExportGiDrawablePE_Region> drwblRgnPE;
static OdStaticRxObject<PdfExportGiDrawablePE_Surface> drwblSrfPE;
static OdStaticRxObject<PdfExportGiDrawablePE_Body> drwblBdPE;
#endif

static OdStaticRxObject<PdfExportGiDrawablePE_Curve> drwblCrvPE;
static OdStaticRxObject<PdfExportGiDrawablePE_Line> drwblLnPE;
static OdStaticRxObject<PdfExportGiDrawablePE_Circle> drwblClPE;
static OdStaticRxObject<PdfExportGiDrawablePE_Arc> drwblArcPE;
static OdStaticRxObject<PdfExportGiDrawablePE_Polyline> drwblPlPE;
static OdStaticRxObject<PdfExportGiDrawablePE_2dPolyline> drwbl2dPlPE;
static OdStaticRxObject<PdfExportLayerPE_LayerTableRecord> layerPE;


void OdDwg2PrcExportModule::initApp()
{
  {
    OdRxModulePtr pModule = odrxDynamicLinker()->loadModule(OdPrcBaseExportModuleName);
    if (!pModule.isNull())
    {
      pModule->addRef();
    }
  }
  {
    OdRxModulePtr pDbModule = odrxDynamicLinker()->loadModule(OdDbModuleName);
    if (!pDbModule.isNull())
    {
      pDbModule->addRef();
    }
  }

  OdPrcContextForPdfExport_Default::rxInit();
  OdPrcContextForPdfExport_AllInSingleView::rxInit();
  OdPrcContextForPdfExport_OnlySolidsMultiView::rxInit();
  OdPrcContextForPdfExport_OnlySolidsSingleView::rxInit();

  PdfExportLayerPE::rxInit();
  PdfExportLayerPE_LayerTableRecord::rxInit();
  OdDbLayerTableRecord::desc()->addX(PdfExportLayerPE::desc(), &layerPE);
  PdfExportGiDrawablePE_Entity::rxInit();
  OdDbEntity::desc()->addX(PdfExportGiDrawablePE::desc(), &drwblEntPE);
#ifdef PRC_EXPORT_BREP_OLD
  PdfExportGiDrawablePE_Solid_IFace::rxInit();
  PdfExportGiDrawablePE_3dSolid::rxInit();
  OdDb3dSolid::desc()->addX(PdfExportGiDrawablePE::desc(), &drwblSldPE);
  PdfExportGiDrawablePE_Region::rxInit();
  OdDbRegion::desc()->addX(PdfExportGiDrawablePE::desc(), &drwblRgnPE);
  PdfExportGiDrawablePE_Surface::rxInit();
  OdDbSurface::desc()->addX(PdfExportGiDrawablePE::desc(), &drwblSrfPE);
  PdfExportGiDrawablePE_Body::rxInit();
  OdDbBody::desc()->addX(PdfExportGiDrawablePE::desc(), &drwblBdPE);
#endif

  PdfExportGiDrawablePE_Curve::rxInit();
  OdDbCurve::desc()->addX(PdfExportGiDrawablePE::desc(), &drwblCrvPE);
  PdfExportGiDrawablePE_Line::rxInit();
  OdDbLine::desc()->addX(PdfExportGiDrawablePE::desc(), &drwblLnPE);
  PdfExportGiDrawablePE_Circle::rxInit();
  OdDbCircle::desc()->addX(PdfExportGiDrawablePE::desc(), &drwblClPE);
  PdfExportGiDrawablePE_Arc::rxInit();
  OdDbArc::desc()->addX(PdfExportGiDrawablePE::desc(), &drwblArcPE);
  PdfExportGiDrawablePE_Polyline::rxInit();
  OdDbPolyline::desc()->addX(PdfExportGiDrawablePE::desc(), &drwblPlPE);
  PdfExportGiDrawablePE_2dPolyline::rxInit();
  OdDb2dPolyline::desc()->addX(PdfExportGiDrawablePE::desc(), &drwbl2dPlPE);
}

void OdDwg2PrcExportModule::uninitApp()
{
  OdPrcContextForPdfExport_Default::rxUninit();
  OdPrcContextForPdfExport_AllInSingleView::rxUninit();
  OdPrcContextForPdfExport_OnlySolidsMultiView::rxUninit();
  OdPrcContextForPdfExport_OnlySolidsSingleView::rxUninit();
#ifdef PRC_EXPORT_BREP_OLD
  OdDb3dSolid::desc()->delX(PdfExportGiDrawablePE::desc());
  PdfExportGiDrawablePE_3dSolid::rxUninit();
  OdDbRegion::desc()->delX(PdfExportGiDrawablePE::desc());
  PdfExportGiDrawablePE_Region::rxUninit();
  OdDbSurface::desc()->delX(PdfExportGiDrawablePE::desc());
  PdfExportGiDrawablePE_Surface::rxUninit();
  OdDbBody::desc()->delX(PdfExportGiDrawablePE::desc());
  PdfExportGiDrawablePE_Body::rxUninit();
#endif
  OdDbCurve::desc()->delX(PdfExportGiDrawablePE::desc());
  PdfExportGiDrawablePE_Curve::rxUninit();
  OdDbLine::desc()->delX(PdfExportGiDrawablePE::desc());
  PdfExportGiDrawablePE_Line::rxUninit();
  OdDbCircle::desc()->delX(PdfExportGiDrawablePE::desc());
  PdfExportGiDrawablePE_Circle::rxUninit();
  OdDbArc::desc()->delX(PdfExportGiDrawablePE::desc());
  PdfExportGiDrawablePE_Arc::rxUninit();
  OdDbPolyline::desc()->delX(PdfExportGiDrawablePE::desc());
  PdfExportGiDrawablePE_Polyline::rxUninit();
  OdDb2dPolyline::desc()->delX(PdfExportGiDrawablePE::desc());
  PdfExportGiDrawablePE_2dPolyline::rxUninit();

#ifdef PRC_EXPORT_BREP_OLD
  PdfExportGiDrawablePE_Solid_IFace::rxUninit();
#endif
  OdDbEntity::desc()->delX(PdfExportGiDrawablePE::desc());
  PdfExportGiDrawablePE_Entity::rxUninit();
  OdDbLayerTableRecord::desc()->delX(PdfExportLayerPE::desc());
  PdfExportLayerPE_LayerTableRecord::rxUninit();
  PdfExportLayerPE::rxUninit();

  {
    OdRxModulePtr pDbModule = odrxDynamicLinker()->getModule(OdDbModuleName);
    if (!pDbModule.isNull())
    {
      pDbModule->release();
    }
  }
  {
    OdRxModulePtr pModule = odrxDynamicLinker()->getModule(OdPrcBaseExportModuleName);
    if (!pModule.isNull())
    {
      pModule->release();
    }
  }
}
