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

#include "VisualizeModelsGeneratorUtils.h"

//***************************************************************************//
// PRIVATE methods
//***************************************************************************//

void OdTvVisualizeSampleModelsUtils::generatePointOnCircle(OdGePoint3d& pt, OdGePoint3d& center, double radius, int axis, double angle)
{
  OdGePoint3d temp;

  switch (axis)
  {
  case 0:
    pt.set(center.x + radius * cos(angle), center.y, center.z + radius * sin(angle));
    break;
  case 1:
    pt.set(center.x + radius * cos(angle), center.y + radius * sin(angle), center.z);
    break;
  case 2:
    pt.set(center.x, center.y + radius * cos(angle), center.z + radius * sin(angle));
    break;
  default:
    pt.set(center.x + radius * cos(angle), center.y + radius * sin(angle), center.z);
    break;
  }

  return;
}

void OdTvVisualizeSampleModelsUtils::getColorByValue(double min, double max, double value, OdUInt8* r, OdUInt8* g, OdUInt8* b)
{
  double rel;

  if (!r || !g || !b)
    return;

  rel = fabs(value - min) / fabs(max - min);

  if (rel > 1.)
    return;

  float rf, gf, bf;

  if (rel < 0.25)
  {
    rf = 0.0f;
    bf = 1.0f;
    gf = (float)rel / 0.25f;
  }
  else if (rel < 0.5)
  {
    rf = 0.0f;
    bf = (0.5f - (float)rel) / 0.25f;
    gf = 1.0f;
  }
  else if (rel < 0.75)
  {
    rf = ((float)rel - 0.5f) / 0.25f;
    bf = 0.0f;
    gf = 1.0f;
  }
  else
  {
    rf = 1.0f;
    bf = 0.0f;
    gf = (1.0f - (float)rel) / 0.25f;
  }

  *r = OdUInt8(rf*255.f);
  *g = OdUInt8(gf*255.f);
  *b = OdUInt8(bf*255.f);

  return;
}

void OdTvVisualizeSampleModelsUtils::fillPointsForX(OdTvPoint& pointOne, OdTvPoint& pointTwo, OdTvPoint& pointThree, OdTvPoint& pointFour, OdTvPoint& pointFive, double& posStep, double& markStep, double& pos, OdUInt32 num, const OdTvPoint& topLeft, const OdTvPoint& bottomRight, double startMark, double endMark)
{
  pointOne = OdTvPoint(0., bottomRight.y - 0.05, bottomRight.z);
  pointTwo = OdTvPoint(0., bottomRight.y, bottomRight.z);
  pointThree = OdTvPoint(0., bottomRight.y + 0.01, bottomRight.z);
  pointFour = OdTvPoint(0., topLeft.y, topLeft.z);
  pointFive = OdTvPoint(0., topLeft.y - 0.01, topLeft.z);

  pos = topLeft.x;
  posStep = fabs(bottomRight.x - topLeft.x) / (num - 1);
  markStep = fabs(endMark - startMark) / (num - 1);
}

void OdTvVisualizeSampleModelsUtils::fillPointsForY(OdTvPoint& pointOne, OdTvPoint& pointTwo, OdTvPoint& pointThree, OdTvPoint& pointFour, OdTvPoint& pointFive, double& posStep, double& markStep, double& pos, OdUInt32 num, const OdTvPoint& topLeft, const OdTvPoint& bottomRight, double startMark, double endMark)
{
  pointOne = OdTvPoint(topLeft.x - 0.05, 0., bottomRight.z);
  pointTwo = OdTvPoint(topLeft.x, 0., topLeft.z);
  pointThree = OdTvPoint(topLeft.x + 0.01, 0., topLeft.z);
  pointFour = OdTvPoint(bottomRight.x, 0., bottomRight.z);
  pointFive = OdTvPoint(bottomRight.x - 0.01, 0., bottomRight.z);

  pos = bottomRight.y - 0.015;
  posStep = fabs(topLeft.y - bottomRight.y) / (num - 1);
  markStep = fabs(endMark - startMark) / (num - 1);
}

OdTvPoint& OdTvVisualizeSampleModelsUtils::updatePointForX(OdTvPoint& point, double value, bool bIsTextPoint)
{
  point.x = value;
  return point;
}

OdTvPoint& OdTvVisualizeSampleModelsUtils::updatePointForY(OdTvPoint& point, double value, bool bIsTextPoint)
{
  point.y = value;
  if (!bIsTextPoint)
    point.y += 0.015;

  return point;
}

void OdTvVisualizeSampleModelsUtils::drawAxis(OdTvEntityPtr pGraphEntity, double startMark, double endMark, OdUInt32 num, const OdTvPoint& topLeft, const OdTvPoint& bottomRight,
                                              void(*fillData) (OdTvPoint&, OdTvPoint&, OdTvPoint&, OdTvPoint&, OdTvPoint&, double&, double&, double&, OdUInt32, const OdTvPoint&,
                                              const OdTvPoint&, double, double), OdTvPoint& (*updatePoint) (OdTvPoint&, double, bool))
{
  double pos = 0, posStep = 0, markStep = 0;
  OdTvPoint pointOne, pointTwo, pointThree, pointFour, pointFive;
  fillData(pointOne, pointTwo, pointThree, pointFour, pointFive, posStep, markStep, pos, num, topLeft, bottomRight, startMark, endMark);
  double mark = startMark;

  for (OdUInt32 i = 0; i < num; i++)
  {
    OdString markStr; double temp; OdGeTol tol;
    double fraction = modf(mark, &temp);

    if (fabs(fraction) > tol.equalPoint())
      markStr.format(OD_T("%.1f"), mark);
    else
      markStr.format(OD_T("%d"), (OdInt32)mark);

    pGraphEntity->appendText(updatePoint(pointOne, pos, true), markStr);
    pGraphEntity->appendPolyline(updatePoint(pointTwo, pos, false), updatePoint(pointThree, pos, false));
    pGraphEntity->appendPolyline(updatePoint(pointFour, pos, false), updatePoint(pointFive, pos, false));

    pos += posStep;

    mark += markStep;
  }
}

double OdTvVisualizeSampleModelsUtils::getTempGradientFromZ(double zCur, double zLeft, double zRight, double dTMax)
{
  double dT = 0.;

  if (zCur > zLeft && zCur < zRight)
  {
    //according to the normal law
    double sigma = 1. / (sqrt(Oda2PI) * dTMax);
    double M = (zRight + zLeft) / 2. - zLeft;
    double dZ = (zCur - zLeft) - M;
    double expVal = -dZ * dZ / (2. * sigma * sigma);

    dT = dTMax * exp(expVal);
  }

  return dT;
}

//***************************************************************************//
// PUBLIC methods
//***************************************************************************//

OdTvGeometryDataId OdTvVisualizeSampleModelsUtils::appendRectangle(OdTvEntityPtr entity, double x0, double y0, double x1, double y1, double z, bool bFill, bool bForcePolygon)
{
  OdTvGeometryDataId geom;
  OdTvPointArray pts; pts.resize(4);

  pts[0].x = x0;   pts[0].y = y0;   pts[0].z = z;
  pts[1].x = x0;   pts[1].y = y1;   pts[1].z = z;
  pts[2].x = x1;   pts[2].y = y1;   pts[2].z = z;
  pts[3].x = x1;   pts[3].y = y0;   pts[3].z = z;

  if (bFill || bForcePolygon)
  {
    geom = entity->appendPolygon(pts);
    geom.openAsPolygon()->setFilled(bFill);
    // for correct working of the line type
    geom.openAsPolygon()->setUseInverseNormal(true);
  }
  else
  {
    pts.resize(5);
    pts[4].x = x0;   pts[4].y = y0;   pts[4].z = z;
    geom = entity->appendPolyline(pts);

    // for correct working of the line type
    OdTvVector normal = OdTvVector::kZAxis;
    geom.openAsPolyline()->setNormal(&normal);
  }
  return geom;
}


void OdTvVisualizeSampleModelsUtils::generatePointsOnCircle(OdGePoint3dArray& pts, OdGePoint3d& center, double radius, int axis)
{
  int size = (int)pts.size();
  int i;
  double angle = 2.0 * OdaPI / (double)size;

  for (i = 0; i < size; i++)
  {
    OdTvVisualizeSampleModelsUtils::generatePointOnCircle(pts[i], center, radius, axis, angle*i);
  }

  return;
}


double OdTvVisualizeSampleModelsUtils::getLinInterCoef(double x1, double x0, double y1, double y0)
{
  if (OdEqual(x1, x0))
    return 0.;

  return (y1 - y0) / (x1 - x0);
}


double OdTvVisualizeSampleModelsUtils::mediana(double a, double b)
{
  return (a + b) / 2;
}


OdTvLinetypeId OdTvVisualizeSampleModelsUtils::generateCustomLineTypeWithText(OdTvDatabaseId databaseId)
{
  OdTvDatabasePtr pDb = databaseId.openObject(OdTv::kForWrite);

  // create true type text style
  OdTvTextStyleId ttfTsId = pDb->createTextStyle("Algerian_ttf");

  OdString typeface = L"Algerian";
  OdInt16 charset = 0;
  OdInt16 family = 34;
  bool bold = false;
  bool italic = false;

  OdTvTextStylePtr pTextStyle = ttfTsId.openObject(OdTv::kForWrite);
  pTextStyle->setFont(typeface, bold, italic, charset, family);

  // Create custom linetype with text
  // Create array of the linetype pattern elements
  OdTvLinetypeDashElementPtr pDash = OdTvLinetypeDashElement::createObject();
  pDash->setSize(0.8);

  OdTvLinetypeSpaceElementPtr pSpace = OdTvLinetypeSpaceElement::createObject();
  pSpace->setSize(0.2);

  OdTvLinetypeTextElementPtr pText = OdTvLinetypeTextElement::createObject();
  pText->setSize(-1.);
  pText->setText("ODA");
  pText->setStyle(ttfTsId);
  pText->setOffset(OdTvVector2d(-0.7, 0.));

  OdTvLinetypeElementArray lparray;
  lparray.push_back(pDash);
  lparray.push_back(pText);
  lparray.push_back(pSpace);

  // create custom line type based on the pattern
  return pDb->createLinetype("Custom with text", lparray);
}


void OdTvVisualizeSampleModelsUtils::append3dPlot(OdTvEntityPtr pGraphEntity, double startX, double endX, double startY, double endY, double startXMark, double startYMark, double startZMark, double endXMark, double endYMark,
                                                  double endZMark, OdUInt32 nDiv, const OdTvPoint& pointXYZ, const OdTvPoint& pointXY, const OdTvPoint& pointXZ, double(*func)(double, double))
{
  double xScale = fabs(getLinInterCoef(endXMark, startXMark, pointXYZ.x, pointXY.x));
  double yScale = fabs(getLinInterCoef(endYMark, startYMark, pointXYZ.y, pointXY.y));
  double zScale = fabs(getLinInterCoef(endZMark, startZMark, pointXYZ.z, pointXZ.z));

  OdTvPoint zeroPoint( pointXYZ.x - fabs(startXMark) * xScale,
                       pointXYZ.y - fabs(startYMark) * yScale,
                       pointXYZ.z + fabs(startZMark) * zScale );

  OdTvPointArray vertices;
  OdTvRGBColorDefArray colors;
  OdUInt8 r, g, b;
  double x = startX;

  for (OdUInt32 i = 0; i < nDiv; i++)
  {
    double y = startY;
    for (OdUInt32 j = 0; j < nDiv; j++)
    {
      double z = func(x, y);
      vertices.append(zeroPoint + OdTvVector(x*xScale, y*yScale, z*zScale));
      
      getColorByValue(startZMark, endZMark, z, &r, &g, &b);
      colors.append(OdTvRGBColorDef(r, g, b));

      y += (fabs(startY - endY) / nDiv);
    }
    x += (fabs(startX - endX) / nDiv);
  }

  OdTvGeometryDataId meshId = pGraphEntity->appendMesh(nDiv, nDiv, vertices);

  OdTvMeshDataPtr pMesh = meshId.openAsMesh();
  pMesh->setVertexColorsViaRange(0, colors);
}


void OdTvVisualizeSampleModelsUtils::appendGridLines(OdTvEntityPtr pModelRootEntity, bool bBig, OdUInt32 nColumns, OdUInt32 nRows, double startX, double startY, double xLenth, double yLenth)
{
  OdTvGeometryDataId base_lines_Id = pModelRootEntity->appendSubEntity(OD_T("base_lines"));
  {
    OdTvEntityPtr base_lines_ptr = base_lines_Id.openAsSubEntity(OdTv::kForWrite);
    base_lines_ptr->setColor(OdTvColorDef(128, 128, 128), OdTvGeometryData::kAll);
    base_lines_ptr->setLineWeight(OdTvLineWeightDef(1));

    double x = startX, y = startY;

    if (bBig)
    {
      OdTvVisualizeSampleModelsUtils::appendGridLines(pModelRootEntity, false, 3, 8, startX, 0.33, 0.67, yLenth);
      OdTvVisualizeSampleModelsUtils::appendGridLines(pModelRootEntity, false, 1, 4, 1.01, -0.99, 0.67, yLenth);
    }
    else //add rectangle
    {
      for (OdUInt32 i = 0; i < nRows; i++, y -= yLenth)
      {
        double tempX = x;
        for (OdUInt32 j = 0; j < nColumns; j++, tempX += xLenth)
        {
          OdTvVisualizeSampleModelsUtils::appendRectangle(base_lines_ptr, tempX, y, tempX + xLenth, y - yLenth, 0.);
        }
      }
    }
  }

  return;
}

void OdTvVisualizeSampleModelsUtils::append2dPlot(OdTvEntityPtr pGraphEntity, double start, double end, double startXMark, double startYMark, double endXMark, double endYMark, OdUInt32 nDiv, const OdTvPoint& topLeft, const OdTvPoint& bottomRight, double(*func)(double))
{
  double xScale = fabs(getLinInterCoef(endXMark, startXMark, topLeft.x, bottomRight.x));
  double yScale = fabs(getLinInterCoef(endYMark, startYMark, topLeft.y, bottomRight.y));

  OdTvPoint zeroPoint(topLeft.x + fabs(startXMark) * xScale, topLeft.y - fabs(startYMark) * yScale, 0.);

  double x = start;
  double y = func(x);
  OdTvPoint prevPoint = zeroPoint + OdTvVector(x*xScale, y*yScale, 0.);

  for (OdUInt32 i = 0; i < nDiv; i++)
  {
    x += (fabs(start - end) / nDiv);
    y = func(x);
    OdTvPoint curPoint = zeroPoint + OdTvVector(x*xScale, y*yScale, 0.);
    pGraphEntity->appendPolyline(prevPoint, curPoint);

    prevPoint = curPoint;
  }
}

void OdTvVisualizeSampleModelsUtils::append2dGraphAxis(OdTvEntityPtr pGraphEntity, double startXMark, double endXMark, double startYMark, double endYMark, OdUInt32 xNum, OdUInt32 yNum, const OdTvPoint& topLeft, const OdTvPoint& bottomRight)
{
  // Draw X axis
  drawAxis(pGraphEntity, startXMark, endXMark, xNum, topLeft, bottomRight, &OdTvVisualizeSampleModelsUtils::fillPointsForX, &OdTvVisualizeSampleModelsUtils::updatePointForX);
  
  // Draw Y axis
  drawAxis(pGraphEntity, startYMark, endYMark, yNum, topLeft, bottomRight, &OdTvVisualizeSampleModelsUtils::fillPointsForY, &OdTvVisualizeSampleModelsUtils::updatePointForY);
}

void OdTvVisualizeSampleModelsUtils::appendColoredLegend(OdTvDatabaseId& databaseId, OdTvEntityPtr pEntity, OdString title, double x0, double y0, double x1, double y1, double max, double min, int nDiv)
{
  OdTvPointArray vertices;
  OdInt32Array faces;
  OdTvRGBColorDefArray colors;
  OdUInt8 r, g, b;

  // generate text style
  OdTvDatabasePtr pTvDb = databaseId.openObject();
  OdTvTextStyleId textStyleId = pTvDb->createTextStyle(OD_T("kMiddleRight"));
  {
    OdTvTextStylePtr pTextStyle = textStyleId.openObject(OdTv::kForWrite);

    pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleRight);
    pTextStyle->setTextSize(0.02);
  }
  pEntity->setTextStyle(textStyleId);

  vertices.resize((nDiv + 1) * 2);
  colors.resize((nDiv + 1) * 2);
  faces.resize(nDiv * 5);

  int iVertInd = 0;

  double yCur = y0;
  double dy = (y1 - y0) / double(nDiv);

  double curVal = min;
  double dVal = (max - min) / double(nDiv);

  // add first two vertices
  getColorByValue(y0, y1, yCur, &r, &g, &b);
  colors[iVertInd].setColor(r, g, b);
  vertices[iVertInd++] = OdTvPoint(x0, yCur, 0.);

  getColorByValue(y0, y1, yCur, &r, &g, &b);
  colors[iVertInd].setColor(r, g, b);
  vertices[iVertInd++] = OdTvPoint(x1, yCur, 0.);

  //append text
  pEntity->appendText(OdTvPoint(x0 - 0.01, yCur, 0.), OdString().format(OD_T("%.1f"), curVal));

  int iFacesInfoArrayInd = 0;
  for (OdInt32 i = 0; i < nDiv; i++)
  {
    yCur += dy;
    curVal += dVal;

    getColorByValue(y0, y1, yCur, &r, &g, &b);
    colors[iVertInd].setColor(r, g, b);
    vertices[iVertInd++] = OdTvPoint(x0, yCur, 0.);

    getColorByValue(y0, y1, yCur, &r, &g, &b);
    colors[iVertInd].setColor(r, g, b);
    vertices[iVertInd++] = OdTvPoint(x1, yCur, 0.);

    //append text
    pEntity->appendText(OdTvPoint(x0 - 0.01, yCur, 0.), OdString().format(OD_T("%.1f"), curVal));

    faces[iFacesInfoArrayInd++] = 4;
    faces[iFacesInfoArrayInd++] = iVertInd - 4;
    faces[iFacesInfoArrayInd++] = iVertInd - 3;
    faces[iFacesInfoArrayInd++] = iVertInd - 1;
    faces[iFacesInfoArrayInd++] = iVertInd - 2;
  }

  //append title
  pEntity->appendText(OdTvPoint(x0, y1 + 0.07, 0.), title);

  // create shell
  OdTvGeometryDataId shellId = pEntity->appendShell(vertices, faces);

  OdTvShellDataPtr pShell = shellId.openAsShell();
  pShell->setVertexColorsViaRange(0, colors);
  pShell->setDisableLighting(true);

  return;
}

void OdTvVisualizeSampleModelsUtils::appendSampleColoredCylinder(OdTvEntityPtr pEntity, double zMin, double zMax, double rad, double max, double min)
{
  OdTvPointArray vertices;
  OdInt32Array faces;
  OdTvRGBColorDefArray colors;
  OdUInt8 r, g, b;

  OdUInt32 nDivZ = 150, nDivQ = 50;

  vertices.resize((nDivZ + 1) * nDivQ);
  colors.resize((nDivZ + 1) * nDivQ);
  faces.resize((nDivZ * nDivQ) * 5 + 2 * (nDivQ + 1));

  double TempMid = (max + min) / 2.;
  int iVertInd = 0;
  int iFacesInfoArrayInd = 0;

  double zCur = zMin;
  double dz = (zMax - zMin) / double(nDivZ);
  double dq = 2 * OdaPI / double(nDivQ);
  double zLeft = zMin + (zMax - zMin) / double(3);
  double zRight = zMax - (zMax - zMin) / double(3);

  for (OdUInt32 i = 0; i < nDivZ + 1; i++)
  {
    double qCur = 0.;

    for (OdUInt32 j = 0; j < nDivQ; j++)
    {
      double dT = getTempGradientFromZ(zCur, zLeft, zRight, 5.);

      double TempCur = TempMid + dT * cos(qCur + OdaPI4);
      //get color for the vertex
      getColorByValue(min, max, TempCur, &r, &g, &b);
      colors[iVertInd].setColor(r, g, b);

      //set vertex
      vertices[iVertInd++] = OdTvPoint(rad*cos(qCur), rad*sin(qCur), zCur);
      qCur += dq;
    }

    int iStartVertInd_prev = iVertInd - 2 * (nDivQ);
    int iStartVertInd = iVertInd - nDivQ;
    if (i > 0)
    {
      for (OdUInt32 j = 0; j < nDivQ - 1; j++)
      {
        faces[iFacesInfoArrayInd++] = 4;
        faces[iFacesInfoArrayInd++] = iStartVertInd_prev + j;
        faces[iFacesInfoArrayInd++] = iStartVertInd_prev + j + 1;
        faces[iFacesInfoArrayInd++] = iStartVertInd + j + 1;
        faces[iFacesInfoArrayInd++] = iStartVertInd + j;
      }

      //add last face
      faces[iFacesInfoArrayInd++] = 4;
      faces[iFacesInfoArrayInd++] = iStartVertInd_prev + nDivQ - 1;
      faces[iFacesInfoArrayInd++] = iStartVertInd_prev;
      faces[iFacesInfoArrayInd++] = iStartVertInd;
      faces[iFacesInfoArrayInd++] = iStartVertInd + nDivQ - 1;
    }
    zCur += dz;
  }

  //add caps faces
  faces[iFacesInfoArrayInd++] = nDivQ;
  for (OdUInt32 j = 0; j < nDivQ; j++)
  {
    faces[iFacesInfoArrayInd++] = j;
  }

  faces[iFacesInfoArrayInd++] = nDivQ;
  for (OdUInt32 j = 0; j < nDivQ; j++)
  {
    faces[iFacesInfoArrayInd++] = vertices.size() - nDivQ + j;
  }

  // create shell
  OdTvGeometryDataId shellId = pEntity->appendShell(vertices, faces);

  OdTvShellDataPtr pShell = shellId.openAsShell();
  pShell->setVertexColorsViaRange(0, colors);
  pShell->setDisableLighting(true);

  //add transformation matrix for the good initial view
  OdTvMatrix matr;
  OdGeMatrix3d rotationMatX;
  rotationMatX.setToRotation(OdaPI4, OdGeVector3d::kXAxis);
  OdGeMatrix3d rotationMatY;
  rotationMatY.setToRotation(-OdaPI4, OdGeVector3d::kYAxis);
  OdGeMatrix3d rotationMatZ;
  rotationMatZ.setToRotation(OdaPI2, OdGeVector3d::kZAxis);
  matr = rotationMatX * rotationMatY * rotationMatZ;

  shellId.openObject()->setModelingMatrix(matr);

  return;
}

OdTvLayerId OdTvVisualizeSampleModelsUtils::generateLayer(const OdTvDatabaseId& databaseId, const OdString& name, const OdTvColorDef& color, OdInt8 lw, const OdTvLinetypeId& linetypeId, const OdString& description, bool bVisible)
{
  OdTvDatabasePtr pDb = databaseId.openObject(OdTv::kForWrite);

  OdTvLayerId layerId = pDb->createLayer(name);
  OdTvLayerPtr layerPtr = layerId.openObject(OdTv::kForWrite);
  layerPtr->setColor(color);
  layerPtr->setLineWeight(lw);
  if (!linetypeId.isNull())
  {
    OdTvLinetypeDef linetypeDef = OdTvLinetypeDef(linetypeId);
    layerPtr->setLinetype(linetypeDef);
  }
  layerPtr->setDescription(description);
  layerPtr->setVisible(bVisible);
  return layerId;
}

void OdTvVisualizeSampleModelsUtils::generateMeshVertices(double x, double y, OdTvPointArray& points)
{
  points.append(OdTvPoint(x - 0.1, y - 0.1, 0.01));
  points.append(OdTvPoint(x + 0., y - 0.1, 0.));
  points.append(OdTvPoint(x + 0.1, y - 0.1, -0.01));
  points.append(OdTvPoint(x + 0.2, y - 0.1, 0.));

  points.append(OdTvPoint(x - 0.1, y, 0.));
  points.append(OdTvPoint(x + 0., y, 0.));
  points.append(OdTvPoint(x + 0.1, y, -0.01));
  points.append(OdTvPoint(x + 0.2, y, -0.01));

  points.append(OdTvPoint(x - 0.1, y + 0.1, -0.01));
  points.append(OdTvPoint(x + 0., y + 0.1, -0.01));
  points.append(OdTvPoint(x + 0.1, y + 0.1, 0.));
  points.append(OdTvPoint(x + 0.2, y + 0.1, 0.));
}

void OdTvVisualizeSampleModelsUtils::generateMeshEditVertices(double x, double y, OdTvPointArray& points)
{
  points.append(OdTvPoint(x + 0., y, 0.1));
  points.append(OdTvPoint(x + 0.1, y, 0.1));

  points.append(OdTvPoint(x + 0., y + 0.1, 0.1));
  points.append(OdTvPoint(x + 0.1, y + 0.1, 0.1));
}

OdString OdTvVisualizeSampleModelsUtils::formatPath(const OdString& strResourceFolder, const OdString& filename)
{
  OdString path;
  path.format(L"%ls\\%ls", strResourceFolder.c_str(), filename.c_str());
#if defined(ODA_WINDOWS)
  path.replace('/', '\\');
  path.replace(L"\\\\", L"\\");
#else
  path.replace('\\', '/');
  path.replace(L"//", L"/");
#endif

  return path;
}

void OdTvVisualizeSampleModelsUtils::generateBlade(OdTvPointArray& bladeVertices0, OdTvPointArray& bladeVertices1, OdInt32Array& bladeFaces, OdTvPoint2dArray& bladeVerticesCoords, double x, double y)
{
  bladeVertices0.append(OdTvPoint(x - 0.025, y, 0.)); // 0
  bladeVertices0.append(OdTvPoint(x - 0.025, y - 1., 0.)); // 1
  bladeVertices0.append(OdTvPoint(x, y - 1., 0.005)); // 2
  bladeVertices0.append(OdTvPoint(x, y, 0.005)); // 3
  bladeVertices0.append(OdTvPoint(x + 0.025, y - 1., 0.)); // 4
  bladeVertices0.append(OdTvPoint(x + 0.025, y, 0.)); // 5
  bladeVertices0.append(OdTvPoint(x, y - 1.04, 0)); // 6

  bladeVertices1.append(OdTvPoint(x - 0.025, y, 0.)); // 0
  bladeVertices1.append(OdTvPoint(x - 0.025, y - 1., 0.)); // 1
  bladeVertices1.append(OdTvPoint(x, y - 1., -0.005)); // 2
  bladeVertices1.append(OdTvPoint(x, y, -0.005)); // 3
  bladeVertices1.append(OdTvPoint(x + 0.025, y - 1., 0.)); // 4
  bladeVertices1.append(OdTvPoint(x + 0.025, y, 0.)); // 5
  bladeVertices1.append(OdTvPoint(x, y - 1.04, 0)); // 6


  bladeFaces.append(4);
  bladeFaces.append(0);
  bladeFaces.append(1);
  bladeFaces.append(2);
  bladeFaces.append(3);

  bladeFaces.append(3);
  bladeFaces.append(1);
  bladeFaces.append(6);
  bladeFaces.append(2);

  bladeFaces.append(4);
  bladeFaces.append(3);
  bladeFaces.append(2);
  bladeFaces.append(4);
  bladeFaces.append(5);

  bladeFaces.append(3);
  bladeFaces.append(2);
  bladeFaces.append(6);
  bladeFaces.append(4);


  bladeVerticesCoords.append(OdTvPoint2d(0., 0.));
  bladeVerticesCoords.append(OdTvPoint2d(0., 0.97));
  bladeVerticesCoords.append(OdTvPoint2d(0.5, 0.97));
  bladeVerticesCoords.append(OdTvPoint2d(0.5, 0.));
  bladeVerticesCoords.append(OdTvPoint2d(1., 0.97));
  bladeVerticesCoords.append(OdTvPoint2d(1., 0.));
  bladeVerticesCoords.append(OdTvPoint2d(0.5, 1.));
}

void OdTvVisualizeSampleModelsUtils::generateGuard(OdTvPointArray& guardVertices, OdInt32Array& guardFaces, double x, double y)
{
  guardVertices.append(OdTvPoint(x - 0.08, y, -0.01)); // 0
  guardVertices.append(OdTvPoint(x + 0.08, y, -0.01)); // 1
  guardVertices.append(OdTvPoint(x + 0.08, y, 0.01)); // 2
  guardVertices.append(OdTvPoint(x - 0.08, y, 0.01)); // 3

  guardVertices.append(OdTvPoint(x - 0.08, y - 0.03, -0.01)); // 4
  guardVertices.append(OdTvPoint(x + 0.08, y - 0.03, -0.01)); // 5
  guardVertices.append(OdTvPoint(x + 0.08, y - 0.03, 0.01)); // 6
  guardVertices.append(OdTvPoint(x - 0.08, y - 0.03, 0.01)); // 7

  //0
  guardFaces.append(4);
  guardFaces.append(0);
  guardFaces.append(1);
  guardFaces.append(2);
  guardFaces.append(3);
  //1
  guardFaces.append(4);
  guardFaces.append(0);
  guardFaces.append(3);
  guardFaces.append(7);
  guardFaces.append(4);
  //2
  guardFaces.append(4);
  guardFaces.append(3);
  guardFaces.append(2);
  guardFaces.append(6);
  guardFaces.append(7);
  //3
  guardFaces.append(4);
  guardFaces.append(2);
  guardFaces.append(1);
  guardFaces.append(5);
  guardFaces.append(6);
  //4
  guardFaces.append(4);
  guardFaces.append(0);
  guardFaces.append(4);
  guardFaces.append(5);
  guardFaces.append(1);
  //5
  guardFaces.append(4);
  guardFaces.append(4);
  guardFaces.append(7);
  guardFaces.append(6);
  guardFaces.append(5);
}

void OdTvVisualizeSampleModelsUtils::generateHandle(OdTvPointArray& handleVertices, OdInt32Array& handleFaces, OdTvPoint2dArray& handleVerticesCoords, double x, double y)
{
  handleVertices.append(OdTvPoint(x - 0.023, y, -0.009)); // 0
  handleVertices.append(OdTvPoint(x + 0.023, y, -0.009)); // 1
  handleVertices.append(OdTvPoint(x + 0.023, y, 0.009)); // 2
  handleVertices.append(OdTvPoint(x - 0.023, y, 0.009)); // 3

  handleVertices.append(OdTvPoint(x - 0.021, y + 0.14, -0.008)); // 4
  handleVertices.append(OdTvPoint(x + 0.021, y + 0.14, -0.008)); // 5
  handleVertices.append(OdTvPoint(x + 0.021, y + 0.14, 0.008)); // 6
  handleVertices.append(OdTvPoint(x - 0.021, y + 0.14, 0.008)); // 7

  handleFaces.append(4);//0
  handleFaces.append(0);
  handleFaces.append(1);
  handleFaces.append(2);
  handleFaces.append(3);
  handleFaces.append(4);//1
  handleFaces.append(0);
  handleFaces.append(1);
  handleFaces.append(5);
  handleFaces.append(4);
  handleFaces.append(4);//2
  handleFaces.append(1);
  handleFaces.append(2);
  handleFaces.append(6);
  handleFaces.append(5);
  handleFaces.append(4);//3
  handleFaces.append(2);
  handleFaces.append(3);
  handleFaces.append(7);
  handleFaces.append(6);
  handleFaces.append(4);//4
  handleFaces.append(0);
  handleFaces.append(3);
  handleFaces.append(7);
  handleFaces.append(4);
  handleFaces.append(4);//5
  handleFaces.append(4);
  handleFaces.append(5);
  handleFaces.append(6);
  handleFaces.append(7);

  handleVerticesCoords.append(OdTvPoint2d(0.1, 0.1));
  handleVerticesCoords.append(OdTvPoint2d(0.9, 0.1));
  handleVerticesCoords.append(OdTvPoint2d(0.9, 0.9));
  handleVerticesCoords.append(OdTvPoint2d(0.1, 0.9));
  handleVerticesCoords.append(OdTvPoint2d(0, 0));
  handleVerticesCoords.append(OdTvPoint2d(1, 0));
  handleVerticesCoords.append(OdTvPoint2d(1, 1));
  handleVerticesCoords.append(OdTvPoint2d(0, 1));
}

void OdTvVisualizeSampleModelsUtils::generateBox(OdTvPointArray& vertices, OdInt32Array& faceList, double x, double y, double z)
{
  vertices.append(OdTvPoint(x - 0.9, y - 0.2, z - 0.9));
  vertices.append(OdTvPoint(x + 0.9, y - 0.2, z - 0.9));
  vertices.append(OdTvPoint(x + 0.9, y + 1.6, z - 0.9));
  vertices.append(OdTvPoint(x - 0.9, y + 1.6, z - 0.9));
  vertices.append(OdTvPoint(x - 0.9, y - 0.2, z + 0.9));
  vertices.append(OdTvPoint(x + 0.9, y - 0.2, z + 0.9));
  vertices.append(OdTvPoint(x + 0.9, y + 1.6, z + 0.9));
  vertices.append(OdTvPoint(x - 0.9, y + 1.6, z + 0.9));

  faceList.append(4);//0
  faceList.append(0);
  faceList.append(1);
  faceList.append(2);
  faceList.append(3);
  faceList.append(4);//1
  faceList.append(0);
  faceList.append(1);
  faceList.append(5);
  faceList.append(4);
  faceList.append(4);//2
  faceList.append(1);
  faceList.append(2);
  faceList.append(6);
  faceList.append(5);
  faceList.append(4);//3
  faceList.append(2);
  faceList.append(3);
  faceList.append(7);
  faceList.append(6);
  faceList.append(4);//4
  faceList.append(0);
  faceList.append(3);
  faceList.append(7);
  faceList.append(4);
  faceList.append(4);//5
  faceList.append(4);
  faceList.append(5);
  faceList.append(6);
  faceList.append(7);
}
