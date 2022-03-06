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

#pragma once

#ifndef OdTvDbAssocSurfaceActionBody_INCLUDED_
#define OdTvDbAssocSurfaceActionBody_INCLUDED_ /*!DOM*/

#include "DbAssocParamBasedActionBody.h"
#include "DbGeomRef.h"

#include "TD_PackPush.h"

/** \details
This class represents the base class OdTvDbAssocSurfaceActionBody for the Assoc surfaces bodies.

Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT ODRX_ABSTRACT  OdTvDbAssocSurfaceActionBody : public OdTvDbAssocParamBasedActionBody
{
public:
	ODRX_DECLARE_MEMBERS(OdTvDbAssocSurfaceActionBody);

	/** \details
	Constructor creates an instance of this class.
	*/
	OdTvDbAssocSurfaceActionBody() {};

	/** \details
	This is the notification call of the corresponding evaluate() method
	of the parent class that owns this action body.
	*/
	virtual void evaluateOverride(void);

	enum OdResult setGeometryParam(double newValue, const OdString& paramName, bool assertEnable = true);
	enum OdResult getGeometryParam(double& value, const OdString& paramName) const;
}; 

/** \details
The typified smart pointer. This template class is specialization of the OdSmartPtr class
for the OdTvDbAssocSurfaceActionBody class.

\sa
<link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbAssocSurfaceActionBody> OdTvDbAssocSurfaceActionBodyPtr;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** \details
  <group Contraint_Classes>
  Library: Source code provided.
*/
class DBCONSTRAINTS_EXPORT ODRX_ABSTRACT OdTvDbAssocPathBasedSurfaceActionBody : public OdTvDbAssocSurfaceActionBody
{
public:
	ODRX_DECLARE_MEMBERS(OdTvDbAssocPathBasedSurfaceActionBody);

	/** \details
	Constructor creates an instance of this class.
	*/
	OdTvDbAssocPathBasedSurfaceActionBody(bool createImpObj = true) {};

	/** \details
	Destructor destroys an instance of this class.
	*/
	virtual ~OdTvDbAssocPathBasedSurfaceActionBody() {};
}; 

typedef OdSmartPtr<OdTvDbAssocPathBasedSurfaceActionBody> OdTvDbAssocPathBasedSurfaceActionBodyPtr;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "TD_PackPop.h"

#endif

