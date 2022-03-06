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

#ifndef _PRCPICTURE_INCLUDED_
#define _PRCPICTURE_INCLUDED_ 
 

#include "PrcBase.h"
#include "Gi/GiRasterImage.h"

SMARTPTR(OdPrcPicture);
class OdPrcFileStructure;

/** \details 
<group PRC_Graphic_Classes> 

Class representing a picture embedded in the .prc file.
*/
class PRC_TOOLKIT OdPrcPicture : public OdPrcBase
{

public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcPicture)
  //DOM-IGNORE-END

  /** \details 
  Sets a new value of the picture format.
  
  \param format [in] A new picture format value.
  */
  void setFormat(OdInt32 format);
  
  /** \details
  Returns the current picture format code.
  */
  OdInt32 format() const;
  
  /** \details
  Sets a new picture height in pixels.

  \param pixel_height [in] A new height in pixels to be set.
  */
  void setPixelHeight(OdUInt32 pixel_height);
  
  /** \details
  Returns the current picture height in pixels.
  */
  OdUInt32 pixelHeight() const;
  
  /** \details
  Sets a new picture width in pixels.

  \param pixel_width [in] A new width in pixels to be set.
  */
  void setPixelWidth(OdUInt32 pixel_width);
  
  /** \details
  Returns the current picture width in pixels.
  */
  OdUInt32 pixelWidth() const;
  
  /** \details
  Sets a new value for an uncompressed file index.

  \param uncompressed_file_index [in] A new index to be set.
  */
  void setUncompressedFileIndex(OdUInt32 uncompressed_file_index);
  
  /** \details
  Returns the current value of an uncompressed file index.
  */
  OdUInt32 uncompressedFileIndex() const;

  /** \details 
  Creates a picture basing on a specified raster image. 
  The method adds the created picture in a specified file structure.
  \param pImage            [in] A raster image to be used as a base for creating the picture.
  \param fileStructure     [out] A reference to a file structure where the created picture object should be added.
  \param bPreventDuplicate [in] A flag that determines whether duplication of pictures is allowed (if it is equal to false) or not (if it is equal to true).
  \returns A smart pointer to the created picture object.
  */
  static OdPrcPicturePtr createByImage(const OdGiRasterImagePtr &pImage, OdPrcFileStructure &fileStructure, bool bPreventDuplicate = true);

  /** \details 
  Creates a picture basing on a specified raster image. 
  The method adds the created picture in a specified file structure.
  \param filename          [in] A string that contains the full path to the origin raster image.
  \param fileStructure     [out] A reference to a file structure where the created picture object should be added.
  \param bPreventDuplicate [in] A flag that determines whether duplication of pictures is allowed (if it is equal to false) or not (if it is equal to true).
  \returns A smart pointer to the created picture object.
  */  
  static OdPrcPicturePtr createByImage(const OdString &filename, OdPrcFileStructure &fileStructure, bool bPreventDuplicate = true);
};

#endif // _PRCPICTURE_INCLUDED_

