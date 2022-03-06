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

#ifndef _BFC_TOPIC_PROCESSOR_H
#define _BFC_TOPIC_PROCESSOR_H

#include "BcfCommon.h"
#include "DbHostAppProgressMeter.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfVersion;
  typedef OdSmartPtr<OdBcfVersion> OdBcfVersionPtr;

  class OdBcfProjectExtension;
  typedef OdSmartPtr<OdBcfProjectExtension> OdBcfProjectExtensionPtr;

  class OdBcfTopicFolder;
  typedef OdSmartPtr<OdBcfTopicFolder> OdBcfTopicFolderPtr;

  class OdBcfMarkup;
  typedef OdSmartPtr<OdBcfMarkup> OdBcfMarkupPtr;

  class OdBcfVisualizationInfo;
  typedef OdSmartPtr<OdBcfVisualizationInfo> OdBcfVisualizationInfoPtr;

  class OdBcfArchive;
  typedef OdSmartPtr<OdBcfArchive> OdBcfArchivePtr;

  /** \details
  An abstract class that provides the interface for getting access to BCF data.
  */
  class BCF_EXPORT OdBcfDataAccessor : public OdRxObject
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfDataAccessor);
    //DOM-IGNORE-END

    /** \details
    Saves a BCF file.
    \param projectName [in] A string that contains the name of the BCF file.
    \param pArchive    [in] A pointer to archive that contains BCF file data.
    \returns eOk if the project was successfully saved; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult putArchive(const OdString &projectName, const OdBcfArchivePtr &pArchive) = 0;

    /** \details
    Sets a progress meter.
    \param pMeter [in] A pointer to progress meter.
    \returns eOk if the progress meter was successfully set; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult setProgressMeter(OdDbHostAppProgressMeter* pMeter) = 0;

    /** \details
    Retrieves information on the BCF schema used.
    \param projectName [in] A string that contains the name of the BCF file.
    \param result      [out] A raw pointer to a variable containing the result of the operation.
    \returns A smart pointer to the version data.
    */
    virtual OdBcfVersionPtr getVersion(const OdString &projectName, OdResult *result = NULL) = 0;

    /** \details
    Retrieves information about the project.
    \param projectName [in] A string that contains the name of the BCF file.
    \param result      [out] A raw pointer to a variable containing the result of the operation.
    \returns A smart pointer to the project data.
    */
    virtual OdBcfProjectExtensionPtr getProjectExtension(const OdString &projectName, OdResult *result = NULL) = 0;

    /** \details
    Retrieves all information about the specified topic.
    \param projectName [in] A string that contains the name of the BCF file.
    \param topicId     [in] A string containing topic identifier.
    \param result      [out] A pointer to a variable containing the result of the operation.
    \returns A smart pointer to the topic folder data.
    */
    virtual OdBcfTopicFolderPtr getTopic(const OdString &projectName, const OdString &topicId, OdResult *result = NULL) = 0;

    /** \details
    Retrieves the markup data of the specified topic.
    \param projectName [in] A string that contains the name of the BCF file.
    \param topicId [in] A string containing topic identifier.
    \param result  [out] A pointer to a variable containing the result of the operation.
    \returns A smart pointer to the markup data.
    */
    virtual OdBcfMarkupPtr getMarkup(const OdString &projectName, const OdString &topicId, OdResult *result = NULL) = 0;

    /** \details
    Retrieves visualization information for the specified topic.
    \param projectName [in] A string that contains the name of the BCF file.
    \param topicId     [in] A string containing topic identifier.
    \param viewpoint   [in] A string containing viewpoint name.
    \param result      [out] A pointer to a variable containing the result of the operation.
    \returns A smart pointer to the visualization information.
    */
    virtual OdBcfVisualizationInfoPtr getVisualizationInfo(
      const OdString &projectName, 
      const OdString &topicId, 
      const OdString &viewpoint = DEFAULT_VIEWPOINT_FILE_NAME,
      OdResult *result = NULL) = 0;

    /** \details
    Retrieves all the data about the specified project.
    \param projectName [in] A string that contains the name of the BCF file.
    \param result      [out] A pointer to a variable containing the result of the operation.
    \returns A smart pointer to an archive object representing the BCF project.
    */
    virtual OdBcfArchivePtr getArchive(const OdString &projectName, OdResult *result = NULL) = 0;
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfDataAccessor, OdBcfDataAccessor> object.
  */
  typedef OdSmartPtr<OdBcfDataAccessor> OdBcfDataAccessorPtr;

} //namespace OdBcf

#endif // _BFC_TOPIC_PROCESSOR_H
