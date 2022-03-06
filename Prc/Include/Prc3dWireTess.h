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

#ifndef _PRC3DWIRETESS_INCLUDED_
#define _PRC3DWIRETESS_INCLUDED_ 
 

#include "PrcBaseTessData.h"
#include "PrcArrayRgba.h"

/** \details 
<group PRC_Tessellation_Classes> 

Class representing tessellation data for a 3D wire edge.
*/
class PRC_TOOLKIT OdPrc3dWireTess : public OdPrcBaseTessData
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_TESS(OdPrc3dWireTess);
  //DOM-IGNORE-END

  /** \details
    Returns current wire indexes of the tessellation.
    Wire indexes are returned as a reference to an OdUInt32Array object, therefore it can be used to set a new wire index array for the tessellation.
  */
  OdUInt32Array &wireIndexes();

  /** \details
    Returns current wire indexes of the tessellation.
  */
  const OdUInt32Array &wireIndexes() const;

  /** \details
    Returns current RGBA colors of the tessellation.
    RGBA colors are returned as a reference to an OdUInt32Array object, therefore it can be used to set new RGBA colors for the tessellation.
  */
  OdPrcArrayRgba &arrayRGBA();

  /** \details
    Returns current RGBA colors of the tessellation.
  */
  const OdPrcArrayRgba &arrayRGBA() const;

  /** \details
    Returns current coordinates of the tessellation. 
    Coordinates are returned as a reference to an OdFloatArray object, therefore it can be used to set new coordinates for the tessellation.
  */
  OdFloatArray &coordinates();

  /** \details
    Returns current coordinates of the tessellation. 
  */
  const OdFloatArray &coordinates() const;

  /** \details
    Sets a new value of the color segment flag.
    Color segment flag indicates that every segment of the tessellation can have its own color.

    \param is_segment_color [in] A boolean value of the flag.
  */
  void setIsSegmentColor(bool is_segment_color);

  /** \details
    Returns the current value of the color segment flag.
    Color segment flag indicates that every segment of the tessellation can have its own color.
  */
  bool isSegmentColor() const;

  /** \details
    Sets a new value of the calculation flag.
    Calculation flag determines whether tessellation data was calculated during import or retrieved from an original CAD application.

    \param is_calculated [in] A boolean value of the flag.
  */
  void setIsCalculated(bool is_calculated);
  
  /** \details
    Returns the current value the calculation flag.
    Calculation flag determines whether tessellation data was calculated during import or retrieved from an original CAD application.
    Method returns true if data was calculated or false in the other case.
  */
  bool isCalculated() const;
};

SMARTPTR(OdPrc3dWireTess);

#endif // _PRC3DWIRETESS_INCLUDED_

