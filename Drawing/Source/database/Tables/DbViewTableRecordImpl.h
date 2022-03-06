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

#ifndef _ODDBVIEWTABLERECORDIMPL_INCLUDED_
#define _ODDBVIEWTABLERECORDIMPL_INCLUDED_

#include "DbSystemInternals.h"
#include "DbViewTableRecord.h"
#include "DbAbstractViewTableRecordImpl.h"


class OdDbViewTableRecordImpl : public OdDbAbstractViewTableRecordImpl 
{
  static OdDbViewTableRecordImpl* getImpl(const OdDbViewTableRecord *pObj)
  { return (OdDbViewTableRecordImpl*)OdDbSystemInternals::getImpl(pObj);}

  enum 
  {
    PAPERSPACE = 1
  };

  bool isModelView() const;
public:
  OdDbViewTableRecordImpl() : m_bCameraPlottable(false) { }

  bool isPaperSpaceView() const { return GETBIT(m_Flags, PAPERSPACE); }
  void setIsPaperSpaceView(bool value) { SETBIT(m_Flags, PAPERSPACE, value); }

  virtual bool isViewTableRecord() const { return true; }

  // Called for each database object during conversion
  // pObj - interface of object
  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, 
    OdDb::DwgVersion version);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, 
    OdDb::DwgVersion version);
  void audit (OdDbAuditInfo* pAuditInfo);

private:
  bool m_bCameraPlottable;
  OdDbSoftPointerId m_liveSection;
  OdDbObjectId m_camera;

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  static OdDbXrecordPtr viewInfo(OdDbObject* pObj, bool bCreate = false);
  static OdDbXrecordPtr thumbnail(OdDbObject* pObj, bool bCreate = false);

  friend class OdDbViewTableRecord;
  friend class OdDwgR12FileLoader;
  friend class OdDwgR12FileWriter;
};

#endif //_ODDBVIEWTABLERECORDIMPL_INCLUDED_
