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

#include "TvFactory.h"
#include "Ps2Visualize.h"
#include "TvGeomCollector.h"
#include "TvFilerTimer.h"
#include "TvDatabaseUtils.h"

// Parasolid
#include "PSToolkit/IPSHelper.h"

//Brep
#include "Br/BrBrep.h"  
#include "BrepRenderer/BrepRendererImpl.h"

OdTvVisualizeParasolidFilerProperties::OdTvVisualizeParasolidFilerProperties() : m_defaultColor(ODRGB(191, 191, 191))
{
}

OdRxDictionaryPtr OdTvVisualizeParasolidFilerProperties::createObject()
{
  return OdRxObjectImpl<OdTvVisualizeParasolidFilerProperties, OdRxDictionary>::createObject();
}

OdTvVisualizeParasolidFilerProperties::~OdTvVisualizeParasolidFilerProperties()
{
}

ODRX_DECLARE_PROPERTY(DefaultColor)

ODRX_BEGIN_DYNAMIC_PROPERTY_MAP(OdTvVisualizeParasolidFilerProperties);
ODRX_GENERATE_PROPERTY(DefaultColor)
ODRX_END_DYNAMIC_PROPERTY_MAP(OdTvVisualizeParasolidFilerProperties);

ODRX_DEFINE_PROPERTY_METHODS(DefaultColor, OdTvVisualizeParasolidFilerProperties, getDefaultColor, setDefaultColor, getIntPtr);

void OdTvVisualizeParasolidFilerProperties::setDefaultColor(OdIntPtr ptr)
{
  ODCOLORREF* pColor = (ODCOLORREF*)(ptr);
  if (!pColor)
  {
    ODA_ASSERT(false);
  }
  m_defaultColor = *pColor;
}

OdIntPtr OdTvVisualizeParasolidFilerProperties::getDefaultColor() const
{
  return (OdIntPtr)(&m_defaultColor);
}

//***************************************************************************//
// 'OdTvVisualizeParasolidFiler' methods implementation
//***************************************************************************//

OdTvVisualizeParasolidFiler::OdTvVisualizeParasolidFiler() : m_properties(OdTvVisualizeParasolidFilerProperties::createObject())
{
}

OdTvDatabaseId OdTvVisualizeParasolidFiler::loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvDatabaseId tvDbId;

  if (rc)
    *rc = tvOk;

  // get default color from properties
  ODCOLORREF* pDefColor = (ODCOLORREF*)m_properties->getDefaultColor();
  OdUInt8 r, g, b;
  r = ODGETRED(*pDefColor);
  g = ODGETGREEN(*pDefColor);
  b = ODGETBLUE(*pDefColor);

  //check that time profiling is need
  bool bUseTimeProfiling = false;
  if (pProfileRes)
    bUseTimeProfiling = true;

  //prepare timing object
  OdTvFilerTimer timing(bUseTimeProfiling);
  timing.startTotal();

  OdStreamBufPtr pStreamBuf = odrxSystemServices()->createFile(filePath);
  if (pStreamBuf.isNull())
  {
    if (rc)
      *rc = tvCannotOpenFile;
    return tvDbId;
  }

  //generate model name
  OdString filename = OdTvDatabaseUtils::getFileNameFromPath(filePath);

  // create tv database
  OdTvFactoryId tvFactoryId  = odTvGetFactory();
  tvDbId = tvFactoryId.createDatabase();
  OdTvDatabasePtr pDb = tvDbId.openObject(OdTv::kForWrite);

  // save filename to database user data
  OdTvDatabaseUtils::writeFileNameToTvDatabase(tvDbId, filename);

  //create tv model
  OdTvModelId tvModelId = pDb->createModel(filename);

  //prepare tv model for modifications
  OdTvModelPtr pTvModel = tvModelId.openObject(OdTv::kForWrite);

  OdTvGeomCollector wd(bUseTimeProfiling);
  
  IPSHelper *pHelper = createPSHelper();

  try
  {
    bool bSuccess = false;
    if (pHelper && pStreamBuf->length() != 0)
      bSuccess = pHelper->in(pStreamBuf);

    if (bSuccess)
    {
      timing.startVectorizing();

      OdBrBrep brep;
      brep.set(pHelper->getIBr());

      OdBrepRendererImpl brepRenderer;

      wrTriangulationParams defaultTriangulationParams;
      brepRenderer.setTriangulationParams(&defaultTriangulationParams);

      brepRenderer.setBrep(brep);

      OdTvEntityId entityId = pTvModel->appendEntity();
      entityId.openObject(OdTv::kForWrite)->setColor(OdTvColorDef(r, g, b));

      wd.setTargetDisplayMode(OdTvGeometryData::kRender);
      wd.setTvEntity(entityId);
      brepRenderer.draw(&wd, BrepRenderModes::kShells, 0);

      wd.setTargetDisplayMode(OdTvGeometryData::kWireframe);
      brepRenderer.draw(&wd, BrepRenderModes::kEdges, 0);
      brepRenderer.draw(&wd, BrepRenderModes::kIsolines, 0);

      OdTvDatabaseUtils::createDeviceAndView(tvDbId, tvModelId, OdTvGsView::kWireframe);

      timing.endVectorizing();
    }
  }
  catch (...)
  {
    if (rc)
      *rc = tvInternal;

    timing.endVectorizing();
  }
  
  deletePSHelper(pHelper);

  timing.endTotal();

  if (pProfileRes)
  {
    pProfileRes->setImportTime(OdInt64((timing.getTotalTime() - timing.getVectorizingTime()) * 1000.));
    pProfileRes->setVectorizingTime(OdInt64((timing.getVectorizingTime()) * 1000.));
    pProfileRes->setTvTime(OdInt64(wd.getTotalTime() * 1000.));
  }

  return tvDbId;
}


OdTvDatabaseId OdTvVisualizeParasolidFiler::generate(OdTvFilerTimeProfiling* pProfileRes) const
{
  OdTvDatabaseId tvDbId;
  
  // does nothing
  return tvDbId;
}

OdTvResult OdTvVisualizeParasolidFiler::appendFrom(const OdTvDatabaseId& databaseId, const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes) const
{
  return tvNotImplementedYet;
}

//***************************************************************************//
// 'OdTvVisualizeParasolidFilerModule' methods implementation
//***************************************************************************//

ODRX_DEFINE_DYNAMIC_MODULE(OdTvVisualizeParasolidFilerModule);

void OdTvVisualizeParasolidFilerModule::initApp()
{
  // initialize the Visualize SDK
  odTvInitialize();
}

void OdTvVisualizeParasolidFilerModule::uninitApp()
{
  // Uninitialize the Visualize SDK
  odTvUninitialize();
}

OdTvVisualizeFilerPtr OdTvVisualizeParasolidFilerModule::getVisualizeFiler() const
{
  OdTvVisualizeFilerPtr pPsFiler = new OdTvVisualizeParasolidFiler();

  return pPsFiler;
}

