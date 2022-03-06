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

#ifndef _ODDBRASTERVARIABLESIMPL_INCLUDED_
#define _ODDBRASTERVARIABLESIMPL_INCLUDED_


#include "DbSystemInternals.h"
#include "DbRasterVariables.h"
#include "DbObjectImpl.h"

class OdTvDbRasterVariablesImpl : public OdTvDbObjectImpl
{
  static OdTvDbRasterVariablesImpl* getImpl(const OdTvDbRasterVariables *pObj)
  { return (OdTvDbRasterVariablesImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  OdInt32  m_ClassVersion;
  OdInt16 m_DisplayFrame;
  OdInt16 m_DisplayQuality;
  OdInt16 m_Units;

public:
  OdTvDbRasterVariablesImpl();

private:
  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  friend class OdTvDbRasterVariables;
};

#endif // _ODDBRASTERVARIABLESIMPL_INCLUDED_
