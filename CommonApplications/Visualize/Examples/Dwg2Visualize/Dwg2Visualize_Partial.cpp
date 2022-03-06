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

//ODA SDK
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

#include "TvFactory.h"
#include "TvModel.h"
#include "TvGeomCollector.h"
#include "TvFilerTimer.h"
#include "TvModuleNames.h"
#include "TvDatabaseCleaner.h"
#include "TvDatabaseUtils.h"

#include "Dwg2Visualize.h"

#include "ModelerGeometry/ModelerModule.h"
#include "Wr/wrTriangulationParams.h"

#include "DbObjectId.h"
#include "../Drawing/Include/DbObjectId.h"
#include "../Kernel/DevInclude/DbRoot/OdDbStub.h"
#include "DbAttributeDefinition.h"

#include "PartialImportNotifier.h"

#include "DbObjectContextCollection.h"
#include "DbObjectContextManager.h"

#ifndef ODA_UNIXOS
#define pathChar '\\'
#define oldPathChar '/'
#define separatorChar ';'
#else
#define pathChar '/'
#define oldPathChar '\\'
#define separatorChar ':'
#endif
//***************************************************************************//
using namespace DWG2Visualize;

class OdTvDbBlockTableRecordOverrule : public OdStaticRxObject< OdGiDrawableOverrule >
{
public:
  OdTvDbBlockTableRecordOverrule( bool bDraw, bool bUnload )
  {
    m_bDoDraw = bDraw;
    m_bUnloadObjects = bUnload;
    OdRxOverrule::setIsOverruling( true );
    OdRxOverrule::addOverrule( OdDbBlockTableRecord::desc(), this );
    m_pNotifier = NULL;
  }

  ~OdTvDbBlockTableRecordOverrule()
  {
    OdRxOverrule::removeOverrule( OdDbBlockTableRecord::desc(), this );
    OdRxOverrule::setIsOverruling( false );
    m_pNotifier = NULL;
  }

  void setNotifier( OdTvPartialImportNotifier* pNotifier )
  {
    m_pNotifier = pNotifier;
  }

  virtual bool isApplicable(const OdRxObject* /*pOverruledSubject*/) const { return true; }

  virtual bool worldDraw(const OdGiDrawable* pSubject, OdGiWorldDraw *pWd)
  {
    if( m_pNotifier )
    {
      if( m_pNotifier->abortImport() ) return true;
    }
    OdGiContext* pCtx = pWd->context();
    OdDbDatabase* pDb = OdDbDatabase::cast(pCtx->database()).get();
    OdDbBlockTableRecordPtr pBlock = OdDbBlockTableRecord::cast( pSubject );
    if( pBlock.isNull() ) return true;
    if (!pDb)
    {
      pDb = pBlock->database();
    }

    bool bDBRO = pBlock->isDBRO();
    OdDbStub* pBlockId = pBlock->objectId();
    bool bNoAutoLock = ( pBlockId && pBlockId->flags( kOdDbIdNoAutoLock ) != 0 );

    OdDbObjectIteratorPtr pIter = pBlock->newIterator( true, true, true );

    if( m_pNotifier )
    {
      OdDbObjectIteratorPtr pEntIter = pBlock->newIterator( true, true, true );
      OdUInt32 nCount = 0;
      for (;  !pEntIter->done(); pEntIter->step())
      {
        nCount++;
      }
      m_pNotifier->setBlockTableEntitiesCount( pBlock->id(), nCount );
    }

    OdDbStub* entId;

    OdRxClass* attDefDesc = OdDbAttributeDefinition::desc();

    OdGiGeometry& geom = pWd->geometry();

    for (;  !pIter->done() && !pWd->regenAbort(); pIter->step())
    {
      if( m_pNotifier )
      {
        if( m_pNotifier->abortImport() ) return true;
      }
      if(bNoAutoLock)
      {
        OdDbStub* id = pIter->objectId();
        if(id->flags(kOdDbIdRedirected)==kOdDbIdRedirected)
          id->getData(kOdDbIdMappingData, id);
        id->setFlags(kOdDbIdNoAutoLock, kOdDbIdNoAutoLock);
      }
      if(bDBRO) 
      {
        entId = pIter->objectId();
        if(entId->flags(kOdDbIdLoading)==kOdDbIdLoading)
          continue;
      }
      OdUInt32 flgs = entId->flags();
      if( entId->flags( kObjectLeftOnDisk ) != kObjectLeftOnDisk )
      {
        ODA_FAIL();
      }
      
      {
        OdDbEntityPtr ent = pIter->entity();
        if( ent.isNull() ) continue;
        if( m_bDoDraw )
        {
          if( !attDefDesc || !ent->isKindOf( attDefDesc ) )
          {
            geom.draw( ent );
          }
        }
      }

      if( m_bUnloadObjects )
      {
        pDb->enqueuePaging( entId );
        pDb->pageObjects();
      }

      if( entId->flags( kObjectLeftOnDisk ) != kObjectLeftOnDisk )
      {
        ODA_FAIL();
      }      
    }
    return true;
  }
protected:
  bool m_bUnloadObjects;
  bool m_bDoDraw;
  OdTvPartialImportNotifier* m_pNotifier;
};

//partial import notifier impl
void OdTvPartialImportNotifier::entityVectorizationDone( const OdTvEntityId& entityId )
{
  if( entityId.isNull() ) return;
  if( m_bAddPartialIndex )
  {
    if( m_parents.empty() )
    {
      ODA_FAIL();
      return;
    }
    if( !m_parents.top()->m_bIsBlock )
    {
      OdTvModelPtr pModel = m_parents.top()->m_model.openObject( OdTv::kForWrite );
      pModel->extendPartialViewIndex( entityId );
    }
    else
    {
      OdTvBlockPtr pBlock = m_parents.top()->m_block.openObject( OdTv::kForWrite );
      pBlock->extendPartialViewIndex( entityId );
    }
  }
  if( m_pLimitManager )
  {
    m_entitiesToUnload.push_back( entityId );
    if( m_pLimitManager->checkMemoryUsage( OdTvLimitManager::kReasonUnloadObject ) == OdTvLimitManager::kNotPassed )
    {
      unloadCachedEntities();
    }
  }
  else
  {
    //remove empty data
    if (m_bClearEmptySubEntities && entityId.getType() == OdTvEntityId::kEntity)
    {
      OdTvEntityPtr pEntity = entityId.openObject(OdTv::kForWrite);
      OdTvDatabaseCleaner::clearGeometryLevel(pEntity);
    }

    m_pDatabase->writeObjectPartial( entityId );
  }
  m_nCurrentObject++;
  if( m_pMeter )
  {
    m_pMeter->meterProgress();
  }
}

void OdTvPartialImportNotifier::insertVectorizationDone( const OdTvEntityId& insertId )
{
  if( m_bAddPartialIndex )
  {
    if( m_parents.empty() )
    {
      ODA_FAIL();
      return;
    }
    if( !m_parents.top()->m_bIsBlock )
    {
      OdTvModelPtr pModel = m_parents.top()->m_model.openObject( OdTv::kForWrite );
      pModel->extendPartialViewIndex( insertId );
    }
    else
    {
      OdTvBlockPtr pBlock = m_parents.top()->m_block.openObject( OdTv::kForWrite );
      pBlock->extendPartialViewIndex( insertId );
    }
  }
  if( m_pLimitManager )
  {
    m_entitiesToUnload.push_back( insertId );
    if( m_pLimitManager->checkMemoryUsage( OdTvLimitManager::kReasonUnloadObject ) == OdTvLimitManager::kPassed )
    {
      unloadCachedEntities();
    }
  }
  else
  {
    m_pDatabase->writeObjectPartial( insertId );
  }
  m_nCurrentObject++;
  if( m_pMeter )
  {
    m_pMeter->meterProgress();
  }
}

void OdTvPartialImportNotifier::blockCreated( const OdTvBlockId& blockId )
{
  if( !m_bAddPartialIndex ) return;
  if( blockId.isNull() ) return;
  OdTvBlockPtr pBlock = blockId.openObject( OdTv::kForWrite );
  pBlock->addPartialViewIndex( false );
}

void OdTvPartialImportNotifier::blockVectorizationBegin( const OdTvBlockId& blockId )
{
  if( !m_bAddPartialIndex ) return;
  if( blockId.isNull() || m_parents.empty() ) return;
  OdTvModelId modelId = m_parents.top()->m_model;
  ParentDescr* descr = m_parents.push();
  descr->m_model = modelId;
  descr->m_block = blockId;
  descr->m_bIsBlock = true;
}

void OdTvPartialImportNotifier::blockVectorizationDone( const OdTvBlockId& blockId )
{
  if( !m_bAddPartialIndex ) return;
  if( blockId.isNull() || m_parents.empty() ) return;
  ODA_ASSERT( m_parents.top()->m_block == blockId );
  m_parents.pop();
}

void OdTvPartialImportNotifier::modelCreated( const OdTvModelId& modelId )
{
  if( !m_bAddPartialIndex ) return;
  if( modelId.isNull() ) return;
  OdTvModelPtr pModel = modelId.openObject( OdTv::kForWrite );
  pModel->addPartialViewIndex( false );
}

void OdTvPartialImportNotifier::modelActivated( const OdTvModelId& modelId )
{
  if( !m_bAddPartialIndex ) return;
  if( modelId.isNull() ) return;
  if( m_parents.empty() || m_parents.top()->m_model != modelId )
  {
    if( !m_parents.empty() )
    {
      ODA_ASSERT( !m_parents.top()->m_bIsBlock );
    }
    while( !m_parents.empty() )
    {
      m_parents.pop();
    }
    ParentDescr* descr = m_parents.push();
    descr->m_model = modelId;
  }
}

OdTvPartialImportNotifier::OdTvPartialImportNotifier( OdTvDatabasePtr pDb, bool bAddPartialIndex, bool clearEmptySubEntities )
{
  m_pDatabase = pDb;
  m_bAddPartialIndex = bAddPartialIndex;
  m_pLimitManager = NULL;
  m_nEntitiesEstimation = 0;
  m_nCurrentObject = 0;
  m_pMeter = NULL;
  m_bClearEmptySubEntities = clearEmptySubEntities;
  m_pAbort = NULL;
}

OdTvPartialImportNotifier::~OdTvPartialImportNotifier()
{
  while( !m_parents.empty() )
  {
    m_parents.pop();
  }
}

void OdTvPartialImportNotifier::clearProcessedMaps()
{
  m_processedBlocks.clear();
}

void OdTvPartialImportNotifier::setBlockTableEntitiesCount( OdDbStub* id, OdUInt32 nCount )
{
  if( m_processedBlocks.find( id ) != m_processedBlocks.end() || nCount == 0 )
  {
    return;
  }
  m_processedBlocks.insert( id );
  m_nEntitiesEstimation += nCount;
  if( m_pMeter ) m_pMeter->setLimit( m_nEntitiesEstimation );
}

void OdTvPartialImportNotifier::unloadCachedEntities()
{
  for( OdUInt32 i = 0; i < m_entitiesToUnload.size(); ++i )
  {
    m_pDatabase->writeObjectPartial( m_entitiesToUnload[ i ] );
  }
  m_entitiesToUnload.clear();
}

bool OdTvPartialImportNotifier::abortImport() const
{
  if( m_pAbort ) return m_pAbort->abortImport(); 
  return false;
}

void OdTvPartialImportNotifier::setImportAbort( OdTvLowMemoryImportAbort* pAbort )
{
  m_pAbort = pAbort;
}


OdTvDatabaseId OdTvVisualizeDwgFiler::partialLoadFrom(OdTvVisualizeDwgFilerDbSource *pDwgDatabaseSource, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
#ifdef OD_TV_MEASURE_PARTIAL
  clock_t timeStart1 = clock();
  clock_t timeEnd1 = 0;
  clock_t timeStart2 = 0;
  OdUInt64 memUsage = 0;
#endif
  bool bRemoveResultFile = false;
  OdString resultFileName;

  OdRxModulePtr pPlotSettingsModule;

  OdDbHostAppProgressMeter* pMeter = pDwgDatabaseSource->progressMeter();
  const bool bDoVSFUnloading = true;
  const bool bDoAddPartialIndex = true;
  const bool bDrawDWG = true;
  const bool bUnloadDWG = true;
  ODCOLORREF background = *((ODCOLORREF*)m_properties->getBackgroundColor());
  bool bUseAdvancedTess = m_properties->getUseAdvancedTess();
  double facetRes = m_properties->getFacetRes();
  OdTvVSFExportOptions* pVSFCompressionOptions = (OdTvVSFExportOptions*)m_properties->getLowMemoryImportVSFCompression();

  //create empty tv database.
  OdTvFactoryId tvFactoryId = odTvGetFactory();
  OdTvDatabaseId tvDbId = tvFactoryId.createDatabase();

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
  
  //apply new tesselation
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

  OdString moduleName;
  bool bOdExceptionCatched = false;
  OdResult exceptionCode;
  try
  {
    OdDbDatabasePtr pDb = pDwgDatabaseSource->getDb();

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
      OdTvDbBlockTableRecordOverrule overrule( bDrawDWG, bUnloadDWG );
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

        //unload modeler if it was loaded
        if (pModelerModule.get())
          pModelerModule.release();

        //uninitialize ODA SDK DB
        if (pDwgDatabaseSource->odWasInitialized())
          odUninitialize();

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
        return tvDbId;
      }

      pPlotSettingsModule = ::odrxDynamicLinker()->loadModule(OdPlotSettingsValidatorModuleName);

      // Set code page
      tvDbId.openObject(OdTv::kForWrite)->setCodePage(pDb->getDWGCODEPAGE());

      //enable database partial import mode
      OdTvDatabasePtr pTvDatabase = tvDbId.openObject( OdTv::kForWrite );
      if( bDoVSFUnloading )
      {
        pTvDatabase->beginPartialImport( m_properties->getPartialImportDumpFile() );
        bRemoveResultFile = true;
        resultFileName = m_properties->getPartialImportDumpFile();
      }

      //setup compression options (no compression by default)
      if (pVSFCompressionOptions)
        pTvDatabase->setVSFExportOptions(*pVSFCompressionOptions);

      OdTvPartialImportNotifier notifier( pTvDatabase, bDoAddPartialIndex, m_properties->getClearEmptyObjects());
      notifier.setImportAbort( (OdTvLowMemoryImportAbort*)(m_properties->getLowMemoryImportAbort()) );
      overrule.setNotifier( &notifier );
      if( pMeter )
      {
        pMeter->start( OD_T("Import starting...") );
      }
      notifier.setProgressMeter( pMeter );
      OdTvLimitManager* pManager = tvFactoryId.limitManager();
      if( pManager && ( pManager->supportedLimits() & OdTvLimitManager::kUnloadingLimit ) != 0 )
      {
        notifier.setLimitManager( pManager );
      }

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

        notifier.clearProcessedMaps();

        //update layout in the database
        pDb->setCurrentLayout(m_spaces[i]);

        //create Ex Visualize device
        OdGsDevicePtr pDevice = pGsModule->createDevice();

        // setup ExVisualize device properties
        OdRxDictionaryPtr pProperties = pDevice->properties();
        OdTvGsDeviceId activeTvDeviceId = OdTvGsDeviceId();
        setupExVisualizeDeviceProp(pProperties, tvDbId, bUseTimeProfiling, modelSpaceName, dwgPath, m_properties, deviceCache, activeTvDeviceId, bHavePaperSpace);
        //rewrite some options
        if (pProperties->has(OD_T("EnableMultithread")))
          pProperties->putAt(OD_T("EnableMultithread"), OdRxVariantValue(false));
        if( bDoVSFUnloading )
        {
          if( pProperties->has( OD_T("DeviceNotifier") ) )
          {
            pProperties->putAt( OD_T("DeviceNotifier"), OdRxVariantValue( (OdIntPtr)(&notifier) ) );
          }
        }
        if( pProperties->has( OD_T("DisableEntityCaching") ))
          pProperties->putAt( OD_T("DisableEntityCaching"), OdRxVariantValue( true ) );
        //setup additional property
        if (pDb->getLIGHTGLYPHDISPLAY())
        {
          if (pProperties->has(OD_T("LightGlyphDisplay")))
            pProperties->putAt(OD_T("LightGlyphDisplay"), OdRxVariantValue(true));
        }

        //setup dwg context
        OdGiContextForDbDatabasePtr pDwgContext = OdGiContextForDbDatabase::createObject();
        pDwgContext->enableGsModel(false);
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

      if( pMeter ) pMeter->stop();

      timing.startMisc();

      //VIS-1142
      //if (tvDbId.isValid() && m_properties->getClearEmptyObjects())
        //OdTvDatabaseCleaner::cleanTvDatabase(tvDbId);

      //disable database partial import mode
      notifier.unloadCachedEntities();
      if( bDoVSFUnloading )
      {
        pTvDatabase->endPartialImport();
        bRemoveResultFile = false;
      }

      timing.endMisc();
      tvDbExternalTiming += timing.getMiscTime();

      timing.endVectorizing();
#ifdef OD_TV_MEASURE_PARTIAL
      memUsage = GetMemoryUsageInternalInfo( 0 );
#endif
      moduleName = pGsModule->moduleName();

      //add user data for native db
      writeNativeDbDataAsUserData(tvDbId, pDb);
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

  //SEA if exception happens before, writeFileNameToTvDatabase and removeDatabase may be unsafe
  //So, we wrap them in try{} and remove vsf file after it unlocked
  try
  {
    // unload gs module
    if (pGsModule.get())
      pGsModule.release();
    if (!moduleName.isEmpty())
      odrxDynamicLinker()->unloadModule(moduleName);
  
    timing.startMisc();

    // save filename to database user data
    OdTvDatabaseUtils::writeFileNameToTvDatabase(tvDbId, pDwgDatabaseSource->getFilename());

    //unload modeler if it was loaded
    if (pModelerModule.get())
      pModelerModule.release();

    if (pPlotSettingsModule.get())
      pPlotSettingsModule.release();

    //uninitialize ODA SDK DB
    if (pDwgDatabaseSource->odWasInitialized())
      odUninitialize();

    OdTvFactoryId tvFactoryId = odTvGetFactory();
  #ifdef __IPHONE_OS_VERSION_MIN_REQUIRED
    OdTvDevicesIteratorPtr pDevicesIterator = tvDbId.openObject()->getDevicesIterator();
    if (!pDevicesIterator.isNull())
    {
      while (!pDevicesIterator->done())
      {
        OdTvGsDeviceId tvDeviceId = pDevicesIterator->getDevice();
        tvDeviceId.openObject(OdTv::kForWrite)->eraseAllViews();
        pDevicesIterator->step();
      }
    }
  #endif
    tvFactoryId.removeDatabase( tvDbId );

    timing.endMisc();
    tvDbExternalTiming += timing.getMiscTime();
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
    clock_t timeDiff = timeEnd2 - timeStart2 + ( timeEnd1 - timeStart1 );
    wsprintf( buff, L"PartialMode:\nMemory %ld (%ld MB)\nTime %ld (%ld sec)", memUsage, memUsage / ( 1024 * 1024 ), timeDiff, timeDiff / 1000 );
    MessageBox( NULL, buff, L"Partial MODE", MB_OK );
  #endif
  }
  catch( ... )
  {

  }

  if( bRemoveResultFile && !resultFileName.isEmpty() )
  {
#if !defined(_WIN32_WCE)
    remove(OdAnsiString(resultFileName).c_str());
#else
    DeleteFile(resultFileName.c_str());
#endif 
  }

  return OdTvDatabaseId();
}
