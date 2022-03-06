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

#ifndef TVDATABASECOPIER_NWD_H
#define TVDATABASECOPIER_NWD_H

#include "TD_PackPush.h"

#include "RxObject.h"
#include "NwHostAppServices.h"

// Visualize
#include "TvDatabase.h"
#include "TvImportUserData.h"

//Gi
#include "GiMaterial.h"

class OdHatchPatternManager;

class OdNwDatabase;
typedef OdSmartPtr<OdNwDatabase> OdNwDatabasePtr;
class OdNwObjectId;

class OdTvBlockId;
class OdTvGsViewId;

/** \details
This class is service for creating database for dwg file
*/
class OdTvNwdService : public OdNwHostAppServices
{
  virtual OdHatchPatternManager* patternManager() { return NULL; }
};

class OdTv2NwdCopier
{
public:
  OdTv2NwdCopier(const OdTvDatabaseId& tvDbId, OdTvGsDeviceId deviceId, OdTvGsViewId viewId, OdTvModelId modelId, bool bConvertNurbsToSpline);
  ~OdTv2NwdCopier();
  OdNwDatabasePtr copyDatabase();

  //OdDbObjectId getNewBdObjectIdFromOldBdObjectId(OdUInt64 tvHandle) const;
  //OdDbObjectId getRasterImageDbIdFrmPath(OdString sFilePath);

  OdNwDatabasePtr getCopiedDatabasae() const { return m_pDb; };

  OdTvGsViewId getViewForExport() { return m_viewIdForExport; };

protected:

  void copyMaterials(OdNwDatabasePtr& pDb);
  void copyLinetypes(OdNwDatabasePtr& pDb);
  void copyRasterImages(OdNwDatabasePtr& pDb);
  void copyTextStyles(OdNwDatabasePtr& pDb);
  void copyBackground(OdNwDatabasePtr& pDb);
  void copyVisualStyles(OdNwDatabasePtr& pDb);
  void copyViews(OdNwDatabasePtr& pDb);
  OdNwObjectId copyBlock(OdNwDatabasePtr& pDb, OdTvBlockId blockTvId, OdTvGsViewId tvViewId);
  void copyModels(OdNwDatabasePtr& pDb);

  static OdGiMaterialColor getOdGiMaterialColorFromOdTvMaterialColor(const OdTvMaterialColor& materialColor);
  static OdGiMaterialMap getOdGiMaterialMapFromOdTvMaterialMap(const OdTvMaterialMap& materialMap);

  static OdCmEntityColor getTvCmEntityColorFromDef(const OdTvColorDef& color);
  static OdGiMapper getGiMapperFromTvMapper(const OdTvTextureMapper& tvMapper);

  void eyeToWorldPoint(OdTvPoint& basePoint, const OdTvGsViewPtr& pView) const;
  void eyeToWorldVector(OdTvVector& vector, const OdTvGsViewPtr& pView) const;

  OdTvRegAppId getRegAppId(OdTvDatabasePtr& pTvDb, const OdString& strAppName) const;
  bool getViewUserData(OdTvGsViewPtr& pTvView, OdTvDatabasePtr& pTvDb, OdTvDwgViewData& dwgViewData) const;
  bool getLayoutUserData(OdTvGsDevicePtr& pTvDevice, OdTvDatabasePtr& pTvDb, OdTvDwgLayoutData& dwgLayoutData) const;

private:
  OdTvDatabaseId m_tvDbId;
  OdNwDatabasePtr m_pDb;
  bool m_bConvertNurbsToSpline;
  OdStaticRxObject<OdTvNwdService> m_svcs;

  OdTvGsDeviceId m_deviceForExport;
  OdTvGsViewId m_viewIdForExport;
  OdTvModelId m_modelIdForExport;
};

#include "TD_PackPop.h"

#endif // TVDATABASECOPIER_NWD_H
