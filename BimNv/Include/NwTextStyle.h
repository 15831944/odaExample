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

#ifndef __TNW_TEST_STYLE_H__
#define __TNW_TEST_STYLE_H__

#include "NwObject.h"
#include "RxSystemServices.h"

/** \details
  This class represents a text style.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwTextStyle : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwTextStyle);
  //DOM-IGNORE-END

protected:
  OdNwTextStyle();
  explicit OdNwTextStyle(OdNwObjectImpl* pImpl);

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwTextStyle();

public:

  /** \details
    Returns the type face for this text style.

    \returns
    Returns an OdString value of type face.
  */
  OdString getTypeFace() const;

  /** \details
    Returns the font height for this text style.

    \returns
    Returns a double precision floating-point value of font height.
  */
  double getFontHeight() const;

  /** \details
    Returns the point size for this text style.

    \returns
    Returns an integer value of point size.
  */
  OdUInt32 getPointSize() const;

  /** \details
    Returns the font weight for this text style.

    \returns
    Returns an integer value of font weight.
  */
  OdUInt32 getFontWeight() const;

  /** \details
    Returns the text style for this text style.

    \returns
    Returns an integer value of the style.
  */
  OdUInt32 getStyle() const;

  /** \details
    Returns the render style for this text style.

    \returns
    Returns an integer value of the render style.
  */
  OdUInt32 getRenderStyle() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwTextStyle object pointers.
*/
typedef OdSmartPtr<OdNwTextStyle> OdNwTextStylePtr;

#endif //__TNW_TEST_STYLE_H__
