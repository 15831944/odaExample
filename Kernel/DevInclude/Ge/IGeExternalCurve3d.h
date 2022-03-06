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

#ifndef OD_IGEEXTC3D_H
#define OD_IGEEXTC3D_H /* {Secret} */

class OdGeExternalCurve3d;
class OdGeNurbCurve3d;

#include "Ge/GeCurve3d.h"

#include "TD_PackPush.h"

class GE_TOOLKIT_EXPORT OdIGeExternalCurve3d
{
public:
  virtual ~OdIGeExternalCurve3d() {}
  virtual bool isLine() const = 0;
  virtual bool isRay() const = 0;
  virtual bool isLineSeg() const = 0;
  virtual bool isCircArc() const = 0;
  virtual bool isEllipArc() const = 0;
  virtual bool isNurbCurve() const = 0;
  virtual bool isNurbCurve(OdGeNurbCurve3d& nurbCurve) const = 0;
  virtual bool isDefined() const = 0;
  virtual bool isNativeCurve(OdGeCurve3d*& nativeCurve) const = 0;
  virtual OdGe::ExternalEntityKind externalCurveKind() const = 0;
  virtual OdIGeExternalCurve3d& set(void* pCurveDef,
                                      OdGe::ExternalEntityKind curveKind,
                                      bool makeCopy = true) = 0;
  virtual OdIGeExternalCurve3d& operator =(const OdIGeExternalCurve3d& extCurve) = 0;
  virtual bool isOwnerOfCurve() const = 0;
  virtual OdIGeExternalCurve3d& setToOwnCurve() = 0;

  virtual void getInterval(OdGeInterval& interval) const = 0;
  virtual bool hasStartPoint(OdGePoint3d& startPoint) const = 0;
  virtual bool hasEndPoint(OdGePoint3d& endPoint) const = 0;
  virtual OdGePoint3d evalPoint(double param) const = 0;
  virtual OdGePoint3d evalPoint(double param, 
                                int numDeriv, 
                                OdGeVector3dArray& derivatives) const = 0;
  virtual void appendSamplePoints(double, 
                                  double, 
                                  double, 
                                  OdGePoint3dArray&, 
                                  OdGeDoubleArray*) const = 0;
  virtual double paramOf(const OdGePoint3d& point, 
                         const OdGeTol& tol = OdGeContext::gTol) const = 0;
  virtual void setInterval() = 0;
  virtual bool setInterval(const OdGeInterval& interval) = 0;
  virtual void reverseParam() = 0;
  virtual OdIGeExternalCurve3d* copy() const = 0;
  virtual bool isEqualTo(const OdIGeExternalCurve3d& curve,
                         const OdGeTol& tol = OdGeContext::gTol) const = 0;
  virtual bool isPeriodic(double& period) const = 0;

  virtual void transformBy(const OdGeMatrix3d& mat) = 0;
  virtual void translateBy(const OdGeVector3d& vec) = 0;

  virtual double length(double startPrm, double endPrm,
                        double tol = OdGeContext::gTol.equalPoint()) const = 0;

  virtual double paramAtLength(double datumPrm, double length, bool posPrmDir,
                               double tol = OdGeContext::gTol.equalPoint()) const = 0;

  virtual bool area(double& value, double startPrm, double endPrm,
                    const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual bool isPlanar(OdGePlane& plane,
                        const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual bool isLinear(OdGeLine3d& line,
                        const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual OdGePoint3d closestPointTo(const OdGePoint3d& point, const OdGeTol& tol) const = 0;

  virtual OdGePoint3d closestPointTo(const OdGeCurve3d& curve, OdGePoint3d& pntOnOtherCurve, const OdGeTol& tol) const = 0;

  virtual void getClosestPointTo( const OdGePoint3d& point, 
                                  OdGePointOnCurve3d& pntOnCrv, 
                                  const OdGeTol& tol = OdGeContext::gTol) const = 0;
  virtual void getClosestPointTo( const OdGeCurve3d& curve, 
                                  OdGePointOnCurve3d& pntOnThisCrv, 
                                  OdGePointOnCurve3d& pntOnOtherCrv, 
                                  const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual void getProjClosestPointTo( const OdGePoint3d& point, 
                                      const OdGeVector3d& projectDirection, 
                                      OdGePointOnCurve3d& pntOnCrv, 
                                      const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual void getProjClosestPointTo( const OdGeCurve3d& curve,
                                      const OdGeVector3d& projectDirection,
                                      OdGePointOnCurve3d& pntOnThisCrv,
                                      OdGePointOnCurve3d& pntOnOtherCrv,
                                      const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual bool getNormalPoint(const OdGePoint3d& point,
                              OdGePointOnCurve3d& pntOnCrv,
                              const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual OdGeBoundBlock3d boundBlock() const = 0;

  virtual OdGeBoundBlock3d boundBlock(const OdGeInterval& range) const = 0;

  virtual OdGeBoundBlock3d orthoBoundBlock() const = 0;
  virtual OdGeBoundBlock3d orthoBoundBlock(const OdGeInterval& range) const = 0;

  virtual double distanceTo(const OdGeCurve3d& curve, const OdGeTol& tol) const = 0;
  virtual double distanceTo(const OdGePoint3d& point,
                            const OdGeTol& tol = OdGeContext::gTol) const = 0;

  //
  virtual OdGeEntity3d* project(const OdGePlane& projectionPlane,
                                const OdGeVector3d& projectDirection,
                                const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual OdGeEntity3d* orthoProject(const OdGePlane& projectionPlane,
                                     const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual bool isOn(const OdGePoint3d& point, 
                    double& param,
                    const OdGeTol& tol = OdGeContext::gTol) const = 0;
  virtual bool isOn(double param, 
                    const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual void getTrimmedOffset(double distance, 
                                const OdGeVector3d& planeNormal, 
                                OdGeCurve3dPtrArray& offsetCurveList, 
                                OdGe::OffsetCrvExtType extensionType = OdGe::kFillet, 
                                const OdGeTol& tol = OdGeContext::gTol)  const = 0;

  virtual bool isDegenerate(OdGe::EntityId& degenerateType, 
                            const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual bool isDegenerate(OdGeEntity3d*& pConvertedEntity, 
                            const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual void getSplitCurves(double param, 
                              OdGeCurve3d*& piece1,
                              OdGeCurve3d*& piece2) const = 0;

  virtual void getLocalClosestPoints( const OdGePoint3d& point,
                                      OdGePointOnCurve3d& approxPntOnThisCrv,
                                      const OdGeInterval* pInterval1 = NULL,
                                      const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual void getLocalClosestPoints( const OdGeCurve3d& curve,
                                      OdGePointOnCurve3d& approxPntOnThisCrv,
                                      OdGePointOnCurve3d& approxPntOnOtherCrv,
                                      const OdGeInterval* pInterval1 = NULL,
                                      const OdGeInterval* pInterval2 = NULL,
                                      const OdGeTol& tol = OdGeContext::gTol) const = 0;
};

#include "TD_PackPop.h"

#endif // OD_IGEEXTC3D_H

