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

#ifndef __NWFILEINFOIMPL_H__
#define __NWFILEINFOIMPL_H__

#include "NwFileInfo.h"
#include "NwSavedGroupItemImpl.h"
#define STL_USING_VECTOR
#include "OdaSTL.h"

class OdNwPropertyAttribute;
typedef OdSmartPtr<OdNwPropertyAttribute> OdNwPropertyAttributePtr;

class NWDBEXPORT OdNwFileInfoImpl : public OdNwSavedGroupItemImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwFileInfo)
public:
  ODRX_DECLARE_MEMBERS(OdNwFileInfoImpl);

public:
  OdNwFileInfoImpl();
  virtual ~OdNwFileInfoImpl();

public:
  static OdNwFileInfoImpl* getImpl(const OdNwFileInfo* pNwSVA);
  static OdNwFileInfoImpl* getImpl(const OdRxObject* pRxSVA);

public:
  OdInt32 getIndexOfSheetId(const OdString& sheetId) const;
  OdString getCurrentSheet() const;
  inline std::vector<OdNwPropertyAttributePtr>& getAttributes() { return m_vAttributes; };
  OdGUID getSourceGuid() const;
  OdGUID getFileVersionGuid() const;

public:
  inline void setCurrentSheet(const OdString& val) { m_currentSheet = val; }
  void setSourceGuid(const OdGUID& val);
  void setFileVersionGuid(const OdGUID& val);

//OdNwObjectImpl methods
private:
  void subSetDatabaseDefaults(OdNwDatabase* pDb, bool doSubents) override;

protected:
  OdString m_currentSheet;
  std::vector<OdNwPropertyAttributePtr> m_vAttributes;
  OdGUID m_sourceGuid;
  OdGUID m_fileVersionGuid;
};

typedef OdSmartPtr<OdNwFileInfoImpl> OdNwFileInfoImplPtr;

#endif // __NWFILEINFOIMPL_H__
