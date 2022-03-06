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

#ifndef __NWREDLINEELLIPSE_INCLUDED_
#define __NWREDLINEELLIPSE_INCLUDED_

#include "NwRedLine.h"
#include "Ge/GePoint2d.h"

/** \details
  This class represents ellipse redline objects.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwRedLineEllipse : public OdNwRedLine
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwRedLineEllipse);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwRedLineEllipse object.
  */
  OdNwRedLineEllipse();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwRedLineEllipse();

public:
  /** \details
    Returns the minimum point.

    \returns Minimum point as an OdGePoint2d object.
  */
  OdGePoint2d getMin() const;
  /** \details
    Returns the maximum point.

    \returns Maximum point as an OdGePoint2d object.
  */
  OdGePoint2d getMax() const;

public:
  /** \details
    Sets the minimum point.

    \param val [in] New minimum point.
  */
  void setMin(const OdGePoint2d& val);
  /** \details
    Sets the maximum point.

    \param val [in] New maximum point.
  */
  void setMax(const OdGePoint2d& val);
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwRedLineEllipse object pointers.
*/
typedef OdSmartPtr<OdNwRedLineEllipse> OdNwRedLineEllipsePtr;

#endif //__NWREDLINEELLIPSE_INCLUDED_
