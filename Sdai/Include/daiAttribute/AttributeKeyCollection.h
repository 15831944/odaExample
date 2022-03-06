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

#ifndef _DAI_ATTRIBUTE_KEY_COLLECTION_H_
#define _DAI_ATTRIBUTE_KEY_COLLECTION_H_

#include "OdaCommon.h"
#include "TD_PackPush.h"
#include "daiTypeCode.h"

#define STL_USING_FUNCTIONAL
#define STL_USING_VECTOR
#include "OdaSTL.h"

#include "daiAttribute/AttributeKey.h"

namespace OdDAI
{
  class Attribute;
  class Entity;
  class OdSpfFilerBase;

  enum KeyCollectionEntityType
  {
    entityStaticSchema = 0,
    entityRuntime,
    entityComplex,
    entityPartialComplex,

    entityTypesCount,
  };

  class DAI_EXPORT AttributeKeyCollection
  {
  public:
    const AttributeKey* getByAttribute(const Attribute* attribute) const;
    const AttributeKey* getByAttributeInverse(const Attribute* attribute) const;
    const AttributeKey* getByName(const char* name) const;
    const AttributeKey* getByNameInverse(const char* name) const;

    size_t  getCount(bool withInverse) const;
    unsigned int  getDataBlockSize() const;

    void forEachKeyInDeclareOrder(std::function<bool(const AttributeKey*)> callBack) const;

    void createBuffer(unsigned char** buffer) const;
    void cleanBuffer(unsigned char* buffer) const;

    static std::unique_ptr<OdDAI::AttributeKeyCollection> createByType(KeyCollectionEntityType entityType, const OdDAI::Entity* entity);

  private:

    void emplace_key(AttributeKey&& key);
    void emplace_inverse_key(AttributeKey&& key);

    void sortKeys();

    static std::unique_ptr<OdDAI::AttributeKeyCollection> createFromEntity(const OdDAI::Entity* entityOfInstance);
    static std::unique_ptr<OdDAI::AttributeKeyCollection> createFromEntityInverseOnly(const OdDAI::Entity* entityOfInstance);
    static std::unique_ptr<OdDAI::AttributeKeyCollection> createFromEntityComplex(const OdDAI::Entity* entityOfInstance);
    static std::unique_ptr<OdDAI::AttributeKeyCollection> createFromEntityForComplexRead(const OdDAI::Entity* entityOfInstance);

    static void collectAttributeKeys(const OdDAI::Entity* parent,
                                     OdDAI::AttributeKeyCollection& keyCollection,
                                     const OdDAI::Entity* entityOfInstance,
                                     unsigned int& orderIndex, 
                                     bool forComplexRead = false);


    static void collectParentKeys(const OdDAI::Entity* parent,
                                  OdDAI::AttributeKeyCollection& keyCollection,
                                  unsigned int& orderIndex,
                                  const OdDAI::Entity* entityOfInstance,
                                  OdArray<const OdDAI::Entity*>& processed);

    static void collectParentKeysInverseOnly(const OdDAI::Entity* parent,
                                             OdDAI::AttributeKeyCollection& keyCollection);

    static void collectComplexKeys(const OdDAI::Entity* parent,
                                   OdDAI::AttributeKeyCollection& keyCollection);

  private:
    std::vector<AttributeKey> m_collection;
    std::vector<AttributeKey> m_collectionInverse;

    std::vector<const AttributeKey*> m_collectionDeclareOrder;

    unsigned int    m_dataBlockSize = 0;
  };
}

#include "TD_PackPop.h"

#endif // _DAI_ATTRIBUTE_KEY_H_
