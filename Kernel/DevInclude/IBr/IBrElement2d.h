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
#ifndef IBRELEMENT2D_H_INCLUDED
#define IBRELEMENT2D_H_INCLUDED

#include "IBrElement.h"
#include "Ge/GeVector3d.h"
#include "Ge/GePoint3d.h"
#include "Ge/GePoint2d.h"

class OdIBrMesh2d;
class OdIBrNode;

class OdIBrElement2d : public OdIBrElement
{
public:
  virtual OdBrErrorStatus getNormal (OdGeVector3d& normal) const = 0;
  virtual OdIBrMesh2d *parent() = 0;
  virtual void next(const OdIBrNode *pFirstChild,  OdIBrNode * & pCurChild) = 0;
  virtual OdBrErrorStatus getSurfaceNormal(OdGeVector3d& normal) const = 0;
  virtual OdBrErrorStatus getParamPoint(OdGePoint3d &point3D, OdGePoint2d &point2D) const = 0;
};


#endif

