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

#ifndef _ZIP_UTILS_H
#define _ZIP_UTILS_H

#include "OdPlatformSettings.h"
#include "StringArray.h"

#include <cstdint>

/** \details
Contains declarations related to working with Zip files content.
*/
namespace ZipUtils
{

#define FILE_BUFFER_SIZE 1024

  /** \details
  Converts unicode string to UTF-8.
  \param sUnicode [in] A string in unicode format.
  \returns Returns string in UTF-8 format.
  */
  OdAnsiString OdStringToUtf8(const OdString &sUnicode);

  /** \details
  Formats path to file to conform current platform.
  \param path [in] A string containing path to file.
  \returns Returns string containing formatted path.
  */
  OdString formatPath(const OdString &path);

  /** \details
  Formats path to directory to conform current platform.
  \param dir [in] A string containing path to directory.
  \returns Returns string containing formatted path.
  \remarks
  The function ensures that there is separator on the end of the path.
  */
  OdString formatDir(const OdString &dir);

  /** \details
  Checks if string contains path to directory.
  \param dir [in] A string containing path.
  \returns Returns true if string contains path to directory; otherwise the method returns false.
  */
  bool containsDir(const OdString &dir);

  /** \details
  Checks if string is path to directory.
  \param dir [in] A string containing path.
  \returns Returns true if string is path to directory; otherwise the method returns false.
  */
  bool isDir(const OdString &dir);

  /** \details
  Selects file extension part of the path.
  \param path [in] A string containing path to the file.
  \returns Returns string containing file extension.
  */
  OdString getFileExtension(const OdString &path);

  /** \details
  Selects file part of the path.
  \param path [in] A string containing path to the file.
  \returns Returns string containing file name.
  */
  OdString getFile(const OdString &path);

  /** \details
  Selects directory part of the path.
  \param path [in] A string containing path to the directory.
  \returns Returns string containing path the directory.
  */
  OdString getDir(const OdString &path);

  /** \details
  Creates file.
  \param path [in] A string containing path to file.
  \param data [in] A pointer to buffer containing file data.
  \param size [in] Length of the buffer containing file data.
  \returns Returns 0 if file was successfully created; otherwise, the method returns an appropriate error.
  */
  int createFile(const OdString &path, const char *data, unsigned int size);

  /** \details
  Copies existing file to new location under specified name.
  \param existingFileName [in] A string containing path to exsiting file.
  \param newFileName      [in] A string containing path to new file.
  \returns Returns 0 if file was successfully copied; otherwise, the method returns an appropriate error.
  */
  int copyFile(const OdString &existingFileName, const OdString &newFileName);

  /** \details
  Removes file.
  \param path [in] A string containing path to file.
  \returns Returns 0 if file was successfully removed; otherwise, the method returns an appropriate error.
  */
  int removeFile(const OdString &path);

  /** \details
  Checks if string is path to existing directory.
  \param dir [in] A string containing path.
  \returns Returns true if string is path to existing directory; otherwise the method returns false.
  */
  bool dirExists(const OdString &dir);

  /** \details
  Creates empty directory.
  \param dir [in] A string containing path to new directory.
  \returns Returns 0 if directory was successfully created; otherwise, the method returns an appropriate error.
  */
  int createDir(const OdString &dir);

  /** \details
  Removes empty directory.
  \param value [in] A string containing path to new directory.
  \returns Returns 0 if directory was successfully removed; otherwise, the method returns an appropriate error.
  */
  int removeEmptyDir(const OdString &dir);

  /** \details
  Removes directory.
  \param dir [in] A string containing path to new directory.
  \returns Returns 0 if directory was successfully removed; otherwise, the method returns an appropriate error.
  \remarks
  The function removes all files from directory and recursively removes all subdirectories.
  */
  int removeDir(const OdString &dir);

  /** \details
  Creates list of all files in specified directory.
  \param dir [in] A string containing path to directory.
  \returns Returns list of files.
  */
  OdStringArray getFileList(const OdString &dir);

  /** \details
  Creates list of all directories in specified directory.
  \param dir [in] A string containing path to directory.
  \returns Returns list of directories.
  */
  OdStringArray getDirList(const OdString &dir);

  /** \details
  Returns identifier of current process.
  \returns Returns id of process.
  */
  uintmax_t getProcessId();

  /** \details
  Returns unique name for current process and time.
  \returns Returns unique name.
  */
  OdString getUniqueDirName();

  /** \details
  Unzips file to directory.
  \param filePath           [in] A string containing path to the zip file.
  \param targetDir          [in] A string containing name of the target directory.
  \param overwriteTargetDir [in] Return error if false and target directory is not empty; otherwise, overwrite target directory.
  \returns Returns appropriate error code.
  */
  OdResult unzipFile(const OdString &filePath, const OdString &targetDir, bool overwriteTargetDir = true);

  /** \details
  Zips directory to file.
  \param targetFile          [in] A string containing path to the target zip file.
  \param filesDir            [in] A string containing name of the source directory.
  \param overwriteTargetFile [in] Return error if false and target file exists; otherwise, overwrite target file.
  \returns Returns appropriate error code.
  */
  OdResult zipToFile(const OdString &targetFile, const OdString &filesDir, bool overwriteTargetFile = true);

} //namespace ZipUtils

#endif // _ZIP_UTILS_H
