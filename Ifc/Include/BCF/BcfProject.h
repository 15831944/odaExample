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

#ifndef _BFC_PROJECT_H
#define _BFC_PROJECT_H

#include "BcfCommon.h"

#include "BcfElement.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfSession;

  /** \details
  A class that stores a BCF project data.
  */
  class OdBcfProjectData
  {
  public:
    /** \details 
    A string that contains the BCF project name.
    */
    OdString m_name;
  protected:
  
    /** \details
    A string that contains the BCF project identifier.
    */
    OdString m_projectId;
  };

  /** \details
  A class that stores and operates a BCF project data.
  */
  class BCF_EXPORT OdBcfProject : public OdBcfElement, protected OdBcfProjectData
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfProject);
    //DOM-IGNORE-END

     /** \details
    Creates a new project object with default parameters.
    */
    OdBcfProject();

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
    Checks whether the project instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    /** \details
    Sets the BCF project name.
    \param nameValue [in] A string that contains the project name to be set.
    */
    void setName(const OdString &nameValue);

    /** \details
    Retrieves the BCF project name.
    \returns A string that contains the project name.
    \remarks 
    The string returned by the method can be modified in the calling subroutine.
    */
    OdString& getName();

    /** \details
    Retrieves the BCF project name.
    \returns A string that contains the project name.
    \remarks 
    The string returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getName() const;

    /** \details
    Defines whether the BCF project name is not initialized.
    \returns true if the project name is not initialized; otherwise, the method returns false.
    */
    bool isNameUnset() const;

    /** \details
    Retrieves the project identifier.
    \returns A string that contains the project identifier.
    \remarks 
    The string returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getProjectId() const;

    /** \details
    Defines whether the project identifier is not initialized.
    \returns true if the project identifier is not initialized; otherwise, the method returns false.
    */
    bool isProjectIdUnset() const;


    //DOM-IGNORE-BEGIN
  protected:
    /** \details
    Retrieves ProjectId while allowing changes.
    \returns ProjectId value.
    */
    OdString& getProjectId();

    /** \details
    Sets a new ProjectId value.
    \param projectIdValue [in] A new value to set.
    */
    void setProjectId(const OdString &projectIdValue);

    /** \details 
    An assignment operator for the BCF project class that associates specified project data with the project instance.
    \param val [in] An <link OdBcf::OdBcfProjectData, OdBcfProjectData> object that contains project data that represents the right-hand operand of the assignment operation.
    \returns The reference to the project instance modified by the assignment operation.
    */
    OdBcfProject& operator = (const OdBcfProjectData& val);

    friend OdBcfSession;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfProject, OdBcfProject> object.
  */
  typedef OdSmartPtr<OdBcfProject> OdBcfProjectPtr;

} //namespace OdBcf

#endif // _BFC_PROJECT_H
