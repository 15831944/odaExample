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

// DwgFileController.h: interface for the OdDwgFileController class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ODDWGFILECONTROLLER_H_INCLUDED_)
#define _ODDWGFILECONTROLLER_H_INCLUDED_


#include "../DbFilerController.h"
#include "StaticRxObject.h"
#include "OdPlatformStreamer.h"

#include "../OdDwgDigitalSignature.h"

class OdStreamWithCrc : public OdRxObjectImpl<OdStreamBuf>
{
protected:
  OdStreamBufPtr m_pUnderlyingIo;
  OdStreamWithCrc(OdStreamBuf* pStreamBuf) : m_pUnderlyingIo(pStreamBuf) {}
  OdStreamWithCrc() {}
public:
  ODRX_DECLARE_MEMBERS(OdStreamWithCrc);

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

class OdStreamWithCrc16 : public OdStreamWithCrc
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

  OdStreamWithCrc16(OdStreamBuf* pStreamBuf) : OdStreamWithCrc(pStreamBuf), m_nCRC((OdUInt16)0) { }
public:
  ODRX_DECLARE_MEMBERS(OdStreamWithCrc16);

  static inline OdStreamBufPtr create(OdStreamBuf* pStreamBuf)
  {
    return OdStreamBufPtr((OdStreamBuf*)new OdStreamWithCrc16(pStreamBuf), kOdRxObjAttach);
  }

  inline void initCRC(OdUInt16 val) { m_nCRC = val; }
  inline OdUInt16 getCRC() { return m_nCRC; }
  inline void checkCRC() { if (m_nCRC) throw OdError(eDwgCRCError); }

  OdUInt8 getByte();
  void getBytes(void* buffer, OdUInt32 nLen);
  void putByte(OdUInt8 val);
  void putBytes(const void* bytes, OdUInt32 len);
};

class OdMeasurementIo : public OdStaticRxObject<OdStreamBuf>
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
  OdMeasurementIo(OdUInt32 nStartPos = 0)
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

class DBIO_EXPORT OdDwgFileSectionsInfo
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

  inline OdDwgFileSectionsInfo() { ::memset(this, 0, sizeof(*this)); }
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

class DBIO_EXPORT OdDwgFileController
  : public OdDbFilerController
  , public OdDwgFileSectionsInfo
{
  inline OdStreamWithCrc16* streamWithCrc()
  { return getStreamBuf()->isA() == OdStreamWithCrc16::desc() ? (OdStreamWithCrc16*)getStreamBuf() : 0; }
public:
  ODRX_DECLARE_MEMBERS(OdDwgFileController);
protected:
  OdDwgFileController();
  virtual ~OdDwgFileController();

public:
  void initCRC(OdUInt16 val)
  {
    OdStreamWithCrc16* pStream = streamWithCrc();
    if(pStream)
      pStream->initCRC(val);
  }
  OdUInt16 getCRC()
  {
    OdStreamWithCrc16* pStream = streamWithCrc();
    if(pStream)
      return pStream->getCRC();
    return 0;
  }
  void checkCRC()
  {
    OdStreamWithCrc16* pStream = streamWithCrc();
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

  void readFile(OdStreamBuf* pFileBuff, bool bPartial, OdDbAuditInfo *pAuditInfo, const OdPassword& password, bool /*bAllowCPConversion*/ );
};

class DBIO_EXPORT OdDwgFileSecurity
{
public:
  OdDwgFileSecurity();
  void initSecurity();

  inline bool decryptData(OdBinaryData& data);
  inline bool encryptData(OdBinaryData& data);

  void wrSecurity(OdDwgFileController* pCtrl);
  void rdSecurity(OdDwgFileController* pCtrl);

  void setPassword(const OdPassword& password);
  bool checkPassword(const OdBinaryData& buffer);

  bool rdSignature(OdDwgFileController* pCtrl);

  bool digitalSignatureModeLaunched();
  void appendDataToProcessSignature(const OdBinaryData& dataBlock);

  bool signData();
  void wrSignature(OdDwgFileController* pCtrl);

  void verifySignature(OdCryptoServices::OdSignatureVerificationResult& verificationResult, 
    OdSignatureDescription& signatureDesc);

protected:
  OdDbCryptPtr        m_pCrypt;
  OdSecurityParams    m_securityParams;

  OdDwgDigitalSignaturePtr m_pSignature;
};

//----------------------------------------------------------
//
// Inline methods
//
//----------------------------------------------------------

inline
bool OdDwgFileSecurity::encryptData(OdBinaryData& buffer)
{
  if (m_pCrypt.isNull())
    return false;
  if (!m_pCrypt->encryptData(buffer.asArrayPtr(), buffer.size()))
    throw OdError(eDecryptionError);
  return true;
}

inline
bool OdDwgFileSecurity::decryptData(OdBinaryData& buffer)
{
  if (m_pCrypt.isNull())
    return false;
  if (!m_pCrypt->decryptData(buffer.asArrayPtr(), buffer.size()))
    throw OdError(eDecryptionError);
  return true;
}

#endif // !defined(_ODDWGFILECONTROLLER_H_INCLUDED_)
