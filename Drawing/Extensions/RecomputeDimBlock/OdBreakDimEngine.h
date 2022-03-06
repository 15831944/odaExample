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

#ifndef __OD_BREAK_DIM_ENGINE__
#define __OD_BREAK_DIM_ENGINE__

#include "TD_PackPush.h"
#include "DbEntity.h"
#include "DbBreakData.h"
#include "Ge/GeCircArc3d.h"
#include "Ge/GeLineSeg3d.h"

/** \details
  Library: Source provided.
  <group RecomputeDimBlock_Classes> 
*/
struct BreakPointData
{
  enum TypeBreakPoint
  {
    BREAK_POINT    = 1,
    BREAK_TEXT     = 2,
    BREAK_STATIC   = 3,
  };

  TypeBreakPoint m_Type;
  OdGePoint3d m_Point;
  OdGePoint3d m_Point2;
  double m_Distance;
  double m_Angle;
  double m_Angle2;
  BreakPointData() 
  : m_Type(TypeBreakPoint::BREAK_POINT)
  , m_Distance(0.0)
  , m_Angle(0.0)
  , m_Angle2(0.0)
  {}
};

/** \details
  Library: Source provided.
  <group RecomputeDimBlock_Classes> 
*/
class OdBreakDimEngine
{
  double m_BreakSize;
  OdGeMatrix3d m_Matrix;
  OdGeTol m_tol;

  OdDbEntityPtr m_curEntity;
  OdArray<BreakPointData> m_BreakPoints;

  void addBreakPoint(BreakPointData brData);
  bool breakDimensionLine();
  double breakAngle(double radius);

  int getIntersectionPoints(const OdGeCircArc3d* arc, const OdGePoint3dArray& boundingPoints, OdGePoint3d& p1, OdGePoint3d& p2);
  int getIntersectionPoints(const OdGeLine3d* line, const OdGePoint3dArray& boundingPoints, OdGePoint3d& p1, OdGePoint3d& p2);

  void intersectWithGeLine(OdGeLineSeg3d* lineSeg, OdGeCurve3d* geCurveBrkDim);

  void collectBreakPoints(const OdDbEntity* pLine, const OdDbBreakPointRefPtrArray& pntRefArray);
  void breakBy2StaticPoint(const OdDbEntity* pEnt, OdGePoint3d point1, OdGePoint3d point2, OdInt32 index);
  void intersectWithArc(const OdDbEntity* pArc, OdGeCurve3d* geCurveBrkDim);
  void intersectWithLine(const OdDbEntity* pLine, OdGeCurve3d* geCurveBrkDim);
  void intersectWithText(const OdDbEntity* pText, OdGeCurve3d* geCurveBrkDim);
  void intersectWithPolyline(const OdDbEntity* pPolyline, OdGeCurve3d* geCurveBrkDim);
  void intersectWith2DPolyline (const OdDbEntity* p2DPolyline, OdGeCurve3d* geCurveBrkDim);
  void intersectWithEllipse (const OdDbEntity* pText, OdGeCurve3d* geCurveBrkDim);
  void intersectWithSpline(const OdDbEntity* pEllipse, OdGeCurve3d* geCurveBrkDim);
  void intersectWithLeader(const OdDbEntity* pLeader, OdGeCurve3d* geCurveBrkDim);
  void intersectWithDimension(const OdDbEntity* pDimension, OdGeCurve3d* geCurveBrkDim);
  void intersectWithBlock(const OdDbEntity* pBlock, OdGeCurve3d* geCurveBrkDim);
  void intersectWithMLeader(const OdDbEntity* pBlock, OdGeCurve3d* geCurveBrkDim);

public:

  OdBreakDimEngine(double breakSize)
  {
    m_BreakSize = breakSize/2.0;
  }
  ~OdBreakDimEngine(){}

  void setDimensionEnts(OdArray<OdDbEntityPtr>& ents, OdGeMatrix3d matr);
  void breakDimension(OdDbBreakDataPtr brData);

  OdArray<OdDbEntityPtr> m_DimEnts;
  OdArray<OdDbEntityPtr> m_newDimEnts;
};

#include "TD_PackPop.h"

#endif //__OD_BREAK_DIM_ENGINE__
