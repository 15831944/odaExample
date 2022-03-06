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

#ifndef __NWSHEETINFOIMPL_H__
#define __NWSHEETINFOIMPL_H__

#include "NwSheetInfo.h"
#include "NwSavedItemImpl.h"
#define STL_USING_VECTOR
#include "OdaSTL.h"

//sheet data includes
#include "NwSheetData.h"
#include "NwTreeItem.h"
#include "NwPathLinkMap.h"
#include "Grid/NwGridSystemElement.h"
#include "SelectionSets/NwSelectionSetsElement.h"
#include "NwGeometryCompressSettings.h"
#include "NwAttribute.h"

class OdNwPropertyAttribute;
typedef OdSmartPtr<OdNwPropertyAttribute> OdNwPropertyAttributePtr;

class NWDBEXPORT OdNwSheetInfoImpl : public OdNwSavedItemImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwSheetInfo)
public:
  ODRX_DECLARE_MEMBERS(OdNwSheetInfoImpl);

public:
  OdNwSheetInfoImpl();
  virtual ~OdNwSheetInfoImpl();

public:
  static OdNwSheetInfoImpl* getImpl(const OdNwSheetInfo* pNwSVA);
  static OdNwSheetInfoImpl* getImpl(const OdRxObject* pRxSVA);

public:
  inline OdString getSheetId() const { return m_sheetId; }
  inline NwSheetType::Enum getSheetType() const { return m_sheetType; }
  inline std::vector<OdNwPropertyAttributePtr>& getAttributes() { return m_vAttributes; };
  inline OdString getInitialLoadFile() const { return m_initialLoadFile; }
  inline OdString getInitialLoadSheetId() const { return m_initialLoadSheetId; }
  inline OdString getInitialLoadSheetDisplayName() const { return m_initialLoadSheetDisplayName; }
  OdGUID getSourceGUId() const;
  bool isEnabled() const;

//sheet data getters
public:
  inline OdNwSheetData& getSheetData() { return m_sheetData; }
  inline const OdNwSheetData& getSheetData() const { return m_sheetData; }

public:
  inline void setSheetId(const OdString& val) { m_sheetId = val; }
  inline void setSheetType(NwSheetType::Enum val) { m_sheetType = val; }
  inline void setInitialLoadFile(const OdString& val) { m_initialLoadFile = val; }
  inline void setInitialLoadSheetId(const OdString& val) { m_initialLoadSheetId = val; }
  inline void setInitialLoadSheetDisplayName(const OdString& val) { m_initialLoadSheetDisplayName = val; }
  void setSourceGUId(const OdGUID& val);

//OdNwObjectImpl part
private:
  void subSetDatabaseDefaults(OdNwDatabase* pDb, bool doSubents) override;

protected:
  //sheet info data from stream for OdNwSheetInfo object
  OdString m_sheetId;
  NwSheetType::Enum m_sheetType;
  std::vector<OdNwPropertyAttributePtr> m_vAttributes;
  OdString m_initialLoadFile;
  OdString m_initialLoadSheetId;
  OdString m_initialLoadSheetDisplayName;
  OdGUID m_sourceGUId;
  //sheet data with state for sheet
  OdNwSheetData m_sheetData;
};

typedef OdSmartPtr<OdNwSheetInfoImpl> OdNwSheetInfoImplPtr;

#endif // __NWSHEETINFOIMPL_H__
