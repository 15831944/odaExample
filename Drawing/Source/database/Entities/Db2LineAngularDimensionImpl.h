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

#ifndef _ODDB2LANGDIMIMPL_INCLUDED_
#define _ODDB2LANGDIMIMPL_INCLUDED_

#include "Db3PointAngularDimensionImpl.h"
#include "Db2LineAngularDimension.h"
#include "DbSystemInternals.h"

class OdDb2LineAngularDimensionImpl : public OdDb3PointAngularDimensionImpl
{
  static OdDb2LineAngularDimensionImpl* getImpl(const OdDb2LineAngularDimension *pObj)
  { return (OdDb2LineAngularDimensionImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
  // OdGePoint3d m_ArcDefPt;
  ODIMPL_DEFINE_WCS_OCS_POINT(ArcDefPt);

  virtual OdUInt8 getDimTypeFlag() { return OdDbDimensionImpl::Dim2LineAngular; }

  /** Transforms this entity by the specified matrix.
  */
  OdResult transformBy(const OdGeMatrix3d& xform, bool b2Copy);
  virtual void copyFromContextData(OdDbObject* pObj, OdDbObjectContextData* pData, OdDbObjectContextData* pDefData);

  // Sets the text position to default(just like acad sets it)
  // void setDefaultTextPosition();

  friend class OdDb2LineAngularDimension;
  friend class OdDwgR12FileLoader;
};

#endif // _ODDB2LANGDIMIMPL_INCLUDED_
