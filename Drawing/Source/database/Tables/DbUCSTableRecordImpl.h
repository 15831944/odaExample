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

#ifndef _ODDBUCSTABLERECORDIMPL_INCLUDED_
#define _ODDBUCSTABLERECORDIMPL_INCLUDED_

#include "DbSystemInternals.h"
#include "DbUCSTableRecord.h"
#include "DbSymbolTableRecordImpl.h"
#include "UCSInfo.h"

typedef std::pair<OdInt16, OdGePoint3d> OdUcsBaseOrg;
typedef OdArray<OdUcsBaseOrg, OdMemoryAllocator<OdUcsBaseOrg> > OdUcsBaseOrgArray;

class OdDbUCSTableRecordImpl : public OdDbSymbolTableRecordImpl,
                               public OdUCSInfo
{
public:
  static OdDbUCSTableRecordImpl* getImpl(const OdDbUCSTableRecord *pObj)
  { return (OdDbUCSTableRecordImpl*)OdDbSystemInternals::getImpl(pObj);}

  OdUcsBaseOrgArray m_orthoTypesOrigins;

  OdDbUCSTableRecordImpl();
  void audit(OdDbAuditInfo* pAuditInfo);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version, OdDbAuditInfo* pAuditInfo);

private:
  friend class OdDbUCSTableRecord;
  friend class OdDwgR12FileLoader;
  friend class OdDwgR12FileWriter;
};

#endif //_ODDBUCSTABLERECORDIMPL_INCLUDED_