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

#ifndef _EX_IFCBRIDGE_PIER_H
#define _EX_IFCBRIDGE_PIER_H

#include "IfcRepresentationBuilder.h"

class ExPier : public IfcRepresentationAdapter
{
  double m_fullHeight;
  double m_xdimColumn;
  double m_ydimColumn;
  double m_fillet_r;
  double m_xdimCap;
  double m_ydimCap;
  double m_capHeight;
  double m_capWing;
  double m_bearingThickness;

  virtual OdIfc::OdIfcEntityPtr subProcess();

public:

  ExPier(
    const OdGeMatrix3d &objectPlacement,
    double fullHeight,
    double xdimColumn,
    double ydimColumn,
    double fillet_r,
    double xdimCap,
    double ydimCap,
    double capHeight,
    double capWing,
    double bearingThickness);

};

#endif // #ifndef _EX_IFCBRIDGE_PIER_H
