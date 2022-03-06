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

#ifndef _EX_IFCBRIDGE_GIRDER2_H
#define _EX_IFCBRIDGE_GIRDER2_H

#include "IfcRepresentationBuilder.h"

class ExGirder2 : public IfcRepresentationAdapter
{
  OdAnsiString m_name;
  double m_xdim;
  double m_ydim;
  double m_plateThickness;
  double m_wingWidth;
  double m_bearingDist;
  double m_bearingXDim;
  double m_girderDepth;

  OdIfc::OdIfcEntityPtr createDeckProfile(
    const OdAnsiString &name);

  OdIfc::OdIfcEntityPtr createGirderProfileBig(
    const OdAnsiString &name);
  OdIfc::OdIfcEntityPtr createGirderProfileSmall(
    const OdAnsiString &name);

  virtual OdIfc::OdIfcEntityPtr subProcess();

public:

  ExGirder2(
    const OdGeMatrix3d &objectPlacement,
    const OdAnsiString &name,
    double xdim,
    double ydim,
    double plateThickness,
    double wingWidth,
    double bearingDist,
    double bearingXDim,
    double girderDepth);

};

#endif // #ifndef _EX_IFCBRIDGE_GIRDER2_H
