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

#ifndef _BFC_MARKUP_H
#define _BFC_MARKUP_H

#include "BcfCommon.h"
#include "OdArray.h"

#include "BcfElement.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfHeader;
  typedef OdSmartPtr<OdBcfHeader> OdBcfHeaderPtr;

  class OdBcfTopic;
  typedef OdSmartPtr<OdBcfTopic> OdBcfTopicPtr;

  class OdBcfComment;
  typedef OdSmartPtr<OdBcfComment> OdBcfCommentPtr;
  
  /** \details 
  A data type that represents an array of smart pointers to <link OdBcf::OdBcfComment, OdBcfComment> objects.
  */
  typedef OdArray<OdBcfCommentPtr> OdBcfCommentArray;

  class OdBcfViewPoint;
  typedef OdSmartPtr<OdBcfViewPoint> OdBcfViewPointPtr;
  typedef OdArray<OdBcfViewPointPtr> OdBcfViewPointArray;

  /** \details
  A class that stores and operates a markup data within the BCF format.
  */
  class BCF_EXPORT OdBcfMarkup : public OdBcfElement
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfMarkup);
    //DOM-IGNORE-END

    /** \details
    Creates a new markup object.
    \param pTopic     [in] A smart pointer to the topic of the markup.
    \param pHeader    [in] A smart pointer to the header of the markup.
    \param comment    [in] An array of smart pointers to comments assigned with the markup.
    \param viewpoints [in] An array of smart pointers to viewpoints assigned with the markup.
    \returns A smart pointer to the created <link OdBcf::OdBcfMarkup, OdBcfMarkup> instance.
    */
    static OdSmartPtr<OdBcfMarkup> createObject(
      const OdBcfTopicPtr       &pTopic,
      const OdBcfHeaderPtr      &pHeader = OdBcfHeaderPtr(),
      const OdBcfCommentArray   &comment = OdBcfCommentArray(),
      const OdBcfViewPointArray &viewpoints = OdBcfViewPointArray()); 
      
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
    Checks whether the markup instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    /** \details
    Sets the header object for the markup instance.
    \param headerValue [in] A smart pointer to the <link OdBcf::OdBcfHeader, OdBcfHeader> object to be set.
    */
    void setHeader(const OdBcfHeaderPtr &headerValue);

    /** \details
    Retrieves the header object of the markup instance.
    \returns A smart pointer to the <link OdBcf::OdBcfHeader, OdBcfHeader> object.
    \remarks 
    The header object returned by the method can be modified in the calling subroutine.
    */
    OdBcfHeaderPtr& getHeader();

    /** \details
    Retrieves the header object of the markup instance.
    \returns A smart pointer to the <link OdBcf::OdBcfHeader, OdBcfHeader> object.
    \remarks 
    The header object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfHeaderPtr& getHeader() const;

    /** \details
    Defines whether the markup header object is not initialized.
    \returns true if the header object is not initialized; otherwise, the method returns false.
    */
    bool isHeaderUnset() const;

    /** \details
    Sets the markup's topic.
    \param topicValue [in] A smart pointer to the <link OdBcf::OdBcfTopic, OdBcfTopic> object to be set.
    */
    void setTopic(const OdBcfTopicPtr &topicValue);

    /** \details
    Retrieves the topic object of the markup instance.
    \returns A smart pointer to the <link OdBcf::OdBcfTopic, OdBcfTopic> object.
    \remarks 
    The topic object returned by the method can be modified in the calling subroutine.
    */
    OdBcfTopicPtr& getTopic();

    /** \details
    Retrieves the topic object of the markup instance.
    \returns A smart pointer to the <link OdBcf::OdBcfTopic, OdBcfTopic> object.
    \remarks 
    The topic object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfTopicPtr& getTopic() const;

    /** \details
    Defines whether the markup topic object is not initialized.
    \returns true if the topic object is not initialized; otherwise, the method returns false.
    */
    bool isTopicUnset() const;

    /** \details
    Sets the markup's comment.
    \param commentValue [in] A smart pointer to the <link OdBcf::OdBcfComment, OdBcfComment> object to be set.
    */
    void setComment(const OdBcfCommentArray &commentValue);

    /** \details
    Retrieves the comment of the markup instance.
    \returns A smart pointer to the <link OdBcf::OdBcfComment, OdBcfComment> object.
    \remarks 
    The comment object returned by the method can be modified in the calling subroutine.
    */
    OdBcfCommentArray& getComment();

    /** \details
    Retrieves the comment of the markup instance.
    \returns A smart pointer to the <link OdBcf::OdBcfComment, OdBcfComment> object.
    \remarks 
    The comment object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfCommentArray& getComment() const;

    /** \details
    Defines whether the markup comment is not initialized.
    \returns true if the comment is not initialized; otherwise, the method returns false.
    */
    bool isCommentUnset() const;

    /** \details
    Sets the markup's viewpoints.
    \param viewpointsValue [in] An array of smart pointers to <link OdBcf::OdBcfViewPoint, OdBcfViewPoint> objects to be set.
    */
    void setViewpoints(const OdBcfViewPointArray &viewpointsValue);

    /** \details
    Retrieves the viewpoints of the markup instance.
    \returns An array of smart pointers to <link OdBcf::OdBcfViewPoint, OdBcfViewPoint> objects.
    \remarks 
    The array returned by the method can be modified in the calling subroutine.
    */
    OdBcfViewPointArray& getViewpoints();

    /** \details
    Retrieves the viewpoints of the markup instance.
    \returns An array of smart pointers to <link OdBcf::OdBcfViewPoint, OdBcfViewPoint> objects.
    \remarks 
    The array returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfViewPointArray& getViewpoints() const;

    /** \details
    Defines whether the array of markup viewpoints is not initialized.
    \returns true if the viewpoints array is not initialized; otherwise, the method returns false.
    */
    bool isViewpointsUnset() const;


    //DOM-IGNORE-BEGIN
  protected:
    OdBcfHeaderPtr      m_pHeader;
    OdBcfTopicPtr       m_pTopic;
    OdBcfCommentArray   m_comment;
    OdBcfViewPointArray m_viewpoints;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfMarkup, OdBcfMarkup> object.
  */
  typedef OdSmartPtr<OdBcfMarkup> OdBcfMarkupPtr;

} //namespace OdBcf

#endif // _BFC_MARKUP_H
