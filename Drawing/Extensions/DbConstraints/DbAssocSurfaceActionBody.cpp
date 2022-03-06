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
#include "DbImpAssocExtrudedSurfaceActionBody.h"
#include "DbImpAssocOffsetSurfaceActionBody.h"

ODRX_NO_CONS_DEFINE_MEMBERS_ALTNAME(OdDbAssocSurfaceActionBody, OdDbAssocParamBasedActionBody, L"AcDbAssocSurfaceActionBody")
ODRX_NO_CONS_DEFINE_MEMBERS_ALTNAME(OdDbAssocPathBasedSurfaceActionBody, OdDbAssocSurfaceActionBody, L"AcDbAssocPathBasedSurfaceActionBody")

void OdDbAssocSurfaceActionBody::evaluateOverride()
{
	static_cast<OdDbImpAssocSurfaceActionBody *>(m_pImpObj)->evaluateOverride(parentAction());
}

enum OdResult OdDbAssocSurfaceActionBody::setGeometryParam(double newValue, const OdString& paramName, bool assertEnable)
{
	if (assertEnable)
		assertWriteEnabled();

	const OdDbEvalVariantPtr value = OdDbEvalVariant::init(newValue);
	OdString emptyStr("");
	return setValueParam(paramName, *value.get(), OD_T(""), OD_T(""), emptyStr, false, 0);
	//return static_cast<OdDbImpCenterMarkActionBody *>
	//  (m_pImpObj)->setHorizontalStartOvershoot(newovershoot, parentAction());
}

enum OdResult OdDbAssocSurfaceActionBody::getGeometryParam(double& newValue, const OdString& paramName) const
{
	OdDbEvalVariantPtr value = OdDbEvalVariant::init(double(1));
	OdString expression(""), evaluatorId("");
	const OdResult ret = getValueParam(paramName, *value.get(), expression, evaluatorId, 0);

	if (ret == eOk)
		newValue = value->getDouble();

	return ret;
}

