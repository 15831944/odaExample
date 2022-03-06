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

#ifndef __NWREDLINELINE_INCLUDED_
#define __NWREDLINELINE_INCLUDED_

#include "NwRedLine.h"
#include "Ge/GePoint2d.h"

/** \details
  This class represents line redline objects.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwRedLineLine: public OdNwRedLine
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwRedLineLine);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwRedLineLine object.
  */
  OdNwRedLineLine();
  
  /** \details
    Constructor for objects of the OdNwRedLineLine class. Creates a new
    OdNwRedLineLine object for the specified item.

    \param pImpl [in] Item to create an OdNwRedLineLine object for.
  */
  explicit OdNwRedLineLine(OdNwObjectImpl* pImpl);

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwRedLineLine();

public:
  /** \details
    Returns the start point.

    \returns Start point as an OdGePoint2d object.
  */
  OdGePoint2d getStart() const;
  /** \details
    Returns the end point.

    \returns End point as an OdGePoint2d object.
  */
  OdGePoint2d getEnd() const;

public:
  /** \details
    Sets the start point.

    \param val [in] New start point.
  */
  void setStart(const OdGePoint2d& val);
  /** \details
    Sets the end point.

    \param val [in] New end point.
  */
  void setEnd(const OdGePoint2d& val);
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwRedLineLine object pointers.
*/
typedef OdSmartPtr<OdNwRedLineLine> OdNwRedLineLinePtr;

#endif //__NWREDLINELINE_INCLUDED_
