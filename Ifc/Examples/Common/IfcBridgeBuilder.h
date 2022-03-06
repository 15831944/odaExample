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

#ifndef _IFC_BRIDGE_BUILDER_H
#define _IFC_BRIDGE_BUILDER_H

#include "IfcBuilder.h"

class IfcBridgeBuilder : public IfcBuilder
{
public:

  enum Type
  {
    kARCHED,
    kCABLE_STAYED,
    kCANTILEVER,
    kCULVERT,
    kFRAMEWORK,
    kGIRDER,
    kSUSPENSION,
    kTRUSS,
    kUSERDEFINED,
    kNOTDEFINED,
  };

  enum PartType
  {
    kABUTMENT,
    kDECK,
    kDECK_SEGMENT,
    kFOUNDATION,
    kPIER,
    kPIER_SEGMENT,
    kPYLON,
    kSUBSTRUCTURE,
    kSUPERSTRUCTURE,
    kSURFACESTRUCTURE,
    kUSERDEFINED_PART_TYPE,
    kNOTDEFINED_PART_TYPE,
  };

protected:

  static OdSmartPtr<IfcBridgeBuilder> createObject(ExIfcModelFiller *filler, const OdAnsiString &name, Type type = kNOTDEFINED);

  OdIfc::OdIfcEntityPtr m_bridge;
  Type m_predefinedType;
  OdAnsiString m_name;
  OdIfc::OdIfcEntityPtr appendIfcBridge();
  OdDAI::EntityPtr m_productDef;

public:

  ODRX_DECLARE_MEMBERS(IfcBridgeBuilder);

  IfcBridgeBuilder()
    : m_predefinedType(kNOTDEFINED)
  {};

  OdIfc::OdIfcEntityPtr getBridge() { return m_bridge; };

  OdIfc::OdIfcEntityPtr appendBridgePart(const OdAnsiString &name, OdIfc::OdIfcEntityPtr pParent = OdIfc::OdIfcEntityPtr(), PartType partType = kNOTDEFINED_PART_TYPE);

  OdIfc::OdIfcEntityPtr appendProduct(OdIfc::OdIfcEntityPtr pContainer, const OdAnsiString &typeName, const OdAnsiString &name, OdIfc::OdIfcEntity *relPlacement);

  friend class ExIfcModelFiller;
};
typedef OdSmartPtr<IfcBridgeBuilder> IfcBridgeBuilderPtr;

#endif // _IFC_BRIDGE_BUILDER_H
