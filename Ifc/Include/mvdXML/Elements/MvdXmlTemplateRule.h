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

#if !defined(ODA_ODMVDXMLTEMPLATERULE_H_INCLUDED_)
#define ODA_ODMVDXMLTEMPLATERULE_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IfcEntity.h"
#include "MvdXmlDefinition.h"
#include "MvdXmlConceptTemplate.h"

namespace OdMvdXml
{
  SMARTPTR(OdMvdXmlTemplateRule);

  class MVDXML_EXPORT OdMvdXmlTemplateRule : public OdMvdXmlDefinitions
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlTemplateRule);

  public:
    const OdAnsiString& getParameters() const { return m_parameters; };
    void setParameters(const OdAnsiString &value) { m_parameters = value; };

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
      Writing attributes to the xml element.

      \param pItem [in] Pointer to the xml element to which you want to add attributes.

      \returns eOk if the data was written successfully; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult outAttributes(TiXmlElement* pItem) override;

  private:
    /** \details
      Parameters string is defined by expression where each boolean_term requires a parameter.
      The parameter corresponds to the RuleID of an AttributeRule or EntityRule at the referenced ConceptTemplate.
    */
    OdAnsiString m_parameters;
  };
}

#endif // !defined(ODA_ODMVDXMLTEMPLATERULE_H_INCLUDED_)

