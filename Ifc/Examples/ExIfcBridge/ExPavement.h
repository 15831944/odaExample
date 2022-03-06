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

#ifndef _EX_IFCBRIDGE_PAVEMENT_H
#define _EX_IFCBRIDGE_PAVEMENT_H

#include "IfcRepresentationBuilder.h"

class ExPavement : public IfcRepresentationAdapter
{
  OdGePoint3d m_startPoint;
  OdGePoint3d m_endPoint;
  OdAnsiString m_name;
  OdAnsiString m_styleName;
  double m_xdim;
  double m_ydim;

  OdIfc::OdIfcEntityPtr createProfile(
    const OdAnsiString &name = "");

  virtual OdIfc::OdIfcEntityPtr subProcess();

public:

  ExPavement(
    const OdGePoint3d &startPoint,
    const OdGePoint3d &endPoint,
    const OdAnsiString &name,
    double xdim,
    double ydim,
    const OdAnsiString &styleName
  );

};

#endif // #ifndef _EX_IFCBRIDGE_PAVEMENT_H
