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

#if !defined(ODA_ODMVDXMLMODELVIEW_H_INCLUDED_)
#define ODA_ODMVDXMLMODELVIEW_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MvdXmlIdentity.h"
#include "MvdXmlConceptRoot.h"
#include "MvdXmlExchangeRequirement.h"

namespace OdMvdXml
{
  SMARTPTR(OdMvdXmlModelView);

  class MVDXML_EXPORT OdMvdXmlModelView : public OdMvdXmlIdentityDefinitions
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlModelView);

  public:
    const OdAnsiString& getApplicableSchema() const { return m_applicableSchema; };
    void setApplicableSchema(const OdAnsiString &value) { m_applicableSchema = value; };
    const OdAnsiString& getBaseView() const { return m_baseView; };
    void setBaseView(const OdAnsiString &value) { m_baseView = value; };
    const OdMvdXmlConceptRootPtrArray& getConceptRoots() const;

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
      Identifies the default schema for which the template applies, such as
      IFC2X_FINAL, IFC2X2_FINAL, IFC2X3, or IFC4.The template may be
      used for model views of other schemas, if all enclosed rules resolve to
      available attributes and types.
    */
    OdAnsiString m_applicableSchema;
    /** \details
      Reference to a base model view definition(in case that this model view
      represents an add - on model view that extents a base view).
    */
    OdAnsiString m_baseView;
    /** \details
      List of exchange requirements defined within this model view.
      They should appear in logical order.
    */
    OdMvdXmlExchangeRequirementPtrArray m_exchangeRequirements;
    /** \details
      List of root concepts defined within scope of the model view.
    */
    OdMvdXmlConceptRootPtrArray m_roots;
  }; 
}

#endif // !defined(ODA_ODMVDXMLMODELVIEW_H_INCLUDED_)

