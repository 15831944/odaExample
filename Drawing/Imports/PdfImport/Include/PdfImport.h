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

#ifndef _PDFIMPORT_INCLUDED_
#define _PDFIMPORT_INCLUDED_

#include "RxModule.h"
#include "RxDictionary.h"
#include "DynamicLinker.h"

//////////////////////////////////////////////////////////////////////////

#include "OdPlatformSettings.h"
#include <functional>

#ifdef PDFIMPORT_EXPORTS
  #define PDFIMPORT_TOOLKIT         OD_TOOLKIT_EXPORT
  #define PDFIMPORT_TOOLKIT_STATIC  OD_STATIC_EXPORT
#else                               
  #define PDFIMPORT_TOOLKIT         OD_TOOLKIT_IMPORT
  #define PDFIMPORT_TOOLKIT_STATIC  OD_STATIC_IMPORT
#endif

//////////////////////////////////////////////////////////////////////////

class OdDbDatabase;

/** \details
This is a prototype of the preferred font setting function.

\param font_name                 [in] The name of the current font. The name is the same as the one displayed in the properties of the PDF document.
\param font_family               [in] FamilyName for the current font.
\param is_found                  [in] Flag to determine if the current font is found in the system.

\returns The name of the font to which the current font is to be replaced, or an empty string if replacement is not required.
*/
using PreferableFontCallback = std::function<OdAnsiString(const char*, const char*, const bool)>;

//DD:EXPORT_ON

/** \details
An abstract class that represents the interface for the import from a .pdf file.
<group OdPdfImport_Classes>
*/
class OdPdfImport : public OdRxObject
{
public:
  /** \details 
  Contains a list of the PDF import operation results that are handled by the <link OdPdfImportModule, PDF import module>.
  */
  enum ImportResult 
  {
    /** The import process is successfully finished.*/
    success, 
    /**The import process failed.*/
    fail, 
    /** The import process failed because of an incorrect password.*/
    bad_password, 
    /** The import process failed because of an incorrect input .pdf file.*/
    bad_file, 
    /** The import process failed because of an incorrect destination database object.*/
    bad_database, 
    /** The import process failed because of an encrypted input .pdf file.*/
    encrypted_file, 
    /** The import process failed because of an invalid page number of the input .pdf file.*/
    invalid_page_number, 
    /** The import process failed because of an error during the image file saving (the possible reason is an invalid directory for saving).*/
    image_file_error, 
    /** The import process failed because no objects were imported.*/
    no_objects_imported,
    /** The import process failed because of an error during the embedded font file saving (the possible reason is an invalid directory for saving).*/
    font_file_error
  };
  
  /** \details 
  Imports a .pdf file's contents to a drawing database with specified properties.
  This method should be reimplemented to provide the functionality for importing from a .pdf file.
  \returns Returns a value of the <link OdPdfImport::ImportResult, ImportResult> enumeration that contains the result of the import process.
  \remarks 
  To specify import properties, use the <link OdPdfImport::properties, properties()> method to get access to the import properties dictionary object.
  */
  virtual ImportResult import() = 0;

  /** \details 
  Retrieves a dictionary object that contains the set of .pdf import properties.
  \returns Returns a smart pointer to the dictionary object that contains properties used for the import of a .pdf file's content to a drawing database. 
  \remarks 
  The list of supported properties for the PDF import operation is represented in the table below.
  <table>
    <tr>
      <th>Property Name</th>  <th>Description</th>
    </tr>
    <tr>
      <td>Database</td>  <td>A target database object (an instance of the OdDbDatabase class). The contents of the .pdf file are imported to this database.</td>
    </tr>
    <tr>
      <td>PdfPath</td>  <td>A full path to the imported .pdf file.</td>
    </tr>
    <tr>
      <td>Password</td>  <td>A password for the input .pdf file (empty by default).</td>
    </tr>
    <tr>
      <td>PageNumber</td>  <td>A page number of the input .pdf file. Starts from 1 (by default).</td>
    </tr>
    <tr>
      <td>LayersUseType</td>  <td>A method that determines how imported objects should be assigned to layers in the target database.</td>
    </tr>
    <tr>
      <td>ImportVectorGeometry</td>  <td>A flag that determines whether the PDF geometry data types are imported (true by default).</td>
    </tr>
    <tr>
      <td>ImportSolidFills</td>  <td>A flag that determines whether all solid-filled areas are imported (true by default).</td>
    </tr>
    <tr>
      <td>ImportTrueTypeText</td>  <td>A flag that determines whether text objects that use TrueType fonts should be imported (true by default).
                                     Some symbols exported from a .pdf document may display incorrectly because the .pdf document uses symbols that the origin TrueType font does not contain. 
                                     To correctly display all symbols, switch on the ImportTrueTypeTextAsGeometry option for the import process.</td>
    </tr>
    <tr>
      <td>ImportWidgets</td>  <td>A flag that determines whether the widgets (text fields, buttons etc.) data types are imported. Widgets are imported as a set of geometric objects, 
                                     solid-filled objects, images and text, so enabling options to import corresponding objects affects widget imports. By default the property is equal to true.</td> 
    </tr>
    <tr>
      <td>ImportRasterImages</td>  <td>A flag that determines whether raster images are imported by saving them as .png files and attaching them to the current drawing (true by default).</td> 
    </tr>
    <tr>
      <td>ImportGradientFills</td>  <td>A flag that determines whether shaded objects are imported as images by saving them as .png files and attaching them to the current drawing (true by default). </td>
    </tr>
    <tr>
      <td>ImportAsBlock</td>  <td>A flag that determines whether the .pdf file is imported as a block, not as separate objects (false by default).</td>
    </tr>
    <tr>
      <td>JoinLineAndArcSegments</td>  <td>A flag that determines whether contiguous segments are joined into a polyline if it is possible (true by default).</td>
    </tr>
    <tr>
      <td>ConvertSolidsToHatches</td>  <td>A flag that determines whether 2D solid objects are converted into solid-filled hatches (true by default).</td>
    </tr>
    <tr>
      <td>ApplyLineweight</td>  <td>A flag that determines whether lineweight properties of the imported objects remain (if true) or are ignored (if false). By default the property is equal to true.</td>
    </tr>
    <tr>
      <td>ImportTrueTypeTextAsGeometry</td>  <td>A flag that determines whether text objects that use TrueType fonts are imported as polylines and solid-filled hatches (false by default).
                                     To import text as geometry, switch on the ImportVectorGeometry and ImportSolidFills import options.</td>
    </tr>
    <tr>
      <td>Scaling</td>  <td>Specifies the scaling factor for imported objects (equal to 1.0 by default).</td>
    </tr>
    <tr>
      <td>Rotation</td>  <td>Specifies the rotation angle for imported objects (equal to 0.0 by default).</td>
    </tr>
    <tr>
      <td>InsertionPointX</td>  <td>An X-coordinate of the imported PDF content location relative to the location of the current UCS (equal to 0.0 by default).</td>
    </tr>
    <tr>
      <td>InsertionPointY</td>  <td>A Y-coordinate of the imported PDF content location relative to the location of the current UCS (equal to 0.0 by default).</td>
    </tr>
    <tr>
      <td>UseProgressMeter</td>  <td>A flag that determines whether a progress meter is used for the import (true by default). Using the progress meter can reduce performance.</td>
    </tr>
    <tr>
      <td>UseGeometryOptimization</td>  <td>A flag that determines whether a geometry optimization algorithm is used for the import (true be default).</td>
    </tr>
    <tr>
      <td>ImportType3AsTrueTypeText</td>  <td>A flag that determines whether text objects that use Type3 fonts are imported as objects that use TrueType fonts (false by default).
                                     Some symbols exported from a .pdf document may display incorrectly because the .pdf document uses Type3 font glyphs, which the origin TrueType font does not contain.</td>
    </tr>
    <tr>
      <td>UseRgbColor</td>  <td>A flag that determines whether RGB colors are used or colors are selected from the palette, if possible (false by default).</td>
    </tr>
    <tr>
      <td>ImportInvalidTTTextAsGeometry</td>  <td>A flag that determines whether text objects that use invalid TrueType fonts are imported as polylines and solid-filled hatches (true by default).</td>
    </tr>
    <tr>
      <td>UseClipping</td>  <td>A flag that determines whether clipping support is used at import (false by default).</td>
    </tr>
    <tr>
      <td>UsePageBorderClipping</td>  <td>A flag that determines whether clipping support is used at the border of the page. Only affects if UseClipping is used (false by default).</td>
    </tr>
    <tr>
      <td>UseImageClipping</td>  <td>A flag that determines whether image clipping support is used at import. The image is modified on import, so that the clipped part of the image 
                                     becomes transparent. Only affects if UseClipping is used (false by default).</td>
    </tr>
    <tr>
      <td>TakeAddMeasurementFactors</td>  <td>A flag that determines whether additional measurement factors are used for the pdf page (true by default).</td>
    </tr>
    <tr>
      <td>CombineTextObjects</td>  <td>A flag that determines whether text objects that use the same font and are on the same line are combined (false by default).</td>
    </tr>
    <tr>
      <td>CharSpaceFactor</td>  <td>Specifies the factor for the width of the space between characters in the word. If the distance between the test objects in the string is less
                                     than the width of the space taken from the font metric multiplied by this factor, the text objects are combined into one word. 
                                     Only affects if CombineTextObjects is used (equal to 0.6 by default).</td>
    </tr>
    <tr>
      <td>SpaceFactor</td>  <td>Defines the factor for the width of the space between words on a line. If the distance between the test objects in the string is 
                                     greater than the width of the space between characters in the word (specified by CharSpaceFactor), but less than the width of the 
                                     space taken from the font metrics multiplied by this factor, the text objects are combined into one word. 
                                     Only affects if CombineTextObjects is used (equal to 1.5 by default).</td>
    </tr>
    <tr>
      <td>UsePdfTransparency</td>  <td>A flag that determines whether transparency for geometric objects is used from a PDF stream (if true) or set to 50%  for objects that will 
                                     be imported as solid-filled areas (if false). By default the property is equal to false.</td>
    </tr>
    <tr>
      <td>ImportHyperlinkMethod</td>  <td>Defines how hyperlinks are imported. Can accept the following values: 
                                     0 - Import as a hyperlink (OdDbHyperlink) belonging to an Entity. Hyperlinks are assigned to Entities if the hyperlink's bounding box contains
                                     an entity bounding box, and the hyperlink with the smallest bounding box is selected. The others hyperlinks are ignored.
                                     1 - Hyperlinks are imported as transparent OdDbHatch objects with assigned OdDbHyperlinks.In this case all hyperlinks are imported over other 
                                     objects and according to the drawing order.
                                     2 - Mixed method. Hyperlinks are imported as in mode "0". If the hyperlink does not match the conditions of this mode, it is imported as a 
                                     transparent Hatch object with OdDbHyperlinks assigned to it.
                                     The default value is 0.</td>
    </tr>
    <tr>
      <td>ConsiderINSUNITS</td>  <td>A flag that determines whether INSUNITS value is used when importing PDF. If true then all imported object dimensions are scaled according to 
                                     the value from INSUNITS. By default the property is false.</td>
    </tr>
    <tr>
      <td>Type3TextDefaultFont</td>  <td>The name of the font that is used when importing test objects that use the Type3 font. Can take the value of TrueType typeface name or 
                                     Uni-font filename. By default the property is empty value.</td>
    </tr>
    <tr>
      <td>ImagePath</td>  <td>String parameter that determines the directory to save the images when importing PDF. If not specified, the value of the PDFIMPORTIMAGEPATH
                                     system variable is used; if not specified and the system variable, the images are saved in the application's temporary directory. 
                                     By default, the property is an empty value.</td>
    </tr>
    <tr>
      <td>ExtractEmbeddedFonts</td> <td>A flag that determines whether support for extracting embedded fonts is used when importing, if possible (default is false).</td>
    </tr>
    <tr>
      <td>EmbeddedFontsPath</td>  <td>String parameter that determines the directory to extract the embedded fonts when importing PDF. If not specified, the fonts are 
                                     saved in the application's temporary directory. By default, the property is an empty value.</td>
    </tr>
    <tr>
      <td>TryFixUnicodeTable</td>  <td>A flag that determines whether ToUnicode table fixing is used for CID and Type3 fonts when importing, if possible (default is false).</td>
    </tr>
  </table>
  */
  virtual OdRxDictionaryPtr properties() = 0;

  /** \details
  Sets a function to select the preferred font.
  \param callback [in] A pointer to the function for selecting the preferred font.
  \remarks
  If the font name is changed using PreferableFontCallback, this takes precedence over the Type3TextDefaultFont option.
  */
  virtual void setPreferableFontCallback(PreferableFontCallback callback) = 0;
};

/** \details
A data type that represents a smart pointer to a <link OdPdfImport, PDF importer> object.
*/
typedef OdSmartPtr<OdPdfImport> OdPdfImportPtr;

/** \details
An abstract class that provides an interface for the PDF import module. 
<group OdPdfImport_Classes> 
*/
class OdPdfImportModule : public OdRxModule
{
public:
    
    /** \details
    Creates an instance of the PDF import module if it was not created yet; otherwise, provides access to the previously created module.
    \returns Returns a smart pointer to the <link OdPdfImportModule, PDF import module>. 
    */
    virtual OdPdfImportPtr create () = 0;
    
};

/** \details
A data type that represents a smart pointer to a <link OdPdfImportModule, PDF import module>.
*/
typedef OdSmartPtr<OdPdfImportModule> OdPdfImportModulePtr;


/** \details 
Creates an instance of the <link OdPdfImportModule, PDF import module> class.
\returns Returns a smart pointer to the <link OdPdfImportModule, PDF import module>. 
<group OdPdfImport_Classes>
*/
inline OdPdfImportPtr createImporter()
{
     OdPdfImportModulePtr pModule = ::odrxDynamicLinker()->loadApp(OdPdfImportModuleName);
     if ( !pModule.isNull() ) return pModule->create ();
     return (OdPdfImport*)0;
}

//DD:EXPORT_OFF

#endif // _PDFIMPORT_INCLUDED_
