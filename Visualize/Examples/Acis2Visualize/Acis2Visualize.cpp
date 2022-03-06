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
#include "Ge/GeExtents2d.h"

#include "TvFactory.h"
#include "TvGeomCollector.h"
#include "TvFilerTimer.h"
#include "TvDatabaseUtils.h"

#include "Acis2Visualize.h"

// ACIS
#include "AcisBuilder/ISatConverter.h"

//Brep
#include "Br/BrBrep.h"
#include "BrepRenderer/BrepRendererImpl.h"

using namespace Acis2Visualize;

OdTv::Units getUnits(double coefToMM, OdTv::Units defaultUnits, double& additionalConvCoeffToMeters)
{
  OdTv::Units tvUnits = defaultUnits;
  additionalConvCoeffToMeters = 1.;

  if (fabs(coefToMM - 1.) < 1.0e-3)
  {
    tvUnits = OdTv::kMillimeters;
  }
  else if (fabs(coefToMM - 25.4) < 1.0e-4)
  {
    tvUnits = OdTv::kInches;
  }
  else if (fabs(coefToMM - 10.) < 1.0e-3)
  {
    tvUnits = OdTv::kCentimeters;
  }
  else if (fabs(coefToMM - 1000.) < 1.0e-3)
  {
    tvUnits = OdTv::kMeters;
  }
  else if (fabs(coefToMM - 304.8) < 1.0e-4)
  {
    tvUnits = OdTv::kFeet;
  }
  else
  {
    tvUnits = OdTv::kUserDefined;
    additionalConvCoeffToMeters = coefToMM / 1000.;
  }

  return tvUnits;
}

OdTvVisualizeAcisFilerProperties::OdTvVisualizeAcisFilerProperties() :
  m_defaultColor(ODRGB(191, 191, 191))
  , m_bImportBrepAsBrep(false)
  , m_dFACETRES(1.)
{
}

OdRxDictionaryPtr OdTvVisualizeAcisFilerProperties::createObject()
{
  return OdRxObjectImpl<OdTvVisualizeAcisFilerProperties, OdRxDictionary>::createObject();
}

OdTvVisualizeAcisFilerProperties::~OdTvVisualizeAcisFilerProperties()
{
}

namespace Acis2Visualize {
  ODRX_DECLARE_PROPERTY(DefaultColor)
    ODRX_DECLARE_PROPERTY(FacetRes)
    ODRX_DECLARE_PROPERTY(ImportBrepAsBrep)
    ODRX_DECLARE_PROPERTY(DCRect)

    ODRX_BEGIN_DYNAMIC_PROPERTY_MAP(OdTvVisualizeAcisFilerProperties);
  ODRX_GENERATE_PROPERTY(FacetRes)
    ODRX_GENERATE_PROPERTY(ImportBrepAsBrep)
    ODRX_GENERATE_PROPERTY(DefaultColor)
    ODRX_GENERATE_PROPERTY(DCRect)
    ODRX_END_DYNAMIC_PROPERTY_MAP(OdTvVisualizeAcisFilerProperties);

  ODRX_DEFINE_PROPERTY_METHODS(FacetRes, OdTvVisualizeAcisFilerProperties, getFacetRes, setFacetRes, getDouble);
  ODRX_DEFINE_PROPERTY_METHODS(ImportBrepAsBrep, OdTvVisualizeAcisFilerProperties, getImportBrepAsBrep, setImportBrepAsBrep, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(DefaultColor, OdTvVisualizeAcisFilerProperties, getDefaultColor, setDefaultColor, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(DCRect, OdTvVisualizeAcisFilerProperties, getDCRect, setDCRect, getIntPtr);
}

void OdTvVisualizeAcisFilerProperties::setDefaultColor(OdIntPtr ptr)
{
  ODCOLORREF* pColor = (ODCOLORREF*)(ptr);
  if (!pColor)
  {
    ODA_ASSERT(false);
  }
  m_defaultColor = *pColor;
}

OdIntPtr OdTvVisualizeAcisFilerProperties::getDefaultColor() const
{
  return (OdIntPtr)(&m_defaultColor);
}

void OdTvVisualizeAcisFilerProperties::setFacetRes(double dFacetRes)
{
  m_dFACETRES = dFacetRes;

  if (dFacetRes < 0.01)
    m_dFACETRES = 0.01;

  if (dFacetRes > 10.)
    m_dFACETRES = 10.;
}

double OdTvVisualizeAcisFilerProperties::getFacetRes() const
{
  return m_dFACETRES;
}

void OdTvVisualizeAcisFilerProperties::setImportBrepAsBrep(bool bImportBrepAsBrep)
{
  m_bImportBrepAsBrep = bImportBrepAsBrep;
}

bool OdTvVisualizeAcisFilerProperties::getImportBrepAsBrep() const
{
  return m_bImportBrepAsBrep;
}

void OdTvVisualizeAcisFilerProperties::setDCRect(OdIntPtr rect)
{
  OdTvDCRect* pRect = (OdTvDCRect*)(rect);
  if (!pRect)
  {
    ODA_ASSERT(false);
  }

  m_importRect = *pRect;
}

OdIntPtr OdTvVisualizeAcisFilerProperties::getDCRect() const
{
  return (OdIntPtr)(&m_importRect);
}

//***************************************************************************//
// 'OdTvVisualizeAcisFiler' methods implementation
//***************************************************************************//

OdTvVisualizeAcisFiler::OdTvVisualizeAcisFiler() : m_properties(OdTvVisualizeAcisFilerProperties::createObject())
{
}

OdTvDatabaseId OdTvVisualizeAcisFiler::loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvDatabaseId tvDbId;
  bool bUseTimeProfiling = pProfileRes != NULL;

  OdTvFilerTimer timing(bUseTimeProfiling);
  timing.startMisc();
  OdStreamBufPtr pStreamBuf = odrxSystemServices()->createFile(filePath);
  timing.endMisc();

  if (pStreamBuf.isNull())
  {
    if (rc)
      *rc = tvCannotOpenFile;
    return tvDbId;
  }

  tvDbId = loadFrom(pStreamBuf.get(), pProfileRes, rc);

  if (bUseTimeProfiling)
    pProfileRes->setImportTime(pProfileRes->getImportTime() + (timing.getMiscTime() * 1000));

  return tvDbId;
}

OdTvDatabaseId OdTvVisualizeAcisFiler::loadFrom(OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes /*= NULL*/, OdTvResult* rc /*= NULL*/) const
{
  if (rc)
    *rc = tvNotImplementedYet;

  return OdTvDatabaseId();
}

OdTvDatabaseId OdTvVisualizeAcisFiler::loadFrom(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes /*= NULL*/, OdTvResult* rc /*= NULL*/) const
{
  OdTvDatabaseId tvDbId;

  if (!pBuffer)
  {
    if (rc)
      *rc = tvFilerEmptyInternalDatabase;
    return tvDbId;
  }

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
  OdString filename = OdTvDatabaseUtils::getFileNameFromPath(pBuffer->fileName());

  // create tv database
  OdTvFactoryId tvFactoryId = odTvGetFactory();
  tvDbId = tvFactoryId.createDatabase();
  OdTvDatabasePtr pTvDb = tvDbId.openObject(OdTv::kForWrite);

  // save filename to database user data
  OdTvDatabaseUtils::writeFileNameToTvDatabase(tvDbId, filename);

  //create tv model
  OdTvModelId tvModelId = pTvDb->createModel(filename);

  //prepare tv model for modifications
  OdTvModelPtr pTvModel = tvModelId.openObject(OdTv::kForWrite);

  OdTvGeomCollector wd(bUseTimeProfiling);

  OdArray<ISATConverter*> out;
  try
  {
    bool bSuccess = ABBreakToSingleBody(pBuffer, NULL, true, out);

    //extract units
    double coefToMM = 1.;
    if (bSuccess)
    {
      OdArray<ISATConverter*>::iterator pIt = out.begin()
        , pEnd = out.end();
      for (; pIt != pEnd; ++pIt)
      {
        coefToMM = (*pIt)->getUnitToMMCoef();
        break;
      }
    }

    double addUnitCoefToMeters;
    OdTv::Units tvUnits = getUnits(coefToMM, OdTv::kMillimeters, addUnitCoefToMeters);

    if (bSuccess)
    {
      timing.startVectorizing();

      if (m_properties->getImportBrepAsBrep())
      {
        int bodyNumber = 1;
        OdArray<ISATConverter*>::iterator pIt = out.begin()
          , pEnd = out.end();
        for (; pIt != pEnd; ++pIt)
        {
          OdBrepRendererImpl brepRenderer;

          OdBrBrep brep;
          // Set the acis data for brep from the converter (file)
          brep.set((*pIt)->getIBr());

          // append Tv Entity
          OdString entityName;
          entityName.format(OD_T("%s%d"), OD_T("Body "), bodyNumber);

          OdTvEntityId entityId = pTvModel->appendEntity(entityName);
          OdTvEntityPtr pEntity = entityId.openObject(OdTv::kForWrite);
          pEntity->setColor(OdTvColorDef(r, g, b));

          OdTvGeometryDataId brepId = pEntity->appendBrep(brep, NULL, rc);
          if (brepId.isValid())
          {
            brepId.openAsBrep()->setFacetRes(m_properties->getFacetRes());
            brepId.openAsBrep()->setEnableCaching(true);
          }

          bodyNumber++;
        }

        OdTvDatabaseUtils::createDeviceAndView(tvDbId, tvModelId, OdTvGsView::kFlatShaded);
      }
      else
      {
        // 1. First attempt to fill TV model with purpose to calculate extents
        OdTvModelId tvTempModelId = pTvDb->createModel(filename + OD_T("_TempModel"));
        OdTvModelPtr pTvTempModel = tvTempModelId.openObject(OdTv::kForWrite);

        int bodyNumber = 1;
        OdArray<ISATConverter*>::iterator pIt = out.begin(), pEnd = out.end();
        for (; pIt != pEnd; ++pIt)
        {
          OdBrepRendererImpl brepRenderer;

          OdBrBrep brep;
          // Set the acis data for brep from the converter (file)
          brep.set((*pIt)->getIBr());

          // Set triangulation params to some defaults.
          wrTriangulationParams m_DefaultTriangulationParams = wrTriangulationParams(true);
          brepRenderer.setTriangulationParams(&m_DefaultTriangulationParams);

          // Set the brep data for the renderer
          brepRenderer.setBrep(brep);

          // append Tv Entity
          OdString entityName;
          entityName.format(OD_T("%s%d"), OD_T("Body "), bodyNumber);

          OdTvEntityId entityId = pTvTempModel->appendEntity(entityName);
          entityId.openObject(OdTv::kForWrite)->setColor(OdTvColorDef(r, g, b));

          // Do rendering
          wd.setTargetDisplayMode(OdTvGeometryData::kWireframe);
          wd.setTvEntity(entityId);
          brepRenderer.draw(&wd, BrepRenderModes::kEdges, 0);

          bodyNumber++;
        }

        // 2. Create temp device and view for calculate extents and appropriate deviation
        double dDeviation = 1.;
        {
          // Create temp device
          OdTvGsDeviceId tempDeviceId = pTvDb->createBitmapDevice(OD_T("Tv_TempRentedDevice"));
          OdTvGsDevicePtr pTempDevice = tempDeviceId.openObject(OdTv::kForWrite);

          // Create and setup temp view
          OdTvGsViewId tvTempViewId = pTempDevice->createView(OD_T("TempView"));
          OdTvGsViewPtr pTempView = tvTempViewId.openObject(OdTv::kForWrite);
          pTempView->addModel(tvTempModelId);
          pTempView->setMode(OdTvGsView::kWireframe);
          pTempView->setView(OdTvPoint(0., 0., 1.), OdTvPoint(0., 0., 0.), OdTvVector(0., 1., 0.), 1., 1.);
          pTempView->setActive(true);
          pTempDevice->addView(tvTempViewId);

          OdTvDCRect* pRect = (OdTvDCRect*)m_properties->getDCRect();
          int iWidth = pRect->xmax - pRect->xmin;
          int iHeight = pRect->ymin - pRect->ymax;

          // Setup temp device
          pTempDevice->setupGsBitmap(iWidth, iHeight, OdTvGsDevice::kOpenGLES2);

          // Get extents
          OdGeBoundBlock3d extents;
          OdTvPoint minPoint = OdTvPoint(0., 0., 0.), maxPoint = OdTvPoint(1., 1., 1.);
          bool bRes = pTempView->viewExtents(extents);
          extents.setToBox(true); //since we know that we are not perspective
          extents.getMinMaxPoints(minPoint, maxPoint);

          // Set extents
          pTempView->zoomExtents(minPoint, maxPoint);

          OdGePoint2d pixelsPerUnit;
          OdTvPoint pt; //since we are use non-perspective view, this point is not important
          pTempView->getNumPixelsInUnitSquare(pt, pixelsPerUnit, false);
          pixelsPerUnit.x = fabs(pixelsPerUnit.x);
          pixelsPerUnit.y = fabs(pixelsPerUnit.y);

          dDeviation = 0.5 / odmax(pixelsPerUnit.x, pixelsPerUnit.y);

          // Remove temp database objects
          pTempDevice->removeView(tvTempViewId);
          pTvDb->removeDevice(tempDeviceId);
          pTvDb->removeModel(tvTempModelId);
        }

        // 3. Fill database again
        bodyNumber = 1;
        pIt = out.begin(), pEnd = out.end();
        for (; pIt != pEnd; ++pIt)
        {
          OdBrepRendererImpl brepRenderer;

          OdBrBrep brep;
          // Set the acis data for brep from the converter (file)
          brep.set((*pIt)->getIBr());

          // Set triangulation params to some defaults.
          wrTriangulationParams m_DefaultTriangulationParams = wrTriangulationParams(true);
          m_DefaultTriangulationParams.surfaceTolerance = dDeviation / m_properties->getFacetRes();
          brepRenderer.setTriangulationParams(&m_DefaultTriangulationParams);

          // Set the brep data for the renderer
          brepRenderer.setBrep(brep);

          // append Tv Entity
          OdString entityName;
          entityName.format(OD_T("%s%d"), OD_T("Body "), bodyNumber);

          OdTvEntityId entityId = pTvModel->appendEntity(entityName);
          entityId.openObject(OdTv::kForWrite)->setColor(OdTvColorDef(r, g, b));

          // Do rendering
          wd.setTargetDisplayMode(OdTvGeometryData::kRender);
          wd.setTvEntity(entityId);
          brepRenderer.draw(&wd, BrepRenderModes::kShells, 0);

          wd.setTargetDisplayMode(OdTvGeometryData::kWireframe);
          wd.setColorForByLayer(OdCmEntityColor(0, 0, 0));
          brepRenderer.draw(&wd, BrepRenderModes::kEdges, 0);
          //brepRenderer.draw(&wd, BrepRenderModes::kIsolines, 0);
          wd.setColorForByLayer(OdCmEntityColor::kNone);

          bodyNumber++;
        }
        OdTvDatabaseUtils::createDeviceAndView(tvDbId, tvModelId, OdTvGsView::kGouraudShaded);

      }

      //set units
      pTvModel->setUnits(tvUnits, tvUnits == OdTv::kUserDefined ? addUnitCoefToMeters : 1.);

      timing.endVectorizing();
    }
  }
  catch (...)
  {
    if (rc)
      *rc = tvInternal;
    timing.endVectorizing();
  }

  // Delete the converters
  for (OdUInt32 f = 0; f < out.size(); ++f)
    ABDeleteConverter(out[f]);

  timing.endTotal();

  if (pProfileRes)
  {
    pProfileRes->setImportTime(OdInt64((timing.getTotalTime() - timing.getVectorizingTime()) * 1000.));
    pProfileRes->setVectorizingTime(OdInt64(timing.getVectorizingTime() * 1000.));
    pProfileRes->setTvTime(OdInt64(wd.getTotalTime() * 1000.));
  }

  return tvDbId;
}

OdTvDatabaseId OdTvVisualizeAcisFiler::generate(OdTvFilerTimeProfiling* pProfileRes) const
{
  OdTvDatabaseId tvDbId;

  // does nothing
  return tvDbId;
}

OdTvModelId OdTvVisualizeAcisFiler::appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes /*= NULL*/, OdTvResult* rc /*= NULL*/) const
{
  if (rc)
    *rc = tvNotImplementedYet;

  return OdTvModelId();
}

OdTvModelId OdTvVisualizeAcisFiler::appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes /*= NULL*/, OdTvResult* rc /*= NULL*/) const
{
  if (rc)
    *rc = tvNotImplementedYet;

  return OdTvModelId();
}

OdTvModelId OdTvVisualizeAcisFiler::appendFrom(const OdTvDatabaseId& databaseId, const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes /*= NULL*/, OdTvResult* rc /*= NULL*/) const
{
  if (rc)
    *rc = tvNotImplementedYet;

  return OdTvModelId();
}

//***************************************************************************//
// 'OdTvVisualizeAcisFilerModule' methods implementation
//***************************************************************************//

ODRX_DEFINE_DYNAMIC_MODULE(OdTvVisualizeAcisFilerModule);

void OdTvVisualizeAcisFilerModule::initApp()
{
  // initialize the Visualize SDK
  odTvInitialize();

}

void OdTvVisualizeAcisFilerModule::uninitApp()
{
  // Uninitialize the Visualize SDK
  odTvUninitialize();
}

OdTvVisualizeFilerPtr OdTvVisualizeAcisFilerModule::getVisualizeFiler() const
{
  OdTvVisualizeFilerPtr pAcisFiler = new OdTvVisualizeAcisFiler();

  return pAcisFiler;
}
