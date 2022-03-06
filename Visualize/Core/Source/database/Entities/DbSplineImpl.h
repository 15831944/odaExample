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

#ifndef _ODDBSPLINEIMPL_INCLUDED_
#define _ODDBSPLINEIMPL_INCLUDED_

#include "DbCurveImpl.h"
#include "Ge/GeNurbCurve3d.h"
#include "DbSystemInternals.h"
#include "DbSpline.h"

class OdTvDbSplineImpl : public OdTvDbCurveImpl, public OdGeNurbCurve3d
{
  static OdTvDbSplineImpl* getImpl(const OdTvDbSpline *pObj)
  { return (OdTvDbSplineImpl*)OdTvDbSystemInternals::getImpl(pObj);}

  typedef enum
  {
		SPLINE_PERIODIC = 1,
		SPLINE_PLANAR   = 2,
		SPLINE_LINEAR   = 4
  } SplineFlags;

	mutable OdUInt8 m_SplineFlags;

  void setPeriodic(bool value) const { SETBIT(m_SplineFlags, SPLINE_PERIODIC, value); } 
  void setPlanar(bool value) const { SETBIT(m_SplineFlags, SPLINE_PLANAR, value); }
  void setLinear(bool value) const { SETBIT(m_SplineFlags, SPLINE_LINEAR, value); }

  void checkPlanarAndLinearFlags() const;

  // AC27 support (TODO)
  typedef enum
  {
    kSplineMethodFitPoints  = 1,
    kSplineCVFrameShow      = 2,
    kSplineIsPeriodic       = 4,
    kSplineUseKnotParam     = 8
  } SplineFlags1;
  OdUInt32 m_Flags1;
  OdInt32  m_KnotParam;

public:
  double m_dCtrlTol;

public:
  ODRX_HEAP_OPERATORS();  // ODRX_USING_HEAP_OPERATORS() causes mac compiler error

  OdTvDbSplineImpl();

  /* void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format,
                                      OdDb::DwgVersion version);*/
  OdGeVector3d getNormal() const;

  bool isClosedSpline(const OdGeTol& tol = OdGeContext::gTol) const;

  TD_USING(OdGeNurbCurve3d::isPeriodic);
  bool isPeriodic() const;
  
  TD_USING(OdGeNurbCurve3d::isPlanar);
  bool isPlanar() const;

  TD_USING(OdGeNurbCurve3d::isLinear);
  bool isLinear() const;

  void invalidateFlags();

  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  void audit(OdTvDbAuditInfo* pAuditInfo);

  void setCastShadows(bool) {}
  bool castShadows() const { return false; }

  void setReceiveShadows(bool) {}
  bool receiveShadows() const { return false; }

  virtual void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  virtual void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  OdTvDbSpline::SplineType type() const;
  OdResult setType(OdTvDbSpline::SplineType type);

  // acad 2013 specific behavior
  OdResult makeClosedImpl();

  virtual void drawFrame(const OdTvDbSpline *pSpline, OdGiWorldDraw* pWd) const;
private:
  mutable OdGeVector3d m_Normal;  

  friend class OdTvDbSpline;
};

#endif // _ODDBSPLINEIMPL_INCLUDED_
