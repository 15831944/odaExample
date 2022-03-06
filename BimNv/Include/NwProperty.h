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

#ifndef __TNW_PROPERTY_H__
#define __TNW_PROPERTY_H__

#include "NwObject.h"
#include "RxSystemServices.h"
#include "NwExport.h"
#include "NwPropertyValueType.h"
#include "StringArray.h"
#include "NwModelUnits.h"

class OdNwColor;
class OdGeVector3d;
class OdGePoint3d;
class OdGePoint2d;


/** \details
  This class represents a published property.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwProperty : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwProperty);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwProperty class.
  */
  OdNwProperty();
  
  /** \details
    Constructor. Creates a new OdNwProperty instance.

    \param pImpl [in] Implementation object for this object.
  */
  explicit OdNwProperty(OdNwObjectImpl* pImpl);

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwProperty();

public:

  /** \details
    Returns the display name of the property.

    \returns Display name of the property.
  */
  OdString getDisplayName() const;

  /** \details
    Returns the name of the property.

    \returns Name of the property.
  */
  OdString getName() const;

  /** \details
    Returns the type of the property's value.

    \remarks
    getValueType() returns one of the following:

    <table>
    Name                                             Value    Description
    NwPropertyValueType::value_type_default          0        Default value type
    NwPropertyValueType::value_type_bool             1        Boolean value type
    NwPropertyValueType::value_type_double           2        Double value type
    NwPropertyValueType::value_type_float            3        Float value type
    NwPropertyValueType::value_type_OdInt32          4        Integer value type
    NwPropertyValueType::value_type_OdInt8           5        Short integer value type
    NwPropertyValueType::value_type_OdUInt32         6        Unsigned integer value type
    NwPropertyValueType::value_type_OdUInt8          7        Unsigned short integer value type
    NwPropertyValueType::value_type_OdString         8        OdString value type
    NwPropertyValueType::value_type_OdStringArray    9        OdStringArray value type
    NwPropertyValueType::value_type_OdGeVector3d     10       OdGeVector3d value type
    NwPropertyValueType::value_type_OdUInt64         11       Uunsigned long integer value type
    NwPropertyValueType::value_type_OdNwColor        12       OdNwColor value type
    NwPropertyValueType::value_type_tm               13       Datetime value type
    </table>
  */
  NwPropertyValueType::Enum getValueType() const;

  /** \details
    Returns the string value of the property.

    \param val [out] OdString object with the property's value.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.

    \remarks
    This method is used only if the property's value is of the OdString type.
  */
  OdResult getValue(OdString& val) const;

  /** \details
    Returns the double value of the property.

    \param val [out] Double object with the property's value.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.

    \remarks
    This method is used only if the property's value is of the double type.
  */
  OdResult getValue(double& val) const;

  /** \details
    Returns the float value of the property.

    \param val [out] Float object with the property's value.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.

    \remarks
    This method is used only if the property's value is of the float type.
  */
  OdResult getValue(float& val) const;

  /** \details
    Returns the OdInt32 value of the property.

    \param val [out] OdInt32 object with the property's value.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.

    \remarks
    This method is used only if the property's value is of the integer type.
  */
  OdResult getValue(OdInt32& val) const;

  /** \details
    Returns the OdInt8 value of the property.

    \param val [out] OdInt8 object with the property's value.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.

    \remarks
    This method is used only if the property's value is of the short integer
    type.
  */
  OdResult getValue(OdInt8& val) const;

  /** \details
    Returns the OdUInt32 value of the property.

    \param val [out] OdUInt32 object with the property's value.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.

    \remarks
    This method is used only if the property's value is of the unsigned integer
    type.
  */
  OdResult getValue(OdUInt32& val) const;

  /** \details
    Returns the OdUInt8 value of the property.

    \param val [out] OdUInt8 object with the property's value.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.

    \remarks
    This method is used only if the property's value is of the unsigned short
    integer type.
  */
  OdResult getValue(OdUInt8& val) const;

  /** \details
    Returns the OdStringArray value of the property.

    \param val [out] OdStringArray object with the property's value.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.

    \remarks
    This method is used only if the property's value is of the OdStringArray
    type.
  */
  OdResult getValue(OdStringArray& val) const;

  /** \details
    Returns the OdGeVector3d value of the property.

    \param val [out] OdGeVector3d object with the property's value.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.

    \remarks
    This method is used only if the property's value is of the OdGeVector3d
    type.
  */
  OdResult getValue(OdGeVector3d& val) const;

  /** \details
    Returns the OdUInt64 value of the property.

    \param val [out] OdUInt64 object with the property's value.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.

    \remarks
    This method is used only if the property's value is of the unsigned long
    integer type.
  */
  OdResult getValue(OdUInt64& val) const;

  /** \details
    Returns the OdNwColor value of the property.

    \param val [out] OdNwColor object with the property's value.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.

    \remarks
    This method is used only if the property's value is of the OdNwColor type.
  */
  OdResult getValue(OdNwColor& val) const;

  /** \details
    Returns the datetime value of the property.

    \param val [out] The tm object with the property's value.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.

    \remarks
    This method is used only if the property's value is of the datetime type.
  */
  OdResult getValue(tm& val) const;
  /** \details
    Returns the GUID value of the property.

    \param val [out] The OdGUID object with the property's value.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.

    \remarks
    This method is used only if the property's value is of the OdGUID type.
  */
  OdResult getValue(OdGUID& val) const;

  /** \details
    Returns the boolean value of the property.

    \param val [out] A bool object with the property's value.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.

    \remarks
    This method is used only if the property's value is of the boolean type.
  */
  OdResult getValue(bool& val) const;

  /** \details
    Returns the OdGePoint3d value of the property.

    \param val [out] A OdGePoint3d object with the property's value.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.

    \remarks
    This method is used only if the property's value is of the OdGePoint3d type.
  */
  OdResult getValue(OdGePoint3d& val) const;

  /** \details
  Returns the OdGePoint2d value of the property.

  \param val [out] A OdGePoint2d object with the property's value.

  \returns eOk if the operation is successful, or an appropriate error code
  otherwise.

  \remarks
  This method is used only if the property's value is of the OdGePoint2d type.
*/
  OdResult getValue(OdGePoint2d& val) const;
  
  /** \details
    Returns the measurement units of the property.

    \param units [out] An NwPropertyValueType::Enum object with the property's units.

    \returns eOk if the property has units, or an appropriate error code
    otherwise.

    \remarks
    Measurement units can be one of the following:

    <table>
    Name                                            Value    Description
    NwModelUnits::UNITS_METERS                      0x00     SI meter. Length of the path travelled by light in a vacuum in 1 299,792,458th of second
    NwModelUnits::UNITS_CENTIMETERS                 0x01     1 100th of an SI meter
    NwModelUnits::UNITS_MILLIMETERS                 0x02     1 1000th of an SI meter
    NwModelUnits::UNITS_FEET                        0x03     1 3rd of a yard
    NwModelUnits::UNITS_INCHES                      0x04     1 12th of a foot, 2.54 SI centimeters
    NwModelUnits::UNITS_YARDS                       0x05     Imperial yard, 0.9144 SI meters
    NwModelUnits::UNITS_KILOMETERS                  0x06     1000 SI meters
    NwModelUnits::UNITS_MILES                       0x07     1760 yards
    NwModelUnits::UNITS_MICROMETERS                 0x08     1 1,000,000th of an SI meter, micron
    NwModelUnits::UNITS_MILS                        0x09     1 1,000th of an inch
    NwModelUnits::UNITS_MICROINCHES                 0x0A     1 1,000,000th of an inch
    NwModelUnits::UNITS_SQUARE_METERS               0x1A     1 square meter
    NwModelUnits::UNITS_SQUARE_CENTIMETERS          0x1B     1 square centimeter
    NwModelUnits::UNITS_SQUARE_MILLIMETERS          0x1C     1 square millimeter
    NwModelUnits::UNITS_SQUARE_FEET                 0x1D     1 square feet
    NwModelUnits::UNITS_SQUARE_INCHES               0x1E     1 square inch
    NwModelUnits::UNITS_SQUARE_YARDS                0x1F     1 square yard
    NwModelUnits::UNITS_SQUARE_KILOMETERS           0x20     1 square kilometer
    NwModelUnits::UNITS_SQUARE_MILES                0x21     1 square mile
    NwModelUnits::UNITS_SQUARE_MICROMETERS          0x22     1 square micrometer
    NwModelUnits::UNITS_SQUARE_MILS                 0x23     1 square mil
    NwModelUnits::UNITS_SQUARE_MICROINCHES          0x24     1 square microinch
    NwModelUnits::UNITS_CUBE_METERS                 0x25     1 cube meter
    NwModelUnits::UNITS_CUBE_CENTIMETERS            0x26     1 cube centimeter
    NwModelUnits::UNITS_CUBE_MILLIMETERS            0x27     1 cube millimeter
    NwModelUnits::UNITS_CUBE_FEET                   0x28     1 cube feet
    NwModelUnits::UNITS_CUBE_INCHES                 0x29     1 cube inch
    NwModelUnits::UNITS_CUBE_YARDS                  0x2A     1 cube yard
    NwModelUnits::UNITS_CUBE_KILOMETERS             0x2B     1 cube kilometer
    NwModelUnits::UNITS_CUBE_MILES                  0x2C     1 cube mile
    NwModelUnits::UNITS_CUBE_MICROMETERS            0x2D     1 cube micrometer
    NwModelUnits::UNITS_CUBE_MILS                   0x2E     1 cube mil
    NwModelUnits::UNITS_CUBE_MICROINCHES            0x2F     1 cube microinch
    NwModelUnits::UNITS_CANDELA_PER_SQUARE_METER    0x30     1 candela per square meter
    </table>
  */
  OdResult getUnits(NwModelUnits::Enum& units) const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwProperty object pointers.
*/
typedef OdSmartPtr<OdNwProperty> OdNwPropertyPtr;

#endif //__TNW_PROPERTY_H__

