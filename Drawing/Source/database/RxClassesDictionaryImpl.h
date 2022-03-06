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

#ifndef _RXCLASSESDICTIONARYIMPL_INC_
#define _RXCLASSESDICTIONARYIMPL_INC_

#include "../root/RxDictionaryImpl.h"


// ODA_MT_DBIO_BEGIN
//class OdRxClassesDictionaryImpl : public OdRxDictionaryImpl<>
class OdRxClassesDictionaryImpl : public OdRxDictionaryImpl<OdString::lessnocase, OdMutex>
// ODA_MT_DBIO_END
{
  OdRxClassesDictionaryImpl& operator = (const OdRxClassesDictionaryImpl&);
public:

  OdRxObjectPtr putAt(const OdString& key, OdRxObject* pObject, OdUInt32* pResId = NULL)
  {
// ODA_MT_DBIO_BEGIN
    //return OdRxDictionaryImpl<>::putAt(key, pObject, pResId);
    return OdRxDictionaryImpl<OdString::lessnocase, OdMutex>::putAt(key, pObject, pResId);
// ODA_MT_DBIO_END
  }

  OdRxObjectPtr putAt(OdUInt32 id, OdRxObject* pObject)
  {
// ODA_MT_DBIO_BEGIN
    //return OdRxDictionaryImpl<>::putAt(id, pObject);
    return OdRxDictionaryImpl<OdString::lessnocase, OdMutex>::putAt(id, pObject);
// ODA_MT_DBIO_END
  }

  OdRxObjectPtr remove(const OdString& key)
  {
    OdRxObjectPtr pRes;
    sorted_iterator iter;
    if(find(key, iter))
    {
      pRes = getAt(*iter);
      m_sortedItems.erase(iter);
      if(*iter+1 == m_items.size()) // last item
        m_items.resize(*iter);
      else
        m_items[*iter].setVal(OdRxObjectPtr());
    }
    return pRes;
  }

  OdRxObjectPtr remove(OdUInt32 id)
  {
    OdRxObjectPtr pRes;
    sorted_iterator iter;
    if(find(m_items[id].getKey(), iter))
    {
      pRes = getAt(id);
      m_sortedItems.erase(iter);
      if(id+1 == m_items.size()) // last item
        m_items.resize(id);
      else
        m_items[id].setVal(OdRxObjectPtr());
    }
    return pRes;
  }

// ODA_MT_DBIO_BEGIN
  //TD_USING(OdRxDictionaryImpl<>::remove);
// ODA_MT_DBIO_END
};

#endif // _RXCLASSESDICTIONARYIMPL_INC_

