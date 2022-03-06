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

#ifndef _ODDBELLIPSEIMPL_INCLUDED_
#define _ODDBELLIPSEIMPL_INCLUDED_

#include "DbCurveImpl.h"
#include "Ge/GeEllipArc3d.h"
#include "DbSystemInternals.h"
#include "DbEllipse.h"

class OdDbEllipseImpl : public OdDbCurveImpl, public OdGeEllipArc3d
{
  static OdDbEllipseImpl* getImpl(const OdDbEllipse *pObj)
  { return (OdDbEllipseImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
  ODRX_HEAP_OPERATORS();  // ODRX_USING_HEAP_OPERATORS() causes mac compiler error

  OdDbEllipseImpl();
  void audit(OdDbAuditInfo* pAuditInfo);
  virtual void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format,
                                    OdDb::DwgVersion version);

  // ! These functions return non-unit length vectors - opposite to OdGeEllipArc3d
  OdGeVector3d minorAxisInt() const  { return OdGeEllipArc3d::minorAxis()*OdGeEllipArc3d::minorRadius(); }
  OdGeVector3d majorAxisInt() const  { return OdGeEllipArc3d::majorAxis()*OdGeEllipArc3d::majorRadius(); }

  void setCastShadows(bool) {}
  bool castShadows() const { return false; }

  void setReceiveShadows(bool) {}
  bool receiveShadows() const { return false; }


private:
  OdResult dwgInFields(OdDbDwgFiler* pFiler, OdDbEllipse* pObj);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;

  friend class OdDbEllipse;
};

#endif // _ODDBELLIPSEIMPL_INCLUDED_
