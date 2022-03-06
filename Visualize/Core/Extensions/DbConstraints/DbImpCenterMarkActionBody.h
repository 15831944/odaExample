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
#ifndef DbImpCenterMarkActionBody_INCLUDED_
#define DbImpCenterMarkActionBody_INCLUDED_ /*!DOM*/

#include "DbImpSmartCenterActionBody.h"
#include "DbCenterMarkActionBody.h"
#include "DbDatabase.h"

#include "TD_PackPush.h"
/** \details
This class represents the custom implementation of the CenterMark and CentwerLine of the action body.

Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpCenterMarkActionBody : public OdTvDbImpSmartCenterActionBody
{
public:
  //static OdTvDbImpCenterMarkActionBody* getImpl(const OdTvDbCenterMarkActionBody *pObj)
  //{
  //  return (OdTvDbImpCenterMarkActionBody*)OdTvDbSystemInternals::getImpl(pObj);
  //}

  /** \details
	Constructor creates an instance of this class.
	*/
	OdTvDbImpCenterMarkActionBody();

	/** \details
	Destructor destroys an instance of this class.
	*/
	virtual ~OdTvDbImpCenterMarkActionBody();

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
	////////////////////////////////////////////////////////////////////////////////////
	/*OdTvDbCenterMarkObjectWrapper(OdTvDbCenterMarkObjectWrapper const & ) ;
	OdTvDbCenterMarkObjectWrapper(OdTvDbObjectId) ;
	OdTvDbCenterMarkObjectWrapper &  operator=(OdTvDbCenterMarkObjectWrapper const & ) ;
	void __autoclassinit2(unsigned __int64) ;*/
	//double crossHairGap(void)const ;
	OdString crossHairGapExpression(OdTvDbAssocActionPtr pAction)const ;
	//double crossHairLength(void)const ;
	OdString crossHairLengthExpression(OdTvDbAssocActionPtr pAction)const ;
	//enum OdResult getAllExtensionPoints(OdArray<OdGePoint3d,OdArrayMemCopyReallocator<OdGePoint3d> > & ) ;
	//enum OdResult getAllExtensionPoints(OdGePoint3d & ,OdGePoint3d & ,OdGePoint3d & ,OdGePoint3d & ) ;
	//enum OdResult getAllOvershootPoints(OdArray<OdGePoint3d,OdArrayMemCopyReallocator<OdGePoint3d> > & ) ;
	//enum OdResult getAllOvershootPoints(OdGePoint3d & ,OdGePoint3d & ,OdGePoint3d & ,OdGePoint3d & ) ;
	//enum OdResult getCenterPoint(OdGePoint3d & ) ;
	//enum OdResult getCrossLengthAndGap(double & ,double & )const ;
	//double getExtensionLineLength(enum AcCenterMarkSubEntType)const ;
  OdDb::Visibility getExtensionLinesVisibility(OdTvDbAssocActionPtr pAction)const ;
	static OdResult getRefCircle(OdGeCircArc3d & , const OdTvDbObjectId &parentActionId);
	static OdResult getRefCircle(OdGeCircArc3d & , const OdTvDbAssocGeomDependency* pGeomDep);
	//double getRefCircleRadius(void)const ;
	//bool getSubEntVisibility(enum AcCenterMarkSubEntType)const ;
	//OdGeVector3d getSubentDirection(enum AcCenterMarkSubEntType)const ;
	//OdGeLineSeg3d getSubentLineGeometry(enum AcCenterMarkSubEntType,bool)const ;
	double horizontalEndExtension(const OdTvDbAssocActionPtr pAction)const ;
	//OdGePoint3d horizontalEndExtensionPoint(void) ;
	double horizontalEndOvershoot(OdTvDbAssocActionPtr pAction)const ;
	//OdGePoint3d horizontalEndOvershootPoint(void) ;
	double horizontalStartExtension(const OdTvDbAssocActionPtr pAction)const ;
	//OdGePoint3d horizontalStartExtensionPoint(void) ;
	double horizontalStartOvershoot(OdTvDbAssocActionPtr pAction)const ;
	//OdGePoint3d horizontalStartOvershootPoint(void) ;
	//bool isCenterCrossTooLarge(enum AcCenterMarkSubEntType)const ;
	double rotation(const OdTvDbObjectId &parentActionId)const ;
	//enum OdResult setAllOvershoots(double) ;
	//enum OdResult setCachedCircleRadius(double) ;
  OdResult setCenterPoint(const OdGePoint3d &, const OdTvDbObjectId &parentActionId);
	enum OdResult setCrossHairGapExpression(OdString const &, OdTvDbAssocActionPtr pAction) ;
	enum OdResult setCrossHairLengthExpression(OdString const &, OdTvDbAssocActionPtr pAction) ;
	enum OdResult setExtensionLinesVisibility(OdDb::Visibility, OdTvDbAssocActionPtr pAction) ;
	enum OdResult setHorizontalEndExtension(double, OdTvDbAssocActionPtr pAction) ;
	enum OdResult setHorizontalEndOvershoot(double, OdTvDbAssocActionPtr pAction);
	enum OdResult setHorizontalStartExtension(double, OdTvDbAssocActionPtr pAction) ;
	enum OdResult setHorizontalStartOvershoot(double , OdTvDbAssocActionPtr pAction);
	enum OdResult setRotation(double, const OdTvDbObjectId parentActionId) ;
	//enum OdResult setSubEntVisibility(enum AcCenterMarkSubEntType,bool) ;
	enum OdResult setVerticalEndExtension(double, OdTvDbAssocActionPtr pActio) ;
	enum OdResult setVerticalEndOvershoot(double, OdTvDbAssocActionPtr pAction) ;
	enum OdResult setVerticalStartExtension(double, OdTvDbAssocActionPtr pAction) ;
	enum OdResult setVerticalStartOvershoot(double, OdTvDbAssocActionPtr pAction) ;
	//void updateCachedCircleRadius(void) ;
	double verticalEndExtension(const OdTvDbAssocActionPtr pAction)const ;
	//OdGePoint3d verticalEndExtensionPoint(void) ;
	double verticalEndOvershoot(OdTvDbAssocActionPtr pAction)const ;
	//OdGePoint3d verticalEndOvershootPoint(void) ;
	double verticalStartExtension(const OdTvDbAssocActionPtr pAction)const ;
	//OdGePoint3d verticalStartExtensionPoint(void) ;
	double verticalStartOvershoot(OdTvDbAssocActionPtr pAction) const ;
	//OdGePoint3d verticalStartOvershootPoint(void) ;
	//static enum SmartCenterType wrapperCenterType(void);
  ////////////////////////////////////////////////////////////////////// from Arx for parent classes
  /** \details
  This is the notification call of the corresponding evaluate() method
  of the parent class that owns this action body.
  */
  virtual void evaluateOverride(OdTvDbObjectId parentActionId);

  /** \details
  Creates associative Center Mark: action, action body, dependencies etc.
  */
  static OdResult createInstance(
    const OdTvDbFullSubentPath subentPath,
    OdTvDbObjectId& centerMarkId,
    OdTvDbObjectId& actionBodyId);
  protected:
    /*!DOM*/
    //OdTvDbSmartCenterMarkParametersPtr m_pParams;
};

#include "TD_PackPop.h"

#endif
