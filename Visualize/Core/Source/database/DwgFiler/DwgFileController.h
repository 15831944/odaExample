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

// DwgFileController.h: interface for the OdTvDwgFileController class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ODDWGFILECONTROLLER_H_INCLUDED_)
#define _ODDWGFILECONTROLLER_H_INCLUDED_


#include "../DbFilerController.h"
#include "StaticRxObject.h"
#include "OdPlatformStreamer.h"

#include "../OdDwgDigitalSignature.h"

class OdTvStreamWithCrc : public OdRxObjectImpl<OdStreamBuf>
{
protected:
  OdStreamBufPtr m_pUnderlyingIo;
  OdTvStreamWithCrc(OdStreamBuf* pStreamBuf) : m_pUnderlyingIo(pStreamBuf) {}
  OdTvStreamWithCrc() {}
public:
  ODRX_DECLARE_MEMBERS(OdTvStreamWithCrc);

  OdUInt64 length();
  OdUInt64 seek(OdInt64 offset, OdDb::FilerSeekType whence);
  OdUInt64 tell();
  bool isEof();
  OdString fileName();
  void truncate();

// ODA_MT_DBIO_BEGIN
  OdStreamBuf* underlyingStream() { return m_pUnderlyingIo; }
// ODA_MT_DBIO_END
};

class OdTvStreamWithCrc16 : public OdTvStreamWithCrc
{
  OdUInt16 m_nCRC;
  static const OdUInt16 m_crcTable[];
  void crc8(OdUInt8 byte)
  {
    OdUInt8 nTemp;
    nTemp  = (OdUInt8)(byte ^ ((OdUInt8)(m_nCRC & 0xFF)));
    m_nCRC = (OdUInt16)((m_nCRC >> 8) & 0xFF);
    m_nCRC = (OdUInt16)(m_nCRC ^ m_crcTable[nTemp & 0xFF]);
  }
  void crc8(OdUInt8 *p, OdUInt32 n)
  {
    while (n-- > 0) crc8(*(p++));
  }

  OdTvStreamWithCrc16(OdStreamBuf* pStreamBuf) : OdTvStreamWithCrc(pStreamBuf), m_nCRC((OdUInt16)0) { }
public:
  ODRX_DECLARE_MEMBERS(OdTvStreamWithCrc16);

  static inline OdStreamBufPtr create(OdStreamBuf* pStreamBuf)
  {
    return OdStreamBufPtr((OdStreamBuf*)new OdTvStreamWithCrc16(pStreamBuf), kOdRxObjAttach);
  }

  inline void initCRC(OdUInt16 val) { m_nCRC = val; }
  inline OdUInt16 getCRC() { return m_nCRC; }
  inline void checkCRC() { if (m_nCRC) throw OdError(eDwgCRCError); }

  OdUInt8 getByte();
  void getBytes(void* buffer, OdUInt32 nLen);
  void putByte(OdUInt8 val);
  void putBytes(const void* bytes, OdUInt32 len);
};

class OdTvMeasurementIo : public OdStaticRxObject<OdStreamBuf>
{
protected:
  OdUInt32 m_nStartPos;
  OdUInt32 m_nCurrPos;
  OdUInt32 m_nEndPos;
  void iterate(OdInt32 n)
  {
    m_nCurrPos += n;
    m_nEndPos = (m_nCurrPos > m_nEndPos ? m_nCurrPos : m_nEndPos);
  }
public:
  OdTvMeasurementIo(OdUInt32 nStartPos = 0)
  { init(nStartPos, nStartPos); }

  void init(OdUInt32 nStartPos, OdUInt32 nEndPos)
  {
    m_nStartPos = m_nCurrPos = nStartPos;
    m_nEndPos = nEndPos;
  }

  bool isEof();
  OdUInt64 length();
  OdUInt64 tell();

  OdUInt8 getByte();
  void getBytes(void* buffer, OdUInt32 nLen);
  void putByte(OdUInt8 val);
  void putBytes(const void* bytes, OdUInt32 len);

};

class DBIO_EXPORT OdTvDwgFileSectionsInfo
{
public:
  OdUInt32 m_HeaderAddr;
  OdUInt32 m_HeaderSize;
  OdUInt32 m_ClassesAddr;
  OdUInt32 m_ClassesSize;
  OdUInt32 m_HandlesAddr;
  OdUInt32 m_ObjectsStart;
  OdUInt32 m_HandlesSize;
  OdUInt32 m_ObjFreeSpaceAddr;
  OdUInt32 m_ObjFreeSpaceSize;
  OdUInt32 m_TemplateAddr;
  OdUInt32 m_TemplateSize;
  OdUInt32 m_AuxHeaderAddr;
  OdUInt32 m_AuxHeaderSize;

  OdUInt32 m_PreviewAddr;
  OdUInt32 m_SummaryInfoAddr;
  OdUInt32 m_VbaProjectAddr;
  OdUInt32 m_AppInfoAddr;

  inline OdTvDwgFileSectionsInfo() { ::memset(this, 0, sizeof(*this)); }
  inline OdUInt8 getSectionCount() const
  {
	  return OdUInt8((m_HeaderAddr ? 1 : 0) +
					  (m_ClassesSize ? 1 : 0) +
					  (m_AuxHeaderSize ? 1 : 0) +
					  (m_HandlesSize ? 1 : 0) +
					  (m_ObjFreeSpaceSize ? 1 : 0) +
					  (m_TemplateSize ? 1 : 0));
  }

  static const OdUInt8 m_ssHeader[16];
  static const OdUInt8 m_esHeader[16];
  static const OdUInt8 m_ssClasses[16];
  static const OdUInt8 m_esClasses[16];
  static const OdUInt8 m_ssPreviewImg[16];
  static const OdUInt8 m_esPreviewImg[16];
  static const OdUInt8 m_ssSecondFileHeader[16];
  static const OdUInt8 m_esSecondFileHeader[16];
};

class DBIO_EXPORT OdTvDwgFileController
  : public OdTvDbFilerController
  , public OdTvDwgFileSectionsInfo
{
  inline OdTvStreamWithCrc16* streamWithCrc()
  { return getStreamBuf()->isA() == OdTvStreamWithCrc16::desc() ? (OdTvStreamWithCrc16*)getStreamBuf() : 0; }
public:
  ODRX_DECLARE_MEMBERS(OdTvDwgFileController);
protected:
  OdTvDwgFileController();
  virtual ~OdTvDwgFileController();

public:
  void initCRC(OdUInt16 val)
  {
    OdTvStreamWithCrc16* pStream = streamWithCrc();
    if(pStream)
      pStream->initCRC(val);
  }
  OdUInt16 getCRC()
  {
    OdTvStreamWithCrc16* pStream = streamWithCrc();
    if(pStream)
      return pStream->getCRC();
    return 0;
  }
  void checkCRC()
  {
    OdTvStreamWithCrc16* pStream = streamWithCrc();
    if(pStream)
      pStream->checkCRC();
  }

  OdUInt64 length() { return getStreamBuf()->length(); }

  OdUInt64 seek(OdInt64 offset, OdDb::FilerSeekType whence)
  { return getStreamBuf()->seek(offset, whence); }

  OdUInt64 tell() { return getStreamBuf()->tell(); }
  bool isEof() { return getStreamBuf()->isEof(); }
  void rdBytes(void* buffer, OdUInt32 nLen) { getStreamBuf()->getBytes(buffer, nLen); }

  OdInt8      rdInt8() { return getStreamBuf()->getByte(); }
  OdUInt8     rdUInt8() { return getStreamBuf()->getByte(); }
  OdInt16     rdInt16() { return OdPlatformStreamer::rdInt16(*getStreamBuf()); }
  OdUInt16    rdUInt16() { return rdInt16(); }
  OdInt32     rdInt32() { return OdPlatformStreamer::rdInt32(*getStreamBuf()); }
  OdUInt32    rdUInt32() { return rdInt32(); }
  OdInt64     rdInt64() { return OdPlatformStreamer::rdInt64(*getStreamBuf()); }
  OdUInt64    rdUInt64() { return rdInt64(); }
  double      rdDouble() { return OdPlatformStreamer::rdDouble(*getStreamBuf()); }
  OdDbHandle  rdDbHandle() { return OdDbHandle(rdUInt64()); }
  virtual OdString rdString();
  virtual OdString rdString32();

  void wrBytes(const void* buffer, OdUInt32 nLen)
  { getStreamBuf()->putBytes(buffer, nLen); }

  void wrInt8(OdInt8 val) { getStreamBuf()->putByte(val); }
  void wrUInt8(OdUInt8 val) { getStreamBuf()->putByte(val); }
  void wrInt16(OdInt16 val) { OdPlatformStreamer::wrInt16(*getStreamBuf(), val); }
  void wrUInt16(OdInt16 val) { wrInt16(val); }
  void wrInt32(OdInt32 val) { OdPlatformStreamer::wrInt32(*getStreamBuf(), val); }
  void wrUInt32(OdInt32 val) { wrInt32(val); }
  void wrInt64(OdInt64 val) { OdPlatformStreamer::wrInt64(*getStreamBuf(), val); }
  void wrUInt64(OdUInt64 val) { wrInt64(val); }
  void wrDouble(double val) { OdPlatformStreamer::wrDouble(*getStreamBuf(), val); }
  void wrDbHandle(const OdDbHandle& val) { wrUInt64((OdUInt64)val); }
  virtual void wrString(const OdString& val);
  virtual void wrString32(const OdString& str);

  void readFile(OdStreamBuf* pFileBuff, bool bPartial, OdTvDbAuditInfo *pAuditInfo, const OdPassword& password, bool /*bAllowCPConversion*/ );
};

class DBIO_EXPORT OdTvDwgFileSecurity
{
public:
  OdTvDwgFileSecurity();
  void initSecurity();

  inline bool decryptData(OdBinaryData& data);
  inline bool encryptData(OdBinaryData& data);

  void wrSecurity(OdTvDwgFileController* pCtrl);
  void rdSecurity(OdTvDwgFileController* pCtrl);

  void setPassword(const OdPassword& password);
  bool checkPassword(const OdBinaryData& buffer);

  bool rdSignature(OdTvDwgFileController* pCtrl);

  bool digitalSignatureModeLaunched();
  void appendDataToProcessSignature(const OdBinaryData& dataBlock);

  bool signData();
  void wrSignature(OdTvDwgFileController* pCtrl);

  void verifySignature(OdCryptoServices::OdSignatureVerificationResult& verificationResult, 
    OdSignatureDescription& signatureDesc);

protected:
  OdTvDbCryptPtr        m_pCrypt;
  OdSecurityParams    m_securityParams;

  OdTvDwgDigitalSignaturePtr m_pSignature;
};

//----------------------------------------------------------
//
// Inline methods
//
//----------------------------------------------------------

inline
bool OdTvDwgFileSecurity::encryptData(OdBinaryData& buffer)
{
  if (m_pCrypt.isNull())
    return false;
  if (!m_pCrypt->encryptData(buffer.asArrayPtr(), buffer.size()))
    throw OdError(eDecryptionError);
  return true;
}

inline
bool OdTvDwgFileSecurity::decryptData(OdBinaryData& buffer)
{
  if (m_pCrypt.isNull())
    return false;
  if (!m_pCrypt->decryptData(buffer.asArrayPtr(), buffer.size()))
    throw OdError(eDecryptionError);
  return true;
}

#endif // !defined(_ODDWGFILECONTROLLER_H_INCLUDED_)
