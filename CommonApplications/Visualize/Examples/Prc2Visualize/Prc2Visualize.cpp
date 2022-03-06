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
#include "RxInit.h"

#include "HatchPatternManager.h"

#include "TvFactory.h"
#include "TvFilerTimer.h"
#include "Prc2Visualize.h"
#include "TvModuleNames.h"
#include "TvDatabaseCleaner.h"
#include "TvDatabaseUtils.h"

#include "ColorMapping.h"
#include "GiGs/PrcGiContext.h"
#ifdef U3D_MODULE_ENABLED
#include "U3D2PrcImport.h"
#endif

//*************************************************************************************//
// Implementation of the methods of the inheritants of 'OdTvVisualizePrcFilerDbSource'
//*************************************************************************************//

class OdTvBaseVisualizePrcFilerSource : public OdTvVisualizePrcFilerDbSource
{
protected:
  OdTvResult*  m_RC;
public:
  OdTvBaseVisualizePrcFilerSource(OdTvResult*  rc)
    :m_RC(rc)
  {

  }
  virtual OdTvResult* getResult()
  {
    return m_RC;
  }
  virtual OdPrcFilePtr getDb() = 0;
};


class OdTvVisualizePrcFilerSourceFromDb : public OdTvBaseVisualizePrcFilerSource
{
  OdDbBaseDatabase *m_Database;
public:
  OdTvVisualizePrcFilerSourceFromDb(OdDbBaseDatabase *pDatabase, OdTvResult*  rc) 
    :OdTvBaseVisualizePrcFilerSource(rc)
    ,m_Database(pDatabase) 
  {
  };
  virtual OdPrcFilePtr   getDb() { return m_Database; };
  virtual bool              odWasInitialized() const { return false; }
  virtual OdString          getFilename()
  {
    OdPrcFilePtr pDb = m_Database;
    if (!pDb.isNull())
    {
      OdString fileName = pDb->getFilename();
      if (!fileName.isEmpty())
        return fileName;
    }

    return OD_T("NoNamePrcDatabase");
  }
};

class OdTvBaseVisualizePrcU3DFilerSource : public OdTvBaseVisualizePrcFilerSource
{

protected:
  OdStaticRxObject<OdTvPrc2VisService> m_SVCS;
  double                               m_initTime;
public:
  OdTvBaseVisualizePrcU3DFilerSource(OdTvResult* rc)
    :OdTvBaseVisualizePrcFilerSource(rc)
  {

  }
  virtual OdPrcFilePtr getDb() = 0;
  virtual double getInitTime() const
  {
    return m_initTime;
  }
  void initialize(OdTvFilerTimeProfiling* pProfileRes)
  {
    OdTvFilerTimer timing(needTimer(pProfileRes));
    timing.startTotal();

    //load module
    ::odrxDynamicLinker()->loadApp(OdPrcModuleName, false);

    timing.endTotal();
    m_initTime = timing.getTotalTime();
  };
  bool isU3D(const OdString& file_path)
  {
    OdString strExt = file_path.mid(file_path.reverseFind('.') + 1);
    strExt.makeUpper();
    if (strExt.isEmpty() || strExt != OD_T("U3D"))
      return false;
    return true;
  }
  OdPrcFilePtr importFromU3D(const OdString& file_path)
  {
#ifdef U3D_MODULE_ENABLED
    OdPrcFilePtr pFile = m_SVCS.createDatabase();
    OdU3D2PrcImportModulePtr pModule = ::odrxDynamicLinker()->loadModule(OdU3D2PrcImportModuleName, false);
    if (!pModule.isNull())
    {
      OdU3D2PrcImportPtr importer = pModule->create();
      if (!importer.isNull())
      {
        importer->properties()->putAt(L"Database", pFile);
        importer->properties()->putAt(L"U3DPath", OdRxVariantValue(file_path));
        OdResult result = importer->import();
        if (m_RC)
        {
          if (::eLoadFailed == result)
            *m_RC = tvErrorDuringOpenFile;
        }
      }
      else
      {
        if (m_RC)
        {
          *m_RC = tvInternal;
        }
      }
    }
    else
    {
      if (m_RC)
      {
        *m_RC = tvMissingFilerModule;
      }
    }
    return pFile;
#else
    if (m_RC)
    {
      *m_RC = tvMissingFilerModule;
    }
    return OdPrcFilePtr();
#endif
  }
};

class OdTvVisualizePrcFilerSourceFromStream : public OdTvBaseVisualizePrcU3DFilerSource
{
  OdStreamBufPtr m_StreamBuf;

public:
  OdTvVisualizePrcFilerSourceFromStream(OdStreamBufPtr pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc)
  :OdTvBaseVisualizePrcU3DFilerSource(rc)
  , m_StreamBuf(pBuffer)
  {
    initialize(pProfileRes); 
  };
  virtual OdPrcFilePtr getDb() 
  { 
    OdString strFileName = m_StreamBuf->fileName();
    if(strFileName.isEmpty() || !isU3D(strFileName))
      return m_SVCS.readFile(m_StreamBuf); 
    return importFromU3D(strFileName);
  };
  virtual OdString getFilename()
  {
    OdString strFileName = m_StreamBuf->fileName();
    if (strFileName.isEmpty())
      return OD_T("NoNamePrcDatabase");

    //generate name for the stream file
    return OdTvDatabaseUtils::getFileNameFromPath(strFileName);
  };
};


class OdTvVisualizePrcFilerSourceFromFile : public OdTvBaseVisualizePrcU3DFilerSource
{
  OdString m_FilePath;

public:
  OdTvVisualizePrcFilerSourceFromFile(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc)
  :OdTvBaseVisualizePrcU3DFilerSource(rc)
  ,m_FilePath(filePath)
  { 
    initialize(pProfileRes); 
  };
  virtual OdPrcFilePtr getDb() 
  { 
    if (isU3D(m_FilePath))
      return importFromU3D(m_FilePath);
    return m_SVCS.readFile(m_FilePath);
  };
  virtual OdString        getFilename()
  {
    //generate name for the stream file
    return OdTvDatabaseUtils::getFileNameFromPath(m_FilePath);
  };
};

using namespace PRC2Visualize;
//***************************************************************************//
// 'OdTvVisualizePrcFilerProperties' methods implementation
//***************************************************************************//

OdTvVisualizePrcFilerProperties::OdTvVisualizePrcFilerProperties() : m_flags(kClearEmptyObjects|kRearrangeObjects), m_pPalette(0), m_dFACETRES(1.)
{
  m_importRect.xmax = 0;
  m_importRect.xmin = 0;
  m_importRect.ymax = 0;
  m_importRect.ymin = 0;
}

OdRxDictionaryPtr OdTvVisualizePrcFilerProperties::createObject()
{
  return OdRxObjectImpl<OdTvVisualizePrcFilerProperties, OdRxDictionary>::createObject();
}

void OdTvVisualizePrcFilerProperties::setPalette(OdIntPtr palette)
{
  const ODCOLORREF* pPalette = (const ODCOLORREF*)(palette);

  m_pPalette = pPalette;
}

OdIntPtr OdTvVisualizePrcFilerProperties::getPalette() const
{
  return (OdIntPtr)(m_pPalette);
}

OdTvVisualizePrcFilerProperties::~OdTvVisualizePrcFilerProperties()
{
}

namespace PRC2Visualize {
  ODRX_DECLARE_PROPERTY(Palette)
    ODRX_DECLARE_PROPERTY(DCRect)
    ODRX_DECLARE_PROPERTY(ObjectNaming)
    ODRX_DECLARE_PROPERTY(StoreSourceObjects)
    ODRX_DECLARE_PROPERTY(ClearEmptyObjects)
    ODRX_DECLARE_PROPERTY(RearrangeObjects)
    ODRX_DECLARE_PROPERTY(ImportBrepAsBrep)
    ODRX_DECLARE_PROPERTY(BrepFacetRes)
    ODRX_DECLARE_PROPERTY(AppendTransform)

    ODRX_BEGIN_DYNAMIC_PROPERTY_MAP(OdTvVisualizePrcFilerProperties);
    ODRX_GENERATE_PROPERTY(Palette)
    ODRX_GENERATE_PROPERTY(DCRect)
    ODRX_GENERATE_PROPERTY(ObjectNaming)
    ODRX_GENERATE_PROPERTY(StoreSourceObjects)
    ODRX_GENERATE_PROPERTY(ClearEmptyObjects)
    ODRX_GENERATE_PROPERTY(RearrangeObjects)
    ODRX_GENERATE_PROPERTY(ImportBrepAsBrep)
    ODRX_GENERATE_PROPERTY(BrepFacetRes)
    ODRX_GENERATE_PROPERTY(AppendTransform)
    ODRX_END_DYNAMIC_PROPERTY_MAP(OdTvVisualizePrcFilerProperties);

  ODRX_DEFINE_PROPERTY_METHODS(Palette, OdTvVisualizePrcFilerProperties, getPalette, setPalette, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(DCRect, OdTvVisualizePrcFilerProperties, getDCRect, setDCRect, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(ObjectNaming, OdTvVisualizePrcFilerProperties, getObjectNaming, setObjectNaming, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(StoreSourceObjects, OdTvVisualizePrcFilerProperties, getStoreSourceObjects, setStoreSourceObjects, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(ClearEmptyObjects, OdTvVisualizePrcFilerProperties, getClearEmptyObjects, setClearEmptyObjects, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(RearrangeObjects, OdTvVisualizePrcFilerProperties, getRearrangeObjects, setRearrangeObjects, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(ImportBrepAsBrep, OdTvVisualizePrcFilerProperties, getImportBrepAsBrep, setImportBrepAsBrep, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(BrepFacetRes, OdTvVisualizePrcFilerProperties, getBrepFacetRes, setBrepFacetRes, getDouble);
  ODRX_DEFINE_PROPERTY_METHODS(AppendTransform, OdTvVisualizePrcFilerProperties, getAppendTransform, setAppendTransform, getIntPtr);
}

void OdTvVisualizePrcFilerProperties::setDCRect(OdIntPtr rect)
{
  OdTvDCRect* pRect = (OdTvDCRect*)(rect);
  if (!pRect)
  {
    ODA_ASSERT(false);
  }

  m_importRect = *pRect;
}

OdIntPtr OdTvVisualizePrcFilerProperties::getDCRect() const
{
  return (OdIntPtr)(&m_importRect);
}

void OdTvVisualizePrcFilerProperties::setBrepFacetRes(double dFacetRes)
{
  m_dFACETRES = dFacetRes;

  if (dFacetRes < 0.01)
    m_dFACETRES = 0.01;

  if (dFacetRes > 10.)
    m_dFACETRES = 10.;
}

double OdTvVisualizePrcFilerProperties::getBrepFacetRes() const
{
  return m_dFACETRES;
}

void OdTvVisualizePrcFilerProperties::setAppendTransform(OdIntPtr pTransform)
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

OdIntPtr OdTvVisualizePrcFilerProperties::getAppendTransform() const
{
  return (OdIntPtr)(&m_appendTransform);
}

//***************************************************************************//
// 'OdTvVisualizePrcFiler' methods implementation
//***************************************************************************//

OdTvVisualizePrcFiler::OdTvVisualizePrcFiler() : m_properties(OdTvVisualizePrcFilerProperties::createObject())
{
}

OdTvDatabaseId OdTvVisualizePrcFiler::loadFrom(OdDbBaseDatabase *pDatabase, OdTvFilerTimeProfiling* pProfileRes /*= NULL*/, OdTvResult* rc /*= NULL*/) const
{
  OdTvVisualizePrcFilerSourceFromDb dl(pDatabase, rc);
  return loadFrom(&dl, pProfileRes, rc);
}

OdTvDatabaseId OdTvVisualizePrcFiler::loadFrom(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes /*= NULL*/, OdTvResult* rc /*= NULL*/) const
{
  OdTvVisualizePrcFilerSourceFromStream dl(pBuffer, pProfileRes, rc);
  return loadFrom(&dl, pProfileRes, rc);
}

OdTvDatabaseId OdTvVisualizePrcFiler::loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizePrcFilerSourceFromFile dl(filePath, pProfileRes, rc);
  return loadFrom(&dl, pProfileRes, rc);
}

OdTvDatabaseId OdTvVisualizePrcFiler::generate(OdTvFilerTimeProfiling* pProfileRes) const
{
  OdTvDatabaseId tvDbId;

  // does nothing
  return tvDbId;
}

OdTvModelId OdTvVisualizePrcFiler::appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase *pDatabase, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizePrcFilerSourceFromDb dl(pDatabase, rc);
  return appendFrom(databaseId, &dl, pProfileRes, rc);
}

OdTvModelId OdTvVisualizePrcFiler::appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizePrcFilerSourceFromStream dl(pBuffer, pProfileRes, rc);
  return appendFrom(databaseId, &dl, pProfileRes, rc);
}

OdTvModelId OdTvVisualizePrcFiler::appendFrom(const OdTvDatabaseId& databaseId, const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizePrcFilerSourceFromFile dl(filePath, pProfileRes, rc);
  return appendFrom(databaseId, &dl, pProfileRes, rc);
}

OdTv::Units getPrcUnit(OdPrcFilePtr& pDb, double& addUnitCoefToMeters)
{
  addUnitCoefToMeters = 1.0;

  OdPrcUnit prc_unit = pDb->unit();
  if (prc_unit.unitFromCADFile())
  {
    const double prc_unit_val = prc_unit.unit();
    if (OdEqual(prc_unit_val, 1.0))
    {
      return OdTv::kMillimeters;
    }

    if (OdEqual(prc_unit_val, 10.0))
    {
      return OdTv::kCentimeters;
    }

    if (OdEqual(prc_unit_val, 1000.0))
    {
      return OdTv::kMeters;
    }

    if (OdEqual(prc_unit_val, 0.001))
    {
      return OdTv::kMicrometers;
    }

    if (OdEqual(prc_unit_val, 1000000.0))
    {
      return OdTv::kKilometers;
    }

    if (OdEqual(prc_unit_val, 25.40))
    {
      return OdTv::kInches;
    }

    if (OdEqual(prc_unit_val, 12.0 * 25.40))
    {
      return OdTv::kFeet;
    }

    if (OdEqual(prc_unit_val, 25.40 / 1000.0))
    {
      return OdTv::kMils;
    }

    if (OdEqual(prc_unit_val, 25.40 / 1000000.0))
    {
      return OdTv::kMicroInches;
    }

    if (OdEqual(prc_unit_val, 914.4))
    {
      return OdTv::kYards;
    }

    if (OdEqual(prc_unit_val, 1760.0 * 914.4))
    {
      return OdTv::kMiles;
    }

    addUnitCoefToMeters = prc_unit_val * 1000.0;
    return OdTv::kUserDefined;
  }

  return OdTv::kMillimeters;
}

OdTvDatabaseId OdTvVisualizePrcFiler::loadFrom(OdTvVisualizePrcFilerDbSource *pPrcDatabaseSource, OdTvFilerTimeProfiling* pProfileRes /*= NULL*/, OdTvResult* rc /*= NULL*/) const
{
  OdTvDatabaseId tvDbId;

  if (rc)
    *rc = tvOk;

  //check that time profiling is need
  bool bUseTimeProfiling = needTimer(pProfileRes);

  double internalTiming = 0.;
  double externalTiming = 0;

  //prepare timing object
  OdTvFilerTimer timing(bUseTimeProfiling);
  timing.startTotal();

  //store visualize device module name
  OdString moduleName;
  try
  {
    OdPrcFilePtr pDb = pPrcDatabaseSource->getDb();

    timing.startVectorizing();

    if (!pDb.isNull())
    {

      OdGiContextForPrcDatabasePtr pPrcContext = OdGiContextForPrcDatabase::createObject();
      pPrcContext->enableGsModel(true);
      pPrcContext->setDatabase(pDb);

      double addUnitCoefToMeters(1.0);
      OdTv::Units tvUnits = getPrcUnit(pDb, addUnitCoefToMeters);

      OdGsModulePtr pGs = ::odrxDynamicLinker()->loadModule(OdTvVisualizeDeviceModuleName, false);
      if (pGs.isNull())
      {
        if (rc)
          *rc = tvMissingVisualizeDeviceModule;
        return tvDbId;
      }
      OdGsDevicePtr pDevice = pGs->createDevice();
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

        if (pProperties->has(OD_T("WriteUserData")))
          pProperties->putAt(OD_T("WriteUserData"), OdRxVariantValue(m_properties->getStoreSourceObjects()));
        if (pProperties->has(OD_T("GenerateEntityNames")))
          pProperties->putAt(OD_T("GenerateEntityNames"), OdRxVariantValue(m_properties->getObjectNaming()));
        if (pProperties->has(OD_T("CompareUnnamedImages")))
          pProperties->putAt(OD_T("CompareUnnamedImages"), OdRxVariantValue(true));
        
        //Write font file path as user data
        if( pProperties->has( OD_T("WriteFontFilePath") ))
          pProperties->putAt( OD_T("WriteFontFilePath"), OdRxVariantValue( true ) );

        //setup support direct draw of the breps
        bool bImportBrepAsBrep = m_properties->getImportBrepAsBrep();
        if (bImportBrepAsBrep)
        {
          if (pProperties->has(OD_T("SuppoprtBrepDraw")))
            pProperties->putAt(OD_T("SuppoprtBrepDraw"), OdRxVariantValue(true));

          if (pProperties->has(OD_T("FullRegenDependentVectorization")))
            pProperties->putAt(OD_T("FullRegenDependentVectorization"), OdRxVariantValue(false));

          if (pProperties->has(OD_T("FacetResForBrep")))
            pProperties->putAt(OD_T("FacetResForBrep"), OdRxVariantValue(m_properties->getBrepFacetRes()));
        }
      }

      OdGsPrcLayoutHelperPtr pLayoutHelper = OdPrcGsManager::setupActiveLayoutViews(pDevice.get(), pPrcContext);
      pLayoutHelper->activeView()->setMode(OdGsView::kGouraudShaded);

      //set the palette
      const ODCOLORREF* palette = (const ODCOLORREF*)m_properties->getPalette();
      bool bDefaultPalette = false;
      if (palette == 0)
      {
        bDefaultPalette = true;
        palette = odcmAcadPalette(ODRGB(255, 255, 255));
      }

      OdArray<ODCOLORREF, OdMemoryAllocator<ODCOLORREF> > pPalCpy;
      pPalCpy.insert(pPalCpy.begin(), palette, palette + 256);
      pDevice->setLogicalPalette(pPalCpy.asArrayPtr(), 256);

      pDevice->setBackgroundColor(ODRGB(64, 64, 64));
      pPrcContext->setPaletteBackground(ODRGB(64, 64, 64));

      //call onsize
      OdTvDCRect* pRect = (OdTvDCRect*)m_properties->getDCRect();
      if (pRect && (pRect->xmax > 0 || pRect->xmin > 0 || pRect->ymax > 0 || pRect->ymin > 0))
      {
        OdGsDCRect  gsRect(pRect->xmin, pRect->xmax, pRect->ymin, pRect->ymax);
        pDevice->onSize(gsRect);
      }

      pDb->applyCurrentView();

      pLayoutHelper->update();

      if (pProperties->has(OD_T("TvDatabaseID")))
        tvDbId = *(OdTvDatabaseId*)OdRxVariantValue(pProperties->getAt(OD_T("TvDatabaseID")).get())->getIntPtr();
      if (bUseTimeProfiling)
      {
#if !defined(__APPLE__)
        if (pProperties->has(OD_T("TvElapsedTime")))
        {
          internalTiming = OdRxVariantValue(pProperties->getAt(OD_T("TvElapsedTime")).get())->getDouble();
        }
#endif
      }

      moduleName = pGs->moduleName();

      //setup active view
      timing.startMisc();

      if (tvDbId.isValid())
      {
        int iActViewViewInd = getActiveViewId(pLayoutHelper.get());

        //get active tv View
        OdTvGsViewId tvViewId = getActiveTvView(tvDbId, iActViewViewInd);
        if (!tvViewId.isNull())
        {
          OdTvGsViewPtr pActiveTvView = tvViewId.openObject(OdTv::kForWrite);
          if (!pActiveTvView.isNull())
          {
            pActiveTvView->setActive(true);
            pActiveTvView->setName(OD_TV_COMMON_VIEW_NAME);
            OdTvDatabasePtr pDb = tvDbId.openObject(OdTv::kForWrite);
            pDb->getDevicesIterator()->getDevice().openObject(OdTv::kForWrite)->setName(OD_TV_COMMON_DEVICE_NAME);

            //set gradient background to the active view
            OdTvGsViewBackgroundId bkgId = pDb->createBackground(OD_T("PRC2VISUALIZE"), OdTvGsViewBackgroundId::kGradient);
            if (!bkgId.isNull())
            {
              {
                OdTvGsViewGradientBackgroundPtr pGradientBackground = bkgId.openAsGradientBackground(OdTv::kForWrite);

                pGradientBackground->setColorTop(OdTvColorDef(33, 108, 170));
                pGradientBackground->setColorMiddle(OdTvColorDef(109, 158, 200));
                pGradientBackground->setColorBottom(OdTvColorDef(184, 208, 230));
                pGradientBackground->setHeight(0.33);
                pGradientBackground->setHorizon(0.5);
              }

              pActiveTvView->setBackground(bkgId);
              pActiveTvView->setDefaultLightingIntensity(1.);
              pActiveTvView->setAmbientLightColor(OdTvColorDef(50, 50, 50));
            }
          }
        }

        // save filename to database user data
        OdTvDatabaseUtils::writeFileNameToTvDatabase(tvDbId, pPrcDatabaseSource->getFilename());

        //rename the model (here we suppose that database contain only one model)
        OdTvModelsIteratorPtr pModelsIterator = tvDbId.openObject()->getModelsIterator();
        if (!pModelsIterator.isNull() && !pModelsIterator->done())
        {
          OdTvModelId modelId = pModelsIterator->getModel();
          OdTvModelPtr pModel = modelId.openObject(OdTv::kForWrite);
          if (!pModel.isNull())
          {
            pModel->setName(pPrcDatabaseSource->getFilename());
            pModel->setUnits(tvUnits, tvUnits == OdTv::kUserDefined ? addUnitCoefToMeters : 1.);

            if (m_properties->getRearrangeObjects())
            {
              //collect entities before exploding (array is not a best solution but here we suppose that we have only one entity)
              OdArray<OdTvEntityId> entitiesForExplode;
              OdTvEntitiesIteratorPtr pEntitiesIterator = pModel->getEntitiesIterator();
              while (!pEntitiesIterator->done())
              {
                OdTvEntityId entityId = pEntitiesIterator->getEntity();
                if (entityId.getType() == OdTvEntityId::kEntity)
                {
                  entitiesForExplode.append(pEntitiesIterator->getEntity());
                }
                pEntitiesIterator->step();
              }

              // Explode one level of sub entities
              for (unsigned i = 0; i < entitiesForExplode.size(); i++)
              {
                OdTvEntityPtr pEntity = entitiesForExplode[i].openObject(OdTv::kForWrite);
                pEntity->explodeSubEntities();
                if (pEntity->isEmpty())
                {
                  pEntity.release();
                  pModel->removeEntity(entitiesForExplode[i]);
                }
              }
            }
          }
        }
      }

      if (tvDbId.isValid() && m_properties->getClearEmptyObjects())
        OdTvDatabaseCleaner::cleanTvDatabase(tvDbId);

      timing.endMisc();
      externalTiming += timing.getMiscTime();

      timing.endVectorizing();
    }
    else
    {
      if (rc && (tvOk == *rc))
        *rc = tvFilerEmptyInternalDatabase;
    }
  }
  catch (...)
  {
    if (rc)
      *rc = tvInternal;

    timing.endVectorizing();
  }

  //unload Prc modules (try to emulate the OdUninitialized for PRC)
  //here we will unload all including Visualize device
  if (!moduleName.isEmpty())
    odrxDynamicLinker()->unloadUnreferenced();

  timing.endTotal();

  if (pProfileRes)
  {
    pProfileRes->setImportTime(OdInt64((timing.getTotalTime() - timing.getVectorizingTime() + pPrcDatabaseSource->getInitTime()) * 1000.));
    pProfileRes->setVectorizingTime(OdInt64((timing.getVectorizingTime()) * 1000.));
#if !defined(__APPLE__)
    pProfileRes->setTvTime(OdInt64((internalTiming + externalTiming) * 1000.));
#endif
  }

  return tvDbId;
}


OdTvModelId OdTvVisualizePrcFiler::appendFrom(const OdTvDatabaseId& databaseId, OdTvVisualizePrcFilerDbSource *pPrcDatabaseSource, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvModelId tvModelId;

  if (rc)
    *rc = tvOk;

  //check that we are in the real append mode
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
  else
  {
    background = ODRGB(171, 200, 232);
    OdTvDCRect* pRect = (OdTvDCRect*)m_properties->getDCRect();
    if (pRect)
      rect = *pRect;

    //set the palette
    const ODCOLORREF* palette = (const ODCOLORREF*)m_properties->getPalette();
    bool bDefaultPalette = false;
    if (palette == 0)
    {
      bDefaultPalette = true;
      palette = odcmAcadPalette(ODRGB(255, 255, 255));
    }

    pPalCpy.insert(pPalCpy.begin(), palette, palette + 256);
  }

  //collcet current models and blocks
  std::set<OdTvGsViewId> foreignViews;
  std::set<OdTvModelId> foreignModels;
  std::set<OdTvBlockId> foreignBlocks;
  OdTvDatabaseUtils::collectViewsModelsAndBlocks(databaseId, foreignViews, foreignModels, foreignBlocks);

  //check that time profiling is need
  bool bUseTimeProfiling = needTimer(pProfileRes);
  double internalTiming = 0.;
  double externalTiming = 0;

  //prepare timing object
  OdTvFilerTimer timing(bUseTimeProfiling);
  timing.startTotal();

  OdString moduleName;
  try
  {
    OdPrcFilePtr pDb = pPrcDatabaseSource->getDb();

    timing.startVectorizing();

    if (!pDb.isNull())
    {
      OdGiContextForPrcDatabasePtr pPrcContext = OdGiContextForPrcDatabase::createObject();
      pPrcContext->enableGsModel(true);
      pPrcContext->setDatabase(pDb);

      double addUnitCoefToMeters(1.0);
      OdTv::Units tvUnits = getPrcUnit(pDb, addUnitCoefToMeters);

      OdGsModulePtr pGs = ::odrxDynamicLinker()->loadModule(OdTvVisualizeDeviceModuleName, false);
      if (pGs.isNull())
      {
        if (rc)
          *rc = tvMissingVisualizeDeviceModule;
        return tvModelId;
      }

      // Generate model name
      OdString modelName = OdTvDatabaseUtils::generateModelName(databaseId, pPrcDatabaseSource->getFilename());

      OdGsDevicePtr pDevice = pGs->createDevice();
      OdRxDictionaryPtr pProperties = pDevice->properties();

      if (pProperties.get())
      {
        if (pProperties->has(OD_T("TvDatabaseID")))
          pProperties->putAt(OD_T("TvDatabaseID"), OdRxVariantValue((OdIntPtr)(&databaseId)));

        if (pProperties->has(OD_T("DisplayViaGLES2")))
          pProperties->putAt(OD_T("DisplayViaGLES2"), OdRxVariantValue(false));
        if (pProperties->has(OD_T("AllowNonPersistentObjects")))
          pProperties->putAt(OD_T("AllowNonPersistentObjects"), OdRxVariantValue(false));
#if !defined(__APPLE__)
        if (pProperties->has(OD_T("EnableTiming")))
          pProperties->putAt(OD_T("EnableTiming"), OdRxVariantValue(bUseTimeProfiling));
#endif

        if (pProperties->has(OD_T("WriteUserData")))
          pProperties->putAt(OD_T("WriteUserData"), OdRxVariantValue(m_properties->getStoreSourceObjects()));
        if (pProperties->has(OD_T("GenerateEntityNames")))
          pProperties->putAt(OD_T("GenerateEntityNames"), OdRxVariantValue(m_properties->getObjectNaming()));
        if (pProperties->has(OD_T("CompareUnnamedImages")))
          pProperties->putAt(OD_T("CompareUnnamedImages"), OdRxVariantValue(true));

        if (pProperties->has(OD_T("ModelName")))
          pProperties->putAt(OD_T("ModelName"), OdRxVariantValue(modelName));

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
        if (pProperties->has(OD_T("WriteFontFilePath")))
          pProperties->putAt(OD_T("WriteFontFilePath"), OdRxVariantValue(true));

        //setup support direct draw of the breps
        bool bImportBrepAsBrep = m_properties->getImportBrepAsBrep();
        if (bImportBrepAsBrep)
        {
          if (pProperties->has(OD_T("SuppoprtBrepDraw")))
            pProperties->putAt(OD_T("SuppoprtBrepDraw"), OdRxVariantValue(true));

          if (pProperties->has(OD_T("FullRegenDependentVectorization")))
            pProperties->putAt(OD_T("FullRegenDependentVectorization"), OdRxVariantValue(false));

          if (pProperties->has(OD_T("FacetResForBrep")))
            pProperties->putAt(OD_T("FacetResForBrep"), OdRxVariantValue(m_properties->getBrepFacetRes()));
        }

        //we don't need to setup extents inside appendFrom since we can have additional units transform matrix here
        if (pProperties->has(OD_T("DisableSetingExtents")))
          pProperties->putAt(OD_T("DisableSetingExtents"), OdRxVariantValue(true));
      }

      OdGsPrcLayoutHelperPtr pLayoutHelper = OdPrcGsManager::setupActiveLayoutViews(pDevice.get(), pPrcContext);
      pLayoutHelper->activeView()->setMode(OdGsView::kGouraudShaded);

      //setup palette, background and device size
      //a.palette
      pDevice->setLogicalPalette(pPalCpy.asArrayPtr(), 256);

      //b. background
      pDevice->setBackgroundColor(background);
      pPrcContext->setPaletteBackground(background);

      //c. call onsize
      if (rect.xmax > 0 || rect.xmin > 0 || rect.ymax > 0 || rect.ymin > 0)
      {
        OdGsDCRect  gsRect(rect.xmin, rect.xmax, rect.ymin, rect.ymax);
        pDevice->onSize(gsRect);
      }

      pDb->applyCurrentView();

      pLayoutHelper->update();

      if (bUseTimeProfiling)
      {
#if !defined(__APPLE__)
        if (pProperties->has(OD_T("TvElapsedTime")))
        {
          internalTiming = OdRxVariantValue(pProperties->getAt(OD_T("TvElapsedTime")).get())->getDouble();
        }
#endif
      }

      moduleName = pGs->moduleName();

      //setup active view
      timing.startMisc();

      if (databaseId.isValid())
      {
        timing.startMisc();

        {
          OdTvDatabasePtr pTvDb = databaseId.openObject();
          tvModelId = pTvDb->findModel(modelName);
        }
        
        // rearrange entities if need
        if (m_properties->getRearrangeObjects())
        {
          OdTvModelPtr pModel = tvModelId.openObject(OdTv::kForWrite);
          if (!pModel.isNull())
          {
            //collect entities before exploding (array is not a best solution but here we suppose that we have only one entity)
            OdArray<OdTvEntityId> entitiesForExplode;
            OdTvEntitiesIteratorPtr pEntitiesIterator = pModel->getEntitiesIterator();
            while (!pEntitiesIterator->done())
            {
              OdTvEntityId entityId = pEntitiesIterator->getEntity();
              if (entityId.getType() == OdTvEntityId::kEntity)
              {
                entitiesForExplode.append(pEntitiesIterator->getEntity());
              }
              pEntitiesIterator->step();
            }

            // Explode one level of sub entities
            for (unsigned i = 0; i < entitiesForExplode.size(); i++)
            {
              OdTvEntityPtr pEntity = entitiesForExplode[i].openObject(OdTv::kForWrite);
              pEntity->explodeSubEntities();
              if (pEntity->isEmpty())
              {
                pEntity.release();
                pModel->removeEntity(entitiesForExplode[i]);
              }
            }
          }
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
          OdTvModelPtr pModel = tvModelId.openObject(OdTv::kForWrite);
          if (!pModel.isNull())
          {
            //set units
            pModel->setUnits(tvUnits, tvUnits == OdTv::kUserDefined ? addUnitCoefToMeters : 1.);
          }
        }

        timing.endMisc();
        externalTiming = timing.getMiscTime();
      }

      timing.endVectorizing();

    }
    else
    {
      if (rc && (tvOk == *rc))
        *rc = tvFilerEmptyInternalDatabase;
    }

  }
  catch (...)
  {
    if (rc)
      *rc = tvInternal;

    timing.endVectorizing();
  }

  //unload Prc modules (try to emulate the OdUninitialized for PRC)
  //here we will unload all including Visualize device
  if (!moduleName.isEmpty())
    odrxDynamicLinker()->unloadUnreferenced();

  timing.endTotal();

  if (pProfileRes)
  {
    pProfileRes->setImportTime(OdInt64((timing.getTotalTime() - timing.getVectorizingTime() + pPrcDatabaseSource->getInitTime()) * 1000.));
    pProfileRes->setVectorizingTime(OdInt64((timing.getVectorizingTime()) * 1000.));
#if !defined(__APPLE__)
    pProfileRes->setTvTime(OdInt64((internalTiming + externalTiming) * 1000.));
#endif
  }

  return tvModelId;
}

int OdTvVisualizePrcFiler::getActiveViewId(OdGsPrcLayoutHelper* pLayoutHelper) const
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

OdTvGsViewId OdTvVisualizePrcFiler::getActiveTvView(OdTvDatabaseId& dbId, int iActViewViewInd) const
{
  OdTvDevicesIteratorPtr pDevicesIterator = dbId.openObject()->getDevicesIterator();
  if (!pDevicesIterator.isNull() && !pDevicesIterator->done())
  {
    OdTvGsDevicePtr pTvDevice = pDevicesIterator->getDevice().openObject();
    if (!pTvDevice.isNull())
    {
      return pTvDevice->viewAt(iActViewViewInd);
    }
  }

  return OdTvGsViewId();
}

//***************************************************************************//
// 'OdTvVisualizePrcFilerModule' methods implementation
//***************************************************************************//

ODRX_DEFINE_DYNAMIC_MODULE(OdTvVisualizePrcFilerModule);

void OdTvVisualizePrcFilerModule::initApp()
{
  // initialize the Visualize SDK
  odTvInitialize();
}

void OdTvVisualizePrcFilerModule::uninitApp()
{
  // Uninitialize the Visualize SDK
  odTvUninitialize();
}

OdTvVisualizeFilerPtr OdTvVisualizePrcFilerModule::getVisualizeFiler() const
{
  OdTvVisualizeFilerPtr pDwgFiler = new OdTvVisualizePrcFiler();

  return pDwgFiler;
}
