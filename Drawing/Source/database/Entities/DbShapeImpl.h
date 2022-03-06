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

#ifndef _ODDBSHAPEIMPL_INCLUDED_
#define _ODDBSHAPEIMPL_INCLUDED_

#include "DbEntityImpl.h"
#include "DbSystemInternals.h"
#include "DbShape.h"

class OdDbShapeImpl : public OdDbEntityImpl, public OdDb2dEntityImpl
{
  static OdDbShapeImpl* getImpl(const OdDbShape *pObj)
  { return (OdDbShapeImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
  OdGePoint3d       m_InsertionPoint; // In Ocs!
  double            m_dScale;
  double            m_dAngle;
  double            m_dWidthFactor;
  double            m_dOblique;
  OdUInt16          m_nShapeNumber;
  OdDbHardPointerId m_StyleId;
  OdString          m_Name;     // TODO: remove it

public:
  OdDbShapeImpl();
  virtual double thickness() const {return m_dThickness;}
  virtual void setThickness(double val) { m_dThickness = val; }

private:
  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;

  void audit(OdDbAuditInfo* pAuditInfo);

  friend class OdDbShape;
};

#endif // _ODDBSHAPEIMPL_INCLUDED_
