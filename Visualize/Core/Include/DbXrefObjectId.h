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

#ifndef _ODDBXREFOBJECTID_H_INCLUDED_
#define _ODDBXREFOBJECTID_H_INCLUDED_

#include "TD_PackPush.h"

#include "DbObjectId.h"

/** \details
    This class representing an Xref database object Id.

    Corresponding C++ library: TD_Db
    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbXrefObjectId
{
  protected:
    OdTvDbObjectId m_objectId;
    OdDbHandle   m_objectHandle;
  public:
    OdTvDbXrefObjectId() { }

    bool operator ==(const OdTvDbXrefObjectId& xrefId) const
    { return (xrefId.m_objectId == m_objectId) && (xrefId.m_objectHandle == m_objectHandle); }
    bool operator !=(const OdTvDbXrefObjectId& xrefId) const
    { return (xrefId.m_objectId != m_objectId) || (xrefId.m_objectHandle != m_objectHandle); }

    bool isXref() const { return !m_objectHandle.isNull(); }
    bool isValid() const { return m_objectId.isValid(); }

    bool isNull() const { return m_objectId.isNull(); }
    void setNull()
    {
      m_objectId = OdTvDbObjectId::kNull;
      m_objectHandle = OdDbHandle();
    }

    OdTvDbObjectId getLocalId() const
    {
      if (isXref())
        throw OdError(eInvalidXrefObjectId);
      return m_objectId;
    }
    void setLocalId(const OdTvDbObjectId &objectId)
    {
      m_objectId = objectId;
      m_objectHandle = OdDbHandle();
    }

    OdTvDbObjectId getXrefId(OdDbHandle &objectHandle)
    {
      if (!isXref())
        throw OdError(eInvalidXrefObjectId);
      objectHandle = m_objectHandle;
      return m_objectId;
    }
    void setXrefId(const OdTvDbObjectId &objectId, const OdDbHandle &objectHandle)
    {
      if (objectId.isNull())
        throw OdError(eNullObjectId);
      if (objectHandle.isNull())
        throw OdError(eNullHandle);
      m_objectId = objectId;
      m_objectHandle = objectHandle;
    }

    OdTvDbObjectId resolveObjectId() const;

    void serializeToResbuf(OdTvResBufPtr &pResBuf, OdTvResBufPtr &pLastResBuf) const;
    void serializeFromResbuf(const OdTvResBufPtr pResBuf, OdTvResBufPtr &pNextResBuf, const OdTvDbDatabase* pDb);

    // Helpers
    static void seekToResbuf(OdTvResBufPtr &pResBuf, OdTvResBufPtr &pLastResBuf);
};

#include "TD_PackPop.h"

#endif // _ODDBXREFOBJECTID_H_INCLUDED_
