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

// DwgRecover.h: interface for the OdDwgRecover class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _OD_DBRECOVER_H_INCLUDED_
#define _OD_DBRECOVER_H_INCLUDED_

class OdDbAuditInfo;

//
// Class to contain object info while recover
// (from ObjectMap, recover result, class)
//
class DwgObjectInfo
{
public:
  DwgObjectInfo ()
    : m_Offset (0)
    , m_ObjectDwgType (0)
    , m_pObjectClass (0) { initState(); }
  DwgObjectInfo (const OdDbObjectId& objectId, OdUInt64 offset)
    : m_ObjectId (objectId)
    , m_Offset (offset)
    , m_ObjectDwgType (0)
    , m_pObjectClass (0) { initState(); }

  // Methods to get object info (set only thru constructor)
  OdDbObjectId getObjectId() const { return m_ObjectId; }
  OdUInt64     getOffset() const { return m_Offset; }
  OdUInt16&    objectDwgType() { return m_ObjectDwgType; }
  OdUInt16     getObjectDwgType() const { return m_ObjectDwgType; }
  const OdRxClass* objectClass() const { return m_pObjectClass; }
  void setObjectClass(const OdRxClass* pClass) { m_pObjectClass = pClass; }
  // Methods to set/get result of object recover
  void initState () { m_bLoaded = false; m_bInvalid = false; }
  void setLoaded() { ODA_ASSERT(!isTriedToLoad()); m_bLoaded = true; }
  void setLoadedWithError() { ODA_ASSERT(!isTriedToLoad()); m_bLoaded = true; m_bInvalid = true;}
  void setInvalid() { ODA_ASSERT(!isTriedToLoad()); m_bInvalid = true;}
  bool isTriedToLoad() const { return m_bLoaded || m_bInvalid; }
  bool isLoaded() const { return m_bLoaded; }
  bool isInvalid() const { return m_bInvalid;}
private:
  // ObjectMap info
  OdDbObjectId m_ObjectId;
  OdUInt64     m_Offset;
  OdUInt16     m_ObjectDwgType;
  // Flags showing result of object recover
  bool m_bLoaded;
  bool m_bInvalid;
  // Pre-loaded object info
  const OdRxClass* m_pObjectClass;
};
typedef OdArray<DwgObjectInfo> DwgObjectInfoArray;


//
// Class to print out recover info
//
class OdDbRecover
{
protected:
  enum OdDwgTableType
  {
    kBlock,
    kLayer,
    kTextStyle,
    kLinetype,
    kView,
    kUCS,
    kViewport,
    kRegApp,
    kDimStyle,
    kVX,
    kTableAmount
  };

  OdDbRecover() : m_pRecoverInfo(NULL), m_pHostApp(NULL), m_nErrors(0) {}
  ~OdDbRecover() {}

  virtual void startDbRecover (OdDbDatabase* pDbToRecover);
  virtual void endDbRecover() = 0;

  DwgObjectInfoArray& objectMap() { return m_ObjectMap; }
  void setAuditInfo(OdDbAuditInfo* pAuditInfo);

  bool seekAddr (OdDwgFileController* pCtlr, OdUInt64 addr, OdString info);
  void checkCRC (OdDwgFileController* pCtlr, OdString info);
  OdUInt32 findSequence (OdDwgFileController* pCtlr, const OdUInt8* pData, OdUInt8 nLength);
  OdBinaryData m_FileBuff;

  void errorsFound (OdUInt32 nErrors) { m_nErrors += nErrors; }
  OdUInt32 numErrors () { return m_nErrors; }
  void printError(OdDbObject* pObj, const OdString& strValue,
                  const OdString& strValidation, const OdString& strDefaultValue);
  void printError(const OdString& strName, const OdString& strValue,
                  const OdString& strValidation, const OdString& strDefaultValue);
  void printInfo (const OdString& strInfo);
  OdDbHostAppServices* hostApp() { ODA_ASSERT(m_pHostApp); return m_pHostApp; }
private:
  DwgObjectInfoArray   m_ObjectMap;
  OdDbAuditInfo*       m_pRecoverInfo;
  OdUInt32             m_nErrors;
  OdDbHostAppServices* m_pHostApp;
protected:
  OdDbAuditInfo*       recoverInfo()  { return m_pRecoverInfo;}
};

#endif // _OD_DBRECOVER_H_INCLUDED_
