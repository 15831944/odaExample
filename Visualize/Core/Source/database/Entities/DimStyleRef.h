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
  OdTvDbObjectId m_DStyleId;
public:
  DimStyleRef() : T()/*, m_DStyleIndx(0)*/  {}

  OdTvDbObjectId dimStyleId() const
  {
/*
    OdTvDbDatabase* pDb = T::database();
    if (!pDb)
      return OdTvDbObjectId::kNull;

    OdTvDbDimStyleTablePtr pTable = pDb->getDimStyleTableId().safeOpenObject();
    return OdTvDbDimStyleTableImpl::getImpl(pTable)->getByIndex(m_DStyleIndx);
*/
    return m_DStyleId;
  }

  OdString dimStyleName() const
  {
/*
    OdTvDbDatabase* pDb = T::database();
    if (!pDb)
      return OdString();

    OdTvDbDimStyleTablePtr pTable = pDb->getDimStyleTableId().safeOpenObject();
    return OdTvDbDimStyleTableImpl::getImpl(pTable)->getNameByIndex(m_DStyleIndx);
*/
    return OdTvDbSymUtil::getSymbolName(m_DStyleId);
  }
  void setDimStyle(OdTvDbObjectId id)
  {
/*
    if (id.isErased())
    {
      m_DStyleIndx = 0;
    }
    else
    {
      OdTvDbDatabase* pDb = id.database();
			T::setDatabase(pDb);
      OdTvDbDimStyleTablePtr pTable = pDb->getDimStyleTableId().safeOpenObject(OdDb::kForWrite);
      OdTvDbDimStyleTableImpl* pTableImpl = OdTvDbDimStyleTableImpl::getImpl(pTable);
      OdTvDbDimStyleTableImpl::sorted_iterator iter;

      OdTvDbSymbolTableRecordPtr pRec = id.safeOpenObject(OdDb::kForWrite);
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
    OdTvDbDatabase* pDb = T::database();
    if (!pDb)
      throw OdError(eNoDatabase);
/*
    OdTvDbDimStyleTablePtr pTable = pDb->getDimStyleTableId().safeOpenObject();
    m_DStyleIndx = OdTvDbDimStyleTableImpl::getImpl(pTable)->getIndexByName(name);
*/
    m_DStyleId = OdTvDbSymUtil::getDimStyleId(name, pDb);
  }

  // Overriden
  void audit (OdTvDbAuditInfo* pAuditInfo)
  {
    T::audit(pAuditInfo);

    // Check DIMSTYLE
    OdTvDbDimStyleTableRecordPtr pDs = OdTvDbDimStyleTableRecord::cast(m_DStyleId.openObject());
    if (pDs.isNull())
    {
      OdTvDbHostAppServices* pHostApp = this->database()->appServices();
      OdTvDbObjectPtr pObj = this->objectId().openObject();

      OdTvDbObjectId dsId;
      OdTvDbDatabase* pDb = T::database();
      OdString strDefName;
      if (pDb)
      {
        dsId = this->database()->getDimStyleStandardId();
        strDefName = OdTvDbSymUtil::getSymbolName(dsId);
      }

      pAuditInfo->errorsFound(1);
      pAuditInfo->printError(pObj,
        pHostApp->formatMessage(sidDimStyle, odTvDbGetObjectIdName(m_DStyleId).c_str()),
        pHostApp->formatMessage(sidVarValidInvalid),
        strDefName);
      if (pAuditInfo->fixErrors() && !dsId.isNull())
      {
        m_DStyleId = dsId;
        pAuditInfo->errorsFixed(1);
      }
    }

    OdTvDimensionInfo::auditDimOverrides(pAuditInfo, T::objectId());
  }

  void processOverrideReferences( OdTvDbDwgFiler * pFiler, const OdTvDbEntity* pEnt, int nFromDxf, int nToDxf)
  {
    if (T::m_pXData && pFiler->usesReferences())
    {
      OdTvResBufPtr pRb;
      for (int nDxf = nFromDxf; nDxf <= nToDxf; ++nDxf)
      {
        pRb = getDimVar(pEnt, nDxf);
        if (!pRb.isNull())
        {
          try
          {
            OdTvDbObjectId id = pRb->getObjectId(T::database());
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
