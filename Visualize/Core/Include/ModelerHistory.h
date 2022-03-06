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


#ifndef _OD_MODELERHISTORY_INCLUDED_
#define _OD_MODELERHISTORY_INCLUDED_

#define STL_USING_MAP
#include "OdaSTL.h"
#include "RxObject.h"
#include "ModelerDefs.h"
#include "Db3dSolid.h"
#include "DbObject.h"

#include "TD_PackPush.h"


/** \details

  Corresponding C++ library: TD_Db
  <group OdTvDbSh_Classes> 
*/
class DBENT_EXPORT OdTvDbShModelerHistory : public OdRxObject
{
protected:
  OdTvDbShModelerHistory() {}
public:  
  ODRX_DECLARE_MEMBERS(OdTvDbShModelerHistory);

  virtual OdTvDbObjectId createShHistory(OdTvDb3dSolid const* pSolid, OdTvDbObjectPtr& pHistObj) = 0;
  virtual void getHistoryVariables(const OdTvDbObjectPtr& pHistObj, bool& bShowHistory, bool& bRecordHistory) = 0;
  virtual void setShowHistory(OdTvDbObjectPtr& pHistObj, bool bShowHistory) = 0;
  virtual void setRecordHistory(OdTvDbObjectPtr& pHistObj, bool bRecordHistory) = 0;
  virtual void clearHistory(OdTvDbObjectPtr& pHistObj) = 0;

  virtual OdResult createBox(OdTvDb3dSolid* pSolid, double dXLen, double dYLen, double dZLen) = 0;
  virtual OdResult createFrustum(OdTvDb3dSolid* pSolid, double dHeight, double dXRadius, double dYRadius, double dTopXRadius) = 0;
  virtual OdResult createWedge(OdTvDb3dSolid* pSolid, double dXLen, double dYLen, double dZLen) = 0;
  virtual OdResult createPyramid(OdTvDb3dSolid* pSolid, double dHeight, int iSides, double dRadius, double dTopRadius) = 0;
  virtual OdResult createSphere(OdTvDb3dSolid* pSolid, double dRadius) = 0;
  virtual OdResult createTorus(OdTvDb3dSolid* pSolid, double dMajorRadius, double dMinorRadius) = 0;

  virtual OdResult setSubentColor(OdTvDb3dSolid* pSolid, const OdDbSubentId &subentId, const OdTvCmColor &color) = 0;
  virtual OdResult setSubentMaterial(OdTvDb3dSolid* pSolid, const OdDbSubentId &subentId, OdTvDbObjectId matId) = 0;

  virtual OdResult createLoftedSolid(OdTvDb3dSolid* pSolid, OdTvDbEntityPtrArray& crossSections, OdTvDbEntityPtrArray& guideCurves, OdTvDbEntity* pPathCurve, OdTvDbLoftOptions& loftOpt) = 0;
  virtual OdResult createRevolvedSolid(OdTvDb3dSolid* pSolid, OdTvDbEntity* pRevolveCurve, const OdGePoint3d& axisPoint, const OdGeVector3d& axisDir, double dAngleOfRevolution, double dStartAngle, OdTvDbRevolveOptions& revolveOpt) = 0;
  virtual OdResult createSweptSolid(OdTvDb3dSolid* pSolid, OdTvDbEntity* pSweepCurve, OdTvDbEntity* pPathCurve, const OdGeVector3d& directioVector, OdTvDbSweepOptions& sweepOpt) = 0;

  virtual OdResult booleanOper(OdTvDb3dSolid* pSolid, OdTvDb3dSolid* pSecondEll, OdDb::BoolOperType operation) = 0;

  virtual OdResult postInDatabase(OdTvDbObjectId objSolidId ) = 0;
  virtual OdResult subTransformBy(OdTvDb3dSolid* pSolid, const OdGeMatrix3d& xform) = 0;
  virtual OdResult filletEdges(OdTvDb3dSolid* pSolid, const OdArray<OdDbSubentId *> &edgeSubentIds, const OdGeDoubleArray& radius, const OdGeDoubleArray& startSetback, const OdGeDoubleArray& endSetback) = 0;
  virtual OdResult chamferEdges(OdTvDb3dSolid* pSolid, const OdArray<OdDbSubentId *> &edgeSubentIds, const OdDbSubentId& baseFaceSubentId, double baseDist, double otherDist) = 0;
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdModelerHistory object pointers.
*/
typedef OdSmartPtr<OdTvDbShModelerHistory> OdTvDbShModelerHistoryPtr;

#include "TD_PackPop.h"

#endif // _OD_MODELERHISTORY_INCLUDED_
