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

// This file is generated automatically.

#ifndef _IFC2X2_FINAL_IFCEXTERNALLYDEFINEDSYMBOL_AUTO_IMPL_H
#define _IFC2X2_FINAL_IFCEXTERNALLYDEFINEDSYMBOL_AUTO_IMPL_H

#include "IfcExternalReferenceAutoImpl.h"

/** \details
  The namespace contains schema-dependent classes, definitions and sub routines
  for work with IFC2X2_FINAL express schema definitions.
*/
namespace OdIfc2x2_final {

class IFC2X2_FINAL_EXPORT IfcExternallyDefinedSymbol : public IfcExternalReference
{
  //DOM-IGNORE-BEGIN
  OD_EXP_DECLARE_MEMBERS(OdIfc2x2_final::IfcExternallyDefinedSymbol);
  //DOM-IGNORE-END


public:

  /** \details
  Returns a type of a class instance.
  \returns
  Pointer to the <link OdDAI__Entity, OdDAI::Entity> type that determines an entity definition within a schema.
  */
  virtual OdDAI::Entity* getInstanceType() const;

  /** \details
  Checks whether the specified instance is the object derived from or belongs to this class.
  \param entityType [in] Entity to check.
  \returns
  true if the specified instance is the object derived from or belongs to this class, false otherwise.
  */
  virtual bool isKindOf(OdIfc::OdIfcEntityType entityType) const;

  /** \details
  Returns the type of this entity.
  \returns
  A value of the <link OdIfc__OdIfcEntityType, OdIfc::OdIfcEntityType> type that represents type of this entity.
  */
  virtual OdIfc::OdIfcEntityType type() const;
};

/** \details
  A data type that represents a smart pointer to a <link OdIfc2x2_final::IfcExternallyDefinedSymbol, IfcExternallyDefinedSymbol> object.
*/
typedef OdSmartPtr<IfcExternallyDefinedSymbol> IfcExternallyDefinedSymbolPtr;

} // namespace

#endif // _IFC2X2_FINAL_IFCEXTERNALLYDEFINEDSYMBOL_AUTO_IMPL_H
