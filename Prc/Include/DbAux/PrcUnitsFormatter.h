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

#ifndef _ODPRCUNITSFORMATTER_H_INCLUDED_
#define _ODPRCUNITSFORMATTER_H_INCLUDED_

#include "OdUnitsFormatter.h"

class OdGePoint3d;

/** \details 
An abstract class which implements a units formatter interface. 

<group PRC_DbAux_Classes>
*/
class ODRX_ABSTRACT PRC_TOOLKIT OdPrcUnitsFormatter : public OdUnitsFormatter
{ 
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcUnitsFormatter);
  //DOM-IGNORE-END

  /** \details 
  Returns the specified 3D point value as a string.
  
  \param value [in] A value to format.
  */
  virtual OdString formatPoint(const OdGePoint3d& value) const = 0;

  /** \details 
  Returns the specified string as a point value.
  
  \param string [in] A string to be unformatted.
  */
  virtual OdGePoint3d unformatPoint(const OdString& string) const = 0;
};

/** \details 
This template class is a specialization of the OdSmartPtr class for OdPrcUnitsFormatter object pointers.
*/
typedef OdSmartPtr<OdPrcUnitsFormatter> OdPrcUnitsFormatterPtr;


#endif //#ifndef _ODPRCUNITSFORMATTER_H_INCLUDED_
