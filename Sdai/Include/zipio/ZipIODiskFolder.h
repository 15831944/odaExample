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

#ifndef _ZIPIO_DISK_FOLDER_H
#define _ZIPIO_DISK_FOLDER_H

#include "ZipIOCommon.h"
#include "OdString.h"
#define STL_USING_MAP
#include "OdaSTL.h"

/** \details
Contains declarations related to working with Zip files content.
*/
namespace OdZipIO {

  /** \details
  A class that provides functionality for working with archive folder.
  */
  class ZIPIO_EXPORT OdZipIODiskFolder : public OdRxObject
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdZipIODiskFolder);
    //DOM-IGNORE-END

    /** \details
    Creates a new archive folder object.
    \param folder [in] A string containing path to archive working folder.
    \returns Returns a smart pointer to the created <link OdBcf::OdZipIODiskFolder, OdZipIODiskFolder> instance.
    */
    static OdSmartPtr<OdZipIODiskFolder> createObject(const OdString &folder);

    /** \details
    Destroys archive folder.
    */
    ~OdZipIODiskFolder();

    const OdString& getFolder() const;

    //DOM-IGNORE-BEGIN
  protected:
    OdString m_folder;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdZipIODiskFolder, OdZipIODiskFolder> object.
  */
  typedef OdSmartPtr<OdZipIODiskFolder> OdZipIODiskFolderPtr;

  /** \details
  A data type that represents an STD map of pairs consisting of OdGUID and a pointer to an <link OdBcf::OdZipIODiskFolder, OdZipIODiskFolder> objects.
  */
  typedef std::map<OdString, OdZipIODiskFolderPtr> OdZipIODiskFolderMap;

} //namespace OdBcf

#endif // _ZIPIO_DISK_FOLDER_H
