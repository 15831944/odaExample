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

// ExCustEntity.h: interface for the ExCustEntity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(EXCUSTENTITY_INCLUDED)
#define EXCUSTENTITY_INCLUDED

#include "ExCustObjExport.h"
#include "DbCircle.h"


class EXCUSTOBJEXPORT ExCustEntity : public OdDbCircle
{
  static const OdInt16 lastKnownVersion;
  OdInt16 m_nCount;
  static void propertyConstructor(OdRxMemberCollectionBuilder&, void*);
public:
  // Macro to declare
  ODDB_DECLARE_MEMBERS(ExCustEntity);

  ExCustEntity();
  virtual ~ExCustEntity();

  static OdInt16 getVersion();

  void setCount(OdInt16 n);
  OdInt16 getCount() const;

  // Methods to override
  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler) const;
  bool subWorldDraw(OdGiWorldDraw * pWd) const;
  virtual OdResult subGetClassID(
    void* pClsid) const;
};

typedef OdSmartPtr<ExCustEntity> ExCustEntityPtr;

#endif
