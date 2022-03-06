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
#ifndef DbImpAssocRotatedDimActionBody_INCLUDED_
#define DbImpAssocRotatedDimActionBody_INCLUDED_ /*!DOM*/

#include "DbAssocGlobal.h"
#include "DbImpAssocActionBody.h"
#include "DbAssocRotatedDimActionBody.h"
#include "DbAssocMLeaderActionBody.h"
#include "DbSmartCenterActionBody.h"
#include "DbAssocGeomDependency.h"
#include "DbRotatedDimension.h"
#include "DbAlignedDimension.h"
#include "DbBlockReference.h"
#include "DbAssocActionParam.h"
#include "DbImpSmartCenterActionBody.h"

#include "TD_PackPush.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** \details
Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocAnnotationActionBody : public OdTvDbImpAssocActionBody
{
public:
  /** \details
  Constructor creates an instance of this class.
  */
  OdTvDbImpAssocAnnotationActionBody();

  /** \details
  Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssocAnnotationActionBody();

  /** \details
  Reads the .dwg file data of this object.

  \param pFiler [in]  Filer object from which data are read.

  \remarks
  Returns the filer status.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  /** \details
  Writes the .dwg file data of this object.

  \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
  Reads the .dxf file data of this object.

  \param pFiler [in]  Filer object from which data are read.

  \remarks
  Returns the filer status.
  */
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);

  /** \details
  Writes the .dxf file data of this object.

  \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
  ////////////////////////////////////////////////////////////////////// From Arx
  /** \details
  This is the notification call of the corresponding evaluate() method
  of the parent class that owns this action body.
  */
  virtual void evaluateOverride(OdTvDbObjectId parentActionId);

  void evaluateOverrideAssocDim(OdTvDbObjectId parentActionId, OdGePoint3d* ptPoint, OdGePoint3d* ptDimPoint, const int pointNum);
  /** \details
  Gets the object ID of the associated array which this action controlls.
  */
  virtual OdTvDbObjectId getArrayEntity(OdTvDbObjectId parentActionId) const;

  OdTvDbObjectId getViewPortIdFromDependency(OdTvDbObjectId parentActionId) const;

  void setAssocDependencyID(OdTvDbObjectId objID);
  void setActionParamID1(OdTvDbObjectId objID);
  void setActionParamID2(OdTvDbObjectId objID);
  OdTvDbObjectId actionParamID1() const { return m_ActionParamID1; }
  OdTvDbObjectId actionParamID2() const { return m_ActionParamID2; }
protected:
  //virtual OdResult setAndGetEdgeRefs(OdTvDbObjectId assocActionParam, OdGeCurve3d* geometry, OdGePoint3d ptPoint, OdTvDbObjectId parentActionId, OdTvDbEdgeRef& edgeRef);
  virtual OdResult resetEdgeRefs(OdTvDbAssocEdgeActionParamPtr pEdgeParam, OdGeCurve3d* geometry, /*OdGePoint3d ptPoint,*/ OdTvDbObjectId parentActionId, OdTvDbEdgeRef& edgeRef);
  virtual OdResult getGeometryAndSidePointForDimension(OdGeCurve3d* &geometry, OdGePoint3d & refLineSegment, int seg, OdTvDbAssocActionPtr pAction);
  virtual OdResult setDataToActionParam(OdGeCurve3d* geometry, OdTvDbObjectId snapPointParamId, OdGePoint3d& ptPoint, OdGePoint3d ptDimPoint,
    OdTvDbObjectId parentActionId/*, OdTvDbBlockReferencePtr pBlockRef, OdTvDbViewportPtr  pViewport*/);
  static OdTvDbObjectId createOdTvDbAssocOSnapPointRefActionParam( const OdTvDbObjectId actionId, const OdTvDbObjectId source, OdGePoint3d ptPoint1, const OdTvDbAssocGeomDependencyPtr pGeomDependency1, 
    const OdTvDbAssocGeomDependencyPtr pGeomDependency2, OdTvDbObjectId& anchorId, const PointPositionOnBlockLine isStartPoint, int index);
  static void CreateGeomDependencies(const OdTvDbFullSubentPath entPath, const OdTvDbObjectId actionId, const OdTvDbObjectId source, 
    OdTvDbAssocGeomDependencyPtr& pGeomDependency1, OdTvDbAssocGeomDependencyPtr& pGeomDependency2, PointPositionOnBlockLine& isStartPoint);
  static OdTvDbObjectId getAssocDependencyForAction(const OdTvDbObjectId parentActionId);
  static OdTvDbObjectId GetLineIDByPoint(OdTvDbBlockReferencePtr bRef, OdGePoint3d ptPoint, PointPositionOnBlockLine&  isStartPoint);
  /*!DOM*/
  friend class OdTvDbImpAssocAction;
  static OdTvDbObjectId getIdForFirstWriteDependency(OdTvDbObjectIdArray depIDs);
  //enum AssocActionBodyTypes
  //{
  //  kUnDefined = 0,
  //  kMleader,
  //  kRotatedDim
  //};

  //AssocActionBodyTypes m_ActionBodyType;
//private:
protected:	
	OdTvDbObjectId m_ActionParamID1;
	OdTvDbObjectId m_ActionParamID2;
	OdTvDbObjectId m_ActionParamID3;
	OdUInt16 m_undefined2;
  OdTvDbObjectId m_assocDependencyID;
  OdUInt16 m_undefinedAnnotationActionBody;

  OdTvDbImpAssocParamBasedActionBody *m_paramBasedActionBody;
};

//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** \details
This class represents the custom implementation of the action body based on AnnotationActionBody.

Library: Source code provided.
<group Contraint_Classes>
*/

class DBCONSTRAINTS_EXPORT OdTvDbImpAssocRotatedDimActionBody : public OdTvDbImpAssocAnnotationActionBody
{
public:
  /** \details
  Constructor creates an instance of this class.
  */
  OdTvDbImpAssocRotatedDimActionBody();

  /** \details
  Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssocRotatedDimActionBody();

  /** \details
  Reads the .dwg file data of this object.

  \param pFiler [in]  Filer object from which data are read.

  \remarks
  Returns the filer status.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  /** \details
  Writes the .dwg file data of this object.

  \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
  Reads the .dxf file data of this object.

  \param pFiler [in]  Filer object from which data are read.

  \remarks
  Returns the filer status.
  */
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);

  /** \details
  Writes the .dxf file data of this object.

  \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
  /** \details
  Returns a pointer to the array of parameters for writing.
  */
  //const OdTvDbSmartCenterMarkParametersPtr parameters() const;
  //OdTvDbSmartCenterMarkParametersPtr& parameters();

  virtual void composeForLoad(OdTvDbObject *pObject, OdDb::SaveType format, OdDb::DwgVersion version, OdTvDbAuditInfo* pAuditInfo);
  /** \details
  This is the notification call of the corresponding evaluate() method
  of the parent class that owns this action body.
  */
  virtual void evaluateOverride(OdTvDbObjectId parentActionId);

  /** \details
  Creates associative rotated dimensin: action, action body, dependencies etc.
  */
  static OdResult createInstance(
	  const OdTvDbFullSubentPathArray entPathArray,
	  OdGePoint3dArray ptsSelected,
	  OdTvDbObjectId& actionBodyId, OdString paramName = OD_T("Rotated"));

  virtual OdStringArray compareWith(OdTvDbImpAssocActionBody *bodyIDToCompare, OdDb::DwgVersion filerVersion = OdDb::kDHL_CURRENT) const;
};

#include "TD_PackPop.h"

#endif

