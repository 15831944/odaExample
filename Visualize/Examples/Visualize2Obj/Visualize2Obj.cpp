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

// ODA Platform
#include "OdaCommon.h"
#include "RxDynamicModule.h"
#include "RxVariantValue.h"

// Visualize SDK
#include "TvFactory.h"

//OBJ export
#include "Visualize2Obj.h"
#include "DynamicLinker.h"
#include "TvError.h"
#include "OBJToolkit.h"


//***************************************************************************//
// 'OdTvVisualize2PdfFilerProperties' methods implementation
//***************************************************************************//

OdTvVisualize2ObjExportProperties::OdTvVisualize2ObjExportProperties()
{
}

OdTvVisualize2ObjExportProperties::~OdTvVisualize2ObjExportProperties()
{
}

OdRxDictionaryPtr OdTvVisualize2ObjExportProperties::createObject()
{
  return OdRxObjectImpl<OdTvVisualize2ObjExportProperties, OdRxDictionary>::createObject();
}

ODRX_BEGIN_DYNAMIC_PROPERTY_MAP(OdTvVisualize2ObjExportProperties);
ODRX_END_DYNAMIC_PROPERTY_MAP(OdTvVisualize2ObjExportProperties);


//***************************************************************************//
// 'OdTvVisualize2PdfFiler' methods implementation
//***************************************************************************//

OdTvVisualize2ObjExport::OdTvVisualize2ObjExport()
{
  m_properties = OdTvVisualize2ObjExportProperties::createObject();
}

OdTvResult OdTvVisualize2ObjExport::exportTo(const OdTvDatabaseId& tvDbId, const OdString& fileName) const
{
  OdTvDatabasePtr pTvDb = tvDbId.openObject();
  if (pTvDb.isNull())
    return tvInvalidInput;

  //call method for write the file
  try
  {
    OdDbBaseDatabase* pDb = static_cast<OdDbBaseDatabase*>(pTvDb->getInternalDatabase());
    // try to load pdf export module
    OBJToolkit::OdObjToolkitModulePtr pModule = odrxDynamicLinker()->loadApp(OdObjToolkitModuleName);
    if (pModule.isNull())
      return tvMissingObject;

    OBJToolkit::OdObjExportOptions options;
    options.m_applicationComment = OD_T("ODA Visualize Viewer");
    OdResult res = pModule->exportObj(pDb, fileName, &options);

    pModule.release();
    odrxDynamicLinker()->unloadModule(OdObjToolkitModuleName);
    if (res != eOk)
      return tvErrorDuringExport;
  }
  catch (OdTvError& )
  {
    return tvInternal;
  }

  return tvOk;
}

//***************************************************************************//
// 'OdTvVisualize2PdfFilerModule' methods implementation
//***************************************************************************//

ODRX_DEFINE_DYNAMIC_MODULE(OdTvVisualize2ObjFilerModule);

OdTvVisualizeExportPtr OdTvVisualize2ObjFilerModule::getVisualizeExporter() const
{
  OdTvVisualizeExportPtr pObjExporter = new OdTvVisualize2ObjExport();
  return pObjExporter;
}

void OdTvVisualize2ObjFilerModule::initApp()
{
  // initialize the Visualize SDK
  odTvInitialize();
}

void OdTvVisualize2ObjFilerModule::uninitApp()
{
  // Uninitialize the Visualize SDK
  odTvUninitialize();
}
