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


#ifndef POINTCLOUD2VISUALIZE_H
#define POINTCLOUD2VISUALIZE_H

#include "TD_PackPush.h"

#include "RxDispatchImpl.h"
#include "TvVisualizeFiler.h"

namespace PointCloud2Visualize {
  /** \details
  This class implements the properties of the rcs loader
  */
  class OdTvVisualizePointCloudFilerProperties : public OdRxDispatchImpl<>
  {
  public:
    OdTvVisualizePointCloudFilerProperties();
    virtual ~OdTvVisualizePointCloudFilerProperties();

    ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(OdTvVisualizePointCloudFilerProperties);
    static OdRxDictionaryPtr createObject();

    void     setDefaultColor(OdIntPtr pDefColor);
    OdIntPtr getDefaultColor() const;

    void     setPointSize(OdUInt8 pointSize) { m_iPointSize = pointSize; }
    OdUInt8  getPointSize() const { return m_iPointSize; }

    void      setAppendTransform(OdIntPtr pTransform);
    OdIntPtr  getAppendTransform() const;

    void     setImportAsRcsPointCloud(bool bSet) { m_bImportAsRcsPointCloud = bSet; }
    bool     getImportAsRcsPointCloud() const { return m_bImportAsRcsPointCloud; }

    void setUseSpatialTreeForSelection(bool bSet) { m_bUseSpatialTreeForSelection = bSet; }
    bool getUseSpatialTreeForSelection() const { return m_bUseSpatialTreeForSelection; }

    void setSeparator(OdIntPtr separator);
    OdIntPtr getSeparator() const;

    void setXYZIndexes(OdIntPtr pIndexes);
    OdIntPtr getXYZIndexes() const;

    void setRGBIndexes(OdIntPtr pIndexes);
    OdIntPtr getRGBIndexes() const;

    void setSkipLinesCount(OdUInt32 lines);
    OdUInt32 getSkipLinesCount() const;

    void      setDefaultUnits(OdUInt8 units) { m_defaultUnits = units; }
    OdUInt8   getDefaultUnits() const { return m_defaultUnits; }

  protected:

    ODCOLORREF    m_defaultColor;                // default color which is set to the entity
    OdUInt8       m_iPointSize;                  // Point size
    bool          m_bImportAsRcsPointCloud;      // Import as rcs point cloud
    bool          m_bUseSpatialTreeForSelection; // Use spatial tree for selection
    OdTvMatrix    m_appendTransform;             // Transform for the append
    OdString      m_separator;                   // Separator symbol
    OdArray<int>  m_xyzIndexes;                  // Indexes of XYZ columns
    OdArray<int>  m_rgbIndexes;                  // Indexes of RGB columns
    OdUInt32      m_iSkipLines;
    OdUInt8       m_defaultUnits;                // default units
  };
  typedef OdSmartPtr<OdTvVisualizePointCloudFilerProperties> OdTvVisualizePointCloudPropertiesPtr;
}

class OdTvVisualizePointCloudFiler : public OdTvVisualizeFiler
{
public:

  OdTvVisualizePointCloudFiler();

  virtual OdTvDatabaseId loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;

  // Inherited via OdTvVisualizeFiler
  virtual OdRxDictionaryPtr properties();
  virtual OdTvDatabaseId loadFrom(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId loadFrom(OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId generate(OdTvFilerTimeProfiling* pProfileRes = NULL) const;
  virtual OdTvModelId appendFrom(const OdTvDatabaseId& databaseId, const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvModelId appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvModelId appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;

private:
  PointCloud2Visualize::OdTvVisualizePointCloudPropertiesPtr m_properties;
};

class OdTvVisualizePointCloudFilerModule : public OdTvVisualizeFilerModule
{
public:
  virtual OdTvVisualizeFilerPtr getVisualizeFiler() const;

  void initApp();
  void uninitApp();
};


#include "TD_PackPop.h"

#endif // POINTCLOUD2VISUALIZE_H
