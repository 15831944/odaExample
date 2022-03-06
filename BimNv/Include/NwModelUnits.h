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


#ifndef TNW_MODEL_UNITS_H_
#define TNW_MODEL_UNITS_H_

/** \details
  Units of linear dimension.

  <group TNW_Namespaces>
*/
namespace NwModelUnits
{
  /** \details
    Units of linear dimension.
  */
  enum Enum
  {
    /** SI meter. Length of the path travelled by light in a vacuum in 1 299,792,458th of a second. */
    UNITS_METERS = 0x00,
    /** 1 100th of an SI meter. */
    UNITS_CENTIMETERS = 0x01,
    /** 1 1000th of an SI meter. */
    UNITS_MILLIMETERS = 0x02,
    /** 1 3rd of a yard. */
    UNITS_FEET = 0x03,
    /** 1 12th of a foot, 2.54 SI centimeters. */
    UNITS_INCHES = 0x04,
    /** Imperial yard, 0.9144 SI meters. */
    UNITS_YARDS = 0x05,
    /** 1000 SI meters. */
    UNITS_KILOMETERS = 0x06,
    /** 1760 yards. */
    UNITS_MILES = 0x07,
    /** 1 1,000,000th of an SI meter, micron. */
    UNITS_MICROMETERS = 0x08,
    /** 1 1,000th of an inch. */
    UNITS_MILS = 0x09,
    /** 1 1,000,000th of an inch. */
    UNITS_MICROINCHES = 0x0A,
    /** 1 square meter. */
    UNITS_SQUARE_METERS = 0x1A,
    /** 1 square centimeter. */
    UNITS_SQUARE_CENTIMETERS = 0x1B,
    /** 1 square milimeter. */
    UNITS_SQUARE_MILLIMETERS = 0x1C,
    /** 1 square feet. */
    UNITS_SQUARE_FEET = 0x1D,
    /** 1 square inch. */
    UNITS_SQUARE_INCHES = 0x1E,
    /** 1 square yard. */
    UNITS_SQUARE_YARDS = 0x1F,
    /** 1 square kilometer. */
    UNITS_SQUARE_KILOMETERS = 0x20,
    /** 1 square mile. */
    UNITS_SQUARE_MILES = 0x21,
    /** 1 square micrometer. */
    UNITS_SQUARE_MICROMETERS = 0x22,
    /** 1 square mil. */
    UNITS_SQUARE_MILS = 0x23,
    /** 1 square microinch. */
    UNITS_SQUARE_MICROINCHES = 0x24,
    /** 1 cubic meter. */
    UNITS_CUBE_METERS = 0x25,
    /** 1 cubic centimeter. */
    UNITS_CUBE_CENTIMETERS = 0x26,
    /** 1 cubic millimeter. */
    UNITS_CUBE_MILLIMETERS = 0x27,
    /** 1 cubic feet. */
    UNITS_CUBE_FEET = 0x28,
    /** 1 cubic inch. */
    UNITS_CUBE_INCHES = 0x29,
    /** 1 cubic yard. */
    UNITS_CUBE_YARDS = 0x2A,
    /** 1 cubic kilometer. */
    UNITS_CUBE_KILOMETERS = 0x2B,
    /** 1 cubic mile. */
    UNITS_CUBE_MILES = 0x2C,
    /** 1 cubic micrometer. */
    UNITS_CUBE_MICROMETERS = 0x2D,
    /** 1 cubic mil. */
    UNITS_CUBE_MILS = 0x2E,
    /** 1 cubic microinch. */
    UNITS_CUBE_MICROINCHES = 0x2F,
    /** 1 candela per square meter. */
    UNITS_CANDELA_PER_SQUARE_METER = 0x30,
  };
}
#endif  // TNW_MODEL_UNITS_H_

