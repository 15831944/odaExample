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
#include "IfcQuantitySetFiller.h"

using namespace OdIfc;

ODRX_CONS_DEFINE_MEMBERS(IfcQuantitySetFiller, IfcBuilder, RXIMPL_CONSTR);

OdSmartPtr<IfcQuantitySetFiller> IfcQuantitySetFiller::createObject(
  ExIfcModelFiller *filler,
  OdIfc::OdIfcEntityPtr objectDefinition)
{
  OdSmartPtr<IfcQuantitySetFiller> res = IfcQuantitySetFiller::desc()->create();
  res->setFiller(filler);
  res->m_objectDefinition = objectDefinition;
  return res;
}

IfcQuantitySetFiller& IfcQuantitySetFiller::appendQuantityCount(
  const OdAnsiString &name,
  double countValue, const OdAnsiString &formula)
{
  OdIfc::OdIfcEntityPtr quantityCount = filler()->model()->createEntityInstance("ifcquantitycount");
  quantityCount->putAttr(OdIfc::kName, name);
  quantityCount->putAttr(OdIfc::kCountValue, countValue);
  m_idProperties.append(
    filler()->model()->appendEntityInstance(quantityCount));
  return *this;
}

IfcQuantitySetFiller& IfcQuantitySetFiller::appendQuantityLength(
  const OdAnsiString &name,
  double lengthValue, const OdAnsiString &formula)
{
  OdIfc::OdIfcEntityPtr quantityCount = filler()->model()->createEntityInstance("ifcquantitylength");
  quantityCount->putAttr(OdIfc::kName, name);
  quantityCount->putAttr(OdIfc::kLengthValue, lengthValue);
  m_idProperties.append(
    filler()->model()->appendEntityInstance(quantityCount));
  return *this;
}

OdIfc::OdIfcEntityPtr IfcQuantitySetFiller::createQuantitySet(const OdAnsiString &name)
{
  OdIfc::OdIfcEntityPtr quantitySet = filler()->model()->createEntityInstance("ifcelementquantity");
  OdIfc::Utils::assignGlobalId(quantitySet);
  quantitySet->putAttr("ownerhistory", OdDAIObjectId(filler()->ownerHistory()->id()));
  quantitySet->putAttr("name", name);
  quantitySet->putAttr("quantities", m_idProperties);
  filler()->model()->appendEntityInstance(quantitySet);
  m_idProperties.clear();

  return filler()->appendRelDefinesByProperties(quantitySet, m_objectDefinition);
}

