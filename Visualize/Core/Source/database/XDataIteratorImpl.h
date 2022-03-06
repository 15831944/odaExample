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

#ifndef ODXDATAITERATORIMPL_INCLUDED
#define ODXDATAITERATORIMPL_INCLUDED

#include "OdPlatform.h"
#include "XDataIterator.h"
#include "DbFiler.h" // OdTvDxfCode class

class TOOLKIT_EXPORT OdTvXDataIteratorImpl
{
public:
  OdBinaryData*                         m_pBinData;
  OdUInt32                              m_nGcPos;
  OdUInt32                              m_nEndOfApp;
  mutable int                           m_nSize;
  mutable OdTvDxfCode::Type               m_Type;
  bool                                  m_bLayerNameAsHandle;

  OdTvXDataIteratorImpl() : 
    m_pBinData(NULL)
    , m_nGcPos(0)
    , m_nEndOfApp(0)
    , m_nSize(0)
    , m_Type(OdTvDxfCode::Unknown)
    , m_bLayerNameAsHandle(false)
  {
  }
  virtual ~OdTvXDataIteratorImpl(){}
  static OdTvXDataIteratorImpl* getImpl(OdTvXDataIterator* i){ return i->m_pImpl; }
  static const OdTvXDataIteratorImpl* getImpl(const OdTvXDataIterator* i){ return i->m_pImpl; }
  virtual int restypeSize() const { return 1; }

  void init(OdBinaryData* pBinData, OdUInt32 nGcPos = 0, OdUInt32 nAppEnd = 0)
  {
    m_pBinData = pBinData;
    m_nGcPos   = nGcPos;
    m_nEndOfApp= nAppEnd;
  }

  void start()
  {
    m_nGcPos = 0;
    m_nSize = 0;
    m_Type = OdTvDxfCode::Unknown;
  }

  void next()
  {
    m_nGcPos += dataSize();
    m_nGcPos += restypeSize();
    m_nSize = 0;
    m_Type=OdTvDxfCode::Unknown;
  }

  OdTvDxfCode::Type type() const
  {
    ODA_ASSERT(m_nGcPos<m_pBinData->size());
    if(m_Type==OdTvDxfCode::Unknown)
    {
      m_Type = OdTvDxfCode::_getType(curRestype());
    }
    return m_Type;
  }

  inline const OdUInt8* data() const
  {
    const OdBinaryData* pBinData = m_pBinData;
    return &pBinData->at(0) + m_nGcPos + restypeSize();
  }
  inline OdUInt8* data() { return &m_pBinData->at(0) + m_nGcPos + restypeSize(); }

  inline OdBinaryData::iterator iter_data() const { return m_pBinData->begin() + m_nGcPos + restypeSize(); }
  inline OdBinaryData::iterator iter_data() { return m_pBinData->begin() + m_nGcPos + restypeSize(); }

  virtual int dataSize() const
  {
    if(!m_nSize)
    {
      m_nSize = 0;
      switch(type())
      {
      case OdTvDxfCode::Unknown:
        ODA_FAIL_ONCE();
        throw OdError(eInvalidGroupCode);
      case OdTvDxfCode::Name:
      case OdTvDxfCode::String:
        {
          if(curRestype()!=1002)
          {
            const OdUInt8* pBuff = data();
            m_nSize = OD_INT16_FROM_BUFFPTR(pBuff) + 2 + 1;
          }
          else
          {
            m_nSize = 1;
          }
        }
        break;
      case OdTvDxfCode::Bool:
      case OdTvDxfCode::Integer8:
        m_nSize=1;
        break;
      case OdTvDxfCode::Integer16:
        m_nSize=2;
        break;
      case OdTvDxfCode::Integer32:
        m_nSize=4;
        break;
      case OdTvDxfCode::Integer64:
        // New in R24 (AC24 support)
        m_nSize=8;
        break;
      case OdTvDxfCode::Point:
        m_nSize=24;
        break;
      case OdTvDxfCode::BinaryChunk:
        m_nSize = (*data()) + 1;
        break;
      case OdTvDxfCode::Double:
      case OdTvDxfCode::Angle:
      case OdTvDxfCode::Handle:
      case OdTvDxfCode::LayerName:
      case OdTvDxfCode::ObjectId:
      case OdTvDxfCode::SoftPointerId:
      case OdTvDxfCode::HardPointerId:
      case OdTvDxfCode::SoftOwnershipId:
      case OdTvDxfCode::HardOwnershipId:
        m_nSize=8;
        break;
      }
    }
    ODA_ASSERT(m_nSize);
    return m_nSize;
  }

  virtual int curRestype() const
  {
    const OdBinaryData* pBinData = m_pBinData;
    return pBinData->at(m_nGcPos) + 1000;
  }

  virtual void setRestype(int gCode)
  {
    ODA_ASSERT(m_nGcPos<m_pBinData->size());
    ODA_ASSERT(gCode >= 1000);
    m_pBinData->at(m_nGcPos) = OdUInt8(gCode - 1000);
  }

  virtual OdUInt8* beforeWriteItem(int nNewItemDataSize);

  virtual OdString getString() const;
  virtual void setString(int gCode, const OdString& val);
  virtual OdDbHandle getHandle() const;
  virtual void setHandle(int gCode, const OdDbHandle& val);

  void setTreatLayerNameAsHandle(bool val) { m_bLayerNameAsHandle = val; }
  bool isTreatLayerNameAsHandle() { return m_bLayerNameAsHandle; }
};

class TOOLKIT_EXPORT OdTvXDataR21IteratorImpl : public OdTvXDataIteratorImpl
{
public:
  virtual int dataSize() const;
  virtual OdString getString() const;
  virtual void setString(int gCode, const OdString& str);
};

#endif  // ODXDATAITERATORIMPL_INCLUDED
