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

#ifndef __NW_PROXY_IMPL_INCLUDED__
#define __NW_PROXY_IMPL_INCLUDED__

#include "NwProxy.h"
#include "NwObjectImpl.h"
#include "NwStreamType.h"

#define STL_USING_MEMORY
#define STL_USING_FUNCTIONAL
#include "OdaSTL.h"

class OdNwProxy;
class OdNwGeometryStreamLoader;
typedef std::weak_ptr<OdNwGeometryStreamLoader> OdNwGeometryStreamLoaderWeakPtr;
typedef std::shared_ptr<OdNwGeometryStreamLoader> OdNwGeometryStreamLoaderPtr;

class OdNwGeometry;
typedef OdSmartPtr<OdNwGeometry> OdNwGeometryPtr;

class OdNwProxyImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwProxy)
public:
  OdNwProxyImpl();
  virtual ~OdNwProxyImpl();
  ODRX_DECLARE_MEMBERS(OdNwProxyImpl);

public:
  virtual bool draw(OdGiWorldDraw* pWd) const;

public:
  static OdNwProxyImpl* getImpl(const OdNwProxy* pNwGeometry);
  static OdNwProxyImpl* getImpl(const OdRxObject* pRxGeometry);

public:
  // TODO: set to start offset and end offset?
  void setObjectIndex(const OdInt32 index);
  OdInt32 getObjectIndex() const;

  OdNwGeometryPtr resolveGeometry() const;
  void setGeometryLoader(const OdNwGeometryStreamLoaderPtr& pGeomLoader);

protected:
  OdInt32 m_nObjectIndex;
  OdNwGeometryStreamLoaderWeakPtr m_pGeomLoaders;
};

#endif //__NWGEOMETRYIMPL_INCLUDED__
