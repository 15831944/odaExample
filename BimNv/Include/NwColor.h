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

#ifndef __TNW_COLOR_H__
#define __TNW_COLOR_H__

#include "NwExport.h"
#include "NwObject.h"
#include "SharedPtr.h"

class OdNwColorImpl;

/** \details
  This class represents a color.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwColor
{
public:

  /** \details
    Default constructor. 
    Sets red, blue and green components of the color to 0.0 and sets alpha to 1.0 (opaque).
  */
  OdNwColor();
  
  /** \details
    Constructor. Creates a color with the given red, blue, green and alpha components.
  */
  OdNwColor(float a, float r, float g, float b);
  
  /** \details
    Constructor. Creates a color with the given red, blue, green components and sets alpha to the default value 1.0 (opaque).
  */
  OdNwColor(float r, float g, float b);
  
  /** \details
    Copy constructor. Creates a color from the given OdNwColor object.
  */
  OdNwColor(const OdNwColor&);
  
  /** \details
    Copy assignment operator.
  */
  OdNwColor& operator=(const OdNwColor&);

  /** \details
    Destructor. Frees allocated resources.
  */
  ~OdNwColor();

  /** \details
    Returns the object ID of the color.

    \return OdNwObjectId object with the database ID of the color.

    \remarks
    The method is deprecated.
  */
  virtual OdNwObjectId objectId() const;

  /** \details
    Returns the object ID of the color's owner.

    \return Pointer to OdDbStub with the database ID of the color's owner.

    \remarks
    The method is deprecated.
  */
  virtual OdDbStub* ownerId() const;

  /** \details
    Returns the database ID of the color.

    \return Pointer to OdDbStub with the database ID of the color.

    \remarks Returns a null pointer if the color is not persistent.

    \remarks
    The method is deprecated.
  */
  OdDbStub* id() const;

public:

  /** \details
    Gets the alpha component of the color.

    \returns Float value of the color's alpha component.
  */
  float A() const;

  /** \details
    Gets the red component of the color.

    \returns Float value of the color's red component.
  */
  float R() const;

  /** \details
    Gets the green component of the color.

    \returns Float value of the color's green component.
  */
  float G() const;

  /** \details
    Gets the blue component of the color.

    \returns Float value of the color's blue component.
  */
  float B() const;

public:

  /** \details
    Returns the color in the ODCOLORREF type.
  */
  ODCOLORREF ToColor() const;

  /** \details
    Scales the intensity of the color with color values from the input OdNwColor object.

    \param color [in]  Input OdNwColor object used to scale the color intensity. The current value of each component is multiplied by a value of the corresponding component of the input color.  

    \returns OdNwColor object with the multiplied values of the color components.
  */
  OdNwColor Multiply(const OdNwColor& color) const;

  /** \details
    Scales the intensity of the color with color values from the input ODCOLORREF object.

    \param color [in]  Input ODCOLORREF object used to scale the color intensity. Current value of each component is multiplied by a normalized value of the corresponding component of the input color.

    \returns OdNwColor object with the value of scaling.
  */
  OdNwColor Multiply(ODCOLORREF color) const;

private:
  friend class OdNwColorImpl;
  OdSharedPtr<OdNwColorImpl> m_pImpl;
};

#endif // __TNW_COLOR_H__
