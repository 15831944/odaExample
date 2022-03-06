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
#include "OdPrcCreateStart.h"
#include "PrcCreateTopologyHelper.h"
#include "PrcFileStructure.h"
#include "PrcBrepModel.h"
#include "PrcBrepData.h"
#include "PrcFillBrepByVertexHelper.h"

void addLineStyleForBrep (OdPrcFileStructure &newStructure, double r, double g, double b);
void addGraphicDataToBrep (OdPrcFileStructure &newStructure);

OdPrcFilePtr CreatePRCCommonForBrepComplex (void);
void CreateTopologyCommonForComplex (OdPrcFileStructurePtr curStructure, OdPrcProductOccurrencePtr curOccurrence, OdGeExtents3d &extents, const char* brepModelName);
void addColorToBaseWithGraphics(OdPrcFileStructurePtr curFileStructure, OdPrcBaseWithGraphicsPtr pBaseWithGraphics, double r, double g, double b);

// main
void brepByVerticesExample (OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  // create prc BrepData Model
  OdPrcFilePtr pFile = createTopologyCommon();
  OdPrcFileStructure &newStructure = *(pFile->fileStructures().last());
  OdPrcProductOccurrencePtr pRootPO = newStructure.fileStructureTree().internalData().getRootProductOccurrenceID().openObject(kForWrite);
  OdPrcPartDefinitionPtr newDefinition = createPartDefinition(newStructure, *pRootPO);
  OdPrcTopoContextPtr newTopoContext = createTopoContext(newStructure);
  
  OdGeExtents3d extents(OdGePoint3d(0, 0, 0), OdGePoint3d(1, 1, 1));
  OdPrcRepresentationItemPtr newRepItem = createRI<OdPrcBrepModel>(newStructure, *newDefinition);
  newDefinition->boundingBox().box() = extents;
  OdPrcBrepDataPtr brepData = createBody<OdPrcBrepData>(newStructure, *newTopoContext, *newRepItem);
  brepData->boundingBox().box() = extents;
  brepData->contentBody().setBoundingBoxBehaviour(2);

  // Add line style to globals
  addLineStyleForBrep(newStructure, 1.0f, 0.0f, 0.0f);

  // Add graphic
  addGraphicDataToBrep(newStructure);
  pRootPO->name().setName(L"BrepByVertices");


  OdGePoint3dArray vertexList;
  OdArray<OdUInt32Array> vertexOrder;
  if (mode == kBoxByVerticesExample)
  {
    newRepItem->name().setName(L"BoxByVertices");

    // generate list of vertices
    vertexList.push_back(OdGePoint3d(0,0,20));
    vertexList.push_back(OdGePoint3d(20,0,20));
    vertexList.push_back(OdGePoint3d(20,20,20));
    vertexList.push_back(OdGePoint3d(0,20,20));
    vertexList.push_back(OdGePoint3d(0,20,0));
    vertexList.push_back(OdGePoint3d(20,20,0));
    vertexList.push_back(OdGePoint3d(20,0,0));
    vertexList.push_back(OdGePoint3d(0,0,0));

    // generate faces
    OdUInt32Array face1, face2, face3, face4, face5, face6;

    face1.push_back(1); face1.push_back(2); face1.push_back(3); face1.push_back(4);
    face2.push_back(3); face2.push_back(2); face2.push_back(7); face2.push_back(6);
    face3.push_back(5); face3.push_back(6); face3.push_back(7); face3.push_back(8);
    face4.push_back(1); face4.push_back(4); face4.push_back(5); face4.push_back(8);
    face5.push_back(2); face5.push_back(1); face5.push_back(8); face5.push_back(7);
    face6.push_back(4); face6.push_back(3); face6.push_back(6); face6.push_back(5);

    vertexOrder.push_back(face1); vertexOrder.push_back(face2); vertexOrder.push_back(face3);
    vertexOrder.push_back(face4); vertexOrder.push_back(face5); vertexOrder.push_back(face6);
  }
  else if (mode == kPyramidByVerticesExample)
  {
    newRepItem->name().setName(L"PyramidByVertices");

    // generate list of vertices
    vertexList.push_back(OdGePoint3d(0,0,0));
    vertexList.push_back(OdGePoint3d(20,0,0));
    vertexList.push_back(OdGePoint3d(20,20,0));
    vertexList.push_back(OdGePoint3d(0,20,0));
    vertexList.push_back(OdGePoint3d(10,10,25));

    // generate faces
    OdUInt32Array face1, face2, face3, face4, face5;

    face1.push_back(1); face1.push_back(2); face1.push_back(3); face1.push_back(4);
    face2.push_back(5); face2.push_back(3); face2.push_back(2);
    face3.push_back(5); face3.push_back(2); face3.push_back(1);
    face4.push_back(5); face4.push_back(1); face4.push_back(4);
    face5.push_back(5); face5.push_back(4); face5.push_back(3);

    vertexOrder.push_back(face1); vertexOrder.push_back(face2); vertexOrder.push_back(face3);
    vertexOrder.push_back(face4); vertexOrder.push_back(face5);
  }
  else if (mode == kTqsSolidByVerticesExample)
  {
    newRepItem->name().setName(L"TqsSolidByVertices");

    // generate list of vertices
    // extruded solid
    vertexList.push_back(OdGePoint3d(90,175,300));  //1
    vertexList.push_back(OdGePoint3d(110,175,300)); //2
    vertexList.push_back(OdGePoint3d(110,225,300)); //3
    vertexList.push_back(OdGePoint3d(90,225,300));  //4
    vertexList.push_back(OdGePoint3d(90,225,0));    //5
    vertexList.push_back(OdGePoint3d(110,225,0));   //6
    vertexList.push_back(OdGePoint3d(110,175,0));   //7
    vertexList.push_back(OdGePoint3d(90,175,0));    //8

    // foot foundation
    vertexList.push_back(OdGePoint3d(25,125,-40));  //9
    vertexList.push_back(OdGePoint3d(175,125,-40)); //10
    vertexList.push_back(OdGePoint3d(115,170,0));   //11
    vertexList.push_back(OdGePoint3d(85,170,0));    //12
    vertexList.push_back(OdGePoint3d(175,275,-40)); //13
    vertexList.push_back(OdGePoint3d(115,230,0));   //14
    vertexList.push_back(OdGePoint3d(25,275,-40));  //15
    vertexList.push_back(OdGePoint3d(85,230,0));    //16

    // bottom box
    vertexList.push_back(OdGePoint3d(25,125,-50));  //17
    vertexList.push_back(OdGePoint3d(25,275,-50));  //18
    vertexList.push_back(OdGePoint3d(175,275,-50)); //19
    vertexList.push_back(OdGePoint3d(175,125,-50)); //20

    // generate faces
    // extruded solid
    OdUInt32Array face1, face2, face3, face4, face5, face6;

    face1.push_back(1); face1.push_back(2); face1.push_back(3); face1.push_back(4);
    face2.push_back(2); face2.push_back(1); face2.push_back(8); face2.push_back(7);
    face3.push_back(3); face3.push_back(2); face3.push_back(7); face3.push_back(6);
    face4.push_back(4); face4.push_back(3); face4.push_back(6); face4.push_back(5);
    face5.push_back(1); face5.push_back(4); face5.push_back(5); face5.push_back(8);
    face6.push_back(5); face6.push_back(6); face6.push_back(7); face6.push_back(8);

    vertexOrder.push_back(face1); vertexOrder.push_back(face2); vertexOrder.push_back(face3);
    vertexOrder.push_back(face4); vertexOrder.push_back(face5); vertexOrder.push_back(face6);

    // foot foundation
    face1.clear(); face2.clear(); face3.clear(); face4.clear(); face5.clear(); face6.clear();

    face1.push_back(9); face1.push_back(10); face1.push_back(11); face1.push_back(12);
    face2.push_back(10); face2.push_back(13); face2.push_back(14); face2.push_back(11);
    face3.push_back(13); face3.push_back(15); face3.push_back(16); face3.push_back(14);
    face4.push_back(15); face4.push_back(9); face4.push_back(12); face4.push_back(16);
    face5.push_back(12); face5.push_back(11); face5.push_back(14); face5.push_back(16);
    face6.push_back(9); face6.push_back(15); face6.push_back(13); face6.push_back(10);

    vertexOrder.push_back(face1); vertexOrder.push_back(face2); vertexOrder.push_back(face3);
    vertexOrder.push_back(face4); vertexOrder.push_back(face5); vertexOrder.push_back(face6);

    // bottom box
    face1.clear(); face2.clear(); face3.clear(); face4.clear(); face5.clear(); face6.clear();

    face1.push_back(9); face1.push_back(10); face1.push_back(13); face1.push_back(15);
    face2.push_back(17); face2.push_back(20); face2.push_back(10); face2.push_back(9);
    face3.push_back(20); face3.push_back(19); face3.push_back(13); face3.push_back(10);
    face4.push_back(19); face4.push_back(18); face4.push_back(15); face4.push_back(13);
    face5.push_back(18); face5.push_back(17); face5.push_back(9); face5.push_back(15);
    face6.push_back(17); face6.push_back(18); face6.push_back(19); face6.push_back(20);

    vertexOrder.push_back(face1); vertexOrder.push_back(face2); vertexOrder.push_back(face3);
    vertexOrder.push_back(face4); vertexOrder.push_back(face5); vertexOrder.push_back(face6);
  }
  else
  {
    ODA_VERIFY(!"Wrong Mode!!!");
    return;
  }

  ODA_VERIFY(fillBrepDataByVertex(brepData,vertexList,vertexOrder) == eOk);

  OdPrcBrepModelPtr pBrepModel = newDefinition->representationItem().last().openObject(kForWrite);
  newStructure.fileStructureGeometry().fileStructureExactGeometry().updateCoedgeNeighbours();
  ODA_VERIFY(pBrepModel->updateIsClosedFlag() == eOk);

  // export prc
  pFile->writeFile(pPrcStream);
}

void manyBrepByVerticesExample (OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  if (mode != kManyTqsSolidByVerticesExample)
  {
    ODA_VERIFY(!"Wrong Mode!!!");
    return;
  }

  // common
  OdGeExtents3d extents;
  extents.addPoint(OdGePoint3d(0,0,0));
  extents.addPoint(OdGePoint3d(1,1,1));
  OdPrcFilePtr pFile = CreatePRCCommonForBrepComplex();

  // Is taken into account the order of addition FS
  OdPrcFileStructurePtr tqsStructure = addNewFileStructure(*pFile);
  OdPrcFileStructurePtr rootStructure = addNewFileStructure(*pFile);

  tqsStructure->fileStructureId() = OdPrcUniqueId(1,2,3,4);
  rootStructure->fileStructureId() = OdPrcUniqueId(5,6,7,8);

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // create root Tqs product occurrence
  OdPrcProductOccurrencePtr rootOccurrenceTqs = OdPrcProductOccurrence::createObject();
  tqsStructure->addObject(rootOccurrenceTqs);
  tqsStructure->fileStructureTree().internalData().setRootProductOccurrence(rootOccurrenceTqs->objectId());
  rootOccurrenceTqs->name().setName(L"Tqs");
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // create root product occurrence
  OdPrcProductOccurrencePtr rootOccurrence = OdPrcProductOccurrence::createObject();
  rootStructure->addObject(rootOccurrence);
  OdPrcObjectIdArray &son_occurrences = rootOccurrence->referencesOfProductOccurrence().getSonProductOccurrences();
  pFile->modelFileData().addStartRootOccurrence(*rootOccurrence);
  rootStructure->fileStructureTree().internalData().setRootProductOccurrence(rootOccurrence->objectId());
  rootOccurrence->name().setName(L"ROOT");
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // fill BrepData
  {
    CreateTopologyCommonForComplex(tqsStructure, rootOccurrenceTqs, extents, "TqsSolid");

    // fill it with Brep Data
    OdPrcTopoContextPtr newTopoContext = tqsStructure->fileStructureGeometry().fileStructureExactGeometry().topologicalContext().last();
    OdPrcBrepDataPtr brepData = newTopoContext->bodies().last().safeOpenObject(kForWrite);

    OdGePoint3dArray vertexList;
    OdArray<OdUInt32Array> vertexOrder;

    // generate list of vertices
    // extruded solid
    vertexList.push_back(OdGePoint3d(90,175,300));  //1
    vertexList.push_back(OdGePoint3d(110,175,300)); //2
    vertexList.push_back(OdGePoint3d(110,225,300)); //3
    vertexList.push_back(OdGePoint3d(90,225,300));  //4
    vertexList.push_back(OdGePoint3d(90,225,0));    //5
    vertexList.push_back(OdGePoint3d(110,225,0));   //6
    vertexList.push_back(OdGePoint3d(110,175,0));   //7
    vertexList.push_back(OdGePoint3d(90,175,0));    //8

    // foot foundation
    vertexList.push_back(OdGePoint3d(25,125,-40));  //9
    vertexList.push_back(OdGePoint3d(175,125,-40)); //10
    vertexList.push_back(OdGePoint3d(115,170,0));   //11
    vertexList.push_back(OdGePoint3d(85,170,0));    //12
    vertexList.push_back(OdGePoint3d(175,275,-40)); //13
    vertexList.push_back(OdGePoint3d(115,230,0));   //14
    vertexList.push_back(OdGePoint3d(25,275,-40));  //15
    vertexList.push_back(OdGePoint3d(85,230,0));    //16

    // bottom box
    vertexList.push_back(OdGePoint3d(25,125,-50));  //17
    vertexList.push_back(OdGePoint3d(25,275,-50));  //18
    vertexList.push_back(OdGePoint3d(175,275,-50)); //19
    vertexList.push_back(OdGePoint3d(175,125,-50)); //20

    // generate faces
    // extruded solid
    OdUInt32Array face1, face2, face3, face4, face5, face6;

    face1.push_back(1); face1.push_back(2); face1.push_back(3); face1.push_back(4);
    face2.push_back(2); face2.push_back(1); face2.push_back(8); face2.push_back(7);
    face3.push_back(3); face3.push_back(2); face3.push_back(7); face3.push_back(6);
    face4.push_back(4); face4.push_back(3); face4.push_back(6); face4.push_back(5);
    face5.push_back(1); face5.push_back(4); face5.push_back(5); face5.push_back(8);
    face6.push_back(5); face6.push_back(6); face6.push_back(7); face6.push_back(8);

    vertexOrder.push_back(face1); vertexOrder.push_back(face2); vertexOrder.push_back(face3);
    vertexOrder.push_back(face4); vertexOrder.push_back(face5); vertexOrder.push_back(face6);

    // foot foundation
    face1.clear(); face2.clear(); face3.clear(); face4.clear(); face5.clear(); face6.clear();

    face1.push_back(9); face1.push_back(10); face1.push_back(11); face1.push_back(12);
    face2.push_back(10); face2.push_back(13); face2.push_back(14); face2.push_back(11);
    face3.push_back(13); face3.push_back(15); face3.push_back(16); face3.push_back(14);
    face4.push_back(15); face4.push_back(9); face4.push_back(12); face4.push_back(16);
    face5.push_back(12); face5.push_back(11); face5.push_back(14); face5.push_back(16);
    face6.push_back(9); face6.push_back(15); face6.push_back(13); face6.push_back(10);

    vertexOrder.push_back(face1); vertexOrder.push_back(face2); vertexOrder.push_back(face3);
    vertexOrder.push_back(face4); vertexOrder.push_back(face5); vertexOrder.push_back(face6);

    // bottom box
    face1.clear(); face2.clear(); face3.clear(); face4.clear(); face5.clear(); face6.clear();

    face1.push_back(9); face1.push_back(10); face1.push_back(13); face1.push_back(15);
    face2.push_back(17); face2.push_back(20); face2.push_back(10); face2.push_back(9);
    face3.push_back(20); face3.push_back(19); face3.push_back(13); face3.push_back(10);
    face4.push_back(19); face4.push_back(18); face4.push_back(15); face4.push_back(13);
    face5.push_back(18); face5.push_back(17); face5.push_back(9); face5.push_back(15);
    face6.push_back(17); face6.push_back(18); face6.push_back(19); face6.push_back(20);

    vertexOrder.push_back(face1); vertexOrder.push_back(face2); vertexOrder.push_back(face3);
    vertexOrder.push_back(face4); vertexOrder.push_back(face5); vertexOrder.push_back(face6);

    ODA_VERIFY(fillBrepDataByVertex(brepData,vertexList,vertexOrder) == eOk);

    OdPrcPartDefinitionPtr newDefinitionTqs = tqsStructure->fileStructureTree().partDefinition().last().safeOpenObject(kForWrite);
    OdPrcBrepModelPtr pBrepModelTqs = newDefinitionTqs->representationItem().last().openObject(kForWrite);
    tqsStructure->fileStructureGeometry().fileStructureExactGeometry().updateCoedgeNeighbours();
    ODA_VERIFY(pBrepModelTqs->updateIsClosedFlag() == eOk);
  }

  OdPrcTransformation3d shift;
  double r(0), g(0), b(0);
  for (int idx = 0; idx < 40000; idx++)
  {
    OdPrcProductOccurrencePtr newProductOccurrenceForTqs = OdPrcProductOccurrence::createObject();

    // set color
    if (idx%3 == 0)
    {
      r = 1; g = 0; b = 0;
    }
    else if (idx%2 == 0)
    {
      r = 0; g = 1; b = 0;
    }
    else
    {
      r = 0; g = 0; b = 1;
    }
    addColorToBaseWithGraphics(rootStructure, newProductOccurrenceForTqs, r, g, b);

    char intStr[33] = "";
    sprintf(intStr, "%d", idx);
    char name[40] = "child ";
    strcat(name,intStr);
    newProductOccurrenceForTqs->name().setName(name);
    rootStructure->addObject(newProductOccurrenceForTqs);

    // add transformation
    OdGeVector3d translateVect(idx%400 * 160, idx/400 * 160, 0);
    OdGeMatrix3d geMatrix;
    geMatrix.setTranslation(translateVect);
    shift.set(geMatrix);
    newProductOccurrenceForTqs->setLocation(&shift);

    newProductOccurrenceForTqs->referencesOfProductOccurrence().setPrototype(rootOccurrenceTqs->objectId());

    son_occurrences.push_back(newProductOccurrenceForTqs->objectId());
  }

  // export prc
  {
    pFile->writeFile(pPrcStream);
  }
}

