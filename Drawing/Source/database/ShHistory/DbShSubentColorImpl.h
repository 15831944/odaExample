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

#ifndef _OD_DB_SHSUBENTCOLOR_IMPL_
#define _OD_DB_SHSUBENTCOLOR_IMPL_

#include "ShHistory/DbShSubentColor.h"
#include "DbShHistoryNodeImpl.h"


class OdDbShSubentColorImpl : public OdDbShHistoryNodeImpl
{
  OdInt32   m_nVersionMajor;
  OdInt32   m_nVersionMinor;
  OdInt32   m_iIdSubent; //It index which depend on number of ShSubentColor 1,2,3 ... number of ShSubentColor. DXF 92
  OdInt32   m_iId;   // m_iId = m_iStepId - 1.  It depend on OdDbPersSubentManager.  DXF 93
  bool      m_bFace; //290
  OdCmColor m_colorSubent;

  friend class OdDbShSubentColor;

public:
  OdDbShSubentColorImpl();

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler) const;

  void setFaceVariable(bool bVal);
  //OdResult connectOperand(unsigned long)
  //OdResult evaluateOnOperand(BODY *);
  //OdResult setSubent(BODY const *, ENTITY *)

  DECLARE_GET_IMPL(OdDbShSubentColor);

private:
  virtual bool evaluate(OdDbEvalContext const* ctx);
};

#endif
