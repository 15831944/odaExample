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
#include "TvGeomCollector.h"
#include "TvFilerTimer.h"

#include "VisualizeModelsGenerator.h"
#include "VisualizeModelsGeneratorImpl.h"
#include "VisualizeDebugModelsGeneratorImpl.h"

//***************************************************************************//
// 'OdTvVisualizeSampleModelsFilerProperties' methods implementation
//***************************************************************************//

OdTvVisualizeSampleModelsFilerProperties::OdTvVisualizeSampleModelsFilerProperties() : m_sampleId(0)
{
}

OdRxDictionaryPtr OdTvVisualizeSampleModelsFilerProperties::createObject()
{
  return OdRxObjectImpl<OdTvVisualizeSampleModelsFilerProperties, OdRxDictionary>::createObject();
}

OdTvVisualizeSampleModelsFilerProperties::~OdTvVisualizeSampleModelsFilerProperties()
{
}

ODRX_DECLARE_PROPERTY(SampleID)
ODRX_DECLARE_PROPERTY(ResourceFolder)

ODRX_BEGIN_DYNAMIC_PROPERTY_MAP(OdTvVisualizeSampleModelsFilerProperties);
ODRX_GENERATE_PROPERTY(SampleID)
ODRX_GENERATE_PROPERTY(ResourceFolder)
ODRX_END_DYNAMIC_PROPERTY_MAP(OdTvVisualizeSampleModelsFilerProperties);

ODRX_DEFINE_PROPERTY_METHODS(SampleID, OdTvVisualizeSampleModelsFilerProperties, getSampleID, setSampleID, getUInt16);
ODRX_DEFINE_PROPERTY_METHODS(ResourceFolder, OdTvVisualizeSampleModelsFilerProperties, getResourceFolder, setResourceFolder, getString);


//***************************************************************************//
// 'OdTvVisualizeAcisFiler' methods implementation
//***************************************************************************//

OdTvVisualizeSampleModelsFiler::OdTvVisualizeSampleModelsFiler() : m_properties(OdTvVisualizeSampleModelsFilerProperties::createObject())
{
}

OdTvDatabaseId OdTvVisualizeSampleModelsFiler::loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvDatabaseId tvDbId;

  // does nothing
  return tvDbId;
}

OdTvDatabaseId OdTvVisualizeSampleModelsFiler::loadFrom(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvDatabaseId tvDbId;

  // does nothing
  return tvDbId;
}

OdTvDatabaseId OdTvVisualizeSampleModelsFiler::loadFrom(OdDbBaseDatabase *pDatabase, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvDatabaseId tvDbId;

  // does nothing
  return tvDbId;
}

OdTvDatabaseId OdTvVisualizeSampleModelsFiler::generate(OdTvFilerTimeProfiling* pProfileRes) const
{
  OdTvDatabaseId tvDbId;

  OdTvFactoryId tvFactoryId = odTvGetFactory();
  OdString strResourceFolder = m_properties->getResourceFolder();

  switch (m_properties->getSampleID())
  {
  case 0:
    tvDbId = OdTvVisualizeSampleModels::generateEmptyModel(tvFactoryId);
    break;
  case 1:
    tvDbId = OdTvVisualizeSampleModels::generateSoccerModel(tvFactoryId);
    break;
  case 2:
    tvDbId = OdTvVisualizeSampleModels::generateAllEntitiesModel(tvFactoryId, strResourceFolder);
    break;
  case 3:
    tvDbId = OdTvVisualizeSampleModels::generateCAEModel(tvFactoryId, 0);
    break;
  case 4:
    tvDbId = OdTvVisualizeSampleModels::generateCAEModel(tvFactoryId, 1);
    break;
  case 5:
    tvDbId = OdTvVisualizeSampleModels::generateCAEModel(tvFactoryId, 2);
    break;
  case 6:
    tvDbId = OdTvVisualizeSampleModels::generateMaterialsSampleModel(tvFactoryId, NULL, strResourceFolder, 0);
    break;
  case 7:
    tvDbId = OdTvVisualizeSampleModels::generateMaterialsSampleModel(tvFactoryId, NULL, strResourceFolder, 1);
    break;
  case 8:
    tvDbId = OdTvVisualizeSampleModels::generateMaterialsSampleModel(tvFactoryId, pProfileRes, strResourceFolder, 3);
    break;
  case 9:
    tvDbId = OdTvVisualizeSampleModels::generateMaterialsSampleModel(tvFactoryId, NULL, strResourceFolder, 2);
    break;
  case 10:
    tvDbId = OdTvVisualizeSampleModels::generateMaterialsSampleModel(tvFactoryId, NULL, strResourceFolder, 4);
    break;
  case 11:
    tvDbId = OdTvVisualizeSampleModels::generateMaterialsSampleModel(tvFactoryId, NULL, strResourceFolder, 5);
    break;
  case 1001:
    tvDbId = OdTvViewerDebugSampleModels::generateCircleEllipseModel(tvFactoryId);
    break;
  case 1002:
    tvDbId = OdTvViewerDebugSampleModels::generateLinetypeSampleModel(tvFactoryId);
    break;
  case 1003:
    tvDbId = OdTvViewerDebugSampleModels::generateLayersSampleModel(tvFactoryId);
    break;
  case 1004:
    tvDbId = OdTvViewerDebugSampleModels::generateTransparencySampleModel(tvFactoryId);
    break;
  case 1005:
    tvDbId = OdTvViewerDebugSampleModels::generateLightSampleModel(tvFactoryId);
    break;
  case 1006:
    tvDbId = OdTvViewerDebugSampleModels::generateDebugMaterialsSampleModel(tvFactoryId, strResourceFolder);
    break;
  case 1007:
    tvDbId = OdTvViewerDebugSampleModels::generateShellModel(tvFactoryId, 0);
    break;
  case 1008:
    tvDbId = OdTvViewerDebugSampleModels::generateShellModel(tvFactoryId, 1);
    break;
  case 1009:
    tvDbId = OdTvViewerDebugSampleModels::generate3DGeometryAttributesModel(tvFactoryId, 0);
    break;
  case 1010:
    tvDbId = OdTvViewerDebugSampleModels::generate3DGeometryAttributesModel(tvFactoryId, 1);
    break;
  case 1011:
    tvDbId = OdTvViewerDebugSampleModels::generate3DGeometryAttributesModel(tvFactoryId, 2);
    break;
  case 1012:
    tvDbId = OdTvViewerDebugSampleModels::generateMeshModel(tvFactoryId, 0);
    break;
  case 1013:
    tvDbId = OdTvViewerDebugSampleModels::generateMeshModel(tvFactoryId, 1);
    break;
  case 1014:
    tvDbId = OdTvViewerDebugSampleModels::generateResetAttributesModel(tvFactoryId, 0);
    break;
  case 1015:
    tvDbId = OdTvViewerDebugSampleModels::generateResetAttributesModel(tvFactoryId, 1);
    break;
  case 1016:
    tvDbId = OdTvViewerDebugSampleModels::generateResetAttributesModel(tvFactoryId, 2);
    break;
  case 1017:
    tvDbId = OdTvViewerDebugSampleModels::generateResetAttributesModel(tvFactoryId, 3);
    break;
  case 1018:
    tvDbId = OdTvViewerDebugSampleModels::generateResetAttributesModel(tvFactoryId, 4);
    break;
  case 1019:
    tvDbId = OdTvViewerDebugSampleModels::generateResetAttributesModel(tvFactoryId, 5);
    break;
  case 1020:
    tvDbId = OdTvViewerDebugSampleModels::generateManyCylindersModel(tvFactoryId, 0);
    break;
  case 1021:
    tvDbId = OdTvViewerDebugSampleModels::generateManyCylindersModel(tvFactoryId, 1);
    break;
  case 1022:
    tvDbId = OdTvVisualizeSampleModels::generateProgressiveMeshModel( tvFactoryId, strResourceFolder );
    break;
  case 1023:
    tvDbId = OdTvViewerDebugSampleModels::generateSelectionModel(tvFactoryId);
    break;
  case 1024:
    tvDbId = OdTvViewerDebugSampleModels::generateSelectionModel(tvFactoryId, 1);
    break;
  case 1025:
    tvDbId = OdTvVisualizeSampleModels::generateAnimationSample( tvFactoryId );
    break;
  case 1026:
    tvDbId = OdTvVisualizeSampleModels::generateCameraAnimationSample( tvFactoryId, pProfileRes, strResourceFolder );
    break;
  case 1027:
    tvDbId = OdTvVisualizeSampleModels::generateCameraWalkSample( tvFactoryId, pProfileRes, strResourceFolder );
    break;
  }

  // does nothing
  return tvDbId;
}

OdTvModelId OdTvVisualizeSampleModelsFiler::appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase *pDatabase, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  if (rc)
    *rc = tvNotSupported;

  return OdTvModelId();
}

OdTvModelId OdTvVisualizeSampleModelsFiler::appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  if (rc)
    *rc = tvNotSupported;

  return OdTvModelId();
}

OdTvModelId OdTvVisualizeSampleModelsFiler::appendFrom(const OdTvDatabaseId& databaseId, const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  if (rc)
    *rc = tvNotSupported;

  return OdTvModelId();
}

//***************************************************************************//
// 'OdTvVisualizeSampleModelsFilerModule' methods implementation
//***************************************************************************//

ODRX_DEFINE_DYNAMIC_MODULE(OdTvVisualizeSampleModelsFilerModule);

void OdTvVisualizeSampleModelsFilerModule::initApp()
{
  // initialize the Visualize SDK
  odTvInitialize();
}

void OdTvVisualizeSampleModelsFilerModule::uninitApp()
{
  // Uninitialize the Visualize SDK
  odTvUninitialize();
}

OdTvVisualizeFilerPtr OdTvVisualizeSampleModelsFilerModule::getVisualizeFiler() const
{
  OdTvVisualizeFilerPtr pModelGeneratorFiler = new OdTvVisualizeSampleModelsFiler();

  return pModelGeneratorFiler;
}
