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

#ifndef _BFC_PROJECT_EXTENSION_H
#define _BFC_PROJECT_EXTENSION_H

#include "BcfCommon.h"
#include "OdArray.h"
#include "OdGUID.h"

#include "BcfElement.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfProject;
  typedef OdSmartPtr<OdBcfProject> OdBcfProjectPtr;

  class OdBcfSession;

  /** \details
  A class that stores a BCF project extension metadata.
  */
  class OdBcfProjectExtensionData
  {
  public:
  
    /** \details 
    A smart pointer to a related <link OdBcf::OdBcfProject, BCF project> object.
    */
    OdBcfProjectPtr m_pProject;
  protected:
  
    /** \details 
    A string that contains the project extension schema.
    */
    OdString        m_extensionSchema;
  };

  /** \details
  A class that stores and operates a project extension data.
  */
  class BCF_EXPORT OdBcfProjectExtension : public OdBcfElement, protected OdBcfProjectExtensionData
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfProjectExtension);
    //DOM-IGNORE-END

    /** \details
    Creates a new project extension object with default parameters.
    */
    OdBcfProjectExtension();

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
    Checks whether the project extension instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    /** \details
    Sets the project instance for the project extension.
    \param projectValue [in] A smart pointer to an <link OdBcf::OdBcfProject, OdBcfProject> instance to be set.
    */
    void setProject(const OdBcfProjectPtr &projectValue);

    /** \details
    Retrieves the project instance associated with the project extension.
    \returns A smart pointer to the <link OdBcf::OdBcfProject, OdBcfProject> object that represents the project instance.
    \remarks 
    The project instance returned by the method can be modified in the calling subroutine.
    */
    OdBcfProjectPtr& getProject();

    /** \details
    Retrieves the project instance associated with the project extension.
    \returns A smart pointer to the <link OdBcf::OdBcfProject, OdBcfProject> object that represents the project instance.
    \remarks 
    The project instance returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfProjectPtr& getProject() const;

    /** \details
    Defines whether the project instance associated with the project extension is not initialized.
    \returns true if the project instance is not initialized; otherwise, the method returns false.
    */
    bool isProjectUnset() const;

    /** \details
    Retrieves the name of the project extension schema.
    \returns A string that contains the name of the schema.
    \remarks 
    The string returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getExtensionSchema() const;

    /** \details
    Defines whether the name of the project extension schema is not initialized.
    \returns true if the schema name is not initialized; otherwise, the method returns false.
    */
    bool isExtensionSchemaUnset() const;


    //DOM-IGNORE-BEGIN
  protected:
    /** \details
    Sets a new ExtensionSchema value.
    \param extensionSchemaValue [in] A new value to set.
    */
    void setExtensionSchema(const OdString &extensionSchemaValue);

    /** \details
    Retrieves ExtensionSchema while allowing changes.
    \returns ExtensionSchema value.
    */
    OdString& getExtensionSchema();

    /** \details 
    An assignment operator for the BCF project extension class that associates specified data with the project extension object.
    \param val [in] An <link OdBcf::OdBcfProjectExtensionData, OdBcfProjectExtensionData> object that contains data that represents the right-hand operand of the assignment operation.
    \returns The reference to the project extension object modified by the assignment operation.
    */
    OdBcfProjectExtension& operator = (const OdBcfProjectExtensionData& val);

    friend OdBcfSession;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfProjectExtension, OdBcfProjectExtension> object.
  */
  typedef OdSmartPtr<OdBcfProjectExtension> OdBcfProjectExtensionPtr;

} //namespace OdBcf

#endif // _BFC_PROJECT_EXTENSION_H
