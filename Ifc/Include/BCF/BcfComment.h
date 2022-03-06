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

#ifndef _BFC_COMMENT_H
#define _BFC_COMMENT_H

#include "BcfCommon.h"
#include "OdGUID.h"

#include "BcfElement.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfTimeStamp;
  typedef OdSmartPtr<OdBcfTimeStamp> OdBcfTimeStampPtr;

  class OdBcfGUIDAttribute;
  typedef OdSmartPtr<OdBcfGUIDAttribute> OdBcfGUIDAttributePtr;

  class OdBcfSession;

  /** \details
  A class that stores and operates comments data.
  */
  class BCF_EXPORT OdBcfComment : public OdBcfElement
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfComment);
    //DOM-IGNORE-END

    /** \details
    Creates a new commentary object with default parameters.
    */
    OdBcfComment();

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
    Checks whether the commentary instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    /** \details
    Retrieves the comment's date.
    \returns A smart pointer to the <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> object that contains the date.
    \remarks 
    The timestamp object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfTimeStampPtr& getDate() const;

    /** \details
    Defines whether the comment's date is not initialized.
    \returns true if the date is not initialized; otherwise, the method returns false.
    */
    bool isDateUnset() const;

    /** \details
    Retrieves the comment's author.
    \returns A string that contains information about the comment's author.
    \remarks 
    The string with information about the author returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getAuthor() const;

    /** \details
    Defines whether the comment's author is not initialized.
    \returns true if the author is not initialized; otherwise, the method returns false.
    */
    bool isAuthorUnset() const;

    /** \details
    Sets a new comment's text.
    \param commentValue [in] A string that contains the new comment text.
    */
    void setComment(const OdString &commentValue);

    /** \details
    Retrieves the comment text.
    \returns A string that contains the comment text.
    \remarks 
    The comment text returned by the method can be modified in the calling subroutine.
    */
    OdString& getComment();

    /** \details
    Retrieves the comment text.
    \returns A string that contains the comment text.
    \remarks 
    The comment text returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getComment() const;

    /** \details
    Defines whether the comment text is not initialized.
    \returns true if the comment text is not initialized; otherwise, the method returns false.
    */
    bool isCommentUnset() const;

    /** \details
    Sets a new viewpoint value.
    \param viewpointValue [in] A smart pointer to the <link OdBcf::OdBcfGUIDAttribute, OdBcfGUIDAttribute> object that contains the new viewpoint value.
    */
    void setViewpoint(const OdBcfGUIDAttributePtr &viewpointValue);

    /** \details
    Retrieves the comment's viewpoint value.
    \returns A smart pointer to the <link OdBcf::OdBcfGUIDAttribute, OdBcfGUIDAttribute> object that represents the view point value.
    \remarks 
    The viewpoint value returned by the method can be modified in the calling subroutine.
    */
    OdBcfGUIDAttributePtr& getViewpoint();

    /** \details
    Retrieves the comment's viewpoint value.
    \returns A smart pointer to the <link OdBcf::OdBcfGUIDAttribute, OdBcfGUIDAttribute> object that represents the view point value.
    \remarks 
    The viewpoint value returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfGUIDAttributePtr& getViewpoint() const;

    /** \details
    Defines whether the comment viewpoint value is not initialized.
    \returns true if the viewpoint value is not initialized; otherwise, the method returns false.
    */
    bool isViewpointUnset() const;

    /** \details
    Sets a new date of the last comment text modification.
    \param modifiedDateValue [in] A smart pointer to the <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> object that contains the new date of modification.
    */
    void setModifiedDate(const OdBcfTimeStampPtr &modifiedDateValue);

    /** \details
    Retrieves the date of the last modification of the comment text.
    \returns A smart pointer to the <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> object that contains the date of the last comment text modification.
    \remarks 
    The timestamp object returned by the method can be modified in the calling subroutine.
    */
    OdBcfTimeStampPtr& getModifiedDate();

    /** \details
    Retrieves the date of the last modification of the comment text.
    \returns A smart pointer to the <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> object that contains the date of the last comment text modification.
    \remarks 
    The timestamp object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfTimeStampPtr& getModifiedDate() const;

    /** \details
    Defines whether the date of the last comment text modification is not initialized.
    \returns true if the date of the last modification is not initialized; otherwise, the method returns false.
    */
    bool isModifiedDateUnset() const;

    /** \details
    Sets a new author of the last comment text modification.
    \param modifiedAuthorValue [in] A string that contains information about the author of the last comment text modification.
    */
    void setModifiedAuthor(const OdString &modifiedAuthorValue);

    /** \details
    Retrieves the information about the author of the last modification of the comment text.
    \returns A string that contains the information about the author of the last comment text modification.
    \remarks 
    The string returned by the method can be modified in the calling subroutine.
    */
    OdString& getModifiedAuthor();

    /** \details
    Retrieves the information about the author of the last modification of the comment text.
    \returns A string that contains the information about the author of the last comment text modification.
    \remarks 
    The string returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getModifiedAuthor() const;

    /** \details
    Defines whether the information about the author of the last comment text modification is not initialized.
    \returns true if the author of the last modification is not initialized; otherwise, the method returns false.
    */
    bool isModifiedAuthorUnset() const;

    /** \details
    Retrieves the global unique identifier (GUID) of the comment object.
    \returns An <exref target="https://docs.opendesign.com/tkernel/OdGUID.html">OdGUID</exref> object that contains the GUID value.
    \remarks 
    The GUID returned by the method can't be modified in the calling subroutine.
    */
    const OdGUID& getGuid() const;

    /** \details
    Defines whether the global unique identifier (GUID) of the comment object is not initialized.
    \returns true if the GUID is not initialized; otherwise, the method returns false.
    */
    bool isGuidUnset() const;


    //DOM-IGNORE-BEGIN
  protected:
    OdBcfTimeStampPtr     m_pDate;
    OdString              m_author;
    OdString              m_comment;
    OdBcfGUIDAttributePtr m_pViewpoint;
    OdBcfTimeStampPtr     m_pModifiedDate;
    OdString              m_modifiedAuthor;
    OdGUID                m_guid;

    /** \details
    Retrieves the creation date of the comment object.
    \returns A smart pointer to the <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> object that represents the creation date.
    \remarks 
    The timestamp object returned by the method can be modified in the calling subroutine.
    */
    OdBcfTimeStampPtr& getDate();

    /** \details
    Retrieves the information about the author of the comment object.
    \returns A string that contains information about the author of the comment object.
    \remarks 
    The string returned by the method can be modified in the calling subroutine.
    */
    OdString& getAuthor();

    /** \details
    Retrieves the global unique identifier (GUID) of the comment object.
    \returns An <exref target="https://docs.opendesign.com/tkernel/OdGUID.html">OdGUID</exref> object that contains the comment GUID.
    \remarks 
    The GUID returned by the method can be modified in the calling subroutine.
    */
    OdGUID& getGuid();

    /** \details
    Sets the date of the creation of the comment object.
    \param dateValue [in] A new value to set represented with the <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> object.
    */
    void setDate(const OdBcfTimeStampPtr &dateValue);

    /** \details
    Sets information about the author of the comment object.
    \param authorValue [in] A string with information about the comment author.
    */
    void setAuthor(const OdString &authorValue);

    /** \details
    Sets the global unique identifier (GUID) for the comment object.
    \param guidValue [in] An <exref target="https://docs.opendesign.com/tkernel/OdGUID.html">OdGUID</exref> object that contains the comment GUID.
    */
    void setGuid(const OdGUID &guidValue);

    friend OdBcfSession;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfComment, OdBcfComment> object.
  */
  typedef OdSmartPtr<OdBcfComment> OdBcfCommentPtr;

} //namespace OdBcf

#endif // _BFC_COMMENT_H
