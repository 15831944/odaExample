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

#ifndef _ODPRCUNITSFORMATTER_H_IMPL_
#define _ODPRCUNITSFORMATTER_H_IMPL_

#include "TD_PackPush.h"

#include "DbAux/PrcUnitsFormatter.h"

class OdPrcFile;

/** \details 
This class provides the default implementation for OdDbUnitsFormatter. 

<group PRC_DbAux_Classes>
*/
class PRC_TOOLKIT OdPrcUnitsFormatterImpl : public OdPrcUnitsFormatter
{ 
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcUnitsFormatterImpl);
  //DOM-IGNORE-END

  /** \details 
  Returns the specified distance value as a string.
  The returned value depends on the DIMZIN, LUNITS, LUPREC, and UNITMODE system variables.
  
  \param value [in] A value to format.
  */
  virtual OdString formatLinear(double value) const;

  /** \details 
  Returns the specified string as a distance value.
  The returned value depends on the UNITMODE system variable.
  
  \param string [in] A string to unformat.
  */
  virtual double unformatLinear(const OdString& string) const;

  /** \details 
  Returns the specified angle value as a string.
  The returned value depends on the ANGBASE, AUNITS, AUPREC, DIMZIN, and UNITMODE system variables.
  
  \param value [in] A value to format.
  
  \remarks 
  All angles are expressed in radians.
  */
  virtual OdString formatAngle(double value) const;

  /** \details 
  Returns the specified string as an angle value.
  The returned value depends on the ANGBASE system variable.
  
  \param string [in] A string to unformat.
  
  \remarks 
  All angles are expressed in radians.
  */
  virtual double unformatAngle(const OdString& string) const;

  /** \details 
  Returns the specified 3D point value as a string.
  The returned value depends on the DIMZIN, LUNITS, LUPREC, and UNITMODE system variables.
  
  \param value [in] A value to format.
  */
  virtual OdString formatPoint(const OdGePoint3d& value) const;

  /** \details 
  Returns the specified string as a point value.
  
  \param string [in] A string to unformat.
  */
  virtual OdGePoint3d unformatPoint(const OdString& string) const;

  /** \details 
  Sets a database that the unit formatter is associated with.
  
  \param db [in] A pointer to an associated database (.prc file).
  */
  void setDatabase(OdPrcFile* db);

  /** \details 
  Returns the specified color value as a string.
  
  \param value [in] A color value to format.
  */
  virtual OdString formatCmColor(const OdCmColorBase& value) const;

  /** \details 
  Returns the specified string as a color value.
  
  \param string [in] A string to unformat.
  */
  virtual OdSharedPtr<OdCmColorBase> unformatCmColor(const OdString& string) const;
protected:
  OdPrcFile* m_pDb;
};

#include "TD_PackPop.h"

#endif // _ODPRCUNITSFORMATTER_H_IMPL_
