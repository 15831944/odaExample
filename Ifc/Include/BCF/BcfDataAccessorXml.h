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

#ifndef _BFC_TOPIC_PROCESSOR_XML_H
#define _BFC_TOPIC_PROCESSOR_XML_H

#include "BcfCommon.h"
#define STL_USING_MAP
#include "OdaSTL.h"

#include "BcfDataAccessor.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfArchiveFolder;
  typedef OdSmartPtr<OdBcfArchiveFolder> OdBcfArchiveFolderPtr;
  typedef std::map<OdString, OdBcfArchiveFolderPtr> OdBcfArchiveFolderMap;

  class OdBcfVersion;
  typedef OdSmartPtr<OdBcfVersion> OdBcfVersionPtr;

  class OdBcfProjectExtension;
  typedef OdSmartPtr<OdBcfProjectExtension> OdBcfProjectExtensionPtr;

  class OdBcfTopicFolder;
  typedef OdSmartPtr<OdBcfTopicFolder> OdBcfTopicFolderPtr;

  class OdBcfTopic;
  typedef OdSmartPtr<OdBcfTopic> OdBcfTopicPtr;
  typedef OdArray<OdBcfTopicPtr> OdBcfTopicArray;

  class OdBcfMarkup;
  typedef OdSmartPtr<OdBcfMarkup> OdBcfMarkupPtr;

  class OdBcfVisualizationInfo;
  typedef OdSmartPtr<OdBcfVisualizationInfo> OdBcfVisualizationInfoPtr;

  class OdBcfArchive;
  typedef OdSmartPtr<OdBcfArchive> OdBcfArchivePtr;

  /** \details
  A class that provides the interface for getting access to  BCF data in XML format.
  */
  class BCF_EXPORT OdBcfDataAccessorXml : public OdBcfDataAccessor
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfDataAccessorXml);
    //DOM-IGNORE-END

    /** \details
    Creates a new data accessor object for the specified directory that stores unpacked BCF XML data.
    \param folderPath [in] A string that contains the path to the directory with BCF files.
    \returns A smart pointer to the created <link OdBcf::OdBcfDataAccessorXml, OdBcfDataAccessorXml> instance.
    \remarks 
    A temporary directory of the HostAppServices instance can be used for an example.
    */
    static OdSmartPtr<OdBcfDataAccessorXml> createObject(const OdString &folderPath);

    /** \details
    Opens a BCF XML file for interaction.
    \param projectName  [in] A string that contains the name of the BCF file.
    \param forcedReopen [in] Open BCF file again even if it's already open.
    \returns eOk if the project was successfully opened; otherwise, the method returns an appropriate error code.
    \remarks
    The method unpacks BCF data into the directory that was passed to the createObject() method call.
    */
    OdResult openProject(const OdString &projectName, bool forcedReopen = false);

    /** \details
    Closes a BCF XML file.
    \param projectName [in] A string that contains the name of the BCF XML file.
    \returns eOk if the project was successfully closed; otherwise, the method returns an appropriate error code.
    \remarks
    The method removes unpacked BCF file data.
    */
    OdResult closeProject(const OdString &projectName);

    /** \details
    Saves a BCF XML file.
    \param projectName [in] A string that contains the name of the BCF XML file.
    \param pArchive    [in] A pointer to the archive that contains BCF XML file data.
    \returns eOk if the project was successfully saved; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult putArchive(const OdString &projectName, const OdBcfArchivePtr &pArchive) ODRX_OVERRIDE;

    /** \details
    Checks if the specified BCF XML project was opened.
    \param projectName [in] A string that contains the name of the BCF XML file.
    \returns true if the project was opened; otherwise, the method returns false.
    */
    bool projectOpened(const OdString &projectName) const;

    /** \details
    Sets a progress meter.
    \param pMeter [in] A pointer to progress meter.
    \returns eOk if the progress meter was successfully set; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult setProgressMeter(OdDbHostAppProgressMeter* pMeter) ODRX_OVERRIDE;

    /** \details
    Retrieves information about used BCF XML schema.
    \param projectName [in] A string that contains the name of the BCF XML file.
    \param result      [out] A pointer to a variable containing the result of the operation.
    \returns A smart pointer to the version data.
    */
    virtual OdBcfVersionPtr getVersion(const OdString &projectName, OdResult *result = NULL) ODRX_OVERRIDE;

    /** \details
    Retrieves information about the project.
    \param projectName [in] A string that contains the name of the BCF XML file.
    \param result      [out] A pointer to a variable containing the result of the operation.
    \returns A smart pointer to the project data.
    */
    virtual OdBcfProjectExtensionPtr getProjectExtension(const OdString &projectName, OdResult *result = NULL) ODRX_OVERRIDE;

    /** \details
    Retrieves all information about the specified topic.
    \param projectName [in] A string that contains the name of the BCF XML file.
    \param topicId     [in] A string containing topic identifier.
    \param result      [out] A pointer to a variable containing the result of the operation.
    \returns A smart pointer to the topic folder data.
    */
    virtual OdBcfTopicFolderPtr getTopic(const OdString &projectName, const OdString &topicId, OdResult *result = NULL) ODRX_OVERRIDE;

    /** \details
    Retrieves markup data for the specified topic.
    \param projectName [in] A string that contains the name of the BCF XML file.
    \param topicId     [in] A string containing topic identifier.
    \param result      [out] A pointer to a variable containing the result of the operation.
    \returns A smart pointer to the markup data.
    */
    virtual OdBcfMarkupPtr getMarkup(const OdString &projectName, const OdString &topicId, OdResult *result = NULL) ODRX_OVERRIDE;

    /** \details
    Retrieves visualization information for the specified topic.
    \param projectName [in] A string that contains the name of the BCF XML file.
    \param topicId     [in] A string containing topic identifier.
    \param viewpoint   [in] A string containing viewpoint name.
    \param result      [out] A pointer to a variable containing the result of the operation.
    \returns A smart pointer to the visualization information.
    */
    virtual OdBcfVisualizationInfoPtr getVisualizationInfo(
      const OdString &projectName, 
      const OdString &topicId, 
      const OdString &viewpoint = DEFAULT_VIEWPOINT_FILE_NAME, 
      OdResult *result = NULL) ODRX_OVERRIDE;

    /** \details
    Retrieves all topics from the specified project.
    \param projectName [in] A string that contains the name of the BCF XML file.
    \param result      [out] A pointer to a variable containing the result of the operation.
    \returns An array of topics.
    */
    virtual OdBcfTopicArray getTopics(const OdString &projectName, OdResult *result = NULL);

    /** \details
    Retrieves all data of the specified project.
    \param projectName [in] A string that contains the name of the BCF XML file.
    \param result      [out] A pointer to a variable containing the result of the operation.
    \returns A smart pointer to an archive containing the BCF project.
    */
    virtual OdBcfArchivePtr getArchive(const OdString &projectName, OdResult *result = NULL) ODRX_OVERRIDE;

    //DOM-IGNORE-BEGIN
  protected:
    OdString                  m_folderPath;
    OdBcfArchiveFolderMap     m_openedProjects;
    OdDbHostAppProgressMeter *m_pMeter;

    OdString getExtractPath(const OdString &projectName) const;
    OdString getExtractProjectNameFromPath(const OdString &projectName) const;
    OdString getProjectWorkFolder(const OdString &projectName) const;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfDataAccessorXml, OdBcfDataAccessorXml> object.
  */
  typedef OdSmartPtr<OdBcfDataAccessorXml> OdBcfDataAccessorXmlPtr;

} //namespace OdBcf

#endif // _BFC_TOPIC_PROCESSOR_XML_H
