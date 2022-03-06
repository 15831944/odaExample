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

#ifndef _BFC_SESSION_H
#define _BFC_SESSION_H

#include "BcfCommon.h"
#include "OdGUID.h"
#include "OdArray.h"
#define STL_USING_MAP
#define STL_USING_UTILITY
#include "OdaSTL.h"

class OdDbHostAppProgressMeter;

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfProjectExtensionData;
  class OdBcfProjectExtension;
  typedef OdSmartPtr<OdBcfProjectExtension> OdBcfProjectExtensionPtr;

  class OdBcfProjectData;
  class OdBcfProject;
  typedef OdSmartPtr<OdBcfProject> OdBcfProjectPtr;

  class OdBcfVersion;
  typedef OdSmartPtr<OdBcfVersion> OdBcfVersionPtr;

  class OdBcfTopicData;
  class OdBcfTopic;
  typedef OdSmartPtr<OdBcfTopic> OdBcfTopicPtr;

  class OdBcfMarkup;
  typedef OdSmartPtr<OdBcfMarkup> OdBcfMarkupPtr;

  class OdBcfViewPoint;
  typedef OdSmartPtr<OdBcfViewPoint> OdBcfViewPointPtr;
  
  /** \details 
  A data type that represents an array of smart pointers to <link OdBcf::OdBcfViewPoint, OdBcfViewPoint> objects.
  */
  typedef OdArray<OdBcfViewPointPtr> OdBcfViewPointArray;

  class OdBcfComponent;
  typedef OdSmartPtr<OdBcfComponent> OdBcfComponentPtr;
  
  /** \details 
  A data type that represents an array of smart pointers to <link OdBcf::OdBcfComponent, OdBcfComponent> objects.
  */
  typedef OdArray<OdBcfComponentPtr> OdBcfComponentArray;

  class OdBcfViewSetupHints;
  typedef OdSmartPtr<OdBcfViewSetupHints> OdBcfViewSetupHintsPtr;

  class OdBcfComponentSelection;
  typedef OdSmartPtr<OdBcfComponentSelection> OdBcfComponentSelectionPtr;

  class OdBcfComponentVisibility;
  typedef OdSmartPtr<OdBcfComponentVisibility> OdBcfComponentVisibilityPtr;

  class OdBcfColor;
  typedef OdSmartPtr<OdBcfColor> OdBcfColorPtr;

  class OdBcfComponentColoring;
  typedef OdSmartPtr<OdBcfComponentColoring> OdBcfComponentColoringPtr;

  class OdBcfComponents;
  typedef OdSmartPtr<OdBcfComponents> OdBcfComponentsPtr;

  class OdBcfBitmapData;
  class OdBcfBitmap;
  typedef OdSmartPtr<OdBcfBitmap> OdBcfBitmapPtr;

  class OdBcfVisualizationInfoData;
  class OdBcfVisualizationInfo;
  typedef OdSmartPtr<OdBcfVisualizationInfo> OdBcfVisualizationInfoPtr;
  
  /** \details 
  A data type that represents an array of smart pointers to <link OdBcf::OdBcfVisualizationInfo, OdBcfVisualizationInfo> objects.
  */
  typedef OdArray<OdBcfVisualizationInfoPtr> OdBcfVisualizationInfoArray;

  class OdBcfTopicFolder;
  typedef OdSmartPtr<OdBcfTopicFolder> OdBcfTopicFolderPtr;
  
  /** \details 
  A data type that represents an array of smart pointers to <link OdBcf::OdBcfTopicFolder, OdBcfTopicFolder> objects.
  */
  typedef OdArray<OdBcfTopicFolderPtr> OdBcfTopicFolderArray;

  class OdBcfArchive;
  typedef OdSmartPtr<OdBcfArchive> OdBcfArchivePtr;
  typedef std::map<OdString, OdBcfArchivePtr> OdBcfArchiveMap;

  class OdBcfDataAccessor;
  typedef OdSmartPtr<OdBcfDataAccessor> OdBcfDataAccessorPtr;

  /** \details
  A class that provides functionality for managing a session for work with BCF data.
  */
  class BCF_EXPORT OdBcfSession : public OdRxObject
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfSession);
    //DOM-IGNORE-END

    /** \details
    Creates a new session object.
    \param author          [in] A string that contains the session author.
    \param authoringToolId [in] A string that contains the identifier of the authoring application used by the author.
    \param pDataAccessor   [in] A smart pointer to a data accessor object.
    \returns A smart pointer to the created <link OdBcf::OdBcfSession, OdBcfSession> instance.
    */
    static OdSmartPtr<OdBcfSession> createObject(
      const OdString &author,
      const OdString &authoringToolId,
      const OdBcfDataAccessorPtr &pDataAccessor = OdBcfDataAccessorPtr());

    //const OdBcfArchiveMap& loadProjects(OdResult *result = NULL);

    /** \details 
    Sets a new session author. 
    \param author [in] A string that contains the session author.
    */
    void setAuthor(const OdString& author);

    /** \details
    Sets a progress meter.
    \param pMeter [in] A pointer to progress meter.
    \returns eOk if the progress meter was successfully set; otherwise, the method returns an appropriate error code.
    */
    OdResult setProgressMeter(OdDbHostAppProgressMeter* pMeter);

    /** \details
    Saves the archive using a specified data accessor object.
    \param projectId     [in] A string that contains the project Id.
    \param fileName      [in] A string that contains the file name to use for the saving.
    \param pDataAccessor [in] A smart pointer to the data accessor object that should be used for the saving.
    \param result        [out] A raw pointer to a value that contains the result of the operation. 
    */
    void saveProject(
      const OdString &projectId, 
      const OdString &fileName = OdString(), 
      OdBcfDataAccessorPtr pDataAccessor = OdBcfDataAccessorPtr(), 
      OdResult *result = NULL);

    /** \details
    Loads an archive using a specified data accessor.
    \param fileName      [in] A string that contains the full file name to load.
    \param pDataAccessor [in] A smart pointer to the data accessor to use for loading.
    \param result        [out] A raw pointer to a value that contains the result of the operation. 
    \returns A string that contains the identifier of the loaded project.
    */
    OdString loadProject(
      const OdString &fileName,
      OdBcfDataAccessorPtr pDataAccessor = OdBcfDataAccessorPtr(),
      OdResult *result = NULL);

    /** \details
    Adds an existing archive object to the session collection.
    \param pArchive [in] A smart pointer to the archive object.
    \param result   [out] A raw pointer to a value that contains the result of the operation. 
    \returns A string that contains the project identifier of the archive object.
    */
    OdString addArchive(const OdBcfArchivePtr &pArchive, OdResult *result = NULL);

    /** \details
    Retrieves an archive with the specified identifier.
    \param projectId [in] A string that contains the project identifier.
    \param result    [out] A raw pointer to a value that contains the result of the operation. 
    \returns A smart pointer to the archive.
    */
    OdBcfArchivePtr getArchive(const OdString &projectId, OdResult *result = NULL);

    /** \details
    Validates the archive with a specified identifier.
    \param projectId [in] A string that contains the project Id.
    \param result    [out] A raw pointer to a value that contains the result of the operation.
    \returns true if the specified archive contains all required data; otherwise the method returns false.
    */
    bool validateArchive(const OdString &projectId, OdResult *result = NULL) const;

    /** \details
    Removes the archive with a specified identifier.
    \param projectId [in] A string that contains the project identifier.
    \param result    [out] A raw pointer to a value that contains the result of the operation.
    \returns A smart pointer to the removed archive.
    */
    OdBcfArchivePtr removeArchive(const OdString &projectId, OdResult *result = NULL);

    /** \details
    Enumerates supported sort orders within the session.
    */
    enum eSortParameter
    {
      /**Sorting by the global unique identifier (GUID).*/
      kSortParameter_Guid = 0,
      /**Sorting by the date of creation.*/
      kSortParameter_CreationDate,
      /**Sorting by the date of the last modification.*/
      kSortParameter_ModifiedDate,
      /**Sorting by the index.*/
      kSortParameter_Index
    };

    /** \details
    Retrieves the topic folders of a specified project.
    \param projectId     [in] A string that contains the project identifier.
    \param sortParameter [in] A sort type for the output topic folders list.
    \param result        [out] A raw pointer to a value that contains the result of the operation.
    \returns An array of smart pointers to topic folder objects.
    */
    OdBcfTopicFolderArray getTopics(const OdString &projectId, eSortParameter sortParameter = kSortParameter_Guid, OdResult *result = NULL);

    /** \details
    Adds an existing topic folder object to a specified project.
    \param projectId    [in] A string that contains the project identifier.
    \param pTopicFolder [in] A smart pointer to the topic folder object.
    \param result       [out] A raw pointer to a value that contains the result of the operation.
    \returns A GUID of the added topic folder object.
    */
    OdGUID addTopicFolder(const OdString &projectId, const OdBcfTopicFolderPtr& pTopicFolder, OdResult *result = NULL);

    /** \details
    Returns an OdGUID of topic folder.
    \param pTopicFolder [in] A smart pointer to the topic folder object.
    \param result       [out] A raw pointer to a value that contains the result of the operation.
    \returns A GUID of the topic folder object.
    */
    static OdGUID getTopicId(const OdBcfTopicFolderPtr& pTopicFolder, OdResult* result = NULL);

    /** \details
    Retrieves the topic folder object with a specified GUID from a specified project.
    \param projectId [in] A string that contains the project identifier.
    \param topicId   [in] A GUID of the topic folder object.
    \param result    [out] A raw pointer to a value that contains the result of the operation.
    \returns A smart pointer to the topic folder object. 
    */
    OdBcfTopicFolderPtr getTopicFolder(const OdString &projectId, const OdGUID &topicId, OdResult *result = NULL);

    /** \details
    Removes a topic folder object with a specified GUID from a specified project.
    \param projectId [in] A string that contains the project identifier.
    \param topicId   [in] A GUID of the topic folder object.
    \param result    [out] A raw pointer to a value that contains the result of the operation.
    */
    void removeTopicFolder(const OdString &projectId, const OdGUID &topicId, OdResult *result = NULL);

    /** \details
    Adds comment to a topic with a specified GUID from a specified project.
    \param projectId [in] A string that contains the project identifier.
    \param topicId   [in] A GUID of the topic folder object.
    \param comment   [in] A string that contains comment text.
    \param result    [out] A raw pointer to a value that contains the result of the operation.
    \remarks
    If you want to get the result of adding the comment, pass a valid pointer to the 
    <exref target="https://docs.opendesign.com/tkernel/OdResult.html">OdResult</exref> value to the method and analyze it after the method call ends. 
    */
    void addComment(const OdString& projectId, const OdGUID& topicId, const OdString& comment, OdResult* result = NULL);

    /** \details
    Edit the comment from the topic with a specified GUID from a specified project.
    \param projectId [in] A string that contains the project identifier.
    \param topicId   [in] A GUID of the topic folder object.
    \param commentId [in] A GUID of the comment.
    \param comment   [in] A string that contains the new comment text.
    \param result    [out] A raw pointer to a value that contains the result of the operation.
    \remarks
    If you want to get the result of editing the comment, pass a valid pointer to the 
    <exref target="https://docs.opendesign.com/tkernel/OdResult.html">OdResult</exref> value to the method and analyze it after the method call ends. 
    */
    void editComment(const OdString& projectId, const OdGUID& topicId, const OdGUID& commentId, const OdString& comment, OdResult* result = NULL);

    /** \details
    Delete the comment from the topic with a specified GUID from a specified project.
    \param projectId [in] A string that contains the project identifier.
    \param topicId   [in] A GUID of the topic folder object.
    \param commentId [in] A GUID of the comment.
    \param result    [out] A raw pointer to a value that contains the result of the operation.
    \remarks
    If you want to get the result of the comment deletion, pass a valid pointer to the 
    <exref target="https://docs.opendesign.com/tkernel/OdResult.html">OdResult</exref> value to the method and analyze it after the method call ends. 
    */
    void deleteComment(const OdString& projectId, const OdGUID& topicId, const OdGUID& commentId, OdResult* result = NULL);

    /** \details
    Adds a screenshot to a specified topic folder object.
    \param projectId [in] A string that contains the project identifier.
    \param topicId   [in] A GUID of the topic folder object.
    \param fileName  [in] A string that contains the file name to use for the saving operation.
    \param data      [in] A pointer to a data buffer that contains the file data.
    \param size      [in] A length of the data buffer that contains the file data.
    \param result    [out] A raw pointer to a value that contains the result of the operation.
    */
    void addScreenshot(
      const OdString &projectId,
      const OdGUID &topicId,
      const OdString &fileName,
      const char *data,
      unsigned int size,
      OdResult *result = NULL);

    /** \details
    Constructs the path to the screenshot of a specified topic.
    \param projectId [in] A string containing project Id.
    \param topicId   [in] A GUID of the topic folder.
    \param fileName  [in] A string that contains the full file name of the screenshot.
    \param result    [out] A raw pointer to a value that contains the result of the operation.
    \returns A string that contains the path to the screenshot.
    \remarks 
    If the file name of the screenshot is not provided (an empty string is passed) the method uses the default screenshot name.
    */
    OdString getScreenshot(const OdString &projectId, const OdGUID &topicId, const OdString &fileName = OdString(), OdResult *result = NULL);

    /** \details
    Creates a new project instance.
    \param pProjectData [in] A aw pointer to an object that contains values for the instance initialization.
    \param result       [out] A raw pointer to a value that contains the result of the operation.
    \returns A smart pointer to the created <link OdBcf::OdBcfProject, OdBcfProject> instance.
    */
    OdBcfProjectPtr createProject(const OdBcfProjectData *pProjectData, OdResult *result = NULL) const;

    /** \details
    Creates a new project extension instance.
    \param pProjectExtensionData [in] A raw pointer to an object that contains values for the instance initialization.
    \param result                [out] A raw pointer to a value that contains the result of the operation.
    \returns A smart pointer to the created <link OdBcf::OdBcfProjectExtension, OdBcfProjectExtension> instance.
    */
    OdBcfProjectExtensionPtr createProjectExtension(const OdBcfProjectExtensionData *pProjectExtensionData, OdResult *result = NULL) const;

    /** \details
    Creates a new version instance.
    \param result [out] A raw pointer to a value that contains the result of the operation.
    \returns A smart pointer to the created <link OdBcf::OdBcfVersion, OdBcfVersion> instance.
    */
    OdBcfVersionPtr createVersion(OdResult *result = NULL) const;

    /** \details
    Creates a new topic instance.
    \param pTopicData [in] A raw pointer to an object that contains values for the instance initialization.
    \param result     [out] A raw pointer to a value that contains the result of the operation.
    \returns A smart pointer to the created <link OdBcf::OdBcfTopic, OdBcfTopic> instance.
    */
    OdBcfTopicPtr createTopic(const OdBcfTopicData *pTopicData, OdResult *result = NULL) const;

    /** \details
    Creates a new view setup hints instance.
    \param result [out] A raw pointer to a value that contains the result of the operation.
    \returns A smart pointer to the created <link OdBcf::OdBcfProject, OdBcfProject> instance.
    */
    OdBcfViewSetupHintsPtr createViewSetupHints(OdResult *result = NULL) const;

    /** \details
    Creates a new component selection instance.
    \param ifcGuids [in] An array of strings that contains GUIDs for the instance initialization.
    \param result   [out] A raw pointer to a value that contains the result of the operation.
    \returns A smart pointer to the created <link OdBcf::OdBcfComponentSelection, OdBcfComponentSelection> instance.
    */
    OdBcfComponentSelectionPtr createComponentSelection(const OdArray<OdString> &ifcGuids, OdResult *result = NULL) const;

    /** \details
    Creates a new component visibility instance.
    \param ifcGuids          [in] An array of strings that contains GUIDs for the instance initialization.
    \param defaultVisibility [in] A flag that determines whether the components are visible by default (if it is equal to true) or hidden (if it is equal to false).
    \param result            [out] A raw pointer to a value that contains the result of the operation.
    \returns A smart pointer to the created <link OdBcf::OdBcfComponentVisibility, OdBcfComponentVisibility> instance.
    */
    OdBcfComponentVisibilityPtr createComponentVisibility(const OdArray<OdString> &ifcGuids, bool defaultVisibility = false, OdResult *result = NULL) const;

    /** \details
    A data type that represents an STD pair containing an array of strings with component GUIDs and a string that represents a color value.
    */
    typedef std::pair<OdArray<OdString>, OdString> ComponentColoring;

    /** \details
    A data type that represents an ODA array of <link OdBcf::OdBcfSession::ComponentColoring, ComponentColoring> objects.
    */
    typedef OdArray<ComponentColoring> ComponentColoringArray;

    /** \details
    Creates a new component coloring instance.
    \param componentColoring [in] An array of ComponentColoring objects for instance initialization.
    \param result            [out] A pointer to variable containing result of operation.
    \returns A smart pointer to the created <link OdBcf::OdBcfSession::ComponentColoring, OdBcfComponentColoring> instance.
    */
    OdBcfComponentColoringPtr createComponentColoring(const ComponentColoringArray &componentColoring, OdResult *result = NULL) const;

    /** \details
    Creates a new bitmap instance.
    \param pBitmapData [in] A pointer to a variable containing initial values for instance initialization.
    \param result      [out] A pointer to variable containing result of operation.
    \returns A smart pointer to the created <link OdBcf::OdBcfBitmap, OdBcfBitmap> instance.
    */
    OdBcfBitmapPtr createBitmap(const OdBcfBitmapData *pBitmapData, OdResult *result = NULL) const;

    /** \details
    Creates a new visualization info instance.
    \param pVisualizationInfoData [in] A pointer to a variable containing initial values for instance initialization.
    \param visInfoFileName        [in] A string containing visualization information file name.
    \param screenshotFileName     [in] A string containing screenshot file name.
    \param pMarkup                [out] A pointer to a existing markup data for visualization information initialization.
    \param result                 [out] A pointer to variable containing result of operation.
    \returns A smart pointer to the created <link OdBcf::OdBcfVisualizationInfo, OdBcfVisualizationInfo> instance.
    */
    OdBcfVisualizationInfoPtr createVisualizationInfo(
      const OdBcfVisualizationInfoData *pVisualizationInfoData, 
      const OdString &visInfoFileName,
      const OdString &screenshotFileName,
      OdBcfMarkupPtr pMarkup,
      OdInt32 viewPointIndex = OdBcf::Utils::getUnset<OdInt32>(),
      OdResult *result = NULL) const;

    /** \details
    Delete the viewpoint from the topic with a specified GUID from a specified project.
    \param projectId   [in] A string that contains the project identifier.
    \param topicId     [in] A GUID of the topic folder object.
    \param viewpointId [in] A GUID of the viewpoint.
    \param result      [out] A raw pointer to a value that contains the result of the operation.
    \remarks
    If you want to get the result of the viewpoint deletion, pass a valid pointer to the
    <exref target="https://docs.opendesign.com/tkernel/OdResult.html">OdResult</exref> value to the method and analyze it after the method call ends.
    */
    void deleteViewpoint(const OdString& projectId, const OdGUID& topicId, const OdGUID& viewpointId, OdResult* result = NULL);

    //DOM-IGNORE-BEGIN
  protected:
    OdString                  m_author;
    OdString                  m_authoringToolId;
    OdBcfDataAccessorPtr      m_pDataAccessor;
    OdBcfArchiveMap           m_archives;
    OdDbHostAppProgressMeter *m_pMeter;

    const OdBcfComponentPtr createComponent(const OdString &ifcGuid) const;
    OdBcfComponentArray createComponents(const OdArray<OdString> &ifcGuids) const;
    OdBcfColorPtr createColor(const OdArray<OdString> &ifcGuids, const OdString &color) const;

    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfSession, OdBcfSession> object.
  */
  typedef OdSmartPtr<OdBcfSession> OdBcfSessionPtr;

} //namespace OdBcf

#endif // _BFC_SESSION_H
