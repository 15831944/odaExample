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

#ifndef _DAI_GLOBAL_RULE_H_
#define _DAI_GLOBAL_RULE_H_

#include "daiDictionaryInstance.h"
#include "daiWhereRule.h"
#include "daiValueTypes.h"
#include "daiPrimitive.h"

//DOM-IGNORE-BEGIN
class AST;
//DOM-IGNORE-END

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class Schema;

  class Model;
  typedef OdSmartPtr<Model> ModelPtr;

  class Entity;
  typedef OdSmartPtr<Entity> EntityPtr;

  //class WhereRule;
  //typedef OdSmartPtr<WhereRule> WhereRulePtr;

  class NamedType;

  class ApplicationInstance;
  typedef OdSmartPtr<ApplicationInstance> ApplicationInstancePtr;

  /** \details
  This class represents a Global Rule for model validation pourposes.
  */
  class DAI_EXPORT GlobalRule : public DictionaryInstance
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(GlobalRule);
    //DOM-IGNORE-END

    static OdSmartPtr<GlobalRule> createObject(OdDAI::Schema *schema, const OdAnsiString &name, const OdArray<EntityPtr> &entities, AST *ast);

    /** \details
    Destructor.
    */
    ~GlobalRule();

    /** \details
    Returns a label of the Where Rule.
    */
    const OdAnsiString& name() const { return m_name; }

    /** \details
    Returns an original label of the Where Rule in form which it presents in schema.
    */
    const OdAnsiString& originalName() const { return m_originalName; }

    /** \details
    Retrieves an array of entity definitions for which global rule to be applied.
    \returns Returns an OdArray of smart pointers to Entity instances.
    */
    const OdArray<EntityPtr>& entities() const { return m_entities; }

    /** \details
    Returns a raw pointer to parent Schema instance.
    */
    Schema* parentSchema() const { return m_parentSchema; }

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
    OdDAI::Logical validate(ModelPtr model, OdAnsiStringList &aggr) const;

    /** \details
    Retrieves a Where Rules list associated with the Named Type.
    \returns Returns a list of pointers to associated Where Rules.
    */
    const WhereRuleList& whereRules() const { return m_whereRules; };

    /** \details
    Returns an expression of the Where Rule.
    \returns Returns an expression of the Where Rule.
    */
    const OdAnsiString expression() const;

//DOM-IGNORE-BEGIN

    /** \details
    Append Where Rule to the Named Type.
    \param ruleDef [in] Smart pointer to rule definition.
    */
    void appendWhereRule(WhereRule *ruleDef);

    AST* ast() const { return m_expression; };

  private:

    OdAnsiString m_name;
    OdAnsiString m_originalName;
    OdArray<OdDAI::EntityPtr> m_entities;
    WhereRuleList m_whereRules;
    Schema *m_parentSchema;

    AST *m_expression;

    friend class Session;
//DOM-IGNORE-END

  };
  typedef OdSmartPtr<GlobalRule> GlobalRulePtr;

}

#endif // _DAI_GLOBAL_RULE_H_
