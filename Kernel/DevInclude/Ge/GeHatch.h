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

#ifndef OD_GEHATCH_H
#define OD_GEHATCH_H

#include "Ge/GeGbl.h"
#include "Ge/GeTol.h"
#include "Ge/GeDoubleArray.h"
#include "Int32Array.h"
#include "Ge/GeLineSeg2d.h"
#include "GePoint2dArrayArray.h"
#include "UInt8Array.h"
#include "CmEntityColorArray.h"
#include "Ge/GePoint3d.h"
#include "Ge/GePoint3dArray.h"
#include "Ge/GeLineSeg2dArray.h"
#include "HatchPattern.h"
#include "IntArray.h"
#include "Gi/GiGeometry.h"
#include "Ge/GeSegmentChain2d.h"
#include "DbBaseDatabase.h"

#define SKIP_RATIO 0.00035
#define POINTS_LIMIT 7500


enum GradientType
{
  GR_INVALID = 0,
  GR_SPHERE,
  GR_HEMISPHERE,
  GR_CURVED,
  GR_LINEAR,
  GR_CYLINDER
};


enum OdGeHatchLoopType
{
  OdGeHatchLoopType_Default          = 0,       // The loop type has yet to be specified.
  OdGeHatchLoopType_External         = 1,       // The loop is comprised of external entities. 
  OdGeHatchLoopType_Polyline         = 2,       // The loop is an OdGePolyline2d.
  OdGeHatchLoopType_Derived          = 4,       // The loop was derived from a picked point.
  OdGeHatchLoopType_Textbox          = 8,       // The loop is the box surrounding OdDbText.
  OdGeHatchLoopType_Outermost        = 0x10,    // The loop is the outermost loop.
  OdGeHatchLoopType_NotClosed        = 0x20,    // The loop is not closed.
  OdGeHatchLoopType_SelfIntersecting = 0x40,    // The loop is self-intersecting.
  OdGeHatchLoopType_TextIsland       = 0x80     // The loop is a OdGeHatchLoopType_Textbox that are 
                                                // surrounded by even number of outer loops, 
                                                // and is avoided when during solid fill.
};

struct GiLoop
{
  OdGiEdge2dArray m_edges;

  GiLoop(const OdGiEdge2dArray& edges, const OdUInt32 flags)
  {
    m_edges = edges;
    m_Flags = flags;
  }

  inline bool isPolyline() const
  {
    return GETBIT(m_Flags, OdDbBaseHatchPE::kPolyline);
  }
  inline bool isDerived() const
  {
    return GETBIT(m_Flags, OdDbBaseHatchPE::kDerived);
  }
  inline bool isTextBox() const
  {
    return GETBIT(m_Flags, OdDbBaseHatchPE::kTextbox);
  }
  inline bool isOuterMost() const
  {
    return GETBIT(m_Flags, OdDbBaseHatchPE::kOutermost);
  }
  inline bool isNotClosed() const
  {
    return GETBIT(m_Flags, OdDbBaseHatchPE::kNotClosed);
  }
  inline bool isDuplicate() const
  {
    return GETBIT(m_Flags, OdDbBaseHatchPE::kDuplicate);
  }
  inline bool isTextIsland() const
  {
    return GETBIT(m_Flags, OdDbBaseHatchPE::kTextIsland);
  }
  inline bool isAnnotative() const
  {
    return GETBIT(m_Flags, OdDbBaseHatchPE::kIsAnnotative);
  }
  inline OdUInt32 getFlags() const
  {
    return m_Flags;
  }
private:
  GiLoop() : m_Flags(0){};
  OdUInt32 m_Flags;
};

struct GE_TOOLKIT_EXPORT GiLoopListCustom
{//this struct using to get segments by fillSegmentLoopLtArrays for two loopList.
  //fillSegmentLoopLtArrays will call twice and second time segmentsArray will be continue to fill (we will get one big segment array from two loopList)
  const OdUInt32 startLoopNum;//startLoopNum == otherLoopList.size()
  const OdUInt32 countLoops;//mLoopList.size() + otherLoopList.size()
  OdArray<GiLoop> mLoopList;
  GiLoopListCustom(const OdUInt32 startLoopNumIn, const OdUInt32 countLoopsIn)
    : startLoopNum(startLoopNumIn), countLoops(countLoopsIn)
  {
    const OdUInt32 iReserve = countLoops - startLoopNum;
    mLoopList.reserve(iReserve > 0 ? iReserve : 0);
  }

  void appendLoop(const OdGiEdge2dArray& giEdgeArray, OdUInt32 flags)
  {
    mLoopList.push_back(GiLoop(giEdgeArray, flags));
  }
private:
  GiLoopListCustom();
};

// Indexes of segments, with which stroke intersects.
class OdGeStrokeData
{
public:
  OdGeStrokeData () : m_startNum(0), m_endNum(0) {}
  OdGeStrokeData (
    OdUInt32 startNum, 
    OdUInt32 endNum) : m_startNum(startNum), m_endNum(endNum) {}
  bool operator == (
    const OdGeStrokeData &sd) const
  {
    return m_startNum == sd.m_startNum && m_endNum == sd.m_endNum;
  }
  OdUInt32 m_startNum;
  OdUInt32 m_endNum;
};


// For comments see the file GeHatch.cpp
//DD:EXPORT_ON
class GE_TOOLKIT_EXPORT OdGeHatchStrokes
{
public:
  virtual double getNearestStroke (
    double prevEvent) const = 0;
  virtual double getNextStroke (
    double prevEvent) const = 0;
  virtual ~OdGeHatchStrokes() {}
};

class GE_TOOLKIT_EXPORT OdGeEqualStepHatchStrokes : public OdGeHatchStrokes
{
  double m_dZeroPoint;
  double m_dStep;
public:
  OdGeEqualStepHatchStrokes (
    double d0, 
    double step);
  virtual double getNearestStroke (
    double prevEvent) const ODRX_OVERRIDE;
  virtual double getNextStroke (
    double prevEvent) const ODRX_OVERRIDE;
};

class GE_TOOLKIT_EXPORT OdGeNonEqualStepHatchStrokes : public OdGeHatchStrokes
{
  double m_dZeroPoint;
  OdGeDoubleArray m_Positions;
  mutable int m_curPos;
public:
  OdGeNonEqualStepHatchStrokes (
    double d0, 
    const OdGeDoubleArray &Positions);
  virtual double getNearestStroke (
    double prevEvent) const ODRX_OVERRIDE;
  virtual double getNextStroke (
    double prevEvent) const ODRX_OVERRIDE;
};

/** Description:
    Library: Ge
    {group:Structs} 
*/
struct OdGeShellData
{
  OdGePoint3dArray     m_vertices;
  OdInt32Array         m_faces;
  OdUInt8Array         m_edgeVisibilities;
  OdCmEntityColorArray m_colors;
};

// 09.09.2004 GU
// pShell - is only for solid hatch

GE_TOOLKIT_EXPORT void 
OdGeDrawSegmentHatch (
    const OdArray<OdGeLineSeg2d>& segments, 
    const OdGeIntArray& loops, 
    const OdGeIntArray& loopTypes, 
    OdGeHatchStrokes *StrokeParams, OdGeIslandStyle iStyle, 
    bool isSolid, 
    OdArray<OdGeLineSeg2d> &strokes, 
    const OdGeTol& tol = 1.0e-10,
    OdArray<OdGeStrokeData>* pStrokeData = NULL, 
    OdGeShellData* pShell = NULL,
    bool bIncludeBoundary = false);

GE_TOOLKIT_EXPORT void 
OdGeDrawSegmentHatchXY (
                      const OdArray<OdGeLineSeg2d>& segments, 
                      const OdGeIntArray& loops, 
                      const OdGeIntArray& loopTypes, 
                      OdGeHatchStrokes *StrokeParams, OdGeIslandStyle iStyle, 
                      bool isSolid, 
                      OdArray<OdGeLineSeg2d> &strokes, 
                      const OdGeTol& tol = 1.0e-10,
                      OdArray<OdGeStrokeData>* pStrokeData = NULL, 
                      OdGeShellData* pShell = NULL);

// builds 2D shell. Looks which of the contours are contours and which
// of contours are holes and puts them just like GiGeometry's shell
// primitive - holes are strictly after its contour.

// Parameters:
// contours - [in]  array of input contours
// style    - [in]  holes detection style (0 - normal, 1 - outermost, 2 - ignore)
// vertixes - [out] shell's verts
// indexes  - [out] shell's face list
// tol      - [in]  tolerance
GE_TOOLKIT_EXPORT OdResult build2dShell (
  const OdGePoint2dArrayArray& contours, 
  OdInt16 style, 
  OdGePoint2dArray& vertixes, 
  OdInt32Array& indexes, 
  const OdGeTol& tol);

class OdGeHatchDashTaker
{
public:
  virtual bool dash(const OdGePoint2d& start, const OdGePoint2d& end) = 0;
  virtual void setShift(const OdGeVector2d& pShift) {};
  virtual void setDashPeriod(const bool value) {};
  virtual bool hasCache() const { return false; };
  virtual void setDeviation(const double deviation) {};
  virtual void setSmallerDashPeriod(const double dSmallerPeriod) {};
  
};

class DashTakerHatchImpl : public OdGeHatchDashTaker
{
  OdGePoint2d m_p1;
  OdGePoint2d m_p2;
  OdUInt32 m_maxHatchDensity;
  OdUInt32 currentDashCount;
  OdGeVector2d m_shift;
  double m_dDeviation;
  double m_dSmallerDashPeriod;
  bool m_hasDashPeriod;
  OdGePoint2dArray m_startPts;
  OdGePoint2dArray m_endPts;
public:
  DashTakerHatchImpl(const OdUInt32 maxHatchDensity)
    : m_dDeviation(0.)
    , m_dSmallerDashPeriod(0.)
    , m_hasDashPeriod(false)
    , currentDashCount(0)
    , m_maxHatchDensity(maxHatchDensity)
  {
  }
  void setDashPeriod(const bool value) ODRX_OVERRIDE
  {
    m_hasDashPeriod = value;
  }
  virtual void setShift(const OdGeVector2d& pShift) ODRX_OVERRIDE
  {
    m_shift = pShift;
  };
  virtual bool hasCache() const ODRX_OVERRIDE
  {
    return !m_startPts.isEmpty();
  }
  void setSmallerDashPeriod(const double dSmallerPeriod) ODRX_OVERRIDE
  {
    m_dSmallerDashPeriod = dSmallerPeriod;
  }

  bool dash(const OdGePoint2d& start, const OdGePoint2d& end) ODRX_OVERRIDE
  {
    if (++currentDashCount > m_maxHatchDensity)
      return false;
    if (!OdZero(m_dDeviation))
    {
      double len = start.distanceTo(end);
      if (!m_hasDashPeriod)
      {
        if (len <= m_dDeviation && !OdZero(len))
          return true;
      }
      else
      {
        if (len <= m_dSmallerDashPeriod && len <= m_dDeviation && !OdZero(len))
          return true;
      }
    }
    m_p1 = start + m_shift;
    m_p2 = end + m_shift;
    m_startPts.push_back(m_p1);
    m_endPts.push_back(m_p2);
    return true;
  }
  virtual void setDeviation(const double deviation) ODRX_OVERRIDE
  {
    m_dDeviation = deviation;
  }
  OdGeVector2d shift() const
  {
    return m_shift;
  }
  OdGePoint2dArray getStartPoints() const
  {
    return m_startPts;
  }
  OdGePoint2dArray getEndPoints() const
  {
    return m_endPts;
  }
};



GE_TOOLKIT_EXPORT OdResult odgeDrawDashedHatch(
  const OdHatchPattern& pattern,
  const OdGeLineSeg2dArray& segmentArray,
  const OdGeIntArray& loopArray,
  const OdGeIntArray& loopTypes,
  const OdGeTol& hatchTolerance,
  OdGeIslandStyle islandStyle,
  OdUInt32 maxHatchDensity,
  OdGeHatchDashTaker& dashTaker,
  const bool bCheckDense = true,
  bool bIncludeBoundary = false);

GE_TOOLKIT_EXPORT void fillSegmentLoopLtArrays(OdGeLineSeg2dArray& segmentArray, OdIntArray& loopArray, OdIntArray& loopTypes, const GiLoopListCustom& loopListCustom,
  const OdGeVector2d vOffset, const double dDeviation, const OdUInt32 pointLimit, const OdInt16 nHPSmooth, const bool bGradientFill, const bool bSolid,
  const bool isEvaluateHatchArea = false, const bool isRegionCreate = false);

GE_TOOLKIT_EXPORT bool processGradientHatch(OdSharedPtr<OdGeShellData>& pShell, const OdString& gradName, const double dShift, const double dAngle, int r1, int g1, int b1, int r2, int g2, int b2);

GE_TOOLKIT_EXPORT OdGeTol calculateEffectiveTolerance(const OdArray<OdGeLineSeg2d>& segments, double absTol, OdGeExtents2d& ext);

GE_TOOLKIT_EXPORT double calculateDashTakerDeviation(const OdGeExtents2d& ext, const double deviation);

GE_TOOLKIT_EXPORT bool checkDenstiy(const OdGeLineSeg2dArray& segmentArray, const OdIntArray& loopArray, const OdHatchPattern &hp, const OdGeExtents2d &ext,
                                    const OdUInt32 loopAmount, const OdUInt32 maxHatchDensity, const bool isMPolygon, bool &bHatchTooDense);

GE_TOOLKIT_EXPORT OdResult evaluateDashedHatch(const GiLoopListCustom& giLoopList,
                                               const OdHatchPattern& hatchPattern,
                                               const OdGeIslandStyle eHatchStyle,
                                               const double dViewRotation, const double dDeviation,
                                               const OdUInt32 loopAmount, const OdUInt32 pointLimit, const OdUInt32 maxHatchDensity, const OdUInt32 maxPointsToDraw, const OdInt16 nHPSmooth,
                                               const bool bSolidFill, const bool bGradientFill, const bool isEvaluateHatchArea, const bool isMPolygon, const bool isDBRO,
                                               bool& bHatchTooDense,
                                               OdGeHatchDashTaker* dashTaker,
                                               OdGeLineSeg2dArray& segmentArrayOut, OdIntArray& loopArrayOut, OdIntArray& loopTypesOut,
                                               OdGeExtents2d& ext2dOut,
                                               OdGeTol& tol);

//DD:EXPORT_OFF
#endif  /* OD_GEHATCH_H */
