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

#ifndef _IFC_QUANTITY_SET_FILLER_H
#define _IFC_QUANTITY_SET_FILLER_H

#include "IfcBuilder.h"

class IfcQuantitySetFiller : public IfcBuilder
{
protected:

  static OdSmartPtr<IfcQuantitySetFiller> createObject(
    ExIfcModelFiller *filler,
    OdIfc::OdIfcEntityPtr objectDefinition);

  OdIfc::OdIfcEntityPtr m_objectDefinition;
  OdIfc::OdIfcEntityPtr m_quantitySet;

  OdDAIObjectIds m_idProperties;

public:

  ODRX_DECLARE_MEMBERS(IfcQuantitySetFiller);

  OdIfc::OdIfcEntityPtr getObjectDefinition() { return m_objectDefinition; };
  OdIfc::OdIfcEntityPtr getQuantitySet() { return m_quantitySet; };

  IfcQuantitySetFiller& appendQuantityCount(
    const OdAnsiString &name,
    double countValue, const OdAnsiString &formula);

  IfcQuantitySetFiller& appendQuantityLength(
    const OdAnsiString &name,
    double lengthValue, const OdAnsiString &formula);

  OdIfc::OdIfcEntityPtr createQuantitySet(const OdAnsiString &name);
  
  friend class ExIfcModelFiller;
};
typedef OdSmartPtr<IfcQuantitySetFiller> IfcQuantitySetFillerPtr;

#endif // _IFC_QUANTITY_SET_FILLER_H
