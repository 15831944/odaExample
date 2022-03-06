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
#include "IfcPropertySetFiller.h"

using namespace OdIfc;

ODRX_CONS_DEFINE_MEMBERS(IfcPropertySetFiller, IfcBuilder, RXIMPL_CONSTR);

OdSmartPtr<IfcPropertySetFiller> IfcPropertySetFiller::createObject(
  ExIfcModelFiller *filler,
  OdIfc::OdIfcEntityPtr objectDefinition)
{
  OdSmartPtr<IfcPropertySetFiller> res = IfcPropertySetFiller::desc()->create();
  res->setFiller(filler);
  res->m_objectDefinition = objectDefinition;
  return res;
}

IfcPropertySetFiller& IfcPropertySetFiller::appendPropertySingleValue(const OdAnsiString &name, OdRxValue val, const OdAnsiString &typePath)
{
  OdIfc::OdIfcEntityPtr propertySingleValue = filler()->model()->createEntityInstance("ifcpropertysinglevalue");
  propertySingleValue->putAttr("name", name);

  // TODO: Types checking
  OdRxSpecifiedValueType *vt = new OdRxSpecifiedValueType(val.type(), typePath);
  if (propertySingleValue->putAttr("nominalvalue", OdRxValue(*vt, val)))
  {
    m_idProperties.append(
      filler()->model()->appendEntityInstance(propertySingleValue));
  }
  delete vt;

  /*if (val.type() == OdRxValueType::Desc<OdAnsiString>::value())
  {
    //OdRxSpecifiedValueType vt(val.type(), typePath);
    OdRxSpecifiedValueType *vt = new OdRxSpecifiedValueType(val.type(), typePath);
    OdRxValue supVal(*vt, val);
    propertySingleValue->putAttr(OdIfc::kNominalValue, supVal);
  }
  if (val.type() == OdRxValueType::Desc<double>::value())
  {
    OdRxSpecifiedValueType vt(val.type(), typePath);
    OdRxValue supVal(vt, val);
    propertySingleValue->putAttr(OdIfc::kNominalValue, supVal);
  }
  if (val.type() == OdRxValueType::Desc<int>::value())
  {
    OdRxSpecifiedValueType vt(val.type(), typePath);
    OdRxValue supVal(vt, val);
    propertySingleValue->putAttr(OdIfc::kNominalValue, supVal);
  }
  if (val.type() == OdRxValueType::Desc<bool>::value())
  {
    OdRxSpecifiedValueType vt(val.type(), typePath);
    OdRxValue supVal(vt, val);
    propertySingleValue->putAttr(OdIfc::kNominalValue, supVal);
  }*/

  
  return *this;
}

OdIfc::OdIfcEntityPtr IfcPropertySetFiller::createPropertySet(const OdAnsiString &name)
{
  OdIfc::OdIfcEntityPtr propertySet = filler()->model()->createEntityInstance("ifcpropertyset");
  OdIfc::Utils::assignGlobalId(propertySet);
  propertySet->putAttr("ownerhistory", OdDAIObjectId(filler()->ownerHistory()->id()));
  propertySet->putAttr("name", name);
  propertySet->putAttr("hasproperties", m_idProperties);
  filler()->model()->appendEntityInstance(propertySet);
  m_idProperties.clear();

  return filler()->appendRelDefinesByProperties(propertySet, m_objectDefinition);
}

