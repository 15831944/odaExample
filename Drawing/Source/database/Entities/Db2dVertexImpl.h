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

#ifndef _ODDB2DVERTEXIMPL_INCLUDED_
#define _ODDB2DVERTEXIMPL_INCLUDED_

#include "DbVertexImpl.h"
#include "DbSystemInternals.h"
#include "Db2dVertex.h"

class OdDbDatabaseImpl;

 class OdDb2dVertexImpl : public OdDbVertexImpl
{
  static OdDb2dVertexImpl* getImpl(const OdDb2dVertex *pObj)
  { return (OdDb2dVertexImpl*)OdDbSystemInternals::getImpl(pObj);}

  void transformBy(const OdGeMatrix3d& trans, double scale, bool bNegBulge);

public:
  double  m_dStartWidth;
  double  m_dEndWidth;
  double  m_dBulge;
  double  m_dTangentDir;
  OdInt32 m_vertexId;
  OdUInt8 m_VertexFlags;

public:
  OdDb2dVertexImpl();

  OdUInt8 getVertexFlags() const { return m_VertexFlags; }
  void setVertexFlags(OdUInt8 val) { m_VertexFlags = val; }

  OdResult dxfInFields(OdDbDxfFiler* pFiler); 
  void dxfOutFields(OdDbDxfFiler* pFiler) const;

  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  void decomposeVertexId(OdDbObject* pObj);
  void composeVertexId(OdDbObject* pObj);

private:
  friend class OdDb2dVertex;
  friend class OdDb2dPolyline;
  friend class OdDb2dPolylineImpl;
  friend class OdPlineCacheResolver;
};

#endif // _ODDB2DVERTEXIMPL_INCLUDED_
