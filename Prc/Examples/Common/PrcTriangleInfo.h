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

#ifndef ODPRCTRIANGLEINFO
#define ODPRCTRIANGLEINFO

#include "Ge/GePoint3d.h"

struct Od3Float
{
  float x;
  float y;
  float z;

  Od3Float()
    : x(0.), y(0.), z(0.)
  { }

  Od3Float(float a, float b, float c)
    : x(a), y(b), z(c)
  { }

  Od3Float const operator- (const Od3Float other) const
  {
    return Od3Float(x - other.x, y - other.y, z - other.z);
  }

  Od3Float operator- (const Od3Float other)
  {
    return Od3Float(x - other.x, y - other.y, z - other.z);
  }

  void normalize()
  {
    float len = sqrt(x*x + y*y + z*z);
    if (OdZero(len))
    {
      return;
      throw OdError(eInvalidInput);
    }

    x /= len;
    y /= len;
    z /= len;
  }

  bool same(const Od3Float other, const float e) const
  {
    return  fabs(x - other.x) <= e &&
      fabs(y - other.y) <= e &&
      fabs(z - other.z) <= e;
  }

  float dotProduct(Od3Float other)
  {
    return (x * other.x) + (y * other.y) + (z * other.z);
  }

  Od3Float crossProduct(Od3Float other)
  {
    return Od3Float((y * other.z) - (z * other.y), (z * other.x) - (x * other.z), (x * other.y) - (y * other.x));
  }

  void set(const OdGePoint3d &p)
  {
    x = (float)p.x;
    y = (float)p.y;
    z = (float)p.z;
  }

  void set(const OdGeVector3d &p)
  {
    if (p.isZeroLength())
    {
      x = y = z = 0;
    }
    else
    {
      OdGeVector3d n = p.normal();
      x = (float)n.x;
      y = (float)n.y;
      z = (float)n.z;
    }
  }
};

class TriangleInfo
{
public:
  enum TriangleType
  {
    kTriangle,
    kTriangleTextured,
    kTriangleColored
  };
  Od3Float p1;
  Od3Float p2;
  Od3Float p3;
  OdCmEntityColor color;
  OdUInt8 alpha; // 0 - transparent, 255 - opaque
  OdUInt32 faceIdx;
  OdDbStub* materialID;
  OdGeVector3d vtx_normal[3];

  TriangleInfo()
    : faceIdx(0)
    , materialID(NULL)
    , alpha(255)
    , color(OdCmEntityColor::kNone)
  {
  }
  virtual TriangleType getTriangleType() const
  {
    return kTriangle;
  }
  bool collinear(float tol)
  {
    return p1.same(p2, tol) || p1.same(p3, tol) || p3.same(p2, tol);
  }
};

typedef OdSharedPtr<TriangleInfo> TriangleInfoPtr;
typedef OdArray<TriangleInfoPtr> TriangleInfoPtrArray;

class TriangleInfoTextured : public TriangleInfo
{
public:
  OdGePoint2d texCoords[3];
  OdDbStub * materialLineStyleID;
  TriangleInfoTextured()
  {
    materialLineStyleID = NULL;
  }
  virtual TriangleType getTriangleType() const
  {
    return kTriangleTextured;
  }
};

class TriangleInfoColoredPoints : public TriangleInfo
{
public:
  OdUInt8 red[3];
  OdUInt8 green[3];
  OdUInt8 blue[3];

  TriangleInfoColoredPoints()
  {
    for (OdUInt32 i = 0; i < 3; ++i)
    {
      red[i] = 0;
      green[i] = 0;
      blue[i] = 0;
    }
  }
  virtual TriangleType getTriangleType() const
  {
    return kTriangleColored;
  }
};

#endif //ODPRCTRIANGLEINFO
