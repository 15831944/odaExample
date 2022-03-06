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

#ifndef _ODNWHOSTAPPSERVICES_H_
#define _ODNWHOSTAPPSERVICES_H_

#include "TD_PackPush.h"

#include "DbBaseHostAppServices.h"
#include "NwExport.h"
#include <map>
#include "NwOpenOptions.h"

/** \details
    This class is for BimNv-specific progress metering.

    Corresponding C++ library: TNW_Db.

    \remarks
    This class receives progress notifications during various database operations such
    as loading and saving a file.

    Calls to an instance of this class always come in the following order:

    1.  setLimit() (called once).
    2.  start() (called once).
    3.  meterProgress() (called repeatedly).
    4.  stop() (called once).

    <group OdNw_Classes>
*/
class NwDbHostAppProgressMeter : public OdDbHostAppProgressMeter
{
public:
  /** \details
    Default constructor. Creates a new NwDbHostAppProgressMeter object.
  */
  NwDbHostAppProgressMeter();

  // OdDbHostAppProgressMeter overridden
  
  /** \details
    Notification function called to initialize this ProgressMeter object.
    \param displayString [in]  String to be displayed.
  */
  virtual void start(const OdString& displayString = OdString::kEmpty);
  
  /** \details
    Notification function called to terminate this ProgressMeter object.
  */
  virtual void stop();
  
  /** \details
    Notification function called to increment this ProgressMeter object.

    \remarks
    The completion percentage can be calculated by dividing the number of times
    this function is called by the value set by setLimit().

    \remarks
    Throwing an exception indicates that the operation associated with this ProgressMeter object
    should be stopped.
  */
  virtual void meterProgress();
  
  /** \details
    Notification function called to specify the maximum number of times this
    ProgressMeter object is incremented.

    \param max [in]  Maximum meterProgress calls.
  */
  virtual void setLimit(int max);

  /** \details
    Controls the display of this ProgressMeter.
    \param disable [in]  Output disable flag.
  */
  void disableOutput(bool disable); 
  
  /** \details
    Sets the prefix string for this ProgressMeter.
    \param prefix [in] Prefix string.
  */
  void setPrefix(const OdString& prefix); 

protected:
  OdString m_Prefix;
  long m_MeterLimit, m_MeterCurrent, m_MeterOld;
  bool m_disableOutput;
};

/** \details
    This class is for platform-specific operations within ODA BimNv SDK.

    Corresponding C++ library: TNW_Db

    <group OdNw_Classes>
*/
class NWDBEXPORT OdNwHostAppServices : public OdDbBaseHostAppServices
{
  ODRX_DECLARE_MEMBERS(OdNwHostAppServices);
public:

  /** \details
    Default constructor. Creates a new HostAppServices object.
  */
  OdNwHostAppServices();
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwHostAppServices();

  /** \details
    Returns the fully qualified path to the specified file.

    \param filename [in]  Name of the file to find.
    \param pDb [in]  Pointer to the database context.
    \param hint [in]  Hint that indicates the type of file that is required.

    \remarks
    Returns an empty string if the file is not found.

    This function is called by ODA BimNv SDK when access is needed to a
    file, such as a font file, a template file, etc.

    pDb == 0 specifies that this file search is not related to a database.

    If pDb != 0, call pDb->getFilename() to determine the path to the .dwg
    file associated with the database.

    The typical search order is as follows:

    1.  The filename itself.
    2.  The current directory.
    3.  The drawing directory (for SHX font, image, and external reference files).
    4.  The directories listed in the "ACAD" environment variable.
    5.  The Windows fonts directory (only for TTF fonts on Windows).

    The hint must be one of the following:

    <table>
    Name                    Value     Description Extension
    kDefault                0         Any file.                         any
    kFontFile               1         Can be either a SHX or TTF file.    SHX or TTF
    kCompiledShapeFile      2         SHX file.                         SHX
    kTrueTypeFontFile       3         TTF file.                         TTF
    kEmbeddedImageFile      4         Image file.                       ISM
    kXRefDrawing            5         Drawing template file.            DWT
    kPatternFile            6         Pattern file (PAT).               PAT
    kTXApplication          7         ODA BimNv SDK Xtension file.      TX
    kFontMapFile            8         FontMap file.                     FMP
    kUnderlayFile           9         Underlay file.
    kTextureMapFile        10
    </table>

    \note
    The client application can return any non-null string, so long as
    the application can handle that string in OdDbSystemServices::createFile.
  */
  virtual OdString findFile(
    const OdString& filename,
    OdDbBaseDatabase* pDb = 0,
    FindFileHint hint = kDefault);

  /** \details
    Returns an instance of an OdDbHostAppProgressMeter.
  */
  virtual OdDbHostAppProgressMeter* newProgressMeter();

  /** \details
    Notification function called whenever ODA BimNv SDK no longer needs the specified
    ProgressMeter object.

    \param pProgressMeter [in]  Pointer to the ProgressMeter object no longer needed by ODA BimNv SDK.

    \note
    The default implementation of this function does nothing but return.
  */
  virtual void releaseProgressMeter(
    OdDbHostAppProgressMeter* pProgressMeter);

  /** \details
    Returns the static OdRxClass description object associated with the database.

    \remarks
    Returns OdNwDatabase::desc();.
  */
  virtual OdRxClass* databaseClass() const;

  /** \details
    Creates an instance of an OdNwDatabase object.

    \param createDefault [in]  If and only if true, the newly created database
            is populated with the default set of objects (one sheet element with root model item, background element and current viewpoint).

    \remarks
    Returns the newly created database.

    This HostAppServices object will be associated with the newly created database.
  */
  virtual OdSmartPtr<class OdNwDatabase> createDatabase(bool createDefault = true) const;

  /** \details
    Loads the contents of the specified StreamBuf or NWD file into the
    database with which this HostAppServices object is associated.

    \param pStreamBuf [in]  Pointer to the StreamBuf object from which the data is to be read.
    \param partialLoad [in]  Controls the partial loading of NWD files.

    \remarks
    Returns a SmartPointer to the database containing the contents of the file.
  */
  virtual OdSmartPtr<OdNwDatabase> readFile(
    OdStreamBuf* pStreamBuf,
    bool partialLoad = true);

  /** \details
    \param filename [in]  Path of the NWD file to read.
  */
  virtual OdSmartPtr<OdNwDatabase> readFile(
    const OdString& filename,
    bool partialLoad = true);

  /** \details
    Returns the name of the client program.

    \remarks
    This function is typically used for populating "About" information.

    \note
    The default implementation of this function returns oddbGetLibraryInfo()->getLibName().
  */
  virtual const OdString program();

  /** \details
    Returns the name of the client product.

    \remarks
    This function is typically used for populating "About" information.

    \note
    The default implementation of this function returns program().
  */
  virtual const OdString product();

  /** \details
    Returns the name of the client company.

    \remarks
    This function is typically used for populating "About" information.

    \note
    The default implementation of this function returns oddbGetLibraryInfo()->getCompanyName().
  */
  virtual const OdString companyName();

  /** \details
    Returns the name of the client product code.

    \remarks
    This function is typically used for populating "About" information.

    prodcode() returns one of the following:

    <table>
    Name          Value   Description
    kProd_ACAD    1       Plain
    kProd_LT      2       Lite
    kProd_OEM     3       OEM
    kProd_OdDb    4       ..
    </table>

    \note
    The default implementation of this function returns kProd_OEM and should not be overridden.
  */
  virtual ProdIdCode prodcode();

  /** \details
    Returns the release major and minor version string of the client application.

    \note
    The default implementation of this function returns oddbGetLibraryInfo()->getLibVersion().
  */
  virtual const OdString releaseMajorMinorString();

  /** \details
    Returns the release major version of the client application.

    \note
    The default implementation of this function returns TD_MAJOR_VERSION.
  */
  virtual int releaseMajorVersion();

  /** \details
    Returns the release minor version of the client application.

    \note
    The default implementation of this function returns TD_MINOR_VERSION.
  */
  virtual int releaseMinorVersion();

  /** \details
    Returns the release version string of the client application.

    \note
    The default implementation of this function returns oddbGetLibraryInfo()->getLibVersion().
  */
  virtual const OdString versionString();

  /** Description:
    Returns the font file to be used when a given font file is not found by ODA BimNv.

    \note
    The default implementation of this function returns an empty string.
  */
  virtual OdString getAlternateFontName() const;

  /** \details
    Returns the name of the font mapping file used by the getPreferableFont function.

    \sa
    Font Handling

    \note
    The default implementation of this function does nothing but return an empty string.
    It will be fully implemented in a future release.
  */
  virtual OdString getFontMapFileName() const;

  /** \details
    Returns the preferable font name for the specified font name and type.


    \param fontName [in]  Font name.
    \param fontType [in]  Font type.

    \remarks
    This function is called as the first step in the process of resolving a font file.
    The default implementation tries to locate a font mapping file by calling
    getFontMapFileName, and substitutes the font name based on the contents of this
    file.

    fontType must be one of the following:

    <table>
    Name                    Value    Description
    kFontTypeUnknown        0        Unknown.
    kFontTypeShx            1        SHX font.
    kFontTypeTrueType       2        TrueType font.
    kFontTypeShape          3        Shape file.
    kFontTypeBig            4        BigFont file.
    </table>

    \sa
    Font Handling
  */
  virtual OdString getPreferableFont(
    const OdString& fontName,
    OdFontType fontType);

  /** \details
    Returns the font to be used when the specified font is not found.

    \param fontName [in]  Font name.
    \param fontType [in]  Font type.

    \remarks
    fontType must be one of the following:

    <table>
    Name                    Value    Description
    kFontTypeUnknown        0        Unknown.
    kFontTypeShx            1        SHX font.
    kFontTypeTrueType       2        TrueType font.
    kFontTypeShape          3        Shape file.
    kFontTypeBig            4        BigFont file.
    </table>

    The default implementation of this function calls getAlternateFontName for
    fonts that are not of type kFontTypeShape or kFontTypeBig. When they are,
    an empty string is returned.

    Client code can override this function to perform a custom substitution
    for these types of fonts.

    \sa
    Font Handling
  */
  virtual OdString getSubstituteFont(
    const OdString& fontName,
    OdFontType fontType);

  /** \details
    Returns the gsBitmapDevice associated with this HostAppServices object.

    \param pViewObj [in]  OdAbstractViewPE-compatible object (OdGsView, OdDbViewport, etc.).
    \param pDb [in]  Pointer to the database context.
    \param flags [in]  Bitmap device flags.
  */
  virtual OdGsDevicePtr gsBitmapDevice(OdRxObject* pViewObj = NULL,
                                       OdDbBaseDatabase* pDb = NULL,
                                       OdUInt32 flags = 0);

  /** \details
    Returns the OdDbHostAppServices object used for reading files.
  */
  virtual OdDbBaseHostAppServices* getDbHostAppServices() const;

  /** \details
     Controls display of this ProgressMeter.

    \param disable [in] Indicates whether this ProgressMeter is to be disabled.
  */
  void disableProgressMeterOutput(bool disable);

  /** \details
    Sets the directory path for textures.

    \param path [in] Directory's path.
    \param rename_path [in] Boolean flag for renaming the texture directory's path.
  */
  void setTextureDirectoryPath(const OdString& path, bool rename_path);
  
  /** \details
    Returns how multi-threading is used (bit-coded). See OdDb::MultiThreadedMode.
   \remarks
   
    The returned value can be one of the following:
    
  <table>
   <b>Value</b>   <b>Description</b>
   0              Multi-threaded file loading and regeneration are disabled.
   1              Multi-threaded file loading is enabled.
   2              Multi-threaded regeneration is enabled.
   3              Multi-threaded file loading and regeneration are enabled.
  </table>
  */
  virtual OdInt16 getMtMode() const;

  /** \details
    Sets how multi-threading is used (bit-coded). See OdDb::MultiThreadedMode.

    \param nMode [in] MtMode controls.
      <table>
       <b>Value</b>   <b>Description</b>
       0              Multi-threaded file loading and regeneration are disabled.
       1              Multi-threaded file loading is enabled.
       2              Multi-threaded regeneration is enabled.
       3              Multi-threaded file loading and regeneration are enabled.
      </table>
  */
  void setMtMode(OdInt16 nMode);
  
  /** \details
    Sets the database settings before reading the file.

    \param option [in] Field name to set.
    \param value [in] Field value to set.

    \remarks
    The option must be one of the following:

    <table>
    Name                           Value    Description
    kOptionCacheGeometry           0x00     Cache geometry.
    kOptionDrawParametricGeometry  0x01     Draw parametric geometry such as circles and cylinders.
    </table>
  */
  void setOption(NwOpenOptions::Enum option, const OdInt32 value);
    
  /** \details
    Gets the value of a database field to set.

    \param option [in] Field name to set.

    \returns OdInt32 with the set field value.

    \remarks
    The option must be one of the following:

    <table>
    Name                           Value    Description
    kOptionCacheGeometry           0x00     Cache geometry.
    kOptionDrawParametricGeometry  0x01     Draw parametric geometry such as lines, circles, and cylinders.
    </table>
  */
  OdInt32 getOption(NwOpenOptions::Enum option);

protected:
  OdMutex                         m_TextureDirectoryMutex;
  OdString                        m_TextureDirectoryPath;
  NwDbHostAppProgressMeter        m_progressMeter;
  OdInt16                         m_MTMode;
  std::map<NwOpenOptions::Enum, OdInt32>   m_openOptions;
};

typedef OdSmartPtr<OdNwHostAppServices> OdNwHostAppServicesPtr;

#include "TD_PackPop.h"

#endif // _ODNWHOSTAPPSERVICES_H_
