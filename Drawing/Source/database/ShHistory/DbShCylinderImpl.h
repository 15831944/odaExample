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

#ifndef _OD_DB_SHCYLINDER_IMPL_
#define _OD_DB_SHCYLINDER_IMPL_

#include "ShHistory/DbShCylinder.h"
#include "DbShPrimitiveImpl.h"


class OdDbShCylinderImpl : public OdDbShPrimitiveImpl
{
  friend class OdDbShCone;
  friend class OdDbShCylinder;
public:
  OdDbShCylinderImpl() : m_dHeight(0)
                       , m_dMajorRad(0)
                       , m_dMinorRad(0)
                       , m_dTopMinorRad(0) {}

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler) const;
  DECLARE_GET_IMPL(OdDbShCylinder);

private:
  virtual OdResult transformBy(const OdGeMatrix3d& mat);
  virtual bool evaluate(OdDbEvalContext const* ctx);
protected:
  double m_dHeight;
  double m_dMajorRad;
  double m_dMinorRad;
  double m_dTopMinorRad;
};

class OdDbShConeImpl : public OdDbShCylinderImpl
{
  friend class OdDbShCone;
public:
  OdDbShConeImpl() {}

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler) const;

  DECLARE_GET_IMPL(OdDbShCone);

private:
  virtual bool evaluate(OdDbEvalContext const* ctx);
};
#endif
