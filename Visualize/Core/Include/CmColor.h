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


#ifndef ODA_CM_COLOR
#define ODA_CM_COLOR

#include "OdString.h"
#include "Gi/Gi.h"
#include "CmColorBase.h"
#include "DbExport.h"

class OdCmEntityColor;
class OdTvDbDwgFiler;
class OdTvDbDxfFiler;
class OdTvDbAuditInfo;

#include "TD_PackPush.h"

class OdTvDbObject;
class OdTvDbFiler;

/** \details
    <group OdCm_Classes>

    This class implements Color object that represents the unnamed and named colors
    specified by the byLayer, byBlock, byColor, byACI, byPen, Foreground, byDgnIndex, or None 
    color methods.

    The OdCmEntityColor class,  the OdCmColorBase class
*/
class TOOLKIT_EXPORT OdTvCmColor : public OdCmColorBase
{
public:
  /** \details
    Default constructor. Sets the color to that of the layer.

    \remarks
      Specifies that the color method used by this color is kByLayer.
  */
  OdTvCmColor();
  
  /** \details
    Copy constructor. Sets the color according to a parameter.

    \param color [in] New color as OdTvCmColor.
  */
  OdTvCmColor(
    const OdTvCmColor& color);
  
  /** \details
    Constructor. Sets the color according to a parameter.

    \param color [in] New color as OdCmColorBase object.
  */
  OdTvCmColor(
    const OdCmColorBase& color);
  
  /** \details
    Constructor. Sets the color according to a color method.

    \param color [in] Color method.
    \remarks
    The color method can be one of the following:
    
    <table>
    <b>Name</b>    <b>Value</b>    <b>Description</b>
    kByLayer       0xC0            Color is specified by the layer object on which the object resides.
    kByBlock       0xC1            Color is specified by the block reference color.
    kByColor       0xC2            Color is specified by an RGB value.
    kByACI         0xC3            Color is specified by an index (ACI) of a color palette.
    kByPen         0xC4            Color is specified by an index of a pen color table.
    kForeground    0xC5            Color is the same as the foreground color.
    kByDgnIndex    0xC7            Color is specified by an index of a .dgn color table.
    kNone          0xC8            Color is absent (object is clear).
    </table>
  */
  OdTvCmColor(
    OdCmEntityColor::ColorMethod color);
    
  /** \details
    Assignment operator. Assigns values of the rhs parameter to the lhs parameter.

    \param color [in] Color as OdCmdColor object.
    \returns OdTvCmColor object with values identical to those of the parameter.
    \remarks
      Values that are being assigned are RGBM, colorName and bookName. 
  */
  OdTvCmColor& operator=(
    const OdTvCmColor& color);
    
  /** \details
    Assignment operator. Assigns values of the rhs parameter to the lhs parameter.

    \param color [in] Color as OdCmColorBase object.
    \returns OdTvCmColor object with values identical to those of the parameter.
  */
  OdTvCmColor& operator=(
    const OdCmColorBase& color);
    
  /** \details
    Empty destructor.
  */
  ~OdTvCmColor();

  /** \details
    Compares two database color objects using their integer values together with their color names
    and returns true when their values are equal, or false when their values are not equal.

    \param color [in] Color as OdTvCmColor.
    \returns true if the objects are equal, false - otherwise.
  */
    bool operator ==(
    const OdTvCmColor& color) const;
    
  /** \details
    Compares an OdTvCmColor object and OdCmColorBase object using their integer values together with 
    their color names and returns true when their values are equal, or false when their values are 
    not equal. For comparison the OdCmColorBase object is converted to OdTvCmColor.

    \param color [in] Color as OdCmColorBase object.
    \returns true if the objects are equal, false - otherwise.
  */
  bool operator ==(
    const OdCmColorBase& color) const;

  /** \details
    Compares two database color objects using their integer values together with their color names
    and returns true when their values are not equal, or false when their values are equal.

    \param color [in] Color as OdTvCmColor.
    \returns true if the objects are not equal, false - otherwise.
  */
    bool operator !=(
    const OdTvCmColor& color) const;

  /** \details
    Compares two color objects as OdTvCmColor and OdCmColorBase their integer values together with their color names
    and returns true when their values are not equal, or false when their values are equal.
    For comparison the OdCmColorBase object is converted to OdTvCmColor.
  
    \param color [in] Color as OdCmColorBase.
    \returns true if the objects are not equal, false - otherwise.
  */
  bool operator !=(
    const OdCmColorBase& color) const;
  
  /** \details
    Returns the description string of the database color object.
  */
  OdString getDescription() const;

  /** \details
    Returns the explanation string of the database color object.
  */
  OdString getExplanation() const;

  /** \details
    Returns the color method of this color.

    \remarks
    The color method can be one of the following:

    <table>
    <b>Name</b>    <b>Value</b>    <b>Description</b>
    kByLayer       0xC0            Color is specified by the layer object on which the object resides.
    kByBlock       0xC1            Color is specified by the block reference color.
    kByColor       0xC2            Color is specified by an RGB value.
    kByACI         0xC3            Color is specified by an index (ACI) of a color palette.
    kByPen         0xC4            Color is specified by an index of a pen color table.
    kForeground    0xC5            Color is the same as the foreground color.
    kByDgnIndex    0xC7            Color is specified by an index of a .dgn color table.
    kNone          0xC8            Color is absent (object is clear).
    </table>
  */
  virtual OdCmEntityColor::ColorMethod colorMethod() const;

  /** \details
    Sets a color method for this color.

    \param colorMethod [in] Color method. Possible values are listed below.
    \remarks
    The color method can be one of the following:

    <table>
    <b>Name</b>    <b>Value</b>    <b>Description</b>
    kByLayer       0xC0            Color is specified by the layer object on which the object resides.
    kByBlock       0xC1            Color is specified by the block reference color.
    kByColor       0xC2            Color is specified by an RGB value.
    kByACI         0xC3            Color is specified by an index (ACI) of a color palette.
    kByPen         0xC4            Color is specified by an index of a pen color table.
    kForeground    0xC5            Color is the same as the foreground color.
    kByDgnIndex    0xC7            Color is specified by an index of a .dgn color table.
    kNone          0xC8            Color is absent (object is clear).
    </table>
  */
  virtual void setColorMethod(
    OdCmEntityColor::ColorMethod colorMethod);

  /** \details
    Checks if the color is specified by an RGB value
    (color method of this color is set to "kByColor").
    

    \returns 
      true if the color method of this color is set to "kByColor", 
      false - otherwise.
  */
  virtual bool isByColor() const;

  /** \details
    Checks if the color is specified by the layer object on which the object resides
    (color method of this color is set to "kByLayer", 
    or it is set to "kByACI" and ACI color method is "kACIbyLayer").

    \returns 
      true if the color method of this color is set to "kByLayer",
      or if it is set to "kByACI" and ACI color method is "kACIbyLayer",
      false - otherwise.
  */
  virtual bool isByLayer() const;

  /** \details
    Checks if the color is specified by the block object in which the object is contained
    (color method of this color is set to "kByBlock",
    or it is set to "kByACI" and ACI color method is "kACIbyBlock").

    \returns 
      true if the color method of this color is set to "kByBlock", 
      or if it is set to "kByACI" and ACI color method is "kACIbyBlock",
      false - otherwise.
  */
  virtual bool isByBlock() const;

  /** \details
    Checks if the color is specified by an index (ACI) of a color palette 
    (color method of this color is set to "kByACI").

    \returns 
      true if the color method of this color is set to "kByACI", 
      false - otherwise.
  */
  virtual bool isByACI() const;

  /** \details
    Checks if the color is the same as the foreground color 
    (color method of this color is set to "kForeground",
    or it is set to "kByACI" and ACI color method is "kACIforeground").

    \returns 
      true if the color method of this color is set to "kForeground",
      or if it is set to "kByACI" and ACI color method is "kACIforeground",
      false - otherwise.
  */
  virtual bool isForeground() const;

  /** \details
    Checks if the color is specified by an index of a .dgn color table 
    (color method of this color is set to "kByDgnIndex").

    \returns Always false.
  */
  virtual bool isByDgnIndex() const;

  /** \details
    Checks if the color is absent 
    (color method of this color is set to "kNone",
    or it is set to "kByACI" and ACI color method is "kACInone").
    
    \returns 
      true if the color method of this color is set to "kNone",
      or if it is set to "kByACI" and ACI color method is "kACInone",
      false - otherwise.
  */
  bool isNone() const;

  /** \details
    Returns the current color value as integer.
  */
  virtual OdUInt32 color() const;

  /** \details
    Sets a color and color method from an integer value.

    \param color [in] Color value as integer.
  */
  virtual void setColor(
    OdUInt32 color);

  /** \details
    Sets color using RGB values. Color method is set to "kByColor".

    \param red [in] Red component value.
    \param green [in] Green component value.
    \param blue [in] Blue component value.
  */
  virtual void setRGB(
    OdUInt8 red, 
    OdUInt8 green, 
    OdUInt8 blue);

  /** \details
    Sets the red component of this color.

    \param red [in] Red component value.
  */
  virtual void setRed(
    OdUInt8 red);

  /** \details
    Sets the green component of this color.

    \param green [in] Green component value.
  */
  virtual void setGreen(
    OdUInt8 green);

  /** \details
    Sets the blue component of this color.

    \param blue [in] Blue component value.
  */
  virtual void setBlue(
    OdUInt8 blue);

  /** \details
    Returns the value of the red component of this color.
  */
  virtual OdUInt8 red() const;

  /** \details
    Returns the value of the green component of this color.
  */
  virtual OdUInt8 green() const;
  
  /** \details
    Returns the value of the blue component of this color.
  */
  virtual OdUInt8 blue() const;

  /** \details
    Returns the color index (ACI) of the entity color object.
        
    \remarks
      The color index can be one of the following:
     
      <table>
      Name              Value   Description
      kACIbyBlock       0       Sets the color method to byBlock.
      kACIRed           1       Red. 
      kACIYellow        2       Yellow. 
      kACIGreen         3       Green. 
      kACICyan          4       Cyan. 
      kACIBlue          5       Blue. 
      kACIMagenta       6       Magenta. 
      kACIforeground    7       Sets the color method to Foreground.
      ..                8-255   Defined by current palette.
      kACIbyLayer       256     Sets the color method to byLayer. 
      kACInone          257     Sets the color method to None.
      </table>
  */
  virtual OdUInt16 colorIndex() const;

  /** \details
    Sets the color index (ACI) of a color palette and sets the color method to byACI for the entity color object.

    \param colorIndex [in]  An integer value that is the index of the color in a palette.
    \remarks
      The color index can be one of the following:

      <table>
      Name              Value   Description
      kACIbyBlock       0       Sets the color method to byBlock.
      kACIRed           1       Red.
      kACIYellow        2       Yellow.
      kACIGreen         3       Green.
      kACICyan          4       Cyan.
      kACIBlue          5       Blue.
      kACIMagenta       6       Magenta.
      kACIforeground    7       Sets the color method to Foreground.
      ..                8-255   Defined by current palette.
      kACIbyLayer       256     Sets the color method to byLayer.
      kACInone          257     Sets the color method to None.
      </table>

      An entity does not have a color from the time it is first instantiated until it is assigned one
      or added to a database.
  */
  virtual void setColorIndex(
    OdUInt16 colorIndex);

  /** \details
    Sets the color name and the book name.

    \param colorName [in] Name of the color to be set.
    \param bookName [in] Name of the book to be set.
    \returns 
      true if the operation is complete.
      If colorName is empty, but bookName isn't - returns false.
      If colorName and bookName are empty - returns true.
    \remarks
      If colorName is empty, then current bookName will be emptied,
      and the new one will not be assigned.
  */
  virtual bool setNames(
    const OdString& colorName,
    const OdString& bookName = OdString::kEmpty);

  /** \details
    Returns the name of the current color.
  */
  virtual OdString colorName() const;

  /** \details
    Returns the current book name.
  */
  virtual OdString bookName() const;

  /**
    If colorName isn't empty, returns it as a string.
    Otherwise returns color method as a string.
  */
  virtual OdString colorNameForDisplay() const;

  /** \details
    Returns the OdCmEntityColor settings of the database color object.
  */
  OdCmEntityColor entityColor() const;

  /** \details
    Returns a dictionary key based on the color name and book name of the database color object.
   
    \remarks
    OdTvCmColor objects with color names can be stored in the form of an OdTvDbColor in a dictionary.
    getDictionaryKey() returns the key for that dictionary.
  */
  OdString getDictionaryKey() const;
  
  /** \details
    Sets the book name and color name for the dictionary keyword.

    \param dictionaryKey [in]  Dictionary keyword.   
    \returns
      Returns true if and only if successful.
      The dictionary key is the string that is the combination of the book name and color name joined by the dollar '$' symbol
  */
  bool setNamesFromDictionaryKey(
    const OdString& dictionaryKey);

  /** \details
    Reads the .dwg file format data of this object from the specified file.
       
    \param pFiler [in]  Pointer to the filer from which the data are to be read.
  */
  void dwgIn(
    OdTvDbDwgFiler* pFiler);

  /** \details
    Writes the .dwg file format data of this object to the specified filer. 
    
    \param pFiler [in]  Pointer to the filer to which the data are to be written.
  */
  void dwgOut(
    OdTvDbDwgFiler* pFiler) const;

  /** \details
    Reads the DXF format data of this object from the specified filer. 
    
    \param pFiler [in]  Pointer to the filer from which the data are to be read.
    \param groupCodeOffset [in]  Group code offset.
  */
  void dxfIn(
    OdTvDbDxfFiler* pFiler, 
    int groupCodeOffset = 0);

  /** \details
    Writes the DXF format data of this object to the specified filer. 
    
    \param pFiler [in]  Pointer to the filer to which the data are to be written.
    \param groupCodeOffset [in]  Group code offset.
  */
  void dxfOut(
    OdTvDbDxfFiler* pFiler, 
    int groupCodeOffset = 0) const;

  /** \details
    Perform an audit operation on this object.

    \param pAuditInfo [in]  Pointer to an AuditInfo object.
    \remarks
      When overriding this function for a custom class, first call OdCmColorBase::audit(pAuditInfo) 
      to validate the audit operation.
  */
  void audit(
    OdTvDbAuditInfo* pAuditInfo);

  /*!DOM*/
  void     dwgInAsTrueColor (
    OdTvDbDwgFiler* pFiler);

  /*!DOM*/
  void     dwgOutAsTrueColor(
    OdTvDbDwgFiler* pFiler) const;

  TOOLKIT_EXPORT_STATIC static const OdUInt16 MaxColorIndex;

private:
  enum NameFlags
  {    
    kNoNames      = 0,
    kHasColorName = 1,
    kHasBookName  = 2
  };
  OdCmEntityColor::RGBM   m_RGBM;
  OdString                m_colorName;
  OdString                m_bookName;
};

class OdTvCmTransparency
{
public:
  //DOM-IGNORE-BEGIN
  ODRX_HEAP_OPERATORS();
  //DOM-IGNORE-END

    /** \details
      Represents the transparency method.

      \sa
      <exref target="https://docs.opendesign.com/td/cm_transparency_method.html">Methods of the Transparency Definition</exref>
    */
  enum transparencyMethod
  {
    kByLayer = 0, // Use the setting for the layer.
    kByBlock = 1, // Use the setting for the block.
    kByAlpha = 2, // Use the Alpha-value in this object.
    kErrorValue = 3  // Error value.
  };

  /** \details Creates a transparency object with default properties.

    \remarks
    The default transparency method is kByLayer.
  */
  OdTvCmTransparency() { setMethod( kByLayer ); }

  /** \details Creates a transparency object and sets the specified transparency
    method for it.

    \param method [in] Transparency method.

    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_method.html">Methods of the Transparency Definition</exref>
  */
  OdTvCmTransparency( transparencyMethod method ) { setMethod( method ); }

  /** \details Creates a transparency object and sets its transparency property
    using a specified alpha value.

    \param alpha [in] An alpha value of transparency as an integer value in the
      range from 0 to 255.

    \remarks
    The transparency method is set to kByAlpha.
    Alpha = 0 corresponds to full transparency. Alpha = 255 corresponds to full opacity.

    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_alpha.html">Transparency Functionality as an Alpha-value</exref>
  */
  OdTvCmTransparency( OdUInt8 alpha ) { setAlpha( alpha ); }

  /** \details Creates a transparency object and sets its transparency property
    using a specified alpha value as a percentage.

    \param alphaPercent [in] An alpha value of transparency in percent as a
      double value in the range from 0.0 to 1.0.

    \remarks
    The transparency method is set to kByAlpha.
    Alpha = 0.0 corresponds to full transparency. Alpha = 1.0 corresponds to full opacity.

    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_alpha.html">Transparency Functionality as an Alpha-value</exref>
  */
  OdTvCmTransparency( double alphaPercent ) { setAlphaPercent( alphaPercent ); }

  /** \details Creates a copy of an existing transparency object.

    \param transparency [in] The transparency object to be copied.
  */
  OdTvCmTransparency(
    const OdTvCmTransparency& transparency ) {
    m_AM = transparency.m_AM;
  }

  OdTvCmTransparency( const OdCmTransparency& tr )
  {
    m_AM = tr.serializeOut();
  }

  operator OdCmTransparency() const
  {
    OdCmTransparency tr;
    tr.serializeIn( m_AM );
    return tr;
  }

  //DOM-IGNORE-BEGIN
  ~OdTvCmTransparency() {}
  //DOM-IGNORE-END

    /** \details
      Copies a transparency object specified on the right of the operator to the transparency object specified on the left.

      \sa
      <exref target="https://docs.opendesign.com/td/cm_transparency_sample.html">Example of Working with Transparency</exref>

      <exref target="https://docs.opendesign.com/td/cm_transparency_integer.html">Transparency Functionality as an Integer-value</exref>
    */
  OdTvCmTransparency& operator=(
    const OdTvCmTransparency& transparency ) {
    m_AM = transparency.m_AM; return *this;
  }

  /** \details
    Compares two transparency objects as integer values, and returns true when
    their values are equal or false when their values are not equal.

    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_sample.html">Example of Working with Transparency</exref>

    <exref target="https://docs.opendesign.com/td/cm_transparency_integer.html">Transparency Functionality as an Integer-value</exref>
  */
  bool operator==(
    const OdTvCmTransparency& transparency ) const {
    return ( m_AM == transparency.m_AM );
  }

  /** \details
    Compares two transparency objects as integer values, and returns true when
    their values are not equal or false when their values are equal.

    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_sample.html">Example of Working with Transparency</exref>

    <exref target="https://docs.opendesign.com/td/cm_transparency_integer.html">Transparency Functionality as an Integer-value</exref>
  */
  bool operator!=(
    const OdTvCmTransparency& transparency ) const {
    return ( m_AM != transparency.m_AM );
  }

  /** \details
    Sets the alpha value and switches the transparency method to kByAlpha for the transparency object.

    \param alpha [in]  Alpha value as an integer value in the range 0 to 255.

    \remarks
    An alpha value defines the degree of transparency.
    Alpha = 0 corresponds to full transparency. Alpha = 255 corresponds to full opacity.

    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_sample.html">Example of Working with Transparency</exref>

    <exref target="https://docs.opendesign.com/td/cm_transparency_alpha.html">Transparency Functionality as an Alpha-value</exref>
  */
  void setAlpha(
    OdUInt8 alpha )
  {
    m_AM = ( (OdUInt32)kByAlpha << 24 ) | alpha;
  }

  /** \details
    Returns the alpha value in the range from 0 to 255 of the transparency object.

    \remarks
    An alpha value defines the degree of transparency.
    Alpha = 0 corresponds to full transparency. Alpha = 255 corresponds to full opacity.

    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_sample.html">Example of Working with Transparency</exref>

    <exref target="https://docs.opendesign.com/td/cm_transparency_alpha.html">Transparency Functionality as an Alpha-value</exref>
  */
  OdUInt8 alpha() const
  {
    if( !isByAlpha() )
      return 255;
    return OdUInt8( m_AM & 0xFF );
  }

  /** \details
    Sets the alpha value as a percentage and switches the transparency method to
    kByAlpha for the transparency object.

    \param alphaPercent [in]  Alpha as a double value in the range from 0.0 to 1.0.

    \remarks
    An alpha value defines the degree of transparency.
    Alpha = 0.0 corresponds to full transparency. Alpha = 1.0 corresponds to full opacity.

    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_sample.html">Example of Working with Transparency</exref>

    <exref target="https://docs.opendesign.com/td/cm_transparency_alpha.html">Transparency Functionality as an Alpha-value</exref>
  */
  void setAlphaPercent(
    double alphaPercent )
  {
    if( alphaPercent < 0.0 )
      setAlpha( 0 );
    else if( alphaPercent > 1.0 )
      setAlpha( 0xFF );
    else
      setAlpha( (OdUInt8)( alphaPercent * 255 ) );
  }

  /** \details
    Returns the alpha value in the range from 0.0 to 1.0 of the transparency object.

    \remarks
    An alpha value defines the degree of transparency.
    Alpha = 0.0 corresponds to full transparency. Alpha = 1.0 corresponds to full opacity.

    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_sample.html">Example of Working with Transparency</exref>

    <exref target="https://docs.opendesign.com/td/cm_transparency_alpha.html">Transparency Functionality as an Alpha-value</exref>
  */
  double alphaPercent() const
  {
    return (double)alpha() / 255;
  }

  /** \details
    Returns the transparency method of the transparency object as a value of the transparencyMethod enumeration.

    \remarks
    The transparency method can be a one of the following:

    <table>
    <b>Name</b>    <b>Value</b>    <b>Description</b>
    kByLayer       0               Transparency is specified by the layer object that the object is assigned to.
    kByBlock       1               Transparency is specified by the block object that the object is contained in.
    kByAlpha       2               Transparency is specified by an alpha value.
    </table>

    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_sample.html">Example of Working with Transparency</exref>

    <exref target="https://docs.opendesign.com/td/cm_transparency_method.html">Methods of the Transparency Definition</exref>
  */
  transparencyMethod method() const
  {
    return transparencyMethod( OdUInt8( m_AM >> 24 ) );
  }

  /** \details
    Sets the transparency method for the transparency object.

    \param method [in]  Transparency method as the transparencyMethod enumeration.

    \remarks
    The transparency method can be one of the following:

    <table>
    <b>Name</b>    <b>Value</b>    <b>Description</b>
    kByLayer       0               Transparency is specified by the layer object that the object is assigned to.
    kByBlock       1               Transparency is specified by the block object that the object is contained in.
    kByAlpha       2               Transparency is specified by an alpha value.
    </table>

    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_sample.html">Example of Working with Transparency</exref>

    <exref target="https://docs.opendesign.com/td/cm_transparency_method.html">Methods of the Transparency Definition</exref>
  */
  void setMethod(
    transparencyMethod method )
  {
    m_AM = (OdUInt32)method << 24;
  }

  /** \details
    Checks whether the transparency method is byAlpha for the transparency
    object and returns true if and only if the transparency method is set to
    kByAlpha, otherwise it returns false.

    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_sample.html">Example of Working with Transparency</exref>

    <exref target="https://docs.opendesign.com/td/cm_transparency_method.html">Methods of the Transparency Definition</exref>
  */
  bool isByAlpha() const { return ( method() == kByAlpha ); }

  /** \details
    Checks whether the transparency method is byBlock for the transparency
    object and returns true if and only if the transparency method is set to
    kByBlock, otherwise it returns false.

    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_sample.html">Example of Working with Transparency</exref>

    <exref target="https://docs.opendesign.com/td/cm_transparency_method.html">Methods of the Transparency Definition</exref>
  */
  bool isByBlock() const { return ( method() == kByBlock ); }

  /** \details
    Checks whether the transparency method is byLayer for the transparency
    object and returns true if and only if the transparency method is set to
    kByLayer, otherwise it returns false.

    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_sample.html">Example of Working with Transparency</exref>

    <exref target="https://docs.opendesign.com/td/cm_transparency_method.html">Methods of the Transparency Definition</exref>
  */
  bool isByLayer() const { return ( method() == kByLayer ); }

  /** \details
    Checks whether the transparency method is an error value for the transparency
    object and returns true if and only if the transparency method is set to
    kErrorValue, otherwise it returns false.

    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_sample.html">Example of Working with Transparency</exref>

    <exref target="https://docs.opendesign.com/td/cm_transparency_method.html">Methods of the Transparency Definition</exref>
  */
  bool isInvalid() const { return ( method() == kErrorValue ); }

  /** \details
    Checks whether the transparency method is byAlpha and the transparency is
    set to full for this transparency object. It returns true if and only if the
    transparency method is set to kByAlpha and Alpha = 0, otherwise it returns
    false.

    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_sample.html">Example of Working with Transparency</exref>

    <exref target="https://docs.opendesign.com/td/cm_transparency_method.html">Methods of the Transparency Definition</exref>

    <exref target="https://docs.opendesign.com/td/cm_transparency_alpha.html">Transparency Functionality as an Alpha-value</exref>
  */
  bool isClear() const   { return ( method() == kByAlpha ) && ( alpha() == 0 ); }

  /** \details
    Checks whether the transparency method is byAlpha and the opacity is set to
    full for this transparency object. It returns true if and only if the
    transparency method is set to kByAlpha and Alpha = 255, otherwise it returns
    false.

    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_sample.html">Example of Working with Transparency</exref>

    <exref target="https://docs.opendesign.com/td/cm_transparency_method.html">Methods of the Transparency Definition</exref>

    <exref target="https://docs.opendesign.com/td/cm_transparency_alpha.html">Transparency Functionality as an Alpha-value</exref>
  */
  bool isSolid() const   { return ( method() == kByAlpha ) && ( alpha() == 255 ); }

  /** \details
    Returns the packed 32-bit integer value that stores the transparency method
    and transparency components.

    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_sample.html">Example of Working with Transparency</exref>

    <exref target="https://docs.opendesign.com/td/cm_transparency_method.html">Methods of the Transparency Definition</exref>

    <exref target="https://docs.opendesign.com/td/cm_transparency_integer.html">Transparency Functionality as an Integer-value</exref>
  */
  OdUInt32 serializeOut() const { return m_AM; }

  /** \details
    Sets the transparency method and transparency components as an integer value
    for the transparency object.

    \param transparency [in]  A packed 32-bit integer value that specifies the
      transparency method and transparency components.

    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_sample.html">Example of Working with Transparency</exref>

    <exref target="https://docs.opendesign.com/td/cm_transparency_method.html">Methods of the Transparency Definition</exref>

    <exref target="https://docs.opendesign.com/td/cm_transparency_integer.html">Transparency Functionality as an Integer-value</exref>
  */
  void serializeIn(
    OdUInt32 transparency ) {
    m_AM = transparency;
  }

  /** \details
    Reads from the specified .dwg filer data for this object.

    \param pFiler [in]  Pointer to the filer that the data is to be read from.
  */
  void dwgIn(
    OdDbDwgFiler* pFiler );

  /** \details
    Writes to the specified .dwg filer data of this object.

    \param pFiler [in]  Pointer to the filer that the data is to be written to.
  */
  void dwgOut(
    OdDbDwgFiler* pFiler ) const;

private:

  /** \details
    The combined value of the transparency method and transparency components.

    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_method.html">Methods of the Transparency Definition</exref>
  */
  OdUInt32 m_AM;
};



#include "TD_PackPop.h"

#endif // ODA_CM_COLOR
