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

#ifndef _ODTV_LINETYPEELEMENTIMPL_H_INCLUDED_
#define _ODTV_LINETYPEELEMENTIMPL_H_INCLUDED_

#include "TD_PackPush.h"

#include "TvLinetypeElement.h"

/** \details
    This class is the base implementation class for all typed objects of the linetype pattern (dashes, dots, spaces and shapes (or texts))
*/
class OdTvLinetypeElementImpl
{
  friend class OdTvLinetypeElement;

protected:

  enum ShapeFlags
  {
    kAbsoluteRotation = 1 << 0,
    kUprightRotation = 1 << 1
  };

public:

  /** \details
    Empty constructor
  */
  OdTvLinetypeElementImpl();

  /** \details
    Destructor
  */
  virtual ~OdTvLinetypeElementImpl();

  /** \details
  Returns the linetype pattern elements type
  */
  virtual OdTvLinetypeElement::Type getType() const;

  /** \details
  Returns the valid state of the linetype pattern element
  */
  virtual bool isValid() const;

protected:

  OdRefCounter      m_nRefCounter;
};


/** \details
    This class is used for the specifying the dash elements within a linetype pattern
*/
class OdTvLinetypeDashElementImpl : public OdTvLinetypeElementImpl
{
  public:

  /** \details
    Empty constructor
  */
  OdTvLinetypeDashElementImpl();

  /** \details
  Constructs an object with the defined length in drawing units.
  */
  OdTvLinetypeDashElementImpl (double dSize); 

  /** \details
    Destructor
  */
  virtual ~OdTvLinetypeDashElementImpl() {};

  /** \details
  Returns the linetype pattern elements type
  */
  virtual OdTvLinetypeElement::Type getType() const;

  /** \details
  Returns the valid state of the linetype pattern element
  */
  virtual bool isValid() const;

  /** \details
    Sets the length of the dash in drawing units (should be positive).

    \param dSize [in]  Dash length as a Double value.
  */
  void setSize(double dSize);

  /** \details
    Returns the length of the linetype dash in drawing units. If a length value is negative,
    it means that the dash length was not set. Such objects will be ignored in the process of constructing
    of the linetype pattern.
  */
  double getSize() const;

private:
  double m_dLength;
};


/** \details
    This class is used for the specifying the space elements within a linetype pattern
*/
class OdTvLinetypeSpaceElementImpl : public OdTvLinetypeElementImpl
{
  public:

  /** \details
    Empty constructor
  */
  OdTvLinetypeSpaceElementImpl();

  /** \details
  Constructs an object with the defined length in drawing units.
  */
  OdTvLinetypeSpaceElementImpl (double dSize); 

  /** \details
    Destructor
  */
  virtual ~OdTvLinetypeSpaceElementImpl() {};

  /** \details
  Returns the linetype pattern elements type
  */
  virtual OdTvLinetypeElement::Type getType() const;

  /** \details
  Returns the valid state of the linetype pattern element
  */
  virtual bool isValid() const;

  /** \details
    Sets the length of the dash in drawing units (should be positive).

    \param dSize [in]  Dash length as a Double value.
  */
  void setSize(double dSize);

  /** \details
    Returns the length of the linetype dash in drawing units. If a length value is negative,
    it means that the dash length was not set. Such objects will be ignored in the process of constructing
    of the linetype pattern.
  */
  double getSize() const;

private:
  double m_dLength;
};


/** \details
    This class is used for the specifying the dot elements within a linetype pattern.
*/
/** \details
    This class is used for the specifying the dash elements within a linetype pattern
*/
class OdTvLinetypeDotElementImpl : public OdTvLinetypeElementImpl
{
  public:

  /** \details
    Empty constructor
  */
  OdTvLinetypeDotElementImpl();

  /** \details
    Destructor
  */
  virtual ~OdTvLinetypeDotElementImpl() {};

  /** \details
  Returns the linetype pattern elements type
  */
  virtual OdTvLinetypeElement::Type getType() const;

  /** \details
  Returns the valid state of the linetype pattern element
  */
  virtual bool isValid() const;
};



/** \details
    This class is used for the specifying the shape elements within a linetype pattern
*/
class OdTvLinetypeShapeElementImpl : public OdTvLinetypeElementImpl
{
  public:

  /** \details
    Empty constructor
  */
  OdTvLinetypeShapeElementImpl();

  /** \details
    Destructor
  */
  virtual ~OdTvLinetypeShapeElementImpl() {};

  /** \details
  Returns the linetype pattern elements type
  */
  virtual OdTvLinetypeElement::Type getType() const;

  /** \details
  Returns the valid state of the linetype pattern element
  */
  virtual bool isValid() const;

 /** \details
    Returns the code of this shape object. When the code is zero, it means that the shape's
    code was not set. Such objects will be ignored in the process of constructing
    of the linetype pattern.
  */
  OdUInt16 getSourceNumber( ) const;

  /** \details
    Sets the code of the shape (should be greater than zero).

    \param shapeNumber [in]  Shape code to be set as an Integer value.

    \remarks
    Applying a shape's code requires the availability of the .shx file which must be 
    previously loaded and the text style that defines the shape parameters. 
  */
  void setSourceNumber( OdUInt16 shapeNumber );

  /** \details
    Returns the text style ID which specifies the characteristics of this shape object.
  */
  OdTvTextStyleId getStyle() const;

  /** \details
    Sets the text style ID for this shape object, which specifies the characteristics of the shape oject.
    The initial value is empty.
      
    \param idTextStyle [in]  text style ID to be set.
  */
  void setStyle( OdTvTextStyleId idTextStyle );

  /** \details
    Returns the length of the shape's pattern element in drawing units. If a length value is negative,
    it means that the shape's pattern element length was not set. Such objects will be ignored in the process of constructing
    of the linetype pattern.
  */
  double getSize() const;

  /** \details
    Sets the length of the shape's pattern element in drawing units (should be positive).

    \param dSize [in]  Shape length as a Double value.
  */
  void setSize(double dSize);

  /** \details
    Returns the angle on which the shape is rotated within the pattern element 
    counterclockwise relative to the direction vector of  
    the linetype in the range -2PI to 2PI radians. If the angle is positive, the shape 
    is rotated counterclockwise. If the angle is negative, the shape is rotated clockwise.
    If the angle is zero, the direction of the linetype and shape are the same.
  */
  double getRotation( ) const;

  /** \details
    Sets the angle on which the shape is rotated within the pattern element 
    counterclockwise relative to the direction vector of  
    the linetype in the range -2PI to 2PI radians. A positive angle rotates the shape 
    counterclockwise. A negative angle rotates the shape clockwise. A zero angle indicates 
    that the direction of the linetype and shape are the same. If an absolute angle value 
    is greater than 2PI, it converts to the range ±2PI. The initial value is zero by default.
  */
  void setRotation( double dRotation );

    /** \details
    Returns the factor by which the shape scales within the pattern element. If the scale factor is less than 1.0,
    the ishape is condensed. If the scale factor is greater than 1.0, the shape is expanded.
    If the scale factor equals 1.0, the height of the associated text style defines the shape size.
  */
  double getScale( ) const;

  /** \details
    Sets the factor by which shape scales within the pattern element. A value less than 1.0 
    condenses the shape. A value greater than 1.0 expandes the inclusion.
    A value 1.0 defines shape size specified the associated text style.

    \param shapeScale [in]  Scale factor as a positive non-zero Double value.

  */
  void setScale( double dScale );

  /** \details
    Returns the shape offset inside the pattern element. This
    offset defines the two-dimensional displacement to the insertion point of the shape 
    relative to the end of the current pattern element that contains the shape.
    This method returns the offset as an instance of the two-dimensional vector object.
  */
  OdTvVector2d getOffset() const;


  /** \details
    Sets the shape offset inside the pattern element. This offset specifies the two-dimensional displacement
    to the insertion point of an shape relative to the end of the current pattern element that contains the shape.
    
    \param shapeOffset [in]  Offset as an instance of the two-dimensional vector object.
  */
  void setOffset( const OdTvVector2d& vOffset );

    /** \details
    Determines whether the shape is UCS-oriented inside the pattern element and returns 
    True if the shape is oriented relative to the current UCS or False if the inclusion
    is oriented relative to the line within which it is embedded. 
  */
  bool getUcsOriented() const;

  /** \details
    Sets the UCS-orientation of the shape inside the pattern element either relative to the current UCS (byUCS)
    or relative to the line within which it is embedded (byLine).
    The initial value is False (byLine) by default.

    \param isUcsOriented [in]  True - to orient the inclusion byUCS, or False - to orient the inclusion 
                      byLine.
  */
  void setUcsOriented( bool isUcsOriented );

  /** \details
    Determines whether the shape is Upright-oriented inside the pattern element and
    returns True if the shape is oriented upright.
  */
  bool getUpright() const;

  /** \details
    Sets the Upright orientation of the shape inside the pattern element.
    The initial value is False by default.

    \param isUpright [in]  True - to orient the inclusion Upright.
  */
  void setUpright( bool isUpright );

private:
  double            m_dLength;
  OdUInt16          m_iShapeNumber;
  OdTvTextStyleId  m_styleId;
  
  double            m_dRotation;
  double            m_dScale;
  OdTvVector2d     m_vOffset;
  OdUInt8           m_flags;
};

/** \details
    This class is used for the specifying the text elements within a linetype pattern
*/
class OdTvLinetypeTextElementImpl : public OdTvLinetypeElementImpl
{
  public:

  /** \details
    Empty constructor
  */
  OdTvLinetypeTextElementImpl();

  /** \details
  Destructor
  */
  virtual ~OdTvLinetypeTextElementImpl() {};

  /** \details
  Returns the linetype pattern elements type
  */
  virtual OdTvLinetypeElement::Type getType() const;

  /** \details
  Returns the valid state of the linetype pattern element
  */
  virtual bool isValid() const;

  /** \details
    Returns the text of this text object. When the string is empty, it means that the text
    was not set. Such objects will be ignored in the process of constructing of the linetype pattern.
  */
  OdString getText() const;

  /** \details
    Sets the text string for this text object (should be not empty).

    \param textString [in]  Text string to be set.

    \remarks
    Applying a text requires the availability of a text style that defines the 
    appearance and parameters of the text inside the pattern element.
  */
  void setText( const OdString& textString );

  /** \details
    Returns the text style ID which specifies the characteristics of this text object.
  */
  OdTvTextStyleId getStyle() const;

  /** \details
    Sets the text style ID for this text object, which specifies the characteristics of the text oject.
    The initial value is empty.
      
    \param idTextStyle [in]  text style ID to be set.
  */
  void setStyle( OdTvTextStyleId idTextStyle );

  /** \details
    Returns the length of the text's pattern element in drawing units. If a length value is negative,
    it means that the shape's pattern element length was not set. Such objects will be ignored in the process of constructing
    of the linetype pattern.
  */
  double getSize() const;

  /** \details
    Sets the length of the text's pattern element in drawing units (should be positive).

    \param dSize [in]  Shape length as a Double value.
  */
  void setSize(double dSize);

  /** \details
    Returns the angle on which the text is rotated within the pattern element 
    counterclockwise relative to the direction vector of  
    the linetype in the range -2PI to 2PI radians. If the angle is positive, the text 
    is rotated counterclockwise. If the angle is negative, the text is rotated clockwise.
    If the angle is zero, the direction of the linetype and text are the same.
  */
  double getRotation( ) const;

  /** \details
    Sets the angle on which the text is rotated within the pattern element 
    counterclockwise relative to the direction vector of  
    the linetype in the range -2PI to 2PI radians. A positive angle rotates the text 
    counterclockwise. A negative angle rotates the text clockwise. A zero angle indicates 
    that the direction of the linetype and text are the same. If an absolute angle value 
    is greater than 2PI, it converts to the range ±2PI. The initial value is zero by default.
  */
  void setRotation( double dRotation );

    /** \details
    Returns the factor by which the text scales within the pattern element. If the scale factor is less than 1.0,
    the ishape is condensed. If the scale factor is greater than 1.0, the text is expanded.
    If the scale factor equals 1.0, the height of the associated text style defines the text size.
  */
  double getScale( ) const;

  /** \details
    Sets the factor by which text scales within the pattern element. A value less than 1.0 
    condenses the text. A value greater than 1.0 expandes the inclusion.
    A value 1.0 defines text size specified the associated text style.

    \param shapeScale [in]  Scale factor as a positive non-zero Double value.

  */
  void setScale( double dScale );

  /** \details
    Returns the text offset inside the pattern element. This
    offset defines the two-dimensional displacement to the insertion point of the text 
    relative to the end of the current pattern element that contains the text.
    This method returns the offset as an instance of the two-dimensional vector object.
  */
  OdTvVector2d getOffset() const;


  /** \details
    Sets the text offset inside the pattern element. This offset specifies the two-dimensional displacement
    to the insertion point of an text relative to the end of the current pattern element that contains the text.
    
    \param shapeOffset [in]  Offset as an instance of the two-dimensional vector object.
  */
  void setOffset( const OdTvVector2d& vOffset );

    /** \details
    Determines whether the text is UCS-oriented inside the pattern element and returns 
    True if the text is oriented relative to the current UCS or False if the inclusion
    is oriented relative to the line within which it is embedded. 
  */
  bool getUcsOriented() const;

  /** \details
    Sets the UCS-orientation of the text inside the pattern element either relative to the current UCS (byUCS)
    or relative to the line within which it is embedded (byLine).
    The initial value is False (byLine) by default.

    \param isUcsOriented [in]  True - to orient the inclusion byUCS, or False - to orient the inclusion 
                      byLine.
  */
  void setUcsOriented( bool isUcsOriented );

  /** \details
    Determines whether the text is Upright-oriented inside the pattern element and
    returns True if the text is oriented upright.
  */
  bool getUpright() const;

  /** \details
    Sets the Upright orientation of the text inside the pattern element.
    The initial value is False by default.

    \param isUpright [in]  True - to orient the inclusion Upright.
  */
  void setUpright( bool isUpright );

private:
  double            m_dLength;
  OdString          m_textString;
  OdTvTextStyleId  m_styleId;
  
  double            m_dRotation;
  double            m_dScale;
  OdTvVector2d     m_vOffset;
  OdUInt8           m_flags;
};

#include "TD_PackPop.h"

#endif //_ODTV_LINETYPEELEMENTIMPL_H_INCLUDED_
