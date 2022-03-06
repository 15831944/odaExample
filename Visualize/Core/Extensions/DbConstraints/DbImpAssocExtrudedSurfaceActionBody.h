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
#ifndef DbImpAssocExtrudedSurfaceActionBody_INCLUDED_
#define DbImpAssocExtrudedSurfaceActionBody_INCLUDED_ /*!DOM*/

#include "DbImpAssocPathBasedSurfaceActionBody.h"
#include "TD_PackPush.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** \details
This class represents the custom implementation of the action body based on AnnotationActionBody.

Library: Source code provided.
<group Contraint_Classes>
*/

class DBCONSTRAINTS_EXPORT OdTvDbImpAssocExtrudedSurfaceActionBody : public OdTvDbImpAssocPathBasedSurfaceActionBody
{
public:
	/** \details
	Constructor creates an instance of this class.
	*/
	OdTvDbImpAssocExtrudedSurfaceActionBody();

	/** \details
	Destructor destroys an instance of this class.
	*/
	virtual ~OdTvDbImpAssocExtrudedSurfaceActionBody();

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

	//virtual void composeForLoad(OdTvDbObject *pObject, OdDb::SaveType format, OdDb::DwgVersion version, OdTvDbAuditInfo* pAuditInfo);
	/** \details
	This is the notification call of the corresponding evaluate() method
	of the parent class that owns this action body.
	*/
	virtual void evaluateOverride(OdTvDbObjectId parentActionId);

  /// <summary><para> 
  /// Set taper angle ( correspondent to draft angle in OdTvDbSweepOptions )
  /// </para><para>
  OdResult setTaperAngle(OdTvDbAssocActionPtr pAction, OdDouble dTaperAngle, const OdString& expression/* = OdString()*/,
    const OdString& evaluatorId/* = OdString()*/);

  /// <summary><para> 
  /// Get taper angle ( correspondent to draft angle in OdTvDbSweepOptions )
  /// </para><para>
  OdDouble taperAngle(const OdTvDbAssocActionPtr pAction, OdString& expression/* = dummyString()*/, OdString& evaluatorId /*= dummyString()*/) const;

  /// <summary><para> 
  /// Set extrusion height of the surface
  /// </para><para>
  OdResult setHeight(OdTvDbAssocActionPtr pAction, OdDouble dHeight, const OdString& expression/* = OdString()*/,
    const OdString& evaluatorId /*= OdString()*/);

  /// <summary><para> 
  /// Get extrusion height of the surface
  /// </para><para>
  OdDouble            height(const OdTvDbAssocActionPtr pAction, OdString& expression /*= dummyString()*/, OdString& evaluatorId/* = dummyString()*/) const;

	//virtual OdStringArray compareWith(const OdTvDbImpAssocActionBody *bodyIDToCompare, OdDb::DwgVersion filerVersion = OdDb::kDHL_CURRENT) const;
private:
	OdUInt32 m_unknownInt32;
};

#include "TD_PackPop.h"

#endif
