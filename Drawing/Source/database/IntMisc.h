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

#ifndef _OD_INTMISC_H_
#define _OD_INTMISC_H_

#include "Ge/GePoint3d.h"

TOOLKIT_EXPORT OdDb::LineWeight LwEnumToActualLineweight(OdInt16 theEnum);
TOOLKIT_EXPORT OdInt16 ActualLineweightToLwEnum(OdDb::LineWeight weight);

//bool operator==(OdGePoint3d& p1, OdGePoint3d& p2) { return p1.x == p2.x && p1.y == p2.y && p1.z == p2.z; }

void SetPoint3UnderTol(OdGePoint3d& p, double tolerance, double value);


#endif
