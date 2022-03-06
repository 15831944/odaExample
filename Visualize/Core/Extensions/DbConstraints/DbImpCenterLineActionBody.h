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
#ifndef DbImpCenterLineActionBody_INCLUDED_
#define DbImpCenterLineActionBody_INCLUDED_ /*!DOM*/

#include "DbImpSmartCenterActionBody.h"
#include "DbCenterLineActionBody.h"
#include "DbSmartCenterActionBody.h"

#include "TD_PackPush.h"
/** \details
This class represents the custom implementation of the CenterLine and CentwerLine of the action body.

Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpCenterLineActionBody : public OdTvDbImpSmartCenterActionBody
{
public:
	/** \details
	Constructor creates an instance of this class.
	*/
	OdTvDbImpCenterLineActionBody();

	/** \details
	Destructor destroys an instance of this class.
	*/
	virtual ~OdTvDbImpCenterLineActionBody();

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

  //const OdTvDbSmartCenterLineParametersPtr parameters() const;
  //OdTvDbSmartCenterLineParametersPtr& parameters();
  
  virtual void composeForLoad(OdTvDbObject *pObject, OdDb::SaveType format, OdDb::DwgVersion version, OdTvDbAuditInfo* pAuditInfo);
	//////////////////////////////////////////////////////////////////////////////////// From Arx
	//OdTvDbCenterLineObjectWrapper(OdTvDbCenterLineObjectWrapper const &);
	//OdTvDbCenterLineObjectWrapper(OdTvDbObjectId);
	//OdTvDbCenterLineObjectWrapper &  operator=(OdTvDbCenterLineObjectWrapper const &);
	//void __autoclassinit2(unsigned __int64);

	//OdGeVector3d cachedCenterLineDirection(void)const;
	//double cachedCenterLineLength(void)const;
	//int edgeRefDirEnding(int);
  enum OdResult edgeRefDirEndingArray(OdTvDbAssocActionPtr pAction, OdArray<int>  &);// , OdArrayMemCopyReallocator<int> > &);
	double endExtension(OdTvDbAssocActionPtr pAction)const;
	double endOvershoot(OdTvDbAssocActionPtr pAction)const;
	enum OdResult getCenterLineGeometry(OdGeLineSeg3d &, bool, OdTvDbObjectId parentActionId);
	//enum OdResult getCenterPoint(OdGePoint3d &);
	//enum OdResult setCachedCenterLineDirection(OdGeVector3d const &);
	//enum OdResult setCachedCenterLineLength(double);
	//enum OdResult setEdgeRefDirEnding(int, int);
	enum OdResult setEdgeRefDirEndingArray(OdTvDbAssocActionPtr pAction, OdArray<int>  &);
	enum OdResult setEndExtension(double, OdTvDbAssocActionPtr pAction);
	enum OdResult setEndOvershoot(double, OdTvDbAssocActionPtr pAction);
	enum OdResult setStartExtension(double, OdTvDbAssocActionPtr pAction);
	enum OdResult setStartOvershoot(double, OdTvDbAssocActionPtr pAction);
	double startExtension(OdTvDbAssocActionPtr pAction)const;
	double startOvershoot(OdTvDbAssocActionPtr pAction)const;
	//static enum SmartCenterType wrapperCenterType(void);
  ////////////////////////////////////////////////////////////////////// from Arx for parent classes
  /** \details
  This is the notification call of the corresponding evaluate() method
  of the parent class that owns this action body.
  */
  virtual void evaluateOverride(OdTvDbObjectId parentActionId);
  /** \details
  Creates associative centerLine: action, action body, dependencies etc.
  */
  static OdResult createInstance(
    const OdTvDbFullSubentPathArray entPathArray,
    OdArray<int> inputArr,
    OdTvDbObjectId& centerLineId,
    OdTvDbObjectId& actionBodyId);

  static OdResult createInstance(
    const OdTvDbFullSubentPathArray entPathArray,
    //OdGePoint3dArray ptsSelected,
    OdTvDbObjectId& centerLineId,
    OdTvDbObjectId& actionBodyId);

  static OdResult setParametersAndCreateCL(
    OdArray<int> inputArr,
    OdTvDbDatabasePtr pDb,
    OdTvDbAssocActionPtr pAction,
    OdTvDbCenterLineActionBodyPtr pActionBody,
    OdTvDbAssocDependencyPtr pDependency,
    OdTvDbBlockTableRecordPtr pDestinationBTR,
    OdTvDbLinetypeTableRecordPtr centerLTypetableRec,
    OdTvDbBlockReferencePtr pCenterLineBlock,
    OdTvDbObjectId& centerLineId
    );

  static OdResult getPtrsForTree(
    const OdTvDbFullSubentPathArray entPathArray,
    OdTvDbDatabasePtr& pDb,
    OdTvDbAssocActionPtr& pAction,
    OdTvDbCenterLineActionBodyPtr& pActionBody,
    OdTvDbAssocDependencyPtr& pDependency,
    OdArray<OdTvDbAssocGeomDependencyPtr>& pGeomDependency,
    OdTvDbBlockTableRecordPtr& pDestinationBTR,
    OdTvDbLinetypeTableRecordPtr& centerLTypetableRec,
    OdTvDbBlockReferencePtr& pCenterLineBlock,
    OdArray<OdGeLineSeg3d>& segLineArr,
    OdTvDbObjectId& actionBodyId
    );
//protected:
//  OdTvDbSmartCenterLineParametersPtr m_pParams;
};

#include "TD_PackPop.h"
#endif
