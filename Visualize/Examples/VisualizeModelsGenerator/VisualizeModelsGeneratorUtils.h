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

#ifndef VISUALIZEMODELSGENERATORUTILS_H
#define VISUALIZEMODELSGENERATORUTILS_H

// Visualize SDK
#include "TvFactory.h"

class OdTvVisualizeSampleModelsUtils
{
public:

  static OdTvGeometryDataId appendRectangle(OdTvEntityPtr entity, double x0, double y0, double x1, double y1, double z = 0.0f, bool bFill = false, bool bForcePolygon = false);

  static void generatePointsOnCircle(OdGePoint3dArray& pts, OdGePoint3d& center, double radius, int axis);

  static double getLinInterCoef(double x1, double x0, double y1, double y0);
  
  static double mediana(double a, double b);

  static OdTvLinetypeId generateCustomLineTypeWithText(OdTvDatabaseId databaseId);

  static void append3dPlot(OdTvEntityPtr pGraphEntity, double startX, double endX, double startY, double endY, double startXMark, double startYMark, double startZMark, double endXMark, double endYMark,
                           double endZMark, OdUInt32 nDiv, const OdTvPoint& pointXYZ, const OdTvPoint& pointXY, const OdTvPoint& pointXZ, double(*funct)(double, double));

  static void appendGridLines(OdTvEntityPtr pModelRootEntity, bool bBig, OdUInt32 nColumns, OdUInt32 nRows, double startX, double startY, double xLenth, double yLenth);

  static void append2dPlot(OdTvEntityPtr pGraphEntity, double start, double end, double startXMark, double startYMark, double endXMark,
                           double endYMark, OdUInt32 nDiv, const OdTvPoint& topLeft, const OdTvPoint& bottomRight, double(*func)(double));

  static void append2dGraphAxis(OdTvEntityPtr pGraphEntity, double startXMark, double endXMark, double startYMark, double endYMark, OdUInt32 xNum, OdUInt32 yNum,
                                const OdTvPoint& topLeft, const OdTvPoint& bottomRight);

  static void appendColoredLegend(OdTvDatabaseId& databaseId, OdTvEntityPtr entity, OdString title, double x0, double y0, double x1, double y1, double max, double min, int nDiv);
  
  static void appendSampleColoredCylinder(OdTvEntityPtr pEntity, double zMin, double zMax, double rad, double max, double min);

  static OdTvLayerId generateLayer(const OdTvDatabaseId& databaseId, const OdString& name, const OdTvColorDef& color, OdInt8 lw, const OdTvLinetypeId& linetypeId, const OdString& description, bool bVisible);

  static void generateMeshVertices(double x, double y, OdTvPointArray& points);

  static void generateMeshEditVertices(double x, double y, OdTvPointArray& points);

  static OdString formatPath(const OdString& strResourceFolder, const OdString& filename);

  // methods for materials samples

  static void generateBlade(OdTvPointArray& bladeVertices0, OdTvPointArray& bladeVertices1, OdInt32Array& bladeFaces0, OdTvPoint2dArray& bladeVerticesCoords, double x, double y);

  static void generateGuard(OdTvPointArray& guardVertices, OdInt32Array& guardFaces, double x, double y);

  static void generateHandle(OdTvPointArray& handleVertices, OdInt32Array& handleFaces0, OdTvPoint2dArray& handleVerticesCoords, double x, double y);

  static void generateBox(OdTvPointArray& vertices, OdInt32Array& faceList, double x = 0., double y = 0., double z = 0.);

private:

  static void getColorByValue(double min, double max, double value, OdUInt8* r, OdUInt8* g, OdUInt8* b);
  
  static void generatePointOnCircle(OdGePoint3d& pt, OdGePoint3d& center, double radius, int axis, double angle);

  static void fillPointsForX(OdTvPoint& pointOne, OdTvPoint& pointTwo, OdTvPoint& pointThree, OdTvPoint& pointFour, OdTvPoint& pointFive, double& posStep, double& markStep, double& pos, OdUInt32 num, const OdTvPoint& topLeft, const OdTvPoint& bottomRight, double startMark, double endMark);
  static void fillPointsForY(OdTvPoint& pointOne, OdTvPoint& pointTwo, OdTvPoint& pointThree, OdTvPoint& pointFour, OdTvPoint& pointFive, double& posStep, double& markStep, double& pos, OdUInt32 num, const OdTvPoint& topLeft, const OdTvPoint& bottomRight, double startMark, double endMark);
  
  static OdTvPoint& updatePointForX(OdTvPoint& point, double value, bool bIsTextPoint);
  static OdTvPoint& updatePointForY(OdTvPoint& point, double value, bool bIsTextPoint);
  
  static void drawAxis(OdTvEntityPtr pGraphEntity, double startMark, double endMark, OdUInt32 num, const OdTvPoint& topLeft, const OdTvPoint& bottomRight,
                      void(*fillData) (OdTvPoint&, OdTvPoint&, OdTvPoint&, OdTvPoint&, OdTvPoint&, double&, double&, double&, OdUInt32, const OdTvPoint&, const OdTvPoint&, double, double),
                      OdTvPoint& (*updatePoint) (OdTvPoint&, double, bool));
  
  static double getTempGradientFromZ(double zCur, double zLeft, double zRight, double dTMax);
};

#endif //VISUALIZEMODELSGENERATORUTILS_H
