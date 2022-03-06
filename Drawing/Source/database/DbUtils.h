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

class OdDbSymbolTable;
class OdDbObject;
class OdDbObjectId;
class OdDbMlineStyle;
class OdDbBlockReference;
typedef OdSmartPtr<OdDbMlineStyle> OdDbMlineStylePtr;

class OdDbUtils
{
public:
  static OdDbObjectId symbolTableRecordIdByIndex(const OdDbSymbolTable* pTable, OdInt16 nIndex);
  static OdString symbolTableRecordNameByIndex(const OdDbSymbolTable* pTable, OdInt16 nIndex);
  static TOOLKIT_EXPORT OdInt16 symbolTableRecordIndex(const OdDbSymbolTable* pTable, OdDbObjectId id);
  static OdInt16 symbolTableRecordIndex(const OdDbSymbolTable* pTable, const OdString& pName);

  // These functions will make a substitution if index is invalid to avoid exception
  static TOOLKIT_EXPORT OdDbObjectId symbolTableRecordIdByIndex(const OdDbSymbolTable* pTable, OdInt16 nIndex, const OdDbObjectId& substituteId);
  static TOOLKIT_EXPORT OdDbObjectId linetypeIdByIndex(int nIndex, OdDbDatabase *pDb, const OdDbObjectId& substituteId);
  static TOOLKIT_EXPORT OdDbObjectId layerIdByIndex(int nIndex, OdDbDatabase *pDb, const OdDbObjectId& substituteId);
  static TOOLKIT_EXPORT OdDbObjectId plotstyleIdByIndex(OdUInt32 nIndex, OdDbDatabase *pDb);

  // pDb parameter is necessary because id may be from external database
  // In such case these functions may return -1
  static TOOLKIT_EXPORT OdInt16 linetypeIndexById(OdDbObjectId id, OdDbDatabase *pDb);
  static TOOLKIT_EXPORT OdInt16 layerIndexById(OdDbObjectId id, OdDbDatabase *pDb);

  static TOOLKIT_EXPORT OdInt8 lineWeightIndex(OdDb::LineWeight lw);
  static TOOLKIT_EXPORT OdDb::LineWeight lineWeightByIndex(OdInt8 lw);

  enum
  {
    kLwIndexByLayer = 29,
    kLwIndexByBlock = 30,
    kLwIndexDefault = 31
  };

  static inline bool FindStartOfSection(OdResBufPtr pResBuf, OdResBufPtr &pStart,
    OdResBufPtr &pPrevStart, const OdString& SectName,
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

  static TOOLKIT_EXPORT void appendAcadXData(OdDbObject* pObj, OdResBufPtr pStart);

  static TOOLKIT_EXPORT OdDbMlineStylePtr createDefaultMlineStyle(OdDbObjectId linetypeId);
  static TOOLKIT_EXPORT void appendAttributeToBlockRef(OdDbBlockReference *pBlkRef, OdDbObjectId insBlkId);

  static TOOLKIT_EXPORT void stubPtrArrayToObjectIdsArray(const OdDbStubPtrArray &stubs, OdDbObjectIdArray &ids);
  static OdDbObjectIdArray stubPtrArrayToObjectIdsArray(const OdDbStubPtrArray &stubs)
  {
    OdDbObjectIdArray ids;
    stubPtrArrayToObjectIdsArray(stubs, ids);
    return ids;
  }
  static TOOLKIT_EXPORT void objectIdsArrayToStubPtrArray(const OdDbObjectIdArray &ids, OdDbStubPtrArray &stubs);
  static OdDbStubPtrArray objectIdsArrayToStubPtrArray(const OdDbObjectIdArray &ids)
  {
    OdDbStubPtrArray stubs;
    objectIdsArrayToStubPtrArray(ids, stubs);
    return stubs;
  }
};

#endif  // DB_UTILS_DEFINED
