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

#ifndef __NWGEOMETRYIMPL_INCLUDED__
#define __NWGEOMETRYIMPL_INCLUDED__

#include "NwProxyImpl.h"
#include "NwGeometry.h"
#include "NwVerticesDataImpl.h"
#include "Ge/GeExtents3d.h"

#include "Ge/GePoint3dArray.h"
#include "Ge/GePoint2dArray.h"
#include "Ge/GeVector3dArray.h"
#include "UInt32Array.h"
#include "NwStreamType.h"

#define STL_USING_MEMORY
#define STL_USING_FUNCTIONAL
#include "OdaSTL.h"

class OdNwGeometryImpl;
class OdNwStreamLoader;
typedef std::shared_ptr<OdNwStreamLoader> OdNwStreamLoaderPtr;

class OdNwGeometryImpl : public OdNwProxyImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwGeometry)
public:
  OdNwGeometryImpl();
  virtual ~OdNwGeometryImpl();
  ODRX_DECLARE_MEMBERS(OdNwGeometryImpl);

public:
  static OdNwGeometryImpl* getImpl(const OdNwGeometry* pNwGeometry);
  static OdNwGeometryImpl* getImpl(const OdRxObject* pRxGeometry);

public:
  // deprecated
  virtual OdArray<OdGePoint3d> getVertexes() const;
  virtual OdArray<OdUInt32> getColors() const;

  virtual OdGeExtents3d calculateBoundingBox() const;
  virtual OdUInt32 getPrimitiveCount() const;
};

#endif //__NWGEOMETRYIMPL_INCLUDED__
