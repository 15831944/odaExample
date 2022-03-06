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
#include "DbHostAppServices.h"
#include "HatchPatternManager.h"
#include "StaticRxObject.h"

#include "GiContextForDbDatabase.h"
#include "RxVariantValue.h"
#include "DbGsManager.h"
#include "ColorMapping.h"

#include "DbDictionary.h"
#include "DbLayoutPaperPE.h"
#include "DbBlockTableRecord.h"
#include "DbViewportTableRecord.h"
#include "DbViewportTable.h"
#include "DbViewport.h"
#include "MemoryStream.h"

#include "TvFactory.h"
#include "TvModel.h"
#include "TvGeomCollector.h"
#include "TvFilerTimer.h"
#include "TvModuleNames.h"
#include "TvDatabaseCleaner.h"
#include "TvDatabaseUtils.h"
#include "TvImportUserData.h"

#include "Dwg2Visualize.h"

#include "ModelerGeometry/ModelerModule.h"
#include "Wr/wrTriangulationParams.h"

#include "DbObjectContextCollection.h"
#include "DbObjectContextManager.h"

#include "OdPlatformStreamer.h"

#ifdef MECHANICAL_ENABLED
#include "../../Mechanical/Include/TmModuleNames.h"
#endif
#include "DbLayerTable.h"
#include "DbLayerTableRecord.h"

#ifndef ODA_UNIXOS
#define pathChar '\\'
#define oldPathChar '/'
#define separatorChar ';'
#else
#define pathChar '/'
#define oldPathChar '\\'
#define separatorChar ':'
#endif

#define DWG2VIS_PDF_DEVICE_NAME L"DWG To PDF.pc3"
#define DWG2VIS_CUSTOM_DEVICE_NAME L"Custom Device"

OdTv::Units getUnits(OdDbDatabasePtr pDb, OdTv::Units defaultUnits, double& additionalConvCoeffToMeters)
{
  OdTv::Units tvUnits = OdTv::kMeters;
  additionalConvCoeffToMeters = 1.;

  OdDb::UnitsValue dbUnits = pDb->getINSUNITS();
  switch(dbUnits)
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

  return tvUnits;
}

/************************************************************************/
/* Add paper-drawing protocol extension                                 */
/************************************************************************/
bool addTvPaperDrawingCustomization()
{
  static class OdTvDbLayoutPaperPEImpl : public OdStaticRxObject<OdDbLayoutPaperPE>
  {
  public:
    virtual bool drawPaper(const OdDbLayout*, OdGiWorldDraw* pWd, OdGePoint3d* points)
    {
      pWd->geometry().polygon(4, points);
      return true;
    }
    virtual bool drawBorder(const OdDbLayout*, OdGiWorldDraw* pWd, OdGePoint3d* points)
    {
      pWd->geometry().polygon(4, points);
      return true;
    }
    virtual bool drawMargins(const OdDbLayout*, OdGiWorldDraw* pWd, OdGePoint3d* points)
    {
      if (points[0] == points[1] || points[1] == points[2])
        return true;

      int nDashes = 15, i;
      OdGiGeometry& geom = pWd->geometry();
      OdGePoint3d dash1[2];
      OdGePoint3d dash2[2];
      OdGeVector3d step = (points[1] - points[0]) / (nDashes * 2 + 1);
      dash1[0] = points[0];
      dash2[0] = points[2];
      for (i = 0; i <= nDashes; ++i)
      {
        dash1[1] = dash1[0] + step;
        geom.polyline(2, dash1);
        dash1[0] = dash1[1] + step;
        dash2[1] = dash2[0] - step;
        geom.polyline(2, dash2);
        dash2[0] = dash2[1] - step;
      }
      nDashes = int((points[2] - points[1]).length() / step.length() - 1) / 2;
      step = (points[2] - points[1]) / (nDashes * 2 + 1);
      dash1[0] = points[1];
      dash2[0] = points[3];
      for (i = 0; i <= nDashes; ++i)
      {
        dash1[1] = dash1[0] + step;
        geom.polyline(2, dash1);
        dash1[0] = dash1[1] + step;
        dash2[1] = dash2[0] - step;
        geom.polyline(2, dash2);
        dash2[0] = dash2[1] - step;
      }
      return true;
    }
  }
  s_PaperDrawExt;

  if (OdDbLayout::desc()->getX(OdDbLayoutPaperPE::desc()).isNull())
  {
    OdDbLayout::desc()->addX(OdDbLayoutPaperPE::desc(), &s_PaperDrawExt);
    return true;
  }

  return false;
}

/************************************************************************/
/* Remove paper-drawing protocol extension                              */
/************************************************************************/
void removeTvPaperDrawingCustomization()
{
  OdDbLayout::desc()->delX(OdDbLayoutPaperPE::desc());
}

/************************************************************************/
/* Add user data to the database                                        */
/************************************************************************/

void writeNativeDbDataAsUserData(const OdTvDatabaseId& dbId, OdDbDatabasePtr pNativeDb)
{
  //save some data as user data
  bool alreadyExist = false;
  OdTvRegAppId appId = dbId.openObject()->registerAppName(OdTvDWGUserData, alreadyExist);

  OdTvDwgDbData dbData;
  SETBIT(dbData.m_prop, OdTvDwgDbData::kDisplaySilhouettes, pNativeDb->getDISPSILH());
  dbData.m_iMeasurement = pNativeDb->getMEASUREMENT();
  dbData.m_insUnits     = pNativeDb->getINSUNITS();

  //prepare stream
  OdStreamBufPtr pStreamBuff = OdMemoryStream::createNew();
  dbData.write(pStreamBuff);
  pStreamBuff->rewind();

  OdUInt8Array buffer;
  buffer.resize(pStreamBuff->length());
  pStreamBuff->getBytes(buffer.asArrayPtr(), pStreamBuff->length());

  // Add user data
  OdTvByteUserData* pDbUserData = new OdTvByteUserData(buffer.asArrayPtr(), pStreamBuff->length(), OdTvByteUserData::kCopyOwn, true);
  dbId.openObject()->appendUserData(pDbUserData, appId);

  // Add units in model user data
  OdUInt16 val = dbData.m_insUnits;
  odSwap2BytesNumber(&val);
  OdTvByteUserData* pUserData = new OdTvByteUserData(&val, sizeof(OdUInt16), OdTvByteUserData::kCopyOwn, true);

  OdTvModelsIteratorPtr itr = dbId.openObject()->getModelsIterator();
  if (!itr->getModel().isNull())
  {
    itr->getModel().openObject()->appendUserData(pUserData, appId);
  }

  return;
}

//*************************************************************************************//
// Implementation of the methods of the inheritants of 'OdTvVisualizeDwgFilerDbSource'
//*************************************************************************************//
class OdTvVisualizeDwgFilerSourceFromDb : public OdTvVisualizeDwgFilerDbSource
{
  OdDbBaseDatabase *mDatabase;

public:
  OdTvVisualizeDwgFilerSourceFromDb(OdDbBaseDatabase *pDatabase) : mDatabase(pDatabase) {};
  virtual OdDbDatabasePtr   getDb() {return mDatabase; };
  virtual bool              odWasInitialized() const { return false; }
  virtual OdString          getFilename()
  {
    OdDbDatabasePtr pDb = mDatabase;
    if (!pDb.isNull())
    {
      OdString fileName = pDb->getFilename();
      if (!fileName.isEmpty())
        return fileName;
    }

    return OD_T("NoNameDwgDatabase");
  }
};


class OdTvVisualizeDwgFilerSourceFromStream : public OdTvVisualizeDwgFilerDbSource
{
  OdStaticRxObject<OdTvDwgService> svcs;
  OdStreamBufPtr mStreamBuf;

protected:
  double         m_initTime;
  bool           m_bPartialOpen;

public:
  OdTvVisualizeDwgFilerSourceFromStream(OdStreamBufPtr pBuffer, OdTvFilerTimeProfiling* pProfileRes)
  { 
    initialize(pBuffer, pProfileRes);
  };

  virtual OdDbDatabasePtr getDb() 
  { 
    return svcs.readFile(mStreamBuf, false, isPartialOpen()); 
  };

  virtual double          getInitTime() const { return m_initTime; }
  virtual OdString getFilename()
  {
    OdString strFileName = mStreamBuf->fileName();
    if (strFileName.isEmpty())
      return OD_T("NoNameDwgDatabase");

    //generate name for the stream file
    return OdTvDatabaseUtils::getFileNameFromPath(strFileName);
  };

  bool isPartialOpen() const { return m_bPartialOpen; }
  void setPartialOpen( bool b, bool bLowMemoryMode, OdTvHostAppProgressMeter* pMeter = NULL)
  {
    m_bPartialOpen = b;
    if( bLowMemoryMode )
    {
      svcs.setPagingType( OdDb::kUnload );

      //set host app meter to the services
      svcs.setHostAppProgressMeter(pMeter);
    }
    else
    {
      svcs.setPagingType( 0 );
    }
  }

  bool isDisableFontSubstitution() const { return svcs.getDisableFontSubstitution(); }

  void setDisableFontSubstitution( bool bSet )
  {
    svcs.setDisableFontSubstitution( bSet );
  }

  virtual OdDbHostAppProgressMeter* progressMeter()
  {
    return dynamic_cast<OdDbHostAppProgressMeter*>(&svcs);
  }

  void releaseStream()
  {
    if ( !mStreamBuf.isNull() )
      mStreamBuf.release();
  }

protected:
  OdTvVisualizeDwgFilerSourceFromStream() : m_bPartialOpen( false ) {};
  void initialize(OdStreamBufPtr pBuffer, OdTvFilerTimeProfiling* pProfileRes)
  {
    mStreamBuf = pBuffer;

    OdTvFilerTimer timing(needTimer(pProfileRes));
    timing.startTotal();

    //initialize ODA Platform DB
    odInitialize(&svcs);

    // Set variable for MT loading.
    OdInt16 nMode = svcs.getMtMode();
    SETBIT(nMode, 1, true);
    svcs.setMtMode(nMode);

    timing.endTotal();
    m_initTime = timing.getTotalTime();

    m_bPartialOpen = false;
  };
};


class OdTvVisualizeDwgFilerSourceFromFile : public OdTvVisualizeDwgFilerSourceFromStream
{
  OdString mFilePath;

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
    OdTvVisualizeDwgFilerSourceFromStream::initialize(pStreamBuf, NULL);

#ifdef MECHANICAL_ENABLED
    // Load modules for mechanical
    LoadTeighaMechanicalModules(true);
#endif

    timing.endTotal();
    m_initTime = timing.getTotalTime();

    return true;
  };

  virtual OdString getFilename()
  {
    //generate name for the stream file
    return OdTvDatabaseUtils::getFileNameFromPath(mFilePath);
  };
};

//***************************************************************************//
// 'OdTvVisualizeDwgFilerProperties' methods implementation
//***************************************************************************//
using namespace DWG2Visualize;

OdTvVisualizeDwgFilerProperties::OdTvVisualizeDwgFilerProperties() : m_background(ODRGB(0, 0, 0)), m_pPalette(0), m_pCallback(0)
, m_nThreads(4), m_flags(kClearEmptyObjects|kUseAdvancedTess), m_dFACETRES(1.), m_pHostAppProgressMeter(0), m_pLowMemoryImportAbort( NULL )
{
  m_importRect.xmax = 0;
  m_importRect.xmin = 0;
  m_importRect.ymax = 0;
  m_importRect.ymin = 0;

  m_defaultUnits = OdTv::kMillimeters;
}

OdRxDictionaryPtr OdTvVisualizeDwgFilerProperties::createObject()
{
  return OdRxObjectImpl<OdTvVisualizeDwgFilerProperties, OdRxDictionary>::createObject();
}

OdTvVisualizeDwgFilerProperties::~OdTvVisualizeDwgFilerProperties()
{
}

namespace DWG2Visualize {
  ODRX_DECLARE_PROPERTY(BackgroundColor)
    ODRX_DECLARE_PROPERTY(Palette)
    ODRX_DECLARE_PROPERTY(DCRect)
    ODRX_DECLARE_PROPERTY(ObjectNaming)
    ODRX_DECLARE_PROPERTY(StoreSourceObjects)
    ODRX_DECLARE_PROPERTY(ClearEmptyObjects)
    ODRX_DECLARE_PROPERTY(FeedbackForChooseCallback)
    ODRX_DECLARE_PROPERTY(EnableMultithreading)
    ODRX_DECLARE_PROPERTY(MaxThreads)
    ODRX_DECLARE_PROPERTY(UseAdvancedTess)
    ODRX_DECLARE_PROPERTY(FacetRes)
    ODRX_DECLARE_PROPERTY(AppendTransform)
    ODRX_DECLARE_PROPERTY(PartialOpen)
    ODRX_DECLARE_PROPERTY(LowMemoryImportToVSF)
    ODRX_DECLARE_PROPERTY(ImportBrepAsBrep)
    ODRX_DECLARE_PROPERTY(ConvertIndexedToRGB)
    ODRX_DECLARE_PROPERTY(PartialImportDumpFile)
    ODRX_DECLARE_PROPERTY(HostAppProgressMeter)
    ODRX_DECLARE_PROPERTY(NeedCDATree)
    ODRX_DECLARE_PROPERTY(NeedCollectPropertiesInCDA)
    ODRX_DECLARE_PROPERTY(LowMemoryImportAbort)
    ODRX_DECLARE_PROPERTY(LowMemoryImportVSFCompression)
    ODRX_DECLARE_PROPERTY(DisableFontSubstitution)
    ODRX_DECLARE_PROPERTY(ImportFrozenLayers)
    ODRX_DECLARE_PROPERTY(DefaultUnits)

    ODRX_BEGIN_DYNAMIC_PROPERTY_MAP(OdTvVisualizeDwgFilerProperties);
    ODRX_GENERATE_PROPERTY(BackgroundColor)
    ODRX_GENERATE_PROPERTY(Palette)
    ODRX_GENERATE_PROPERTY(DCRect)
    ODRX_GENERATE_PROPERTY(ObjectNaming)
    ODRX_GENERATE_PROPERTY(StoreSourceObjects)
    ODRX_GENERATE_PROPERTY(ClearEmptyObjects)
    ODRX_GENERATE_PROPERTY(FeedbackForChooseCallback)
    ODRX_GENERATE_PROPERTY(EnableMultithreading)
    ODRX_GENERATE_PROPERTY(MaxThreads)
    ODRX_GENERATE_PROPERTY(UseAdvancedTess)
    ODRX_GENERATE_PROPERTY(FacetRes)
    ODRX_GENERATE_PROPERTY(AppendTransform)
    ODRX_GENERATE_PROPERTY(PartialOpen)
    ODRX_GENERATE_PROPERTY(LowMemoryImportToVSF)
    ODRX_GENERATE_PROPERTY(ImportBrepAsBrep)
    ODRX_GENERATE_PROPERTY(ConvertIndexedToRGB)
    ODRX_GENERATE_PROPERTY(PartialImportDumpFile)
    ODRX_GENERATE_PROPERTY(HostAppProgressMeter)
    ODRX_GENERATE_PROPERTY(NeedCDATree)
    ODRX_GENERATE_PROPERTY(NeedCollectPropertiesInCDA)
    ODRX_GENERATE_PROPERTY(LowMemoryImportAbort)
    ODRX_GENERATE_PROPERTY(LowMemoryImportVSFCompression)
    ODRX_GENERATE_PROPERTY(DisableFontSubstitution)
    ODRX_GENERATE_PROPERTY(ImportFrozenLayers)
    ODRX_GENERATE_PROPERTY(DefaultUnits)
    ODRX_END_DYNAMIC_PROPERTY_MAP(OdTvVisualizeDwgFilerProperties);

  ODRX_DEFINE_PROPERTY_METHODS(BackgroundColor, OdTvVisualizeDwgFilerProperties, getBackgroundColor, setBackgroundColor, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(Palette, OdTvVisualizeDwgFilerProperties, getPalette, setPalette, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(DCRect, OdTvVisualizeDwgFilerProperties, getDCRect, setDCRect, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(ObjectNaming, OdTvVisualizeDwgFilerProperties, getObjectNaming, setObjectNaming, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(StoreSourceObjects, OdTvVisualizeDwgFilerProperties, getStoreSourceObjects, setStoreSourceObjects, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(ClearEmptyObjects, OdTvVisualizeDwgFilerProperties, getClearEmptyObjects, setClearEmptyObjects, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(FeedbackForChooseCallback, OdTvVisualizeDwgFilerProperties, getFeedbackForChooseCallback, setFeedbackForChooseCallback, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(EnableMultithreading, OdTvVisualizeDwgFilerProperties, getMultithreading, setMultithreading, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(MaxThreads, OdTvVisualizeDwgFilerProperties, getCountOfThreads, setCountOfThreads, getUInt16);
  ODRX_DEFINE_PROPERTY_METHODS(UseAdvancedTess, OdTvVisualizeDwgFilerProperties, getUseAdvancedTess, setUseAdvancedTess, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(FacetRes, OdTvVisualizeDwgFilerProperties, getFacetRes, setFacetRes, getDouble);
  ODRX_DEFINE_PROPERTY_METHODS(AppendTransform, OdTvVisualizeDwgFilerProperties, getAppendTransform, setAppendTransform, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(PartialOpen, OdTvVisualizeDwgFilerProperties, getPartialOpen, setPartialOpen, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(LowMemoryImportToVSF, OdTvVisualizeDwgFilerProperties, getLowMemoryImportToVSF, setLowMemoryImportToVSF, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(ImportBrepAsBrep, OdTvVisualizeDwgFilerProperties, getImportBrepAsBrep, setImportBrepAsBrep, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(ConvertIndexedToRGB, OdTvVisualizeDwgFilerProperties, getConvertIndexedToRGB, setConvertIndexedToRGB, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(PartialImportDumpFile, OdTvVisualizeDwgFilerProperties, getPartialImportDumpFile, setPartialImportDumpFile, getString);
  ODRX_DEFINE_PROPERTY_METHODS(HostAppProgressMeter, OdTvVisualizeDwgFilerProperties, getHostAppProgressMeter, setHostAppProgressMeter, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(NeedCDATree, OdTvVisualizeDwgFilerProperties, getNeedCDATree, setNeedCDATree, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(NeedCollectPropertiesInCDA, OdTvVisualizeDwgFilerProperties, getNeedCollectPropertiesInCDA, setNeedCollectPropertiesInCDA, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(LowMemoryImportAbort, OdTvVisualizeDwgFilerProperties, getLowMemoryImportAbort, setLowMemoryImportAbort, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(LowMemoryImportVSFCompression, OdTvVisualizeDwgFilerProperties, getLowMemoryImportVSFCompression, setLowMemoryImportVSFCompression, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(DisableFontSubstitution, OdTvVisualizeDwgFilerProperties, getDisableFontSubstitution, setDisableFontSubstitution, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(ImportFrozenLayers, OdTvVisualizeDwgFilerProperties, getImportFrozenLayers, setImportFrozenLayers, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(DefaultUnits, OdTvVisualizeDwgFilerProperties, getDefaultUnits, setDefaultUnits, getIntPtr);
}

void OdTvVisualizeDwgFilerProperties::setBackgroundColor(OdIntPtr ptr)
{
  ODCOLORREF* pColor = (ODCOLORREF*)(ptr);
  if (!pColor)
  {
    ODA_ASSERT(false);
  }
  m_background = *pColor;
}

OdIntPtr OdTvVisualizeDwgFilerProperties::getBackgroundColor() const
{
  return (OdIntPtr)(&m_background);
}

void OdTvVisualizeDwgFilerProperties::setPalette(OdIntPtr palette)
{
  const ODCOLORREF* pPalette = (const ODCOLORREF*)(palette);

  m_pPalette = pPalette;
}

OdIntPtr OdTvVisualizeDwgFilerProperties::getPalette() const
{
  return (OdIntPtr)(m_pPalette);
}

void OdTvVisualizeDwgFilerProperties::setDCRect(OdIntPtr rect)
{
  OdTvDCRect* pRect = (OdTvDCRect*)(rect);
  if (!pRect)
  {
    ODA_ASSERT(false);
  }

  m_importRect = *pRect;
}

OdIntPtr OdTvVisualizeDwgFilerProperties::getDCRect() const
{
  return (OdIntPtr)(&m_importRect);
}

void OdTvVisualizeDwgFilerProperties::setCountOfThreads(OdUInt16 nThreads)
{
  m_nThreads = nThreads;
}

OdUInt16 OdTvVisualizeDwgFilerProperties::getCountOfThreads() const
{
  return m_nThreads;
}

void OdTvVisualizeDwgFilerProperties::setFeedbackForChooseCallback(OdIntPtr pCallback)
{
  m_pCallback = (OdTvFeedbackForChooseCallback)pCallback;
}

OdIntPtr OdTvVisualizeDwgFilerProperties::getFeedbackForChooseCallback() const
{
  return (OdIntPtr)m_pCallback;
}

void OdTvVisualizeDwgFilerProperties::setFacetRes(double dFacetRes)
{
  m_dFACETRES = dFacetRes;

  if (dFacetRes < 0.01)
    m_dFACETRES = 0.01;

  if (dFacetRes > 10.)
    m_dFACETRES = 10.;
}

double OdTvVisualizeDwgFilerProperties::getFacetRes() const
{
  return m_dFACETRES;
}

void OdTvVisualizeDwgFilerProperties::setAppendTransform(OdIntPtr pTransform)
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

OdIntPtr OdTvVisualizeDwgFilerProperties::getAppendTransform() const
{
  return (OdIntPtr)(&m_appendTransform);
}

void      OdTvVisualizeDwgFilerProperties::setHostAppProgressMeter(OdIntPtr pProgressMeter)
{
  m_pHostAppProgressMeter = (OdTvHostAppProgressMeter*)pProgressMeter;
}

OdIntPtr  OdTvVisualizeDwgFilerProperties::getHostAppProgressMeter() const
{
  return (OdIntPtr)m_pHostAppProgressMeter;
}

void OdTvVisualizeDwgFilerProperties::setLowMemoryImportAbort(OdIntPtr pAbort)
{
  m_pLowMemoryImportAbort = (OdTvLowMemoryImportAbort*)pAbort;
}

OdIntPtr OdTvVisualizeDwgFilerProperties::getLowMemoryImportAbort() const
{
  return (OdIntPtr)(m_pLowMemoryImportAbort);
}

void OdTvVisualizeDwgFilerProperties::setLowMemoryImportVSFCompression(OdIntPtr pOptions)
{
  const OdTvVSFExportOptions* pCompressOptions = (const OdTvVSFExportOptions*)(pOptions);

  if (pCompressOptions)
  {
    m_VSFCompressOptions = *pCompressOptions;
  }
  else
  {
    m_VSFCompressOptions = OdTvVSFExportOptions();
  }
}

OdIntPtr OdTvVisualizeDwgFilerProperties::getLowMemoryImportVSFCompression() const
{
  return (OdIntPtr)(&m_VSFCompressOptions);
}

//***************************************************************************//
// 'OdTvVisualizeDwgFiler' methods implementation
//***************************************************************************//

OdTvVisualizeDwgFiler::OdTvVisualizeDwgFiler() : m_properties(OdTvVisualizeDwgFilerProperties::createObject())
{
}

OdTvDatabaseId OdTvVisualizeDwgFiler::loadFrom(OdDbBaseDatabase *pDatabase, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeDwgFilerSourceFromDb dl(pDatabase);
  return loadFrom(&dl, pProfileRes, rc);
}

OdTvDatabaseId OdTvVisualizeDwgFiler::loadFrom(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeDwgFilerSourceFromStream dl(pBuffer, pProfileRes);
  return loadFrom(&dl, pProfileRes, rc);
}

OdTvDatabaseId OdTvVisualizeDwgFiler::loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeDwgFilerSourceFromFile dl;
  if( dl.initialize(filePath, pProfileRes, rc) )
  {
    if( !m_properties.isNull() )
    {
      dl.setPartialOpen( m_properties->getPartialOpen(), m_properties->getLowMemoryImportToVSF(), (OdTvHostAppProgressMeter*)m_properties->getHostAppProgressMeter());
      dl.setDisableFontSubstitution( m_properties->getDisableFontSubstitution() );
    }
    return loadFrom(&dl, pProfileRes, rc);
  }
  return OdTvDatabaseId();
}

OdTvDatabaseId OdTvVisualizeDwgFiler::generate(OdTvFilerTimeProfiling* pProfileRes) const
{
  OdTvDatabaseId tvDbId;

  // does nothing
  return tvDbId;
}

OdTvModelId OdTvVisualizeDwgFiler::appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase *pDatabase, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeDwgFilerSourceFromDb dl(pDatabase);
  return appendFrom(databaseId, &dl, pProfileRes, rc);
}

OdTvModelId OdTvVisualizeDwgFiler::appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeDwgFilerSourceFromStream dl(pBuffer, pProfileRes);
  return appendFrom(databaseId, &dl, pProfileRes, rc);
}

OdTvModelId OdTvVisualizeDwgFiler::appendFrom(const OdTvDatabaseId& databaseId, const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeDwgFilerSourceFromFile dl;
  return dl.initialize(filePath, pProfileRes, rc) ? appendFrom(databaseId, &dl, pProfileRes, rc) : OdTvModelId();
}

OdTvResult OdTvVisualizeDwgFiler::startActionsWithNativeProperties(const OdString& sFilePath, bool bIsPartial)
{
  if (!m_pDatabaseForNativeProp.isNull() && m_pDatabaseForNativeProp->getFilename() != sFilePath)
    m_pDatabaseForNativeProp.release();
  else if (!m_pDatabaseForNativeProp.isNull())
    return tvOk;

  if(m_pSourceOfDatabaseForNativeProp.isNull() )
    m_pSourceOfDatabaseForNativeProp = new OdTvVisualizeDwgFilerSourceFromFile;
  OdTvVisualizeDwgFilerSourceFromFile* pDbSource = (OdTvVisualizeDwgFilerSourceFromFile*)m_pSourceOfDatabaseForNativeProp.get();
  
  OdTvResult rc = tvOk;
  if (!pDbSource->initialize(sFilePath, NULL, &rc))
  {
    m_pSourceOfDatabaseForNativeProp = NULL;
    return tvFilerEmptyInternalDatabase;
  }

  //set partial open param
  pDbSource->setPartialOpen(bIsPartial, false);

  {
    if (m_pRxPropertiesModule.isNull())
      m_pRxPropertiesModule = ::odrxDynamicLinker()->loadModule(L"RxProperties");

    if (m_pDbPropertiesModule.isNull())
      m_pDbPropertiesModule = ::odrxDynamicLinker()->loadModule(L"DbProperties");

    try
    {
      m_pDatabaseForNativeProp = pDbSource->getDb();

      // we need to release the stream
      pDbSource->releaseStream();
    }
    catch (...)
    {
      return tvFilerEmptyInternalDatabase;
    }
  }

  return rc;
}

bool OdTvVisualizeDwgFiler::isActionsWithNativePropertiesStarted(const OdString& sFilePath)
{
  if (!m_pDatabaseForNativeProp.isNull() && m_pDatabaseForNativeProp->getFilename() == sFilePath)
    return true;

  return false;
}

OdTvResult OdTvVisualizeDwgFiler::endActionsWithNativeProperties()
{
  m_pSourceOfDatabaseForNativeProp = NULL;

  if (!m_pDatabaseForNativeProp.isNull())
    m_pDatabaseForNativeProp.release();

  if ( !m_pDbPropertiesModule.isNull() )
  {
    m_pRxPropertiesModule.release();
    m_pDbPropertiesModule.release();
    odUninitialize();
    ::odrxDynamicLinker()->unloadModule(L"RxProperties");
    ::odrxDynamicLinker()->unloadModule(L"DbProperties");
    ::odrxDynamicLinker()->unloadUnreferenced();
  }

  return tvOk;
}

OdRxMemberIteratorPtr OdTvVisualizeDwgFiler::getNativePropertiesIterator(OdUInt64 dbHandle, OdTvResult* rc)
{
  if (m_pDatabaseForNativeProp.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedDatabase;
    return OdRxMemberIteratorPtr();
  }

  OdRxMemberIteratorPtr pIter;
  if (dbHandle == 0)
    pIter = OdRxMemberQueryEngine::theEngine()->newMemberIterator(m_pDatabaseForNativeProp.get());
  else
  {
    OdDbObjectId dbObjectId = m_pDatabaseForNativeProp->getOdDbObjectId(OdDbHandle(dbHandle));
    if (dbObjectId.isNull())
    {
      if (rc)
        *rc = tvNativePropMissedObject;
      return OdRxMemberIteratorPtr();
    }
    OdDbObjectPtr pDbObject = dbObjectId.safeOpenObject(OdDb::kForRead);
    pIter = OdRxMemberQueryEngine::theEngine()->newMemberIterator(pDbObject.get());
  }

  if (pIter.isNull())
  {
    if (rc)
      *rc = tvInternal;
    return OdRxMemberIteratorPtr();
  }

  if (rc)
    *rc = tvOk;

  return pIter;
}

OdRxValue OdTvVisualizeDwgFiler::getNativePropertyValue(OdUInt64 dbHandle, const OdRxPropertyPtr& pProperty, bool* bReadOnly, OdTvResult* rc)
{
  if (pProperty.isNull())
  {
    if (rc)
      *rc = tvInvalidInput;
    return OdRxValue();
  }

  if (m_pDatabaseForNativeProp.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedDatabase;
    return OdRxValue();
  }

  OdDbObjectPtr pDbObject;
  if (dbHandle == 0)
    pDbObject = m_pDatabaseForNativeProp;
  else
  {
    OdDbObjectId dbObjectId = m_pDatabaseForNativeProp->getOdDbObjectId(dbHandle);
    pDbObject = dbObjectId.safeOpenObject(OdDb::kForRead);
  }

  if (pDbObject.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedObject;
    return OdRxValue();
  }

  OdRxValue value;
  OdResult odRes = pProperty->getValue(pDbObject, value);
  if (bReadOnly)
    *bReadOnly = pProperty->isReadOnly(pDbObject);

  if (odRes != eOk)
  {
    if (rc)
      *rc = tvInternal;

    return OdRxValue();
  }

  if (rc)
    *rc = tvOk;

  return value;
}

OdRxValueIteratorPtr OdTvVisualizeDwgFiler::getNativeCollectionPropertyIterator(OdUInt64 dbHandle, const OdRxCollectionPropertyPtr& pCollectionProperty, bool* bReadOnly /*= NULL*/, OdTvResult* rc /*= NULL*/)
{
  if (m_pDatabaseForNativeProp.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedDatabase;
    return OdRxValueIteratorPtr();
  }

  if (pCollectionProperty.isNull())
  {
    if (rc)
      *rc = tvInvalidInput;
    return OdRxValueIteratorPtr();
  }

  OdRxValueIteratorPtr pValIter;
  if (dbHandle == 0)
  {
    pValIter = pCollectionProperty->newValueIterator(m_pDatabaseForNativeProp.get());

    if (bReadOnly)
      *bReadOnly = pCollectionProperty->isReadOnly(m_pDatabaseForNativeProp);
  }
  else
  {
    OdDbObjectId dbObjectId = m_pDatabaseForNativeProp->getOdDbObjectId(OdDbHandle(dbHandle));
    if (dbObjectId.isNull())
    {
      if (rc)
        *rc = tvNativePropMissedObject;
      return OdRxValueIteratorPtr();
    }
    OdDbObjectPtr pDbObject = dbObjectId.safeOpenObject(OdDb::kForRead);

    pValIter = pCollectionProperty->newValueIterator(pDbObject.get());

    if (bReadOnly)
      *bReadOnly = pCollectionProperty->isReadOnly(pDbObject.get());

  }

  if (rc)
    *rc = tvOk;

  return pValIter;
}

OdTvResult OdTvVisualizeDwgFiler::setNativePropertyValue(OdUInt64 dbHandle, OdRxPropertyPtr& pProperty, const OdRxValue& value)
{
  if (pProperty.isNull())
    return tvInvalidInput;

  if (m_pDatabaseForNativeProp.isNull())
    return tvNativePropMissedDatabase;

  OdDbObjectPtr pDbObject;
  if (dbHandle == 0)
    pDbObject = m_pDatabaseForNativeProp;
  else
  {
    OdDbObjectId dbObjectId = m_pDatabaseForNativeProp->getOdDbObjectId(dbHandle);
    pDbObject = dbObjectId.safeOpenObject(OdDb::kForWrite);
  }

  if ( pDbObject.isNull() )
    return tvNativePropMissedObject;

  pProperty->setValue(pDbObject, value);

  return tvOk;
}

OdDbBaseDatabase* OdTvVisualizeDwgFiler::getNativeDatabase(OdTvResult* rc) const
{
  if (m_pDatabaseForNativeProp.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedDatabase;
    return NULL;
  }

  return (OdDbBaseDatabase*)m_pDatabaseForNativeProp.get();
}

OdTvDatabaseId OdTvVisualizeDwgFiler::loadFrom(OdTvVisualizeDwgFilerDbSource *pDwgDatabaseSource, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  if( m_properties->getLowMemoryImportToVSF() )
  {
    return partialLoadFrom( pDwgDatabaseSource, pProfileRes, rc );
  }

  OdTvFactoryId tvFactoryId = odTvGetFactory();
  OdTvDatabaseId tvDbId = tvFactoryId.createDatabase();

#ifdef OD_TV_MEASURE_PARTIAL
  clock_t timeStart1 = clock();
  clock_t timeEnd1 = 0;
  clock_t timeStart2 = 0;
  OdUInt64 memUsage = 0;
#endif

  OdRxModulePtr pPlotSettingsModule;

  ODCOLORREF background = *((ODCOLORREF*)m_properties->getBackgroundColor());
  bool bUseAdvancedTess = m_properties->getUseAdvancedTess();
  double facetRes = m_properties->getFacetRes();

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

  //apply new tessellation
  OdRxModulePtr pModelerModule;
  bool bApplyFacetRes = false;
  if (!odrxDynamicLinker()->getModule(OdC3dModelerModuleName).get() && !odrxDynamicLinker()->getModule(OdSpaModelerModuleName).get())
  {
    pModelerModule = odrxDynamicLinker()->loadModule(OdModelerGeometryModuleName);
    if (pModelerModule.get())
    {
      // TODO create common interface with virtual getTriangulationParams/setTriangulationParams
      ModelerModule* pModModule = static_cast<ModelerModule*>(pModelerModule.get());

      wrTriangulationParams curTriangulationParams;
      wrTriangulationParams newTriangulationParams(bUseAdvancedTess);

      //ask old triangulation params
      pModModule->getTriangulationParams(curTriangulationParams);
      if ( curTriangulationParams.bUseTesselation == bUseAdvancedTess )
        newTriangulationParams = curTriangulationParams;
      
      if ( bUseAdvancedTess )
        bApplyFacetRes = true;

      pModModule->setTriangulationParams(newTriangulationParams);
    }
  }

  std::set<OdString> spacesNames;
  OdString moduleName;
  bool bOdExceptionCatched = false;
  OdResult exceptionCode;
  try
  {
    OdDbDatabasePtr pDb = pDwgDatabaseSource->getDb();

    if (!pDb.isNull() && m_properties->getImportFrozenLayers())
      const_cast<OdTvVisualizeDwgFiler*>(this)->changeFrozenLayersToHidden(pDb);

    //apply facet res
    if (bApplyFacetRes)
    {
      OdResBufPtr val = OdResBuf::createObject(); val->setRestype(OdResBuf::kRtDouble); val->setDouble(facetRes);
      pDb->setSysVar(L"FACETRES", val);
    }

    timing.endMisc();
    dbReadingTime = timing.getMiscTime() + pDwgDatabaseSource->getInitTime();

    if (!pDb.isNull())
    {
      //get drawing folder
      OdString dwgPath = pDb->getFilename();
      dwgPath.replace(oldPathChar, pathChar);
      dwgPath = dwgPath.left(dwgPath.reverseFind(pathChar));

      //ask about what to load
      OdTvFilerFeedbackForChooseObject filerFeedbackForChooseObject(OD_T("Choose spaces for import"));
#ifdef OD_TV_MEASURE_PARTIAL
      timeEnd1 = clock();
#endif
      bool bCanceled = false;
      int nMaxTabOrder = getChoosedSpaces(pDb, filerFeedbackForChooseObject, bCanceled);
      if (bCanceled)
      {
        tvFactoryId.removeDatabase(tvDbId);

        if (rc)
          *rc = tvFilerEmptyInternalDatabase;
        pDb = NULL;
        //unload modeler if it was loaded
        if (pModelerModule.get())
          pModelerModule.release();

        //uninitialize ODA Platform DB
        if (pDwgDatabaseSource->odWasInitialized())
        {
          odUninitialize();
          odrxDynamicLinker()->unloadUnreferenced();
        }
        return OdTvDatabaseId();
      }
#ifdef OD_TV_MEASURE_PARTIAL
      timeStart2 = clock();
#endif
      if (nMaxTabOrder < 0)
        nMaxTabOrder = 0;

      //remember active layout id
      OdDbObjectId activeLayoutId;
      {
        OdDbBlockTableRecordPtr pBr = pDb->getActiveLayoutBTRId().openObject();
        activeLayoutId = pBr->getLayoutId();
      }

      // collect list of layouts according to the tab order
      OdVector<OdDbObjectId> m_spaces;
      m_spaces.resize(nMaxTabOrder + 1);
      bool bHavePaperSpace = false;
      OdDbDictionaryPtr         pLayoutDict = pDb->getLayoutDictionaryId().safeOpenObject();
      OdDbDictionaryIteratorPtr pIter = pLayoutDict->newIterator();
      while (!pIter->done())
      {
        if ( !filerFeedbackForChooseObject.find(OdTvFilerFeedbackItemForChoose(pIter->name(), true)) )
        {
          pIter->next();
          continue;
        }

        OdDbLayoutPtr pLayout = pIter->objectId().openObject();
        if (!pLayout.isNull() && pLayout->getTabOrder() < (int)m_spaces.size())
        {
          m_spaces[pLayout->getTabOrder()] = pIter->objectId();
          //check that we have paper space
          if (pLayout->getBlockTableRecordId() != pDb->getModelSpaceId())
            bHavePaperSpace = true;
          // add handle to set
          spacesNames.insert(pIter->name());
        }

        pIter->next();
      }

      timing.startVectorizing();

      pGsModule = ::odrxDynamicLinker()->loadModule(OdTvVisualizeDeviceModuleName, false);
      if (pGsModule.isNull())
      {
        tvFactoryId.removeDatabase(tvDbId);

        if (rc)
          *rc = tvMissingVisualizeDeviceModule;
        return OdTvDatabaseId();
      }

      pPlotSettingsModule = ::odrxDynamicLinker()->loadModule(OdPlotSettingsValidatorModuleName);

      tvDbId.openObject(OdTv::kForWrite)->setCodePage(pDb->getDWGCODEPAGE());
      //VIS-1724: notifier, TODO: implement me
      OdTvDwgImportNotifier notifier;

      //SEA name for ModelSpace
      OdString modelSpaceName = OdString::kEmpty;

      //SEA initialize cache and switch it to the "write only" mode
      ExGsVisualizeDeviceCache deviceCache;
      deviceCache.m_bApplyCacheData = false;
      //SEA cache layout helper to share GsModel
      OdGsLayoutHelperPtr pCachedLayoutHelper;

      //run over all spaces (layouts), which was decided to load
      unsigned int tvDevicesCount = 0;
      for ( int i = 0; i < nMaxTabOrder + 1; i++)
      {
        if ( !m_spaces[i].isValid() )
          continue;

        //update layout in the database
        pDb->setCurrentLayout(m_spaces[i]);

        //create Ex Visualize device
        OdGsDevicePtr pDevice = pGsModule->createDevice();

        // setup ExVisualize device properties
        OdRxDictionaryPtr pProperties = pDevice->properties();
        OdTvGsDeviceId activeTvDeviceId = OdTvGsDeviceId();
        setupExVisualizeDeviceProp(pProperties, tvDbId, bUseTimeProfiling, modelSpaceName, dwgPath, m_properties, deviceCache, activeTvDeviceId, bHavePaperSpace);

        //setup additional property
        if (pDb->getLIGHTGLYPHDISPLAY())
        {
          if (pProperties->has(OD_T("LightGlyphDisplay")))
            pProperties->putAt(OD_T("LightGlyphDisplay"), OdRxVariantValue(true));
        }
        if( pProperties->has( OD_T( "DeviceNotifier" ) ) )
        {
          pProperties->putAt( OD_T( "DeviceNotifier" ), OdRxVariantValue( (OdIntPtr)( &notifier ) ) );
        }

        //setup dwg context
        OdGiContextForDbDatabasePtr pDwgContext = OdGiContextForDbDatabase::createObject();
        pDwgContext->enableGsModel(true);
        pDwgContext->setDatabase(pDb);
        
        //setup layout
        OdGsLayoutHelperPtr pLayoutHelper = OdDbGsManager::setupLayoutViews(m_spaces[i], pDevice, pDwgContext);
        if( pCachedLayoutHelper.isNull() )
        {
          pCachedLayoutHelper = pLayoutHelper;
        }
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
        OdGsPaperLayoutHelperPtr pPSHelper = OdGsPaperLayoutHelper::cast(pLayoutHelper);
        if (pPSHelper.isNull())
          pDevice->setBackgroundColor(background); // for model space
        else
          pDevice->setBackgroundColor(ODRGB(173, 174, 173)); // ACAD's color for paper bg

        pDwgContext->setPaletteBackground(background);

        //set view border properties
        if (pPSHelper.isNull())
          setViewBorderProperties(pDevice.get(), pPalCpy[7]);

        //call onsize
        OdTvDCRect* pRect = (OdTvDCRect*)m_properties->getDCRect();
        if (pRect && (pRect->xmax > 0 || pRect->xmin > 0 || pRect->ymax > 0 || pRect->ymin > 0))
        {
          OdGsDCRect  gsRect(pRect->xmin, pRect->xmax, pRect->ymin, pRect->ymax);
          pDevice->onSize(gsRect);
        }

        bool bPaperPEWasSet = addTvPaperDrawingCustomization();

        //main call - vectorization into the tv database
        pLayoutHelper->update();

        if (bPaperPEWasSet)
          removeTvPaperDrawingCustomization();

        if (bUseTimeProfiling)
        {
#if !defined(__APPLE__) && !defined(ANDROID)
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

          if (!pDb.isNull() && m_properties->getImportFrozenLayers())
            const_cast<OdTvVisualizeDwgFiler*>(this)->setFrozenLayersTotallyInvisible(&deviceCache);

          OdTvDevicesIteratorPtr pDevicesIterator = tvDbId.openObject()->getDevicesIterator();
          if (!pDevicesIterator.isNull()) // here we have O(n^2) but for us not a problem
          {
            unsigned int nCount = 0;
            while (!pDevicesIterator->done())
            {
              OdTvGsDeviceId tvDeviceId = pDevicesIterator->getDevice();
              if (nCount == tvDevicesCount)
              {
                if (pLayoutHelper->layoutId() == activeLayoutId && !tvDeviceId.isNull() )
                  tvDeviceId.openObject(OdTv::kForWrite)->setActive(true);

                if (!tvDeviceId.isNull())
                  tvDeviceId.openObject(OdTv::kForWrite)->setOption(OdTvGsDevice::kUseVisualStyles, true);

                setupTvViews(pLayoutHelper->layoutId(), pLayoutHelper.get(), tvDeviceId, pPalCpy[7], &modelSpaceName);
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

      //set units
      if (tvDbId.isValid())
      {
        OdTvModelsIteratorPtr modelsIterPtr = tvDbId.openObject()->getModelsIterator();
        while (!modelsIterPtr->done())
        {
          OdTvModelPtr pModel = modelsIterPtr->getModel().openObject(OdTv::kForWrite);
          if (!pModel.isNull())
          {
            //get units
            double addUnitCoefToMeters;
            OdTv::Units tvUnits = getUnits(pDb, (OdTv::Units)m_properties->getDefaultUnits(), addUnitCoefToMeters);
            pModel->setUnits(tvUnits, tvUnits == OdTv::kUserDefined ? addUnitCoefToMeters : 1.);
          }
          modelsIterPtr->step();
        }
      }

      timing.endMisc();
      tvDbExternalTiming += timing.getMiscTime();

      timing.endVectorizing();
#ifdef OD_TV_MEASURE_PARTIAL
      memUsage = GetMemoryUsageInternalInfo( 0 );
#endif
      moduleName = pGsModule->moduleName();

      writeNativeDbDataAsUserData(tvDbId, pDb);
    }
    else
    {
      if (rc)
        *rc = tvFilerEmptyInternalDatabase;
    }

    if (m_properties->getNeedCDATree())
    {
      timing.startMisc();

      OdTvDatabasePtr pTvDb = tvDbId.openObject(OdTv::kForWrite);
      if (!pTvDb.isNull())
        createCommonDataAccessTree(pTvDb, pDb.get(), pDwgDatabaseSource->getFilename() + OD_T(".dwg"), spacesNames);

      timing.endMisc();

      if (pProfileRes)
        pProfileRes->setCDATreeCreationTime(OdInt64((timing.getMiscTime()) * 1000.));
    }
  }
  catch (const OdError& e)
  {
    if (rc)
      *rc = tvInternal;

    timing.endVectorizing();

    // unload gs module
    if (pGsModule.get())
      pGsModule.release();

    //unload modeler if it was loaded
    if (pModelerModule.get())
      pModelerModule.release();

    // unload plot setiings module
    if (pPlotSettingsModule.get())
      pPlotSettingsModule.release();

    bOdExceptionCatched = true;
    exceptionCode = e.code();
  }
  catch (...)
  {
    if (rc)
      *rc = tvInternal;

    timing.endVectorizing();

    // unload gs module
    if (pGsModule.get())
      pGsModule.release();

    //unload modeler if it was loaded
    if (pModelerModule.get())
      pModelerModule.release();

    // unload plot setiings module
    if (pPlotSettingsModule.get())
      pPlotSettingsModule.release();

    //uninitialize ODA Platform DB
    if (pDwgDatabaseSource->odWasInitialized())
    {
      odUninitialize();
      odrxDynamicLinker()->unloadUnreferenced();
    }

    throw;
  }

  //redirect exception
  if (bOdExceptionCatched)
  {
    //uninitialize ODA Platform DB
    if (pDwgDatabaseSource->odWasInitialized())
    {
      odUninitialize();
      odrxDynamicLinker()->unloadUnreferenced();
    }

    throw OdError(exceptionCode);
  }

  // unload gs module
  if (pGsModule.get())
    pGsModule.release();
  if (!moduleName.isEmpty())
    odrxDynamicLinker()->unloadModule(moduleName);
  
  timing.startMisc();

  // save filename to database user data
  OdTvDatabaseUtils::writeFileNameToTvDatabase(tvDbId, pDwgDatabaseSource->getFilename());

  timing.endMisc();
  tvDbExternalTiming += timing.getMiscTime();

  //unload modeler if it was loaded
  if (pModelerModule.get())
    pModelerModule.release();

  if (pPlotSettingsModule.get())
    pPlotSettingsModule.release();

  //uninitialize ODA Platform DB
  if (pDwgDatabaseSource->odWasInitialized())
  {
    odUninitialize();
    odrxDynamicLinker()->unloadUnreferenced();
  }

  timing.endTotal();

  if (pProfileRes)
  {
    pProfileRes->setImportTime(OdInt64(dbReadingTime * 1000.));
    pProfileRes->setVectorizingTime(OdInt64((timing.getVectorizingTime()) * 1000.));
#if !defined(__APPLE__) && !defined(ANDROID)
    pProfileRes->setTvTime(OdInt64((tvDbInternalTiming + tvDbExternalTiming) * 1000.));
#endif
  }
#ifdef OD_TV_MEASURE_PARTIAL
  clock_t timeEnd2 = clock();
  wchar_t buff[256];
  clock_t timeDiff = timeEnd2 - timeStart2 + ( timeEnd1 - timeStart1 );
  wsprintf( buff, L"NormalMode:\nMemory %ld (%ld MB)\nTime %ld (%ld sec)", memUsage, memUsage / ( 1024 * 1024 ), timeDiff, timeDiff / 1000 );
  MessageBox( NULL, buff, L"Normal MODE", MB_OK );
#endif
  return tvDbId;
}


OdTvModelId OdTvVisualizeDwgFiler::appendFrom(const OdTvDatabaseId& databaseId, OdTvVisualizeDwgFilerDbSource *pDwgDatabaseSource, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvModelId tvModelId;

  if (rc)
    *rc = tvOk;

  bool bUseAdvancedTess = m_properties->getUseAdvancedTess();
  double facetRes = m_properties->getFacetRes();

  OdRxModulePtr pPlotSettingsModule;
  
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
  OdTvDCRect rect(0,0,0,0);
  OdArray<ODCOLORREF, OdMemoryAllocator<ODCOLORREF> > pPalCpy;

  if (!activeTvGsDeviceId.isNull())
  {
    OdTvGsDevicePtr pTvDevice = activeTvGsDeviceId.openObject();

    background = pTvDevice->getBackgroundColor();
    pTvDevice->getSize(rect);

    if (rect.xmax == 0 || rect.ymin == 0)
    {
      OdTvDCRect* pRect = (OdTvDCRect*)m_properties->getDCRect();
      if (pRect)
        rect = *pRect;
    }

    int nColors;
    const ODCOLORREF* pPalette = pTvDevice->getLogicalPalette(nColors);
    if ( nColors >= 256 )
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

  //apply new tessellation
  OdRxModulePtr pModelerModule;
  bool bApplyFacetRes = false;
  if (!odrxDynamicLinker()->getModule(OdC3dModelerModuleName).get() && !odrxDynamicLinker()->getModule(OdSpaModelerModuleName).get())
  {
    pModelerModule = odrxDynamicLinker()->loadModule(OdModelerGeometryModuleName);
    if (pModelerModule.get())
    {
      // TODO create common interface with virtual getTriangulationParams/setTriangulationParams
      ModelerModule* pModModule = static_cast<ModelerModule*>(pModelerModule.get());

      wrTriangulationParams curTriangulationParams;
      wrTriangulationParams newTriangulationParams(bUseAdvancedTess);

      //ask old triangulation params
      pModModule->getTriangulationParams(curTriangulationParams);
      if (curTriangulationParams.bUseTesselation == bUseAdvancedTess)
        newTriangulationParams = curTriangulationParams;

      if (bUseAdvancedTess)
        bApplyFacetRes = true;

      pModModule->setTriangulationParams(newTriangulationParams);
    }
  }

  OdString moduleName;
  bool bOdExceptionCatched = false;
  OdResult exceptionCode;
  try
  {
    OdDbDatabasePtr pDb = pDwgDatabaseSource->getDb();

    if (!pDb.isNull() && m_properties->getImportFrozenLayers())
      const_cast<OdTvVisualizeDwgFiler*>(this)->changeFrozenLayersToHidden(pDb);

    //apply facet res
    if (bApplyFacetRes)
    {
      OdResBufPtr val = OdResBuf::createObject(); val->setRestype(OdResBuf::kRtDouble); val->setDouble(facetRes);
      pDb->setSysVar(L"FACETRES", val);
    }

    timing.endMisc();
    dbReadingTime = timing.getMiscTime() + pDwgDatabaseSource->getInitTime();

    if (!pDb.isNull())
    {
      //get drawing folder
      OdString dwgPath = pDb->getFilename();
      dwgPath.replace(oldPathChar, pathChar);
      dwgPath = dwgPath.left(dwgPath.reverseFind(pathChar));

      //set active layout as model space
      OdDbObjectId modelSpaceLayoutId;
      {
        OdDbBlockTableRecordPtr pModelSpace = pDb->getModelSpaceId().safeOpenObject();
        modelSpaceLayoutId = pModelSpace->getLayoutId();
        pDb->setCurrentLayout(modelSpaceLayoutId);
      }

      if (!modelSpaceLayoutId.isValid())
      {
        if (rc)
          *rc = tvNullObjectPtr;
        return tvModelId;
      }

      timing.startVectorizing();

      pGsModule = ::odrxDynamicLinker()->loadModule(OdTvVisualizeDeviceModuleName, false);
      if (pGsModule.isNull())
      {
        if (rc)
          *rc = tvMissingVisualizeDeviceModule;
        return tvModelId;
      }

      pPlotSettingsModule = ::odrxDynamicLinker()->loadModule(OdPlotSettingsValidatorModuleName);

      //SEA initialize cache and switch it to the "write only" mode
      ExGsVisualizeDeviceCache deviceCache;
      deviceCache.m_bApplyCacheData = false;

      //create ExVisualize device
      OdGsDevicePtr pDevice = pGsModule->createDevice();

      // setup ExVisualize device properties
      OdRxDictionaryPtr pProperties = pDevice->properties();
      OdString modelSpaceName = OdTvDatabaseUtils::generateModelName(databaseId, pDwgDatabaseSource->getFilename());
      setupExVisualizeDeviceProp(pProperties, databaseId, bUseTimeProfiling, modelSpaceName, dwgPath, m_properties, deviceCache, activeTvGsDeviceId, false);

      //setup additional property
      if (pDb->getLIGHTGLYPHDISPLAY())
      {
        if (pProperties->has(OD_T("LightGlyphDisplay")))
          pProperties->putAt(OD_T("LightGlyphDisplay"), OdRxVariantValue(true));
      }

      //we don't need to setup extents inside appendFrom since we can have additional units transform matrix here
      if (pProperties->has(OD_T("DisableSetingExtents")))
        pProperties->putAt(OD_T("DisableSetingExtents"), OdRxVariantValue(true));

      //create dwg context
      OdGiContextForDbDatabasePtr pDwgContext = OdGiContextForDbDatabase::createObject();
      pDwgContext->enableGsModel(true);
      pDwgContext->setDatabase(pDb);

      //setup layout
      OdGsLayoutHelperPtr pLayoutHelper = OdDbGsManager::setupLayoutViews(modelSpaceLayoutId, pDevice, pDwgContext);

      //setup palette, background and device size
      //a.palette
      pDevice->setLogicalPalette(pPalCpy.asArrayPtr(), 256);

      //b. background
      pDevice->setBackgroundColor(background);
      pDwgContext->setPaletteBackground(background);

      //c. call onsize
      if (rect.xmax > 0 || rect.xmin > 0 || rect.ymax > 0 || rect.ymin > 0)
      {
        OdGsDCRect  gsRect(rect.xmin, rect.xmax, rect.ymin, rect.ymax);
        pDevice->onSize(gsRect);
      }

      //perform vectorization
      pLayoutHelper->update();

      if (bUseTimeProfiling)
      {
#if !defined(__APPLE__) && !defined(ANDROID)
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

        if (!pDb.isNull() && m_properties->getImportFrozenLayers())
          const_cast<OdTvVisualizeDwgFiler*>(this)->setFrozenLayersTotallyInvisible(&deviceCache);

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
          {
            //get units
            double addUnitCoefToMeters;
            OdTv::Units tvUnits = getUnits(pDb, (OdTv::Units)m_properties->getDefaultUnits(), addUnitCoefToMeters);
            pModel->setUnits(tvUnits, tvUnits == OdTv::kUserDefined ? addUnitCoefToMeters : 1.);
          }
        }

        {
          if (m_properties->getNeedCDATree())
          {
            timing.startMisc();

            OdTvDatabasePtr pTvDb = databaseId.openObject();
            std::set<OdString> spaces;
            if (!pTvDb.isNull())
              createCommonDataAccessTree(pTvDb, pDb.get(), pDwgDatabaseSource->getFilename() + OD_T(".dwg"), spaces);

            timing.endMisc();

            if (pProfileRes)
              pProfileRes->setCDATreeCreationTime(OdInt64((timing.getMiscTime()) * 1000.));
          }

          if (activeTvGsDeviceId.isNull())
          {
            OdTvDevicesIteratorPtr pDevicesIterator = databaseId.openObject()->getDevicesIterator();
            if (!pDevicesIterator.isNull() && !pDevicesIterator->done())
            {
              OdTvGsDeviceId tvDeviceId = pDevicesIterator->getDevice();
              OdTvGsDevicePtr pTvDevice = tvDeviceId.openObject(OdTv::kForWrite);
              OdDbObjectId layoutId = pLayoutHelper->layoutId();
              OdDbLayoutPtr pLayout = layoutId.safeOpenObject(OdDb::kForWrite);

              OdString sLayoutName = pLayout->getLayoutName();
              pTvDevice->setName(pLayout->getLayoutName());
              
              OdTvRegAppId appId = setLayoutUserData(tvDeviceId, layoutId, databaseId);

              //setup views
              for (int i = 0; i < pTvDevice->numViews(); i++)
              {
                OdTvGsViewId tvViewId = pTvDevice->viewAt(i);
                if (tvViewId.isNull())
                  continue;

                //prepare user data
                OdTvDwgViewData viewData;

                //setup view connection
                {
                  viewData.m_type = OdTvDwgViewData::kModel;

                  OdDbViewportTablePtr pVPT = pLayout->database()->getViewportTableId().safeOpenObject();
                  OdDbViewportTableRecordPtr pActiveVP = pVPT->getActiveViewportId().safeOpenObject();
                  viewData.m_target = pActiveVP->target(); //for possible later using in PE (applyLayoutSettings)
                }

                //append user data
                if (!appId.isNull())
                {
                  OdStreamBufPtr pStreamBuff = OdMemoryStream::createNew();
                  viewData.write(pStreamBuff);
                  pStreamBuff->rewind();

                  OdUInt8Array buffer;
                  buffer.resize(pStreamBuff->length());
                  pStreamBuff->getBytes(buffer.asArrayPtr(), pStreamBuff->length());

                  OdTvByteUserData* data = new OdTvByteUserData(buffer.asArrayPtr(), pStreamBuff->length(), OdTvByteUserData::kCopyOwn, true);
                  tvViewId.openObject()->appendUserData(data, appId);
                }
              }
            }
          }
        }

        timing.endMisc();
        tvDbExternalTiming = timing.getMiscTime();
      }

      timing.endVectorizing();

      moduleName = pGsModule->moduleName();

      //add user data for native db
      if (activeTvGsDeviceId.isNull())
        writeNativeDbDataAsUserData(databaseId, pDb);
    }
    else
    {
      if (rc)
        *rc = tvFilerEmptyInternalDatabase;
    }

  }
  catch (const OdError& e)
  {
    if (rc)
      *rc = tvInternal;

    timing.endVectorizing();

    // unload gs module
    if (pGsModule.get())
      pGsModule.release();

    //unload modeler if it was loaded
    if (pModelerModule.get())
      pModelerModule.release();

    // unload plot setiings module
    if (pPlotSettingsModule.get())
      pPlotSettingsModule.release();

    bOdExceptionCatched = true;
    exceptionCode = e.code();
  }
  catch (...)
  {
    if (rc)
      *rc = tvInternal;

    timing.endVectorizing();

    // unload gs module
    if (pGsModule.get())
      pGsModule.release();

    //unload modeler if it was loaded
    if (pModelerModule.get())
      pModelerModule.release();

    // unload plot setiings module
    if (pPlotSettingsModule.get())
      pPlotSettingsModule.release();

    //uninitialize ODA Platform DB
    if (pDwgDatabaseSource->odWasInitialized())
    {
      odUninitialize();
      odrxDynamicLinker()->unloadUnreferenced();
    }

    throw;
  }

  //redirect exception
  if (bOdExceptionCatched)
  {
    //uninitialize ODA Platform DB
    if (pDwgDatabaseSource->odWasInitialized())
    {
      odUninitialize();
      odrxDynamicLinker()->unloadUnreferenced();
    }

    throw OdError(exceptionCode);
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
    OdTvDatabaseUtils::writeFileNameToTvDatabase(databaseId, pDwgDatabaseSource->getFilename());

    timing.endMisc();
    tvDbExternalTiming += timing.getMiscTime();
  }

  //unload modeler if it was loaded
  if (pModelerModule.get())
    pModelerModule.release();

  if (pPlotSettingsModule.get())
    pPlotSettingsModule.release();

  //uninitialize ODA Platform DB
  if (pDwgDatabaseSource->odWasInitialized())
  {
    odUninitialize();
    odrxDynamicLinker()->unloadUnreferenced();
  }

  timing.endTotal();

  if (pProfileRes)
  {
    pProfileRes->setImportTime(OdInt64(dbReadingTime * 1000.));
    pProfileRes->setVectorizingTime(OdInt64((timing.getVectorizingTime()) * 1000.));
#if !defined(__APPLE__) && !defined(ANDROID)
    pProfileRes->setTvTime(OdInt64((tvDbInternalTiming + tvDbExternalTiming) * 1000.));
#endif
  }

  return tvModelId;
}

void OdTvVisualizeDwgFiler::setupTvViews(OdDbObjectId layoutId, OdGsLayoutHelper* pLayoutHelper, OdTvGsDeviceId idTVDevice, const ODCOLORREF& borderColor, OdString* pNewModelName) const
{
  //check existence of the tv device
  OdTvGsDevicePtr pTvDevice = idTVDevice.openObject(OdTv::kForWrite);
  if (pTvDevice.isNull())
    return;

  //check that the layout helper is paper space
  bool bPaperSpace = false;
  if (pLayoutHelper->isA() == OdGsPaperLayoutHelper::desc())
    bPaperSpace = true;

  //setup active view
  int iPaperViewInd = -1;
  int iActViewViewInd = getActiveViewId(pLayoutHelper, iPaperViewInd);
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

  //get DB layout helper. Here also we will update the pliot cfg file for the layout (for possible future PDF-export)
  OdDbLayoutPtr pLayout = layoutId.safeOpenObject(OdDb::kForWrite);
  
  OdString printer = pLayout->getPlotCfgName();
  if (printer != OdString(DWG2VIS_PDF_DEVICE_NAME) && printer != OdString(DWG2VIS_CUSTOM_DEVICE_NAME))
  {
    OdDbPlotSettingsValidatorPtr pValidator = pLayout->database()->appServices()->plotSettingsValidator();
    if (!pValidator.isNull())
    {
      OdString mediaName = pLayout->getCanonicalMediaName();
      OdResult res = pValidator->setPlotCfgName((OdDbPlotSettings*)pLayout, DWG2VIS_PDF_DEVICE_NAME, mediaName);
    }
  }

  OdTvDatabaseId databaseId = pTvActiveView->getDatabase();
  if (databaseId.isNull())
    return;

  OdTvRegAppId appId = setLayoutUserData(idTVDevice, layoutId, databaseId);
  
  //set device name
  pTvDevice->setName(pLayout->getLayoutName());

  std::map<OdDbObjectId, OdTvGsViewId>* pViewsMap = const_cast<std::map<OdDbObjectId, OdTvGsViewId>*>(&m_viewportMap);

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

    // fill map
    if(pViewsMap)
      pViewsMap->insert(std::pair<OdDbObjectId, OdTvGsViewId>(viewInfo.viewportObjectId, tvViewId));

    //setup model and view name
    setViewAndModelNames(tvViewId, pTvDevice->getName(), viewInfo, pNewModelName);

    //prepare user data
    OdTvDwgViewData viewData;

    //setup view connection
    if ( bPaperSpace )
    {
      if ( i == iActViewViewInd )
      {
        viewData.m_type = OdTvDwgViewData::kPaper;
        OdDbViewportPtr pActiveVP = pLayout->overallVportId().safeOpenObject();
        viewData.m_target = pActiveVP->viewTarget();   // in plotPaperUnits
      }
      else if (i == iPaperViewInd)
      {
        pTvActiveView->addSibling(tvViewId);
        viewData.m_type = OdTvDwgViewData::kUnderlayingPaper;
        OdDbViewportPtr pActiveVP = pLayout->overallVportId().safeOpenObject();
        viewData.m_target = pActiveVP->viewTarget();   // in plotPaperUnits
      }
      else
      {
        setViewportConfiguration(tvViewId, tvActiveViewId, pLayoutHelper, iActViewViewInd, i);
        viewData.m_type = OdTvDwgViewData::kViewport;
        OdDbObjectId viewportId = viewInfo.viewportObjectId;
        if (viewportId.isValid())
        {
          OdDbViewportPtr pDbViewport = viewportId.safeOpenObject();
          if (!pDbViewport.isNull())
          {
            viewData.m_shadePlot = pDbViewport->shadePlot();
            viewData.m_bPlotHidden = pDbViewport->hiddenLinesRemoved();
          }
        }
      }
    }
    else
    {
      viewData.m_type = OdTvDwgViewData::kModel;

      OdDbViewportTablePtr pVPT = pLayout->database()->getViewportTableId().safeOpenObject();
      OdDbViewportTableRecordPtr pActiveVP = pVPT->getActiveViewportId().safeOpenObject();
      viewData.m_target = pActiveVP->target(); //for possible later using in PE (applyLayoutSettings)
    }

    //append user data
    if (!appId.isNull())
    {
      OdStreamBufPtr pStreamBuff = OdMemoryStream::createNew();
      viewData.write(pStreamBuff);
      pStreamBuff->rewind();

      OdUInt8Array buffer;
      buffer.resize(pStreamBuff->length());
      pStreamBuff->getBytes(buffer.asArrayPtr(), pStreamBuff->length());

      OdTvByteUserData* data = new OdTvByteUserData(buffer.asArrayPtr(), pStreamBuff->length(), OdTvByteUserData::kCopyOwn, true);
      tvViewId.openObject()->appendUserData(data, appId);
    }
  }

  return;
}

int OdTvVisualizeDwgFiler::getActiveViewId(OdGsLayoutHelper* pLayoutHelper, int& iPaperViewId) const
{
  if (!pLayoutHelper)
    return 0;

  iPaperViewId = -1;
  bool bPaperSpace = false;
  if (pLayoutHelper->isA() == OdGsPaperLayoutHelper::desc())
    bPaperSpace = true;

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
      else if (viewInfo.viewportFlags & OdGsClientViewInfo::kDependentGeometry)
        iPaperViewId = i;
    }
  }

  return iActViewViewInd;
}

void OdTvVisualizeDwgFiler::setViewBorderProperties(OdGsDevice* pDevice, const ODCOLORREF& color) const
{
  int n = pDevice->numViews();
  if (n>1)
  {
    for (int i = 0; i<n; ++i)
    {
      OdGsViewPtr pView = pDevice->viewAt(i);
      pView->setViewportBorderVisibility(true);
      pView->setViewportBorderProperties(color, 1);
    }
  }
}

int OdTvVisualizeDwgFiler::getChoosedSpaces(const OdDbDatabasePtr pDbDatabase, OdTvFilerFeedbackForChooseObject & filerFeedbackForChoose, bool& bCanceled) const
{
  int nMaxTabOrder = -1;
  OdTvFilerFeedbackItemForChooseArray* pFilerFeedbackForChooseArray = filerFeedbackForChoose.getFilerFeedbackItemForChooseArrayPtr();
  OdDbDictionaryPtr         pLayoutDict = pDbDatabase->getLayoutDictionaryId().safeOpenObject();
  OdDbDictionaryIteratorPtr pIter = pLayoutDict->newIterator();

  OdDbBlockTableRecordPtr pBr = pDbDatabase->getActiveLayoutBTRId().openObject();
  OdDbObjectId activeLayoutId = pBr->getLayoutId();

  pFilerFeedbackForChooseArray->resize(pLayoutDict->numEntries());

  while (!pIter->done())
  {
    OdTvFilerFeedbackItemForChoose filerFeedbackForChoose(pIter->name());
    if (pIter->objectId() == activeLayoutId)
      filerFeedbackForChoose.m_bChosen = true;

    OdDbLayoutPtr pLayout = pIter->objectId().openObject();
    int tabOrder = pLayout->getTabOrder();

    if (tabOrder > nMaxTabOrder)
      nMaxTabOrder = tabOrder;

    pFilerFeedbackForChooseArray->setAt(tabOrder, filerFeedbackForChoose);

    pIter->next();
  }

  if (m_properties->getFeedbackForChooseCallback() != NULL)
  {
    ((OdTvFeedbackForChooseCallback)m_properties->getFeedbackForChooseCallback())(filerFeedbackForChoose);
    if (filerFeedbackForChoose.getFilerFeedbackItemForChooseArrayPtr()->length() == 0)
      bCanceled = true;
  }

  return nMaxTabOrder;
}

void OdTvVisualizeDwgFiler::setViewAndModelNames(const OdTvGsViewId& viewId, const OdString& deviceName, const OdGsClientViewInfo& viewInfo, OdString* pNewModelName) const
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
          m_paperViewportId = viewInfo.viewportObjectId;
        }
        else
        {
          OdString modelName = L"Model";
          OdString viewportName;
          viewportName.format(L"%s_View_%d", deviceName.c_str(), (int)viewInfo.viewportId);
          pModel->setName(modelName);
          pView->setName(viewportName);
          if( pNewModelName )
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

void OdTvVisualizeDwgFiler::setViewportConfiguration(const OdTvGsViewId& viewId, const OdTvGsViewId& activeViewId, OdGsLayoutHelperPtr pLayoutHelper, int iActViewInd, int ind) const
{
  OdGeMatrix3d matr = pLayoutHelper->viewAt(iActViewInd)->worldToDeviceMatrix();
  matr.invert();

  OdTvGsViewPtr pViewportObject = viewId.openObject();

  if (!pViewportObject.isNull())
  {
    OdTvGsView::ViewportObjectInfo vi;

    //get viewport parameters
    OdGsView* pGsView = pLayoutHelper->viewAt(ind);
    OdGsDCRect rect;
    pGsView->getViewport(rect);

    OdTvPoint ll, ur;
    ll.set(rect.m_min.x, rect.m_min.y, 0.);
    ur.set(rect.m_max.x, rect.m_max.y, 0.);

    ll.transformBy(matr);
    ur.transformBy(matr);

    vi.m_wcsLowerLeft = OdTvPoint2d(ll.x, ll.y);
    vi.m_wcsUpperRight = OdTvPoint2d(ur.x, ur.y);

    //get clipping parameters
    OdIntArray counts;
    OdGePoint2dArray vertices;
    pGsView->viewportClipRegion(counts, vertices);

    vi.m_numPtsInContours.resize(counts.size());
    for (unsigned int i = 0; i < counts.size(); i++)
    {
      vi.m_numPtsInContours[i] = OdUInt32(counts[i]);
    }

    vi.m_wcsCountoursPts.resize(vertices.size());
    for (unsigned int i = 0; i < vertices.size(); i++)
    {
      OdTvPoint vertices3d = OdTvPoint(vertices[i].x, vertices[i].y, 0.);
      vertices3d.transformBy(matr);
      vi.m_wcsCountoursPts[i] = OdTvPoint2d(vertices3d.x, vertices3d.y);
    }

    //add view as a viewport object
    OdTvGsViewPtr pActiveTvView = activeViewId.openObject(OdTv::kForWrite);
    pActiveTvView->addViewportObject(viewId, vi);
  }
}

void OdTvVisualizeDwgFiler::setupExVisualizeDeviceProp(OdRxDictionaryPtr& pProperties, const OdTvDatabaseId& tvDbId, bool bUseTimeProfiling,
                                                       const OdString& modelSpaceName, const OdString& strDwgPath,
                                                       const OdTvVisualizeDwgFilerPropertiesPtr& importProperties,
                                                       const ExGsVisualizeDeviceCache& deviceCache, OdTvGsDeviceId& tvDeviceIdForAppend,
                                                       bool bHavePaperSpace) const
{
  if (pProperties.get())
  {
    if (pProperties->has(OD_T("DisplayViaGLES2")))
      pProperties->putAt(OD_T("DisplayViaGLES2"), OdRxVariantValue(false));
    if (pProperties->has(OD_T("AllowNonPersistentObjects")))
      pProperties->putAt(OD_T("AllowNonPersistentObjects"), OdRxVariantValue(false));
#if !defined(__APPLE__) && !defined(ANDROID)
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

    if (pProperties->has(OD_T("EnableMultithread")))
      pProperties->putAt(OD_T("EnableMultithread"), OdRxVariantValue(m_properties->getMultithreading()));
    if (pProperties->has(OD_T("MaxRegenThreads")))
      pProperties->putAt(OD_T("MaxRegenThreads"), OdRxVariantValue(m_properties->getCountOfThreads()));

    if (pProperties->has(OD_T("CustomFontFolder")) && !strDwgPath.isEmpty())
      pProperties->putAt(OD_T("CustomFontFolder"), OdRxVariantValue(strDwgPath));

    //setup support direct draw of the breps
    bool bImportBrepAsBrep = m_properties->getImportBrepAsBrep();
    if (bImportBrepAsBrep)
    {
      if (pProperties->has(OD_T("SuppoprtBrepDraw")))
        pProperties->putAt(OD_T("SuppoprtBrepDraw"), OdRxVariantValue(true));

      if (pProperties->has(OD_T("FullRegenDependentVectorization")))
        pProperties->putAt(OD_T("FullRegenDependentVectorization"), OdRxVariantValue(false));

      if (pProperties->has(OD_T("FacetResForBrep")))
        pProperties->putAt(OD_T("FacetResForBrep"), OdRxVariantValue(m_properties->getFacetRes()));
    }

    //setup convert indexed colors
    if (m_properties->getConvertIndexedToRGB())
    {
      if (pProperties->has(OD_T("ConvertIndexedColor")))
        pProperties->putAt(OD_T("ConvertIndexedColor"), OdRxVariantValue(true));
    }

    //SEA zero layer name
    if( pProperties->has( OD_T("ByBlockLayerName") ) )
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
        pProperties->putAt(OD_T("IgnoreFlags"), OdRxVariantValue(OdUInt16(1)/*DeviceIgnoreFlags::kIgnoreViewInfoFlags*/));
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
    if( pProperties->has( OD_T("WriteFontFilePath") ))
      pProperties->putAt( OD_T("WriteFontFilePath"), OdRxVariantValue( true ) );
  }
}

void OdTvVisualizeDwgFiler::createCommonDataAccessTree(OdTvDatabasePtr pTvDb, OdDbDatabase *pDatabase, const OdString& strTreeName, const std::set<OdString>& spaces) const
{
  ::odrxDynamicLinker()->loadModule(L"DbProperties");

  //Create CDA tree
  OdTvCDATreePtr pTree = OdTvCDATree::createObject();
  if (m_properties->getNeedCollectPropertiesInCDA())
    pTree->createDatabaseHierarchyTree(pDatabase, true);
  else
  {
    std::set<OdString> props;
    props.insert(OdTvCDAPropNameForGrouping);
    pTree->createDatabaseHierarchyTree(pDatabase, &props);
  }

  //Add tree to the Tv database
  OdTvResult rc;
  OdTvCDATreeStorageId cdaTreeId = pTvDb->addCDATreeStorage(strTreeName, pTree, &rc);
  if (rc == tvAlreadyExistSameName)
  {
    OdUInt32 i = 1;
    while (rc != tvOk && i < MAX_CDATREENAME_GENERATION_ATTEMPTS)
    {
      OdString str;
      str.format(L"%s_%d", strTreeName.c_str(), i++); //not to fast but it is not a "bottle neck"
      cdaTreeId = pTvDb->addCDATreeStorage(str, pTree, &rc);
    }
  }

  //Add new CDA tree to the appropriate models
  OdTvModelsIteratorPtr modelsIterPtr = pTvDb->getModelsIterator();
  std::map<OdString, OdTvModelId> modelsMap;
  while (!modelsIterPtr->done())
  {
    OdTvModelPtr pModel = modelsIterPtr->getModel().openObject();
    if (!pModel.isNull())
      pModel->setCDATreeStorage(cdaTreeId);
    modelsMap.insert(std::pair<OdString, OdTvModelId>(pModel->getName(), modelsIterPtr->getModel()));
    modelsIterPtr->step();
  }

  // filter cda tree
  OdRxModelTreeBaseNodePtr pDbNode = pTree->getDatabaseNode();
  if (pDbNode.isNull())
    return;
  const OdRxModelTreeBaseNodePtrArray& lvl0Arr = pDbNode->getChildren();
  if (lvl0Arr.isEmpty())
    return;
  for (OdRxModelTreeBaseNodePtrArray::const_iterator itLvl0 = lvl0Arr.begin(); itLvl0 != lvl0Arr.end(); ++itLvl0)
  {
    OdTvCDATreeNodePtr pNodeLvl0 = dynamic_cast<const OdTvCDATreeNode*>((*itLvl0).get());
    if (pNodeLvl0.isNull())
      continue;

    // set invisible for BlockTable node
    if (pNodeLvl0->getNodeName().compare(OD_T("BlockTable")) == false)
    {
      pNodeLvl0->setInvisible(true);
      continue;
    }

    // skip first node
    pNodeLvl0->setExploded(true);

    if (spaces.empty())
      continue;
    const OdRxModelTreeBaseNodePtrArray& lvl1Arr = pNodeLvl0->getChildren();
    for (OdRxModelTreeBaseNodePtrArray::const_iterator itLvl1 = lvl1Arr.begin(); itLvl1 != lvl1Arr.end(); ++itLvl1)
    {
      OdTvCDATreeNodePtr pNodeLvl1 = dynamic_cast<const OdTvCDATreeNode*>((*itLvl1).get());
      if (pNodeLvl1.isNull())
        continue;
      // set invisible for not choosen spaces
      if (spaces.find(pNodeLvl1->getNodeName()) == spaces.end())
        pNodeLvl1->setInvisible(true);
      else
      {
        // skip second node
        pNodeLvl1->setExploded(true);
        const OdRxModelTreeBaseNodePtrArray& lvl2Arr = pNodeLvl1->getChildren();
        for (OdRxModelTreeBaseNodePtrArray::const_iterator itLvl2 = lvl2Arr.begin(); itLvl2 != lvl2Arr.end(); ++itLvl2)
        {
          OdTvCDATreeNodePtr pNodeLvl2 = dynamic_cast<const OdTvCDATreeNode*>((*itLvl2).get());
          if (pNodeLvl2.isNull())
            continue;
          // rename node
          OdString nodeName = pNodeLvl1->getNodeName();

          // add model id to node
          std::map<OdString, OdTvModelId>::const_iterator modelIt = modelsMap.find(nodeName);
          if (modelIt != modelsMap.end())
          {
            pNodeLvl2->setTvModelId(modelIt->second);
            pNodeLvl2->setAlwaysGroup(true);
          }

          if (!nodeName.compare(OD_T("Model"))) // model space
            nodeName = OD_T("Model_Space");
          else // paper space
          {
            // viewport clip entities map
            std::map<OdDbObjectId, OdTvCDATreeNodePtr> nonViewportEntitiesMap;
            // viewport objects
            std::map<OdDbObjectId, OdTvCDATreeNodePtr> viewportEntitiesMap;
            // find and fill viewport nodes
            const OdRxModelTreeBaseNodePtrArray& lvl3Arr = pNodeLvl2->getChildren();
            for (OdRxModelTreeBaseNodePtrArray::const_iterator itLvl3 = lvl3Arr.begin(); itLvl3 != lvl3Arr.end(); ++itLvl3)
            {
              OdTvCDATreeNodePtr pNodeLvl3 = dynamic_cast<const OdTvCDATreeNode*>((*itLvl3).get());
              if (pNodeLvl3.isNull())
                continue;
              OdUInt64 uniqueId = pNodeLvl3->getUniqueSourceID();
              OdDbObjectId odDbId = pDatabase->getOdDbObjectId(uniqueId);
              if (!odDbId.isValid())
                continue;
              if (odDbId.openObject()->isA() == OdDbViewport::desc())
              {
                if (m_viewportMap.find(odDbId) == m_viewportMap.end())
                  continue;
                // not show paper viewport
                if (odDbId == m_paperViewportId)
                {
                  pNodeLvl3->setInvisible(true);
                  continue;
                }
                std::map<OdDbObjectId, OdTvGsViewId>::const_iterator pos = m_viewportMap.find(odDbId);
                if (pos != m_viewportMap.end())
                {
                  pNodeLvl3->setViewportObject(pos->second);
                }

                viewportEntitiesMap.insert( std::pair<OdDbObjectId, OdTvCDATreeNodePtr>(odDbId, pNodeLvl3) );
              }
              else // add entities to map
                nonViewportEntitiesMap.insert( std::pair<OdDbObjectId, OdTvCDATreeNodePtr>(odDbId, pNodeLvl3) );
            }

            // connect viewport nodes with clip entities nodes
            for (std::map<OdDbObjectId, OdTvCDATreeNodePtr>::const_iterator it = viewportEntitiesMap.begin(); it != viewportEntitiesMap.end(); ++it)
            {
              OdDbObjectId viewportId = it->first;
              OdDbViewportPtr pViewport = viewportId.openObject();
              if(pViewport.isNull())
                continue;
              OdTvCDATreeNodePtr pViewportNode = it->second;
              if(pViewportNode.isNull())
                continue;

              // get clip entity id
              OdDbObjectId clipEntId = pViewport->nonRectClipEntityId();
              if(!clipEntId.isValid())
                continue;

              // try find in entities map
              if(nonViewportEntitiesMap.find(clipEntId) == nonViewportEntitiesMap.end())
                continue;
              OdTvCDATreeNodePtr pClipEntityNode;
              std::map<OdDbObjectId, OdTvCDATreeNodePtr>::const_iterator posV = nonViewportEntitiesMap.find(clipEntId);
              if (posV != nonViewportEntitiesMap.end())
              {
                pClipEntityNode = posV->second;
              }
              if(pClipEntityNode.isNull())
                continue;

              // connect viewport node with border node
              pViewportNode->setSiblingNode(pClipEntityNode);
              pClipEntityNode->setSiblingNode(pViewportNode);
            }
          }
          pNodeLvl2->setNodeName(nodeName);
        }
      }
    }
  }
}

OdTvRegAppId OdTvVisualizeDwgFiler::setLayoutUserData(OdTvGsDeviceId tvDeviceId, OdDbObjectId layoutId, OdTvDatabaseId databaseId) const
{
  OdTvGsDevicePtr pTvDevice = tvDeviceId.openObject(OdTv::kForWrite);
  OdDbLayoutPtr pLayout = layoutId.safeOpenObject(OdDb::kForWrite);

  //register app for user data
  bool alreadyExist = false;
  OdTvRegAppId appId = databaseId.openObject()->registerAppName(OdTvDWGUserData, alreadyExist);

  //append layout user data
  OdTvDwgLayoutData layoutData;
  SETBIT(layoutData.m_PlotLayoutFlags, OdTvDwgLayoutData::kModelSpace, pLayout->modelType());
  layoutData.m_strPaperName = pLayout->getCanonicalMediaName();
  SETBIT(layoutData.m_PlotLayoutFlags, OdTvDwgLayoutData::kScaledToFit, pLayout->useStandardScale() && (OdDbPlotSettings::kScaleToFit == pLayout->stdScaleType()));
  SETBIT(layoutData.m_PlotLayoutFlags, OdTvDwgLayoutData::kCentered, pLayout->plotCentered());
  layoutData.m_iPaperUnits = pLayout->plotPaperUnits();
  pLayout->getPlotPaperSize(layoutData.m_dPrinterWidth, layoutData.m_dPrinterHeight);
  pLayout->getPlotOrigin(layoutData.m_dOffsetX, layoutData.m_dOffsetY);
  layoutData.m_paperImageOrigin = pLayout->getPaperImageOrigin();
  layoutData.m_dLeftMargin = pLayout->getLeftMargin();
  layoutData.m_dRightMargin = pLayout->getRightMargin();
  layoutData.m_dTopMargin = pLayout->getTopMargin();
  layoutData.m_dBottomMargin = pLayout->getBottomMargin();
  layoutData.m_plotType = pLayout->plotType();
  layoutData.m_plotRot = pLayout->plotRotation();
  pLayout->getPlotWindowArea(layoutData.m_dXmin, layoutData.m_dYmin, layoutData.m_dXmax, layoutData.m_dYmax);
  SETBIT(layoutData.m_PlotLayoutFlags, OdTvDwgLayoutData::kPrintLineweights, pLayout->printLineweights());

  SETBIT(layoutData.m_PlotLayoutFlags, OdTvDwgLayoutData::kUseStandardScale, pLayout->useStandardScale());
  pLayout->getStdScale(layoutData.m_dStdScale);
  pLayout->getCustomPrintScale(layoutData.m_dCustomScaleNumerator, layoutData.m_dCustomScaleDenominator);

  layoutData.m_shadePlot = pLayout->shadePlot();
  SETBIT(layoutData.m_PlotLayoutFlags, OdTvDwgLayoutData::kPlotHidden, pLayout->plotHidden());

  SETBIT(layoutData.m_PlotLayoutFlags, OdTvDwgLayoutData::kScaleLineWeights, pLayout->scaleLineweights());
  SETBIT(layoutData.m_PlotLayoutFlags, OdTvDwgLayoutData::kPlotPlotstyles, pLayout->plotPlotStyles());

  layoutData.m_strCurStyleSheet = pLayout->getCurrentStyleSheet();

  //prepare stream
  OdStreamBufPtr pStreamBuff = OdMemoryStream::createNew();
  layoutData.write(pStreamBuff);
  pStreamBuff->rewind();

  OdUInt8Array buffer;
  buffer.resize(pStreamBuff->length());
  pStreamBuff->getBytes(buffer.asArrayPtr(), pStreamBuff->length());

  // Add user data
  OdTvByteUserData* pLayoutUserData = new OdTvByteUserData(buffer.asArrayPtr(), pStreamBuff->length(), OdTvByteUserData::kCopyOwn, true);
  pTvDevice->appendUserData(pLayoutUserData, appId);

  return appId;
}

void OdTvVisualizeDwgFiler::changeFrozenLayersToHidden(const OdDbDatabasePtr& pDb)
{
  OdDbLayerTablePtr pLayers = pDb->getLayerTableId().safeOpenObject(OdDb::kForWrite);
  OdDbSymbolTableIteratorPtr pIter = pLayers->newIterator();
  for (pIter->start(); !pIter->done(); pIter->step())
  {
    OdDbObjectId recordId = pIter->getRecordId();
    OdDbLayerTableRecordPtr pLayer = recordId.safeOpenObject(OdDb::kForWrite);

    if (pLayer->isFrozen())
    {
      m_frozenLayers.append((OdDbStub*)recordId);
      pLayer->setIsFrozen(false);
      pLayer->setIsOff(true);
    }
  }

}

void OdTvVisualizeDwgFiler::setFrozenLayersTotallyInvisible(const ExGsVisualizeDeviceCache* pDeviceCache)
{
  for (OdUInt64 i = 0; i < m_frozenLayers.length(); i++)
  {
    std::map< OdDbStub*, OdTvLayerId >::const_iterator pIter = pDeviceCache->m_cachedLayers.find(m_frozenLayers.at(i));
    if (pIter != pDeviceCache->m_cachedLayers.end())
      pIter->second.openObject(OdTv::kForWrite)->setTotallyInvisible(true);
  }
}

//***************************************************************************//
// 'OdTvVisualizeDwgFilerModule' methods implementation
//***************************************************************************//

ODRX_DEFINE_DYNAMIC_MODULE(OdTvVisualizeDwgFilerModule);

void OdTvVisualizeDwgFilerModule::initApp()
{
  // initialize the Visualize SDK
  odTvInitialize();
}

void OdTvVisualizeDwgFilerModule::uninitApp()
{
  // Uninitialize the Visualize SDK
  odTvUninitialize();
}

OdTvVisualizeFilerPtr OdTvVisualizeDwgFilerModule::getVisualizeFiler() const
{
  OdTvVisualizeFilerPtr pDwgFiler = new OdTvVisualizeDwgFiler();

  return pDwgFiler;
}
