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

#ifndef _PRCCRVNURBS3d_INCLUDED_
#define _PRCCRVNURBS3d_INCLUDED_ 
 

#include "PrcCurve3d.h"
#include "Ge/GeNurbCurve3d.h"

/** \details
<group PRC_Curve_Classes>

Class implements a three-dimentional non-uniform rational bspline (NURBS) curve.
*/
class PRC_TOOLKIT OdPrcNurbsCurve3d : public OdPrcCurve3d
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_CRV(OdPrcNurbsCurve3d)
  //DOM-IGNORE-END
};
SMARTPTR(OdPrcNurbsCurve3d);

#endif // _PRCCRVNURBS3d_INCLUDED_

