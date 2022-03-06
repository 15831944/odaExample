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

#ifndef _ODDBABSTRACTVIEWTABLERECORDIMPL_INCLUDED_
#define _ODDBABSTRACTVIEWTABLERECORDIMPL_INCLUDED_

#include "DbSystemInternals.h"
#include "DbAbstractViewTableRecord.h"
#include "ViInfo.h"
#include "DbSymbolTableRecordImpl.h"

class OdTvDbAbstractViewTableRecordImpl : public OdTvDbSymbolTableRecordImpl, 
                                        public OdTvViInfo
{
  static OdTvDbAbstractViewTableRecordImpl* getImpl(const OdTvDbAbstractViewTableRecord *pObj)
  { return (OdTvDbAbstractViewTableRecordImpl*)OdTvDbSystemInternals::getImpl(pObj);}

  bool m_bUcsSavedWithViewport;
  virtual bool isModelView() const;
public:
  OdTvDbAbstractViewTableRecordImpl();

  void setViewWidth(double value)
  {
    m_dViewWidth = value;
  }
	inline bool isUcsSavedWithViewport() const { return m_bUcsSavedWithViewport; }
  inline void setUcsSavedWithViewport(bool value) { m_bUcsSavedWithViewport = value; }

  virtual bool isViewTableRecord() const { return false; }
  void enableUcsSavedWithViewportForDbViewTableRecord() { if (isViewTableRecord()) setUcsSavedWithViewport(true); }

	double  m_dViewWidth;

  void audit (OdTvDbAuditInfo* pAuditInfo);
protected:
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
private:
  OdResult dwgInFields(OdTvDbDwgFiler* pFiler)
  {
	  setViewHeight(pFiler->rdDouble());
	  m_dViewWidth = pFiler->rdDouble();
    return OdTvViInfo::dwgInFields(pFiler);
  }
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const
  {
	  pFiler->wrDouble(getViewHeight());
	  pFiler->wrDouble(m_dViewWidth);
    OdTvViInfo::dwgOutFields(pFiler);
  }

  friend class OdTvDbAbstractViewTableRecord;
};

#endif //_ODDBABSTRACTVIEWTABLERECORDIMPL_INCLUDED_
