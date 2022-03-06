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


///////////////////////////////////////////////////////////////////////////////
//
// PdfPublishCADDefinition.h
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PDF_PUBLISH_CADDEFINITION_INCLUDED_
#define _PDF_PUBLISH_CADDEFINITION_INCLUDED_

#include "PdfPublishCommon.h"
#include "PdfPublishBaseObject.h"
#include "DbBaseDatabase.h"


/** \details
  Contains declarations for Publish SDK.
  <group TD_Namespaces>
*/
namespace OdPdfPublish{

/** \details
  This class implements a CAD definition object in .pdf documents created with Publish SDK.
*/
class PDFPUBLISH_TOOLKIT OdCADDefinition : public OdObject
{
  //DOM-IGNORE-BEGIN
protected:
  OdCADDefinition();
  //DOM-IGNORE-END
public:

/** \details
  This class implements a wrapper interface to work with the database for the CAD definition object.
*/
  class DatabaseWrapperInterface
  {
  public:
    /** \details
      Creates a new instance of the DatabaseWrapperInterface object with default parameters.
    */
    DatabaseWrapperInterface() {}

    /** \details
      Destroys the DatabaseWrapperInterface object.
    */
    virtual ~DatabaseWrapperInterface() {}

    /** \details
      Starts the base handling operation.
      \remarks
      Can be used to open the database before publishing it.
    */
    virtual void startDatabaseHandling() = 0;

    /** \details
      Ends the base handling operation.
      \remarks
      Can be used to close the database after it is published.
    */
    virtual void endDatabaseHandling() = 0;

    /** \details
      Retrieves the database associated with the Database Wrapper object.
      \returns A pointer to the database object.
    */
    virtual OdDbBaseDatabase* getDatabase() = 0;
  };


  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdCADDefinition);
  ODRX_HEAP_OPERATORS();
  //DOM-IGNORE-END

  /** \details
    Destroys the CAD definition object.
  */
  virtual ~OdCADDefinition();

  /** \details
    Sets the source database for the CAD definition object.
    \param database [in] A pointer to a database object.
    \remarks
    Only one of the values setDatabase or setDatabaseWrapper can be used for publishing. The setDatabaseWrapper value will be reset when the source database is set.
  */
  void setDatabase(OdDbBaseDatabase *database);

  /** \details
    Sets the Database Wrapper object for the CAD definition object.
    \param database [in] A pointer to a database object.
    \remarks
    Only one of the values setDatabase or setDatabaseWrapper can be used for publishing. The setDatabase value will be reset when the Database Wrapper is set.
  */
  void setDatabaseWrapper(DatabaseWrapperInterface* database_wrapper);
  
  /** \details
    Sets the layout name for the CAD definition object.
    \param name [in] A layout name.
  */
  void setLayoutName(const OdString& name);

  /** \details
    Sets the media size for the CAD definition object.
    \param units  [in] A paper unit used for measuring the media size.
    \param width  [in] A width of the media.
    \param height [in] A height of the media.
    \remarks
    The whole drawing will be published (using its extents) and scaled to fit the specified output media size.
  */
  void setMediaSize(const Page::PaperUnits units, const double width, const double height);

  /** \details
    Sets the embedded TTF fonts usage flag value.
    \param state  [in] A new flag value.
    \remarks
    The embedded TTF fonts usage flag determines whether embedded true type fonts should be used (if the flag value is true) or not (if false).
  */
  void setEmbededTrueTypeFonts(const bool state);
  
  /** \details
    Sets the TTF fonts geometry representation flag value.
    \param state  [in] A new flag value.
    \remarks
    The TTF fonts geometry representation flag determines whether true type fonts are represented as geometry (if the flag value is true) or not (if false).
  */
  void setTrueTypeFontAsGeometry(const bool state);
  
  /** \details
    Sets the SHX fonts geometry representation flag value.
    \param state  [in] A new flag value.
    \remarks
    The SHX fonts geometry representation flag determines whether SHX fonts are represented as geometry (if the flag value is true) or not (if false).
  */
  void setSHXTextAsGeometry(const bool state);
  
  /** \details
    Sets the TTF text searchable flag value.
    \param state  [in] A new flag value.
    \remarks
    The TTF text searchable flag determines whether it is possible to search text represented with a true type font (if the flag value is true) or not (if false).
    This flag works only if the TTF fonts geometry representation flag is equal to true.
  */
  void setTextSearchable(const bool state);
  
  /** \details
    Sets a value of the flag that determines whether hyperlinks in the CAD definition object should be exported.
    \param state  [in] A new flag value.
    \remarks
    If the hyperlinks should be exported, the flag value is true, otherwise it is equal to false.
  */
  void setExportHyperlinks(const bool state);

  /** \details
    Sets the resolution for the geometry (dots-per-inch, DPI).
    \param dpi  [in] A new resolution value.
  */
  void setGeomDPI(const OdUInt32 dpi);
  
  /** \details
    Sets the resolution for monochrome images (dots-per-inch, DPI).
    \param dpi  [in] A new resolution value.
  */
  void setBWImagesDPI(const OdUInt32 dpi);
  
  /** \details
    Sets the resolution for color images (dots-per-inch, DPI).
    \param dpi  [in] A new resolution value.
  */
  void setColorImagesDPI(const OdUInt32 dpi);

  /** \details
    Sets the measuring flag value.
    \param state [in] A new flag value.
  */
  void setMeasuring(const bool state);

  /** \details
    Sets the color policy for the CAD definition object.
    \param policy  [in] A new color policy.
  */
  void setColorPolicy(const CAD::ColorPolicy policy);

  /** \details
    Sets the simple geometry optimization flag value.
    \param policy  [in] A new flag value.
  */
  void setUseSimpleGeomOptimization(const bool state);

  /** \details
    Sets the vector hidden-line removal for corresponding viewports flag value.
    \param policy  [in] A new flag value.
  */
  void setUseHLR(bool state);

  /** \details
    Sets the compression of internal PDF streams flag value.
    \param policy  [in] A new flag value.
  */
  void setUseFlateCompression(const bool state);

  /** \details
    Sets the ASCIIHex encoding of internal PDF streams flag value.
    \param policy  [in] A new flag value.
  */
  void setUseASCIIHexEncoding(const bool state);

  /** \details
    Sets the GsCache flag value.
    \param policy  [in] A new flag value.
  */
  void setUseGsCache(const bool state);

  /** \details
    Sets the multithreaded vectorization flag value.
    \param policy  [in] A new flag value.
  */
  void setUseParallelVectorization(const bool state);

  /** \details
    Sets the enable PDF layer support flag value.
    \param policy  [in] A new flag value.
  */
  void setEnableLayers(const bool state);

  /** \details
    Sets support for adding invisible layers flag value.
    \param policy  [in] A new flag value.
  */
  void setIncludeOffLayers(const bool state);

  /** \details
    Retrieves the database associated with the CAD definition object.
    \returns Returns a pointer to the database object.
  */
  OdDbBaseDatabase* getDatabase() const;

  /** \details
    Retrieves the Database Wrapper object associated with the CAD definition object.
    \returns A pointer to the database object.
  */
  DatabaseWrapperInterface* getDatabaseWrapper() const;

  /** \details
    Returns the current layout name for the CAD definition object.
    The method accepts a string value, fills it with the layout name and returns it to a calling subroutine.
    \param name [out] A placeholder for the layout name.
  */  
  void getLayoutName(OdString& name) const;

  /** \details
    Returns the current media size for the CAD definition object.
    The method fills passed values with the paper unit, width and height, then returns them to a calling subroutine.
    \param units  [out] A paper unit used for measuring the media size.
    \param width  [out] A width of the media.
    \param height [out] A height of the media.
    \remarks
    The whole drawing will be published (using its extents) and scaled to fit the specified output media size.
  */
  void getMediaSize(Page::PaperUnits& units, double& width, double& height) const;

  /** \details
    Returns the current value of the embedded TTF fonts usage flag.
    The method fills a passed boolean value with the flag value and returns it to a calling subroutine.
    \param state  [out] A placeholder for the flag value.
    \remarks
    The embedded TTF fonts usage flag determines whether embedded true type fonts should be used (if the flag value is true) or not (if false).
  */
  void getEmbededTrueTypeFonts(bool& state) const;
  
  /** \details
    Returns the current value of the TTF fonts geometry representation flag.
    The method fills a passed boolean value with the flag value and returns it to a calling subroutine.
    \param state  [out] A placeholder for the flag value.
    \remarks
    The TTF fonts geometry representation flag determines whether true type fonts are represented as geometry (if the flag value is true) or not (if false).
  */
  void getTrueTypeFontAsGeometry(bool& state) const;
  
  /** \details
    Returns the current value of the SHX fonts geometry representation flag.
    \param state  [out] A placeholder for the flag value.
    \remarks
    The SHX fonts geometry representation flag determines whether SHX fonts are represented as geometry (if the flag value is true) or not (if false).
  */
  void getSHXTextAsGeometry(bool& state) const;
  
  /** \details
    Returns the current value of the TTF text searchable flag.
    The method fills a passed boolean value with the flag value and returns it to a calling subroutine.
    \param state  [out] A placeholder for the flag value.
    \remarks
    The TTF text searchable flag determines whether it is possible to search text represented with a true type font (if the flag value is true) or not (if false).
    This flag works only if the TTF fonts geometry representation flag is equal to true.
  */
  void getTextSearchable(bool& state) const;

  /** \details
    Returns the current value of the flag that determines whether hyperlinks in the CAD definition object should be exported.
    The method fills a passed boolean value with the flag value and returns it to a calling subroutine.
    \param state  [out] A placeholder for the flag value.
    \remarks
    If the hyperlinks should be exported, the flag value is true, otherwise it is equal to false.
  */
  void getExportHyperlinks(bool& state) const;

  /** \details
    Returns the current resolution for the geometry.
    The method fills a passed value with the resolution value and returns it to a calling subroutine.
    \param dpi  [out] A placeholder for the resolution value.
  */
  void getGeomDPI(OdUInt32& dpi) const;
  
  /** \details
    Returns the current resolution for monochrome images.
    The method fills a passed value with the resolution value and returns it to a calling subroutine.
    \param dpi  [out] A placeholder for the resolution value.
  */
  void getBWImagesDPI(OdUInt32& dpi) const;
  
  /** \details
    Returns the current resolution for color images.
    The method fills a passed value with the resolution value and returns it to a calling subroutine.
    \param dpi  [out] A placeholder for the resolution value.
  */
  void getColorImagesDPI(OdUInt32& dpi) const;

  /** \details
    Returns the current measuring flag value.
    The method fills a passed boolean value with the flag value and returns it to a calling subroutine.
    \param state  [out] A placeholder for the flag value.
  */
  void getMeasuring(bool& state) const;

  /** \details
    Returns the current color policy for the CAD definition object.
    The method fills a passed value with the color policy value and returns it to a calling subroutine.
    \param policy  [out] A placeholder for the current color policy value.
  */
  void getColorPolicy(CAD::ColorPolicy& policy) const;

  /** \details
    Returns the current simple geometry optimization flag value.
    The method fills a passed boolean value with the flag value and returns it to a calling subroutine.
  \param state  [out] A placeholder for the flag value.
  */
  void getUseSimpleGeomOptimization(bool& state) const;

  /** \details
    Gets the vector hidden-line removal for corresponding viewports flag value.
    \param state  [out] A placeholder for the flag value.
  */
  void getUseHLR(bool& state) const;

  /** \details
    Gets the compression of internal PDF streams flag value.
    \param state  [out] A placeholder for the flag value.
  */
  void getUseFlateCompression(bool& state) const;

  /** \details
    Gets the ASCIIHex encoding of internal PDF streams flag value.
    \param state  [out] A placeholder for the flag value.
  */
  void getUseASCIIHexEncoding(bool& state) const;

  /** \details
    Returns the current GsCache flag value.
    The method fills a passed boolean value with the flag value and returns it to a calling subroutine.
    \param state  [out] A placeholder for the flag value.
  */
  void getUseGsCache(bool& state) const;

  /** \details
    Gets the multithreaded vectorization flag value.
    \param state  [out] A placeholder for the flag value.
  */
  void getUseParallelVectorization(bool& state) const;

  /** \details
    Gets the enable PDF layer support flag value.
    \param state  [out] A placeholder for the flag value.
  */
  void getEnableLayers(bool& state) const;

  /** \details
    Gets support for adding invisible layers flag value.
    \param state  [out] A placeholder for the flag value.
  */
  void getIncludeOffLayers(bool& state) const;
};

/** \details
  A data type that represents a smart pointer to an <link OdPdfPublish::OdCADDefinition, OdCADDefinition> object.
*/
SMARTPTR(OdCADDefinition);

}
#endif // _PDF_PUBLISH_CADDEFINITION_INCLUDED_

