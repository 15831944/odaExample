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
#include "OdVisualizeSamples.h"
#include "TvDatabase.h"
#include "TvFactory.h"
#include "TvError.h"
#include "TvModuleNames.h"
#include "RxRasterServices.h"
#include "RxVariantValue.h"
#include "DynamicLinker.h"

#define OdVisualizePathChar '\\'

void doEvents()
{
  MSG msg;
  BOOL result;

  while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
  {
    result = ::GetMessage(&msg, NULL, 0, 0);
    if (result == 0) // WM_QUIT
    {
      ::PostQuitMessage(msg.wParam);
      break;
    }
    else if (result == -1)
    {
      // Handle errors/exit application, etc.
    }
    else
    {
      ::TranslateMessage(&msg);
      ::DispatchMessage(&msg);
    }
  }
}

/**
\details
Multi-view sample: imports file and present it using 3 different views. 
The first view also have the third view as sibling: all changes in first view will be also transfered to the third view.
However, if third view become active, changes in third view will not affect first view.
\remarks
First view will become active. Use "Navigation -> Change active view" to make other view active.
After import database already should have device and view. We will use this view to obtain view parameters for new views.
*/
class OdVisualizeMultiViewSample : public OdVisualizeSample
{

public:
  /**
  \details 
  Data for view parameters transfer
  */
  struct ViewParams
  {
    OdTvPoint position;
    OdTvPoint target;
    OdTvVector upVector;
    double fieldWidth;
    double fieldHeight;
    OdTvGsView::Projection proj;
  };
  /**
  \details
  Retrives parameters of original view (after import)
  */
  ViewParams obtainOriginalViewProps(OdTvDatabasePtr pDb)
  {
    ViewParams params;
    OdTvDevicesIteratorPtr pDevIt = pDb->getDevicesIterator();
    if (pDevIt->done()) return params;
    OdTvGsDeviceId origDevId = pDevIt->getDevice();
    OdTvGsViewId origView = origDevId.openObject( OdTv::kForRead )->viewAt( 0 );
    OdTvGsViewPtr pOrigView = origView.openObject( OdTv::kForRead );
    if (pOrigView.isNull()) return params;
    params.position = pOrigView->position();
    params.target = pOrigView->target();
    params.upVector = pOrigView->upVector();
    params.fieldWidth = pOrigView->fieldWidth();
    params.fieldHeight = pOrigView->fieldHeight();
    params.proj = pOrigView->isPerspective() ? OdTvGsView::kPerspective : OdTvGsView::kParallel;
    return params;
  }

  virtual bool run( OdVisualizeSampleContext* pContext )
  {
    //Extract file path from context
    if( !pContext ) return false;
    OdString path = pContext->filePath( OdVisualizeSampleContext::kOBJ );
    if( path.isEmpty() ) return false;

    //Create structure with *.obj file import params
    OdTvObjImportParams  objImportParam;
    objImportParam.setFilePath( path );

    //Import *.obj file to Visualize
    OdTvResult rc = tvOk;
    OdTvFactoryId factId = odTvGetFactory();
    OdTvDatabaseId dbId = factId.importFile( &objImportParam, &rc );
    if( rc != tvOk  ) return false;
    
    //Check that database is valid
    OdTvDatabasePtr pDb = dbId.openObject();
    if( pDb.isNull() ) return false;

    /* Retrive original view parameters
       After import database already should have deviceand view.We will use this view to obtain view parameters for new views.
    */
    ViewParams params = obtainOriginalViewProps( pDb );

    //Obtain imported model
    OdTvModelsIteratorPtr pModelsIt = pDb->getModelsIterator();
    if( pModelsIt->done() ) return false;
    OdTvModelId modelId = pModelsIt->getModel();
    
    //Create new device
    OdTvGsDeviceId devId = pContext->createDevice( dbId );
    
    //Create 3 views in device
    OdTvGsDevicePtr pDevice = devId.openObject( OdTv::kForWrite );
    OdTvGsViewId mainViewId = pDevice->createView( "ShadedView" );
    OdTvGsViewId view1Id = pDevice->createView( "WireframeView" );
    OdTvGsViewId view2Id = pDevice->createView( "SketchyView" );
    
    /* Setup first view: add model, set view paramaters obtained from imported view,
       set relative position of the view in the device, set render mode
    */
    OdTvGsViewPtr pView = mainViewId.openObject( OdTv::kForWrite );
    pView->addModel( modelId );
    pView->setView( params.position, params.target, params.upVector, params.fieldWidth, params.fieldHeight, params.proj );
    pView->setViewport( OdTvPoint2d( 0, 0 ), OdTvPoint2d( 0.5, 1 ) ); //Use left half of the screen
    pView->setMode(OdTvGsView::kGouraudShaded);
    pView->setBorderVisibility(true);

    //Add view to the device
    pDevice->addView(mainViewId);

    /* Setup second view: add model, set view paramaters obtained from imported view,
       set relative position of the view in the device
    */
    pView = view1Id.openObject( OdTv::kForWrite );
    pView->addModel( modelId );
    pView->setView( params.position, params.target, params.upVector, params.fieldWidth, params.fieldHeight, params.proj );
    pView->setViewport( OdTvPoint2d( 0.5, 0.5 ), OdTvPoint2d( 1, 1 ) ); //Use top right quarter of the screen
    pView->setBorderVisibility(true);

    //Rotate a bit around the eye vector and add to the device
    pView->roll( OdaPI4 );
    pDevice->addView(view1Id);
    
    /* Setup third view: add model, set view paramaters obtained from imported view,
       set relative position of the view in the device, set visual style
    */
    pView = view2Id.openObject(OdTv::kForWrite);
    pView->addModel(modelId);
    pView->setView( params.position, params.target, params.upVector, params.fieldWidth, params.fieldHeight, params.proj );
    pView->setViewport( OdTvPoint2d( 0.5, 0 ), OdTvPoint2d( 1, 0.5 ) );     //Use bottom right quarter of the screen
    pView->setBorderVisibility(true);

    //Use default "Sketchy" visual style and add to the device
    pView->setVisualStyle( pDb->findVisualStyle( OD_T( "Sketchy" ) ) );  
    pDevice->addView(view2Id);

    //Notify application about changes:
    //New active database
    pContext->setActiveDatabase( dbId );

    //New active device
    pContext->setActiverDevice( devId );

    //New active view with index 0 (mainViewId - first view, that we create)
    pContext->setActiveView( mainViewId, 0 );

    //First update. We need it to obtain extents and perform ZoomToExtents
    pDevice->update();

    //Zoom to extents in first view
    pView = mainViewId.openObject(OdTv::kForWrite);
    OdGeBoundBlock3d bb;
    pView->viewExtents(bb);
    pView->zoomExtents(bb.minPoint(), bb.maxPoint());

    //Zoom to extents in second view
    pView = view1Id.openObject(OdTv::kForWrite);
    pView->viewExtents(bb);
    pView->zoomExtents(bb.minPoint(), bb.maxPoint());

    //Zoom to extents in third view
    pView = view2Id.openObject(OdTv::kForWrite);
    pView->viewExtents(bb);
    pView->zoomExtents(bb.minPoint(), bb.maxPoint());

    //Specify third view as sibling of the first view
    pView = mainViewId.openObject( OdTv::kForWrite );
    pView->addSibling( view2Id );

    //Final update
    pDevice->update();

    return true;
  }
};

/**
\details
Walking animation sample sample: performs short walking through some predefined model
*/
class OdVisualizeWalkingAnimationSample : public OdVisualizeSample
{
public:

  OdVisualizeWalkingAnimationSample() {};

  virtual bool run(OdVisualizeSampleContext* pContext)
  {
    //get exe folder path
    wchar_t path[MAX_PATH + 1] = { 0 };
    GetModuleFileNameW(NULL, path, MAX_PATH);
    OdString strResourceFolderPath = path;
    strResourceFolderPath = strResourceFolderPath.left(strResourceFolderPath.reverseFind(OdVisualizePathChar) + 1);

    //prepare empty database ID
    OdTvDatabaseId dbId;

    //load models generator module
    {
      OdTvVisualizeFilerModulePtr pVisualizeFilerModule = ::odrxDynamicLinker()->loadApp(OdTvModelsGeneratorModuleName);
      if (pVisualizeFilerModule.isNull())
        return false;

      //get filer interface
      OdTvVisualizeFilerPtr pFiler = pVisualizeFilerModule->getVisualizeFiler();
      if (pFiler.isNull())
        return false;

      // get properties
      OdRxDictionaryPtr pProperties = pFiler->properties();
      if (pProperties.get())
      {
        OdUInt16 sampleID = 1027; //means camra walk sample

        if (pProperties->has(OD_T("SampleID")))
          pProperties->putAt(OD_T("SampleID"), OdRxVariantValue(sampleID));

        if (pProperties->has(OD_T("ResourceFolder")))
          pProperties->putAt(OD_T("ResourceFolder"), OdRxVariantValue(strResourceFolderPath));
      }

      // generate sample model
      dbId = pFiler->generate();
    }

    //unload module
    ::odrxDynamicLinker()->unloadModule(OdTvModelsGeneratorModuleName);

    //Check that database is valid
    OdTvDatabasePtr pDb = dbId.openObject();
    if (pDb.isNull()) return false;

    // Get device (here it is always the first device) and setup
    OdTvDevicesIteratorPtr pIt = pDb->getDevicesIterator();
    if (!pIt.isNull())
    {
      OdTvGsDeviceId deviceId = pIt->getDevice();

      //setup device
      OdTvDCRect rect = pContext->setupDevice(deviceId);

      //get pointer to the device object
      OdTvGsDevicePtr pDevice = deviceId.openObject(OdTv::kForWrite);

      //set option to use Scene Graph (performance optimization)
      pDevice->setOption(OdTvGsDevice::kUseSceneGraph, true);

      // Update device
      pDevice->onSize(rect);
      pDevice->update();

      //Notify application about changes:
      //New active database
      pContext->setActiveDatabase(dbId);

      //New active device
      pContext->setActiverDevice(deviceId);

      //New active view with index 0 (mainViewId - first view, that we create)
      pContext->setActiveView(pDevice->getActiveView(), 0);

      //show message box to start animation
      pContext->showMessageBox(L"Press OK to start animation", L"Start animation", MB_OK | MB_ICONINFORMATION);

      //start animation playing
      //We know that this predefined database contains one animation container, so get it
      OdTvDatabasePtr pDb = dbId.openObject();
      OdTvAnimationContainersIteratorPtr pContIt = pDb->getAnimationContainersIterator();
      if (pContIt->done())
        return false;

      OdTvAnimationContainerId containerId = pContIt->getAnimationContainer();
      
      OdUInt32 totalTime = 0;
      containerId.openObject()->totalTime(totalTime);

      clock_t start = clock();
      clock_t curTime = start;
      while (curTime - start < (OdInt32)totalTime)
      {
        containerId.openObject(OdTv::kForWrite)->setCurrentTime(curTime - start);
        curTime = clock();
        pDevice->update();
        doEvents();
      }
    }

    return true;
  }
};

bool OdVisualizeSampleManager::run( Samples sample, OdVisualizeSampleContext* pContext )
{
  switch( sample )
  {
  case kMultiViewSample:
  {
    OdVisualizeMultiViewSample smpl;
    return smpl.run( pContext );
  }
  break;
  case kWalkingAnimation:
  {
    OdVisualizeWalkingAnimationSample smpl;
    return smpl.run(pContext);
  }
  break;
  }
  return false;
}

