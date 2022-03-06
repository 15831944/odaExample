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


#ifndef _ODDBAUDITCONTROLLER_INCLUDED_
#define _ODDBAUDITCONTROLLER_INCLUDED_

#include "DbFiler.h"
#include "DbFilerController.h"
#include "DbStubExt.h"

// This validation constant was gotten via experiments with ACAD.
// But the value correlates with the next known DXF specific.
// During DXF reading all doubles are reading with 2 decimal places of mantissa only
// (for example: 1.e+123 in file  -> DXF reading -> 1.e+12)
const double cdAuditDoubleMaxLimit = 1.0e+100; 

class OdTvDbAuditFiler : public OdRxObjectImpl<OdTvIdFiler>
{
public:
  OdTvDbAuditFiler();

  void audit(OdTvDbObject* pObj);

  //
  // Overridden OdTvDbDwgFiler methods
  //
  OdTvDbFiler::FilerType filerType() const
  {
    return OdTvDbFiler::kCopyFiler;
  }

  void wrSoftOwnershipId(const OdTvDbObjectId& id)
  {
    verifyOwnership(id, OdDb::kSoftOwnershipRef);
  }
  void wrHardOwnershipId(const OdTvDbObjectId& id)
  {
    verifyOwnership(id, OdDb::kHardOwnershipRef);
  }
  void wrSoftPointerId(const OdTvDbObjectId&) {}
  void wrHardPointerId(const OdTvDbObjectId&) {}

  void wrDouble(double val)
  {
    verifyDouble(OD_T("Double"), val);
  }

  void wrPoint2d(const OdGePoint2d& pt)
  {
    verifyDouble(OD_T("X coordinate"), pt.x);
    verifyDouble(OD_T("Y coordinate"), pt.y);
  }

  void wrPoint3d(const OdGePoint3d& pt)
  {
    verifyDouble(OD_T("X coordinate"), pt.x);
    verifyDouble(OD_T("Y coordinate"), pt.y);
    verifyDouble(OD_T("Z coordinate"), pt.z);
  }

  void wrVector2d(const OdGeVector2d& v)
  {
    verifyDouble(OD_T("X offset"), v.x);
    verifyDouble(OD_T("Y offset"), v.y);
  }

  void wrVector3d(const OdGeVector3d& v)
  {
    verifyDouble(OD_T("X offset"), v.x);
    verifyDouble(OD_T("Y offset"), v.y);
    verifyDouble(OD_T("Z offset"), v.z);
  }

  void wrScale3d(const OdGeScale3d& s) 
  {
    verifyDouble(OD_T("X scale"), s.sx, 1.0);
    verifyDouble(OD_T("Y scale"), s.sy, 1.0);
    verifyDouble(OD_T("Z scale"), s.sz, 1.0);
  }

private:
  // Methods to print error messages and collect errors data
  void errorInvalidOwnerId(OdTvDbObject* pChild);
  void errorDuplicateOwnership(const OdTvDbObjectId& entryId);
  void errorInvalidDouble(const OdChar* valName, double val, double valDef);

  // Methods to apply fixes
  void fixDuplicateOwnershipId(OdTvDbObject* pObj);
  void fixInvalidOwnerId(OdTvDbObject* pObj);
  void fixInvalidDouble(OdTvDbObject* pObj);

  // Methods to verify object's values
  void verifyOwnership(const OdTvDbObjectId& id, OdDb::ReferenceType rt)
  {
    if (id.isErased())
      return;

    if (id->flags(kOdDbIdOwned) == kOdDbIdOwned)
    {
      errorDuplicateOwnership(id);
    }
    else
    {
      addReference(id, rt);
      OdTvDbObjectPtr pChild = id.openObject();
      if (pChild.get() && pChild->ownerId() != m_objectId)
      {
        errorInvalidOwnerId(pChild);
      }
    }
  }

  void verifyDouble(const OdChar* valName, double val, double valDef = 0)
  {
    if (m_verifyDouble && fabs(val) >= cdAuditDoubleMaxLimit)
    {
      errorInvalidDouble(valName, val, valDef);
    }
  }

  OdTvDbObjectId           m_objectId;
  std::set<OdTvDbObjectId> m_duplicateOwnershipIds;
  std::set<OdTvDbObjectId> m_invalidOwnerIds;
  int                    m_invalidDouble;
  bool                   m_verifyDouble;
};


class OdTvDbAuditController : public OdRxObjectImpl<OdTvDbFilerController>
{
  virtual OdTvDbObjectPtr loadObject(OdUInt64) { ODA_FAIL(); return OdTvDbObjectPtr(); };
public:
  OdTvDbAuditController() {}
  void auditDatabase(OdTvDbDatabase* pDbToAudit, OdTvDbAuditInfo* pAuditInfo);
  void auditBranch(OdTvDbObjectId id, OdTvDbAuditInfo* pAuditInfo, OdTvDbAuditFiler& auditFiler);
  void auditNamedDictionaries(OdTvDbObjectId id, OdTvDbAuditInfo* pAuditInfo, OdTvDbAuditFiler& auditFiler);
  void startDbAudit(OdTvDbDatabase* pDbToAudit, OdTvDbAuditInfo* pAuditInfo);
  void endDbAudit();
};

#endif // _ODDBAUDITCONTROLLER_INCLUDED_
