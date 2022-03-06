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


#ifndef TNW_FORMAT_VERSION_EX_H_
#define TNW_FORMAT_VERSION_EX_H_

namespace NwFormatVersionEx
{
  enum Enum
  {
    NAVISWORKS1_2 = 2,
    NAVISWORKS1_3 = 3,
    NAVISWORKS1_5 = 5,
    NAVISWORKS2 = 22,
    NAVISWORKS2_34 = 34,
    NAVISWORKS2_45 = 45,
    NAWISWORKS2_53 = 53,
    NAWISWORKS2_57 = 57,
    NAWISWORKS2_62 = 62,
    NAWISWORKS2_63 = 63,
    NAWISWORKS2_64 = 64,
    NAWISWORKS4 = 72, // ???
    NAWISWORKS4_78 = 78,
    NAWISWORKS4_80 = 80,
    NAWISWORKS4_82 = 82,
    NAWISWORKS5 = 90,//the lower level(Architecture.nwc)
    NAWISWORKS5_92 = 92,
    NAWISWORKS5_96 = 96,
    NAWISWORKS2009 = 103,
    NAWISWORKS2009_107 = 107,
    NAWISWORKS2009_109 = 109,
    NAWISWORKS2009_110 = 110,
    NAWISWORKS2009_112 = 112,
    NAWISWORKS2010 = 114,
    NAWISWORKS2010_115 = 115,
    NAWISWORKS2010_116 = 116,
    NAWISWORKS2010_118 = 118,
    NAWISWORKS2011 = 120,
    NAWISWORKS2011_203 = 203,
    NAWISWORKS2011_214 = 214,
    NAWISWORKS2011_215 = 215,
    NAWISWORKS2011_217 = 217,
    NAWISWORKS2011_220 = 220,
    NAWISWORKS2011_222 = 222,
    NAWISWORKS2011_230 = 230,
    NAWISWORKS2012 = 238,
    NAWISWORKS2012_242 = 242,
    NAWISWORKS2012_243 = 243,
    NAWISWORKS2012_244 = 244,
    NAWISWORKS2012_246 = 246,
    NAWISWORKS2012_249 = 249,
    NAWISWORKS2012_251 = 251,
    NAWISWORKS2012_252 = 252,
    NAWISWORKS2012_254 = 254,
    NAWISWORKS2012_303 = 303,
    NAWISWORKS2012_306 = 306,
    NAWISWORKS2012_401 = 401,
    NAWISWORKS2013 = 405,
    NAWISWORKS2013_407 = 407,
    NAWISWORKS2013_409 = 409,
    NAWISWORKS2013_410 = 410,
    NAWISWORKS2013_411 = 411,
    NAWISWORKS2013_413 = 413,
    NAWISWORKS2013_415 = 415,
    NAWISWORKS2013_417 = 417,
    NAWISWORKS2013_419 = 419,
    NAWISWORKS2013_421 = 421,
    NAWISWORKS2013_425 = 425,
    NAWISWORKS2013_429 = 429,
    NAWISWORKS2013_430 = 430,
    NAWISWORKS2014 = 431,
    NAWISWORKS2014_437 = 437,
    NAWISWORKS2014_438 = 438,
    NAWISWORKS2015 = 441,
    NAWISWORKS2015_443 = 443,
    NAWISWORKS2015_447 = 447,
    NAWISWORKS2016 = 448 // 2016 and 2017
  };

  static bool isDefined(NwFormatVersionEx::Enum Formatversion)
  {
    return (Formatversion == NAWISWORKS4)
        || (Formatversion == NAWISWORKS5)
        || (Formatversion == NAWISWORKS2009)
        || (Formatversion == NAWISWORKS2010)
        || (Formatversion == NAWISWORKS2011)
        || (Formatversion == NAWISWORKS2012)
        || (Formatversion == NAWISWORKS2013)
        || (Formatversion == NAWISWORKS2014)
        || (Formatversion == NAWISWORKS2015)
        || (Formatversion == NAWISWORKS2016)
      ;
  }
}

#endif  // TNW_FORMAT_VERSION_EX_H_

