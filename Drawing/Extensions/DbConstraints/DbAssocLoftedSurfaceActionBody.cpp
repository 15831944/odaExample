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

#include "OdaCommon.h"
#include "DbAssocSurfaceActionBody.h"
#include "DbAssocLoftedSurfaceActionBody.h"
#include "DbImpAssocLoftedSurfaceActionBody.h"
#include "DbImpAssocExtrudedSurfaceActionBody.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ODRX_DEFINE_MEMBERS_EX(OdDbAssocLoftedSurfaceActionBody,      // ClassName
	OdDbAssocPathBasedSurfaceActionBody, // ParentClass
	DBOBJECT_CONSTR,               // DOCREATE
	OdDb::kDHL_1024,               // DwgVer
								   //OdDb::kMRelease125,              // MaintVer
	OdDb::kMRelease25,              // MaintVer
	1025,                          // nProxyFlags 
	L"AcDbAssocLoftedSurfaceActionBody",   // DWG class name
	L"ACDBASSOCLOFTEDSURFACEACTIONBODY",   // DxfName
	L"ObjectDBX Classes",         // AppName
	OdRx::kMTLoading | OdRx::kHistoryAware);

OdDbAssocLoftedSurfaceActionBody::OdDbAssocLoftedSurfaceActionBody(bool bCreateImpl)
{
	if (bCreateImpl)
		m_pImpObj = static_cast<OdDbImpAssocActionBody*>(new OdDbImpAssocLoftedSurfaceActionBody());
	else
		m_pImpObj = NULL;
}

OdDbAssocLoftedSurfaceActionBody::~OdDbAssocLoftedSurfaceActionBody()
{
	// via base class // delete m_pImpObj;
}

//void OdDbAssocRotatedDimActionBody::composeForLoad(OdDb::SaveType format, OdDb::DwgVersion version, OdDbAuditInfo* pAuditInfo)
//{
//	static_cast<OdDbImpAssocRotatedDimActionBody *>(m_pImpObj)->composeForLoad(this, format, version, pAuditInfo);
//}
//
//
const OdDbAssocLoftParametersPtr OdDbAssocLoftedSurfaceActionBody::parameters() const
{
  return static_cast<OdDbImpAssocLoftedSurfaceActionBody *>(m_pImpObj)->parameters();
}

OdDbAssocLoftParametersPtr& OdDbAssocLoftedSurfaceActionBody::parameters()
{
  return static_cast<OdDbImpAssocLoftedSurfaceActionBody *>(m_pImpObj)->parameters();
}

OdResult OdDbAssocLoftedSurfaceActionBody::createInstance(
	const OdDbFullSubentPathArray crossSectionsArray,
	const OdDbFullSubentPathArray guideCurves, // TODO
	const OdDbFullSubentPath pathCurve,				// TODO	
	const OdDbLoftOptions& loftOptions,				// TODO
	//const OdArray<int>& continuityArray,
	//const OdArray<double>& bulgeArray,
	//bool bEnabled,
	OdDbObjectId& actionBodyId)
{
	return OdDbImpAssocLoftedSurfaceActionBody::createInstance
		( crossSectionsArray,
			guideCurves,
			pathCurve,
			loftOptions,
			//continuityArray,
			//bulgeArray,
			//bEnabled,
		  actionBodyId);
}

//OdStringArray OdDbAssocRotatedDimActionBody::compareWith(const OdDbObjectId bodyIDToCompare, OdDb::DwgVersion filerVersion /*OdDb::kDHL_CURRENT*/) const
//{
//	OdStringArray retArray;
//	OdDbAssocRotatedDimActionBodyPtr comparedBodyPtr = OdDbAssocRotatedDimActionBody::cast(bodyIDToCompare.openObject());
//
//	if (comparedBodyPtr.isNull())
//	{
//		retArray.append(CS_OBJECT_ERROR);
//		return retArray;
//	}
//
//	OdDbImpAssocRotatedDimActionBody* pImpObjCompared = static_cast<OdDbImpAssocRotatedDimActionBody *>(comparedBodyPtr->m_pImpObj);
//
//	return static_cast<OdDbImpAssocRotatedDimActionBody *>
//		(m_pImpObj)->compareWith(pImpObjCompared);
//}
