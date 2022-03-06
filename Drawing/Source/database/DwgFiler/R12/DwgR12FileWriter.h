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

class OdDbText;
class OdPolylineBaseImpl;
class OdDbVertexImpl;
class OdDbDimensionImpl;
class OdEntitySeqEndContainer;

//----------------------------------------------------------
//
// OdDwgR12FileWriter
//
//----------------------------------------------------------
class OdDwgR12FileWriter : public OdDwgFileController,
                           public DwgR12FileInfo
{
  friend class DwgR12IOContext;
public :
  ODRX_DECLARE_MEMBERS(OdDwgR12FileWriter);
  OdDwgR12FileWriter() {}
  void writeDatabase(OdStreamBuf* pOpenedIo, OdDbDatabase* pDbToSave);

private:
  //
  // The following methods used to load file header, tables, blocks, entities
  //
  void writeHeader              ();
  void writeFileEnd             ();
  void writeEntitiesList        ();
  void writeBlockRecordEntities ();
  void writeTables              (OdDbDwgFiler* pFiler);
  void writeTablesToFile        (OdStreamBuf* pBuff);
  void writeTable               (OdDbDwgFiler* pFiler, OdUInt8 i);
  void writeEntities            (OdDbBlockTableRecord* pRecord);
  void prepareEntity            (OdDbEntity* pEntity);
  void writeEntity              (OdDbEntity* pEntity);
  void writeEntityCommonData    (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writeComplexEntity       (OdEntitySeqEndContainer* pContainer);

  //
  // The following methods used to write certain table record
  //
  bool writeSymbolTR   (OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);
  bool writeBlockTR    (OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);
  bool writeDimStyleTR (OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);
  bool writeLayerTR    (OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);
  bool writeLinetypeTR (OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);
  bool writeRegAppTR   (OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);
  bool writeTextStyleTR(OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);
  bool writeUcsTR      (OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);
  bool writeViewTR     (OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);
  bool writeViewportTR (OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);
  bool writeVXTR       (OdDbDwgFiler* pFiler, OdDbSymbolTableRecord* pSTR);

  //
  // The following methods used to write certain entity
  //
  void writeEntity              (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writeText                (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writeAttributeDefinition (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writeAttribute           (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writeArc                 (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writeCircle              (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writeLine                (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writePoint               (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void write2dPolyline          (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void write3dPolyline          (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writePolyFaceMesh        (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writePolygonMesh         (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writeShape               (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writeTrace               (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void write2dVertex            (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writePolyVertex          (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writeFaceRecord          (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writeFace                (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writeBlockBegin          (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writeBlockEnd            (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writeBlockReference      (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writeMInsertBlock        (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void write3PointAngularDimension(OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writeAlignedDimension      (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writeOrdinateDimension     (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writeRadialDimension       (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writeViewport            (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writeSequenceEnd         (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);

  // Support methods
  void loadTextData (OdDbDwgFiler* pFiler, OdDbText* pEntity, int nFlags);
  void writePolylineCommonData (OdDbDwgFiler* pFiler, OdPolylineBaseImpl* pImpl);
  void writeVertexCommonData (OdDbDwgFiler* pFiler, OdDbVertexImpl* pImpl);
  void writeDimensionCommonDataStart (OdDbDwgFiler* pFiler, OdDbDimensionImpl* pImpl);
  void writeDimensionCommonDataEnd (OdDbDwgFiler* pFiler, OdDbDimensionImpl* pImpl);
  void writeBlockReferenceStart (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  void writeBlockReferenceEnd   (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  inline bool isSkippedBlock (OdDbBlockTableRecordPtr pBTR);
  void writeFixedString(OdDbDwgFiler* pFiler, const char* str, OdUInt32 nLength, const OdDbObjectId& id = OdDbObjectId::kNull);

public:
  //
  // The following members used to choose the object write method by object type
  //
  // Typedef of pointer to object write method
  typedef void (OdDwgR12FileWriter::*WriteMethod) (OdDbDwgFiler* pFiler, OdDbEntity* pEntity);
  // Entity write info structure
  struct DwgR12EntityWriteInfo
  {
    const OdChar*      m_strName;
    OdUInt32           m_nEntityType;
    WriteMethod        m_pWriteMethod;
  };

  // Typedef of table ptr
  typedef OdDbObjectId& (OdDbDatabaseImpl::*TableIdPtr)();
  // Typedef of pointer to STR write method
  typedef bool (OdDwgR12FileWriter::*WriteRecMethod) (OdDbDwgFiler*, OdDbSymbolTableRecord*);

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
  virtual OdDbObjectPtr loadObject(OdUInt64) { ODA_FAIL(); return OdDbObjectPtr(); };
};

typedef OdSmartPtr<OdDwgR12FileWriter> OdDwgR12FileWriterPtr;

inline
bool OdDwgR12FileWriter::isSkippedBlock(OdDbBlockTableRecordPtr pRec)
{
  // Skip ModelSpace, PaperSpace
  return pRec->objectId() == database()->getModelSpaceId() ||
         pRec->objectId() == database()->getPaperSpaceId(); 
         //|| ( pBTR->objectId() == OdDbSymUtil::getBlockId ("*Paper_Space0", database()) &&
         //    pBTR->newIterator()->done() );
}

#endif //_DWGR12FILEWRITER_INCLUDED_
