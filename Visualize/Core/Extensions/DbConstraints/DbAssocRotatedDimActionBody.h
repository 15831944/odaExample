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

#ifndef OdTvDbAssocRotatedDimActionBody_INCLUDED_
#define OdTvDbAssocRotatedDimActionBody_INCLUDED_ /*!DOM*/

#include "DbAssocActionBody.h"
#include "DbGeomRef.h"

#include "TD_PackPush.h"

/** \details
This class represents the base class OdTvDbAssocAnnotationActionBody for the Assoc Dim action bodies.

Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT ODRX_ABSTRACT OdTvDbAssocAnnotationActionBody : public OdTvDbAssocActionBody
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocAnnotationActionBody);

  /** \details
  Constructor creates an instance of this class.
  */
  OdTvDbAssocAnnotationActionBody();

  /** \details
  This is the notification call of the corresponding evaluate() method
  of the parent class that owns this action body.
  */
  virtual void evaluateOverride(void);

  void setAssocDependencyID(OdTvDbObjectId objID);
  void setActionParamID1(OdTvDbObjectId objID);
  void setActionParamID2(OdTvDbObjectId objID);
};

/** \details
The typified smart pointer. This template class is specialization of the OdSmartPtr class
for the OdTvDbAssocAnnotationActionBody class.

\sa
<link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbAssocAnnotationActionBody> OdTvDbAssocAnnotationActionBodyPtr;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** \details
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocRotatedDimActionBody : public OdTvDbAssocAnnotationActionBody
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocRotatedDimActionBody);

  /** \details
  Constructor creates an instance of this class.
  */
  OdTvDbAssocRotatedDimActionBody(bool createImpObj = true);

  /** \details
  Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbAssocRotatedDimActionBody();

  //const OdTvDbSmartCenterMarkParametersPtr parameters() const;
  //OdTvDbSmartCenterMarkParametersPtr& parameters();
    virtual void composeForLoad(OdDb::SaveType format, OdDb::DwgVersion version, OdTvDbAuditInfo* pAuditInfo);
  /** \details
  Creates associative AssocRotatedDim: action, action body, dependencies etc.
  */
  static OdResult createInstance(
	  const OdTvDbFullSubentPathArray entPathArray,
	  OdGePoint3dArray ptsSelected,
	  OdTvDbObjectId& actionBodyId);
};

typedef OdSmartPtr<OdTvDbAssocRotatedDimActionBody> OdTvDbAssocRotatedDimActionBodyPtr;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "TD_PackPop.h"

#endif

