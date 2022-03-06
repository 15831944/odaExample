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

#ifndef _DAI_ENUM_VALUE_TYPE_H_
#define _DAI_ENUM_VALUE_TYPE_H_

#include "OdaCommon.h"
#include "daiEnum.h"
#include "daiEnumDefines.h"
#include "daiAggr/daiTypedAggrItemManager.h"

#define STL_USING_VECTOR
#include "OdaSTL.h"

#include "RxValueTypeUtil.h"

ODRX_DECLARE_VALUE_TYPE(OdDAI::Enum, DAI_EXPORT);
DAI_DECLARE_VT_ENUM_PTR(OdDAI::Enum, DAI_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdArray<OdDAI::Enum>, DAI_EXPORT);
 
bool DAI_EXPORT operator >> (const OdRxValue& valueFrom, OdDAI::Enum& itemTo);

template<> DAI_EXPORT bool OdRxEnumType<OdDAI::Enum>::subEqualTo(const void* a, const void* b) const; 
template<> DAI_EXPORT OdRxValue::OdRxValue(OdDAI::Enum const& val) throw();
template<> DAI_EXPORT OdString OdRxEnumType<OdDAI::Enum>::subToString(const void* instance, OdRxValueType::StringFormat) const;
template<> DAI_EXPORT bool OdRxEnumWithUnderlyingType<OdDAI::Enum>::subToValueType(const OdRxValueType& vt, const OdRxValue& instance, OdRxValue& subVal) const;

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI
{
  /** \details 
  A class that implements storing enumeration data type within OdRx functionality.
  */
  class DAI_EXPORT EnumTypePOD
    : public OdRxEnumWithUnderlyingType<OdDAI::Enum>
  {
  public:
    /** \details 
    Create a new enumeration data type with default parameters.
    */
    EnumTypePOD();
    
    /** \details 
    Creates a new enumeration data type with a specified name.
    \param uniqueName [in] A string that contains the enumeration unique name.
    */
    EnumTypePOD(const wchar_t* uniqueName);

    bool subToValueType(const OdRxValueType& vt, const OdRxValue& instance, OdRxValue& subVal) const override;
    bool subFromValueType(const OdRxValue& from, OdRxValue& instance) const override;

  protected:
    bool fromEnumtoValueType(const OdRxValueType& vt, const Enum& instance, OdRxValue& subVal) const;
  };
}

namespace OdDAI
{
  class DAI_EXPORT SpecifiedEnumValueType
    : public EnumTypePOD
  {
  public:

    static SpecifiedEnumValueType*  createObject(const OdDAI::EnumerationType* enumerationType);
    static void releaseObject(SpecifiedEnumValueType* enumerationType);

    int count() const override;
    const OdRxEnumTag& getAt(int i) const override;

    bool subToValueType(const OdRxValueType& vt, const OdRxValue& instance, OdRxValue& subVal) const override;

  protected:
    SpecifiedEnumValueType(const OdDAI::EnumerationType* enumerationType);

  protected:
    const OdDAI::EnumerationType* m_enumerationType = nullptr;
    mutable std::vector<OdRxEnumTagPtr>   m_tagCollection;
    mutable OdRxEnumTagPtr  m_unsetledTag;
  };

}

namespace OdDAI
{

  struct EmptyEnumPtrEnumeration
    : public IOdRxEnumeration
  {
  public:
    EmptyEnumPtrEnumeration()
      : m_emptyTag(OdRxEnumTag::createObject())
    {
    }

  private:

    int count() const override { return 0; }

    const OdRxEnumTag& getAt(int index) const override
    {
      return *m_emptyTag.get();
    }

  public:
    OdRxEnumTagPtr m_emptyTag;
  };

  class DAI_EXPORT EnumPtrTypePOD
    : public OdRxValueTypePOD<Enum*>
  {
  public:
    EnumPtrTypePOD();
    
    bool subToValueType(const OdRxValueType& vt, const OdRxValue& instance, OdRxValue& subVal) const override;
    bool subEqualTo(const void* a, const void* b) const override;
    OdString subToString(const void* instance, StringFormat format) const override;

    const IOdRxEnumeration* enumeration() const override;

  protected:
    EnumPtrTypePOD(const OdChar* customName);

  protected:
    bool fromEnumtoValueType(const OdRxValueType& vt, const Enum& instance, OdRxValue& subVal) const;

  private:
    // TODO: change to unique_ptr, when we exclude gcc5.3
    EmptyEnumPtrEnumeration m_emptyEnumeration;
  };
}

namespace OdDAI
{
  class SpecifiedEnumPtrValueType;

  class SpecifiedPtrEnumeration
    : public IOdRxEnumeration
  {
  public:
    SpecifiedPtrEnumeration(const OdDAI::EnumerationType* enumerationType,
                            SpecifiedEnumPtrValueType* owner);

    int count() const override;
    const OdRxEnumTag& getAt(int i) const override;
    const OdDAI::EnumerationType* getEnumerationType();

  private:
    const OdDAI::EnumerationType* m_enumerationType;
    SpecifiedEnumPtrValueType* m_owner;
    mutable std::vector<OdRxEnumTagPtr>   m_tagCollection;
    mutable OdRxEnumTagPtr  m_unsetledTag;
  };

  class DAI_EXPORT SpecifiedEnumPtrValueType
    : public EnumPtrTypePOD
  {
  public:

    static SpecifiedEnumPtrValueType* createObject(const OdDAI::EnumerationType* enumerationType);
    static void releaseObject(SpecifiedEnumPtrValueType* enumerationType);

    const IOdRxEnumeration* enumeration() const override;
    bool subToValueType(const OdRxValueType& vt, const OdRxValue& instance, OdRxValue& subVal) const override;

  protected:
    SpecifiedEnumPtrValueType(const OdDAI::EnumerationType* enumerationType);

  protected:
    OdSharedPtr<SpecifiedPtrEnumeration> m_enumeration;
  };

}


namespace OdDAI
{
  template<class SchemaItemTypeProvide>
  class TypedAggrItemManager<OdDAI::Enum, SchemaItemTypeProvide>
  {
  public:
    static  bool translate(const OdRxValue& valueFrom, OdDAI::Enum& itemTo)
    {
      itemTo = OdDAI::Enum(SchemaItemTypeProvide::SchemaType());
      return valueFrom >> itemTo;
    }

    static bool checkType(const OdDAI::Enum& itemTo)
    {
      return itemTo.getSchemaType() == SchemaItemTypeProvide::SchemaType();
    }
  };

}


#endif
