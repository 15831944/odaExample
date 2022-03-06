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

#ifndef _IFC2X3_IFCSTYLEMODEL_AUTO_IMPL_H
#define _IFC2X3_IFCSTYLEMODEL_AUTO_IMPL_H

#include "IfcRepresentationAutoImpl.h"

/** \details
  The namespace contains schema-dependent classes, definitions and sub routines
  for work with IFC2X3 express schema definitions.
*/
namespace OdIfc2x3 {

class IFC2X3_EXPORT IfcStyleModel : public IfcRepresentation
{
  //DOM-IGNORE-BEGIN
  OD_EXP_NON_INSTANTIABLE_DECLARE_MEMBERS(OdIfc2x3::IfcStyleModel);
  //DOM-IGNORE-END


public:

  /** \details
  Returns a type of a class instance.
  \returns
  Pointer to the <link OdDAI__Entity, OdDAI::Entity> type that determines an entity definition within a schema.
  */
  virtual OdDAI::Entity* getInstanceType() const;

  /** \details
  Early-bound version of instances comparison.
  \param pOther [in] Other application instance.
  \param ordering [out] Receives the ordering (comparison) status.
  \returns
  true if comparison was performed, false if method has no implementation, so late-bound version could be applied.
  \remarks
  If the method returns true,
  the ordering parameter can receive one of the following statuses:
  <table>
    Name             Value    Description
    _kLessThan_      -1       This object < Other Object.
    _kEqual_          0       This object = Other Object.
    _kGreaterThan_    1       This object > Other Object.
    _kNotOrderable_   2       This class is not orderable.
  </table>
  */
  virtual bool comparedToEarlyImpl(const OdDAI::ApplicationInstance *pOther, OdRx::Ordering &ordering) const;

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
  A data type that represents a smart pointer to a <link OdIfc2x3::IfcStyleModel, IfcStyleModel> object.
*/
typedef OdSmartPtr<IfcStyleModel> IfcStyleModelPtr;

} // namespace

#endif // _IFC2X3_IFCSTYLEMODEL_AUTO_IMPL_H
