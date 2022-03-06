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

#include "TvGeomCollector.h"

#include "Ge/GeKnotVector.h"
#include "Ge/GeNurbCurve3d.h"
#include "Ge/GeEllipArc3d.h"
#include "Gi/GiGeometry.h"

#define START_TIMER                   \
  if (m_timer)                        \
    m_timer->start();

#define END_TIMER                                    \
  if (m_timer)                                       \
  {                                                  \
    m_totalTime += m_timer->permanentSec();          \
    m_timer->stop();                                 \
  }


//***************************************************************************//
// 'OdTvGeomCollector' methods implementation
//***************************************************************************//

OdTvGeomCollector::OdTvGeomCollector(bool bWithTiming) : m_CurColor(OdCmEntityColor::kByLayer)
, m_ColorForByLayer(OdCmEntityColor::kNone)
, m_targetDisplayMode(OdTvGeometryData::kEveryWhere)
, m_totalTime(0)
{
  if (bWithTiming)
    m_timer = OdPerfTimerBase::createTiming();
  else
    m_timer = NULL;
}

OdTvGeomCollector::~OdTvGeomCollector()
{
  if ( m_timer )
  {
    OdPerfTimerBase::destroyTiming(m_timer);
    m_timer = NULL;
  }
}

void OdTvGeomCollector::setTvEntity(OdTvEntityId entityId)
{
  m_tvEntity = entityId;
}
void OdTvGeomCollector::setTvEntity(OdTvGeometryDataId entityId)
{
  m_tvSubEntity = entityId;
}

OdTvEntityPtr OdTvGeomCollector::open() const
{
  //exactly one ID must be set
  ODA_ASSERT(int(m_tvEntity.isNull()) + int(m_tvSubEntity.isNull()) == 1);
  if (!m_tvEntity.isNull())
    return m_tvEntity.openObject(OdTv::kForWrite);
  else
    return m_tvSubEntity.openAsSubEntity(OdTv::kForWrite);
}

void OdTvGeomCollector::setTrueColor(const OdCmEntityColor& color)
{
  m_CurColor = color;
}

void OdTvGeomCollector::pushModelTransform(const OdGeMatrix3d& xMat)
{ 
  bool bIsEmpty = m_xModelStack.empty();
  OdGeMatrix3d* pNew = m_xModelStack.push();

  if (!bIsEmpty)
    pNew->setToProduct(*m_xModelStack.beforeTop(), xMat);
  else
    *pNew = xMat;
}

void OdTvGeomCollector::popModelTransform()
{
  m_xModelStack.pop();
}

void OdTvGeomCollector::polyline(OdInt32 nbPoints, const OdGePoint3d* pVertexList, const OdGeVector3d* pNormal, OdGsMarker lBaseSubEntMarker)
{
  START_TIMER

  OdTvEntityPtr entity = open();
  applyTraitsAndTransform(entity->appendPolyline(nbPoints, pVertexList));

  END_TIMER
}

void OdTvGeomCollector::nurbs(const OdGeNurbCurve3d& nurbsCurve)
{
  START_TIMER

  int degree;
  bool rational;
  bool periodic;
  OdGeKnotVector knots;
  OdGePoint3dArray controlPoints;
  OdGeDoubleArray weights;
  
  nurbsCurve.getDefinitionData(degree, rational, periodic, knots, controlPoints, weights);

  //recalculate interval from [A; B] to [0; 1]
  
  //1. get interval
  OdGeInterval interval;
  nurbsCurve.getInterval(interval);

  double nurbStart = interval.lowerBound();
  double nurbEnd = interval.upperBound();

  //2. get global interval range
  double startKnotParam = knots[0];
  double endKnotParam = knots[knots.logicalLength() - degree - 1];

  //3. perform [A; B] to [0; 1]
  double start = 0.;
  double end = 1.;
  double intervalRange = endKnotParam - startKnotParam;
  if (!OdZero(intervalRange))
  {
    start = (nurbStart - startKnotParam) / intervalRange;
    end = (nurbEnd - startKnotParam) / intervalRange;
  }

  if ((start < 0. || start > 1.) || (end < 0. || end > 1.) || start > end)
  {
    start = 0.;
    end = 1.;
  }

  OdTvEntityPtr entity = open();
  applyTraitsAndTransform(entity->appendNurbs(degree, controlPoints.length(), controlPoints.asArrayPtr(), weights.asArrayPtr(), knots.length(), knots.asArrayPtr(), start, end));

  END_TIMER
}

void OdTvGeomCollector::circle(const OdGePoint3d& center, double radius, const OdGeVector3d& normal)
{
  START_TIMER

  OdTvEntityPtr entity = open();
  applyTraitsAndTransform(entity->appendCircle(center, radius, normal));

  END_TIMER
}

void OdTvGeomCollector::circle(const OdGePoint3d& firstPoint, const OdGePoint3d& secondPoint, const OdGePoint3d& thirdPoint)
{
  START_TIMER

  OdTvEntityPtr entity = open();
  applyTraitsAndTransform(entity->appendCircle(firstPoint, secondPoint, thirdPoint));

  END_TIMER
}

void OdTvGeomCollector::circularArc(const OdGePoint3d& center, double radius, const OdGeVector3d& normal, const OdGeVector3d& startVector, double sweepAngle, OdGiArcType arcType)
{
  START_TIMER

  OdGeCircArc3d arc(center, normal, startVector, radius, 0., sweepAngle);

  OdTvEntityPtr entity = open();
  applyTraitsAndTransform(entity->appendCircleArc(arc.evalPoint(0.), arc.evalPoint(sweepAngle / 2.), arc.evalPoint(sweepAngle)));

  END_TIMER
}

void OdTvGeomCollector::circularArc(const OdGePoint3d& firstPoint, const OdGePoint3d& secondPoint, const OdGePoint3d& thirdPoint, OdGiArcType arcType)
{
  START_TIMER

  OdTvEntityPtr entity = open();
  applyTraitsAndTransform(entity->appendCircleArc(firstPoint, secondPoint, thirdPoint));

  END_TIMER
}

void OdTvGeomCollector::ellipArc(const OdGeEllipArc3d& ellipArc, const OdGePoint3d* endPointsOverrides, OdGiArcType arcType)
{
  START_TIMER

  OdTvPoint center = ellipArc.center();
  OdTvVector majorAxis = ellipArc.majorAxis();
  OdTvVector minorAxis = ellipArc.minorAxis();
  double majorRadius = ellipArc.majorRadius();
  double minorRadius = ellipArc.minorRadius();

  majorAxis = majorRadius * majorAxis.normalize();
  minorAxis = minorRadius * minorAxis.normalize();
  
  OdTvPoint majorPoint = OdTvPoint(center + majorAxis);
  OdTvPoint minorPoint = OdTvPoint(center + minorAxis);

  OdTvEntityPtr entity = open();
  applyTraitsAndTransform(entity->appendEllipticArc(center, majorPoint, minorPoint, ellipArc.startAng(), ellipArc.endAng()));

  END_TIMER
}

void OdTvGeomCollector::shell(OdInt32 numVertices, const OdGePoint3d* vertexList, OdInt32 faceListSize, const OdInt32* faceList, 
                                    const OdGiEdgeData* pEdgeData, const OdGiFaceData* pFaceData, const OdGiVertexData* pVertexData)
{
  START_TIMER

  // open entity
  OdTvEntityPtr entity = open();
  OdTvGeometryDataId shellId = entity->appendShell(numVertices, vertexList, faceListSize, faceList);

  //open shell
  OdTvShellDataPtr pShell = shellId.openAsShell();
  if (!pShell.isNull())
  {
    // get information about vertices
    if (pVertexData != NULL)
    {
      //colors
      if (pVertexData->trueColors() != NULL)
      {
        OdCmEntityColor* pColors = (OdCmEntityColor*)pVertexData->trueColors();
        OdTvRGBColorDefArray colors;
        colors.resize(numVertices);
        
        for (OdInt32 i = 0; i < numVertices; i++)
        {
          if (pColors[i].colorMethod() != OdCmEntityColor::kByColor) // color can be only rgb
          {
            ODA_ASSERT(1);
            colors[i] = OdTvRGBColorDef(255,255,255);
          }
          else
            colors[i] = OdTvRGBColorDef(pColors[i].red(), pColors[i].green(), pColors[i].blue());
        }

        pShell->setVertexColorsViaRange(0, colors);
      }

      // normals
      if (pVertexData->normals() != NULL)
        pShell->setVertexNormalsViaRange(0, numVertices, pVertexData->normals());

      // orientation
      if (pVertexData->orientationFlag() != kOdGiNoOrientation)
      {
        OdTv::OrientationType orientationType = OdTv::kCounterClockwise;
        if (pVertexData->orientationFlag() == kOdGiClockwise)
          orientationType = OdTv::kClockwise;

        pShell->setVertexOrientation(orientationType);
      }
    }

    // calculate number of faces and edges (if need)
    OdInt32 nFace = 0;
    OdInt32 nEdge = 0;
    if (pFaceData != NULL || pEdgeData != NULL)
    {
      getNumberOfShellFacesAndEdges(faceListSize, faceList, nFace, nEdge);
    }

    // get information about faces
    if (pFaceData != NULL)
    {
      // colors
      if (pFaceData->trueColors() != NULL)
      {
        OdCmEntityColor* pColors = (OdCmEntityColor*)pFaceData->trueColors();
        OdTvColorDefArray colors;

        fillColors(nFace, pColors, colors);

        pShell->setFaceColorsViaRange(0, colors);
      }

      //normals
      if (pFaceData->normals() != NULL)
        pShell->setFaceNormalsViaRange(0, nFace, pFaceData->normals());

      //visibility
      if (pFaceData->visibility() != NULL)
      {
        OdUInt8* pVisibility = (OdUInt8*)pFaceData->visibility();
        OdTvVisibilityDefArray visibilities;
        
        fillVisibilities(nFace, pVisibility, visibilities);

        pShell->setFaceVisibilitiesViaRange(0, visibilities);
      }
    }

    // get information about edges
    if (pEdgeData != NULL)
    {
      //colors
      if (pEdgeData->trueColors() != NULL)
      {
        OdCmEntityColor* pColors = (OdCmEntityColor*)pEdgeData->trueColors();
        OdTvColorDefArray colors;

        fillColors(nEdge, pColors, colors);

        pShell->setEdgeColorsViaRange(0, colors);
      }

      //visibility
      if (pEdgeData->visibility() != NULL)
      {
        OdUInt8* pVisibility = (OdUInt8*)pEdgeData->visibility();
        OdTvVisibilityDefArray visibilities;

        fillVisibilities(nEdge, pVisibility, visibilities);

        pShell->setEdgeVisibilitiesViaRange(0, visibilities);
      }
    }
  }

  //apply some properties and transform
  applyTraitsAndTransform(shellId);

  END_TIMER
}

void OdTvGeomCollector::polypoint(OdInt32 numPoints, const OdGePoint3d* pointList, const OdCmEntityColor* pColors, const OdCmTransparency* pTransparency, const OdGeVector3d* pNormals /*= NULL*/, const OdGsMarker* pSubEntMarkers /*NULL*/, OdInt32 nPointSize /*= 0*/)
{
  START_TIMER

  OdTvEntityPtr entity = open();
  OdTvGeometryDataId pointCloudId = entity->appendPointCloud(numPoints, pointList);
  OdTvPointCloudDataPtr pPointCloud = pointCloudId.openAsPointCloud();

  OdTvRGBColorDefArray colors;
  colors.resize(numPoints);
  for (OdInt32 i = 0; i < numPoints; i++)
    colors[i].setColor(pColors[i].red(), pColors[i].green(), pColors[i].blue());

  pPointCloud->setPointColorsViaRange(0, numPoints, colors.asArrayPtr());
  if(pNormals)
    pPointCloud->setPointNormalsViaRange(0, numPoints, pNormals);
  pPointCloud->setPointSize(nPointSize);

  //apply some properties and transform
  applyTraitsAndTransform(pointCloudId);

  END_TIMER
}

void OdTvGeomCollector::applyTraitsAndTransform(const OdTvGeometryDataId& geomId)
{
  OdTvGeometryDataPtr pGeom = geomId.openObject();
  if (pGeom.isNull())
    return;

  pGeom->setTargetDisplayMode(m_targetDisplayMode);

  if ( !m_xModelStack.empty() )
    pGeom->setModelingMatrix(*m_xModelStack.top());

  if (m_CurColor.colorMethod() == OdCmEntityColor::kByColor)
    pGeom->setColor(OdTvColorDef(m_CurColor.red(), m_CurColor.green(), m_CurColor.blue()));
  else if (m_CurColor.colorMethod() == OdCmEntityColor::kByACI)
  {
    OdUInt32 color = OdCmEntityColor::lookUpRGB(m_CurColor.colorIndex());
    color |= 0xC2000000; //sets kByColor
    pGeom->setColor( OdTvColorDef(OdCmEntityColor::red(&color), OdCmEntityColor::green(&color), OdCmEntityColor::blue(&color)) );
  }
  else if (m_CurColor.colorMethod() == OdCmEntityColor::kByLayer)
  {
    if (m_ColorForByLayer.colorMethod() == OdCmEntityColor::kByColor)
      pGeom->setColor(OdTvColorDef(m_ColorForByLayer.red(), m_ColorForByLayer.green(), m_ColorForByLayer.blue()));
  }
}

void OdTvGeomCollector::getNumberOfShellFacesAndEdges(OdInt32 faceListSize, const OdInt32* faceList, OdInt32& nFace, OdInt32& nEdge) const
{
  nFace = 0;
  nEdge = 0;

  OdInt32 i = 0;

  while (i < faceListSize)
  {
    OdInt32 n = faceList[i++];
    if (n > 0)
      nFace++;
    else
      n = -n;

    nEdge += n;

    i += n;
  }
}

void OdTvGeomCollector::fillVisibilities(OdInt32 nVisibilities, OdUInt8* pVisibilities, OdTvVisibilityDefArray& visibilities)
{
  visibilities.resize(nVisibilities);

  for (OdInt32 i = 0; i < nVisibilities; i++)
  {
    visibilities[i] = OdTvVisibilityDef(pVisibilities[i] == 1 ? true : false);
  }

  return;
}

void OdTvGeomCollector::fillColors(OdInt32 nColors, OdCmEntityColor* pColors, OdTvColorDefArray& colors)
{
  colors.resize(nColors);

  for (OdInt32 i = 0; i < nColors; i++)
  {
    switch (pColors[i].colorMethod())
    {
    case OdCmEntityColor::kByColor:
      colors[i] = OdTvColorDef(pColors[i].red(), pColors[i].green(), pColors[i].blue());
      break;
    case OdCmEntityColor::kByLayer:
      colors[i] = OdTvColorDef(OdTv::kByLayer);
      break;
    case OdCmEntityColor::kByBlock:
      colors[i] = OdTvColorDef(OdTv::kByBlock);
      break;
    case OdCmEntityColor::kByACI:
    case OdCmEntityColor::kByDgnIndex:
      colors[i] = OdTvColorDef((OdUInt8)pColors[i].colorIndex());
      break;
    default:
      ODA_ASSERT(1);
      colors[i] = OdTvColorDef(255, 255, 255);
      break;
    }
  }

  return;
}

OdTvResult OdTvGeomCollector::setTargetDisplayMode(OdTvGeometryData::TargetDisplayMode targetMode)
{
  m_targetDisplayMode = targetMode;
  return tvOk;
}

OdTvGeometryData::TargetDisplayMode  OdTvGeomCollector::getTargetDisplayMode(OdTvResult*rc) const
{
  return m_targetDisplayMode;
}

void OdTvGeomCollector::setColorForByLayer(const OdCmEntityColor& color)
{
  m_ColorForByLayer = color;
}

double OdTvGeomCollector::getTotalTime() const
{
  return m_totalTime;
}
