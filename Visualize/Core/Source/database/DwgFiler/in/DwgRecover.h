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

// DwgRecover.h: interface for the OdTvDwgRecover class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _OD_DWGRECOVER_H_INCLUDED_
#define _OD_DWGRECOVER_H_INCLUDED_

#include "DwgInController.h"
#include "DwgStreams.h"
#include "DbRecover.h"

//
// Main recover class
//
class OdTvDwgRecover : public OdTvDwgInController,
                     public OdTvDbRecover
{
  friend class OdTvObjectDwgRecoverStream;
public:
  ODRX_DECLARE_MEMBERS(OdTvDwgRecover);
  OdTvDwgRecover()
    : m_bReconstructedMap(false)
    , m_bSkipComposing(false)
  {}

  void startDbLoading(OdTvDbDatabase* pLoadedDb, OdDbHostAppProgressMeter* pProgressMeter);
  void endDbLoading();
  bool supportsPartialLoading() const  { return false; }
  void setAuditInfo(OdTvDbAuditInfo* pAuditInfo)
  { OdTvDbRecover::setAuditInfo(pAuditInfo);
    OdTvDwgInController::setAuditInfo(pAuditInfo);
  }
  void rdObjectId(OdTvDbDwgFiler& filer, OdTvDbObjectId& resId);

  // Table id in Db header -- public so it can be accessed from struct below.
  typedef OdTvDbObjectId& (OdTvDbDatabaseImpl::*TableIdPtr)();
private:
  // Overridden
  OdTvDbObjectPtr loadObject(OdUInt64 offset);
  void endDbRecover();

  // Recover Db parts methods
  void recoverFileHeader();
  void recoverTables (OdTvDbRecover::OdTvDwgTableType nStartTbl, OdTvDbRecover::OdTvDwgTableType nEndTbl);
  void recoverDictionaries();
  void recoverTableRecords();
  void recoverClasses();
  void recoverObjectMap();
  void recoverObjectMapFromObjects();
  void recoverSecondHeader(OdUInt64 nSecondHeaderAddr);
  void loadSecondHeader(OdUInt64 nSecondHeaderAddr);

  // Support methods
  void getObjectIds (const OdRxClass* pClass, OdTvDbObjectIdArray& ids);
  void loadObjectMapTypes();
  void loadRemains();
  void loadOwnershipObjects();
  void loadRecords (OdTvDwgRecover::OdTvDwgTableType type, bool bWithContent = true);
  void recoverDictionary (OdTvDbDictionaryPtr pRootDict, OdTvDbObjectId& dbDicId,
                          const OdString& className, const OdString& dicName);
  void recoverClass (OdRxClass* pClass);
  OdTvDbObjectId recoverRootId (OdTvDbObjectId id, const OdRxClass& cls);
  OdRxObjectPtr createObject (OdRxClass* pClass);
  void recognizeTable (DwgObjectInfo& objInfo);
  void removeHangingId();
  //OdUInt32 findSequence (const OdUInt8* pData, OdUInt8 nLength);
  void seekSection (OdUInt64 addr1, OdUInt64 addr2, OdString secName, const OdUInt8* pStartSntl = NULL);
  //bool seekAddr (OdUInt32 addr, OdString info);

  //
  // Structs & arrays of Db tables info
  //
  // Tables static info
  struct TableInfo
  {
    const OdRxClass*  m_pTableClass;
    const OdRxClass*  m_pRecordClass;
    TableIdPtr        m_pTableId;
  };
  static TableInfo m_Tables [kTableAmount];
  static void initTableInfo();

  // Tables info from dwg file
  struct DwgTableInfo
  {
    DwgTableInfo() : m_pInfo (0) {}
    DwgObjectInfo*    m_pInfo;
    OdTvDbObjectIdArray m_Ids;
  private:
  };
  DwgTableInfo m_DwgMapTables [kTableAmount];

  //
  // File info
  //
  OdTvDwgFileSectionsInfo   m_SectionInfo2;
  //OdBinaryData            m_FileBuff;

  //
  // Info for reconstruct ObjectMap from objects
  // 
  bool                    m_bReconstructedMap;  // flag shows that ObjectMap reconstructed is from objects
  OdTvDbObjectIdArray       m_HangingIds;         // array of id that was read in dwgIn but missed in ObjectMap
  OdTvDbObjectIdArray       m_PaperSpaceIds;      // used to restore layouts for ps0..N in damaged file

  // Local flag
  bool m_bSkipComposing;
};

typedef OdSmartPtr<OdTvDwgRecover> OdTvDwgRecoverPtr;


class OdTvObjectDwgRecoverStream : public OdTvDwgFileSplitStream
{
  // OdTvDwgFileStream overridden
	virtual OdTvDbObjectId handleToId(const OdDbHandle& h);
};

#endif // _OD_DWGRECOVER_H_INCLUDED_
