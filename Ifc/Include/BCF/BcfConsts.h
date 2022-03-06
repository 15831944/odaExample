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

#ifndef _BCF_CONSTS_H
#define _BCF_CONSTS_H

#include "BcfCommon.h"

#define STL_USING_LIMITS
#include "OdaSTL.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf
{
    /** \details
  Contains declarations of constants related to working with BCF files content.
  */
  namespace Consts
  {
    // This function should be tested on different platform. After successful tests we should move it to OdPlatfrom.h
    
    /** \details 
    A template function that returns a Not-a-Number (Nan) value for a specified real datatype.
    \returns A Nan value for the specified datatype.
    */
    template<class RealType>
    inline RealType nanIEEERealCreate()
    {
      /*
      int inf = 0x7F800000;
      int nan = 0x7F800001;
      */
      union nanType
      {
        RealType nan;
        unsigned char buf[sizeof(RealType)];
      };

      nanType nanGenerator = { 0 };

#ifdef ODA_BIGENDIAN
      nanGenerator.buf[0] = 0x7F;
      nanGenerator.buf[1] = 0xF0;
      nanGenerator.buf[sizeof(RealType) - 1] = 0x1;
#else
      nanGenerator.buf[sizeof(RealType) - 1] = 0x7F;
      nanGenerator.buf[sizeof(RealType) - 2] = 0xF0;
      nanGenerator.buf[0] = 0x1;
#endif

      return nanGenerator.nan;
  }

#ifdef USE_LIB_NAN
    /** \details 
    A Nan value for the double datatype used for BCF format operations.
    */
  static const double OdNan = nan("");
  
    /** \details 
    A Nan value for the float datatype used for BCF format operations.
    */
  static const float OdNanf = nanf("");
#else
    /** \details 
    A Nan value for the double datatype used for BCF format operations.
    */
    static const double OdNan = nanIEEERealCreate<double>();
    
    /** \details 
    A Nan value for the float datatype used for BCF format operations.
    */
    static const float OdNanf = nanIEEERealCreate<float>();
#endif

    /** \details 
    An undefined (unset) value for the long datatype used for BCF format operations.
    */
    static const long OdLongUnset = std::numeric_limits<long>::max();
    
    /** \details 
    An undefined (unset) value for the int datatype used for BCF format operations.
    */
    static const int OdIntUnset = std::numeric_limits<int>::max();
    
    /** \details 
    An undefined (unset) value for strings used for BCF format operations.
    */
    static const char OdStringUnset[] = "\xff";
    
    /** \details 
    An undefined (unset) value for the string length used for BCF format operations.
    */
    static const size_t OdStringUnsetLength = strlen(OdStringUnset);

    /** \details 
    An undefined (unset) value for ANSI strings used for BCF format operations.
    */
    static const OdAnsiString AnsiStringUnset(OdBcf::Consts::OdStringUnset);
  }
}

#endif // _BCF_CONSTS_H
