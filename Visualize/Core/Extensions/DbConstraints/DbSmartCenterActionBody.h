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

#ifndef DbSmartCenterActionBody_INCLUDED_
#define DbSmartCenterActionBody_INCLUDED_ /*!DOM*/

#include "DbSmartCenterActionBodyBase.h"
#include "DbLayout.h"
#include "TD_PackPush.h"
#include "DbSmartCenterObjectsParameters.h"

class OdTvDbBlockReference;

/** \details
Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT ODRX_ABSTRACT OdTvDbSmartCenterActionBody : public OdTvDbSmartCenterActionBodyBase
{
public:
	ODRX_DECLARE_MEMBERS(OdTvDbSmartCenterActionBody);

	/** \details
	Constructor creates an instance of this class.
	*/
	OdTvDbSmartCenterActionBody();

  /** \details
  Returns a pointer to the array of parameters for writing.
  */
  const OdTvDbSmartCenterCommonParametersPtr parameters() const;

  /** \details
  Returns a pointer to the array of parameters for writing.
  */
  OdTvDbSmartCenterCommonParametersPtr& parameters();

	//////////////////////////////////////////////////////////////////////////// fromArx
	////AcTvDbSmartCenterActionBody(void);
	////virtual ~AcTvDbSmartCenterActionBody(void);
	////void __autoclassinit2(unsigned __int64);
	//enum OdResult addDependencyToStyle(OdTvDbObjectId);
	//enum OdResult addEntitiesIntoCenterAnonymousBTR(OdTvDbDatabase *, OdTvDbObjectId);
  
	//bool associationToBeBroken(void)const;
	//double autoMatchExtension(void)const;
	//enum OdResult breakAssociativity(void);
	//bool cacheAssociateStatus(void);
	//void cacheViewportScale(void);
	//double cachedViewportScale(void)const;
	////static OdTvDbSmartCenterActionBody *  cast(OdRxObject const *);
	//OdTvDbObjectId centerDepId(void)const;
	//OdTvDbObjectId centerObjectId(void)const;
	//enum OdResult createCenterEntity(OdTvDbDatabase *);
	//virtual bool doesActionMatchCurrentGeometry(void)const;
	//bool doesActionMatchCurrentSubEntLineWeight(void)const;
	//bool doesActionMatchCurrentSubEntLinetype(void)const;
	//bool doesActionMatchCurrentSubEntLinetypeScale(void)const;
	//bool doesActionNeedUpdate(void)const;
	//enum OdResult eraseCenterEntity(void);

  /** \details
  This is the notification call of the corresponding evaluate() method
  of the parent class that owns this action body.
  */
  virtual void evaluateOverride(void);

	////enum OdResult getAssociatedEntitiesIds(OdArray<OdTvDbObjectId, OdArrayMemCopyReallocator<OdTvDbObjectId> > &);
	//bool getCachedAssociateStatus(void)const;
	////enum OdResult getCenterEntitesIds(OdArray<OdTvDbObjectId, OdArrayMemCopyReallocator<OdTvDbObjectId> > &)const;
	////enum OdResult getCenterObjGeometry(OdArray<OdGeCurve3d *, OdArrayMemCopyReallocator<OdGeCurve3d * > > &)const;
	////virtual enum OdResult getEdgeRefs(OdArray<OdTvDbEdgeRef, OdArrayObjectCopyReallocator<OdTvDbEdgeRef> > &)const;
	////virtual OdTvDbSmartCenterLayout *  getLayout(void)const;
	//virtual OdTvDbLayoutPtr * getLayout(void)const;
	//OdTvDbObjectId getStyleId(void)const;
	//virtual bool handleBreakingAssociation(void);
	//bool isAssociative(void)const;
	//bool isAutoMatchExtension(double)const;
	//bool isCenterObjectErased(void)const;
	//bool isDragging(void);
	//bool isExplicitlyDeassociatived(void)const;
  /** \details
  This is the notification call of the corresponding postProcessAfterDeepClone() method
  of the parent class that owns this action body.
  */
	//virtual enum OdResult resetExtensions(void);
	//virtual enum OdResult resetOvershoots(void);
	//virtual bool rotationToBeChecked(void)const;
	//static void rxInit(void(*)(OdRxClass const *, wchar_t *  &, int));
	//void setAssociationToBeBroken(bool);
	//enum OdResult setCachedAssociateStatus(bool);
	//enum OdResult setCachedViewportScale(double);
	//enum OdResult setCenterDepId(OdTvDbObjectId);
	//enum OdResult setIsExplicitlyDeassociatived(bool);
	//enum OdResult setStyleDepId(OdTvDbObjectId);
	//enum OdResult setSubentLineType(OdString);
	//enum OdResult setSubentLineWeight(int);
	//enum OdResult setSubentLinetypeScale(double);
	//OdTvDbObjectId styleDepId(void)const;
	//OdString subentLineType(void)const;
	//int subentLineWeight(void)const;
	//double subentLinetypeScale(void)const;
  enum OdResult setGeometryParam(double newOvershoot, const OdString& paramName, bool assertEnable = true);
  enum OdResult getGeometryParam(double& newOvershoot, const OdString& paramName) const;
  enum OdResult setStringGeometryParam(const OdString newValue, const OdString& paramName);
  enum OdResult getStringGeometryParam(OdString& newString, const OdString& paramName) const;	
  static OdTvDbObjectId getSmartCenterActionBody(const OdTvDbBlockReference* pBlkRef);

  OdResult postProcessAfterDeepCloneOverride(OdTvDbIdMapping& idMap) ODRX_OVERRIDE;

protected:
  virtual OdResult addSubentitySpecialSettings(OdTvDbEntityPtr ent, const OdDbSubentId subentId, OdUInt32 idx);

  friend class OdTvDbImpSmartCenterActionBody;
  friend class OdTvDbImpCenterLineActionBody;
  friend class OdTvDbImpCenterMarkActionBody;
};

/** \details
The typified smart pointer. This template class is specialization of the OdSmartPtr class
for the OdTvDbSmartCenterActionBodyBase class.

\sa	
<link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbSmartCenterActionBody> OdTvDbSmartCenterActionBodyPtr;

#include "TD_PackPop.h"

#endif

