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

#ifndef DIMSTYLEREF_DEFINED
#define DIMSTYLEREF_DEFINED

#include "DbDimStyleTableImpl.h"
#include "DbHostAppServices.h"
#include "DimensionInfo.h"

template<class T> class DimStyleRef : public T
{
//  OdUInt16  m_DStyleIndx;
  OdDbObjectId m_DStyleId;
public:
  DimStyleRef() : T()/*, m_DStyleIndx(0)*/  {}

  OdDbObjectId dimStyleId() const
  {
/*
    OdDbDatabase* pDb = T::database();
    if (!pDb)
      return OdDbObjectId::kNull;

    OdDbDimStyleTablePtr pTable = pDb->getDimStyleTableId().safeOpenObject();
    return OdDbDimStyleTableImpl::getImpl(pTable)->getByIndex(m_DStyleIndx);
*/
    return m_DStyleId;
  }

  OdString dimStyleName() const
  {
/*
    OdDbDatabase* pDb = T::database();
    if (!pDb)
      return OdString();

    OdDbDimStyleTablePtr pTable = pDb->getDimStyleTableId().safeOpenObject();
    return OdDbDimStyleTableImpl::getImpl(pTable)->getNameByIndex(m_DStyleIndx);
*/
    return OdDbSymUtil::getSymbolName(m_DStyleId);
  }
  void setDimStyle(OdDbObjectId id)
  {
/*
    if (id.isErased())
    {
      m_DStyleIndx = 0;
    }
    else
    {
      OdDbDatabase* pDb = id.database();
			T::setDatabase(pDb);
      OdDbDimStyleTablePtr pTable = pDb->getDimStyleTableId().safeOpenObject(OdDb::kForWrite);
      OdDbDimStyleTableImpl* pTableImpl = OdDbDimStyleTableImpl::getImpl(pTable);
      OdDbDimStyleTableImpl::sorted_iterator iter;

      OdDbSymbolTableRecordPtr pRec = id.safeOpenObject(OdDb::kForWrite);
      if(pTableImpl->find(id, iter))
      {
        m_DStyleIndx = OdUInt16(*iter);
      }
      else
      {
        pDb->appServices()->warning(eInvalidDimStyle, T::objectId());
        setDimStyle(pTable->add(pRec));
      }
    }
*/
    m_DStyleId = id;
  }

  void setDimStyle(const OdString& name)
  {
    OdDbDatabase* pDb = T::database();
    if (!pDb)
      throw OdError(eNoDatabase);
/*
    OdDbDimStyleTablePtr pTable = pDb->getDimStyleTableId().safeOpenObject();
    m_DStyleIndx = OdDbDimStyleTableImpl::getImpl(pTable)->getIndexByName(name);
*/
    m_DStyleId = OdDbSymUtil::getDimStyleId(name, pDb);
  }

  // Overriden
  void audit (OdDbAuditInfo* pAuditInfo)
  {
    T::audit(pAuditInfo);

    // Check DIMSTYLE
    OdDbDimStyleTableRecordPtr pDs = OdDbDimStyleTableRecord::cast(m_DStyleId.openObject());
    if (pDs.isNull())
    {
      OdDbHostAppServices* pHostApp = this->database()->appServices();
      OdDbObjectPtr pObj = this->objectId().openObject();

      OdDbObjectId dsId;
      OdDbDatabase* pDb = T::database();
      OdString strDefName;
      if (pDb)
      {
        dsId = this->database()->getDimStyleStandardId();
        strDefName = OdDbSymUtil::getSymbolName(dsId);
      }

      pAuditInfo->errorsFound(1);
      pAuditInfo->printError(pObj,
        pHostApp->formatMessage(sidDimStyle, odDbGetObjectIdName(m_DStyleId).c_str()),
        pHostApp->formatMessage(sidVarValidInvalid),
        strDefName);
      if (pAuditInfo->fixErrors() && !dsId.isNull())
      {
        m_DStyleId = dsId;
        pAuditInfo->errorsFixed(1);
      }
    }

    OdDimensionInfo::auditDimOverrides(pAuditInfo, T::objectId());
  }

  void processOverrideReferences( OdDbDwgFiler * pFiler, const OdDbEntity* pEnt, int nFromDxf, int nToDxf)
  {
    if (T::m_pXData && pFiler->usesReferences())
    {
      OdResBufPtr pRb;
      for (int nDxf = nFromDxf; nDxf <= nToDxf; ++nDxf)
      {
        pRb = getDimVar(pEnt, nDxf);
        if (!pRb.isNull())
        {
          try
          {
            OdDbObjectId id = pRb->getObjectId(T::database());
            if (!id.isNull())
              pFiler->addReference(id, OdDb::kHardPointerRef);
          }
          catch (const OdError_InvalidResBuf&)
          {
            continue;
          }
        }
      }
    }
  }

};

#endif  // DIMSTYLEREF_DEFINED
