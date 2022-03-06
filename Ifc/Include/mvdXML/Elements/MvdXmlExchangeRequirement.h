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

#if !defined(ODA_ODMVDXMLEXCHANGEREQUIREMENT_H_INCLUDED_)
#define ODA_ODMVDXMLEXCHANGEREQUIREMENT_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MvdXmlIdentity.h"

namespace OdMvdXml
{
  SMARTPTR(OdMvdXmlExchangeRequirement);

  class MVDXML_EXPORT OdMvdXmlExchangeRequirement : public OdMvdXmlIdentityDefinitions
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlExchangeRequirement);

  public:
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

    /** \details
      Identifies if the ERM is specific for:
       - import
       - export
       - both
    */
    OdMvdApplicability m_applicability;
  };
}

#endif // !defined(ODA_ODMVDXMLEXCHANGEREQUIREMENT_H_INCLUDED_)

