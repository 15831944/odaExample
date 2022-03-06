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


#ifndef _NWVALUETYPES_H_INCLUDED_
#define _NWVALUETYPES_H_INCLUDED_

#include "RxValue.h"
#include "NwExport.h"
#include "NwModelUnits.h"
#include "RxAttribute.h"
#include "NwModelItemIcon.h"
#include "NwTextureSpaceMapping.h"

class OdNwColor;
class OdGUID;
class OdNwObjectId;
class OdNwObject;

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwObject object pointers.
*/
typedef OdSmartPtr<OdNwObject> OdNwObjectPtr;

//DOM-IGNORE-BEGIN
ODRX_DECLARE_VALUE_TYPE(OdNwObjectPtr, NWDBEXPORT);
ODRX_DECLARE_VALUE_TYPE(NwModelUnits::Enum, NWDBEXPORT);
ODRX_DECLARE_VALUE_TYPE(OdNwColor, NWDBEXPORT);
ODRX_DECLARE_VALUE_TYPE(OdGUID, NWDBEXPORT);
ODRX_DECLARE_VALUE_TYPE(tm, NWDBEXPORT);
ODRX_DECLARE_VALUE_TYPE(NwModelItemIcon::Enum, NWDBEXPORT);
ODRX_DECLARE_VALUE_TYPE(OdNwObjectId, NWDBEXPORT);
ODRX_DECLARE_VALUE_TYPE(NwTextureSpaceMapping::Enum, NWDBEXPORT);
//DOM-IGNORE-END

/** \details
  This class represents the DisplayAs attribute. This attribute can be used
  by a user interface to represent properties of non-referenceable types in
  a human-readable form (instead of displaying just a handle).

  <group OdNv_Classes>
*/
class NWDBEXPORT OdNwDisplayAsAttribute : public OdRxDisplayAsAttribute
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwDisplayAsAttribute);
  //DOM-IGNORE-END
public:
  /** \details
    Creates an instance of the OdNwDisplayAsAttribute class.

    \param setDisplayName [in] Value of the SetDisplayName attribute.
    \returns Pointer to the created object.
  */
  static OdRxAttributePtr createObject(bool setDisplayName);

  /** \details
    Returns the value of the DisplayAs attribute.

    \param value                [in] Value to get the DisplayAs attribute of.
    \param useDynamicProperties [in] True to use dynamic properties.
    \returns OdString containing the value of the DisplayAs attribute.
  */
  virtual OdString getDisplayValue(OdRxValue& value, bool useDynamicProperties);

  /** \details
    Default constructor.
  */
  OdNwDisplayAsAttribute();

protected:
  bool m_bSetDisplayName;
};

/** \details
  This class represents the HierarchyLevel attribute. This attribute marks this
  property as a tree node in the 'Common Data Access' API data structure.

  <group ONw_Classes>
*/
class NWDBEXPORT OdNwHierarchyLevelAttribute : public OdRxHierarchyLevelAttribute
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwHierarchyLevelAttribute);
  //DOM-IGNORE-END
public:
  /** \details
    Returns the value of the hierarchy level attribute.

    \param value [in] Value to get the hierarchy level attribute value of.
    \returns Returns an OdString with the value of the attribute.
  */
  virtual OdString value(OdRxValue& value);
};

#endif
