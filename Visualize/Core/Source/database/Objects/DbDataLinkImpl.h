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

#ifndef _ODDBDATALINKIMPL_INCLUDED_
#define _ODDBDATALINKIMPL_INCLUDED_

#include "DbObjectImpl.h"
#include "DbCustomData.h"

class OdTvDbDataLinkImpl : public OdTvDbObjectImpl
{
public:
  static OdTvDbDataLinkImpl* getImpl(const OdTvDbDataLink *pObj)
  { return (OdTvDbDataLinkImpl*)OdTvDbSystemInternals::getImpl(pObj); }


public:
  OdTvDbDataLinkImpl() : OdTvDbObjectImpl()
    , m_linkOption(0)
    , m_updateOption(0)
    , m_updateDirection(0)
    , m_errCode(0)
    , m_pathOption(0)
  {
    for (int i = 0; i < 7; ++i)
      m_dateTime[i] = 0;
  }

  OdString m_dataAdapterId;
  OdString m_description;
  OdString m_toolTip;
  OdString m_connectionString;
  OdString m_linkName;

  OdInt32 m_linkOption;
  OdInt32 m_updateOption;
  OdInt32 m_updateDirection;
  OdInt32 m_errCode;
  OdUInt16 m_pathOption;

  OdString m_errMessage;
  
  OdInt16 m_dateTime[7];

  OdCustomDataArray m_customData;

  OdTvDbObjectIdArray m_targetIds;
  OdTvDbObjectId m_tableContent;

  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void addTarget(const OdTvDbObjectId& id);
  void removeTarget(const OdTvDbObjectId& id);

private:
  friend  class OdTvDbDataLink;
};

#endif // _ODDBDATALINKIMPL_INCLUDED_
