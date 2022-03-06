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

#ifndef OBJPARSERULES_H
#define OBJPARSERULES_H

#include "OBJToolkit.h"

#include "SharedPtr.h"
#include "RxObjectImpl.h"
#include "OdString.h"

namespace OBJToolkit {

  enum OdObjTokens {
      otObject  = 0

    , otGroup   = 1
    , otVertex  = 2
    , otVertexP = 3
    , otVertexT = 4
    , otNormal  = 5
    , otPoint   = 6
    , otLine    = 7
    , otFace    = 8
    , otCstype  = 9
    , otDeg     = 10
    , otCurve   = 11
    , otParm    = 12
    , otEnd     = 13
    , otCurv2   = 14
    , otSurface = 15
    , otTrim    = 16
    , otHole    = 17

    , otMtlLib  = 40
    , otUseMtl  = 41

    , otUnknown = otUseMtl + 1
  };

  enum OdMtlVal {
    mtvMtlName        = 0,
    mtvNs             = 1,
    mtvNi             = 2,
    mtvTr             = 3,
    mtvIllum          = 4,

    mtvD              = 5,
    mtvDHalo          = 6,

    // Options
    mtvMapType        = 10,
    mtvOpt1           = 11,
    mtvOpt2           = 12,
    mtvOpt3           = 13,
    mtvOptFilename    = 14,
    mtvOptFactor      = 15,

    mtvMapKaOpts      = 40,
    mtvMapKdOpts      = 41,
    mtvMapKsOpts      = 42,
    mtvMapDOpts       = 43,
    mtvMapNsOpts      = 44,
    mtvDecalOpts      = 45,
    mtvDispOpts       = 46,
    mtvBumpOpts       = 47,
    mtvReflOpts       = 48,
    mtvMapAATOpts     = 49,

    mtvMapKaFilename  = 60,
    mtvMapKdFilename  = 61,
    mtvMapKsFilename  = 62,
    mtvMapDFilename   = 63,
  };

  enum OdMtlOpts {

      mopBumpMultiplier   = 0
    , mopClamp            = 1
    , mopBlendU           = 2
    , mopBlendV           = 3
    , mopColorCorrection  = 4
    , mopImfChan          = 5
    , mopMm               = 6     // range over which scalar or color texture values may vary
    , mopO                = 7
    , mopS                = 8
    , mopT                = 9
    , mopTexRes           = 10
    , mopReflType         = 11
    , mopBoost            = 12

    , mopLast             = mopBoost
    , mopUnknown          = mopLast + 1
  };

}

#endif // OBJPARSERULES_H
