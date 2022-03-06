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

// DbUndoFiler.h: interface for the OdTvDbUndoFiler class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _ODDBUNDOOBJFILER_H_
#define _ODDBUNDOOBJFILER_H_

#include "TD_PackPush.h"

#include "DbFiler.h"
#include "DoubleArray.h"
#include "StringArray.h"
#include "Int8Array.h"
#include "Ge/GePoint2dArray.h"

// IS_DIFF_UNDO_ENABLED() support

enum EDiffUndoType
{
  eDiffUndoNo,
  eDiffUndoBegin,
  eDiffUndoEnd
};

enum EDiffType
{
  eAddOne,
  eAddN,
  eDeleteOne,
  eDeleteN,
  eEnd
};

class OdTvDbUndoObjFiler: public OdTvDbDwgFiler
{
public:
  enum EDataType
  {
    eNone,
    eBool,
    eInt8,
    eUInt8,
    eInt16,
    eInt32,
    eLastSimple = eInt32,
    eInt64,
    eSoftOwnershipId,
    eHardOwnershipId,
    eSoftPointerId,
    eHardPointerId,
    eString,
    eBytes,
    eDouble,
    eDbHandle,
    ePoint2d,
    ePoint3d,
    eVector2d,
    eVector3d,
    eScale3d
  };

public:
  OdTvDbUndoObjFiler(): m_db(NULL), m_iPos(0), m_size(0), m_aRef(100, -100)
  {
    m_aRef.resize(m_aRef.physicalLength());
  }
  ~OdTvDbUndoObjFiler()
  {
    DataRef *pArray = m_aRef.asArrayPtr();
    for(unsigned i = 0, k = size(); i < k; ++i)
    {
      if(pArray[i].type() == eString)
        pArray[i].setType(eNone);
    }
  }
  OdTvDbFiler::FilerType filerType() const { return OdTvDbFiler::kUndoFiler; }
  static OdSmartPtr<OdTvDbUndoObjFiler> createObject(OdTvDbDatabase* pDb);
#ifdef _DEBUG
  unsigned getSizeInStream() const
  {
    unsigned val = 0;
    for(unsigned i = 0; i < size(); ++i)
      val += m_aRef[i].getSizeInStream();
    return val;
  }
#endif

  OdTvDbDatabase* database() const { return m_db; }

  // Data output functions
  virtual void seek(OdInt64 /*offset*/, OdDb::FilerSeekType /*whence*/) {}
  virtual OdUInt64 tell() const { return 0; }

  //////////////////////////////////////////////
  // reading
  virtual bool         rdBool();
  virtual OdString     rdString();
  virtual void         rdBytes(void* buffer, OdUInt32 nLen);

  virtual OdInt8       rdInt8();
  virtual OdUInt8      rdUInt8();

  virtual OdInt16      rdInt16();
  virtual OdInt32      rdInt32();
  virtual OdInt64      rdInt64();
  virtual double       rdDouble();
  virtual OdDbHandle   rdDbHandle();

  virtual OdTvDbObjectId rdSoftOwnershipId();
  virtual OdTvDbObjectId rdHardOwnershipId();
  virtual OdTvDbObjectId rdHardPointerId();
  virtual OdTvDbObjectId rdSoftPointerId();

  virtual OdGePoint2d rdPoint2d();
  virtual OdGePoint3d rdPoint3d();
  virtual OdGeVector3d rdVector3d();
  virtual OdGeVector2d rdVector2d();
  virtual OdGeScale3d rdScale3d();

  //////////////////////////////////////////////
  // writing
  virtual void wrBool(bool);
  virtual void wrString(const OdString &string);
  virtual void wrBytes(const void* buffer, OdUInt32 nLen);

  virtual void wrInt8(OdInt8 val);
  virtual void wrUInt8(OdUInt8 val);

  virtual void wrInt16(OdInt16 val);
  virtual void wrInt32(OdInt32 val);
  virtual void wrInt64(OdInt64 val);
  virtual void wrDouble(double val);
  virtual void wrDbHandle(const OdDbHandle& val);

  virtual void wrSoftOwnershipId(const OdTvDbObjectId& id);
  virtual void wrHardOwnershipId(const OdTvDbObjectId& id);
  virtual void wrSoftPointerId(const OdTvDbObjectId& id);
  virtual void wrHardPointerId(const OdTvDbObjectId& id);

  virtual void wrPoint2d(const OdGePoint2d& pt);
  virtual void wrPoint3d(const OdGePoint3d& pt);
  virtual void wrVector2d(const OdGeVector2d& vec);
  virtual void wrVector3d(const OdGeVector3d& vec);
  virtual void wrScale3d(const OdGeScale3d& point);

  void rewind() { m_iPos = 0; }
  void seekEnd() { m_iPos = m_size; }
  void reset()
  {
    for(int i = 0; i < (int)size(); ++i)
    {
      if(m_aRef[i].type() == eString)
        m_aRef[i].setType(eNone);
    }
    m_iPos = 0;
    m_size = 0;
    if(m_aPt2d.size())
      m_aPt2d.resize(0);
    if(m_aPt3d.size())
      m_aPt3d.resize(0);
    if(m_aBytes.size())
      m_aBytes.resize(0);
  }
  unsigned size() const { return m_size; }
  void wrItem(int iItem, OdTvDbDwgFiler* pFiler) const;
  void rdItem(int iItem, OdTvDbDwgFiler* pFiler);
  void deleteItemsAt(int iPos, int nItems);
  bool isItemEqual(int iItem, const OdTvDbUndoObjFiler& otherData, int iItemOtherData) const;
  bool isItemEqual(int iItem, const OdString& value) const
  {
    ODA_ASSERT(iItem >= 0 && iItem < (int)size());
    return (m_aRef[iItem].type() == eString) && (m_aRef[iItem].getString() == value);
  }
  bool isItemEqual(int iItem, EDataType eType, const OdTvDbObjectId& id) const
  {
    ODA_ASSERT(iItem >= 0 && iItem < (int)size());
    return (m_aRef[iItem].type() == eType) && (m_aRef[iItem].getAddress() == (const OdDbStub*)id);
  }
  bool isItemEqual(int iItem, OdInt32 value) const
  {
    ODA_ASSERT(iItem >= 0 && iItem < (int)size());
    return (m_aRef[iItem].type() == eInt32) && (m_aRef[iItem].getInt32() == value);
  }
  bool isItemEqual(int iItem, OdInt64 value) const
  {
    ODA_ASSERT(iItem >= 0 && iItem < (int)size());
    return (m_aRef[iItem].type() == eInt64) && ((OdInt64)m_aRef[iItem].getInt64() == value);
  }
  bool isItemEqual(int iItem, bool value) const
  {
    ODA_ASSERT(iItem >= 0 && iItem < (int)size());
    return (m_aRef[iItem].type() == eBool) && (m_aRef[iItem].getInt32() == (int)value);
  }
  bool isItemEqual(int iItem, OdInt8 value) const
  {
    ODA_ASSERT(iItem >= 0 && iItem < (int)size());
    return (m_aRef[iItem].type() == eInt8) && (m_aRef[iItem].getInt32() == (int)value);
  }
  bool isItemEqual(int iItem, OdUInt8 value) const
  {
    ODA_ASSERT(iItem >= 0 && iItem < (int)size());
    return (m_aRef[iItem].type() == eUInt8) && (m_aRef[iItem].getInt32() == (int)value);
  }
  bool isItemEqual(int iItem, OdInt16 value) const
  {
    ODA_ASSERT(iItem >= 0 && iItem < (int)size());
    return (m_aRef[iItem].type() == eInt16) && (m_aRef[iItem].getInt32() == (int)value);
  }
  bool isItemEqual(int iItem, double value) const
  {
    ODA_ASSERT(iItem >= 0 && iItem < (int)size());
    return (m_aRef[iItem].type() == eDouble) && (m_aRef[iItem].getDouble() == value);
  }
  bool isItemEqual(int iItem, const OdDbHandle& value) const
  {
    ODA_ASSERT(iItem >= 0 && iItem < (int)size());
    return (m_aRef[iItem].type() == eDbHandle) && (m_aRef[iItem].getInt64() == value);
  }
  bool isItemEqual(int iItem, const OdGePoint2d& value) const
  {
    ODA_ASSERT(iItem >= 0 && iItem < (int)size());
    return (m_aRef[iItem].type() == ePoint2d) && (m_aPt2d[m_aRef[iItem].getInt32()] == value);
  }
  bool isItemEqual(int iItem, const OdGePoint3d& value) const
  {
    ODA_ASSERT(iItem >= 0 && iItem < (int)size());
    return (m_aRef[iItem].type() == ePoint3d) && (m_aPt3d[m_aRef[iItem].getInt32()] == value);
  }
  bool isItemEqual(int iItem, const OdGeVector2d& value) const
  {
    ODA_ASSERT(iItem >= 0 && iItem < (int)size());
    return (m_aRef[iItem].type() == eVector2d) && (m_aPt2d[m_aRef[iItem].getInt32()] == (const OdGePoint2d&)value);
  }
  bool isItemEqual(int iItem, const OdGeVector3d& value) const
  {
    ODA_ASSERT(iItem >= 0 && iItem < (int)size());
    return (m_aRef[iItem].type() == eVector3d) && (m_aPt3d[m_aRef[iItem].getInt32()] == (const OdGePoint3d&)value);
  }
  bool isItemEqual(int iItem, const OdGeScale3d& value) const
  {
    ODA_ASSERT(iItem >= 0 && iItem < (int)size());
    return (m_aRef[iItem].type() == eScale3d) && (m_aPt3d[m_aRef[iItem].getInt32()] == (const OdGePoint3d&)value);
  }

  void copyItems(const OdTvDbUndoObjFiler& otherData, int iItemOtherData, int nItems);

protected:
  union Data
  {
    OdInt32 Int32;
    double  Double;
    OdUInt8 Bytes[sizeof(OdInt64)];
    OdUInt64 Int64;//handle as well
    OdInt32 BinData[2]; //len, index
    const void* Address;
  };

  class DataRef
  {
  public:
    DataRef(): m_eType(eNone){}
    DataRef(EDataType eType): m_eType(eNone)
    {
      if(eType == eString)
        constructString();
      m_eType = eType;
    }
    ~DataRef(){ if(type() == eString) destroyString(); }
    EDataType type() const { return m_eType; }
    DataRef(const DataRef& c): m_eType(eNone)
    {
      setType(c.type());
      if(c.type() == eString)
        setString(c.getString());
      else
      {
        ODA_ASSERT(sizeof(m_data) == sizeof(m_data.Int64));
        m_data.Int64 = c.m_data.Int64;
      }
    }
    void init()
    {
      m_eType = eNone;
    }
    const OdString& getString() const
    {
      ODA_ASSERT(type() == eString);
      return *((OdString*)m_data.Bytes);
    }
    void setString(const OdString& s)
    {
      ODA_ASSERT(type() == eString);
      *((OdString*)m_data.Bytes) = s;
    }
    OdInt32 getInt32() const
    {
      ODA_ASSERT(type() >= eBool && type() <= eLastSimple ||
        type() >= ePoint2d && type() <= eScale3d);
      return m_data.Int32;
    }
    void setInt32(OdInt32 value)
    {
      ODA_ASSERT(type() >= eBool && type() <= eLastSimple ||
        type() >= ePoint2d && type() <= eScale3d);
      m_data.Int32 = value;
    }
    OdUInt64 getInt64() const
    {
      ODA_ASSERT(type() == eDbHandle || type() == eInt64);
      return m_data.Int64;
    }
    void setInt64(OdUInt64 value)
    {
      ODA_ASSERT(type() == eDbHandle || type() == eInt64);
      m_data.Int64 = value;
    }
    double getDouble() const
    {
      ODA_ASSERT(type() == eDouble);
      return m_data.Double;
    }
    void setDouble(double value)
    {
      ODA_ASSERT(type() == eDouble);
      m_data.Double = value;
    }
    OdInt32 getBinDataLen() const
    {
      ODA_ASSERT(type() == eBytes);
      return m_data.BinData[0];
    }
    OdInt32 getBinDataIdx() const
    {
      ODA_ASSERT(type() == eBytes);
      return m_data.BinData[1];
    }
    void setBinData(OdInt32 len, OdInt32 idx)
    {
      ODA_ASSERT(type() == eBytes);
      m_data.BinData[0] = len;
      m_data.BinData[1] = idx;
    }
    const void* getAddress() const
    {
      ODA_ASSERT(type() >= eSoftOwnershipId && type() <= eHardPointerId);
      return m_data.Address;
    }
    void setAddress(const void* value)
    {
      ODA_ASSERT(type() >= eSoftOwnershipId && type() <= eHardPointerId);
      m_data.Address = value;
    }

    DataRef& setType(EDataType eType)
    {
      if(eType == type())
        return *this;
      if(type() == eString)
        destroyString();
      else if(eType == eString)
        constructString();
      m_eType = eType;
      return *this;
    }
#ifdef _DEBUG
    unsigned getSizeInStream() const
    {
      unsigned val = 0;
      switch(type())
      {
      case eBool: case eInt8: case eUInt8:
        val += sizeof(OdInt8);
        break;
      case eInt16:
        val += sizeof(OdInt16);
        break;
      case eInt64: case eDbHandle:
        val += sizeof(OdInt64);
        break;
      case eInt32: case eSoftOwnershipId: case eHardOwnershipId:
      case eSoftPointerId: case eHardPointerId: 
        val += sizeof(OdUInt32);
        break;
      case eString:
        val += sizeof(OdUInt16) + getString().getLengthA() + 1;
        break;
      case eBytes:
        val += sizeof(OdUInt32) + getBinDataLen();
        break;
      case eDouble:
        val += sizeof(double);
        break;
      case ePoint2d: case eVector2d:
        val += sizeof(OdGePoint2d);
        break;
      case ePoint3d: case eVector3d: case eScale3d:
        val += sizeof(OdGePoint3d);
        break;
      default:
        ODA_ASSERT(false);
      }
      return val;
    }
#endif
  protected:
    void constructString()
    {
      new (reinterpret_cast<void*>(m_data.Bytes)) OdString;
    }
    void destroyString()
    {
      reinterpret_cast<OdString*>(m_data.Bytes)->~OdString();
    }

  protected:
    EDataType m_eType;
    Data m_data;
  };

protected:
  EDataType getType() const { return m_aRef[m_iPos].type(); }
  DataRef& appendRef(EDataType eType)
  {
    if(m_iPos == (int)m_aRef.size())
    {
      m_aRef.resize(m_aRef.size() + 1);
      m_aRef.resize(m_aRef.physicalLength());
    }
    DataRef &pRef = ((DataRef*)m_aRef.getPtr())[m_iPos];
    pRef.init();
    ++m_size;
    ++m_iPos;
    return pRef.setType(eType);
  }
  DataRef& insertRef(OdInt32 iPos, EDataType eType)
  {
    m_aRef.insertAt(iPos, DataRef(eNone));
    ++m_size;
    if(m_iPos >= iPos)
      ++m_iPos;
    return m_aRef[iPos].setType(eType);
  }

protected:
  OdTvDbDatabase* m_db;
  OdArray<DataRef, OdMemoryAllocator<DataRef> > m_aRef;
  OdGePoint2dArray m_aPt2d;
  OdGePoint3dArray m_aPt3d;
  OdInt8Array m_aBytes;
  OdInt32 m_iPos;
  unsigned m_size;
};

typedef OdSmartPtr<OdTvDbUndoObjFiler> OdTvDbUndoObjFilerPtr;

#include "TD_PackPop.h"

#endif // _ODDBUNDOOBJFILER_H_
