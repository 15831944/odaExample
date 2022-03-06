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

#include "ExIfcModelFiller.h"
#include "IfcRailwayBuilder.h"
#include "IfcEntity.h"

using namespace OdIfc;

ODRX_CONS_DEFINE_MEMBERS(IfcRailwayBuilder, IfcBuilder, RXIMPL_CONSTR);

//
// TODO: Move to separate .cpp file
//
OdIfc::OdIfcEntityPtr IfcBuilder::appendProduct(const char *type, const OdAnsiString &name)
{
  OdIfc::OdIfcEntityPtr product = filler()->model()->createEntityInstance(type);
  OdIfc::Utils::assignGlobalId(product);
  product->putAttr("ownerhistory", OdDAIObjectId(filler()->ownerHistory()->id()));
  product->putAttr("name", name);
  return product;
};

OdIfc::OdIfcEntityPtr IfcBuilder::appendPoint(const OdGePoint2d &p)
{
  return m_filler->createCartesianPoint2D(p);
}

OdSmartPtr<IfcRailwayBuilder> IfcRailwayBuilder::createObject(ExIfcModelFiller *filler, const OdAnsiString &name)
{
  OdSmartPtr<IfcRailwayBuilder> res = IfcRailwayBuilder::desc()->create();
  res->setFiller(filler);
  res->m_name = name;
  return res;
}

OdIfc::OdIfcEntityPtr IfcRailwayBuilder::appendIfcRailway()
{
  if (!m_railway.isNull())
  {
    return m_railway;
  }

  m_railway = appendProduct("ifcrailway", m_name);
  filler()->appendRelAggregates(filler()->site(), m_railway);

  return m_railway;
}

OdIfc::OdIfcEntityPtr IfcRailwayBuilder::appendRail(const OdAnsiString &name, RailType railType)
{
  if (m_railway.isNull())
  {
    ODA_ASSERT("No Railway found for IfcRailwayBuilder.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfc::OdIfcEntityPtr rail = appendProduct("ifcrail", name);

  static char* railTypes[] = {
    "RACKRAIL",
    "BLADE",
    "GUARDRAIL",
    "STOCKRAIL",
    "CHECKRAIL",
    "RAIL",
    "USERDEFINED",
    "NOTDEFINED"
  };

  rail->putAttr("predefinedtype", (const char*)railTypes[railType]);

  filler()->addRelAggregates(m_railway, rail);
  return rail;
}
