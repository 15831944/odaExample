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

#include "VisualizeModelsGeneratorImpl.h"
#include "VisualizeModelsGeneratorUtils.h"
#include "VisualizeModelsGeneratorTeapot.h"

#include "TvFilerTimer.h"

double SinPlusCos(double x, double y)
{
  return sin(x) + cos(y);
}


//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************

OdTvDatabaseId OdTvVisualizeSampleModels::generateEmptyModel(OdTvFactoryId& id)
{
  static int sequenceNumber = 1;

  OdString strCurTitle;
  strCurTitle.format(OD_T("TV_Model%d"), sequenceNumber++);

  //create empty database
  OdTvDatabaseId databaseId = id.createDatabase();

  // create empty model
  OdTvDatabasePtr dbPtr = databaseId.openObject(OdTv::kForWrite);

  OdTvModelId modelId = dbPtr->createModel(strCurTitle);

  return databaseId;
}

OdTvDatabaseId OdTvVisualizeSampleModels::generateSoccerModel(OdTvFactoryId& id)
{
  static int sequenceSoccerNumber = 1;

  // Create window title
  OdString strCurTitle;
  strCurTitle.format(OD_T("SoccerField%d"), sequenceSoccerNumber++);

  //create empty database
  OdTvDatabaseId databaseId = id.createDatabase();

  //create and fill the model
  OdTvDatabasePtr dbPtr = databaseId.openObject(OdTv::kForWrite);

  OdTvModelId modelId = dbPtr->createModel(strCurTitle);

  // fill model according to the soccer example
  initSoccerFieldModel(databaseId, modelId);

  return databaseId;
}

OdTvDatabaseId OdTvVisualizeSampleModels::generateAllEntitiesModel(OdTvFactoryId& id, const OdString& strResourceFolder)
{
  static int sequenceAllEntitiesNumber = 1;

  // Create window title
  OdString strCurTitle;
  strCurTitle.format(OD_T("AllEntitiesModel%d"), sequenceAllEntitiesNumber++);

  //create empty database
  OdTvDatabaseId databaseId = id.createDatabase();

  //create and fill the model
  OdTvDatabasePtr dbPtr = databaseId.openObject(OdTv::kForWrite);

  OdTvModelId modelId = dbPtr->createModel(strCurTitle);

  // fill model according to the soccer example
  initAllEntitiesModel(databaseId, modelId, strResourceFolder);

  return databaseId;
}

OdTvDatabaseId OdTvVisualizeSampleModels::generateProgressiveMeshModel( OdTvFactoryId& id, const OdString& strResourceFolder )
{
  //Read existing file
  OdString fileName = strResourceFolder + OD_T( "pmExample.vsf" );
  OdTvDatabaseId dbId = importVSF( fileName );
  // Create window title
  static int sequencePMNumber = 1;
  OdString strCurTitle;
  strCurTitle.format( OD_T( "ProgressiveMeshModel%d" ), sequencePMNumber++ );
  if( dbId.isNull() ) return dbId;
  //Rename existing model
  OdTvDatabasePtr pDb = dbId.openObject( OdTv::kForWrite );
  OdTvModelPtr pModel = pDb->getModelsIterator()->getModel().openObject( OdTv::kForWrite );
  pModel->setName( strCurTitle );
  return dbId;
}

OdTvDatabaseId OdTvVisualizeSampleModels::generateCAEModel(OdTvFactoryId& id, int type)
{
  static int sequenceCAENumber = 1;

  static int viewNumber = 1;
  static int compositeWindowNumber = 1;
  static int titleViewNumber = 1;
  static int colorBarViewNumber = 1;

  // Create window title
  OdString strCurTitle;
  strCurTitle.format(OD_T("CAE_SAMPLE%d_%d"), sequenceCAENumber++, type + 1);

  //create empty database
  OdTvDatabaseId databaseId = id.createDatabase();

  //create and fill the model
  OdTvDatabasePtr dbPtr = databaseId.openObject(OdTv::kForWrite);

  OdTvModelId modelId = dbPtr->createModel(strCurTitle);

  OdTvModelId tvSecondModelId, tvThirdModelId;

  // fill model with CAE 3D sample
  if (type == 0)
  {
    initPlotModel(databaseId, modelId);
  }
  else if (type == 1)
  {
    tvSecondModelId = dbPtr->createModel(OdString(OD_T("COLOR_BAR")));
    tvThirdModelId = dbPtr->createModel(OdString(OD_T("TITLE")));

    initSurfPlotOtherModel(databaseId, tvSecondModelId, tvThirdModelId);
    initSurfPlotModel(databaseId, modelId);
  }
  else if (type == 2)
  {
    tvSecondModelId = dbPtr->createModel(OdString(OD_T("COLOR_BAR")));
    tvThirdModelId = dbPtr->createModel(OdString(OD_T("TITLE")));

    initCylinderTemperatureModel(databaseId, modelId, tvSecondModelId, tvThirdModelId);
  }

  // create and fill devices and views
  OdTvResult rc;

  OdString strDeviceName;
  strDeviceName.format(OD_T("WindowComposite_%d"), compositeWindowNumber++);

  OdString strViewName;
  strViewName.format(OD_T("View_%d"), viewNumber++);

  OdString strColorBarViewName;
  strColorBarViewName.format(OD_T("ColorBarView_%d"), colorBarViewNumber++);

  OdString strTitleViewName;
  strTitleViewName.format(OD_T("TitleView_%d"), titleViewNumber++);

  // create "non-setup device"
  OdTvGsDeviceId deviceId = dbPtr->createDevice(strDeviceName);
  OdTvGsDevicePtr pDevice = deviceId.openObject(OdTv::kForWrite);

  // create main view
  OdTvGsViewId viewId = pDevice->createView(strViewName, true, &rc);
  pDevice->addView(viewId);
  // add current model to the view
  {
    OdTvGsViewPtr viewPtr = viewId.openObject();

    if (type == 0)
    {
      viewPtr->set2dMode(true);
      viewPtr->setView(OdTvPoint(0., 0., 1.), OdTvPoint(0., 0., 0.), OdTvVector(0., 1., 0.), 1.5, 1.5);
    }
    else if (type == 1)
    {
      viewPtr->setView(OdTvPoint(-1., -1., 0.5), OdTvPoint(0., 0., 0.), OdTvVector(0., 0., 1.), 2., 2.);
      viewPtr->setMode(OdTvGsView::kGouraudShadedWithWireframe);
    }
    else
    {
      viewPtr->setView(OdTvPoint(0., 0., 1.), OdTvPoint(0., 0., 0.), OdTvVector(0., 1., 0.), 1., 1.);
      viewPtr->setMode(OdTvGsView::kGouraudShadedWithWireframe);
    }

    viewPtr->addModel(modelId);

    viewPtr->setActive(true);
  }

  if (type > 0)
  {
    // add view with color bar
    OdTvGsViewId colorBarViewId = pDevice->createView(strColorBarViewName, true, &rc);
    pDevice->addView(colorBarViewId);

    // add second model to the view
    {
      OdTvGsViewPtr viewPtr = colorBarViewId.openObject();

      viewPtr->setView(OdTvPoint(0., 0., 1.), OdTvPoint(0., 0., 0.), OdTvVector(0., 1., 0.), 1. / 2.1, 1. / 2.1);
      viewPtr->addModel(tvSecondModelId);
      viewPtr->setMode(OdTvGsView::kGouraudShadedWithWireframe);
      viewPtr->setViewport(OdGePoint2d(0.8, 0), OdGePoint2d(1, 0.9));
    }

    // add view with title
    OdTvGsViewId titleViewId = pDevice->createView(strTitleViewName, true, &rc);
    pDevice->addView(titleViewId);

    // add third model to the view
    {
      OdTvGsViewPtr viewPtr = titleViewId.openObject();

      viewPtr->setView(OdTvPoint(0., 0., 1.), OdTvPoint(0., 0., 0.), OdTvVector(0., 1., 0.), 1. / 6., 1. / 6.);
      viewPtr->addModel(tvThirdModelId);
      viewPtr->setMode(OdTvGsView::kGouraudShadedWithWireframe);
      viewPtr->setViewport(OdGePoint2d(0, 0.9), OdGePoint2d(1, 1));
    }
  }

  return databaseId;
}

OdTvDatabaseId OdTvVisualizeSampleModels::generateMaterialsSampleModel(OdTvFactoryId& id, OdTvFilerTimeProfiling* pProfileRes, const OdString& strResourceFolder, int type)
{
  static int sequenceMaterialsNumber = 1;

  // Create window title
  OdString strCurTitle;
  strCurTitle.format(OD_T("Materials%d"), sequenceMaterialsNumber++);

  OdTvDatabaseId databaseId;
  OdTvModelId modelId;
  if (type != 3)
  {
    //create empty database
    databaseId = id.createDatabase();

    //create and fill the model
    OdTvDatabasePtr dbPtr = databaseId.openObject(OdTv::kForWrite);

    modelId = dbPtr->createModel(strCurTitle);

    if (type == 0)
    {
      // fill sword example
      initSwordModel(databaseId, modelId, strResourceFolder);
    }
    else if (type == 1)
    {
      // fill ball example
      initBallModel(databaseId, modelId, strResourceFolder);
    }
    else if (type == 2)
    {
      // fill teapot example
      initTeapotModel(databaseId, modelId, strResourceFolder);
    }
    else if (type == 4)
    {
      // fill opacity example
      initOpacityModel(databaseId, modelId, strResourceFolder);
    }
    else if (type == 5)
    {
      // fill bump example
      initBumpModel(databaseId, modelId, strResourceFolder);
    }

    // create "non-setup device"
    OdTvGsDeviceId deviceId = dbPtr->createDevice(strCurTitle);

    OdTvGsDevicePtr pDevice = deviceId.openObject(OdTv::kForWrite);

    OdString strViewName;
    strViewName.format(OD_T("View_%d"), sequenceMaterialsNumber++);

    OdTvResult rc;

    // create main view
    OdTvGsViewId viewId = pDevice->createView(strViewName, true, &rc);
    pDevice->addView(viewId);
    // add current model to the view
    {
      OdTvGsViewPtr viewPtr = viewId.openObject();
      if (type == 0)
        viewPtr->setView(OdTvPoint(0., -0.5, 0.), OdTvPoint(0., -0.5, 0.), OdTvVector(0., 1., 0.), 1.5, 1.5);
      else if (type == 1)
        viewPtr->setView(OdTvPoint(3., 3., 0.), OdTvPoint(3., 3., 0.), OdTvVector(0., 1., 0.), 4., 4.);
      else if (type == 4)
        viewPtr->setView(OdTvPoint(0., 0., 1.), OdTvPoint(0., 0., 0.), OdTvVector(0., 1., 0.), 1.7, 1.);
      else if (type == 5)
        viewPtr->setView(OdTvPoint(0., 0., 1.), OdTvPoint(0., 0., 0.), OdTvVector(0., 1., 0.), 4., 3.);
      else
        viewPtr->setView(OdTvPoint(0.1, 0.8, 0.), OdTvPoint(0.1, 0.8, 0.), OdTvVector(0., 1., 0.), 3.5, 2.);

      viewPtr->addModel(modelId);
      viewPtr->setMode(OdTvGsView::kGouraudShaded);
      if (type == 2)
        viewPtr->enableDefaultLighting(false);

      viewPtr->setActive(true);
    }
  }
  else // fill pepsi can example
    initPepcianModel(databaseId, id, modelId, pProfileRes, strResourceFolder);

  return databaseId;
}


OdTvDatabaseId OdTvVisualizeSampleModels::generateAnimationSample( OdTvFactoryId& factId )
{
  OdTvDatabaseId dbId = factId.createDatabase();
  OdTvDatabasePtr pDb = dbId.openObject( OdTv::kForWrite );
  OdTvModelId modelId = pDb->createModel( OD_T( "EntityAnimationModel" ) );
  OdTvModelPtr pModel = modelId.openObject( OdTv::kForWrite );
  //1.2 Create entity with single line
  OdTvEntityId entId = pModel->appendEntity( OD_T( "RotatingLine1" ) );
  OdTvEntityPtr pEnt = entId.openObject( OdTv::kForWrite );
  pEnt->appendPolyline( OdTvPoint( -1.0, -1.0, 0.0 ), OdTvPoint( 1.0, 1.0, 0.0 ) );
  //2. Create animation
  //2.1 Create animation container
  OdTvAnimationContainerId contId = pDb->createAnimationContainer( OD_T( "FirstLineAnimation" ) );
  OdTvAnimationContainerPtr pCont = contId.openObject( OdTv::kForWrite );
  //2.2 Create animation action: rotation on 360 degrees around Z axis
  //2.2.1 Create action
  OdTvAnimationActionId actionId = pDb->createAnimationAction( OD_T( "LineRotation" ) );
  OdTvAnimationActionPtr pAction = actionId.openObject( OdTv::kForWrite );
  //2.2.2 Specify number of frames
  pAction->setNumFrames( 361 );
  //2.2.3 Each 10 frame is a key frame
  for( OdUInt32 i = 0; i <= 360; i += 10 )
  {
    double angle = (double)(i)*OdaPI / 180.0;
    pAction->setKeypoint( i, OdTvAnimationAction::kRotationZ, angle, OdTvAnimationAction::kLinear );
  }
  //2.3 Specify actor
  OdTvSubItemPath actor;
  actor.entitiesIds().push_back( entId );
  //2.4 Add pair <Actor, Action> to the container with infinite repeats number
  pCont->addAnimation( actor, actionId, -1 );

  //Another animation with the same action
  entId = pModel->appendEntity( OD_T( "RotatingLine2" ) );
  pEnt = entId.openObject( OdTv::kForWrite );
  pEnt->appendPolyline( OdTvPoint( -1.0, -1.0, 0.0 ), OdTvPoint( 1.0, 1.0, 0.0 ) );
  pEnt->setModelingMatrix( OdTvMatrix::translation( OdTvVector( 3.0, 0.0, 0.0 ) ) );
  contId = pDb->createAnimationContainer( OD_T( "SecondLineAnimation" ) );
  pCont = contId.openObject( OdTv::kForWrite );
  OdTvSubItemPath actor1;
  actor1.entitiesIds().push_back( entId );
  pCont->addAnimation( actor1, actionId, -1 );

  //Third animation - translation
  entId = pModel->appendEntity( OD_T( "MovingLine" ) );
  pEnt = entId.openObject( OdTv::kForWrite );
  pEnt->appendPolyline( OdTvPoint( -3.0, 1.0, 0.0 ), OdTvPoint( -3.0, -1.0, 0.0 ) );
  contId = pDb->createAnimationContainer( OD_T( "ThirdLineAnimation" ) );
  pCont = contId.openObject( OdTv::kForWrite );
  OdTvSubItemPath actor2;
  actor2.entitiesIds().push_back( entId );
  actionId = pDb->createAnimationAction( OD_T( "LineTranslation" ) );
  pAction = actionId.openObject( OdTv::kForWrite );
  pAction->setNumFrames( 41 );
  pAction->setKeypoint( 0, OdTvAnimationAction::kTranslationX, 0.0, OdTvAnimationAction::kLinear );
  pAction->setKeypoint( 0, OdTvAnimationAction::kTranslationY, 0.0, OdTvAnimationAction::kLinear );

  pAction->setKeypoint( 10, OdTvAnimationAction::kTranslationX, -1.0, OdTvAnimationAction::kLinear );
  pAction->setKeypoint( 10, OdTvAnimationAction::kTranslationY, -1.0, OdTvAnimationAction::kLinear );

  pAction->setKeypoint( 20, OdTvAnimationAction::kTranslationX, -1.0, OdTvAnimationAction::kLinear );
  pAction->setKeypoint( 20, OdTvAnimationAction::kTranslationY, 0.0, OdTvAnimationAction::kLinear );

  pAction->setKeypoint( 30, OdTvAnimationAction::kTranslationX, 0.0, OdTvAnimationAction::kLinear );
  pAction->setKeypoint( 30, OdTvAnimationAction::kTranslationY, -1.0, OdTvAnimationAction::kLinear );

  pAction->setKeypoint( 40, OdTvAnimationAction::kTranslationX, 0.0, OdTvAnimationAction::kLinear );
  pAction->setKeypoint( 40, OdTvAnimationAction::kTranslationY, 0.0, OdTvAnimationAction::kLinear );

  pCont->addAnimation( actor2, actionId, -1 );

  return dbId;
}

OdTvDatabaseId OdTvVisualizeSampleModels::generateCameraAnimationSample( OdTvFactoryId& factId, OdTvFilerTimeProfiling* pProfileRes, const OdString& strResourceFolder )
{
  OdString odSFileName = OdTvVisualizeSampleModelsUtils::formatPath(strResourceFolder, OD_T("samples/CameraAnimationExample.vsf"));

  // read the file
  //prepare timing object
  OdTvFilerTimer timing(true);
  timing.startTotal();

  OdTvResult rc;
  OdTvDatabaseId databaseId = importVSF(odSFileName, false, false, &rc);

  // fill profiling info
  if (pProfileRes)
    pProfileRes->setImportTime(OdInt64(timing.getTotalTime() * 1000.));

  //get active model 
  OdTvDatabasePtr pTvDb;
  OdTvModelId modelId;
  if (databaseId.isValid())
  {
    pTvDb = databaseId.openObject();

    if (!pTvDb.isNull())
    {
      OdTvModelsIteratorPtr pModelsIterator = pTvDb->getModelsIterator();
      modelId = pModelsIterator->getModel();
    }
  }

  //checks
  if( modelId.isNull() || pTvDb.isNull() )
  {
    ODA_FAIL();
    return databaseId;
  }

  //0) Initial preporations: create copy of original view
  //0.1) Obtain original view
  OdTvDevicesIteratorPtr pDevIt = pTvDb->getDevicesIterator();
  OdTvGsDevicePtr pDevice = pDevIt->getDevice().openObject( OdTv::kForWrite );
  OdTvGsViewId originalViewId = pDevice->viewAt( 0 );
  OdTvGsViewPtr pOriginalView = originalViewId.openObject( OdTv::kForWrite );
  //0.2) Create new view
  OdTvGsViewId newViewId = pDevice->createView( OD_T( "SecondView" ) );
  OdTvGsViewPtr pView = newViewId.openObject( OdTv::kForWrite );
  pView->addModel( modelId );
  pDevice->addView( newViewId );
  //0.3) Copy parameters from original view to the new one
  pView->setView( pOriginalView->position(), pOriginalView->target(), pOriginalView->upVector(), pOriginalView->fieldWidth(), pOriginalView->fieldHeight() );
  pView->setBackground( pOriginalView->getBackground() );
  pView->setVisualStyle( pOriginalView->getVisualStyle() );
  pView->setDefaultLightingColor( pOriginalView->defaultLightingColor() );
  pView->setDefaultLightingIntensity( pOriginalView->defaultLightingIntensity() );
  pView->enableDefaultLighting( pOriginalView->defaultLightingEnabled(), pOriginalView->defaultLightingType() );
  //0.4) Specify new viewports for both views
  pOriginalView->setViewport( OdTvPoint2d( 0., 0. ), OdTvPoint2d( 0.5, 1. ) );
  pView->setBorderVisibility( true );
  pOriginalView->setBorderVisibility( true );
  pView->setViewport( OdTvPoint2d( 0.5, 0. ), OdTvPoint2d( 1., 1. ) );

  //1) Get model extents
  OdTvModelPtr pModel = modelId.openObject( OdTv::kForWrite );
  OdTvExtents3d extents;
  pModel->getExtents( extents );
  if( !extents.isValidExtents() )
  {
    ODA_FAIL();
    return databaseId;
  }
  //2.1) Create camera using extents: target is center, position (initial) in Min X, Min Y, center Z, up is X
  OdTvPoint target = extents.center();
  OdTvPoint position = target;
  position.x = extents.minPoint().x;
  position.y = extents.minPoint().y;
  OdTvVector up = OdTvVector::kZAxis;
  //2.2) Move position away from extents. Since camera will be parallel, it will have no effect on assigned view,
  //     but it will have effect in other cases
  position = target + ( position - target ) * 2.0;
  //2.3) Create circle to demonstrate camera orbit, only for the original view
  OdTvEntityId entId = pModel->appendEntity( OD_T( "CameraOrbit" ) );
  OdTvEntityPtr pEnt = entId.openObject( OdTv::kForWrite );
  pEnt->appendCircle( target, ( target - position ).length(), up );
  pEnt->addViewDependency( originalViewId );
  //2.4) Create and setup camera 
  OdTvEntityId cameraId = pModel->appendCamera( OD_T( "AnimatedCamera" ) );
  OdTvCameraPtr pCamera = cameraId.openObjectAsCamera( OdTv::kForWrite );
  pCamera->setupCamera( position, target, up );
  //pCamera->setViewParameters( extents.maxPoint().x - extents.minPoint().x, extents.maxPoint().y - extents.minPoint().y, false );
  //2.4.1) Field width should be diagonal of extents planes to emulate Zoom to Extents
  //       Field height should be extents Z size
  OdTvPoint p1 = OdTvPoint( extents.maxPoint().x, extents.minPoint().y, extents.maxPoint().z );
  OdTvPoint p2 = OdTvPoint( extents.minPoint().x, extents.maxPoint().y, extents.maxPoint().z );
  double fW = ( p2 - p1 ).length();
  double fH = fabs( extents.maxPoint().z - extents.minPoint().z );
  pCamera->setViewParameters( fW, fH, false );
  //2.4.2) Make camera glyph and target visible
  pCamera->setDisplayGlyph( true );
  pCamera->setDisplayTarget( true );
  //3) Create animation: rotate camera about X axis (follow by the circle)
  //3.1) Animation container
  OdTvAnimationContainerId contId = pTvDb->createAnimationContainer( OD_T( "CameraRotationExample" ) );
  OdTvAnimationContainerPtr pContainer = contId.openObject( OdTv::kForWrite );
  //3.2) Animation action
  OdTvAnimationActionId actionId = pTvDb->createAnimationAction( OD_T( "CameraRotationAction" ) );
  OdTvAnimationActionPtr pAction = actionId.openObject( OdTv::kForWrite );
  pAction->setNumFrames( 360 );
  pAction->setKeypoint( 0, OdTvAnimationAction::kRotationZ, 0.0, OdTvAnimationAction::kLinear );
  pAction->setKeypoint( 359, OdTvAnimationAction::kRotationZ, 359.0 * OdaPI / 180.0, OdTvAnimationAction::kLinear );
  pAction->setFPS( 36 );
  //3.3) Animation actor
  OdTvSubItemPath actor;
  actor.entitiesIds().push_back( cameraId );
  //3.4) Prepare animation basis: we need target as origin
  OdTvAnimationContainer::OdTvActorBasis basis;
  basis.origin() = target;
  //3.5) Add endless animation
  pContainer->addAnimation( actor, actionId, -1, 0, &basis );
  //4) Create almost the same animation using different action: instead of camera rotation we will move camera position by the circle
  //4.1) Animation container
  contId = pTvDb->createAnimationContainer( OD_T( "CameraPositionMoveExample" ) );
  pContainer = contId.openObject( OdTv::kForWrite );
  //4.2) Animation action
  actionId = pTvDb->createAnimationAction( OD_T( "CameraPositionMoveAction" ) );
  pAction = actionId.openObject( OdTv::kForWrite );
  pAction->setNumFrames( 361 );
  //4.2.1) Each 10 frame - is a key frame
  for( OdUInt32 i = 0; i < 361; i+= 10 )
  {
    OdTvPoint newPosition = position;
    double angle = (double)(i)*OdaPI / 180.0;
    newPosition.rotateBy( angle, up, target );
    pAction->setKeypoint( i, OdTvAnimationAction::kTranslationX, newPosition.x - position.x, OdTvAnimationAction::kLinear );
    pAction->setKeypoint( i, OdTvAnimationAction::kTranslationY, newPosition.y - position.y, OdTvAnimationAction::kLinear );
  }
  pAction->setFPS( 36 );
  //4.3) Animation actor
  OdTvSubItemPath actorPosition;
  actorPosition.entitiesIds().push_back( cameraId );
  actorPosition.geometryDatasIds().push_back( pCamera->positionId() );
  //4.4) Add endless animation
  pContainer->addAnimation( actorPosition, actionId, -1 );
  //5) Assign new view to the camera, so
  //   Original view will demonstarte camera as object in scene
  //   New view will demonstarte camera as viewpoint
  pCamera->assignView( newViewId );

  return databaseId;
}

void setActionPoint( OdTvAnimationActionPtr pAction, OdUInt32 nFrame, const OdTvPoint& pt )
{
  pAction->setKeypoint( nFrame, OdTvAnimationAction::kTranslationX, pt.x, OdTvAnimationAction::kLinear );
  pAction->setKeypoint( nFrame, OdTvAnimationAction::kTranslationY, pt.y, OdTvAnimationAction::kLinear );
  pAction->setKeypoint( nFrame, OdTvAnimationAction::kTranslationZ, pt.z, OdTvAnimationAction::kLinear );
}

void setActionPoint( OdTvAnimationActionPtr pAction, OdUInt32 nFrame, const OdTvVector& v )
{
  pAction->setKeypoint( nFrame, OdTvAnimationAction::kTranslationX, v.x, OdTvAnimationAction::kLinear );
  pAction->setKeypoint( nFrame, OdTvAnimationAction::kTranslationY, v.y, OdTvAnimationAction::kLinear );
  pAction->setKeypoint( nFrame, OdTvAnimationAction::kTranslationZ, v.z, OdTvAnimationAction::kLinear );
}

OdTvDatabaseId OdTvVisualizeSampleModels::generateCameraWalkSample( OdTvFactoryId& factId, OdTvFilerTimeProfiling* pProfileRes, const OdString& strResourceFolder )
{
  //generate full path to VSF file with the model
  OdString odSFileName = OdTvVisualizeSampleModelsUtils::formatPath( strResourceFolder, OD_T( "samples/CameraWalkExample.vsf" ) );
  
  // read the file
  //prepare timing object
  OdTvFilerTimer timing( true );
  timing.startTotal();

  // read the VSF file with the model
  OdTvResult rc;
  OdTvDatabaseId databaseId = importVSF( odSFileName, false, false, &rc );

  // fill profiling info
  if( pProfileRes )
    pProfileRes->setImportTime( OdInt64( timing.getTotalTime() * 1000. ) );

  //get active model 
  OdTvDatabasePtr pTvDb;
  OdTvModelId modelId;
  if( databaseId.isValid() )
  {
    pTvDb = databaseId.openObject();

    if( !pTvDb.isNull() )
    {
      OdTvModelsIteratorPtr pModelsIterator = pTvDb->getModelsIterator();
      modelId = pModelsIterator->getModel();
    }
  }

  //checks
  if( modelId.isNull() || pTvDb.isNull() )
  {
    ODA_FAIL();
    return databaseId;
  }

  //0) Initial preparations
  //0.1) Obtain original view
  OdTvDevicesIteratorPtr pDevIt = pTvDb->getDevicesIterator();
  OdTvGsDevicePtr pDevice = pDevIt->getDevice().openObject( OdTv::kForWrite );
  OdTvGsViewId originalViewId = pDevice->viewAt( 0 );
  OdTvGsViewPtr pOriginalView = originalViewId.openObject( OdTv::kForWrite );

  //0.2) Create new view
  OdTvGsViewId newViewId = pDevice->createView( OD_T( "SecondView" ) );
  OdTvGsViewPtr pView = newViewId.openObject( OdTv::kForWrite );
  pView->addModel( modelId );
  pDevice->addView( newViewId );

  //0.3) Copy parameters from original view to the new one
  pView->setView( pOriginalView->position(), pOriginalView->target(), pOriginalView->upVector(), pOriginalView->fieldWidth(), pOriginalView->fieldHeight() );
  pView->setBackground( pOriginalView->getBackground() );
  pView->setVisualStyle( pOriginalView->getVisualStyle() );
  pView->setDefaultLightingColor( pOriginalView->defaultLightingColor() );
  pView->setDefaultLightingIntensity( pOriginalView->defaultLightingIntensity() );

  //0.4) Specify new viewports for both views
  pOriginalView->setViewport( OdTvPoint2d( 0., 0. ), OdTvPoint2d( 1, 1. ) );
  pView->setBorderVisibility( true );
  pView->setViewport( OdTvPoint2d( 0.66, 0.66 ), OdTvPoint2d( 1., 1. ) );

  //0.5) Walk path preparations
  OdTvPoint positions[] = { OdTvPoint( 78.5732, 63.3735, 12.0 ),
                            OdTvPoint( 61.2221, 53.0744, 12.0 ),
                            OdTvPoint( 35.8042, 53.1759, 12.0 ),
                            OdTvPoint( 34.114, 12.1115, 12.0 )
  };
  OdTvPoint originalTarget = OdTvPoint( 61.2221, 53.0744, 12.0 );
  OdTvPoint originalPosition = positions[ 0 ];
  OdTvVector originalUp = OdTvVector::kZAxis;
  OdTvModelPtr pModel = modelId.openObject( OdTv::kForWrite );

  //0.6) Entity to present path in the second view
  OdTvEntityId pathId = pModel->appendEntity( OD_T( "CameraPath" ) );
  OdTvEntityPtr pPath = pathId.openObject( OdTv::kForWrite );
  pPath->appendPolyline( 4, positions );
  pPath->setColor( OdTvColorDef( 255, 0, 0 ) );
  pPath->addViewDependency( newViewId );

  //0.7) Camera
  OdTvEntityId cameraId = pModel->appendCamera( OD_T( "CameraForWalk" ) );
  OdTvCameraPtr pCamera = cameraId.openObjectAsCamera( OdTv::kForWrite );
  pCamera->setupCamera( originalPosition, originalTarget, originalUp );
  pCamera->setViewParameters( 7.3, 6, true );
  pCamera->setDisplayTarget( false );

  //0.8) Animation container and actions 
  OdTvAnimationContainerId containerId = pTvDb->createAnimationContainer( OD_T( "CameraWalkContainer" ) );
  OdTvAnimationContainerPtr pContainer = containerId.openObject( OdTv::kForWrite );
  //The same may be implemented using only 1 actor: whole camera, combining translation and rotation.
  //Hovewer, 2 different actors for target and position look better for demonstration purposes.
  //We will use 24 frames for the second.
  OdTvAnimationActionId positionActionId = pTvDb->createAnimationAction( OD_T( "CameraWalkPosition" ) );
  OdTvAnimationActionPtr pPositionAction = positionActionId.openObject( OdTv::kForWrite );
  pPositionAction->setNumFrames( 24 * 18 + 1 );
  pPositionAction->setFPS( 24 );
  OdTvAnimationActionId targetActionId = pTvDb->createAnimationAction( OD_T( "CameraWalkTarget" ) );
  OdTvAnimationActionPtr pTargetAction = targetActionId.openObject( OdTv::kForWrite );
  pTargetAction->setNumFrames( 24 * 18 + 1 );
  pTargetAction->setFPS( 24 );

  //Define camera walk
  //We have to calculate new target and position for each keyframe
  //and setup difference between new and original values into the corresponding action.
  //0. Initial state
  setActionPoint( pPositionAction, 0, OdTvPoint::kOrigin );
  setActionPoint( pTargetAction, 0, OdTvPoint::kOrigin );
  OdTvPoint newTarget = originalTarget;
  double targetL = ( newTarget - originalPosition ).length();

  //1. Move position to position 1, target - in the same dir, 4 sec
  OdTvVector moveDir = positions[ 1 ] - positions[ 0 ];
  setActionPoint( pPositionAction, 24 * 4, moveDir );
  setActionPoint( pTargetAction, 24 * 4, moveDir );
  newTarget = originalTarget + moveDir;

  //2. Keep position, rotate target, 4 + 1 sec = 5 sec
  setActionPoint( pPositionAction, 24 * 5, moveDir );
  moveDir = ( positions[ 2 ] - positions[ 1 ] ).normalize();
  newTarget = positions[ 1 ] + moveDir * targetL;
  setActionPoint( pTargetAction, 24 * 5, newTarget - originalTarget );
  newTarget = positions[ 1 ] + moveDir * targetL;

  //3. Move position to position 2, target - in the same dir, 5 + 4 sec = 9 sec
  moveDir = positions[ 2 ] - positions[ 0 ];
  setActionPoint( pPositionAction, 24 * 9, moveDir );
  newTarget = newTarget + (positions[ 2 ] - positions[ 1 ] );
  setActionPoint( pTargetAction, 24 * 9, newTarget - originalTarget );

  //5. Keep position, rotate target, 9 + 3 = 12 sec
  setActionPoint( pPositionAction, 24 * 12, positions[ 2 ] - positions[ 0 ] );
  newTarget = positions[ 2 ] + ( positions[ 3 ] - positions[ 2 ] ).normalize() * targetL;
  setActionPoint( pTargetAction, 24 * 12, newTarget - originalTarget );

  //6. Move target and positions to the end, 12 + 6 = 18 sec
  setActionPoint( pPositionAction, 24 * 18, positions[ 3 ] - positions[ 0 ] );
  newTarget = newTarget + ( positions[ 3 ] - positions[ 2 ] );
  setActionPoint( pTargetAction, 24 * 18, newTarget - originalTarget );

  //Finalization: create actors, put them with actions into the animation container
  OdTvSubItemPath positionActor;
  positionActor.entitiesIds().push_back( cameraId );
  positionActor.geometryDatasIds().push_back( pCamera->positionId() );
  OdTvSubItemPath targetActor;
  targetActor.entitiesIds().push_back( cameraId );
  targetActor.geometryDatasIds().push_back( pCamera->targetId() );
  pContainer->addAnimation( positionActor, positionActionId );
  pContainer->addAnimation( targetActor, targetActionId );

  //Assign original (big) view with camera.
  pCamera->assignView( originalViewId );
  return databaseId;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private methods
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OdTvVisualizeSampleModels::initSoccerFieldModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId)
{
  //Create custom line type with text
  OdTvLinetypeId ltId = OdTvVisualizeSampleModelsUtils::generateCustomLineTypeWithText(databaseId);

  //generate text style
  OdTvDatabasePtr pTvDb = databaseId.openObject();
  OdTvTextStyleId textStyle = pTvDb->createTextStyle(OD_T("kMiddleCenter"));
  {
    OdTvTextStylePtr pTextStyle = textStyle.openObject(OdTv::kForWrite);
    pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleCenter);
    pTextStyle->setTextSize(0.02);
  }

  // generate geometry
  OdGePoint3d center(0., 0., 0.);

  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId modelKeyEntityId = modelPtr->appendEntity(OD_T("Soccer field"));
  {
    OdTvEntityPtr modelKeyEntity = modelKeyEntityId.openObject(OdTv::kForWrite);

    // set the color
    modelKeyEntity->setColor(OdTvColorDef(0, 0, 255), OdTvGeometryData::kPolylines | OdTvGeometryData::kEdges | OdTvGeometryData::kText);
    
    // set line and edge weight
    modelKeyEntity->setLineWeight(OdTvLineWeightDef(2), OdTvGeometryData::kPolylines | OdTvGeometryData::kEdges);

    //1. Add title
    OdTvGeometryDataId titleEntityId = modelKeyEntity->appendSubEntity(OD_T("title"));
    {
      OdTvEntityPtr titleEntity = titleEntityId.openAsSubEntity(OdTv::kForWrite);
      titleEntity->appendText(OdTvPoint(0.0, 0.8, 0.0), OD_T("Sample Soccer Field"));

      titleEntity->setTextStyle(textStyle);
    }

    //2. Add base field
    OdTvGeometryDataId base_field_Id = modelKeyEntity->appendSubEntity(OD_T("base_field"));
    {
      OdTvEntityPtr base_field_ptr = base_field_Id.openAsSubEntity(OdTv::kForWrite);

      //add rectangle
      OdTvVisualizeSampleModelsUtils::appendRectangle(base_field_ptr, -0.75, -0.5, 0.75, 0.5, 0., false, false);

      //add line
      OdGePoint3d start(0., 0.5, 0.);    OdGePoint3d end(0., -0.5, 0.);
      base_field_ptr->appendPolyline(start, end);

      //add circle (with predefined line type)
      OdGePoint3dArray pts; pts.resize(3);
      OdTvVisualizeSampleModelsUtils::generatePointsOnCircle(pts, center, 0.2f, 1);
      base_field_ptr->appendCircle(pts[0], pts[1], pts[2]);

      //add subentity
      OdTvGeometryDataId subentityId = base_field_ptr->appendSubEntity(OD_T("text"));
      {
        OdTvEntityPtr subentity = subentityId.openAsSubEntity(OdTv::kForWrite);

        subentity->appendPolyline(OdTvPoint(-0.85, 0.5, 0.0), OdTvPoint(-0.85, 0.1, 0.0));
        subentity->appendPolyline(OdTvPoint(-0.85, -0.5, 0.0), OdTvPoint(-0.85, -0.1, 0.0));
        subentity->appendPolyline(OdTvPoint(-0.90, 0.5, 0.0), OdTvPoint(-0.80, 0.5, 0.0));
        subentity->appendPolyline(OdTvPoint(-0.90, -0.5, 0.0), OdTvPoint(-0.80, -0.5, 0.0));
        subentity->appendText(OdTvPoint(-0.85, 0.0, 0.0), OD_T("75m"));

        subentity->appendPolyline(OdTvPoint(-0.75, 0.6, 0.0), OdTvPoint(-0.1, 0.6, 0.0));
        subentity->appendPolyline(OdTvPoint(0.75, 0.6, 0.0), OdTvPoint(0.1, 0.6, 0.0));
        subentity->appendPolyline(OdTvPoint(-0.75, 0.55, 0.0), OdTvPoint(-0.75, 0.65, 0.0));
        subentity->appendPolyline(OdTvPoint(0.75, 0.55, 0.0), OdTvPoint(0.75, 0.65, 0.0));
        subentity->appendText(OdTvPoint(0.0, 0.6, 0.0), OD_T("120m"));

        subentity->setTextStyle(textStyle);
      }
    }

    //3. Add penalty areas
    OdTvGeometryDataId penalty_areas_Id = modelKeyEntity->appendSubEntity(OD_T("penalty_areas"));
    {
      OdTvEntityPtr penalty_areas_ptr = penalty_areas_Id.openAsSubEntity(OdTv::kForWrite);

      //set linetype
      penalty_areas_ptr->setLinetype(ltId, OdTvGeometryData::kEdges);
      penalty_areas_ptr->setLinetypeScale(0.05, OdTvGeometryData::kEdges);
      //set color
      penalty_areas_ptr->setColor(OdTvColorDef(0, 255, 0), OdTvGeometryData::kFaces);
      //add rectangle
      OdTvVisualizeSampleModelsUtils::appendRectangle(penalty_areas_ptr, -0.75, -0.3, -0.50, 0.3, 0.0, true, false);
      OdTvVisualizeSampleModelsUtils::appendRectangle(penalty_areas_ptr, 0.75, -0.3, 0.50, 0.3, 0.0, true, false);

      //add subentity
      OdTvGeometryDataId subentityId = penalty_areas_ptr->appendSubEntity(OD_T("text"));
      {
        OdTvEntityPtr subentity = subentityId.openAsSubEntity(OdTv::kForWrite);

        subentity->setTextStyle(textStyle);

        subentity->appendPolyline(OdTvPoint(-0.40, 0.3, 0.0), OdTvPoint(-0.40, 0.05, 0.0));
        subentity->appendPolyline(OdTvPoint(-0.40, -0.3, 0.0), OdTvPoint(-0.40, -0.05, 0.0));
        subentity->appendPolyline(OdTvPoint(-0.45, 0.3, 0.0), OdTvPoint(-0.35, 0.3, 0.0));
        subentity->appendPolyline(OdTvPoint(-0.45, -0.3, 0.0), OdTvPoint(-0.35, -0.3, 0.0));
        subentity->appendText(OdTvPoint(-0.40, 0.0, 0.0), OD_T("25m"));

        subentity->appendPolyline(OdTvPoint(-0.75, 0.4, 0.0), OdTvPoint(-0.70, 0.4, 0.0));
        subentity->appendPolyline(OdTvPoint(-0.50, 0.4, 0.0), OdTvPoint(-0.55, 0.4, 0.0));
        subentity->appendPolyline(OdTvPoint(-0.50, 0.35, 0.0), OdTvPoint(-0.50, 0.45, 0.0));
        subentity->appendText(OdTvPoint(-0.625, 0.4, 0.0), OD_T("18m"));

      }
    }

    OdTvGeometryDataId goals_Id = modelKeyEntity->appendSubEntity(OD_T("goals"));
    {
      OdTvEntityPtr goals_ptr = goals_Id.openAsSubEntity(OdTv::kForWrite);

      //add rectangle
      OdTvVisualizeSampleModelsUtils::appendRectangle(goals_ptr, -0.75, -0.15, -0.70, 0.15, 0.0, true, false);
      OdTvVisualizeSampleModelsUtils::appendRectangle(goals_ptr, 0.75, -0.15, 0.70, 0.15, 0.0, true, false);

      goals_ptr->setColor(OdTvColorDef(255, 0, 0), OdTvGeometryData::kFaces);

      //add subentity
      OdTvGeometryDataId subentityId = goals_ptr->appendSubEntity(OD_T("text"));
      {
        OdTvEntityPtr subentity = subentityId.openAsSubEntity(OdTv::kForWrite);

        subentity->setTextStyle(textStyle);

        subentity->appendPolyline(OdTvPoint(0.85, 0.15, 0.0), OdTvPoint(0.85, 0.05, 0.0));
        subentity->appendPolyline(OdTvPoint(0.85, -0.15, 0.0), OdTvPoint(0.85, -0.05, 0.0));
        subentity->appendPolyline(OdTvPoint(0.80, 0.15, 0.0), OdTvPoint(0.90, 0.15, 0.0));
        subentity->appendPolyline(OdTvPoint(0.80, -0.15, 0.0), OdTvPoint(0.90, -0.15, 0.0));
        subentity->appendText(OdTvPoint(0.85, 0.0, 0.0), OD_T("6m"));
      }
    }
  }

  return;
}

void OdTvVisualizeSampleModels::initAllEntitiesModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId, const OdString& strResourceFolder)
{
  //generate text style
  OdTvDatabasePtr pTvDb = databaseId.openObject();

  OdTvTextStyleId textStyle = pTvDb->createTextStyle(OD_T("kMiddleCenter"));
  {
    OdTvTextStylePtr pTextStyle = textStyle.openObject(OdTv::kForWrite);
    pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleCenter);
    OdString typeface = L"Verdana";
    OdInt16 charset = 0;
    OdInt16 family = 34;
    bool bold = false;
    bool italic = false;
    pTextStyle->setFont(typeface, bold, italic, charset, family);
    pTextStyle->setTextSize(0.02);
  }

  OdTvTextStyleId textStyleModern = pTvDb->createTextStyle(OD_T("kMiddleCenterModern"));
  {
    OdTvTextStylePtr pTextStyle = textStyleModern.openObject(OdTv::kForWrite);

    OdString typeface = L"Algerian";
    OdInt16 charset = 0;
    OdInt16 family = 34;
    bool bold = false;
    bool italic = false;
    pTextStyle->setFont(typeface, bold, italic, charset, family);
    pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleCenter);
    pTextStyle->setTextSize(0.02);
  }

  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId modelKeyEntityId = modelPtr->appendEntity(OD_T("All entities"));
  {
    OdTvEntityPtr modelKeyEntity = modelKeyEntityId.openObject(OdTv::kForWrite);

    //1. Add title
    OdTvGeometryDataId titleEntityId = modelKeyEntity->appendSubEntity(OD_T("title"));
    {
      OdTvEntityPtr titleEntity = titleEntityId.openAsSubEntity(OdTv::kForWrite);
      titleEntity->setColor(OdTvColorDef(128, 0, 0), OdTvGeometryData::kAll);
      titleEntity->setTextStyle(textStyle);
      titleEntity->setLineWeight(2);
      OdTvGeometryDataId title = titleEntity->appendText(OdTvPoint(0.0, .75, 0.0), OD_T("All entities"));
      title.openAsText()->setTextSize(0.04);
    }

    //2. Add grid lines
    OdTvVisualizeSampleModelsUtils::appendGridLines(modelKeyEntity, false, 3, 6, -1., 0.66, 0.66, 0.33);

    double x0 = -0.66, x1 = 0., x2 = 0.66;
    double y0 = 0.5;
    double txtY = 0.14;

    // row 1 line, nurbs, circle
    {
      OdTvGeometryDataId geom_txt = modelKeyEntity->appendSubEntity(OD_T("row_1_txt"));
      {
        OdTvEntityPtr pTxtEntity = geom_txt.openAsSubEntity(OdTv::kForWrite);
        pTxtEntity->appendText(OdTvPoint(x0, y0 + txtY, 0.), "Polyline");
        pTxtEntity->appendText(OdTvPoint(x1, y0 + txtY, 0.), "Nurbs");
        pTxtEntity->appendText(OdTvPoint(x2, y0 + txtY, 0.), "Circle");
        pTxtEntity->setTextStyle(textStyle);
      }

      OdTvGeometryDataId geom_line = modelKeyEntity->appendSubEntity(OD_T("line"));
      {
        geom_line.openObject()->setLineWeight(2);

        OdTvEntityPtr pGeomEntity = geom_line.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity->setColor(OdTvColorDef(255, 0, 0));
        pGeomEntity->appendPolyline(OdTvPoint(x0 - 0.3, y0 - 0.15, 0.), OdTvPoint(x0 - 0.25, y0 + 0.1, 0.));
        pGeomEntity->appendPolyline(OdTvPoint(x0 - 0.25, y0 + 0.1, 0.), OdTvPoint(x0 - 0.2, y0 - 0.15, 0.));
        pGeomEntity->appendPolyline(OdTvPoint(x0 - 0.2, y0 - 0.15, 0.), OdTvPoint(x0 - 0.15, y0 + 0.1, 0.));
        pGeomEntity->appendPolyline(OdTvPoint(x0 - 0.15, y0 + 0.1, 0.), OdTvPoint(x0 - 0.1, y0 - 0.15, 0.));
        pGeomEntity->appendPolyline(OdTvPoint(x0 - 0.1, y0 - 0.15, 0.), OdTvPoint(x0 - 0.05, y0 + 0.1, 0.));
        pGeomEntity->appendPolyline(OdTvPoint(x0 - 0.05, y0 + 0.1, 0.), OdTvPoint(x0, y0 - 0.15, 0.));
        pGeomEntity->appendPolyline(OdTvPoint(x0, y0 - 0.15, 0.), OdTvPoint(x0 + 0.05, y0 + 0.1, 0.));
        pGeomEntity->appendPolyline(OdTvPoint(x0 + 0.05, y0 + 0.1, 0.), OdTvPoint(x0 + 0.1, y0 - 0.15, 0.));
        pGeomEntity->appendPolyline(OdTvPoint(x0 + 0.1, y0 - 0.15, 0.), OdTvPoint(x0 + 0.15, y0 + 0.1, 0.));
        pGeomEntity->appendPolyline(OdTvPoint(x0 + 0.15, y0 + 0.1, 0.), OdTvPoint(x0 + 0.2, y0 - 0.15, 0.));
        pGeomEntity->appendPolyline(OdTvPoint(x0 + 0.2, y0 - 0.15, 0.), OdTvPoint(x0 + 0.25, y0 + 0.1, 0.));
        pGeomEntity->appendPolyline(OdTvPoint(x0 + 0.25, y0 + 0.1, 0.), OdTvPoint(x0 + 0.3, y0 - 0.15, 0.));
      }

      OdTvGeometryDataId geom_nurbs = modelKeyEntity->appendSubEntity(OD_T("nurbs"));
      {
        geom_nurbs.openObject()->setLineWeight(2);

        OdTvEntityPtr pGeomEntity = geom_nurbs.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity->setColor(OdTvColorDef(0, 255, 0));
        OdTvPointArray points;
        points.append(OdTvPoint(x1 - 0.3, y0 - y0 / 4, 0.));
        points.append(OdTvPoint(x1 - 0.15, y0 + y0 / 4, 0.));
        points.append(OdTvPoint(x1 + 0.15, y0 - y0 / 4, 0.));
        points.append(OdTvPoint(x1 + 0.3, y0 + y0 / 4, 0.));
        OdDoubleArray weightArr;
        weightArr.append(1.);
        weightArr.append(1.);
        weightArr.append(1.);
        weightArr.append(1.);

        OdDoubleArray knotsArr;
        knotsArr.append(0.);
        knotsArr.append(0.);
        knotsArr.append(0.);
        knotsArr.append(0.);
        knotsArr.append(1.);
        knotsArr.append(1.);
        knotsArr.append(1.);
        knotsArr.append(1.);

        pGeomEntity->appendNurbs(3, points, weightArr, knotsArr);
      }

      OdTvGeometryDataId geom_circle = modelKeyEntity->appendSubEntity(OD_T("circle"));
      {
        geom_circle.openObject()->setLineWeight(2);
        OdTvEntityPtr pGeomEntity = geom_circle.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity->setColor(OdTvColorDef(0, 0, 255));
        pGeomEntity->appendCircle(OdTvPoint(x2, y0, 0.), 0.12, OdTvVector(0, 0, 1));
      }
    }
    y0 -= 0.33;
    // row 2 circle arc, ellipse, ellipArc
    {
      OdTvGeometryDataId geom_txt = modelKeyEntity->appendSubEntity(OD_T("row_2_txt"));
      {
        OdTvEntityPtr pTxtEntity = geom_txt.openAsSubEntity(OdTv::kForWrite);
        pTxtEntity->appendText(OdTvPoint(x0, y0 + txtY, 0.), "Circle arc");
        pTxtEntity->appendText(OdTvPoint(x1, y0 + txtY, 0.), "Ellipse");
        pTxtEntity->appendText(OdTvPoint(x2, y0 + txtY, 0.), "Elliptic arc");
        pTxtEntity->setTextStyle(textStyle);
      }

      OdTvGeometryDataId geom_circArc = modelKeyEntity->appendSubEntity(OD_T("circArc"));
      {
        geom_circArc.openObject()->setLineWeight(2);

        OdTvEntityPtr pGeomEntity = geom_circArc.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity->setColor(OdTvColorDef(204, 153, 255));
        pGeomEntity->appendCircleArc(OdTvPoint(x0 - 0.25, y0 + 0.1, 0.), OdTvPoint(x0, y0 - 0.15, 0.), OdTvPoint(x0 + 0.25, y0 + 0.1, 0.));
      }

      OdTvGeometryDataId geom_ellipse = modelKeyEntity->appendSubEntity(OD_T("ellipse"));
      {
        geom_ellipse.openObject()->setLineWeight(2);

        OdTvEntityPtr pGeomEntity = geom_ellipse.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity->setColor(OdTvColorDef(204, 102, 0));
        OdTvLinetypeId ltId = OdTvVisualizeSampleModelsUtils::generateCustomLineTypeWithText(databaseId);
        pGeomEntity->setLinetype(ltId, OdTvGeometryData::kEdges);
        pGeomEntity->setLinetypeScale(0.05, OdTvGeometryData::kEdges);
        pGeomEntity->appendEllipse(OdTvPoint(x1, y0 - 0.03, 0.), OdTvPoint(x1 + 0.3, y0 - 0.03, 0.), OdTvPoint(x1, y0 + 0.08, 0.));
      }

      OdTvGeometryDataId geom_ellipArc = modelKeyEntity->appendSubEntity(OD_T("ellipArc"));
      {
        geom_ellipArc.openObject()->setLineWeight(2);
        OdTvEntityPtr pGeomEntity = geom_ellipArc.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity->setColor(OdTvColorDef(204, 55, 143));
        pGeomEntity->appendEllipticArc(OdTvPoint(x2, y0 - 0.03, 0.), OdTvPoint(x2 + 0.3, y0 - 0.03, 0.), OdTvPoint(x2, y0 + 0.08, 0.), 0, 60);
      }
    }
    y0 -= 0.33;
    // row 3 wedge, sphere, cylinder
    {
      OdTvGeometryDataId geom_txt = modelKeyEntity->appendSubEntity(OD_T("row_3_txt"));
      {
        OdTvEntityPtr pTxtEntity = geom_txt.openAsSubEntity(OdTv::kForWrite);
        pTxtEntity->appendText(OdTvPoint(x0, y0 + txtY, 0.), "Wedge");
        pTxtEntity->appendText(OdTvPoint(x1, y0 + txtY, 0.), "Sphere");
        pTxtEntity->appendText(OdTvPoint(x2, y0 + txtY, 0.), "Cylinder");
        pTxtEntity->setTextStyle(textStyle);
      }

      OdTvGeometryDataId geom_wedge = modelKeyEntity->appendSubEntity(OD_T("wedge"));
      {
        geom_wedge.openObject()->setLineWeight(2);

        OdTvEntityPtr pGeomEntity = geom_wedge.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity->setColor(OdTvColorDef(102, 0, 204));
        pGeomEntity->appendCircleWedge(OdTvPoint(x0 - 0.2, y0 + 0.1, 0.), OdTvPoint(x0, y0 - 0.15, 0.), OdTvPoint(x0 + 0.2, y0 + 0.1, 0.));
      }

      OdTvGeometryDataId geom_sphere = modelKeyEntity->appendSubEntity(OD_T("sphere"));
      {
        geom_sphere.openObject()->setLineWeight(2);

        OdTvEntityPtr pGeomEntity = geom_sphere.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity->setColor(OdTvColorDef(153, 0, 0));
        pGeomEntity->appendSphere(OdTvPoint(x1, y0 - 0.03, 0.), 0.12, OdTvVector(0, 0, 1));
      }

      OdTvGeometryDataId geom_cylinder = modelKeyEntity->appendSubEntity(OD_T("cylinder"));
      {
        geom_cylinder.openObject()->setLineWeight(2);
        OdTvEntityPtr pGeomEntity = geom_cylinder.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity->setColor(OdTvColorDef(0, 255, 255));
        pGeomEntity->appendCylinder(OdTvPoint(x2 - 0.15, y0 - 0.07, 0.), OdTvPoint(x2 + 0.17, y0 - 0.03, 0.), 0.07, OdTvCylinderData::kSecond);

        //add transformation matrix for the good initial view
        OdTvMatrix matr;
        OdGeMatrix3d rotationMatX;
        rotationMatX.setToRotation(-OdaPI4 * 1.2, OdGeVector3d::kXAxis, OdTvPoint(x2, y0, 0.));
        OdGeMatrix3d rotationMatY;
        rotationMatY.setToRotation(-OdaPI4, OdGeVector3d::kYAxis, OdTvPoint(x2, y0, 0.));
        OdGeMatrix3d rotationMatZ;
        rotationMatZ.setToRotation(OdaPI4, OdGeVector3d::kZAxis, OdTvPoint(x2, y0, 0.));
        matr = rotationMatX * /** rotationMatY */ rotationMatZ;

        geom_cylinder.openObject()->setModelingMatrix(matr);
      }
    }
    y0 -= 0.33;
    // row 3 mesh, shell, cylinder
    {
      OdTvGeometryDataId geom_txt = modelKeyEntity->appendSubEntity(OD_T("row_4_txt"));
      {
        OdTvEntityPtr pTxtEntity = geom_txt.openAsSubEntity(OdTv::kForWrite);
        pTxtEntity->appendText(OdTvPoint(x0, y0 + txtY, 0.), "Mesh");
        pTxtEntity->appendText(OdTvPoint(x1, y0 + txtY, 0.), "Shell");
        pTxtEntity->appendText(OdTvPoint(x2, y0 + txtY, 0.), "Polycylinder");
        pTxtEntity->setTextStyle(textStyle);
      }

      OdTvGeometryDataId geom_mesh = modelKeyEntity->appendSubEntity(OD_T("mesh"));
      {
        OdTvEntityPtr pGeomEntity = geom_mesh.openAsSubEntity(OdTv::kForWrite);
        //3. Define initial parameters for the mesh model
        OdTvPoint pointXYZ = OdTvPoint(x0 - 0.2, y0 - 0.15, -0.06), pointXY = OdTvPoint(x0 + 0.2, y0 + 0.15, pointXYZ.z), pointXZ = OdTvPoint(pointXYZ.x, pointXYZ.y, 0.06);

        double startXMark = 1., startYMark = 0., startZMark = -2.;
        double endXMark = 10., endYMark = 20., endZMark = 2.;

        OdTvPoint zeroPoint(pointXYZ.x - fabs(OdTvVisualizeSampleModelsUtils::getLinInterCoef(endXMark, startXMark, pointXYZ.x, pointXY.x)), pointXYZ.y, OdTvVisualizeSampleModelsUtils::mediana(pointXZ.z, pointXYZ.z));

        double startX = 1., endX = 10., startY = 0., endY = 20.;
        OdUInt32 nDiv = 30;

        OdTvVisualizeSampleModelsUtils::append3dPlot(pGeomEntity, startX, endX, startY, endY, startXMark, startYMark, startZMark, endXMark, endYMark, endZMark, nDiv,
                                                     pointXYZ, pointXY, pointXZ, &SinPlusCos);

        //add transformation matrix for the good initial view
        OdTvMatrix matr;
        OdGeMatrix3d rotationMatX;
        rotationMatX.setToRotation(-OdaPI4 * 1.2, OdGeVector3d::kXAxis, OdTvPoint(x0 + 0.03, y0 - 0.05, 0.));
        OdGeMatrix3d rotationMatZ;
        rotationMatZ.setToRotation(OdaPI4, OdGeVector3d::kZAxis, OdTvPoint(x0 + 0.03, y0 - 0.05, 0.));
        matr = rotationMatX * rotationMatZ;

        geom_mesh.openObject()->setModelingMatrix(matr);
      }

      OdTvGeometryDataId geom_shell = modelKeyEntity->appendSubEntity(OD_T("shell"));
      {
        geom_shell.openObject()->setLineWeight(1);

        OdTvEntityPtr pGeomEntity = geom_shell.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity->setColor(OdTvColorDef(0, 0, 150));
        OdTvPointArray points;
        OdInt32Array faces;
        double z = 0.3;
        OdInt32 cntOfEdges = 10;
        double newZ = z / cntOfEdges;
        for (int i = 0; i < cntOfEdges; i++)
        {
          newZ = i * z / cntOfEdges;
          points.append(OdTvPoint(x1 - 0.2, y0 - 0.15, z / 2 - newZ));
        }

        double newX = 0.4 / cntOfEdges;
        for (int i = 0; i < cntOfEdges; i++)
        {
          newX = i * 0.4 / cntOfEdges;
          points.append(OdTvPoint(x1 - 0.2 + newX, y0 - 0.15, -z / 2));
        }

        newZ = z / cntOfEdges;
        for (int i = 0; i < cntOfEdges; i++)
        {
          newZ = i * z / cntOfEdges;
          points.append(OdTvPoint(x1 + 0.2, y0 - 0.15, -z / 2 + newZ));
        }

        newX = 0.4 / 10;
        for (int i = 0; i < cntOfEdges; i++)
        {
          newX = i * 0.4 / cntOfEdges;
          points.append(OdTvPoint(x1 + 0.2 - newX, y0 - 0.15, z / 2));
        }

        points.append(OdTvPoint(x1, y0 + 0.12, 0.));

        OdInt32 last = points.size() - 1;
        for (int i = 0; i < last; i++)
        {
          faces.append(3);
          faces.append(i);
          faces.append(last);
          faces.append(i + 1);
        }
        // fill last triangle
        faces.append(3);
        faces.append(last - 1);
        faces.append(last);
        faces.append(0);

        pGeomEntity->appendShell(points, faces);
      }

      OdTvGeometryDataId geom_polycylinder = modelKeyEntity->appendSubEntity(OD_T("polycylinder"));
      {
        geom_polycylinder.openObject()->setLineWeight(2);
        OdTvEntityPtr pGeomEntity = geom_polycylinder.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity->setColor(OdTvColorDef(51, 153, 255));

        OdTvPointArray vertices;
        vertices.append(OdTvPoint(x2, y0 + 0.1, 0.));
        vertices.append(OdTvPoint(x2, y0 + 0.07, 0.));
        vertices.append(OdTvPoint(x2, y0 - 0.01, 0.));
        vertices.append(OdTvPoint(x2, y0 - 0.11, 0.));
        vertices.append(OdTvPoint(x2, y0 - 0.14, 0.));
        OdDoubleArray radii;
        radii.append(0.08);
        radii.append(0.05);
        radii.append(0.055);
        radii.append(0.05);
        radii.append(0.08);

        pGeomEntity->appendCylinder(vertices, radii, OdTvCylinderData::kBoth);

        //add transformation matrix for the good initial view
        OdTvMatrix matr;
        OdGeMatrix3d rotationMatX;
        rotationMatX.setToRotation(-OdaPI4, OdGeVector3d::kXAxis, OdTvPoint(x2, y0, 0.));
        OdGeMatrix3d rotationMatZ;
        rotationMatZ.setToRotation(-OdaPI4, OdGeVector3d::kZAxis, OdTvPoint(x2, y0, 0.));
        matr = rotationMatX * rotationMatZ;

        geom_polycylinder.openObject()->setModelingMatrix(matr);
      }
    }

    y0 -= 0.33;
    // row 5 image, text, cylinder(cone)
    {
      OdTvGeometryDataId geom_txt = modelKeyEntity->appendSubEntity(OD_T("row_5_txt"));
      {
        OdTvEntityPtr pTxtEntity = geom_txt.openAsSubEntity(OdTv::kForWrite);
        pTxtEntity->appendText(OdTvPoint(x0, y0 + txtY, 0.), "Image");
        pTxtEntity->appendText(OdTvPoint(x1, y0 + txtY, 0.), "Text");
        pTxtEntity->appendText(OdTvPoint(x2, y0 + txtY, 0.), "Polygon");
        pTxtEntity->setTextStyle(textStyle);
      }

      OdTvGeometryDataId geom_image = modelKeyEntity->appendSubEntity(OD_T("image"));
      {
        OdTvEntityPtr pGeomEntity = geom_image.openAsSubEntity(OdTv::kForWrite);
        OdString imagePath = strResourceFolder + OD_T("oda.png");
        OdTvRasterImageId imgId = databaseId.openObject(OdTv::kForWrite)->createRasterImage(OdString("logo").c_str(), imagePath.c_str(), true);

        pGeomEntity->appendRasterImage(imgId, OdTvPoint(x0 - 0.12, y0 - 0.15, 0.), OdTvVector(0.26, 0., 0.), OdTvVector(0., 0.26, 0.));
      }

      OdTvGeometryDataId geom_text = modelKeyEntity->appendSubEntity(OD_T("text"));
      {
        OdTvEntityPtr pTxtEntity = geom_text.openAsSubEntity(OdTv::kForWrite);
        pTxtEntity->setColor(OdTvColorDef(51, 0, 102));
        pTxtEntity->setTextStyle(textStyleModern);
        OdTvGeometryDataId openTxt = pTxtEntity->appendText(OdTvPoint(x1, y0 + 0.06, 0.), "Open");
        openTxt.openAsText()->setTextSize(0.04);
        OdTvGeometryDataId designTxt = pTxtEntity->appendText(OdTvPoint(x1, y0 - 0.01, 0.), "Design");
        designTxt.openAsText()->setTextSize(0.04);
        OdTvGeometryDataId allianceTxt = pTxtEntity->appendText(OdTvPoint(x1, y0 - 0.07, 0.), "Alliance");
        allianceTxt.openAsText()->setTextSize(0.04);

      }

      OdTvGeometryDataId geom_polygon = modelKeyEntity->appendSubEntity(OD_T("polygon"));
      {
        OdTvEntityPtr pGeomEntity = geom_polygon.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity->setColor(OdTvColorDef(0, 0, 139), OdTvGeometryData::kFaces);
        pGeomEntity->setColor(OdTvColorDef(179, 0, 0), OdTvGeometryData::kEdges);
        pGeomEntity->setLineWeight(4);
        OdTvPointArray points;
        points.append(OdTvPoint(x2 - 0.25, y0 - 0.0875, 0.));
        points.append(OdTvPoint(x2 - 0.25, y0 + 0.0375, 0.));
        points.append(OdTvPoint(x2, y0 + 0.1, 0.));
        points.append(OdTvPoint(x2 + 0.25, y0 + 0.0375, 0.));
        points.append(OdTvPoint(x2 + 0.25, y0 - 0.0875, 0.));
        points.append(OdTvPoint(x2, y0 - 0.15, 0.));

        OdTvGeometryDataId polygonId = pGeomEntity->appendPolygon(points);
        polygonId.openAsPolygon()->setFilled(true);
      }
    }

    y0 -= 0.33;
    // row 6 grid, //text, cylinder(cone)
    {
      OdTvGeometryDataId geom_txt = modelKeyEntity->appendSubEntity(OD_T("row_6_txt"));
      {
        OdTvEntityPtr pTxtEntity = geom_txt.openAsSubEntity(OdTv::kForWrite);
        pTxtEntity->appendText(OdTvPoint(x0, y0 + txtY, 0.), "Grid");
        pTxtEntity->setTextStyle(textStyle);
      }

      OdTvGeometryDataId geom_image = modelKeyEntity->appendSubEntity(OD_T("grid"));
      {
        OdTvEntityPtr pGeomEntity = geom_image.openAsSubEntity(OdTv::kForWrite);

        pGeomEntity->appendGrid(OdTvPoint(x0, y0 - 0.02, 0.), OdTvPoint(0.049, 0., 0.), OdTvPoint(0., 1., 0.), 3, 6, OdTvGridData::kRadial);
        pGeomEntity->setColor(OdTvColorDef(194, 194, 255));
      }
    }
  }
}

void OdTvVisualizeSampleModels::initPlotModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId)
{
  //generate text style
  OdTvDatabasePtr pTvDb = databaseId.openObject();
  OdTvTextStyleId textStyle = pTvDb->createTextStyle(OD_T("kMiddleCenter"));
  {
    OdTvTextStylePtr pTextStyle = textStyle.openObject(OdTv::kForWrite);
    pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleCenter);
    pTextStyle->setTextSize(0.02);
  }
  OdTvTextStyleId textStyle1 = pTvDb->createTextStyle(OD_T("kBottomCenter"));
  {
    OdTvTextStylePtr pTextStyle = textStyle1.openObject(OdTv::kForWrite);
    pTextStyle->setAlignmentMode(OdTvTextStyle::kBottomCenter);
    pTextStyle->setTextSize(0.02);
  }

  OdTvPoint topLeft = OdTvPoint(-0.75, 0.5, 0), bottomRight = OdTvPoint(0.75, -0.5, 0);

  OdUInt32 xNum = 9, yNum = 11;
  double startXMark = -8., startYMark = -1.;
  double endXMark = 8., endYMark = 1.;
  double startX = -6., endX = 6;
  OdUInt32 nDiv = 100;

  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);

  //1. Add title
  OdTvEntityId titleEntityId = modelPtr->appendEntity(OD_T("title"));
  {
    OdTvEntityPtr titleEntity = titleEntityId.openObject(OdTv::kForWrite);
    titleEntity->setLineWeight(2);
    titleEntity->setTextStyle(textStyle);

    titleEntity->appendText(OdTvPoint(0.0, .55, 0.0), OD_T("Sin vs Cos"));
  }

  OdTvEntityId geometries_entity_Id_rectangle = modelPtr->appendEntity(OD_T("rectangle_column_txt"));
  {
    OdTvEntityPtr pRectEntityPtr = geometries_entity_Id_rectangle.openObject(OdTv::kForWrite);
    OdTvVisualizeSampleModelsUtils::appendRectangle(pRectEntityPtr, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
  }

  //2. X and Y axis
  OdTvEntityId geometries_entity_Id_axis = modelPtr->appendEntity(OD_T("axis"));
  {
    OdTvEntityPtr pGraphEntity = geometries_entity_Id_axis.openObject(OdTv::kForWrite);
    pGraphEntity->setTextStyle(textStyle1);
    OdTvVisualizeSampleModelsUtils::append2dGraphAxis(pGraphEntity, startXMark, endXMark, startYMark, endYMark, xNum, yNum, topLeft, bottomRight);
  }

  //3. Draw sin
  OdTvEntityId geometries_entity_Id_sin = modelPtr->appendEntity(OD_T("sin"));
  {
    OdTvEntityPtr pGraphEntity = geometries_entity_Id_sin.openObject(OdTv::kForWrite);
    pGraphEntity->setColor(OdTvColorDef(255, 0, 0));

    OdTvVisualizeSampleModelsUtils::append2dPlot(pGraphEntity, startX, endX, startXMark, startYMark, endXMark, endYMark, nDiv, topLeft, bottomRight, &sin);
  }

  //4. Draw cos
  OdTvEntityId geometries_entity_Id_cos = modelPtr->appendEntity(OD_T("cos"));
  {
    OdTvEntityPtr pGraphEntity = geometries_entity_Id_cos.openObject(OdTv::kForWrite);
    pGraphEntity->setColor(OdTvColorDef(0, 0, 255));

    OdTvVisualizeSampleModelsUtils::append2dPlot(pGraphEntity, startX, endX, startXMark, startYMark, endXMark, endYMark, nDiv, topLeft, bottomRight, &cos);
  }
}

void OdTvVisualizeSampleModels::initSurfPlotOtherModel(OdTvDatabaseId& databaseId, OdTvModelId& tvSecondModelId, OdTvModelId& tvThirdModelId)
{
  //generate text style
  OdTvDatabasePtr pTvDb = databaseId.openObject();
  OdTvTextStyleId textStyle = pTvDb->createTextStyle(OD_T("kMiddleCenter"));
  {
    OdTvTextStylePtr pTextStyle = textStyle.openObject(OdTv::kForWrite);

    OdString typeface = L"Algerian";
    OdInt16 charset = 0;
    OdInt16 family = 34;
    bool bold = false;
    bool italic = false;
    pTextStyle->setFont(typeface, bold, italic, charset, family);
    pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleCenter);
    pTextStyle->setTextSize(0.02);
  }

  // 1. fill title model.
  OdTvModelPtr pThirdModel = tvThirdModelId.openObject(OdTv::kForWrite);

  //1.1 Add title
  OdTvEntityId titleId = pThirdModel->appendEntity(OD_T("Title"));
  {
    OdTvEntityPtr pTitle = titleId.openObject(OdTv::kForWrite);
    pTitle->setColor(OdTvColorDef(0, 0, 0));
    pTitle->setTextStyle(textStyle);
    pTitle->appendText(OdTvPoint(0.0, 0., 0.0), OD_T("Z = sin(X) + cos(Y)"));
  }

  // 2. fill color bar model.
  OdTvModelPtr pSecondModel = tvSecondModelId.openObject(OdTv::kForWrite);

  //2.1 Add temperature legend
  OdTvEntityId labelId = pSecondModel->appendEntity(OD_T("ColorBar"));
  {
    OdTvEntityPtr pLabel = labelId.openObject(OdTv::kForWrite);
    OdTvVisualizeSampleModelsUtils::appendColoredLegend(databaseId, pLabel, OD_T(""), 0.01, -0.5, 0.06, 0.5, 2., -2., 8);
  }
}

 void OdTvVisualizeSampleModels::initSurfPlotModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId)
 {
   // 1. Fill main model. This model will contain mesh with (sin(x) + cos(y)) field
   OdTvModelPtr pModel = modelId.openObject(OdTv::kForWrite);
 
   //2. Define initial parameters for the mesh model
   OdTvPoint pointXYZ = OdTvPoint(-0.75, -0.75, -0.5), pointXY = OdTvPoint(0.75, 0.75, pointXYZ.z), pointXZ = OdTvPoint(pointXYZ.x, pointXYZ.y, 0.5);
 
   OdUInt32 xNum = 10, yNum = 5, zNum = 9;
   double startXMark = 1., startYMark = 0., startZMark = -2.;
   double endXMark = 10., endYMark = 20., endZMark = 2.;
   double startX = 2., endX = 10., startY = 1., endY = 20.;
   OdUInt32 nDiv = 70;

   // 3. Add surface
   OdTvEntityId surfaceId = pModel->appendEntity(OD_T("Surface"));
   {
     OdTvEntityPtr pGraphEntity = surfaceId.openObject(OdTv::kForWrite);
 
     OdTvVisualizeSampleModelsUtils::append3dPlot(pGraphEntity, startX, endX, startY, endY, startXMark, startYMark, startZMark, endXMark, endYMark, endZMark, nDiv,
                                                  pointXYZ, pointXY, pointXZ, &SinPlusCos);
   }
 }

void OdTvVisualizeSampleModels::initCylinderTemperatureModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId, OdTvModelId& tvSecondModelId, OdTvModelId& tvThirdModelId)
{
  // generate text style
  OdTvDatabasePtr pTvDb = databaseId.openObject();
  OdTvTextStyleId textStyle = pTvDb->createTextStyle(OD_T("kMiddleCenter"));
  {
    OdTvTextStylePtr pTextStyle = textStyle.openObject(OdTv::kForWrite);

    OdString typeface = L"Algerian";
    OdInt16 charset = 0;
    OdInt16 family = 34;
    bool bold = false;
    bool italic = false;
    pTextStyle->setFont(typeface, bold, italic, charset, family);

    pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleCenter);
    pTextStyle->setTextSize(0.02);
  }

  // 1. fill title model.
  OdTvModelPtr pThirdModel = tvThirdModelId.openObject(OdTv::kForWrite);

  //1.1 Add title
  OdTvEntityId titleId = pThirdModel->appendEntity(OD_T("Title"));
  {
    OdTvEntityPtr pTitle = titleId.openObject(OdTv::kForWrite);
    pTitle->setColor(OdTvColorDef(0, 0, 0));
    pTitle->setTextStyle(textStyle);
    pTitle->appendText(OdTvPoint(0.0, 0.0, 0.0), OD_T("Temperature distribution at the shaft in the case of the Morton effect"));
  }

  // 2. fill color bar model.
  OdTvModelPtr pSecondModel = tvSecondModelId.openObject(OdTv::kForWrite);

  //2.1 Add temperature legend
  OdTvEntityId labelId = pSecondModel->appendEntity(OD_T("ColorBar"));
  {
    OdTvEntityPtr pLabel = labelId.openObject(OdTv::kForWrite);
    OdTvVisualizeSampleModelsUtils::appendColoredLegend(databaseId, pLabel, OD_T("Temperature (C)"), 0.01, -0.5, 0.06, 0.5, 30., 20, 10);
  }

  // 2. fill main model. This model will contain cylinder with temperature field at the surface
  OdTvModelPtr pFirstModel = modelId.openObject(OdTv::kForWrite);

  //2.1 Add cylinder
  OdTvEntityId cylinderId = pFirstModel->appendEntity(OD_T("Cylinder"));
  {
    OdTvEntityPtr pCylinder = cylinderId.openObject(OdTv::kForWrite);
    OdTvVisualizeSampleModelsUtils::appendSampleColoredCylinder(pCylinder, -0.5, 0.5, 0.1, 30., 20);
  }

  return;
}

void OdTvVisualizeSampleModels::initSwordModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId, const OdString& strResourceFolder)
{
  //generate text style
  OdTvDatabasePtr pTvDb = databaseId.openObject();
  OdTvTextStyleId textStyle = pTvDb->createTextStyle(OD_T("kMiddleCenter"));
  {
    OdTvTextStylePtr pTextStyle = textStyle.openObject(OdTv::kForWrite);
    pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleCenter);
    pTextStyle->setTextSize(0.02);
  }

  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId modelKeyEntityId = modelPtr->appendEntity(OD_T("Layers"));
  {
    OdTvEntityPtr modelKeyEntity = modelKeyEntityId.openObject(OdTv::kForWrite);

    //1. Add title
    OdTvGeometryDataId titleEntityId = modelKeyEntity->appendSubEntity(OD_T("title"));
    {
      OdTvEntityPtr titleEntity = titleEntityId.openAsSubEntity(OdTv::kForWrite);
      titleEntity->setColor(OdTvColorDef(128, 000, 128), OdTvGeometryData::kAll);
      titleEntity->setLineWeight(2);
      titleEntity->setTextStyle(textStyle);

      titleEntity->appendText(OdTvPoint(0.0, 0.2, 0.0), OD_T("Sword example"));
    }

    //2. Sword example
    double xS = 0., yS = 0.;
    OdTvGeometryDataId entitySword_Id = modelKeyEntity->appendSubEntity(OD_T("Sword"));
    {
      OdTvEntityPtr pSwordEntity = entitySword_Id.openAsSubEntity(OdTv::kForWrite);

      //2.1 Blade
      // Create path to texture image file
      OdString metalTexturePath = OdTvVisualizeSampleModelsUtils::formatPath(strResourceFolder, OD_T("textures/metal.jpg"));

      // Create material map and set texture
      OdTvMaterialMap materialMap;
      materialMap.setSourceFileName(metalTexturePath);

      // Create material and open it. Material must have unique name.
      OdTvMaterialId bladeMaterialId = pTvDb->createMaterial(OD_T("BladeMaterial"));
      OdTvMaterialPtr pBladeMaterial = bladeMaterialId.openObject(OdTv::kForWrite);
      pBladeMaterial->setDiffuse(OdTvMaterialColor(OdTvColorDef(0, 0, 0)), materialMap);
      pBladeMaterial->setSpecular(OdTvMaterialColor(OdTvColorDef(255, 255, 255)), 0.5);

      OdTvPointArray bladeVertices0;
      OdTvPointArray bladeVertices1;
      OdInt32Array bladeFaces0;
      OdTvPoint2dArray bladeVerticesCoords;

      // Get vertices, faces list and mapping coordinates 
      OdTvVisualizeSampleModelsUtils::generateBlade(bladeVertices0, bladeVertices1, bladeFaces0, bladeVerticesCoords, xS, yS);

      // Draw shell and set material to faces using mapping coordinates
      OdTvGeometryDataId bladeId0 = pSwordEntity->appendShell(bladeVertices0, bladeFaces0);
      OdTvShellDataPtr pBlade0 = bladeId0.openAsShell();
      pBlade0->setFaceMaterialsViaRange(0, pBlade0->getFacesCount(), bladeMaterialId);
      pBlade0->setVertexMappingCoordsViaRange(0, bladeVerticesCoords);

      OdTvGeometryDataId bladeId1 = pSwordEntity->appendShell(bladeVertices1, bladeFaces0);
      OdTvShellDataPtr pBlade1 = bladeId1.openAsShell();
      pBlade1->setFaceMaterialsViaRange(0, pBlade1->getFacesCount(), bladeMaterialId);
      pBlade1->setVertexMappingCoordsViaRange(0, bladeVerticesCoords);

      //2.2 Guard
      // Create material and open it
      OdTvMaterialId guardMaterialId = pTvDb->createMaterial(OD_T("GuardMaterial"));
      OdTvMaterialPtr pGuardMaterial = guardMaterialId.openObject(OdTv::kForWrite);
      pGuardMaterial->setSpecular(OdTvMaterialColor(OdTvColorDef(5, 5, 5)), 0.5);

      OdTvPointArray guardVertices;
      OdInt32Array guardFaces;

      // Get vertices and faces list
      OdTvVisualizeSampleModelsUtils::generateGuard(guardVertices, guardFaces, xS, yS);

      // Draw shell and set material
      OdTvGeometryDataId guardId = pSwordEntity->appendShell(guardVertices, guardFaces);
      OdTvShellDataPtr pGuard = guardId.openAsShell();
      pGuard->setFaceColorsViaRange(0, pGuard->getFacesCount(), OdTvColorDef(125, 125, 125));
      pGuard->setFaceMaterialsViaRange(0, pGuard->getFacesCount(), guardMaterialId);

      //2.3 Handle
      OdTvPointArray handleVertices;
      OdInt32Array handleFaces;
      OdTvPoint2dArray handleVerticesCoords;

      // Get vertices, faces list and mapping coordinates 
      OdTvVisualizeSampleModelsUtils::generateHandle(handleVertices, handleFaces, handleVerticesCoords, xS, yS);

      // Create path to texture image file
      OdString handleTexturePath = OdTvVisualizeSampleModelsUtils::formatPath(strResourceFolder, OD_T("textures/handle.jpg"));

      // Create material map and set texture
      OdTvMaterialMap handleMap;
      handleMap.setSourceFileName(handleTexturePath);

      // Create material and open it
      OdTvMaterialId handleMaterialId = pTvDb->createMaterial(OD_T("HandleMaterial"));
      OdTvMaterialPtr pHandleMaterial = handleMaterialId.openObject(OdTv::kForWrite);
      pHandleMaterial->setDiffuse(OdTvMaterialColor(OdTvColorDef(0, 0, 0)), handleMap);

      OdTvGeometryDataId handleId = pSwordEntity->appendShell(handleVertices, handleFaces);
      OdTvShellDataPtr pHandle = handleId.openAsShell();
      pHandle->setFaceMaterialsViaRange(0, pHandle->getFacesCount(), handleMaterialId);
      pHandle->setVertexMappingCoordsViaRange(0, handleVerticesCoords);

      //2.4 Apple
      // Create material and open it
      OdTvMaterialId appleMaterialId = pTvDb->createMaterial(OD_T("AppelMaterial"));
      OdTvMaterialPtr pAppleMaterial = appleMaterialId.openObject(OdTv::kForWrite);
      pAppleMaterial->setSpecular(OdTvMaterialColor(OdTvColorDef(0, 255, 0)), 0.5);
      pAppleMaterial->setOpacity(0.5);

      // Draw shell and set material
      OdTvGeometryDataId appleId = pSwordEntity->appendShellFromSphere(OdTvPoint(xS, yS + 0.15, 0.), 0.03, OdTvVector::kYAxis, OdTvVector::kXAxis, 250);
      OdTvShellDataPtr pApple = appleId.openAsShell();
      pApple->setFaceColorsViaRange(0, pApple->getFacesCount() / 4, OdTvColorDef(255, 0, 0));
      pApple->setFaceColorsViaRange(pApple->getFacesCount() / 4, 3 * pApple->getFacesCount() / 4, OdTvColorDef(125, 125, 125));
      pApple->setFaceMaterialsViaRange(0, pApple->getFacesCount() / 4, appleMaterialId);
      pApple->setFaceMaterialsViaRange(pApple->getFacesCount() / 4 + 1, 3 * pApple->getFacesCount() / 4, guardMaterialId);
    }
  }
}

void OdTvVisualizeSampleModels::initBallModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId, const OdString& strResourceFolder)
{
  // Open database
  OdTvDatabasePtr pTvDb = databaseId.openObject();

  // Create entity
  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId entityId = modelPtr->appendEntity(OD_T("Ball"));
  OdTvEntityPtr pEntity = entityId.openObject(OdTv::kForWrite);

  // Append sphere to entity
  pEntity->appendShellFromSphere(OdTvPoint(3., 3., 3.), 1., OdTvVector::kYAxis, OdTvVector::kXAxis, 50);

  // Create material with unique name
  OdTvMaterialId materialId = pTvDb->createMaterial("Material");
  OdTvMaterialPtr pMaterial = materialId.openObject(OdTv::kForWrite);

  // Create material map
  OdTvMaterialMap materialMap;

  // Create path to texture image file and set it to map
  OdString texturePath = OdTvVisualizeSampleModelsUtils::formatPath(strResourceFolder, OD_T("textures/ball.png"));
  materialMap.setSourceFileName(texturePath);

  // Create entity mapper
  OdTvMapperDef entityMapper;
  entityMapper.setProjection(OdTvMapperDef::kSphere);
  // Translate and rotate texture
  entityMapper.translate(3., 3., 3.);
  entityMapper.rotate(0., OdaPI / 2., OdaPI / 2.);

  // Create material mapper, set texture sample size and set it to map
  OdTvTextureMapper materialMapper;
  materialMapper.setSampleSize(1., 1.);
  materialMap.setMapper(materialMapper);

  // Set mapper to entity
  pEntity->setMaterialMapper(entityMapper);

  // Set material map to material
  pMaterial->setDiffuse(OdTvMaterialColor(OdTvColorDef(255, 0, 0)), materialMap);

  // Set material to mapper
  pEntity->setMaterial(materialId);
}

void OdTvVisualizeSampleModels::initTeapotModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId, const OdString& strResourceFolder)
{
  //generate text style
  OdTvDatabasePtr pTvDb = databaseId.openObject();
  OdTvTextStyleId textStyle = pTvDb->createTextStyle(OD_T("kMiddleCenter"));
  {
    OdTvTextStylePtr pTextStyle = textStyle.openObject(OdTv::kForWrite);
    pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleCenter);
  }

  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId modelKeyEntityId = modelPtr->appendEntity(OD_T("LightExampleEntity"));
  {
    OdTvEntityPtr modelKeyEntity = modelKeyEntityId.openObject(OdTv::kForWrite);

    //2. Add teapot and light
    OdTvGeometryDataId geometries_entity_Id = modelKeyEntity->appendSubEntity(OD_T("entity0"));
    {
      OdTvEntityPtr pGeometryEntity = geometries_entity_Id.openAsSubEntity(OdTv::kForWrite);

      OdTvShellDataPtr pShell;
      OdTvPoint2dArray mappingCoords;

      // Draw shell and get mapping coordinates
      OdTvVisualizeSampleModelsTeapot::drawTeapot(pShell, mappingCoords, pGeometryEntity);

      // Create material with unique name
      OdTvMaterialId materialId = pTvDb->createMaterial("Material");
      OdTvMaterialPtr pMaterial = materialId.openObject(OdTv::kForWrite);

      // Construct path to texture image file
      OdString texturePath = OdTvVisualizeSampleModelsUtils::formatPath(strResourceFolder, OD_T("textures/marble.png"));

      // Create material map and set texture to map
      OdTvMaterialMap materialMap;
      materialMap.setSourceFileName(texturePath);
      // Set material map to material
      pMaterial->setDiffuse(OdTvMaterialColor(OdTvColorDef(255, 0, 0)), materialMap);

      // set material to the entity
      pGeometryEntity->setMaterial(materialId);

      // Set mapping coordinates to shell
      pShell->setVertexMappingCoordsViaRange(0, mappingCoords);
      pShell->setBackFaceCulling(OdTvShellData::kOn);

      //create lights
      OdTvEntityId light0Id = modelPtr->appendLight(OD_T("Light0"));
      OdTvLightPtr pLight0 = light0Id.openObjectAsLight(OdTv::kForWrite);
      pLight0->setPosition(OdTvPoint(-2., 2., 2.));
      pLight0->setLightColor(OdTvColorDef(255, 0, 0));
      pLight0->setTargetLocation(OdTvPoint(0., 1., 0.));
      pLight0->setIntensity(3.);
      pLight0->setHotspotAndFalloff(OdaPI4, 11. * OdaPI4 / 10.);

      OdTvEntityId light1Id = modelPtr->appendLight(OD_T("Light1"));
      OdTvLightPtr pLight1 = light1Id.openObjectAsLight(OdTv::kForWrite);
      pLight1->setPosition(OdTvPoint(2., 2., 2.));
      pLight1->setLightColor(OdTvColorDef(0, 255, 0));
      pLight1->setTargetLocation(OdTvPoint(0., 1., 0.));
      pLight1->setIntensity(3.);
      pLight1->setHotspotAndFalloff(OdaPI4, 11. * OdaPI4 / 10.);

      OdTvEntityId light2Id = modelPtr->appendLight(OD_T("Light2"));
      OdTvLightPtr pLight2 = light2Id.openObjectAsLight(OdTv::kForWrite);
      pLight2->setPosition(OdTvPoint(0., -1., 2.));
      pLight2->setLightColor(OdTvColorDef(0, 0, 255));
      pLight2->setTargetLocation(OdTvPoint(0., 1., 0.));
      pLight2->setIntensity(3.);
      pLight2->setHotspotAndFalloff(OdaPI4, 11. * OdaPI4 / 10.);
      pLight2->setGlyphDisplay(OdTvLight::kGlyphDisplayOff);
    }
  }
}

void OdTvVisualizeSampleModels::initPepcianModel(OdTvDatabaseId& databaseId, OdTvFactoryId& factoryId, OdTvModelId& modelId, OdTvFilerTimeProfiling* pProfileRes, const OdString& strResourceFolder)
{
  // Read VSF file
  OdString odSFileName = OdTvVisualizeSampleModelsUtils::formatPath(strResourceFolder, OD_T("samples/pepsi_can.vsf"));

  // read the file
  //prepare timing object
  OdTvFilerTimer timing(true);
  timing.startTotal();

  OdTvResult rc;
  databaseId = importVSF(odSFileName, false, false, &rc);

  // fill profiling info
  if (pProfileRes)
    pProfileRes->setImportTime(OdInt64(timing.getTotalTime() * 1000.));

  //get active model 
  OdTvDatabasePtr pTvDb;
  if (databaseId.isValid())
  {
    pTvDb = databaseId.openObject();

    if (!pTvDb.isNull())
    {
      OdTvModelsIteratorPtr pModelsIterator = pTvDb->getModelsIterator();
      modelId = pModelsIterator->getModel();
    }
  }
 
  // Create material with unique name
  OdTvMaterialId materialId = pTvDb->createMaterial("Pepsi can");
  OdTvMaterialPtr pMaterial = materialId.openObject(OdTv::kForWrite);

  // Create material map
  OdTvMaterialMap materialMap;

  // Construct path to texture image file
  OdString texturePath = OdTvVisualizeSampleModelsUtils::formatPath(strResourceFolder, OD_T("textures/pepsi.jpg"));
  materialMap.setSourceFileName(texturePath);

  // Create material mapper
  OdTvTextureMapper materialMapper;
  materialMapper.setUTiling(OdTvTextureMapper::kCrop);
  materialMapper.setVTiling(OdTvTextureMapper::kCrop);
  materialMap.setMapper(materialMapper);

  pMaterial->setDiffuse(OdTvMaterialColor(OdTvColorDef(255, 0, 0)), materialMap);

  // Create entity mapper
  OdTvMapperDef entityMapper;
  entityMapper.setProjection(OdTvMapperDef::kCylinder);
  entityMapper.translate(OdTvVector(-0.160561546, 1.8961546, 0.));
  entityMapper.scale(1., 1., 26.1499);

  // Get entities and set material
  OdTvEntityPtr pTopEntity = modelId.openObject(OdTv::kForRead)->findEntity(0x007A).openObject(OdTv::kForWrite);
  pTopEntity->setMaterialMapper(entityMapper);
  pTopEntity->setMaterial(materialId);

  OdTvEntityPtr pBodyEntity = pTopEntity->findSubEntity(0x007D).openAsSubEntity(OdTv::kForWrite);
  pBodyEntity->setMaterialMapper(entityMapper);
  pBodyEntity->setMaterial(materialId);
}

void OdTvVisualizeSampleModels::initOpacityModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId, const OdString& strResourceFolder)
{
  // Open database
  OdTvDatabasePtr pTvDb = databaseId.openObject();

  // Create entity
  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId entityId = modelPtr->appendEntity(OD_T("Sphere"));
  OdTvEntityPtr pEntity = entityId.openObject(OdTv::kForWrite);

  // Append shell to entity
  OdTvPointArray points;
  points.append(OdTvPoint(-0.5, -0.5, -0.5));
  points.append(OdTvPoint(-0.5, 0.5, -0.5));
  points.append(OdTvPoint(0.5, 0.5, -0.5));
  points.append(OdTvPoint(0.5, -0.5, -0.5));

  OdInt32Array faces;
  faces.append(4);
  faces.append(0);
  faces.append(1);
  faces.append(2);
  faces.append(3);

  OdTvGeometryDataId shellId = pEntity->appendShell(points, faces);
  OdTvShellDataPtr pShell = shellId.openAsShell();

  OdTvPoint2dArray mappingCoords;
  mappingCoords.append(OdTvPoint2d(0., 0.));
  mappingCoords.append(OdTvPoint2d(0., 1.));
  mappingCoords.append(OdTvPoint2d(1., 1.));
  mappingCoords.append(OdTvPoint2d(1., 0.));
  pShell->setVertexMappingCoordsViaRange(0, mappingCoords);

  // Create material with unique name
  OdTvMaterialId materialId = pTvDb->createMaterial("Material");
  OdTvMaterialPtr pMaterial = materialId.openObject(OdTv::kForWrite);

  // Create diffuse map
  OdTvMaterialMap diffuseMap;

  // Create path to texture image file and set it to diffuse map
  OdString texturePath = OdTvVisualizeSampleModelsUtils::formatPath(strResourceFolder, OD_T("textures/texture_for_opacity.png"));
  diffuseMap.setSourceFileName(texturePath);

  // Set material map to material
  pMaterial->setDiffuse(OdTvMaterialColor(OdTvColorDef(255, 0, 0)), diffuseMap);

  OdTvMaterialMap opacityMap;
  OdString opacityTexturePath = OdTvVisualizeSampleModelsUtils::formatPath(strResourceFolder, OD_T("textures/opacity.png"));
  opacityMap.setSourceFileName(opacityTexturePath);
  opacityMap.setBlendFactor(1.);
  pMaterial->setOpacity(1., &opacityMap);

  // Set material to mapper
  pEntity->setMaterial(materialId);
}

void OdTvVisualizeSampleModels::initBumpModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId, const OdString& strResourceFolder)
{
  // Open database
  OdTvDatabasePtr pTvDb = databaseId.openObject();

  // Create entity
  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId entityId = modelPtr->appendEntity(OD_T("Sphere"));
  OdTvEntityPtr pEntity = entityId.openObject(OdTv::kForWrite);

  // Append sphere to entity
  pEntity->appendShellFromSphere(OdTvPoint(0., 0., 0.), 0.5, OdTvVector::kYAxis, OdTvVector::kXAxis, 50);

  OdTvEntityId entityId1 = modelPtr->appendEntity(OD_T("Sphere1"));
  OdTvEntityPtr pEntity1 = entityId1.openObject(OdTv::kForWrite);

  // Append sphere to entity
  pEntity1->appendShellFromSphere(OdTvPoint(1.25, 0., 0.), 0.5, OdTvVector::kYAxis, OdTvVector::kXAxis, 50);

  // Create material with unique name
  OdTvMaterialId materialId = pTvDb->createMaterial("Material");
  OdTvMaterialPtr pMaterial = materialId.openObject(OdTv::kForWrite);

  OdTvMaterialId materialId1 = pTvDb->createMaterial("Material1");
  OdTvMaterialPtr pMaterial1 = materialId1.openObject(OdTv::kForWrite);

  // Create diffuse map
  OdTvMaterialMap diffuseMap;

  // Create path to texture image file and set it to diffuse map
  OdString texturePath = OdTvVisualizeSampleModelsUtils::formatPath(strResourceFolder, OD_T("textures/diffuse.png"));
  diffuseMap.setSourceFileName(texturePath);

  // Create entity mapper
  OdTvMapperDef entityMapper;
  entityMapper.setProjection(OdTvMapperDef::kSphere);
  // Rotate texture
  entityMapper.rotate(OdaPI / 2., 0., 0.);

  OdTvMapperDef entityMapper1;
  entityMapper1.setProjection(OdTvMapperDef::kSphere);
  // Rotate texture
  entityMapper1.translate(1.25, 0., 0.);
  entityMapper1.rotate(OdaPI / 2., 0., 0.);

  // Create material mapper, set texture sample size and set it to map
  OdTvTextureMapper materialMapper;
  materialMapper.setSampleSize(0.5, 0.5);
  diffuseMap.setMapper(materialMapper);

  // Set mapper to entity
  pEntity->setMaterialMapper(entityMapper);
  pEntity1->setMaterialMapper(entityMapper1);

  // Set material map to material
  pMaterial->setDiffuse(OdTvMaterialColor(OdTvColorDef(255, 0, 0)), diffuseMap);

  // Set material map to material
  pMaterial1->setDiffuse(OdTvMaterialColor(OdTvColorDef(255, 0, 0)), diffuseMap);

  // Create bump map
  OdTvMaterialMap bumpMap;

  // Create path to bump texture image file and set it to bump map
  OdString bumpTexturePath = OdTvVisualizeSampleModelsUtils::formatPath(strResourceFolder, OD_T("textures/bump.png"));
  bumpMap.setSourceFileName(bumpTexturePath);
  bumpMap.setMapper(materialMapper);

  // Set bump to material
  pMaterial->setBump(bumpMap);

  // Set material to mapper
  pEntity->setMaterial(materialId);

  // Set material to mapper
  pEntity1->setMaterial(materialId1);
}

OdTvDatabaseId OdTvVisualizeSampleModels::importVSF( const OdString& filename, bool bMtMode, bool bPartialMode, OdTvResult* rc )
{
  OdTvVsfImportParams params;
  params.setFilePath( filename );
  params.setMtImport( bMtMode );
  OdTvFactoryId factId = odTvGetFactory();
  return factId.importFile( &params, rc );
}

