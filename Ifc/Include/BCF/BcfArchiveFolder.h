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

#ifndef _BFC_ARCHIVE_FOLDER_H
#define _BFC_ARCHIVE_FOLDER_H

#include "BcfCommon.h"
#include "OdString.h"
#define STL_USING_MAP
#include "OdaSTL.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  /** \details
  A class that provides functionality for working with an archive folder.
  */
  class BCF_EXPORT OdBcfArchiveFolder : public OdRxObject
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfArchiveFolder);
    //DOM-IGNORE-END

    /** \details
    Creates a new archive folder object.
    \param folder [in] A string containing the path to archive working folder.
    \returns A smart pointer to the created <link OdBcf::OdBcfArchiveFolder, OdBcfArchiveFolder> instance.
    */
    static OdSmartPtr<OdBcfArchiveFolder> createObject(const OdString &folder);

    /** \details
    Creates a new archive folder object with an unset path.
    */
    OdBcfArchiveFolder();

    /** \details
    Destroys the archive folder object.
    */
    ~OdBcfArchiveFolder();

    /** \details
    Retrieves the path to the archive folder. 
    The archive folder is a temporary folder on a drive where the BCF archive was unpacked.
    \returns A string that contains the path.
    \remarks 
    The folder path returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getFolder() const;

    /** \details
    Defines whether the path to the archive folder is not initialized.
    \returns true if the path to the archive folder is not initialized; otherwise, the method returns false.
    */
    bool isFolderUnset() const;

    //DOM-IGNORE-BEGIN
  protected:
    OdString m_folder;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfArchiveFolder, OdBcfArchiveFolder> object.
  */
  typedef OdSmartPtr<OdBcfArchiveFolder> OdBcfArchiveFolderPtr;

  /** \details
  A data type that represents an STD map of pairs consisting of OdGUID and a pointer to an <link OdBcf::OdBcfArchiveFolder, OdBcfArchiveFolder> objects.
  */
  typedef std::map<OdString, OdBcfArchiveFolderPtr> OdBcfArchiveFolderMap;

} //namespace OdBcf

#endif // _BFC_ARCHIVE_FOLDER_H
