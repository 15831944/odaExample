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

#if !defined(ODA_ODMVDXMLTEMPLATERULES_H_INCLUDED_)
#define ODA_ODMVDXMLTEMPLATERULES_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MvdXmlDefinition.h"
#include "MvdXmlTemplateRule.h"

namespace OdMvdXml
{
  SMARTPTR(OdMvdXmlTemplateRules);

  /** \details
    This element establishes the possibility to define a tree of logical expressions. Individual TemplateRule are 
    grouped under a TemplateRules element and are logically interpreted by the @operator attribute.

    \remarks
    This  improves  the  previous  way  to  embed  the  logical  operator  in  the  Parameter  string  at  the
    TemplateRule. Due to its tree structure realized by the recursive definition of TemplateRules, the logical operators
    can be nested.
  */
  class MVDXML_EXPORT OdMvdXmlTemplateRules : public OdMvdXmlDefinitions
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlTemplateRules);

  public:
    /** \details
      Reads data from a xml element.

      \param pItem [in] Pointer to a xml element containing data.

      \returns eOk if the data was successfully read; otherwise, the method returns an appropriate error code.
    */
    OdResult inFields(TiXmlElement* pParent);
    OdResult execute(const OdMvdXmlConceptTemplate* pTemplate, bool& result) const;

  protected:
    /** \details
      Retrieves the name of the element. This name is used to write the element to a file.

      \returns The name of the element.
    */
    virtual OdAnsiString getElementName();

    /** \details
      Reads attributes from a xml element.

      \param pItem [in] Pointer to a xml element containing attributes.

      \returns eOk if the data was successfully read; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult inAttributes(TiXmlElement* pItem) override;

    /** \details
      Reads child element from a xml element.

      \param nodeName [in] The node name of the xml element containing the child data.
      \param pChild [in] Pointer to a xml element containing child data.

      \returns eOk if the data was successfully read; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult inChildNode(const char *nodeName, TiXmlElement* pChild) override;

    /** \details
      Writing attributes to the xml element.

      \param pItem [in] Pointer to the xml element to which you want to add attributes.

      \returns eOk if the data was written successfully; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult outAttributes(TiXmlElement* pItem) override;

    /** \details
      Writing child elements to the xml element.

      \param pParent [in] Pointer to the xml element to which you want to add children.

      \returns eOk if the data was written successfully; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult outChildNodes(TiXmlNode* pParent) override;

  private:
    /** \details
      The logical operator, which is used to combine the nested TemplateRules
      and TemplateRule.The Boolean results of the nested rules are combined
      by the logical operation according to the Truth table.
      The following logical operators are defined :
       - AND
       - OR
       - NOT
       - NAND
       - NOR
       - XOR
       - NXOR
      NOTE : The valid number of the nested elements depend on the value of
      the @operator. E.g. for the operator NOT, only one nested element shall
      exist.
    */
    OdMvdOperator m_operator;
    /** \details
      Set of Template Rules.
    */
    OdMvdXmlTemplateRulePtrArray  m_rules;
    /** \details
      Tree of TemplateRules.
    */
    OdMvdXmlTemplateRulesPtrArray m_subrules;
  };
}

#endif // !defined(ODA_ODMVDXMLTEMPLATERULES_H_INCLUDED_)

