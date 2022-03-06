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

#ifndef __ODA_DB_FILER_IMPL__
#define __ODA_DB_FILER_IMPL__

/////////////////////////////////////////////////////////////

// Common DXF filer functionality
class DBIO_EXPORT OdDbCommonDxfFilerImpl : public OdDbDxfFiler
{
protected:
  OdDbFilerController *m_pController;

  const OdDbObjectId& idLoaded(OdDxfCode::Type type, const OdDbObjectId& id);
public:
  ODRX_DECLARE_MEMBERS(OdDbCommonDxfFilerImpl);

  OdDbCommonDxfFilerImpl();
  OdDbFiler::FilerType filerType() const;
  virtual void setController(OdDbFilerController * pController);
  OdDbFilerController* controller() const;
  virtual OdUInt64 tell() const ODRX_OVERRIDE;
  virtual OdUInt64 currentLine() const{return 0;}
  virtual void setCurrentLine(OdUInt64){}
};

// ASCII DXF filer functionality
class DBIO_EXPORT OdDbAsciiDxfFilerImpl : public OdDbCommonDxfFilerImpl
{
  OdAnsiString  m_cache;
protected:
  int           m_state;
  OdInt64       m_nCurrentLine;
  virtual OdUInt64 currentLine() const
  {
    return m_nCurrentLine;
  }
  virtual void setCurrentLine(OdUInt64 l)
  {
    m_nCurrentLine = l;
  }
  enum {  // State values
    NotReady, Ready
  };
  short         m_groupCode;
  OdAnsiString m_value;
  char          m_DxfBuf[260];
  int           m_nPrecision;
  double        m_dEpsilon;
  const static double m_dEpsilonArray[];

  OdDbAsciiDxfFilerImpl();

  inline void wrDxfGroupCode(OdStreamBuf* pStream, int groupCode);
  inline void wrDxftime(OdStreamBuf* pStream, int groupCode, double val, int numchars);
  inline void wrDxfString(int groupCode, const char* pStr);
  inline void wrDxfString(int groupCode, const OdAnsiString &string);
  OdString convertFromDxf( const OdString& str );
  OdAnsiString convertFromDxfAnsi( const OdAnsiString& str );
  OdAnsiString convertToDxf(const OdString& str );
  OdAnsiString convertToDxfAnsi(const OdAnsiString& str);
  short currentGroupCode();
  void readNext();
public:
  ODRX_DECLARE_MEMBERS(OdDbAsciiDxfFilerImpl);

  bool atEOF();
  bool atEndOfObject();
  bool atExtendedData();
  bool atSubclassData(const OdString& subClassName);
  bool atEmbeddedObjectStart();
  void pushBackItem();
  int  nextItem();

  bool isZero(double d, int prec);
  inline bool isZero(double d)
  { return d < m_dEpsilon; }
  int  precision() const
  {
    return m_nPrecision;
  }
  void setPrecision(int prec);

  void seek(OdInt64 offset, OdDb::FilerSeekType whence);

  inline OdString rdString() { return OdDbCommonDxfFilerImpl::rdString(); }
  void        rdString(OdString &string);
  virtual void rdAnsiString(OdAnsiString &string);
  bool        rdBool();
  OdInt8      rdInt8();
  OdInt16     rdInt16();
  OdInt32     rdInt32();
  OdInt64     rdInt64();
  OdUInt8     rdUInt8();
  OdUInt16    rdUInt16();
  OdUInt32    rdUInt32();
  OdUInt64    rdUInt64();
  OdDbHandle  rdHandle();
  OdDbObjectId rdObjectId();
  double      rdAngle();
  double      rdDouble();
  void        rdPoint2d(OdGePoint2d& pt);
  void        rdPoint3d(OdGePoint3d& pt);
  void        rdVector2d(OdGeVector2d& pt);
  void        rdVector3d(OdGeVector3d& pt);
  void        rdScale3d(OdGeScale3d& pt);
  void        rdBinaryChunk(OdBinaryData&);

  virtual void wrAnsiString(int groupCode, const OdAnsiString& string);
  void        wrString(int groupCode, const OdString& string);
  void        wrName(int groupCode, const OdString& string);
  void        wrBool(int groupCode, bool val);
  void        wrInt8(int groupCode, OdInt8 val);
  void        wrUInt8(int groupCode, OdUInt8 val);
  void        wrInt16(int groupCode, OdInt16 val);
  void        wrUInt16(int groupCode, OdUInt16 val);
  void        wrInt32(int groupCode, OdInt32 val);
  void        wrUInt32(int groupCode, OdUInt32 val);
  void        wrInt64(int groupCode, OdInt64 val);
  void        wrUInt64(int groupCode, OdUInt64 val);
  void        wrHandle(int groupCode, OdDbHandle val);
  void        wrObjectId(int groupCode, OdDbObjectId val);
  void        wrAngle(int groupCode, double val, int precision = kDfltPrec);
  void        wrDouble(int groupCode, double val, int precision = kDfltPrec);
  void        wrPoint2d(int groupCode, const OdGePoint2d& pt, int precision = kDfltPrec);
  void        wrPoint3d(int groupCode, const OdGePoint3d& pt, int precision = kDfltPrec);
  void        wrVector2d(int groupCode, const OdGeVector2d& pt, int precision = kDfltPrec);
  void        wrVector3d(int groupCode, const OdGeVector3d& pt, int precision = kDfltPrec);
  void        wrScale3d(int groupCode, const OdGeScale3d& pt, int precision = kDfltPrec);
  void        wrBinaryChunk(int groupCode, const OdUInt8* pBuff, OdUInt32 nSize);
};

typedef OdSmartPtr<OdDbAsciiDxfFilerImpl> OdDbAsciiDxfFilerImplPtr;

// Binary DXF file functionality
class DBIO_EXPORT OdDbBinaryDxfFilerImpl : public OdDbCommonDxfFilerImpl
{
protected:  
  OdDbBinaryDxfFilerImpl();

  // short m_groupCode;
  OdUInt64 m_previousPosition; // for pushBackItem
  OdInt16  m_groupCode;

  // values(maybe should unioned?)
  /*OdString     m_strValue;
  bool         m_bValue;
  OdInt8       m_i8Value;
  OdInt16      m_i16Value;
  OdInt32      m_i32Value;
  double       m_dValue;
  OdGePoint3d  m_ptValue;
  OdBinaryData m_bdValue;
  OdDbHandle   m_hValue;*/
  OdResBufPtr  m_pRbValue;

  // Version-dependent
  void  wrGroupCode(int groupCode);
  short rdGroupCode();

public:
  ODRX_DECLARE_MEMBERS(OdDbBinaryDxfFilerImpl);

  int  m_nReadBytesPerGroupCode;

  void seek(OdInt64 offset, OdDb::FilerSeekType whence);

  int  precision() const;
  void setPrecision(int prec);

  bool atEOF();
  bool atEndOfObject();
  bool atExtendedData();
  bool atSubclassData(const OdString& subClassName);
  bool atEmbeddedObjectStart();

  int nextItem();
  void pushBackItem();

  inline OdString rdString() { return OdDbCommonDxfFilerImpl::rdString(); }
  void         rdString(OdString &string);
  bool         rdBool();
  OdInt8       rdInt8();
  OdInt16      rdInt16();
  OdInt32      rdInt32();
  OdInt64      rdInt64();
  OdUInt8      rdUInt8();
  OdUInt16     rdUInt16();
  OdUInt32     rdUInt32();
  OdUInt64     rdUInt64();
  OdDbHandle   rdHandle();
  OdDbObjectId rdObjectId();
  double       rdAngle();
  double       rdDouble();
  void         rdPoint2d(OdGePoint2d& pt);
  void         rdPoint3d(OdGePoint3d& pt);
  void         rdVector2d(OdGeVector2d& pt);
  void         rdVector3d(OdGeVector3d& pt);
  void         rdScale3d(OdGeScale3d& pt);
  void         rdBinaryChunk(OdBinaryData&);

  void wrString(int groupCode, const OdString& string);
  void wrName(int groupCode, const OdString& string);
  void wrBool(int groupCode, bool val);
  void wrInt8(int groupCode, OdInt8 val);
  void wrUInt8(int groupCode, OdUInt8 val);
  void wrInt16(int groupCode, OdInt16 val);
  void wrUInt16(int groupCode, OdUInt16 val);
  void wrInt32(int groupCode, OdInt32 val);
  void wrUInt32(int groupCode, OdUInt32 val);
  void wrInt64(int groupCode, OdInt64 val);
  void wrUInt64(int groupCode, OdUInt64 val);
  void wrHandle(int groupCode, OdDbHandle val);
  void wrObjectId(int groupCode, OdDbObjectId val);
  void wrAngle(int groupCode, double val, int precision = kDfltPrec);
  void wrDouble(int groupCode, double val, int precision = kDfltPrec);
  void wrPoint2d(int groupCode, const OdGePoint2d& pt, int precision = kDfltPrec);
  void wrPoint3d(int groupCode, const OdGePoint3d& pt, int precision = kDfltPrec);
  void wrVector2d(int groupCode, const OdGeVector2d& pt, int precision = kDfltPrec);
  void wrVector3d(int groupCode, const OdGeVector3d& pt, int precision = kDfltPrec);
  void wrScale3d(int groupCode, const OdGeScale3d& pt, int precision = kDfltPrec);
  void wrBinaryChunk(int groupCode, const OdBinaryData& bd);
  void wrBinaryChunk(int groupCode, const OdUInt8* pBuff, OdUInt32 nSize);
};

#endif
