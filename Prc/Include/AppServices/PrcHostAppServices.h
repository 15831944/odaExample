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



#ifndef _ODPRC_HOSTAPPLICATIONSERVICES_INCLUDED_
#define _ODPRC_HOSTAPPLICATIONSERVICES_INCLUDED_


#include "TD_PackPush.h"

#include "DbBaseHostAppServices.h"
#include "StringArray.h"

class OdPrcFile;
typedef OdSmartPtr<OdPrcFile> OdPrcFilePtr;

class wrTriangulationParams;

/** \details 
This class is the base class for platform specific operations within PRC SDK.
<group PRC_Base_Classes>
*/
class ODRX_ABSTRACT PRC_TOOLKIT OdPrcHostAppServices : public OdDbBaseHostAppServices {
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcHostAppServices);
  //DOM-IGNORE-END

  /** \details 
  Creates platform specific operations services for .prc file functionality. 
  */
  OdPrcHostAppServices();

  /** \details 
  Enumeration for default database content initialization modes.
  */
  enum DatabaseDefaultContent
  {
    /** Database content is not to be initialized.*/
    kDbNotInitialized   = 0,  
  /** Default database content initialization mode.*/
    kDbDefault          = 1   
  };

  /** \details
  Returns the static OdRxClass description object associated with the database.

  \returns Returns the result of the OdPrcFile::desc() method.
  */
  virtual OdRxClass* databaseClass() const;

  /** \details 
  Creates an instance of an OdPrcFile object.

  \param defaultContent [in] A default database content flag. It determines whether the newly created database is populated with the default set of objects (by default).
  If the parameter value is equal to kNotInitialized, the database default content is not initialized.

  \returns Returns the newly created database.
  
  \remarks
  This HostAppServices object will be associated with the newly created database.

   */
  virtual OdPrcFilePtr createDatabase(
    DatabaseDefaultContent defaultContent = kDbDefault) const;

  /** \details 
  Returns the fully qualified path to the specified file.

  \param filename [in] A name of the file to find.
  \param pDb      [in] A pointer to the database context. If the parameter value is equal to NULL, then the file search is not related with a database.
  \param hint     [in] A hint that indicates the type of file that is required.

  \remarks 
  Returns an empty string if the file is not found.

  This method is called by PRC SDK when access is needed to a
  file, such as a font file, a template file, etc.

  If pDb parameter value is not equal to NULL, call pDb->getFilename() to determine the path to the .prc file associated with the database.

  The typical search order is as follows:

# The file name itself.
# The current directory.
# The drawing directory (for shx font, image, and xref files).
# The Windows fonts directory (only for TTF fonts on Windows).

  The hint parameter must be one of the following:
  
  <table>
  Name                    Value     Description Extension
  kDefault                0         Any file.                         any
  kFontFile               1         Can be either SHX or TTF file.    SHX or TTF
  kCompiledShapeFile      2         SHX file.                         SHX
  kTrueTypeFontFile       3         TTF file.                         TTF
  kEmbeddedImageFile      4         Image file.                       ISM
  kXRefDrawing            5         External reference file.
  kPatternFile            6         Pattern file (PAT)                PAT
  kDRXApplication         7         DRX application file.             DRX
  kFontMapFile            8         FontMap file.                     FMP
  </table>
  */
  virtual OdString findFile(
    const OdString& filename,
    OdDbBaseDatabase* pDb = 0,
    FindFileHint hint = kDefault);

  /** \details 
  Returns the current name of the client program.
  This method is typically used for populating "About" information.

  \remarks 
  The default implementation of this method returns oddgGetLibraryInfo()->getLibName().
  */
  virtual const OdString program();

  /** \details 
  Returns current name of the client product.
  This method is typically used for populating "About" information.

  \remarks
  The default implementation of this method returns program().
  */
  virtual const OdString product();

  /** \details
  Returns the current name of the client company.
  This method is typically used for populating "About" information.

  \remarks 
  The default implementation of this method returns oddgGetLibraryInfo()->getCompanyName().
  */
  virtual const OdString companyName();

  /** \details 
  Returns the release major and minor version string of the client application.
  
  \remarks
  The default implementation of this method returns oddgGetLibraryInfo()->getLibVersion().
  */
  virtual const OdString releaseMajorMinorString();

  /** \details 
  Returns the release version string of the client application.
  
  \remarks
  The default implementation of this method returns oddgGetLibraryInfo()->getLibVersion().
  */
  virtual const OdString versionString();

  /** details 
  Returns a formatted message corresponding to the specified error code(s).
  
  \param errorCode [in] An error code.
   */
  virtual OdString formatMessage(
    unsigned int errorCode,...);

  /** \details 
  Returns the path to the font file to be used when a given font file is
  not found by PRC SDK.

  \remarks
  The default implementation of this method returns an empty string.
  
  \sa
  Font Handling
  */
  virtual OdString getAlternateFontName() const;

  /** \details 
  Returns the name of the font mapping file used by the getPreferableFont method.

  \remarks 
  The default implementation of this method returns an empty string.
  
  \sa
  Font Handling
  */
  virtual OdString getFontMapFileName() const;

  /** \details 
  Returns the preferable font name for the specified font name and type.

  \param fontName [in] A font name.
  \param fontType [in] A font type.

  The fontType parameter value must be one of the following:
  
  <table>
  Name                    Value    Description
  kFontTypeUnknown        0        Unknown.
  kFontTypeShx            1        SHX font.
  kFontTypeTrueType       2        TrueType font.
  kFontTypeShape          3        Shape file.
  kFontTypeBig            4        BigFont file.
  </table>

  \remarks 
  The default implementation of this method returns an empty string.
  
  \sa
  Font Handling
  */
  virtual OdString getPreferableFont(
    const OdString& fontName,
    OdFontType fontType);

  /** \details 
  Returns the font to be used when the specified font is not found.

  \param fontName [in] A font name.
  \param fontType [in] A font type.

  The fontType parameter value must be one of the following:

  <table>
  Name                    Value    Description
  kFontTypeUnknown        0        Unknown.
  kFontTypeShx            1        SHX font.
  kFontTypeTrueType       2        TrueType font.
  kFontTypeShape          3        Shape file.
  kFontTypeBig            4        BigFont file.
  </table>

  \remarks 
  The default implementation of this method returns an empty string.
  
  \sa 
  Font Handling
  */
  virtual OdString getSubstituteFont(
    const OdString& fontName,
    OdFontType fontType);

  /** \details
    Returns the typeface name of the TTF font which has the character.

    \param pFont [in]        Current font.
    \param unicodeChar [in]  Current symbol.
    \param pDb [in]          Pointer to the database context.

    \sa
    Font Handling

    \note
    The default implementation uses Windows API for getting the font.
  */
  virtual OdString getSubstituteFontByChar(
    const OdFont& pFont,
    OdChar unicodeChar, OdDbBaseDatabase *pDb);

  /** \details
  Returns a the gsBitmapDevice associated with this HostAppServices object.

  \param pViewObj [in]  OdAbstractViewPE compatible object (OdGsView, OdDbViewport or etc.).
  \param pDb [in]  Pointer to the database context.
  \param flags [in]  Bitmap device flags.
  */
  virtual OdGsDevicePtr gsBitmapDevice(
    OdRxObject* pViewObj = NULL,
    OdDbBaseDatabase* pDb = NULL,
    OdUInt32 flags = 0);

  /** \details
  Reads .prc file content from a specified stream and returns a smart pointer to the created OdPrcFile object. 
  
  \param pFileBuff [in] A raw pointer to a stream to read data from.
  \returns A smart pointer to an OdPrcFile object that contains the read data.
  */
  virtual OdPrcFilePtr readFile(OdStreamBuf* pFileBuff);

  /** \details
  Reads content from a specified file, creates a .prc file, and returns a smart pointer to the created OdPrcFile object. 
  
  \param file [in] A path to the file to read data from.
  \returns A smart pointer to an OdPrcFile object that contains the read data.
  */
  virtual OdPrcFilePtr readFile(const OdString &file);

  /** \details
  Sets a new global setting of the B-Rep triangulation.
  \param params [out] An object that contains the settings to be applied.
  \returns eOk if the new settings were successfully set; otherwise, the method returns an appropriate error code.
  */
  virtual OdResult setTriangulationParams(const wrTriangulationParams &params);

  /** \details
  Retrieves the global setting of the B-Rep triangulation.
  \param params [out] A placeholder for the global settings of the B-Rep triangulation.
  \returns eOk if the settings were successfully returned; otherwise, the method returns an appropriate error code.
  */
  virtual OdResult getTriangulationParams(wrTriangulationParams &params);

  /** \details
  Initializes brep builder with product specific implementation. 

  \param bbuilder [in] An placeholder for the instance of B-Rep builder class.
  \param bbType   [in] A type of B-Rep object.
  \returns eOk in the B-Rep builder object was successfully initialized; otherwise, the method returns an appropriated error code.
  \remarks 
  The method returns eNotImplementedYet by default.
  */
  virtual OdResult brepBuilder(OdBrepBuilder& bbuilder, BrepType bbType);
};

#include "TD_PackPop.h"

#endif /* _ODPRC_HOSTAPPLICATIONSERVICES_INCLUDED_ */



