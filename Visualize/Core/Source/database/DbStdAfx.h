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

#ifndef _DbStdAfx_h_Defined_
#define _DbStdAfx_h_Defined_

#include "OdaCommon.h"
#include "OdPlatform.h"
#include "OdaDefs.h"
#include <math.h>
#include <stdlib.h>
#include "TDVersion.h"
#define STL_USING_ALL
#include "OdaSTL.h"

// Turn on below warnings at level 3
#ifdef _MSC_VER
  #pragma warning(3 : 4018) // '>' : signed/unsigned mismatch
  #pragma warning(3 : 4127) // conditional expression is constant
  #pragma warning(3 : 4131) // function declaration is not in prototype form
  #pragma warning(3 : 4245) // 'argument' : conversion from 'int' to 'OdUInt32', signed/unsigned mismatch
  #pragma warning(3 : 4701) // potentially uninitialized local variable used
  #pragma warning(3 : 4702) // unreachable code
  #pragma warning(3 : 4706) // assignment within conditional expression
  #pragma warning(3 : 4389) // '==' : signed/unsigned mismatch
#endif

#include "RxObject.h"
#include "RxObjectImpl.h"
#include "OdString.h"
#include "OdErrorContext.h"
#include "DbSystemServices.h"
#include "DbHostAppServices.h"
#include "RxInit.h"
#include "RxSystemServices.h"
#include "RxDictionary.h"
#include "StaticRxObject.h"
#include "RxModule.h"
#include "OdArray.h"
#include "OdRound.h"
#include "OdStreamBuf.h"

#include "Ge/GeCircArc2d.h"
#include "Ge/GeCircArc3d.h"
#include "Ge/GeEllipArc2d.h"
#include "Ge/GeEllipArc3d.h"
#include "Ge/GeExtents2d.h"
#include "Ge/GeExtents3d.h"
//#include "GeHatch.h"
#include "IntArray.h"
#include "Ge/GeInterval.h"
#include "Ge/GeKnotVector.h"
#include "Ge/GeLineSeg2d.h"
#include "Ge/GeLineSeg3d.h"
#include "Ge/GeMatrix3d.h"
#include "Ge/GeNurbCurve2d.h"
#include "Ge/GeNurbSurface.h"
#include "Ge/GePlane.h"
#include "Ge/GePoint2dArray.h"
#include "Ge/GePoint3d.h"
#include "Ge/GeVector3d.h"
#include "Ge/GePolyline2d.h"
#include "Ge/GeSegmentChain2d.h"
#include "Ge/GeScale3d.h"
//#include "Ge/GeSystemInternals.h"

#include "Gi/Gi.h"
#include "Gi/GiClipBoundary.h"
#include "Gi/GiCommonDraw.h"
#include "Gi/GiDrawable.h"
#include "Gi/GiViewport.h"
#include "Gi/GiViewportDraw.h"
#include "Gi/GiViewportGeometry.h"
#include "Gi/GiWorldDraw.h"

#include "Gs/Gs.h"

#include "CmColor.h"
#include "DbAudit.h"
#include "DbDatabase.h"
#include "DbDictionary.h"
#include "DbEntity.h"
#include "DbExport.h"
#include "DbFiler.h"
#include "DbIdMapping.h"
#include "DbObject.h"
#include "DbObjectId.h"
#include "DbSymbolTable.h"
#include "DbSymbolTableRecord.h"
#include "DbSymUtl.h"
#include "DbSystemInternals.h"
#include "DynamicLinker.h"
#include "FlatMemStream.h"
#include "IdArrays.h"
#include "MemoryStream.h"
#include "OdBinaryData.h"
#include "OdDwgCopyFiler.h"
#include "OdToolKit.h"
#include "ProxyStuff.h"
#include "ResBuf.h"
#include "RxEventProvider.h"

#if defined(__GNUC__) && (GCC_VERSION >= 40201)
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#endif

#endif //_DbStdAfx_h_Defined_
