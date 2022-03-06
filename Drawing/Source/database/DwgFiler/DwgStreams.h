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

#ifndef _OD_DWGFILESTREAM_H_INCLUDED_
#define _OD_DWGFILESTREAM_H_INCLUDED_

#include "DwgStream.h"

//----------------------------------------------------------
//
// OdDwgFileStream
//
//----------------------------------------------------------
#pragma OD_WARNING_PUSH
#pragma OD_WARNING_DISABLE(4263)

class DBIO_EXPORT OdDwgFileStream : public OdDwgStream
{
public:
  ODRX_DECLARE_MEMBERS(OdDwgFileStream);
  OdDwgFileStream ():m_pController(0) {}

	virtual void openR(const OdBinaryData* pBuffer, OdDbFilerController* pController);
  virtual void openR(const OdBitBinaryData* pBuffer, OdDbFilerController* pController);
	virtual void openW(OdBinaryData* pBuffer, OdDbFilerController* pController);

  // OdDbFiler overridden
  FilerType filerType() const { return kFileFiler; }
  bool isPersistentMode() const { return true; }
  OdDb::DwgVersion dwgVersion(OdDb::MaintReleaseVer *pnMaintReleaseVer = NULL) const;

  // Overridden read/write functions
	OdDbObjectId rdObjectId(OdDb::ReferenceType* pRefType = 0);
  OdDbObjectId rdSoftOwnershipId();
  OdDbObjectId rdHardOwnershipId();
  OdDbObjectId rdHardPointerId();
  OdDbObjectId rdSoftPointerId();
  void wrObjectId(OdDbObjectId id, OdDb::ReferenceType refType);

  // Read/write functions
  OdDb::ReferenceType rdBitHRef(OdDbHandle& res);
  void wrBitHRef(OdDb::ReferenceType rt, OdUInt64 res);
  void wrBitRelativeHRef(OdUInt64 base, OdUInt64 hRef);

  OdDbFilerController* controller() const;

  virtual void rdInitData() {}
  virtual OdUInt16 rdDwgType() { return rdInt16(); }
  virtual void wrDwgType(OdUInt16 val) { wrInt16(val); }

protected:
	virtual OdDbObjectId handleToId(const OdDbHandle& h);

  OdDbFilerController* m_pController;

  friend class OdDwgFileSplitStream;
  friend class OdDwgR21FileSplitStream;
};

//----------------------------------------------------------
//
// OdDwgFileSplitStream
//
//----------------------------------------------------------
class DBIO_EXPORT OdDwgFileSplitStream : public OdDwgFileStream
{
public:
  ODRX_DECLARE_MEMBERS(OdDwgFileSplitStream);
  OdDwgFileSplitStream();
  ~OdDwgFileSplitStream();

  // OdDwgStream overridden
  void close();

  // OdDwgFileStream overridden
  void openR(const OdBinaryData* pBuffer, OdDbFilerController* pController);
  void openR(const OdBitBinaryData* pBuffer, OdDbFilerController* pController);
  void openW(OdBinaryData* pBuffer, OdDbFilerController* pController);

  void openW(OdBinaryData* pBuffer, OdBinaryData* pIdBuffer, OdDbFilerController* pController);

  // Control split data functions
  void reserveDataSizePos();
  struct Pos
  {
    OdUInt64 _dataPos;
    OdUInt64 _strPos;
    OdUInt64 _idPos;
  };
  virtual Pos tellPos();
  virtual void seekPos(Pos pos);
  // OdDwgFileStream overridden
  void rdInitData();

  // Overridden read/write functions
  OdDbObjectId rdObjectId(OdDb::ReferenceType* pRefType = 0);
  OdDbObjectId rdSoftOwnershipId();
  OdDbObjectId rdHardOwnershipId();
  OdDbObjectId rdHardPointerId();
  OdDbObjectId rdSoftPointerId();
  void wrSoftOwnershipId(const OdDbObjectId& id);
  void wrHardOwnershipId(const OdDbObjectId& id);
  void wrSoftPointerId(const OdDbObjectId& id);
  void wrHardPointerId(const OdDbObjectId& id);

  // Write SoftPointer of the R15 list of entities
  virtual void wrRelativeSoftPointerId(const OdDbObjectId& idBase, const OdDbObjectId& idRef);

  // The methods provide access to ids stream
  void separateIds(bool val);
  OdDwgFileStream* getIdStream() const { return m_pIdStream; }
  OdUInt64 getIdStreamPos() { return m_idStreamPos; }

  // The method used by controller to set Id of the current object
  void setObjectId(const OdDbObjectId& id) { m_objId = id; }

  // The methods provide access to string stream
  virtual OdDwgStream* getStrStream() { return 0; }

protected:
  OdDwgFileStream* m_pIdStream;
  OdUInt64 m_dataSizePos;
  OdUInt64 m_idStreamPos;

private :
  OdDbHandle objHandle() const;
  OdDbObjectId m_objId;
  OdStaticRxObject<OdDwgFileStream> m_IdStream;
};

typedef OdSmartPtr<OdDwgFileSplitStream> OdDwgFileSplitStreamPtr;

//----------------------------------------------------------
//
// OdDwgR21FileSplitStream
//
//----------------------------------------------------------
class DBIO_EXPORT OdDwgR21FileSplitStream : public OdDwgFileSplitStream
{
public:
  ODRX_DECLARE_MEMBERS(OdDwgR21FileSplitStream);
  OdDwgR21FileSplitStream();
  ~OdDwgR21FileSplitStream();

  // OdDwgStream overridden
  void close();

  // OdDwgFileStream overridden
  void openR(const OdBinaryData* pBuffer, OdDbFilerController* pController);
  void openW(OdBinaryData* pBuffer, OdBinaryData* pIdBuffer, OdBinaryData* pStrBuffer, OdDbFilerController* pController);

  // OdDwgFileSplitStream overridden
  void rdInitData();
  Pos tellPos();
  void seekPos(Pos pos);

  // Overridden string r/w functions
  OdString rdString();
  void wrString(const OdString& val);

  static void readStrDataLength(OdDwgStream* pStream, OdUInt64& endPos, OdUInt64& strsSize);
  static void extractStrData(OdBitBinaryData& binData, OdBitBinaryData& strData);
  static void appendStrData(OdBitBinaryData& binData, const OdBitBinaryData& strData);
  static void appendStrData(OdDwgStream* pStream, const OdBinaryData& strData, OdUInt64 bitSize);

  virtual OdDwgStream* getStrStream() { return &m_StrStream; }

protected:
  OdStaticRxObject<OdDwgR21Stream> m_StrStream;
};

#pragma OD_WARNING_POP

typedef OdSmartPtr<OdDwgR21FileSplitStream> OdDwgR21FileSplitStreamPtr;


#endif // _OD_DWGFILESTREAM_H_INCLUDED_
