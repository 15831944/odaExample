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

#include "OdaCommon.h"
#include "RxDynamicModule.h"
#include "RxVariantValue.h"

// Visualize SDK
#include "TvFactory.h"

#include "PointCloud2Visualize.h"
#include "TvFilerTimer.h"
#include "TvDatabaseUtils.h"
#include "TvGeomCollector.h"
#include "TvError.h"
#include "DynamicLinker.h"
#include "TvPointCloudDataSources.h"

using namespace PointCloud2Visualize;

OdTvVisualizePointCloudFilerProperties::OdTvVisualizePointCloudFilerProperties()
  : m_defaultColor(ODRGB(191, 191, 191))
  , m_iPointSize(1)
  , m_bImportAsRcsPointCloud(true)
  , m_bUseSpatialTreeForSelection(false)
  , m_separator(OD_T(" "))
{
}

OdTvVisualizePointCloudFilerProperties::~OdTvVisualizePointCloudFilerProperties()
{

}

OdRxDictionaryPtr OdTvVisualizePointCloudFilerProperties::createObject()
{
  return OdRxObjectImpl<OdTvVisualizePointCloudFilerProperties, OdRxDictionary>::createObject();
}

namespace PointCloud2Visualize {
  ODRX_DECLARE_PROPERTY(DefaultColor)
  ODRX_DECLARE_PROPERTY(PointSize)
  ODRX_DECLARE_PROPERTY(AppendTransform)
  ODRX_DECLARE_PROPERTY(ImportAsRcsPointCloud)
  ODRX_DECLARE_PROPERTY(UseSpatialTreeForSelection)
  ODRX_DECLARE_PROPERTY(Separator)
  ODRX_DECLARE_PROPERTY(XYZIndexes)
  ODRX_DECLARE_PROPERTY(RGBIndexes)
  ODRX_DECLARE_PROPERTY(SkipLinesCount)
  ODRX_DECLARE_PROPERTY(DefaultUnits)

  ODRX_BEGIN_DYNAMIC_PROPERTY_MAP(OdTvVisualizePointCloudFilerProperties);
  ODRX_GENERATE_PROPERTY(DefaultColor)
  ODRX_GENERATE_PROPERTY(PointSize)
  ODRX_GENERATE_PROPERTY(AppendTransform)
  ODRX_GENERATE_PROPERTY(ImportAsRcsPointCloud)
  ODRX_GENERATE_PROPERTY(UseSpatialTreeForSelection)
  ODRX_GENERATE_PROPERTY(Separator)
  ODRX_GENERATE_PROPERTY(XYZIndexes)
  ODRX_GENERATE_PROPERTY(RGBIndexes)
  ODRX_GENERATE_PROPERTY(SkipLinesCount)
  ODRX_GENERATE_PROPERTY(DefaultUnits)
  ODRX_END_DYNAMIC_PROPERTY_MAP(OdTvVisualizePointCloudFilerProperties);

  ODRX_DEFINE_PROPERTY_METHODS(DefaultColor, OdTvVisualizePointCloudFilerProperties, getDefaultColor, setDefaultColor, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(PointSize, OdTvVisualizePointCloudFilerProperties, getPointSize, setPointSize, getUInt8);
  ODRX_DEFINE_PROPERTY_METHODS(AppendTransform, OdTvVisualizePointCloudFilerProperties, getAppendTransform, setAppendTransform, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(ImportAsRcsPointCloud, OdTvVisualizePointCloudFilerProperties, getImportAsRcsPointCloud, setImportAsRcsPointCloud, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(UseSpatialTreeForSelection, OdTvVisualizePointCloudFilerProperties, getUseSpatialTreeForSelection, setUseSpatialTreeForSelection, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(Separator, OdTvVisualizePointCloudFilerProperties, getSeparator, setSeparator, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(XYZIndexes, OdTvVisualizePointCloudFilerProperties, getXYZIndexes, setXYZIndexes, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(RGBIndexes, OdTvVisualizePointCloudFilerProperties, getRGBIndexes, setRGBIndexes, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(SkipLinesCount, OdTvVisualizePointCloudFilerProperties, getSkipLinesCount, setSkipLinesCount, getUInt32);
  ODRX_DEFINE_PROPERTY_METHODS(DefaultUnits, OdTvVisualizePointCloudFilerProperties, getDefaultUnits, setDefaultUnits, getIntPtr);
}

void OdTvVisualizePointCloudFilerProperties::setDefaultColor(OdIntPtr pDefColor)
{
  ODCOLORREF* pColor = (ODCOLORREF*)(pDefColor);
  if (!pColor)
  {
    ODA_ASSERT(false);
  }
  m_defaultColor = *pColor;
}

OdIntPtr OdTvVisualizePointCloudFilerProperties::getDefaultColor() const
{
  return (OdIntPtr)(&m_defaultColor);
}

void OdTvVisualizePointCloudFilerProperties::setAppendTransform(OdIntPtr pTransform)
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

OdIntPtr OdTvVisualizePointCloudFilerProperties::getAppendTransform() const
{
  return (OdIntPtr)(&m_appendTransform);
}


void OdTvVisualizePointCloudFilerProperties::setSeparator(OdIntPtr separator)
{
  OdString* pStr = (OdString*)separator;
  if (pStr)
    m_separator = *pStr;
  else
    m_separator = OD_T(" ");
}

OdIntPtr OdTvVisualizePointCloudFilerProperties::getSeparator() const
{
  return (OdIntPtr)(&m_separator);
}

void OdTvVisualizePointCloudFilerProperties::setXYZIndexes(OdIntPtr pIndexes)
{
  OdArray<int>* pArr = (OdArray<int>*)pIndexes;
  if (pArr)
    m_xyzIndexes = *pArr;
}

OdIntPtr OdTvVisualizePointCloudFilerProperties::getXYZIndexes() const
{
  return (OdIntPtr)(&m_xyzIndexes);
}

void OdTvVisualizePointCloudFilerProperties::setRGBIndexes(OdIntPtr pIndexes)
{
  OdArray<int>* pArr = (OdArray<int>*)pIndexes;
  if (pArr)
    m_rgbIndexes = *pArr;
}

OdIntPtr OdTvVisualizePointCloudFilerProperties::getRGBIndexes() const
{
  return (OdIntPtr)(&m_rgbIndexes);
}

void OdTvVisualizePointCloudFilerProperties::setSkipLinesCount(OdUInt32 lines)
{
  m_iSkipLines = lines;
}

OdUInt32 OdTvVisualizePointCloudFilerProperties::getSkipLinesCount() const
{
  return m_iSkipLines;
}

OdTvVisualizePointCloudFiler::OdTvVisualizePointCloudFiler()
  : m_properties(OdTvVisualizePointCloudFilerProperties::createObject())
{

}

OdTvDatabaseId OdTvVisualizePointCloudFiler::loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvDatabaseId tvDbId;

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

  OdString fileExt = filePath.right(3);
  fileExt.makeUpper();

  try
  {
    OdPointCloudDataSourcePtr pDataSource;
    if(!fileExt.compare(OD_T("PTS")))
      pDataSource = new OdTvPointCloudDataSource(filePath);
    else
    {
      OdString sep = (*((OdString*)m_properties->getSeparator()));
      OdArray<int> xyzArr = (*((OdArray<int>*)m_properties->getXYZIndexes()));
      OdArray<int> rgbArr = (*((OdArray<int>*)m_properties->getRGBIndexes()));
      pDataSource = new OdTvPointCloudDataSource(filePath, sep, m_properties->getSkipLinesCount(), xyzArr, rgbArr, *pDefColor);
    }

    if (pDataSource.isNull())
      return tvDbId;

    timing.startVectorizing();

    OdTvEntityId entityId = pTvModel->appendEntity();
    OdTvEntityPtr entity = entityId.openObject(OdTv::kForWrite);
    entity->setColor(OdTvColorDef(r, g, b));

    OdTvResult tvRes = tvOk;
    OdGeExtents3d pointCloudExtents;
    if (m_properties->getImportAsRcsPointCloud())
    {
      OdString newFilePath = filePath.left(filePath.getLength() - 3) + OD_T("rcs");

      timing.startMisc();
      OdTvGeometryDataId pointCloudId = entity->appendRcsPointCloud(pDataSource, newFilePath);
      timing.endMisc();

      if (tvRes != tvOk)
      {
        if (rc)
          *rc = tvRes;
        return tvDbId;
      }

      OdTvGeometryDataPtr pGeom = pointCloudId.openObject();
      if (!pGeom.isNull())
      {
        pGeom->setTargetDisplayMode(OdTvGeometryData::kEveryWhere);
        OdTvRcsPointCloudDataPtr pPointCloud = pointCloudId.openAsRcsPointCloud();
        pPointCloud->setPointSize(m_properties->getPointSize());

        pointCloudExtents = pPointCloud->getTransformedExtents();
      }
    }
    else
    {
      timing.startMisc();
      OdTvGeometryDataId tvPntCloudId = entity->appendPointCloud(pDataSource, &tvRes);
      if (!tvPntCloudId.isNull())
        tvPntCloudId.openAsPointCloud()->setPointSize(m_properties->getPointSize());
      timing.endMisc();

      if (tvRes != tvOk)
      {
        if (rc)
          *rc = tvRes;
        return tvDbId;
      }

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

    //set units
    if (!pTvModel.isNull())
    {
      //get units
      OdTv::Units tvUnits = (OdTv::Units)m_properties->getDefaultUnits();
      pTvModel->setUnits(tvUnits, 1.);
    }

    timing.endVectorizing();
  }
  catch (...)
  {
    if (rc)
      *rc = tvCannotOpenFile;
    return tvDbId;
  }

  ////////////////////////////////////////////////////////////////////

  timing.endTotal();

  ::odrxDynamicLinker()->unloadUnreferenced();

  if (pProfileRes)
  {
    pProfileRes->setImportTime(OdInt64((timing.getTotalTime() - timing.getVectorizingTime()) * 1000.));
    pProfileRes->setVectorizingTime(OdInt64((timing.getVectorizingTime()) * 1000.));
#if !defined(__APPLE__)
    pProfileRes->setTvTime(OdInt64(timing.getMiscTime() * 1000.));
#endif
  }

  if (rc)
    *rc = tvOk;

  return tvDbId;
}

OdRxDictionaryPtr OdTvVisualizePointCloudFiler::properties()
{
  return m_properties;
}

OdTvDatabaseId OdTvVisualizePointCloudFiler::loadFrom(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  return OdTvDatabaseId();
}

OdTvDatabaseId OdTvVisualizePointCloudFiler::loadFrom(OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  return OdTvDatabaseId();
}

OdTvDatabaseId OdTvVisualizePointCloudFiler::generate(OdTvFilerTimeProfiling* pProfileRes) const
{
  return OdTvDatabaseId();
}

OdTvModelId OdTvVisualizePointCloudFiler::appendFrom(const OdTvDatabaseId& databaseId, const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
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

  OdString fileExt = filePath.right(3);
  fileExt.makeUpper();

  try
  {
    OdPointCloudDataSourcePtr pDataSource;
    if (!fileExt.compare(OD_T("PTS")))
      pDataSource = new OdTvPointCloudDataSource(filePath);
    else
    {
      OdString sep = (*((OdString*)m_properties->getSeparator()));
      OdArray<int> xyzArr = (*((OdArray<int>*)m_properties->getXYZIndexes()));
      OdArray<int> rgbArr = (*((OdArray<int>*)m_properties->getRGBIndexes()));
      pDataSource = new OdTvPointCloudDataSource(filePath, sep, m_properties->getSkipLinesCount(), xyzArr, rgbArr, *pDefColor);
    }

    if (pDataSource.isNull())
      return tvModelId;

    timing.startVectorizing();

    OdTvEntityId entityId = pTvModel->appendEntity();
    OdTvEntityPtr entity = entityId.openObject(OdTv::kForWrite);
    entity->setColor(OdTvColorDef(r, g, b));

    // TV time
    if (m_properties->getImportAsRcsPointCloud())
    {
      OdTvResult tvRes = tvOk;
      OdString newFilePath = filePath.left(filePath.getLength() - 3) + OD_T("rcs");

      timing.startMisc();
      OdTvGeometryDataId pointCloudId = entity->appendRcsPointCloud(pDataSource, newFilePath, &tvRes);
      timing.endMisc();

      if (tvRes != tvOk)
      {
        if (rc)
          *rc = tvRes;
        return tvModelId;
      }

      OdTvGeometryDataPtr pGeom = pointCloudId.openObject();
      if (!pGeom.isNull())
      {
        pGeom->setTargetDisplayMode(OdTvGeometryData::kEveryWhere);
        OdTvRcsPointCloudDataPtr pPointCloud = pointCloudId.openAsRcsPointCloud();
        pPointCloud->setPointSize(m_properties->getPointSize());
      }
    }
    else
    {
      timing.startMisc();
      OdTvResult tvRes = tvOk;
      OdTvGeometryDataId tvPntCloudId = entity->appendPointCloud(pDataSource, &tvRes);
      if (tvPntCloudId.isNull())
        tvPntCloudId.openAsPointCloud()->setPointSize(m_properties->getPointSize());

      if (tvRes != tvOk)
      {
        if (rc)
          *rc = tvRes;
        return tvModelId;
      }
      timing.endMisc();

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

    //set units
    if (!pTvModel.isNull())
    {
      //get units
      OdTv::Units tvUnits = (OdTv::Units)m_properties->getDefaultUnits();
      pTvModel->setUnits(tvUnits, 1.);
    }

    timing.endVectorizing();
  }
  catch (...)
  {
    if (rc)
      *rc = tvCannotOpenFile;
    return tvModelId;
  }

  ////////////////////////////////////////////////////////////////////

  timing.endTotal();

  ::odrxDynamicLinker()->unloadUnreferenced();

  if (pProfileRes)
  {
    pProfileRes->setImportTime(OdInt64((timing.getTotalTime() - timing.getVectorizingTime()) * 1000.));
    pProfileRes->setVectorizingTime(OdInt64((timing.getVectorizingTime()) * 1000.));
#if !defined(__APPLE__)
    pProfileRes->setTvTime(OdInt64(timing.getMiscTime() * 1000.));
#endif
  }

  return tvModelId;
}

OdTvModelId OdTvVisualizePointCloudFiler::appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  return OdTvModelId();
}

OdTvModelId OdTvVisualizePointCloudFiler::appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  return OdTvModelId();
}


//***************************************************************************//
// 'OdTvVisualizePointCloudFilerModule' methods implementation
//***************************************************************************//
ODRX_DEFINE_DYNAMIC_MODULE(OdTvVisualizePointCloudFilerModule);

OdTvVisualizeFilerPtr OdTvVisualizePointCloudFilerModule::getVisualizeFiler() const
{
  OdTvVisualizeFilerPtr pFiler = new OdTvVisualizePointCloudFiler();
  return pFiler;
}

void OdTvVisualizePointCloudFilerModule::initApp()
{
  // initialize the Visualize SDK
  odTvInitialize();
}

void OdTvVisualizePointCloudFilerModule::uninitApp()
{
  // Uninitialize the Visualize SDK
  odTvUninitialize();
}
