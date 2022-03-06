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

#include "VisualizeDebugModelsGeneratorImpl.h"
#include "VisualizeModelsGeneratorUtils.h"
#include "VisualizeModelsGeneratorTeapot.h"
#include "TvInsert.h"

OdTvDatabaseId OdTvViewerDebugSampleModels::generateCircleEllipseModel(OdTvFactoryId& id)
{
  static int sequenceCircleEllipseNumber = 1;

  // Create window title
  OdString strCurTitle;
  strCurTitle.format(OD_T("Circle_Ellipse_arcs_Field%d"), sequenceCircleEllipseNumber++);

  //create empty database
  OdTvDatabaseId databaseId = id.createDatabase();

  //create and fill the model
  OdTvDatabasePtr dbPtr = databaseId.openObject(OdTv::kForWrite);

  OdTvModelId modelId = dbPtr->createModel(strCurTitle);

  // fill model according to the soccer example
  initCircleEllipseArcsModel(modelId);

  return databaseId;
}

OdTvDatabaseId OdTvViewerDebugSampleModels::generateLinetypeSampleModel(OdTvFactoryId& id)
{
  static int sequenceLinetypeNumber = 1;

  // Create window title
  OdString strCurTitle;
  strCurTitle.format(OD_T("Linetypes%d"), sequenceLinetypeNumber++);

  //create empty database
  OdTvDatabaseId databaseId = id.createDatabase();

  //create and fill the model
  OdTvDatabasePtr dbPtr = databaseId.openObject(OdTv::kForWrite);

  OdTvModelId modelId = dbPtr->createModel(strCurTitle);

  // fill model with different geometry and linetypes
  initLinetypesModel(databaseId, modelId);

  return databaseId;
}

OdTvDatabaseId OdTvViewerDebugSampleModels::generateLayersSampleModel(OdTvFactoryId& id)
{
  static int sequenceLayerNumber = 1;

  // Create window title
  OdString strCurTitle;
  strCurTitle.format(OD_T("Layers%d"), sequenceLayerNumber++);

  //create empty database
  OdTvDatabaseId databaseId = id.createDatabase();

  //create and fill the model
  OdTvDatabasePtr dbPtr = databaseId.openObject(OdTv::kForWrite);

  OdTvModelId modelId = dbPtr->createModel(strCurTitle);

  // fill model with different geometry with layers
  initLayersModel(databaseId, modelId);

  return databaseId;
}

OdTvDatabaseId OdTvViewerDebugSampleModels::generateTransparencySampleModel(OdTvFactoryId& id)
{
  static int sequenceTransparencyNumber = 1;

  // Create window title
  OdString strCurTitle;
  strCurTitle.format(OD_T("Transparency%d"), sequenceTransparencyNumber++);

  //create empty database
  OdTvDatabaseId databaseId = id.createDatabase();

  //create and fill the model
  OdTvDatabasePtr dbPtr = databaseId.openObject(OdTv::kForWrite);

  OdTvModelId modelId = dbPtr->createModel(strCurTitle);

  // fill model with different geometry with layers
  initTransparencyModel(databaseId, modelId);

  // create "non-setup device"
  OdTvGsDeviceId deviceId = dbPtr->createDevice(strCurTitle);

  OdTvGsDevicePtr pDevice = deviceId.openObject(OdTv::kForWrite);

  OdString strViewName;
  strViewName.format(OD_T("View_%d"), sequenceTransparencyNumber++);

  OdTvResult rc;

  // create main view
  OdTvGsViewId viewId = pDevice->createView(strViewName, true, &rc);
  pDevice->addView(viewId);
  // add current model to the view
  {
    OdTvGsViewPtr viewPtr = viewId.openObject(OdTv::kForWrite);

    viewPtr->setView(OdTvPoint(-0.4, -0.45, 0.), OdTvPoint(-0.4, -0.45, 0.), OdTvVector(0., 1., 0.), 2.55, 2.55);

    viewPtr->addModel(modelId);
    viewPtr->setMode(OdTvGsView::kGouraudShaded);

    viewPtr->setActive(true);
  }

  return databaseId;
}

OdTvDatabaseId OdTvViewerDebugSampleModels::generateLightSampleModel(OdTvFactoryId& id)
{
  static int sequenceLightNumber = 1;

  // Create window title
  OdString strCurTitle;
  strCurTitle.format(OD_T("Light%d"), sequenceLightNumber++);

  //create empty database
  OdTvDatabaseId databaseId = id.createDatabase();

  //create and fill the model
  OdTvDatabasePtr dbPtr = databaseId.openObject(OdTv::kForWrite);

  OdTvModelId modelId = dbPtr->createModel(strCurTitle);

  // fill model with different light
  initLightModel(databaseId, modelId);

  // create "non-setup device"
  OdTvGsDeviceId deviceId = dbPtr->createDevice(strCurTitle);

  OdTvGsDevicePtr pDevice = deviceId.openObject(OdTv::kForWrite);

  OdString strViewName;
  strViewName.format(OD_T("View_%d"), sequenceLightNumber++);

  OdTvResult rc;

  // create main view
  OdTvGsViewId viewId = pDevice->createView(strViewName, true, &rc);
  pDevice->addView(viewId);
  // add current model to the view
  {
    OdTvGsViewPtr viewPtr = viewId.openObject(OdTv::kForWrite);

    viewPtr->setView(OdTvPoint(0., 0., 0.), OdTvPoint(0., 0., 0.), OdTvVector(0., 1., 0.), 3., 3.);

    viewPtr->addModel(modelId);
    viewPtr->setMode(OdTvGsView::kGouraudShaded);

    viewPtr->setActive(true);
  }

  return databaseId;
}

OdTvDatabaseId OdTvViewerDebugSampleModels::generateDebugMaterialsSampleModel(OdTvFactoryId& id, const OdString& strResourceFolder)
{
  static int sequenceMaterialsNumber = 1;

  // Create window title
  OdString strCurTitle;
  strCurTitle.format(OD_T("Materials%d"), sequenceMaterialsNumber++);

  //create empty database
  OdTvDatabaseId databaseId = id.createDatabase();

  //create and fill the model
  OdTvDatabasePtr dbPtr = databaseId.openObject(OdTv::kForWrite);

  OdTvModelId modelId = dbPtr->createModel(strCurTitle);

  // fill model with materials
  initMaterialsModel(databaseId, modelId, strResourceFolder);

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
    OdTvGsViewPtr viewPtr = viewId.openObject(OdTv::kForWrite);

    viewPtr->setView(OdTvPoint(-1., -10., 0.), OdTvPoint(-1., -10., 0.), OdTvVector(0., 1., 0.), 25., 25.);

    viewPtr->addModel(modelId);
    viewPtr->setMode(OdTvGsView::kGouraudShaded);

    viewPtr->setActive(true);
  }

  return databaseId;
}

OdTvDatabaseId OdTvViewerDebugSampleModels::generateShellModel(OdTvFactoryId& id, int type)
{
  static int sequenceShellNumber = 1;

  // Create window title
  OdString strCurTitle;
  strCurTitle.format(OD_T("Shells%d%d"), sequenceShellNumber++, type == 0 ? OD_T("_Faces") : OD_T("_Edges"));

  //create empty database
  OdTvDatabaseId databaseId = id.createDatabase();

  //create and fill the model
  OdTvDatabasePtr dbPtr = databaseId.openObject(OdTv::kForWrite);

  OdTvModelId modelId = dbPtr->createModel(strCurTitle);

  // fill model with different faces or edges attributes
  if (type == 0)
    initShellFacesAttributesModel(databaseId, modelId);
  else
    initShellEdgesAttributesModel(databaseId, modelId);

  // create "non-setup device"
  OdTvGsDeviceId deviceId = dbPtr->createDevice(strCurTitle);

  OdTvGsDevicePtr pDevice = deviceId.openObject(OdTv::kForWrite);

  OdString strViewName;
  strViewName.format(OD_T("View_%d"), sequenceShellNumber++);

  OdTvResult rc;

  // create main view
  OdTvGsViewId viewId = pDevice->createView(strViewName, true, &rc);
  pDevice->addView(viewId);
  // add current model to the view
  {
    OdTvGsViewPtr viewPtr = viewId.openObject(OdTv::kForWrite);

    viewPtr->setView(OdTvPoint(-0.12, 0., 0.), OdTvPoint(-0.12, 0., 0.), OdTvVector(0., 1., 0.), 2., 2.);

    viewPtr->addModel(modelId);
   if (type == 0)
      viewPtr->setMode(OdTvGsView::kGouraudShaded);

   viewPtr->setActive(true);
  }

  return databaseId;
}

OdTvDatabaseId OdTvViewerDebugSampleModels::generate3DGeometryAttributesModel(OdTvFactoryId& id, int type)
{
  static int sequenceNumber = 1;

  // Create window title
  OdString strCurTitle;
  strCurTitle.format(OD_T("3DGeometryAttributes%d"), sequenceNumber++);

  //create empty database
  OdTvDatabaseId databaseId = id.createDatabase();

  //create and fill the model
  OdTvDatabasePtr dbPtr = databaseId.openObject(OdTv::kForWrite);

  OdTvModelId modelId = dbPtr->createModel(strCurTitle);

  // fill model with different cylinder and sphere attributes
  if (type == 0)
    initCylinderAttributesModel(databaseId, modelId);
  else if (type == 1)
    initSphereAttributesModel(databaseId, modelId);
  else if (type == 2)
    initBoxAttributesModel(databaseId, modelId);

  // create "non-setup device"
  OdTvGsDeviceId deviceId = dbPtr->createDevice(strCurTitle);

  OdTvGsDevicePtr pDevice = deviceId.openObject(OdTv::kForWrite);

  OdString strViewName;
  strViewName.format(OD_T("View_%d"), sequenceNumber++);

  OdTvResult rc;

  // create main view
  OdTvGsViewId viewId = pDevice->createView(strViewName, true, &rc);
  pDevice->addView(viewId);
  // add current model to the view
  {
    OdTvGsViewPtr viewPtr = viewId.openObject(OdTv::kForWrite);

    viewPtr->setView(OdTvPoint(-0.12, 0., 0.), OdTvPoint(-0.12, 0., 0.), OdTvVector(0., 1., 0.), 1.85, 1.85);

    viewPtr->addModel(modelId);
    viewPtr->setMode(OdTvGsView::kGouraudShadedWithWireframe);

    viewPtr->setActive(true);
  }

  return databaseId;
}

OdTvDatabaseId OdTvViewerDebugSampleModels::generateMeshModel(OdTvFactoryId& id, int type)
{
  static int sequenceMeshNumber = 1;

  // Create window title
  OdString strCurTitle;
  strCurTitle.format(OD_T("Meshes%d%d"), sequenceMeshNumber++, type == 0 ? OD_T("_Faces") : OD_T("_Edges"));

  //create empty database
  OdTvDatabaseId databaseId = id.createDatabase();

  //create and fill the model
  OdTvDatabasePtr dbPtr = databaseId.openObject(OdTv::kForWrite);

  OdTvModelId modelId = dbPtr->createModel(strCurTitle);

  // fill model with different faces or edges attributes
  if (type == 0)
    initMeshFacesAttributesModel(databaseId, modelId);
  else
    initMeshEdgesAttributesModel(databaseId, modelId);

  // create "non-setup device"
  OdTvGsDeviceId deviceId = dbPtr->createDevice(strCurTitle);

  OdTvGsDevicePtr pDevice = deviceId.openObject(OdTv::kForWrite);

  OdString strViewName;
  strViewName.format(OD_T("View_%d"), sequenceMeshNumber++);

  OdTvResult rc;

  // create main view
  OdTvGsViewId viewId = pDevice->createView(strViewName, true, &rc);
  pDevice->addView(viewId);
  // add current model to the view
  {
    OdTvGsViewPtr viewPtr = viewId.openObject(OdTv::kForWrite);


    if (type == 0)
      viewPtr->setMode(OdTvGsView::kGouraudShaded);

    viewPtr->setView(OdTvPoint(-0.175, -0.1, 0.), OdTvPoint(-0.175, -0.1, 0.), OdTvVector(0., 1., 0.), 1.95, 1.95);

    viewPtr->addModel(modelId);

    viewPtr->setActive(true);
  }

  return databaseId;
}

OdTvDatabaseId OdTvViewerDebugSampleModels::generateResetAttributesModel(OdTvFactoryId& id, int type)
{
  static int sequenceLinetypeNumber = 1;

  // Create window title
  OdString strCurTitle;
  strCurTitle.format(OD_T("Reset attributes%d"), sequenceLinetypeNumber++);

  //create empty database
  OdTvDatabaseId databaseId = id.createDatabase();

  //create and fill the model
  OdTvDatabasePtr dbPtr = databaseId.openObject(OdTv::kForWrite);

  OdTvModelId modelId = dbPtr->createModel(strCurTitle);

  // fill model with reseting attributes examples
  if (type == 0)
  {
    initResetColorsModel(databaseId, modelId);
  }
  else if (type == 1)
  {
    initResetLineWeightModel(databaseId, modelId);
  }
  else if (type == 2)
  {
    initResetLinetypeModel(databaseId, modelId);
  }
  else if (type == 3)
  {
    initResetLinetypeScaleModel(databaseId, modelId);
  }
  else if (type == 4)
  {
    initResetLayerModel(databaseId, modelId);
  }
  else if (type == 5)
  {
    initResetVisibilityModel(databaseId, modelId);
  }

  return databaseId;
}

OdTvDatabaseId OdTvViewerDebugSampleModels::generateManyCylindersModel(OdTvFactoryId& id, int type)
{
  // Create window title
  OdString strCurTitle;
  strCurTitle.format(OD_T("Cylinders_%d"), type);

  //create empty database
  OdTvDatabaseId databaseId = id.createDatabase();

  //create and fill the model
  OdTvDatabasePtr dbPtr = databaseId.openObject(OdTv::kForWrite);
  OdTvModelId modelId = dbPtr->createModel(strCurTitle);
  OdTvModelPtr pModel = modelId.openObject(OdTv::kForWrite);

  // fill model
  int max = pow(50000, 1.0 / 3.0);

  for (int x = 0; x < max; x++)
  {
    for (int y = 0; y < max; y++)
    {
      for (int z = 0; z < max; z++)
      {
        OdTvEntityId entity = pModel->appendEntity("Pipe");
        OdTvEntityPtr entityPtr = entity.openObject(OdTv::kForWrite);

        OdTvPoint arr[2] = { OdTvPoint(0.0, 0.0, 0.0), OdTvPoint(0, 0, 8) };
        double radii[2] = { 2, 2 };

        if (type == 0 || type == 2)
          entityPtr->appendShellFromCylinder(2, &arr[0], 2, &radii[0], OdTvCylinderData::Capping::kBoth, 48);
        else
        {
          OdTvGeometryDataId geomId = entityPtr->appendCylinder(2, &arr[0], 2, &radii[0], OdTvCylinderData::Capping::kBoth);
          geomId.openAsCylinder()->setDeviation(OdTvCylinderData::kFixed, 48);
        }
        entityPtr->setColor(OdTvColorDef(150, 200, 230));
        entityPtr->translate(10*x, 10*y, 10 * z);
      }
    }
  }

  //create device and view
  OdTvGsDeviceId devId = dbPtr->createDevice(strCurTitle);
  OdTvGsViewId viewId = devId.openObject(OdTv::kForWrite)->createView(strCurTitle);
  OdTvGsViewPtr pView = viewId.openObject(OdTv::kForWrite);
  
  pView->addModel(modelId);
  pView->setMode(OdTvGsView::kGouraudShaded);
  devId.openObject(OdTv::kForWrite)->addView(viewId);

  pView->setActive(true);

  return databaseId;
}

OdTvDatabaseId OdTvViewerDebugSampleModels::generateSelectionModel(OdTvFactoryId& id, int type)
{
  //create empty database
  OdTvDatabaseId databaseId = id.createDatabase();

  //create and fill the model and the block
  {
    OdTvDatabasePtr dbPtr = databaseId.openObject(OdTv::kForWrite);
    OdTvModelId modelId = dbPtr->createModel(OD_T("MODEL_1"));
    OdTvModelPtr pModel = modelId.openObject(OdTv::kForWrite);

    OdTvBlockId blockId = dbPtr->createBlock(OD_T("BLOCK_1"));
    OdTvBlockPtr pBlock = blockId.openObject(OdTv::kForWrite);

    for (int i = 0; i < 2; i++)
    {
      OdTvEntityId entId = (i == 0) ? pModel->appendEntity(OD_T("Entity_1")) : pBlock->appendEntity(OD_T("Entity_1_inblock"));
      OdTvEntityPtr pEnt = entId.openObject(OdTv::kForWrite);
      pEnt->setColor(OdTv::kByBlock);

      pEnt->appendPolyline(OdTvPoint(-0.25, 0.5, 0), OdTvPoint(0.4, 0.35, 0.));
      pEnt->appendShellFromSphere(OdTvPoint(1.2, 0.5, 0.), 0.5);

      if (i > 0)
      {
        entId = pBlock->appendEntity(OD_T("Entity_2_inblock"));
        OdTvEntityPtr pEnt1 = entId.openObject(OdTv::kForWrite);
        pEnt1->setColor(OdTv::kByBlock);

        pEnt1->appendCircle(OdTvPoint(1.2, -0.5, 0.), 0.5, OdTvVector(0.,0.,1.));
      }
    }

    OdTvEntityId insertId = pModel->appendInsert(blockId, OD_T("Insert_1"));
    OdTvInsertPtr pIns = insertId.openObjectAsInsert(OdTv::kForWrite);
    pIns->setColor(OdTvColorDef(255, 0, 0));
    pIns->setPosition(OdTvPoint(0., -1.2, 0));


    //cerate device and view
    OdTvGsDeviceId tvDeviceId = dbPtr->createDevice(OD_T("DEVICE_1"));
    OdTvGsDevicePtr pDevice = tvDeviceId.openObject(OdTv::kForWrite);

    // create view
    OdTvGsViewId tvViewId = pDevice->createView(OD_T("VIEW_1"));
    pDevice->addView(tvViewId);

    //setup view
    OdTvGsViewPtr pView = tvViewId.openObject(OdTv::kForWrite);
    pView->addModel(modelId);
    pView->setView(OdTvPoint(0., 0., 1.), OdTvPoint(0., 0., 0.), OdTvVector(0., 1., 0.), 1., 1.);
    pView->setActive(true);

    if (type > 0)
      pDevice->setOption(OdTvGsDevice::kBlocksCache, true);

    // since the GS is not setup yet,we can call empty zoom to extens to mark the view.
    // The action will be performed inside first setupGs
    OdTvPoint minPt, maxPt;
    pView->zoomExtents(minPt, maxPt);
  }

  return databaseId;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private methods
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OdTvViewerDebugSampleModels::initCircleEllipseArcsModel(OdTvModelId& modelId)
{
  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvDatabaseId databaseId = modelPtr->getDatabase();

  //generate text style
  OdTvDatabasePtr pTvDb = databaseId.openObject();
  OdTvTextStyleId textStyle = pTvDb->createTextStyle(OD_T("kMiddleCenter"));
  {
    OdTvTextStylePtr pTextStyle = textStyle.openObject(OdTv::kForWrite);
    pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleCenter);
    pTextStyle->setTextSize(0.02);
  }

  OdTvEntityId modelKeyEntityId = modelPtr->appendEntity(OD_T("Circles, Ellipses, Arcs"));
  {
    OdTvEntityPtr modelKeyEntity = modelKeyEntityId.openObject(OdTv::kForWrite);

    //1. Add title
    OdTvGeometryDataId titleEntityId = modelKeyEntity->appendSubEntity(OD_T("title"));
    {
      OdTvEntityPtr titleEntity = titleEntityId.openAsSubEntity(OdTv::kForWrite);
      titleEntity->setColor(OdTvColorDef(128, 000, 128), OdTvGeometryData::kAll);
      titleEntity->setLineWeight(2);

      titleEntity->appendText(OdTvPoint(0.0, 0.78, 0.0), OD_T("Circles, Ellipses, Arcs"));
      titleEntity->setTextStyle(textStyle);
    }

    //2. Add grid lines
    OdTvVisualizeSampleModelsUtils::appendGridLines(modelKeyEntity, false, 3, 5, -1., 0.66, 0.66, 0.33);

    //3.Add simple subentity (not filled, not edges)
    OdTvGeometryDataId simple_entity_Id = modelKeyEntity->appendSubEntity(OD_T("simple subentity"));
    {
      OdTvEntityPtr simple_entity_ptr = simple_entity_Id.openAsSubEntity(OdTv::kForWrite);
      simple_entity_ptr->setColor(OdTvColorDef(0, 0, 255), OdTvGeometryData::kEdges);
      simple_entity_ptr->setLineWeight(2);

      simple_entity_ptr->appendCircle(OdGePoint3d(-0.82, 0.5, 0.), OdGePoint3d(-0.67, 0.64, 0.), OdGePoint3d(-0.52, 0.5, 0.));
      simple_entity_ptr->appendCircleArc(OdGePoint3d(-0.95, 0.05, 0.), OdGePoint3d(-0.67, 0.3, 0.), OdGePoint3d(-0.39, 0.05, 0.));
      simple_entity_ptr->appendCircleWedge(OdGePoint3d(-0.95, -0.12, 0.), OdGePoint3d(-0.67, -0.32, 0.), OdGePoint3d(-0.39, -0.12, 0.));
      simple_entity_ptr->appendEllipse(OdGePoint3d(-0.66, -0.49, 0.), OdGePoint3d(-0.86, -0.4, 0.), OdGePoint3d(-0.46, -0.4, 0.));
      simple_entity_ptr->appendEllipticArc(OdGePoint3d(-0.76, -0.81, 0.), OdGePoint3d(-0.96, -0.72, 0.), OdGePoint3d(-0.56, -0.72, 0.), 1., 4.);
    }

    //4.Add filled subentity
    OdTvGeometryDataId filled_entity_Id = modelKeyEntity->appendSubEntity(OD_T("filled entity"));
    {
      OdTvEntityPtr filled_entity_ptr = filled_entity_Id.openAsSubEntity(OdTv::kForWrite);
      filled_entity_ptr->setColor(OdTvColorDef(255, 0, 0));
      filled_entity_ptr->setLineWeight(2);

      filled_entity_ptr->appendCircle(OdGePoint3d(-0.15, 0.5, 0.), OdGePoint3d(0., 0.64, 0.), OdGePoint3d(0.15, 0.5, 0.))
        .openAsCircle()->setFilled(true);

      filled_entity_ptr->appendCircleArc(OdGePoint3d(-0.28, 0.05, 0.), OdGePoint3d(0, 0.3, 0.), OdGePoint3d(0.28, 0.05, 0.))
        .openAsCircleArc()->setFilled(true);

      filled_entity_ptr->appendCircleWedge(OdGePoint3d(-0.28, -0.12, 0.), OdGePoint3d(0., -0.32, 0.), OdGePoint3d(0.28, -0.12, 0.))
        .openAsCircleWedge()->setFilled(true);

      filled_entity_ptr->appendEllipse(OdGePoint3d(0, -0.49, 0.), OdGePoint3d(0.2, -0.4, 0.), OdGePoint3d(-0.2, -0.4, 0.))
        .openAsEllipse()->setFilled(true);

      filled_entity_ptr->appendEllipticArc(OdGePoint3d(-0.1, -0.81, 0.), OdGePoint3d(-0.3, -0.72, 0.), OdGePoint3d(0.1, -0.72, 0.), 1., 4.)
        .openAsEllipticArc()->setFilled(true);
    }

    //5.Add filed edged subentity
    OdTvGeometryDataId filled_edged_entity_Id = modelKeyEntity->appendSubEntity(OD_T("filled edged entity"));
    {
      OdTvEntityPtr filled_edged_entity_ptr = filled_edged_entity_Id.openAsSubEntity(OdTv::kForWrite);
      filled_edged_entity_ptr->setColor(OdTvColorDef(0, 255, 0), OdTvGeometryData::kFaces);
      filled_edged_entity_ptr->setColor(OdTvColorDef(0, 0, 255));
      filled_edged_entity_ptr->setLineWeight(2);

      filled_edged_entity_ptr->appendCircle(OdGePoint3d(0.52, 0.5, 0.), OdGePoint3d(0.67, 0.64, 0.), OdGePoint3d(0.82, 0.5, 0.))
        .openAsCircle()->setFilled(true);

      filled_edged_entity_ptr->appendCircleArc(OdGePoint3d(0.39, 0.05, 0.), OdGePoint3d(0.67, 0.3, 0.), OdGePoint3d(0.95, 0.05, 0.))
        .openAsCircleArc()->setFilled(true);

      filled_edged_entity_ptr->appendCircleWedge(OdGePoint3d(0.39, -0.12, 0.), OdGePoint3d(0.67, -0.32, 0.), OdGePoint3d(0.95, -0.12, 0.))
        .openAsCircleWedge()->setFilled(true);

      filled_edged_entity_ptr->appendEllipse(OdGePoint3d(0.66, -0.49, 0.), OdGePoint3d(0.46, -0.4, 0.), OdGePoint3d(0.86, -0.4, 0.))
        .openAsEllipse()->setFilled(true);

      filled_edged_entity_ptr->appendEllipticArc(OdGePoint3d(0.56, -0.81, 0.), OdGePoint3d(0.36, -0.72, 0.), OdGePoint3d(0.76, -0.72, 0.), 1., 4.)
        .openAsEllipticArc()->setFilled(true);
    }
  }

  return;
}

void OdTvViewerDebugSampleModels::initLinetypesModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId)
{
  //generate text style
  OdTvDatabasePtr pTvDb = databaseId.openObject();
  OdTvTextStyleId textStyle = pTvDb->createTextStyle(OD_T("kMiddleCenter"));
  {
    OdTvTextStylePtr pTextStyle = textStyle.openObject(OdTv::kForWrite);
    pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleCenter);
    pTextStyle->setTextSize(0.02);
  }

  OdTvVector normal = OdTvVector::kZAxis;

  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId modelKeyEntityId = modelPtr->appendEntity(OD_T("Linetypes"));
  {
    OdTvEntityPtr modelKeyEntity = modelKeyEntityId.openObject(OdTv::kForWrite);

    //1. Add title
    OdTvGeometryDataId titleEntityId = modelKeyEntity->appendSubEntity(OD_T("title"));
    {
      OdTvEntityPtr titleEntity = titleEntityId.openAsSubEntity(OdTv::kForWrite);
      titleEntity->setColor(OdTvColorDef(128, 000, 128), OdTvGeometryData::kAll);
      titleEntity->setLineWeight(2);

      titleEntity->appendText(OdTvPoint(0.0, 0.45, 0.0), OD_T("Linetypes"));
      titleEntity->setTextStyle(textStyle);
    }

    //2. Add grid lines
    OdTvVisualizeSampleModelsUtils::appendGridLines(modelKeyEntity, true, 3, 6, -1., 0.66, 0.66, 0.33);

    //3. Add first column (solid line type)
    double x0 = -0.95;
    double y0 = 0.28;

    OdTvGeometryDataId geometries_entity_Id = modelKeyEntity->appendSubEntity(OD_T("solid"));
    {
      OdTvEntityPtr pGeomEntity = geometries_entity_Id.openAsSubEntity(OdTv::kForWrite);
      pGeomEntity->setColor(OdTvColorDef(0, 0, 255), OdTvGeometryData::kEdges | OdTvGeometryData::kPolylines);
      pGeomEntity->setColor(OdTvColorDef(0, 255, 0), OdTvGeometryData::kFaces);
      pGeomEntity->setLinetype(OdTvLinetypeDef(OdTvLinetype::kSolid));

      //add lines
      OdTvGeometryDataId gId = pGeomEntity->appendPolyline(OdTvPoint(x0, y0, 0.), OdTvPoint(x0 + 0.57, y0, 0.));
      gId.openObject()->setColor(OdTvColorDef(255, 0, 0));
      gId = pGeomEntity->appendPolyline(OdTvPoint(x0 + 0.59, y0, 0.), OdTvPoint(x0 + 0.59, y0 - 0.23, 0.));
      gId.openObject()->setColor(OdTvColorDef(255, 0, 255));
      pGeomEntity->appendPolyline(OdTvPoint(x0 + 0.57, y0 - 0.23, 0.), OdTvPoint(x0, y0 - 0.23, 0.));
      pGeomEntity->appendPolyline(OdTvPoint(x0 - 0.02, y0 - 0.23, 0.), OdTvPoint(x0 - 0.02, y0, 0.));

      y0 = -0.05;
      //add opposite direction
      gId = pGeomEntity->appendPolyline(OdTvPoint(x0 + 0.57, y0, 0.), OdTvPoint(x0, y0, 0.));
      gId.openObject()->setColor(OdTvColorDef(255, 0, 0));
      gId = pGeomEntity->appendPolyline(OdTvPoint(x0 - 0.02, y0, 0.), OdTvPoint(x0 - 0.02, y0 - 0.23, 0.));
      gId.openObject()->setColor(OdTvColorDef(255, 0, 255));
      pGeomEntity->appendPolyline(OdTvPoint(x0, y0 - 0.23, 0.), OdTvPoint(x0 + 0.57, y0 - 0.23, 0.));
      pGeomEntity->appendPolyline(OdTvPoint(x0 + 0.59, y0 - 0.23, 0.), OdTvPoint(x0 + 0.59, y0, 0.));

      //add rectangle
      OdTvVisualizeSampleModelsUtils::appendRectangle(pGeomEntity, x0 - 0.02, -0.61, x0 + 0.59, -0.38);

      //add rectangle (opposite direction)
      OdTvVisualizeSampleModelsUtils::appendRectangle(pGeomEntity, x0 - 0.02, -0.71, x0 + 0.59, -0.94);

      //add rectangle as polygon
      y0 = -1.05;
      OdTvVisualizeSampleModelsUtils::appendRectangle(pGeomEntity, x0 - 0.02, y0 - 0.23, x0 + 0.59, y0, 0., false, true);

      //add rectangle as polygon (opposite direction)
      y0 = -1.38;
      OdTvVisualizeSampleModelsUtils::appendRectangle(pGeomEntity, x0 - 0.02, y0, x0 + 0.59, y0 - 0.23, 0., false, true);

      //add circe
      y0 = -1.71;
      pGeomEntity->appendCircle(OdTvPoint(x0 + 0.305, y0 - 0.115, 0.), 0.115, OdTvVector::kZAxis);

      //add circe (opposite direction)
      y0 = -2.04;
      pGeomEntity->appendCircle(OdTvPoint(x0 + 0.305, y0 - 0.115, 0.), 0.115, -OdTvVector::kZAxis);
    }

    //4. Add second column (dash line type)
    x0 = -0.28;
    y0 = 0.28;
    geometries_entity_Id = modelKeyEntity->appendSubEntity(OD_T("dash"));
    {
      OdTvEntityPtr pGeomEntity = geometries_entity_Id.openAsSubEntity(OdTv::kForWrite);
      pGeomEntity->setColor(OdTvColorDef(0, 0, 255), OdTvGeometryData::kEdges | OdTvGeometryData::kPolylines);
      pGeomEntity->setColor(OdTvColorDef(0, 255, 0), OdTvGeometryData::kFaces);
      pGeomEntity->setLinetype(OdTvLinetype::kDashed);
      pGeomEntity->setLinetypeScale(0.05);

      //add lines
      OdTvGeometryDataId gId = pGeomEntity->appendPolyline(OdTvPoint(x0, y0, 0.), OdTvPoint(x0 + 0.57, y0, 0.));
      gId.openObject()->setColor(OdTvColorDef(255, 0, 0));
      gId = pGeomEntity->appendPolyline(OdTvPoint(x0 + 0.59, y0, 0.), OdTvPoint(x0 + 0.59, y0 - 0.23, 0.));
      gId.openObject()->setColor(OdTvColorDef(255, 0, 255));
      pGeomEntity->appendPolyline(OdTvPoint(x0 + 0.57, y0 - 0.23, 0.), OdTvPoint(x0, y0 - 0.23, 0.));
      pGeomEntity->appendPolyline(OdTvPoint(x0 - 0.02, y0 - 0.23, 0.), OdTvPoint(x0 - 0.02, y0, 0.));

      y0 = -0.05;
      //add opposite direction
      gId = pGeomEntity->appendPolyline(OdTvPoint(x0 + 0.57, y0, 0.), OdTvPoint(x0, y0, 0.));
      gId.openObject()->setColor(OdTvColorDef(255, 0, 0));
      gId = pGeomEntity->appendPolyline(OdTvPoint(x0 - 0.02, y0, 0.), OdTvPoint(x0 - 0.02, y0 - 0.23, 0.));
      gId.openObject()->setColor(OdTvColorDef(255, 0, 255));
      pGeomEntity->appendPolyline(OdTvPoint(x0, y0 - 0.23, 0.), OdTvPoint(x0 + 0.57, y0 - 0.23, 0.));
      pGeomEntity->appendPolyline(OdTvPoint(x0 + 0.59, y0 - 0.23, 0.), OdTvPoint(x0 + 0.59, y0, 0.));

      //add rectangle
      OdTvVisualizeSampleModelsUtils::appendRectangle(pGeomEntity, x0 - 0.02, -0.61, x0 + 0.59, -0.38);

      //add rectangle (opposite direction)
      OdTvVisualizeSampleModelsUtils::appendRectangle(pGeomEntity, x0 - 0.02, -0.71, x0 + 0.59, -0.94);

      //add rectangle as polygon
      y0 = -1.05;
      OdTvVisualizeSampleModelsUtils::appendRectangle(pGeomEntity, x0 - 0.02, y0 - 0.23, x0 + 0.59, y0, 0., false, true);

      //add rectangle as polygon (opposite direction)
      y0 = -1.38;
      OdTvVisualizeSampleModelsUtils::appendRectangle(pGeomEntity, x0 - 0.02, y0, x0 + 0.59, y0 - 0.23, 0., false, true);

      //add circe
      y0 = -1.71;
      pGeomEntity->appendCircle(OdTvPoint(x0 + 0.305, y0 - 0.115, 0.), 0.115, OdTvVector::kZAxis);

      //add circe (opposite direction)
      y0 = -2.04;
      pGeomEntity->appendCircle(OdTvPoint(x0 + 0.305, y0 - 0.115, 0.), 0.115, -OdTvVector::kZAxis);
    }

    //5. Add third column (custom line type with text)

    // 5.1 Create text style for the line type
    OdTvLinetypeId ltId = OdTvVisualizeSampleModelsUtils::generateCustomLineTypeWithText(databaseId);

    // 5.2 Create geometry
    x0 = 0.39;
    y0 = 0.28;
    geometries_entity_Id = modelKeyEntity->appendSubEntity(OD_T("custom with text"));
    {
      OdTvEntityPtr pGeomEntity = geometries_entity_Id.openAsSubEntity(OdTv::kForWrite);
      pGeomEntity->setColor(OdTvColorDef(0, 0, 255), OdTvGeometryData::kEdges | OdTvGeometryData::kPolylines);
      pGeomEntity->setColor(OdTvColorDef(0, 255, 0), OdTvGeometryData::kFaces);
      pGeomEntity->setLinetype(ltId);
      pGeomEntity->setLinetypeScale(0.05);

      //add lines
      OdTvGeometryDataId gId = pGeomEntity->appendPolyline(OdTvPoint(x0, y0, 0.), OdTvPoint(x0 + 0.57, y0, 0.));
      gId.openObject()->setColor(OdTvColorDef(255, 0, 0));
      gId.openAsPolyline()->setNormal(&normal);
      gId = pGeomEntity->appendPolyline(OdTvPoint(x0 + 0.59, y0, 0.), OdTvPoint(x0 + 0.59, y0 - 0.23, 0.));
      gId.openObject()->setColor(OdTvColorDef(255, 0, 255));
      gId.openAsPolyline()->setNormal(&normal);
      gId = pGeomEntity->appendPolyline(OdTvPoint(x0 + 0.57, y0 - 0.23, 0.), OdTvPoint(x0, y0 - 0.23, 0.));
      gId.openAsPolyline()->setNormal(&normal);
      gId = pGeomEntity->appendPolyline(OdTvPoint(x0 - 0.02, y0 - 0.23, 0.), OdTvPoint(x0 - 0.02, y0, 0.));
      gId.openAsPolyline()->setNormal(&normal);

      y0 = -0.05;
      //add opposite direction
      gId = pGeomEntity->appendPolyline(OdTvPoint(x0 + 0.57, y0, 0.), OdTvPoint(x0, y0, 0.));
      gId.openObject()->setColor(OdTvColorDef(255, 0, 0));
      gId.openAsPolyline()->setNormal(&normal);
      gId = pGeomEntity->appendPolyline(OdTvPoint(x0 - 0.02, y0, 0.), OdTvPoint(x0 - 0.02, y0 - 0.23, 0.));
      gId.openObject()->setColor(OdTvColorDef(255, 0, 255));
      gId.openAsPolyline()->setNormal(&normal);
      gId = pGeomEntity->appendPolyline(OdTvPoint(x0, y0 - 0.23, 0.), OdTvPoint(x0 + 0.57, y0 - 0.23, 0.));
      gId.openAsPolyline()->setNormal(&normal);
      gId = pGeomEntity->appendPolyline(OdTvPoint(x0 + 0.59, y0 - 0.23, 0.), OdTvPoint(x0 + 0.59, y0, 0.));
      gId.openAsPolyline()->setNormal(&normal);

      //add rectangle
      OdTvVisualizeSampleModelsUtils::appendRectangle(pGeomEntity, x0 - 0.02, -0.61, x0 + 0.59, -0.38);

      //add rectangle (opposite direction)
      OdTvVisualizeSampleModelsUtils::appendRectangle(pGeomEntity, x0 - 0.02, -0.71, x0 + 0.59, -0.94);

      //add rectangle as polygon
      y0 = -1.05;
      OdTvVisualizeSampleModelsUtils::appendRectangle(pGeomEntity, x0 - 0.02, y0 - 0.23, x0 + 0.59, y0, 0., false, true);

      //add rectangle as polygon (opposite direction)
      y0 = -1.38;
      OdTvVisualizeSampleModelsUtils::appendRectangle(pGeomEntity, x0 - 0.02, y0, x0 + 0.59, y0 - 0.23, 0., false, true);

      //add circe
      y0 = -1.71;
      pGeomEntity->appendCircle(OdTvPoint(x0 + 0.305, y0 - 0.115, 0.), 0.115, OdTvVector::kZAxis);

      //add circe (opposite direction)
      y0 = -2.04;
      pGeomEntity->appendCircle(OdTvPoint(x0 + 0.305, y0 - 0.115, 0.), 0.115, -OdTvVector::kZAxis);
    }

    //6. Add fourth column (filled and linetype)
    x0 = 1.06;
    y0 = -1.05;
    geometries_entity_Id = modelKeyEntity->appendSubEntity(OD_T("custom with text"));
    {
      OdTvEntityPtr pGeomEntity = geometries_entity_Id.openAsSubEntity(OdTv::kForWrite);
      pGeomEntity->setColor(OdTvColorDef(0, 0, 255), OdTvGeometryData::kEdges | OdTvGeometryData::kPolylines);
      pGeomEntity->setColor(OdTvColorDef(0, 255, 0), OdTvGeometryData::kFaces);
      pGeomEntity->setLinetype(ltId);
      pGeomEntity->setLinetypeScale(0.05);

      //add rectangle as polygon
      OdTvVisualizeSampleModelsUtils::appendRectangle(pGeomEntity, x0 - 0.02, y0 - 0.23, x0 + 0.59, y0, 0., true);

      //add rectangle as polygon (opposite direction)
      y0 = -1.38;
      OdTvVisualizeSampleModelsUtils::appendRectangle(pGeomEntity, x0 - 0.02, y0, x0 + 0.59, y0 - 0.23, 0., true);

      //add circe
      y0 = -1.71;
      pGeomEntity->appendCircle(OdTvPoint(x0 + 0.305, y0 - 0.115, 0.), 0.115, OdTvVector::kZAxis).openAsCircle()->setFilled(true);

      //add circe (opposite direction)
      y0 = -2.04;
      pGeomEntity->appendCircle(OdTvPoint(x0 + 0.305, y0 - 0.115, 0.), 0.115, -OdTvVector::kZAxis).openAsCircle()->setFilled(true);
    }
  }

  return;
}

void OdTvViewerDebugSampleModels::initLayersModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId)
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
  OdTvTextStyleId textStyle2 = pTvDb->createTextStyle(OD_T("kBottomRight"));
  {
    OdTvTextStylePtr pTextStyle = textStyle2.openObject(OdTv::kForWrite);
    pTextStyle->setAlignmentMode(OdTvTextStyle::kBottomRight);
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

      titleEntity->appendText(OdTvPoint(0.0, .75, 0.0), OD_T("Layers"));
    }

    //2. Add grid lines and write text
    OdTvVisualizeSampleModelsUtils::appendGridLines(modelKeyEntity, false, 2, 6, -1., 0.66, 0.66, 0.33);

    double x = -0.66, x0 = -0.95, x1 = 0.;
    double y0 = 0.5;
    // column's text
    OdTvGeometryDataId geometries_entity_Id_Text_col = modelKeyEntity->appendSubEntity(OD_T("edge_column_txt"));
    {
      OdTvEntityPtr pTextEntity = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity->setTextStyle(textStyle1);

      pTextEntity->appendText(OdTvPoint(x, y0 + 0.18, 0.), OD_T("kAll"));
      pTextEntity->appendText(OdTvPoint(x1, y0 + 0.18, 0.), OD_T("kEdges (transparency kFaces)"));
    }
    // row's text
    OdTvGeometryDataId geometries_entity_Id_Text_row = modelKeyEntity->appendSubEntity(OD_T("edge_row_txt"));
    {
      OdTvEntityPtr pTextEntity = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity->setTextStyle(textStyle2);

      pTextEntity->appendText(OdTvPoint(x - 0.35, y0, 0.), OD_T("Layer only with color"));
      pTextEntity->appendText(OdTvPoint(x - 0.35, y0 - 0.33, 0.), OD_T("Layer only with  linetype"));
      pTextEntity->appendText(OdTvPoint(x - 0.35, y0 - 0.66, 0.), OD_T("Layer only with lineweight"));
      pTextEntity->appendText(OdTvPoint(x - 0.35, y0 - 0.99, 0.), OD_T("Layer only with visibility"));
      pTextEntity->appendText(OdTvPoint(x - 0.35, y0 - 1.32, 0.), OD_T("Layer with transparency"));
      pTextEntity->appendText(OdTvPoint(x - 0.35, y0 - 1.65, 0.), OD_T("Layer with color, linetype, lineweight"));
    }

    //4. Create layers and linetypes
    OdTvDatabasePtr pDb = databaseId.openObject(OdTv::kForWrite);

    OdTvLayerId colorLayer0Id = pDb->createLayer(OD_T("ColorLayer0"));
    colorLayer0Id.openObject(OdTv::kForWrite)->setColor(OdTvColorDef(0, 255, 0));

    OdTvLayerId linetypeLayer0Id = pDb->createLayer(OD_T("LinetypeLayer0"));
    OdTvLinetypeId textLinetypeId = OdTvVisualizeSampleModelsUtils::generateCustomLineTypeWithText(databaseId);
    linetypeLayer0Id.openObject(OdTv::kForWrite)->setLinetype(textLinetypeId);

    OdTvLayerId lineweightLayer0Id = pDb->createLayer(OD_T("LineweightLayer0"));
    lineweightLayer0Id.openObject(OdTv::kForWrite)->setLineWeight(5);

    OdTvLayerId visibilityLayer0Id = pDb->createLayer(OD_T("InvisibleLayer0"));
    visibilityLayer0Id.openObject(OdTv::kForWrite)->setVisible(false);

    OdTvLayerId multiParamLayer0Id = OdTvVisualizeSampleModelsUtils::generateLayer(databaseId, "MultiParamLayer0", OdTvColorDef(0, 255, 0), 5, textLinetypeId, "MultiParamLayer0_description", true);

    OdTvLayerId transparencyLayer0Id = pDb->createLayer(OD_T("TransparencyLayer0"));
    transparencyLayer0Id.openObject(OdTv::kForWrite)->setTransparency(0.8);

    //5. kAll
    {
      OdTvGeometryDataId entity_Id_color0 = modelKeyEntity->appendSubEntity(OD_T("layer_1_1"));
      {
        OdTvEntityPtr pGeomEntityColor0 = entity_Id_color0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntityColor0->setLayer(colorLayer0Id);
        pGeomEntityColor0->appendPolyline(OdTvPoint(x0, y0, 0.), OdTvPoint(x0 + 0.57, y0, 0.));
      }

      OdTvGeometryDataId entity_Id_linetype0 = modelKeyEntity->appendSubEntity(OD_T("layer_1_2"));
      {
        OdTvEntityPtr pGeomEntityLinetype0 = entity_Id_linetype0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntityLinetype0->setLayer(linetypeLayer0Id);
        pGeomEntityLinetype0->setLinetypeScale(0.05);
        pGeomEntityLinetype0->appendPolyline(OdTvPoint(x0, y0 - 0.33, 0.), OdTvPoint(x0 + 0.57, y0 - 0.33, 0.));
      }

      OdTvGeometryDataId entity_Id_lineweight0 = modelKeyEntity->appendSubEntity(OD_T("layer_1_3"));
      {
        OdTvEntityPtr pGeomEntityLineweight0 = entity_Id_lineweight0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntityLineweight0->setLayer(lineweightLayer0Id);
        pGeomEntityLineweight0->appendPolyline(OdTvPoint(x0, y0 - 0.66, 0.), OdTvPoint(x0 + 0.57, y0 - 0.66, 0.));
      }

      OdTvGeometryDataId entity_Id_invisible0 = modelKeyEntity->appendSubEntity(OD_T("layer_1_4"));
      {
        OdTvEntityPtr pGeomEntityInvisible0 = entity_Id_invisible0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntityInvisible0->setLayer(visibilityLayer0Id);
        pGeomEntityInvisible0->appendPolyline(OdTvPoint(x0, y0 - 0.99, 0.), OdTvPoint(x0 + 0.57, y0 - 0.99, 0.));
      }

      OdTvGeometryDataId entity_Id_transparency0 = modelKeyEntity->appendSubEntity(OD_T("layer_1_5"));
      {
        OdTvEntityPtr pGeomEntityLayer0 = entity_Id_transparency0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntityLayer0->setLayer(transparencyLayer0Id);
        pGeomEntityLayer0->appendPolyline(OdTvPoint(x0, y0 - 1.32, 0.), OdTvPoint(x0 + 0.57, y0 - 1.32, 0.));
      }

      OdTvGeometryDataId entity_Id_multi_param0 = modelKeyEntity->appendSubEntity(OD_T("layer_1_6"));
      {
        OdTvEntityPtr pGeomEntityMultiParam0 = entity_Id_multi_param0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntityMultiParam0->setLayer(multiParamLayer0Id);
        pGeomEntityMultiParam0->setLinetypeScale(0.05);
        pGeomEntityMultiParam0->appendPolyline(OdTvPoint(x0, y0 - 1.65, 0.), OdTvPoint(x0 + 0.57, y0 - 1.65, 0.));
      }
    }

    //6. kAll and kEdges
    {
      OdTvGeometryDataId entity_Id_color1 = modelKeyEntity->appendSubEntity(OD_T("layer_2_1"));
      {
        OdTvEntityPtr pGeomEntityColor1 = entity_Id_color1.openAsSubEntity(OdTv::kForWrite);
        pGeomEntityColor1->setLayer(colorLayer0Id, OdTvGeometryData::kEdges);
        pGeomEntityColor1->appendCircle(OdGePoint3d(x1 - 0.12, y0, 0.), OdGePoint3d(x1, y0 + 0.12, 0.), OdGePoint3d(x1 + 0.12, y0, 0.));
      }

      OdTvGeometryDataId entity_Id_linetype1 = modelKeyEntity->appendSubEntity(OD_T("layer_2_2"));
      {
        OdTvEntityPtr pGeomEntityLinetype1 = entity_Id_linetype1.openAsSubEntity(OdTv::kForWrite);
        pGeomEntityLinetype1->setLayer(linetypeLayer0Id, OdTvGeometryData::kEdges);
        pGeomEntityLinetype1->setLinetypeScale(0.05);
        pGeomEntityLinetype1->appendCircleArc(OdGePoint3d(x1 - 0.24, y0 - 0.44, 0.), OdGePoint3d(x1, y0 - 0.22, 0.), OdGePoint3d(x1 + 0.24, y0 - 0.44, 0.));
      }

      OdTvGeometryDataId entity_Id_lineweight1 = modelKeyEntity->appendSubEntity(OD_T("layer_2_3"));
      {
        OdTvEntityPtr pGeomEntityLineweight1 = entity_Id_lineweight1.openAsSubEntity(OdTv::kForWrite);
        pGeomEntityLineweight1->setLayer(lineweightLayer0Id, OdTvGeometryData::kEdges);
        pGeomEntityLineweight1->appendCircleWedge(OdGePoint3d(x1 - 0.24, y0 - 0.75, 0.), OdGePoint3d(x1, y0 - 0.53, 0.), OdGePoint3d(x1 + 0.24, y0 - 0.75, 0.));
      }

      OdTvGeometryDataId entity_Id_invisible1 = modelKeyEntity->appendSubEntity(OD_T("layer_2_4"));
      {
        OdTvEntityPtr pGeomEntityInvisible1 = entity_Id_invisible1.openAsSubEntity(OdTv::kForWrite);
        pGeomEntityInvisible1->setLayer(visibilityLayer0Id, OdTvGeometryData::kEdges);
        pGeomEntityInvisible1->appendEllipse(OdGePoint3d(x1, y0 - 0.99, 0.), OdGePoint3d(x1 + 0.24, y0 - 0.99, 0.), OdGePoint3d(x1, y0 - 1.11, 0.));
      }

      OdTvGeometryDataId entity_Id_transparency1 = modelKeyEntity->appendSubEntity(OD_T("layer_2_5"));
      {
        OdTvEntityPtr pGeomEntityTransparency1 = entity_Id_transparency1.openAsSubEntity(OdTv::kForWrite);
        pGeomEntityTransparency1->setLayer(transparencyLayer0Id, OdTvGeometryData::kEdges);
        pGeomEntityTransparency1->appendEllipticArc(OdGePoint3d(x1 + 0.05, y0 - 1.31, 0.), OdGePoint3d(x1 + 0.29, y0 - 1.31, 0.), OdGePoint3d(x1 + 0.05, y0 - 1.41, 0.), 1., 4.);
      }

      OdTvGeometryDataId entity_Id_multi_param1 = modelKeyEntity->appendSubEntity(OD_T("layer_2_6"));
      {
        OdTvEntityPtr pGeomEntityMultiParam1 = entity_Id_multi_param1.openAsSubEntity(OdTv::kForWrite);
        pGeomEntityMultiParam1->setLayer(multiParamLayer0Id, OdTvGeometryData::kEdges);
        pGeomEntityMultiParam1->setLinetypeScale(0.05);
        pGeomEntityMultiParam1->appendEllipticArc(OdGePoint3d(x1 + 0.05, y0 - 1.64, 0.), OdGePoint3d(x1 + 0.29, y0 - 1.64, 0.), OdGePoint3d(x1 + 0.05, y0 - 1.74, 0.), 1., 4.);
      }

    }
  }
}

void OdTvViewerDebugSampleModels::initTransparencyModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId)
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
  OdTvTextStyleId textStyle2 = pTvDb->createTextStyle(OD_T("kBottomRight"));
  {
    OdTvTextStylePtr pTextStyle = textStyle2.openObject(OdTv::kForWrite);
    pTextStyle->setAlignmentMode(OdTvTextStyle::kBottomRight);
    pTextStyle->setTextSize(0.02);
  }

  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId modelKeyEntityId = modelPtr->appendEntity(OD_T("Transparency"));
  {
    OdTvEntityPtr modelKeyEntity = modelKeyEntityId.openObject(OdTv::kForWrite);

    //1. Add title
    OdTvGeometryDataId titleEntityId = modelKeyEntity->appendSubEntity(OD_T("title"));
    {
      OdTvEntityPtr titleEntity = titleEntityId.openAsSubEntity(OdTv::kForWrite);
      titleEntity->setColor(OdTvColorDef(128, 000, 128), OdTvGeometryData::kAll);
      titleEntity->setLineWeight(2);
      titleEntity->setTextStyle(textStyle);

      titleEntity->appendText(OdTvPoint(0.0, .75, 0.0), OD_T("Transparency"));
    }

    //2. Add grid lines
    OdTvVisualizeSampleModelsUtils::appendGridLines(modelKeyEntity, false, 2, 7, -1., 0.66, 0.66, 0.33);

    double x0 = -0.66, x1 = 0.;
    double y0 = 0.5;

    // column's text
    OdTvGeometryDataId geometries_entity_Id_Text_col = modelKeyEntity->appendSubEntity(OD_T("face_column_txt"));
    {
      OdTvEntityPtr pTextEntity0 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity0->setTextStyle(textStyle1);

      pTextEntity0->appendText(OdTvPoint(x0, y0 + 0.18, 0.), OD_T("Entity"));
      pTextEntity0->appendText(OdTvPoint(x1, y0 + 0.18, 0.), OD_T("Geometry"));
    }
    // row's text
    OdTvGeometryDataId geometries_entity_Id_Text_row = modelKeyEntity->appendSubEntity(OD_T("face_row_txt"));
    {
      OdTvEntityPtr pTextEntity0 = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity0->setTextStyle(textStyle2);

      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0, 0.), OD_T("Circle"));
      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0 - 0.33, 0.), OD_T("Lines"));
      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0 - 0.66, 0.), OD_T("Text"));
      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0 - 0.99, 0.), OD_T("Shell"));
      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0 - 1.31, 0.), OD_T("Mesh"));
      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0 - 1.64, 0.), OD_T("Shell setViaRange"));
      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0 - 1.97, 0.), OD_T("Mesh setViaRange"));
    }

    //3. Create entities
    OdTvGeometryDataId geometries_entity_face_transp_Id = modelKeyEntity->appendSubEntity(OD_T("face_transp_entity"));
    OdTvEntityPtr pGeomEntityTranspFace = geometries_entity_face_transp_Id.openAsSubEntity(OdTv::kForWrite);
    pGeomEntityTranspFace->setTransparency(0.8, OdTvGeometryData::kFaces);

    OdTvGeometryDataId geometries_entity_line_transp_Id = modelKeyEntity->appendSubEntity(OD_T("line_transp_entity"));
    OdTvEntityPtr pGeomEntityTranspLine = geometries_entity_line_transp_Id.openAsSubEntity(OdTv::kForWrite);
    pGeomEntityTranspLine->setTransparency(0.8, OdTvGeometryData::kPolylines);

    OdTvGeometryDataId geometries_entity_text_transp_Id = modelKeyEntity->appendSubEntity(OD_T("text_transp_entity"));
    OdTvEntityPtr pGeomEntityTranspText = geometries_entity_text_transp_Id.openAsSubEntity(OdTv::kForWrite);
    pGeomEntityTranspText->setTransparency(0.8, OdTvGeometryData::kText);

    OdTvGeometryDataId geometries_entity_Id = modelKeyEntity->appendSubEntity(OD_T("entity"));
    OdTvEntityPtr pGeomEntity = geometries_entity_Id.openAsSubEntity(OdTv::kForWrite);

    OdTvGeometryDataId additional_entity_Id = modelKeyEntity->appendSubEntity(OD_T("entity"));
    OdTvEntityPtr pAdditionalEntity = additional_entity_Id.openAsSubEntity(OdTv::kForWrite);

    //4. Add filled geometry
    {
      pGeomEntityTranspFace->appendCircle(OdTvPoint(x0, y0, 0.), 0.1, OdTvVector::kZAxis).openAsCircle()->setFilled(true);

      OdTvGeometryDataId fiiledCircleId1 = pGeomEntity->appendCircle(OdTvPoint(x1, y0, 0.), 0.1, OdTvVector::kZAxis);
      fiiledCircleId1.openAsCircle()->setFilled(true);
      fiiledCircleId1.openObject()->setTransparency(0.8);
    }

    //5. Add polyline
    y0 -= 0.33;
    {
      pGeomEntityTranspLine->appendPolyline(OdTvPoint(x0 - 0.2, y0 - 0.05, 0.), OdTvPoint(x0 + 0.2, y0 + 0.05, 0.));

      pGeomEntity->appendPolyline(OdTvPoint(x1 - 0.2, y0 - 0.05, 0.), OdTvPoint(x1 + 0.2, y0 + 0.05, 0.)).openObject()->setTransparency(0.8);
    }

    //6. Add text
    y0 -= 0.33;
    {
      pGeomEntityTranspText->appendText(OdTvPoint(x0 - 0.1, y0, 0.), OD_T("Text")).openAsText()->setTextSize(0.05);

      OdTvGeometryDataId textId = pGeomEntity->appendText(OdTvPoint(x1 - 0.1, y0, 0.), OD_T("Text"));
      textId.openObject()->setTransparency(0.8);
      textId.openAsText()->setTextSize(0.05);
    }

    //7. Add shell
    y0 -= 0.33;
    {
      pGeomEntityTranspFace->appendShellFromSphere(OdTvPoint(x0, y0, 0.), 0.1);

      pGeomEntity->appendShellFromSphere(OdTvPoint(x1, y0, 0.), 0.1).openObject()->setTransparency(0.8);
    }

    //8. Add meshes
    y0 -= 0.33;
    {
      OdTvPointArray points0;
      OdTvVisualizeSampleModelsUtils::generateMeshVertices(x0 - 0.05, y0, points0);
      pGeomEntityTranspFace->appendMesh(3, 4, points0);

      OdTvPointArray points1;
      OdTvVisualizeSampleModelsUtils::generateMeshVertices(x1 - 0.05, y0, points1);
      pGeomEntity->appendMesh(3, 4, points1).openObject()->setTransparency(0.8);
    }

    OdTvGeometryDataId crossEntityId = modelKeyEntity->appendSubEntity(OD_T("cross"));
    OdTvEntityPtr crossEntity = crossEntityId.openAsSubEntity(OdTv::kForWrite);

    //9. Shell with setViaRange
    y0 -= 0.33;
    {
      OdTvGeometryDataId textId = crossEntity->appendText(OdTvPoint(x0 - 0.12, y0, 0.), OD_T("nothing"));
      textId.openAsText()->setTextSize(0.05);

      OdTvGeometryDataId shellId1 = pGeomEntity->appendShellFromSphere(OdTvPoint(x1, y0, 0.), 0.1);
      OdTvShellDataPtr pShellData = shellId1.openAsShell();
      pShellData->setFaceTransparencyViaRange(0, pShellData->getFacesCount() / 2, 0.8);

      pAdditionalEntity->appendShellFromSphere(OdTvPoint(x1, y0, 0.), 0.05).openObject()->setColor(OdTvColorDef(255, 0, 0));
    }

    //10. Mesh with setViaList
    y0 -= 0.33;
    {
      OdTvGeometryDataId textId = crossEntity->appendText(OdTvPoint(x0 - 0.12, y0, 0.), OD_T("nothing"));
      textId.openAsText()->setTextSize(0.05);

      OdTvPointArray points1;
      OdTvVisualizeSampleModelsUtils::generateMeshVertices(x1 - 0.05, y0, points1);
      OdInt32Array indFaces;
      indFaces.append(0);
      indFaces.append(1);
      pGeomEntity->appendMesh(3, 4, points1).openAsMesh()->setFaceTransparencyViaList(indFaces, 0.8);
    }

  }

}

void OdTvViewerDebugSampleModels::initShellFacesAttributesModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId)
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
  OdTvTextStyleId textStyle2 = pTvDb->createTextStyle(OD_T("kBottomRight"));
  {
    OdTvTextStylePtr pTextStyle = textStyle2.openObject(OdTv::kForWrite);
    pTextStyle->setAlignmentMode(OdTvTextStyle::kBottomRight);
    pTextStyle->setTextSize(0.02);
  }

  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId modelKeyEntityId = modelPtr->appendEntity(OD_T("Shell's faces"));
  {
    OdTvEntityPtr modelKeyEntity = modelKeyEntityId.openObject(OdTv::kForWrite);

    //1. Add title
    OdTvGeometryDataId titleEntityId = modelKeyEntity->appendSubEntity(OD_T("title"));
    {
      OdTvEntityPtr titleEntity = titleEntityId.openAsSubEntity(OdTv::kForWrite);
      titleEntity->setColor(OdTvColorDef(128, 000, 128), OdTvGeometryData::kAll);
      titleEntity->setLineWeight(2);
      titleEntity->setTextStyle(textStyle);

      titleEntity->appendText(OdTvPoint(0.0, .75, 0.0), OD_T("Shell's faces attributes"));
    }

    //2. Add grid lines
    OdTvVisualizeSampleModelsUtils::appendGridLines(modelKeyEntity, false, 3, 4, -1., 0.66, 0.66, 0.33);

    double x0 = -0.66, x1 = 0., x2 = 0.66;
    double y0 = 0.5;
    double shellRadius = 0.14;

    // column's text
    OdTvGeometryDataId geometries_entity_Id_Text_col = modelKeyEntity->appendSubEntity(OD_T("face_column_txt"));
    {
      OdTvEntityPtr pTextEntity0 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity0->setTextStyle(textStyle1);

      pTextEntity0->appendText(OdTvPoint(x0, y0 + 0.18, 0.), OD_T("kFaces"));
      pTextEntity0->appendText(OdTvPoint(x1, y0 + 0.18, 0.), OD_T("All filled"));
      pTextEntity0->appendText(OdTvPoint(x2, y0 + 0.18, 0.), OD_T("50 filled"));
    }
    // row's text
    OdTvGeometryDataId geometries_entity_Id_Text_row = modelKeyEntity->appendSubEntity(OD_T("face_row_txt"));
    {
      OdTvEntityPtr pTextEntity0 = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity0->setTextStyle(textStyle2);

      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0, 0.), OD_T("Colors"));
      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0 - 0.33, 0.), OD_T("Layers with color"));
      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0 - 0.66, 0.), OD_T("Visibilities"));
      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0 - 0.99, 0.), OD_T("Transparency"));
    }

    //3. Color attribute
    {
      OdTvGeometryDataId geometries_entity_Id_color0 = modelKeyEntity->appendSubEntity(OD_T("face_col_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_color0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setColor(OdTvColorDef(255, 0, 0), OdTvGeometryData::kFaces);

        OdTvGeometryDataId shell0Id = pGeomEntity0->appendShellFromSphere(OdTvPoint(x0, y0, 0.), shellRadius);
      }

      OdTvGeometryDataId geometries_entity_Id_color1 = modelKeyEntity->appendSubEntity(OD_T("face_col_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_color1.openAsSubEntity(OdTv::kForWrite);

        OdTvGeometryDataId shell1Id = pGeomEntity1->appendShellFromSphere(OdTvPoint(x1, y0, 0.), shellRadius);
        OdTvShellDataPtr shell1Ptr = shell1Id.openAsShell();
        shell1Ptr->setFaceColorsViaRange(0, shell1Ptr->getFacesCount(), OdTvColorDef(255, 0, 0));
      }

      OdTvGeometryDataId geometries_entity_Id_color2 = modelKeyEntity->appendSubEntity(OD_T("face_col_2"));
      {
        OdTvEntityPtr pGeomEntity2 = geometries_entity_Id_color2.openAsSubEntity(OdTv::kForWrite);

        OdTvGeometryDataId shell2Id = pGeomEntity2->appendShellFromSphere(OdTvPoint(x2, y0, 0.), shellRadius);
        OdTvShellDataPtr shell2Ptr = shell2Id.openAsShell();
        shell2Ptr->setFaceColorsViaRange(0, 50, OdTvColorDef(255, 0, 0));
      }
    }

    // 4. Layer attributes
    y0 -= 0.33;
    {
      OdTvDatabasePtr pDb = databaseId.openObject(OdTv::kForWrite);
      OdTvLayerId layerId = pDb->createLayer(OD_T("Green_layer"));
      OdTvLayerPtr layerPtr = layerId.openObject(OdTv::kForWrite);
      layerPtr->setColor(OdTvColorDef(0, 255, 0));


      OdTvGeometryDataId geometries_entity_Id_layer0 = modelKeyEntity->appendSubEntity(OD_T("face_lay_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_layer0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setLayer(layerId, OdTvGeometryData::kFaces);

        OdTvGeometryDataId shell0Id = pGeomEntity0->appendShellFromSphere(OdTvPoint(x0, y0, 0.), shellRadius);
      }

      OdTvGeometryDataId geometries_entity_Id_layer1 = modelKeyEntity->appendSubEntity(OD_T("face_lay_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_layer1.openAsSubEntity(OdTv::kForWrite);

        OdTvGeometryDataId shell1Id = pGeomEntity1->appendShellFromSphere(OdTvPoint(x1, y0, 0.), shellRadius);
        OdTvShellDataPtr shell1Ptr = shell1Id.openAsShell();
        shell1Ptr->setFaceLayersViaRange(0, shell1Ptr->getFacesCount(), layerId);
      }

      OdTvGeometryDataId geometries_entity_Id_layer2 = modelKeyEntity->appendSubEntity(OD_T("face_lay_2"));
      {
        OdTvEntityPtr pGeomEntity2 = geometries_entity_Id_layer2.openAsSubEntity(OdTv::kForWrite);

        OdTvGeometryDataId shell2Id = pGeomEntity2->appendShellFromSphere(OdTvPoint(x2, y0, 0.), shellRadius);
        OdTvShellDataPtr shell2Ptr = shell2Id.openAsShell();
        shell2Ptr->setFaceLayersViaRange(0, 50, layerId);
      }
    }

    // 5. Visibility attributes
    y0 -= 0.33;
    {
      OdTvGeometryDataId geometries_entity_Id_visibility0 = modelKeyEntity->appendSubEntity(OD_T("face_vis_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_visibility0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setVisibility(OdTvVisibilityDef(false), OdTvGeometryData::kFaces);

        pGeomEntity0->appendShellFromSphere(OdTvPoint(x0, y0, 0.), shellRadius);
      }

      OdTvGeometryDataId geometries_entity_Id_visibility1 = modelKeyEntity->appendSubEntity(OD_T("face_vis_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_visibility1.openAsSubEntity(OdTv::kForWrite);

        OdTvGeometryDataId shell1Id = pGeomEntity1->appendShellFromSphere(OdTvPoint(x1, y0, 0.), shellRadius);
        OdTvShellDataPtr shell1Ptr = shell1Id.openAsShell();
        shell1Ptr->setFaceVisibilitiesViaRange(0, shell1Ptr->getFacesCount(), OdTvVisibilityDef(false));
      }

      OdTvGeometryDataId geometries_entity_Id_visibility2 = modelKeyEntity->appendSubEntity(OD_T("face_vis_2"));
      {
        OdTvEntityPtr pGeomEntity2 = geometries_entity_Id_visibility2.openAsSubEntity(OdTv::kForWrite);

        OdTvGeometryDataId shell2Id = pGeomEntity2->appendShellFromSphere(OdTvPoint(x2, y0, 0.), shellRadius);
        OdTvShellDataPtr shell2Ptr = shell2Id.openAsShell();
        shell2Ptr->setFaceVisibilitiesViaRange(0, 50, OdTvVisibilityDef(false));

        pGeomEntity2->appendShellFromSphere(OdTvPoint(x2, y0, 0.), shellRadius / 2.).openObject()->setColor(OdTvColorDef(255, 0, 0));
      }
    }

    //6. Transparency
    y0 -= 0.33;
    {
      OdTvGeometryDataId geometries_entity_Id_transparency0 = modelKeyEntity->appendSubEntity(OD_T("face_transparency_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_transparency0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setTransparency(0.7, OdTvGeometryData::kFaces);

        pGeomEntity0->appendShellFromSphere(OdTvPoint(x0, y0, 0.), shellRadius);
      }

      OdTvGeometryDataId geometries_entity_Id_transparency1 = modelKeyEntity->appendSubEntity(OD_T("face_transparency_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_transparency1.openAsSubEntity(OdTv::kForWrite);

        OdTvGeometryDataId shell1Id = pGeomEntity1->appendShellFromSphere(OdTvPoint(x1, y0, 0.), shellRadius);
        OdTvShellDataPtr shell1Ptr = shell1Id.openAsShell();
        shell1Ptr->setFaceTransparencyViaRange(0, shell1Ptr->getFacesCount(), 0.7);
      }

      OdTvGeometryDataId geometries_entity_Id_transparency2 = modelKeyEntity->appendSubEntity(OD_T("face_transparency_2"));
      {
        OdTvEntityPtr pGeomEntity2 = geometries_entity_Id_transparency2.openAsSubEntity(OdTv::kForWrite);

        OdTvGeometryDataId shell2Id = pGeomEntity2->appendShellFromSphere(OdTvPoint(x2, y0, 0.), shellRadius);
        OdTvShellDataPtr shell2Ptr = shell2Id.openAsShell();
        shell2Ptr->setFaceTransparencyViaRange(0, 50, 0.7);

        pGeomEntity2->appendShellFromSphere(OdTvPoint(x2, y0, 0.), shellRadius / 2.).openObject()->setColor(OdTvColorDef(255, 0, 0));
      }
    }

  }
}

void OdTvViewerDebugSampleModels::initLightModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId)
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

    //1. Add title
    OdTvGeometryDataId titleEntityId = modelKeyEntity->appendSubEntity(OD_T("title"));
    {
      OdTvEntityPtr titleEntity = titleEntityId.openAsSubEntity(OdTv::kForWrite);
      titleEntity->setColor(OdTvColorDef(128, 000, 128), OdTvGeometryData::kAll);
      titleEntity->setLineWeight(2);
      titleEntity->setTextStyle(textStyle);

      titleEntity->appendText(OdTvPoint(0.0, 1.2, 0.0), OD_T("Light"));
    }

    //2. Add geometry and light
    OdTvGeometryDataId geometries_entity_Id = modelKeyEntity->appendSubEntity(OD_T("entity0"));
    {
      OdTvEntityPtr pGrometryEntity = geometries_entity_Id.openAsSubEntity(OdTv::kForWrite);

      pGrometryEntity->appendShellFromSphere(OdTvPoint::kOrigin, 1., OdTvVector::kYAxis, OdTvVector::kXAxis, 200).openObject()->setColor(OdTvColorDef(128, 128, 128));

      OdTvEntityId light0Id = modelPtr->appendLight(OD_T("Light0"));
      OdTvLightPtr pLight0 = light0Id.openObjectAsLight(OdTv::kForWrite);
      pLight0->setPosition(OdTvPoint(-2., 1., 2.));
      pLight0->setTargetLocation(OdTvPoint(0., 0., 0.));
      pLight0->setLightColor(OdTvColorDef(255, 0, 0));
      pLight0->setIntensity(3.);
      pLight0->setHotspotAndFalloff(OdaPI4, 11. * OdaPI4 / 10.);

      OdTvEntityId light1Id = modelPtr->appendLight(OD_T("Light1"));
      OdTvLightPtr pLight1 = light1Id.openObjectAsLight(OdTv::kForWrite);
      pLight1->setPosition(OdTvPoint(2., 1., 2.));
      pLight1->setLightColor(OdTvColorDef(0, 255, 0));
      pLight1->setTargetLocation(OdTvPoint(0., 0., 0.));
      pLight1->setIntensity(3.);
      pLight1->setHotspotAndFalloff(OdaPI4, 11. * OdaPI4 / 10.);

      OdTvEntityId light2Id = modelPtr->appendLight(OD_T("Light2"));
      OdTvLightPtr pLight2 = light2Id.openObjectAsLight(OdTv::kForWrite);
      pLight2->setPosition(OdTvPoint(0., -1., 2.));
      pLight2->setLightColor(OdTvColorDef(0, 0, 255));
      pLight2->setTargetLocation(OdTvPoint(0., 0., 0.));
      pLight2->setIntensity(3.);
      pLight2->setHotspotAndFalloff(OdaPI4, 11. * OdaPI4 / 10.);
    }
  }

}

void OdTvViewerDebugSampleModels::initShellEdgesAttributesModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId)
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
  OdTvTextStyleId textStyle2 = pTvDb->createTextStyle(OD_T("kBottomRight"));
  {
    OdTvTextStylePtr pTextStyle = textStyle2.openObject(OdTv::kForWrite);
    pTextStyle->setAlignmentMode(OdTvTextStyle::kBottomRight);
    pTextStyle->setTextSize(0.02);
  }

  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId modelKeyEntityId = modelPtr->appendEntity(OD_T("Shell's edges"));
  {
    OdTvEntityPtr modelKeyEntity = modelKeyEntityId.openObject(OdTv::kForWrite);

    //1. Add title
    OdTvGeometryDataId titleEntityId = modelKeyEntity->appendSubEntity(OD_T("title"));
    {
      OdTvEntityPtr titleEntity = titleEntityId.openAsSubEntity(OdTv::kForWrite);
      titleEntity->setColor(OdTvColorDef(128, 000, 128), OdTvGeometryData::kAll);
      titleEntity->setLineWeight(2);
      titleEntity->setTextStyle(textStyle);

      titleEntity->appendText(OdTvPoint(0.0, .75, 0.0), OD_T("Shell's edges attributes"));
    }

    //2. Add grid lines
    OdTvVisualizeSampleModelsUtils::appendGridLines(modelKeyEntity, false, 3, 4, -1., 0.66, 0.66, 0.33);

    double x0 = -0.66, x1 = 0., x2 = 0.66;
    double y0 = 0.5;
    double shellRadius = 0.14;

    // column's text
    OdTvGeometryDataId geometries_entity_Id_Text_col = modelKeyEntity->appendSubEntity(OD_T("edge_column_txt"));
    {
      OdTvEntityPtr pTextEntity = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity->setTextStyle(textStyle1);

      pTextEntity->appendText(OdTvPoint(x0, y0 + 0.18, 0.), OD_T("kEdges"));
      pTextEntity->appendText(OdTvPoint(x1, y0 + 0.18, 0.), OD_T("All filled"));
      pTextEntity->appendText(OdTvPoint(x2, y0 + 0.18, 0.), OD_T("400 filled"));
    }
    // row's text
    OdTvGeometryDataId geometries_entity_Id_Text_row = modelKeyEntity->appendSubEntity(OD_T("edge_row_txt"));
    {
      OdTvEntityPtr pTextEntity = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity->setTextStyle(textStyle2);

      pTextEntity->appendText(OdTvPoint(x0 - 0.35, y0, 0.), OD_T("Colors"));
      pTextEntity->appendText(OdTvPoint(x0 - 0.35, y0 - 0.33, 0.), OD_T("Layers with color"));
      pTextEntity->appendText(OdTvPoint(x0 - 0.35, y0 - 0.66, 0.), OD_T("Visibilities"));
      pTextEntity->appendText(OdTvPoint(x0 - 0.35, y0 - 0.99, 0.), OD_T("Linetypes"));
    }

    //3. Color attribute
    {
      OdTvGeometryDataId geometries_entity_Id_color0 = modelKeyEntity->appendSubEntity(OD_T("edge_col_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_color0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setColor(OdTvColorDef(255, 0, 0), OdTvGeometryData::kEdges);

        pGeomEntity0->appendShellFromSphere(OdTvPoint(x0, y0, 0.), shellRadius);;
      }

      OdTvGeometryDataId geometries_entity_Id_color1 = modelKeyEntity->appendSubEntity(OD_T("edge_col_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_color1.openAsSubEntity(OdTv::kForWrite);

        OdTvGeometryDataId shell1Id = pGeomEntity1->appendShellFromSphere(OdTvPoint(x1, y0, 0.), shellRadius);
        OdTvShellDataPtr shell1Ptr = shell1Id.openAsShell();
        shell1Ptr->setEdgeColorsViaRange(0, shell1Ptr->getEdgesCount(), OdTvColorDef(255, 0, 0));
      }

      OdTvGeometryDataId geometries_entity_Id_color2 = modelKeyEntity->appendSubEntity(OD_T("edge_col_2"));
      {
        OdTvEntityPtr pGeomEntity2 = geometries_entity_Id_color2.openAsSubEntity(OdTv::kForWrite);

        OdTvGeometryDataId shell2Id = pGeomEntity2->appendShellFromSphere(OdTvPoint(x2, y0, 0.), shellRadius);
        OdTvShellDataPtr shell2Ptr = shell2Id.openAsShell();
        shell2Ptr->setEdgeColorsViaRange(0, 400, OdTvColorDef(255, 0, 0));
      }
    }

    // 4. Layer attributes
    y0 -= 0.33;
    {
      OdTvDatabasePtr pDb = databaseId.openObject(OdTv::kForWrite);
      OdTvLayerId layerId = pDb->createLayer(OD_T("Green_layer"));
      OdTvLayerPtr layerPtr = layerId.openObject(OdTv::kForWrite);
      layerPtr->setColor(OdTvColorDef(0, 255, 0));

      OdTvGeometryDataId geometries_entity_Id_layer0 = modelKeyEntity->appendSubEntity(OD_T("edge_lay_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_layer0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setLayer(layerId, OdTvGeometryData::kEdges);

        pGeomEntity0->appendShellFromSphere(OdTvPoint(x0, y0, 0.), shellRadius);
      }

      OdTvGeometryDataId geometries_entity_Id_layer1 = modelKeyEntity->appendSubEntity(OD_T("edge_lay_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_layer1.openAsSubEntity(OdTv::kForWrite);

        OdTvGeometryDataId shell1Id = pGeomEntity1->appendShellFromSphere(OdTvPoint(x1, y0, 0.), shellRadius);
        OdTvShellDataPtr shell1Ptr = shell1Id.openAsShell();
        shell1Ptr->setEdgeLayersViaRange(0, shell1Ptr->getEdgesCount(), layerId);
      }

      OdTvGeometryDataId geometries_entity_Id_layer2 = modelKeyEntity->appendSubEntity(OD_T("edge_lay_2"));
      {
        OdTvEntityPtr pGeomEntity2 = geometries_entity_Id_layer2.openAsSubEntity(OdTv::kForWrite);

        OdTvGeometryDataId shell2Id = pGeomEntity2->appendShellFromSphere(OdTvPoint(x2, y0, 0.), shellRadius);
        OdTvShellDataPtr shell2Ptr = shell2Id.openAsShell();
        shell2Ptr->setEdgeLayersViaRange(0, 400, layerId);
      }
    }

    // 5. Visibility attributes
    y0 -= 0.33;
    {
      OdTvGeometryDataId geometries_entity_Id_visibility0 = modelKeyEntity->appendSubEntity(OD_T("edge_vis_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_visibility0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setVisibility(OdTvVisibilityDef(false), OdTvGeometryData::kEdges);

        pGeomEntity0->appendShellFromSphere(OdTvPoint(x0, y0, 0.), shellRadius);
      }

      OdTvGeometryDataId geometries_entity_Id_visibility1 = modelKeyEntity->appendSubEntity(OD_T("edge_vis_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_visibility1.openAsSubEntity(OdTv::kForWrite);

        OdTvGeometryDataId shell1Id = pGeomEntity1->appendShellFromSphere(OdTvPoint(x1, y0, 0.), shellRadius);
        OdTvShellDataPtr shell1Ptr = shell1Id.openAsShell();
        shell1Ptr->setEdgeVisibilitiesViaRange(0, shell1Ptr->getEdgesCount(), OdTvVisibilityDef(false));
      }

      OdTvGeometryDataId geometries_entity_Id_visibility2 = modelKeyEntity->appendSubEntity(OD_T("edge_vis_2"));
      {
        OdTvEntityPtr pGeomEntity2 = geometries_entity_Id_visibility2.openAsSubEntity(OdTv::kForWrite);

        OdTvGeometryDataId shell2Id = pGeomEntity2->appendShellFromSphere(OdTvPoint(x2, y0, 0.), shellRadius);
        OdTvShellDataPtr shell2Ptr = shell2Id.openAsShell();
        OdInt32Array indPos;
        for (OdInt32 i = 0; i < (OdInt32)shell2Ptr->getEdgesCount(); i++)
        {
          if (i % 3 != 0)
            indPos.append(i);
        }
        shell2Ptr->setEdgeVisibilitiesViaList(indPos, OdTvVisibilityDef(false));
      }
    }

    // 6. Linetype attribute
    y0 -= 0.33;
    {
      OdTvGeometryDataId geometries_entity_Id_linetype0 = modelKeyEntity->appendSubEntity(OD_T("edge_lt_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_linetype0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setLinetype(OdTvLinetype::kDashed, OdTvGeometryData::kEdges);
        pGeomEntity0->setLinetypeScale(0.05);

        pGeomEntity0->appendShellFromSphere(OdTvPoint(x0, y0, 0.), shellRadius);
      }

      OdTvGeometryDataId geometries_entity_Id_linetype1 = modelKeyEntity->appendSubEntity(OD_T("edge_lt_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_linetype1.openAsSubEntity(OdTv::kForWrite);

        OdTvGeometryDataId shell1Id = pGeomEntity1->appendShellFromSphere(OdTvPoint(x1, y0, 0.), shellRadius);
        OdTvGeometryDataPtr shell1Ptr = shell1Id.openObject();
        shell1Ptr->getAsShell()->setEdgeLinetypesViaRange(0, shell1Ptr->getAsShell()->getEdgesCount(), OdTvLinetype::kDashed);
        shell1Ptr->setLinetypeScale(0.05);
      }

      OdTvGeometryDataId geometries_entity_Id_linetype2 = modelKeyEntity->appendSubEntity(OD_T("edge_lt_2"));
      {
        OdTvEntityPtr pGeomEntity2 = geometries_entity_Id_linetype2.openAsSubEntity(OdTv::kForWrite);

        OdTvGeometryDataId shell2Id = pGeomEntity2->appendShellFromSphere(OdTvPoint(x2, y0, 0.), shellRadius);
        OdTvGeometryDataPtr shell2Ptr = shell2Id.openObject();
        shell2Ptr->getAsShell()->setEdgeLinetypesViaRange(0, 400, OdTvLinetype::kDashed);
        shell2Ptr->setLinetypeScale(0.05);
      }
    }

  }
}

void OdTvViewerDebugSampleModels::initMaterialsModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId, const OdString& strResourceFolder)
{
  //generate text style
  OdTvDatabasePtr pTvDb = databaseId.openObject();
  OdTvTextStyleId textStyle = pTvDb->createTextStyle(OD_T("kMiddleCenter"));
  {
    OdTvTextStylePtr pTextStyle = textStyle.openObject(OdTv::kForWrite);
    pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleCenter);
    pTextStyle->setTextSize(0.02);
  }
  OdTvTextStyleId textStyle1 = pTvDb->createTextStyle(OD_T("kMiddleRight"));
  {
    OdTvTextStylePtr pTextStyle = textStyle1.openObject(OdTv::kForWrite);
    pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleRight);
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

      titleEntity->appendText(OdTvPoint(0.0, 2., 0.0), OD_T("Materials")).openAsText()->setTextSize(0.3);
    }

    OdTvGeometryDataId entityText_Id = modelKeyEntity->appendSubEntity(OD_T("Text"));
    OdTvEntityPtr pTextEntity = entityText_Id.openAsSubEntity(OdTv::kForWrite);
    pTextEntity->setTextStyle(textStyle1);

    //2. Teapot examples 
    double y = 0;
    OdTvGeometryDataId entityTeapot_Id = modelKeyEntity->appendSubEntity(OD_T("Teapot"));
    {
      OdTvEntityPtr pTeapotEntity = entityTeapot_Id.openAsSubEntity(OdTv::kForWrite);

      OdTvShellDataPtr pShell;
      OdTvPoint2dArray mappingCoords;

      OdTvVisualizeSampleModelsTeapot::drawTeapot(pShell, mappingCoords, pTeapotEntity, 0., y, 0.);

      pShell->setFaceColorsViaRange(0, pShell->getFacesCount(), OdTvColorDef(0, 0, 255));

      pTextEntity->appendText(OdTvPoint(-1., y, 0), OD_T("Without materials")).openAsText()->setTextSize(0.3);
    }

    //2.1 Red Diffuse
    y -= 2.;
    OdTvGeometryDataId entityTeapot0_Id = modelKeyEntity->appendSubEntity(OD_T("Teapot0"));
    {
      OdTvEntityPtr pTeapotEntity = entityTeapot0_Id.openAsSubEntity(OdTv::kForWrite);

      OdTvShellDataPtr pShell;
      OdTvPoint2dArray mappingCoords;

      // Draw shell and get mapping coordinates
      OdTvVisualizeSampleModelsTeapot::drawTeapot(pShell, mappingCoords, pTeapotEntity, 0., y, 0.);

      // Create material with unique name
      OdTvMaterialId materialId = pTvDb->createMaterial("Material0");
      OdTvMaterialPtr pMaterial = materialId.openObject(OdTv::kForWrite);
      // Create empty map for diffuse
      OdTvMaterialMap materialMap;
      // Set diffuse to material
      pMaterial->setDiffuse(OdTvMaterialColor(OdTvColorDef(255, 0, 0)), materialMap);

      // Set material to shell
      pShell->setFaceMaterialsViaRange(0, pShell->getFacesCount(), materialId);

      pTextEntity->appendText(OdTvPoint(-1., y, 0), OD_T("Red Diffuse")).openAsText()->setTextSize(0.3);
    }

    //2.2 Green Diffuse with blue Ambient
    y -= 2.;
    OdTvGeometryDataId entityTeapot1_Id = modelKeyEntity->appendSubEntity(OD_T("Teapot1"));
    {
      OdTvEntityPtr pTeapotEntity = entityTeapot1_Id.openAsSubEntity(OdTv::kForWrite);

      OdTvShellDataPtr pShell;
      OdTvPoint2dArray mappingCoords;

      // Draw shell and get mapping coordinates
      OdTvVisualizeSampleModelsTeapot::drawTeapot(pShell, mappingCoords, pTeapotEntity, 0., y, 0.);

      // Create material with unique name
      OdTvMaterialId materialId = pTvDb->createMaterial("Material1");
      OdTvMaterialPtr pMaterial = materialId.openObject(OdTv::kForWrite);
      // Create empty map for diffuse
      OdTvMaterialMap materialMap;
      pMaterial->setDiffuse(OdTvMaterialColor(OdTvColorDef(0, 255, 0)), materialMap);
      pMaterial->setAmbient(OdTvMaterialColor(OdTvColorDef(0, 0, 255)));

      pShell->setFaceMaterialsViaRange(0, pShell->getFacesCount(), materialId);

      pTextEntity->appendText(OdTvPoint(-1., y, 0), OD_T("Green Diffuse with blue Ambient")).openAsText()->setTextSize(0.3);
    }

    //2.3 Red Diffuse with 0.5 blue Specular
    y -= 2.;
    OdTvGeometryDataId entityTeapot2_Id = modelKeyEntity->appendSubEntity(OD_T("Teapot2"));
    {
      OdTvEntityPtr pTeapotEntity = entityTeapot2_Id.openAsSubEntity(OdTv::kForWrite);

      OdTvShellDataPtr pShell;
      OdTvPoint2dArray mappingCoords;

      // Draw shell and get mapping coordinates
      OdTvVisualizeSampleModelsTeapot::drawTeapot(pShell, mappingCoords, pTeapotEntity, 0., y, 0.);

      // Create material with unique name
      OdTvMaterialId materialId = pTvDb->createMaterial("Material2");
      OdTvMaterialPtr pMaterial = materialId.openObject(OdTv::kForWrite);
      // Create empty map for diffuse
      OdTvMaterialMap materialMap;
      pMaterial->setDiffuse(OdTvMaterialColor(OdTvColorDef(255, 0, 0)), materialMap);
      pMaterial->setSpecular(OdTvMaterialColor(OdTvColorDef(0, 0, 255)), 0.5);

      pShell->setFaceMaterialsViaRange(0, pShell->getFacesCount(), materialId);

      pTextEntity->appendText(OdTvPoint(-1., y, 0), OD_T("Red Diffuse with 0.5 blue Specular")).openAsText()->setTextSize(0.3);
    }

    //2.4 Texture by mapping coordinates
    y -= 2.;
    OdTvGeometryDataId entityTeapot3_Id = modelKeyEntity->appendSubEntity(OD_T("Teapot3"));
    {
      OdTvEntityPtr pTeapotEntity = entityTeapot3_Id.openAsSubEntity(OdTv::kForWrite);

      OdTvShellDataPtr pShell;
      OdTvPoint2dArray mappingCoords;

      // Draw shell and get mapping coordinates
      OdTvVisualizeSampleModelsTeapot::drawTeapot(pShell, mappingCoords, pTeapotEntity, 0., y, 0.);

      // Create material with unique name
      OdTvMaterialId materialId = pTvDb->createMaterial("Material3");
      OdTvMaterialPtr pMaterial = materialId.openObject(OdTv::kForWrite);
      // Create path to texture image file
      OdString texturePath = OdTvVisualizeSampleModelsUtils::formatPath(strResourceFolder, OD_T("textures/marble.png"));

      // Create material map and set texture to map
      OdTvMaterialMap materialMap;
      materialMap.setSourceFileName(texturePath);
      // Set material map to material
      pMaterial->setDiffuse(OdTvMaterialColor(OdTvColorDef(255, 0, 0)), materialMap);

      // Set material and mapping coordinates to shell
      pShell->setFaceMaterialsViaRange(0, pShell->getFacesCount(), materialId);
      pShell->setVertexMappingCoordsViaRange(0, mappingCoords);

      pTextEntity->appendText(OdTvPoint(-1., y, 0), OD_T("Texture by mapping coordinates")).openAsText()->setTextSize(0.3);
    }

    //2.5 Texture by sphere mapping
    y -= 2.;
    OdTvGeometryDataId entitySphere4_Id = modelKeyEntity->appendSubEntity(OD_T("Sphere4"));
    {
      OdTvEntityPtr pSphereEntity = entitySphere4_Id.openAsSubEntity(OdTv::kForWrite);
      OdTvGeometryDataId sphereId = pSphereEntity->appendShellFromSphere(OdTvPoint(0., y + 0.7, 0.), 0.9, OdTvVector::kYAxis, OdTvVector::kXAxis, 50);

      OdTvShellDataPtr pSphere = sphereId.openAsShell();

      // Create entity mapper
      OdTvMapperDef entityMapper;
      entityMapper.setProjection(OdTvMapperDef::kSphere);
      entityMapper.translate(0., y + 0.7, 0.);
      pSphereEntity->setMaterialMapper(entityMapper);

      // Create material with unique name
      OdTvMaterialId materialId = pTvDb->createMaterial("Material4");
      OdTvMaterialPtr pMaterial = materialId.openObject(OdTv::kForWrite);
      // Create path to texture image file
      OdString texturePath = OdTvVisualizeSampleModelsUtils::formatPath(strResourceFolder, OD_T("textures/marble.png"));

      // Create material map and set texture to map
      OdTvMaterialMap materialMap;
      materialMap.setSourceFileName(texturePath);
      OdTvTextureMapper materialMapper;
      materialMapper.setSampleSize(1., 1.);
      materialMap.setMapper(materialMapper);
      // Set material map to material
      pMaterial->setDiffuse(OdTvMaterialColor(OdTvColorDef(255, 0, 0)), materialMap);

      // Set material to entity
      pSphereEntity->setMaterial(materialId);

      pTextEntity->appendText(OdTvPoint(-1., y, 0), OD_T("Texture by sphere mapping")).openAsText()->setTextSize(0.3);
    }

    // 2.6 Texture by box mapping
    y -= 2.;
    OdTvGeometryDataId entityBox5_Id = modelKeyEntity->appendSubEntity(OD_T("Box5"));
    {
      OdTvEntityPtr pBoxEntity = entityBox5_Id.openAsSubEntity(OdTv::kForWrite);

      // Create entity mapper
      OdTvMapperDef entityMapper;
      entityMapper.setProjection(OdTvMapperDef::kBox);
      // Create transform matrix
      entityMapper.translate(0., y + 0.7, 0.);
      pBoxEntity->setMaterialMapper(entityMapper);

      // Vertices and face indexes for shell
      OdTvPointArray vertices;
      OdInt32Array faceList;
      OdTvVisualizeSampleModelsUtils::generateBox(vertices, faceList, 0., y, 0.);

      OdTvGeometryDataId boxId = pBoxEntity->appendShell(vertices, faceList);

      OdTvShellDataPtr pBox = boxId.openAsShell();

      // Create material with unique name
      OdTvMaterialId materialId = pTvDb->createMaterial("Material5");
      OdTvMaterialPtr pMaterial = materialId.openObject(OdTv::kForWrite);
      // Create path to texture image file
      OdString texturePath = OdTvVisualizeSampleModelsUtils::formatPath(strResourceFolder, OD_T("textures/wood.png"));
      // Create sphere mapper for texture mapping on shell
      OdTvTextureMapper materialMapper;
      materialMapper.setSampleSize(1., 1.);
      // Create material map and set texture to map
      OdTvMaterialMap materialMap;
      materialMap.setSourceFileName(texturePath);
      materialMap.setMapper(materialMapper);
      // Set material map to material
      pMaterial->setDiffuse(OdTvMaterialColor(OdTvColorDef(255, 0, 0)), materialMap);

      // Set material to entity
      pBoxEntity->setMaterial(materialId);

      pTextEntity->appendText(OdTvPoint(-1., y, 0), OD_T("Texture by box mapping")).openAsText()->setTextSize(0.3);
    }

    //2.7 Green Diffuse with 0.2 SpecularGloss
    y -= 2.;
    OdTvGeometryDataId entityTeapot7_Id = modelKeyEntity->appendSubEntity(OD_T("Teapot7"));
    {
      OdTvEntityPtr pTeapotEntity = entityTeapot7_Id.openAsSubEntity(OdTv::kForWrite);

      OdTvShellDataPtr pShell;
      OdTvPoint2dArray mappingCoords;

      // Draw shell and get mapping coordinates
      OdTvVisualizeSampleModelsTeapot::drawTeapot(pShell, mappingCoords, pTeapotEntity, 0., y, 0.);

      // Create material with unique name
      OdTvMaterialId materialId = pTvDb->createMaterial("Material7");
      OdTvMaterialPtr pMaterial = materialId.openObject(OdTv::kForWrite);
      pMaterial->setSpecularGloss(0.2);
      // Create empty map for diffuse
      OdTvMaterialMap materialMap;
      pMaterial->setDiffuse(OdTvMaterialColor(OdTvColorDef(0, 128, 0)), materialMap);

      // Set material to shell
      pShell->setFaceMaterialsViaRange(0, pShell->getFacesCount(), materialId);

      pTextEntity->appendText(OdTvPoint(-1., y, 0), OD_T("Green Diffuse with 0.2 SpecularGloss")).openAsText()->setTextSize(0.3);
    }

    //2.8 Green Diffuse with 0.9 SpecularGloss
    y -= 2.;
    OdTvGeometryDataId entityTeapot8_Id = modelKeyEntity->appendSubEntity(OD_T("Teapot8"));
    {
      OdTvEntityPtr pTeapotEntity = entityTeapot8_Id.openAsSubEntity(OdTv::kForWrite);

      OdTvShellDataPtr pShell;
      OdTvPoint2dArray mappingCoords;

      // Draw shell and get mapping coordinates
      OdTvVisualizeSampleModelsTeapot::drawTeapot(pShell, mappingCoords, pTeapotEntity, 0., y, 0.);

      // Create material with unique name
      OdTvMaterialId materialId = pTvDb->createMaterial("Material8");
      OdTvMaterialPtr pMaterial = materialId.openObject(OdTv::kForWrite);
      pMaterial->setSpecularGloss(0.9);
      // Create empty map for diffuse
      OdTvMaterialMap materialMap;
      pMaterial->setDiffuse(OdTvMaterialColor(OdTvColorDef(0, 128, 0)), materialMap);

      // Set material to shell
      pShell->setFaceMaterialsViaRange(0, pShell->getFacesCount(), materialId);

      pTextEntity->appendText(OdTvPoint(-1., y, 0), OD_T("Green Diffuse with 0.9 SpecularGloss")).openAsText()->setTextSize(0.3);
    }

    //2.9 Green Diffuse with 0.2 Opacity
    y -= 2.;
    OdTvGeometryDataId entityTeapot9_Id = modelKeyEntity->appendSubEntity(OD_T("Teapot9"));
    {
      OdTvEntityPtr pTeapotEntity = entityTeapot9_Id.openAsSubEntity(OdTv::kForWrite);

      OdTvShellDataPtr pShell;
      OdTvPoint2dArray mappingCoords;

      // Draw shell and get mapping coordinates
      OdTvVisualizeSampleModelsTeapot::drawTeapot(pShell, mappingCoords, pTeapotEntity, 0., y, 0.);

      // Create material with unique name
      OdTvMaterialId materialId = pTvDb->createMaterial("Material9");
      OdTvMaterialPtr pMaterial = materialId.openObject(OdTv::kForWrite);
      pMaterial->setOpacity(0.2);
      // Create empty map for diffuse
      OdTvMaterialMap materialMap;
      pMaterial->setDiffuse(OdTvMaterialColor(OdTvColorDef(0, 128, 0)), materialMap);

      // Set material to shell
      pShell->setFaceMaterialsViaRange(0, pShell->getFacesCount(), materialId);

      pTextEntity->appendText(OdTvPoint(-1., y, 0), OD_T("Green Diffuse with 0.2 Opacity")).openAsText()->setTextSize(0.3);
    }

    //2.10 Red Difuse with blue Emission
    y -= 2.;
    OdTvGeometryDataId entityTeapot10_Id = modelKeyEntity->appendSubEntity(OD_T("Teapot10"));
    {
      OdTvEntityPtr pTeapotEntity = entityTeapot10_Id.openAsSubEntity(OdTv::kForWrite);

      OdTvShellDataPtr pShell;
      OdTvPoint2dArray mappingCoords;

      // Draw shell and get mapping coordinates
      OdTvVisualizeSampleModelsTeapot::drawTeapot(pShell, mappingCoords, pTeapotEntity, 0., y, 0.);

      // Create material with unique name
      OdTvMaterialId materialId = pTvDb->createMaterial("Material10");
      OdTvMaterialPtr pMaterial = materialId.openObject(OdTv::kForWrite);
      // Create empty map for diffuse
      OdTvMaterialMap materialMap;
      pMaterial->setDiffuse(OdTvMaterialColor(OdTvColorDef(255, 0, 0)), materialMap);
      pMaterial->setEmission(OdTvMaterialColor(OdTvColorDef(0, 0, 255)));

      // Set material to shell
      pShell->setFaceMaterialsViaRange(0, pShell->getFacesCount(), materialId);

      pTextEntity->appendText(OdTvPoint(-1., y, 0), OD_T("Red Diffuse with blue Emission")).openAsText()->setTextSize(0.3);
    }

    //2.11 Set material to layer
    y -= 2.;
    OdTvGeometryDataId entityInhered11_Id = modelKeyEntity->appendSubEntity(OD_T("Teapot11"));
    {
      OdTvEntityPtr pTeapotEntity = entityInhered11_Id.openAsSubEntity(OdTv::kForWrite);

      // Create material with unique name
      OdTvMaterialId materialId = pTvDb->createMaterial("Material12");
      OdTvMaterialPtr pMaterial = materialId.openObject(OdTv::kForWrite);
      // Create empty map for diffuse
      OdTvMaterialMap materialMap;
      pMaterial->setDiffuse(OdTvMaterialColor(OdTvColorDef(0, 255, 0)), materialMap);
      pMaterial->setEmission(OdTvMaterialColor(OdTvColorDef(0, 0, 255)));

      OdTvLayerId layerId = pTvDb->createLayer(OD_T("layer"));
      OdTvLayerPtr pLayer = layerId.openObject(OdTv::kForWrite);
      pLayer->setMaterial(materialId);
      pTeapotEntity->setLayer(layerId);

      OdTvShellDataPtr pShell;
      OdTvPoint2dArray mappingCoords;

      // Create material def for entity with kByLayer property
      OdTvMaterialDef inheritedMaterial;
      inheritedMaterial.setInheritedMaterial(OdTv::kByLayer);
      // Set inherited material to entity
      pTeapotEntity->setMaterial(inheritedMaterial);

      // Draw shell and get mapping coordinates
      OdTvVisualizeSampleModelsTeapot::drawTeapot(pShell, mappingCoords, pTeapotEntity, 0., y, 0.);

      pTextEntity->appendText(OdTvPoint(-1., y, 0), OD_T("Green Diffuse with blue Emission in the layer")).openAsText()->setTextSize(0.3);
    }

    //3. Iterator example
    {
      OdTvMaterialId material0Id = pTvDb->createMaterial("Mat0");
      OdTvMaterialId material1Id = pTvDb->createMaterial("Mat1");
      OdTvMaterialId material2Id = pTvDb->createMaterial("Mat2");
      OdTvMaterialId material3Id = pTvDb->createMaterial("Mat3");

      OdTvMaterialsIteratorPtr materialsIter = pTvDb->getMaterialsIterator();
      while (!materialsIter->done())
      {
        OdTvMaterialId materialId = materialsIter->getMaterial();
        materialsIter->step();

        OdString name = materialId.openObject(OdTv::kForRead)->getName();
      }
    }

  }
}

void OdTvViewerDebugSampleModels::initCylinderAttributesModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId)
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
  OdTvTextStyleId textStyle2 = pTvDb->createTextStyle(OD_T("kBottomRight"));
  {
    OdTvTextStylePtr pTextStyle = textStyle2.openObject(OdTv::kForWrite);
    pTextStyle->setAlignmentMode(OdTvTextStyle::kBottomRight);
    pTextStyle->setTextSize(0.02);
  }

  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId modelKeyEntityId = modelPtr->appendEntity(OD_T("Cylinder's attributes"));
  {
    OdTvEntityPtr modelKeyEntity = modelKeyEntityId.openObject(OdTv::kForWrite);

    //1. Add title
    OdTvGeometryDataId titleEntityId = modelKeyEntity->appendSubEntity(OD_T("title"));
    {
      OdTvEntityPtr titleEntity = titleEntityId.openAsSubEntity(OdTv::kForWrite);
      titleEntity->setColor(OdTvColorDef(128, 000, 128), OdTvGeometryData::kAll);
      titleEntity->setLineWeight(2);
      titleEntity->setTextStyle(textStyle);

      titleEntity->appendText(OdTvPoint(0.0, .75, 0.0), OD_T("Cylinder's attributes"));
    }

    //2. Add grid lines
    OdTvVisualizeSampleModelsUtils::appendGridLines(modelKeyEntity, false, 3, 4, -1., 0.66, 0.66, 0.33);

    double x0 = -0.66, x1 = 0., x2 = 0.66;
    double y0 = 0.5;
    double shellRadius = 0.14;

    // column's text
    OdTvGeometryDataId geometries_entity_Id_Text_col = modelKeyEntity->appendSubEntity(OD_T("cyl_column_txt"));
    {
      OdTvEntityPtr pTextEntity = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity->setTextStyle(textStyle1);

      pTextEntity->appendText(OdTvPoint(x0, y0 + 0.18, 0.), OD_T("Faces"));
      pTextEntity->appendText(OdTvPoint(x1, y0 + 0.18, 0.), OD_T("Edges"));
      pTextEntity->appendText(OdTvPoint(x2, y0 + 0.18, 0.), OD_T("Vertices"));
    }
    // row's text
    OdTvGeometryDataId geometries_entity_Id_Text_row = modelKeyEntity->appendSubEntity(OD_T("cyl_row_txt"));
    {
      OdTvEntityPtr pTextEntity = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity->setTextStyle(textStyle2);

      pTextEntity->appendText(OdTvPoint(x0 - 0.35, y0, 0.), OD_T("Colors"));
      pTextEntity->appendText(OdTvPoint(x0 - 0.35, y0 - 0.33, 0.), OD_T("Layers with color"));
      pTextEntity->appendText(OdTvPoint(x0 - 0.35, y0 - 0.66, 0.), OD_T("Visibilities"));
      pTextEntity->appendText(OdTvPoint(x0 - 0.35, y0 - 0.99, 0.), OD_T("Linetypes"));
    }

    //3. Color attribute
    {
      OdTvGeometryDataId geometries_entity_Id_color0 = modelKeyEntity->appendSubEntity(OD_T("col_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_color0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setColor(OdTvColorDef(255, 0, 0), OdTvGeometryData::kFaces);

        pGeomEntity0->appendCylinder(OdTvPoint(x0, y0 - 0.1, 0.), OdTvPoint(x0, y0 + 0.1, 0.), shellRadius);
      }

      // Not working
      OdTvGeometryDataId geometries_entity_Id_color1 = modelKeyEntity->appendSubEntity(OD_T("col_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_color1.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity1->setColor(OdTvColorDef(255, 0, 0), OdTvGeometryData::kEdges);

        pGeomEntity1->appendCylinder(OdTvPoint(x1, y0 - 0.1, 0.), OdTvPoint(x1, y0 + 0.1, 0.), shellRadius);
      }

      OdTvGeometryDataId geometries_entity_Id_color2 = modelKeyEntity->appendSubEntity(OD_T("col_2"));
      {
        OdTvEntityPtr pGeomEntity2 = geometries_entity_Id_color2.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity2->setColor(OdTvColorDef(255, 0, 0), OdTvGeometryData::kVertices);

        pGeomEntity2->appendCylinder(OdTvPoint(x2, y0 - 0.1, 0.), OdTvPoint(x2, y0 + 0.1, 0.), shellRadius);
      }
    }

    // 4. Layer attributes
    y0 -= 0.33;
    {
      OdTvDatabasePtr pDb = databaseId.openObject(OdTv::kForWrite);
      OdTvLayerId layerId = pDb->createLayer(OD_T("Green_layer"));
      OdTvLayerPtr layerPtr = layerId.openObject(OdTv::kForWrite);
      layerPtr->setColor(OdTvColorDef(0, 255, 0));

      OdTvGeometryDataId geometries_entity_Id_layer0 = modelKeyEntity->appendSubEntity(OD_T("lay_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_layer0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setLayer(layerId, OdTvGeometryData::kFaces);

        pGeomEntity0->appendCylinder(OdTvPoint(x0, y0 - 0.1, 0.), OdTvPoint(x0, y0 + 0.1, 0.), shellRadius);
      }

      // Not working
      OdTvGeometryDataId geometries_entity_Id_layer1 = modelKeyEntity->appendSubEntity(OD_T("lay_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_layer1.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity1->setLayer(layerId, OdTvGeometryData::kEdges);

        pGeomEntity1->appendCylinder(OdTvPoint(x1, y0 - 0.1, 0.), OdTvPoint(x1, y0 + 0.1, 0.), shellRadius);
      }

      OdTvGeometryDataId additionalEntityId = modelKeyEntity->appendSubEntity(OD_T("lay_1"));
      {
        OdTvEntityPtr pAdditionalEntity1 = additionalEntityId.openAsSubEntity(OdTv::kForWrite);

        pAdditionalEntity1->appendPolyline(OdTvPoint(x2 - 0.1, y0, 0.), OdTvPoint(x2 + 0.1, y0, 0.));
      }
    }

    // 5. Visibility attributes
    y0 -= 0.33;
    {
      OdTvGeometryDataId geometries_entity_Id_visibility0 = modelKeyEntity->appendSubEntity(OD_T("vis_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_visibility0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setVisibility(OdTvVisibilityDef(false), OdTvGeometryData::kFaces);

        pGeomEntity0->appendCylinder(OdTvPoint(x0, y0 - 0.1, 0.), OdTvPoint(x0, y0 + 0.1, 0.), shellRadius).openObject()->setColor(OdTvColorDef(0, 255, 0));
      }

      OdTvGeometryDataId geometries_entity_Id_visibility1 = modelKeyEntity->appendSubEntity(OD_T("vis_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_visibility1.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity1->setVisibility(OdTvVisibilityDef(false), OdTvGeometryData::kEdges);

        pGeomEntity1->appendCylinder(OdTvPoint(x1, y0 - 0.1, 0.), OdTvPoint(x1, y0 + 0.1, 0.), shellRadius).openObject()->setColor(OdTvColorDef(0, 255, 0));
      }

      OdTvGeometryDataId additionalEntityId = modelKeyEntity->appendSubEntity(OD_T("lay_1"));
      {
        OdTvEntityPtr pAdditionalEntity1 = additionalEntityId.openAsSubEntity(OdTv::kForWrite);

        pAdditionalEntity1->appendPolyline(OdTvPoint(x2 - 0.1, y0, 0.), OdTvPoint(x2 + 0.1, y0, 0.));
      }

    }

    // 6. Linetype attribute
    y0 -= 0.33;
    {
      OdTvGeometryDataId additionalEntity1Id = modelKeyEntity->appendSubEntity(OD_T("lay_1"));
      {
        OdTvEntityPtr pAdditionalEntity1 = additionalEntity1Id.openAsSubEntity(OdTv::kForWrite);

        pAdditionalEntity1->appendPolyline(OdTvPoint(x0 - 0.1, y0, 0.), OdTvPoint(x0 + 0.1, y0, 0.));
      }

      // Not working
      OdTvGeometryDataId geometries_entity_Id_linetype0 = modelKeyEntity->appendSubEntity(OD_T("lt_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_linetype0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setLinetype(OdTvLinetype::kDashed, OdTvGeometryData::kEdges);
        pGeomEntity0->setLinetypeScale(0.05);

        pGeomEntity0->appendCylinder(OdTvPoint(x1, y0 - 0.1, 0.), OdTvPoint(x1, y0 + 0.1, 0.), shellRadius);
      }

      OdTvGeometryDataId additionalEntity2Id = modelKeyEntity->appendSubEntity(OD_T("lay_1"));
      {
        OdTvEntityPtr pAdditionalEntity1 = additionalEntity2Id.openAsSubEntity(OdTv::kForWrite);

        pAdditionalEntity1->appendPolyline(OdTvPoint(x2 - 0.1, y0, 0.), OdTvPoint(x2 + 0.1, y0, 0.));
      }

    }
  }
}

void OdTvViewerDebugSampleModels::initSphereAttributesModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId)
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
  OdTvTextStyleId textStyle2 = pTvDb->createTextStyle(OD_T("kBottomRight"));
  {
    OdTvTextStylePtr pTextStyle = textStyle2.openObject(OdTv::kForWrite);
    pTextStyle->setAlignmentMode(OdTvTextStyle::kBottomRight);
    pTextStyle->setTextSize(0.02);
  }

  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId modelKeyEntityId = modelPtr->appendEntity(OD_T("Sphere's attributes"));
  {
    OdTvEntityPtr modelKeyEntity = modelKeyEntityId.openObject(OdTv::kForWrite);

    //1. Add title
    OdTvGeometryDataId titleEntityId = modelKeyEntity->appendSubEntity(OD_T("title"));
    {
      OdTvEntityPtr titleEntity = titleEntityId.openAsSubEntity(OdTv::kForWrite);
      titleEntity->setColor(OdTvColorDef(128, 000, 128), OdTvGeometryData::kAll);
      titleEntity->setLineWeight(2);
      titleEntity->setTextStyle(textStyle);

      titleEntity->appendText(OdTvPoint(0.0, .75, 0.0), OD_T("Sphere's attributes"));
    }

    //2. Add grid lines
    OdTvVisualizeSampleModelsUtils::appendGridLines(modelKeyEntity, false, 3, 3, -1., 0.66, 0.66, 0.33);

    double x0 = -0.66, x1 = 0., x2 = 0.66;
    double y0 = 0.5;
    double shellRadius = 0.14;

    // column's text
    OdTvGeometryDataId geometries_entity_Id_Text_col = modelKeyEntity->appendSubEntity(OD_T("sphere_column_txt"));
    {
      OdTvEntityPtr pTextEntity = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity->setTextStyle(textStyle1);

      pTextEntity->appendText(OdTvPoint(x0, y0 + 0.18, 0.), OD_T("Faces"));
      pTextEntity->appendText(OdTvPoint(x1, y0 + 0.18, 0.), OD_T("Edges"));
      pTextEntity->appendText(OdTvPoint(x2, y0 + 0.18, 0.), OD_T("Vertices"));

    }
    // row's text
    OdTvGeometryDataId geometries_entity_Id_Text_row = modelKeyEntity->appendSubEntity(OD_T("sphere_row_txt"));
    {
      OdTvEntityPtr pTextEntity = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity->setTextStyle(textStyle2);

      pTextEntity->appendText(OdTvPoint(x0 - 0.35, y0, 0.), OD_T("Colors"));
      pTextEntity->appendText(OdTvPoint(x0 - 0.35, y0 - 0.33, 0.), OD_T("Layers with color"));
      pTextEntity->appendText(OdTvPoint(x0 - 0.35, y0 - 0.66, 0.), OD_T("Visibilities"));
    }

    //3. Color attribute
    {
      OdTvGeometryDataId geometries_entity_Id_color0 = modelKeyEntity->appendSubEntity(OD_T("col_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_color0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setColor(OdTvColorDef(255, 0, 0), OdTvGeometryData::kFaces);

        pGeomEntity0->appendSphere(OdTvPoint(x0, y0, 0.), shellRadius);
      }

      OdTvGeometryDataId geometries_entity_Id_color1 = modelKeyEntity->appendSubEntity(OD_T("col_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_color1.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity1->setColor(OdTvColorDef(255, 0, 0), OdTvGeometryData::kEdges);

        pGeomEntity1->appendSphere(OdTvPoint(x1, y0, 0.), shellRadius);
      }

      OdTvGeometryDataId geometries_entity_Id_color2 = modelKeyEntity->appendSubEntity(OD_T("col_2"));
      {
        OdTvEntityPtr pGeomEntity2 = geometries_entity_Id_color2.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity2->setColor(OdTvColorDef(255, 0, 0), OdTvGeometryData::kVertices);

        pGeomEntity2->appendSphere(OdTvPoint(x2, y0, 0.), shellRadius);
      }
    }

    // 4. Layer attributes
    y0 -= 0.33;
    {
      OdTvDatabasePtr pDb = databaseId.openObject(OdTv::kForWrite);
      OdTvLayerId layerId = pDb->createLayer(OD_T("Green_layer"));
      OdTvLayerPtr layerPtr = layerId.openObject(OdTv::kForWrite);
      layerPtr->setColor(OdTvColorDef(0, 255, 0));

      OdTvGeometryDataId geometries_entity_Id_layer0 = modelKeyEntity->appendSubEntity(OD_T("lay_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_layer0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setLayer(layerId, OdTvGeometryData::kFaces);

        pGeomEntity0->appendSphere(OdTvPoint(x0, y0, 0.), shellRadius);
      }

      OdTvGeometryDataId geometries_entity_Id_layer1 = modelKeyEntity->appendSubEntity(OD_T("lay_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_layer1.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity1->setLayer(layerId, OdTvGeometryData::kEdges);

        pGeomEntity1->appendSphere(OdTvPoint(x1, y0, 0.), shellRadius);
      }

      OdTvGeometryDataId additionalEntity1Id = modelKeyEntity->appendSubEntity(OD_T("lay_1"));
      {
        OdTvEntityPtr pAdditionalEntity1 = additionalEntity1Id.openAsSubEntity(OdTv::kForWrite);

        pAdditionalEntity1->appendPolyline(OdTvPoint(x2 - 0.1, y0, 0.), OdTvPoint(x2 + 0.1, y0, 0.));
      }

    }

    // 5. Visibility attributes
    y0 -= 0.33;
    {
      OdTvGeometryDataId geometries_entity_Id_visibility0 = modelKeyEntity->appendSubEntity(OD_T("vis_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_visibility0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setVisibility(OdTvVisibilityDef(false), OdTvGeometryData::kFaces);

        pGeomEntity0->appendSphere(OdTvPoint(x0, y0, 0.), shellRadius).openObject()->setColor(OdTvColorDef(0, 255, 0));
      }

      OdTvGeometryDataId geometries_entity_Id_visibility1 = modelKeyEntity->appendSubEntity(OD_T("vis_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_visibility1.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity1->setVisibility(OdTvVisibilityDef(false), OdTvGeometryData::kEdges);

        pGeomEntity1->appendSphere(OdTvPoint(x1, y0, 0.), shellRadius).openObject()->setColor(OdTvColorDef(0, 255, 0));
      }

      OdTvGeometryDataId additionalEntity1Id = modelKeyEntity->appendSubEntity(OD_T("lay_1"));
      {
        OdTvEntityPtr pAdditionalEntity1 = additionalEntity1Id.openAsSubEntity(OdTv::kForWrite);

        pAdditionalEntity1->appendPolyline(OdTvPoint(x2 - 0.1, y0, 0.), OdTvPoint(x2 + 0.1, y0, 0.));
      }

    }
  }
}

void OdTvViewerDebugSampleModels::initBoxAttributesModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId)
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
  OdTvTextStyleId textStyle2 = pTvDb->createTextStyle(OD_T("kBottomRight"));
  {
    OdTvTextStylePtr pTextStyle = textStyle2.openObject(OdTv::kForWrite);
    pTextStyle->setAlignmentMode(OdTvTextStyle::kBottomRight);
    pTextStyle->setTextSize(0.02);
  }

  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId modelKeyEntityId = modelPtr->appendEntity(OD_T("Boxes attributes"));
  {
    OdTvEntityPtr modelKeyEntity = modelKeyEntityId.openObject(OdTv::kForWrite);

    //1. Add title
    OdTvGeometryDataId titleEntityId = modelKeyEntity->appendSubEntity(OD_T("title"));
    {
      OdTvEntityPtr titleEntity = titleEntityId.openAsSubEntity(OdTv::kForWrite);
      titleEntity->setColor(OdTvColorDef(128, 000, 128), OdTvGeometryData::kAll);
      titleEntity->setLineWeight(2);
      titleEntity->setTextStyle(textStyle);

      titleEntity->appendText(OdTvPoint(0.0, .75, 0.0), OD_T("Boxes attributes"));
    }

    //2. Add grid lines
    OdTvVisualizeSampleModelsUtils::appendGridLines(modelKeyEntity, false, 3, 4, -1., 0.66, 0.66, 0.33);

    double x0 = -0.66, x1 = 0., x2 = 0.66;
    double y0 = 0.5;

    // column's text
    OdTvGeometryDataId geometries_entity_Id_Text_col = modelKeyEntity->appendSubEntity(OD_T("box_column_txt"));
    {
      OdTvEntityPtr pTextEntity = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity->setTextStyle(textStyle1);

      pTextEntity->appendText(OdTvPoint(x0, y0 + 0.18, 0.), OD_T("Faces"));
      pTextEntity->appendText(OdTvPoint(x1, y0 + 0.18, 0.), OD_T("Edges"));
      pTextEntity->appendText(OdTvPoint(x2, y0 + 0.18, 0.), OD_T("Vertices"));
    }
    // row's text
    OdTvGeometryDataId geometries_entity_Id_Text_row = modelKeyEntity->appendSubEntity(OD_T("box_row_txt"));
    {
      OdTvEntityPtr pTextEntity = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity->setTextStyle(textStyle2);

      pTextEntity->appendText(OdTvPoint(x0 - 0.35, y0, 0.), OD_T("Colors"));
      pTextEntity->appendText(OdTvPoint(x0 - 0.35, y0 - 0.33, 0.), OD_T("Layers with color"));
      pTextEntity->appendText(OdTvPoint(x0 - 0.35, y0 - 0.66, 0.), OD_T("Visibilities"));
      pTextEntity->appendText(OdTvPoint(x0 - 0.35, y0 - 0.99, 0.), OD_T("Linetypes"));
    }

    //3. Color attribute
    {
      OdTvGeometryDataId geometries_entity_Id_color0 = modelKeyEntity->appendSubEntity(OD_T("col_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_color0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setColor(OdTvColorDef(255, 0, 0), OdTvGeometryData::kFaces);

        pGeomEntity0->appendBox(OdTvPoint(x0, y0, 0.), 0.2, 0.2, 0.2);
      }

      // Not working
      OdTvGeometryDataId geometries_entity_Id_color1 = modelKeyEntity->appendSubEntity(OD_T("col_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_color1.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity1->setColor(OdTvColorDef(255, 0, 0), OdTvGeometryData::kEdges);

        pGeomEntity1->appendBox(OdTvPoint(x1, y0, 0.), 0.2, 0.2, 0.2);
      }

      OdTvGeometryDataId geometries_entity_Id_color2 = modelKeyEntity->appendSubEntity(OD_T("col_2"));
      {
        OdTvEntityPtr pGeomEntity2 = geometries_entity_Id_color2.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity2->setColor(OdTvColorDef(255, 0, 0), OdTvGeometryData::kVertices);

        pGeomEntity2->appendBox(OdTvPoint(x2, y0, 0.), 0.2, 0.2, 0.2);
      }
    }

    // 4. Layer attributes
    y0 -= 0.33;
    {
      OdTvDatabasePtr pDb = databaseId.openObject(OdTv::kForWrite);
      OdTvLayerId layerId = pDb->createLayer(OD_T("Green_layer"));
      OdTvLayerPtr layerPtr = layerId.openObject(OdTv::kForWrite);
      layerPtr->setColor(OdTvColorDef(0, 255, 0));

      OdTvGeometryDataId geometries_entity_Id_layer0 = modelKeyEntity->appendSubEntity(OD_T("lay_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_layer0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setLayer(layerId, OdTvGeometryData::kFaces);

        pGeomEntity0->appendBox(OdTvPoint(x0, y0, 0.), 0.2, 0.2, 0.2);
      }

      // Not working
      OdTvGeometryDataId geometries_entity_Id_layer1 = modelKeyEntity->appendSubEntity(OD_T("lay_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_layer1.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity1->setLayer(layerId, OdTvGeometryData::kEdges);

        pGeomEntity1->appendBox(OdTvPoint(x1, y0, 0.), 0.2, 0.2, 0.2);
      }

      OdTvGeometryDataId additionalEntityId = modelKeyEntity->appendSubEntity(OD_T("lay_1"));
      {
        OdTvEntityPtr pAdditionalEntity1 = additionalEntityId.openAsSubEntity(OdTv::kForWrite);

        pAdditionalEntity1->appendPolyline(OdTvPoint(x2 - 0.1, y0, 0.), OdTvPoint(x2 + 0.1, y0, 0.));
      }
    }

    // 5. Visibility attributes
    y0 -= 0.33;
    {
      OdTvGeometryDataId geometries_entity_Id_visibility0 = modelKeyEntity->appendSubEntity(OD_T("vis_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_visibility0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setVisibility(OdTvVisibilityDef(false), OdTvGeometryData::kFaces);

        pGeomEntity0->appendBox(OdTvPoint(x0, y0, 0.), 0.2, 0.2, 0.2).openObject()->setColor(OdTvColorDef(0, 255, 0));
      }

      OdTvGeometryDataId geometries_entity_Id_visibility1 = modelKeyEntity->appendSubEntity(OD_T("vis_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_visibility1.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity1->setVisibility(OdTvVisibilityDef(false), OdTvGeometryData::kEdges);

        pGeomEntity1->appendBox(OdTvPoint(x1, y0, 0.), 0.2, 0.2, 0.2).openObject()->setColor(OdTvColorDef(0, 255, 0));
      }

      OdTvGeometryDataId additionalEntityId = modelKeyEntity->appendSubEntity(OD_T("lay_1"));
      {
        OdTvEntityPtr pAdditionalEntity1 = additionalEntityId.openAsSubEntity(OdTv::kForWrite);

        pAdditionalEntity1->appendPolyline(OdTvPoint(x2 - 0.1, y0, 0.), OdTvPoint(x2 + 0.1, y0, 0.));
      }

    }

    // 6. Linetype attribute
    y0 -= 0.33;
    {
      OdTvGeometryDataId additionalEntity1Id = modelKeyEntity->appendSubEntity(OD_T("lay_1"));
      {
        OdTvEntityPtr pAdditionalEntity1 = additionalEntity1Id.openAsSubEntity(OdTv::kForWrite);

        pAdditionalEntity1->appendPolyline(OdTvPoint(x0 - 0.1, y0, 0.), OdTvPoint(x0 + 0.1, y0, 0.));
      }

      // Not working
      OdTvGeometryDataId geometries_entity_Id_linetype0 = modelKeyEntity->appendSubEntity(OD_T("lt_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_linetype0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setLinetype(OdTvLinetype::kDashed, OdTvGeometryData::kEdges);
        pGeomEntity0->setLinetypeScale(0.05);

        pGeomEntity0->appendBox(OdTvPoint(x1, y0, 0.), 0.2, 0.2, 0.2);
      }

      OdTvGeometryDataId additionalEntity2Id = modelKeyEntity->appendSubEntity(OD_T("lay_1"));
      {
        OdTvEntityPtr pAdditionalEntity1 = additionalEntity2Id.openAsSubEntity(OdTv::kForWrite);

        pAdditionalEntity1->appendPolyline(OdTvPoint(x2 - 0.1, y0, 0.), OdTvPoint(x2 + 0.1, y0, 0.));
      }

    }
  }
}

void OdTvViewerDebugSampleModels::initMeshFacesAttributesModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId)
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
  OdTvTextStyleId textStyle2 = pTvDb->createTextStyle(OD_T("kBottomRight"));
  {
    OdTvTextStylePtr pTextStyle = textStyle2.openObject(OdTv::kForWrite);
    pTextStyle->setAlignmentMode(OdTvTextStyle::kBottomRight);
    pTextStyle->setTextSize(0.02);
  }

  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId modelKeyEntityId = modelPtr->appendEntity(OD_T("Mesh's faces"));
  {
    OdTvEntityPtr modelKeyEntity = modelKeyEntityId.openObject(OdTv::kForWrite);

    //1. Add title
    OdTvGeometryDataId titleEntityId = modelKeyEntity->appendSubEntity(OD_T("title"));
    {
      OdTvEntityPtr titleEntity = titleEntityId.openAsSubEntity(OdTv::kForWrite);
      titleEntity->setColor(OdTvColorDef(128, 000, 128), OdTvGeometryData::kAll);
      titleEntity->setLineWeight(2);
      titleEntity->setTextStyle(textStyle);

      titleEntity->appendText(OdTvPoint(0.0, .75, 0.0), OD_T("Mesh's faces attributes and vertices editing"));
    }

    //2. Add grid lines
    OdTvVisualizeSampleModelsUtils::appendGridLines(modelKeyEntity, false, 3, 5, -1., 0.66, 0.66, 0.33);

    double x0 = -0.72, x1 = -0.05, x2 = 0.62;
    double y0 = 0.5;

    // column's text
    OdTvGeometryDataId geometries_entity_Id_Text_col = modelKeyEntity->appendSubEntity(OD_T("face_column_txt"));
    {
      OdTvEntityPtr pTextEntity0 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity0->setTextStyle(textStyle1);

      pTextEntity0->appendText(OdTvPoint(x0, y0 + 0.18, 0.), OD_T("kFaces"));
      pTextEntity0->appendText(OdTvPoint(x1, y0 + 0.18, 0.), OD_T("All filled"));
      pTextEntity0->appendText(OdTvPoint(x2, y0 + 0.18, 0.), OD_T("Half filled"));
    }
    // row's text
    OdTvGeometryDataId geometries_entity_Id_Text_row = modelKeyEntity->appendSubEntity(OD_T("face_row_txt"));
    {
      OdTvEntityPtr pTextEntity0 = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity0->setTextStyle(textStyle2);

      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0, 0.), OD_T("Colors"));
      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0 - 0.33, 0.), OD_T("Layers with color"));
      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0 - 0.66, 0.), OD_T("Visibilities"));
      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0 - 0.99, 0.), OD_T("Vertices editing"));
      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0 - 1.31, 0.), OD_T("Transparency"));
    }

    //3. Color attribute
    {
      OdTvGeometryDataId geometries_entity_Id_color0 = modelKeyEntity->appendSubEntity(OD_T("face_col_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_color0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setColor(OdTvColorDef(255, 0, 0), OdTvGeometryData::kFaces);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x0, y0, points);
        pGeomEntity0->appendMesh(3, 4, points);
      }

      OdTvGeometryDataId geometries_entity_Id_color1 = modelKeyEntity->appendSubEntity(OD_T("face_col_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_color1.openAsSubEntity(OdTv::kForWrite);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x1, y0, points);
        OdTvGeometryDataId mesh1Id = pGeomEntity1->appendMesh(3, 4, points);
        OdTvMeshDataPtr mesh1Ptr = mesh1Id.openAsMesh();

        mesh1Ptr->setFaceColorsViaRange(0, mesh1Ptr->getFacesCount(), OdTvColorDef(255, 0, 0));
      }

      OdTvGeometryDataId geometries_entity_Id_color2 = modelKeyEntity->appendSubEntity(OD_T("face_col_2"));
      {
        OdTvEntityPtr pGeomEntity2 = geometries_entity_Id_color2.openAsSubEntity(OdTv::kForWrite);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x2, y0, points);
        OdTvGeometryDataId mesh2Id = pGeomEntity2->appendMesh(3, 4, points);
        OdTvMeshDataPtr mesh2Ptr = mesh2Id.openAsMesh();

        mesh2Ptr->setFaceColorsViaRange(0, 0.5 * mesh2Ptr->getFacesCount(), OdTvColorDef(255, 0, 0));
      }
    }

    // 4. Layer attributes
    y0 -= 0.33;
    {
      OdTvDatabasePtr pDb = databaseId.openObject(OdTv::kForWrite);
      OdTvLayerId layerId = pDb->createLayer(OD_T("Green_layer"));
      OdTvLayerPtr layerPtr = layerId.openObject(OdTv::kForWrite);
      layerPtr->setColor(OdTvColorDef(0, 255, 0));


      OdTvGeometryDataId geometries_entity_Id_layer0 = modelKeyEntity->appendSubEntity(OD_T("face_lay_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_layer0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setLayer(layerId, OdTvGeometryData::kFaces);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x0, y0, points);
        pGeomEntity0->appendMesh(3, 4, points);
      }

      OdTvGeometryDataId geometries_entity_Id_layer1 = modelKeyEntity->appendSubEntity(OD_T("face_lay_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_layer1.openAsSubEntity(OdTv::kForWrite);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x1, y0, points);
        OdTvGeometryDataId mesh1Id = pGeomEntity1->appendMesh(3, 4, points);
        OdTvMeshDataPtr mesh1Ptr = mesh1Id.openAsMesh();

        mesh1Ptr->setFaceLayersViaRange(0, mesh1Ptr->getFacesCount(), layerId);
      }

      OdTvGeometryDataId geometries_entity_Id_layer2 = modelKeyEntity->appendSubEntity(OD_T("face_lay_2"));
      {
        OdTvEntityPtr pGeomEntity2 = geometries_entity_Id_layer2.openAsSubEntity(OdTv::kForWrite);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x2, y0, points);
        OdTvGeometryDataId mesh2Id = pGeomEntity2->appendMesh(3, 4, points);
        OdTvMeshDataPtr mesh2Ptr = mesh2Id.openAsMesh();

        mesh2Ptr->setFaceLayersViaRange(0, 0.5 * mesh2Ptr->getFacesCount(), layerId);
      }
    }

    // 5. Visibility attributes
    y0 -= 0.33;
    {
      OdTvGeometryDataId geometries_entity_Id_visibility0 = modelKeyEntity->appendSubEntity(OD_T("face_vis_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_visibility0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setVisibility(OdTvVisibilityDef(false), OdTvGeometryData::kFaces);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x0, y0, points);
        pGeomEntity0->appendMesh(3, 4, points);
      }

      OdTvGeometryDataId geometries_entity_Id_visibility1 = modelKeyEntity->appendSubEntity(OD_T("face_vis_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_visibility1.openAsSubEntity(OdTv::kForWrite);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x1, y0, points);
        OdTvGeometryDataId mesh1Id = pGeomEntity1->appendMesh(3, 4, points);
        OdTvMeshDataPtr mesh1Ptr = mesh1Id.openAsMesh();

        mesh1Ptr->setFaceVisibilitiesViaRange(0, mesh1Ptr->getFacesCount(), OdTvVisibilityDef(false));
      }

      OdTvGeometryDataId geometries_entity_Id_visibility2 = modelKeyEntity->appendSubEntity(OD_T("face_vis_2"));
      {
        OdTvEntityPtr pGeomEntity2 = geometries_entity_Id_visibility2.openAsSubEntity(OdTv::kForWrite);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x2, y0, points);
        OdTvGeometryDataId mesh2Id = pGeomEntity2->appendMesh(3, 4, points);
        OdTvMeshDataPtr mesh2Ptr = mesh2Id.openAsMesh();

        mesh2Ptr->setFaceVisibilitiesViaRange(0, 0.5 * mesh2Ptr->getFacesCount(), OdTvVisibilityDef(false));
      }
    }

    // 6. Vertices editing
    y0 -= 0.33;
    {
      OdTvGeometryDataId geometries_entity_Id_linetype0 = modelKeyEntity->appendSubEntity(OD_T("edge_lt_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_linetype0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setLinetype(OdTvLinetype::kDashed, OdTvGeometryData::kEdges);
        pGeomEntity0->setLinetypeScale(0.05);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x0, y0, points);
        OdTvGeometryDataId mesh0Id = pGeomEntity0->appendMesh(3, 4, points);
        OdTvMeshDataPtr mesh0Ptr = mesh0Id.openAsMesh();

        OdTvVertexPosArray poses;
        poses.append(OdTvVertexPos(1, 1));
        poses.append(OdTvVertexPos(1, 2));
        poses.append(OdTvVertexPos(2, 1));
        poses.append(OdTvVertexPos(2, 2));

        OdTvPointArray editedPoints;
        OdTvVisualizeSampleModelsUtils::generateMeshEditVertices(x0, y0, editedPoints);
        mesh0Ptr->editVerticesViaList(poses, editedPoints);

      }

      OdTvGeometryDataId geometries_entity_Id_linetype1 = modelKeyEntity->appendSubEntity(OD_T("edge_lt_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_linetype1.openAsSubEntity(OdTv::kForWrite);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x1, y0, points);
        OdTvGeometryDataId mesh1Id = pGeomEntity1->appendMesh(3, 4, points);
        OdTvMeshDataPtr mesh1Ptr = mesh1Id.openAsMesh();

        OdTvPointArray editedPoints;
        OdTvVisualizeSampleModelsUtils::generateMeshEditVertices(x1, y0, editedPoints);
        mesh1Ptr->editVerticesViaRange(1, 1, 2, 2, editedPoints);
      }

      OdTvGeometryDataId geometries_entity_Id_linetype2 = modelKeyEntity->appendSubEntity(OD_T("edge_lt_2"));
      {
        OdTvEntityPtr pGeomEntity2 = geometries_entity_Id_linetype2.openAsSubEntity(OdTv::kForWrite);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x2, y0, points);
        OdTvGeometryDataId mesh1Id = pGeomEntity2->appendMesh(3, 4, points);
        OdTvMeshDataPtr mesh1Ptr = mesh1Id.openAsMesh();

        OdTvPointArray editedPoints;
        OdTvVisualizeSampleModelsUtils::generateMeshEditVertices(x2, y0, editedPoints);
        mesh1Ptr->editVerticesViaRange(1, 1, 2, 2, 4, editedPoints.asArrayPtr());
      }
    }

    //7. Transparency attribute
    y0 -= 0.33;
    {
      OdTvGeometryDataId geometries_entity_Id_transparency0 = modelKeyEntity->appendSubEntity(OD_T("edge_transparency_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_transparency0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setTransparency(0.8, OdTvGeometryData::kFaces);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x0, y0, points);
        pGeomEntity0->appendMesh(3, 4, points);
      }

      OdTvGeometryDataId geometries_entity_Id_transparency1 = modelKeyEntity->appendSubEntity(OD_T("edge_transparency_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_transparency1.openAsSubEntity(OdTv::kForWrite);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x1, y0, points);
        OdTvGeometryDataId mesh1Id = pGeomEntity1->appendMesh(3, 4, points);
        OdTvMeshDataPtr mesh1Ptr = mesh1Id.openAsMesh();

        mesh1Ptr->setFaceTransparencyViaRange(0, mesh1Ptr->getFacesCount(), 0.8);
      }

      OdTvGeometryDataId geometries_entity_Id_transparency2 = modelKeyEntity->appendSubEntity(OD_T("edge_transparency_2"));
      {
        OdTvEntityPtr pGeomEntity2 = geometries_entity_Id_transparency2.openAsSubEntity(OdTv::kForWrite);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x2, y0, points);
        OdTvGeometryDataId mesh2Id = pGeomEntity2->appendMesh(3, 4, points);
        OdTvMeshDataPtr mesh2Ptr = mesh2Id.openAsMesh();

        mesh2Ptr->setFaceTransparencyViaRange(0, 0.5 * mesh2Ptr->getFacesCount(), 0.8);
      }
    }

  }
}

void OdTvViewerDebugSampleModels::initMeshEdgesAttributesModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId)
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
  OdTvTextStyleId textStyle2 = pTvDb->createTextStyle(OD_T("kBottomRight"));
  {
    OdTvTextStylePtr pTextStyle = textStyle2.openObject(OdTv::kForWrite);
    pTextStyle->setAlignmentMode(OdTvTextStyle::kBottomRight);
    pTextStyle->setTextSize(0.02);
  }

  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId modelKeyEntityId = modelPtr->appendEntity(OD_T("Mesh's edges"));
  {
    OdTvEntityPtr modelKeyEntity = modelKeyEntityId.openObject(OdTv::kForWrite);

    //1. Add title
    OdTvGeometryDataId titleEntityId = modelKeyEntity->appendSubEntity(OD_T("title"));
    {
      OdTvEntityPtr titleEntity = titleEntityId.openAsSubEntity(OdTv::kForWrite);
      titleEntity->setColor(OdTvColorDef(128, 000, 128), OdTvGeometryData::kAll);
      titleEntity->setLineWeight(2);
      titleEntity->setTextStyle(textStyle);

      titleEntity->appendText(OdTvPoint(0.0, .75, 0.0), OD_T("Mesh's edges attributes"));
    }

    //2. Add grid lines
    OdTvVisualizeSampleModelsUtils::appendGridLines(modelKeyEntity, false, 3, 4, -1., 0.66, 0.66, 0.33);

    double x0 = -0.72, x1 = -0.05, x2 = 0.62;
    double y0 = 0.5;

    // column's text
    OdTvGeometryDataId geometries_entity_Id_Text_col = modelKeyEntity->appendSubEntity(OD_T("edge_column_txt"));
    {
      OdTvEntityPtr pTextEntity = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity->setTextStyle(textStyle1);

      pTextEntity->appendText(OdTvPoint(x0, y0 + 0.18, 0.), OD_T("kEdges"));
      pTextEntity->appendText(OdTvPoint(x1, y0 + 0.18, 0.), OD_T("All filled"));
      pTextEntity->appendText(OdTvPoint(x2, y0 + 0.18, 0.), OD_T("Half filled"));
    }
    // row's text
    OdTvGeometryDataId geometries_entity_Id_Text_row = modelKeyEntity->appendSubEntity(OD_T("edge_row_txt"));
    {
      OdTvEntityPtr pTextEntity = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity->setTextStyle(textStyle2);

      pTextEntity->appendText(OdTvPoint(x0 - 0.35, y0, 0.), OD_T("Colors"));
      pTextEntity->appendText(OdTvPoint(x0 - 0.35, y0 - 0.33, 0.), OD_T("Layers with color"));
      pTextEntity->appendText(OdTvPoint(x0 - 0.35, y0 - 0.66, 0.), OD_T("Visibilities"));
      pTextEntity->appendText(OdTvPoint(x0 - 0.35, y0 - 0.99, 0.), OD_T("Linetypes"));
    }

    //3. Color attribute
    {
      OdTvGeometryDataId geometries_entity_Id_color0 = modelKeyEntity->appendSubEntity(OD_T("edge_col_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_color0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setColor(OdTvColorDef(255, 0, 0), OdTvGeometryData::kEdges);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x0, y0, points);
        pGeomEntity0->appendMesh(3, 4, points);
      }

      OdTvGeometryDataId geometries_entity_Id_color1 = modelKeyEntity->appendSubEntity(OD_T("edge_col_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_color1.openAsSubEntity(OdTv::kForWrite);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x1, y0, points);
        OdTvGeometryDataId mesh1Id = pGeomEntity1->appendMesh(3, 4, points);
        OdTvMeshDataPtr mesh1Ptr = mesh1Id.openAsMesh();

        mesh1Ptr->setEdgeColorsViaRange(0, mesh1Ptr->getEdgesCount(), OdTvColorDef(255, 0, 0));
      }

      OdTvGeometryDataId geometries_entity_Id_color2 = modelKeyEntity->appendSubEntity(OD_T("edge_col_2"));
      {
        OdTvEntityPtr pGeomEntity2 = geometries_entity_Id_color2.openAsSubEntity(OdTv::kForWrite);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x2, y0, points);
        OdTvGeometryDataId mesh2Id = pGeomEntity2->appendMesh(3, 4, points);
        OdTvMeshDataPtr mesh2Ptr = mesh2Id.openAsMesh();

        mesh2Ptr->setEdgeColorsViaRange(0, 0.5 * mesh2Ptr->getEdgesCount(), OdTvColorDef(255, 0, 0));
      }
    }

    // 4. Layer attributes
    y0 -= 0.33;
    {
      OdTvDatabasePtr pDb = databaseId.openObject(OdTv::kForWrite);
      OdTvLayerId layerId = pDb->createLayer(OD_T("Green_layer"));
      OdTvLayerPtr layerPtr = layerId.openObject(OdTv::kForWrite);
      layerPtr->setColor(OdTvColorDef(0, 255, 0));

      OdTvGeometryDataId geometries_entity_Id_layer0 = modelKeyEntity->appendSubEntity(OD_T("edge_lay_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_layer0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setLayer(layerId, OdTvGeometryData::kEdges);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x0, y0, points);
        pGeomEntity0->appendMesh(3, 4, points);
      }

      OdTvGeometryDataId geometries_entity_Id_layer1 = modelKeyEntity->appendSubEntity(OD_T("edge_lay_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_layer1.openAsSubEntity(OdTv::kForWrite);


        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x1, y0, points);
        OdTvGeometryDataId mesh1Id = pGeomEntity1->appendMesh(3, 4, points);
        OdTvMeshDataPtr mesh1Ptr = mesh1Id.openAsMesh();

        mesh1Ptr->setEdgeLayersViaRange(0, mesh1Ptr->getEdgesCount(), layerId);
      }

      OdTvGeometryDataId geometries_entity_Id_layer2 = modelKeyEntity->appendSubEntity(OD_T("edge_lay_2"));
      {
        OdTvEntityPtr pGeomEntity2 = geometries_entity_Id_layer2.openAsSubEntity(OdTv::kForWrite);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x2, y0, points);
        OdTvGeometryDataId mesh2Id = pGeomEntity2->appendMesh(3, 4, points);
        OdTvMeshDataPtr mesh2Ptr = mesh2Id.openAsMesh();

        mesh2Ptr->setEdgeLayersViaRange(0, 0.5 * mesh2Ptr->getEdgesCount(), layerId);
      }
    }

    // 5. Visibility attributes
    y0 -= 0.33;
    {
      OdTvGeometryDataId geometries_entity_Id_visibility0 = modelKeyEntity->appendSubEntity(OD_T("edge_vis_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_visibility0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setVisibility(OdTvVisibilityDef(false), OdTvGeometryData::kEdges);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x0, y0, points);
        pGeomEntity0->appendMesh(3, 4, points);
      }

      OdTvGeometryDataId geometries_entity_Id_visibility1 = modelKeyEntity->appendSubEntity(OD_T("edge_vis_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_visibility1.openAsSubEntity(OdTv::kForWrite);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x1, y0, points);
        OdTvGeometryDataId mesh1Id = pGeomEntity1->appendMesh(3, 4, points);
        OdTvMeshDataPtr mesh1Ptr = mesh1Id.openAsMesh();

        mesh1Ptr->setEdgeVisibilitiesViaRange(0, mesh1Ptr->getEdgesCount(), OdTvVisibilityDef(false));
      }

      OdTvGeometryDataId geometries_entity_Id_visibility2 = modelKeyEntity->appendSubEntity(OD_T("edge_vis_2"));
      {
        OdTvEntityPtr pGeomEntity2 = geometries_entity_Id_visibility2.openAsSubEntity(OdTv::kForWrite);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x2, y0, points);
        OdTvGeometryDataId mesh2Id = pGeomEntity2->appendMesh(3, 4, points);
        OdTvMeshDataPtr mesh2Ptr = mesh2Id.openAsMesh();

        OdInt32Array indPos;
        for (OdInt32 i = 0; i < (OdInt32)mesh2Ptr->getEdgesCount(); i++)
        {
          if (i % 3 != 0)
            indPos.append(i);
        }
        mesh2Ptr->setEdgeVisibilitiesViaList(indPos, OdTvVisibilityDef(false));
      }
    }

    // 6. Linetype attribute
    y0 -= 0.33;
    {
      OdTvGeometryDataId geometries_entity_Id_linetype0 = modelKeyEntity->appendSubEntity(OD_T("edge_lt_0"));
      {
        OdTvEntityPtr pGeomEntity0 = geometries_entity_Id_linetype0.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity0->setLinetype(OdTvLinetype::kDashed, OdTvGeometryData::kEdges);
        pGeomEntity0->setLinetypeScale(0.05);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x0, y0, points);
        pGeomEntity0->appendMesh(3, 4, points);
      }

      OdTvGeometryDataId geometries_entity_Id_linetype1 = modelKeyEntity->appendSubEntity(OD_T("edge_lt_1"));
      {
        OdTvEntityPtr pGeomEntity1 = geometries_entity_Id_linetype1.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity1->setLinetypeScale(0.05);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x1, y0, points);
        OdTvGeometryDataId mesh1Id = pGeomEntity1->appendMesh(3, 4, points);
        OdTvMeshDataPtr mesh1Ptr = mesh1Id.openAsMesh();

        mesh1Ptr->setEdgeLinetypesViaRange(0, mesh1Ptr->getEdgesCount(), OdTvLinetype::kDashed);
      }

      OdTvGeometryDataId geometries_entity_Id_linetype2 = modelKeyEntity->appendSubEntity(OD_T("edge_lt_2"));
      {
        OdTvEntityPtr pGeomEntity2 = geometries_entity_Id_linetype2.openAsSubEntity(OdTv::kForWrite);
        pGeomEntity2->setLinetypeScale(0.05);

        OdTvPointArray points;
        OdTvVisualizeSampleModelsUtils::generateMeshVertices(x2, y0, points);
        OdTvGeometryDataId mesh1Id = pGeomEntity2->appendMesh(3, 4, points);
        OdTvMeshDataPtr mesh1Ptr = mesh1Id.openAsMesh();

        mesh1Ptr->setEdgeLinetypesViaRange(0, 400, OdTvLinetype::kDashed);
      }
    }

  }

}

void OdTvViewerDebugSampleModels::initResetColorsModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId)
{
  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId modelKeyEntityId = modelPtr->appendEntity(OD_T("ResetAttributes"));
  {
    OdTvEntityPtr modelKeyEntity = modelKeyEntityId.openObject(OdTv::kForWrite);

    OdTvDatabasePtr pTvDb = databaseId.openObject();
    OdTvTextStyleId textStyleCol = pTvDb->createTextStyle(OD_T("kMiddleCenter"));
    {
      OdTvTextStylePtr pTextStyle = textStyleCol.openObject(OdTv::kForWrite);
      pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleCenter);
      pTextStyle->setTextSize(0.05);
    }
    OdTvTextStyleId textStyleRaw = pTvDb->createTextStyle(OD_T("kMiddleRight"));
    {
      OdTvTextStylePtr pTextStyle = textStyleRaw.openObject(OdTv::kForWrite);
      pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleRight);
      pTextStyle->setTextSize(0.05);
    }

    //1. Add title
    OdTvGeometryDataId titleEntityId = modelKeyEntity->appendSubEntity(OD_T("title"));
    {
      OdTvEntityPtr titleEntity = titleEntityId.openAsSubEntity(OdTv::kForWrite);
      titleEntity->setColor(OdTvColorDef(128, 000, 128), OdTvGeometryData::kAll);
      titleEntity->setLineWeight(2);

      titleEntity->appendText(OdTvPoint(0.0, .75, 0.0), OD_T("Color reset"));
      titleEntity->setTextStyle(textStyleCol);
    }

    //2. Add grid lines
    OdTvVisualizeSampleModelsUtils::appendGridLines(modelKeyEntity, false, 4, 3, -1., 0.66, 0.66, 0.33);

    double x0 = -0.66, x1 = 0., x2 = 0.66, x3 = 1.31;
    double y0 = 0.5;
    double shellRadius = 0.14;

    // column's text
    OdTvGeometryDataId geometries_entity_Id_Text_col = modelKeyEntity->appendSubEntity(OD_T("reset_column_txt"));
    {
      OdTvEntityPtr pTextEntity0 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity0->appendText(OdTvPoint(x0, y0 + 0.18, 0.), OD_T("Parent"));
      pTextEntity0->setTextStyle(textStyleCol);

      OdTvEntityPtr pTextEntity1 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity1->appendText(OdTvPoint(x1, y0 + 0.18, 0.), OD_T("Child"));
      pTextEntity1->setTextStyle(textStyleCol);

      OdTvEntityPtr pTextEntity2 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity2->appendText(OdTvPoint(x2, y0 + 0.18, 0.), OD_T("Child of child"));
      pTextEntity2->setTextStyle(textStyleCol);

      OdTvEntityPtr pTextEntity3 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity3->appendText(OdTvPoint(x3, y0 + 0.18, 0.), OD_T("Child geometry"));
      pTextEntity3->setTextStyle(textStyleCol);
    }
    // row's text
    OdTvGeometryDataId geometries_entity_Id_Text_row = modelKeyEntity->appendSubEntity(OD_T("reset_row_txt"));
    {
      OdTvEntityPtr pTextEntity0 = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0, 0.), OD_T("kAll"));
      pTextEntity0->setTextStyle(textStyleRaw);

      OdTvEntityPtr pTextEntity1 = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity1->appendText(OdTvPoint(x0 - 0.35, y0 - 0.33, 0.), OD_T("kEdges"));
      pTextEntity1->setTextStyle(textStyleRaw);

      OdTvEntityPtr pTextEntity2 = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity2->appendText(OdTvPoint(x0 - 0.35, y0 - 0.66, 0.), OD_T("SetColorViaRange"));
      pTextEntity2->setTextStyle(textStyleRaw);
    }

    //3. kAll
    OdTvGeometryDataId parentEntityId0 = modelKeyEntity->appendSubEntity(OD_T("parent0"));
    {
      OdTvEntityPtr pParentEntity0 = parentEntityId0.openAsSubEntity(OdTv::kForWrite);

      pParentEntity0->appendSphere(OdTvPoint(x0, y0, 0.), shellRadius);
      pParentEntity0->setColor(OdTvColorDef(0, 0, 255));

      OdTvGeometryDataId childEntityId0 = pParentEntity0->appendSubEntity(OD_T("childL0"));
      OdTvEntityPtr pChildEntity0 = childEntityId0.openAsSubEntity(OdTv::kForWrite);
      {
        pChildEntity0->appendSphere(OdTvPoint(x1, y0, 0.), shellRadius);
        pChildEntity0->setColor(OdTvColorDef(0, 255, 0));
      }

      OdTvGeometryDataId childChildEntityId0 = pChildEntity0->appendSubEntity(OD_T("childChild0"));
      OdTvEntityPtr pChildChildEntity0 = childChildEntityId0.openAsSubEntity(OdTv::kForWrite);
      {
        pChildChildEntity0->appendSphere(OdTvPoint(x2, y0, 0.), shellRadius);
      }

      {
        OdTvGeometryDataId childGeometryId0 = pParentEntity0->appendSphere(OdTvPoint(x3, y0, 0.), shellRadius);
        OdTvGeometryDataPtr pChildGeometry0 = childGeometryId0.openObject();
        pChildGeometry0->setColor(OdTvColorDef(255, 0, 0));

        OdTvColorDef resetColor;
        resetColor.setDefault();
        pChildGeometry0->setColor(resetColor);
      }

      OdTvColorDef resetColor;
      resetColor.setDefault();
      pParentEntity0->setColor(resetColor);
    }

    //4. kEdges
    y0 -= 0.33;
    OdTvGeometryDataId parentEntityId1 = modelKeyEntity->appendSubEntity(OD_T("parent1"));
    {
      OdTvEntityPtr pParentEntity1 = parentEntityId1.openAsSubEntity(OdTv::kForWrite);

      pParentEntity1->appendSphere(OdTvPoint(x0, y0, 0.), shellRadius);
      pParentEntity1->setColor(OdTvColorDef(0, 0, 255), OdTvGeometryData::kEdges);

      OdTvGeometryDataId childEntityId1 = pParentEntity1->appendSubEntity(OD_T("childL1"));
      OdTvEntityPtr pChildEntity1 = childEntityId1.openAsSubEntity(OdTv::kForWrite);
      {
        pChildEntity1->appendSphere(OdTvPoint(x1, y0, 0.), shellRadius);
        pChildEntity1->setColor(OdTvColorDef(0, 255, 0), OdTvGeometryData::kEdges);
        pChildEntity1->setLineWeight(5, OdTvGeometryData::kEdges);
      }

      OdTvGeometryDataId childChildEntityId1 = pChildEntity1->appendSubEntity(OD_T("childChild1"));
      OdTvEntityPtr pChildChildEntity1 = childChildEntityId1.openAsSubEntity(OdTv::kForWrite);
      {
        pChildChildEntity1->appendSphere(OdTvPoint(x2, y0, 0.), shellRadius);
      }

      OdTvGeometryDataId childGeometryId1 = pParentEntity1->appendSphere(OdTvPoint(x3, y0, 0.), shellRadius);
      OdTvGeometryDataPtr pChildGeometry1 = childGeometryId1.openObject();
      {
        pChildGeometry1->setColor(OdTvColorDef(255, 0, 0), OdTvGeometryData::kEdges);

        OdTvColorDef resetColor;
        resetColor.setDefault();
        pChildGeometry1->setColor(resetColor, OdTvGeometryData::kEdges);
      }

      OdTvColorDef resetColor;
      resetColor.setDefault();
      pParentEntity1->setColor(resetColor, OdTvGeometryData::kEdges);
    }

    //5. SetColorViaRange
    y0 -= 0.33;
    OdTvGeometryDataId parentEntityId2 = modelKeyEntity->appendSubEntity(OD_T("parent2"));
    {
      OdTvEntityPtr pParentEntity2 = parentEntityId2.openAsSubEntity(OdTv::kForWrite);

      pParentEntity2->appendShellFromSphere(OdTvPoint(x0, y0, 0.), shellRadius);
      pParentEntity2->setColor(OdTvColorDef(0, 0, 255));

      OdTvGeometryDataId childEntityId2 = pParentEntity2->appendSubEntity(OD_T("childL2"));
      OdTvEntityPtr pChildEntity2 = childEntityId2.openAsSubEntity(OdTv::kForWrite);
      {
        pChildEntity2->appendShellFromSphere(OdTvPoint(x1, y0, 0.), shellRadius);
        pChildEntity2->setColor(OdTvColorDef(0, 255, 0), OdTvGeometryData::kEdges);
      }

      OdTvGeometryDataId childChildEntityId2 = pChildEntity2->appendSubEntity(OD_T("childChild2"));
      OdTvEntityPtr pChildChildEntity2 = childChildEntityId2.openAsSubEntity(OdTv::kForWrite);
      {
        pChildChildEntity2->appendShellFromSphere(OdTvPoint(x2, y0, 0.), shellRadius);
      }

      OdTvColorDef resetColor;
      resetColor.setDefault();
      pChildEntity2->setColor(resetColor, OdTvGeometryData::kEdges);

      OdTvGeometryDataId childGeometryId2 = pParentEntity2->appendShellFromSphere(OdTvPoint(x3, y0, 0.), shellRadius);
      OdTvGeometryDataPtr pChildGeometry2 = childGeometryId2.openObject();
      {
        pChildGeometry2->getAsShell()->setEdgeColorsViaRange(0, pChildGeometry2->getAsShell()->getEdgesCount(), OdTvColorDef(255, 0, 0));

        OdTvColorDef resetColor;
        resetColor.setDefault();
        pChildGeometry2->getAsShell()->setEdgeColorsViaRange(0, pChildGeometry2->getAsShell()->getEdgesCount() / 3, resetColor);
      }

    }

  }

}

void OdTvViewerDebugSampleModels::initResetLineWeightModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId)
{
  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId modelKeyEntityId = modelPtr->appendEntity(OD_T("ResetAttributes"));
  {
    OdTvEntityPtr modelKeyEntity = modelKeyEntityId.openObject(OdTv::kForWrite);

    OdTvDatabasePtr pTvDb = databaseId.openObject();
    OdTvTextStyleId textStyleCol = pTvDb->createTextStyle(OD_T("kMiddleCenter"));
    {
      OdTvTextStylePtr pTextStyle = textStyleCol.openObject(OdTv::kForWrite);
      pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleCenter);
      pTextStyle->setTextSize(0.05);
    }
    OdTvTextStyleId textStyleRaw = pTvDb->createTextStyle(OD_T("kMiddleRight"));
    {
      OdTvTextStylePtr pTextStyle = textStyleRaw.openObject(OdTv::kForWrite);
      pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleRight);
      pTextStyle->setTextSize(0.05);
    }

    //1. Add title
    OdTvGeometryDataId titleEntityId = modelKeyEntity->appendSubEntity(OD_T("title"));
    {
      OdTvEntityPtr titleEntity = titleEntityId.openAsSubEntity(OdTv::kForWrite);
      titleEntity->setColor(OdTvColorDef(128, 000, 128), OdTvGeometryData::kAll);
      titleEntity->setLineWeight(2);

      titleEntity->appendText(OdTvPoint(0.0, .75, 0.0), OD_T("LineWeight reset"));
      titleEntity->setTextStyle(textStyleCol);
    }

    //2. Add grid lines
    OdTvVisualizeSampleModelsUtils::appendGridLines(modelKeyEntity, false, 4, 2, -1., 0.66, 0.66, 0.33);

    double x0 = -0.66, x1 = 0., x2 = 0.66, x3 = 1.31;
    double y0 = 0.5;
    double shellRadius = 0.14;

    // column's text
    OdTvGeometryDataId geometries_entity_Id_Text_col = modelKeyEntity->appendSubEntity(OD_T("reset_column_txt"));
    {
      OdTvEntityPtr pTextEntity0 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity0->appendText(OdTvPoint(x0, y0 + 0.18, 0.), OD_T("Parent"));
      pTextEntity0->setTextStyle(textStyleCol);

      OdTvEntityPtr pTextEntity1 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity1->appendText(OdTvPoint(x1, y0 + 0.18, 0.), OD_T("Child"));
      pTextEntity1->setTextStyle(textStyleCol);

      OdTvEntityPtr pTextEntity2 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity2->appendText(OdTvPoint(x2, y0 + 0.18, 0.), OD_T("Child of child"));
      pTextEntity2->setTextStyle(textStyleCol);

      OdTvEntityPtr pTextEntity3 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity3->appendText(OdTvPoint(x3, y0 + 0.18, 0.), OD_T("Child geometry"));
      pTextEntity3->setTextStyle(textStyleCol);
    }
    // row's text
    OdTvGeometryDataId geometries_entity_Id_Text_row = modelKeyEntity->appendSubEntity(OD_T("reset_row_txt"));
    {
      OdTvEntityPtr pTextEntity0 = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0, 0.), OD_T("kAll"));
      pTextEntity0->setTextStyle(textStyleRaw);

      OdTvEntityPtr pTextEntity1 = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity1->appendText(OdTvPoint(x0 - 0.35, y0 - 0.33, 0.), OD_T("kEdges"));
      pTextEntity1->setTextStyle(textStyleRaw);
    }

    //3. kAll
    OdTvGeometryDataId parentEntityId0 = modelKeyEntity->appendSubEntity(OD_T("parent0"));
    {
      OdTvEntityPtr pParentEntity0 = parentEntityId0.openAsSubEntity(OdTv::kForWrite);

      pParentEntity0->appendSphere(OdTvPoint(x0, y0, 0.), shellRadius);
      pParentEntity0->setLineWeight(2);

      OdTvGeometryDataId childEntityId0 = pParentEntity0->appendSubEntity(OD_T("childL0"));
      OdTvEntityPtr pChildEntity0 = childEntityId0.openAsSubEntity(OdTv::kForWrite);
      {
        pChildEntity0->appendSphere(OdTvPoint(x1, y0, 0.), shellRadius);
        pChildEntity0->setLineWeight(5);
      }

      OdTvGeometryDataId childChildEntityId0 = pChildEntity0->appendSubEntity(OD_T("childChild0"));
      OdTvEntityPtr pChildChildEntity0 = childChildEntityId0.openAsSubEntity(OdTv::kForWrite);
      {
        pChildChildEntity0->appendSphere(OdTvPoint(x2, y0, 0.), shellRadius);
      }

      {
        OdTvGeometryDataId childGeometryId0 = pParentEntity0->appendSphere(OdTvPoint(x3, y0, 0.), shellRadius);
        OdTvGeometryDataPtr pChildGeometry0 = childGeometryId0.openObject();

        OdTvLineWeightDef resetLineWeight;
        resetLineWeight.setDefault();
        pChildGeometry0->setLineWeight(resetLineWeight);
      }

      OdTvLineWeightDef resetLineWeight;
      resetLineWeight.setDefault();
      pParentEntity0->setLineWeight(resetLineWeight);
    }

    //4. kEdges
    y0 -= 0.33;
    OdTvGeometryDataId parentEntityId1 = modelKeyEntity->appendSubEntity(OD_T("parent1"));
    {
      OdTvEntityPtr pParentEntity1 = parentEntityId1.openAsSubEntity(OdTv::kForWrite);

      pParentEntity1->appendSphere(OdTvPoint(x0, y0, 0.), shellRadius);
      pParentEntity1->setLineWeight(2, OdTvGeometryData::kEdges);

      OdTvGeometryDataId childEntityId1 = pParentEntity1->appendSubEntity(OD_T("childL1"));
      OdTvEntityPtr pChildEntity1 = childEntityId1.openAsSubEntity(OdTv::kForWrite);
      {
        pChildEntity1->appendSphere(OdTvPoint(x1, y0, 0.), shellRadius);
        pChildEntity1->setLineWeight(5, OdTvGeometryData::kEdges);
      }

      OdTvGeometryDataId childChildEntityId1 = pChildEntity1->appendSubEntity(OD_T("childChild1"));
      OdTvEntityPtr pChildChildEntity1 = childChildEntityId1.openAsSubEntity(OdTv::kForWrite);
      {
        pChildChildEntity1->appendSphere(OdTvPoint(x2, y0, 0.), shellRadius);
      }

      OdTvGeometryDataId childGeometryId1 = pParentEntity1->appendSphere(OdTvPoint(x3, y0, 0.), shellRadius);
      OdTvGeometryDataPtr pChildGeometry1 = childGeometryId1.openObject();
      {
        pChildGeometry1->setLineWeight(5);

        OdTvLineWeightDef resetLineWeight;
        resetLineWeight.setDefault();
        pChildGeometry1->setLineWeight(resetLineWeight);
      }

      OdTvLineWeightDef resetLineWeight;
      resetLineWeight.setDefault();
      pParentEntity1->setLineWeight(resetLineWeight, OdTvGeometryData::kEdges);
    }

  }

}

void OdTvViewerDebugSampleModels::initResetLinetypeModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId)
{
  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId modelKeyEntityId = modelPtr->appendEntity(OD_T("ResetAttributes"));
  {
    OdTvEntityPtr modelKeyEntity = modelKeyEntityId.openObject(OdTv::kForWrite);

    OdTvDatabasePtr pTvDb = databaseId.openObject();
    OdTvTextStyleId textStyleCol = pTvDb->createTextStyle(OD_T("kMiddleCenter"));
    {
      OdTvTextStylePtr pTextStyle = textStyleCol.openObject(OdTv::kForWrite);
      pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleCenter);
      pTextStyle->setTextSize(0.05);
    }
    OdTvTextStyleId textStyleRaw = pTvDb->createTextStyle(OD_T("kMiddleRight"));
    {
      OdTvTextStylePtr pTextStyle = textStyleRaw.openObject(OdTv::kForWrite);
      pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleRight);
      pTextStyle->setTextSize(0.05);
    }

    //1. Add title
    OdTvGeometryDataId titleEntityId = modelKeyEntity->appendSubEntity(OD_T("title"));
    {
      OdTvEntityPtr titleEntity = titleEntityId.openAsSubEntity(OdTv::kForWrite);
      titleEntity->setColor(OdTvColorDef(128, 000, 128), OdTvGeometryData::kAll);
      titleEntity->setLineWeight(2);

      titleEntity->appendText(OdTvPoint(0.0, .75, 0.0), OD_T("Linetype reset"));
      titleEntity->setTextStyle(textStyleCol);
    }

    //2. Add grid lines
    OdTvVisualizeSampleModelsUtils::appendGridLines(modelKeyEntity, false, 4, 3, -1., 0.66, 0.66, 0.33);

    double x0 = -0.66, x1 = 0., x2 = 0.66, x3 = 1.31;
    double y0 = 0.5;
    double shellRadius = 0.14;

    // column's text
    OdTvGeometryDataId geometries_entity_Id_Text_col = modelKeyEntity->appendSubEntity(OD_T("reset_column_txt"));
    {
      OdTvEntityPtr pTextEntity0 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity0->appendText(OdTvPoint(x0, y0 + 0.18, 0.), OD_T("Parent"));
      pTextEntity0->setTextStyle(textStyleCol);

      OdTvEntityPtr pTextEntity1 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity1->appendText(OdTvPoint(x1, y0 + 0.18, 0.), OD_T("Child"));
      pTextEntity1->setTextStyle(textStyleCol);

      OdTvEntityPtr pTextEntity2 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity2->appendText(OdTvPoint(x2, y0 + 0.18, 0.), OD_T("Child of child"));
      pTextEntity2->setTextStyle(textStyleCol);

      OdTvEntityPtr pTextEntity3 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity3->appendText(OdTvPoint(x3, y0 + 0.18, 0.), OD_T("Child geometry"));
      pTextEntity3->setTextStyle(textStyleCol);
    }
    // row's text
    OdTvGeometryDataId geometries_entity_Id_Text_row = modelKeyEntity->appendSubEntity(OD_T("reset_row_txt"));
    {
      OdTvEntityPtr pTextEntity0 = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0, 0.), OD_T("kAll"));
      pTextEntity0->setTextStyle(textStyleRaw);

      OdTvEntityPtr pTextEntity1 = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity1->appendText(OdTvPoint(x0 - 0.35, y0 - 0.33, 0.), OD_T("kEdges"));
      pTextEntity1->setTextStyle(textStyleRaw);

      OdTvEntityPtr pTextEntity2 = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity2->appendText(OdTvPoint(x0 - 0.35, y0 - 0.66, 0.), OD_T("SetLinetypeViaRange"));
      pTextEntity2->setTextStyle(textStyleRaw);
    }

    //3. kAll
    OdTvGeometryDataId parentEntityId0 = modelKeyEntity->appendSubEntity(OD_T("parent0"));
    {
      OdTvEntityPtr pParentEntity0 = parentEntityId0.openAsSubEntity(OdTv::kForWrite);

      pParentEntity0->appendSphere(OdTvPoint(x0, y0, 0.), shellRadius);
      pParentEntity0->setLinetype(OdTvLinetypeDef(OdTvLinetype::kDashDot));
      pParentEntity0->setLinetypeScale(0.05);

      OdTvGeometryDataId childEntityId0 = pParentEntity0->appendSubEntity(OD_T("childL0"));
      OdTvEntityPtr pChildEntity0 = childEntityId0.openAsSubEntity(OdTv::kForWrite);
      {
        pChildEntity0->appendSphere(OdTvPoint(x1, y0, 0.), shellRadius);

        pChildEntity0->setLinetype(OdTvLinetypeDef(OdTvLinetype::kDotted));
        pChildEntity0->setLinetypeScale(0.05);
      }

      OdTvGeometryDataId childChildEntityId0 = pChildEntity0->appendSubEntity(OD_T("childChild0"));
      OdTvEntityPtr pChildChildEntity0 = childChildEntityId0.openAsSubEntity(OdTv::kForWrite);
      {
        pChildChildEntity0->appendSphere(OdTvPoint(x2, y0, 0.), shellRadius);
      }

      {
        OdTvGeometryDataId childGeometryId0 = pParentEntity0->appendSphere(OdTvPoint(x3, y0, 0.), shellRadius);
        OdTvGeometryDataPtr pChildGeometry0 = childGeometryId0.openObject();

        pChildGeometry0->setLinetype(OdTvLinetypeDef(OdTvLinetype::kDashed));
        pChildGeometry0->setLinetypeScale(0.05);

        OdTvLinetypeDef resetLinetype;
        resetLinetype.setDefault();
        pChildGeometry0->setLinetype(resetLinetype);
      }

      OdTvLinetypeDef resetLinetype;
      resetLinetype.setDefault();
      pParentEntity0->setLinetype(resetLinetype);
    }

    //4. kEdges
    y0 -= 0.33;
    OdTvGeometryDataId parentEntityId1 = modelKeyEntity->appendSubEntity(OD_T("parent1"));
    {
      OdTvEntityPtr pParentEntity1 = parentEntityId1.openAsSubEntity(OdTv::kForWrite);
      pParentEntity1->setLinetype(OdTvLinetypeDef(OdTvLinetype::kDashDot), OdTvGeometryData::kEdges);
      pParentEntity1->setLinetypeScale(0.05, OdTvGeometryData::kEdges);

      pParentEntity1->appendSphere(OdTvPoint(x0, y0, 0.), shellRadius);

      OdTvGeometryDataId childEntityId1 = pParentEntity1->appendSubEntity(OD_T("childL1"));
      OdTvEntityPtr pChildEntity1 = childEntityId1.openAsSubEntity(OdTv::kForWrite);
      {
        pChildEntity1->appendSphere(OdTvPoint(x1, y0, 0.), shellRadius);

        pChildEntity1->setLinetype(OdTvLinetypeDef(OdTvLinetype::kDotted), OdTvGeometryData::kEdges);
        pChildEntity1->setLinetypeScale(0.05, OdTvGeometryData::kEdges);
      }

      OdTvGeometryDataId childChildEntityId1 = pChildEntity1->appendSubEntity(OD_T("childChild1"));
      OdTvEntityPtr pChildChildEntity1 = childChildEntityId1.openAsSubEntity(OdTv::kForWrite);
      {
        pChildChildEntity1->appendSphere(OdTvPoint(x2, y0, 0.), shellRadius);
      }

      pParentEntity1->appendPolyline(OdTvPoint(x3 - 0.1, y0, 0.), OdTvPoint(x3 + 0.1, y0, 0.));

      OdTvLinetypeDef resetLinetype;
      resetLinetype.setDefault();
      pParentEntity1->setLinetype(resetLinetype, OdTvGeometryData::kEdges);
    }

    //5. SetLinetypeViaRange
    y0 -= 0.33;
    OdTvGeometryDataId parentEntityId2 = modelKeyEntity->appendSubEntity(OD_T("parent2"));
    {
      OdTvEntityPtr pParentEntity2 = parentEntityId2.openAsSubEntity(OdTv::kForWrite);

      pParentEntity2->appendPolyline(OdTvPoint(x0 - 0.1, y0, 0.), OdTvPoint(x0 + 0.1, y0, 0.));
      pParentEntity2->appendPolyline(OdTvPoint(x1 - 0.1, y0, 0.), OdTvPoint(x1 + 0.1, y0, 0.));
      pParentEntity2->appendPolyline(OdTvPoint(x2 - 0.1, y0, 0.), OdTvPoint(x2 + 0.1, y0, 0.));

      OdTvGeometryDataId childGeometryId2 = pParentEntity2->appendShellFromSphere(OdTvPoint(x3, y0, 0.), shellRadius);
      OdTvGeometryDataPtr pChildGeometry2 = childGeometryId2.openObject();
      {
        pChildGeometry2->getAsShell()->setEdgeLinetypesViaRange(0, pChildGeometry2->getAsShell()->getEdgesCount(), OdTvLinetypeDef(OdTvLinetype::kDashed));
        pChildGeometry2->setLinetypeScale(0.05);

        OdTvLinetypeDef resetLinetype;
        resetLinetype.setDefault();
      }
    }

  }

}

void OdTvViewerDebugSampleModels::initResetLinetypeScaleModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId)
{
  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId modelKeyEntityId = modelPtr->appendEntity(OD_T("ResetAttributes"));
  {
    OdTvEntityPtr modelKeyEntity = modelKeyEntityId.openObject(OdTv::kForWrite);

    OdTvDatabasePtr pTvDb = databaseId.openObject();
    OdTvTextStyleId textStyleCol = pTvDb->createTextStyle(OD_T("kMiddleCenter"));
    {
      OdTvTextStylePtr pTextStyle = textStyleCol.openObject(OdTv::kForWrite);
      pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleCenter);
      pTextStyle->setTextSize(0.05);
    }
    OdTvTextStyleId textStyleRaw = pTvDb->createTextStyle(OD_T("kMiddleRight"));
    {
      OdTvTextStylePtr pTextStyle = textStyleRaw.openObject(OdTv::kForWrite);
      pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleRight);
      pTextStyle->setTextSize(0.05);
    }

    //1. Add title
    OdTvGeometryDataId titleEntityId = modelKeyEntity->appendSubEntity(OD_T("title"));
    {
      OdTvEntityPtr titleEntity = titleEntityId.openAsSubEntity(OdTv::kForWrite);
      titleEntity->setColor(OdTvColorDef(128, 000, 128), OdTvGeometryData::kAll);
      titleEntity->setLineWeight(2);

      titleEntity->appendText(OdTvPoint(0.0, .75, 0.0), OD_T("LinetypeScale reset"));
      titleEntity->setTextStyle(textStyleCol);
    }

    //2. Add grid lines
    OdTvVisualizeSampleModelsUtils::appendGridLines(modelKeyEntity, false, 4, 2, -1., 0.66, 0.66, 0.33);

    double x0 = -0.66, x1 = 0., x2 = 0.66, x3 = 1.31;
    double y0 = 0.5;
    double shellRadius = 0.14;

    // column's text
    OdTvGeometryDataId geometries_entity_Id_Text_col = modelKeyEntity->appendSubEntity(OD_T("reset_column_txt"));
    {
      OdTvEntityPtr pTextEntity0 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity0->appendText(OdTvPoint(x0, y0 + 0.18, 0.), OD_T("Parent"));
      pTextEntity0->setTextStyle(textStyleCol);

      OdTvEntityPtr pTextEntity1 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity1->appendText(OdTvPoint(x1, y0 + 0.18, 0.), OD_T("Child"));
      pTextEntity1->setTextStyle(textStyleCol);

      OdTvEntityPtr pTextEntity2 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity2->appendText(OdTvPoint(x2, y0 + 0.18, 0.), OD_T("Child of child"));
      pTextEntity2->setTextStyle(textStyleCol);

      OdTvEntityPtr pTextEntity3 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity3->appendText(OdTvPoint(x3, y0 + 0.18, 0.), OD_T("Child geometry"));
      pTextEntity3->setTextStyle(textStyleCol);
    }
    // row's text
    OdTvGeometryDataId geometries_entity_Id_Text_row = modelKeyEntity->appendSubEntity(OD_T("reset_row_txt"));
    {
      OdTvEntityPtr pTextEntity0 = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0, 0.), OD_T("kAll"));
      pTextEntity0->setTextStyle(textStyleRaw);

      OdTvEntityPtr pTextEntity1 = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity1->appendText(OdTvPoint(x0 - 0.35, y0 - 0.33, 0.), OD_T("kEdges"));
      pTextEntity1->setTextStyle(textStyleRaw);
    }

    //3. kAll
    OdTvGeometryDataId parentEntityId0 = modelKeyEntity->appendSubEntity(OD_T("parent0"));
    {
      OdTvEntityPtr pParentEntity0 = parentEntityId0.openAsSubEntity(OdTv::kForWrite);
      pParentEntity0->setLinetype(OdTvLinetypeDef(OdTvLinetype::kDash2Dot));
      pParentEntity0->setLinetypeScale(0.05);

      pParentEntity0->appendSphere(OdTvPoint(x0, y0, 0.), shellRadius);

      OdTvGeometryDataId childEntityId0 = pParentEntity0->appendSubEntity(OD_T("childL0"));
      OdTvEntityPtr pChildEntity0 = childEntityId0.openAsSubEntity(OdTv::kForWrite);
      {
        pChildEntity0->appendSphere(OdTvPoint(x1, y0, 0.), shellRadius);

        pChildEntity0->setLinetype(OdTvLinetypeDef(OdTvLinetype::kDash2Dot));
        pChildEntity0->setLinetypeScale(0.05);
      }

      OdTvGeometryDataId childChildEntityId0 = pChildEntity0->appendSubEntity(OD_T("childChild0"));
      OdTvEntityPtr pChildChildEntity0 = childChildEntityId0.openAsSubEntity(OdTv::kForWrite);
      {
        pChildChildEntity0->appendSphere(OdTvPoint(x2, y0, 0.), shellRadius);
      }

      {
        OdTvGeometryDataId childGeometryId0 = pParentEntity0->appendSphere(OdTvPoint(x3, y0, 0.), shellRadius);
        OdTvGeometryDataPtr pChildGeometry0 = childGeometryId0.openObject();

        pChildGeometry0->setLinetype(OdTvLinetypeDef(OdTvLinetype::kDash2Dot));
        pChildGeometry0->setLinetypeScale(0.05);

        pChildGeometry0->setLinetypeScale(1.);
      }

      pParentEntity0->setLinetypeScale(1.);
    }

    //4. kEdges
    y0 -= 0.33;
    OdTvGeometryDataId parentEntityId1 = modelKeyEntity->appendSubEntity(OD_T("parent1"));
    {
      OdTvEntityPtr pParentEntity1 = parentEntityId1.openAsSubEntity(OdTv::kForWrite);
      pParentEntity1->setLinetype(OdTvLinetypeDef(OdTvLinetype::kDash2Dot), OdTvGeometryData::kEdges);
      pParentEntity1->setLinetypeScale(0.05, OdTvGeometryData::kEdges);

      pParentEntity1->appendSphere(OdTvPoint(x0, y0, 0.), shellRadius);

      OdTvGeometryDataId childEntityId1 = pParentEntity1->appendSubEntity(OD_T("childL1"));
      OdTvEntityPtr pChildEntity1 = childEntityId1.openAsSubEntity(OdTv::kForWrite);
      {
        pChildEntity1->appendSphere(OdTvPoint(x1, y0, 0.), shellRadius);

        pChildEntity1->setLinetype(OdTvLinetypeDef(OdTvLinetype::kDash2Dot), OdTvGeometryData::kEdges);
        pChildEntity1->setLinetypeScale(0.05, OdTvGeometryData::kEdges);
      }

      OdTvGeometryDataId childChildEntityId1 = pChildEntity1->appendSubEntity(OD_T("childChild1"));
      OdTvEntityPtr pChildChildEntity1 = childChildEntityId1.openAsSubEntity(OdTv::kForWrite);
      {
        pChildChildEntity1->appendSphere(OdTvPoint(x2, y0, 0.), shellRadius);
      }

      pParentEntity1->appendPolyline(OdTvPoint(x3 - 0.1, y0, 0.), OdTvPoint(x3 + 0.1, y0, 0.));

      pParentEntity1->setLinetypeScale(1., OdTvGeometryData::kEdges);
    }
  }

}

void OdTvViewerDebugSampleModels::initResetLayerModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId)
{
  OdTvDatabasePtr pDb = databaseId.openObject(OdTv::kForWrite);

  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId modelKeyEntityId = modelPtr->appendEntity(OD_T("ResetAttributes"));
  {
    OdTvEntityPtr modelKeyEntity = modelKeyEntityId.openObject(OdTv::kForWrite);

    OdTvDatabasePtr pTvDb = databaseId.openObject();
    OdTvTextStyleId textStyleCol = pTvDb->createTextStyle(OD_T("kMiddleCenter"));
    {
      OdTvTextStylePtr pTextStyle = textStyleCol.openObject(OdTv::kForWrite);
      pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleCenter);
      pTextStyle->setTextSize(0.05);
    }
    OdTvTextStyleId textStyleRaw = pTvDb->createTextStyle(OD_T("kMiddleRight"));
    {
      OdTvTextStylePtr pTextStyle = textStyleRaw.openObject(OdTv::kForWrite);
      pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleRight);
      pTextStyle->setTextSize(0.05);
    }

    //1. Add title
    OdTvGeometryDataId titleEntityId = modelKeyEntity->appendSubEntity(OD_T("title"));
    {
      OdTvEntityPtr titleEntity = titleEntityId.openAsSubEntity(OdTv::kForWrite);
      titleEntity->setColor(OdTvColorDef(128, 000, 128), OdTvGeometryData::kAll);
      titleEntity->setLineWeight(2);

      titleEntity->appendText(OdTvPoint(0.0, .75, 0.0), OD_T("Layer reset"));
      titleEntity->setTextStyle(textStyleCol);
    }

    //2. Add grid lines
    OdTvVisualizeSampleModelsUtils::appendGridLines(modelKeyEntity, false, 4, 3, -1., 0.66, 0.66, 0.33);

    double x0 = -0.66, x1 = 0., x2 = 0.66, x3 = 1.31;
    double y0 = 0.5;
    double shellRadius = 0.14;

    // column's text
    OdTvGeometryDataId geometries_entity_Id_Text_col = modelKeyEntity->appendSubEntity(OD_T("reset_column_txt"));
    {
      OdTvEntityPtr pTextEntity0 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity0->appendText(OdTvPoint(x0, y0 + 0.18, 0.), OD_T("Parent"));
      pTextEntity0->setTextStyle(textStyleCol);

      OdTvEntityPtr pTextEntity1 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity1->appendText(OdTvPoint(x1, y0 + 0.18, 0.), OD_T("Child"));
      pTextEntity1->setTextStyle(textStyleCol);

      OdTvEntityPtr pTextEntity2 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity2->appendText(OdTvPoint(x2, y0 + 0.18, 0.), OD_T("Child of child"));
      pTextEntity2->setTextStyle(textStyleCol);

      OdTvEntityPtr pTextEntity3 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity3->appendText(OdTvPoint(x3, y0 + 0.18, 0.), OD_T("Child geometry"));
      pTextEntity3->setTextStyle(textStyleCol);
    }
    // row's text
    OdTvGeometryDataId geometries_entity_Id_Text_row = modelKeyEntity->appendSubEntity(OD_T("reset_row_txt"));
    {
      OdTvEntityPtr pTextEntity0 = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0, 0.), OD_T("kAll"));
      pTextEntity0->setTextStyle(textStyleRaw);

      OdTvEntityPtr pTextEntity1 = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity1->appendText(OdTvPoint(x0 - 0.35, y0 - 0.33, 0.), OD_T("kEdges"));
      pTextEntity1->setTextStyle(textStyleRaw);

      OdTvEntityPtr pTextEntity2 = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity2->appendText(OdTvPoint(x0 - 0.35, y0 - 0.66, 0.), OD_T("SetLayerViaRange"));
      pTextEntity2->setTextStyle(textStyleRaw);
    }

    // 3. Create layers
    OdTvLayerId lineweightLayer0Id = pDb->createLayer(OD_T("LineweightLayer0"));
    lineweightLayer0Id.openObject(OdTv::kForWrite)->setLineWeight(5);

    OdTvLayerId childGeometrycolorLayer0Id = pDb->createLayer(OD_T("ChildGeometryColorLayer0"));
    childGeometrycolorLayer0Id.openObject(OdTv::kForWrite)->setColor(OdTvColorDef(255, 255, 0));

    OdTvLayerId colorLayer0Id = pDb->createLayer(OD_T("ColorLayer0"));
    colorLayer0Id.openObject(OdTv::kForWrite)->setColor(OdTvColorDef(0, 255, 0));

    //4. kAll
    OdTvGeometryDataId parentEntityId0 = modelKeyEntity->appendSubEntity(OD_T("parent0"));
    {
      OdTvEntityPtr pParentEntity0 = parentEntityId0.openAsSubEntity(OdTv::kForWrite);
      pParentEntity0->setLayer(colorLayer0Id);

      pParentEntity0->appendSphere(OdTvPoint(x0, y0, 0.), shellRadius);

      OdTvGeometryDataId childEntityId0 = pParentEntity0->appendSubEntity(OD_T("childL0"));
      OdTvEntityPtr pChildEntity0 = childEntityId0.openAsSubEntity(OdTv::kForWrite);
      {
        pChildEntity0->appendSphere(OdTvPoint(x1, y0, 0.), shellRadius);

        pChildEntity0->setLayer(lineweightLayer0Id);
      }

      OdTvGeometryDataId childChildEntityId0 = pChildEntity0->appendSubEntity(OD_T("childChild0"));
      OdTvEntityPtr pChildChildEntity0 = childChildEntityId0.openAsSubEntity(OdTv::kForWrite);
      {
        pChildChildEntity0->appendSphere(OdTvPoint(x2, y0, 0.), shellRadius);
      }

      {
        OdTvGeometryDataId childGeometryId0 = pParentEntity0->appendSphere(OdTvPoint(x3, y0, 0.), shellRadius);
        OdTvGeometryDataPtr pChildGeometry0 = childGeometryId0.openObject();

        pChildGeometry0->setLayer(childGeometrycolorLayer0Id);

        OdTvLayerDef resetLayer;
        resetLayer.setDefault();
        pChildGeometry0->setLayer(resetLayer);
      }

      OdTvLayerDef resetLayer;
      resetLayer.setDefault();
      pParentEntity0->setLayer(resetLayer);
    }

    //5. kEdges
    y0 -= 0.33;
    OdTvGeometryDataId parentEntityId1 = modelKeyEntity->appendSubEntity(OD_T("parent1"));
    {
      OdTvEntityPtr pParentEntity1 = parentEntityId1.openAsSubEntity(OdTv::kForWrite);
      pParentEntity1->setLayer(colorLayer0Id, OdTvGeometryData::kEdges);

      pParentEntity1->appendSphere(OdTvPoint(x0, y0, 0.), shellRadius);

      OdTvGeometryDataId childEntityId1 = pParentEntity1->appendSubEntity(OD_T("childL1"));
      OdTvEntityPtr pChildEntity1 = childEntityId1.openAsSubEntity(OdTv::kForWrite);
      {
        pChildEntity1->appendSphere(OdTvPoint(x1, y0, 0.), shellRadius);

        pChildEntity1->setLayer(lineweightLayer0Id, OdTvGeometryData::kEdges);
      }

      OdTvGeometryDataId childChildEntityId1 = pChildEntity1->appendSubEntity(OD_T("childChild1"));
      OdTvEntityPtr pChildChildEntity1 = childChildEntityId1.openAsSubEntity(OdTv::kForWrite);
      {
        pChildChildEntity1->appendSphere(OdTvPoint(x2, y0, 0.), shellRadius);
      }

      pParentEntity1->appendPolyline(OdTvPoint(x3 - 0.1, y0, 0.), OdTvPoint(x3 + 0.1, y0, 0.));

      OdTvLayerDef resetLayer;
      resetLayer.setDefault();
      pParentEntity1->setLayer(resetLayer, OdTvGeometryData::kEdges);
    }

    //6. SetLayerViaRange
    y0 -= 0.33;
    OdTvGeometryDataId parentEntityId2 = modelKeyEntity->appendSubEntity(OD_T("parent2"));
    {
      OdTvEntityPtr pParentEntity2 = parentEntityId2.openAsSubEntity(OdTv::kForWrite);

      pParentEntity2->appendPolyline(OdTvPoint(x0 - 0.1, y0, 0.), OdTvPoint(x0 + 0.1, y0, 0.));
      pParentEntity2->appendPolyline(OdTvPoint(x1 - 0.1, y0, 0.), OdTvPoint(x1 + 0.1, y0, 0.));
      pParentEntity2->appendPolyline(OdTvPoint(x2 - 0.1, y0, 0.), OdTvPoint(x2 + 0.1, y0, 0.));

      OdTvGeometryDataId childGeometryId2 = pParentEntity2->appendShellFromSphere(OdTvPoint(x3, y0, 0.), shellRadius);
      OdTvGeometryDataPtr pChildGeometry2 = childGeometryId2.openObject();
      {
        pChildGeometry2->getAsShell()->setEdgeLayersViaRange(0, pChildGeometry2->getAsShell()->getEdgesCount(), childGeometrycolorLayer0Id);

        OdTvLayerDef resetLayer;
        resetLayer.setDefault();
        pChildGeometry2->getAsShell()->setEdgeLayersViaRange(0, pChildGeometry2->getAsShell()->getEdgesCount() / 3, resetLayer);
      }
    }

  }
}

void OdTvViewerDebugSampleModels::initResetVisibilityModel(OdTvDatabaseId& databaseId, OdTvModelId& modelId)
{
  OdTvModelPtr modelPtr = modelId.openObject(OdTv::kForWrite);
  OdTvEntityId modelKeyEntityId = modelPtr->appendEntity(OD_T("ResetAttributes"));
  {
    OdTvEntityPtr modelKeyEntity = modelKeyEntityId.openObject(OdTv::kForWrite);

    OdTvDatabasePtr pTvDb = databaseId.openObject();
    OdTvTextStyleId textStyleCol = pTvDb->createTextStyle(OD_T("kMiddleCenter"));
    {
      OdTvTextStylePtr pTextStyle = textStyleCol.openObject(OdTv::kForWrite);
      pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleCenter);
      pTextStyle->setTextSize(0.05);
    }
    OdTvTextStyleId textStyleRaw = pTvDb->createTextStyle(OD_T("kMiddleRight"));
    {
      OdTvTextStylePtr pTextStyle = textStyleRaw.openObject(OdTv::kForWrite);
      pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleRight);
      pTextStyle->setTextSize(0.05);
    }

    //1. Add title
    OdTvGeometryDataId titleEntityId = modelKeyEntity->appendSubEntity(OD_T("title"));
    {
      OdTvEntityPtr titleEntity = titleEntityId.openAsSubEntity(OdTv::kForWrite);
      titleEntity->setColor(OdTvColorDef(128, 000, 128), OdTvGeometryData::kAll);
      titleEntity->setLineWeight(2);

      titleEntity->appendText(OdTvPoint(0.0, .75, 0.0), OD_T("Visibility reset"));
      titleEntity->setTextStyle(textStyleCol);
    }

    //2. Add grid lines
    OdTvVisualizeSampleModelsUtils::appendGridLines(modelKeyEntity, false, 4, 3, -1., 0.66, 0.66, 0.33);

    double x0 = -0.66, x1 = 0., x2 = 0.66, x3 = 1.31;
    double y0 = 0.5;
    double shellRadius = 0.14;

    // column's text
    OdTvGeometryDataId geometries_entity_Id_Text_col = modelKeyEntity->appendSubEntity(OD_T("reset_column_txt"));
    {
      OdTvEntityPtr pTextEntity0 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity0->appendText(OdTvPoint(x0, y0 + 0.18, 0.), OD_T("Parent"));
      pTextEntity0->setTextStyle(textStyleCol);

      OdTvEntityPtr pTextEntity1 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity1->appendText(OdTvPoint(x1, y0 + 0.18, 0.), OD_T("Child"));
      pTextEntity1->setTextStyle(textStyleCol);

      OdTvEntityPtr pTextEntity2 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity2->appendText(OdTvPoint(x2, y0 + 0.18, 0.), OD_T("Child of child"));
      pTextEntity2->setTextStyle(textStyleCol);

      OdTvEntityPtr pTextEntity3 = geometries_entity_Id_Text_col.openAsSubEntity(OdTv::kForWrite);
      pTextEntity3->appendText(OdTvPoint(x3, y0 + 0.18, 0.), OD_T("Child geometry"));
      pTextEntity3->setTextStyle(textStyleCol);
    }
    // row's text
    OdTvGeometryDataId geometries_entity_Id_Text_row = modelKeyEntity->appendSubEntity(OD_T("reset_row_txt"));
    {
      OdTvEntityPtr pTextEntity0 = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity0->appendText(OdTvPoint(x0 - 0.35, y0, 0.), OD_T("kAll"));
      pTextEntity0->setTextStyle(textStyleRaw);

      OdTvEntityPtr pTextEntity1 = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity1->appendText(OdTvPoint(x0 - 0.35, y0 - 0.33, 0.), OD_T("kEdges"));
      pTextEntity1->setTextStyle(textStyleRaw);

      OdTvEntityPtr pTextEntity2 = geometries_entity_Id_Text_row.openAsSubEntity(OdTv::kForWrite);
      pTextEntity2->appendText(OdTvPoint(x0 - 0.35, y0 - 0.66, 0.), OD_T("SetVisibilityViaRange"));
      pTextEntity2->setTextStyle(textStyleRaw);
    }

    //3. kAll
    OdTvGeometryDataId parentEntityId0 = modelKeyEntity->appendSubEntity(OD_T("parent0"));
    {
      OdTvEntityPtr pParentEntity0 = parentEntityId0.openAsSubEntity(OdTv::kForWrite);
      pParentEntity0->setVisibility(false);

      pParentEntity0->appendSphere(OdTvPoint(x0, y0, 0.), shellRadius);

      OdTvGeometryDataId childEntityId0 = pParentEntity0->appendSubEntity(OD_T("childL0"));
      OdTvEntityPtr pChildEntity0 = childEntityId0.openAsSubEntity(OdTv::kForWrite);
      {
        pChildEntity0->appendSphere(OdTvPoint(x1, y0, 0.), shellRadius);
        pChildEntity0->setVisibility(true);
      }

      OdTvGeometryDataId childChildEntityId0 = pChildEntity0->appendSubEntity(OD_T("childChild0"));
      OdTvEntityPtr pChildChildEntity0 = childChildEntityId0.openAsSubEntity(OdTv::kForWrite);
      {
        pChildChildEntity0->appendSphere(OdTvPoint(x2, y0, 0.), shellRadius);
      }

      {
        OdTvGeometryDataId childGeometryId0 = pParentEntity0->appendSphere(OdTvPoint(x3, y0, 0.), shellRadius);
        OdTvGeometryDataPtr pChildGeometry0 = childGeometryId0.openObject();
        pChildGeometry0->setVisibility(false);

        OdTvVisibilityDef resetVisibility;
        resetVisibility.setDefault();
        pChildGeometry0->setVisibility(resetVisibility);
      }

      OdTvVisibilityDef resetVisibility;
      resetVisibility.setDefault();
      pParentEntity0->setVisibility(resetVisibility);
    }

    //4. kEdges
    y0 -= 0.33;
    OdTvGeometryDataId parentEntityId1 = modelKeyEntity->appendSubEntity(OD_T("parent1"));
    {
      OdTvEntityPtr pParentEntity1 = parentEntityId1.openAsSubEntity(OdTv::kForWrite);
      pParentEntity1->setVisibility(false, OdTvGeometryData::kEdges);

      pParentEntity1->appendSphere(OdTvPoint(x0, y0, 0.), shellRadius);

      OdTvGeometryDataId childEntityId1 = pParentEntity1->appendSubEntity(OD_T("childL1"));
      OdTvEntityPtr pChildEntity1 = childEntityId1.openAsSubEntity(OdTv::kForWrite);
      {
        pChildEntity1->appendSphere(OdTvPoint(x1, y0, 0.), shellRadius);
        pChildEntity1->setVisibility(true, OdTvGeometryData::kEdges);
      }

      OdTvGeometryDataId childChildEntityId1 = pChildEntity1->appendSubEntity(OD_T("childChild1"));
      OdTvEntityPtr pChildChildEntity1 = childChildEntityId1.openAsSubEntity(OdTv::kForWrite);
      {
        pChildChildEntity1->appendSphere(OdTvPoint(x2, y0, 0.), shellRadius);
      }

      pParentEntity1->appendPolyline(OdTvPoint(x3 - 0.1, y0, 0.), OdTvPoint(x3 + 0.1, y0, 0.));

      OdTvVisibilityDef resetVisibility;
      resetVisibility.setDefault();
      pParentEntity1->setVisibility(resetVisibility, OdTvGeometryData::kEdges);

    }

    //5. SetVisibilityViaRange
    y0 -= 0.33;
    OdTvGeometryDataId parentEntityId2 = modelKeyEntity->appendSubEntity(OD_T("parent2"));
    {
      OdTvEntityPtr pParentEntity2 = parentEntityId2.openAsSubEntity(OdTv::kForWrite);

      pParentEntity2->appendPolyline(OdTvPoint(x0 - 0.1, y0, 0.), OdTvPoint(x0 + 0.1, y0, 0.));
      pParentEntity2->appendPolyline(OdTvPoint(x1 - 0.1, y0, 0.), OdTvPoint(x1 + 0.1, y0, 0.));
      pParentEntity2->appendPolyline(OdTvPoint(x2 - 0.1, y0, 0.), OdTvPoint(x2 + 0.1, y0, 0.));

      OdTvGeometryDataId childGeometryId2 = pParentEntity2->appendShellFromSphere(OdTvPoint(x3, y0, 0.), shellRadius);
      OdTvGeometryDataPtr pChildGeometry2 = childGeometryId2.openObject();
      {
        pChildGeometry2->getAsShell()->setEdgeVisibilitiesViaRange(0, pChildGeometry2->getAsShell()->getEdgesCount(), OdTvVisibilityDef(false));

        OdTvVisibilityDef resetVisibility;
        resetVisibility.setDefault();
        pChildGeometry2->getAsShell()->setEdgeVisibilitiesViaRange(0, pChildGeometry2->getAsShell()->getEdgesCount() / 3, resetVisibility);
      }

    }

  }

}
