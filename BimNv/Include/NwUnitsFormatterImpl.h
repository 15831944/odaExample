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

#ifndef _OD_NW_UNITSFORMATTER_H_IMPL_
#define _OD_NW_UNITSFORMATTER_H_IMPL_

#include "TD_PackPush.h"

#include "NwUnitsFormatter.h"
#include "NwDatabase.h"

/** \details
  This class provides default implementation for OdDbUnitsFormatter.

  {group:OdNw_Classes}

  <group Nw_Classes>
*/
class NWDBEXPORT OdNwUnitsFormatterImpl : public OdNwUnitsFormatter
{
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwUnitsFormatterImpl);
  //DOM-IGNORE-END

  /** \details
    Returns the specified distance value as a string.
    \param value [in] Value to format.
    \returns Specified distance value as a string.
    \remarks
    The returned value depends on the DIMZIN, LUNITS, LUPREC, and UNITMODE
    system variables.
  */
  virtual OdString formatLinear(double value) const;

  /** \details
    Returns the specified string as a distance value.
    \param string [in] String to unformat.
    \returns Distance value.    \remarks
    The returned value depends on the UNITMODE system variable.
  */
  virtual double unformatLinear(const OdString& string) const;

  /** \details
    Returns the specified angle value as a string.
    \param value [in] Value to format.
    \returns Specified angle value as a string.    \remarks
    The returned value depends on the ANGBASE, AUNITS, AUPREC, DIMZIN, and
    UNITMODE system variables.
    Note: All angles are expressed in radians.
  */
  virtual OdString formatAngle(double value) const;

  /** \details
    Returns the specified string as an angle value.
    \param string [in] String to unformat.
    \returns Angle value.    \remarks
    The returned value depends on the ANGBASE system variable.
    Note: All angles are expressed in radians.
  */
  virtual double unformatAngle(const OdString& string) const;

  /** \details
    Returns the specified 3D point value as a string.
    \param value [in] Value to format.
    \returns Specified 3D point value as a string.    \remarks
    The returned value depends on the DIMZIN, LUNITS, LUPREC, and UNITMODE
    system variables.
  */
  virtual OdString formatPoint(const OdGePoint3d& value) const;

  /** \details
    Returns the specified string as a 3D point value.
    \param string [in] String to unformat.
    \returns 3D point value.
  */
  virtual OdGePoint3d unformatPoint(const OdString& string) const;

  /** \details
    Sets the currant database for this units formatter object.
    \param db [in] Database to set.
  */
  void setDatabase(OdNwDatabase* db);

  /** \details
    Returns the specified color value as a string.
    \param value [in] Value to format.
    \returns Specified color value as a string.
  */
  virtual OdString formatCmColor(const OdCmColorBase& value) const;

  /** \details
    Returns the specified string as a color value.
    \param string [in] String to unformat.
    \returns Shared pointer to the color value.
  */
  virtual OdSharedPtr<OdCmColorBase> unformatCmColor(const OdString& string) const;
protected:
  //DOM-IGNORE-BEGIN
  OdNwDatabase* m_pDb;
  //DOM-IGNORE-END
};

#include "TD_PackPop.h"

#endif // _OD_NW_UNITSFORMATTER_H_IMPL_
