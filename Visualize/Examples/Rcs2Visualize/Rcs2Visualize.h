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


#ifndef RCS2VISUALIZE_H
#define RCS2VISUALIZE_H

#include "TD_PackPush.h"
#include "RxDispatchImpl.h"

#include "TvVisualizeFiler.h"
#include "DbPointCloudObj/DbPointCloudHostPE.h"
#include "RcsFileServices/RxRcsFileServices.h"

#define STL_USING_LIST
#include "OdaSTL.h"
#include "CmEntityColorArray.h"
#include "DbObject.h"

namespace RCS2Visualize {
  /** \details
  This class implements the properties of the rcs loader
  */
  class OdTvVisualizeRcsFilerProperties : public OdRxDispatchImpl<>
  {
  public:
    OdTvVisualizeRcsFilerProperties();
    virtual ~OdTvVisualizeRcsFilerProperties();

    ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(OdTvVisualizeRcsFilerProperties);
    static OdRxDictionaryPtr createObject();

    void     setDefaultColor(OdIntPtr pDefColor);
    OdIntPtr getDefaultColor() const;

    void     setPointSize(OdUInt32 pointSize) {m_iPointSize = pointSize; }
    OdUInt8  getPointSize() const { return m_iPointSize; }

    void      setAppendTransform(OdIntPtr pTransform);
    OdIntPtr  getAppendTransform() const;

    void     setImportAsRcsPointCloud(bool bSet) { m_bImportAsRcsPointCloud = bSet; }
    bool     getImportAsRcsPointCloud() const { return m_bImportAsRcsPointCloud; }

    void setUseSpatialTreeForSelection(bool bSet) { m_bUseSpatialTreeForSelection = bSet; }
    bool getUseSpatialTreeForSelection() const { return m_bUseSpatialTreeForSelection; }

  protected:

    ODCOLORREF m_defaultColor;                // default color which is set to the entity
    OdUInt8    m_iPointSize;                  // Point size
    bool       m_bImportAsRcsPointCloud;      // Import as rcs point cloud
    bool       m_bUseSpatialTreeForSelection; // Use spatial tree for selection
    OdTvMatrix m_appendTransform;             // Transform for the append
  };
  typedef OdSmartPtr<OdTvVisualizeRcsFilerProperties> OdTvVisualizeRcsFilerPropertiesPtr;
}

/** \details
This class is rcs loader (to the Visualize database)
*/
class OdTvVisualizeRcsFiler : public OdTvVisualizeFiler
{
public:

  OdTvVisualizeRcsFiler();

  virtual OdRxDictionaryPtr properties() { return m_properties; }
  virtual OdTvDatabaseId loadFrom(OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId loadFrom(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId generate(OdTvFilerTimeProfiling* pProfileRes = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase*  pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf*       pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, const OdString&    filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;

private:
  RCS2Visualize::OdTvVisualizeRcsFilerPropertiesPtr m_properties;
};


/** \details
This class is rcs loader module implementation
*/
class OdTvVisualizeRcsFilerModule : public OdTvVisualizeFilerModule
{
public:
  virtual OdTvVisualizeFilerPtr getVisualizeFiler() const;

  void initApp();
  void uninitApp();
};


/** \details
This class represents an interface of a Point Cloud Ex Scan Item
*/
class OdTvExPointCloudExScanItem : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdTvExPointCloudExScanItem);

  OdTvExPointCloudExScanItem() : m_pointSize(2) {}

  virtual ~OdTvExPointCloudExScanItem() {};

  virtual bool worldDrawPoints(const OdDbPointCloudEx* pEnt, OdGiWorldDraw* pWd) const;

private:
  void drawPoints(OdGiGeometry& geom, OdInt32 pointSize) const;
  void appendPointsDataFromSource(const OdGePoint3dArray& points, const OdCmEntityColorArray& colors);

  OdPointCloudScanDatabasePtr m_pScanDb;

  std::list<OdGePoint3dArray> m_pointsArrayList;
  std::list<OdCmEntityColorArray> m_pointColorsArrayList;
  //OdGeExtents3d m_extents;

  OdInt32 m_pointSize;

  friend class OdTvVisualizeRcsFiler;
};
typedef OdSmartPtr<OdTvExPointCloudExScanItem> OdTvExPointCloudExScanItemPtr;

#include "TD_PackPop.h"

#endif // RCS2VISUALIZE_H
