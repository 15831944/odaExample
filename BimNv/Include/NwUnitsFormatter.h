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

#ifndef _ODNWUNITSFORMATTER_H_INCLUDED_
#define _ODNWUNITSFORMATTER_H_INCLUDED_

#include "OdUnitsFormatter.h"
#include "NwCmColor.h"

class OdGePoint3d;

/** \details
  This class defines the interface for a Units Formatter.

  {group:OdNw_Classes}

  <group Database_Classes>
*/
class ODRX_ABSTRACT NWDBEXPORT OdNwUnitsFormatter : public OdUnitsFormatter
{
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwUnitsFormatter);
  //DOM-IGNORE-END

  /** \details
    Returns the specified 3D point value as a string.
    \param value [in] Value to format.
    \returns Specified 3D point value as a string.
    \remarks
    The returned value depends on the DIMZIN, LUNITS, LUPREC, and UNITMODE
    system variables.
  */
  virtual OdString formatPoint(const OdGePoint3d& value) const = 0;

  /** \details
    Returns the specified string as a 3D point value.
    \param string [in] String to unformat.
    \returns 3D point value.
  */
  virtual OdGePoint3d unformatPoint(const OdString& string) const = 0;

  /** \details
    Returns the specified color value or OdBmCmColor object as a string.
    \param value [in] Value to format.
    \returns Specified color value or OdNwCmColor object as a string.
  */
  static OdString formatColor(const OdNwCmColor& value);

  /** \details
    Returns the specified string as an OdBmCmColor object.
    \param string [in] String to unformat.
    \returns OdNwCmColor object.
  */
  static OdNwCmColor unformatColor(const OdString& string);
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwUnitsFormatter object pointers.
*/
typedef OdSmartPtr<OdNwUnitsFormatter> OdNwUnitsFormatterPtr;


#endif //#ifndef _ODNWUNITSFORMATTER_H_INCLUDED_
