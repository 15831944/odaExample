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

#ifndef _DAI_ATTRIBUTE_COLLECTION_H_
#define _DAI_ATTRIBUTE_COLLECTION_H_

#include "TD_PackPush.h"

#include "daiEntity.h"
#include "daiAttribute/AttributeKeyCollection.h"
#include "daiAggr/daiSet.h"
#include "daiAggr/daiBag.h"

#define STL_USING_LIST
#include "OdaSTL.h"

namespace OdDAI
{
  class OutFieldsController
  {
  public:
    virtual bool onBeforeWriteAttribute(OdDAI::OdSpfFilerBase* rdFiler, const AttributeKey* attribute) = 0;
    virtual void onAfterWriteAttribute(OdDAI::OdSpfFilerBase* rdFiler, const AttributeKey* attribute) = 0;
  };

  class DAI_EXPORT DynamicAttributeHolder
  {
  public:
    using ComplexEntityReadInfo = std::pair<OdDAI::DynamicAttributeHolder,const AttributeKeyCollection*>;

  public:

    bool isNull() { return m_data == nullptr; };

    template<class TType>
    inline TType* getTypedAttr(const char* attrName, const OdDAI::AttributeKeyCollection& attributeCollection, bool inverse);

    template<class TType>
    inline bool setTypedAttr(const char* attrName, const TType& newValue, const OdDAI::AttributeKeyCollection& attributeCollection, bool inverse);

    bool comparedToEarlyImpl(const OdDAI::DynamicAttributeHolder& otherAttributes,
                             OdRx::Ordering& ordering, 
                             const OdDAI::AttributeKeyCollection& attributeCollection) const;

    bool copy(const OdDAI::DynamicAttributeHolder& from, const OdDAI::AttributeKeyCollection& attributeCollection);
    

    OdRxValue getAttr(const OdDAI::AttributeKey* attrKey, const OdDAI::AttributeKeyCollection& attributeCollection);
    OdRxValue getAttr(const char* attrName, const OdDAI::AttributeKeyCollection& attributeCollection, bool inverse);
    
    bool testAttr(const char* attrName, const OdDAI::AttributeKeyCollection& attributeCollection, bool inverse) const;
    bool testAttr(const AttributePtr& attribute, const OdDAI::AttributeKeyCollection& attributeCollection, bool inverse) const;
    
    bool putAttr(const char* attrName, const OdRxValue& val, const OdDAI::AttributeKeyCollection& attributeCollection, bool inverse);
    void unsetAttr(const char* attrName, const OdDAI::AttributeKeyCollection& attributeCollection, bool inverse);
    void unsetAttr(const AttributePtr& attribute, const OdDAI::AttributeKeyCollection& attributeCollection, bool inverse);

    void inFields(OdDAI::OdSpfFilerBase* rdFiler, const OdDAI::AttributeKeyCollection& attributeCollection);
    void outFields(OdDAI::OdSpfFilerBase* wrFiler, const OdDAI::AttributeKeyCollection& attributeCollection);
    void outFields(OdDAI::OdSpfFilerBase* wrFiler, 
                   const OdDAI::AttributeKeyCollection& attributeCollection, 
                   OutFieldsController* controller);

    void init(const OdDAI::AttributeKeyCollection& attributeCollection, const unsigned char* initFrom = nullptr);
    void init(const OdDAI::AttributeKeyCollection& attributeCollection, 
              std::list<DynamicAttributeHolder::ComplexEntityReadInfo>& complexReadDataCollection);

    void clean(const OdDAI::AttributeKeyCollection& attributeCollection);
    bool getData(const OdDAI::AttributeKeyCollection& attributeCollection, unsigned char* copyTo);

  private:
    mutable unsigned char* m_data = nullptr; 
  };

  template<class TType>
  inline TType* DynamicAttributeHolder::getTypedAttr(const char* attrName, const OdDAI::AttributeKeyCollection& attributeCollection, bool inverse)
  {
    if (!attrName)
    {
      return nullptr;
    }

    const OdDAI::AttributeKey* key = !inverse ? attributeCollection.getByName(attrName) : attributeCollection.getByNameInverse(attrName);

    if (!key)
    {
      return nullptr;
    }

    if (m_data == nullptr)
    {
      init(attributeCollection);
    }

    return reinterpret_cast<TType*>(m_data + key->typeOffset);
  }

  template<class TType>
  inline bool DynamicAttributeHolder::setTypedAttr(const char* attrName, const TType& newValue, const OdDAI::AttributeKeyCollection& attributeCollection, bool inverse)
  {
    if (!attrName)
    {
      return false;
    }

    const OdDAI::AttributeKey* key = !inverse ? attributeCollection.getByName(attrName) : attributeCollection.getByNameInverse(attrName);
    if (!key)
    {
      return false;
    }

    if (m_data == nullptr)
    {
      init(attributeCollection);
    }

    *reinterpret_cast<TType*>(m_data + key->typeOffset) = newValue;
    return true;
  }

  #if !defined(SWIG)
  template OdDAIObjectId* DynamicAttributeHolder::getTypedAttr<>(const char* attrName, const OdDAI::AttributeKeyCollection& attributeCollection, bool inverse) ;
  template OdDAI::Set<OdDAIObjectId>* DynamicAttributeHolder::getTypedAttr<>(const char* attrName, const OdDAI::AttributeKeyCollection& attributeCollection, bool inverse) ;
  template OdDAI::Bag<OdDAIObjectId>* DynamicAttributeHolder::getTypedAttr<>(const char* attrName, const OdDAI::AttributeKeyCollection& attributeCollection, bool inverse);
  #endif
}


#include "TD_PackPop.h"

#endif // _DAI_TYPECODE_H_
