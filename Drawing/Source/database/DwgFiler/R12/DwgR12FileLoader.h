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

class OdDbText;
class OdDbBlockReference;
class OdDbDimension;


//----------------------------------------------------------
//
// OdDwgR12FileLoader
//
//----------------------------------------------------------
class OdDwgR12FileLoader : public OdDwgFileController,
                           public DwgR12FileInfo
{
public :
  ODRX_DECLARE_MEMBERS(OdDwgR12FileLoader);
  OdDwgR12FileLoader() {}

  void openR(OdStreamBuf* pOpenedIo);
  void startDbLoading(OdDbDatabase* pDbToLoad, OdDbHostAppProgressMeter* pProgressMeter);
  void getPreviewImg(OdThumbnailImage* /*pPreview*/) {}
  bool supportsPartialLoading() const;

  // Typedef of pointer to entity load method
  typedef void (OdDwgR12FileLoader::*LoadMethod) (OdDbDwgFiler*, OdDbEntityPtr&);
  // Typedef of pointer to STR load method
  typedef void (OdDwgR12FileLoader::*LoadRecMethod) (OdDbDwgFiler*, OdDbSymbolTableRecord*);

protected:
  // Function to load string with known length
  OdAnsiString rdStringR12(OdDbDwgFiler* pFiler, int nLength);

  //
  // The following methods used to load file header, tables, blocks, entities
  //
  void loadFile();
  void loadTables();
  void restoreDefaultDb();
  void loadBlockRecordEntities();
  void loadEntityList();
  void loadEntities(OdDbBlockTableRecord* pPsRec, OdDbBlockTableRecord* pMsRec,
                    OdUInt32 nNextLocBase, OdUInt32 nEndPos);
  bool loadComplexEntityContents(OdDbEntity* pOwnerEntity);
  bool loadEntityHeader();
  virtual void loadHeader();
  virtual void loadTable(OdDwgR12TableRecordType nType);
  virtual void loadTableRecord(OdDwgR12TableRecordType nType, OdDbDwgFiler* pFiler, OdDbSymbolTable* pTable, OdUInt32 recIndex);
  virtual bool loadEntity(OdDbEntityPtr& pEntity);
  // Support methods
  virtual void addDbEntity(OdDbEntityPtr& pEntity, OdDbHandle handle);
  virtual bool seekAddr(OdUInt32 addr, OdString info);
  virtual void checkCrcInfo(OdString info);
  virtual void getRecordId(OdDwgR12TableRecordType nType, OdInt32 nIndex, OdDbObjectId& objId);
  void purge ();
  void purgeByFlag(OdDwgR12TableRecordType nType);

  //
  // The following methods used to load certain table record
  //
  void loadSymbolTR   (OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);
  void loadBlockTR    (OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);
  void loadDimStyleTR (OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);
  void loadLayerTR    (OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);
  void loadLinetypeTR (OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);
  void loadRegAppTR   (OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);
  void loadTextStyleTR(OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);
  void loadUcsTR      (OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);
  void loadViewTR     (OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);
  void loadViewportTR (OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);
  void loadVXTR       (OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);

  //
  // The following methods used to load certain entity
  //
  void loadEntityStub          (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  void loadText                (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  void loadAttributeDefinition (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  void loadAttribute           (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  void loadArc                 (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  void loadCircle              (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  void loadLine                (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  void loadLine3d              (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  void loadPoint               (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  void loadPolyline            (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  void loadShape               (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  void loadTrace               (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  void loadVertex              (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  void loadFace                (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  void loadFaceRecord          (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  void loadBlockBegin          (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  void loadBlockEnd            (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  void loadInsertBlock         (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  void loadDimension           (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  void loadViewport            (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  void loadSequenceEnd         (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  // Support methods
  void loadEntity              (OdDbDwgFiler* pFiler, OdDbEntityPtr& pEntity);
  void loadTextData            (OdDbDwgFiler* pFiler, OdDbText* pEntity, int nFlags);
  void loadBlockReferenceStart (OdDbDwgFiler* pFiler, OdDbBlockReference* pEntity);
  void loadBlockReferenceEnd   (OdDbDwgFiler* pFiler, OdDbBlockReference* pEntity);
  void verifyRecName(OdDbSymbolTable* pTable, OdDbSymbolTableRecord* pRec, OdDwgR12TableRecordType recType, OdUInt32 recIndex);
  void verifyDuplRecName(OdDbSymbolTable* pTable, OdDbSymbolTableRecord* pSTR, OdUInt32 index);
  static void copyDbDimension (OdDbDimension* pDest, OdDbDimension* pSrc);
  static void copyDbEntity (OdDbEntity* pDest, OdDbEntity* pSrc);
  OdDbDatabaseImpl* dbImpl() { return OdDbDatabaseImpl::getImpl(database()); }

  //
  // The following members used to choose the object load method by object type
  //  - array of entity info (enum OdDwgR12EntityType)
  //  - array of symbol table records load methods
  //
  struct DwgR12EntityMap
  {
    const OdChar*       m_strObjectName;
    OdDb::DwgVersion  m_nDwgVersion;
    LoadMethod        m_pMethod;
  };
  static DwgR12EntityMap m_theEntitiesMap[R12_EntityAmount];
  inline void loadEntity(OdDbDwgFiler* pFiler, OdUInt8 nEntityType, OdDbEntityPtr& pEntity);
  inline bool isValidEntityType(OdUInt8 type) const;
  static LoadRecMethod m_LoadRecMethod[R12_TRAmount];

  // The loading context
  DwgR12IOContext m_Context;
  // Stub
  virtual OdDbObjectPtr loadObject(OdUInt64) { return OdDbObjectPtr(); };

  friend class DwgR12IOContext;

  OdBinaryData m_EntityData;
};

//----------------------------------------------------------
//
// OdDwgR12FileLoader inline methods
//
//----------------------------------------------------------
inline
void OdDwgR12FileLoader::loadEntity(OdDbDwgFiler* pFiler, OdUInt8 nEntityType, OdDbEntityPtr& pEntity)
{
  ODA_ASSERT(nEntityType <= R12_EntityAmount);
  ODA_ASSERT(getDwgVer() >= m_theEntitiesMap [nEntityType-1].m_nDwgVersion);
  ODA_ASSERT(m_theEntitiesMap [nEntityType-1].m_pMethod);
  ODA_ASSERT(!m_Context.m_bEntErased);

  (this->*m_theEntitiesMap[nEntityType-1].m_pMethod)(pFiler, pEntity);
}

inline
bool OdDwgR12FileLoader::isValidEntityType(OdUInt8 type) const
{
  return ( type <= R12_EntityAmount
        && type > 0
        && type != 5
        && type != 6
        && type != 10 );
}

#endif //_DWGR12FILELOADER_INCLUDED_
