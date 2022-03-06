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

#ifndef _ODDBVISUALSTYLEMPL_INCLUDED_
#define _ODDBVISUALSTYLEMPL_INCLUDED_

#include "DbVisualStyle.h"
#include "Gi/GiVisualStyle.h"
#include "GiVisualStyleImpl.h"
#include "DbObjectImpl.h"

class OdTvDbVisualStyleImpl : public OdTvDbObjectImpl
                          , public OdRxObjectImpl<OdTvGiVisualStyleImpl>
{
  static OdTvDbVisualStyleImpl* getImpl(const OdTvDbVisualStyle *pObj)
  { return (OdTvDbVisualStyleImpl*)OdTvDbSystemInternals::getImpl(pObj);}
protected:
  OdGiVisualStylePtr m_pVisualStyleMorpher;
  OdGiVisualStyle *getVisualStyleMorpher();
public:
  ODRX_USING_HEAP_OPERATORS(OdTvDbObjectImpl);

  OdTvDbVisualStyleImpl();

  // OdTvDbObjectImpl overridden
  //
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void audit(OdTvDbAuditInfo* pAuditInfo);

private:
  OdTvGiFaceStyleImpl& faceStyleImpl() { return m_faceStyle; }
  OdTvGiEdgeStyleImpl& edgeStyleImpl() { return m_edgeStyle; }
  OdTvGiDisplayStyleImpl& displayStyleImpl() { return m_displayStyle; }

  OdString              m_description;
  bool                  m_bInternalUseOnly;
  double                m_dUnknown;

  // AC24 support
  OdUInt16 m_version;

  friend  class OdTvDbVisualStyle;

  void rdOperation(OdTvDbDxfFiler *pFiler, int index);
  void rdVer3PropsChain(OdTvDbDxfFiler *pFiler);
  void wrVer3PropsChain(OdTvDbDxfFiler *pFiler) const;
};

TOOLKIT_EXPORT void odtvdbVerifyDefVisualStyles(OdTvDbDatabaseImpl* pDbImpl);

#endif // _ODDBVISUALSTYLEMPL_INCLUDED_
