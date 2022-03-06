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

#ifndef _ODDB_CURVEIMPL_INCLUDED_
#define _ODDB_CURVEIMPL_INCLUDED_

#include "DbCurveImpl.h"
#include "EntityContainer.h"

class OdPolylineBaseImpl : public OdTvDbCurveImpl, public OdTvEntitySeqEndContainer
{
  const OdTvDbObjectImpl* dbObjectImpl() const { return this; }
  OdTvEntityContainer* entContainer() { return this; }
public:
  typedef enum
  {
    ODA_PLINE_CLOSED        = 1,
    ODA_PLINE_CURVEFIT      = 2,
    ODA_PLINE_SPLINEFIT     = 4,
    ODA_PLINE_3DPLINE       = 8,
    ODA_PLINE_3DMESH        = 16,
    ODA_PLINE_CLOSEDN       = 32,
    ODA_PLINE_POLYFACEMESH  = 64,
    ODA_PLINE_CONTINUELT    = 128
  } OdaPLineFlags;

	OdUInt16 m_PolyFlags;
	OdInt16  m_FitType;

public:
  OdPolylineBaseImpl();

  OdResult dxfIn(OdTvDbDxfFiler* pFiler);
  void audit (OdTvDbAuditInfo* pAuditInfo);

  virtual void recvPropagateModify(OdTvDbObject* pOwner, const OdTvDbObject* pSubObj);
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  TD_USING(OdTvDbCurveImpl::setLayer);
};
#endif // _ODDBCURVEIMPL_INCLUDED_
