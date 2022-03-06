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

#ifndef _BFC_TOPIC_H
#define _BFC_TOPIC_H

#include "BcfCommon.h"

#include "SharedPtr.h"
#include "StringArray.h"
#include "OdGUID.h"

#include "BcfElement.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfTimeStamp;
  typedef OdSmartPtr<OdBcfTimeStamp> OdBcfTimeStampPtr;

  class OdBcfBimSnippet;
  typedef OdSmartPtr<OdBcfBimSnippet> OdBcfBimSnippetPtr;

  class OdBcfDocumentReference;
  
  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfDocumentReference, OdBcfDocumentReference> object.
  */
  typedef OdSmartPtr<OdBcfDocumentReference> OdBcfDocumentReferencePtr;
  
  /** \details 
  A data type that represents an array of smart pointers to <link OdBcf::OdBcfDocumentReference, OdBcfDocumentReference> objects.
  */
  typedef OdArray<OdBcfDocumentReferencePtr> OdBcfDocumentReferenceArray;

  class OdBcfGUIDAttribute;
  typedef OdSmartPtr<OdBcfGUIDAttribute> OdBcfGUIDAttributePtr;
  
  /** \details 
  A data type that represents an array of smart pointers to <link OdBcf::OdBcfGUIDAttribute, OdBcfGUIDAttribute> objects.
  */
  typedef OdArray<OdBcfGUIDAttributePtr> OdBcfGUIDAttributeArray;

  class OdBcfSession;

  /** \details
  A class that stores a BCF topic metadata.
  */
  class OdBcfTopicData
  {
  public:
    /** \details 
    A string array that contains reference links to the topic.
    */
    OdStringArray               m_referenceLink;
    
    /** \details 
    A string that contains the topic's title.
    */
    OdString                    m_title;
    
    /** \details 
    A string that contains the topic's priority value.
    */
    OdString                    m_priority;

    /** \details 
    The topic's index value.
    */    
    OdInt32                     m_index;
    
    /** \details 
    A string array that contains the topic's labels.
    */
    OdStringArray               m_labels;
    
    /** \details 
    A smart pointer to the timestamp object that contains the topic's due date.
    */
    OdBcfTimeStampPtr           m_pDueDate;
    
    /** \details 
    A string that contains the object the topic is assigned to.
    */
    OdString                    m_assignedTo;
    
    /** \details 
    A string that contains the topic's stage name.
    */
    OdString                    m_stage;
    
    /** \details 
    A string that contains the topic's description.
    */
    OdString                    m_description;
    
    /** \details 
    A smart pointer to the topic's BIM snippet object.
    */
    OdBcfBimSnippetPtr          m_pBimSnippet;
    
    /** \details 
    A string that contains the topic's type.
    */
    OdString                    m_topicType;
    
    /** \details 
    A string that contains the topic's status.
    */
    OdString                    m_topicStatus;
  protected:
  
    /** \details 
    A smart pointer to a timestamp object that contains the date and time of the topic creation.
    */
    OdBcfTimeStampPtr           m_pCreationDate;
    
    /** \details 
    A string that contains the topic's author.
    */
    OdString                    m_creationAuthor;
    
    /** \details 
    A smart pointer to a timestamp object that contains the date and time of the topic modification.
    */
    OdBcfTimeStampPtr           m_pModifiedDate;
    
    /** \details 
    A string that contains the name of the author that modified the topic.
    */
    OdString                    m_modifiedAuthor;
    
    /** \details 
    An array of smart pointers to document references, which are related to the topic.
    */
    OdBcfDocumentReferenceArray m_documentReference;
    
    /** \details 
    An array of smart pointers to globally unique identifiers of related topics.
    */
    OdBcfGUIDAttributeArray     m_relatedTopic;
    
    /** \details 
    A globally unique identifier of the topic.
    */
    OdGUID                      m_guid;
  };

  /** \details
  A class that stores and operates a topic data.
  */
  class BCF_EXPORT OdBcfTopic : public OdBcfElement, protected OdBcfTopicData
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfTopic);
    //DOM-IGNORE-END

    /** \details
    Creates a new topic object with default parameters.
    */
    OdBcfTopic();

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
    Checks whether the topic instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    /** \details
    Sets an array of reference links for the topic object.
    \param referenceLinkValue [in] A string array that contains reference links.
    */
    void setReferenceLink(const OdStringArray &referenceLinkValue);

    /** \details
    Retrieves the array of reference links related to the topic object.
    \returns An array of strings that contains the links.
    \remarks 
    The array returned by the method can be modified in the calling subroutine.
    */
    OdStringArray& getReferenceLink();

    /** \details
    Retrieves the array of reference links related to the topic object.
    \returns An array of strings that contains the links.
    \remarks 
    The array returned by the method can't be modified in the calling subroutine.
    */
    const OdStringArray& getReferenceLink() const;

    /** \details
    Defines whether the array of reference links associated with the topic object is not initialized.
    \returns true if the reference links array is not initialized; otherwise, the method returns false.
    */
    bool isReferenceLinkUnset() const;

    /** \details
    Sets the title of the topic object.
    \param titleValue [in] A string array that contains the title text.
    */
    void setTitle(const OdString &titleValue);

    /** \details
    Retrieves the topic title.
    \returns A string that contains the title text.
    \remarks 
    The title text returned by the method can be modified in the calling subroutine.
    */
    OdString& getTitle();

    /** \details
    Retrieves the topic title.
    \returns A string that contains the title text.
    \remarks 
    The title text returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getTitle() const;

    /** \details
    Defines whether the title of the topic object is not initialized.
    \returns true if the title is not initialized; otherwise, the method returns false.
    */
    bool isTitleUnset() const;

    /** \details
    Sets the priority of the topic object.
    \param priorityValue [in] A string array that contains the priority value to be set.
    */
    void setPriority(const OdString &priorityValue);

    /** \details
    Retrieves the topic priority.
    \returns A string that contains the priority value.
    \remarks 
    The priority value returned by the method can be modified in the calling subroutine.
    */
    OdString& getPriority();

    /** \details
    Retrieves the topic priority.
    \returns A string that contains the priority value.
    \remarks 
    The priority value returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getPriority() const;

    /** \details
    Defines whether the priority value of the topic object is not initialized.
    \returns true if the priority value is not initialized; otherwise, the method returns false.
    */
    bool isPriorityUnset() const;

    /** \details
    Sets the index of the topic object.
    \param indexValue [in] A 32-bit integer value that represents the index to be set.
    */
    void setIndex(const OdInt32 &indexValue);

    /** \details
    Retrieves the topic index.
    \returns A 32-bit integer value that represents the index.
    \remarks 
    The index value returned by the method can be modified in the calling subroutine.
    */
    OdInt32& getIndex();

    /** \details
    Retrieves the topic index.
    \returns A 32-bit integer value that represents the index.
    \remarks 
    The index value returned by the method can't be modified in the calling subroutine.
    */
    const OdInt32& getIndex() const;

    /** \details
    Defines whether the topic index is not initialized.
    \returns true if the index value is not initialized; otherwise, the method returns false.
    */
    bool isIndexUnset() const;

    /** \details
    Sets the topic labels.
    \param labelsValue [in] An array of strings, which contain the label texts.
    */
    void setLabels(const OdStringArray &labelsValue);

    /** \details
    Retrieves the topic labels.
    \returns An array of strings, which contain label texts.
    \remarks 
    The array returned by the method can be modified in the calling subroutine.
    */
    OdStringArray& getLabels();

    /** \details
    Retrieves the topic labels.
    \returns An array of strings, which contain label texts.
    \remarks 
    The array returned by the method can't be modified in the calling subroutine.
    */
    const OdStringArray& getLabels() const;

    /** \details
    Defines whether the topic labels are not initialized.
    \returns true if the string array that contains strings with label texts is not initialized; otherwise, the method returns false.
    */
    bool isLabelsUnset() const;

    /** \details
    Sets a new due date for the topic object.
    \param dueDateValue [in] A smart pointer to the <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> object that contains the due date to be set.
    */
    void setDueDate(const OdBcfTimeStampPtr &dueDateValue);

    /** \details
    Retrieves the topic due date.
    \returns A smart pointer to the <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> object that contains the due date.
    \remarks 
    The timestamp object returned by the method can be modified in the calling subroutine.
    */
    OdBcfTimeStampPtr& getDueDate();

    /** \details
    Retrieves the topic due date.
    \returns A smart pointer to the <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> object that contains the due date.
    \remarks 
    The timestamp object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfTimeStampPtr& getDueDate() const;

    /** \details
    Defines whether the topic due date is not initialized.
    \returns true if the due date is not initialized; otherwise, the method returns false.
    */
    bool isDueDateUnset() const;

    /** \details
    Sets a new value of the AssignedTo property of the topic object.
    \param assignedToValue [in] A string that contains AssignedTo property value to be set.
    */
    void setAssignedTo(const OdString &assignedToValue);

    /** \details
    Retrieves the topic's AssignedTo property value.
    \returns A string that contains the AssignedTo property value.
    \remarks 
    The property value returned by the method can be modified in the calling subroutine.
    */
    OdString& getAssignedTo();

    /** \details
    Retrieves the topic's AssignedTo property value.
    \returns A string that contains the AssignedTo property value.
    \remarks 
    The property value returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getAssignedTo() const;

    /** \details
    Defines whether the topic's AssignedTo property is not initialized.
    \returns true if the property value is not initialized; otherwise, the method returns false.
    */
    bool isAssignedToUnset() const;

    /** \details
    Sets a new value of the Stage property for the topic object.
    \param stageValue [in] A string that contains a new stage value to be set.
    */
    void setStage(const OdString &stageValue);

    /** \details
    Retrieves the topic's Stage property value.
    \returns A string that contains the Stage property value.
    \remarks 
    The property value returned by the method can be modified in the calling subroutine.
    */
    OdString& getStage();

    /** \details
    Retrieves the topic's Stage property value.
    \returns A string that contains the Stage property value.
    \remarks 
    The property value returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getStage() const;
    
    /** \details
    Defines whether the topic's Stage property is not initialized.
    \returns true if the property value is not initialized; otherwise, the method returns false.
    */
    bool isStageUnset() const;

    /** \details
    Sets the topic description.
    \param descriptionValue [in] A string that contains the new description to be set.
    */
    void setDescription(const OdString &descriptionValue);

    /** \details
    Retrieves the topic description.
    \returns A string that contains the description.
    \remarks 
    The description returned by the method can be modified in the calling subroutine.
    */
    OdString& getDescription();

    /** \details
    Retrieves the topic description.
    \returns A string that contains the description.
    \remarks 
    The description returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getDescription() const;

    /** \details
    Defines whether the topic description is not initialized.
    \returns true if the description is not initialized; otherwise, the method returns false.
    */
    bool isDescriptionUnset() const;

    /** \details
    Sets a new BimSnippet object of the topic.
    \param bimSnippetValue [in] A smart pointer to an <link OdBcf::OdBcfBimSnippet, OdBcfBimSnippet> object to be set.
    */
    void setBimSnippet(const OdBcfBimSnippetPtr &bimSnippetValue);

    /** \details
    Retrieves the <link OdBcf::OdBcfBimSnippet, OdBcfBimSnippet> object associated with the topic.
    \returns A smart pointer to the <link OdBcf::OdBcfBimSnippet, OdBcfBimSnippet> object.
    \remarks 
    The <link OdBcf::OdBcfBimSnippet, OdBcfBimSnippet> object returned by the method can be modified in the calling subroutine.
    */
    OdBcfBimSnippetPtr& getBimSnippet();

    /** \details
    Retrieves the <link OdBcf::OdBcfBimSnippet, OdBcfBimSnippet> object associated with the topic.
    \returns A smart pointer to the <link OdBcf::OdBcfBimSnippet, OdBcfBimSnippet> object.
    \remarks 
    The <link OdBcf::OdBcfBimSnippet, OdBcfBimSnippet> object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfBimSnippetPtr& getBimSnippet() const;

    /** \details
    Defines whether the <link OdBcf::OdBcfBimSnippet, OdBcfBimSnippet> object is not initialized.
    \returns true if the <link OdBcf::OdBcfBimSnippet, OdBcfBimSnippet> object is not initialized; otherwise, the method returns false.
    */
    bool isBimSnippetUnset() const;

    /** \details
    Sets the type of the topic.
    \param topicTypeValue [in] A string that contains the type name.
    */
    void setTopicType(const OdString &topicTypeValue);

    /** \details
    Retrieves the topic type.
    \returns A string that contains the topic type name.
    \remarks 
    The topic type name returned by the method can be modified in the calling subroutine.
    */
    OdString& getTopicType();

    /** \details
    Retrieves the topic type.
    \returns A string that contains the topic type name.
    \remarks 
    The topic type name returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getTopicType() const;

    /** \details
    Defines whether the topic type is not initialized.
    \returns true if the topic type is not initialized; otherwise, the method returns false.
    */
    bool isTopicTypeUnset() const;

    /** \details
    Sets the topic status.
    \param topicStatusValue [in] A string that contains the topic status to be set.
    */
    void setTopicStatus(const OdString &topicStatusValue);

    /** \details
    Retrieves the topic status.
    \returns A string that contains the topic status value.
    \remarks 
    The topic status value returned by the method can be modified in the calling subroutine.
    */
    OdString& getTopicStatus();

    /** \details
    Retrieves the topic status.
    \returns A string that contains the topic status value.
    \remarks 
    The topic status value returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getTopicStatus() const;

    /** \details
    Defines whether the topic status value is not initialized.
    \returns true if the topic status value is not initialized; otherwise, the method returns false.
    */
    bool isTopicStatusUnset() const;


    /** \details
    Retrieves the topic creation date.
    \returns A smart pointer to an <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> object that contains the creation date.
    \remarks 
    The timestamp object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfTimeStampPtr& getCreationDate() const;

    /** \details
    Defines whether the topic creation date is not initialized.
    \returns true if the topic creation date is not initialized; otherwise, the method returns false.
    */
    bool isCreationDateUnset() const;

    /** \details
    Retrieves the information about an author that has created the topic.
    \returns A string that contains data about the creator of the topic.
    \remarks 
    The string returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getCreationAuthor() const;

    /** \details
    Defines whether the data about the author that has created the topic is not initialized.
    \returns true if the author data is not initialized; otherwise, the method returns false.
    */
    bool isCreationAuthorUnset() const;

    /** \details
    Retrieves the date of the last modification of the topic.
    \returns A smart pointer to an <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> object that contains the date of the topic modification.
    \remarks 
    The timestamp object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfTimeStampPtr& getModifiedDate() const;

    /** \details
    Defines whether the topic modification date is not initialized.
    \returns true if the modification date is not initialized; otherwise, the method returns false.
    */
    bool isModifiedDateUnset() const;

    /** \details
    Retrieves the information about an author that has modified the topic.
    \returns A string that contains data about the author that has modified the topic.
    \remarks 
    The string returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getModifiedAuthor() const;

    /** \details
    Defines whether the data about the author that has modified the topic is not initialized.
    \returns true if the data about the author of the modification is not initialized; otherwise, the method returns false.
    */
    bool isModifiedAuthorUnset() const;

    /** \details
    Retrieves the array of documents referenced within the topic.
    \returns An array of smart pointers to <link OdBcf::OdBcfDocumentReference, OdBcfDocumentReference>  objects. 
    \remarks 
    The array returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfDocumentReferenceArray& getDocumentReference() const;

    /** \details
    Defines whether the array of documents referenced within the topic is not initialized.
    \returns true if the document references array is not initialized; otherwise, the method returns false.
    */
    bool isDocumentReferenceUnset() const;

    /** \details
    Retrieves the array of related topics for the topic.
    \returns An array of smart pointers to <link OdBcf::OdBcfGUIDAttribute, OdBcfGUIDAttribute>  objects that contains the related topics. 
    \remarks 
    The array returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfGUIDAttributeArray& getRelatedTopic() const;

    /** \details
    Defines whether the array of related topics is not initialized.
    \returns true if the array of related topics is not initialized; otherwise, the method returns false.
    */
    bool isRelatedTopicUnset() const;

    /** \details
    Retrieves the global unique identifier (GUID) of the topic.
    \returns An <exref target="https://docs.opendesign.com/tkernel/OdGUID.html">OdGUID</exref> object that contains the topic GUID.
    \remarks 
    The GUID returned by the method can't be modified in the calling subroutine.
    */
    const OdGUID& getGuid() const;

    /** \details
    Defines whether the global unique identifier (GUID) of the topic is not initialized.
    \returns true if the GUID is not initialized; otherwise, the method returns false.
    */
    bool isGuidUnset() const;


    //DOM-IGNORE-BEGIN
  protected:
    /** \details
    Sets the topic creation date.
    \param creationDateValue [in] A smart pointer to an <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> object that contains the creation date to be set.
    */
    void setCreationDate(const OdBcfTimeStampPtr &creationDateValue);

    /** \details
    Sets the data about the creator of the topic.
    \param creationAuthorValue [in] A string that contains the data about the topic creator.
    */
    void setCreationAuthor(const OdString &creationAuthorValue);

    /** \details
    Sets the date of the last modification of the topic
    \param modifiedDateValue [in] A smart pointer to an <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> object that contains the date of the last topic modification.
    */
    void setModifiedDate(const OdBcfTimeStampPtr &modifiedDateValue);

    /** \details
    Sets the data about the author of the last modification of the topic.
    \param modifiedAuthorValue [in] A string that contains the data about the last modification author.
    */
    void setModifiedAuthor(const OdString &modifiedAuthorValue);

    /** \details
    Sets a new array of referenced documents for the topic.
    \param documentReferenceValue [in] An array of smart pointers to <link OdBcf::OdBcfDocumentReference, OdBcfDocumentReference> objects to be set.
    */
    void setDocumentReference(const OdBcfDocumentReferenceArray &documentReferenceValue);

    /** \details
    Sets an array of related topics.
    \param relatedTopicValue [in] An array of smart pointers to <link OdBcf::OdBcfGUIDAttribute, OdBcfGUIDAttribute> objects that represents the related topics.
    */
    void setRelatedTopic(const OdBcfGUIDAttributeArray &relatedTopicValue);

    /** \details
    Sets the global unique identifier of the topic (GUID).
    \param guidValue [in] An <exref target="https://docs.opendesign.com/tkernel/OdGUID.html">OdGUID</exref> object that contains the GUID for the topic to be set.
    */
    void setGuid(const OdGUID &guidValue);

    /** \details
    Retrieves the topic creation date.
    \returns A smart pointer to an <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> object that contains the creation date.
    \remarks 
    The timestamp object returned by the method can be modified in the calling subroutine.
    */
    OdBcfTimeStampPtr& getCreationDate();

    /** \details
    Retrieves the information about an author that has created the topic.
    \returns A string that contains data about the creator of the topic.
    \remarks 
    The string returned by the method can be modified in the calling subroutine.
    */
    OdString& getCreationAuthor();

    /** \details
    Retrieves the date of the last modification of the topic.
    \returns A smart pointer to an <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> object that contains the date of the topic modification.
    \remarks 
    The timestamp object returned by the method can be modified in the calling subroutine.
    */
    OdBcfTimeStampPtr& getModifiedDate();

    /** \details
    Retrieves the information about an author that has modified the topic.
    \returns A string that contains data about the author that has modified the topic.
    \remarks 
    The string returned by the method can be modified in the calling subroutine.
    */
    OdString& getModifiedAuthor();

    /** \details
    Retrieves the array of documents referenced within the topic.
    \returns An array of smart pointers to <link OdBcf::OdBcfDocumentReference, OdBcfDocumentReference>  objects. 
    \remarks 
    The array returned by the method can be modified in the calling subroutine.
    */
    OdBcfDocumentReferenceArray& getDocumentReference();

    /** \details
    Retrieves the array of related topics for the topic.
    \returns An array of smart pointers to <link OdBcf::OdBcfGUIDAttribute, OdBcfGUIDAttribute>  objects that contains the related topics. 
    \remarks 
    The array returned by the method can't be modified in the calling subroutine.
    */
    OdBcfGUIDAttributeArray& getRelatedTopic();

    /** \details
    Retrieves the global unique identifier (GUID) of the topic.
    \returns An <exref target="https://docs.opendesign.com/tkernel/OdGUID.html">OdGUID</exref> object that contains the topic GUID.
    \remarks 
    The GUID returned by the method can be modified in the calling subroutine.
    */
    OdGUID& getGuid();


    /** \details
    An assignment operator for a BCF topic object.
    \param val [in] Another BCF topic object that should be assigned (the right-hand operand).
    \returns A reference to the topic object after the modification by the assignment operator.
    */
    OdBcfTopic& operator = (const OdBcfTopicData& val);

    friend OdBcfSession;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfTopic, OdBcfTopic> object.
  */
  typedef OdSmartPtr<OdBcfTopic> OdBcfTopicPtr;

  /** \details
   A data type that represents an ODA array of <link OdBcf::OdBcfTopicPtr, OdBcfTopicPtr> objects.
   */
  typedef OdArray<OdBcfTopicPtr> OdBcfTopicArray;

} //namespace OdBcf

#endif // _BFC_TOPIC_H
