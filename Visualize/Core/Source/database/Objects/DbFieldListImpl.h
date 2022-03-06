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

#ifndef OD_DBFIELDLISTIMPL_H
#define OD_DBFIELDLISTIMPL_H

#include "DbDictionaryImpl.h"
#include "DbSystemInternals.h"
#include "DbFieldList.h"
#define STL_USING_MAP
#include "OdaSTL.h"

//*************************************************************************
// OdTvDbFieldList
//*************************************************************************

class OdTvDbFieldListImpl : public OdTvDbObjectImpl
{
  static OdTvDbFieldListImpl* getImpl(const OdTvDbFieldList *pObj)
  { return (OdTvDbFieldListImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  OdTvDbFieldListImpl() : m_UknownFlag(false) {}

  OdTvDbObjectIdArray m_idSet;
  std::map<OdTvDbObjectId, OdTvDbObjectIdArray::size_type> m_idMap; // map from objId to index in m_idSet
  bool          m_UknownFlag;

  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

private:
  friend class OdTvDbFieldList;
};

#endif // OD_DBFIELDLISTIMPL_H
