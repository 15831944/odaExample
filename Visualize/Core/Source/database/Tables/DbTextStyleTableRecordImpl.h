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

#ifndef _ODDBTEXTSTYLETABLERECORDIMPL_INCLUDED_
#define _ODDBTEXTSTYLETABLERECORDIMPL_INCLUDED_

#include "DbSystemInternals.h"
#include "DbTextStyleTableRecord.h"
#include "Gi/GiTextStyle.h"
#include "DbSymbolTableRecordImpl.h"
#include "ResBuf.h"
#include "OdFont.h"
#include "TextStyleFileDependency.h"


class OdTvDbTextStyleTableRecordImpl
  : public OdTvDbSymbolTableRecordImpl
  , public OdGiTextStyle
{
  static OdTvDbTextStyleTableRecordImpl* getImpl(const OdTvDbTextStyleTableRecord *pObj)
  { return (OdTvDbTextStyleTableRecordImpl*)OdTvDbSystemInternals::getImpl(pObj);}

	// OdTvDbObjectId  m_PrimaryFont;
	// OdTvDbObjectId  m_BigFont;
  
	enum
	{
		kShape     = 1,
		kVertical  = 4
	};

  OdDb::TvTextStyleFileDependency m_FileName;
  OdDb::TvTextStyleFileDependency m_BigFileName;
public:
	double        m_dPriorSize;
  OdUInt32      m_cntChanges; // mtext cache update

  void setGenerationFlags(OdUInt16 flags)
  {
    setBackward((flags & 0x02) != 0);
    setUpsideDown((flags & 0x04) != 0);
  }

  OdUInt16 getGenerationFlags() const
  {
    return OdUInt16((isBackward() ? 0x02 : 0x00) | (isUpsideDown() ? 0x04 : 0x00));
  }
  virtual void setFlags(OdUInt16 val);
  virtual OdUInt16 flags() const;

  OdTvDbTextStyleTableRecordImpl();

  void setTtfParams(OdTvResBuf* pRb)
  {
    // acad sometimes uses this:        instead of this:
    // 1000 <typeface>                  1000 <typeface>
    // 1002 {                           1071 <flags>
    // 1071 <flags>
    // 1002 }
    // 
    // Acad uses the last occurrence of 1000 & 1071 if there are duplicates.
    for ( ; pRb;  pRb = pRb->next()) 
    {
      if (pRb->restype() == 1000)
      {
        ttfdescriptor().setTypeFace(pRb->getString());
      }
      else if (pRb->restype()==1071)     
      {
        ttfdescriptor().setTtfFlags(pRb->getInt32());
      }
    }
  } 

  void setTTFXData(OdTvDbObject *obj);
  
  // void setIsShape(bool value) { SETBIT(m_Flags, kShape, value); }
  // bool isShape() const { return GETBIT(m_Flags, kShape); }

  static void createFontRecords(OdTvDbTextStyleTableRecord *pRec);

  TOOLKIT_EXPORT static void setDefaultVar(OdTvDbTextStyleTableRecord *pRec, OdDb::MeasurementValue measurement = OdDb::kEnglish);

	TOOLKIT_EXPORT static OdUInt16 shapeIndexByName(const OdTvDbObjectId& styleId, const OdString& shapeName);

	TOOLKIT_EXPORT static OdString shapeNameByIndex(const OdTvDbObjectId& styleId, OdUInt16 index);

  virtual void audit (OdTvDbAuditInfo* pAuditInfo);

  // OdTvDbSymbolTableRecordImpl overridden
  //
  virtual void verifyName(OdTvDbAuditInfo* pAuditInfo);
  virtual int verifyName(const OdString& strName, bool bLeadAsteriskAllowed = false) const;
  virtual OdString getDxfName() const;
  virtual bool mangleName(
    OdDb::DeepCloneType cloneType,
    OdDb::DuplicateRecordCloning drc,
    const OdString& recName,
    unsigned index = 0,
    const OdString& xrefName = OdString::kEmpty);
  void adjustXrefDependenceFromDXF(OdTvDbSymbolTable* pBlockTable);
  void bindXrefRecord(OdTvDbIdPair& idPair, OdTvDbIdMapping& idMap, OdTvDbIdMapping& mergeMap);

  bool isAnnotative() const { return isAnnotativeByXdata(); }

  friend class OdTvDbTextStyleTableRecord;
  friend class OdTvDwgR12FileLoader;
  friend class OdTvDwgR12FileWriter;
  friend class OdTvDbMTextImpl;
  friend class OdTvDbTextImpl;
#ifndef PROTECTED_DLL_BUILDING // warning with dll linkage - no need in key module anyway
  friend void giFromDbTextStyle(const OdTvDbTextStyleTableRecord*, OdGiTextStyle&);
#endif // PROTECTED_DLL_BUILDING

};

#endif //_ODDBTEXTSTYLETABLERECORDIMPL_INCLUDED_
