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

#ifndef _ODDBOLE2FRAMEIMPL_INCLUDED_
#define _ODDBOLE2FRAMEIMPL_INCLUDED_

#include "DbOleFrameImpl.h"
#include "DbSystemInternals.h"
#include "DbOle2Frame.h"
#include "Gi/GiMetafile.h"
#include "OleItemHandler.h"

class OdTvDbOle2FrameImpl : public OdTvDbOleFrameImpl
{
  static OdTvDbOle2FrameImpl* getImpl(const OdTvDbOle2Frame *pObj)
  { return (OdTvDbOle2FrameImpl*)OdTvDbSystemInternals::getImpl(pObj);}

  void load(OdStreamBuf& stream);
  void save(OdStreamBuf& stream) const;

  OdInt32     m_version;

public:
  OdString    m_sUserType;      // DXF 3
  OdInt32     m_nUnknown0;
  OdUInt8     m_nUnknown1;
  OdUInt8     m_nUnknown2;
  OdUInt8     m_nOleObjType;    // DXF 71
  OdUInt8     m_nOutputQuality; // DXF 73

  OdGePoint3d m_upperLeft;
  OdGePoint3d m_upperRight;
  OdGePoint3d m_lowerRight;
  OdGePoint3d m_lowerLeft;

  OdUInt16    m_himetricWidth;
  OdUInt16    m_himetricHeight;

  OdOleItemHandlerPtr m_pOleItem;

  OdTvDbOle2FrameImpl();

  virtual void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format,
                                      OdDb::DwgVersion version);
  OdUInt32 modelFlag() const;

  void setCastShadows(bool) {}
  bool castShadows() const { return false; }

  void setReceiveShadows(bool) {}
  bool receiveShadows() const { return false; }

  friend class OdTvDbOle2Frame;
};

#endif // _ODDBOLE2FRAMEIMPL_INCLUDED_
