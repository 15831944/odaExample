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

#include "TvGeomCollector.h"
#include "TvFilerTimer.h"
#include "Rcs2Visualize.h"
#include "TvDatabaseUtils.h"

#include "RcsFileServices/RxRcsFileServices.h"
#include "DbDatabase.h"

using namespace RCS2Visualize;

OdTvVisualizeRcsFilerProperties::OdTvVisualizeRcsFilerProperties() 
  : m_defaultColor(ODRGB(191, 191, 191))
  , m_iPointSize(2)
  , m_bImportAsRcsPointCloud(true)
, m_bUseSpatialTreeForSelection(false)
{
}

OdRxDictionaryPtr OdTvVisualizeRcsFilerProperties::createObject()
{
  return OdRxObjectImpl<OdTvVisualizeRcsFilerProperties, OdRxDictionary>::createObject();
}

OdTvVisualizeRcsFilerProperties::~OdTvVisualizeRcsFilerProperties()
{
}

namespace RCS2Visualize {
  ODRX_DECLARE_PROPERTY(DefaultColor)
    ODRX_DECLARE_PROPERTY(PointSize)
    ODRX_DECLARE_PROPERTY(AppendTransform)
    ODRX_DECLARE_PROPERTY(ImportAsRcsPointCloud)
    ODRX_DECLARE_PROPERTY(UseSpatialTreeForSelection)

    ODRX_BEGIN_DYNAMIC_PROPERTY_MAP(OdTvVisualizeRcsFilerProperties);
  ODRX_GENERATE_PROPERTY(DefaultColor)
    ODRX_GENERATE_PROPERTY(PointSize)
    ODRX_GENERATE_PROPERTY(AppendTransform)
    ODRX_GENERATE_PROPERTY(ImportAsRcsPointCloud)
    ODRX_GENERATE_PROPERTY(UseSpatialTreeForSelection)
    ODRX_END_DYNAMIC_PROPERTY_MAP(OdTvVisualizeRcsFilerProperties);

  ODRX_DEFINE_PROPERTY_METHODS(DefaultColor, OdTvVisualizeRcsFilerProperties, getDefaultColor, setDefaultColor, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(PointSize, OdTvVisualizeRcsFilerProperties, getPointSize, setPointSize, getUInt8);
  ODRX_DEFINE_PROPERTY_METHODS(AppendTransform, OdTvVisualizeRcsFilerProperties, getAppendTransform, setAppendTransform, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(ImportAsRcsPointCloud, OdTvVisualizeRcsFilerProperties, getImportAsRcsPointCloud, setImportAsRcsPointCloud, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(UseSpatialTreeForSelection, OdTvVisualizeRcsFilerProperties, getUseSpatialTreeForSelection, setUseSpatialTreeForSelection, getBool);
}

void OdTvVisualizeRcsFilerProperties::setDefaultColor(OdIntPtr ptr)
{
  ODCOLORREF* pColor = (ODCOLORREF*)(ptr);
  if (!pColor)
  {
    ODA_ASSERT(false);
  }
  m_defaultColor = *pColor;
}

OdIntPtr OdTvVisualizeRcsFilerProperties::getDefaultColor() const
{
  return (OdIntPtr)(&m_defaultColor);
}

void OdTvVisualizeRcsFilerProperties::setAppendTransform(OdIntPtr pTransform)
{
  const OdTvMatrix* pAppendTransform = (const OdTvMatrix*)(pTransform);

  if (pAppendTransform)
  {
    m_appendTransform = *pAppendTransform;
  }
  else
  {
    m_appendTransform = OdTvMatrix::kIdentity;
  }
}

OdIntPtr OdTvVisualizeRcsFilerProperties::getAppendTransform() const
{
  return (OdIntPtr)(&m_appendTransform);
}

//***************************************************************************//
// 'OdTvVisualizeRcsFiler' methods implementation
//***************************************************************************//

OdTvVisualizeRcsFiler::OdTvVisualizeRcsFiler() : m_properties(OdTvVisualizeRcsFilerProperties::createObject())
{
}

OdTvDatabaseId OdTvVisualizeRcsFiler::loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
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

  //generate model name
  OdString filename = OdTvDatabaseUtils::getFileNameFromPath(filePath);

  // create tv database
  OdTvFactoryId tvFactoryId = odTvGetFactory();
  tvDbId = tvFactoryId.createDatabase();
  OdTvDatabasePtr pDb = tvDbId.openObject(OdTv::kForWrite);

  // save filename to database user data
  OdTvDatabaseUtils::writeFileNameToTvDatabase(tvDbId, filename);

  //create tv model
  OdTvModelId tvModelId = pDb->createModel(filename);

  //prepare tv model for modifications
  OdTvModelPtr pTvModel = tvModelId.openObject(OdTv::kForWrite);

  OdTvGeomCollector wd(bUseTimeProfiling);

  /////////////////////////////////////////////////////////////////////

  //An additional block has been introduced to eliminate the discrepancy
  //between the function call and the exit of variables from the scope (it may be redesigned later)
  {
    // now we should read the header of *.rcs file to recieve the extents (or to read all points)
    OdPointCloudProjectDatabasePtr pProjDb;
    OdPointCloudScanDatabasePtr pScanDb;
    OdGeExtents3d pointCloudExtents;
    OdTvExPointCloudExScanItemPtr exItem;

    OdString fileExt = filePath.right(3);
    fileExt.makeUpper();

    {
      OdRxRcsFileServicesPtr pRcsFileServices;
      pRcsFileServices = odrxDynamicLinker()->loadApp(RX_RCS_FILE_SERVICES);

      if (!pRcsFileServices.isNull())
      {
        try
        {
          if (fileExt == OD_T("RCP"))
          {
            pProjDb = pRcsFileServices->readRcpFile(filePath);

            if (m_properties->getImportAsRcsPointCloud())
            {
              pointCloudExtents = pProjDb->getExtents();
            }
            else
            {
              throw OdError(OD_T("Only .rcs file can be loaded using the legacy mechanism in this application!"));
            }
          }
          else
          {
            pScanDb = pRcsFileServices->readRcsFile(filePath);

            if (m_properties->getImportAsRcsPointCloud())
            {
              pointCloudExtents = pScanDb->getTransformedExtents();
            }
            else
            {
              exItem = OdTvExPointCloudExScanItem::createObject();

              exItem->m_pScanDb = pScanDb;

              OdRcsVoxelIteratorPtr pVoxelIt = pScanDb->getVoxelIterator();
              for (; !pVoxelIt->done(); pVoxelIt->step())
              {
                OdRcsVoxelPtr pVoxel = pVoxelIt->getVoxel();
                OdGeExtents3d voxelExtents = pVoxel->getExtents();
                OdGePoint3d voxelExtentsMinPoint = voxelExtents.minPoint();
                OdUInt32 numberOfPoints = pVoxel->getTotalNumberOfPoints();
                OdRcsPointDataIteratorPtr pPointDataIt = pVoxel->getPointDataIterator();

                OdGePoint3dArray coords;
                OdCmEntityColorArray colors;
                pPointDataIt->getPoints(coords, colors, numberOfPoints);

                for (OdUInt32 pointIndex = 0; pointIndex < numberOfPoints; pointIndex++)
                {
                  coords[pointIndex].asVector() += voxelExtentsMinPoint.asVector();
                }

                exItem->appendPointsDataFromSource(coords, colors);
                exItem->m_pointSize = m_properties->getPointSize();
              }
            }
          }
        }
        catch (OdError& /*e*/)
        {
          if (rc)
            *rc = tvCannotOpenFile;
          return tvDbId;
        }
      }
      else
      {
        if (rc)
          *rc = tvRcsModuleIsMissed;
        return tvDbId;
      }
    }

    timing.startVectorizing();

    OdTvEntityId entityId = pTvModel->appendEntity();
    OdTvEntityPtr entity = entityId.openObject(OdTv::kForWrite);
    entity->setColor(OdTvColorDef(r, g, b));

    if (m_properties->getImportAsRcsPointCloud())
    {
      if (fileExt == OD_T("RCP"))
      {
        OdPointCloudScanIteratorPtr pScanIt = pProjDb->getScanIterator();
        for (; !pScanIt->done(); pScanIt->step())
        {
          OdPointCloudScanDatabasePtr pCurScanDb = pScanIt->getScanDb();

          if (!pCurScanDb.isNull())
          {
            OdTvResult tvAddRes;
            OdTvGeometryDataId pointCloudId = entity->appendRcsPointCloud(pCurScanDb, pProjDb, &tvAddRes);
            if (tvAddRes != tvOk)
            {
              if (rc)
                *rc = tvAddRes;

              return tvDbId;
            }

            OdTvGeometryDataPtr pGeom = pointCloudId.openObject();
            if (!pGeom.isNull())
            {
              pGeom->setTargetDisplayMode(OdTvGeometryData::kEveryWhere);
              OdTvRcsPointCloudDataPtr pPointCloud = pointCloudId.openAsRcsPointCloud();
              pPointCloud->setPointSize(m_properties->getPointSize());
            }
          }
        }
      }
      else
      {
        OdTvResult tvAddRes;
        OdTvGeometryDataId pointCloudId = entity->appendRcsPointCloud(pScanDb, NULL, &tvAddRes);
        if (tvAddRes != tvOk)
        {
          if (rc)
            *rc = tvAddRes;

          return tvDbId;
        }

        OdTvGeometryDataPtr pGeom = pointCloudId.openObject();
        if (!pGeom.isNull())
        {
          pGeom->setTargetDisplayMode(OdTvGeometryData::kEveryWhere);
          OdTvRcsPointCloudDataPtr pPointCloud = pointCloudId.openAsRcsPointCloud();
          pPointCloud->setPointSize(m_properties->getPointSize());
        }
      }
    }
    else
    {
      wd.setTvEntity(entityId);
      exItem->worldDrawPoints(NULL, &wd);

      if (m_properties->getUseSpatialTreeForSelection())
      {
        OdTvGeometryDataIteratorPtr pGeometriesIter = entity->getGeometryDataIterator();
        while (!pGeometriesIter->done())
        {
          OdTvGeometryDataId geometryDataId = pGeometriesIter->getGeometryData();
          if (geometryDataId.getType() == OdTv::kPointCloud)
          {
            OdTvPointCloudDataPtr pPointCloud = geometryDataId.openAsPointCloud();
            pPointCloud->setUseSpatialTreeForSelection(m_properties->getUseSpatialTreeForSelection());
          }

          pGeometriesIter->step();
        }
      }

    }

    //apply units
    pTvModel->setUnits(OdTv::kMeters);

    OdTvDatabaseUtils::createDeviceAndView(tvDbId, tvModelId, OdTvGsView::kWireframe);

    if (m_properties->getImportAsRcsPointCloud())
    {
      OdTvDevicesIteratorPtr pDevicesIterator = pDb->getDevicesIterator();
      OdTvGsDeviceId deviceId;
      while (!pDevicesIterator->done())
      {
        deviceId = pDevicesIterator->getDevice();
        if (deviceId.openObject()->getActive())
          break;
      }

      OdTvGsViewId viewId = deviceId.openObject()->getActiveView();
      if (!viewId.isNull())
        viewId.openObject(OdTv::kForWrite)->zoomExtents(pointCloudExtents.minPoint(), pointCloudExtents.maxPoint(), true);
    }

    timing.endVectorizing();

    /////////////////////////////////////////////////////////////////////

    timing.endTotal();

    exItem.release();

    if (!m_properties->getImportAsRcsPointCloud())
    {
      pProjDb.detach();
      pScanDb.detach();
    }
  }
    
  ::odrxDynamicLinker()->unloadUnreferenced();

  if (pProfileRes)
  {
    pProfileRes->setImportTime(OdInt64((timing.getTotalTime() - timing.getVectorizingTime()) * 1000.));
    pProfileRes->setVectorizingTime(OdInt64((timing.getVectorizingTime()) * 1000.));
#if !defined(__APPLE__)
    pProfileRes->setTvTime(OdInt64(wd.getTotalTime() * 1000.));
#endif
  }

  return tvDbId;
}

OdTvDatabaseId OdTvVisualizeRcsFiler::loadFrom(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  if (rc)
    *rc = tvNotImplementedYet;

  return OdTvDatabaseId();
}

OdTvDatabaseId OdTvVisualizeRcsFiler::loadFrom(OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  if (rc)
    *rc = tvNotImplementedYet;

  return OdTvDatabaseId();
}

OdTvDatabaseId OdTvVisualizeRcsFiler::generate(OdTvFilerTimeProfiling* pProfileRes) const
{
  OdTvDatabaseId tvDbId;

  // does nothing
  return tvDbId;
}

OdTvModelId OdTvVisualizeRcsFiler::appendFrom(const OdTvDatabaseId& databaseId, const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvModelId tvModelId;

  if (rc)
    *rc = tvOk;

  OdTvDatabasePtr pDb = databaseId.openObject(OdTv::kForWrite);
  //check that we are in the real append mode
  OdTvGsDeviceId activeTvGsDeviceId;
  {
    OdTvDevicesIteratorPtr devicesIteratorPtr = pDb->getDevicesIterator();
    while (!devicesIteratorPtr->done())
    {
      activeTvGsDeviceId = devicesIteratorPtr->getDevice();
      if (activeTvGsDeviceId.openObject()->getActive())
        break;
    }
  }

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

  //generate model name
  OdString fileName = OdTvDatabaseUtils::getFileNameFromPath(filePath);

  // save filename to database user data
  OdTvDatabaseUtils::writeFileNameToTvDatabase(databaseId, fileName);

  // Generate model name
  OdString modelName = OdTvDatabaseUtils::generateModelName(databaseId, fileName);

  //create tv model
  tvModelId = pDb->createModel(modelName);

  //prepare tv model for modifications
  OdTvModelPtr pTvModel = tvModelId.openObject(OdTv::kForWrite);

  OdTvGeomCollector wd(bUseTimeProfiling);

  // load rcs file serives
  OdRxRcsFileServicesPtr pRcsFileServices;
  pRcsFileServices = odrxDynamicLinker()->loadApp(RX_RCS_FILE_SERVICES);

  if (!pRcsFileServices.isNull())
  {
    OdPointCloudScanDatabasePtr pScanDb;

    try
    {      
      pScanDb = pRcsFileServices->readRcsFile(filePath);
    }
    catch (OdError_CantOpenFile&)
    {
      if (rc)
        *rc = tvCannotOpenFile;
      return tvModelId;
    }

    OdTvExPointCloudExScanItemPtr exItem = OdTvExPointCloudExScanItem::createObject();

    exItem->m_pScanDb = pScanDb;

    // work with voxels
    OdRcsVoxelIteratorPtr pVoxelIt = pScanDb->getVoxelIterator();
    for (; !pVoxelIt->done(); pVoxelIt->step())
    {
      OdRcsVoxelPtr pVoxel = pVoxelIt->getVoxel();
      OdGeExtents3d voxelExtents = pVoxel->getExtents();
      OdGePoint3d voxelExtentsMinPoint = voxelExtents.minPoint();
      OdUInt32 numberOfPoints = pVoxel->getTotalNumberOfPoints();
      OdRcsPointDataIteratorPtr pPointDataIt = pVoxel->getPointDataIterator();

      OdGePoint3dArray coords;
      OdCmEntityColorArray colors;
      pPointDataIt->getPoints(coords, colors, numberOfPoints);

      for (OdUInt32 pointIndex = 0; pointIndex < numberOfPoints; pointIndex++)
      {
        coords[pointIndex].asVector() += voxelExtentsMinPoint.asVector();
      }

      exItem->appendPointsDataFromSource(coords, colors);
      exItem->m_pointSize = m_properties->getPointSize();
    }

    timing.startVectorizing();

    // add entity and draw points
    OdTvEntityId entityId = pTvModel->appendEntity();
    entityId.openObject(OdTv::kForWrite)->setColor(OdTvColorDef(r, g, b));

    wd.setTvEntity(entityId);
    exItem->worldDrawPoints(NULL, &wd);

    //add model to view
    if (activeTvGsDeviceId.isNull())
      OdTvDatabaseUtils::createDeviceAndView(databaseId, tvModelId, OdTvGsView::kWireframe);
    else
    {
      OdTvGsViewId viewId = activeTvGsDeviceId.openObject()->getActiveView();
      if (!viewId.isNull())
        viewId.openObject(OdTv::kForWrite)->addModel(tvModelId);
    }

    //apply transform if need 
    OdTvMatrix* pTransfrom = (OdTvMatrix*)m_properties->getAppendTransform();
    if (pTransfrom)
    {
      OdTvDatabaseId& tvDvId = const_cast<OdTvDatabaseId&>(databaseId);
      OdTvDatabaseUtils::applyTransformToTheModel(tvDvId, modelName, *pTransfrom);
    }

    //apply units
    pTvModel->setUnits(OdTv::kMeters);

    timing.endVectorizing();
  }

  timing.endTotal();

  pRcsFileServices.release();
  ::odrxDynamicLinker()->unloadUnreferenced();

  if (pProfileRes)
  {
    pProfileRes->setImportTime(OdInt64((timing.getTotalTime() - timing.getVectorizingTime()) * 1000.));
    pProfileRes->setVectorizingTime(OdInt64((timing.getVectorizingTime() - wd.getTotalTime()) * 1000.));
    pProfileRes->setTvTime(OdInt64(wd.getTotalTime() * 1000.));
  }

  return tvModelId;
}

OdTvModelId OdTvVisualizeRcsFiler::appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  if (rc)
    *rc = tvNotImplementedYet;

  return OdTvModelId();
}

OdTvModelId OdTvVisualizeRcsFiler::appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  if (rc)
    *rc = tvNotImplementedYet;

  return OdTvModelId();
}

//***************************************************************************//
// 'OdTvVisualizeRcsFilerModule' methods implementation
//***************************************************************************//

ODRX_DEFINE_DYNAMIC_MODULE(OdTvVisualizeRcsFilerModule);

void OdTvVisualizeRcsFilerModule::initApp()
{
  // initialize the Visualize SDK
  odTvInitialize();

  OdTvExPointCloudExScanItem::rxInit();
}

void OdTvVisualizeRcsFilerModule::uninitApp()
{
  // Uninitialize the Visualize SDK
  odTvUninitialize();

  OdTvExPointCloudExScanItem::rxUninit();
}

OdTvVisualizeFilerPtr OdTvVisualizeRcsFilerModule::getVisualizeFiler() const
{
  OdTvVisualizeFilerPtr pRcsFiler = new OdTvVisualizeRcsFiler();

  return pRcsFiler;
}

//***************************************************************************//
// 'OdTvExPointCloudExScanItem' methods implementation
//***************************************************************************//
ODRX_CONS_DEFINE_MEMBERS(OdTvExPointCloudExScanItem, OdRxObject, RXIMPL_CONSTR);

bool OdTvExPointCloudExScanItem::worldDrawPoints(const OdDbPointCloudEx* pEnt, OdGiWorldDraw* pWd) const
{
  drawPoints(pWd->geometry(), m_pointSize);

  return true;
}

void OdTvExPointCloudExScanItem::drawPoints(OdGiGeometry& geom, OdInt32 pointSize) const
{
  geom.pushModelTransform(m_pScanDb->getTransformMatrix());
  std::list<OdGePoint3dArray>::const_iterator pointsArrayListIt = m_pointsArrayList.begin();
  std::list<OdCmEntityColorArray>::const_iterator pointColorsArrayListIt = m_pointColorsArrayList.begin();

  for (; pointsArrayListIt != m_pointsArrayList.end(); ++pointsArrayListIt, ++pointColorsArrayListIt)
  {
    OdInt32 nCount = 0;
    nCount = (*pointsArrayListIt).size();

    const OdGePoint3d* pPt = (*pointsArrayListIt).getPtr();
    const OdCmEntityColor* pColor = (*pointColorsArrayListIt).getPtr();

    geom.polypoint(nCount, pPt, pColor, NULL, NULL, NULL, pointSize);
  }
  geom.popModelTransform();
}

void OdTvExPointCloudExScanItem::appendPointsDataFromSource(const OdGePoint3dArray& points, const OdCmEntityColorArray& colors)
{
  m_pointsArrayList.push_back(points);
  m_pointColorsArrayList.push_back(colors);
}
