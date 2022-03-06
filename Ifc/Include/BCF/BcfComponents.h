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

#ifndef _BFC_COMPONENTS_H
#define _BFC_COMPONENTS_H

#include "BcfCommon.h"

#include "BcfElement.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfViewSetupHints;
  typedef OdSmartPtr<OdBcfViewSetupHints> OdBcfViewSetupHintsPtr;

  class OdBcfComponentSelection;
  typedef OdSmartPtr<OdBcfComponentSelection> OdBcfComponentSelectionPtr;

  class OdBcfComponentVisibility;
  typedef OdSmartPtr<OdBcfComponentVisibility> OdBcfComponentVisibilityPtr;

  class OdBcfComponentColoring;
  typedef OdSmartPtr<OdBcfComponentColoring> OdBcfComponentColoringPtr;

  class OdBcfSession;

  /** \details
  A class that stores and operates the components data type.
  */
  class BCF_EXPORT OdBcfComponents : public OdBcfElement
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfComponents);
    //DOM-IGNORE-END

    /** \details
    Creates a new components object.
    \param pVisibility     [in] A smart pointer to the value that determines the visibility of components.
    \param pViewSetupHints [in] A smart pointer to the value that determines the view setup hints of components.
    \param pSelection      [in] A smart pointer to the selection of components.
    \param pColoring       [in] A smart pointer to the coloring of components.
    \returns A smart pointer to the created <link OdBcf::OdBcfComponents, OdBcfComponents> instance.
    */
    static OdSmartPtr<OdBcfComponents> createObject(
      const OdBcfComponentVisibilityPtr &pVisibility,
      const OdBcfViewSetupHintsPtr      &pViewSetupHints = OdBcfViewSetupHintsPtr(),
      const OdBcfComponentSelectionPtr  &pSelection = OdBcfComponentSelectionPtr(),
      const OdBcfComponentColoringPtr   &pColoring = OdBcfComponentColoringPtr());

    /** \details
    Reads XML data into ODA data structures.
    \param pParent [in] A pointer to the parent element of the data structure.
    \returns eOk if data was successfully read; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult inFields(TiXmlElement *pParent) ODRX_OVERRIDE;

    /** \details
    Writes data into XML structures.
    \param pParent [in] A pointer to the parent element of the data structure.
    \returns eOk if data was successfully written; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult outFields(TiXmlElement *pParent) const ODRX_OVERRIDE;

    /** \details
    Checks whether components instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    /** \details
    Retrieves the view setup hints of the components.
    \returns A smart pointer to the <link OdBcf::OdBcfViewSetupHints, OdBcfViewSetupHints> object that represents the view setup hints.
    \remarks 
    The view setup hints object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfViewSetupHintsPtr& getViewSetupHints() const;

    /** \details
    Defines whether the view setup hints of components are not initialized.
    \returns true if the view setup hints are not initialized; otherwise, the method returns false.
    */
    bool isViewSetupHintsUnset() const;

    /** \details
    Retrieves the components selection.
    \returns A smart pointer to the <link OdBcf::OdBcfComponentSelection, OdBcfComponentSelection> object that represents the selection.
    \remarks 
    The components selection object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfComponentSelectionPtr& getSelection() const;

    /** \details
    Defines whether the components selection is not initialized.
    \returns true if the components selection is not initialized; otherwise, the method returns false.
    */
    bool isSelectionUnset() const;

    /** \details
    Retrieves the visibility of the components.
    \returns A smart pointer to the <link OdBcf::OdBcfComponentVisibility, OdBcfComponentVisibility> object that represents the visibility of the components.
    \remarks 
    The visibility of the components returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfComponentVisibilityPtr& getVisibility() const;

    /** \details
    Defines whether the visibility of the components is not initialized.
    \returns true if the visibility of the components is not initialized; otherwise, the method returns false.
    */
    bool isVisibilityUnset() const;

    /** \details
    Retrieves the coloring of the components.
    \returns A smart pointer to the <link OdBcf::OdBcfComponentColoring, OdBcfComponentColoring> object that represents the coloring the components.
    \remarks 
    The coloring of the components returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfComponentColoringPtr& getColoring() const;

    /** \details
    Defines whether the coloring of the components is not initialized.
    \returns true if the coloring of the components is not initialized; otherwise, the method returns false.
    */
    bool isColoringUnset() const;


    //DOM-IGNORE-BEGIN
  protected:
    OdBcfViewSetupHintsPtr      m_pViewSetupHints;
    OdBcfComponentSelectionPtr  m_pSelection;
    OdBcfComponentVisibilityPtr m_pVisibility;
    OdBcfComponentColoringPtr   m_pColoring;

    friend OdBcfSession;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfComponents, OdBcfComponents> object.
  */
  typedef OdSmartPtr<OdBcfComponents> OdBcfComponentsPtr;

} //namespace OdBcf

#endif // _BFC_COMPONENTS_H
