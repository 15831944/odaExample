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


#ifndef _DWGR12IOCONTEXT_INCLUDED_
#define _DWGR12IOCONTEXT_INCLUDED_

#include "OdPlatformStreamer.h"


enum OdDwgR12EntityType
{
  R12_ENT_LINE = 1,      //1
  R12_ENT_POINT,         //2
  R12_ENT_CIRCLE,        //3
  R12_ENT_SHAPE,         //4
  R12_ENT_ELLIPSE,       //5
  R12_ENT_SPLINE,        //6
  R12_ENT_TEXT,          //7
  R12_ENT_ARC,           //8
  R12_ENT_TRACE,         //9
  R12_ENT_REGION,        //10
  R12_ENT_SOLID,         //11
  R12_ENT_BLOCKBEGIN,    //12
  R12_ENT_ENDBLK,        //13
  R12_ENT_INSERT,        //14
  R12_ENT_ATTDEF,        //15
  R12_ENT_ATTRIB,        //16
  R12_ENT_SEQEND,        //17
  R12_ENT_NEXTLOCATION,  //18
  R12_ENT_POLYLINE,      //19
  R12_ENT_VERTEX,        //20
  R12_ENT_LINE3D,        //21
  R12_ENT_FACE3D,        //22
  R12_ENT_DIMENSION,     //23
  R12_ENT_VIEWPORT,      //24
  R12_EntityAmount = R12_ENT_VIEWPORT
};

enum OdDwgR12TableRecordType
{
  R12_Symbol = 0,
  R12_Block,  
  R12_Linetype,
  R12_Layer,
  R12_TextStyle,
  R12_View,
  R12_UCS,
  R12_Viewport,
  R12_RegApp,
  R12_DimStyle,
  R12_VX,
  R12_TRAmount
};

//----------------------------------------------------------
//
// DwgR12FileInfo - class contained general dwgR12 info
//
//----------------------------------------------------------
class DwgR12FileInfo
{
public:
  // Typedef of table ptr--must be public or some compilers won't allow DwgR12TableMap to access it.
  typedef OdDbObjectId& (OdDbDatabaseImpl::*TableIdPtr)();

protected:

  // STR info structure
  struct DwgR12TableMap
  {
    const OdChar* m_strObjectName;
    OdUInt8     m_Sentinel[32]; // vAC12
    OdUInt16    m_nRecSize;     // vAC12
    OdUInt16    m_nMagicCRC;    // vAC12
    TableIdPtr  m_pTableId;
  };
  // Array of symbol table records info 
  // (order is defined by STR type <enum OdDwgR12TableRecordType>)
  static const DwgR12TableMap m_TableMap[R12_TRAmount];

  // Sentinels (vAC12)
  static const OdUInt8 m_ssEntitiesList[16]; // Sentinel after header and before entities list
  static const OdUInt8 m_esEntitiesList[32]; // Sentinel after entities list and before BlockTableRecord list
  static const OdUInt8 m_ss2ndHdr[64];
  static const OdUInt8 m_es2ndHdr[16];
};


//----------------------------------------------------------
//
// DwgR12IOContext - class to store dwgR12 loading/writing context 
//
//----------------------------------------------------------
class DwgR12IOContext
{
public:
  struct ViewportsInfo
  {
    OdDbStub* m_Id;
    OdUInt32  m_Offset;
  };        

  DwgR12IOContext();
  void clearEntityReadContext();
  void clearEntityWriteContext();
  void clearAll();

  inline void addRecInfo (OdDwgR12TableRecordType nType, OdDbObjectId id, OdString strName);
  inline OdUInt16 getRecIndex (OdDwgR12TableRecordType nType, const OdDbObjectId& id) const;
  inline OdUInt16 getRecIndex (OdDwgR12TableRecordType nType, const OdDbHandle& handle) const;
  inline OdUInt16 getRecIndex (OdDwgR12TableRecordType nType, const OdString& str) const;
  inline OdResult getRecIndex (OdDwgR12TableRecordType nType, const OdDbObjectId& id, OdUInt16& index) const;
  inline const OdDbObjectId& getRecId (OdDwgR12TableRecordType nType, OdUInt32 nIndex) const;
  inline bool getReferencedRecId (OdDwgR12TableRecordType nType, OdUInt32 nIndex, OdDbObjectId& objId) const;
  inline bool isReferencedRec (OdDwgR12TableRecordType nType, OdUInt32 nIndex) const;
  inline const OdString& getRecName (OdDwgR12TableRecordType nType, OdUInt32 nIndex) const;
  inline OdUInt32 getTblSize (OdDwgR12TableRecordType nType) const { return m_TableInfo[nType].getSize(); }
  inline OdUInt16& tblRecSize (OdDwgR12TableRecordType nType) { return m_TableInfo[nType].m_nRecSize; }
  inline OdUInt32& tblRecNumber (OdDwgR12TableRecordType nType) { return m_TableInfo[nType].m_nRecNumber; }
  inline OdUInt32& tblStartAddr (OdDwgR12TableRecordType nType) { return m_TableInfo[nType].m_nStartAddr; }

  inline void setBlockEntitiesOffset (const OdDbObjectId& id, OdUInt32 nFilePos);
  inline void addBlockEntitiesOffset (OdUInt32 nOffset);
  inline OdUInt32 getBlockEntitiesOffset (OdUInt32 nIndex) const;
  inline OdUInt32 getBlockEntitiesOffsetsSize() const;

  inline void setViewportsOffset (const OdDbObjectId& id, OdUInt32 nFilePos);
  inline const ViewportsInfo* getVpInfoByPos (OdUInt32 nFilePos) const;
  inline void addViewportsInfo (OdDbObjectId id, OdUInt32 nOffset);
  inline const OdDbHandle& getHandle() const { return m_Handle; }
  inline void setRdHandle (const OdDbHandle& value) { m_Handle = value; }
  inline void setWrHandle (const OdDbHandle& value) { m_Handle = value; }
  inline void setBlockTableRecords (OdDbBlockTableRecord* pMSRecord, OdDbBlockTableRecord* pPSRecord);
  inline OdDbBlockTableRecord* getObjOwner() const;
  inline bool isBlockObjOwner() const;

  inline OdUInt32 getPmSize();
  inline void initPmStep();
  inline bool isPmStep (OdInt32 nLoaded);
public:
  // Entity context
  OdUInt8               m_nEntType;
  OdUInt16              m_nEntFlags;
  OdInt16               m_nLayerIndex;
  OdUInt8               m_nProperties;
  double                m_dEntElevation;
  bool                  m_bEntErased;
  OdUInt16              m_nEntLength;
  OdUInt8               m_nXDataFlag;
  bool                  m_bIsPSEntity;
  double                m_dThickness;
  bool                  m_bIsLine3dFormat; // Used only for Line entity
  OdBinaryData          m_XDataR12;
private:
  OdDbBlockTableRecord* m_pMSRecord;
  OdDbBlockTableRecord* m_pPSRecord;
  OdDbHandle            m_Handle;
  // Progress  context
  OdUInt32              m_nPmStep;
  OdInt32               m_nPmLoaded;

public:
  // Entities context
  bool     m_bAttribsFollow;
  OdUInt32 m_nEntityStart;
  OdUInt32 m_nNextLocBase;
  OdUInt32 m_nEntitiesEndPos;

  // Complex entities context
  OdDbEntity* m_pOwner; 
  
  // File context
  OdArray<OdUInt32>      m_theBlockEntitiesOffsets;
  OdArray<ViewportsInfo> m_theViewportsInfo;        // write only
  OdStreamBuf*           m_pSTRData;                // write only
  OdUInt16               m_nVpLastIndex;            // write only
  OdUInt16               m_nCurVpEntIndex;
  OdDbDatabase*          m_pDatabase;
  OdUInt32               m_nEntListStart;
  OdUInt32               m_nEntListEnd;
  OdUInt32               m_nBlkDefStart;
  OdUInt32               m_nBlkDefSize;
  OdUInt32               m_nExtraEntStart;
  OdUInt32               m_nExtraEntSize;
  bool                   m_bHandling;
  // Active ViewportTableRecord properties
  OdGePoint2d m_VIEWCTR;
  double      m_VIEWSIZE;
  OdInt16     m_SNAPMODE;
  OdGePoint2d m_SNAPUNIT;
  OdGePoint2d m_SNAPBASE;
  double      m_SNAPANG;
  OdInt16     m_SNAPSTYLE;
  OdInt16     m_SNAPISOPAIR;
  OdInt16     m_GRIDMODE;
  OdGePoint2d m_GRIDUNIT;
  OdGePoint3d m_VPOINT;
  OdInt16     m_FASTZOOM;
  OdGePoint3d m_TARGET;
  double      m_LENSLENGTH;
  double      m_VIEWTWIST;
  double      m_FRONTZ;
  double      m_BACKZ;
  OdInt16     m_UCSICON;
  // Indices & strings of current setting
  OdInt16  m_nCurUcs;
  OdInt16  m_nCurPUcs;
  OdInt16  m_nCurDimStyle;
  OdInt16  m_nCurLayer;
  OdInt16  m_nCurLinetype;
  OdInt16  m_nCurStyle;
  OdString m_strBlkName;
  OdString m_strBlk1Name;
  OdString m_strBlk2Name;
  OdString m_strUCSName;
private:
  class TableInfo
  {
  public:
    TableInfo() { clear(); }
    inline void clear();
    inline void add(OdDbObjectId id, OdString strName);
    inline const OdDbObjectId& getRecId(OdUInt32 i, bool isRef = true) const;
    inline const OdString& getRecName(OdUInt32 i) const;
    inline OdInt32 getRecIndex(const OdDbObjectId& id) const;
    inline OdInt32 getRecIndex(const OdString& str) const;
    inline OdUInt32 getSize() const { return m_RecIds.size(); }
    inline bool isReferenced(OdUInt32 i) const { return m_RecHasRefs[i]; }

    OdUInt16 m_nRecSize;
    OdUInt32 m_nRecNumber;
    OdUInt32 m_nStartAddr;
  private:
    OdArray<OdString>     m_RecNames;
    OdArray<OdDbObjectId> m_RecIds;
    mutable OdArray<bool> m_RecHasRefs;
  } m_TableInfo[R12_TRAmount];
};

//----------------------------------------------------------
//
// DwgR12IOContext::TableInfo inline methods
//
//----------------------------------------------------------
void DwgR12IOContext::TableInfo::clear()
{
  m_RecNames.clear();
  m_RecIds.clear();
  m_RecHasRefs.clear();
  m_nStartAddr = 0;
  m_nRecSize = 0;
  m_nRecNumber = 0;
}

void DwgR12IOContext::TableInfo::add(OdDbObjectId id, OdString strName)
{
  m_RecIds.push_back(id);
  m_RecNames.push_back(strName);
  m_RecHasRefs.push_back(false);
}

const OdDbObjectId& DwgR12IOContext::TableInfo::getRecId(OdUInt32 i, bool isRef) const
{ 
  ODA_ASSERT(i < m_RecIds.size());
  if (isRef)
    m_RecHasRefs[i] = true;
  return m_RecIds[i];
}

const OdString& DwgR12IOContext::TableInfo::getRecName(OdUInt32 i) const
{ 
  ODA_ASSERT(i < m_RecNames.size());
  m_RecHasRefs[i] = true;
  return m_RecNames[i];
}

OdInt32 DwgR12IOContext::TableInfo::getRecIndex(const OdDbObjectId& id) const
{ 
  ODA_ASSERT(!id.isNull());
  if (id.isNull())
    return -1;
  for (OdUInt32 i = 0; i < m_RecIds.size(); ++i)
    if (m_RecIds[i] == id)
      return i;
  return -1;
}

OdInt32 DwgR12IOContext::TableInfo::getRecIndex(const OdString& str) const
{ 
  if (str.isEmpty() || !odStrLen(str))
    return -1;
  for (OdUInt32 i = 0; i < m_RecNames.size(); ++i)
    if (m_RecNames[i] == str)
      return i;
  return -1;
}

//----------------------------------------------------------
//
// DwgR12IOContext inline methods
//
//----------------------------------------------------------
OdUInt16 DwgR12IOContext::getRecIndex (OdDwgR12TableRecordType nType, const OdDbObjectId& id) const
{
  OdInt32 i = m_TableInfo[nType].getRecIndex(id);
  if (i < 0 || i > 0xffff)
    throw OdError_InvalidIndex();
  return OdUInt16(i);
}

OdResult DwgR12IOContext::getRecIndex (OdDwgR12TableRecordType nType, const OdDbObjectId& id, OdUInt16& index) const
{
  OdInt32 i = m_TableInfo[nType].getRecIndex(id);
  index = OdUInt16(i);
  return (i < 0 || i > 0xffff) ? eInvalidIndex : eOk;
}

OdUInt16 DwgR12IOContext::getRecIndex (OdDwgR12TableRecordType nType, const OdDbHandle& handle) const
{
  if (handle.isNull())
    return 0;
  OdDbObjectId id = m_pDatabase->getOdDbObjectId (handle);
  OdInt32 i = m_TableInfo[nType].getRecIndex(id);
  return OdUInt16((i < 0 || i > 0xffff) ? 0 : i);
}

OdUInt16 DwgR12IOContext::getRecIndex (OdDwgR12TableRecordType nType, const OdString& str) const
{
  OdInt32 i = m_TableInfo[nType].getRecIndex(str);
  return OdUInt16((i < 0 || i > 0xffff) ? 0 : i);
}

void DwgR12IOContext::addBlockEntitiesOffset (OdUInt32 nOffset)
{
  m_theBlockEntitiesOffsets.push_back (nOffset);
}

void DwgR12IOContext::addViewportsInfo(OdDbObjectId id, OdUInt32 nOffset)
{
  ViewportsInfo info = {id, nOffset};
  m_theViewportsInfo.push_back (info);
}

void DwgR12IOContext::addRecInfo (OdDwgR12TableRecordType nType, OdDbObjectId id, OdString strName)
{
  m_TableInfo[nType].add(id, strName);
}

bool DwgR12IOContext::getReferencedRecId (OdDwgR12TableRecordType nType, OdUInt32 nIndex, OdDbObjectId& objId) const
{
  objId = nIndex < m_TableInfo[nType].getSize() 
    ? m_TableInfo[nType].getRecId(nIndex) : OdDbObjectId::kNull;
  return !objId.isNull();
}

const OdDbObjectId& DwgR12IOContext::getRecId (OdDwgR12TableRecordType nType, OdUInt32 nIndex) const
{
  ODA_ASSERT(nIndex < m_TableInfo[nType].getSize());
  return m_TableInfo[nType].getRecId(nIndex, false);
}

bool DwgR12IOContext::isReferencedRec (OdDwgR12TableRecordType nType, OdUInt32 nIndex) const
{
  return m_TableInfo[nType].isReferenced(nIndex);
}

const OdString& DwgR12IOContext::getRecName (OdDwgR12TableRecordType nType, OdUInt32 nIndex) const
{
  if (nIndex >= m_TableInfo[nType].getSize())
    throw OdError_InvalidIndex();
  return m_TableInfo[nType].getRecName(nIndex);
}

OdUInt32 DwgR12IOContext::getBlockEntitiesOffset (OdUInt32 nIndex) const
{
  if (nIndex >= m_theBlockEntitiesOffsets.size())
    throw OdError_InvalidIndex();
  return m_theBlockEntitiesOffsets[nIndex];
}

OdUInt32 DwgR12IOContext::getBlockEntitiesOffsetsSize () const
{
  return m_theBlockEntitiesOffsets.size();
}

void DwgR12IOContext::setBlockTableRecords (OdDbBlockTableRecord* pMSRecord,
                           OdDbBlockTableRecord* pPSRecord) 
{ 
  m_pMSRecord = pMSRecord; 
  m_pPSRecord = pPSRecord; 
}

OdDbBlockTableRecord* DwgR12IOContext::getObjOwner () const
{ 
  return m_bIsPSEntity ? m_pPSRecord : m_pMSRecord; 
}

bool DwgR12IOContext::isBlockObjOwner () const
{ 
  return m_pPSRecord == m_pMSRecord; 
} 

void DwgR12IOContext::setBlockEntitiesOffset (const OdDbObjectId& id, OdUInt32 nFilePos)
{
  OdInt32 nIndex = getRecIndex (R12_Block, id);
  ODA_ASSERT (m_pSTRData && nIndex>=0 && nFilePos >= m_nBlkDefStart);

  m_pSTRData->seek(m_theBlockEntitiesOffsets[nIndex], OdDb::kSeekFromStart);
  OdPlatformStreamer::wrInt32(*m_pSTRData, (nFilePos - m_nBlkDefStart) | 0x40000000L);
}

void DwgR12IOContext::setViewportsOffset (const OdDbObjectId& id, OdUInt32 nFilePos)
{
  ODA_ASSERT (m_pSTRData);

  OdUInt32 nOffset = 0;
  for (OdUInt32 i = 0; i<m_theViewportsInfo.size() ; ++i)
  {
    if ( id == OdDbObjectId(m_theViewportsInfo[i].m_Id) )
    {
      nOffset = m_theViewportsInfo[i].m_Offset;
      break;
    }
  }
  if (nOffset>0)
  {
    m_pSTRData->seek(nOffset, OdDb::kSeekFromStart);
    OdPlatformStreamer::wrInt32(*m_pSTRData, nFilePos);
  }
}

const DwgR12IOContext::ViewportsInfo* DwgR12IOContext::getVpInfoByPos (OdUInt32 nFilePos) const
{
  for (OdUInt32 i = 0; i<m_theViewportsInfo.size() ; ++i)
    if (nFilePos == m_theViewportsInfo[i].m_Offset)
      return &m_theViewportsInfo[i];
  return 0;
}

OdUInt32 DwgR12IOContext::getPmSize ()
{
  return 100;
}

void DwgR12IOContext::initPmStep ()
{
  m_nPmLoaded = m_nPmStep = 
    (m_nEntListEnd - m_nEntListStart + m_nBlkDefSize + m_nExtraEntSize) / getPmSize() + 1;
}

bool DwgR12IOContext::isPmStep (OdInt32 nLoaded)
{
  m_nPmLoaded -= nLoaded;
  if (m_nPmLoaded > 0)
    return false;
  m_nPmLoaded = m_nPmStep - m_nPmLoaded;
  return true;
}

#endif //_DWGR12IOCONTEXT_INCLUDED_
