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

#ifndef _ODDBDIMASSOCIMPL_INCLUDED_
#define _ODDBDIMASSOCIMPL_INCLUDED_


#include "DbSystemInternals.h"
#include "DbDimAssoc.h"
#include "DbObjectImpl.h"

class OdDbDimAssocImpl : public OdDbObjectImpl
{
  static OdDbDimAssocImpl* getImpl(const OdDbDimAssoc *pObj)
  { return (OdDbDimAssocImpl*)OdDbSystemInternals::getImpl(pObj);}

  friend class OdDbDimAssoc;
public:
  OdDbDimAssocImpl();

private:
  OdInt32 associativityFlag() const;
  void setAssocFlag(int pointIndex, bool value);

  OdDbObjectId  m_DimensionId;
  OdUInt8       m_RotatedDimType;
  bool          m_bTransSpace;

  OdDbOsnapPointRefPtr m_Points[OdDbDimAssoc::kMaxPointRefs];

  void audit(OdDbAuditInfo* pAuditInfo);
  
  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  OdDbObjectPtr checkClone(OdDbDimAssoc* pClone, OdDbIdMapping& idMap, OdDbObject* pOwner) const;
};

#endif  // _ODDBDIMASSOCIMPL_INCLUDED_
