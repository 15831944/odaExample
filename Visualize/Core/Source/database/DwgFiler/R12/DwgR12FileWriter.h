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


#ifndef _DWGR12FILEWRITER_INCLUDED_
#define _DWGR12FILEWRITER_INCLUDED_

#include "DwgR12IOContext.h"
#include "DwgFileController.h"
#include "DbBlockTableRecord.h"

class OdTvDbText;
class OdPolylineBaseImpl;
class OdTvDbVertexImpl;
class OdTvDbDimensionImpl;
class OdTvEntitySeqEndContainer;

//----------------------------------------------------------
//
// OdTvDwgR12FileWriter
//
//----------------------------------------------------------
class OdTvDwgR12FileWriter : public OdTvDwgFileController,
                           public DwgR12FileInfo
{
  friend class DwgR12IOContext;
public :
  ODRX_DECLARE_MEMBERS(OdTvDwgR12FileWriter);
  OdTvDwgR12FileWriter() {}
  void writeDatabase(OdStreamBuf* pOpenedIo, OdTvDbDatabase* pDbToSave);

private:
  //
  // The following methods used to load file header, tables, blocks, entities
  //
  void writeHeader              ();
  void writeFileEnd             ();
  void writeEntitiesList        ();
  void writeBlockRecordEntities ();
  void writeTables              (OdTvDbDwgFiler* pFiler);
  void writeTablesToFile        (OdStreamBuf* pBuff);
  void writeTable               (OdTvDbDwgFiler* pFiler, OdUInt8 i);
  void writeEntities            (OdTvDbBlockTableRecord* pRecord);
  void prepareEntity            (OdTvDbEntity* pEntity);
  void writeEntity              (OdTvDbEntity* pEntity);
  void writeEntityCommonData    (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writeComplexEntity       (OdTvEntitySeqEndContainer* pContainer);

  //
  // The following methods used to write certain table record
  //
  bool writeSymbolTR   (OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);
  bool writeBlockTR    (OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);
  bool writeDimStyleTR (OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);
  bool writeLayerTR    (OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);
  bool writeLinetypeTR (OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);
  bool writeRegAppTR   (OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);
  bool writeTextStyleTR(OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);
  bool writeUcsTR      (OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);
  bool writeViewTR     (OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);
  bool writeViewportTR (OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);
  bool writeVXTR       (OdTvDbDwgFiler* pFiler, OdTvDbSymbolTableRecord* pSTR);

  //
  // The following methods used to write certain entity
  //
  void writeEntity              (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writeText                (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writeAttributeDefinition (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writeAttribute           (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writeArc                 (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writeCircle              (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writeLine                (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writePoint               (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void write2dPolyline          (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void write3dPolyline          (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writePolyFaceMesh        (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writePolygonMesh         (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writeShape               (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writeTrace               (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void write2dVertex            (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writePolyVertex          (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writeFaceRecord          (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writeFace                (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writeBlockBegin          (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writeBlockEnd            (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writeBlockReference      (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writeMInsertBlock        (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void write3PointAngularDimension(OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writeAlignedDimension      (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writeOrdinateDimension     (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writeRadialDimension       (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writeViewport            (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writeSequenceEnd         (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);

  // Support methods
  void loadTextData (OdTvDbDwgFiler* pFiler, OdTvDbText* pEntity, int nFlags);
  void writePolylineCommonData (OdTvDbDwgFiler* pFiler, OdPolylineBaseImpl* pImpl);
  void writeVertexCommonData (OdTvDbDwgFiler* pFiler, OdTvDbVertexImpl* pImpl);
  void writeDimensionCommonDataStart (OdTvDbDwgFiler* pFiler, OdTvDbDimensionImpl* pImpl);
  void writeDimensionCommonDataEnd (OdTvDbDwgFiler* pFiler, OdTvDbDimensionImpl* pImpl);
  void writeBlockReferenceStart (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  void writeBlockReferenceEnd   (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  inline bool isSkippedBlock (OdTvDbBlockTableRecordPtr pBTR);
  void writeFixedString(OdTvDbDwgFiler* pFiler, const char* str, OdUInt32 nLength, const OdTvDbObjectId& id = OdTvDbObjectId::kNull);

public:
  //
  // The following members used to choose the object write method by object type
  //
  // Typedef of pointer to object write method
  typedef void (OdTvDwgR12FileWriter::*WriteMethod) (OdTvDbDwgFiler* pFiler, OdTvDbEntity* pEntity);
  // Entity write info structure
  struct DwgR12EntityWriteInfo
  {
    const OdChar*      m_strName;
    OdUInt32           m_nEntityType;
    WriteMethod        m_pWriteMethod;
  };

  // Typedef of table ptr
  typedef OdTvDbObjectId& (OdTvDbDatabaseImpl::*TableIdPtr)();
  // Typedef of pointer to STR write method
  typedef bool (OdTvDwgR12FileWriter::*WriteRecMethod) (OdTvDbDwgFiler*, OdTvDbSymbolTableRecord*);

private:
  // Array of entity info
  static DwgR12EntityWriteInfo m_theEntitiesMap [];
  // Array of methods to write recs
  static WriteRecMethod m_WriteRecMethod[R12_TRAmount];
  // Method used to get info by class
  const DwgR12EntityWriteInfo* getDwgR12EntityWriteInfo(const OdRxClass* pClass);
  // The loading context
  DwgR12IOContext m_Context;
  // stub
  virtual OdTvDbObjectPtr loadObject(OdUInt64) { ODA_FAIL(); return OdTvDbObjectPtr(); };
};

typedef OdSmartPtr<OdTvDwgR12FileWriter> OdTvDwgR12FileWriterPtr;

inline
bool OdTvDwgR12FileWriter::isSkippedBlock(OdTvDbBlockTableRecordPtr pRec)
{
  // Skip ModelSpace, PaperSpace
  return pRec->objectId() == database()->getModelSpaceId() ||
         pRec->objectId() == database()->getPaperSpaceId(); 
         //|| ( pBTR->objectId() == OdTvDbSymUtil::getBlockId ("*Paper_Space0", database()) &&
         //    pBTR->newIterator()->done() );
}

#endif //_DWGR12FILEWRITER_INCLUDED_
