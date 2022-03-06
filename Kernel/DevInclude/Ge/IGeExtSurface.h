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

#ifndef OD_IGEEXTSF_H
#define OD_IGEEXTSF_H /* {Secret} */

#include "Ge/Ge.h"
#include "TD_PackPush.h"
#include "Ge/GeVector3dArray.h"

class OdGePoint2d;
class OdGePoint3d;
class OdGeInterval;
class OdGeSurface;
class OdGeTol;
class OdGeCurveBoundary;
class OdGePointOnSurface;

class OdIGeExtSurface
{
public:
  virtual ~OdIGeExtSurface() {}
  virtual OdGe::ExternalEntityKind externalSurfaceKind() const = 0;
  virtual bool isPlane() const = 0;
  virtual bool isSphere() const = 0;
  virtual bool isCylinder() const = 0;
  virtual bool isCone() const = 0;
  virtual bool isEllipCylinder() const = 0;
  virtual bool isEllipCone() const = 0;
  virtual bool isTorus() const = 0;
  virtual bool isNurbs() const { throw eNotImplemented; };
  virtual bool isDefined() const = 0;
  virtual bool isOwnerOfSurface() const = 0;

  //surface
  virtual void getEnvelope(OdGeInterval& intrvlU, OdGeInterval& intrvlV) const = 0;
  virtual bool isClosedInU(const OdGeTol& tol) const = 0;
  virtual bool isClosedInV(const OdGeTol& tol) const = 0;
  virtual OdGePoint3d evalPoint(const OdGePoint2d& param) const = 0;
  virtual OdGePoint3d evalPoint(const OdGePoint2d& param, int numDeriv, OdGeVector3dArray& derivatives) const = 0;
  virtual OdGePoint3d evalPoint(const OdGePoint2d& param, int numDeriv, OdGeVector3dArray& derivatives, OdGeVector3d& normal) const = 0;
  virtual OdGePoint2d paramOf(const OdGePoint3d& p, const OdGeTol& tol) const = 0;

  virtual bool isNormalReversed() const = 0;
  virtual bool isOn(const OdGePoint3d& point, OdGePoint2d& paramPoint, const OdGeTol& tol) const = 0;
  virtual OdGePoint3d closestPointTo(const OdGePoint3d& point, const OdGeTol& tol) const = 0;
  virtual double distanceTo(const OdGePoint3d& point, const OdGeTol& tol) const = 0;
  virtual void reverseNormal() = 0;
  virtual void getClosestPointTo(const OdGePoint3d& point, OdGePointOnSurface& pntOnSurface, const OdGeTol& tol) const = 0;

  virtual OdGe::EntityId type() const = 0;
  virtual bool isKindOf(OdGe::EntityId id) const = 0;
  virtual bool project(const OdGePoint3d& p, OdGePoint3d& projP, const OdGeTol& tol = OdGeContext::gTol) const {return false;}
  virtual void transformBy(const OdGeMatrix3d& mat) { throw eNotImplemented; };
  virtual void getCurveIntersection(const OdGeCurve3d&, OdGePoint3dArray& intPts) const { throw eNotImplemented; };
  virtual OdIGeExtSurface* copy() const = 0;
};
#include "TD_PackPop.h"

#endif // OD_IGEEXTSF_H

