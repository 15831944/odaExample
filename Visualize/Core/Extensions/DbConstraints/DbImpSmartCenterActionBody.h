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

#ifndef DbImpSmartCenterActionBody_INCLUDED_
#define DbImpSmartCenterActionBody_INCLUDED_ /*!DOM*/

#include "DbConstraintsExports.h"
#include "DbAssocGlobal.h"
#include "DbObject.h"
#include "DbObjectIterator.h"
#include "RxObjectImpl.h"
#include "SharedPtr.h"
#include "DbEvalVariant.h"
#include "DbImpAssocActionBody.h"
#include "DbBlockTableRecord.h"
#include "DbLine.h"
#include "DbAssocGeomDependency.h"
#include "DbSmartCenterActionBody.h"

#include "TD_PackPush.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** \details
Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpSmartCenterActionBodyBase : public OdTvDbImpAssocActionBody
{
public:
	/** \details
	Constructor creates an instance of this class.
	*/
		OdTvDbImpSmartCenterActionBodyBase();

	/** \details
	Destructor destroys an instance of this class.
	*/
	virtual ~OdTvDbImpSmartCenterActionBodyBase();

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
    Implements the corresponding 'Override' method of the OdTvDbAssocActionBody
    which owns this implementation object.

    \sa
    OdTvDbAssocActionBody::addMoreObjectsToDeepCloneOverride()
    OdTvDbAssocAction::addMoreObjectsToDeepClone()
  */
  virtual OdResult addMoreObjectsToDeepCloneOverride(const OdTvDbAssocActionBody *body,
    OdTvDbIdMapping &idMap, OdTvDbObjectIdArray &additionalObjectsToClone) const ODRX_OVERRIDE;

protected:
	/*!DOM*/
	friend class OdTvDbImpAssocAction;
	/*!DOM*/
	//OdTvDbObjectIdArray m_arrParams;
	/*!DOM*/
	//OdArray<OdTvDbImpValueParamPtr> m_arrValueParams;
};

//////////////////////////////////////////////////////////////////////////////////////////////
/** \details
This class represents the custom implementation of the associated parameter of the action body.
	
Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpSmartCenterActionBody : public OdTvDbImpSmartCenterActionBodyBase
{
public:
	/** \details
	Constructor creates an instance of this class.
	*/
	OdTvDbImpSmartCenterActionBody();

	/** \details
	Destructor destroys an instance of this class.
	*/
	virtual ~OdTvDbImpSmartCenterActionBody();

  /** \details
  Returns a pointer to the array of parameters for writing.
  */
  const OdTvDbSmartCenterCommonParametersPtr parameters() const;

  /** \details
  Returns a pointer to the array of parameters for writing.
  */
  OdTvDbSmartCenterCommonParametersPtr& parameters();

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
  virtual void evaluateOverride(OdTvDbObjectId parentActionId) {}

  /** \details
  Gets the object ID of the associated array which this action controlls.
  */
  //virtual OdTvDbObjectId getGeomDependEntity(OdTvDbObjectId parentActionId) const;
  //enum OdResult addDependencyToStyle(OdTvDbObjectId);
  //enum OdResult addEntitiesIntoCenterAnonymousBTR(OdTvDbDatabase *, OdTvDbObjectId);

  static OdTvDbViewportPtr getViewPortFromCompoundObject(OdTvDbAssocGeomDependencyPtr pGeomDep);
  //bool associationToBeBroken(void)const;
  //double autoMatchExtension(void)const;
  //enum OdResult breakAssociativity(void);
  //bool cacheAssociateStatus(void);
  //void cacheViewportScale(void);
  //double cachedViewportScale(void)const;
  //static OdTvDbSmartCenterActionBody *  cast(AcRxObject const *);
  //OdTvDbObjectId centerDepId(void)const;
  //OdTvDbObjectId centerObjectId(void)const;
  //enum OdResult createCenterEntity(OdTvDbDatabase *);
  //static AcRxClass *  desc(void);
  //virtual bool doesActionMatchCurrentGeometry(void)const;
  //bool doesActionMatchCurrentSubEntLineWeight(void)const;
  //bool doesActionMatchCurrentSubEntLinetype(void)const;
  //bool doesActionMatchCurrentSubEntLinetypeScale(void)const;
  //bool doesActionNeedUpdate(void)const;
  //enum OdResult eraseCenterEntity(void);
  //virtual void evaluateOverride(void);
  //enum OdResult getAssociatedEntitiesIds(AcArray<OdTvDbObjectId, AcArrayMemCopyReallocator<OdTvDbObjectId> > &);
  //bool getCachedAssociateStatus(void)const;
  //enum OdResult getCenterEntitesIds(AcArray<OdTvDbObjectId, AcArrayMemCopyReallocator<OdTvDbObjectId> > &)const;
  //enum OdResult getCenterObjGeometry(AcArray<AcGeCurve3d *, AcArrayMemCopyReallocator<AcGeCurve3d * > > &)const;
  //virtual enum OdResult getEdgeRefs(AcArray<OdTvDbEdgeRef, AcArrayObjectCopyReallocator<OdTvDbEdgeRef> > &)const;
  //virtual OdTvDbSmartCenterLayout *  getLayout(void)const;
  //OdTvDbObjectId getStyleId(void)const;
  //virtual bool handleBreakingAssociation(void);
  //virtual AcRxClass *  isA(void)const;
  //bool isAssociative(void)const;
  //bool isAutoMatchExtension(double)const;
  //bool isCenterObjectErased(void)const;
  //bool isDragging(void);
  //bool isExplicitlyDeassociatived(void)const;
  //virtual enum OdResult resetExtensions(void);
  //virtual enum OdResult resetOvershoots(void);
  //virtual bool rotationToBeChecked(void)const;
  //static void rxInit(void(*)(AcRxClass const *, wchar_t *  &, int));
  //static void rxInit(void);
  //void setAssociationToBeBroken(bool);
  //enum OdResult setCachedAssociateStatus(bool);
  //enum OdResult setCachedViewportScale(double);
  //enum OdResult setCenterDepId(OdTvDbObjectId);
  //enum OdResult setIsExplicitlyDeassociatived(bool);
  //enum OdResult setStyleDepId(OdTvDbObjectId);
  enum OdResult setSubentLineType(OdString, OdTvDbAssocActionPtr pAction);
  static enum OdResult setSubentLineWeight(double, OdTvDbAssocActionPtr pAction);
  enum OdResult setSubentLinetypeScale(double, OdTvDbAssocActionPtr pAction);
  //OdTvDbObjectId styleDepId(void)const;
  OdString subentLineType(OdTvDbAssocActionPtr pAction)const;
  OdInt32 subentLineWeight(OdTvDbAssocActionPtr pAction)const;
  double subentLinetypeScale(OdTvDbAssocActionPtr pAction)const;
protected:
  virtual OdResult addSubentitySpecialSettings(OdTvDbEntityPtr ent, const OdDbSubentId subentId, OdUInt32 idx, OdTvDbSmartCenterActionBodyPtr pActionBody);
  OdTvDbSmartCenterCommonParametersPtr m_pParams;
  static OdTvDbLinetypeTableRecordPtr getCenterLType(OdTvDbDatabase* pDb, OdString newType = OdString::kEmpty);
  static void setAddedEntityPropertiesByBlock(OdTvDbEntityPtr pLine, OdTvDbAssocActionPtr pAction);// const double newScale, const OdDb::LineWeight newWeight, const OdTvCmColor newColor);
	static OdTvDbObjectId getCenterLayerId(OdTvDbDatabase* pDb);
  OdTvDbImpAssocParamBasedActionBody* m_pParamActionBody;
	/*!DOM*/
	friend class OdTvDbImpAssocAction;
  friend class OdTvDbSmartCenterActionBody;
};

OdTvDbAssocGeomDependencyPtr  getAssocGeomDependencyPtr(OdTvDbAssocActionPtr pAction, OdDb::OpenMode mode = OdDb::kForRead, int geomDepNumber = 0);

#include "TD_PackPop.h"
#endif
