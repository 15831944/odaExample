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

/////////////////////////////////////////////////////////////////////
// Utils.h
// Database Utility Functions

#ifndef DB_UTILS_DEFINED
#define DB_UTILS_DEFINED

#include "OdaDefs.h"
#include "ResBuf.h"
#include "OdString.h"

class OdTvDbSymbolTable;
class OdTvDbObject;
class OdTvDbObjectId;
class OdTvDbMlineStyle;
class OdTvDbBlockReference;
typedef OdSmartPtr<OdTvDbMlineStyle> OdTvDbMlineStylePtr;

class OdTvDbUtils
{
public:
  static OdTvDbObjectId symbolTableRecordIdByIndex(const OdTvDbSymbolTable* pTable, OdInt16 nIndex);
  static OdString symbolTableRecordNameByIndex(const OdTvDbSymbolTable* pTable, OdInt16 nIndex);
  static TOOLKIT_EXPORT OdInt16 symbolTableRecordIndex(const OdTvDbSymbolTable* pTable, OdTvDbObjectId id);
  static OdInt16 symbolTableRecordIndex(const OdTvDbSymbolTable* pTable, const OdString& pName);

  // These functions will make a substitution if index is invalid to avoid exception
  static TOOLKIT_EXPORT OdTvDbObjectId symbolTableRecordIdByIndex(const OdTvDbSymbolTable* pTable, OdInt16 nIndex, const OdTvDbObjectId& substituteId);
  static TOOLKIT_EXPORT OdTvDbObjectId linetypeIdByIndex(int nIndex, OdTvDbDatabase *pDb, const OdTvDbObjectId& substituteId);
  static TOOLKIT_EXPORT OdTvDbObjectId layerIdByIndex(int nIndex, OdTvDbDatabase *pDb, const OdTvDbObjectId& substituteId);
  static TOOLKIT_EXPORT OdTvDbObjectId plotstyleIdByIndex(OdUInt32 nIndex, OdTvDbDatabase *pDb);

  // pDb parameter is necessary because id may be from external database
  // In such case these functions may return -1
  static TOOLKIT_EXPORT OdInt16 linetypeIndexById(OdTvDbObjectId id, OdTvDbDatabase *pDb);
  static TOOLKIT_EXPORT OdInt16 layerIndexById(OdTvDbObjectId id, OdTvDbDatabase *pDb);

  static TOOLKIT_EXPORT OdInt8 lineWeightIndex(OdDb::LineWeight lw);
  static TOOLKIT_EXPORT OdDb::LineWeight lineWeightByIndex(OdInt8 lw);

  enum
  {
    kLwIndexByLayer = 29,
    kLwIndexByBlock = 30,
    kLwIndexDefault = 31
  };

  static inline bool FindStartOfSection(OdTvResBufPtr pResBuf, OdTvResBufPtr &pStart,
    OdTvResBufPtr &pPrevStart, const OdString& SectName,
    int restype = 102)
  {
    pPrevStart.release();
    do
    {
      if (pResBuf->restype() == restype && !pResBuf->getString().compare(SectName))
      {
        pStart = pResBuf;
        return true;
      }
      pPrevStart = pResBuf;
			pResBuf = pResBuf->next();
    }
    while (!pResBuf.isNull());
    return false;
  }

  static TOOLKIT_EXPORT void appendAcadXData(OdTvDbObject* pObj, OdTvResBufPtr pStart);

  static TOOLKIT_EXPORT OdTvDbMlineStylePtr createDefaultMlineStyle(OdTvDbObjectId linetypeId);
  static TOOLKIT_EXPORT void appendAttributeToBlockRef(OdTvDbBlockReference *pBlkRef, OdTvDbObjectId insBlkId);

  static TOOLKIT_EXPORT void stubPtrArrayToObjectIdsArray(const OdDbStubPtrArray &stubs, OdTvDbObjectIdArray &ids);
  static OdTvDbObjectIdArray stubPtrArrayToObjectIdsArray(const OdDbStubPtrArray &stubs)
  {
    OdTvDbObjectIdArray ids;
    stubPtrArrayToObjectIdsArray(stubs, ids);
    return ids;
  }
  static TOOLKIT_EXPORT void objectIdsArrayToStubPtrArray(const OdTvDbObjectIdArray &ids, OdDbStubPtrArray &stubs);
  static OdDbStubPtrArray objectIdsArrayToStubPtrArray(const OdTvDbObjectIdArray &ids)
  {
    OdDbStubPtrArray stubs;
    objectIdsArrayToStubPtrArray(ids, stubs);
    return stubs;
  }
};

#endif  // DB_UTILS_DEFINED
