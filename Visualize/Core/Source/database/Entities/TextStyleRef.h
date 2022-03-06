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

#ifndef TEXTSTYLEREF_DEFINED
#define TEXTSTYLEREF_DEFINED

#include "DbUtils.h"
#include "DbAudit.h"
#include "DbHostAppServices.h"
#include "DbTextStyleTable.h"

template<class T> class TextStyleRef : public T
{
protected:
  mutable OdTvDbSoftPointerId m_textStyleId;
private:
  OdTvDbDatabase* safeGetDb() const
  {
    OdTvDbDatabase  *pDb = T::database();
    if (!pDb)
    {
      throw OdError(eNoDatabase);
    }
    return pDb;
  }
public:
  TextStyleRef() : T() {}

  bool hasDefaultTextStyle() const { return safeGetDb()->getTextStyleStandardId() == textStyleId(); }
  void setDefaultTextStyle() { m_textStyleId = safeGetDb()->getTextStyleStandardId();}

  OdTvDbObjectId textStyleId() const
  {
    if(m_textStyleId.isNull())
    {
      OdTvDbDatabase* pDb = T::database();
      if(pDb)
      {
          m_textStyleId = pDb->getTextStyleStandardId();
      }
    }
    return m_textStyleId;
  }

  OdString textStyleName() const { return OdTvDbSymUtil::getSymbolName(textStyleId()); }

  void setTextStyle(OdTvDbObjectId id)
  {
    m_textStyleId = id;
    if (!T::database())
    {
      T::setDatabase(id.database());
    }
  }

  void setTextStyle(const OdString& name) { setTextStyle(name, T::database()); }

  void setTextStyle(const OdString& name, OdTvDbDatabase* pDb)
  {
    if (!pDb)
      throw OdError(eNoDatabase);
    m_textStyleId = OdTvDbSymUtil::getTextStyleId(name, pDb);
  }

  bool setTextStyleWithCheck(const OdString&  name, OdTvDbFiler* pFiler)
  {
    OdTvDbAuditInfo* pAudit = pFiler->getAuditInfo();
    OdTvDbDatabase* pDb = T::database();
    if (!pDb)
      pDb = pFiler->database();
    if (!pDb)
      throw OdError(eNoDatabase);

    bool                bRet = true;
    OdTvDbObjectId        iTmp;
    OdTvDbSymbolTablePtr  pTable = pDb->getTextStyleTableId().openObject();
    iTmp = pTable->getAt(name);

    if (iTmp.isNull())
    {
      bRet = false;
      if (pAudit)
      {
        OdTvDbHostAppServices* pHostApp = pDb->appServices();
        OdTvDbObjectPtr pObj(T::objectId().openObject());
        pAudit->printError(pObj,
          pHostApp->formatMessage(sidTextTextStyle, name.c_str()),
          pHostApp->formatMessage(sidVarValidInvalid),
          textStyleName());

        pAudit->errorsFound(1);
        pAudit->errorsFixed(1);
      }
    }
    else
    {
      m_textStyleId = iTmp;
    }
    return bRet;
  }
};

#endif  // TEXTSTYLEREF_DEFINED
