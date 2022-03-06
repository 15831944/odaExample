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

#ifndef OD_IGEEXTCURVE2D_H
#define OD_IGEEXTCURVE2D_H /* {Secret} */

#include "Ge/GeCurve2d.h"

#include "TD_PackPush.h"

class OdGeNurbCurve2d;

class GE_TOOLKIT_EXPORT OdIGeExternalCurve2d
{
public:
  virtual ~OdIGeExternalCurve2d() {}
  virtual bool isLine() const = 0;
  virtual bool isRay() const = 0;
  virtual bool isLineSeg() const = 0;
  virtual bool isCircArc() const = 0;
  virtual bool isEllipArc() const = 0;
  virtual bool isNurbCurve() const = 0;
  virtual bool isNurbCurve(OdGeNurbCurve2d& nurbCurve) const = 0;
  virtual bool isDefined() const = 0;
  virtual bool isNativeCurve(OdGeCurve2d*& nativeCurve) const = 0;
  virtual OdGe::ExternalEntityKind externalCurveKind() const = 0;
  virtual OdIGeExternalCurve2d& set(void* pCurveDef,
                                      OdGe::ExternalEntityKind curveKind,
                                      bool makeCopy = true) = 0;
  virtual OdIGeExternalCurve2d& operator = (const OdIGeExternalCurve2d& extCurve) = 0;
  virtual bool isOwnerOfCurve() const = 0;
  virtual OdIGeExternalCurve2d& setToOwnCurve() = 0;

  virtual void getInterval(OdGeInterval& interval) const = 0;
  virtual bool hasStartPoint(OdGePoint2d& startPoint) const = 0;
  virtual bool hasEndPoint(OdGePoint2d& endPoint) const = 0;
  virtual OdGePoint2d evalPoint(double param) const = 0;
  virtual OdGePoint2d evalPoint(double param, 
                                int numDeriv, 
                                OdGeVector2dArray& derivatives) const = 0;
  virtual void appendSamplePoints(double , 
                                  double , 
                                  double , 
                                  OdGePoint2dArray& , 
                                  OdGeDoubleArray* ) const = 0;
  virtual double paramOf(const OdGePoint2d& point, 
                         const OdGeTol& tol = OdGeContext::gTol) const = 0;
  virtual void setInterval() = 0;
  virtual bool setInterval(const OdGeInterval& interval) = 0;

  virtual OdIGeExternalCurve2d* copy() const = 0;

  virtual bool isEqualTo(const OdIGeExternalCurve2d& curve,
                         const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual void transformBy(const OdGeMatrix2d& mat) = 0;

  virtual void translateBy(const OdGeVector2d& vec) = 0;
  
  virtual OdGeCurve2d& reverseParam() = 0;

  virtual double distanceTo(const OdGeCurve2d& otherCur,
                            const OdGeTol& tol = OdGeContext::gTol) const = 0;
  virtual double distanceTo(const OdGePoint2d& point,
                            const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual OdGePoint2d closestPointTo( const OdGePoint2d& point,
                                      const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual OdGePoint2d closestPointTo( const OdGeCurve2d& curve2d,
                                      OdGePoint2d& pntOnOtherCrv,
                                      const OdGeTol& tol= OdGeContext::gTol) const = 0;

  virtual bool isOn(const OdGePoint2d& point, 
                    double& param,
                    const OdGeTol& tol = OdGeContext::gTol) const = 0;
  virtual bool isOn(double param, 
                    const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual bool isPeriodic(double& period) const = 0;

  virtual double length(double startPrm, double endPrm,
                        double tol = OdGeContext::gTol.equalPoint()) const = 0;

  virtual double paramAtLength(double datumPrm, double length, bool posPrmDir,
                               double tol = OdGeContext::gTol.equalPoint()) const = 0;

  virtual bool area(double& value, double startPrm, double endPrm,
                    const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual bool isLinear(OdGeLine2d& line, 
                        const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual void getClosestPointTo( const OdGePoint2d& point,
                                  OdGePointOnCurve2d& pntOnCrv,
                                  const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual void getClosestPointTo( const OdGeCurve2d& curve2d,
                                  OdGePointOnCurve2d& pntOnThisCrv,
                                  OdGePointOnCurve2d& pntOnOtherCrv,
                                  const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual bool getNormalPoint(const OdGePoint2d& point,
                              OdGePointOnCurve2d& pntOnCrv,
                              const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual OdGeBoundBlock2d boundBlock() const = 0;
  virtual OdGeBoundBlock2d boundBlock(const OdGeInterval& range) const = 0;

  virtual OdGeBoundBlock2d orthoBoundBlock() const = 0;
  virtual OdGeBoundBlock2d orthoBoundBlock(const OdGeInterval& range) const = 0;

  virtual bool isDegenerate(OdGe::EntityId& degenerateType, 
                            const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual bool isDegenerate(OdGeEntity2d*& pConvertedEntity, 
                            const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual void getSplitCurves(double param, 
                              OdGeCurve2d*& piece1,
                              OdGeCurve2d*& piece2) const = 0;

  virtual void getTrimmedOffset(double distance,
                                OdGeCurve2dPtrArray& offsetCurveList,
                                OdGe::OffsetCrvExtType extensionType = OdGe::kFillet,
                                const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual void getLocalClosestPoints( const OdGePoint2d& point,
                                      OdGePointOnCurve2d& approxPnt,
                                      const OdGeInterval* nbhd = NULL,
                                      const OdGeTol& tol = OdGeContext::gTol) const = 0;

  virtual void getLocalClosestPoints( const OdGeCurve2d& otherCurve,
                                      OdGePointOnCurve2d& approxPntOnThisCrv,
                                      OdGePointOnCurve2d& approxPntOnOtherCrv,
                                      const OdGeInterval* nbhd1 = NULL,
                                      const OdGeInterval* nbhd2 = NULL,
                                      const OdGeTol& tol = OdGeContext::gTol) const = 0;
};

#include "TD_PackPop.h"

#endif // OD_IGEEXTCURVE2D_H
