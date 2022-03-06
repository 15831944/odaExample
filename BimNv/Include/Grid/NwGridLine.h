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
#ifndef __TNW_GRIDLINE_H__
#define __TNW_GRIDLINE_H__

#include "NwObject.h"

class OdNwGridLineSegment;
class OdGePoint2d;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwGridLineSegment object pointers.
*/
typedef OdSmartPtr<OdNwGridLineSegment> OdNwGridLineSegmentPtr;

/** \details
  This class represents a grid line.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwGridLine : public OdNwObject
{

  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwGridLine);
  //DOM-IGNORE-END
public:
  /** \details
    Default constructor.
  */
  OdNwGridLine();
public:

  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwGridLine();
  
  /** \details
    Gets an array of the grid line segments contained in the grid line.

    \param gridLineSegmentList [out] OdArray with OdNwGridLineSegment smart pointers as values.
    \returns eOk if the sceneRefs are retrieved successfully, or an appropriate error code otherwise.
  */
  OdResult getGridLineSegmentList(OdArray<OdNwGridLineSegmentPtr> & gridLineSegmentList) const;

  /** \details
    Returns the display name of the grid line.

    \returns Grid line display name.
  */
  const OdString getName() const;
  
  /** \details
    Returns the point of the grid line.
  
    \returns Grid line point.
  */
  const OdGePoint2d getPoint() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwGridLine object pointers.
*/
typedef OdSmartPtr<OdNwGridLine> OdNwGridLinePtr;
#endif
