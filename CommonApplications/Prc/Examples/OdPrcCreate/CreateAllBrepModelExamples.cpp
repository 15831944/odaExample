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

#include "PrcCommon.h"
#include "PrcFile.h"
#include "PrcBrepModel.h"
#include "PrcBrepData.h"
#include "PrcRepresentationItem.h"
#include "Ge/GeExtents3d.h"
#include "OdPrcCreateStart.h"
#include "PrcCreateTopologyHelper.h"


void FillTopoBrepFace (OdPrcBrepDataPtr brepData, OdPrcSurfacePtr pSurface);
OdPrcSurfacePtr CreateSphere ();
OdPrcSurfacePtr createCylinder ();
OdPrcSurfacePtr CreateCone ();
OdPrcSurfacePtr CreateRuled ();
OdPrcSurfacePtr CreateExtrusion ();
OdPrcSurfacePtr CreateFromCurves ();
OdPrcSurfacePtr CreateRevolution ();
OdPrcSurfacePtr CreateCylindrical ();
OdPrcSurfacePtr CreateNURBS ();
OdPrcSurfacePtr CreateTorus ();
OdPrcSurfacePtr CreateAppleTorus ();
OdPrcSurfacePtr CreateOffset ();
OdPrcSurfacePtr CreateTransform ();
OdPrcSurfacePtr CreatePlane ();
OdPrcSurfacePtr CreateBlend01 ();
OdPrcSurfacePtr CreateBlend02 ();
OdPrcSurfacePtr CreateBlend03 ();

void addLineStyleForBrep (OdPrcFileStructure &newStructure, double r, double g, double b);
void addGraphicDataToBrep (OdPrcFileStructure &newStructure);

void FillTopoBrepModel (OdPrcBrepDataPtr &brepData, int subTest)
{
  if (0 == subTest)
  {
    FillTopoBrepFace(brepData,CreateSphere());
  } 
  else if (1 == subTest)
  {
    FillTopoBrepFace(brepData,createCylinder());
  }
  else if (2 == subTest)
  {
    FillTopoBrepFace(brepData,CreateCone());
  }
  else if (3 == subTest)
  {
    FillTopoBrepFace(brepData,CreateRuled());
  }
  else if (4 == subTest)
  {
    FillTopoBrepFace(brepData,CreateExtrusion());
  }
  else if (5 == subTest)
  {
    FillTopoBrepFace(brepData,CreateFromCurves());
  }
  else if (6 == subTest)
  {
    FillTopoBrepFace(brepData,CreateRevolution());
  }
  else if (7 == subTest)
  {
    FillTopoBrepFace(brepData,CreateCylindrical());
  }
  else if (8 == subTest)
  {
    FillTopoBrepFace(brepData,CreateNURBS());
  }
  else if (9 == subTest)
  {
    FillTopoBrepFace(brepData,CreateTorus());
  }
  else if (10 == subTest)
  {
    FillTopoBrepFace(brepData,CreateAppleTorus());
  }
  else if (11 == subTest)
  {
    FillTopoBrepFace(brepData,CreateOffset());
  }
  else if (12 == subTest)
  {
    FillTopoBrepFace(brepData,CreateTransform());
  }
  else if (13 == subTest)
  {
    FillTopoBrepFace(brepData,CreatePlane());
  }
  else if (14 == subTest)
  {
    FillTopoBrepFace(brepData,CreateBlend01());
  }
  else if (15 == subTest)
  {
    FillTopoBrepFace(brepData,CreateBlend02());
  }
  else if (16 == subTest)
  {
    FillTopoBrepFace(brepData,CreateBlend03());
  }
  else
  {
    ODA_ASSERT(false);
  }
}


void setName (OdPrcBrepModelPtr &brepModel, int subTest)
{
  if (0 == subTest)
  {
    brepModel->name().setName(L"Sphere");
  } 
  else if (1 == subTest)
  {
    brepModel->name().setName(L"Cylinder");
  }
  else if (2 == subTest)
  {
    brepModel->name().setName(L"Cone");
  }
  else if (3 == subTest)
  {
    brepModel->name().setName(L"Ruled");
  }
  else if (4 == subTest)
  {
    brepModel->name().setName(L"Extrusion");
  }
  else if (5 == subTest)
  {
    brepModel->name().setName(L"FromCurves");
  }
  else if (6 == subTest)
  {
    brepModel->name().setName(L"Revolution");
  }
  else if (7 == subTest)
  {
    brepModel->name().setName(L"Cylindrical");
  }
  else if (8 == subTest)
  {
    brepModel->name().setName(L"NURBS");
  }
  else if (9 == subTest)
  {
    brepModel->name().setName(L"TorusT1_origin");
  }
  else if (10 == subTest)
  {
    brepModel->name().setName(L"TorusT2_apple");
  }
  else if (11 == subTest)
  {
    brepModel->name().setName(L"Offset");
  }
  else if (12 == subTest)
  {
    brepModel->name().setName(L"Transform");
  }
  else if (13 == subTest)
  {
    brepModel->name().setName(L"Plane");
  }
  else if (14 == subTest)
  {
    brepModel->name().setName(L"Blend01");
  }
  else if (15 == subTest)
  {
    brepModel->name().setName(L"Blend02");
  }
  else if (16 == subTest)
  {
    brepModel->name().setName(L"Blend03");
  }
  else
  {
    ODA_ASSERT(false);
  }
}

OdPrcProductOccurrencePtr CreateTopologyCommonForBrepModel(OdPrcFilePtr &pFile, OdGeExtents3d &extents, int idx)
{
  OdPrcFileStructurePtr newStructure = pFile->fileStructures().last();

  // product occurrence section
  OdPrcProductOccurrencePtr newProductOccurrence = OdPrcProductOccurrence::createObject();
  newStructure->addObject(newProductOccurrence);

  OdPrcPartDefinitionPtr newDefinition = createPartDefinition(*newStructure, *newProductOccurrence);

  // bounding box
  newDefinition->boundingBox().box() = extents;

  // create brep model
  OdPrcBrepModelPtr newBrep = OdPrcBrepModel::createObject();
  newStructure->addObject(newBrep);
  newBrep->setIsClosed(true);

  setName(newBrep,idx);
  newDefinition->representationItem().push_back(newBrep->objectId());

  // create Brep Data
  OdPrcBrepDataPtr newBrepData = OdPrcBrepData::createObject();
  newStructure->addObject(newBrepData);
  newBrepData->boundingBox().box() = extents;
  newBrepData->contentBody().setBoundingBoxBehaviour(2);
  
  // set reference to this body in representation item
  newBrep->setReferenceToBody(newBrepData);

  // file structure geometry section
  OdPrcTopoContextPtr newTopoContext = createTopoContext(*newStructure);
  newTopoContext->appendBody(newBrepData->objectId());

  return newProductOccurrence;
}

// tweak scales of bodies for this test
void ApplyScalingForBrep (OdGeMatrix3d &geMatrix, int idx)
{
  if (idx == 1)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(6000.0);
    geMatrix = geMatrix * tmpgeMatrix;

    OdGeMatrix3d tmp2geMatrix;
    tmp2geMatrix.setToRotation(90.0f, OdGeVector3d::kYAxis);
    geMatrix = geMatrix * tmp2geMatrix;
    return;
  }

  if (idx < 3)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(6000.0);
    geMatrix = geMatrix * tmpgeMatrix;
    return;
  }

  if (idx == 3)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(2000.0);
    geMatrix = geMatrix * tmpgeMatrix;
    return;
  }
  
  if (idx == 4)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(2000.0);
    geMatrix = geMatrix * tmpgeMatrix;

    OdGeMatrix3d tmp2geMatrix;
    tmp2geMatrix.setToRotation(90.0f, OdGeVector3d::kYAxis);
    geMatrix = geMatrix * tmp2geMatrix;
    return;
  }

  if (idx == 5)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(10000.0);
    geMatrix = geMatrix * tmpgeMatrix;

    OdGeVector3d translateVect (-1.0, 0.0, 0.0);
    OdGeMatrix3d tmp2geMatrix;
    tmp2geMatrix.setTranslation(translateVect);
    geMatrix = geMatrix * tmp2geMatrix;
    return;
  }

  if (idx < 8)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(10000.0);
    geMatrix = geMatrix * tmpgeMatrix;
    return;
  }

  if (idx == 8)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(2000.0);
    geMatrix = geMatrix * tmpgeMatrix;
    return;
  }

  if (idx == 9)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(6000.0);
    geMatrix = geMatrix * tmpgeMatrix;
    return;
  }

  if (idx == 10)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(12000.0);
    geMatrix = geMatrix * tmpgeMatrix;
    return;
  }

  if (idx == 11)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(5000.0);
    geMatrix = geMatrix * tmpgeMatrix;

    OdGeVector3d translateVect (0.0, 5.0, 0.0);
    OdGeMatrix3d tmp2geMatrix;
    tmp2geMatrix.setTranslation(translateVect);
    geMatrix = geMatrix * tmp2geMatrix;
    return;
  }

  if (idx == 12)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(7000.0);
    geMatrix = geMatrix * tmpgeMatrix;
    return;
  }

  if (idx == 13)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(8000.0);
    geMatrix = geMatrix * tmpgeMatrix;

    OdGeVector3d translateVect (-1.0, 1.0, 0.0);
    OdGeMatrix3d tmp2geMatrix;
    tmp2geMatrix.setTranslation(translateVect);
    geMatrix = geMatrix * tmp2geMatrix;
    return;
  }

  if (idx == 14)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(15000.0);
    geMatrix = geMatrix * tmpgeMatrix;

    OdGeVector3d translateVect (-0.5, 0.0, 0.0);
    OdGeMatrix3d tmp2geMatrix;
    tmp2geMatrix.setTranslation(translateVect);
    geMatrix = geMatrix * tmp2geMatrix;

    OdGeMatrix3d tmp3geMatrix;
    tmp3geMatrix.setToRotation(0.35, OdGeVector3d::kYAxis);
    geMatrix = geMatrix * tmp3geMatrix;
    return;
  }

  if (idx == 15)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(7000.0);
    geMatrix = geMatrix * tmpgeMatrix;

    OdGeVector3d translateVect (0.0, 53.0, -32.0);
    OdGeMatrix3d tmp2geMatrix;
    tmp2geMatrix.setTranslation(translateVect);
    geMatrix = geMatrix * tmp2geMatrix;
    return;
  }

  if (idx == 16)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(4000.0);
    geMatrix = geMatrix * tmpgeMatrix;

    OdGeVector3d translateVect (-12.0, 8850.0, -5463.0);
    OdGeMatrix3d tmp2geMatrix;
    tmp2geMatrix.setTranslation(translateVect);
    geMatrix = geMatrix * tmp2geMatrix;
    return;
  }
}

OdPrcFilePtr CreateAllBrepModels (void)
{
  // common
  OdGeExtents3d extents;
  extents.addPoint(OdGePoint3d(-5,-5,-5));
  extents.addPoint(OdGePoint3d(5,5,5));
  OdPrcFilePtr pFile = createTopologyCommon();
  OdPrcFileStructure &newStructure = *(pFile->fileStructures().last());

  OdPrcProductOccurrencePtr rootOccurrence = pFile->modelFileData().getStartRootOccurrences().last().openObject(kForWrite);
  OdPrcObjectIdArray &son_occurrences = rootOccurrence->referencesOfProductOccurrence().getSonProductOccurrences();
  OdPrcTransformation3d shift;

  // loop for all breps
  const int countImplementedBodies = 17;
  for (int idx = 0; idx < countImplementedBodies; ++idx)
  {
    OdPrcProductOccurrencePtr newProductOccurrence = CreateTopologyCommonForBrepModel(pFile, extents, idx);

    // Add line style to globals
    addLineStyleForBrep(newStructure, 1.0f, 0.0f, 0.0f);

    // Add graphic
    addGraphicDataToBrep(newStructure);

    // fill it with Brep Data
    OdPrcTopoContextPtr newTopoContext = newStructure.fileStructureGeometry().fileStructureExactGeometry().topologicalContext().last();
    OdPrcBrepDataPtr brepData = newTopoContext->bodies().last().safeOpenObject(kForWrite);
    FillTopoBrepModel(brepData, idx);

    OdPrcPartDefinitionPtr newDefinition = newStructure.fileStructureTree().partDefinition().last().safeOpenObject(kForWrite);
    OdPrcBrepModelPtr pBrepModel = newDefinition->representationItem().last().openObject(kForWrite);
    ODA_VERIFY(pBrepModel->updateIsClosedFlag() == eOk);

    // add transformation
    OdGeVector3d translateVect (idx%4 * (-30000), idx/4 * -30000, 0);
    OdGeMatrix3d geMatrix;
    geMatrix.setTranslation(translateVect);
    ApplyScalingForBrep(geMatrix, idx);
    shift.set(geMatrix);
    newProductOccurrence->setLocation(&shift);

    // add reference to root product occurrence
    son_occurrences.push_back(newProductOccurrence->objectId());
  }
  return pFile;
}


void CreateAllBrepModelExamples (OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  ODA_ASSERT(mode == kAllBrepModelExamples);

  // create prc with all brep examples
  OdPrcFilePtr pFile = CreateAllBrepModels();

  // export prc
  pFile->writeFile(pPrcStream);
}
