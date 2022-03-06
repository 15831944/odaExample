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


#ifndef TNW_UNIT_UTILS_H_
#define TNW_UNIT_UTILS_H_

#include "NwExport.h"
#include "NwModelUnits.h"
#include "OdResult.h"

class OdGeMatrix3d;

/** \details
  This class contains methods for working with values that have units.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwUnitUtils
{
public:
  /** \details
    Returns the double result of converting current units to desired units.

    \param value            [in] Double value to be converted.
    \param currentModelUnit [in] Units from which to convert.
    \param desiredModelUnit [in] Units to which to convert.
    \param pResult         [out] OdResult with error code.

    \returns Double value with the conversion result.

    \remarks
    Error code is eOk if conversion is successful, eNotApplicable &mdash; if
    current and desired units are not the same type of measurements.
    Measurement units can be one of the following:

    <table>
    Name                                      Value    Description
    NwModelUnits::UNITS_METERS                0x00     SI meter. Length of the path travelled by light in a vacuum in 1 299,792,458th of second
    NwModelUnits::UNITS_CENTIMETERS           0x01     1 100th of an SI meter
    NwModelUnits::UNITS_MILLIMETERS           0x02     1 1000th of an SI meter
    NwModelUnits::UNITS_FEET                  0x03     1 3rd of a yard
    NwModelUnits::UNITS_INCHES                0x04     1 12th of a foot, 2.54 SI centimeters
    NwModelUnits::UNITS_YARDS                 0x05     Imperial yard, 0.9144 SI meters
    NwModelUnits::UNITS_KILOMETERS            0x06     1000 SI meters
    NwModelUnits::UNITS_MILES                 0x07     1760 yards
    NwModelUnits::UNITS_MICROMETERS           0x08     1 1,000,000th of an SI meter, micron
    NwModelUnits::UNITS_MILS                  0x09     1 1,000th of an inch
    NwModelUnits::UNITS_MICROINCHES           0x0A     1 1,000,000th of an inch
    NwModelUnits::UNITS_SQUARE_METERS         0x1A     1 square meter
    NwModelUnits::UNITS_SQUARE_CENTIMETERS    0x1B     1 square centimeter
    NwModelUnits::UNITS_SQUARE_MILLIMETERS    0x1C     1 square millimeter
    NwModelUnits::UNITS_SQUARE_FEET           0x1D     1 square feet
    NwModelUnits::UNITS_SQUARE_INCHES         0x1E     1 square inch
    NwModelUnits::UNITS_SQUARE_YARDS          0x1F     1 square yard
    NwModelUnits::UNITS_SQUARE_KILOMETERS     0x20     1 square kilometer
    NwModelUnits::UNITS_SQUARE_MILES          0x21     1 square mile
    NwModelUnits::UNITS_SQUARE_MICROMETERS    0x22     1 square micrometer
    NwModelUnits::UNITS_SQUARE_MILS           0x23     1 square mil
    NwModelUnits::UNITS_SQUARE_MICROINCHES    0x24     1 square microinch
    NwModelUnits::UNITS_CUBE_METERS           0x25     1 cube meter
    NwModelUnits::UNITS_CUBE_CENTIMETERS      0x26     1 cube centimeter
    NwModelUnits::UNITS_CUBE_MILLIMETERS      0x27     1 cube millimeter
    NwModelUnits::UNITS_CUBE_FEET             0x28     1 cube feet
    NwModelUnits::UNITS_CUBE_INCHES           0x29     1 cube inch
    NwModelUnits::UNITS_CUBE_YARDS            0x2A     1 cube yard
    NwModelUnits::UNITS_CUBE_KILOMETERS       0x2B     1 cube kilometer
    NwModelUnits::UNITS_CUBE_MILES            0x2C     1 cube mile
    NwModelUnits::UNITS_CUBE_MICROMETERS      0x2D     1 cube micrometer
    NwModelUnits::UNITS_CUBE_MILS             0x2E     1 cube mil
    NwModelUnits::UNITS_CUBE_MICROINCHES      0x2F     1 cube microinch
    </table>
  */
  static double convert(double value, NwModelUnits::Enum currentModelUnit, NwModelUnits::Enum desiredModelUnit, OdResult* pResult = NULL);

  /** \details
    Converts a matrix from current units to desired units.

    \param value        [in/out] OdGeMatrix3d value to convert.
    \param currentModelUnit [in] Units from which to convert.
    \param desiredModelUnit [in] Units to which to convert.

    \returns eOk if successful, eNotApplicable &mdash; if current and desired
    units are not the same type of measurements.

    \remarks
    Measurement units can be one of the following:

    <table>
    Name                                      Value    Description
    NwModelUnits::UNITS_METERS                0x00     SI meter. Length of the path travelled by light in a vacuum in 1 299,792,458th of second
    NwModelUnits::UNITS_CENTIMETERS           0x01     1 100th of an SI meter
    NwModelUnits::UNITS_MILLIMETERS           0x02     1 1000th of an SI meter
    NwModelUnits::UNITS_FEET                  0x03     1 3rd of a yard
    NwModelUnits::UNITS_INCHES                0x04     1 12th of a foot, 2.54 SI centimeters
    NwModelUnits::UNITS_YARDS                 0x05     Imperial yard, 0.9144 SI meters
    NwModelUnits::UNITS_KILOMETERS            0x06     1000 SI meters
    NwModelUnits::UNITS_MILES                 0x07     1760 yards
    NwModelUnits::UNITS_MICROMETERS           0x08     1 1,000,000th of an SI meter, micron
    NwModelUnits::UNITS_MILS                  0x09     1 1,000th of an inch
    NwModelUnits::UNITS_MICROINCHES           0x0A     1 1,000,000th of an inch
    NwModelUnits::UNITS_SQUARE_METERS         0x1A     1 square meter
    NwModelUnits::UNITS_SQUARE_CENTIMETERS    0x1B     1 square centimeter
    NwModelUnits::UNITS_SQUARE_MILLIMETERS    0x1C     1 square millimeter
    NwModelUnits::UNITS_SQUARE_FEET           0x1D     1 square feet
    NwModelUnits::UNITS_SQUARE_INCHES         0x1E     1 square inch
    NwModelUnits::UNITS_SQUARE_YARDS          0x1F     1 square yard
    NwModelUnits::UNITS_SQUARE_KILOMETERS     0x20     1 square kilometer
    NwModelUnits::UNITS_SQUARE_MILES          0x21     1 square mile
    NwModelUnits::UNITS_SQUARE_MICROMETERS    0x22     1 square micrometer
    NwModelUnits::UNITS_SQUARE_MILS           0x23     1 square mil
    NwModelUnits::UNITS_SQUARE_MICROINCHES    0x24     1 square microinch
    NwModelUnits::UNITS_CUBE_METERS           0x25     1 cube meter
    NwModelUnits::UNITS_CUBE_CENTIMETERS      0x26     1 cube centimeter
    NwModelUnits::UNITS_CUBE_MILLIMETERS      0x27     1 cube millimeter
    NwModelUnits::UNITS_CUBE_FEET             0x28     1 cube feet
    NwModelUnits::UNITS_CUBE_INCHES           0x29     1 cube inch
    NwModelUnits::UNITS_CUBE_YARDS            0x2A     1 cube yard
    NwModelUnits::UNITS_CUBE_KILOMETERS       0x2B     1 cube kilometer
    NwModelUnits::UNITS_CUBE_MILES            0x2C     1 cube mile
    NwModelUnits::UNITS_CUBE_MICROMETERS      0x2D     1 cube micrometer
    NwModelUnits::UNITS_CUBE_MILS             0x2E     1 cube mil
    NwModelUnits::UNITS_CUBE_MICROINCHES      0x2F     1 cube microinch
    </table>
  */
  static OdResult convertMatrix3d(OdGeMatrix3d& value, NwModelUnits::Enum currentModelUnit, NwModelUnits::Enum desiredModelUnit);

  /** \details
    Converts current length units to area units.

    \param modelUnits [in] Units to be converted.

    \returns Converted area units.

    \remarks
    Units for convertion must be linear for correct work.
    Measurement units can be one of the following:

    <table>
    Name                               Value    Description
    NwModelUnits::UNITS_METERS         0x00     SI meter. Length of the path travelled by light in a vacuum in 1 299,792,458th of second
    NwModelUnits::UNITS_CENTIMETERS    0x01     1 100th of an SI meter
    NwModelUnits::UNITS_MILLIMETERS    0x02     1 1000th of an SI meter
    NwModelUnits::UNITS_FEET           0x03     1 3rd of a yard
    NwModelUnits::UNITS_INCHES         0x04     1 12th of a foot, 2.54 SI centimeters
    NwModelUnits::UNITS_YARDS          0x05     Imperial yard, 0.9144 SI meters
    NwModelUnits::UNITS_KILOMETERS     0x06     1000 SI meters
    NwModelUnits::UNITS_MILES          0x07     1760 yards
    NwModelUnits::UNITS_MICROMETERS    0x08     1 1,000,000th of an SI meter, micron
    NwModelUnits::UNITS_MILS           0x09     1 1,000th of an inch
    NwModelUnits::UNITS_MICROINCHES    0x0A     1 1,000,000th of an inch
    </table>
  */
  static NwModelUnits::Enum getSquareByLinear(NwModelUnits::Enum modelUnits);

  /** \details
    Converts current length units to cube units.

    \param modelUnits [in] Units to be converted.

    \returns Converted cube units.

    \remarks
    Units for convertion must be linear for correct work.
    Measurement units can be one of the following:

    <table>
    Name                               Value    Description
    NwModelUnits::UNITS_METERS         0x00     SI meter. Length of the path travelled by light in a vacuum in 1 299,792,458th of second
    NwModelUnits::UNITS_CENTIMETERS    0x01     1 100th of an SI meter
    NwModelUnits::UNITS_MILLIMETERS    0x02     1 1000th of an SI meter
    NwModelUnits::UNITS_FEET           0x03     1 3rd of a yard
    NwModelUnits::UNITS_INCHES         0x04     1 12th of a foot, 2.54 SI centimeters
    NwModelUnits::UNITS_YARDS          0x05     Imperial yard, 0.9144 SI meters
    NwModelUnits::UNITS_KILOMETERS     0x06     1000 SI meters
    NwModelUnits::UNITS_MILES          0x07     1760 yards
    NwModelUnits::UNITS_MICROMETERS    0x08     1 1,000,000th of an SI meter, micron
    NwModelUnits::UNITS_MILS           0x09     1 1,000th of an inch
    NwModelUnits::UNITS_MICROINCHES    0x0A     1 1,000,000th of an inch
    </table>
  */
  static NwModelUnits::Enum getCubeByLinear(NwModelUnits::Enum modelUnits);

  /** \details
    Checks whether the specified units have linear type of measurement.

    \param modelUnits [in] Units to be checked.

    \returns True if units is linear; false otherwise.

    \remarks
    Measurement units can be one of the following:

    <table>
    Name                               Value    Description
    NwModelUnits::UNITS_METERS         0x00     SI meter. Length of the path travelled by light in a vacuum in 1 299,792,458th of second
    NwModelUnits::UNITS_CENTIMETERS    0x01     1 100th of an SI meter
    NwModelUnits::UNITS_MILLIMETERS    0x02     1 1000th of an SI meter
    NwModelUnits::UNITS_FEET           0x03     1 3rd of a yard
    NwModelUnits::UNITS_INCHES         0x04     1 12th of a foot, 2.54 SI centimeters
    NwModelUnits::UNITS_YARDS          0x05     Imperial yard, 0.9144 SI meters
    NwModelUnits::UNITS_KILOMETERS     0x06     1000 SI meters
    NwModelUnits::UNITS_MILES          0x07     1760 yards
    NwModelUnits::UNITS_MICROMETERS    0x08     1 1,000,000th of an SI meter, micron
    NwModelUnits::UNITS_MILS           0x09     1 1,000th of an inch
    NwModelUnits::UNITS_MICROINCHES    0x0A     1 1,000,000th of an inch
    </table>
  */
  static bool isLinear(NwModelUnits::Enum modelUnits);

  /** \details
    Checks if the specified units have square type of measurement.

    \param modelUnits [in] Units to be checked.

    \returns True if units is square; false otherwise.

    \remarks
    Measurement units can be one of the following:

    <table>
    Name                                      Value    Description
    NwModelUnits::UNITS_SQUARE_METERS         0x1A     1 square meter
    NwModelUnits::UNITS_SQUARE_CENTIMETERS    0x1B     1 square centimeter
    NwModelUnits::UNITS_SQUARE_MILLIMETERS    0x1C     1 square millimeter
    NwModelUnits::UNITS_SQUARE_FEET           0x1D     1 square feet
    NwModelUnits::UNITS_SQUARE_INCHES         0x1E     1 square inch
    NwModelUnits::UNITS_SQUARE_YARDS          0x1F     1 square yard
    NwModelUnits::UNITS_SQUARE_KILOMETERS     0x20     1 square kilometer
    NwModelUnits::UNITS_SQUARE_MILES          0x21     1 square mile
    NwModelUnits::UNITS_SQUARE_MICROMETERS    0x22     1 square micrometer
    NwModelUnits::UNITS_SQUARE_MILS           0x23     1 square mil
    NwModelUnits::UNITS_SQUARE_MICROINCHES    0x24     1 square microinch
    </table>
  */
  static bool isSquare(NwModelUnits::Enum modelUnits);

  /** \details
    Checks if the specified units have cube type of measurement.

    \param modelUnits [in] Units to be checked.

    \returns True if units is cube; false otherwise.

    \remarks
    Measurement units can be one of the following:

    <table>
    Name                                    Value    Description
    NwModelUnits::UNITS_CUBE_METERS         0x25     1 cube meter
    NwModelUnits::UNITS_CUBE_CENTIMETERS    0x26     1 cube centimeter
    NwModelUnits::UNITS_CUBE_MILLIMETERS    0x27     1 cube millimeter
    NwModelUnits::UNITS_CUBE_FEET           0x28     1 cube feet
    NwModelUnits::UNITS_CUBE_INCHES         0x29     1 cube inch
    NwModelUnits::UNITS_CUBE_YARDS          0x2A     1 cube yard
    NwModelUnits::UNITS_CUBE_KILOMETERS     0x2B     1 cube kilometer
    NwModelUnits::UNITS_CUBE_MILES          0x2C     1 cube mile
    NwModelUnits::UNITS_CUBE_MICROMETERS    0x2D     1 cube micrometer
    NwModelUnits::UNITS_CUBE_MILS           0x2E     1 cube mil
    NwModelUnits::UNITS_CUBE_MICROINCHES    0x2F     1 cube microinch
    </table>
  */
  static bool isCube(NwModelUnits::Enum modelUnits);
};

#endif  // TNW_UNIT_UTILS_H_

