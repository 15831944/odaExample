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

extern OdResBufPtr getDimVar(const OdDbObjectId& dsid, int dxf, const OdDbObject* pObj);


class OdDbDimStyleTableRecordImpl : public OdDbSymbolTableRecordImpl,
                                    public OdDimensionInfo
{
  static OdDbDimStyleTableRecordImpl* getImpl(const OdDbDimStyleTableRecord *pObj)
  { return (OdDbDimStyleTableRecordImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
  OdDbDimStyleTableRecordImpl() : m_nRevision(0), m_bModifiedForRecompute(false) {}

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
  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version, OdDbAuditInfo* pAuditInfo);
  bool readR14Roundtrip(OdResBufPtr& pRb);
  void readR2010Roundtrip(OdResBufPtr& pRb);

  void audit (OdDbAuditInfo* pAuditInfo);

  static void setDefVar(OdDbDimStyleTableRecord * pRec, OdDb::MeasurementValue measurement)
  {
    getImpl(pRec)->setDefaultVar(measurement);
  }

  static void getDimensionInfo(const OdDbDimStyleTableRecord * pRec, OdDimensionInfo * pInfo)
  {
    *pInfo = *getImpl(pRec);
  }

  static void setDimensionInfo(OdDbDimStyleTableRecord * pRec, OdDimensionInfo * pInfo)
  {
    *((OdDimensionInfo*)getImpl(pRec)) = *pInfo;
  }

  static void getDimstyleData(const OdDbObjectId& dsid, OdDbObject* pObj, const OdDbDimStyleTableRecord * pRec);
  static void setDimstyleData(const OdDbObjectId& dsid, const OdDbObject* pObj, OdDbDimStyleTableRecord * pRec);
  static OdResult setDimstyleDataImpl(OdDbObjectId dsid, const OdDbObject* pObj, OdDbDimStyleTableRecord * pRec);

  void getRtBgrndTxtColor(OdDbObject *pObj);
  void setRtBgrndTxtColor(OdDbObject *pObj);

  void getRtExtLineFixLenEnable(OdDbObject *pObj);
  void setRtExtLineFixLenEnable(OdDbObject *pObj);

  void setRtExtLineFixLen(OdDbObject *pObj);
  void getRtExtLineFixLen(OdDbObject *pObj);

  void getRtJogAngle(OdDbObject *pObj);
  void setRtJogAngle(OdDbObject *pObj);

  void getRtArcSymbolType(OdDbObject *pObj);
  void setRtArcSymbolType(OdDbObject *pObj);

  void getRtDimLinetype(OdDbObject *pObj);
  void setRtDimLinetype(OdDbObject *pObj);

  void getRtDimExt1Linetype(OdDbObject *pObj);
  void setRtDimExt1Linetype(OdDbObject *pObj);

  void getRtDimExt2Linetype(OdDbObject *pObj);
  void setRtDimExt2Linetype(OdDbObject *pObj);

  double getDimBREAK(const OdDbObject* pObj);
  void setDimBREAK(OdDbObject* pObj, double value);

  static double jogSymbolHeight(const OdDbObject* pObj);
  static void setJogSymbolHeight(OdDbObject* pObj, double value);

  static bool getDimTALN(const OdDbObject* pObj);
  static void setDimTALN(OdDbObject* pObj, bool value);

  static bool isModifiedForRecompute(const OdDbObject* pObj);
  static OdUInt32 getRevision(OdDbDimStyleTableRecord* pDim)
  {
    if (pDim == 0)
      return 0;
    return OdDbDimStyleTableRecordImpl::getImpl(pDim)->m_nRevision;
  }
  void setModifiedForRecompute()
  {
    m_bModifiedForRecompute = true;
    ++m_nRevision;
  }

  // OdDbObjectImpl overridden to support m_bModifiedForRecompute flag
  virtual void setModified(bool val);

  bool isAnnotative() const { return isAnnotativeByXdata(); }
private:
  OdUInt32 m_nRevision;
  bool m_bModifiedForRecompute;

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;

  friend class OdDbDimStyleTableRecord;
  friend class DimStyleDxfLoadResolver;
  friend class OdDwgR12FileLoader;
  friend class OdDwgR12FileWriter;
  friend OdResBufPtr getDimVar(const OdDbObjectId& dsid, int dxf, const OdDbObject* pObj);
  friend OdResBufPtr getDimVarFromStyle(const OdDbObjectId& dsid, int dxf, const OdDbDatabase* pDb);
};

#endif //_ODDBDIMSTYLETABLERECORDIMPL_INCLUDED_
