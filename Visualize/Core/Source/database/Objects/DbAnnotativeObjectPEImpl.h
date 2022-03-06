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

#ifndef _DBANNOTATIVEOBJECTPEIMPL_H_INCLUDED_
#define _DBANNOTATIVEOBJECTPEIMPL_H_INCLUDED_
#include "DbAnnotativeObjectPE.h"

class DBENT_EXPORT OdTvDbAnnotativeObjectPEImpl : public OdTvDbAnnotativeObjectPE
{
  virtual bool annotative(const OdTvDbObject* pObject) const ODRX_OVERRIDE;
  virtual OdResult setAnnotative(OdTvDbObject* pObject, bool bAnnotative ) ODRX_OVERRIDE;
  virtual OdResult setFromStyle(OdTvDbObject* pObject, bool& bUpdated) ODRX_OVERRIDE;
  virtual bool forceAnnoAllVisible(const OdTvDbObject* pObj) const ODRX_OVERRIDE;
  virtual OdResult setForceAnnoAllVisible(OdTvDbObject* pObj, bool bForce) const ODRX_OVERRIDE;
  virtual OdResult resetScaleDependentProperties(OdTvDbObject* pObject) ODRX_OVERRIDE;
  virtual bool decompose(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version) ODRX_OVERRIDE;
};


class OdTvDbAnnotativeMLeaderPEImpl : public OdTvDbAnnotativeObjectPEImpl
{
  virtual bool annotative(const OdTvDbObject* pObject) const;
  virtual OdResult setAnnotative(OdTvDbObject* pObject, bool bAnnotative );
  virtual OdResult setFromStyle(OdTvDbObject* pObject, bool& bUpdated);
  virtual bool forceAnnoAllVisible(OdTvDbObject* pObj) const;
  virtual OdResult setForceAnnoAllVisible(OdTvDbObject* pObj, bool bForce) const;
  virtual OdResult resetScaleDependentProperties(OdTvDbObject* pObject);
};

class OdTvDbAnnotativeStylePE : public OdTvDbAnnotativeObjectPEImpl
{
  virtual OdResult setAnnotative(OdTvDbObject* pObject, bool bAnnotative );
};

class OdTvDbAnnotativeBlockPE : public OdTvDbAnnotativeObjectPEImpl
{
  virtual OdResult setAnnotative(OdTvDbObject* pObject, bool bAnnotative);
};

class OdTvDbAnnotativeDimensionPE : public OdTvDbAnnotativeObjectPEImpl
{
  virtual OdResult setAnnotative(OdTvDbObject* pObject, bool bAnnotative);
};

DBENT_EXPORT void odtvdbSetAnnoXData(OdTvDbObject* pObject, bool bAnnotative);

#endif //_DBANNOTATIVEOBJECTPEIMPL_H_INCLUDED_
