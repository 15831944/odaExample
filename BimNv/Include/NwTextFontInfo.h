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

#ifndef __TNW_TEXTFONTINFO_H__
#define __TNW_TEXTFONTINFO_H__

#include "NwExport.h"
#include "RxObject.h"

class OdNwTextFontInfoImpl;

/** \details
  This class represents a text font.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwTextFontInfo
{
public:
  /** \details
    Default constructor. Creates a new OdNwTextFontInfo object.
  */
  OdNwTextFontInfo();
  
  /** \details
    Copy constructor. Creates a new OdNwTextFontInfo object from the specified object.
  */
  OdNwTextFontInfo(const OdNwTextFontInfo&);
  
  /** \details
    Copy operator.
  */
  OdNwTextFontInfo& operator=(const OdNwTextFontInfo&);

  /** \details
    Default destructor. Frees allocated resources.
  */
  ~OdNwTextFontInfo();

public:

  /** \details
    Returns the name of the font.

    \returns An OdString object with the name of the font.
  */
  OdString getName() const;

  /** \details
    Checks whether the font is italic.

    \returns True if the font is italic, or false otherwise.
  */
  bool isItalic() const;

private:
  friend class OdNwTextFontInfoImpl;
  OdSmartPtr<OdNwTextFontInfoImpl> m_pImpl;
};

#endif //__TNW_TEXTFONTINFO_H__
