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

#ifndef OdTvDbAssocBlendSurfaceActionBody_INCLUDED_
#define OdTvDbAssocBlendSurfaceActionBody_INCLUDED_ /*!DOM*/
#include "DbAssocSurfaceActionBody.h"
#include "TD_PackPush.h"

/** \details
  <group Contraint_Classes>
  
  This class represents the base class OdTvDbAssocBlendSurfaceActionBody for the action bodies.

  Library: Source code provided.
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocBlendSurfaceActionBody : public OdTvDbAssocPathBasedSurfaceActionBody
{
public:
	ODRX_DECLARE_MEMBERS(OdTvDbAssocBlendSurfaceActionBody);

	/** \details
	Constructor creates an instance of this class.
	*/
	OdTvDbAssocBlendSurfaceActionBody(bool createImpObj = true);

	/** \details
	Destructor destroys an instance of this class.
	*/
	virtual ~OdTvDbAssocBlendSurfaceActionBody();

	//const OdTvDbSmartCenterMarkParametersPtr parameters() const;
	//OdTvDbSmartCenterMarkParametersPtr& parameters();
	//virtual void composeForLoad(OdDb::SaveType format, OdDb::DwgVersion version, OdTvDbAuditInfo* pAuditInfo);
	/** \details
	Creates associative AssocRotatedDim: action, action body, dependencies etc.
	*/
  /** \details
  Creates associative blend: action, action body, dependencies etc.
  */
  static OdResult createInstance(
    const OdTvDbFullSubentPathArray entPathArray,
    OdGePoint3dArray ptsSelected,
    OdTvDbObjectId& centerLineId,
    OdTvDbObjectId& actionBodyId);

	///// <summary><para> 
	///// Get continuity of start profile
	///// </para><para>
  OdInt16  startEdgeContinuity(const OdTvDbAssocActionPtr pAction, OdString& expression, OdString& evaluatorId) const;

	///// <summary><para> 
	///// Set continuity of start profile of the surface
	///// </para><para>
  OdResult  setStartEdgeContinuity(OdTvDbAssocActionPtr pAction, OdInt16 value, const OdString& expression, const OdString& evaluatorId);

	///// <summary><para> 
	///// Get continuity of end profile
	///// </para><para>
  OdInt16  endEdgeContinuity(const OdTvDbAssocActionPtr pAction, OdString& expression, OdString& evaluatorId) const;
  OdArray<OdInt16>  arrayEdgeContinuity(const OdTvDbAssocActionPtr pAction, OdString& expression, OdString& evaluatorId) const;
  OdResult  setArrayEdgeContinuity(const OdTvDbAssocActionPtr pAction, OdArray<OdInt16>& values, OdString& expression, OdString& evaluatorId);

  ///// <summary><para> 
	///// Set continuity of end profile
	///// </para><para>
  OdResult  setEndEdgeContinuity(OdTvDbAssocActionPtr pAction, OdInt16 value, const OdString& expression, const OdString& evaluatorId);

	///// <summary><para> 
	///// Get bulge factor of end profil
	///// </para><para>
  double  startEdgeBulge(const OdTvDbAssocActionPtr pAction, OdString& expression, OdString& evaluatorId) const;
  OdArray<double>  arrayEdgeBulge(const OdTvDbAssocActionPtr pAction, OdString& expression, OdString& evaluatorId) const;
  OdResult  setArrayEdgeBulge(const OdTvDbAssocActionPtr pAction, OdArray<double>& values, OdString& expression, OdString& evaluatorId);

	///// <summary><para> 
	///// Set bulge factor
	///// </para><para>
	OdResult  setStartEdgeBulge(OdTvDbAssocActionPtr pAction, double value, const OdString& expression, const OdString& evaluatorId);

	///// <summary><para> 
	///// Get bulge factor of end profile
	///// </para><para>
  double  endEdgeBulge(const OdTvDbAssocActionPtr pAction, OdString& expression, OdString& evaluatorId) const;

	///// <summary><para> 
	///// Set bulge factor of end profile
	///// </para><para>
  OdResult  setEndEdgeBulge(OdTvDbAssocActionPtr pAction, double value, const OdString& expression, const OdString& evaluatorId);
};


typedef OdSmartPtr<OdTvDbAssocBlendSurfaceActionBody> OdTvDbAssocBlendSurfaceActionBodyPtr;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "TD_PackPop.h"

#endif


