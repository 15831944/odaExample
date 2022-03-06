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

#ifndef _DAI_WHERE_RULE_H_
#define _DAI_WHERE_RULE_H_

#include "daiDictionaryInstance.h"
#include "daiPrimitive.h"

//DOM-IGNORE-BEGIN
class AST;
//DOM-IGNORE-END

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class Schema;

  class NamedType;

  class ApplicationInstance;
  typedef OdSmartPtr<ApplicationInstance> ApplicationInstancePtr;

  /** \details
  This class represents a where rule for instance validation pourposes.
  */
  class DAI_EXPORT WhereRule : public DictionaryInstance
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(WhereRule);
    //DOM-IGNORE-END

    //static OdSmartPtr<WhereRule> createObject(OdDAI::Schema *schema, const OdAnsiString &label, const OdAnsiString &expression);
    static OdSmartPtr<WhereRule> createObject(OdDAI::Schema *schema, const OdAnsiString &label, AST *ast);

    /** \details
    Destructor.
    */
    ~WhereRule();

    /** \details
    Returns a label of the Where Rule.
    */
    const OdAnsiString& label() const { return m_label; }

    /** \details
    Returns an original label of the Where Rule in form which it presents in schema.
    */
    const OdAnsiString& originalLabel() const { return m_originalLabel; }

    /** \details
    Retrieves the current value of an attribute specified by its name.
    \param attrName [in] An ANSI string that contains the attribute name.
    \returns Returns the current value of the attribute.
    \remarks
    The method provides the late binding access to the attribute value by its name.
    Attributes of select and aggregate data types are also supported.
    */
    virtual OdRxValue getAttr(const char * attrName) const;

    /** \details

    */
    OdDAI::Logical validate(const ApplicationInstancePtr inst) const;

    /** \details

    */
    OdDAI::Logical validate(const OdRxValue &val, const OdDAI::Schema *schema) const;


    /** \details
    Returns an expression of the Where Rule.
    \returns Returns an expression of the Where Rule.
    */
    const OdAnsiString expression() const;

    AST* ast() const { return m_expression; };

//DOM-IGNORE-BEGIN
  private:

    OdAnsiString m_label;
    OdAnsiString m_originalLabel;
    AST *m_expression = nullptr;

    // TypeOrRule m_parentItem;

    friend class Session;
//DOM-IGNORE-END

  };
  typedef OdSmartPtr<WhereRule> WhereRulePtr;

}

#endif // _DAI_WHERE_RULE_H_
