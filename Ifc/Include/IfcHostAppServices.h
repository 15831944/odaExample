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

#ifndef _IFC_HOST_APP_SERVICES_H_
#define _IFC_HOST_APP_SERVICES_H_

#include "IfcFile.h"

#include "daiHostAppServicesBase.h"

#include "TD_PackPush.h"

class OdIfcFile;
typedef OdSmartPtr<OdIfcFile> OdIfcFilePtr;

/** \details 
The class that implements for platform-specific operations within the IFC SDK. 
*/
class /*ODRX_ABSTRACT*/ IFCCORE_EXPORT OdIfcHostAppServices : public OdDAIHostAppServicesBase
{
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdIfcHostAppServices);
  //DOM-IGNORE-END

  /** \details
  Creates a platform-specific operation services object for IFC functionality.
  */
  OdIfcHostAppServices();

  /** \details
  Retrieves the IFC database class description.
  \returns The desc() method's result of the <link OdIfcFile, OdIfcFile> object.
  */
  virtual OdRxClass* databaseClass() const;

  /** \details
  Creates a new instance of the <link OdIfcFile, OdIfcFile> class.
  \param initialSchema [in] An initial schema to be used for the new instance creation. 
  \returns A smart pointer to the <link OdIfcFile, OdIfcFile> object that represents the created database instance.
  \remarks 
  If the parameter is equal to the kScmUndefined value, the created .ifc file doesn't have underlying <link OdDAI::Model, OdDAI::Model> object. 
  This way of initialization is used for the file open operation when the underlying model should be created during the file loading process.
  The host application services object is associated with the newly created database.
  */
  virtual OdIfcFilePtr createDatabase(
    IfcSchema initialSchema = kScmUndefined) const;

  /** \details
  Creates a new instance of the <link OdIfcFile, OdIfcFile> class.
  \param schemaName [in] An initial schema name to be used for the new instance creation.
  \returns A smart pointer to the <link OdIfcFile, OdIfcFile> object that represents the created database instance.
  \remarks
  If the parameter string is empty, the created .ifc file doesn't have underlying <link OdDAI::Model, OdDAI::Model> object.
  This way of initialization is used for the file open operation when the underlying model should be created during the file loading process.
  The host application services object is associated with the newly created database.
  */
  virtual OdIfcFilePtr createDatabase(
    const OdAnsiString &schemaName) const;

  /** \details
  Searches for a specified file.
  \param filename [in] A name of the file to find.
  \param pDb      [in] A pointer to the database context. If the parameter value is equal to NULL, the file search is not related to a database.
  \param hint     [in] A hint that indicates the type of file that is required.
  \returns The full path to the found file; if the file was not found, the method returns an empty string.
  \remarks
  This method is called by IFC SDK when it needs to get access to a file, such as a font file, a template file, etc.
  If the pointer to the database context is not equal to NULL, it is possible to call the getFilename() method of the database instance 
  to determine the full path to the IFC file associated with the database.
  The typical search order is the following:

  # The file name itself.
  # The current directory.
  # The drawing directory (for SHX font, image, and xref files).
  # The Windows fonts directory (only for TTF fonts on Windows platforms).

  The hint parameter's value must be one of the following:

  <table>
  Name                    Value     Description Extension
  kDefault                0         Any file.                         any
  kFontFile               1         Can be either SHX or TTF file.    SHX or TTF
  kCompiledShapeFile      2         SHX file.                         SHX
  kTrueTypeFontFile       3         TTF file.                         TTF
  kEmbeddedImageFile      4         Image file.                       ISM
  kXRefDrawing            5         External reference file.
  kPatternFile            6         Pattern file (PAT).               PAT
  kDRXApplication         7         DRX application file.             DRX
  kFontMapFile            8         FontMap file.                     FMP
  </table>
  */
  virtual OdString findFile(
    const OdString& filename,
    OdDbBaseDatabase* pDb = 0,
    FindFileHint hint = kDefault);

  /** \details
  Retrieves the current name of the client program based on ODA IFC SDK.
  \returns A string object containing the custom application name.
  \remarks
  The default implementation of this method returns oddgGetLibraryInfo()->getLibName().
  This method is typically used for populating information about the application.
  */
  virtual const OdString program();

  /** \details
  Retrieves the current name of the client product based on ODA IFC SDK.
  \returns A string object containing the current name of the client product.
  \remarks
  The default implementation of this method returns the result of the program() method.
  This method is typically used for populating information about the product.
  */
  virtual const OdString product();

  /** \details
  Retrieves the current name of the client company.
  \returns A string object containing the current name of the client company.
  \remarks
  The default implementation of this method returns the result returned by the oddgGetLibraryInfo()->getCompanyName().
  This method is typically used for populating information about the client's company.
  */
  virtual const OdString companyName();

  /** details
  Formats an error message string corresponding to the specified error code(s). 
  \param errorCode [in] An error code.
  \returns A string with a formatted error message.
  */
  virtual OdString formatMessage(
    unsigned int errorCode,...);

  /** \details
  Retrieves the current default font name. 
  \returns the path to the font file to be used when a given font file can not be found by IFC SDK.
  \remarks
  The default implementation of the method returns an empty string.
  \sa
  <exref target="https://docs.opendesign.com/td/FontHandling.html">Font Handling</exref>
  */
  virtual OdString getAlternateFontName() const;

  /** \details
  Retrieves the current font mapping file. This font mapping file is used by the 
  <link OdIfcHostAppServices::getPreferableFont@OdString&@OdFontType, getPreferableFont()> method.
  \returns the name of the font mapping file.
  \remarks
  The default implementation of this method returns an empty string.
  \sa
  <exref target="https://docs.opendesign.com/td/FontHandling.html">Font Handling</exref>
  */
  virtual OdString getFontMapFileName() const;

  /** \details
  Retrieves the current preferable font name for a specified font name and type.
  \param fontName [in] A font name.
  \param fontType [in] A font type.
  \returns a string object containing the preferable font name.
  \remarks
  The default implementation of this method returns an empty string.

  The fontType parameter value must be one of the following:

  <table>
  Name                    Value    Description
  kFontTypeUnknown        0        Unknown.
  kFontTypeShx            1        SHX font.
  kFontTypeTrueType       2        TrueType font.
  kFontTypeShape          3        Shape file.
  kFontTypeBig            4        BigFont file.
  </table>
  \sa
  <exref target="https://docs.opendesign.com/td/FontHandling.html">Font Handling</exref>
  */
  virtual OdString getPreferableFont(
    const OdString& fontName,
    OdFontType fontType);

  /** \details
  Retrieves the current substitute font name. The substitute font is used in cases when a specified font is not found.
  \param fontName [in] A font name.
  \param fontType [in] A font type.
  \returns a string object that contains the substitute font name.
  \remarks 
  The default implementation of this method returns an empty string.
  The fontType parameter value must be one of the following:

  <table>
  Name                    Value    Description
  kFontTypeUnknown        0        Unknown.
  kFontTypeShx            1        SHX font.
  kFontTypeTrueType       2        TrueType font.
  kFontTypeShape          3        Shape file.
  kFontTypeBig            4        BigFont file.
  </table>
  \sa
  <exref target="https://docs.opendesign.com/td/FontHandling.html">Font Handling</exref>
  */
  virtual OdString getSubstituteFont(
    const OdString& fontName,
    OdFontType fontType);

  /** \details
  Retrieves the typeface name of the TTF font that has the specified character.
  \param pFont        [in] A TTF font object.
  \param unicodeChar  [in] A symbol to find in the substitute font name.
  \param pDb          [in] A raw pointer to the database context.
  \returns a string object that contains the substitute font name. 
  \remarks
  The default method implementation uses the Windows API for getting the font.
  \sa
  <exref target="https://docs.opendesign.com/td/FontHandling.html">Font Handling</exref>
  */
  virtual OdString getSubstituteFontByChar(
    const OdFont& pFont,
    OdChar unicodeChar, OdDbBaseDatabase *pDb);

  /** \details
  Retrieves the current bitmap <exref target="https://docs.opendesign.com/tv/OdGsDevice.html">device</exref> 
  associated with the host application services object.
  \param pViewObj [in] A raw pointer to an <exref target="https://docs.opendesign.com/tkernel/OdAbstractViewPE.html">OdAbstractViewPE</exref> compatible object  
  (<exref target="https://docs.opendesign.com/tv/OdGsView.html">OdGsView</exref>, <exref target="https://docs.opendesign.com/td/OdDbViewport.html">OdDbViewport</exref>, etc).
  \param pDb      [in] A raw pointer to the database context.
  \param flags    [in] Bitmap device flags.
  \returns a smart pointer to the <exref target="https://docs.opendesign.com/tv/OdGsDevice.html">device</exref> object associated with the host application services object.
  */
  virtual OdGsDevicePtr gsBitmapDevice(
    OdRxObject* pViewObj = NULL,
    OdDbBaseDatabase* pDb = NULL,
    OdUInt32 flags = 0);

  /** \details
  Reads an IFC file content from a specified stream and creates an instance of the <link OdIfcFile, OdIfcFile> class.
  \param pFileBuff [in] A raw pointer to a stream to read data from.
  \returns a smart pointer to the created <link OdIfcFile, IFC file object>.
  */
  virtual OdIfcFilePtr readFile(OdStreamBuf* pFileBuff);

  /** \details
  Reads an IFC file content from a specified file and creates an instance of the <link OdIfcFile, OdIfcFile> class.
  \param file [in] A full path to the file to read data from.
  \returns a smart pointer to the created <link OdIfcFile, IFC file object>.
  */
  virtual OdIfcFilePtr readFile(const OdString &file);

//DOM-IGNORE-BEGIN
  /** \details
  Global setting of B-Rep triangulation.
  */
  //virtual OdResult setTriangulationParams(const wrTriangulationParams &params);

  /** \details
  Global setting of B-Rep triangulation.
  */
  //virtual OdResult getTriangulationParams(wrTriangulationParams &params);
//DOM-IGNORE-END
  
  /** \details
  Initializes the boundary representation builder with a product-specific implementation.
  \param brepBuilder  [out] A reference to an instance of the boundary representation builder class to be initialized.
  \param bbType       [in]  A type of boundary representation.
  \returns eOk if the B-Rep builder was successfully initialized; otherwise the method returns an appropriate error code.
  \remarks 
  The method returns eNotImplementedYet value by default.
  */
  virtual OdResult brepBuilder(OdBrepBuilder& bbuilder, BrepType bbType);

  /* \details
  Retrieves whether an OdGiAuxDataForIfc object should be used while vectorizing.
  \returns true if the OdGiAuxDataForIfc object should be created inside the OdGiContextForIfcDatabase object to use during the vectorization process; otherwise, the method returns false.
  */
  virtual bool getUseVectAuxData() const;
};

#include "TD_PackPop.h"

#endif // _IFC_HOST_APP_SERVICES_H_
