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

#ifndef _ODDB3DPOLYLINEVERTEXIMPL_INCLUDED_
#define _ODDB3DPOLYLINEVERTEXIMPL_INCLUDED_

#include "DbVertexImpl.h"
#include "DbSystemInternals.h"
#include "Db3dPolylineVertex.h"

class OdDb3dPolylineVertexImpl : public OdDbVertexImpl
{
  static OdDb3dPolylineVertexImpl* getImpl(const OdDb3dPolylineVertex *pObj)
  { return (OdDb3dPolylineVertexImpl*)OdDbSystemInternals::getImpl(pObj);}

protected:
  OdUInt8 m_VertexFlags;

public:
  OdDb3dPolylineVertexImpl()
    : m_VertexFlags(OdDbVertexImpl::k3dPolylineVertex)
  {}

  OdUInt8 getVertexFlags() const { return m_VertexFlags; }
  void setVertexFlags(OdUInt8 val) { m_VertexFlags = val; }

  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdDbDxfFiler* pFiler) const;
protected:
  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;

  friend class OdDb3dPolylineVertex;
  friend class OdDb3dPolyline;
  friend class OdDb3dPolylineImpl;
  friend class Od3dPolylineCacheResolver;
};

#endif // _ODDB3DPOLYLINEVERTEXIMPL_INCLUDED_
