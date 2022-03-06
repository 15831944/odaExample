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

#ifndef _DAI_CONSTS_H_
#define _DAI_CONSTS_H_

#include "daiPlatform.h"
#include "daiObjectId.h"

#define STL_USING_LIMITS
#include "OdaSTL.h"

namespace OdDAI
{
  namespace Consts
  {

//#ifdef HAS_MOVE_SEMANTICS
//# define USE_LIB_NAN
//#endif

//#ifdef __cplusplus 
//# if __cplusplus > 199711L
//#   define USE_LIB_NAN
//# endif
//#endif

#ifdef USE_LIB_NAN
    static const double OdNan = nan("");
    static const float OdNanf = nanf("");
#else
    static const double OdNan = nanIEEERealCreate<double>();
    static const float OdNanf = nanIEEERealCreate<float>();
#endif

    static const long OdLongUnset = std::numeric_limits<long>::max();
    static const unsigned long OdULongUnset = std::numeric_limits<unsigned long>::max();
    static const int OdIntUnset = std::numeric_limits<int>::max();
    static const char OdStringUnset[] = "\xff";
    static const size_t OdStringUnsetLength = strlen(OdStringUnset);
    static const OdDAIObjectId OdHandleUnset = OdDAIObjectId::kNull;

    static const OdAnsiString StringF("F");
    static const OdAnsiString StringT("T");
    static const OdAnsiString StringU("U");
    static const OdAnsiString AnsiStringUnset(OdDAI::Consts::OdStringUnset);
  }
}

#endif // _DAI_CONSTS_H_
