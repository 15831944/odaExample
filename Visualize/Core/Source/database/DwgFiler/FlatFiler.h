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

// FlatFiler.h: interface for the OdTvFlatFiler class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _ODFLATFILER_H__INCLUDED_
#define _ODFLATFILER_H__INCLUDED_


#include "DbFiler.h"
#include "OdStreamBuf.h"
#include "RxObjectImpl.h"

#include "TD_PackPush.h"

class TOOLKIT_EXPORT OdTvFlatFiler : public OdTvDbDwgFiler
{
protected:
  OdStreamBufPtr          m_pStream;
public:
  inline OdStreamBuf& io() { return *m_pStream.get(); }
  void setStreamBuf(OdStreamBufPtr pStream) { m_pStream = pStream; }

  OdTvDbFilerController*
                controller() const;
  FilerType     filerType() const;
  void          seek(OdInt64 offset, OdDb::FilerSeekType whence);
  OdUInt64      tell() const;

  void          rdBytes(void* buffer, OdUInt32 nLen);
  OdInt8        rdInt8();
  OdUInt8       rdUInt8();
  bool          rdBool();
  OdInt16       rdInt16();
  OdInt32       rdInt32();
  OdInt64       rdInt64();
  double        rdDouble();
  OdDbHandle    rdDbHandle();
  OdString      rdString();
  OdTvDbObjectId  rdSoftOwnershipId();
  OdTvDbObjectId  rdHardOwnershipId();
  OdTvDbObjectId  rdHardPointerId();
  OdTvDbObjectId  rdSoftPointerId();
  OdGePoint2d   rdPoint2d();
  OdGePoint3d   rdPoint3d();
  OdGeVector2d  rdVector2d();
  OdGeVector3d  rdVector3d();
	OdGeScale3d   rdScale3d();

  void wrBytes(const void* buffer, OdUInt32 nLen);
  void wrBool(bool val);
  void wrInt8(OdInt8 val);
  void wrUInt8(OdUInt8 val);
  void wrInt16(OdInt16 val);
  void wrInt32(OdInt32 val);
  void wrInt64(OdInt64 val);
  void wrDouble(double val);
  void wrDbHandle(const OdDbHandle& val);
  void wrString(const OdString& val);
  void wrSoftOwnershipId(const OdTvDbObjectId& id);
  void wrHardOwnershipId(const OdTvDbObjectId& id);
  void wrSoftPointerId(const OdTvDbObjectId& id);
  void wrHardPointerId(const OdTvDbObjectId& id);
  void wrPoint2d(const OdGePoint2d& pt);
  void wrPoint3d(const OdGePoint3d& pt);
  void wrVector2d(const OdGeVector2d& vec);
  void wrVector3d(const OdGeVector3d& vec);
	void wrScale3d(const OdGeScale3d& point);
};

#include "TD_PackPop.h"

#endif // _ODFLATFILER_H__INCLUDED_
