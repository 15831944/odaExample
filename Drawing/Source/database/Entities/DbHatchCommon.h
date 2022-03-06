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

// DbHatchCommon.h
// common parts of loading, rendering, and roundtrip data processing

// They are not in DbHatchImpl.h because changing DbHatchImpl.h forces
// too many files to recompile (DbFactories, DbClasses, etc)

#ifndef __OD_DB_HATCH_COMMON__
#define __OD_DB_HATCH_COMMON__

#include "DbHatchImpl.h"

inline short dxfNumberCurve(OdGeCurve2d* seg)
{
  switch(seg->type())
  {
  case OdGe::kCircArc2d:
    return 2;
    break;
  case OdGe::kEllipArc2d:
    return 3;
    break;
  case OdGe::kLineSeg2d:
    return 1;
    break;
  case OdGe::kNurbCurve2d:
    return 4;
    break;
  default:break;
  }
  ODA_FAIL();
  return -1;
}

// This inline method is optimized for evaluating (big amount of calls)
// 'int' type used to speed calls
inline OdCmEntityColor evaluateGradientColorAt(double value, 
                                               int r1, int g1, int b1, 
                                               int r2, int g2, int b2)
{
  OdCmEntityColor color;
  color.setRed  ((OdUInt8)OdRound((1.0-value)*r1 + value*r2));
  color.setGreen((OdUInt8)OdRound((1.0-value)*g1 + value*g2));
  color.setBlue ((OdUInt8)OdRound((1.0-value)*b1 + value*b2));
  return color;
}//TODO GeHatch.cpp has same function. Make one impl.

// because it is need in both DbHatchRoundtrip.cpp and DbHatchRender.cpp
inline void getLoopPts(const OdDbHatchImpl::Loop& loop, OdGePoint2dArray& pts, double tol = 0.0)
{
  if(loop.isPolyline())
  {
    OdGeInterval intvl;
    loop.m_Boundaries.pPolyline->getInterval(intvl);
    loop.m_Boundaries.pPolyline->appendSamplePoints(intvl.lowerBound(), intvl.upperBound(), tol, pts);
  }
  else
  {
    for(EdgeArray::iterator pEdg = loop.m_Boundaries.pSegments->begin(); pEdg != 
      loop.m_Boundaries.pSegments->end(); ++ pEdg)
    {
      OdGeInterval intvl;
      (*pEdg)->getInterval(intvl);
      (*pEdg)->appendSamplePoints(intvl.lowerBound(), intvl.upperBound(), tol, pts);
    }
  }
}

#endif // __OD_DB_HATCH_COMMON__
