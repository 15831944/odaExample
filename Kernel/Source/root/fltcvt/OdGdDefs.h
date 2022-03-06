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


#ifndef _OD_GD_DEFS_
#define _OD_GD_DEFS_


// Platform setting
#ifndef ODA_BIGENDIAN
#define IEEE_8087
#else
#define IEEE_MC68k
#endif
#define d_QNAN0 0x0
#define d_QNAN1 0xfff80000

// Define types used in GD library
#define ANSI(x) x
#define Void    void
#define CONST   const
#define Long    OdInt32
#define ULong   OdUInt32
#define UShort  OdUInt16

#ifdef BUILTIN_INT64
#define Llong   OdInt64
#define ULLong  OdUInt64
#else
#define NO_LONG_LONG
#endif

// Define NO_HEX_FP to disable recognition of C9x's hexadecimal	floating-point constants.
#define NO_HEX_FP

#define NO_INFNAN_CHECK

#define NO_ERRNO

// Avoid warnings in GD library
#ifdef _MSC_VER
#pragma warning(disable: 4102)  // unreferenced label for unused definition
#pragma warning(disable: 4554)  // '<<'/'>>' : check operator precedence for possible error; use parentheses to clarify precedence
#pragma warning(disable: 4127)  // conditional expression is constant
#pragma warning(disable: 4701)  // local variable may be used without having been initialized
#ifdef BUILTIN_INT64
#pragma warning(disable: 4244)  // conversion from 'OdUInt64' to 'ULong', possible loss of data
#endif // BUILTIN_INT64
#endif // _MSC_VER

#endif // _OD_GD_DEFS_
