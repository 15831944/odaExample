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

#ifndef _ODTV_LINETYPEELEMENT_H_INCLUDED_
#define _ODTV_LINETYPEELEMENT_H_INCLUDED_

#include "Tv.h"
#include "TvIObject.h"
#include "TvTextStyle.h"

class OdTvLinetypeElementImpl;
class OdTvLinetypeElementPtr;

/** \details
  The base class for all typified elements of a linetype pattern (dashes, dots, spaces, shapes and text).
  
  \remarks 
  The objects of this class can not be used for linetype pattern construction.
  For this purpose you need to use inherited classes.
  \sa
  <link tv_working_with_attributes_linetypes_pattern, Work with Linetype Pattern Elements>
*/
class ODTV_EXPORT OdTvLinetypeElement : public OdTvIObject
{
//DOM-IGNORE-BEGIN
protected:

  /** \details
    Empty constructor.
  */
  OdTvLinetypeElement();

  /** \details
    Constructor with parameters.
  */
  OdTvLinetypeElement(OdTvLinetypeElementImpl* pImpl);
//DOM-IGNORE-END

public:

  /** \details
    Linetype pattern element types.
  */
  enum Type
  {
    kUndefined = 0, // An undefined pattern.
    kDash = 1,      // A dash pattern.
    kSpace = 2,     // A space pattern.
    kDot = 3,       // A dot pattern.
    kShape = 4,     // A shape pattern.
    kText = 5       // A text pattern.
  };

  /** \details
    Creates a new linetype element.
    
    \returns Returns a smart pointer to the created linetype element. 
  */
  static OdTvLinetypeElementPtr createObject(); 

  /** \details
    Destroys the linetype element. 
  */
  ~OdTvLinetypeElement();

  /** \details
    Retrieves the current linetype pattern type for the element.
    
    \returns Returns the current linetype pattern type for the element.
  */
  Type getType() const;

  /** \details
    Retrieves whether the current linetype pattern element is valid. 
    
    \returns Returns true if the linetype pattern element is valid; otherwise returns false.
  */
  bool isValid() const;

  /** \details
    Increments the reference quantity for the linetype element.
  */
  void addRef();

  /** \details
    Decrements the reference quantity for the linetype element.
    
    \remarks
    When the reference quantity becomes equal to zero, the object is deleted.
  */
  void release();

  /** \details
    Retrieves the current reference quantity for the linetype element.
    
    \returns Returns the reference quantity.
  */
  long numRefs() const;

//DOM-IGNORE-BEGIN
protected:
  /*
  Pointer to the internal implementation.
  */
  OdTvLinetypeElementImpl*   m_pImpl;
//DOM-IGNORE-END
};


/** \details
  The base class for the dash pattern element.
  \sa
  <link tv_working_with_attributes_linetypes_pattern_dash, Work with Linetype Dashes>
*/
class ODTV_EXPORT OdTvLinetypeDashElement : public OdTvLinetypeElement
{
//DOM-IGNORE-BEGIN
  /** \details
    Empty constructor.
  */
  OdTvLinetypeDashElement();
//DOM-IGNORE-END

public:

  /** \details
    Creates a new empty dash object. 
    
    \returns Returns a smart pointer to the created dash object.
    \remarks 
    The empty dash object is ignored during the process of constructing a linetype pattern. 
    To make the dash object non-empty, set its length to a positive value using the <link OdTvLinetypeDashElement::setSize@double, setSize()> method.
  */
  static OdTvSmartPtr<OdTvLinetypeDashElement> createObject(); 

  /** \details
    Creates a new dash object with the specified length in drawing units.
    
    \param dSize [in] A new length value.
    \returns Returns a smart pointer to the created dash object. 
  */
  static OdTvSmartPtr<OdTvLinetypeDashElement> createObject(double dSize); 

  /** \details
    Sets a new length of the dash object in drawing units.
    
    \param dSize [in] A new dash length value to be set.
    \remarks 
    The dash length value should be positive.
  */
  void setSize(double dSize);

  /** \details
    Retrieves the current length of the dash object. 
    
    \returns Returns the current dash object's length in drawing units. 
    \remarks 
    If the returned length value is negative, the dash length was not set. In this case the dash object is ignored during the construction process of the linetype pattern.
  */
  double getSize() const;

};

/** \details
  A data type that represents a smart pointer to an <link OdTvLinetypeDashElement, OdTvLinetypeDashElement> object.
*/
typedef OdTvSmartPtr<OdTvLinetypeDashElement> OdTvLinetypeDashElementPtr;


/** \details
  The base class for the space pattern element.
  \sa
  <link tv_working_with_attributes_linetypes_pattern_space, Work with Linetype Spaces>
*/
class ODTV_EXPORT OdTvLinetypeSpaceElement : public OdTvLinetypeElement
{
//DOM-IGNORE-BEGIN
  /** \details
    Empty constructor.
  */
  OdTvLinetypeSpaceElement();
//DOM-IGNORE-END
  
public:

  /** \details
    Creates a new empty space object. 
    
    \returns Returns a smart pointer to the created space object.
    \remarks 
    The empty space object is ignored during the process of constructing the linetype pattern. 
    To make the space object non-empty, set its length to a positive value using the <link OdTvLinetypeSpaceElement::setSize@double, setSize()> method.
  */
  static OdTvSmartPtr<OdTvLinetypeSpaceElement> createObject(); 

  /** \details
    Creates a new space object with the specified length in drawing units.
    
    \param dSize [in] A new length value.
    \returns Returns a smart pointer to the created space object. 
  */
  static OdTvSmartPtr<OdTvLinetypeSpaceElement> createObject(double dSize); 

  /** \details
    Sets a new length of the space object in drawing units.
    
    \param dSize [in] A new space length value to be set.
    \remarks 
    The space length value should be positive.
  */
  void setSize(double dSize);

  /** \details
    Retrieves the current length of the space object. 
    
    \returns Returns the current space object's length in drawing units. 
    \remarks 
    If the returned length value is negative, the space length was not set. In this case the space object is ignored during the construction process of the linetype pattern.
  */
  double getSize() const;

};

/** \details
  A data type that represents a smart pointer to an <link OdTvLinetypeSpaceElement, OdTvLinetypeSpaceElement> object.
*/
typedef OdTvSmartPtr<OdTvLinetypeSpaceElement> OdTvLinetypeSpaceElementPtr;


/** \details
  The base class for the dot pattern element.
  \sa
  <link tv_working_with_attributes_linetypes_pattern_dot, Work with Linetype Dots>
*/
class ODTV_EXPORT OdTvLinetypeDotElement : public OdTvLinetypeElement
{
//DOM-IGNORE-BEGIN
  /** \details
    Empty constructor.
  */
  OdTvLinetypeDotElement();
//DOM-IGNORE-END
  
public:

  /** \details
    Creates a new empty dot object. 
    
    \returns Returns a smart pointer to the created dot object.
  */
  static OdTvSmartPtr<OdTvLinetypeDotElement> createObject(); 
};

/** \details
  A data type that represents a smart pointer to an <link OdTvLinetypeDotElement, OdTvLinetypeDotElement> object.
*/
typedef OdTvSmartPtr<OdTvLinetypeDotElement> OdTvLinetypeDotElementPtr;


/** \details
  The base class for the shape pattern element.
  \sa
  <link tv_working_with_attributes_linetypes_pattern_shape, Work with Linetype Shapes>
*/
class ODTV_EXPORT OdTvLinetypeShapeElement : public OdTvLinetypeElement
{
//DOM-IGNORE-BEGIN
  /** \details
    Empty constructor.
  */
  OdTvLinetypeShapeElement();

  /** \details
    Destructor.
  */
  virtual ~OdTvLinetypeShapeElement() {};
//DOM-IGNORE-END

public:

  /** \details
    Creates a new empty shape object. 
    
    \returns Returns a smart pointer to the created shape object.
    \remarks 
    The empty shape object is ignored during the process of constructing the linetype pattern. 
    To make the shape object non-empty:
    * Set the shape element's length to a positive value using the <link OdTvLinetypeShapeElement::setSize@double, setSize()> method.
    * Set the shape element's code to a positive value using the <link OdTvLinetypeShapeElement::setSourceNumber@OdUInt16, setSourceNumber()> method.
    * Set the shape element's text style using the <link OdTvLinetypeShapeElement::setStyle@OdTvTextStyleId, setStyle()> method.
  */
  static OdTvSmartPtr<OdTvLinetypeShapeElement> createObject(); 

  /** \details
    Retrieves the current code of the shape object. 
    
    \returns Returns the current shape object's code value. 
    \remarks 
    If the returned code value is equal to zero, the shape code was not set. In this case the shape object is ignored during the construction process of the linetype pattern.
  */
  OdUInt16 getSourceNumber( ) const;

  /** \details
    Sets a new code of the shape object.
    
    \param shapeNumber [in] A new code value to be set.
    \remarks
    Applying a shape's code requires the availability of the .shx file that must be previously loaded and the text style that defines the shape parameters. 
    The new code value should be greater than zero.
  */
  void setSourceNumber( OdUInt16 shapeNumber );

  /** \details
    Retrieves the current text style for the shape object. 
    
    \returns Returns an identifier of a text style object that specifies the current text style of the shape object.
  */
  OdTvTextStyleId getStyle() const;

  /** \details
    Sets a new text style for the shape object.
    
    \param idTextStyle [in] An identifier of a text style object to be set.
    \remarks 
    The initial text style after the creation of the shape object is empty.
  */
  void setStyle( OdTvTextStyleId idTextStyle );

  /** \details
    Retrieves the current length of the shape object. 
    
    \returns Returns the current shape object's length in drawing units. 
    \remarks 
    If the returned length value is zero, the shape length was not set. In this case the shape object is ignored during the construction process of the linetype pattern.
  */
  double getSize() const;

  /** \details
    Sets a new length of the shape object in drawing units.
    
    \param dSize [in] A new shape length value to be set.
    \remarks 
    The shape length value should not be equal to zero.
  */
  void setSize(double dSize);

  /** \details
    Retrieves the current rotation angle value. 
    The rotation direction is counterclockwise relative to the direction vector for the linetype element. 
    
    \returns Returns the current rotation angle.
    \remarks 
    The rotation angle differs from -2*PI to 2*PI. 
    If the angle is negative, the rotation is clockwise; if the angle is positive, the rotation is counterclockwise. 
    If the angle is equal to zero, the shape object rotation is the same as the linetype rotation. 
    If the absolute angle value is greater than 2*PI, it is converted to the range of -2*PI ... 2*PI. 
    The initial rotation angle value is equal to zero.
  */
  double getRotation( ) const;

  /** \details
    Sets a new rotation angle value. 
    The rotation direction is counterclockwise relative to the direction vector for the linetype element. 
    
    \param dRotation [in] A new rotation angle value to be set.
    \remarks 
    The rotation angle differs from -2*PI to 2*PI. 
    If the angle is negative, the rotation is clockwise; if the angle is positive, the rotation is counterclockwise. 
    If the angle is equal to zero, the shape object rotation is the same as the linetype rotation. 
    If the absolute angle value is greater than 2*PI, it is converted to the range of -2*PI ... 2*PI. 
    The initial rotation angle value is equal to zero.
  */
  void setRotation( double dRotation );

  /** \details
    Retrieves the current scale factor.
    The factor value scales the shape object within the pattern element.
    
    \returns Returns the current scale factor.
    \remarks 
    The scale factor value is a positive non-zero double value.
    If the scale factor is less than 1.0, the shape is condensed. If the scale factor is greater than 1.0, the shape is expanded.
    If the scale factor equals 1.0, the height of the associated text style defines the shape size.
  */
  double getScale( ) const;

  /** \details
    Sets a new scale factor value for the shape object. 
    
    \param dScale [in] A new scale factor value to be set.
    \remarks 
    The scale factor value should be a positive non-zero double value.
    If the scale factor is less than 1.0, the shape is condensed. If the scale factor is greater than 1.0, the shape is expanded.
    If the scale factor equals 1.0, the height of the associated text style defines the shape size.
  */
  void setScale( double dScale );

  /** \details
    Retrieves the current shape offset inside the pattern element. 
    The offset defines a two-dimensional displacement from the insertion point of the shape relative to the end of the current pattern element that contains the shape.
    
    \returns Returns an instance of the <link OdTvVector2d, OdTvVector2d> class that represents the current shape offset.
  */
  OdTvVector2d getOffset() const;

  /** \details
    Sets a new shape offset inside the pattern element. 
    
    \param vOffset [in] An <link OdTvVector2d, OdTvVector2d> object that represents a new shape offset to be set.
    \remarks 
    The offset defines a two-dimensional displacement from the insertion point of the shape relative to the end of the current pattern element that contains the shape.
  */
  void setOffset( const OdTvVector2d& vOffset );

  /** \details
    Retrieves whether the shape object is UCS-oriented inside the pattern element.
    
    \returns Returns true if the shape is oriented relative to the current UCS; the method returns false if the inclusion is oriented relative to the line within which it is embedded. 
    \remarks 
    The initial flag value is equal to false (byLine).
  */
  bool getUcsOriented() const;

  /** \details
    Sets a new value to the flag that determines whether the shape object is UCS-oriented inside the pattern element.
    
    \param isUcsOriented [in] A new flag value. 
    \remarks 
    The flag value is equal to true if the shape is oriented relative to the current UCS (byUCS); 
    the method returns false if the inclusion is oriented relative to the line within which it is embedded (byLine). 
  */
  void setUcsOriented( bool isUcsOriented );

  /** \details
    Retrieves whether the shape object is upright-oriented inside the pattern element. 
    
    \returns Returns true if the shape is upright-oriented; otherwise the method returns false.
    \remarks 
    The initial value of the upright-orientation flag is equal to false.
  */
  bool getUpright() const;

  /** \details
    Sets a new value of the upright-orientation flag. 
    This flag is equal to true if the shape is upright-oriented; otherwise the method returns false.
    
    \param isUpright [in] A new flag value to be set.
    \remarks 
    The initial value of the upright-orientation flag is equal to false.
  */
  void setUpright( bool isUpright );
};

/** \details
  A data type that represents a smart pointer to an <link OdTvLinetypeShapeElement, OdTvLinetypeShapeElement> object.
*/
typedef OdTvSmartPtr<OdTvLinetypeShapeElement> OdTvLinetypeShapeElementPtr;


/** \details
  The base class for the text pattern element.
  \sa
  <link tv_working_with_attributes_linetypes_pattern_text, Work with Linetype Text>
*/
class ODTV_EXPORT OdTvLinetypeTextElement : public OdTvLinetypeElement
{
//DOM-IGNORE-BEGIN
  /** \details
    Empty constructor.
  */
  OdTvLinetypeTextElement();

  /** \details
    Destructor.
  */
  virtual ~OdTvLinetypeTextElement() {};
//DOM-IGNORE-END
  
public:

  /** \details
    Creates a new empty text pattern object. 
    
    \returns Returns a smart pointer to the created text pattern object.
    \remarks 
    The empty text pattern object is ignored during the construction process of the linetype pattern. 
    To make the text pattern object non-empty:
    * Set the text pattern element's length to a positive value using the <link OdTvLinetypeTextElement::setSize@double, setSize()> method.
    * Set the text pattern element's text to a non-empty using the <link OdTvLinetypeTextElement::setText@OdString&, setText()> method.
    * Set the text pattern element's style using the <link OdTvLinetypeTextElement::setStyle@OdTvTextStyleId, setStyle()> method.
  */
  static OdTvSmartPtr<OdTvLinetypeTextElement> createObject(); 

  /** \details
    Retrieves the current text of the text pattern element.
    
    \returns Returns a string object that contains the current text.
    \remarks 
    When the returned string is empty, the text is not set. 
    In this case the text pattern object is ignored during the construction process of the linetype pattern.
  */
  OdString getText() const;

  /** \details
    Sets new text for the text pattern element.
    
    \param textString [in]  A string object that contains the text to be set.
    \remarks
    The text should not be empty.
    Applying text requires the availability of a text style that defines the appearance and parameters of the text inside the pattern element.
    When the text is empty, the text pattern object is ignored during the construction process of the linetype pattern.
  */
  void setText( const OdString& textString );

  /** \details
    Retrieves the current text style of the text pattern element.
    
    \returns Returns an identifier of the <link OdTvTextStyle, text style> object that specifies parameters of the text pattern object.
  */
  OdTvTextStyleId getStyle() const;

  /** \details
    Sets a new text style for the text pattern element. 
    
    The text style specifies parameters of the text pattern object.
    \param idTextStyle [in] An identifier of a <link OdTvTextStyle, text style> object to be set.
    \remarks 
    The initial value is empty.
  */
  void setStyle( OdTvTextStyleId idTextStyle );

  /** \details
    Retrieves the current length of the text pattern element in drawing units.
    
    \returns Returns the current length of the text pattern element. 
    \remarks 
    If the length value is zero, the text pattern element length was not set. 
    In this case the text pattern object is ignored during the construction process of the linetype pattern.
  */
  double getSize() const;

  /** \details
    Sets a new length of the text pattern element in drawing units.
    
    \param dSize [in]  A new text pattern length represented with a double value.
    \remarks 
    The length value should not be equal to zero.
  */
  void setSize(double dSize);

  /** \details
    Retrieves the current rotation angle value. 
    The rotation direction is counterclockwise relative to the direction vector for the linetype element. 
    
    \returns Returns the current rotation angle.
    \remarks 
    The rotation angle differs from -2*PI to 2*PI. 
    If the angle is negative, the rotation is clockwise; if the angle is positive, the rotation is counterclockwise. 
    If the angle is equal to zero, the text pattern object rotation is the same as the linetype rotation. 
    If the absolute angle value is greater than 2*PI, it is converted to the range of -2*PI ... 2*PI. 
    The initial rotation angle value is equal to zero.
  */
  double getRotation( ) const;

  /** \details
    Sets a new rotation angle value. 
    The rotation direction is counterclockwise relative to the direction vector for the linetype element. 
    
    \param dRotation [in] A new rotation angle value to be set.
    \remarks 
    The rotation angle differs from -2*PI to 2*PI. 
    If the angle is negative, the rotation is clockwise; if the angle is positive, the rotation is counterclockwise. 
    If the angle is equal to zero, the text pattern object rotation is the same as the linetype rotation. 
    If the absolute angle value is greater than 2*PI, it is converted to the range of -2*PI ... 2*PI. 
    The initial rotation angle value is equal to zero.
  */
  void setRotation( double dRotation );

  /** \details
    Retrieves the current scale factor.
    The factor value scales the text pattern object within the pattern element.
    
    \returns Returns the current scale factor.
    \remarks 
    The scale factor value is a positive non-zero double value.
    If the scale factor is less than 1.0, the text pattern object is condensed. If the scale factor is greater than 1.0, the text pattern object is expanded.
    If the scale factor equals 1.0, the height of the associated text style defines the text pattern object's size.
  */
  double getScale( ) const;

  /** \details
    Sets a new scale factor value for the text pattern object. 
    
    \param dScale [in] A new scale factor value to be set.
    \remarks 
    The scale factor value should be a positive non-zero double value.
    If the scale factor is less than 1.0, the text pattern object is condensed. If the scale factor is greater than 1.0, the text pattern object is expanded.
    If the scale factor equals 1.0, the height of the associated text style defines the text pattern object's size.
  */
  void setScale( double dScale );

  /** \details
    Retrieves the current text pattern offset inside the pattern element. 
    The offset defines a two-dimensional displacement from the insertion point of the text pattern relative to the end of the current pattern element that contains the text pattern.
    
    \returns Returns an instance of the <link OdTvVector2d, OdTvVector2d> class that represents the current text pattern offset.
  */
  OdTvVector2d getOffset() const;


  /** \details
    Sets a new text pattern offset inside the pattern element. 
    
    \param vOffset [in] An <link OdTvVector2d, OdTvVector2d> object that represents a new text pattern offset to be set.
    \remarks 
    The offset defines a two-dimensional displacement from the insertion point of the text pattern relative to the end of the current pattern element that contains the text pattern.
  */
  void setOffset( const OdTvVector2d& vOffset );

  /** \details
    Retrieves whether the text pattern object is UCS-oriented inside the pattern element.
    
    \returns Returns true if the text pattern is oriented relative to the current UCS; the method returns false if the inclusion is oriented relative to the line within which it is embedded. 
    \remarks 
    The initial flag value is equal to false (byLine).
  */
  bool getUcsOriented() const;

  /** \details
    Sets a new value for the flag that determines whether the text pattern object is UCS-oriented inside the pattern element.
    
    \param isUcsOriented [in] A new flag value. 
    \remarks 
    The flag value is equal to true if the text pattern is oriented relative to the current UCS (byUCS); 
    the method returns false if the inclusion is oriented relative to the line within which it is embedded (byLine). 
  */
  void setUcsOriented( bool isUcsOriented );

  /** \details
    Retrieves whether the text pattern object is upright-oriented inside the pattern element. 
    
    \returns Returns true if the text pattern is upright-oriented; otherwise the method returns false.
    \remarks 
    The initial value of the upright-orientation flag is equal to false.
  */
  bool getUpright() const;

  /** \details
    Sets a new value of the upright-orientation flag. 
    This flag is equal to true if the text pattern is upright-oriented; otherwise the method returns false.
    
    \param isUpright [in] A new flag value to be set.
    \remarks 
    The initial value of the upright-orientation flag is equal to false.
  */
  void setUpright( bool isUpright );
};

/** \details
  A data type that represents a smart pointer to an <link OdTvLinetypeTextElement, OdTvLinetypeTextElement> object.
*/
typedef OdTvSmartPtr<OdTvLinetypeTextElement> OdTvLinetypeTextElementPtr;


/** \details
  The class provides the implementation of the smart pointer functionality for <link OdTvLinetypeElement, OdTvLinetypeElement> class instances.
  This class provides additional constructors for smart pointers to instances of classes derived from the <link OdTvLinetypeElement, OdTvLinetypeElement>.
  \sa
  <link tv_working_with_attributes_linetypes_pattern, Work with Linetype Pattern Elements>
*/
class ODTV_EXPORT OdTvLinetypeElementPtr : public OdTvSmartPtr<OdTvLinetypeElement>
{
public:

  /** \details
    Creates a new smart pointer to an <link OdTvLinetypeElement, OdTvLinetypeElement> object.
  */
  OdTvLinetypeElementPtr();
  
  /** \details
    Creates a new smart pointer to an <link OdTvLinetypeElement, OdTvLinetypeElement> object specified with a raw pointer.
    
    \param pObject  [in] A raw pointer to the <link OdTvLinetypeElement, OdTvLinetypeElement> object.
    \param mode     [in] If this parameter is specified, the reference counter is not incremented.
  */
  OdTvLinetypeElementPtr(const OdTvLinetypeElement* pObject, OdRxObjMod mode);
  
  /** \details
    Creates a new smart pointer to an <link OdTvLinetypeElement, OdTvLinetypeElement> object as a copy of an already existing smart pointer (copy constructor).
    
    \param pObject  [in] Another smart pointer to be copied.
  */
  OdTvLinetypeElementPtr(const OdTvLinetypeElementPtr& pObject);

  /** \details
    Creates a new <link OdTvLinetypeElement, OdTvLinetypeElement> object smart pointer that refers to an existing <link OdTvLinetypeDashElement, OdTvLinetypeDashElement> object.
    
    \param pObject [in] A smart pointer to a <link OdTvLinetypeDashElement, OdTvLinetypeDashElement> object to be referred to with the linetype element's smart pointer.
  */
  OdTvLinetypeElementPtr(const OdTvLinetypeDashElementPtr& pObject);
  
  /** \details
    Creates a new <link OdTvLinetypeElement, OdTvLinetypeElement> object smart pointer that refers to an existing <link OdTvLinetypeSpaceElement, OdTvLinetypeSpaceElement> object.
    
    \param pObject [in] A smart pointer to a <link OdTvLinetypeSpaceElement, OdTvLinetypeSpaceElement> object to be referred to with the linetype element's smart pointer.
  */
  OdTvLinetypeElementPtr(const OdTvLinetypeSpaceElementPtr& pObject);
  
  /** \details
    Creates a new <link OdTvLinetypeElement, OdTvLinetypeElement> object smart pointer that refers to an existing <link OdTvLinetypeDotElement, OdTvLinetypeDotElement> object.
    
    \param pObject [in] A smart pointer to a <link OdTvLinetypeDotElement, OdTvLinetypeDotElement> object to be referred to with the linetype element's smart pointer.
  */
  OdTvLinetypeElementPtr(const OdTvLinetypeDotElementPtr& pObject);
  
  /** \details
    Creates a new <link OdTvLinetypeElement, OdTvLinetypeElement> object smart pointer that refers to an existing <link OdTvLinetypeShapeElement, OdTvLinetypeShapeElement> object.
    
    \param pObject [in] A smart pointer to a <link OdTvLinetypeShapeElement, OdTvLinetypeShapeElement> object to be referred to with the linetype element's smart pointer.
  */
  OdTvLinetypeElementPtr(const OdTvLinetypeShapeElementPtr& pObject);
  
  /** \details
    Creates a new <link OdTvLinetypeElement, OdTvLinetypeElement> object smart pointer that refers to an existing <link OdTvLinetypeTextElement, OdTvLinetypeTextElement> object.
    
    \param pObject [in] A smart pointer to a <link OdTvLinetypeTextElement, OdTvLinetypeTextElement> object to be referred to with the linetype element's smart pointer.
  */
  OdTvLinetypeElementPtr(const OdTvLinetypeTextElementPtr& pObject);

  /** \details 
    Converts the smart pointer to an <link OdTvLinetypeElement, OdTvLinetypeElement> object into a smart pointer to an <link OdTvLinetypeDashElement, OdTvLinetypeDashElement> object.
    
    \returns Returns a smart pointer to an <link OdTvLinetypeDashElement, OdTvLinetypeDashElement> object.
  */
  OdTvLinetypeDashElementPtr    getAsDash() const;
  
  /** \details 
    Converts the smart pointer to an <link OdTvLinetypeElement, OdTvLinetypeElement> object into a smart pointer to an <link OdTvLinetypeSpaceElement, OdTvLinetypeSpaceElement> object.
    
    \returns Returns a smart pointer to an <link OdTvLinetypeSpaceElement, OdTvLinetypeSpaceElement> object.
  */
  OdTvLinetypeSpaceElementPtr   getAsSpace() const;
  
  /** \details 
    Converts the smart pointer to an <link OdTvLinetypeElement, OdTvLinetypeElement> object into a smart pointer to an <link OdTvLinetypeDotElement, OdTvLinetypeDotElement> object.
    
    \returns Returns a smart pointer to an <link OdTvLinetypeDotElement, OdTvLinetypeDotElement> object.
  */
  OdTvLinetypeDotElementPtr     getAsDot() const;
  
  /** \details 
    Converts the smart pointer to an <link OdTvLinetypeElement, OdTvLinetypeElement> object into a smart pointer to an <link OdTvLinetypeShapeElement, OdTvLinetypeShapeElement> object.
    
    \returns Returns a smart pointer to an <link OdTvLinetypeShapeElement, OdTvLinetypeShapeElement> object.
  */
  OdTvLinetypeShapeElementPtr   getAsShape() const;
  
  /** \details 
    Converts the smart pointer to an <link OdTvLinetypeElement, OdTvLinetypeElement> object into a smart pointer to an <link OdTvLinetypeTextElement, OdTvLinetypeTextElement> object.
    
    \returns Returns a smart pointer to an <link OdTvLinetypeTextElement, OdTvLinetypeTextElement> object.
  */
  OdTvLinetypeTextElementPtr    getAsText() const;
};

/** \details
  A data type that represents an array of smart pointers to an <link OdTvLinetypeElement, OdTvLinetypeElement> object.
*/
typedef OdVector<OdTvLinetypeElementPtr>  OdTvLinetypeElementArray;



#endif // _ODTV_LINETYPEELEMENT_H_INCLUDED_
