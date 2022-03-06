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
#include "IfcBridgeBuilder.h"
#include "IfcEntity.h"
#include "RxValueType.h"
#include "daiSelectValueType.h"

using namespace OdIfc;

ODRX_CONS_DEFINE_MEMBERS(IfcBridgeBuilder, IfcBuilder, RXIMPL_CONSTR);

OdIfc::OdIfcEntityPtr IfcBridgeBuilder::appendIfcBridge()
{
  if (!m_bridge.isNull())
  {
    return m_bridge;
  }

  static char* bridgeTypes[] = {
    "ARCHED",
    "CABLE_STAYED",
    "CANTILEVER",
    "CULVERT",
    "FRAMEWORK",
    "GIRDER",
    "SUSPENSION",
    "TRUSS",
    "USERDEFINED",
    "NOTDEFINED"
  };

  OdAnsiString strBridgeType(bridgeTypes[m_predefinedType]);

  m_bridge = filler()->model()->createEntityInstance("ifcbridge");
  OdIfc::Utils::assignGlobalId(m_bridge);
  m_bridge->putAttr(kOwnerHistory, OdDAIObjectId(filler()->ownerHistory()->id()));
  m_bridge->putAttr(kName, m_name);
  m_bridge->putAttr(kPredefinedType, strBridgeType);

  filler()->appendRelAggregates(filler()->site(), m_bridge);
  return m_bridge;
}

OdSmartPtr<IfcBridgeBuilder> IfcBridgeBuilder::createObject(ExIfcModelFiller *filler, const OdAnsiString &name, Type type)
{
  OdSmartPtr<IfcBridgeBuilder> res = IfcBridgeBuilder::desc()->create();
  res->setFiller(filler);
  res->m_predefinedType = type;
  res->m_name = name;
  return res;
}

OdIfc::OdIfcEntityPtr IfcBridgeBuilder::appendBridgePart(const OdAnsiString &name, OdIfc::OdIfcEntityPtr pParent, PartType partType)
{
  if (partType == kNOTDEFINED_PART_TYPE)
    return OdIfc::OdIfcEntityPtr();

  bool directlyToBridge = (partType == kSUBSTRUCTURE || partType == kSUPERSTRUCTURE || partType == kFOUNDATION);
  if ((pParent.isNull() || pParent == m_bridge))
  {
    if (!directlyToBridge)
    {
      ODA_ASSERT("Can not append this part type directly to IfcBridge.");
      return OdIfc::OdIfcEntityPtr();
    }
  }
  else
  {
    if (directlyToBridge)
    {
      ODA_ASSERT("Can not append this part type directly to IfcFacilityPart.");
      return OdIfc::OdIfcEntityPtr();
    }
  }

  OdIfc::OdIfcEntityPtr bridgePart = filler()->model()->createEntityInstance("ifcfacilitypart");
  OdIfc::Utils::assignGlobalId(bridgePart);
  bridgePart->putAttr(kOwnerHistory, OdDAIObjectId(filler()->ownerHistory()->id()));
  bridgePart->putAttr(kName, name);
  bridgePart->putAttr(kUsageType, OdAnsiString("USERDEFINED"));

  static char* bridgePartTypes[] = {
    "ABUTMENT",
    "DECK",
    "DECK_SEGMENT",
    "FOUNDATION",
    "PIER",
    "PIER_SEGMENT",
    "PYLON",
    "SUBSTRUCTURE",
    "SUPERSTRUCTURE",
    "SURFACESTRUCTURE",
    "USERDEFINED",
    "NOTDEFINED"
  };

  OdDAI::Select *predefinedType;
  if (bridgePart->getAttr("predefinedtype") >> predefinedType)
  {
    if (predefinedType->underlyingTypeName("IFCBRIDGEPARTTYPEENUM"))
    {
      predefinedType->setEnum(partType);
    }
  }

  // This way is also available:
  //OdRxValue val((unsigned long)partType);
  //OdRxSpecifiedValueType vt(val.type(), OdAnsiString("IfcBridgePartTypeEnum"));
  //bridgePart->putAttr(kPredefinedType, OdRxValue(vt, val));

  /* TODO:
  OdDAI::AttributeDataBlock adb;
  adb.typePath.add("IFCBRIDGEPARTTYPEENUM");
  adb.value.setValue(bridgePartTypes[partType]);
  bridgePart->putAttr("predefinedtype", OdRxValue(adb));*/

  filler()->addRelAggregates(pParent, bridgePart);
  return bridgePart;
}

OdIfc::OdIfcEntityPtr IfcBridgeBuilder::appendProduct(OdIfc::OdIfcEntityPtr pContainer, const OdAnsiString &typeName, const OdAnsiString &name, OdIfc::OdIfcEntity *relPlacement)
{
  if (pContainer.isNull())
  {
    ODA_ASSERT("Container is null.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (!pContainer->isKindOf("ifcbridge") && !pContainer->isKindOf("ifcfacilitypart"))
  {
    ODA_ASSERT("Not ifcbridge or ifcfacilitypart.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfcModelPtr pModel = filler()->model();
  OdDAI::SchemaPtr pSchema = pModel->underlyingSchema();
  const OdDAI::EntityPtr pEntityDef = pSchema->find(typeName);
  if (pEntityDef.isNull())
  {
    ODA_ASSERT("No such entity in current schema.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (m_productDef.isNull())
    m_productDef = pSchema->find("ifcproduct");
  if (!m_productDef->isSupertypeOf(pEntityDef))
  {
    ODA_ASSERT("Type name should is not derived from IfcProduct.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfc::OdIfcEntityPtr pInst = pModel->createEntityInstance(typeName);
  OdIfc::Utils::assignGlobalId(pInst);
  pInst->putAttr(kOwnerHistory, OdDAIObjectId(filler()->ownerHistory()->id()));
  pInst->putAttr(kName, name);
  if (relPlacement)
  {
    OdIfc::OdIfcEntityPtr objectPlacement = pModel->createEntityInstance("ifclocalplacement");// filler->createIfcAxis2Placement3D(mPlacement);
    objectPlacement->putAttr("placementrelto", OdDAIObjectId(relPlacement->id()));
    OdDAIObjectId idObjectPlacement = pModel->appendEntityInstance(objectPlacement);
    pInst->putAttr("objectplacement", idObjectPlacement);
  }

  filler()->appendRelContainedInSpatialStructure(pContainer, pInst);
  return pInst;
}
