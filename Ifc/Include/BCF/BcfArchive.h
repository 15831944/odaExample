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

#ifndef _BFC_ARCHIVE_H
#define _BFC_ARCHIVE_H

#include "BcfCommon.h"
#include "OdGUID.h"
#define STL_USING_MAP
#include "OdaSTL.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfArchiveFolder;
  typedef OdSmartPtr<OdBcfArchiveFolder> OdBcfArchiveFolderPtr;

  class OdBcfProjectExtension;
  typedef OdSmartPtr<OdBcfProjectExtension> OdBcfProjectExtensionPtr;

  class OdBcfVersion;
  typedef OdSmartPtr<OdBcfVersion> OdBcfVersionPtr;

  class OdBcfTopicFolder;
  typedef OdSmartPtr<OdBcfTopicFolder> OdBcfTopicFolderPtr;
  typedef std::map<OdGUID, OdBcfTopicFolderPtr> OdBcfTopicFolderMap;

  class OdBcfSession;

  /** \details
  A class that provides functionality for working with project archive.
  */
  class BCF_EXPORT OdBcfArchive : public OdRxObject
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfArchive);
    //DOM-IGNORE-END

    /** \details
    Creates a new archive object.
    \param rootDir           [in] A pointer to the archive root directory.
    \param pVersion          [in] A pointer to version of archive.
    \param pProjectExtension [in] A pointer to project extension of archive.
    \param topics            [in] A map of topics in the archive.
    \param changed           [in] A flag that determines whether the archive was changed after creation (equal to true) or not (equal to false).
    \returns  A smart pointer to the created <link OdBcf::OdBcfArchive, OdBcfArchive> instance.
    */
    static OdSmartPtr<OdBcfArchive> createObject(
      const OdBcfArchiveFolderPtr    &rootDir,
      const OdBcfVersionPtr          &pVersion,
      const OdBcfProjectExtensionPtr &pProjectExtension  = OdBcfProjectExtensionPtr(),
      const OdBcfTopicFolderMap      &topics = OdBcfTopicFolderMap(),
      bool                            changed = false);

    /** \details
    Creates a new archive object with default parameters.
    */
    OdBcfArchive();

    /** \details
    Checks whether the instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise, the method returns false.
    */
    virtual bool validate() const;

    /** \details
    Retrieves the archive's root directory.
    \returns A smart pointer to the <link OdBcf::OdBcfArchiveFolder, OdBcfArchiveFolder> object that represents the root directory.
    \remarks 
    The root directory object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfArchiveFolderPtr& getRootDir() const;

    /** \details
    Defines whether the archive's root directory is not initialized.
    \returns true if the root directory is not initialized; otherwise, the method returns false.
    */
    bool isRootDirUnset() const;

    /** \details
    Retrieves the archive's version.
    \returns A smart pointer to the <link OdBcf::OdBcfVersion, OdBcfVersion> object that represents the version.
    \remarks 
    The version object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfVersionPtr& getVersion() const;

    /** \details
    Defines whether the archive's version is not initialized.
    \returns true if the version is not initialized; otherwise, the method returns false.
    */
    bool isVersionUnset() const;

    /** \details
    Sets a new project extension object for the archive.
    \param projectExtensionValue [in] A smart pointer to the <link OdBcf::OdBcfProjectExtension, OdBcfProjectExtension> object to be set.
    */
    void setProjectExtension(const OdBcfProjectExtensionPtr &projectExtensionValue);

    /** \details
    Retrieves the archive's project extension.
    \returns A smart pointer to the <link OdBcf::OdBcfProjectExtension, OdBcfProjectExtension> object that represents the project extension.
    \remarks 
    The project extension object returned by the method can be modified in the calling subroutine.
    */
    OdBcfProjectExtensionPtr& getProjectExtension();

    /** \details
    Retrieves the archive's project extension.
    \returns A smart pointer to the <link OdBcf::OdBcfProjectExtension, OdBcfProjectExtension> object that represents the project extension.
    \remarks 
    The project extension object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfProjectExtensionPtr& getProjectExtension() const;

    /** \details
    Defines whether the archive's project extension is not initialized.
    \returns true if the project extension is not initialized; otherwise, the method returns false.
    */
    bool isProjectExtensionUnset() const;

    /** \details
    Sets new topic folders for the archive.
    \param topicsValue [in] A smart pointer to the map of <link OdBcf::OdBcfTopicFolder, OdBcfTopicFolder> objects to be set as archive topics.
    */
    void setTopics(const OdBcfTopicFolderMap &topicsValue);

    /** \details
    Retrieves the archive's topic folders.
    \returns A map of the <link OdBcf::OdBcfTopicFolder, OdBcfTopicFolder> objects.
    \remarks 
    The project extension object returned by the method can be modified in the calling subroutine.
    */
    OdBcfTopicFolderMap& getTopics();

    /** \details
    Retrieves the archive's topic folders.
    \returns A map of the <link OdBcf::OdBcfTopicFolder, OdBcfTopicFolder> objects.
    \remarks 
    The project extension object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfTopicFolderMap& getTopics() const;

    /** \details
    Defines whether the archive's topic folders are not initialized.
    \returns true if the topic folders map is not initialized; otherwise, the method returns false.
    */
    bool isTopicsUnset() const;

    /** \details
    Retrieves the archive's global unique identifier (GUID).
    \returns An <exref target="https://docs.opendesign.com/tkernel/OdGUID.html">OdGUID</exref> object that represents the identifier.
    */
    const OdGUID& getArchiveGUID() const;

    /** \details
    Defines whether the archive's global unique identifier (GUID) is not initialized.
    \returns true if the GUID is not initialized; otherwise, the method returns false.
    */
    bool isArchiveGUIDUnset() const;

  //DOM-IGNORE-BEGIN
  protected:
    OdBcfVersionPtr          m_pVersion;
    OdBcfProjectExtensionPtr m_pProjectExtension;
    OdBcfTopicFolderMap      m_topics;
    OdGUID                   m_archiveGUID;
    OdBcfArchiveFolderPtr    m_rootDir;
    bool                     m_changed;

    /** \details
    Sets a new root directory for the archive.
    \param rootDirValue [in] A smart pointer to the <link OdBcf::OdBcfArchiveFolder, OdBcfArchiveFolder> object to be set as a root directory.
    */
    void setRootDir(const OdBcfArchiveFolderPtr &rootDirValue);

    /** \details
    Sets a new version for the archive.
    \param versionValue [in] A smart pointer to the <link OdBcf::OdBcfVersion, version> object to be set.
    */
    void setVersion(const OdBcfVersionPtr &versionValue);

    /** \details
    Retrieves the archive's root directory.
    \returns A smart pointer to the <link OdBcf::OdBcfArchiveFolder, OdBcfArchiveFolder> object that represents the root directory.
    \remarks 
    The object that represents the root directory returned by the method can be modified in the calling subroutine.
    */
    OdBcfArchiveFolderPtr& getRootDir();

    /** \details
    Retrieves the archive's version.
    \returns A smart pointer to the <link OdBcf::OdBcfVersion, OdBcfVersion> object that represents the version.
    \remarks 
    The object that represents the version returned by the method can be modified in the calling subroutine.
    */
    OdBcfVersionPtr& getVersion();


    friend OdBcfSession;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfArchive, OdBcfArchive> object.
  */
  typedef OdSmartPtr<OdBcfArchive> OdBcfArchivePtr;

  /** \details
  A data type that represents an STD map of pairs consisting of a string and a pointer to an <link OdBcf::OdBcfArchive, OdBcfArchive> objects.
  */
  typedef std::map<OdString, OdBcfArchivePtr> OdBcfArchiveMap;

} //namespace OdBcf

#endif // _BFC_ARCHIVE_H
