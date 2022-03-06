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

#ifndef DbAssocOrdinateDimActionBody_INCLUDED_
#define AssocOrdinateDimActionBody_INCLUDED_ /*!DOM*/

#include "DbAssocRotatedDimActionBody.h"
#include "DbGeomRef.h"

#include "TD_PackPush.h"

/** \details
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdDbAssocOrdinateDimActionBody : public OdDbAssocAnnotationActionBody
{
public:
  ODRX_DECLARE_MEMBERS(OdDbAssocOrdinateDimActionBody);

  /** \details
  Constructor creates an instance of this class.
  */
  OdDbAssocOrdinateDimActionBody(bool createImpObj = true);

  /** \details
  Destructor destroys an instance of this class.
  */
  virtual ~OdDbAssocOrdinateDimActionBody();
};

typedef OdSmartPtr<OdDbAssocOrdinateDimActionBody> OdDbAssocOrdinateDimActionBodyPtr;

#include "TD_PackPop.h"

#endif


