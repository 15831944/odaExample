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

#ifndef _ODDBDIMSTYLETABLERECORDIMPL_INCLUDED_
#define _ODDBDIMSTYLETABLERECORDIMPL_INCLUDED_

#include "DbSystemInternals.h"
#include "DbDimStyleTableRecord.h"
#include "DbSymbolTableRecordImpl.h"
#include "DimensionInfo.h"

extern OdTvResBufPtr getDimVar(const OdTvDbObjectId& dsid, int dxf, const OdTvDbObject* pObj);


class OdTvDbDimStyleTableRecordImpl : public OdTvDbSymbolTableRecordImpl,
                                    public OdTvDimensionInfo
{
  static OdTvDbDimStyleTableRecordImpl* getImpl(const OdTvDbDimStyleTableRecord *pObj)
  { return (OdTvDbDimStyleTableRecordImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  OdTvDbDimStyleTableRecordImpl() : m_nRevision(0), m_bModifiedForRecompute(false) {}

  // This overrides is need for conversions
  OdDbHandle getDimblkHandle() const;
  OdDbHandle getDimldrblkHandle() const;
  OdDbHandle getDimblk1Handle() const;
  OdDbHandle getDimblk2Handle() const;

  void setDimblkHandle(OdDbHandle);
  void setDimldrblkHandle(OdDbHandle);
  void setDimblk1Handle(OdDbHandle);
  void setDimblk2Handle(OdDbHandle);

#define VAR_DEF(type, name, dxf, def_value, metric_def_value, reserve1, reserve2) \
  type getDim##name() const { return m_Dim##name; }     \
  void setDim##name(type val)  { m_Dim##name = val; }

#include "DimVarDefs.h"
#undef VAR_DEF

  // Called for each database object during conversion
  // pObj - interface of object
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version, OdTvDbAuditInfo* pAuditInfo);
  bool readR14Roundtrip(OdTvResBufPtr& pRb);
  void readR2010Roundtrip(OdTvResBufPtr& pRb);

  void audit (OdTvDbAuditInfo* pAuditInfo);

  static void setDefVar(OdTvDbDimStyleTableRecord * pRec, OdDb::MeasurementValue measurement)
  {
    getImpl(pRec)->setDefaultVar(measurement);
  }

  static void getDimensionInfo(const OdTvDbDimStyleTableRecord * pRec, OdTvDimensionInfo * pInfo)
  {
    *pInfo = *getImpl(pRec);
  }

  static void setDimensionInfo(OdTvDbDimStyleTableRecord * pRec, OdTvDimensionInfo * pInfo)
  {
    *((OdTvDimensionInfo*)getImpl(pRec)) = *pInfo;
  }

  static void getDimstyleData(const OdTvDbObjectId& dsid, OdTvDbObject* pObj, const OdTvDbDimStyleTableRecord * pRec);
  static void setDimstyleData(const OdTvDbObjectId& dsid, const OdTvDbObject* pObj, OdTvDbDimStyleTableRecord * pRec);
  static OdResult setDimstyleDataImpl(OdTvDbObjectId dsid, const OdTvDbObject* pObj, OdTvDbDimStyleTableRecord * pRec);

  void getRtBgrndTxtColor(OdTvDbObject *pObj);
  void setRtBgrndTxtColor(OdTvDbObject *pObj);

  void getRtExtLineFixLenEnable(OdTvDbObject *pObj);
  void setRtExtLineFixLenEnable(OdTvDbObject *pObj);

  void setRtExtLineFixLen(OdTvDbObject *pObj);
  void getRtExtLineFixLen(OdTvDbObject *pObj);

  void getRtJogAngle(OdTvDbObject *pObj);
  void setRtJogAngle(OdTvDbObject *pObj);

  void getRtArcSymbolType(OdTvDbObject *pObj);
  void setRtArcSymbolType(OdTvDbObject *pObj);

  void getRtDimLinetype(OdTvDbObject *pObj);
  void setRtDimLinetype(OdTvDbObject *pObj);

  void getRtDimExt1Linetype(OdTvDbObject *pObj);
  void setRtDimExt1Linetype(OdTvDbObject *pObj);

  void getRtDimExt2Linetype(OdTvDbObject *pObj);
  void setRtDimExt2Linetype(OdTvDbObject *pObj);

  double getDimBREAK(const OdTvDbObject* pObj);
  void setDimBREAK(OdTvDbObject* pObj, double value);

  static double jogSymbolHeight(const OdTvDbObject* pObj);
  static void setJogSymbolHeight(OdTvDbObject* pObj, double value);

  static bool getDimTALN(const OdTvDbObject* pObj);
  static void setDimTALN(OdTvDbObject* pObj, bool value);

  static bool isModifiedForRecompute(const OdTvDbObject* pObj);
  static OdUInt32 getRevision(OdTvDbDimStyleTableRecord* pDim)
  {
    if (pDim == 0)
      return 0;
    return OdTvDbDimStyleTableRecordImpl::getImpl(pDim)->m_nRevision;
  }
  void setModifiedForRecompute()
  {
    m_bModifiedForRecompute = true;
    ++m_nRevision;
  }

  // OdTvDbObjectImpl overridden to support m_bModifiedForRecompute flag
  virtual void setModified(bool val);

  bool isAnnotative() const { return isAnnotativeByXdata(); }
private:
  OdUInt32 m_nRevision;
  bool m_bModifiedForRecompute;

  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  friend class OdTvDbDimStyleTableRecord;
  friend class DimStyleDxfLoadResolver;
  friend class OdTvDwgR12FileLoader;
  friend class OdTvDwgR12FileWriter;
  friend OdTvResBufPtr getDimVar(const OdTvDbObjectId& dsid, int dxf, const OdTvDbObject* pObj);
  friend OdTvResBufPtr getDimVarFromStyle(const OdTvDbObjectId& dsid, int dxf, const OdTvDbDatabase* pDb);
};

#endif //_ODDBDIMSTYLETABLERECORDIMPL_INCLUDED_
