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

#ifndef _ODDBSYMBOLTABLERECORDIMPL_INCLUDED_
#define _ODDBSYMBOLTABLERECORDIMPL_INCLUDED_

#include "../DbSystemInternals.h"
#include "DbSymbolTableRecord.h"
#include "OdString.h"
#include "../Objects/DbObjectImpl.h"
#include "DbIdMapping.h"


class OdDbDwgFiler;
class OdNameIterator;

#define OD_R15_TO_R14_TRUNC_NAMELEN   26    //* AC2000 uses it while saving to minor versions
#define OD_MAX_R14_NAMELEN            31
#define OD_MAX_XREF_TRUNC_NAMELEN      4

class TOOLKIT_EXPORT OdDbSymbolTableRecordImpl : public OdDbObjectImpl
{
  static OdDbSymbolTableRecordImpl* getImpl(const OdDbSymbolTableRecord *pObj)
  { return (OdDbSymbolTableRecordImpl*)OdDbSystemInternals::getImpl(pObj);}

protected:
  OdUInt8  m_Flags;
	OdDbHardPointerId m_XRefBlockId;
  void verifyXrefDepFlagFromDXF();
  virtual void adjustXrefDependenceFromDXF(OdDbSymbolTable* pBlockTable);

public:
  void setDependentOnXref(bool value) { SETBIT(m_Flags, DEPXREF, value); }
  OdString m_Name;
  virtual OdUInt16 flags() const { return m_Flags; }
  virtual void setFlags(OdUInt16 val) { ODA_ASSERT(OdUInt8(val)==val); m_Flags = OdUInt8(val); }
  static OdDbObjectId xRefBlockId(const OdDbSymbolTableRecord* pThis)
  {
    pThis->assertReadEnabled();
    return getImpl(pThis)->m_XRefBlockId;
  }
  static void setXrefBlockId(OdDbSymbolTableRecord* pThis, const OdDbObjectId& xrefBlockId)
  {
    pThis->assertWriteEnabled();
    getImpl(pThis)->m_XRefBlockId = xrefBlockId;
    getImpl(pThis)->setDependentOnXref(!xrefBlockId.isNull());
  }
  static void setXrefResolved(OdDbSymbolTableRecord* pThis, bool isResolved)
  {
    pThis->assertWriteEnabled();
    getImpl(pThis)->setXrefResolved(isResolved);
  }
  static void bindXrefRecord(OdDbSymbolTableRecord* pThis, OdDbIdPair& idPair, OdDbIdMapping& idMap, OdDbIdMapping& mergeMap)
  {
    if (pThis->isDependent())
    {
      pThis->assertWriteEnabled();
      setXrefBlockId(pThis, OdDbObjectId::kNull);
      getImpl(pThis)->bindXrefRecord(idPair, idMap, mergeMap);
    }
  }

  virtual void setXrefBlockId(
    const OdDbObjectId& xrefBlockId,
    OdDbSymbolTableRecord* pRec);
  virtual void mergeXrefTable(
    OdDbIdPair& idPair,
    OdDbSymbolTable* pTable,
    OdDbIdMapping& idMap,
    OdDbSymbolTableRecord* pRec);
  virtual bool mangleName(
    OdDb::DeepCloneType cloneType,
    OdDb::DuplicateRecordCloning drc,
    const OdString& recName,
    unsigned index = 0,
    const OdString& xrefName = OdString::kEmpty);
  virtual void bindXrefRecord(
    OdDbIdPair& idPair, 
    OdDbIdMapping& idMap,
    OdDbIdMapping& mergeMap);

public:
  OdDbSymbolTableRecordImpl() : m_Flags(0) { }

  enum
	{
    // Bits 1, 2, 4, 8 depend on type of entry
		DEPXREF      = 16,
		XREFRESOLVED = 32,
		REFERENCED   = 64,
    PURGED       =128
	};

  bool isDependentOnXref() const { return GETBIT(m_Flags, DEPXREF); }

  bool isXrefResolved() const { return GETBIT(m_Flags, XREFRESOLVED); }
  void setXrefResolved(bool value) { SETBIT(m_Flags, XREFRESOLVED, value); }

  void setReferenced(bool value) { SETBIT(m_Flags, REFERENCED, value); }
  bool isReferenced() const { return GETBIT(m_Flags, REFERENCED); }

  void setPurged(bool value) { SETBIT(m_Flags, PURGED, value); }
  bool isPurged() const { return GETBIT(m_Flags, PURGED); }

  // OdDbObjectImpl overridden
  //
  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void audit(OdDbAuditInfo* pAuditInfo);
  bool subErasePermanently();

  void truncateXRefName(OdDbObjectIdArray& xrefIds);
  virtual void verifyXrefDependence(OdDbAuditInfo* pAuditInfo);

  virtual void verifyName(OdDbAuditInfo* pAuditInfo);
  virtual int verifyName(const OdString& strName, bool bLeadAsteriskAllowed = false) const;
  virtual OdString getName() const;
  virtual void setName(const OdString& name);
  virtual void setKeyName(const OdString& name);
private:
  virtual bool hasXData(OdDb::DwgVersion ver, OdDbFiler::FilerType filerType) const;
  virtual OdString getDxfName() const {return getName();}

  friend class OdDbSymbolTableRecord;
  friend class OdSymbolTableItem;
  friend class OdDbSymbolTableImpl;
  friend class OdDbDxfLoader;
  friend class OdDwgR12FileLoader;
  friend class OdDbVXTableRecord;
  friend class MissingLayerReferenceResolver;
  friend struct OdDbSymbolTableRecordTfPE;
};

#endif //_ODDBSYMBOLTABLERECORDIMPL_INCLUDED_
