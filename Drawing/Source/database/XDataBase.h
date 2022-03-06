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

#ifndef _XDATA_INCLUDED_
#define _XDATA_INCLUDED_

#include "OdBinaryData.h"
#include "XDataIterator.h"
#include "XDataIteratorImpl.h"
#include "OdDbStub.h"
#include "StaticRxObject.h"
#include "RxObjectImpl.h"
#include "DbSymUtl.h"

#include "TD_PackPush.h"

#define StaticXDataR15Iterator OdStaticRxObject<OdObjectWithImpl<OdXDataIterator, OdXDataIteratorImpl> >
#define StaticXDataR21Iterator OdStaticRxObject<OdObjectWithImpl<OdXDataIterator, OdXDataR21IteratorImpl> >

template< class TRegApp >
class TOOLKIT_EXPORT OdXDataBase : public OdBinaryData
{
public:
  using OdBinaryData::size;
  using OdBinaryData::begin;
  typedef size_type Position;
  class Item
  {
  public:
    mutable OdDbStub* m_appId;
    mutable OdString  m_appName;
    OdXDataBase<TRegApp>* m_pXData;

    OdUInt16      m_nDataSize;
    OdUInt8*      m_pData;
    Item()
      : m_pXData(0)
      , m_pData(0)
      , m_nDataSize(0)
      , m_appId(0)
    {}

    void initReadIterator(OdXDataIteratorImpl& i, bool treatLayerNameAsHandle = false) const
    {
      i.init(m_pXData, (OdUInt32)(m_pData - m_pXData->begin()), (OdUInt32)(m_pData - m_pXData->begin() + m_nDataSize));
      i.setTreatLayerNameAsHandle(treatLayerNameAsHandle);
    }
    OdXDataIteratorPtr getReadIterator(bool treatLayerNameAsHandle = false) const
    {
      OdXDataIteratorPtr p;
      if (m_pXData->isInR15Format())
        p = OdRxObjectImpl<OdObjectWithImpl<OdXDataIterator, OdXDataIteratorImpl> >::createObject();
      else
        p = OdRxObjectImpl<OdObjectWithImpl<OdXDataIterator, OdXDataR21IteratorImpl> >::createObject();
      initReadIterator(*OdXDataIteratorImpl::getImpl(p), treatLayerNameAsHandle);
      return p;
    }
    OdXDataIteratorPtr getWriteIterator(OdBinaryData* bin, bool bXDataIsInR15Format, bool treatLayerNameAsHandle) const
    {
      OdXDataIteratorPtr p;
      if (bXDataIsInR15Format)
        p = OdRxObjectImpl<OdObjectWithImpl<OdXDataIterator, OdXDataIteratorImpl> >::createObject();
      else
        p = OdRxObjectImpl<OdObjectWithImpl<OdXDataIterator, OdXDataR21IteratorImpl> >::createObject();
      OdXDataIteratorImpl::getImpl(p)->init(bin);
      OdXDataIteratorImpl::getImpl(p)->setTreatLayerNameAsHandle(treatLayerNameAsHandle);
      return p;
    }

    OdDbStub* getAppId(OdDbBaseDatabase* pDatabase) const
    {
      if(!m_appId)
      {
        if (pDatabase)  // Null for non-DBR
          m_appId = TRegApp::getRegAppId(m_appName, pDatabase);
      }
      return m_appId;
    }
    const OdString& getAppName() const
    {
      if(m_appName.isEmpty())
      {
        m_appName = TRegApp::getRegAppName(m_appId);
      }
      return m_appName;
    }
    void setAppId(OdDbStub* appId)
    {
      m_appName.empty();
      m_appId = appId;
    }
    void setAppName(const OdString& appName)
    {
      m_appId = 0;
      m_appName = appName;
    }
  };

  inline OdXDataBase()
    : m_bAppAsId(false)
    , m_bXDataIsInR15Format(false)
  {}

  inline Position firstItemPos() const { return 0; }

  bool isInR15Format()const {return m_bXDataIsInR15Format;}
  void setXDataFormatIsR15(bool bXDataIsInR15Format){ m_bXDataIsInR15Format = bXDataIsInR15Format; }
  void convertToFormat(bool bToR15Format, OdDbBaseDatabase* pDb)
  {
    if (bToR15Format == m_bXDataIsInR15Format)
      return;
    StaticXDataR15Iterator r15Iter;
    StaticXDataR21Iterator r21Iter;
    OdXDataIterator* pSrc, *pDst;
    if (bToR15Format)
    {
      pSrc = &r21Iter;
      pDst = &r15Iter;
    }
    else
    {
      pSrc = &r15Iter;
      pDst = &r21Iter;
    }
    OdBinaryData bin;
    OdXDataIteratorImpl::getImpl(pDst)->init(&bin);
    Position posSrc = firstItemPos();
    Position posDst = 0;
    OD_TYPENAME OdXDataBase<TRegApp>::Item itemSrc;
    OD_TYPENAME OdXDataBase<TRegApp>::Item itemDst;
    OdXDataBase<TRegApp> pXData;
    pXData.setXDataFormatIsR15(!m_bXDataIsInR15Format);
    while (nextItem(posSrc, itemSrc))
    {
      itemSrc.initReadIterator(*OdXDataIteratorImpl::getImpl(pSrc));
      pDst->start();
      bin.clear();
      itemDst.setAppId(itemSrc.getAppId(pDb));
      while (!pSrc->atEndOfApp())
      {
        OdResBufPtr pNext = pSrc->readItem(pDb);
        if (OdDxfCode::_getType(pNext->restype()) == OdDxfCode::Unknown)
          break;
        pDst->writeItem(pNext, pDb);
      }
      itemDst.m_nDataSize = (OdUInt16)bin.size();
      itemDst.m_pData = bin.asArrayPtr();
      pXData.setNextItem(posDst, itemDst, pDb);
    }
    *this = pXData;
  }

  bool nextItem(Position& pos, Item& item) const
  {
    OdUInt16 len;
    if(this == NULL || pos >= size())
        return false;
    
    const OdUInt8* pStart = &at(pos);
    const OdUInt8* pBuff = pStart;
    if(m_bAppAsId)
    {
        OdDbObjectId id;
        memcpy(&id, pBuff, sizeof(OdDbObjectId));
        ODA_ASSERT(!id.isNull());
        item.setAppId(id);
        pBuff += sizeof(OdDbObjectId);
    }
    else
    {
        len = (OdUInt16)OD_INT16_FROM_BUFFPTR(pBuff);
        item.setAppName(OdString((const char*)pBuff, len));
        pBuff += len;
    }
    len = (OdUInt16)OD_INT16_FROM_BUFFPTR(pBuff);
    item.m_nDataSize = len;
    item.m_pData = (OdUInt8*)pBuff;
    item.m_pXData = const_cast<OdXDataBase<TRegApp>*>(this);
    pos += Position(pBuff - pStart);
    pos += item.m_nDataSize;
    return true;
  }

  void setNextItem(Position& pos, Item& item, OdDbBaseDatabase* pDb)
  {
    if(size()==0) // FirstItem
    {
      m_bAppAsId = (pDb!=NULL);
    }
    if (item.m_nDataSize > 0)
    {
      unsigned nItemSize = 0;
      OdUInt8* pBuff = 0;
      if(m_bAppAsId)
      {
        nItemSize = sizeof(OdDbObjectId) + item.m_nDataSize + sizeof(OdUInt16);
        pBuff = itemResize(pos, nItemSize);
        OdDbObjectId id = item.getAppId(pDb);
        if (id.isNull())
        {
          throw OdError(eRegappIdNotFound);
        }
        //nItemSize = sizeof(OdDbObjectId) + item.m_nDataSize + sizeof(OdUInt16);
        //pBuff = itemResize(pos, nItemSize);
        memcpy(pBuff, &id, sizeof(OdDbObjectId));
        pBuff += sizeof(OdDbObjectId);
      }
      else
      {
        int nLen = item.getAppName().getLengthA();
        nItemSize = nLen + sizeof(OdUInt16) + item.m_nDataSize + sizeof(OdUInt16);
        pBuff = itemResize(pos, nItemSize);
        if (nLen == 0)
        {
          throw OdError(eRegappIdNotFound);
        }
        //nItemSize = nLen + sizeof(OdUInt16) + item.m_nDataSize + sizeof(OdUInt16);
        //pBuff = itemResize(pos, nItemSize);
        OD_INT16_TO_BUFFPTR(pBuff, nLen);
        memcpy(pBuff, (const char*)item.getAppName(), nLen);
        pBuff += nLen;
      }
      ODA_ASSERT(nItemSize == itemSize(item));
      pos += nItemSize;
      OD_INT16_TO_BUFFPTR(pBuff, item.m_nDataSize);
      if(item.m_pData)
      {
        memcpy(pBuff, item.m_pData, item.m_nDataSize);
      }
      else
      {
        item.m_pData = pBuff;
      }
    }
    else
    {
      itemResize(pos, 0);
    }
  }

  Position find(const OdChar* appName) const
  {
    Position cur = firstItemPos();
    Position pos = cur;
    Item item;
    while(nextItem(cur, item))
    {
      if(item.getAppName().iCompare(appName) == 0)
        return pos;
      pos = cur;
    }
    return pos;
  }

  bool find(const OdChar* appName, Item& item) const
  {
    Position pos = firstItemPos();
    while(nextItem(pos, item))
    {
      if(item.getAppName().iCompare(appName) == 0)
        return true;
    }
    return false;
  }

  bool find(const OdDbObjectId &appId, Item& item, OdDbDatabase* pDb) const
  {
    if (m_bAppAsId)
    {
      Position pos = firstItemPos();
      while(nextItem(pos, item))
      {
        if(item.getAppId(pDb)==appId)
          return true;
      }
    }
    else
    {
      return find(OdDbSymUtil::getSymbolName(appId), item);
    }
    return false;
  }

  OdUInt16 itemSize(const Item& item) const
  {
    int res;
    if(m_bAppAsId)
    {
      res = sizeof(OdDbObjectId);
    }
    else
    {
      ODA_ASSERT(!item.getAppName().isEmpty());
      res = OdUInt16(item.getAppName().getLengthA() + sizeof(OdUInt16));
    }
    res += (item.m_nDataSize + sizeof(OdUInt16));
    ODA_ASSERT(res==OdUInt16(res));
    return OdUInt16(res);
  }

  OdUInt16 itemSize(Position pos) const
  {
    Item item;
    if(nextItem(pos, item))
    {
      return itemSize(item);
    }
    return 0;
  }

  OdUInt8* itemResize(Position pos, OdUInt16 nNewSize)
  {
    const Position temp = pos;  // Borland 5.6 modifies the parameter to itemSize() below!
    int nDiff = itemSize(temp) - nNewSize;
    if(nDiff > 0)
    {
      erase(begin()+pos, begin()+pos+nDiff);
    }
    else if(nDiff < 0)
    {
      insert(begin() + pos, -nDiff, 0xCD);
    }
    if(pos < size())
      return asArrayPtr() + pos;
    return NULL;
  }

  bool getAppAsIdFlag()
  {
    return m_bAppAsId;
  }
private:
  bool m_bAppAsId;
  bool m_bXDataIsInR15Format;
};


#include "TD_PackPop.h"

#endif //_XDATA_INCLUDED_
