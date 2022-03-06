/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2020, Open Design Alliance (the "Alliance"). 
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
//   Open Design Alliance Copyright (C) 2002-2020 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////


#ifndef TNW_LINEAR_UNITS_H_
#define TNW_LINEAR_UNITS_H_

/** \details
  Units of linear dimension.

  <group TNW_Namespaces>
*/
namespace NwLinearUnits
{
  enum Enum
  {
    /**SI meter. Length of the path travelled by light in a vacuum in 1 299,792,458th of a second. */
    UNITS_METERS = 0x00,
    /**1 100th of an SI meter. */
    UNITS_CENTIMETERS = 0x01,
    /**1 1000th of an SI meter.*/
    UNITS_MILLIMETERS = 0x02,
    /**1 3rd of a yard.*/
    UNITS_FEET = 0x03,
    /**1 12th of a foot, 2.54 SI centimeters. */
    UNITS_INCHES = 0x04,
    /**Imperial yard, 0.9144 SI meters.*/
    UNITS_YARDS = 0x05,
    /**1000 SI meters. */
    UNITS_KILOMETERS = 0x06,
    /**1760 yards. */
    UNITS_MILES = 0x07,
    /**1 1,000,000th of an SI meter, micron.*/
    UNITS_MICROMETERS = 0x08,
    /**1 1,000th of an inch.*/
    UNITS_MILS = 0x09,
    /**1 1,000,000th of an inch.*/
    UNITS_MICROINCHES = 0x0A
  };
}

#endif  // TNW_LINEAR_UNITS_H_

