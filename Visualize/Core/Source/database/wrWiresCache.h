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

#ifndef _WRWIRECACHE_H_
#define _WRWIRECACHE_H_

#include "OdArray.h"
#include "Ge/GeNurbCurve3d.h"
#include "Ge/GeCircArc3d.h"
#include "Ge/GeInterval.h"
#include "Ge/GeMatrix3d.h"
#include "Ge/GeCurve3dPtrArray.h"
#include "CmColor.h"

#define STL_USING_ALGORITHM
#define STL_USING_FUNCTIONAL
#include "OdaSTL.h"

/** Description:

    {group:BrepRenderer_Classes} 
*/
class wrWire
{
  public:
    struct setWireColor
    {
      OdCmEntityColor m_clr;

      setWireColor(OdCmEntityColor clr) : m_clr(clr) {}

      inline void operator ()(wrWire &wire) const
      {
        wire.color = m_clr;
      }
    };

  bool operator !=(const wrWire& wire) const
  {
    if (pTransform && wire.pTransform)
    {
      if (*pTransform != *wire.pTransform)
        return true;
    }

    if (pTransform || wire.pTransform)
      return true;

    return !(type == wire.type 
          && selMarker == wire.selMarker 
          && color == wire.color 
          && acisIndex == wire.acisIndex
          && points == wire.points);
  }     

  wrWire & operator = (const wrWire &wire)
  {
    if(&wire == this)
      return(*this);

    if (wire.pTransform)
    {
      pTransform = new Transform;
      *pTransform = *wire.pTransform;
    }
    else
      pTransform = NULL;

    type = wire.type;
    selMarker = wire.selMarker;
    color = wire.color;
    acisIndex = wire.acisIndex;
    points = wire.points;

    return (*this);
  }     

  enum
  {
    kUnInit = 0,
    kLine   = 1,
    kCircle = 2,
    kArc3pt = 3,
    kSpline = 4
  };
  OdUInt8           type;
  OdGsMarker        selMarker; // dwg format uses indexes -1,-2,-3... (not 0)
  OdCmEntityColor   color;
  OdInt32           acisIndex; // Used with kSpline type
  OdGePoint3dArray  points;    // Used with all but kSpline type

  wrWire()
    : type(kUnInit)
    , color(OdCmEntityColor::kNone)
    , acisIndex(-1)
    , pTransform(0)
    , selMarker(-1)
  {}

  wrWire(const wrWire &wire)
    : type(wire.type)
    , color(wire.color)
    , acisIndex(wire.acisIndex)
    , selMarker(wire.selMarker)
    , points(wire.points)
  {
    if (wire.pTransform)
    {
      pTransform = new Transform;
      *pTransform = *wire.pTransform;
    }
    else
      pTransform = NULL;
  }

  ~wrWire()
  {
    if (pTransform)
    {
      delete pTransform;
      pTransform = 0;
    }
  }

  void addTransform(const OdGeMatrix3d &xmat)
  {
    if (!pTransform)
      pTransform = new Transform;
    *pTransform = xmat;
  }

  class Transform
  {
  public:
    OdGeVector3d xAxis;
    OdGeVector3d yAxis;
    OdGeVector3d zAxis;
    OdGePoint3d translation;
    double       Scale;
    bool         HasRotation;
    bool         HasReflection;
    bool         HasShear;
    Transform()
      : Scale(1.)
      , HasRotation(false)
      , HasReflection(false)
      , HasShear(false)
    {}

    void operator =( const OdGeMatrix3d& xMat )
    {
      xMat.getCoordSystem(translation, xAxis, yAxis, zAxis);
      Scale = 1.;
      HasRotation = HasReflection = HasShear = false;
    }

    operator OdGeMatrix3d() const
    {
      OdGeMatrix3d xMat;
      xMat.setCoordSystem(translation, xAxis, yAxis, zAxis);
      return xMat;
    }
  
    bool operator !=(const Transform& tr) const
    {
      return (xAxis != tr.xAxis 
           || yAxis != tr.yAxis 
           || zAxis != tr.zAxis 
           || !OdEqual(Scale, tr.Scale) 
           || HasRotation != tr.HasRotation
           || HasReflection != tr.HasReflection
           || HasShear != tr.HasShear);
    }

  } *pTransform;

  void circle(const OdGePoint3d& center, double radius, const OdGeVector3d& normal)
  {
    OdGeCircArc3d ca(center, normal, radius);
    double t = Oda2PI / 3.;
    points.push_back(ca.evalPoint(-OdaPI));
    points.push_back(ca.evalPoint(-OdaPI + t));
    points.push_back(ca.evalPoint(-OdaPI + t + t));

    type = kCircle;
  }

  void circle(const OdGePoint3d& p1, const OdGePoint3d& p2, const OdGePoint3d& p3)
  {
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);

    type = kCircle;
  }

  void circularArc(const OdGePoint3d& center,
    double radius,
    const OdGeVector3d& normal,
    const OdGeVector3d& startVector,
    double sweepAngle)
  {
    OdGeCircArc3d ca(center, normal, startVector, radius, 0., sweepAngle);

    OdGeInterval i;
    ca.getInterval(i);

    points.push_back(ca.evalPoint(i.lowerBound()));
    points.push_back(ca.evalPoint((i.upperBound() + i.lowerBound()) / 2.));
    points.push_back(ca.evalPoint(i.upperBound()));

    type = kArc3pt;
  }

  void circularArc(const OdGePoint3d& start,
    const OdGePoint3d& point,
    const OdGePoint3d& end)
  {
    points.push_back(start);
    points.push_back(point);
    points.push_back(end);

    type = kArc3pt;
  }
  void polyline(OdInt32 nbPoints,
    const OdGePoint3d* pVertexList)
  {
    while(nbPoints > 0)
    {
      --nbPoints;
      points.push_back(*pVertexList);
      ++pVertexList;
    }

    type = kLine;
  }
  void nurbs(const OdGeNurbCurve3d &nurb)
  {
    type = kSpline;
  }
};

/** Description:

    {group:BrepRenderer_Classes} 
*/

typedef OdArray<wrWire> wrWireArray;

/** Description:

    {group:BrepRenderer_Classes} 
*/
class wrTransformStore
{
  OdGeMatrix3d m_Transform;
  
public:

  const OdGeMatrix3d &getTransform() const
  {
    return m_Transform;
  }

  void transformBy(const OdGeMatrix3d &xMat)
  {
    //  m_Transform *= xMat;
    m_Transform.preMultBy(xMat);
  }

  void clearTransform()
  {
    m_Transform.setToIdentity();
  }

  void setTransform(const OdGeMatrix3d &xMat)
  {
    m_Transform = xMat;
  }

  bool isTransformIdentity() const
  {
    return m_Transform.isEqualTo(OdGeMatrix3d::kIdentity);
  }
};

class wrWiresCache : public wrTransformStore
{
public:
  OdUInt32    m_numISOLINES;
  wrWireArray m_Wires;
  bool        m_bSupportTrueColor;

  wrWiresCache()
    : m_numISOLINES(OdUInt32(-1))
    , m_bSupportTrueColor(false)
  {
    m_Wires.setGrowLength(-100);
  }

  void setColor(OdCmEntityColor clr)
  {
    std::for_each(m_Wires.begin(), m_Wires.end(), wrWire::setWireColor(clr));
    m_bSupportTrueColor = true;
  }

  bool isUninit() const
  {
    return m_numISOLINES == OdUInt32(-1);
  }

  void invalidateCache()
  {
    clearCache(OdUInt32(-1));
  }

  void clearCache(OdUInt32 numberOfIsolines)
  {
    m_numISOLINES = numberOfIsolines;
    m_Wires.clear();
    clearTransform();
    m_bSupportTrueColor = false;
  }
};

#endif // _WRWIRECACHE_H_
