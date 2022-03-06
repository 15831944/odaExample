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

#ifndef __TNW_DATAPROPERTY_H__
#define __TNW_DATAPROPERTY_H__

#include "NwObject.h"
#include "RxSystemServices.h"
#include "NwExport.h"
#include "NwDataType.h"

class OdNwVariant;

/** \details
  This class represents a named property with data.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwDataProperty : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwDataProperty);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwDataProperty object.
  */
  OdNwDataProperty();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwDataProperty();

public:

  /** \details
    Returns the combined name of the property. The combined name contains a combination of the name and the display name. 

    \returns The combined name of the property as an OdString object.
  */
  OdString getCombineName() const;

  /** \details
    Returns the display name of the property.

    \returns Display name of the property as an OdString object.
  */
  OdString getDisplayName() const;

  /** \details
    Returns the name of the property.

    \returns Name of the property as an OdString object.
  */
  OdString getName() const;

  /** \details
    Returns the type of the property's value.
    
    \returns Type of the property's value as an NwDataType::Enum item.
    \remarks 
      Type can be one of the following:
    
    <table>
    Name                                Value   Description
    NwDataType::dt_NONE                 0       Default value type.
    NwDataType::dt_DOUBLE               0x01    Double value type.
    NwDataType::dt_INT32                0x02    32-bit integer value type.
    NwDataType::dt_BOOL                 0x03    Boolean value type.
    NwDataType::dt_DISPLAY_STRING       0x04    Display end-user string value type.
    NwDataType::dt_DATETIME             0x05    Date time value type.
    NwDataType::dt_DOUBLE_LENGTH        0x06    Double value type for length (in length's units).
    NwDataType::dt_DOUBLE_ANGLE         0x07    Double value type for angle (in radians).
    NwDataType::dt_NAME                 0x08    Name value type (with pointer to OdNwName object).
    NwDataType::dt_IDENTIFIER_STRING    0x09    Programmatic identifier string value type.
    NwDataType::dt_DOUBLE_AREA          0x0A    Double value type for area.
    NwDataType::dt_DOUBLE_VOLUME        0x0B    Double value type for volume.
    NwDataType::dt_POINT3D              0x0C    Point3d value type.
    NwDataType::dt_POINT2D              0x0D    Point2d value type.
    </table>
  */
  NwDataType::Enum getDataType() const;

  /** \details
    Gets a value of the property.

    \param val [out] OdNwVariant object with the returned property's value.
    \returns eOk if the property value is returned successfully, or an appropriate error code otherwise.
  */
  OdResult getValue(OdNwVariant& val) const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwDataProperty object pointers.
*/
typedef OdSmartPtr<OdNwDataProperty> OdNwDataPropertyPtr;

#endif //__TNW_DATAPROPERTY_H__

