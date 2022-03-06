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

#ifndef _ODTV_TRAITSDEF_H_INCLUDED_
#define _ODTV_TRAITSDEF_H_INCLUDED_

#include "TvLinetype.h"
#include "TvLayer.h"
#include "TvMaterial.h"
#include "Tv.h"

/** \details
  The base interface class for working with Visualize SDK color definition objects.
  \sa
  <link tv_working_with_attributes_colors_colordef, Work with Color Definition Objects>
*/
class ODTV_EXPORT OdTvColorDef
{
public:

  /** \details 
    Color types. 
  */
  enum ColorType
  {
    kDefault = 0,    // Default color.
    kColor = 1,     // Color specified by the definition object.
    kInherited = 2, // Inherited color.
    kIndexed = 3    // Color defined with an index.
  };

  /** \details 
    Creates a new instance of a color definition with default parameters.
  */
  OdTvColorDef();
  
  /** \details 
    Creates a new color definition object as a copy of an existing object (copy constructor).
    
    \param color [in] A color definition object to be copied.
  */
  OdTvColorDef(const OdTvColorDef & color);
  
  /** \details 
    Creates a new color definition object based on an RGB color value.
    
    \param r [in] A red value of the RGB color definition.
    \param g [in] A green value of the RGB color definition.
    \param b [in] A blue value of the RGB color definition.
  */
  OdTvColorDef(OdUInt8 r, OdUInt8 g, OdUInt8 b);
  
  /** \details 
    Creates a new color definition object based on an inherited attribute.
    
    \param lt [in] An inherited attribute value.
  */
  OdTvColorDef(OdTv::InheritedAttribute lt);
  
  /** \details 
    Creates a new color definition object based on a color index.
    
    \param colorInd [in] A color index.
  */
  OdTvColorDef(OdUInt8 colorInd);
  
  /** \details 
    Destroys the color definition object.
  */
  virtual ~OdTvColorDef() {};

  /** \details
    The assignment operator for the color definition object. 
    
    \param color [in] Another color definition object that represents the second operand of the assignment operation.
    \returns Returns a reference to the color definition object modified after the assignment operation.
  */
  OdTvColorDef& operator =(const OdTvColorDef& color);
  
  /** \details
    The equal operator for two color definition objects. 
    
    \param color [in] Another color definition object to be compared with.
    \returns Returns true if the color definition object is equal to the other color definition object specified with the color parameter; otherwise the method returns false.
  */
  bool operator ==(const OdTvColorDef& color) const;
  
  /** \details
    The non-equal operator for two color definition objects. 
    
    \param color [in] Another color definition object to be compared with.
    \returns Returns true if the color definition object is not equal to the other color definition object specified with the color parameter; otherwise the method returns false.
  */
  bool operator !=(const OdTvColorDef& color) const;

  /** \details
    Retrieves the current color type of the color definition object.
    
    \returns Returns the current color type.
  */
  ColorType getType() const;

  /** \details
    Retrieves the current RGB color components of the color definition object.
    
    \param r [out] A placeholder for red color component value.
    \param g [out] A placeholder for green color component value.
    \param b [out] A placeholder for blue color component value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the current RGB component values were successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  OdTvResult getColor(OdUInt8& r, OdUInt8& g, OdUInt8& b) const;

  /** \details
    Retrieves the current inherited color of the color definition object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a <link OdTv::InheritedAttribute, InheritedAttribute> enumeration value that represents the current inherited color.
    \remarks 
    If the rc parameter is not null and the inherited color was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  OdTv::InheritedAttribute getInheritedColor(OdTvResult* rc = NULL) const;

  /** \details
    Retrieves the current indexed color of the color definition object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current indexed color.
    \remarks 
    If the rc parameter is not null and the indexed color was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  OdUInt8 getIndexedColor(OdTvResult* rc = NULL) const;

  /** \details
    Sets new RGB color components for the color definition object.
    
    \param r [in] A new red color component value.
    \param g [in] A new green color component value.
    \param b [in] A new blue color component value.
  */
  void setColor(OdUInt8 r, OdUInt8 g, OdUInt8 b);
  
  /** \details
    Sets a new inherited color for the color definition object.
    
    \param lt [in] An <link OdTv::InheritedAttribute, InheritedAttribute> enumeration value that represents the new inherited color to be set.
  */
  void setInheritedColor(OdTv::InheritedAttribute lt);

  /** \details
    Sets a new indexed color for the color definition object.
    
    \param colorInd [in] A new color index to be set.
  */
  void setIndexedColor(OdUInt8 colorInd);

  /** \details
    Sets the default color for the color definition object.
  */
  void setDefault();

//DOM-IGNORE-BEGIN
private:

  //data
  OdUInt32 m_color;
//DOM-IGNORE-END
};

/** \details
  A data type that represents an array of <link OdTvColorDef, OdTvColorDef> objects.
*/
typedef OdVector<OdTvColorDef, OdMemoryAllocator<OdTvColorDef> >  OdTvColorDefArray;



/** \details
  The base interface class for working with Visualize SDK RGB color definition objects.
  \sa
  <link tv_working_with_attributes_colors_rgbcolordef, Work with RGB Color Definition Objects>
*/
class ODTV_EXPORT OdTvRGBColorDef
{
public:

  /** \details 
    Creates a new instance of RGB color definitions with default parameters.
  */
  OdTvRGBColorDef();
  
  /** \details 
    Creates a new RGB color definition object with specified RGB components.
    
    \param r [in] A red value of the RGB color definition.
    \param g [in] A green value of the RGB color definition.
    \param b [in] A blue value of the RGB color definition.
  */
  OdTvRGBColorDef(OdUInt8 r, OdUInt8 g, OdUInt8 b);
  
  /** \details 
    Creates a new RGB color definition object as a copy of an existing object (copy constructor).
    
    \param color [in] An RGB color definition object to be copied.
  */  
  OdTvRGBColorDef(const OdTvRGBColorDef& color);
  
  /** \details 
    Destroys the color definition object.
  */
  virtual ~OdTvRGBColorDef() {};

  /** \details
    The assignment operator for the RGB color definition object. 
    
    \param color [in] Another RGB color definition object that represents the second operand of the assignment operation.
    \returns Returns the reference to the RGB color definition object modified after the assignment operation.
  */
  OdTvRGBColorDef& operator =(const OdTvRGBColorDef& color);
  
  /** \details
    The equal operator for two RGB color definition objects. 
    
    \param color [in] Another RGB color definition object to be compared with.
    \returns Returns true if the RGB color definition object is equal to the other RGB color definition object specified with the color parameter; otherwise the method returns false.
  */
  bool operator ==(const OdTvRGBColorDef& color) const;
  
  /** \details
    The non-equal operator for two RGB color definition objects. 
    
    \param color [in] Another RGB color definition object to be compared with.
    \returns Returns true if the RGB color definition object is not equal to the other RGB color definition object specified with the color parameter; otherwise the method returns false.
  */
  bool operator !=(const OdTvRGBColorDef& color) const;

  /** \details
    Checks whether the RGB color definition object is the default color.
    
    \returns Returns true if this RGB color definition is used as the default color; otherwise the method returns false.
  */
  bool isDefault() const;

  /** \details
    Retrieves the current color components of the RGB color definition object.
    
    \param r [out] A placeholder for red color component value.
    \param g [out] A placeholder for green color component value.
    \param b [out] A placeholder for blue color component value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the current component colors were successfully retrieved, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  OdTvResult getColor(OdUInt8& r, OdUInt8& g, OdUInt8& b) const;

  /** \details
    Sets new color components for the RGB color definition object.
    
    \param r [in] A new red color component value.
    \param g [in] A new green color component value.
    \param b [in] A new blue color component value.
  */
  void setColor(OdUInt8 r, OdUInt8 g, OdUInt8 b);

  /** \details
    Sets the default color flag to true. 
    The default color flag determines whether the color definition object is used as the default color (if equal to true) or not (if equal to false).
  */
  void setDefault();

//DOM-IGNORE-BEGIN
private:

  //data
  OdUInt8 m_flags;
  OdUInt8 m_r;
  OdUInt8 m_g;
  OdUInt8 m_b;
//DOM-IGNORE-END
};

/** \details
  A data type that represents an array of <link OdTvRGBColorDef, OdTvRGBColorDef> objects.
*/
typedef OdVector<OdTvRGBColorDef, OdMemoryAllocator<OdTvRGBColorDef> >  OdTvRGBColorDefArray;



/** \details
  The base interface class for working with Visualize SDK linetype definition objects.
  \sa
  <link tv_working_with_attributes_linetypes, Work with Linetypes>
*/
class ODTV_EXPORT OdTvLinetypeDef
{
public:

  /** \details
    Different kinds of linetypes supported by Visualize SDK.
  */
  enum LinetypeType
  {
    kDefault      = 0, // Default linetype.
    kId           = 1, // A linetype defined by its identifier.
    kPredefined   = 2, // A predefined linetype.
    kInherited    = 3  // An inherited linetype.
  };

  /** \details 
    Creates a new instance of a linetype definition with default parameters.
  */
  OdTvLinetypeDef();
  
    /** \details 
    Creates a new linetype definition object as a copy of an existing object (copy constructor).
    
    \param ltDef [in] A linetype definition object to be copied.
  */
  OdTvLinetypeDef(const OdTvLinetypeDef & ltDef);
  
  /** \details 
    Creates a new linetype definition object based on a linetype object specified with its identifier.
    
    \param lt [in] An identifier of a linetype object.
  */
  OdTvLinetypeDef(const OdTvLinetypeId& lt);
  
  /** \details 
    Creates a new linetype definition object based on an inherited attribute.
    
    \param lt [in] An inherited attribute value.
  */
  OdTvLinetypeDef(OdTv::InheritedAttribute lt);
  
  /** \details 
    Creates a new predefined linetype definition object.
    
    \param lt [in] A type of predefined linetype.
  */  
  OdTvLinetypeDef(OdTvLinetype::Predefined lt);
  
  /** \details 
    Destroys the linetype definition object.
  */
  virtual ~OdTvLinetypeDef() {};

  /** \details
    The assignment operator for the linetype definition object. 
    
    \param ltDef [in] Another linetype definition object that represents the second operand of the assignment operation.
    \returns Returns the reference to the linetype modified after the assignment operation.
  */
  OdTvLinetypeDef& operator =(const OdTvLinetypeDef& ltDef);
  
  /** \details
    The equal operator for two linetype definition objects. 
    
    \param ltDef [in] Another linetype definition object to be compared with.
    \returns Returns true if the linetype definition object is equal to the other linetype definition object specified with the ltDef parameter; otherwise the method returns false.
  */
  bool operator ==(const OdTvLinetypeDef& ltDef) const;
  
  /** \details
    The non-equal operator for two linetype definition objects. 
    
    \param ltDef [in] Another linetype definition object to be compared with.
    \returns Returns true if the linetype definition object is not equal to the other linetype definition object specified with the ltDef parameter; otherwise the method returns false.
  */
  bool operator !=(const OdTvLinetypeDef& ltDef) const;

  /** \details
    Retrieves the current type of linetype definition object.
    
    \returns Returns the current type of linetype.
  */
  LinetypeType getType() const;

  /** \details
    Retrieves the current linetype object associated with the linetype definition object.
    
    \returns Returns the identifier of the current linetype object.
  */
  OdTvLinetypeId getLinetype() const;

  /** \details
    Retrieves the current inherited linetype of the linetype definition object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns an <link OdTv::InheritedAttribute, InheritedAttribute> enumeration value that represents the current inherited linetype.
    \remarks 
    If the rc parameter is not null and the inherited linetype was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  OdTv::InheritedAttribute getInheritedLinetype(OdTvResult* rc = NULL) const;

  /** \details
    Retrieves the current predefined linetype of the linetype definition object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a <link OdTvLinetype::Predefined, Predefined> enumeration value that represents the current predefined linetype.
    \remarks 
    If the rc parameter is not null and the predefined linetype was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  OdTvLinetype::Predefined getPredefinedLinetype(OdTvResult* rc = NULL) const;

  /** \details
    Sets a new linetype object for the linetype definition object.
    
    \param lt [in] An identifier of the linetype object.
  */
  void setLinetype(const OdTvLinetypeId& lt);
  
  /** \details
    Sets a new inherited linetype for the linetype definition object.
    
    \param lt [in] An <link OdTv::InheritedAttribute, InheritedAttribute> enumeration value that represents the new inherited linetype to be set.
  */
  void setInheritedLinetype(OdTv::InheritedAttribute lt);
  
  /** \details
    Sets a new predefined linetype for the linetype definition object.
    
    \param lt [in] A <link OdTvLinetype::Predefined, Predefined> enumeration value that represents the new predefined linetype to be set.
  */
  void setPredefinedLinetype(OdTvLinetype::Predefined lt);

  /** \details
    Sets the linetype object as the default.
  */
  void setDefault();

//DOM-IGNORE-BEGIN  
private:

  //data
  OdTvLinetypeId m_ltId;
  OdUInt16 m_data;
//DOM-IGNORE-END
};

/** \details
  A data type that represents an array of <link OdTvLinetypeDef, OdTvLinetypeDef> objects.
*/
typedef OdVector<OdTvLinetypeDef, OdMemoryAllocator<OdTvLinetypeDef> >  OdTvLinetypeDefArray;

/** \details
  The base interface class for working with Visualize SDK lineweight definition objects.
  \sa
  <link tv_working_with_attributes_lineweights, Work with Lineweights>
*/
class ODTV_EXPORT OdTvLineWeightDef
{
public:

  /** \details
    Lineweight types supported by Visualize SDK.
  */
  enum LineWeightType
  {
    kDefault    = 0, // Default lineweight.
    kValue      = 1, // A lineweight specified with an appropriate value.
    kInherited  = 2  // An inherited lineweight.
  };

  /** \details 
    Creates a new instance of a lineweight definition with default parameters.
  */
  OdTvLineWeightDef();
  
  /** \details 
    Creates a new lineweight definition object as a copy of an existing object (copy constructor).
    
    \param lineWeight [in] A lineweight definition object to be copied.
  */
  OdTvLineWeightDef(const OdTvLineWeightDef& lineWeight);
  
  /** \details 
    Creates a new lineweight type definition object with a specified weight value.
    
    \param value [in] A lineweight value.
  */
  OdTvLineWeightDef(OdUInt8 value);
  
  /** \details 
    Creates a new lineweight definition object based on an inherited attribute.
    
    \param inhAttr [in] An inherited attribute value.
  */
  OdTvLineWeightDef(OdTv::InheritedAttribute inhAttr);
  
  /** \details 
    Destroys the linetype definition object.
  */
  ~OdTvLineWeightDef() {};

  /** \details
    The assignment operator for the lineweight definition object. 
    
    \param ltDef [in] Another lineweight definition object that represents the second operand of the assignment operation.
    \returns Returns the reference to the lineweight definition object modified after the assignment operation.
  */
  OdTvLineWeightDef& operator =(const OdTvLineWeightDef& ltDef);
  
  /** \details
    The equal operator for two lineweight definition objects. 
    
    \param ltDef [in] Another lineweight definition object to be compared with.
    \returns Returns true if the lineweight definition object is equal to the other lineweight definition object specified with the ltDef parameter; otherwise the method returns false.
  */
  bool operator ==(const OdTvLineWeightDef& ltDef) const;
  
  /** \details
    The non-equal operator for two lineweight definition objects. 
    
    \param ltDef [in] Another lineweight definition object to be compared with.
    \returns Returns true if the lineweight definition object is not equal to the other lineweight definition object specified with the ltDef parameter; otherwise the method returns false.
  */
  bool operator !=(const OdTvLineWeightDef& ltDef) const;

  /** \details
    Retrieves the current lineweight type of the lineweight definition object.
    
    \returns Returns the current type of the lineweight.
  */
  LineWeightType getType() const;

  /** \details
    Retrieves the current lineweight value of the lineweight definition object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current lineweight value.
    \remarks 
    If the rc parameter is not null and the current lineweight value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  OdUInt8 getValue(OdTvResult* rc = NULL) const;

  /** \details
    Retrieves the current inherited lineweight of the lineweight definition object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns an <link OdTv::InheritedAttribute, InheritedAttribute> enumeration value that represents the current inherited lineweight.
    \remarks 
    If the rc parameter is not null and the inherited lineweight was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  OdTv::InheritedAttribute getInheritedLineWeight(OdTvResult* rc = NULL) const;

  /** \details
    Sets a new lineweight value for the lineweight definition object.
    
    \param value [in] A lineweight value to be set.
  */
  void setValue(OdUInt8 value);

  /** \details
    Sets a new inherited lineweight for the lineweight definition object.
    
    \param inhAttr [in] An <link OdTv::InheritedAttribute, InheritedAttribute> enumeration value that represents the new inherited lineweight to be set.
  */
  void setInherited(OdTv::InheritedAttribute inhAttr);

  /** \details
    Sets the lineweight object as the default.
  */
  void setDefault();

//DOM-IGNORE-BEGIN
private:
  OdUInt16 m_data;
//DOM-IGNORE-END
};


/** \details
  The base interface class for working with Visualize SDK layer definition objects.
  \sa
  <link tv_working_with_attributes_layers, Work with Layers>
*/
class ODTV_EXPORT OdTvLayerDef
{
public:
  
  /** \details
    Layer types supported by Visualize SDK.
  */
  enum LayerType
  {
    kDefault = 0, // Default layer.
    kId = 1,      // A layer defined by its identifier.
  };

  /** \details 
    Creates a new layer definition object with default parameters.
  */
  OdTvLayerDef();
  
  /** \details 
    Creates a new layer definition object as a copy of an existing object (copy constructor).
    
    \param layerDef [in] A layer definition object to be copied.
  */
  OdTvLayerDef(const OdTvLayerDef & layerDef);
  
  /** \details 
    Creates a new layer definition object based on a layer object specified with its identifier.
    
    \param layer [in] An identifier of a layer object.
  */
  OdTvLayerDef(const OdTvLayerId& layer);
  
  /** \details 
    Destroys the layer definition object.
  */
  virtual ~OdTvLayerDef() {};

  /** \details
    The assignment operator for the layer definition object. 
    
    \param lDef [in] Another layer definition object that represents the second operand of the assignment operation.
    \returns Returns the reference to the layer definition object modified after the assignment operation.
  */
  OdTvLayerDef& operator =(const OdTvLayerDef& lDef);
  
  /** \details
    The equal operator for two layer definition objects. 
    
    \param layerDef [in] Another layer definition object to be compared with.
    \returns Returns true if the layer definition object is equal to the other layer definition object specified with the layerDef parameter; otherwise the method returns false.
  */
  bool operator ==(const OdTvLayerDef& layerDef) const;
  
  /** \details
    The non-equal operator for two layer definition objects. 
    
    \param layerDef [in] Another layer definition object to be compared with.
    \returns Returns true if the layer definition object is not equal to the other layer definition object specified with the layerDef parameter; otherwise the method returns false.
  */
  bool operator !=(const OdTvLayerDef& layerDef) const;

  /** \details
    Retrieves the current layer type of the layer definition object.
    
    \returns Returns the current layer type.
  */
  LayerType getType() const;

  /** \details
    Retrieves the current layer object associated with the layer definition object.
    
    \returns Returns the identifier of the current layer object.
  */
  OdTvLayerId getLayer() const;

  /** \details
    Sets a new layer object for the layer definition object.
    
    \param layer [in] An identifier of the layer object.
  */
  void setLayer(const OdTvLayerId& layer);

  /** \details
    Sets the layer definition object as the default.
  */
  void setDefault();

//DOM-IGNORE-BEGIN
private:

  // data
  OdTvLayerId m_lId;
  OdUInt8 m_data;
//DOM-IGNORE-END
};

/** \details
  A data type that represents an array of <link OdTvLayerDef, OdTvLayerDef> objects.
*/
typedef OdVector<OdTvLayerDef, OdMemoryAllocator<OdTvLayerDef> >  OdTvLayerDefArray;

/** \details
  The base interface class for working with Visualize SDK visibility definition objects.
*/
class ODTV_EXPORT OdTvVisibilityDef
{
public:

  /** \details
    Visibility types supported by Visualize SDK.
  */
  enum VisibilityType
  {
    kInvisible  = 0, // An invisible object.
    kVisible    = 1, // A visible object.
    kDefault    = 2  // Default visibility.
  };

  /** \details 
    Creates a new instance of a visibility definition with default parameters.
  */
  OdTvVisibilityDef();
  
  /** \details 
    Creates a new visibility definition object with a specified visibility option.
    
    \param bVisible [in] A visibility value (if equal to true, the object is visible; otherwise the object is invisible).
  */
  OdTvVisibilityDef(const bool& bVisible);
  
  /** \details 
    Creates a new visibility definition object as a copy of an existing object (copy constructor).
    
    \param visibility [in] A visibility definition object to be copied.
  */
  OdTvVisibilityDef(const OdTvVisibilityDef& visibility);
  
  /** \details 
    Destroys the visibility definition object.
  */
  virtual ~OdTvVisibilityDef() {};

  /** \details
    The assignment operator for the visibility definition object. 
    
    \param visDef [in] Another visibility definition object that represents the second operand of the assignment operation.
    \returns Returns the reference to the visibility definition object modified after the assignment operation.
  */
  OdTvVisibilityDef& operator =(const OdTvVisibilityDef& visDef);
  
  /** \details
    The equal operator for two visibility definition objects. 
    
    \param visDef [in] Another visibility definition object to be compared with.
    \returns Returns true if the visibility definition object is equal to the other visibility definition object specified with the visDef parameter; otherwise the method returns false.
  */
  bool operator ==(const OdTvVisibilityDef& visDef) const;
  
  /** \details
    The non-equal operator for two visibility definition objects. 
    
    \param visDef [in] Another visibility definition object to be compared with.
    \returns Returns true if the visibility definition object is not equal to the other visibility definition object specified with the visDef parameter; otherwise the method returns false.
  */
  bool operator !=(const OdTvVisibilityDef& visDef) const;

  /** \details
    Retrieves the current type of the visibility definition object.
    
    \returns Returns the current visibility type.
  */
  VisibilityType getType() const;

  /** \details
    Sets the visibility object as the default.
  */
  void setDefault();

  /** \details
    Sets the visibility flag of the visibility definition object to true. 
    The object associated with the visibility definition becomes visible.
  */
  void setVisible();

  /** \details
    Sets the visibility flag of the visibility definition object to false. 
    The object associated with the visibility definition becomes invisible.
  */
  void setInvisible();

//DOM-IGNORE-BEGIN
private:
  OdUInt8 m_data;
//DOM-IGNORE-END
};

/** \details
  A data type that represents an array of <link OdTvVisibilityDef, OdTvVisibilityDef> objects.
*/
typedef OdVector<OdTvVisibilityDef, OdMemoryAllocator<OdTvVisibilityDef> >  OdTvVisibilityDefArray;

/** \details
  The base interface class for working with Visualize SDK text style definition objects.
  \sa
  <link tv_working_with_attributes_text_style, Work with Text Styles>
*/
class ODTV_EXPORT OdTvTextStyleDef
{
public:

  /** \details
    Types of text styles supported by Visualize SDK.
  */
  enum TextStyleType
  {
    kDefault      = 0, // Default text style.
    kId           = 1, // A text style is defined by its identifier.
  };

  /** \details 
    Creates a new text style definition object with default parameters.
  */
  OdTvTextStyleDef();
  
  /** \details 
    Creates a new text style definition object as a copy of an existing object (copy constructor).
    
    \param testStyleDef [in] A text style definition object to be copied.
  */
  OdTvTextStyleDef(const OdTvTextStyleDef & testStyleDef);
  
  /** \details 
    Creates a new text style definition object based on a text style object specified with its identifier.
    
    \param textStyle [in] An identifier of a text style object.
  */
  OdTvTextStyleDef(const OdTvTextStyleId& textStyle);
  
  /** \details 
    Destroys the text style definition object.
  */
  virtual ~OdTvTextStyleDef() {};

  /** \details
    The assignment operator for the text style definition object. 
    
    \param tsDef [in] Another text style definition object that represents the second operand of the assignment operation.
    \returns Returns the reference to the text style definition object modified after the assignment operation.
  */
  OdTvTextStyleDef& operator =(const OdTvTextStyleDef& tsDef);
  
  /** \details
    The equal operator for two text style definition objects. 
    
    \param testStyleDef [in] Another text style definition object to be compared with.
    \returns Returns true if the text style definition object is equal to the other text style definition object specified with the testStyle parameter; otherwise the method returns false.
  */
  bool operator ==(const OdTvTextStyleDef& testStyleDef) const;
  
  /** \details
    The non-equal operator for two text style definition objects. 
    
    \param testStyleDef [in] Another text style definition object to be compared with.
    \returns Returns true if the text style definition object is not equal to the other text style definition object specified with the testStyle parameter; otherwise the method returns false.
  */
  bool operator !=(const OdTvTextStyleDef& testStyleDef) const;

  /** \details
    Retrieves the current type of the text style definition object.
    
    \returns Returns the current type of the text style.
  */
  TextStyleType getType() const;

  /** \details
    Retrieves the current text style object associated with the text style definition object.
    
    \returns Returns the identifier of the current text style object.
  */
  OdTvTextStyleId getTextStyle() const;

  /** \details
    Sets a new text style object for the text style definition object.
    
    \param textStyle [in] An identifier of the text style object.
  */
  void setTextStyle(const OdTvTextStyleId& textStyle);

  /** \details
    Sets the text style object as the default.
  */
  void setDefault();

//DOM-IGNORE-BEGIN
private:

  // data
  OdTvTextStyleId m_lId;
  OdUInt8 m_data;
//DOM-IGNORE-END
};

/** \details
  The base interface class for working with Visualize SDK transparency definition objects.
*/
class ODTV_EXPORT OdTvTransparencyDef
{
public:

  /** \details
    Types of transparency supported by Visualize SDK.
  */
  enum TransparencyType
  {
    kDefault    = 0,  // Default transparency. 
    kValue      = 1,  // A transparency is defined with a specified value.
    kInherited  = 2   // An inherited transparency.
  };

  /** \details 
    Creates a new transparency definition object with default parameters.
  */
  OdTvTransparencyDef();
  
  /** \details 
    Creates a new transparency definition object as a copy of an existing object (copy constructor).
    
    \param transparency [in] A transparency definition object to be copied.
  */  
  OdTvTransparencyDef(const OdTvTransparencyDef& transparency);
  
  /** \details 
    Creates a new transparency definition object based on an inherited attribute.
    
    \param inhAttr [in] An inherited attribute value.
  */
  OdTvTransparencyDef(OdTv::InheritedAttribute inhAttr);
  
  /** \details 
    Creates a new transparency definition object with a specified transparency level.
    
    \param dPercentage [in] A transparency value.
  */
  OdTvTransparencyDef(double dPercentage);
  
  /** \details 
    Destroys the transparency definition object.
  */
  ~OdTvTransparencyDef() {};

  /** \details
    The assignment operator for the transparency definition object. 
    
    \param trDef [in] Another transparency definition object that represents the second operand of the assignment operation.
    \returns Returns the reference to the transparency definition object modified after the assignment operation.
  */
  OdTvTransparencyDef& operator =(const OdTvTransparencyDef& trDef);
  
  /** \details
    The equal operator for two transparency definition objects. 
    
    \param trDef [in] Another transparency definition object to be compared with.
    \returns Returns true if the transparency definition object is equal to the other transparency definition object specified with the trDef parameter; otherwise the method returns false.
  */
  bool operator ==(const OdTvTransparencyDef& trDef);
  
  /** \details
    The non-equal operator for two transparency definition objects. 
    
    \param trDef [in] Another transparency definition object to be compared with.
    \returns Returns true if the transparency definition object is not equal to the other transparency definition object specified with the trDef parameter; otherwise the method returns false.
  */
  bool operator !=(const OdTvTransparencyDef& trDef);


  /** \details
    Retrieves the current type of the transparency definition object.
    
    \returns Returns the current type of the transparency.
  */
  TransparencyType getType() const;

  /** \details
    Retrieves the current transparency value of the transparency definition object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current transparency value.
    \remarks 
    If the rc parameter is not null and the current transparency value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  double getValue(OdTvResult* rc = NULL) const;

  /** \details
    Retrieves the current inherited transparency value of the transparency definition object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns an <link OdTv::InheritedAttribute, InheritedAttribute> enumeration value that represents the current inherited transparency value.
    \remarks 
    If the rc parameter is not null and the inherited transparency value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  OdTv::InheritedAttribute getInheritedTransparency(OdTvResult* rc = NULL) const;

  /** \details
    Sets a new transparency value for the transparency definition object.
    
    \param dPercentage [in] A new transparency value to be set.
  */
  void setValue(double dPercentage);

  /** \details
    Sets a new inherited transparency for the linetype definition object.
    
    \param inhAttr [in] An <link OdTv::InheritedAttribute, InheritedAttribute> enumeration value that represents the new inherited transparency value to be set.
  */
  void setInherited(OdTv::InheritedAttribute inhAttr);

  /** \details
    Sets the transparency object as the default.
  */
  void setDefault();

//DOM-IGNORE-BEGIN
private:

  OdUInt16 m_data;
//DOM-IGNORE-END
};

/** \details
  A data type that represents an array of <link OdTvTransparencyDef, OdTvTransparencyDef> objects.
*/
typedef OdVector<OdTvTransparencyDef, OdMemoryAllocator<OdTvTransparencyDef> >  OdTvTransparencyDefArray;

/** \details
  The base interface class for working with Visualize SDK material definition objects.
  \sa
  <link tv_working_with_attributes_materials, Work with Materials>
*/
class ODTV_EXPORT OdTvMaterialDef
{
public:

  /** \details
    Types of materials supported by Visualize SDK.
  */
  enum MaterialType
  {
    kDefault   = 0, // Default material.
    kId        = 1, // A material defined by its identifier.
    kInherited = 2  // An inherited material.
  };

  /** \details 
    Creates a new material definition object with default parameters.
  */
  OdTvMaterialDef();
  
  /** \details 
    Creates a new material definition object as a copy of an existing object (copy constructor).
    
    \param materialDef [in] A material definition object to be copied.
  */
  OdTvMaterialDef(const OdTvMaterialDef & materialDef);
  
  /** \details 
    Creates a new material definition object based on a material object specified with its identifier.
    
    \param material [in] An identifier of a material object.
  */
  OdTvMaterialDef(const OdTvMaterialId& material);
  
  /** \details 
    Creates a new material definition object based on an inherited attribute.
    
    \param mat [in] An inherited attribute value.
  */
  OdTvMaterialDef(OdTv::InheritedAttribute mat);
  
  /** \details 
  Destroys the material definition object.
  */
  virtual ~OdTvMaterialDef() {};

  /** \details
    The assignment operator for the material definition object. 
    
    \param mDef [in] Another material definition object that represents the second operand of the assignment operation.
    \returns Returns the reference to the material definition object modified after the assignment operation.
  */
  OdTvMaterialDef& operator =(const OdTvMaterialDef& mDef);
  
  /** \details
    The equal operator for two material definition objects. 
    
    \param materialDef [in] Another material definition object to be compared with.
    \returns Returns true if the material definition object is equal to the other material definition object specified with the materialDef parameter; otherwise the method returns false.
  */
  bool operator ==(const OdTvMaterialDef& materialDef) const;
  
  /** \details
    The non-equal operator for two material definition objects. 
    
    \param materialDef [in] Another material definition object to be compared with.
    \returns Returns true if the material definition object is not equal to the other material definition object specified with the materialDef parameter; otherwise the method returns false.
  */
  bool operator !=(const OdTvMaterialDef& materialDef) const;

  /** \details
    Retrieves the current material type of the material definition object.
    
    \returns Returns the current material type.
  */
  MaterialType getType() const;

  /** \details
    Retrieves the current material ID associated with the material definition object.
    
    \returns Returns the identifier of the current material object.
  */
  OdTvMaterialId getMaterial() const;

  /** \details
    Retrieves the current inherited material of the material definition object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns an <link OdTv::InheritedAttribute, InheritedAttribute> enumeration value that represents the current inherited material.
    \remarks 
    If the rc parameter is not null and the inherited material was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  OdTv::InheritedAttribute getInheritedMaterial(OdTvResult* rc = NULL) const;

  /** \details
    Sets a new material object for the material definition object.
    
    \param material [in] An identifier of the material object.
  */
  void setMaterial(const OdTvMaterialId& material);

  /** \details
    Sets the material object as the default.
  */
  void setDefault();

  /** \details
    Sets a new inherited material for the material definition object.
    
    \param mat [in] An <link OdTv::InheritedAttribute, InheritedAttribute> enumeration value that represents the new inherited material to be set.
  */
  void setInheritedMaterial(OdTv::InheritedAttribute mat);

//DOM-IGNORE-BEGIN
private:

  // data
  OdTvMaterialId m_mId;
  OdUInt16 m_data;
//DOM-IGNORE-END
};

/** \details
  A data type that represents an array of <link OdTvMaterialDef, OdTvMaterialDef> objects.
*/
typedef OdVector<OdTvMaterialDef, OdMemoryAllocator<OdTvMaterialDef> >  OdTvMaterialDefArray;

/** \details
  The base interface class for working with Visualize SDK mapper definition objects.
  \sa
  <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
*/
class ODTV_EXPORT OdTvMapperDef
{
public:

  /** \details
    Types of mappers supported by Visualize SDK.
  */
  enum MapperType
  {
    kDefault = 0, // Default mapper.
    kValue = 1    // A mapper defined with a specified value.
  };

  /** \details
    Mapping projections.
  */
  enum Projection
  {
    kPlanar = 0,      // Maps directly to XY coordinates.
    kBox = 1,         // Maps to planes perpendicular to major axes.
    kCylinder = 2,    // Maps to cylinders aligned with the Z-axis.
    kSphere = 3       // Maps to spheres aligned with the Z-axis.
  };

  /** \details
    Automatic transformation modes.
  */
  enum AutoTransform
  {
    kNone = 0x1,      // No automatic transformation.
    kObject = 0x2,    // Adjusts the mapper transformation to align with and fit the current object.
    kModel = 0x4      // Multiplies the mapper transformation by the current block transformation.
  };

  /** \details 
    Creates a new mapper definition object with default parameters.
  */
  OdTvMapperDef();
  
  /** \details 
  Creates a new mapper definition object as a copy of an existing object (copy constructor).
  \param mapper [in] A mapper definition object to be copied.
  */
  OdTvMapperDef(const OdTvMapperDef& mapper);
  
  /** \details
    The assignment operator for the mapper definition object. 
    
    \param mapper [in] Another mapper definition object that represents the second operand of the assignment operation.
    \returns Returns the reference to the mapper definition modified after the assignment operation.
  */
  OdTvMapperDef& operator=(const OdTvMapperDef& mapper);
  
  /** \details
    The equal operator for two mapper definition objects. 
    
    \param mapper [in] Another mapper definition object to be compared with.
    \returns Returns true if the mapper definition object is equal to the other mapper definition object specified with the mapper parameter; otherwise the method returns false.
  */
  bool operator==(const OdTvMapperDef& mapper) const;
  
  /** \details
    The non-equal operator for two mapper definition objects. 
    
    \param mapper [in] Another mapper definition object to be compared with.
    \returns Returns true if the mapper definition object is not equal to the other mapper definition object specified with the mapper parameter; otherwise the method returns false.
  */
  bool operator!=(const OdTvMapperDef& mapper) const;

  /** \details
    Sets a new projection type for the mapper definition object.
    
    \param projection [in] A new projection type to be set.
  */
  void setProjection(Projection projection);

  /** \details
    Sets a new automatic transformation type for the mapper definition object.
    
    \param autoTransform [in] A new automatic transformation type to be set.
  */
  void setAutoTransform(AutoTransform autoTransform);

  /** \details
    Retrieves the current projection type of the mapper definition object.
    
    \returns Returns the current projection type.
  */
  Projection projection() const;

  /** \details
    Retrieves the current type of the automatic transformation for the mapper definition object.
    
    \returns Returns the current type of the automatic transformation.
  */
  AutoTransform autoTransform() const;

  /** \details
    Retrieves the current transformation matrix for the mapper definition object.
    
    \returns Returns the current transformation matrix.
  */
  const OdTvMatrix& transform() const;

  /** \details
    Applies a new transformation matrix for the mapper definition object.
    
    \param tm [in] A new transformation matrix to be applied.
  */
  void setTransform(const OdTvMatrix &tm);

  /** \details
    Sets new rotation angles for the mapper definition object.
    
    \param x [in] A rotation angle relative to the X-axis.
    \param y [in] A rotation angle relative to the Y-axis.
    \param z [in] A rotation angle relative to the Z-axis.
  */
  void rotate(double x, double y, double z);

  /** \details
    Sets new translation parameters for the mapper definition object.
    
    \param x [in] A translation distance along the X-axis.
    \param y [in] A translation distance along the Y-axis.
    \param z [in] A translation distance along the Z-axis.
  */
  void translate(double x, double y, double z);

  /** \details
    Sets a new translation vector for the mapper definition object.
    
    \param aVector [in] A translation vector.
  */
  void translate(const OdTvVector& aVector);

  /** \details
    Sets new scale factors for the mapper definition object. 
    
    \param x [in] A scaling factor value along the X-axis.
    \param y [in] A scaling factor value along the Y-axis.
    \param z [in] A scaling factor value along the Z-axis.
  */
  void scale(double x, double y, double z);

  /** \details
    Sets the mapper object as the default.
  */
  void setDefault();

  /** \details
    Retrieves the current type of the mapper definition object.
    
    \returns Returns the current mapper type.
  */
  MapperType getType() const;

//DOM-IGNORE-BEGIN
private:

  Projection    m_projection;
  AutoTransform m_autoTransform;
  OdTvMatrix    m_transform;
  MapperType    m_mapperType;
//DOM-IGNORE-END
};

/** \details
  A data type that represents an array of <link OdTvMapperDef, OdTvMapperDef> objects.
*/
typedef OdVector<OdTvMapperDef, OdMemoryAllocator<OdTvMapperDef> > OdTvMapperDefArray;


/** \details
  The base interface class for working with Visualize SDK selectability definition objects.
  \sa
  <link tv_working_with_features_selections, Work with Selections>
*/
class ODTV_EXPORT OdTvSelectabilityDef
{
public:

  /** \details 
    Creates a new selectability definition object with default parameters.
  */
  OdTvSelectabilityDef();
  
  /** \details 
    Creates a new selectability definition object as a copy of an existing object (copy constructor).
    
    \param selectabilityDef [in] A selectability definition object to be copied.
  */
  OdTvSelectabilityDef(const OdTvSelectabilityDef& selectabilityDef);
  
  /** \details 
    Destroys the selectability definition object.
  */
  virtual ~OdTvSelectabilityDef() {};

  /** \details
    The assignment operator for the selectability definition object. 
    
    \param selectabilityDef [in] Another selectability definition object that represents the second operand of the assignment operation.
    \returns Returns the reference to the selectability definition object modified after the assignment operation.
  */
  OdTvSelectabilityDef& operator =(const OdTvSelectabilityDef& selectabilityDef);
  
  /** \details
    The equal operator for two selectability definition objects. 
    
    \param selectabilityDef [in] Another selectability definition object to be compared with.
    \returns Returns true if the selectability definition object is equal to the other selectability definition object specified with the selectabilityDef parameter; otherwise the method returns false.
  */
  bool operator ==(const OdTvSelectabilityDef& selectabilityDef) const;
  
  /** \details
    The non-equal operator for two selectability definition objects. 
    
    \param selectabilityDef [in] Another selectability definition object to be compared with.
    \returns Returns true if the selectability definition object is not equal to the other selectability definition object specified with the selectabilityDef parameter; otherwise the method returns false.
  */
  bool operator !=(const OdTvSelectabilityDef& selectabilityDef) const;

  /** \details
    Sets the current selectability value as the default.
  */
  void setDefault();

  /** \details
    Checks whether the current selectability value is used as the default.
    
    \returns Returns true if the current selectability value is the default value; otherwise the method returns false.
  */
  bool getDefault() const;

  /** \details
    Sets the selectability for geometry entities.
    
    \param bVal [in] A value that specifies the selectability.
    \remarks
    If the method input parameter is equal to true, any geometry entity or all the geometry entities can be selected; 
    if the method input parameter is equal to false, no geometry entity can be selected.
  */
  void setGeometries(bool bVal);

  /** \details
    Checks whether geometry entities can be selected.
    
    \returns Returns true if any geometry entity or all geometry entities can be selected; if no geometry entity can be selected, the method returns false.
  */
  bool getGeometries() const;

  /** \details
    Sets the selectability for faces.
    
    \param bVal [in] A value that specifies the selectability.
    \remarks
    If the method input parameter is equal to true, any face or all the faces can be selected; 
    if the method input parameter is equal to false, no face can be selected.
  */
  void setFaces(bool bVal);

  /** \details
    Checks whether faces can be selected.
    
    \returns Returns true if any face or all faces can be selected; if no face can be selected, the method returns false.
  */
  bool getFaces() const;

  /** \details
    Sets the selectability for edges.
    
    \param bVal [in] A value that specifies the selectability.
    \remarks
    If the method input parameter is equal to true, any edge or all the edges can be selected; 
    if the method input parameter is equal to false, no edge can be selected.
  */
  void setEdges(bool bVal);

  /** \details
    Checks whether edges can be selected.
    
    \returns Returns true if any edge or all edges can be selected; if no edge can be selected, the method returns false.
  */
  bool getEdges() const;

  /** \details
    Sets the selectability for vertices.
    
    \param bVal [in] A value that specifies the selectability.
    \remarks
    If the method input parameter is equal to true, any vertex or all the vertices can be selected; 
    if the method input parameter is equal to false, no vertex can be selected.
    This method is not implemented yet.
  */
  void setVertices(bool bVal);

  /** \details
    Checks whether vertices can be selected.
    
    \returns Returns true if any vertex or all vertices can be selected; if no vertex can be selected, the method returns false.
    \remarks 
    This method is not implemented yet.
  */
  bool getVertices() const;

//DOM-IGNORE-BEGIN
protected:

  OdUInt8 m_data;
//DOM-IGNORE-END
};

/** \details
  A data type that represents an array of double values.
*/
typedef OdArray<double, OdMemoryAllocator<double> > OdTvDoubleArray;

/** \details
  The base interface class for working with Visualize SDK hatch pattern line definition objects.
  \sa
  <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
*/
class ODTV_EXPORT OdTvHatchPatternLineDef
{
public:

  /** \details 
    Creates a new hatch pattern line definition object with default parameters.
  */
  OdTvHatchPatternLineDef();
  
  /** \details 
    Creates a new hatch pattern line definition object as a copy of an existing object (copy constructor).
    
    \param def [in] A hatch pattern line definition object to be copied.
  */
  OdTvHatchPatternLineDef(const OdTvHatchPatternLineDef& def);
  
  /** \details 
    Destroys the hatch pattern line definition object.
  */
  virtual ~OdTvHatchPatternLineDef() {}

  /** \details 
    Retrieves the current line angle of the hatch pattern line definition object.
    
    \returns Returns the current line angle.
    \remarks 
    The line angle is calculated from a horizontal line in a counterclockwise direction in radians.
  */
  double lineAngle() const;
  
  /** \details
    Sets a new line angle value for the hatch pattern line definition object.
    
    \param dAngle [in] A new line angle to be set.
    \remarks 
    The line angle is calculated from a horizontal line in a counterclockwise direction in radians.
  */
  void setLineAngle(double dAngle);

  /** \details 
    Retrieves the current base point of the hatch pattern line definition object.
    
    \returns Returns the current base point.
    \remarks 
    The base point is a point from which pattern lines are calculated.
  */
  OdTvPoint2d basePoint() const;
  
  /** \details
    Sets a new base point for the hatch pattern line definition object.
    
    \param pt [in] A new base point to be set.
    \remarks 
    The base point is a point from which pattern lines are calculated.
  */
  void setBasePoint(const OdTvPoint2d& pt);

  /** \details 
    Retrieves the current offset vector of the hatch pattern line definition object.
    
    \returns Returns the current offset vector.
    \remarks 
    The pattern offset defines the spacing between pattern lines in the X-axis and Y-axis.
  */
  OdTvVector2d patternOffset() const;
  
  /** \details
    Sets a new offset vector for the hatch pattern line definition object.
    
    \param offset [in] A new offset vector to be set.
    \remarks 
    The pattern offset defines spacing between pattern lines in the X-axis and Y-axis.
  */
  void setPatternOffset(const OdTvVector2d& offset);

  /** \details 
    Retrieves the current dashes array of the hatch pattern line definition object.
    
    \returns Returns the current dashes array.
    \remarks 
    The returned array can include both positive and negative Double values. Positive values represent dashes, and negative values represent spaces (gaps).
  */
  OdTvDoubleArray dashes() const;
  
  /** \details
    Sets a new dash array for the hatch pattern line definition object.
    
    \param dash [in] A new dash array to be set.
    \remarks 
    The dash array can include both positive and negative Double values. Positive values represent dashes, and negative values represent spaces (gaps).
  */
  void setDashes(const OdTvDoubleArray& dash);

//DOM-IGNORE-BEGIN
protected:
  double            m_dLineAngle;
  OdTvPoint2d       m_basePoint;
  OdTvVector2d      m_patternOffset;
  OdTvDoubleArray   m_dashes;
//DOM-IGNORE-END
};

/** \details
  A data type that represents an array of <link OdTvHatchPatternLineDef, OdTvHatchPatternLineDef> objects.
*/
typedef OdArray<OdTvHatchPatternLineDef> OdTvHatchPatternLines;

/** \details
  The base interface class for working with Visualize SDK hatch pattern definition objects.
  \sa
  <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
*/
class ODTV_EXPORT OdTvHatchPatternDef
{
public:

  /** \details 
    Creates a new hatch pattern definition object with default parameters.
  */
  OdTvHatchPatternDef();
  
  /** \details 
    Creates a new hatch pattern definition object as a copy of an existing object (copy constructor).
    
    \param def [in] A hatch pattern definition object to be copied.
  */
  OdTvHatchPatternDef(const OdTvHatchPatternDef& def);
  
  /** \details 
    Destroys the hatch pattern definition object.
  */
  virtual ~OdTvHatchPatternDef() {}

  /** \details
    Retrieves the current hatch pattern line object of the hatch pattern definition object.
    
    \returns Returns the current hatch pattern line object.
    \remarks 
    The referenced object returned by the method is read-only.
  */
  const OdTvHatchPatternLines& patternLines() const;
  
  /** \details
    Retrieves the current hatch pattern line object of the hatch pattern definition object.
    
    \returns Returns the current hatch pattern line object.
    \remarks 
    The referenced object returned by the method can be modified, and modifications are saved in the hatch pattern object.
  */
  OdTvHatchPatternLines& patternLines();
  
  /** \details
    Sets a new hatch pattern line object for the hatch pattern definition object.
    
    \param hatchPattern [in] An hatch pattern line object to be set.
  */
  void setPatternLines(const OdTvHatchPatternLines& hatchPattern);

  /** \details
    Retrieves the current deviation value of the hatch pattern definition object.
    
    \returns Returns the current deviation value.
    \remarks
    The deviation is a parameter that defines the accuracy of the algorithm for generating pattern lines. High values make the algorithm perform faster but less accurately.
  */
  double deviation() const;
  
  /** \details
    Sets a new deviation value for the hatch pattern definition object.
    
    \param d [in] A new deviation value to be set.
    \remarks 
    The deviation is a parameter that defines the accuracy of the algorithm for generating pattern lines. High values make algorithm perform faster but less accurately.
  */
  void setDeviation(double d);

  /** \details
    Retrieves the current pattern scale value of the hatch pattern definition object.
    
    \returns Returns the current pattern scale value.
    \remarks 
    The pattern scale determines the scale of a pattern as a whole.
  */
  double patternScale() const;
  
  /** \details
    Sets a new pattern scale value for the hatch pattern definition object.
    
    \param scale [in] A new pattern scale value to be set.
    \remarks 
    Pattern scale determines the scale of a pattern as a whole.
  */
  void setPatternScale( double scale );

  /** \details
  Retrieves the current pattern color of the hatch pattern definition object.
  \returns Returns the current pattern color.
  */
  OdTvColorDef getPatternColor() const;

  /** \details
  Sets a new pattern color for the hatch pattern definition object.
  \param scale [in] A new pattern color to be set.
  */
  void setPatternColor(const OdTvColorDef& color);

  /** \details
  Retrieves the current pattern line weight value of the hatch pattern definition object.
  \returns Returns the current pattern line weight value.
  */
  OdTvLineWeightDef getPatternLineWeight() const;

  /** \details
  Sets a new pattern line weight value for the hatch pattern definition object.
  \param scale [in] A new pattern line weight value to be set.
  */
  void setPatternLineWeight(OdTvLineWeightDef lineweight);

  /** \details
  Is used to obtain custom pattern transparency value (Default is 255)
  \returns Pattern transparency value
  */
  OdTvTransparencyDef getPatternTransparency() const;

  /** \details
  Sets custom pattern transparency value.
  \param transparency [in] Pattern transparency value.
  */
  void setPatternTransparency(const OdTvTransparencyDef& transparency);

//DOM-IGNORE-BEGIN
protected:
  OdTvHatchPatternLines m_hatchPattern;
  double m_dDeviation;
  double m_dPatternScale;
  OdTvColorDef m_patternColor;
  OdTvLineWeightDef m_patternLineWeight;
  OdTvTransparencyDef m_patternTransparency;

//DOM-IGNORE-END

};

#endif // _ODTRF_TRAITSDEF_H_INCLUDED_
