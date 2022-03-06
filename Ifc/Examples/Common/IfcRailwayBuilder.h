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

#ifndef _IFC_RAILWAY_BUILDER_H
#define _IFC_RAILWAY_BUILDER_H

#include "IfcBuilder.h"

class IfcRailwayBuilder : public IfcBuilder
{
public:

  enum RailType
  {
    kRACKRAIL,
    kBLADE,
    kGUARDRAIL,
    kSTOCKRAIL,
    kCHECKRAIL,
    kRAIL,
    kUSERDEFINED,
    kNOTDEFINED,
  };

protected:

  OdIfc::OdIfcEntityPtr m_railway;
  OdAnsiString m_name;

  static OdSmartPtr<IfcRailwayBuilder> createObject(ExIfcModelFiller *filler, const OdAnsiString &name);

  OdIfc::OdIfcEntityPtr appendIfcRailway();

public:

  ODRX_DECLARE_MEMBERS(IfcRailwayBuilder);

  OdIfc::OdIfcEntityPtr railway() { return m_railway; };

  OdIfc::OdIfcEntityPtr appendRail(const OdAnsiString &name, RailType railType);

  friend class ExIfcModelFiller;
};
typedef OdSmartPtr<IfcRailwayBuilder> IfcRailwayBuilderPtr;

#endif // _IFC_RAILWAY_BUILDER_H
