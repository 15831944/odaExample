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

#ifndef _PRCMARKUPSERIALIZATIONHELPER_INCLUDED_
#define _PRCMARKUPSERIALIZATIONHELPER_INCLUDED_ 
 

#include "PrcFontKeysSameFont.h"

/** \details
    <group PRC_Markup_Classes>
    Class stores data of data serialization for markup font information.
*/
class PRC_TOOLKIT OdPrcMarkupSerializationHelper
{
private:
  OdPrcFontKeysSameFontArray m_FontKeysSameFont;
  OdString                   m_default_font_family_name;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcMarkupSerializationHelper)
  //DOM-IGNORE-END

  /** \details
  Returns the current array of font keys sharing the same font.
  The array is returned as a reference to an OdPrcFontKeysSameFontArray object, therefore it can be used to set new font keys.
  */
  OdPrcFontKeysSameFontArray &fontKeysSameFont();
  
  /** \details
  Returns the current array of font keys sharing the same font.
  */
  const OdPrcFontKeysSameFontArray &fontKeysSameFont() const;
  
  /** \details
  Sets a new default font family name for text.

  \param default_font_family_name [in] A new default font family name to be set.
  */
  void setDefaultFontFamilyName(OdString default_font_family_name);
  
  /** \details
  Returns the current default font family name for text.
  */
  OdString defaultFontFamilyName() const;
};

#endif // _PRCMARKUPSERIALIZATIONHELPER_INCLUDED_

