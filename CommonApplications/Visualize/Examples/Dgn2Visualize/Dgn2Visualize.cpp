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

#include "RxObject.h"
#include "DgHostAppServices.h"
#include "HatchPatternManager.h"
#include "StaticRxObject.h"

#include "TvFactory.h"
#include "TvGeomCollector.h"
#include "TvFilerTimer.h"
#include "TvModuleNames.h"
#include "TvDatabaseCleaner.h"
#include "TvDatabaseUtils.h"

#include "Dgn2Visualize.h"
#include "RxInit.h"
#include "RxVariantValue.h"
#include "DgGiContext.h"
#include "DgGsManager.h"
#include "ColorMapping.h"

//SEA
#include "../Extensions/ExVisualizeDevice/GsVisualizeVectorizer.h"
#include "RxModelTreeBaseNode.h"
#include "RxModelHierarchyTreeBase.h"

OdTv::Units getUnits(OdDgModelPtr pModel, OdTv::Units defaultUnits, double& additionalConvCoeffToMeters)
{
  OdTv::Units tvUnits = defaultUnits;
  additionalConvCoeffToMeters = 1.;
 
  switch (pModel->getMasterUnit())
  {
  case OdDgModel::kUndefinedMeasure:
    tvUnits = defaultUnits;
    break;
  case OdDgModel::kMegameters:
    tvUnits = OdTv::kUserDefined;
    additionalConvCoeffToMeters = 1000000.;
    break;
  case OdDgModel::kKilometers:
    tvUnits = OdTv::kKilometers;
    break;
  case OdDgModel::kMeters:
    tvUnits = OdTv::kMeters;
    break;
  case OdDgModel::kDecimeters:
    tvUnits = OdTv::kUserDefined;
    additionalConvCoeffToMeters = 0.1;
    break;
  case OdDgModel::kCentimeters:
    tvUnits = OdTv::kCentimeters;
    break;
  case OdDgModel::kMillimeters:
    tvUnits = OdTv::kMillimeters;
    break;
  case OdDgModel::kMicrometers:
    tvUnits = OdTv::kMicrometers;
    break;
  case OdDgModel::kNanometers:
    tvUnits = OdTv::kUserDefined;
    additionalConvCoeffToMeters = 1.0e-9;
    break;
  case OdDgModel::kPicometers:
    tvUnits = OdTv::kUserDefined;
    additionalConvCoeffToMeters = 1.0e-12;
    break;
  case OdDgModel::kMiles:
    tvUnits = OdTv::kMiles;
    break;
  case OdDgModel::kYards:
    tvUnits = OdTv::kYards;
    break;
  case OdDgModel::kFeet:
    tvUnits = OdTv::kFeet;
    break;
  case OdDgModel::kInches:
    tvUnits = OdTv::kInches;
    break;
  case OdDgModel::kMils:
    tvUnits = OdTv::kMils;
    break;
  case OdDgModel::kUSSurveyFeet:
    tvUnits = OdTv::kUserDefined;
    additionalConvCoeffToMeters = 0.3048 / 0.999998;
    break;
  case OdDgModel::kMicroinches:
    tvUnits = OdTv::kMicroInches;
    break;
  }

  return tvUnits;
}

//*************************************************************************************//
// Implementation of the methods of the inheritants of 'OdTvVisualizeDwgFilerDbSource'
//*************************************************************************************//
class OdTvVisualizeDgnFilerSourceFromDb : public OdTvVisualizeDgnFilerDbSource
{
  OdDbBaseDatabase *mDatabase;

public:
  OdTvVisualizeDgnFilerSourceFromDb(OdDbBaseDatabase *pDatabase) : mDatabase(pDatabase) {};
  virtual OdDgDatabasePtr   getDb() { return mDatabase; };
  virtual bool              odWasInitialized() const { return false; }
  virtual OdString          getFilename()
  {
    OdDgDatabasePtr pDb = mDatabase;
    if (!pDb.isNull())
    {
      OdString fileName = pDb->getFilename();
      if (!fileName.isEmpty())
        return fileName;
    }

    return OD_T("NoNameDgnDatabase");
  }
};


class OdTvVisualizeDgnFilerSourceFromFile : public OdTvVisualizeDgnFilerDbSource
{
  OdStaticRxObject<OdTvDgnService> svcs;
  OdString mFilePath;

protected:
  double         m_initTime;

public:
  OdTvVisualizeDgnFilerSourceFromFile(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, const DGN2Visualize::OdTvVisualizeDgnFilerPropertiesPtr pProperties) { initialize(filePath, pProfileRes, pProperties); };
  virtual OdDgDatabasePtr getDb() { return svcs.readFile(mFilePath); };
  virtual double          getInitTime() const { return m_initTime; }
  virtual OdString        getFilename()
  {
    //generate name for the stream file
    return OdTvDatabaseUtils::getFileNameFromPath(mFilePath);
  };

protected:
  OdTvVisualizeDgnFilerSourceFromFile() {};
  void initialize(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, const DGN2Visualize::OdTvVisualizeDgnFilerPropertiesPtr pProperties)
  {
    mFilePath = filePath;

    OdTvFilerTimer timing(needTimer(pProfileRes));
    timing.startTotal();

    svcs.setMS_3DOBJ_WF_ISOLINES(pProperties->getUseIsolinesFor3DObjects());

    //load module
    ::odrxDynamicLinker()->loadModule(OdDgnDbModuleName, false);

    timing.endTotal();
    m_initTime = timing.getTotalTime();
  };
};

//***************************************************************************//
// 'OdTvVisualizeDgnFilerProperties' methods implementation
//***************************************************************************//

using namespace DGN2Visualize;

OdTvVisualizeDgnFilerProperties::OdTvVisualizeDgnFilerProperties() : m_flags(kClearEmptyObjects | kUseIsolinesFor3DObjects), m_pCallback(0)
{
  m_importRect.xmax = 0;
  m_importRect.xmin = 0;
  m_importRect.ymax = 0;
  m_importRect.ymin = 0;

  m_defaultUnits = OdTv::kMillimeters;
}

OdRxDictionaryPtr OdTvVisualizeDgnFilerProperties::createObject()
{
  return OdRxObjectImpl<OdTvVisualizeDgnFilerProperties, OdRxDictionary>::createObject();
}

OdTvVisualizeDgnFilerProperties::~OdTvVisualizeDgnFilerProperties()
{
}

namespace DGN2Visualize
{
  ODRX_DECLARE_PROPERTY(Palette)
  ODRX_DECLARE_PROPERTY(DCRect)
  ODRX_DECLARE_PROPERTY(ObjectNaming)
  ODRX_DECLARE_PROPERTY(StoreSourceObjects)
  ODRX_DECLARE_PROPERTY(FeedbackForChooseCallback)
  ODRX_DECLARE_PROPERTY(ClearEmptyObjects)
  ODRX_DECLARE_PROPERTY(UseIsolinesFor3DObjects)
  ODRX_DECLARE_PROPERTY(AppendTransform)
  ODRX_DECLARE_PROPERTY(NeedCDATree)
  ODRX_DECLARE_PROPERTY(NeedCollectPropertiesInCDA)
  ODRX_DECLARE_PROPERTY(DefaultUnits)

  ODRX_BEGIN_DYNAMIC_PROPERTY_MAP(OdTvVisualizeDgnFilerProperties);
  ODRX_GENERATE_PROPERTY(Palette)
  ODRX_GENERATE_PROPERTY(DCRect)
  ODRX_GENERATE_PROPERTY(ObjectNaming)
  ODRX_GENERATE_PROPERTY(StoreSourceObjects)
  ODRX_GENERATE_PROPERTY(FeedbackForChooseCallback)
  ODRX_GENERATE_PROPERTY(ClearEmptyObjects)
  ODRX_GENERATE_PROPERTY(UseIsolinesFor3DObjects)
  ODRX_GENERATE_PROPERTY(AppendTransform)
  ODRX_GENERATE_PROPERTY(NeedCDATree)
  ODRX_GENERATE_PROPERTY(NeedCollectPropertiesInCDA)
  ODRX_GENERATE_PROPERTY(DefaultUnits)
  ODRX_END_DYNAMIC_PROPERTY_MAP(OdTvVisualizeDgnFilerProperties);

  ODRX_DEFINE_PROPERTY_METHODS(Palette, OdTvVisualizeDgnFilerProperties, getPalette, setPalette, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(DCRect, OdTvVisualizeDgnFilerProperties, getDCRect, setDCRect, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(ObjectNaming, OdTvVisualizeDgnFilerProperties, getObjectNaming, setObjectNaming, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(StoreSourceObjects, OdTvVisualizeDgnFilerProperties, getStoreSourceObjects, setStoreSourceObjects, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(FeedbackForChooseCallback, OdTvVisualizeDgnFilerProperties, getFeedbackForChooseCallback, setFeedbackForChooseCallback, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(ClearEmptyObjects, OdTvVisualizeDgnFilerProperties, getClearEmptyObjects, setClearEmptyObjects, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(UseIsolinesFor3DObjects, OdTvVisualizeDgnFilerProperties, getUseIsolinesFor3DObjects, setUseIsolinesFor3DObjects, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(AppendTransform, OdTvVisualizeDgnFilerProperties, getAppendTransform, setAppendTransform, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(NeedCDATree, OdTvVisualizeDgnFilerProperties, getNeedCDATree, setNeedCDATree, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(NeedCollectPropertiesInCDA, OdTvVisualizeDgnFilerProperties, getNeedCollectPropertiesInCDA, setNeedCollectPropertiesInCDA, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(DefaultUnits, OdTvVisualizeDgnFilerProperties, getDefaultUnits, setDefaultUnits, getIntPtr);
}

void OdTvVisualizeDgnFilerProperties::setPalette(OdIntPtr palette)
{
  const ODCOLORREF* pPalette = (const ODCOLORREF*)(palette);

  m_pPalette = pPalette;
}

OdIntPtr OdTvVisualizeDgnFilerProperties::getPalette() const
{
  return (OdIntPtr)(m_pPalette);
}

void OdTvVisualizeDgnFilerProperties::setDCRect(OdIntPtr rect)
{
  OdTvDCRect* pRect = (OdTvDCRect*)(rect);
  if (!pRect)
  {
    ODA_ASSERT(false);
  }

  m_importRect = *pRect;
}

OdIntPtr OdTvVisualizeDgnFilerProperties::getDCRect() const
{
  return (OdIntPtr)(&m_importRect);
}

void OdTvVisualizeDgnFilerProperties::setFeedbackForChooseCallback(OdIntPtr pCallback)
{
  m_pCallback = (OdTvFeedbackForChooseCallback)pCallback;
}

OdIntPtr OdTvVisualizeDgnFilerProperties::getFeedbackForChooseCallback() const
{
  return (OdIntPtr)m_pCallback;
}

void OdTvVisualizeDgnFilerProperties::setAppendTransform(OdIntPtr pTransform)
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

OdIntPtr OdTvVisualizeDgnFilerProperties::getAppendTransform() const
{
  return (OdIntPtr)(&m_appendTransform);
}

//***************************************************************************//
// 'OdTvVisualizeDgnFiler' methods implementation
//***************************************************************************//

OdTvVisualizeDgnFiler::OdTvVisualizeDgnFiler() : m_properties(OdTvVisualizeDgnFilerProperties::createObject()), m_pDl(NULL)
{
}

OdTvVisualizeDgnFiler::~OdTvVisualizeDgnFiler()
{
  if (m_pDl)
    m_pDl = NULL;
}

OdTvDatabaseId OdTvVisualizeDgnFiler::loadFrom(OdDbBaseDatabase *pDatabase, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeDgnFilerSourceFromDb dl(pDatabase);
  return loadFrom(&dl, pProfileRes, rc);
}

OdTvDatabaseId OdTvVisualizeDgnFiler::loadFrom(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  if (rc)
    *rc = tvNotSupported;

  return OdTvDatabaseId();
}

OdTvDatabaseId OdTvVisualizeDgnFiler::loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeDgnFilerSourceFromFile dl(filePath, pProfileRes, m_properties);
  return loadFrom(&dl, pProfileRes, rc);
}

OdTvDatabaseId OdTvVisualizeDgnFiler::generate(OdTvFilerTimeProfiling* pProfileRes) const
{
  return OdTvDatabaseId();
}

OdTvModelId OdTvVisualizeDgnFiler::appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase *pDatabase, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeDgnFilerSourceFromDb dl(pDatabase);
  return appendFrom(databaseId, &dl, pProfileRes, rc);
}

OdTvModelId OdTvVisualizeDgnFiler::appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf        *pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  if (rc)
    *rc = tvNotSupported;

  return OdTvModelId();
}

OdTvModelId OdTvVisualizeDgnFiler::appendFrom(const OdTvDatabaseId& databaseId, const OdString    &filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeDgnFilerSourceFromFile dl(filePath, pProfileRes, m_properties);
  return appendFrom(databaseId, &dl, pProfileRes, rc);
}

OdTvResult OdTvVisualizeDgnFiler::startActionsWithNativeProperties(const OdString& sFilePath, bool bPartial)
{
  if (!m_pDatabaseForNativeProp.isNull() && m_pDatabaseForNativeProp->getFilename() != sFilePath)
    m_pDatabaseForNativeProp.release();
  else if (!m_pDatabaseForNativeProp.isNull())
    return tvOk;

  OdTvResult rc = tvOk;
  const_cast<OdTvVisualizeDgnFiler*>(this)->m_pDl = new OdTvVisualizeDgnFilerSourceFromFile(sFilePath, NULL, m_properties);

  {
    if (m_pRxPropertiesModule.isNull())
      m_pRxPropertiesModule = ::odrxDynamicLinker()->loadModule(L"RxProperties");

    if (m_pDgPropertiesModule.isNull())
      m_pDgPropertiesModule = ::odrxDynamicLinker()->loadModule(L"DgProperties");

    if (m_pDgDatabaseModule.isNull())
      m_pDgDatabaseModule = ::odrxDynamicLinker()->loadModule(OdDgnDbModuleName);
    
    try
    {
      m_pDatabaseForNativeProp = m_pDl->getDb();
    }
    catch (...)
    {
      return tvFilerEmptyInternalDatabase;
    }

  }

  return rc;
}

bool OdTvVisualizeDgnFiler::isActionsWithNativePropertiesStarted(const OdString& sFilePath)
{
  if (!m_pDatabaseForNativeProp.isNull() && m_pDatabaseForNativeProp->getFilename() == sFilePath)
    return true;

  return false;
}

OdTvResult OdTvVisualizeDgnFiler::endActionsWithNativeProperties()
{
  if (!m_pDatabaseForNativeProp.isNull())
    m_pDatabaseForNativeProp.release();

  if (!m_pDgPropertiesModule.isNull())
  {
    m_pRxPropertiesModule.release();
    m_pDgPropertiesModule.release();
    m_pDgDatabaseModule.release();
    ::odrxDynamicLinker()->unloadModule(L"RxProperties");
    ::odrxDynamicLinker()->unloadModule(L"DgProperties");
    ::odrxDynamicLinker()->unloadModule(OdDgnDbModuleName);
    ::odrxDynamicLinker()->unloadUnreferenced();

    if (m_pDl)
    {
      delete m_pDl;
      m_pDl = NULL;
    }
  }

  return tvOk;
}

OdRxMemberIteratorPtr OdTvVisualizeDgnFiler::getNativePropertiesIterator(OdUInt64 dbHandle, OdTvResult* rc)
{
  if (m_pDatabaseForNativeProp.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedDatabase;
    return OdRxMemberIteratorPtr();
  }

  OdRxMemberIteratorPtr pIter;
  if (dbHandle == 0)
    pIter = OdRxMemberQueryEngine::theEngine()->newMemberIterator(m_pDatabaseForNativeProp);
  else
  {
    OdDgElementId elementId = m_pDatabaseForNativeProp->getElementId(dbHandle);
    if (elementId.isNull())
    {
      if (rc)
        *rc = tvNativePropMissedObject;
      return OdRxMemberIteratorPtr();
    }
    pIter = OdRxMemberQueryEngine::theEngine()->newMemberIterator(elementId.openObject(OdDg::kForRead));
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

OdRxValue OdTvVisualizeDgnFiler::getNativePropertyValue(OdUInt64 dbHandle, const OdRxPropertyPtr& pProperty, bool* bReadOnly, OdTvResult* rc)
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

  OdRxObjectPtr pElement;
  if (dbHandle == 0)
    pElement = m_pDatabaseForNativeProp;
  else
  {
    OdDgElementId elementId = m_pDatabaseForNativeProp->getElementId(dbHandle);
    pElement = elementId.openObject(OdDg::kForWrite);
  }

  if (pElement.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedObject;
    return OdRxValue();
  }

  OdRxValue value;
  OdResult odRes = pProperty->getValue(pElement, value);
  if (bReadOnly)
    *bReadOnly = pProperty->isReadOnly(pElement);

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

OdRxValueIteratorPtr OdTvVisualizeDgnFiler::getNativeCollectionPropertyIterator(OdUInt64 dbHandle, const OdRxCollectionPropertyPtr& pCollectionProperty, bool* bReadOnly, OdTvResult* rc)
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
    pValIter = pCollectionProperty->newValueIterator(m_pDatabaseForNativeProp);

    if (bReadOnly)
      *bReadOnly = pCollectionProperty->isReadOnly(m_pDatabaseForNativeProp);
  }
  else
  {
    OdDgElementId elementId = m_pDatabaseForNativeProp->getElementId(dbHandle);
    if (elementId.isNull())
    {
      if (rc)
        *rc = tvNativePropMissedObject;
      return OdRxValueIteratorPtr();
    }
    pValIter = pCollectionProperty->newValueIterator(elementId.openObject(OdDg::kForRead));

    if (bReadOnly)
      *bReadOnly = pCollectionProperty->isReadOnly(elementId.openObject(OdDg::kForRead));
  }


  if (rc)
    *rc = tvOk;

  return pValIter;
}

OdTvResult OdTvVisualizeDgnFiler::setNativePropertyValue(OdUInt64 dbHandle, OdRxPropertyPtr& pProperty, const OdRxValue& value)
{
  if (pProperty.isNull())
    return tvInvalidInput;

  if (m_pDatabaseForNativeProp.isNull())
    return tvNativePropMissedDatabase;

  OdRxObjectPtr pElement;
  if (dbHandle == 0)
    pElement = m_pDatabaseForNativeProp;
  else
  {
    OdDgElementId elementId = m_pDatabaseForNativeProp->getElementId(dbHandle);
    pElement = elementId.openObject(OdDg::kForWrite);
  }

  if (pElement.isNull())
    return tvNativePropMissedObject;

  pProperty->setValue(pElement, value);

  return tvOk;
}

OdDbBaseDatabase* OdTvVisualizeDgnFiler::getNativeDatabase(OdTvResult* rc) const
{
  if (m_pDatabaseForNativeProp.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedDatabase;
    return NULL;
  }

  return (OdDbBaseDatabase*)m_pDatabaseForNativeProp.get();
}

OdTvDatabaseId OdTvVisualizeDgnFiler::loadFrom(OdTvVisualizeDgnFilerDbSource *pDgnDatabaseSource, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvDatabaseId tvDbId;

  if (rc)
    *rc = tvOk;

  //check that time profiling is need
  bool bUseTimeProfiling = needTimer(pProfileRes);
  double internalTiming = 0.;
  double externalTiming = 0.;

  //prepare timing object
  OdTvFilerTimer timing(bUseTimeProfiling);
  timing.startTotal();

  double dbReadingTime = 0.;
  
  //store visualize device module name
  OdString moduleName;
  try
  {
    OdDgDatabasePtr pDb = pDgnDatabaseSource->getDb();

    if (!pDb.isNull())
    {
      //check existence of the view group and model
      OdDgViewGroupPtr pViewGroup = pDb->getActiveViewGroupId().openObject(OdDg::kForRead);

      OdDgElementId dgActiveModelId = pDb->getActiveModelId();
      if (dgActiveModelId.isNull())
      {
        //  If Model is is invalid let's try to get & use a Default.
        dgActiveModelId = pDb->getDefaultModelId();
        pDb->setActiveModelId(dgActiveModelId);
      }

      if (dgActiveModelId.isNull())
        return tvDbId;

      if (pViewGroup.isNull())
      {
        pViewGroup = pDb->recommendActiveViewGroupId().openObject();
        if (pViewGroup.isNull())
        {
          // Add View group
          OdDgModelPtr pModel = OdDgModel::cast(dgActiveModelId.openObject());
          pModel->createViewGroup();
          pModel->fitToView();
          pViewGroup = pDb->recommendActiveViewGroupId().openObject();
        }
      }

      if (pViewGroup.isNull())
        return tvDbId;

      timing.endTotal();
      dbReadingTime = timing.getTotalTime() + pDgnDatabaseSource->getInitTime();

      OdTvFilerFeedbackForChooseObject filerFeedbackForChooseObject(OD_T("Choose views for import"));
      bool bCanceled = false;
      getChoosedViews(pViewGroup, filerFeedbackForChooseObject, bCanceled);
      if (bCanceled)
      {
        if (rc)
          *rc = tvFilerEmptyInternalDatabase;
        pDb = NULL;
        //unload Dgn modules (try to emulate the OdUninitialized for DGN)
        //here we will unload all including Visualize device
        odrxDynamicLinker()->unloadUnreferenced();
        return tvDbId;
      }

      timing.startTotal();
      timing.startVectorizing();

      OdGsModulePtr pGs = ::odrxDynamicLinker()->loadModule(OdTvVisualizeDeviceModuleName, false);
      if (pGs.isNull())
      {
        if (rc)
          *rc = tvMissingVisualizeDeviceModule;
        return tvDbId;
      }

      //get the palette from the database
      const ODCOLORREF* refColors = OdDgColorTable::currentPalette(pDb);

      //For the each 'OdDgView' will be created a separate device with a separate model.
      //More of it, for each view it will used a new Visualize device. At the same time the 
      //TV database will be the same. That's why we will create the tv database outside of the
      //visualize device.

      //create empty tv database.
      OdTvFactoryId tvFactoryId = odTvGetFactory();
      tvDbId = tvFactoryId.createDatabase();
      OdTvDatabasePtr pTvDb = tvDbId.openObject(OdTv::kForWrite);

      // save filename to database user data
      OdTvDatabaseUtils::writeFileNameToTvDatabase(tvDbId, pDgnDatabaseSource->getFilename());

      //Also there are some objects like material which should be the same for all models. For this 
      //purpose we will use special Visualize device cache
      
      //initialize cache and switch it to the "write only" mode
      ExGsVisualizeDeviceCache deviceCache;
      deviceCache.m_bApplyCacheData = false;

      //run cycle over views in the view group
      unsigned int idDevice = 0;
      OdDgElementIteratorPtr pIt = pViewGroup->createIterator();

      // Models counter
      unsigned int iModels = 0;

      OdGsDeviceForDgModelPtr pCachedDevice;
      for (; !pIt->done(); pIt->step())
      {
        OdDgViewPtr pCurView = OdDgView::cast(pIt->item().openObject(OdDg::kForRead));

        //construct name of the view
        OdString strIndex;
        strIndex.format(OD_T("%d"), pCurView->getIndex());

        if (!filerFeedbackForChooseObject.find(OdTvFilerFeedbackItemForChoose(strIndex, true)))
          continue;

        if (pCurView.get() && pCurView->getVisibleFlag())
        {
          if (!pCurView.isNull())
          {
            // get Dg model
            OdDgElementId dgMoodelId = pCurView->getModelId();
            OdDgElementId dgViewId = pCurView->elementId();

            //get the background color from the model
            OdDgModelPtr pModel = dgMoodelId.safeOpenObject();
            ODCOLORREF background = pModel->getBackground();

            //create device
            OdGsDevicePtr pDevice = pGs->createDevice();

            OdGiContextForDgDatabasePtr pDgnContext = OdGiContextForDgDatabaseToPlotStyleSupport::createObject();
            pDgnContext->setDatabase(pDb);
            pDgnContext->setView(pCurView);
            pDgnContext->enableGsModel(true);
            pDgnContext->setPaletteBackground(background);

            pDgnContext->setLineWeightConfiguration(OdGiContext::kPointLineWeight, 1);
            pDgnContext->setLineWeightConfiguration(OdGiContext::kLineCapStyle, (OdUInt32)(OdPs::kLesButt));
            pDgnContext->setLineWeightConfiguration(OdGiContext::kLineJoinStyle, (OdUInt32)(OdPs::kLjsDiamond));

            OdRxDictionaryPtr pProperties = pDevice->properties();
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
                pProperties->putAt(OD_T("WriteUserData"), OdRxVariantValue(m_properties->getStoreSourceObjects()));
              if (pProperties->has(OD_T("GenerateEntityNames")))
                pProperties->putAt(OD_T("GenerateEntityNames"), OdRxVariantValue(m_properties->getObjectNaming()));
              if (pProperties->has(OD_T("DeviceCache")))
                pProperties->putAt(OD_T("DeviceCache"), OdRxVariantValue((OdIntPtr)(&deviceCache)));
              if (pProperties->has(OD_T("CompareUnnamedImages")))
                pProperties->putAt(OD_T("CompareUnnamedImages"), OdRxVariantValue(true));
              if (pProperties->has(OD_T("EnableViewDependentEntities")))
                pProperties->putAt(OD_T("EnableViewDependentEntities"), OdRxVariantValue(true));

              if (pProperties->has(OD_T("ModelName")))
              {
                OdString strModelName = pModel->getName();
                //OdString viewPartOfTheName;
                //viewPartOfTheName.format(OD_T("_View%d"), pCurView->getIndex());
                //strModelName += viewPartOfTheName;
                pProperties->putAt(OD_T("ModelName"), OdRxVariantValue(strModelName));
              }
              //Write font file path as user data
              if( pProperties->has( OD_T("WriteFontFilePath") ))
                pProperties->putAt( OD_T("WriteFontFilePath"), OdRxVariantValue( true ) );
              //Do not transform layer lineweight
              if( pProperties->has( OD_T( "DisableNonEntityLineweightTransformation" ) ) )
                pProperties->putAt( OD_T( "DisableNonEntityLineweightTransformation" ), OdRxVariantValue( true ) );
            }

            //set the palette and background to the device
            OdArray<ODCOLORREF, OdMemoryAllocator<ODCOLORREF> > pPalCpy;
            pPalCpy.insert(pPalCpy.begin(), refColors, refColors + 256);

            // Color with #255 always defines backround. The background of the active model must be considered in the device palette.
            pPalCpy[255] = background;
            // Note: This method should be called to resolve "white background issue" before setting device palette
            bool bCorrected = OdDgColorTable::correctPaletteForWhiteBackground(pPalCpy.asArrayPtr());

            pDevice->setLogicalPalette(pPalCpy.asArrayPtr(), 256);
            pDevice->setBackgroundColor(background);

            // setup the device and views
            OdGsDeviceForDgModelPtr pDeviceForDg = OdGsDeviceForDgModel::setupModelView(dgMoodelId, dgViewId, pDevice, pDgnContext);
            if (pCachedDevice.isNull())
            {
              pCachedDevice = pDeviceForDg;
            }

            //call onsize
            OdTvDCRect* pRect = (OdTvDCRect*)m_properties->getDCRect();
            if (pRect && (pRect->xmax > 0 || pRect->xmin > 0 || pRect->ymax > 0 || pRect->ymin > 0))
            {
              OdGsDCRect  gsRect(pRect->xmin, pRect->xmax, pRect->ymin, pRect->ymax);
              pDevice->onSize(gsRect);
            }

            //call draw to the Visualize database
            pDeviceForDg->update();

            if (bUseTimeProfiling)
            {
#if !defined(__APPLE__)
              if (pProperties->has(OD_T("TvElapsedTime")))
              {
                internalTiming += OdRxVariantValue(pProperties->getAt(OD_T("TvElapsedTime")).get())->getDouble();
              }
#endif
            }

            //we should update the state of the device cache marked it to use the cached data during next vectorizing
            if (pProperties->has(OD_T("DeviceCache")))
            {
              deviceCache.m_bApplyCacheData = true;
              OdIntPtr ptr = OdRxVariantValue(pProperties->getAt(OD_T("DeviceCache")).get())->getIntPtr();
            }

            //setup active view and the relation between views
            timing.startMisc();
            if (tvDbId.isValid())
            {
              // Set units to new models
              OdTvModelsIteratorPtr modelsIterPtr = tvDbId.openObject()->getModelsIterator();
              unsigned int curModel = 0;
              while (!modelsIterPtr->done())
              {
                OdTvModelPtr pTvModel = modelsIterPtr->getModel().openObject(OdTv::kForWrite);
                if (!pTvModel.isNull())
                {
                  curModel++;
                  if (curModel > iModels)
                  {
                    //get units
                    double addUnitCoefToMeters = 0.;
                    OdTv::Units tvUnits = getUnits(pModel, (OdTv::Units)m_properties->getDefaultUnits(), addUnitCoefToMeters);
                    pTvModel->setUnits(tvUnits, tvUnits == OdTv::kUserDefined ? addUnitCoefToMeters : 1.);
                  }

                }
                modelsIterPtr->step();
              }
              iModels = curModel;

              int iActViewViewInd = getActiveViewId(pDeviceForDg.get());
              if (iActViewViewInd >= 0)
              {
                //get current tv device
                OdTvGsDeviceId tvDeviceId = getActiveTvDevice(tvDbId, idDevice);
                OdTvGsDevicePtr pTvDevice = tvDeviceId.openObject(OdTv::kForWrite);
                if (!pTvDevice.isNull())
                {
                  OdString newName;
                  newName.format(OD_T("%d"), pCurView->getIndex());
                  pTvDevice->setName(newName);
                }

                OdTvGsViewId tvViewId = getActiveTvView(tvDeviceId, iActViewViewInd);
                if (!tvDeviceId.isNull() && !tvViewId.isNull())
                {
                  OdTvGsViewPtr pActiveTvView = tvViewId.openObject(OdTv::kForWrite);
                  pActiveTvView->setActive(true);

                  // mark other views sibling
                  if (!pTvDevice.isNull())
                  {
                    for (int i = 0; i < pTvDevice->numViews(); i++)
                    {
                      OdTvGsViewId viewId = pTvDevice->viewAt(i);
                      OdTvGsViewPtr pView = viewId.openObject(OdTv::kForWrite);
                      for (int j = 0; j < pView->numModels(); j++)
                      {
                        if (pView->numModels() == 1)
                          pView->setName(pView->modelAt(j).openObject()->getName());
                      }
                      
                      if (i == iActViewViewInd)
                        continue;

                      pActiveTvView->addSibling(viewId);
                    }
                  }
                }
              }
            }

            timing.endMisc();
            externalTiming += timing.getMiscTime();

            idDevice++;
          }
        }
      }

      moduleName = pGs->moduleName();

      timing.startMisc();

      if (tvDbId.isValid() && m_properties->getClearEmptyObjects())
        OdTvDatabaseCleaner::cleanTvDatabase(tvDbId);

      if (m_properties->getNeedCDATree())
        createCommonDataAccessTree(pTvDb, pDb, pDgnDatabaseSource->getFilename() + OD_T(".dgn"));

      timing.endMisc();
      externalTiming += timing.getMiscTime();

      timing.endVectorizing();


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
  }

  //unload Dgn modules (try to emulate the OdUninitialized for DGN)
  //here we will unload all including Visualize device
  odrxDynamicLinker()->unloadUnreferenced();

  timing.endTotal();

  if (pProfileRes)
  {
    pProfileRes->setImportTime(OdInt64(dbReadingTime * 1000.));
    pProfileRes->setVectorizingTime(OdInt64(timing.getVectorizingTime() * 1000.));
#if !defined(__APPLE__)
    pProfileRes->setTvTime(OdInt64((internalTiming + externalTiming) * 1000.));
#endif
  }

  return tvDbId;
}

OdTvModelId OdTvVisualizeDgnFiler::appendFrom(const OdTvDatabaseId& databaseId, OdTvVisualizeDgnFilerDbSource *pDgnDatabaseSource, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvModelId tvModelId;

  if (rc)
    *rc = tvOk;

  OdTvGsDeviceId activeTvGsDeviceId;
  {
    OdTvDatabasePtr pTvDb = databaseId.openObject();
    OdTvDevicesIteratorPtr devicesIteratorPtr = pTvDb->getDevicesIterator();
    while (!devicesIteratorPtr->done())
    {
      activeTvGsDeviceId = devicesIteratorPtr->getDevice();
      if (activeTvGsDeviceId.openObject()->getActive())
        break;
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

  //collcet current models and blocks
  std::set<OdTvGsViewId> foreignViews;
  std::set<OdTvModelId> foreignModels;
  std::set<OdTvBlockId> foreignBlocks;
  OdTvDatabaseUtils::collectViewsModelsAndBlocks(databaseId, foreignViews, foreignModels, foreignBlocks);

  //check that time profiling is need
  bool bUseTimeProfiling = false;
  if (pProfileRes)
    bUseTimeProfiling = true;
  double internalTiming = 0.;
  double externalTiming = 0;

  //prepare timing object
  OdTvFilerTimer timing(bUseTimeProfiling);
  timing.startTotal();

  // Generate model name
  OdString modelName = OdTvDatabaseUtils::generateModelName(databaseId, pDgnDatabaseSource->getFilename());

  //store visualize device module name
  OdString moduleName;
  try
  {
    OdDgDatabasePtr pDb = pDgnDatabaseSource->getDb();

    if (!pDb.isNull())
    {
      //check existance of the view group and model
      OdDgViewGroupPtr pViewGroup = pDb->getActiveViewGroupId().openObject(OdDg::kForRead);

      OdDgElementId dgActiveModelId = pDb->getActiveModelId();
      if (dgActiveModelId.isNull())
      {
        //  If Model is is invalid let's try to get & use a Default.
        dgActiveModelId = pDb->getDefaultModelId();
        pDb->setActiveModelId(dgActiveModelId);
      }

      if (dgActiveModelId.isNull())
      {
        if (rc)
          *rc = tvNullObjectPtr;
        return tvModelId;
      }

      if (pViewGroup.isNull())
      {
        pViewGroup = pDb->recommendActiveViewGroupId().openObject();
        if (pViewGroup.isNull())
        {
          // Add View group
          OdDgModelPtr pModel = OdDgModel::cast(dgActiveModelId.openObject());
          pModel->createViewGroup();
          pModel->fitToView();
          pViewGroup = pDb->recommendActiveViewGroupId().openObject();
        }
      }

      if (pViewGroup.isNull())
      {
        if (rc)
          *rc = tvNullObjectPtr;
        return tvModelId;
      }

      timing.startVectorizing();

      OdGsModulePtr pGs = ::odrxDynamicLinker()->loadModule(OdTvVisualizeDeviceModuleName, false);
      if (pGs.isNull())
      {
        if (rc)
          *rc = tvMissingVisualizeDeviceModule;
        return tvModelId;
      }

      //get the palette from the database
      if (activeTvGsDeviceId.isNull())
      {
        const ODCOLORREF* refColors = OdDgColorTable::currentPalette(pDb);
        pPalCpy.insert(pPalCpy.begin(), refColors, refColors + 256);
      }

      // save file name to database user data
      OdTvDatabaseUtils::writeFileNameToTvDatabase(databaseId, pDgnDatabaseSource->getFilename());

      //initialize cache and switch it to the "write only" mode
      ExGsVisualizeDeviceCache deviceCache;
      deviceCache.m_bApplyCacheData = false;

      OdDgElementIteratorPtr pIt = pViewGroup->createIterator();
      if (pIt->done())
      {
        if (rc)
          *rc = tvNullObjectPtr;
        return tvModelId;
      }
      
      OdDgViewPtr pCurView;
      for (; !pIt->done(); pIt->step())
      {
        OdDgViewPtr pImportView = OdDgView::cast(pIt->item().openObject(OdDg::kForRead));
        if (pImportView.get() && pImportView->getVisibleFlag())
        {
          pCurView = pImportView;
          break;
        }
      }

      if (!pCurView.isNull())
      {
        // get Dg model
        OdDgElementId dgMoodelId = pCurView->getModelId();
        OdDgElementId dgViewId = pCurView->elementId();

        //get the background color from the model
        OdDgModelPtr pModel = dgMoodelId.safeOpenObject();
        if (activeTvGsDeviceId.isNull())
          background = pModel->getBackground();

        //create device
        OdGsDevicePtr pDevice = pGs->createDevice();

        OdGiContextForDgDatabasePtr pDgnContext = OdGiContextForDgDatabaseToPlotStyleSupport::createObject();
        pDgnContext->setDatabase(pDb);
        pDgnContext->setView(pCurView);
        pDgnContext->enableGsModel(true);

        pDgnContext->setLineWeightConfiguration(OdGiContext::kPointLineWeight, 1);
        pDgnContext->setLineWeightConfiguration(OdGiContext::kLineCapStyle, (OdUInt32)(OdPs::kLesButt));
        pDgnContext->setLineWeightConfiguration(OdGiContext::kLineJoinStyle, (OdUInt32)(OdPs::kLjsDiamond));
        OdRxDictionaryPtr pProperties = pDevice->properties();
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
            pProperties->putAt(OD_T("TvDatabaseID"), OdRxVariantValue((OdIntPtr)(&databaseId)));

          if (pProperties->has(OD_T("WriteUserData")))
            pProperties->putAt(OD_T("WriteUserData"), OdRxVariantValue(m_properties->getStoreSourceObjects()));
          if (pProperties->has(OD_T("GenerateEntityNames")))
            pProperties->putAt(OD_T("GenerateEntityNames"), OdRxVariantValue(m_properties->getObjectNaming()));
          if (pProperties->has(OD_T("ModelName")))
            pProperties->putAt(OD_T("ModelName"), OdRxVariantValue(modelName));
          if (pProperties->has(OD_T("DeviceCache")))
            pProperties->putAt(OD_T("DeviceCache"), OdRxVariantValue((OdIntPtr)(&deviceCache)));
          if (pProperties->has(OD_T("CompareUnnamedImages")))
            pProperties->putAt(OD_T("CompareUnnamedImages"), OdRxVariantValue(true));
          //we don't need to setup extents inside appendFrom since we can have additional units transform matrix here
          if (pProperties->has(OD_T("DisableSetingExtents")))
            pProperties->putAt(OD_T("DisableSetingExtents"), OdRxVariantValue(true));

          if (!activeTvGsDeviceId.isNull())
          {
            if (pProperties->has(OD_T("IgnoreFlags")))
              pProperties->putAt(OD_T("IgnoreFlags"), OdRxVariantValue(OdUInt16(1)/*DeviceIgnoreFlags::kIgnoreViewInfoFlags*/));
            if (pProperties->has(OD_T("NamePrefix")))
              pProperties->putAt(OD_T("NamePrefix"), OdRxVariantValue(modelName));
            if (pProperties->has(OD_T("TvDeviceDAM")))
              pProperties->putAt(OD_T("TvDeviceDAM"), OdRxVariantValue((OdIntPtr)(&activeTvGsDeviceId)));

            OdTvGsViewId viewId = activeTvGsDeviceId.openObject()->getActiveView();
            OdString name = viewId.openObject()->getName();
            if (pProperties->has(OD_T("TvViewDAM")))
              pProperties->putAt(OD_T("TvViewDAM"), OdRxVariantValue((OdIntPtr)(&viewId)));
          }
          //Write font file path as user data
          if( pProperties->has( OD_T("WriteFontFilePath") ))
            pProperties->putAt( OD_T("WriteFontFilePath"), OdRxVariantValue( true ) );
        }

        if (activeTvGsDeviceId.isNull())
        {
          // Color with #255 always defines background. The background of the active model must be considered in the device palette.
          pPalCpy[255] = background;
          // Note: This method should be called to resolve "white background issue" before setting device palette
          OdDgColorTable::correctPaletteForWhiteBackground(pPalCpy.asArrayPtr());
        }

        pDevice->setLogicalPalette(pPalCpy.asArrayPtr(), 256);

        // Set properties if tv device does not exist.
        pDevice->setBackgroundColor(background);

        // setup the device and views
        OdGsDeviceForDgModelPtr pDeviceForDg = OdGsDeviceForDgModel::setupModelView(dgMoodelId, dgViewId, pDevice, pDgnContext);

        if (rect.xmax > 0 || rect.xmin > 0 || rect.ymax > 0 || rect.ymin > 0)
        {
          OdGsDCRect  gsRect(rect.xmin, rect.xmax, rect.ymin, rect.ymax);
          pDevice->onSize(gsRect);
        }

        //call draw to the Visualize database
        pDeviceForDg->update();

        if (bUseTimeProfiling)
        {
#if !defined(__APPLE__)
          if (pProperties->has(OD_T("TvElapsedTime")))
          {
            internalTiming += OdRxVariantValue(pProperties->getAt(OD_T("TvElapsedTime")).get())->getDouble();
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
            tvModelId = pTvDb->findModel(modelName);
          }

          OdTvDatabaseId& tvDvId = const_cast<OdTvDatabaseId&>(databaseId);
          OdTvDatabaseCleaner::cleanTvDatabaseForAppend(tvDvId, foreignViews, foreignModels, foreignBlocks);

          //apply transform if need 
          OdTvMatrix* pTransfrom = (OdTvMatrix*)m_properties->getAppendTransform();
          if (pTransfrom)
          {
            OdTvDatabaseId& tvDvId = const_cast<OdTvDatabaseId&>(databaseId);
            OdTvDatabaseUtils::applyTransformToTheModel(tvDvId, modelName, *pTransfrom);
          }

          //apply units
          if (!tvModelId.isNull())
          {
            OdTvModelPtr pTvModel = tvModelId.openObject(OdTv::kForWrite);
            if (!pTvModel.isNull())
            {
              //get units
              double addUnitCoefToMeters;
              OdTv::Units tvUnits = getUnits(pModel, (OdTv::Units)m_properties->getDefaultUnits(), addUnitCoefToMeters);
              pTvModel->setUnits(tvUnits, tvUnits == OdTv::kUserDefined ? addUnitCoefToMeters : 1.);
            }
          }

          timing.endMisc();
        }
      }

      moduleName = pGs->moduleName();

      if (m_properties->getNeedCDATree())
      {
        OdTvDatabasePtr pTvDb = databaseId.openObject();
        createCommonDataAccessTree(pTvDb, pDb, pDgnDatabaseSource->getFilename() + OD_T(".dgn"));
      }

      externalTiming = timing.getMiscTime();

      timing.endVectorizing();

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
  }

  //unload Dgn modules (try to emulate the OdUninitialized for DGN)
  //here we will unload all including Visualize device
  odrxDynamicLinker()->unloadUnreferenced();

  timing.endTotal();

  if (pProfileRes)
  {
    pProfileRes->setImportTime(OdInt64((timing.getTotalTime() - timing.getVectorizingTime() + pDgnDatabaseSource->getInitTime()) * 1000.));
    pProfileRes->setVectorizingTime(OdInt64(timing.getVectorizingTime() * 1000.));
#if !defined(__APPLE__)
    pProfileRes->setTvTime(OdInt64((internalTiming + externalTiming) * 1000.));
#endif
  }

  return tvModelId;
}

int OdTvVisualizeDgnFiler::getActiveViewId(OdGsDeviceForDgModel* pLayoutHelper) const
{
  if (!pLayoutHelper)
    return -1;

  OdGsViewPtr pActiveView = pLayoutHelper->activeView();

  int num = pLayoutHelper->numViews();
  int iActViewViewInd = 0;
  for (int i = 0; i < num; ++i)
  {
    OdGsView* pView = pLayoutHelper->viewAt(i);

    if (pView == pActiveView.get())
    {
      iActViewViewInd = i;
      break;
    }
  }

  return iActViewViewInd;
}

OdTvGsDeviceId OdTvVisualizeDgnFiler::getActiveTvDevice(OdTvDatabaseId& tvDbId, int idDevice) const
{
  OdTvDevicesIteratorPtr pDevicesIterator = tvDbId.openObject()->getDevicesIterator();
  unsigned iDeviceInd = 0;
  while (!pDevicesIterator.isNull() && !pDevicesIterator->done())
  {
    if (iDeviceInd == idDevice)
      return pDevicesIterator->getDevice();

    iDeviceInd++;
    pDevicesIterator->step();
  }

  return OdTvGsDeviceId();
}

OdTvGsViewId OdTvVisualizeDgnFiler::getActiveTvView(OdTvGsDeviceId& tvDeviceId, int iActViewViewInd) const
{
  OdTvGsDevicePtr pTvDevice = tvDeviceId.openObject();
  if (!pTvDevice.isNull())
  {
    return pTvDevice->viewAt(iActViewViewInd);
  }
  return OdTvGsViewId();
}

void OdTvVisualizeDgnFiler::getChoosedViews(OdDgViewGroupPtr pViewGroup, OdTvFilerFeedbackForChooseObject& filerFeedbackForChoose, bool& bCanceled) const
{
  OdTvFilerFeedbackItemForChooseArray* pFilerFeedbackForChooseArray = filerFeedbackForChoose.getFilerFeedbackItemForChooseArrayPtr();

  OdDgElementIteratorPtr pIt = pViewGroup->createIterator();
  for (; !pIt->done(); pIt->step())
  {
    OdDgViewPtr pCurView = OdDgView::cast(pIt->item().openObject(OdDg::kForRead));
    if (pCurView->getVisibleFlag())
    {
      OdString strIndex;
      strIndex.format(OD_T("%d"), pCurView->getIndex());

      OdTvFilerFeedbackItemForChoose filerFeedbackForChoose(strIndex);
      pFilerFeedbackForChooseArray->append(filerFeedbackForChoose);
    }
  }

  if (pFilerFeedbackForChooseArray->size() > 0)
    pFilerFeedbackForChooseArray->at(0).m_bChosen = true;

  if (m_properties->getFeedbackForChooseCallback() != NULL)
  {
    ((OdTvFeedbackForChooseCallback)m_properties->getFeedbackForChooseCallback())(filerFeedbackForChoose);
    if (filerFeedbackForChoose.getFilerFeedbackItemForChooseArrayPtr()->length() == 0)
      bCanceled = true;
  }
}

void OdTvVisualizeDgnFiler::createCommonDataAccessTree(OdTvDatabasePtr pTvDb, OdDbBaseDatabase *pDatabase, const OdString& strTreeName) const
{
  ::odrxDynamicLinker()->loadModule(L"DgProperties");

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
  OdTvCDATreeStorageId cdaTreeId = pTvDb->addCDATreeStorage(strTreeName,pTree, &rc);
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
    {
      pModel->setCDATreeStorage(cdaTreeId);
      modelsMap.insert(std::pair<OdString, OdTvModelId>(pModel->getName(), modelsIterPtr->getModel()));
    }
    modelsIterPtr->step();
  }

  // add models id to nodes
  OdTvCDATreeNodePtr pTvNode = pTree->getDatabaseNode();
  if (!pTvNode.isNull())
  {
    const OdRxModelTreeBaseNodePtrArray nodes = pTvNode->getChildren();
    for (OdRxModelTreeBaseNodePtrArray::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
      OdTvCDATreeNodePtr pNode = *it;
      if (pNode.isNull())
        continue;

      OdString nodeName = pNode->getNodeName();

      // add model id to node
      std::map<OdString, OdTvModelId>::const_iterator modelIt = modelsMap.find(nodeName);
      if (modelIt != modelsMap.end())
        pNode->setTvModelId(modelIt->second);

    }
  }
}

//***************************************************************************//
// 'OdTvVisualizeDgnFilerModule' methods implementation
//***************************************************************************//

ODRX_DEFINE_DYNAMIC_MODULE(OdTvVisualizeDgnFilerModule);

void OdTvVisualizeDgnFilerModule::initApp()
{
  // initialize the Visualize
  odTvInitialize();
}

void OdTvVisualizeDgnFilerModule::uninitApp()
{
  // Uninitialize the Visualize
  odTvUninitialize();
}

OdTvVisualizeFilerPtr OdTvVisualizeDgnFilerModule::getVisualizeFiler() const
{
  OdTvVisualizeFilerPtr pAcisFiler = new OdTvVisualizeDgnFiler();

  return pAcisFiler;
}

