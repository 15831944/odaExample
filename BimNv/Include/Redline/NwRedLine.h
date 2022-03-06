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

#ifndef __NWREDLINE_INCLUDED_
#define __NWREDLINE_INCLUDED_

#include "NwRedLineType.h"
#include "NwColor.h"
#include "NwObject.h"
#include "NwExport.h"

/** \details
  This is the base class for redline objects.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwRedLine : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwRedLine);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor.
  */
  OdNwRedLine();

  /** \details
    Constructor for objects of the OdNwRedLine class. Creates a new
    OdNwRedLine object for the specified item.

    \param pImpl [in] Item to create an OdNwRedLine object for.
  */
  explicit OdNwRedLine(OdNwObjectImpl* pImpl);

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwRedLine();

public:
  /** \details
    Returns the redline type.

    \returns Redline type as a value defined by the NwRedLineType::Enum enumeration.
  */
  NwRedLineType::Enum getType() const;
  /** \details
    Returns the line thickness.

    \returns Line thickness as an OdUInt32 value.
  */
  OdUInt32 getLineThikness() const;
  /** \details
    Returns the line pattern.

    \returns Line pattern as an OdUInt32 value.
  */
  OdUInt16 getLinePattern() const;
  /** \details
    Returns the line color.

    \returns Line color as an OdNwColor value.
  */
  OdNwColor getLineColor() const;

public:
  /** \details
    Sets the line thickness.

    \param val [in] New line thickness value.
  */
  void setLineThikness(OdUInt32 val);
  /** \details
    Sets the line pattern.

    \param val [in] New line pattern value.
  */
  void setLinePattern(OdUInt16 val);
  /** \details
    Sets the line color.

    \param val [in] New line color value.
  */
  void setLineColor(const OdNwColor& val);
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwRedLine object pointers.
*/
typedef OdSmartPtr<OdNwRedLine> OdNwRedLinePtr;

#endif //__NWREDLINE_INCLUDED_
