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
#include "NextCodeDefs.h"
#include "DbAssocArrayModifyActionBody.h"
#include "DbBlockTableRecord.h"
#include "DbBlockTable.h"
#include "DbAssocDependency.h"
#include "DbLinetypeTable.h"
#include "DbImpAssocRestoreEntityStateActionBody.h"
#include "DbObjectId.h"
#include "Ge/GeLineSeg3d.h"
#include "Ge/GeCircArc3d.h"
#include "DbAssocNetwork.h"
#include "DbDimStyleTable.h"
#include "DbDimStyleTableRecord.h"

//////////////////////////////////////////////////////////////////////////

OdDbImpAssocRestoreEntityStateActionBody::OdDbImpAssocRestoreEntityStateActionBody()
{
	m_undefined = 0;
}

OdDbImpAssocRestoreEntityStateActionBody::~OdDbImpAssocRestoreEntityStateActionBody()
{
}

OdResult OdDbImpAssocRestoreEntityStateActionBody::dwgInFields(OdDbDwgFiler* pFiler)
{
	OdResult res = OdDbImpAssocActionBody::dwgInFields(pFiler);

	if (res != eOk)
		return res;

	m_undefined = pFiler->rdInt32();  
	m_undefObjectDepId = pFiler->rdSoftPointerId();

	return res;
}

void OdDbImpAssocRestoreEntityStateActionBody::dwgOutFields(OdDbDwgFiler* pFiler) const
{
	OdDbImpAssocActionBody::dwgOutFields(pFiler);
	pFiler->wrInt32(m_undefined);
	pFiler->wrSoftPointerId(m_undefObjectDepId);
}

OdResult OdDbImpAssocRestoreEntityStateActionBody::dxfInFields(OdDbDxfFiler* pFiler)
{
	OdResult res = OdDbImpAssocActionBody::dxfInFields(pFiler);

	if (res != eOk)
		return res;

	if (!pFiler->atSubclassData(OdDbAssocRestoreEntityStateActionBody::desc()->name()))
	{
		ODA_FAIL_ONCE();
		return eMakeMeProxy;
	}

	NEXT_CODE(90)
	m_undefined = pFiler->rdUInt32();
	NEXT_CODE(330)
	m_undefObjectDepId = pFiler->rdObjectId();


	return eOk;
}

void OdDbImpAssocRestoreEntityStateActionBody::dxfOutFields(OdDbDxfFiler* pFiler) const
{
	OdDbImpAssocActionBody::dxfOutFields(pFiler);

	pFiler->wrSubclassMarker(OdDbAssocRestoreEntityStateActionBody::desc()->name());
	pFiler->wrUInt32(90, m_undefined);
	pFiler->wrObjectId(330, m_undefObjectDepId);
}

//const OdDbSmartCenterMarkParametersPtr OdDbImpAssocRestoreEntityStateActionBody::parameters() const
//{
//  return m_pParams;
//}
//
//OdDbSmartCenterMarkParametersPtr& OdDbImpAssocRestoreEntityStateActionBody::parameters()
//{
//  return m_pParams;
//}
//

//////////////////////////////////////////////////////////////////////////
