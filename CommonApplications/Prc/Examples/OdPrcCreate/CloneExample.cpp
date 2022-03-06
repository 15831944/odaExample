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

#include "OdPrcCreateStart.h"

#include "PrcConnex.h"
#include "PrcBrepData.h"
#include "PrcCreateTopologyHelper.h"
#include "AppServices/PrcHostAppServices.h"

struct OdPrcCloneMap
{
  std::map<OdRxObjectPtr, OdRxObjectPtr> mapOld2New;
  OdPrcFileStructurePtr pTargetDatabase;
  //OdPrcFileStructurePtr pInputDatabase;
};

void copyPrcObjectById(OdPrcObjectId & pNewObjectId, const OdPrcObjectId & pObjectId, OdPrcCloneMap & mapOld2New);

#include "PrcLinePattern.h"
void copyPrcLinePattern(OdPrcLinePatternPtr & pNewLinePattern, const OdPrcLinePatternPtr & pLinePattern, OdPrcCloneMap & mapOld2New)
{
  if (pLinePattern.isNull())
  {
    pNewLinePattern = NULL;
    return;
  }
  std::map<OdRxObjectPtr, OdRxObjectPtr>::const_iterator pIt = mapOld2New.mapOld2New.find(pLinePattern);
  if (pIt != mapOld2New.mapOld2New.end())
  {
    pNewLinePattern = pIt->second;
    return;
  }
  pNewLinePattern = OdPrcLinePattern::createObject();
  mapOld2New.mapOld2New[pLinePattern] = pNewLinePattern;
  mapOld2New.pTargetDatabase->addObject(pNewLinePattern);
  mapOld2New.pTargetDatabase->fileStructureGlobals().linePatterns().push_back(pNewLinePattern->id());

  pNewLinePattern->length() = pLinePattern->length();
  pNewLinePattern->setPhase(pLinePattern->phase());
  pNewLinePattern->setIsRealLength(pLinePattern->isRealLength());
}

#include "PrcCategory1LineStyle.h"
void copyPrcCategory1LineStyle(OdPrcCategory1LineStylePtr & pNewCategory1LineStype, const OdPrcCategory1LineStylePtr & pCategory1LineStype, OdPrcCloneMap & mapOld2New)
{
  if (pCategory1LineStype.isNull())
  {
    pNewCategory1LineStype = NULL;
    return;
  }
  std::map<OdRxObjectPtr, OdRxObjectPtr>::const_iterator pIt = mapOld2New.mapOld2New.find(pCategory1LineStype);
  if (pIt != mapOld2New.mapOld2New.end())
  {
    pNewCategory1LineStype = pIt->second;
    return;
  }
  pNewCategory1LineStype = OdPrcCategory1LineStyle::createObject();
  mapOld2New.mapOld2New[pCategory1LineStype] = pNewCategory1LineStype;
  mapOld2New.pTargetDatabase->addObject(pNewCategory1LineStype);

  mapOld2New.pTargetDatabase->fileStructureGlobals().category1LineStyles().push_back(pNewCategory1LineStype->id());

  pNewCategory1LineStype->setLineWidth(pCategory1LineStype->lineWidth());
  if (!pCategory1LineStype->getLinePatternID().isNull())
  {
    OdPrcObjectId pNewLinePattern;
    copyPrcObjectById(pNewLinePattern, pCategory1LineStype->getLinePatternID(), mapOld2New);
    pNewCategory1LineStype->setLinePatternID(pNewLinePattern);
  }
  else
  {
    //OdUInt32        m_idx_picture; TODO
    ODA_ASSERT(0);
  }

  OdInt8 nTransparency;
  if (pCategory1LineStype->getTransparency(nTransparency))
  {
    pNewCategory1LineStype->setTransparency(nTransparency);
  }
  else
  {
    pNewCategory1LineStype->clearTransparency();
  }

  OdInt8 nAddData;
  if (pCategory1LineStype->getAdditionalData1(nAddData))
  {
    pNewCategory1LineStype->setAdditionalData1(nAddData);
  }
  else
  {
    pNewCategory1LineStype->clearAdditionalData1();
  }

  if (pCategory1LineStype->getAdditionalData2(nAddData))
  {
    pNewCategory1LineStype->setAdditionalData2(nAddData);
  }
  else
  {
    pNewCategory1LineStype->clearAdditionalData2();
  }

  if (pCategory1LineStype->getAdditionalData3(nAddData))
  {
    pNewCategory1LineStype->setAdditionalData3(nAddData);
  }
  else
  {
    pNewCategory1LineStype->clearAdditionalData3();
  }

  OdPrcFileStructurePtr pInputDatabase = pCategory1LineStype->objectId().database();
  if (pCategory1LineStype->getColor().isInit())
  {
    OdCmEntityColor cmColor = pCategory1LineStype->getTrueColor();
    pNewCategory1LineStype->setColor(mapOld2New.pTargetDatabase->fileStructureGlobals().colors().size());
    mapOld2New.pTargetDatabase->fileStructureGlobals().colors().push_back(cmColor); //TODO: avoid duplicate colors
  }
  else
  {
    //pNewCategory1LineStype->setMaterialID(pCategory1LineStype->getMaterialID()); TODO!
    ODA_ASSERT(0);
  }
}

void copyPrcObjectById(OdPrcObjectId & pNewObjectId, const OdPrcObjectId & pObjectId, OdPrcCloneMap & mapOld2New)
{
  OdPrcObjectPtr pObj = pObjectId.openObject();
  if (pObj->isKindOf(OdPrcCategory1LineStyle::desc()))
  {
    OdPrcCategory1LineStylePtr pNewCategory1LineStyle;
    copyPrcCategory1LineStyle(pNewCategory1LineStyle, pObj, mapOld2New);
    pNewObjectId = pNewCategory1LineStyle->id();
  }
  else if (pObj->isKindOf(OdPrcLinePattern::desc()))
  {
    OdPrcLinePatternPtr pNewLinePattern;
    copyPrcLinePattern(pNewLinePattern, pObj, mapOld2New);
    pNewObjectId = pNewLinePattern->id();
  }
  else
  {
    ODA_ASSERT(0);
  }
}

#include "PrcGraphics.h"
void copyPrcGraphics(OdPrcGraphics & pNewGraphics, const OdPrcGraphics & pGraphics, OdPrcCloneMap & mapOld2New)
{
  copyPrcObjectById(pNewGraphics.styleId(), pGraphics.styleId(), mapOld2New);
  pNewGraphics.setLayerIndex(pGraphics.layerIndex());
  pNewGraphics.setBehaviourBitField(pGraphics.behaviourBitField());
}

#include "PrcBaseGeometry.h"
void copyPrcBaseGeometry(OdPrcBaseGeometry & newBaseGeometry, const OdPrcBaseGeometry & baseGeometry)
{
  if (baseGeometry.hasBaseInformation())
  {
    newBaseGeometry.setBaseInformation(true);
    newBaseGeometry.attributeData() = baseGeometry.attributeData();
    newBaseGeometry.name() = baseGeometry.name();
    newBaseGeometry.setIdentifier(baseGeometry.identifier());
  }
  else
  {
    newBaseGeometry.setBaseInformation(false);
  }
}

#include "PrcContentSurface.h"
void copyPrcContentSurface(OdPrcContentSurface & newContentSurface, const OdPrcContentSurface & contentSurface)
{
  copyPrcBaseGeometry(newContentSurface.baseGeometry(), contentSurface.baseGeometry());
  newContentSurface.set_extendInfo(contentSurface.extendInfo());
}

#include "PrcContentCurve.h"
void copyPrcContentCurve(OdPrcContentCurve & newContentCurve, const OdPrcContentCurve & contentCurve)
{
  copyPrcBaseGeometry(newContentCurve.baseGeometry(), contentCurve.baseGeometry());
  newContentCurve.setExtendInfo(contentCurve.extendInfo());
}
void copyPrcBaseTopology(OdPrcBaseTopology & pNewBaseTopology, const OdPrcBaseTopology & pBaseTopology)
{
  pNewBaseTopology.name() = pBaseTopology.name();
  pNewBaseTopology.attributeData() = pBaseTopology.attributeData();
  pNewBaseTopology.setIdentifier(pBaseTopology.identifier());
  pNewBaseTopology.setBaseInformation(pBaseTopology.baseInformation());
}


#include "PrcMultipleVertex.h"
#include "PrcUniqueVertex.h"
void copyPrcVertex(OdPrcTopoItemPtr & pNewVertex, const OdPrcTopoItemPtr & pVertex, OdPrcCloneMap & mapOld2New)
{
  if (pVertex.isNull())
  {
    pNewVertex = NULL;
    return;
  }
  std::map<OdRxObjectPtr, OdRxObjectPtr>::const_iterator pIt = mapOld2New.mapOld2New.find(pVertex);
  if (pIt != mapOld2New.mapOld2New.end())
  {
    pNewVertex = pIt->second;
    return;
  }
  if (pVertex->isKindOf(OdPrcUniqueVertex::desc()))
  {
    OdPrcUniqueVertexPtr pNewVertexStart = pNewVertex = OdPrcUniqueVertex::createObject();
    mapOld2New.mapOld2New[pVertex] = pNewVertex;
    OdPrcUniqueVertexPtr pVertexUnique = pVertex;
    copyPrcBaseTopology(pNewVertexStart->baseTopology(), pVertexUnique->baseTopology());
    pNewVertexStart->point() = pVertexUnique->point();
    pNewVertexStart->setHaveTolerance(pVertexUnique->haveTolerance());
    pNewVertexStart->setTolerance(pVertexUnique->tolerance());
  }
  else if (pVertex->isKindOf(OdPrcMultipleVertex::desc()))
  {
    OdPrcMultipleVertexPtr pNewVertexStart = pNewVertex = OdPrcMultipleVertex::createObject();
    mapOld2New.mapOld2New[pVertex] = pNewVertex;
    OdPrcMultipleVertexPtr pVertexMultiple = pVertex;
    copyPrcBaseTopology(pNewVertexStart->baseTopology(), pVertexMultiple->baseTopology());
    pNewVertexStart->points() = pVertexMultiple->points();
  }
  else
  {
    ODA_ASSERT(0);
  }
}

void copyPrcCurve(OdPrcCurvePtr & pNewCurve, const OdPrcCurvePtr & pCurve, OdPrcCloneMap & mapOld2New);
void copyPrcSurface(OdPrcSurfacePtr & pNewSurface, const OdPrcSurfacePtr & pSurface, OdPrcCloneMap & mapOld2New);


#include "PrcMath1d.h"
#include "PrcMath1dArcTanCos.h"
#include "PrcMath1dCombination.h"
#include "PrcMath1dFraction.h"
#include "PrcMath1dPolynom.h"
#include "PrcMath1dTrigonometric.h"

void copyPrcMath1d(OdPrcMath1dPtr & pNewMath1d, const OdPrcMath1dPtr & pMath1d, OdPrcCloneMap & mapOld2New)
{
  if (pMath1d.isNull())
  {
    pNewMath1d = NULL;
    return;
  }
  std::map<OdRxObjectPtr, OdRxObjectPtr>::const_iterator pIt = mapOld2New.mapOld2New.find(pMath1d);
  if (pIt != mapOld2New.mapOld2New.end())
  {
    pNewMath1d = pIt->second;
    return;
  }
  if (pMath1d->isKindOf(OdPrcMath1dArcTanCos::desc()))
  {
    OdPrcMath1dArcTanCosPtr pNewPrcMath1dArcTanCos = pNewMath1d = OdPrcMath1dArcTanCos::createObject();
    mapOld2New.mapOld2New[pMath1d] = pNewMath1d;
    OdPrcMath1dArcTanCosPtr pPrcMath1dArcTanCos = pMath1d;
    pPrcMath1dArcTanCos->setPhase(pPrcMath1dArcTanCos->phase());
    pPrcMath1dArcTanCos->setFrequency(pPrcMath1dArcTanCos->frequency());
    pPrcMath1dArcTanCos->setA(pPrcMath1dArcTanCos->a());
    pPrcMath1dArcTanCos->setAmplitude(pPrcMath1dArcTanCos->amplitude());
  }
  else if (pMath1d->isKindOf(OdPrcMath1dCombination::desc()))
  {
    OdPrcMath1dCombinationPtr pNewPrcMath1dCombination = pNewMath1d = OdPrcMath1dCombination::createObject();
    mapOld2New.mapOld2New[pMath1d] = pNewMath1d;
    OdPrcMath1dCombinationPtr pPrcMath1dCombination = pMath1d;
    pNewPrcMath1dCombination->combinationFunctions().resize(pPrcMath1dCombination->combinationFunctions().size());
    for (OdUInt32 i = 0; i < pPrcMath1dCombination->combinationFunctions().size(); ++i)
    {
      pNewPrcMath1dCombination->combinationFunctions()[i].setCoefficient(pPrcMath1dCombination->combinationFunctions()[i].getCoefficient());
      copyPrcMath1d(pNewPrcMath1dCombination->combinationFunctions()[i].function(), pPrcMath1dCombination->combinationFunctions()[i].function(), mapOld2New);
    }
  }
  else if (pMath1d->isKindOf(OdPrcMath1dFraction::desc()))
  {
    OdPrcMath1dFractionPtr pNewPrcMath1dFraction = pNewMath1d = OdPrcMath1dFraction::createObject();
    mapOld2New.mapOld2New[pMath1d] = pNewMath1d;
    OdPrcMath1dFractionPtr pPrcMath1dFraction = pMath1d;

    OdPrcMath1dPtr pNewNumerator;
    copyPrcMath1d(pNewNumerator, pPrcMath1dFraction->numerator(), mapOld2New);
    pNewPrcMath1dFraction->setNumerator(pNewNumerator);

    OdPrcMath1dPtr pNewDenominator;
    copyPrcMath1d(pNewDenominator, pPrcMath1dFraction->denominator(), mapOld2New);
    pNewPrcMath1dFraction->setNumerator(pNewDenominator);
  }
  else if (pMath1d->isKindOf(OdPrcMath1dPolynom::desc()))
  {
    OdPrcMath1dPolynomPtr pNewPrcMath1dPolynom = pNewMath1d = OdPrcMath1dPolynom::createObject();
    mapOld2New.mapOld2New[pMath1d] = pNewMath1d;
    OdPrcMath1dPolynomPtr pPrcMath1dPolynom = pMath1d;
    pNewPrcMath1dPolynom->coefficient() = pPrcMath1dPolynom->coefficient();
  }
  else if (pMath1d->isKindOf(OdPrcMath1dTrigonometric::desc()))
  {
    OdPrcMath1dTrigonometricPtr pNewPrcMath1dTrigonometric = pNewMath1d = OdPrcMath1dTrigonometric::createObject();
    mapOld2New.mapOld2New[pMath1d] = pNewMath1d;
    OdPrcMath1dTrigonometricPtr pPrcMath1dTrigonometric = pMath1d;
    pNewPrcMath1dTrigonometric->setDcOffset(pPrcMath1dTrigonometric->dcOffset());
    pNewPrcMath1dTrigonometric->setFrequency(pPrcMath1dTrigonometric->frequency());
    pNewPrcMath1dTrigonometric->setPhase(pPrcMath1dTrigonometric->phase());
    pNewPrcMath1dTrigonometric->setAmplitude(pPrcMath1dTrigonometric->amplitude());
  }
  else
  {
    ODA_ASSERT(0);
  }
}

#include "PrcMath3d.h"
#include "PrcMath3dLinear.h"
#include "PrcMath3dNonLinear.h"
void copyPrcMath3d(OdPrcMath3dPtr & pNewMath3d, const OdPrcMath3dPtr & pMath3d, OdPrcCloneMap & mapOld2New)
{
  if (pMath3d.isNull())
  {
    pNewMath3d = NULL;
    return;
  }
  std::map<OdRxObjectPtr, OdRxObjectPtr>::const_iterator pIt = mapOld2New.mapOld2New.find(pMath3d);
  if (pIt != mapOld2New.mapOld2New.end())
  {
    pNewMath3d = pIt->second;
    return;
  }
  if (pMath3d->isKindOf(OdPrcMath3dLinear::desc()))
  {
    OdPrcMath3dLinearPtr pNewPrcMath3dLinear = pNewMath3d = OdPrcMath3dLinear::createObject();
    mapOld2New.mapOld2New[pMath3d] = pNewMath3d;
    OdPrcMath3dLinearPtr pPrcMath3dLinear = pMath3d;
    pNewPrcMath3dLinear->mat() = pPrcMath3dLinear->mat();
  }
  else if (pMath3d->isKindOf(OdPrcMath3dNonLinear::desc()))
  {
    OdPrcMath3dNonLinearPtr pNewPrcMath3dNonLinear = pNewMath3d = OdPrcMath3dNonLinear::createObject();
    mapOld2New.mapOld2New[pMath3d] = pNewMath3d;
    OdPrcMath3dNonLinearPtr pPrcMath3dNonLinear = pMath3d;
    pNewPrcMath3dNonLinear->setD2(pPrcMath3dNonLinear->d2());

    OdPrcMath3dPtr pLeftTransformation;
    copyPrcMath3d(pLeftTransformation, pPrcMath3dNonLinear->leftTransformation(), mapOld2New);
    pNewPrcMath3dNonLinear->setLeftTransformation(pLeftTransformation);

    OdPrcMath3dPtr pRightTransformation;
    copyPrcMath3d(pRightTransformation, pPrcMath3dNonLinear->rightTransformation(), mapOld2New);
    pNewPrcMath3dNonLinear->setRightTransformation(pRightTransformation);
  }
  else
  {
    ODA_ASSERT(0);
  }
}

#include "Prc2dCurveOnSurfaceCurve3d.h"
#include "PrcBlend02Boundary3d.h"
#include "PrcCircle2d.h"
#include "PrcCircle3d.h"
#include "PrcCompositeCurve2d.h"
#include "PrcCompositeCurve3d.h"
#include "PrcEllipse2d.h"
#include "PrcEllipse3d.h"
#include "PrcEquationCurve2d.h"
#include "PrcEquationCurve3d.h"
#include "PrcHelixType0Curve.h"
#include "PrcHelixType1Curve.h"
#include "PrcHyperbola2d.h"
#include "PrcHyperbola3d.h"
#include "PrcIntersectionCurve3d.h"
#include "PrcLine2d.h"
#include "PrcLine3d.h"
#include "PrcNurbsCurve2d.h"
#include "PrcNurbsCurve3d.h"
#include "PrcOffsetCurve3d.h"
#include "PrcParabola2d.h"
#include "PrcParabola3d.h"
#include "PrcPolyLine2d.h"
#include "PrcPolyLine3d.h"
#include "PrcTransformedCurve2d.h"
#include "PrcTransformedCurve3d.h"

void copyPrcCurve(OdPrcCurvePtr & pNewCurve, const OdPrcCurvePtr & pCurve, OdPrcCloneMap & mapOld2New)
{
  if (pCurve.isNull())
  {
    pNewCurve = NULL;
    return;
  }
  std::map<OdRxObjectPtr, OdRxObjectPtr>::const_iterator pIt = mapOld2New.mapOld2New.find(pCurve);
  if (pIt != mapOld2New.mapOld2New.end())
  {
    pNewCurve = pIt->second;
    return;
  }

  if (pCurve->isKindOf(OdPrc2dCurveOnSurfaceCurve3d::desc()))
  {
    OdPrc2dCurveOnSurfaceCurve3dPtr pNewPrc2dCurveOnSurfaceCurve3d = pNewCurve = OdPrc2dCurveOnSurfaceCurve3d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrc2dCurveOnSurfaceCurve3dPtr pPrc2dCurveOnSurfaceCurve3d = pCurve;
    pNewPrc2dCurveOnSurfaceCurve3d->setTolerance(pPrc2dCurveOnSurfaceCurve3d->tolerance());

    OdPrcCurvePtr pNewUvCurve;
    copyPrcCurve(pNewUvCurve, pPrc2dCurveOnSurfaceCurve3d->curveUV(), mapOld2New);
    pNewPrc2dCurveOnSurfaceCurve3d->setCurveUV(pNewUvCurve);

    OdPrcSurfacePtr pNewBaseSurface;
    copyPrcSurface(pNewBaseSurface, pPrc2dCurveOnSurfaceCurve3d->baseSurface(), mapOld2New);
    pNewPrc2dCurveOnSurfaceCurve3d->setBaseSurface(pNewBaseSurface);
  }
  else if (pCurve->isKindOf(OdPrcBlend02Boundary3d::desc()))
  {
    OdPrcBlend02Boundary3dPtr pNewPrcBlend02Boundary3d = pNewCurve = OdPrcBlend02Boundary3d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcBlend02Boundary3dPtr pPrcBlend02Boundary3d = pCurve;

    pNewPrcBlend02Boundary3d->setTransformation(pPrcBlend02Boundary3d->transformation());
    pNewPrcBlend02Boundary3d->endLimitPoint() = pPrcBlend02Boundary3d->endLimitPoint();
    pNewPrcBlend02Boundary3d->startLimitPoint() = pPrcBlend02Boundary3d->startLimitPoint();

    pNewPrcBlend02Boundary3d->crossingPointPositions() = pPrcBlend02Boundary3d->crossingPointPositions();
    pNewPrcBlend02Boundary3d->setBaseScale(pPrcBlend02Boundary3d->baseScale());
    pNewPrcBlend02Boundary3d->setBaseParameter(pPrcBlend02Boundary3d->baseParameter());
    pNewPrcBlend02Boundary3d->setAngularError(pPrcBlend02Boundary3d->angularError());
    pNewPrcBlend02Boundary3d->setChordalError(pPrcBlend02Boundary3d->chordalError());
    pNewPrcBlend02Boundary3d->setIntersectionCurveSens(pPrcBlend02Boundary3d->intersectionCurveSens());
    pNewPrcBlend02Boundary3d->setIntersectionOrder(pPrcBlend02Boundary3d->intersectionOrder());
    pNewPrcBlend02Boundary3d->setBoundingSurfaceSens(pPrcBlend02Boundary3d->boundingSurfaceSens());

    OdPrcSurfacePtr pNewBlendSurface;
    copyPrcSurface(pNewBlendSurface, pPrcBlend02Boundary3d->blend(), mapOld2New);
    pNewPrcBlend02Boundary3d->setBlend(pNewBlendSurface);

    pNewPrcBlend02Boundary3d->setBound(pPrcBlend02Boundary3d->bound());

    OdPrcSurfacePtr pNewBoundingSurface;
    copyPrcSurface(pNewBoundingSurface, pPrcBlend02Boundary3d->boundingSurface(), mapOld2New);
    pNewPrcBlend02Boundary3d->setBoundingSurface(pNewBoundingSurface);

    pNewPrcBlend02Boundary3d->setStartLimitType(pNewPrcBlend02Boundary3d->startLimitType());
    pNewPrcBlend02Boundary3d->setEndLimitType(pNewPrcBlend02Boundary3d->endLimitType());
  }
  else if (pCurve->isKindOf(OdPrcCircle2d::desc()))
  {
    OdPrcCircle2dPtr pNewPrcCircle2d = pNewCurve = OdPrcCircle2d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcCircle2dPtr pPrcCircle2d = pCurve;

    pNewPrcCircle2d->setTransformation(pPrcCircle2d->transformation());
    pNewPrcCircle2d->setRadius(pPrcCircle2d->radius());
  }
  else if (pCurve->isKindOf(OdPrcCircle3d::desc()))
  {
    OdPrcCircle3dPtr pNewPrcCircle3d = pNewCurve = OdPrcCircle3d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcCircle3dPtr pPrcCircle3d = pCurve;
    pNewPrcCircle3d->setTransformation(pPrcCircle3d->transformation());
    pNewPrcCircle3d->setRadius(pPrcCircle3d->radius());
  }
  else if (pCurve->isKindOf(OdPrcCompositeCurve2d::desc()))
  {
    OdPrcCompositeCurve2dPtr pNewPrcCompositeCurve2d = pNewCurve = OdPrcCompositeCurve2d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcCompositeCurve2dPtr pPrcCompositeCurve2d = pCurve;
    pNewPrcCompositeCurve2d->setTransformation(pPrcCompositeCurve2d->transformation());
    pNewPrcCompositeCurve2d->setIsClosed(pPrcCompositeCurve2d->isClosed());

    OdPrcCurvePtrArray arrNewBaseCurve;
    arrNewBaseCurve.resize(pPrcCompositeCurve2d->baseCurve().size());
    for (OdUInt32 i = 0; i < pPrcCompositeCurve2d->baseCurve().size(); ++i)
    {
      copyPrcCurve(arrNewBaseCurve[i], pPrcCompositeCurve2d->baseCurve()[i], mapOld2New);
    }
    pNewPrcCompositeCurve2d->baseCurve() = arrNewBaseCurve;
    pNewPrcCompositeCurve2d->baseSense() = pPrcCompositeCurve2d->baseSense();
  }
  else if (pCurve->isKindOf(OdPrcCompositeCurve3d::desc()))
  {
    OdPrcCompositeCurve3dPtr pNewPrcCompositeCurve3d = pNewCurve = OdPrcCompositeCurve3d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcCompositeCurve3dPtr pPrcCompositeCurve3d = pCurve;

    pNewPrcCompositeCurve3d->setTransformation(pPrcCompositeCurve3d->transformation());
    pNewPrcCompositeCurve3d->setIsClosed(pPrcCompositeCurve3d->isClosed());

    OdPrcCurvePtrArray arrNewBaseCurve;
    arrNewBaseCurve.resize(pPrcCompositeCurve3d->baseCurve().size());
    for (OdUInt32 i = 0; i < pPrcCompositeCurve3d->baseCurve().size(); ++i)
    {
      copyPrcCurve(arrNewBaseCurve[i], pPrcCompositeCurve3d->baseCurve()[i], mapOld2New);
    }
    pNewPrcCompositeCurve3d->baseCurve() = arrNewBaseCurve;
    pNewPrcCompositeCurve3d->baseSense() = pPrcCompositeCurve3d->baseSense();
  }
  else if (pCurve->isKindOf(OdPrcEllipse2d::desc()))
  {
    OdPrcEllipse2dPtr pNewPrcEllipse2d = pNewCurve = OdPrcEllipse2d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcEllipse2dPtr pPrcEllipse2d = pCurve;
    pNewPrcEllipse2d->setTransformation(pPrcEllipse2d->transformation());
    pNewPrcEllipse2d->setRadiusAtXAxis(pPrcEllipse2d->radiusAtXAxis());
    pNewPrcEllipse2d->setRadiusAtYAxis(pPrcEllipse2d->radiusAtYAxis());
  }
  else if (pCurve->isKindOf(OdPrcEllipse3d::desc()))
  {
    OdPrcEllipse3dPtr pNewPrcEllipse3d = pNewCurve = OdPrcEllipse3d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcEllipse3dPtr pPrcEllipse3d = pCurve;
    pNewPrcEllipse3d->setTransformation(pPrcEllipse3d->transformation());
    pNewPrcEllipse3d->setRadiusAtXAxis(pPrcEllipse3d->radiusAtXAxis());
    pNewPrcEllipse3d->setRadiusAtYAxis(pPrcEllipse3d->radiusAtYAxis());
  }
  else if (pCurve->isKindOf(OdPrcEquationCurve2d::desc()))
  {
    OdPrcEquationCurve2dPtr pNewPrcEquationCurve2d = pNewCurve = OdPrcEquationCurve2d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcEquationCurve2dPtr pPrcEquationCurve2d = pCurve;
    pNewPrcEquationCurve2d->setTransformation(pPrcEquationCurve2d->transformation());

    OdPrcMath1dPtr pNewFunctionX;
    copyPrcMath1d(pNewFunctionX, pPrcEquationCurve2d->functionX(), mapOld2New);
    pNewPrcEquationCurve2d->setFunctionX(pNewFunctionX);

    OdPrcMath1dPtr pNewFunctionY;
    copyPrcMath1d(pNewFunctionY, pPrcEquationCurve2d->functionY(), mapOld2New);
    pNewPrcEquationCurve2d->setFunctionY(pNewFunctionY);
  }
  else if (pCurve->isKindOf(OdPrcEquationCurve3d::desc()))
  {
    OdPrcEquationCurve3dPtr pNewPrcEquationCurve3d = pNewCurve = OdPrcEquationCurve3d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcEquationCurve3dPtr pPrcEquationCurve3d = pCurve;
    pNewPrcEquationCurve3d->setTransformation(pPrcEquationCurve3d->transformation());

    OdPrcMath1dPtr pNewFunctionX;
    copyPrcMath1d(pNewFunctionX, pPrcEquationCurve3d->functionX(), mapOld2New);
    pNewPrcEquationCurve3d->setFunctionX(pNewFunctionX);

    OdPrcMath1dPtr pNewFunctionY;
    copyPrcMath1d(pNewFunctionY, pPrcEquationCurve3d->functionY(), mapOld2New);
    pNewPrcEquationCurve3d->setFunctionY(pNewFunctionY);

    OdPrcMath1dPtr pNewFunctionZ;
    copyPrcMath1d(pNewFunctionZ, pPrcEquationCurve3d->functionZ(), mapOld2New);
    pNewPrcEquationCurve3d->setFunctionZ(pNewFunctionZ);
  }
  else if (pCurve->isKindOf(OdPrcHelixType0Curve::desc()))
  {
    OdPrcHelixType0CurvePtr pNewPrcHelixType0Curve = pNewCurve = OdPrcHelixType0Curve::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcHelixType0CurvePtr pPrcHelixType0Curve = pCurve;
    pNewPrcHelixType0Curve->setTransformation(pPrcHelixType0Curve->transformation());
    pNewPrcHelixType0Curve->direction() = pPrcHelixType0Curve->direction();
    pNewPrcHelixType0Curve->origin() = pPrcHelixType0Curve->origin();
    pNewPrcHelixType0Curve->start() = pPrcHelixType0Curve->start();
    pNewPrcHelixType0Curve->setRadiusEvolution(pPrcHelixType0Curve->radiusEvolution());
    pNewPrcHelixType0Curve->setPitch(pPrcHelixType0Curve->pitch());
    pNewPrcHelixType0Curve->setTrigonometricOrientation(pPrcHelixType0Curve->trigonometricOrientation());
  }
  else if (pCurve->isKindOf(OdPrcHelixType1Curve::desc()))
  {
    OdPrcHelixType1CurvePtr pNewPrcHelixType1Curve = pNewCurve = OdPrcHelixType1Curve::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcHelixType1CurvePtr pPrcHelixType1Curve = pCurve;

    pNewPrcHelixType1Curve->setTransformation(pPrcHelixType1Curve->transformation());
    pNewPrcHelixType1Curve->start() = pPrcHelixType1Curve->start();
    pNewPrcHelixType1Curve->setTrigonometricOrientation(pPrcHelixType1Curve->trigonometricOrientation());
    pNewPrcHelixType1Curve->setUnitZ(pPrcHelixType1Curve->unitZ());
    pNewPrcHelixType1Curve->setUnitU(pPrcHelixType1Curve->unitU());

    OdPrcMath1dPtr pNewRadiusLaw;
    copyPrcMath1d(pNewRadiusLaw, pPrcHelixType1Curve->radiusLaw(), mapOld2New);
    pNewPrcHelixType1Curve->setRadiusLaw(pNewRadiusLaw);

    OdPrcMath1dPtr pNewZLaw;
    copyPrcMath1d(pNewZLaw, pPrcHelixType1Curve->zLaw(), mapOld2New);
    pNewPrcHelixType1Curve->setZLaw(pNewZLaw);

    OdPrcMath1dPtr pNewThetaLaw;
    copyPrcMath1d(pNewThetaLaw, pPrcHelixType1Curve->thetaLaw(), mapOld2New);
    pNewPrcHelixType1Curve->setThetaLaw(pNewThetaLaw);
  }
  else if (pCurve->isKindOf(OdPrcHyperbola2d::desc()))
  {
    OdPrcHyperbola2dPtr pNewPrcHyperbola2d = pNewCurve = OdPrcHyperbola2d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcHyperbola2dPtr pPrcHyperbola2d = pCurve;
    pNewPrcHyperbola2d->setTransformation(pPrcHyperbola2d->transformation());
    pNewPrcHyperbola2d->setSemiImageAxis(pPrcHyperbola2d->semiImageAxis());
    pNewPrcHyperbola2d->setSemiAxis(pPrcHyperbola2d->semiAxis());
    pNewPrcHyperbola2d->setParameterizationType(pPrcHyperbola2d->parameterizationType());
  }
  else if (pCurve->isKindOf(OdPrcHyperbola3d::desc()))
  {
    OdPrcHyperbola3dPtr pNewPrcHyperbola3d = pNewCurve = OdPrcHyperbola3d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcHyperbola3dPtr pPrcHyperbola3d = pCurve;
    pNewPrcHyperbola3d->setTransformation(pPrcHyperbola3d->transformation());
    pNewPrcHyperbola3d->setSemiImageAxis(pPrcHyperbola3d->semiImageAxis());
    pNewPrcHyperbola3d->setSemiAxis(pPrcHyperbola3d->semiAxis());
    pNewPrcHyperbola3d->setParameterizationType(pPrcHyperbola3d->parameterizationType());
  }
  else if (pCurve->isKindOf(OdPrcIntersectionCurve3d::desc()))
  {
    OdPrcIntersectionCurve3dPtr pNewPrcIntersectionCurve3d = pNewCurve = OdPrcIntersectionCurve3d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcIntersectionCurve3dPtr pPrcIntersectionCurve3d = pCurve;
    pNewPrcIntersectionCurve3d->setTransformation(pPrcIntersectionCurve3d->transformation());
    pNewPrcIntersectionCurve3d->endLimitPoint() = pPrcIntersectionCurve3d->endLimitPoint();
    pNewPrcIntersectionCurve3d->startLimitPoint() = pPrcIntersectionCurve3d->startLimitPoint();
    pNewPrcIntersectionCurve3d->crossingPointsCrvIntersection() = pPrcIntersectionCurve3d->crossingPointsCrvIntersection();
    pNewPrcIntersectionCurve3d->setAngularError(pPrcIntersectionCurve3d->angularError());
    pNewPrcIntersectionCurve3d->setChordalError(pPrcIntersectionCurve3d->chordalError());
    pNewPrcIntersectionCurve3d->setParameterizationDefinitionRespected(pPrcIntersectionCurve3d->parameterizationDefinitionRespected());
    pNewPrcIntersectionCurve3d->setIntersectionSense(pPrcIntersectionCurve3d->intersectionSense());

    pNewPrcIntersectionCurve3d->setSurface1Sense(pPrcIntersectionCurve3d->surface1Sense());
    pNewPrcIntersectionCurve3d->setSurface2Sense(pPrcIntersectionCurve3d->surface2Sense());

    OdPrcSurfacePtr pNewSurface1;
    copyPrcSurface(pNewSurface1, pPrcIntersectionCurve3d->surface1(), mapOld2New);
    pNewPrcIntersectionCurve3d->setSurface1(pNewSurface1);

    OdPrcSurfacePtr pNewSurface2;
    copyPrcSurface(pNewSurface2, pPrcIntersectionCurve3d->surface2(), mapOld2New);
    pNewPrcIntersectionCurve3d->setSurface2(pNewSurface2);

    pNewPrcIntersectionCurve3d->setStartLimitType(pPrcIntersectionCurve3d->startLimitType());
    pNewPrcIntersectionCurve3d->setEndLimitType(pPrcIntersectionCurve3d->endLimitType());
  }
  else if (pCurve->isKindOf(OdPrcLine2d::desc()))
  {
    OdPrcLine2dPtr pNewPrcLine2d = pNewCurve = OdPrcLine2d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcLine2dPtr pPrcLine2d = pCurve;
    pNewPrcLine2d->setTransformation(pPrcLine2d->transformation());
  }
  else if (pCurve->isKindOf(OdPrcLine3d::desc()))
  {
    OdPrcLine3dPtr pNewPrcLine3d = pNewCurve = OdPrcLine3d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcLine3dPtr pPrcLine3d = pCurve;
    pNewPrcLine3d->setTransformation(pPrcLine3d->transformation());
  }
  else if (pCurve->isKindOf(OdPrcNurbsCurve2d::desc()))
  {
    OdPrcNurbsCurve2dPtr pNewPrcNurbsCurve2d = pNewCurve = OdPrcNurbsCurve2d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcNurbsCurve2dPtr pPrcNurbsCurve2d = pCurve;
    OdGeCurve2d *pCurve2d = NULL;
    pPrcNurbsCurve2d->getOdGeCurve(pCurve2d);
    pNewPrcNurbsCurve2d->setFromOdGeCurve(*pCurve2d);
    delete pCurve2d;
  }
  else if (pCurve->isKindOf(OdPrcNurbsCurve3d::desc()))
  {
    OdPrcNurbsCurve3dPtr pNewPrcNurbsCurve3d = pNewCurve = OdPrcNurbsCurve3d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcNurbsCurve3dPtr pPrcNurbsCurve3d = pCurve;
    OdGeCurve3d *pCurve3d = NULL;
    pPrcNurbsCurve3d->getOdGeCurve(pCurve3d);
    pNewPrcNurbsCurve3d->setFromOdGeCurve(*pCurve3d);
    delete pCurve3d;
  }
  else if (pCurve->isKindOf(OdPrcOffsetCurve3d::desc()))
  {
    OdPrcOffsetCurve3dPtr pNewPrcOffsetCurve3d = pNewCurve = OdPrcOffsetCurve3d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcOffsetCurve3dPtr pPrcOffsetCurve3d = pCurve;
    pNewPrcOffsetCurve3d->setOffsetDistance(pPrcOffsetCurve3d->offsetDistance());
    OdPrcCurvePtr pNewCurve;
    copyPrcCurve(pNewCurve, pPrcOffsetCurve3d->baseCurve(), mapOld2New);
    pNewPrcOffsetCurve3d->setBaseCurve(pNewCurve);
    pNewPrcOffsetCurve3d->setOffsetPlaneNormal(pPrcOffsetCurve3d->offsetPlaneNormal());
  }
  else if (pCurve->isKindOf(OdPrcParabola2d::desc()))
  {
    OdPrcParabola2dPtr pNewPrcParabola2d = pNewCurve = OdPrcParabola2d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcParabola2dPtr pPrcParabola2d = pCurve;
    pNewPrcParabola2d->setTransformation(pPrcParabola2d->transformation());
    pNewPrcParabola2d->setParameterizationType(pPrcParabola2d->parameterizationType());
    pNewPrcParabola2d->setFocalLength(pPrcParabola2d->focalLength());
  }
  else if (pCurve->isKindOf(OdPrcParabola3d::desc()))
  {
    OdPrcParabola3dPtr pNewPrcParabola3d = pNewCurve = OdPrcParabola3d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcParabola3dPtr pPrcParabola3d = pCurve;
    pNewPrcParabola3d->setTransformation(pPrcParabola3d->transformation());
    pNewPrcParabola3d->setParameterizationType(pPrcParabola3d->parameterizationType());
    pNewPrcParabola3d->setFocalLength(pPrcParabola3d->focalLength());
  }
  else if (pCurve->isKindOf(OdPrcPolyLine2d::desc()))
  {
    OdPrcPolyLine2dPtr pNewPrcPolyLine2d = pNewCurve = OdPrcPolyLine2d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcPolyLine2dPtr pPrcPolyLine2d = pCurve;
    pNewPrcPolyLine2d->setTransformation(pPrcPolyLine2d->transformation());
    pNewPrcPolyLine2d->setPoints(pPrcPolyLine2d->points());
  }
  else if (pCurve->isKindOf(OdPrcPolyLine3d::desc()))
  {
    OdPrcPolyLine3dPtr pNewPrcPolyLine3d = pNewCurve = OdPrcPolyLine3d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcPolyLine3dPtr pPrcPolyLine3d = pCurve;
    pNewPrcPolyLine3d->setTransformation(pPrcPolyLine3d->transformation());
    pNewPrcPolyLine3d->setPoints(pPrcPolyLine3d->points());
  }
  else if (pCurve->isKindOf(OdPrcTransformedCurve2d::desc()))
  {
    OdPrcTransformedCurve2dPtr pNewPrcTransformedCurve2d = pNewCurve = OdPrcTransformedCurve2d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcTransformedCurve2dPtr pPrcTransformedCurve2d = pCurve;
    pNewPrcTransformedCurve2d->setTransformation(pPrcTransformedCurve2d->transformation());
    OdPrcCurvePtr pNewBaseCurve;
    copyPrcCurve(pNewBaseCurve, pPrcTransformedCurve2d->baseCurve(), mapOld2New);
    pNewPrcTransformedCurve2d->setBaseCurve(pNewBaseCurve);
    copyPrcMath3d(pNewPrcTransformedCurve2d->mathTransformation(), pPrcTransformedCurve2d->mathTransformation(), mapOld2New);
  }
  else if (pCurve->isKindOf(OdPrcTransformedCurve3d::desc()))
  {
    OdPrcTransformedCurve3dPtr pNewPrcTransformedCurve3d = pNewCurve = OdPrcTransformedCurve3d::createObject();
    mapOld2New.mapOld2New[pCurve] = pNewCurve;
    OdPrcTransformedCurve3dPtr pPrcTransformedCurve3d = pCurve;
    pNewPrcTransformedCurve3d->setTransformation(pPrcTransformedCurve3d->transformation());
    OdPrcCurvePtr pNewBaseCurve;
    copyPrcCurve(pNewBaseCurve, pPrcTransformedCurve3d->baseCurve(), mapOld2New);
    pNewPrcTransformedCurve3d->setBaseCurve(pNewBaseCurve);
    copyPrcMath3d(pNewPrcTransformedCurve3d->mathTransformation(), pPrcTransformedCurve3d->mathTransformation(), mapOld2New);
  }
  else
  {
    ODA_ASSERT(0);
  }
  pNewCurve->setParameterization(pCurve->parameterization());
  copyPrcContentCurve(pNewCurve->contentCurve(), pCurve->contentCurve());
}

#include "PrcBlend01Surface.h"
#include "PrcBlend02Surface.h"
#include "PrcBlend03Surface.h"
#include "PrcCone.h"
#include "PrcCylinder.h"
#include "PrcCylindricalSurface.h"
#include "PrcExtrusionSurface.h"
#include "PrcFromCurvesSurface.h"
#include "PrcNurbsSurface.h"
#include "PrcOffsetSurface.h"
#include "PrcPlane.h"
#include "PrcRevolutionSurface.h"
#include "PrcRuledSurface.h"
#include "PrcSphere.h"
#include "PrcTorus.h"
#include "PrcTransformedSurface.h"

//not in public:
//#include "PrcBlend04.h" 
//#include "PrcPipe.h"

void copyPrcSurface(OdPrcSurfacePtr & pNewSurface, const OdPrcSurfacePtr & pSurface, OdPrcCloneMap & mapOld2New)
{
  if (pSurface.isNull())
  {
    pNewSurface = NULL;
    return;
  }
  std::map<OdRxObjectPtr, OdRxObjectPtr>::const_iterator pIt = mapOld2New.mapOld2New.find(pSurface);
  if (pIt != mapOld2New.mapOld2New.end())
  {
    pNewSurface = pIt->second;
    return;
  }

  if (pSurface->isKindOf(OdPrcBlend01Surface::desc()))
  {
    OdPrcBlend01SurfacePtr pNewPrcBlend01Surface = pNewSurface = OdPrcBlend01Surface::createObject();
    mapOld2New.mapOld2New[pSurface] = pNewSurface;
    OdPrcBlend01SurfacePtr pPrcBlend01Surface = pSurface;
    pNewPrcBlend01Surface->setTransformation(pPrcBlend01Surface->transformation());

    OdPrcCurvePtr pNewCenterCurve;
    copyPrcCurve(pNewCenterCurve, pPrcBlend01Surface->centerCurve(), mapOld2New);
    pNewPrcBlend01Surface->setCenterCurve(pNewCenterCurve);

    OdPrcCurvePtr pNewOriginCurve;
    copyPrcCurve(pNewOriginCurve, pPrcBlend01Surface->originCurve(), mapOld2New);
    pNewPrcBlend01Surface->setOriginCurve(pNewOriginCurve);

    OdPrcCurvePtr pNewTangentCurve;
    copyPrcCurve(pNewTangentCurve, pPrcBlend01Surface->tangentCurve(), mapOld2New);
    pNewPrcBlend01Surface->setTangentCurve(pNewTangentCurve);
  }
  else if (pSurface->isKindOf(OdPrcBlend02Surface::desc()))
  {
    OdPrcBlend02SurfacePtr pNewPrcBlend02Surface = pNewSurface = OdPrcBlend02Surface::createObject();
    mapOld2New.mapOld2New[pSurface] = pNewSurface;
    OdPrcBlend02SurfacePtr pPrcBlend02Surface = pSurface;
    pNewPrcBlend02Surface->setTransformation(pPrcBlend02Surface->transformation());

    copyPrcSurface(pNewPrcBlend02Surface->cliffSupportingSurface0(), pPrcBlend02Surface->cliffSupportingSurface0(), mapOld2New);
    copyPrcSurface(pNewPrcBlend02Surface->cliffSupportingSurface1(), pPrcBlend02Surface->cliffSupportingSurface1(), mapOld2New);

    copyPrcCurve(pNewPrcBlend02Surface->boundCurve0(), pPrcBlend02Surface->boundCurve0(), mapOld2New);
    copyPrcCurve(pNewPrcBlend02Surface->boundCurve1(), pPrcBlend02Surface->boundCurve1(), mapOld2New);
    copyPrcSurface(pNewPrcBlend02Surface->boundSurface0(), pPrcBlend02Surface->boundSurface0(), mapOld2New);
    copyPrcSurface(pNewPrcBlend02Surface->boundSurface1(), pPrcBlend02Surface->boundSurface1(), mapOld2New);

    pNewPrcBlend02Surface->setRadius0(pPrcBlend02Surface->radius0());
    pNewPrcBlend02Surface->setRadius1(pPrcBlend02Surface->radius1());

    pNewPrcBlend02Surface->setBoundSurfaceSens0(pPrcBlend02Surface->boundSurfaceSens0());
    pNewPrcBlend02Surface->setBoundSurfaceSens1(pPrcBlend02Surface->boundSurfaceSens1());
    pNewPrcBlend02Surface->setCenterCurveSens(pPrcBlend02Surface->centerCurveSens());

    OdPrcCurvePtr pNewCenterCurve;
    copyPrcCurve(pNewCenterCurve, pPrcBlend02Surface->centerCurve(), mapOld2New);
    pNewPrcBlend02Surface->setCenterCurve(pNewCenterCurve);

    pNewPrcBlend02Surface->setParameterizationType(pPrcBlend02Surface->parameterizationType());
  }
  else if (pSurface->isKindOf(OdPrcBlend03Surface::desc()))
  {
    OdPrcBlend03SurfacePtr pNewPrcBlend03Surface = pNewSurface = OdPrcBlend03Surface::createObject();
    mapOld2New.mapOld2New[pSurface] = pNewSurface;
    OdPrcBlend03SurfacePtr pPrcBlend03Surface = pSurface;
    pNewPrcBlend03Surface->setTransformation(pPrcBlend03Surface->transformation());
    pNewPrcBlend03Surface->secondDerivatives() = pPrcBlend03Surface->secondDerivatives();
    pNewPrcBlend03Surface->tangent() = pPrcBlend03Surface->tangent();
    pNewPrcBlend03Surface->position() = pPrcBlend03Surface->position();
    pNewPrcBlend03Surface->multiplicities() = pPrcBlend03Surface->multiplicities();
    pNewPrcBlend03Surface->rail2SecondDerivatives() = pPrcBlend03Surface->rail2SecondDerivatives();
    pNewPrcBlend03Surface->rail2DerivativesV() = pPrcBlend03Surface->rail2DerivativesV();
    pNewPrcBlend03Surface->rail2AnglesV() = pPrcBlend03Surface->rail2AnglesV();
    pNewPrcBlend03Surface->parameters() = pPrcBlend03Surface->parameters();
    pNewPrcBlend03Surface->setTrimVMax(pPrcBlend03Surface->trimVMax());
    pNewPrcBlend03Surface->setTrimVMin(pPrcBlend03Surface->trimVMin());
    pNewPrcBlend03Surface->setRail2ParameterV(pPrcBlend03Surface->rail2ParameterV());

    //OdUInt32               m_reserved_int; TODO!
    //OdUInt32               m_reserved_int4;
  }
  else if (pSurface->isKindOf(OdPrcCone::desc()))
  {
    OdPrcConePtr pNewPrcCone = pNewSurface = OdPrcCone::createObject();
    mapOld2New.mapOld2New[pSurface] = pNewSurface;
    OdPrcConePtr pPrcCone = pSurface;

    pNewPrcCone->setTransformation(pPrcCone->transformation());
    pNewPrcCone->setSemiAngle(pPrcCone->semiAngle());
    pNewPrcCone->setBottomRadius(pPrcCone->bottomRadius());
  }
  else if (pSurface->isKindOf(OdPrcCylinder::desc()))
  {
    OdPrcCylinderPtr pNewPrcCylinder = pNewSurface = OdPrcCylinder::createObject();
    mapOld2New.mapOld2New[pSurface] = pNewSurface;
    OdPrcCylinderPtr pPrcCylinder = pSurface;
    pNewPrcCylinder->setTransformation(pPrcCylinder->transformation());
    pNewPrcCylinder->setRadius(pPrcCylinder->radius());
  }
  else if (pSurface->isKindOf(OdPrcCylindricalSurface::desc()))
  {
    OdPrcCylindricalSurfacePtr pNewPrcCylindricalSurface = pNewSurface = OdPrcCylindricalSurface::createObject();
    mapOld2New.mapOld2New[pSurface] = pNewSurface;
    OdPrcCylindricalSurfacePtr pPrcCylindricalSurface = pSurface;
    pNewPrcCylindricalSurface->setTransformation(pPrcCylindricalSurface->transformation());
    pNewPrcCylindricalSurface->setTolerance(pPrcCylindricalSurface->tolerance());

    OdPrcSurfacePtr pNewBaseSurface;
    copyPrcSurface(pNewBaseSurface, pPrcCylindricalSurface->baseSurface(), mapOld2New);
    pNewPrcCylindricalSurface->setBaseSurface(pNewBaseSurface);

    //OdGeExtents3d         m_baseSurfExt_cache; TODO!
  }
  else if (pSurface->isKindOf(OdPrcExtrusionSurface::desc()))
  {
    OdPrcExtrusionSurfacePtr pNewPrcExtrusionSurface = pNewSurface = OdPrcExtrusionSurface::createObject();
    mapOld2New.mapOld2New[pSurface] = pNewSurface;
    OdPrcExtrusionSurfacePtr pPrcExtrusionSurface = pSurface;
    pNewPrcExtrusionSurface->setTransformation(pPrcExtrusionSurface->transformation());
    pNewPrcExtrusionSurface->sweepVector() = pPrcExtrusionSurface->sweepVector();

    OdPrcCurvePtr pNewBaseCurve;
    copyPrcCurve(pNewBaseCurve, pPrcExtrusionSurface->baseCurve(), mapOld2New);
    pNewPrcExtrusionSurface->setBaseCurve(pNewBaseCurve);
  }
  else if (pSurface->isKindOf(OdPrcFromCurvesSurface::desc()))
  {
    OdPrcFromCurvesSurfacePtr pNewPrcFromCurvesSurface = pNewSurface = OdPrcFromCurvesSurface::createObject();
    mapOld2New.mapOld2New[pSurface] = pNewSurface;
    OdPrcFromCurvesSurfacePtr pPrcFromCurvesSurface = pSurface;
    pNewPrcFromCurvesSurface->setTransformation(pPrcFromCurvesSurface->transformation());
    pNewPrcFromCurvesSurface->origin() = pPrcFromCurvesSurface->origin();
    copyPrcCurve(pNewPrcFromCurvesSurface->firstCurve(), pPrcFromCurvesSurface->firstCurve(), mapOld2New);
    copyPrcCurve(pNewPrcFromCurvesSurface->secondCurve(), pPrcFromCurvesSurface->secondCurve(), mapOld2New);
  }
  else if (pSurface->isKindOf(OdPrcNurbsSurface::desc()))
  {
    OdPrcNurbsSurfacePtr pNewPrcNurbsSurface = pNewSurface = OdPrcNurbsSurface::createObject();
    mapOld2New.mapOld2New[pSurface] = pNewSurface;
    OdPrcNurbsSurfacePtr pPrcNurbsSurface = pSurface;
    pNewPrcNurbsSurface->setKnotType(pPrcNurbsSurface->knotType());
    pNewPrcNurbsSurface->setSurfaceForm(pPrcNurbsSurface->surfaceForm());

    OdGeSurface *pSurface = NULL;
    pPrcNurbsSurface->getOdGeSurface(pSurface);
    pNewPrcNurbsSurface->setFromOdGeSurface(*pSurface);
    delete pSurface;
    //OdGeNurbSurface     m_nurbSurface;
    //bool                m_bNurbInitialized; //TODO!
  }
  else if (pSurface->isKindOf(OdPrcOffsetSurface::desc()))
  {
    OdPrcOffsetSurfacePtr pNewPrcOffsetSurface = pNewSurface = OdPrcOffsetSurface::createObject();
    mapOld2New.mapOld2New[pSurface] = pNewSurface;
    OdPrcOffsetSurfacePtr pPrcOffsetSurface = pSurface;
    pNewPrcOffsetSurface->setTransformation(pPrcOffsetSurface->transformation());
    pNewPrcOffsetSurface->setOffsetDistance(pPrcOffsetSurface->offsetDistance());

    OdPrcSurfacePtr pNewBaseSurface;
    copyPrcSurface(pNewBaseSurface, pPrcOffsetSurface->baseSurface(), mapOld2New);
    pNewPrcOffsetSurface->setBaseSurface(pNewBaseSurface);
  }
  else if (pSurface->isKindOf(OdPrcPlane::desc()))
  {
    OdPrcPlanePtr pNewPrcPlane = pNewSurface = OdPrcPlane::createObject();
    mapOld2New.mapOld2New[pSurface] = pNewSurface;
    OdPrcPlanePtr pPrcPlane = pSurface;
    pNewPrcPlane->setTransformation(pPrcPlane->transformation());
  }
  else if (pSurface->isKindOf(OdPrcRevolutionSurface::desc()))
  {
    OdPrcRevolutionSurfacePtr pNewPrcRevolutionSurface = pNewSurface = OdPrcRevolutionSurface::createObject();
    mapOld2New.mapOld2New[pSurface] = pNewSurface;
    OdPrcRevolutionSurfacePtr pPrcRevolutionSurface = pSurface;

    pNewPrcRevolutionSurface->setTransformation(pPrcRevolutionSurface->transformation());
    pNewPrcRevolutionSurface->x() = pPrcRevolutionSurface->x();
    pNewPrcRevolutionSurface->y() = pPrcRevolutionSurface->y();
    pNewPrcRevolutionSurface->origin() = pPrcRevolutionSurface->origin();
    pNewPrcRevolutionSurface->setTolerance(pPrcRevolutionSurface->tolerance());

    OdPrcCurvePtr pNewBaseCurve;
    copyPrcCurve(pNewBaseCurve, pPrcRevolutionSurface->baseCurve(), mapOld2New);
    pNewPrcRevolutionSurface->setBaseCurve(pNewBaseCurve);
  }
  else if (pSurface->isKindOf(OdPrcRuledSurface::desc()))
  {
    OdPrcRuledSurfacePtr pNewPrcRuledSurface = pNewSurface = OdPrcRuledSurface::createObject();
    mapOld2New.mapOld2New[pSurface] = pNewSurface;
    OdPrcRuledSurfacePtr pPrcRuledSurface = pSurface;
    pNewPrcRuledSurface->setTransformation(pPrcRuledSurface->transformation());
    copyPrcCurve(pNewPrcRuledSurface->firstCurve(), pPrcRuledSurface->firstCurve(), mapOld2New);
    copyPrcCurve(pNewPrcRuledSurface->secondCurve(), pPrcRuledSurface->secondCurve(), mapOld2New);
  }
  else if (pSurface->isKindOf(OdPrcSphere::desc()))
  {
    OdPrcSpherePtr pNewPrcSphere = pNewSurface = OdPrcSphere::createObject();
    mapOld2New.mapOld2New[pSurface] = pNewSurface;
    OdPrcSpherePtr pPrcSphere = pSurface;
    pNewPrcSphere->setTransformation(pPrcSphere->transformation());
    pNewPrcSphere->setRadius(pPrcSphere->radius());
  }
  else if (pSurface->isKindOf(OdPrcTorus::desc()))
  {
    OdPrcTorusPtr pNewPrcTorus = pNewSurface = OdPrcTorus::createObject();
    mapOld2New.mapOld2New[pSurface] = pNewSurface;
    OdPrcTorusPtr pPrcTorus = pSurface;
    pNewPrcTorus->setTransformation(pPrcTorus->transformation());
    pNewPrcTorus->setMinorRadius(pPrcTorus->minorRadius());
    pNewPrcTorus->setMajorRadius(pPrcTorus->majorRadius());
  }
  else if (pSurface->isKindOf(OdPrcTransformedSurface::desc()))
  {
    OdPrcTransformedSurfacePtr pNewPrcTransformedSurface = pNewSurface = OdPrcTransformedSurface::createObject();
    mapOld2New.mapOld2New[pSurface] = pNewSurface;
    OdPrcTransformedSurfacePtr pPrcTransformedSurface = pSurface;
    pNewPrcTransformedSurface->setTransformation(pPrcTransformedSurface->transformation());
    copyPrcMath3d(pNewPrcTransformedSurface->mathTransformation(), pPrcTransformedSurface->mathTransformation(), mapOld2New);

    OdPrcSurfacePtr pNewBaseSurface;
    copyPrcSurface(pNewBaseSurface, pPrcTransformedSurface->baseSurface(), mapOld2New);
    pNewPrcTransformedSurface->setBaseSurface(pNewBaseSurface);
  }
  /*else if (pSurface->isKindOf(OdPrcBlend04::desc()))
  {
    OdPrcBlend04Ptr pNewPrcBlend04 = pNewSurface = OdPrcBlend04::createObject();
    mapOld2New.mapOld2New[pSurface] = pNewSurface;
    OdPrcBlend04Ptr pPrcBlend04 = pSurface;
    // This type is currently not supported and is reserved for future use.
    ODA_ASSERT(0);
  }
  else if (pSurface->isKindOf(OdPrcPipe::desc()))
  {
    OdPrcPipePtr pNewPrcPipe = pNewSurface = OdPrcPipe::createObject();
    mapOld2New.mapOld2New[pSurface] = pNewSurface;
    OdPrcPipePtr pPrcPipe = pSurface;
    // This surface type is currently not supported and reserved for future use.
    ODA_ASSERT(0);
  }*/
  else
  {
    ODA_ASSERT(0);
  }

  pNewSurface->setUVParameterization(pSurface->uVParameterization());
  copyPrcContentSurface(pNewSurface->contentSurface(), pSurface->contentSurface());
}

void copyPrcEdge(OdPrcEdgePtr & pNewEdge, const OdPrcEdgePtr & pEdge, OdPrcCloneMap & mapOld2New)
{
  if (pEdge.isNull())
  {
    pNewEdge = NULL;
    return;
  }
  std::map<OdRxObjectPtr, OdRxObjectPtr>::const_iterator pIt = mapOld2New.mapOld2New.find(pEdge);
  if (pIt != mapOld2New.mapOld2New.end())
  {
    pNewEdge = pIt->second;
    return;
  }
  pNewEdge = OdPrcEdge::createObject();
  mapOld2New.mapOld2New[pEdge] = pNewEdge;

  OdPrcContentWireEdge & newContentWireEdge = pNewEdge->contentWireEdge();
  const OdPrcContentWireEdge & contentWireEdge = pEdge->contentWireEdge();

  copyPrcBaseTopology(newContentWireEdge.baseTopology(), contentWireEdge.baseTopology());
  newContentWireEdge.setTrimInterval(contentWireEdge.trimInterval());
  copyPrcCurve(newContentWireEdge.curve(), contentWireEdge.curve(), mapOld2New);

  OdPrcTopoItemPtr pVertexStart, pVertexEnd;
  copyPrcVertex(pVertexStart, pEdge->vertexStart(), mapOld2New);
  pNewEdge->setStartVertex(pVertexStart);
  copyPrcVertex(pVertexEnd, pEdge->vertexEnd(), mapOld2New);
  pNewEdge->setEndVertex(pVertexEnd);
  pNewEdge->setTolerance(pEdge->tolerance());
}

void copyPrcCoEdge(OdPrcCoEdgePtr & pNewCoEdge, const OdPrcCoEdgePtr & pCoEdge, OdPrcCloneMap & mapOld2New)
{
  if (pCoEdge.isNull())
  {
    pNewCoEdge = NULL;
    return;
  }
  std::map<OdRxObjectPtr, OdRxObjectPtr>::const_iterator pIt = mapOld2New.mapOld2New.find(pCoEdge);
  if (pIt != mapOld2New.mapOld2New.end())
  {
    pNewCoEdge = pIt->second;
    return;
  }
  pNewCoEdge = OdPrcCoEdge::createObject();
  mapOld2New.mapOld2New[pCoEdge] = pNewCoEdge;
  copyPrcBaseTopology(pNewCoEdge->baseTopology(), pCoEdge->baseTopology());
  OdPrcEdgePtr pEdge;
  copyPrcEdge(pEdge, pCoEdge->edge(), mapOld2New);
  pNewCoEdge->setEdge(pEdge);

  copyPrcCurve(pNewCoEdge->curveUV(), pCoEdge->curveUV(), mapOld2New);
  pNewCoEdge->setOrientationWithLoop(pCoEdge->orientationWithLoop());
  pNewCoEdge->setOrientationUvWithLoop(pCoEdge->orientationUvWithLoop());

  OdPrcCoEdgePtr pNewNeighCoEdge;
  copyPrcCoEdge(pNewNeighCoEdge, pCoEdge->neighCoEdge(), mapOld2New);
  pNewCoEdge->setNeighCoEdge(pNewNeighCoEdge);
}

void copyPrcLoop(OdPrcLoopPtr & pNewLoop, const OdPrcLoopPtr & pLoop, OdPrcCloneMap & mapOld2New)
{
  if (pLoop.isNull())
  {
    pNewLoop = NULL;
    return;
  }
  std::map<OdRxObjectPtr, OdRxObjectPtr>::const_iterator pIt = mapOld2New.mapOld2New.find(pLoop);
  if (pIt != mapOld2New.mapOld2New.end())
  {
    pNewLoop = pIt->second;
    return;
  }
  pNewLoop = OdPrcLoop::createObject();
  mapOld2New.mapOld2New[pLoop] = pNewLoop;
  copyPrcBaseTopology(pNewLoop->baseTopology(), pLoop->baseTopology());
  pNewLoop->setOrientationWithSurface(pLoop->orientationWithSurface());

  const OdPrcCoEdgePtrArray & arrCoEdge = pLoop->coedges();
  for (OdUInt32 i = 0; i < arrCoEdge.size(); ++i)
  {
    OdPrcCoEdgePtr pNewCoEdge;
    copyPrcCoEdge(pNewCoEdge, arrCoEdge[i], mapOld2New);
    pNewLoop->addCoEdge(pNewCoEdge);
  }
}

void copyPrcFace(OdPrcFacePtr & pNewFace, const OdPrcFacePtr & pFace, OdPrcCloneMap & mapOld2New)
{
  if (pFace.isNull())
  {
    pNewFace = NULL;
    return;
  }
  std::map<OdRxObjectPtr, OdRxObjectPtr>::const_iterator pIt = mapOld2New.mapOld2New.find(pFace);
  if (pIt != mapOld2New.mapOld2New.end())
  {
    pNewFace = pIt->second;
    return;
  }
  pNewFace = OdPrcFace::createObject();
  mapOld2New.mapOld2New[pFace] = pNewFace;
  copyPrcBaseTopology(pNewFace->baseTopology(), pFace->baseTopology());
  copyPrcSurface(pNewFace->baseSurface(), pFace->baseSurface(), mapOld2New);
  pNewFace->setSurfaceTrimDomain(pFace->surfaceTrimDomain());
  pNewFace->setTolerance(pFace->tolerance());

  const OdPrcLoopPtrArray & arrLoops = pFace->loops();
  for (OdUInt32 i = 0; i < arrLoops.size(); ++i)
  {
    OdPrcLoopPtr pNewLoop;
    copyPrcLoop(pNewLoop, arrLoops[i], mapOld2New);
    pNewFace->addLoop(pNewLoop);
  }

  pNewFace->setOuterLoopIndex(pFace->getOuterLoopIndex());
  pNewFace->orientationSurfaceWithShell() = pFace->orientationSurfaceWithShell();

  //OdPrcGraphics *m_face_graphics; TODO: not fully implemented, only line styles with color can be copied
  /*if (pFace->hasGraphics())
  {
    OdPrcGraphics newGraphics;
    copyPrcGraphics(newGraphics, *pFace->graphics(), mapOld2New);
    pNewFace->setGraphics(&newGraphics);
  }*/
}

void copyPrcShell(OdPrcShellPtr & pNewShell, const OdPrcShellPtr & pShell, OdPrcCloneMap & mapOld2New)
{
  if (pShell.isNull())
  {
    pNewShell = NULL;
    return;
  }
  std::map<OdRxObjectPtr, OdRxObjectPtr>::const_iterator pIt = mapOld2New.mapOld2New.find(pShell);
  if (pIt != mapOld2New.mapOld2New.end())
  {
    pNewShell = pIt->second;
    return;
  }
  pNewShell = OdPrcShell::createObject();
  mapOld2New.mapOld2New[pShell] = pNewShell;
  copyPrcBaseTopology(pNewShell->baseTopology(), pShell->baseTopology());
  pNewShell->setShellIsClosed(pShell->shellIsClosed());

  const OdPrcFacePtrArray & arrFaces = pShell->faces();
  for (OdUInt32 i = 0; i < arrFaces.size(); ++i)
  {
    OdPrcFacePtr pNewFace;
    copyPrcFace(pNewFace, arrFaces[i], mapOld2New);
    pNewShell->addFace(pNewFace);
  }
}

void copyPrcConnex(OdPrcConnexPtr & pNewConnex, const OdPrcConnexPtr & pConnex, OdPrcCloneMap & mapOld2New)
{
  if (pConnex.isNull())
  {
    pNewConnex = NULL;
    return;
  }
  std::map<OdRxObjectPtr, OdRxObjectPtr>::const_iterator pIt = mapOld2New.mapOld2New.find(pConnex);
  if (pIt != mapOld2New.mapOld2New.end())
  {
    pNewConnex = pIt->second;
    return;
  }
  pNewConnex = OdPrcConnex::createObject();
  mapOld2New.mapOld2New[pConnex] = pNewConnex;
  copyPrcBaseTopology(pNewConnex->baseTopology(), pConnex->baseTopology());

  const OdPrcShellPtrArray & arrShells = pConnex->shells();
  for (OdUInt32 i = 0; i < arrShells.size(); ++i)
  {
    OdPrcShellPtr pNewShell;
    copyPrcShell(pNewShell, arrShells[i], mapOld2New);
    pNewConnex->addShell(pNewShell);
  }
}

void prcWblockCloneObject(OdRxObjectPtr & pNewObj, const OdRxObjectPtr & pObj, OdPrcCloneMap & mapOld2New)
{
  if (pObj->isKindOf(OdPrcConnex::desc()))
  {
    OdPrcConnexPtr pConnex;
    copyPrcConnex(pConnex, pObj, mapOld2New);
    pNewObj = pConnex;
  }
  else
  {
    ODA_ASSERT(0);
  }
}

OdPrcFilePtr CreateComplexModels(void); // from CreateComplexExample.cpp

void cloneConnexesFromComplexExample(OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  ODA_ASSERT(mode == kCloneConnexesFromComplexExample);

  // create new file
  OdPrcFilePtr pNewFile = createTopologyCommon();
  OdPrcFileStructurePtr pNewStructure = pNewFile->fileStructures().last();
  OdPrcProductOccurrencePtr pRootPO = pNewStructure->fileStructureTree().internalData().getRootProductOccurrenceID().openObject(kForWrite);
  OdPrcPartDefinitionPtr pPD = createPartDefinition(*pNewStructure, *pRootPO);
  OdPrcTopoContextPtr newTopoContext = createTopoContext(*pNewStructure);

  {
    //OdPrcFilePtr pFile = pHostApp->readFile(pHostApp->findFile(L"D:/1.prc"));
    OdPrcFilePtr pFile = CreateComplexModels(); // create prc with all brep examples

    const OdPrcFileStructurePtrArray & arrFs = pFile->fileStructures();
    for (OdUInt32 i = 0; i < arrFs.size(); ++i)
    {
      OdPrcFileStructurePtr pFs = arrFs[i];
      const OdPrcFileStructureExactGeometry & exactGeom = pFs->fileStructureGeometry().fileStructureExactGeometry();
      const OdPrcTopoContextPtrArray & arrCB = exactGeom.topologicalContext();
      for (OdUInt32 i = 0; i < arrCB.size(); ++i)
      {
        const OdPrcObjectIdArray & arrBody = arrCB[i]->bodies();
        for (OdUInt32 i = 0; i < arrBody.size(); ++i)
        {
          OdPrcBrepDataPtr pBD = arrBody[i].openObject();

          OdGeExtents3d extents = pBD->boundingBox().box();
          OdPrcRepresentationItemPtr pNewRepItem = createRI<OdPrcBrepModel>(*pNewStructure, *pPD);
          pPD->boundingBox().box() = extents;
          OdPrcBrepDataPtr pNewBD = createBody<OdPrcBrepData>(*pNewStructure, *newTopoContext, *pNewRepItem);
          pNewBD->boundingBox().box() = extents;
          pNewBD->contentBody().setBoundingBoxBehaviour(2);

          pNewRepItem->name().setName(OdString().format(L"BrepData without graphics[%d]", newTopoContext->bodies().size()));

          const OdPrcConnexPtrArray & arrConnex = pBD->connex();
          for (OdUInt32 i = 0; i < arrConnex.size(); ++i)
          {
            OdPrcCloneMap cloneMap;
            cloneMap.pTargetDatabase = pNewStructure;
            OdRxObjectPtr pNewConnex;
            prcWblockCloneObject(pNewConnex, arrConnex[i], cloneMap);
            pNewBD->addConnex(pNewConnex); // all into one brepData
          }
        }
      }
    }
  }

  pNewFile->writeFile(pPrcStream);
}

void copyPrcShellFaces(OdPrcShellPtrArray & aPtrNewShell, const OdPrcShellPtr & pShell, OdPrcCloneMap & mapOld2New)
{
  if (pShell.isNull())
  {
    return;
  }
  std::map<OdRxObjectPtr, OdRxObjectPtr>::const_iterator pIt = mapOld2New.mapOld2New.find(pShell);
  if (pIt != mapOld2New.mapOld2New.end())
  {
    return;
  }

  const OdPrcFacePtrArray & arrFaces = pShell->faces();
  for (OdUInt32 i = 0; i < arrFaces.size(); ++i)
  {
    OdPrcShellPtr pNewShell = OdPrcShell::createObject();
    mapOld2New.mapOld2New[pShell] = pNewShell;
    copyPrcBaseTopology(pNewShell->baseTopology(), pShell->baseTopology());
    pNewShell->setShellIsClosed(pShell->shellIsClosed());

    OdPrcFacePtr pNewFace;
    copyPrcFace(pNewFace, arrFaces[i], mapOld2New);
    pNewShell->addFace(pNewFace);

    aPtrNewShell.push_back(pNewShell);
  }
}

void copyPrcConnexFaces(OdPrcConnexPtrArray & aNewConnex, const OdPrcConnexPtr & pConnex, OdPrcCloneMap & mapOld2New)
{
  if (pConnex.isNull())
  {
    return;
  }
  std::map<OdRxObjectPtr, OdRxObjectPtr>::const_iterator pIt = mapOld2New.mapOld2New.find(pConnex);
  if (pIt != mapOld2New.mapOld2New.end())
  {
    return;
  }

  const OdPrcShellPtrArray & arrShells = pConnex->shells();
  for (OdUInt32 i = 0; i < arrShells.size(); ++i)
  {
    OdPrcShellPtrArray aNewShellArray;
    copyPrcShellFaces(aNewShellArray, arrShells[i], mapOld2New);

    for (OdUInt32 j = 0; j < aNewShellArray.size(); ++j)
    {
      OdPrcShellPtr pNewShell = aNewShellArray[j];
      OdPrcConnexPtr pNewConnex = OdPrcConnex::createObject();
      mapOld2New.mapOld2New[pConnex] = pNewConnex;

      copyPrcBaseTopology(pNewConnex->baseTopology(), pConnex->baseTopology());
      pNewConnex->addShell(pNewShell);

      aNewConnex.push_back(pNewConnex);
    }

  }
}

void explodeExample(OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  // create new file
  OdPrcFilePtr pNewFile = createTopologyCommon();
  OdPrcFileStructurePtr pNewStructure = pNewFile->fileStructures().last();
  OdPrcProductOccurrencePtr pRootPO = pNewStructure->fileStructureTree().internalData().getRootProductOccurrenceID().openObject(kForWrite);
  OdPrcPartDefinitionPtr pPD = createPartDefinition(*pNewStructure, *pRootPO);
  OdPrcTopoContextPtr newTopoContext = createTopoContext(*pNewStructure);

  {
    //OdPrcFilePtr pFile = pPrcHost.readFile(pPrcHost.findFile(L"d:/Component_View_2_23_17_resaved_color.prc"));
    OdPrcFilePtr pFile = CreateComplexModels(); // create prc with all brep examples

    const OdPrcFileStructurePtrArray & arrFs = pFile->fileStructures();
    for (OdUInt32 i = 0; i < arrFs.size(); ++i)
    {
      OdPrcFileStructurePtr pFs = arrFs[i];
      const OdPrcFileStructureExactGeometry & exactGeom = pFs->fileStructureGeometry().fileStructureExactGeometry();
      const OdPrcTopoContextPtrArray & arrCB = exactGeom.topologicalContext();
      for (OdUInt32 j = 0; j < arrCB.size(); ++j)
      {
        const OdPrcObjectIdArray & arrBody = arrCB[j]->bodies();
        for (OdUInt32 k = 0; k < arrBody.size(); ++k)
        {
          // Open Old BrepData
          OdPrcBrepDataPtr pBD = arrBody[k].openObject();
          const OdPrcConnexPtrArray & arrConnex = pBD->connex();
          OdPrcConnexPtrArray aNewConnex;
          for (OdUInt32 p = 0; p < arrConnex.size(); ++p)
          {
            OdPrcCloneMap cloneMap;
            cloneMap.pTargetDatabase = pNewStructure;
            copyPrcConnexFaces(aNewConnex, arrConnex[p], cloneMap);

            for (OdUInt32 l = 0; l < aNewConnex.size(); ++l)
            {
              OdGeExtents3d extents = pBD->boundingBox().box();
              OdPrcRepresentationItemPtr pNewRepItem = createRI<OdPrcBrepModel>(*pNewStructure, *pPD);
              pPD->boundingBox().box() = extents;
              OdPrcBrepDataPtr pNewBD = createBody<OdPrcBrepData>(*pNewStructure, *newTopoContext, *pNewRepItem);
              pNewBD->boundingBox().box() = extents;
              pNewBD->contentBody().setBoundingBoxBehaviour(2);

              pNewRepItem->name().setName(OdString().format(L"BrepData without graphics[%d]", newTopoContext->bodies().size()));

              pNewBD->addConnex(aNewConnex[l]);
            }
          }
        }
      }
    }
  }

  pNewFile->writeFile(pPrcStream);
}
