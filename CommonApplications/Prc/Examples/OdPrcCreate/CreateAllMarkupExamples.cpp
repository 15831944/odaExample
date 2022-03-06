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
#include "PrcMarkupTess.h"
#include "PrcAnnotationItem.h"
#include "Ge/GeExtents3d.h"
#include "OdPrcCreateStart.h"
#include "PrcCreateTopologyHelper.h"


void FillTopoMarkups (OdPrcFileStructure &newStructure,OdPrcProductOccurrencePtr &newProductOccurrence, OdPrcMarkupTessPtr mTess, OdPrcMarkup::MarkupType type, OdPrcMarkup::MarkupSubType subtype, OdPrcMarkupLeaderPtrArray arr_leader, OdPrcName name);

OdPrcMarkupTessPtr CreatePlainTextMarkup (OdPrcFileStructure &pCurFS);
OdPrcMarkupTessPtr CreateDistanceDimensionMarkup (OdPrcFileStructure &pCurFS);
OdPrcMarkupTessPtr CreateDimensionRadiusMarkup (OdPrcFileStructure &pCurFS);
OdPrcMarkupTessPtr CreateDiameterDimensionMarkup (OdPrcFileStructure &pCurFS);
OdPrcMarkupTessPtr CreateTangentDiameterDimensionMarkup (OdPrcFileStructure &pCurFS);
OdPrcMarkupTessPtr createCylinderDiameterDimensionMarkup (OdPrcFileStructure &pCurFS);
OdPrcMarkupTessPtr CreateLengthDimensionMarkup (OdPrcFileStructure &pCurFS);
OdPrcMarkupTessPtr CreateAngleDimensionMarkup (OdPrcFileStructure &pCurFS);
OdPrcMarkupTessPtr CreateDatumIdentifierMarkup (OdPrcFileStructure &pCurFS);
OdPrcMarkupTessPtr CreateDatumTargetMarkup (OdPrcFileStructure &pCurFS);
OdPrcMarkupTessPtr CreateGDTMarkup (OdPrcFileStructure &pCurFS);
OdPrcMarkupTessPtr CreateRoughnessMarkup (OdPrcFileStructure &pCurFS);
OdPrcMarkupTessPtr CreateTableMarkup (OdPrcFileStructure &pCurFS);
OdPrcMarkupLeaderPtrArray CreateNoLeader();
OdPrcMarkupLeaderPtrArray CreateDistanceDimensionLeader(OdPrcFileStructure &pCurFS);
OdPrcMarkupLeaderPtrArray CreateDimensionRadiusLeader(OdPrcFileStructure &pCurFS);
OdPrcMarkupLeaderPtrArray CreateTangentDiameterDimensionLeader(OdPrcFileStructure &pCurFS);
OdPrcMarkupLeaderPtrArray createCylinderDiameterDimensionLeader(OdPrcFileStructure &pCurFS);
OdPrcMarkupLeaderPtrArray CreateAngleDimensionLeader(OdPrcFileStructure &pCurFS);
OdPrcMarkupLeaderPtrArray CreateDatumIdentifierLeader(OdPrcFileStructure &pCurFS);
OdPrcMarkupLeaderPtrArray CreateDatumTargetLeader(OdPrcFileStructure &pCurFS);

void FillTopoMarkup (OdPrcFileStructure &newStructure,OdPrcProductOccurrencePtr &newProductOccurrence, int subTest)
{
  OdPrcName name;
  if (0 == subTest)
  {
    name.setName(L"PlainTextMarkup");
    FillTopoMarkups(newStructure,newProductOccurrence,CreatePlainTextMarkup(newStructure),OdPrcMarkup::kText,OdPrcMarkup::kUnknownSubtype,CreateNoLeader(), name);
  } 
  else if (1 == subTest)
  {
    name.setName(L"DistanceDimensionMarkup");  
    FillTopoMarkups(newStructure,newProductOccurrence,CreateDistanceDimensionMarkup(newStructure),OdPrcMarkup::kDimension,OdPrcMarkup::kDimension_Distance,CreateDistanceDimensionLeader(newStructure), name);
  }
  else if (2 == subTest)
  {
    name.setName(L"DimensionRadiusMarkup");  
    FillTopoMarkups(newStructure,newProductOccurrence,CreateDimensionRadiusMarkup(newStructure),OdPrcMarkup::kDimension,OdPrcMarkup::kDimension_Radius,CreateDimensionRadiusLeader(newStructure), name);
  }
  else if (3 == subTest)
  {
    name.setName(L"DiameterDimensionMarkup");  
    FillTopoMarkups(newStructure,newProductOccurrence,CreateDiameterDimensionMarkup(newStructure),OdPrcMarkup::kDimension,OdPrcMarkup::kDimension_Diameter,CreateNoLeader(), name);
  }
  else if (4 == subTest)
  {
    name.setName(L"TangentDiameterDimensionMarkup");  
    FillTopoMarkups(newStructure,newProductOccurrence,CreateTangentDiameterDimensionMarkup(newStructure),OdPrcMarkup::kDimension,OdPrcMarkup::kDimension_Diameter_Tangent,CreateTangentDiameterDimensionLeader(newStructure), name);
  }
  else if (5 == subTest)
  {
    name.setName(L"CylinderDiameterDimensionMarkup");  
    FillTopoMarkups(newStructure,newProductOccurrence,createCylinderDiameterDimensionMarkup(newStructure),OdPrcMarkup::kDimension,OdPrcMarkup::kDimension_Diameter_Cylinder,createCylinderDiameterDimensionLeader(newStructure), name);
  }
  else if (6 == subTest)
  {
    name.setName(L"LengthDimensionMarkup");  
    FillTopoMarkups(newStructure,newProductOccurrence,CreateLengthDimensionMarkup(newStructure),OdPrcMarkup::kDimension,OdPrcMarkup::kDimension_Length,CreateNoLeader(), name);
  }
  else if (7 == subTest)
  {
    name.setName(L"AngleDimensionMarkup");  
    FillTopoMarkups(newStructure,newProductOccurrence,CreateAngleDimensionMarkup(newStructure),OdPrcMarkup::kDimension,OdPrcMarkup::kDimension_Angle,CreateAngleDimensionLeader(newStructure), name);
  }
  else if (8 == subTest)
  {
    name.setName(L"DatumIdentifierMarkup");  
    FillTopoMarkups(newStructure,newProductOccurrence,CreateDatumIdentifierMarkup(newStructure),OdPrcMarkup::kDatum,OdPrcMarkup::kDatum_Ident,CreateDatumIdentifierLeader(newStructure), name);
  }
  else if (9 == subTest)
  {
    name.setName(L"DatumTargetMarkup");  
    FillTopoMarkups(newStructure,newProductOccurrence,CreateDatumTargetMarkup(newStructure),OdPrcMarkup::kDatum,OdPrcMarkup::kDatum_Target,CreateDatumTargetLeader(newStructure), name);
  }
  else if (10 == subTest)
  {
    name.setName(L"GDTMarkup");  
    FillTopoMarkups(newStructure,newProductOccurrence,CreateGDTMarkup(newStructure),OdPrcMarkup::kGdt,OdPrcMarkup::kGdt_Fcf,CreateNoLeader(), name);
  }
  else if (11 == subTest)
  {
    name.setName(L"RoughnessMarkup");  
    FillTopoMarkups(newStructure,newProductOccurrence,CreateRoughnessMarkup(newStructure),OdPrcMarkup::kRoughness,OdPrcMarkup::kUnknownSubtype,CreateNoLeader(), name);
  }
  else if (12 == subTest)
  {
    name.setName(L"TableMarkup");  
    FillTopoMarkups(newStructure,newProductOccurrence,CreateTableMarkup(newStructure),OdPrcMarkup::kTable,OdPrcMarkup::kUnknownSubtype,CreateNoLeader(), name);
  }
  else
  {
    ODA_ASSERT(false);
  }
}

// tweak scales of bodies for this test
void ApplyScalingForMarkup (OdGeMatrix3d &geMatrix, int idx)
{
  if (idx == 0)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(2.0);
    geMatrix = geMatrix * tmpgeMatrix;
    return;
  }
  if (idx == 1)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(5);
    geMatrix = geMatrix * tmpgeMatrix;

    OdGeVector3d translateVect (1, 0, 0);
    OdGeMatrix3d tmp2geMatrix;
    tmp2geMatrix.setTranslation(translateVect);
    geMatrix = geMatrix * tmp2geMatrix;

    return;
  }
  if (idx == 2)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(6);
    geMatrix = geMatrix * tmpgeMatrix;

    OdGeVector3d translateVect (1, 0, 0);
    OdGeMatrix3d tmp2geMatrix;
    tmp2geMatrix.setTranslation(translateVect);
    geMatrix = geMatrix * tmp2geMatrix;

    return;
  }
  if (idx == 5)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(6);
    geMatrix = geMatrix * tmpgeMatrix;

    OdGeVector3d translateVect (3, 0, 0);
    OdGeMatrix3d tmp2geMatrix;
    tmp2geMatrix.setTranslation(translateVect);
    geMatrix = geMatrix * tmp2geMatrix;

    return;
  }
  if (idx == 7)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(5);
    geMatrix = geMatrix * tmpgeMatrix;

    OdGeVector3d translateVect (6, 4, 0);
    OdGeMatrix3d tmp2geMatrix;
    tmp2geMatrix.setTranslation(translateVect);
    geMatrix = geMatrix * tmp2geMatrix;

    return;
  }
  if (idx == 8)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(5);
    geMatrix = geMatrix * tmpgeMatrix;

    OdGeVector3d translateVect (4, 0, 0);
    OdGeMatrix3d tmp2geMatrix;
    tmp2geMatrix.setTranslation(translateVect);
    geMatrix = geMatrix * tmp2geMatrix;

    return;
  }
  if (idx == 9)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(5);
    geMatrix = geMatrix * tmpgeMatrix;

    OdGeVector3d translateVect (3, 0, 0);
    OdGeMatrix3d tmp2geMatrix;
    tmp2geMatrix.setTranslation(translateVect);
    geMatrix = geMatrix * tmp2geMatrix;

    return;
  }
  if (idx < 10)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(4.5);
    geMatrix = geMatrix * tmpgeMatrix;
    return;
  }
  if (idx == 10)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(2);
    geMatrix = geMatrix * tmpgeMatrix;
    return;
  }
  if (idx == 11)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(8);
    geMatrix = geMatrix * tmpgeMatrix;

    OdGeVector3d translateVect (-2, -2, 0);
    OdGeMatrix3d tmp2geMatrix;
    tmp2geMatrix.setTranslation(translateVect);
    geMatrix = geMatrix * tmp2geMatrix;

    return;
  }
  if (idx == 12)
  {
    OdGeMatrix3d tmpgeMatrix;
    tmpgeMatrix.setToScaling(4);
    geMatrix = geMatrix * tmpgeMatrix;

    OdGeVector3d translateVect (12, 0, 0);
    OdGeMatrix3d tmp2geMatrix;
    tmp2geMatrix.setTranslation(translateVect);
    geMatrix = geMatrix * tmp2geMatrix;

    return;
  }
}

OdPrcFilePtr CreateAllMarkups (void)
{
  // common
  OdGeExtents3d extents;
  extents.addPoint(OdGePoint3d(0,0,0));
  extents.addPoint(OdGePoint3d(1,1,1));
  OdPrcFilePtr pFile = createTopologyCommon();
  OdPrcFileStructurePtr pFS = pFile->fileStructures().last();

  OdPrcTransformation3d shift;

  // loop for all markups
  const int countImplementedBodies = 13;
  for (int idx = 0; idx < countImplementedBodies; ++idx)
  {
    OdPrcProductOccurrencePtr pRootPO = pFS->fileStructureTree().internalData().getRootProductOccurrenceID().openObject(kForWrite);
    OdPrcProductOccurrencePtr pPO = createProductOccurrence(*pFS, *pRootPO);
    OdPrcPartDefinitionPtr pPD = createPartDefinition(*pFS, *pPO);
    pPD->boundingBox().box() = extents;

    FillTopoMarkup(*pFS, pPO, idx);

    // add transformation
    OdGeVector3d translateVect (idx%3 * 50, idx/3 * (-40), 0);
    OdGeMatrix3d geMatrix;
    geMatrix.setTranslation(translateVect);
    ApplyScalingForMarkup(geMatrix, idx);
    shift.set(geMatrix);
    pPO->setLocation(&shift);
  }
  return pFile;
}


void CreateAllMarkupExamples (OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  ODA_ASSERT(mode == kAllMarkupExamples);

  // create prc with all markups examples
  OdPrcFilePtr pFile = CreateAllMarkups();

  // export prc
  pFile->writeFile(pPrcStream);
}
