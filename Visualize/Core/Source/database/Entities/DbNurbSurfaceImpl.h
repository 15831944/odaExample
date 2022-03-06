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

#ifndef _DbNurbSurfaceImpl_h_
#define _DbNurbSurfaceImpl_h_

#include "TD_PackPush.h"
#include "DbNurbSurface.h"
#include "DbSurfaceImpl.h"


class OdTvDbNurbSurfaceImpl : public OdTvDbSurfaceImpl
{
  friend class OdTvDbSurfaceImpl;
protected:
  bool m_bModlrDecomposedType;
  bool m_bModlrDecomposedChecksum;
  OdBinaryData m_binDataFull;
  OdString m_sChecksum;
  // new in 2013
  bool m_bShowCVHull;
  OdInt16 m_unkInt16;
  OdGeVector3d m_unkVectors[4];
  
public:
  OdTvDbNurbSurfaceImpl();

  static OdTvDbNurbSurfaceImpl* getImpl(const OdTvDbNurbSurface *pObj)
  { return (OdTvDbNurbSurfaceImpl*)OdTvDbSystemInternals::getImpl(pObj);}

  virtual OdResult get( int& iUDegree, int& iVDegree, bool& bRational, int& iUNumControlPoints, int& iVNumControlPoints,
                        OdGePoint3dArray& ctrlPtsArr, OdGeDoubleArray& weights, 
                        OdGeKnotVector& uKnots, OdGeKnotVector& vKnots) const;

  virtual OdResult set( int iUDegree, int iVDegree, bool bRational, int iUNumControlPoints, int iVNumControlPoints,
                        const OdGePoint3dArray& ctrlPtsArr, const OdGeDoubleArray& weights, 
                        const OdGeKnotVector& uKnots, const OdGeKnotVector& vKnots);
  
  virtual OdResult getNumberOfControlPointsInU(int& iCount) const;
  virtual OdResult getNumberOfControlPointsInV(int& iCount) const;

  virtual OdResult getNumberOfKnotsInU(int& iCount) const;
  virtual OdResult getNumberOfKnotsInV(int& iCount) const;

  virtual OdResult getUKnots(OdGeKnotVector& knots) const;
  virtual OdResult getVKnots(OdGeKnotVector& knots) const;

  virtual OdResult getDegreeInU(int& iDegree) const;
  virtual OdResult getDegreeInV(int& iDegree) const;

  virtual OdResult isClosedInU(bool& bIsClosed) const;
  virtual OdResult isClosedInV(bool& bIsClosed) const;

  virtual OdResult isPeriodicInU(bool& bIsPeriodic) const;
  virtual OdResult isPeriodicInV(bool& bIsPeriodic) const;

  virtual OdResult getPeriodInU(double& dPeriod) const; 
  virtual OdResult getPeriodInV(double& dPeriod) const; 
  
  virtual OdResult evaluate(double dU, double dV, OdGePoint3d& pos) const;

  virtual OdResult evaluate(double dU, double dV, OdGePoint3d& pos, OdGeVector3d& uDeriv, OdGeVector3d& vDeriv) const;

  virtual OdResult evaluate(double dU, double dV, OdGePoint3d& pos, OdGeVector3d& uDeriv, OdGeVector3d& vDeriv,
                            OdGeVector3d& uuDeriv, OdGeVector3d& uvDeriv, OdGeVector3d& vvDeriv) const;

  virtual OdResult evaluate(double dU, double dV, int iDerivDegree, OdGePoint3d& point, OdGeVector3dArray& derivatives) const;

  virtual OdResult isRational(bool& bIsRational) const;

  virtual OdResult isPlanar(bool& bIsPlanar, OdGePoint3d& ptOnSurface, OdGeVector3d& normal) const;

  virtual OdResult isPointOnSurface(const OdGePoint3d& point, bool& bOnSurface) const;

  virtual OdResult getNormal(double dU, double dV, OdGeVector3d& normal) const;

  virtual OdResult getNumberOfSpansInU(int& iSpan) const;
  virtual OdResult getNumberOfSpansInV(int& iSpan) const;

  virtual OdResult getIsolineAtU(double dNumberSegments, OdTvDbCurvePtrArray& lineSegments) const;
  virtual OdResult getIsolineAtV(double dNumberSegments, OdTvDbCurvePtrArray& lineSegments) const;

  // Insert a knot in (U - 0; V - 1)
  virtual OdResult InsertKnot(double dVal, int iUorV);

  virtual OdResult InsertControlPointsAtU(double dU, const OdGePoint3dArray& vCtrlPts, const OdGeDoubleArray& vWeights);
  virtual OdResult InsertControlPointsAtV(double dV, const OdGePoint3dArray& uCtrlPts, const OdGeDoubleArray& uWeights);

  virtual OdResult RemoveControlPointsAtU(int iUDegree);
  virtual OdResult RemoveControlPointsAtV(int iVDegree);

  virtual OdResult rebuild(int iUDegree, int iVDegree, int iNumUCtrlPts, int iNumVCtrlPts, bool bRestore);

  virtual OdResult modifyPositionAndTangent(double dU, double dV, const OdGePoint3d& point, const OdGeVector3d* uDeriv, const OdGeVector3d* vDeriv);

  virtual OdResult getParameterOfPoint(const OdGePoint3d& point, double& dU, double& dV) const;

  virtual OdResult getControlPoints(int& iUCount, int& iVCount, OdGePoint3dArray& points) const;

  virtual OdResult setControlPoints(int iUCount, int iVCount, const OdGePoint3dArray& points);

  virtual OdResult getControlPointAndWeight(int iUIndex, int iVIndex, OdGePoint3d& point, double& weight, bool& bIsRational) const;

  virtual OdResult setControlPointAndWeight(int iUIndex, int iVIndex, const OdGePoint3d& point, double weight);

  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  virtual OdResult dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  friend class OdTvDbNurbSurface;
};
  
typedef OdSmartPtr<OdTvDbNurbSurface> OdTvDbNurbSurfacePtr;

#include "TD_PackPop.h"
#endif //_DbNurbSurfaceImpl_h_
