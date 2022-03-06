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

#include "RailProfileDef.h"
#include <math.h>

namespace 
{
  // Use some other external PI for geometry representation
  const double pi = std::acos(-1.0);
}



RailProfileDef::RailProfileDef(double scaleFactor)
{
  lengthBase1 = 384 * scaleFactor;
  lengthBase2 = 28 * scaleFactor;
  lengthBase3 = 78 * scaleFactor;
  lengthBase4 = 94 * scaleFactor;

  angleBase1 = 17;
  angleBase2 = 56;

  // web parameters:
  lengthWeb1 = -1 * scaleFactor;
  lengthWeb2 = 217 * scaleFactor;

  // head parameters:
  lengthHead1 = 111 * scaleFactor;
  lengthHead2 = 119 * scaleFactor;
  lengthHead3 = 88 * scaleFactor;

  angleHead1 = 10;
  angleHead2 = 51;
}

void RailProfileDef::buildPoints(std::vector<PointF>& collection)
{
  double centerX = lengthBase1 / 2;
  PointF current{ 0, 0 };
  
  collection.push_back(current);

  // LB1
  current = PointF{ current.X + lengthBase1, current.Y + 0 };
  collection.push_back(current);

  // LB2 right
  current = PointF{ current.X + 0, current.Y + lengthBase2 };
  collection.push_back(current);

  // LB3 right
  auto angle = pi * (180 - angleBase1) / 360.0;
  current = PointF{ current.X - lengthBase3 * (float)std::sin(angle),
                       current.Y + lengthBase3 * (float)std::cos(angle) };
  collection.push_back(current);

  // LB4 right
  angle = pi * (180 - angleBase2) / 360.0;
  current = PointF { current.X - lengthBase4 * (float)std::sin(angle),
                       current.Y + lengthBase4 * (float)std::cos(angle) };
  collection.push_back(current);

  // LW2 right
  current = PointF { current.X + 0, current.Y + lengthWeb2 };
  collection.push_back(current);

  // LH3 right
  angle = pi * (180 - angleHead2) / 360.0;
  current = PointF { current.X + lengthHead3 * (float)std::sin(angle),
    current.Y + lengthHead3 * (float)std::cos(angle) };
  collection.push_back(current);

  // LH1 right
  angle = pi * (180 - angleHead1) / 360.0;
  current = PointF { current.X - lengthHead1 * (float)std::cos(angle), 
    current.Y + lengthHead1 * (float)std::sin(angle) };
  collection.push_back(current);

  // LH2 center
  current = PointF { lengthBase1 - current.X, current.Y + 0 };
  collection.push_back(current);

  // LH1 left
  angle = pi * (180 - angleHead1) / 360.0;
  current = PointF { current.X - lengthHead1 * (float)std::cos(angle), 
    current.Y - lengthHead1 * (float)std::sin(angle) };
  collection.push_back(current);

  // LH3 left
  angle = pi * (180 - angleHead2) / 360.0;
  current = PointF { current.X + lengthHead3 * (float)std::sin(angle), 
    current.Y - lengthHead3 * (float)std::cos(angle) };
  collection.push_back(current);

  // LW2 left
  current = PointF { current.X + 0, current.Y - lengthWeb2 };
  collection.push_back(current);

  // LB4 left
  angle = pi * (180 - angleBase2) / 360.0;
  current = PointF { current.X - lengthBase4 * (float)std::sin(angle), 
    current.Y - lengthBase4 * (float)std::cos(angle) };
  collection.push_back(current);

  // LB3 left
  angle = pi * (180 - angleBase1) / 360.0;
  current = PointF { current.X - lengthBase3 * (float)std::sin(angle), 
    current.Y - lengthBase3 * (float)std::cos(angle) };
  collection.push_back(current);

  // LB2 left
  current = PointF { current.X + 0, current.Y - lengthBase2 };
  collection.push_back(current);
}

bool RailProfileDef::buildProfile(SdaiModel model, SdaiAppInstance profileDefinition)
{
  std::vector<PointF> pointsCollection;
  buildPoints(pointsCollection);

  if (pointsCollection.empty())
  {
    return false;
  }

  SdaiAppInstance polyLine = sdaiCreateInstanceBN(model, "IFCPOLYLINE");

  if (!polyLine)
  {
    return false;
  }

  SdaiAggr   primitiveIdCollection = nullptr;
  sdaiCreateAggrBN(polyLine, "points");
  sdaiGetAttrBN(polyLine, "points", sdaiAGGR, &primitiveIdCollection);

  if (!primitiveIdCollection)
  {
    return false;
  }

  int insertIndex = 0;

  for (auto& point : pointsCollection)
  {
    SdaiAppInstance pointInstance = sdaiCreateInstanceBN(model, "IFCCARTESIANPOINT");
    if (!pointInstance)
    {
      return false;
    }

    sdaiCreateAggrBN(pointInstance, "coordinates");

    SdaiAggr  coordinateAggr = nullptr;
    sdaiGetAttrBN(pointInstance, "coordinates", sdaiAGGR, &coordinateAggr);

    if (!coordinateAggr)
    {
      return false;
    }

    sdaiPutAggrByIndex(coordinateAggr, 0, sdaiREAL, point.X);
    sdaiPutAggrByIndex(coordinateAggr, 1, sdaiREAL, point.Y);

    sdaiPutAggrByIndex(primitiveIdCollection, insertIndex, sdaiINSTANCE, pointInstance);
    ++insertIndex;
  }

  sdaiPutAttrBN(profileDefinition, "outercurve", sdaiINSTANCE, polyLine);

  return true;
}
