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

#ifndef OD_TV_DATABASENAMING_H
#define OD_TV_DATABASENAMING_H

#include "TvDatabase.h"

#define STL_USING_SET
#include "OdaSTL.h"

#define OD_TV_COMMON_DEVICE_NAME L"Device"
#define OD_TV_COMMON_VIEW_NAME L"View"
#define MAX_CDATREENAME_GENERATION_ATTEMPTS 100

class OdTvDatabaseUtils
{
public:
  static OdString getFileNameFromPath(const OdString& filePath);
  static void writeFileNameToTvDatabase(const OdTvDatabaseId& dbId, const OdString& fileName);
  static void createDeviceAndView(const OdTvDatabaseId& dbId, const OdTvModelId& modelId, OdTvGsView::RenderMode renderMode, bool bAdvencedLightingSetup = false);
  static OdString generateModelName(OdTvDatabaseId databaseId, const OdString& fileName);

  static bool applyTransformToTheModel(OdTvDatabaseId& databaseId, const OdString& modelSpaceName, const OdTvMatrix& transform);
  static void collectViewsModelsAndBlocks(const OdTvDatabaseId& tvDbId, std::set<OdTvGsViewId>& foreignViews, std::set<OdTvModelId>& foreignModels, std::set<OdTvBlockId>& foreignBlocks);

  static void markCDANode(OdRxModelTreeBaseNode* pNode);
};

#endif //OD_TV_DATABASENAMING_H
