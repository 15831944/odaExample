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

#ifndef _IFC_VALUE_TYPES_H_
#define _IFC_VALUE_TYPES_H_

#include "daiValueTypes.h"

#include "IfcGUID.h"

ODRX_DECLARE_VALUE_TYPE(OdIfcGUID, IFCCORE_EXPORT);

//-----------------------------------------------------------------------------------------

class OdIfcRxDisplayAsAttribute;

/** \details 
A data type that represents a smart pointer to an <link OdIfcRxDisplayAsAttribute, OdIfcRxDisplayAsAttribute> object.
*/
typedef OdSmartPtr<OdIfcRxDisplayAsAttribute> OdIfcRxDisplayAsAttributePtr;

/** \details 
The class implements an IFC attribute that can be used by the user interface to represent property values in a human-readable form (instead of displaying just a handle). 
*/
class IFCCORE_EXPORT OdIfcRxDisplayAsAttribute : public OdRxDisplayAsAttribute
{
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdIfcRxDisplayAsAttribute);
  //DOM-IGNORE-END
  
  /** \details 
  Createa a new IFC attribute instance with specified parameters. 
  \param bShowIndex       [in] A flag that determines whether the index of the created attributes should be shown.
  \param bShowObjectType  [in] A flag that determines whether the type of the created attributes should be shown.
  \returns A smart pointer to the created attribut object.
  */
  static OdRxAttributePtr createObject(bool bShowIndex, bool bShowObjectType);

  /** \details 
  Dereferences the IFC attribute value and retrieves the property which name is stored in the attribute. 
  \param value                [in] A value to dereference and retrieve the property of.
  \param useDynamicProperties [in] A flag that determines whether the getting of the displayed value should be optimized (is equal to true) or not (is equal to false).
  \returns 
  The name of the dereferenced object's property to use instead of the object identifier. 
  If the passed value type is not a reference or the referenced object has no such property, the method returns an empty string.
  \remarks 
  The useDynamicProperties flag can be set to false only if all properties of the database objects are statically dependent on the object type. 
  */
  virtual OdString getDisplayValue(OdRxValue& value, bool useDynamicProperties);
  
  /** \details 
  Sets the new value of the flag that determines whether the attribute type is displayed.
  If the flag value is equal to true, the type is displayed; otherwise (the flag value is equal to false), the type is not displayed.
  \param val [in] A new flag value to be set.
  */
  void setShowObjectType(bool val);
  
 /** \details 
  Sets the new value of the flag that determines whether the attribute index is displayed.
  If the flag value is equal to true, the index is displayed; otherwise (the flag value is equal to false), the index is not displayed.
  \param val [in] A new flag value to be set.
  */
  void setShowIndex(bool val);
  
//DOM-IGNORE-BEGIN
private:
  bool m_bShowIndex;
  bool m_bShowObjectType;
//DOM-IGNORE-END
};

#endif // _IFC_VALUE_TYPES_H_
