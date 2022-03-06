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

#ifndef _DAI_EXPLICIT_OR_DERIVED_H
#define _DAI_EXPLICIT_OR_DERIVED_H

#include "daiDictionaryInstance.h"
#include "daiBaseType.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class ExplicitAttribute;
  class DerivedAttribute;

  /** \details
  Container for defenition of Explicit Attribute or Derived Attribute.
  */
  class DAI_EXPORT ExplicitOrDerived : public DictionaryInstance
  {
  public:

    ODRX_DECLARE_MEMBERS(ExplicitOrDerived);

    typedef enum {
      kUnset             = 0,
      kExplicitAttribute = 1,
      kDerivedAttribute  = 2
    } OdExplicitOrDerivedKind;

    static OdSmartPtr<ExplicitOrDerived> createObject(ExplicitAttribute *explicitAttribute);
    static OdSmartPtr<ExplicitOrDerived> createObject(DerivedAttribute *derivedAttribute);

    ExplicitOrDerived() : m_kind(kUnset) {};
    int exists() const { return m_kind == kUnset ? 0 : 1; };
    void unset() { m_kind = kUnset; };
    OdExplicitOrDerivedKind kind() const { return m_kind; };

    bool isExplicitAttribute() const { return m_kind == kExplicitAttribute; };
    void setExplicitAttribute(ExplicitAttribute *explicitAttribute);
    const ExplicitAttribute* explicitAttribute() const;

    bool isDerivedAttribute() const { return m_kind == kDerivedAttribute; };
    void setDerivedAttribute(DerivedAttribute *derivedAttribute);
    const DerivedAttribute* derivedAttribute() const;

    const BaseTypePtr domain() const;
    bool optional() const;

  private:

    OdExplicitOrDerivedKind m_kind;
    AttributePtr m_pAttribute;

    friend class Schema;
  };
  typedef OdSmartPtr<ExplicitOrDerived> ExplicitOrDerivedPtr;

}

#endif // _DAI_EXPLICIT_OR_DERIVED_H
