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


#ifndef TNW_FORMAT_VERSION_H_
#define TNW_FORMAT_VERSION_H_

/** \details
  Contains format version definitions.

  <group TNW_Namespaces>
*/
namespace NwFormatVersion
{
  /** \details
    This enumeration specifies NW format versions.
  */
  enum Enum
  {
    /** Format version is unknown or below NW-5 */
    NW_UNSUPPORTED,
    /** Format version is NW-5 */
    NW_5,
    /** Format version is NW-2009 */
    NW_2009,
    /** Format version is NW-2010 */
    NW_2010,
    /** Format version is NW-2011 */
    NW_2011,
    /** Format version is NW-2012 */
    NW_2012,
    /** Format version is NW-2013 */
    NW_2013,
    /** Format version is NW-2014 */
    NW_2014,
    /** Format version is NW-2015 */
    NW_2015,
    /** Format version is NW-2016..NW-2021 */
    NW_2016
  };
}

#endif  // TNW_FORMAT_VERSION_H_

