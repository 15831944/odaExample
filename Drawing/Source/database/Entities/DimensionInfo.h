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

#ifndef _ODDIMENSIONINFO_H_
#define _ODDIMENSIONINFO_H_

#include "../VarValRef.h"
#include "DbObjectId.h"
#include "OdString.h"
#include "ResBuf.h"
#include "DbDimStyleTableRecord.h"
#include "OdCodePage.h"
#include "Ge/GePoint2d.h"
#include "Ge/GePoint3d.h"
#include "DbDate.h"
#include "CmColor.h"
#include "DbDatabase.h" // :(


class OdDimInfoResBufValidator
{
  enum
  {
    kString,
    kHandle,
    kDouble,
    kInt16,
    kInt32
  };
public:
  TOOLKIT_EXPORT static const int* xdata_codes();
  TOOLKIT_EXPORT static const int* dxf_codes();
  inline OdDimInfoResBufValidator(bool val, OdResBuf* pRb, const int* code = xdata_codes())
  {
    pRb->setRestype(code[kInt16]);
    pRb->setInt16(OdInt16(val ? 1 : 0));
  }
  inline OdDimInfoResBufValidator(OdUInt8 val, OdResBuf* pRb, const int* code = xdata_codes())
  {
    pRb->setRestype(code[kInt16]);
    pRb->setInt16(val);
  }
  inline OdDimInfoResBufValidator(OdUInt16 val, OdResBuf* pRb, const int* code = xdata_codes())
  {
    pRb->setRestype(code[kInt16]);
    pRb->setInt16(val);
  }
  inline OdDimInfoResBufValidator(OdInt16 val, OdResBuf* pRb, const int* code = xdata_codes())
  {
    pRb->setRestype(code[kInt16]);
    pRb->setInt16(val);
  }
  inline OdDimInfoResBufValidator(OdDbHandle val, OdResBuf* pRb, const int* code = xdata_codes())
  {
    pRb->setRestype(code[kHandle]);
    pRb->setHandle(val);
  }
  inline OdDimInfoResBufValidator(double val, OdResBuf* pRb, const int* code = xdata_codes())
  {
    pRb->setRestype(code[kDouble]);
    pRb->setDouble(val);
  }
  inline OdDimInfoResBufValidator(const OdString& val, OdResBuf* pRb, const int* code = xdata_codes())
  {
    pRb->setRestype(code[kString]);
    pRb->setString(val);
  }
  inline OdDimInfoResBufValidator(OdDbHardPointerId val, OdResBuf* pRb, const int* code = xdata_codes())
  {
    pRb->setRestype(code[kHandle]);
    pRb->setHandle(val.getNonForwardedHandle());
  }
  /*
  inline OdDimInfoResBufValidator(OdChar val, OdResBuf* pRb, const int* code = xdata_codes())
  {
    pRb->setRestype(code[kInt16]);
    pRb->setInt16(val);
  }
  */
  inline OdDimInfoResBufValidator(OdDb::LineWeight val, OdResBuf* pRb, const int* code = xdata_codes())
  {
    pRb->setRestype(code[kInt16]);
    pRb->setInt16(OdInt16(val));
  }
  inline OdDimInfoResBufValidator(OdCmColor val, OdResBuf* pRb, const int* code = xdata_codes())
  {
    pRb->setRestype(code[kInt16]);
    pRb->setInt16(val.colorIndex());
  }
};

class TOOLKIT_EXPORT OdDimensionInfo
{
protected:
  char dummy;

#define VAR_DEF(type, name, dxf, def_value, metric_def_value, reserve1, reserve2)  \
protected:                                                  \
  type  m_Dim##name;                                        \
public:                                                     \
  inline type dim##name() const { return m_Dim##name; }     \
  inline void setDim##name(type val)  { m_Dim##name = val; } \
  static inline type defValDim##name(OdDb::MeasurementValue measurement);

#include "DimVarDefs.h"
#undef VAR_DEF

public:
	OdDimensionInfo();
  void setDefaultVar(OdDb::MeasurementValue measurement);

  OdResBufPtr getByDxfCode(int nCode) const;
  void setByDxfCode(int nCode, const OdResBuf* pRbVal, OdDbDatabase* pDb);

  // Functions implementing virtual access to obsolete variables
  int dimfit() const;
  void setDimfit(int);

  void setDimunit(int val);
  int dimunit() const;

  OdDimensionInfo& operator = (const OdDimensionInfo& diminfo);

  static void auditDimOverrides(OdDbAuditInfo* pAuditInfo, OdDbObjectId objId);
protected:
  void auditDimInfo(OdDbAuditInfo* pAuditInfo, OdDbDatabase* pDb, OdDbObject* pObj = NULL);
};


#define VAR_DEF(type, name, dxf, def, metric_def, reserve1, reserve2) \
type TOOLKIT_EXPORT oddbGetDim##name(const OdDbObjectId& dsid, const OdDbObject* pObj); \
void TOOLKIT_EXPORT oddbSetDim##name(OdDbObject* pObj, type value, bool bValidate = true);\
bool TOOLKIT_EXPORT oddbOverrideFlag_Dim##name(const OdDbObject* pObj);

#include "DimVarDefs.h"
#undef  VAR_DEF

#define VAR_DEF(type, name, dxf, def_value, metric_def_value, reserve1, reserve2)  \
inline type OdDimensionInfo::defValDim##name (OdDb::MeasurementValue measurement) \
{ \
  if (measurement == OdDb::kEnglish) \
    return def_value; \
  else \
    return metric_def_value; \
}
#include "DimVarDefs.h"
#undef VAR_DEF

// Support dimension overrides
TOOLKIT_EXPORT OdResBufPtr getDimVar(const OdDbObject* pObj, int dxf);
TOOLKIT_EXPORT void removeDimVar(OdDbObject* pObj, int dxf);
TOOLKIT_EXPORT void setDimVar(OdDbObject* pObj, int dxf, OdResBuf* pNewVal);

template<class Type>
inline bool safeGetDimVarValue(Type& res, OdResBufPtr pRb, OdDbDatabase* pDb)
{
  if (pRb.isNull()) return false;
  try { res = (Type)OdVarValRef(pRb.get(), pDb); return true; }
  catch(const OdError_InvalidResBuf&) { return false; }
}

#define szRegDSTYLE_DIMEXT_LENGTH   OD_T("ACAD_DSTYLE_DIMEXT_LENGTH")
#define szRegDSTYLE_DIMEXT_ENABLED  OD_T("ACAD_DSTYLE_DIMEXT_ENABLED")
#define szRegDSTYLE_DIMTEXT_FILL    OD_T("ACAD_DSTYLE_DIMTEXT_FILL")
#define szRegDSTYLE_DIMARC_SYMBOL   OD_T("ACAD_DSTYLE_DIMARC_LENGTH_SYMBOL")
#define szRegDSTYLE_JOGANGLE_SYMBOL OD_T("ACAD_DSTYLE_DIMJOGGED_JOGANGLE_SYMBOL")
#define szRegDSTYLE_DIMTALN         OD_T("ACAD_DSTYLE_DIMTALN")
#define szRegDSTYLE_DIMBREAK        OD_T("ACAD_DSTYLE_DIMBREAK")

#define szRegDSTYLE_DIM_LINETYPE      OD_T("ACAD_DSTYLE_DIM_LINETYPE")
#define szRegDSTYLE_DIM_EXT1_LINETYPE OD_T("ACAD_DSTYLE_DIM_EXT1_LINETYPE")
#define szRegDSTYLE_DIM_EXT2_LINETYPE OD_T("ACAD_DSTYLE_DIM_EXT2_LINETYPE")

#define szRegDSTYLE_DIM_FLIPARROW_SYMBOL   OD_T("ACAD_DSTYLE_DIMFLIPARROW_SYMBOL")
#define szRegDSTYLE_DIM_FLIPARROW_WHICH_SYMBOL   OD_T("ACAD_DSTYLE_DIMFLIPARROW_WHICH_SYMBOL")

#endif //_ODDIMENSIONINFO_H_
