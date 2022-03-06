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

#ifndef VISUALIZEDEBUGMODELSGENERATORIMPL_H
#define VISUALIZEDEBUGMODELSGENERATORIMPL_H

// Visualize SDK
#include "TvFactory.h"

class ODTV_EXPORT OdTvViewerDebugSampleModels {
public:

  static OdTvDatabaseId generateCircleEllipseModel(OdTvFactoryId& id);

  static OdTvDatabaseId generateLinetypeSampleModel(OdTvFactoryId& id);

  static OdTvDatabaseId generateLayersSampleModel(OdTvFactoryId& id);

  static OdTvDatabaseId generateTransparencySampleModel(OdTvFactoryId& id);

  static OdTvDatabaseId generateLightSampleModel(OdTvFactoryId& id);

  static OdTvDatabaseId generateDebugMaterialsSampleModel(OdTvFactoryId& id, const OdString& strResourceFolder);

  static OdTvDatabaseId generateShellModel(OdTvFactoryId& id, int type = 0);

  static OdTvDatabaseId generate3DGeometryAttributesModel(OdTvFactoryId& id, int type = 0);

  static OdTvDatabaseId generateMeshModel(OdTvFactoryId& id, int type = 0);

  static OdTvDatabaseId generateResetAttributesModel(OdTvFactoryId& id, int type);

  static OdTvDatabaseId generateManyCylindersModel(OdTvFactoryId& id, int type);

  static OdTvDatabaseId generateSelectionModel(OdTvFactoryId& id, int type = 0);

private:

  static void initCircleEllipseArcsModel(OdTvModelId& modelId);

  static void initLinetypesModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId);

  static void initLayersModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId);

  static void initTransparencyModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId);

  static void initLightModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId);

  static void initMaterialsModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId, const OdString& strResourceFolder);

  static void initShellEdgesAttributesModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId);

  static void initShellFacesAttributesModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId);

  static void initCylinderAttributesModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId);
  
  static void initSphereAttributesModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId);

  static void initBoxAttributesModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId);

  static void initMeshFacesAttributesModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId);

  static void initMeshEdgesAttributesModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId);

  static void initResetColorsModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId);

  static void initResetLineWeightModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId);

  static void initResetLinetypeModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId);

  static void initResetLinetypeScaleModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId);

  static void initResetLayerModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId);

  static void initResetVisibilityModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId);
};

#endif //VISUALIZEDEBUGMODELSGENERATORIMPL_H
