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

#ifndef _BFC_COMPONENT_H
#define _BFC_COMPONENT_H

#include "BcfCommon.h"

#include "BcfElement.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfSession;

  /** \details
  A class that stores data of a component.
  */
  class OdBcfComponentData
  {
  protected:
    /**An IFC global unique identifier (IfcGUID) of the component.*/
    OdString m_ifcGuid;
    /**A string that contains the name of the original system for the component.*/
    OdString m_originatingSystem;
    /**A string that contains the identifier of the authoring tool that was used to create the component.*/
    OdString m_authoringToolId;

    friend OdBcfSession;
  };

  /** \details
  A class that stores and operates a component data type.
  */
  class BCF_EXPORT OdBcfComponent : public OdBcfElement, protected OdBcfComponentData
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfComponent);
    //DOM-IGNORE-END

    /** \details
    Creates a new component object with default parameters.
    */
    OdBcfComponent();

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
    Checks whether the component instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;
    
    /** \details
    Retrieves the IFC global unique identifier (IfcGUID) of the component object.
    \returns A string that contains the IfcGUID value.
    \remarks  
    The string with the IfcGUID returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getIfcGuid() const;

    /** \details
    Defines whether the IFC global unique identifier (IfcGUID) of the component object is not initialized.
    \returns true if the IfcGUID is not initialized; otherwise, the method returns false.
    */
    bool isIfcGuidUnset() const;

    /** \details
    Retrieves the originating system's name of the component object.
    \returns A string that contains the originating system's name.
    \remarks 
    The string returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getOriginatingSystem() const;

    /** \details
    Defines whether the originating system name is not initialized.
    \returns true if the originating system name is not initialized; otherwise, the method returns false.
    */
    bool isOriginatingSystemUnset() const;

    /** \details
    Retrieves the identifier of the authoring tool that was used for the creation of the component object.
    \returns A string that contains the authoring tool identifier.
    \remarks 
    The string returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getAuthoringToolId() const;

    /** \details
    Defines whether the identifier of the authoring tool that was used for the component object creation is not initialized.
    \returns true if the authoring tool identifier is not initialized; otherwise, the method returns false.
    */
    bool isAuthoringToolIdUnset() const;


    //DOM-IGNORE-BEGIN
  protected:
    OdBcfComponent& operator = (const OdBcfComponentData &val);

    friend class OdBcfSession;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfComponent, OdBcfComponent> object.
  */
  typedef OdSmartPtr<OdBcfComponent> OdBcfComponentPtr;

} //namespace OdBcf

#endif // _BFC_COMPONENT_H
