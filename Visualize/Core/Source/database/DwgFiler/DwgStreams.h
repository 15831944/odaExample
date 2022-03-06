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
// OdTvDwgFileStream
//
//----------------------------------------------------------
#pragma OD_WARNING_PUSH
#pragma OD_WARNING_DISABLE(4263)

class DBIO_EXPORT OdTvDwgFileStream : public OdTvDwgStream
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDwgFileStream);
  OdTvDwgFileStream ():m_pController(0) {}

	virtual void openR(const OdBinaryData* pBuffer, OdTvDbFilerController* pController);
  virtual void openR(const OdBitBinaryData* pBuffer, OdTvDbFilerController* pController);
	virtual void openW(OdBinaryData* pBuffer, OdTvDbFilerController* pController);

  // OdTvDbFiler overridden
  FilerType filerType() const { return kFileFiler; }
  bool isPersistentMode() const { return true; }
  OdDb::DwgVersion dwgVersion(OdDb::MaintReleaseVer *pnMaintReleaseVer = NULL) const;

  // Overridden read/write functions
	OdTvDbObjectId rdObjectId(OdDb::ReferenceType* pRefType = 0);
  OdTvDbObjectId rdSoftOwnershipId();
  OdTvDbObjectId rdHardOwnershipId();
  OdTvDbObjectId rdHardPointerId();
  OdTvDbObjectId rdSoftPointerId();
  void wrObjectId(OdTvDbObjectId id, OdDb::ReferenceType refType);

  // Read/write functions
  OdDb::ReferenceType rdBitHRef(OdDbHandle& res);
  void wrBitHRef(OdDb::ReferenceType rt, OdUInt64 res);
  void wrBitRelativeHRef(OdUInt64 base, OdUInt64 hRef);

  OdTvDbFilerController* controller() const;

  virtual void rdInitData() {}
  virtual OdUInt16 rdDwgType() { return rdInt16(); }
  virtual void wrDwgType(OdUInt16 val) { wrInt16(val); }

protected:
	virtual OdTvDbObjectId handleToId(const OdDbHandle& h);

  OdTvDbFilerController* m_pController;

  friend class OdTvDwgFileSplitStream;
  friend class OdTvDwgR21FileSplitStream;
};

//----------------------------------------------------------
//
// OdTvDwgFileSplitStream
//
//----------------------------------------------------------
class DBIO_EXPORT OdTvDwgFileSplitStream : public OdTvDwgFileStream
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDwgFileSplitStream);
  OdTvDwgFileSplitStream();
  ~OdTvDwgFileSplitStream();

  // OdTvDwgStream overridden
  void close();

  // OdTvDwgFileStream overridden
  void openR(const OdBinaryData* pBuffer, OdTvDbFilerController* pController);
  void openR(const OdBitBinaryData* pBuffer, OdTvDbFilerController* pController);
  void openW(OdBinaryData* pBuffer, OdTvDbFilerController* pController);

  void openW(OdBinaryData* pBuffer, OdBinaryData* pIdBuffer, OdTvDbFilerController* pController);

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
  // OdTvDwgFileStream overridden
  void rdInitData();

  // Overridden read/write functions
  OdTvDbObjectId rdObjectId(OdDb::ReferenceType* pRefType = 0);
  OdTvDbObjectId rdSoftOwnershipId();
  OdTvDbObjectId rdHardOwnershipId();
  OdTvDbObjectId rdHardPointerId();
  OdTvDbObjectId rdSoftPointerId();
  void wrSoftOwnershipId(const OdTvDbObjectId& id);
  void wrHardOwnershipId(const OdTvDbObjectId& id);
  void wrSoftPointerId(const OdTvDbObjectId& id);
  void wrHardPointerId(const OdTvDbObjectId& id);

  // Write SoftPointer of the R15 list of entities
  virtual void wrRelativeSoftPointerId(const OdTvDbObjectId& idBase, const OdTvDbObjectId& idRef);

  // The methods provide access to ids stream
  void separateIds(bool val);
  OdTvDwgFileStream* getIdStream() const { return m_pIdStream; }
  OdUInt64 getIdStreamPos() { return m_idStreamPos; }

  // The method used by controller to set Id of the current object
  void setObjectId(const OdTvDbObjectId& id) { m_objId = id; }

  // The methods provide access to string stream
  virtual OdTvDwgStream* getStrStream() { return 0; }

protected:
  OdTvDwgFileStream* m_pIdStream;
  OdUInt64 m_dataSizePos;
  OdUInt64 m_idStreamPos;

private :
  OdDbHandle objHandle() const;
  OdTvDbObjectId m_objId;
  OdStaticRxObject<OdTvDwgFileStream> m_IdStream;
};

typedef OdSmartPtr<OdTvDwgFileSplitStream> OdTvDwgFileSplitStreamPtr;

//----------------------------------------------------------
//
// OdTvDwgR21FileSplitStream
//
//----------------------------------------------------------
class DBIO_EXPORT OdTvDwgR21FileSplitStream : public OdTvDwgFileSplitStream
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDwgR21FileSplitStream);
  OdTvDwgR21FileSplitStream();
  ~OdTvDwgR21FileSplitStream();

  // OdTvDwgStream overridden
  void close();

  // OdTvDwgFileStream overridden
  void openR(const OdBinaryData* pBuffer, OdTvDbFilerController* pController);
  void openW(OdBinaryData* pBuffer, OdBinaryData* pIdBuffer, OdBinaryData* pStrBuffer, OdTvDbFilerController* pController);

  // OdTvDwgFileSplitStream overridden
  void rdInitData();
  Pos tellPos();
  void seekPos(Pos pos);

  // Overridden string r/w functions
  OdString rdString();
  void wrString(const OdString& val);

  static void readStrDataLength(OdTvDwgStream* pStream, OdUInt64& endPos, OdUInt64& strsSize);
  static void extractStrData(OdBitBinaryData& binData, OdBitBinaryData& strData);
  static void appendStrData(OdBitBinaryData& binData, const OdBitBinaryData& strData);
  static void appendStrData(OdTvDwgStream* pStream, const OdBinaryData& strData, OdUInt64 bitSize);

  virtual OdTvDwgStream* getStrStream() { return &m_StrStream; }

protected:
  OdStaticRxObject<OdTvDwgR21Stream> m_StrStream;
};

#pragma OD_WARNING_POP

typedef OdSmartPtr<OdTvDwgR21FileSplitStream> OdTvDwgR21FileSplitStreamPtr;


#endif // _OD_DWGFILESTREAM_H_INCLUDED_
