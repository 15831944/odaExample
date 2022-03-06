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

#ifndef _ODRXMEMBERIMPL_INCLUDED_
#define _ODRXMEMBERIMPL_INCLUDED_

#include "RxMember.h"
#include "RxAttribute.h"

class OdRxMemberImpl
{
public:
  OdString m_name;
  OdRxAttributeCollection m_attributes;
  OdRxValueTypePtr m_type;
  const OdRxObject* m_owner;
  OdArray<OdRxMemberPtr>* m_children;
  static OdRxMemberImpl* getImpl(const OdRxMember* tag)
  {
    return tag->m_pImpl;
  }
  OdRxMemberImpl() : m_children(0), m_owner(0){}
  ~OdRxMemberImpl() {
    delete m_children;
  }
};

class OdRxMemberCollectionImpl : public OdRxMemberCollection
{
public:
  OdArray<OdRxMemberPtr> m_members;
  virtual int count() const ODRX_OVERRIDE;
  virtual OdRxMember* getAt(int index) const ODRX_OVERRIDE;
  void collectMembers(const OdRxClass* pClass, OdRxMemberCollectionConstructorPtr c, void* userData);
};

class OdRxPropertyBaseImpl : public OdRxMemberImpl {};
class OdRxPropertyImpl : public OdRxPropertyBaseImpl {};
class OdRxCollectionPropertyImpl : public OdRxPropertyBaseImpl {};
class OdRxIndexedPropertyImpl : public OdRxCollectionPropertyImpl {};
class OdRxDictionaryPropertyImpl : public OdRxCollectionPropertyImpl {};

#endif
