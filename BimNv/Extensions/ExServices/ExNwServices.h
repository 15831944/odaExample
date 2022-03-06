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
#ifndef _EX_NWSERVICES_H_
#define _EX_NWSERVICES_H_

#include "ExSystemServices.h"

/** *********************************************************************
*/
/* Define a Custom Services class.                                      */
/*                                                                      */
/* Combines the platform dependent functionality of                     */
/* ExSystemServices and ExHostAppServices                               */ 
/** *********************************************************************
*/
// TODO: Redesign ExSystemServices - may be template : ExSystemServices<TBaseClass>.
// ExSystemServices is inherited from OdNwSystemServices
// and can not be used without ODA BimNv SDK database,
// but OdNwSystemServices has no methods - only constructor/destructor.
//

/** \details
  <group Nw_Extension_Classes>

  This class implements the root run-time service object for an NwInterop application.
*/
class OdExNwSystemServices : public ExSystemServices
{
public:
  OdExNwSystemServices() {}
};
#endif //_EX_NWSERVICES_H_
