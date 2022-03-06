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


class OdDbTextStyleTableRecordImpl
  : public OdDbSymbolTableRecordImpl
  , public OdGiTextStyle
{
  static OdDbTextStyleTableRecordImpl* getImpl(const OdDbTextStyleTableRecord *pObj)
  { return (OdDbTextStyleTableRecordImpl*)OdDbSystemInternals::getImpl(pObj);}

	// OdDbObjectId  m_PrimaryFont;
	// OdDbObjectId  m_BigFont;
  
	enum
	{
		kShape     = 1,
		kVertical  = 4
	};

  OdDb::TextStyleFileDependency m_FileName;
  OdDb::TextStyleFileDependency m_BigFileName;
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

  OdDbTextStyleTableRecordImpl();

  void setTtfParams(OdResBuf* pRb)
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

  void setTTFXData(OdDbObject *obj);
  
  // void setIsShape(bool value) { SETBIT(m_Flags, kShape, value); }
  // bool isShape() const { return GETBIT(m_Flags, kShape); }

  static void createFontRecords(OdDbTextStyleTableRecord *pRec);

  TOOLKIT_EXPORT static void setDefaultVar(OdDbTextStyleTableRecord *pRec, OdDb::MeasurementValue measurement = OdDb::kEnglish);

	TOOLKIT_EXPORT static OdUInt16 shapeIndexByName(const OdDbObjectId& styleId, const OdString& shapeName);

	TOOLKIT_EXPORT static OdString shapeNameByIndex(const OdDbObjectId& styleId, OdUInt16 index);

  virtual void audit (OdDbAuditInfo* pAuditInfo);

  // OdDbSymbolTableRecordImpl overridden
  //
  virtual void verifyName(OdDbAuditInfo* pAuditInfo);
  virtual int verifyName(const OdString& strName, bool bLeadAsteriskAllowed = false) const;
  virtual OdString getDxfName() const;
  virtual bool mangleName(
    OdDb::DeepCloneType cloneType,
    OdDb::DuplicateRecordCloning drc,
    const OdString& recName,
    unsigned index = 0,
    const OdString& xrefName = OdString::kEmpty);
  void adjustXrefDependenceFromDXF(OdDbSymbolTable* pBlockTable);
  void bindXrefRecord(OdDbIdPair& idPair, OdDbIdMapping& idMap, OdDbIdMapping& mergeMap);

  bool isAnnotative() const { return isAnnotativeByXdata(); }

  friend class OdDbTextStyleTableRecord;
  friend class OdDwgR12FileLoader;
  friend class OdDwgR12FileWriter;
  friend class OdDbMTextImpl;
  friend class OdDbTextImpl;
#ifndef PROTECTED_DLL_BUILDING // warning with dll linkage - no need in key module anyway
  friend void giFromDbTextStyle(const OdDbTextStyleTableRecord*, OdGiTextStyle&);
  friend OdGiTextStyle giTextStyleFromDb(const OdDbTextStyleTableRecord* pTStyle);
#endif // PROTECTED_DLL_BUILDING

};

#endif //_ODDBTEXTSTYLETABLERECORDIMPL_INCLUDED_
