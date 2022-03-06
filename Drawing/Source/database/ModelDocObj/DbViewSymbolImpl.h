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

#ifndef _ODDBVIEVSYMBOLIMPL_INCLUDED_
#define _ODDBVIEVSYMBOLIMPL_INCLUDED_

#include "DbViewSymbol.h"

#include "DbSystemInternals.h"
#include "DbEntityImpl.h"

class OdDbViewSymbolImpl : public OdDbEntityImpl
{
  static OdDbViewSymbolImpl* getImpl(const OdDbViewSymbol* pObj)
  { 
    return (OdDbViewSymbolImpl*) OdDbSystemInternals::getImpl(pObj);
  }
protected:
  friend  class OdDbViewSymbol;

  OdDbViewSymbolImpl();

  virtual OdResult getIdentifier(OdString& sName) const = 0;
  virtual OdResult setIdentifier(const OdString& sName) = 0;

  // OdDbObjectImpl methods
  //virtual void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  virtual void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  OdDbObjectId m_symbolStyleId;
  double m_scale;
  OdDbObjectId m_owningViewRepId;
  OdInt16 m_tag;
};

#endif // _ODDBVIEVSYMBOLIMPL_INCLUDED_
