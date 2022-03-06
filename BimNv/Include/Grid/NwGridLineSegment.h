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
#ifndef __TNW_GRIDLINESEGMENT_H__
#define __TNW_GRIDLINESEGMENT_H__

#include "NwObject.h"
#include "Grid/NwGridTypes.h"

class OdGeLine2d;
class OdGePoint2d;

/** \details
  This template class is a specialization of the OdArray class for OdGePoint2d objects.
*/
typedef OdArray<OdGePoint2d, OdMemoryAllocator<OdGePoint2d> > OdGePoint2dArray;

/** \details
  This class represents a grid segment.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwGridLineSegment : public OdNwObject 
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwGridLineSegment);
  //DOM-IGNORE-END
public:
  /** \details
    Default constructor.
  */
  OdNwGridLineSegment();

public:

  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwGridLineSegment();
  
  /** \details
    Returns the type of grid line segement.
   
    \returns Type of grid line segment.

    \remarks
    The returned type must be one of the following:

   <table>
   Name                             Value     Description
   NwGridLineSegemntType::Enum::CIRCLE     2         Type circle
   NwGridLineSegemntType::Enum::LINE          5         Type line
   </table>
  */
  NwGridLineSegmentType::Enum getType() const;

  /** \details
    Returns the points of the grid line segement primitive.
    
    \returns Various points for the primitive of the grid line segment.
    
    \remarks
    If getType() returns NwGridLineSegemntType::Enum::LINE, two points are returned.
    If getType() returns NwGridLineSegemntType::Enum::CIRCLE, three points are returned.
  */
  const OdGePoint2dArray getPrimPointList() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwGridLineSegment object pointers.
*/
typedef OdSmartPtr<OdNwGridLineSegment> OdNwGridLineSegmentPtr;

#endif
