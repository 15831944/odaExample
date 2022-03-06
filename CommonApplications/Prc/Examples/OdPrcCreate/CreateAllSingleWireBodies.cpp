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

#include <PrcCommon.h>
#include "PrcFile.h"
#include <DynamicLinker.h>
#include "PrcSingleWireBody.h"
#include "Ge/GeExtents3d.h"
#include "PrcRepresentationItem.h"
#include "PrcWireCurve.h"
#include "OdPrcCreateStart.h"
#include "PrcCreateTopologyHelper.h"


void FillTopoSingleWireBodyForLine (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForNURBS (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForCircle (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForPolyLine (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForHyperbola (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForParabola (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForEllipse (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForOnSurf (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForHelixT0 (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForHelixT1 (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForIntersection (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForBlend02Boundary (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForComposite (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForTransform (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForOffset (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForEquation (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForPolyLine2d (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForEquation2d (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForNURBS2d (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForComposite2d (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForTransform2d (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForLine2d (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForCircle2d (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForHyperbola2d (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForParabola2d (OdPrcSingleWireBodyPtr &wireBody);
void FillTopoSingleWireBodyForEllipse2d (OdPrcSingleWireBodyPtr &wireBody);

void FillTopoSingleWireBody (OdPrcSingleWireBodyPtr &wireBody, int subTest)
{
  if (0 == subTest)
  {
    FillTopoSingleWireBodyForLine(wireBody);
  } 
  else if (1 == subTest)
  {
    FillTopoSingleWireBodyForNURBS(wireBody);
  }
  else if (2 == subTest)
  {
    FillTopoSingleWireBodyForCircle(wireBody);
  }
  else if (3 == subTest)
  {
    FillTopoSingleWireBodyForPolyLine(wireBody);
  }
  else if (4 == subTest)
  {
    FillTopoSingleWireBodyForHyperbola(wireBody);
  }
  else if (5 == subTest)
  {
    FillTopoSingleWireBodyForParabola(wireBody);
  }
  else if (6 == subTest)
  {
    FillTopoSingleWireBodyForEllipse(wireBody);
  }
  else if (7 == subTest)
  {
    FillTopoSingleWireBodyForOnSurf(wireBody);
  }
  else if (8 == subTest)
  {
    FillTopoSingleWireBodyForHelixT0(wireBody);
  }
  else if (9 == subTest)
  {
    FillTopoSingleWireBodyForIntersection(wireBody);
  }
  else if (10 == subTest)
  {
    FillTopoSingleWireBodyForComposite(wireBody);
  }
  else if (11 == subTest)
  {
    FillTopoSingleWireBodyForBlend02Boundary(wireBody);
  }
  else if (12 == subTest)
  {
    FillTopoSingleWireBodyForHelixT1(wireBody);
  }
  else if (13 == subTest)
  {
    FillTopoSingleWireBodyForTransform(wireBody);
  }
  else if (14 == subTest)
  {
    FillTopoSingleWireBodyForOffset(wireBody);
  }
  else if (15 == subTest)
  {
    FillTopoSingleWireBodyForEquation(wireBody);
  }
  else if (16 == subTest)
  {
    FillTopoSingleWireBodyForPolyLine2d(wireBody);
  }
  else if (17 == subTest)
  {
    FillTopoSingleWireBodyForEquation2d(wireBody);
  }
  else if (18 == subTest)
  {
    FillTopoSingleWireBodyForNURBS2d(wireBody);
  }
  else if (19 == subTest)
  {
    FillTopoSingleWireBodyForComposite2d(wireBody);
  }
  else if (20 == subTest)
  {
    FillTopoSingleWireBodyForTransform2d(wireBody);
  }
  else if (21 == subTest)
  {
    FillTopoSingleWireBodyForLine2d(wireBody);
  }
  else if (22 == subTest)
  {
    FillTopoSingleWireBodyForCircle2d(wireBody);
  }
  else if (23 == subTest)
  {
    FillTopoSingleWireBodyForHyperbola2d(wireBody);
  }
  else if (24 == subTest)
  {
    FillTopoSingleWireBodyForParabola2d(wireBody);
  }
  else if (25 == subTest)
  {
    FillTopoSingleWireBodyForEllipse2d(wireBody);
  }
  else
  {
    ODA_ASSERT(!"Invalid subTest number");
  }
}

void setName (OdPrcWireCurvePtr &newCurve, int subTest)
{
  if (0 == subTest)
  {
    newCurve->name().setName(L"line");
  } 
  else if (1 == subTest)
  {
    newCurve->name().setName(L"NURBS3d");
  }
  else if (2 == subTest)
  {
    newCurve->name().setName(L"Circle");
  }
  else if (3 == subTest)
  {
    newCurve->name().setName(L"polyline3d");
  }
  else if (4 == subTest)
  {
    newCurve->name().setName(L"hyperbola");
  }
  else if (5 == subTest)
  {
    newCurve->name().setName(L"parabola");
  }
  else if (6 == subTest)
  {
    newCurve->name().setName(L"ellipse");
  }
  else if (7 == subTest)
  {
    newCurve->name().setName(L"on surf");
  }
  else if (8 == subTest)
  {
    newCurve->name().setName(L"helix T0");
  }
  else if (9 == subTest)
  {
    newCurve->name().setName(L"intersection");
  }
  else if (10 == subTest)
  {
    newCurve->name().setName(L"composite3d");
  }
  else if (11 == subTest)
  {
    newCurve->name().setName(L"blend02boundary");
  }
  else if (12 == subTest)
  {
    newCurve->name().setName(L"helix T1");
  }
  else if (13 == subTest)
  {
    newCurve->name().setName(L"transform3d");
  }
  else if (14 == subTest)
  {
    newCurve->name().setName(L"offset");
  }
  else if (15 == subTest)
  {
    newCurve->name().setName(L"equation3d");
  }
  else if (16 == subTest)
  {
    newCurve->name().setName(L"polyLine2d");
  }
  else if (17 == subTest)
  {
    newCurve->name().setName(L"equation2d");
  }
  else if (18 == subTest)
  {
    newCurve->name().setName(L"NURBS2d");
  }
  else if (19 == subTest)
  {
    newCurve->name().setName(L"composite2d");
  }
  else if (20 == subTest)
  {
    newCurve->name().setName(L"transform2d");
  }
  else if (21 == subTest)
  {
    newCurve->name().setName(L"line 2d");
  }
  else if (22 == subTest)
  {
    newCurve->name().setName(L"circle 2d");
  }
  else if (23 == subTest)
  {
    newCurve->name().setName(L"hyperbola 2d");
  }
  else if (24 == subTest)
  {
    newCurve->name().setName(L"parabola 2d");
  }
  else if (25 == subTest)
  {
    newCurve->name().setName(L"ellipse 2d");
  }
  else
  {
    ODA_ASSERT(!"Invalid subTest number");
  }
}

OdPrcProductOccurrencePtr CreateTopologyCommonForSingleWire(OdPrcFilePtr &pFile, OdGeExtents3d &extents, int idx)
{
  OdPrcFileStructurePtr newStructure = pFile->fileStructures().last();

  // product occurrence section
  OdPrcProductOccurrencePtr newProductOccurrence = OdPrcProductOccurrence::createObject();
  newStructure->addObject(newProductOccurrence);

  OdPrcPartDefinitionPtr newDefinition = createPartDefinition(*newStructure, *newProductOccurrence);
  
  // - create single wire body
  OdPrcSingleWireBodyPtr wireBody = OdPrcSingleWireBody::createObject();
  newStructure->addObject(wireBody);

  // file structure geometry section
  OdPrcTopoContextPtr newTopoContext = createTopoContext(*newStructure);
  newTopoContext->appendBody(wireBody->objectId());

  // - create curve representation item
  OdPrcWireCurvePtr newCurve = OdPrcWireCurve::createObject();
  newStructure->addObject(newCurve);
  setName(newCurve, idx);
  newCurve->setReferenceToBody(wireBody);
  newDefinition->representationItem().push_back(newCurve->objectId());

  // bounding box
  newDefinition->boundingBox().box() = extents;

  return newProductOccurrence;
}

// tweak scales of bodies for this test
void ApplyScaling (OdGeMatrix3d &geMatrix, int idx)
{
  if (idx < 4)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(30.0);
    geMatrix = geMatrix * tmpgeMatrix;
    return;
  }
  
  if (idx == 4)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(2.5);
    geMatrix = geMatrix * tmpgeMatrix;

    OdGeMatrix3d tmp2geMatrix;
    tmp2geMatrix.setToRotation(90.0f, OdGeVector3d::kYAxis);
    geMatrix = geMatrix * tmp2geMatrix;

    return;
  }

  if (idx < 8)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(5.0);
    geMatrix = geMatrix * tmpgeMatrix;
    return;
  }

  if (idx == 8)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(2.0);
    geMatrix = geMatrix * tmpgeMatrix;
    return;
  }

  if (idx == 9)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(4000.0);
    geMatrix = geMatrix * tmpgeMatrix;

    OdGeVector3d translateVect (-0.125, -0.045, 0.135);
    OdGeMatrix3d tmp2geMatrix;
    tmp2geMatrix.setTranslation(translateVect);
    geMatrix = geMatrix * tmp2geMatrix;

    return;
  }

  if (idx == 11)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(4000.0);
    geMatrix = geMatrix * tmpgeMatrix;

    OdGeVector3d translateVect (-0.125, -0.045, -0.03);
    OdGeMatrix3d tmp2geMatrix;
    tmp2geMatrix.setTranslation(translateVect);
    geMatrix = geMatrix * tmp2geMatrix;

    return;
  }

  if (idx < 12)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(5.0);
    geMatrix = geMatrix * tmpgeMatrix;
    return;
  }

  if (idx == 12)
  {
    return;
  }

  if (idx < 16)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(7.5);
    geMatrix = geMatrix * tmpgeMatrix;
    return;
  }

  if (idx < 20)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(10);
    geMatrix = geMatrix * tmpgeMatrix;
    return;
  }

  if (idx == 20)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToRotation(OdaPI/2,tmpgeMatrix.getCsZAxis(),tmpgeMatrix.getCsOrigin());      
    geMatrix = geMatrix * tmpgeMatrix;
    tmpgeMatrix.setToScaling(10);
    geMatrix = geMatrix * tmpgeMatrix;
    return;
  }

  if ((idx < 26) && (idx != 23))
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(10.0);
    geMatrix = geMatrix * tmpgeMatrix;
    return;
  }

  if (idx == 23)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(5.0);
    geMatrix = geMatrix * tmpgeMatrix;
    return;
  }
}

OdPrcFilePtr CreateAllWiresModel (void)
{
  // common
  OdGeExtents3d extents;
  extents.addPoint(OdGePoint3d(0,0,0));
  extents.addPoint(OdGePoint3d(1,1,1));
  OdPrcFilePtr pFile = createTopologyCommon();
  OdPrcFileStructure &newStructure = *(pFile->fileStructures().last());

  OdPrcProductOccurrencePtr rootOccurrence = pFile->modelFileData().getStartRootOccurrences().last().openObject(kForWrite);
  OdPrcObjectIdArray &son_occurrences = rootOccurrence->referencesOfProductOccurrence().getSonProductOccurrences();

  OdPrcTransformation3d shift;

  // loop for all wire bodies
  const int countImplementedBodies = 25;
  for (int idx = 0; idx < countImplementedBodies; ++idx)
  {
    OdPrcProductOccurrencePtr newProductOccurrence = CreateTopologyCommonForSingleWire(pFile, extents, idx);

    // fill it with curve
    OdPrcTopoContextPtr newTopoContext = newStructure.fileStructureGeometry().fileStructureExactGeometry().topologicalContext().last();
    OdPrcSingleWireBodyPtr wireBody = newTopoContext->bodies().last().safeOpenObject(kForWrite);;
    FillTopoSingleWireBody(wireBody, idx);

    // add transformation
    //OdPrcProductOccurrence &newProductOccurrence = *newStructure.fileStructureTree().productOccurrence()[idx];
    OdGeVector3d translateVect (idx%4 * (-100), idx/4 * -100, 0);
    OdGeMatrix3d geMatrix;
    geMatrix.setTranslation(translateVect);
    ApplyScaling(geMatrix, idx);
    shift.set(geMatrix);
    newProductOccurrence->setLocation(&shift);

    // add reference to root product occurrence
    //son_occurrences.push_back(newProductOccurrence->objectId());
    son_occurrences.push_back(newProductOccurrence->objectId());
  }

  return pFile;
}


void CreateAllSingleWireBodies (OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  ODA_ASSERT(mode == kAllSingleWireBodies);

  // create prc with all single wire bodies
  OdPrcFilePtr pFile = CreateAllWiresModel();

  // export prc
  pFile->writeFile(pPrcStream);
}
