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

#include "RxObject.h"
#include "StaticRxObject.h"
#include "DynamicLinker.h"

#include "ColorMapping.h"
#include "TvFactory.h"
#include "TvModel.h"
#include "TvFilerTimer.h"
#include "TvModuleNames.h"
#include "TvDatabaseCleaner.h"
#include "TvDatabaseUtils.h"

#include "Dwf2Visualize.h"

#include "DwfDatabase.h"
#include "DwfGiContext.h"
#include "DwfObjectImpl.h"
#include "DwfGsLayoutHelper.h"

#ifndef ODA_UNIXOS
#define pathChar '\\'
#define oldPathChar '/'
#else
#define pathChar '/'
#define oldPathChar '\\'
#endif

#define NO_NAME_DATABASE OD_T("NoNameDwfDatabase")

OdTv::Units getUnits(OdDwfViewPtr pView, OdTv::Units defaultUnits, double& additionalConvCoeffToMeters)
{
  OdTv::Units tvUnits = defaultUnits;
  additionalConvCoeffToMeters = 1.;
  OdDb::UnitsValue dbUnits = OdDb::kUnitsUndefined;

  if (!pView->isModelLayout())
  {
    OdDwfLayoutViewPtr pLayoutView = pView;
    if (pLayoutView.isNull())
      return tvUnits;

    switch (pLayoutView->getUnits())
    {
    case OdDb::kUnitsUndefined:
      tvUnits = defaultUnits;
      break;
    case OdDb::kUnitsInches:
      tvUnits = OdTv::kInches;
      break;
    case OdDb::kUnitsFeet:
      tvUnits = OdTv::kFeet;
      break;
    case OdDb::kUnitsMiles:
      tvUnits = OdTv::kMiles;
      break;
    case OdDb::kUnitsMillimeters:
      tvUnits = OdTv::kMillimeters;
      break;
    case OdDb::kUnitsCentimeters:
      tvUnits = OdTv::kCentimeters;
      break;
    case OdDb::kUnitsMeters:
      tvUnits = OdTv::kMeters;
      break;
    case OdDb::kUnitsKilometers:
      tvUnits = OdTv::kKilometers;
      break;
    case OdDb::kUnitsMicroinches:
      tvUnits = OdTv::kMicroInches;
      break;
    case OdDb::kUnitsMils:
      tvUnits = OdTv::kMils;
      break;
    case OdDb::kUnitsYards:
      tvUnits = OdTv::kYards;
      break;
    case OdDb::kUnitsAngstroms:
      tvUnits = OdTv::kUserDefined;
      additionalConvCoeffToMeters = 1.0e-10;
    case OdDb::kUnitsNanometers:
      tvUnits = OdTv::kUserDefined;
      additionalConvCoeffToMeters = 1.0e-9;
    case OdDb::kUnitsMicrons:
      tvUnits = OdTv::kMicrometers;
      break;
    case OdDb::kUnitsDecimeters:
      tvUnits = OdTv::kUserDefined;
      additionalConvCoeffToMeters = 0.1;
      break;
    case OdDb::kUnitsDekameters:
      tvUnits = OdTv::kUserDefined;
      additionalConvCoeffToMeters = 10.;
      break;
    case OdDb::kUnitsHectometers:
      tvUnits = OdTv::kUserDefined;
      additionalConvCoeffToMeters = 100.;
    case OdDb::kUnitsGigameters:
      tvUnits = OdTv::kUserDefined;
      additionalConvCoeffToMeters = 1.0e9;
    case OdDb::kUnitsAstronomical:
      tvUnits = OdTv::kUserDefined;
      additionalConvCoeffToMeters = 149597870700;
    case OdDb::kUnitsLightYears:
      tvUnits = OdTv::kUserDefined;
      additionalConvCoeffToMeters = 94607304725808800;
    case OdDb::kUnitsParsecs:
      tvUnits = OdTv::kUserDefined;
      additionalConvCoeffToMeters = 3.085677581 * 10000000000000000; //10^16
    case OdDb::kUnitsUSSurveyFeet:
      tvUnits = OdTv::kUserDefined;
      additionalConvCoeffToMeters = 0.3048 / 0.999998;
    case OdDb::kUnitsUSSurveyInch:
      tvUnits = OdTv::kUserDefined;
      additionalConvCoeffToMeters = 0.0254 / 0.999998;
    case OdDb::kUnitsUSSurveyYard:
      tvUnits = OdTv::kUserDefined;
      additionalConvCoeffToMeters = 0.9144 / 0.999998;
    case OdDb::kUnitsUSSurveyMile:
      tvUnits = OdTv::kUserDefined;
      additionalConvCoeffToMeters = 1609.344 / 0.999998;
    }
  }
  else
  {
    OdDwfModelViewPtr pLayoutView = pView;

    const OdString sUnitName = pLayoutView->unitName();
    if (sUnitName == L"mm")
      tvUnits = OdTv::kMillimeters;
    else if (sUnitName == L"cm")
      tvUnits = OdTv::kCentimeters;
    else if (sUnitName == L"m")
      tvUnits = OdTv::kMeters;
    else if (sUnitName == L"in")
      tvUnits = OdTv::kInches;
    else if (sUnitName == L"ft")
      tvUnits = OdTv::kFeet;
  }

  return tvUnits;
}

class OdTvVisualizeDwfFilerSourceFromDb : public OdTvVisualizeDwfFilerSource
{
public:
  OdTvVisualizeDwfFilerSourceFromDb(OdDbBaseDatabase *pDatabase) : m_Database(pDatabase) {}

  virtual OdDwfDatabasePtr getDb() ODRX_OVERRIDE
  {
    return m_Database;
  }

  virtual OdString getFilename() ODRX_OVERRIDE
  {
    if (!m_Database.isNull())
    {
      OdString fileName = m_Database->getFilename();
      if (!fileName.isEmpty())
        return fileName;
    }

    return NO_NAME_DATABASE;
  }

private:
  OdDwfDatabasePtr m_Database;
};

class OdTvVisualizeDwfFilerSourceFromStream : public OdTvVisualizeDwfFilerSource
{
public:
  OdTvVisualizeDwfFilerSourceFromStream(OdStreamBufPtr pBuffer, OdTvFilerTimeProfiling* pProfileRes)
    :m_initTime(0)
  {
    initialize(pBuffer, pProfileRes);
  }

  OdDwfDatabasePtr getDb() ODRX_OVERRIDE
  {
    return svcs.readFile(m_StreamBuf);
  }

  virtual OdString getFilename() ODRX_OVERRIDE
  {
    OdString strFileName = m_StreamBuf->fileName();
    if (strFileName.isEmpty())
      return NO_NAME_DATABASE;

    //generate name for the stream file
    return OdTvDatabaseUtils::getFileNameFromPath(strFileName);
  };

  void releaseStream()
  {
    if (!m_StreamBuf.isNull())
      m_StreamBuf.release();
  }

  virtual double getInitTime() 
  { 
    return m_initTime; 
  }

protected:
  OdTvVisualizeDwfFilerSourceFromStream()
  {}

  void initialize(OdStreamBufPtr pBuffer, OdTvFilerTimeProfiling* pProfileRes)
  {
    m_StreamBuf = pBuffer;
  };

private:
  OdStaticRxObject<OdTvDwfServices> svcs;
  OdStreamBufPtr m_StreamBuf;

protected:
  double m_initTime;

};


class OdTvVisualizeDwfFilerSourceFromFile : public OdTvVisualizeDwfFilerSourceFromStream
{
public:
  bool initialize(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult *rc = NULL)
  {
    mFilePath = filePath;

    OdTvFilerTimer timing(needTimer(pProfileRes));
    timing.startTotal();

    OdStreamBufPtr pStreamBuf = odrxSystemServices()->createFile(filePath);
    if (pStreamBuf.isNull())
    {
      if (rc)
        *rc = tvInvalidFilePath;
      return false;
    }
    OdTvVisualizeDwfFilerSourceFromStream::initialize(pStreamBuf, NULL);

    timing.endTotal();
    m_initTime = timing.getTotalTime();

    return true;
  };

  virtual OdString getFilename() ODRX_OVERRIDE
  {
    //generate name for the stream file
    return OdTvDatabaseUtils::getFileNameFromPath(mFilePath);
  };

private:
  OdString mFilePath;
};

using namespace DWF2Visualize;

OdTvVisualizeDwfFilerProperties::OdTvVisualizeDwfFilerProperties() 
  :m_background(ODRGB(0, 0, 0)),
  m_pPalette(0),
  m_pCallback(0),
  m_flags(kClearEmptyObjects),
  m_importRect(0, 0, 0, 0)
{
}

OdRxDictionaryPtr OdTvVisualizeDwfFilerProperties::createObject()
{
  return OdRxObjectImpl<OdTvVisualizeDwfFilerProperties, OdRxDictionary>::createObject();
}

OdTvVisualizeDwfFilerProperties::~OdTvVisualizeDwfFilerProperties()
{
}

namespace DWF2Visualize {
ODRX_DECLARE_PROPERTY(BackgroundColor)
ODRX_DECLARE_PROPERTY(Palette)
ODRX_DECLARE_PROPERTY(DCRect)
ODRX_DECLARE_PROPERTY(ObjectNaming)
ODRX_DECLARE_PROPERTY(StoreSourceObjects)
ODRX_DECLARE_PROPERTY(ClearEmptyObjects)
ODRX_DECLARE_PROPERTY(FeedbackForChooseCallback)
ODRX_DECLARE_PROPERTY(AppendTransform)
ODRX_DECLARE_PROPERTY(ConvertIndexedToRGB)

ODRX_BEGIN_DYNAMIC_PROPERTY_MAP(OdTvVisualizeDwfFilerProperties);
ODRX_GENERATE_PROPERTY(BackgroundColor)
ODRX_GENERATE_PROPERTY(Palette)
ODRX_GENERATE_PROPERTY(DCRect)
ODRX_GENERATE_PROPERTY(ObjectNaming)
ODRX_GENERATE_PROPERTY(StoreSourceObjects)
ODRX_GENERATE_PROPERTY(ClearEmptyObjects)
ODRX_GENERATE_PROPERTY(FeedbackForChooseCallback)
ODRX_GENERATE_PROPERTY(AppendTransform)
ODRX_GENERATE_PROPERTY(ConvertIndexedToRGB)
ODRX_END_DYNAMIC_PROPERTY_MAP(OdTvVisualizeDwfFilerProperties);

ODRX_DEFINE_PROPERTY_METHODS(BackgroundColor, OdTvVisualizeDwfFilerProperties, getBackgroundColor, setBackgroundColor, getIntPtr);
ODRX_DEFINE_PROPERTY_METHODS(Palette, OdTvVisualizeDwfFilerProperties, getPalette, setPalette, getIntPtr);
ODRX_DEFINE_PROPERTY_METHODS(DCRect, OdTvVisualizeDwfFilerProperties, getDCRect, setDCRect, getIntPtr);
ODRX_DEFINE_PROPERTY_METHODS(ObjectNaming, OdTvVisualizeDwfFilerProperties, getObjectNaming, setObjectNaming, getBool);
ODRX_DEFINE_PROPERTY_METHODS(StoreSourceObjects, OdTvVisualizeDwfFilerProperties, getStoreSourceObjects, setStoreSourceObjects, getBool);
ODRX_DEFINE_PROPERTY_METHODS(ClearEmptyObjects, OdTvVisualizeDwfFilerProperties, getClearEmptyObjects, setClearEmptyObjects, getBool);
ODRX_DEFINE_PROPERTY_METHODS(FeedbackForChooseCallback, OdTvVisualizeDwfFilerProperties, getFeedbackForChooseCallback, setFeedbackForChooseCallback, getIntPtr);
ODRX_DEFINE_PROPERTY_METHODS(AppendTransform, OdTvVisualizeDwfFilerProperties, getAppendTransform, setAppendTransform, getIntPtr);
ODRX_DEFINE_PROPERTY_METHODS(ConvertIndexedToRGB, OdTvVisualizeDwfFilerProperties, getConvertIndexedToRGB, setConvertIndexedToRGB, getBool);
}

void OdTvVisualizeDwfFilerProperties::setBackgroundColor(OdIntPtr ptr)
{
  ODCOLORREF* pColor = (ODCOLORREF*)(ptr);
  if (!pColor)
  {
    ODA_ASSERT(false);
  }
  m_background = *pColor;
}

OdIntPtr OdTvVisualizeDwfFilerProperties::getBackgroundColor() const
{
  return (OdIntPtr)(&m_background);
}

void OdTvVisualizeDwfFilerProperties::setPalette(OdIntPtr palette)
{
  const ODCOLORREF* pPalette = (const ODCOLORREF*)(palette);

  m_pPalette = pPalette;
}

OdIntPtr OdTvVisualizeDwfFilerProperties::getPalette() const
{
  return (OdIntPtr)(m_pPalette);
}

void OdTvVisualizeDwfFilerProperties::setDCRect(OdIntPtr rect)
{
  OdTvDCRect* pRect = (OdTvDCRect*)(rect);
  if (!pRect)
  {
    ODA_ASSERT(false);
  }

  m_importRect = *pRect;
}

OdIntPtr OdTvVisualizeDwfFilerProperties::getDCRect() const
{
  return (OdIntPtr)(&m_importRect);
}

void OdTvVisualizeDwfFilerProperties::setFeedbackForChooseCallback(OdIntPtr pCallback)
{
  m_pCallback = (OdTvFeedbackForChooseCallback)pCallback;
}

OdIntPtr OdTvVisualizeDwfFilerProperties::getFeedbackForChooseCallback() const
{
  return (OdIntPtr)m_pCallback;
}

void OdTvVisualizeDwfFilerProperties::setAppendTransform(OdIntPtr pTransform)
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

OdIntPtr OdTvVisualizeDwfFilerProperties::getAppendTransform() const
{
  return (OdIntPtr)(&m_appendTransform);
}

OdTvVisualizeDwfFiler::OdTvVisualizeDwfFiler() : m_properties(OdTvVisualizeDwfFilerProperties::createObject())
{
}

OdTvDatabaseId OdTvVisualizeDwfFiler::loadFrom(OdDbBaseDatabase *pDatabase, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeDwfFilerSourceFromDb dl(pDatabase);
  return loadFrom(&dl, pProfileRes, rc);
}

OdTvDatabaseId OdTvVisualizeDwfFiler::loadFrom(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeDwfFilerSourceFromStream dl(pBuffer, pProfileRes);
  return loadFrom(&dl, pProfileRes, rc);
}

OdTvDatabaseId OdTvVisualizeDwfFiler::loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeDwfFilerSourceFromFile dl;
  if (dl.initialize(filePath, pProfileRes, rc))
  {
    return loadFrom(&dl, pProfileRes, rc);
  }
  return OdTvDatabaseId();
}

OdTvDatabaseId OdTvVisualizeDwfFiler::generate(OdTvFilerTimeProfiling* pProfileRes) const
{
  OdTvDatabaseId tvDbId;

  // does nothing
  return tvDbId;
}

OdTvModelId OdTvVisualizeDwfFiler::appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase *pDatabase, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeDwfFilerSourceFromDb dl(pDatabase);
  return appendFrom(databaseId, &dl, pProfileRes, rc);
}

OdTvModelId OdTvVisualizeDwfFiler::appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeDwfFilerSourceFromStream dl(pBuffer, pProfileRes);
  return appendFrom(databaseId, &dl, pProfileRes, rc);
}

OdTvModelId OdTvVisualizeDwfFiler::appendFrom(const OdTvDatabaseId& databaseId, const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeDwfFilerSourceFromFile dl;
  return dl.initialize(filePath, pProfileRes, rc) ? appendFrom(databaseId, &dl, pProfileRes, rc) : OdTvModelId();
}

OdTvDatabaseId OdTvVisualizeDwfFiler::loadFrom(OdTvVisualizeDwfFilerSource *pDatabaseSource, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
#ifdef OD_TV_MEASURE_PARTIAL
  clock_t timeStart1 = clock();
  clock_t timeEnd1 = 0;
  clock_t timeStart2 = 0;
  OdUInt64 memUsage = 0;
#endif

  ODCOLORREF background = *((ODCOLORREF*)m_properties->getBackgroundColor());

  OdTvDatabaseId tvDbId;

  if (rc)
    *rc = tvOk;

  //check that time profiling is need
  bool bUseTimeProfiling = needTimer(pProfileRes);
  double dbReadingTime = 0.;
  double tvDbExternalTiming = 0.;
  double tvDbInternalTiming = 0.;

  //prepare timing object
  OdTvFilerTimer timing(bUseTimeProfiling);
  timing.startTotal();
  timing.startMisc();

  // Gs module
  OdGsModulePtr pGsModule;
  std::set<OdString> spacesNames;
  OdString moduleName;
  ::odrxDynamicLinker()->loadModule(OdDwfDbModuleName, false);
  try
  {
    OdDwfDatabasePtr pDb = pDatabaseSource->getDb();
    OdDbBaseDatabasePEPtr pDbPE = OdDbBaseDatabasePE::cast(pDb);

    timing.endMisc();
    dbReadingTime = timing.getMiscTime() + pDatabaseSource->getInitTime();

    if (!pDb.isNull())
    {
      //get drawing folder
      OdString dwfPath = pDb->getFilename();
      dwfPath.replace(oldPathChar, pathChar);
      dwfPath = dwfPath.left(dwfPath.reverseFind(pathChar));

      //ask about what to load
      OdTvFilerFeedbackForChooseObject filerFeedbackForChooseObject(OD_T("Choose spaces for import"));
#ifdef OD_TV_MEASURE_PARTIAL
      timeEnd1 = clock();
#endif
      bool bCanceled = false;
      getChoosedSpaces(pDb, filerFeedbackForChooseObject, bCanceled);
      if (bCanceled)
      {
        if (rc)
          *rc = tvFilerEmptyInternalDatabase;
        pDb = NULL;

        odrxDynamicLinker()->unloadUnreferenced();
        return OdTvDatabaseId();
      }
#ifdef OD_TV_MEASURE_PARTIAL
      timeStart2 = clock();
#endif

      //remember active layout id
      OdDwfObjectId activeLayoutId = pDb->currentLayoutId();

      bool bHavePaperSpace = false;
      OdDwfObjectIdArray layoutIds = pDb->layoutIds();
      for (OdDwfObjectIdArray::iterator iter = layoutIds.begin(); iter != layoutIds.end(); ++iter)
      {
        OdDwfViewPtr pView = OdDwfView::cast(iter->getObject());
        if (pView.isNull())
          continue;
        if (!pView->isModelLayout())
        {
          bHavePaperSpace = true;
          break;
        }
      }

      timing.startVectorizing();

      pGsModule = ::odrxDynamicLinker()->loadModule(OdTvVisualizeDeviceModuleName, false);
      if (pGsModule.isNull())
      {
        if (rc)
          *rc = tvMissingVisualizeDeviceModule;
        return tvDbId;
      }

      //create empty tv database.
      OdTvFactoryId tvFactoryId = odTvGetFactory();
      tvDbId = tvFactoryId.createDatabase();

      //SEA name for ModelSpace
      OdString modelSpaceName = OdString::kEmpty;

      //SEA initialize cache and switch it to the "write only" mode
      ExGsVisualizeDeviceCache deviceCache;
      deviceCache.m_bApplyCacheData = false;
      //SEA cache layout helper to share GsModel

      //run over all spaces (layouts), which was decided to load
      unsigned int tvDevicesCount = 0;
      for (OdDwfObjectIdArray::iterator iter = layoutIds.begin(); iter != layoutIds.end(); ++iter)
      {
        OdDwfViewPtr pView = OdDwfView::cast(iter->getObject());
        if (pView.isNull())
          continue;

        if (!filerFeedbackForChooseObject.find(OdTvFilerFeedbackItemForChoose(pView->getName(), true)))
        {
          continue;
        }

        //get units from DWF view
        double addUnitCoefToMeters;
        OdTv::Units tvUnits = getUnits(pView, OdTv::kInches, addUnitCoefToMeters);

        //update layout in the database
        pDbPE->setCurrentLayout(pDb, pView->getName());

        //create Ex Visualize device
        OdGsDevicePtr pDevice = pGsModule->createDevice();

        // setup ExVisualize device properties
        OdRxDictionaryPtr pProperties = pDevice->properties();
        OdTvGsDeviceId activeTvDeviceId = OdTvGsDeviceId();
        setupExVisualizeDeviceProp(pProperties, tvDbId, bUseTimeProfiling, modelSpaceName, dwfPath, m_properties, deviceCache, activeTvDeviceId, bHavePaperSpace);

        //setup context
        OdGiContextForDwfDatabasePtr pContext = OdGiContextForDwfDatabase::createObject();
        pContext->setDatabase(OdDwfDatabase::cast(pDb));
        pContext->enableGsModel(true);

        //setup layout
        OdDwfGsLayoutHelperPtr pLayoutHelper = OdDwfGsLayoutHelper::setupLayoutView(*iter, pDevice, pContext);
        //set the palette
        const ODCOLORREF* palette = (const ODCOLORREF*)m_properties->getPalette();
        bool bDefaultPalette = false;
        if (palette == 0)
        {
          bDefaultPalette = true;
          palette = odcmAcadPalette(background);  // black background
        }

        OdArray<ODCOLORREF, OdMemoryAllocator<ODCOLORREF> > pPalCpy;
        pPalCpy.insert(pPalCpy.begin(), palette, palette + 256);

        if (bDefaultPalette)
          pPalCpy[0] = background;
        pDevice->setLogicalPalette(pPalCpy.asArrayPtr(), 256);

        //set the background
        pDevice->setBackgroundColor(background);
        pContext->setPaletteBackground(background);

        //set view border properties
        setViewBorderProperties(pDevice.get(), pPalCpy[7]);

        //call onsize
        OdTvDCRect* pRect = (OdTvDCRect*)m_properties->getDCRect();
        if (pRect && (pRect->xmax > 0 || pRect->xmin > 0 || pRect->ymax > 0 || pRect->ymin > 0))
        {
          OdGsDCRect  gsRect(pRect->xmin, pRect->xmax, pRect->ymin, pRect->ymax);
          pDevice->onSize(gsRect);
        }

        //main call - vectorization into the tv database
        pLayoutHelper->update();

        if (bUseTimeProfiling)
        {
#if !defined(__APPLE__)
          if (pProperties->has(OD_T("TvElapsedTime")))
          {
            tvDbInternalTiming = OdRxVariantValue(pProperties->getAt(OD_T("TvElapsedTime")).get())->getDouble();
          }
#endif
        }

        //we should update the state of the device cache marked it to use the cached data during next vectorizing
        if (pProperties->has(OD_T("DeviceCache")))
        {
          deviceCache.m_bApplyCacheData = true;
          OdIntPtr ptr = OdRxVariantValue(pProperties->getAt(OD_T("DeviceCache")).get())->getIntPtr();
        }

        //setup active view and the relation between views in paper space case (here we know that it will be only 1 device)
        if (tvDbId.isValid())
        {
          timing.startMisc();

          OdTvDevicesIteratorPtr pDevicesIterator = tvDbId.openObject()->getDevicesIterator();
          if (!pDevicesIterator.isNull()) // here we have O(n^2) but ut us not a problem
          {
            unsigned int nCount = 0;
            while (!pDevicesIterator->done())
            {
              OdTvGsDeviceId tvDeviceId = pDevicesIterator->getDevice();
              if (nCount == tvDevicesCount)
              {
                if (*iter == pDb->currentLayoutId() && !tvDeviceId.isNull())
                  tvDeviceId.openObject(OdTv::kForWrite)->setActive(true);

                if (!tvDeviceId.isNull())
                  tvDeviceId.openObject(OdTv::kForWrite)->setOption(OdTvGsDevice::kUseVisualStyles, true);

                setupTvViews(pView, pLayoutHelper, tvDeviceId, pPalCpy[7], tvUnits, addUnitCoefToMeters, &modelSpaceName);
                break;
              }
              nCount++;
              pDevicesIterator->step();
            }
          }

          timing.endMisc();
          tvDbExternalTiming += timing.getMiscTime();
        }

        tvDevicesCount++;
      } // eo for...

      timing.startMisc();

      if (tvDbId.isValid() && m_properties->getClearEmptyObjects())
        OdTvDatabaseCleaner::cleanTvDatabase(tvDbId);

      //change a few settings of conceptual visual style from fast to DWG-like
      if (tvDbId.isValid())
      {
        OdTvVisualStyleId visId = tvDbId.openObject()->findVisualStyle(OD_T("Conceptual"));
        OdTvVisualStylePtr pVisStyle = visId.openObject(OdTv::kForWrite);
        if (!pVisStyle.isNull())
        {
          pVisStyle->setOption(OdTvVisualStyleOptions::kEdgeModel, (OdInt32)OdTvVisualStyleOptions::kFacetEdges);
          pVisStyle->setOption(OdTvVisualStyleOptions::kEdgeStyles, (OdInt32)OdTvVisualStyleOptions::kSilhouette);
          pVisStyle->setOption(OdTvVisualStyleOptions::kDisplayStyles, (OdInt32)OdTvVisualStyleOptions::kBackgrounds);
        }
      }

      timing.endMisc();
      tvDbExternalTiming += timing.getMiscTime();

      timing.endVectorizing();
#ifdef OD_TV_MEASURE_PARTIAL
      memUsage = GetMemoryUsageInternalInfo(0);
#endif
      moduleName = pGsModule->moduleName();
    }
    else
    {
      if (rc)
        *rc = tvFilerEmptyInternalDatabase;
    }
  }
  catch (...)
  {
    if (rc)
      *rc = tvInternal;

    timing.endVectorizing();

    // unload gs module
    if (pGsModule.get())
      pGsModule.release();

    odrxDynamicLinker()->unloadUnreferenced();
    throw;
  }

  // unload gs module
  if (pGsModule.get())
    pGsModule.release();
  if (!moduleName.isEmpty())
    odrxDynamicLinker()->unloadModule(moduleName);

  timing.startMisc();

  // save filename to database user data
  OdTvDatabaseUtils::writeFileNameToTvDatabase(tvDbId, pDatabaseSource->getFilename());

  timing.endMisc();
  tvDbExternalTiming += timing.getMiscTime();

  odrxDynamicLinker()->unloadUnreferenced();

  timing.endTotal();

  if (pProfileRes)
  {
    pProfileRes->setImportTime(OdInt64(dbReadingTime * 1000.));
    pProfileRes->setVectorizingTime(OdInt64((timing.getVectorizingTime()) * 1000.));
#if !defined(__APPLE__)
    pProfileRes->setTvTime(OdInt64((tvDbInternalTiming + tvDbExternalTiming) * 1000.));
#endif
  }
#ifdef OD_TV_MEASURE_PARTIAL
  clock_t timeEnd2 = clock();
  wchar_t buff[256];
  clock_t timeDiff = timeEnd2 - timeStart2 + (timeEnd1 - timeStart1);
  wsprintf(buff, L"NormalMode:\nMemory %ld (%ld MB)\nTime %ld (%ld sec)", memUsage, memUsage / (1024 * 1024), timeDiff, timeDiff / 1000);
  MessageBox(NULL, buff, L"Normal MODE", MB_OK);
#endif
  return tvDbId;
}


OdTvModelId OdTvVisualizeDwfFiler::appendFrom(const OdTvDatabaseId& databaseId, OdTvVisualizeDwfFilerSource *pDatabaseSource, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvModelId tvModelId;

  if (rc)
    *rc = tvOk;

  //check that we are in the real append mode
  OdTvGsDeviceId activeTvGsDeviceId;
  {
    OdTvDatabasePtr pTvDb = databaseId.openObject();
    pTvDb->disableInternalNotifications();
    OdTvDevicesIteratorPtr devicesIteratorPtr = pTvDb->getDevicesIterator();
    while (!devicesIteratorPtr->done())
    {
      activeTvGsDeviceId = devicesIteratorPtr->getDevice();
      if (activeTvGsDeviceId.openObject()->getActive())
        break;
      devicesIteratorPtr->step();
    }
  }

  //get palette, background and device size
  ODCOLORREF background = ODRGB(0, 0, 0);
  OdTvDCRect rect(0, 0, 0, 0);
  OdArray<ODCOLORREF, OdMemoryAllocator<ODCOLORREF> > pPalCpy;

  if (!activeTvGsDeviceId.isNull())
  {
    OdTvGsDevicePtr pTvDevice = activeTvGsDeviceId.openObject();

    background = pTvDevice->getBackgroundColor();
    pTvDevice->getSize(rect);

    int nColors;
    const ODCOLORREF* pPalette = pTvDevice->getLogicalPalette(nColors);
    if (nColors >= 256)
      pPalCpy.insert(pPalCpy.begin(), pPalette, pPalette + 256);
    else
    {
      pPalCpy.insert(pPalCpy.begin(), pPalette, pPalette + nColors);
      pPalCpy.insert(pPalCpy.begin() + nColors, 256 - nColors, ODRGB(0, 0, 0));
    }
  }
  else
  {
    background = *((ODCOLORREF*)m_properties->getBackgroundColor());
    OdTvDCRect* pRect = (OdTvDCRect*)m_properties->getDCRect();
    if (pRect)
      rect = *pRect;

    const ODCOLORREF* palette = (const ODCOLORREF*)m_properties->getPalette();
    bool bDefaultPalette = false;
    if (palette == 0)
    {
      bDefaultPalette = true;
      palette = odcmAcadPalette(background);  // black background
    }

    pPalCpy.insert(pPalCpy.begin(), palette, palette + 256);

    if (bDefaultPalette)
      pPalCpy[0] = background;
  }

  //collcet current models and blocks
  std::set<OdTvGsViewId> foreignViews;
  std::set<OdTvModelId> foreignModels;
  std::set<OdTvBlockId> foreignBlocks;
  OdTvDatabaseUtils::collectViewsModelsAndBlocks(databaseId, foreignViews, foreignModels, foreignBlocks);

  //check that time profiling is need
  bool bUseTimeProfiling = false;
  if (pProfileRes)
    bUseTimeProfiling = true;

  double dbReadingTime = 0.;
  double tvDbExternalTiming = 0.;
  double tvDbInternalTiming = 0.;

  //prepare timing object
  OdTvFilerTimer timing(bUseTimeProfiling);
  timing.startTotal();
  timing.startMisc();

  // Gs module
  OdGsModulePtr pGsModule;
  OdString moduleName;
  ::odrxDynamicLinker()->loadModule(OdDwfDbModuleName, false);

  try
  {
    OdDwfDatabasePtr pDb = pDatabaseSource->getDb();
    OdDbBaseDatabasePEPtr pDbPE = OdDbBaseDatabasePE::cast(pDb);

    timing.endMisc();
    dbReadingTime = timing.getMiscTime() + pDatabaseSource->getInitTime();

    if (!pDb.isNull())
    {
      //get drawing folder
      OdString dwgPath = pDb->getFilename();
      dwgPath.replace(oldPathChar, pathChar);
      dwgPath = dwgPath.left(dwgPath.reverseFind(pathChar));

      //set active layout as model space
      OdDwfObjectIdArray layoutIds = pDb->layoutIds();
      for (OdDwfObjectIdArray::iterator iter = layoutIds.begin(); iter != layoutIds.end(); ++iter)
      {
        OdDwfViewPtr pView = OdDwfView::cast(iter->getObject());
        if (pView.isNull())
          continue;
        if (pView->isModelLayout())
        {
          pDbPE->setCurrentLayout(pDb, pView->getName());
          break;
        }
      }

      OdDwfViewPtr pCurrentView = OdDwfView::cast(pDb->currentLayoutId().openObject());
      if(pCurrentView.isNull() || !pCurrentView->isModelLayout())
      {
        if (rc)
          *rc = tvNullObjectPtr;
        return tvModelId;
      }

      //get units from DWF view
      double addUnitCoefToMeters;
      OdTv::Units tvUnits = getUnits(pCurrentView, OdTv::kInches, addUnitCoefToMeters);

      timing.startVectorizing();

      pGsModule = ::odrxDynamicLinker()->loadModule(OdTvVisualizeDeviceModuleName, false);
      if (pGsModule.isNull())
      {
        if (rc)
          *rc = tvMissingVisualizeDeviceModule;
        return tvModelId;
      }

      //SEA initialize cache and switch it to the "write only" mode
      ExGsVisualizeDeviceCache deviceCache;
      deviceCache.m_bApplyCacheData = false;

      //create ExVisualize device
      OdGsDevicePtr pDevice = pGsModule->createDevice();

      // setup ExVisualize device properties
      OdRxDictionaryPtr pProperties = pDevice->properties();
      OdString modelSpaceName = OdTvDatabaseUtils::generateModelName(databaseId, pDatabaseSource->getFilename());
      setupExVisualizeDeviceProp(pProperties, databaseId, bUseTimeProfiling, modelSpaceName, dwgPath, m_properties, deviceCache, activeTvGsDeviceId, false);

      //we don't need to setup extents inside appendFrom since we can have additional units transform matrix here
      if (pProperties->has(OD_T("DisableSetingExtents")))
        pProperties->putAt(OD_T("DisableSetingExtents"), OdRxVariantValue(true));

      //create dwg context
      OdGiContextForDwfDatabasePtr pContext = OdGiContextForDwfDatabase::createObject();
      pContext->enableGsModel(true);
      pContext->setDatabase(pDb);

      //setup layout
      OdGsDevicePtr pLayoutHelper = OdDwfGsLayoutHelper::setupLayoutView(pDb->currentLayoutId(), pDevice, pContext);

      //setup palette, background and device size
      //a.palette
      pDevice->setLogicalPalette(pPalCpy.asArrayPtr(), 256);

      //b. background
      pDevice->setBackgroundColor(background);
      pContext->setPaletteBackground(background);

      //c. call onsize
      if (rect.xmax > 0 || rect.xmin > 0 || rect.ymax > 0 || rect.ymin > 0)
      {
        OdGsDCRect gsRect(rect.xmin, rect.xmax, rect.ymin, rect.ymax);
        pDevice->onSize(gsRect);
      }

      //perform vectorization
      pLayoutHelper->update();

      if (bUseTimeProfiling)
      {
#if !defined(__APPLE__)
        if (pProperties->has(OD_T("TvElapsedTime")))
        {
          tvDbInternalTiming = OdRxVariantValue(pProperties->getAt(OD_T("TvElapsedTime")).get())->getDouble();
        }
#endif
      }

      //we should update the state of the device cache marked it to use the cached data during next vectorizing
      if (pProperties->has(OD_T("DeviceCache")))
      {
        deviceCache.m_bApplyCacheData = true;
        OdIntPtr ptr = OdRxVariantValue(pProperties->getAt(OD_T("DeviceCache")).get())->getIntPtr();
      }

      if (databaseId.isValid())
      {
        timing.startMisc();

        {
          OdTvDatabasePtr pTvDb = databaseId.openObject();
          tvModelId = pTvDb->findModel(modelSpaceName);
        }

        //clear empty objects (always)
        OdTvDatabaseId& tvDvId = const_cast<OdTvDatabaseId&>(databaseId);
        OdTvDatabaseCleaner::cleanTvDatabaseForAppend(tvDvId, foreignViews, foreignModels, foreignBlocks);

        //apply transform if need 
        OdTvMatrix* pTransfrom = (OdTvMatrix*)m_properties->getAppendTransform();
        if (pTransfrom)
        {
          OdTvDatabaseId& tvDvId = const_cast<OdTvDatabaseId&>(databaseId);
          OdTvDatabaseUtils::applyTransformToTheModel(tvDvId, modelSpaceName, *pTransfrom);
        }

        //apply units
        if (!tvModelId.isNull())
        {
          OdTvModelPtr pModel = tvModelId.openObject(OdTv::kForWrite);
          if (!pModel.isNull())
            pModel->setUnits(tvUnits, tvUnits == OdTv::kUserDefined ? addUnitCoefToMeters : 1.);
        }

        timing.endMisc();
        tvDbExternalTiming = timing.getMiscTime();
      }

      timing.endVectorizing();

      moduleName = pGsModule->moduleName();
    }
    else
    {
      if (rc)
        *rc = tvFilerEmptyInternalDatabase;
    }

  }
  catch (...)
  {
    if (rc)
      *rc = tvInternal;

    timing.endVectorizing();

    // unload gs module
    if (pGsModule.get())
      pGsModule.release();

    odrxDynamicLinker()->unloadUnreferenced();

    throw;
  }

  // unload gs module
  if (pGsModule.get())
    pGsModule.release();
  if (!moduleName.isEmpty())
    odrxDynamicLinker()->unloadModule(moduleName);

  if (activeTvGsDeviceId.isNull())
  {
    timing.startMisc();

    // save file name to database user data
    OdTvDatabaseUtils::writeFileNameToTvDatabase(databaseId, pDatabaseSource->getFilename());

    timing.endMisc();
    tvDbExternalTiming += timing.getMiscTime();
  }

  odrxDynamicLinker()->unloadUnreferenced();

  timing.endTotal();

  if (pProfileRes)
  {
    pProfileRes->setImportTime(OdInt64(dbReadingTime * 1000.));
    pProfileRes->setVectorizingTime(OdInt64((timing.getVectorizingTime()) * 1000.));
#if !defined(__APPLE__)
    pProfileRes->setTvTime(OdInt64((tvDbInternalTiming + tvDbExternalTiming) * 1000.));
#endif
  }

  return tvModelId;
}

void OdTvVisualizeDwfFiler::setupTvViews(OdDwfViewPtr pDwfView, OdDwfGsLayoutHelperPtr pLayoutHelper, OdTvGsDeviceId idTVDevice, const ODCOLORREF& borderColor,
                                         OdTv::Units units, double userDefCoefToMeters, OdString* pNewModelName) const
{
  //check existance of the tv device
  OdTvGsDevicePtr pTvDevice = idTVDevice.openObject(OdTv::kForWrite);
  if (pTvDevice.isNull())
    return;

  //check that the layout helper is paper space
  bool bPaperSpace = !pDwfView->isModelLayout();

  //setup active view
  int iPaperViewInd = -1;
  int iActViewViewInd = getActiveViewId(pLayoutHelper, bPaperSpace, iPaperViewInd);
  OdTvGsViewId tvActiveViewId = pTvDevice->viewAt(iActViewViewInd);
  if (tvActiveViewId.isNull())
    return;

  OdTvGsViewPtr pTvActiveView = tvActiveViewId.openObject(OdTv::kForWrite);
  pTvActiveView->setActive(true);
  if (bPaperSpace)
    pTvActiveView->set2dMode(true);
  if (pTvActiveView->getBorderVisibility())
  {
    pTvActiveView->setBorderProperties(borderColor, 2);
  }

  //set device name
  pTvDevice->setName(pDwfView->getName());

  //setup views
  for (int i = 0; i < pTvDevice->numViews(); i++)
  {
    OdGsView* pGsView = pLayoutHelper->viewAt(i);
    OdGsClientViewInfo viewInfo;
    pGsView->clientViewInfo(viewInfo);

    // set new name for view and models
    OdTvGsViewId tvViewId = pTvDevice->viewAt(i);
    if (tvViewId.isNull())
      continue;

    //setup model and view name
    setViewAndModelNames(tvViewId, pTvDevice->getName(), viewInfo, units, userDefCoefToMeters, pNewModelName);

    //setup view connection
    if (bPaperSpace)
    {
      if (i == iActViewViewInd)
        continue;

      if (i == iPaperViewInd)
        pTvActiveView->addSibling(tvViewId);
    }
  }

  return;
}

int OdTvVisualizeDwfFiler::getActiveViewId(OdDwfGsLayoutHelperPtr pLayoutHelper, bool bPaperSpace, int& iPaperViewId) const
{
  if (pLayoutHelper.isNull())
    return 0;

  iPaperViewId = -1;
  OdGsViewPtr pActiveView = pLayoutHelper->activeView();
  int num = pLayoutHelper->numViews();
  int iActViewViewInd = 0;
  for (int i = 0; i < num; ++i)
  {
    OdGsView* pView = pLayoutHelper->viewAt(i);
    OdGsClientViewInfo viewInfo;
    pView->clientViewInfo(viewInfo);

    if (!bPaperSpace)
    {
      if (pView == pActiveView.get())
      {
        iActViewViewInd = i;
        break;
      }
    }
    else
    {
      if (viewInfo.viewportFlags & OdGsClientViewInfo::kHelperView)
      {
        iActViewViewInd = i;
      }
      else if (pView == pActiveView.get())
        iPaperViewId = i;
    }
  }

  return iActViewViewInd;
}

void OdTvVisualizeDwfFiler::setViewBorderProperties(OdGsDevice* pDevice, const ODCOLORREF& color) const
{
  int n = pDevice->numViews();
  if (n > 1)
  {
    for (int i = 0; i < n; ++i)
    {
      OdGsViewPtr pView = pDevice->viewAt(i);
      pView->setViewportBorderVisibility(true);
      pView->setViewportBorderProperties(color, 1);
    }
  }
}

void OdTvVisualizeDwfFiler::getChoosedSpaces(OdDwfDatabasePtr pDb, OdTvFilerFeedbackForChooseObject & filerFeedbackForChoose, bool& bCanceled) const
{
  OdTvFilerFeedbackItemForChooseArray* pFilerFeedbackForChooseArray = filerFeedbackForChoose.getFilerFeedbackItemForChooseArrayPtr();
  OdDwfObjectIdArray layouts = pDb->layoutIds();
  for (OdDwfObjectIdArray::iterator iter = layouts.begin(); iter != layouts.end(); ++iter)
  {
    OdDwfViewPtr pView = OdDwfView::cast(iter->getObject());
    if (pView.isNull())
      continue;
    OdTvFilerFeedbackItemForChoose filerFeedbackForChoose(pView->getName());
    filerFeedbackForChoose.m_bChosen = pDb->currentLayoutId() == *iter;

    pFilerFeedbackForChooseArray->append(filerFeedbackForChoose);
  }

  if (m_properties->getFeedbackForChooseCallback() != NULL && layouts.size() > 0)
  {
    ((OdTvFeedbackForChooseCallback)m_properties->getFeedbackForChooseCallback())(filerFeedbackForChoose);
    if (filerFeedbackForChoose.getFilerFeedbackItemForChooseArrayPtr()->length() == 0)
      bCanceled = true;
  }
}

void OdTvVisualizeDwfFiler::setViewAndModelNames(const OdTvGsViewId& viewId, const OdString& deviceName, const OdGsClientViewInfo& viewInfo,
                                                  OdTv::Units units, double userDefCoefToMeters, OdString* pNewModelName) const
{
  OdTvGsViewPtr pView = viewId.openObject(OdTv::kForWrite);
  OdString viewName = pView->getName();
  int nModels = pView->numModels();
  for (int j = 0; j < nModels; j++)
  {
    OdTvModelId modelId = pView->modelAt(j);
    OdTvModelPtr pModel = modelId.openObject(OdTv::kForWrite);
    if (!pModel.isNull())
    {
      pModel->setUnits(units, units == OdTv::kUserDefined ? userDefCoefToMeters : 1.);
      if (nModels == 1)
      {
        if (viewInfo.viewportFlags & OdGsClientViewInfo::kHelperView)
        {
          OdString nameForPaper = deviceName;
          pModel->setName(nameForPaper);
          pView->setName(nameForPaper);
        }
        else if (viewInfo.viewportFlags & OdGsClientViewInfo::kDependentGeometry)
        {
          OdString paperOnlyName = deviceName + "_Paper";
          pModel->setName(paperOnlyName);
          pView->setName(paperOnlyName);
        }
        else
        {
          OdString modelName = L"Model";
          OdString viewportName;
          viewportName.format(L"%s_View_%d", deviceName.c_str(), (int)viewInfo.viewportId);
          pModel->setName(modelName);
          pView->setName(viewportName);
          if (pNewModelName)
          {
            *pNewModelName = modelName;
          }
        }
      }
      else
      {
        OdString modelName;
        modelName.format(L"%s_%d", viewName.c_str(), j + 1);
        pModel->setName(modelName);
      }
    }
  }
}

void OdTvVisualizeDwfFiler::setupExVisualizeDeviceProp(OdRxDictionaryPtr& pProperties, const OdTvDatabaseId& tvDbId, bool bUseTimeProfiling,
  const OdString& modelSpaceName, const OdString& strDwfPath,
  const OdTvVisualizeDwfFilerPropertiesPtr& importProperties,
  const ExGsVisualizeDeviceCache& deviceCache, OdTvGsDeviceId& tvDeviceIdForAppend,
  bool bHavePaperSpace) const
{
  if (pProperties.get())
  {
    if (pProperties->has(OD_T("DisplayViaGLES2")))
      pProperties->putAt(OD_T("DisplayViaGLES2"), OdRxVariantValue(false));
    if (pProperties->has(OD_T("AllowNonPersistentObjects")))
      pProperties->putAt(OD_T("AllowNonPersistentObjects"), OdRxVariantValue(false));
#if !defined(__APPLE__)
    if (pProperties->has(OD_T("EnableTiming")))
      pProperties->putAt(OD_T("EnableTiming"), OdRxVariantValue(bUseTimeProfiling));
#endif
    if (pProperties->has(OD_T("TvDatabaseID")))
      pProperties->putAt(OD_T("TvDatabaseID"), OdRxVariantValue((OdIntPtr)(&tvDbId)));

    if (pProperties->has(OD_T("WriteUserData")))
      pProperties->putAt(OD_T("WriteUserData"), OdRxVariantValue(importProperties->getStoreSourceObjects()));
    if (pProperties->has(OD_T("GenerateEntityNames")))
      pProperties->putAt(OD_T("GenerateEntityNames"), OdRxVariantValue(importProperties->getObjectNaming()));

    if (pProperties->has(OD_T("ModelName")) && !modelSpaceName.isEmpty())
      pProperties->putAt(OD_T("ModelName"), OdRxVariantValue(modelSpaceName));
    if (pProperties->has(OD_T("DeviceCache")))
      pProperties->putAt(OD_T("DeviceCache"), OdRxVariantValue((OdIntPtr)(&deviceCache)));
    if (pProperties->has(OD_T("DisableEntitiesRemoving")))
      pProperties->putAt(OD_T("DisableEntitiesRemoving"), OdRxVariantValue(true));

    if (pProperties->has(OD_T("PerModelViews")))
      pProperties->putAt(OD_T("PerModelViews"), OdRxVariantValue(true));

    if (pProperties->has(OD_T("CustomFontFolder")) && !strDwfPath.isEmpty())
      pProperties->putAt(OD_T("CustomFontFolder"), OdRxVariantValue(strDwfPath));

    //setup convert indexed colors
    if (m_properties->getConvertIndexedToRGB())
    {
      if (pProperties->has(OD_T("ConvertIndexedColor")))
        pProperties->putAt(OD_T("ConvertIndexedColor"), OdRxVariantValue(true));
    }

    //SEA zero layer name
    if (pProperties->has(OD_T("ByBlockLayerName")))
      pProperties->putAt(OD_T("ByBlockLayerName"), OdRxVariantValue(OdString(OD_T("0"))));

    if (tvDeviceIdForAppend.isNull()) // normal open
    {
      if (bHavePaperSpace)
      {
        if (pProperties->has(OD_T("EnableViewDependentEntities")))
          pProperties->putAt(OD_T("EnableViewDependentEntities"), OdRxVariantValue(true));
      }
    }
    else // append mode
    {
      if (pProperties->has(OD_T("IgnoreFlags")))
        pProperties->putAt(OD_T("IgnoreFlags"), OdRxVariantValue(OdUInt16(kIgnoreViewInfoFlags)));
      if (pProperties->has(OD_T("NamePrefix")))
        pProperties->putAt(OD_T("NamePrefix"), OdRxVariantValue(modelSpaceName));
      if (pProperties->has(OD_T("TvDeviceDAM")))
        pProperties->putAt(OD_T("TvDeviceDAM"), OdRxVariantValue((OdIntPtr)(&tvDeviceIdForAppend)));

      OdTvGsViewId viewId = tvDeviceIdForAppend.openObject()->getActiveView();
      if (!viewId.isNull())
      {
        OdString name = viewId.openObject()->getName();
        if (pProperties->has(OD_T("TvViewDAM")))
          pProperties->putAt(OD_T("TvViewDAM"), OdRxVariantValue((OdIntPtr)(&viewId)));
      }
    }

    //Write font file path as user data
    if (pProperties->has(OD_T("WriteFontFilePath")))
      pProperties->putAt(OD_T("WriteFontFilePath"), OdRxVariantValue(true));
  }
}

ODRX_DEFINE_DYNAMIC_MODULE(OdTvVisualizeDwfFilerModule);

void OdTvVisualizeDwfFilerModule::initApp()
{
  // initialize the Visualize SDK
  odTvInitialize();
}

void OdTvVisualizeDwfFilerModule::uninitApp()
{
  // Uninitialize the Visualize SDK
  odTvUninitialize();
}

OdTvVisualizeFilerPtr OdTvVisualizeDwfFilerModule::getVisualizeFiler() const
{
  OdTvVisualizeFilerPtr pFiler = new OdTvVisualizeDwfFiler();

  return pFiler;
}
