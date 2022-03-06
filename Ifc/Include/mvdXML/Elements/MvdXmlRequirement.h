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

#if !defined(ODA_ODMVDXMLREQUIREMENT_H_INCLUDED_)
#define ODA_ODMVDXMLREQUIREMENT_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MvdXmlElement.h"

namespace OdMvdXml
{
  class MVDXML_EXPORT OdMvdXmlRequirement : public OdMvdXmlElement
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlRequirement);

  public:
    const OdGUID& getExchangeRequirement() const;
    const OdMvdRequirement& getRequirement() const;
    const OdMvdApplicability& getApplicability() const;

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
    virtual OdResult inAttributes(TiXmlElement* pParent) override;

    /** \details
      Writing attributes to the xml element.

      \param pItem [in] Pointer to the xml element to which you want to add attributes.

      \returns eOk if the data was written successfully; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult outAttributes(TiXmlElement* pItem) override;

  private:
    /** \details
      Identifies the ExchangeRequirement by GUID within the same Model View
      Definition.
    */
    OdGUID m_exchangeRequirement;
    /** \details
      Describes the interpretation of the result of the outermost TemplateRule
      specific for one exchange requirements.
       - mandatory : must be true, otherwise create an error
       - recommended : should be true, otherwise create a warning
       - not-relevant : no requirement;
       - not-recommended: should not be true, otherwise create a warning
       - excluded : must not be true, otherwise create an error
    */
    OdMvdRequirement m_requirement;
    /** \details
      Identifies if the requirement applies to
       - import
       - export
       - both
      NOTE If such value is provided, then it must match, if given, with the
      applicability setting of the exchange requirement in which it is used.
    */
    OdMvdApplicability m_applicability;
  };
  SMARTPTR(OdMvdXmlRequirement);
}

#endif // !defined(ODA_ODMVDXMLREQUIREMENT_H_INCLUDED_)

