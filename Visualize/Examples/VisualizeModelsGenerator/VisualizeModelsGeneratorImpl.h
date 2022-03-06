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

#ifndef VISUALIZEMODELSGENERATORIMPL_H
#define VISUALIZEMODELSGENERATORIMPL_H

// Visualize SDK
#include "TvFactory.h"

class ODTV_EXPORT OdTvVisualizeSampleModels
{
public:

  static OdTvDatabaseId generateEmptyModel( OdTvFactoryId& id );

  static OdTvDatabaseId generateSoccerModel( OdTvFactoryId& id );

  static OdTvDatabaseId generateAllEntitiesModel( OdTvFactoryId& id, const OdString& strResourceFolder );

  static OdTvDatabaseId generateCAEModel( OdTvFactoryId& id, int type );

  static OdTvDatabaseId generateMaterialsSampleModel(OdTvFactoryId& id, OdTvFilerTimeProfiling* pProfileRes, const OdString& strResourceFolder, int type);

  static OdTvDatabaseId generateProgressiveMeshModel( OdTvFactoryId& id, const OdString& strResourceFolder );

  static OdTvDatabaseId generateAnimationSample( OdTvFactoryId& id );

  static OdTvDatabaseId generateCameraAnimationSample( OdTvFactoryId& id, OdTvFilerTimeProfiling* pProfileRes, const OdString& strResourceFolder );

  static OdTvDatabaseId generateCameraWalkSample( OdTvFactoryId& id, OdTvFilerTimeProfiling* pProfileRes, const OdString& strResourceFolder );

private:

  static void initSoccerFieldModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId);

  static void initAllEntitiesModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId, const OdString& strResourceFolder);

  static void initPlotModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId);

  static void initSurfPlotOtherModel(OdTvDatabaseId& databaseId, OdTvModelId& tvSecondModelId, OdTvModelId& tvThirdModelId);

  static void initSurfPlotModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId);

  static void initCylinderTemperatureModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId, OdTvModelId& tvSecondModelId, OdTvModelId& tvThirdModelId);

  static void initSwordModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId, const OdString& strResourceFolder);

  static void initBallModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId, const OdString& strResourceFolder);

  static void initTeapotModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId, const OdString& strResourceFolder);

  static void initPepcianModel(OdTvDatabaseId& databaseId, OdTvFactoryId& factoryId, OdTvModelId& modelId, OdTvFilerTimeProfiling* pProfileRes, const OdString& strResourceFolder);

  static void initOpacityModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId, const OdString& strResourceFolder);

  static void initBumpModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId, const OdString& strResourceFolder);

  static OdTvDatabaseId importVSF( const OdString& filename, bool bMtMode = false, bool bPartialMode = false, OdTvResult* rc = NULL );

};

#endif //VISUALIZEMODELSGENERATORIMPL_H
