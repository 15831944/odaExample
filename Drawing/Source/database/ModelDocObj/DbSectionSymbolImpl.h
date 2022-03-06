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

#ifndef _ODDBSECTIONSYMBOLIMPL_INCLUDED_
#define _ODDBSECTIONSYMBOLIMPL_INCLUDED_

#include "DbSectionSymbol.h"
#include "DbViewSymbolImpl.h"
#include "UInt8Array.h"
#include "Ge/GeDoubleArray.h"

class OdDbSectionSymbolImpl : public OdDbViewSymbolImpl
{
public:
  static OdDbSectionSymbolImpl* getImpl(const OdDbSectionSymbol* pObj)
  { 
    return (OdDbSectionSymbolImpl*) OdDbSystemInternals::getImpl(pObj);
  }
  OdDbSectionSymbolImpl();
protected:
  friend class OdDbSectionSymbol;

  // OdDbViewSymbolImpl methods :
  virtual OdResult getIdentifier(OdString& sName) const;
  virtual OdResult setIdentifier(const OdString& sName);

  OdUInt32  m_nFlags;
  bool isViewDirectionLeft()            {return GETBIT(m_nFlags, 2);}
  bool isHalfSection()                  {return GETBIT(m_nFlags, 1);}
  void setViewDirectionLeft(bool bVal)  {SETBIT(m_nFlags, 2, bVal);}
  void setIsHalfSection(bool bVal)      {SETBIT(m_nFlags, 1, bVal);}

  OdGePoint3dArray m_sectionPoints;
  OdGeDoubleArray m_bulges;
  OdStringArray m_labelNames;
  OdGeVector3dArray m_labelOffsets;
  OdUInt8Array m_labelBits; // 0 - default position, 1 - user's custom position
};

#endif // _ODDBSECTIONSYMBOLIMPL_INCLUDED_
