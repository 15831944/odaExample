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


#ifndef OD_GEEXT_H
#define OD_GEEXT_H /*!DOM*/

#include "Ge/GeTol.h"

#include "Ge/Ge.h"
#include "Ge/GeIntArray.h"

class OdGeSurface;
class OdGeCurve2d;

#include "TD_PackPush.h"

namespace OdGeExt
{

  //DOM-IGNORE-BEGIN
  // For internal use only
  GE_TOOLKIT_EXPORT OdResult calcLoopIncludeOrder(OdArray<OdGeIntArray>& loopIndices,
    const OdGeSurface& surf, bool surfReversed,
    const OdArray< OdArray<const OdGeCurve2d*> >& loops, const OdArray< OdArray<bool> >& loopsReversed,
    const OdGeTol& tol);
  //DOM-IGNORE-END

}

#include "TD_PackPop.h"

#endif // OD_GEEXT_H

