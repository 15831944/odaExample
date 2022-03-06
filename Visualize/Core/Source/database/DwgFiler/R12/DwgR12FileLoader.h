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

  
#ifndef _DWGR12FILELOADER_INCLUDED_
#define _DWGR12FILELOADER_INCLUDED_

#include "DwgR12IOContext.h"
#include "DwgFileController.h"
#include "R12DwgFiler.h"
#include "DbDatabaseImpl.h"

class OdTvDbText;
class OdTvDbBlockReference;
class OdTvDbDimension;


//----------------------------------------------------------
//
// OdTvDwgR12FileLoader
//
//----------------------------------------------------------
class OdTvDwgR12FileLoader : public OdTvDwgFileController,
                           public DwgR12FileInfo
{
public :
  ODRX_DECLARE_MEMBERS(OdTvDwgR12FileLoader);
  OdTvDwgR12FileLoader() {}

  void openR(OdStreamBuf* pOpenedIo);
  void startDbLoading(OdTvDbDatabase* pDbToLoad, OdDbHostAppProgressMeter* pProgressMeter);
  void getPreviewImg(OdThumbnailImage* /*pPreview*/) {}
  bool supportsPartialLoading() const;

  // Typedef of pointer to entity load method
  typedef void (OdTvDwgR12FileLoader::*LoadMethod) (OdTvDbDwgFiler*, OdTvDbEntityPtr&);
  // Typedef of pointer to STR load method
  typedef void (OdTvDwgR12FileLoader::*LoadRecMethod) (OdTvDbDwgFiler*, OdTvDbSymbolTableRecord*);

protected:
  // Function to load string with known length
  OdAnsiString rdStringR12(OdTvDbDwgFiler* pFiler, int nLength);

  //
  // The following methods used to load file header, tables, blocks, entities
  //
  void loadFile();
  void loadTables();
  void restoreDefaultDb();
  void loadBlockRecordEntities();
  void loadEntityList();
  void loadEntities(OdTvDbBlockTableRecord* pPsRec, OdTvDbBlockTableRecord* pMsRec,
                    OdUInt32 nNextLocBase, OdUInt32 nEndPos);
  bool loadComplexEntityContents(OdTvDbEntity* pOwnerEntity);
  bool loadEntityHeader();
  virtual void loadHeader();
  virtual void loadTable(OdTvDwgR12TableRecordType nType);
  virtual void loadTableRecord(OdTvDwgR12TableRecordType nType, OdTvDbDwgFiler* pFiler, OdTvDbSymbolTable* pTable, OdUInt32 recIndex);
  virtual bool loadEntity(OdTvDbEntityPtr& pEntity);
  // Support methods
  virtual void addDbEntity(OdTvDbEntityPtr& pEntity, OdDbHandle handle);
  virtual bool seekAddr(OdUInt32 addr, OdString info);
  virtual void checkCrcInfo(OdString info);
  virtual void getRecordId(OdTvDwgR12TableRecordType nType, OdInt32 nIndex, OdTvDbObjectId& objId);
  void purge ();
  void purgeByFlag(OdTvDwgR12TableRecordType nType);

  //
  // The following methods used to load certain table record
  //
  void loadSymbolTR   (OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);
  void loadBlockTR    (OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);
  void loadDimStyleTR (OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);
  void loadLayerTR    (OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);
  void loadLinetypeTR (OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);
  void loadRegAppTR   (OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);
  void loadTextStyleTR(OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);
  void loadUcsTR      (OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);
  void loadViewTR     (OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);
  void loadViewportTR (OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);
  void loadVXTR       (OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);

  //
  // The following methods used to load certain entity
  //
  void loadEntityStub          (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  void loadText                (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  void loadAttributeDefinition (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  void loadAttribute           (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  void loadArc                 (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  void loadCircle              (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  void loadLine                (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  void loadLine3d              (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  void loadPoint               (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  void loadPolyline            (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  void loadShape               (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  void loadTrace               (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  void loadVertex              (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  void loadFace                (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  void loadFaceRecord          (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  void loadBlockBegin          (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  void loadBlockEnd            (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  void loadInsertBlock         (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  void loadDimension           (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  void loadViewport            (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  void loadSequenceEnd         (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  // Support methods
  void loadEntity              (OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& pEntity);
  void loadTextData            (OdTvDbDwgFiler* pFiler, OdTvDbText* pEntity, int nFlags);
  void loadBlockReferenceStart (OdTvDbDwgFiler* pFiler, OdTvDbBlockReference* pEntity);
  void loadBlockReferenceEnd   (OdTvDbDwgFiler* pFiler, OdTvDbBlockReference* pEntity);
  void verifyRecName(OdTvDbSymbolTable* pTable, OdTvDbSymbolTableRecord* pRec, OdTvDwgR12TableRecordType recType, OdUInt32 recIndex);
  void verifyDuplRecName(OdTvDbSymbolTable* pTable, OdTvDbSymbolTableRecord* pSTR, OdUInt32 index);
  static void copyDbDimension (OdTvDbDimension* pDest, OdTvDbDimension* pSrc);
  static void copyDbEntity (OdTvDbEntity* pDest, OdTvDbEntity* pSrc);
  OdTvDbDatabaseImpl* dbImpl() { return OdTvDbDatabaseImpl::getImpl(database()); }

  //
  // The following members used to choose the object load method by object type
  //  - array of entity info (enum OdTvDwgR12EntityType)
  //  - array of symbol table records load methods
  //
  struct DwgR12EntityMap
  {
    const OdChar*       m_strObjectName;
    OdDb::DwgVersion  m_nDwgVersion;
    LoadMethod        m_pMethod;
  };
  static DwgR12EntityMap m_theEntitiesMap[R12_EntityAmount];
  inline void loadEntity(OdTvDbDwgFiler* pFiler, OdUInt8 nEntityType, OdTvDbEntityPtr& pEntity);
  inline bool isValidEntityType(OdUInt8 type) const;
  static LoadRecMethod m_LoadRecMethod[R12_TRAmount];

  // The loading context
  DwgR12IOContext m_Context;
  // Stub
  virtual OdTvDbObjectPtr loadObject(OdUInt64) { return OdTvDbObjectPtr(); };

  friend class DwgR12IOContext;

  OdBinaryData m_EntityData;
};

//----------------------------------------------------------
//
// OdTvDwgR12FileLoader inline methods
//
//----------------------------------------------------------
inline
void OdTvDwgR12FileLoader::loadEntity(OdTvDbDwgFiler* pFiler, OdUInt8 nEntityType, OdTvDbEntityPtr& pEntity)
{
  ODA_ASSERT(nEntityType <= R12_EntityAmount);
  ODA_ASSERT(getDwgVer() >= m_theEntitiesMap [nEntityType-1].m_nDwgVersion);
  ODA_ASSERT(m_theEntitiesMap [nEntityType-1].m_pMethod);
  ODA_ASSERT(!m_Context.m_bEntErased);

  (this->*m_theEntitiesMap[nEntityType-1].m_pMethod)(pFiler, pEntity);
}

inline
bool OdTvDwgR12FileLoader::isValidEntityType(OdUInt8 type) const
{
  return ( type <= R12_EntityAmount
        && type > 0
        && type != 5
        && type != 6
        && type != 10 );
}

#endif //_DWGR12FILELOADER_INCLUDED_
